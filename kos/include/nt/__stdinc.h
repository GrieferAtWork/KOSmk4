/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _NT___STDINC_H
#define _NT___STDINC_H 1

#include "../__stdinc.h"

#if !defined(STRICT) && !defined(NO_STRICT)
#define STRICT 1
#endif /* !STRICT && !NO_STRICT */

#ifndef CONST
#define CONST const
#endif /* !CONST */
#ifndef UNALIGNED
#define UNALIGNED /* nothing */
#endif /* !UNALIGNED */
#ifndef RESTRICTED_POINTER
#define RESTRICTED_POINTER __restrict
#endif /* !RESTRICTED_POINTER */

#ifndef DUMMYUNIONNAME
#define DUMMYUNIONNAME /* Nothing */
#endif /* !DUMMYUNIONNAME */
#ifndef DUMMYUNIONNAME2
#define DUMMYUNIONNAME2 /* Nothing */
#endif /* !DUMMYUNIONNAME2 */
#ifndef DUMMYSTRUCTNAME
#define DUMMYSTRUCTNAME /* Nothing */
#endif /* !DUMMYSTRUCTNAME */
#ifndef DUMMYSTRUCTNAME2
#define DUMMYSTRUCTNAME2 /* Nothing */
#endif /* !DUMMYSTRUCTNAME2 */
#ifndef __C89_NAMELESS
#define __C89_NAMELESS /* Nothing */
#endif /* !__C89_NAMELESS */

#ifndef __NT_STDCALL
#ifdef __x86_64__
#define __NT_STDCALL __ATTR_MSABI
#else /* __x86_64__ */
#define __NT_STDCALL __ATTR_STDCALL
#endif /* !__x86_64__ */
#endif /* !__NT_STDCALL */

#ifndef __NT_CDECL
#ifdef __x86_64__
#define __NT_CDECL __ATTR_MSABI
#else /* __x86_64__ */
#define __NT_CDECL __ATTR_CDECL
#endif /* !__x86_64__ */
#endif /* !__NT_CDECL */

#ifndef __NT_FASTCALL
#ifdef __x86_64__
#define __NT_FASTCALL __ATTR_MSABI
#else /* __x86_64__ */
#define __NT_FASTCALL __ATTR_FASTCALL
#endif /* !__x86_64__ */
#endif /* !__NT_FASTCALL */


#ifndef far
#define far /* Nothing */
#endif /* !far */
#ifndef near
#define near /* Nothing */
#endif /* !near */
#ifndef pascal
#define pascal __NT_STDCALL
#endif /* !pascal */
#ifndef cdecl
#define cdecl __NT_CDECL
#endif /* !cdecl */
#ifndef CDECL
#define CDECL __NT_CDECL
#endif /* !CDECL */
#ifndef CALLBACK
#define CALLBACK __NT_STDCALL
#endif /* !CALLBACK */
#ifndef WINAPI
#define WINAPI __NT_STDCALL
#endif /* !WINAPI */
#ifndef WINAPIV
#define WINAPIV __NT_CDECL
#endif /* !WINAPIV */
#ifndef APIENTRY
#define APIENTRY WINAPI
#endif /* !APIENTRY */
#ifndef APIPRIVATE
#define APIPRIVATE WINAPI
#endif /* !APIPRIVATE */
#ifndef PASCAL
#define PASCAL WINAPI
#endif /* !PASCAL */
#ifndef WINAPI_INLINE
#define WINAPI_INLINE WINAPI
#endif /* !WINAPI_INLINE */
#ifndef FAR
#define FAR /* Nothing */
#endif /* !FAR */
#ifndef NEAR
#define NEAR /* Nothing */
#endif /* !NEAR */

#ifndef FASTCALL
#define FASTCALL __NT_FASTCALL
#endif /* !FASTCALL */
#ifndef NTAPI
#define NTAPI __NT_STDCALL
#endif /* !NTAPI */
#ifndef DECLSPEC_NORETURN
#define DECLSPEC_NORETURN __ATTR_NORETURN
#endif /* !DECLSPEC_NORETURN */
#ifndef DECLSPEC_ALIGN
#define DECLSPEC_ALIGN __ATTR_ALIGNED
#endif /* !DECLSPEC_ALIGN */

#ifndef WINBASEAPI
#define WINBASEAPI
#endif /* !WINBASEAPI */

#ifndef __MSABI_LONG
#if __SIZEOF_LONG__ == 4
#define __MSABI_LONG(x) x##L
#elif __SIZEOF_LONG_LONG__ == 4
#define __MSABI_LONG(x) x##LL
#else /* ... */
#define __MSABI_LONG(x) x
#endif /* !... */
#endif /* !__MSABI_LONG */

#ifndef TRUE
#define TRUE 1
#endif /* !TRUE */
#ifndef FALSE
#define FALSE 0
#endif /* !FALSE */

#ifndef __MINGW_NAME_AW
#ifdef UNICODE
#define __MINGW_NAME_AW(x) x##W
#else /* UNICODE */
#define __MINGW_NAME_AW(x) x##A
#endif /* !UNICODE */
#endif /* !__MINGW_NAME_AW */

#ifndef __MINGW_TYPEDEF_AW
#ifdef UNICODE
#define __MINGW_TYPEDEF_AW(x) typedef x##W x;
#else /* UNICODE */
#define __MINGW_TYPEDEF_AW(x) typedef x##A x;
#endif /* !UNICODE */
#endif /* !__MINGW_TYPEDEF_AW */


#endif /* !_NT___STDINC_H */
