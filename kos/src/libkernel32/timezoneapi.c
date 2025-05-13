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
#ifndef GUARD_LIBKERNEL32_TIMEZONEAPI_C
#define GUARD_LIBKERNEL32_TIMEZONEAPI_C 1
#define _TIME64_SOURCE 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <nt/__stdinc.h>
#include <nt/timezoneapi.h>
#include <nt/types.h>
#include <sys/time.h>

#include <string.h>
#include <time.h>

DECL_BEGIN

/************************************************************************/
INTDEF FILETIME CC libk32_TimeSpecToFileTime(struct timespec64 const *ts);
INTDEF struct timespec64 CC libk32_FileTimeToTimeSpec(CONST FILETIME *ft);

INTERN WINBOOL WINAPI
libk32_SystemTimeToTzSpecificLocalTime(CONST TIME_ZONE_INFORMATION *lpTimeZoneInformation,
                                       CONST SYSTEMTIME *lpUniversalTime, LPSYSTEMTIME lpLocalTime) {
	(void)lpTimeZoneInformation;
	*lpLocalTime = *lpUniversalTime;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_TzSpecificLocalTimeToSystemTime(CONST TIME_ZONE_INFORMATION *lpTimeZoneInformation,
                                       CONST SYSTEMTIME *lpLocalTime, LPSYSTEMTIME lpUniversalTime) {
	(void)lpTimeZoneInformation;
	*lpUniversalTime = *lpLocalTime;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_FileTimeToSystemTime(CONST FILETIME *lpFileTime, LPSYSTEMTIME lpSystemTime) {
	struct timespec64 ts;
	struct tm tms;
	ts = libk32_FileTimeToTimeSpec(lpFileTime);
	gmtime64_r(&ts.tv_sec, &tms);
	lpSystemTime->wYear         = tms.tm_year + 1900;
	lpSystemTime->wMonth        = tms.tm_mon + 1;
	lpSystemTime->wDayOfWeek    = tms.tm_wday;
	lpSystemTime->wDay          = tms.tm_wday;
	lpSystemTime->wHour         = tms.tm_hour;
	lpSystemTime->wMinute       = tms.tm_min;
	lpSystemTime->wSecond       = tms.tm_sec;
	lpSystemTime->wMilliseconds = ts.tv_nsec / 1000000;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_SystemTimeToFileTime(CONST SYSTEMTIME *lpSystemTime, LPFILETIME lpFileTime) {
	struct timespec64 ts;
	struct tm tms;
	tms.tm_year = lpSystemTime->wYear - 1900;
	tms.tm_mon  = lpSystemTime->wMonth - 1;
	tms.tm_wday = lpSystemTime->wDayOfWeek;
	tms.tm_wday = lpSystemTime->wDay;
	tms.tm_hour = lpSystemTime->wHour;
	tms.tm_min  = lpSystemTime->wMinute;
	tms.tm_sec  = lpSystemTime->wSecond;
	ts.tv_sec   = mktime64(&tms);
	ts.tv_nsec  = lpSystemTime->wMilliseconds * 1000000;
	*lpFileTime = libk32_TimeSpecToFileTime(&ts);
	return TRUE;
}

INTERN DWORD WINAPI
libk32_GetTimeZoneInformation(LPTIME_ZONE_INFORMATION lpTimeZoneInformation) {
	struct tm tms;
	struct timeval ts;
	struct timezone tz;
	bzero(lpTimeZoneInformation, sizeof(*lpTimeZoneInformation));
	lpTimeZoneInformation->StandardName[0] = 'U';
	lpTimeZoneInformation->StandardName[1] = 'n';
	lpTimeZoneInformation->StandardName[2] = 'k';
	lpTimeZoneInformation->StandardName[3] = 'n';
	lpTimeZoneInformation->StandardName[4] = 'o';
	lpTimeZoneInformation->StandardName[5] = 'w';
	lpTimeZoneInformation->StandardName[6] = 'n';
	lpTimeZoneInformation->StandardName[7] = '\0';
	memcpy(lpTimeZoneInformation->DaylightName,
	       lpTimeZoneInformation->StandardName,
	       8, sizeof(WCHAR));
	if (gettimeofday(&ts, &tz) != 0)
		return TIME_ZONE_ID_INVALID;
	gmtime_r(&ts.tv_sec, &tms);
	/* The DST stuff below may be incorrect... /\°~°/\ */
	lpTimeZoneInformation->Bias         = tz.tz_minuteswest;
	lpTimeZoneInformation->StandardBias = tz.tz_minuteswest;
	lpTimeZoneInformation->DaylightBias = tz.tz_minuteswest;
	if (tz.tz_dsttime == 0)
		return TIME_ZONE_ID_UNKNOWN;
	if (tms.tm_isdst) {
		lpTimeZoneInformation->DaylightBias -= 60;
		return TIME_ZONE_ID_DAYLIGHT;
	}
	lpTimeZoneInformation->StandardBias -= 60;
	return TIME_ZONE_ID_STANDARD;
}

DEFINE_PUBLIC_ALIAS(SystemTimeToTzSpecificLocalTime, libk32_SystemTimeToTzSpecificLocalTime);
DEFINE_PUBLIC_ALIAS(TzSpecificLocalTimeToSystemTime, libk32_TzSpecificLocalTimeToSystemTime);
DEFINE_PUBLIC_ALIAS(FileTimeToSystemTime, libk32_FileTimeToSystemTime);
DEFINE_PUBLIC_ALIAS(SystemTimeToFileTime, libk32_SystemTimeToFileTime);
DEFINE_PUBLIC_ALIAS(GetTimeZoneInformation, libk32_GetTimeZoneInformation);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_TIMEZONEAPI_C */
