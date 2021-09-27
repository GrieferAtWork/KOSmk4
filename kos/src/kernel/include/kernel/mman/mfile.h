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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_H 1

#include <kernel/compiler.h>

#include <kernel/memory.h>
#include <kernel/types.h>
#include <misc/unlockinfo.h>
#include <sched/atomic64.h>
#include <sched/signal.h>

#include <hybrid/__minmax.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <bits/os/timespec.h>
#include <kos/lockop.h>

#include <libvio/api.h> /* LIBVIO_CONFIG_ENABLED */

#undef CONFIG_MFILE_LEGACY_VIO_OPS
#ifndef CONFIG_USE_NEW_FS
#if 1 /* TODO: Currently required for  backwards compatibility to  the old  mman.
       * The  plan is to  eventually disable this  option, and merge `inode_type'
       * with `mfile_ops', which should then contain a pointer for VIO operators.
       * With this option enabled, the old behavior is used, instead. */
#define CONFIG_MFILE_LEGACY_VIO_OPS
#endif
#endif /* !CONFIG_USE_NEW_FS */

/* Trace program counters of write-locks to mfile objects. */
#undef CONFIG_MFILE_TRACE_WRLOCK_PC
#ifndef NDEBUG
#define CONFIG_MFILE_TRACE_WRLOCK_PC
#endif /* !NDEBUG */


#ifdef __CC__
DECL_BEGIN

struct mpart; /* Memory file part. */
struct mfile; /* Memory storage owner/descriptor. */
struct mfile_ops;
struct mman;
struct iov_buffer;
struct iov_physbuffer;

#ifndef __mpart_slist_defined
#define __mpart_slist_defined
SLIST_HEAD(mpart_slist, mpart);
#endif /* !__mpart_slist_defined */

/* Block-index within some given mem-file. */
#ifndef __mfile_block_t_defined
#define __mfile_block_t_defined
typedef pos_t mfile_block_t;
#endif /* !__mfile_block_t_defined */



/* Special   value   for   `struct mfile::mf_parts':   Anonymous    file.
 * When  this value is used, then attempting  to access one of the file's
 * memory  parts  will yield  unique parts  for  every access,  such that
 * writes made to one part will not be mirrored by writes made to another
 * part that (supposedly) describes the same position. */
#define MFILE_PARTS_ANONYMOUS ((struct mpart *)-1)


#ifndef __poll_mode_t_defined
#define __poll_mode_t_defined
typedef unsigned int poll_mode_t; /* Set of `POLL*' */
#endif /* !poll_mode_t_defined */

/*
 * HINTS: Disallowing certain operations for `struct mfile' users:
 *
 * - MFILE_F_FIXEDFILESIZE:
 *    - mfile_truncate()   (throws: E_INVALID_ARGUMENT_CONTEXT_FIXED_LENGTH_FILE)
 *    - mfile_tailread()   (for offsets >= mf_filesize: blocks forever)
 *    - mfile_tailwrite()  (THROW(E_FSERROR_DISK_FULL))
 *    - mfile_read()       (for offsets >= mf_filesize: returns `0')
 *    - mfile_write()      (for offsets >= mf_filesize: THROW(E_FSERROR_DISK_FULL))
 *    - Combine with `mf_filesize = 0' to disable all conventional file  access.
 *      If this is done, note that you can still override the file's size-value,
 *      as returned by `stat(2)' by implementing `mf_ops->mo_stream->mso_stat'!
 *
 * - MFILE_F_READONLY:
 *    - mfile_tailwrite()  (THROW(E_FSERROR_READONLY))
 *    - mfile_write()      (THROW(E_FSERROR_READONLY))
 *    - mmap(SHARED|WRITE) (THROW(E_FSERROR_READONLY))
 *    - Note that `mfile_truncate()' is _not_ affected!
 *
 * - MFILE_F_DELETED:
 *    - Implies: MFILE_F_FIXEDFILESIZE                              (indirect; flag isn't actually set)
 *    - Implies: MFILE_F_READONLY                                   (indirect; flag isn't actually set)
 *    - Implies: @CTL.AF(mf_filesize == 0)                          (Sooner or later, mf_filesize will eventually become 0)
 *    - Implies: @CTL.AF(ALL(mf_parts)->mp_file == &mfile_anon[*])  (Sooner or later, ...)
 *    - Implies: @CTL.AF(mpart_isanon(ALL(mf_parts)))               (Sooner or later, ...)
 *    - Implies: @CTL.AF(mf_parts == MFILE_PARTS_ANONYMOUS)         (Sooner or later, ...)
 *    - Implies: @CTL.AF(mf_changed == MFILE_PARTS_ANONYMOUS)       (Sooner or later, ...)
 *    - Parts returned by `mfile_makepart(file)' point at `&mfile_anon[file->mf_blockshift]'
 *    - Note  @CTL.AF here means that the actual effects  of deleting a file might only become
 *      visible at random points in the future. This is because file deletion actually happens
 *      asynchronously (s.a. `mfile_delete()')
 *
 */


#ifdef CONFIG_USE_NEW_FS
struct handle_mmap_info;
struct stat;

/* Extended operators used for implementing stream interface
 * functions and/or overriding the behavior of certain user-
 * exposed functions. */
struct mfile_stream_ops {
	/* [0..1] Hook for `open(2)': Override what is actually returned when opening this file.
	 * @param: hand: [in|out] Upon entry, this handle describes the already-initialized mfile-
	 *                        handle that will be made  available to user-space. The  callback
	 *                        is allowed to modify that handle, however it must also take care
	 *                        to  account  for the  fact  that `hand->h_data'  must  contain a
	 *                        reference both on entry and exit!
	 * HINT: `hand' is initialized as follows upon entry:
	 * >> hand->h_type = HANDLE_TYPE_MFILE;
	 * >> hand->h_mode = ...; // Depending on o-flags passed to open(2).
	 * >> hand->h_data = incref(self);
	 * NOTE: `h_data' is reference on entry (when modified, you must
	 *       `decref_nokill(self)'  and  assign   `incref(new_obj)') */
	NONNULL((1, 2)) void
	(KCALL *mso_open)(struct mfile *__restrict self,
	                  struct handle *__restrict hand);

	/* [0..1] Hooks  for `read(2)' and  `readv(2)': stream-oriented file reading.
	 * Note that for consistency, anything that implements these operators should
	 * either document that read(2) returns different data than pread(2)/mmap(2),
	 * or disallow use of the later with `mf_filesize = 0, MFILE_F_FIXEDFILESIZE' */
	WUNUSED NONNULL((1)) size_t
	(KCALL *mso_read)(struct mfile *__restrict self, USER CHECKED void *dst,
	                  size_t num_bytes, iomode_t mode) THROWS(...);
	WUNUSED NONNULL((1, 2)) size_t
	(KCALL *mso_readv)(struct mfile *__restrict self, struct iov_buffer *__restrict dst,
	                   size_t num_bytes, iomode_t mode) THROWS(...);

	/* [0..1] Hooks  for `write(2)' and  `writev(2)': stream-oriented file writing.
	 * Note that for consistency, anything  that implements these operators  should
	 * either document that write(2) affects different data than pwrite(2)/mmap(2),
	 * or disallow use of the later with `mf_filesize = 0, MFILE_F_FIXEDFILESIZE' */
	WUNUSED NONNULL((1)) size_t
	(KCALL *mso_write)(struct mfile *__restrict self, USER CHECKED void const *src,
	                   size_t num_bytes, iomode_t mode) THROWS(...);
	WUNUSED NONNULL((1, 2)) size_t
	(KCALL *mso_writev)(struct mfile *__restrict self, struct iov_buffer *__restrict src,
	                    size_t num_bytes, iomode_t mode) THROWS(...);


