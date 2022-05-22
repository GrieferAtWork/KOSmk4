/* HASH CRC-32:0x93db7c79 */
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
#ifndef __local_ctime64_r_defined
#define __local_ctime64_r_defined
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_asctime_r_defined
#define __local___localdep_asctime_r_defined
#ifdef __CRT_HAVE_asctime_r
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,__localdep_asctime_r,(struct __NAMESPACE_STD_SYM tm const *__restrict __tp, char __buf[26]),asctime_r,(__tp,__buf))
#else /* __CRT_HAVE_asctime_r */
__NAMESPACE_LOCAL_END
#include <libc/local/time/asctime_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_asctime_r __LIBC_LOCAL_NAME(asctime_r)
#endif /* !__CRT_HAVE_asctime_r */
#endif /* !__local___localdep_asctime_r_defined */
#if !defined(__local___localdep_crt_ctime64_s_defined) && defined(__CRT_HAVE__ctime64_s)
#define __local___localdep_crt_ctime64_s_defined
__CREDIRECT(__ATTR_IN(3) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,__localdep_crt_ctime64_s,(char __buf[26], __SIZE_TYPE__ __bufsize, __time64_t const *__restrict __timer),_ctime64_s,(__buf,__bufsize,__timer))
#endif /* !__local___localdep_crt_ctime64_s_defined && __CRT_HAVE__ctime64_s */
#ifndef __local___localdep_localtime64_r_defined
#define __local___localdep_localtime64_r_defined
#if defined(__CRT_HAVE_localtime_r) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE_localtime64_r)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64_r,(__time64_t const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime64_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/localtime64_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_localtime64_r __LIBC_LOCAL_NAME(localtime64_r)
#endif /* !... */
#endif /* !__local___localdep_localtime64_r_defined */
__LOCAL_LIBC(ctime64_r) __ATTR_IN(1) __ATTR_OUT(2) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ctime64_r))(__time64_t const *__restrict __timer, char __buf[26]) {
#ifdef __CRT_HAVE__ctime64_s
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_ctime64_s)(__buf, 26, __timer) ? __NULLPTR : __buf;
#else /* __CRT_HAVE__ctime64_s */
	struct __NAMESPACE_STD_SYM tm __ltm;
	return (__NAMESPACE_LOCAL_SYM __localdep_asctime_r)((__NAMESPACE_LOCAL_SYM __localdep_localtime64_r)(__timer, &__ltm), __buf);
#endif /* !__CRT_HAVE__ctime64_s */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ctime64_r_defined
#define __local___localdep_ctime64_r_defined
#define __localdep_ctime64_r __LIBC_LOCAL_NAME(ctime64_r)
#endif /* !__local___localdep_ctime64_r_defined */
#endif /* !__local_ctime64_r_defined */
