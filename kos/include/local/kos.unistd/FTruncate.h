/* HASH CRC-32:0xea4568e8 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_FTruncate_defined
#if defined(__CRT_HAVE_FTruncate) || defined(__CRT_HAVE_FTruncate64)
#define __local_FTruncate_defined 1
#include <kos/anno.h>
/* Dependency: "FTruncate32" from "kos.unistd" */
#ifndef ____localdep_FTruncate32_defined
#define ____localdep_FTruncate32_defined 1
#ifdef __CRT_HAVE_FTruncate
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT(,int,,__localdep_FTruncate32,(__fd_t __fd, __pos32_t __length),FTruncate,(__fd,__length)) __THROWS(...)
#else /* LIBC: FTruncate */
#undef ____localdep_FTruncate32_defined
#endif /* FTruncate32... */
#endif /* !____localdep_FTruncate32_defined */

/* Dependency: "FTruncate64" from "kos.unistd" */
#ifndef ____localdep_FTruncate64_defined
#define ____localdep_FTruncate64_defined 1
#ifdef __CRT_HAVE_FTruncate64
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT_VOID(,,__localdep_FTruncate64,(__fd_t __fd, __pos64_t __length),FTruncate64,(__fd,__length)) __THROWS(...)
#elif defined(__CRT_HAVE_FTruncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__CREDIRECT_VOID(,,__localdep_FTruncate64,(__fd_t __fd, __pos64_t __length),FTruncate,(__fd,__length)) __THROWS(...)
#elif defined(__CRT_HAVE_FTruncate)
#include <local/kos.unistd/FTruncate64.h>
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
#define __localdep_FTruncate64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(FTruncate64))
#else /* CUSTOM: FTruncate64 */
#undef ____localdep_FTruncate64_defined
#endif /* FTruncate64... */
#endif /* !____localdep_FTruncate64_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> ftruncate(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__LOCAL_LIBC(FTruncate) void
(__LIBCCALL __LIBC_LOCAL_NAME(FTruncate))(__fd_t __fd,
                                          __FS_TYPE(pos) __length) __THROWS(...) {
#line 605 "kos/src/libc/magic/kos.unistd.c"
#ifdef __CRT_HAVE_FTruncate
	__localdep_FTruncate32(__fd, (__pos32_t)__length);
#else /* __CRT_HAVE_FTruncate */
	__localdep_FTruncate64(__fd, (__pos64_t)__length);
#endif /* !__CRT_HAVE_FTruncate */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_FTruncate || __CRT_HAVE_FTruncate64 */
#endif /* !__local_FTruncate_defined */
