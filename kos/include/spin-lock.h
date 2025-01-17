/* HASH CRC-32:0x1903fa9b */
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
/* (#) Portability: GNU C Library (/mach/spin-lock.h) */
/* (#) Portability: GNU Hurd      (/usr/include/spin-lock.h) */
#ifndef _SPIN_LOCK_H
#define _SPIN_LOCK_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <lock-intern.h>

#ifdef __CC__
__SYSDECL_BEGIN

typedef __spin_lock_t spin_lock_t;
#define SPIN_LOCK_INITIALIZER __SPIN_LOCK_INITIALIZER

#define spin_lock_init(lock) __spin_lock_init(lock)
#include <kos/bits/shared-lock.h>
#if defined(__CRT_HAVE___spin_lock) || defined(__CRT_HAVE___spin_lock_solid) || defined(__CRT_HAVE___mutex_lock) || defined(__CRT_HAVE___mutex_lock_solid) || defined(__CRT_HAVE_mutex_wait_lock) || defined(__CRT_HAVE_shared_lock_acquire) || defined(__KERNEL__) || defined(__shared_lock_wait_impl)
#define spin_lock(lock) __spin_lock(lock)
#endif /* __CRT_HAVE___spin_lock || __CRT_HAVE___spin_lock_solid || __CRT_HAVE___mutex_lock || __CRT_HAVE___mutex_lock_solid || __CRT_HAVE_mutex_wait_lock || __CRT_HAVE_shared_lock_acquire || __KERNEL__ || __shared_lock_wait_impl */
#define spin_try_lock(lock) __spin_try_lock(lock)
#if defined(__CRT_HAVE___spin_unlock) || defined(__CRT_HAVE___mutex_unlock) || defined(__CRT_HAVE_mutex_unlock) || defined(__CRT_HAVE_shared_lock_release_ex) || defined(__shared_lock_release_ex) || (defined(__shared_lock_sendone) && defined(__shared_lock_sendall))
#define spin_unlock(lock) __spin_unlock(lock)
#endif /* __CRT_HAVE___spin_unlock || __CRT_HAVE___mutex_unlock || __CRT_HAVE_mutex_unlock || __CRT_HAVE_shared_lock_release_ex || __shared_lock_release_ex || (__shared_lock_sendone && __shared_lock_sendall) */
#if defined(__CRT_HAVE___spin_lock_locked) || defined(__shared_lock_available)
#define spin_lock_locked(lock) __spin_lock_locked(lock)
#endif /* __CRT_HAVE___spin_lock_locked || __shared_lock_available */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SPIN_LOCK_H */
