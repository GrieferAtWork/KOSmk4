/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_PTHREAD_C
#define GUARD_LIBC_USER_PTHREAD_C 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>
#include <hybrid/byteorder.h>
#include <hybrid/host.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/anno.h>
#include <kos/except.h>
#include <kos/futex.h>
#include <kos/syscalls.h>
#include <kos/thread.h>
#include <kos/types.h>
#include <linux/futex.h>
#include <sys/mman.h>
#include <sys/resource.h>

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <malloc.h>
#include <sched.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

#include <librpc/rpc.h>

#include "../libc/dl.h"
#include "../libc/tls.h"
#include "pthread.h"
#include "sched.h"

DECL_BEGIN

/* Verify that pthread offset constants are correct */
STATIC_ASSERT(offsetof(struct pthread, pt_tid) == __OFFSET_PTHREAD_TID);
STATIC_ASSERT(offsetof(struct pthread, pt_refcnt) == __OFFSET_PTHREAD_REFCNT);
STATIC_ASSERT(offsetof(struct pthread, pt_retval) == __OFFSET_PTHREAD_RETVAL);
STATIC_ASSERT(offsetof(struct pthread, pt_tls) == __OFFSET_PTHREAD_TLS);
STATIC_ASSERT(offsetof(struct pthread, pt_stackaddr) == __OFFSET_PTHREAD_STACKADDR);
STATIC_ASSERT(offsetof(struct pthread, pt_stacksize) == __OFFSET_PTHREAD_STACKSIZE);
STATIC_ASSERT(offsetof(struct pthread, pt_flags) == __OFFSET_PTHREAD_FLAGS);

/* pthread_attr_t */
STATIC_ASSERT(sizeof(pthread_attr_t) <= __SIZEOF_PTHREAD_ATTR_T);
STATIC_ASSERT(offsetof(pthread_attr_t, pa_schedparam) == __OFFSET_PTHREAD_ATTR_SCHEDPARAM);
STATIC_ASSERT(offsetof(pthread_attr_t, pa_schedpolicy) == __OFFSET_PTHREAD_ATTR_SCHEDPOLICY);
STATIC_ASSERT(offsetof(pthread_attr_t, pa_flags) == __OFFSET_PTHREAD_ATTR_FLAGS);
STATIC_ASSERT(offsetof(pthread_attr_t, pa_guardsize) == __OFFSET_PTHREAD_ATTR_GUARDSIZE);
STATIC_ASSERT(offsetof(pthread_attr_t, pa_stackaddr) == __OFFSET_PTHREAD_ATTR_STACKADDR);
STATIC_ASSERT(offsetof(pthread_attr_t, pa_stacksize) == __OFFSET_PTHREAD_ATTR_STACKSIZE);
STATIC_ASSERT(offsetof(pthread_attr_t, pa_cpuset) == __OFFSET_PTHREAD_ATTR_CPUSET);
STATIC_ASSERT(offsetof(pthread_attr_t, pa_cpusetsize) == __OFFSET_PTHREAD_ATTR_CPUSETSIZE);

/* pthread_mutexattr_t */
STATIC_ASSERT(sizeof(pthread_mutexattr_t) <= __SIZEOF_PTHREAD_MUTEXATTR_T);
STATIC_ASSERT(offsetof(pthread_mutexattr_t, ma_kind) == __OFFSET_PTHREAD_MUTEXATTR_KIND);

/* pthread_mutex_t */
STATIC_ASSERT(sizeof(pthread_mutex_t) <= __SIZEOF_PTHREAD_MUTEX_T);
STATIC_ASSERT(offsetof(pthread_mutex_t, m_lock) == __OFFSET_PTHREAD_MUTEX_LOCK);
STATIC_ASSERT(offsetof(pthread_mutex_t, m_count) == __OFFSET_PTHREAD_MUTEX_COUNT);
STATIC_ASSERT(offsetof(pthread_mutex_t, _m_owner) == __OFFSET_PTHREAD_MUTEX_OWNER);
STATIC_ASSERT(offsetof(pthread_mutex_t, m_kind) == __OFFSET_PTHREAD_MUTEX_KIND);
STATIC_ASSERT(offsetof(pthread_mutex_t, _m_nusers) == __OFFSET_PTHREAD_MUTEX_NUSERS);
STATIC_ASSERT(offsetof(pthread_mutex_t, _m_spins) == __OFFSET_PTHREAD_MUTEX_SPINS);
STATIC_ASSERT(offsetof(pthread_mutex_t, _m_elision) == __OFFSET_PTHREAD_MUTEX_ELISION);
STATIC_ASSERT(offsetof(pthread_mutex_t, _m_list) == __OFFSET_PTHREAD_MUTEX_LIST);
STATIC_ASSERT(offsetof(pthread_mutex_t, _m_list._l_next) == __OFFSET_PTHREAD_MUTEX_LIST_NEXT);
#ifdef __OFFSET_PTHREAD_MUTEX_LIST_PREV
STATIC_ASSERT(offsetof(pthread_mutex_t, _m_list._l_prev) == __OFFSET_PTHREAD_MUTEX_LIST_PREV);
#endif /* !__OFFSET_PTHREAD_MUTEX_LIST_PREV */

/* pthread_condattr_t */
STATIC_ASSERT(sizeof(pthread_condattr_t) <= __SIZEOF_PTHREAD_CONDATTR_T);
STATIC_ASSERT(offsetof(pthread_condattr_t, ca_value) == __OFFSET_PTHREAD_CONDATTR_VALUE);

/* pthread_cond_t */
STATIC_ASSERT(sizeof(pthread_cond_t) <= __SIZEOF_PTHREAD_COND_T);
STATIC_ASSERT(offsetof(pthread_cond_t, _c_lock) == __OFFSET_PTHREAD_COND_LOCK);
STATIC_ASSERT(offsetof(pthread_cond_t, c_futex) == __OFFSET_PTHREAD_COND_FUTEX);
STATIC_ASSERT(offsetof(pthread_cond_t, _c_total_seq) == __OFFSET_PTHREAD_COND_TOTAL_SEQ);
STATIC_ASSERT(offsetof(pthread_cond_t, _c_wakeup_seq) == __OFFSET_PTHREAD_COND_WAKEUP_SEQ);
STATIC_ASSERT(offsetof(pthread_cond_t, _c_woken_seq) == __OFFSET_PTHREAD_COND_WOKEN_SEQ);
STATIC_ASSERT(offsetof(pthread_cond_t, _c_mutex) == __OFFSET_PTHREAD_COND_MUTEX);
STATIC_ASSERT(offsetof(pthread_cond_t, _c_nwaiters) == __OFFSET_PTHREAD_COND_NWAITERS);
STATIC_ASSERT(offsetof(pthread_cond_t, _c_broadcast_seq) == __OFFSET_PTHREAD_COND_BROADCAST_SEQ);

/* pthread_rwlockattr_t */
STATIC_ASSERT(sizeof(pthread_rwlockattr_t) <= __SIZEOF_PTHREAD_RWLOCKATTR_T);
STATIC_ASSERT(offsetof(pthread_rwlockattr_t, rwa_kind) == __OFFSET_PTHREAD_RWLOCKATTR_KIND);
STATIC_ASSERT(offsetof(pthread_rwlockattr_t, rwa_shared) == __OFFSET_PTHREAD_RWLOCKATTR_SHARED);

/* pthread_rwlock_t */
STATIC_ASSERT(sizeof(pthread_rwlock_t) <= __SIZEOF_PTHREAD_RWLOCK_T);
STATIC_ASSERT(offsetof(pthread_rwlock_t, rw_lock) == __OFFSET_PTHREAD_RWLOCK_LOCK);
STATIC_ASSERT(offsetof(pthread_rwlock_t, _rw_nr_readers) == __OFFSET_PTHREAD_RWLOCK_NR_READERS);
STATIC_ASSERT(offsetof(pthread_rwlock_t, _rw_readers_wakeup) == __OFFSET_PTHREAD_RWLOCK_READERS_WAKEUP);
STATIC_ASSERT(offsetof(pthread_rwlock_t, _rw_writer_wakeup) == __OFFSET_PTHREAD_RWLOCK_WRITER_WAKEUP);
STATIC_ASSERT(offsetof(pthread_rwlock_t, _rw_nr_readers_queued) == __OFFSET_PTHREAD_RWLOCK_NR_READERS_QUEUED);
STATIC_ASSERT(offsetof(pthread_rwlock_t, _rw_nr_writers_queued) == __OFFSET_PTHREAD_RWLOCK_NR_WRITERS_QUEUED);
STATIC_ASSERT(offsetof(pthread_rwlock_t, rw_flags) == __OFFSET_PTHREAD_RWLOCK_FLAGS);
STATIC_ASSERT(offsetof(pthread_rwlock_t, _rw_shared) == __OFFSET_PTHREAD_RWLOCK_SHARED);
STATIC_ASSERT(offsetof(pthread_rwlock_t, _rw_rwelision) == __OFFSET_PTHREAD_RWLOCK_RWELISION);
STATIC_ASSERT(offsetof(pthread_rwlock_t, rw_writer) == __OFFSET_PTHREAD_RWLOCK_WRITER);

/* pthread_spinlock_t */
STATIC_ASSERT(sizeof(pthread_spinlock_t) <= __SIZEOF_PTHREAD_SPINLOCK_T);

/* pthread_barrierattr_t */
STATIC_ASSERT(sizeof(pthread_barrierattr_t) <= __SIZEOF_PTHREAD_BARRIERATTR_T);
STATIC_ASSERT(offsetof(pthread_barrierattr_t, ba_pshared) == __OFFSET_PTHREAD_BARRIERATTR_PSHARED);

/* pthread_barrier_t */
STATIC_ASSERT(sizeof(pthread_barrier_t) <= __SIZEOF_PTHREAD_BARRIER_T);
STATIC_ASSERT(offsetof(pthread_barrier_t, b_in) == __OFFSET_PTHREAD_BARRIER_IN);
STATIC_ASSERT(offsetof(pthread_barrier_t, b_current_round) == __OFFSET_PTHREAD_BARRIER_CURRENT_ROUND);
STATIC_ASSERT(offsetof(pthread_barrier_t, b_count) == __OFFSET_PTHREAD_BARRIER_COUNT);
STATIC_ASSERT(offsetof(pthread_barrier_t, b_shared) == __OFFSET_PTHREAD_BARRIER_SHARED);
STATIC_ASSERT(offsetof(pthread_barrier_t, b_out) == __OFFSET_PTHREAD_BARRIER_OUT);




