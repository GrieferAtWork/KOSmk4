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
#ifndef GUARD_LIBC_USER_AIO_C
#define GUARD_LIBC_USER_AIO_C 1
#define _KOS_SOURCE 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sched/atomic-lock.h>

#include <kos/anno.h>
#include <kos/futex.h>
#include <kos/rpc.h>
#include <kos/syscalls.h>
#include <linux/futex.h>

#include <assert.h>
#include <fcntl.h>
#include <malloc.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>

/**/
#include "aio.h"

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#ifndef SYS_futex_time64
#define sys_futex_time64 sys_futex
#endif /* !SYS_futex_time64 */

#ifndef WEAK
#define WEAK __WEAK
#endif /* !WEAK */

#ifndef REF
#define REF __REF
#endif /* !REF */


/************************************************************************/
/* AIO Opcodes                                                          */
/************************************************************************/
#ifndef LIO_READ
#define LIO_READ  __LIO_READ  /* Perform an async `read(2)' or `pread(2)' */
#endif /* !LIO_READ */
#ifndef LIO_WRITE
#define LIO_WRITE __LIO_WRITE /* Perform an async `write(2)' or `pwrite(2)' */
#endif /* !LIO_WRITE */
#ifndef LIO_NOP
#define LIO_NOP   __LIO_NOP   /* No-op */
#endif /* !LIO_NOP */

#define _LIO_PUBLIC_OP_MAX LIO_READ
#if _LIO_PUBLIC_OP_MAX < LIO_WRITE
#undef _LIO_PUBLIC_OP_MAX
#define _LIO_PUBLIC_OP_MAX LIO_WRITE
#endif /* _LIO_PUBLIC_OP_MAX < LIO_WRITE */
#if _LIO_PUBLIC_OP_MAX < LIO_NOP
#undef _LIO_PUBLIC_OP_MAX
#define _LIO_PUBLIC_OP_MAX LIO_NOP
#endif /* _LIO_PUBLIC_OP_MAX < LIO_NOP */


/* Extended (internal) AIO opcodes. */
#define LIO_FSYNC     (_LIO_PUBLIC_OP_MAX + 1) /* Do `fsync(2)' */
#define LIO_FDATASYNC (_LIO_PUBLIC_OP_MAX + 2) /* Do `fdatasync(2)' */



/* Trigger the given signal event as the result of completing an AIO operation. */
PRIVATE NONNULL((1)) errno_t
NOTHROW_NCX(LIBCCALL sigevent_notify)(struct sigevent const *__restrict self) {
	errno_t result = EOK;
	switch (self->sigev_notify) {

	case SIGEV_INLINE_THREAD:
		(*self->sigev_notify_function)(self->sigev_value);
		break;

	case SIGEV_THREAD: {
		static_assert((sizeof(sigval_t) == sizeof(void *)));
		pthread_t p;
		pthread_attr_t _attr;
		pthread_attr_t *attr;
		attr = (pthread_attr_t *)self->sigev_notify_attributes;
		if (!attr) {
			result = pthread_attr_init(&_attr);
			if (result != EOK)
				break;
			result = pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_DETACHED);
			if (result != EOK) {
				pthread_attr_destroy(&_attr);
				break;
			}
			attr = &_attr;
		}

		/* Because sizeof(sigval_t) == sizeof(void *), and because the thread spawned
		 * here doesn't care about whatever its callback might return, we can  simply
		 * use the signal event function directly, even though it returns `void'! */
		result = pthread_create(&p, attr,
		                        (void *(LIBKCALL *)(void *))(void *)self->sigev_notify_function,
		                        self->sigev_value.sival_ptr);
		if (!self->sigev_notify_attributes)
			pthread_attr_destroy(&_attr);
	}	break;

	case SIGEV_SIGNAL:
	case SIGEV_THREAD_ID: {
		/* When `sigev_signo == 0', the below syscalls would become no-ops
		 * Or   rather,   would  "test if we're allowed to send a signal". */
		siginfo_t info;
		bzero(&info, sizeof(siginfo_t));
		info.si_signo = self->sigev_signo;
		info.si_code  = SI_ASYNCIO;
		info.si_pid   = getpid();
		info.si_uid   = getuid();
		info.si_value = self->sigev_value;
		if (self->sigev_notify == SIGEV_SIGNAL) {
			result = -sys_rt_sigqueueinfo(info.si_pid, info.si_signo, &info);
		} else {
			/* PORTABILITY WARNING: Support for this case isn't implemented by
			 *                      Glibc, which only supports `SIGEV_SIGNAL'! */
			result = -sys_rt_tgsigqueueinfo(info.si_pid, self->_sigev_tid,
			                                info.si_signo, &info);
		}
	}	break;

	default:
		break;
	}
	return result;
}


struct aio_set_completion {
	WEAK refcnt_t   asc_refcnt; /* Reference counter. */
	struct sigevent asc_event;  /* [const] Event triggered once `asc_refcnt' reaches `0' */
};

PRIVATE NONNULL((1)) void
NOTHROW_NCX(LIBCCALL aio_set_completion_decref)(struct aio_set_completion *__restrict self) {
	if (ATOMIC_DECFETCH(self->asc_refcnt) != 0)
		return;
	sigevent_notify(&self->asc_event);
	free(self);
}








/* AIO Status codes. The following transitions are allowed:
 *
 *  - AIO_STATUS_PENDING  ->  AIO_STATUS_CANCELING       // `aio_cancel(3)' was called.
 *  - AIO_STATUS_PENDING  ->  AIO_STATUS_RUNNING         // AIO worker thread is currently performing the operation
 *
 *  - AIO_STATUS_CANCELING ->  AIO_STATUS_REMOVED        // Once Removed from the pending list, and
 *                                                       // Completion actions have been performed.
 *
 *  - AIO_STATUS_RUNNING  -> AIO_STATUS_INTERRUPTING     // `aio_cancel(3)' was called.
 *                                                       // After this transition  is set, you  must send a  synchronous
 *                                                       // RPC to the AIO worker thread, thus causing the AIO operation
 *                                                       // to (possibly) fail with EINTR. When an operation fails  with
 *                                                       // this error, the  worker thread will  respond by checking  if
 *                                                       // the status is  `AIO_STATUS_INTERRUPTING', in  which case  it
 *                                                       // will  transition  to  `AIO_STATUS_REMOVED'.  If  the  status
 *                                                       // is anything different, the  interrupt will be considered  as
 *                                                       // sporadic and the operation will be re-attempted.
 *  - AIO_STATUS_RUNNING  -> AIO_STATUS_FINISHED         // Operation completed normally
 *
 *  - AIO_STATUS_FINISHED -> AIO_STATUS_COMPLETED        // Completion actions have been performed.
 *
 *  - AIO_STATUS_INTERRUPTING -> AIO_STATUS_REMOVED      // Async operation failed with `EINTR'. Transition is
 *                                                       // made after Completion actions have been performed.
 *  - AIO_STATUS_INTERRUPTING -> AIO_STATUS_COMPLETED    // Async operation completed before an interrupt could be
 *                                                       // received.  In this case, `aio_cancel(3)' should return
 *                                                       // with `AIO_ALLDONE'
 *
 *  - AIO_STATUS_COMPLETED -> AIO_STATUS_RETURN_READ     // `aio_return(3)' was called.
 *
 */

/* NOTE: `AIO_STATUS_PENDING != 0' so-as to guard against memset(0) usage. */
#define AIO_STATUS_PENDING      1 /* Initial status (`aio_link' is valid) */
#define AIO_STATUS_CANCELING    2 /* Cancel requested (`aio_link' is valid) */
#define AIO_STATUS_REMOVED      3 /* Removed from pending list after cancel.
                                   * NOTE: TERMINAL STATE; DON'T ACCESS STRUCT ONCE SET, UNLESS YOU OWN IT! */
