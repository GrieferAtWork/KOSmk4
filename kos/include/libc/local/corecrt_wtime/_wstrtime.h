/* HASH CRC-32:0x782ccdf2 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__wstrtime_defined
#define __local__wstrtime_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__strtime_defined
#define __local___localdep__strtime_defined
#ifdef __CRT_HAVE__strtime
__CREDIRECT(__ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep__strtime,(char __buf[9]),_strtime,(__buf))
#elif defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_LOCAL_END
#include <libc/local/time/_strtime.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__strtime __LIBC_LOCAL_NAME(_strtime)
#else /* ... */
#undef __local___localdep__strtime_defined
#endif /* !... */
#endif /* !__local___localdep__strtime_defined */
__LOCAL_LIBC(_wstrtime) __ATTR_OUT(1) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wstrtime))(__WCHAR_TYPE__ __buf[9]) {
	unsigned int __i;
	char __abuf[9], *__ptr;
	__ptr = (__NAMESPACE_LOCAL_SYM __localdep__strtime)(__abuf);

	if __unlikely(!__ptr)
		return __NULLPTR;

	for (__i = 0; __i < 9; ++__i)
		__buf[__i] = (__WCHAR_TYPE__)__ptr[__i]; /* Guarantied no unicode in here! */
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wstrtime_defined
#define __local___localdep__wstrtime_defined
#define __localdep__wstrtime __LIBC_LOCAL_NAME(_wstrtime)
#endif /* !__local___localdep__wstrtime_defined */
#else /* __CRT_HAVE__strtime || __CRT_HAVE_time64 || __CRT_HAVE__time64 || __CRT_HAVE_time || __CRT_HAVE___time || __CRT_HAVE___libc_time || __CRT_HAVE__time32 */
#undef __local__wstrtime_defined
#endif /* !__CRT_HAVE__strtime && !__CRT_HAVE_time64 && !__CRT_HAVE__time64 && !__CRT_HAVE_time && !__CRT_HAVE___time && !__CRT_HAVE___libc_time && !__CRT_HAVE__time32 */
#endif /* !__local__wstrtime_defined */
