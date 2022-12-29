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
#ifndef GUARD_LIBC_USER_PTHREAD_C
#define GUARD_LIBC_USER_PTHREAD_C 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>
#include <hybrid/byteorder.h>
#include <hybrid/host.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <kos/anno.h>
#include <kos/except.h>
#include <kos/futex.h>
#include <kos/futexexpr.h>
#include <kos/rpc.h>
#include <kos/syscalls.h>
#include <kos/thread.h>
#include <kos/types.h>
#include <linux/futex.h>
#include <linux/prctl.h> /* TASK_COMM_LEN */
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/resource.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <malloc.h>
#include <sched.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

#include "../libc/dl.h"
#include "../libc/globals.h"
#include "../libc/tls.h"
#include "pthread.h"
#include "sched.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Verify that pthread offset constants are correct */
#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
#define pt_tid pt_pmask.lpm_pmask.pm_mytid
static_assert(offsetof(struct pthread, pt_pmask) == __OFFSET_PTHREAD_PMASK);
#endif /* __LIBC_CONFIG_HAVE_USERPROCMASK */
static_assert(offsetof(struct pthread, pt_tid) == __OFFSET_PTHREAD_TID);
static_assert(offsetof(struct pthread, pt_refcnt) == __OFFSET_PTHREAD_REFCNT);
static_assert(offsetof(struct pthread, pt_retval) == __OFFSET_PTHREAD_RETVAL);
static_assert(offsetof(struct pthread, pt_tls) == __OFFSET_PTHREAD_TLS);
static_assert(offsetof(struct pthread, pt_stackaddr) == __OFFSET_PTHREAD_STACKADDR);
static_assert(offsetof(struct pthread, pt_stacksize) == __OFFSET_PTHREAD_STACKSIZE);
static_assert(offsetof(struct pthread, pt_flags) == __OFFSET_PTHREAD_FLAGS);

/* pthread_attr_t */
static_assert(sizeof(pthread_attr_t) <= __SIZEOF_PTHREAD_ATTR_T);
static_assert(offsetof(pthread_attr_t, pa_schedparam) == __OFFSET_PTHREAD_ATTR_SCHEDPARAM);
static_assert(offsetof(pthread_attr_t, pa_schedpolicy) == __OFFSET_PTHREAD_ATTR_SCHEDPOLICY);
static_assert(offsetof(pthread_attr_t, pa_flags) == __OFFSET_PTHREAD_ATTR_FLAGS);
static_assert(offsetof(pthread_attr_t, pa_guardsize) == __OFFSET_PTHREAD_ATTR_GUARDSIZE);
static_assert(offsetof(pthread_attr_t, pa_stackaddr) == __OFFSET_PTHREAD_ATTR_STACKADDR);
static_assert(offsetof(pthread_attr_t, pa_stacksize) == __OFFSET_PTHREAD_ATTR_STACKSIZE);
static_assert(offsetof(pthread_attr_t, pa_cpuset) == __OFFSET_PTHREAD_ATTR_CPUSET);
static_assert(offsetof(pthread_attr_t, pa_cpusetsize) == __OFFSET_PTHREAD_ATTR_CPUSETSIZE);

/* pthread_mutexattr_t */
static_assert(sizeof(pthread_mutexattr_t) <= __SIZEOF_PTHREAD_MUTEXATTR_T);
static_assert(offsetof(pthread_mutexattr_t, ma_kind) == __OFFSET_PTHREAD_MUTEXATTR_KIND);

/* pthread_mutex_t */
static_assert(sizeof(pthread_mutex_t) <= __SIZEOF_PTHREAD_MUTEX_T);
static_assert(offsetof(pthread_mutex_t, m_lock) == __OFFSET_PTHREAD_MUTEX_LOCK);
static_assert(offsetof(pthread_mutex_t, m_count) == __OFFSET_PTHREAD_MUTEX_COUNT);
static_assert(offsetof(pthread_mutex_t, _m_owner) == __OFFSET_PTHREAD_MUTEX_OWNER);
static_assert(offsetof(pthread_mutex_t, m_kind) == __OFFSET_PTHREAD_MUTEX_KIND);
static_assert(offsetof(pthread_mutex_t, _m_nusers) == __OFFSET_PTHREAD_MUTEX_NUSERS);
static_assert(offsetof(pthread_mutex_t, _m_spins) == __OFFSET_PTHREAD_MUTEX_SPINS);
static_assert(offsetof(pthread_mutex_t, _m_elision) == __OFFSET_PTHREAD_MUTEX_ELISION);
static_assert(offsetof(pthread_mutex_t, _m_list) == __OFFSET_PTHREAD_MUTEX_LIST);
static_assert(offsetof(pthread_mutex_t, _m_list._l_next) == __OFFSET_PTHREAD_MUTEX_LIST_NEXT);
#ifdef __OFFSET_PTHREAD_MUTEX_LIST_PREV
static_assert(offsetof(pthread_mutex_t, _m_list._l_prev) == __OFFSET_PTHREAD_MUTEX_LIST_PREV);
#endif /* !__OFFSET_PTHREAD_MUTEX_LIST_PREV */

/* pthread_condattr_t */
static_assert(sizeof(pthread_condattr_t) <= __SIZEOF_PTHREAD_CONDATTR_T);
static_assert(offsetof(pthread_condattr_t, ca_value) == __OFFSET_PTHREAD_CONDATTR_VALUE);

/* pthread_cond_t */
static_assert(sizeof(pthread_cond_t) <= __SIZEOF_PTHREAD_COND_T);
static_assert(offsetof(pthread_cond_t, _c_lock) == __OFFSET_PTHREAD_COND_LOCK);
static_assert(offsetof(pthread_cond_t, c_futex) == __OFFSET_PTHREAD_COND_FUTEX);
static_assert(offsetof(pthread_cond_t, _c_total_seq) == __OFFSET_PTHREAD_COND_TOTAL_SEQ);
static_assert(offsetof(pthread_cond_t, _c_wakeup_seq) == __OFFSET_PTHREAD_COND_WAKEUP_SEQ);
static_assert(offsetof(pthread_cond_t, _c_woken_seq) == __OFFSET_PTHREAD_COND_WOKEN_SEQ);
static_assert(offsetof(pthread_cond_t, _c_mutex) == __OFFSET_PTHREAD_COND_MUTEX);
static_assert(offsetof(pthread_cond_t, _c_nwaiters) == __OFFSET_PTHREAD_COND_NWAITERS);
static_assert(offsetof(pthread_cond_t, _c_broadcast_seq) == __OFFSET_PTHREAD_COND_BROADCAST_SEQ);

/* pthread_rwlockattr_t */
static_assert(sizeof(pthread_rwlockattr_t) <= __SIZEOF_PTHREAD_RWLOCKATTR_T);
static_assert(offsetof(pthread_rwlockattr_t, rwa_kind) == __OFFSET_PTHREAD_RWLOCKATTR_KIND);
static_assert(offsetof(pthread_rwlockattr_t, rwa_shared) == __OFFSET_PTHREAD_RWLOCKATTR_SHARED);

/* pthread_rwlock_t */
static_assert(sizeof(pthread_rwlock_t) <= __SIZEOF_PTHREAD_RWLOCK_T);
static_assert(offsetof(pthread_rwlock_t, rw_lock) == __OFFSET_PTHREAD_RWLOCK_LOCK);
static_assert(offsetof(pthread_rwlock_t, _rw_nr_readers) == __OFFSET_PTHREAD_RWLOCK_NR_READERS);
static_assert(offsetof(pthread_rwlock_t, rw_readers_wakeup) == __OFFSET_PTHREAD_RWLOCK_READERS_WAKEUP);
static_assert(offsetof(pthread_rwlock_t, rw_writer_wakeup) == __OFFSET_PTHREAD_RWLOCK_WRITER_WAKEUP);
static_assert(offsetof(pthread_rwlock_t, rw_nr_writers) == __OFFSET_PTHREAD_RWLOCK_NR_WRITERS);
static_assert(offsetof(pthread_rwlock_t, _rw_nr_writers_queued) == __OFFSET_PTHREAD_RWLOCK_NR_WRITERS_QUEUED);
static_assert(offsetof(pthread_rwlock_t, rw_flags) == __OFFSET_PTHREAD_RWLOCK_FLAGS);
static_assert(offsetof(pthread_rwlock_t, _rw_shared) == __OFFSET_PTHREAD_RWLOCK_SHARED);
static_assert(offsetof(pthread_rwlock_t, _rw_rwelision) == __OFFSET_PTHREAD_RWLOCK_RWELISION);
static_assert(offsetof(pthread_rwlock_t, rw_writer) == __OFFSET_PTHREAD_RWLOCK_WRITER);

/* pthread_spinlock_t */
static_assert(sizeof(pthread_spinlock_t) <= __SIZEOF_PTHREAD_SPINLOCK_T);

/* pthread_barrierattr_t */
static_assert(sizeof(pthread_barrierattr_t) <= __SIZEOF_PTHREAD_BARRIERATTR_T);
static_assert(offsetof(pthread_barrierattr_t, ba_pshared) == __OFFSET_PTHREAD_BARRIERATTR_PSHARED);

/* pthread_barrier_t */
static_assert(sizeof(pthread_barrier_t) <= __SIZEOF_PTHREAD_BARRIER_T);
static_assert(offsetof(pthread_barrier_t, b_in) == __OFFSET_PTHREAD_BARRIER_IN);
static_assert(offsetof(pthread_barrier_t, b_current_round) == __OFFSET_PTHREAD_BARRIER_CURRENT_ROUND);
static_assert(offsetof(pthread_barrier_t, b_count) == __OFFSET_PTHREAD_BARRIER_COUNT);
static_assert(offsetof(pthread_barrier_t, b_shared) == __OFFSET_PTHREAD_BARRIER_SHARED);
static_assert(offsetof(pthread_barrier_t, b_out) == __OFFSET_PTHREAD_BARRIER_OUT);


/* Global variable  to indicate  that  a process  is  single-threaded.
 * Exposed as `__libc_single_threaded(3)' in `<sys/single_threaded.h>' */
#undef __libc_single_threaded
DEFINE_PUBLIC_ALIAS(__libc_single_threaded, libc___libc_single_threaded);
INTERN ATTR_SECTION(".data.crt.sched.pthread") char libc___libc_single_threaded = (char)1;
#define __libc_single_threaded GET_NOREL_GLOBAL(__libc_single_threaded)


/* Destroy a given `pthread' `self' */
LOCAL ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) void
NOTHROW(LIBCCALL destroy)(struct pthread *__restrict self) {
	/* NOTE: This also invokes TLS finalizers! */
	dltlsfreeseg(self->pt_tls);
}

LOCAL ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) void
NOTHROW(LIBCCALL decref)(struct pthread *__restrict self) {
	if (ATOMIC_FETCHDEC(self->pt_refcnt) == 1)
		destroy(self);
}


/* Attributes  used  by  `pthread_create()'  when  the  given  `ATTR'  is  NULL
 * NOTE: When `pa_stacksize' is zero, `PTHREAD_STACK_MIN' will be used instead! */
PRIVATE ATTR_SECTION(".bss.crt.sched.pthread") pthread_attr_t pthread_default_attr = {};
PRIVATE ATTR_SECTION(".bss.crt.sched.pthread") struct atomic_rwlock pthread_default_attr_lock = ATOMIC_RWLOCK_INIT;

/* Helper macros for `pthread_default_attr_lock' */
#define pthread_default_attr_mustreap()   0
#define pthread_default_attr_reap()       (void)0
#define _pthread_default_attr_reap()      (void)0
#define pthread_default_attr_write()      atomic_rwlock_write(&pthread_default_attr_lock)
#define pthread_default_attr_trywrite()   atomic_rwlock_trywrite(&pthread_default_attr_lock)
#define pthread_default_attr_endwrite()   (atomic_rwlock_endwrite(&pthread_default_attr_lock), pthread_default_attr_reap())
#define _pthread_default_attr_endwrite()  atomic_rwlock_endwrite(&pthread_default_attr_lock)
#define pthread_default_attr_read()       atomic_rwlock_read(&pthread_default_attr_lock)
#define pthread_default_attr_tryread()    atomic_rwlock_tryread(&pthread_default_attr_lock)
#define _pthread_default_attr_endread()   atomic_rwlock_endread(&pthread_default_attr_lock)
#define pthread_default_attr_endread()    (void)(atomic_rwlock_endread(&pthread_default_attr_lock) && (pthread_default_attr_reap(), 0))
#define _pthread_default_attr_end()       atomic_rwlock_end(&pthread_default_attr_lock)
#define pthread_default_attr_end()        (void)(atomic_rwlock_end(&pthread_default_attr_lock) && (pthread_default_attr_reap(), 0))
#define pthread_default_attr_upgrade()    atomic_rwlock_upgrade(&pthread_default_attr_lock)
#define pthread_default_attr_tryupgrade() atomic_rwlock_tryupgrade(&pthread_default_attr_lock)
#define pthread_default_attr_downgrade()  atomic_rwlock_downgrade(&pthread_default_attr_lock)
#define pthread_default_attr_reading()    atomic_rwlock_reading(&pthread_default_attr_lock)
#define pthread_default_attr_writing()    atomic_rwlock_writing(&pthread_default_attr_lock)
#define pthread_default_attr_canread()    atomic_rwlock_canread(&pthread_default_attr_lock)
#define pthread_default_attr_canwrite()   atomic_rwlock_canwrite(&pthread_default_attr_lock)
#define pthread_default_attr_waitread()   atomic_rwlock_waitread(&pthread_default_attr_lock)
#define pthread_default_attr_waitwrite()  atomic_rwlock_waitwrite(&pthread_default_attr_lock)



/* Called just before a thread exits (used to destroy() the thread's
 * `pthread_self'   structure  in  case  the  thread  was  detached) */
INTERN ATTR_SECTION(".text.crt.sched.pthread") void
NOTHROW(LIBCCALL libc_pthread_onexit)(struct pthread *__restrict me) {
	if (ATOMIC_FETCHDEC(me->pt_refcnt) == 1) {
		/* At some point,  our thread got  detached from its  creator,
		 * so  it is  left up to  us to destroy()  our own descriptor.
		 * Because of this, we must prevent the kernel from attempting
		 * to write into  our TID address  field (since we're  freeing
		 * the associated structure right now). */
		sys_set_tid_address(NULL);
		/* Destroy our thread. */
		destroy(me);
	}
}

INTDEF ATTR_NORETURN void __FCALL
libc_pthread_unmap_stack_and_exit(void *stackaddr,
                                  size_t stacksize,
                                  int exitcode);

#undef sys_sigprocmask
#define sys_sigprocmask(how, set, oset) \
	sys_rt_sigprocmask(how, set, oset, sizeof(sigset_t))


/* Perform cleanup & terminate the current thread `me'. */
PRIVATE ATTR_NORETURN ATTR_SECTION(".text.crt.sched.pthread") void
NOTHROW(LIBCCALL pthread_exit_thread)(struct pthread *__restrict me, int exitcode) {
	/* Mask _all_ posix signals for our thread.
	 *
	 * We  don't  want  to accidentally  invoke  signal handlers
	 * once our  TLS-state is  broken,  or once  we've  unmapped
	 * our stack.  Note that  in regards  to the  former,  POSIX
	 * requires  that  access to  `errno'  be async-signal-safe,
	 * meaning that since we use ATTR_THREAD-memory to implement
	 * errno, we mustn't run any  more signal handlers once  TLS
	 * has been torn down! */
	static sigset_t const fullset = SIGSET_INIT_FULL;
#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
	/* NOTE: If userprocmask was enabled for the calling thread, then we
	 *       have to disable it before we can safely destroy our own TLS
	 *       segment. - Otherwise, the kernel might try to write into it
	 *       after it was already free'd, resulting in data corruption.
	 * Note  that we first change our signal  mask to become the full set
	 * of signals, since the  use of `sys_set_tid_address(2)' to  disable
	 * the userprocmask mechanism will copy the then-set signal mask into
	 * kernel-space, and assign  it as  the active mask  for the  calling
	 * thread. By doing this, we don't have to do another system call  to
	 * `sigprocmask(2)' in order  to mask  signals, but can  have all  of
	 * this be done by `sys_set_tid_address(2)'. */
	if (me->pt_pmask.lpm_pmask.pm_sigmask) {
		COMPILER_BARRIER();
		ATOMIC_WRITE(me->pt_pmask.lpm_pmask.pm_sigmask, (sigset_t *)&fullset);
		COMPILER_BARRIER();
		sys_set_tid_address(&me->pt_tid);
	} else
#endif /* __LIBC_CONFIG_HAVE_USERPROCMASK */
	{
		/* Simply change our procmask to mask all signals. */
		sys_sigprocmask(SIG_SETMASK, &fullset, NULL);
	}

	if ((me->pt_flags & (PTHREAD_FUSERSTACK | PTHREAD_FNOSTACK)) == 0) {
		/* Must unmap our own stack. */
		void *stack_addr;
		size_t stack_size;
		stack_addr = me->pt_stackaddr;
		stack_size = me->pt_stacksize;
		libc_pthread_onexit(me);
		libc_pthread_unmap_stack_and_exit(stack_addr,
		                                  stack_size,
		                                  exitcode);
		__builtin_unreachable();
	}
	libc_pthread_onexit(me);
	/* Reminder: `sys_exit()' only terminates the calling thread.
	 * To terminate the calling process, you'd have to call `sys_exit_group()'! */
	sys_exit(exitcode);
	__builtin_unreachable();
}


/* Allow these to  be overwritten on  a per-architecture  basis.
 * This makes it possible for assembly to pass arguments through
 * registers to `libc_pthread_main()' in the most efficient way. */
#ifndef LIBC_PTHREAD_MAIN_CC
#define LIBC_PTHREAD_MAIN_CC __FCALL
#endif /* !LIBC_PTHREAD_MAIN_CC */
#ifndef LIBC_PTHREAD_MAIN_ARGS
#define LIBC_PTHREAD_MAIN_ARGS     \
	struct pthread *__restrict me, \
	void *(LIBCCALL start)(void *arg)
#endif /* !LIBC_PTHREAD_MAIN_ARGS */

INTERN ATTR_NORETURN ATTR_SECTION(".text.crt.sched.pthread") void
NOTHROW(LIBC_PTHREAD_MAIN_CC libc_pthread_main)(LIBC_PTHREAD_MAIN_ARGS) {
	/* NOTE: At this point, me == &current */
	int exitcode = 0;

	/* Apply the initial affinity mask (if given) */
	if (me->pt_cpuset) {
		size_t cpuset_size;
		cpuset_size = me->pt_cpusetsize;
		if (me->pt_cpuset == (cpu_set_t *)&me->pt_cpusetsize) {
			cpuset_size = sizeof(me->pt_cpusetsize);
			while (cpuset_size && ((byte_t *)&me->pt_cpusetsize)[cpuset_size - 1] == 0)
				--cpuset_size;
		}
		sys_sched_setaffinity(me->pt_tid, cpuset_size, me->pt_cpuset);
		if (me->pt_cpuset != (cpu_set_t *)&me->pt_cpusetsize)
			free(me->pt_cpuset);
	}

	/* Indicate that the process is no longer single-threaded */
	COMPILER_BARRIER();
	__libc_single_threaded = 0;
	COMPILER_BARRIER();

	TRY {
		/* Invoke the thread-main function. */
		me->pt_retval = (*start)(me->pt_retval);
	} EXCEPT {
		/* Always invoke the on-exit callback, no matter what happens! */
		if (!was_thrown(E_EXIT_THREAD)) {
			/* Anything else  can just  be propagated  directly,
			 * since it's considered an unhandled exception that
			 * will cause the process to terminate.
			 * However, E_EXIT_THREAD must be handled explicitly
			 * in  case  we  have   to  unmap  our  own   stack. */
			RETHROW();
		}
		exitcode = (int)except_data()->e_args.e_exit_thread.et_exit_code;
		me->pt_retval = PTHREAD_CANCELED;
	}

	/* Perform cleanup & terminate the current thread. */
	pthread_exit_thread(me, exitcode);
}

/* Assembly-side for the process of cloning a thread. */
INTDEF NONNULL((1, 2)) pid_t
NOTHROW(__FCALL libc_pthread_clone)(struct pthread_clone_args *__restrict args,
                                    struct pthread *__restrict thread);

struct pthread_clone_args {
	struct clone_args pca_args;              /* Clone arguments. */
	void  *(LIBCCALL *pca_start)(void *arg); /* [1..1] Thread start function */
};


PRIVATE ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_do_create)(pthread_t *__restrict newthread,
                                             pthread_attr_t const *__restrict attr,
                                             void *(LIBCCALL start_routine)(void *arg),
                                             void *__restrict arg) {
	void *tls;
	pid_t cpid;
	struct pthread *pt;
	struct pthread_clone_args args;

	/* Allocate the DL TLS segment */
	tls = dltlsallocseg();
	if unlikely(!tls)
		goto err_nomem;

	/* This should only be able to fail when libc isn't part of the static TLS
	 * segment, which can only happen when libc was loaded by dlopen(), rather
	 * having been pre-loaded by one of the initial application's DT_NEEDED-s. */
	pt = current_from_tls(tls);
	if unlikely(!pt)
		goto err_nomem_tls;

#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
	/* Initialize the new thread's initial userprocmask structure,
	 * such  that it will  lazily initialize it  the first time it
	 * performs a call to `sigprocmask(2)'. */
	bzero(&pt->pt_pmask, offsetof(struct userprocmask, pm_pending));
#if USERPROCMASK_FLAG_NORMAL != 0
	pt->pt_pmask.lpm_pmask.pm_flags = USERPROCMASK_FLAG_NORMAL;
#endif /* USERPROCMASK_FLAG_NORMAL != 0 */
	pt->pt_pmask.lpm_pmask.pm_sigsize = sizeof(sigset_t);
/*	pt->pt_pmask.lpm_pmask.pm_sigmask = NULL; */ /* Already done by the bzero (NULL means not-yet-initialized) */
#endif /* __LIBC_CONFIG_HAVE_USERPROCMASK */
	pt->pt_refcnt    = 2;
	pt->pt_flags     = PTHREAD_FNORMAL | PTHREAD_FTIDSET; /* We use `CLONE_CHILD_SETTID', so the TID is set from the get-go. */
	pt->pt_stackaddr = attr->pa_stackaddr;
	pt->pt_stacksize = attr->pa_stacksize;
	pt->pt_cpuset    = NULL;
	pt->pt_tls       = tls;

	/* Copy affinity cpuset information. */
	if (attr->pa_cpuset) {
		pt->pt_cpusetsize = attr->pa_cpusetsize;
		if (attr->pa_cpuset == (cpu_set_t *)&attr->pa_cpusetsize) {
			pt->pt_cpuset = (cpu_set_t *)&pt->pt_cpusetsize;
		} else {
			pt->pt_cpuset = (cpu_set_t *)malloc(pt->pt_cpusetsize);
			if unlikely(!pt->pt_cpuset)
				goto err_nomem_tls;
			memcpy(pt->pt_cpuset, attr->pa_cpuset, pt->pt_cpusetsize);
		}
	}

	if (!(attr->pa_flags & PTHREAD_ATTR_FLAG_STACKADDR)) {
		/* Automatically allocate a stack. */
		if (!pt->pt_stacksize)
			pt->pt_stacksize = PTHREAD_STACK_MIN;
		pt->pt_stackaddr = mmap(NULL, pt->pt_stacksize,
		                        PROT_READ | PROT_WRITE,
		                        MAP_PRIVATE | MAP_STACK | MAP_ANONYMOUS,
		                        -1, 0);
		if (pt->pt_stackaddr == MAP_FAILED)
			goto err_nomem_tls_cpuset;
	} else {
		/* The thread uses a custom, user-provided stack. */
		pt->pt_flags |= PTHREAD_FUSERSTACK;
	}

	/* Set-up clone arguments. */
	bzero(&args, sizeof(args));
	args.pca_args.ca_flags = CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE |
	                         CLONE_PARENT | CLONE_THREAD | CLONE_SYSVSEM | CLONE_SETTLS |
	                         CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_CHILD_SETTID |
	                         CLONE_IO | CLONE_PARENT_SETTID | CLONE_CRED;
	args.pca_args.ca_stack      = pt->pt_stackaddr;
	args.pca_args.ca_stack_size = pt->pt_stacksize;
	args.pca_args.ca_tls        = pt->pt_tls;
	args.pca_args.ca_parent_tid = &pt->pt_tid;
	args.pca_args.ca_child_tid  = &pt->pt_tid;
	args.pca_start              = start_routine;
	pt->pt_retval               = arg;

	/* Do the actual clone. */
	cpid = libc_pthread_clone(&args, pt);
	if unlikely(E_ISERR(cpid)) {
		/* The clone() system call failed. */
		if (pt->pt_cpuset != (cpu_set_t *)&pt->pt_cpusetsize)
			free(pt->pt_cpuset);
		dltlsfreeseg(tls);
		return (errno_t)-cpid;
	}

	/* Indicate that the process is no longer single-threaded */
	COMPILER_BARRIER();
	__libc_single_threaded = 0;
	COMPILER_BARRIER();

	/* Create as detached; iow: detach after creation... */
	if (attr->pa_flags & PTHREAD_ATTR_FLAG_DETACHSTATE)
		libc_pthread_detach(pt);
	*newthread = pt;
	return EOK;
err_nomem_tls_cpuset:
	if (pt->pt_cpuset != (cpu_set_t *)&pt->pt_cpusetsize)
		free(pt->pt_cpuset);
err_nomem_tls:
	dltlsfreeseg(tls);
err_nomem:
	return ENOMEM;
}


