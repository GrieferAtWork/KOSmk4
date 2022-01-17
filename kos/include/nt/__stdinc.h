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


#ifndef far
#define far /* Nothing */
#endif /* !far */
#ifndef near
#define near /* Nothing */
#endif /* !near */
#ifndef pascal
#define pascal __ATTR_STDCALL
#endif /* !pascal */
#ifndef cdecl
#define cdecl __ATTR_CDECL
#endif /* !cdecl */
#ifndef CDECL
#define CDECL __ATTR_CDECL
#endif /* !CDECL */
#ifndef CALLBACK
#define CALLBACK __ATTR_STDCALL
#endif /* !CALLBACK */
#ifndef WINAPI
#define WINAPI __ATTR_STDCALL
#endif /* !WINAPI */
#ifndef WINAPIV
#define WINAPIV __ATTR_CDECL
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
#define FASTCALL __ATTR_FASTCALL
#endif /* !FASTCALL */
#ifndef NTAPI
#define NTAPI __ATTR_STDCALL
#endif /* !NTAPI */

#endif /* !_NT___STDINC_H */