#define AIO_STATUS_RUNNING      4 /* Operation is current being performed, or is about to start. */
#define AIO_STATUS_INTERRUPTING 5 /* An interrupt request was made */
#define AIO_STATUS_FINISHED     6 /* Operation completed (either with or without error) */
#define AIO_STATUS_COMPLETED    7 /* Operation completed (either with or without error)
                                   * NOTE: TERMINAL STATE; DON'T ACCESS STRUCT ONCE SET, UNLESS YOU OWN IT! */
#define AIO_STATUS_RETURN_READ  8 /* `aio_return(3)' was called. */

/* AIO flags */
#define AIO_FLAG_NORMAL  0x0000 /* Normal flags. */
#define AIO_FLAG_WAITERS 0x0001 /* When set, clear and broadcast a futex `&aio_status_and_flags'
                                 * when the  AIO descriptor  has completed  (either due  to  the
                                 * operation finishing, or being canceled). */




struct aio;
TAILQ_HEAD(aio_tailq, aio);
union aio_status {
	struct {
		uint16_t as_status; /* [lock(ATOMIC)] One of `AIO_STATUS_*' */
		uint16_t as_flags;  /* [lock(ATOMIC)] Set of `AIO_FLAG_*' */
	};
	uint32_t     as_word;   /* [lock(ATOMIC)] Status word */
};

struct aio {
	int32_t          aio_fildes;     /* [TYPE(fd_t)][const] File descriptor to operate upon */
	int32_t          aio_lio_opcode; /* [const] AIO opcode (one of `LIO_*') */
	int32_t          aio_reqprio;    /* [const] ... (???) */
#if __SIZEOF_POINTER__ > 4
	int32_t        __aio_pad0;       /* ... */
#endif /* __SIZEOF_POINTER__ > 4 */
	void            *aio_buf;        /* [const] Input/output buffer for `aio_write(3)' and `aio_read(3)' */
	size_t           aio_nbytes;     /* [const] Number of bytes to transfer `aio_write(3)' and `aio_read(3)' */
	struct sigevent  aio_sigevent;   /* [const] Signal event triggered once AIO operation has completed. */
	/* Internal members. */
	TAILQ_ENTRY(aio) aio_link;       /* [0..1][lock(aio_pending_lock)]
	                                  * [valid_if(aio_status.as_status == AIO_STATUS_PENDING ||
	                                  *           aio_status.as_status == AIO_STATUS_CANCELING)]
	                                  * Pending AIO link entry. */
#if __SIZEOF_POINTER__ <= 4
	int32_t        __aio_pad1[1];    /* ... */
#endif /* __SIZEOF_SIZE_T__ <= 4 */
	union aio_status aio_status;     /* AIO Status */
#if __SIZEOF_SIZE_T__ > 4
	int32_t        __aio_pad2;       /* ... */
#endif /* __SIZEOF_SIZE_T__ > 4 */
	ssize_t          aio_retval;     /* [valid_if(aio_status.as_status == AIO_STATUS_COMPLETED ||
	                                  *           aio_status.as_status == AIO_STATUS_RETURN_READ)]
	                                  * Return value, or negative errno. */
	pos64_t          aio_offset;     /* [const] File offset for `aio_write(3)' and `aio_read(3)' */
	REF struct aio_set_completion
	                *aio_set;        /* [0..1][const] Associated AIO set.
	                                  * Must be decref'd just after a `TERMINAL STATE' is set. */
	pid_t            aio_threadtid;  /* TID of the thread that is servicing this descriptor. */
};

#define SAME_FIELD(a, b)                                               \
	(offsetof(struct aio, a) == offsetof(struct aiocb, b) &&           \
	 sizeof(((struct aio *)0)->a) == sizeof(((struct aiocb *)0)->b) && \
	 offsetof(struct aio, a) == offsetof(struct aiocb64, b) &&         \
	 sizeof(((struct aio *)0)->a) == sizeof(((struct aiocb64 *)0)->b))
static_assert(SAME_FIELD(aio_fildes, aio_fildes));
static_assert(SAME_FIELD(aio_lio_opcode, aio_lio_opcode));
static_assert(SAME_FIELD(aio_reqprio, aio_reqprio));
static_assert(SAME_FIELD(aio_buf, aio_buf));
static_assert(SAME_FIELD(aio_nbytes, aio_nbytes));
static_assert(SAME_FIELD(aio_sigevent, aio_sigevent));
static_assert(SAME_FIELD(aio_status.as_word, __error_code));
static_assert(SAME_FIELD(aio_retval, __return_value));
static_assert(offsetof(struct aio, aio_offset) == offsetof(struct aiocb, aio_offset));
static_assert(offsetof(struct aio, aio_offset) == offsetof(struct aiocb64, aio_offset));
static_assert(sizeof(struct aio) <= sizeof(struct aiocb));
static_assert(sizeof(struct aio) <= sizeof(struct aiocb64));

/* Helper macros to unify `struct aiocb' variants into `struct aio' */
#define aiocb_as_aio(self)   ((struct aio *)(self))
#define aiocb64_as_aio(self) ((struct aio *)(self))
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
#define aiocb_with_offset_as_aio(self)   ((struct aio *)(self))
#define aiocb64_with_offset_as_aio(self) ((struct aio *)(self))
#else /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
#define aiocb_with_offset_as_aio(self)   (((struct aio *)(self))->aio_offset = (self)->aio_offset, (struct aio *)(self))
#define aiocb64_with_offset_as_aio(self) ((struct aio *)(self))
#endif /* __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */


/************************************************************************/
/* Pending AIO queue                                                    */
/************************************************************************/

/* Lock for the AIO pending list. */
PRIVATE ATTR_SECTION(".bss.crt.utility.aio")
struct atomic_lock aio_pending_lock = ATOMIC_LOCK_INIT;

/* [lock(aio_pending_lock)] List of pending AIO operations. */
PRIVATE ATTR_SECTION(".bss.crt.utility.aio")
struct aio_tailq aio_pending_list = { NULL, NULL }; /* Lazily initialized. */
#define aio_pending_list__lazy_init()                                  \
	(aio_pending_list.tqh_last == NULL                                 \
	 ? (void)(aio_pending_list.tqh_last = &aio_pending_list.tqh_first) \
	 : (void)0)

/* [lock(aio_pending_lock)] Total  #  of  pending  AIO   operations.
 * Broadcast by the number of additions when new descriptors appear. */
PRIVATE ATTR_SECTION(".bss.crt.utility.aio") lfutex_t aio_pending_count = 0;

/************************************************************************/
/* AIO Thread info                                                      */
/************************************************************************/

/* [lock(ATOMIC)] The # of AIO worker threads in existence.
 * Incremented just before `pthread_create()', and decremented just before
 * the actual AIO worker thread exits. */
PRIVATE ATTR_SECTION(".bss.crt.utility.aio") size_t aio_thread_count = 0;

/* [lock(ATOMIC)] The # of  idle AIO worker  threads in  existence.
 * Incremented just before the call to sys_lfutex() for the purpose
 * of waiting for more AIO descriptors, and decremented just  after
 * that system call returns. */
PRIVATE ATTR_SECTION(".bss.crt.utility.aio") size_t aio_thread_idle = 0;


/************************************************************************/
/* AIO Limits                                                           */
/************************************************************************/
PRIVATE ATTR_SECTION(".data.crt.utility.aio") size_t aiolimit_threads = 4; /* Max # of simultaneous AIO threads. */
PRIVATE ATTR_SECTION(".data.crt.utility.aio") time_t aiolimit_timeout = 1; /* # of seconds before AIO threads self-terminate. */


