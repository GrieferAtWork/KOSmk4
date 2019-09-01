/* HASH 0xc49a397f */
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
#ifndef __local_fallocate64_defined
#define __local_fallocate64_defined 1
#include <bits/types.h>
#include <bits/types.h>
/* Dependency: "fallocate" from "fcntl" */
#ifndef ____localdep_fallocate_defined
#define ____localdep_fallocate_defined 1
#if defined(__CRT_HAVE_fallocate64) && (defined(__USE_FILE_OFFSET64))
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_fallocate,(__fd_t __fd, int __mode, __off64_t __offset, __off64_t __length),fallocate64,(__fd,__mode,__offset,__length))
#elif defined(__CRT_HAVE_fallocate) && (!defined(__USE_FILE_OFFSET64))
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_fallocate,(__fd_t __fd, int __mode, __off32_t __offset, __off32_t __length),fallocate,(__fd,__mode,__offset,__length))
#else /* LIBC: fallocate */
#include <local/fcntl/fallocate.h>
#define __localdep_fallocate(fd, mode, offset, length) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fallocate))(fd, mode, (__FS_TYPE(off))(offset), (__FS_TYPE(off))(length))
#endif /* fallocate... */
#endif /* !____localdep_fallocate_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fallocate64) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fallocate64))(__fd_t __fd,
                                                         int __mode,
                                                         __off64_t __offset,
                                                         __off64_t __length) {
#line 169 "kos/src/libc/magic/fcntl.c"
#ifdef __CRT_HAVE_fallocate
	return __localdep_fallocate(__fd, __mode, (__off32_t)__offset, (__off32_t)__length);
#else /* __CRT_HAVE_fallocate */
	(void)__fd;
	(void)__mode;
	(void)__offset;
	(void)__length;
	return 0;
#endif /* !__CRT_HAVE_fallocate */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_fallocate64_defined */
