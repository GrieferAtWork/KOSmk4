/* HASH CRC-32:0x2906f2c8 */
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
#ifndef __local__localtime32_defined
#define __local__localtime32_defined
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_localtime_defined
#define __local___localdep_localtime_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_localtime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime,(__time_t const *__timer),localtime,(__timer))
#elif defined(__CRT_HAVE__localtime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime,(__time_t const *__timer),_localtime32,(__timer))
#elif defined(__CRT_HAVE_localtime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime,(__time_t const *__timer),localtime64,(__timer))
#elif defined(__CRT_HAVE__localtime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime,(__time_t const *__timer),_localtime64,(__timer))
#elif defined(__CRT_HAVE___localtime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime,(__time_t const *__timer),__localtime64,(__timer))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/localtime.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_localtime __LIBC_LOCAL_NAME(localtime)
#endif /* !... */
#endif /* !__local___localdep_localtime_defined */
__LOCAL_LIBC(_localtime32) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct __NAMESPACE_STD_SYM tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_localtime32))(__time32_t const *__timer) {
	__time_t __timer2 = (__time_t)*__timer;
	return (__NAMESPACE_LOCAL_SYM __localdep_localtime)(&__timer2);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__localtime32_defined
#define __local___localdep__localtime32_defined
#define __localdep__localtime32 __LIBC_LOCAL_NAME(_localtime32)
#endif /* !__local___localdep__localtime32_defined */
#endif /* !__local__localtime32_defined */
