/* HASH CRC-32:0x61b211ca */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_normalize_struct_tm_defined
#define __local_normalize_struct_tm_defined
#include <__crt.h>
#include <bits/crt/tm.h>
#ifndef ____TIME_MONTH_NUMDAYS_DEFINED
#define ____TIME_MONTH_NUMDAYS_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA(__time_month_numdays)
__UINT8_TYPE__ const __time_month_numdays[2][12] = {
	{ 30, 31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31 },
	{ 30, 31, 29, 31, 30, 31, 30, 31, 30, 31, 30, 31 }
};
__NAMESPACE_LOCAL_END
#endif /* !____TIME_MONTH_NUMDAYS_DEFINED */
#ifndef ____TIME_MONTHSTART_YDAY_DEFINED
#define ____TIME_MONTHSTART_YDAY_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA(__time_monthstart_yday)
__UINT16_TYPE__ const __time_monthstart_yday[2][13] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};
__NAMESPACE_LOCAL_END
#endif /* !____TIME_MONTHSTART_YDAY_DEFINED */
#ifndef __isleap
#define __isleap(__year) ((__year) % 4 == 0 && ((__year) % 100 != 0 || (__year) % 400 == 0))
#endif /* !__isleap */
#ifndef __yearstodays
#define __yearstodays(__n_years) (((146097 * (__n_years)) / 400) /*-1*/) /* rounding error? */
#endif /* !__yearstodays */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(normalize_struct_tm) __ATTR_RETNONNULL __ATTR_INOUT(1) struct __NAMESPACE_STD_SYM tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(normalize_struct_tm))(struct __NAMESPACE_STD_SYM tm *__restrict __tp) {
	/* Normalize seconds. */
	if (__tp->tm_sec < 0) {
		unsigned int __delta;
		__delta = ((unsigned int)-__tp->tm_sec + 59) / 60;
		__tp->tm_min -= __delta;
		__tp->tm_sec += __delta * 60;
	} else if (__tp->tm_sec > 59) {
		unsigned int __delta;
		__delta = (unsigned int)__tp->tm_sec / 60;
		__tp->tm_min += __delta;
		__tp->tm_sec -= __delta * 60;
	}

	/* Normalize minutes. */
	if (__tp->tm_min < 0) {
		unsigned int __delta;
		__delta = ((unsigned int)-__tp->tm_min + 59) / 60;
		__tp->tm_hour -= __delta;
		__tp->tm_min += __delta * 60;
	} else if (__tp->tm_min > 59) {
		unsigned int __delta;
		__delta = (unsigned int)__tp->tm_min / 60;
		__tp->tm_hour += __delta;
		__tp->tm_min -= __delta * 60;
	}

	/* Normalize hours. */
	if (__tp->tm_hour < 0) {
		unsigned int __delta;
		__delta = ((unsigned int)-__tp->tm_sec + 23) / 24;
		__tp->tm_mday -= __delta;
		__tp->tm_hour += __delta * 24;
	} else if (__tp->tm_hour > 23) {
		unsigned int __delta;
		__delta = (unsigned int)__tp->tm_hour / 24;
		__tp->tm_mday += __delta;
		__tp->tm_hour -= __delta * 24;
	}

	for (;;) {
		/* Normalize month. */
		if (__tp->tm_mon < 0) {
			unsigned int __delta;
			__delta = ((unsigned int)-__tp->tm_mon + 11) / 12;
			__tp->tm_year -= __delta;
			__tp->tm_mon += __delta * 12;
		} else if (__tp->tm_mon > 11) {
			unsigned int __delta;
			__delta = (unsigned int)__tp->tm_mon / 12;
			__tp->tm_year += __delta;
			__tp->tm_mon -= __delta * 12;
		}

		/* Normalize day-of-the-month.
		 * Note that because of February (and leap years), we can only adjust by 1 month every time. */
		if (__tp->tm_mday < 1) {
			--__tp->tm_mon;
			__COMPILER_BARRIER(); /* Prevent GCC warning about sign stuff */
			if (__tp->tm_mon < 0) {
				__tp->tm_mon = 11;
				--__tp->tm_year;
			}
			__tp->tm_mday += __NAMESPACE_LOCAL_SYM __time_month_numdays[__isleap(1900 + __tp->tm_year)][__tp->tm_mon];
			continue;
		} else {
			unsigned int __current_month_days;
			__current_month_days = __NAMESPACE_LOCAL_SYM __time_month_numdays[__isleap(1900 + __tp->tm_year)][__tp->tm_mon];
			if ((unsigned int)(__tp->tm_mday - 1) >= __current_month_days) {
				__tp->tm_mday -= __current_month_days;
				++__tp->tm_mon;
				continue;
			}
		}
		break;
	}

	/* Figure out the year-day. */
	__tp->tm_yday = __NAMESPACE_LOCAL_SYM __time_monthstart_yday[__isleap(1900 + __tp->tm_year)][__tp->tm_mon];
	__tp->tm_yday += __tp->tm_mday;

	/* Figure out the week-day. */
	{
		__UINT64_TYPE__ __total_days;
		__total_days = __yearstodays(1900 + __tp->tm_year);
		__total_days += __tp->tm_yday;
		__tp->tm_wday = (int)(__total_days % 7);
	}

	/* Figure out if daylight savings time is currently on. */
	/* found here: "http://stackoverflow.com/questions/5590429/calculating-daylight-savings-time-from-only-date" */
	if (__tp->tm_mon < 2 || __tp->tm_mon > 10) {
		//January, February, and December are out.
		__tp->tm_isdst = 0;
	} else if (__tp->tm_mon > 2 && __tp->tm_mon < 10) {
		//April to October are in
		__tp->tm_isdst = 1;
	} else {
		int __previousSunday;
		__previousSunday = __tp->tm_mday - __tp->tm_wday;
		if (__tp->tm_mon == 2) {
			//In march, we are DST if our previous Sunday was on or after the 8th.
			__tp->tm_isdst = __previousSunday >= 8;
		} else {
			//In November we must be before the first Sunday to be dst.
			//That means the  previous Sunday must  be before the  1st.
			__tp->tm_isdst = __previousSunday <= 0;
		}
	}
	return __tp;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_normalize_struct_tm_defined
#define __local___localdep_normalize_struct_tm_defined
#define __localdep_normalize_struct_tm __LIBC_LOCAL_NAME(normalize_struct_tm)
#endif /* !__local___localdep_normalize_struct_tm_defined */
#endif /* !__local_normalize_struct_tm_defined */
