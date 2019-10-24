/* HASH CRC-32:0x74bd2a35 */
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
#ifndef __local_localtime64_r_defined
#define __local_localtime64_r_defined 1
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
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif /* !__STRUCT_TM */
/* Dependency: "dos_localtime64_s" from "time" */
#ifndef ____localdep_dos_localtime64_s_defined
#define ____localdep_dos_localtime64_s_defined 1
#if defined(__CRT_HAVE__localtime64_s)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_localtime64_s,(__STRUCT_TM *__restrict __tp, __time64_t const *__restrict __timer),_localtime64_s,(__tp,__timer))
#elif defined(__CRT_HAVE__gmtime32_s)
#include <local/time/dos_localtime64_s.h>
#define __localdep_dos_localtime64_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(dos_localtime64_s))
#else /* CUSTOM: dos_localtime64_s */
#undef ____localdep_dos_localtime64_s_defined
#endif /* dos_localtime64_s... */
#endif /* !____localdep_dos_localtime64_s_defined */

/* Dependency: "gmtime64_r" from "time" */
#ifndef ____localdep_gmtime64_r_defined
#define ____localdep_gmtime64_r_defined 1
#if defined(__CRT_HAVE_gmtime64_r)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_gmtime64_r,(__time64_t const *__restrict __timer, __STRUCT_TM *__restrict __tp),gmtime64_r,(__timer,__tp))
#elif defined(__CRT_HAVE_gmtime_r) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STRUCT_TM *,__NOTHROW_NCX,__localdep_gmtime64_r,(__time64_t const *__restrict __timer, __STRUCT_TM *__restrict __tp),gmtime_r,(__timer,__tp))
#else /* LIBC: gmtime64_r */
#include <local/time/gmtime64_r.h>
/* Return the `struct tm' representation of *TIMER in UTC, using *TP to store the result */
#define __localdep_gmtime64_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gmtime64_r))
#endif /* gmtime64_r... */
#endif /* !____localdep_gmtime64_r_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__LOCAL_LIBC(localtime64_r) __ATTR_NONNULL((1, 2)) __STRUCT_TM *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(localtime64_r))(__time64_t const *__restrict __timer,
                                                           __STRUCT_TM *__restrict __tp) {
#line 1566 "kos/src/libc/magic/time.c"
#if defined(__CRT_HAVE__localtime32_s) || defined(__CRT_HAVE__localtime64_s)
	return __localdep_dos_localtime64_s(__tp, __timer) ? __NULLPTR : __tp;
#else
	/* XXX: Timezone support? */
	return __localdep_gmtime64_r(__timer, __tp);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* !__local_localtime64_r_defined */
