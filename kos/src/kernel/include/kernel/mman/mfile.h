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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_H 1

#include <kernel/compiler.h>

#include <kernel/fs/notify-config.h> /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#include <kernel/malloc-defs.h>      /* ATTR_BLOCKLIKE_CC(...) */
#include <kernel/memory.h>
#include <kernel/types.h>
#include <misc/unlockinfo.h>
#include <sched/atomic64.h>
#include <sched/sig.h>

#include <hybrid/sched/__preemption.h>
#include <hybrid/sched/atomic-rwlock.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>

#include <bits/crt/format-printer.h>
#include <bits/os/timespec.h>
#include <kos/lockop.h>

#include <libvio/api.h> /* LIBVIO_CONFIG_ENABLED */

#ifdef __WANT_FS_INIT
#include <hybrid/__minmax.h>
#endif /* __WANT_FS_INIT */

#ifdef __WANT_MFILE__mf_compl
#include <sched/sigcomp.h>
#endif /* __WANT_MFILE__mf_compl */

#if (__SIZEOF_POINTER__ < 8 && defined(__WANT_MFILE_INIT_mf_filesize_symbol) && defined(__WANT_FS_INIT))
#include <hybrid/byteorder.h>
#endif /* __SIZEOF_POINTER__ < 8 && __WANT_MFILE_INIT_mf_filesize_symbol && __WANT_FS_INIT */

/*[[[config CONFIG_KERNEL_MFILE_TRACES_LOCKPC: bool = !defined(NDEBUG)
 * Trace program counters of write-locks to mfile objects.
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_MFILE_TRACES_LOCKPC
#undef CONFIG_KERNEL_MFILE_TRACES_LOCKPC
#elif !defined(CONFIG_KERNEL_MFILE_TRACES_LOCKPC)
#ifndef NDEBUG
#define CONFIG_KERNEL_MFILE_TRACES_LOCKPC
#else /* !NDEBUG */
#define CONFIG_NO_KERNEL_MFILE_TRACES_LOCKPC
#endif /* NDEBUG */
#elif (-CONFIG_KERNEL_MFILE_TRACES_LOCKPC - 1) == -1
#undef CONFIG_KERNEL_MFILE_TRACES_LOCKPC
#define CONFIG_NO_KERNEL_MFILE_TRACES_LOCKPC
#endif /* ... */
/*[[[end]]]*/


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
 *    - mfile_truncate()   (throws: E_FSERROR_READONLY)
 *    - mfile_tailread()   (for offsets >= mf_filesize: blocks forever)
 *    - mfile_tailwrite()  (THROW(E_FSERROR_FILE_TOO_BIG))
 *    - mfile_read()       (for offsets >= mf_filesize: returns `0')
 *    - mfile_write()      (for offsets >= mf_filesize: THROW(E_FSERROR_FILE_TOO_BIG))
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


struct handle_mmap_info;
struct stat;
struct path;
struct fdirent;
struct handle;
struct ccinfo;

#ifndef __fallocate_mode_t_defined
#define __fallocate_mode_t_defined
typedef unsigned int fallocate_mode_t; /* TODO */
#endif /* !__fallocate_mode_t_defined */

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
	 * @param: access_path: [0..1] The path by which the open is being performed (if available)
	 * @param: access_dent: [0..1] The directory entry of `self' (if available)
	 * @param: oflags:      Additional open-flags. Set of: `0 | O_NOCTTY'
	 *                      All other flags  should be silently  ignored.
	 * HINT: `hand' is initialized as follows upon entry:
	 * >> hand->h_type = HANDLE_TYPE_MFILE;
	 * >> hand->h_mode = ...; // Depending on o-flags passed to open(2).
	 * >> hand->h_data = incref(self);
	 * NOTE: `h_data' is reference on entry (when modified, you must
	 *       `decref_nokill(self)'  and  assign   `incref(new_obj)') */
	BLOCKING NONNULL_T((1, 2)) void
	(KCALL *mso_open)(struct mfile *__restrict self,
	                  /*in|out*/ REF struct handle *__restrict hand,
	                  struct path *access_path,
	                  struct fdirent *access_dent,
	                  oflag_t oflags);

	/* [0..1] Hooks  for `read(2)' and  `readv(2)': stream-oriented file reading.
	 * Note that for consistency, anything that implements these operators should
	 * either document that read(2) returns different data than pread(2)/mmap(2),
	 * or disallow use of the later with `mf_filesize = 0, MFILE_F_FIXEDFILESIZE' */
	BLOCKING WUNUSED_T NONNULL_T((1)) size_t
	(KCALL *mso_read)(struct mfile *__restrict self, NCX void *dst,
	                  size_t num_bytes, iomode_t mode) THROWS(...);
	BLOCKING WUNUSED_T NONNULL_T((1, 2)) size_t
	(KCALL *mso_readv)(struct mfile *__restrict self, struct iov_buffer *__restrict dst,
	                   size_t num_bytes, iomode_t mode) THROWS(...);

	/* [0..1] Hooks  for `write(2)' and  `writev(2)': stream-oriented file writing.
	 * Note that for consistency, anything  that implements these operators  should
	 * either document that write(2) affects different data than pwrite(2)/mmap(2),
	 * or disallow use of the later with `mf_filesize = 0, MFILE_F_FIXEDFILESIZE' */
	BLOCKING WUNUSED_T NONNULL_T((1)) size_t
	(KCALL *mso_write)(struct mfile *__restrict self, NCX void const *src,
	                   size_t num_bytes, iomode_t mode) THROWS(...);
	BLOCKING WUNUSED_T NONNULL_T((1, 2)) size_t
	(KCALL *mso_writev)(struct mfile *__restrict self, struct iov_buffer *__restrict src,
	                    size_t num_bytes, iomode_t mode) THROWS(...);


	/* [0..1] Hooks for `pread(2)' and `pwrite(2)'.
	 * The pread/pwrite callbacks are only called by handle_pread() and handle_pwrite(),
	 * and  if  not given,  will default  to  using `mfile_read()'  and `mfile_write()'. */
	BLOCKING WUNUSED_T NONNULL_T((1)) size_t
	(KCALL *mso_pread)(struct mfile *__restrict self, NCX void *dst,
	                   size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
	BLOCKING WUNUSED_T NONNULL_T((1, 2)) size_t
	(KCALL *mso_preadv)(struct mfile *__restrict self, struct iov_buffer *__restrict dst,
	                    size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
	BLOCKING WUNUSED_T NONNULL_T((1)) size_t
	(KCALL *mso_pwrite)(struct mfile *__restrict self, NCX void const *src,
	                    size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
	BLOCKING WUNUSED_T NONNULL_T((1, 2)) size_t
	(KCALL *mso_pwritev)(struct mfile *__restrict self, struct iov_buffer *__restrict src,
	                     size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);

	/* [0..1] Hook for `lseek(2)': stream-oriented file seeking. */
	BLOCKING NONNULL_T((1)) pos_t
	(KCALL *mso_seek)(struct mfile *__restrict self, off_t offset,
	                  unsigned int whence) THROWS(...);

	/* [0..1] Hook for `ftruncate(2)': File length setting.
	 * If defined, this callback will only be called by  `handle_mfile_truncate()',
	 * where  it  will take  the  place of  the  usual call  to `mfile_truncate()'.
	 * Note that this callback will  _not_ be called by `mfile_truncate()'  itself,
	 * and that `handle_mfile_truncate()' will not call  the later if this one  was
	 * called first, meaning that this callback itself must call `mfile_truncate()'
	 * when conventional file-truncation behavior is wanted. */
	BLOCKING NONNULL_T((1)) void
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
	BLOCKING NONNULL_T((1, 2)) void
	(KCALL *mso_mmap)(struct mfile *__restrict self,
	                  struct handle_mmap_info *__restrict info)
			THROWS(...);

	/* [0..1] Override   for   `fallocate(2)':  File   data  pre-allocations.
	 * You may define this function to override the default behavior for pre-
	 * loading parts of a given file. By default, `mfile_preload() (TODO)' is
	 * used to pre-allocate  mem-parts, as well  as initialize their  backing
	 * memory.
	 * @return: * : The amount of newly allocated bytes. */
	BLOCKING NONNULL_T((1)) pos_t
	(KCALL *mso_allocate)(struct mfile *__restrict self,
	                      fallocate_mode_t mode,
	                      pos_t start, pos_t length)
			THROWS(...);

	/* [0..1] Additional information for `stat(2)': File information.
	 * This operator is entirely optional, and may be used to fill in
	 * additional file information that  wasn't already filled in  by
	 * the caller. By default, the caller will have already filled:
	 *   - st_nlink   = 1;
	 *   - st_size    = mfile_getsize(self);
	 *   - st_blksize = mfile_getblocksize(self);
	 *   - st_blocks  = mfile_getblockcount(self);
	 *   - st_atim    = mf_atime;
	 *   - st_mtim    = mf_mtime;
	 *   - st_ctim    = mf_ctime;
	 *   - st_btim    = mf_btime;
	 *   - All other fields have been pre-initialized to zero
	 * As such, only the following fields always have fixed values:
	 *   - st_dev
	 *   - st_ino
	 *   - st_mode
	 *   - st_nlink
	 *   - st_uid
	 *   - st_gid
	 *   - st_rdev */
	BLOCKING NONNULL_T((1)) void
	(KCALL *mso_stat)(struct mfile *__restrict self,
	                  NCX struct stat *result)
			THROWS(...);

	/* [0..1] Implementation for poll(2): Connect to signals.
	 * When not implemented, `handle_pollconnect()' simply behaves as a no-op */
	BLOCKING NONNULL_T((1)) void
	(KCALL *mso_pollconnect)(struct mfile *__restrict self,
	                         poll_mode_t what)
			THROWS(...);

	/* [0..1] Implementation  for  poll(2):  Connect  to  signals.
	 * When not implemented, `handle_polltest()' always indicates:
	 *  - readable: when `MFILE_F_NOUSRIO' isn't set, or `mso_read' or `mso_readv' are defined
	 *  - writable: when `MFILE_F_NOUSRIO' isn't set, or `mso_write' or `mso_writev' are defined
	 */
	BLOCKING WUNUSED_T NONNULL_T((1)) poll_mode_t
	(KCALL *mso_polltest)(struct mfile *__restrict self,
	                      poll_mode_t what)
			THROWS(...);

	/* [0..1] Hook for `ioctl(2)': Extended file I/O control.
	 * Note that no standard ioctl commands are defined for mem-files, meaning that
	 * this callback has completely unfiltered control over the `ioctl(2)' syscall.
	 * When `NULL', same as `mfile_v_ioctl'. */
	BLOCKING NONNULL_T((1)) syscall_slong_t
	(KCALL *mso_ioctl)(struct mfile *__restrict self, ioctl_t cmd,
	                   NCX UNCHECKED void *arg, iomode_t mode)
			THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...);

	/* [0..1] Try  to cast the given mem-file into a different handle type.
	 * When this operator isn't defined, the mem-file cannot be cast to any
	 * other  handle type. Note  that you may  assume that `wanted_type' is
	 * never given as `HANDLE_TYPE_MFILE'.
	 * @param: wanted_type: The requested handle type.
	 * @return: NULL:       Cannot cast to `wanted_type'. */
	BLOCKING WUNUSED_T NONNULL_T((1)) REF void *
	(KCALL *mso_tryas)(struct mfile *__restrict self, uintptr_half_t wanted_type)
			THROWS(...);

	/* [0..1] Print the text which should appear under `readlink("/proc/[pid]/fd/[fdno]")' */
	BLOCKING NONNULL_T((1, 2)) ssize_t
	(KCALL *mso_printlink)(struct mfile *__restrict self, __pformatprinter printer, void *arg)
			THROWS(E_WOULDBLOCK, ...);

	/* [0..1] Additional callback that should be invoked during `fsync()' / `fdatasync()' */
	BLOCKING NONNULL_T((1)) void
	(KCALL *mso_sync)(struct mfile *__restrict self)
			THROWS(E_WOULDBLOCK, E_IOERROR, ...);

	/* [0..1] Clear internal object caches.
	 * Generally speaking, locking done by this function should locks like:
	 * >> if (!mylock_tryacquire(self)) {
	 * >>     if (ccinfo_noblock(info))
	 * >>         return 0; // Not allowed to block :(
	 * >>     if (!mylock_acquire_nx(self))
	 * >>         return 0; // Cannot acquire lock...
	 * >> }
	 * >> ...
	 * >> mylock_release(self); */
	ATTR_BLOCKLIKE_CC(info) NONNULL_T((1)) void
	NOTHROW_T(KCALL *mso_cc)(struct mfile *__restrict self,
	                         struct ccinfo *__restrict info);

#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
	/* [0..1] Operator pair used for creating/destroying additional cookie objects
	 *        that remain alive for as long as `mfm_notify != NULL' (iow: for as
	 *        long as fs events are being tracked for a file)
	 *
	 * These operators can be used to start/stop object-specific async jobs for
	 * the purpose of polling signals and generating file notification  events:
	 *  - `mso_notify_attach' is called when a `struct inotify_controller' is created
	 *  - `mso_notify_detach' is called when a `struct inotify_controller' is destroyed
	 *
	 * WARNING: `wasdestroyed(self)' may be the case when `mso_notify_detach' is called,
	 *          but  in this case  it is guarantied that  (aside from `mfm_notify'), all
	 *          other fields of `self' remain in a valid state until after the  operator
	 *          returns (though the operator still isn't allowed to incref(self)!)
	 *
	 * NOTE: `mso_notify_attach' _is_ allowed to incref(self), and have `mso_notify_detach'
	 *       be the one to eventually decref() it. HOWEVER! If you do this, the system will
	 *       have a harder time trying  to unload unused files in  those cases where it  is
	 *       the containing directory that is being watched (rather than the file  itself),
	 *       because  `system_cc()' won't  be able to  identify `self' as  unused until the
	 *       user stops watching the containing directory (it is recommended to use `AWREF'
	 *       to reference the attached mfile and clear that reference in mso_notify_detach)
	 *
	 * @return: * : Cookie object to store alongside the `struct inotify_controller'.
	 *              Whatever  is returned here (even if it's NULL) will eventually be
	 *              passed to `mso_notify_detach' when the notify is detached. */
	BLOCKING NONNULL_T((1)) void *
	(KCALL *mso_notify_attach)(struct mfile *__restrict self) THROWS(E_BADALLOC, ...);
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(KCALL *mso_notify_detach)(struct mfile *__restrict self, void *cookie);
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */

};

/* Default ioctl(2) operator for mfile-s. Implements:
 *  - FS_IOC_GETFLAGS, FS_IOC_SETFLAGS
 *  - FS_IOC_GETFSLABEL, FS_IOC_SETFSLABEL
 *  - BLKROSET, BLKROGET, BLKFLSBUF
 *  - BLKSSZGET, BLKBSZGET,
 *  - BLKGETSIZE, BLKGETSIZE64
 *  - FILE_IOC_BLKSHIFT
 *  - FILE_IOC_MSALIGN
 *  - FILE_IOC_SUBREGION
 *  - FILE_IOC_DELREGION
 *  - FILE_IOC_TAILREAD
 *  - FILE_IOC_TRIM
 *  - FILE_IOC_GETFS*
 */
FUNDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL
mfile_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
              NCX UNCHECKED void *arg, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...);

