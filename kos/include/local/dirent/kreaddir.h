/* HASH CRC-32:0xb800274f */
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
#ifndef __local_kreaddir_defined
#if defined(__CRT_HAVE_kreaddirf) || (defined(__CRT_HAVE_kreaddirf64) && defined(_DIRENT_MATCHES_DIRENT64))
#define __local_kreaddir_defined 1
/* Dependency: "kreaddirf" */
#ifndef ____localdep_kreaddirf_defined
#define ____localdep_kreaddirf_defined 1
#ifdef __CRT_HAVE_kreaddirf
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_kreaddirf,(__fd_t __fd, struct dirent *__buf, __SIZE_TYPE__ __bufsize, unsigned int __mode, __oflag_t __flags),kreaddirf,(__fd,__buf,__bufsize,__mode,__flags))
#elif defined(__CRT_HAVE_kreaddirf64) && defined(_DIRENT_MATCHES_DIRENT64)
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_kreaddirf,(__fd_t __fd, struct dirent *__buf, __SIZE_TYPE__ __bufsize, unsigned int __mode, __oflag_t __flags),kreaddirf64,(__fd,__buf,__bufsize,__mode,__flags))
#else /* LIBC: kreaddirf */
#undef ____localdep_kreaddirf_defined
#endif /* kreaddirf... */
#endif /* !____localdep_kreaddirf_defined */

__NAMESPACE_LOCAL_BEGIN
/* The KOS-specific system call for reading a single directory entry
 * from a file descriptor referring to an open directory stream.
 * @param: MODE: One of `READDIR_*' (See below)
 * @return: * : The actually required buffer size for the directory entry (in bytes)
 *              NOTE: When `READDIR_DEFAULT' was passed for `MODE', the directory
 *                    stream will only be advanced when this value is >= 'BUFSIZE'
 * @return: 0 : The end of the directory has been reached.
 * @return: -1: Failed to read a directory entry for some reason (s.a.: `errno') */
__LOCAL_LIBC(kreaddir) __ATTR_WUNUSED __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(kreaddir))(__fd_t __fd,
                                                      struct dirent *__buf,
                                                      __SIZE_TYPE__ __bufsize,
                                                      unsigned int __mode) {
#line 345 "kos/src/libc/magic/dirent.c"
	return __localdep_kreaddirf(__fd, __buf, __bufsize, __mode, 0);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_kreaddirf || (__CRT_HAVE_kreaddirf64 && _DIRENT_MATCHES_DIRENT64) */
#endif /* !__local_kreaddir_defined */
