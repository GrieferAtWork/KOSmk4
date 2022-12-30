/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Linux (/usr/include/linux/futex.h) */
#ifndef _LINUX_FUTEX_H
#define _LINUX_FUTEX_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <linux/types.h>


/* NOTE: KOS's lfutex() and linux's futex() system calls can be used interchangably.
 *       However, note that lfutex() operates  on `uintptr_t', while linux  operates
 *       on  `int', meaning  that associated data  type sizes may  differ on certain
 *       architectures. */


/* Second argument to futex syscall */

#define FUTEX_WAIT            0 /* while(*uaddr == val) wait(uaddr, rel_timeout); */
#define FUTEX_WAKE            1 /* wake(uaddr, max: val); */
#define FUTEX_FD              2
#define FUTEX_REQUEUE         3
#define FUTEX_CMP_REQUEUE     4
#define FUTEX_WAKE_OP         5
#define FUTEX_LOCK_PI         6
#define FUTEX_UNLOCK_PI       7
#define FUTEX_TRYLOCK_PI      8
#define FUTEX_WAIT_BITSET     9  /* while(*uaddr == val) wait(uaddr, abs_timeout, channels: val3); */
#define FUTEX_WAKE_BITSET     10 /* wake(uaddr, max: val, channels: val3); */
#define FUTEX_WAIT_REQUEUE_PI 11
#define FUTEX_CMP_REQUEUE_PI  12

#define FUTEX_PRIVATE_FLAG            128
#define FUTEX_CLOCK_REALTIME          256
#define FUTEX_CMD_MASK                (~(FUTEX_PRIVATE_FLAG | FUTEX_CLOCK_REALTIME))
#define FUTEX_WAIT_PRIVATE            (FUTEX_WAIT | FUTEX_PRIVATE_FLAG)
#define FUTEX_WAKE_PRIVATE            (FUTEX_WAKE | FUTEX_PRIVATE_FLAG)
#define FUTEX_REQUEUE_PRIVATE         (FUTEX_REQUEUE | FUTEX_PRIVATE_FLAG)
#define FUTEX_CMP_REQUEUE_PRIVATE     (FUTEX_CMP_REQUEUE | FUTEX_PRIVATE_FLAG)
#define FUTEX_WAKE_OP_PRIVATE         (FUTEX_WAKE_OP | FUTEX_PRIVATE_FLAG)
#define FUTEX_LOCK_PI_PRIVATE         (FUTEX_LOCK_PI | FUTEX_PRIVATE_FLAG)
#define FUTEX_UNLOCK_PI_PRIVATE       (FUTEX_UNLOCK_PI | FUTEX_PRIVATE_FLAG)
#define FUTEX_TRYLOCK_PI_PRIVATE      (FUTEX_TRYLOCK_PI | FUTEX_PRIVATE_FLAG)
#define FUTEX_WAIT_BITSET_PRIVATE     (FUTEX_WAIT_BITSET | FUTEX_PRIVATE_FLAG)
#define FUTEX_WAKE_BITSET_PRIVATE     (FUTEX_WAKE_BITSET | FUTEX_PRIVATE_FLAG)
#define FUTEX_WAIT_REQUEUE_PI_PRIVATE (FUTEX_WAIT_REQUEUE_PI | FUTEX_PRIVATE_FLAG)
#define FUTEX_CMP_REQUEUE_PI_PRIVATE  (FUTEX_CMP_REQUEUE_PI | FUTEX_PRIVATE_FLAG)

/* Support for robust futexes: the kernel cleans up held futexes at thread exit time. */

#ifdef __CC__
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("robust_list")
#pragma push_macro("robust_list_head")
#pragma push_macro("next")
#pragma push_macro("list")
#pragma push_macro("futex_offset")
#pragma push_macro("list_op_pending")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef robust_list
#undef robust_list_head
#undef next
#undef list
#undef futex_offset
#undef list_op_pending

/* Per-lock list entry - embedded in user-space locks, somewhere close
 * to  the futex field. (Note: user-space uses a double-linked list to
 * achieve O(1) list add and remove, but the kernel only needs to know
 * about the forward link)
 * NOTE: this structure is part of the syscall ABI, and must not be changed. */
