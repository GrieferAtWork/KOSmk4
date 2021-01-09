/* HASH CRC-32:0x78e26594 */
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
#ifndef __local_ctime_r_defined
#define __local_ctime_r_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: asctime_r from time */
#ifndef __local___localdep_asctime_r_defined
#define __local___localdep_asctime_r_defined 1
#ifdef __CRT_HAVE_asctime_r
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
__CREDIRECT(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_asctime_r,(struct __NAMESPACE_STD_SYM tm const *__restrict __tp, char __buf[26]),asctime_r,(__tp,__buf))
#else /* __CRT_HAVE_asctime_r */
__NAMESPACE_LOCAL_END
#include <libc/local/time/asctime_r.h>
__NAMESPACE_LOCAL_BEGIN
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
#define __localdep_asctime_r __LIBC_LOCAL_NAME(asctime_r)
#endif /* !__CRT_HAVE_asctime_r */
#endif /* !__local___localdep_asctime_r_defined */
/* Dependency: dos_ctime_s from time */
#ifndef __local___localdep_dos_ctime_s_defined
#define __local___localdep_dos_ctime_s_defined 1
#if defined(__CRT_HAVE__ctime32_s) && defined(__USE_TIME_BITS64)
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__CREDIRECT(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,__localdep_dos_ctime_s,(char __buf[26], __SIZE_TYPE__ __bufsize, __TM_TYPE(time) const *__restrict __timer),_ctime32_s,(__buf,__bufsize,__timer))
#elif defined(__CRT_HAVE__ctime64_s) && !defined(__USE_TIME_BITS64)
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__CREDIRECT(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,__localdep_dos_ctime_s,(char __buf[26], __SIZE_TYPE__ __bufsize, __TM_TYPE(time) const *__restrict __timer),_ctime64_s,(__buf,__bufsize,__timer))
#elif defined(__CRT_HAVE__ctime64_s) || defined(__CRT_HAVE__ctime32_s)
__NAMESPACE_LOCAL_END
#include <libc/local/time/dos_ctime_s.h>
__NAMESPACE_LOCAL_BEGIN
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
#define __localdep_dos_ctime_s __LIBC_LOCAL_NAME(dos_ctime_s)
#else /* ... */
#undef __local___localdep_dos_ctime_s_defined
#endif /* !... */
#endif /* !__local___localdep_dos_ctime_s_defined */
/* Dependency: localtime_r from time */
#ifndef __local___localdep_localtime_r_defined
#define __local___localdep_localtime_r_defined 1
#ifdef __CRT_HAVE_localtime_r
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime_r,(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime_r,(__timer,__tp))
#else /* __CRT_HAVE_localtime_r */
__NAMESPACE_LOCAL_END
#include <libc/local/time/localtime_r.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
#define __localdep_localtime_r __LIBC_LOCAL_NAME(localtime_r)
#endif /* !__CRT_HAVE_localtime_r */
#endif /* !__local___localdep_localtime_r_defined */
/* Equivalent to `asctime_r(localtime_r(timer, *TMP*), buf)' */
__LOCAL_LIBC(ctime_r) __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ctime_r))(__TM_TYPE(time) const *__restrict __timer, char __buf[26]) {



#if defined(__CRT_HAVE__ctime64_s) || defined(__CRT_HAVE__ctime32_s)
	return __localdep_dos_ctime_s(__buf, 26, __timer) ? __NULLPTR : __buf;
#else /* __CRT_HAVE__ctime64_s || __CRT_HAVE__ctime32_s */
	struct __NAMESPACE_STD_SYM tm __ltm;
	return __localdep_asctime_r(__localdep_localtime_r(__timer, &__ltm), __buf);
#endif /* !__CRT_HAVE__ctime64_s && !__CRT_HAVE__ctime32_s */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ctime_r_defined
#define __local___localdep_ctime_r_defined 1
#define __localdep_ctime_r __LIBC_LOCAL_NAME(ctime_r)
#endif /* !__local___localdep_ctime_r_defined */
#endif /* !__local_ctime_r_defined */
