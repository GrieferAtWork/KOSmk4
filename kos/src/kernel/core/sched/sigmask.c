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
#ifndef GUARD_KERNEL_SRC_SCHED_SIGMASK_C
#define GUARD_KERNEL_SRC_SCHED_SIGMASK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/nopf.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/rt/except-handler.h>
#include <kernel/rt/except-syscall.h> /* CONFIG_HAVE_USERPROCMASK */
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/rpc-internal.h>
#include <sched/sigmask.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/typecore.h>

#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <sys/param.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <signal.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/types.h>
#include <compat/pointer.h>
#include <compat/signal.h>
#endif /* __ARCH_HAVE_COMPAT */


DECL_BEGIN

/* An empty signal mask used to initialize `this_kernel_sigmask' */
PUBLIC struct kernel_sigmask kernel_sigmask_empty = {
	.sm_refcnt = 2,
	.sm_share  = 2,
	.sm_mask   = {{ 0 }}
};


#define SIGSET_WORD_C   __UINTPTR_C
#define SIGSET_WORDBITS (__SIZEOF_POINTER__ * NBBY)
#define SIGSET_NUMBITS  (__SIGSET_NWORDS * SIGSET_WORDBITS)


/* A full signal mask (i.e. one that blocks all signals (except for SIGKILL and SIGSTOP)) */
PUBLIC struct kernel_sigmask kernel_sigmask_full = {
	.sm_refcnt = 2,
	.sm_share  = 2,
	.sm_mask   = {{
/*[[[deemon

// Supported values for various signal constants
local supported_SIGKILL_values = [9];
local supported_SIGSTOP_values = [19];
local supported_sigset_bits    = [1024];
local supported_pointer_bits   = [32, 64];

function printMap(unmaskedSignals, bitsof_sigset, bits_per_word) {
	local numWords = (bitsof_sigset + bits_per_word - 1) / bits_per_word;
	local wordValues = [(1 << bits_per_word) - 1] * numWords;
	function clearSig(signo) {
		signo = signo - 1;
		local word = signo / bits_per_word;
		local mask = 1 << (signo % bits_per_word);
		wordValues[word] = wordValues[word] & ~mask;
	}
	for (local x: unmaskedSignals)
		clearSig(x);
	local i, v;
	import util;
	for (i, v: util.enumerate(wordValues)) {
		if ((i % 4) == 0)
			print("\t\t"),;
		else {
			print(" "),;
		}
		print("SIGSET_WORD_C(", v.hex(), ")"),;
		if (i != #wordValues - 1)
			print(","),;
		if ((i % 4) == 3)
			print;
	}
	if ((i % 4) != 3)
		print;
}

local combinations = [];
for (local a: supported_SIGKILL_values) {
	for (local b: supported_SIGSTOP_values) {
		for (local c: supported_sigset_bits) {
			for (local d: supported_pointer_bits) {
				combinations.append((a, b, c, d));
			}
		}
	}
}

local isFirst = true;
for (local sigkill, sigstop, bitsof_sigset, bits_per_word: combinations) {
	print("#", isFirst ? "" : "el",
		"if SIGKILL == ", sigkill,
		" && SIGSTOP == ", sigstop,
		" && SIGSET_NUMBITS == ", bitsof_sigset,
		" && SIGSET_WORDBITS == ", bits_per_word);
	printMap((sigkill, sigstop), bitsof_sigset, bits_per_word);
	isFirst = false;
}
print("#elif !defined(__DEEMON__)");
print("#error \"Unsupported combination of signal constants\"");
print("#endif /" "* ... *" "/");
]]]*/
#if SIGKILL == 9 && SIGSTOP == 19 && SIGSET_NUMBITS == 1024 && SIGSET_WORDBITS == 32
		SIGSET_WORD_C(0xfffbfeff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff),
		SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff),
		SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff),
		SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff),
		SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff),
		SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff),
		SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff),
		SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff)
#elif SIGKILL == 9 && SIGSTOP == 19 && SIGSET_NUMBITS == 1024 && SIGSET_WORDBITS == 64
		SIGSET_WORD_C(0xfffffffffffbfeff), SIGSET_WORD_C(0xffffffffffffffff), SIGSET_WORD_C(0xffffffffffffffff), SIGSET_WORD_C(0xffffffffffffffff),
		SIGSET_WORD_C(0xffffffffffffffff), SIGSET_WORD_C(0xffffffffffffffff), SIGSET_WORD_C(0xffffffffffffffff), SIGSET_WORD_C(0xffffffffffffffff),
		SIGSET_WORD_C(0xffffffffffffffff), SIGSET_WORD_C(0xffffffffffffffff), SIGSET_WORD_C(0xffffffffffffffff), SIGSET_WORD_C(0xffffffffffffffff),
		SIGSET_WORD_C(0xffffffffffffffff), SIGSET_WORD_C(0xffffffffffffffff), SIGSET_WORD_C(0xffffffffffffffff), SIGSET_WORD_C(0xffffffffffffffff)
#elif !defined(__DEEMON__)
#error "Unsupported combination of signal constants"
#endif /* ... */
/*[[[end]]]*/
	}}
};



