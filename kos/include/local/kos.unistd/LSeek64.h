/* HASH CRC-32:0x8a188bde */
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
#ifndef __local_LSeek64_defined
#ifdef __CRT_HAVE_LSeek
#define __local_LSeek64_defined 1
#include <kos/anno.h>
/* Dependency: "LSeek32" from "kos.unistd" */
#ifndef ____localdep_LSeek32_defined
#define ____localdep_LSeek32_defined 1
#ifdef __CRT_HAVE_LSeek
/* >> lseek32(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__CREDIRECT(,__pos32_t,,__localdep_LSeek32,(__fd_t __fd, __off32_t __offset, int __whence),LSeek,(__fd,__offset,__whence)) __THROWS(...)
#else /* LIBC: LSeek */
#undef ____localdep_LSeek32_defined
#endif /* LSeek32... */
#endif /* !____localdep_LSeek32_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> lseek64(2)
 * Change the position of the file read/write pointer within a file referred to by `FD' */
__LOCAL_LIBC(LSeek64) __pos64_t
(__LIBCCALL __LIBC_LOCAL_NAME(LSeek64))(__fd_t __fd,
                                        __off64_t __offset,
                                        int __whence) __THROWS(...) {
#line 293 "kos/src/libc/magic/kos.unistd.c"
	return __localdep_LSeek32(__fd, (__off32_t)__offset, __whence);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_LSeek */
#endif /* !__local_LSeek64_defined */
