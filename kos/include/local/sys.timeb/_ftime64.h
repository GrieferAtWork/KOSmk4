/* HASH CRC-32:0xbef12678 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__ftime64_defined
#if defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE_ftime)
#define __local__ftime64_defined 1
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "crt_ftime64_s" from "sys.timeb" */
#ifndef ____localdep_crt_ftime64_s_defined
#define ____localdep_crt_ftime64_s_defined 1
#ifdef __CRT_HAVE__ftime64_s
/* Fill in TIMEBUF with information about the current time */
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,__localdep_crt_ftime64_s,(struct __timeb64 *__timebuf),_ftime64_s,(__timebuf))
#else /* LIBC: _ftime64_s */
#undef ____localdep_crt_ftime64_s_defined
#endif /* crt_ftime64_s... */
#endif /* !____localdep_crt_ftime64_s_defined */

/* Dependency: "memset" from "string" */
#ifndef ____localdep_memset_defined
#define ____localdep_memset_defined 1
#ifdef __fast_memset_defined
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memset))
#elif defined(__CRT_HAVE_memset)
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* LIBC: memset */
#include <local/string/memset.h>
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset))
#endif /* memset... */
#endif /* !____localdep_memset_defined */

/* Dependency: "crt_ftime64" from "sys.timeb" */
#ifndef ____localdep_crt_ftime64_defined
#define ____localdep_crt_ftime64_defined 1
#ifdef __CRT_HAVE_ftime64
/* Fill in TIMEBUF with information about the current time */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_crt_ftime64,(struct __timeb64 *__timebuf),ftime64,(__timebuf))
#else /* LIBC: ftime64 */
#undef ____localdep_crt_ftime64_defined
#endif /* crt_ftime64... */
#endif /* !____localdep_crt_ftime64_defined */

/* Dependency: "crt_dos_ftime32" from "sys.timeb" */
#ifndef ____localdep_crt_dos_ftime32_defined
#define ____localdep_crt_dos_ftime32_defined 1
#ifdef __CRT_HAVE__ftime32
/* Fill in TIMEBUF with information about the current time */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_crt_dos_ftime32,(struct __timeb32 *__timebuf),_ftime32,(__timebuf))
#else /* LIBC: _ftime32 */
#undef ____localdep_crt_dos_ftime32_defined
#endif /* crt_dos_ftime32... */
#endif /* !____localdep_crt_dos_ftime32_defined */

/* Dependency: "crt_ftime32_s" from "sys.timeb" */
#ifndef ____localdep_crt_ftime32_s_defined
#define ____localdep_crt_ftime32_s_defined 1
#ifdef __CRT_HAVE__ftime32_s
/* Fill in TIMEBUF with information about the current time */
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,__localdep_crt_ftime32_s,(struct __timeb32 *__timebuf),_ftime32_s,(__timebuf))
#else /* LIBC: _ftime32_s */
#undef ____localdep_crt_ftime32_s_defined
#endif /* crt_ftime32_s... */
#endif /* !____localdep_crt_ftime32_s_defined */

/* Dependency: "crt_ftime32" from "sys.timeb" */
#ifndef ____localdep_crt_ftime32_defined
#define ____localdep_crt_ftime32_defined 1
#ifdef __CRT_HAVE_ftime
/* Fill in TIMEBUF with information about the current time */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_crt_ftime32,(struct __timeb32 *__timebuf),ftime,(__timebuf))
#else /* LIBC: ftime */
#undef ____localdep_crt_ftime32_defined
#endif /* crt_ftime32... */
#endif /* !____localdep_crt_ftime32_defined */

__NAMESPACE_LOCAL_BEGIN
/* Fill in TIMEBUF with information about the current time */
__LOCAL_LIBC(_ftime64) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_ftime64))(struct __timeb64 *__timebuf) {
#line 101 "kos/src/libc/magic/sys.timeb.c"
#if defined(__CRT_HAVE__ftime64_s)
	if __unlikely(__localdep_crt_ftime64_s(__timebuf))
		__localdep_memset(__timebuf,0,sizeof(*__timebuf));
#elif defined(__CRT_HAVE_ftime64)
	if __unlikely(__localdep_crt_ftime64(__timebuf))
		__localdep_memset(__timebuf,0,sizeof(*__timebuf));
#elif defined(__CRT_HAVE__ftime32)
	struct __timeb32 __temp;
	__localdep_crt_dos_ftime32(&__temp)
	__timebuf->time     = (__time64_t)__temp.time;
	__timebuf->millitm  = __temp.millitm;
	__timebuf->timezone = __temp.timezone;
	__timebuf->dstflag  = __temp.dstflag;
#else
	struct __timeb32 __temp;
#ifdef __CRT_HAVE__ftime32_s
	if __unlikely(__localdep_crt_ftime32_s(&__temp))
#else /* __CRT_HAVE__ftime32_s */
	if __unlikely(__localdep_crt_ftime32(&__temp))
#endif /* !__CRT_HAVE__ftime32_s */
	{
		__localdep_memset(__timebuf, 0, sizeof(*__timebuf));
	} else {
		__timebuf->time     = (__time64_t)__temp.time;
		__timebuf->millitm  = __temp.millitm;
		__timebuf->timezone = __temp.timezone;
		__timebuf->dstflag  = __temp.dstflag;
	}
#endif
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE__ftime64_s || __CRT_HAVE_ftime64 || __CRT_HAVE__ftime32 || __CRT_HAVE__ftime32_s || __CRT_HAVE_ftime */
#endif /* !__local__ftime64_defined */