/************************************************************************/
/* AIO Completion signals                                               */
/************************************************************************/

/* Incremented every time `aio_after_finished_or_removing()' is called.
 * When `aio_completion_signal_waiters' is non-zero, that field is also
 * set to zero before a futex at this location is broadcast. */
PRIVATE ATTR_SECTION(".bss.crt.utility.aio")
lfutex_t aio_completion_signal_version = 0;

/* When non-zero, a futex at `aio_completion_signal_version'
 * must   be   broadcast  following   the   next  increment. */
PRIVATE ATTR_SECTION(".bss.crt.utility.aio")
uint8_t aio_completion_signal_waiters = 0;


/* Execute  completion  triggers of  `self' and
 * set the descriptor's status to `post_status' */
PRIVATE ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL aio_on_completion)(struct aio *__restrict self,
                                        uint16_t post_status) {
	struct sigevent completion;
	struct aio_set_completion *set;
	if (self->aio_status.as_flags & AIO_FLAG_WAITERS) {
		ATOMIC_AND(self->aio_status.as_flags, ~AIO_FLAG_WAITERS);
		sys_futex(&self->aio_status.as_word, FUTEX_WAKE, (uint32_t)-1, NULL, NULL, 0);
	}

	set = self->aio_set;
	DBG_memset(&self->aio_set, 0xcc, sizeof(self->aio_set));
	memcpy(&completion, &self->aio_sigevent, sizeof(completion));
	/* Don't do this (The user may not fully re-initialize the aiocb object!) */
/*	DBG_memset(&self->aio_sigevent, 0xcc, sizeof(self->aio_sigevent)); */

	/* Set the status to removed. */
	ATOMIC_WRITE(self->aio_status.as_status, post_status);

	/* Increment the global completion status. */
	ATOMIC_INC(aio_completion_signal_version);
	if (aio_completion_signal_waiters != 0) {
		ATOMIC_WRITE(aio_completion_signal_waiters, 0);
		sys_lfutex(&aio_completion_signal_version,
		           LFUTEX_WAKE, (uintptr_t)-1, NULL, 0);
	}

	/* Trigger post-completion events. */
	sigevent_notify(&completion);
	if (set != NULL)
		aio_set_completion_decref(set);
}



