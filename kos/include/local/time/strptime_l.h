/* HASH CRC-32:0x3648e927 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strptime_l_defined
#define __local_strptime_l_defined 1
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
/* Dependency: "strptime" from "time" */
#ifndef ____localdep_strptime_defined
#define ____localdep_strptime_defined 1
#ifdef __CRT_HAVE_strptime
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),char *,__NOTHROW_NCX,__localdep_strptime,(char const *__restrict __s, char const *__restrict __format, __STRUCT_TM *__restrict __tp),strptime,(__s,__format,__tp))
#else /* LIBC: strptime */
#include <local/time/strptime.h>
/* Parse S according to FORMAT and store binary time information in TP.
 * The return value is a pointer to the first unparsed character in S */
#define __localdep_strptime (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strptime))
#endif /* strptime... */
#endif /* !____localdep_strptime_defined */

__NAMESPACE_LOCAL_BEGIN
/* Similar to `strptime' but take the information from
 * the provided locale and not the global locale */
__LOCAL_LIBC(strptime_l) __ATTR_NONNULL((1, 2, 3)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strptime_l))(char const *__restrict __s,
                                                        char const *__restrict __format,
                                                        __STRUCT_TM *__restrict __tp,
                                                        __locale_t __locale) {
#line 1394 "kos/src/libc/magic/time.c"
	(void)__locale;
	return __localdep_strptime(__s, __format, __tp);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strptime_l_defined */
