/* HASH CRC-32:0xe6919335 */
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
#ifndef __local_ftruncate_defined
#if defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s)
#define __local_ftruncate_defined 1
/* Dependency: "ftruncate32" from "unistd" */
#ifndef ____localdep_ftruncate32_defined
#define ____localdep_ftruncate32_defined 1
#ifdef __CRT_HAVE_ftruncate
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_ftruncate32,(__fd_t __fd, __pos32_t __length),ftruncate,(__fd,__length))
#else /* LIBC: ftruncate */
#undef ____localdep_ftruncate32_defined
#endif /* ftruncate32... */
#endif /* !____localdep_ftruncate32_defined */

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
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__LOCAL_LIBC(ftruncate) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ftruncate))(__fd_t __fd,
                                                       __PIO_OFFSET __length) {
#line 1638 "kos/src/libc/magic/unistd.c"
#if defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize)
	return __localdep_ftruncate32(__fd, (__pos32_t)__length);
#else
	return __localdep_ftruncate64(__fd, (__pos64_t)__length);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) */
#endif /* !__local_ftruncate_defined */
