/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FILESYS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FILESYS_H 1

#include <kernel/compiler.h>

#include <kernel/mman/module.h>
#include <kernel/types.h>

#include <hybrid/sched/atomic-lock.h>

#include <kos/lockop.h>

#ifdef __CC__
DECL_BEGIN

#ifndef REF_IF
#define REF_IF __REF_IF
#endif /* !REF_IF */

struct fsuper;
struct mfile;
struct driver;

#define FFILESYS_F_NORMAL 0x00 /* Normal filesystem flags. */
#define FFILESYS_F_NODEV  0x01 /* Don't need a block-device to open this filesystem. */
#define FFILESYS_F_SINGLE 0x80 /* This filesystem is actually a singleton. */

struct ffilesys;
SLIST_HEAD(ffilesys_slist, ffilesys);
struct ffilesys {
	SLIST_ENTRY(ffilesys) ffs_link;  /* [0..1][lock(INTERNAL)] Link entry of known filesystems. */
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
		 *
		 * This function must _ONLY_ initialize the following fields:
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_ops        = ...;  # Fs-specific operators for superblocks
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_parts      = ...;  # Properly with `NULL' (though `MFILE_PARTS_ANONYMOUS' and anything else is also OK)
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_changed    = ...;  # Properly with `SLIST_INIT' (though `MFILE_PARTS_ANONYMOUS' and anything else is also OK)
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift = ...;  # Address <=> block shift used by the filesystem
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_iobashift  = dev ? dev->mf_iobashift : ...; # Probably...
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_flags      = ...;  # Set of `MFILE_F_READONLY | MFILE_FS_NOSUID | MFILE_FS_NOEXEC |
		 *                                                                        #         MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO | MFILE_F_FIXEDFILESIZE |
		 *                                                                        #         MFILE_F_NOATIME |  MFILE_F_NOMTIME  |  MFILE_FN_NODIRATIME  |
		 *                                                                        #         MFILE_F_STRICTATIME | MFILE_F_LAZYTIME | MFILE_F_PERSISTENT |
		 *                                                                        #         MFILE_FN_ATTRREADONLY | MFILE_F_ROFLAGS'
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_filesize   = (pos_t)-1;      # Probably...
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_atime      = realtime();     # Probably...
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_mtime      = realtime();     # Probably...
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_ctime      = realtime();     # Probably...
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_btime      = realtime();     # Probably...
		 *   - return->fs_root._fdirnode_node_ fn_mode                    = S_IFDIR | 0777; # Probably...
		 *   - return->fs_root._fdirnode_node_ fn_ino                     = ...;  # Special INode number used for the fs-root
		 *   - return->fs_root._fdirnode_node_ fn_nlink                   = 1;    # Probably...
		 *   - return->fs_root._fdirnode_node_ fn_uid                     = 0;    # Probably...
		 *   - return->fs_root._fdirnode_node_ fn_gid                     = 0;    # Probably...
		 *   - return->fs_feat                                            = ...;  # Filesystem feature information
		 *   - *                                                                  # Any field added by a sub-class of `struct fsuper'
		 *
		 * The following fields will be initialized by the caller:
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_refcnt     = 1;
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_lock       = ATOMIC_RWLOCK_INIT;
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_initdone   = SIG_INIT(...);
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_lockops    = SLIST_HEAD_INITIALIZER(~);
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_part_amask = MAX(PAGESIZE, 1 << return->fs_root._fdirnode_node_ _fnode_file_ mf_blockshift) - 1;
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_meta       = NULL;
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_flags |= ... & (MFILE_F_READONLY | MFILE_FS_NOSUID | MFILE_FS_NOEXEC |    # Conditionally set
		 *                                                                     MFILE_F_NOATIME | MFILE_F_NOMTIME | MFILE_FN_NODIRATIME | # ...
		 *                                                                     MFILE_F_STRICTATIME | MFILE_F_LAZYTIME);                  # ...
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_trunclock  = 0;
		 *   - return->fs_root._fdirnode_node_ fn_super                   = return;
		 *   - return->fs_root._fdirnode_node_ fn_changed                 = LIST_ENTRY_UNBOUND_INITIALIZER;
		 *   - return->fs_root._fdirnode_node_ fn_supent.rb_lhs           = NULL;
		 *   - return->fs_root._fdirnode_node_ fn_supent.rb_rhs           = NULL;
		 *   - return->fs_root._fdirnode_node_ fn_allsuper                = ...;               // Caller will add to `fallsuper_list' once that should happen
		 *   - return->fs_nodes                                           = &return->fs_root;
		 *   - return->fs_nodeslock                                       = ATOMIC_RWLOCK_INIT;
		 *   - return->fs_nodeslockops                                    = SLIST_HEAD_INITIALIZER(~);
		 *   - return->fs_mounts                                          = LIST_HEAD_INITIALIZER(~);
		 *   - return->fs_mountslock                                      = ATOMIC_RWLOCK_INIT;
		 *   - return->fs_mountslockops                                   = SLIST_HEAD_INITIALIZER(~);
		 *   - return->fs_sys                                             = incref(filesys);
		 *   - return->fs_dev                                             = xincref(dev);
		 *   - return->fs_loadblocks                                      = ...; // Based on `dev->(mf_blockshift|mf_iobashift)' and `return->fs_root.(mf_blockshift|mf_iobashift)',
		 *   - return->fs_saveblocks                                      = ...; // as well as the set of mfile-block operators actually supported by `dev'
		 *   - return->fs_changednodes                                    = LIST_HEAD_INITIALIZER(~);
		 *   - return->fs_changednodes_lock                               = ATOMIC_LOCK_INIT;
		 *   - return->fs_changednodes_lops                               = SLIST_HEAD_INITIALIZER(~);
		 *   - return->fs_changedsuper                                    = LIST_ENTRY_UNBOUND_INITIALIZER;
		 *
		 * When the superblock should be  discarded without being mounted,  destroy(return)
		 * is called with caller-initialized fields in the same configuration as documented
		 * in the initialized-by-the-caller section, with the following additions:
		 *   - return->fs_root._fdirnode_node_ _fnode_file_ mf_refcnt = 0;
		 *   - return->fs_root._fdirnode_node_ fn_allsuper            = LIST_ENTRY_UNBOUND_INITIALIZER;
		 *
		 * =====================================================================================
		 * === Device requirements (s.a. `E_FSERROR_MOUNT_UNSUPPORTED_DEVICE')
		 *  - dev->mf_ops->mo_loadblocks != NULL
		 *  - dev->mf_ops->mo_stream == NULL || dev->mf_ops->mo_stream->mso_pread == NULL
		 *  - dev->mf_ops->mo_stream == NULL || dev->mf_ops->mo_stream->mso_preadv == NULL
		 *  - dev->mf_ops->mo_stream == NULL || dev->mf_ops->mo_stream->mso_pwrite == NULL
		 *  - dev->mf_ops->mo_stream == NULL || dev->mf_ops->mo_stream->mso_pwritev == NULL
		 *  - dev->mf_ops->mo_stream == NULL || dev->mf_ops->mo_stream->mso_mmap == NULL
		 *  - (dev->mf_flags & (MFILE_F_NOUSRIO | MFILE_F_NOUSRMMAP)) == 0
		 * If  these requirements aren't  fulfilled, the caller will  have already thrown an
		 * `E_FSERROR_MOUNT_UNSUPPORTED_DEVICE' exception. Also note that these requirements
		 * imply `mfile_hasrawio(dev)'
		 * =====================================================================================
		 *
		 * @param: dev: [1..1][!FFILESYS_F_NODEV] The  backing storage device  for the filesystem. The
		 *                                        caller  has incremented `mf_trunclock' such that the
		 *                                        file will not be truncated  for the duration of  the
		 *                                        call, and upon success, it will remain impossible to
		 *                                        truncate the file until the superblock is destroyed.
		 * @param: dev: [0..0][FFILESYS_F_NODEV] Always NULL
		 * @return: * : A new instance of a superblock for `dev'
		 * @return: NULL: `dev' cannot be mounted using this filesystem. */
		BLOCKING WUNUSED_T NONNULL_T((1)) struct fsuper *
		(KCALL *ffs_open)(struct ffilesys *__restrict filesys,
		                  struct mfile *dev, NCX UNCHECKED char *args)
				THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_CORRUPTED_FILE_SYSTEM, ...);

