/* HASH CRC-32:0xcf1cdb1d */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_mknod_defined
#define __local_mknod_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && defined(__AT_FDCWD)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mknodat_defined
#define __local___localdep_mknodat_defined
#ifdef __CRT_HAVE_mknodat
__CREDIRECT(__ATTR_IN(2),int,__NOTHROW_RPC,__localdep_mknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev),mknodat,(__dirfd,__nodename,__mode,__dev))
#elif defined(__CRT_HAVE_fmknodat)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/mknodat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mknodat __LIBC_LOCAL_NAME(mknodat)
#else /* ... */
#undef __local___localdep_mknodat_defined
#endif /* !... */
#endif /* !__local___localdep_mknodat_defined */
__LOCAL_LIBC(mknod) __ATTR_IN(1) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(mknod))(char const *__nodename, __mode_t __mode, __dev_t __dev) {
	return (__NAMESPACE_LOCAL_SYM __localdep_mknodat)(__AT_FDCWD, __nodename, __mode, __dev);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mknod_defined
#define __local___localdep_mknod_defined
#define __localdep_mknod __LIBC_LOCAL_NAME(mknod)
#endif /* !__local___localdep_mknod_defined */
#else /* (__CRT_HAVE_mknodat || __CRT_HAVE_fmknodat) && __AT_FDCWD */
#undef __local_mknod_defined
#endif /* (!__CRT_HAVE_mknodat && !__CRT_HAVE_fmknodat) || !__AT_FDCWD */
#endif /* !__local_mknod_defined */
