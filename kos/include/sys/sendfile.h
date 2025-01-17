/* HASH CRC-32:0xa0434c94 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: GNU C Library (/io/sys/sendfile.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/sendfile.h) */
/* (#) Portability: diet libc     (/include/sys/sendfile.h) */
/* (#) Portability: musl libc     (/include/sys/sendfile.h) */
/* (#) Portability: uClibc        (/include/sys/sendfile.h) */
#ifndef _SYS_SENDFILE_H
#define _SYS_SENDFILE_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <hybrid/typecore.h>

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#if defined(__CRT_HAVE_sendfile) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CDECLARE(__ATTR_FDREAD(2) __ATTR_FDWRITE(1) __ATTR_INOUT_OPT(3),ssize_t,__NOTHROW_NCX,sendfile,(__fd_t __out_fd, __fd_t __in_fd, __off_t *__offset, size_t __count),(__out_fd,__in_fd,__offset,__count))
#elif defined(__CRT_HAVE_sendfile64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDREAD(2) __ATTR_FDWRITE(1) __ATTR_INOUT_OPT(3),ssize_t,__NOTHROW_NCX,sendfile,(__fd_t __out_fd, __fd_t __in_fd, __off_t *__offset, size_t __count),sendfile64,(__out_fd,__in_fd,__offset,__count))
#elif defined(__CRT_HAVE_sendfile64) || defined(__CRT_HAVE_sendfile)
#include <libc/local/sys.sendfile/sendfile.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sendfile, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(2) __ATTR_FDWRITE(1) __ATTR_INOUT_OPT(3) ssize_t __NOTHROW_NCX(__LIBCCALL sendfile)(__fd_t __out_fd, __fd_t __in_fd, __off_t *__offset, size_t __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sendfile))(__out_fd, __in_fd, __offset, __count); })
#endif /* ... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_sendfile) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDREAD(2) __ATTR_FDWRITE(1) __ATTR_INOUT_OPT(3),ssize_t,__NOTHROW_NCX,sendfile64,(__fd_t __out_fd, __fd_t __in_fd, __off64_t *__offset, size_t __count),sendfile,(__out_fd,__in_fd,__offset,__count))
#elif defined(__CRT_HAVE_sendfile64)
__CDECLARE(__ATTR_FDREAD(2) __ATTR_FDWRITE(1) __ATTR_INOUT_OPT(3),ssize_t,__NOTHROW_NCX,sendfile64,(__fd_t __out_fd, __fd_t __in_fd, __off64_t *__offset, size_t __count),(__out_fd,__in_fd,__offset,__count))
#elif defined(__CRT_HAVE_sendfile)
#include <libc/local/sys.sendfile/sendfile64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sendfile64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDREAD(2) __ATTR_FDWRITE(1) __ATTR_INOUT_OPT(3) ssize_t __NOTHROW_NCX(__LIBCCALL sendfile64)(__fd_t __out_fd, __fd_t __in_fd, __off64_t *__offset, size_t __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sendfile64))(__out_fd, __in_fd, __offset, __count); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_SENDFILE_H */
