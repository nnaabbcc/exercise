/*
ImDisk Virtual Disk Driver for Windows NT/2000/XP.
This driver emulates harddisk partitions, floppy drives and CD/DVD-ROM
drives from disk image files, in virtual memory or by redirecting I/O
requests somewhere else, possibly to another machine, through a
co-operating user-mode service, ImDskSvc.

Copyright (C) 2005-2015 Olof Lagerkvist.

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

This source file contains some GNU GPL licensed code:
- Parts related to floppy emulation based on VFD by Ken Kato.
http://chitchat.at.infoseek.co.jp/vmware/vfd.html
Copyright (C) Free Software Foundation, Inc.
Read gpl.txt for the full GNU GPL license.

This source file may contain BSD licensed code:
- Some code ported to NT from the FreeBSD md driver by Olof Lagerkvist.
http://www.ltr-data.se
Copyright (C) The FreeBSD Project.
Copyright (C) The Regents of the University of California.
*/

#include "imdsksys.h"

NTSTATUS
ImDiskCallProxy(IN PPROXY_CONNECTION Proxy,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    IN PKEVENT CancelEvent OPTIONAL,
    IN PVOID RequestHeader,
    IN ULONG RequestHeaderSize,
    IN PVOID RequestData,
    IN ULONG RequestDataSize,
    IN OUT PVOID ResponseHeader,
    IN ULONG ResponseHeaderSize,
    IN OUT PVOID ResponseData,
    IN ULONG ResponseDataBufferSize,
    IN ULONG *ResponseDataSize)
{
    NTSTATUS status;

    ASSERT(Proxy != NULL);

    switch (Proxy->connection_type)
    {
    case PROXY_CONNECTION::PROXY_CONNECTION_DEVICE:
    {
        PUCHAR io_buffer = NULL;
        PUCHAR temp_buffer = NULL;
        ULONG io_size = RequestHeaderSize + RequestDataSize;

        if ((RequestHeaderSize > 0) &&
            (RequestDataSize > 0))
        {
            temp_buffer = (PUCHAR)
                ExAllocatePoolWithTag(NonPagedPool, io_size, POOL_TAG);

            if (temp_buffer == NULL)
            {
                KdPrint(("ImDisk Proxy Client: Memory allocation failed.\n."));

                IoStatusBlock->Status = STATUS_INSUFFICIENT_RESOURCES;
                IoStatusBlock->Information = 0;
                return IoStatusBlock->Status;
            }

            if (RequestHeaderSize > 0)
            {
                RtlCopyMemory(temp_buffer, RequestHeader, RequestHeaderSize);
            }

            if (RequestDataSize > 0)
            {
                RtlCopyMemory(temp_buffer + RequestHeaderSize, RequestData, RequestDataSize);
            }

            io_buffer = temp_buffer;
        }
        else if (RequestHeaderSize > 0)
        {
            io_buffer = (PUCHAR)RequestHeader;
        }
        else if (RequestDataSize > 0)
        {
            io_buffer = (PUCHAR)RequestData;
        }

        if (io_size > 0)
        {
            if (CancelEvent != NULL ?
                KeReadStateEvent(CancelEvent) != 0 :
                FALSE)
            {
                KdPrint(("ImDisk Proxy Client: Request cancelled.\n."));

                if (temp_buffer != NULL)
                {
                    ExFreePoolWithTag(temp_buffer, POOL_TAG);
                }

                IoStatusBlock->Status = STATUS_CANCELLED;
                IoStatusBlock->Information = 0;
                return IoStatusBlock->Status;
            }

            status = ImDiskSafeIOStream(Proxy->device,
                IRP_MJ_WRITE,
                IoStatusBlock,
                CancelEvent,
                io_buffer,
                io_size);

            if (!NT_SUCCESS(status))
            {
                KdPrint(("ImDisk Proxy Client: Request error %#x\n.",
                    status));

                if (temp_buffer != NULL)
                {
                    ExFreePoolWithTag(temp_buffer, POOL_TAG);
                }

                IoStatusBlock->Status = STATUS_IO_DEVICE_ERROR;
                IoStatusBlock->Information = 0;
                return IoStatusBlock->Status;
            }
        }

        if (temp_buffer != NULL)
        {
            ExFreePoolWithTag(temp_buffer, POOL_TAG);
        }

        if (ResponseHeaderSize > 0)
        {
            if (CancelEvent != NULL ?
                KeReadStateEvent(CancelEvent) != 0 :
                FALSE)
            {
                KdPrint(("ImDisk Proxy Client: Request cancelled.\n."));

                IoStatusBlock->Status = STATUS_CANCELLED;
                IoStatusBlock->Information = 0;
                return IoStatusBlock->Status;
            }

            status = ImDiskSafeIOStream(Proxy->device,
                IRP_MJ_READ,
                IoStatusBlock,
                CancelEvent,
                ResponseHeader,
                ResponseHeaderSize);

            if (!NT_SUCCESS(status))
            {
                KdPrint(("ImDisk Proxy Client: Response header error %#x\n.",
                    status));

                IoStatusBlock->Status = STATUS_IO_DEVICE_ERROR;
                IoStatusBlock->Information = 0;
                return IoStatusBlock->Status;
            }
        }

        if (ResponseDataSize != NULL && *ResponseDataSize > 0)
        {
            if (*ResponseDataSize > ResponseDataBufferSize)
            {
                KdPrint(("ImDisk Proxy Client: Fatal: Request %u bytes, "
                    "receiving %u bytes.\n",
                    ResponseDataBufferSize, *ResponseDataSize));

                IoStatusBlock->Status = STATUS_IO_DEVICE_ERROR;
                IoStatusBlock->Information = 0;
                return IoStatusBlock->Status;
            }

            if (CancelEvent != NULL ?
                KeReadStateEvent(CancelEvent) != 0 :
                FALSE)
            {
                KdPrint(("ImDisk Proxy Client: Request cancelled.\n."));

                IoStatusBlock->Status = STATUS_CANCELLED;
                IoStatusBlock->Information = 0;
                return IoStatusBlock->Status;
            }

            KdPrint2
                (("ImDisk Proxy Client: Got ok resp. Waiting for data.\n"));

            status = ImDiskSafeIOStream(Proxy->device,
                IRP_MJ_READ,
                IoStatusBlock,
                CancelEvent,
                ResponseData,
                *ResponseDataSize);

            if (!NT_SUCCESS(status))
            {
                KdPrint(("ImDisk Proxy Client: Response data error %#x\n.",
                    status));

                KdPrint(("ImDisk Proxy Client: Response data %u bytes, "
                    "got %u bytes.\n",
                    *ResponseDataSize,
                    (ULONG)IoStatusBlock->Information));

                IoStatusBlock->Status = STATUS_IO_DEVICE_ERROR;
                IoStatusBlock->Information = 0;
                return IoStatusBlock->Status;
            }

            KdPrint2
                (("ImDisk Proxy Client: Received %u byte data stream.\n",
                    IoStatusBlock->Information));
        }

        IoStatusBlock->Status = STATUS_SUCCESS;

        IoStatusBlock->Information = RequestDataSize;

        if (ResponseDataSize != NULL)
        {
            IoStatusBlock->Information += *ResponseDataSize;
        }

        return IoStatusBlock->Status;
    }

    case PROXY_CONNECTION::PROXY_CONNECTION_SHM:
    {
        PKEVENT wait_objects[] = {
            Proxy->response_event,
            CancelEvent
        };

        ULONG number_of_wait_objects = CancelEvent != NULL ? 2 : 1;

        // Some parameter sanity checks
        if ((RequestHeaderSize > IMDPROXY_HEADER_SIZE) |
            (ResponseHeaderSize > IMDPROXY_HEADER_SIZE) |
            ((RequestDataSize + IMDPROXY_HEADER_SIZE) >
                Proxy->shared_memory_size))
        {
            KdPrint(("ImDisk Proxy Client: "
                "Parameter values not supported.\n."));

            IoStatusBlock->Status = STATUS_INVALID_BUFFER_SIZE;
            IoStatusBlock->Information = 0;
            return IoStatusBlock->Status;
        }

        IoStatusBlock->Information = 0;

        if (RequestHeaderSize > 0)
            RtlCopyMemory(Proxy->shared_memory,
                RequestHeader,
                RequestHeaderSize);

        if (RequestDataSize > 0)
            RtlCopyMemory(Proxy->shared_memory + IMDPROXY_HEADER_SIZE,
                RequestData,
                RequestDataSize);

#pragma warning(suppress: 28160)
        KeSetEvent(Proxy->request_event, (KPRIORITY)0, TRUE);

        status = KeWaitForMultipleObjects(number_of_wait_objects,
            (PVOID*)wait_objects,
            WaitAny,
            Executive,
            KernelMode,
            FALSE,
            NULL,
            NULL);

        if (status == STATUS_WAIT_1)
        {
            KdPrint(("ImDisk Proxy Client: Incomplete wait %#x.\n.", status));

            IoStatusBlock->Status = STATUS_CANCELLED;
            IoStatusBlock->Information = 0;
            return IoStatusBlock->Status;
        }

        if (ResponseHeaderSize > 0)
            RtlCopyMemory(ResponseHeader,
                Proxy->shared_memory,
                ResponseHeaderSize);

        // If server end requests to send more data than we requested, we
        // treat that as an unrecoverable device error and exit.
        if (ResponseDataSize != NULL ? *ResponseDataSize > 0 : FALSE)
            if ((*ResponseDataSize > ResponseDataBufferSize) |
                ((*ResponseDataSize + IMDPROXY_HEADER_SIZE) >
                    Proxy->shared_memory_size))
            {
                KdPrint(("ImDisk Proxy Client: Invalid response size %u.\n.",
                    *ResponseDataSize));

                IoStatusBlock->Status = STATUS_IO_DEVICE_ERROR;
                IoStatusBlock->Information = 0;
                return IoStatusBlock->Status;
            }
            else
            {
                RtlCopyMemory(ResponseData,
                    Proxy->shared_memory + IMDPROXY_HEADER_SIZE,
                    *ResponseDataSize);

                IoStatusBlock->Information = *ResponseDataSize;
            }

        IoStatusBlock->Status = STATUS_SUCCESS;
        if ((RequestDataSize > 0) & (IoStatusBlock->Information == 0))
            IoStatusBlock->Information = RequestDataSize;
        return IoStatusBlock->Status;
    }

    default:
        return STATUS_DRIVER_INTERNAL_ERROR;
    }
}