/* Constructs a wrapper object that implements seeking, allowing normal reads/writes to
 * be dispatched via `mfile_upread()' and `mfile_upwrite()' (which uses the `mso_pread'
 * and `mso_pwrite' operators, with `mfile_read()' and `mfile_write()' as fallback, so-
 * long as `MFILE_F_NOUSRIO' isn't set)
 *
 * The operators of the following system calls are forwarded 1-on-1 to `mfile_u*':
 *   - pread(2), preadv(2), pwrite(2), pwritev(2)
 *   - ioctl(2), truncate(2), mmap(2), fallocate(2)
 *   - fsync(2), fdatasync(2), stat(2), poll(2)
 * As stated, `lseek(2)', `read(2)' and `write(2)' are dispatched via pread/pwrite
 *
 * This function is actually used when trying to open a mem-file with neither
 * `mso_read'/`mso_readv', nor `mso_write'/`mso_writev' pre-defined. As such,
 * open(2)-ing a generic mfile object uses `mfile_open()' (see below). */
FUNDEF NONNULL((1, 2)) void KCALL
mfile_v_open(struct mfile *__restrict self,
             /*in|out*/ REF struct handle *__restrict hand,
             struct path *access_path, struct fdirent *access_dent,
             oflag_t oflags)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Generic open function for arbitrary  mem-file objects. This function  is
 * unconditionally invoked during a call to `open(2)' in order to construct
 * wrapper objects and the like. This function is implemented as:
 *
 * >> struct mfile_stream_ops const *stream = self->mf_ops->mo_stream;
 * >> if (!stream) {
 * >>     mfile_v_open(self, hand, access_path, access_dent, oflags);
 * >> } else if (stream->mso_open) {
 * >>     (*stream->mso_open)(self, hand, access_path, access_dent, oflags);
 * >> } else if (!stream->mso_read && !stream->mso_readv &&
 * >>            !stream->mso_write && !stream->mso_writev) {
 * >>     mfile_v_open(self, hand, access_path, access_dent, oflags);
 * >> } else {
 * >>     // Open mfile itself (iow: `hand->h_data == self')
 * >> } */
FUNDEF BLOCKING NONNULL((1, 2)) void KCALL
mfile_open(struct mfile *__restrict self, struct handle *__restrict hand,
           struct path *access_path, struct fdirent *access_dent,
           oflag_t oflags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

struct aio_multihandle;

/* Helper wrapper for invocation of `mfile_ops::mo_loadblocks' and `mfile_ops::mo_saveblocks'
 * within  a synchronous context. This function will invoke `io' with a locally allocated AIO
 * handle before proceeding to wait for I/O to complete.
 *
 * If the calling thread is interrupted during  waiting, I/O is canceled and the  function
 * returned with an exception. Otherwise, the function returns normally once I/O completed
 * successfully. In the event of an I/O error, this function will re-throw said error. */
FUNDEF BLOCKING NONNULL((1, 2)) void KCALL
mfile_dosyncio(struct mfile *__restrict self,
               NONNULL_T((1, 5)) void (KCALL *io)(struct mfile *__restrict self, pos_t addr,
                                                  physaddr_t buf, size_t num_bytes,
                                                  struct aio_multihandle *__restrict aio),
               pos_t addr, physaddr_t buf, size_t num_bytes);

/* Read/Write whole file blocks using direct I/O
 * @assume(IS_ALIGNED(buf, (size_t)1 << self->mf_iobashift));
 * @assume(IS_ALIGNED(addr, mfile_getblocksize(self)));
 * @assume(IS_ALIGNED(num_bytes, mfile_getblocksize(self)));
 * @assume(addr + num_bytes <= self->mf_filesize);
 * @assume(num_bytes != 0);
 * @assume(self->mf_trunclock != 0);
 *
 * As you can see, in order to do direct I/O, you need to fulfill 2 different  alignment
 * constraints (but note that `self->mf_iobashift <= self->mf_blockshift'), meaning that
 * it's also good enough to only fulfill `self->mf_blockshift'. As such:
 *   - (size_t)1 << self->mf_blockshift: This is the size of a logical data-block, as well
 *                                       as  the granularity of allowed buffer sizes, such
 *                                       that only whole blocks can be read/written.
 *   - (size_t)1 << self->mf_iobashift:  This is the required alignment for `buf', that  is
 *                                       the  alignment required of DMA buffers. This tends
 *                                       to be less than `mf_blockshift', but in many cases
 *                                       (including  those of ramfs-based files), it simply
 *                                       is equal to `mf_blockshift'. */
#define mfile_rdblocks_async(self, addr, buf, num_bytes, aio) mfile_doasyncio(self, (self)->mf_ops->mo_loadblocks, addr, buf, num_bytes, aio)
#define mfile_wrblocks_async(self, addr, buf, num_bytes, aio) mfile_doasyncio(self, (self)->mf_ops->mo_saveblocks, addr, buf, num_bytes, aio)
#define mfile_rdblocks(self, addr, buf, num_bytes)            mfile_dosyncio(self, (self)->mf_ops->mo_loadblocks, addr, buf, num_bytes)
#define mfile_wrblocks(self, addr, buf, num_bytes)            mfile_dosyncio(self, (self)->mf_ops->mo_saveblocks, addr, buf, num_bytes)
#define mfile_haverdblocks(self)                              ((self)->mf_ops->mo_loadblocks != __NULLPTR)
#define mfile_havewrblocks(self)                              ((self)->mf_ops->mo_saveblocks != __NULLPTR)

#ifdef NDEBUG
#define mfile_doasyncio(self, io, addr, buf, num_bytes, aio) \
	((*io)(self, addr, buf, num_bytes, aio))
#else /* NDEBUG */
FUNDEF BLOCKING NONNULL((1, 2)) void
(KCALL mfile_doasyncio)(struct mfile *__restrict self,
                        NONNULL_T((1, 5)) void (KCALL *io)(struct mfile *__restrict self, pos_t addr,
                                                           physaddr_t buf, size_t num_bytes,
                                                           struct aio_multihandle *__restrict aio),
                        pos_t addr, physaddr_t buf, size_t num_bytes,
                        struct aio_multihandle *__restrict aio)
		ASMNAME("mfile_doasyncio_dbg");
#endif /* !NDEBUG */

/* Helper macros for low-level block sizes */
#define mfile_getblockshift(self) (self)->mf_blockshift
#define mfile_getblocksize(self)  ((size_t)1 << (self)->mf_blockshift)
#define mfile_getblockmask(self)  (mfile_getblocksize(self) - 1)

/* For these 2, the caller must be holding a trunc-lock, or `MFILE_F_FIXEDFILESIZE' must be set.
 * NOTE: For the `*_nonatomic' versions, `MFILE_F_FIXEDFILESIZE' must be set unconditionally. */
#define mfile_getsize(self)           ((pos_t)atomic64_read(&(self)->mf_filesize))
#define mfile_getsize_nonatomic(self) ((pos_t)_atomic64_val((self)->mf_filesize))
#define mfile_getblockcount(self)     (mfile_getsize(self) >> (self)->mf_blockshift)


struct mfile_ops {
	/* [0..1] Finalize + free the given mem-file.
	 * The caller will  have already finalized  all mfile-fields,  and
	 * this operator is now supposed to finalize any sub-class fields,
	 * as well as kfree(self). */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(KCALL *mo_destroy)(struct mfile *__restrict self);

	/* [0..1] Construct a new given mem-part. When not implemented, use the default
	 *        mechanism for the creation of new mem-parts.
	 * This function is mainly intended to be used by `mfile_pyhs' in order to create
	 * custom, already-initialized mem-parts for use with a given physical  location.
	 * NOTE: This function may assume that the given address range is aligned by `mf_part_amask'.
	 * The following fields should _NOT_ already be initialized by this
	 * function, and will unconditionally be initialized by the caller:
	 *  - mp_refcnt                      (Initialized to whatever is the correct value)
	 *  - mp_xflags = MPART_XF_NORMAL;
	 *  - mp_flags & MPART_F_GLOBAL_REF  (Set if `self' isn't anonymous)
	 *  - mp_flags & MPART_F_LOCKBIT     (Must not be set)
	 *  - mp_flags & MPART_F_CHANGED     (Must not be set)
	 *  - mp_flags & MPART_F__RBRED      (Needed of the file-tree)
	 *  - mp_file                        (Set to `self' or `mfile_anon[*]')
	 *  - mp_copy                        (Initialized as empty)
	 *  - mp_share                       (Initialized as empty)
	 *  - mp_lockops                     (Initialized as empty)
	 *  - mp_allparts                    (The part (may be) added to the all-list only
	 *                                    _after_ all other fields were initialized)
	 *  - mp_minaddr                     (Set to `minaddr' by the caller)
	 *  - mp_maxaddr                     (Set to `minaddr + num_bytes - 1' by the caller)
	 *  - mp_changed                     (Intentionally left uninitialized)
	 *  - mp_filent                      (Needed of the file-tree; set to indicate
	 *                                    an anon-part if `self' was anonymous)
	 * As such, this function may only initialize:
	 *  - mp_flags & ...                 (All flags except for the above)
	 *  - mp_state                       (usually `MPART_ST_VOID' or `MPART_ST_MEM')
	 *  - mp_blkst_ptr / mp_blkst_inl    (Containing the fully initialized initial block-status bitset)
	 *  - mp_mem / mp_mem_sc / ...       (Containing the initial backing storage location; s.a. `mp_state')
	 *  - mp_meta                        (usually `NULL') */
	ATTR_RETNONNULL_T NONNULL_T((1)) REF struct mpart *
	(KCALL *mo_newpart)(struct mfile *__restrict self,
	                    PAGEDIR_PAGEALIGNED pos_t minaddr,
	                    PAGEDIR_PAGEALIGNED size_t num_bytes)
			THROWS(E_WOULDBLOCK, E_BADALLOC);

	/* NOTE: Don't get any ideas about adding IOV support for mo_loadblocks/mo_saveblocks (again).
	 *
	 * Since these functions  include AIO  support, IOV could  simply be  implemented on-top  of
	 * AIO  by invoking the callback once for every IOV entry (using the same AIO multi-handle).
	 * Afterwards, just do the normal waitfor-and-cancel-on-error-then-rethrow-io-error sequence
	 * to wait for all of  the operations to complete, whilst  allowing hardware to perform  all
	 * of the read/write operations (potentially) in parallel! */

	/* [0..1][if(!mfile_isanon(self), [1..1])]
	 * Load/initialize the given physical memory buffer (this is the read-from-disk callback)
	 * This  operator _must_ be implemented for files  that aren't anonymous from the get-go!
	 * @assume(IS_ALIGNED(buf, (size_t)1 << self->mf_iobashift));
	 * @assume(IS_ALIGNED(addr, mfile_getblocksize(self)));
	 * @assume(IS_ALIGNED(num_bytes, mfile_getblocksize(self)));
	 * @assume(addr + num_bytes <= mfile_partaddr_ceilalign(self, self->mf_filesize));
	 * @assume(num_bytes != 0);
	 * @assume(self->mf_trunclock != 0 || (self->mf_flags & MFILE_F_FIXEDFILESIZE));
	 * @assume(!(self->mf_flags & MFILE_F_DELETING));
	 * NOTE: This callback must _NOT_ invoke `aio_multihandle_done(aio)' (that's the caller's job)
	 * NOTE: This function is allowed to be BLOCKING, but must still guaranty not to do so
	 *       indefinitely,  as it may be called in the context of async workers, which may
	 *       otherwise become locked-up. The intend is to use `aio' if the operation would
	 *       need to block for an unspecified amount of time. */
	BLOCKING NONNULL_T((1, 5)) void
	(KCALL *mo_loadblocks)(struct mfile *__restrict self, pos_t addr,
	                       physaddr_t buf, size_t num_bytes,
	                       struct aio_multihandle *__restrict aio)
			THROWS(E_IOERROR, ...);

	/* [0..1]
	 * Save/write-back the given physical memory buffer (this is the write-to-disk callback)
	 * @assume(IS_ALIGNED(buf, (size_t)1 << self->mf_iobashift));
	 * @assume(IS_ALIGNED(addr, mfile_getblocksize(self)));
	 * @assume(IS_ALIGNED(num_bytes, mfile_getblocksize(self)));
	 * @assume(addr + num_bytes <= mfile_partaddr_ceilalign(self, self->mf_filesize));
	 * @assume(num_bytes != 0);
	 * @assume(self->mf_trunclock != 0 || (self->mf_flags & MFILE_F_FIXEDFILESIZE));
	 * @assume(!(self->mf_flags & MFILE_F_DELETING));
	 * NOTE: This callback must _NOT_ invoke `aio_multihandle_done(aio)' (that's the caller's job)
	 * NOTE: This function is allowed to be BLOCKING, but must still guaranty not to do so
	 *       indefinitely,  as it may be called in the context of async workers, which may
	 *       otherwise become locked-up. The intend is to use `aio' if the operation would
	 *       need to block for an unspecified amount of time. */
	BLOCKING NONNULL_T((1, 5)) void
	(KCALL *mo_saveblocks)(struct mfile *__restrict self, pos_t addr,
	                       physaddr_t buf, size_t num_bytes,
	                       struct aio_multihandle *__restrict aio)
			THROWS(E_IOERROR, ...);

	/* [0..1]
	 * Deallocate file blocks from disk (blocks are lazily allocated by `mo_saveblocks')
	 * @assume(IS_ALIGNED(minaddr, mfile_getblocksize(self)));
	 * @assume(IS_ALIGNED(maxaddr + 1, mfile_getblocksize(self)));
	 * @assume(maxaddr + 1 <= mfile_partaddr_ceilalign(self, self->mf_filesize)); // Assuming no overflows
	 * @assume(minaddr <= maxaddr);
	 * @assume(self->mf_trunclock == 0);
	 * @assume(self->mf_flags & MFILE_F_DELETING); // Caller is thread that set `MFILE_F_DELETING'
	 * @assume(!(self->mf_flags & MFILE_F_FIXEDFILESIZE)); */
	BLOCKING NONNULL_T((1)) void
	(KCALL *mo_freeblocks)(struct mfile *__restrict self,
	                       pos_t minaddr, pos_t maxaddr)
			THROWS(E_IOERROR, ...);

	/* [0..1] Called after `MFILE_F_CHANGED' and/or `MFILE_F_ATTRCHANGED' becomes set.
	 * @param: oldflags: Old file flags. (set of `MFILE_F_*')
	 * @param: newflags: New file flags. (set of `MFILE_F_*')
	 *                   Contains at least one of `MFILE_F_CHANGED | MFILE_F_ATTRCHANGED'
	 *                   that wasn't already contained in `oldflags' */
	NOBLOCK NONNULL_T((1)) void
	NOTHROW_T(KCALL *mo_changed)(struct mfile *__restrict self,
	                             uintptr_t oldflags, uintptr_t newflags);

	/* [0..1] Stream operators. */
	struct mfile_stream_ops const *mo_stream;

#ifdef LIBVIO_CONFIG_ENABLED
	/* [0..1] VIO file operators. When non-NULL,  then this file is backed  by
	 * VIO, and the `mo_loadblocks' and `mo_saveblocks' operators are ignored,
	 * though should still be set to `NULL' for consistency. */
	struct vio_ops const *mo_vio;
#endif /* LIBVIO_CONFIG_ENABLED */
};


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
 *  0x00000800  MFILE_FN_NODIRATIME    ST_NODIRATIME       MS_NODIRATIME
 *  0x00010000                                             MS_POSIXACL
 *  0x00020000                                             MS_UNBINDABLE
 *  0x00200000  MFILE_F_RELATIME                           MS_RELATIME
 *  0x01000000  MFILE_F_STRICTATIME                        MS_STRICTATIME
 *  0x02000000  MFILE_F_LAZYTIME                           MS_LAZYTIME
 * ```
 */

/* Flags for `struct mfile::mf_flags' */
#define MFILE_F_NORMAL          0x00000000 /* Normal flags. */
#define MFILE_F_READONLY        0x00000001 /* [lock(READ:  mf_lock || mpart_lock_acquired(ANY(mf_parts)),
                                            *       WRITE: mf_lock && mpart_lock_acquired(ALL(mf_parts)))]
                                            * Disallow `mfile_write()', as  well as `PROT_WRITE|PROT_SHARED'  mappings.
                                            * Attempting to do either will result in `E_FSERROR_READONLY' being thrown.
                                            *
                                            * NOTE: If intending to set this flag, you should probably precede this  by
                                            *       a call to `mfile_parts_denywrite_or_unlock()'. Else, existing write
                                            *       mappings of file parts will continue to have that access! */
