/* HASH CRC-32:0x833aaaba */
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
#ifndef __local_ftruncate64_defined
#if defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize)
#define __local_ftruncate64_defined 1
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

__NAMESPACE_LOCAL_BEGIN
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__LOCAL_LIBC(ftruncate64) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ftruncate64))(__fd_t __fd,
                                                         __PIO_OFFSET64 __length) {
#line 1663 "kos/src/libc/magic/unistd.c"
	return __localdep_ftruncate32(__fd, (__pos32_t)__length);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE__chsize) */
#endif /* !__local_ftruncate64_defined */