VOID
ImDiskCloseProxy(IN PPROXY_CONNECTION Proxy)
{
    ASSERT(Proxy != NULL);

    switch (Proxy->connection_type)
    {
    case PROXY_CONNECTION::PROXY_CONNECTION_DEVICE:
        if (Proxy->device != NULL)
            ObDereferenceObject(Proxy->device);

        Proxy->device = NULL;
        break;

    case PROXY_CONNECTION::PROXY_CONNECTION_SHM:
        if ((Proxy->request_event != NULL) &
            (Proxy->response_event != NULL) &
            (Proxy->shared_memory != NULL))
        {
            *(ULONGLONG*)Proxy->shared_memory = IMDPROXY_REQ_CLOSE;
            KeSetEvent(Proxy->request_event, (KPRIORITY)0, FALSE);
        }

        if (Proxy->request_event_handle != NULL)
        {
            ZwClose(Proxy->request_event_handle);
            Proxy->request_event_handle = NULL;
        }

        if (Proxy->response_event_handle != NULL)
        {
            ZwClose(Proxy->response_event_handle);
            Proxy->response_event_handle = NULL;
        }

        if (Proxy->request_event != NULL)
        {
            ObDereferenceObject(Proxy->request_event);
            Proxy->request_event = NULL;
        }

        if (Proxy->response_event != NULL)
        {
            ObDereferenceObject(Proxy->response_event);
            Proxy->response_event = NULL;
        }

        if (Proxy->shared_memory != NULL)
        {
            ZwUnmapViewOfSection(NtCurrentProcess(), Proxy->shared_memory);
            Proxy->shared_memory = NULL;
        }

        break;
    }
}

