/* HASH CRC-32:0xb25c1d79 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBC_FENV_H
#define _LIBC_FENV_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/fenv.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include "slow/fenv.h"

#ifdef __fast_feraiseexcept_defined
/* Raise the supported exceptions represented by EXCEPTS */
#define __libc_feraiseexcept (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(feraiseexcept))
#else /* __fast_feraiseexcept_defined */
/* Raise the supported exceptions represented by EXCEPTS */
#define __libc_feraiseexcept __libc_slow_feraiseexcept
#endif /* !__fast_feraiseexcept_defined */
#ifdef __fast_fegetround_defined
/* Get current rounding direction */
#define __libc_fegetround (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(fegetround))
#else /* __fast_fegetround_defined */
/* Get current rounding direction */
#define __libc_fegetround __libc_slow_fegetround
#endif /* !__fast_fegetround_defined */

#endif /* __CC__ */

#endif /* !_LIBC_FENV_H */