#define MFILE_FS_NOSUID         0x00000002 /* [lock(ATOMIC)] fsuper-specific: Ignore `S_ISGID' and `S_ISUID' bits. */
#define MFILE_FN_GLOBAL_REF     0x00000004 /* [lock(CLEAR(ATOMIC), SET(<WAS_SET_PREVIOUSLY> && !MFILE_F_DELETED &&
                                            *                          _MFILE_F_SMP_TSLOCK && fall[nodes|super]_acquired()))]
                                            * fnode-specific: The global list of fnode-s or fsuper-s holds a reference to this one. */
#define MFILE_FS_NOEXEC         0x00000008 /* [lock(ATOMIC)] fsuper-specific: Disallow execution of files. */
/*      MFILE_F_                0x00000010  * ... Reserved: MS_SYNCHRONOUS */
#define MFILE_F_DELETED         0x00000020 /* [lock(WRITE_ONCE)] The file has been marked as  deleted. When this flag is  set,
                                            * new parts may be created with `mfile_anon[*]' set for their pointed-to `mp_file'
                                            * field. This  flag also  means that  `mfile_isanon(self)' and  `mf_filesize == 0'
                                            * will be the case  sooner or later, though  this may not be  the case yet,  since
                                            * file anonymization &  all of  that jazz  happens asynchronously  through use  of
                                            * lockops!
                                            * Note  that this flag  implies `MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE', but also
                                            * negates `MFILE_F_READONLY' for memory mappings (since those will eventually become
                                            * anonymous, at which point write access is  once again allowed). But note that  the
                                            * delete-operation itself will eventually be allowed to set the file's size to  `0'.
                                            * Once async deletion is complete, the file's part-tree and changed-list will be set
                                            * to  MFILE_PARTS_ANONYMOUS, the file will have a size  of `0', and all of its used-
                                            * to-be parts will be anon, too.
                                            * Once `mfile_delete()' has set this flag, `mf_initdone' is broadcast */
/*      MFILE_F_                0x00000040  * ... Reserved: MS_MANDLOCK */
/*      MFILE_F_                0x00000080  * ... Reserved: MS_DIRSYNC */
#define MFILE_F_ATTRCHANGED     0x00000100 /* [lock(SET(ATOMIC), CLEAR(WEAK))][const_SET_if(MFILE_F_DELETED)]
                                            * Indicates that attributes of this file (its size, etc.) have changed. */
#define MFILE_F_CHANGED         0x00000200 /* [lock(SET(ATOMIC), CLEAR(WEAK))][const_SET_if(MFILE_F_DELETED)]
                                            * This flag is set before `mo_changed()' is invoked, which also won't
                                            * be  invoked again until  this flag has been  cleared, which is done
                                            * as part of a call to `mfile_sync()' */
#define MFILE_F_NOATIME         0x00000400 /* [lock(ATOMIC)][const_if(MFILE_F_DELETED)] Don't modify the value of `mf_atime' */
#define MFILE_FN_NODIRATIME     0x00000800 /* [lock(ATOMIC)][const_if(MFILE_F_DELETED)] Don't update `mf_atime' during path traversal */
#define MFILE_F_NOUSRMMAP       0x00001000 /* [lock(ATOMIC)] Disallow user-space from mmap(2)-ing this file. (ignored when `mso_mmap' is defined) */
#define MFILE_F_NOUSRIO         0x00002000 /* [lock(ATOMIC)] Disallow  user-space  from  pread(2)-ing or  pwrite(2)-ing  this file.
                                            * Doesn't affect `mso_pread' and `mso_pwrite'; only `mfile_read()' and `mfile_write()'. */
