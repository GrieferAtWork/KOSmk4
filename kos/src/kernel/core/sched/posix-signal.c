/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_SCHED_POSIX_SIGNAL_C
#define GUARD_KERNEL_SRC_SCHED_POSIX_SIGNAL_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/hook.h> /* DEFINE_DBG_BZERO_OBJECT */
#include <kernel/coredump.h>
#include <kernel/except.h>
#include <kernel/mman.h>
#include <kernel/mman/event.h> /* DEFINE_PERMMAN_ONEXEC() */
#include <kernel/mman/nopf.h>
#include <kernel/paging.h> /* KERNELSPACE_HIGHMEM */
#include <kernel/printk.h>
#include <kernel/rt/except-handler.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <compat/config.h>
#include <kos/except/reason/inval.h>
#include <sys/param.h>
#include <sys/wait.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <sched.h>
#include <signal.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/sigaction.h>
#include <compat/bits/os/siginfo-convert.h>
#include <compat/bits/os/siginfo.h>
#include <compat/bits/os/timespec.h>
#include <compat/kos/types.h>
#include <compat/pointer.h>
#include <compat/signal.h>
#endif /* __ARCH_HAVE_COMPAT */

/* Need pointer sets for gathering targets of
 * process-group-wide   signal    broadcasts. */
#define POINTER_SET_BUFSIZE 16
#include <misc/pointer-set.h>

DECL_BEGIN

STATIC_ASSERT_MSG(NSIG - 1 <= 0xff,
                  "This is an ABI requirement imposed by:\n"
                  " - clone(2)\n"
                  " - RPC_SIGNO_MASK\n"
                  " - RPC_OP_sigblock");


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



/* [0..1][lock(READ(ATOMIC), WRITE(THIS_TASK))]
 * Reference to the signal mask (set of signals being blocked) in the  current
 * thread. The pointed-to object is meaningless (but must still be valid) when
 * the associated thread make use of userprocmask.
 *
 * NOTE: Only ever NULL for kernel-space threads! */
PUBLIC ATTR_PERTASK struct kernel_sigmask_arref
this_kernel_sigmask = ARREF_INIT(&kernel_sigmask_empty);


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
				       um, signo, task_getroottid_of_s(self));
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
				       um, signo, task_getroottid_s());
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
		/* Always behave as though this was `kernel_sigmask_full'. */
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




/* [0..1][valid_if(!TASK_FKERNTHREAD)][lock(PRIVATE(THIS_TASK))]
 * User-space  signal   handlers   for   the   calling   thread. */
PUBLIC ATTR_PERTASK REF struct sighand_ptr *this_sighand_ptr = NULL;

/* Lock for accessing any remote thread's this_sighand_ptr field */
#ifndef CONFIG_NO_SMP
PRIVATE struct atomic_lock sighand_ptr_change_lock = ATOMIC_LOCK_INIT;
#define sighand_ptr_change_lock_acquire_nopr() atomic_lock_acquire_nopr(&sighand_ptr_change_lock)
#define sighand_ptr_change_lock_release_nopr() atomic_lock_release(&sighand_ptr_change_lock)
#else /* !CONFIG_NO_SMP */
#define sighand_ptr_change_lock_acquire_nopr() (void)0
#define sighand_ptr_change_lock_release_nopr() (void)0
#endif /* CONFIG_NO_SMP */

/* Return the sighand pointer of the given thread. */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) REF struct sighand_ptr *
NOTHROW(FCALL task_getsighand_ptr)(struct task *__restrict thread) {
	pflag_t was;
	REF struct sighand_ptr *result;
	was = PREEMPTION_PUSHOFF();
	sighand_ptr_change_lock_acquire_nopr();
	assert(FORTASK(thread, this_sighand_ptr));
	result = xincref(FORTASK(thread, this_sighand_ptr));
	sighand_ptr_change_lock_release_nopr();
	PREEMPTION_POP(was);
	return result;
}

/* Exchange the sighand pointer of the calling thread. */
PUBLIC WUNUSED REF struct sighand_ptr *
NOTHROW(FCALL task_setsighand_ptr)(struct sighand_ptr *newsighand_ptr) {
	pflag_t was;
	REF struct sighand_ptr *result;
	was = PREEMPTION_PUSHOFF();
	sighand_ptr_change_lock_acquire_nopr();
	result = PERTASK_GET(this_sighand_ptr);
	xincref(newsighand_ptr);
	PERTASK_SET(this_sighand_ptr, newsighand_ptr);
	sighand_ptr_change_lock_release_nopr();
	PREEMPTION_POP(was);
	return result;
}



DEFINE_PERTASK_CLONE(clone_posix_signals);
PRIVATE ATTR_USED void KCALL
clone_posix_signals(struct task *__restrict new_thread, uintptr_t flags) {
	/* Clone the current signal mask. */
#ifdef CONFIG_HAVE_USERPROCMASK
	if (PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
		struct userprocmask *um;
		um = PERTASK_GET(this_userprocmask_address);
		if (!(flags & CLONE_VM)) {
			/* Special case:
			 * ```
			 *  During a call to fork() or clone() (w/o CLONE_VM), the parent thread's
			 *  TASK_FUSERPROCMASK    attribute    is    inherited    unconditionally.
			 * ```
			 */
inherit_parent_userprocmask:
			FORTASK(new_thread, this_userprocmask_address) = um;
			new_thread->t_flags |= TASK_FUSERPROCMASK;
			/* The static initialization for the kernel-space `this_kernel_sigmask' is sufficient in this case! */
			/*FORTASK(new_thread, this_kernel_sigmask) = ARREF_INIT(&kernel_sigmask_empty);*/
		} else if (flags & CLONE_VFORK) {
			/* Special case:
			 * ```
			 *  During a vfork(2), where the parent thread has the TASK_FUSERPROCMASK
			 *  attribute set [...]
			 *  The  child  thread is  started  with the  `TASK_FUSERPROCMASK'  attribute set,
			 *  which will be cleared the normal way once the child performs a successful call
			 *  to either exec(2) or  _Exit(2), at which pointer  the process will once  again
			 *  wake up.
			 * ```
			 */
			goto inherit_parent_userprocmask;
		} else {
			/* Special case:
			 * ```
			 *  During a call to clone(CLONE_VM), where the parent is a userprocmask  thread,
			 *  prior to clone() returning in either the parent or child, the parent thread's
			 *  user-space `pm_sigmask' is copied into  the kernel-space buffer of the  child
			 *  thread, while the child thread will start with TASK_FUSERPROCMASK=0.
			 * ```
			 *
			 * In other words: We must copy `um->pm_sigmask' into `FORTASK(new_thread, this_kernel_sigmask)'
			 */
			struct kernel_sigmask *new_thread_mask;
			new_thread_mask = (struct kernel_sigmask *)kmalloc(sizeof(struct kernel_sigmask),
			                                                   GFP_NORMAL);
			TRY {
				USER UNCHECKED sigset_t *parent_umask;
				parent_umask = ATOMIC_READ(um->pm_sigmask);
				validate_readable(parent_umask, sizeof(sigset_t));
				memcpy(&new_thread_mask->sm_mask,
				       parent_umask,
				       sizeof(sigset_t));
			} EXCEPT {
				kfree(new_thread_mask);
				RETHROW();
			}
			new_thread_mask->sm_refcnt = 1;
			new_thread_mask->sm_share  = 1;
			/* Initialize the new  thread's signal mask  with
			 * the copy of the parent's current userprocmask. */
			arref_init(&FORTASK(new_thread, this_kernel_sigmask), new_thread_mask);
		}
	} else
#endif /* CONFIG_HAVE_USERPROCMASK */
	{
		if (sigmask_kernel_getrd() == &kernel_sigmask_empty) {
			/* Nothing to do here! */
		} else {
			REF struct kernel_sigmask *mask;
			struct kernel_sigmask_arref *maskref;
			maskref = &PERTASK(this_kernel_sigmask);
			mask    = arref_get(maskref);
			assert(mask != &kernel_sigmask_empty);
			ATOMIC_INC(mask->sm_share);
			COMPILER_WRITE_BARRIER();
			arref_init(&FORTASK(new_thread, this_kernel_sigmask), mask); /* Inherit reference. */
			COMPILER_WRITE_BARRIER();
		}
	}
	if (flags & CLONE_SIGHAND) {
		/* Must share signal handlers. */
		REF struct sighand_ptr *myptr;
		myptr = PERTASK_GET(this_sighand_ptr);
		if (!myptr) {
			/* Must allocate the signal handler table pointer so we can share it! */
			myptr = (REF struct sighand_ptr *)kmalloc(sizeof(struct sighand_ptr),
			                                          GFP_NORMAL);
			myptr->sp_refcnt = 2;
			atomic_rwlock_init(&myptr->sp_lock);
			myptr->sp_hand = NULL;
			assert(!PERTASK_TEST(this_sighand_ptr));
			PERTASK_SET(this_sighand_ptr, myptr);
		} else {
			incref(myptr);
		}
		FORTASK(new_thread, this_sighand_ptr) = myptr;
	} else {
		/* Set signal handlers of the thread as a copy of the caller. */
		struct sighand_ptr *myptr;
		myptr = PERTASK_GET(this_sighand_ptr);
		if (!myptr) {
			/* No handlers -> Nothing to copy (the new thread will also use default handlers!) */
		} else {
			REF struct sighand_ptr *newptr;
			struct sighand *myhand;
			newptr = (REF struct sighand_ptr *)kmalloc(sizeof(struct sighand_ptr),
			                                           GFP_NORMAL);
again_lock_myptr:
			TRY {
				sync_read(myptr);
				COMPILER_READ_BARRIER();
				myhand = myptr->sp_hand;
				COMPILER_READ_BARRIER();
				if (!myhand) {
					/* No handlers -> Nothing to copy (the new thread will also use default handlers!) */
					sync_endread(myptr);
					kfree(newptr);
					newptr = NULL;
				} else {
					if (!sync_trywrite(myhand)) {
						sync_endread(myptr);
						task_yield();
						goto again_lock_myptr;
					}
					sync_endread(myptr);
					sighand_incshare(myhand);
					sync_endwrite(myhand);

					/* Still share the handler table as copy-on-write. */
					atomic_rwlock_init(&newptr->sp_lock);
					newptr->sp_refcnt = 1;
					newptr->sp_hand = myhand;
				}
			} EXCEPT {
				kfree(newptr);
				RETHROW();
			}
			FORTASK(new_thread, this_sighand_ptr) = newptr;
		}
	}
}