#ifndef __LIBCCALL_IS_LIBDCALL
struct libd_pthread_create_wrapper_struct {
	void *(LIBDCALL *start_routine)(void *arg);
	void *arg;
};
PRIVATE ATTR_SECTION(".text.crt.dos.sched.pthread") void *LIBCCALL
libd_pthread_create_wrapper(struct libd_pthread_create_wrapper_struct *arg) {
	struct libd_pthread_create_wrapper_struct cookie = *arg;
	free(arg);
	return (*cookie.start_routine)(cookie.arg);
}
#endif /* !__LIBCCALL_IS_LIBDCALL */

/*[[[head:libd_pthread_create,hash:CRC-32=0x276fa510]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
/* >> pthread_create(3)
 * Create a  new thread,  starting with  execution of  `start_routine'
 * getting passed `arg'. Creation attributed come from `attr'. The new
 * handle is stored in `*newthread'
 * @return: EOK:    Success
 * @return: EAGAIN: Insufficient resources, or operation-not-permitted
 *                  (read: `ENOMEM', but posix didn't want to use that
 *                  errno for whatever reason...) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.sched.pthread") ATTR_IN_OPT(2) ATTR_OUT(1) NONNULL((3)) errno_t
NOTHROW_NCX(LIBDCALL libd_pthread_create)(pthread_t *__restrict newthread,
                                          pthread_attr_t const *__restrict attr,
                                          void *(LIBDCALL *start_routine)(void *arg),
                                          void *arg)
/*[[[body:libd_pthread_create]]]*/
{
	errno_t result;
	struct libd_pthread_create_wrapper_struct *cookie;
	cookie = (struct libd_pthread_create_wrapper_struct *)malloc(sizeof(struct libd_pthread_create_wrapper_struct));
	if unlikely(!cookie)
		return ENOMEM;
	cookie->start_routine = start_routine;
	cookie->arg           = arg;
	result = libc_pthread_create(newthread, attr, (void *(LIBCCALL *)(void *))&libd_pthread_create_wrapper, cookie);
	if unlikely(result != EOK)
		free(cookie);
	return result;
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_pthread_create]]]*/

/*[[[head:libc_pthread_create,hash:CRC-32=0x9cc17cf4]]]*/
/* >> pthread_create(3)
 * Create a  new thread,  starting with  execution of  `start_routine'
 * getting passed `arg'. Creation attributed come from `attr'. The new
 * handle is stored in `*newthread'
 * @return: EOK:    Success
 * @return: EAGAIN: Insufficient resources, or operation-not-permitted
 *                  (read: `ENOMEM', but posix didn't want to use that
 *                  errno for whatever reason...) */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN_OPT(2) ATTR_OUT(1) NONNULL((3)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_create)(pthread_t *__restrict newthread,
                                          pthread_attr_t const *__restrict attr,
                                          void *(LIBCCALL *start_routine)(void *arg),
                                          void *arg)
/*[[[body:libc_pthread_create]]]*/
{
	errno_t result;
	if (attr) {
		result = libc_pthread_do_create(newthread, attr, start_routine, arg);
	} else {
		pthread_attr_t def;
		result = pthread_getattr_default_np(&def);
		if likely(result == EOK) {
			result = libc_pthread_do_create(newthread, &def, start_routine, arg);
			pthread_attr_destroy(&def);
		}
	}
	if unlikely(result != EOK) {
		/* Posix wants EAGAIN on insufficient-resources and operation-not-permitted
		 * Ugh... WHY YU DO DIS, POSIX???!?!? */
		if (result == ENOMEM || result == EPERM)
			result = EAGAIN;
	}
	return result;
}
/*[[[end:libc_pthread_create]]]*/

/*[[[head:libc_pthread_exit,hash:CRC-32=0xf9e0636b]]]*/
/* >> pthread_exit(3)
 * Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_NORETURN ATTR_ACCESS_NONE(1) void
(LIBCCALL libc_pthread_exit)(void *retval) THROWS(...)
/*[[[body:libc_pthread_exit]]]*/
{
	__REF struct pthread *me = &current;
	me->pt_retval = retval;
	/* TODO: Unwind the stack (using `_Unwind_ForcedUnwind') and
	 *       invoke c++ finally+catch-all  handlers, as well  as
	 *       manually  registered ones (via a custom `stop' cb),
	 *       as per `__pthread_register_cancel()' */

	/* Perform cleanup & terminate the current thread. */
	pthread_exit_thread(me, 0);
}
/*[[[end:libc_pthread_exit]]]*/

/*[[[head:libc_pthread_join,hash:CRC-32=0x61dfe688]]]*/
/* >> pthread_join(3)
 * Make calling thread wait for termination of the thread `pthread'.
 * The exit status of the  thread is stored in `*thread_return',  if
 * `thread_return' is not `NULL'.
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT_OPT(2) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_join)(pthread_t pthread,
                                        void **thread_return)
/*[[[body:libc_pthread_join]]]*/
{
	errno_t result;
	result = libc_pthread_timedjoin_np(pthread,
	                                   thread_return,
	                                   NULL);
	return result;
}
/*[[[end:libc_pthread_join]]]*/

/*[[[head:libc_pthread_getresult_np,hash:CRC-32=0x5785f489]]]*/
/* >> pthread_getresult_np(3)
 * Same as `pthread_join(3)', but don't destroy `pthread' at the end.
 * Instead, the caller must destroy `pthread' themselves via  another
 * call to `pthread_detach(3)'.
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT_OPT(2) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_getresult_np)(pthread_t pthread,
                                                void **thread_return)
/*[[[body:libc_pthread_getresult_np]]]*/
/*AUTO*/{
	(void)pthread;
	(void)thread_return;
	CRT_UNIMPLEMENTEDF("pthread_getresult_np(pthread: %" PRIxN(__SIZEOF_PTHREAD_T) ", thread_return: %p)", pthread, thread_return); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_getresult_np]]]*/

/*[[[head:libc_pthread_tryjoin_np,hash:CRC-32=0x61b8953b]]]*/
/* >> pthread_tryjoin_np(3)
 * Check whether thread `pthread' has terminated. If so return the
 * status of the thread in `*thread_return', if `thread_return' is
 * not `NULL'.
 * @return: EOK:   Success
 * @return: EBUSY: The thread has yet to terminate */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT_OPT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_tryjoin_np)(pthread_t pthread,
                                              void **thread_return)
/*[[[body:libc_pthread_tryjoin_np]]]*/
{
	if (ATOMIC_READ(pthread->pt_tid) == 0) {
		if (thread_return)
			*thread_return = pthread->pt_retval;
		decref(pthread);
		return EOK;
	}
	if unlikely(pthread == &current)
		return EDEADLK;
	return EBUSY;
}
/*[[[end:libc_pthread_tryjoin_np]]]*/

/*[[[head:libc_pthread_timedjoin_np,hash:CRC-32=0xa816bb57]]]*/
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread wait for termination of the thread `pthread',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN_OPT(3) ATTR_OUT_OPT(2) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_timedjoin_np)(pthread_t pthread,
                                                void **thread_return,
                                                struct timespec const *abstime)
/*[[[body:libc_pthread_timedjoin_np]]]*/
{
	for (;;) {
		pid_t tid;
		syscall_slong_t result;
		/* Check if the thread already terminated. */
		tid = ATOMIC_READ(pthread->pt_tid);
		if (tid == 0)
			break;
		if unlikely(pthread == &current)
			return EDEADLK;
		/* >> wait_while(pthread->pt_tid == tid) */
		result = sys_futex((uint32_t *)&pthread->pt_tid,
		                   FUTEX_WAIT, tid,
		                   abstime, NULL, 0);
		if (result == -ETIMEDOUT)
			return (errno_t)-result;
	}
	if (thread_return)
		*thread_return = pthread->pt_retval;
	decref(pthread);
	return EOK;
}
/*[[[end:libc_pthread_timedjoin_np]]]*/

/*[[[head:libc_pthread_timedjoin64_np,hash:CRC-32=0x4c479bdb]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_timedjoin64_np, libc_pthread_timedjoin_np);
#else /* MAGIC:alias */
/* >> pthread_timedjoin_np(3), pthread_timedjoin64_np(3)
 * Make calling thread wait for termination of the thread `pthread',
 * but only until `timeout'. The exit status of the thread is stored
 * in  `*thread_return',   if   `thread_return'   is   not   `NULL'.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN_OPT(3) ATTR_OUT_OPT(2) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_timedjoin64_np)(pthread_t pthread,
                                                  void **thread_return,
                                                  struct timespec64 const *abstime)
/*[[[body:libc_pthread_timedjoin64_np]]]*/
{
#if __SIZEOF_POINTER__ == 4
	for (;;) {
		pid_t tid;
		syscall_slong_t result;
		/* Check if the thread already terminated. */
		tid = ATOMIC_READ(pthread->pt_tid);
		if (tid == 0)
			break;
		if unlikely(pthread == &current)
			return EDEADLK;
		/* >> wait_while(pthread->pt_tid == tid) */
		result = sys_lfutex((uint32_t *)&pthread->pt_tid,
		                    LFUTEX_WAIT_WHILE, tid,
		                    abstime, 0);
		if (result == -ETIMEDOUT)
			return (errno_t)-result;
	}
	if (thread_return)
		*thread_return = pthread->pt_retval;
	decref(pthread);
	return EOK;
#else /* __SIZEOF_POINTER__ == 4 */
	errno_t result;
	struct timespec32 abstime32;
	abstime32.tv_sec  = (time32_t)abstime->tv_sec;
	abstime32.tv_nsec = abstime->tv_nsec;
	result = libc_pthread_timedjoin_np(pthread, thread_return, &abstime32);
	return result;
#endif /* __SIZEOF_POINTER__ != 4 */
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_timedjoin64_np]]]*/

/*[[[head:libc_pthread_detach,hash:CRC-32=0xbdd5134e]]]*/
/* >> pthread_detach(3)
 * Indicate  that the  thread `pthread' is  never to be  joined with `pthread_join(3)'.
 * The  resources  of   `pthread'  will   therefore  be  freed   immediately  when   it
 * terminates, instead of waiting for another thread to perform `pthread_join(3)' on it
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_detach)(pthread_t pthread)
/*[[[body:libc_pthread_detach]]]*/
{
	refcnt_t refcnt;
	for (;;) {
		refcnt = ATOMIC_READ(pthread->pt_refcnt);
		assert(refcnt >= 1);
		if (refcnt == 1) {
			/* Special handling requiring for when this is the last reference!
			 *
			 * In  this case,  the thread  will have  already invoked `libc_pthread_onexit()',
			 * however did not destroy() its own structure, or deleted its kernel tid-address.
			 * There is a  chance that the  thread is still  running, and that  the kernel  is
			 * still going to write 0 to the TID address.
			 *
			 * In  this case, we must wait for it to do so, since we mustn't destroy()
			 * the pthread structure before then, else the kernel might possibly write
			 * to free'd memory. */
			if (ATOMIC_READ(pthread->pt_tid) != 0) {
				sys_sched_yield();
				continue;
			}

			/* The TID field was already set to ZERO. -> Set the  reference
			 * counter to zero and destroy() the pthread structure ourself. */
			if (!ATOMIC_CMPXCH_WEAK(pthread->pt_refcnt, 1, 0))
				continue;
			destroy(pthread);
			break;
		}
		if (ATOMIC_CMPXCH_WEAK(pthread->pt_refcnt, refcnt, refcnt - 1))
			break;
	}
	return EOK;
}
/*[[[end:libc_pthread_detach]]]*/

/*[[[head:libc_pthread_self,hash:CRC-32=0xaad45458]]]*/
/* >> pthread_self(3)
 * Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_CONST WUNUSED pthread_t
NOTHROW(LIBCCALL libc_pthread_self)(void)
/*[[[body:libc_pthread_self]]]*/
{
	struct pthread *result = &current;
	if unlikely(!(result->pt_flags & PTHREAD_FTIDSET)) {
		/* Lazily initialize the thread descriptor's TID field.
		 *
		 * We get here if the calling thread was created by some API other
		 * than pthread that still made proper use of dltlsallocseg(),  or
		 * if the caller is the program's main() thread. */
		result->pt_tid = sys_set_tid_address(&result->pt_tid);
		result->pt_flags |= PTHREAD_FTIDSET;
	}
	return result;
}
/*[[[end:libc_pthread_self]]]*/

/*[[[head:libc_pthread_gettid_np,hash:CRC-32=0x1c294043]]]*/
/* >> pthread_gettid_np(3)
 * Return the TID of the given `target_thread'.
 * If the given `target_thread' has already terminated, 0 is returned
 * @return: * : The TID of the given thread
 * @return: 0 : The given `target_thread' has already terminated */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_PURE WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_pthread_gettid_np)(pthread_t target_thread)
/*[[[body:libc_pthread_gettid_np]]]*/
{
	pid_t result;
	result = target_thread->pt_tid;
	return result;
}
/*[[[end:libc_pthread_gettid_np]]]*/

/*[[[head:libc_pthread_mainthread_np,hash:CRC-32=0xff77a072]]]*/
/* >> pthread_mainthread_np(3)
 * Obtain the identifier of the main thread
 * @return: * : Handle for the main thread */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_CONST WUNUSED pthread_t
NOTHROW(LIBCCALL libc_pthread_mainthread_np)(void)
/*[[[body:libc_pthread_mainthread_np]]]*/
{
	void *maintls  = dlauxctrl(NULL, DLAUXCTRL_GET_MAIN_TLSSEG);
	pthread_t main = current_from_tls(maintls);
	if (main->pt_tid == 0) {
		/* Initially, the TID field of the main  thread's `current' will be set to  `0'.
		 * However, this setting would cause practically all other pthread APIs to think
		 * that said thread has already terminated when  in fact that has yet to  happen
		 * (and in this case  won't ever happen, since  your main thread terminating  on
		 * KOS  will automatically cause  the kernel to terminate  all other threads and
		 * consequently the entire process).
		 *
		 * However:  not to worry. - On KOS, the main thread's TID is equal to `getpid()',
		 * so  we can simply fill in that field lazily (no data race here; so-long as this
		 * function isn't called from a vfork'd child process, the PID the kernel gives us
		 * here will always be correct) */
		main->pt_tid = getpid();
	}
	return main;
}
/*[[[end:libc_pthread_mainthread_np]]]*/

/*[[[head:libc_pthread_attr_init,hash:CRC-32=0xf01da372]]]*/
/* >> pthread_attr_init(3)
 * Initialize thread  attribute `*attr'  with default  attributes (detachstate  is
 * `PTHREAD_JOINABLE', scheduling policy is `SCHED_OTHER', no user-provided stack)
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_init)(pthread_attr_t *attr)
/*[[[body:libc_pthread_attr_init]]]*/
{
	bzero(attr, sizeof(*attr));
	attr->pa_guardsize = getpagesize();
	return EOK;
}
/*[[[end:libc_pthread_attr_init]]]*/

/*[[[head:libc_pthread_attr_destroy,hash:CRC-32=0xbf9439f3]]]*/
/* >> pthread_attr_destroy(3)
 * Destroy thread attribute `*attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_destroy)(pthread_attr_t *attr)
/*[[[body:libc_pthread_attr_destroy]]]*/
{
	if likely(!(attr->pa_flags & PTHREAD_ATTR_FLAG_OLDATTR)) {
		if (attr->pa_cpuset != (cpu_set_t *)&attr->pa_cpusetsize)
			free(attr->pa_cpuset);
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_destroy]]]*/

/*[[[head:libc_pthread_attr_getdetachstate,hash:CRC-32=0x3d00db4]]]*/
/* >> pthread_attr_getdetachstate(3)
 * Get   detach   state    attribute
 * @param: *detachstate: One of `PTHREAD_CREATE_JOINABLE', `PTHREAD_CREATE_DETACHED'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getdetachstate)(pthread_attr_t const *__restrict attr,
                                                       int *__restrict detachstate)
/*[[[body:libc_pthread_attr_getdetachstate]]]*/
{
	*detachstate = (attr->pa_flags & PTHREAD_ATTR_FLAG_DETACHSTATE
	                ? PTHREAD_CREATE_DETACHED
	                : PTHREAD_CREATE_JOINABLE);
	return EOK;
}
/*[[[end:libc_pthread_attr_getdetachstate]]]*/

/*[[[head:libc_pthread_attr_setdetachstate,hash:CRC-32=0x25f43b86]]]*/
/* >> pthread_attr_setdetachstate(3)
 * Set   detach   state    attribute
 * @param: detachstate: One of `PTHREAD_CREATE_JOINABLE', `PTHREAD_CREATE_DETACHED'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `detachstate' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setdetachstate)(pthread_attr_t *attr,
                                                       int detachstate)
/*[[[body:libc_pthread_attr_setdetachstate]]]*/
{
	if (detachstate == PTHREAD_CREATE_DETACHED) {
		attr->pa_flags |= PTHREAD_ATTR_FLAG_DETACHSTATE;
	} else if (detachstate == PTHREAD_CREATE_JOINABLE) {
		attr->pa_flags &= ~PTHREAD_ATTR_FLAG_DETACHSTATE;
	} else {
		return EINVAL;
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_setdetachstate]]]*/

/*[[[head:libc_pthread_attr_getguardsize,hash:CRC-32=0xb4eb54c]]]*/
/* >> pthread_attr_getguardsize(3)
 * Get the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getguardsize)(pthread_attr_t const *__restrict attr,
                                                     size_t *__restrict guardsize)
/*[[[body:libc_pthread_attr_getguardsize]]]*/
{
	*guardsize = attr->pa_guardsize;
	return EOK;
}
/*[[[end:libc_pthread_attr_getguardsize]]]*/

/*[[[head:libc_pthread_attr_setguardsize,hash:CRC-32=0x2e265a29]]]*/
/* >> pthread_attr_setguardsize(3)
 * Set the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setguardsize)(pthread_attr_t *attr,
                                                     size_t guardsize)
/*[[[body:libc_pthread_attr_setguardsize]]]*/
{
	attr->pa_guardsize = guardsize;
	return EOK;
}
/*[[[end:libc_pthread_attr_setguardsize]]]*/

/*[[[head:libc_pthread_attr_getschedparam,hash:CRC-32=0x7227ffb5]]]*/
/* >> pthread_attr_getschedparam(3)
 * Return in `*param' the scheduling parameters of `*attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getschedparam)(pthread_attr_t const *__restrict attr,
                                                      struct sched_param *__restrict param)
/*[[[body:libc_pthread_attr_getschedparam]]]*/
{
	memcpy(param, &attr->pa_schedparam, sizeof(struct sched_param));
	return EOK;
}
/*[[[end:libc_pthread_attr_getschedparam]]]*/

/*[[[head:libc_pthread_attr_setschedparam,hash:CRC-32=0x643164c0]]]*/
/* >> pthread_attr_setschedparam(3)
 * Set scheduling parameters (priority, etc) in `*attr' according to `param'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `param' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setschedparam)(pthread_attr_t *__restrict attr,
                                                      struct sched_param const *__restrict param)
/*[[[body:libc_pthread_attr_setschedparam]]]*/
{
	memcpy(&attr->pa_schedparam, param, sizeof(struct sched_param));
	return EOK;
}
/*[[[end:libc_pthread_attr_setschedparam]]]*/

/*[[[head:libc_pthread_attr_getschedpolicy,hash:CRC-32=0x18cc1ca]]]*/
/* >> pthread_attr_getschedpolicy(3)
 * Return in `*policy' the scheduling policy of `*attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getschedpolicy)(pthread_attr_t const *__restrict attr,
                                                       int *__restrict policy)
/*[[[body:libc_pthread_attr_getschedpolicy]]]*/
{
	*policy = attr->pa_schedpolicy;
	return EOK;
}
/*[[[end:libc_pthread_attr_getschedpolicy]]]*/

/*[[[head:libc_pthread_attr_setschedpolicy,hash:CRC-32=0xd73a3f99]]]*/
/* >> pthread_attr_setschedpolicy(3)
 * Set scheduling policy in `*attr' according to `policy'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `policy' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setschedpolicy)(pthread_attr_t *attr,
                                                       int policy)
/*[[[body:libc_pthread_attr_setschedpolicy]]]*/
{
	if (policy != SCHED_OTHER && policy != SCHED_FIFO && policy != SCHED_RR)
		return EINVAL;
	attr->pa_schedpolicy = policy;
	attr->pa_flags |= PTHREAD_ATTR_FLAG_POLICY_SET;
	return EOK;
}
/*[[[end:libc_pthread_attr_setschedpolicy]]]*/

/*[[[head:libc_pthread_attr_getinheritsched,hash:CRC-32=0x2e39d18e]]]*/
/* >> pthread_attr_getinheritsched(3)
 * Return in `*inherit' the scheduling inheritance mode of `*attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getinheritsched)(pthread_attr_t const *__restrict attr,
                                                        int *__restrict inherit)
/*[[[body:libc_pthread_attr_getinheritsched]]]*/
{
	*inherit = (attr->pa_flags & PTHREAD_ATTR_FLAG_NOTINHERITSCHED
	            ? PTHREAD_EXPLICIT_SCHED
	            : PTHREAD_INHERIT_SCHED);
	return EOK;
}
/*[[[end:libc_pthread_attr_getinheritsched]]]*/

/*[[[head:libc_pthread_attr_setinheritsched,hash:CRC-32=0x4c047020]]]*/
/* >> pthread_attr_setinheritsched(3)
 * Set scheduling inheritance mode in `*attr' according to `inherit'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `inherit' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setinheritsched)(pthread_attr_t *attr,
                                                        int inherit)
/*[[[body:libc_pthread_attr_setinheritsched]]]*/
{
	if (inherit == PTHREAD_EXPLICIT_SCHED) {
		attr->pa_flags |= PTHREAD_ATTR_FLAG_NOTINHERITSCHED;
	} else if (inherit == PTHREAD_INHERIT_SCHED) {
		attr->pa_flags &= ~PTHREAD_ATTR_FLAG_NOTINHERITSCHED;
	} else {
		return EINVAL;
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_setinheritsched]]]*/

/*[[[head:libc_pthread_attr_getscope,hash:CRC-32=0xc123a249]]]*/
/* >> pthread_attr_getscope(3)
 * Return in `*scope' the scheduling contention scope of `*attr'
 * @param:  scope: Filled with one of `PTHREAD_SCOPE_*'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getscope)(pthread_attr_t const *__restrict attr,
                                                 int *__restrict scope)
/*[[[body:libc_pthread_attr_getscope]]]*/
{
	*scope = (attr->pa_flags & PTHREAD_ATTR_FLAG_SCOPEPROCESS
	          ? PTHREAD_SCOPE_PROCESS
	          : PTHREAD_SCOPE_SYSTEM);
	return EOK;
}
/*[[[end:libc_pthread_attr_getscope]]]*/

/*[[[head:libc_pthread_attr_setscope,hash:CRC-32=0xc2edf3ef]]]*/
/* >> pthread_attr_setscope(3)
 * Set scheduling contention scope in `*attr' according to `scope'
 * @param:  scope:  One of `PTHREAD_SCOPE_*'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `scope' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setscope)(pthread_attr_t *attr,
                                                 int scope)
/*[[[body:libc_pthread_attr_setscope]]]*/
{
	if (scope == PTHREAD_SCOPE_PROCESS) {
		attr->pa_flags |= PTHREAD_ATTR_FLAG_SCOPEPROCESS;
	} else if (scope == PTHREAD_SCOPE_SYSTEM) {
		attr->pa_flags &= ~PTHREAD_ATTR_FLAG_SCOPEPROCESS;
	} else {
		return EINVAL;
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_setscope]]]*/

/*[[[head:libc_pthread_attr_getstackaddr,hash:CRC-32=0x84d5175a]]]*/
/* >> pthread_attr_getstackaddr(3)
 * Return the previously set address for the stack
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_DEPRECATED("Use pthread_attr_getstack()") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstackaddr)(pthread_attr_t const *__restrict attr,
                                                     void **__restrict stackaddr)
/*[[[body:libc_pthread_attr_getstackaddr]]]*/
{
	*stackaddr = attr->pa_stackaddr;
	return EOK;
}
/*[[[end:libc_pthread_attr_getstackaddr]]]*/

/*[[[head:libc_pthread_attr_setstackaddr,hash:CRC-32=0x10c71da7]]]*/
/* >> pthread_attr_setstackaddr(3)
 * Set the starting address  of the stack of  the thread to be  created.
 * Depending on whether the stack grows up or down the value must either
 * be higher or  lower than  all the address  in the  memory block.  The
 * minimal size of the block must be `PTHREAD_STACK_MIN'
 * @return: EOK:    Success
 * @return: EINVAL: The stack isn't suitably aligned */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_DEPRECATED("Use pthread_attr_setstack()") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setstackaddr)(pthread_attr_t *attr,
                                                     void *stackaddr)
/*[[[body:libc_pthread_attr_setstackaddr]]]*/
{
	attr->pa_stackaddr = stackaddr;
	attr->pa_flags |= PTHREAD_ATTR_FLAG_STACKADDR;
	return EOK;
}
/*[[[end:libc_pthread_attr_setstackaddr]]]*/

