#pragma once
#include <windows.h>
#include "../../../api/include/hook.h"

typedef BOOL (WINAPI* PFN_AllocConsole)();

class AllocConsoleHook : public SM::Hook {
public:
	AllocConsoleHook();
	~AllocConsoleHook() = default;

	static BOOL WINAPI Detour();
	static PFN_AllocConsole Original;
};