PRIVATE ATTR_SECTION(".rodata.crt.sched.pthread.rpc.libname") char const librpc_name[] = LIBRPC_LIBRARY_NAME;
PRIVATE ATTR_SECTION(".bss.crt.sched.pthread.rpc.librpc") void *librpc = NULL;
PRIVATE ATTR_SECTION(".bss.crt.sched.pthread.rpc.rpc_schedule") PRPC_SCHEDULE pdyn_rpc_schedule = NULL;
PRIVATE ATTR_SECTION(".bss.crt.sched.pthread.rpc.rpc_service") PRPC_SERVICE pdyn_rpc_service = NULL;
PRIVATE ATTR_SECTION(".rodata.crt.sched.pthread.rpc.name_rpc_schedule") char const name_rpc_schedule[] = "rpc_schedule";
PRIVATE ATTR_SECTION(".rodata.crt.sched.pthread.rpc.name_rpc_service") char const name_rpc_service[] = "rpc_service";

PRIVATE ATTR_SECTION(".text.crt.sched.pthread.rpc.librpc_init")
WUNUSED bool LIBCCALL librpc_init(void) {
	void *lib;
again:
	lib = ATOMIC_READ(librpc);
	if (lib)
		return lib != (void *)-1;
	lib = dlopen(librpc_name, RTLD_LOCAL);
	if (!lib)
		goto err_nolib;
	*(void **)&pdyn_rpc_schedule = dlsym(lib, name_rpc_schedule);
	if unlikely(!pdyn_rpc_schedule)
		goto err;
	*(void **)&pdyn_rpc_service = dlsym(lib, name_rpc_service);
	if unlikely(!pdyn_rpc_service)
		goto err;
	if (!ATOMIC_CMPXCH(librpc, NULL, lib)) {
		dlclose(lib);
		goto again;
	}
	return true;
err:
	dlclose(lib);
err_nolib:
	if (!ATOMIC_CMPXCH(librpc, NULL, (void *)-1))
		goto again;
	return false;
}





/* Destroy a given `pthread' `self' */
LOCAL NONNULL((1)) void
NOTHROW(LIBCCALL destroy)(struct pthread *__restrict self) {
	free(self);
}


/* Attributes used by `pthread_create()' when the given `ATTR' is NULL
 * NOTE: When `pa_stacksize' is zero, `PTHREAD_STACK_MIN' will be used instead! */
ATTR_SECTION(".bss.crt.sched.pthread.pthread_default_attr.attr")
PRIVATE pthread_attr_t pthread_default_attr = {};
ATTR_SECTION(".bss.crt.sched.pthread.pthread_default_attr.lock")
PRIVATE DEFINE_ATOMIC_RWLOCK(pthread_default_attr_lock);



/* Called just before a thread exists (used to destroy() the thread's
 * `pthread_self' structure in case the thread was detached) */
INTERN ATTR_SECTION(".text.crt.sched.pthread.pthread_onexit") void
NOTHROW(LIBCCALL libc_pthread_onexit)(struct pthread *__restrict me) {
	void *tls;
	tls = me->pt_tls;
	if (ATOMIC_FETCHDEC(me->pt_refcnt) == 1) {
		/* At some point, our thread got detached from its creator,
		 * so it is left up to us to destroy() our own descriptor.
		 * Because of this, we must prevent the kernel from attempting
		 * to write into our TID address field (since we're freeing
		 * the associated structure right now). */
		sys_set_tid_address(NULL);
		destroy(me);
	}
	/* Free our thread's TLS segment. */
	dltlsfreeseg(tls);
}

INTDEF ATTR_NORETURN void __FCALL
libc_pthread_unmap_stack_and_exit(void *stackaddr,
                                  size_t stacksize,
                                  int exitcode);

/* Perform cleanup & terminate the current thread `me'. */
INTERN ATTR_NORETURN ATTR_SECTION(".text.crt.sched.pthread.pthread_exit_thread") void
NOTHROW(__FCALL pthread_exit_thread)(struct pthread *__restrict me, int exitcode) {
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

INTERN ATTR_NORETURN ATTR_SECTION(".text.crt.sched.pthread.pthread_main") void
NOTHROW(__FCALL libc_pthread_main)(struct pthread *__restrict me,
                                   __pthread_start_routine_t start) {
	int exitcode = 0;
	/* Set the TLS variable for `pthread_self' to `me' */
	tls.t_pthread = me;
	COMPILER_BARRIER();
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
	COMPILER_BARRIER();
	TRY {
		/* Invoke the thread-main function. */
		me->pt_retval = (*start)(me->pt_retval);
	} EXCEPT {
		/* Always invoke the on-exit callback, no matter what happens! */
		if (!was_thrown(E_EXIT_THREAD)) {
			/* Anything else can just be propagated directly,
			 * since it's considered an unhandled exception that
			 * will cause the process to terminate.
			 * However, E_EXIT_THREAD must be handled explicitly
			 * in case we have to unmap our own stack. */
			RETHROW();
		}
		exitcode = error_data()->e_args.e_exit_thread.et_exit_code;
		me->pt_retval = NULL;
	}
	/* Perform cleanup & terminate the current thread. */
	pthread_exit_thread(me, exitcode);
}

/* Assembly-side for the process of cloning a thread.
 * This function simply clones the calling thread before invoking
 * `libc_pthread_main()' within the context of the newly spawned thread.
 * NOTE: This function also fills in `thread->pt_tid' */
INTDEF pid_t NOTHROW(__FCALL libc_pthread_clone)(struct pthread *__restrict thread,
                                                 __pthread_start_routine_t start);


PRIVATE NONNULL((1, 2, 3))
ATTR_SECTION(".text.crt.sched.pthread.pthread_dp_create") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_do_create)(pthread_t *__restrict newthread,
                                             pthread_attr_t const *__restrict attr,
                                             __pthread_start_routine_t start_routine,
                                             void *__restrict arg) {
	pid_t cpid;
	struct pthread *pt;
	pt = (struct pthread *)malloc(sizeof(struct pthread));
	if unlikely(!pt)
		goto err_nomem;
	/* Allocate the DL TLS segment */
	pt->pt_tls = dltlsallocseg();
	if unlikely(!pt->pt_tls)
		goto err_nomem_pt;
	pt->pt_refcnt    = 2;
	pt->pt_flags     = PTHREAD_FNORMAL;
	pt->pt_stackaddr = attr->pa_stackaddr;
	pt->pt_stacksize = attr->pa_stacksize;
	pt->pt_cpuset    = NULL;
	/* Copy affinity cpuset information. */
	if (attr->pa_cpuset) {
		pt->pt_cpusetsize = attr->pa_cpusetsize;
		if (attr->pa_cpuset == (cpu_set_t *)&attr->pa_cpusetsize) {
			pt->pt_cpuset = (cpu_set_t *)&pt->pt_cpusetsize;
		} else {
			pt->pt_cpuset = (cpu_set_t *)malloc(pt->pt_cpusetsize);
			if unlikely(!pt->pt_cpuset)
				goto err_nomem_pt_tls;
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
			goto err_nomem_pt_tls_cpuset;
	} else {
		/* The thread uses a custom, user-provided stack. */
		pt->pt_flags |= PTHREAD_FUSERSTACK;
	}
	pt->pt_retval = arg;
	cpid = libc_pthread_clone(pt, start_routine);
	if unlikely(E_ISERR(cpid)) {
		/* The clone() system call failed. */
		dltlsfreeseg(pt->pt_tls);
		if (pt->pt_cpuset != (cpu_set_t *)&pt->pt_cpusetsize)
			free(pt->pt_cpuset);
		free(pt);
		return (errno_t)-cpid;
	}
	*newthread = pt;
	return EOK;
err_nomem_pt_tls_cpuset:
	if (pt->pt_cpuset != (cpu_set_t *)&pt->pt_cpusetsize)
		free(pt->pt_cpuset);
err_nomem_pt_tls:
	dltlsfreeseg(pt->pt_tls);
err_nomem_pt:
	free(pt);
err_nomem:
	return ENOMEM;
}

/*[[[start:implementation]]]*/

/*[[[head:libc_pthread_create,hash:CRC-32=0x886e989b]]]*/
/* Create a new thread, starting with execution of START-ROUTINE
 * getting passed ARG. Creation attributed come from ATTR. The new
 * handle is stored in *NEWTHREAD
 * @return: EOK:    Success
 * @return: EAGAIN: Insufficient resources, or operation-not-permitted */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_create)(pthread_t *__restrict newthread,
                                          pthread_attr_t const *__restrict attr,
                                          __pthread_start_routine_t start_routine,
                                          void *__restrict arg)
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

/*[[[head:libc_pthread_exit,hash:CRC-32=0x67ca671f]]]*/
/* Terminate calling thread.
 * The registered cleanup handlers are called via exception handling */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_NORETURN void
(LIBCCALL libc_pthread_exit)(void *retval) THROWS(...)
/*[[[body:libc_pthread_exit]]]*/
{
	__REF struct pthread *me = tls.t_pthread;
	if (me) {
		me->pt_retval = retval;
		/* Perform cleanup & terminate the current thread. */
		pthread_exit_thread(me, 0);
		__builtin_unreachable();
	}
	/* XXX: THROW(E_EXIT_THREAD)? */
	/* Reminder: `sys_exit()' only terminates the calling thread.
	 * To terminate the calling process, you'd have to call `sys_exit_group()'! */
	sys_exit(0);
}
/*[[[end:libc_pthread_exit]]]*/

/*[[[head:libc_pthread_join,hash:CRC-32=0x1f8032e3]]]*/
/* Make calling thread wait for termination of the thread THREAD. The
 * exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
 * is not NULL
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
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

/*[[[head:libc_pthread_tryjoin_np,hash:CRC-32=0xb01fbcda]]]*/
/* Check whether thread THREAD has terminated. If yes return the status of
 * the thread in *THREAD_RETURN, if THREAD_RETURN is not NULL
 * @return: EOK:   Success
 * @return: EBUSY: The thread has yet to terminate */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_tryjoin_np)(pthread_t pthread,
                                              void **thread_return)
/*[[[body:libc_pthread_tryjoin_np]]]*/
{
	if (ATOMIC_READ(pthread->pt_tid) == 0) {
		if (thread_return)
			*thread_return = pthread->pt_retval;
		if (ATOMIC_FETCHDEC(pthread->pt_refcnt) == 1)
			destroy(pthread);
		return EOK;
	}
	if unlikely(pthread == tls.t_pthread)
		return EDEADLK;
	return EBUSY;
}
/*[[[end:libc_pthread_tryjoin_np]]]*/

/*[[[head:libc_pthread_timedjoin_np,hash:CRC-32=0x7c33eeaa]]]*/
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
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
		if unlikely(pthread == tls.t_pthread)
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
	if (ATOMIC_FETCHDEC(pthread->pt_refcnt) == 1)
		destroy(pthread);
	return EOK;
}
/*[[[end:libc_pthread_timedjoin_np]]]*/

/*[[[head:libc_pthread_timedjoin64_np,hash:CRC-32=0xf705e381]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_timedjoin64_np, libc_pthread_timedjoin_np);
#else /* MAGIC:alias */
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL.
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
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
		if unlikely(pthread == tls.t_pthread)
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
	if (ATOMIC_FETCHDEC(pthread->pt_refcnt) == 1)
		destroy(pthread);
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