#pragma code_seg("PAGE")

///
/// Note that this function when successful replaces the Proxy->device pointer
/// to point to the connected device object instead of the proxy service pipe.
/// This means that the only reference to the proxy service pipe after calling
/// this function is the original handle to the pipe.
///
NTSTATUS
ImDiskConnectProxy(IN OUT PPROXY_CONNECTION Proxy,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    IN PKEVENT CancelEvent OPTIONAL,
    IN ULONG Flags,
    IN PWSTR ConnectionString,
    IN USHORT ConnectionStringLength)
{
    IMDPROXY_CONNECT_REQ connect_req;
    IMDPROXY_CONNECT_RESP connect_resp;
    NTSTATUS status;

    PAGED_CODE();

    ASSERT(Proxy != NULL);
    ASSERT(IoStatusBlock != NULL);
    ASSERT(ConnectionString != NULL);

    if (IMDISK_PROXY_TYPE(Flags) == IMDISK_PROXY_TYPE_SHM)
    {
        OBJECT_ATTRIBUTES object_attributes;
        UNICODE_STRING base_name = { 0 };
        UNICODE_STRING event_name = { 0 };
        base_name.Buffer = ConnectionString;
        base_name.Length = ConnectionStringLength;
        base_name.MaximumLength = ConnectionStringLength;
        event_name.MaximumLength = ConnectionStringLength + 20;
        event_name.Buffer =
            (PWCHAR)ExAllocatePoolWithTag(PagedPool,
                event_name.MaximumLength,
                POOL_TAG);
        if (event_name.Buffer == NULL)
        {
            status = STATUS_INSUFFICIENT_RESOURCES;

            IoStatusBlock->Status = status;
            IoStatusBlock->Information = 0;
            return IoStatusBlock->Status;
        }

        InitializeObjectAttributes(&object_attributes,
            &event_name,
            OBJ_CASE_INSENSITIVE,
            NULL,
            NULL);

        RtlCopyUnicodeString(&event_name, &base_name);
        RtlAppendUnicodeToString(&event_name, L"_Request");

        status = ZwOpenEvent(&Proxy->request_event_handle,
            EVENT_ALL_ACCESS,
            &object_attributes);

        if (!NT_SUCCESS(status))
        {
            Proxy->request_event_handle = NULL;
            ExFreePoolWithTag(event_name.Buffer, POOL_TAG);

            IoStatusBlock->Status = status;
            IoStatusBlock->Information = 0;
            return IoStatusBlock->Status;
        }

        status = ObReferenceObjectByHandle(Proxy->request_event_handle,
            EVENT_ALL_ACCESS,
            *ExEventObjectType,
            KernelMode,
            (PVOID*)&Proxy->request_event,
            NULL);

        if (!NT_SUCCESS(status))
        {
            Proxy->request_event = NULL;
            ExFreePoolWithTag(event_name.Buffer, POOL_TAG);

            IoStatusBlock->Status = status;
            IoStatusBlock->Information = 0;
            return IoStatusBlock->Status;
        }

        RtlCopyUnicodeString(&event_name, &base_name);
        RtlAppendUnicodeToString(&event_name, L"_Response");

        status = ZwOpenEvent(&Proxy->response_event_handle,
            EVENT_ALL_ACCESS,
            &object_attributes);

        if (!NT_SUCCESS(status))
        {
            Proxy->response_event_handle = NULL;
            ExFreePoolWithTag(event_name.Buffer, POOL_TAG);

            IoStatusBlock->Status = status;
            IoStatusBlock->Information = 0;
            return IoStatusBlock->Status;
        }

        status = ObReferenceObjectByHandle(Proxy->response_event_handle,
            EVENT_ALL_ACCESS,
            *ExEventObjectType,
            KernelMode,
            (PVOID*)&Proxy->response_event,
            NULL);

        if (!NT_SUCCESS(status))
        {
            Proxy->response_event = NULL;
            ExFreePoolWithTag(event_name.Buffer, POOL_TAG);

            IoStatusBlock->Status = status;
            IoStatusBlock->Information = 0;
            return IoStatusBlock->Status;
        }

        IoStatusBlock->Status = STATUS_SUCCESS;
        IoStatusBlock->Information = 0;
        return IoStatusBlock->Status;
    }

    connect_req.request_code = IMDPROXY_REQ_CONNECT;
    connect_req.flags = Flags;
    connect_req.length = ConnectionStringLength;

    KdPrint(("ImDisk Proxy Client: Sending IMDPROXY_CONNECT_REQ.\n"));

    status = ImDiskCallProxy(Proxy,
        IoStatusBlock,
        CancelEvent,
        &connect_req,
        sizeof(connect_req),
        ConnectionString,
        ConnectionStringLength,
        &connect_resp,
        sizeof(IMDPROXY_CONNECT_RESP),
        NULL,
        0,
        NULL);

    if (!NT_SUCCESS(status))
    {
        IoStatusBlock->Status = status;
        IoStatusBlock->Information = 0;
        return IoStatusBlock->Status;
    }

    if (connect_resp.error_code != 0)
    {
        IoStatusBlock->Status = STATUS_CONNECTION_REFUSED;
        IoStatusBlock->Information = 0;
        return IoStatusBlock->Status;
    }

    // If the proxy gave us a reference to an object to use for direct connection
    // to the server we have to change the active reference to use here.
    if (connect_resp.object_ptr != 0)
    {
        // First check that connect_resp.object_ptr is really something we have
        // referenced earlier.

        KEVENT event;
        IO_STATUS_BLOCK io_status;
        PIRP irp;

        KeInitializeEvent(&event, NotificationEvent, FALSE);

        irp = IoBuildDeviceIoControlRequest(
            IOCTL_IMDISK_GET_REFERENCED_HANDLE,
            ImDiskCtlDevice,
            &connect_resp.object_ptr,
            sizeof(PFILE_OBJECT),
            NULL,
            0,
            TRUE,
            &event,
            &io_status);

        if (irp == NULL)
        {
            IoStatusBlock->Status = STATUS_INSUFFICIENT_RESOURCES;
            IoStatusBlock->Information = 0;
            return IoStatusBlock->Status;
        }

        status = IoCallDriver(ImDiskCtlDevice, irp);

        if (status == STATUS_PENDING)
        {
            KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
        }

        if (!NT_SUCCESS(status))
        {
            DbgPrint("ImDisk: Failed claiming referenced object %p: %#x\n",
                (PVOID)(ULONG_PTR)connect_resp.object_ptr, status);

            IoStatusBlock->Status = status;
            IoStatusBlock->Information = 0;
            return IoStatusBlock->Status;
        }

        ObDereferenceObject(Proxy->device);
        Proxy->device = (PFILE_OBJECT)(ULONG_PTR)connect_resp.object_ptr;
    }

    KdPrint(("ImDisk Proxy Client: Got ok response IMDPROXY_CONNECT_RESP.\n"));

    IoStatusBlock->Status = STATUS_SUCCESS;
    IoStatusBlock->Information = 0;
    return IoStatusBlock->Status;
}

