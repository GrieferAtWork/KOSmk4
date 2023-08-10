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
#ifndef GUARD_KERNEL_SRC_SCHED_SIGMASK_C
#define GUARD_KERNEL_SRC_SCHED_SIGMASK_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/rt/except-handler.h>
#include <kernel/rt/except-syscall.h> /* CONFIG_HAVE_KERNEL_USERPROCMASK */
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/sigmask.h>
#include <sched/task.h>

#include <hybrid/sched/preemption.h>
#include <hybrid/typecore.h>
#include <hybrid/unaligned.h>

#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/nopf.h>
#include <sys/param.h>

#include <assert.h>
#include <atomic.h>
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

#define SIGSET_WORD_C   __UINTPTR_C
#define SIGSET_WORDBITS (__SIZEOF_POINTER__ * NBBY)
#define SIGSET_NUMBITS  (__SIGSET_NWORDS * SIGSET_WORDBITS)

/* A full signal mask (i.e. one that blocks all signals (except for SIGKILL and SIGSTOP)) */
PUBLIC_CONST sigset_t const sigmask_full = {{
/*[[[deemon

// Supported values for various signal constants
local supported_SIGKILL_values = [9];
local supported_SIGSTOP_values = [19];
local supported_sigset_bits    = [32, 64, 128, 1024];
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
		if ((i % 4) == 0) {
			print("\t"),;
		} else {
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
#if SIGKILL == 9 && SIGSTOP == 19 && SIGSET_NUMBITS == 32 && SIGSET_WORDBITS == 32
	SIGSET_WORD_C(0xfffbfeff)
#elif SIGKILL == 9 && SIGSTOP == 19 && SIGSET_NUMBITS == 32 && SIGSET_WORDBITS == 64
	SIGSET_WORD_C(0xfffffffffffbfeff)
#elif SIGKILL == 9 && SIGSTOP == 19 && SIGSET_NUMBITS == 64 && SIGSET_WORDBITS == 32
	SIGSET_WORD_C(0xfffbfeff), SIGSET_WORD_C(0xffffffff)
#elif SIGKILL == 9 && SIGSTOP == 19 && SIGSET_NUMBITS == 64 && SIGSET_WORDBITS == 64
	SIGSET_WORD_C(0xfffffffffffbfeff)
#elif SIGKILL == 9 && SIGSTOP == 19 && SIGSET_NUMBITS == 128 && SIGSET_WORDBITS == 32
	SIGSET_WORD_C(0xfffbfeff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff), SIGSET_WORD_C(0xffffffff)
#elif SIGKILL == 9 && SIGSTOP == 19 && SIGSET_NUMBITS == 128 && SIGSET_WORDBITS == 64
	SIGSET_WORD_C(0xfffffffffffbfeff), SIGSET_WORD_C(0xffffffffffffffff)
#elif SIGKILL == 9 && SIGSTOP == 19 && SIGSET_NUMBITS == 1024 && SIGSET_WORDBITS == 32
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
}};



/* [lock(READ(ATOMIC), WRITE(THIS_TASK))]
 * Reference to the signal mask (set of signals being blocked) in the  current
 * thread. The pointed-to object is meaningless (but must still be valid) when
 * the associated thread make use of userprocmask.
 *
 * WARNING: This signal set must  _NEVER_ contain `SIGKILL' or  `SIGSTOP'.
 *          Not when `TASK_USERPROCMASK' is set, and neither for only just
 *          a couple of moments. -- NO EXCEPTIONS!
 * Furthermore, this set may not contain garbage when `TASK_USERPROCMASK'
 * is set. Instead, in this case  it must contain the last-active  signal
 * mask prior to the calling thread activating `TASK_USERPROCMASK'.  This
 * is needed so that after  checking that `TASK_USERPROCMASK' isn't  set,
 * any  thread can safely read from this  set with the knowledge that any
 * unmasked signal was masked at  the time of the of  `TASK_USERPROCMASK'
 * not having been set, or has since become masked by the thread  itself. */
PUBLIC ATTR_PERTASK ATTR_ALIGN(sigset_t)
this_kernel_sigmask = SIGSET_INIT_EMPTY;




#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
PRIVATE ATTR_PURE WUNUSED bool FCALL
usersigmask_ismasked_chk(signo_t signo) THROWS(E_SEGFAULT) {
	ulongptr_t mask, word;
	NCX struct userprocmask *umask;
	NCX UNCHECKED sigset_t *usigset;
	bool result;

	/* Load the address of the userprocmask descriptor. */
	umask = PERTASK_GET(this_userprocmask_address);
	assert(umask && ADDR_ISUSER(umask));

	/* Mark the signal as pending for this thread. */
	word = __sigset_word(signo);
	mask = __sigset_mask(signo);

	/* First user-space memory access: read our current signal mask. */
	usigset = atomic_read(&umask->pm_sigmask);

	/* Make sure that the user-space pointer is valid. */
	validate_readable(usigset, sizeof(sigset_t));

	/* Check if `signo' is a member.
	 * NOTE: This call contains the second user-space memory access! */
	result = (usigset->__val[word] & mask) != 0;

	if (result) {
		/* The is the signal is masked, we must tell user-space that we've
		 * checked, and  that the  signal may  be pending  at this  point. */
		if ((atomic_read(&umask->pm_pending.__val[word]) & mask) == 0) {
			atomic_or(&umask->pm_pending.__val[word], mask);
			atomic_or(&umask->pm_flags, USERPROCMASK_FLAG_HASPENDING);
			printk(KERN_DEBUG "[userprocmask:%p] Mark signal %d as pending\n",
			       umask, signo);
		}
	}
	return result;
}
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */


/* NMI Signals (NonMaskableInterrupt)
 * Userspace is unable to block these signals, no matter what they do. */
#undef NMI_SIGNALS_ALL_SAME_WORD
#undef NMI_SIGNALS_IN_WORD0
#if __sigset_word_c(SIGKILL) ==  __sigset_word_c(SIGSTOP)
#define NMI_SIGNALS_ALL_SAME_WORD
#if __sigset_word_c(SIGKILL) ==  0
#define NMI_SIGNALS_IN_WORD0
#endif /* __sigset_word_c(SIGKILL) ==  0 */
#endif /* __sigset_word_c(SIGKILL) ==  __sigset_word_c(SIGSTOP) */


/* Inherit/clear/set SIGKILL and SIGSTOP within a given signal set */
#ifdef NMI_SIGNALS_ALL_SAME_WORD
#define _NMI_SIGNALS_WORD (__sigset_word(SIGKILL))
#define _NMI_SIGNALS_MASK (__sigset_mask(SIGKILL) | __sigset_mask(SIGSTOP))
#define nmiandorset(dst, src) \
	((dst)->__val[_NMI_SIGNALS_WORD] |= (src)->__val[_NMI_SIGNALS_WORD] & _NMI_SIGNALS_MASK)
#define nmidelset(self) \
	((self)->__val[_NMI_SIGNALS_WORD] &= ~_NMI_SIGNALS_MASK)
#define nmiaddset(self) \
	((self)->__val[_NMI_SIGNALS_WORD] |= _NMI_SIGNALS_MASK)
#ifdef NMI_SIGNALS_IN_WORD0
#define nmidelsetword0(p_word) (void)(*(p_word) &= ~_NMI_SIGNALS_MASK)
#else /* NMI_SIGNALS_IN_WORD0 */
#define nmidelsetword0(p_word) (void)0
#endif /* !NMI_SIGNALS_IN_WORD0 */
#define nmidelsetword(p_word, word_index) \
	((word_index) == _NMI_SIGNALS_WORD ? (void)(*(p_word) &= ~_NMI_SIGNALS_MASK) : (void)0)
#else /* NMI_SIGNALS_ALL_SAME_WORD */
#define nmiandorset(dst, src)                                                                               \
	((dst)->__val[__sigset_word(SIGKILL)] |= (src)->__val[__sigset_word(SIGKILL)] & __sigset_mask(SIGKILL), \
	 (dst)->__val[__sigset_word(SIGSTOP)] |= (src)->__val[__sigset_word(SIGSTOP)] & __sigset_mask(SIGSTOP))
#define nmidelset(self)                                                \
	((self)->__val[__sigset_word(SIGKILL)] &= ~__sigset_mask(SIGKILL), \
	 (self)->__val[__sigset_word(SIGSTOP)] &= ~__sigset_mask(SIGSTOP))
#define nmiaddset(self)                                               \
	((self)->__val[__sigset_word(SIGKILL)] |= __sigset_mask(SIGKILL), \
	 (self)->__val[__sigset_word(SIGSTOP)] |= __sigset_mask(SIGSTOP))
#define nmidelsetword(p_word, word_index)                                                             \
	((word_index) == __sigset_word(SIGKILL) ? (void)(*(p_word) &= ~__sigset_mask(SIGKILL)) : (void)0, \
	 (word_index) == __sigset_word(SIGSTOP) ? (void)(*(p_word) &= ~__sigset_mask(SIGSTOP)) : (void)0)
#endif /* !NMI_SIGNALS_ALL_SAME_WORD */
#ifndef nmidelsetword0
#define nmidelsetword0(p_word) nmidelsetword(p_word, 0)
#endif /* !nmidelsetword0 */

/* Check if `signo' is a "non-maskable-interrupt" signal. */
#define isnmi(signo) ((signo) == SIGKILL || (signo) == SIGSTOP)

/* Check if `set' contains any NMI signals */
#define nmiismember(set) (sigismember(set, SIGKILL) || sigismember(set, SIGSTOP))



/* Make sure that casting boolean expressions to
 * integers  yields the expected results of 0/1.
 * This is assumed by code below */
static_assert(SIGMASK_ISMASKED_NOPF_NO == (int)false);
static_assert(SIGMASK_ISMASKED_NOPF_NO == (int)(10 == 0));
static_assert(SIGMASK_ISMASKED_NOPF_YES == (int)true);
static_assert(SIGMASK_ISMASKED_NOPF_YES == (int)(10 != 0));

#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
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
	NCX struct userprocmask *um;
	NCX UNCHECKED sigset_t *current_sigmask;
	struct mman *mymm, *threadmm;
	/* NOTE: This read is safe, since `self' is running on  THIS_CPU,
	 *       the `this_userprocmask_address'  field is  write-private
	 *       to `self', and preemption  is disabled, meaning that  we
	 *       know that nothing can change `this_userprocmask_address' */
	um = FORTASK(self, this_userprocmask_address);

	/* Make sure we're operating in the context of  `self->t_mman'
	 * Note that we don't use task_setmman() to change ours, since
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
	NCX struct userprocmask *um;
	NCX UNCHECKED sigset_t *current_sigmask;
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
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */


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
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
PUBLIC NOBLOCK_IF(!allow_blocking_and_exception_when_self_is_THIS_TASK || self != THIS_TASK)
ATTR_PURE WUNUSED NONNULL((1)) int FCALL
sigmask_ismasked_in(struct task *__restrict self, signo_t signo,
                    bool allow_blocking_and_exception_when_self_is_THIS_TASK)
		THROWS(E_SEGFAULT)
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW(FCALL sigmask_ismasked_in)(struct task *__restrict self, signo_t signo)
#define sigmask_ismasked_in(self, signo, _) sigmask_ismasked_in(self, signo)
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
{
	int result;
	uintptr_t thread_flags = atomic_read(&self->t_flags);
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
	if (thread_flags & (TASK_FVFORK | TASK_FUSERPROCMASK))
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
	if (thread_flags & TASK_FVFORK)
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
	{
		/* Special case for NMI signals, which are assumed to always be
		 * unmasked, no matter what the thread's userprocmask may  say. */
		if (isnmi(signo))
			return SIGMASK_ISMASKED_NOPF_NO; /* Cannot be masked. */

		/* A vfork'd thread always has all signals masked. */
#ifndef CONFIG_HAVE_KERNEL_USERPROCMASK
		return SIGMASK_ISMASKED_NOPF_YES;
#else /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
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
		 *     atomic_read(&FORTASK(self,  this_userprocmask_address)->pm_sigmask)
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
		if (atomic_read(&self->t_cpu) == THIS_CPU) {
			/* When `self' is running on the same CPU as we are, then we can
			 * try  to gain  insight into  their user-space  memory state by
			 * disabling preemption, temporarily switching page directories,
			 * and finally using memcpy_nopf() to access memory. */
			preemption_flag_t was;
			preemption_pushoff(&was);
			/* Check again, now that our CPU won't change. */
			if likely(atomic_read(&self->t_cpu) == THIS_CPU)
				result = sigmask_ismasked_in_userprocmask_nopf(self, signo);
			preemption_pop(&was);
		}
		return result;
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */
	}

	/* Use the normal per-thread kernel sigmask. */
	result = (int)!!sigismember(&FORTASK(self, this_kernel_sigmask), signo);
	assertf(isnmi(signo)
	        ? result == SIGMASK_ISMASKED_NOPF_NO
	        : true,
	        "These 2 signals must never appear as masked in `this_kernel_sigmask'");
	return result;
}

/* Same as `sigmask_ismasked_in()', but for the calling thread.
 * This function doesn't perform  any special checks for  VFORK
 * or  USERPROCMASK  scenarios.  Use  `sigmask_ismasked()'   if
 * these situations must also be handled. */
#define this_kernel_sigmask_ismember(signo) \
	sigismember(&THIS_KERNEL_SIGMASK, signo)

/* Check if a given `signo' is currently masked. This function
 * handles all of the special cases, including TASK_VFORK  and
 * TASK_USERPROCMASK, as well as making sure that SIGSTOP  and
 * SIGKILL are never considered to be masked. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
PUBLIC ATTR_PURE WUNUSED bool FCALL
sigmask_ismasked(signo_t signo) THROWS(E_SEGFAULT)
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
PUBLIC NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL sigmask_ismasked)(signo_t signo)
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
{
	bool result;
	uintptr_t thread_flags;
	thread_flags = PERTASK_GET(this_task.t_flags);
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
	if (thread_flags & (TASK_FVFORK | TASK_FUSERPROCMASK))
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
	if (thread_flags & TASK_FVFORK)
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
	{
		/* Always behave as though this was `sigmask_full'. */
		if (isnmi(signo))
			return false; /* Cannot be masked. */

		/* A vfork'd thread always has all signals masked. */
#ifndef CONFIG_HAVE_KERNEL_USERPROCMASK
		return true;
#else /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
		if unlikely(thread_flags & TASK_FVFORK)
			return true;
		/* The nitty-gritty case: The thread is using a userprocmask... */
		result = usersigmask_ismasked_chk(signo);
		return result;
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */
	}
	result = this_kernel_sigmask_ismember(signo) != 0;
	return result;
}