PRIVATE void *LIBCCALL
aio_worker_main(void *UNUSED(arg)) {
	ssize_t result;
	struct aio *self;
	pid_t mytid;
	mytid = gettid();
again:
	atomic_lock_acquire(&aio_pending_lock);
	self = TAILQ_FIRST(&aio_pending_list);
	if (!self) {
		errno_t error;
		struct timespec64 timeout;
		assert(aio_pending_count == 0);
		atomic_lock_release(&aio_pending_lock);
		/* Wait for more threads to show up. */
		timeout.tv_sec  = ATOMIC_READ(aiolimit_timeout);
		timeout.tv_nsec = 0;
		error = sys_lfutex(&aio_pending_count,
		                   LFUTEX_WAIT_WHILE |
		                   LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
		                   0, &timeout, 0);
		if (ATOMIC_READ(aio_pending_count) != 0)
			goto again;
		if (error == -ETIMEDOUT) {
			/* Initiate self-termination */
			ATOMIC_DEC(aio_thread_count);
			if (ATOMIC_READ(aio_pending_count) != 0) {
				ATOMIC_INC(aio_thread_count);
				goto again;
			}
			return NULL;
		}
		goto again;
	}

	/* Found an entry -> Remove from the pending list. */
	TAILQ_REMOVE_HEAD(&aio_pending_list, aio_link);
	assert(aio_pending_count != 0);
	--aio_pending_count;

	/* Set our TID as the one responsible for this descriptor. */
	self->aio_threadtid = mytid;

	/* Try to start serving this descriptor. */
	if (!ATOMIC_CMPXCH(self->aio_status.as_status,
	                   AIO_STATUS_PENDING,
	                   AIO_STATUS_RUNNING)) {
		/* Special case: descriptor was canceled. */
		atomic_lock_release(&aio_pending_lock);
		assert(self->aio_status.as_status == AIO_STATUS_CANCELING);
		aio_on_completion(self, AIO_STATUS_REMOVED);
		goto again;
	}
	atomic_lock_release(&aio_pending_lock);

	/* The descriptor is now in  progress, so let's to  the
	 * actual work that all of this has been leading up to! */
again_operation:
	switch (self->aio_lio_opcode) {

	case LIO_READ:
		result = sys_pread64(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
		if (result == -ESPIPE) /* pread not supported by this file... */
			result = sys_read(self->aio_fildes, self->aio_buf, self->aio_nbytes);
		break;

	case LIO_WRITE:
		result = sys_pwrite64(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
		if (result == -ESPIPE) /* pwrite not supported by this file... */
			result = sys_write(self->aio_fildes, self->aio_buf, self->aio_nbytes);
		break;

	case LIO_FSYNC:
		result = sys_fsync(self->aio_fildes);
		break;

	case LIO_FDATASYNC:
		result = sys_fdatasync(self->aio_fildes);
		break;

	/* TODO: Expose `LIO_FSYNC' and `LIO_FDATASYNC'
	 *       as `_KOS_SOURCE' extensions in <aio.h> */

	/* TODO: KOS-specific extensions for AIO versions of:
	 *  - LIO_READALL   --> readall(3)
	 *  - LIO_WRITEALL  --> writeall(3)
	 *  - LIO_READV     --> sys_preadv() / sys_readv()
	 *  - LIO_WRITEV    --> sys_pwritev() / sys_writev()
	 *  - LIO_SYNC      --> sys_sync()
	 *  - LIO_SYNCFS    --> sys_syncfs()
	 *  - LIO_SEND      --> sys_send()      // NOTE: recv doesn't really make sense, though...
	 *  - LIO_SENDTO    --> sys_sendto()
	 *  - LIO_SENDMSG   --> sys_sendmsg()
	 *  - LIO_SENDMMSG  --> sys_sendmmsg()
	 *  - LIO_MOUNT     --> sys_mount()
	 *  - LIO_UMOUNT    --> sys_umount()
	 *  - LIO_SWAPON    --> sys_swapon()
	 *  - LIO_SWAPOFF   --> sys_swapoff()
	 *  - LIO_SENDFILE  --> sys_sendfile()
	 */

	default:
		/* Fallback: Invalid operation. */
		result = -EINVAL;
		break;
	}

	/* Deal with interrupts. */
	if (result == -EINTR) {
		if (ATOMIC_READ(self->aio_status.as_status) != AIO_STATUS_INTERRUPTING)
			goto again_operation; /* Sporadic interrupt */
		/* Intentional interrupt */
		aio_on_completion(self, AIO_STATUS_REMOVED);
		goto again;
	}

	/* Store the return value. */
	self->aio_retval = result;

	/* Indicate completion. */
	ATOMIC_WRITE(self->aio_status.as_status, AIO_STATUS_FINISHED);
	aio_on_completion(self, AIO_STATUS_COMPLETED);

	/* Check for more work to be done. */
	goto again;
}




/* Spawn a new AIO worker thread.
 * @return: EOK:    Success.
 * @return: EAGAIN: Out of memory. */
PRIVATE errno_t
NOTHROW(LIBCCALL spawn_aio_worker_thread)(void) {
	errno_t error;
	pthread_t pt;
	pthread_attr_t attr;
	error = pthread_attr_init(&attr);
	if unlikely(error != EOK)
		goto done;

	/* Create the thread with DETACHED disposition. */
	error = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if unlikely(error != EOK)
		goto done_attr;

	/* Create the new thread */
	ATOMIC_INC(aio_thread_count);
	error = pthread_create(&pt, &attr, &aio_worker_main, NULL);
	if unlikely(error != EOK)
		ATOMIC_DEC(aio_thread_count);

done_attr:
	pthread_attr_destroy(&attr);
done:
	return error;
}



/* @return: 0:  Success
 * @return: -1: [errno=EAGAIN] Out of memory (read: `ENOMEM') */
PRIVATE ATTR_SECTION(".text.crt.utility.aio") NONNULL((1, 2)) int
NOTHROW_NCX(LIBCCALL start_aio_operation_ex)(struct aio *first,
                                             struct aio *last,
                                             size_t count) {
	size_t thread_limit, spawn_limit;
	assert(count != 0);
	assert(first->aio_status.as_status == AIO_STATUS_PENDING);
	atomic_lock_acquire(&aio_pending_lock);
	aio_pending_list__lazy_init();
	TAILQ_INSERT_TAIL_R(&aio_pending_list, first, last, aio_link);
	aio_pending_count += count;
	atomic_lock_release(&aio_pending_lock);

	/* spawn AIO worker threads while:
	 * >>     // As set by libc_aio_init()::aioinit::aio_threads
	 * >> ATOMIC_READ(aio_thread_count) < thread_limit &&
	 * >>     // Note that `aio_pending_count' is constantly re-
	 * >>     // read as threads are spawned and will already
	 * >>     // begin to consume AIO descriptors.
	 * >> ATOMIC_READ(aio_thread_idle) < ATOMIC_READ(aio_pending_count) &&
	 * >>     // Limit to spawning at most `count' threads
	 * >> (count-- != 0); */
	thread_limit = ATOMIC_READ(aiolimit_threads);
	spawn_limit  = count;
	do {
		errno_t error;
		if (ATOMIC_READ(aio_thread_count) >= thread_limit)
			break; /* Not allowed to spawn any more threads. */
		if (ATOMIC_READ(aio_thread_idle) >= ATOMIC_READ(aio_pending_count))
			break; /* Already got 1 idle thread for every pending
			        * request, so no point in starting even more! */

		error = spawn_aio_worker_thread();
		if (error != EOK) {
			/* Failed to spawn another thread. If there is at least one
			 * thread that is still alive, then we may assume that said
			 * thread would sooner or later get around to servicing our
			 * descriptor. */
			if (ATOMIC_READ(aio_thread_count) != 0)
				break;

			/* Remove our operations from the pending queue. */
			atomic_lock_acquire(&aio_pending_lock);

			/* Re-check  that no  other thread  was able  to spawn more
			 * threads, and that the first descriptor is still pending. */
			if (ATOMIC_READ(aio_thread_count) != 0 &&
			    first->aio_status.as_status == AIO_STATUS_PENDING) {
				atomic_lock_release(&aio_pending_lock);
				break;
			}

			/* We know that _all_ of our descriptors will still be pending,
			 * because there aren't any  threads which could consume  them,
			 * as the only place that can remove arbitrary descriptors from
			 * the pending set is inside of the AIO worker main function.
			 *
			 * As such, there is no race condition in regards to only a few
			 * of our descriptors having been  completed, as they were  all
			 * posted  at the same time, meaning that if something had been
			 * able to consume them, it would have done so for all of them,
			 * which  we've already checked by looking at the status of the
			 * first of the set of descriptors we've posted earlier. */
			assert(aio_pending_count >= count);
			aio_pending_count -= count;
			TAILQ_REMOVE_R(&aio_pending_list, first, last, aio_link);

			/* Release our lock from the pending list of AIO descriptors. */
			atomic_lock_release(&aio_pending_lock);

			/* Set the thread-creation-errno and indicate failure. */
			return libc_seterrno(error);
		}
	} while (--spawn_limit);

	/* Wake up at most `aio_pending_count'  AIO worker threads waiting for  work
	 * to show up. Note that this must happen after the above spawn loop so that
	 * the number of idle threads is still correct in relation to new  requests. */
	sys_lfutex(&aio_pending_count, LFUTEX_WAKE,
	           ATOMIC_READ(aio_pending_count),
	           NULL, 0);

	/* And with that, there should be at least 1 thread out there to do our dirty work. */
	return 0;
}


/* Search for AIO descriptors for a given `fd'.
 * If the caller intends to use the returned descriptor, it is their responsibility
 * to ensure that said descriptor won't end up being destroyed before they are done
 * using it. This  function makes no  guaranty on the  lifetime of said  descriptor
 * following a non-NULL return. */
PRIVATE ATTR_SECTION(".text.crt.utility.aio") struct aio *
NOTHROW_NCX(LIBCCALL find_aio_for_fd)(fd_t fd) {
	struct aio *result;
	atomic_lock_acquire(&aio_pending_lock);
	TAILQ_FOREACH (result, &aio_pending_list, aio_link) {
		if (result->aio_fildes == fd)
			break;
	}
	atomic_lock_release(&aio_pending_lock);
	return result;
}


/* Send a sporadic interrupt to the thread hosting `self' */
PRIVATE ATTR_SECTION(".text.crt.utility.aio") void
NOTHROW_NCX(LIBCCALL interrupt_aio_thread)(struct aio *__restrict self) {
	/* Use `RPC_PRIORITY_HIGH', thus  trying to  do
	 * an implicit yield to the thread in question. */
	errno_t saved = libc_geterrno();
	rpc_interrupt(self->aio_threadtid, RPC_SYNCMODE_CP | RPC_PRIORITY_HIGH);
	libc_seterrno(saved);
}


/* Cancel a specific AIO operation.
 * NOTE: When `AIO_CANCELED' is returned, the completion event of `self',
 *       as  specified in `self->aio_sigevent'  will have been triggered,
 *       as completion events are triggered even for canceled operations.
 * @return: AIO_CANCELED: Operation canceled successfully
 * @return: AIO_ALLDONE:  Operation was already completed before the call was made */
PRIVATE ATTR_SECTION(".text.crt.utility.aio") int
NOTHROW_NCX(LIBCCALL cancel_aio)(struct aio *__restrict self) {
	union aio_status status;
again:
	status.as_word = ATOMIC_READ(self->aio_status.as_word);
switch_status:
	switch (status.as_status) {

	case AIO_STATUS_PENDING: {
		union aio_status new_status;
		new_status           = status;
		new_status.as_status = AIO_STATUS_CANCELING;
		if (!ATOMIC_CMPXCH(self->aio_status.as_word,
		                   status.as_word,
		                   new_status.as_word))
			goto again;

		/* Try to remove the list from the pending list.
		 * NOTE: If this fails, the AIO worker thread is also
		 *       allowed  to remove descriptors and set their
		 *       status to `AIO_STATUS_REMOVED' */
		while (!atomic_lock_tryacquire(&aio_pending_lock)) {
			sched_yield();
			status.as_word = ATOMIC_READ(self->aio_status.as_word);
			if (status.as_status != AIO_STATUS_CANCELING)
				goto switch_status; /* Should be `AIO_STATUS_REMOVED' at this point... */
		}
		/* Remove from the pending list. */
		TAILQ_REMOVE(&aio_pending_list, self, aio_link);
		assert(aio_pending_count != 0);
		--aio_pending_count;
		atomic_lock_release(&aio_pending_lock);

		/* Trigger completion events. */
		aio_on_completion(self, AIO_STATUS_REMOVED);
	}	ATTR_FALLTHROUGH
	case AIO_STATUS_REMOVED:
		return AIO_CANCELED;

	case AIO_STATUS_RUNNING: {
		/* Operation is running right now. -> Try to switch to interrupting. */
		union aio_status new_status;
		new_status           = status;
		new_status.as_status = AIO_STATUS_INTERRUPTING;
		if (!ATOMIC_CMPXCH(self->aio_status.as_word,
		                   status.as_word,
		                   new_status.as_word))
			goto again;

		/* Send a sporadic interrupt to the thread servicing the given AIO. */
		interrupt_aio_thread(self);

		/* Wait until `AIO_STATUS_INTERRUPTING' goes away. */
		goto again;
	}	break;

	case AIO_STATUS_FINISHED:
	case AIO_STATUS_CANCELING:
	case AIO_STATUS_INTERRUPTING:
		/* Wait until these status codes goes away. */
		sched_yield();
		goto again;

	default:
		break;
	}
	return AIO_ALLDONE;
}


/* Suspend the calling thread until  the given AIO operations  has
 * been completed, or a signal is delivered to the calling thread.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
PRIVATE ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL waitfor_single_aio)(struct aio *__restrict self,
                                         struct timespec64 const *rel_timeout) {
	union aio_status status;
again:
	status.as_word = ATOMIC_READ(self->aio_status.as_word);
	switch (status.as_status) {

	case AIO_STATUS_PENDING:
	case AIO_STATUS_RUNNING: {
		errno_t error;

		/* Set the waiters-flag. */
		if (!(status.as_flags & AIO_FLAG_WAITERS)) {
			union aio_status new_status;
			new_status = status;
			new_status.as_flags |= AIO_FLAG_WAITERS;
			if (!ATOMIC_CMPXCH(self->aio_status.as_word,
			                   status.as_word,
			                   new_status.as_word))
				goto again;
		}

		/* Wait until the status changes. */
		error = sys_futex_time64(&self->aio_status.as_word,
		                         FUTEX_WAIT, status.as_word,
		                         rel_timeout, NULL, 0);
		if (E_ISERR(error)) {
			if (error == -ETIMEDOUT)
				error = -EAGAIN;
			return libc_seterrno_neg(error);
		}
		goto again;
	}	break;

	case AIO_STATUS_FINISHED:
	case AIO_STATUS_CANCELING:
	case AIO_STATUS_INTERRUPTING:
		/* Wait for completion signals to finish */
		sched_yield();
		goto again;

	default:
		break;
	}
	return 0;
}


