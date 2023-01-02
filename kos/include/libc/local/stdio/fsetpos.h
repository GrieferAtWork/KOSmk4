/* HASH CRC-32:0x9e4cc14a */
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
#ifndef __local_fsetpos_defined
#define __local_fsetpos_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#include <kos/anno.h>
#include <bits/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_fseek_defined
#define __local___localdep_crt_fseek_defined
#if defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && __SIZEOF_LONG__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#else /* ... */
#undef __local___localdep_crt_fseek_defined
#endif /* !... */
#endif /* !__local___localdep_crt_fseek_defined */
#ifndef __local___localdep_crt_fseeko_defined
#define __local___localdep_crt_fseeko_defined
#if defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#else /* ... */
#undef __local___localdep_crt_fseeko_defined
#endif /* !... */
#endif /* !__local___localdep_crt_fseeko_defined */
#ifndef __local___localdep_crt_fseeko64_defined
#define __local___localdep_crt_fseeko64_defined
#if defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseek64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),_fseeki64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek64_unlocked)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseek64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#else /* ... */
#undef __local___localdep_crt_fseeko64_defined
#endif /* !... */
#endif /* !__local___localdep_crt_fseeko64_defined */
#ifndef __local___localdep_crt_fsetpos_defined
#define __local___localdep_crt_fsetpos_defined
#if defined(__CRT_HAVE_fsetpos_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos,(__FILE *__restrict __stream, __pos32_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos,(__FILE *__restrict __stream, __pos32_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos,(__FILE *__restrict __stream, __pos32_t const *__restrict __pos),fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos,(__FILE *__restrict __stream, __pos32_t const *__restrict __pos),_IO_fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos,(__FILE *__restrict __stream, __pos32_t const *__restrict __pos),fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos,(__FILE *__restrict __stream, __pos32_t const *__restrict __pos),_IO_fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos_unlocked)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos,(__FILE *__restrict __stream, __pos32_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos,(__FILE *__restrict __stream, __pos32_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#else /* ... */
#undef __local___localdep_crt_fsetpos_defined
#endif /* !... */
#endif /* !__local___localdep_crt_fsetpos_defined */
#ifndef __local___localdep_crt_fsetpos64_defined
#define __local___localdep_crt_fsetpos64_defined
#if defined(__CRT_HAVE_fsetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos64,(__FILE *__restrict __stream, __pos64_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos64,(__FILE *__restrict __stream, __pos64_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos64,(__FILE *__restrict __stream, __pos64_t const *__restrict __pos),fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos64,(__FILE *__restrict __stream, __pos64_t const *__restrict __pos),_IO_fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos64,(__FILE *__restrict __stream, __pos64_t const *__restrict __pos),fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos64)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos64,(__FILE *__restrict __stream, __pos64_t const *__restrict __pos),_IO_fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos64,(__FILE *__restrict __stream, __pos64_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__THROWING,__localdep_crt_fsetpos64,(__FILE *__restrict __stream, __pos64_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#else /* ... */
#undef __local___localdep_crt_fsetpos64_defined
#endif /* !... */
#endif /* !__local___localdep_crt_fsetpos64_defined */
__LOCAL_LIBC(fsetpos) __ATTR_IN(2) __ATTR_INOUT(1) int
(__LIBCCALL __LIBC_LOCAL_NAME(fsetpos))(__FILE *__restrict __stream, __fpos_t const *__restrict __pos) __THROWS(...) {
#if __SIZEOF_OFF_T__ == __SIZEOF_OFF64_T__ && ((defined(__CRT_HAVE_fseek) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE_fseeko) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || (defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock))
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_fseeko64)(__stream, (__off64_t)*__pos, __SEEK_SET);
#elif defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || (defined(__CRT_HAVE_fsetpos64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || (defined(__CRT_HAVE__IO_fsetpos64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__CRT_HAVE_fsetpos64_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
	__pos32_t __pos32 = (__pos32_t)*__pos;
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_fsetpos)(__stream, &__pos32);
#elif defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked)
	__fpos64_t __pos64 = (__fpos64_t)*__pos;
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_fsetpos64)(__stream, &__pos64);
#elif (defined(__CRT_HAVE_fseek) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE_fseeko) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || (defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF64_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE_fseeko_unlocked) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock)
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_fseeko64)(__stream, (__off64_t)*__pos, __SEEK_SET);
#elif (defined(__CRT_HAVE_fseek) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__) || defined(__CRT_HAVE_fseeko) || (defined(__CRT_HAVE_fseek_unlocked) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__) || (defined(__CRT_HAVE__fseek_nolock) && __SIZEOF_OFF32_T__ == __SIZEOF_LONG__) || defined(__CRT_HAVE_fseeko_unlocked)
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_fseeko)(__stream, (__off32_t)*__pos, __SEEK_SET);
#else /* ... */
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_fseek)(__stream, (long int)*__pos, __SEEK_SET);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fsetpos_defined
#define __local___localdep_fsetpos_defined
#define __localdep_fsetpos __LIBC_LOCAL_NAME(fsetpos)
#endif /* !__local___localdep_fsetpos_defined */
#else /* __CRT_HAVE_fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || __CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock */
#undef __local_fsetpos_defined
#endif /* !__CRT_HAVE_fseeko64 && !__CRT_HAVE_fseek64 && !__CRT_HAVE__fseeki64 && !__CRT_HAVE_fseeko64_unlocked && !__CRT_HAVE_fseek64_unlocked && !__CRT_HAVE__fseeki64_nolock && !__CRT_HAVE_fsetpos && !__CRT_HAVE__IO_fsetpos && !__CRT_HAVE_fsetpos_unlocked && !__CRT_HAVE_fsetpos64 && !__CRT_HAVE__IO_fsetpos64 && !__CRT_HAVE_fsetpos64_unlocked && !__CRT_HAVE_fseeko && !__CRT_HAVE_fseeko_unlocked && !__CRT_HAVE_fseek && !__CRT_HAVE_fseek_unlocked && !__CRT_HAVE__fseek_nolock */
#endif /* !__local_fsetpos_defined */