#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
/* Non-faulting version of `sigmask_ismasked()'.
 * @return: * : One of `SIGMASK_ISMASKED_NOPF_*' */
PUBLIC NOBLOCK ATTR_PURE WUNUSED int
NOTHROW(FCALL sigmask_ismasked_nopf)(signo_t signo) {
	uintptr_t thread_flags;
	thread_flags = PERTASK_GET(this_task.t_flags);
	if (thread_flags & (TASK_FVFORK | TASK_FUSERPROCMASK)) {
		if (isnmi(signo))
			return SIGMASK_ISMASKED_NOPF_NO; /* Cannot be masked. */

		/* A vfork'd thread always has all signals masked. */
		if unlikely(thread_flags & TASK_FVFORK)
			return SIGMASK_ISMASKED_NOPF_YES;

		/* The nitty-gritty case: The thread is using a userprocmask... */
		return sigmask_ismasked_in_my_userprocmask_nopf(signo);
	}
	if (this_kernel_sigmask_ismember(signo))
		return SIGMASK_ISMASKED_NOPF_YES;
	return SIGMASK_ISMASKED_NOPF_NO;
}
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */


/* Prepare the calling thread for a sigsuspend operation.
 *
 * This  function must be  called during the  setup phase of a
 * system call that intends to use `task_serve_with_sigmask()' */