#define MFILE_F_NOMTIME         0x00004000 /* [lock(ATOMIC)][const_if(MFILE_F_DELETED)] Don't modify the value of `mf_mtime' */
#define MFILE_F_DELETING        0x00008000 /* [lock(ATOMIC)] Special flag  to indicate  that the  file
                                            * (may be) about to be deleted. In order to set this flag:
                                            * - self->mf_trunclock == 0
                                            * - mfile_lock_writing(self)
                                            * - mpart_lock_acquired(self->mf_parts->*)
                                            * - For all parts that overlap with the address range that should get deleted:
                                            *   - Address ranges belonging to MAP_PRIVATE mappings have been loaded (block status LOAD or CHNG)
                                            *   - Address ranges belonging to MAP_SHARED mappings had their write-access revoked
                                            * After setting the flag (NOT done by `mfile_deleting_begin_locked_or_unlock()'):
                                            * - Either call `mfile_msalign_makeanon_locked_or_unlock()' for the range you wish to delete
                                            * - Or recursively  call `mfile_deleting_begin_locked_or_unlock()'  to set  `MFILE_F_DELETING'
                                            *   for all misaligned sub-files. In this variant, caches of misaligned sub-files are not lost
                                            *   when  the delete-operation needs to be rolled back (e.g. `unlink(2)' notices that the file
                                            *   still has additional  hard-links), however  also requires that  misaligned sub-files  that
                                            *   were marked as DELETING are kept track dynamically.
                                            * When the flag is set:
                                            * - Not allowed to increment `self->mf_trunclock'
                                            * - Not allowed to fault a `MAP_SHARED' file mappings
                                            * - Not allowed to increase `self->mf_filesize'
                                            * - Not allowed to decrease `self->mf_filesize' (except in thread that set `MFILE_F_DELETING')
                                            * - Not  allowed to trim any part of the file that is used by a MAP_PRIVATE mapping
                                            *   If the file is a misaligned sub-file, then this restriction also applies if the
                                            *   underlying file has this flag set.
                                            * - Not allowed to create new misaligned sub-files  (`mf_msalign'), though existing ones can be  used.
                                            *   This is important to ensure that the set of misaligned sub-files doesn't change (since `unlink(2)'
                                            *   sets the `MFILE_F_DELETING' flag  for all misaligned  sub-files so-as not  to necessarily have  to
                                            *   unload *everything* in case the file being deleted has extra hard-links)
                                            * After clearing this flag, `mf_initdone' is broadcast */
/*      MFILE_F_                0x00010000  * ... Reserved: MS_POSIXACL */
/*      MFILE_F_                0x00020000  * ... Reserved: MS_UNBINDABLE */
#define MFILE_F_PERSISTENT      0x00040000 /* [lock(CLEAR_ONCE)] Parts of this file should not be unloaded to free up
                                            * memory, even if it may appear  as though no external references  (other
                                            * than MPART_F_GLOBAl_REF) exist for those parts.
                                            * This flag  is used  to implement  ramfs-based filesystems,  where
                                            * is used to prevent files from being deleted when the kernel tries
                                            * to reclaim memory.
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
#define MFILE_FN_ATTRREADONLY   0x00100000 /* [lock(ATOMIC)] fnode-specific: `chmod(2)', `chown(2)' and `utime(2)'
                                            *                                should fail with `E_FSERROR_READONLY' */
#define MFILE_F_RELATIME        0x00200000 /* [lock(ATOMIC)][const_if(MFILE_F_DELETED)] Only  relevant when  `MFILE_F_NOATIME'
                                            * isn't set: the last-accessed timestamp is only changed to the current realtime()
                                            * when  `OLD(mf_atime) < mf_mtime'. As such,  atime can only  be used to determine
                                            * accessed-after-last-modified when this flag has been set. */
/*efine MFILE_F_                0x00400000  * ... */
/*efine MFILE_F_                0x00800000  * ... */
#define MFILE_F_STRICTATIME     0x01000000 /* [lock(ATOMIC)] Strict last-accessed timestamps ??? */
#define MFILE_F_LAZYTIME        0x02000000 /* [lock(ATOMIC)] Lazy timestamps ??? */
#define MFILE_F_EXTUSAGE        0x04000000 /* [lock(WRITE_ONCE)] A super-block *might* be using  this file as its  device
                                            * (or in the future: some other rarely used, global wrapper around an mfile). */
#define MFILE_F_ROFLAGS         0x08000000 /* [lock(WRITE_ONCE)]
                                            * The following flags may not be changed by user-space:
                                            *  - MFILE_F_READONLY, MFILE_FN_ATTRREADONLY
                                            *  - MFILE_F_NOUSRMMAP, MFILE_F_NOUSRIO
                                            * The primary purpose of this flag is to be used for `mramfile'
                                            * objects, such as `execabi_system_rtld_file', in order to stop
                                            * user-space from being able to clear `MFILE_F_READONLY' and be
                                            * able to modify the system RTLD. Try not to use this flag  too
                                            * much (in most cases, there should be some way for programs to
                                            * clear flags such as READONLY, even for FLEETING, or SINGLETON
                                            * files).
                                            * Trying  to modify  these flags  after this  one's been set
                                            * causes `mfile_chflags()' to fail by throwing an exception:
                                            * E_ILLEGAL_OPERATION:E_ILLEGAL_OPERATION_CONTEXT_READONLY_FILE_FLAGS */
#define _MFILE_F_ROFLAGSMASK                                  \
	(MFILE_F_ROFLAGS | MFILE_F_READONLY | MFILE_F_NOUSRMMAP | \
	 MFILE_F_NOUSRIO | MFILE_FN_ATTRREADONLY)
#define MFILE_FN_FLEETING       0x10000000 /* [const] When set for fdirnode-derived nodes, don't recent-cache `struct path'
                                            * objects created for the purpose of path  traversal. - This is used by  procfs
                                            * for  per-process directories in  order to prevent them  being cached, as such
                                            * folders can randomly disappear as the result of thread/process exits. */
#define _MFILE_DEVFS_BYNAME_RED 0x20000000 /* [lock(devfs_byname_lock)] Internal flag: This file is a red node in the devfs by-name tree. */
#define _MFILE_FN__RBRED        0x40000000 /* [lock(:fn_super->fs_nodeslock)] Internal flag: This file-node is a red node. */
#ifndef CONFIG_NO_SMP
#define _MFILE_F_SMP_TSLOCK     0x80000000 /* [lock(ATOMIC)] SMP-lock for TimeStamps (`mf_atime', `mf_mtime', ...). */
#endif /* !CONFIG_NO_SMP */

#if defined(__WANT_MFILE__mf_fsuperlop) || defined(__WANT_MFILE__mf_fsuperplop)
struct fsuper;
#endif /* __WANT_MFILE__mf_fsuperlop || __WANT_MFILE__mf_fsuperplop */
#if defined(__WANT_MFILE__mf_delfnodes) || defined(__WANT_MFILE__mf_deadnod)
struct fnode;
#endif /* __WANT_MFILE__mf_delfnodes || __WANT_MFILE__mf_deadnod */
#if defined(__WANT_MFILE__mf_ramdirlop) || defined(__WANT_MFILE__mf_ramdirplop)
struct ramfs_dirnode;
#endif /* __WANT_MFILE__mf_ramdirlop || __WANT_MFILE__mf_ramdirplop */
#ifdef __WANT_MFILE__mf_delsup
struct fsuper;
#endif /* __WANT_MFILE__mf_delsup */
#ifdef __WANT_MFILE__mf_deadrament
#ifndef __ramfs_dirent_slist_defined
#define __ramfs_dirent_slist_defined
struct ramfs_dirent;
SLIST_HEAD(ramfs_dirent_slist, ramfs_dirent);
#endif /* !__ramfs_dirent_slist_defined */
#endif /* __WANT_MFILE__mf_deadrament */

struct misaligned_mfile;
LIST_HEAD(misaligned_mfile_list, misaligned_mfile);

struct mfilemeta;
struct mfile {
	WEAK refcnt_t                 mf_refcnt;     /* Reference counter. */
	struct mfile_ops const       *mf_ops;        /* [1..1][const] File operators. */
	struct atomic_rwlock          mf_lock;       /* Lock for this file. */
	Toblockop_slist(mfile)        mf_lockops;    /* [0..n][lock(ATOMIC)] Chain of lock operations. */
#ifdef CONFIG_KERNEL_MFILE_TRACES_LOCKPC
	void const                  *_mf_wrlockpc;   /* [lock(mf_lock)] Write-lock program counter. */
#endif /* CONFIG_KERNEL_MFILE_TRACES_LOCKPC */
	RBTREE_ROOT(mpart)            mf_parts;      /* [0..n][lock(mf_lock)] File parts. (or `MFILE_PARTS_ANONYMOUS') */
	struct sig                    mf_initdone;   /* Signal broadcast whenever one of the blocks of one of
	                                              * the contained parts changes state from INIT to  LOAD. */
	struct REF mpart_slist        mf_changed;    /* [0..n][lock(APPEND: ATOMIC,
	                                              *             CLEAR:  ATOMIC && mf_lock)]
	                                              * Chain of references to parts that contain unsaved changes.
	                                              * NOTE: Set to `MFILE_PARTS_ANONYMOUS'  if changed parts  should
	                                              *       always be ignored unconditionally. When no save callback
	                                              *       is defined (`mf_ops->mo_saveblocks == NULL'), this  must
	                                              *       always be kept `NULL' or `MFILE_PARTS_ANONYMOUS'.
	                                              * The following implications can be made:
	                                              * - IN(struct mpart *part):
	                                              *   A part with `MPART_F_CHANGED' set implies that the associated
	                                              *   file  either has  an anonymous  changed list,  or a non-empty
	                                              *   changed  list while also implementing the `mo_saveblocks' op.
	                                              *   >> (part->mp_flags & MPART_F_CHANGED) != 0 -->
	                                              *   >>     part->mp_file->mf_changed == MFILE_PARTS_ANONYMOUS ||
	                                              *   >>     (part->mp_file->mf_changed != NULL &&
	                                              *   >>      part->mp_file->mf_ops->mo_saveblocks != NULL)
	                                              * - IN(struct mfile *file):
	                                              *   A file with an `mo_saveblocks' op always has its changed list
	                                              *   set to `MFILE_PARTS_ANONYMOUS' or `NULL'
	                                              *   >> file->mf_ops->mo_saveblocks == NULL -->
	                                              *   >>     file->mf_changed == MFILE_PARTS_ANONYMOUS ||
	                                              *   >>     file->mf_changed == NULL
	                                              */
	size_t                        mf_part_amask; /* [const] == MAX(PAGESIZE, 1 << mf_blockshift) - 1
	                                              * This field  describes the  minimum alignment  of file  positions
	                                              * described by parts, minus one (meaning it can be used as a mask) */
	shift_t                       mf_blockshift; /* [const] == log2(FILE_BLOCK_SIZE) */
	shift_t                       mf_iobashift;  /* [const][<= mf_blockshift] == log2(REQUIRED_BLOCK_BUFFER_ALIGNMENT) */
#if ((2 * __SIZEOF_SHIFT_T__) % __SIZEOF_SIZE_T__) != 0
	byte_t                       _mf_pad[sizeof(size_t) - ((2 * __SIZEOF_SHIFT_T__) % __SIZEOF_SIZE_T__)]; /* ... */
#endif /* ((2 * __SIZEOF_SHIFT_T__) % __SIZEOF_SIZE_T__) != 0 */

#ifdef __WANT_FS_INIT
#define MFILE_INIT_mf_refcnt(mf_refcnt)   mf_refcnt
#define MFILE_INIT_mf_ops(mf_ops)         mf_ops
#ifdef CONFIG_KERNEL_MFILE_TRACES_LOCKPC
#define MFILE_INIT_mf_lock                ATOMIC_RWLOCK_INIT, SLIST_HEAD_INITIALIZER(~), __NULLPTR
#else /* CONFIG_KERNEL_MFILE_TRACES_LOCKPC */
#define MFILE_INIT_mf_lock                ATOMIC_RWLOCK_INIT, SLIST_HEAD_INITIALIZER(~)
#endif /* !CONFIG_KERNEL_MFILE_TRACES_LOCKPC */
#define MFILE_INIT_mf_parts(mf_parts)     mf_parts
#define MFILE_INIT_mf_initdone(mfile)     SIG_INIT(mfile.mf_initdone)
#define MFILE_INIT_mf_changed(mf_changed) { mf_changed }
#if ((2 * __SIZEOF_SHIFT_T__) % __SIZEOF_SIZE_T__) != 0
#define MFILE_INIT_mf_blockshift(mf_blockshift, mf_iobashift) \
	__hybrid_max_c2(PAGESIZE, (size_t)1 << (mf_blockshift)) - 1, mf_blockshift, mf_iobashift, { }
#else /* ((2 * __SIZEOF_SHIFT_T__) % __SIZEOF_SIZE_T__) != 0 */
#define MFILE_INIT_mf_blockshift(mf_blockshift, mf_iobashift) \
	__hybrid_max_c2(PAGESIZE, (size_t)1 << (mf_blockshift)) - 1, mf_blockshift, mf_iobashift
#endif /* ((2 * __SIZEOF_SHIFT_T__) % __SIZEOF_SIZE_T__) == 0 */
#define MFILE_INIT_mf_meta                __NULLPTR
#define MFILE_INIT_mf_flags(mf_flags)     mf_flags
#define MFILE_INIT_mf_trunclock           0
#endif /* __WANT_FS_INIT */
	struct mfilemeta             *mf_meta;       /* [0..1][lock(WRITE_ONCE)] Meta-data controller (to encapsulate rarely used file-related data). */
	uintptr_t                     mf_flags;      /* File flags (set of `MFILE_F_*') */
	WEAK size_t                   mf_trunclock;  /* [lock(INC((RDLOCK(mf_lock) || mpart_lock_acquired(ANY(mf_parts))) && !(mf_flags & MFILE_F_DELETING)),
	                                              *       DEC(ATOMIC))]
	                                              * Non-zero if `mf_filesize' must not be lowered. Incrementing this
	                                              * counter requires one  to be holding  a lock to  one of the  mem-
	                                              * parts  of  this file,  or a  lock to  the file  itself. However,
	                                              * decrementing it  doesn't impose  such a  requirement. When  this
	                                              * counter hits 0, then `mf_initdone' must be broadcast. */
#ifdef __WANT_FS_INIT
#if __SIZEOF_POINTER__ < 8 && defined(__WANT_MFILE_INIT_mf_filesize_symbol)
	/* Hacky work-around so that we're able to statically initialize
	 * `mf_filesize' from a linker symbol. The problem we're working
	 * around is GCC (under 32-bit)  refusing to do something  like:
	 * >> extern byte_t symbol[];
	 * >> static uint64_t var = (uint64_t)(uintptr_t)symbol;
	 *
	 * So we have to work around this issue and do the zero-extension
	 * of the static initialization ourselves. */
	union {
		atomic64_t                mf_filesize;   /* ... */
		uintptr_t                _mf_filesize_ptr[2]; /* ... */
	};
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define MFILE_INIT_mf_filesize_symbol(mf_filesize) { ._mf_filesize_ptr = { mf_filesize, 0 } }
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define MFILE_INIT_mf_filesize_symbol(mf_filesize) { ._mf_filesize_ptr = { 0, mf_filesize } }
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
#define MFILE_INIT_mf_filesize(mf_filesize)        { ATOMIC64_INIT(mf_filesize) }
#else /* __SIZEOF_POINTER__ < 8 */
#define MFILE_INIT_mf_filesize(mf_filesize) ATOMIC64_INIT(mf_filesize)
#ifdef __WANT_MFILE_INIT_mf_filesize_symbol
#define MFILE_INIT_mf_filesize_symbol MFILE_INIT_mf_filesize
#endif /* __WANT_MFILE_INIT_mf_filesize_symbol */
	atomic64_t                    mf_filesize;   /* ... */
#endif /* __SIZEOF_POINTER__ >= 8 */
#else /* __WANT_FS_INIT */
	atomic64_t                    mf_filesize;   /* [lock(READ:      ATOMIC,
	                                              *       INCREMENT: mf_trunclock != 0 && ATOMIC,  // NOTE: `mf_trunclock'  was  incremented while  holding `mf_lock'!  By first
	                                              *                                                // acquiring a write-lock to  `mf_lock' and waiting for  `mf_trunclock == 0',
	                                              *                                                // as well as one must be able to prevent `mf_filesize' from changing at all!
	                                              *       DECREMENT: mf_trunclock == 0 && ATOMIC &&
	                                              *                  (!(mf_flags & MFILE_F_DELETING) && mfile_partaddr_ceilalign(OLDVALUE) == mfile_partaddr_ceilalign(NEWVALUE) ||
	                                              *                   // Allowed to lower after setting `MFILE_F_DELETING' (but not if other thread set)
	                                              *                   (mf_flags & MFILE_F_DELETING) ||
	                                              *                   // Allowed to set  to 0 while  holding a lock  after `MFILE_F_DELETED' was  set
	                                              *                   (mfile_lock_writing(self) && (mf_flags & MFILE_F_DELETED) && NEW_VALUE == 0)))]
	                                              * [const_if(MFILE_F_FIXEDFILESIZE || MFILE_F_DELETED)]
	                                              * [valid_if(!mfile_isanon(self))] File       size       field.
	                                              * Attempting  to  construct new  mem-parts above  this address
	                                              * will  fail  and/or clamp  the  max accessible  file  size to
	                                              * the given address. Note however that  in the case of a  file
	                                              * that doesn't have the `MFILE_F_FIXEDFILESIZE' flag set, this
	                                              * values _can_ be increased by  writing beyond the end of  the
	                                              * file in a call to  `mfile_write()'. Also note that  whenever
	                                              * this value is increased, then the `mf_initdone' signal  will
	                                              * be broadcast.
	                                              *
	                                              * NOTE: When `mfile_isnode(self)', then this field can never grow larger
	                                              *       than    `mfile_asnode(self)->fn_super->fs_feat.sf_filesize_max'!
	                                              * Attempting to expand the size beyond this boundary must result in an
	                                              * `E_FSERROR_FILE_TOO_BIG' exceptions being thrown. */
#endif /* !__WANT_FS_INIT */
#if (defined(__WANT_MFILE__mf_lop) || defined(__WANT_MFILE__mf_plop) ||             \
     defined(__WANT_MFILE__mf_mflop) || defined(__WANT_MFILE__mf_mplop) ||          \
     defined(__WANT_MFILE__mf_fsuperlop) || defined(__WANT_MFILE__mf_fsuperplop) || \
     defined(__WANT_MFILE__mf_mfplop) || defined(__WANT_MFILE__mf_deadparts) ||     \
     defined(__WANT_MFILE__mf_mpplop) || defined(__WANT_MFILE__mf_compl) ||         \
     defined(__WANT_MFILE__mf_deadnod) || defined(__WANT_MFILE__mf_ramdirplop) ||   \
     defined(__WANT_MFILE__mf_ramdirlop) || defined(__WANT_MFILE__mf_deadrament) || \
     defined(__WANT_MFILE__mf_delsup) || defined(__WANT_MFILE__mf_lopX))
#ifdef __WANT_FS_INIT
#define MFILE_INIT_mf_atime(mf_atime__tv_sec, mf_atime__tv_nsec) {{ { .tv_sec = mf_atime__tv_sec, .tv_nsec = mf_atime__tv_nsec }
#define MFILE_INIT_mf_mtime(mf_mtime__tv_sec, mf_mtime__tv_nsec)    { .tv_sec = mf_mtime__tv_sec, .tv_nsec = mf_mtime__tv_nsec }
#define MFILE_INIT_mf_ctime(mf_ctime__tv_sec, mf_ctime__tv_nsec)    { .tv_sec = mf_ctime__tv_sec, .tv_nsec = mf_ctime__tv_nsec }
#define MFILE_INIT_mf_btime(mf_btime__tv_sec, mf_btime__tv_nsec)    { .tv_sec = mf_btime__tv_sec, .tv_nsec = mf_btime__tv_nsec } }}
#endif /* __WANT_FS_INIT */
	union {
		struct {
			struct timespec       mf_atime;      /* ... */
			struct timespec       mf_mtime;      /* ... */
			struct timespec       mf_ctime;      /* ... */
			struct timespec       mf_btime;      /* ... */
		};

#ifdef __WANT_MFILE__mf_lop
		struct lockop            _mf_lop;        /* lock operation */
#endif /* __WANT_MFILE__mf_lop */

#ifdef __WANT_MFILE__mf_plop
		struct postlockop        _mf_plop;       /* post-lock operation */
#endif /* __WANT_MFILE__mf_plop */

#ifdef __WANT_MFILE__mf_mflop
		Toblockop(mfile)         _mf_mflop;      /* mem-file lock operation */
#endif /* __WANT_MFILE__mf_mflop */

#ifdef __WANT_MFILE__mf_mplop
		Toblockop(mpart)         _mf_mplop;      /* mem-part lock operation */
#endif /* __WANT_MFILE__mf_mplop */

#ifdef __WANT_MFILE__mf_fsuperlop
		Toblockop(fsuper)        _mf_fsuperlop;  /* filesystem-super lock operation */
#endif /* __WANT_MFILE__mf_fsuperlop */

#ifdef __WANT_MFILE__mf_mpplop
		Tobpostlockop(mpart)     _mf_mpplop;     /* mem-part post-lock operation */
#endif /* __WANT_MFILE__mf_mpplop */

#ifdef __WANT_MFILE__mf_ramdirlop
		Toblockop(ramfs_dirnode) _mf_ramdirlop;  /* ramfs-dirnode post-lock operation */
#endif /* __WANT_MFILE__mf_ramdirlop */

#if defined(__WANT_MFILE__mf_fsuperplop) && defined(__WANT_MFILE__mf_delfnodes)
		struct {
			Tobpostlockop(fsuper) _mf_fsuperplop;/* filesystem-super post-lock operation */
			REF struct fnode     *_mf_delfnodes; /* Used during `fsuper_delete()' */
		};
#elif defined(__WANT_MFILE__mf_fsuperplop)
		Tobpostlockop(fsuper)    _mf_fsuperplop; /* filesystem-super post-lock operation */
#elif defined(__WANT_MFILE__mf_delfnodes)
#error "__WANT_MFILE__mf_delfnodes requires __WANT_MFILE__mf_fsuperplop"
#endif /* ... */

#if defined(__WANT_MFILE__mf_mfplop) && defined(__WANT_MFILE__mf_deadparts)
		struct {
			Tobpostlockop(mfile) _mf_mfplop;     /* mem-file post-lock operation */
			struct mpart_slist   _mf_deadparts;  /* Only used by `mfile_decref_and_destroy_deadparts_postop' */
		};
#elif defined(__WANT_MFILE__mf_mfplop)
		Tobpostlockop(mfile)     _mf_mfplop;     /* mem-file post-lock operation */
#elif defined(__WANT_MFILE__mf_deadparts)
#error "__WANT_MFILE__mf_deadparts requires __WANT_MFILE__mf_mfplop"
#endif /* __WANT_MFILE__mf_deadparts */

#if defined(__WANT_MFILE__mf_ramdirplop) && defined(__WANT_MFILE__mf_deadrament)
		struct {
			Tobpostlockop(ramfs_dirnode)  _mf_ramdirplop; /* Used internally for unmounting ramfs filesystems. */
			struct REF ramfs_dirent_slist _mf_deadrament; /* Used internally for unmounting ramfs filesystems. */
		};
#elif defined(__WANT_MFILE__mf_ramdirplop)
		Tobpostlockop(ramfs_dirnode)      _mf_ramdirplop; /* Used internally for unmounting ramfs filesystems. */
#elif defined(__WANT_MFILE__mf_deadrament)
#error "__WANT_MFILE__mf_deadrament requires __WANT_MFILE__mf_ramdirplop"
#endif /* __WANT_MFILE__mf_deadrament */

#ifdef __WANT_MFILE__mf_compl
		struct sigcompcon        _mf_compl;      /* Signal completion callback. (used for waiting on `mf_trunclock') */
#endif /* __WANT_MFILE__mf_compl */

#ifdef __WANT_MFILE__mf_deadnod
		SLIST_ENTRY(fnode)       _mf_deadnod;    /* Used internally */
#endif /* __WANT_MFILE__mf_deadnod */

#ifdef __WANT_MFILE__mf_delsup
		SLIST_ENTRY(fsuper)      _mf_delsup;     /* Used internally */
#endif /* __WANT_MFILE__mf_delsup */

#ifdef __WANT_MFILE__mf_lopX
		byte_t _mf_lopX[4 * sizeof(struct timespec)]; /* ... */
#endif /* __WANT_MFILE__mf_lopX */
	};
#else /* __WANT_MFILE__mf_... */
#ifdef __WANT_FS_INIT
#define MFILE_INIT_mf_atime(mf_atime__tv_sec, mf_atime__tv_nsec) { .tv_sec = mf_atime__tv_sec, .tv_nsec = mf_atime__tv_nsec }
#define MFILE_INIT_mf_mtime(mf_mtime__tv_sec, mf_mtime__tv_nsec) { .tv_sec = mf_mtime__tv_sec, .tv_nsec = mf_mtime__tv_nsec }
#define MFILE_INIT_mf_ctime(mf_ctime__tv_sec, mf_ctime__tv_nsec) { .tv_sec = mf_ctime__tv_sec, .tv_nsec = mf_ctime__tv_nsec }
#define MFILE_INIT_mf_btime(mf_btime__tv_sec, mf_btime__tv_nsec) { .tv_sec = mf_btime__tv_sec, .tv_nsec = mf_btime__tv_nsec }
#endif /* __WANT_FS_INIT */
	struct timespec               mf_atime;      /* [lock(_MFILE_F_SMP_TSLOCK)][const_if(MFILE_F_NOATIME)][valid_if(!MFILE_F_DELETED)]
	                                              * Last-accessed timestamp. NOTE!!!  Becomes invalid when  `MFILE_F_DELETED' is  set!
	                                              * iow: After reading this field, you must first check if `MFILE_F_DELETED' is set
	                                              *      before proceeding to use the data you've just read! */
	struct timespec               mf_mtime;      /* [lock(_MFILE_F_SMP_TSLOCK)][const_if(MFILE_F_NOMTIME)][valid_if(!MFILE_F_DELETED)]
	                                              * Last-modified timestamp. NOTE!!!  Becomes invalid when  `MFILE_F_DELETED' is  set!
	                                              * iow: After reading this field, you must first check if `MFILE_F_DELETED' is set
	                                              *      before proceeding to use the data you've just read! */
	struct timespec               mf_ctime;      /* [const][valid_if(!MFILE_F_DELETED)]
	                                              * Last-changed timestamp. Same as `mf_mtime',  but whereas `mf_mtime' only  changes
	                                              * when file data is altered, this one also changes when file attributes (other than
	                                              * timestamps) are altered. (e.g. `chmod(2)', `chown(2)') */
	struct timespec               mf_btime;      /* [const][valid_if(!MFILE_F_DELETED)]
	                                              * Birth timestamp. NOTE!!! Becomes invalid when `MFILE_F_DELETED' is set!
	                                              * iow: After reading this field, you must first check if `MFILE_F_DELETED' is set
	                                              *      before proceeding to use the data you've just read! */
#endif /* !__WANT_MFILE__mf_... */
	struct misaligned_mfile_list  mf_msalign;    /* [lock(mf_lock)][0..n] List of misaligned wrappers.
	                                              * Elements  may only be added when `MFILE_F_DELETED'
	                                              * and `MFILE_F_DELETING' aren't set. */
#ifdef __WANT_FS_INIT
#define MFILE_INIT_mf_msalign(mf_msalign) { mf_msalign }
#endif /* __WANT_FS_INIT */
};



/* Increment  or  decrement the  size-lock  counter. In  order  to use
 * `mfile_trunclock_inc_locked',  the caller must currently be holding
 * a lock to `self->mf_lock',  or at least one  of the parts found  in
 * the tree of `self->mf_parts', and made sure that `MFILE_F_DELETING'
 * isn't set (and `MFILE_F_DELETED' *shouldn't* be set).
 *
 * Alternatively, when `mfile_isanon(self)' is true, then no such
 * requirements are imposed,  and use of  these functions  become
 * optional. */
#define mfile_trunclock_inc_locked(self) \
	__hybrid_atomic_inc(&(self)->mf_trunclock, __ATOMIC_ACQUIRE)
#define mfile_trunclock_dec(self)                                         \
	(__hybrid_assert((self)->mf_trunclock != 0),                          \
	 __hybrid_atomic_decfetch(&(self)->mf_trunclock, __ATOMIC_RELEASE) || \
	 (sig_broadcast(&(self)->mf_initdone), 0))
#define mfile_trunclock_dec_nosignal(self)       \
	(__hybrid_assert((self)->mf_trunclock != 0), \
	 __hybrid_atomic_dec(&(self)->mf_trunclock, __ATOMIC_RELEASE))

/* Acquire a lock to `self', wait for `MFILE_F_DELETING' to go away
 * and check if `MFILE_F_DELETED' is set, then increment the trunc-
 * lock. If `MFILE_F_DELETED' was set, return `false'.
 * @return: true:  Success
 * @return: false: Failed to increment the trunc-lock (`MFILE_F_DELETED' was set) */
FUNDEF BLOCKING WUNUSED NONNULL((1)) __BOOL FCALL
mfile_trunclock_inc(struct mfile *__restrict self)
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...);

/* Blocking wait until `self->mf_trunclock == 0' */
FUNDEF BLOCKING NONNULL((1)) void FCALL
mfile_trunclock_waitfor(struct mfile *__restrict self)
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...);