	/* [0..1] Hooks for `pread(2)' and `pwrite(2)'.
	 * The praed/pwrite callbacks are only called by handle_pread() and handle_pwrite(),
	 * and  if  not given,  will default  to  using `mfile_read()'  and `mfile_write()'. */
	WUNUSED NONNULL((1)) size_t
	(KCALL *mso_pread)(struct mfile *__restrict self, USER CHECKED void *dst,
	                   size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
	WUNUSED NONNULL((1, 2)) size_t
	(KCALL *mso_preadv)(struct mfile *__restrict self, struct iov_buffer *__restrict dst,
	                    size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
	WUNUSED NONNULL((1)) size_t
	(KCALL *mso_pwrite)(struct mfile *__restrict self, USER CHECKED void const *src,
	                    size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
	WUNUSED NONNULL((1, 2)) size_t
	(KCALL *mso_pwritev)(struct mfile *__restrict self, struct iov_buffer *__restrict src,
	                     size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);

	/* [0..1] Hook for `lseek(2)': stream-oriented file seeking. */
	NONNULL((1)) pos_t
	(KCALL *mso_seek)(struct mfile *__restrict self, off_t offset,
	                  unsigned int whence) THROWS(...);

	/* [0..1] Hook for `ioctl(2)': Extended file I/O control.
	 * Note that no standard ioctl commands are defined for mem-files, meaning that
	 * this callback has completely unfiltered control over the `ioctl(2)' syscall. */
	NONNULL((1)) syscall_slong_t
	(KCALL *mso_ioctl)(struct mfile *__restrict self, syscall_ulong_t cmd,
	                   USER UNCHECKED void *arg, iomode_t mode)
			THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...);

	/* [0..1] Hook for `ftruncate(2)': File length setting.
	 * If defined, this callback will only be called by  `handle_mfile_truncate()',
	 * where  it  will take  the  place of  the  usual call  to `mfile_truncate()'.
	 * Note that this callback will  _not_ be called by `mfile_truncate()'  itself,
	 * and that `handle_mfile_truncate()' will not call  the later if this one  was
	 * called first, meaning that this callback itself must call `mfile_truncate()'
	 * when conventional file-truncation behavior is wanted. */
	NONNULL((1)) void
	(KCALL *mso_truncate)(struct mfile *__restrict self, pos_t new_size)
			THROWS(...);

	/* [0..1] Override for `mmap(2)': File mapping.
	 * If defined, this  function can be  used to fill  in mmap information  which
	 * may differ from  the default  behavior, which is  to simply  set `self'  as
	 * the  file  to-be   mapped,  while  leaving   the  other  arguments   alone.
	 * If you intend  to override  this operator,  I suggest  you initialize  your
	 * file as anonymous from the get-go, and possibly also set `mf_filesize = 0',
	 * as  well as the  `MFILE_F_FIXEDFILESIZE' flag to  prevent anyone from using
	 * your file's normal mem-file interface. */
	NONNULL((1, 2)) void
	(KCALL *mso_mmap)(struct mfile *__restrict self,
	                  struct handle_mmap_info *__restrict info)
			THROWS(...);

	/* [0..1] Override   for   `fallocate(2)':  File   data  pre-allocations.
	 * You may define this function to override the default behavior for pre-
	 * loading parts of a given file. By default, `mfile_preload() (TODO)' is
	 * used to pre-allocate  mem-parts, as well  as initialize their  backing
	 * memory.
	 * @return: * : The amount of newly allocated bytes. */
	NONNULL((1)) pos_t
	(KCALL *mso_allocate)(struct mfile *__restrict self,
	                      fallocate_mode_t mode,
	                      pos_t start, pos_t length)
			THROWS(...);

	/* [0..1] Additional information for `stat(2)': File information.
	 * This operator is entirely optional, and may be used to fill in
	 * additional file information that  wasn't already filled in  by
	 * the caller. By default, the caller will have already filled:
	 *   - st_nlink   = 1;
	 *   - st_size    = mf_filesize;
	 *   - st_blksize = 1 << mf_blockshift;
	 *   - st_blocks  = mf_filesize >> mf_blockshift;
	 *   - st_atim    = mf_atime;
	 *   - st_mtim    = mf_mtime;
	 *   - st_ctim    = mf_ctime;
	 *   - All other fields have been pre-initialized to zero
	 * As such, only the following fields always have fixed values:
	 *   - st_dev
	 *   - st_ino
	 *   - st_mode
	 *   - st_nlink
	 *   - st_uid
	 *   - st_gid
	 *   - st_rdev */
	NONNULL((1)) void
	(KCALL *mso_stat)(struct mfile *__restrict self,
	                  struct stat *__restrict result)
			THROWS(...);

	/* [0..1] Implementation for poll(2): Connect to signals.
	 * When not implemented, `handle_pollconnect()' simply behaves as a no-op */
	NONNULL((1)) void
	(KCALL *mso_pollconnect)(struct mfile *__restrict self,
	                         poll_mode_t what)
			THROWS(...);

	/* [0..1] Implementation for poll(2): Connect to signals.
	 * When not implemented, `handle_polltest()' always indicates readable+writable */
	WUNUSED NONNULL((1)) poll_mode_t
	(KCALL *mso_polltest)(struct mfile *__restrict self,
	                      poll_mode_t what)
			THROWS(...);

	/* [0..1] Implementation for custom hop(2)-operators (s.a. `<kos/hop/[...].h>')
	 * When not implemented, only the default set of hop-operators for mem-files is
	 * usable with this mem-file.
	 * @throws: E_WOULDBLOCK: `IO_NONBLOCK' was given and no data/space was available (at the moment) */
	NONNULL((1)) syscall_slong_t
	(KCALL *mso_hop)(struct mfile *__restrict self, syscall_ulong_t cmd,
	                 USER UNCHECKED void *arg, iomode_t mode)
			THROWS(...);

};
#endif /* CONFIG_USE_NEW_FS */


struct mfile_ops {
#ifdef CONFIG_USE_NEW_FS
#define _mfile_ops_firstfield(prefix) prefix##destroy
#define MFILE_OPS_FIELDS(prefix, T)                                                                         \
	/* [0..1] Finalize + free the given mem-file. */                                                        \
	NOBLOCK NONNULL((1)) void                                                                               \
	/*NOTHROW*/ (KCALL *prefix##destroy)(T *__restrict self);                                               \
	                                                                                                        \
	/* [0..1] Construct a new given mem-part. When not implemented, use the default                         \
	 *        mechanism for the creation of new mem-parts.                                                  \
	 * This function is mainly intended to be used by `mfile_pyhs' in order to create                       \
	 * custom, already-initialized mem-parts for use with a given physical  location.                       \
	 * NOTE: This function may assume that the given address range is aligned by `mf_part_amask'.           \
	 * The following fields should _NOT_ already be initialized by this                                     \
	 * function, and will unconditionally be initialized by the caller:                                     \
	 *  - mp_refcnt                      (Initialized to whatever is the correct value)                     \
	 *  - mp_flags & MPART_F_GLOBAL_REF  (Set if `self' isn't anonymous)                                    \
	 *  - mp_flags & MPART_F_LOCKBIT     (Must not be set)                                                  \
	 *  - mp_flags & MPART_F_CHANGED     (Must not be set)                                                  \
	 *  - mp_flags & MPART_F_PERSISTENT  (Set if `self' isn't anonymous and                                 \
	 *                                    has the `MFILE_F_PERSISTENT' flag set)                            \
	 *  - mp_flags & MPART_F__RBRED      (Needed of the file-tree)                                          \
	 *  - mp_file                        (Set to `self' or `mfile_anon[*]')                                 \
	 *  - mp_copy                        (Initialized as empty)                                             \
	 *  - mp_share                       (Initialized as empty)                                             \
	 *  - mp_lockops                     (Initialized as empty)                                             \
	 *  - mp_allparts                    (The part (may be) added to the all-list only                      \
	 *                                    _after_ all other fields were initialized)                        \
	 *  - mp_minaddr                     (Set to `minaddr' by the caller)                                   \
	 *  - mp_maxaddr                     (Set to `minaddr + num_bytes - 1' by the caller)                   \
	 *  - mp_changed                     (Intentionally left uninitialized)                                 \
	 *  - mp_filent                      (Needed of the file-tree; set to indicate                          \
	 *                                    an anon-part if `self' was anonymous)                             \
	 * As such, this function may only initialize:                                                          \
	 *  - mp_flags & ...                 (All flags except for the above)                                   \
	 *  - mp_state                       (usually `MPART_ST_VOID' or `MPART_ST_MEM')                        \
	 *  - mp_blkst_ptr / mp_blkst_inl    (Containing the fully initialized initial block-status bitset)     \
	 *  - mp_mem / mp_mem_sc / ...       (Containing the initial backing storage location; s.a. `mp_state') \
	 *  - mp_meta                        (usually `NULL') */                                                \
	ATTR_RETNONNULL NONNULL((1)) REF struct mpart *                                                         \
	(KCALL *prefix##newpart)(T *__restrict self,                                                            \
	                         PAGEDIR_PAGEALIGNED pos_t minaddr,                                             \
	                         PAGEDIR_PAGEALIGNED size_t num_bytes);                                         \
	                                                                                                        \
	/* [0..1] Load/initialize the given physical memory buffer (this is the read-from-disk callback)        \
	 * @assume(IS_ALIGNED(buf, (size_t)1 << MIN(self->mf_blockshift, PAGESHIFT)));                          \
	 * @assume(IS_ALIGNED(addr, (size_t)1 << self->mf_blockshift));                                         \
	 * @assume(addr + num_bytes <= self->mf_filesize);                                                      \
	 * @assume(self->mf_trunclock != 0);                                                                    \
	 * @assume(num_bytes != 0);                                                                             \
	 * @assume(WRITABLE_BUFFER_SIZE(buf) >= CEIL_ALIGN(num_bytes, 1 << self->mf_blockshift));               \
	 * NOTE: WRITABLE_BUFFER_SIZE means that this function is allowed to write until the aligned            \
	 *       end of the last  file-block when `num_bytes' isn't  aligned by whole blocks,  where            \
	 *       the size of a block is defined as `1 << self->mf_blockshift'. */                               \
	/* TODO: Change this function to add support for iov-based I/O  */                                      \
	NONNULL((1)) void (KCALL *prefix##loadblocks)(T *__restrict self, pos_t addr,                           \
	                                              physaddr_t buf, size_t num_bytes);                        \
	                                                                                                        \
	/* [0..1] Save/write-back the given physical memory buffer (this is the write-to-disk callback)         \
	 * @assume(IS_ALIGNED(buf, (size_t)1 << MIN(self->mf_blockshift, PAGESHIFT)));                          \
	 * @assume(IS_ALIGNED(addr, (size_t)1 << self->mf_blockshift));                                         \
	 * @assume(addr + num_bytes <= self->mf_filesize);                                                      \
	 * @assume(self->mf_trunclock != 0);                                                                    \
	 * @assume(num_bytes != 0);                                                                             \
	 * @assume(READABLE_BUFFER_SIZE(buf) >= CEIL_ALIGN(num_bytes, 1 << self->mf_blockshift));               \
	 * NOTE: READABLE_BUFFER_SIZE means that this function is allowed to read until the aligned             \
	 *       end  of the last file-block when `num_bytes'  isn't aligned by whole blocks, where             \
	 *       the size of a block is defined as `1 << self->mf_blockshift'. */                               \
	/* TODO: Change this function to add support for iov-based I/O  */                                      \
	NONNULL((1)) void (KCALL *prefix##saveblocks)(T *__restrict self, pos_t addr,                           \
	                                              physaddr_t buf, size_t num_bytes);                        \
	                                                                                                        \
	/* [0..1] Called after `MFILE_F_CHANGED' and/or `MFILE_F_ATTRCHANGED' becomes set.                      \
	 * @param: oldflags: Old file flags. (set of `MFILE_F_*')                                               \
	 * @param: newflags: New file flags. (set of `MFILE_F_*')                                               \
	 *                   Contains at least one of `MFILE_F_CHANGED | MFILE_F_ATTRCHANGED'                   \
	 *                   that wasn't already contained in `oldflags' */                                     \
	NOBLOCK NONNULL((1)) void                                                                               \
	/*NOTHROW*/ (KCALL *prefix##changed)(T *__restrict self,                                                \
	                                     uintptr_t oldflags, uintptr_t newflags);                           \
	                                                                                                        \
	/* [0..1] Stream operators. */                                                                          \
	struct mfile_stream_ops const *prefix##stream;                                                          \
	                                                                                                        \
	/* [0..1] VIO file operators. When non-NULL,  then this file is backed  by                              \
	 * VIO, and the `mo_loadblocks' and `mo_saveblocks' operators are ignored,                              \
	 * though should still be set to `NULL' for consistency. */                                             \
	struct vio_operators const *prefix##vio

	MFILE_OPS_FIELDS(mo_, struct mfile);

#else /* CONFIG_USE_NEW_FS */
	/* [0..1] Finalize + free the given mem-file. */
	NOBLOCK NONNULL((1)) void
	/*NOTHROW*/ (KCALL *mo_destroy)(struct mfile *__restrict self);

	/* [0..1] Construct a new given mem-part. When not implemented, use the default
	 *        mechanism for the creation of new mem-parts.
	 * This function is mainly intended to be used by `mfile_pyhs' in order to create
	 * custom, already-initialized mem-parts for use with a given physical  location.
	 * NOTE: This function may assume that the given address range is aligned by `mf_part_amask'.
	 * The following fields should _NOT_ already be initialized by this
	 * function, and will unconditionally be initialized by the caller:
	 *  - mp_refcnt                      (Initialized to whatever is the correct value)
	 *  - mp_flags & MPART_F_GLOBAL_REF  (Set if `self' isn't anonymous)
	 *  - mp_flags & MPART_F_LOCKBIT     (Must not be set)
	 *  - mp_flags & MPART_F_CHANGED     (Must not be set)
	 *  - mp_flags & MPART_F_PERSISTENT  (Set if `self' isn't anonymous and has the `MFILE_F_PERSISTENT' flag set)
	 *  - mp_flags & MPART_F__RBRED      (Needed of the file-tree)
	 *  - mp_file                        (Set to `self' or `mfile_anon[*]')
	 *  - mp_copy                        (Initialized as empty)
	 *  - mp_share                       (Initialized as empty)
	 *  - mp_lockops                     (Initialized as empty)
	 *  - mp_allparts                    (The part (may be) added to the all-list only _after_ all other fields were initialized)
	 *  - mp_minaddr                     (Set to `minaddr' by the caller)
	 *  - mp_maxaddr                     (Set to `minaddr + num_bytes - 1' by the caller)
	 *  - mp_changed                     (Intentionally left uninitialized)
	 *  - mp_filent                      (Needed of the file-tree; set to indicate an anon-part if `self' was anonymous)
	 * As such, this function may only initialize:
	 *  - mp_flags & ...                 (All flags except for the above)
	 *  - mp_state                       (usually `MPART_ST_VOID' or `MPART_ST_MEM')
	 *  - mp_blkst_ptr / mp_blkst_inl    (Containing the fully initialized initial block-status bitset)
	 *  - mp_mem / mp_mem_sc / ...       (Containing the initial backing storage location; s.a. `mp_state')
	 *  - mp_meta                        (usually `NULL') */
	ATTR_RETNONNULL NONNULL((1)) REF struct mpart *
	(KCALL *mo_newpart)(struct mfile *__restrict self,
	                    PAGEDIR_PAGEALIGNED pos_t minaddr,
	                    PAGEDIR_PAGEALIGNED size_t num_bytes);

	/* [0..1] Load/initialize the given physical memory buffer (this is the read-from-disk callback)
	 * @assume(IS_ALIGNED(buf, (size_t)1 << MIN(self->mf_blockshift, PAGESHIFT)));
	 * @assume(IS_ALIGNED(addr, (size_t)1 << self->mf_blockshift));
	 * @assume(addr + num_bytes <= self->mf_filesize);
	 * @assume(self->mf_trunclock != 0);
	 * @assume(num_bytes != 0);
	 * @assume(WRITABLE_BUFFER_SIZE(buf) >= CEIL_ALIGN(num_bytes, 1 << self->mf_blockshift));
	 * NOTE: WRITABLE_BUFFER_SIZE means that this function is allowed to write until the aligned
	 *       end of the last  file-block when `num_bytes' isn't  aligned by whole blocks,  where
	 *       the size of a block is defined as `1 << self->mf_blockshift'. */
	NONNULL((1)) void (KCALL *mo_loadblocks)(struct mfile *__restrict self, pos_t addr,
	                                         physaddr_t buf, size_t num_bytes);

	/* [0..1] Save/write-back the given physical memory buffer (this is the write-to-disk callback)
	 * @assume(IS_ALIGNED(buf, (size_t)1 << MIN(self->mf_blockshift, PAGESHIFT)));
	 * @assume(IS_ALIGNED(addr, (size_t)1 << self->mf_blockshift));
	 * @assume(addr + num_bytes <= self->mf_filesize);
	 * @assume(self->mf_trunclock != 0);
	 * @assume(num_bytes != 0);
	 * @assume(READABLE_BUFFER_SIZE(buf) >= CEIL_ALIGN(num_bytes, 1 << self->mf_blockshift));
	 * NOTE: READABLE_BUFFER_SIZE means that this function is allowed to read until the aligned
	 *       end  of the last file-block when `num_bytes'  isn't aligned by whole blocks, where
	 *       the size of a block is defined as `1 << self->mf_blockshift'. */
	NONNULL((1)) void (KCALL *mo_saveblocks)(struct mfile *__restrict self, pos_t addr,
	                                         physaddr_t buf, size_t num_bytes);

	/* [0..1] Called the first time the `MPART_F_CHANGED' flag is set for `part'.
	 * WARNING: This  function  is  called  while  a  lock  to  `part'  is  held!
	 * NOTE: Not invoked if a new change part is created as the result
	 *       of  an   already-known-as-changed   part   being   split. */
	NOBLOCK NONNULL((1, 2)) void
	/*NOTHROW*/ (KCALL *mo_changed)(struct mfile *__restrict self,
	                                struct mpart *__restrict part);

	/* Hacky forward-compatibility... */

	/* [0..1] Optional operators for when read(2) or write(2) is used with
	 *        a file descriptor pointing to a mfile of this type.
	 * These callbacks are  used by UVIO  datablocks to implement  the
	 * server/client architecture for user-space driven VIO emulation.
	 * They are also used to implement flexible-context files such  as
	 * those found under `/proc' */
	WUNUSED NONNULL((1)) size_t
	(KCALL *mo_stream_read)(struct mfile *__restrict self,
	                        USER CHECKED void *dst,
	                        size_t num_bytes, iomode_t mode) THROWS(...);
	WUNUSED NONNULL((1)) size_t
	(KCALL *mo_stream_write)(struct mfile *__restrict self,
	                         USER CHECKED void const *src,
	                         size_t num_bytes, iomode_t mode) THROWS(...);
	/* [0..1] Same as above, but used  when polling for data being  available.
	 * When not implemented (i.e. when set to `NULL'), poll is implemented for
	 * the datablock through use of  `rwlock_poll(read|write)(&self->mf_lock)' */
	NONNULL((1)) void
	(KCALL *dt_handle_pollconnect)(struct mfile *__restrict self,
	                               poll_mode_t what) THROWS(...);
	WUNUSED NONNULL((1)) poll_mode_t
	(KCALL *dt_handle_polltest)(struct mfile *__restrict self,
	                            poll_mode_t what) THROWS(...);
#endif /* !CONFIG_USE_NEW_FS */
};

#ifdef CONFIG_USE_NEW_FS
/* Flags defined here also map to:
 *  - `ST_*' from <sys/statvfs.h>
 *  - `MS_*' from <sys/mount.h>
 *
 * ```
 *  0x00000001  MFILE_F_READONLY       ST_RDONLY           MS_RDONLY
 *  0x00000002  MFILE_FS_NOSUID        ST_NOSUID           MS_NOSUID
 *  0x00000004                         ST_NODEV            MS_NODEV
 *  0x00000008  MFILE_FS_NOEXEC        ST_NOEXEC           MS_NOEXEC
 *  0x00000010                         ST_SYNCHRONOUS      MS_SYNCHRONOUS
 *  0x00000040                         ST_MANDLOCK         MS_MANDLOCK
 *  0x00000080                                             MS_DIRSYNC
 *  0x00000400  MFILE_F_NOATIME        ST_NOATIME          MS_NOATIME
 *  0x00000800                         ST_NODIRATIME       MS_NODIRATIME
 *  0x00010000                                             MS_POSIXACL
 *  0x00020000                                             MS_UNBINDABLE
 *  0x00200000                                             MS_RELATIME
 *  0x01000000                                             MS_STRICTATIME
 *  0x02000000                                             MS_LAZYTIME
 * ```
 */

/* Flags for `struct mfile::mf_flags' */
#define MFILE_F_NORMAL          0x00000000 /* Normal flags. */
#define MFILE_F_READONLY        0x00000001 /* [lock(READ:  mf_lock || mpart_lock_acquired(ANY(mf_parts)),
                                            *       WRITE: mf_lock && mpart_lock_acquired(ALL(mf_parts)))]
                                            * Disallow `mfile_write()', as  well as `PROT_WRITE|PROT_SHARED'  mappings.
                                            * Attempting to do either will result in `E_FSERROR_READONLY' being thrown. */
#define MFILE_FS_NOSUID         0x00000002 /* [lock(ATOMIC)] fsuper-specific: Ignore `S_ISGID' and `S_ISUID' bits. */
#define MFILE_FN_GLOBAL_REF     0x00000004 /* [lock(CLEAR_ONCE)] fnode-specific: The global list of fnode-s holds a reference to this one. */
#define MFILE_FS_NOEXEC         0x00000008 /* [lock(ATOMIC)] fsuper-specific: Disallow execution of files. */
/*      MFILE_F_                0x00000010  * ... Reserved: MS_SYNCHRONOUS */
#define MFILE_F_DELETED         0x00000020 /* [lock(WRITE_ONCE)][const_if(MFILE_F_READONLY)] The  file has  been marked  as
                                            * deleted. When this flag is set, new parts may be created with `mfile_anon[*]'
                                            * set  for  their  pointed-to  `mp_file'  field.  This  flag  also  means  that
                                            * `mfile_isanon(self)' and `mf_filesize == 0' will be the same sooner or later,
                                            * though  this may not be the case yet,  since file anonymization & all of that
                                            * jazz happens asynchronously through use of lockops!
                                            * Note that  this flag  implies `MFILE_F_READONLY|MFILE_F_FIXEDFILESIZE',  except
                                            * that the delete-operation itself will eventually  be allowed to set the  file's
                                            * size to `0'. Once async deletion is complete, the file's part-tree and changed-
                                            * list will be set to  MFILE_PARTS_ANONYMOUS, the file will  have a zero of  `0',
                                            * and all of its used-to-be parts will be anon, too. */
/*      MFILE_F_                0x00000040  * ... Reserved: MS_MANDLOCK */
/*      MFILE_F_                0x00000080  * ... Reserved: MS_DIRSYNC */
#define MFILE_F_ATTRCHANGED     0x00000100 /* [lock(SET(ATOMIC), CLEAR(WEAK))]
                                            * Indicates that attributes of this file (its size, etc.) have changed. */
#define MFILE_F_CHANGED         0x00000200 /* [lock(SET(ATOMIC), CLEAR(WEAK))]
                                            * This flag is set before `mo_changed()' is invoked, which also won't
                                            * be  invoked again until  this flag has been  cleared, which is done
                                            * as part of a call to `mfile_sync()' */
#define MFILE_F_NOATIME         0x00000400 /* [lock(_MFILE_F_SMP_TSLOCK)][const_if(MFILE_F_DELETED)] Don't modify the value of `mf_atime' */
/*      MFILE_F_                0x00000800  * ... Reserved: MS_NODIRATIME */
#define MFILE_F_NOUSRMMAP       0x00001000 /* [lock(ATOMIC)] Disallow user-space from mmap(2)-ing this file. */
#define MFILE_F_NOUSRIO         0x00002000 /* [lock(ATOMIC)] Disallow user-space from read(2)-ing or write(2)-ing this file. */
#define MFILE_F_NOMTIME         0x00004000 /* [lock(_MFILE_F_SMP_TSLOCK)][const_if(MFILE_F_DELETED)] Don't modify the value of `mf_mtime' */
/*efine MFILE_F_                0x00008000  * ... */
/*      MFILE_F_                0x00010000  * ... Reserved: MS_POSIXACL */
/*      MFILE_F_                0x00020000  * ... Reserved: MS_UNBINDABLE */
#define MFILE_F_PERSISTENT      0x00040000 /* [lock(CLEAR_ONCE)] Parts  of this file  should not be  unloaded to free up
                                            * memory. When this flag is set, then newly created parts (if non-anonymous)
                                            * will be created with the `MPART_F_PERSISTENT' flag set.
                                            * This  flag is used to implement ramfs-based filesystems, where it is
                                            * used to prevent files on such filesystem from being deleted when the
                                            * kernel tries to reclaim memory.
                                            * This flag is cleared when such a file is (intentionally) unlink(2)'d,
                                            * or when the backing superblock is unmounted. */
#define MFILE_F_FIXEDFILESIZE   0x00080000 /* [lock(WRITE_ONCE)] The  size  of  this  file  cannot  be altered.
                                            * Note that when using `mfile_write()' on a VIO-file, the call will
                                            * act as though this flag was always set, since it's impossible  to
                                            * atomically modify the file's  size while also invoking  (possibly
                                            * blocking) VIO callbacks, without locking all other write-past-end
                                            * operations on the same file. Note however that you can still  use
                                            * `mfile_truncate()' to change the size  of a VIO-file, so-long  as
                                            * it doesn't have this flag set! */
/*efine MFILE_F_                0x00100000  * ... */
/*      MFILE_F_                0x00200000  * ... Reserved: MS_RELATIME */
/*efine MFILE_F_                0x00400000  * ... */
/*efine MFILE_F_                0x00800000  * ... */
/*      MFILE_F_                0x01000000  * ... Reserved: MS_STRICTATIME */
/*      MFILE_F_                0x02000000  * ... Reserved: MS_LAZYTIME */
/*efine MFILE_F_                0x04000000  * ... */
/*efine MFILE_F_                0x08000000  * ... */
/*efine MFILE_F_                0x10000000  * ... */
/*efine MFILE_F_                0x20000000  * ... */
/*efine MFILE_F_                0x40000000  * ... */
#ifndef CONFIG_NO_SMP
#define _MFILE_F_SMP_TSLOCK     0x80000000 /* [lock(ATOMIC)] SMP-lock for TimeStamps (`mf_atime', `mf_mtime'). */
#endif /* !CONFIG_NO_SMP */
#endif /* CONFIG_USE_NEW_FS */