PUBLIC NOBLOCK void
NOTHROW(FCALL sigmask_prepare_sigsuspend)(void) {
	struct task *me = THIS_TASK;

	/* Indicate that we want to receive wake-ups for masked signals.
	 * NOTE: We also set the RPC flag in case there are pending
	 *       RPCs  that would normally be considered as masked! */
	atomic_or(&me->t_flags, (TASK_FWAKEONMSKRPC | TASK_FRPC));

	/* This will clear `TASK_FWAKEONMSKRPC', as well as
	 * perform a check for signals not in `these' which
	 * may have also appeared in the mean time prior to
	 * returning to user-space. */
	userexcept_sysret_inject_self();

	/* Because we may have  come here from `userexcept_handler()',  we
	 * have to do some additional work in order to make sure that  all
	 * thread-directed RPCs are  active. Otherwise, we  won't be  able
	 * to pick up on RPCs that were already present before the  system
	 * call, but were masked by the caller's *actual* signal mask, and
	 * subsequently marked as INACTIVE.
	 *
	 * Because a different signal mask is used below, we have to make
	 * sure that `task_serve()' won't skip over them.
	 *
	 * Normally,  RPC handlers are allowed to go tinker with the internals
	 * of other pending RPCs, but because we only get here if the RPC gets
	 * triggered as `RPC_REASONCTX_SYSCALL', we  have a much more  lenient
	 * execution context which doesn't even require us to return normally.
	 * The only thing we have to guaranty in this scenario, is to  respect
	 * the  setting of `userexcept_sysret_inject_self()' (which we already
	 * do unconditionally), so that it could clear the INACTIVE flags just
	 * like we do here, whilst also executing SYSRET RPCs, all of which we
	 * want to be able to interrupt our `task_serve()' below!
	 *
	 * s.a.: (copied verbatim from "misc/except-handler-userexcept.c.inl"):
	 * """
	 * WARNING: User-space RPCs in `restore' may still be marked as INACTIVE
	 *          at this point. This is normally  OK, but in case the  system
	 *          call doesn't want that, it  has to clear the INACTIVE  flags
	 *          itself. -- This has to be done in the case of  sigsuspend()!
	 * """
	 */
	{
		struct pending_rpc *rpcs;
		/* NOTE: No need to steal pending  RPCs. -- These are private  to
		 *       our thread, and while other  threads are allowed to  add
		 *       more (hence the  atomic_read from the  list head),  only
		 *       we are allowed to remove them, meaning that we know that
		 *       (other than the list head), none of the pointers between
		 *       elements can change.
		 * Also note that in case another thread adds a new RPC, it will
		 * come  without the INACTIVE  flag, so it'll  already be in the
		 * state we want all of our RPCs to be in! */
		rpcs = atomic_read(&FORTASK(me, this_rpcs.slh_first));
		assertf(rpcs != THIS_RPCS_TERMINATED, "How did we get here from task_exit()?");
		for (; rpcs; rpcs = SLIST_NEXT(rpcs, pr_link))
			rpcs->pr_flags &= ~_RPC_CONTEXT_INACTIVE;
	}
}


