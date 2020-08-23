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

#include "../libc/pthread.h"
/**/

#include <hybrid/atomic.h>
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




STATIC_ASSERT(offsetof(struct pthread, pt_tid) == OFFSET_PTHREAD_TID);
STATIC_ASSERT(offsetof(struct pthread, pt_refcnt) == OFFSET_PTHREAD_REFCNT);
STATIC_ASSERT(offsetof(struct pthread, pt_retval) == OFFSET_PTHREAD_RETVAL);
STATIC_ASSERT(offsetof(struct pthread, pt_tls) == OFFSET_PTHREAD_TLS);
STATIC_ASSERT(offsetof(struct pthread, pt_stackaddr) == OFFSET_PTHREAD_STACKADDR);
STATIC_ASSERT(offsetof(struct pthread, pt_stacksize) == OFFSET_PTHREAD_STACKSIZE);
STATIC_ASSERT(offsetof(struct pthread, pt_flags) == OFFSET_PTHREAD_FLAGS);


/* Destroy a given `pthread' `self' */
LOCAL NONNULL((1)) void
NOTHROW(LIBCCALL destroy)(struct pthread *__restrict self) {
	free(self);
}


struct pthread_attr {
	/* NOTE: This structure shares binary compatibility with GLibc (for the most part)
	 *       The only difference is that we allow the re-use of `pa_cpusetsize' as an
	 *       in-line 32/64-bit cpuset, thus preventing the need to dynamically allocate
	 *       small cpu sets on the heap when most of the time those structures would
	 *       only be a couple of bytes large. */
	struct sched_param pa_schedparam;  /* Scheduler parameters and priority. */
	int                pa_schedpolicy;
	int                pa_flags;       /* Various flags like detachstate, scope, etc (St of `ATTR_FLAG_*'). */
	size_t             pa_guardsize;   /* Size of guard area. */
	void              *pa_stackaddr;   /* Stack handling. */
	size_t             pa_stacksize;
	cpu_set_t         *pa_cpuset;      /* Affinity map. */
	size_t             pa_cpusetsize;
};
#define ATTR_FLAG_DETACHSTATE     0x0001
#define ATTR_FLAG_NOTINHERITSCHED 0x0002
#define ATTR_FLAG_SCOPEPROCESS    0x0004
#define ATTR_FLAG_STACKADDR       0x0008
#define ATTR_FLAG_OLDATTR         0x0010
#define ATTR_FLAG_SCHED_SET       0x0020
#define ATTR_FLAG_POLICY_SET      0x0040
STATIC_ASSERT(__SIZEOF_PTHREAD_ATTR_T >= sizeof(struct pthread_attr));

/* Attributes used by `pthread_create()' when the given `ATTR' is NULL
 * NOTE: When `pa_stacksize' is zero, `PTHREAD_STACK_MIN' will be used instead! */
ATTR_SECTION(".bss.crt.sched.pthread.pthread_default_attr.attr")
PRIVATE struct pthread_attr pthread_default_attr = {};
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
		exitcode = error_data()->e_pointers[0];
		me->pt_retval = NULL;
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
	struct pthread_attr const *at = (struct pthread_attr const *)attr;
	pt = (struct pthread *)malloc(sizeof(struct pthread));
	if unlikely(!pt)
		goto err_nomem;
	/* Allocate the DL TLS segment */
	pt->pt_tls = dltlsallocseg();
	if unlikely(!pt->pt_tls)
		goto err_nomem_pt;
	pt->pt_refcnt    = 2;
	pt->pt_flags     = PTHREAD_FNORMAL;
	pt->pt_stackaddr = at->pa_stackaddr;
	pt->pt_stacksize = at->pa_stacksize;
	pt->pt_cpuset    = NULL;
	/* Copy affinity cpuset information. */
	if (at->pa_cpuset) {
		pt->pt_cpusetsize = at->pa_cpusetsize;
		if (at->pa_cpuset == (cpu_set_t *)&at->pa_cpusetsize) {
			pt->pt_cpuset = (cpu_set_t *)&pt->pt_cpusetsize;
		} else {
			pt->pt_cpuset = (cpu_set_t *)malloc(pt->pt_cpusetsize);
			if unlikely(!pt->pt_cpuset)
				goto err_nomem_pt_tls;
			memcpy(pt->pt_cpuset, at->pa_cpuset, pt->pt_cpusetsize);
		}
	}
	if (!(at->pa_flags & ATTR_FLAG_STACKADDR)) {
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
	*newthread = (pthread_t)pt;
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

/*[[[head:libc_pthread_create,hash:CRC-32=0x690314e8]]]*/
/* Create a new thread, starting with execution of START-ROUTINE
 * getting passed ARG. Creation attributed come from ATTR. The new
 * handle is stored in *NEWTHREAD */
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
		libc_pthread_onexit(me);
	}
	/* XXX: THROW(E_EXIT_THREAD)? */
	/* Reminder: `sys_exit()' only terminates the calling thread.
	 * To terminate the calling process, you'd have to call `sys_exit_group()'! */
	sys_exit(0);
}
/*[[[end:libc_pthread_exit]]]*/

/*[[[head:libc_pthread_join,hash:CRC-32=0x1c1bd9ab]]]*/
/* Make calling thread wait for termination of the thread THREAD. The
 * exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
 * is not NULL */
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

/*[[[head:libc_pthread_tryjoin_np,hash:CRC-32=0xdeb4f067]]]*/
/* Check whether thread THREAD has terminated. If yes return the status of
 * the thread in *THREAD_RETURN, if THREAD_RETURN is not NULL */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_tryjoin_np)(pthread_t pthread,
                                              void **thread_return)
/*[[[body:libc_pthread_tryjoin_np]]]*/
{
	struct pthread *pt = (struct pthread *)pthread;
	if (ATOMIC_READ(pt->pt_tid) == 0) {
		if (thread_return)
			*thread_return = pt->pt_retval;
		if (ATOMIC_FETCHDEC(pt->pt_refcnt) == 1)
			destroy(pt);
		return EOK;
	}
	if unlikely(pt == tls.t_pthread)
		return EDEADLK;
	return EBUSY;
}
/*[[[end:libc_pthread_tryjoin_np]]]*/

/*[[[head:libc_pthread_timedjoin_np,hash:CRC-32=0x616d67d1]]]*/
/* Make calling thread wait for termination of the thread THREAD, but only
 * until TIMEOUT. The exit status of the thread is stored in
 * *THREAD_RETURN, if THREAD_RETURN is not NULL. */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_timedjoin_np)(pthread_t pthread,
                                                void **thread_return,
                                                struct timespec const *abstime)
/*[[[body:libc_pthread_timedjoin_np]]]*/
{
	struct pthread *pt = (struct pthread *)pthread;
	for (;;) {
		pid_t tid;
		syscall_slong_t result;
		/* Check if the thread already terminated. */
		tid = ATOMIC_READ(pt->pt_tid);
		if (tid == 0)
			break;
		if unlikely(pt == tls.t_pthread)
			return EDEADLK;
		/* >> wait_while(pt->pt_tid == tid) */
		result = sys_futex((uint32_t *)&pt->pt_tid,
		                   FUTEX_WAIT, tid,
		                   abstime, NULL, 0);
		if (result == -ETIMEDOUT)
			return (errno_t)-result;
	}
	if (thread_return)
		*thread_return = pt->pt_retval;
	if (ATOMIC_FETCHDEC(pt->pt_refcnt) == 1)
		destroy(pt);
	return EOK;
}
/*[[[end:libc_pthread_timedjoin_np]]]*/

/*[[[head:libc_pthread_timedjoin64_np,hash:CRC-32=0xb84bf015]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_timedjoin64_np, libc_pthread_timedjoin_np);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_timedjoin64_np)(pthread_t pthread,
                                                  void **thread_return,
                                                  struct timespec64 const *abstime)
/*[[[body:libc_pthread_timedjoin64_np]]]*/
{
#if __SIZEOF_POINTER__ == 4
	struct pthread *pt = (struct pthread *)pthread;
	for (;;) {
		pid_t tid;
		syscall_slong_t result;
		/* Check if the thread already terminated. */
		tid = ATOMIC_READ(pt->pt_tid);
		if (tid == 0)
			break;
		if unlikely(pt == tls.t_pthread)
			return EDEADLK;
		/* >> wait_while(pt->pt_tid == tid) */
		result = sys_lfutex((uint32_t *)&pt->pt_tid,
		                    LFUTEX_WAIT_WHILE, tid,
		                    abstime, 0);
		if (result == -ETIMEDOUT)
			return (errno_t)-result;
	}
	if (thread_return)
		*thread_return = pt->pt_retval;
	if (ATOMIC_FETCHDEC(pt->pt_refcnt) == 1)
		destroy(pt);
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

/*[[[head:libc_pthread_detach,hash:CRC-32=0x87278afb]]]*/
/* Indicate that the thread THREAD is never to be joined with PTHREAD_JOIN.
 * The resources of THREAD will therefore be freed immediately when it
 * terminates, instead of waiting for another thread to perform PTHREAD_JOIN on it */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_detach)(pthread_t pthread)
