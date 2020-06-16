/* HASH CRC-32:0x5400a5fd */
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
#ifndef __local_dos_localtime_s_defined
#define __local_dos_localtime_s_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE__localtime64_s) || defined(__CRT_HAVE__localtime32_s)
#include <bits/types.h>
#ifndef __STRUCT_TM
#ifdef __tm_defined
#define __STRUCT_TM struct tm
#else /* __tm_defined */
#define __STRUCT_TM struct __NAMESPACE_STD_SYM tm
#ifndef __std_tm_defined
#define __std_tm_defined 1
__NAMESPACE_STD_BEGIN
struct tm {
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
	__LONGPTR_TYPE__ tm_gmtoff;   /* Seconds east of UTC. */
	char const      *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	__LONGPTR_TYPE__ __tm_gmtoff; /* Seconds east of UTC. */
	char const      *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* __CRT_GLC */
};
__NAMESPACE_STD_END
#endif /* !__std_tm_defined */
#endif /* !__tm_defined */
#endif
__NAMESPACE_LOCAL_BEGIN
/* Dependency: dos_localtime32_s from time */
#if !defined(__local___localdep_dos_localtime32_s_defined) && defined(__CRT_HAVE__localtime32_s)
#define __local___localdep_dos_localtime32_s_defined 1
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_localtime32_s,(__STRUCT_TM *__restrict __tp, __time32_t const *__restrict __timer),_localtime32_s,(__tp,__timer))
#endif /* !__local___localdep_dos_localtime32_s_defined && __CRT_HAVE__localtime32_s */
/* Dependency: dos_localtime64_s from time */
#ifndef __local___localdep_dos_localtime64_s_defined
#define __local___localdep_dos_localtime64_s_defined 1
#ifdef __CRT_HAVE__localtime64_s
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_localtime64_s,(__STRUCT_TM *__restrict __tp, __time64_t const *__restrict __timer),_localtime64_s,(__tp,__timer))
#elif defined(__CRT_HAVE__localtime32_s)
__NAMESPACE_LOCAL_END
#include <local/time/dos_localtime64_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_dos_localtime64_s __LIBC_LOCAL_NAME(dos_localtime64_s)
#else /* ... */
#undef __local___localdep_dos_localtime64_s_defined
#endif /* !... */
#endif /* !__local___localdep_dos_localtime64_s_defined */
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__LOCAL_LIBC(dos_localtime_s) __ATTR_NONNULL((1, 2)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dos_localtime_s))(__STRUCT_TM *__restrict __tp, __TM_TYPE(time) const *__restrict __timer) {
#if defined(__CRT_HAVE__localtime64_s) || defined(__CRT_HAVE__localtime32_s)
	__time64_t __tm64 = *__timer;
	return __localdep_dos_localtime64_s(__tp, &__tm64);
#else /* __CRT_HAVE__localtime64_s || __CRT_HAVE__localtime32_s */
	__time32_t __tm32 = *__timer;
	return __localdep_dos_localtime32_s(__tp, &__tm32);
#endif /* !__CRT_HAVE__localtime64_s && !__CRT_HAVE__localtime32_s */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dos_localtime_s_defined
#define __local___localdep_dos_localtime_s_defined 1
#define __localdep_dos_localtime_s __LIBC_LOCAL_NAME(dos_localtime_s)
#endif /* !__local___localdep_dos_localtime_s_defined */
#else /* __CRT_HAVE__localtime64_s || __CRT_HAVE__localtime32_s */
#undef __local_dos_localtime_s_defined
#endif /* !__CRT_HAVE__localtime64_s && !__CRT_HAVE__localtime32_s */
#endif /* !__local_dos_localtime_s_defined */