/*[[[head:libc_pthread_detach,hash:CRC-32=0xf62b3010]]]*/
/* Indicate that the thread THREAD is never to be joined with PTHREAD_JOIN.
 * The resources of THREAD will therefore be freed immediately when it
 * terminates, instead of waiting for another thread to perform PTHREAD_JOIN on it
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
			 * In this case, the thread will have already invoked `libc_pthread_onexit()',
			 * however did not destroy() its own structure, or deleted its kernel tid-address.
			 * There is a chance that the thread is still running, and that the kernel is
			 * still going to write 0 to the TID address.
			 * In this case, we must wait for it to do so, since we mustn't destroy()
			 * the pthread structure before then, else the kernel might possibly write
			 * to free'd memory. */
			if (ATOMIC_READ(pthread->pt_tid) != 0) {
				sys_sched_yield();
				continue;
			}
			/* The TID field was already set to ZERO. -> Set the reference
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

/*[[[head:libc_pthread_self,hash:CRC-32=0xe9554f99]]]*/
/* Obtain the identifier of the current thread
 * @return: * : Handle for the calling thread */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_CONST pthread_t
NOTHROW_NCX(LIBCCALL libc_pthread_self)(void)
/*[[[body:libc_pthread_self]]]*/
{
	struct pthread *result;
	result = tls.t_pthread;
	if unlikely(!result) {
		result = (struct pthread *)malloc(sizeof(struct pthread));
		if unlikely(!result) {
			PRIVATE ATTR_SECTION(".rodata.crt.sched.pthread.pthread_self_error_message") char const
				message[] = "[libc] Failed to allocate descriptor for pthread_self()\n";
			syslog(LOG_ERR, message);
			exit(EXIT_FAILURE);
		}
		result->pt_tid       = sys_set_tid_address(&result->pt_tid);
		result->pt_refcnt    = 1;
		result->pt_retval    = NULL;
		result->pt_tls       = RD_TLS_BASE_REGISTER();
		result->pt_stackaddr = NULL;
		result->pt_stacksize = 0;
		result->pt_flags     = PTHREAD_FNOSTACK;
		COMPILER_WRITE_BARRIER();
		tls.t_pthread = result;
	}
	return result;
}
/*[[[end:libc_pthread_self]]]*/

/*[[[head:libc_pthread_gettid_np,hash:CRC-32=0xa88f585e]]]*/
/* Return the TID of the given `target_thread'.
 * If the given `target_thread' has already terminated, 0 is returned
 * @return: * : The PID OF the given thread
 * @return: 0 : The given `target_thread' has already terminated */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_CONST WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_pthread_gettid_np)(pthread_t target_thread)
/*[[[body:libc_pthread_gettid_np]]]*/
{
	pid_t result;
	result = target_thread->pt_tid;
	return result;
}
/*[[[end:libc_pthread_gettid_np]]]*/

/*[[[head:libc_pthread_attr_init,hash:CRC-32=0xd794b805]]]*/
/* Initialize thread attribute *ATTR with default attributes (detachstate is
 * PTHREAD_JOINABLE, scheduling policy is SCHED_OTHER, no user-provided stack)
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_init)(pthread_attr_t *attr)
/*[[[body:libc_pthread_attr_init]]]*/
{
	memset(attr, 0, sizeof(*attr));
	attr->pa_guardsize = getpagesize();
	return EOK;
}
/*[[[end:libc_pthread_attr_init]]]*/

/*[[[head:libc_pthread_attr_destroy,hash:CRC-32=0x99e913e0]]]*/
/* Destroy thread attribute *ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_attr_getdetachstate,hash:CRC-32=0xca10d935]]]*/
/* Get detach state attribute
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getdetachstate)(pthread_attr_t const *attr,
                                                       int *detachstate)
/*[[[body:libc_pthread_attr_getdetachstate]]]*/
{
	*detachstate = (attr->pa_flags & PTHREAD_ATTR_FLAG_DETACHSTATE
	                ? PTHREAD_CREATE_DETACHED
	                : PTHREAD_CREATE_JOINABLE);
	return EOK;
}
/*[[[end:libc_pthread_attr_getdetachstate]]]*/

/*[[[head:libc_pthread_attr_setdetachstate,hash:CRC-32=0x476bf355]]]*/
/* Set detach state attribute
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `detachstate' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setdetachstate)(pthread_attr_t *attr,
                                                       int detachstate)
/*[[[body:libc_pthread_attr_setdetachstate]]]*/
{
	if (detachstate == PTHREAD_CREATE_DETACHED)
		attr->pa_flags |= PTHREAD_ATTR_FLAG_DETACHSTATE;
	else if (detachstate == PTHREAD_CREATE_JOINABLE)
		attr->pa_flags &= ~PTHREAD_ATTR_FLAG_DETACHSTATE;
	else {
		return EINVAL;
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_setdetachstate]]]*/

/*[[[head:libc_pthread_attr_getguardsize,hash:CRC-32=0xf0ecd20a]]]*/
/* Get the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getguardsize)(pthread_attr_t const *attr,
                                                     size_t *guardsize)
/*[[[body:libc_pthread_attr_getguardsize]]]*/
{
	*guardsize = attr->pa_guardsize;
	return EOK;
}
/*[[[end:libc_pthread_attr_getguardsize]]]*/

/*[[[head:libc_pthread_attr_setguardsize,hash:CRC-32=0x35db3f77]]]*/
/* Set the size of the guard area created for stack overflow protection
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setguardsize)(pthread_attr_t *attr,
                                                     size_t guardsize)
/*[[[body:libc_pthread_attr_setguardsize]]]*/
{
	attr->pa_guardsize = guardsize;
	return EOK;
}
/*[[[end:libc_pthread_attr_setguardsize]]]*/

/*[[[head:libc_pthread_attr_getschedparam,hash:CRC-32=0x8031e695]]]*/
/* Return in *PARAM the scheduling parameters of *ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getschedparam)(pthread_attr_t const *__restrict attr,
                                                      struct sched_param *__restrict param)
/*[[[body:libc_pthread_attr_getschedparam]]]*/
{
	memcpy(param, &attr->pa_schedparam, sizeof(struct sched_param));
	return EOK;
}
/*[[[end:libc_pthread_attr_getschedparam]]]*/

/*[[[head:libc_pthread_attr_setschedparam,hash:CRC-32=0xbf681157]]]*/
/* Set scheduling parameters (priority, etc) in *ATTR according to PARAM
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `param' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setschedparam)(pthread_attr_t *__restrict attr,
                                                      struct sched_param const *__restrict param)
/*[[[body:libc_pthread_attr_setschedparam]]]*/
{
	memcpy(&attr->pa_schedparam, param, sizeof(struct sched_param));
	return EOK;
}
/*[[[end:libc_pthread_attr_setschedparam]]]*/

/*[[[head:libc_pthread_attr_getschedpolicy,hash:CRC-32=0xd56c37b]]]*/
/* Return in *POLICY the scheduling policy of *ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getschedpolicy)(pthread_attr_t const *__restrict attr,
                                                       int *__restrict policy)
/*[[[body:libc_pthread_attr_getschedpolicy]]]*/
{
	*policy = attr->pa_schedpolicy;
	return EOK;
}
/*[[[end:libc_pthread_attr_getschedpolicy]]]*/

/*[[[head:libc_pthread_attr_setschedpolicy,hash:CRC-32=0x7039c2b9]]]*/
/* Set scheduling policy in *ATTR according to POLICY
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `policy' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_attr_getinheritsched,hash:CRC-32=0xa4192b9e]]]*/
/* Return in *INHERIT the scheduling inheritance mode of *ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
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

/*[[[head:libc_pthread_attr_setinheritsched,hash:CRC-32=0x92ac8266]]]*/
/* Set scheduling inheritance mode in *ATTR according to INHERIT
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `inherit' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setinheritsched)(pthread_attr_t *attr,
                                                        int inherit)
/*[[[body:libc_pthread_attr_setinheritsched]]]*/
{
	if (inherit == PTHREAD_EXPLICIT_SCHED)
		attr->pa_flags |= PTHREAD_ATTR_FLAG_NOTINHERITSCHED;
	else if (inherit == PTHREAD_INHERIT_SCHED)
		attr->pa_flags &= ~PTHREAD_ATTR_FLAG_NOTINHERITSCHED;
	else {
		return EINVAL;
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_setinheritsched]]]*/

/*[[[head:libc_pthread_attr_getscope,hash:CRC-32=0x921ad3f2]]]*/
/* Return in *SCOPE the scheduling contention scope of *ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
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

/*[[[head:libc_pthread_attr_setscope,hash:CRC-32=0x153a502a]]]*/
/* Set scheduling contention scope in *ATTR according to SCOPE
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `scope' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setscope)(pthread_attr_t *attr,
                                                 int scope)
/*[[[body:libc_pthread_attr_setscope]]]*/
{
	if (scope == PTHREAD_SCOPE_PROCESS)
		attr->pa_flags |= PTHREAD_ATTR_FLAG_SCOPEPROCESS;
	else if (scope == PTHREAD_SCOPE_SYSTEM)
		attr->pa_flags &= ~PTHREAD_ATTR_FLAG_SCOPEPROCESS;
	else {
		return EINVAL;
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_setscope]]]*/

/*[[[head:libc_pthread_attr_getstackaddr,hash:CRC-32=0x2971432d]]]*/
/* Return the previously set address for the stack
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_DEPRECATED("Use pthread_attr_getstack()") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstackaddr)(pthread_attr_t const *__restrict attr,
                                                     void **__restrict stackaddr)
/*[[[body:libc_pthread_attr_getstackaddr]]]*/
{
	*stackaddr = attr->pa_stackaddr;
	return EOK;
}
/*[[[end:libc_pthread_attr_getstackaddr]]]*/

/*[[[head:libc_pthread_attr_setstackaddr,hash:CRC-32=0x50aeef59]]]*/
/* Set the starting address of the stack of the thread to be created.
 * Depending on whether the stack grows up or down the value must either
 * be higher or lower than all the address in the memory block. The
 * minimal size of the block must be PTHREAD_STACK_MIN
 * @return: EOK:    Success
 * @return: EINVAL: The stack isn't suitably aligned */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_DEPRECATED("Use pthread_attr_setstack()") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setstackaddr)(pthread_attr_t *attr,
                                                     void *stackaddr)
/*[[[body:libc_pthread_attr_setstackaddr]]]*/
{
	attr->pa_stackaddr = stackaddr;
	attr->pa_flags |= PTHREAD_ATTR_FLAG_STACKADDR;
	return EOK;
}
/*[[[end:libc_pthread_attr_setstackaddr]]]*/

/*[[[head:libc_pthread_attr_getstacksize,hash:CRC-32=0x571f7a3b]]]*/
/* Return the currently used minimal stack size
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstacksize)(pthread_attr_t const *__restrict attr,
                                                     size_t *__restrict stacksize)
/*[[[body:libc_pthread_attr_getstacksize]]]*/
{
	*stacksize = attr->pa_stacksize;
	return EOK;
}
/*[[[end:libc_pthread_attr_getstacksize]]]*/