/*[[[body:libc_pthread_detach]]]*/
{
	struct pthread *pt;
	refcnt_t refcnt;
	pt = (struct pthread *)pthread;
	for (;;) {
		refcnt = ATOMIC_READ(pt->pt_refcnt);
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
			if (ATOMIC_READ(pt->pt_tid) != 0) {
				sys_sched_yield();
				continue;
			}
			/* The TID field was already set to ZERO. -> Set the reference
			 * counter to zero and destroy() the pthread structure ourself. */
			if (!ATOMIC_CMPXCH_WEAK(pt->pt_refcnt, 1, 0))
				continue;
			destroy(pt);
			break;
		}
		if (ATOMIC_CMPXCH_WEAK(pt->pt_refcnt, refcnt, refcnt - 1))
			break;
	}
	return EOK;
}
/*[[[end:libc_pthread_detach]]]*/

/*[[[head:libc_pthread_self,hash:CRC-32=0xd8a2de59]]]*/
/* Obtain the identifier of the current thread */
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
	return (pthread_t)result;
}
/*[[[end:libc_pthread_self]]]*/

/*[[[head:libc_pthread_gettid_np,hash:CRC-32=0x66dcbc0f]]]*/
/* Return the TID of the given `target_thread'
 * If the given `target_thread' has already terminated, 0 is returned */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_CONST WUNUSED pid_t
NOTHROW_NCX(LIBCCALL libc_pthread_gettid_np)(pthread_t target_thread)
/*[[[body:libc_pthread_gettid_np]]]*/
{
	pid_t result;
	struct pthread *pt;
	pt     = (struct pthread *)target_thread;
	result = pt->pt_tid;
	return result;
}
/*[[[end:libc_pthread_gettid_np]]]*/

/*[[[head:libc_pthread_attr_init,hash:CRC-32=0xd92491d0]]]*/
/* Initialize thread attribute *ATTR with default attributes
 * (detachstate is PTHREAD_JOINABLE, scheduling policy is SCHED_OTHER, no user-provided stack) */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_init)(pthread_attr_t *attr)
/*[[[body:libc_pthread_attr_init]]]*/
{
	struct pthread_attr *at;
	memset(attr, '\0', __SIZEOF_PTHREAD_ATTR_T);
	at = (struct pthread_attr *)attr;
	at->pa_guardsize = getpagesize();
	return EOK;
}
/*[[[end:libc_pthread_attr_init]]]*/

/*[[[head:libc_pthread_attr_destroy,hash:CRC-32=0x65637425]]]*/
/* Destroy thread attribute *ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_destroy)(pthread_attr_t *attr)
/*[[[body:libc_pthread_attr_destroy]]]*/
{
	struct pthread_attr *at = (struct pthread_attr *)attr;
	if likely(!(at->pa_flags & ATTR_FLAG_OLDATTR)) {
		if (at->pa_cpuset != (cpu_set_t *)&at->pa_cpusetsize)
			free(at->pa_cpuset);
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_destroy]]]*/

/*[[[head:libc_pthread_attr_getdetachstate,hash:CRC-32=0xaf732ceb]]]*/
/* Get detach state attribute */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getdetachstate)(pthread_attr_t const *attr,
                                                       int *detachstate)
/*[[[body:libc_pthread_attr_getdetachstate]]]*/
{
	struct pthread_attr const *at;
	at = (struct pthread_attr const *)attr;
	*detachstate = (at->pa_flags & ATTR_FLAG_DETACHSTATE
	                ? PTHREAD_CREATE_DETACHED
	                : PTHREAD_CREATE_JOINABLE);
	return EOK;
}
/*[[[end:libc_pthread_attr_getdetachstate]]]*/

/*[[[head:libc_pthread_attr_setdetachstate,hash:CRC-32=0x55ea5a26]]]*/
/* Set detach state attribute */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setdetachstate)(pthread_attr_t *attr,
                                                       int detachstate)
/*[[[body:libc_pthread_attr_setdetachstate]]]*/
{
	struct pthread_attr *at;
	at = (struct pthread_attr *)attr;
	if (detachstate == PTHREAD_CREATE_DETACHED)
		at->pa_flags |= ATTR_FLAG_DETACHSTATE;
	else if (detachstate == PTHREAD_CREATE_JOINABLE)
		at->pa_flags &= ~ATTR_FLAG_DETACHSTATE;
	else {
		return EINVAL;
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_setdetachstate]]]*/

/*[[[head:libc_pthread_attr_getguardsize,hash:CRC-32=0x1706e3a5]]]*/
/* Get the size of the guard area created for stack overflow protection */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getguardsize)(pthread_attr_t const *attr,
                                                     size_t *guardsize)
/*[[[body:libc_pthread_attr_getguardsize]]]*/
{
	struct pthread_attr const *at;
	at = (struct pthread_attr const *)attr;
	*guardsize = at->pa_guardsize;
	return EOK;
}
/*[[[end:libc_pthread_attr_getguardsize]]]*/

/*[[[head:libc_pthread_attr_setguardsize,hash:CRC-32=0xf6640ab3]]]*/
/* Set the size of the guard area created for stack overflow protection */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setguardsize)(pthread_attr_t *attr,
                                                     size_t guardsize)
/*[[[body:libc_pthread_attr_setguardsize]]]*/
{
	struct pthread_attr *at;
	at = (struct pthread_attr *)attr;
	at->pa_guardsize = guardsize;
	return EOK;
}
/*[[[end:libc_pthread_attr_setguardsize]]]*/

/*[[[head:libc_pthread_attr_getschedparam,hash:CRC-32=0xeb576ed]]]*/
/* Return in *PARAM the scheduling parameters of *ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getschedparam)(pthread_attr_t const *__restrict attr,
                                                      struct sched_param *__restrict param)
/*[[[body:libc_pthread_attr_getschedparam]]]*/
{
	struct pthread_attr const *at;
	at = (struct pthread_attr const *)attr;
	memcpy(param, &at->pa_schedparam, sizeof(struct sched_param));
	return EOK;
}
/*[[[end:libc_pthread_attr_getschedparam]]]*/

/*[[[head:libc_pthread_attr_setschedparam,hash:CRC-32=0x6632fa10]]]*/
/* Set scheduling parameters (priority, etc) in *ATTR according to PARAM */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setschedparam)(pthread_attr_t *__restrict attr,
                                                      struct sched_param const *__restrict param)
/*[[[body:libc_pthread_attr_setschedparam]]]*/
{
	struct pthread_attr *at;
	at = (struct pthread_attr *)attr;
	memcpy(&at->pa_schedparam, param, sizeof(struct sched_param));
	return EOK;
}
/*[[[end:libc_pthread_attr_setschedparam]]]*/

/*[[[head:libc_pthread_attr_getschedpolicy,hash:CRC-32=0xf2a974e7]]]*/
/* Return in *POLICY the scheduling policy of *ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getschedpolicy)(pthread_attr_t const *__restrict attr,
                                                       int *__restrict policy)
/*[[[body:libc_pthread_attr_getschedpolicy]]]*/
{
	struct pthread_attr const *at;
	at = (struct pthread_attr const *)attr;
	*policy = at->pa_schedpolicy;
	return EOK;
}
/*[[[end:libc_pthread_attr_getschedpolicy]]]*/

/*[[[head:libc_pthread_attr_setschedpolicy,hash:CRC-32=0xe7372782]]]*/
/* Set scheduling policy in *ATTR according to POLICY */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setschedpolicy)(pthread_attr_t *attr,
                                                       int policy)
/*[[[body:libc_pthread_attr_setschedpolicy]]]*/
{
	struct pthread_attr *at;
	at = (struct pthread_attr *)attr;
	if (policy != SCHED_OTHER && policy != SCHED_FIFO && policy != SCHED_RR)
		return EINVAL;
	at->pa_schedpolicy = policy;
	at->pa_flags |= ATTR_FLAG_POLICY_SET;
	return EOK;
}
/*[[[end:libc_pthread_attr_setschedpolicy]]]*/

/*[[[head:libc_pthread_attr_getinheritsched,hash:CRC-32=0x19e586a]]]*/
/* Return in *INHERIT the scheduling inheritance mode of *ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getinheritsched)(pthread_attr_t const *__restrict attr,
                                                        int *__restrict inherit)
/*[[[body:libc_pthread_attr_getinheritsched]]]*/
{
	struct pthread_attr const *at;
	at = (struct pthread_attr const *)attr;
	*inherit = (at->pa_flags & ATTR_FLAG_NOTINHERITSCHED
	            ? PTHREAD_EXPLICIT_SCHED
	            : PTHREAD_INHERIT_SCHED);
	return EOK;
}
/*[[[end:libc_pthread_attr_getinheritsched]]]*/

/*[[[head:libc_pthread_attr_setinheritsched,hash:CRC-32=0x3767d013]]]*/
/* Set scheduling inheritance mode in *ATTR according to INHERIT */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setinheritsched)(pthread_attr_t *attr,
                                                        int inherit)
/*[[[body:libc_pthread_attr_setinheritsched]]]*/
{
	struct pthread_attr *at;
	at = (struct pthread_attr *)attr;
	if (inherit == PTHREAD_EXPLICIT_SCHED)
		at->pa_flags |= ATTR_FLAG_NOTINHERITSCHED;
	else if (inherit == PTHREAD_INHERIT_SCHED)
		at->pa_flags &= ~ATTR_FLAG_NOTINHERITSCHED;
	else {
		return EINVAL;
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_setinheritsched]]]*/