/* [1..1][lock(READ(ATOMIC), WRITE(THIS_TASK))]
 * Reference to the signal mask (set of signals being blocked) in the  current
 * thread. The pointed-to object is meaningless (but must still be valid) when
 * the associated thread make use of userprocmask. */
PUBLIC ATTR_PERTASK struct kernel_sigmask_arref
this_kernel_sigmask = ARREF_INIT(&kernel_sigmask_empty);

DEFINE_PERTASK_FINI(fini_this_kernel_sigmask);
PRIVATE NOBLOCK ATTR_USED NONNULL((1)) void
NOTHROW(KCALL fini_this_kernel_sigmask)(struct task *__restrict thread) {
	REF struct kernel_sigmask *mask;
	mask = arref_ptr(&FORTASK(thread, this_kernel_sigmask));
	if (mask != &kernel_sigmask_empty)
		decref(mask);
}




#ifdef CONFIG_HAVE_USERPROCMASK
PRIVATE ATTR_PURE WUNUSED bool FCALL
usersigmask_ismasked_chk(signo_t signo) THROWS(E_SEGFAULT) {
	ulongptr_t mask, word;
	USER CHECKED struct userprocmask *umask;
	USER UNCHECKED sigset_t *usigset;
	bool result;

	/* Load the address of the userprocmask descriptor. */
	umask = PERTASK_GET(this_userprocmask_address);
	assert(umask && ADDR_ISUSER(umask));

	/* Mark the signal as pending for this thread. */
	word = __sigset_word(signo);
	mask = __sigset_mask(signo);

	/* First user-space memory access: read our current signal mask. */
	usigset = ATOMIC_READ(umask->pm_sigmask);

	/* Make sure that the user-space pointer is valid. */
	validate_readable(usigset, sizeof(sigset_t));

	/* Check if `signo' is a member.
	 * NOTE: This call contains the second user-space memory access! */
	result = (usigset->__val[word] & mask) != 0;

	if (result) {
		/* The is the signal is masked, we must tell user-space that we've
		 * checked, and  that the  signal may  be pending  at this  point. */
		if ((ATOMIC_READ(umask->pm_pending.__val[word]) & mask) == 0) {
			ATOMIC_OR(umask->pm_pending.__val[word], mask);
			ATOMIC_OR(umask->pm_flags, USERPROCMASK_FLAG_HASPENDING);
			printk(KERN_DEBUG "[userprocmask:%p] Mark signal %d as pending\n",
			       umask, signo);
		}
	}
	return result;
}
#endif /* CONFIG_HAVE_USERPROCMASK */




/* Make sure that casting boolean expressions to
 * integers  yields the expected results of 0/1.
 * This is assumed by code below */
STATIC_ASSERT(SIGMASK_ISMASKED_NOPF_NO == (int)false);
STATIC_ASSERT(SIGMASK_ISMASKED_NOPF_NO == (int)(10 == 0));
STATIC_ASSERT(SIGMASK_ISMASKED_NOPF_YES == (int)true);
STATIC_ASSERT(SIGMASK_ISMASKED_NOPF_YES == (int)(10 != 0));

#ifdef CONFIG_HAVE_USERPROCMASK
/* Try  to  switch  page  directory  to  that  of  `self',  and  make  use
 * of  memcpy_nopf()   to  try   to  read   its  user-space   userprocmask
 * to  determine  if  the  given   `signo'  is  currently  being   masked.
 * If any of these steps fail, simply return `SIGMASK_ISMASKED_NOPF_FAULT'
 * NOTE: The caller is responsible to ensure that `self->t_cpu == THIS_CPU',
 *       as well as that preemption has been disabled. */
