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
#include <kernel/paging.h> /* KERNELSPACE_HIGHMEM */
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/vm.h> /* DEFINE_PERVM_ONEXEC() */
#include <kernel/mman/nopf.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/except-handler.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
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

#include <librpc/rpc.h>

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

/* An empty signal mask used to initialize `this_sigmask' */
PUBLIC struct kernel_sigmask kernel_sigmask_empty = {
	/* .sm_refcnt = */ 2,
	/* .sm_share  = */ 2,
	/* .sm_mask   = */ { { 0 } }
};


#define SIGSET_WORD_C   __UINTPTR_C
#define SIGSET_WORDBITS (__SIZEOF_POINTER__ * NBBY)
#define SIGSET_NUMBITS  (__SIGSET_NWORDS * SIGSET_WORDBITS)


/* A full signal mask (i.e. one that blocks all signals (except for SIGKILL and SIGSTOP)) */
PUBLIC struct kernel_sigmask kernel_sigmask_full = {
	/* .sm_refcnt = */ 2,
	/* .sm_share  = */ 2,
	/* .sm_mask   = */ {{
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
 * Reference to the signal mask (set of signals being blocked) in the current thread. */
PUBLIC ATTR_PERTASK struct kernel_sigmask_arref
this_sigmask = ARREF_INIT(&kernel_sigmask_empty);


#ifdef CONFIG_HAVE_USERPROCMASK
PRIVATE ATTR_PURE WUNUSED bool FCALL
usersigmask_ismasked_chk(signo_t signo) {
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
			printk(KERN_DEBUG "[userprocmask:%p] Mark signal %d as pending\n",
			       umask, signo);
		}
	}
	return result;
}
#endif /* CONFIG_HAVE_USERPROCMASK */




#define SIGMASK_ISMASKED_NO  0 /* The signal isn't masked */
#define SIGMASK_ISMASKED_YES 1 /* The signal is masked */
#ifdef CONFIG_HAVE_USERPROCMASK
/* The signal may be masked, or it may not be, however due  to
 * the target thread running on a different CPU, or using VIO,
 * a faulty pointer, or memory  currently not loaded into  the
 * core for the backing memory of its usersigmask, the calling
 * thread cannot conclusively determine this. */
#define SIGMASK_ISMASKED_MAYBE (-2)
#endif /* !CONFIG_HAVE_USERPROCMASK */

/* Make sure that casting boolean expressions to
 * integers  yields the expected results of 0/1.
 * This is assumed by code below */
STATIC_ASSERT(SIGMASK_ISMASKED_NO == (int)false);
STATIC_ASSERT(SIGMASK_ISMASKED_NO == (int)(10 == 0));
STATIC_ASSERT(SIGMASK_ISMASKED_YES == (int)true);
STATIC_ASSERT(SIGMASK_ISMASKED_YES == (int)(10 != 0));

#ifdef CONFIG_HAVE_USERPROCMASK
/* Try  to  switch page  directory to  that of  `self', and  make use
 * of memcpy_nopf()  to  try  to  read  its  user-space  userprocmask
 * to  determine  if the  given  `signo' is  currently  being masked.
 * If any of these steps fail, simply return `SIGMASK_ISMASKED_MAYBE'
 * NOTE: The caller is responsible to ensure that `self->t_cpu == THIS_CPU',
 *       as well as that preemption has been disabled. */
PRIVATE NOBLOCK NOPREEMPT ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW(FCALL sigmask_ismasked_in_userprocmask_nopf)(struct task *__restrict self,
                                                     signo_t signo) {
	int result = SIGMASK_ISMASKED_MAYBE;
	USER CHECKED struct userprocmask *um;
	USER UNCHECKED sigset_t *current_sigmask;
	struct vm *myvm, *threadvm;
	/* NOTE: This read is safe, since `self' is running on  THIS_CPU,
	 *       the `this_userprocmask_address'  field is  write-private
	 *       to `self', and preemption  is disabled, meaning that  we
	 *       know that nothing can change `this_userprocmask_address' */
	um = FORTASK(self, this_userprocmask_address);

	/* Make sure we're operating in the context of `self->t_mman'
	 * Note that we don't use task_setvm() to change our's, since
	 * that function may throw an exception, and would already be
	 * complete overkill for our purposes. */
	myvm     = THIS_MMAN;
	threadvm = self->t_mman;
	if (myvm != threadvm)
		pagedir_set(threadvm->v_pdir_phys);

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

		if (result == SIGMASK_ISMASKED_YES) {
			/* The signal _is_ being masked! */
			if unlikely(!read_nopf(&um->pm_pending.__val[word], &user_sigmask_word)) {
set_maybe_and_return:
				result = SIGMASK_ISMASKED_MAYBE;
				goto done;
			}
			if ((user_sigmask_word & mask) == 0) {
				/* The signal _is_ being masked, but isn't marked as  pending.
				 * As such, we then we still have to turn on the corresponding
				 * bit in `um->pm_pending'! */
#ifdef atomic_or_nopf
				if unlikely(!atomic_or_nopf(&um->pm_pending.__val[word], mask))
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
	/* Switch back to our own VM */
	if (myvm != threadvm)
		pagedir_set(myvm->v_pdir_phys);
	return result;
}
#endif /* CONFIG_HAVE_USERPROCMASK */


/* Check if the given `signo' is currently masked by `self'.
 * @param: allow_blocking_and_exception_when_self_is_THIS_TASK:
 *              Like the argument name says: When self == THIS_TASK,
 *              and this argument is true, then this call is allowed
 *              to block, as well as throw exceptions.
 * @return: * : One of `SIGMASK_ISMASKED_*' (see above) */
#ifdef CONFIG_HAVE_USERPROCMASK
PRIVATE NOBLOCK_IF(!allow_blocking_and_exception_when_self_is_THIS_TASK || self != THIS_TASK)
ATTR_PURE WUNUSED NONNULL((1)) int FCALL
sigmask_ismasked_in(struct task *__restrict self, signo_t signo,
                    bool allow_blocking_and_exception_when_self_is_THIS_TASK)
#else /* CONFIG_HAVE_USERPROCMASK */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) int
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
			return SIGMASK_ISMASKED_NO; /* Cannot be masked. */
		/* A vfork'd thread always has all signals masked. */
#ifndef CONFIG_HAVE_USERPROCMASK
		return SIGMASK_ISMASKED_YES;
#else /* !CONFIG_HAVE_USERPROCMASK */
		if unlikely(thread_flags & TASK_FVFORK)
			return SIGMASK_ISMASKED_YES;
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
		result = SIGMASK_ISMASKED_MAYBE;
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
	sm     = arref_get(&FORTASK(self, this_sigmask));
	result = (int)!!sigismember(&sm->sm_mask, signo);
	decref_unlikely(sm);
	if (result != SIGMASK_ISMASKED_NO &&
	    unlikely(signo == SIGKILL || signo == SIGSTOP))
		result = SIGMASK_ISMASKED_NO; /* Cannot be masked. */
	return result;
}

/* Same as `sigmask_ismasked_in()', but for the calling thread.
 * This function doesn't perform  any special checks for  VFORK
 * or USERPROCMASK scenarios.  Use `sigmask_ismasked_chk()'  if
 * these situations must also be handled. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL sigmask_ismasked)(signo_t signo) {
	bool result;
	struct kernel_sigmask *sm;
	sm     = sigmask_kernel_getrd();
	result = sigismember(&sm->sm_mask, signo);
	return result;
}

/* Same  as `sigmask_ismasked()', but  also handle VFORK and
 * USERPROCMASK scenarios. As such, this function may access
 * user-space memory, which can include VIO memory!
 * NOTE: If  the  thread uses  USERPROCMASK, this  function  will also  mark the
 *       given `signo' as pending within `this_userprocmask_address->pm_pending' */
PRIVATE ATTR_PURE WUNUSED bool FCALL
sigmask_ismasked_chk(signo_t signo) {
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
	result = sigmask_ismasked(signo);
	return result;
}



/* [0..1][valid_if(!TASK_FKERNTHREAD)][lock(PRIVATE(THIS_TASK))]
 * User-space  signal   handlers   for   the   calling   thread. */
PUBLIC ATTR_PERTASK REF struct sighand_ptr *this_sighand_ptr = NULL;

/* Lock for accessing any remote thread's this_sighand_ptr field */
#ifndef CONFIG_NO_SMP
PRIVATE struct atomic_rwlock sighand_ptr_change_lock = ATOMIC_RWLOCK_INIT;
DEFINE_DBG_BZERO_OBJECT(sighand_ptr_change_lock);
#endif /* !CONFIG_NO_SMP */

/* Return the sighand pointer of the given thread. */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) REF struct sighand_ptr *
NOTHROW(FCALL task_getsighand_ptr)(struct task *__restrict thread) {
	pflag_t was;
	REF struct sighand_ptr *result;
	was = PREEMPTION_PUSHOFF();
#ifndef CONFIG_NO_SMP
	while unlikely(!sync_tryread(&sighand_ptr_change_lock))
		task_pause();
#endif /* !CONFIG_NO_SMP */
	assert(FORTASK(thread, this_sighand_ptr));
	result = xincref(FORTASK(thread, this_sighand_ptr));
#ifndef CONFIG_NO_SMP
	sync_endread(&sighand_ptr_change_lock);
#endif /* !CONFIG_NO_SMP */
	PREEMPTION_POP(was);
	return result;
}

/* Exchange the sighand pointer of the calling thread. */
PUBLIC WUNUSED REF struct sighand_ptr *
NOTHROW(FCALL task_setsighand_ptr)(struct sighand_ptr *newsighand_ptr) {
	pflag_t was;
	REF struct sighand_ptr *result;
	was = PREEMPTION_PUSHOFF();
#ifndef CONFIG_NO_SMP
	while unlikely(!sync_trywrite(&sighand_ptr_change_lock))
		task_pause();
#endif /* !CONFIG_NO_SMP */
	result = PERTASK_GET(this_sighand_ptr);
	xincref(newsighand_ptr);
	PERTASK_SET(this_sighand_ptr, newsighand_ptr);
#ifndef CONFIG_NO_SMP
	sync_endwrite(&sighand_ptr_change_lock);
#endif /* !CONFIG_NO_SMP */
	PREEMPTION_POP(was);
	return result;
}



DEFINE_PERTASK_CLONE(clone_posix_signals);
PRIVATE ATTR_USED void KCALL
clone_posix_signals(struct task *__restrict new_thread, uintptr_t flags) {
	/* Clone the current signal mask. */
#ifdef CONFIG_HAVE_USERPROCMASK
	if (PERTASK_GET(this_task.t_flags) & TASK_FUSERPROCMASK) {
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
			/* The static initialization for the kernel-space `this_sigmask' is sufficient in this case! */
			/*FORTASK(new_thread, this_sigmask) = ARREF_INIT(&kernel_sigmask_empty);*/
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
			 * In other words: We must copy `um->pm_sigmask' into `FORTASK(new_thread, this_sigmask)'
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
			arref_init(&FORTASK(new_thread, this_sigmask), new_thread_mask);
		}
	} else
#endif /* CONFIG_HAVE_USERPROCMASK */
	{
		if (sigmask_kernel_getrd() == &kernel_sigmask_empty) {
			/* Nothing to do here! */
		} else {
			REF struct kernel_sigmask *mask;
			struct kernel_sigmask_arref *maskref;
			maskref = &PERTASK(this_sigmask);
			mask    = arref_get(maskref);
			assert(mask != &kernel_sigmask_empty);
			ATOMIC_INC(mask->sm_share);
			COMPILER_WRITE_BARRIER();
			arref_init(&FORTASK(new_thread, this_sigmask), mask); /* Inherit reference. */
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
			assert(!PERTASK_GET(this_sighand_ptr));
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
	mask = arref_ptr(&FORTASK(thread, this_sigmask));
	if (mask != &kernel_sigmask_empty)
		decref(mask);
	xdecref(FORTASK(thread, this_sighand_ptr));
}



/* Return a pointer to the signal mask of the calling thread. */
#ifdef CONFIG_HAVE_USERPROCMASK
PUBLIC WUNUSED USER CHECKED sigset_t *KCALL
sigmask_getrd(void) THROWS(...) {
	if (PERTASK_GET(this_task.t_flags) & TASK_FUSERPROCMASK) {
		USER CHECKED sigset_t *result;
		result = ATOMIC_READ(PERTASK_GET(this_userprocmask_address)->pm_sigmask);
		validate_readable(result, sizeof(sigset_t));
		return result;
	}
	return &sigmask_kernel_getrd()->sm_mask;
}
#endif /* CONFIG_HAVE_USERPROCMASK */

/* Make sure that `this_sigmask' is allocated, and isn't being shared.
 * Then, always return `PERTASK_GET(this_sigmask)' */
PUBLIC WUNUSED ATTR_RETNONNULL struct kernel_sigmask *KCALL
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

		maskref = &PERTASK(this_sigmask);
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
/* Make sure that `this_sigmask' is allocated, and isn't being shared.
 * Then, always return `PERTASK_GET(this_sigmask)'
 * NOTE: When  calling thread has  the `TASK_FUSERPROCMASK' flag set,
 *       then this function will return the address of the currently-
 *       assigned  user-space signal mask,  rather than its in-kernel
 *       counterpart! */
PUBLIC WUNUSED USER CHECKED sigset_t *KCALL
sigmask_getwr(void) THROWS(E_BADALLOC, ...) {
	USER CHECKED sigset_t *result;
	if (PERTASK_GET(this_task.t_flags) & TASK_FUSERPROCMASK) {
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
PUBLIC struct sighand *KCALL
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

PUBLIC ATTR_RETNONNULL struct sighand *KCALL
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


/* Return the default action to perform when faced with `signo' configured as `KERNEL_SIG_DFL'
 * @return: * : One of `KERNEL_SIG_*' (excluding `KERNEL_SIG_DFL' and `KERNEL_SIG_GET') */
PUBLIC NOBLOCK WUNUSED ATTR_CONST user_sighandler_func_t
NOTHROW(KCALL sighand_default_action)(signo_t signo) {
	user_sighandler_func_t result;
	result = KERNEL_SIG_IGN;
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
		result = KERNEL_SIG_CORE;
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
		result = KERNEL_SIG_TERM;
		break;

	case SIGCONT:
		result = KERNEL_SIG_CONT;
		break;

	case SIGSTOP:
	case SIGTSTP:
	case SIGTTIN:
	case SIGTTOU:
		result = KERNEL_SIG_STOP;
		break;

	default: break;
	}
	return result;
}


/* Suspend execution of the calling thread by setting `TASK_FSUSPENDED',
 * and keep  the  thread  suspended until  `task_sigcont()'  is  called.
 * This is used to implement SIGSTOP/SIGCONT behavior.
 * @param: stop_code: The stop code (created with `W_STOPCODE(signo)') */
PUBLIC void KCALL task_sigstop(int stop_code)
		THROWS(E_WOULDBLOCK, E_INTERRUPT) {
	struct taskpid *pid = THIS_TASKPID;
	printk(KERN_DEBUG "[sig] Stop execution of thread\n");
	/* NOTE: The write order here is highly important! */
	ATOMIC_STORE(pid->tp_status.w_status, stop_code); /* #1: Set the stop status */
	ATOMIC_OR(THIS_TASK->t_flags, TASK_FSUSPENDED);   /* #2: Set the suspended flag */
	sig_broadcast(&pid->tp_changed);                  /* #3: Broadcast that our status changed. */
	/* #4: Wait for the SUSPENDED flag to go away */
	TRY {
		do {
			task_connect_for_poll(&pid->tp_changed);
			if unlikely(!(ATOMIC_READ(THIS_TASK->t_flags) & TASK_FSUSPENDED)) {
				/* Race condition: we were already re-awoken. */
				task_disconnectall();
				break;
			}
			/* Wait for tp_changed to be broadcast. */
			task_waitfor();
		} while (ATOMIC_READ(THIS_TASK->t_flags) & TASK_FSUSPENDED);
	} EXCEPT {
		/* TODO: What about E_INTERRUPT_USER? - With  this, any kind of  RPC
		 *       or POSIX-SIGNAL would resume execution of a stopped thread! */

		/* Unset the STOP status */
		task_sigcont(THIS_TASK);
		RETHROW();
	}
}

/* Continue execution in `thread', if that thread is currently suspended
 * due to having called `task_sigstop()'
 * WARNING: A race condition exists where `thread' may not have started waiting
 *          yet, in which  case this function  will return `false',  indicating
 *          that the given thread wasn't actually woken.
 * @return: true:  Successfully set `thread' to continue execution
 * @return: false: Either `thread' hasn't started sleeping, or was already continued. */
PUBLIC NOBLOCK bool
NOTHROW(KCALL task_sigcont)(struct task *__restrict thread) {
	struct taskpid *pid;
	if (!(ATOMIC_FETCHAND(thread->t_flags, ~TASK_FSUSPENDED) & TASK_FSUSPENDED))
		return false; /* Not suspended */
	printk(KERN_DEBUG "[sig] Resume execution of thread [tid=%" PRIuN(__SIZEOF_PID_T__) "]\n",
	       task_getrootpid_of_s(thread));
	/* Now we must wake up the thread! */
	pid = FORTASK(thread, this_taskpid);
	ATOMIC_STORE(pid->tp_status.w_status, __W_CONTINUED);
	sig_broadcast(&pid->tp_changed);
	return true;
}




/* Reset  the current handler for `signo' when  `current_action' matches the currently set action.
 * This function should be called by kernel-space signal delivery implementations to implement the
 * behavior of `SIGACTION_SA_RESETHAND' when handling a signal.
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



PRIVATE struct icpustate *FCALL
set_syscall_return(struct icpustate *__restrict state, syscall_ulong_t value) {
#ifdef __x86_64__
	state->ics_gpregs.gp_rax = (u64)(uintptr_t)value;
#elif defined(__i386__)
	state->ics_gpregs.gp_eax = (u32)(uintptr_t)value;
#else
#error Unsupported arch
#endif
	return state;
}



PRIVATE struct icpustate *FCALL
task_sigmask_check_rpc_handler(void *UNUSED(arg),
                               struct icpustate *__restrict state,
                               unsigned int reason,
                               struct rpc_syscall_info const *sc_info) {
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	assert((reason == TASK_RPC_REASON_SYSCALL) == (sc_info != NULL));
	if likely(reason != TASK_RPC_REASON_SHUTDOWN) {
		struct icpustate *new_state;
		/* Check for unmasked signals. */
		new_state = sigmask_check_s(state, sc_info);
		if (reason == TASK_RPC_REASON_SYSCALL ||
		    new_state != TASK_RPC_RESTART_SYSCALL) {
			/* Apply the new signal state.
			 * Note that we return `TASK_RPC_RESTART_SYSCALL' when a system
			 * call got interrupted,  but no pending  signals actually  got
			 * unmasked. */
			state = new_state;
		}
	}
	return state;
}

PRIVATE struct icpustate *FCALL
task_sigmask_check_rpc_handler_after_syscall(void *arg,
                                             struct icpustate *__restrict state,
                                             unsigned int reason,
                                             struct rpc_syscall_info const *sc_info) {
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	assert((reason == TASK_RPC_REASON_SYSCALL) == (sc_info != NULL));
	if likely(reason != TASK_RPC_REASON_SHUTDOWN) {
		struct icpustate *new_state;
		/* Check for unmasked signals. */
		if (reason == TASK_RPC_REASON_SYSCALL)
			state = set_syscall_return(state, (syscall_ulong_t)arg);
		new_state = sigmask_check_s(state, NULL); /* After syscall -> Don't allow for restarting! */
		if (reason == TASK_RPC_REASON_SYSCALL ||
		    new_state != TASK_RPC_RESTART_SYSCALL) {
			/* Apply the new signal state.
			 * Note that we return `TASK_RPC_RESTART_SYSCALL' when a system
			 * call got interrupted,  but no pending  signals actually  got
			 * unmasked. */
			state = new_state;
		}
	}
	return state;
}

/* handle the given signal and update `state' */
PRIVATE struct icpustate *FCALL
handle_signal(struct sigqueue_entry *__restrict info,
              struct icpustate *__restrict state,
              struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	struct kernel_sigaction action;
	struct sighand *myhand;
	struct sighand_ptr *myhandptr;
	/* Figure out what action to handle the signal with. */
again_gethand:
	myhandptr = THIS_SIGHAND_PTR;
	if (!myhandptr)
		goto default_action;
	assert(info->sqe_info.si_signo != 0);
	assert(info->sqe_info.si_signo < NSIG);
	myhand = sighand_ptr_lockread(myhandptr);
	if (!myhand) {
		/* Default action. */
default_action:
		memset(&action, 0, sizeof(action));
		assert(action.sa_handler == KERNEL_SIG_DFL);
	} else {
		memcpy(&action,
		       &myhand->sh_actions[info->sqe_info.si_signo - 1],
		       sizeof(action));
		xincref(action.sa_mask);
		sync_endread(myhand);
	}
	/* Check for default signal action. */
	if (action.sa_handler == KERNEL_SIG_DFL)
		action.sa_handler = sighand_default_action(info->sqe_info.si_signo);

	/* Actually handle the signal */
	switch ((uintptr_t)(void *)action.sa_handler) {

#undef __CCAST
#define __CCAST(T) /* nothing */

	case KERNEL_SIG_IGN:
		xdecref_unlikely(action.sa_mask);
#if 0 /* `SA_RESETHAND' only affects user-space signal handler functions */
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
		    unlikely(!sighand_reset_handler(info->sqe_info.si_signo, &action)))
			goto again_gethand;
#endif
		goto dont_handle;

	case KERNEL_SIG_CORE:
		xdecref_unlikely(action.sa_mask);
		/* Create a coredump */
		coredump_create_for_signal(state, &info->sqe_info);
		THROW(E_EXIT_PROCESS, W_EXITCODE(1, info->sqe_info.si_signo));

	case KERNEL_SIG_TERM:
		xdecref_unlikely(action.sa_mask);
		THROW(E_EXIT_PROCESS, W_EXITCODE(1, info->sqe_info.si_signo));

	case KERNEL_SIG_EXIT:
		xdecref_unlikely(action.sa_mask);
		THROW(E_EXIT_THREAD, W_EXITCODE(1, info->sqe_info.si_signo));

	case KERNEL_SIG_CONT:
		xdecref_unlikely(action.sa_mask);
#if 0 /* `SA_RESETHAND' only affects user-space signal handler functions */
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
		    unlikely(!sighand_reset_handler(info->sqe_info.si_signo, &action)))
			goto again_gethand;
#endif
		/* Continue execution. */
		task_sigcont(THIS_TASK);
		goto dont_handle;

	case KERNEL_SIG_STOP:
		/* XXX: Should we  mask additional  signals by  looking
		 *      at `SIGACTION_SA_NODEFER' and `action.sa_mask'? */
		xdecref_unlikely(action.sa_mask);
#if 0 /* `SA_RESETHAND' only affects user-space signal handler functions */
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
		    unlikely(!sighand_reset_handler(info->sqe_info.si_signo, &action)))
			goto again_gethand;
