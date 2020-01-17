/* HASH CRC-32:0xa9f5d9a2 */
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
#ifndef __local_FTruncate64_defined
#ifdef __CRT_HAVE_FTruncate
#define __local_FTruncate64_defined 1
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

__NAMESPACE_LOCAL_BEGIN
/* >> ftruncate64(2)
 * Truncate the given file `FD' to a length of `LENGTH' */
__LOCAL_LIBC(FTruncate64) void
(__LIBCCALL __LIBC_LOCAL_NAME(FTruncate64))(__fd_t __fd,
                                            __pos64_t __length) __THROWS(...) {
#line 620 "kos/src/libc/magic/kos.unistd.c"
	__localdep_FTruncate32(__fd, (__pos32_t)__length);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_FTruncate */
#endif /* !__local_FTruncate64_defined */
