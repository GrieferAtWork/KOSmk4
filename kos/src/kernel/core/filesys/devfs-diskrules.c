/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FILESYS_DEVFS_DISKRULES_C
#define GUARD_KERNEL_CORE_FILESYS_DEVFS_DISKRULES_C 1

#include <kernel/compiler.h>

#include <kernel/fs/blkdev.h>
#include <kernel/fs/devfs-disk.h>

#include <stddef.h>

DECL_BEGIN

/************************************************************************/
/* /dev/disk/by-id                                                      */
/************************************************************************/
INTERN WUNUSED NONNULL((1, 2)) REF struct blkdev *KCALL
devdisk_id_byname(struct devdiskruledir *__restrict UNUSED(self),
                  struct flookup_info *__restrict info) {
	/* TODO */
	COMPILER_IMPURE();
	(void)info;
	return NULL;
}

INTERN WUNUSED NONNULL((1, 2, 3)) ssize_t KCALL
devdisk_id_toname(struct devdiskruledir *__restrict UNUSED(self),
                  struct blkdev *__restrict dev,
                  __pformatprinter printer, void *arg) {
	/* TODO */
	COMPILER_IMPURE();
	(void)dev;
	(void)printer;
	(void)arg;
	return 0;
}



/************************************************************************/
/* /dev/disk/by-label                                                   */
/************************************************************************/
INTERN WUNUSED NONNULL((1, 2)) REF struct blkdev *KCALL
devdisk_label_byname(struct devdiskruledir *__restrict UNUSED(self),
                     struct flookup_info *__restrict info) {
	/* TODO */
	COMPILER_IMPURE();
	(void)info;
	return NULL;
}

INTERN WUNUSED NONNULL((1, 2, 3)) ssize_t KCALL
devdisk_label_toname(struct devdiskruledir *__restrict UNUSED(self),
                     struct blkdev *__restrict dev,
                     __pformatprinter printer, void *arg) {
	/* TODO */
	COMPILER_IMPURE();
	(void)dev;
	(void)printer;
	(void)arg;
	return 0;
}



/************************************************************************/
/* /dev/disk/by-partlabel                                               */
/************************************************************************/
INTERN WUNUSED NONNULL((1, 2)) REF struct blkdev *KCALL
devdisk_partlabel_byname(struct devdiskruledir *__restrict UNUSED(self),
                         struct flookup_info *__restrict info) {
	/* TODO */
	COMPILER_IMPURE();
	(void)info;
	return NULL;
}

INTERN WUNUSED NONNULL((1, 2, 3)) ssize_t KCALL
devdisk_partlabel_toname(struct devdiskruledir *__restrict UNUSED(self),
                         struct blkdev *__restrict dev,
                         __pformatprinter printer, void *arg) {
	/* TODO */
	COMPILER_IMPURE();
	(void)dev;
	(void)printer;
	(void)arg;
	return 0;
}



/************************************************************************/
/* /dev/disk/by-partuuid                                                */
/************************************************************************/
INTERN WUNUSED NONNULL((1, 2)) REF struct blkdev *KCALL
devdisk_partuuid_byname(struct devdiskruledir *__restrict UNUSED(self),
                        struct flookup_info *__restrict info) {
	/* TODO */
	COMPILER_IMPURE();
	(void)info;
	return NULL;
}

INTERN WUNUSED NONNULL((1, 2, 3)) ssize_t KCALL
devdisk_partuuid_toname(struct devdiskruledir *__restrict UNUSED(self),
                        struct blkdev *__restrict dev,
                        __pformatprinter printer, void *arg) {
	/* TODO */
	COMPILER_IMPURE();
	(void)dev;
	(void)printer;
	(void)arg;
	return 0;
}



/************************************************************************/
/* /dev/disk/by-path                                                    */
/************************************************************************/
INTERN WUNUSED NONNULL((1, 2)) REF struct blkdev *KCALL
devdisk_path_byname(struct devdiskruledir *__restrict UNUSED(self),
                    struct flookup_info *__restrict info) {
	/* TODO */
	COMPILER_IMPURE();
	(void)info;
	return NULL;
}

INTERN WUNUSED NONNULL((1, 2, 3)) ssize_t KCALL
devdisk_path_toname(struct devdiskruledir *__restrict UNUSED(self),
                    struct blkdev *__restrict dev,
                    __pformatprinter printer, void *arg) {
	/* TODO */
	COMPILER_IMPURE();
	(void)dev;
	(void)printer;
	(void)arg;
	return 0;
}



/************************************************************************/
/* /dev/disk/by-uuid                                                    */
/************************************************************************/
INTERN WUNUSED NONNULL((1, 2)) REF struct blkdev *KCALL
devdisk_uuid_byname(struct devdiskruledir *__restrict UNUSED(self),
                    struct flookup_info *__restrict info) {
	/* TODO */
	COMPILER_IMPURE();
	(void)info;
	return NULL;
}

INTERN WUNUSED NONNULL((1, 2, 3)) ssize_t KCALL
devdisk_uuid_toname(struct devdiskruledir *__restrict UNUSED(self),
                    struct blkdev *__restrict dev,
                    __pformatprinter printer, void *arg) {
	/* TODO */
	COMPILER_IMPURE();
	(void)dev;
	(void)printer;
	(void)arg;
	return 0;
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DEVFS_DISKRULES_C */