/* Blocking wait until `MFILE_F_DELETING' isn't set, or `MFILE_F_DELETED' is set
 * @return: true:  `MFILE_F_DELETING' is no longer set
 * @return: false: `MFILE_F_DELETED' became set */
FUNDEF BLOCKING NONNULL((1)) __BOOL FCALL
mfile_deleting_waitfor(struct mfile *__restrict self)
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...);



/************************************************************************/
/* Do various things necessary to set `MFILE_F_DELETING' in `self->mf_flags'.
 *
 * NOTES:
 * - The caller must have already asserted that there are no trunc-lock (`self->mf_trunclock == 0')
 * - The caller must have already asserted that `MFILE_F_DELETING' isn't already set.
 * - The caller must be holding a write-lock to `self'
 * - This function will *NEVER* set `MFILE_F_DELETED' itself (it only checks if it is/gets set)
 * - The given in-file address range is used to determine which MAP_PRIVATE parts to load
 * - The caller of this function still has to decide how to deal with misaligned sub-files of `self'
 *
 * @param: delete_minaddr: The lowest in-file address where you intend to delete data
 * @param: delete_maxaddr: The greatest in-file address where you intend to delete data
 * @return: true:  Success (`MFILE_F_DELETING' is now set)
 * @return: false: Locks were released -> try again */
FUNDEF BLOCKING WUNUSED NONNULL((1)) __BOOL FCALL
mfile_deleting_begin_locked_or_unlock(struct mfile *__restrict self,
                                      pos_t delete_minaddr DFL((pos_t)0),
                                      pos_t delete_maxaddr DFL((pos_t)-1),
                                      struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...);

/* Roll-back a delete-operation previously started with `mfile_deleting_begin()' */
#define mfile_deleting_rollback(self)                                             \
	(__hybrid_atomic_and(&(self)->mf_flags, ~MFILE_F_DELETING, __ATOMIC_SEQ_CST), \
	 sig_broadcast(&(self)->mf_initdone))

/* Commit a delete-operation previously started with `mfile_deleting_begin()'
 * NOTE: This is only a convenience wrapper to document the connection with `mfile_delete()' */
#define mfile_deleting_commit(self) mfile_delete(self)
/************************************************************************/






/************************************************************************/
struct mfile_unlink_info {
	__BOOL mfui_deleted; /* Set to true if the file was already deleted. */
};

/* Prepare `self' for being unlinked.
 *
 * This function uses `mfile_deleting_begin_locked_or_unlock()' to set `MFILE_F_DELETING'
 * for `self' and all associated misaligned sub-files, as well as forces all  MAP_PRIVATE
 * file mappings into memory (which obviously includes mmapread mappings).
 *
 * This function should be called in order to prepare a file for unlinking. */
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) __BOOL FCALL
mfile_unlink_prepare_locked_or_unlock(struct mfile *__restrict self,
                                      /*out*/ struct mfile_unlink_info *__restrict info,
                                      struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) __BOOL FCALL
mfile_unlink_prepare_or_unlock(struct mfile *__restrict self,
                               /*out*/ struct mfile_unlink_info *__restrict info,
                               struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...);

/* Roll-back the actions of `mfile_unlink_prepare_or_unlock()' */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfile_unlink_rollback)(struct mfile *__restrict self,
                                     struct mfile_unlink_info const *__restrict info);

/* Must be called prior to `mfile_delete(self)' or whatever other
 * function has to  be used to  asynchronously anonymize  `self'. */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL _mfile_unlink_commit_prehook)(struct mfile *__restrict self,
                                            struct mfile_unlink_info const *__restrict info);
#define _mfile_unlink_commit(self, info, mfile_delete_fn) (_mfile_unlink_commit_prehook(self, info), mfile_delete_fn(self))
#define mfile_unlink_commit(self, info)                   _mfile_unlink_commit(self, info, mfile_delete)
/************************************************************************/




#ifdef CONFIG_NO_SMP
#define mfile_tslock_tryacquire(self)   1
#define mfile_tslock_acquire_nopr(self) (void)0
#define mfile_tslock_release_nopr(self) (void)0
#else /* CONFIG_NO_SMP */
#define mfile_tslock_tryacquire(self)               \
	(!(__hybrid_atomic_fetchor(&(self)->mf_flags,   \
	                           _MFILE_F_SMP_TSLOCK, \
	                           __ATOMIC_ACQUIRE) &  \
	   _MFILE_F_SMP_TSLOCK))
#define mfile_tslock_acquire_nopr(self)        \
	do {                                       \
		while (!mfile_tslock_tryacquire(self)) \
			task_pause();                      \
	}	__WHILE0
#define mfile_tslock_release_nopr(self) \
	__hybrid_atomic_and(&(self)->mf_flags, ~_MFILE_F_SMP_TSLOCK, __ATOMIC_RELEASE)
