/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _NT_STRINGAPISET_H
#define _NT_STRINGAPISET_H 1

#include "__stdinc.h"
/**/

#include "types.h"

#ifdef __CC__
__DECL_BEGIN

/************************************************************************/
/* <STRING.H>-STYLE FUNCTIONS                                           */
/************************************************************************/
WINBASEAPI int WINAPI lstrcmpA(LPCSTR lpString1, LPCSTR lpString2);
WINBASEAPI int WINAPI lstrcmpW(LPCWSTR lpString1, LPCWSTR lpString2);
WINBASEAPI int WINAPI lstrcmpiA(LPCSTR lpString1, LPCSTR lpString2);
WINBASEAPI int WINAPI lstrcmpiW(LPCWSTR lpString1, LPCWSTR lpString2);
WINBASEAPI LPSTR WINAPI lstrcpynA(LPSTR lpString1, LPCSTR lpString2, int iMaxLength);
WINBASEAPI LPWSTR WINAPI lstrcpynW(LPWSTR lpString1, LPCWSTR lpString2, int iMaxLength);
WINBASEAPI LPSTR WINAPI lstrcpyA(LPSTR lpString1, LPCSTR lpString2);
WINBASEAPI LPWSTR WINAPI lstrcpyW(LPWSTR lpString1, LPCWSTR lpString2);
WINBASEAPI LPSTR WINAPI lstrcatA(LPSTR lpString1, LPCSTR lpString2);
WINBASEAPI LPWSTR WINAPI lstrcatW(LPWSTR lpString1, LPCWSTR lpString2);
WINBASEAPI int WINAPI lstrlenA(LPCSTR lpString);
WINBASEAPI int WINAPI lstrlenW(LPCWSTR lpString);



/************************************************************************/
/* CODEC CONVERSION                                                     */
/************************************************************************/
WINBASEAPI int WINAPI MultiByteToWideChar(UINT uCodePage, DWORD dwFlags, LPCCH lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);
WINBASEAPI int WINAPI WideCharToMultiByte(UINT uCodePage, DWORD dwFlags, LPCWCH lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar);

__DECL_END
#endif /* __CC__ */

#endif /* !_NT_STRINGAPISET_H */
