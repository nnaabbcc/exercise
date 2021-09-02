/* displays pnp function instances */

#include <stdio.h>
#include <FunctionDiscovery.h>

HRESULT PrintFIs(IFunctionInstanceCollection* FIs);

int __cdecl wmain(
    __in int argc, 
    __in_ecount(argc) PWSTR
)
{
    HRESULT hr = S_OK;
    IFunctionDiscovery *pFD = NULL;
    IFunctionInstanceCollectionQuery *pPnpQuery = NULL;
    IFunctionInstanceCollection *pFICollection = NULL;

    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    // CoCreate FunctionDiscovery
    if (S_OK == hr)
    {
        hr = CoCreateInstance(
                __uuidof(FunctionDiscovery),
                NULL,
                CLSCTX_ALL,
                __uuidof(IFunctionDiscovery),
                (PVOID*)&pFD);
    }

    // Query the pnp provider
    if (S_OK == hr)
    {
        hr = pFD->CreateInstanceCollectionQuery(
                FCTN_CATEGORY_PNP, // pnp category (defined in functiondiscoverycategories.h)
                NULL,              // subcategory
                FALSE,             // include subcategories
                NULL,              // notification callback
                NULL,              // context
                &pPnpQuery);       // FI collection query
    }

    // * optional *
    // add property constraints
    // generally only works with core FD properties, and not provider specific properties
    if (S_OK == hr)
    {
        PROPVARIANT pv;

        PropVariantClear(&pv);

        pv.vt = VT_UINT;
        pv.uintVal = 0;

        hr = pPnpQuery->AddPropertyConstraint(PKEY_FD_Visibility, &pv, QC_EQUALS);

        PropVariantClear(&pv);
    }

    // * optional *
    // add query constraints
    // refer to functiondiscoveryconstraints.h
    if (S_OK == hr)
    {
        hr = pPnpQuery->AddQueryConstraint(PNP_CONSTRAINTVALUE_NOTPRESENT, FD_CONSTRAINTVALUE_TRUE);
    }

    if (S_OK == hr)
    {
        hr = pPnpQuery->Execute(&pFICollection);
    }

    if (S_OK == hr)
    {
        hr = PrintFIs(pFICollection);
    }

    // clean up
    if (pFD)
    {
        pFD->Release();
    }

    if (pPnpQuery)
    {
        pPnpQuery->Release();
    }

    if (pFICollection)
    {
        pFICollection->Release();
    }

    CoUninitialize();

    if (S_OK != hr)
    {
        wprintf(L"an error occured (hr == 0x%x)\n", hr);
        return 1;
    }

    return 0;
}

HRESULT PrintFIs(
    IFunctionInstanceCollection* FIs
)
{
    HRESULT hr = S_OK;
    DWORD cFIs = 0;
    IFunctionInstance *pFI = NULL;
    IFunctionInstanceCollection *pDeviceFunctionCollection = NULL;

    if (FIs)
    {
        hr = FIs->GetCount(&cFIs);

        wprintf(L"*******************************************************\n");
        wprintf(L"* %i Function Instances\n", cFIs);
        wprintf(L"*******************************************************\n\n");

        // go through each function instance
        for (DWORD i = 0; S_OK == hr && i < cFIs; i++)
        {
            hr = FIs->Item(i, &pFI);

            if (S_OK == hr)
            {
                IPropertyStore *pPropertyStore = NULL;

                pFI->OpenPropertyStore(STGM_READ, &pPropertyStore);

                if (pPropertyStore)
                {
                    PROPVARIANT pv;

                    PropVariantClear(&pv);

                    // PKEYs can be found in these headers in the SDK:
                    // functiondiscoverykeys.h functiondiscoverykeys_devpkey.h
                    // Providers do not populate all PKEYs.
                    hr = pPropertyStore->GetValue(PKEY_Device_FriendlyName, &pv);

                    if (S_OK == hr)
                    {
                        wprintf(L"Device Friendly Name : \"%s\"\n", (pv.vt == VT_LPWSTR) ? pv.pwszVal : L"");
                    }

                    PropVariantClear(&pv);


                    hr = pPropertyStore->GetValue(PKEY_Device_InstanceId, &pv);

                    if (S_OK == hr && VT_LPWSTR == pv.vt)
                    {
                        wprintf(L"\tDevice Instance ID : \"%s\"\n", pv.pwszVal);
                    }

                    PropVariantClear(&pv);

                    hr = pPropertyStore->GetValue(PKEY_Device_Class, &pv);

                    if (S_OK == hr && VT_LPWSTR == pv.vt)
                    {
                        wprintf(L"\tClass : %s",pv.pwszVal);
                    }

                    PropVariantClear(&pv);

                    hr = pPropertyStore->GetValue(PKEY_Device_ClassGuid, &pv);

                    if (S_OK == hr && VT_CLSID == pv.vt)
                    {
                        wprintf(L"\t(GUID : %x-%x-%x-%x%x-%x%x%x%x%x%x)\n",
                                pv.puuid->Data1, 
                                pv.puuid->Data2, 
                                pv.puuid->Data3, 
                                pv.puuid->Data4[0],
                                pv.puuid->Data4[1],
                                pv.puuid->Data4[2],
                                pv.puuid->Data4[3],
                                pv.puuid->Data4[4],
                                pv.puuid->Data4[5],
                                pv.puuid->Data4[6],
                                pv.puuid->Data4[7]
                                );
                    }

                    PropVariantClear(&pv);

                    pPropertyStore->Release();
                }
            }

            if (pFI)
            {
                pFI->Release();
                pFI = NULL;
            }

            if (pDeviceFunctionCollection)
            {
                pDeviceFunctionCollection->Release();
                pDeviceFunctionCollection = NULL;
            }
        }
    }

    return hr;
}