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
/* (#) Portability: NetBSD (/sys/sys/common_int_mwgwtypes.h) */
#ifndef _SYS_COMMON_INT_MWGWTYPES_H
#define _SYS_COMMON_INT_MWGWTYPES_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

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

#ifndef __intmax_t_defined
#define __intmax_t_defined
typedef __INTMAX_TYPE__  intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;
#endif /* !__intmax_t_defined */

__DECL_END
#endif /* __CC__ */


#endif /* !_SYS_COMMON_INT_MWGWTYPES_H */
