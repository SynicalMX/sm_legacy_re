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
	if (!result) return result;

	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	freopen_s(&f, "CONOUT$", "w", stderr);
	freopen_s(&f, "CONIN$",  "r", stdin);
	std::ios::sync_with_stdio(true);
	std::cout.setf(std::ios::unitbuf);

	return result;
}

PFN_AllocConsole AllocConsoleHook::Original = nullptr;
