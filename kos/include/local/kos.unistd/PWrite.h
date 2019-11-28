/* HASH CRC-32:0x18cce4b7 */
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
#ifndef __local_PWrite_defined
#ifdef __CRT_HAVE_PWrite64
#define __local_PWrite_defined 1
#include <kos/anno.h>
/* Dependency: "PWrite64" from "kos.unistd" */
#ifndef ____localdep_PWrite64_defined
#define ____localdep_PWrite64_defined 1
#ifdef __CRT_HAVE_PWrite64
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,,__localdep_PWrite64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos64_t __offset),PWrite64,(__fd,__buf,__bufsize,__offset)) __THROWS(...)
#elif defined(__CRT_HAVE_PWrite) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,,__localdep_PWrite64,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize, __pos64_t __offset),PWrite,(__fd,__buf,__bufsize,__offset)) __THROWS(...)
#elif defined(__CRT_HAVE_PWrite)
#include <local/kos.unistd/PWrite64.h>
/* >> pwrite64(2)
 * Write data to a file at a specific offset */
#define __localdep_PWrite64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(PWrite64))
#else /* CUSTOM: PWrite64 */
#undef ____localdep_PWrite64_defined
#endif /* PWrite64... */
#endif /* !____localdep_PWrite64_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> pwrite(2)
 * Write data to a file at a specific offset */
__LOCAL_LIBC(PWrite) __ATTR_NONNULL((2)) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(PWrite))(__fd_t __fd,
                                       void const *__buf,
                                       __SIZE_TYPE__ __bufsize,
                                       __FS_TYPE(pos) __offset) __THROWS(...) {
#line 320 "kos/src/libc/magic/kos.unistd.c"
	return __localdep_PWrite64(__fd, __buf, __bufsize, (__pos64_t)__offset);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_PWrite64 */
#endif /* !__local_PWrite_defined */
