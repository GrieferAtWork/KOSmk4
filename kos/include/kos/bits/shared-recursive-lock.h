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
#ifndef _KOS_BITS_SHARED_RECURSIVE_LOCK_H
#define _KOS_BITS_SHARED_RECURSIVE_LOCK_H 1

#include <__stdinc.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/sched/__gettid.h>

#include <bits/types.h>
#include <kos/bits/shared-lock.h>

#ifdef __CC__
__DECL_BEGIN

#define __shared_recursive_lock_tid_t       __hybrid_tid_t
#define __shared_recursive_lock_gettid()    __hybrid_gettid()
#define __shared_recursive_lock_eqtid(a, b) __hybrid_gettid_equal(a, b)
#define __shared_recursive_lock_mytid(tid)  __hybrid_gettid_iscaller(tid)
#define __SHARED_RECURSIVE_LOCK_BADTID      __HYBRID_GETTID_INVALID
#ifdef __HYBRID_GETTID_INVALID_IS_ZERO
#define __SHARED_RECURSIVE_LOCK_BADTID_ISZERO
#endif /* __HYBRID_GETTID_INVALID_IS_ZERO */

struct shared_recursive_lock {
	struct shared_lock            sr_lock;  /* Underlying lock */
	__shared_recursive_lock_tid_t sr_owner; /* [0..1|NULL(__HYBRID_GETTID_INVALID)] Thread holding the lock */
	__uintptr_t                   sr_rcnt;  /* [lock(WRITING)] Number of recursive locks (0 means only one lock remains) */
};

/* Check if the caller is is the owner of `self' */
#define __shared_recursive_lock_isown(self) \
	__shared_recursive_lock_mytid((self)->sr_owner)

/* Set the caller as the owner of `self' */
#define __shared_recursive_lock_setown(self)              \
	((self)->sr_owner = __shared_recursive_lock_gettid(), \
	 __hybrid_assert((self)->sr_rcnt == 0))

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_SHARED_RECURSIVE_LOCK_H */
