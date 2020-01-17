/* HASH CRC-32:0x2ff8084f */
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
#ifndef __local_posix_fadvise_defined
#define __local_posix_fadvise_defined 1
#include <bits/types.h>
#include <bits/types.h>
/* Dependency: "posix_fadvise64" from "fcntl" */
#ifndef ____localdep_posix_fadvise64_defined
#define ____localdep_posix_fadvise64_defined 1
#ifdef __CRT_HAVE_posix_fadvise64
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_posix_fadvise64,(__fd_t __fd, __off64_t __offset, __off64_t __length, int __advise),posix_fadvise64,(__fd,__offset,__length,__advise))
#elif defined(__CRT_HAVE_posix_fadvise) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_posix_fadvise64,(__fd_t __fd, __off64_t __offset, __off64_t __length, int __advise),posix_fadvise,(__fd,__offset,__length,__advise))
#else /* LIBC: posix_fadvise64 */
#include <local/fcntl/posix_fadvise64.h>
#define __localdep_posix_fadvise64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_fadvise64))
#endif /* posix_fadvise64... */
#endif /* !____localdep_posix_fadvise64_defined */

/* Dependency: "posix_fadvise32" from "fcntl" */
#ifndef ____localdep_posix_fadvise32_defined
#define ____localdep_posix_fadvise32_defined 1
#ifdef __CRT_HAVE_posix_fadvise
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_posix_fadvise32,(__fd_t __fd, __off32_t __offset, __off32_t __length, int __advise),posix_fadvise,(__fd,__offset,__length,__advise))
#else /* LIBC: posix_fadvise */
#undef ____localdep_posix_fadvise32_defined
#endif /* posix_fadvise32... */
#endif /* !____localdep_posix_fadvise32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(posix_fadvise) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_fadvise))(__fd_t __fd,
                                                           __FS_TYPE(off) __offset,
                                                           __FS_TYPE(off) __length,
                                                           int __advise) {
#line 302 "kos/src/libc/magic/fcntl.c"
#ifdef __CRT_HAVE_posix_fadvise64
	return __localdep_posix_fadvise64(__fd, (__off64_t)__offset, (__off64_t)__length, __advise);
#elif defined(__CRT_HAVE_posix_fadvise)
	return __localdep_posix_fadvise32(__fd, (__off32_t)__offset, (__off32_t)__length, __advise);
#else /* __CRT_HAVE_posix_fadvise64 */
	(void)__fd;
	(void)__offset;
	(void)__length;
	(void)__advise;
	return 0;
#endif /* !__CRT_HAVE_posix_fadvise64 */
}
__NAMESPACE_LOCAL_END
#endif /* !__local_posix_fadvise_defined */
