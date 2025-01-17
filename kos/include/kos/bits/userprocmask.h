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
#ifndef _KOS_BITS_USERPROCMASK_H
#define _KOS_BITS_USERPROCMASK_H 1

#include <__stdinc.h>

#include <bits/os/sigset.h>
#include <bits/types.h>

#define __OFFSET_USERPROCMASK_MYTID   0
#define __OFFSET_USERPROCMASK_SIGSIZE __SIZEOF_POINTER__
#define __OFFSET_USERPROCMASK_SIGMASK (__SIZEOF_POINTER__ * 2)
#define __OFFSET_USERPROCMASK_FLAGS   (__SIZEOF_POINTER__ * 3)
#define __OFFSET_USERPROCMASK_PENDING (__SIZEOF_POINTER__ * 4)
#define __SIZEOF_USERPROCMASK         (__SIZEOF_POINTER__ * 4 + __SIZEOF_SIGSET_T__)

/* Bits for `userprocmask::pm_flags' */
#define USERPROCMASK_FLAG_NORMAL     0x0000 /* Normal flags. */
#define USERPROCMASK_FLAG_HASPENDING 0x0001 /* FLAG: `pm_pending' may contain  non-zero entries.  Set
                                             * by the kernel and expected to be cleared by userspace. */

#ifdef __CC__
__DECL_BEGIN

/* User-space sigprocmask() control structure (this structure should be
 * placed in TLS memory, and its  contents are shared with the  kernel)
 *
 * NOTE: Arch-specific variants of  this structure  may contain  additional
 *       fields that must  be initialized  to all 0-es,  meaning that  when
 *       the caller intends to initialize this structure, they must  either
 *       know of all of these fields, or they may simply bzero() the entire
 *       structure before filling in the intended fields.
 *       Also note that for this purpose, `pm_pending' is _always_ the last
 *       element of this structure, as this field is technically  variable-
 *       length, such that  the actual sizeof()  this structure is  always:
 *       >> offsetof(struct userprocmask, pm_pending) + self->pm_sigsize; */
struct userprocmask /*[PREFIX(pm_)]*/ {
	__pid_t                 pm_mytid;   /* [const] TID of the thread (same as `set_tid_address(2)') */
#if __SIZEOF_PID_T__ < __SIZEOF_POINTER__
	__byte_t _pm_pad[__SIZEOF_POINTER__ - __SIZEOF_PID_T__]; /* ... */
#endif /* __SIZEOF_PID_T__ < __SIZEOF_POINTER__ */
	__size_t                pm_sigsize; /* [const] == sizeof(sigset_t) */
	struct __sigset_struct *pm_sigmask; /* [KERNEL:READ|WRITE(1), USER:WRITE][0..1] Pointer to the current signal mask
	                                     * The  kernel may or' this with another mask when a signal handler is invoked
	                                     * that contains a non-empty `sa_mask'.
	                                     * Set to `NULL' to indicate that `sys_set_userprocmask_address(2)' wasn't called, yet. */
	__uintptr_t             pm_flags;   /* [KERNEL:WRITE, USER:READWRITE] Set of `USERPROCMASK_FLAG_*' */
	struct __sigset_struct  pm_pending; /* [KERNEL:WRITE, USER:READWRITE][sizeof(== pm_sigsize)] Set of pending signals
	                                     * When a currently masked signal arrives, the kernel
	                                     * will set its associated bit to 1 within this set. */
};

#define USERPROCMASK_INIT(mytid, sigsize, sigmask, flags, pending) \
	{ mytid, sigsize, sigmask, flags, pending }

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_USERPROCMASK_H */