/* Check if the given AIO has completed. */
PRIVATE ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) bool
NOTHROW_NCX(LIBCCALL trywaitfor_single_aio)(struct aio const *__restrict self) {
	union aio_status status;
again:
	status.as_word = ATOMIC_READ(self->aio_status.as_word);
	switch (status.as_status) {

	case AIO_STATUS_PENDING:
	case AIO_STATUS_RUNNING:
		return false;

	case AIO_STATUS_INTERRUPTING:
	case AIO_STATUS_CANCELING:
		/* Wait for completion events to finish */
		sched_yield();
		goto again;

	default:
		break;
	}
	return true;
}


/* Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
PRIVATE ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL waitfor_aio)(struct aio *const list[], size_t nent,
                                  struct timespec64 const *rel_timeout) {
	errno_t error;
	size_t i;
	lfutex_t version;
	if unlikely(nent == 0) /* Special case: nothing to wait for. */
		return 0;
	if (nent == 1) /* Special case: wait for a single AIO operation. */
		return waitfor_single_aio(list[0], rel_timeout);

	/* Check if any of the AIO objects have already completed. */
again:
	version = ATOMIC_READ(aio_completion_signal_version);
	for (i = 0; i < nent; ++i) {
		struct aio *ent = list[i];
		if (trywaitfor_single_aio(ent))
			return 0; /* This one's completed! */
	}

	/* All operations are in progress.
	 * Wait until `aio_completion_signal_version' changes. */
	if (ATOMIC_READ(aio_completion_signal_version) != version)
		goto again;
	ATOMIC_WRITE(aio_completion_signal_waiters, 1);
	error = sys_lfutex(&aio_completion_signal_version,
	                   LFUTEX_WAIT_WHILE |
	                   LFUTEX_WAIT_FLAG_TIMEOUT_RELATIVE,
	                   version, rel_timeout, 0);
	if (!E_ISERR(error))
		goto again;
	if (error == -ETIMEDOUT)
		error = -EAGAIN;
	return libc_seterrno_neg(error);
}



/* Helper wrapper for `start_aio_operation_ex()' */
PRIVATE ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL start_aio_operation)(struct aio *__restrict self,
                                          int opcode) {
	self->aio_lio_opcode       = opcode; /* Operation opcode */
	self->aio_status.as_status = AIO_STATUS_PENDING;
	self->aio_status.as_flags  = AIO_FLAG_NORMAL;
	self->aio_set              = NULL; /* Not part of a set */
	return start_aio_operation_ex(self, self, 1);
}




/* Execute/perform  a `list' of  AIO operations, where  each element of `list'
 * describes a read (`elem->aio_lio_opcode == LIO_READ'), write (`LIO_WRITE'),
 * or no-op (`LIO_NOP') operation.
 *
 * Once all operations are in progress, and `mode == LIO_WAIT', wait for all
 * of  them to complete  and return `0' on  success, or `-1'  is any of them
 * failed (individual errors/return values can be queried via `aio_error(3)'
 * and `aio_return(3)' on each of the elements from `list')
 *
 * Alternatively,  when `mode == LIO_NOWAIT', AIO is performed asynchronously,
 * and the function returns immediately once all operations have been started.
 * If  this was successful, return `0', or  `-1' if doing so failed (`errno').
 * Note that upon error here, no AIO operations will have been started, yet.
 *
 * Additionally, the given `sigev' (if non-NULL) will be assigned as a master
 * completion event that is only triggered  once _all_ of the AIO  operations
 * have completed. Note that in this case, `sigev' will/has always be invoked
 * if this function returns  `0', even if  any of the  AIO operations end  up
 * being canceled (s.a. `aio_cancel(3)') before they could be performed.
 *
 * @param: mode: One of `LIO_WAIT', `LIO_NOWAIT'
 * @return: 0 : Success
 * @return: -1: [errno=EAGAIN] Out of memory (read: `ENOMEM')
 * @return: -1: [errno=EINVAL] Invalid `mode'
 * @return: -1: [errno=EINTR]  When `mode == LIO_WAIT': Calling thread was interrupted.
 *                             Note that in  this case incomplete  AIO operations  will
 *                             continue to run and that  the caller should handle  this
 *                             case by looping over  all and using `aio_suspend(3)'  to
 *                             wait for each until doing so has succeeded at least once
 *                             for every entry.
 * @return: -1: [errno=EIO]    When `mode == LIO_WAIT': At least one of the operations
 *                             failed (s.a. `aio_error(3)') */
