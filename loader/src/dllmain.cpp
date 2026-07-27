#include <cstdio>
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

#include "../../api/include/modmanager.h"
#include "../include/loader.h"
#include "../include/hooks/allocconsole.h"
#include "../include/hooks/contraptionstart.h"

static bool g_threadRunning = true;
static HMODULE g_module = nullptr;
static HANDLE g_thread = nullptr;
static AllocConsoleHook* g_consoleHook = nullptr;
static ContraptionStartHook* g_contraptionStartHook = nullptr;

static void SuspendGame()
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return;

    THREADENTRY32 te;
    te.dwSize = sizeof(te);
    DWORD currentTid = GetCurrentThreadId();
    DWORD pid = GetCurrentProcessId();

    if (Thread32First(hSnapshot, &te))
    {
        do
        {
            if (te.th32OwnerProcessID == pid && te.th32ThreadID != currentTid)
            {
                HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
                if (hThread)
                {
                    SuspendThread(hThread);
                    CloseHandle(hThread);
                }
            }
        } while (Thread32Next(hSnapshot, &te));
    }

    CloseHandle(hSnapshot);
}

static void ResumeGame()
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return;

    THREADENTRY32 te;
    te.dwSize = sizeof(te);
    DWORD currentTid = GetCurrentThreadId();
    DWORD pid = GetCurrentProcessId();

    if (Thread32First(hSnapshot, &te))
    {
        do
        {
            if (te.th32OwnerProcessID == pid && te.th32ThreadID != currentTid)
            {
                HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
                if (hThread)
                {
                    ResumeThread(hThread);
                    CloseHandle(hThread);
                }
            }
        } while (Thread32Next(hSnapshot, &te));
    }

    CloseHandle(hSnapshot);
}

void ModLoaderFree()
{
    g_threadRunning = false;
    if (g_consoleHook)       { g_consoleHook->Disable();        delete g_consoleHook;        g_consoleHook = nullptr; }
    if (g_contraptionStartHook) { g_contraptionStartHook->Disable(); delete g_contraptionStartHook; g_contraptionStartHook = nullptr; }
    SM::ModManager::Destroy();
    Loader::FreeAPI();
    FreeLibraryAndExitThread(g_module, 0);
}

static DWORD WINAPI ModLoaderThread(LPVOID)
{
    // SuspendGame();

    g_consoleHook = new AllocConsoleHook();
    g_consoleHook->Enable();

    // g_contraptionStartHook = new ContraptionStartHook();
    // g_contraptionStartHook->Enable();

    Loader::LoadAPI();
    Loader::LoadMods();
    SM::ModManager::Init();

    // ResumeGame();

    while (g_threadRunning)
    {
        if (GetAsyncKeyState(VK_F9) & 0x8000)
            g_threadRunning = false;

        SM::ModManager::Update();
        Sleep(16);
    }

    ModLoaderFree();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            g_module = hModule;
            g_thread = CreateThread(nullptr, 0, ModLoaderThread, nullptr, 0, nullptr);
            break;
        case DLL_PROCESS_DETACH:
            if (lpReserved == nullptr)
                ModLoaderFree();
            break;
    }
    return TRUE;
}