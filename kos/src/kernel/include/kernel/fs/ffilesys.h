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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FFILESYS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FFILESYS_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/types.h>
#include <kernel/driver.h>

#ifdef __CC__
DECL_BEGIN

struct fsuper;
struct blkdev;

#define FFILESYS_F_NORMAL 0x00 /* Normal filesystem flags. */
#define FFILESYS_F_NODEV  0x01 /* Don't need a block-device to open this filesystem. */
#define FFILESYS_F_SINGLE 0x80 /* This filesystem is actually a singleton. */

struct ffilesys;
struct ffilesys {
	LIST_ENTRY(ffilesys)          ffs_link;  /* [0..1][lock(INTERNAL)] Link entry of known filesystems. */
	REF struct driver            *ffs_drv;   /* [1..1][const] The implementing driver application. */
	union {
		/* [1..1][valid_if(!FFILESYS_F_SINGLE)]
		 * Construct  a new superblock  instance of this  filesystem type that uses
		 * the  given `dev'.  May return `NULL'  (if and only  if `dev != NULL') if
		 * that device doesn't contain a valid instance of the expected filesystem.
		 * @param: dev: [1..1][!FFILESYS_F_NODEV] The backing storage device for the filesystem.
		 * @param: dev: [0..0][FFILESYS_F_NODEV] Always NULL
		 * @return: * : A new instance of a superblock for `dev' */
		WUNUSED NONNULL((1)) REF struct fsuper *
		(KCALL *ffs_open)(struct ffilesys *__restrict filesys,
		                  struct blkdev *dev, UNCHECKED USER char *args);

		/* [1..1][valid_if(FFILESYS_F_SINGLE)]
		 * Singleton instance of a superblock associated with this filesystem type. */
		REF struct fsuper        *ffs_single;
	};
	uint8_t                       ffs_flags; /* Filesystem type flags (Set of `FFILESYS_F_*') */
	COMPILER_FLEXIBLE_ARRAY(char, ffs_name); /* [const] Name of the filesystem type (As passed to `mount' using
	                                          *         the `-t' option, as well as appearing in `/dev/filesystems') */
};

#define ffilesys_destroy(self) driver_destroy((self)->ffs_drv)
DEFINE_REFCOUNT_FUNCTIONS(struct ffilesys, ffs_drv->d_refcnt, ffilesys_destroy)

/* Register a given filesystem. - May only be called once for any  given
 * filesystem. Furthermore, the filesystem will be automatically removed
 * from the list of known filesystem types when the associated driver is
 * being unloaded. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL ffilesys_register)(struct ffilesys *__restrict self);

/* TODO: API for inspecting registered filesystem  types.
 *       Should work the same as the all-mpart-s systems. */

DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FFILESYS_H */
