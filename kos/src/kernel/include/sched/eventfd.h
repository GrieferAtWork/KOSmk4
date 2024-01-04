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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_EVENTFD_H
#define GUARD_KERNEL_INCLUDE_SCHED_EVENTFD_H 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/types.h>
#include <sched/atomic64.h>
#include <sched/sig.h>

DECL_BEGIN

#ifdef __CC__

struct eventfd {
	WEAK refcnt_t ef_refcnt; /* Reference counter. */
	struct sig    ef_signal; /* Signal send when reading or writing becomes non-blocking. */
	atomic64_t    ef_value;  /* Eventfd value. */
};

/* Destroy a given eventfd object. */
#define eventfd_destroy(self)                    \
	(sig_broadcast_for_fini(&(self)->ef_signal), \
	 kfree(self))
DEFINE_REFCNT_FUNCTIONS(struct eventfd, ef_refcnt, eventfd_destroy)

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_EVENTFD_H */
