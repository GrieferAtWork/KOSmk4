/* HASH CRC-32:0x5d115b0e */
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
#ifndef __local_fgetpos64_defined
#define __local_fgetpos64_defined 1
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || (defined(__CRT_HAVE_fgetpos64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE__IO_fgetpos64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_fgetpos_unlocked) || (defined(__CRT_HAVE_fgetpos64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
#include <bits/crt/stdio.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: crt_fgetpos from stdio */
#ifndef __local___localdep_crt_fgetpos_defined
#define __local___localdep_crt_fgetpos_defined 1
#if defined(__CRT_HAVE_fgetpos_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),_IO_fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),_IO_fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos_unlocked)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#else /* ... */
#undef __local___localdep_crt_fgetpos_defined
#endif /* !... */
#endif /* !__local___localdep_crt_fgetpos_defined */
/* Dependency: crt_ftell from stdio */
#ifndef __local___localdep_crt_ftell_defined
#define __local___localdep_crt_ftell_defined 1
#if defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell)
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell)
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),long int,__THROWING,__localdep_crt_ftell,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#else /* ... */
#undef __local___localdep_crt_ftell_defined
#endif /* !... */
#endif /* !__local___localdep_crt_ftell_defined */
/* Dependency: crt_ftello from stdio */
#ifndef __local___localdep_crt_ftello_defined
#define __local___localdep_crt_ftello_defined 1
#if defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello)
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#else /* ... */
#undef __local___localdep_crt_ftello_defined
#endif /* !... */
#endif /* !__local___localdep_crt_ftello_defined */
/* Dependency: crt_ftello64 from stdio */
#ifndef __local___localdep_crt_ftello64_defined
#define __local___localdep_crt_ftello64_defined 1
#if defined(__CRT_HAVE_ftell_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64)
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64)
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64)
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,__THROWING,__localdep_crt_ftello64,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#else /* ... */
#undef __local___localdep_crt_ftello64_defined
#endif /* !... */
#endif /* !__local___localdep_crt_ftello64_defined */
/* 64-bit variant of `fgetpos' */
__LOCAL_LIBC(fgetpos64) __ATTR_NONNULL((1, 2)) int
(__LIBCCALL __LIBC_LOCAL_NAME(fgetpos64))(__FILE *__restrict __stream, __fpos64_t *__restrict __pos) __THROWS(...) {
#if (defined(__CRT_HAVE_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE_ftello) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || (defined(__CRT_HAVE_ftell_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE__ftell_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE_ftello_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock)
	return (__INT64_TYPE__)(*__pos = (__fpos64_t)__localdep_crt_ftello64(__stream)) < 0 ? -1 : 0;
#elif defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || (defined(__CRT_HAVE_fgetpos64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE__IO_fgetpos64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_fgetpos_unlocked) || (defined(__CRT_HAVE_fgetpos64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
	__pos32_t __pos32;
	int __result = __localdep_crt_fgetpos(__stream, &__pos32);
	if (!__result)
		*__pos = (__fpos64_t)__pos32;
	return __result;
#elif (defined(__CRT_HAVE_ftell) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__) || defined(__CRT_HAVE_ftello) || (defined(__CRT_HAVE_ftell_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE__ftell_nolock) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__) || defined(__CRT_HAVE_ftello_unlocked)
	return (__INT64_TYPE__)(*__pos = (__fpos64_t)__localdep_crt_ftello(__stream)) < 0 ? -1 : 0;
#else /* ... */
	return (__INT64_TYPE__)(*__pos = (__fpos64_t)__localdep_crt_ftell(__stream)) < 0 ? -1 : 0;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fgetpos64_defined
#define __local___localdep_fgetpos64_defined 1
#define __localdep_fgetpos64 __LIBC_LOCAL_NAME(fgetpos64)
#endif /* !__local___localdep_fgetpos64_defined */
#else /* __CRT_HAVE_ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || (__CRT_HAVE_fgetpos64 && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (__CRT_HAVE__IO_fgetpos64 && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || __CRT_HAVE_fgetpos_unlocked || (__CRT_HAVE_fgetpos64_unlocked && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock */
#undef __local_fgetpos64_defined
#endif /* !__CRT_HAVE_ftello64 && !__CRT_HAVE_ftell64 && !__CRT_HAVE__ftelli64 && !__CRT_HAVE_ftello64_unlocked && !__CRT_HAVE_ftell64_unlocked && !__CRT_HAVE__ftelli64_nolock && !__CRT_HAVE_fgetpos && !__CRT_HAVE__IO_fgetpos && (!__CRT_HAVE_fgetpos64 || __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) && (!__CRT_HAVE__IO_fgetpos64 || __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) && !__CRT_HAVE_fgetpos_unlocked && (!__CRT_HAVE_fgetpos64_unlocked || __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) && !__CRT_HAVE_ftello && !__CRT_HAVE_ftello_unlocked && !__CRT_HAVE_ftell && !__CRT_HAVE__IO_ftell && !__CRT_HAVE_ftell_unlocked && !__CRT_HAVE__ftell_nolock */
#endif /* !__local_fgetpos64_defined */
