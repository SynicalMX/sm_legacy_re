#include "../include/bootstrapper.h"
#include <windows.h>

static HMODULE g_loaderModule;

void BootstrapModLoader() {
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(nullptr, path, MAX_PATH);

    wchar_t* lastSlash = wcsrchr(path, L'\\');
    if (lastSlash) *(lastSlash + 1) = L'\0';

    wcscat_s(path, MAX_PATH, L"sm_legacy\\sm_legacy_loader.dll");

    g_loaderModule = LoadLibraryExW(path, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
}

void FreeModLoader() {
    if (g_loaderModule == nullptr) return;

    FreeLibrary(g_loaderModule);
    g_loaderModule = nullptr;
}
