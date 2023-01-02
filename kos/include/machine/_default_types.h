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
/* (#) Portability: Cygwin (/newlib/libc/include/machine/_default_types.h) */
/* (#) Portability: Newlib (/newlib/libc/include/machine/_default_types.h) */
#ifndef _MACHINE__DEFAULT_TYPES_H
#define _MACHINE__DEFAULT_TYPES_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

__DECL_BEGIN

#ifdef __CC__

/* Other types were already defined in <bits/types.h> */
typedef __INT_LEAST8_TYPE__   __int_least8_t;
typedef __UINT_LEAST8_TYPE__  __uint_least8_t;
typedef __INT_LEAST16_TYPE__  __int_least16_t;
typedef __UINT_LEAST16_TYPE__ __uint_least16_t;
typedef __INT_LEAST32_TYPE__  __int_least32_t;
typedef __UINT_LEAST32_TYPE__ __uint_least32_t;
#ifdef __UINT_LEAST64_TYPE__
typedef __INT_LEAST64_TYPE__  __int_least64_t;
typedef __UINT_LEAST64_TYPE__ __uint_least64_t;
#endif /* __UINT_LEAST64_TYPE__ */
typedef __INTMAX_TYPE__       __intmax_t;
typedef __UINTMAX_TYPE__      __uintmax_t;

#endif /* __CC__ */

__DECL_END

#endif /* !_MACHINE__DEFAULT_TYPES_H */