#endif
		/* Suspend execution. */
		task_sigstop(W_STOPCODE(info->sqe_info.si_signo));
		goto dont_handle;

#undef __CCAST
#define __CCAST(T) (T)
	default: break;
	}
	/* Raise the given signal in user-space. */
	TRY {
		state = sighand_raise_signal(state,
		                             &action,
		                             &info->sqe_info,
		                             sc_info);
	} EXCEPT {
		xdecref_unlikely(action.sa_mask);
		RETHROW();
	}
	xdecref_unlikely(action.sa_mask);
	if unlikely(!state)
		goto again_gethand; /* SIGACTION_SA_RESETHAND... */
dont_handle:
	return state;
}

PRIVATE struct icpustate *FCALL
task_signal_rpc_handler(void *arg,
                        struct icpustate *__restrict state,
                        unsigned int reason,
                        struct rpc_syscall_info const *sc_info) {
	struct sigqueue_entry *info;
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	assert((reason == TASK_RPC_REASON_SYSCALL) == (sc_info != NULL));
	info = (struct sigqueue_entry *)arg;
	assert(info->sqe_info.si_signo != 0);
	assert(info->sqe_info.si_signo < NSIG);
	TRY {
		if likely(reason != TASK_RPC_REASON_SHUTDOWN) {
			/* Make sure that the signal  isn't being masked (the  RPC may have been  delivered
			 * after our current thread masked the signal, meaning that the signal being raised
			 * still triggered the RPC) */
			if unlikely(sigmask_ismasked_chk(info->sqe_info.si_signo)) {
				/* Mark the signal as pending within the current thread. */
				struct sigqueue *pertask_pending;
				struct sigqueue_entry *next;
				pertask_pending = &THIS_SIGQUEUE;
				do {
					next = ATOMIC_READ(pertask_pending->sq_queue);
					if unlikely(next == SIGQUEUE_SQ_QUEUE_TERMINATED)
						goto dont_handle; /* Might happen if the signal was delivered before the thread exited.
						                   * But then again, shouldn't `reason == TASK_RPC_REASON_SHUTDOWN'  be
						                   * in this case? - Anyways: better be safe! */
					info->sqe_next = next;
					COMPILER_WRITE_BARRIER();
				} while (!ATOMIC_CMPXCH_WEAK(pertask_pending->sq_queue, next, info));
				/* Only one thread can ever handle the signal, so use `sig_send()' */
				sig_send(&pertask_pending->sq_newsig);
				/* Restart the interrupted system call without letting userspace know. */
				if (reason == TASK_RPC_REASON_SYSCALL) {
					kfree(info);
					return TASK_RPC_RESTART_SYSCALL;
				}
				goto done;
			}
			/* Actually handle the signal */
			state = handle_signal(info,
			                      state,
			                      sc_info);
		}
	} EXCEPT {
		kfree(info);
		RETHROW();
	}
dont_handle:
	kfree(info);
done:
	return state;
}