DEFINE_PERTASK_FINI(fini_posix_signals);
PRIVATE NOBLOCK ATTR_USED void
NOTHROW(KCALL fini_posix_signals)(struct task *__restrict thread) {
	struct kernel_sigmask *mask;
	mask = arref_ptr(&FORTASK(thread, this_kernel_sigmask));
	if (mask != &kernel_sigmask_empty)
		decref(mask);
	xdecref(FORTASK(thread, this_sighand_ptr));
}



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



PUBLIC NOBLOCK void
NOTHROW(KCALL sighand_destroy)(struct sighand *__restrict self) {
	unsigned int i;
	for (i = 0; i < NSIG - 1; ++i)
		xdecref(self->sh_actions[i].sa_mask);
	kfree(self);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL sighand_ptr_destroy)(struct sighand_ptr *__restrict self) {
	if (self->sp_hand)
		sighand_decshare(self->sp_hand);
	kfree(self);
}




/* Acquire a lock to the underlying signal handler table that is associated
 * with the  given  `sighand_ptr',  either for  reading,  or  for  writing.
 * For reading:
 * >> struct sighand *h;
 * >> h = sighand_ptr_lockread(THIS_SIGHAND_PTR);
 * >> ...
 * >> sync_endread(h);
 * For writing:
 * >> h = sighand_ptr_lockwrite();
 * >> ...
 * >> sync_endwrite(h);
 * With that in mind, these function will perform the necessary unsharing  of
 * copy-on-write signal handler  tables, while still  keeping association  of
 * handlers in check when it comes to shared handler tables, as usually found
 * within the same process. */
PUBLIC WUNUSED NONNULL((1)) struct sighand *KCALL
sighand_ptr_lockread(struct sighand_ptr *__restrict ptr)
		THROWS(E_WOULDBLOCK) {
	struct sighand *result;
	bool lock_ok;
again:
	sync_read(&ptr->sp_lock);
	COMPILER_READ_BARRIER();
	result = ptr->sp_hand;
	COMPILER_READ_BARRIER();
	lock_ok = !result ? true : sync_tryread(result);
	sync_endread(&ptr->sp_lock);
	if (!lock_ok) {
		task_yield();
		goto again;
	}
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED struct sighand *KCALL
sighand_ptr_lockwrite(void) THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct sighand *result;
	struct sighand_ptr *ptr;
	bool lock_ok;
again_read_thread_ptr:
	ptr = THIS_SIGHAND_PTR;
	if (!ptr) {
		/* No handlers allocated (yet).  - Allocate it now  as an empty handler  table.
		 * NOTE: this can easily be done by zero-initializing the signal handler table. */
		result = (struct sighand *)kmalloc(sizeof(struct sighand), GFP_CALLOC);
		TRY {
			ptr = (struct sighand_ptr *)kmalloc(sizeof(struct sighand_ptr), GFP_NORMAL);
		} EXCEPT {
			kfree(result);
			RETHROW();
		}
		ptr->sp_hand = result;
		atomic_rwlock_cinit_write(&result->sh_lock);
		result->sh_share = 1;
		ptr->sp_refcnt = 1;
		atomic_rwlock_init(&ptr->sp_lock);
		if (!ATOMIC_CMPXCH(PERTASK(this_sighand_ptr), NULL, ptr)) {
			COMPILER_READ_BARRIER();
			/* Race condition: someone else already allocated the sighand_ptr for `thread' */
			kfree(result);
			kfree(ptr);
			goto again_read_thread_ptr;
		}
		return result;
	}
again_lock_ptr:
	sync_read(ptr);
	COMPILER_READ_BARRIER();
	result = ptr->sp_hand;
	COMPILER_READ_BARRIER();
	if (!result) {
		sync_endread(ptr);
		/* Lazily allocate the signal handler table. */
		result = (struct sighand *)kmalloc(sizeof(struct sighand), GFP_CALLOC);
		atomic_rwlock_cinit_write(&result->sh_lock); /* Init in write-mode */
		result->sh_share = 1;
		TRY {
			sync_write(ptr);
		} EXCEPT {
			kfree(result);
			RETHROW();
		}
		COMPILER_BARRIER();
		if likely(!ptr->sp_hand) {
			ptr->sp_hand = result;
			sync_endwrite(ptr);
			return result;
		}
		/* Race condition: another thread also allocated the handler table in the mean time! */
		sync_endwrite(ptr);
		kfree(result);
		goto again_lock_ptr;
	}
	/* Got the handler table! - Now to lock it. */
	lock_ok = sync_trywrite(result);
	sync_endread(ptr);
	if (!lock_ok) {
		task_yield();
		goto again_lock_ptr;
	}
	/* At  this point we have a write-lock to the handler table.
	 * Now we must verify that the table isn't being shared, and
	 * if it is being shared, we must unshare it and replace  it
	 * with a copy. */
	if (ATOMIC_READ(result->sh_share) > 1) {
		struct sighand *copy;
		sync_endwrite(result);
		copy = (struct sighand *)kmalloc(sizeof(struct sighand), GFP_NORMAL);
		TRY {
			unsigned int i;
again_lock_ptr_for_copy:
			sync_write(ptr);
			COMPILER_READ_BARRIER();
			result = ptr->sp_hand;
			COMPILER_READ_BARRIER();
			if (!sync_tryread(result)) {
				sync_endwrite(ptr);
				task_yield();
				goto again_lock_ptr_for_copy;
			}
			if unlikely(ATOMIC_READ(result->sh_share) <= 1) {
				/* The handler table already got unshared in the mean time...
				 * No need to initialize + save our copy! */
				sync_endwrite(ptr);
				if (!sync_tryupgrade(result)) {
					sync_endread(result);
					kfree(copy);
					task_yield();
					goto again_lock_ptr;
				}
				kfree(copy);
				return result;
			}
			/* Initialize the new copy as a duplicate of the old handler table. */
			memcpy(copy->sh_actions,
			       result->sh_actions,
			       sizeof(result->sh_actions));
			/* Load references to signal masks. */
			for (i = 0; i < NSIG - 1; ++i)
				xincref(copy->sh_actions[i].sa_mask);
			sync_endread(result);
			copy->sh_share = 1; /* Only 1 sighand_ptr will use this copy (for now) */
			atomic_rwlock_init_write(&copy->sh_lock);
			/* Store the copy in the thread-local sighand_ptr */
			COMPILER_WRITE_BARRIER();
			ptr->sp_hand = copy;
			COMPILER_WRITE_BARRIER();
			sync_endwrite(ptr);
		} EXCEPT {
			kfree(copy);
			RETHROW();
		}
		/* NOTE: At this point we're still holding a write-lock to `copy',
		 *       which we're eventually going to propagate to the  caller. */
		/* Drop the share reference from the old handler table. */
		sighand_decshare(result);
		/* Return newly constructed copy of the handler table. */
		result = copy;
	}
	return result;
}