struct mfile {
	WEAK refcnt_t                 mf_refcnt;     /* Reference counter. */
	struct mfile_ops const       *mf_ops;        /* [1..1][const] File operators. */
#ifdef CONFIG_MFILE_LEGACY_VIO_OPS
	struct vio_operators const   *mf_vio;        /* [0..1][const] VIO operators. (deprecated field!) */
#endif /* CONFIG_MFILE_LEGACY_VIO_OPS */
	struct atomic_rwlock          mf_lock;       /* Lock for this file. */
#ifdef CONFIG_MFILE_TRACE_WRLOCK_PC
	void const                  *_mf_wrlockpc;   /* [lock(mf_lock)] Write-lock program counter. */
#endif /* CONFIG_MFILE_TRACE_WRLOCK_PC */
	RBTREE_ROOT(mpart)            mf_parts;      /* [0..n][lock(mf_lock)] File parts. */
	struct sig                    mf_initdone;   /* Signal broadcast whenever one of the blocks of one of
	                                              * the contained parts changes state from INIT to  LOAD. */
	Toblockop_slist(mfile)        mf_lockops;    /* [0..n][lock(ATOMIC)] Chain of lock operations. */
	struct REF mpart_slist        mf_changed;    /* [0..n][lock(APPEND: ATOMIC,
	                                              *             CLEAR:  ATOMIC && mf_lock)]
	                                              * Chain of references to parts that contain unsaved changes.
	                                              * NOTE: Set to `MFILE_PARTS_ANONYMOUS' if changed parts should
	                                              *       always  be ignored unconditionally,  the same way they
	                                              *       would be when `mf_ops->mo_saveblocks' is `NULL'. */
	size_t                        mf_part_amask; /* [const] == MAX(PAGESIZE, 1 << mf_blockshift) - 1
	                                              * This field describes the minimum alignment of file positions
	                                              * described by parts, minus one (meaning  it can be used as  a
	                                              * mask) */
	unsigned int                  mf_blockshift; /* [const] == log2(FILE_BLOCK_SIZE) */

#ifdef CONFIG_USE_NEW_FS
	uintptr_t                     mf_flags;      /* File flags (set of `MFILE_F_*') */
	WEAK size_t                   mf_trunclock;  /* [lock(INC(RDLOCK(mf_lock) || mpart_lock_acquired(ANY(mf_parts))),
	                                              *       DEC(ATOMIC))]
	                                              * Non-zero if `mf_filesize' must not be lowered. Incrementing this
	                                              * counter requires one  to be holding  a lock to  one of the  mem-
	                                              * parts  of  this file,  or a  lock to  the file  itself. However,
	                                              * decrementing it  doesn't impose  such a  requirement. When  this
	                                              * counter hits 0, then `mf_initdone' must be broadcast. */
	atomic64_t                    mf_filesize;   /* [lock(READ:      ATOMIC,
	                                              *       INCREMENT: mf_trunclock != 0 && ATOMIC,  // NOTE: `mf_trunclock' was incremented while holding `mf_lock'!
	                                              *                                                // By acquiring a write-lock to `mf_lock' and waiting for `mf_trunclock == 0',
	                                              *                                                // one must be able to prevent `mf_filesize' from changing at all!
	                                              *       DECREMENT: WRLOCK(mf_lock) && mf_trunclock == 0 &&
	                                              *                  mpart_lock_acquired(ALL(mf_parts)))]
	                                              * [const_if(MFILE_F_FIXEDFILESIZE || MFILE_F_DELETED)] // Also cannot be lowered when `mf_trunclock != 0'
	                                              * [valid_if(!mfile_isanon(self))] File       size       field.
	                                              * Attempting  to  construct new  mem-parts above  this address
	                                              * will  fail  and/or clamp  the  max accessible  file  size to
	                                              * the given address. Note however that  in the case of a  file
	                                              * that doesn't have the `MFILE_F_FIXEDFILESIZE' flag set, this
	                                              * values _can_ be increased by  writing beyond the end of  the
	                                              * file in a call to  `mfile_write()'. Also note that  whenever
	                                              * this value is increased, then the `mf_initdone' signal  will
	                                              * be broadcast. */
	struct timespec               mf_atime;      /* [lock(_MFILE_F_SMP_TSLOCK)][const_if(MFILE_F_NOATIME)][valid_if(!MFILE_F_DELETED)]
	                                              * Last-accessed timestamp. NOTE!!!  Becomes invalid when  `MFILE_F_DELETED' is  set!
	                                              * iow: After reading this field, you must first check if `MFILE_F_DELETED' is set
	                                              *      before proceeding to use the data you've just read! */
	struct timespec               mf_mtime;      /* [lock(_MFILE_F_SMP_TSLOCK)][const_if(MFILE_F_NOMTIME)][valid_if(!MFILE_F_DELETED)]
	                                              * Last-modified timestamp. NOTE!!!  Becomes invalid when  `MFILE_F_DELETED' is  set!
	                                              * iow: After reading this field, you must first check if `MFILE_F_DELETED' is set
	                                              *      before proceeding to use the data you've just read! */
	struct timespec               mf_ctime;      /* [const][valid_if(!MFILE_F_DELETED)]
	                                              * Creation timestamp. NOTE!!! Becomes invalid when `MFILE_F_DELETED' is set!
	                                              * iow: After reading this field, you must first check if `MFILE_F_DELETED' is set
	                                              *      before proceeding to use the data you've just read! */
#endif /* CONFIG_USE_NEW_FS */
};


