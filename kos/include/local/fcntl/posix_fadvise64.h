/* HASH CRC-32:0x94dc8d11 */
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
#ifndef __local_posix_fadvise64_defined
#define __local_posix_fadvise64_defined 1
#include <bits/types.h>
#include <bits/types.h>
/* Dependency: "posix_fadvise32" from "fcntl" */
#ifndef ____localdep_posix_fadvise32_defined
#define ____localdep_posix_fadvise32_defined 1
#if defined(__CRT_HAVE_posix_fadvise)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_posix_fadvise32,(__fd_t __fd, __off32_t __offset, __off32_t __length, int __advise),posix_fadvise,(__fd,__offset,__length,__advise))
#else /* LIBC: posix_fadvise */
#undef ____localdep_posix_fadvise32_defined
#endif /* posix_fadvise32... */
#endif /* !____localdep_posix_fadvise32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(posix_fadvise64) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_fadvise64))(__fd_t __fd,
                                                             __off64_t __offset,
                                                             __off64_t __length,
                                                             int __advise) {
#line 340 "kos/src/libc/magic/fcntl.c"
#ifdef __CRT_HAVE_posix_fadvise
	return __localdep_posix_fadvise32(__fd, (__off32_t)__offset, (__off32_t)__length, __advise);
#else /* __CRT_HAVE_posix_fadvise */
	(void)__fd;
	(void)__offset;
	(void)__length;
	(void)__advise;
	return 0;
#endif /* !__CRT_HAVE_posix_fadvise */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_posix_fadvise64_defined */
