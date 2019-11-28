/* HASH CRC-32:0xb7599860 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ctime_r_defined
#define __local_ctime_r_defined 1
#ifndef __STRUCT_TM
#ifdef __tm_defined
#define __STRUCT_TM struct __NAMESPACE_STD_SYM tm
#else /* __tm_defined */
#define __STRUCT_TM struct __NAMESPACE_STD_SYM __NAMESPACE_STD_SYM tm
#ifndef __std_tm_defined
#define __std_tm_defined 1
__NAMESPACE_STD_BEGIN
struct __NAMESPACE_STD_SYM tm {
	int         tm_sec;      /* seconds [0, 61]. */
	int         tm_min;      /* minutes [0, 59]. */
	int         tm_hour;     /* hour [0, 23]. */
	int         tm_mday;     /* day of month [1, 31]. */
	int         tm_mon;      /* month of year [0, 11]. */
	int         tm_year;     /* years since 1900. */
	int         tm_wday;     /* day of week [0, 6] (Sunday = 0). */
	int         tm_yday;     /* day of year [0, 365]. */
	int         tm_isdst;    /* daylight savings flag. */
#ifdef __CRT_GLC
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* __CRT_GLC */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Dependency: "dos_ctime_s" from "time" */
#ifndef ____localdep_dos_ctime_s_defined
#define ____localdep_dos_ctime_s_defined 1
#if defined(__CRT_HAVE__ctime32_s) && defined(__USE_TIME_BITS64)
/* Equivalent to `asctime_r (localtime_r (timer, *TMP*), buf)' */
__CREDIRECT(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,__localdep_dos_ctime_s,(char __buf[26], __SIZE_TYPE__ __bufsize, __TM_TYPE(time) const *__restrict __timer),_ctime32_s,(__buf,__bufsize,__timer))
#elif defined(__CRT_HAVE__ctime64_s) && (!defined(__USE_TIME_BITS64))
/* Equivalent to `asctime_r (localtime_r (timer, *TMP*), buf)' */
__CREDIRECT(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,__localdep_dos_ctime_s,(char __buf[26], __SIZE_TYPE__ __bufsize, __TM_TYPE(time) const *__restrict __timer),_ctime64_s,(__buf,__bufsize,__timer))
#elif defined(__CRT_HAVE__ctime32_s) || defined(__CRT_HAVE__ctime64_s)
#include <local/time/dos_ctime_s.h>
/* Equivalent to `asctime_r (localtime_r (timer, *TMP*), buf)' */
#define __localdep_dos_ctime_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dos_ctime_s))
#else /* CUSTOM: dos_ctime_s */
#undef ____localdep_dos_ctime_s_defined
#endif /* dos_ctime_s... */
#endif /* !____localdep_dos_ctime_s_defined */

/* Dependency: "asctime_r" from "time" */
#ifndef ____localdep_asctime_r_defined
#define ____localdep_asctime_r_defined 1
#ifdef __CRT_HAVE_asctime_r
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
__CREDIRECT(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_asctime_r,(__STRUCT_TM const *__restrict __tp, char __buf[26]),asctime_r,(__tp,__buf))
#else /* LIBC: asctime_r */
#include <local/time/asctime_r.h>
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
#define __localdep_asctime_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asctime_r))
#endif /* asctime_r... */
#endif /* !____localdep_asctime_r_defined */

/* Dependency: "localtime_r" from "time" */
#ifndef ____localdep_localtime_r_defined
#define ____localdep_localtime_r_defined 1
#ifdef __CRT_HAVE_localtime_r
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_localtime_r,(__TM_TYPE(time) const *__restrict __timer, __STRUCT_TM *__restrict __tp),localtime_r,(__timer,__tp))
#else /* LIBC: localtime_r */
#include <local/time/localtime_r.h>
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
#define __localdep_localtime_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(localtime_r))
#endif /* localtime_r... */
#endif /* !____localdep_localtime_r_defined */

__NAMESPACE_LOCAL_BEGIN
/* Equivalent to `asctime_r (localtime_r (timer, *TMP*), buf)' */
__LOCAL_LIBC(ctime_r) __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ctime_r))(__TM_TYPE(time) const *__restrict __timer,
                                                     char __buf[26]) {
#line 1477 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE__ctime32_s) || defined(__CRT_HAVE__ctime64_s)
	return __localdep_dos_ctime_s(__buf, 26, __timer) ? __NULLPTR : __buf;
#else
#ifdef __std_tm_defined
	struct __NAMESPACE_STD_SYM tm __ltm;
#else /* __std_tm_defined */
	struct tm __ltm;
#endif /* !__std_tm_defined */
	return __localdep_asctime_r(__localdep_localtime_r(__timer, &__ltm), __buf);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_ctime_r_defined */
