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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>

#include <hybrid/limitcore.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <bits/crt/format-printer.h>
#include <kos/io.h>
#include <kos/kernel/handle.h>

#include <stdbool.h>


/* Management of user-space descriptors  for kernel data, here  called
 * handles,   but  referred  to  as  file-descriptors  in  user-space.
 * The associated user-space data type is `fd_t', which aliases `int',
 * which  is  why  the  kernel  uses  `unsigned int'  as  its internal
 * descriptor type. */

#ifdef __CC__
DECL_BEGIN

struct dirent;
struct stat;
struct aio_multihandle;
struct path;
struct fdirent;
struct fnode;
struct mfile;
struct fsuper;
struct taskpid;
struct task;
struct mman;
struct pipe;
struct driver;
struct pidns;
struct socket;
struct epoll_controller;


struct handle_mmap_info {
	/* mmap information to-be filled in  by implementations of the  `h_mmap'
	 * operator. Note that the caller will have already filled in fields as:
	 *   - hmi_minaddr = 0;
	 *   - hmi_maxaddr = (pos_t)-1;
	 *   - hmi_fspath  = NULL;
	 *   - hmi_fsname  = NULL;
	 * Meaning that in order to comply with requirements, the `h_mmap' implementation
	 * only needs to  fill in `hmi_file'  in order  to be able  to indicate  success. */
	REF struct mfile   *hmi_file;    /* [1..1][out] The file that should be mapped. */
	pos_t               hmi_minaddr; /* [in|out] Lowest mmap-able address from `hmi_file'. This value will also
	                                  * be used as an addend to the offset-argument of `mmap(2)', meaning  that
	                                  * any file-map operation will be relative to this. */
	pos_t               hmi_maxaddr; /* [in|out] Similar to `hmi_minaddr': The max address that may be  mapped
	                                  * by user-space.  Note that  this field  slightly differs  from an  mmap
	                                  * limit which  may be  imposed by  `hmi_file->mf_filesize': Whereas  the
	                                  * later will throw `E_ILLEGAL_OPERATION_CONTEXT_MMAP_BEYOND_END_OF_FILE'
	                                  * when trying  to mmap  beyond the  end of  a file,  attempting to  mmap
	                                  * memory beyond  this address  will simply  result in  mfile_zero to  be
	                                  * mapped within that area, rather  than the intended file being  mapped.
	                                  * s.a. `mman_map_subrange()' and `mfile_getpart()' */
	REF struct path    *hmi_fspath;  /* [0..1][in|out] Filesystem path of `hmi_file' */
	REF struct fdirent *hmi_fsname;  /* [0..1][in|out] Filesystem name of `hmi_file' */
};

#ifdef __INTELLISENSE__
DATDEF
#endif /* __INTELLISENSE__ */
struct handle_types {
	/* NOTE: _ALL_ callbacks in here are _always_ defined. (aka. `[1..1]')
	 *       Those that aren't explicitly implemented are aliased to `h_*[HANDLE_TYPE_UNDEFINED]',
	 *       which  (when  invoked)  always throws  an  `E_NOT_IMPLEMENTED_UNSUPPORTED' exception.
	 *       In other words: To check if a function is implemented, compare it with
	 *                       its `HANDLE_TYPE_UNDEFINED' counterpart!
	 * NOTE: The incref() and decref() functions for `HANDLE_TYPE_UNDEFINED' are no-ops.
	 * NOTE: The  reason why type-ids  are vectored at  this lowest possible level
	 *       is to speed up callback selection by ensuring a constant base address
	 *      (since `handle_type_db' is known at compile-time, and offsets to fields
	 *       are known, also), with the type-index then only having to be multiplied
	 *       by the size of a pointer.
	 *       Thanks to this, the necessary call operation can be encoded as a single
	 *       instruction on X86:
	 *       >> movl   HANDLE_TYPE, %eax
	 *       >> calll  *handle_type_db+h_sync(,%eax,4)
	 */
	char const *h_typename[HANDLE_TYPE_COUNT];

