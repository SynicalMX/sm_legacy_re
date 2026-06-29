#pragma once

namespace Loader {
    void LoadAPI();
    void FreeAPI();

    void LoadMods();
    void LoadModsInDirectory(const wchar_t* dir);
}