PRIVATE struct icpustate *FCALL
task_signal_rpc_handler_after_syscall(void *arg,
                                      struct icpustate *__restrict state,
                                      unsigned int reason,
                                      struct rpc_syscall_info const *sc_info) {
	struct sigqueue_entry *info;
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	assert((reason == TASK_RPC_REASON_SYSCALL) == (sc_info != NULL));
	info = (struct sigqueue_entry *)arg;
	assert(info->sqe_info.si_signo != 0);
	assert(info->sqe_info.si_signo < NSIG);
	TRY {
		if likely(reason != TASK_RPC_REASON_SHUTDOWN) {
			if (reason == TASK_RPC_REASON_SYSCALL)
				state = set_syscall_return(state, (syscall_ulong_t)(uintptr_t)info->sqe_next);
			/* Make sure that the signal  isn't being masked (the  RPC may have been  delivered
			 * after our current thread masked the signal, meaning that the signal being raised
			 * still triggered the RPC. - Schedule the ) */
			if unlikely(sigmask_ismasked_chk(info->sqe_info.si_signo)) {
				/* Mark the signal as pending within the current thread. */
				struct sigqueue *pertask_pending;
				struct sigqueue_entry *next;
				pertask_pending = &THIS_SIGQUEUE;
				do {
					next = ATOMIC_READ(pertask_pending->sq_queue);
					if unlikely(next == SIGQUEUE_SQ_QUEUE_TERMINATED)
						goto dont_handle; /* Might happen if the signal was delivered before the thread exited.
						                   * But then again, shouldn't `reason == TASK_RPC_REASON_SHUTDOWN'  be
						                   * in this case? - Anyways: better be safe! */
					info->sqe_next = next;
					COMPILER_WRITE_BARRIER();
				} while (!ATOMIC_CMPXCH_WEAK(pertask_pending->sq_queue, next, info));
				/* Only one thread can ever handle the signal, so use `sig_send()' */
				sig_send(&pertask_pending->sq_newsig);
				/* Restart the interrupted system call without letting userspace know. */
				if (reason == TASK_RPC_REASON_SYSCALL)
					return TASK_RPC_RESTART_SYSCALL;
				goto done;
			}
			/* Actually handle the signal */
			state = handle_signal(info,
			                      state,
			                      NULL);
		}
	} EXCEPT {
		kfree(info);
		RETHROW();
	}
dont_handle:
	kfree(info);
done:
	return state;
}


/* Deliver the given signal `info' to some thread apart of the process lead by `process_leader'
 * If all threads are masking the given signal, schedule the signal as pending for the process.
 * @return: true:  Success (either delivered, or scheduled as pending).
 * @return: false: The given process has terminated. */
PRIVATE bool KCALL
deliver_signal_to_some_thread_in_process(struct task *__restrict process_leader,
                                         /*inherit(always)*/ struct sigqueue_entry *__restrict info)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INTERRUPT_USER_RPC);


/* Same as `task_signal_rpc_handler', but masked signals as process signals. */
PRIVATE struct icpustate *FCALL
task_process_signal_rpc_handler(void *arg,
                                struct icpustate *__restrict state,
                                unsigned int reason,
                                struct rpc_syscall_info const *sc_info) {
	struct sigqueue_entry *info;
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	assert((reason == TASK_RPC_REASON_SYSCALL) == (sc_info != NULL));
	info = (struct sigqueue_entry *)arg;
	assert(info->sqe_info.si_signo != 0);
	assert(info->sqe_info.si_signo < NSIG);
	TRY {
		if likely(reason != TASK_RPC_REASON_SHUTDOWN) {
			/* Make sure that the signal  isn't being masked (the  RPC may have been  delivered
			 * after our current thread masked the signal, meaning that the signal being raised
			 * still triggered the RPC) */
			if unlikely(sigmask_ismasked_chk(info->sqe_info.si_signo))
				goto deliver_to_some_thread;
			/* Actually handle the signal */
			state = handle_signal(info,
			                      state,
			                      sc_info);
		}
	} EXCEPT {
		kfree(info);
		RETHROW();
	}
	kfree(info);
done:
	return state;
deliver_to_some_thread:
	/* Deliver the signal to some other thread... */
	deliver_signal_to_some_thread_in_process(task_getprocess(),
	                                         info);
	/* Restart the interrupted system call without letting userspace know. */
	if (reason == TASK_RPC_REASON_SYSCALL)
		return TASK_RPC_RESTART_SYSCALL;
	goto done;
}





