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
#ifndef _NT_PROCESSENV_H
#define _NT_PROCESSENV_H 1

#include "__stdinc.h"
/**/

#include "types.h"
/**/

#ifdef __CC__
__DECL_BEGIN

/************************************************************************/
/* GetCurrentDirectory() / SetCurrentDirectory()                        */
/************************************************************************/
WINBASEAPI WINBOOL WINAPI SetCurrentDirectoryA(LPCSTR lpPathName);
WINBASEAPI WINBOOL WINAPI SetCurrentDirectoryW(LPCWSTR lpPathName);
WINBASEAPI DWORD WINAPI GetCurrentDirectoryA(DWORD nBufferLength, LPSTR lpBuffer);
WINBASEAPI DWORD WINAPI GetCurrentDirectoryW(DWORD nBufferLength, LPWSTR lpBuffer);



/************************************************************************/
/* GetStdHandle() / SetStdHandle()                                      */
/************************************************************************/
#define STD_INPUT_HANDLE  ((DWORD)-10)
#define STD_OUTPUT_HANDLE ((DWORD)-11)
#define STD_ERROR_HANDLE  ((DWORD)-12)
WINBASEAPI HANDLE WINAPI GetStdHandle(DWORD nStdHandle);
WINBASEAPI WINBOOL WINAPI SetStdHandle(DWORD nStdHandle, HANDLE hHandle);
WINBASEAPI WINBOOL WINAPI SetStdHandleEx(DWORD nStdHandle, HANDLE hHandle, PHANDLE phPrevValue);



/************************************************************************/
/* GetCommandLine()                                                     */
/************************************************************************/
WINBASEAPI LPSTR WINAPI GetCommandLineA(VOID);
WINBASEAPI LPWSTR WINAPI GetCommandLineW(VOID);



/************************************************************************/
/* ENVIRON                                                              */
/************************************************************************/
#define ERROR_ENVVAR_NOT_FOUND 203
WINBASEAPI LPCH WINAPI GetEnvironmentStrings(VOID);
WINBASEAPI LPWCH WINAPI GetEnvironmentStringsW(VOID);
WINBASEAPI WINBOOL WINAPI FreeEnvironmentStringsA(LPCH penv);
WINBASEAPI WINBOOL WINAPI FreeEnvironmentStringsW(LPWCH penv);
WINBASEAPI DWORD WINAPI ExpandEnvironmentStringsA(LPCSTR lpSrc, LPSTR lpDst, DWORD nSize);
WINBASEAPI DWORD WINAPI ExpandEnvironmentStringsW(LPCWSTR lpSrc, LPWSTR lpDst, DWORD nSize);
WINBASEAPI DWORD WINAPI GetEnvironmentVariableA(LPCSTR lpName, LPSTR lpBuffer, DWORD nSize);
WINBASEAPI DWORD WINAPI GetEnvironmentVariableW(LPCWSTR lpName, LPWSTR lpBuffer, DWORD nSize);
WINBASEAPI WINBOOL WINAPI SetEnvironmentVariableA(LPCSTR lpName, LPCSTR lpValue);
WINBASEAPI WINBOOL WINAPI SetEnvironmentVariableW(LPCWSTR lpName, LPCWSTR lpValue);


__DECL_END
#endif /* __CC__ */

#endif /* !_NT_PROCESSENV_H */
