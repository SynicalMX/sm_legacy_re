#include <cstdio>
#include <iostream>
#include <windows.h>

#include "../../api/include/modmanager.h"
#include "../include/loader.h"
#include "../include/hooks/allocconsole.h"

static bool g_threadRunning = false;
static HMODULE g_module;
static HANDLE g_thread;
static AllocConsoleHook* g_consoleHook = nullptr;

void ModLoaderFree() {
    SM::ModManager::Destroy();
    Loader::FreeAPI();
    FreeLibraryAndExitThread(g_module, 0);
}

void ModLoaderThread() {
    Loader::LoadAPI();
    Loader::LoadMods();
    SM::ModManager::Init();

    while (!g_threadRunning) {
        // panic button
        if (GetAsyncKeyState(VK_F9) & 0x8000) {
            g_threadRunning = false;
        }

        SM::ModManager::Update();
    }

    ModLoaderFree();
}

BOOL APIENTRY DllMain(const HMODULE hModule, const DWORD dwReason, const LPVOID lpReserved ) {
    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);

            g_consoleHook = new AllocConsoleHook();
            g_consoleHook->Enable();

            g_threadRunning = true;
            g_thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(ModLoaderThread), lpReserved, 0, nullptr);
            break;
        case DLL_PROCESS_DETACH:
            ModLoaderFree();
            break;
        default:
            break;
    }

    return TRUE;
}
