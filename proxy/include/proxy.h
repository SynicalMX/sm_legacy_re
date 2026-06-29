#pragma once
#include <windows.h>

typedef BOOL  (WINAPI* PFN_GetFileVersionInfoA)    (LPCSTR,  DWORD, DWORD, LPVOID);
typedef BOOL  (WINAPI* PFN_GetFileVersionInfoW)    (LPCWSTR, DWORD, DWORD, LPVOID);
typedef DWORD (WINAPI* PFN_GetFileVersionInfoSizeA)(LPCSTR,  LPDWORD);
typedef DWORD (WINAPI* PFN_GetFileVersionInfoSizeW)(LPCWSTR, LPDWORD);
typedef BOOL  (WINAPI* PFN_VerQueryValueA)         (LPCVOID, LPCSTR,  LPVOID*, PUINT);
typedef BOOL  (WINAPI* PFN_VerQueryValueW)         (LPCVOID, LPCWSTR, LPVOID*, PUINT);

void LoadOriginal();
void FreeOriginal();