#ifdef CONFIG_USE_NEW_FS
/* Increment or decrement the size-lock counter. In order to use these  functions,
 * the caller must currently be holding a lock to `self->mf_lock', or at least one
 * of the parts found in the tree of `self->mf_parts'.
 * Alternatively, when `mfile_isanon(self)' is true, then no such requirements are
 * imposed, and use of these functions becomes optional. */
#define mfile_trunclock_inc(self) \
	__hybrid_atomic_inc((self)->mf_trunclock, __ATOMIC_ACQUIRE)
#define mfile_trunclock_dec(self)                                        \
	(__hybrid_atomic_decfetch((self)->mf_trunclock, __ATOMIC_RELEASE) || \
	 (sig_broadcast(&(self)->mf_initdone), 0))
#define mfile_trunclock_dec_nosignal(self) \
	__hybrid_atomic_decfetch((self)->mf_trunclock, __ATOMIC_RELEASE)

#ifdef CONFIG_NO_SMP
#define mfile_tslock_tryacquire(self)   1
#define mfile_tslock_acquire_nopr(self) (void)0
#define mfile_tslock_release_nopr(self) (void)0
#else /* CONFIG_NO_SMP */
#define mfile_tslock_tryacquire(self)               \
	(!(__hybrid_atomic_fetchor((self)->mf_flags,    \
	                           _MFILE_F_SMP_TSLOCK, \
	                           __ATOMIC_ACQUIRE) &  \
	   _MFILE_F_SMP_TSLOCK))