PRIVATE ATTR_SECTION(".text.crt.utility.aio") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL start_aio_listio)(int mode, struct aio *const list[__restrict_arr],
                                       size_t nent, struct sigevent *sigev) {
	size_t i, count;
	struct aio_tailq aio_req;
	REF struct aio_set_completion *completion;

	/* Validate the `mode' argument. */
	if unlikely(mode != LIO_WAIT && mode != LIO_NOWAIT)
		return libc_seterrno(EINVAL);

	/* Special case: Nothing to do but signal completion if the caller wants us to do so.
	 * Also  note that if something ends up  preventing this notify from succeeding, then
	 * we mustn't return to indicate an error, but still update our thread's `errno'.
	 *
	 * This same behavior can also be seen in Glibc! */
	if unlikely(!nent) {
no_wait_aio:
		if (mode == LIO_NOWAIT && sigev != NULL) {
			errno_t error;
			error = sigevent_notify(sigev);
			if (error != EOK)
				libc_seterrno(error);
		}
		return 0;
	}

	/* If necessary, set-up a completion set. */
	completion = NULL;
	if (mode == LIO_NOWAIT && sigev != NULL) {
		completion = (REF struct aio_set_completion *)malloc(sizeof(struct aio_set_completion));
		if unlikely(!completion)
			return libc_seterrno(EAGAIN);
		memcpy(&completion->asc_event, sigev, sizeof(*sigev));
	}

	/* Chain all of the requests so we can schedule them all at once. */
	TAILQ_INIT(&aio_req);
	for (i = count = 0; i < nent; ++i) {
		struct aio *req = list[i];
		if (req->aio_lio_opcode == LIO_NOP)
			continue; /* Ignore... */
		/* Append to the end of the list of pending requests. */
		TAILQ_INSERT_TAIL(&aio_req, req, aio_link);
		req->aio_set              = completion;
		req->aio_status.as_status = AIO_STATUS_PENDING;
		req->aio_status.as_flags  = AIO_FLAG_NORMAL;
		++count;
	}
	if (completion)
		completion->asc_refcnt = count;

	/* Check for special case: nothing was actually requested. */
	if unlikely(TAILQ_EMPTY(&aio_req)) {
		assert(count == 0);
		free(completion);
		goto no_wait_aio;
	}
	assert(!completion || completion->asc_refcnt != 0);

	/* Actually initiate AIO. */
	if (start_aio_operation_ex(TAILQ_FIRST(&aio_req),
	                           TAILQ_LAST(&aio_req),
	                           count) != 0) {
		/* Failed to start AIO operation.
		 * Note that we here we `free()' the completion controller rather destroy
		 * it, since the caller-given `sigev' should not be invoked in this case. */
		free(completion);
		return -1;
	}

	/* In wait-mode, wait for all of the AIO operations to complete. */
	if (mode == LIO_WAIT) {
		for (i = 0; i < nent; ++i) {
			int error;
			struct aio *req = list[i];
			if (req->aio_lio_opcode == LIO_NOP)
				continue; /* Ignore... */
			error = waitfor_single_aio(req, NULL);
			if (error != 0)
				return error; /* Calling thread was interrupted. */
		}

		/* Now  that all of  them have completed,  check if any of
		 * the AIO operations failed (in which case we must return
		 * with errno == EIO). */
		for (i = 0; i < nent; ++i) {
			struct aio *req = list[i];
			if (req->aio_lio_opcode == LIO_NOP)
				continue; /* Ignore... */
			if (E_ISERR(req->aio_retval))
				return libc_seterrno(EIO);
		}
	}
	return 0;
}





/*[[[head:libc_aio_read,hash:CRC-32=0xde6b5ca4]]]*/
/* >> aio_read(3), aio_read64(3)
 * Begin an async `pread(2)' operation:
 * >> pread(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pread(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `read(2)' is called instead (in which case `self->aio_offset' is ignored) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_read)(struct aiocb *self)
/*[[[body:libc_aio_read]]]*/
{
	return start_aio_operation(aiocb_with_offset_as_aio(self),
	                           LIO_READ);
}
/*[[[end:libc_aio_read]]]*/

/*[[[head:libc_aio_write,hash:CRC-32=0xc5e8e2b2]]]*/
/* >> aio_write(3), aio_write64(3)
 * Begin an async `pwrite(2)' operation:
 * >> pwrite(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pwrite(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `write(2)' is called instead (in which case `self->aio_offset' is ignored) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_write)(struct aiocb *self)
/*[[[body:libc_aio_write]]]*/
{
	return start_aio_operation(aiocb_with_offset_as_aio(self),
	                           LIO_WRITE);
}
/*[[[end:libc_aio_write]]]*/

/*[[[head:libc_lio_listio,hash:CRC-32=0x895cd25a]]]*/
/* >> lio_listio(3), lio_listio64(3)
 * Execute/perform  a `list' of  AIO operations, where  each element of `list'
 * describes a read (`elem->aio_lio_opcode == LIO_READ'), write (`LIO_WRITE'),
 * or no-op (`LIO_NOP') operation.
 *
 * Once all operations are in progress, and `mode == LIO_WAIT', wait for all
 * of  them to complete  and return `0' on  success, or `-1'  is any of them
 * failed (individual errors/return values can be queried via `aio_error(3)'
 * and `aio_return(3)' on each of the elements from `list')
 *
 * Alternatively,  when `mode == LIO_NOWAIT', AIO is performed asynchronously,
 * and the function returns immediately once all operations have been started.
 * If  this was successful, return `0', or  `-1' if doing so failed (`errno').
 * Note that upon error here, no AIO operations will have been started, yet.
 *
 * Additionally, the given `sigev' (if non-NULL) will be assigned as a master
 * completion event that is only triggered  once _all_ of the AIO  operations
 * have completed. Note that in this case, `sigev' will/has always be invoked
 * if this function returns  `0', even if  any of the  AIO operations end  up
 * being canceled (s.a. `aio_cancel(3)') before they could be performed.
 *
 * @param: mode: One of `LIO_WAIT', `LIO_NOWAIT'
 * @return: 0 : Success
 * @return: -1: [errno=EAGAIN] Out of memory (read: `ENOMEM')
 * @return: -1: [errno=EINVAL] Invalid `mode'
 * @return: -1: [errno=EINTR]  When `mode == LIO_WAIT': Calling thread was interrupted.
 *                             Note that in  this case incomplete  AIO operations  will
 *                             continue to run and that  the caller should handle  this
 *                             case by looping over  all and using `aio_suspend(3)'  to
 *                             wait for each until doing so has succeeded at least once
 *                             for every entry.
 * @return: -1: [errno=EIO]    When `mode == LIO_WAIT': At least one of the operations
 *                             failed (s.a. `aio_error(3)') */
INTERN ATTR_SECTION(".text.crt.utility.aio") ATTR_INS(2, 3) int
NOTHROW_NCX(LIBCCALL libc_lio_listio)(int mode,
                                      struct aiocb *const list[__restrict_arr],
                                      __STDC_INT_AS_SIZE_T nent,
                                      struct sigevent *__restrict sigev)
/*[[[body:libc_lio_listio]]]*/
{
#if __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__
	size_t i;
	for (i = 0; i < nent; ++i) {
		struct aio *nstruct;
		struct aiocb *ostruct;
		ostruct = list[i];
		nstruct = aiocb_as_aio(ostruct);
		/* Expand the offset values of all of the AIO descriptors. */
		nstruct->aio_offset = ostruct->aio_offset;
	}
#endif /* __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */
	return start_aio_listio(mode, (struct aio *const *)list, nent, sigev);
}
/*[[[end:libc_lio_listio]]]*/

/*[[[head:libc_aio_error,hash:CRC-32=0xbfe117ec]]]*/
/* >> aio_error(3), aio_error64(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress (or pending)
 * @return: ECANCELED:   Operation was canceled (s.a. `aio_cancel(3)')
 * @return: EINVAL:      `self' is invalid, or its return value has already been read.
 * @return: * :          The   `errno'  with  which   the  async  operation  failed.
 *                       s.a. `pread(2)', `pwrite(2)', `fsync(2)' and `fdatasync(2)' */
INTERN ATTR_SECTION(".text.crt.utility.aio") WUNUSED ATTR_IN(1) errno_t
NOTHROW_NCX(LIBCCALL libc_aio_error)(struct aiocb const *self)
/*[[[body:libc_aio_error]]]*/
{
	struct aio const *me;
	if unlikely(!self)
		goto err_inval;
	me = (struct aio const *)self;
	switch (ATOMIC_READ(me->aio_status.as_status)) {

	case AIO_STATUS_PENDING:
	case AIO_STATUS_RUNNING:
	case AIO_STATUS_INTERRUPTING:
		/* AIO_STATUS_CANWAIT() */
	case AIO_STATUS_CANCELING: /* Technically canceled, but can't tell the caller that, yet */
	case AIO_STATUS_FINISHED:  /* Technically completed, but can't tell the caller that, yet */
		return EINPROGRESS;

	case AIO_STATUS_REMOVED:
		return ECANCELED;

	case AIO_STATUS_COMPLETED:
	case AIO_STATUS_RETURN_READ:
		/* Check the status of a completed operation. */
		if (E_ISERR(me->aio_retval))
			return -me->aio_retval;
		return EOK;

	default:
		break;
	}
err_inval:
	return libc_seterrno(EINVAL);
}
/*[[[end:libc_aio_error]]]*/

