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

DECL_BEGIN

/* Management of user-space descriptors  for kernel data, here  called
 * handles,   but  referred  to  as  file-descriptors  in  user-space.
 * The associated user-space data type is `fd_t', which aliases `int',
 * which  is  why  the  kernel  uses  `unsigned int'  as  its internal
 * descriptor type. */


#ifdef __CC__
struct dirent;
struct stat;
struct aio_multihandle;
struct path;
struct fdirent;

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
	refcnt_t /*NOTHROW*/ (NOBLOCK WUNUSED NONNULL((1)) FCALL *h_refcnt[HANDLE_TYPE_COUNT])(/*T*/ void const *__restrict ptr);
	void /*NOTHROW*/ (NOBLOCK NONNULL((1)) FCALL *h_incref[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr);
	void /*NOTHROW*/ (NOBLOCK NONNULL((1)) FCALL *h_decref[HANDLE_TYPE_COUNT])(REF /*T*/ void *__restrict ptr);
	__BOOL /*NOTHROW*/ (NOBLOCK NONNULL((1)) FCALL *h_tryincref[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr);

	/* ============== Weak reference counting API */
	WEAK REF void * /*NOTHROW*/ (NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) FCALL *h_weakgetref[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr);
	REF /*T*/ void * /*NOTHROW*/ (NOBLOCK WUNUSED NONNULL((1)) FCALL *h_weaklckref[HANDLE_TYPE_COUNT])(void *__restrict weakref_ptr);
	void /*NOTHROW*/ (NOBLOCK NONNULL((1)) FCALL *h_weakdecref[HANDLE_TYPE_COUNT])(WEAK REF void *__restrict weakref_ptr);

	/* Basic read/write primitives.
	 * @throws: E_WOULDBLOCK: `IO_NONBLOCK' was given and no data/space was available (at the moment)
	 * @return: 0 : EOF has been reached
	 * @return: * : The amount of read/written bytes (`<= num_bytes') */
	size_t (BLOCKING WUNUSED NONNULL((1)) KCALL *h_read[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) /*THROWS(...)*/;
	size_t (BLOCKING WUNUSED NONNULL((1)) KCALL *h_write[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, iomode_t mode) /*THROWS(...)*/;

	/* Position-based read/write primitives.
	 * @throws: * : Same as `h_read' / `h_write'
	 * @return: * : Same as `h_read' / `h_write' */
	size_t (BLOCKING WUNUSED NONNULL((1)) KCALL *h_pread[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, USER CHECKED void *dst, size_t num_bytes, pos_t addr, iomode_t mode) /*THROWS(...)*/;
	size_t (BLOCKING WUNUSED NONNULL((1)) KCALL *h_pwrite[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, USER CHECKED void const *src, size_t num_bytes, pos_t addr, iomode_t mode) /*THROWS(...)*/;

	/* Vector-based read/write primitives.
	 * @throws: * : Same as `h_read' / `h_write'
	 * @return: * : Same as `h_read' / `h_write' */
	size_t (BLOCKING WUNUSED NONNULL((1, 2)) KCALL *h_readv[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, struct iov_buffer *__restrict dst, size_t num_bytes, iomode_t mode) /*THROWS(...)*/;
	size_t (BLOCKING WUNUSED NONNULL((1, 2)) KCALL *h_writev[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, struct iov_buffer *__restrict src, size_t num_bytes, iomode_t mode) /*THROWS(...)*/;
	size_t (BLOCKING WUNUSED NONNULL((1, 2)) KCALL *h_preadv[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, struct iov_buffer *__restrict dst, size_t num_bytes, pos_t addr, iomode_t mode) /*THROWS(...)*/;
	size_t (BLOCKING WUNUSED NONNULL((1, 2)) KCALL *h_pwritev[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, struct iov_buffer *__restrict src, size_t num_bytes, pos_t addr, iomode_t mode) /*THROWS(...)*/;

	/* Read a directory entry from the given handle.
	 * @throws: E_WOULDBLOCK: `IO_NONBLOCK' was given and no data/space was available (at the moment)
	 * @return: * : The required buffer size for the current entry */
	size_t (BLOCKING NONNULL((1)) KCALL *h_readdir[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, USER CHECKED struct dirent *buf,
	                                                                   size_t bufsize, readdir_mode_t readdir_mode, iomode_t mode)
			/*THROWS(...)*/;

	/* Seek within the data stream. */
	pos_t (BLOCKING NONNULL((1)) KCALL *h_seek[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr,
	                                                               off_t offset,
	                                                               unsigned int whence)
			/*THROWS(...)*/;

	/* Perform an ioctl() operation.
	 * @throws: E_WOULDBLOCK: `IO_NONBLOCK' was given and no data/space was available (at the moment)
	 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND: [...] */
	syscall_slong_t (BLOCKING NONNULL((1)) KCALL *h_ioctl[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, ioctl_t cmd,
	                                                                          USER UNCHECKED void *arg, iomode_t mode)
			/*THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...)*/;

	/* Change the effective size of the object (s.a. `ftruncate()'). */
	void (BLOCKING NONNULL((1)) KCALL *h_truncate[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, pos_t new_size)
			/*THROWS(...)*/;

	/* Return information on how this handle might be used in a call to `mmap(2)' */
	void (BLOCKING NONNULL((1, 2)) KCALL *h_mmap[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr,
	                                                                 struct handle_mmap_info *__restrict info)
			/*THROWS(...)*/;

	/* @return: * : The amount of newly allocated bytes. */
	pos_t (BLOCKING NONNULL((1)) KCALL *h_allocate[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr,
	                                                                   fallocate_mode_t mode,
	                                                                   pos_t start, pos_t length)
			/*THROWS(...)*/;

	/* Synchronize data */
	void (BLOCKING NONNULL((1)) KCALL *h_sync[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr) /*THROWS(...)*/;
	void (BLOCKING NONNULL((1)) KCALL *h_datasync[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr) /*THROWS(...)*/;

	/* Gather stat-information (s.a. `fstat()')
	 * NOTE: The given `result' will _NOT_ have been initialized already! */
	void (BLOCKING NONNULL((1)) KCALL *h_stat[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr,
	                                                              USER CHECKED struct stat *result)
			/*THROWS(...)*/;

	/* Connect to the signals for monitoring `what' */
	void (BLOCKING NONNULL((1)) KCALL *h_pollconnect[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, poll_mode_t what)
			/*THROWS(...)*/;
	/* @return: * : Set of available signals. */
	poll_mode_t (BLOCKING WUNUSED NONNULL((1)) KCALL *h_polltest[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, poll_mode_t what)
			/*THROWS(...)*/;

	/* Try to convert the given object into a handle data pointer of a different type.
	 * If such a conversion isn't possible, this operator should simply return `NULL'.
	 * NOTE: This operator is allowed to throw exceptions, however only as the  result
	 *       of attempting to acquire some kind of lock while preemption was disabled.
	 * The caller must ensure that `wanted_type' isn't already this handle's type. */
	REF void *(BLOCKING NONNULL((1)) KCALL *h_tryas[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, uintptr_half_t wanted_type)
			/*THROWS(E_WOULDBLOCK)*/;

	/* Print the text that should appear when doing `readlink("/proc/[pid]/fd/[fdno]")' */
	ssize_t (BLOCKING NONNULL((1, 2)) KCALL *h_printlink[HANDLE_TYPE_COUNT])(/*T*/ void *__restrict ptr, __pformatprinter printer, void *arg)
			/*THROWS(E_WOULDBLOCK, ...)*/;
}
#ifdef __INTELLISENSE__
	const handle_type_db;
#else /* __INTELLISENSE__ */
;
DATDEF struct handle_types const handle_type_db;
#endif /* !__INTELLISENSE__ */
#endif /* __CC__ */

#ifdef __CC__

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

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL NONNULL((1)) struct handle const *
NOTHROW(KCALL incref)(struct handle const *__restrict self) {
	return &incref(*self);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL NONNULL((1)) void
NOTHROW(KCALL decref)(struct handle const *__restrict self) {
	decref(*self);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL NONNULL((1)) void
NOTHROW(KCALL decref_likely)(struct handle const *__restrict self) {
	decref_likely(*self);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL NONNULL((1)) void
NOTHROW(KCALL decref_unlikely)(struct handle const *__restrict self) {
	decref_unlikely(*self);
}

} /* extern "C++" */
#endif /* __cplusplus */

struct fnode;
struct fdirent;
struct mfile;
struct fsuper;
struct path;
struct taskpid;
struct task;
struct mman;
struct pipe;
struct driver;
struct pidns;
struct socket;
struct epoll_controller;

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



#endif /* __CC__ */




#ifndef CONFIG_USE_NEW_HANDMAN
#ifdef __CC__
struct handle_hashent {
#define HANDLE_HASHENT_SENTINEL_ID ((unsigned int)-1)
	unsigned int   hh_handle_id;    /* The handle ID in question (or `HANDLE_HASHENT_SENTINEL_ID' for sentinel) */
	unsigned int   hh_vector_index; /* [valid_if(hh_handle_id != HANDLE_HASHENT_SENTINEL_ID)]
	                                 * Index into `hm_vector', where the associated handle is mapped.
	                                 * NOTE: Set to `(unsigned int)-1' when deleted. */
};
struct handle_manager {
	WEAK refcnt_t        hm_refcnt;   /* Reference counter. */
	struct atomic_rwlock hm_lock;     /* Lock for this handle manager's control structures. */
	unsigned int         hm_cntlimit; /* [lock(hm_lock)] The max number of handles which may be bound.
	                                   * NOTE:  May  not   be  set  to   `HANDLE_HASHENT_SENTINEL_ID'! */
	unsigned int         hm_maxlimit; /* [lock(hm_lock)] The max allowed handle number which may be used.
	                                   * NOTE:  May   not   be   set   to   `HANDLE_HASHENT_SENTINEL_ID'! */
	unsigned int         hm_count;    /* [lock(hm_lock)] Number of handles currently in use. */
	unsigned int         hm_minfree;  /* [lock(hm_lock)] Lowest handle index that is potentially unused.
	                                   * When searching for a new, unused handle, start searching  here. */
	unsigned int         hm_mode;     /* [lock(hm_lock)] Handle manager operations mode (one of `HANDLE_MANAGER_MODE_*'). */
#define HANDLE_MANAGER_MODE_LINEAR     0x0000 /* Handles are indexed linearly. */
#define HANDLE_MANAGER_MODE_HASHVECTOR 0x0001 /* Handles are indexed via hash-vector indirection. */
	unsigned int         hm_clofork_count; /* [lock(hm_lock)] Number of handles with the `IO_CLOFORK' flag set. */
	unsigned int         hm_cloexec_count; /* [lock(hm_lock)] Number of handles with the `IO_CLOEXEC' flag set. */
	union {
		struct {
			unsigned int   hm_alloc;  /* [lock(hm_lock)] Allocated number of handles. */
			struct handle *hm_vector; /* [0..hm_alloc][owned] Vector of handles. (index == handle-number) */
		}                hm_linear;   /* HANDLE_MANAGER_MODE_LINEAR */
		struct {
			unsigned int   hm_alloc;  /* [lock(hm_lock)] Allocated size of `hm_vector'. */
			struct handle *hm_vector; /* [0..hm_alloc][owned] Vector of handles. (index == hm_hashvec[*].hh_vector_index) */
			struct handle_hashent
			              *hm_hashvec;/* [lock(hm_lock)][1..hm_hashmsk+1][owned] Hash-vector for translating
			                           * handle  IDs   from  `fd_t'   into   an  index   into   `hm_vector'. */
			unsigned int   hm_hashmsk;/* [lock(hm_lock)] Hash-mask for `hm_hashvec'. */
			unsigned int   hm_hashuse;/* [lock(hm_lock)] Number of used handle_hashent (i.e. ones with
			                           * `hh_handle_id != HANDLE_HASHENT_SENTINEL_ID').
			                           * Note  that this is very similar to `hm_count', but includes handles
			                           * that have been deleted (i.e. `hh_vector_index == (unsigned int)-1') */
			unsigned int   hm_vecfree;/* [lock(hm_lock)] Lowest index in `hm_vector' that may contain an unused slot. */
#define handle_manager_hashnext(i, perturb) ((i) = (((i) << 2) + (i) + (perturb) + 1), (perturb) >>= 5)
		}                hm_hashvector; /* HANDLE_MANAGER_MODE_HASHVECTOR */
	};
};

/* Helpers for accessing `hm_lock' */
#define _handle_manager_reap(self)        (void)0
#define handle_manager_reap(self)         (void)0
#define handle_manager_mustreap(self)     0
#define handle_manager_write(self)        atomic_rwlock_write(&(self)->hm_lock)
#define handle_manager_write_nx(self)     atomic_rwlock_write_nx(&(self)->hm_lock)
#define handle_manager_trywrite(self)     atomic_rwlock_trywrite(&(self)->hm_lock)
#define handle_manager_endwrite(self)     (atomic_rwlock_endwrite(&(self)->hm_lock), handle_manager_reap(self))
#define _handle_manager_endwrite(self)    atomic_rwlock_endwrite(&(self)->hm_lock)
#define handle_manager_read(self)         atomic_rwlock_read(&(self)->hm_lock)
#define handle_manager_read_nx(self)      atomic_rwlock_read_nx(&(self)->hm_lock)
#define handle_manager_tryread(self)      atomic_rwlock_tryread(&(self)->hm_lock)
#define _handle_manager_endread(self)     atomic_rwlock_endread(&(self)->hm_lock)
#define handle_manager_endread(self)      (void)(atomic_rwlock_endread(&(self)->hm_lock) && (handle_manager_reap(self), 0))
#define _handle_manager_end(self)         atomic_rwlock_end(&(self)->hm_lock)
#define handle_manager_end(self)          (void)(atomic_rwlock_end(&(self)->hm_lock) && (handle_manager_reap(self), 0))
#define handle_manager_upgrade(self)      atomic_rwlock_upgrade(&(self)->hm_lock)
#define handle_manager_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->hm_lock)
#define handle_manager_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->hm_lock)
#define handle_manager_downgrade(self)    atomic_rwlock_downgrade(&(self)->hm_lock)
#define handle_manager_reading(self)      atomic_rwlock_reading(&(self)->hm_lock)
#define handle_manager_writing(self)      atomic_rwlock_writing(&(self)->hm_lock)
#define handle_manager_canread(self)      atomic_rwlock_canread(&(self)->hm_lock)
#define handle_manager_canwrite(self)     atomic_rwlock_canwrite(&(self)->hm_lock)
#define handle_manager_waitread(self)     atomic_rwlock_waitread(&(self)->hm_lock)
#define handle_manager_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->hm_lock)
#define handle_manager_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->hm_lock)
#define handle_manager_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->hm_lock)


/* Destroy the given handle manager. */
FUNDEF NOBLOCK void
NOTHROW(KCALL handle_manager_destroy)(struct handle_manager *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct handle_manager, hm_refcnt, handle_manager_destroy)

/* Copy the given handle manager (exclusing `IO_CLOFORK' handles) */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL REF struct handle_manager *KCALL
handle_manager_clone(struct handle_manager *__restrict self)
		THROWS(E_BADALLOC, E_WOULDBLOCK);

#ifdef NDEBUG
#define handle_manager_assert_integrity(self) (void)0
#else /* NDEBUG */
FUNDEF NONNULL((1)) void
NOTHROW(FCALL handle_manager_assert_integrity)(struct handle_manager *__restrict self);
#endif /* !NDEBUG */


/* The handle manager of the kernel itself. */
DATDEF struct handle_manager handle_manager_kernel;

/* [1..1][lock(read(THIS_TASK || INTERN(lock)),
 *             write(THIS_TASK && INTERN(lock)))]
 * Handle manager of the calling thread. */
DATDEF ATTR_PERTASK struct handle_manager *this_handle_manager;
#define THIS_HANDLE_MANAGER    PERTASK_GET(this_handle_manager)

/* Return the handle manager of the given thread. */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct handle_manager *
NOTHROW(FCALL task_gethandlemanager)(struct task *__restrict thread);

/* Exchange the handle manager of the calling thread (and return the old one). */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct handle_manager *
NOTHROW(FCALL task_sethandlemanager)(struct handle_manager *__restrict newman);


/* Close all handles with the `IO_FCLOEXEC' flag set.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked. */
FUNDEF NONNULL((1)) void FCALL
handle_manager_cloexec(struct handle_manager *__restrict self)
		THROWS(E_WOULDBLOCK);

/* Try to close the handle associated with `fd'.
 * @return: true:  The handle under `fd' was closed.
 * @return: false: No handle was associated with `fd'.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked. */
FUNDEF __BOOL FCALL
handle_tryclose(unsigned int fd)
		THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((2)) __BOOL FCALL
handle_tryclose_nosym(unsigned int fd,
                      struct handle_manager *__restrict self)
		THROWS(E_WOULDBLOCK);

/* Same as `handle_tryclose()', but throw an error if the given `fd' is invalid */
FUNDEF void FCALL handle_close(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

/* Same as `handle_tryclose_nosym()', but throw an error if the given `fd' is invalid */
FUNDEF NONNULL((2)) void FCALL
handle_close_nosym(unsigned int fd,
                   struct handle_manager *__restrict self)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

/* Close all open file handles `>= fd' and return how many were actually closed.
 * If nothing was closed  at all (i.e. what  would be `return == 0'), then  this
 * function  returns by throwing  an `E_INVALID_HANDLE_FILE' (-EBADF) exception. */
FUNDEF NONNULL((2)) unsigned int FCALL
handle_closefrom_nosym(unsigned int startfd,
                       struct handle_manager *__restrict self)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

/* Return the next valid FD that is `>= startfd'
 * If no such FD exists, throw an `E_INVALID_HANDLE_FILE' exception */
FUNDEF NONNULL((2)) unsigned int FCALL
handle_nextfd(unsigned int startfd,
              struct handle_manager *__restrict self)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);
/* Same as `handle_nextfd()', but return `(unsigned int)-1' instead of throwing `E_INVALID_HANDLE_FILE'
 * @param: p_data: Filled with `HANDLE.h_data' (used for ino numbers in procfs) */
FUNDEF NONNULL((2, 3)) unsigned int FCALL
handle_trynextfd(unsigned int startfd,
                 struct handle_manager *__restrict self,
                 void **__restrict p_data)
		THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((2, 3)) unsigned int
NOTHROW(FCALL handle_trynextfd_locked)(unsigned int startfd,
                                       struct handle_manager *__restrict self,
                                       struct handle *__restrict phand);


/* Modify the I/O-flags of a given file handle
 * The new I/O flags are calculated as `(old_flags & mask) | flag'
 * @return: * :  The handle's old I/O-flags */
FUNDEF NONNULL((1)) iomode_t FCALL
handle_chflags(struct handle_manager *__restrict self,
               unsigned int fd, iomode_t mask, iomode_t flag)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);


/* Add the given handle  to the handle manager  and
 * return the handle number of where it was placed.
 * @throw: E_BADALLOC: Insufficient kernel memory to allocate more handle slots
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: Too many open handles
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_RANGE: Too many open handles
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked */
FUNDEF NONNULL((1, 2)) unsigned int FCALL
handle_install(struct handle_manager *__restrict self,
               struct handle const *__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE);

/* Similar to  `handle_put()', but  place  the handle  in  a
 * descriptor slot that is greater than, or equal to `hint'.
 * @throw: E_BADALLOC: Insufficient kernel memory to allocate more handle slots
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: Too many open handles
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_RANGE: `hint' is outside the allowed handle range.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked */
FUNDEF NONNULL((1, 3)) unsigned int FCALL
handle_installat(struct handle_manager *__restrict self,
                 unsigned int hint,
                 struct handle const *__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE);

/* Place the given handle into the specified handle slot `dst_fd'.
 * @throw: E_BADALLOC: Insufficient kernel memory to allocate more handle slots
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: Too many open handles
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_RANGE: `dst_fd' is outside the allowed handle range.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked */
FUNDEF NONNULL((1, 3)) void FCALL
handle_installinto(struct handle_manager *__restrict self,
                   unsigned int dst_fd,
                   struct handle const *__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE);

/* Same  as `handle_installinto()', but  return the old handle
 * (or a HANDLE_TYPE_UNDEFINED) previously bound to that slot. */
FUNDEF WUNUSED NONNULL((1, 3)) REF struct handle FCALL
handle_installxchg(struct handle_manager *__restrict self,
                   unsigned int dst_fd,
                   struct handle const *__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE);



struct openfd;
/* Do everything required to install a handle via a open openfd
 * command data  packet that  has been  passed via  user-space.
 * Note that `data' is an UNCHECKED user pointer! */
FUNDEF NONNULL((2)) unsigned int FCALL
handle_installopenfd(USER UNCHECKED struct openfd *data,
                     struct handle const *__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE,
		       E_SEGFAULT, E_INVALID_ARGUMENT);


/* Same as `handle_installinto()', but allow `dst_fd' to be a writable, symbolic handle.
 * @throw: E_BADALLOC: Insufficient kernel memory to allocate more handle slots
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS: Too many open handles
 * @throw: E_BADALLOC_INSUFFICIENT_HANDLE_RANGE: `dst_fd' is outside the allowed handle range.
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked */
FUNDEF NONNULL((2)) void FCALL
handle_installinto_sym(unsigned int dst_fd,
                       struct handle const *__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE);

#ifdef __cplusplus
extern "C++" {
FUNDEF NONNULL((1)) unsigned int FCALL
handle_install(struct handle_manager *__restrict self,
               struct handle const &__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE)
		ASMNAME("handle_install");
FUNDEF NONNULL((1)) unsigned int FCALL
handle_installat(struct handle_manager *__restrict self,
                 unsigned int hint,
                 struct handle const &__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE)
		ASMNAME("handle_installat");
FUNDEF NONNULL((1)) void FCALL
handle_installinto(struct handle_manager *__restrict self,
                   unsigned int dst_fd,
                   struct handle const &__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE)
		ASMNAME("handle_installinto");
FUNDEF WUNUSED NONNULL((1)) REF struct handle FCALL
handle_installxchg(struct handle_manager *__restrict self,
                   unsigned int dst_fd,
                   struct handle const &__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE)
		ASMNAME("handle_installxchg");
FUNDEF unsigned int FCALL
handle_installopenfd(USER UNCHECKED struct openfd *data,
                     struct handle const &__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE,
		       E_SEGFAULT, E_INVALID_ARGUMENT)
		ASMNAME("handle_installopenfd");
FUNDEF void FCALL
handle_installinto_sym(unsigned int dst_fd,
                       struct handle const &__restrict hnd)
		THROWS(E_WOULDBLOCK, E_BADALLOC,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE)
		ASMNAME("handle_installinto_sym");
} /* extern "C++" */
#endif /* __cplusplus */


/* The kernel-space equivalent of the user-space `fcntl()' function.
 * @param: cmd: One of `F_*' from <kos/io.h> */
FUNDEF NONNULL((1)) syscall_ulong_t KCALL
handle_fcntl(struct handle_manager *__restrict self,
             unsigned int fd, fcntl_t cmd,
             UNCHECKED USER void *arg)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_BADALLOC_INSUFFICIENT_HANDLE_RANGE,
		       E_WOULDBLOCK, E_BADALLOC, ...);


/* Lookup a given fd-number and return the associated handle.
 * NOTE: When `fd' doesn't refer to a valid handle, the returned
 *       handle  has  its type  set  to `HANDLE_TYPE_UNDEFINED'.
 * NOTE: This function also handles symbolic file descriptors!
 * @throw: E_WOULDBLOCK: Preemption was disabled, and the operation would have blocked */
FUNDEF WUNUSED REF struct handle FCALL
handle_trylookup(struct handle_manager *__restrict self,
                 unsigned int fd)
		THROWS(E_WOULDBLOCK);

/* Same as `handle_trylookup()', but throw an error when `fd' is invalid. */
FUNDEF WUNUSED REF struct handle FCALL
handle_lookup(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

FUNDEF WUNUSED REF struct handle FCALL
handle_lookupin(unsigned int fd, struct handle_manager *__restrict self)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);

/* Same as `handle_lookup()', but don't allow for symbolic handles. */
FUNDEF WUNUSED REF struct handle FCALL
handle_lookup_nosym(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE);


struct fnode;
struct fdirent;
struct mfile;
struct fsuper;
struct path;
struct taskpid;
struct task;
struct mman;
struct pipe;
struct driver;
struct pidns;
struct socket;
struct epoll_controller;

/* Directly translate handlers to references to objects of specific types. */
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED REF void *FCALL
handle_getas(unsigned int fd, uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE);

FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED REF struct fnode *FCALL
handle_get_fnode(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE);

FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED REF struct fsuper *FCALL
handle_get_fsuper_relaxed(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE);

/* @throw: E_PROCESS_EXITED: `fd' belongs to a task that is no longer allocated. */
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED REF struct task *FCALL
handle_get_task(unsigned int fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE, E_PROCESS_EXITED);

#define handle_get_mfile(fd)            ((REF struct mfile *)handle_getas(fd, HANDLE_TYPE_MFILE))
#define handle_get_fdirent(fd)          ((REF struct fdirent *)handle_getas(fd, HANDLE_TYPE_DIRENT))
#define handle_get_path(fd)             ((REF struct path *)handle_getas(fd, HANDLE_TYPE_PATH))
#define handle_get_taskpid(fd)          ((REF struct taskpid *)handle_getas(fd, HANDLE_TYPE_PIDFD))
#define handle_get_pipe(fd)             ((REF struct pipe *)handle_getas(fd, HANDLE_TYPE_PIPE))
#define handle_get_module(fd)           ((REF struct driver *)handle_getas(fd, HANDLE_TYPE_MODULE))
#define handle_get_socket(fd)           ((REF struct socket *)handle_getas(fd, HANDLE_TYPE_SOCKET))
#define handle_get_epoll_controller(fd) ((REF struct epoll_controller *)handle_getas(fd, HANDLE_TYPE_EPOLL))

#endif /* __CC__ */
#endif /* !CONFIG_USE_NEW_HANDMAN */

DECL_END

#ifdef CONFIG_USE_NEW_HANDMAN
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_HANDMAN_H
#include <kernel/handman.h>
#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_HANDMAN_H */

/* Backwards compatibility */
#define handle_manager_assert_integrity(self) (void)0
#define handle_manager              handman
#define _handle_manager_reap        _handman_reap
#define handle_manager_reap         handman_reap
#define handle_manager_mustreap     handman_mustreap
#define handle_manager_write        handman_write
#define handle_manager_write_nx     handman_write_nx
#define handle_manager_trywrite     handman_trywrite
#define handle_manager_endwrite     handman_endwrite
#define _handle_manager_endwrite    _handman_endwrite
#define handle_manager_read         handman_read
#define handle_manager_read_nx      handman_read_nx
#define handle_manager_tryread      handman_tryread
#define _handle_manager_endread     _handman_endread
#define handle_manager_endread      handman_endread
#define _handle_manager_end         _handman_end
#define handle_manager_end          handman_end
#define handle_manager_upgrade      handman_upgrade
#define handle_manager_upgrade_nx   handman_upgrade_nx
#define handle_manager_tryupgrade   handman_tryupgrade
#define handle_manager_downgrade    handman_downgrade
#define handle_manager_reading      handman_reading
#define handle_manager_writing      handman_writing
#define handle_manager_canread      handman_canread
#define handle_manager_canwrite     handman_canwrite
#define handle_manager_waitread     handman_waitread
#define handle_manager_waitwrite    handman_waitwrite
#define handle_manager_waitread_nx  handman_waitread_nx
#define handle_manager_waitwrite_nx handman_waitwrite_nx
#define handle_manager_destroy      handman_destroy
#define handle_manager_clone        handman_fork
#define handle_manager_kernel       handman_kernel
#define this_handle_manager         this_handman
#define THIS_HANDLE_MANAGER         THIS_HANDMAN
#define task_gethandlemanager       task_gethandman
#define task_sethandlemanager       task_sethandman
#define handle_manager_cloexec      handman_cloexec

/* TODO: When eventually removing the following, make sure to get rid of `(unsigned int)' casts. */
#define handle_install(self, hnd)             ((unsigned int)handman_install(self, hnd))
#define handle_installat(self, hint, hnd)     ((unsigned int)handman_install(self, hnd, (fd_t)(hint)))
#define handle_installinto(self, dst_fd, hnd) ((unsigned int)handman_install_into_simple(self, (fd_t)(dst_fd), hnd))
#define handle_installopenfd(data, hnd)       ((unsigned int)handles_install_openfd(hnd, data))
#define handle_installinto_sym(dst_fd, hnd)   (void)handles_install_into((fd_t)(dst_fd), hnd)
#define handle_trylookup(self, fd)            handman_trylookup(self, (fd_t)(fd))
#define handle_lookup(fd)                     handles_lookup((fd_t)(fd))
#define handle_lookupin(fd, self)             handman_lookup(self, (fd_t)(fd))
#define handle_lookup_nosym(fd)               handman_lookup(THIS_HANDMAN, (fd_t)(fd))
#define handle_getas(fd, wanted_type)         handles_lookupobj((fd_t)(fd), wanted_type)
#define handle_get_fnode(fd)                  handles_lookupfnode((fd_t)(fd))
#define handle_get_fsuper_relaxed(fd)         handles_lookupfsuper_relatex((fd_t)(fd))
#define handle_get_task(fd)                   handles_lookuptask((fd_t)(fd))
#define handle_get_mfile(fd)                  handles_lookupmfile((fd_t)(fd))
#define handle_get_fdirent(fd)                handles_lookupfdirent((fd_t)(fd))
#define handle_get_path(fd)                   handles_lookuppath((fd_t)(fd))
#define handle_get_taskpid(fd)                handles_lookuppidfd((fd_t)(fd))
#define handle_get_pipe(fd)                   handles_lookuppipe((fd_t)(fd))
#define handle_get_module(fd)                 handles_lookupmodule((fd_t)(fd))
#define handle_get_socket(fd)                 handles_lookupsocket((fd_t)(fd))
#define handle_get_epoll_controller(fd)       handles_lookupepoll((fd_t)(fd))
#endif /* CONFIG_USE_NEW_HANDMAN */


#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_HANDLE_H */
