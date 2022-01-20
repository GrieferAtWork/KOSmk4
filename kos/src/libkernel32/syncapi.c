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
#ifndef GUARD_LIBKERNEL32_SYNCAPI_C
#define GUARD_LIBKERNEL32_SYNCAPI_C 1
#define _KOS_ALTERATIONS_SOURCE 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"

#include <hybrid/atomic.h>

#include <kos/futex.h>
#include <kos/ioctl/fd.h>
#include <kos/types.h>
#include <nt/handleapi.h>
#include <nt/synchapi.h>
#include <nt/types.h>
#include <sys/poll.h>

#include <assert.h>
#include <errno.h>
#include <malloca.h>
#include <pthread.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

DECL_BEGIN


/************************************************************************/
/* CRITICAL_SECTION                                                     */
/************************************************************************/
#define DEFAULT_SPIN_COUNT 8
DEFINE_PUBLIC_ALIAS(EnterCriticalSection, libk32_EnterCriticalSection);
DEFINE_PUBLIC_ALIAS(LeaveCriticalSection, libk32_LeaveCriticalSection);
DEFINE_PUBLIC_ALIAS(TryEnterCriticalSection, libk32_TryEnterCriticalSection);
DEFINE_PUBLIC_ALIAS(DeleteCriticalSection, libk32_DeleteCriticalSection);
DEFINE_PUBLIC_ALIAS(SetCriticalSectionSpinCount, libk32_SetCriticalSectionSpinCount);
DEFINE_PUBLIC_ALIAS(InitializeCriticalSectionEx, libk32_InitializeCriticalSectionEx);
DEFINE_PUBLIC_ALIAS(InitializeCriticalSectionAndSpinCount, libk32_InitializeCriticalSectionAndSpinCount);
DEFINE_PUBLIC_ALIAS(InitializeCriticalSection, libk32_InitializeCriticalSection);

INTERN WINBOOL WINAPI
libk32_TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
	if (ATOMIC_CMPXCH(lpCriticalSection->LockSemaphore, 0, 1)) {
		/* Initial lock. */
		lpCriticalSection->OwningThread = pthread_self();
		return TRUE;
	}

	/* Check for lock recursion. */
	if (lpCriticalSection->OwningThread == pthread_self()) {
		ATOMIC_INC(lpCriticalSection->LockSemaphore);
		return TRUE;
	}

	/* Lock not held */
	return FALSE;
}

INTERN VOID WINAPI
libk32_EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
	ULONG_PTR spin;
again:
	if (libk32_TryEnterCriticalSection(lpCriticalSection))
		return;
	for (spin = ATOMIC_READ(lpCriticalSection->SpinCount); spin; --spin) {
		pthread_yield();
		if (libk32_TryEnterCriticalSection(lpCriticalSection))
			return;
	}

	/* Do a blocking wait for `LockSemaphore' to become `0' */
	futex_waituntil(&lpCriticalSection->LockSemaphore, 0);
	goto again;
}

INTERN VOID WINAPI
libk32_LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
	assertf(lpCriticalSection->OwningThread == pthread_self(),
	        "You're not holding this lock");
	assert(lpCriticalSection->LockSemaphore != 0);
	if (lpCriticalSection->LockSemaphore == 1) {
		/* Last lock went away. */
		lpCriticalSection->OwningThread = 0;
		ATOMIC_WRITE(lpCriticalSection->LockSemaphore, 0);
		futex_wake(&lpCriticalSection->LockSemaphore, 1);
	} else {
		ATOMIC_DEC(lpCriticalSection->LockSemaphore);
	}
}

INTERN VOID WINAPI
libk32_DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
	futex_wake(&lpCriticalSection->LockSemaphore);
}

INTERN DWORD WINAPI
libk32_SetCriticalSectionSpinCount(LPCRITICAL_SECTION lpCriticalSection,
                                   DWORD dwSpinCount) {
	return ATOMIC_XCH(lpCriticalSection->SpinCount, dwSpinCount);
}

INTERN WINBOOL WINAPI
libk32_InitializeCriticalSectionEx(LPCRITICAL_SECTION lpCriticalSection,
                                   DWORD dwSpinCount, DWORD Flags) {
	(void)Flags; /* Ignored */
	bzero(lpCriticalSection, sizeof(*lpCriticalSection));
	lpCriticalSection->SpinCount = dwSpinCount;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_InitializeCriticalSectionAndSpinCount(LPCRITICAL_SECTION lpCriticalSection,
                                             DWORD dwSpinCount) {
	return libk32_InitializeCriticalSectionEx(lpCriticalSection, dwSpinCount, DEFAULT_SPIN_COUNT);
}

INTERN VOID WINAPI
libk32_InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
	libk32_InitializeCriticalSectionEx(lpCriticalSection, DEFAULT_SPIN_COUNT, 0);
}
/************************************************************************/