PRIVATE NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW(FCALL sigmask_ismasked_in_userprocmask_nopf)(struct task *__restrict self,
                                                     signo_t signo) {
	int result = SIGMASK_ISMASKED_NOPF_FAULT;
	USER CHECKED struct userprocmask *um;
	USER UNCHECKED sigset_t *current_sigmask;
	struct mman *mymm, *threadmm;
	/* NOTE: This read is safe, since `self' is running on  THIS_CPU,
	 *       the `this_userprocmask_address'  field is  write-private
	 *       to `self', and preemption  is disabled, meaning that  we
	 *       know that nothing can change `this_userprocmask_address' */
	um = FORTASK(self, this_userprocmask_address);

	/* Make sure we're operating  in the context of  `self->t_mman'
	 * Note that we don't use task_setmman() to change our's, since
	 * that function would be complete overkill for our purposes. */
	mymm     = THIS_MMAN;
	threadmm = self->t_mman;
	if (mymm != threadmm)
		pagedir_set(threadmm->mm_pagedir_p);

	/* Use memcpy_nopf() to read the thread's current signal mask pointer. */
	if (!read_nopf(&um->pm_sigmask, &current_sigmask))
		goto done;

	/* Verify that `current_sigmask' points into user-space. */
	if unlikely(!ADDR_ISUSER(current_sigmask))
		goto done;

	/* Now dereference `current_sigmask' at an appropriate location
	 * in relation to `signo' */
	{
		ulongptr_t user_sigmask_word;
		ulongptr_t word, mask;
		word = __sigset_word(signo);
		mask = __sigset_mask(signo);
		if (!read_nopf(&current_sigmask->__val[word], &user_sigmask_word))
			goto done;

		/* If we manage to get to this point, then we know that `user_sigmask_word'
		 * is  the correct mask value that we were after. - Use it now to determine
		 * the masking-state of `signo' in `self' */
		result = (user_sigmask_word & mask) != 0;

		if (result == SIGMASK_ISMASKED_NOPF_YES) {
			/* The signal _is_ being masked! */
			if unlikely(!read_nopf(&um->pm_pending.__val[word], &user_sigmask_word)) {
set_maybe_and_return:
				result = SIGMASK_ISMASKED_NOPF_FAULT;
				goto done;
			}
			if ((user_sigmask_word & mask) == 0) {
				/* The signal _is_ being masked, but isn't marked as  pending.
				 * As such, we then we still have to turn on the corresponding
				 * bit in `um->pm_pending'! */
#ifdef atomic_or_nopf
				if unlikely(!atomic_or_nopf(&um->pm_pending.__val[word], mask))
					goto set_maybe_and_return;
				if unlikely(!atomic_or_nopf(&um->pm_flags, USERPROCMASK_FLAG_HASPENDING))
					goto set_maybe_and_return;
				printk(KERN_DEBUG "[userprocmask:%p] Mark signal %d as pending "
				                  "[tid=%" PRIuN(__SIZEOF_PID_T__) "]\n",
				       um, signo, task_getroottid_of(self));
#else /* atomic_or_nopf */
				/* If the architecture doesn't support `atomic_cmpxch_nopf()',
				 * and  the signal hasn't been marked as pending, yet, then we
				 * must act like we weren't  able to figure out the  is-masked
				 * state  of the  thread, and have  our caller send  an RPC to
				 * the given thread `self' to do  all of this outside of  NOPF
				 * mode. */
				goto set_maybe_and_return;
#endif /* !atomic_or_nopf */
			}
		}
	}

done:
	/* Switch back to our own pagedir */
	if (mymm != threadmm)
		pagedir_set(mymm->mm_pagedir_p);
	return result;
}

/* Version of `sigmask_ismasked_in_userprocmask_nopf()'  that
 * always operates on the userprocmask of the current thread. */
PRIVATE NOBLOCK NOPREEMPT ATTR_PURE WUNUSED int
NOTHROW(FCALL sigmask_ismasked_in_my_userprocmask_nopf)(signo_t signo) {
	int result = SIGMASK_ISMASKED_NOPF_FAULT;
	USER CHECKED struct userprocmask *um;
	USER UNCHECKED sigset_t *current_sigmask;
	um = PERTASK_GET(this_userprocmask_address);

	/* Use memcpy_nopf() to read the thread's current signal mask pointer. */
	if (!read_nopf(&um->pm_sigmask, &current_sigmask))
		goto done;

	/* Verify that `current_sigmask' points into user-space. */
	if unlikely(!ADDR_ISUSER(current_sigmask))
		goto done;

	/* Now dereference `current_sigmask' at an appropriate location
	 * in relation to `signo' */
	{
		ulongptr_t user_sigmask_word;
		ulongptr_t word, mask;
		word = __sigset_word(signo);
		mask = __sigset_mask(signo);
		if (!read_nopf(&current_sigmask->__val[word], &user_sigmask_word))
			goto done;

		/* If we manage to get to this point, then we know that `user_sigmask_word'
		 * is  the correct mask value that we were after. - Use it now to determine
		 * the masking-state of `signo' in `self' */
		result = (user_sigmask_word & mask) != 0;

		if (result == SIGMASK_ISMASKED_NOPF_YES) {
			/* The signal _is_ being masked! */
			if unlikely(!read_nopf(&um->pm_pending.__val[word], &user_sigmask_word)) {
set_maybe_and_return:
				result = SIGMASK_ISMASKED_NOPF_FAULT;
				goto done;
			}
			if ((user_sigmask_word & mask) == 0) {
				/* The signal _is_ being masked, but isn't marked as  pending.
				 * As such, we then we still have to turn on the corresponding
				 * bit in `um->pm_pending'! */
#ifdef atomic_or_nopf
				if unlikely(!atomic_or_nopf(&um->pm_pending.__val[word], mask))
					goto set_maybe_and_return;
				if unlikely(!atomic_or_nopf(&um->pm_flags, USERPROCMASK_FLAG_HASPENDING))
					goto set_maybe_and_return;
				printk(KERN_DEBUG "[userprocmask:%p] Mark signal %d as pending "
				                  "[tid=%" PRIuN(__SIZEOF_PID_T__) "]\n",
				       um, signo, task_getroottid());
#else /* atomic_or_nopf */
				/* If the architecture doesn't support `atomic_cmpxch_nopf()',
				 * and  the signal hasn't been marked as pending, yet, then we
				 * must act like we weren't  able to figure out the  is-masked
				 * state  of the  thread, and have  our caller send  an RPC to
				 * the given thread `self' to do  all of this outside of  NOPF
				 * mode. */
				goto set_maybe_and_return;
#endif /* !atomic_or_nopf */
			}
		}
	}
done:
	return result;
}
#endif /* CONFIG_HAVE_USERPROCMASK */


