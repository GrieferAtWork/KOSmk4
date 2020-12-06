/* HASH CRC-32:0xf293497f */
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
#include <sys/types.h>

/* Documentation taken from GLibc /usr/include/i386-linux-gnu/sys/sendfile.h */
/* sendfile -- copy data directly from one file descriptor to another
   Copyright (C) 1998-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__CRT_HAVE_sendfile64) && defined(__USE_FILE_OFFSET64)
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
__CREDIRECT(,ssize_t,__NOTHROW_NCX,sendfile,(__fd_t __out_fd, __fd_t __in_fd, off_t *__offset, size_t __count),sendfile64,(__out_fd,__in_fd,__offset,__count))
#elif defined(__CRT_HAVE_sendfile) && !defined(__USE_FILE_OFFSET64)
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
__CDECLARE(,ssize_t,__NOTHROW_NCX,sendfile,(__fd_t __out_fd, __fd_t __in_fd, off_t *__offset, size_t __count),(__out_fd,__in_fd,__offset,__count))
#elif defined(__CRT_HAVE_sendfile64) || defined(__CRT_HAVE_sendfile)
#include <libc/local/sys.sendfile/sendfile.h>
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
__NAMESPACE_LOCAL_USING_OR_IMPL(sendfile, __FORCELOCAL __ATTR_ARTIFICIAL ssize_t __NOTHROW_NCX(__LIBCCALL sendfile)(__fd_t __out_fd, __fd_t __in_fd, off_t *__offset, size_t __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sendfile))(__out_fd, __in_fd, __offset, __count); })
#endif /* ... */
#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_sendfile64
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
__CDECLARE(,ssize_t,__NOTHROW_NCX,sendfile64,(__fd_t __out_fd, __fd_t __in_fd, __off64_t *__offset, size_t __count),(__out_fd,__in_fd,__offset,__count))
#elif defined(__CRT_HAVE_sendfile) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
__CREDIRECT(,ssize_t,__NOTHROW_NCX,sendfile64,(__fd_t __out_fd, __fd_t __in_fd, __off64_t *__offset, size_t __count),sendfile,(__out_fd,__in_fd,__offset,__count))
#elif defined(__CRT_HAVE_sendfile)
#include <libc/local/sys.sendfile/sendfile64.h>
/* Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
 * to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
 * read bytes. If OFFSET is a null pointer, use the normal file position instead.
 * Return the number of written bytes, or -1 in case of error */
__NAMESPACE_LOCAL_USING_OR_IMPL(sendfile64, __FORCELOCAL __ATTR_ARTIFICIAL ssize_t __NOTHROW_NCX(__LIBCCALL sendfile64)(__fd_t __out_fd, __fd_t __in_fd, __off64_t *__offset, size_t __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sendfile64))(__out_fd, __in_fd, __offset, __count); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_SENDFILE_H */
