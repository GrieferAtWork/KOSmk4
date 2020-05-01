/* HASH CRC-32:0x2577a143 */
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
#ifndef __local_PWrite64_defined
#ifdef __CRT_HAVE_PWrite
#define __local_PWrite64_defined 1
#include <__crt.h>
#include <kos/anno.h>
/* Dependency: "PWrite32" from "kos.unistd" */
#ifndef ____localdep_PWrite32_defined
#define ____localdep_PWrite32_defined 1
#ifdef __CRT_HAVE_PWrite
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,,__localdep_PWrite32,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize, __pos32_t __offset),PWrite,(__fd,__buf,__bufsize,__offset)) __THROWS(...)
#else /* LIBC: PWrite */
#undef ____localdep_PWrite32_defined
#endif /* PWrite32... */
#endif /* !____localdep_PWrite32_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__LOCAL_LIBC(PWrite64) __ATTR_NONNULL((2)) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(PWrite64))(__fd_t __fd,
                                         void *__buf,
                                         __SIZE_TYPE__ __bufsize,
                                         __pos64_t __offset) __THROWS(...) {
#line 365 "kos/src/libc/magic/kos.unistd.c"
	return __localdep_PWrite32(__fd, __buf, __bufsize, (__pos32_t)__offset);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_PWrite */
#endif /* !__local_PWrite64_defined */