/* Helper  function that can  be used to determine  the masking status for
 * an arbitrary signal within an  arbitrary thread. Not that  userprocmask
 * signals  can _ONLY_  be determined (at  all) when `self'  is running on
 * the same CPU as the calling thread. If this is not the case, and `self'
 * uses the  userprocmask mechanism,  then SIGMASK_ISMASKED_NOPF_FAULT  is
 * _always_ returned.
 * @param: allow_blocking_and_exception_when_self_is_THIS_TASK:
 *              Like the argument name says: When self == THIS_TASK,
 *              and this argument is true, then this call is allowed
 *              to block, as well as throw exceptions.
 * @return: * : One of `SIGMASK_ISMASKED_*' (see above) */
#ifdef CONFIG_HAVE_USERPROCMASK
PUBLIC NOBLOCK_IF(!allow_blocking_and_exception_when_self_is_THIS_TASK || self != THIS_TASK)
ATTR_PURE WUNUSED NONNULL((1)) int FCALL
sigmask_ismasked_in(struct task *__restrict self, signo_t signo,
                    bool allow_blocking_and_exception_when_self_is_THIS_TASK)
		THROWS(E_SEGFAULT)
#else /* CONFIG_HAVE_USERPROCMASK */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW(FCALL sigmask_ismasked_in)(struct task *__restrict self, signo_t signo)
#define sigmask_ismasked_in(self, signo, x) sigmask_ismasked_in(self, signo)
#endif /* !CONFIG_HAVE_USERPROCMASK */
{
	int result;
	REF struct kernel_sigmask *sm;
	uintptr_t thread_flags = ATOMIC_READ(self->t_flags);
#ifdef CONFIG_HAVE_USERPROCMASK
	if (thread_flags & (TASK_FVFORK | TASK_FUSERPROCMASK))
#else /* CONFIG_HAVE_USERPROCMASK */
	if (thread_flags & TASK_FVFORK)
#endif /* !CONFIG_HAVE_USERPROCMASK */
	{
		/* Special case for SIGKILL and  SIGSTOP, which are assumed  to
		 * always be unmasked, no matter what the thread's userprocmask
		 * may say. */
		if (signo == SIGKILL || signo == SIGSTOP)
			return SIGMASK_ISMASKED_NOPF_NO; /* Cannot be masked. */
		/* A vfork'd thread always has all signals masked. */
#ifndef CONFIG_HAVE_USERPROCMASK
		return SIGMASK_ISMASKED_NOPF_YES;
#else /* !CONFIG_HAVE_USERPROCMASK */
		if unlikely(thread_flags & TASK_FVFORK)
			return SIGMASK_ISMASKED_NOPF_YES;
		/* Special handling for when `self' is the caller. */
		if (self == THIS_TASK && allow_blocking_and_exception_when_self_is_THIS_TASK)
			return (int)usersigmask_ismasked_chk(signo);
		/* USERPROCMASK  would  have  a  soft-lock  scenario,  where a
		 * signal  sent to  a process  containing at  least 2 threads,
		 * with the first (in terms of checking-order when determining
		 * who should receive a posix signal send to the process as  a
		 * whole) 2 of those threads both using userprocmask.
		 *
		 *  [tid=1]: fork()  -> tid=2
		 *
		 *  [tid=2]: set_userprocmask_address(UM1)
		 *  [tid=2]: sigdelset(UM1->pm_sigmask, SIGUSR1)
		 *  [tid=2]: clone() -> tid=3
		 *
		 *  [tid=3]: set_userprocmask_address(UM2)
		 *  [tid=3]: sigdelset(UM2->pm_sigmask, SIGUSR1)
		 *
		 *  [tid=1]: kill(-2, SIGUSR1)
		 *
		 * That  last kill() call  will get here,  and notice that [tid=2]
		 * uses USERPROCMASK, but isn't equal to the sender, so the sender
		 * can't determine if the target thread is masking the signal.
		 *
		 * As such, it will assume that [tid=2] isn't masking it, and send
		 * an  RPC  `task_process_signal_rpc_handler'   to  that   thread.
		 *
		 * That RPC  will then  be able  to confirm  if the  signal is  masked
		 * for sure,  at  which  point  it will  notice  that  the  signal  is
		 * masked,  and try to forward the signal  to some other thread in its
		 * current process, using `deliver_signal_to_some_thread_in_process()'
		 *
		 * At that  point, `deliver_signal_to_some_thread_in_process()'  will
		 * once again check if [tid=2] is masking the signal, but can confirm
		 * that it is since at that point THIS_TASK==[tid=2], so it will send
		 * the signal to [tid=3]
		 *
		 * In  [tid=3],  the same  will happen,  but now  the signal  will get
		 * forwarded back to [tid=2], forming a soft-lock of 2 threads sending
		 * each other RPC for all of eternity.
		 *
		 * This problem can be reproduced via `playground sigbounce'
		 *
		 * Problem with the direct approach of just doing the check for a foreign thread:
		 *   - There needs to be a way for the kernel to read the USERPROCMASK of
		 *     a thread different than THIS_TASK. For this purpose, we'd need to:
		 *     - Ensure that `self' doesn't change `FORTASK(self, this_userprocmask_address)'
		 *       This is doable, since the  only way to change that  value is through use  of
		 *       the set_tid_address(2) or set_userprocmask_address(2)
		 *   - With this, we'd be able to safely do:
		 *     ATOMIC_READ(FORTASK(self,   this_userprocmask_address)->pm_sigmask)
		 *     Note though that since this is a user-space memory access, we  also
		 *     need  to deal  with VIO, meaning  that whatever is  used to prevent
		 *     the thread from changing `FORTASK(self, this_userprocmask_address)'
		 *     can't be an atomic lock.
		 *   - But how would we do that? Once we've read `pm_sigmask', nothing's stopping
		 *     the user-space side of `self' from setting a new signal mask, and  writing
		 *     unrelated garbage to the pointer we've read before.
		 *
		 * Solution:
		 *   - We  can do this test when `self' is running on the same CPU as we are,
		 *     at  which point we could do all  of the memory access via memcpy_nopf,
		 *     and only return is-masked if all of the reads were OK. Since this test
		 *     should work in most cases, then not accounting for one of the  threads
		 *     using  VIO for its  sigmask, we'd end up  with at most `cpu_count - 1'
		 *     threads for which we still won't know
		 *   - `sigmask_ismasked_in()' needs to return a tri-state boolean:
		 *         `true', `false', `maybe'
		 *     Where   `maybe'  means  that  the  is-masked  state  could  not  be  determined.
		 *     When this happens, and our caller is `deliver_signal_to_some_thread_in_process',
		 *     then they  must  gather  references  to  all  threads  for  which  this  happens
		 *     into  a  `pointer_set',  schedule  the   signal  within  the  process's   signal
		 *     queue,  and  send  a  `task_sigmask_check_rpc_handler'  RPC  to  each  of  them.
		 *     Since that  RPC won't  try to  forward  itself onto  other threads,  the  signal
		 *     forwarding  loop  will have  been  broken. (and  each  of the  process's threads
		 *     will have  marked the  signal as  pending within  their respective's  user-space
		 *     pending-signal-set)
		 */
		result = SIGMASK_ISMASKED_NOPF_FAULT;
		if (ATOMIC_READ(self->t_cpu) == THIS_CPU) {
			/* When `self' is running on the same CPU as we are, then we can
			 * try  to gain  insight into  their user-space  memory state by
			 * disabling preemption, temporarily switching page directories,
			 * and finally using memcpy_nopf() to access memory. */
			pflag_t was;
			was = PREEMPTION_PUSHOFF();
			/* Check again, how that our CPU won't change. */
			if likely(ATOMIC_READ(self->t_cpu) == THIS_CPU)
				result = sigmask_ismasked_in_userprocmask_nopf(self, signo);
			PREEMPTION_POP(was);
		}
		return result;
#endif /* CONFIG_HAVE_USERPROCMASK */
	}
	sm     = arref_get(&FORTASK(self, this_kernel_sigmask));
	result = (int)!!sigismember(&sm->sm_mask, signo);
	decref_unlikely(sm);
	if (result != SIGMASK_ISMASKED_NOPF_NO &&
	    unlikely(signo == SIGKILL || signo == SIGSTOP))
		result = SIGMASK_ISMASKED_NOPF_NO; /* Cannot be masked. */
	return result;
}