#define mfile_tslock_acquire_nopr(self)        \
	do {                                       \
		while (!mfile_tslock_tryacquire(self)) \
			task_pause();                      \
	}	__WHILE0
#define mfile_tslock_release_nopr(self) \
	__hybrid_atomic_and((self)->mf_flags, ~_MFILE_F_SMP_TSLOCK, __ATOMIC_RELEASE)
#endif /* !CONFIG_NO_SMP */
#define mfile_tslock_acquire(self)                \
	do {                                          \
		pflag_t _mtsl_was = PREEMPTION_PUSHOFF(); \
		mfile_tslock_acquire_nopr(self)
#define mfile_tslock_release(self)       \
		mfile_tslock_release_nopr(self); \
	} __WHILE0


/* Mark `what' as having changed for `self'
 * @param: what: Set of `MFILE_F_CHANGED | MFILE_F_ATTRCHANGED' */
FORCELOCAL NOBLOCK NONNULL((1)) void
NOTHROW(mfile_changed)(struct mfile *__restrict self, uintptr_t what) {
	uintptr_t old_flags, new_flags;
	old_flags = __hybrid_atomic_fetchor(self->mf_flags, what, __ATOMIC_SEQ_CST);
	new_flags = old_flags | what;
	if (old_flags != new_flags && self->mf_ops->mo_changed)
		(*self->mf_ops->mo_changed)(self, old_flags, new_flags);
}
#endif /* CONFIG_USE_NEW_FS */

#ifdef CONFIG_MFILE_LEGACY_VIO_OPS
#define __mfile_init_vio(self)  (self)->mf_vio = __NULLPTR,
#define __mfile_cinit_vio(self) __hybrid_assert((self)->mf_vio == __NULLPTR),
#else /* CONFIG_MFILE_LEGACY_VIO_OPS */
#define __mfile_init_vio(self)  /* nothing */
#define __mfile_cinit_vio(self) /* nothing */
#endif /* !CONFIG_MFILE_LEGACY_VIO_OPS */

#define _mfile_cinit_blockshift _mfile_init_blockshift
#define _mfile_init_blockshift(self, block_shift)                               \
	((self)->mf_blockshift = (block_shift),                                     \
	 (self)->mf_part_amask = ((size_t)1 << (((self)->mf_blockshift) > PAGESHIFT \
	                                        ? ((self)->mf_blockshift)           \
	                                        : PAGESHIFT)) -                     \
	                         1)
#ifdef CONFIG_MFILE_TRACE_WRLOCK_PC
#define __MFILE_INIT_WRLOCKPC        __NULLPTR,
#define __mfile_init_wrlockpc(self)  (self)->_mf_wrlockpc = __NULLPTR,
#define __mfile_cinit_wrlockpc(self) __hybrid_assert((self)->_mf_wrlockpc == __NULLPTR),
#else /* CONFIG_MFILE_TRACE_WRLOCK_PC */
#define __MFILE_INIT_WRLOCKPC        /* nothing */
#define __mfile_init_wrlockpc(self)  /* nothing */
#define __mfile_cinit_wrlockpc(self) /* nothing */
#endif /* !CONFIG_MFILE_TRACE_WRLOCK_PC */


#ifdef CONFIG_USE_NEW_FS
/* Initialize common fields. The caller must still initialize:
 *  - mf_ops,  mf_parts,  mf_part_amask,   mf_blockshift,
 *    mf_flags, mf_filesize, mf_atime, mf_mtime, mf_ctime */
#define _mfile_init_common(self)           \
	((self)->mf_refcnt = 1,                \
	 atomic_rwlock_init(&(self)->mf_lock), \
	 sig_init(&(self)->mf_initdone),       \
	 SLIST_INIT(&(self)->mf_lockops),      \
	 (self)->mf_trunclock = 0)
#define _mfile_cinit_common(self)                       \
	((self)->mf_refcnt = 1,                             \
	 atomic_rwlock_cinit(&(self)->mf_lock),             \
	 sig_cinit(&(self)->mf_initdone),                   \
	 __hybrid_assert(SLIST_EMPTY(&(self)->mf_lockops)), \
	 __hybrid_assert((self)->mf_trunclock == 0))

/* Initialize common+basic fields. The caller must still initialize:
 *  - mf_parts, mf_flags, mf_filesize, mf_atime, mf_mtime, mf_ctime */
#define _mfile_init(self, ops, block_shift) \
	(_mfile_init_common(self),              \
	 (self)->mf_ops = (ops),                \
	 __mfile_init_wrlockpc(self)            \
	 _mfile_init_blockshift(self, block_shift))
