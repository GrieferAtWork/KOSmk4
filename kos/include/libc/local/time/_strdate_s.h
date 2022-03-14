/* HASH CRC-32:0xc04154b7 */
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
#ifndef __local__strdate_s_defined
#define __local__strdate_s_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE__strdate) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__strdate_defined
#define __local___localdep__strdate_defined
#ifdef __CRT_HAVE__strdate
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep__strdate,(char __buf[9]),_strdate,(__buf))
#elif defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
__NAMESPACE_LOCAL_END
#include <libc/local/time/_strdate.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__strdate __LIBC_LOCAL_NAME(_strdate)
#else /* ... */
#undef __local___localdep__strdate_defined
#endif /* !... */
#endif /* !__local___localdep__strdate_defined */
__LOCAL_LIBC(_strdate_s) __ATTR_NONNULL((1)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_strdate_s))(char *__buf, __SIZE_TYPE__ __bufsize) {
	if __unlikely(__bufsize < 9)
		return 34;
	(__NAMESPACE_LOCAL_SYM __localdep__strdate)(__buf);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__strdate_s_defined
#define __local___localdep__strdate_s_defined
#define __localdep__strdate_s __LIBC_LOCAL_NAME(_strdate_s)
#endif /* !__local___localdep__strdate_s_defined */
#else /* __CRT_HAVE__strdate || __CRT_HAVE_time64 || __CRT_HAVE__time64 || __CRT_HAVE_time || __CRT_HAVE___time || __CRT_HAVE___libc_time || __CRT_HAVE__time32 */
#undef __local__strdate_s_defined
#endif /* !__CRT_HAVE__strdate && !__CRT_HAVE_time64 && !__CRT_HAVE__time64 && !__CRT_HAVE_time && !__CRT_HAVE___time && !__CRT_HAVE___libc_time && !__CRT_HAVE__time32 */
#endif /* !__local__strdate_s_defined */