/* Same as `sigmask_ismasked_in()', but for the calling thread.
 * This function doesn't perform  any special checks for  VFORK
 * or  USERPROCMASK  scenarios.  Use  `sigmask_ismasked()'   if
 * these situations must also be handled. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL sigmask_ismasked_nospecial)(signo_t signo) {
	bool result;
	struct kernel_sigmask *sm;
	sm     = sigmask_kernel_getrd();
	result = sigismember(&sm->sm_mask, signo);
	return result;
}

/* Check if a given `signo' is currently masked. This function
 * handles all of the special cases, including TASK_VFORK  and
 * TASK_USERPROCMASK, as well as making sure that SIGSTOP  and
 * SIGKILL are never considered to be masked. */
#ifdef CONFIG_HAVE_USERPROCMASK
PUBLIC ATTR_PURE WUNUSED bool FCALL
sigmask_ismasked(signo_t signo) THROWS(E_SEGFAULT)
#else /* CONFIG_HAVE_USERPROCMASK */
PUBLIC NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL sigmask_ismasked)(signo_t signo)
#endif /* !CONFIG_HAVE_USERPROCMASK */
{
	bool result;
	uintptr_t thread_flags;
	thread_flags = PERTASK_GET(this_task.t_flags);
#ifdef CONFIG_HAVE_USERPROCMASK
	if (thread_flags & (TASK_FVFORK | TASK_FUSERPROCMASK))
#else /* CONFIG_HAVE_USERPROCMASK */
	if (thread_flags & TASK_FVFORK)
#endif /* !CONFIG_HAVE_USERPROCMASK */
	{
		/* Always behave as though this was `kernel_sigmask_full'. */
		if (signo == SIGKILL || signo == SIGSTOP)
			return false; /* Cannot be masked. */
		/* A vfork'd thread always has all signals masked. */
#ifndef CONFIG_HAVE_USERPROCMASK
		return true;
#else /* !CONFIG_HAVE_USERPROCMASK */
		if unlikely(thread_flags & TASK_FVFORK)
			return true;
		/* The nitty-gritty case: The thread is using a userprocmask... */
		result = usersigmask_ismasked_chk(signo);
		return result;
#endif /* CONFIG_HAVE_USERPROCMASK */
	}
	result = sigmask_ismasked_nospecial(signo);
	return result;
}


