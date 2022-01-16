/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_DEV_BLOCK_H
#define GUARD_KERNEL_INCLUDE_DEV_BLOCK_H 1

#include <kernel/compiler.h>

/* TODO: Deprecated header! */
#include <kernel/fs/blkdev.h>

#define blkdev_devno(self)          device_getdevno(self)
#define blkdev_lookup_name(name)    ((REF struct blkdev *)device_lookup_bystring(name, strlen(name), S_IFBLK))
#define blkdev_lookup               blkdev_lookup_bydev
#define blkdev_lookup_nx            blkdev_lookup_bydev_nx
#define blkdev_getdevno             device_getdevno
#define blkdev_getname              device_getname
#define blkdev_getname_lock_acquire device_getname_lock_acquire
#define blkdev_getname_lock_release device_getname_lock_release

#endif /* !GUARD_KERNEL_INCLUDE_DEV_BLOCK_H */