#define _mfile_cinit(self, ops, block_shift) \
	(_mfile_cinit_common(self),              \
	 (self)->mf_ops = (ops),                 \
	 __mfile_cinit_wrlockpc(self)            \
	 _mfile_cinit_blockshift(self, block_shift))
#else /* CONFIG_USE_NEW_FS */
#define mfile_init(self, ops, block_shift) \
	((self)->mf_refcnt = 1,                \
	 (self)->mf_ops    = (ops),            \
	 __mfile_init_vio(self)                \
	 __mfile_init_wrlockpc(self)           \
	 atomic_rwlock_init(&(self)->mf_lock), \
	 (self)->mf_parts = __NULLPTR,         \
	 sig_init(&(self)->mf_initdone),       \
	 SLIST_INIT(&(self)->mf_lockops),      \
	 SLIST_INIT(&(self)->mf_changed),      \
	 _mfile_init_blockshift(self, block_shift))
#define mfile_cinit(self, ops, block_shift)             \
	((self)->mf_refcnt = 1,                             \
	 (self)->mf_ops    = (ops),                         \
	 __mfile_cinit_vio(self)                            \
	 __mfile_cinit_wrlockpc(self)                       \
	 atomic_rwlock_cinit(&(self)->mf_lock),             \
	 __hybrid_assert((self)->mf_parts == __NULLPTR),    \
	 sig_cinit(&(self)->mf_initdone),                   \
	 __hybrid_assert(SLIST_EMPTY(&(self)->mf_lockops)), \
	 __hybrid_assert(SLIST_EMPTY(&(self)->mf_changed)), \
	 _mfile_init_blockshift(self, block_shift))
#endif /* !CONFIG_USE_NEW_FS */

/* Get a [0..1]-pointer to the VIO operators of `self' */
#ifdef CONFIG_MFILE_LEGACY_VIO_OPS
#define mfile_getvio(self) ((self)->mf_vio)
#else /* CONFIG_MFILE_LEGACY_VIO_OPS */
#define mfile_getvio(self) ((self)->mf_ops->mo_vio)
#endif /* !CONFIG_MFILE_LEGACY_VIO_OPS */


#ifdef CONFIG_MFILE_LEGACY_VIO_OPS
#define MFILE_INIT_EX(refcnt, ops, parts, changed, blockshift)                         \
	{                                                                                  \
		/* .mf_refcnt     = */ refcnt,                                                 \
		/* .mf_ops        = */ ops,                                                    \
		/* .mf_vio        = */ __NULLPTR,                                              \
		/* .mf_lock       = */ ATOMIC_RWLOCK_INIT, __MFILE_INIT_WRLOCKPC               \
		/* .mf_parts      = */ parts,                                                  \
		/* .mf_initdone   = */ SIG_INIT,                                               \
		/* .mf_lockops    = */ SLIST_HEAD_INITIALIZER(~),                              \
		/* .mf_changed    = */ { changed },                                            \
		/* .mf_part_amask = */ __hybrid_max_c2(PAGESIZE, (size_t)1 << blockshift) - 1, \
		/* .mf_blockshift = */ blockshift,                                             \
	}

/* TODO: Remove the following 2! */
#define MFILE_INIT_VIO_EX(type, vio, parts, pageshift)                   \
	{                                                                    \
		/* .mf_refcnt     = */ 1,                                        \
		/* .mf_ops        = */ type,                                     \
		/* .mf_vio        = */ vio,                                      \
		/* .mf_lock       = */ ATOMIC_RWLOCK_INIT, __MFILE_INIT_WRLOCKPC \
		/* .mf_parts      = */ parts,                                    \
		/* .mf_initdone   = */ SIG_INIT,                                 \
		/* .mf_lockops    = */ SLIST_HEAD_INITIALIZER(~),                \
		/* .mf_changed    = */ SLIST_HEAD_INITIALIZER(~),                \
		/* .mf_blockshift = */ PAGESHIFT - (pageshift),                  \
		/* .mf_part_amask = */ PAGESIZE - 1,                             \
	}
#define MFILE_INIT_VIO(vio) MFILE_INIT_VIO_EX(&mfile_ndef_ops, vio, __NULLPTR, 0)
#else /* CONFIG_MFILE_LEGACY_VIO_OPS */
#define MFILE_INIT_EX(refcnt, ops, parts, changed, blockshift)                         \
	{                                                                                  \
		/* .mf_refcnt     = */ refcnt,                                                 \
		/* .mf_ops        = */ ops,                                                    \
		/* .mf_lock       = */ ATOMIC_RWLOCK_INIT, __MFILE_INIT_WRLOCKPC               \
		/* .mf_parts      = */ parts,                                                  \
		/* .mf_initdone   = */ SIG_INIT,                                               \
		/* .mf_lockops    = */ SLIST_HEAD_INITIALIZER(~),                              \
		/* .mf_changed    = */ { changed },                                            \
		/* .mf_part_amask = */ __hybrid_max_c2(PAGESIZE, (size_t)1 << blockshift) - 1, \
		/* .mf_blockshift = */ blockshift,                                             \
	}
#endif /* !CONFIG_MFILE_LEGACY_VIO_OPS */
#define MFILE_INIT(ops, blockshift)      MFILE_INIT_EX(1, ops, __NULLPTR, __NULLPTR, blockshift)
#define MFILE_INIT_ANON(ops, blockshift) MFILE_INIT_EX(1, ops, MFILE_PARTS_ANONYMOUS, MFILE_PARTS_ANONYMOUS, blockshift)


/* Allocate physical memory for use with mem-parts created for `self'
 * This function is a more restrictive version of `page_malloc_part(1, max_pages, res_pages)',
 * in   that  it  will  also  ensure  that  returned  pages  are  properly  aligned,  as  well
 * as that  the  given  `max_pages'  is  also properly  aligned.  Note  however  that  so-long
 * as   the  size  of  a  single  file-block  is  <=  PAGESIZE,  this  function  behaves  100%
 * identical to the above call to `page_malloc_part()' */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 3)) physpage_t
NOTHROW(FCALL mfile_alloc_physmem)(struct mfile *__restrict self,
                                   physpagecnt_t max_pages,
                                   physpagecnt_t *__restrict res_pages);


/* Destroy a given mem-file */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mfile_destroy)(struct mfile *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct mfile, mf_refcnt, mfile_destroy)


/* Check if the given mem-file has been marked as  anonymous.
 * When this is the case, then accessed mem-parts of the file
 * as always unique and never the same during repeated calls. */
#define mfile_isanon(self) ((self)->mf_parts == MFILE_PARTS_ANONYMOUS)

/* Floor- or ceil-align a given `addr' such that it may describe the start/end of a mem-part. */
#define mfile_addr_flooralign(self, addr) (pos_t)((uint64_t)(addr) & ~(self)->mf_part_amask)
#define mfile_addr_ceilalign(self, addr)  (pos_t)(((uint64_t)(addr) + (self)->mf_part_amask) & ~(self)->mf_part_amask)
#define mfile_addr_aligned(self, addr)    (((uint64_t)(addr) & (self)->mf_part_amask) == 0)

/* Reap lock operations of `self' */
#define _mfile_lockops_reap(self)    _oblockop_reap_atomic_rwlock(&(self)->mf_lockops, &(self)->mf_lock, self)
#define mfile_lockops_reap(self)     oblockop_reap_atomic_rwlock(&(self)->mf_lockops, &(self)->mf_lock, self)
#define mfile_lockops_mustreap(self) (__hybrid_atomic_load((self)->mf_lockops.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)