/*[[[head:libc_pthread_attr_getstacksize,hash:CRC-32=0xe843c2b7]]]*/
/* >> pthread_attr_getstacksize(3)
 * Return the currently used minimal stack size
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstacksize)(pthread_attr_t const *__restrict attr,
                                                     size_t *__restrict stacksize)
/*[[[body:libc_pthread_attr_getstacksize]]]*/
{
	*stacksize = attr->pa_stacksize;
	return EOK;
}
/*[[[end:libc_pthread_attr_getstacksize]]]*/

/*[[[head:libc_pthread_attr_setstacksize,hash:CRC-32=0x1d7a6ccf]]]*/
/* >> pthread_attr_setstacksize(3)
 * Add information about the minimum  stack size needed for the  thread
 * to be started. This size must never be less than `PTHREAD_STACK_MIN'
 * and must also not exceed the system limits
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setstacksize)(pthread_attr_t *attr,
                                                     size_t stacksize)
/*[[[body:libc_pthread_attr_setstacksize]]]*/
{
	if unlikely(stacksize < PTHREAD_STACK_MIN)
		return EINVAL;
	attr->pa_stacksize = stacksize;
	return EOK;
}
/*[[[end:libc_pthread_attr_setstacksize]]]*/

/*[[[head:libc_pthread_attr_getstack,hash:CRC-32=0xbd5ab5a0]]]*/
/* >> pthread_attr_getstack(3)
 * Return the previously set address for the stack
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(3) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstack)(pthread_attr_t const *__restrict attr,
                                                 void **__restrict stackaddr,
                                                 size_t *__restrict stacksize)
/*[[[body:libc_pthread_attr_getstack]]]*/
{
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
	*stackaddr = (byte_t *)attr->pa_stackaddr - attr->pa_stacksize;
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
	*stackaddr = attr->pa_stackaddr;
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
	*stacksize = attr->pa_stacksize;
	return EOK;
}
/*[[[end:libc_pthread_attr_getstack]]]*/

/*[[[head:libc_pthread_attr_setstack,hash:CRC-32=0x9b8cc6e4]]]*/
/* >> pthread_attr_setstack(3)
 * The following two interfaces are intended to replace the last two. They
 * require setting the address as well as the size since only setting  the
 * address will make the implementation on some architectures impossible
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small, or the stack isn't suitably aligned */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setstack)(pthread_attr_t *attr,
                                                 void *stackaddr,
                                                 size_t stacksize)
/*[[[body:libc_pthread_attr_setstack]]]*/
{
	if (stacksize < PTHREAD_STACK_MIN)
		return EINVAL;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
	attr->pa_stackaddr = (byte_t *)stackaddr + attr->pa_stacksize;
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
	attr->pa_stackaddr = stackaddr;
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
	attr->pa_stacksize = stacksize;
	attr->pa_flags |= PTHREAD_ATTR_FLAG_STACKADDR;
	return EOK;
}
/*[[[end:libc_pthread_attr_setstack]]]*/

/*[[[head:libc_pthread_attr_setaffinity_np,hash:CRC-32=0xff0027a4]]]*/
/* >> pthread_attr_setaffinity_np(3)
 * Set cpuset on which the thread will be allowed to run
 * @return: EOK:    Success
 * @return: EINVAL: The given set contains a non-existant CPU
 * @return: ENOMEM: Insufficient memory */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) ATTR_IN_OPT(3) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setaffinity_np)(pthread_attr_t *attr,
                                                       size_t cpusetsize,
                                                       cpu_set_t const *cpuset)
/*[[[body:libc_pthread_attr_setaffinity_np]]]*/
{
	/* Truncate the cpu set */
	while (cpusetsize && ((byte_t *)cpuset)[cpusetsize - 1] == 0)
		--cpusetsize;
	if (!cpusetsize || !cpuset) {
		/* NOTE: Glibc also accepts  a zero-value in  either argument as  indicator
		 *       to clear out a previously set affinity, even though it would  make
		 *       more sense to only allow `cpusetsize == 0', and require a non-NULL
		 *       `cpuset' when `cpusetsize != 0'... */
		if (attr->pa_cpuset != (cpu_set_t *)&attr->pa_cpusetsize)
			free(attr->pa_cpuset);
		attr->pa_cpuset     = NULL;
		attr->pa_cpusetsize = 0;
	} else if (cpusetsize <= sizeof(attr->pa_cpusetsize)) {
		/* Optimization: Don't  use  the heap  for small  cpu sets.
		 * In practice, this means that we usually always get here,
		 * since most machines don't have more than 32 cpus... */
		if (attr->pa_cpuset != (cpu_set_t *)&attr->pa_cpusetsize) {
			free(attr->pa_cpuset);
			attr->pa_cpuset = (cpu_set_t *)&attr->pa_cpusetsize;
		}
		bzero(&attr->pa_cpusetsize, sizeof(attr->pa_cpusetsize));
		memcpy(&attr->pa_cpusetsize, cpuset, cpusetsize);
	} else {
		cpu_set_t *newset;
		if (attr->pa_cpuset == (cpu_set_t *)&attr->pa_cpusetsize) {
			newset = (cpu_set_t *)malloc(cpusetsize);
			if unlikely(!newset)
				return ENOMEM;
			goto use_newset;
		} else if (cpusetsize != attr->pa_cpusetsize) {
			newset = (cpu_set_t *)realloc(attr->pa_cpuset,
			                              cpusetsize);
			if unlikely(!newset)
				return ENOMEM;
use_newset:
			attr->pa_cpuset     = newset;
			attr->pa_cpusetsize = cpusetsize;
		}
		memcpy(attr->pa_cpuset, cpuset, cpusetsize);
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_setaffinity_np]]]*/

/*[[[head:libc_pthread_attr_getaffinity_np,hash:CRC-32=0x54dcd582]]]*/
/* >> pthread_attr_getaffinity_np(3)
 * Get cpuset on which the thread will be allowed to run
 * @return: EOK:    Success
 * @return: EINVAL: `cpusetsize' is too small */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT_OPT(3) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getaffinity_np)(pthread_attr_t const *attr,
                                                       size_t cpusetsize,
                                                       cpu_set_t *cpuset)
/*[[[body:libc_pthread_attr_getaffinity_np]]]*/
{
	if (attr->pa_cpuset) {
		size_t setsize;
		byte_t *p;
		setsize = attr->pa_cpusetsize;
		if (attr->pa_cpuset == (cpu_set_t *)&attr->pa_cpusetsize) {
			setsize = sizeof(attr->pa_cpusetsize);
			while (setsize && ((byte_t *)attr->pa_cpuset)[setsize - 1] == 0)
				--setsize;
		}
		/* Check if the given buffer is too small. */
		if (cpusetsize < setsize)
			return EINVAL; /* Glibc returns EINVAL here (I would have used ERANGE for this, but whatever...) */
		p = (byte_t *)mempcpy(cpuset, attr->pa_cpuset, setsize);
		/* Fill in the remainder with zeroes */
		bzero(p, cpusetsize - setsize);
	} else {
		/* No affinity set defined -> All cpus may be used. */
		memset(cpuset, 0xff, cpusetsize);
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_getaffinity_np]]]*/

/*[[[head:libc_pthread_getattr_default_np,hash:CRC-32=0x71962db]]]*/
/* >> pthread_getattr_default_np(3)
 * Get the default attributes used by `pthread_create(3)' when given `NULL' for its `attr' argument.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getattr_default_np)(pthread_attr_t *attr)
/*[[[body:libc_pthread_getattr_default_np]]]*/
{
	cpu_set_t *cpuset = NULL;
	size_t cpuset_size = 0;
again:
	pthread_default_attr_read();
	memcpy(attr, &pthread_default_attr, sizeof(pthread_attr_t));
	if (pthread_default_attr.pa_cpuset) {
		if (pthread_default_attr.pa_cpuset == (cpu_set_t *)&pthread_default_attr.pa_cpusetsize) {
			attr->pa_cpuset = (cpu_set_t *)&attr->pa_cpusetsize;
		} else if (cpuset_size != pthread_default_attr.pa_cpusetsize) {
			cpuset_size = pthread_default_attr.pa_cpusetsize;
			pthread_default_attr_endread();
			cpuset = (cpu_set_t *)reallocf(cpuset, cpuset_size);
			if unlikely(!cpuset)
				return ENOMEM;
			goto again;
		}
		attr->pa_cpuset     = cpuset;
		attr->pa_cpusetsize = cpuset_size;
		cpuset              = NULL; /* Don't free() below */
	}
	pthread_default_attr_endread();
	if (attr->pa_stacksize == 0)
		attr->pa_stacksize = PTHREAD_STACK_MIN;
	free(cpuset);
	__STATIC_IF(sizeof(pthread_attr_t) > sizeof(pthread_attr_t)) {
		bzero((byte_t *)attr + sizeof(pthread_attr_t),
		      sizeof(pthread_attr_t) - sizeof(pthread_attr_t));
	}
	return EOK;
}
/*[[[end:libc_pthread_getattr_default_np]]]*/

/*[[[head:libc_pthread_setattr_default_np,hash:CRC-32=0x18810153]]]*/
/* >> pthread_setattr_default_np(3)
 * Set the default attributes to be used by `pthread_create(3)' when given `NULL' for its `attr' argument.
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setattr_default_np)(pthread_attr_t const *attr)
/*[[[body:libc_pthread_setattr_default_np]]]*/
{
	cpu_set_t *old_set = NULL;
	cpu_set_t *new_set = NULL;
	size_t new_set_size = 0;
	if (attr->pa_cpuset &&
	    attr->pa_cpuset != (cpu_set_t *)&attr->pa_cpusetsize) {
		new_set_size = attr->pa_cpusetsize;
		new_set      = (cpu_set_t *)malloc(attr->pa_cpusetsize);
		if unlikely(!new_set)
			return ENOMEM;
	}
	pthread_default_attr_write();
	old_set = pthread_default_attr.pa_cpuset;
	if (old_set == (cpu_set_t *)&pthread_default_attr.pa_cpusetsize)
		old_set = NULL;
	if (new_set) {
		/* Set large affinity set */
		pthread_default_attr.pa_cpuset     = new_set;
		pthread_default_attr.pa_cpusetsize = new_set_size;
	} else if (attr->pa_cpuset) {
		/* Copy small affinity set */
		assert(attr->pa_cpuset == (cpu_set_t *)&attr->pa_cpusetsize);
		pthread_default_attr.pa_cpuset     = (cpu_set_t *)&pthread_default_attr.pa_cpusetsize;
		pthread_default_attr.pa_cpusetsize = attr->pa_cpusetsize;
	} else {
		/* Clear affinity */
		pthread_default_attr.pa_cpuset     = NULL;
		pthread_default_attr.pa_cpusetsize = 0;
	}
	pthread_default_attr.pa_schedparam  = attr->pa_schedparam;
	pthread_default_attr.pa_schedpolicy = attr->pa_schedpolicy;
	pthread_default_attr.pa_flags       = attr->pa_flags;
	pthread_default_attr.pa_guardsize   = attr->pa_guardsize;
	pthread_default_attr.pa_stackaddr   = attr->pa_stackaddr;
	pthread_default_attr.pa_stacksize   = attr->pa_stacksize;
	pthread_default_attr_endwrite();
	free(old_set);
	return EOK;
}
/*[[[end:libc_pthread_setattr_default_np]]]*/

PRIVATE ATTR_SECTION(".text.crt.sched.pthread") void PRPC_EXEC_CALLBACK_CC
get_stack_pointer_rpc(struct rpc_context *__restrict ctx, void *cookie) {
	*(void **)cookie = ctx;
}

/* Use /proc/self/maps to figure out the mapping containing `pointer' */
PRIVATE ATTR_SECTION(".text.crt.sched.pthread") int PRPC_EXEC_CALLBACK_CC
get_mapping_from_pointer(void *pointer, void **p_minaddr, void **p_endaddr) {
	char *line;
	FILE *fp = fopen("/proc/self/maps", "r");
	if unlikely(!fp)
		goto err;
	while ((line = fgetln(fp, NULL)) != NULL) {
		if (sscanf(line, "%p-%p", p_minaddr, p_endaddr) != 2)
			continue;
		if (pointer >= *p_minaddr && pointer < *p_endaddr) {
			/* Found it! */
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
err:
	return -1;
}

/*[[[head:libc_pthread_getattr_np,hash:CRC-32=0xa6adbade]]]*/
/* >> pthread_getattr_np(3)
 * Initialize thread  attribute `*attr'  with attributes  corresponding to  the
 * already running thread `pthread'. It shall be called on uninitialized `attr'
 * and destroyed with `pthread_attr_destroy(3)' when no longer needed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getattr_np)(pthread_t pthread,
                                              pthread_attr_t *attr)
/*[[[body:libc_pthread_getattr_np]]]*/
{
	errno_t error;
	attr->pa_flags = 0;
	if (pthread_getschedparam(pthread,
	                          &attr->pa_schedpolicy,
	                          &attr->pa_schedparam) == EOK)
		attr->pa_flags |= PTHREAD_ATTR_FLAG_SCHED_SET | PTHREAD_ATTR_FLAG_POLICY_SET;
	attr->pa_guardsize = getpagesize();
	if (pthread->pt_flags & PTHREAD_FUSERSTACK)
		attr->pa_flags |= PTHREAD_ATTR_FLAG_STACKADDR;
	if (pthread->pt_flags & PTHREAD_FNOSTACK) {
		pthread_t main;
		attr->pa_stackaddr = NULL;
		attr->pa_stacksize = 0;

		/* Check for special case: requesting information on the main thread. */
		main = pthread_mainthread_np();
		if (pthread_equal(pthread, main)) {
			void *pointer_to_main_stack;
			void *stack_min, *stack_end;
			/* If `pthread' is the main thread:
			 * #1: Check if caller if main thread. - If so, use address of some stack variable. Else,
			 *     send  an RPC whose sole purpose is to retrieve the address of some stack variable.
			 * #2: With a stack pointer on hand, use /proc/self/maps to figure out the memory
			 *     mapping that pointer is part of.
			 * #3: With information on the bounds of the discovered mapping, return those
			 *     bounds to our caller.
			 * #4: Also write-back that same information to the given `pthread' structure, such
			 *     that future requests as to the main thread's stack can be served without the
			 *     need of going through all of the hoops above. */
			if (main == &current) {
				/* Simple case: caller _is_ the main thread. */
				pointer_to_main_stack = &pointer_to_main_stack;
			} else {
				pointer_to_main_stack = (void *)-1;
				COMPILER_BARRIER();
				if unlikely(rpc_exec(main->pt_tid,
				                     RPC_SYNCMODE_ASYNC | RPC_SYSRESTART_RESTART |
				                     RPC_DOMAIN_THREAD | RPC_JOIN_WAITFOR,
				                     &get_stack_pointer_rpc, &pointer_to_main_stack) != 0)
					goto done_stack;
				COMPILER_BARRIER();
				while (ATOMIC_READ(pointer_to_main_stack) == (void *)-1)
					sched_yield();
			}
			/* Use /proc/self/maps to figure out the mapping containing `pointer_to_main_stack' */
			if unlikely(get_mapping_from_pointer(pointer_to_main_stack, &stack_min, &stack_end) != 0)
				goto done_stack;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			attr->pa_stackaddr = stack_end;
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
			attr->pa_stackaddr = stack_min;
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
			attr->pa_stacksize = (size_t)((byte_t *)stack_end - (byte_t *)stack_min);

			/* Store results in the main thread's controller. */
			COMPILER_WRITE_BARRIER();
			main->pt_stackaddr  = attr->pa_stackaddr;
			main->pt_cpusetsize = attr->pa_stacksize;
			COMPILER_WRITE_BARRIER();
			main->pt_flags &= ~PTHREAD_FNOSTACK;
			COMPILER_WRITE_BARRIER();
		}
	} else {
		attr->pa_stackaddr = pthread->pt_stackaddr;
		attr->pa_stacksize = pthread->pt_stacksize;
	}
done_stack:
	/* When the thread is running (pt_tid != 0) and has a reference  counter
	 * of `1', then  that means it  got detached. Note  the order of  checks
	 * which ensures that a thread currently exiting isn't detected as being
	 * detached! */
	if (ATOMIC_READ(pthread->pt_refcnt) == 1 &&
	    ATOMIC_READ(pthread->pt_tid) != 0)
		attr->pa_flags |= PTHREAD_ATTR_FLAG_DETACHSTATE;
	attr->pa_cpuset = (cpu_set_t *)&attr->pa_cpusetsize;
	error = pthread_getaffinity_np(pthread,
	                               sizeof(attr->pa_cpusetsize),
	                               attr->pa_cpuset);
	if (error == EOK) {
		/* Success */
	} else {
		if (error == EINVAL) {
			/* Buffer too small. */
			cpu_set_t *buf = NULL, *newbuf;
			size_t bufsize = sizeof(attr->pa_cpusetsize) * 2;
			do {
				newbuf = (cpu_set_t *)reallocf(buf, bufsize);
				if unlikely(!newbuf)
					return ENOMEM;
				buf = newbuf;
				error = pthread_getaffinity_np(pthread, bufsize, buf);
				if (error == EOK) {
					while (bufsize && ((byte_t *)buf)[bufsize - 1])
						--bufsize;
					if unlikely(!bufsize) {
						free(buf);
						attr->pa_cpuset     = NULL;
						attr->pa_cpusetsize = 0;
					} else {
						newbuf = (cpu_set_t *)realloc(buf, bufsize);
						if likely(newbuf)
							buf = newbuf;
						attr->pa_cpuset     = buf;
						attr->pa_cpusetsize = bufsize;
					}
					goto done;
				}
				if (error != EINVAL)
					break;
				bufsize *= 2;
			} while (bufsize < sizeof(attr->pa_cpusetsize) * 512);
			free(buf);
		}
		/* Indicate that the thread's affinity is unknown. */
		attr->pa_cpuset     = NULL;
		attr->pa_cpusetsize = 0;
	}
done:
	return EOK;
}
/*[[[end:libc_pthread_getattr_np]]]*/

/*[[[head:libc_pthread_setschedparam,hash:CRC-32=0x9ced1154]]]*/
/* >> pthread_setschedparam(3)
 * Set the scheduling parameters for `target_thread' according to `policy' and `*param'
 * @return: EOK:    Success
 * @return: EPERM:  The caller isn't allowed to specify `policy' and `param'
 * @return: ESRCH:  `pthread' has already exited
 * @return: EINVAL: Invalid/unsupported `policy', or `param' is malformed for `policy' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(3) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setschedparam)(pthread_t target_thread,
                                                 int policy,
                                                 struct sched_param const *param)
/*[[[body:libc_pthread_setschedparam]]]*/
{
	errno_t result;
	pid_t tid = ATOMIC_READ(target_thread->pt_tid);
	syscall_slong_t old_policy;
	struct sched_param old_param;
	if unlikely(tid == 0)
		return ESRCH; /* The given thread has already terminated. */
	old_policy = sys_sched_getscheduler(tid);
	if unlikely(E_ISERR(old_policy))
		return (errno_t)-old_policy;
	result = sys_sched_getparam(tid, &old_param);
	if unlikely(E_ISERR(result))
		return (errno_t)-result;
	result = sys_sched_setscheduler(tid, policy, param);
	if unlikely(E_ISERR(result))
		return -result;
	if unlikely(ATOMIC_READ(target_thread->pt_tid) == 0) {
		/* The thread has terminated in the mean time, and we've accidentally
		 * modified  the  scheduler  parameters  of  some  unrelated  thread.
		 * Try to undo the damage we've caused...
		 * Note: This is  a race  condition that  Glibc
		 *       doesn't even check and simply ignores! */
		sys_sched_setscheduler(tid, old_policy, &old_param);
		return ESRCH;
	}
	return EOK;
}
/*[[[end:libc_pthread_setschedparam]]]*/

/*[[[head:libc_pthread_getschedparam,hash:CRC-32=0xfea46513]]]*/
/* >> pthread_getschedparam(3)
 * Return in `*policy' and `*param' the scheduling parameters for `target_thread'
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(2) ATTR_OUT(3) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getschedparam)(pthread_t target_thread,
                                                 int *__restrict policy,
                                                 struct sched_param *__restrict param)
/*[[[body:libc_pthread_getschedparam]]]*/
{
	pid_t tid;
	errno_t result;
	syscall_slong_t sys_policy;
	tid = ATOMIC_READ(target_thread->pt_tid);
	if unlikely(tid == 0)
		return ESRCH; /* The given thread has already terminated. */
	sys_policy = sys_sched_getscheduler(tid);
	if unlikely(E_ISERR(sys_policy))
		return (errno_t)-sys_policy;
	*policy = sys_policy;
	result = sys_sched_getparam(tid, param);
	if unlikely(E_ISERR(result))
		return (errno_t)-result;
	if unlikely(ATOMIC_READ(target_thread->pt_tid) == 0) {
		/* The thread has terminated in the mean time.
		 * Note: This is  a race  condition that  Glibc
		 *       doesn't even check and simply ignores! */
		return ESRCH;
	}
	return EOK;
}
/*[[[end:libc_pthread_getschedparam]]]*/

/*[[[head:libc_pthread_setschedprio,hash:CRC-32=0x8159a410]]]*/
/* >> pthread_setschedprio(3)
 * Set the scheduling priority for `target_thread'
 * @return: EOK:    Success
 * @return: EPERM:  The caller isn't allowed to specify `prio'
 * @return: ESRCH:  `pthread' has already exited
 * @return: EINVAL: Invalid/unsupported `prio' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setschedprio)(pthread_t target_thread,
                                                int prio)
/*[[[body:libc_pthread_setschedprio]]]*/
{
	errno_t error;
	syscall_slong_t old_prio;
	pid_t tid;
	tid = ATOMIC_READ(target_thread->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	old_prio = sys_getpriority(PRIO_PROCESS, tid);
	if unlikely(E_ISERR(old_prio))
		return (errno_t)-old_prio;
	error = sys_setpriority(PRIO_PROCESS, tid, (syscall_ulong_t)(20 - prio));
	if unlikely(E_ISERR(error))
		return (errno_t)-error;
	if unlikely(ATOMIC_READ(target_thread->pt_tid) == 0) {
		/* The thread has terminated in the mean time.
		 * Note: This is  a race  condition that  Glibc
		 *       doesn't even check and simply ignores! */
		sys_setpriority(PRIO_PROCESS, tid, old_prio);
		return ESRCH;
	}
	return EOK;
}
/*[[[end:libc_pthread_setschedprio]]]*/

/*[[[head:libc_pthread_getname_np,hash:CRC-32=0x8a25bf67]]]*/
/* >> pthread_getname_np(3)
 * Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUTS(2, 3) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getname_np)(pthread_t target_thread,
                                              char *buf,
                                              size_t buflen)
/*[[[body:libc_pthread_getname_np]]]*/
{
	pid_t tid;
	fd_t commfd;
	ssize_t result;
	char pathname[lengthof("/proc/" PRIMAXu "/comm")];
	tid = ATOMIC_READ(target_thread->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	sprintf(pathname, "/proc/%u/comm", tid);
	commfd = sys_open(pathname, O_RDONLY, 0);
	if unlikely(E_ISERR(commfd))
		return -commfd;
	result = sys_read(commfd, buf, buflen);
	sys_close(commfd);
	if (E_ISERR(result))
		return -result;
	if ((size_t)result == buflen)
		return ERANGE;  /* Need more space for trailing NUL */
	buf[result] = '\0'; /* Append trailing NUL */
	return EOK;
}
/*[[[end:libc_pthread_getname_np]]]*/

/*[[[head:libc_pthread_setname_np,hash:CRC-32=0xb7eccf60]]]*/
/* >> pthread_setname_np(3)
 * Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setname_np)(pthread_t target_thread,
                                              const char *name)
/*[[[body:libc_pthread_setname_np]]]*/
{
	pid_t tid;
	ssize_t result;
	tid = ATOMIC_READ(target_thread->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
#ifndef __OPTIMIZE_SIZE__
	if (target_thread == &current) {
		/* Simple case: can use a dedicated prctl code to set the name. */
		result = sys_prctl(PR_SET_NAME, (syscall_ulong_t)(uintptr_t)name, 0, 0, 0);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		/* Just like under linux,  KOS's /proc/[pid]/comm file always  re-returns
		 * the given `num_bytes' argument, rather than return the # of bytes that
		 * were actually written to the thread's comm name.
		 *
		 * Because of this (and because we mustn't modify the thread's actual
		 * name in case the caller-given name is too long), we have to  check
		 * the length of `name' before even passing it along to the kernel! */
		fd_t commfd;
		char pathname[lengthof("/proc/" PRIMAXu "/comm")];
		size_t namelen = strlen(name);
#ifdef TASK_COMM_LEN
		if unlikely(namelen > (TASK_COMM_LEN - 1))
			return ERANGE;
#endif /* TASK_COMM_LEN */
		sprintf(pathname, "/proc/%u/comm", tid);
		commfd = sys_open(pathname, O_WRONLY, 0);
		if unlikely(E_ISERR(commfd))
			return -commfd;
		result = sys_write(commfd, name, namelen * sizeof(char));
		sys_close(commfd);
	}
	if (E_ISERR(result))
		return -result;
	return EOK;
}
/*[[[end:libc_pthread_setname_np]]]*/

PRIVATE ATTR_SECTION(".bss.crt.sched.pthread") int pthread_concurrency_level = 0;

/*[[[head:libc_pthread_getconcurrency,hash:CRC-32=0x2040f7e9]]]*/
/* >> pthread_getconcurrency(3)
 * Determine level of concurrency
 * @return: * : The current concurrency level */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_PURE int
NOTHROW_NCX(LIBCCALL libc_pthread_getconcurrency)(void)
/*[[[body:libc_pthread_getconcurrency]]]*/
{
	return pthread_concurrency_level;
}
/*[[[end:libc_pthread_getconcurrency]]]*/

/*[[[head:libc_pthread_setconcurrency,hash:CRC-32=0xed028bd5]]]*/
/* >> pthread_setconcurrency(3)
 * Set new concurrency level to `level'
 * @return: EOK:    Success
 * @return: EINVAL: The given `level' is negative */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setconcurrency)(int level)
/*[[[body:libc_pthread_setconcurrency]]]*/
{
	if unlikely(level < 0)
		return EINVAL;
	pthread_concurrency_level = level;
	return EOK;
}
/*[[[end:libc_pthread_setconcurrency]]]*/

/*[[[head:libc_pthread_setaffinity_np,hash:CRC-32=0x9346fc31]]]*/
/* >> pthread_setaffinity_np(3)
 * Limit specified thread `pthread' to run only on the processors represented in `cpuset'
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN_OPT(3) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setaffinity_np)(pthread_t pthread,
                                                  size_t cpusetsize,
                                                  cpu_set_t const *cpuset)
/*[[[body:libc_pthread_setaffinity_np]]]*/
{
	errno_t error;
	size_t old_cpusetsize;
	cpu_set_t *old_cpuset = (cpu_set_t *)&old_cpusetsize;
	pid_t tid = ATOMIC_READ(pthread->pt_tid);
	if (tid == 0)
		return ESRCH;
	error = sys_sched_getaffinity(tid, sizeof(old_cpusetsize), old_cpuset);
	if (error == EINVAL) {
		/* Buffer too small. */
		cpu_set_t *buf = NULL, *newbuf;
		size_t bufsize = sizeof(old_cpusetsize) * 2;
		for (;;) {
			newbuf = (cpu_set_t *)reallocf(buf, bufsize);
			if unlikely(!newbuf)
				return ENOMEM;
			buf = newbuf;
			error = sys_sched_getaffinity(tid, bufsize, buf);
			if (E_ISOK(error)) {
				while (bufsize && ((byte_t *)buf)[bufsize - 1])
					--bufsize;
				if unlikely(!bufsize) {
					free(buf);
					old_cpuset     = NULL;
					old_cpusetsize = 0;
				} else {
					newbuf = (cpu_set_t *)realloc(buf, bufsize);
					if likely(newbuf)
						buf = newbuf;
					old_cpuset     = buf;
					old_cpusetsize = bufsize;
				}
				goto got_old_affinity;
			}
			if (error != -EINVAL || (bufsize >= sizeof(old_cpusetsize) * 512)) {
				free(buf);
				goto err;
			}
			bufsize *= 2;
		}
		free(buf);
	}
got_old_affinity:
	error = sys_sched_setaffinity(tid, cpusetsize, cpuset);
	if (E_ISOK(error)) {
		if unlikely(ATOMIC_READ(pthread->pt_tid) == 0) {
			/* The thread has terminated in the mean time.
			 * Note: This is  a race  condition that  Glibc
			 *       doesn't even check and simply ignores! */
			sys_sched_setaffinity(tid, old_cpusetsize, old_cpuset);
			error = -ESRCH;
		}
	}
	if (old_cpuset != (cpu_set_t *)&old_cpusetsize)
		free(old_cpuset);
err:
	return (errno_t)-error;
}
/*[[[end:libc_pthread_setaffinity_np]]]*/

/*[[[head:libc_pthread_getaffinity_np,hash:CRC-32=0x8c8cf63c]]]*/
/* >> pthread_getaffinity_np(3)
 * Get bit set in `cpuset' representing the processors `pthread' can run on
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT_OPT(3) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getaffinity_np)(pthread_t pthread,
                                                  size_t cpusetsize,
                                                  cpu_set_t *cpuset)
/*[[[body:libc_pthread_getaffinity_np]]]*/
{
	errno_t error;
	pid_t tid = ATOMIC_READ(pthread->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	error = sys_sched_getaffinity(tid, cpusetsize, cpuset);
	if (E_ISOK(error)) {
		if unlikely(ATOMIC_READ(pthread->pt_tid) == 0) {
			/* The thread has terminated in the mean time.
			 * Note: This is  a race  condition that  Glibc
			 *       doesn't even check and simply ignores! */
			error = -ESRCH;
		}
	}
	return (errno_t)-error;
}
/*[[[end:libc_pthread_getaffinity_np]]]*/


/*[[[head:libc_pthread_setcancelstate,hash:CRC-32=0x96bf0b1e]]]*/
/* >> pthread_setcancelstate(3)
 * Set  cancelability  state   of  current   thread  to   `state',
 * returning old state in `*oldstate' if `oldstate' is not `NULL'.
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `state' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT_OPT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setcancelstate)(int state,
                                                  int *oldstate)
/*[[[body:libc_pthread_setcancelstate]]]*/
/*AUTO*/{
	(void)state;
	(void)oldstate;
	CRT_UNIMPLEMENTEDF("pthread_setcancelstate(state: %x, oldstate: %p)", state, oldstate); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_setcancelstate]]]*/

/*[[[head:libc_pthread_setcanceltype,hash:CRC-32=0x3e41f119]]]*/
/* >> pthread_setcanceltype(3)
 * Set cancellation state of current thread to `type',
 * returning the old type in `*oldtype' if `oldtype' is not `NULL'.
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `type' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT_OPT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setcanceltype)(int type,
                                                 int *oldtype)
/*[[[body:libc_pthread_setcanceltype]]]*/
/*AUTO*/{
	(void)type;
	(void)oldtype;
	CRT_UNIMPLEMENTEDF("pthread_setcanceltype(type: %x, oldtype: %p)", type, oldtype); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_setcanceltype]]]*/

PRIVATE ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
pthread_cancel_self_rpc(struct rpc_context *__restrict UNUSED(ctx), void *UNUSED(cookie)) {
	THROW(E_EXIT_THREAD);
}


/*[[[head:libc_pthread_cancel,hash:CRC-32=0x94f5477c]]]*/
/* >> pthread_cancel(3)
 * Cancel `pthread' immediately or at the next possibility
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cancel)(pthread_t pthread)
/*[[[body:libc_pthread_cancel]]]*/
{
	pid_t tid;
	tid = ATOMIC_READ(pthread->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	/* NOTE: Use `RPC_JOIN_ASYNC' for joining since `pthread_cancel(3)' isn't
	 *       a cancellation point itself,  and `rpc_exec()' becomes one  when
	 *       `RPC_JOIN_WAITFOR' is used. */

	/* TODO: Support for `PTHREAD_CANCEL_ENABLE' / `PTHREAD_CANCEL_DISABLE':
	 *  - Could be implemented by using a dedicated signal here, and having
	 *    the thread be able to mask/unmask it via `pthread_setcancelstate'
	 *  - As far as I know, picking a dedicated signal is also how Glibc
	 *    goes about implementing this. (only that it uses regular,  old
	 *    posix signal handlers, rather than fancy RPCs like we do)
	 *  - Currently, this right here uses SIGRPC for RPC delivery */

	/* TODO: Support for `PTHREAD_CANCEL_DEFERRED' / `PTHREAD_CANCEL_ASYNCHRONOUS':
	 *  - Could be implemented very easily by:
	 *     - Using `RPC_SYNCMODE_CP' for `PTHREAD_CANCEL_DEFERRED'
	 *     - Using `RPC_SYNCMODE_ASYNC' for `PTHREAD_CANCEL_ASYNCHRONOUS'
	 *       NOTE: When a thread switches to `RPC_SYNCMODE_ASYNC', it must
	 *             also call `sys_rpc_serve()' in  order to deal with  any
	 *             CP-based cancel RPC  send before the  change was  made.
	 *             When transitioning in the other direction, no such call
	 *             is needed since the async  may literally happen at  any
	 *             point.
	 *  - Currently, `RPC_SYNCMODE_CP' is being hard-coded. */
	if unlikely(rpc_exec(tid, RPC_SYNCMODE_CP | RPC_DOMAIN_THREAD | RPC_JOIN_ASYNC,
	                     &pthread_cancel_self_rpc, NULL) != 0)
		return libc_geterrno();
	return EOK;
}
/*[[[end:libc_pthread_cancel]]]*/

/*[[[head:libc_pthread_testcancel,hash:CRC-32=0xde2da9fc]]]*/
/* >> pthread_testcancel(3)
 * Test for pending cancellation for the current thread and terminate the
 * thread as per `pthread_exit(PTHREAD_CANCELED)' if it has been canceled */
INTERN ATTR_SECTION(".text.crt.sched.pthread") void
NOTHROW_RPC(LIBCCALL libc_pthread_testcancel)(void)
/*[[[body:libc_pthread_testcancel]]]*/
{
	sys_rpc_serve();
}
/*[[[end:libc_pthread_testcancel]]]*/

/*[[[head:libc_pthread_getcpuclockid,hash:CRC-32=0x9dc80c76]]]*/
/* >> pthread_getcpuclockid(3)
 * Get the ID of CPU-time clock for thread `pthread'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getcpuclockid)(pthread_t pthread,
                                                 clockid_t *clock_id)
/*[[[body:libc_pthread_getcpuclockid]]]*/
/*AUTO*/{
	(void)pthread;
	(void)clock_id;
	CRT_UNIMPLEMENTEDF("pthread_getcpuclockid(pthread: %" PRIxN(__SIZEOF_PTHREAD_T) ", clock_id: %p)", pthread, clock_id); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_getcpuclockid]]]*/