/* Set  the given signal mask as active for the calling thread.
 * Primarily used for  `sigreturn(2)', this  function has  some
 * special handling to ensure that `SIGKILL' and `SIGSTOP'  are
 * not masked, whilst still ensuring not to modify a  potential
 * userprocmask unless absolutely necessary (including the case
 * where the userprocmask indicates that SIGKILL or SIGSTOP are
 * currently masked (which wouldn't actually be the case))
 *
 * @return: true:  Changes were made to the caller's signal mask. In
 *                 this case, the caller should make another call to
 *                 `userexcept_sysret_inject_self()'  in  order   to
 *                 check for pending signals upon the next return to
 *                 user-space (unless it  is known  that the  signal
 *                 mask didn't get less restrictive)
 * @return: false: The caller's signal mask remains unchanged. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
PUBLIC NONNULL((1)) bool FCALL
sigmask_setmask(sigset_t const *__restrict mask)
		THROWS(E_SEGFAULT)
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL sigmask_setmask)(sigset_t const *__restrict mask)
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
{
	bool changed;
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
	if (PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
		NCX struct userprocmask *um;
		NCX UNCHECKED sigset_t *umask;
		sigset_t new_umask;
		sigset_t current_umask;
		size_t umasksize;
		um        = PERTASK_GET(this_userprocmask_address);
		umask     = um->pm_sigmask;
		umasksize = um->pm_sigsize;
		COMPILER_READ_BARRIER();
		validate_readwrite(umask, umasksize);
		if (umasksize > sizeof(sigset_t))
			umasksize = sizeof(sigset_t);

		/* Load the current userprocmask */
		memset(mempcpy(&current_umask, umask, umasksize),
		       0xff, sizeof(sigset_t) - umasksize);

		/* Because the userprocmask may  point to read-only memory,  only
		 * write memory if contents have actually changed (otherwise, the
		 * signal mask restore can be considered a no-op)
		 *
		 * Keep the old setting for SIGKILL and SIGSTOP (they're state is
		 * ignored within the userprocmask, but  try not to change  their
		 * actual state, so-as not to  accidentally write to a  read-only
		 * mask blob) */
		if (nmiismember(&current_umask)) {
			mask = (sigset_t *)memcpy(&new_umask, mask, sizeof(sigset_t));
			nmiandorset(&new_umask, &current_umask);
		}

		/* Check if the masks differ. */
		changed = bcmp(&current_umask, mask, sizeof(sigset_t)) != 0;

		/* If changes are present, write-back the new mask.
		 * Note that in this case, we don't modify extended
		 * mask bits which may appear in the userprocmask.
		 *
		 * We only write signals bits present within the actually used range. */
		if (changed)
			memcpy(umask, mask, umasksize);
	} else
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
	{
		sigset_t *mymask;
		mymask  = &THIS_KERNEL_SIGMASK;
		changed = bcmp(mymask, mask, sizeof(sigset_t)) != 0;
		if (changed)
			memcpy(mymask, mask, sizeof(sigset_t));
	}
	return changed;
}

/* Helper wrapper for `sigmask_setmask()' that takes a signal-set from user-space. */
PUBLIC bool FCALL
sigmask_setmask_from_user(NCX sigset_t const *mask, size_t size)
		THROWS(E_SEGFAULT) {
	sigset_t newmask;
	if (size > sizeof(sigset_t))
		size = sizeof(sigset_t);
	memset(mempcpy(&newmask, mask, size),
	       0xff, sizeof(sigset_t) - size);

	/* Never mask NMI signals! */
	nmidelset(&newmask);

	/* Apply the new signal mask. */
	return sigmask_setmask(&newmask);
}


/* Get the calling thread's current signal mask. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
PUBLIC NONNULL((1)) void FCALL
sigmask_getmask(sigset_t *__restrict mask)
		THROWS(E_SEGFAULT) {
	if (PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
		NCX struct userprocmask *um;
		NCX UNCHECKED sigset_t *umask;
		size_t umasksize;
		um        = PERTASK_GET(this_userprocmask_address);
		umask     = um->pm_sigmask;
		umasksize = um->pm_sigsize;
		COMPILER_READ_BARRIER();
		validate_readwrite(umask, umasksize);
		if (umasksize > sizeof(sigset_t))
			umasksize = sizeof(sigset_t);
		memset(mempcpy(mask, umask, umasksize),
		       0xff, sizeof(sigset_t) - umasksize);
		COMPILER_BARRIER();

		/* Ignore user-space trying to mask these signals. */
		nmidelset(mask);
	} else {
		memcpy(mask, &THIS_KERNEL_SIGMASK, sizeof(sigset_t));
	}
}
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */

/* Return the first word from the calling thread's signal mask. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
PUBLIC ATTR_PURE WUNUSED ulongptr_t FCALL
sigmask_getmask_word0(void) THROWS(E_SEGFAULT) {
	union {
		ulongptr_t word;
		byte_t bytes[sizeof(ulongptr_t)];
	} result;
	if (PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
		NCX struct userprocmask *um;
		NCX UNCHECKED sigset_t *umask;
		size_t umasksize;
		um        = PERTASK_GET(this_userprocmask_address);
		umask     = um->pm_sigmask;
		umasksize = um->pm_sigsize;
		COMPILER_READ_BARRIER();
		validate_readwrite(umask, umasksize);
		if likely(umasksize >= sizeof(result.bytes)) {
			result.word = UNALIGNED_GET(&umask->__val[0]);
		} else {
			result.word = (ulongptr_t)-1;
			memcpy(result.bytes, &umask->__val[0], umasksize);
		}
		COMPILER_BARRIER();

		/* Ignore user-space trying to mask NMI signals. */
		nmidelsetword0(&result.word);
	} else {
		result.word = PERTASK_GET(this_kernel_sigmask.__val[0]);
	}
	return result.word;
}
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */

/* Return the `index' word from the calling thread's signal mask.
 * @param: index: Index into the caller's sigmask mask sigset (`< SIGSET_NWORDS') */