/* Return the default action to perform when faced with `signo' configured as `SIG_DFL'
 * @return: * : One of `SIG_*' (excluding `SIG_DFL' and `SIG_GET') */
PUBLIC NOBLOCK WUNUSED ATTR_CONST user_sighandler_func_t
NOTHROW(KCALL sighand_default_action)(signo_t signo) {
	user_sighandler_func_t result;
	result = SIG_IGN;
	switch (signo) {

	case SIGQUIT:
	case SIGILL:
	case SIGABRT:
	case SIGFPE:
	case SIGSEGV:
	case SIGBUS:
	case SIGSYS:
	case SIGTRAP:
	case SIGXCPU:
	case SIGXFSZ:
#if defined(SIGIOT) && SIGIOT != SIGABRT
	case SIGIOT:
#endif /* SIGIOT != SIGABRT */
#if defined(SIGUNUSED) && SIGUNUSED != SIGSYS
	case SIGUNUSED:
#endif /* SIGUNUSED != SIGSYS */
		result = SIG_CORE;
		break;

	case SIGHUP:
	case SIGINT:
	case SIGKILL:
	case SIGPIPE:
	case SIGALRM:
	case SIGTERM:
	case SIGUSR1:
	case SIGUSR2:
	case SIGPOLL:
	case SIGPROF:
	case SIGVTALRM:
#ifdef SIGEMT
	case SIGEMT:
#endif /* SIGEMT */
	case SIGSTKFLT:
#if defined(SIGIO) && SIGIO != SIGPOLL
	case SIGIO:
#endif /* SIGIO != SIGPOLL */
	case SIGPWR:
#ifdef SIGLOST
	case SIGLOST:
#endif /* SIGLOST */
		result = SIG_TERM;
		break;

	case SIGCONT:
		result = SIG_CONT;
		break;

	case SIGSTOP:
	case SIGTSTP:
	case SIGTTIN:
	case SIGTTOU:
		result = SIG_STOP;
		break;

	default: break;
	}
	return result;
}



/* Reset  the current handler for `signo' when  `current_action' matches the currently set action.
 * This function should be called by kernel-space signal delivery implementations to implement the
 * behavior of `SA_RESETHAND' when handling a signal.
 * @return: true:  Successfully reset the handler
 * @return: false: The given `current_action' didn't match the currently set action. */
PUBLIC bool KCALL
sighand_reset_handler(signo_t signo,
                      struct kernel_sigaction const *__restrict current_action)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct sighand *hand;
	assert(signo != 0);
	assert(signo < NSIG);
	if unlikely(!THIS_SIGHAND_PTR)
		return false;
	hand = sighand_ptr_lockwrite();
	if (memcmp(current_action,
	           &hand->sh_actions[signo - 1],
	           sizeof(struct kernel_sigaction)) != 0) {
		sync_endwrite(hand);
		return false;
	}
	/* Reset the action. */
	memset(&hand->sh_actions[signo - 1], 0,
	       sizeof(struct kernel_sigaction));
	sync_endwrite(hand);
	/* Drop the reference held by the `sh_actions' vector.
	 * Note however that since the caller must have copied that action at one point,
	 * they  must currently  be holding a  reference to its  `sa_mask', meaning that
	 * decref-ing that field mustn't be able to destroy the mask object! */
	xdecref_nokill(current_action->sa_mask);
	return true;
}



/* Check  if  `self' contains  any handlers  set to
 * SIG_IGN that wouldn't be set as such by default. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL sighand_has_nondefault_sig_ign)(struct sighand const *__restrict self) {
	unsigned int i;
	for (i = 0; i < NSIG - 1; ++i) {
		/* Check if the handler's action is SIG_IGN */
		if (self->sh_actions[i].sa_handler != SIG_IGN)
			continue; /* Something other than SIG_IGN */
		/* Check if the default action is something other than SIG_IGN */
		if (sighand_default_action(i + 1) == SIG_IGN)
			continue; /* Default would also be SIG_IGN */
		/* Found one! */
		return true;
	}
	return false;
}


/* During exec(), all signal handler dispositions of the calling thread are reset */
DEFINE_PERMMAN_ONEXEC(onexec_posix_signals_reset_action);
INTERN void KCALL onexec_posix_signals_reset_action(void) {
	REF struct sighand_ptr *handptr;
	/* Posix says that signals set to SIG_IGN should remain SIG_IGN after exec(). */
	handptr = ATOMIC_XCH(PERTASK(this_sighand_ptr), NULL);
	if (handptr) {
		struct sighand *hand;
		REF struct sighand *newhand;
		unsigned int i;
		hand = sighand_ptr_lockread(handptr);
		if unlikely(!hand)
			goto done_handptr;
		/* Check if there are any signals set to SIG_IGN, for which
		 * `sighand_default_action()'   returns   something   else. */
		if (!sighand_has_nondefault_sig_ign(hand)) {
			sync_endread(hand);
			goto done_handptr;
		}
		/* We have to create a new, custom set of signal handlers... */
		/* NOTE: Use GFP_CALLOC  because  `SIG_DFL = 0',  and  we  only
		 *       need to inherit handlers that were marked as `SIG_IGN' */
		newhand = (REF struct sighand *)kmalloc_nx(sizeof(struct sighand),
		                                           GFP_CALLOC | GFP_ATOMIC);
		if (!newhand) {
			sync_endread(hand);
			newhand = (REF struct sighand *)kmalloc(sizeof(struct sighand), GFP_CALLOC);
			TRY {
				hand = sighand_ptr_lockread(handptr);
			} EXCEPT {
				kfree(newhand);
				assert(!PERTASK_TEST(this_sighand_ptr));
				PERTASK_SET(this_sighand_ptr, handptr);
				RETHROW();
			}
			if unlikely(!hand) {
				kfree(newhand);
				goto done_handptr;
			}
			if (sighand_has_nondefault_sig_ign(hand)) {
				sync_endread(hand);
				kfree(newhand);
				goto done_handptr;
			}
		}
		/* Copy handlers that have their disposition set to SIG_IGN.
		 * However,  don't copy anything  else about those handlers,
		 * or any other handlers for that matter.
		 * Especially of note is that we also don't copy signal masks,
		 * since  those wouldn't actually matter for SIG_IGN handlers. */
		for (i = 0; i < NSIG - 1; ++i) {
			if (hand->sh_actions[i].sa_handler == SIG_IGN)
				newhand->sh_actions[i].sa_handler = SIG_IGN;
		}
		atomic_rwlock_cinit(&newhand->sh_lock);
		newhand->sh_share = 1;
		sync_endread(hand);
		if (!isshared(handptr)) {
			/* We can re-use `handptr' to point to `newhand' */
			TRY {
				/* This really shouldn't block since handptr isn't shared.
				 * ... But better to be safe than sorry. */
				sync_write(&handptr->sp_lock);
			} EXCEPT {
				kfree(newhand);
				decref(handptr);
				assert(!PERTASK_TEST(this_sighand_ptr));
				PERTASK_SET(this_sighand_ptr, handptr);
				RETHROW();
			}
			assert(!isshared(handptr));
			hand = handptr->sp_hand;    /* Inherit reference */
			handptr->sp_hand = newhand; /* Inherit reference */
			sync_endwrite(&handptr->sp_lock);
			/* Restore the old hand-pointer for the calling thread. */
			assert(!PERTASK_TEST(this_sighand_ptr));
			PERTASK_SET(this_sighand_ptr, handptr);
			/* Now that we're  using `newhand',  drop
			 * our shared reference from the original */
			sighand_decshare(hand);
		} else {
			/* Must allocate a new `handptr' */
			REF struct sighand_ptr *newhandptr;
			TRY {
				newhandptr = (REF struct sighand_ptr *)kmalloc(sizeof(struct sighand_ptr),
				                                               GFP_NORMAL);
			} EXCEPT {
				kfree(newhand);
				decref(handptr);
				assert(!PERTASK_TEST(this_sighand_ptr));
				PERTASK_SET(this_sighand_ptr, handptr);
				RETHROW();
			}
			newhandptr->sp_refcnt = 1;
			atomic_rwlock_init(&newhandptr->sp_lock);
			newhandptr->sp_hand = newhand; /* Inherit reference */
			assert(!PERTASK_TEST(this_sighand_ptr));
			PERTASK_SET(this_sighand_ptr, newhandptr); /* Inherit reference */
done_handptr:
			decref(handptr);
		}
	}
}