NTSTATUS
ImDiskQueryInformationProxy(IN PPROXY_CONNECTION Proxy,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    IN PKEVENT CancelEvent,
    OUT PIMDPROXY_INFO_RESP ProxyInfoResponse,
    IN ULONG ProxyInfoResponseLength)
{
    ULONGLONG proxy_req = IMDPROXY_REQ_INFO;
    NTSTATUS status;

    PAGED_CODE();

    ASSERT(Proxy != NULL);
    ASSERT(IoStatusBlock != NULL);

    if ((ProxyInfoResponse == NULL) |
        (ProxyInfoResponseLength < sizeof(IMDPROXY_INFO_RESP)))
    {
        IoStatusBlock->Status = STATUS_BUFFER_OVERFLOW;
        IoStatusBlock->Information = 0;
        return IoStatusBlock->Status;
    }

    KdPrint(("ImDisk Proxy Client: Sending IMDPROXY_REQ_INFO.\n"));

    status = ImDiskCallProxy(Proxy,
        IoStatusBlock,
        CancelEvent,
        &proxy_req,
        sizeof(proxy_req),
        NULL,
        0,
        ProxyInfoResponse,
        sizeof(IMDPROXY_INFO_RESP),
        NULL,
        0,
        NULL);

    if (!NT_SUCCESS(status))
    {
        IoStatusBlock->Status = status;
        IoStatusBlock->Information = 0;
        return IoStatusBlock->Status;
    }

    KdPrint(("ImDisk Proxy Client: Got ok response IMDPROXY_INFO_RESP.\n"));

    if (ProxyInfoResponse->req_alignment - 1 > FILE_512_BYTE_ALIGNMENT)
    {
#pragma warning(suppress: 6064)
#pragma warning(suppress: 6328)
        KdPrint(("ImDisk IMDPROXY_INFO_RESP: Unsupported sizes. "
            "Got 0x%.8x%.8x size and 0x%.8x%.8x alignment.\n",
            ProxyInfoResponse->file_size,
            ProxyInfoResponse->req_alignment));

        IoStatusBlock->Status = STATUS_INVALID_PARAMETER;
        IoStatusBlock->Information = 0;
        return IoStatusBlock->Status;
    }

    IoStatusBlock->Status = STATUS_SUCCESS;
    IoStatusBlock->Information = 0;
    return IoStatusBlock->Status;
}

