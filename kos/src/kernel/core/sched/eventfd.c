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
#ifndef GUARD_KERNEL_SRC_SCHED_EVENTFD_C
#define GUARD_KERNEL_SRC_SCHED_EVENTFD_C 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <sched/eventfd.h>
#include <sched/signal.h>

#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <sys/eventfd.h>

#include <assert.h>
#include <stdint.h>

DECL_BEGIN

PRIVATE ATTR_MALLOC WUNUSED ATTR_RETNONNULL
REF struct eventfd *KCALL eventfd_create(u64 value) THROWS(E_BADALLOC) {
	struct eventfd *result;
	result = (struct eventfd *)kmalloc(sizeof(struct eventfd), GFP_NORMAL);
	result->ef_refcnt = 1;
	sig_init(&result->ef_signal);
	atomic64_init(&result->ef_value, value);
	return result;
}

DEFINE_HANDLE_REFCNT_FUNCTIONS(eventfd_fence, struct eventfd);
DEFINE_INTERN_ALIAS(handle_eventfd_sema_incref, handle_eventfd_fence_incref);
DEFINE_INTERN_ALIAS(handle_eventfd_sema_decref, handle_eventfd_fence_decref);
DEFINE_INTERN_ALIAS(handle_eventfd_sema_refcnt, handle_eventfd_fence_refcnt);

INTERN size_t KCALL
handle_eventfd_fence_read(struct eventfd *__restrict self,
                          USER CHECKED void *dst,
                          size_t num_bytes, iomode_t mode) {
	/* Fence-like read-operation */
	u64 val;
	if unlikely(num_bytes < 8) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_EVENTFD_BUFSIZE,
		      num_bytes);
	}
again:
	val = atomic64_xch(&self->ef_value, 0);
	if (!val) {
		if (mode & IO_NONBLOCK) {
			if (mode & IO_NODATAZERO)
				return 0;
			THROW(E_WOULDBLOCK_WAITFORSIGNAL);
		}
		task_connect(&self->ef_signal);
		val = atomic64_xch(&self->ef_value, 0);
		if likely(val == 0) {
			task_waitfor();
			goto again;
		}
		task_disconnectall();
	}
	/* If writing has just become available, wake up writers. */
	if (val >= (u64)UINT64_C(0xfffffffffffffffe))
		sig_broadcast(&self->ef_signal);
	UNALIGNED_SET64((u64 *)dst, val);
	return 8;
}

INTERN size_t KCALL
handle_eventfd_sema_read(struct eventfd *__restrict self,
                         USER CHECKED void *dst,
                         size_t num_bytes, iomode_t mode) {
	/* Semaphore-like read-operation */
	u64 val;
	if unlikely(num_bytes < 8) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_EVENTFD_BUFSIZE,
		      num_bytes);
	}
	for (;;) {
		/* Decrement by one if non-zero, and wait if zero. */
		val = atomic64_read(&self->ef_value);
		if (!val) {
			if (mode & IO_NONBLOCK) {
				if (mode & IO_NODATAZERO)
					return 0;
				THROW(E_WOULDBLOCK_WAITFORSIGNAL);
			}
			task_connect(&self->ef_signal);
			val = atomic64_read(&self->ef_value);
			if likely(val == 0) {
				task_waitfor();
				continue;
			}
			task_disconnectall();
		}
		if (atomic64_cmpxch(&self->ef_value, val, val - 1))
			break;
	}
	/* If writing has just become available, wake up writers. */
	if (val >= (u64)UINT64_C(0xfffffffffffffffe))
		sig_broadcast(&self->ef_signal);
	UNALIGNED_SET64((u64 *)dst, val);
	return 8;
}


INTERN size_t KCALL
handle_eventfd_fence_write(struct eventfd *__restrict self,
                           USER CHECKED void const *src,
                           size_t num_bytes, iomode_t UNUSED(mode)) {
	u64 val, oldval, newval;
	if unlikely(num_bytes < 8) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_EVENTFD_BUFSIZE,
		      num_bytes);
	}
	val = UNALIGNED_GET64((u64 const *)src);
	for (;;) {
		oldval = atomic64_read(&self->ef_value);
		if (OVERFLOW_UMUL(oldval, val, &newval) ||
		    newval > (u64)UINT64_C(0xfffffffffffffffe)) {
			/* Must wait for writing to become possible / invalid argument. */
			if unlikely(val == (u64)UINT64_C(0xffffffffffffffff)) {
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_EVENTFD_WRITE_FFFFFFFFFFFFFFFFh,
				      (uintptr_t)-1);
			}
			/* Wait for something to happen. */
			task_connect(&self->ef_signal);
			newval = atomic64_read(&self->ef_value);
			if unlikely(newval != oldval) {
				task_disconnectall();
				continue;
			}
			task_waitfor();
			continue;
		}
		if (!atomic64_cmpxch(&self->ef_value, oldval, newval))
			continue;
		/* Wake up a single reader. */
		sig_send(&self->ef_signal);
	}
	return 8;
}