/* Decref every task-object from `self'. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL taskref_pointer_set_decref_all)(struct pointer_set *__restrict self) {
	REF struct task *thread;
	POINTER_SET_FOREACH(thread, self) {
		/* Arguably a  `decref_likely()', but  only if  the
		 * total # of threads in the set is extremely high,
		 * and only if the signal that was send caused most
		 * if not all of these threads to terminate. */
		decref(thread);
	}
}

/* Finalize a pointer set filled with `REF struct task *' elements. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL taskref_pointer_set_fini)(struct pointer_set *__restrict self) {
	taskref_pointer_set_decref_all(self);
	pointer_set_fini(self);
}



/* Raise a posix signal within a given thread `target'
 * @return: true:  Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false: The given thread `target' has already terminated execution.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or > `_NSIG' */
PUBLIC NONNULL((1)) bool KCALL
task_raisesignalthread(struct task *__restrict target,
                       USER CHECKED siginfo_t const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE, E_SEGFAULT) {
	struct pending_rpc *rpc;
	/* TODO: If `target's SIGHAND disposition for `info->si_signo' is set
	 *       to `SIG_IGN', then don't send the signal and silently return
	 *       with `true'. */

	rpc = pending_rpc_alloc_psig(GFP_NORMAL);

	/* Fill in RPC signal information. */
	memcpy(&rpc->pr_psig, info, sizeof(siginfo_t));
	COMPILER_READ_BARRIER();
	if unlikely(rpc->pr_psig.si_signo <= 0 ||
	            rpc->pr_psig.si_signo >= NSIG) {
		signo_t signo = rpc->pr_psig.si_signo;
		pending_rpc_free(rpc);
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      signo);
	}

	/* Set RPC flags: posix signals are _always_ async */
	rpc->pr_flags = RPC_SYNCMODE_F_ALLOW_ASYNC |
	                RPC_CONTEXT_SIGNAL |
	                RPC_SIGNO(rpc->pr_psig.si_signo);

	/* Schedule the RPC */
	if (task_rpc_schedule(target, rpc))
		return true;

	/* Target thread already died :( */
	pending_rpc_free(rpc);
	return false;
}





/* Raise a posix signal within a given process that `target' is apart of
 * @return: true:  Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false: The given process `target' has already terminated execution.
 * @return: false: The given process `target' is a kernel thread.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or >= `NSIG' */
PUBLIC NONNULL((1)) bool KCALL
task_raisesignalprocess(struct task *__restrict target,
                        USER CHECKED siginfo_t const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE, E_SEGFAULT) {
	struct pending_rpc *rpc;
	/* TODO: If any of `target's threads has a SIGHAND disposition for `info->si_signo'
	 *       that  is set to `SIG_IGN', then don't  send the signal and silently return
	 *       with `true'. */

	rpc = pending_rpc_alloc_psig(GFP_NORMAL);

	/* Fill in RPC signal information. */
	memcpy(&rpc->pr_psig, info, sizeof(siginfo_t));
	COMPILER_READ_BARRIER();
	if unlikely(rpc->pr_psig.si_signo <= 0 ||
	            rpc->pr_psig.si_signo >= NSIG) {
		signo_t signo = rpc->pr_psig.si_signo;
		pending_rpc_free(rpc);
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      signo);
	}

	/* Set RPC flags: posix signals are _always_ async */
	rpc->pr_flags = RPC_SYNCMODE_F_ALLOW_ASYNC |
	                RPC_CONTEXT_SIGNAL |
	                RPC_SIGNO(rpc->pr_psig.si_signo);

	/* Schedule the RPC */
	if (proc_rpc_schedule(target, rpc))
		return true;

	/* Target thread already died :( */
	pending_rpc_free(rpc);
	return false;
}


/* Send a signal to every process within the same process group that `target' is apart of.
 * @return: * : The number of processes to which the signal was delivered. */
PUBLIC NONNULL((1)) size_t KCALL
task_raisesignalprocessgroup(struct task *__restrict target,
                             USER CHECKED siginfo_t const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE, E_PROCESS_EXITED) {
	size_t result = 0;
	REF struct task *pgroup;
	struct taskgroup *pgroup_group;
	struct pointer_set ps; /* Set of processes already visited. */
	/* Deliver the first signal to the process group leader. */
	pgroup = task_getprocessgroupleader_srch_of(target);
	pgroup_group = &FORTASK(pgroup, this_taskgroup);
	TRY {
		if (task_raisesignalprocess(pgroup, info))
			++result;
	} EXCEPT {
		decref_unlikely(pgroup);
		RETHROW();
	}
	pointer_set_init(&ps);
	RAII_FINALLY {
		taskref_pointer_set_fini(&ps);
		decref_unlikely(pgroup);
	};
	{
		REF struct task *pending_delivery_procv[8];
		size_t pending_delivery_procc;
		bool there_are_more_procs;
		struct task *iter;
load_more_threads:
		pending_delivery_procc = 0;
		there_are_more_procs = false;
		sync_read(&pgroup_group->tg_pgrp_processes_lock);
		FOREACH_taskgroup__pgrp_processes(iter, pgroup_group) {
			assert(iter != pgroup);
			if (pointer_set_contains(&ps, iter))
				continue;
			if (!tryincref(iter))
				continue;
			/* Always re-start as  long as  we're able to  find any  other process that  is able  to
			 * receive  the signal. Otherwise, there would be  a race condition between us releasing
			 * the `tg_pgrp_processes_lock' lock,  and some process  calling `task_setprocess()'  to
			 * add itself to the process group. When this happens, that process wouldn't receive the
			 * signal that we're sending to every process within the group.
			 *
			 * This might sound like intended behavior on the surface, but this could also lead
			 * to a scenario  where you're  unable to kill  everyone from  some process  group:
			 *
			 *  #1: Thread[5]: setpgid(0, 0)                          - Become a process group leader
			 *  #2: Thread[5]: sys_fork()                             - Create new Process Thread[6]
			 *  #3: Thread[2]: kill(-5, SIGKILL);                     - Send SIGKILL to every process in PGROUP[5]
			 *  #4: Thread[2]: task_raisesignalprocessgroup()
			 *  #5: Thread[2]: sync_read(tg_pgrp_processes_lock)      - Acquire the lock to view every process apart of PGROUP[5]
			 *  #6: Thread[6]: sys_fork()                             - Try to create Thread[7]
			 *  #7: Thread[6]: task_setprocess(Thread[7])
			 *  #8: Thread[6]: sync_write(tg_pgrp_processes_lock)     - Acquire  the  lock  to add  Thread[7]  to PGROUP[5].
			 *                                                          This  blocks because we're  already holding the lock
			 *                                                          from step #5, so the call blocks until the lock will
			 *                                                          become available.
			 *  #9: Thread[2]: -- Gather all processes from PGROUP[5] (but keep `there_are_more_procs = false')
			 * #10: Thread[2]: sync_endread(tg_pgrp_processes_lock)             - The scheduler chooses not to wake-up `Thread[6]'
			 * #11: Thread[2]: -- Send SIGKILL to every process in PGROUP[5]
			 * #12: Thread[2]: sync_read(tg_pgrp_processes_lock)
			 * #13: Thread[2]: -- Scan for more processes that haven't gotten the signal, yet
			 * #14: Thread[2]: sync_endread(tg_pgrp_processes_lock)
			 * #15: Thread[2]: -- No further processes found
			 * #16: Thread[6]: sync_write(tg_pgrp_processes_lock)     - Finally stops blocking
			 * #17: Thread[6]: -- Add Thread[7] to process to PGROUP[5]
			 * #18: Thread[6]: sync_endwrite(tg_pgrp_processes_lock)
			 *
			 * #19: -- Every thread handles its signals in a random order and terminates.
			 *         However, Thread[7] was never given sent a signal and will continue
			 *         to run indefinitely.
			 *
			 * This is fixed  by always  keeping on searching  for more  processes to  receive
			 * the signal, which then interlocks with the call to `task_serve()' in `clone()',
			 * that is done by the parent process and can be used to prevent the child process
			 * from being started. */
			there_are_more_procs = true;
			pending_delivery_procv[pending_delivery_procc] = iter;
			++pending_delivery_procc;
			if (pending_delivery_procc >= COMPILER_LENOF(pending_delivery_procv))
				break;
		}
		sync_endread(&pgroup_group->tg_pgrp_processes_lock);
		TRY {
			while (pending_delivery_procc) {
				REF struct task *thread;
				thread = pending_delivery_procv[pending_delivery_procc - 1];
				/* Deliver to this process. */
				if (task_raisesignalprocess(thread, info))
					++result;
				/* NOTE: We must insert references to threads which already had
				 *       a signal get delivered. This is _required_ to  prevent
				 *       the scenario where:
				 *        - SEND_SIGNAL_TO_THREAD(t1);
				 *        - ps.insert(t1);
				 *        - In t1: task_exit();
				 *        - In t1: decref(THIS_TASK);
				 *        - In t1: destroy(THIS_TASK);
				 *        - In t1: free(THIS_TASK);
				 *        - In t2: clone();
				 *        - In t2: t3 = kmalloc(struct task);   // addrof(t3) == addrof(t2)
				 *        - In t2: init(t3);
				 *        - In t2: task_start(t3);
				 *       In this case, we'd never end up sending a signal to `t3',
				 *       since we'd think that that thread already had the  signal
				 *       delivered.
				 *
				 * It is kind-of sad  that we have to  keep references to all  of
				 * the threads that already got the signal, since we really don't
				 * need those references for anything else. But it's the simplest
				 * thing we can do here.
				 *
				 * NOTE: We don't keep references for the taskpid structures of
				 * threads that already got the signal, since certain types  of
				 * thread (kernel threads) don't have taskpid descriptors! */
				pointer_set_insert(&ps, thread, GFP_NORMAL); /* Inherit reference. */
				/*decref_unlikely(thread);*/ /* Inherited by `ps' */
				--pending_delivery_procc;
			}
		} EXCEPT {
			while (pending_delivery_procc--)
				decref_unlikely(pending_delivery_procv[pending_delivery_procc]);
			RETHROW();
		}
		if (there_are_more_procs)
			goto load_more_threads;
	}
	return result;
}








