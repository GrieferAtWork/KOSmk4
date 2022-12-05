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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MEMFD_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MEMFD_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/filehandle.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/mman/memfd.h>
#include <kernel/mman/mpart.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/tsc.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/handle.h>
#include <sys/mman.h>

#include <dirent.h>
#include <format-printer.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL memfd_v_destroy)(struct mfile *__restrict self) {
	struct memfd *me = mfile_asmemfd(self);
	decref_likely(me->mfd_name);
	kfree(me);
}


INTDEF NONNULL((1)) void /* From "./mfile.c" */
NOTHROW(KCALL mfile_zero_loadpages)(struct mfile *__restrict self,
                                    pos_t addr, physaddr_t buf, size_t num_bytes,
                                    struct aio_multihandle *__restrict aio);

PRIVATE WUNUSED NONNULL((1)) REF void *
NOTHROW(KCALL memfd_v_tryas)(struct mfile *__restrict self,
                             uintptr_half_t wanted_type) {
	struct memfd *me = mfile_asmemfd(self);
	if (wanted_type == HANDLE_TYPE_DIRENT)
		return incref(me->mfd_name);
	return NULL;
}

PRIVATE WUNUSED NONNULL((1, 2)) ssize_t KCALL
memfd_v_printlink(struct mfile *__restrict self,
                  pformatprinter printer, void *arg) {
	struct memfd *me = mfile_asmemfd(self);
	return format_printf(printer, arg, "memfd:%$s",
	                     (size_t)me->mfd_name->fd_namelen,
	                     me->mfd_name->fd_name);
}


PRIVATE struct mfile_stream_ops const memfd_v_stream_ops = {
	.mso_tryas     = &memfd_v_tryas,
	.mso_printlink = &memfd_v_printlink,
};

/* Operators used for memfd files. */
PUBLIC_CONST struct mfile_ops const memfd_ops = {
	.mo_destroy    = &memfd_v_destroy,
	.mo_loadblocks = &mfile_zero_loadpages,
	.mo_stream     = &memfd_v_stream_ops,
};


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL memfd_name_v_destroy)(struct fdirent *__restrict self) {
	kfree(self);
}

PRIVATE struct fdirent_ops const memfd_name_ops = {
	.fdo_destroy = &memfd_name_v_destroy,

	/* There is no directory, so there should be no way this operator would
	 * ever be invoked. As such, assign a bad pointer so the kernel  panics
	 * if it were to ever be invoked. */
	.fdo_opennode = (typeoffield(struct fdirent_ops, fdo_opennode))(void *)-1,

	/* Same as `fdo_opennode': shouldn't ever be invocable, so assign a bad pointer. */
	.fdo_getino = (typeoffield(struct fdirent_ops, fdo_getino))(void *)-1,
};

/* Construct a new mem-fd object (s.a. `memfd_create(2)')
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_MEMFD_CREATE_NAME_TOO_LONG: [...] */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct memfd *FCALL
memfd_new(USER CHECKED char const *name)
		THROWS(E_SEGFAULT, E_BADALLOC, E_INVALID_ARGUMENT_BAD_VALUE) {
	REF struct fdirent *memfd_name;
	REF struct memfd *result;
	size_t namelen = strlen(name);

	/* This `249' is a linux-defined hard limit, and is documented under `man 2 memfd_create' */
	if unlikely(namelen > 249) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_MEMFD_CREATE_NAME_TOO_LONG,
		      namelen);
	}

	memfd_name = (REF struct fdirent *)kmalloc(offsetof(struct fdirent, fd_name) +
	                                           (namelen + 1) * sizeof(char),
	                                           GFP_NORMAL);
	TRY {
		*(char *)mempcpy(memfd_name->fd_name, name, namelen, sizeof(char)) = '\0';
		result = (REF struct memfd *)kmalloc(sizeof(struct memfd), GFP_NORMAL);
	} EXCEPT {
		kfree(memfd_name);
		RETHROW();
	}

	/* The rest of initialization is non-throwing. */
	_mfile_init(result, &memfd_ops, PAGESHIFT, PAGESHIFT);
	result->mf_parts             = NULL;
	result->mf_changed.slh_first = MFILE_PARTS_ANONYMOUS; /* Don't need to track changes. */
	result->mf_flags             = MFILE_F_PERSISTENT | MFILE_F_ATTRCHANGED | MFILE_F_CHANGED;
	atomic64_init(&result->mf_filesize, 0);
	result->mf_atime = realtime();
	result->mf_mtime = result->mf_atime;
	result->mf_ctime = result->mf_atime;
	result->mf_btime = result->mf_atime;
	result->mfd_name = memfd_name;
	DBG_memset(&memfd_name->fd_ino, 0xcc, sizeof(memfd_name->fd_ino));
	memfd_name->fd_refcnt  = 1; /* +1: result->mfd_name */
	memfd_name->fd_ops     = &memfd_name_ops;
	memfd_name->fd_hash    = fdirent_hash(memfd_name->fd_name, (u16)namelen);
	memfd_name->fd_namelen = (u16)namelen;
	memfd_name->fd_type    = DT_REG; /* Kind-of... It's the closest we've got... */
	return result;
}


/* Wrapper  for `memfd_new()' that  packages the memfd  inside of a filehandle,
 * thus allowing all of the normal read(2) / write(2) operations on it as well. */
PRIVATE ATTR_RETNONNULL WUNUSED REF struct filehandle *FCALL
memfd_new_with_filehandle(USER CHECKED char const *name)
		THROWS(E_SEGFAULT, E_BADALLOC, E_INVALID_ARGUMENT_BAD_VALUE) {
	REF struct memfd *mfd = memfd_new(name);
	FINALLY_DECREF_UNLIKELY(mfd);
	return filehandle_new(mfd, NULL, NULL);
}


DEFINE_SYSCALL2(fd_t, memfd_create,
                USER UNCHECKED char const *, name,
                syscall_ulong_t, flags) {
	fd_t resfd;
	iomode_t mode;
	struct handle_install_data install;
	REF struct filehandle *hand;

	/* Validate arguments. */
	validate_readable(name, 1);
	VALIDATE_FLAGSET(flags,
	                 MFD_CLOEXEC | MFD_ALLOW_SEALING |
	                 MFD_HUGETLB | MFD_CLOFORK,
	                 E_INVALID_ARGUMENT_CONTEXT_MEMFD_CREATE_FLAGS);

	resfd = handles_install_begin(&install);
	TRY {
		/* Construct the new mem-fd object. */
		hand = memfd_new_with_filehandle(name);
	} EXCEPT {
		handles_install_rollback(&install);
		RETHROW();
	}

	/* Construct handle access mode. */
	mode = IO_RDWR;
	if (flags & MFD_CLOEXEC)
		mode |= IO_CLOEXEC;
	if (flags & MFD_CLOFORK)
		mode |= IO_CLOFORK;

	/* Use TEMPHANDLE, so the memfd is deleted during close()
	 * If we used a normal FILEHANDLE, we'd get a reference leak:
	 *       mpart_all_list->mpart->memfd */
	handles_install_commit_inherit(&install, hand, mode,
	                               HANDLE_TYPE_TEMPHANDLE);
	return resfd;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MEMFD_C */
