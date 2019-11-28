/* HASH CRC-32:0x5572b586 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fftruncate64_defined
#if (defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s)) && (defined(__CRT_HAVE_fileno) || defined(__CRT_HAVE__fileno) || defined(__CRT_HAVE_fileno_unlocked))
#define __local_fftruncate64_defined 1
#include <kos/anno.h>
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
/* Dependency: "fileno" */
#ifndef ____localdep_fileno_defined
#define ____localdep_fileno_defined 1
#if defined(__CRT_HAVE_fileno_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#elif defined(__CRT_HAVE_fileno)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno,(__stream))
#elif defined(__CRT_HAVE__fileno)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),_fileno,(__stream))
#elif defined(__CRT_HAVE_fileno_unlocked)
/* Return the underlying file descriptor number used by `STREAM' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_fileno,(__FILE *__restrict __stream),fileno_unlocked,(__stream))
#else /* LIBC: fileno */
#undef ____localdep_fileno_defined
#endif /* fileno... */
#endif /* !____localdep_fileno_defined */

/* Dependency: "ftruncate64" from "unistd" */
#ifndef ____localdep_ftruncate64_defined
#define ____localdep_ftruncate64_defined 1
#ifdef __CRT_HAVE_ftruncate64
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),ftruncate64,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s)
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate64,(__fd_t __fd, __PIO_OFFSET64 __length),_chsize_s,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize)
#include <local/unistd/ftruncate64.h>
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
#define __localdep_ftruncate64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftruncate64))
#else /* CUSTOM: ftruncate64 */
#undef ____localdep_ftruncate64_defined
#endif /* ftruncate64... */
#endif /* !____localdep_ftruncate64_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> fftruncate64(3)
 * Truncate the given file `STREAM' to a length of `LENGTH' */
__LOCAL_LIBC(fftruncate64) __ATTR_NONNULL((1)) int
(__LIBCCALL __LIBC_LOCAL_NAME(fftruncate64))(__FILE *__restrict __stream,
                                             __PIO_OFFSET64 __length) __THROWS(...) {
#line 2030 "kos/src/libc/magic/stdio.c"
	int __result = -1;
	__fd_t __fd = __localdep_fileno(__stream);
	if __likely(__fd >= 0)
		__result = __localdep_ftruncate64(__fd, __length);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_HAVE_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s) && (__CRT_HAVE_fileno || __CRT_HAVE__fileno || __CRT_HAVE_fileno_unlocked) */
#endif /* !__local_fftruncate64_defined */