	/* ============== Normal (strong) reference counting API */
	refcnt_t NOTHROW_T(NOBLOCK WUNUSED_T NONNULL_T((1)) FCALL *h_refcnt[HANDLE_TYPE_COUNT])(/*T*/ void const *__restrict ptr);
	void NOTHROW_T(NOBLOCK NONNULL_T((1)) FCALL *h_incref[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr);
	void NOTHROW_T(NOBLOCK NONNULL_T((1)) FCALL *h_decref[HANDLE_TYPE_COUNT])(REF /*T*/ void *__restrict ptr);
	__BOOL NOTHROW_T(NOBLOCK NONNULL_T((1)) FCALL *h_tryincref[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr);

	/* ============== Weak reference counting API */
	WEAK REF void *NOTHROW_T(NOBLOCK ATTR_RETNONNULL_T WUNUSED_T NONNULL_T((1)) FCALL *h_weakgetref[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr);
	REF /*T*/ void *NOTHROW_T(NOBLOCK WUNUSED_T NONNULL_T((1)) FCALL *h_weaklckref[HANDLE_TYPE_COUNT])(void *__restrict weakref_ptr);
	void NOTHROW_T(NOBLOCK NONNULL_T((1)) FCALL *h_weakdecref[HANDLE_TYPE_COUNT])(WEAK REF void *__restrict weakref_ptr);

	/* Basic read/write primitives.
	 * @throws: E_WOULDBLOCK: `IO_NONBLOCK' was given and no data/space was available (at the moment)
	 * @return: 0 : EOF has been reached
	 * @return: * : The amount of read/written bytes (`<= num_bytes') */
	size_t (BLOCKING WUNUSED_T NONNULL_T((1)) KCALL *h_read[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
	size_t (BLOCKING WUNUSED_T NONNULL_T((1)) KCALL *h_write[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) THROWS(...);

	/* Position-based read/write primitives.
	 * @throws: * : Same as `h_read' / `h_write'
	 * @return: * : Same as `h_read' / `h_write' */
	size_t (BLOCKING WUNUSED_T NONNULL_T((1)) KCALL *h_pread[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
	size_t (BLOCKING WUNUSED_T NONNULL_T((1)) KCALL *h_pwrite[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);

	/* Vector-based read/write primitives.
	 * @throws: * : Same as `h_read' / `h_write'
	 * @return: * : Same as `h_read' / `h_write' */
	size_t (BLOCKING WUNUSED_T NONNULL_T((1, 2)) KCALL *h_readv[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) THROWS(...);
	size_t (BLOCKING WUNUSED_T NONNULL_T((1, 2)) KCALL *h_writev[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) THROWS(...);
	size_t (BLOCKING WUNUSED_T NONNULL_T((1, 2)) KCALL *h_preadv[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
	size_t (BLOCKING WUNUSED_T NONNULL_T((1, 2)) KCALL *h_pwritev[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);

	/* Read a directory entry from the given handle.
	 * @throws: E_WOULDBLOCK: `IO_NONBLOCK' was given and no data/space was available (at the moment)
	 * @return: * : The required buffer size for the current entry */
	size_t (BLOCKING NONNULL_T((1)) KCALL *h_readdir[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, USER CHECKED struct dirent *buf,
	                                                                   size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode)
			THROWS(...);

	/* Seek within the data stream. */
	pos_t (BLOCKING NONNULL_T((1)) KCALL *h_seek[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr,
	                                                               off_t offset,
	                                                               unsigned int whence)
			THROWS(...);

	/* Perform an ioctl() operation.
	 * @throws: E_WOULDBLOCK: `IO_NONBLOCK' was given and no data/space was available (at the moment)
	 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND: [...] */
	syscall_slong_t (BLOCKING NONNULL_T((1)) KCALL *h_ioctl[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, ioctl_t cmd,
	                                                                          USER UNCHECKED void *arg, iomode_t mode)
			THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...);

	/* Change the effective size of the object (s.a. `ftruncate()'). */
	void (BLOCKING NONNULL_T((1)) KCALL *h_truncate[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, pos_t new_size)
			THROWS(...);

	/* Return information on how this handle might be used in a call to `mmap(2)' */
	void (BLOCKING NONNULL_T((1, 2)) KCALL *h_mmap[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr,
	                                                                 struct handle_mmap_info *__restrict info)
			THROWS(...);

	/* @return: * : The amount of newly allocated bytes. */
	pos_t (BLOCKING NONNULL_T((1)) KCALL *h_allocate[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr,
	                                                                   fallocate_mode_t mode,
	                                                                   pos_t start, pos_t length)
			THROWS(...);

	/* Synchronize data */
	void (BLOCKING NONNULL_T((1)) KCALL *h_sync[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr) THROWS(...);
	void (BLOCKING NONNULL_T((1)) KCALL *h_datasync[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr) THROWS(...);

	/* Gather stat-information (s.a. `fstat()')
	 * NOTE: The given `result' will _NOT_ have been initialized already! */
	void (BLOCKING NONNULL_T((1)) KCALL *h_stat[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr,
	                                                              USER CHECKED struct stat *result)
			THROWS(...);

	/* Connect to the signals for monitoring `what' */
	void (BLOCKING NONNULL_T((1)) KCALL *h_pollconnect[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, poll_mode_t what)
			THROWS(...);
	/* @return: * : Set of available signals. */
	poll_mode_t (BLOCKING WUNUSED_T NONNULL_T((1)) KCALL *h_polltest[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, poll_mode_t what)
			THROWS(...);

	/* Try to convert the given object into a handle data pointer of a different type.
	 * If such a conversion isn't possible, this operator should simply return `NULL'.
	 * NOTE: This operator is allowed to throw exceptions, however only as the  result
	 *       of attempting to acquire some kind of lock while preemption was disabled.
	 * The caller must ensure that `wanted_type' isn't already this handle's type. */
	REF void *(BLOCKING NONNULL_T((1)) KCALL *h_tryas[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, uintptr_half_t wanted_type)
			THROWS(E_WOULDBLOCK);

	/* Print the text that should appear when doing `readlink("/proc/[pid]/fd/[fdno]")' */
	ssize_t (BLOCKING NONNULL_T((1, 2)) KCALL *h_printlink[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, __pformatprinter printer, void *arg)
			THROWS(E_WOULDBLOCK, ...);
}
#ifdef __INTELLISENSE__
	const handle_type_db;
#else /* __INTELLISENSE__ */
;
DATDEF struct handle_types const handle_type_db;
#endif /* !__INTELLISENSE__ */


struct handle {
	REF void      *h_data; /* [1..1] Handle data pointer. */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	iomode_t       h_mode; /* Handle I/O mode (Set of `IO_*'). */
	uintptr_half_t h_type; /* Handle type (One of `HANDLE_TYPE_*') */
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	uintptr_half_t h_type; /* Handle type (One of `HANDLE_TYPE_*') */
	iomode_t       h_mode; /* Handle I/O mode (Set of `IO_*'). */
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
};


/* Returns the type-kind code for `self' (One of `HANDLE_TYPEKIND_*') */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_half_t
NOTHROW(KCALL handle_typekind)(struct handle const *__restrict self);
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_half_t
NOTHROW(KCALL mfile_typekind)(struct mfile const *__restrict self);

/* Try to determine the effective data size of the given handle (as returned by `FIOQSIZE')
 * @return: true:  The data size was stored in `*presult'.
 * @return: false: The data size could not be determined. */
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) __BOOL KCALL
handle_datasize(struct handle const *__restrict self,
                pos_t *__restrict presult);

#ifdef __cplusplus
extern "C++" {
FUNDEF NOBLOCK ATTR_PURE WUNUSED uintptr_half_t
NOTHROW(KCALL handle_typekind)(struct handle const &__restrict self)
		ASMNAME("handle_typekind");
FUNDEF BLOCKING WUNUSED NONNULL((2)) __BOOL KCALL
handle_datasize(struct handle const &__restrict self,
                pos_t *__restrict presult)
		ASMNAME("handle_datasize");
} /* extern "C++" */
#endif /* __cplusplus */


#define HANDLE_FUNC(self, name) (*handle_type_db.name[(self).h_type])

#define /*        */ handle_typename(self)                                    handle_type_db.h_typename[(self).h_type]
#define /*        */ handle_incref(self)                                      HANDLE_FUNC(self, h_incref)((self).h_data)
#define /*        */ handle_decref(self)                                      HANDLE_FUNC(self, h_decref)((self).h_data)
#define /*        */ handle_refcnt(self)                                      HANDLE_FUNC(self, h_refcnt)((self).h_data)
#define /*        */ handle_tryincref(self)                                   HANDLE_FUNC(self, h_tryincref)((self).h_data)
#define /*        */ handle_weakgetref(self)                                  HANDLE_FUNC(self, h_weakgetref)((self).h_data)
#define /*BLOCKING*/ handle_read(self, dst, num_bytes)                        HANDLE_FUNC(self, h_read)((self).h_data, dst, num_bytes, (self).h_mode)
#define /*BLOCKING*/ handle_write(self, src, num_bytes)                       HANDLE_FUNC(self, h_write)((self).h_data, src, num_bytes, (self).h_mode)
#define /*BLOCKING*/ handle_readf(self, dst, num_bytes, mode)                 HANDLE_FUNC(self, h_read)((self).h_data, dst, num_bytes, mode)
#define /*BLOCKING*/ handle_writef(self, src, num_bytes, mode)                HANDLE_FUNC(self, h_write)((self).h_data, src, num_bytes, mode)
#define /*BLOCKING*/ handle_readv(self, dst, num_bytes)                       HANDLE_FUNC(self, h_readv)((self).h_data, dst, num_bytes, (self).h_mode)
#define /*BLOCKING*/ handle_writev(self, src, num_bytes)                      HANDLE_FUNC(self, h_writev)((self).h_data, src, num_bytes, (self).h_mode)
#define /*BLOCKING*/ handle_readvf(self, dst, num_bytes, mode)                HANDLE_FUNC(self, h_readv)((self).h_data, dst, num_bytes, mode)
#define /*BLOCKING*/ handle_writevf(self, src, num_bytes, mode)               HANDLE_FUNC(self, h_writev)((self).h_data, src, num_bytes, mode)
#define /*BLOCKING*/ handle_pread(self, dst, num_bytes, addr)                 HANDLE_FUNC(self, h_pread)((self).h_data, dst, num_bytes, addr, (self).h_mode)
#define /*BLOCKING*/ handle_pwrite(self, src, num_bytes, addr)                HANDLE_FUNC(self, h_pwrite)((self).h_data, src, num_bytes, addr, (self).h_mode)
#define /*BLOCKING*/ handle_preadf(self, dst, num_bytes, addr, mode)          HANDLE_FUNC(self, h_pread)((self).h_data, dst, num_bytes, addr, mode)
#define /*BLOCKING*/ handle_pwritef(self, src, num_bytes, addr, mode)         HANDLE_FUNC(self, h_pwrite)((self).h_data, src, num_bytes, addr, mode)
#define /*BLOCKING*/ handle_preadv(self, dst, num_bytes, addr)                HANDLE_FUNC(self, h_preadv)((self).h_data, dst, num_bytes, addr, (self).h_mode)
#define /*BLOCKING*/ handle_pwritev(self, src, num_bytes, addr)               HANDLE_FUNC(self, h_pwritev)((self).h_data, src, num_bytes, addr, (self).h_mode)
#define /*BLOCKING*/ handle_preadvf(self, dst, num_bytes, addr, mode)         HANDLE_FUNC(self, h_preadv)((self).h_data, dst, num_bytes, addr, mode)
#define /*BLOCKING*/ handle_pwritevf(self, src, num_bytes, addr, mode)        HANDLE_FUNC(self, h_pwritev)((self).h_data, src, num_bytes, addr, mode)
#define /*BLOCKING*/ handle_readdir(self, buf, bufsize, readdir_mode)         HANDLE_FUNC(self, h_readdir)((self).h_data, buf, bufsize, readdir_mode, (self).h_mode)
#define /*BLOCKING*/ handle_readdirf(self, buf, bufsize, readdir_mode, mode)  HANDLE_FUNC(self, h_readdir)((self).h_data, buf, bufsize, readdir_mode, mode)
#define /*BLOCKING*/ handle_seek(self, off, whence)                           HANDLE_FUNC(self, h_seek)((self).h_data, off, whence)
#define /*BLOCKING*/ handle_ioctl(self, cmd, arg)                             HANDLE_FUNC(self, h_ioctl)((self).h_data, cmd, arg, (self).h_mode)
#define /*BLOCKING*/ handle_ioctlf(self, cmd, arg, flags)                     HANDLE_FUNC(self, h_ioctl)((self).h_data, cmd, arg, flags)
#define /*BLOCKING*/ handle_truncate(self, new_size)                          HANDLE_FUNC(self, h_truncate)((self).h_data, new_size)
#define /*BLOCKING*/ handle_mmap(self, info)                                  HANDLE_FUNC(self, h_mmap)((self).h_data, info)
#define /*BLOCKING*/ handle_allocate(self, mode, start, length)               HANDLE_FUNC(self, h_allocate)((self).h_data, mode, start, length)
#define /*BLOCKING*/ handle_sync(self)                                        HANDLE_FUNC(self, h_sync)((self).h_data)
#define /*BLOCKING*/ handle_datasync(self)                                    HANDLE_FUNC(self, h_datasync)((self).h_data)
#define /*BLOCKING*/ handle_stat(self, result)                                HANDLE_FUNC(self, h_stat)((self).h_data, result)
#define /*BLOCKING*/ handle_pollconnect(self, what)                           HANDLE_FUNC(self, h_pollconnect)((self).h_data, what)
#define /*BLOCKING*/ handle_polltest(self, what)                              HANDLE_FUNC(self, h_polltest)((self).h_data, what)
#define /*BLOCKING*/ handle_poll(self, what)                                  _handle_poll(&(self), what)
#define /*BLOCKING*/ _handle_tryas(self, wanted_type)                         HANDLE_FUNC(self, h_tryas)((self).h_data, wanted_type)
#define /*BLOCKING*/ handle_printlink(self, printer, arg)                     HANDLE_FUNC(self, h_printlink)((self).h_data, printer, arg)

FORCELOCAL BLOCKING ATTR_ARTIFICIAL WUNUSED NONNULL((1)) poll_mode_t KCALL
_handle_poll(struct handle *__restrict self, poll_mode_t what) {
	poll_mode_t result;
#ifndef __OPTIMIZE_SIZE__
	result = handle_polltest(*self, what);
	if (result == 0)
#endif /* !__OPTIMIZE_SIZE__ */
	{
		handle_pollconnect(*self, what);
		result = handle_polltest(*self, what);
	}
	return result;
}

#ifdef __cplusplus
extern "C++" {

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL struct handle const &
NOTHROW(KCALL incref)(struct handle const &__restrict self) {
	handle_incref(self);
	return self;
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(KCALL decref)(struct handle const &__restrict self) {
	handle_decref(self);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(KCALL decref_likely)(struct handle const &__restrict self) {
	handle_decref(self);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(KCALL decref_unlikely)(struct handle const &__restrict self) {
	handle_decref(self);
}

} /* extern "C++" */
#endif /* __cplusplus */

/* Cast  the given handle `self' into `wanted_type', and return a reference
 * to a handle-compatible object with type `wanted_type'. If such a cast is
 * impossible, an `E_INVALID_HANDLE_FILETYPE' error is thrown.
 * NOTE: This function also inherits a reference to `self' (unless an exception is thrown) */
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF void *FCALL
handle_as(/*inherit(on_success)*/ REF struct handle const *__restrict self, uintptr_half_t wanted_type)
		THROWS(E_INVALID_HANDLE_FILETYPE);
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF void *FCALL
handle_as_noinherit(struct handle const *__restrict self, uintptr_half_t wanted_type)
		THROWS(E_INVALID_HANDLE_FILETYPE);

FORCELOCAL BLOCKING WUNUSED REF void *FCALL
handle_tryas(/*inherit(on_success)*/ REF struct handle const *__restrict self, uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	REF void *result;
	if unlikely(self->h_type == wanted_type)
		return self->h_data; /* Inherit reference */
	result = _handle_tryas(*self, wanted_type);
	if (result)
		handle_decref(*self);
	return result;
}

FORCELOCAL BLOCKING WUNUSED REF void *FCALL
handle_tryas_noinherit(struct handle const *__restrict self,
                       uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	if unlikely(self->h_type == wanted_type)
		return self->h_data; /* Inherit reference */
	return _handle_tryas(*self, wanted_type);
}

/* Extended handle converted functions */

#define handle_as_mfile(self)   ((REF struct mfile *)handle_as(self, HANDLE_TYPE_MFILE))
#define handle_as_fdirent(self) ((REF struct fdirent *)handle_as(self, HANDLE_TYPE_DIRENT))
#define handle_as_path(self)    ((REF struct path *)handle_as(self, HANDLE_TYPE_PATH))
#define handle_as_taskpid(self) ((REF struct taskpid *)handle_as(self, HANDLE_TYPE_PIDFD))
#define handle_as_pipe(self)    ((REF struct pipe *)handle_as(self, HANDLE_TYPE_PIPE))
#define handle_as_module(self)  ((REF struct driver *)handle_as(self, HANDLE_TYPE_MODULE))
#define handle_as_socket(self)  ((REF struct socket *)handle_as(self, HANDLE_TYPE_SOCKET))

#if defined(__cplusplus) && !defined(NO_CXX_HANDLE_AS_OVERLOADS)
extern "C++" {
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED REF void *FCALL
handle_as(/*inherit(on_success)*/ REF struct handle const &__restrict self,
          uintptr_half_t wanted_type)
		THROWS(E_INVALID_HANDLE_FILETYPE)
		ASMNAME("handle_as");
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED REF void *FCALL
handle_as_noinherit(/*inherit(on_success)*/ REF struct handle const &__restrict self,
                    uintptr_half_t wanted_type)
		THROWS(E_INVALID_HANDLE_FILETYPE)
		ASMNAME("handle_as_noinherit");

FORCELOCAL BLOCKING WUNUSED REF void *FCALL
handle_tryas(/*inherit(on_success)*/ REF struct handle const &__restrict self,
             uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	return handle_tryas(&self, wanted_type);
}

FORCELOCAL BLOCKING WUNUSED REF void *FCALL
handle_tryas_noinherit(struct handle const &__restrict self,
                       uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	return handle_tryas_noinherit(&self, wanted_type);
}
} /* extern "C++" */
#endif /* __cplusplus && !NO_CXX_HANDLE_AS_OVERLOADS */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_H */
