#pragma once

#include <Wbemidl.h>
#include <comdef.h>
#include <iostream>
#pragma comment(lib, "wbemuuid.lib")

int query()
{
    HRESULT hres;
    // Initialize COM
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres))
    {
        std::cout << "Failed to initialize COM library. Error code: " << hres << std::endl;
        return 1;
    }
    // Initialize WMI
    hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL,
                                EOAC_NONE, NULL);
    if (FAILED(hres))
    {
        std::cout << "Failed to initialize WMI security. Error code: " << hres << std::endl;
        CoUninitialize();
        return 1;
    }
    IWbemLocator *pLoc = NULL;
    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *)&pLoc);
    if (FAILED(hres))
    {
        std::cout << "Failed to create IWbemLocator object. Error code: " << hres << std::endl;
        CoUninitialize();
        return 1;
    }
    IWbemServices *pSvc = NULL;
    hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
    if (FAILED(hres))
    {
        std::cout << "Failed to connect to IWbemServices object. Error code: " << hres << std::endl;
        pLoc->Release();
        CoUninitialize();
        return 1;
    }
    hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL,
                             RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
    if (FAILED(hres))
    {
        std::cout << "Failed to set WMI proxy blanket. Error code: " << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }
    // Execute WMI query to get graphics card information
    IEnumWbemClassObject *pEnumerator = NULL;
    hres = pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_VideoController"),
                           WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
    if (FAILED(hres))
    {
        std::cout << "Failed to execute WMI query. Error code: " << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;
    }
    // Retrieve graphics card information and print driver version
    IWbemClassObject *pclsObj = NULL;
    ULONG uReturn = 0;
    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (0 == uReturn)
        {
            break;
        }
        VARIANT vtProp;
        hr = pclsObj->Get(L"DriverVersion", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hr))
        {
            std::wcout << "Driver version: " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }
        pclsObj->Release();
    }
    // Cleanup
    pEnumerator->Release();
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();
    return 0;
}