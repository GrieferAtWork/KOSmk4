/* HASH CRC-32:0x7a955335 */
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
#ifndef _SYS_STATFS_H
#define _SYS_STATFS_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <sys/types.h>
#include <bits/statfs.h>

__SYSDECL_BEGIN

/* Documentation (partially) derived from Glibc /usr/include/i386-linux-gnu/sys/statfs.h */
/* Definitions for getting information about a filesystem.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
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


#ifdef __CC__

#if defined(__CRT_HAVE_statfs) && !defined(__USE_FILE_OFFSET64)
/* Return information about the filesystem on which FILE resides */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,statfs,(char const *__file, struct statfs *__buf),(__file,__buf))
#elif defined(__CRT_HAVE___statfs) && !defined(__USE_FILE_OFFSET64)
/* Return information about the filesystem on which FILE resides */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,statfs,(char const *__file, struct statfs *__buf),__statfs,(__file,__buf))
#elif defined(__CRT_HAVE_statfs64) && defined(__USE_FILE_OFFSET64)
/* Return information about the filesystem on which FILE resides */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,statfs,(char const *__file, struct statfs *__buf),statfs64,(__file,__buf))
#endif /* ... */
#if defined(__CRT_HAVE_fstatfs) && !defined(__USE_FILE_OFFSET64)
/* Return information about the filesystem containing the file FILDES refers to */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstatfs,(__fd_t __filedes, struct statfs *__buf),(__filedes,__buf))
#elif defined(__CRT_HAVE_fstatfs64) && defined(__USE_FILE_OFFSET64)
/* Return information about the filesystem containing the file FILDES refers to */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstatfs,(__fd_t __filedes, struct statfs *__buf),fstatfs64,(__filedes,__buf))
#endif /* ... */

#ifdef __USE_LARGEFILE64
#ifndef statfs64
#ifdef __CRT_HAVE_statfs64
/* Return information about the filesystem on which FILE resides */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,statfs64,(const char *__file, struct statfs64 *__buf),(__file,__buf))
#elif defined(__CRT_HAVE_statfs) && defined(_STATFS_MATCHES_STATFS64)
/* Return information about the filesystem on which FILE resides */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,statfs64,(const char *__file, struct statfs64 *__buf),statfs,(__file,__buf))
#endif /* ... */
#endif /* !statfs64 */
#ifdef __CRT_HAVE_fstatfs64
/* Return information about the filesystem containing the file FILDES refers to */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstatfs64,(__fd_t __filedes, struct statfs64 *__buf),(__filedes,__buf))
#elif defined(__CRT_HAVE_fstatfs) && defined(_STATFS_MATCHES_STATFS64)
/* Return information about the filesystem containing the file FILDES refers to */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstatfs64,(__fd_t __filedes, struct statfs64 *__buf),fstatfs,(__filedes,__buf))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_STATFS_H */