#if defined(CONFIG_HAVE_KERNEL_USERPROCMASK) && SIGSET_NWORDS > 1
PUBLIC ATTR_PURE WUNUSED ulongptr_t FCALL
sigmask_getmask_word(size_t index)
		THROWS(E_SEGFAULT) {
	assert(index < SIGSET_NWORDS);
	union {
		ulongptr_t word;
		byte_t bytes[sizeof(ulongptr_t)];
	} result;
	if (PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
		NCX struct userprocmask *um;
		NCX UNCHECKED sigset_t *umask;
		size_t umasksize, skip;
		um        = PERTASK_GET(this_userprocmask_address);
		umask     = um->pm_sigmask;
		umasksize = um->pm_sigsize;
		COMPILER_READ_BARRIER();
		validate_readwrite(umask, umasksize);
		skip = index * sizeof(ulongptr_t);
		if likely(umasksize >= skip + sizeof(ulongptr_t)) {
			result.word = UNALIGNED_GET(&umask->__val[index]);
		} else if likely(umasksize > skip) {
			result.word = (ulongptr_t)-1;
			memcpy(result.bytes, &umask->__val[0], umasksize - skip);
		} else {
			result.word = (ulongptr_t)-1;
		}
		COMPILER_BARRIER();

		/* Ignore user-space trying to mask NMI signals. */
		nmidelsetword(&result.word, index);
	} else {
		result.word = PERTASK_GET(this_kernel_sigmask.__val[0]);
	}
	return result.word;
}
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK && SIGSET_NWORDS > 1 */

#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
/* Copy masking bits for `SIGKILL' and `SIGSTOP' from `src' to `dst',
 * and return the new value for `dst'. Both `dst' and `src' are  mask
 * words who's least significant bit represents `signal_word_base'. */
PRIVATE ATTR_CONST WUNUSED ulongptr_t
NOTHROW(FCALL copy_nmi_signal_mask_bits)(ulongptr_t dst,
                                         ulongptr_t src,
                                         signo_t signal_word_base) {
#define IS_SIGNAL_IN_RANGE(signo)   ((signo)-1 >= signal_word_base && (signo)-1 < (signal_word_base + (sizeof(ulongptr_t) * NBBY)))
#define RELATIVE_SIGNAL_MASK(signo) ((ulongptr_t)1 << (((signo)-1) - signal_word_base))
	ulongptr_t copymask = 0;
	if (IS_SIGNAL_IN_RANGE(SIGKILL))
		copymask |= RELATIVE_SIGNAL_MASK(SIGKILL);
	if (IS_SIGNAL_IN_RANGE(SIGSTOP))
		copymask |= RELATIVE_SIGNAL_MASK(SIGSTOP);
	dst &= ~copymask;      /* Clear bits to-be inherited from `src' */
	dst |= src & copymask; /* Copy bits inherited from `src' */
	return dst;
#undef RELATIVE_SIGNAL_MASK
#undef IS_SIGNAL_IN_RANGE
}
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */

