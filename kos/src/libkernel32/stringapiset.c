/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBKERNEL32_STRINGAPISET_C
#define GUARD_LIBKERNEL32_STRINGAPISET_C 1
#define _UTF_SOURCE 1

#include "api.h"

#include <kos/except.h>
#include <kos/types.h>
#include <nt/stringapiset.h>

#include <string.h>
#include <syslog.h>
#include <uchar.h>
#include <wchar.h>


DECL_BEGIN

/************************************************************************/
/* <STRING.H>-STYLE FUNCTIONS                                           */
/************************************************************************/
INTERN ATTR_PURE int
NOTHROW_NCX(WINAPI libk32_lstrcmpA)(LPCSTR lpString1, LPCSTR lpString2) {
	return strcmp(lpString1, lpString2);
}

INTERN ATTR_PURE int
NOTHROW_NCX(WINAPI libk32_lstrcmpW)(LPCWSTR lpString1, LPCWSTR lpString2) {
	return c16cmp(lpString1, lpString2);
}

INTERN ATTR_PURE int
NOTHROW_NCX(WINAPI libk32_lstrcmpiA)(LPCSTR lpString1, LPCSTR lpString2) {
	return strcasecmp(lpString1, lpString2);
}

INTERN ATTR_PURE int
NOTHROW_NCX(WINAPI libk32_lstrcmpiW)(LPCWSTR lpString1, LPCWSTR lpString2) {
	return c16casecmp(lpString1, lpString2);
}

INTERN LPSTR WINAPI
libk32_lstrcpynA(LPSTR lpString1, LPCSTR lpString2, int iMaxLength) {
	TRY {
		return strncpy(lpString1, lpString2, (size_t)(unsigned int)iMaxLength);
	} EXCEPT {
	}
	return NULL;
}

INTERN LPWSTR WINAPI
libk32_lstrcpynW(LPWSTR lpString1, LPCWSTR lpString2, int iMaxLength) {
	TRY {
		return c16ncpy(lpString1, lpString2, (size_t)(unsigned int)iMaxLength);
	} EXCEPT {
	}
	return NULL;
}

INTERN LPSTR WINAPI
libk32_lstrcpyA(LPSTR lpString1, LPCSTR lpString2) {
	TRY {
		return strcpy(lpString1, lpString2);
	} EXCEPT {
	}
	return NULL;
}

INTERN LPWSTR WINAPI
libk32_lstrcpyW(LPWSTR lpString1, LPCWSTR lpString2) {
	TRY {
		return c16cpy(lpString1, lpString2);
	} EXCEPT {
	}
	return NULL;
}

INTERN LPSTR
NOTHROW_NCX(WINAPI libk32_lstrcatA)(LPSTR lpString1, LPCSTR lpString2) {
	return strcat(lpString1, lpString2);
}

INTERN LPWSTR
NOTHROW_NCX(WINAPI libk32_lstrcatW)(LPWSTR lpString1, LPCWSTR lpString2) {
	return c16cat(lpString1, lpString2);
}

INTERN ATTR_PURE int
NOTHROW_NCX(WINAPI libk32_lstrlenA)(LPCSTR lpString) {
	return !lpString ? 0 : (int)(unsigned int)strlen(lpString);
}

INTERN ATTR_PURE int
NOTHROW_NCX(WINAPI libk32_lstrlenW)(LPCWSTR lpString) {
	return !lpString ? 0 : (int)(unsigned int)c16len(lpString);
}

DEFINE_PUBLIC_ALIAS(lstrcmpA, libk32_lstrcmpA);
DEFINE_PUBLIC_ALIAS(lstrcmpW, libk32_lstrcmpW);
DEFINE_PUBLIC_ALIAS(lstrcmpiA, libk32_lstrcmpiA);
DEFINE_PUBLIC_ALIAS(lstrcmpiW, libk32_lstrcmpiW);
DEFINE_PUBLIC_ALIAS(lstrcpynA, libk32_lstrcpynA);
DEFINE_PUBLIC_ALIAS(lstrcpynW, libk32_lstrcpynW);
DEFINE_PUBLIC_ALIAS(lstrcpyA, libk32_lstrcpyA);
DEFINE_PUBLIC_ALIAS(lstrcpyW, libk32_lstrcpyW);
DEFINE_PUBLIC_ALIAS(lstrcatA, libk32_lstrcatA);
DEFINE_PUBLIC_ALIAS(lstrcatW, libk32_lstrcatW);
DEFINE_PUBLIC_ALIAS(lstrlenA, libk32_lstrlenA);
DEFINE_PUBLIC_ALIAS(lstrlenW, libk32_lstrlenW);
/************************************************************************/




/************************************************************************/
/* CODEC CONVERSION                                                     */
/************************************************************************/
INTERN int WINAPI
libk32_MultiByteToWideChar(UINT uCodePage, DWORD dwFlags,
                           LPCCH lpMultiByteStr, int cbMultiByte,
                           LPWSTR lpWideCharStr, int cchWideChar) {
	TRACE("MultiByteToWideChar(%u, %#x, %q, %d, %p, %d)",
	      uCodePage, dwFlags, lpMultiByteStr,
	      cbMultiByte, lpWideCharStr, cchWideChar);
	syslog(LOG_WARNING, "NotImplemented: MultiByteToWideChar(%u, %#x, %q, %d, %p, %d)\n",
	       uCodePage, dwFlags, lpMultiByteStr, cbMultiByte, lpWideCharStr, cchWideChar);
	/* TODO */
	return 0;
}

INTERN int WINAPI
libk32_WideCharToMultiByte(UINT uCodePage, DWORD dwFlags,
                           LPCWCH lpWideCharStr, int cchWideChar,
                           LPSTR lpMultiByteStr, int cbMultiByte,
                           LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar) {
	TRACE("WideCharToMultiByte(%u, %#x, %I16q, %d, %p, %d, %p, %p)",
	      uCodePage, dwFlags, lpWideCharStr, cchWideChar,
	      lpMultiByteStr, cbMultiByte, lpDefaultChar, lpUsedDefaultChar);
	syslog(LOG_WARNING, "NotImplemented: WideCharToMultiByte(%u, %#x, %I16q, %d, %p, %d, %p, %p)\n",
	       uCodePage, dwFlags, lpWideCharStr, cchWideChar,
	       lpMultiByteStr, cbMultiByte, lpDefaultChar, lpUsedDefaultChar);
	/* TODO */
	return 0;
}

DEFINE_PUBLIC_ALIAS(MultiByteToWideChar, libk32_MultiByteToWideChar);
DEFINE_PUBLIC_ALIAS(WideCharToMultiByte, libk32_WideCharToMultiByte);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_STRINGAPISET_C */