LOCAL ATTR_PURE WUNUSED NONNULL((1)) poll_mode_t KCALL
evenfd_getavail(struct eventfd *__restrict self) {
	u64 value;
	poll_mode_t result = 0;
	value = atomic64_read(&self->ef_value);
	if (value > 0)
		result |= POLLINMASK; /* read() wouldn't block */
	if (value < (u64)UINT64_C(0xfffffffffffffffe))
		result |= POLLOUTMASK; /* write() wouldn't block */
	return result;
}

DEFINE_INTERN_ALIAS(handle_eventfd_sema_write, handle_eventfd_fence_write);

/* TODO: handle_eventfd_fence_readv */
/* TODO: handle_eventfd_fence_writev */
/* TODO: handle_eventfd_sema_readv */
DEFINE_INTERN_ALIAS(handle_eventfd_sema_writev, handle_eventfd_fence_writev);


INTERN void KCALL
handle_eventfd_fence_pollconnect(struct eventfd *__restrict self,
                                 poll_mode_t UNUSED(what)) {
	task_connect_for_poll(&self->ef_signal);
}

INTERN ATTR_PURE poll_mode_t KCALL
handle_eventfd_fence_polltest(struct eventfd *__restrict self,
                              poll_mode_t what) {
	/* Check what operations are currently available. */
	return evenfd_getavail(self) & what;
}

DEFINE_INTERN_ALIAS(handle_eventfd_sema_pollconnect, handle_eventfd_fence_pollconnect);
DEFINE_INTERN_ALIAS(handle_eventfd_sema_polltest, handle_eventfd_fence_polltest);





/************************************************************************/
/* eventfd2(), eventfd()                                                */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_EVENTFD2
DEFINE_SYSCALL2(fd_t, eventfd2,
                syscall_ulong_t, initval,
                syscall_ulong_t, flags) {
	unsigned int result;
	REF struct eventfd *efd;
	VALIDATE_FLAGSET(flags,
	                 EFD_SEMAPHORE | EFD_NONBLOCK | EFD_CLOEXEC,
	                 E_INVALID_ARGUMENT_CONTEXT_EVENTFD_FLAGS);
#if __SIZEOF_SYSCALL_LONG_T__ >= 8
	if (initval >= (uint64_t)-1) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_EVENTFD_WRITE_FFFFFFFFFFFFFFFFh,
		      initval);
	}
#endif /* __SIZEOF_SYSCALL_LONG_T__ >= 8 */
	efd = eventfd_create((u64)initval);
	TRY {
		struct handle hnd;
		/* Setup the handle.
		 * Note   that  under  KOS,   the  fence  vs.  semaphore
		 * differentiation is made using the handle's type code. */
		hnd.h_type = HANDLE_TYPE_EVENTFD_FENCE;
		if (flags & EFD_SEMAPHORE)
			hnd.h_type = HANDLE_TYPE_EVENTFD_SEMA;
		/* Always grant read/write access to that both post() and wait() work. */
		hnd.h_mode = IO_RDWR;
		if (flags & EFD_NONBLOCK)
			hnd.h_mode |= IO_NONBLOCK;
		if (flags & EFD_CLOEXEC)
			hnd.h_mode |= IO_CLOEXEC;
		hnd.h_data = efd; /* Inherit reference */
		/* Install the eventfd handle. */
		result = handle_install(THIS_HANDLE_MANAGER, hnd);
	} EXCEPT {
		destroy(efd);
		RETHROW();
	}
	return (fd_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_EVENTFD2 */

#ifdef __ARCH_WANT_SYSCALL_EVENTFD
DEFINE_SYSCALL1(fd_t, eventfd,
                syscall_ulong_t, initval) {
	return sys_eventfd2(initval, 0);
}
#endif /* __ARCH_WANT_SYSCALL_EVENTFD */

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_EVENTFD_C */
