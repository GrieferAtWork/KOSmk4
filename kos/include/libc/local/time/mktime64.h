/* HASH CRC-32:0xc5397458 */
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
#ifndef __local_mktime64_defined
#define __local_mktime64_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <features.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mktime32 from time */
#ifndef __local___localdep_mktime32_defined
#define __local___localdep_mktime32_defined 1
#ifdef __CRT_HAVE_mktime
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time32_t,__NOTHROW_NCX,__localdep_mktime32,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),mktime,(__tp))
#elif defined(__CRT_HAVE__mktime32)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time32_t,__NOTHROW_NCX,__localdep_mktime32,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),_mktime32,(__tp))
#elif defined(__CRT_HAVE_timelocal)
/* Return the `time_t' representation of TP and normalize TP */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__time32_t,__NOTHROW_NCX,__localdep_mktime32,(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp),timelocal,(__tp))
#else /* ... */
#undef __local___localdep_mktime32_defined
#endif /* !... */
#endif /* !__local___localdep_mktime32_defined */
__NAMESPACE_LOCAL_END
#ifndef __yearstodays
#define __yearstodays(__n_years) (((146097*(__n_years))/400)/*-1*/) /* rounding error? */
#endif /* !__yearstodays */
__NAMESPACE_LOCAL_BEGIN
/* Return the `time_t' representation of TP and normalize TP */
__LOCAL_LIBC(mktime64) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __time64_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mktime64))(struct __NAMESPACE_STD_SYM tm __KOS_FIXED_CONST *__tp) {









#if defined(__CRT_HAVE_mktime) || defined(__CRT_HAVE__mktime32) || defined(__CRT_HAVE_timelocal)
	return (__time64_t)__localdep_mktime32(__tp);
#else /* __CRT_HAVE_mktime || __CRT_HAVE__mktime32 || __CRT_HAVE_timelocal */
	__time64_t __result;
	__result = __yearstodays(__tp->tm_year) - __yearstodays(1970); /* UNIX_TIME_START_YEAR */
	__result += __tp->tm_yday;
	__result *= 86400; /* SECONDS_PER_DAY */
	__result += __tp->tm_hour*60*60;
	__result += __tp->tm_min*60;
	__result += __tp->tm_sec;
	return __result;
#endif /* !__CRT_HAVE_mktime && !__CRT_HAVE__mktime32 && !__CRT_HAVE_timelocal */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mktime64_defined
#define __local___localdep_mktime64_defined 1
#define __localdep_mktime64 __LIBC_LOCAL_NAME(mktime64)
#endif /* !__local___localdep_mktime64_defined */
#endif /* !__local_mktime64_defined */
