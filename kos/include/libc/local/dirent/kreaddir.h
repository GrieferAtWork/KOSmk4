/* HASH CRC-32:0xa65cdb97 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_kreaddir_defined
#define __local_kreaddir_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_kreaddirf) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))) || (defined(__CRT_HAVE_kreaddirf64) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)))
#include <bits/os/dirent.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_kreaddirf_defined
#define __local___localdep_kreaddirf_defined 1
#if defined(__CRT_HAVE_kreaddirf) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_kreaddirf,(__fd_t __fd, struct dirent *__buf, __SIZE_TYPE__ __bufsize, unsigned int __mode, __oflag_t __flags),kreaddirf,(__fd,__buf,__bufsize,__mode,__flags))
#elif defined(__CRT_HAVE_kreaddirf64) && (defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))
__CREDIRECT(__ATTR_WUNUSED,__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_kreaddirf,(__fd_t __fd, struct dirent *__buf, __SIZE_TYPE__ __bufsize, unsigned int __mode, __oflag_t __flags),kreaddirf64,(__fd,__buf,__bufsize,__mode,__flags))
#else /* ... */
#undef __local___localdep_kreaddirf_defined
#endif /* !... */
#endif /* !__local___localdep_kreaddirf_defined */
__LOCAL_LIBC(kreaddir) __ATTR_WUNUSED __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(kreaddir))(__fd_t __fd, struct dirent *__buf, __SIZE_TYPE__ __bufsize, unsigned int __mode) {
	return __NAMESPACE_LOCAL_SYM __localdep_kreaddirf(__fd, __buf, __bufsize, __mode, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_kreaddir_defined
#define __local___localdep_kreaddir_defined 1
#define __localdep_kreaddir __LIBC_LOCAL_NAME(kreaddir)
#endif /* !__local___localdep_kreaddir_defined */
#else /* (__CRT_HAVE_kreaddirf && (!__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64)) || (__CRT_HAVE_kreaddirf64 && (__USE_FILE_OFFSET64 || _DIRENT_MATCHES_DIRENT64)) */
#undef __local_kreaddir_defined
#endif /* (!__CRT_HAVE_kreaddirf || (__USE_FILE_OFFSET64 && !_DIRENT_MATCHES_DIRENT64)) && (!__CRT_HAVE_kreaddirf64 || (!__USE_FILE_OFFSET64 && !_DIRENT_MATCHES_DIRENT64)) */
#endif /* !__local_kreaddir_defined */