#endif /* !CONFIG_NO_SMP */

/* Helper macros for working with the TSLOCK of `self' */
#define mfile_tslock_acquire(self)           __hybrid_preemption_acquire_smp(mfile_tslock_tryacquire(self))
#define mfile_tslock_release(self)           __hybrid_preemption_release_smp(mfile_tslock_release_nopr(self))
#define mfile_tslock_acquire_br(self)        __hybrid_preemption_acquire_smp_b(mfile_tslock_tryacquire(self))
#define mfile_tslock_release_br(self)        __hybrid_preemption_release_smp_b(mfile_tslock_release_nopr(self))
#define mfile_tslock_release_pronly_br(self) __hybrid_preemption_release_smp_b((void)0)
#define mfile_tslock_release_pronly(self)    __hybrid_preemption_release_smp((void)0)


/* Mark `what' as having changed for `self'
 * @param: what: Set of `MFILE_F_CHANGED | MFILE_F_ATTRCHANGED' */
EIDECLARE(NOBLOCK NONNULL((1)), void, NOTHROW, FCALL,
          mfile_changed, (struct mfile *__restrict self, uintptr_t what), {
	uintptr_t old_flags, new_flags;
	old_flags = __hybrid_atomic_fetchor(&self->mf_flags, what, __ATOMIC_SEQ_CST);
	new_flags = old_flags | what;
	if (old_flags != new_flags && self->mf_ops->mo_changed)
		(*self->mf_ops->mo_changed)(self, old_flags, new_flags);
})


#define _mfile_cinit_blockshift _mfile_init_blockshift
#define _mfile_init_blockshift(self, blockshift, iobashift)                     \
	((self)->mf_blockshift = (blockshift),                                      \
	 (self)->mf_iobashift  = (iobashift),                                       \
	 (self)->mf_part_amask = ((size_t)1 << (((self)->mf_blockshift) > PAGESHIFT \
	                                        ? ((self)->mf_blockshift)           \
	                                        : PAGESHIFT)) -                     \
	                         1)
#ifdef CONFIG_KERNEL_MFILE_TRACES_LOCKPC
#define _mfile_init_wrlockpc_(self)  (self)->_mf_wrlockpc = __NULLPTR,
#define _mfile_cinit_wrlockpc_(self) __hybrid_assert((self)->_mf_wrlockpc == __NULLPTR),
#else /* CONFIG_KERNEL_MFILE_TRACES_LOCKPC */
#define _mfile_init_wrlockpc_(self)  /* nothing */
#define _mfile_cinit_wrlockpc_(self) /* nothing */
#endif /* !CONFIG_KERNEL_MFILE_TRACES_LOCKPC */


/* Initialize common fields. The caller must still initialize:
 *  - mf_ops, mf_parts, mf_changed, mf_part_amask, mf_blockshift,
 *    mf_iobashift, mf_flags,  mf_filesize,  mf_atime,  mf_mtime,
 *    mf_ctime, mf_btime */
#define _mfile_init_common(self) \
	((self)->mf_refcnt = 1, __mfile_init_common_norefcnt(self))
#define _mfile_cinit_common(self)                       \
	((self)->mf_refcnt = 1, __mfile_cinit_common_norefcnt(self))
#define __mfile_init_common_norefcnt(self) \
	(_mfile_init_wrlockpc_(self)           \
	 (self)->mf_meta = __NULLPTR,          \
	 atomic_rwlock_init(&(self)->mf_lock), \
	 SLIST_INIT(&(self)->mf_lockops),      \
	 sig_init(&(self)->mf_initdone),       \
	 LIST_INIT(&(self)->mf_msalign),       \
	 (self)->mf_trunclock = 0)
#define __mfile_cinit_common_norefcnt(self)             \
	(_mfile_cinit_wrlockpc_(self)                       \
	 __hybrid_assert((self)->mf_meta == __NULLPTR),     \
	 atomic_rwlock_cinit(&(self)->mf_lock),             \
	 __hybrid_assert(SLIST_EMPTY(&(self)->mf_lockops)), \
	 sig_cinit(&(self)->mf_initdone),                   \
	 __hybrid_assert(LIST_EMPTY(&(self)->mf_msalign)),  \
	 __hybrid_assert((self)->mf_trunclock == 0))

/* Initialize common+basic fields. The caller must still initialize:
 *  - mf_parts, mf_changed, mf_flags, mf_filesize, mf_atime, mf_mtime, mf_ctime, mf_btime */
#define _mfile_init(self, ops, block_shift, iobashift) \
	(_mfile_init_common(self),                         \
	 (self)->mf_ops = (ops),                           \
	 _mfile_init_blockshift(self, block_shift, iobashift))
#define _mfile_cinit(self, ops, block_shift, iobashift) \
	(_mfile_cinit_common(self),                         \
	 (self)->mf_ops = (ops),                            \
	 _mfile_cinit_blockshift(self, block_shift, iobashift))


/* Allocate physical memory for use with mem-parts created for `self'
 * This function is a more restrictive version of `page_malloc_part(1, max_pages, res_pages)',
 * in that it will also ensure that returned  pages are properly aligned, as well as that  the
 * given `max_pages' is  also properly aligned.  Note however that  so-long as the  size of  a
 * single file-block is <= PAGESIZE,  this function behaves 100%  identical to the above  call
 * to `page_malloc_part()' */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 3)) physpage_t
NOTHROW(FCALL mfile_alloc_physmem_nocc)(struct mfile *__restrict self,
                                        physpagecnt_t max_pages,
                                        physpagecnt_t *__restrict res_pages);


/* Destroy a given mem-file */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mfile_destroy)(struct mfile *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct mfile, mf_refcnt, mfile_destroy)


/* Check if the given mem-file has been marked as  anonymous.
 * When this is the case, then accessed mem-parts of the file
 * as always unique and never the same during repeated calls. */
#define mfile_isanon(self) ((self)->mf_parts == MFILE_PARTS_ANONYMOUS)

/* Floor- or ceil-align a given `addr'/`size' such that it may describe the start/end/size of a mem-part. */
#define mfile_partaddr_flooralign(self, addr) (pos_t)((uint64_t)(addr) & ~(uint64_t)(self)->mf_part_amask)
#define mfile_partaddr_ceilalign(self, addr)  (pos_t)(((uint64_t)(addr) + (self)->mf_part_amask) & ~(uint64_t)(self)->mf_part_amask)
#define mfile_partaddr_aligned(self, addr)    (((uint64_t)(addr) & (self)->mf_part_amask) == 0)
#define mfile_partsize_flooralign(self, size) ((size) & ~(self)->mf_part_amask)
#define mfile_partsize_ceilalign(self, size)  (((size) + (self)->mf_part_amask) & ~(self)->mf_part_amask)
#define mfile_partsize_aligned(self, size)    (((size) & (self)->mf_part_amask) == 0)

/* Floor- or ceil-align a given `addr'/`size' such that it may be used as `addr' or `num_bytes' of `mo_(load|save)blocks'. */
#define mfile_blockaddr_flooralign(self, addr) (pos_t)(((uint64_t)(addr) >> (self)->mf_blockshift) << (self)->mf_blockshift)
#define mfile_blockaddr_ceilalign(self, addr)  mfile_blockaddr_flooralign(self, (addr) + ((size_t)1 << (self)->mf_blockshift) - 1)
#define mfile_blockaddr_aligned(self, addr)    (((uint64_t)(addr) & (((size_t)1 << (self)->mf_blockshift) - 1)) == 0)
#define mfile_blocksize_flooralign(self, size) (((size) >> (self)->mf_blockshift) << (self)->mf_blockshift)
#define mfile_blocksize_ceilalign(self, size)  mfile_blocksize_flooralign(self, (size) + ((size_t)1 << (self)->mf_blockshift) - 1)
#define mfile_blocksize_aligned(self, size)    (((size) & (((size_t)1 << (self)->mf_blockshift) - 1)) == 0)

/* Reap lock operations of `self' */
#define _mfile_lockops_reap(self)    _oblockop_reap_atomic_rwlockT((struct mfile *)(self), mf_lockops, mf_lock)
#define mfile_lockops_reap(self)     oblockop_reap_atomic_rwlockT((struct mfile *)(self), mf_lockops, mf_lock)
#define mfile_lockops_mustreap(self) (__hybrid_atomic_load(&(self)->mf_lockops.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)

/* Lock accessor helpers for `struct mfile' */
#ifdef CONFIG_KERNEL_MFILE_TRACES_LOCKPC
#include <asm/intrin.h>
#define _mfile_trace_wrlock_setpc(self) (void)((self)->_mf_wrlockpc = __rdpc())
#define _mfile_trace_wrlock_clrpc(self) (void)((self)->_mf_wrlockpc = __NULLPTR)
#define mfile_lock_write(self)          (atomic_rwlock_write(&(self)->mf_lock), _mfile_trace_wrlock_setpc(self))
#define mfile_lock_write_nx(self)       (atomic_rwlock_write_nx(&(self)->mf_lock) ? (_mfile_trace_wrlock_setpc(self), 1) : 0)
#define mfile_lock_trywrite(self)       (atomic_rwlock_trywrite(&(self)->mf_lock) ? (_mfile_trace_wrlock_setpc(self), 1) : 0)
#define mfile_lock_endwrite(self)       (_mfile_trace_wrlock_clrpc(self), atomic_rwlock_endwrite(&(self)->mf_lock), mfile_lockops_reap(self))
#define mfile_lock_endwrite_f(self)     (_mfile_trace_wrlock_clrpc(self), atomic_rwlock_endwrite(&(self)->mf_lock))
#define mfile_lock_end(self)            (void)(mfile_lock_writing(self) ? _mfile_trace_wrlock_clrpc(self) : (void)0, atomic_rwlock_end_ex(&(self)->mf_lock) && (mfile_lockops_reap(self), 0))
#define mfile_lock_end_f(self)          (mfile_lock_writing(self) ? _mfile_trace_wrlock_clrpc(self) : (void)0, atomic_rwlock_end_ex(&(self)->mf_lock))
#define mfile_lock_upgrade(self)        ({ __BOOL __ok = atomic_rwlock_upgrade(&(self)->mf_lock); _mfile_trace_wrlock_setpc(self); __ok; })
#define mfile_lock_upgrade_nx(self)     ({ unsigned int __ok = atomic_rwlock_upgrade_nx(&(self)->mf_lock); if (__ok != 0) _mfile_trace_wrlock_setpc(self); __ok; })
#define mfile_lock_tryupgrade(self)     (atomic_rwlock_tryupgrade(&(self)->mf_lock) ? (_mfile_trace_wrlock_setpc(self), 1) : 0)
#define mfile_lock_downgrade(self)      (_mfile_trace_wrlock_clrpc(self), atomic_rwlock_downgrade(&(self)->mf_lock))
#else /* CONFIG_KERNEL_MFILE_TRACES_LOCKPC */
#define mfile_lock_write(self)      atomic_rwlock_write(&(self)->mf_lock)
#define mfile_lock_write_nx(self)   atomic_rwlock_write_nx(&(self)->mf_lock)
#define mfile_lock_trywrite(self)   atomic_rwlock_trywrite(&(self)->mf_lock)
#define mfile_lock_endwrite(self)   (atomic_rwlock_endwrite(&(self)->mf_lock), mfile_lockops_reap(self))
#define mfile_lock_endwrite_f(self) atomic_rwlock_endwrite(&(self)->mf_lock)
#define mfile_lock_end(self)        (void)(atomic_rwlock_end_ex(&(self)->mf_lock) && (mfile_lockops_reap(self), 0))
#define mfile_lock_end_f(self)      atomic_rwlock_end(&(self)->mf_lock)
#define mfile_lock_upgrade(self)    atomic_rwlock_upgrade(&(self)->mf_lock)
#define mfile_lock_upgrade_nx(self) atomic_rwlock_upgrade_nx(&(self)->mf_lock)
#define mfile_lock_tryupgrade(self) atomic_rwlock_tryupgrade(&(self)->mf_lock)
#define mfile_lock_downgrade(self)  atomic_rwlock_downgrade(&(self)->mf_lock)
#endif /* !CONFIG_KERNEL_MFILE_TRACES_LOCKPC */
#define mfile_lock_read(self)         atomic_rwlock_read(&(self)->mf_lock)
#define mfile_lock_read_nx(self)      atomic_rwlock_read_nx(&(self)->mf_lock)
#define mfile_lock_tryread(self)      atomic_rwlock_tryread(&(self)->mf_lock)
#define mfile_lock_endread(self)      (void)(atomic_rwlock_endread_ex(&(self)->mf_lock) && (mfile_lockops_reap(self), 0))
#define mfile_lock_endread_f(self)    atomic_rwlock_endread(&(self)->mf_lock)
#define mfile_lock_reading(self)      atomic_rwlock_reading(&(self)->mf_lock)
#define mfile_lock_writing(self)      atomic_rwlock_writing(&(self)->mf_lock)
#define mfile_lock_canread(self)      atomic_rwlock_canread(&(self)->mf_lock)
#define mfile_lock_canwrite(self)     atomic_rwlock_canwrite(&(self)->mf_lock)
#define mfile_lock_waitread(self)     atomic_rwlock_waitread(&(self)->mf_lock)
#define mfile_lock_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->mf_lock)
#define mfile_lock_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->mf_lock)
#define mfile_lock_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->mf_lock)