/* Lock accessor helpers for `struct mfile' */
#ifdef CONFIG_MFILE_TRACE_WRLOCK_PC
#include <asm/intrin.h>
#define __mfile_trace_wrlock_setpc(self) (void)((self)->_mf_wrlockpc = __rdip())
#define __mfile_trace_wrlock_clrpc(self) (void)((self)->_mf_wrlockpc = __NULLPTR)
#define mfile_lock_write(self)      (atomic_rwlock_write(&(self)->mf_lock), __mfile_trace_wrlock_setpc(self))
#define mfile_lock_write_nx(self)   (atomic_rwlock_write_nx(&(self)->mf_lock) ? (__mfile_trace_wrlock_setpc(self), 1) : 0)
#define mfile_lock_trywrite(self)   (atomic_rwlock_trywrite(&(self)->mf_lock) ? (__mfile_trace_wrlock_setpc(self), 1) : 0)
#define mfile_lock_endwrite(self)   (__mfile_trace_wrlock_clrpc(self), atomic_rwlock_endwrite(&(self)->mf_lock), mfile_lockops_reap(self))
#define mfile_lock_endwrite_f(self) (__mfile_trace_wrlock_clrpc(self), atomic_rwlock_endwrite(&(self)->mf_lock))
#define mfile_lock_end(self)        (void)(mfile_lock_writing(self) ? __mfile_trace_wrlock_clrpc(self) : (void)0, atomic_rwlock_end(&(self)->mf_lock) && (mfile_lockops_reap(self), 0))
#define mfile_lock_end_f(self)      (mfile_lock_writing(self) ? __mfile_trace_wrlock_clrpc(self) : (void)0, atomic_rwlock_end(&(self)->mf_lock))
#define mfile_lock_upgrade(self)    ({ __BOOL __ok = atomic_rwlock_upgrade(&(self)->mf_lock); __mfile_trace_wrlock_setpc(self); __ok; })
#define mfile_lock_upgrade_nx(self) ({ unsigned int __ok = atomic_rwlock_upgrade_nx(&(self)->mf_lock); if (__ok != 0) __mfile_trace_wrlock_setpc(self); __ok; })
#define mfile_lock_tryupgrade(self) (atomic_rwlock_tryupgrade(&(self)->mf_lock) ? (__mfile_trace_wrlock_setpc(self), 1) : 0)
#define mfile_lock_downgrade(self)  (__mfile_trace_wrlock_clrpc(self), atomic_rwlock_downgrade(&(self)->mf_lock))
#else /* CONFIG_MFILE_TRACE_WRLOCK_PC */
#define mfile_lock_write(self)      atomic_rwlock_write(&(self)->mf_lock)
#define mfile_lock_write_nx(self)   atomic_rwlock_write_nx(&(self)->mf_lock)
#define mfile_lock_trywrite(self)   atomic_rwlock_trywrite(&(self)->mf_lock)
#define mfile_lock_endwrite(self)   (atomic_rwlock_endwrite(&(self)->mf_lock), mfile_lockops_reap(self))
#define mfile_lock_endwrite_f(self) atomic_rwlock_endwrite(&(self)->mf_lock)
#define mfile_lock_end(self)        (void)(atomic_rwlock_end(&(self)->mf_lock) && (mfile_lockops_reap(self), 0))
#define mfile_lock_end_f(self)      atomic_rwlock_end(&(self)->mf_lock)
#define mfile_lock_upgrade(self)    atomic_rwlock_upgrade(&(self)->mf_lock)
#define mfile_lock_upgrade_nx(self) atomic_rwlock_upgrade_nx(&(self)->mf_lock)
#define mfile_lock_tryupgrade(self) atomic_rwlock_tryupgrade(&(self)->mf_lock)
#define mfile_lock_downgrade(self)  atomic_rwlock_downgrade(&(self)->mf_lock)
#endif /* !CONFIG_MFILE_TRACE_WRLOCK_PC */
#define mfile_lock_read(self)       atomic_rwlock_read(&(self)->mf_lock)
#define mfile_lock_read_nx(self)    atomic_rwlock_read_nx(&(self)->mf_lock)
#define mfile_lock_tryread(self)    atomic_rwlock_tryread(&(self)->mf_lock)
#define mfile_lock_endread(self)    (void)(atomic_rwlock_endread(&(self)->mf_lock) && (mfile_lockops_reap(self), 0))
#define mfile_lock_endread_f(self)  atomic_rwlock_endread(&(self)->mf_lock)
#define mfile_lock_reading(self)    atomic_rwlock_reading(&(self)->mf_lock)
#define mfile_lock_writing(self)    atomic_rwlock_writing(&(self)->mf_lock)
#define mfile_lock_canread(self)    atomic_rwlock_canread(&(self)->mf_lock)
#define mfile_lock_canwrite(self)   atomic_rwlock_canwrite(&(self)->mf_lock)


#ifdef CONFIG_USE_NEW_FS
/* Make the given file anonymous+deleted. What this means is that (in order):
 *  - The `MFILE_F_DELETED' flag is set for the file.
 *  - The file-fields of all mem-parts are altered to point
 *    at  anonymous  memory   files.  (s.a.   `mfile_anon')
 *  - The `MPART_F_GLOBAL_REF' flag is cleared for all parts
 *  - The `mf_parts' and `mf_changed' fields are set to `MFILE_PARTS_ANONYMOUS'
 *  - The `mf_filesize' field is set to `0'.
 * The result of all of this is that it is no longer possible to
 * trace  back  mappings  of  parts  of  `self'  to  that  file.
 *
 * This function is called when the given file `self' should be deleted,
 * or has become  unavailable for  some other reason  (e.g. the  backing
 * filesystem has been unmounted)
 *
 * Note that  (with the  exception of  `MFILE_F_DELETED' being  set, which  is
 * always done synchronously), this function operates entirely asynchronously,
 * meaning  that it uses lockops in order to wait for any locks it may need to
 * become available. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_delete)(struct mfile *__restrict self);
#else /* CONFIG_USE_NEW_FS */
/* Make the given file anonymous+deleted. What this means is that:
 *  - Existing mappings of all  mem-parts are altered to  point
 *    at anonymous memory files. For this purpose, the nodes of
 *    all existing mappings are altered. (s.a. `mfile_anon')
 *  - The `MPART_F_GLOBAL_REF' flag is cleared for all parts
 *  - The `mf_parts' and `mf_changed' are set to `MFILE_PARTS_ANONYMOUS'
 * The result of all of this is that it is no longer possible to
 * trace  back  mappings  of  parts  of  `self'  to  that  file.
 *
 * This function is called when the given file `self' should be deleted,
 * or has become  unavailable for  some other reason  (e.g. the  backing
 * filesystem has been unmounted) */
FUNDEF NONNULL((1)) void FCALL
mfile_delete(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK);
#endif /* !CONFIG_USE_NEW_FS */


/* Sync unwritten changes made to parts within the given address range.
 * @return: * : The total # of bytes that have been synced. */
FUNDEF NONNULL((1)) pos_t FCALL
mfile_sync(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK, ...);

/* Check if there are unwritten changes made to any of the parts of `self' */
#define mfile_haschanged(self) \
	(((uintptr_t)__hybrid_atomic_load((self)->mf_changed.slh_first, __ATOMIC_ACQUIRE) - 1) < (uintptr_t)-2)


/* Check `self' for a known mem-part that contains `addr', and (if
 * found), return that part. Otherwise, construct a new part start
 * starts at `addr' and spans around `hint_bytes' bytes (less  may
 * be returned if another part  already exists that describes  the
 * mapping above the requested location, and more may be  returned
 * if  a pre-existing part was spans beyond `addr +hint_bytes -1')
 *
 * Note that the caller must ensure that:
 * >> mfile_addr_aligned(addr) && mfile_addr_aligned(hint_bytes)
 * @return: * : A reference to a part that (at some point in the past) contained
 *              the given `addr'. It may no  longer contain that address now  as
 *              the result of being truncated since.
 * @throw: E_INVALID_ARGUMENT:E_INVALID_ARGUMENT_CONTEXT_MMAP_BEYOND_END_OF_FILE: ... */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_getpart(struct mfile *__restrict self,
              PAGEDIR_PAGEALIGNED pos_t addr,
              PAGEDIR_PAGEALIGNED size_t hint_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INVALID_ARGUMENT, ...);

/* Same as `mfile_getpart()', but may _only_ be used when `self' is an
 * anonymous file! As such, this  function is mainly used to  allocate
 * parts for `mfile_ndef' and `mfile_zero' */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_makepart(struct mfile *__restrict self,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);


struct mfile_extendpart_data {
	PAGEDIR_PAGEALIGNED pos_t  mep_minaddr;  /* Base address of an unmapped range to fill by extending another part. */
	pos_t                      mep_maxaddr;  /* Last byte of the gap that should be filled. */
	int                        _placeholder; /* ... */
};
#define mfile_extendpart_data_init(self) ((self)->_placeholder = 0)
#define mfile_extendpart_data_fini(self) ((self)->_placeholder = 0)

/* While holding a read- or write-lock to `self', try to extend an
 * existing mem-part that borders against the given address  range
 * in order to fill the specified gap.
 * This function assumes that:
 *  - @assume(mfile_lock_reading(self) || mfile_lock_writing(self));
 *  - @assume(data->mep_minaddr <= data->mep_maxaddr);
 *  - @assume(mfile_addr_aligned(self, data->mep_minaddr));
 *  - @assume(mfile_addr_aligned(self, data->mep_maxaddr + 1));
 *  - @assume(WAS_CALLED(mfile_extendpart_data_init(data)));
 *  - @assume(self->mf_parts != MFILE_PARTS_ANONYMOUS);
 *  - @assume(mfile_addr_ceilalign(self, self->mf_filesize) >= data->mep_maxaddr + 1);
 *  - @assume(!mpart_tree_rlocate(self->mf_parts, data->mep_minaddr, data->mep_maxaddr));
 * Locking logic:
 *   in:                                         mfile_lock_reading(self) || mfile_lock_writing(self)
 *   return == *:                                mfile_lock_writing(self) && undefined(out(data)) &&
 *                                               mpart_lock_acquired(return)
 *   return == MFILE_EXTENDPART_OR_UNLOCK_NOSIB: (mfile_lock_reading(self) || mfile_lock_writing(self)) &&
 *                                               undefined(out(data))
 *   return == MFILE_EXTENDPART_OR_UNLOCK_AGAIN: mfile_lock_end(self) && unlock()
 *   EXCEPT:                                     mfile_lock_end(self) && unlock()
 * @return: * : Success: A pointer to an extended mem-part that contains the entirety
 *                       of the address  range originally specified  in `data'.  Note
 *                       that in this case, you're inheriting a lock to that part.
 *                       Note: In this case, this function also guaranties that the
 *                       returned part doesn't exist in  SWAP, though it may  still
 *                       not be allowed (i.e. it's state may be MPART_ST_VOID)
 * @return: MFILE_EXTENDPART_OR_UNLOCK_NOSIB: (kind-of) success; the function was unable
 *                       to extend a pre-existing mem-part, but this is because there was
 *                       no such part to begin with: No existing part was neighboring, or
 *                       was even remotely close to the given address range, meaning that
 *                       extending such a part (if one even exists at all) would be  less
 *                       efficient than just creating a new, separate part.
 * @return: MFILE_EXTENDPART_OR_UNLOCK_AGAIN: The lock to `self' (and `unlock') was lost.
 *                       Simply re-acquire those locks and try again. Note that in this
 *                       case, the caller should always acquire a write-lock to `self'! */