		/* [1..1][valid_if(FFILESYS_F_SINGLE)]
		 * Singleton instance of a superblock associated with this filesystem type. */
		REF struct fsuper        *ffs_single;
	};
	uint8_t                       ffs_flags; /* Filesystem type flags (Set of `FFILESYS_F_*') */
	COMPILER_FLEXIBLE_ARRAY(char, ffs_name); /* [const] Name of the filesystem type (As passed to `mount' using
	                                          * the `-t' option, as  well as appearing in  `/proc/filesystems') */
};

#define ffilesys_destroy(self)   module_destroy((struct module *)(self)->ffs_drv)
#define _ffilesys_refcnt_p(self) ((struct module *)(self)->ffs_drv)->md_refcnt
DEFINE_REFCNT_FUNCTIONS_P(struct ffilesys, _ffilesys_refcnt_p, ffilesys_destroy)


/* Global set of registered filesystem formats. */
DATDEF struct ffilesys_slist ffilesys_formats_list; /* [0..n][lock(ffilesys_formats_lock)] */
DATDEF struct atomic_lock ffilesys_formats_lock;    /* Lock for `ffilesys_formats_list' */
DATDEF struct lockop_slist ffilesys_formats_lops;   /* Lock operations for `ffilesys_formats_lock' */

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
#define ffilesys_formats_waitfor()    atomic_lock_waitfor(&ffilesys_formats_lock)
#define ffilesys_formats_waitfor_nx() atomic_lock_waitfor_nx(&ffilesys_formats_lock)