/* Make the given file anonymous+deleted. What this means is that (in order):
 *  - The `MFILE_F_DELETED' flag is set for the file.
 *  - The `MFILE_F_PERSISTENT' flag is cleared for the file.
 *  - The `MFILE_F_DELETING' flag is cleared for the file.
 *  - The file-fields of all mem-parts are altered to point
 *    at  anonymous  memory   files.  (s.a.   `mfile_anon')
 *  - The `MPART_F_GLOBAL_REF' flag is cleared for all parts
 *  - The `mf_parts' and `mf_changed' fields are set to `MFILE_PARTS_ANONYMOUS'
 *  - The `mf_filesize' field is set to `0'.
 *  - The `mf_msalign' list is cleared and after recursively mfile_delete-ing contained files.
 * The result of all of this is that it is no longer possible to
 * trace  back  mappings  of  parts  of  `self'  to  that  file.
 *
 * This function is called when the given file `self' should be deleted,
 * or has become  unavailable for  some other reason  (e.g. the  backing
 * filesystem has been unmounted or physically removed)
 *
 * Note that  (with the  exception of  `MFILE_F_DELETED' being  set, which  is
 * always done synchronously), this function operates entirely asynchronously,
 * meaning  that it uses lockops in order to wait for any locks it may need to
 * become available. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_delete)(struct mfile *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_delete_and_decref)(REF struct mfile *__restrict self);

/* Internal implementation of `mfile_delete()' (don't call this one
 * unless you know that you're doing; otherwise, you may cause race
 * conditions that can result in data corruption) */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_delete_impl)(/*inherit(always)*/ REF struct mfile *__restrict self);

/* Check if a given file has been marked as deleted. */
#define mfile_wasdeleted(self) (__hybrid_atomic_load(&(self)->mf_flags, __ATOMIC_ACQUIRE) & MFILE_F_DELETED)


/* Change  the size of the given file. If the new size is smaller than
 * the old size, mem-parts outside the new file's size-bounds are made
 * anonymous. When the size is increased, the behavior is the same  as
 * though  a  call `mfile_write(self, "", 1, new_size - 1)'  was made,
 * only that no actual write to the file is performed.
 *
 * @throw: E_FSERROR_READONLY:     The `MFILE_F_FIXEDFILESIZE' flag was set.
 * @throw: E_FSERROR_FILE_TOO_BIG: `new_size' is greater than the fs-specific limit. */
FUNDEF BLOCKING NONNULL((1)) void FCALL
mfile_truncate(struct mfile *__restrict self, pos_t new_size)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY,
		       E_FSERROR_FILE_TOO_BIG, ...);



/* Sync unwritten changes made to parts within the given address range.
 * @return: * : The total # of bytes that have been synced. */
FUNDEF BLOCKING NONNULL((1)) pos_t FCALL
mfile_sync(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK, ...);

/* Check if there are unwritten changes made to any of the parts of `self' */
#define mfile_haschanged(self) \
	(((uintptr_t)__hybrid_atomic_load(&(self)->mf_changed.slh_first, __ATOMIC_ACQUIRE) - 1) < (uintptr_t)-2)


/* Check `self' for a known mem-part that contains `addr', and (if
 * found), return that part. Otherwise, construct a new part  that
 * starts at `addr' and spans around `hint_bytes' bytes (less  may
 * be returned if another part  already exists that describes  the
 * mapping above the requested location, and more may be  returned
 * if a pre-existing part spans beyond `addr +hint_bytes -1')
 *
 * Note that the caller must ensure that:
 * @assume(mfile_partaddr_aligned(addr));
 * @assume(mfile_partaddr_aligned(hint_bytes));
 * @return: * : A reference to a part that (at some point in the past) contained
 *              the given `addr'. It may no  longer contain that address now  as
 *              the result of being truncated since.
 * @throw: E_INVALID_OPERATION:E_ILLEGAL_OPERATION_CONTEXT_MMAP_BEYOND_END_OF_FILE: ... */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_getpart(struct mfile *__restrict self,
              PAGEDIR_PAGEALIGNED pos_t addr,
              PAGEDIR_PAGEALIGNED size_t hint_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INVALID_ARGUMENT);

/* Same as `mfile_getpart()', but may _only_ be used when `self' is an
 * anonymous file! As such, this  function is mainly used to  allocate
 * parts for `mfile_ndef' and `mfile_zero' */
FUNDEF ATTR_RETNONNULL NONNULL((1)) REF struct mpart *FCALL
mfile_makepart(struct mfile *__restrict self,
               PAGEDIR_PAGEALIGNED pos_t addr,
               PAGEDIR_PAGEALIGNED size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


struct mfile_extendpart_data {
	PAGEDIR_PAGEALIGNED pos_t  mep_minaddr;  /* Base address of an unmapped range to fill by extending another part. */
	pos_t                      mep_maxaddr;  /* Last byte of the gap that should be filled. */
	int                        _placeholder; /* ... */
};
#define mfile_extendpart_data_init(self) ((self)->_placeholder = 0)
#define mfile_extendpart_data_fini(self) ((self)->_placeholder = 0)

struct unlockinfo;

/* While holding a read- or write-lock to `self', try to extend an
 * existing mem-part that borders against the given address  range
 * in order to fill the specified gap.
 * This function assumes that:
 *  - @assume(mfile_lock_reading(self) || mfile_lock_writing(self));
 *  - @assume(data->mep_minaddr <= data->mep_maxaddr);
 *  - @assume(mfile_partaddr_aligned(self, data->mep_minaddr));
 *  - @assume(mfile_partaddr_aligned(self, data->mep_maxaddr + 1));
 *  - @assume(WAS_CALLED(mfile_extendpart_data_init(data)));
 *  - @assume(self->mf_parts != MFILE_PARTS_ANONYMOUS);
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
                           struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_BADALLOC);
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
		THROWS(E_WOULDBLOCK, E_BADALLOC);


/* Look  at the neighbors of `part' and try to merge them with `part'. If
 * no neighbors exist, or if those neighbors are so far away that merging
 * with  them wouldn't be efficient, then simply insert `part' as-is into
 * the given mem-file `self', before adding `part' to the global list  of
 * parts, and finally releasing a lock to `self', as well as re-returning
 * a pointer to the given part.
 *  - For this purpose,  the caller must  initialize:
 *    >> part->mp_refcnt = MPART_F_GLOBAL_REF ? 2 : 1
 *  - If the `MPART_F_CHANGED' flag is  set, the given part, or  the
 *    combination of it and the to-be returned part will be added to
 *    the changed-part list.
 *  - However, if this is done, the caller is responsible for updating
 *    the file such that `MFILE_F_CHANGED' is set, and  `mo_changed()'
 *    is invoked.
 *  - If merging was done, return a reference to the new part against
 *    within the given `part' was merged (i.e. the one that was  left
 *    apart of the mem-part tree of `self')
 * This function assumes that:
 *  - @assume(mfile_lock_writing(self));
 *  - @assume(mfile_partaddr_aligned(self, part->mp_minaddr));
 *  - @assume(mfile_partaddr_aligned(self, part->mp_maxaddr + 1));
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
FUNDEF NOBLOCK WUNUSED NONNULL((1)) REF struct mpart *
NOTHROW(FCALL mfile_insert_and_merge_part_and_unlock)(struct mfile *__restrict self,
                                                      /*inherit(on_success)*/ struct mpart *__restrict part);




/************************************************************************/
/* MFile part locking helpers.                                          */
/************************************************************************/

/* Acquire locks to all of the mem-parts associated with a given mfile.
 * - The caller must be holding a write-lock to `self' and must ensure
 *   that `self' isn't anonymous.
 * - Acquire  references to  all parts of  `self'. If any  one of these
 *   cannot be acquired due to some part already having been destroyed,
 *   remove the offending part from the part-tree and mark it as  anon.
 * - Afterwards, try to acquire a lock to each of the parts. If  this
 *   fails, release locks from all  already-locked parts, as well  as
 *   the write-lock to `self' and `unlock'. Then wait for the lock to
 *   the blocking part to become available and return `false'
 * - If all locks could be acquired, return `true'
 * @return: true:  Locks+references acquired.
 * @return: false: All locks were locks; try again. */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mfile_incref_and_lock_parts_or_unlock(struct mfile *__restrict self,
                                      struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK);
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mfile_incref_and_lock_parts_r_or_unlock(struct mfile *__restrict self,
                                        pos_t minaddr, pos_t maxaddr,
                                        struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK);

/* Same  as  `mfile_incref_and_lock_parts_or_unlock()', but  return a
 * reference to the blocking part (if any), and not release any locks
 * other than those to mem-parts that could be locked before the part
 * that is blocking was encountered:
 * - Try to acquire references and locks to an entire part tree. When
 *   there is some part to which no lock can be acquired immediately,
 *   return a reference to said part.
 * - When this function returns `NULL', locks+references have been acquired. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) REF struct mpart *
NOTHROW(FCALL mfile_tryincref_and_lock_parts)(struct mfile *__restrict self);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) REF struct mpart *
NOTHROW(FCALL mfile_tryincref_and_lock_parts_r)(struct mfile *__restrict self,
                                                pos_t minaddr, pos_t maxaddr);

/* Do the inverse of `mfile_incref_and_lock_parts_or_unlock()' and
 * release locks+references to parts of `self'. NOTE: The lock  to
 * `self' is _NOT_ released during this! */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_unlock_and_decref_parts)(struct mfile *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_unlock_and_decref_parts_r)(struct mfile *__restrict self,
                                               pos_t minaddr, pos_t maxaddr);

/* Same as `mfile_unlock_and_decref_parts()', but keep a lock & reference to `part' */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfile_unlock_and_decref_parts_except)(struct mfile *__restrict self,
                                                    struct mpart *__restrict part);
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfile_unlock_and_decref_parts_r_except)(struct mfile *__restrict self,
                                                      struct mpart *__restrict part,
                                                      pos_t minaddr, pos_t maxaddr);

/* Deny  write  access  to anyone  currently  mapping any  part  of `self'.
 * The caller must be holding a write-lock to `self', as well as individual
 * locks to every part associated with it, as well as be holding references
 * to all of the parts of `self' (`mfile_incref_and_lock_parts_or_unlock').
 *
 * @return: true:  Success: write access has been denied to all parts.
 * @return: false: Locks were lost and you must try again.
 *
 * Locking logic:
 *   - return == true:  No locks are lost, and no locks are gained
 *   - return == false: - mfile_unlock_and_decref_parts(self);
 *                      - mfile_lock_endwrite(unlock);
 *                      - unlockinfo_xunlock(unlock);
 *   - THROW:           like `return == false' */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mfile_parts_denywrite_or_unlock(struct mfile *__restrict self,
                                struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY);
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mfile_parts_denywrite_r_or_unlock(struct mfile *__restrict self,
                                  pos_t minaddr, pos_t maxaddr,
                                  struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY);


/* Load MAP_PRIVATE (copy-on-write) nodes of `self' into memory.
 *
 * The caller must be holding a write-lock to `self', as well as individual
 * locks to every part associated with it, as well as be holding references
 * to all of the parts of `self' (`mfile_incref_and_lock_parts_or_unlock').
 *
 * @return: true:  Success: all blocks linked to copy-on-write nodes are loaded.
 * @return: false: Locks were lost and you must try again.
 *
 * Locking logic:
 *   - return == true:  No locks are lost, and no locks are gained
 *   - return == false: - mfile_unlock_and_decref_parts(self);
 *                      - mfile_lock_endwrite(unlock);
 *                      - unlockinfo_xunlock(unlock);
 *   - THROW:           like `return == false' */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mfile_parts_loadprivate_or_unlock(struct mfile *__restrict self,
                                  struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY);
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
mfile_parts_loadprivate_r_or_unlock(struct mfile *__restrict self,
                                    pos_t minaddr, pos_t maxaddr,
                                    struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY);


/* Ensure  that the `MFILE_F_DELETING' flag isn't set. The
 * caller must be holding a read- or write-lock to `self'. */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
_mfile_notdeleting_or_unlock(struct mfile *__restrict self,
                             struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...)
		ASMNAME("mfile_notdeleting_or_unlock");
