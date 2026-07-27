#include "../../include/hooks/allocconsole.h"
#include <cstdio>
#include <iostream>

AllocConsoleHook::AllocConsoleHook()
	: Hook(
		reinterpret_cast<void*>(GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "AllocConsole")),
		reinterpret_cast<void*>(Detour),
		reinterpret_cast<void**>(&Original)
	)
{
}

BOOL WINAPI AllocConsoleHook::Detour()
{
	BOOL result = Original();
	freopen_s(reinterpret_cast<FILE **>(stdout), "CONOUT$", "w", stdout);

	printf("AllocConsole redirected\n");

	return result;
}

PFN_AllocConsole AllocConsoleHook::Original = nullptr;
