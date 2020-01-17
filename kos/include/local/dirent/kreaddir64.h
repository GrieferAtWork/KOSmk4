/* HASH CRC-32:0x21cd3c77 */
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
#ifndef __local_kreaddir64_defined
#if defined(__CRT_HAVE_kreaddirf64) || (defined(__CRT_HAVE_kreaddirf) && defined(_DIRENT_MATCHES_DIRENT64))
#define __local_kreaddir64_defined 1
/* Dependency: "kreaddirf64" */
#ifndef ____localdep_kreaddirf64_defined
#define ____localdep_kreaddirf64_defined 1
#ifdef __CRT_HAVE_kreaddirf64
/* 64-bit variant of `kreaddirf()' */
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_kreaddirf64,(__fd_t __fd, struct dirent64 *__buf, __SIZE_TYPE__ __bufsize, unsigned int __mode, __oflag_t __flags),kreaddirf64,(__fd,__buf,__bufsize,__mode,__flags))
#elif defined(__CRT_HAVE_kreaddirf) && defined(_DIRENT_MATCHES_DIRENT64)
/* 64-bit variant of `kreaddirf()' */
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_kreaddirf64,(__fd_t __fd, struct dirent64 *__buf, __SIZE_TYPE__ __bufsize, unsigned int __mode, __oflag_t __flags),kreaddirf,(__fd,__buf,__bufsize,__mode,__flags))
#else /* LIBC: kreaddirf64 */
#undef ____localdep_kreaddirf64_defined
#endif /* kreaddirf64... */
#endif /* !____localdep_kreaddirf64_defined */

__NAMESPACE_LOCAL_BEGIN
/* 64-bit variant of `kreaddir()' */
__LOCAL_LIBC(kreaddir64) __ATTR_WUNUSED __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(kreaddir64))(__fd_t __fd,
                                                        struct dirent64 *__buf,
                                                        __SIZE_TYPE__ __bufsize,
                                                        unsigned int __mode) {
#line 345 "kos/src/libc/magic/dirent.c"
	return __localdep_kreaddirf64(__fd, __buf, __bufsize, __mode, 0);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_kreaddirf64 || (__CRT_HAVE_kreaddirf && _DIRENT_MATCHES_DIRENT64) */
#endif /* !__local_kreaddir64_defined */
