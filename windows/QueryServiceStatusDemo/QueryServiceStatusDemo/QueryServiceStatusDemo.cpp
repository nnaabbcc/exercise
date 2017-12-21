
#include <stdio.h>
#include <Windows.h>


void print_service_status_process(SERVICE_STATUS_PROCESS& status)
{
    // status.dwServiceType
    printf("dwServiceType = ");
    switch (status.dwServiceType)
    {
    case SERVICE_FILE_SYSTEM_DRIVER:
        printf("SERVICE_FILE_SYSTEM_DRIVER");
        break;
    case SERVICE_KERNEL_DRIVER:
        printf("SERVICE_KERNEL_DRIVER");
        break;
    case SERVICE_WIN32_OWN_PROCESS:
        printf("SERVICE_WIN32_OWN_PROCESS");
        break;
    case SERVICE_WIN32_SHARE_PROCESS:
        printf("SERVICE_WIN32_SHARE_PROCESS");
        break;
    case SERVICE_INTERACTIVE_PROCESS:
        printf("SERVICE_INTERACTIVE_PROCESS");
        break;
    default:
        printf("Unknown Service Type %d", status.dwServiceType);
    }
    printf("\n");
}

void query_service_status()
{
    SC_HANDLE schSCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);

    DWORD bytesNeeded = 0;
    DWORD serviceReturned = 0;

    EnumServicesStatusExW(schSCManager,
        SC_ENUM_PROCESS_INFO,
        SERVICE_DRIVER | SERVICE_WIN32,
        SERVICE_STATE_ALL,
        nullptr,
        0,
        &bytesNeeded,
        &serviceReturned,
        nullptr,
        nullptr);

    if (ERROR_MORE_DATA == GetLastError())
    {
        printf("%d, %d\n", bytesNeeded, serviceReturned);

        BYTE* pMemory = new BYTE[bytesNeeded];
        BOOL ret = EnumServicesStatusExW(schSCManager,
            SC_ENUM_PROCESS_INFO,
            SERVICE_DRIVER | SERVICE_WIN32,
            SERVICE_STATE_ALL,
            pMemory,
            bytesNeeded,
            &bytesNeeded,
            &serviceReturned,
            nullptr,
            nullptr);
        if (ret)
        {
            printf("EnumServiceStatus success\n");
            printf("Got %d service status\n", serviceReturned);
            printf("\n");

            ENUM_SERVICE_STATUS_PROCESSW *pService = static_cast<ENUM_SERVICE_STATUS_PROCESSW*>(static_cast<void*>(pMemory));
            for (DWORD i = 0; i < serviceReturned; i++, pService++)
            {
                printf("==================== %d =======================\n", i + 1);
                wprintf(L"ServiceName = %s\n", pService->lpServiceName);
                wprintf(L"DisplayName = %s\n", pService->lpDisplayName);
                print_service_status_process(pService->ServiceStatusProcess);
                printf("\n");
            }
        }
        else
        {
            printf("EnumServiceStatus failed\n");
        }
        delete[] pMemory;
    }
    else {
        printf("unknown error\n");
    }

    CloseServiceHandle(schSCManager);
}

int main()
{
    query_service_status();
    return 0;
}

