/* Copyright (c) 2019-2022 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _NT_LIBLOADERAPI_H
#define _NT_LIBLOADERAPI_H 1

#include "__stdinc.h"
/**/

#include "types.h"
/**/

#include <hybrid/typecore.h>

/* NT Library API */

#ifdef __CC__
__DECL_BEGIN

/* Reason codes for DllMain() */
#define DLL_PROCESS_DETACH   0
#define DLL_PROCESS_ATTACH   1
#define DLL_THREAD_ATTACH    2
#define DLL_THREAD_DETACH    3
#define DLL_PROCESS_VERIFIER 4

#ifndef _HMODULE_DEFINED
#define _HMODULE_DEFINED
DECLARE_HANDLE(HMODULE);
#endif /* !_HMODULE_DEFINED */

#ifndef _HRSRC_DEFINED
#define _HRSRC_DEFINED
DECLARE_HANDLE(HRSRC);
#endif /* !_HRSRC_DEFINED */

typedef struct tagENUMUILANG {
	ULONG NumOfEnumUILang;
	ULONG SizeOfEnumUIBuffer;
	LANGID *pEnumUIBuffer;
} ENUMUILANG, *PENUMUILANG;

#ifdef STRICT
typedef WINBOOL (CALLBACK *ENUMRESLANGPROCA)(HMODULE hModule, LPCSTR lpType, LPCSTR lpName, WORD wLanguage, LONG_PTR lParam);
typedef WINBOOL (CALLBACK *ENUMRESLANGPROCW)(HMODULE hModule, LPCWSTR lpType, LPCWSTR lpName, WORD wLanguage, LONG_PTR lParam);
typedef WINBOOL (CALLBACK *ENUMRESNAMEPROCA)(HMODULE hModule, LPCSTR lpType, LPSTR lpName, LONG_PTR lParam);
typedef WINBOOL (CALLBACK *ENUMRESNAMEPROCW)(HMODULE hModule, LPCWSTR lpType, LPWSTR lpName, LONG_PTR lParam);
typedef WINBOOL (CALLBACK *ENUMRESTYPEPROCA)(HMODULE hModule, LPSTR lpType, LONG_PTR lParam);
typedef WINBOOL (CALLBACK *ENUMRESTYPEPROCW)(HMODULE hModule, LPWSTR lpType, LONG_PTR lParam);
#else /* STRICT */
typedef FARPROC ENUMRESTYPEPROCA;
typedef FARPROC ENUMRESTYPEPROCW;
typedef FARPROC ENUMRESNAMEPROCA;
typedef FARPROC ENUMRESNAMEPROCW;
typedef FARPROC ENUMRESLANGPROCA;
typedef FARPROC ENUMRESLANGPROCW;
#endif /* !STRICT */
#define ENUMRESLANGPROC __MINGW_NAME_AW(ENUMRESLANGPROC)
#define ENUMRESNAMEPROC __MINGW_NAME_AW(ENUMRESNAMEPROC)
#define ENUMRESTYPEPROC __MINGW_NAME_AW(ENUMRESTYPEPROC)

typedef WINBOOL (WINAPI *PGET_MODULE_HANDLE_EXA)(DWORD dwFlags, LPCSTR lpModuleName, HMODULE *phModule);
typedef WINBOOL (WINAPI *PGET_MODULE_HANDLE_EXW)(DWORD dwFlags, LPCWSTR lpModuleName, HMODULE *phModule);
typedef PVOID DLL_DIRECTORY_COOKIE, *PDLL_DIRECTORY_COOKIE;

#define FIND_RESOURCE_DIRECTORY_TYPES     0x0100
#define FIND_RESOURCE_DIRECTORY_NAMES     0x0200
#define FIND_RESOURCE_DIRECTORY_LANGUAGES 0x0400