/*[[[head:libc_pthread_attr_setstacksize,hash:CRC-32=0x44b6e383]]]*/
/* Add information about the minimum stack size needed for the thread
 * to be started. This size must never be less than PTHREAD_STACK_MIN
 * and must also not exceed the system limits
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_attr_getstack,hash:CRC-32=0x9fe6b598]]]*/
/* Return the previously set address for the stack
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2, 3)) errno_t
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

/*[[[head:libc_pthread_attr_setstack,hash:CRC-32=0x2170195e]]]*/
/* The following two interfaces are intended to replace the last two. They
 * require setting the address as well as the size since only setting the
 * address will make the implementation on some architectures impossible
 * @return: EOK:    Success
 * @return: EINVAL: `stacksize' is too small, or the stack isn't suitably aligned */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_attr_setaffinity_np,hash:CRC-32=0x25665b0d]]]*/
/* Thread created with attribute ATTR will be limited to run only on
 * the processors represented in CPUSET
 * @return: EOK:    Success
 * @return: EINVAL: The given set contains a non-existant CPU
 * @return: ENOMEM: Insufficient memory */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setaffinity_np)(pthread_attr_t *attr,
                                                       size_t cpusetsize,
                                                       cpu_set_t const *cpuset)
/*[[[body:libc_pthread_attr_setaffinity_np]]]*/
{
	/* Truncate the cpu set */
	while (cpusetsize && ((byte_t *)cpuset)[cpusetsize - 1] == 0)
		--cpusetsize;
	if (!cpusetsize || !cpuset) {
		/* NOTE: Glibc also accepts a zero-value in either argument as indicator
		 *       to clear out a previously set affinity, even though it would make
		 *       more sense to only allow `cpusetsize == 0', and require a non-NULL
		 *       `cpuset' when `cpusetsize != 0'... */
		if (attr->pa_cpuset != (cpu_set_t *)&attr->pa_cpusetsize)
			free(attr->pa_cpuset);
		attr->pa_cpuset     = NULL;
		attr->pa_cpusetsize = 0;
	} else if (cpusetsize <= sizeof(attr->pa_cpusetsize)) {
		/* Optimization: Don't use the heap for small cpu sets.
		 * In practice, this means that we usually always get here,
		 * since most machines don't have more than 32 cpus... */
		if (attr->pa_cpuset != (cpu_set_t *)&attr->pa_cpusetsize) {
			free(attr->pa_cpuset);
			attr->pa_cpuset = (cpu_set_t *)&attr->pa_cpusetsize;
		}
		memset(&attr->pa_cpusetsize, 0, sizeof(attr->pa_cpusetsize));
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

/*[[[head:libc_pthread_attr_getaffinity_np,hash:CRC-32=0xcccd264f]]]*/
/* Get bit set in CPUSET representing the processors threads created with ATTR can run on
 * @return: EOK:    Success
 * @return: EINVAL: `cpusetsize' is too small */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 3)) errno_t
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
			return EINVAL; /* GLibc returns EINVAL here (I would have used ERANGE for this, but whatever...) */
		p = (byte_t *)mempcpy(cpuset, attr->pa_cpuset, setsize);
		/* Fill in the remainder with zeroes */
		memset(p, 0, cpusetsize - setsize);
	} else {
		/* No affinity set defined -> All cpus may be used. */
		memset(cpuset, 0xff, cpusetsize);
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_getaffinity_np]]]*/

/*[[[head:libc_pthread_getattr_default_np,hash:CRC-32=0xe8033152]]]*/
/* Get the default attributes used by pthread_create in this process
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getattr_default_np)(pthread_attr_t *attr)
/*[[[body:libc_pthread_getattr_default_np]]]*/
{
	cpu_set_t *cpuset = NULL;
	size_t cpuset_size = 0;
again:
	atomic_rwlock_read(&pthread_default_attr_lock);
	memcpy(attr, &pthread_default_attr, sizeof(pthread_attr_t));
	if (pthread_default_attr.pa_cpuset) {
		if (pthread_default_attr.pa_cpuset == (cpu_set_t *)&pthread_default_attr.pa_cpusetsize) {
			attr->pa_cpuset = (cpu_set_t *)&attr->pa_cpusetsize;
		} else if (cpuset_size != pthread_default_attr.pa_cpusetsize) {
			cpuset_size = pthread_default_attr.pa_cpusetsize;
			atomic_rwlock_endread(&pthread_default_attr_lock);
			cpuset = (cpu_set_t *)realloc(cpuset, cpuset_size);
			if unlikely(!cpuset)
				return ENOMEM;
			goto again;
		}
		attr->pa_cpuset     = cpuset;
		attr->pa_cpusetsize = cpuset_size;
		cpuset            = NULL; /* Don't free() below */
	}
	atomic_rwlock_endread(&pthread_default_attr_lock);
	if (attr->pa_stacksize == 0)
		attr->pa_stacksize = PTHREAD_STACK_MIN;
	free(cpuset);
	__STATIC_IF(sizeof(pthread_attr_t) > sizeof(pthread_attr_t)) {
		memset((byte_t *)attr + sizeof(pthread_attr_t), 0x00,
		       sizeof(pthread_attr_t) - sizeof(pthread_attr_t));
	}
	return EOK;
}
/*[[[end:libc_pthread_getattr_default_np]]]*/

/*[[[head:libc_pthread_setattr_default_np,hash:CRC-32=0x2519ccce]]]*/
/* Set the default attributes to be used by pthread_create in this process
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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
	atomic_rwlock_write(&pthread_default_attr_lock);
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
	atomic_rwlock_endwrite(&pthread_default_attr_lock);
	free(old_set);
	return EOK;
}
/*[[[end:libc_pthread_setattr_default_np]]]*/

/*[[[head:libc_pthread_getattr_np,hash:CRC-32=0xc33e8041]]]*/
/* Initialize thread attribute *ATTR with attributes corresponding to the
 * already running thread THREAD. It shall be called on uninitialized ATTR
 * and destroyed with pthread_attr_destroy when no longer needed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getattr_np)(pthread_t pthread,
                                              pthread_attr_t *attr)
/*[[[body:libc_pthread_getattr_np]]]*/
{
	errno_t result;
	result = pthread_getschedparam(pthread, &attr->pa_schedpolicy, &attr->pa_schedparam);
	if (result != EOK)
		goto done;
	if (pthread->pt_flags & PTHREAD_FNOSTACK) {
		attr->pa_stackaddr = NULL;
		attr->pa_stacksize = 0;
	} else {
		attr->pa_stackaddr = pthread->pt_stackaddr;
		attr->pa_stacksize = pthread->pt_stacksize;
	}
	attr->pa_guardsize = getpagesize();
	attr->pa_flags = PTHREAD_ATTR_FLAG_SCHED_SET | PTHREAD_ATTR_FLAG_POLICY_SET;
	if (pthread->pt_flags & PTHREAD_FUSERSTACK)
		attr->pa_flags |= PTHREAD_ATTR_FLAG_STACKADDR;
	attr->pa_cpuset = (cpu_set_t *)&attr->pa_cpusetsize;
	result = pthread_getaffinity_np(pthread,
	                                sizeof(attr->pa_cpusetsize),
	                                attr->pa_cpuset);
	if (result != ESRCH) {
		/* Buffer too small. */
		cpu_set_t *buf = NULL, *newbuf;
		size_t bufsize = sizeof(attr->pa_cpusetsize) * 2;
		do {
			newbuf = (cpu_set_t *)realloc(buf, bufsize);
			if unlikely(!newbuf) {
				free(buf);
				return ENOMEM;
			}
			buf = newbuf;
			result = pthread_getaffinity_np(pthread, bufsize, buf);
			if (result == EOK) {
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
			if (result != EINVAL)
				break;
			bufsize *= 2;
		} while (bufsize < sizeof(attr->pa_cpusetsize) * 512);
		free(buf);
	}
done:
	return result;
}
/*[[[end:libc_pthread_getattr_np]]]*/

/*[[[head:libc_pthread_setschedparam,hash:CRC-32=0xfbb3947a]]]*/
/* Set the scheduling parameters for TARGET_THREAD according to POLICY and *PARAM
 * @return: EOK:    Success
 * @return: EPERM:  The caller isn't allowed to specify `policy' and `param'
 * @return: ESRCH:  `pthread' has already exited
 * @return: EINVAL: Invalid/unsupported `policy', or `param' is malformed for `policy' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((3)) errno_t
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
		 * modified the scheduler parameters of some unrelated thread.
		 * Try to undo the damage we've caused...
		 * Note: This is a race condition that Glibc
		 *       doesn't even check and simply ignores! */
		sys_sched_setscheduler(tid, old_policy, &old_param);
		return ESRCH;
	}
	return EOK;
}
/*[[[end:libc_pthread_setschedparam]]]*/

/*[[[head:libc_pthread_getschedparam,hash:CRC-32=0x438c7fbe]]]*/
/* Return in *POLICY and *PARAM the scheduling parameters for TARGET_THREAD
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((2, 3)) errno_t
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
		 * Note: This is a race condition that Glibc
		 *       doesn't even check and simply ignores! */
		return ESRCH;
	}
	return EOK;
}
/*[[[end:libc_pthread_getschedparam]]]*/

/*[[[head:libc_pthread_setschedprio,hash:CRC-32=0x48fbb9a5]]]*/
/* Set the scheduling priority for TARGET_THREAD
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
		 * Note: This is a race condition that Glibc
		 *       doesn't even check and simply ignores! */
		sys_setpriority(PRIO_PROCESS, tid, old_prio);
		return ESRCH;
	}
	return EOK;
}
/*[[[end:libc_pthread_setschedprio]]]*/

/*[[[head:libc_pthread_getname_np,hash:CRC-32=0x3f2c67ed]]]*/
/* Get thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `buflen' is too small */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getname_np)(pthread_t target_thread,
                                              char *buf,
                                              size_t buflen)
/*[[[body:libc_pthread_getname_np]]]*/
{
	pid_t tid;
	tid = ATOMIC_READ(target_thread->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	if unlikely(snprintf(buf, buflen, "tid{%u}", tid) >= buflen)
		return ERANGE;
	if unlikely(ATOMIC_READ(target_thread->pt_tid) == 0)
		return ESRCH;
	return EOK;
}
/*[[[end:libc_pthread_getname_np]]]*/

/*[[[head:libc_pthread_setname_np,hash:CRC-32=0x9362205c]]]*/
/* Set thread name visible in the kernel and its interfaces
 * @return: EOK:    Success
 * @return: ERANGE: The given `name' is too long */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setname_np)(pthread_t target_thread,
                                              const char *name)
