/* HASH CRC-32:0xa078e193 */
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
#ifndef __local_gmtime64_r_defined
#define __local_gmtime64_r_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dos_gmtime64_s_defined
#define __local___localdep_dos_gmtime64_s_defined 1
#ifdef __CRT_HAVE__gmtime64_s
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_gmtime64_s,(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time64_t const *__restrict __timer),_gmtime64_s,(__tp,__timer))
#elif defined(__CRT_HAVE__gmtime32_s)
__NAMESPACE_LOCAL_END
#include <libc/local/time/dos_gmtime64_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dos_gmtime64_s __LIBC_LOCAL_NAME(dos_gmtime64_s)
#else /* ... */
#undef __local___localdep_dos_gmtime64_s_defined
#endif /* !... */
#endif /* !__local___localdep_dos_gmtime64_s_defined */
__NAMESPACE_LOCAL_END
#if defined(__BUILDING_LIBC) || (!defined(__CRT_HAVE__gmtime64_s) && !defined(__CRT_HAVE__gmtime32_s))
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

#endif /* __BUILDING_LIBC || (!__CRT_HAVE__gmtime64_s && !__CRT_HAVE__gmtime32_s) */
#ifndef __isleap
#define __isleap(__year) ((__year)%4 == 0 && ((__year)%100 != 0 || (__year)%400 == 0))
#endif /* !__isleap */
#ifndef __daystoyears
#define __daystoyears(__n_days)  ((400*((__n_days)+1))/146097)
#endif /* !__daystoyears */
#ifndef __yearstodays
#define __yearstodays(__n_years) (((146097*(__n_years))/400)/*-1*/) /* rounding error? */
#endif /* !__yearstodays */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(gmtime64_r) __ATTR_NONNULL((1, 2)) struct __NAMESPACE_STD_SYM tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(gmtime64_r))(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp) {









































#if defined(__CRT_HAVE__gmtime64_s) || defined(__CRT_HAVE__gmtime32_s)
	return __localdep_dos_gmtime64_s(__tp, __timer) ? __NULLPTR : __tp;
#else /* __CRT_HAVE__gmtime64_s || __CRT_HAVE__gmtime32_s */
	__time64_t __t; int __i;
	__UINT16_TYPE__ const *__monthvec;
	__t = *__timer;
	__tp->tm_sec  = (int)(__t % 60);
	__tp->tm_min  = (int)((__t/60) % 60);
	__tp->tm_hour = (int)((__t/(60*60)) % 24);
	__t /= 86400; /* SECONDS_PER_DAY */
	__t += __yearstodays(1970); /* UNIX_TIME_START_YEAR */
	__tp->tm_wday = (int)(__t % 7); /* DAYS_PER_WEEK */
	__tp->tm_year = (int)__daystoyears(__t);
	__t -= __yearstodays(__tp->tm_year);
	__tp->tm_yday = (int)__t;
	__monthvec = __NAMESPACE_LOCAL_SYM __time_monthstart_yday[__isleap(__tp->tm_year)];
	for (__i = 1; __i < 12; ++__i)
		if (__monthvec[__i] >= __t)
			break;
	__tp->tm_mon = __i - 1;
	__t -= __monthvec[__i - 1];
	__tp->tm_mday = __t + 1;
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
	__tp->tm_year -= 1900;
	return __tp;
#endif /* !__CRT_HAVE__gmtime64_s && !__CRT_HAVE__gmtime32_s */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_gmtime64_r_defined
#define __local___localdep_gmtime64_r_defined 1
#define __localdep_gmtime64_r __LIBC_LOCAL_NAME(gmtime64_r)
#endif /* !__local___localdep_gmtime64_r_defined */
#endif /* !__local_gmtime64_r_defined */