/*[[[head:libc_pthread_attr_getscope,hash:CRC-32=0x47992366]]]*/
/* Return in *SCOPE the scheduling contention scope of *ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getscope)(pthread_attr_t const *__restrict attr,
                                                 int *__restrict scope)
/*[[[body:libc_pthread_attr_getscope]]]*/
{
	struct pthread_attr *at;
	at = (struct pthread_attr *)attr;
	*scope = (at->pa_flags & ATTR_FLAG_SCOPEPROCESS
	          ? PTHREAD_SCOPE_PROCESS
	          : PTHREAD_SCOPE_SYSTEM);
	return EOK;
}
/*[[[end:libc_pthread_attr_getscope]]]*/

/*[[[head:libc_pthread_attr_setscope,hash:CRC-32=0xcb279dbb]]]*/
/* Set scheduling contention scope in *ATTR according to SCOPE */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setscope)(pthread_attr_t *attr,
                                                 int scope)
/*[[[body:libc_pthread_attr_setscope]]]*/
{
	struct pthread_attr *at;
	at = (struct pthread_attr *)attr;
	if (scope == PTHREAD_SCOPE_PROCESS)
		at->pa_flags |= ATTR_FLAG_SCOPEPROCESS;
	else if (scope == PTHREAD_SCOPE_SYSTEM)
		at->pa_flags &= ~ATTR_FLAG_SCOPEPROCESS;
	else {
		return EINVAL;
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_setscope]]]*/

/*[[[head:libc_pthread_attr_getstackaddr,hash:CRC-32=0xfad02ec6]]]*/
/* Return the previously set address for the stack */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_DEPRECATED("Use pthread_attr_getstack()") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstackaddr)(pthread_attr_t const *__restrict attr,
                                                     void **__restrict stackaddr)
/*[[[body:libc_pthread_attr_getstackaddr]]]*/
{
	struct pthread_attr const *at;
	at = (struct pthread_attr const *)attr;
	*stackaddr = at->pa_stackaddr;
	return EOK;
}
/*[[[end:libc_pthread_attr_getstackaddr]]]*/

/*[[[head:libc_pthread_attr_setstackaddr,hash:CRC-32=0x7d3ed696]]]*/
/* Set the starting address of the stack of the thread to be created.
 * Depending on whether the stack grows up or down the value must either
 * be higher or lower than all the address in the memory block. The
 * minimal size of the block must be PTHREAD_STACK_MIN */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_DEPRECATED("Use pthread_attr_setstack()") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setstackaddr)(pthread_attr_t *attr,
                                                     void *stackaddr)
/*[[[body:libc_pthread_attr_setstackaddr]]]*/
{
	struct pthread_attr *at;
	at = (struct pthread_attr *)attr;
	at->pa_stackaddr = stackaddr;
	at->pa_flags |= ATTR_FLAG_STACKADDR;
	return EOK;
}
/*[[[end:libc_pthread_attr_setstackaddr]]]*/

/*[[[head:libc_pthread_attr_getstacksize,hash:CRC-32=0xa1b99a41]]]*/
/* Return the currently used minimal stack size */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstacksize)(pthread_attr_t const *__restrict attr,
                                                     size_t *__restrict stacksize)
/*[[[body:libc_pthread_attr_getstacksize]]]*/
{
	struct pthread_attr const *at;
	at = (struct pthread_attr const *)attr;
	*stacksize = at->pa_stacksize;
	return EOK;
}
/*[[[end:libc_pthread_attr_getstacksize]]]*/

/*[[[head:libc_pthread_attr_setstacksize,hash:CRC-32=0x5d6cef8c]]]*/
/* Add information about the minimum stack size needed for the thread
 * to be started. This size must never be less than PTHREAD_STACK_MIN
 * and must also not exceed the system limits */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setstacksize)(pthread_attr_t *attr,
                                                     size_t stacksize)
/*[[[body:libc_pthread_attr_setstacksize]]]*/
{
	struct pthread_attr *at;
	at = (struct pthread_attr *)attr;
	if unlikely(stacksize < PTHREAD_STACK_MIN)
		return EINVAL;
	at->pa_stacksize = stacksize;
	return EOK;
}
/*[[[end:libc_pthread_attr_setstacksize]]]*/

/*[[[head:libc_pthread_attr_getstack,hash:CRC-32=0x49bc1fc9]]]*/
/* Return the previously set address for the stack */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getstack)(pthread_attr_t const *__restrict attr,
                                                 void **__restrict stackaddr,
                                                 size_t *__restrict stacksize)
/*[[[body:libc_pthread_attr_getstack]]]*/
{
	struct pthread_attr *at;
	at = (struct pthread_attr *)attr;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
	*stackaddr = (byte_t *)at->pa_stackaddr - at->pa_stacksize;
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
	*stackaddr = at->pa_stackaddr;
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
	*stacksize = at->pa_stacksize;
	return EOK;
}
/*[[[end:libc_pthread_attr_getstack]]]*/

/*[[[head:libc_pthread_attr_setstack,hash:CRC-32=0x899dcd11]]]*/
/* The following two interfaces are intended to replace the last two. They
 * require setting the address as well as the size since only setting the
 * address will make the implementation on some architectures impossible */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setstack)(pthread_attr_t *attr,
                                                 void *stackaddr,
                                                 size_t stacksize)
/*[[[body:libc_pthread_attr_setstack]]]*/
{
	struct pthread_attr *at;
	at = (struct pthread_attr *)attr;
	if (stacksize < PTHREAD_STACK_MIN)
		return EINVAL;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
	at->pa_stackaddr = (byte_t *)stackaddr + at->pa_stacksize;
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
	at->pa_stackaddr = stackaddr;
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
	at->pa_stacksize = stacksize;
	at->pa_flags |= ATTR_FLAG_STACKADDR;
	return EOK;
}
/*[[[end:libc_pthread_attr_setstack]]]*/

/*[[[head:libc_pthread_attr_setaffinity_np,hash:CRC-32=0xff0fa043]]]*/
/* Thread created with attribute ATTR will be limited to run only on
 * the processors represented in CPUSET */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_setaffinity_np)(pthread_attr_t *attr,
                                                       size_t cpusetsize,
                                                       cpu_set_t const *cpuset)
/*[[[body:libc_pthread_attr_setaffinity_np]]]*/
{
	struct pthread_attr *at;
	at = (struct pthread_attr *)attr;
	/* Truncate the cpu set */
	while (cpusetsize && ((byte_t *)cpuset)[cpusetsize - 1] == 0)
		--cpusetsize;
	if (!cpusetsize || !cpuset) {
		/* NOTE: Glibc also accepts a zero-value in either argument as indicator
		 *       to clear out a previously set affinity, even though it would make
		 *       more sense to only allow `cpusetsize == 0', and require a non-NULL
		 *       `cpuset' when `cpusetsize != 0'... */
		if (at->pa_cpuset != (cpu_set_t *)&at->pa_cpusetsize)
			free(at->pa_cpuset);
		at->pa_cpuset     = NULL;
		at->pa_cpusetsize = 0;
	} else if (cpusetsize <= sizeof(at->pa_cpusetsize)) {
		/* Optimization: Don't use the heap for small cpu sets.
		 * In practice, this means that we usually always get here,
		 * since most machines don't have more than 32 cpus... */
		if (at->pa_cpuset != (cpu_set_t *)&at->pa_cpusetsize) {
			free(at->pa_cpuset);
			at->pa_cpuset = (cpu_set_t *)&at->pa_cpusetsize;
		}
		memset(&at->pa_cpusetsize, 0, sizeof(at->pa_cpusetsize));
		memcpy(&at->pa_cpusetsize, cpuset, cpusetsize);
	} else {
		cpu_set_t *newset;
		if (at->pa_cpuset == (cpu_set_t *)&at->pa_cpusetsize) {
			newset = (cpu_set_t *)malloc(cpusetsize);
			if unlikely(!newset)
				return ENOMEM;
			goto use_newset;
		} else if (cpusetsize != at->pa_cpusetsize) {
			newset = (cpu_set_t *)realloc(at->pa_cpuset,
			                              cpusetsize);
			if unlikely(!newset)
				return ENOMEM;
use_newset:
			at->pa_cpuset     = newset;
			at->pa_cpusetsize = cpusetsize;
		}
		memcpy(at->pa_cpuset, cpuset, cpusetsize);
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_setaffinity_np]]]*/

/*[[[head:libc_pthread_attr_getaffinity_np,hash:CRC-32=0x28a42da6]]]*/
/* Get bit set in CPUSET representing the processors threads created with ATTR can run on */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_attr_getaffinity_np)(pthread_attr_t const *attr,
                                                       size_t cpusetsize,
                                                       cpu_set_t *cpuset)
