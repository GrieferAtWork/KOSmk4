/* HASH CRC-32:0x7eb4c33c */
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
#ifndef _SYS_MOUNT_H
#define _SYS_MOUNT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/ioctls/block.h> /* BLK* (ioctls) */
#include <asm/mount.h>

__SYSDECL_BEGIN

/* Header file for mounting/unmount Linux filesystems.
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

#ifdef __BLOCK_SIZE
#define BLOCK_SIZE __BLOCK_SIZE /* ... */
#endif /* __BLOCK_SIZE */
#ifdef __BLOCK_SIZE_BITS
#define BLOCK_SIZE_BITS __BLOCK_SIZE_BITS /* ... */
#endif /* __BLOCK_SIZE_BITS */

#ifdef __MS_RDONLY
#define MS_RDONLY __MS_RDONLY /* Mount read-only. */
#endif /* __MS_RDONLY */
#ifdef __MS_NOSUID
#define MS_NOSUID __MS_NOSUID /* Ignore suid and sgid bits. */
#endif /* __MS_NOSUID */
#ifdef __MS_NODEV
#define MS_NODEV __MS_NODEV /* Disallow access to device special files. */
#endif /* __MS_NODEV */
#ifdef __MS_NOEXEC
#define MS_NOEXEC __MS_NOEXEC /* Disallow program execution. */
#endif /* __MS_NOEXEC */
#ifdef __MS_SYNCHRONOUS
#define MS_SYNCHRONOUS __MS_SYNCHRONOUS /* Writes are synced at once. */
#endif /* __MS_SYNCHRONOUS */
#ifdef __MS_REMOUNT
#define MS_REMOUNT __MS_REMOUNT /* Alter flags of a mounted FS. */
#endif /* __MS_REMOUNT */
#ifdef __MS_MANDLOCK
#define MS_MANDLOCK __MS_MANDLOCK /* Allow mandatory locks on an FS. */
#endif /* __MS_MANDLOCK */
#ifdef __MS_DIRSYNC
#define MS_DIRSYNC __MS_DIRSYNC /* Directory modifications are synchronous. */
#endif /* __MS_DIRSYNC */
#ifdef __MS_NOATIME
#define MS_NOATIME __MS_NOATIME /* Do not update access times. */
#endif /* __MS_NOATIME */
#ifdef __MS_NODIRATIME
#define MS_NODIRATIME __MS_NODIRATIME /* Do not update directory access times. */
#endif /* __MS_NODIRATIME */
#ifdef __MS_BIND
#define MS_BIND __MS_BIND /* Bind directory at different place. */
#endif /* __MS_BIND */
#ifdef __MS_MOVE
#define MS_MOVE __MS_MOVE /* ... */
#endif /* __MS_MOVE */
#ifdef __MS_REC
#define MS_REC __MS_REC /* ... */
#endif /* __MS_REC */
#ifdef __MS_SILENT
#define MS_SILENT __MS_SILENT /* ... */
#endif /* __MS_SILENT */

#ifdef __MS_POSIXACL
#define MS_POSIXACL __MS_POSIXACL /* VFS does not apply the umask. */
#endif /* __MS_POSIXACL */
#ifdef __MS_UNBINDABLE
#define MS_UNBINDABLE __MS_UNBINDABLE /* Change to unbindable. */
#endif /* __MS_UNBINDABLE */
#ifdef __MS_PRIVATE
#define MS_PRIVATE __MS_PRIVATE /* Change to private. */
#endif /* __MS_PRIVATE */
#ifdef __MS_SLAVE
#define MS_SLAVE __MS_SLAVE /* Change to slave. */
#endif /* __MS_SLAVE */
#ifdef __MS_SHARED
#define MS_SHARED __MS_SHARED /* Change to shared. */
#endif /* __MS_SHARED */
#ifdef __MS_RELATIME
#define MS_RELATIME __MS_RELATIME /* Update atime relative to mtime/ctime. */
#endif /* __MS_RELATIME */
#ifdef __MS_KERNMOUNT
#define MS_KERNMOUNT __MS_KERNMOUNT /* This is a kern_mount call. */
#endif /* __MS_KERNMOUNT */
#ifdef __MS_I_VERSION
#define MS_I_VERSION __MS_I_VERSION /* Update inode I_version field. */
#endif /* __MS_I_VERSION */
#ifdef __MS_STRICTATIME
#define MS_STRICTATIME __MS_STRICTATIME /* Always perform atime updates. */
#endif /* __MS_STRICTATIME */
#ifdef __MS_LAZYTIME
#define MS_LAZYTIME __MS_LAZYTIME /* Update the on-disk [acm]times lazily. */
#endif /* __MS_LAZYTIME */
#ifdef __MS_ACTIVE
#define MS_ACTIVE __MS_ACTIVE
#endif /* __MS_ACTIVE */
#ifdef __MS_NOUSER
#define MS_NOUSER __MS_NOUSER
#endif /* __MS_NOUSER */

/* Flags that can be altered by MS_REMOUNT  */
#ifdef __MS_RMT_MASK
#define MS_RMT_MASK __MS_RMT_MASK
#endif /* __MS_RMT_MASK */

/* Magic mount flag number. Has to be or-ed to the flag values. */
#ifdef __MS_MGC_VAL
#define MS_MGC_VAL __MS_MGC_VAL /* Magic flag number to indicate "new" flags. */
#endif /* __MS_MGC_VAL */
#ifdef __MS_MGC_MSK
#define MS_MGC_MSK __MS_MGC_MSK /* Magic flag number mask. */
#endif /* __MS_MGC_MSK */

/* Possible value for FLAGS parameter of `umount2'. */
#ifdef __MNT_FORCE
#define MNT_FORCE __MNT_FORCE /* Force unmounting. */
#endif /* __MNT_FORCE */
#ifdef __MNT_DETACH
#define MNT_DETACH __MNT_DETACH /* Just detach from the tree. */
#endif /* __MNT_DETACH */
#ifdef __MNT_EXPIRE
#define MNT_EXPIRE __MNT_EXPIRE /* Mark for expiry. */
#endif /* __MNT_EXPIRE */
#ifdef __UMOUNT_NOFOLLOW
#define UMOUNT_NOFOLLOW __UMOUNT_NOFOLLOW /* Don't follow symlink on umount. */
#endif /* __UMOUNT_NOFOLLOW */

#ifdef __CC__
__CDECLARE_OPT(,int,__NOTHROW_RPC,mount,(char const *__special_file, char const *__dir, char const *__fstype, __ULONGPTR_TYPE__ __mountflags, void const *__data),(__special_file,__dir,__fstype,__mountflags,__data))
#ifdef __CRT_HAVE_umount
__CDECLARE(,int,__NOTHROW_RPC,umount,(char const *__special_file),(__special_file))
#elif defined(__CRT_HAVE_umount2)
#include <libc/local/sys.mount/umount.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(umount, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL umount)(char const *__special_file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(umount))(__special_file); })
#endif /* ... */
__CDECLARE_OPT(,int,__NOTHROW_RPC,umount2,(char const *__special_file, __STDC_INT_AS_UINT_T __flags),(__special_file,__flags))
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_MOUNT_H */
