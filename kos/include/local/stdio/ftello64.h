/* HASH CRC-32:0xcbc2ae79 */
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
#ifndef __local_ftello64_defined
#define __local_ftello64_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftello) || (defined(__CRT_HAVE_ftello64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE_ftell64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE__ftelli64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_ftello_unlocked) || (defined(__CRT_HAVE_ftello64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE_ftell64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE__ftelli64_nolock) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || (defined(__CRT_HAVE_ftello64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE_ftell64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE__ftelli64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock) || (defined(__CRT_HAVE_ftello64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE_ftell64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE__ftelli64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: crt_fgetpos from stdio */
#ifndef __local___localdep_crt_fgetpos_defined
#define __local___localdep_crt_fgetpos_defined 1
#if defined(__CRT_HAVE_fgetpos_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),_IO_fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),_IO_fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos_unlocked)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#else /* ... */
#undef __local___localdep_crt_fgetpos_defined
#endif /* !... */
#endif /* !__local___localdep_crt_fgetpos_defined */
/* Dependency: crt_fgetpos64 from stdio */
#ifndef __local___localdep_crt_fgetpos64_defined
#define __local___localdep_crt_fgetpos64_defined 1
#if defined(__CRT_HAVE_fgetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos64,(__FILE *__restrict __stream, __pos64_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos64,(__FILE *__restrict __stream, __pos64_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos64,(__FILE *__restrict __stream, __pos64_t *__restrict __pos),fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos64,(__FILE *__restrict __stream, __pos64_t *__restrict __pos),_IO_fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos64,(__FILE *__restrict __stream, __pos64_t *__restrict __pos),fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos64)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos64,(__FILE *__restrict __stream, __pos64_t *__restrict __pos),_IO_fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos64,(__FILE *__restrict __stream, __pos64_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fgetpos64,(__FILE *__restrict __stream, __pos64_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#else /* ... */
#undef __local___localdep_crt_fgetpos64_defined
#endif /* !... */
#endif /* !__local___localdep_crt_fgetpos64_defined */
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
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#elif defined(__CRT_HAVE_ftell) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftell,(__stream))
#elif defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),_IO_ftell,(__stream))
#elif defined(__CRT_HAVE_ftello)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello,(__stream))
#elif defined(__CRT_HAVE_ftello64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello64,(__stream))
#elif defined(__CRT_HAVE_ftell64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftell64,(__stream))
#elif defined(__CRT_HAVE__ftelli64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),_ftelli64,(__stream))
#elif defined(__CRT_HAVE_ftell_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftell_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftell_nolock) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),_ftell_nolock,(__stream))
#elif defined(__CRT_HAVE_ftello_unlocked)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftello64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello64_unlocked,(__stream))
#elif defined(__CRT_HAVE_ftell64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),ftell64_unlocked,(__stream))
#elif defined(__CRT_HAVE__ftelli64_nolock) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,__THROWING,__localdep_crt_ftello,(__FILE *__restrict __stream),_ftelli64_nolock,(__stream))
#else /* ... */
#undef __local___localdep_crt_ftello_defined
#endif /* !... */
#endif /* !__local___localdep_crt_ftello_defined */
/* 64-bit variant of `ftello' */
__LOCAL_LIBC(ftello64) __ATTR_WUNUSED __ATTR_NONNULL((1)) __off64_t
(__LIBCCALL __LIBC_LOCAL_NAME(ftello64))(__FILE *__restrict __stream) __THROWS(...) {
#if (defined(__CRT_HAVE_fgetpos) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || (defined(__CRT_HAVE__IO_fgetpos) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || (defined(__CRT_HAVE_fgetpos_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_fgetpos64_unlocked)
	__pos64_t __pos;
	if (__localdep_crt_fgetpos64(__stream, &__pos))
		return -1;
	return (__off64_t)__pos;
#elif defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked)
	__pos32_t __pos;
	if (__localdep_crt_fgetpos(__stream, &__pos))
		return -1;
	return (__off64_t)(__off32_t)__pos;
#elif (defined(__CRT_HAVE_ftell) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE__IO_ftell) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__) || defined(__CRT_HAVE_ftello) || (defined(__CRT_HAVE_ftello64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE_ftell64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE__ftelli64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE_ftell_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE__ftell_nolock) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__) || defined(__CRT_HAVE_ftello_unlocked) || (defined(__CRT_HAVE_ftello64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE_ftell64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE__ftelli64_nolock) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
	return (__off64_t)__localdep_crt_ftello(__stream);
#else /* ... */
	return (__off64_t)__localdep_crt_ftell(__stream);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ftello64_defined
#define __local___localdep_ftello64_defined 1
#define __localdep_ftello64 __LIBC_LOCAL_NAME(ftello64)
#endif /* !__local___localdep_ftello64_defined */
#else /* __CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_ftello || (__CRT_HAVE_ftello64 && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (__CRT_HAVE_ftell64 && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (__CRT_HAVE__ftelli64 && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || __CRT_HAVE_ftello_unlocked || (__CRT_HAVE_ftello64_unlocked && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (__CRT_HAVE_ftell64_unlocked && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (__CRT_HAVE__ftelli64_nolock && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || (__CRT_HAVE_ftello64 && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || (__CRT_HAVE_ftell64 && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || (__CRT_HAVE__ftelli64 && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock || (__CRT_HAVE_ftello64_unlocked && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || (__CRT_HAVE_ftell64_unlocked && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) || (__CRT_HAVE__ftelli64_nolock && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__) */
#undef __local_ftello64_defined
#endif /* !__CRT_HAVE_fgetpos64 && !__CRT_HAVE__IO_fgetpos64 && !__CRT_HAVE_fgetpos64_unlocked && !__CRT_HAVE_fgetpos && !__CRT_HAVE__IO_fgetpos && !__CRT_HAVE_fgetpos_unlocked && !__CRT_HAVE_ftello && (!__CRT_HAVE_ftello64 || __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) && (!__CRT_HAVE_ftell64 || __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) && (!__CRT_HAVE__ftelli64 || __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) && !__CRT_HAVE_ftello_unlocked && (!__CRT_HAVE_ftello64_unlocked || __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) && (!__CRT_HAVE_ftell64_unlocked || __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) && (!__CRT_HAVE__ftelli64_nolock || __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__) && !__CRT_HAVE_ftell && !__CRT_HAVE__IO_ftell && (!__CRT_HAVE_ftello64 || __SIZEOF_LONG__ != __SIZEOF_OFF64_T__) && (!__CRT_HAVE_ftell64 || __SIZEOF_LONG__ != __SIZEOF_OFF64_T__) && (!__CRT_HAVE__ftelli64 || __SIZEOF_LONG__ != __SIZEOF_OFF64_T__) && !__CRT_HAVE_ftell_unlocked && !__CRT_HAVE__ftell_nolock && (!__CRT_HAVE_ftello64_unlocked || __SIZEOF_LONG__ != __SIZEOF_OFF64_T__) && (!__CRT_HAVE_ftell64_unlocked || __SIZEOF_LONG__ != __SIZEOF_OFF64_T__) && (!__CRT_HAVE__ftelli64_nolock || __SIZEOF_LONG__ != __SIZEOF_OFF64_T__) */
#endif /* !__local_ftello64_defined */
