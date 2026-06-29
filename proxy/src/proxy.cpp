#include "../include/proxy.h"

static HMODULE g_proxyModule = nullptr;

static PFN_GetFileVersionInfoA     o_GetFileVersionInfoA;
static PFN_GetFileVersionInfoW     o_GetFileVersionInfoW;
static PFN_GetFileVersionInfoSizeA o_GetFileVersionInfoSizeA;
static PFN_GetFileVersionInfoSizeW o_GetFileVersionInfoSizeW;
static PFN_VerQueryValueA          o_VerQueryValueA;
static PFN_VerQueryValueW          o_VerQueryValueW;

extern "C" BOOL  WINAPI GetFileVersionInfoA    (LPCSTR  a, DWORD b, DWORD c, LPVOID d)    { return o_GetFileVersionInfoA(a,b,c,d); }
extern "C" BOOL  WINAPI GetFileVersionInfoW    (LPCWSTR a, DWORD b, DWORD c, LPVOID d)    { return o_GetFileVersionInfoW(a,b,c,d); }
extern "C" DWORD WINAPI GetFileVersionInfoSizeA(LPCSTR  a, LPDWORD b)                     { return o_GetFileVersionInfoSizeA(a,b); }
extern "C" DWORD WINAPI GetFileVersionInfoSizeW(LPCWSTR a, LPDWORD b)                     { return o_GetFileVersionInfoSizeW(a,b); }
extern "C" BOOL  WINAPI VerQueryValueA         (LPCVOID a, LPCSTR  b, LPVOID* c, PUINT d) { return o_VerQueryValueA(a,b,c,d); }
extern "C" BOOL  WINAPI VerQueryValueW         (LPCVOID a, LPCWSTR b, LPVOID* c, PUINT d) { return o_VerQueryValueW(a,b,c,d); }

void LoadOriginal()
{
    wchar_t path[MAX_PATH];
    GetSystemDirectoryW(path, MAX_PATH);
    wcscat_s(path, MAX_PATH, L"\\version.dll");

    g_proxyModule = LoadLibraryW(path);
    if (!g_proxyModule)
    {
        MessageBoxW(nullptr, L"Failed to load real version.dll!", L"Proxy Error", MB_ICONERROR);
        ExitProcess(1);
    }

#define GETPROC(name) o_##name = (PFN_##name)GetProcAddress(g_proxyModule, #name)
    GETPROC(GetFileVersionInfoA);
    GETPROC(GetFileVersionInfoW);
    GETPROC(GetFileVersionInfoSizeA);
    GETPROC(GetFileVersionInfoSizeW);
    GETPROC(VerQueryValueA);
    GETPROC(VerQueryValueW);
#undef GETPROC
}

void FreeOriginal()
{
    if (!g_proxyModule) return;
    FreeLibrary(g_proxyModule);
    g_proxyModule = nullptr;
}