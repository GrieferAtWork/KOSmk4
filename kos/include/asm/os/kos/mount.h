/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_KOS_MOUNT_H
#define _ASM_OS_KOS_MOUNT_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __BLOCK_SIZE      1024 /* ... */
#define __BLOCK_SIZE_BITS 10   /* ... */

#define __MS_RDONLY      0x00000001 /* Disallow `write(2)',  as  well  as  `PROT_WRITE | PROT_SHARED'  mappings.
                                     * Attempting to do either will result in `E_FSERROR_READONLY' being thrown. */
#define __MS_NOSUID      0x00000002 /* Ignore `S_ISGID' and `S_ISUID' bits */
#define __MS_NODEV       0x00000004 /* ??? */
#define __MS_NOEXEC      0x00000008 /* Disallow execution of files. */
#define __MS_SYNCHRONOUS 0x00000010 /* ??? */
#define __MS_REMOUNT     0x00000020 /* ACTION: Modify mounting point flags */
#define __MS_MANDLOCK    0x00000040 /* ??? */
#define __MS_DIRSYNC     0x00000080 /* ??? */
#define __MS_NOATIME     0x00000400 /* Don't modify the value of `ATIME' (implies `MS_NODIRATIME') */
#define __MS_NODIRATIME  0x00000800 /* Don't update `ATIME' during path traversal */
#define __MS_BIND        0x00001000 /* ACTION: Bind fdirnode at `source' to `target' (MS_REMOUNT: override mounting point at target) */
#define __MS_MOVE        0x00002000 /* ACTION: Move a mounting point from `source' to `target' (MS_REMOUNT: override mounting point at target) */
#define __MS_REC         0x00004000 /* ??? */
#define __MS_SILENT      0x00008000 /* ??? */
#define __MS_POSIXACL    0x00010000 /* ??? */
#define __MS_UNBINDABLE  0x00020000 /* ??? */
#define __MS_PRIVATE     0x00040000 /* ??? */
#define __MS_SLAVE       0x00080000 /* ??? */
#define __MS_SHARED      0x00100000 /* ??? */
#define __MS_RELATIME    0x00200000 /* Only relevant when `MS_NOATIME' isn't set: the last-accessed timestamp is only changed to the
                                     * current realtime() when `OLD(ATIME) < MTIME'.  As such, ATIME can  only be used to  determine
                                     * accessed-after-last-modified when this flag has been set. */
#define __MS_KERNMOUNT   0x00400000 /* ??? */
#define __MS_I_VERSION   0x00800000 /* ??? */
#define __MS_STRICTATIME 0x01000000 /* ??? */
#define __MS_LAZYTIME    0x02000000 /* ??? */
#define __MS_ACTIVE      0x40000000 /* ??? */
#define __MS_NOUSER      0x80000000 /* ??? */

/* Flags that can be changed when combined with `MS_REMOUNT' */
#define __MS_RMT_MASK (__MS_RDONLY | __MS_SYNCHRONOUS | __MS_MANDLOCK | __MS_I_VERSION | __MS_LAZYTIME)

/* Magic mount flag number. Must be or'd with flag values. */
#define __MS_MGC_VAL 0xc0ed0000 /* Magic flag indicating ~new~ flags. */
#define __MS_MGC_MSK 0xffff0000 /* Magic flag mask. */

/* Flags for `umount2(2)' */
#define __MNT_FORCE       0x0001 /* Force unmount. */
#define __MNT_DETACH      0x0002 /* Only detach from the file-tree. (Umount happens once no more path-references exist) */
#define __MNT_EXPIRE      0x0004 /* Mark mounting point as expired. */
#define __UMOUNT_NOFOLLOW 0x0008 /* Don't follow symbolic links. */

#endif /* !_ASM_OS_KOS_MOUNT_H */