struct robust_list {
	struct robust_list *next;
};

/* Per-thread list head:
 * NOTE: this structure is part of the syscall ABI, and must only  be
 * changed  if the change is first communicated with the Glibc folks.
 * (When an incompatible change is done, we'll increase the structure
 * size, which Glibc will detect) */
struct robust_list_head {

	/* The head of the list. Points back to itself if empty: */
	struct robust_list  list;

	/* This  relative offset is set by user-space, it gives the kernel
	 * the relative position of the  futex field to examine. This  way
	 * we keep userspace flexible, to freely shape its data-structure,
	 * without hardcoding any particular offset into the kernel: */
	__LONGPTR_TYPE__    futex_offset;

	/* The death of  the thread may  race with userspace  setting
	 * up a lock's links. So to handle this race, userspace first
	 * sets this field  to the address  of the to-be-taken  lock,
	 * then  does the lock  acquire, and then  adds itself to the
	 * list, and then  clears this field.  Hence the kernel  will
	 * always have full  knowledge of all  locks that the  thread
	 * _might_  have taken. We  check the owner  TID in any case,
	 * so only truly owned locks will be handled. */
	struct robust_list *list_op_pending;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("list_op_pending")
#pragma pop_macro("futex_offset")
#pragma pop_macro("list")
#pragma pop_macro("next")
#pragma pop_macro("robust_list_head")
#pragma pop_macro("robust_list")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __CC__ */

#define FUTEX_WAITERS          0x80000000 /* Are there any waiters for this robust futex */
#define FUTEX_OWNER_DIED       0x40000000 /* The kernel signals via this bit that a thread holding a futex
                                           * has exited without unlocking the futex. The kernel also  does
                                           * a  FUTEX_WAKE on such futexes, after setting the bit, to wake
                                           * up any possible waiters */
#define FUTEX_TID_MASK         0x3fffffff /* The rest of the robust-futex field is for the TID */
#define ROBUST_LIST_LIMIT      2048       /* This limit protects against a deliberately circular list.
                                           * (Not worth introducing an rlimit for it) */
#define FUTEX_BITSET_MATCH_ANY 0xffffffff /* bitset with all bits set for the FUTEX_xxx_BITSET OPs to request a match of any bit. */

#define FUTEX_OP_SET         0 /* *(int *)UADDR2 = OPARG; */
#define FUTEX_OP_ADD         1 /* *(int *)UADDR2 += OPARG; */
#define FUTEX_OP_OR          2 /* *(int *)UADDR2 |= OPARG; */
#define FUTEX_OP_ANDN        3 /* *(int *)UADDR2 &= ~OPARG; */
#define FUTEX_OP_XOR         4 /* *(int *)UADDR2 ^= OPARG; */
#define FUTEX_OP_OPARG_SHIFT 8 /* Use (1 << OPARG) instead of OPARG.  */
#define FUTEX_OP_CMP_EQ      0 /* if (oldval == CMPARG) wake */
#define FUTEX_OP_CMP_NE      1 /* if (oldval != CMPARG) wake */
#define FUTEX_OP_CMP_LT      2 /* if (oldval < CMPARG) wake */
#define FUTEX_OP_CMP_LE      3 /* if (oldval <= CMPARG) wake */
#define FUTEX_OP_CMP_GT      4 /* if (oldval > CMPARG) wake */
#define FUTEX_OP_CMP_GE      5 /* if (oldval >= CMPARG) wake */

/* FUTEX_WAKE_OP will perform atomically
 * >> int oldval = *(int *)UADDR2;
 * >> *(int *)UADDR2 = oldval OP OPARG;
 * >> if (oldval CMP CMPARG)
 * >>     wake UADDR2; */
#define FUTEX_OP(op, oparg, cmp, cmparg)        \
	(((op & 0xf) << 28) | ((cmp & 0xf) << 24) | \
	 ((oparg & 0xfff) << 12) | (cmparg & 0xfff))

#endif /* _LINUX_FUTEX_H */