/************************************************************************/
/* sigaction(), rt_sigaction(), signal()                                */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_SIGACTION) ||           \
     defined(__ARCH_WANT_SYSCALL_RT_SIGACTION) ||        \
     defined(__ARCH_WANT_SYSCALL_SIGNAL) ||              \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SIGACTION) ||    \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGACTION) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SIGNAL))
#define WANT_SIGACTION 1
#endif /* ... */

#ifdef WANT_SIGACTION
PRIVATE void KCALL
do_sigaction(signo_t signo,
             CHECKED USER struct sigaction const *act,
             CHECKED USER struct sigaction *oact) {
	struct kernel_sigaction ohandler;
	struct sighand *hand;
	if unlikely(signo <= 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      signo);
	if (!act) {
		if (oact) {
			struct sighand_ptr *handptr;
			handptr = THIS_SIGHAND_PTR;
			if (handptr) {
				hand = sighand_ptr_lockread(handptr);
				if (!hand)
					goto no_old_handler;
				memcpy(&ohandler,
				       &hand->sh_actions[signo - 1],
				       sizeof(ohandler));
				xincref(ohandler.sa_mask);
				sync_endread(hand);
inherit_and_copy_ohandler:
				FINALLY_XDECREF(ohandler.sa_mask);
				COMPILER_WRITE_BARRIER();
				oact->sa_handler  = ohandler.sa_handler;
				oact->sa_flags    = ohandler.sa_flags;
				oact->sa_restorer = ohandler.sa_restore;
				if (ohandler.sa_mask) {
					memcpy(&oact->sa_mask,
					       &ohandler.sa_mask->sm_mask,
					       sizeof(sigset_t));
				} else {
					memset(&oact->sa_mask, 0,
					       sizeof(sigset_t));
				}
				COMPILER_WRITE_BARRIER();
			} else {
no_old_handler:
				memset(oact, 0, sizeof(*oact));
			}
		}
	} else {
		struct kernel_sigaction nhandler;
		COMPILER_READ_BARRIER();
		nhandler.sa_handler = act->sa_handler;
		nhandler.sa_flags   = act->sa_flags;
		COMPILER_READ_BARRIER();
#ifndef KERNELSPACE_HIGHMEM
		if ((uintptr_t)nhandler.sa_handler >= __SIG_GET)
#endif /* !KERNELSPACE_HIGHMEM */
		{
			validate_executable((void const *)nhandler.sa_handler);
		}
		VALIDATE_FLAGSET(nhandler.sa_flags,
		                 SA_NOCLDSTOP | SA_NOCLDWAIT | SA_SIGINFO |
		                 SA_RESTORER | SA_ONSTACK | SA_RESTART |
		                 SA_NODEFER | SA_RESETHAND | SA_INTERRUPT,
		                 E_INVALID_ARGUMENT_CONTEXT_SIGACTION_ACT_FLAGS);
		COMPILER_BARRIER();
		nhandler.sa_restore = NULL;
		if (nhandler.sa_flags & SA_RESTORER) {
			nhandler.sa_restore = act->sa_restorer;
			COMPILER_READ_BARRIER();
			validate_executable((void const *)nhandler.sa_restore);
		}
		COMPILER_BARRIER();
		nhandler.sa_mask = NULL;
		/* Check if the given signal set is empty. */
		{
			size_t i;
			for (i = 0; i < COMPILER_LENOF(act->sa_mask.__val); ++i) {
				REF struct kernel_sigmask *mask;
				if (act->sa_mask.__val[i] == 0)
					continue;
				COMPILER_READ_BARRIER();
				/* Must allocate a custom signal mask. */
				mask = (REF struct kernel_sigmask *)kmalloc(sizeof(struct kernel_sigmask),
				                                            GFP_NORMAL);
				TRY {
					COMPILER_READ_BARRIER();
					memcpy(&mask->sm_mask, &act->sa_mask, sizeof(sigset_t));
					COMPILER_READ_BARRIER();
				} EXCEPT {
					kfree(mask);
					RETHROW();
				}
				mask->sm_refcnt  = 1;
				mask->sm_share   = 1;
				nhandler.sa_mask = mask;
				break;
			}
		}
		COMPILER_BARRIER();
		TRY {
			hand = sighand_ptr_lockwrite();
		} EXCEPT {
			kfree(nhandler.sa_mask);
			RETHROW();
		}
		/* Change the signal action. */
		memcpy(&ohandler, &hand->sh_actions[signo - 1], sizeof(ohandler));
		memcpy(&hand->sh_actions[signo - 1], &nhandler, sizeof(nhandler));
		sync_endwrite(hand);
		/* Check if user-space also wants to get the old action. */
		if (oact)
			goto inherit_and_copy_ohandler;
		xdecref(ohandler.sa_mask);
	}
}
#endif /* WANT_SIGACTION */