/*[[[head:libc_pthread_rpc_exec,hash:CRC-32=0xd42ab8fa]]]*/
/* >> pthread_rpc_exec(3)
 * Schedule an RPC for `target_thread' to-be executed the next  time
 * it makes a call to a cancellation-point system call (or interrupt
 * an active system call, should one such currently be in progress).
 *   - RPCs are also executed by `pthread_testcancel(3)'
 *   - The `struct rpc_context' structure is defined in `<kos/rpc.h>'
 * @return: 0:      Success
 * @return: ENOMEM: Insufficient system memory
 * @return: ESRCH:  The given `target_thread' has already terminated */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rpc_exec)(pthread_t target_thread,
                                            void (LIBKCALL *func)(struct rpc_context *__restrict ctx, void *cookie),
                                            void *cookie)
/*[[[body:libc_pthread_rpc_exec]]]*/
{
	pid_t tid;
	tid = ATOMIC_READ(target_thread->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	/* Schedule  an RPC in the target thread that  will cause the thread to terminate itself.
	 * Note that this RPC is scheduled to only execute the next time a call to a cancellation
	 * point  system call is  made, and that system  call ends up  blocking (iow: calling the
	 * kernel function `task_serve()') */
	if unlikely(rpc_exec(tid, RPC_SYNCMODE_CP | RPC_DOMAIN_THREAD | RPC_JOIN_WAITFOR, func, cookie) != 0)
		return libc_geterrno();
	return EOK;
}
/*[[[end:libc_pthread_rpc_exec]]]*/

















/************************************************************************/
/* MISC PTHREAD FUNCTIONS                                               */
/************************************************************************/

/*[[[head:libc_pthread_atfork,hash:CRC-32=0xaf6eedad]]]*/
/* >> pthread_atfork(3)
 * Install handlers to be called when a new process is created with  `fork(2)'.
 * The `prepare' handler is called in the parent process just before performing
 * `fork(2)'. The `parent' handler is called  in the parent process just  after
 * `fork(2)'.  The `child' handler is called in  the child process. Each of the
 * three  handlers can be `NULL', meaning that no handler needs to be called at
 * that point.
 * `pthread_atfork(3)' can be called several times, in which case the `prepare'
 * handlers are  called in  LIFO order  (last added  with  `pthread_atfork(3)',
 * first  called before `fork(2)'),  and the `parent'  and `child' handlers are
 * called in FIFO order (first added -> first called)
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to register callbacks */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_atfork)(void (LIBCCALL *prepare)(void),
                                          void (LIBCCALL *parent)(void),
                                          void (LIBCCALL *child)(void))
/*[[[body:libc_pthread_atfork]]]*/
/*AUTO*/{
	(void)prepare;
	(void)parent;
	(void)child;
	CRT_UNIMPLEMENTEDF("pthread_atfork(prepare: %p, parent: %p, child: %p)", prepare, parent, child); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_atfork]]]*/

/*[[[head:libc___pthread_register_cancel,hash:CRC-32=0xa8bf5df4]]]*/
INTERN ATTR_SECTION(".text.crt.sched.pthread") __cleanup_fct_attribute void
NOTHROW_NCX(LIBCCALL libc___pthread_register_cancel)(__pthread_unwind_buf_t *buf)
/*[[[body:libc___pthread_register_cancel]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("__pthread_register_cancel(buf: %p)", buf); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc___pthread_register_cancel]]]*/

/*[[[head:libc___pthread_unregister_cancel,hash:CRC-32=0x79cf6309]]]*/
INTERN ATTR_SECTION(".text.crt.sched.pthread") __cleanup_fct_attribute ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc___pthread_unregister_cancel)(__pthread_unwind_buf_t *buf)
/*[[[body:libc___pthread_unregister_cancel]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("__pthread_unregister_cancel(buf: %p)", buf); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc___pthread_unregister_cancel]]]*/

/*[[[head:libc___pthread_register_cancel_defer,hash:CRC-32=0xe3d84e6b]]]*/
INTERN ATTR_SECTION(".text.crt.sched.pthread") __cleanup_fct_attribute ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc___pthread_register_cancel_defer)(__pthread_unwind_buf_t *buf)
/*[[[body:libc___pthread_register_cancel_defer]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("__pthread_register_cancel_defer(buf: %p)", buf); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc___pthread_register_cancel_defer]]]*/

/*[[[head:libc___pthread_unregister_cancel_restore,hash:CRC-32=0x76a3bdce]]]*/
INTERN ATTR_SECTION(".text.crt.sched.pthread") __cleanup_fct_attribute ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc___pthread_unregister_cancel_restore)(__pthread_unwind_buf_t *buf)
/*[[[body:libc___pthread_unregister_cancel_restore]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("__pthread_unregister_cancel_restore(buf: %p)", buf); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc___pthread_unregister_cancel_restore]]]*/

/*[[[head:libc___pthread_unwind_next,hash:CRC-32=0xf9e7c536]]]*/
/* Internal interface to initiate cleanup */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_WEAK __cleanup_fct_attribute ATTR_INOUT(1) void
NOTHROW_NCX(LIBCCALL libc___pthread_unwind_next)(__pthread_unwind_buf_t *buf)
/*[[[body:libc___pthread_unwind_next]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("__pthread_unwind_next(buf: %p)", buf); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc___pthread_unwind_next]]]*/















/************************************************************************/
/* pthread_mutexattr_t                                                  */
/************************************************************************/

/*[[[head:libc_pthread_mutexattr_init,hash:CRC-32=0xa78a3d95]]]*/
/* >> pthread_mutexattr_init(3)
 * Initialize mutex attribute object `attr' with default
 * attributes    (kind    is   `PTHREAD_MUTEX_TIMED_NP')
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_init)(pthread_mutexattr_t *attr)
/*[[[body:libc_pthread_mutexattr_init]]]*/
{
	attr->ma_kind = PTHREAD_MUTEX_NORMAL;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_init]]]*/

/*[[[head:libc_pthread_mutexattr_destroy,hash:CRC-32=0x6c7305a7]]]*/
/* >> pthread_mutexattr_destroy(3)
 * Destroy mutex attribute object `attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_destroy)(pthread_mutexattr_t *attr)
/*[[[body:libc_pthread_mutexattr_destroy]]]*/
{
	(void)attr;
	DBG_memset(attr, 0xcc, sizeof(*attr));
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_destroy]]]*/

/*[[[head:libc_pthread_mutexattr_getpshared,hash:CRC-32=0x6e6f15a5]]]*/
/* >> pthread_mutexattr_getpshared(3)
 * Get the process-shared flag of the mutex attribute `attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getpshared)(pthread_mutexattr_t const *__restrict attr,
                                                        int *__restrict pshared)
/*[[[body:libc_pthread_mutexattr_getpshared]]]*/
{
	*pshared = attr->ma_kind & PTHREAD_MUTEXATTR_FLAG_PSHARED
	           ? PTHREAD_PROCESS_SHARED
	           : PTHREAD_PROCESS_PRIVATE;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_getpshared]]]*/

/*[[[head:libc_pthread_mutexattr_setpshared,hash:CRC-32=0xc107b25d]]]*/
/* >> pthread_mutexattr_setpshared(3)
 * Set the process-shared flag of the mutex attribute `attr'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setpshared)(pthread_mutexattr_t *attr,
                                                        int pshared)
/*[[[body:libc_pthread_mutexattr_setpshared]]]*/
{
	if unlikely(pshared != PTHREAD_PROCESS_PRIVATE &&
	            pshared != PTHREAD_PROCESS_SHARED)
		return EINVAL;
	attr->ma_kind &= ~PTHREAD_MUTEXATTR_FLAG_PSHARED;
	if (pshared == PTHREAD_PROCESS_SHARED)
		attr->ma_kind |= PTHREAD_MUTEXATTR_FLAG_PSHARED;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_setpshared]]]*/

/*[[[head:libc_pthread_mutexattr_gettype,hash:CRC-32=0x66f44ef4]]]*/
/* >> pthread_mutexattr_gettype(3)
 * Return in `*kind' the mutex kind attribute in `*attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_gettype)(pthread_mutexattr_t const *__restrict attr,
                                                     int *__restrict kind)
/*[[[body:libc_pthread_mutexattr_gettype]]]*/
{
	*kind = attr->ma_kind & PTHREAD_MUTEXATTR_KIND_MASK;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_gettype]]]*/

/*[[[head:libc_pthread_mutexattr_settype,hash:CRC-32=0xeca18daa]]]*/
/* >> pthread_mutexattr_settype(3)
 * Set  the mutex kind attribute in `*attr' to `kind' (either `PTHREAD_MUTEX_NORMAL',
 * `PTHREAD_MUTEX_RECURSIVE', `PTHREAD_MUTEX_ERRORCHECK', or `PTHREAD_MUTEX_DEFAULT')
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_settype)(pthread_mutexattr_t *attr,
                                                     int kind)
/*[[[body:libc_pthread_mutexattr_settype]]]*/
{
	if unlikely(kind != PTHREAD_MUTEX_TIMED_NP &&
	            kind != PTHREAD_MUTEX_RECURSIVE &&
	            kind != PTHREAD_MUTEX_ERRORCHECK &&
	            kind != PTHREAD_MUTEX_ADAPTIVE_NP)
		return EINVAL;
	attr->ma_kind &= ~PTHREAD_MUTEXATTR_KIND_MASK;
	attr->ma_kind |= kind;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_settype]]]*/

/*[[[head:libc_pthread_mutexattr_getprotocol,hash:CRC-32=0x3dda78bc]]]*/
/* >> pthread_mutexattr_getprotocol(3)
 * Return in `*protocol' the mutex protocol attribute in `*attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getprotocol)(pthread_mutexattr_t const *__restrict attr,
                                                         int *__restrict protocol)
/*[[[body:libc_pthread_mutexattr_getprotocol]]]*/
{
	*protocol = (attr->ma_kind & PTHREAD_MUTEXATTR_PROTOCOL_MASK) >>
	            PTHREAD_MUTEXATTR_PROTOCOL_SHIFT;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_getprotocol]]]*/

/*[[[head:libc_pthread_mutexattr_setprotocol,hash:CRC-32=0x234b23e0]]]*/
/* >> pthread_mutexattr_setprotocol(3)
 * Set  the  mutex protocol  attribute  in `*attr'  to  `protocol' (either
 * `PTHREAD_PRIO_NONE', `PTHREAD_PRIO_INHERIT', or `PTHREAD_PRIO_PROTECT')
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `protocol' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setprotocol)(pthread_mutexattr_t *attr,
                                                         int protocol)
/*[[[body:libc_pthread_mutexattr_setprotocol]]]*/
{
	if unlikely(protocol != PTHREAD_PRIO_NONE &&
	            protocol != PTHREAD_PRIO_INHERIT &&
	            protocol != PTHREAD_PRIO_PROTECT)
		return EINVAL;
	attr->ma_kind &= ~PTHREAD_MUTEXATTR_PROTOCOL_MASK;
	attr->ma_kind |= protocol << PTHREAD_MUTEXATTR_PROTOCOL_SHIFT;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_setprotocol]]]*/

/*[[[head:libc_pthread_mutexattr_getprioceiling,hash:CRC-32=0x6ab218d0]]]*/
/* >> pthread_mutexattr_getprioceiling(3)
 * Return in `*prioceiling' the mutex prioceiling attribute in `*attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getprioceiling)(pthread_mutexattr_t const *__restrict attr,
                                                            int *__restrict prioceiling)
/*[[[body:libc_pthread_mutexattr_getprioceiling]]]*/
{
	*prioceiling = (attr->ma_kind & PTHREAD_MUTEXATTR_PRIO_CEILING_MASK) >>
	               PTHREAD_MUTEXATTR_PRIO_CEILING_SHIFT;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_getprioceiling]]]*/

/*[[[head:libc_pthread_mutexattr_setprioceiling,hash:CRC-32=0x7f831144]]]*/
/* >> pthread_mutexattr_setprioceiling(3)
 * Set the mutex prioceiling attribute in `*attr' to `prioceiling'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setprioceiling)(pthread_mutexattr_t *attr,
                                                            int prioceiling)
/*[[[body:libc_pthread_mutexattr_setprioceiling]]]*/
{
	int min, max;
	min = sched_get_priority_min(SCHED_FIFO);
	if unlikely(min < 0)
		return libc_geterrno();
	if unlikely((unsigned int)prioceiling < (unsigned int)min)
		return EINVAL;
	max = sched_get_priority_max(SCHED_FIFO);
	if unlikely(max < 0)
		return libc_geterrno();
	if unlikely((unsigned int)prioceiling > (unsigned int)max)
		return EINVAL;
	attr->ma_kind &= ~PTHREAD_MUTEXATTR_PRIO_CEILING_MASK;
	attr->ma_kind |= (unsigned int)prioceiling << PTHREAD_MUTEXATTR_PRIO_CEILING_SHIFT;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_setprioceiling]]]*/

/*[[[head:libc_pthread_mutexattr_getrobust,hash:CRC-32=0xf1afd605]]]*/
/* >> pthread_mutexattr_getrobust(3)
 * Get the robustness flag of the mutex attribute `attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getrobust)(pthread_mutexattr_t const *__restrict attr,
                                                       int *__restrict robustness)
/*[[[body:libc_pthread_mutexattr_getrobust]]]*/
{
	*robustness = ((attr->ma_kind & PTHREAD_MUTEXATTR_FLAG_ROBUST) != 0
	               ? PTHREAD_MUTEX_ROBUST
	               : PTHREAD_MUTEX_STALLED);
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_getrobust]]]*/

/*[[[head:libc_pthread_mutexattr_setrobust,hash:CRC-32=0x6ffbe8b4]]]*/
/* >> pthread_mutexattr_setrobust(3)
 * Set the robustness flag of the mutex attribute `attr'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `robustness' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setrobust)(pthread_mutexattr_t *attr,
                                                       int robustness)
/*[[[body:libc_pthread_mutexattr_setrobust]]]*/
{
	if unlikely(robustness != PTHREAD_MUTEX_STALLED &&
	            robustness != PTHREAD_MUTEX_ROBUST)
		return EINVAL;
	attr->ma_kind &= ~PTHREAD_MUTEXATTR_FLAG_ROBUST;
	if (robustness == PTHREAD_MUTEX_ROBUST)
		attr->ma_kind |= PTHREAD_MUTEXATTR_FLAG_ROBUST;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_setrobust]]]*/















/************************************************************************/
/* pthread_rwlockattr_t                                                 */
/************************************************************************/

/*[[[head:libc_pthread_rwlockattr_init,hash:CRC-32=0x215f158b]]]*/
/* >> pthread_rwlockattr_init(3)
 * Initialize attribute object `attr' with default values
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_init)(pthread_rwlockattr_t *attr)
/*[[[body:libc_pthread_rwlockattr_init]]]*/
{
	attr->rwa_kind   = PTHREAD_RWLOCK_DEFAULT_NP;
	attr->rwa_shared = PTHREAD_PROCESS_PRIVATE;
	return EOK;
}
/*[[[end:libc_pthread_rwlockattr_init]]]*/

/*[[[head:libc_pthread_rwlockattr_destroy,hash:CRC-32=0x1cccea8e]]]*/
/* >> pthread_rwlockattr_destroy(3)
 * Destroy attribute object  `attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_destroy)(pthread_rwlockattr_t *attr)
/*[[[body:libc_pthread_rwlockattr_destroy]]]*/
{
	(void)attr;
	DBG_memset(attr, 0xcc, sizeof(*attr));
	return EOK;
}
/*[[[end:libc_pthread_rwlockattr_destroy]]]*/

