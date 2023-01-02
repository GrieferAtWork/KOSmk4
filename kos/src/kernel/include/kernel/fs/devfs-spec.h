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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVFS_SPEC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVFS_SPEC_H 1

#include <kernel/compiler.h>

#include <kernel/fs/devfs.h>
#include <kernel/user.h>

/* Inode numbers for special devfs files. */
#define DEVFS_SPECINO(id)  (__CCAST(ino_t)(DEVFS_INONS_SPEC | ((id) << 3)))
#define DEVFS_INO_ROOT     DEVFS_SPECINO(0x00) /* /dev */
#define DEVFS_INO_BLOCK    DEVFS_SPECINO(0x01) /* /dev/block */
#define DEVFS_INO_CHAR     DEVFS_SPECINO(0x02) /* /dev/char */
#define DEVFS_INO_CPU      DEVFS_SPECINO(0x03) /* /dev/cpu */
#define DEVFS_INO_DISK     DEVFS_SPECINO(0x04) /* /dev/disk */
#define DEVFS_INO_MISC(id) DEVFS_SPECINO(0x80 + (id)) /* Misc, internal files (default disk rules) */

/* Inode numbers for dynamically created devfs files. */
#define DEVFS_INO_DYN(ptr) (__CCAST(ino_t)(DEVFS_INONS_DYN | ((uintptr_t)skew_kernel_pointer(ptr) << 3)))


#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_DEVFS_SPEC_H */
