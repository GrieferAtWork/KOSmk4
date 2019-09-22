/* HASH CRC-32:0x6c9ac0af */
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
#ifndef _SYS_MOUNT_H
#define _SYS_MOUNT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <sys/ioctl.h>

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

#ifndef BLOCK_SIZE
#define BLOCK_SIZE      1024
#endif /* !BLOCK_SIZE */
#ifndef BLOCK_SIZE_BITS
#define BLOCK_SIZE_BITS 10
#endif /* !BLOCK_SIZE_BITS */

#ifndef MS_RDONLY
#define MS_RDONLY      0x00000001 /* Mount read-only. */
#endif /* !MS_RDONLY */
#ifndef MS_NOSUID
#define MS_NOSUID      0x00000002 /* Ignore suid and sgid bits. */
#endif /* !MS_NOSUID */
#ifndef MS_NODEV
#define MS_NODEV       0x00000004 /* Disallow access to device special files. */
#endif /* !MS_NODEV */
#ifndef MS_NOEXEC
#define MS_NOEXEC      0x00000008 /* Disallow program execution. */
#endif /* !MS_NOEXEC */
#ifndef MS_SYNCHRONOUS
#define MS_SYNCHRONOUS 0x00000010 /* Writes are synced at once. */
#endif /* !MS_SYNCHRONOUS */
#ifndef MS_REMOUNT
#define MS_REMOUNT     0x00000020 /* Alter flags of a mounted FS. */
#endif /* !MS_REMOUNT */
#ifndef MS_MANDLOCK
#define MS_MANDLOCK    0x00000040 /* Allow mandatory locks on an FS. */
#endif /* !MS_MANDLOCK */
#ifndef MS_DIRSYNC
#define MS_DIRSYNC     0x00000080 /* Directory modifications are synchronous. */
#endif /* !MS_DIRSYNC */
#ifndef MS_NOATIME
#define MS_NOATIME     0x00000400 /* Do not update access times. */
#endif /* !MS_NOATIME */
#ifndef MS_NODIRATIME
#define MS_NODIRATIME  0x00000800 /* Do not update directory access times. */
#endif /* !MS_NODIRATIME */
#ifndef MS_BIND
#define MS_BIND        0x00001000 /* Bind directory at different place. */
#endif /* !MS_BIND */
#ifndef MS_MOVE
#define MS_MOVE        0x00002000
#endif /* !MS_MOVE */
#ifndef MS_REC
#define MS_REC         0x00004000
#endif /* !MS_REC */
#ifndef MS_SILENT
#define MS_SILENT      0x00008000
#endif /* !MS_SILENT */

#ifndef MS_POSIXACL
#define MS_POSIXACL    0x00010000 /* VFS does not apply the umask. */
#endif /* !MS_POSIXACL */
#ifndef MS_UNBINDABLE
#define MS_UNBINDABLE  0x00020000 /* Change to unbindable. */
#endif /* !MS_UNBINDABLE */
#ifndef MS_PRIVATE
#define MS_PRIVATE     0x00040000 /* Change to private. */
#endif /* !MS_PRIVATE */
#ifndef MS_SLAVE
#define MS_SLAVE       0x00080000 /* Change to slave. */
#endif /* !MS_SLAVE */
#ifndef MS_SHARED
#define MS_SHARED      0x00100000 /* Change to shared. */
#endif /* !MS_SHARED */
#ifndef MS_RELATIME
#define MS_RELATIME    0x00200000 /* Update atime relative to mtime/ctime. */
#endif /* !MS_RELATIME */
#ifndef MS_KERNMOUNT
#define MS_KERNMOUNT   0x00400000 /* This is a kern_mount call. */
#endif /* !MS_KERNMOUNT */
#ifndef MS_I_VERSION
#define MS_I_VERSION   0x00800000 /* Update inode I_version field. */
#endif /* !MS_I_VERSION */
#ifndef MS_STRICTATIME
#define MS_STRICTATIME 0x01000000 /* Always perform atime updates. */
#endif /* !MS_STRICTATIME */
#ifndef MS_LAZYTIME
#define MS_LAZYTIME    0x02000000 /* Update the on-disk [acm]times lazily. */
#endif /* !MS_LAZYTIME */
#ifndef MS_ACTIVE
#define MS_ACTIVE      0x40000000
#endif /* !MS_ACTIVE */
#ifndef MS_NOUSER
#define MS_NOUSER      0x80000000
#endif /* !MS_NOUSER */

/* Flags that can be altered by MS_REMOUNT  */
#ifndef MS_RMT_MASK
#define MS_RMT_MASK   (MS_RDONLY|MS_SYNCHRONOUS|MS_MANDLOCK|MS_I_VERSION|MS_LAZYTIME)
#endif /* !MS_RMT_MASK */

