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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIGMASK_H
#define GUARD_KERNEL_INCLUDE_SCHED_SIGMASK_H 1

#include <kernel/compiler.h>

#include <kernel/rt/except-syscall.h> /* CONFIG_HAVE_USERPROCMASK */
#include <kernel/types.h>

#include <bits/os/sigset.h>
#include <kos/aref.h>

#ifdef __CC__
DECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

/************************************************************************/
/* SIGNAL MASK                                                          */
/************************************************************************/
struct kernel_sigmask {
	WEAK refcnt_t sm_refcnt;  /* Signal mask reference counter. */
	WEAK refcnt_t sm_share;   /* [<= sm_refcnt] Signal mask share counter.
	                           * NOTE: Only allowed to be incremented when `this == sigmask_getrd()' */
	sigset_t      sm_mask;    /* [const_if(sm_share > 1)] Set of signals. */
};

#ifndef ____os_free_defined
#define ____os_free_defined
FUNDEF NOBLOCK void NOTHROW(KCALL __os_free)(VIRT void *ptr) ASMNAME("kfree");
#endif /* !____os_free_defined */
DEFINE_REFCOUNT_FUNCTIONS(struct kernel_sigmask, sm_refcnt, __os_free)

/* An empty signal mask used to initialize `this_kernel_sigmask' */
DATDEF struct kernel_sigmask kernel_sigmask_empty;

/* A full signal mask (i.e. one that blocks all signals; except for SIGKILL and SIGSTOP) */
DATDEF struct kernel_sigmask kernel_sigmask_full;

#ifndef __kernel_sigmask_arref_defined
#define __kernel_sigmask_arref_defined
ARREF(kernel_sigmask_arref, kernel_sigmask);
#endif /* !__kernel_sigmask_arref_defined */

/* [1..1][lock(READ(ATOMIC), WRITE(THIS_TASK))]
 * Reference to the signal mask (set of signals being blocked) in the  current
 * thread. The pointed-to object is meaningless (but must still be valid) when
 * the associated thread make use of userprocmask. */
DATDEF ATTR_PERTASK struct kernel_sigmask_arref this_kernel_sigmask;

/* Return a pointer to the kernel signal mask of the calling thread. */
#define sigmask_kernel_getrd() PERTASK_GET(this_kernel_sigmask.arr_obj)

/* Make sure that `this_kernel_sigmask' is allocated, and isn't being
 * shared.  Then,  always  return  `PERTASK_GET(this_kernel_sigmask)' */
FUNDEF ATTR_RETNONNULL WUNUSED struct kernel_sigmask *KCALL
sigmask_kernel_getwr(void) THROWS(E_BADALLOC);


#ifdef CONFIG_HAVE_USERPROCMASK
/* Return a pointer to the signal mask of the calling thread. */
FUNDEF WUNUSED USER CHECKED sigset_t const *KCALL sigmask_getrd(void) THROWS(E_SEGFAULT);

/* Make sure that `this_kernel_sigmask' is allocated, and isn't being shared.
 * Then, always return `PERTASK_GET(this_kernel_sigmask)'
 * NOTE: When  calling thread has  the `TASK_FUSERPROCMASK' flag set,
 *       then this function will return the address of the currently-
 *       assigned  user-space signal mask,  rather than its in-kernel
 *       counterpart! */
FUNDEF WUNUSED USER CHECKED sigset_t *KCALL sigmask_getwr(void) THROWS(E_BADALLOC, E_SEGFAULT, ...);
#else /* CONFIG_HAVE_USERPROCMASK */
#define sigmask_getrd() (&sigmask_kernel_getrd()->sm_mask)
#define sigmask_getwr() (&sigmask_kernel_getwr()->sm_mask)
#endif /* !CONFIG_HAVE_USERPROCMASK */


/* Check if a given `signo' is currently masked. This function
 * handles all of the special cases, including TASK_VFORK  and
 * TASK_USERPROCMASK, as well as making sure that SIGSTOP  and
 * SIGKILL are never considered to be masked. */
#ifdef CONFIG_HAVE_USERPROCMASK
FUNDEF ATTR_PURE WUNUSED bool FCALL sigmask_ismasked(signo_t signo) THROWS(E_SEGFAULT);
#else /* CONFIG_HAVE_USERPROCMASK */
FUNDEF NOBLOCK ATTR_PURE WUNUSED bool NOTHROW(FCALL sigmask_ismasked)(signo_t signo);
#endif /* !CONFIG_HAVE_USERPROCMASK */


#ifdef CONFIG_HAVE_USERPROCMASK
#define SIGMASK_ISMASKED_NOPF_NO  0 /* The signal isn't masked */
#define SIGMASK_ISMASKED_NOPF_YES 1 /* The signal is masked */
/* The signal may be masked, or it may not be, however due  to
 * the target thread running on a different CPU, or using VIO,
 * a faulty pointer, or memory  currently not loaded into  the
 * core for the backing memory of its usersigmask, the calling
 * thread cannot conclusively determine this. */
#define SIGMASK_ISMASKED_NOPF_FAULT (-2)

/* Non-faulting version of `sigmask_ismasked()'.
 * @return: * : One of `SIGMASK_ISMASKED_NOPF_*' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED int
NOTHROW(FCALL sigmask_ismasked_nopf)(signo_t signo);
#else /* CONFIG_HAVE_USERPROCMASK */
#define SIGMASK_ISMASKED_NOPF_NO     false /* The signal isn't masked */
#define SIGMASK_ISMASKED_NOPF_YES    true  /* The signal is masked */
#define sigmask_ismasked_nopf(signo) sigmask_ismasked(signo)
#endif /* !CONFIG_HAVE_USERPROCMASK */
/************************************************************************/

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
FUNDEF NOBLOCK_IF(!allow_blocking_and_exception_when_self_is_THIS_TASK || self != THIS_TASK)
ATTR_PURE WUNUSED NONNULL((1)) int FCALL
sigmask_ismasked_in(struct task *__restrict self, signo_t signo,
                    bool allow_blocking_and_exception_when_self_is_THIS_TASK __DFL(false))
		THROWS(E_SEGFAULT); /* Is NOTHROW when `allow_blocking_and_exception_when_self_is_THIS_TASK == false && self == THIS_TASK' */
#else /* CONFIG_HAVE_USERPROCMASK */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW(FCALL sigmask_ismasked_in)(struct task *__restrict self, signo_t signo);
#define sigmask_ismasked_in(self, signo, ...) sigmask_ismasked_in(self, signo)
#endif /* !CONFIG_HAVE_USERPROCMASK */


/* Prepare the calling thread for a sigsuspend operation.
 *
 * This  function must be  called during the  setup phase of a
 * system call that intends to use `task_serve_with_sigmask()' */
FUNDEF NOBLOCK void
NOTHROW(FCALL sigmask_prepare_sigsuspend)(void);


DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIGMASK_H */