/*[[[head:libc_pthread_rwlockattr_getpshared,hash:CRC-32=0x9ad9fc3]]]*/
/* >> pthread_rwlockattr_getpshared(3)
 * Return current setting of process-shared attribute of `attr' in `*pshared'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_getpshared)(pthread_rwlockattr_t const *__restrict attr,
                                                         int *__restrict pshared)
/*[[[body:libc_pthread_rwlockattr_getpshared]]]*/
{
	*pshared = attr->rwa_shared;
	return EOK;
}
/*[[[end:libc_pthread_rwlockattr_getpshared]]]*/

/*[[[head:libc_pthread_rwlockattr_setpshared,hash:CRC-32=0x99931321]]]*/
/* >> pthread_rwlockattr_setpshared(3)
 * Set process-shared attribute of `attr' to `pshared'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pthread' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_setpshared)(pthread_rwlockattr_t *attr,
                                                         int pshared)
/*[[[body:libc_pthread_rwlockattr_setpshared]]]*/
{
	if unlikely(pshared != PTHREAD_PROCESS_PRIVATE &&
	            pshared != PTHREAD_PROCESS_SHARED)
		return EINVAL;
	attr->rwa_shared = pshared;
	return EOK;
}
/*[[[end:libc_pthread_rwlockattr_setpshared]]]*/

/*[[[head:libc_pthread_rwlockattr_getkind_np,hash:CRC-32=0xbfef8f69]]]*/
/* >> pthread_rwlockattr_getkind_np(3)
 * Return current setting of reader/writer preference
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_getkind_np)(pthread_rwlockattr_t const *__restrict attr,
                                                         int *__restrict pref)
/*[[[body:libc_pthread_rwlockattr_getkind_np]]]*/
{
	*pref = attr->rwa_kind;
	return EOK;
}
/*[[[end:libc_pthread_rwlockattr_getkind_np]]]*/

/*[[[head:libc_pthread_rwlockattr_setkind_np,hash:CRC-32=0xa3abbd89]]]*/
/* >> pthread_rwlockattr_setkind_np(3)
 * Set     reader/write     preference
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pref' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_setkind_np)(pthread_rwlockattr_t *attr,
                                                         int pref)
/*[[[body:libc_pthread_rwlockattr_setkind_np]]]*/
{
	if unlikely(pref != PTHREAD_RWLOCK_PREFER_READER_NP &&
	            pref != PTHREAD_RWLOCK_PREFER_WRITER_NP &&
	            pref != PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP)
		return EINVAL;
	attr->rwa_kind = pref;
	return EOK;
}
/*[[[end:libc_pthread_rwlockattr_setkind_np]]]*/















/************************************************************************/
/* pthread_condattr_t                                                   */
/************************************************************************/

/*[[[head:libc_pthread_condattr_init,hash:CRC-32=0x918cd8a2]]]*/
/* >> pthread_condattr_init(3)
 * Initialize condition variable attribute `attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_init)(pthread_condattr_t *attr)
/*[[[body:libc_pthread_condattr_init]]]*/
{
	attr->ca_value = CLOCK_REALTIME << PTHREAD_CONDATTR_CLOCKID_SHIFT;
	return EOK;
}
/*[[[end:libc_pthread_condattr_init]]]*/

/*[[[head:libc_pthread_condattr_destroy,hash:CRC-32=0xd3596eac]]]*/
/* >> pthread_condattr_destroy(3)
 * Destroy condition variable attribute `attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_destroy)(pthread_condattr_t *attr)
/*[[[body:libc_pthread_condattr_destroy]]]*/
{
	(void)attr;
	DBG_memset(attr, 0xcc, sizeof(*attr));
	return EOK;
}
/*[[[end:libc_pthread_condattr_destroy]]]*/

/*[[[head:libc_pthread_condattr_getpshared,hash:CRC-32=0x851a6d7a]]]*/
/* >> pthread_condattr_getpshared(3)
 * Get the process-shared flag of the condition variable attribute `attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_getpshared)(pthread_condattr_t const *__restrict attr,
                                                       int *__restrict pshared)
/*[[[body:libc_pthread_condattr_getpshared]]]*/
{
	*pshared = attr->ca_value & PTHREAD_CONDATTR_FLAG_PSHARED
	           ? PTHREAD_PROCESS_SHARED
	           : PTHREAD_PROCESS_PRIVATE;
	return EOK;
}
/*[[[end:libc_pthread_condattr_getpshared]]]*/

/*[[[head:libc_pthread_condattr_setpshared,hash:CRC-32=0xa0b085d7]]]*/
/* >> pthread_condattr_setpshared(3)
 * Set the process-shared flag of the condition variable attribute `attr'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_setpshared)(pthread_condattr_t *attr,
                                                       int pshared)
/*[[[body:libc_pthread_condattr_setpshared]]]*/
{
	if unlikely(pshared != PTHREAD_PROCESS_PRIVATE &&
	            pshared != PTHREAD_PROCESS_SHARED)
		return EINVAL;
	attr->ca_value &= ~PTHREAD_CONDATTR_FLAG_PSHARED;
	if (pshared == PTHREAD_PROCESS_SHARED)
		attr->ca_value |= PTHREAD_CONDATTR_FLAG_PSHARED;
	return EOK;
}
/*[[[end:libc_pthread_condattr_setpshared]]]*/

/*[[[head:libc_pthread_condattr_getclock,hash:CRC-32=0x94ce424f]]]*/
/* >> pthread_condattr_getclock(3)
 * Get the clock selected for the condition variable attribute `attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_getclock)(pthread_condattr_t const *__restrict attr,
                                                     clockid_t *__restrict clock_id)
/*[[[body:libc_pthread_condattr_getclock]]]*/
{
	*clock_id = (clockid_t)(attr->ca_value >> PTHREAD_CONDATTR_CLOCKID_SHIFT);
	return EOK;
}
/*[[[end:libc_pthread_condattr_getclock]]]*/

/*[[[head:libc_pthread_condattr_setclock,hash:CRC-32=0x18bfa182]]]*/
/* >> pthread_condattr_setclock(3)
 * Set the clock selected for the condition variable attribute `attr'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `clock_id' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_setclock)(pthread_condattr_t *attr,
                                                     clockid_t clock_id)
/*[[[body:libc_pthread_condattr_setclock]]]*/
{
	if unlikely(clock_id != CLOCK_MONOTONIC &&
	            clock_id != CLOCK_REALTIME)
		return EINVAL;
	attr->ca_value &= ~PTHREAD_CONDATTR_CLOCKID_MASK;
	attr->ca_value |= clock_id << PTHREAD_CONDATTR_CLOCKID_SHIFT;
	return EOK;
}
/*[[[end:libc_pthread_condattr_setclock]]]*/















/************************************************************************/
/* pthread_barrierattr_t                                                */
/************************************************************************/

/*[[[head:libc_pthread_barrierattr_init,hash:CRC-32=0x62951c15]]]*/
/* >> pthread_barrierattr_init(3)
 * Initialize barrier attribute `attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_init)(pthread_barrierattr_t *attr)
/*[[[body:libc_pthread_barrierattr_init]]]*/
{
	attr->ba_pshared = PTHREAD_PROCESS_PRIVATE;
	return EOK;
}
/*[[[end:libc_pthread_barrierattr_init]]]*/

/*[[[head:libc_pthread_barrierattr_destroy,hash:CRC-32=0x7298e226]]]*/
/* >> pthread_barrierattr_destroy(3)
 * Destroy previously dynamically initialized barrier attribute `attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_destroy)(pthread_barrierattr_t *attr)
/*[[[body:libc_pthread_barrierattr_destroy]]]*/
{
	(void)attr;
	DBG_memset(attr, 0xcc, sizeof(*attr));
	return EOK;
}
/*[[[end:libc_pthread_barrierattr_destroy]]]*/

/*[[[head:libc_pthread_barrierattr_getpshared,hash:CRC-32=0xc7e93956]]]*/
/* >> pthread_barrierattr_getpshared(3)
 * Get the process-shared flag of the barrier attribute `attr'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_getpshared)(pthread_barrierattr_t const *__restrict attr,
                                                          int *__restrict pshared)
/*[[[body:libc_pthread_barrierattr_getpshared]]]*/
{
	*pshared = attr->ba_pshared;
	return EOK;
}
/*[[[end:libc_pthread_barrierattr_getpshared]]]*/

/*[[[head:libc_pthread_barrierattr_setpshared,hash:CRC-32=0x6c39c32c]]]*/
/* >> pthread_barrierattr_setpshared(3)
 * Set the process-shared flag of the barrier attribute `attr'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_setpshared)(pthread_barrierattr_t *attr,
                                                          int pshared)
/*[[[body:libc_pthread_barrierattr_setpshared]]]*/
{
	if unlikely(pshared != PTHREAD_PROCESS_PRIVATE &&
	            pshared != PTHREAD_PROCESS_SHARED)
		return EINVAL;
	attr->ba_pshared = pshared;
	return EOK;
}
/*[[[end:libc_pthread_barrierattr_setpshared]]]*/















/************************************************************************/
/* pthread_mutex_t                                                      */
/************************************************************************/

/*[[[head:libc_pthread_mutex_init,hash:CRC-32=0xeb232a90]]]*/
/* >> pthread_mutex_init(3)
 * Initialize the given `mutex'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_init)(pthread_mutex_t *mutex,
                                              pthread_mutexattr_t const *mutexattr)
/*[[[body:libc_pthread_mutex_init]]]*/
{
	bzero(mutex, sizeof(*mutex));
#if __PTHREAD_MUTEX_TIMED != 0
	mutex->m_kind = __PTHREAD_MUTEX_TIMED;
#endif /* __PTHREAD_MUTEX_TIMED != 0 */
	if (mutexattr) {
		mutex->m_kind = mutexattr->ma_kind & PTHREAD_MUTEXATTR_KIND_MASK;
		/* XXX: mutexattr->ma_kind & PTHREAD_MUTEXATTR_PRIO_CEILING_MASK */
		/* XXX: mutexattr->ma_kind & PTHREAD_MUTEXATTR_PROTOCOL_MASK */
		/* XXX: mutexattr->ma_kind & PTHREAD_MUTEXATTR_FLAG_ROBUST */
		/* XXX: mutexattr->ma_kind & PTHREAD_MUTEXATTR_FLAG_PSHARED */
	}
	return EOK;
}
/*[[[end:libc_pthread_mutex_init]]]*/

/*[[[head:libc_pthread_mutex_destroy,hash:CRC-32=0x8fcb348a]]]*/
/* >> pthread_mutex_destroy(3)
 * Destroy  the  given `mutex'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_destroy)(pthread_mutex_t *mutex)
/*[[[body:libc_pthread_mutex_destroy]]]*/
{
	(void)mutex;
	DBG_memset(mutex, 0xcc, sizeof(*mutex));
	return EOK;
}
/*[[[end:libc_pthread_mutex_destroy]]]*/

LOCAL ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL mutex_trylock)(pthread_mutex_t *__restrict mutex,
                                    uint32_t *__restrict plock) {
	uint32_t lock;
	pid_t mytid = gettid();
	assert((mytid & ~FUTEX_TID_MASK) == 0);
	/* Try to acquire the lock. */
again:
	lock = ATOMIC_READ(mutex->m_lock);
	if ((lock & FUTEX_TID_MASK) == 0) {
		/* Lock not taken. - Try to take it now! */
		if (!ATOMIC_CMPXCH_WEAK(mutex->m_lock,
		                        lock,
		                        (lock & FUTEX_WAITERS) | mytid))
			goto again;
		/* Got it! */
		return EOK;
	}
	/* Lock is already taken, but it may be taken by us. */
	if ((lock & FUTEX_TID_MASK) == (uint32_t)mytid) {
		/* Check if recursive locks are allowed */
		if unlikely(mutex->m_kind != PTHREAD_MUTEX_RECURSIVE_NP)
			return EDEADLK;
		++mutex->m_count;
		return EOK;
	}
	/* Nope! */
	*plock = lock;
	return EBUSY;
}

LOCAL ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL mutex_trylock_waiters)(pthread_mutex_t *__restrict mutex,
                                            uint32_t *__restrict plock) {
	errno_t result;
again:
	result = mutex_trylock(mutex, plock);
	if (result == EBUSY) {
		/* Set the `FUTEX_WAITERS' bit if it wasn't set already. */
		if (!(*plock & FUTEX_WAITERS)) {
			if (!ATOMIC_CMPXCH_WEAK(mutex->m_lock,
			                        *plock,
			                        *plock | FUTEX_WAITERS))
				goto again;
			*plock |= FUTEX_WAITERS;
		}
	}
	return result;
}

/*[[[head:libc_pthread_mutex_trylock,hash:CRC-32=0x6191bd7a]]]*/
/* >> pthread_mutex_trylock(3)
 * Try locking the given `mutex'
 * @return: EOK:   Success
 * @return: EBUSY: The  mutex  has  already  been   locked
 *                 In case of  a recursive mutex,  another
 *                 thread was the one to acquire the lock. */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_trylock)(pthread_mutex_t *mutex)
/*[[[body:libc_pthread_mutex_trylock]]]*/
{
	uint32_t lock;
	return mutex_trylock(mutex, &lock);
}
/*[[[end:libc_pthread_mutex_trylock]]]*/

/*[[[head:libc_pthread_mutex_lock,hash:CRC-32=0xe77e4f9c]]]*/
/* >> pthread_mutex_lock(3)
 * Lock  the  given `mutex'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_mutex_lock)(pthread_mutex_t *mutex)
/*[[[body:libc_pthread_mutex_lock]]]*/
{
	uint32_t lock;
	errno_t result;
again:
	result = mutex_trylock_waiters(mutex, &lock);
	if (result != EBUSY)
		return result;
	/* Wait until the mutex is unlocked. */
	sys_futex((uint32_t *)&mutex->m_lock,
	          FUTEX_WAIT, lock, NULL, NULL, 0);
	goto again;
}
/*[[[end:libc_pthread_mutex_lock]]]*/

/*[[[head:libc_pthread_mutex_timedlock,hash:CRC-32=0xc63ae0eb]]]*/
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_mutex_timedlock)(pthread_mutex_t *__restrict mutex,
                                                   struct timespec const *__restrict abstime)
/*[[[body:libc_pthread_mutex_timedlock]]]*/
{
	uint32_t lock;
	errno_t result;
again:
	result = mutex_trylock_waiters(mutex, &lock);
	if (result != EBUSY)
		return result;
	/* Wait until the mutex is unlocked.
	 * NOTE: Need to use `FUTEX_WAIT_BITSET', since only that one  takes
	 *       an absolute timeout, rather than the relative timeout taken
	 *       by the regular `FUTEX_WAIT' */
	result = (errno_t)sys_futex((uint32_t *)&mutex->m_lock,
	                            FUTEX_WAIT_BITSET, lock, abstime,
	                            NULL, FUTEX_BITSET_MATCH_ANY);
	/* Check for timeout. */
	if (result == -ETIMEDOUT || result == -EINVAL)
		return -result;
	goto again;
}
/*[[[end:libc_pthread_mutex_timedlock]]]*/

/* With a 64-bit timeout, wait  while a 32-bit control word  matches
 * the given value. Note that this function may access up to 8 bytes
 * starting at the base of the  futex control word, though only  the
 * first 4 bytes are actually inspected.
 * HINT: Waiting for 32-bit control words on 64-bit platforms is
 *       done  by  making  use  of   `LFUTEX_WAIT_WHILE_BITMASK' */
#if __SIZEOF_POINTER__ == 4
#define sys_lfutex32_waitwhile64(uaddr, val, timeout, flags) \
	sys_lfutex(uaddr, LFUTEX_WAIT_WHILE | flags, val, timeout, 0)
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define sys_lfutex32_waitwhile64(uaddr, val, timeout, flags) \
	sys_lfutex((uint64_t *)(uaddr),                          \
	           LFUTEX_WAIT_WHILE_BITMASK | flags,            \
	           (uint64_t)UINT32_MAX, timeout,                \
	           (uint64_t)(uint32_t)(val))
#else /* ... */
#define sys_lfutex32_waitwhile64(uaddr, val, timeout, flags) \
	sys_lfutex((uint64_t *)(uaddr),                          \
	           LFUTEX_WAIT_WHILE_BITMASK | flags,            \
	           (uint64_t)UINT32_MAX << 32, timeout,          \
	           (uint64_t)(uint32_t)(val) << 32)
#endif /* !... */


/*[[[head:libc_pthread_mutex_timedlock64,hash:CRC-32=0x55254652]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_mutex_timedlock64, libc_pthread_mutex_timedlock);
#else /* MAGIC:alias */
/* >> pthread_mutex_timedlock(3), pthread_mutex_timedlock64(3)
 * Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_mutex_timedlock64)(pthread_mutex_t *__restrict mutex,
                                                     struct timespec64 const *__restrict abstime)
/*[[[body:libc_pthread_mutex_timedlock64]]]*/
{
	uint32_t lock;
	errno_t result;
again:
	result = mutex_trylock_waiters(mutex, &lock);
	if (result != EBUSY)
		return result;
	/* Wait until the mutex is unlocked. */
	result = (errno_t)sys_lfutex32_waitwhile64((uint32_t *)&mutex->m_lock,
	                                           lock, abstime, 0);
	/* Check for timeout. */
	if (result == -ETIMEDOUT || result == -EINVAL)
		return -result;
	goto again;
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_mutex_timedlock64]]]*/

/*[[[head:libc_pthread_mutex_reltimedlock_np,hash:CRC-32=0xd69ad863]]]*/
/* >> pthread_mutex_reltimedlock_np(3), pthread_mutex_reltimedlock64_np(3)
 * Wait until lock becomes available, or specified amount of time has passed
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_mutex_reltimedlock_np)(pthread_mutex_t *__restrict mutex,
                                                         struct timespec const *__restrict reltime)
/*[[[body:libc_pthread_mutex_reltimedlock_np]]]*/
{
	uint32_t lock;
	errno_t result;
again:
	result = mutex_trylock_waiters(mutex, &lock);
	if (result != EBUSY)
		return result;
	/* Wait until the mutex is unlocked.
	 * NOTE: Need to use `FUTEX_WAIT_BITSET', since only that one  takes
	 *       an absolute timeout, rather than the relative timeout taken
	 *       by the regular `FUTEX_WAIT' */
	result = (errno_t)sys_futex((uint32_t *)&mutex->m_lock,
	                            FUTEX_WAIT, lock, reltime,
	                            NULL, 0);
	/* Check for timeout. */
	if (result == -ETIMEDOUT || result == -EINVAL)
		return -result;
	goto again;
}
/*[[[end:libc_pthread_mutex_reltimedlock_np]]]*/

/*[[[head:libc_pthread_mutex_reltimedlock64_np,hash:CRC-32=0xe1cf6836]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_mutex_reltimedlock64_np, libc_pthread_mutex_reltimedlock_np);
#else /* MAGIC:alias */
/* >> pthread_mutex_reltimedlock_np(3), pthread_mutex_reltimedlock64_np(3)
 * Wait until lock becomes available, or specified amount of time has passed
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_mutex_reltimedlock64_np)(pthread_mutex_t *__restrict mutex,
                                                           struct timespec64 const *__restrict reltime)
/*[[[body:libc_pthread_mutex_reltimedlock64_np]]]*/
{
	uint32_t lock;
	errno_t result;
again:
	result = mutex_trylock_waiters(mutex, &lock);
	if (result != EBUSY)
		return result;
	/* Wait until the mutex is unlocked. */
	result = (errno_t)sys_lfutex32_waitwhile64((uint32_t *)&mutex->m_lock,
	                                           lock, reltime,
	                                           LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE);
	/* Check for timeout. */
	if (result == -ETIMEDOUT || result == -EINVAL)
		return -result;
	goto again;
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_mutex_reltimedlock64_np]]]*/

/*[[[head:libc_pthread_mutex_unlock,hash:CRC-32=0x86cf32c3]]]*/
/* >> pthread_mutex_unlock(3)
 * Unlock  the  given `mutex'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_unlock)(pthread_mutex_t *mutex)
/*[[[body:libc_pthread_mutex_unlock]]]*/
{
	uint32_t lock;
	switch (mutex->m_kind) {

	case PTHREAD_MUTEX_ERRORCHECK: {
		/* Verify that the caller owns this mutex. */
		lock = ATOMIC_READ(mutex->m_lock);
		if ((lock & FUTEX_TID_MASK) != (uint32_t)gettid())
			return EPERM;
	}	break;

	case PTHREAD_MUTEX_RECURSIVE: {
		/* Check if this is a recursive unlock. */
		if (mutex->m_count != 0) {
			--mutex->m_count;
			return EOK;
		}
	}	break;

	default:
		break;
	}
	/* Actually unlock the mutex. */
	lock = ATOMIC_XCH(mutex->m_lock, 0);
	/* If there were any waiting threads, wake one of them now. */
	if (lock & FUTEX_WAITERS)
		sys_futex((uint32_t *)&mutex->m_lock, FUTEX_WAKE, 1, NULL, NULL, 0);
	return EOK;
}
/*[[[end:libc_pthread_mutex_unlock]]]*/

/*[[[head:libc_pthread_mutex_getprioceiling,hash:CRC-32=0xe395ff3a]]]*/
/* >> pthread_mutex_getprioceiling(3)
 * Get the priority ceiling of `mutex'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN(1) ATTR_OUT(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_getprioceiling)(pthread_mutex_t const *__restrict mutex,
                                                        int *__restrict prioceiling)
/*[[[body:libc_pthread_mutex_getprioceiling]]]*/
/*AUTO*/{
	(void)mutex;
	(void)prioceiling;
	CRT_UNIMPLEMENTEDF("pthread_mutex_getprioceiling(mutex: %p, prioceiling: %p)", mutex, prioceiling); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutex_getprioceiling]]]*/

/*[[[head:libc_pthread_mutex_setprioceiling,hash:CRC-32=0x43be97b9]]]*/
/* >> pthread_mutex_setprioceiling(3)
 * Set the priority ceiling of `mutex' to `prioceiling',
 * return old priority  ceiling value in  `*old_ceiling'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) ATTR_OUT_OPT(3) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_setprioceiling)(pthread_mutex_t *__restrict mutex,
                                                        int prioceiling,
                                                        int *__restrict old_ceiling)
/*[[[body:libc_pthread_mutex_setprioceiling]]]*/
/*AUTO*/{
	(void)mutex;
	(void)prioceiling;
	(void)old_ceiling;
	CRT_UNIMPLEMENTEDF("pthread_mutex_setprioceiling(mutex: %p, prioceiling: %x, old_ceiling: %p)", mutex, prioceiling, old_ceiling); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutex_setprioceiling]]]*/

/*[[[head:libc_pthread_mutex_consistent,hash:CRC-32=0x37278c21]]]*/
/* >> pthread_mutex_consistent(3)
 * Declare the state protected by `mutex' as consistent
 * @return: EOK:    Success
 * @return: EINVAL: Not a robust mutex
 * @return: EINVAL: Mutex was already in a consistent state */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_consistent)(pthread_mutex_t *mutex)
/*[[[body:libc_pthread_mutex_consistent]]]*/
/*AUTO*/{
	(void)mutex;
	CRT_UNIMPLEMENTEDF("pthread_mutex_consistent(mutex: %p)", mutex); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutex_consistent]]]*/















/************************************************************************/
/* pthread_rwlock_t                                                     */
/************************************************************************/

/*
 * We implement posix r/w-locks as follows:
 *
 * - PTHREAD_RWLOCK_PREFER_READER_NP,  PTHREAD_RWLOCK_PREFER_WRITER_NP:
 *   These act identical (as they also do in Glibc), and allow the lock
 *   to be used for recursive read-locks. (write-lock are never allowed
 *   to be recursive)
 * - PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP:
 *   This simply makes  it illegal to  acquire recursive  read-locks.
 *   This  option also requires  us to keep track  of which thread is
 *   already holding a  specific read-lock (so  we can deny  requests
 *   to  acquire recursive ones). This is done via a lazily allocated
 *   TLS variable that points to a control structure used for keeping
 *   track  of  which rwlocks  are  acquired by  the  calling thread.
 *   Additionally, this option makes  it possible to use  write-locks
 *   recursively.
 *
 * With recursion out of the way, the actual implementation works the same  as
 * the KOS-specific  `struct shared_rwlock' from  <kos/sched/shared-rwlock.h>,
 * with the addition that we also keep track of the TID of the writing thread.
 *
 *   [pthread_rwlock_t]  [struct shared_rwlock]  [desc]
 *   rw_lock             sl_lock                 # of read-locks, or (uint32_t)-1 if a write-lock is active
 *   rw_readers_wakeup   sl_rdwait               Futex for read-lock waiters (non-zero if threads may be waiting)
 *   rw_writer_wakeup    sl_wrwait               Futex for write-lock waiters (non-zero if threads may be waiting)
 *   rw_flags            N/A                     Non-zero if `PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP'
 *   rw_writer           N/A                     TID of thread holding write-lock (else: `0')
 *   rw_nr_writers       N/A                     Write-lock recursion under `PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP'
 *
 */


struct readlock_bucket {
	pthread_rwlock_t *rb_lock; /* [0..1] Referenced lock, or one of `READLOCK_BUCKET_*' */
#define READLOCK_BUCKET_SENTINEL ((pthread_rwlock_t *)0)  /* End-of-chain */
#define READLOCK_BUCKET_DELETED  ((pthread_rwlock_t *)-1) /* Deleted entry (skip) */
};
#define pthread_rwlock_hashof(self) \
	((uintptr_t)(self))
