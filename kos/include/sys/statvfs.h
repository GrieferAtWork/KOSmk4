/* HASH 0xa199346 */
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
#ifndef _SYS_STATVFS_H
#define _SYS_STATVFS_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/statvfs.h>

__SYSDECL_BEGIN

/* Documentation (partially) derived from Glibc /usr/include/i386-linux-gnu/sys/statvfs.h */
/* Definitions for getting information about a filesystem.
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


#ifdef __CC__

#ifndef __fsblkcnt_t_defined
#define __fsblkcnt_t_defined 1
typedef __FS_TYPE(fsblkcnt) fsblkcnt_t; /* Type to count file system blocks.  */
#endif /* !__fsblkcnt_t_defined */
#ifndef __fsfilcnt_t_defined
#define __fsfilcnt_t_defined 1
typedef __FS_TYPE(fsfilcnt) fsfilcnt_t; /* Type to count file system inodes.  */
#endif /* !__fsfilcnt_t_defined */

#if defined(__CRT_HAVE_statvfs) && (!defined(__USE_FILE_OFFSET64))
/* Return information about the filesystem on which FILE resides */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,statvfs,(char const *__file, struct statvfs *__buf),(__file,__buf))
#elif defined(__CRT_HAVE_statvfs64) && (defined(__USE_FILE_OFFSET64))
/* Return information about the filesystem on which FILE resides */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,statvfs,(char const *__file, struct statvfs *__buf),statvfs64,(__file,__buf))
#endif /* statvfs... */
#if defined(__CRT_HAVE_fstatvfs) && (!defined(__USE_FILE_OFFSET64))
/* Return information about the filesystem containing the file FILDES refers to */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstatvfs,(__fd_t __filedes, struct statvfs *__buf),(__filedes,__buf))
#elif defined(__CRT_HAVE_fstatvfs64) && (defined(__USE_FILE_OFFSET64))
/* Return information about the filesystem containing the file FILDES refers to */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstatvfs,(__fd_t __filedes, struct statvfs *__buf),fstatvfs64,(__filedes,__buf))
#endif /* fstatvfs... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_statvfs64)
/* Return information about the filesystem on which FILE resides */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,statvfs64,(const char *__file, struct statvfs64 *__buf),(__file,__buf))
#elif defined(__CRT_HAVE_statvfs) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* Return information about the filesystem on which FILE resides */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,statvfs64,(const char *__file, struct statvfs64 *__buf),statvfs,(__file,__buf))
#endif /* statvfs64... */
#if defined(__CRT_HAVE_fstatvfs64)
/* Return information about the filesystem containing the file FILDES refers to */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstatvfs64,(__fd_t __filedes, struct statvfs64 *__buf),(__filedes,__buf))
#elif defined(__CRT_HAVE_fstatvfs) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* Return information about the filesystem containing the file FILDES refers to */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstatvfs64,(__fd_t __filedes, struct statvfs64 *__buf),fstatvfs,(__filedes,__buf))
#endif /* fstatvfs64... */
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_STATVFS_H */
