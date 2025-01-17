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
#ifndef _I386_KOS_KOS_BITS_USERPROCMASK_H
#define _I386_KOS_KOS_BITS_USERPROCMASK_H 1

#include <__stdinc.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <bits/os/sigset.h>

#define __OFFSET_USERPROCMASK_MYTID   0
#define __OFFSET_USERPROCMASK_SIGSIZE 8
#define __OFFSET_USERPROCMASK_SIGMASK 16
#define __OFFSET_USERPROCMASK_FLAGS   24
#define __OFFSET_USERPROCMASK_PENDING 32
#define __SIZEOF_USERPROCMASK         (32 + __SIZEOF_SIGSET_T__)

/* Bits for `userprocmask::pm_flags' */
#define USERPROCMASK_FLAG_NORMAL     0x0000 /* Normal flags. */
#define USERPROCMASK_FLAG_HASPENDING 0x0001 /* FLAG: `pm_pending' may contain  non-zero entries.  Set
                                             * by the kernel and expected to be cleared by userspace. */

#ifdef __CC__
__DECL_BEGIN

/* User-space sigprocmask() control structure (this structure should be
 * placed in TLS memory, and its  contents are shared with the  kernel)
 *
 * NOTE: On i386, you must initialize `_pm_pad1' and `_pm_pad2' to `0'
 *       before  calling  `sys_set_userprocmask_address(2)'.  This  is
 *       required for binary compatibility with x86_64! */
struct userprocmask /*[PREFIX(pm_)]*/ {
	__INT32_TYPE__          pm_mytid;   /* [const] TID of the thread (same as `set_tid_address(2)') */
	__UINT32_TYPE__        _pm_pad0;    /* ... */
#ifdef __x86_64__
	__UINT64_TYPE__         pm_sigsize; /* [const] == sizeof(sigset_t) */
	struct __sigset_struct *pm_sigmask; /* [KERNEL:READ|WRITE(1), USER:WRITE][1..1] Pointer to the current signal mask
	                                     * The  kernel may or' this with another mask when a signal handler is invoked
	                                     * that contains a non-empty `sa_mask'.
	                                     * Set to `NULL' to indicate that `sys_set_userprocmask_address(2)' hasn't been called, yet. */
	__UINT64_TYPE__         pm_flags;   /* [KERNEL:WRITE, USER:READWRITE] Set of `USERPROCMASK_FLAG_*' */
#else /* __x86_64__ */
	__UINT32_TYPE__         pm_sigsize; /* [const] == sizeof(sigset_t) */
	__UINT32_TYPE__        _pm_pad1;    /* ... */
	struct __sigset_struct *pm_sigmask; /* [KERNEL:READ|WRITE(1), USER:WRITE][1..1] Pointer to the current signal mask
	                                     * The  kernel may or' this with another mask when a signal handler is invoked
	                                     * that contains a non-empty `sa_mask'.
	                                     * Set to `NULL' to indicate that `sys_set_userprocmask_address(2)' hasn't been called, yet. */
	__UINT32_TYPE__        _pm_pad2;    /* ... */
	__UINT32_TYPE__         pm_flags;   /* [KERNEL:WRITE, USER:READWRITE] Set of `USERPROCMASK_FLAG_*' */
	__UINT32_TYPE__        _pm_pad3;    /* ... */
#endif /* !__x86_64__ */
	struct __sigset_struct  pm_pending; /* [KERNEL:WRITE, USER:READWRITE][sizeof(== pm_sigsize)] Set of pending signals
	                                     * When a currently masked signal arrives, the kernel
	                                     * will set its associated bit to 1 within this set. */
};

#ifdef __x86_64__
#define USERPROCMASK_INIT(mytid, sigsize, sigmask, flags, pending) \
	{ mytid, 0, sigsize, sigmask, flags, pending }
#else /* __x86_64__ */
#define USERPROCMASK_INIT(mytid, sigsize, sigmask, flags, pending) \
	{ mytid, 0, sigsize, 0, sigmask, 0, flags, 0, pending }
#endif /* !__x86_64__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_BITS_USERPROCMASK_H */
