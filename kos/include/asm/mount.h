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
#ifndef _ASM_MOUNT_H
#define _ASM_MOUNT_H 1

#include <__crt.h>
#include <__stdinc.h>

#if defined(__KOS__) || defined(__linux__)
#define __BLOCK_SIZE      1024 /* ... */
#define __BLOCK_SIZE_BITS 10   /* ... */

#define __MS_RDONLY      0x00000001 /* Mount read-only. */
#define __MS_NOSUID      0x00000002 /* Ignore suid and sgid bits. */
#define __MS_NODEV       0x00000004 /* Disallow access to device special files. */
#define __MS_NOEXEC      0x00000008 /* Disallow program execution. */
#define __MS_SYNCHRONOUS 0x00000010 /* Writes are synced at once. */
#define __MS_REMOUNT     0x00000020 /* Alter flags of a mounted FS. */
#define __MS_MANDLOCK    0x00000040 /* Allow mandatory locks on an FS. */
#define __MS_DIRSYNC     0x00000080 /* Directory modifications are synchronous. */
#define __MS_NOATIME     0x00000400 /* Do not update access times. */
#define __MS_NODIRATIME  0x00000800 /* Do not update directory access times. */
#define __MS_BIND        0x00001000 /* Bind directory at different place. */
#define __MS_MOVE        0x00002000 /* ... */
#define __MS_REC         0x00004000 /* ... */
#define __MS_SILENT      0x00008000 /* ... */
#define __MS_POSIXACL    0x00010000 /* VFS does not apply the umask. */
#define __MS_UNBINDABLE  0x00020000 /* Change to unbindable. */
#define __MS_PRIVATE     0x00040000 /* Change to private. */
#define __MS_SLAVE       0x00080000 /* Change to slave. */
#define __MS_SHARED      0x00100000 /* Change to shared. */
#define __MS_RELATIME    0x00200000 /* Update atime relative to mtime/ctime. */
#define __MS_KERNMOUNT   0x00400000 /* This is a kern_mount call. */
#define __MS_I_VERSION   0x00800000 /* Update inode I_version field. */
#define __MS_STRICTATIME 0x01000000 /* Always perform atime updates. */
#define __MS_LAZYTIME    0x02000000 /* Update the on-disk [acm]times lazily. */
#define __MS_ACTIVE      0x40000000 /* ... */
#define __MS_NOUSER      0x80000000 /* ... */

/* Flags that can be altered by MS_REMOUNT  */
#define __MS_RMT_MASK (__MS_RDONLY | __MS_SYNCHRONOUS | __MS_MANDLOCK | __MS_I_VERSION | __MS_LAZYTIME)

/* Magic mount flag number. Has to be or-ed to the flag values. */
#define __MS_MGC_VAL 0xc0ed0000 /* Magic flag number to indicate "new" flags. */
#define __MS_MGC_MSK 0xffff0000 /* Magic flag number mask. */

#define __MNT_FORCE       0x0001 /* Force unmounting. */
#define __MNT_DETACH      0x0002 /* Just detach from the tree. */
#define __MNT_EXPIRE      0x0004 /* Mark for expiry. */
#define __UMOUNT_NOFOLLOW 0x0008 /* Don't follow symlink on umount. */

#endif /* __KOS__ || __linux__ */

#endif /* !_ASM_MOUNT_H */