LOCAL ATTR_NORETURN void KCALL
send_signal_rpc_to_self(/*inherit(always)*/ struct sigqueue_entry *__restrict entry) {
	TRY {
		task_schedule_user_rpc(THIS_TASK,
		                       &task_signal_rpc_handler,
		                       entry,
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
		__builtin_unreachable();
	} EXCEPT {
		if (error_code() != ERROR_CODEOF(E_INTERRUPT_USER_RPC))
			kfree(entry);
		RETHROW();
	}
}

LOCAL ATTR_NORETURN void KCALL
send_signal_rpc_to_self_after_syscall(/*inherit(always)*/ struct sigqueue_entry *__restrict entry,
                                      syscall_ulong_t syscall_result) {
	TRY {
		entry->sqe_next = (struct sigqueue_entry *)(void *)(uintptr_t)syscall_result;
		task_schedule_user_rpc(THIS_TASK,
		                       &task_signal_rpc_handler_after_syscall,
		                       entry,
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
		__builtin_unreachable();
	} EXCEPT {
		if (error_code() != ERROR_CODEOF(E_INTERRUPT_USER_RPC))
			kfree(entry);
		RETHROW();
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL restore_perthread_pending_signals)(struct sigqueue *__restrict myqueue,
                                                 struct sigqueue_entry *__restrict pending) {
	/* Restore all signals pending for the calling thread. */
	if unlikely(!ATOMIC_CMPXCH(myqueue->sq_queue, NULL, pending)) {
		struct sigqueue_entry *last, *next;
		last = pending;
		while (last->sqe_next)
			last = last->sqe_next;
		do {
			next = ATOMIC_READ(myqueue->sq_queue);
			last->sqe_next = next;
			COMPILER_WRITE_BARRIER();
		} while (!ATOMIC_CMPXCH_WEAK(myqueue->sq_queue, next, pending));
	}
}


/* Check for pending signals that are no longer being masked. */
PUBLIC void FCALL
sigmask_check(void) THROWS(E_INTERRUPT, E_WOULDBLOCK) {
	struct sigqueue *myqueue;
	struct process_sigqueue *prqueue;
	struct sigqueue_entry *pending, **piter, *iter;
	myqueue = &THIS_SIGQUEUE;
	/* Temporarily steal all pending per-thread signals. */
	do {
		pending = ATOMIC_READ(myqueue->sq_queue);
		if (!pending)
			goto no_perthread_pending; /* No signals are pending for the calling thread */
		if unlikely(pending == SIGQUEUE_SQ_QUEUE_TERMINATED)
			return; /* Shouldn't happen: The calling thread is currently terminating. */
	} while (!ATOMIC_CMPXCH_WEAK(myqueue->sq_queue, pending, NULL));
	/* Go through pending signals and check if there are any that aren't being masked. */
	iter  = pending;
	piter = &pending;
	do {
		/* XXX: Handle VFORK and USERPROCMASK here, so we can cache user-space memory
		 *      instead of having to re-read  `this_userprocmask_address->pm_sigmask'
		 *      for every signal!
		 * Do this via a new helper function:
		 *    >> NONNULL((1)) struct sigqueue_entry *KCALL
		 *    >> sigqueue_pop_unmasked_entry(struct sigqueue_entry **piter);
		 * That function essentially  just contains  this do...while  loop,
		 * returning NULL if all pending signals are masked, and the popped
		 * signal when one was found that isn't masked. */
		if (!sigmask_ismasked_chk(iter->sqe_info.si_signo)) {
			/* Found one that's not being masked. */
			*piter = iter->sqe_next;
			if (pending)
				restore_perthread_pending_signals(myqueue, pending);
			/* Deliver the signal to ourself */
			send_signal_rpc_to_self(iter);
			break;
		}
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);

	/* Restore all signals pending for the calling thread. */
	restore_perthread_pending_signals(myqueue, pending);
no_perthread_pending:
	/* With per-task signals checked, also check for per-process signals */
	prqueue = &THIS_PROCESS_SIGQUEUE;
	sync_read(&prqueue->psq_lock);
	for (iter = prqueue->psq_queue.sq_queue;
	     iter; iter = iter->sqe_next) {
		/* XXX: Handle VFORK and USERPROCMASK here, so we can cache user-space memory
		 *      instead of having to re-read  `this_userprocmask_address->pm_sigmask'
		 *      for every signal! */
		if (sigmask_ismasked_chk(iter->sqe_info.si_signo))
			continue;
		/* Found an unmasked signal. */
		sync_endread(&prqueue->psq_lock);
		/* Send an RPC to ourself to service the signals.
		 * Note  that we use an RPC including another call to sigmask_check()
		 * here,  since there is  a chance that the  calling thread will mask
		 * the affected signal  before `sigmask_check_s()'  gets invoked,  in
		 * which case if we had stolen the pending signal from the  process's
		 * list  of pending  signal, no other  thread will be  able to handle
		 * to handle the  signal before we  can, and we'd  have to send  even
		 * more  RPCs between all  of the threads  within the current process
		 * before we find someone that's actually able to service the signal! */
		task_schedule_user_rpc(THIS_TASK,
		                       &task_sigmask_check_rpc_handler,
		                       NULL,
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
		__builtin_unreachable();
	}
	sync_endread(&prqueue->psq_lock);
}


/* Same as `sigmask_check()', but if a signal gets triggered, act as though
 * it was being serviced after the current system call has exited with  the
 * given `syscall_result' return value. (preventing system call restarting,
 * or indicating an interrupt exception to user-space)
 * If no signal was triggered, simply return normally.
 * This function is meant to  be used to check  for pending signals after  the
 * original signal mask got restored following the completion of a `pselect()'
 * or `ppoll()' system call. (at which point a previously masked signal should
 * no longer cause the system  call to fail and error  out with -EINTR (to  be
 * restarted), but instead  return its  normal value once  returning from  its
 * associated user-space signal handler (if any))
 * With this in mind, the call order for temporarily overriding the signal mask
 * for the purpose of a single system call looks like this:
 * >> sigset_t oldmask;
 * >> USER CHECKED sigset_t *mymask;
 * >> mymask = sigmask_getwr();
 * >> memcpy(&oldmask, mymask, sizeof(sigset_t));
 * >> TRY {
 * >>     memcpy(mymask, &newmask, sizeof(sigset_t));
 * >> } EXCEPT {
 * >>     memcpy(mymask, &oldmask, sizeof(sigset_t));
 * >>     RETHROW();
 * >> }
 * >> TRY {
 * >>     result = do_my_system_call();
 * >> } EXCEPT {
 * >>     memcpy(mymask, &oldmask, sizeof(sigset_t));
 * >>     sigmask_check_after_except();
 * >>     RETHROW();
 * >> }
 * >> memcpy(mymask, &oldmask, sizeof(sigset_t));
 * >> sigmask_check_after_syscall(result);
 * >> return result;
 */
PUBLIC void FCALL
sigmask_check_after_syscall(syscall_ulong_t syscall_result)
		THROWS(E_INTERRUPT, E_WOULDBLOCK) {
	struct sigqueue *myqueue;
	struct process_sigqueue *prqueue;
	struct sigqueue_entry *pending, **piter, *iter;
	myqueue = &THIS_SIGQUEUE;
	/* Temporarily steal all pending per-thread signals. */
	do {
		pending = ATOMIC_READ(myqueue->sq_queue);
		if (!pending)
			goto no_perthread_pending; /* No signals are pending for the calling thread */
		if unlikely(pending == SIGQUEUE_SQ_QUEUE_TERMINATED)
			return; /* Shouldn't happen: The calling thread is currently terminating. */
	} while (!ATOMIC_CMPXCH_WEAK(myqueue->sq_queue, pending, NULL));
	/* Go through pending signals and check if there are any that aren't being masked. */
	iter  = pending;
	piter = &pending;
	do {
		/* XXX: Handle VFORK and USERPROCMASK here, so we can cache user-space memory
		 *      instead of having to re-read  `this_userprocmask_address->pm_sigmask'
		 *      for every signal! */
		if (!sigmask_ismasked_chk(iter->sqe_info.si_signo)) {
			/* Found one that's not being masked. */
			*piter = iter->sqe_next;
			if (pending)
				restore_perthread_pending_signals(myqueue, pending);
			/* Deliver the signal to ourself */
			send_signal_rpc_to_self_after_syscall(iter, syscall_result);
			__builtin_unreachable();
		}
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);

	/* Restore all signals pending for the calling thread. */
	restore_perthread_pending_signals(myqueue, pending);
no_perthread_pending:
	/* With per-task signals checked, also check for per-process signals */
	prqueue = &THIS_PROCESS_SIGQUEUE;
	sync_read(&prqueue->psq_lock);
	for (iter = prqueue->psq_queue.sq_queue;
	     iter; iter = iter->sqe_next) {
		/* XXX: Handle VFORK and USERPROCMASK here, so we can cache user-space memory
		 *      instead of having to re-read  `this_userprocmask_address->pm_sigmask'
		 *      for every signal! */
		if (sigmask_ismasked_chk(iter->sqe_info.si_signo))
			continue;
		/* Found an unmasked signal. */
		sync_endread(&prqueue->psq_lock);
		/* Send an RPC to ourself to service the signals.
		 * Note  that we use an RPC including another call to sigmask_check()
		 * here,  since there is  a chance that the  calling thread will mask
		 * the affected signal  before `sigmask_check_s()'  gets invoked,  in
		 * which case if we had stolen the pending signal from the  process's
		 * list  of pending  signal, no other  thread will be  able to handle
		 * to handle the  signal before we  can, and we'd  have to send  even
		 * more  RPCs between all  of the threads  within the current process
		 * before we find someone that's actually able to service the signal! */
		task_schedule_user_rpc(THIS_TASK,
		                       &task_sigmask_check_rpc_handler_after_syscall,
		                       (void *)syscall_result,
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
		__builtin_unreachable();
	}
	sync_endread(&prqueue->psq_lock);
}

/* Same as `sigmask_check()', but should be called in order to have
 * user-space handle the currently set  exception in case a  signal
 * handler has to be invoked.
 * See the documentation of `sigmask_check_after_syscall()' for when
 * this function needs to be called. */
PUBLIC void FCALL
sigmask_check_after_except(void)
		THROWS(E_INTERRUPT, E_WOULDBLOCK) {
	/* FIXME: We might get here due to a prior E_INTERRUPT_USER_RPC  exception
	 *        as  the result of `task_sigmask_check_rpc_handler' being sent to
	 *        us. In this case, us repeating the signal-mask check will result
	 *        in that RPC function being invoked twice, which may causes it to
	 *        return with `TASK_RPC_RESTART_SYSCALL'  the second time  around,
	 *        since there won't be any unhandled signals left at that point.
	 * -> There  needs to be some way by which RPCs that get serviced at the
	 *    same time can interact/control each other, because the problem  is
	 *    that one RPC might say that the system call should be  re-started,
	 *    while another expects that it isn't (but rather: that a user-space
	 *    signal handler is executed, or  that the system call returns  with
	 *    an interrupt exception,  or really: anything  else, too, for  that
	 *    matter)
	 *
	 * Solution: An RPC function should be able to indicate that any further
	 *           pending  RPCs should  be invoked  as though  they are being
	 *           serviced not before  returning from a  system call, but  as
	 *           though  execution had already reached user-space, such that
	 *           instead of `reason=TASK_RPC_REASON_SYSCALL',
	 *           `reason=TASK_RPC_REASON_ASYNCUSER' will be used, making it
	 *           impossible for  later  RPCs  to re-start  a  system  call.
	 * Note: I'm not quite sure this would really work in the long run.  The
	 *       RPC system has quite a number of complex control paths, and I'm
	 *       not sure this would work well with all of them.
	 * In reality, the RPC system probably needs a re-write with focus on how
	 * multiple RPCs should interact with each other, where synchronous  RPCs
	 * in general should be split into different groups:
	 *   - ASYNC: Serviced as soon as preemption becomes enabled.
	 *   - SYNC:  Can be serviced  with a  kernel-space CPU  state,
	 *            and can be executed without regards to other RPCs
	 *   - USER:  Serviced before a thread returns back to user-space,
	 *            and must somehow be able to interact with other RPCs
	 *            that came before, and come after it.
	 *
	 * The real problem, I feel, is that I can't come up with short, unambiguous
	 * names for the  different classes  of RPC  callbacks. -  I really  dislike
	 * calling  it  a "user"  RPC, when  there's also  the whole  user-space RPC
	 * thing that's different, yet...
	 * Maybe call it a SYSRET-RPC?
	 */
	NESTED_TRY {
		sigmask_check();
	} EXCEPT {
		/* Rethrow the inner exception and unwind the exception nesting.
		 * This way,  the  more  important of  the  two  exception  will
		 * automatically  be  re-thrown, while  the other  becomes lost. */
		RETHROW();
	}
}


/* Same as `sigmask_check()', but service signals immediately.
 * @param: sc_info: A system call that may be restarted, or NULL.
 * @return: * :                       The updated cpu-state.
 * @return: TASK_RPC_RESTART_SYSCALL: Nothing was handled. */
PUBLIC struct icpustate *FCALL
sigmask_check_s(struct icpustate *__restrict state,
                struct rpc_syscall_info const *sc_info)
		THROWS(E_WOULDBLOCK, E_SEGFAULT) {
	bool did_handle_something = false;
	struct sigqueue *myqueue;
	struct process_sigqueue *prqueue;
	struct sigqueue_entry *pending, **piter, *iter;
	myqueue = &THIS_SIGQUEUE;
	/* Temporarily steal all pending per-thread signals. */
	do {
		pending = ATOMIC_READ(myqueue->sq_queue);
		if (!pending)
			goto no_perthread_pending; /* No signals are pending for the calling thread */
		if unlikely(pending == SIGQUEUE_SQ_QUEUE_TERMINATED)
			return state; /* Shouldn't happen: The calling thread is currently terminating. */
	} while (!ATOMIC_CMPXCH_WEAK(myqueue->sq_queue, pending, NULL));
	/* Go through pending signals and check if there are any that aren't being masked. */
	iter  = pending;
	piter = &pending;
again_iter:
	do {
		/* XXX: Handle VFORK and USERPROCMASK here, so we can cache user-space memory
		 *      instead of having to re-read  `this_userprocmask_address->pm_sigmask'
		 *      for every signal! */
		if (!sigmask_ismasked_chk(iter->sqe_info.si_signo)) {
			/* Found one that's not being masked. */
			*piter = iter->sqe_next;
			if (pending)
				restore_perthread_pending_signals(myqueue, pending);
			/* Handle the signal */
			TRY {
				state = handle_signal(iter,
				                      state,
				                      sc_info);
			} EXCEPT {
				kfree(iter);
				RETHROW();
			}
			kfree(iter);
			did_handle_something = true;
			/* Try to handle even more signals. */
			iter = *piter;
			if (!iter)
				break;
			goto again_iter;
		}
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);

	/* Restore all signals pending for the calling thread. */
	restore_perthread_pending_signals(myqueue, pending);
no_perthread_pending:
	/* With per-task signals checked, also check for per-process signals */
	prqueue = &THIS_PROCESS_SIGQUEUE;
	/* Quick check: are there any pending signals? */
again_lock_prqueue:
	if (ATOMIC_READ(prqueue->psq_queue.sq_queue) != NULL) {
		bool has_write_lock;
		sync_read(&prqueue->psq_lock);
		has_write_lock = false;
again_scan_prqueue:
		for (piter = &prqueue->psq_queue.sq_queue;
			 (iter = *piter) != NULL; piter = &iter->sqe_next) {
			/* XXX: Handle VFORK and USERPROCMASK here, so we can cache user-space memory
			 *      instead of having to re-read  `this_userprocmask_address->pm_sigmask'
			 *      for every signal! */
			if (sigmask_ismasked_chk(iter->sqe_info.si_signo))
				continue;
			/* Found an unmasked signal.
			 * -> Upgrade our lock to write-mode so we can steal it! */
			if (!has_write_lock) {
				has_write_lock = true;
				if unlikely(!sync_upgrade(&prqueue->psq_lock))
					goto again_scan_prqueue;
			}
			/* Steal the current entry. */
			*piter = iter->sqe_next;
			sync_endwrite(&prqueue->psq_lock);
			has_write_lock = false;
			/* Handle this signal. */
			TRY {
				state = handle_signal(iter,
				                      state,
				                      sc_info);
			} EXCEPT {
				kfree(iter);
				RETHROW();
			}
			kfree(iter);
			did_handle_something = true;
			/* Search for more unmasked process signals. */
			goto again_lock_prqueue;
		}
		if unlikely(has_write_lock) {
			sync_endwrite(&prqueue->psq_lock);
		} else {
			sync_endread(&prqueue->psq_lock);
		}
	}
	if (!did_handle_something)
		return TASK_RPC_RESTART_SYSCALL;
	return state;
}




STATIC_ASSERT(SIGACTION_SA_NOCLDSTOP == SA_NOCLDSTOP);
STATIC_ASSERT(SIGACTION_SA_NOCLDWAIT == SA_NOCLDWAIT);
STATIC_ASSERT(SIGACTION_SA_SIGINFO == SA_SIGINFO);
STATIC_ASSERT(SIGACTION_SA_RESTORER == SA_RESTORER);
STATIC_ASSERT(SIGACTION_SA_ONSTACK == SA_ONSTACK);
STATIC_ASSERT(SIGACTION_SA_RESTART == SA_RESTART);
STATIC_ASSERT(SIGACTION_SA_NODEFER == SA_NODEFER);
STATIC_ASSERT(SIGACTION_SA_RESETHAND == SA_RESETHAND);

/* Check  if  `self' contains  any handlers  set to
 * SIG_IGN that wouldn't be set as such by default. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL sighand_has_nondefault_sig_ign)(struct sighand const *__restrict self) {
	unsigned int i;
	for (i = 0; i < NSIG - 1; ++i) {
		/* Check if the handler's action is SIG_IGN */
		if (self->sh_actions[i].sa_handler != KERNEL_SIG_IGN)
			continue; /* Something other than SIG_IGN */
		/* Check if the default action is something other than SIG_IGN */
		if (sighand_default_action(i + 1) == KERNEL_SIG_IGN)
			continue; /* Default would also be SIG_IGN */
		/* Found one! */
		return true;
	}
	return false;
}


/* During exec(), all signal handler dispositions of the calling thread are reset */
DEFINE_PERVM_ONEXEC(onexec_posix_signals_reset_action);
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
		/* NOTE: Use GFP_CALLOC because `KERNEL_SIG_DFL = 0', and we only
		 *       need to inherit handlers  that were marked as  `SIG_IGN' */
		newhand = (REF struct sighand *)kmalloc_nx(sizeof(struct sighand),
		                                           GFP_CALLOC | GFP_ATOMIC);
		if (!newhand) {
			sync_endread(hand);
			newhand = (REF struct sighand *)kmalloc(sizeof(struct sighand), GFP_CALLOC);
			TRY {
				hand = sighand_ptr_lockread(handptr);
			} EXCEPT {
				kfree(newhand);
				assert(!PERTASK_GET(this_sighand_ptr));
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
			if (hand->sh_actions[i].sa_handler == KERNEL_SIG_IGN)
				newhand->sh_actions[i].sa_handler = KERNEL_SIG_IGN;
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
				assert(!PERTASK_GET(this_sighand_ptr));
				PERTASK_SET(this_sighand_ptr, handptr);
				RETHROW();
			}
			assert(!isshared(handptr));
			hand = handptr->sp_hand;    /* Inherit reference */
			handptr->sp_hand = newhand; /* Inherit reference */
			sync_endwrite(&handptr->sp_lock);
			/* Restore the old hand-pointer for the calling thread. */
			assert(!PERTASK_GET(this_sighand_ptr));
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
				assert(!PERTASK_GET(this_sighand_ptr));
				PERTASK_SET(this_sighand_ptr, handptr);
				RETHROW();
			}
			newhandptr->sp_refcnt = 1;
			atomic_rwlock_init(&newhandptr->sp_lock);
			newhandptr->sp_hand = newhand; /* Inherit reference */
			assert(!PERTASK_GET(this_sighand_ptr));
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
 * @return: true:   Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false:  The given thread `target' has already terminated execution.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or >= `NSIG'
 * @throw: E_INTERRUPT_USER_RPC:        `target' is the calling thread, and the signal isn't being blocked at the moment. */
PUBLIC NONNULL((1)) bool KCALL
task_raisesignalthread(struct task *__restrict target,
                       USER CHECKED siginfo_t const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_SEGFAULT) {
	bool result;
	struct sigqueue_entry *entry;
	bool maybe_masked;
	/* The signal is being masked.
	 * Allocate a queue entry which is going to be scheduled. */
	entry = (struct sigqueue_entry *)kmalloc(sizeof(struct sigqueue_entry),
	                                         GFP_NORMAL);
	TRY {
		memcpy(&entry->sqe_info, info, sizeof(siginfo_t));
		if unlikely(entry->sqe_info.si_signo <= 0 ||
		            entry->sqe_info.si_signo >= NSIG) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
			      entry->sqe_info.si_signo);
		}
		maybe_masked = sigmask_ismasked_in(target,
		                                   entry->sqe_info.si_signo,
		                                   true) !=
		               SIGMASK_ISMASKED_NO;
	} EXCEPT {
		kfree(entry);
		RETHROW();
	}
	/* Check if the signal is being masked. */
	if (maybe_masked) {
		/* Schedule the signal as pending within the target thread. */
		struct sigqueue *pending;
		struct sigqueue_entry *next;
		pending = &FORTASK(target, this_sigqueue);
		do {
			next = ATOMIC_READ(pending->sq_queue);
			if unlikely(next == SIGQUEUE_SQ_QUEUE_TERMINATED) {
				/* The target thread can no longer receive signals! */
				kfree(entry);
				return false;
			}
			entry->sqe_next = next;
			COMPILER_WRITE_BARRIER();
		} while (!ATOMIC_CMPXCH_WEAK(pending->sq_queue, next, entry));
		/* Only one thread can ever handle the signal, so use `sig_send()' */
		sig_send(&pending->sq_newsig);
		/* Check if the signal is still being masked. - If it isn't, it may have gotten
		 * unmasked before we inserted our new signal into the queue, in which case the
		 * target  thread may not know about it. - Because of this, send an RPC to have
		 * the target thread manually check for unmasked signals. */
		if unlikely(sigmask_ismasked_in(target,
		                                entry->sqe_info.si_signo,
		                                true) !=
		            SIGMASK_ISMASKED_YES) {
			/* The signal is (maybe) unmasked */
			result = task_schedule_user_rpc(target,
			                                &task_sigmask_check_rpc_handler,
			                                NULL,
			                                TASK_USER_RPC_FINTR);
			return result;

		}
		/* The target thread will handle the signal as soon as it gets unmasked! */
		return true;
	}
	/* Deliver an RPC. */
	TRY {
		result = task_schedule_user_rpc(target,
		                                &task_signal_rpc_handler,
		                                entry,
		                                TASK_USER_RPC_FINTR);
	} EXCEPT {
		if (!was_thrown(E_INTERRUPT_USER_RPC))
			kfree(entry);
		RETHROW();
	}
	if (!result)
		kfree(entry);
	return result;

}




/* Find a thread within the process lead by `process_leader' that isn't
 * masking `signo'. If  no such thread  exists, return `NULL'  instead. */
PRIVATE WUNUSED NONNULL((1)) REF struct task *KCALL
find_thread_in_process_with_unmasked_signal(struct task *__restrict process_leader,
                                            signo_t signo)
		THROWS(E_WOULDBLOCK) {
	struct taskgroup *group;
	struct taskpid *cpid;
	assert(!(process_leader->t_flags & TASK_FKERNTHREAD));
	/* First check: is the leader masking the signal? */
	if (sigmask_ismasked_in(process_leader, signo, true) == SIGMASK_ISMASKED_NO)
		return incref(process_leader);
	group = &FORTASK(process_leader, this_taskgroup);
	sync_read(&group->tg_proc_threads_lock);
	FOREACH_taskgroup__proc_threads(cpid, group) {
		REF struct task *child;
		child = awref_get(&cpid->tp_thread);
		if (!child)
			continue;
		/* Only consider child _threads_ (not child processes) */
		if (task_getprocess_of(child) == process_leader) {
			/* Check if the thread is masking the given signal. */
			if (sigmask_ismasked_in(child, signo, false) == SIGMASK_ISMASKED_NO) {
				sync_endread(&group->tg_proc_threads_lock);
				return child;
			}
		}
		decref_unlikely(child);
	}
	sync_endread(&group->tg_proc_threads_lock);
	/* The signal is being masked everywhere. */
	return NULL;
}



#ifdef SIGMASK_ISMASKED_MAYBE
/* Same  as  `find_thread_in_process_with_unmasked_signal()',  but  in  the  event
 * that NULL  ends up  being returned,  initialize `pmaybe_maskers'  as a  pointer
 * set of  references (to-be  finalized  by `taskref_pointer_set_fini()')  of  all
 * the threads for which `sigmask_ismasked_in()' returned `SIGMASK_ISMASKED_MAYBE' */
PRIVATE WUNUSED NONNULL((1, 3)) REF struct task *KCALL
find_thread_in_process_with_unmasked_signal_and_gather_maybe_maskers(struct task *__restrict process_leader, signo_t signo,
                                                                     /*[out_if(return == NULL)]*/ struct pointer_set *__restrict pmaybe_maskers)
		THROWS(E_WOULDBLOCK) {
	struct taskgroup *group;
	struct taskpid *cpid;
	int is_masked;
	size_t has_maybe_masked;
	assert(!(process_leader->t_flags & TASK_FKERNTHREAD));
	/* First check: is the leader masking the signal? */
	is_masked = sigmask_ismasked_in(process_leader, signo, true);
	if (is_masked == SIGMASK_ISMASKED_NO)
		return incref(process_leader);
	has_maybe_masked = is_masked == SIGMASK_ISMASKED_MAYBE ? 1 : 0;
	group = &FORTASK(process_leader, this_taskgroup);
	sync_read(&group->tg_proc_threads_lock);
	FOREACH_taskgroup__proc_threads(cpid, group) {
		REF struct task *child;
		child = awref_get(&cpid->tp_thread);
		if (!child)
			continue;
		/* Only consider child _threads_ (not child processes) */
		if (task_getprocess_of(child) == process_leader) {
			/* Check if the thread is masking the given signal. */
			int is_masked = sigmask_ismasked_in(child, signo, false);
			if (is_masked == SIGMASK_ISMASKED_NO) {
				sync_endread(&group->tg_proc_threads_lock);
				return child;
			}
			if (is_masked == SIGMASK_ISMASKED_MAYBE)
				++has_maybe_masked;
		}
		decref_unlikely(child);
	}
	pointer_set_init(pmaybe_maskers);
	if (has_maybe_masked != 0) {
		/* If there are threads that ~may~ be masking the signal,
		 * gather them up now. */
		sync_endread(&group->tg_proc_threads_lock);
		if (has_maybe_masked > pmaybe_maskers->ps_mask) {
			/* The buffer won't be large enough... */
			pointer_set_clear_and_rehash(pmaybe_maskers,
			                             has_maybe_masked);
		}
again_search_for_maybe_maskers:
		TRY {
			is_masked = sigmask_ismasked_in(process_leader, signo, true);
			if (is_masked == SIGMASK_ISMASKED_NO) {
				pointer_set_fini(pmaybe_maskers);
				return incref(process_leader);
			}
			if (is_masked == SIGMASK_ISMASKED_MAYBE) {
				pointer_set_insert(pmaybe_maskers, process_leader);
				incref(process_leader); /* The reference inherited by `pointer_set_insert()' */
			}
			sync_read(&group->tg_proc_threads_lock);
		} EXCEPT {
			taskref_pointer_set_fini(pmaybe_maskers);
			RETHROW();
		}
		FOREACH_taskgroup__proc_threads(cpid, group) {
			REF struct task *child;
			int is_masked;
			int insert_error;
			child = awref_get(&cpid->tp_thread);
			if (!child)
				continue;
			/* Only consider child _threads_ (not child processes) */
			if (task_getprocess_of(child) != process_leader) {
				decref_unlikely(child);
				continue;
			}
			/* Check if the thread is masking the given signal. */
			is_masked = sigmask_ismasked_in(child, signo, false);
			if unlikely(is_masked == SIGMASK_ISMASKED_NO) {
				/* This really shouldn't happen, but better be safe! */
				sync_endread(&group->tg_proc_threads_lock);
				taskref_pointer_set_fini(pmaybe_maskers);
				return child;
			}
			if (is_masked != SIGMASK_ISMASKED_MAYBE) {
				/* We know that this child _is_ masking the signal, so ignore it. */
				assert(is_masked == SIGMASK_ISMASKED_YES);
				decref_unlikely(child);
				continue;
			}
			/* Add this thread to the pointer set.
			 * If the set is full, and we can't increase its size atomically,
			 * then we must release all locks, clear the set, and start  over
			 * from scratch. */
			insert_error = pointer_set_insert_nx(pmaybe_maskers, child, GFP_ATOMIC);
			if (insert_error != POINTER_SET_INSERT_NX_SUCCESS) {
				assertf(insert_error != POINTER_SET_INSERT_NX_EXISTS,
				        "This would indicate a loop in the child chain of `process_leader'");
				sync_endread(&group->tg_proc_threads_lock);
				decref_unlikely(child);
				taskref_pointer_set_decref_all(pmaybe_maskers);
				/* Increase  the buffer size of `pmaybe_maskers' to have
				 * at least enough space  for +1 additional thread  from
				 * the number of thread that (were) contained until now. */
				TRY {
					pointer_set_clear_and_rehash(pmaybe_maskers,
					                             pmaybe_maskers->ps_size + 1);
				} EXCEPT {
					pointer_set_fini(pmaybe_maskers);
					RETHROW();
				}
				goto again_search_for_maybe_maskers;
			}
			/* In this case, the `pointer_set_insert_nx()' will have inherited
			 * a reference to `child', meaning that we mustn't decref it here! */
			/*decref_unlikely(child);*/
		}
		/* We'll  be returning NULL,  so don't destroy  the set of maybe-masker
		 * threads, since it's our caller responsibility to deal with that one! */
		/*taskref_pointer_set_fini(pmaybe_maskers);*/
	}
	sync_endread(&group->tg_proc_threads_lock);
	/* The signal is being masked everywhere. */
	return NULL;
}
#endif /* SIGMASK_ISMASKED_MAYBE */





/* Deliver the given signal `info' to some thread apart of the process lead by `process_leader'
 * If all threads are masking the given signal, schedule the signal as pending for the process.
 * @return: true:  Success (either delivered, or scheduled as pending).
 * @return: false: The given process has terminated. */
PRIVATE bool KCALL
deliver_signal_to_some_thread_in_process(struct task *__restrict process_leader,
                                         /*inherit(always)*/ struct sigqueue_entry *__restrict info)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INTERRUPT_USER_RPC) {
	bool result;
	REF struct task *target;
	struct process_sigqueue *procqueue;
	u32 kernel_signo;
	assert(!(process_leader->t_flags & TASK_FKERNTHREAD));
	assert(!(info->sqe_info.si_signo <= 0 || info->sqe_info.si_signo >= NSIG));
	if unlikely(ATOMIC_READ(process_leader->t_flags) & (TASK_FTERMINATING | TASK_FTERMINATED)) {
		kfree(info);
		/* No possible receiver in a terminating process. */
		return false;
	}

	/* Search the process for a thread that isn't masking the signal.
	 * If we  can  find  one,  send  the signal  to  it  by  using  a
	 * `task_process_signal_rpc_handler'  RPC  to  have  it  handled.
	 *
	 * If we can't find one, schedule the signal as pending and  re-check
	 * all threads. - If at this point we find one that isn't masking it,
	 * we must deliver a `task_sigmask_check_rpc_handler' RPC to it so it
	 * can be the one to handle the signal. */
	kernel_signo = info->sqe_info.si_signo;
	COMPILER_READ_BARRIER();
	TRY {
		target = find_thread_in_process_with_unmasked_signal(process_leader,
		                                                     kernel_signo);
	} EXCEPT {
		kfree(info);
		RETHROW();
	}
	if (target) {
		FINALLY_DECREF_UNLIKELY(target);
		TRY {
			result = task_schedule_user_rpc(target,
			                                &task_process_signal_rpc_handler,
			                                info,
			                                TASK_USER_RPC_FINTR);
		} EXCEPT {
			if (!was_thrown(E_INTERRUPT_USER_RPC))
				kfree(info);
			RETHROW();
		}
		if unlikely(!result)
			kfree(info);
		return result;
	}

	/* No thread seems to exist  that isn't masking the given  signal.
	 * Schedule the signal as pending within the process signal queue. */
	procqueue = &FORTASK(process_leader, this_taskgroup.tg_proc_signals);
	TRY {
		sync_write(&procqueue->psq_lock);
	} EXCEPT {
		kfree(info);
		RETHROW();
	}
	{
		struct sigqueue_entry *next;
		do {
			next = ATOMIC_READ(procqueue->psq_queue.sq_queue);
			if unlikely(next == SIGQUEUE_SQ_QUEUE_TERMINATED) {
				/* The target process has terminated. */
				sync_endwrite(&procqueue->psq_lock);
				kfree(info);
				return false;
			}
			info->sqe_next = next;
			COMPILER_WRITE_BARRIER();
		} while (!ATOMIC_CMPXCH_WEAK(procqueue->psq_queue.sq_queue,
		                             next, info));
	}
	sync_endwrite(&procqueue->psq_lock);
	/* Signal the arrival of a new pending signal.
	 * Only one thread can ever handle the signal, so use `sig_send()' */
	sig_send(&procqueue->psq_queue.sq_newsig);
again_find_late_target:
	/* Check for a potential target thread one more time. */
	if unlikely(ATOMIC_READ(process_leader->t_flags) & (TASK_FTERMINATING | TASK_FTERMINATED))
		return false; /* No possible receiver in a terminating process. */
	{
#ifdef SIGMASK_ISMASKED_MAYBE
		struct pointer_set maybe_blocking_threads;
		target = find_thread_in_process_with_unmasked_signal_and_gather_maybe_maskers(process_leader,
		                                                                              kernel_signo,
		                                                                              &maybe_blocking_threads);
#else /* SIGMASK_ISMASKED_MAYBE */
		target = find_thread_in_process_with_unmasked_signal(process_leader,
		                                                     kernel_signo);
#endif /* !SIGMASK_ISMASKED_MAYBE */
		if (target) {
			/* Deliver a `task_sigmask_check_rpc_handler' RPC to the target thread. */
			FINALLY_DECREF_UNLIKELY(target);
			if unlikely(!task_schedule_user_rpc(target,
			                                    &task_sigmask_check_rpc_handler,
			                                    NULL,
			                                    TASK_USER_RPC_FINTR)) {
				/* The chosen target has terminated. - Try to find another candidate. */
				goto again_find_late_target;
			}
		}
#ifdef SIGMASK_ISMASKED_MAYBE
		else {
			/* Send  the  `task_sigmask_check_rpc_handler' to  every thread
			 * from  `maybe_blocking_threads'. - Since  we can't figure out
			 * if each one of them is currently masking the signal, they'll
			 * just have to figure that out for themselves. */
			TRY {
				POINTER_SET_FOREACH(target, &maybe_blocking_threads) {
					task_schedule_user_rpc(target,
					                       &task_sigmask_check_rpc_handler,
					                       NULL,
					                       TASK_USER_RPC_FINTR);
				}
			} EXCEPT {
				taskref_pointer_set_fini(&maybe_blocking_threads);
				RETHROW();
			}
			taskref_pointer_set_fini(&maybe_blocking_threads);
		}
#endif /* SIGMASK_ISMASKED_MAYBE */
	}
	return true;
}


