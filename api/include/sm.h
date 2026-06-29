#pragma once
#include <windows.h>

#ifdef SM_API_EXPORTS
#define SM_API __declspec(dllexport)
#else
#define SM_API __declspec(dllimport)
#endif

namespace SM {
    bool SM_API IsDevMode();
}
