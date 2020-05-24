/* HASH CRC-32:0x42f2d290 */
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
#ifndef __local_fsetpos_defined
#if defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)
#define __local_fsetpos_defined 1
#include <__crt.h>
#include <kos/anno.h>
/* Dependency: "crt_fseeko64" from "stdio" */
#ifndef ____localdep_crt_fseeko64_defined
#define ____localdep_crt_fseeko64_defined 1
#if defined(__CRT_HAVE_fseeko64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko64,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko64_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko64_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),_fseeki64_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseeki64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseeko64,(__FILE *__restrict __stream, __off32_t __off, int __whence),_fseeki64,(__stream,__off,__whence))
#else /* LIBC: fseeko64 */
#undef ____localdep_crt_fseeko64_defined
#endif /* crt_fseeko64... */
#endif /* !____localdep_crt_fseeko64_defined */

/* Dependency: "crt_fsetpos" from "stdio" */
#ifndef ____localdep_crt_fsetpos_defined
#define ____localdep_crt_fsetpos_defined 1
#if defined(__CRT_HAVE_fsetpos_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fsetpos,(__FILE *__restrict __stream, __pos32_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fsetpos,(__FILE *__restrict __stream, __pos32_t const *__restrict __pos),fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fsetpos,(__FILE *__restrict __stream, __pos32_t const *__restrict __pos),_IO_fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos_unlocked)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fsetpos,(__FILE *__restrict __stream, __pos32_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#else /* LIBC: fsetpos */
#undef ____localdep_crt_fsetpos_defined
#endif /* crt_fsetpos... */
#endif /* !____localdep_crt_fsetpos_defined */

/* Dependency: "crt_fsetpos64" from "stdio" */
#ifndef ____localdep_crt_fsetpos64_defined
#define ____localdep_crt_fsetpos64_defined 1
#if defined(__CRT_HAVE_fsetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fsetpos64,(__FILE *__restrict __stream, __pos64_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fsetpos64,(__FILE *__restrict __stream, __pos64_t const *__restrict __pos),fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fsetpos64,(__FILE *__restrict __stream, __pos64_t const *__restrict __pos),_IO_fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__THROWING,__localdep_crt_fsetpos64,(__FILE *__restrict __stream, __pos64_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#else /* LIBC: fsetpos64 */
#undef ____localdep_crt_fsetpos64_defined
#endif /* crt_fsetpos64... */
#endif /* !____localdep_crt_fsetpos64_defined */

/* Dependency: "crt_fseeko" from "stdio" */
#ifndef ____localdep_crt_fseeko_defined
#define ____localdep_crt_fseeko_defined 1
#if defined(__CRT_HAVE_fseeko_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseeko_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseeko,(__FILE *__restrict __stream, __off32_t __off, int __whence),fseeko_unlocked,(__stream,__off,__whence))
#else /* LIBC: fseeko */
#undef ____localdep_crt_fseeko_defined
#endif /* crt_fseeko... */
#endif /* !____localdep_crt_fseeko_defined */

/* Dependency: "crt_fseek" from "stdio" */
#ifndef ____localdep_crt_fseek_defined
#define ____localdep_crt_fseek_defined 1
#if defined(__CRT_HAVE_fseek_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseek,(__stream,__off,__whence))
#elif defined(__CRT_HAVE_fseek_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),fseek_unlocked,(__stream,__off,__whence))
#elif defined(__CRT_HAVE__fseek_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_crt_fseek,(__FILE *__restrict __stream, long int __off, int __whence),_fseek_nolock,(__stream,__off,__whence))
#else /* LIBC: fseek */
#undef ____localdep_crt_fseek_defined
#endif /* crt_fseek... */
#endif /* !____localdep_crt_fseek_defined */

__NAMESPACE_LOCAL_BEGIN
/* Set the file position of `STREAM' to `POS', as previously initialized with a call to `fgetpos()' */
__LOCAL_LIBC(fsetpos) __ATTR_NONNULL((1, 2)) int
(__LIBCCALL __LIBC_LOCAL_NAME(fsetpos))(__FILE *__restrict __stream,
                                        __FS_TYPE(pos) const *__restrict __pos) __THROWS(...) {
#line 798 "kos/src/libc/magic/stdio.c"
#if defined(__USE_FILE_OFFSET64) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64))
	return __localdep_crt_fseeko64(__stream, (__off64_t)*__pos, __SEEK_SET);
#elif defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked)
	__pos32_t __pos32 = (__pos32_t)*__pos;
	return __localdep_crt_fsetpos(__stream, &__pos32);
#elif defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked)
	__pos64_t __pos64 = (__pos64_t)*__pos;
	return __localdep_crt_fsetpos64(__stream, &__pos64);
#elif defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE__fseeki64)
	return __localdep_crt_fseeko64(__stream, (__off64_t)*__pos, __SEEK_SET);
#elif defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked)
	return __localdep_crt_fseeko(__stream, (__off32_t)*__pos, __SEEK_SET);
#else
	return __localdep_crt_fseek(__stream, (long int)*__pos, __SEEK_SET);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_fseeko64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE__fseeki64 || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || __CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock */
#endif /* !__local_fsetpos_defined */