/*[[[body:libc_pthread_setname_np]]]*/
{
	pid_t tid;
	tid = ATOMIC_READ(target_thread->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	COMPILER_IMPURE();
	/* Unsupported */
	(void)name;
	return ENOSYS;
}
/*[[[end:libc_pthread_setname_np]]]*/

PRIVATE ATTR_SECTION(".bss.crt.sched.pthread.pthread_concurrency_level") int pthread_concurrency_level = 0;

/*[[[head:libc_pthread_getconcurrency,hash:CRC-32=0x365ea224]]]*/
/* Determine level of concurrency
 * @return: * : The current concurrency level */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_PURE int
NOTHROW_NCX(LIBCCALL libc_pthread_getconcurrency)(void)
/*[[[body:libc_pthread_getconcurrency]]]*/
{
	return pthread_concurrency_level;
}
/*[[[end:libc_pthread_getconcurrency]]]*/

/*[[[head:libc_pthread_setconcurrency,hash:CRC-32=0xa78306ff]]]*/
/* Set new concurrency level to LEVEL
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

/*[[[head:libc_pthread_setaffinity_np,hash:CRC-32=0x6596a5ca]]]*/
/* Limit specified thread THREAD to run only on the processors represented in CPUSET
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((3)) errno_t
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
			newbuf = (cpu_set_t *)realloc(buf, bufsize);
			if unlikely(!newbuf) {
				free(buf);
				return ENOMEM;
			}
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
			 * Note: This is a race condition that Glibc
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

/*[[[head:libc_pthread_getaffinity_np,hash:CRC-32=0xf48cf8d9]]]*/
/* Get bit set in CPUSET representing the processors THREAD can run on
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((3)) errno_t
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
			 * Note: This is a race condition that Glibc
			 *       doesn't even check and simply ignores! */
			error = -ESRCH;
		}
	}
	return (errno_t)-error;
}
/*[[[end:libc_pthread_getaffinity_np]]]*/


/*[[[head:libc_pthread_setcancelstate,hash:CRC-32=0x303704de]]]*/
/* Set cancelability state of current thread to STATE,
 * returning old state in *OLDSTATE if OLDSTATE is not NULL
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `state' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setcancelstate)(int state,
                                                  int *oldstate)
/*[[[body:libc_pthread_setcancelstate]]]*/
/*AUTO*/{
	(void)state;
	(void)oldstate;
	CRT_UNIMPLEMENTEDF("pthread_setcancelstate(%x, %p)", state, oldstate); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_setcancelstate]]]*/

/*[[[head:libc_pthread_setcanceltype,hash:CRC-32=0xeeeea29]]]*/
/* Set cancellation state of current thread to TYPE,
 * returning the old type in *OLDTYPE if OLDTYPE is not NULL
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `type' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setcanceltype)(int type,
                                                 int *oldtype)
/*[[[body:libc_pthread_setcanceltype]]]*/
/*AUTO*/{
	(void)type;
	(void)oldtype;
	CRT_UNIMPLEMENTEDF("pthread_setcanceltype(%x, %p)", type, oldtype); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_setcanceltype]]]*/

PRIVATE ATTR_SECTION(".text.crt.sched.pthread.pthread_cancel_self")
void LIBCCALL pthread_cancel_self(void) {
	THROW(E_EXIT_THREAD);
}

/*[[[head:libc_pthread_cancel,hash:CRC-32=0xcc2c978f]]]*/
/* Cancel THREAD immediately or at the next possibility
 * @return: EOK:   Success
 * @return: ESRCH: `pthread' has already exited */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cancel)(pthread_t pthread)
/*[[[body:libc_pthread_cancel]]]*/
{
	pid_t tid;
	/* Make sure that we can load librpc */
	if (!librpc_init())
		return ENOSYS;
	tid = ATOMIC_READ(pthread->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	/* Schedule an RPC in the target thread that will cause the thread to terminate itself. */
	/* In this case, we sadly cannot handle the race condition of `tid'
	 * terminating at this point (causing the id to become invalid), since
	 * we cannot undo the RPC schedule operation in that case...
	 * NOTE: This is _NOT_ unsafe, even when the target thread has already
	 *       unmapped its stack within `libc_pthread_unmap_stack_and_exit()'
	 *       The reason for this is the `RPC_SCHEDULE_SYNC' which only allows
	 *       the RPC to be executed as the result of a blocking operation,
	 *       none of which happen anymore once the stack has gone away in
	 *       said function! */
	if ((*pdyn_rpc_schedule)(tid, RPC_SCHEDULE_SYNC,
	                         (void (*)())&pthread_cancel_self,
	                         0) != 0)
		return libc_geterrno();
	return EOK;
}
/*[[[end:libc_pthread_cancel]]]*/

/*[[[head:libc_pthread_testcancel,hash:CRC-32=0x11233c93]]]*/
/* Test for pending cancellation for the current thread and terminate
 * the thread as per pthread_exit(PTHREAD_CANCELED) if it has been canceled */
INTERN ATTR_SECTION(".text.crt.sched.pthread") void
NOTHROW_RPC(LIBCCALL libc_pthread_testcancel)(void)
/*[[[body:libc_pthread_testcancel]]]*/
{
	/* Load librpc and use it to service RPCs
	 * Technically, we could just directly invoke `sys_rpc_service()', however
	 * this method allows librpc to perform additional functions, and also makes
	 * it more clear that it is actually librpc that implements this behavior! */
	if (librpc_init())
		(*pdyn_rpc_service)();
}
/*[[[end:libc_pthread_testcancel]]]*/

/*[[[head:libc_pthread_getcpuclockid,hash:CRC-32=0x6c87e8b7]]]*/
/* Get ID of CPU-time clock for thread THREAD_ID
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getcpuclockid)(pthread_t pthread_id,
                                                 clockid_t *clock_id)
/*[[[body:libc_pthread_getcpuclockid]]]*/
/*AUTO*/{
	(void)pthread_id;
	(void)clock_id;
	CRT_UNIMPLEMENTEDF("pthread_getcpuclockid(%" PRIxN(__SIZEOF_PTHREAD_T) ", %p)", pthread_id, clock_id); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_getcpuclockid]]]*/















/************************************************************************/
/* MISC PTHREAD FUNCTIONS                                               */
/************************************************************************/

/*[[[head:libc_pthread_atfork,hash:CRC-32=0x374aee67]]]*/
/* Install handlers to be called when a new process is created with FORK.
 * The PREPARE handler is called in the parent process just before performing
 * FORK. The PARENT handler is called in the parent process just after FORK.
 * The CHILD handler is called in the child process. Each of the three
 * handlers can be NULL, meaning that no handler needs to be called at that
 * point.
 * PTHREAD_ATFORK can be called several times, in which case the PREPARE
 * handlers are called in LIFO order (last added with PTHREAD_ATFORK,
 * first called before FORK), and the PARENT and CHILD handlers are called
 * in FIFO (first added, first called)
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to register callbacks */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_atfork)(__pthread_atfork_func_t prepare,
                                          __pthread_atfork_func_t parent,
                                          __pthread_atfork_func_t child)
/*[[[body:libc_pthread_atfork]]]*/
/*AUTO*/{
	(void)prepare;
	(void)parent;
	(void)child;
	CRT_UNIMPLEMENTEDF("pthread_atfork(%p, %p, %p)", prepare, parent, child); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_atfork]]]*/

/*[[[head:libc___pthread_register_cancel,hash:CRC-32=0xa8bf5df4]]]*/
INTERN ATTR_SECTION(".text.crt.sched.pthread") __cleanup_fct_attribute void
NOTHROW_NCX(LIBCCALL libc___pthread_register_cancel)(__pthread_unwind_buf_t *buf)
/*[[[body:libc___pthread_register_cancel]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("__pthread_register_cancel(%p)", buf); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc___pthread_register_cancel]]]*/

/*[[[head:libc___pthread_unregister_cancel,hash:CRC-32=0x58f63eed]]]*/
INTERN ATTR_SECTION(".text.crt.sched.pthread") __cleanup_fct_attribute NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc___pthread_unregister_cancel)(__pthread_unwind_buf_t *buf)
/*[[[body:libc___pthread_unregister_cancel]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("__pthread_unregister_cancel(%p)", buf); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc___pthread_unregister_cancel]]]*/

/*[[[head:libc___pthread_register_cancel_defer,hash:CRC-32=0x9c4cb803]]]*/
INTERN ATTR_SECTION(".text.crt.sched.pthread") __cleanup_fct_attribute NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc___pthread_register_cancel_defer)(__pthread_unwind_buf_t *buf)
/*[[[body:libc___pthread_register_cancel_defer]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("__pthread_register_cancel_defer(%p)", buf); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc___pthread_register_cancel_defer]]]*/

/*[[[head:libc___pthread_unregister_cancel_restore,hash:CRC-32=0xecef4ef3]]]*/
INTERN ATTR_SECTION(".text.crt.sched.pthread") __cleanup_fct_attribute NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc___pthread_unregister_cancel_restore)(__pthread_unwind_buf_t *buf)
/*[[[body:libc___pthread_unregister_cancel_restore]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("__pthread_unregister_cancel_restore(%p)", buf); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc___pthread_unregister_cancel_restore]]]*/

/*[[[head:libc___pthread_unwind_next,hash:CRC-32=0xb72a137c]]]*/
/* Internal interface to initiate cleanup */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_WEAK __cleanup_fct_attribute NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc___pthread_unwind_next)(__pthread_unwind_buf_t *buf)
/*[[[body:libc___pthread_unwind_next]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("__pthread_unwind_next(%p)", buf); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc___pthread_unwind_next]]]*/















/************************************************************************/
/* pthread_mutexattr_t                                                  */
/************************************************************************/

/*[[[head:libc_pthread_mutexattr_init,hash:CRC-32=0x98507d2d]]]*/
/* Initialize mutex attribute object ATTR with default attributes (kind is PTHREAD_MUTEX_TIMED_NP)
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_init)(pthread_mutexattr_t *attr)
/*[[[body:libc_pthread_mutexattr_init]]]*/
{
	attr->ma_kind = PTHREAD_MUTEX_NORMAL;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_init]]]*/

/*[[[head:libc_pthread_mutexattr_destroy,hash:CRC-32=0x2bd4832d]]]*/
/* Destroy mutex attribute object ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_destroy)(pthread_mutexattr_t *attr)
/*[[[body:libc_pthread_mutexattr_destroy]]]*/
{
	(void)attr;
#ifndef NDEBUG
	memset(attr, 0xcc, sizeof(*attr));
#endif /* !NDEBUG */
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_destroy]]]*/

/*[[[head:libc_pthread_mutexattr_getpshared,hash:CRC-32=0x6c054a]]]*/
/* Get the process-shared flag of the mutex attribute ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
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

/*[[[head:libc_pthread_mutexattr_setpshared,hash:CRC-32=0x49a47498]]]*/
/* Set the process-shared flag of the mutex attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_mutexattr_gettype,hash:CRC-32=0x52daaa98]]]*/
/* Return in *KIND the mutex kind attribute in *ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_gettype)(pthread_mutexattr_t const *__restrict attr,
                                                     int *__restrict kind)
/*[[[body:libc_pthread_mutexattr_gettype]]]*/
{
	*kind = attr->ma_kind & PTHREAD_MUTEXATTR_KIND_MASK;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_gettype]]]*/

