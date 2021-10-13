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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FILESYS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FILESYS_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/mman/module.h>
#include <kernel/types.h>

#include <hybrid/sync/atomic-lock.h>

#include <kos/lockop.h>

#ifdef __CC__
DECL_BEGIN

#ifndef REF_IF
#define REF_IF __REF_IF
#endif /* !REF_IF */

struct fsuper;
struct blkdev;
struct driver;

#define FFILESYS_F_NORMAL 0x00 /* Normal filesystem flags. */
#define FFILESYS_F_NODEV  0x01 /* Don't need a block-device to open this filesystem. */
#define FFILESYS_F_SINGLE 0x80 /* This filesystem is actually a singleton. */

struct ffilesys;
LIST_HEAD(ffilesys_list, ffilesys);
struct ffilesys {
	LIST_ENTRY(ffilesys)          ffs_link;  /* [0..1][lock(INTERNAL)] Link entry of known filesystems. */
	union {
		struct lockop     _ffs_lop;  /* Used internally by `ffilesys_unregister()' */
		struct postlockop _ffs_plop; /* Used internally by `ffilesys_unregister()' */
	};
	REF_IF(LIST_ISBOUND(this, ffs_link))
	struct driver                *ffs_drv;   /* [1..1][const] The implementing driver application. */
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

#define ffilesys_destroy(self)   module_destroy((struct module *)(self)->ffs_drv)
#define _ffilesys_refcnt_p(self) ((struct module *)(self)->ffs_drv)->md_refcnt
DEFINE_REFCOUNT_FUNCTIONS_P(struct ffilesys, _ffilesys_refcnt_p, ffilesys_destroy)


/* Global set of registered filesystem formats. */
DATDEF struct ffilesys_list ffilesys_formats_list; /* [0..n][lock(ffilesys_formats_lock)] */
DATDEF struct atomic_lock ffilesys_formats_lock;   /* Lock for `ffilesys_formats_list' */
DATDEF struct lockop_slist ffilesys_formats_lops;  /* Lock operations for `ffilesys_formats_lock' */

/* Helper macros for working with `fchangedsuper_lock' */
#define _ffilesys_formats_reap()      _lockop_reap_atomic_lock(&ffilesys_formats_lops, &ffilesys_formats_lock)
#define ffilesys_formats_reap()       lockop_reap_atomic_lock(&ffilesys_formats_lops, &ffilesys_formats_lock)
#define ffilesys_formats_mustreap()   lockop_mustreap(&ffilesys_formats_lops)
#define ffilesys_formats_tryacquire() atomic_lock_tryacquire(&ffilesys_formats_lock)
#define ffilesys_formats_acquire()    atomic_lock_acquire(&ffilesys_formats_lock)
#define ffilesys_formats_acquire_nx() atomic_lock_acquire_nx(&ffilesys_formats_lock)
#define _ffilesys_formats_release()   atomic_lock_release(&ffilesys_formats_lock)
#define ffilesys_formats_release()    (atomic_lock_release(&ffilesys_formats_lock), ffilesys_formats_reap())
#define ffilesys_formats_acquired()   atomic_lock_acquired(&ffilesys_formats_lock)
#define ffilesys_formats_available()  atomic_lock_available(&ffilesys_formats_lock)


/* Register a given filesystem format.
 * @return: true:  Success.
 * @return: false: The format was already registered. */
FUNDEF NONNULL((1)) __BOOL FCALL
ffilesys_register(struct ffilesys *__restrict self)
		THROWS(E_WOULDBLOCK);

/* Unregister a given filesystem format.
 * @return: true:  Success.
 * @return: false: The format wasn't registered. */
FUNDEF NONNULL((1)) __BOOL
NOTHROW(FCALL ffilesys_unregister)(struct ffilesys *__restrict self);


DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FILESYS_H */