/* Or the given set of signals `these' with the calling thread's
 * signal mask, thus effectively blocking all of those  signals. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
PUBLIC NONNULL((1)) void FCALL
sigmask_blockmask(sigset_t const *__restrict these)
		THROWS(E_SEGFAULT)
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sigmask_blockmask)(sigset_t const *__restrict these)
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
{
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
	if (PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
		signo_t sigbase;
		NCX struct userprocmask *um;
		NCX UNCHECKED sigset_t *umask;
		size_t umasksize;
		um        = PERTASK_GET(this_userprocmask_address);
		umask     = um->pm_sigmask;
		umasksize = um->pm_sigsize;
		COMPILER_READ_BARRIER();
		validate_readwrite(umask, umasksize);
		if (umasksize > sizeof(sigset_t))
			umasksize = sizeof(sigset_t);
		sigbase = 0;
		while (umasksize >= sizeof(ulongptr_t)) {
			ulongptr_t word, blck, nwrd;
			word = UNALIGNED_GET((NCX ulongptr_t const *)umask);
			blck = *(ulongptr_t const *)these;
			nwrd = word | blck;
			if (nwrd != word) {
				nwrd = copy_nmi_signal_mask_bits(nwrd, word, sigbase);
				if (nwrd != word)
					UNALIGNED_SET((NCX ulongptr_t *)umask, nwrd);
			}
			umask = (NCX sigset_t *)((byte_t *)umask + sizeof(ulongptr_t));
			these = (sigset_t const *)((byte_t const *)these + sizeof(ulongptr_t));
			umasksize -= sizeof(ulongptr_t);
			sigbase += sizeof(ulongptr_t) * NBBY;
		}
		while (umasksize) {
			byte_t word, blck, nwrd;
			word = *(NCX byte_t const *)umask;
			blck = *(byte_t const *)these;
			nwrd = word | blck;
			if (nwrd != word) {
				nwrd = (byte_t)copy_nmi_signal_mask_bits(nwrd, word, sigbase);
				if (nwrd != word)
					*(NCX byte_t *)umask = nwrd;
			}
			umask = (NCX sigset_t *)((byte_t *)umask + 1);
			these = (sigset_t const *)((byte_t const *)these + 1);
			umasksize -= 1;
		}
	} else
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
	{
		sigset_t *mymask;
		mymask = &THIS_KERNEL_SIGMASK;
		sigorset(mymask, mymask, these);
	}
}



/* Unblock the given set of signals `these' within the calling thread's signal mask.
 * @return: true:  Changes were made to the caller's signal mask. In
 *                 this case, the caller should make another call to
 *                 `userexcept_sysret_inject_self()'  in  order   to
 *                 check for pending signals upon the next return to
 *                 user-space (unless it  is known  that the  signal
 *                 mask didn't get less restrictive)
 * @return: false: The caller's signal mask remains unchanged. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
PUBLIC NONNULL((1)) bool FCALL
sigmask_unblockmask(sigset_t const *__restrict these)
		THROWS(E_SEGFAULT)
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL sigmask_unblockmask)(sigset_t const *__restrict these)
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
{
	bool result = false;
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
	if (PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
		signo_t sigbase;
		NCX struct userprocmask *um;
		NCX UNCHECKED sigset_t *umask;
		size_t umasksize;
		um        = PERTASK_GET(this_userprocmask_address);
		umask     = um->pm_sigmask;
		umasksize = um->pm_sigsize;
		COMPILER_READ_BARRIER();
		validate_readwrite(umask, umasksize);
		if (umasksize > sizeof(sigset_t))
			umasksize = sizeof(sigset_t);
		sigbase = 0;
		while (umasksize >= sizeof(ulongptr_t)) {
			ulongptr_t word, blck, nwrd;
			word = UNALIGNED_GET((NCX ulongptr_t const *)umask);
			blck = *(ulongptr_t const *)these;
			nwrd = word & ~blck;
			if (nwrd != word) {
				nwrd = copy_nmi_signal_mask_bits(nwrd, word, sigbase);
				if (nwrd != word) {
					UNALIGNED_SET((NCX ulongptr_t *)umask, nwrd);
					result = true;
				}
			}
			umask = (NCX sigset_t *)((byte_t *)umask + sizeof(ulongptr_t));
			these = (sigset_t const *)((byte_t const *)these + sizeof(ulongptr_t));
			umasksize -= sizeof(ulongptr_t);
			sigbase += sizeof(ulongptr_t) * NBBY;
		}
		while (umasksize) {
			byte_t word, blck, nwrd;
			word = *(NCX byte_t const *)umask;
			blck = *(byte_t const *)these;
			nwrd = word & ~blck;
			if (nwrd != word) {
				nwrd = (byte_t)copy_nmi_signal_mask_bits(nwrd, word, sigbase);
				if (nwrd != word) {
					*(NCX byte_t *)umask = nwrd;
					result = true;
				}
			}
			umask = (NCX sigset_t *)((byte_t *)umask + 1);
			these = (sigset_t const *)((byte_t const *)these + 1);
			umasksize -= 1;
		}
	} else
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
	{
		size_t i;
		sigset_t *mymask;
		mymask = &THIS_KERNEL_SIGMASK;
		for (i = 0; i < SIGSET_NWORDS; ++i) {
			ulongptr_t word, nwrd;
			word = mymask->__val[i];
			nwrd = word & ~these->__val[i];
			if (word == nwrd)
				continue;
			mymask->__val[i] = nwrd;
			result = true;
		}
	}
	return result;
}



/* Combination of `sigmask_getmask()' and `sigmask_setmask()'
 *
 * @return: true:  Changes were made to the caller's signal mask. In
 *                 this case, the caller should make another call to
 *                 `userexcept_sysret_inject_self()'  in  order   to
 *                 check for pending signals upon the next return to
 *                 user-space (unless it  is known  that the  signal
 *                 mask didn't get less restrictive)
 * @return: false: The caller's signal mask remains unchanged. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
PUBLIC NONNULL((1, 2)) bool FCALL
sigmask_getmask_and_setmask(sigset_t *__restrict oldmask,
                            sigset_t const *__restrict newmask)
		THROWS(E_SEGFAULT)
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
PUBLIC NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL sigmask_getmask_and_setmask)(sigset_t *__restrict oldmask,
                                           sigset_t const *__restrict newmask)
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
{
	bool result;
	assert(!nmiismember(newmask));
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
	if (PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
		NCX struct userprocmask *um;
		NCX UNCHECKED sigset_t *umask;
		size_t umasksize;
		um        = PERTASK_GET(this_userprocmask_address);
		umask     = um->pm_sigmask;
		umasksize = um->pm_sigsize;
		COMPILER_READ_BARRIER();
		validate_readwrite(umask, umasksize);
		if (umasksize > sizeof(sigset_t))
			umasksize = sizeof(sigset_t);
		memset(mempcpy(oldmask, umask, umasksize), 0xff,
		       sizeof(sigset_t) - umasksize);
		result = bcmp(newmask, oldmask, sizeof(sigset_t)) != 0;
		if (result) {
			/* Check if the mask still contains changes (but keep the state of change SIGKILL or SIGSTOP) */
			sigset_t used_newmask;
			memcpy(&used_newmask, newmask, sizeof(sigset_t));
			nmiandorset(&used_newmask, oldmask);
			result = bcmp(&used_newmask, oldmask, sizeof(sigset_t)) != 0;
			if (result) {
				/* Write-back modified words into user-space. */
				memcpy(umask, &used_newmask, umasksize);
			}
		}

		/* Don't tell the caller if these were masked in the userprocmask. */
		nmidelset(oldmask);
	} else
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
	{
		sigset_t *mymask = &THIS_KERNEL_SIGMASK;
		memcpy(oldmask, mymask, sizeof(sigset_t)); /* Get old mask */
		memcpy(mymask, newmask, sizeof(sigset_t)); /* Set new mask */
		result = bcmp(oldmask, newmask, sizeof(sigset_t)) != 0;
	}
	return result;
}



/* Combination of `sigmask_getmask()' and `sigmask_blockmask()'
 * @return: true:  Changes were made to the caller's signal mask.
 * @return: false: The caller's signal mask remains unchanged. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
PUBLIC NONNULL((1, 2)) bool FCALL
sigmask_getmask_and_blockmask(sigset_t *__restrict oldmask,
                              sigset_t const *__restrict these)
		THROWS(E_SEGFAULT)
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
PUBLIC NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL sigmask_getmask_and_blockmask)(sigset_t *__restrict oldmask,
                                             sigset_t const *__restrict these)
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
{
	bool result;
	assert(!nmiismember(these));
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
	if (PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
		sigset_t newmask;
		NCX struct userprocmask *um;
		NCX UNCHECKED sigset_t *umask;
		size_t umasksize;
		um        = PERTASK_GET(this_userprocmask_address);
		umask     = um->pm_sigmask;
		umasksize = um->pm_sigsize;
		COMPILER_READ_BARRIER();
		validate_readwrite(umask, umasksize);
		if (umasksize > sizeof(sigset_t))
			umasksize = sizeof(sigset_t);
		memset(mempcpy(oldmask, umask, umasksize), 0xff,
		       sizeof(sigset_t) - umasksize);
		sigorset(&newmask, oldmask, these);
		result = bcmp(&newmask, oldmask, sizeof(sigset_t)) != 0;
		if (result) {
			/* Write-back modified words into user-space. */
			memcpy(umask, &newmask, umasksize);
		}

		/* Don't tell the caller if these were masked in the userprocmask. */
		nmidelset(oldmask);
	} else
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
	{
		sigset_t *mymask = &THIS_KERNEL_SIGMASK;
		memcpy(oldmask, mymask, sizeof(sigset_t));
		sigorset(mymask, mymask, these);
		result = bcmp(oldmask, mymask, sizeof(sigset_t)) != 0;
	}
	return result;
}



