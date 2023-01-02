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
/* (>) Standard: ISO C11 (ISO/IEC 9899:2011) */
/* (#) Portability: DragonFly BSD (/include/stdnoreturn.h) */
/* (#) Portability: FreeBSD       (/include/stdnoreturn.h) */
/* (#) Portability: NetBSD        (/include/stdnoreturn.h) */
/* (#) Portability: PDCLib        (/include/stdnoreturn.h) */
/* (#) Portability: musl libc     (/include/stdnoreturn.h) */
#ifndef _STDNORETURN_H
#define _STDNORETURN_H 1

#include "__stdinc.h"

#ifndef __GCC_VERSION_NUM
#ifdef __GNUC__
#ifndef __GNUC_MINOR__
#define __GNUC_MINOR__ 0
#endif /* !__GNUC_MINOR__ */
#ifndef __GNUC_PATCH__
#ifdef __GNUC_PATCHLEVEL__
#define __GNUC_PATCH__ __GNUC_PATCHLEVEL__
#else /* __GNUC_PATCHLEVEL__ */
#define __GNUC_PATCH__ 0
#endif /* !__GNUC_PATCHLEVEL__ */
#endif /* !__GNUC_PATCH__ */
#ifndef __GCC_VERSION_NUM
#define __GCC_VERSION_NUM (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCH__)
#endif /* !__GCC_VERSION_NUM */
#else /* __GNUC__ */
#define __GCC_VERSION_NUM 0
#endif /* !__GNUC__ */
#endif /* !__GCC_VERSION_NUM */

#if (!defined(noreturn) && !defined(__ATTR_NORETURN_IS_LB_LB_NORETURN_RB_RB) &&                 \
     !defined(__ATTR_NORETURN_IS_NORETURN) && !defined(__ATTR_NORETURN_IS_DECLSPEC_NORETURN) && \
     !defined(__cplusplus) && (__GCC_VERSION_NUM < 40700))
#define noreturn __ATTR_NORETURN
#endif /* ... */

#if (!defined(_Noreturn) && !defined(__ATTR_NORETURN_IS__NORETURN) && \
     (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112))
#define _Noreturn __ATTR_NORETURN
#endif /* ... */

#endif /* !_STDNORETURN_H */