/* Magic mount flag number. Has to be or-ed to the flag values. */
#ifndef MS_MGC_VAL
#define MS_MGC_VAL     0xc0ed0000 /* Magic flag number to indicate "new" flags. */
#endif /* !MS_MGC_VAL */
#ifndef MS_MGC_MSK
#define MS_MGC_MSK     0xffff0000 /* Magic flag number mask. */
#endif /* !MS_MGC_MSK */

/* The read-only stuff doesn't really belong here, but any other place
 * is probably as bad and I don't want to create yet another include file. */
#ifndef BLKROSET
#define BLKROSET     _IO(0x12, 93)  /* [int const *arg] Set device read-only (0 = read-write). */
#endif /* !BLKROSET */
#ifndef BLKROGET
#define BLKROGET     _IO(0x12, 94)  /* [int *arg] Get read-only status (0 = read_write). */
#endif /* !BLKROGET */
#ifndef BLKRRPART
#define BLKRRPART    _IO(0x12, 95)  /* Re-read partition table. */
#endif /* !BLKRRPART */
#ifndef BLKGETSIZE
#define BLKGETSIZE   _IO(0x12, 96)  /* Return device size. (unsigned long *arg) */
#endif /* !BLKGETSIZE */
#ifndef BLKFLSBUF
#define BLKFLSBUF    _IO(0x12, 97)  /* Flush buffer cache. */
#endif /* !BLKFLSBUF */
#ifndef BLKRASET
#define BLKRASET     _IO(0x12, 98)  /* [unsigned long const *arg] Set read ahead for block device. */
#endif /* !BLKRASET */
#ifndef BLKRAGET
#define BLKRAGET     _IO(0x12, 99)  /* [unsigned long *arg] Get current read ahead setting. */
#endif /* !BLKRAGET */
#ifndef BLKFRASET
#define BLKFRASET    _IO(0x12, 100) /* [unsigned long const *arg] Set filesystem read-ahead. */
#endif /* !BLKFRASET */
#ifndef BLKFRAGET
#define BLKFRAGET    _IO(0x12, 101) /* [unsigned long *arg] Get filesystem read-ahead. */
#endif /* !BLKFRAGET */
#ifndef BLKSECTSET
#define BLKSECTSET   _IO(0x12, 102) /* [u16 const *arg] Set max sectors per request. */
#endif /* !BLKSECTSET */
#ifndef BLKSECTGET
#define BLKSECTGET   _IO(0x12, 103) /* [u16 *arg] Get max sectors per request. */
#endif /* !BLKSECTGET */
#ifndef BLKSSZGET
#define BLKSSZGET    _IO(0x12, 104) /* [unsigned int *arg] Get block device sector size. */
#endif /* !BLKSSZGET */
#ifndef BLKBSZGET
#define BLKBSZGET    _IOR(0x12, 112, size_t) /* [size_t *arg] */
#endif /* !BLKBSZGET */
#ifndef BLKBSZSET
#define BLKBSZSET    _IOW(0x12, 113, size_t) /* [size_t *arg] */
#endif /* !BLKBSZSET */
#ifndef BLKGETSIZE64
#define BLKGETSIZE64 _IOR(0x12, 114, size_t) /* [u64 *arg] Return device size. */
#endif /* !BLKGETSIZE64 */

/* Possible value for FLAGS parameter of `umount2'. */
#ifndef MNT_FORCE
#define MNT_FORCE       1 /* Force unmounting. */
#endif /* !MNT_FORCE */
#ifndef MNT_DETACH
#define MNT_DETACH      2 /* Just detach from the tree. */
#endif /* !MNT_DETACH */
#ifndef MNT_EXPIRE
#define MNT_EXPIRE      4 /* Mark for expiry. */
#endif /* !MNT_EXPIRE */

#ifndef UMOUNT_NOFOLLOW
#define UMOUNT_NOFOLLOW 8 /* Don't follow symlink on umount. */
#endif /* !UMOUNT_NOFOLLOW */

#ifdef __CC__
#if defined(__CRT_HAVE_mount)
__CDECLARE(,int,__NOTHROW_RPC,mount,(char const *__special_file, char const *__dir, char const *__fstype, unsigned long int __rwflag, void const *__data),(__special_file,__dir,__fstype,__rwflag,__data))
#endif /* mount... */
#if defined(__CRT_HAVE_umount)
__CDECLARE(,int,__NOTHROW_RPC,umount,(char const *__special_file),(__special_file))
#elif defined(__CRT_HAVE_umount2)
#include <local/sys.mount/umount.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(umount, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL umount)(char const *__special_file) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(umount))(__special_file); })
#endif /* umount... */
#if defined(__CRT_HAVE_umount2)
__CDECLARE(,int,__NOTHROW_RPC,umount2,(char const *__special_file, int __flags),(__special_file,__flags))
#endif /* umount2... */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_MOUNT_H */
