/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBKERNEL32_SYSINFOAPI_C
#define GUARD_LIBKERNEL32_SYSINFOAPI_C 1
#define _GNU_SOURCE 1

#include "api.h"

#include <kos/kernel/paging.h>
#include <kos/types.h>
#include <nt/sysinfoapi.h>
#include <sys/sysinfo.h>
#include <sys/time.h>

#include <time.h>
#include <unistd.h>

DECL_BEGIN

/************************************************************************/
INTDEF FILETIME CC libk32_TimeSpecToFileTime(struct timespec const *ts);

INTERN VOID WINAPI
libk32_GetSystemTime(LPSYSTEMTIME lpSystemTime) {
	struct timeval tv;
	struct tm tms;
	TRACE("GetSystemTime(%p)", lpSystemTime);
	gettimeofday(&tv, NULL);
	gmtime_r(&tv.tv_sec, &tms);
	lpSystemTime->wYear         = tms.tm_year + 1900;
	lpSystemTime->wMonth        = tms.tm_mon + 1;
	lpSystemTime->wDayOfWeek    = tms.tm_wday;
	lpSystemTime->wDay          = tms.tm_wday;
	lpSystemTime->wHour         = tms.tm_hour;
	lpSystemTime->wMinute       = tms.tm_min;
	lpSystemTime->wSecond       = tms.tm_sec;
	lpSystemTime->wMilliseconds = tv.tv_usec / 1000;
}

INTERN VOID WINAPI
libk32_GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime) {
	struct timespec ts;
	struct timeval tv;
	TRACE("GetSystemTimeAsFileTime(%p)", lpSystemTimeAsFileTime);
	gettimeofday(&tv, NULL);
	TIMEVAL_TO_TIMESPEC(&tv, &ts);
	*lpSystemTimeAsFileTime = libk32_TimeSpecToFileTime(&ts);
}

DEFINE_INTERN_ALIAS(libk32_GetSystemTimePreciseAsFileTime, libk32_GetSystemTimeAsFileTime);

INTERN VOID WINAPI
libk32_GetLocalTime(LPSYSTEMTIME lpSystemTime) {
	struct timeval tv;
	struct tm tms;
	TRACE("GetLocalTime(%p)", lpSystemTime);
	gettimeofday(&tv, NULL);
	localtime_r(&tv.tv_sec, &tms);
	lpSystemTime->wYear         = tms.tm_year + 1900;
	lpSystemTime->wMonth        = tms.tm_mon + 1;
	lpSystemTime->wDayOfWeek    = tms.tm_wday;
	lpSystemTime->wDay          = tms.tm_wday;
	lpSystemTime->wHour         = tms.tm_hour;
	lpSystemTime->wMinute       = tms.tm_min;
	lpSystemTime->wSecond       = tms.tm_sec;
	lpSystemTime->wMilliseconds = tv.tv_usec / 1000;
}

INTERN VOID WINAPI
libk32_GetSystemInfo(LPSYSTEM_INFO lpSystemInfo) {
	TRACE("GetSystemInfo(%p)", lpSystemInfo);
	lpSystemInfo->dwOemId    = 0; /* ??? */
	lpSystemInfo->dwPageSize = getpagesize();
#ifdef USERSPACE_BASE
	lpSystemInfo->lpMinimumApplicationAddress = (LPVOID)USERSPACE_BASE;
#else /* USERSPACE_BASE */
	lpSystemInfo->lpMinimumApplicationAddress = (LPVOID)0;
#endif /* !USERSPACE_BASE */
#ifdef USERSPACE_END
	lpSystemInfo->lpMaximumApplicationAddress = (LPVOID)(USERSPACE_END - 1);
#else /* USERSPACE_END */
	lpSystemInfo->lpMaximumApplicationAddress = (LPVOID)(-1);
#endif /* !USERSPACE_END */
	lpSystemInfo->dwActiveProcessorMask   = ((DWORD_PTR)1 << get_nprocs()) - 1; /* Not really correct, but good enough */
	lpSystemInfo->dwNumberOfProcessors    = get_nprocs_conf();
	lpSystemInfo->dwProcessorType         = 0;                        /* ??? */
	lpSystemInfo->dwAllocationGranularity = lpSystemInfo->dwPageSize; /* ??? */
	lpSystemInfo->wProcessorLevel         = 0;                        /* ??? */
	lpSystemInfo->wProcessorRevision      = 0;                        /* ??? */
}

DEFINE_INTERN_ALIAS(libk32_GetNativeSystemInfo, libk32_GetSystemInfo);

INTERN ULONGLONG WINAPI
libk32_GetTickCount64(VOID) {
	struct timespec ts;
	TRACE("GetTickCount64()");
	if unlikely(clock_gettime(CLOCK_BOOTTIME, &ts)) {
		struct timeval tv;
		if unlikely(gettimeofday(&tv, NULL)) {
			ts.tv_sec  = time(NULL);
			ts.tv_nsec = 0;
		}
		ts.tv_sec  = tv.tv_sec;
		ts.tv_nsec = tv.tv_usec * 1000;
	}
	return ((ULONGLONG)ts.tv_sec * 1000 +
	        (ULONGLONG)ts.tv_nsec / 1000000);
}

INTERN DWORD WINAPI
libk32_GetTickCount(VOID) {
	TRACE("GetTickCount()");
	return (DWORD)libk32_GetTickCount64();
}

DEFINE_PUBLIC_ALIAS(GetSystemTime, libk32_GetSystemTime);
DEFINE_PUBLIC_ALIAS(GetSystemTimeAsFileTime, libk32_GetSystemTimeAsFileTime);
DEFINE_PUBLIC_ALIAS(GetSystemTimePreciseAsFileTime, libk32_GetSystemTimePreciseAsFileTime);
DEFINE_PUBLIC_ALIAS(GetLocalTime, libk32_GetLocalTime);
DEFINE_PUBLIC_ALIAS(GetSystemInfo, libk32_GetSystemInfo);
DEFINE_PUBLIC_ALIAS(GetNativeSystemInfo, libk32_GetNativeSystemInfo);
DEFINE_PUBLIC_ALIAS(GetTickCount, libk32_GetTickCount);
DEFINE_PUBLIC_ALIAS(GetTickCount64, libk32_GetTickCount64);
/************************************************************************/


DECL_END

#endif /* !GUARD_LIBKERNEL32_SYSINFOAPI_C */