/* Raise a posix signal within a given process that `target' is apart of
 * @return: true:  Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false: The given process `target' has already terminated execution.
 * @return: false: The given process `target' is a kernel thread.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or >= `NSIG'
 * @throw: E_INTERRUPT_USER_RPC:         The calling thread is apart of the same  process,
 *                                       and the signal isn't being blocked at the moment. */
PUBLIC NONNULL((1)) bool KCALL
task_raisesignalprocess(struct task *__restrict target,
                        USER CHECKED siginfo_t const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_SEGFAULT) {
	struct sigqueue_entry *entry;
	bool result;
	target = task_getprocess_of(target);
	if unlikely(target->t_flags & TASK_FKERNTHREAD)
		return false;
	/* Allocate the queue entry for the given signal. */
	entry = (struct sigqueue_entry *)kmalloc(sizeof(struct sigqueue_entry),
	                                         GFP_NORMAL);
	TRY {
		memcpy(&entry->sqe_info, info, sizeof(siginfo_t));
		if unlikely(entry->sqe_info.si_signo <= 0 || entry->sqe_info.si_signo >= NSIG) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
			      entry->sqe_info.si_signo);
		}
	} EXCEPT {
		kfree(entry);
		RETHROW();
	}
	result = deliver_signal_to_some_thread_in_process(target,
	                                                  entry);
	return result;
}