/*[[[body:libc_pthread_attr_getaffinity_np]]]*/
{
	struct pthread_attr const *at;
	at = (struct pthread_attr const *)attr;
	if (at->pa_cpuset) {
		size_t setsize;
		byte_t *p;
		setsize = at->pa_cpusetsize;
		if (at->pa_cpuset == (cpu_set_t *)&at->pa_cpusetsize) {
			setsize = sizeof(at->pa_cpusetsize);
			while (setsize && ((byte_t *)at->pa_cpuset)[setsize - 1] == 0)
				--setsize;
		}
		/* Check if the given buffer is too small. */
		if (cpusetsize < setsize)
			return EINVAL; /* GLibc returns EINVAL here (I would have used ERANGE for this, but whatever...) */
		p = (byte_t *)mempcpy(cpuset, at->pa_cpuset, setsize);
		/* Fill in the remainder with zeroes */
		memset(p, 0, cpusetsize - setsize);
	} else {
		/* No affinity set defined -> All cpus may be used. */
		memset(cpuset, 0xff, cpusetsize);
	}
	return EOK;
}
/*[[[end:libc_pthread_attr_getaffinity_np]]]*/

/*[[[head:libc_pthread_getattr_default_np,hash:CRC-32=0xa94711b7]]]*/
/* Get the default attributes used by pthread_create in this process */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getattr_default_np)(pthread_attr_t *attr)
/*[[[body:libc_pthread_getattr_default_np]]]*/
{
	struct pthread_attr *at;
	cpu_set_t *cpuset = NULL;
	size_t cpuset_size = 0;
	at = (struct pthread_attr *)attr;
again:
	atomic_rwlock_read(&pthread_default_attr_lock);
	memcpy(at, &pthread_default_attr, sizeof(struct pthread_attr));
	if (pthread_default_attr.pa_cpuset) {
		if (pthread_default_attr.pa_cpuset == (cpu_set_t *)&pthread_default_attr.pa_cpusetsize) {
			at->pa_cpuset = (cpu_set_t *)&at->pa_cpusetsize;
		} else if (cpuset_size != pthread_default_attr.pa_cpusetsize) {
			cpuset_size = pthread_default_attr.pa_cpusetsize;
			atomic_rwlock_endread(&pthread_default_attr_lock);
			cpuset = (cpu_set_t *)realloc(cpuset, cpuset_size);
			if unlikely(!cpuset)
				return ENOMEM;
			goto again;
		}
		at->pa_cpuset     = cpuset;
		at->pa_cpusetsize = cpuset_size;
		cpuset            = NULL; /* Don't free() below */
	}
	atomic_rwlock_endread(&pthread_default_attr_lock);
	if (at->pa_stacksize == 0)
		at->pa_stacksize = PTHREAD_STACK_MIN;
	free(cpuset);
	__STATIC_IF(sizeof(pthread_attr_t) > sizeof(struct pthread_attr)) {
		memset((byte_t *)at + sizeof(struct pthread_attr), 0x00,
		       sizeof(pthread_attr_t) - sizeof(struct pthread_attr));
	}
	return EOK;
}
/*[[[end:libc_pthread_getattr_default_np]]]*/

/*[[[head:libc_pthread_setattr_default_np,hash:CRC-32=0x9335d86a]]]*/
/* Set the default attributes to be used by pthread_create in this process */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setattr_default_np)(pthread_attr_t const *attr)
/*[[[body:libc_pthread_setattr_default_np]]]*/
{
	struct pthread_attr *at;
	cpu_set_t *old_set = NULL;
	cpu_set_t *new_set = NULL;
	size_t new_set_size = 0;
	at = (struct pthread_attr *)attr;
	if (at->pa_cpuset &&
	    at->pa_cpuset != (cpu_set_t *)&at->pa_cpusetsize) {
		new_set_size = at->pa_cpusetsize;
		new_set      = (cpu_set_t *)malloc(at->pa_cpusetsize);
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
	} else if (at->pa_cpuset) {
		/* Copy small affinity set */
		assert(at->pa_cpuset == (cpu_set_t *)&at->pa_cpusetsize);
		pthread_default_attr.pa_cpuset     = (cpu_set_t *)&pthread_default_attr.pa_cpusetsize;
		pthread_default_attr.pa_cpusetsize = at->pa_cpusetsize;
	} else {
		/* Clear affinity */
		pthread_default_attr.pa_cpuset     = NULL;
		pthread_default_attr.pa_cpusetsize = 0;
	}
	pthread_default_attr.pa_schedparam  = at->pa_schedparam;
	pthread_default_attr.pa_schedpolicy = at->pa_schedpolicy;
	pthread_default_attr.pa_flags       = at->pa_flags;
	pthread_default_attr.pa_guardsize   = at->pa_guardsize;
	pthread_default_attr.pa_stackaddr   = at->pa_stackaddr;
	pthread_default_attr.pa_stacksize   = at->pa_stacksize;
	atomic_rwlock_endwrite(&pthread_default_attr_lock);
	free(old_set);
	return EOK;
}
/*[[[end:libc_pthread_setattr_default_np]]]*/

/*[[[head:libc_pthread_getattr_np,hash:CRC-32=0x20b63fd7]]]*/
/* Initialize thread attribute *ATTR with attributes corresponding to the
 * already running thread THREAD. It shall be called on uninitialized ATTR
 * and destroyed with pthread_attr_destroy when no longer needed */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getattr_np)(pthread_t pthread,
                                              pthread_attr_t *attr)
/*[[[body:libc_pthread_getattr_np]]]*/
{
	errno_t result;
	struct pthread *pt = (struct pthread *)pthread;
	struct pthread_attr *at = (struct pthread_attr *)attr;
	result = pthread_getschedparam(pthread, &at->pa_schedpolicy, &at->pa_schedparam);
	if (result != EOK)
		goto done;
	if (pt->pt_flags & PTHREAD_FNOSTACK) {
		at->pa_stackaddr = NULL;
		at->pa_stacksize = 0;
	} else {
		at->pa_stackaddr = pt->pt_stackaddr;
		at->pa_stacksize = pt->pt_stacksize;
	}
	at->pa_guardsize = getpagesize();
	at->pa_flags = ATTR_FLAG_SCHED_SET | ATTR_FLAG_POLICY_SET;
	if (pt->pt_flags & PTHREAD_FUSERSTACK)
		at->pa_flags |= ATTR_FLAG_STACKADDR;
	at->pa_cpuset = (cpu_set_t *)&at->pa_cpusetsize;
	result = pthread_getaffinity_np(pthread,
	                                sizeof(at->pa_cpusetsize),
	                                at->pa_cpuset);
	if (result != ESRCH) {
		/* Buffer too small. */
		cpu_set_t *buf = NULL, *newbuf;
		size_t bufsize = sizeof(at->pa_cpusetsize) * 2;
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
					at->pa_cpuset     = NULL;
					at->pa_cpusetsize = 0;
				} else {
					newbuf = (cpu_set_t *)realloc(buf, bufsize);
					if likely(newbuf)
						buf = newbuf;
					at->pa_cpuset     = buf;
					at->pa_cpusetsize = bufsize;
				}
				goto done;
			}
			if (result != EINVAL)
				break;
			bufsize *= 2;
		} while (bufsize < sizeof(at->pa_cpusetsize) * 512);
		free(buf);
	}
done:
	return result;
}
/*[[[end:libc_pthread_getattr_np]]]*/

/*[[[head:libc_pthread_setschedparam,hash:CRC-32=0x69e108de]]]*/
/* Set the scheduling parameters for TARGET_THREAD according to POLICY and *PARAM */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((3)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setschedparam)(pthread_t target_thread,
                                                 int policy,
                                                 struct sched_param const *param)