FUNDEF WUNUSED NONNULL((1, 2)) struct mpart *FCALL
mfile_extendpart_or_unlock(struct mfile *__restrict self,
                           struct mfile_extendpart_data *__restrict data,
                           struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
#define MFILE_EXTENDPART_OR_UNLOCK_NOSIB ((REF struct mpart *)0)
#define MFILE_EXTENDPART_OR_UNLOCK_AGAIN ((REF struct mpart *)-1)


/* High-level wrapper for `mf_ops->mo_newpart' that automatically does
 * the  right  things when  `mf_ops->mo_newpart' hasn't  been defined.
 * This function doesn't  do any further  initialization than what  is
 * already described by `mf_ops->mo_newpart' */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mpart *FCALL
_mfile_newpart(struct mfile *__restrict self,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);


/* Look at the  neighbors of `part'  and try  to merge them  with `part'.  If
 * no neighbors exist,  or if those  neighbors are so  far away that  merging
 * with them  wouldn't be  efficient, then  simply insert  `part' as-is  into
 * the given mem-file  `self', before  adding `part'  to the  global list  of
 * parts (but only if it has the `MPART_F_GLOBAL_REF' flag set), and  finally
 * releasing a  lock to  `self', as  well as  re-returning a  pointer to  the
 * given part. -  For this  purpose, the  caller must  initialize the  `part'
 * reference    counter    of    `part'    as    `MPART_F_GLOBAL_REF ? 2 : 1'
 * If the `MPART_F_CHANGED' flag is set,  the given part, or the  combination
 * of  it and the to-be returned part will be added to the changed-part list.
 * However, if this is done, the caller is responsible for updating the file,
 * such  that  `MFILE_F_CHANGED'  is  set,  and  `mo_changed()'  is  invoked.
 * If merging was done, returning a reference to the new part against  within
 * the given `part'  was merged  (i.e. the  one that  was left  apart of  the
 * mem-part tree of `self')
 * This function assumes that:
 *  - @assume(mfile_lock_writing(self));
 *  - @assume(mfile_addr_aligned(self, part->mp_minaddr));
 *  - @assume(mfile_addr_aligned(self, part->mp_maxaddr + 1));
 *  - @assume(self->mf_parts != MFILE_PARTS_ANONYMOUS);
 *  - @assume(LIST_EMPTY(&part->mp_copy));
 *  - @assume(LIST_EMPTY(&part->mp_share));
 *  - @assume(UNINITIALIZED(&part->mp_allparts));
 *  - @assume(part->mp_refcnt == 1 + ((part->mp_flags & MPART_F_GLOBAL_REF) != 0) + ((part->mp_flags & MPART_F_CHANGED) != 0));
 *  - @assume(part->mp_file == self);
 *  - @assume(INITIALIZED(part->mp_*)); // All other fields...
 * @return: NULL: A pre-existing part overlaps with the address range of `part':
 *                mpart_tree_rlocate(self->mf_parts, part->mp_minaddr, part->mp_maxaddr) != NULL
 * @return: * :   A reference to a part that (at one point) contained a super-set
 *                of  the   address  range   described  by   the  given   `part'. */
FUNDEF WUNUSED NONNULL((1)) REF struct mpart *FCALL
mfile_insert_and_merge_part_and_unlock(struct mfile *__restrict self,
                                       /*inherit(on_success)*/ struct mpart *__restrict part)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);








/* Read/write raw data to/from a given mem-file. */
#ifdef CONFIG_USE_NEW_FS
FUNDEF WUNUSED NONNULL((1)) size_t KCALL mfile_read(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF WUNUSED NONNULL((1)) size_t KCALL mfile_read_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL mfile_readv(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL mfile_readv_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF WUNUSED NONNULL((1)) size_t KCALL mfile_tailread(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF WUNUSED NONNULL((1)) size_t KCALL mfile_tailread_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL mfile_tailreadv(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL mfile_tailreadv_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) void KCALL mfile_write(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_write_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_writev(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_writev_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) void KCALL mfile_tailwrite(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_tailwrite_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_tailwritev(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_tailwritev_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF WUNUSED NONNULL((1)) void KCALL mfile_readall(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF WUNUSED NONNULL((1)) void KCALL mfile_readall_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF WUNUSED NONNULL((1, 2)) void KCALL mfile_readvall(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF WUNUSED NONNULL((1, 2)) void KCALL mfile_readallv_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Same as the above, but these use an intermediate (stack) buffer for  transfer.
 * As such, these functions are called by the above when `memcpy_nopf()' produces
 * transfer errors that cannot be resolved by `mman_prefault()' */
FUNDEF NONNULL((1)) size_t KCALL _mfile_buffered_read(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL _mfile_buffered_write(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL _mfile_buffered_tailwrite(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) size_t KCALL _mfile_buffered_readv(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL _mfile_buffered_writev(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL _mfile_buffered_tailwritev(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
#endif /* CONFIG_USE_NEW_FS */

/* Helpers for directly reading to/from VIO space. */
#ifdef LIBVIO_CONFIG_ENABLED
FUNDEF NONNULL((1)) void KCALL mfile_vioread(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_viowrite(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1)) void KCALL mfile_vioread_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) void KCALL mfile_viowrite_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_vioreadv(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_viowritev(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_vioreadv_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_viowritev_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
#endif /* LIBVIO_CONFIG_ENABLED */

/* Builtin mem files */
#ifndef __mfile_phys_defined
#define __mfile_phys_defined
DATDEF struct mfile /*     */ mfile_phys;     /* Physical memory access (file position is physical memory address) */
#endif /* !__mfile_phys_defined */
DATDEF struct mfile_ops const mfile_phys_ops; /* ... */
#ifndef __mfile_ndef_defined
#define __mfile_ndef_defined
DATDEF struct mfile /*     */ mfile_ndef;     /* Random, uninitialized, anonymous memory. */
#endif /* !__mfile_ndef_defined */
DATDEF struct mfile_ops const mfile_ndef_ops; /* ... */
#ifndef __mfile_zero_defined
#define __mfile_zero_defined
DATDEF struct mfile /*     */ mfile_zero;     /* Zero-initialized, anonymous memory. */
#endif /* !__mfile_zero_defined */
DATDEF struct mfile_ops const mfile_zero_ops; /* ... */

/* Fallback  files for anonymous memory. These behave the same as `mfile_zero',
 * but one exists for every possible `mf_blockshift' (where the index into this
 * array is equal to that file's `mf_blockshift' value)
 * As such, these files are used by `mfile_delete()' as replacement mappings
 * of the original file. */
DATDEF struct mfile /*     */ mfile_anon[BITSOF(void *)];
DATDEF struct mfile_ops const mfile_anon_ops[BITSOF(void *)];


/* User-visible mem-file access API. (same as the handle access API) */
#ifdef CONFIG_USE_NEW_FS
FUNDEF WUNUSED NONNULL((1)) size_t KCALL mfile_uread(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF WUNUSED NONNULL((1)) size_t KCALL mfile_uwrite(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF WUNUSED NONNULL((1)) size_t KCALL mfile_upread(struct mfile *__restrict self, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
FUNDEF WUNUSED NONNULL((1)) size_t KCALL mfile_upwrite(struct mfile *__restrict self, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL mfile_ureadv(struct mfile *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL mfile_uwritev(struct mfile *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL mfile_upreadv(struct mfile *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
FUNDEF WUNUSED NONNULL((1, 2)) size_t KCALL mfile_upwritev(struct mfile *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) pos_t KCALL mfile_useek(struct mfile *__restrict self, off_t offset, unsigned int whence) THROWS(...);
FUNDEF NONNULL((1)) syscall_slong_t KCALL mfile_uioctl(struct mfile *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) void KCALL mfile_utruncate(struct mfile *__restrict self, pos_t new_size) THROWS(...);
FUNDEF NONNULL((1, 2)) void KCALL mfile_ummap(struct mfile *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
FUNDEF NONNULL((1)) pos_t KCALL mfile_uallocate(struct mfile *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
FUNDEF NONNULL((1)) void KCALL mfile_usync(struct mfile *__restrict self) THROWS(...);
FUNDEF NONNULL((1)) void KCALL mfile_udatasync(struct mfile *__restrict self) THROWS(...);
FUNDEF NONNULL((1)) void KCALL mfile_ustat(struct mfile *__restrict self, USER CHECKED struct stat *result) THROWS(...);
FUNDEF NONNULL((1)) void KCALL mfile_upollconnect(struct mfile *__restrict self, poll_mode_t what) THROWS(...);
FUNDEF WUNUSED NONNULL((1)) poll_mode_t KCALL mfile_upolltest(struct mfile *__restrict self, poll_mode_t what) THROWS(...);
FUNDEF NONNULL((1)) syscall_slong_t KCALL mfile_uhop(struct mfile *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
#endif /* CONFIG_USE_NEW_FS */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_H */