#pragma code_seg()

NTSTATUS
ImDiskReadProxy(IN PPROXY_CONNECTION Proxy,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    IN PKEVENT CancelEvent,
    OUT PVOID Buffer,
    IN ULONG Length,
    IN PLARGE_INTEGER ByteOffset)
{
    IMDPROXY_READ_REQ read_req;
    IMDPROXY_READ_RESP read_resp;
    NTSTATUS status;
    ULONG_PTR max_transfer_size;
    ULONG length_done;

    ASSERT(Proxy != NULL);
    ASSERT(IoStatusBlock != NULL);
    ASSERT(Buffer != NULL);
    ASSERT(ByteOffset != NULL);

    if (Proxy->connection_type == PROXY_CONNECTION::PROXY_CONNECTION_SHM)
        max_transfer_size = Proxy->shared_memory_size - IMDPROXY_HEADER_SIZE;
    else
        max_transfer_size = Length;

    length_done = 0;
    status = STATUS_SUCCESS;

    while (length_done < Length)
    {
        ULONG length_to_do = Length - length_done;

        KdPrint2(("ImDisk Proxy Client: "
            "IMDPROXY_REQ_READ 0x%.8x done 0x%.8x left to do.\n",
            length_done, length_to_do));

        read_req.request_code = IMDPROXY_REQ_READ;
        read_req.offset = ByteOffset->QuadPart + length_done;
        read_req.length =
            length_to_do <= max_transfer_size ?
            length_to_do : max_transfer_size;

        KdPrint2(("ImDisk Proxy Client: "
            "IMDPROXY_REQ_READ 0x%.8x%.8x bytes at 0x%.8x%.8x.\n",
            ((PLARGE_INTEGER)&read_req.length)->HighPart,
            ((PLARGE_INTEGER)&read_req.length)->LowPart,
            ((PLARGE_INTEGER)&read_req.offset)->HighPart,
            ((PLARGE_INTEGER)&read_req.offset)->LowPart));

        status = ImDiskCallProxy(Proxy,
            IoStatusBlock,
            CancelEvent,
            &read_req,
            sizeof(read_req),
            NULL,
            0,
            &read_resp,
            sizeof(read_resp),
            (PUCHAR)Buffer + length_done,
            (ULONG)read_req.length,
            (PULONG)&read_resp.length);

        if (!NT_SUCCESS(status))
        {
            IoStatusBlock->Status = STATUS_IO_DEVICE_ERROR;
            IoStatusBlock->Information = length_done;
            return IoStatusBlock->Status;
        }

        length_done += (ULONG)read_resp.length;

        if (read_resp.errorno != 0)
        {
#pragma warning(suppress: 6064)
#pragma warning(suppress: 6328)
            KdPrint(("ImDisk Proxy Client: Server returned error 0x%.8x%.8x.\n",
                read_resp.errorno));
            IoStatusBlock->Status = STATUS_IO_DEVICE_ERROR;
            IoStatusBlock->Information = length_done;
            return IoStatusBlock->Status;
        }

        KdPrint2(("ImDisk Proxy Client: Server sent 0x%.8x%.8x bytes.\n",
            ((PLARGE_INTEGER)&read_resp.length)->HighPart,
            ((PLARGE_INTEGER)&read_resp.length)->LowPart));

        if (read_resp.length == 0)
            break;
    }

    IoStatusBlock->Status = status;
    IoStatusBlock->Information = length_done;

    return status;
}

