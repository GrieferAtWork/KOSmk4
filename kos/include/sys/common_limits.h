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
/* (#) Portability: NetBSD (/sys/sys/common_limits.h) */
#ifndef _SYS_COMMON_LIMITS_H
#define _SYS_COMMON_LIMITS_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/limitcore.h>

#ifndef _LIMITS_H
#include <limits.h>
#endif /* !_LIMITS_H */

#ifdef __USE_NETBSD
#ifndef SSIZE_MIN
#define SSIZE_MIN __SSIZE_MIN__
#endif /* !SSIZE_MIN */
#ifndef SIZE_T_MAX
#define SIZE_T_MAX __SIZE_MAX__
#endif /* !SIZE_T_MAX */
#if !defined(UQUAD_MAX) && defined(__UINT64_MAX__)
#define UQUAD_MAX __UINT64_MAX__
#endif /* !UQUAD_MAX && __UINT64_MAX__ */
#if !defined(QUAD_MAX) && defined(__INT64_MAX__)
#define QUAD_MAX __INT64_MAX__
#endif /* !QUAD_MAX && __INT64_MAX__ */
#if !defined(QUAD_MIN) && defined(__INT64_MIN__)
#define QUAD_MIN __INT64_MIN__
#endif /* !QUAD_MIN && __INT64_MIN__ */
#endif /* __USE_NETBSD */

#if defined(__USE_XOPEN) || defined(__USE_NETBSD)
/* Only (really) need:
 * >> #define DBL_DIG  __DBL_DIG__
 * >> #define DBL_MAX  __DBL_MAX__
 * >> #define DBL_MIN  __DBL_MIN__
 * >> #define FLT_DIG  __FLT_DIG__
 * >> #define FLT_MAX  __FLT_MAX__
 * >> #define FLT_MIN  __FLT_MIN__
 * >> #define LDBL_DIG __LDBL_DIG__
 * >> #define LDBL_MAX __LDBL_MAX__
 * >> #define LDBL_MIN __LDBL_MIN__ */
#include <float.h>
#endif /* __USE_XOPEN || __USE_NETBSD */

#endif /* !_SYS_COMMON_LIMITS_H */