/*[[[head:libc_aio_return,hash:CRC-32=0x33bbcf8b]]]*/
/* >> aio_return(3), aio_return64(3)
 * @return: * : Return value of async `pread(2)', `pwrite(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: [errno=<unchanged>] AIO operation failed (s.a. `aio_error(3)')
 * @return: -1: [errno=EINVAL]      `self' is invalid (including the case where `self' is still
 *                                  in progress), or  its return value  has already been  read. */
INTERN ATTR_SECTION(".text.crt.utility.aio") ATTR_INOUT(1) ssize_t
NOTHROW_NCX(LIBCCALL libc_aio_return)(struct aiocb *self)
/*[[[body:libc_aio_return]]]*/
{
	struct aio *me;
	if unlikely(!self)
		goto err_inval;
	me = aiocb_as_aio(self);
	if (ATOMIC_READ(me->aio_status.as_status) == AIO_STATUS_COMPLETED) {
		ssize_t result;

		/* Check the status of a completed operation. */
		result = me->aio_retval;
		if (E_ISERR(result))
			result = -1; /* Caller should invoke `aio_error(3)' */

		/* Cause any future status/error reads to fail with EINVAL,
		 * as  is required  by POSIX  which specifies  that the AIO
		 * return value should only be read once. */
		ATOMIC_WRITE(me->aio_status.as_status, AIO_STATUS_RETURN_READ);

		/* Return the AIO return value. */
		return result;
	}
err_inval:
	return libc_seterrno(EINVAL);
}
/*[[[end:libc_aio_return]]]*/

/*[[[head:libc_aio_cancel,hash:CRC-32=0xcb597930]]]*/
/* >> aio_cancel(3), aio_cancel64(3)
 * Cancel  a specific AIO  operation (self != NULL),  or all operations currently
 * operating on a given `fd' (self !=  NULL && fd == self->aio_fildes). For  this
 * purpose,  it is undefined if the numerical value of `fd' is used for searching
 * active operations, or the pointed-to kernel object. As such, it is recommended
 * that you always aio_cancel the same fd as was also used when the AIO operation
 * was initiated.
 * NOTE: When `AIO_CANCELED' is returned, the completion event of `self',
 *       as  specified in `self->aio_sigevent'  will have been triggered,
 *       as completion events are triggered even for canceled operations.
 * @return: AIO_CANCELED:    At least one operation was canceled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 *                           This KOS implementation never returns  this value, as it  includes
 *                           facilities to force-abort any async operation (in the same vain as
 *                           sending SIGKILL can also force-aborts a process)
 *                           NOTE: In other implementations, this return value outweighs
 *                                 `AIO_CANCELED'  and `AIO_ALLDONE' in face of multiple
 *                                 AIO operations.
 * @return: AIO_ALLDONE:     Operations had  already been  completed
 *                           (or canceled) before the call was made.
 * @return: -1: [errno=EBADF]  `fd' is not a valid file descriptor
 * @return: -1: [errno=EINVAL] `self != NULL' and the given `fd' differs from `self->aio_fildes' */
INTERN ATTR_SECTION(".text.crt.utility.aio") int
NOTHROW_NCX(LIBCCALL libc_aio_cancel)(fd_t fd,
                                      struct aiocb *self)
/*[[[body:libc_aio_cancel]]]*/
{
	int result;
	struct aio *desc;
	if (self) {
		if unlikely(self->aio_fildes != fd)
			return libc_seterrno(EINVAL);
		return cancel_aio(aiocb_as_aio(self));
	}

	/* Cancel all descriptors of a given `fd' */
	desc = find_aio_for_fd(fd);
	if (!desc) {
		/* No known descriptors.
		 * -> Must check if `fd' is a valid file descriptor.
		 *    If it isn't, then  we must return with  EBADF. */
		errno_t error;
		error = sys_fcntl(fd, F_GETFD, NULL);
		if (E_ISERR(error))
			return libc_seterrno_neg(error);
		return AIO_ALLDONE;
	}

	/* Cancel the first descriptor. */
	result = cancel_aio(desc);
	while ((desc = find_aio_for_fd(fd)) != NULL) {
		int new_result;
		new_result = cancel_aio(desc);
		/* `AIO_CANCELED' outweighs `AIO_ALLDONE' in this case. */
		if (result == AIO_ALLDONE)
			result = new_result;
	}

	/* And with that they're either all canceled, or completed. */
	return result;
}
/*[[[end:libc_aio_cancel]]]*/

/*[[[head:libc_aio_suspend,hash:CRC-32=0x3ad9ec08]]]*/
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
INTERN ATTR_SECTION(".text.crt.utility.aio") ATTR_INS(1, 2) int
NOTHROW_RPC(LIBCCALL libc_aio_suspend)(struct aiocb const *const list[],
                                       __STDC_INT_AS_SIZE_T nent,
                                       struct timespec const *__restrict rel_timeout)
/*[[[body:libc_aio_suspend]]]*/
{
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
	return waitfor_aio((struct aio *const *)list, nent,
	                   (struct timespec64 const *)rel_timeout);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
	struct timespec64 ts64;
	if (!rel_timeout)
		return waitfor_aio((struct aio *const *)list, nent, NULL);
	ts64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	ts64.tv_nsec = (time64_t)rel_timeout->tv_nsec;
	return waitfor_aio((struct aio *const *)list, nent, &ts64);
#endif /* !__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
}
/*[[[end:libc_aio_suspend]]]*/

/*[[[head:libc_aio_fsync,hash:CRC-32=0x1d1d6c68]]]*/
/* >> aio_fsync(3), aio_fsync64(3)
 * Begin an async `fsync(2)' or `fdatasync(2)' operation:
 * >> if (operation == O_SYNC) {
 * >>     fsync(self->aio_fildes);
 * >> } else if (operation == O_DSYNC) {
 * >>     fdatasync(self->aio_fildes);
 * >> }
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * @param: operation: One of `O_SYNC' or `O_DSYNC'
 * @return: 0 : Operation was started successfully
 * @return: -1: [errno=EAGAIN] Insufficient resources  (read:  `ENOMEM',  but  posix
 *                             didn't want to use that errno for whatever reason...)
 * @return: -1: [errno=EINVAL] `operation' was invalid */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_aio_fsync)(oflag_t operation,
                                     struct aiocb *self)
/*[[[body:libc_aio_fsync]]]*/
{
	int opcode;
	if (operation == O_SYNC) {
		opcode = LIO_FSYNC;
	} else if (operation == O_DSYNC) {
		opcode = LIO_FDATASYNC;
	} else {
		return libc_seterrno(EINVAL);
	}
	return start_aio_operation(aiocb_as_aio(self),
	                           opcode);
}
/*[[[end:libc_aio_fsync]]]*/

/*[[[head:libc_aio_read64,hash:CRC-32=0xb2f80750]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_read64, libc_aio_read);
#else /* MAGIC:alias */
/* >> aio_read(3), aio_read64(3)
 * Begin an async `pread(2)' operation:
 * >> pread(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pread(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `read(2)' is called instead (in which case `self->aio_offset' is ignored) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_read64)(struct aiocb64 *self)
/*[[[body:libc_aio_read64]]]*/
{
	return start_aio_operation(aiocb64_with_offset_as_aio(self),
	                           LIO_READ);
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_read64]]]*/