/* Combination of `sigmask_getmask()' and `sigmask_unblockmask()'
 * @return: true:  Changes were made to the caller's signal mask. In
 *                 this case, the caller should make another call to
 *                 `userexcept_sysret_inject_self()'  in  order   to
 *                 check for pending signals upon the next return to
 *                 user-space (unless it  is known  that the  signal
 *                 mask didn't get less restrictive)
 * @return: false: The caller's signal mask remains unchanged. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
PUBLIC NONNULL((1, 2)) bool FCALL
sigmask_getmask_and_unblockmask(sigset_t *__restrict oldmask,
                                sigset_t const *__restrict these)
		THROWS(E_SEGFAULT)
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
PUBLIC NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL sigmask_getmask_and_unblockmask)(sigset_t *__restrict oldmask,
                                               sigset_t const *__restrict these)
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
{
	bool result;
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
	if (PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
		sigset_t newmask;
		NCX struct userprocmask *um;
		NCX UNCHECKED sigset_t *umask;
		size_t umasksize;
		um        = PERTASK_GET(this_userprocmask_address);
		umask     = um->pm_sigmask;
		umasksize = um->pm_sigsize;
		COMPILER_READ_BARRIER();
		validate_readwrite(umask, umasksize);
		if (umasksize > sizeof(sigset_t))
			umasksize = sizeof(sigset_t);
		memset(mempcpy(oldmask, umask, umasksize), 0xff,
		       sizeof(sigset_t) - umasksize);
		signandset(&newmask, oldmask, these);

		/* Don't do anything if the only thing that changed are SIGKILL or SIGSTOP
		 * They don't matter in the case of  a userprocmask, and we don't want  to
		 * make any modifications if we don't need to (since the userprocmask  may
		 * reside in read-only memory) */
		nmiandorset(&newmask, oldmask);

		/* Check if changes have been made */
		result = bcmp(&newmask, oldmask, sizeof(sigset_t)) != 0;
		if (result) {
			/* Write-back modified words into user-space. */
			memcpy(umask, &newmask, umasksize);
		}

		/* Don't tell the caller if these were masked in the userprocmask. */
		nmidelset(oldmask);
	} else
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
	{
		sigset_t *mymask = &THIS_KERNEL_SIGMASK;
		memcpy(oldmask, mymask, sizeof(sigset_t));
		signandset(mymask, mymask, these);
		result = bcmp(oldmask, mymask, sizeof(sigset_t)) != 0;
	}
	return result;
}












/************************************************************************/
/* SYSTEM CALLS                                                         */
/************************************************************************/

/************************************************************************/
/* sigprocmask(), rt_sigprocmask()                                      */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_RT_SIGPROCMASK) || \
     defined(__ARCH_WANT_SYSCALL_SIGPROCMASK) ||    \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SIGPROCMASK))