/*[[[body:libc_pthread_setschedparam]]]*/
{
	errno_t result;
	struct pthread *pt = (struct pthread *)target_thread;
	pid_t tid = ATOMIC_READ(pt->pt_tid);
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
	if unlikely(ATOMIC_READ(pt->pt_tid) == 0) {
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

/*[[[head:libc_pthread_getschedparam,hash:CRC-32=0x56db8c50]]]*/
/* Return in *POLICY and *PARAM the scheduling parameters for TARGET_THREAD */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((2, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getschedparam)(pthread_t target_thread,
                                                 int *__restrict policy,
                                                 struct sched_param *__restrict param)
/*[[[body:libc_pthread_getschedparam]]]*/
{
	errno_t result;
	struct pthread *pt = (struct pthread *)target_thread;
	pid_t tid = ATOMIC_READ(pt->pt_tid);
	syscall_slong_t sys_policy;
	if unlikely(tid == 0)
		return ESRCH; /* The given thread has already terminated. */
	sys_policy = sys_sched_getscheduler(tid);
	if unlikely(E_ISERR(sys_policy))
		return (errno_t)-sys_policy;
	*policy = sys_policy;
	result = sys_sched_getparam(tid, param);
	if unlikely(E_ISERR(result))
		return (errno_t)-result;
	if unlikely(ATOMIC_READ(pt->pt_tid) == 0) {
		/* The thread has terminated in the mean time.
		 * Note: This is a race condition that Glibc
		 *       doesn't even check and simply ignores! */
		return ESRCH;
	}
	return EOK;
}
/*[[[end:libc_pthread_getschedparam]]]*/

/*[[[head:libc_pthread_setschedprio,hash:CRC-32=0x9bde5ea6]]]*/
/* Set the scheduling priority for TARGET_THREAD */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setschedprio)(pthread_t target_thread,
                                                int prio)
/*[[[body:libc_pthread_setschedprio]]]*/
{
	errno_t error;
	syscall_slong_t old_prio;
	struct pthread *pt = (struct pthread *)target_thread;
	pid_t tid = ATOMIC_READ(pt->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	old_prio = sys_getpriority(PRIO_PROCESS, tid);
	if unlikely(E_ISERR(old_prio))
		return (errno_t)-old_prio;
	error = sys_setpriority(PRIO_PROCESS, tid, (syscall_ulong_t)(20 - prio));
	if unlikely(E_ISERR(error))
		return (errno_t)-error;
	if unlikely(ATOMIC_READ(pt->pt_tid) == 0) {
		/* The thread has terminated in the mean time.
		 * Note: This is a race condition that Glibc
		 *       doesn't even check and simply ignores! */
		sys_setpriority(PRIO_PROCESS, tid, old_prio);
		return ESRCH;
	}
	return EOK;
}
/*[[[end:libc_pthread_setschedprio]]]*/

/*[[[head:libc_pthread_getname_np,hash:CRC-32=0xa13aacbb]]]*/
/* Get thread name visible in the kernel and its interfaces */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getname_np)(pthread_t target_thread,
                                              char *buf,
                                              size_t buflen)
/*[[[body:libc_pthread_getname_np]]]*/
{
	struct pthread *pt = (struct pthread *)target_thread;
	pid_t tid = ATOMIC_READ(pt->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	if unlikely(snprintf(buf, buflen, "tid{%u}", tid) >= buflen)
		return ERANGE;
	if unlikely(ATOMIC_READ(pt->pt_tid) == 0)
		return ESRCH;
	return EOK;
}
/*[[[end:libc_pthread_getname_np]]]*/

/*[[[head:libc_pthread_setname_np,hash:CRC-32=0x75efdc0b]]]*/
/* Set thread name visible in the kernel and its interfaces */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setname_np)(pthread_t target_thread,
                                              const char *name)
/*[[[body:libc_pthread_setname_np]]]*/
{
	struct pthread *pt = (struct pthread *)target_thread;
	pid_t tid = ATOMIC_READ(pt->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	COMPILER_IMPURE();
	/* Unsupported */
	(void)name;
	return ENOSYS;
}
/*[[[end:libc_pthread_setname_np]]]*/

PRIVATE ATTR_SECTION(".bss.crt.sched.pthread.pthread_concurrency_level") int pthread_concurrency_level = 0;

/*[[[head:libc_pthread_getconcurrency,hash:CRC-32=0x6cd2b98f]]]*/
/* Determine level of concurrency */
INTERN ATTR_SECTION(".text.crt.sched.pthread") ATTR_PURE int
NOTHROW_NCX(LIBCCALL libc_pthread_getconcurrency)(void)
/*[[[body:libc_pthread_getconcurrency]]]*/
{
	return pthread_concurrency_level;
}
/*[[[end:libc_pthread_getconcurrency]]]*/

/*[[[head:libc_pthread_setconcurrency,hash:CRC-32=0x8acf8b81]]]*/
/* Set new concurrency level to LEVEL */
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

/*[[[head:libc_pthread_setaffinity_np,hash:CRC-32=0x50617ae7]]]*/
/* Limit specified thread THREAD to run only on the processors represented in CPUSET */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((3)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_setaffinity_np)(pthread_t pthread,
                                                  size_t cpusetsize,
                                                  cpu_set_t const *cpuset)
/*[[[body:libc_pthread_setaffinity_np]]]*/
{
	errno_t error;
	struct pthread *pt = (struct pthread *)pthread;
	size_t old_cpusetsize;
	cpu_set_t *old_cpuset = (cpu_set_t *)&old_cpusetsize;
	pid_t tid = ATOMIC_READ(pt->pt_tid);
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
		if unlikely(ATOMIC_READ(pt->pt_tid) == 0) {
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

/*[[[head:libc_pthread_getaffinity_np,hash:CRC-32=0x86b95e89]]]*/
/* Get bit set in CPUSET representing the processors THREAD can run on */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((3)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_getaffinity_np)(pthread_t pthread,
                                                  size_t cpusetsize,
                                                  cpu_set_t *cpuset)
/*[[[body:libc_pthread_getaffinity_np]]]*/
{
	errno_t error;
	struct pthread *pt = (struct pthread *)pthread;
	pid_t tid = ATOMIC_READ(pt->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	error = sys_sched_getaffinity(tid, cpusetsize, cpuset);
	if (E_ISOK(error)) {
		if unlikely(ATOMIC_READ(pt->pt_tid) == 0) {
			/* The thread has terminated in the mean time.
			 * Note: This is a race condition that Glibc
			 *       doesn't even check and simply ignores! */
			error = -ESRCH;
		}
	}
	return (errno_t)-error;
}
/*[[[end:libc_pthread_getaffinity_np]]]*/


/*[[[head:libc_pthread_setcancelstate,hash:CRC-32=0x523f272c]]]*/
/* Set cancelability state of current thread to STATE,
 * returning old state in *OLDSTATE if OLDSTATE is not NULL */
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

/*[[[head:libc_pthread_setcanceltype,hash:CRC-32=0xc4ab7a94]]]*/
/* Set cancellation state of current thread to TYPE, returning the old
 * type in *OLDTYPE if OLDTYPE is not NULL */
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

/*[[[head:libc_pthread_cancel,hash:CRC-32=0x22cad0a3]]]*/
/* Cancel THREAD immediately or at the next possibility */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cancel)(pthread_t pthread)
/*[[[body:libc_pthread_cancel]]]*/
{
	struct pthread *pt = (struct pthread *)pthread;
	pid_t tid;
	/* Make sure that we can load librpc */
	if (!librpc_init())
		return ENOSYS;
	tid = ATOMIC_READ(pt->pt_tid);
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
	if ((*pdyn_rpc_schedule)(tid, RPC_SCHEDULE_SYNC, (void (*)())&pthread_cancel_self, 0) != 0)
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

/*[[[head:libc_pthread_mutex_init,hash:CRC-32=0x619c6ca8]]]*/
/* Initialize a mutex */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_init)(pthread_mutex_t *mutex,
                                              pthread_mutexattr_t const *mutexattr)
/*[[[body:libc_pthread_mutex_init]]]*/
/*AUTO*/{
	(void)mutex;
	(void)mutexattr;
	CRT_UNIMPLEMENTEDF("pthread_mutex_init(%p, %p)", mutex, mutexattr); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutex_init]]]*/

/*[[[head:libc_pthread_mutex_destroy,hash:CRC-32=0x492563e1]]]*/
/* Destroy a mutex */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_destroy)(pthread_mutex_t *mutex)
/*[[[body:libc_pthread_mutex_destroy]]]*/
/*AUTO*/{
	(void)mutex;
	CRT_UNIMPLEMENTEDF("pthread_mutex_destroy(%p)", mutex); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutex_destroy]]]*/

/*[[[head:libc_pthread_mutex_trylock,hash:CRC-32=0x20a97c8f]]]*/
/* Try locking a mutex */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_trylock)(pthread_mutex_t *mutex)
/*[[[body:libc_pthread_mutex_trylock]]]*/
/*AUTO*/{
	(void)mutex;
	CRT_UNIMPLEMENTEDF("pthread_mutex_trylock(%p)", mutex); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutex_trylock]]]*/

/*[[[head:libc_pthread_mutex_lock,hash:CRC-32=0x9eceef88]]]*/
/* Lock a mutex */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_lock)(pthread_mutex_t *mutex)
/*[[[body:libc_pthread_mutex_lock]]]*/
/*AUTO*/{
	(void)mutex;
	CRT_UNIMPLEMENTEDF("pthread_mutex_lock(%p)", mutex); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutex_lock]]]*/

/*[[[head:libc_pthread_mutex_timedlock,hash:CRC-32=0x1a85bc8e]]]*/
/* Wait until lock becomes available, or specified time passes */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_mutex_timedlock)(pthread_mutex_t *__restrict mutex,
                                                   struct timespec const *__restrict abstime)
/*[[[body:libc_pthread_mutex_timedlock]]]*/
{
	(void)mutex;
	(void)abstime;
	CRT_UNIMPLEMENTED("pthread_mutex_timedlock"); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutex_timedlock]]]*/

/*[[[head:libc_pthread_mutex_timedlock64,hash:CRC-32=0x3e503bfd]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_mutex_timedlock64, libc_pthread_mutex_timedlock);
#else /* MAGIC:alias */
/* Wait until lock becomes available, or specified time passes */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_mutex_timedlock64)(pthread_mutex_t *__restrict mutex,
                                                     struct timespec64 const *__restrict abstime)
/*[[[body:libc_pthread_mutex_timedlock64]]]*/
{
	(void)mutex;
	(void)abstime;
	CRT_UNIMPLEMENTED("pthread_mutex_timedlock64"); /* TODO */
	return ENOSYS;
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_mutex_timedlock64]]]*/

