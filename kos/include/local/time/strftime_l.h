/* HASH CRC-32:0x2458f550 */
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
#ifndef __local_strftime_l_defined
#define __local_strftime_l_defined 1
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
/* Dependency: "strftime" from "time" */
#ifndef ____localdep_strftime_defined
#define ____localdep_strftime_defined 1
#if __has_builtin(__builtin_strftime) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strftime)
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__FORCELOCAL __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL __localdep_strftime)(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __STRUCT_TM const *__restrict __tp) { return __builtin_strftime(__buf, __bufsize, __format, __tp); }
#elif defined(__CRT_HAVE_strftime)
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strftime,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __STRUCT_TM const *__restrict __tp),strftime,(__buf,__bufsize,__format,__tp))
#elif defined(__CRT_HAVE__Strftime)
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strftime,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, __STRUCT_TM const *__restrict __tp),_Strftime,(__buf,__bufsize,__format,__tp))
#else /* LIBC: strftime */
#include <local/time/strftime.h>
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
#define __localdep_strftime (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strftime))
#endif /* strftime... */
#endif /* !____localdep_strftime_defined */

__NAMESPACE_LOCAL_BEGIN
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
__LOCAL_LIBC(strftime_l) __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strftime_l))(char *__restrict __buf,
                                                        __SIZE_TYPE__ __bufsize,
                                                        char const *__restrict __format,
                                                        __STRUCT_TM const *__restrict __tp,
                                                        __locale_t __locale) {
#line 1373 "kos/src/libc/magic/time.c"
	(void)__locale;
	return __localdep_strftime(__buf, __bufsize, __format, __tp);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strftime_l_defined */