#define RESOURCE_ENUM_LN           0x0001
#define RESOURCE_ENUM_MUI          0x0002
#define RESOURCE_ENUM_MUI_SYSTEM   0x0004
#define RESOURCE_ENUM_VALIDATE     0x0008
#define RESOURCE_ENUM_MODULE_EXACT 0x0010

#define SUPPORT_LANG_NUMBER 32

#define DONT_RESOLVE_DLL_REFERENCES               0x00000001
#define LOAD_LIBRARY_AS_DATAFILE                  0x00000002
#define LOAD_WITH_ALTERED_SEARCH_PATH             0x00000008
#define LOAD_IGNORE_CODE_AUTHZ_LEVEL              0x00000010
#define LOAD_LIBRARY_AS_IMAGE_RESOURCE            0x00000020
#define LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE        0x00000040
#define LOAD_LIBRARY_REQUIRE_SIGNED_TARGET        0x00000080
#define LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR          0x00000100
#define LOAD_LIBRARY_SEARCH_APPLICATION_DIR       0x00000200
#define LOAD_LIBRARY_SEARCH_USER_DIRS             0x00000400
#define LOAD_LIBRARY_SEARCH_SYSTEM32              0x00000800
#define LOAD_LIBRARY_SEARCH_DEFAULT_DIRS          0x00001000
#define LOAD_LIBRARY_SAFE_CURRENT_DIRS            0x00002000
#define LOAD_LIBRARY_SEARCH_SYSTEM32_NO_FORWARDER 0x00004000
#define LOAD_LIBRARY_OS_INTEGRITY_CONTINUITY      0x00008000
WINBASEAPI HMODULE WINAPI LoadLibraryExA(LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);
WINBASEAPI HMODULE WINAPI LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);

#define GET_MODULE_HANDLE_EX_FLAG_PIN                0x1
#define GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCNT 0x2
#define GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS       0x4
WINBASEAPI WINBOOL WINAPI GetModuleHandleExA(DWORD dwFlags, LPCSTR lpModuleName, HMODULE *phModule);
WINBASEAPI WINBOOL WINAPI GetModuleHandleExW(DWORD dwFlags, LPCWSTR lpModuleName, HMODULE *phModule);

WINBASEAPI HMODULE WINAPI GetModuleHandleA(LPCSTR lpModuleName);
WINBASEAPI HMODULE WINAPI GetModuleHandleW(LPCWSTR lpModuleName);
WINBASEAPI HMODULE WINAPI LoadLibraryA(LPCSTR lpLibFileName);
WINBASEAPI HMODULE WINAPI LoadLibraryW(LPCWSTR lpLibFileName);
WINBASEAPI FARPROC WINAPI GetProcAddress(HMODULE hModule, LPCSTR lpProcName);
WINBASEAPI WINBOOL WINAPI FreeLibrary(HMODULE hLibModule);
WINBASEAPI DECLSPEC_NORETURN VOID WINAPI FreeLibraryAndExitThread(HMODULE hLibModule, DWORD dwExitCode);

#ifndef ERROR_INSUFFICIENT_BUFFER
#define ERROR_INSUFFICIENT_BUFFER 122
#endif /* !ERROR_INSUFFICIENT_BUFFER */
WINBASEAPI DWORD WINAPI GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize);
WINBASEAPI DWORD WINAPI GetModuleFileNameW(HMODULE hModule, LPWSTR lpFilename, DWORD nSize);

#define GetModuleFileName       __MINGW_NAME_AW(GetModuleFileName)
#define GetModuleHandle         __MINGW_NAME_AW(GetModuleHandle)
#define LoadLibrary             __MINGW_NAME_AW(LoadLibrary)
#define PGET_MODULE_HANDLE_EX   __MINGW_NAME_AW(PGET_MODULE_HANDLE_EX)
#define GetModuleHandleEx       __MINGW_NAME_AW(GetModuleHandleEx)
#define LoadLibraryEx           __MINGW_NAME_AW(LoadLibraryEx)

__DECL_END
#endif /* __CC__ */

#endif /* !_NT_LIBLOADERAPI_H */