/*[[[head:libc_pthread_mutex_unlock,hash:CRC-32=0x4e7b6b17]]]*/
/* Unlock a mutex */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_unlock)(pthread_mutex_t *mutex)
/*[[[body:libc_pthread_mutex_unlock]]]*/
/*AUTO*/{
	(void)mutex;
	CRT_UNIMPLEMENTEDF("pthread_mutex_unlock(%p)", mutex); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutex_unlock]]]*/

/*[[[head:libc_pthread_mutex_getprioceiling,hash:CRC-32=0xe04c4917]]]*/
/* Get the priority ceiling of MUTEX */
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

/*[[[head:libc_pthread_mutex_setprioceiling,hash:CRC-32=0x34d167da]]]*/
/* Set the priority ceiling of MUTEX to PRIOCEILING, return old
 * priority ceiling value in *OLD_CEILING */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 3)) errno_t
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

/*[[[head:libc_pthread_mutex_consistent,hash:CRC-32=0x11df48b1]]]*/
/* Declare the state protected by MUTEX as consistent */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutex_consistent)(pthread_mutex_t *mutex)
/*[[[body:libc_pthread_mutex_consistent]]]*/
/*AUTO*/{
	(void)mutex;
	CRT_UNIMPLEMENTEDF("pthread_mutex_consistent(%p)", mutex); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutex_consistent]]]*/

/*[[[head:libc_pthread_mutexattr_init,hash:CRC-32=0x4da140af]]]*/
/* Initialize mutex attribute object ATTR with default attributes (kind is PTHREAD_MUTEX_TIMED_NP) */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_init)(pthread_mutexattr_t *attr)
/*[[[body:libc_pthread_mutexattr_init]]]*/
/*AUTO*/{
	(void)attr;
	CRT_UNIMPLEMENTEDF("pthread_mutexattr_init(%p)", attr); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutexattr_init]]]*/

/*[[[head:libc_pthread_mutexattr_destroy,hash:CRC-32=0xcf9878a4]]]*/
/* Destroy mutex attribute object ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_destroy)(pthread_mutexattr_t *attr)
/*[[[body:libc_pthread_mutexattr_destroy]]]*/
/*AUTO*/{
	(void)attr;
	CRT_UNIMPLEMENTEDF("pthread_mutexattr_destroy(%p)", attr); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutexattr_destroy]]]*/

/*[[[head:libc_pthread_mutexattr_getpshared,hash:CRC-32=0x5a0c3a2d]]]*/
/* Get the process-shared flag of the mutex attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getpshared)(pthread_mutexattr_t const *__restrict attr,
                                                        int *__restrict pshared)
/*[[[body:libc_pthread_mutexattr_getpshared]]]*/
/*AUTO*/{
	(void)attr;
	(void)pshared;
	CRT_UNIMPLEMENTEDF("pthread_mutexattr_getpshared(%p, %p)", attr, pshared); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutexattr_getpshared]]]*/

/*[[[head:libc_pthread_mutexattr_setpshared,hash:CRC-32=0x8e60bbdb]]]*/
/* Set the process-shared flag of the mutex attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setpshared)(pthread_mutexattr_t *attr,
                                                        int pshared)
/*[[[body:libc_pthread_mutexattr_setpshared]]]*/
/*AUTO*/{
	(void)attr;
	(void)pshared;
	CRT_UNIMPLEMENTEDF("pthread_mutexattr_setpshared(%p, %x)", attr, pshared); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutexattr_setpshared]]]*/

/*[[[head:libc_pthread_mutexattr_gettype,hash:CRC-32=0xaa303859]]]*/
/* Return in *KIND the mutex kind attribute in *ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_gettype)(pthread_mutexattr_t const *__restrict attr,
                                                     int *__restrict kind)
/*[[[body:libc_pthread_mutexattr_gettype]]]*/
/*AUTO*/{
	(void)attr;
	(void)kind;
	CRT_UNIMPLEMENTEDF("pthread_mutexattr_gettype(%p, %p)", attr, kind); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutexattr_gettype]]]*/

/*[[[head:libc_pthread_mutexattr_settype,hash:CRC-32=0x8588e7d2]]]*/
/* Set the mutex kind attribute in *ATTR to KIND (either PTHREAD_MUTEX_NORMAL,
 * PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK, or PTHREAD_MUTEX_DEFAULT) */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_settype)(pthread_mutexattr_t *attr,
                                                     int kind)
/*[[[body:libc_pthread_mutexattr_settype]]]*/
/*AUTO*/{
	(void)attr;
	(void)kind;
	CRT_UNIMPLEMENTEDF("pthread_mutexattr_settype(%p, %x)", attr, kind); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutexattr_settype]]]*/

/*[[[head:libc_pthread_mutexattr_getprotocol,hash:CRC-32=0x69882d2c]]]*/
/* Return in *PROTOCOL the mutex protocol attribute in *ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getprotocol)(pthread_mutexattr_t const *__restrict attr,
                                                         int *__restrict protocol)
/*[[[body:libc_pthread_mutexattr_getprotocol]]]*/
/*AUTO*/{
	(void)attr;
	(void)protocol;
	CRT_UNIMPLEMENTEDF("pthread_mutexattr_getprotocol(%p, %p)", attr, protocol); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutexattr_getprotocol]]]*/

/*[[[head:libc_pthread_mutexattr_setprotocol,hash:CRC-32=0x7f9f1adb]]]*/
/* Set the mutex protocol attribute in *ATTR to PROTOCOL (either
 * PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, or PTHREAD_PRIO_PROTECT) */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setprotocol)(pthread_mutexattr_t *attr,
                                                         int protocol)
/*[[[body:libc_pthread_mutexattr_setprotocol]]]*/
/*AUTO*/{
	(void)attr;
	(void)protocol;
	CRT_UNIMPLEMENTEDF("pthread_mutexattr_setprotocol(%p, %x)", attr, protocol); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutexattr_setprotocol]]]*/

/*[[[head:libc_pthread_mutexattr_getprioceiling,hash:CRC-32=0xb27d72ad]]]*/
/* Return in *PRIOCEILING the mutex prioceiling attribute in *ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getprioceiling)(pthread_mutexattr_t const *__restrict attr,
                                                            int *__restrict prioceiling)
/*[[[body:libc_pthread_mutexattr_getprioceiling]]]*/
/*AUTO*/{
	(void)attr;
	(void)prioceiling;
	CRT_UNIMPLEMENTEDF("pthread_mutexattr_getprioceiling(%p, %p)", attr, prioceiling); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutexattr_getprioceiling]]]*/

/*[[[head:libc_pthread_mutexattr_setprioceiling,hash:CRC-32=0x65fd4591]]]*/
/* Set the mutex prioceiling attribute in *ATTR to PRIOCEILING */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setprioceiling)(pthread_mutexattr_t *attr,
                                                            int prioceiling)
/*[[[body:libc_pthread_mutexattr_setprioceiling]]]*/
/*AUTO*/{
	(void)attr;
	(void)prioceiling;
	CRT_UNIMPLEMENTEDF("pthread_mutexattr_setprioceiling(%p, %x)", attr, prioceiling); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutexattr_setprioceiling]]]*/

/*[[[head:libc_pthread_mutexattr_getrobust,hash:CRC-32=0x6a4ae918]]]*/
/* Get the robustness flag of the mutex attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_getrobust)(pthread_mutexattr_t const *attr,
                                                       int *robustness)
/*[[[body:libc_pthread_mutexattr_getrobust]]]*/
/*AUTO*/{
	(void)attr;
	(void)robustness;
	CRT_UNIMPLEMENTEDF("pthread_mutexattr_getrobust(%p, %p)", attr, robustness); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutexattr_getrobust]]]*/

/*[[[head:libc_pthread_mutexattr_setrobust,hash:CRC-32=0x8013fdd3]]]*/
/* Set the robustness flag of the mutex attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_mutexattr_setrobust)(pthread_mutexattr_t *attr,
                                                       int robustness)
/*[[[body:libc_pthread_mutexattr_setrobust]]]*/
/*AUTO*/{
	(void)attr;
	(void)robustness;
	CRT_UNIMPLEMENTEDF("pthread_mutexattr_setrobust(%p, %x)", attr, robustness); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_mutexattr_setrobust]]]*/

/*[[[head:libc_pthread_rwlock_init,hash:CRC-32=0x8e25e380]]]*/
/* Initialize read-write lock RWLOCK using attributes ATTR,
 * or use the default values if later is NULL */
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

/*[[[head:libc_pthread_rwlock_destroy,hash:CRC-32=0x3ee812fa]]]*/
/* Destroy read-write lock RWLOCK */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_destroy)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_destroy]]]*/
/*AUTO*/{
	(void)rwlock;
	CRT_UNIMPLEMENTEDF("pthread_rwlock_destroy(%p)", rwlock); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_destroy]]]*/

/*[[[head:libc_pthread_rwlock_rdlock,hash:CRC-32=0x9d9202e4]]]*/
/* Acquire read lock for RWLOCK */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_rdlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_rdlock]]]*/
/*AUTO*/{
	(void)rwlock;
	CRT_UNIMPLEMENTEDF("pthread_rwlock_rdlock(%p)", rwlock); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_rdlock]]]*/

