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
#ifndef GUARD_LIBKERNEL32_LIBLOADERAPI_C
#define GUARD_LIBKERNEL32_LIBLOADERAPI_C 1
#define _KOS_ALTERATIONS_SOURCE 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define _UTF_SOURCE 1

#include "api.h"

#include <kos/except.h>
#include <kos/types.h>
#include <nt/handleapi.h>
#include <nt/libloaderapi.h>
#include <nt/types.h>

#include <dlfcn.h>
#include <malloc.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <uchar.h>
#include <wchar.h>

DECL_BEGIN

extern NONNULL((1)) REF void *ATTR_STDCALL /* From "libdl-pe.so" */
PeLoadLibrary(char const *__restrict filename, unsigned int flags);

DEFINE_PUBLIC_ALIAS(LoadLibraryExA, libk32_LoadLibraryExA);
DEFINE_PUBLIC_ALIAS(LoadLibraryExW, libk32_LoadLibraryExW);
DEFINE_PUBLIC_ALIAS(GetModuleHandleExA, libk32_GetModuleHandleExA);
DEFINE_PUBLIC_ALIAS(GetModuleHandleExW, libk32_GetModuleHandleExW);
DEFINE_PUBLIC_ALIAS(GetModuleHandleA, libk32_GetModuleHandleA);
DEFINE_PUBLIC_ALIAS(GetModuleHandleW, libk32_GetModuleHandleW);
DEFINE_PUBLIC_ALIAS(LoadLibraryA, libk32_LoadLibraryA);
DEFINE_PUBLIC_ALIAS(LoadLibraryW, libk32_LoadLibraryW);
/*DEFINE_PUBLIC_ALIAS(GetProcAddress, libk32_GetProcAddress);*/ /* Implicitly forwarded from "libdl-pe.so" */
DEFINE_PUBLIC_ALIAS(FreeLibrary, libk32_FreeLibrary);
DEFINE_PUBLIC_ALIAS(FreeLibraryAndExitThread, libk32_FreeLibraryAndExitThread);

INTERN HMODULE WINAPI
libk32_LoadLibraryExA(LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags) {
	(void)dwFlags;
	if (lpLibFileName == NULL)
		return (HMODULE)fdlopen(NTHANDLE_ASFD(hFile), RTLD_LAZY | RTLD_GLOBAL);
	return (HMODULE)PeLoadLibrary(lpLibFileName, RTLD_LAZY | RTLD_GLOBAL);
}

INTERN HMODULE WINAPI
libk32_LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags) {
	char *utf8;
	HMODULE result;
	(void)dwFlags;
	if (lpLibFileName == NULL)
		return (HMODULE)fdlopen(NTHANDLE_ASFD(hFile), RTLD_LAZY | RTLD_GLOBAL);
	utf8 = convert_c16tombs(lpLibFileName);
	if unlikely(!utf8)
		return NULL;
	result = libk32_LoadLibraryExA(utf8, hFile, dwFlags);
	free(utf8);
	return result;
}

INTERN WINBOOL WINAPI
libk32_GetModuleHandleExA(DWORD dwFlags, LPCSTR lpModuleName, HMODULE *phModule) {
	unsigned int dlflags = 0;
	if (!(dwFlags & GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT))
		dlflags |= DLGETHANDLE_FINCREF;
	if (dwFlags & GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS)
		return (*phModule = (HMODULE)dlgethandle(lpModuleName, dlflags)) != NULL;
	return (*phModule = (HMODULE)dlgetmodule(lpModuleName, dlflags | DLGETHANDLE_FNOCASE)) != NULL;
}

INTERN WINBOOL WINAPI
libk32_GetModuleHandleExW(DWORD dwFlags, LPCWSTR lpModuleName, HMODULE *phModule) {
	WINBOOL result;
	char *utf8;
	if (dwFlags & GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS)
		return GetModuleHandleExA(dwFlags, (LPCSTR)lpModuleName, phModule);
	utf8 = convert_c16tombs(lpModuleName);
	if unlikely(!utf8)
		return FALSE;
	result = libk32_GetModuleHandleExA(dwFlags, utf8, phModule);
	free(utf8);
	return result;
}

INTERN HMODULE WINAPI
libk32_GetModuleHandleA(LPCSTR lpModuleName) {
	return (HMODULE)dlgetmodule(lpModuleName, DLGETHANDLE_FNOCASE);
}

INTERN HMODULE WINAPI
libk32_GetModuleHandleW(LPCWSTR lpModuleName) {
	HMODULE result;
	char *utf8 = convert_c16tombs(lpModuleName);
	if unlikely(!utf8)
		return NULL;
	result = libk32_GetModuleHandleA(utf8);
	free(utf8);
	return result;
}

INTERN HMODULE WINAPI
libk32_LoadLibraryA(LPCSTR lpLibFileName) {
	return LoadLibraryExA(lpLibFileName, NULL, 0);
}

INTERN HMODULE WINAPI
libk32_LoadLibraryW(LPCWSTR lpLibFileName) {
	return LoadLibraryExW(lpLibFileName, NULL, 0);
}

INTERN WINBOOL WINAPI
libk32_FreeLibrary(HMODULE hLibModule) {
	return dlclose(hLibModule) == 0;
}

INTDEF DECLSPEC_NORETURN VOID WINAPI libk32_ExitThread(DWORD dwExitCode);
INTERN DECLSPEC_NORETURN VOID WINAPI
libk32_FreeLibraryAndExitThread(HMODULE hLibModule, DWORD dwExitCode) {
	dlclose(hLibModule);
	libk32_ExitThread(dwExitCode);
}

DEFINE_PUBLIC_ALIAS(GetModuleFileNameA, libk32_GetModuleFileNameA);
DEFINE_PUBLIC_ALIAS(GetModuleFileNameW, libk32_GetModuleFileNameW);
INTERN DWORD WINAPI
libk32_GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
	char const *modname;
	size_t len;
	modname = dlmodulename(hModule);
	if (!modname)
		return 0;
	len = strlen(modname) + 1;
	if (len > nSize) {
		_nterrno = ERROR_INSUFFICIENT_BUFFER;
		len      = nSize;
	}
	memcpy(lpFilename, modname, len, sizeof(CHAR));
	return len - 1;
}

INTERN DWORD WINAPI
libk32_GetModuleFileNameW(HMODULE hModule, LPWSTR lpFilename, DWORD nSize) {
	char const *modname;
	char16_t *wmodname;
	size_t len;
	modname = dlmodulename(hModule);
	if (!modname)
		return 0;
	wmodname = convert_mbstoc16(modname);
	if (!wmodname)
		return 0;
	len = c16len(wmodname) + 1;
	if (len > nSize) {
		_nterrno = ERROR_INSUFFICIENT_BUFFER;
		len      = nSize;
	}
	memcpy(lpFilename, wmodname, len, sizeof(WCHAR));
	free(wmodname);
	return len - 1;
}


DECL_END

#endif /* !GUARD_LIBKERNEL32_LIBLOADERAPI_C */
