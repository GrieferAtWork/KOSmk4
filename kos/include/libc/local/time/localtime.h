/* HASH CRC-32:0x88da2d52 */
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
#ifndef __local_localtime_defined
#define __local_localtime_defined
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_localtime32_defined
#define __local___localdep_crt_localtime32_defined
#ifdef __CRT_HAVE_localtime
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_crt_localtime32,(__time32_t const *__timer),localtime,(__timer))
#elif defined(__CRT_HAVE__localtime32)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_crt_localtime32,(__time32_t const *__timer),_localtime32,(__timer))
#else /* ... */
#undef __local___localdep_crt_localtime32_defined
#endif /* !... */
#endif /* !__local___localdep_crt_localtime32_defined */
#ifndef __local___localdep_localtime64_defined
#define __local___localdep_localtime64_defined
#if defined(__CRT_HAVE_localtime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64,(__time64_t const *__timer),localtime,(__timer))
#elif defined(__CRT_HAVE_localtime64)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64,(__time64_t const *__timer),localtime64,(__timer))
#elif defined(__CRT_HAVE__localtime64)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime64,(__time64_t const *__timer),_localtime64,(__timer))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/localtime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_localtime64 __LIBC_LOCAL_NAME(localtime64)
#endif /* !... */
#endif /* !__local___localdep_localtime64_defined */
#ifndef __local___localdep_localtime_r_defined
#define __local___localdep_localtime_r_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_localtime_r) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime_r,(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime_r,(__timer,__tp))
#elif defined(__CRT_HAVE_localtime64_r) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),struct __NAMESPACE_STD_SYM tm *,__NOTHROW_NCX,__localdep_localtime_r,(__TM_TYPE(time) const *__restrict __timer, struct __NAMESPACE_STD_SYM tm *__restrict __tp),localtime64_r,(__timer,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/time/localtime_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_localtime_r __LIBC_LOCAL_NAME(localtime_r)
#endif /* !... */
#endif /* !__local___localdep_localtime_r_defined */
__NAMESPACE_LOCAL_END
#ifdef __BUILDING_LIBC
#ifndef __LIBC_GMTIME_BUFFER_DEFINED
#define __LIBC_GMTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(__gmtime_buf) struct __NAMESPACE_STD_SYM tm __gmtime_buf = { 0 };
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_GMTIME_BUFFER_DEFINED */
#endif /* __BUILDING_LIBC */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(localtime) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct __NAMESPACE_STD_SYM tm *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(localtime))(__TM_TYPE(time) const *__timer) {

	__time64_t __tm64 = (__time64_t)*__timer;
	return (__NAMESPACE_LOCAL_SYM __localdep_localtime64)(&__tm64);






}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_localtime_defined
#define __local___localdep_localtime_defined
#define __localdep_localtime __LIBC_LOCAL_NAME(localtime)
#endif /* !__local___localdep_localtime_defined */
#endif /* !__local_localtime_defined */