#ifdef CONFIG_HAVE_USERPROCMASK
/* Non-faulting version of `sigmask_ismasked()'.
 * @return: * : One of `SIGMASK_ISMASKED_NOPF_*' */
PUBLIC NOBLOCK ATTR_PURE WUNUSED int
NOTHROW(FCALL sigmask_ismasked_nopf)(signo_t signo) {
	uintptr_t thread_flags;
	thread_flags = PERTASK_GET(this_task.t_flags);
	if (thread_flags & (TASK_FVFORK | TASK_FUSERPROCMASK)) {
		if (signo == SIGKILL || signo == SIGSTOP)
			return SIGMASK_ISMASKED_NOPF_NO; /* Cannot be masked. */

		/* A vfork'd thread always has all signals masked. */
		if unlikely(thread_flags & TASK_FVFORK)
			return SIGMASK_ISMASKED_NOPF_YES;

		/* The nitty-gritty case: The thread is using a userprocmask... */
		return sigmask_ismasked_in_my_userprocmask_nopf(signo);
	}
	return sigmask_ismasked_nospecial(signo);
}
#endif /* CONFIG_HAVE_USERPROCMASK */



/* Return a pointer to the signal mask of the calling thread. */
#ifdef CONFIG_HAVE_USERPROCMASK
PUBLIC WUNUSED USER CHECKED sigset_t const *KCALL
sigmask_getrd(void) THROWS(E_SEGFAULT) {
	if (PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
		USER CHECKED sigset_t *result;
		result = ATOMIC_READ(PERTASK_GET(this_userprocmask_address)->pm_sigmask);
		validate_readable(result, sizeof(sigset_t));
		return result;
	}
	return &sigmask_kernel_getrd()->sm_mask;
}
#endif /* CONFIG_HAVE_USERPROCMASK */

/* Make sure that `this_kernel_sigmask' is allocated, and isn't being
 * shared.  Then,  always  return  `PERTASK_GET(this_kernel_sigmask)' */
PUBLIC ATTR_RETNONNULL WUNUSED struct kernel_sigmask *KCALL
sigmask_kernel_getwr(void) THROWS(E_BADALLOC) {
	struct kernel_sigmask *mymask;
	mymask = sigmask_kernel_getrd();
	if (ATOMIC_READ(mymask->sm_share) > 1) {
		/* Unshare. */
		struct kernel_sigmask *copy;
		struct kernel_sigmask_arref *maskref;
		copy = (struct kernel_sigmask *)kmalloc(sizeof(struct kernel_sigmask),
		                                        GFP_CALLOC);
		memcpy(&copy->sm_mask, &mymask->sm_mask, sizeof(copy->sm_mask));
		copy->sm_refcnt = 1;
		copy->sm_share  = 1;

		maskref = &PERTASK(this_kernel_sigmask);
		mymask  = arref_xch_inherit(maskref, copy);
		if (mymask != &kernel_sigmask_empty) {
			ATOMIC_DEC(mymask->sm_share);
			decref_unlikely(mymask);
		}
		mymask = copy;
	}
	assert(mymask != &kernel_sigmask_empty);
	return mymask;
}

#ifdef CONFIG_HAVE_USERPROCMASK
/* Make sure that `this_kernel_sigmask' is allocated, and isn't being shared.
 * Then, always return `PERTASK_GET(this_kernel_sigmask)'
 * NOTE: When  calling thread has  the `TASK_FUSERPROCMASK' flag set,
 *       then this function will return the address of the currently-
 *       assigned  user-space signal mask,  rather than its in-kernel
 *       counterpart! */
PUBLIC WUNUSED USER CHECKED sigset_t *KCALL
sigmask_getwr(void) THROWS(E_BADALLOC, E_SEGFAULT, ...) {
	USER CHECKED sigset_t *result;
	if (PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
		result = ATOMIC_READ(PERTASK_GET(this_userprocmask_address)->pm_sigmask);
		validate_readwrite(result, sizeof(sigset_t));
	} else {
		result = &sigmask_kernel_getwr()->sm_mask;
	}
	return result;
}
#endif /* CONFIG_HAVE_USERPROCMASK */



/************************************************************************/
/* SYSTEM CALLS                                                         */
/************************************************************************/

