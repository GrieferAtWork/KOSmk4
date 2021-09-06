/* HASH CRC-32:0xe17ce103 */
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
#ifndef __local_ftime_defined
#define __local_ftime_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime64) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE_ftime64)
#include <bits/os/timeb.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_crt_dos_ftime32_defined) && defined(__CRT_HAVE__ftime32)
#define __local___localdep_crt_dos_ftime32_defined 1
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_crt_dos_ftime32,(struct __timeb32 *__timebuf),_ftime32,(__timebuf))
#endif /* !__local___localdep_crt_dos_ftime32_defined && __CRT_HAVE__ftime32 */
#if !defined(__local___localdep_crt_dos_ftime64_defined) && defined(__CRT_HAVE__ftime64)
#define __local___localdep_crt_dos_ftime64_defined 1
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_crt_dos_ftime64,(struct __timeb64 *__timebuf),_ftime64,(__timebuf))
#endif /* !__local___localdep_crt_dos_ftime64_defined && __CRT_HAVE__ftime64 */
#if !defined(__local___localdep_crt_ftime32_defined) && defined(__CRT_HAVE_ftime)
#define __local___localdep_crt_ftime32_defined 1
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_crt_ftime32,(struct __timeb32 *__timebuf),ftime,(__timebuf))
#endif /* !__local___localdep_crt_ftime32_defined && __CRT_HAVE_ftime */
#if !defined(__local___localdep_crt_ftime32_s_defined) && defined(__CRT_HAVE__ftime32_s)
#define __local___localdep_crt_ftime32_s_defined 1
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,__localdep_crt_ftime32_s,(struct __timeb32 *__timebuf),_ftime32_s,(__timebuf))
#endif /* !__local___localdep_crt_ftime32_s_defined && __CRT_HAVE__ftime32_s */
#if !defined(__local___localdep_crt_ftime64_defined) && defined(__CRT_HAVE_ftime64)
#define __local___localdep_crt_ftime64_defined 1
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_crt_ftime64,(struct __timeb64 *__timebuf),ftime64,(__timebuf))
#endif /* !__local___localdep_crt_ftime64_defined && __CRT_HAVE_ftime64 */
#if !defined(__local___localdep_crt_ftime64_s_defined) && defined(__CRT_HAVE__ftime64_s)
#define __local___localdep_crt_ftime64_s_defined 1
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,__localdep_crt_ftime64_s,(struct __timeb64 *__timebuf),_ftime64_s,(__timebuf))
#endif /* !__local___localdep_crt_ftime64_s_defined && __CRT_HAVE__ftime64_s */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ftime) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ftime))(struct timeb *__timebuf) {
#if defined(__CRT_HAVE__ftime32_s) && !defined(__USE_TIME_BITS64)
	__errno_t __error = __localdep_crt_ftime32_s(__timebuf);
	if __unlikely(__error)
		__error = __libc_seterrno(__error);
	return (int)__error;
#elif defined(__CRT_HAVE__ftime64_s) && defined(__USE_TIME_BITS64)
	__errno_t __error = __localdep_crt_ftime64_s(__timebuf);
	if __unlikely(__error)
		__error = __libc_seterrno(__error);
	return (int)__error;
#elif defined(__CRT_HAVE__ftime32) && !defined(__USE_TIME_BITS64)
	__localdep_crt_dos_ftime32(&__temp);
	return 0;
#elif defined(__CRT_HAVE__ftime64) && defined(__USE_TIME_BITS64)
	__localdep_crt_dos_ftime64(&__temp);
	return 0;
#elif defined(__CRT_HAVE_ftime)
	struct __timeb32 __temp;
	int __error = __localdep_crt_ftime32(&__temp);
	if __likely(!__error) {
		__timebuf->time     = (__time64_t)__temp.time;
		__timebuf->millitm  = __temp.millitm;
		__timebuf->timezone = __temp.timezone;
		__timebuf->dstflag  = __temp.dstflag;
	}
	return __error;
#elif defined(__CRT_HAVE_ftime64)
	struct __timeb64 __temp;
	int __error = __localdep_crt_ftime64(&__temp);
	if __likely(!__error) {
		__timebuf->time     = (__time32_t)__temp.time;
		__timebuf->millitm  = __temp.millitm;
		__timebuf->timezone = __temp.timezone;
		__timebuf->dstflag  = __temp.dstflag;
	}
	return __error;
#elif defined(__CRT_HAVE__ftime32_s)
	struct __timeb32 __temp;
	__errno_t __error = __localdep_crt_ftime32_s(&__temp);
	if __unlikely(__error) {
		__error = __libc_seterrno(__error);
	} else {
		__timebuf->time     = (__time64_t)__temp.time;
		__timebuf->millitm  = __temp.millitm;
		__timebuf->timezone = __temp.timezone;
		__timebuf->dstflag  = __temp.dstflag;
	}
	return (int)__error;
#elif defined(__CRT_HAVE__ftime64_s)
	struct __timeb64 __temp;
	__errno_t __error = __localdep_crt_ftime64_s(&__temp);
	if __unlikely(__error) {
		__error = __libc_seterrno(__error);
	} else {
		__timebuf->time     = (__time32_t)__temp.time;
		__timebuf->millitm  = __temp.millitm;
		__timebuf->timezone = __temp.timezone;
		__timebuf->dstflag  = __temp.dstflag;
	}
	return (int)__error;
#elif defined(__CRT_HAVE__ftime32)
	struct __timeb32 __temp;
	__localdep_crt_dos_ftime32(&__temp);
	__timebuf->time     = (__time64_t)__temp.time;
	__timebuf->millitm  = __temp.millitm;
	__timebuf->timezone = __temp.timezone;
	__timebuf->dstflag  = __temp.dstflag;
	return 0;
#else /* ... */
	struct __timeb64 __temp;
	__localdep_crt_dos_ftime64(&__temp);
	__timebuf->time     = (__time32_t)__temp.time;
	__timebuf->millitm  = __temp.millitm;
	__timebuf->timezone = __temp.timezone;
	__timebuf->dstflag  = __temp.dstflag;
	return 0;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ftime_defined
#define __local___localdep_ftime_defined 1
#define __localdep_ftime __LIBC_LOCAL_NAME(ftime)
#endif /* !__local___localdep_ftime_defined */
#else /* __CRT_HAVE__ftime32_s || __CRT_HAVE__ftime64_s || __CRT_HAVE__ftime32 || __CRT_HAVE__ftime64 || __CRT_HAVE_ftime || __CRT_HAVE_ftime64 */
#undef __local_ftime_defined
#endif /* !__CRT_HAVE__ftime32_s && !__CRT_HAVE__ftime64_s && !__CRT_HAVE__ftime32 && !__CRT_HAVE__ftime64 && !__CRT_HAVE_ftime && !__CRT_HAVE_ftime64 */
#endif /* !__local_ftime_defined */