/************************************************************************/
/* MISC                                                                 */
/************************************************************************/
DEFINE_PUBLIC_ALIAS(WaitForMultipleObjects, libk32_WaitForMultipleObjects);
DEFINE_PUBLIC_ALIAS(WaitForMultipleObjectsEx, libk32_WaitForMultipleObjectsEx);
DEFINE_PUBLIC_ALIAS(WaitForSingleObject, libk32_WaitForSingleObject);
DEFINE_PUBLIC_ALIAS(WaitForSingleObjectEx, libk32_WaitForSingleObjectEx);
DEFINE_PUBLIC_ALIAS(SleepEx, libk32_SleepEx);
DEFINE_PUBLIC_ALIAS(Sleep, libk32_Sleep);

PRIVATE DWORD WINAPI
libk32_WaitForObjects(DWORD nCount, CONST HANDLE *lpHandles,
                      DWORD dwMilliseconds) {
	DWORD i, result;
	struct pollfd *pfd;
	ssize_t status;
	pfd = (struct pollfd *)malloca(nCount, sizeof(struct pollfd));
	if (!pfd)
		return WAIT_FAILED;
again:
	for (i = 0; i < nCount; ++i) {
		HANDLE hand = lpHandles[i];
		if (!NTHANDLE_ISFD(hand)) {
			errno = EBADF;
			goto err;
		}
		pfd[i].fd      = NTHANDLE_ASFD(hand);
		pfd[i].events  = POLLSELECT_READFDS;
		pfd[i].revents = 0;
	}
	if (dwMilliseconds != INFINITE) {
		struct timespec ts;
		ts.tv_sec  = 0;
		ts.tv_nsec = 0;
		ts.add_milliseconds(dwMilliseconds);
		status = ppoll(pfd, nCount, &ts, NULL);
	} else {
		status = ppoll(pfd, nCount, NULL, NULL);
	}
	if (status < 0) {
		if (errno == EINTR) {
			result = WAIT_IO_COMPLETION;
			goto done;
		}
		goto err;
	}
	/* Check for signaled objects. */
	for (i = 0; i < nCount; ++i) {
		if (pfd[i].revents != 0) {
			/* TODO: Based on object type, we (may) need to do additional actions!
			 * e.g.: In case of an eventfd, we must do a non-blocking ticket acquire */
			return WAIT_OBJECT_0 + i;
		}
	}
	goto again;
err:
	result = WAIT_FAILED;
done:
	freea(pfd);
	return result;
}

INTERN DWORD WINAPI
libk32_WaitForMultipleObjectsEx(DWORD nCount, CONST HANDLE *lpHandles, WINBOOL bWaitAll,
                                DWORD dwMilliseconds, WINBOOL bAlertable) {
	DWORD result;
	if (bWaitAll && nCount > 1) {
		DWORD i;
		result = WAIT_OBJECT_0;
		for (i = 0; i < nCount; ++i) {
			/* XXX: `dwMilliseconds' is supposed to be the TOTAL! */
			result = libk32_WaitForMultipleObjectsEx(1, &lpHandles[i], FALSE,
			                                         dwMilliseconds, bAlertable);
			if (result != WAIT_OBJECT_0)
				break;
		}
		return result;
	}
	do {
		result = libk32_WaitForObjects(nCount, lpHandles, dwMilliseconds);
	} while (result == WAIT_IO_COMPLETION && bAlertable);
	return result;
}

INTERN DWORD WINAPI
libk32_WaitForMultipleObjects(DWORD nCount, CONST HANDLE *lpHandles,
                              WINBOOL bWaitAll, DWORD dwMilliseconds) {
	return libk32_WaitForMultipleObjectsEx(nCount, lpHandles, bWaitAll, dwMilliseconds, FALSE);
}

INTERN DWORD WINAPI
libk32_WaitForSingleObjectEx(HANDLE hHandle, DWORD dwMilliseconds, WINBOOL bAlertable) {
	return libk32_WaitForMultipleObjectsEx(1, &hHandle, FALSE, dwMilliseconds, bAlertable);
}

INTERN DWORD WINAPI
libk32_WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds) {
	return libk32_WaitForSingleObjectEx(hHandle, dwMilliseconds, FALSE);
}

INTERN DWORD WINAPI
libk32_SleepEx(DWORD dwMilliseconds, WINBOOL bAlertable) {
	struct timespec ts, rem;
	ts.tv_sec  = 0;
	ts.tv_nsec = 0;
	ts.add_milliseconds(dwMilliseconds);
	for (;;) {
		if (nanosleep(&ts, &rem))
			break;
		if (errno == EINTR && bAlertable)
			return WAIT_IO_COMPLETION;
		ts = rem;
	}
	return 0;
}

INTERN VOID WINAPI
libk32_Sleep(DWORD dwMilliseconds) {
	libk32_SleepEx(dwMilliseconds, FALSE);
}
/************************************************************************/


DECL_END

#endif /* !GUARD_LIBKERNEL32_SYNCAPI_C */