/*[[[head:libc_pthread_rwlock_tryrdlock,hash:CRC-32=0x9f291145]]]*/
/* Try to acquire read lock for RWLOCK */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_tryrdlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_tryrdlock]]]*/
/*AUTO*/{
	(void)rwlock;
	CRT_UNIMPLEMENTEDF("pthread_rwlock_tryrdlock(%p)", rwlock); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_tryrdlock]]]*/

/*[[[head:libc_pthread_rwlock_timedrdlock,hash:CRC-32=0xce86de09]]]*/
/* Try to acquire read lock for RWLOCK or return after specfied time */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
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

/*[[[head:libc_pthread_rwlock_timedrdlock64,hash:CRC-32=0x6d900571]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_rwlock_timedrdlock64, libc_pthread_rwlock_timedrdlock);
#else /* MAGIC:alias */
/* Try to acquire read lock for RWLOCK or return after specfied time */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
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

/*[[[head:libc_pthread_rwlock_wrlock,hash:CRC-32=0xd9da4e75]]]*/
/* Acquire write lock for RWLOCK */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_rwlock_wrlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_wrlock]]]*/
/*AUTO*/{
	(void)rwlock;
	CRT_UNIMPLEMENTEDF("pthread_rwlock_wrlock(%p)", rwlock); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_wrlock]]]*/

/*[[[head:libc_pthread_rwlock_trywrlock,hash:CRC-32=0x8081848c]]]*/
/* Try to acquire write lock for RWLOCK */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_trywrlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_trywrlock]]]*/
/*AUTO*/{
	(void)rwlock;
	CRT_UNIMPLEMENTEDF("pthread_rwlock_trywrlock(%p)", rwlock); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_trywrlock]]]*/

/*[[[head:libc_pthread_rwlock_timedwrlock,hash:CRC-32=0x46a10515]]]*/
/* Try to acquire write lock for RWLOCK or return after specfied time */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
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

/*[[[head:libc_pthread_rwlock_timedwrlock64,hash:CRC-32=0x796fadf9]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_rwlock_timedwrlock64, libc_pthread_rwlock_timedwrlock);
#else /* MAGIC:alias */
/* Try to acquire write lock for RWLOCK or return after specfied time */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
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

/*[[[head:libc_pthread_rwlock_unlock,hash:CRC-32=0xee5386b6]]]*/
/* Unlock RWLOCK */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlock_unlock)(pthread_rwlock_t *rwlock)
/*[[[body:libc_pthread_rwlock_unlock]]]*/
/*AUTO*/{
	(void)rwlock;
	CRT_UNIMPLEMENTEDF("pthread_rwlock_unlock(%p)", rwlock); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlock_unlock]]]*/

/*[[[head:libc_pthread_rwlockattr_init,hash:CRC-32=0xec87be81]]]*/
/* Initialize attribute object ATTR with default values */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_init)(pthread_rwlockattr_t *attr)
/*[[[body:libc_pthread_rwlockattr_init]]]*/
/*AUTO*/{
	(void)attr;
	CRT_UNIMPLEMENTEDF("pthread_rwlockattr_init(%p)", attr); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlockattr_init]]]*/

/*[[[head:libc_pthread_rwlockattr_destroy,hash:CRC-32=0xa959ab92]]]*/
/* Destroy attribute object ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_destroy)(pthread_rwlockattr_t *attr)
/*[[[body:libc_pthread_rwlockattr_destroy]]]*/
/*AUTO*/{
	(void)attr;
	CRT_UNIMPLEMENTEDF("pthread_rwlockattr_destroy(%p)", attr); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlockattr_destroy]]]*/

/*[[[head:libc_pthread_rwlockattr_getpshared,hash:CRC-32=0x7b0a5b4d]]]*/
/* Return current setting of process-shared attribute of ATTR in PSHARED */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_getpshared)(pthread_rwlockattr_t const *__restrict attr,
                                                         int *__restrict pshared)
/*[[[body:libc_pthread_rwlockattr_getpshared]]]*/
/*AUTO*/{
	(void)attr;
	(void)pshared;
	CRT_UNIMPLEMENTEDF("pthread_rwlockattr_getpshared(%p, %p)", attr, pshared); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlockattr_getpshared]]]*/

/*[[[head:libc_pthread_rwlockattr_setpshared,hash:CRC-32=0xac9c9f00]]]*/
/* Set process-shared attribute of ATTR to PSHARED */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_setpshared)(pthread_rwlockattr_t *attr,
                                                         int pshared)
/*[[[body:libc_pthread_rwlockattr_setpshared]]]*/
/*AUTO*/{
	(void)attr;
	(void)pshared;
	CRT_UNIMPLEMENTEDF("pthread_rwlockattr_setpshared(%p, %x)", attr, pshared); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlockattr_setpshared]]]*/

/*[[[head:libc_pthread_rwlockattr_getkind_np,hash:CRC-32=0x79cd155a]]]*/
/* Return current setting of reader/writer preference */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_getkind_np)(pthread_rwlockattr_t const *__restrict attr,
                                                         int *__restrict pref)
/*[[[body:libc_pthread_rwlockattr_getkind_np]]]*/
/*AUTO*/{
	(void)attr;
	(void)pref;
	CRT_UNIMPLEMENTEDF("pthread_rwlockattr_getkind_np(%p, %p)", attr, pref); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlockattr_getkind_np]]]*/

/*[[[head:libc_pthread_rwlockattr_setkind_np,hash:CRC-32=0x277e2207]]]*/
/* Set reader/write preference */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_rwlockattr_setkind_np)(pthread_rwlockattr_t *attr,
                                                         int pref)
/*[[[body:libc_pthread_rwlockattr_setkind_np]]]*/
/*AUTO*/{
	(void)attr;
	(void)pref;
	CRT_UNIMPLEMENTEDF("pthread_rwlockattr_setkind_np(%p, %x)", attr, pref); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_rwlockattr_setkind_np]]]*/

/*[[[head:libc_pthread_cond_init,hash:CRC-32=0x7dd94e97]]]*/
/* Initialize condition variable COND using attributes ATTR, or use
 * the default values if later is NULL */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cond_init)(pthread_cond_t *__restrict cond,
                                             pthread_condattr_t const *__restrict cond_attr)
/*[[[body:libc_pthread_cond_init]]]*/
/*AUTO*/{
	(void)cond;
	(void)cond_attr;
	CRT_UNIMPLEMENTEDF("pthread_cond_init(%p, %p)", cond, cond_attr); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_cond_init]]]*/

/*[[[head:libc_pthread_cond_destroy,hash:CRC-32=0xb30efb73]]]*/
/* Destroy condition variable COND */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cond_destroy)(pthread_cond_t *cond)
/*[[[body:libc_pthread_cond_destroy]]]*/
/*AUTO*/{
	(void)cond;
	CRT_UNIMPLEMENTEDF("pthread_cond_destroy(%p)", cond); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_cond_destroy]]]*/

/*[[[head:libc_pthread_cond_signal,hash:CRC-32=0x546042f2]]]*/
/* Wake up one thread waiting for condition variable COND */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cond_signal)(pthread_cond_t *cond)
/*[[[body:libc_pthread_cond_signal]]]*/
/*AUTO*/{
	(void)cond;
	CRT_UNIMPLEMENTEDF("pthread_cond_signal(%p)", cond); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_cond_signal]]]*/

/*[[[head:libc_pthread_cond_broadcast,hash:CRC-32=0x35e18c3b]]]*/
/* Wake up all threads waiting for condition variables COND */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_cond_broadcast)(pthread_cond_t *cond)
/*[[[body:libc_pthread_cond_broadcast]]]*/
/*AUTO*/{
	(void)cond;
	CRT_UNIMPLEMENTEDF("pthread_cond_broadcast(%p)", cond); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_cond_broadcast]]]*/

/*[[[head:libc_pthread_cond_wait,hash:CRC-32=0xd3eb990f]]]*/
/* Wait for condition variable COND to be signaled or broadcast.
 * MUTEX is assumed to be locked before. */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_cond_wait)(pthread_cond_t *__restrict cond,
                                             pthread_mutex_t *__restrict mutex)
/*[[[body:libc_pthread_cond_wait]]]*/
/*AUTO*/{
	(void)cond;
	(void)mutex;
	CRT_UNIMPLEMENTEDF("pthread_cond_wait(%p, %p)", cond, mutex); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_cond_wait]]]*/

/*[[[head:libc_pthread_cond_timedwait,hash:CRC-32=0x88acf80a]]]*/
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2, 3)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_cond_timedwait)(pthread_cond_t *__restrict cond,
                                                  pthread_mutex_t *__restrict mutex,
                                                  struct timespec const *__restrict abstime)
/*[[[body:libc_pthread_cond_timedwait]]]*/
{
	(void)cond;
	(void)mutex;
	(void)abstime;
	CRT_UNIMPLEMENTED("pthread_cond_timedwait"); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_cond_timedwait]]]*/

/*[[[head:libc_pthread_cond_timedwait64,hash:CRC-32=0x7b9ceee0]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_pthread_cond_timedwait64, libc_pthread_cond_timedwait);
#else /* MAGIC:alias */
/* Wait for condition variable COND to be signaled or broadcast until
 * ABSTIME. MUTEX is assumed to be locked before. ABSTIME is an
 * absolute time specification; zero is the beginning of the epoch
 * (00:00:00 GMT, January 1, 1970). */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2, 3)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_cond_timedwait64)(pthread_cond_t *__restrict cond,
                                                    pthread_mutex_t *__restrict mutex,
                                                    struct timespec64 const *__restrict abstime)