PRIVATE errno_t KCALL
sys_sigprocmask_impl(syscall_ulong_t how,
                     NCX UNCHECKED sigset_t const *set,
                     NCX UNCHECKED sigset_t *oset,
                     size_t sigsetsize) {
	size_t overflow = 0;
	if (sigsetsize > sizeof(sigset_t)) {
		overflow   = sigsetsize - sizeof(sigset_t);
		sigsetsize = sizeof(sigset_t);
	}
	validate_readable_opt(set, sigsetsize);
	validate_writable_opt(oset, sigsetsize);
	if (set == NULL) {
		if (oset != NULL) {
			/* Simply read the current signal mask. */
			sigset_t mask;
			sigmask_getmask(&mask);
			memset(mempcpy(oset, &mask, sigsetsize),
			       0xff, overflow);
		}
	} else {
		switch (how) {

		case SIG_SETMASK: {
			bool changed;
			sigset_t newmask;
			memset(mempcpy(&newmask, set, sigsetsize),
			       0xff, sizeof(sigset_t) - sigsetsize);
			nmidelset(&newmask);
			if (oset) {
				sigset_t oldmask;
				changed = sigmask_getmask_and_setmask(&oldmask, &newmask);
				memset(mempcpy(oset, &oldmask, sigsetsize), 0xff, overflow);
			} else {
				changed = sigmask_setmask(&newmask);
			}
			if (changed)
				userexcept_sysret_inject_self();
		}	break;

		case SIG_BLOCK: {
			sigset_t these;
			memset(mempcpy(&these, set, sigsetsize),
			       0xff, sizeof(sigset_t) - sigsetsize);
			nmidelset(&these);
			if (oset) {
				sigset_t oldmask;
				sigmask_getmask_and_blockmask(&oldmask, &these);
				memset(mempcpy(oset, &oldmask, sigsetsize), 0xff, overflow);
			} else {
				sigmask_blockmask(&these);
			}
		}	break;

		case SIG_UNBLOCK: {
			bool changed;
			sigset_t these;
			/* NOTE: in the case of UNBLOCK, we don't unblock any signals
			 *       which  aren't apart of the caller-given signal mask! */
			bzero(mempcpy(&these, set, sigsetsize),
			      sizeof(sigset_t) - sigsetsize);
			if (oset) {
				sigset_t oldmask;
				changed = sigmask_getmask_and_unblockmask(&oldmask, &these);
				memset(mempcpy(oset, &oldmask, sigsetsize), 0xff, overflow);
			} else {
				changed = sigmask_unblockmask(&these);
			}
			if (changed)
				userexcept_sysret_inject_self();
		}	break;

		default:
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_SIGPROCMASK_HOW,
			      how);
		}
	}
	return -EOK;
}
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_RT_SIGPROCMASK
DEFINE_SYSCALL4(errno_t, rt_sigprocmask, syscall_ulong_t, how,
                NCX UNCHECKED sigset_t const *, set,
                NCX UNCHECKED sigset_t *, oset, size_t, sigsetsize) {
	return sys_sigprocmask_impl(how, set, oset, sigsetsize);
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGPROCMASK */

#ifdef __ARCH_WANT_SYSCALL_SIGPROCMASK
DEFINE_SYSCALL3(errno_t, sigprocmask, syscall_ulong_t, how,
                NCX UNCHECKED struct __old_sigset_struct const *, set,
                NCX UNCHECKED struct __old_sigset_struct *, oset) {
	return sys_sigprocmask_impl(how,
	                            (NCX UNCHECKED sigset_t const *)set,
	                            (NCX UNCHECKED sigset_t *)oset,
	                            sizeof(struct __old_sigset_struct));
}
#endif /* __ARCH_WANT_SYSCALL_SIGPROCMASK */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGPROCMASK
DEFINE_COMPAT_SYSCALL3(errno_t, sigprocmask, syscall_ulong_t, how,
                       NCX UNCHECKED struct __compat_old_sigset_struct const *, set,
                       NCX UNCHECKED struct __compat_old_sigset_struct *, oset) {
	return sys_sigprocmask_impl(how,
	                            (NCX UNCHECKED sigset_t const *)set,
	                            (NCX UNCHECKED sigset_t *)oset,
	                            sizeof(struct __compat_old_sigset_struct));
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGPROCMASK */





/************************************************************************/
/* sgetmask(), ssetmask()                                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SGETMASK
DEFINE_SYSCALL0(uint32_t, sgetmask) {
	COMPILER_IMPURE(); /* Yes, this syscall is pure, but we don't care about it in this case. */
	return (uint32_t)sigmask_getmask_word0();
}
#endif /* __ARCH_WANT_SYSCALL_SGETMASK */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SGETMASK
DEFINE_COMPAT_SYSCALL0(uint32_t, sgetmask) {
	COMPILER_IMPURE(); /* Yes, this syscall is pure, but we don't care about it in this case. */
	return (uint32_t)sigmask_getmask_word0();
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SGETMASK */

#ifdef __ARCH_WANT_SYSCALL_SSETMASK
DEFINE_SYSCALL1(uint32_t, ssetmask, uint32_t, new_sigmask) {
	sigset_t oldmask, newmask;
	sigmask_getmask(&oldmask);
	memcpy(&newmask, &oldmask, sizeof(sigset_t));
	newmask.__val[0] = new_sigmask;
	nmidelset(&newmask);
	if (sigmask_setmask(&newmask))
		userexcept_sysret_inject_self();
	return (uint32_t)oldmask.__val[0];
}
#endif /* __ARCH_WANT_SYSCALL_SSETMASK */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SSETMASK
DEFINE_COMPAT_SYSCALL1(uint32_t, ssetmask, uint32_t, new_sigmask) {
	union {
		sigset_t s;
		uint32_t w;
	} oldmask, newmask;
	sigmask_getmask(&oldmask.s);
	memcpy(&newmask.s, &oldmask, sizeof(sigset_t));
	newmask.w = new_sigmask;
	nmidelset(&newmask.s);
	if (sigmask_setmask(&newmask.s))
		userexcept_sysret_inject_self();
	return oldmask.w;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SSETMASK */







/************************************************************************/
/* rt_sigpending(), sigpending()                                        */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_RT_SIGPENDING
DEFINE_SYSCALL2(errno_t, rt_sigpending,
                NCX UNCHECKED sigset_t *, uset,
                size_t, sigsetsize) {
	sigset_t pending;
	validate_writable(uset, sigsetsize);
	sigemptyset(&pending);

	/* Collect pending signals */
	task_rpc_pending_sigset(&pending);
	proc_rpc_pending_sigset(&pending);

	/* Write back results */
	COMPILER_WRITE_BARRIER();
	if (sigsetsize <= sizeof(sigset_t)) {
		memcpy(uset, &pending, sigsetsize);
	} else {
		bzero(mempcpy(uset, &pending, sizeof(sigset_t)),
		      sigsetsize - sizeof(sigset_t));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGPENDING */

#ifdef __ARCH_WANT_SYSCALL_SIGPENDING
DEFINE_SYSCALL1(errno_t, sigpending,
                NCX UNCHECKED struct __old_sigset_struct *, uset) {
	return sys_rt_sigpending((NCX UNCHECKED sigset_t *)uset, sizeof(struct __old_sigset_struct));
}
#endif /* __ARCH_WANT_SYSCALL_SIGPENDING */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGPENDING
DEFINE_COMPAT_SYSCALL1(errno_t, sigpending,
                       NCX UNCHECKED struct __compat_old_sigset_struct *, uset) {
	return sys_rt_sigpending((NCX UNCHECKED sigset_t *)uset, sizeof(struct __compat_old_sigset_struct));
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGPENDING */




/************************************************************************/
/* rt_sigsuspend(), sigsuspend()                                        */
/************************************************************************/

#if (defined(__ARCH_WANT_SYSCALL_RT_SIGSUSPEND) || \
     defined(__ARCH_WANT_SYSCALL_SIGSUSPEND) ||    \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SIGSUSPEND))
/* This function is also called from arch-specific, optimized syscall routers. */
INTERN ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void FCALL
sys_sigsuspend_impl(struct icpustate *__restrict state,
                    struct rpc_syscall_info *__restrict sc_info,
                    size_t sigsetsize) {
	sigset_t not_these;
	NCX UNCHECKED sigset_t const *unot_these;
	unot_these = (NCX UNCHECKED sigset_t const *)sc_info->rsi_regs[0];
	validate_readable(unot_these, sigsetsize);
	if (sigsetsize > sizeof(sigset_t))
		sigsetsize = sizeof(sigset_t);
	memset(mempcpy(&not_these, unot_these, sigsetsize),
	       0xff, sizeof(sigset_t) - sigsetsize);

	/* These signals cannot be masked. (iow: _always_ wait for these signals) */
	nmidelset(&not_these);

	/* Prepare the calling thread for a sigsuspend() operation. */
	sigmask_prepare_sigsuspend();
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
	sys_sigsuspend_impl(ctx->rc_state, &ctx->rc_scinfo,
	                    (size_t)ctx->rc_scinfo.rsi_regs[1]);
	__builtin_unreachable();
}

DEFINE_SYSCALL2(errno_t, rt_sigsuspend,
                NCX UNCHECKED sigset_t const *, unot_these,
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
	sys_sigsuspend_impl(ctx->rc_state, &ctx->rc_scinfo, sizeof(struct __old_sigset_struct));
	__builtin_unreachable();
}

DEFINE_SYSCALL1(errno_t, sigsuspend,
                NCX UNCHECKED struct __old_sigset_struct const *, unot_these) {
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
	sys_sigsuspend_impl(ctx->rc_state, &ctx->rc_scinfo, sizeof(struct __compat_old_sigset_struct));
	__builtin_unreachable();
}

DEFINE_COMPAT_SYSCALL1(errno_t, sigsuspend,
                       NCX UNCHECKED struct __compat_old_sigset_struct const *, unot_these) {
	(void)unot_these;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_compat_sigsuspend_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGSUSPEND */


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_SIGMASK_C */