/* Send a signal to every process within the same process group that `target' is apart of.
 * @return: * : The number of processes to which the signal was delivered. */
PUBLIC NONNULL((1)) size_t KCALL
task_raisesignalprocessgroup(struct task *__restrict target,
                             USER CHECKED siginfo_t const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_PROCESS_EXITED) {
	size_t result = 0;
	bool was_interrupted = false;
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
		if (was_thrown(E_INTERRUPT_USER_RPC))
			was_interrupted = true;
		else {
			decref_unlikely(pgroup);
			RETHROW();
		}
	}
	pointer_set_init(&ps);
	TRY {
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
				TRY {
					if (task_raisesignalprocess(thread, info))
						++result;
				} EXCEPT {
					if (!was_thrown(E_INTERRUPT_USER_RPC))
						RETHROW();
					was_interrupted = true;
				}
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
	} EXCEPT {
		taskref_pointer_set_fini(&ps);
		decref_unlikely(pgroup);
		RETHROW();
	}
	taskref_pointer_set_fini(&ps);
	decref_unlikely(pgroup);
	if (was_interrupted)
		THROW(E_INTERRUPT_USER_RPC);
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
		if ((uintptr_t)nhandler.sa_handler >= (uintptr_t)KERNEL_SIG_GET)
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
	if (handler == KERNEL_SIG_GET) {
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
	if (handler == KERNEL_SIG_GET) {
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
	sigset_t *mymask;
	if unlikely(sigsetsize != sizeof(sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	validate_readable_opt(set, sizeof(*set));
	validate_writable_opt(oset, sizeof(*oset));
	if (!set) {
		if (oset) {
			mymask = sigmask_getrd();
			memcpy(oset, mymask, sizeof(sigset_t));
		}
	} else {
		mymask = sigmask_getwr();
		if (oset)
			memcpy(oset, mymask, sizeof(sigset_t));
		switch (how) {

		case SIG_BLOCK:
			sigorset(mymask, mymask, set);
			break;

		case SIG_UNBLOCK:
			/* No need to check for  mandatory masks being clear,  since
			 * this command is only able to clear masks from the get-go. */
			signandset(mymask, mymask, set);
			/* Since signals (may) have just gotten unmasked, check if we're
			 * now  able   to   handle   any   of   the   pending   signals. */
			sigmask_check_after_syscall(-EOK);
			break;

		case SIG_SETMASK:
			memcpy(mymask, set, sizeof(sigset_t));
			/* Make sure that mandatory signals are in check */
			sigdelset(mymask, SIGKILL);
			sigdelset(mymask, SIGSTOP);
			COMPILER_BARRIER();
			/* Always check for pending signals, since
			 * anything may have happened to our mask. */
			sigmask_check_after_syscall(-EOK);
			break;

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
	USER CHECKED sigset_t *mymask;
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
	USER CHECKED sigset_t *mymask;
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
	sigmask_check_after_syscall(result);
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
	sigmask_check_after_syscall(result);
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
	if unlikely(signo <= 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO, signo);
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
		info.si_pid = taskpid_getpid_ind(mypid, get_pid_indirection(target));;
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
/* @return: NULL : No signal was detected
 * @return: *    : The accepted signal entry (must be inherited by the caller) */
PRIVATE struct sigqueue_entry *KCALL
signal_try_steal_pending(sigset_t const *__restrict these) {
	struct sigqueue *myqueue;
	struct process_sigqueue *prqueue;
	struct sigqueue_entry *pending, **piter, *iter;
	bool has_write_lock;
	myqueue = &THIS_SIGQUEUE;
	/* Temporarily steal all pending per-thread signals. */
	do {
		pending = ATOMIC_READ(myqueue->sq_queue);
		if (!pending)
			goto no_perthread_pending; /* No signals are pending for the calling thread */
		if unlikely(pending == SIGQUEUE_SQ_QUEUE_TERMINATED)
			return NULL; /* Shouldn't happen: The calling thread is currently terminating. */
	} while (!ATOMIC_CMPXCH_WEAK(myqueue->sq_queue, pending, NULL));
	/* Go through pending signals and check if there are any that aren't being masked. */
	iter  = pending;
	piter = &pending;
	do {
		if (sigismember(these, iter->sqe_info.si_signo)) {
			/* Found one that's not being masked. */
			*piter = iter->sqe_next;
			if (pending)
				restore_perthread_pending_signals(myqueue, pending);
			/* Got a signal! */
			return iter;
		}
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);
	/* Must also check if there is a pending signal
	 * that isn't masked by our active signal mask. */
	iter  = pending;
	piter = &pending;
	do {
		/* XXX: Handle VFORK and USERPROCMASK here, so we can cache user-space memory
		 *      instead of having to re-read  `this_userprocmask_address->pm_sigmask'
		 *      for every signal! */
		if (!sigmask_ismasked_chk(iter->sqe_info.si_signo)) {
			/* Found one that's not being masked. */
			*piter = iter->sqe_next;
			if (pending)
				restore_perthread_pending_signals(myqueue, pending);
			/* Deliver the signal to ourself */
			send_signal_rpc_to_self(iter);
			__builtin_unreachable();
		}
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);
	/* Restore all signals pending for the calling thread. */
	restore_perthread_pending_signals(myqueue, pending);
no_perthread_pending:
	/* With per-task signals checked, also check for per-process signals */
	prqueue = &THIS_PROCESS_SIGQUEUE;
	has_write_lock = false;
	sync_read(&prqueue->psq_lock);
again_scan_prqueue:
	piter = &prqueue->psq_queue.sq_queue;
	while ((iter = *piter) != NULL) {
		if (sigismember(these, iter->sqe_info.si_signo)) {
			if (!has_write_lock) {
				has_write_lock = true;
				if (!sync_upgrade(&prqueue->psq_lock))
					goto again_scan_prqueue;
			}
			/* Steal this signal packet. */
			*piter = iter->sqe_next;
			sync_endwrite(&prqueue->psq_lock);
			return iter;
		}
		piter = &iter->sqe_next;
	}
	if (has_write_lock)
		sync_downgrade(&prqueue->psq_lock);
	/* Must also check if there is a pending signal
	 * that isn't masked by our active signal mask. */
	for (iter = prqueue->psq_queue.sq_queue;
	     iter; iter = iter->sqe_next) {
		/* XXX: Handle VFORK and USERPROCMASK here, so we can cache user-space memory
		 *      instead of having to re-read  `this_userprocmask_address->pm_sigmask'
		 *      for every signal! */
		if (sigmask_ismasked_chk(iter->sqe_info.si_signo))
			continue;
		/* Found an unmasked signal. */
		sync_endread(&prqueue->psq_lock);
		task_schedule_user_rpc(THIS_TASK,
		                       &task_sigmask_check_rpc_handler,
		                       NULL,
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
		__builtin_unreachable();
	}
	sync_endread(&prqueue->psq_lock);
	return NULL;
}


/* @return: 0 : The timeout has expired
 * @return: * : The accepted signal number */
PRIVATE syscall_ulong_t KCALL
signal_waitfor(CHECKED USER sigset_t const *uthese,
               CHECKED USER siginfo_t *uinfo,
               ktime_t abs_timeout) {
	sigset_t these;
	syscall_ulong_t result;
	assert(!task_wasconnected());
	memcpy(&these, uthese, sizeof(sigset_t));
	COMPILER_BARRIER();
	/* Make sure that we don't steal these signals */
	sigdelset(&these, SIGKILL);
	sigdelset(&these, SIGSTOP);
	COMPILER_WRITE_BARRIER();
	for (;;) {
		struct sigqueue_entry *ent;
		ent = signal_try_steal_pending(&these);
		if (ent) {
copy_and_free_ent_info:
			result = ent->sqe_info.si_signo;
			if (uinfo) {
				TRY {
					memcpy(uinfo, &ent->sqe_info, sizeof(siginfo_t));
				} EXCEPT {
					kfree(ent);
					RETHROW();
				}
			}
			kfree(ent);
			break;
		}
		/* Connect to the signals that get broadcast when new signals arrive. */
		TRY {
			task_connect(&THIS_SIGQUEUE.sq_newsig);
			task_connect(&THIS_PROCESS_SIGQUEUE.psq_queue.sq_newsig);
			/* Check  for pending signals  once again, now that
			 * we're interlocked their them possibly appearing. */
			ent = signal_try_steal_pending(&these);
			if unlikely(ent) {
				task_disconnectall();
				goto copy_and_free_ent_info;
			}
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
		/* Wait for new signals to be delivered. */
		if (!task_waitfor(abs_timeout)) {
			result = 0;
			break;
		}
	}
	return result;
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
#ifdef __ARCH_WANT_SYSCALL_RT_SIGSUSPEND
/* @return: NULL : No signal was detected
 * @return: *    : The accepted signal entry (must be inherited by the caller) */
PRIVATE struct sigqueue_entry *KCALL
signal_try_steal_one_not_of_these(sigset_t const *__restrict these) {
	struct sigqueue *myqueue;
	struct process_sigqueue *prqueue;
	struct sigqueue_entry *pending, **piter, *iter;
	bool has_write_lock;
	myqueue = &THIS_SIGQUEUE;
	/* Temporarily steal all pending per-thread signals. */
	do {
		pending = ATOMIC_READ(myqueue->sq_queue);
		if (!pending)
			goto no_perthread_pending; /* No signals are pending for the calling thread */
		if unlikely(pending == SIGQUEUE_SQ_QUEUE_TERMINATED)
			return NULL; /* Shouldn't happen: The calling thread is currently terminating. */
	} while (!ATOMIC_CMPXCH_WEAK(myqueue->sq_queue, pending, NULL));
	/* Go through pending signals and check if there are any that aren't being masked. */
	iter  = pending;
	piter = &pending;
	do {
		if (!sigismember(these, iter->sqe_info.si_signo)) {
			/* Found one that's not being masked. */
			*piter = iter->sqe_next;
			if (pending)
				restore_perthread_pending_signals(myqueue, pending);
			/* Got a signal! */
			return iter;
		}
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);
	/* Restore all signals pending for the calling thread. */
	restore_perthread_pending_signals(myqueue, pending);
no_perthread_pending:
	/* With per-task signals checked, also check for per-process signals */
	prqueue = &THIS_PROCESS_SIGQUEUE;
	has_write_lock = false;
	sync_read(&prqueue->psq_lock);
again_scan_prqueue:
	piter = &prqueue->psq_queue.sq_queue;
	while ((iter = *piter) != NULL) {
		if (!sigismember(these, iter->sqe_info.si_signo)) {
			if (!has_write_lock) {
				has_write_lock = true;
				if (!sync_upgrade(&prqueue->psq_lock))
					goto again_scan_prqueue;
			}
			/* Steal this signal packet. */
			*piter = iter->sqe_next;
			sync_endwrite(&prqueue->psq_lock);
			return iter;
		}
		piter = &iter->sqe_next;
	}
	if (has_write_lock)
		sync_endwrite(&prqueue->psq_lock);
	else {
		sync_endread(&prqueue->psq_lock);
	}
	return NULL;
}

PRIVATE struct icpustate *FCALL
sys_rt_sigsuspend_impl(struct icpustate *__restrict state,
                       USER UNCHECKED sigset_t const *uthese) {
	struct sigqueue_entry *ent;
	sigset_t these;
	uintptr_t old_flags;
	validate_readable(uthese, sizeof(sigset_t));
	memcpy(&these, uthese, sizeof(sigset_t));
	/* Make sure that we don't steal these signals */
	sigdelset(&these, SIGKILL);
	sigdelset(&these, SIGSTOP);

	/* Mask   everything,  so  we  don't  get  any
	 * posix-signal-related RPCs screwing with us.
	 *
	 * For  this,  we  (ab-)use  the  VFORK  flag, which
	 * does exactly  what we  want in  this case,  which
	 * is  to  make it  look  like we  have  an all-full
	 * signal mask,  without actually  having to  modify
	 * our signal mask (which may point into user-space) */
	old_flags = PERTASK_GET(this_task.t_flags);
	ATOMIC_OR(THIS_TASK->t_flags, TASK_FVFORK);

	TRY {
		for (;;) {
			ent = signal_try_steal_one_not_of_these(&these);
			if (ent)
				goto do_handle_ent;
			/* Connect to the signals that get broadcast when new signals arrive. */
			TRY {
				task_connect(&THIS_SIGQUEUE.sq_newsig);
				task_connect(&THIS_PROCESS_SIGQUEUE.psq_queue.sq_newsig);
				/* Check  for pending signals  once again, now that
				 * we're interlocked their them possibly appearing. */
				ent = signal_try_steal_one_not_of_these(&these);
				if unlikely(ent) {
					task_disconnectall();
					goto do_handle_ent;
				}
			} EXCEPT {
				task_disconnectall();
				RETHROW();
			}
			/* Wait for new signals to be delivered. */
			task_waitfor();
		}
	} EXCEPT {
		if (!(old_flags & TASK_FVFORK))
			ATOMIC_AND(THIS_TASK->t_flags, ~TASK_FVFORK);
		sigmask_check_after_except();
		RETHROW();
	}
do_handle_ent:
	if (!(old_flags & TASK_FVFORK))
		ATOMIC_AND(THIS_TASK->t_flags, ~TASK_FVFORK);
	TRY {
		/* Directly handle the signal. */
		state = set_syscall_return(state, -EOK);
		/* FIXME: If there was an RPC send to our thread before we  got
		 *        here, that RPC must be prevented from re-starting our
		 *        system call! */
		state = handle_signal(ent, state, NULL);
	} EXCEPT {
		kfree(ent);
		RETHROW();
	}
	kfree(ent);
	/* Having  restored the signal  mask (which may  have once again gotten
	 * modified by `handle_signal()'), we must still check for more signals
	 * that may have  been masked  until now,  but have  gotten visible  in
	 * the mean time. */
	sigmask_check_after_syscall(-EOK);
	return state;
}

PRIVATE WUNUSED NONNULL((2)) struct icpustate *FCALL
syscall_rt_sigsuspend_rpc(void *UNUSED(arg),
                          struct icpustate *__restrict state,
                          unsigned int reason,
                          struct rpc_syscall_info const *sc_info) {
	if (reason == TASK_RPC_REASON_SYSCALL)
		state = sys_rt_sigsuspend_impl(state, (USER UNCHECKED sigset_t const *)sc_info->rsi_regs[0]);
	return state;
}


DEFINE_SYSCALL2(errno_t, rt_sigsuspend,
                USER UNCHECKED sigset_t const *, uthese,
                size_t, sigsetsize) {
	(void)uthese;
	if unlikely(sigsetsize != sizeof(sigset_t)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	}
	/* Send an RPC to ourself, so we can gain access to the user-space register state. */
	task_schedule_user_rpc(THIS_TASK,
	                       &syscall_rt_sigsuspend_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGSUSPEND */

#ifdef __ARCH_WANT_SYSCALL_SIGSUSPEND
DEFINE_SYSCALL1(errno_t, sigsuspend,
                USER UNCHECKED sigset_t const *, uthese) {
	return sys_rt_sigsuspend(uthese, sizeof(sigset_t));
}
#endif /* __ARCH_WANT_SYSCALL_SIGSUSPEND */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGSUSPEND
DEFINE_COMPAT_SYSCALL1(errno_t, sigsuspend,
                       USER UNCHECKED compat_sigset_t const *, uthese) {
	return sys_rt_sigsuspend(uthese, sizeof(compat_sigset_t));
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGSUSPEND */





/************************************************************************/
/* rt_sigpending(), sigpending()                                        */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_RT_SIGPENDING
/* Gather the set of pending signals. */
LOCAL void KCALL
signal_gather_pending(sigset_t *__restrict these) {
	struct sigqueue *myqueue;
	struct process_sigqueue *prqueue;
	struct sigqueue_entry *pending, **piter, *iter;
	myqueue = &THIS_SIGQUEUE;
	/* Temporarily steal all pending per-thread signals. */
	do {
		pending = ATOMIC_READ(myqueue->sq_queue);
		if (!pending)
			goto no_perthread_pending; /* No signals are pending for the calling thread */
		if unlikely(pending == SIGQUEUE_SQ_QUEUE_TERMINATED)
			return; /* Shouldn't happen: The calling thread is currently terminating. */
	} while (!ATOMIC_CMPXCH_WEAK(myqueue->sq_queue, pending, NULL));
	iter  = pending;
	piter = &pending;
	do {
		/* XXX: Handle VFORK and USERPROCMASK here, so we can cache user-space memory
		 *      instead of having to re-read  `this_userprocmask_address->pm_sigmask'
		 *      for every signal! */
		if (!sigmask_ismasked_chk(iter->sqe_info.si_signo)) {
			/* Found one that's not being masked. */
			*piter = iter->sqe_next;
			if (pending)
				restore_perthread_pending_signals(myqueue, pending);
			/* Deliver the signal to ourself */
			send_signal_rpc_to_self(iter);
			break;
		}
		sigaddset(these, iter->sqe_info.si_signo);
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);
	/* Restore all signals pending for the calling thread. */
	restore_perthread_pending_signals(myqueue, pending);
no_perthread_pending:
	/* With per-task signals checked, also check for per-process signals */
	prqueue = &THIS_PROCESS_SIGQUEUE;
	sync_read(&prqueue->psq_lock);
	for (iter = prqueue->psq_queue.sq_queue;
	     iter; iter = iter->sqe_next) {
		/* XXX: Handle VFORK and USERPROCMASK here, so we can cache user-space memory
		 *      instead of having to re-read  `this_userprocmask_address->pm_sigmask'
		 *      for every signal! */
		if (sigmask_ismasked_chk(iter->sqe_info.si_signo)) {
			sigaddset(these, iter->sqe_info.si_signo);
			continue;
		}
		/* Found an unmasked signal. */
		sync_endread(&prqueue->psq_lock);
		task_schedule_user_rpc(THIS_TASK,
		                       &task_sigmask_check_rpc_handler,
		                       NULL,
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
		__builtin_unreachable();
	}
	sync_endread(&prqueue->psq_lock);
}

DEFINE_SYSCALL2(errno_t, rt_sigpending,
                UNCHECKED USER sigset_t *, uset,
                size_t, sigsetsize) {
	sigset_t pending;
	/* Validate the user-space signal set pointer. */
	if unlikely(sigsetsize != sizeof(sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	validate_writable(uset, sizeof(sigset_t));
	memset(&pending, 0, sizeof(pending));
	signal_gather_pending(&pending);
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

#ifdef __ARCH_WANT_SYSCALL_SIGMASK_CHECK
DEFINE_SYSCALL0(errno_t, sigmask_check) {
	/* XXX:  An arch-specific version could be implemented to directly
	 *       call  `sigmask_check_s()', which would be way faster than
	 *       this function is! */
	sigmask_check();
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SIGMASK_CHECK */

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_POSIX_SIGNAL_C */