#define mfile_notdeleting_or_unlock(self, ...)                                              \
	(unlikely(__hybrid_atomic_load(&(self)->mf_flags, __ATOMIC_ACQUIRE) & MFILE_F_DELETING) \
	 ? _mfile_notdeleting_or_unlock(self, ##__VA_ARGS__)                                    \
	 : 1)


/* Go through all `mf_msalign' sub-files of `self' and initialize+anonymize
 * all mem-parts that (at least partially) overlap with  [minaddr,maxaddr].
 * This must be  done whenever  the contents  of the  named range  changed,
 * since any  content-changes mean  that future  misaligned files  need  to
 * create new mem-parts with (then) different memory contents.
 *
 * In order to call this function, the caller must be:
 * - Holding a read-lock to `mfile_lock_read(self)'  (or write)
 * @return: true:  Success (locks are still held)
 * @return: false: Try again (locks were lost)
 * @THROW: Error (locks were lost) */
FUNDEF BLOCKING WUNUSED NONNULL((1)) __BOOL KCALL
_mfile_msalign_makeanon_locked_or_unlock(struct mfile *__restrict self,
                                         pos_t minaddr, pos_t maxaddr,
                                         struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_IOERROR, E_BADALLOC, ...)
		ASMNAME("mfile_msalign_makeanon_locked_or_unlock");
#ifndef __OPTIMIZE_SIZE__
#define mfile_msalign_makeanon_locked_or_unlock(self, ...) \
	(likely(LIST_EMPTY(&(self)->mf_msalign)) ? 1 : likely(_mfile_msalign_makeanon_locked_or_unlock(self, __VA_ARGS__)))
#else /* !__OPTIMIZE_SIZE__ */
#define mfile_msalign_makeanon_locked_or_unlock(self, ...) \
	likely(_mfile_msalign_makeanon_locked_or_unlock(self, __VA_ARGS__))
#endif /* __OPTIMIZE_SIZE__ */


/* Same as `_mfile_msalign_makeanon_locked_or_unlock()', except that
 * the caller doesn't need to worry about holding a lock to  `self'.
 * @return: true:  Success (locks are still held)
 * @return: false: Try again (locks were lost)
 * @THROW: Error (locks were lost) */
FUNDEF BLOCKING WUNUSED NONNULL((1)) __BOOL KCALL
_mfile_msalign_makeanon_or_unlock(struct mfile *__restrict self,
                                  pos_t minaddr, pos_t maxaddr,
                                  struct unlockinfo *unlock DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_IOERROR, E_BADALLOC, ...)
		ASMNAME("mfile_msalign_makeanon_or_unlock");
#ifndef __OPTIMIZE_SIZE__
#define mfile_msalign_makeanon_or_unlock(self, ...)                                            \
	(likely(__hybrid_atomic_load(&(self)->mf_msalign.lh_first, __ATOMIC_ACQUIRE) == __NULLPTR) \
	 ? 1                                                                                       \
	 : likely(_mfile_msalign_makeanon_or_unlock(self, __VA_ARGS__)))
#else /* !__OPTIMIZE_SIZE__ */
#define mfile_msalign_makeanon_or_unlock(self, ...) \
	likely(_mfile_msalign_makeanon_or_unlock(self, __VA_ARGS__))
#endif /* __OPTIMIZE_SIZE__ */



/* Alter  flags  of `self'  like `self->mf_flags = (self->mf_flags & mask) | flags'
 * Special care is taken to ensure that the transformation is performed atomically,
 * and that `MFILE_F_READONLY' is only  altered while holding the necessary  locks,
 * including a preceding denywrite when it is set.
 * @param: mask:  Inverted set of flags, as accepted by `flags'
 * @param: flags: Set of `MFILE_F_READONLY | MFILE_F_NOATIME | MFILE_F_NOUSRMMAP |
 *                        MFILE_F_NOUSRIO | MFILE_F_NOMTIME | MFILE_FN_ATTRREADONLY |
 *                        MFILE_F_RELATIME | MFILE_F_STRICTATIME |  MFILE_F_LAZYTIME'
 * @param: check_permissions: When true, ensure that the caller is allowed to alter
 *                            flags in the requested manner.
 * @return: * : The old set of file flags.
 * @throw: E_ILLEGAL_OPERATION:E_ILLEGAL_OPERATION_CONTEXT_READONLY_FILE_FLAGS: [...] */
FUNDEF NONNULL((1)) uintptr_t KCALL
mfile_chflags(struct mfile *__restrict self, uintptr_t mask,
              uintptr_t flags, __BOOL check_permissions DFL(1))
		THROWS(E_WOULDBLOCK, E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY,
		       E_INSUFFICIENT_RIGHTS, E_ILLEGAL_OPERATION);



/* Trim parts of `self' in the given address range according to  `mode'.
 * This function is a simplified wrapper around `mpart_trim_or_unlock()'
 * that automatically enumerates parts of `self' in relevant ranges, and
 * does all of the necessary lock management.
 * This function primarily implements the `FILE_IOC_TRIM' ioctl.
 *
 * @param: minaddr: The lowest in-file address where data should be trimmed (will be rounded down)
 * @param: maxaddr: The greatest in-file address where data should be trimmed (will be rounded up)
 * @param: mode:    Trimming mode (s.a. `MPART_TRIM_MODE_*' and `MPART_TRIM_FLAG_*')
 * @return: * :     The total number of trimmed bytes (s.a. `struct mpart_trim_data::mtd_bytes') */
FUNDEF BLOCKING WUNUSED NONNULL((1)) pos_t KCALL
mfile_trimparts(struct mfile *__restrict self,
                pos_t minaddr, pos_t maxaddr,
                unsigned int mode)
		THROWS(E_BADALLOC, E_IOERROR, ...);




/* Check if the file's raw I/O interface should be used by default.
 * that is: its mmap operator isn't overwritten, and user-space  is
 * allowed to mmap() the file itself.
 *
 * This is the condition that must be confirmed for a mfile to be
 * exec(2)-able; else  `E_NOT_EXECUTABLE_NOT_REGULAR' is  thrown. */
#define mfile_hasrawio(self)                   \
	((!(self)->mf_ops->mo_stream ||            \
	  !(self)->mf_ops->mo_stream->mso_mmap) && \
	 !((self)->mf_flags & MFILE_F_NOUSRMMAP))


/* Read/write raw data to/from a given mem-file.
 * - These function form the _RAW_ I/O interface to the unified file I/O
 *   buffers. Be careful  about calling these  when operators have  been
 *   overwritten, in which case `mfile_upread'  and friends may need  to
 *   be used instead.
 * - File-write functions (almost) always write all data and thus (almost)
 *   always simply re-return `num_bytes'  as-given. The only exception  to
 *   this  rule is when `self' is a `struct fnode' who's associated fsuper
 *   descriptor limits the max size of a file  (`fs_feat.sf_filesize_max')
 *   such that the attempted write  would be located outside the  possible
 *   boundaries of a file.
 *   In  this case, return the # of bytes that could still be written before
 *   the limit is reached, but if this would end up being `0' bytes (because
 *   the initial file-offset was already `> sf_filesize_max'), then an error
 *   `E_FSERROR_FILE_TOO_BIG' is thrown instead. (iow: `0' is never returned
 *   if a non-zero buffer is given) */
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL mfile_read(struct mfile *__restrict self, NCX void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL mfile_read_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL mfile_readv(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL mfile_readv_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mfile_write(struct mfile *__restrict self, NCX void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mfile_write_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mfile_writev(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mfile_writev_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Read/write functions that will attempt to read/write all requested data. */
FUNDEF BLOCKING NONNULL((1)) void KCALL mfile_readall(struct mfile *__restrict self, NCX void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1)) void KCALL mfile_readall_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1, 2)) void KCALL mfile_readallv(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) void KCALL mfile_readallv_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1)) void KCALL mfile_writeall(struct mfile *__restrict self, NCX void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1)) void KCALL mfile_writeall_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1, 2)) void KCALL mfile_writeallv(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) void KCALL mfile_writeallv_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Use tailread() to block instead of returning 0 for EOF; use tailwrite() for O_APPEND. */
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL mfile_tailread(struct mfile *__restrict self, NCX void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL mfile_tailread_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL mfile_tailreadv(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL mfile_tailreadv_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mfile_tailwrite(struct mfile *__restrict self, NCX void const *src, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mfile_tailwrite_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mfile_tailwritev(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mfile_tailwritev_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Same as the above, but these use an intermediate (stack) buffer for  transfer.
 * As such, these functions are called by the above when `memcpy_nopf()' produces
 * transfer errors that cannot be resolved by `mman_prefault()' */
FUNDEF BLOCKING NONNULL((1)) size_t KCALL _mfile_buffered_read(struct mfile *__restrict self, NCX void *dst, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL _mfile_buffered_write(struct mfile *__restrict self, NCX void const *src, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL _mfile_buffered_tailwrite(struct mfile *__restrict self, NCX void const *src, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL _mfile_buffered_readv(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL _mfile_buffered_writev(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t filepos) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL _mfile_buffered_tailwritev(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);

/* "direct" versions of the above (for use with O_DIRECT; these bypass
 * the unified I/O buffer and directly talk to `mo_(load|save)blocks')
 * - Trying to use these when the given buffer is VIO causes E_SEGFAULT_UNMAPPED,E_SEGFAULT_CONTEXT_VIO
 * - Alignment requirements are checked by these functions (`E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BAD*') */
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL mfile_direct_read(struct mfile *__restrict self, NCX void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL mfile_direct_read_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL mfile_direct_readv(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL mfile_direct_readv_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mfile_direct_write(struct mfile *__restrict self, NCX void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING NONNULL((1)) size_t KCALL mfile_direct_write_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mfile_direct_writev(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) size_t KCALL mfile_direct_writev_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);

/* Same as above, but these are the "async"-io versions
 * NOTE: The virtual functions here will asynchronously and automatically
 *       release DMA locks when  the associated I/O operations  complete. */
FUNDEF BLOCKING WUNUSED NONNULL((1, 5)) size_t KCALL mfile_direct_read_async(struct mfile *__restrict self, NCX void *dst, size_t num_bytes, pos_t src_offset, struct aio_multihandle *__restrict aio) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 5)) size_t KCALL mfile_direct_read_async_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset, struct aio_multihandle *__restrict aio) THROWS(E_WOULDBLOCK, E_BADALLOC, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2, 6)) size_t KCALL mfile_direct_readv_async(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset, struct aio_multihandle *__restrict aio) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2, 6)) size_t KCALL mfile_direct_readv_async_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset, struct aio_multihandle *__restrict aio) THROWS(E_WOULDBLOCK, E_BADALLOC, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING NONNULL((1, 5)) size_t KCALL mfile_direct_write_async(struct mfile *__restrict self, NCX void const *src, size_t num_bytes, pos_t dst_offset, struct aio_multihandle *__restrict aio) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING NONNULL((1, 5)) size_t KCALL mfile_direct_write_async_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes, pos_t dst_offset, struct aio_multihandle *__restrict aio) THROWS(E_WOULDBLOCK, E_BADALLOC, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING NONNULL((1, 2, 6)) size_t KCALL mfile_direct_writev_async(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset, struct aio_multihandle *__restrict aio) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);
FUNDEF BLOCKING NONNULL((1, 2, 6)) size_t KCALL mfile_direct_writev_async_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset, struct aio_multihandle *__restrict aio) THROWS(E_WOULDBLOCK, E_BADALLOC, E_INVALID_ARGUMENT_BAD_ALIGNMENT, ...);

/* Helpers for directly reading/writing to/from VIO space. */
#ifdef LIBVIO_CONFIG_ENABLED
FUNDEF BLOCKING NONNULL((1)) void KCALL mfile_vioread(struct mfile *__restrict self, NCX void *dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1)) void KCALL mfile_viowrite(struct mfile *__restrict self, NCX void const *src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1)) void KCALL mfile_vioread_p(struct mfile *__restrict self, physaddr_t dst, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1)) void KCALL mfile_viowrite_p(struct mfile *__restrict self, physaddr_t src, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1, 2)) void KCALL mfile_vioreadv(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) void KCALL mfile_viowritev(struct mfile *__restrict self, struct iov_buffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);
FUNDEF BLOCKING NONNULL((1, 2)) void KCALL mfile_vioreadv_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t src_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1, 2)) void KCALL mfile_viowritev_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf, size_t buf_offset, size_t num_bytes, pos_t dst_offset) THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
#endif /* LIBVIO_CONFIG_ENABLED */

/* Builtin mem files */
#ifndef __mfile_phys_defined
#define __mfile_phys_defined
DATDEF struct mfile mfile_phys; /* Physical memory access (file position is physical memory address) */
#endif /* !__mfile_phys_defined */
#ifndef __mfile_ndef_defined
#define __mfile_ndef_defined
DATDEF struct mfile mfile_ndef; /* Random, uninitialized, anonymous memory. */
#endif /* !__mfile_ndef_defined */
#ifndef __mfile_zero_defined
#define __mfile_zero_defined
DATDEF struct mfile mfile_zero; /* Zero-initialized, anonymous memory. */
#endif /* !__mfile_zero_defined */

/* Fallback  files for anonymous memory. These behave the same as `mfile_zero',
 * but one exists for every possible `mf_blockshift' (where the index into this
 * array is equal to that file's `mf_blockshift' value)
 * As such, these files are used by `mfile_delete()' as replacement mappings
 * of the original file. */
DATDEF struct mfile /*     */ mfile_anon[BITSOF(void *)];
DATDEF struct mfile_ops const mfile_anon_ops[BITSOF(void *)];


/* Check if `self' is "/dev/zero" or one of the anonymous files, all of which
 * are  set-up such  that memory mapped  by `self' is  initialized to zeroes. */
#define mfile_isdevzero(self) \
	((self) == &mfile_zero || ((self) >= mfile_anon && (self) < COMPILER_ENDOF(mfile_anon)))


/* User-visible mem-file access API. (same as the handle access API) */
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL mfile_uread(struct mfile *__restrict self, NCX void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL mfile_uwrite(struct mfile *__restrict self, NCX void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL mfile_utailwrite(struct mfile *__restrict self, NCX void const *src, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL mfile_upread(struct mfile *__restrict self, NCX void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) size_t KCALL mfile_upwrite(struct mfile *__restrict self, NCX void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL mfile_ureadv(struct mfile *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL mfile_uwritev(struct mfile *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL mfile_utailwritev(struct mfile *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL mfile_upreadv(struct mfile *__restrict self, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL mfile_upwritev(struct mfile *__restrict self, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
FUNDEF BLOCKING NONNULL((1)) pos_t KCALL mfile_useek(struct mfile *__restrict self, off_t offset, unsigned int whence) THROWS(...);
FUNDEF BLOCKING NONNULL((1)) syscall_slong_t KCALL mfile_uioctl(struct mfile *__restrict self, ioctl_t cmd, NCX UNCHECKED void *arg, iomode_t mode) THROWS(...);
FUNDEF BLOCKING NONNULL((1)) void KCALL mfile_utruncate(struct mfile *__restrict self, pos_t new_size) THROWS(...);
FUNDEF BLOCKING NONNULL((1, 2)) void KCALL mfile_ummap(struct mfile *__restrict self, struct handle_mmap_info *__restrict info) THROWS(...);
FUNDEF BLOCKING NONNULL((1)) pos_t KCALL mfile_uallocate(struct mfile *__restrict self, fallocate_mode_t mode, pos_t start, pos_t length) THROWS(...);
FUNDEF BLOCKING NONNULL((1)) void KCALL mfile_usync(struct mfile *__restrict self) THROWS(...);
FUNDEF BLOCKING NONNULL((1)) void KCALL mfile_udatasync(struct mfile *__restrict self) THROWS(...);
FUNDEF BLOCKING NONNULL((1)) void KCALL mfile_ustat(struct mfile *__restrict self, NCX struct stat *result) THROWS(...);
FUNDEF BLOCKING NONNULL((1)) void KCALL mfile_upollconnect(struct mfile *__restrict self, poll_mode_t what) THROWS(...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) poll_mode_t KCALL mfile_upolltest(struct mfile *__restrict self, poll_mode_t what) THROWS(...);
FUNDEF BLOCKING NONNULL((1)) REF void *KCALL mfile_utryas(struct mfile *__restrict self, uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK);
FUNDEF BLOCKING NONNULL((1, 2)) ssize_t KCALL mfile_uprintlink(struct mfile *__restrict self, __pformatprinter printer, void *arg) THROWS(E_WOULDBLOCK, ...);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILE_H */
