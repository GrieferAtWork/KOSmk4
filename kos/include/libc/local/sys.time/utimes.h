/* HASH CRC-32:0x47dabe1d */
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
#ifndef __local_utimes_defined
#define __local_utimes_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_utimes64) || defined(__CRT_HAVE_utimes) || defined(__CRT_HAVE___utimes)
#include <bits/os/timeval.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_utimes32_defined
#define __local___localdep_utimes32_defined
#ifdef __CRT_HAVE_utimes
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_utimes32,(char const *__file, struct __timeval32 const __tvp[2]),utimes,(__file,__tvp))
#elif defined(__CRT_HAVE___utimes)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_utimes32,(char const *__file, struct __timeval32 const __tvp[2]),__utimes,(__file,__tvp))
#else /* ... */
#undef __local___localdep_utimes32_defined
#endif /* !... */
#endif /* !__local___localdep_utimes32_defined */
#ifndef __local___localdep_utimes64_defined
#define __local___localdep_utimes64_defined
#if defined(__CRT_HAVE_utimes) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_utimes64,(char const *__file, struct __timeval64 const __tvp[2]),utimes,(__file,__tvp))
#elif defined(__CRT_HAVE___utimes) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_utimes64,(char const *__file, struct __timeval64 const __tvp[2]),__utimes,(__file,__tvp))
#elif defined(__CRT_HAVE_utimes64)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_NCX,__localdep_utimes64,(char const *__file, struct __timeval64 const __tvp[2]),utimes64,(__file,__tvp))
#elif defined(__CRT_HAVE_utimes) || defined(__CRT_HAVE___utimes)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.time/utimes64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_utimes64 __LIBC_LOCAL_NAME(utimes64)
#else /* ... */
#undef __local___localdep_utimes64_defined
#endif /* !... */
#endif /* !__local___localdep_utimes64_defined */
__LOCAL_LIBC(utimes) __ATTR_IN(1) __ATTR_IN_OPT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(utimes))(char const *__file, struct timeval const __tvp[2]) {
#if defined(__CRT_HAVE_utimes) || defined(__CRT_HAVE___utimes)
	struct __timeval32 __tv32[2];
	if (!__tvp)
		return (__NAMESPACE_LOCAL_SYM __localdep_utimes32)(__file, __NULLPTR);
	__tv32[0].tv_sec  = (__time32_t)__tvp[0].tv_sec;
	__tv32[0].tv_usec = __tvp[0].tv_usec;
	__tv32[1].tv_sec  = (__time32_t)__tvp[1].tv_sec;
	__tv32[1].tv_usec = __tvp[1].tv_usec;
	return (__NAMESPACE_LOCAL_SYM __localdep_utimes32)(__file, __tv32);
#else /* __CRT_HAVE_utimes || __CRT_HAVE___utimes */
	struct __timeval64 __tv64[2];
	if (!__tvp)
		return (__NAMESPACE_LOCAL_SYM __localdep_utimes64)(__file, __NULLPTR);
	__tv64[0].tv_sec  = (__time64_t)__tvp[0].tv_sec;
	__tv64[0].tv_usec = __tvp[0].tv_usec;
	__tv64[1].tv_sec  = (__time64_t)__tvp[1].tv_sec;
	__tv64[1].tv_usec = __tvp[1].tv_usec;
	return (__NAMESPACE_LOCAL_SYM __localdep_utimes64)(__file, __tv64);
#endif /* !__CRT_HAVE_utimes && !__CRT_HAVE___utimes */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_utimes_defined
#define __local___localdep_utimes_defined
#define __localdep_utimes __LIBC_LOCAL_NAME(utimes)
#endif /* !__local___localdep_utimes_defined */
#else /* __CRT_HAVE_utimes64 || __CRT_HAVE_utimes || __CRT_HAVE___utimes */
#undef __local_utimes_defined
#endif /* !__CRT_HAVE_utimes64 && !__CRT_HAVE_utimes && !__CRT_HAVE___utimes */
#endif /* !__local_utimes_defined */
