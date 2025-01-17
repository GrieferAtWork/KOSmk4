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
/* (#) Portability: NetBSD (/sys/sys/common_int_limits.h) */
#ifndef _SYS_COMMON_INT_LIMITS_H
#define _SYS_COMMON_INT_LIMITS_H 1

#include <__stdinc.h>

#include <hybrid/limitcore.h>

#ifndef INT8_MAX
#define INT8_MAX         __INT8_MAX__
#endif /* !INT8_MAX */
#ifndef INT16_MAX
#define INT16_MAX        __INT16_MAX__
#endif /* !INT16_MAX */
#ifndef INT32_MAX
#define INT32_MAX        __INT32_MAX__
#endif /* !INT32_MAX */
#ifndef UINT8_MAX
#define UINT8_MAX        __UINT8_MAX__
#endif /* !UINT8_MAX */
#ifndef UINT16_MAX
#define UINT16_MAX       __UINT16_MAX__
#endif /* !UINT16_MAX */
#ifndef UINT32_MAX
#define UINT32_MAX       __UINT32_MAX__
#endif /* !UINT32_MAX */
#ifdef __UINT64_MAX__
#ifndef INT64_MAX
#define INT64_MAX        __INT64_MAX__
#endif /* !INT64_MAX */
#ifndef UINT64_MAX
#define UINT64_MAX       __UINT64_MAX__
#endif /* !UINT64_MAX */
#endif /* __UINT64_MAX__ */
#ifndef INTMAX_MAX
#define INTMAX_MAX       __INTMAX_MAX__
#endif /* !INTMAX_MAX */
#ifndef UINTMAX_MAX
#define UINTMAX_MAX      __UINTMAX_MAX__
#endif /* !UINTMAX_MAX */
#ifndef INT_LEAST8_MAX
#define INT_LEAST8_MAX   __INT_LEAST8_MAX__
#endif /* !INT_LEAST8_MAX */
#ifndef INT_LEAST16_MAX
#define INT_LEAST16_MAX  __INT_LEAST16_MAX__
#endif /* !INT_LEAST16_MAX */
#ifndef INT_LEAST32_MAX
#define INT_LEAST32_MAX  __INT_LEAST32_MAX__
#endif /* !INT_LEAST32_MAX */
#ifndef UINT_LEAST8_MAX
#define UINT_LEAST8_MAX  __UINT_LEAST8_MAX__
#endif /* !UINT_LEAST8_MAX */
#ifndef UINT_LEAST16_MAX
#define UINT_LEAST16_MAX __UINT_LEAST16_MAX__
#endif /* !UINT_LEAST16_MAX */
#ifndef UINT_LEAST32_MAX
#define UINT_LEAST32_MAX __UINT_LEAST32_MAX__
#endif /* !UINT_LEAST32_MAX */
#ifdef __UINT_LEAST64_MAX__
#ifndef INT_LEAST64_MAX
#define INT_LEAST64_MAX  __INT_LEAST64_MAX__
#endif /* !INT_LEAST64_MAX */
#ifndef UINT_LEAST64_MAX
#define UINT_LEAST64_MAX __UINT_LEAST64_MAX__
#endif /* !UINT_LEAST64_MAX */
#endif /* __UINT_LEAST64_MAX__ */
#ifndef INT_FAST8_MAX
#define INT_FAST8_MAX    __INT_FAST8_MAX__
#endif /* !INT_FAST8_MAX */
#ifndef INT_FAST16_MAX
#define INT_FAST16_MAX   __INT_FAST16_MAX__
#endif /* !INT_FAST16_MAX */
#ifndef INT_FAST32_MAX
#define INT_FAST32_MAX   __INT_FAST32_MAX__
#endif /* !INT_FAST32_MAX */
#ifndef UINT_FAST8_MAX
#define UINT_FAST8_MAX   __UINT_FAST8_MAX__
#endif /* !UINT_FAST8_MAX */
#ifndef UINT_FAST16_MAX
#define UINT_FAST16_MAX  __UINT_FAST16_MAX__
#endif /* !UINT_FAST16_MAX */
#ifndef UINT_FAST32_MAX
#define UINT_FAST32_MAX  __UINT_FAST32_MAX__
#endif /* !UINT_FAST32_MAX */
#ifdef __UINT_FAST64_MAX__
#ifndef INT_FAST64_MAX
#define INT_FAST64_MAX   __INT_FAST64_MAX__
#endif /* !INT_FAST64_MAX */
#ifndef UINT_FAST64_MAX
#define UINT_FAST64_MAX  __UINT_FAST64_MAX__
#endif /* !UINT_FAST64_MAX */
#endif /* __UINT_FAST64_MAX__ */
#ifndef INTPTR_MAX
#define INTPTR_MAX       __INTPTR_MAX__
#endif /* !INTPTR_MAX */
#ifndef UINTPTR_MAX
#define UINTPTR_MAX      __UINTPTR_MAX__
#endif /* !UINTPTR_MAX */
#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX      __PTRDIFF_MAX__
#endif /* !PTRDIFF_MAX */
#ifndef SIZE_MAX
#define SIZE_MAX         __SIZE_MAX__
#endif /* !SIZE_MAX */
#ifndef SIG_ATOMIC_MAX
#define SIG_ATOMIC_MAX   __SIG_ATOMIC_MAX__
#endif /* !SIG_ATOMIC_MAX */
#ifndef INT8_MIN
#define INT8_MIN         __INT8_MIN__
#endif /* !INT8_MIN */
#ifndef INT16_MIN
#define INT16_MIN        __INT16_MIN__
#endif /* !INT16_MIN */
#ifndef INT32_MIN
#define INT32_MIN        __INT32_MIN__
#endif /* !INT32_MIN */
#ifndef INT64_MIN
#define INT64_MIN        __INT64_MIN__
#endif /* !INT64_MIN */
#ifndef INTMAX_MIN
#define INTMAX_MIN       __INTMAX_MIN__
#endif /* !INTMAX_MIN */
#ifndef INT_LEAST8_MIN
#define INT_LEAST8_MIN   __INT_LEAST8_MIN__
#endif /* !INT_LEAST8_MIN */
#ifndef INT_LEAST16_MIN
#define INT_LEAST16_MIN  __INT_LEAST16_MIN__
#endif /* !INT_LEAST16_MIN */
#ifndef INT_LEAST32_MIN
#define INT_LEAST32_MIN  __INT_LEAST32_MIN__
#endif /* !INT_LEAST32_MIN */
#ifndef INT_LEAST64_MIN
#define INT_LEAST64_MIN  __INT_LEAST64_MIN__
#endif /* !INT_LEAST64_MIN */
#ifndef INT_FAST8_MIN
#define INT_FAST8_MIN    __INT_FAST8_MIN__
#endif /* !INT_FAST8_MIN */
#ifndef INT_FAST16_MIN
#define INT_FAST16_MIN   __INT_FAST16_MIN__
#endif /* !INT_FAST16_MIN */
#ifndef INT_FAST32_MIN
#define INT_FAST32_MIN   __INT_FAST32_MIN__
#endif /* !INT_FAST32_MIN */
#ifndef INT_FAST64_MIN
#define INT_FAST64_MIN   __INT_FAST64_MIN__
#endif /* !INT_FAST64_MIN */
#ifndef INTPTR_MIN
#define INTPTR_MIN       __INTPTR_MIN__
#endif /* !INTPTR_MIN */
#ifndef PTRDIFF_MIN
#define PTRDIFF_MIN      __PTRDIFF_MIN__
#endif /* !PTRDIFF_MIN */
#ifndef SIG_ATOMIC_MIN
#define SIG_ATOMIC_MIN   __SIG_ATOMIC_MIN__
#endif /* !SIG_ATOMIC_MIN */

#endif /* !_SYS_COMMON_INT_LIMITS_H */