/************************************************************************/
/* sigprocmask(), rt_sigprocmask()                                      */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_RT_SIGPROCMASK
DEFINE_SYSCALL4(errno_t, rt_sigprocmask, syscall_ulong_t, how,
                UNCHECKED USER sigset_t const *, set,
                UNCHECKED USER sigset_t *, oset, size_t, sigsetsize) {
	if unlikely(sigsetsize != sizeof(sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	validate_readable_opt(set, sizeof(*set));
	validate_writable_opt(oset, sizeof(*oset));
	if (!set) {
		if (oset) {
			USER CHECKED sigset_t const *mymask;
			mymask = sigmask_getrd();
			memcpy(oset, mymask, sizeof(sigset_t));
		}
	} else {
		sigset_t newmask;
		USER CHECKED sigset_t *mymask;
		mymask = sigmask_getwr();
		if (oset)
			memcpy(oset, mymask, sizeof(sigset_t));
		memcpy(&newmask, set, sizeof(sigset_t));
		switch (how) {

		case SIG_BLOCK: {
			size_t i;

			/* Don't block these signals. Technically, this safety measure is
			 * only necessary when USERPROCMASK  is disabled, but it  doesn't
			 * hurt to do it unconditionally. */
			sigdelset(&newmask, SIGKILL);
			sigdelset(&newmask, SIGSTOP);

			/* Don't try to write to a userprocmask if it already contains the correct bits!
			 * This is required since a userprocmask may be read-only if the user knows that
			 * certain signals will never be marked as masked. */
#ifdef CONFIG_HAVE_USERPROCMASK
			for (i = 0; i < COMPILER_LENOF(mymask->__val); ++i) {
				ulongptr_t oldword, newword;
				oldword = mymask->__val[i];
				newword = oldword | newmask.__val[i];
				if (oldword != newword)
					mymask->__val[i] = newword;
			}
#else /* CONFIG_HAVE_USERPROCMASK */
			sigorset(mymask, mymask, &newmask);
#endif /* !CONFIG_HAVE_USERPROCMASK */
		}	break;

		case SIG_UNBLOCK: {
			size_t i;
			bool did_unmask = false;

			/* Don't  modify the state of these signals. Technically, this is only
			 * necessary  when USERPROCMASK is  enabled, in which  case we have to
			 * do our best to make as few modifications to their mask as possible,
			 * thus  improving the chances that no writes  are done at all in case
			 * the mask is read-only. */
#ifdef CONFIG_HAVE_USERPROCMASK
			sigdelset(&newmask, SIGKILL);
			sigdelset(&newmask, SIGSTOP);
#endif /* CONFIG_HAVE_USERPROCMASK */

			/* No need to check for  mandatory masks being clear,  since
			 * this command is only able to clear masks from the get-go. */
			for (i = 0; i < COMPILER_LENOF(mymask->__val); ++i) {
				ulongptr_t oldword, newword;
				oldword = mymask->__val[i];
				newword = oldword & ~newmask.__val[i];
				if (oldword != newword) {
					mymask->__val[i] = newword;
					did_unmask       = true;
				}
			}
			if (did_unmask) {
				/* Check for pending  signals now that  the
				 * mask (may have) gotten less restrictive. */
				userexcept_sysret_inject_self();
			}
		}	break;

		case SIG_SETMASK: {
			size_t i;
			bool did_unmask = false;

			/* Don't allow masking of these signals! */
			sigdelset(&newmask, SIGKILL);
			sigdelset(&newmask, SIGSTOP);

			/* When the userprocmask is enabled,  retain
			 * the old state of mandatory signals. Their
			 * state  doesn't actually matter, but if we
			 * retain  it, we may improve the chances of
			 * not having to do any modifications. */
#ifdef CONFIG_HAVE_USERPROCMASK
			if (PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
				if (sigismember(mymask, SIGKILL))
					sigaddset(&newmask, SIGKILL);
				if (sigismember(mymask, SIGSTOP))
					sigaddset(&newmask, SIGSTOP);
			}
#endif /* CONFIG_HAVE_USERPROCMASK */

			/* Modify the signal mask, but only write to fields
			 * that actually changed (needed to be done for the
			 * sake of userprocmask support) */
			for (i = 0; i < COMPILER_LENOF(mymask->__val); ++i) {
				ulongptr_t oldword, newword;
				oldword = mymask->__val[i];
				newword = newmask.__val[i];
				if (oldword != newword) {
					mymask->__val[i] = newword;
					if ((oldword & ~newword) != 0)
						did_unmask = true; /* some signal just became unmasked! */
				}
			}

			/* If some signal became unmasked, check for pending signals. */
			if (did_unmask) {
				/* Check for pending  signals now that  the
				 * mask (may have) gotten less restrictive. */
				userexcept_sysret_inject_self();
			}
		}	break;

		default:
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_SIGPROCMASK_HOW,
			      how);
		}
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGPROCMASK */

#ifdef __ARCH_WANT_SYSCALL_SIGPROCMASK
DEFINE_SYSCALL3(errno_t, sigprocmask, syscall_ulong_t, how,
                UNCHECKED USER sigset_t const *, set,
                UNCHECKED USER sigset_t *, oset) {
	return sys_rt_sigprocmask(how, set, oset, sizeof(sigset_t));
}
#endif /* __ARCH_WANT_SYSCALL_SIGPROCMASK */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGPROCMASK
DEFINE_COMPAT_SYSCALL3(errno_t, sigprocmask, syscall_ulong_t, how,
                       UNCHECKED USER compat_sigset_t const *, set,
                       UNCHECKED USER compat_sigset_t *, oset) {
	return sys_rt_sigprocmask(how, set, oset, sizeof(compat_sigset_t));
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGPROCMASK */





/************************************************************************/
/* sgetmask(), ssetmask()                                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SGETMASK
DEFINE_SYSCALL0(syscall_ulong_t, sgetmask) {
	syscall_ulong_t result;
	USER CHECKED sigset_t const *mymask;
	mymask = sigmask_getrd();
#if __SIZEOF_SIGSET_T__ < __SIZEOF_SYSCALL_LONG_T__
	result = 0;
#endif /* __SIZEOF_SIGSET_T__ < __SIZEOF_SYSCALL_LONG_T__ */
	memcpy(&result, mymask, MIN_C(sizeof(sigset_t), sizeof(result)));
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_SGETMASK */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SGETMASK
DEFINE_COMPAT_SYSCALL0(syscall_ulong_t, sgetmask) {
	compat_syscall_ulong_t result;
	USER CHECKED sigset_t const *mymask;
	mymask = sigmask_getrd();
#if __SIZEOF_SIGSET_T__ < __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
	result = 0;
#endif /* __SIZEOF_SIGSET_T__ < __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T */
	memcpy(&result, mymask, MIN_C(sizeof(sigset_t), sizeof(result)));
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SGETMASK */

#ifdef __ARCH_WANT_SYSCALL_SSETMASK
DEFINE_SYSCALL1(syscall_ulong_t, ssetmask, syscall_ulong_t, new_sigmask) {
	syscall_ulong_t result;
	sigset_t *mymask;
	mymask = sigmask_getwr();
#if __SIZEOF_SIGSET_T__ < __SIZEOF_SYSCALL_LONG_T__
	result = 0;
#endif /* __SIZEOF_SIGSET_T__ < __SIZEOF_SYSCALL_LONG_T__ */
	memcpy(&result, mymask, MIN_C(sizeof(sigset_t), sizeof(result)));
	memcpy(mymask, &new_sigmask, MIN_C(sizeof(sigset_t), sizeof(new_sigmask)));
#if __SIZEOF_SIGSET_T__ > __SIZEOF_SYSCALL_LONG_T__
	bzero((byte_t *)mymask + sizeof(new_sigmask),
	      sizeof(sigset_t) - sizeof(new_sigmask));
#endif /* __SIZEOF_SIGSET_T__ > __SIZEOF_SYSCALL_LONG_T__ */
	/* Make sure that these two signals aren't being masked! */
	sigdelset(mymask, SIGKILL);
	sigdelset(mymask, SIGSTOP);
	userexcept_sysret_inject_self();
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_SSETMASK */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SSETMASK
DEFINE_COMPAT_SYSCALL1(syscall_ulong_t, ssetmask, syscall_ulong_t, new_sigmask) {
	compat_syscall_ulong_t result;
	compat_syscall_ulong_t used_sigmask;
	USER CHECKED sigset_t *mymask;
	mymask = sigmask_getwr();
	used_sigmask = (compat_syscall_ulong_t)new_sigmask;
#if __SIZEOF_SIGSET_T__ < __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
	result = 0;
#endif /* __SIZEOF_SIGSET_T__ < __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T */
	memcpy(&result, mymask, MIN_C(sizeof(sigset_t), sizeof(result)));
	memcpy(mymask, &used_sigmask, MIN_C(sizeof(sigset_t), sizeof(used_sigmask)));
#if __SIZEOF_SIGSET_T__ > __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
	bzero((byte_t *)mymask+ sizeof(used_sigmask),
	      sizeof(sigset_t) - sizeof(used_sigmask));
#endif /* __SIZEOF_SIGSET_T__ > __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T */
	/* Make sure that these two signals aren't being masked! */
	sigdelset(mymask, SIGKILL);
	sigdelset(mymask, SIGSTOP);
	userexcept_sysret_inject_self();
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SSETMASK */







/************************************************************************/
/* rt_sigpending(), sigpending()                                        */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_RT_SIGPENDING
DEFINE_SYSCALL2(errno_t, rt_sigpending,
                UNCHECKED USER sigset_t *, uset,
                size_t, sigsetsize) {
	sigset_t pending;
	/* Validate the user-space signal set pointer. */
	if unlikely(sigsetsize != sizeof(sigset_t)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	}
	validate_writable(uset, sizeof(sigset_t));
	sigemptyset(&pending);

	/* Collect pending signals */
	task_rpc_pending_sigset(&pending);
	proc_rpc_pending_sigset(&pending);

	/* Write back results */
	COMPILER_WRITE_BARRIER();
	memcpy(uset, &pending, sizeof(pending));
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGPENDING */

#ifdef __ARCH_WANT_SYSCALL_SIGPENDING
DEFINE_SYSCALL1(errno_t, sigpending,
                UNCHECKED USER sigset_t *, uset) {
	return sys_rt_sigpending(uset, sizeof(sigset_t));
}
#endif /* __ARCH_WANT_SYSCALL_SIGPENDING */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGPENDING
DEFINE_COMPAT_SYSCALL1(errno_t, sigpending,
                       UNCHECKED USER compat_sigset_t *, uset) {
	return sys_rt_sigpending(uset, sizeof(compat_sigset_t));
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGPENDING */



DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_SIGMASK_C */
