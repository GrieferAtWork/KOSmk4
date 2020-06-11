/* HASH CRC-32:0x8b86da65 */
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
#ifndef __local_strptime_defined
#define __local_strptime_defined 1
#include <__crt.h>
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
/* Dependency: crt_strptime_l from time */
#if !defined(__local___localdep_crt_strptime_l_defined) && defined(__CRT_HAVE_strptime_l)
#define __local___localdep_crt_strptime_l_defined 1
/* Similar to `strptime' but take the information from
 * the provided locale and not the global locale */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),char *,__NOTHROW_NCX,__localdep_crt_strptime_l,(char const *__restrict __s, char const *__restrict __format, __STRUCT_TM *__restrict __tp, __locale_t __locale),strptime_l,(__s,__format,__tp,__locale))
#endif /* !__local___localdep_crt_strptime_l_defined && __CRT_HAVE_strptime_l */
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
__LOCAL_LIBC(strptime) __ATTR_NONNULL((1, 2, 3)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strptime))(char const *__restrict __s, char const *__restrict __format, __STRUCT_TM *__restrict __tp) {
#ifdef __BUILDING_LIBC
	/* TODO */
	(void)__s;
	(void)__format;
	(void)__tp;
	__COMPILER_IMPURE();
	return __NULLPTR;
#elif defined(__CRT_HAVE_strptime_l)
	return __localdep_crt_strptime_l(__s, __format, __tp, __NULLPTR);
#else /* ... */
	/* TODO */
	(void)__s;
	(void)__format;
	(void)__tp;
	__COMPILER_IMPURE();
	return __NULLPTR;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strptime_defined
#define __local___localdep_strptime_defined 1
#define __localdep_strptime __LIBC_LOCAL_NAME(strptime)
#endif /* !__local___localdep_strptime_defined */
#endif /* !__local_strptime_defined */