#define pthread_rwlock_hashnx(i, perturb) \
	((i) = (((i) << 2) + (i) + (perturb) + 1), (perturb) >>= 5)


struct readlock_tls_data {
	size_t                  rtd_rdlock_used; /* # of non-READLOCK_BUCKET_SENTINEL/READLOCK_BUCKET_DELETED entries */
	size_t                  rtd_rdlock_size; /* # of non-READLOCK_BUCKET_SENTINEL entries */
	size_t                  rtd_rdlock_mask; /* Hash-mask */
	struct readlock_bucket *rtd_rdlock_list; /* [0..rtd_rdlock_mask+1][owned] Hash-map */
};

/* Rehash with the given list buffer */
PRIVATE ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) void CC
readlock_tls_data_rehash_with(struct readlock_tls_data *__restrict self,
                              struct readlock_bucket *__restrict new_list,
                              size_t new_mask) {
	/* Rehash existing entries. */
	uintptr_t i, j, perturb;
	assert(new_mask >= self->rtd_rdlock_used);
	for (i = 0; i <= self->rtd_rdlock_mask; ++i) {
		struct readlock_bucket *dst;
		pthread_rwlock_t *lck;
		uintptr_t hash;
		lck = self->rtd_rdlock_list[i].rb_lock;
		if (lck == READLOCK_BUCKET_SENTINEL ||
		    lck == READLOCK_BUCKET_DELETED)
			continue; /* Empty, or deleted. */
		hash = pthread_rwlock_hashof(lck);
		j = perturb = hash & new_mask;
		for (;; pthread_rwlock_hashnx(j, perturb)) {
			dst = &new_list[j & new_mask];
			if (dst->rb_lock == READLOCK_BUCKET_SENTINEL)
				break;
		}
		dst->rb_lock = lck; /* Rehash */
	}
	free(self->rtd_rdlock_list);
	self->rtd_rdlock_list = new_list;
	self->rtd_rdlock_mask = new_mask;
	self->rtd_rdlock_size = self->rtd_rdlock_used; /* All deleted entries were removed... */
}

PRIVATE ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1, 2)) errno_t
readlock_tls_data_doadd_impl(struct readlock_tls_data *__restrict self,
                             pthread_rwlock_t *__restrict lck) {
	uintptr_t hash, i, perturb;
	struct readlock_bucket *ent;
	assert((self->rtd_rdlock_size + 1) <= self->rtd_rdlock_mask);
	hash = pthread_rwlock_hashof(lck);
	i = perturb = hash & self->rtd_rdlock_mask;
	for (;; pthread_rwlock_hashnx(i, perturb)) {
		pthread_rwlock_t *elck;
		ent  = &self->rtd_rdlock_list[i & self->rtd_rdlock_mask];
		elck = ent->rb_lock;
		if (elck == READLOCK_BUCKET_SENTINEL) {
			/* Found a free slot */
			++self->rtd_rdlock_size;
			break;
		}
		if (elck == READLOCK_BUCKET_DELETED) {
			/* Re-use a previously deleted slot. */
			break;
		}
		/* Check if this is an identical lock. */
		if (elck == lck) {
			/* Identical lock already exists (cannot add) */
			return EDEADLK;
		}
	}
	ent->rb_lock = lck; /* Inherit */
	++self->rtd_rdlock_used;
	return EOK;
}

/*[[[config CONFIG_LIBC_READLOCK_TLS_DATA_INITIAL_MASK! = 7]]]*/
#ifndef CONFIG_LIBC_READLOCK_TLS_DATA_INITIAL_MASK
#define CONFIG_LIBC_READLOCK_TLS_DATA_INITIAL_MASK 7
#endif /* !CONFIG_LIBC_READLOCK_TLS_DATA_INITIAL_MASK */
/*[[[end]]]*/

/* Add the given `lck' to `self' */
PRIVATE ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t CC
readlock_tls_data_doadd(struct readlock_tls_data *__restrict self,
                        pthread_rwlock_t *__restrict lck)
		THROWS(E_BADALLOC) {
	if (((self->rtd_rdlock_size + 1) * 3) / 2 >= self->rtd_rdlock_mask) {
		/* Must rehash! */
		struct readlock_bucket *new_list;
		size_t new_mask = CONFIG_LIBC_READLOCK_TLS_DATA_INITIAL_MASK;
		size_t thresh   = ((self->rtd_rdlock_used + 1) * 3) / 2;
		while (thresh >= new_mask)
			new_mask = (new_mask << 1) | 1;
		new_list = (struct readlock_bucket *)calloc(new_mask + 1, sizeof(struct readlock_bucket));
		if unlikely(!new_list) {
			if ((self->rtd_rdlock_size + 1) <= self->rtd_rdlock_mask)
				goto doadd;
			new_mask = CONFIG_LIBC_READLOCK_TLS_DATA_INITIAL_MASK;
			while ((self->rtd_rdlock_used + 1) > self->rtd_rdlock_mask)
				new_mask = (new_mask << 1) | 1;
			new_list = (struct readlock_bucket *)calloc(new_mask + 1, sizeof(struct readlock_bucket));
			if unlikely(!new_list)
				return ENOMEM;
		}
		/* Rehash using the new list. */
		readlock_tls_data_rehash_with(self, new_list, new_mask);
		assert(self->rtd_rdlock_used == self->rtd_rdlock_size);
	}
doadd:
	return readlock_tls_data_doadd_impl(self, lck);
}


PRIVATE ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) void CC
readlock_tls_data_rehash_after_remove(struct readlock_tls_data *__restrict self) {
	if ((self->rtd_rdlock_used < (self->rtd_rdlock_mask / 3)) &&
	    self->rtd_rdlock_mask > CONFIG_LIBC_READLOCK_TLS_DATA_INITIAL_MASK) {
		/* Try to shrink the hash-vector's mask size. */
		size_t new_mask = CONFIG_LIBC_READLOCK_TLS_DATA_INITIAL_MASK;
		size_t thresh   = ((self->rtd_rdlock_used + 1) * 3) / 2;
		while (thresh >= new_mask)
			new_mask = (new_mask << 1) | 1;
		if (new_mask < self->rtd_rdlock_mask) {
			/* Try to shrink */
			struct readlock_bucket *new_list;
			new_list = (struct readlock_bucket *)calloc(new_mask + 1, sizeof(struct readlock_bucket));
			/* If the alloc worked, re-hash using `new_list' */
			if (new_list)
				readlock_tls_data_rehash_with(self, new_list, new_mask);
		}
	}
}

/* Remove `lck' from the set of locks of `self' */
PRIVATE ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t CC
readlock_tls_data_dodel(struct readlock_tls_data *__restrict self,
                        pthread_rwlock_t *__restrict lck) {
	uintptr_t hash, i, perturb;
	struct readlock_bucket *ent;
	hash = pthread_rwlock_hashof(lck);
	i = perturb = hash & self->rtd_rdlock_mask;
	for (;; pthread_rwlock_hashnx(i, perturb)) {
		pthread_rwlock_t *emon;
		ent  = &self->rtd_rdlock_list[i & self->rtd_rdlock_mask];
		emon = ent->rb_lock;
		if (emon == READLOCK_BUCKET_SENTINEL)
			return EPERM; /* No such read-lock. */
		if (emon == lck)
			break; /* Found it! */
	}
	assert(self->rtd_rdlock_used);
	ent->rb_lock = READLOCK_BUCKET_DELETED;
	--self->rtd_rdlock_used;
	return EOK;
}

/* Remove `lck' from the set of locks of `self' */
ATTR_SECTION(".text.crt.sched.pthread")
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 2)) bool
NOTHROW(CC readlock_tls_data_contains)(struct readlock_tls_data const *__restrict self,
                                       pthread_rwlock_t const *__restrict lck) {
	uintptr_t hash, i, perturb;
	pthread_rwlock_t *emon;
	hash = pthread_rwlock_hashof(lck);
	i = perturb = hash & self->rtd_rdlock_mask;
	for (;; pthread_rwlock_hashnx(i, perturb)) {
		emon = self->rtd_rdlock_list[i & self->rtd_rdlock_mask].rb_lock;
		if (emon == READLOCK_BUCKET_SENTINEL)
			return false; /* No such read-lock. */
		if (emon == lck)
			return true; /* Found it! */
	}
}



PRIVATE ATTR_SECTION(".text.crt.sched.pthread") void
NOTHROW_NCX(LIBCCALL readlock_tls_destroy)(void *data) {
	struct readlock_tls_data *me;
	if (!data)
		return;
	me = (struct readlock_tls_data *)data;
	free(me->rtd_rdlock_list);
	free(me);
}

PRIVATE ATTR_SECTION(".data.crt.sched.pthread")
pthread_key_t readlock_tls_key = PTHREAD_ONCE_KEY_NP;
PRIVATE ATTR_SECTION(".text.crt.sched.pthread") pthread_key_t
NOTHROW_NCX(LIBCCALL readlock_tls_getkey)(void) {
	if (pthread_key_create_once_np(&readlock_tls_key, &readlock_tls_destroy) != EOK)
		return (pthread_key_t)-1;
	return readlock_tls_key;
}

PRIVATE ATTR_SECTION(".text.crt.sched.pthread") struct readlock_tls_data *
NOTHROW_NCX(LIBCCALL readlock_tls_getdata)(void) {
	pthread_key_t key;
	struct readlock_tls_data *data;
	key  = readlock_tls_getkey();
	data = (struct readlock_tls_data *)pthread_getspecific(key);
	if (!data) {
		if unlikely(key == (pthread_key_t)-1)
			return NULL;
		data = (struct readlock_tls_data *)calloc(sizeof(struct readlock_tls_data));
		if unlikely(!data)
			return NULL;
		if unlikely(pthread_setspecific(key, data) != EOK) {
			free(data);
			return NULL;
		}
	}
	return data;
}



/* @return: EOK:     Success
 * @return: ENOMEM:  Out of memory
 * @return: EDEADLK: Already reading */
PRIVATE ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL pthread_rwlock_addreading)(pthread_rwlock_t *__restrict rwlock) {
	struct readlock_tls_data *data;
	data = readlock_tls_getdata();
	if unlikely(!data)
		return ENOMEM;
	return readlock_tls_data_doadd(data, rwlock);
}

/* @return: EOK:    Success
 * @return: EPERM:  Not reading */
PRIVATE ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL pthread_rwlock_delreading)(pthread_rwlock_t *__restrict rwlock) {
	errno_t result;
	struct readlock_tls_data *data;
	data = readlock_tls_getdata();
	if unlikely(!data)
		return EPERM; /* No data -> can't possibly be reading */
	result = readlock_tls_data_dodel(data, rwlock);
	if (result == EOK)
		readlock_tls_data_rehash_after_remove(data);
	return result;
}

PRIVATE ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) bool
NOTHROW_NCX(LIBCCALL pthread_rwlock_isreading)(pthread_rwlock_t *__restrict rwlock) {
	struct readlock_tls_data *data;
	if (readlock_tls_key == (pthread_key_t)-1)
		return false;
	data = readlock_tls_getdata();
	if unlikely(!data)
		return false;
	return readlock_tls_data_contains(data, rwlock);
}




PRIVATE ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_RPC(LIBCCALL pthread_rwlock_acquireread)(pthread_rwlock_t *__restrict self,
                                                 struct timespec64 const *timeout,
                                                 syscall_ulong_t timeout_flags) {
	uint32_t word;
again:
	if (self->rw_flags) {
		/* Special handling to prevent recursive read-locks. */
		errno_t error;
		error = pthread_rwlock_addreading(self);
		if (error == EOK) {
			do {
				word = ATOMIC_READ(self->rw_lock);
				if (word >= (uint32_t)-2) {
					if (word == (uint32_t)-2) {
						error = EAGAIN; /* Too many read-locks */
					} else if (self->rw_writer == gettid()) {
						error = EDEADLK; /* You're already holding a write-lock */
					} else {
						/* Someone else is holding a write-lock */
						pthread_rwlock_delreading(self);
						goto handle_EBUSY;
					}
					pthread_rwlock_delreading(self);
					break;
				}
			} while (!ATOMIC_CMPXCH_WEAK(self->rw_lock, word, word + 1));
		}
		return error;
	}
	do {
		word = ATOMIC_READ(self->rw_lock);
		if (word >= (uint32_t)-2) {
			if (word == (uint32_t)-2)
				return EAGAIN; /* Too many read-locks */
			if (self->rw_writer == gettid())
				return EDEADLK; /* You're already holding a write-lock */
			goto handle_EBUSY;  /* Someone else is holding a write-lock */
		}
	} while (!ATOMIC_CMPXCH_WEAK(self->rw_lock, word, word + 1));
	return EOK;
handle_EBUSY:
	/* Indicate that we are waiting for a read-lock */
	ATOMIC_WRITE(self->rw_readers_wakeup, 1);

	/* Using lfutex expressions to wait on `rw_readers_wakeup', while `rw_lock == (uint32_t)-1' */
	{
		int status;
		static struct lfutexexpr const waitreadexpr[] = {
			LFUTEXEXPR_INIT(__builtin_offsetof(pthread_rwlock_t, rw_lock), LFUTEX_WAIT_WHILE, UINT32_MAX, 0),
			LFUTEXEXPR_INIT(0, LFUTEX_EXPREND, 0, 0)
		};
		status = LFutexExpr64((uintptr_t *)&self->rw_readers_wakeup, self,
		                      waitreadexpr, timeout, timeout_flags);
		if (status < 0) {
			assert(timeout);
			return ETIMEDOUT;
		}
	}

	/* XXX: If we end up waiting again, and `LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE' was
	 *      given, then we must subtract the  amount of time we've already  waited! */
	goto again;
}

PRIVATE ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_RPC(LIBCCALL pthread_rwlock_acquirewrite)(pthread_rwlock_t *__restrict self,
                                                  struct timespec64 const *timeout,
                                                  syscall_ulong_t timeout_flags) {
again:
	if (ATOMIC_CMPXCH(self->rw_lock, 0, (uint32_t)-1)) {
		/* Success */
		self->rw_writer = gettid();
		return EOK;
	}

	/* Check for recursive write-locks */
	if (self->rw_flags && self->rw_writer == gettid()) {
		if unlikely(self->rw_nr_writers == (uint32_t)-1)
			return EAGAIN;     /* Not documented, but mirror what `pthread_rwlock_tryrdlock()' does */
		++self->rw_nr_writers; /* Recursive write-lock! */
		return EOK;
	}

	/* Someone is holding a read-lock. If it's us, that's a EDEADLK */
	if unlikely(self->rw_flags && pthread_rwlock_isreading(self))
		return EDEADLK;

	/* Indicate that we are waiting for a write-lock */
	ATOMIC_WRITE(self->rw_writer_wakeup, 1);

	/* Using lfutex expressions to wait on `rw_writer_wakeup', until `rw_lock == 0' */
	{
		int status;
		static struct lfutexexpr const waitwriteexpr[] = {
			LFUTEXEXPR_INIT(__builtin_offsetof(pthread_rwlock_t, rw_lock), LFUTEX_WAIT_UNTIL, 0, 0),
			LFUTEXEXPR_INIT(0, LFUTEX_EXPREND, 0, 0)
		};
		status = LFutexExpr64((uintptr_t *)&self->rw_writer_wakeup, self,
		                      waitwriteexpr, timeout, timeout_flags);
		if (status < 0) {
			assert(timeout);
			return ETIMEDOUT;
		}
	}

	/* XXX: If we end up waiting again, and `LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE' was
	 *      given, then we must subtract the  amount of time we've already  waited! */
	goto again;
}


/*[[[head:libc_pthread_rwlock_init,hash:CRC-32=0x3d7fb834]]]*/
/* >> pthread_rwlock_init(3)
 * Initialize read-write lock `rwlock' using attributes `attr',
 * or use the default values if later is `NULL'.
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN_OPT(2) ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_init)(pthread_rwlock_t *__restrict rwlock,
                                               pthread_rwlockattr_t const *__restrict attr)
/*[[[body:libc_pthread_rwlock_init]]]*/
{
	rwlock->rw_lock           = 0;
	rwlock->rw_nr_writers     = 0;
	rwlock->rw_readers_wakeup = 0;
	rwlock->rw_writer_wakeup  = 0;
	rwlock->rw_flags          = 0;
	rwlock->rw_writer         = 0;
	if (attr != NULL)
		rwlock->rw_flags = attr->rwa_kind == PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP;
	return EOK;
}
/*[[[end:libc_pthread_rwlock_init]]]*/

/*[[[head:libc_pthread_rwlock_destroy,hash:CRC-32=0x3a61c15b]]]*/
/* >> pthread_rwlock_destroy(3)
 * Destroy read-write lock `rwlock'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_destroy)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_destroy]]]*/
{
	(void)rwlock;
	DBG_memset(rwlock, 0xcc, sizeof(*rwlock));
	return EOK;
}
/*[[[end:libc_pthread_rwlock_destroy]]]*/

/*[[[head:libc_pthread_rwlock_rdlock,hash:CRC-32=0x32086cda]]]*/
/* >> pthread_rwlock_rdlock(3)
 * Acquire read lock for `rwlock'
 * @return: EOK:     Success
 * @return: EAGAIN:  The maximum # of read-locks has been acquired
 * @return: EDEADLK: You're already holding a write-lock
 * @return: EDEADLK: [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                   You're already holding a read-lock */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_rdlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_rdlock]]]*/
{
	return pthread_rwlock_acquireread(rwlock, NULL, 0);
}
/*[[[end:libc_pthread_rwlock_rdlock]]]*/

/*[[[head:libc_pthread_rwlock_tryrdlock,hash:CRC-32=0xe61d6fb0]]]*/
/* >> pthread_rwlock_tryrdlock(3)
 * Try to acquire read lock for `rwlock'
 * @return: EOK:    Success
 * @return: EBUSY:  A read-lock cannot be acquired at the moment,
 *                  because a write-lock  is already being  held.
 * @return: EAGAIN: The maximum # of read-locks has been acquired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_tryrdlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_tryrdlock]]]*/
{
	uint32_t word;
	do {
		word = ATOMIC_READ(rwlock->rw_lock);
		if (word >= (uint32_t)-2) {
			if (word == (uint32_t)-1)
				return EBUSY;
			return EAGAIN;
		}
	} while (!ATOMIC_CMPXCH_WEAK(rwlock->rw_lock, word, word + 1));
	return EOK;
}
/*[[[end:libc_pthread_rwlock_tryrdlock]]]*/

/*[[[head:libc_pthread_rwlock_timedrdlock,hash:CRC-32=0x3a78a9a2]]]*/
/* >> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
 * Try to acquire read lock for `rwlock' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedrdlock)(pthread_rwlock_t *__restrict rwlock,
                                                      struct timespec const *__restrict abstime)
/*[[[body:libc_pthread_rwlock_timedrdlock]]]*/
{
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	return pthread_rwlock_acquireread(rwlock, abstime, 0);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	struct timespec64 ts64;
	ts64.tv_sec  = (time_t)abstime->tv_sec;
	ts64.tv_nsec = (syscall_ulong_t)abstime->tv_nsec;
	return pthread_rwlock_acquireread(rwlock, &ts64, 0);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
}
/*[[[end:libc_pthread_rwlock_timedrdlock]]]*/

/*[[[head:libc_pthread_rwlock_timedrdlock64,hash:CRC-32=0x5c10d3f]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_rwlock_timedrdlock64, libc_pthread_rwlock_timedrdlock);
#else /* MAGIC:alias */
/* >> pthread_rwlock_timedrdlock(3), pthread_rwlock_timedrdlock64(3)
 * Try to acquire read lock for `rwlock' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedrdlock64)(pthread_rwlock_t *__restrict rwlock,
                                                        struct timespec64 const *__restrict abstime)
/*[[[body:libc_pthread_rwlock_timedrdlock64]]]*/
{
	return pthread_rwlock_acquireread(rwlock, abstime, 0);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_rwlock_timedrdlock64]]]*/

/*[[[head:libc_pthread_rwlock_wrlock,hash:CRC-32=0xd28c9340]]]*/
/* >> pthread_rwlock_wrlock(3)
 * Acquire write lock for `rwlock'
 * @return: EOK:     Success
 * @return: EDEADLK: You're already holding a read-lock
 * @return: EDEADLK: [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                   You're already holding a write-lock */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_wrlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_wrlock]]]*/
{
	return pthread_rwlock_acquirewrite(rwlock, NULL, 0);
}
/*[[[end:libc_pthread_rwlock_wrlock]]]*/

/*[[[head:libc_pthread_rwlock_trywrlock,hash:CRC-32=0x3526bca2]]]*/
/* >> pthread_rwlock_trywrlock(3)
 * Try to acquire write lock for `rwlock'
 * @return: EOK:   Success
 * @return: EBUSY: A write-lock cannot be acquired at the moment,
 *                 because read-locks  are  already  being  held. */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_trywrlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_trywrlock]]]*/
{
	if (!ATOMIC_CMPXCH(rwlock->rw_lock, 0, (uint32_t)-1)) {
		/* Check for recursive write-locks */
		if (rwlock->rw_flags && rwlock->rw_writer == gettid()) {
			if unlikely(rwlock->rw_nr_writers == (uint32_t)-1)
				return EAGAIN;       /* Not documented, but mirror what `pthread_rwlock_tryrdlock()' does */
			++rwlock->rw_nr_writers; /* Recursive write-lock! */
			return EOK;
		}
		return EBUSY; /* Locks are already being held */
	}

	/* Success */
	rwlock->rw_writer = gettid();
	return EOK;
}
/*[[[end:libc_pthread_rwlock_trywrlock]]]*/

/*[[[head:libc_pthread_rwlock_timedwrlock,hash:CRC-32=0x73ccb55a]]]*/
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `rwlock' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedwrlock)(pthread_rwlock_t *__restrict rwlock,
                                                      struct timespec const *__restrict abstime)
/*[[[body:libc_pthread_rwlock_timedwrlock]]]*/
{
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	return pthread_rwlock_acquirewrite(rwlock, abstime, 0);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	struct timespec64 ts64;
	ts64.tv_sec  = (time_t)abstime->tv_sec;
	ts64.tv_nsec = (syscall_ulong_t)abstime->tv_nsec;
	return pthread_rwlock_acquirewrite(rwlock, &ts64, 0);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
}
/*[[[end:libc_pthread_rwlock_timedwrlock]]]*/

/*[[[head:libc_pthread_rwlock_timedwrlock64,hash:CRC-32=0xe12b9c54]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_rwlock_timedwrlock64, libc_pthread_rwlock_timedwrlock);
#else /* MAGIC:alias */
/* >> pthread_rwlock_timedwrlock(3), pthread_rwlock_timedwrlock64(3)
 * Try to acquire write lock for `rwlock' or return after the specified time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedwrlock64)(pthread_rwlock_t *__restrict rwlock,
                                                        struct timespec64 const *__restrict abstime)
/*[[[body:libc_pthread_rwlock_timedwrlock64]]]*/
{
	return pthread_rwlock_acquirewrite(rwlock, abstime, 0);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_rwlock_timedwrlock64]]]*/

/*[[[head:libc_pthread_rwlock_reltimedrdlock_np,hash:CRC-32=0xc013a672]]]*/
/* >> pthread_rwlock_reltimedrdlock_np(3), pthread_rwlock_reltimedrdlock64_np(3)
 * Try to acquire  read lock  for `rwlock' or  return after  the specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_reltimedrdlock_np)(pthread_rwlock_t *__restrict rwlock,
                                                            struct timespec const *__restrict reltime)
/*[[[body:libc_pthread_rwlock_reltimedrdlock_np]]]*/
{
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	return pthread_rwlock_acquireread(rwlock, reltime, LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	struct timespec64 ts64;
	ts64.tv_sec  = (time_t)reltime->tv_sec;
	ts64.tv_nsec = (syscall_ulong_t)reltime->tv_nsec;
	return pthread_rwlock_acquireread(rwlock, &ts64, LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
}
/*[[[end:libc_pthread_rwlock_reltimedrdlock_np]]]*/

/*[[[head:libc_pthread_rwlock_reltimedwrlock_np,hash:CRC-32=0x3d2ca58f]]]*/
/* >> pthread_rwlock_reltimedwrlock_np(3), pthread_rwlock_reltimedwrlock64_np(3)
 * Try to acquire  write lock for  `rwlock' or return  after the specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_reltimedwrlock_np)(pthread_rwlock_t *__restrict rwlock,
                                                            struct timespec const *__restrict reltime)
/*[[[body:libc_pthread_rwlock_reltimedwrlock_np]]]*/
{
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	return pthread_rwlock_acquirewrite(rwlock, reltime, LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	struct timespec64 ts64;
	ts64.tv_sec  = (time_t)reltime->tv_sec;
	ts64.tv_nsec = (syscall_ulong_t)reltime->tv_nsec;
	return pthread_rwlock_acquirewrite(rwlock, &ts64, LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
}
/*[[[end:libc_pthread_rwlock_reltimedwrlock_np]]]*/

/*[[[head:libc_pthread_rwlock_reltimedrdlock64_np,hash:CRC-32=0x825109dc]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_rwlock_reltimedrdlock64_np, libc_pthread_rwlock_reltimedrdlock_np);
#else /* MAGIC:alias */
/* >> pthread_rwlock_reltimedrdlock_np(3), pthread_rwlock_reltimedrdlock64_np(3)
 * Try to acquire  read lock  for `rwlock' or  return after  the specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EAGAIN:    The maximum # of read-locks has been acquired
 * @return: EDEADLK:   You're already holding a write-lock
 * @return: EDEADLK:   [PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a read-lock */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_reltimedrdlock64_np)(pthread_rwlock_t *__restrict rwlock,
                                                              struct timespec64 const *__restrict reltime)
/*[[[body:libc_pthread_rwlock_reltimedrdlock64_np]]]*/
{
	return pthread_rwlock_acquireread(rwlock, reltime, LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_rwlock_reltimedrdlock64_np]]]*/

/*[[[head:libc_pthread_rwlock_reltimedwrlock64_np,hash:CRC-32=0xdad86d41]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_rwlock_reltimedwrlock64_np, libc_pthread_rwlock_reltimedwrlock_np);
#else /* MAGIC:alias */
/* >> pthread_rwlock_reltimedwrlock_np(3), pthread_rwlock_reltimedwrlock64_np(3)
 * Try to acquire  write lock for  `rwlock' or return  after the specified  time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired
 * @return: EDEADLK:   You're already holding a read-lock
 * @return: EDEADLK:   [!PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP]
 *                     You're already holding a write-lock */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(2) ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_reltimedwrlock64_np)(pthread_rwlock_t *__restrict rwlock,
                                                              struct timespec64 const *__restrict reltime)
/*[[[body:libc_pthread_rwlock_reltimedwrlock64_np]]]*/
{
	return pthread_rwlock_acquirewrite(rwlock, reltime, LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_rwlock_reltimedwrlock64_np]]]*/

