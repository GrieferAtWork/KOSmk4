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
/* (#) Portability: Cygwin  (/newlib/libc/include/sys/_stdint.h) */
/* (#) Portability: FreeBSD (/sys/sys/_stdint.h) */
/* (#) Portability: Newlib  (/newlib/libc/include/sys/_stdint.h) */
#ifndef _SYS__STDINT_H
#define _SYS__STDINT_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <machine/_default_types.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __INT8_TYPE__
#define _INT8_T_DECLARED
#endif /* __INT8_TYPE__ */
#ifdef __INT16_TYPE__
#define _INT16_T_DECLARED
#endif /* __INT16_TYPE__ */
#ifdef __INT32_TYPE__
#define _INT32_T_DECLARED
#endif /* __INT32_TYPE__ */
#ifdef __INT64_TYPE__
#define _INT64_T_DECLARED
#endif /* __INT64_TYPE__ */

#ifdef __UINT8_TYPE__
#define _UINT8_T_DECLARED
#endif /* __UINT8_TYPE__ */
#ifdef __UINT16_TYPE__
#define _UINT16_T_DECLARED
#endif /* __UINT16_TYPE__ */
#ifdef __UINT32_TYPE__
#define _UINT32_T_DECLARED
#endif /* __UINT32_TYPE__ */
#ifdef __UINT64_TYPE__
#define _UINT64_T_DECLARED
#endif /* __UINT64_TYPE__ */

#define _INTMAX_T_DECLARED
#define _UINTMAX_T_DECLARED
#define _INTPTR_T_DECLARED
#define _UINTPTR_T_DECLARED

#ifndef ___int8_t_defined
#define ___int8_t_defined
#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ _int8_t;
#endif /* __INT8_TYPE__ */
#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ _int16_t;
#endif /* __INT16_TYPE__ */
#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ _int32_t;
#endif /* __INT32_TYPE__ */
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ _int64_t;
#endif /* __INT64_TYPE__ */
#endif /* ___int8_t_defined */

#ifndef ___uint8_t_defined
#define ___uint8_t_defined
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ _uint8_t;
#endif /* __UINT8_TYPE__ */
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ _uint16_t;
#endif /* __UINT16_TYPE__ */
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ _uint32_t;
#endif /* __UINT32_TYPE__ */
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ _uint64_t;
#endif /* __UINT64_TYPE__ */
#endif /* !___uint8_t_defined */

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
#endif /* __int8_t_defined */

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

#ifndef __intmax_t_defined
#define __intmax_t_defined
typedef __INTMAX_TYPE__ intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;
#endif /* !__intmax_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */

#ifndef __uintptr_t_defined
#define __uintptr_t_defined
typedef __uintptr_t uintptr_t;
#endif /* !__uintptr_t_defined */

__DECL_END
#endif /* __CC__ */

#endif /* !_SYS__STDINT_H */
