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
/*!replace_with_include <kos/sched/shared-recursive-rwlock.h>*/
#ifndef _KOS_BITS_SHARED_RECURSIVE_RWLOCK_H
#define _KOS_BITS_SHARED_RECURSIVE_RWLOCK_H 1

#include <__stdinc.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/sched/__gettid.h>

#include <bits/types.h>
#include <kos/bits/shared-rwlock.h>

#ifdef __CC__
__DECL_BEGIN

#define __shared_recursive_rwlock_tid_t       __hybrid_tid_t
#define __shared_recursive_rwlock_gettid()    __hybrid_gettid()
#define __shared_recursive_rwlock_eqtid(a, b) __hybrid_gettid_equal(a, b)
#define __shared_recursive_rwlock_mytid(tid)  __hybrid_gettid_iscaller(tid)
#define __SHARED_RECURSIVE_RWLOCK_BADTID      __HYBRID_GETTID_INVALID
#ifdef __HYBRID_GETTID_INVALID_IS_ZERO
#define __SHARED_RECURSIVE_RWLOCK_BADTID_ISZERO
#endif /* __HYBRID_GETTID_INVALID_IS_ZERO */

struct shared_recursive_rwlock {
	struct shared_rwlock            srr_lock;   /* Underlying R/W-lock */
	__shared_recursive_rwlock_tid_t srr_writer; /* [0..1|NULL(__HYBRID_GETTID_INVALID)] Thread holding a write-lock */
	__uintptr_t                     srr_wrcnt;  /* [lock(WRITING)] Number of additional write-locks (0 means only one write-lock remains) */
};

/* Check if the caller is the write-lock owner of `self' */
#define __shared_recursive_rwlock_isown(self) \
	__shared_recursive_rwlock_mytid((self)->srr_writer)

/* Set the caller as the write-lock owner of `self' */
#define __shared_recursive_rwlock_setown(self)                \
	((self)->srr_writer = __shared_recursive_rwlock_gettid(), \
	 __hybrid_assert((self)->srr_wrcnt == 0))

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_SHARED_RECURSIVE_RWLOCK_H */
