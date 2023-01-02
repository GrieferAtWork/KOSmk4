/* HASH CRC-32:0x822a5a64 */
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
#ifndef _LIBC_UNISTD_H
#define _LIBC_UNISTD_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/unistd.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include "core/unistd.h"

#ifndef ____libc_getpagesize_defined
#ifdef __fast_getpagesize_defined
#define ____libc_getpagesize_defined
#define __libc_getpagesize (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(getpagesize))
#elif defined(____libc_core_getpagesize_defined)
#define ____libc_getpagesize_defined
#define __libc_getpagesize __libc_core_getpagesize
#endif /* ... */
#endif /* !____libc_getpagesize_defined */
#if !defined(____libc_syscall_defined) && defined(____libc_core_syscall_defined)
#define ____libc_syscall_defined
#define __libc_syscall __libc_core_syscall
#endif /* !____libc_syscall_defined && ____libc_core_syscall_defined */
#if !defined(____libc_syscall64_defined) && defined(____libc_core_syscall64_defined)
#define ____libc_syscall64_defined
#define __libc_syscall64 __libc_core_syscall64
#endif /* !____libc_syscall64_defined && ____libc_core_syscall64_defined */

#endif /* __CC__ */

#endif /* !_LIBC_UNISTD_H */