/*[[[head:libc_pthread_rwlock_unlock,hash:CRC-32=0x954a9b93]]]*/
/* >> pthread_rwlock_unlock(3)
 * Unlock `rwlock'
 * @return: EOK:   Success
 * @return: EPERM: You're not holding a read- or write-lock */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_unlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_unlock]]]*/
{
	errno_t error;
	uint32_t word;
	if (rwlock->rw_flags) {
		word = ATOMIC_READ(rwlock->rw_lock);
		if (word == (uint32_t)-1) {
			/* Release write-lock */
			if (rwlock->rw_writer != gettid())
				return EPERM;
			if (rwlock->rw_nr_writers != 0) {
				--rwlock->rw_nr_writers;
				return EOK; /* Recursive write-lock */
			}
			goto do_release_write_lock;
		}

		/* Release read-lock */
		error = pthread_rwlock_delreading(rwlock);
		if (error != EOK)
			return error;
		for (;;) {
			assertf(word != 0, "But `pthread_rwlock_delreading()' "
			                   "said we were holding a read-lock...");
			if (ATOMIC_CMPXCH_WEAK(rwlock->rw_lock, word, word - 1))
				break;
			word = ATOMIC_READ(rwlock->rw_lock);
		}
	} else {
		for (;;) {
			word = ATOMIC_READ(rwlock->rw_lock);
			if (word == (uint32_t)-1) {
				/* Release write-lock */
				if (rwlock->rw_writer != gettid())
					return EPERM;
do_release_write_lock:
				rwlock->rw_writer = 0;
				COMPILER_WRITE_BARRIER();
				ATOMIC_WRITE(rwlock->rw_lock, 0);
				if (rwlock->rw_readers_wakeup) {
					/* Wake-up readers */
					ATOMIC_WRITE(rwlock->rw_readers_wakeup, 0);
					sys_Xfutex(&rwlock->rw_readers_wakeup,
					           FUTEX_WAKE, (uint32_t)-1,
					           NULL, NULL, 0);
				}
				return EOK;
			}
			if unlikely(word == 0)
				return EPERM; /* There aren't locks of any kind */
			if (ATOMIC_CMPXCH_WEAK(rwlock->rw_lock, word, word - 1))
				break;
		}
	}
	if (word == 1) {
		/* Last read-lock went away (must wake-up writers) */
		if (rwlock->rw_writer_wakeup) {
			uint32_t count;
			count = sys_Xfutex(&rwlock->rw_writer_wakeup,
			                   FUTEX_WAKE, 1, NULL, NULL, 0);
			if (count == 0) {
				/* No more writers (clear the "there-may-be-writers" flag
				 * and  broadcast anyone that  may have started listening
				 * in the meantime, so-as to ensure consistency) */
				ATOMIC_WRITE(rwlock->rw_writer_wakeup, 0);
				sys_Xfutex(&rwlock->rw_writer_wakeup,
				           FUTEX_WAKE, (uint32_t)-1,
				           NULL, NULL, 0);
			}
		}
	}
	return EOK;
}
/*[[[end:libc_pthread_rwlock_unlock]]]*/















/************************************************************************/
/* pthread_cond_t                                                       */
/************************************************************************/
/* Reminder (since I had to look this up after not remembering):
 * >> pthread_cond_wait(cond, mutex) {
 * >>     task_connect(&cond->c_lock);
 * >>     pthread_mutex_unlock(mutex);
 * >>     task_waitfor();
 * >>     pthread_mutex_lock(mutex);
 * >> }
 *
 * On KOS, we simply implement this by incrementing `c_futex' every
 * time the condition is signaled, and:
 *  - implementing `task_connect()' by reading from `c_futex'
 *  - implementing `task_waitfor()' by doing an interlocked `wait_while(c_futex == old_c_futex)'
 * Though we also make use of `FUTEX_WAITERS' by only doing a broadcast
 * when someone is actually listening to the futex.
 */


/*[[[head:libc_pthread_cond_init,hash:CRC-32=0x392aae48]]]*/
/* >> pthread_cond_init(3)
 * Initialize condition variable `cond' using attributes
 * `attr', or use the default values if later is `NULL'.
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN_OPT(2) ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cond_init)(pthread_cond_t *__restrict cond,
                                             pthread_condattr_t const *__restrict cond_attr)
/*[[[body:libc_pthread_cond_init]]]*/
{
	bzero(cond, sizeof(*cond));
	(void)cond_attr;
	return EOK;
}
/*[[[end:libc_pthread_cond_init]]]*/

/*[[[head:libc_pthread_cond_destroy,hash:CRC-32=0xb904992d]]]*/
/* >> pthread_cond_destroy(3)
 * Destroy condition variable `cond'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cond_destroy)(pthread_cond_t *cond)
/*[[[body:libc_pthread_cond_destroy]]]*/
{
	(void)cond;
	DBG_memset(cond, 0xcc, sizeof(*cond));
	return EOK;
}
/*[[[end:libc_pthread_cond_destroy]]]*/

PRIVATE ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cond_wake)(pthread_cond_t *__restrict cond,
                                             uint32_t how_many) {
	uint32_t ctl, newctl;
again:
	ctl = ATOMIC_READ(cond->c_futex);
	newctl = ((ctl & ~FUTEX_WAITERS) + 1) & ~FUTEX_WAITERS;
	if (how_many != (uint32_t)-1)
		newctl |= ctl & FUTEX_WAITERS; /* There may still be more waiters afterwards. */
	if (!ATOMIC_CMPXCH_WEAK(cond->c_futex, ctl, newctl))
		goto again;
	if (ctl & FUTEX_WAITERS) {
		/* Wake up waiting threads. */
		syscall_slong_t num_woken;
		num_woken = sys_futex(&cond->c_futex, FUTEX_WAKE,
		                      how_many, NULL, NULL, 0);
		if (num_woken == 0 && (newctl & FUTEX_WAITERS)) {
			/* Failed to wake up anyone, but the new control word
			 * still  contained  the  `FUTEX_WAITERS'  bit   set.
			 *
			 * This can happen when the caller only ever uses
			 * `pthread_cond_signal()', which would result in
			 * the `FUTEX_WAITERS' bit never getting unset.
			 *
			 * However, we do actually want to make use of that
			 * bit, so we don't have to do an expensive  system
			 * call all too often.
			 *
			 * So if we notice that  we couldn't wake up  anyone,
			 * but the futex  control word  still indicates  that
			 * there are waiting threads, then we do another wake
			 * in which we wake up _all_ waiting threads.
			 *
			 * In all likelihood, there won't be any of them  now,
			 * since just a moment ago, no-one was waiting for the
			 * futex,  but  on  the off-chance  that  more waiters
			 * appeared  between then and  now, those threads will
			 * simply receive  a sporadic,  but harmless  wake-up.
			 */
			assert(how_many != (uint32_t)-1);
			how_many = (uint32_t)-1;
			goto again;
		}
	}
	return EOK;
}

/*[[[head:libc_pthread_cond_signal,hash:CRC-32=0xac414598]]]*/
/* >> pthread_cond_signal(3)
 * Wake up one thread waiting for condition variable `cond'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cond_signal)(pthread_cond_t *cond)
/*[[[body:libc_pthread_cond_signal]]]*/
{
	return libc_pthread_cond_wake(cond, 1);
}
/*[[[end:libc_pthread_cond_signal]]]*/

/*[[[head:libc_pthread_cond_broadcast,hash:CRC-32=0xa9142e45]]]*/
/* >> pthread_cond_broadcast(3)
 * Wake up all threads waiting for condition variables `cond'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cond_broadcast)(pthread_cond_t *cond)
/*[[[body:libc_pthread_cond_broadcast]]]*/
{
	return libc_pthread_cond_wake(cond, (uint32_t)-1);
}
/*[[[end:libc_pthread_cond_broadcast]]]*/

/*[[[head:libc_pthread_cond_wait,hash:CRC-32=0x559ce274]]]*/
/* >> pthread_cond_wait(3)
 * Wait for condition variable `cond' to be signaled or broadcast.
 * `mutex' is assumed to be locked before.
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) ATTR_INOUT(2) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_cond_wait)(pthread_cond_t *__restrict cond,
                                             pthread_mutex_t *__restrict mutex)
/*[[[body:libc_pthread_cond_wait]]]*/
{
	uint32_t lock;
	/* Interlocked:begin */
	lock = ATOMIC_READ(cond->c_futex);
	/* Interlocked:op */
	libc_pthread_mutex_unlock(mutex);
	if (!(lock & FUTEX_WAITERS)) {
		/* NOTE: Don't re-load `lock' here! We _need_ the value from _before_
		 *       we've released `mutex',  else there'd be  a race  condition! */
		ATOMIC_OR(cond->c_futex, FUTEX_WAITERS);
		lock |= FUTEX_WAITERS;
	}
	/* Interlocked:wait */
	sys_futex(&cond->c_futex, FUTEX_WAIT, lock, NULL, NULL, 0);
	/* Return-path */
	libc_pthread_mutex_lock(mutex);
	return EOK;
}
/*[[[end:libc_pthread_cond_wait]]]*/

/*[[[head:libc_pthread_cond_timedwait,hash:CRC-32=0x3e8cbc6d]]]*/
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `cond' to be signaled or broadcast
 * until `abstime'.  `mutex'  is  assumed to  be  locked  before.
 * `abstime' is  an  absolute  time specification;  zero  is  the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_cond_timedwait)(pthread_cond_t *__restrict cond,
                                                  pthread_mutex_t *__restrict mutex,
                                                  struct timespec const *__restrict abstime)
/*[[[body:libc_pthread_cond_timedwait]]]*/
{
	errno_t result;
	uint32_t lock;
	/* Interlocked:begin */
	lock = ATOMIC_READ(cond->c_futex);
	/* Interlocked:op */
	libc_pthread_mutex_unlock(mutex);
	if (!(lock & FUTEX_WAITERS)) {
		/* NOTE: Don't re-load `lock' here! We _need_ the value from _before_
		 *       we've released `mutex',  else there'd be  a race  condition! */
		ATOMIC_OR(cond->c_futex, FUTEX_WAITERS);
		lock |= FUTEX_WAITERS;
	}
	/* Interlocked:wait */
	result = (errno_t)-sys_futex(&cond->c_futex, FUTEX_WAIT_BITSET, lock,
	                             abstime, NULL, FUTEX_BITSET_MATCH_ANY);
	/* Check for timeout. */
	if (result != ETIMEDOUT && result != EINVAL)
		result = EOK;
	/* Return-path */
	libc_pthread_mutex_lock(mutex);
	return result;
}
/*[[[end:libc_pthread_cond_timedwait]]]*/

/*[[[head:libc_pthread_cond_timedwait64,hash:CRC-32=0xdc3ee592]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_cond_timedwait64, libc_pthread_cond_timedwait);
#else /* MAGIC:alias */
/* >> pthread_cond_timedwait(3), pthread_cond_timedwait64(3)
 * Wait for condition variable `cond' to be signaled or broadcast
 * until `abstime'.  `mutex'  is  assumed to  be  locked  before.
 * `abstime' is  an  absolute  time specification;  zero  is  the
 * beginning of the epoch (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_cond_timedwait64)(pthread_cond_t *__restrict cond,
                                                    pthread_mutex_t *__restrict mutex,
                                                    struct timespec64 const *__restrict abstime)
/*[[[body:libc_pthread_cond_timedwait64]]]*/
{
	errno_t result;
	uint32_t lock;
	/* Interlocked:begin */
	lock = ATOMIC_READ(cond->c_futex);
	/* Interlocked:op */
	libc_pthread_mutex_unlock(mutex);
	if (!(lock & FUTEX_WAITERS)) {
		/* NOTE: Don't re-load `lock' here! We _need_ the value from _before_
		 *       we've released `mutex',  else there'd be  a race  condition! */
		ATOMIC_OR(cond->c_futex, FUTEX_WAITERS);
		lock |= FUTEX_WAITERS;
	}
	/* Interlocked:wait */
	result = (errno_t)-sys_lfutex32_waitwhile64(&cond->c_futex, lock, abstime, 0);
	/* Check for timeout. */
	if (result != ETIMEDOUT && result != EINVAL)
		result = EOK;
	/* Return-path */
	libc_pthread_mutex_lock(mutex);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_cond_timedwait64]]]*/

/*[[[head:libc_pthread_cond_reltimedwait_np,hash:CRC-32=0xafc1fe7]]]*/
/* >> pthread_cond_reltimedwait_np(3), pthread_cond_reltimedwait64_np(3)
 * Wait for  condition  variable  `cond' to  be  signaled  or  broadcast
 * until `reltime'. `mutex' is assumed to be locked before.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_cond_reltimedwait_np)(pthread_cond_t *__restrict cond,
                                                        pthread_mutex_t *__restrict mutex,
                                                        struct timespec const *__restrict reltime)
/*[[[body:libc_pthread_cond_reltimedwait_np]]]*/
{
	errno_t result;
	uint32_t lock;
	/* Interlocked:begin */
	lock = ATOMIC_READ(cond->c_futex);
	/* Interlocked:op */
	libc_pthread_mutex_unlock(mutex);
	if (!(lock & FUTEX_WAITERS)) {
		/* NOTE: Don't re-load `lock' here! We _need_ the value from _before_
		 *       we've released `mutex',  else there'd be  a race  condition! */
		ATOMIC_OR(cond->c_futex, FUTEX_WAITERS);
		lock |= FUTEX_WAITERS;
	}
	/* Interlocked:wait */
	result = (errno_t)-sys_futex(&cond->c_futex, FUTEX_WAIT,
	                             lock, reltime, NULL, 0);
	/* Check for timeout. */
	if (result != ETIMEDOUT && result != EINVAL)
		result = EOK;
	/* Return-path */
	libc_pthread_mutex_lock(mutex);
	return result;
}
/*[[[end:libc_pthread_cond_reltimedwait_np]]]*/

/*[[[head:libc_pthread_cond_reltimedwait64_np,hash:CRC-32=0x7903630a]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_cond_reltimedwait64_np, libc_pthread_cond_reltimedwait_np);
#else /* MAGIC:alias */
/* >> pthread_cond_reltimedwait_np(3), pthread_cond_reltimedwait64_np(3)
 * Wait for  condition  variable  `cond' to  be  signaled  or  broadcast
 * until `reltime'. `mutex' is assumed to be locked before.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `reltime' is invalid
 * @return: ETIMEDOUT: The given `reltime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED ATTR_IN(3) ATTR_INOUT(1) ATTR_INOUT(2) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_cond_reltimedwait64_np)(pthread_cond_t *__restrict cond,
                                                          pthread_mutex_t *__restrict mutex,
                                                          struct timespec64 const *__restrict reltime)
/*[[[body:libc_pthread_cond_reltimedwait64_np]]]*/
{
	errno_t result;
	uint32_t lock;
	/* Interlocked:begin */
	lock = ATOMIC_READ(cond->c_futex);
	/* Interlocked:op */
	libc_pthread_mutex_unlock(mutex);
	if (!(lock & FUTEX_WAITERS)) {
		/* NOTE: Don't re-load `lock' here! We _need_ the value from _before_
		 *       we've released `mutex',  else there'd be  a race  condition! */
		ATOMIC_OR(cond->c_futex, FUTEX_WAITERS);
		lock |= FUTEX_WAITERS;
	}
	/* Interlocked:wait */
	result = (errno_t)-sys_lfutex32_waitwhile64(&cond->c_futex, lock, reltime,
	                                            LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE);
	/* Check for timeout. */
	if (result != ETIMEDOUT && result != EINVAL)
		result = EOK;
	/* Return-path */
	libc_pthread_mutex_lock(mutex);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_cond_reltimedwait64_np]]]*/















/************************************************************************/
/* pthread_barrier_t                                                    */
/************************************************************************/

/*[[[head:libc_pthread_barrier_init,hash:CRC-32=0x722b495e]]]*/
/* >> pthread_barrier_init(3)
 * Initialize `barrier' with the attributes in `attr'.
 * The  barrier is opened when `count' waiters arrived
 * @return: EOK:    Success
 * @return: EINVAL: The given `count' is ZERO(0) */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_IN_OPT(2) ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrier_init)(pthread_barrier_t *__restrict barrier,
                                                pthread_barrierattr_t const *__restrict attr,
                                                unsigned int count)
/*[[[body:libc_pthread_barrier_init]]]*/
/*AUTO*/{
	(void)barrier;
	(void)attr;
	(void)count;
	CRT_UNIMPLEMENTEDF("pthread_barrier_init(barrier: %p, attr: %p, count: %x)", barrier, attr, count); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_barrier_init]]]*/

/*[[[head:libc_pthread_barrier_destroy,hash:CRC-32=0xe1fa1bbb]]]*/
/* >> pthread_barrier_destroy(3)
 * Destroy the given (previously dynamically initialized) `barrier'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrier_destroy)(pthread_barrier_t *barrier)
/*[[[body:libc_pthread_barrier_destroy]]]*/
/*AUTO*/{
	(void)barrier;
	CRT_UNIMPLEMENTEDF("pthread_barrier_destroy(barrier: %p)", barrier); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_barrier_destroy]]]*/

/*[[[head:libc_pthread_barrier_wait,hash:CRC-32=0x9266172d]]]*/
/* >> pthread_barrier_wait(3)
 * Wait on the given `barrier'
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_INOUT(1) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_barrier_wait)(pthread_barrier_t *barrier)
/*[[[body:libc_pthread_barrier_wait]]]*/
/*AUTO*/{
	(void)barrier;
	CRT_UNIMPLEMENTEDF("pthread_barrier_wait(barrier: %p)", barrier); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_barrier_wait]]]*/















/************************************************************************/
/* pthread_key_t                                                        */
/************************************************************************/

typedef void (LIBCCALL *pthread_destr_function_t)(void *arg);

/* [0..1][0..tls_count][owned] Vector TLS destructors.
 * A NULL-entry indicates a slot that was previously allocated, but has become available. */
PRIVATE ATTR_SECTION(".bss.crt.sched.pthread") pthread_destr_function_t *tls_dtors = NULL;

/* Max allocated TLS key, plus 1. This describes the length of `tls_dtors' */
PRIVATE ATTR_SECTION(".bss.crt.sched.pthread") size_t tls_count = 0;

/* Check that a  given TLS-key  has been  allocated; the  caller must  be
 * holding at least a read-lock to `tls_lock' when calling this function. */
#define tls_keyok(key) ((size_t)(key) < tls_count && tls_dtors[(size_t)(key)] != NULL)


/* Lock for accessing `tls_dtors' and `tls_count' */
PRIVATE ATTR_SECTION(".bss.crt.sched.pthread")
struct atomic_rwlock tls_lock = ATOMIC_RWLOCK_INIT;

/* Helper macros for `tls_lock' */
#define tls_mustreap()   0
#define tls_reap()       (void)0
#define _tls_reap()      (void)0
#define tls_write()      atomic_rwlock_write(&tls_lock)
#define tls_trywrite()   atomic_rwlock_trywrite(&tls_lock)
#define tls_endwrite()   (atomic_rwlock_endwrite(&tls_lock), tls_reap())
#define _tls_endwrite()  atomic_rwlock_endwrite(&tls_lock)
#define tls_read()       atomic_rwlock_read(&tls_lock)
#define tls_tryread()    atomic_rwlock_tryread(&tls_lock)
#define _tls_endread()   atomic_rwlock_endread(&tls_lock)
#define tls_endread()    (void)(atomic_rwlock_endread(&tls_lock) && (tls_reap(), 0))
#define _tls_end()       atomic_rwlock_end(&tls_lock)
#define tls_end()        (void)(atomic_rwlock_end(&tls_lock) && (tls_reap(), 0))
#define tls_upgrade()    atomic_rwlock_upgrade(&tls_lock)
#define tls_tryupgrade() atomic_rwlock_tryupgrade(&tls_lock)
#define tls_downgrade()  atomic_rwlock_downgrade(&tls_lock)
#define tls_reading()    atomic_rwlock_reading(&tls_lock)
#define tls_writing()    atomic_rwlock_writing(&tls_lock)
#define tls_canread()    atomic_rwlock_canread(&tls_lock)
#define tls_canwrite()   atomic_rwlock_canwrite(&tls_lock)
#define tls_waitread()   atomic_rwlock_waitread(&tls_lock)
#define tls_waitwrite()  atomic_rwlock_waitwrite(&tls_lock)


/* [0..1][lock(WRITE_ONCE)] TLS  segment (from  libdl's `dltlsalloc(3D)')  that
 * is  used  for representing  and storing  TLS values  on a  per-thread basis.
 * Technically,  we could get  rid of this right  here, and put  all of the TLS
 * stuff into `current', but since KOS already supports static TLS declaration,
 * aka `ATTR_THREAD'  (which is  actually the  _very_ _much_  preferred  method
 * of allocating  TLS memory),  anything that  is written  to be  more or  less
 * optimized for a platform like KOS shouldn't  even have to make use of  this.
 * As  such,  don't  put  more  stuff  into  `current',  and  use  dynamic  TLS
 * allocations for implementing pthread-based TLS variables. */
PRIVATE ATTR_SECTION(".bss.crt.sched.pthread") void *tls_handle = NULL;

struct pthread_tls_segment {
	/* This is the structure that is pointed-to by instance of `tls_handle'
	 * Note  that   this   structure   exists  on   a   per-thread   basis! */
	size_t  pts_alloc;      /* Allocated TLS value-vector size. */
	void  **pts_values;     /* [?..?][0..pts_alloc] Vector of TLS values. */
	void   *pts_static[32]; /* Initial (static) vector for holding the first N keys.
	                         * This vector gets  allocated by libdl  and is here  so
	                         * we don't waste  too much memory  (since TLS  segments
	                         * allocated  by  `dltlsalloc(3D)' have  quite a  lot of
	                         * overhead) */
};

PRIVATE void __LIBCCALL
pthread_tls_segment_init(void *UNUSED(arg), void *base,
                         void *UNUSED(tls_segment)) {
	struct pthread_tls_segment *me;
	me = (struct pthread_tls_segment *)base;
	me->pts_values = me->pts_static;
	me->pts_alloc  = lengthof(me->pts_static);
}

PRIVATE void __LIBCCALL
pthread_tls_segment_fini(void *UNUSED(arg), void *base,
                         void *UNUSED(tls_segment)) {
	struct pthread_tls_segment *me;
	size_t i, attempt = 0;
	bool found_some;
	do {
		found_some = false;
		me = (struct pthread_tls_segment *)base;
		for (i = 0; i < me->pts_alloc; ++i) {
			void *tls_value;
			tls_value = me->pts_values[i];
			if (tls_value != NULL) {
				pthread_destr_function_t dtor;
				me->pts_values[i] = NULL;
				dtor              = NULL;
				tls_read();
				if likely(i < tls_count)
					dtor = tls_dtors[i];
				tls_endread();
				/* Invoke the TLS destructor for non-NULL values. */
				if (dtor) {
					(*dtor)(tls_value);
					found_some = true;
				}
			}
		}
		++attempt;
	} while (found_some &&
	         attempt < PTHREAD_DESTRUCTOR_ITERATIONS);
	/* Free a dynamically allocated TLS data-vector. */
	if (me->pts_values != me->pts_static)
		free(me->pts_values);
}

/* Return the pthread TLS-segment for the calling thread,
 * allocating  it, as well  as `tls_handle' if necessary.
 * @return: NULL: Insufficient memory. */