/*[[[body:libc_pthread_cond_timedwait64]]]*/
{
	(void)cond;
	(void)mutex;
	(void)abstime;
	CRT_UNIMPLEMENTED("pthread_cond_timedwait64"); /* TODO */
	return ENOSYS;
}
#endif /* MAGIC:alias */
/*[[[end:libc_pthread_cond_timedwait64]]]*/

/*[[[head:libc_pthread_condattr_init,hash:CRC-32=0x2daa820f]]]*/
/* Initialize condition variable attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_init)(pthread_condattr_t *attr)
/*[[[body:libc_pthread_condattr_init]]]*/
/*AUTO*/{
	(void)attr;
	CRT_UNIMPLEMENTEDF("pthread_condattr_init(%p)", attr); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_condattr_init]]]*/

/*[[[head:libc_pthread_condattr_destroy,hash:CRC-32=0xd79bcf4b]]]*/
/* Destroy condition variable attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_destroy)(pthread_condattr_t *attr)
/*[[[body:libc_pthread_condattr_destroy]]]*/
/*AUTO*/{
	(void)attr;
	CRT_UNIMPLEMENTEDF("pthread_condattr_destroy(%p)", attr); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_condattr_destroy]]]*/

/*[[[head:libc_pthread_condattr_getpshared,hash:CRC-32=0xcb796c3f]]]*/
/* Get the process-shared flag of the condition variable attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_getpshared)(pthread_condattr_t const *__restrict attr,
                                                       int *__restrict pshared)
/*[[[body:libc_pthread_condattr_getpshared]]]*/
/*AUTO*/{
	(void)attr;
	(void)pshared;
	CRT_UNIMPLEMENTEDF("pthread_condattr_getpshared(%p, %p)", attr, pshared); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_condattr_getpshared]]]*/

/*[[[head:libc_pthread_condattr_setpshared,hash:CRC-32=0xbc71da02]]]*/
/* Set the process-shared flag of the condition variable attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_setpshared)(pthread_condattr_t *attr,
                                                       int pshared)
/*[[[body:libc_pthread_condattr_setpshared]]]*/
/*AUTO*/{
	(void)attr;
	(void)pshared;
	CRT_UNIMPLEMENTEDF("pthread_condattr_setpshared(%p, %x)", attr, pshared); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_condattr_setpshared]]]*/

/*[[[head:libc_pthread_condattr_getclock,hash:CRC-32=0x4b25dd51]]]*/
/* Get the clock selected for the condition variable attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_getclock)(pthread_condattr_t const *__restrict attr,
                                                     clockid_t *__restrict clock_id)
/*[[[body:libc_pthread_condattr_getclock]]]*/
/*AUTO*/{
	(void)attr;
	(void)clock_id;
	CRT_UNIMPLEMENTEDF("pthread_condattr_getclock(%p, %p)", attr, clock_id); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_condattr_getclock]]]*/

/*[[[head:libc_pthread_condattr_setclock,hash:CRC-32=0xe794578f]]]*/
/* Set the clock selected for the condition variable attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_condattr_setclock)(pthread_condattr_t *attr,
                                                     clockid_t clock_id)
/*[[[body:libc_pthread_condattr_setclock]]]*/
/*AUTO*/{
	(void)attr;
	(void)clock_id;
	CRT_UNIMPLEMENTEDF("pthread_condattr_setclock(%p, %" PRIxN(__SIZEOF_CLOCKID_T__) ")", attr, clock_id); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_condattr_setclock]]]*/

/*[[[head:libc_pthread_barrier_init,hash:CRC-32=0x90a55d0b]]]*/
/* Initialize BARRIER with the attributes in ATTR.
 * The barrier is opened when COUNT waiters arrived */
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

/*[[[head:libc_pthread_barrier_destroy,hash:CRC-32=0xf12d6538]]]*/
/* Destroy a previously dynamically initialized barrier BARRIER */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrier_destroy)(pthread_barrier_t *barrier)
/*[[[body:libc_pthread_barrier_destroy]]]*/
/*AUTO*/{
	(void)barrier;
	CRT_UNIMPLEMENTEDF("pthread_barrier_destroy(%p)", barrier); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_barrier_destroy]]]*/

/*[[[head:libc_pthread_barrier_wait,hash:CRC-32=0xe6b1bf8d]]]*/
/* Wait on barrier BARRIER */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_RPC(LIBCCALL libc_pthread_barrier_wait)(pthread_barrier_t *barrier)
/*[[[body:libc_pthread_barrier_wait]]]*/
/*AUTO*/{
	(void)barrier;
	CRT_UNIMPLEMENTEDF("pthread_barrier_wait(%p)", barrier); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_barrier_wait]]]*/

/*[[[head:libc_pthread_barrierattr_init,hash:CRC-32=0x2e599abc]]]*/
/* Initialize barrier attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_init)(pthread_barrierattr_t *attr)
/*[[[body:libc_pthread_barrierattr_init]]]*/
/*AUTO*/{
	(void)attr;
	CRT_UNIMPLEMENTEDF("pthread_barrierattr_init(%p)", attr); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_barrierattr_init]]]*/

/*[[[head:libc_pthread_barrierattr_destroy,hash:CRC-32=0x86580fdf]]]*/
/* Destroy previously dynamically initialized barrier attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_destroy)(pthread_barrierattr_t *attr)
/*[[[body:libc_pthread_barrierattr_destroy]]]*/
/*AUTO*/{
	(void)attr;
	CRT_UNIMPLEMENTEDF("pthread_barrierattr_destroy(%p)", attr); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_barrierattr_destroy]]]*/

/*[[[head:libc_pthread_barrierattr_getpshared,hash:CRC-32=0x98c9f760]]]*/
/* Get the process-shared flag of the barrier attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1, 2)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_getpshared)(pthread_barrierattr_t const *__restrict attr,
                                                          int *__restrict pshared)
/*[[[body:libc_pthread_barrierattr_getpshared]]]*/
/*AUTO*/{
	(void)attr;
	(void)pshared;
	CRT_UNIMPLEMENTEDF("pthread_barrierattr_getpshared(%p, %p)", attr, pshared); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_barrierattr_getpshared]]]*/

/*[[[head:libc_pthread_barrierattr_setpshared,hash:CRC-32=0x9e39543d]]]*/
/* Set the process-shared flag of the barrier attribute ATTR */
INTERN ATTR_SECTION(".text.crt.sched.pthread") NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_barrierattr_setpshared)(pthread_barrierattr_t *attr,
                                                          int pshared)
/*[[[body:libc_pthread_barrierattr_setpshared]]]*/
/*AUTO*/{
	(void)attr;
	(void)pshared;
	CRT_UNIMPLEMENTEDF("pthread_barrierattr_setpshared(%p, %x)", attr, pshared); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_barrierattr_setpshared]]]*/

/*[[[head:libc_pthread_key_create,hash:CRC-32=0xb78c6bd0]]]*/
/* Create a key value identifying a location in the thread-specific
 * data area. Each thread maintains a distinct thread-specific data
 * area. DESTR_FUNCTION, if non-NULL, is called with the value
 * associated to that key when the key is destroyed.
 * DESTR_FUNCTION is not called if the value associated is NULL when
 * the key is destroyed */
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

/*[[[head:libc_pthread_key_delete,hash:CRC-32=0xe7d715bb]]]*/
/* Destroy KEY */
INTERN ATTR_SECTION(".text.crt.sched.pthread") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_key_delete)(pthread_key_t key)
/*[[[body:libc_pthread_key_delete]]]*/
/*AUTO*/{
	(void)key;
	CRT_UNIMPLEMENTEDF("pthread_key_delete(%" PRIxN(__SIZEOF_PTHREAD_KEY_T) ")", key); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_pthread_key_delete]]]*/

/*[[[head:libc_pthread_getspecific,hash:CRC-32=0x2c316472]]]*/
/* Return current value of the thread-specific data slot identified by KEY */
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

/*[[[head:libc_pthread_setspecific,hash:CRC-32=0x19f7c4f7]]]*/
/* Store POINTER in the thread-specific data slot identified by KEY */
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

/*[[[head:libc_pthread_getcpuclockid,hash:CRC-32=0xfd701727]]]*/
/* Get ID of CPU-time clock for thread THREAD_ID */
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

/*[[[head:libc_pthread_atfork,hash:CRC-32=0xfd8f6d23]]]*/
/* Install handlers to be called when a new process is created with FORK.
 * The PREPARE handler is called in the parent process just before performing
 * FORK. The PARENT handler is called in the parent process just after FORK.
 * The CHILD handler is called in the child process. Each of the three
 * handlers can be NULL, meaning that no handler needs to be called at that
 * point.
 * PTHREAD_ATFORK can be called several times, in which case the PREPARE
 * handlers are called in LIFO order (last added with PTHREAD_ATFORK,
 * first called before FORK), and the PARENT and CHILD handlers are called
 * in FIFO (first added, first called) */
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