#ifdef __ARCH_WANT_SYSCALL_RT_SIGACTION
DEFINE_SYSCALL4(errno_t, rt_sigaction, signo_t, signo,
                UNCHECKED USER struct sigaction const *, act,
                UNCHECKED USER struct sigaction *, oact,
                size_t, sigsetsize) {
	if unlikely(sigsetsize != sizeof(sigset_t)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	}
	/* Validate user-structure pointers. */
	validate_readable_opt(act, sizeof(*act));
	validate_writable_opt(oact, sizeof(*oact));
	do_sigaction(signo, act, oact);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGACTION */

#ifdef __ARCH_WANT_SYSCALL_SIGACTION
DEFINE_SYSCALL3(errno_t, sigaction, signo_t, signo,
                UNCHECKED USER struct sigaction const *, act,
                UNCHECKED USER struct sigaction *, oact) {
	return sys_rt_sigaction(signo, act, oact, sizeof(sigset_t));
}
#endif /* __ARCH_WANT_SYSCALL_SIGACTION */

#if defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGACTION) || \
    defined(__ARCH_WANT_COMPAT_SYSCALL_SIGACTION)
PRIVATE void KCALL
compat_sigaction_to_sigaction(CHECKED USER struct compat_sigaction const *self,
                              struct sigaction *__restrict result) {
	*(void **)&result->sa_handler  = (void *)self->sa_handler;
	memcpy(&result->sa_mask, &self->sa_mask,
	       MIN_C(sizeof(sigset_t), sizeof(compat_sigset_t)));
	__STATIC_IF(sizeof(sigset_t) > sizeof(compat_sigset_t)) {
		memset((byte_t *)&result->sa_mask + sizeof(compat_sigset_t), 0,
		       sizeof(sigset_t) - sizeof(compat_sigset_t));
	}
	result->sa_flags = self->sa_flags;
	*(void **)&result->sa_restorer  = (void *)self->sa_restorer;
}

PRIVATE void KCALL
sigaction_to_compat_sigaction(struct sigaction const *__restrict self,
                              CHECKED USER struct compat_sigaction *result) {
	typedef compat_funptr(void, , compat_sigrestorer_t, (void));
	result->sa_handler = (compat_sighandler_t)(uintptr_t)(void *)self->sa_handler;
	memcpy(&result->sa_mask, &self->sa_mask,
	       MIN_C(sizeof(sigset_t), sizeof(compat_sigset_t)));
	__STATIC_IF(sizeof(compat_sigset_t) > sizeof(sigset_t)) {
		memset((byte_t *)&result->sa_mask + sizeof(sigset_t), 0,
		       sizeof(compat_sigset_t) - sizeof(sigset_t));
	}
	result->sa_flags = self->sa_flags;
	result->sa_restorer = (compat_sigrestorer_t)(uintptr_t)(void *)self->sa_restorer;
}

PRIVATE errno_t KCALL
do_compat_sigaction(compat_signo_t signo,
                    UNCHECKED USER struct compat_sigaction const *act,
                    UNCHECKED USER struct compat_sigaction *oact) {
	struct sigaction real_act, real_oact;
	/* Validate user-structure pointers. */
	validate_readable_opt(act, sizeof(*act));
	validate_writable_opt(oact, sizeof(*oact));
	if (act)
		compat_sigaction_to_sigaction(act, &real_act);
	do_sigaction(signo,
	             act ? &real_act : NULL,
	             oact ? &real_oact : NULL);
	if (oact)
		sigaction_to_compat_sigaction(&real_oact, oact);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGACTION */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGACTION
DEFINE_COMPAT_SYSCALL4(compat_errno_t, rt_sigaction, compat_signo_t, signo,
                       UNCHECKED USER struct compat_sigaction const *, act,
                       UNCHECKED USER struct compat_sigaction *, oact,
                       size_t, sigsetsize) {
	if unlikely(sigsetsize != sizeof(sigset_t)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	}
	return do_compat_sigaction(signo, act, oact);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGACTION */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGACTION
DEFINE_COMPAT_SYSCALL3(compat_errno_t, sigaction, compat_signo_t, signo,
                       UNCHECKED USER struct compat_sigaction const *, act,
                       UNCHECKED USER struct compat_sigaction *, oact) {
	return do_compat_sigaction(signo, act, oact);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGACTION */

#ifdef __ARCH_WANT_SYSCALL_SIGNAL
DEFINE_SYSCALL2(sighandler_t, signal,
                signo_t, signo,
                UNCHECKED USER sighandler_t, handler) {
	struct sigaction oact, act;
	if (handler == SIG_GET) {
		do_sigaction(signo, NULL, &oact);
	} else {
		memset(&act, 0, sizeof(act));
		act.sa_handler = handler;
		do_sigaction(signo, &act, &oact);
	}
	return oact.sa_handler;
}
#endif /* __ARCH_WANT_SYSCALL_SIGNAL */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGNAL
DEFINE_COMPAT_SYSCALL2(sighandler_t, signal,
                       compat_signo_t, signo,
                       UNCHECKED USER sighandler_t, handler) {
	struct sigaction oact, act;
	if (handler == SIG_GET) {
		do_sigaction(signo, NULL, &oact);
	} else {
		memset(&act, 0, sizeof(act));
		act.sa_handler = handler;
		do_sigaction(signo, &act, &oact);
	}
	return oact.sa_handler;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGNAL */





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
	memset((byte_t *)mymask + sizeof(new_sigmask),
	       0, sizeof(sigset_t) - sizeof(new_sigmask));
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
	memset((byte_t *)mymask+ sizeof(used_sigmask),
	       0, sizeof(sigset_t) - sizeof(used_sigmask));
#endif /* __SIZEOF_SIGSET_T__ > __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T */
	/* Make sure that these two signals aren't being masked! */
	sigdelset(mymask, SIGKILL);
	sigdelset(mymask, SIGSTOP);
	userexcept_sysret_inject_self();
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SSETMASK */


LOCAL ATTR_PURE WUNUSED NONNULL((1)) size_t KCALL
get_pid_indirection(struct task const *__restrict thread) {
	struct taskpid *pid = FORTASK(thread, this_taskpid);
	return likely(pid) ? pid->tp_pidns->pn_indirection : 0;
}

LOCAL ATTR_PURE WUNUSED NONNULL((1)) upid_t KCALL
taskpid_getpid_ind(struct taskpid *__restrict self, size_t ind) {
	if likely(ind <= self->tp_pidns->pn_indirection)
		return self->tp_pids[ind];
	return 0;
}





/************************************************************************/
/* kill(), tgkill(), tkill()                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_KILL
DEFINE_SYSCALL2(errno_t, kill, pid_t, pid, signo_t, signo) {
	REF struct task *target;
	struct taskpid *mypid;
	siginfo_t info;
	memset(&info, 0, sizeof(siginfo_t));
	/* Make sure we've been given a valid signal number. */
	if unlikely(signo <= 0 || signo >= NSIG) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      signo);
	}
	info.si_signo = signo;
	info.si_errno = 0;
	info.si_code  = SI_USER;
	info.si_uid   = (__uid_t)cred_geteuid();
	mypid         = THIS_TASKPID;
	if (pid > 0) {
		/* Kill the thread matching `pid'. */
		target = pidns_lookup_task(THIS_PIDNS, (upid_t)pid);
		FINALLY_DECREF_UNLIKELY(target);
		info.si_pid = taskpid_getpid_ind(mypid, get_pid_indirection(target));
		if (!task_raisesignalprocess(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	} else if (pid == 0) {
		/* Kill all processes in the calling thread's process group. */
		target = task_getprocessgroupleader_srch();
		goto do_inherit_target_and_raise_processgroup;
	} else if (pid == -1) {
		/* TODO: Kill all processes that we're allowed to (except for pid=1). */
		THROW(E_NOT_IMPLEMENTED_TODO);
	} else {
		/* Kill the entirety of a process group. */
		target = pidns_lookup_task(THIS_PIDNS, (upid_t)-pid);
do_inherit_target_and_raise_processgroup:
		FINALLY_DECREF_UNLIKELY(target);
		info.si_pid = taskpid_getpid_ind(mypid, get_pid_indirection(target));
		if (!task_raisesignalprocessgroup(target, &info))
			THROW(E_PROCESS_EXITED, task_getpid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_KILL */

#ifdef __ARCH_WANT_SYSCALL_TGKILL
DEFINE_SYSCALL3(errno_t, tgkill,
                pid_t, pid, pid_t, tid,
                signo_t, signo) {
	REF struct task *target;
	if unlikely(signo < 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      signo);
	if unlikely(pid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID,
		      pid);
	if unlikely(tid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_TID,
		      tid);
	target = pidns_lookup_task(THIS_PIDNS, (upid_t)tid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Check if the given TGID matches the group of this thread. */
	if (taskpid_getpid_s(task_getprocesspid_of(target)) != (upid_t)pid) {
		/* Maybe not necessarily exited, but no need to create a new exception type for this... */
		THROW(E_PROCESS_EXITED, pid);
	}
	/* Don't deliver signal `0'. - It's used to test access. */
	if (signo != 0) {
		siginfo_t info;
		memset(&info, 0, sizeof(siginfo_t));
		info.si_signo = signo;
		info.si_errno = 0;
		info.si_code  = SI_TKILL;
		info.si_uid   = (__uid_t)cred_geteuid();
		info.si_pid   = (__pid_t)taskpid_getpid_ind(THIS_TASKPID, get_pid_indirection(target));
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_TGKILL */

#ifdef __ARCH_WANT_SYSCALL_TKILL
DEFINE_SYSCALL2(errno_t, tkill, pid_t, tid, signo_t, signo) {
	REF struct task *target;
	if unlikely(signo < 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO, signo);
	if unlikely(tid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_TID, tid);
	target = pidns_lookup_task(THIS_PIDNS, (upid_t)tid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't deliver signal `0'. - It's used to test access. */
	if (signo != 0) {
		siginfo_t info;
		memset(&info, 0, sizeof(siginfo_t));
		info.si_signo = signo;
		info.si_errno = 0;
		info.si_code  = SI_TKILL;
		info.si_uid   = (__uid_t)cred_geteuid();
		info.si_pid   = (__pid_t)taskpid_getpid_ind(THIS_TASKPID, get_pid_indirection(target));
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_TKILL */





/************************************************************************/
/* rt_sigqueueinfo(), rt_tgsigqueueinfo()                               */
/************************************************************************/

/* Fill in `info' from `usigno' + `uinfo' */
INTERN NONNULL((1)) void KCALL
siginfo_from_user(siginfo_t *__restrict info, signo_t usigno,
                  USER UNCHECKED siginfo_t const *uinfo) {
	if unlikely(usigno < 0 || usigno >= NSIG) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      usigno);
	}
	if (uinfo) {
		validate_readable(uinfo, sizeof(siginfo_t));
		COMPILER_READ_BARRIER();
		memcpy(info, uinfo, sizeof(siginfo_t));
		COMPILER_READ_BARRIER();
		if unlikely(usigno != info->si_signo) {
			THROW(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO,
			      usigno, info->si_signo);
		}
	} else {
		memset(info, 0, sizeof(*info));
		info->si_signo = usigno;
		info->si_errno = 0;
		info->si_code  = SI_USER;
		info->si_pid   = (__pid_t)task_getpid();
		info->si_uid   = (__uid_t)cred_geteuid();
	}
}

#ifdef __ARCH_HAVE_COMPAT
INTERN NONNULL((1)) void KCALL
siginfo_from_compat_user(siginfo_t *__restrict info, signo_t usigno,
                         USER UNCHECKED compat_siginfo_t const *uinfo) {
	if unlikely(usigno < 0 || usigno >= NSIG) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      usigno);
	}
	if (uinfo) {
		compat_validate_readable(uinfo, sizeof(compat_siginfo_t));
		compat_siginfo_to_siginfo(uinfo, info);
		if (usigno != info->si_signo) {
			THROW(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_SIGINFO_SIGNO,
			      usigno, info->si_signo);
		}
	} else {
		memset(info, 0, sizeof(*info));
		info->si_signo = usigno;
		info->si_errno = 0;
		info->si_code  = SI_USER;
		info->si_pid   = (__pid_t)task_getpid();
		info->si_uid   = (__uid_t)cred_geteuid();
	}
}
#endif /* __ARCH_HAVE_COMPAT */


#ifdef __ARCH_WANT_SYSCALL_RT_SIGQUEUEINFO
DEFINE_SYSCALL3(errno_t, rt_sigqueueinfo,
                pid_t, pid, signo_t, signo,
                USER UNCHECKED siginfo_t const *, uinfo) {
	REF struct task *target;
	siginfo_t info;
	if unlikely(pid <= 0) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, pid);
	}
	siginfo_from_user(&info, signo, uinfo);
	target = pidns_lookup_task(THIS_PIDNS, (upid_t)pid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) &&
	    (task_getprocess_of(target) != task_getprocess()))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	if (signo != 0) {
		if (!task_raisesignalprocess(target, &info))
			THROW(E_PROCESS_EXITED, task_getpid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGQUEUEINFO */

#ifdef __ARCH_WANT_SYSCALL_RT_TGSIGQUEUEINFO
DEFINE_SYSCALL4(errno_t, rt_tgsigqueueinfo,
                pid_t, pid, pid_t, tid, signo_t, signo,
                USER UNCHECKED siginfo_t const *, uinfo) {
	siginfo_t info;
	REF struct task *target;
	struct task *leader;
	if unlikely(pid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, pid);
	if unlikely(tid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_TID, tid);
	siginfo_from_user(&info, signo, uinfo);
	target = pidns_lookup_task(THIS_PIDNS, (upid_t)tid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	leader = task_getprocess_of(target);
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) && leader != task_getprocess())
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	/* Check if the thread-group ID matches that of the leader of the requested thread-group. */
	if (task_gettid_of_s(leader) != (upid_t)pid)
		THROW(E_PROCESS_EXITED, pid);
	if (signo != 0) {
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_TGSIGQUEUEINFO */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGQUEUEINFO
DEFINE_COMPAT_SYSCALL3(errno_t, rt_sigqueueinfo,
                       pid_t, pid, signo_t, signo,
                       USER UNCHECKED compat_siginfo_t const *, uinfo) {
	REF struct task *target;
	siginfo_t info;
	if unlikely(pid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, pid);
	siginfo_from_compat_user(&info, signo, uinfo);
	target = pidns_lookup_task(THIS_PIDNS, (upid_t)pid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) &&
	    (task_getprocess_of(target) != task_getprocess()))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	if (signo != 0) {
		if (!task_raisesignalprocess(target, &info))
			THROW(E_PROCESS_EXITED, task_getpid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGQUEUEINFO */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_TGSIGQUEUEINFO
DEFINE_COMPAT_SYSCALL4(errno_t, rt_tgsigqueueinfo,
                       pid_t, pid, pid_t, tid, signo_t, signo,
                       USER UNCHECKED compat_siginfo_t const *, uinfo) {
	siginfo_t info;
	REF struct task *target;
	struct task *leader;
	if unlikely(pid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, pid);
	if unlikely(tid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_TID, tid);
	siginfo_from_compat_user(&info, signo, uinfo);
	target = pidns_lookup_task(THIS_PIDNS, (upid_t)tid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	leader = task_getprocess_of(target);
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) && leader != task_getprocess())
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	/* Check if the thread-group ID matches that of the leader of the requested thread-group. */
	if (task_gettid_of_s(leader) != (upid_t)pid)
		THROW(E_PROCESS_EXITED, pid);
	if (signo != 0) {
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_TGSIGQUEUEINFO */





/************************************************************************/
/* rt_sigtimedwait(), rt_sigtimedwait_time64()                          */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT) ||          \
     defined(__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64) ||        \
     defined(__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT_TIME64) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT_TIME64))
#define WANT_SIGTIMEDWAIT 1
#endif /* ... */

#ifdef WANT_SIGTIMEDWAIT
/* @return: 0 : The timeout has expired
 * @return: * : The accepted signal number */
PRIVATE signo_t KCALL
signal_waitfor(CHECKED USER sigset_t const *uthese,
               CHECKED USER siginfo_t *uinfo,
               ktime_t abs_timeout) {
	sigset_t these;
	assert(!task_wasconnected());
	assert(PREEMPTION_ENABLED());
	memcpy(&these, uthese, sizeof(sigset_t));
	COMPILER_BARRIER();
	/* Make sure that we don't steal these signals */
	sigdelset(&these, SIGKILL);
	sigdelset(&these, SIGSTOP);
	COMPILER_WRITE_BARRIER();

	/* Since we may (very likely)  be waiting for signals that  are
	 * currently masked,  we need  to make  certain that  we  still
	 * receive notification when such a signal arrives, even though
	 * we're unable to handle it by "normal" means. */
	ATOMIC_OR(THIS_TASK->t_flags, TASK_FWAKEONMSKRPC);
	TRY {
		for (;;) {
			struct pending_rpc *rpc;

			/* Disable preemption for interlocking with  sporadic
			 * wakeups send as the result of new RPCs being added
			 * to our thread's or process's pending lists. */
			PREEMPTION_DISABLE();

			/* Try to steal RPCs. */
			rpc = task_rpc_pending_steal_posix_signal(&these);
			if (rpc == NULL) {
				rpc = proc_rpc_pending_trysteal_posix_signal(&these);
				if (rpc == PROC_RPC_PENDING_TRYSTEAL_POSIX_SIGNAL_WOULDBLOCK) {
					struct process_pending_rpcs *proc_rpcs;
					PREEMPTION_ENABLE();
					/* Yield until the lock becomes available. */
					proc_rpcs = &THIS_PROCESS_RPCS;
					process_pending_rpcs_waitwrite(proc_rpcs);
					continue;
				}
			}

			if (rpc != NULL) {
				/* Got one! */
				signo_t result;
				ATOMIC_AND(THIS_TASK->t_flags, ~TASK_FWAKEONMSKRPC);
				PREEMPTION_ENABLE();
				assert(!(rpc->pr_flags & RPC_CONTEXT_KERN));
				assert(rpc->pr_flags & RPC_CONTEXT_SIGNAL);
				result = rpc->pr_psig.si_signo;
				/* Copy signal information to userspace */
				RAII_FINALLY { pending_rpc_free(rpc); };
				memcpy(uinfo, &rpc->pr_psig, sizeof(siginfo_t));
				return result;
			}

			/* Like always, serve RPCs (and posix signals) before going to sleep. */
			if (task_serve())
				continue;

			/* Sleep until the next sporadic interrupt. */
			if (!task_sleep(abs_timeout))
				return 0;
		}
	} EXCEPT {
		ATOMIC_AND(THIS_TASK->t_flags, ~TASK_FWAKEONMSKRPC);
		RETHROW();
	}
}
#endif /* WANT_SIGTIMEDWAIT */

#ifdef __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT
DEFINE_SYSCALL4(syscall_slong_t, rt_sigtimedwait,
                UNCHECKED USER sigset_t const *, uthese,
                UNCHECKED USER siginfo_t *, uinfo,
                UNCHECKED USER struct timespec32 const *, uts,
                size_t, sigsetsize) {
	syscall_slong_t result;
	ktime_t abs_timeout = KTIME_INFINITE;
	/* Validate user-structure pointers. */
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (uts) {
		validate_readable(uts, sizeof(*uts));
		abs_timeout = relktime_from_user_rel(uts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = (syscall_slong_t)signal_waitfor(uthese, uinfo,
	                                         abs_timeout);
	if (!result)
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT */

#if (defined(__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64) || \
     defined(__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT_TIME64))
#ifdef __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64
DEFINE_SYSCALL4(syscall_slong_t, rt_sigtimedwait64,
                UNCHECKED USER sigset_t const *, uthese,
                UNCHECKED USER siginfo_t *, uinfo,
                UNCHECKED USER struct timespec64 const *, uts,
                size_t, sigsetsize)
#else /* __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64 */
DEFINE_SYSCALL4(syscall_slong_t, rt_sigtimedwait_time64,
                UNCHECKED USER sigset_t const *, uthese,
                UNCHECKED USER siginfo_t *, uinfo,
                UNCHECKED USER struct timespec64 const *, uts,
                size_t, sigsetsize)
#endif /* !__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64 */
{
	syscall_slong_t result;
	ktime_t abs_timeout = KTIME_INFINITE;
	/* Validate user-structure pointers. */
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (uts) {
		validate_readable(uts, sizeof(*uts));
		abs_timeout = relktime_from_user_rel(uts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = (syscall_slong_t)signal_waitfor(uthese, uinfo,
	                                         abs_timeout);
	if (!result)
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64 || __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT
DEFINE_COMPAT_SYSCALL4(syscall_slong_t, rt_sigtimedwait,
                       UNCHECKED USER compat_sigset_t const *, uthese,
                       UNCHECKED USER compat_siginfo_t *, uinfo,
                       UNCHECKED USER struct compat_timespec32 const *, uts,
                       size_t, sigsetsize) {
	syscall_slong_t result;
	siginfo_t info;
	ktime_t abs_timeout = KTIME_INFINITE;
	/* Validate user-structure pointers. */
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (uts) {
		validate_readable(uts, sizeof(*uts));
		abs_timeout = relktime_from_user_rel(uts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = (syscall_slong_t)signal_waitfor(uthese, &info,
	                                         abs_timeout);
	if (!result)
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	else {
		siginfo_to_compat_siginfo(&info, uinfo);
	}
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT_TIME64))
#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64
DEFINE_COMPAT_SYSCALL4(syscall_slong_t, rt_sigtimedwait64,
                       UNCHECKED USER compat_sigset_t const *, uthese,
                       UNCHECKED USER compat_siginfo_t *, uinfo,
                       UNCHECKED USER struct compat_timespec64 const *, uts,
                       size_t, sigsetsize)
#else /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64 */
DEFINE_COMPAT_SYSCALL4(syscall_slong_t, rt_sigtimedwait_time64,
                       UNCHECKED USER compat_sigset_t const *, uthese,
                       UNCHECKED USER compat_siginfo_t *, uinfo,
                       UNCHECKED USER struct compat_timespec64 const *, uts,
                       size_t, sigsetsize)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64 */
{
	syscall_slong_t result;
	siginfo_t info;
	ktime_t abs_timeout = KTIME_INFINITE;
	/* Validate user-structure pointers. */
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (uts) {
		validate_readable(uts, sizeof(*uts));
		abs_timeout = relktime_from_user_rel(uts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = (syscall_slong_t)signal_waitfor(uthese, &info,
	                                         abs_timeout);
	if (!result)
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	else {
		siginfo_to_compat_siginfo(&info, uinfo);
	}
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64 || __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT_TIME64 */





/************************************************************************/
/* rt_sigsuspend(), sigsuspend()                                        */
/************************************************************************/

#if (defined(__ARCH_WANT_SYSCALL_RT_SIGSUSPEND) || \
     defined(__ARCH_WANT_SYSCALL_SIGSUSPEND) ||    \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SIGSUSPEND))
/* This function is also called from arch-specific, optimized syscall routers. */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_sigsuspend_impl(struct icpustate *__restrict state,
                    struct rpc_syscall_info *__restrict sc_info,
                    size_t sigsetsize) {
	sigset_t not_these;
	USER UNCHECKED sigset_t const *unot_these;
	if unlikely(sigsetsize != sizeof(sigset_t)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	}
	unot_these = (USER UNCHECKED sigset_t const *)sc_info->rsi_regs[0];
	validate_readable(unot_these, sizeof(sigset_t));
	memcpy(&not_these, unot_these, sizeof(sigset_t));

	/* These signals cannot be masked. (iow: _always_ wait for these signals) */
	sigdelset(&not_these, SIGSTOP);
	sigdelset(&not_these, SIGKILL);

	/* Indicate that we want to receive wake-ups for masked signals. */
	ATOMIC_OR(THIS_TASK->t_flags, TASK_FWAKEONMSKRPC);

	/* This will clear `TASK_FWAKEONMSKRPC', as well as
	 * perform a check for signals not in `these' which
	 * may have also appeared in the mean time prior to
	 * returning to user-space. */
	userexcept_sysret_inject_self();
again:
	TRY {
		/* The  normal implementation of the system call,
		 * except that `task_serve_with_sigmask' replaces
		 * calls to `task_serve()'
		 *
		 * In case of  `sigsuspend(2)`, the "normal"  implementation
		 * is `pause(2)`, which can simply be implemented like this: */
		for (;;) {
			PREEMPTION_DISABLE();
			if (task_serve_with_sigmask(&not_these))
				continue;
			task_sleep();
		}
	} EXCEPT {
		/* This function  only returns  normally
		 * when the syscall should be restarted. */
		state = userexcept_handler_with_sigmask(state, sc_info, &not_these);
		PERTASK_SET(this_exception_code, 1); /* Prevent internal fault */
		goto again;
	}
	__builtin_unreachable();
}
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_RT_SIGSUSPEND
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_rt_sigsuspend_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_sigsuspend_impl(ctx->rc_state, &ctx->rc_scinfo,
	                                    (size_t)ctx->rc_scinfo.rsi_regs[1]);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL2(errno_t, rt_sigsuspend,
                USER UNCHECKED sigset_t const *, unot_these,
                size_t, sigsetsize) {
	(void)unot_these;
	(void)sigsetsize;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_rt_sigsuspend_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGSUSPEND */

#ifdef __ARCH_WANT_SYSCALL_SIGSUSPEND
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_sigsuspend_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_sigsuspend_impl(ctx->rc_state, &ctx->rc_scinfo, sizeof(sigset_t));

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL1(errno_t, sigsuspend,
                USER UNCHECKED sigset_t const *, unot_these) {
	(void)unot_these;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_sigsuspend_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_SIGSUSPEND */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGSUSPEND
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_compat_sigsuspend_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_sigsuspend_impl(ctx->rc_state, &ctx->rc_scinfo, sizeof(compat_sigset_t));

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_COMPAT_SYSCALL1(errno_t, sigsuspend,
                       USER UNCHECKED compat_sigset_t const *, unot_these) {
	(void)unot_these;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_compat_sigsuspend_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGSUSPEND */





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

#endif /* !GUARD_KERNEL_SRC_SCHED_POSIX_SIGNAL_C */