/*[[[head:libc_pthread_mutexattr_settype,hash:CRC-32=0x8b52f09a]]]*/
/* Set the mutex kind attribute in *ATTR to KIND (either PTHREAD_MUTEX_NORMAL,
 * PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK, or PTHREAD_MUTEX_DEFAULT)
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `kind' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_mutexattr_getprotocol,hash:CRC-32=0xad01d9]]]*/
/* Return in *PROTOCOL the mutex protocol attribute in *ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getprotocol)(pthread_mutexattr_t const *__restrict attr,
                                                         int *__restrict protocol)
/*[[[body:libc_pthread_mutexattr_getprotocol]]]*/
{
	*protocol = (attr->ma_kind & PTHREAD_MUTEXATTR_PROTOCOL_MASK) >>
	            PTHREAD_MUTEXATTR_PROTOCOL_SHIFT;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_getprotocol]]]*/

/*[[[head:libc_pthread_mutexattr_setprotocol,hash:CRC-32=0x6be5c193]]]*/
/* Set the mutex protocol attribute in *ATTR to PROTOCOL (either
 * PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, or PTHREAD_PRIO_PROTECT)
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `protocol' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_mutexattr_getprioceiling,hash:CRC-32=0x82c77a]]]*/
/* Return in *PRIOCEILING the mutex prioceiling attribute in *ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getprioceiling)(pthread_mutexattr_t const *__restrict attr,
                                                            int *__restrict prioceiling)
/*[[[body:libc_pthread_mutexattr_getprioceiling]]]*/
{
	*prioceiling = (attr->ma_kind & PTHREAD_MUTEXATTR_PRIO_CEILING_MASK) >>
	               PTHREAD_MUTEXATTR_PRIO_CEILING_SHIFT;
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_getprioceiling]]]*/

/*[[[head:libc_pthread_mutexattr_setprioceiling,hash:CRC-32=0x3bc35fd4]]]*/
/* Set the mutex prioceiling attribute in *ATTR to PRIOCEILING
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_mutexattr_getrobust,hash:CRC-32=0x8efeb6f2]]]*/
/* Get the robustness flag of the mutex attribute ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getrobust)(pthread_mutexattr_t const *attr,
                                                       int *robustness)
/*[[[body:libc_pthread_mutexattr_getrobust]]]*/
{
	*robustness = ((attr->ma_kind & PTHREAD_MUTEXATTR_FLAG_ROBUST) != 0
	               ? PTHREAD_MUTEX_ROBUST
	               : PTHREAD_MUTEX_STALLED);
	return EOK;
}
/*[[[end:libc_pthread_mutexattr_getrobust]]]*/

/*[[[head:libc_pthread_mutexattr_setrobust,hash:CRC-32=0xb642d96d]]]*/
/* Set the robustness flag of the mutex attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `robustness' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_rwlockattr_init,hash:CRC-32=0xc85ba79e]]]*/
/* Initialize attribute object ATTR with default values
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_init)(pthread_rwlockattr_t *attr)
/*[[[body:libc_pthread_rwlockattr_init]]]*/
{
	attr->rwa_kind   = PTHREAD_RWLOCK_DEFAULT_NP;
	attr->rwa_shared = PTHREAD_PROCESS_PRIVATE;
	return EOK;
}
/*[[[end:libc_pthread_rwlockattr_init]]]*/

/*[[[head:libc_pthread_rwlockattr_destroy,hash:CRC-32=0x281c8079]]]*/
/* Destroy attribute object ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_destroy)(pthread_rwlockattr_t *attr)
/*[[[body:libc_pthread_rwlockattr_destroy]]]*/
{
	(void)attr;
#ifndef NDEBUG
	memset(attr, 0xcc, sizeof(*attr));
#endif /* !NDEBUG */
	return EOK;
}
/*[[[end:libc_pthread_rwlockattr_destroy]]]*/

/*[[[head:libc_pthread_rwlockattr_getpshared,hash:CRC-32=0xce801c4d]]]*/
/* Return current setting of process-shared attribute of ATTR in PSHARED
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_getpshared)(pthread_rwlockattr_t const *__restrict attr,
                                                         int *__restrict pshared)
/*[[[body:libc_pthread_rwlockattr_getpshared]]]*/
{
	*pshared = attr->rwa_shared;
	return EOK;
}
/*[[[end:libc_pthread_rwlockattr_getpshared]]]*/

/*[[[head:libc_pthread_rwlockattr_setpshared,hash:CRC-32=0x70df333]]]*/
/* Set process-shared attribute of ATTR to PSHARED
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pthread' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_rwlockattr_getkind_np,hash:CRC-32=0x5c15d21]]]*/
/* Return current setting of reader/writer preference
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_getkind_np)(pthread_rwlockattr_t const *__restrict attr,
                                                         int *__restrict pref)
/*[[[body:libc_pthread_rwlockattr_getkind_np]]]*/
{
	*pref = attr->rwa_kind;
	return EOK;
}
/*[[[end:libc_pthread_rwlockattr_getkind_np]]]*/

/*[[[head:libc_pthread_rwlockattr_setkind_np,hash:CRC-32=0x585726c8]]]*/
/* Set reader/write preference
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pref' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_condattr_init,hash:CRC-32=0xe5f39fd]]]*/
/* Initialize condition variable attribute ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_init)(pthread_condattr_t *attr)
/*[[[body:libc_pthread_condattr_init]]]*/
{
	attr->ca_value = CLOCK_REALTIME << PTHREAD_CONDATTR_CLOCKID_SHIFT;
	return EOK;
}
/*[[[end:libc_pthread_condattr_init]]]*/

/*[[[head:libc_pthread_condattr_destroy,hash:CRC-32=0x47268095]]]*/
/* Destroy condition variable attribute ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_destroy)(pthread_condattr_t *attr)
/*[[[body:libc_pthread_condattr_destroy]]]*/
{
	(void)attr;
#ifndef NDEBUG
	memset(attr, 0xcc, sizeof(*attr));
#endif /* !NDEBUG */
	return EOK;
}
/*[[[end:libc_pthread_condattr_destroy]]]*/

/*[[[head:libc_pthread_condattr_getpshared,hash:CRC-32=0x1e42ba7f]]]*/
/* Get the process-shared flag of the condition variable attribute ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
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

/*[[[head:libc_pthread_condattr_setpshared,hash:CRC-32=0x4bd5bd38]]]*/
/* Set the process-shared flag of the condition variable attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_condattr_getclock,hash:CRC-32=0x577c40cf]]]*/
/* Get the clock selected for the condition variable attribute ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_getclock)(pthread_condattr_t const *__restrict attr,
                                                     clockid_t *__restrict clock_id)
/*[[[body:libc_pthread_condattr_getclock]]]*/
{
	*clock_id = (clockid_t)(attr->ca_value >> PTHREAD_CONDATTR_CLOCKID_SHIFT);
	return EOK;
}
/*[[[end:libc_pthread_condattr_getclock]]]*/

/*[[[head:libc_pthread_condattr_setclock,hash:CRC-32=0x2fbdfa08]]]*/
/* Set the clock selected for the condition variable attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `clock_id' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_barrierattr_init,hash:CRC-32=0x8db33f2f]]]*/
/* Initialize barrier attribute ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_init)(pthread_barrierattr_t *attr)
/*[[[body:libc_pthread_barrierattr_init]]]*/
{
	attr->ba_pshared = PTHREAD_PROCESS_PRIVATE;
	return EOK;
}
/*[[[end:libc_pthread_barrierattr_init]]]*/

/*[[[head:libc_pthread_barrierattr_destroy,hash:CRC-32=0xcb904641]]]*/
/* Destroy previously dynamically initialized barrier attribute ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_destroy)(pthread_barrierattr_t *attr)
/*[[[body:libc_pthread_barrierattr_destroy]]]*/
{
	(void)attr;
#ifndef NDEBUG
	memset(attr, 0xcc, sizeof(*attr));
#endif /* !NDEBUG */
	return EOK;
}
/*[[[end:libc_pthread_barrierattr_destroy]]]*/

/*[[[head:libc_pthread_barrierattr_getpshared,hash:CRC-32=0xccd1a199]]]*/
/* Get the process-shared flag of the barrier attribute ATTR
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_getpshared)(pthread_barrierattr_t const *__restrict attr,
                                                          int *__restrict pshared)
/*[[[body:libc_pthread_barrierattr_getpshared]]]*/
{
	*pshared = attr->ba_pshared;
	return EOK;
}
/*[[[end:libc_pthread_barrierattr_getpshared]]]*/

/*[[[head:libc_pthread_barrierattr_setpshared,hash:CRC-32=0xf2b925f6]]]*/
/* Set the process-shared flag of the barrier attribute ATTR
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `pshared' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_mutex_init,hash:CRC-32=0xd6a445c9]]]*/
/* Initialize a mutex
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_init)(pthread_mutex_t *mutex,
                                              pthread_mutexattr_t const *mutexattr)
/*[[[body:libc_pthread_mutex_init]]]*/
{
	memset(mutex, 0, sizeof(*mutex));
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

/*[[[head:libc_pthread_mutex_destroy,hash:CRC-32=0x5cf2558e]]]*/
/* Destroy a mutex
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_destroy)(pthread_mutex_t *mutex)
/*[[[body:libc_pthread_mutex_destroy]]]*/
{
	(void)mutex;
#ifndef NDEBUG
	memset(mutex, 0xcc, sizeof(*mutex));
#endif /* !NDEBUG */
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

/*[[[head:libc_pthread_mutex_trylock,hash:CRC-32=0x91485880]]]*/
/* Try locking a mutex
 * @return: EOK:   Success
 * @return: EBUSY: The mutex has already been locked
 *                 In case of a recursive mutex, another
 *                 thread was the one to acquire the lock. */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_trylock)(pthread_mutex_t *mutex)
/*[[[body:libc_pthread_mutex_trylock]]]*/
{
	uint32_t lock;
	return mutex_trylock(mutex, &lock);
}
/*[[[end:libc_pthread_mutex_trylock]]]*/

/*[[[head:libc_pthread_mutex_lock,hash:CRC-32=0xf0a7b905]]]*/
/* Lock a mutex
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_mutex_timedlock,hash:CRC-32=0xce8df9ea]]]*/
/* Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1, 2)) errno_t
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
	 * NOTE: Need to use `FUTEX_WAIT_BITSET', since only that one takes
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

/* With a 64-bit timeout, wait while a 32-bit control word matches
 * the given value. Note that this function may access up to 8 bytes
 * starting at the base of the futex control word, through only the
 * first 4 bytes are actually inspected.
 * HINT: Waiting for 32-bit control words on 64-bit platforms is
 *       done by making use of `LFUTEX_WAIT_WHILE_BITMASK' */
#if __SIZEOF_POINTER__ == 4
#define sys_lfutex32_waitwhile64(uaddr, val, timeout) \
	sys_lfutex(uaddr, LFUTEX_WAIT_WHILE, val, timeout, 0)
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define sys_lfutex32_waitwhile64(uaddr, val, timeout)          \
	sys_lfutex((uint64_t *)(uaddr), LFUTEX_WAIT_WHILE_BITMASK, \
	           (uint64_t)UINT32_MAX, timeout,                  \
	           (uint64_t)(uint32_t)(val))
#else /* ... */
#define sys_lfutex32_waitwhile64(uaddr, val, timeout)          \
	sys_lfutex((uint64_t *)(uaddr), LFUTEX_WAIT_WHILE_BITMASK, \
	           (uint64_t)(UINT32_MAX << 32), timeout,          \
	           (uint64_t)(uint32_t)(val) << 32)
#endif /* !... */


/*[[[head:libc_pthread_mutex_timedlock64,hash:CRC-32=0x8ea7106f]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_mutex_timedlock64, libc_pthread_mutex_timedlock);
#else /* MAGIC:alias */
/* Wait until lock becomes available, or specified time passes
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1, 2)) errno_t
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
	                                           lock, abstime);
	/* Check for timeout. */
	if (result == -ETIMEDOUT || result == -EINVAL)
		return -result;
	goto again;
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_mutex_timedlock64]]]*/