NTSTATUS
ImDiskWriteProxy(IN PPROXY_CONNECTION Proxy,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    IN PKEVENT CancelEvent,
    IN PVOID Buffer,
    IN ULONG Length,
    IN PLARGE_INTEGER ByteOffset)
{
    IMDPROXY_WRITE_REQ write_req;
    IMDPROXY_WRITE_RESP write_resp;
    NTSTATUS status;
    ULONG_PTR max_transfer_size;
    ULONG length_done;

    ASSERT(Proxy != NULL);
    ASSERT(IoStatusBlock != NULL);
    ASSERT(Buffer != NULL);
    ASSERT(ByteOffset != NULL);

    if (Proxy->connection_type == PROXY_CONNECTION::PROXY_CONNECTION_SHM)
        max_transfer_size = Proxy->shared_memory_size - IMDPROXY_HEADER_SIZE;
    else
        max_transfer_size = Length;

    length_done = 0;
    status = STATUS_SUCCESS;

    while (length_done < Length)
    {
        ULONG length_to_do = Length - length_done;

        KdPrint2(("ImDisk Proxy Client: "
            "IMDPROXY_REQ_WRITE 0x%.8x done 0x%.8x left to do.\n",
            length_done, length_to_do));

        write_req.request_code = IMDPROXY_REQ_WRITE;
        write_req.offset = ByteOffset->QuadPart + length_done;
        write_req.length =
            length_to_do <= max_transfer_size ?
            length_to_do : max_transfer_size;

        KdPrint2(("ImDisk Proxy Client: "
            "IMDPROXY_REQ_WRITE 0x%.8x%.8x bytes at 0x%.8x%.8x.\n",
            ((PLARGE_INTEGER)&write_req.length)->HighPart,
            ((PLARGE_INTEGER)&write_req.length)->LowPart,
            ((PLARGE_INTEGER)&write_req.offset)->HighPart,
            ((PLARGE_INTEGER)&write_req.offset)->LowPart));

        status = ImDiskCallProxy(Proxy,
            IoStatusBlock,
            CancelEvent,
            &write_req,
            sizeof(write_req),
            (PUCHAR)Buffer + length_done,
            (ULONG)write_req.length,
            &write_resp,
            sizeof(write_resp),
            NULL,
            0,
            NULL);

        if (!NT_SUCCESS(status))
        {
            IoStatusBlock->Status = STATUS_IO_DEVICE_ERROR;
            IoStatusBlock->Information = length_done;
            return IoStatusBlock->Status;
        }

        if (write_resp.errorno != 0)
        {
#pragma warning(suppress: 6064)
#pragma warning(suppress: 6328)
            KdPrint(("ImDisk Proxy Client: Server returned error 0x%.8x%.8x.\n",
                write_resp.errorno));
            IoStatusBlock->Status = STATUS_IO_DEVICE_ERROR;
            IoStatusBlock->Information = length_done;
            return IoStatusBlock->Status;
        }

        if (write_resp.length != write_req.length)
        {
            KdPrint(("ImDisk Proxy Client: IMDPROXY_REQ_WRITE %u bytes, "
                "IMDPROXY_RESP_WRITE %u bytes.\n",
                Length,
                (ULONG)write_resp.length));
            IoStatusBlock->Status = STATUS_IO_DEVICE_ERROR;
            IoStatusBlock->Information = length_done;
            return IoStatusBlock->Status;
        }

        KdPrint2(("ImDisk Proxy Client: Server replied OK.\n"));

        length_done += (ULONG)write_req.length;
    }

    IoStatusBlock->Status = STATUS_SUCCESS;
    IoStatusBlock->Information = length_done;
    return IoStatusBlock->Status;
}

