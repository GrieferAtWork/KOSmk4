/* HASH CRC-32:0xa28c58b0 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_asctime_r_defined
#define __local_asctime_r_defined
#include <__crt.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_crt_asctime_s_defined) && defined(__CRT_HAVE_asctime_s)
#define __local___localdep_crt_asctime_s_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,__localdep_crt_asctime_s,(char *__restrict __buf, __SIZE_TYPE__ __buflen, struct __NAMESPACE_STD_SYM tm const *__restrict __tp),asctime_s,(__buf,__buflen,__tp))
#endif /* !__local___localdep_crt_asctime_s_defined && __CRT_HAVE_asctime_s */
#ifndef __local___localdep_sprintf_defined
#define __local___localdep_sprintf_defined
#if __has_builtin(__builtin_sprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_sprintf,(char *__restrict __buf, char const *__restrict __format, ...),sprintf,{ return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("sprintf");
#elif defined(__CRT_HAVE__IO_sprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("_IO_sprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/sprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sprintf __LIBC_LOCAL_NAME(sprintf)
#endif /* !... */
#endif /* !__local___localdep_sprintf_defined */
__NAMESPACE_LOCAL_END
#if defined(__BUILDING_LIBC) || !defined(__CRT_HAVE_asctime_s)
#ifndef __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED
#define __LIBC_TIME_ABBR_WDAY_NAMES_DEFINED
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA(__abbr_wday_names) char const __abbr_wday_names[7][4] =
	{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_TIME_ABBR_WDAY_NAMES_DEFINED */

#ifndef __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED
#define __LIBC_TIME_ABBR_MONTH_NAMES_DEFINED
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_CONST_DATA(__abbr_month_names) char const __abbr_month_names[12][4] =
	{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_TIME_ABBR_MONTH_NAMES_DEFINED */

#endif /* __BUILDING_LIBC || !__CRT_HAVE_asctime_s */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(asctime_r) __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(asctime_r))(struct __NAMESPACE_STD_SYM tm const *__restrict __tp, char __buf[26]) {
#ifdef __CRT_HAVE_asctime_s
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_asctime_s)(__buf, 26, __tp) ? __NULLPTR : __buf;
#else /* __CRT_HAVE_asctime_s */
	(__NAMESPACE_LOCAL_SYM __localdep_sprintf)(__buf, "%.3s %.3s%3u %.2u:%.2u:%.2u %u\n",
	        (unsigned int)__tp->tm_wday >= 7 ? "??" "?" :
	        __NAMESPACE_LOCAL_SYM __abbr_wday_names[__tp->tm_wday],
	        (unsigned int)__tp->tm_mon >= 12 ? "??" "?" :
	        __NAMESPACE_LOCAL_SYM __abbr_month_names[__tp->tm_mon],
	        (unsigned int)__tp->tm_mday,
	        (unsigned int)__tp->tm_hour,
	        (unsigned int)__tp->tm_min,
	        (unsigned int)__tp->tm_sec,
	        (unsigned int)__tp->tm_year + 1900);
	return __buf;
#endif /* !__CRT_HAVE_asctime_s */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_asctime_r_defined
#define __local___localdep_asctime_r_defined
#define __localdep_asctime_r __LIBC_LOCAL_NAME(asctime_r)
#endif /* !__local___localdep_asctime_r_defined */
#endif /* !__local_asctime_r_defined */