/*[[[head:libc_pthread_mutex_unlock,hash:CRC-32=0x40088005]]]*/
/* Unlock a mutex
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
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

/*[[[head:libc_pthread_mutex_getprioceiling,hash:CRC-32=0x71613e2b]]]*/
/* Get the priority ceiling of MUTEX
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_getprioceiling)(pthread_mutex_t const *__restrict mutex,
                                                        int *__restrict prioceiling)
/*[[[body:libc_pthread_mutex_getprioceiling]]]*/
/*AUTO*/{
	(void)mutex;
	(void)prioceiling;
	CRT_UNIMPLEMENTEDF("pthread_mutex_getprioceiling(%p, %p)", mutex, prioceiling); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutex_getprioceiling]]]*/

/*[[[head:libc_pthread_mutex_setprioceiling,hash:CRC-32=0x24992259]]]*/
/* Set the priority ceiling of MUTEX to PRIOCEILING,
 * return old priority ceiling value in *OLD_CEILING
 * @return: EOK:    Success
 * @return: EINVAL: Invalid/unsupported `prioceiling' */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_setprioceiling)(pthread_mutex_t *__restrict mutex,
                                                        int prioceiling,
                                                        int *__restrict old_ceiling)
/*[[[body:libc_pthread_mutex_setprioceiling]]]*/
/*AUTO*/{
	(void)mutex;
	(void)prioceiling;
	(void)old_ceiling;
	CRT_UNIMPLEMENTEDF("pthread_mutex_setprioceiling(%p, %x, %p)", mutex, prioceiling, old_ceiling); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutex_setprioceiling]]]*/

/*[[[head:libc_pthread_mutex_consistent,hash:CRC-32=0xbfb36079]]]*/
/* Declare the state protected by MUTEX as consistent
 * @return: EOK:    Success
 * @return: EINVAL: Not a robust mutex
 * @return: EINVAL: Mutex was already in a consistent state */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_consistent)(pthread_mutex_t *mutex)
/*[[[body:libc_pthread_mutex_consistent]]]*/
/*AUTO*/{
	(void)mutex;
	CRT_UNIMPLEMENTEDF("pthread_mutex_consistent(%p)", mutex); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutex_consistent]]]*/















/************************************************************************/
/* pthread_rwlock_t                                                     */
/************************************************************************/

/*[[[head:libc_pthread_rwlock_init,hash:CRC-32=0x73144ee6]]]*/
/* Initialize read-write lock RWLOCK using attributes ATTR,
 * or use the default values if later is NULL
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_init)(pthread_rwlock_t *__restrict rwlock,
                                               pthread_rwlockattr_t const *__restrict attr)
/*[[[body:libc_pthread_rwlock_init]]]*/
/*AUTO*/{
	(void)rwlock;
	(void)attr;
	CRT_UNIMPLEMENTEDF("pthread_rwlock_init(%p, %p)", rwlock, attr); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_init]]]*/

/*[[[head:libc_pthread_rwlock_destroy,hash:CRC-32=0xe671d3ec]]]*/
/* Destroy read-write lock RWLOCK
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_destroy)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_destroy]]]*/
/*AUTO*/{
	(void)rwlock;
	CRT_UNIMPLEMENTEDF("pthread_rwlock_destroy(%p)", rwlock); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_destroy]]]*/

/*[[[head:libc_pthread_rwlock_rdlock,hash:CRC-32=0x26072a12]]]*/
/* Acquire read lock for RWLOCK
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_rdlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_rdlock]]]*/
/*AUTO*/{
	(void)rwlock;
	CRT_UNIMPLEMENTEDF("pthread_rwlock_rdlock(%p)", rwlock); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_rdlock]]]*/

/*[[[head:libc_pthread_rwlock_tryrdlock,hash:CRC-32=0x94ad86a4]]]*/
/* Try to acquire read lock for RWLOCK
 * @return: EOK:   Success
 * @return: EBUSY: A read-lock cannot be acquired at the moment,
 *                 because a write-lock is already being held. */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_tryrdlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_tryrdlock]]]*/
/*AUTO*/{
	(void)rwlock;
	CRT_UNIMPLEMENTEDF("pthread_rwlock_tryrdlock(%p)", rwlock); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_tryrdlock]]]*/

/*[[[head:libc_pthread_rwlock_timedrdlock,hash:CRC-32=0xea9f7a9]]]*/
/* Try to acquire read lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1, 2)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedrdlock)(pthread_rwlock_t *__restrict rwlock,
                                                      struct timespec const *__restrict abstime)
/*[[[body:libc_pthread_rwlock_timedrdlock]]]*/
{
	(void)rwlock;
	(void)abstime;
	CRT_UNIMPLEMENTED("pthread_rwlock_timedrdlock"); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_timedrdlock]]]*/

/*[[[head:libc_pthread_rwlock_timedrdlock64,hash:CRC-32=0x169d94e9]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_rwlock_timedrdlock64, libc_pthread_rwlock_timedrdlock);
#else /* MAGIC:alias */
/* Try to acquire read lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1, 2)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedrdlock64)(pthread_rwlock_t *__restrict rwlock,
                                                        struct timespec64 const *__restrict abstime)
/*[[[body:libc_pthread_rwlock_timedrdlock64]]]*/
{
	(void)rwlock;
	(void)abstime;
	CRT_UNIMPLEMENTED("pthread_rwlock_timedrdlock64"); /* TODO */
	return ENOSYS;
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_rwlock_timedrdlock64]]]*/

/*[[[head:libc_pthread_rwlock_wrlock,hash:CRC-32=0xa42db5db]]]*/
/* Acquire write lock for RWLOCK
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_wrlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_wrlock]]]*/
/*AUTO*/{
	(void)rwlock;
	CRT_UNIMPLEMENTEDF("pthread_rwlock_wrlock(%p)", rwlock); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_wrlock]]]*/

/*[[[head:libc_pthread_rwlock_trywrlock,hash:CRC-32=0x13d9deab]]]*/
/* Try to acquire write lock for RWLOCK
 * @return: EOK:   Success
 * @return: EBUSY: A write-lock cannot be acquired at the moment,
 *                 because read-locks are already being held. */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_trywrlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_trywrlock]]]*/
/*AUTO*/{
	(void)rwlock;
	CRT_UNIMPLEMENTEDF("pthread_rwlock_trywrlock(%p)", rwlock); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_trywrlock]]]*/

/*[[[head:libc_pthread_rwlock_timedwrlock,hash:CRC-32=0xc0aa905c]]]*/
/* Try to acquire write lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1, 2)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedwrlock)(pthread_rwlock_t *__restrict rwlock,
                                                      struct timespec const *__restrict abstime)
/*[[[body:libc_pthread_rwlock_timedwrlock]]]*/
{
	(void)rwlock;
	(void)abstime;
	CRT_UNIMPLEMENTED("pthread_rwlock_timedwrlock"); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_timedwrlock]]]*/

/*[[[head:libc_pthread_rwlock_timedwrlock64,hash:CRC-32=0xc711c5e4]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_rwlock_timedwrlock64, libc_pthread_rwlock_timedwrlock);
#else /* MAGIC:alias */
/* Try to acquire write lock for RWLOCK or return after specfied time
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1, 2)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_timedwrlock64)(pthread_rwlock_t *__restrict rwlock,
                                                        struct timespec64 const *__restrict abstime)
/*[[[body:libc_pthread_rwlock_timedwrlock64]]]*/
{
	(void)rwlock;
	(void)abstime;
	CRT_UNIMPLEMENTED("pthread_rwlock_timedwrlock64"); /* TODO */
	return ENOSYS;
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_rwlock_timedwrlock64]]]*/

/*[[[head:libc_pthread_rwlock_unlock,hash:CRC-32=0xdb1089e8]]]*/
/* Unlock RWLOCK
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_unlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_unlock]]]*/
/*AUTO*/{
	(void)rwlock;
	CRT_UNIMPLEMENTEDF("pthread_rwlock_unlock(%p)", rwlock); /* TODO */
	return ENOSYS;
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


/*[[[head:libc_pthread_cond_init,hash:CRC-32=0x157549ec]]]*/
/* Initialize condition variable COND using attributes
 * ATTR, or use the default values if later is NULL
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cond_init)(pthread_cond_t *__restrict cond,
                                             pthread_condattr_t const *__restrict cond_attr)
/*[[[body:libc_pthread_cond_init]]]*/
{
	memset(cond, 0, sizeof(*cond));
	(void)cond_attr;
	return EOK;
}
/*[[[end:libc_pthread_cond_init]]]*/

/*[[[head:libc_pthread_cond_destroy,hash:CRC-32=0xf4aa7c1a]]]*/
/* Destroy condition variable COND
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cond_destroy)(pthread_cond_t *cond)
/*[[[body:libc_pthread_cond_destroy]]]*/
{
	(void)cond;
#ifndef NDEBUG
	memset(cond, 0xcc, sizeof(*cond));
#endif /* !NDEBUG */
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
			 * still contained the `FUTEX_WAITERS' bit set.
			 *
			 * This can happen when the caller only ever uses
			 * `pthread_cond_signal()', which would result in
			 * the `FUTEX_WAITERS' bit never getting unset.
			 *
			 * However, we do actually want to make use of that
			 * bit, so we don't have to do an expensive system
			 * call all too often.
			 *
			 * So if we notice that we couldn't wake up anyone,
			 * but the futex control word still indicates that
			 * there are waiting threads, then we do another wake
			 * in which we wake up _all_ waiting threads.
			 *
			 * In all likelihood, there won't be any of them now,
			 * since just a moment ago, no-one was waiting for the
			 * futex, but on the off-chance that more waiters
			 * appeared between then and now, those threads will
			 * simply receive a sporadic, but harmless wake-up.
			 */
			assert(how_many != (uint32_t)-1);
			how_many = (uint32_t)-1;
			goto again;
		}
	}
	return EOK;
}

/*[[[head:libc_pthread_cond_signal,hash:CRC-32=0x69fb2b65]]]*/
/* Wake up one thread waiting for condition variable COND
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cond_signal)(pthread_cond_t *cond)
/*[[[body:libc_pthread_cond_signal]]]*/
{
	return libc_pthread_cond_wake(cond, 1);
}
/*[[[end:libc_pthread_cond_signal]]]*/

/*[[[head:libc_pthread_cond_broadcast,hash:CRC-32=0xc60ec353]]]*/
/* Wake up all threads waiting for condition variables COND
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cond_broadcast)(pthread_cond_t *cond)
/*[[[body:libc_pthread_cond_broadcast]]]*/
{
	return libc_pthread_cond_wake(cond, (uint32_t)-1);
}
/*[[[end:libc_pthread_cond_broadcast]]]*/

/*[[[head:libc_pthread_cond_wait,hash:CRC-32=0xdfb4b151]]]*/
/* Wait for condition variable COND to be signaled or broadcast.
 * MUTEX is assumed to be locked before.
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
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
		 *       we're released `mutex', else there'd be a race condition! */
		ATOMIC_FETCHOR(cond->c_futex, FUTEX_WAITERS);
		lock |= FUTEX_WAITERS;
	}
	/* Interlocked:wait */
	sys_futex(&cond->c_futex, FUTEX_WAIT, lock, NULL, NULL, 0);
	/* Return-path */
	libc_pthread_mutex_lock(mutex);
	return EOK;
}
/*[[[end:libc_pthread_cond_wait]]]*/

