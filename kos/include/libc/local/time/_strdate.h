/* HASH CRC-32:0x7dca56d2 */
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
#ifndef __local__strdate_defined
#define __local__strdate_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_localtime64_r_defined
#define __local___localdep_localtime64_r_defined
#if defined(__CRT_HAVE_localtime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__NAMESPACE_LOCAL_END
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE_localtime64_r)
__NAMESPACE_LOCAL_END
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime64_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/localtime64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_localtime64_r __LIBC_LOCAL_NAME(localtime64_r)
#endif /* !... */
#endif /* !__local___localdep_localtime64_r_defined */
#ifndef __local___localdep_time64_defined
#define __local___localdep_time64_defined
#if defined(__CRT_HAVE_time) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(,__time64_t,__NOTHROW_NCX,__localdep_time64,(__time64_t *__timer),time,(__timer))
#elif defined(__CRT_HAVE___time) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(,__time64_t,__NOTHROW_NCX,__localdep_time64,(__time64_t *__timer),__time,(__timer))
#elif defined(__CRT_HAVE___libc_time) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(,__time64_t,__NOTHROW_NCX,__localdep_time64,(__time64_t *__timer),__libc_time,(__timer))
#elif defined(__CRT_HAVE_time64)
__CREDIRECT(,__time64_t,__NOTHROW_NCX,__localdep_time64,(__time64_t *__timer),time64,(__timer))
#elif defined(__CRT_HAVE__time64)
__CREDIRECT(,__time64_t,__NOTHROW_NCX,__localdep_time64,(__time64_t *__timer),_time64,(__timer))
#elif defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_LOCAL_END
#include <libc/local/time/time64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_time64 __LIBC_LOCAL_NAME(time64)
#else /* ... */
#undef __local___localdep_time64_defined
#endif /* !... */
#endif /* !__local___localdep_time64_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/tm.h>
#include <libc/template/itoa_digits.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_strdate) __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_strdate))(char __buf[9]) {
	__time64_t __now = (__NAMESPACE_LOCAL_SYM __localdep_time64)(__NULLPTR);
	struct __NAMESPACE_STD_SYM tm __now_tms, *__pn;
	__pn = (__NAMESPACE_LOCAL_SYM __localdep_localtime64_r)(&__now, &__now_tms);
	__buf[0] = __LOCAL_itoa_decimal(__pn->tm_mon / 10);
	__buf[1] = __LOCAL_itoa_decimal(__pn->tm_mon % 10);
	__buf[2] = '/';
	__buf[3] = __LOCAL_itoa_decimal(__pn->tm_mday / 10);
	__buf[4] = __LOCAL_itoa_decimal(__pn->tm_mday % 10);
	__buf[5] = '/';
	__buf[6] = __LOCAL_itoa_decimal((__pn->tm_year / 10) % 10);
	__buf[7] = __LOCAL_itoa_decimal(__pn->tm_year % 10);
	__buf[8] = '\0';
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__strdate_defined
#define __local___localdep__strdate_defined
#define __localdep__strdate __LIBC_LOCAL_NAME(_strdate)
#endif /* !__local___localdep__strdate_defined */
#else /* __CRT_HAVE_time64 || __CRT_HAVE__time64 || __CRT_HAVE_time || __CRT_HAVE___time || __CRT_HAVE___libc_time || __CRT_HAVE__time32 */
#undef __local__strdate_defined
#endif /* !__CRT_HAVE_time64 && !__CRT_HAVE__time64 && !__CRT_HAVE_time && !__CRT_HAVE___time && !__CRT_HAVE___libc_time && !__CRT_HAVE__time32 */
#endif /* !__local__strdate_defined */
