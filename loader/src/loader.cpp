#include "../include/loader.h"
#include "../../api/include/sm.h"
#include "../../api/include/imod.h"
#include "../../api/include/modmanager.h"
#include <windows.h>
#include <shlwapi.h>

namespace Loader {
    static HMODULE g_apiModule = nullptr;

    void LoadAPI() {
        wchar_t path[MAX_PATH];
        GetModuleFileNameW(nullptr, path, MAX_PATH);

        wchar_t* lastSlash = wcsrchr(path, L'\\');
        if (lastSlash) *(lastSlash + 1) = L'\0';

        wcscat_s(path, MAX_PATH, L"sm_legacy\\sm_legacy_api.dll");

        g_apiModule = LoadLibraryExW(path, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
    }

    void FreeAPI() {
        if (g_apiModule == nullptr) return;

        FreeLibrary(g_apiModule);
    }

    void LoadMods()
{
    wchar_t raw[MAX_PATH];
    GetModuleFileNameW(nullptr, raw, MAX_PATH);

    // Resolve any . or .. components
    wchar_t path[MAX_PATH];
    GetFullPathNameW(raw, MAX_PATH, path, nullptr);

    // Strip exe filename
    wchar_t* lastSlash = wcsrchr(path, L'\\');
    if (lastSlash) *lastSlash = L'\0';

    // Strip Release folder
    lastSlash = wcsrchr(path, L'\\');
    if (lastSlash) *(lastSlash + 1) = L'\0';

    wchar_t modsPath[MAX_PATH];
    wcscpy_s(modsPath, path);
    wcscat_s(modsPath, MAX_PATH, L"EngineMods");

    printf("LoadMods: scanning %ls\n", modsPath);

    DWORD attr = GetFileAttributesW(modsPath);
    if (attr == INVALID_FILE_ATTRIBUTES || !(attr & FILE_ATTRIBUTE_DIRECTORY))
    {
        printf("LoadMods: EngineMods folder not found\n");
        return;
    }

    LoadModsInDirectory(modsPath);
}

    void LoadMod(const wchar_t* path)
    {
        HMODULE hMod = LoadLibraryW(path);
        if (!hMod)
        {
            printf("LoadMod: failed to load %ls, error %lu\n", path, GetLastError());
            return;
        }

        using PFN_CreateMod = SM::IMod*(*)();
        auto CreateMod = reinterpret_cast<PFN_CreateMod>(GetProcAddress(hMod, "CreateMod"));
        if (!CreateMod)
        {
            printf("LoadMod: no CreateMod export in %ls\n", path);
            FreeLibrary(hMod);
            return;
        }

        SM::IMod* mod = CreateMod();
        if (!mod)
        {
            printf("LoadMod: CreateMod returned null for %ls\n", path);
            FreeLibrary(hMod);
            return;
        }

        printf("LoadMod: loaded %ls -> %s\n", path, mod->GetModMeta().name.c_str());
        SM::ModManager::Register(mod);
    }

    void LoadModsInDirectory(const wchar_t* dir) {
        wchar_t pattern[MAX_PATH];
        wcscpy_s(pattern, dir);
        wcscat_s(pattern, MAX_PATH, L"\\*");

        WIN32_FIND_DATAW fd;
        HANDLE hFind = FindFirstFileW(pattern, &fd);
        if (hFind == INVALID_HANDLE_VALUE) return;

        do
        {
            if (wcscmp(fd.cFileName, L".") == 0 || wcscmp(fd.cFileName, L"..") == 0)
                continue;

            wchar_t fullPath[MAX_PATH];
            wcscpy_s(fullPath, dir);
            wcscat_s(fullPath, MAX_PATH, L"\\");
            wcscat_s(fullPath, MAX_PATH, fd.cFileName);

            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                LoadModsInDirectory(fullPath);
            }
            else
            {
                wchar_t fullPath[MAX_PATH];
                PathCombineW(fullPath, dir, fd.cFileName);
                LoadMod(fullPath);
            }

        } while (FindNextFileW(hFind, &fd));

        FindClose(hFind);
    }
}