PRIVATE WUNUSED struct pthread_tls_segment *
NOTHROW_NCX(LIBCCALL get_pthread_tls_segment)(void) {
	void *result;
	void *handle = ATOMIC_READ(tls_handle);
	if unlikely(!handle) {
		void *real_handle;
		/* Allocate on first access. */
		handle = dltlsalloc(/* num_bytes:              */ sizeof(struct pthread_tls_segment),
		                    /* min_alignment:          */ alignof(struct pthread_tls_segment),
		                    /* template_data:          */ NULL,
		                    /* template_size:          */ 0,
		                    /* perthread_init:         */ &pthread_tls_segment_init,
		                    /* perthread_fini:         */ &pthread_tls_segment_fini,
		                    /* perthread_callback_arg: */ NULL);
		if unlikely(!handle)
			return NULL;

		/* Remember the handle. */
		real_handle = ATOMIC_CMPXCH_VAL(tls_handle, NULL, handle);
		if unlikely(real_handle != NULL) {
			dltlsfree(handle);
			handle = real_handle;
		}
	}

	/* Now load the segment for the calling thread. */
	result = dltlsaddr(handle);

	/* And return its address. */
	return (struct pthread_tls_segment *)result;
}

/* Return a pointer to the TLS slot described by `id'
 * within the  calling thread's  pthread-tls-segment.
 * If TLS descriptors, or the associated slot had yet
 * to be allocated, try allocate them now, but return
 * `NULL' if doing so failed due to lack of memory.
 * NOTE: It is up  to the  caller to ensure  that `id'  is
 *       a  valid id before calling this function. Because
 *       if it wasn't a valid id beforehand, it will kind-
 *       of become one (at  least for the calling  thread)
 *       once this function returns! */
PRIVATE WUNUSED void **
NOTHROW_NCX(LIBCCALL get_pthread_tls_slot)(size_t id) {
	struct pthread_tls_segment *self;
	self = get_pthread_tls_segment();
	if unlikely(!self)
		return NULL;

	/* Check if the given `id' is allocated. */
	if unlikely(id >= self->pts_alloc) {
		void *old_base, *new_base;

		/* Must allocate more memory. */
		old_base = self->pts_values;
		if (old_base == self->pts_static)
			old_base = NULL;

		/* Use recalloc(), so we automatically zero-initialize newly
		 * allocated slots. */
		new_base = recalloc(old_base, id + 1, sizeof(void *));
		if unlikely(!new_base)
			return NULL;

		/* If the old base was the static vector, then we must
		 * manually copy over old TLS values. */
		if (old_base == self->pts_static) {
			memcpy(new_base, self->pts_static,
			       self->pts_alloc, sizeof(void *));
		}

		/* Write-back updated TLS values. */
		self->pts_alloc  = id + 1;
		self->pts_values = (void **)new_base;
	}

	/* Return the pointer to the appropriate slot. */
	return &self->pts_values[id];
}

/* No-op destructor used to mark TLS-slots without custom destructors as in-use. */
PRIVATE void LIBKCALL noop_dtor(void *UNUSED(value)) {
}

/*[[[head:libc_pthread_key_create,hash:CRC-32=0xa6ac1564]]]*/
/* >> pthread_key_create(3)
 * Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. `destr_function', if non-`NULL', is called with the  value
 * associated to that key when the key is destroyed.
 * `destr_function' is not called if the value associated is `NULL'
 * when the key is destroyed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_OUT(1) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_key_create)(pthread_key_t *key,
                                              void (LIBKCALL *destr_function)(void *value))
/*[[[body:libc_pthread_key_create]]]*/
{
	size_t i, avail, count;
	if (!destr_function)
		destr_function = &noop_dtor;
again:
	tls_write();
	count = ATOMIC_READ(tls_count);
	/* Check if we can re-use a previously freed slot. */
	for (i = 0; i < count; ++i) {
		if (tls_dtors[i] == NULL)
			goto use_ith_slot; /* Re-use this slot! */
	}
	/* Check if we must increase the allocated size of the TLS-destructor-vector. */
	avail = malloc_usable_size(tls_dtors) / sizeof(pthread_destr_function_t);
	assert(i == count);
	assert(count <= avail);
	if (i >= avail) {
		pthread_destr_function_t *old_destructors;
		pthread_destr_function_t *new_destructors;
		tls_endwrite();

		/* Allocate  a new (slightly larger) TLS destructor vector.
		 * Note that we mustn't hold `tls_lock' in here, since that
		 * could lead to a dead-lock  depending on how malloc()  is
		 * implemented.
		 * After all: `tls_lock' is an _atomic_ lock, so we have to
		 *            make a real effort to always hold it for  the
		 *            least amount of time possible. */
		new_destructors = (pthread_destr_function_t *)malloc(count + 1,
		                                                     sizeof(pthread_destr_function_t));

		/* Check if the allocation was ok. */
		if unlikely(!new_destructors)
			return ENOMEM;

		tls_write();
		/* Make sure that the TLS count didn't change in the mean time. */
		if (ATOMIC_READ(tls_count) != count) {
			tls_endwrite();
			free(new_destructors);
			goto again;
		}

		/* Copy over old destructors. */
		old_destructors = tls_dtors;
		memcpy(new_destructors, old_destructors,
		       count, sizeof(pthread_destr_function_t));

		/* Set the new destructors vector as active. */
		tls_dtors = new_destructors;
		tls_endwrite();

		/* Free the old TLS destructors vector. */
		free(old_destructors);
		goto again;
	}
	/* Simply append the new TLS slot at the
	 * end. Note that i == count from above! */
	assert(i == count);
	tls_count = i + 1;
use_ith_slot:
	tls_dtors[i] = destr_function;
	tls_endwrite();
	*key = (pthread_key_t)i;
	return EOK;
}
/*[[[end:libc_pthread_key_create]]]*/

/*[[[head:libc_pthread_key_delete,hash:CRC-32=0x685944ff]]]*/
/* >> pthread_key_delete(3)
 * Destroy the given  `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_key_delete)(pthread_key_t key)
/*[[[body:libc_pthread_key_delete]]]*/
{
	errno_t result = EOK;
	tls_write();
	if unlikely(!tls_keyok(key)) {
		/* Bad key! */
		result = EINVAL;
	} else {
		/* Delete the destructor of key, thus deallocating it. */
		tls_dtors[(size_t)key] = NULL;
		/* Truncate the total count of allocated keys, if possible. */
		if ((size_t)key == tls_count - 1) {
			while (tls_count && !tls_dtors[tls_count - 1])
				--tls_count;
			/* Special case: If all TLS keys have been destroyed, free the destructor-vector. */
			if (!tls_count) {
				pthread_destr_function_t *old_dtors;
				old_dtors = tls_dtors;
				tls_dtors = NULL;
				tls_endwrite();
				free(old_dtors);
				goto done;
			} else {
				/* XXX: >> tls_dtors = realloc_nonblock(tls_dtors,
				 *      >>                              tls_count,
				 *      >>                              sizeof(pthread_destr_function_t));
				 */
			}
		}
	}
	tls_endwrite();
done:
	return result;
}
/*[[[end:libc_pthread_key_delete]]]*/

/*[[[head:libc_pthread_getspecific,hash:CRC-32=0xf0163f03]]]*/
/* >> pthread_getspecific(3)
 * Return current value of the thread-specific data slot identified by `key'
 * @return: * :   The value currently associated with `key' in the calling thread
 * @return: NULL: The current value is `NULL'
 * @return: NULL: No value has been bound, yet
 * @return: NULL: Invalid `key' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED void *
NOTHROW_NCX(LIBCCALL libc_pthread_getspecific)(pthread_key_t key)
/*[[[body:libc_pthread_getspecific]]]*/
{
	void *result = NULL;
	/* Verify that `key' is actually valid. */
	tls_read();
	if unlikely(!tls_keyok(key)) {
		tls_endread();
		/* Bad key! */
	} else {
		void **slot;
		tls_endread();

		/* Lookup the slot for `key' */
		slot = get_pthread_tls_slot((size_t)key);

		/* Load the value of `slot' */
		if likely(slot)
			result = *slot;
	}
	return result;
}
/*[[[end:libc_pthread_getspecific]]]*/

/*[[[head:libc_pthread_setspecific,hash:CRC-32=0x60e794ce]]]*/
/* >> pthread_setspecific(3)
 * Store POINTER in the thread-specific data slot identified by `key'
 * @return: EOK:    Success
 * @return: EINVAL: Invalid `key'
 * @return: ENOMEM: `pointer' is non-`NULL', `key' had yet to be allocated for the
 *                  calling  thread, and an attempt to allocate it just now failed */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_ACCESS_NONE(2) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setspecific)(pthread_key_t key,
                                               void const *pointer)
/*[[[body:libc_pthread_setspecific]]]*/
{
	void **slot;
	/* Verify that `key' is actually valid. */
	tls_read();
	if unlikely(!tls_keyok(key)) {
		tls_endread();
		/* Bad key! */
		return EINVAL;
	}
	tls_endread();

	/* Lookup the slot for `key' */
	slot = get_pthread_tls_slot((size_t)key);
	if unlikely(!slot)
		return ENOMEM;

	/* Write the value to the slot. */
	*slot = (void *)pointer;
	return EOK;
}
/*[[[end:libc_pthread_setspecific]]]*/

/*[[[head:libc_pthread_getspecificptr_np,hash:CRC-32=0x1c1fa9c4]]]*/
/* >> pthread_getspecificptr_np(3)
 * Return a pointer to the per-thread storage location associated with `key'
 * @return: * :   The address read/written by `pthread_getspecific()' / `pthread_setspecific()'
 * @return: NULL: `key' had yet to be allocated for the calling thread,
 *                and an  attempt  to  allocate  it  just  now  failed.
 * @return: NULL: Invalid `key'. */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_CONST WUNUSED void **
NOTHROW_NCX(LIBCCALL libc_pthread_getspecificptr_np)(pthread_key_t key)
/*[[[body:libc_pthread_getspecificptr_np]]]*/
{
	void **result = NULL;
	/* Verify that `key' is actually valid. */
	tls_read();
	if unlikely(!tls_keyok(key)) {
		tls_endread();
		/* Bad key! */
	} else {
		tls_endread();

		/* Lookup the slot for `key' */
		result = get_pthread_tls_slot((size_t)key);
	}
	return result;
}
/*[[[end:libc_pthread_getspecificptr_np]]]*/





/*[[[start:exports,hash:CRC-32=0xdca325be]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$pthread_create, libd_pthread_create);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(pthread_create, libc_pthread_create);
DEFINE_PUBLIC_ALIAS(thr_exit, libc_pthread_exit);
DEFINE_PUBLIC_ALIAS(cthread_exit, libc_pthread_exit);
DEFINE_PUBLIC_ALIAS(pthread_exit, libc_pthread_exit);
DEFINE_PUBLIC_ALIAS(pthread_join, libc_pthread_join);
DEFINE_PUBLIC_ALIAS(pthread_getresult_np, libc_pthread_getresult_np);
DEFINE_PUBLIC_ALIAS(pthread_tryjoin_np, libc_pthread_tryjoin_np);
DEFINE_PUBLIC_ALIAS(pthread_timedjoin_np, libc_pthread_timedjoin_np);
DEFINE_PUBLIC_ALIAS(pthread_timedjoin64_np, libc_pthread_timedjoin64_np);
DEFINE_PUBLIC_ALIAS(cthread_detach, libc_pthread_detach);
DEFINE_PUBLIC_ALIAS(pthread_detach, libc_pthread_detach);
DEFINE_PUBLIC_ALIAS(thrd_current, libc_pthread_self);
DEFINE_PUBLIC_ALIAS(thr_self, libc_pthread_self);
DEFINE_PUBLIC_ALIAS(cthread_self, libc_pthread_self);
DEFINE_PUBLIC_ALIAS(pthread_self, libc_pthread_self);
DEFINE_PUBLIC_ALIAS(pthread_attr_init, libc_pthread_attr_init);
DEFINE_PUBLIC_ALIAS(pthread_attr_destroy, libc_pthread_attr_destroy);
DEFINE_PUBLIC_ALIAS(pthread_attr_getdetachstate, libc_pthread_attr_getdetachstate);
DEFINE_PUBLIC_ALIAS(pthread_attr_setdetachstate, libc_pthread_attr_setdetachstate);
DEFINE_PUBLIC_ALIAS(pthread_attr_getguardsize, libc_pthread_attr_getguardsize);
DEFINE_PUBLIC_ALIAS(pthread_attr_setguardsize, libc_pthread_attr_setguardsize);
DEFINE_PUBLIC_ALIAS(pthread_attr_getschedparam, libc_pthread_attr_getschedparam);
DEFINE_PUBLIC_ALIAS(pthread_attr_setschedparam, libc_pthread_attr_setschedparam);
DEFINE_PUBLIC_ALIAS(pthread_attr_getschedpolicy, libc_pthread_attr_getschedpolicy);
DEFINE_PUBLIC_ALIAS(pthread_attr_setschedpolicy, libc_pthread_attr_setschedpolicy);
DEFINE_PUBLIC_ALIAS(pthread_attr_getinheritsched, libc_pthread_attr_getinheritsched);
DEFINE_PUBLIC_ALIAS(pthread_attr_setinheritsched, libc_pthread_attr_setinheritsched);
DEFINE_PUBLIC_ALIAS(pthread_attr_getscope, libc_pthread_attr_getscope);
DEFINE_PUBLIC_ALIAS(pthread_attr_setscope, libc_pthread_attr_setscope);
DEFINE_PUBLIC_ALIAS(pthread_attr_getstackaddr, libc_pthread_attr_getstackaddr);
DEFINE_PUBLIC_ALIAS(pthread_attr_setstackaddr, libc_pthread_attr_setstackaddr);
DEFINE_PUBLIC_ALIAS(pthread_attr_getstacksize, libc_pthread_attr_getstacksize);
DEFINE_PUBLIC_ALIAS(pthread_attr_setstacksize, libc_pthread_attr_setstacksize);
DEFINE_PUBLIC_ALIAS(pthread_attr_getstack, libc_pthread_attr_getstack);
DEFINE_PUBLIC_ALIAS(pthread_attr_setstack, libc_pthread_attr_setstack);
DEFINE_PUBLIC_ALIAS(pthread_attr_setaffinity_np, libc_pthread_attr_setaffinity_np);
DEFINE_PUBLIC_ALIAS(pthread_attr_getaffinity_np, libc_pthread_attr_getaffinity_np);
DEFINE_PUBLIC_ALIAS(pthread_getattr_default_np, libc_pthread_getattr_default_np);
DEFINE_PUBLIC_ALIAS(pthread_setattr_default_np, libc_pthread_setattr_default_np);
DEFINE_PUBLIC_ALIAS(pthread_getattr_np, libc_pthread_getattr_np);
DEFINE_PUBLIC_ALIAS(pthread_setschedparam, libc_pthread_setschedparam);
DEFINE_PUBLIC_ALIAS(pthread_getschedparam, libc_pthread_getschedparam);
DEFINE_PUBLIC_ALIAS(pthread_setschedprio, libc_pthread_setschedprio);
DEFINE_PUBLIC_ALIAS(pthread_get_name_np, libc_pthread_getname_np);
DEFINE_PUBLIC_ALIAS(pthread_getname_np, libc_pthread_getname_np);
DEFINE_PUBLIC_ALIAS(pthread_set_name_np, libc_pthread_setname_np);
DEFINE_PUBLIC_ALIAS(cthread_set_name, libc_pthread_setname_np);
DEFINE_PUBLIC_ALIAS(pthread_setname_np, libc_pthread_setname_np);
DEFINE_PUBLIC_ALIAS(pthread_gettid_np, libc_pthread_gettid_np);
DEFINE_PUBLIC_ALIAS(pthread_mainthread_np, libc_pthread_mainthread_np);
DEFINE_PUBLIC_ALIAS(pthread_rpc_exec, libc_pthread_rpc_exec);
DEFINE_PUBLIC_ALIAS(thr_getconcurrency, libc_pthread_getconcurrency);
DEFINE_PUBLIC_ALIAS(pthread_getconcurrency, libc_pthread_getconcurrency);
DEFINE_PUBLIC_ALIAS(thr_setconcurrency, libc_pthread_setconcurrency);
DEFINE_PUBLIC_ALIAS(pthread_setconcurrency, libc_pthread_setconcurrency);
DEFINE_PUBLIC_ALIAS(pthread_setaffinity_np, libc_pthread_setaffinity_np);
DEFINE_PUBLIC_ALIAS(pthread_getaffinity_np, libc_pthread_getaffinity_np);
DEFINE_PUBLIC_ALIAS(pthread_setcancelstate, libc_pthread_setcancelstate);
DEFINE_PUBLIC_ALIAS(pthread_setcanceltype, libc_pthread_setcanceltype);
DEFINE_PUBLIC_ALIAS(pthread_cancel, libc_pthread_cancel);
DEFINE_PUBLIC_ALIAS(pthread_testcancel, libc_pthread_testcancel);
DEFINE_PUBLIC_ALIAS(__pthread_register_cancel, libc___pthread_register_cancel);
DEFINE_PUBLIC_ALIAS(__pthread_unregister_cancel, libc___pthread_unregister_cancel);
DEFINE_PUBLIC_ALIAS(__pthread_register_cancel_defer, libc___pthread_register_cancel_defer);
DEFINE_PUBLIC_ALIAS(__pthread_unregister_cancel_restore, libc___pthread_unregister_cancel_restore);
DEFINE_PUBLIC_ALIAS(__pthread_unwind_next, libc___pthread_unwind_next);
DEFINE_PUBLIC_ALIAS(pthread_mutex_init, libc_pthread_mutex_init);
DEFINE_PUBLIC_ALIAS(mtx_destroy, libc_pthread_mutex_destroy);
DEFINE_PUBLIC_ALIAS(pthread_mutex_destroy, libc_pthread_mutex_destroy);
DEFINE_PUBLIC_ALIAS(pthread_mutex_trylock, libc_pthread_mutex_trylock);
DEFINE_PUBLIC_ALIAS(pthread_mutex_lock, libc_pthread_mutex_lock);
DEFINE_PUBLIC_ALIAS(pthread_mutex_timedlock, libc_pthread_mutex_timedlock);
DEFINE_PUBLIC_ALIAS(pthread_mutex_timedlock64, libc_pthread_mutex_timedlock64);
DEFINE_PUBLIC_ALIAS(pthread_mutex_reltimedlock_np, libc_pthread_mutex_reltimedlock_np);
DEFINE_PUBLIC_ALIAS(pthread_mutex_reltimedlock64_np, libc_pthread_mutex_reltimedlock64_np);
DEFINE_PUBLIC_ALIAS(pthread_mutex_unlock, libc_pthread_mutex_unlock);
DEFINE_PUBLIC_ALIAS(pthread_mutex_getprioceiling, libc_pthread_mutex_getprioceiling);
DEFINE_PUBLIC_ALIAS(pthread_mutex_setprioceiling, libc_pthread_mutex_setprioceiling);
DEFINE_PUBLIC_ALIAS(pthread_mutex_consistent_np, libc_pthread_mutex_consistent);
DEFINE_PUBLIC_ALIAS(pthread_mutex_consistent, libc_pthread_mutex_consistent);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_init, libc_pthread_mutexattr_init);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_destroy, libc_pthread_mutexattr_destroy);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_getpshared, libc_pthread_mutexattr_getpshared);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_setpshared, libc_pthread_mutexattr_setpshared);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_getkind_np, libc_pthread_mutexattr_gettype);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_gettype, libc_pthread_mutexattr_gettype);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_setkind_np, libc_pthread_mutexattr_settype);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_settype, libc_pthread_mutexattr_settype);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_getprotocol, libc_pthread_mutexattr_getprotocol);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_setprotocol, libc_pthread_mutexattr_setprotocol);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_getprioceiling, libc_pthread_mutexattr_getprioceiling);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_setprioceiling, libc_pthread_mutexattr_setprioceiling);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_getrobust_np, libc_pthread_mutexattr_getrobust);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_getrobust, libc_pthread_mutexattr_getrobust);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_setrobust_np, libc_pthread_mutexattr_setrobust);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_setrobust, libc_pthread_mutexattr_setrobust);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_init, libc_pthread_rwlock_init);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_destroy, libc_pthread_rwlock_destroy);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_rdlock, libc_pthread_rwlock_rdlock);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_tryrdlock, libc_pthread_rwlock_tryrdlock);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_wrlock, libc_pthread_rwlock_wrlock);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_trywrlock, libc_pthread_rwlock_trywrlock);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_timedrdlock, libc_pthread_rwlock_timedrdlock);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_timedwrlock, libc_pthread_rwlock_timedwrlock);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_timedrdlock64, libc_pthread_rwlock_timedrdlock64);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_timedwrlock64, libc_pthread_rwlock_timedwrlock64);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_reltimedrdlock_np, libc_pthread_rwlock_reltimedrdlock_np);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_reltimedwrlock_np, libc_pthread_rwlock_reltimedwrlock_np);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_reltimedrdlock64_np, libc_pthread_rwlock_reltimedrdlock64_np);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_reltimedwrlock64_np, libc_pthread_rwlock_reltimedwrlock64_np);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_unlock, libc_pthread_rwlock_unlock);
DEFINE_PUBLIC_ALIAS(pthread_rwlockattr_init, libc_pthread_rwlockattr_init);
DEFINE_PUBLIC_ALIAS(pthread_rwlockattr_destroy, libc_pthread_rwlockattr_destroy);
DEFINE_PUBLIC_ALIAS(pthread_rwlockattr_getpshared, libc_pthread_rwlockattr_getpshared);
DEFINE_PUBLIC_ALIAS(pthread_rwlockattr_setpshared, libc_pthread_rwlockattr_setpshared);
DEFINE_PUBLIC_ALIAS(pthread_rwlockattr_getkind_np, libc_pthread_rwlockattr_getkind_np);
DEFINE_PUBLIC_ALIAS(pthread_rwlockattr_setkind_np, libc_pthread_rwlockattr_setkind_np);
DEFINE_PUBLIC_ALIAS(pthread_cond_init, libc_pthread_cond_init);
DEFINE_PUBLIC_ALIAS(cnd_destroy, libc_pthread_cond_destroy);
DEFINE_PUBLIC_ALIAS(pthread_cond_destroy, libc_pthread_cond_destroy);
DEFINE_PUBLIC_ALIAS(pthread_cond_signal, libc_pthread_cond_signal);
DEFINE_PUBLIC_ALIAS(pthread_cond_broadcast, libc_pthread_cond_broadcast);
DEFINE_PUBLIC_ALIAS(pthread_cond_wait, libc_pthread_cond_wait);
DEFINE_PUBLIC_ALIAS(pthread_cond_timedwait, libc_pthread_cond_timedwait);
DEFINE_PUBLIC_ALIAS(pthread_cond_timedwait64, libc_pthread_cond_timedwait64);
DEFINE_PUBLIC_ALIAS(pthread_cond_reltimedwait_np, libc_pthread_cond_reltimedwait_np);
DEFINE_PUBLIC_ALIAS(pthread_cond_reltimedwait64_np, libc_pthread_cond_reltimedwait64_np);
DEFINE_PUBLIC_ALIAS(pthread_condattr_init, libc_pthread_condattr_init);
DEFINE_PUBLIC_ALIAS(pthread_condattr_destroy, libc_pthread_condattr_destroy);
DEFINE_PUBLIC_ALIAS(pthread_condattr_getpshared, libc_pthread_condattr_getpshared);
DEFINE_PUBLIC_ALIAS(pthread_condattr_setpshared, libc_pthread_condattr_setpshared);
DEFINE_PUBLIC_ALIAS(pthread_condattr_getclock, libc_pthread_condattr_getclock);
DEFINE_PUBLIC_ALIAS(pthread_condattr_setclock, libc_pthread_condattr_setclock);
DEFINE_PUBLIC_ALIAS(pthread_barrier_init, libc_pthread_barrier_init);
DEFINE_PUBLIC_ALIAS(pthread_barrier_destroy, libc_pthread_barrier_destroy);
DEFINE_PUBLIC_ALIAS(pthread_barrier_wait, libc_pthread_barrier_wait);
DEFINE_PUBLIC_ALIAS(pthread_barrierattr_init, libc_pthread_barrierattr_init);
DEFINE_PUBLIC_ALIAS(pthread_barrierattr_destroy, libc_pthread_barrierattr_destroy);
DEFINE_PUBLIC_ALIAS(pthread_barrierattr_getpshared, libc_pthread_barrierattr_getpshared);
DEFINE_PUBLIC_ALIAS(pthread_barrierattr_setpshared, libc_pthread_barrierattr_setpshared);
DEFINE_PUBLIC_ALIAS(thr_keycreate, libc_pthread_key_create);
DEFINE_PUBLIC_ALIAS(pthread_key_create, libc_pthread_key_create);
DEFINE_PUBLIC_ALIAS(tss_delete, libc_pthread_key_delete);
DEFINE_PUBLIC_ALIAS(pthread_key_delete, libc_pthread_key_delete);
DEFINE_PUBLIC_ALIAS(tss_get, libc_pthread_getspecific);
DEFINE_PUBLIC_ALIAS(pthread_getspecific, libc_pthread_getspecific);
DEFINE_PUBLIC_ALIAS(thr_setspecific, libc_pthread_setspecific);
DEFINE_PUBLIC_ALIAS(pthread_setspecific, libc_pthread_setspecific);
DEFINE_PUBLIC_ALIAS(pthread_getspecificptr_np, libc_pthread_getspecificptr_np);
DEFINE_PUBLIC_ALIAS(pthread_getcpuclockid, libc_pthread_getcpuclockid);
DEFINE_PUBLIC_ALIAS(pthread_atfork, libc_pthread_atfork);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PTHREAD_C */
