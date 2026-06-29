#include <windows.h>
#include "../include/proxy.h"
#include "../include/bootstrapper.h"

static DWORD WINAPI ProxyThread(LPVOID)
{
    const wchar_t* cmd = GetCommandLineW();

    if (!wcsstr(cmd, L"-noEngineMods"))
        BootstrapModLoader();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            LoadOriginal();
            CreateThread(nullptr, 0, ProxyThread, nullptr, 0, nullptr);
            break;
        case DLL_PROCESS_DETACH:
            FreeOriginal();
            FreeModLoader();
            break;
    }
    return TRUE;
}