NTSTATUS
ImDiskUnmapOrZeroProxy(IN PPROXY_CONNECTION Proxy,
    IN ULONGLONG RequestCode,
    IN OUT PIO_STATUS_BLOCK IoStatusBlock,
    IN PKEVENT CancelEvent OPTIONAL,
    IN ULONG Items,
    IN PDEVICE_DATA_SET_RANGE Ranges)
{
    IMDPROXY_UNMAP_REQ unmap_req;
    IMDPROXY_UNMAP_RESP unmap_resp;
    NTSTATUS status;
    ULONG byte_size = (ULONG)(Items * sizeof(DEVICE_DATA_SET_RANGE));

    ASSERT(Proxy != NULL);
    ASSERT(IoStatusBlock != NULL);
    ASSERT(Ranges != NULL);

    if ((Proxy->connection_type == PROXY_CONNECTION::PROXY_CONNECTION_SHM) &&
        (byte_size >= (Proxy->shared_memory_size - IMDPROXY_HEADER_SIZE)))
    {
        status = STATUS_BUFFER_OVERFLOW;
        IoStatusBlock->Information = 0;
        IoStatusBlock->Status = status;
        return status;
    }

    status = STATUS_SUCCESS;

    unmap_req.request_code = RequestCode;
    unmap_req.length = byte_size;

#pragma warning(suppress: 6064)
#pragma warning(suppress: 6328)
    KdPrint(("ImDisk Proxy Client: Unmap/Zero 0x%.8x%.8x\n", RequestCode));

    status = ImDiskCallProxy(Proxy,
        IoStatusBlock,
        CancelEvent,
        &unmap_req,
        sizeof(unmap_req),
        (PUCHAR)Ranges,
        (ULONG)unmap_req.length,
        &unmap_resp,
        sizeof(unmap_resp),
        NULL,
        0,
        NULL);

    if (!NT_SUCCESS(status))
    {
        IoStatusBlock->Status = status;
        IoStatusBlock->Information = 0;
        return status;
    }

    if (unmap_resp.errorno != 0)
    {
#pragma warning(suppress: 6064)
#pragma warning(suppress: 6328)
        KdPrint(("ImDisk Proxy Client: Server returned error 0x%.8x%.8x.\n",
            unmap_resp.errorno));
        IoStatusBlock->Status = STATUS_IO_DEVICE_ERROR;
        IoStatusBlock->Information = 0;
        return IoStatusBlock->Status;
    }

    KdPrint(("ImDisk Proxy Client: Server replied OK.\n"));

    IoStatusBlock->Status = STATUS_SUCCESS;
    IoStatusBlock->Information = 0;
    return IoStatusBlock->Status;
}