/*[[[head:libc_aio_write64,hash:CRC-32=0xbb483c11]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_aio_write64, libc_aio_write);
#else /* MAGIC:alias */
/* >> aio_write(3), aio_write64(3)
 * Begin an async `pwrite(2)' operation:
 * >> pwrite(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pwrite(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `write(2)' is called instead (in which case `self->aio_offset' is ignored) */
INTERN ATTR_SECTION(".text.crt.utility.aio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_aio_write64)(struct aiocb64 *self)
/*[[[body:libc_aio_write64]]]*/
{
	return start_aio_operation(aiocb64_with_offset_as_aio(self),
	                           LIO_WRITE);
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_write64]]]*/

/*[[[head:libc_lio_listio64,hash:CRC-32=0xb2834aa8]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_lio_listio64, libc_lio_listio);
#else /* MAGIC:alias */
/* >> lio_listio(3), lio_listio64(3)
 * Execute/perform  a `list' of  AIO operations, where  each element of `list'
 * describes a read (`elem->aio_lio_opcode == LIO_READ'), write (`LIO_WRITE'),
 * or no-op (`LIO_NOP') operation.
 *
 * Once all operations are in progress, and `mode == LIO_WAIT', wait for all
 * of  them to complete  and return `0' on  success, or `-1'  is any of them
 * failed (individual errors/return values can be queried via `aio_error(3)'
 * and `aio_return(3)' on each of the elements from `list')
 *
 * Alternatively,  when `mode == LIO_NOWAIT', AIO is performed asynchronously,
 * and the function returns immediately once all operations have been started.
 * If  this was successful, return `0', or  `-1' if doing so failed (`errno').
 * Note that upon error here, no AIO operations will have been started, yet.
 *
 * Additionally, the given `sigev' (if non-NULL) will be assigned as a master
 * completion event that is only triggered  once _all_ of the AIO  operations
 * have completed. Note that in this case, `sigev' will/has always be invoked
 * if this function returns  `0', even if  any of the  AIO operations end  up
 * being canceled (s.a. `aio_cancel(3)') before they could be performed.
 *
 * @param: mode: One of `LIO_WAIT', `LIO_NOWAIT'
 * @return: 0 : Success
 * @return: -1: [errno=EAGAIN] Out of memory (read: `ENOMEM')
 * @return: -1: [errno=EINVAL] Invalid `mode'
 * @return: -1: [errno=EINTR]  When `mode == LIO_WAIT': Calling thread was interrupted.
 *                             Note that in  this case incomplete  AIO operations  will
 *                             continue to run and that  the caller should handle  this
 *                             case by looping over  all and using `aio_suspend(3)'  to
 *                             wait for each until doing so has succeeded at least once
 *                             for every entry.
 * @return: -1: [errno=EIO]    When `mode == LIO_WAIT': At least one of the operations
 *                             failed (s.a. `aio_error(3)') */
INTERN ATTR_SECTION(".text.crt.utility.aio") ATTR_INS(2, 3) int
NOTHROW_NCX(LIBCCALL libc_lio_listio64)(int mode,
                                        struct aiocb64 *const list[__restrict_arr],
                                        __STDC_INT_AS_SIZE_T nent,
                                        struct sigevent *__restrict sigev)
/*[[[body:libc_lio_listio64]]]*/
{
	return start_aio_listio(mode, (struct aio *const *)list, nent, sigev);
}
#endif /* MAGIC:alias */
/*[[[end:libc_lio_listio64]]]*/


/*[[[head:libc_aio_suspendt64,hash:CRC-32=0x9377546a]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_aio_suspendt64, libc_aio_suspend);
#else /* MAGIC:alias */
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
INTERN ATTR_SECTION(".text.crt.utility.aio") ATTR_INS(1, 2) int
NOTHROW_NCX(LIBCCALL libc_aio_suspendt64)(struct aiocb const *const list[],
                                          __STDC_INT_AS_SIZE_T nent,
                                          struct timespec64 const *__restrict rel_timeout)
/*[[[body:libc_aio_suspendt64]]]*/
{
	return waitfor_aio((struct aio *const *)list, nent, rel_timeout);
}
#endif /* MAGIC:alias */
/*[[[end:libc_aio_suspendt64]]]*/


/* Because of binary compatibility between the 32-bit and 64-bit variant, the
 * following functions  can always  be defined  as identical  to each  other! */
/*[[[impl:libc_aio_fsync64]]]*/
/*[[[impl:libc_aio_error64]]]*/
/*[[[impl:libc_aio_return64]]]*/
/*[[[impl:libc_aio_cancel64]]]*/
/*[[[impl:libc_aio_suspend64]]]*/
/*[[[impl:libc_aio_suspend64t64]]]*/
DEFINE_INTERN_WEAK_ALIAS(libc_aio_fsync64, libc_aio_fsync);
DEFINE_INTERN_WEAK_ALIAS(libc_aio_error64, libc_aio_error);
DEFINE_INTERN_WEAK_ALIAS(libc_aio_return64, libc_aio_return);
DEFINE_INTERN_WEAK_ALIAS(libc_aio_cancel64, libc_aio_cancel);
DEFINE_INTERN_WEAK_ALIAS(libc_aio_suspend64, libc_aio_suspend);
DEFINE_INTERN_WEAK_ALIAS(libc_aio_suspend64t64, libc_aio_suspendt64);


/*[[[head:libc_aio_init,hash:CRC-32=0x9f2639e0]]]*/
/* >> aio_init(3) */
INTERN ATTR_SECTION(".text.crt.utility.aio") ATTR_IN(1) void
NOTHROW_NCX(LIBCCALL libc_aio_init)(struct aioinit const *init)
/*[[[body:libc_aio_init]]]*/
{
	size_t threads = init->aio_threads;
	if (threads < 1)
		threads = 1; /* Need at least 1 thread! */
	aiolimit_threads = threads;
	aiolimit_timeout = init->aio_idle_time;
}
/*[[[end:libc_aio_init]]]*/

/*[[[start:exports,hash:CRC-32=0x91b3c220]]]*/
DEFINE_PUBLIC_ALIAS(aio_read, libc_aio_read);
DEFINE_PUBLIC_ALIAS(aio_write, libc_aio_write);
DEFINE_PUBLIC_ALIAS(aio_fsync, libc_aio_fsync);
DEFINE_PUBLIC_ALIAS(lio_listio, libc_lio_listio);
DEFINE_PUBLIC_ALIAS(aio_error, libc_aio_error);
DEFINE_PUBLIC_ALIAS(aio_return, libc_aio_return);
DEFINE_PUBLIC_ALIAS(aio_cancel, libc_aio_cancel);
DEFINE_PUBLIC_ALIAS(aio_suspend, libc_aio_suspend);
DEFINE_PUBLIC_ALIAS(aio_read64, libc_aio_read64);
DEFINE_PUBLIC_ALIAS(aio_write64, libc_aio_write64);
DEFINE_PUBLIC_ALIAS(aio_fsync64, libc_aio_fsync64);
DEFINE_PUBLIC_ALIAS(lio_listio64, libc_lio_listio64);
DEFINE_PUBLIC_ALIAS(aio_error64, libc_aio_error64);
DEFINE_PUBLIC_ALIAS(aio_return64, libc_aio_return64);
DEFINE_PUBLIC_ALIAS(aio_cancel64, libc_aio_cancel64);
DEFINE_PUBLIC_ALIAS(aio_suspend64, libc_aio_suspend64);
DEFINE_PUBLIC_ALIAS(aio_suspendt64, libc_aio_suspendt64);
DEFINE_PUBLIC_ALIAS(aio_suspend64t64, libc_aio_suspend64t64);
DEFINE_PUBLIC_ALIAS(aio_init, libc_aio_init);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_AIO_C */
