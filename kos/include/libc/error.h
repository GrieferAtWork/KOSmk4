/* HASH CRC-32:0x702301cf */
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
#ifndef _LIBC_ERROR_H
#define _LIBC_ERROR_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/error.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include "core/error.h"

#ifndef ____libc_error_defined
#ifdef __fast_error_defined
#define ____libc_error_defined
#define __libc_error (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(error))
#elif defined(____libc_core_error_defined)
#define ____libc_error_defined
#define __libc_error __libc_core_error
#endif /* ... */
#endif /* !____libc_error_defined */
#ifndef ____libc_error_at_line_defined
#ifdef __fast_error_at_line_defined
#define ____libc_error_at_line_defined
#define __libc_error_at_line (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(error_at_line))
#elif defined(____libc_core_error_at_line_defined)
#define ____libc_error_at_line_defined
#define __libc_error_at_line __libc_core_error_at_line
#endif /* ... */
#endif /* !____libc_error_at_line_defined */

#endif /* __CC__ */

#endif /* !_LIBC_ERROR_H */
