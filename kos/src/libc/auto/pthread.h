/* HASH CRC-32:0x6f58d7a6 */
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
#ifndef GUARD_LIBC_AUTO_PTHREAD_H
#define GUARD_LIBC_AUTO_PTHREAD_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <pthread.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Compare two thread identifiers */
INTDEF ATTR_CONST int NOTHROW_NCX(LIBCCALL libc_pthread_equal)(pthread_t thr1, pthread_t thr2);
/* Function called to call the cleanup handler. As an extern inline
 * function the compiler is free to decide inlining the change when
 * needed or fall back on the copy which must exist somewhere else */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc___pthread_cleanup_routine)(struct __pthread_cleanup_frame *frame);
/* Initialize the spinlock LOCK. If PSHARED is nonzero the
 * spinlock can be shared between different processes */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_pthread_spin_init)(pthread_spinlock_t *lock, int pshared);
/* Destroy the spinlock LOCK */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_pthread_spin_destroy)(pthread_spinlock_t *lock);
/* Wait until spinlock LOCK is retrieved */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_pthread_spin_lock)(pthread_spinlock_t *lock);
/* Try to lock spinlock LOCK */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_pthread_spin_trylock)(pthread_spinlock_t *lock);
/* Release spinlock LOCK */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_pthread_spin_unlock)(pthread_spinlock_t *lock);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PTHREAD_H */