/*[[[head:libc_pthread_cond_timedwait,hash:CRC-32=0x877e7300]]]*/
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1, 2, 3)) errno_t
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
		 *       we're released `mutex', else there'd be a race condition! */
		ATOMIC_FETCHOR(cond->c_futex, FUTEX_WAITERS);
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

/*[[[head:libc_pthread_cond_timedwait64,hash:CRC-32=0xdc3f0f17]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_cond_timedwait64, libc_pthread_cond_timedwait);
#else /* MAGIC:alias */
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970).
 * @return: EOK:       Success
 * @return: EINVAL:    The given `abstime' is invalid
 * @return: ETIMEDOUT: The given `abstime' has expired */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED NONNULL((1, 2, 3)) errno_t
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
		 *       we're released `mutex', else there'd be a race condition! */
		ATOMIC_FETCHOR(cond->c_futex, FUTEX_WAITERS);
		lock |= FUTEX_WAITERS;
	}
	/* Interlocked:wait */
	result = (errno_t)-sys_lfutex32_waitwhile64(&cond->c_futex, lock, abstime);
	/* Check for timeout. */
	if (result != ETIMEDOUT && result != EINVAL)
		result = EOK;
	/* Return-path */
	libc_pthread_mutex_lock(mutex);
	return result;
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_cond_timedwait64]]]*/















/************************************************************************/
/* pthread_barrier_t                                                    */
/************************************************************************/

/*[[[head:libc_pthread_barrier_init,hash:CRC-32=0xf6825f87]]]*/
/* Initialize BARRIER with the attributes in ATTR.
 * The barrier is opened when COUNT waiters arrived
 * @return: EOK:    Success
 * @return: EINVAL: The given `count' is ZERO(0) */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrier_init)(pthread_barrier_t *__restrict barrier,
                                                pthread_barrierattr_t const *__restrict attr,
                                                unsigned int count)
/*[[[body:libc_pthread_barrier_init]]]*/
/*AUTO*/{
	(void)barrier;
	(void)attr;
	(void)count;
	CRT_UNIMPLEMENTEDF("pthread_barrier_init(%p, %p, %x)", barrier, attr, count); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_barrier_init]]]*/

/*[[[head:libc_pthread_barrier_destroy,hash:CRC-32=0xc64626e3]]]*/
/* Destroy a previously dynamically initialized barrier BARRIER
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrier_destroy)(pthread_barrier_t *barrier)
/*[[[body:libc_pthread_barrier_destroy]]]*/
/*AUTO*/{
	(void)barrier;
	CRT_UNIMPLEMENTEDF("pthread_barrier_destroy(%p)", barrier); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_barrier_destroy]]]*/

/*[[[head:libc_pthread_barrier_wait,hash:CRC-32=0x75932430]]]*/
/* Wait on barrier BARRIER
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_barrier_wait)(pthread_barrier_t *barrier)
/*[[[body:libc_pthread_barrier_wait]]]*/
/*AUTO*/{
	(void)barrier;
	CRT_UNIMPLEMENTEDF("pthread_barrier_wait(%p)", barrier); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_barrier_wait]]]*/















/************************************************************************/
/* pthread_key_t                                                        */
/************************************************************************/

/*[[[head:libc_pthread_key_create,hash:CRC-32=0x23da4f7d]]]*/
/* Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. DESTR_FUNCTION, if non-NULL, is called with the value
 * associated to that key when the key is destroyed.
 * DESTR_FUNCTION is not called if the value associated is NULL when
 * the key is destroyed
 * @return: EOK:    Success
 * @return: ENOMEM: Insufficient memory to create the key */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_key_create)(pthread_key_t *key,
                                              __pthread_destr_function_t destr_function)
/*[[[body:libc_pthread_key_create]]]*/
/*AUTO*/{
	(void)key;
	(void)destr_function;
	CRT_UNIMPLEMENTEDF("pthread_key_create(%p, %p)", key, destr_function); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_key_create]]]*/

/*[[[head:libc_pthread_key_delete,hash:CRC-32=0x4c9f546c]]]*/
/* Destroy KEY
 * @return: EOK: Success */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_key_delete)(pthread_key_t key)
/*[[[body:libc_pthread_key_delete]]]*/
/*AUTO*/{
	(void)key;
	CRT_UNIMPLEMENTEDF("pthread_key_delete(%" PRIxN(__SIZEOF_PTHREAD_KEY_T) ")", key); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_key_delete]]]*/

/*[[[head:libc_pthread_getspecific,hash:CRC-32=0xbf764dff]]]*/
/* Return current value of the thread-specific data slot identified by KEY
 * @return: * :   The value currently associated with `key' in the calling thread
 * @return: NULL: The current value is `NULL', or no value has been bound, yet */
INTERN ATTR_SECTION(".text.crt.sched.pthread") WUNUSED void *
NOTHROW_NCX(LIBCCALL libc_pthread_getspecific)(pthread_key_t key)
/*[[[body:libc_pthread_getspecific]]]*/
/*AUTO*/{
	(void)key;
	CRT_UNIMPLEMENTEDF("pthread_getspecific(%" PRIxN(__SIZEOF_PTHREAD_KEY_T) ")", key); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_pthread_getspecific]]]*/

/*[[[head:libc_pthread_setspecific,hash:CRC-32=0x35e8a87]]]*/
/* Store POINTER in the thread-specific data slot identified by KEY
 * @return: EOK:    Success
 * @return: ENOMEM: `pointer' is non-NULL, `key' had yet to be allowed for the
 *                  calling thread, and an attempt to allocate it just now failed */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setspecific)(pthread_key_t key,
                                               void const *pointer)
/*[[[body:libc_pthread_setspecific]]]*/
/*AUTO*/{
	(void)key;
	(void)pointer;
	CRT_UNIMPLEMENTEDF("pthread_setspecific(%" PRIxN(__SIZEOF_PTHREAD_KEY_T) ", %p)", key, pointer); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_setspecific]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x4f79b57]]]*/
DEFINE_PUBLIC_ALIAS(pthread_create, libc_pthread_create);
DEFINE_PUBLIC_ALIAS(pthread_exit, libc_pthread_exit);
DEFINE_PUBLIC_ALIAS(pthread_join, libc_pthread_join);
DEFINE_PUBLIC_ALIAS(pthread_tryjoin_np, libc_pthread_tryjoin_np);
DEFINE_PUBLIC_ALIAS(pthread_timedjoin_np, libc_pthread_timedjoin_np);
DEFINE_PUBLIC_ALIAS(pthread_timedjoin64_np, libc_pthread_timedjoin64_np);
DEFINE_PUBLIC_ALIAS(pthread_detach, libc_pthread_detach);
DEFINE_PUBLIC_ALIAS(thrd_current, libc_pthread_self);
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
DEFINE_PUBLIC_ALIAS(pthread_getname_np, libc_pthread_getname_np);
DEFINE_PUBLIC_ALIAS(pthread_setname_np, libc_pthread_setname_np);
DEFINE_PUBLIC_ALIAS(pthread_gettid_np, libc_pthread_gettid_np);
DEFINE_PUBLIC_ALIAS(pthread_getconcurrency, libc_pthread_getconcurrency);
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
DEFINE_PUBLIC_ALIAS(pthread_mutex_unlock, libc_pthread_mutex_unlock);
DEFINE_PUBLIC_ALIAS(pthread_mutex_getprioceiling, libc_pthread_mutex_getprioceiling);
DEFINE_PUBLIC_ALIAS(pthread_mutex_setprioceiling, libc_pthread_mutex_setprioceiling);
DEFINE_PUBLIC_ALIAS(pthread_mutex_consistent_np, libc_pthread_mutex_consistent);
DEFINE_PUBLIC_ALIAS(pthread_mutex_consistent, libc_pthread_mutex_consistent);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_init, libc_pthread_mutexattr_init);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_destroy, libc_pthread_mutexattr_destroy);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_getpshared, libc_pthread_mutexattr_getpshared);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_setpshared, libc_pthread_mutexattr_setpshared);
DEFINE_PUBLIC_ALIAS(pthread_mutexattr_gettype, libc_pthread_mutexattr_gettype);
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
DEFINE_PUBLIC_ALIAS(pthread_rwlock_timedrdlock, libc_pthread_rwlock_timedrdlock);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_timedrdlock64, libc_pthread_rwlock_timedrdlock64);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_wrlock, libc_pthread_rwlock_wrlock);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_trywrlock, libc_pthread_rwlock_trywrlock);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_timedwrlock, libc_pthread_rwlock_timedwrlock);
DEFINE_PUBLIC_ALIAS(pthread_rwlock_timedwrlock64, libc_pthread_rwlock_timedwrlock64);
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
DEFINE_PUBLIC_ALIAS(pthread_key_create, libc_pthread_key_create);
DEFINE_PUBLIC_ALIAS(tss_delete, libc_pthread_key_delete);
DEFINE_PUBLIC_ALIAS(pthread_key_delete, libc_pthread_key_delete);
DEFINE_PUBLIC_ALIAS(tss_get, libc_pthread_getspecific);
DEFINE_PUBLIC_ALIAS(pthread_getspecific, libc_pthread_getspecific);
DEFINE_PUBLIC_ALIAS(pthread_setspecific, libc_pthread_setspecific);
DEFINE_PUBLIC_ALIAS(pthread_getcpuclockid, libc_pthread_getcpuclockid);
DEFINE_PUBLIC_ALIAS(pthread_atfork, libc_pthread_atfork);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PTHREAD_C */