/* Open  a new superblock and return it.  This function is a high-level wrapper
 * around `ffs_open()' that does all of the fixed initialization of fields left
 * uninitialized by `ffs_open()' itself,  with the exception of  `fn_allsuper',
 * which is initialized as `LIST_ENTRY_UNBOUND_INIT()'.
 *
 * The returned superblock is _only_ visible to the caller, unless it's a singleton
 * superblock (`FFILESYS_F_SINGLE'), in which case the returned superblock is fully
 * initialized and its fields must _NOT_ be modified willy-nilly by the caller.
 *
 * WARNING: To safely deal with driver references in the case of singleton superblocks,
 *          the reference that is keeping `self'  alive (which is actually a  reference
 *          to  the backing driver)  may only be dropped  _AFTER_ path_mount() was used
 *          to mount the superblock (since the successful creation of a mounting  point
 *          will be holding a driver reference via `pathmount::pm_fsmount').
 *
 * NOTE: This function takes care to ensure that any given `dev' only ever gets
 *       mounted under a singular filesystem type (an existing fsuper for `dev'
 *       will always  be re-returned  unless its  `fs_mounts' had  been set  to
 *       `FSUPER_MOUNTS_DELETED').  If an existing  fsuper uses filesystem type
 *       other than `self', return `NULL'.
 *
 * @param: pnewly_created: Set to  true/false indicative  of  a new  superblock  having
 *                         been  opened.  When  set to  true,  `!isshared(return)', and
 *                         the caller must complete opening via `ffilesys_open_done()'.
 * @return: * :   The superblock that was opened.
 * @return: NULL: `FFILESYS_F_NODEV' isn't set, and `dev' cannot be mounted as a
 *                filesystem of this type.
 * @throw: E_FSERROR_MOUNT_UNSUPPORTED_DEVICE: `dev' cannot be used to mount superblocks.
 * @throw: E_FSERROR_CORRUPTED_FILE_SYSTEM:    The filesystem type was matched, but the on-disk
 *                                             filesystem  doesn't appear to make any sense. It
 *                                             looks like it's been corrupted... :( */
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) REF struct fsuper *FCALL
ffilesys_open(struct ffilesys *__restrict self, __BOOL *__restrict pnewly_created,
              struct mfile *dev, NCX UNCHECKED char *args)
		THROWS(E_BADALLOC, E_IOERROR, E_FSERROR_MOUNT_UNSUPPORTED_DEVICE,
		       E_FSERROR_CORRUPTED_FILE_SYSTEM, ...);

/* Helper wrapper for `ffilesys_open()' that blindly goes through all  filesystem
 * types and tries to open `dev' with each of those needing a device, that aren't
 * singleton filesystems.
 * @param: pnewly_created: Set to  true/false indicative  of  a new  superblock  having
 *                         been  opened.  When  set to  true,  `!isshared(return)', and
 *                         the caller must complete opening via `ffilesys_open_done()'.
 * @return: * :   The superblock that was opened.
 * @return: NULL: `dev' doesn't contain any known filesystem. */
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) REF struct fsuper *FCALL
ffilesys_opendev(__BOOL *__restrict pnewly_created,
                 struct mfile *__restrict dev,
                 NCX UNCHECKED char *args)
		THROWS(E_BADALLOC, E_FSERROR_MOUNT_UNSUPPORTED_DEVICE,
		       E_FSERROR_CORRUPTED_FILE_SYSTEM, ...);

/* Must be called  after `ffilesys_open()'  returns with  `*pnewly_created = true'
 * while a non-NULL `dev' was given (the same `dev' also passed to this function),
 * and after the newly created superblock  has been added to `fallsuper_list',  or
 * was destroyed in case the open was aborted.
 *
 * This function will indicate that the given `dev' is no longer in the process of
 * being opened, allowing future/concurrent attempts  at opening this device as  a
 * superblock from no longer blocking. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL ffilesys_open_done)(struct mfile *__restrict dev, __BOOL success DFL(1));


/* Lookup a filesystem type, given its name.
 * @return: * :   The named filesystem type.
 * @return: NULL: No such filesystem. */
FUNDEF WUNUSED ATTR_INS(1, 2) REF struct ffilesys *FCALL
ffilesys_byname(NCX char const *name, size_t namelen)
		THROWS(E_SEGFAULT, E_WOULDBLOCK);


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

/* Return a reference to the filesystem type that comes after `prev'
 * When `prev == NULL', return the first filesystem type. Note  that
 * when `prev' has been unloaded, this function will also return the
 * first (still-registered) filesystem type. */
FUNDEF WUNUSED REF struct ffilesys *FCALL
ffilesys_next(struct ffilesys *prev)
		THROWS(E_WOULDBLOCK);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FILESYS_H */
