/* HASH CRC-32:0xa083e520 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__wstrtime_s_defined
#define __local__wstrtime_s_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE__wstrtime) || defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE___time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__wstrtime_defined
#define __local___localdep__wstrtime_defined
#ifdef __CRT_HAVE__wstrtime
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(1),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep__wstrtime,(__WCHAR_TYPE__ __buf[9]),_wstrtime,(__buf))
#elif defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE___time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wtime/_wstrtime.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__wstrtime __LIBC_LOCAL_NAME(_wstrtime)
#else /* ... */
#undef __local___localdep__wstrtime_defined
#endif /* !... */
#endif /* !__local___localdep__wstrtime_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wstrtime_s) __ATTR_OUTS(1, 2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wstrtime_s))(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen) {
	if __unlikely(__buflen < 9)
		return __ERANGE;



	if (!(__NAMESPACE_LOCAL_SYM __localdep__wstrtime)(__buf))
		return __libc_geterrno_or(1);

	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wstrtime_s_defined
#define __local___localdep__wstrtime_s_defined
#define __localdep__wstrtime_s __LIBC_LOCAL_NAME(_wstrtime_s)
#endif /* !__local___localdep__wstrtime_s_defined */
#else /* __CRT_HAVE__wstrtime || __CRT_HAVE__strtime || __CRT_HAVE_time64 || __CRT_HAVE__time64 || __CRT_HAVE___time64 || __CRT_HAVE_time || __CRT_HAVE___time || __CRT_HAVE___libc_time || __CRT_HAVE__time32 */
#undef __local__wstrtime_s_defined
#endif /* !__CRT_HAVE__wstrtime && !__CRT_HAVE__strtime && !__CRT_HAVE_time64 && !__CRT_HAVE__time64 && !__CRT_HAVE___time64 && !__CRT_HAVE_time && !__CRT_HAVE___time && !__CRT_HAVE___libc_time && !__CRT_HAVE__time32 */
#endif /* !__local__wstrtime_s_defined */
