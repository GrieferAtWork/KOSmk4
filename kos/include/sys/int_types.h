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
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/int_types.h) */
#ifndef _SYS_INT_TYPES_H
#define _SYS_INT_TYPES_H 1

#include <__stdinc.h>
#include <features.h> /* Include required for compatibility */

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

/* Deduced set of definitions, as would also be declared by <stdint.h> */

#ifndef __intmax_t_defined
#define __intmax_t_defined
typedef __INTMAX_TYPE__  intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;
#endif /* !__intmax_t_defined */

#ifndef __int8_t_defined
#define __int8_t_defined
#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ int8_t;
#endif /* __INT8_TYPE__ */
#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ int16_t;
#endif /* __INT16_TYPE__ */
#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ int32_t;
#endif /* __INT32_TYPE__ */
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ int64_t;
#endif /* __INT64_TYPE__ */
#endif /* !__int8_t_defined */

#ifndef __uint8_t_defined
#define __uint8_t_defined
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ uint8_t;
#endif /* __UINT8_TYPE__ */
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ uint16_t;
#endif /* __UINT16_TYPE__ */
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ uint32_t;
#endif /* __UINT32_TYPE__ */
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ uint64_t;
#endif /* __UINT64_TYPE__ */
#endif /* !__uint8_t_defined */

#ifndef __int_least8_t_defined
#define __int_least8_t_defined
typedef __INT_LEAST8_TYPE__   int_least8_t;
typedef __INT_LEAST16_TYPE__  int_least16_t;
typedef __INT_LEAST32_TYPE__  int_least32_t;
typedef __UINT_LEAST8_TYPE__  uint_least8_t;
typedef __UINT_LEAST16_TYPE__ uint_least16_t;
typedef __UINT_LEAST32_TYPE__ uint_least32_t;
#ifdef __UINT_LEAST64_TYPE__
typedef __INT_LEAST64_TYPE__  int_least64_t;
typedef __UINT_LEAST64_TYPE__ uint_least64_t;
#endif /* __UINT_LEAST64_TYPE__ */
#endif /* !__int_least8_t_defined */

#ifndef __int_fast8_t_defined
#define __int_fast8_t_defined
typedef __INT_FAST8_TYPE__   int_fast8_t;
typedef __INT_FAST16_TYPE__  int_fast16_t;
typedef __UINT_FAST8_TYPE__  uint_fast8_t;
typedef __UINT_FAST16_TYPE__ uint_fast16_t;
typedef __INT_FAST32_TYPE__  int_fast32_t;
typedef __UINT_FAST32_TYPE__ uint_fast32_t;
#ifdef __UINT_FAST64_TYPE__
typedef __INT_FAST64_TYPE__  int_fast64_t;
typedef __UINT_FAST64_TYPE__ uint_fast64_t;
#endif /* __UINT_FAST64_TYPE__ */
#endif /* !__int_fast8_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined
typedef __INTPTR_TYPE__  intptr_t;
#endif /* !__intptr_t_defined */

#ifndef __uintptr_t_defined
#define __uintptr_t_defined
typedef __UINTPTR_TYPE__ uintptr_t;
#endif /* !__uintptr_t_defined */


__DECL_END
#endif /* __CC__ */

#endif /* !_SYS_INT_TYPES_H */
