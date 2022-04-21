/* HASH CRC-32:0xeba5138c */
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
#ifndef _BITS_CRT_SYS_ERRLIST_H
#define _BITS_CRT_SYS_ERRLIST_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#ifdef __CC__
__SYSDECL_BEGIN

#if defined(__USE_GNU) || defined(__USE_DOS)
#ifndef _sys_errlist
#ifdef sys_errlist
#define _sys_errlist sys_errlist
#else /* sys_errlist */
#if !defined(____sys_errlist_defined) && defined(__CRT_HAVE___sys_errlist)
#define ____sys_errlist_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char const *const *,__NOTHROW,__sys_errlist,(void),())
#endif /* !____sys_errlist_defined && __CRT_HAVE___sys_errlist */
#ifdef ____sys_errlist_defined
#define _sys_errlist (__sys_errlist())
#endif /* ____sys_errlist_defined */
#ifndef _sys_errlist
#if defined(__CRT_HAVE__sys_errlist)
__CSDECLARE2(,char const *const _sys_errlist[],_sys_errlist)
#define _sys_errlist     _sys_errlist
#elif defined(__CRT_HAVE_sys_errlist)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(,char const *const _sys_errlist[],_sys_errlist,sys_errlist)
#define _sys_errlist     _sys_errlist
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE2(,char const *const sys_errlist[],sys_errlist)
#define sys_errlist      sys_errlist
#define _sys_errlist     sys_errlist
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !_sys_errlist */
#endif /* !sys_errlist */
#endif /* !_sys_errlist */

#ifndef _sys_nerr
#ifdef sys_nerr
#define _sys_nerr sys_nerr
#else /* sys_nerr */
#if !defined(____sys_nerr_defined) && defined(__CRT_HAVE___sys_nerr)
#define ____sys_nerr_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW,__sys_nerr,(void),())
#endif /* !____sys_nerr_defined && __CRT_HAVE___sys_nerr */
#ifdef ____sys_nerr_defined
#define _sys_nerr (*__sys_nerr())
#endif /* ____sys_nerr_defined */
#ifndef _sys_nerr
#if defined(__CRT_HAVE__sys_nerr)
__CSDECLARE(,int,_sys_nerr)
#define _sys_nerr _sys_nerr
#elif defined(__CRT_HAVE_sys_nerr)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,int,_sys_nerr,sys_nerr)
#define _sys_nerr _sys_nerr
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,int,sys_nerr)
#define sys_nerr sys_nerr
#define _sys_nerr sys_nerr
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !_sys_nerr */
#endif /* !sys_nerr */
#endif /* !_sys_nerr */
#endif /* __USE_GNU || __USE_DOS */

#if defined(__USE_MISC) || defined(__USE_DOS)
#ifndef sys_errlist
#ifdef _sys_errlist
#define sys_errlist _sys_errlist
#else /* _sys_errlist */
#if !defined(____sys_errlist_defined) && defined(__CRT_HAVE___sys_errlist)
#define ____sys_errlist_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,char const *const *,__NOTHROW,__sys_errlist,(void),())
#endif /* !____sys_errlist_defined && __CRT_HAVE___sys_errlist */
#ifdef ____sys_errlist_defined
#define sys_errlist (__sys_errlist())
#endif /* ____sys_errlist_defined */
#ifndef sys_errlist
#if defined(__CRT_HAVE__sys_errlist)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(,char const *const sys_errlist[],sys_errlist,_sys_errlist)
#define sys_errlist      sys_errlist
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE2(,char const *const _sys_errlist[],_sys_errlist)
#define _sys_errlist     _sys_errlist
#define sys_errlist      _sys_errlist
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE_sys_errlist)
__CSDECLARE2(,char const *const sys_errlist[],sys_errlist)
#define sys_errlist      sys_errlist
#endif /* ... */
#endif /* !sys_errlist */
#endif /* !_sys_errlist */
#endif /* !sys_errlist */

#ifndef sys_nerr
#ifdef _sys_nerr
#define sys_nerr _sys_nerr
#else /* _sys_nerr */
#if !defined(____sys_nerr_defined) && defined(__CRT_HAVE___sys_nerr)
#define ____sys_nerr_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW,__sys_nerr,(void),())
#endif /* !____sys_nerr_defined && __CRT_HAVE___sys_nerr */
#ifdef ____sys_nerr_defined
#define sys_nerr (*__sys_nerr())
#endif /* ____sys_nerr_defined */
#ifndef sys_nerr
#if defined(__CRT_HAVE__sys_nerr)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT(,int,sys_nerr,_sys_nerr)
#define sys_nerr sys_nerr
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE(,int,_sys_nerr)
#define sys_nerr  _sys_nerr
#define _sys_nerr _sys_nerr
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE_sys_nerr)
__CSDECLARE(,int,sys_nerr)
#define sys_nerr sys_nerr
#endif /* ... */
#endif /* !sys_nerr */
#endif /* !_sys_nerr */
#endif /* !sys_nerr */
#endif /* __USE_MISC || __USE_DOS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_SYS_ERRLIST_H */
