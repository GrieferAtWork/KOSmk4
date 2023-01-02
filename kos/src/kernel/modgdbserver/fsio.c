/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODGDBSERVER_FSIO_C
#define GUARD_MODGDBSERVER_FSIO_C 1
#define _KOS_SOURCE 1

#include "fsio.h"

#include <kernel/compiler.h>

#include <kernel/fs/fs.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/path.h>
#include <kernel/fs/vfs.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/types.h>

#include <hybrid/atomic.h>

#include <kos/except.h>
#include <kos/io.h>
#include <sys/stat.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>

#include "gdb.h"
#include "server.h"

DECL_BEGIN

/* Decode a given set of GDB O-flags */
LOCAL NOBLOCK ATTR_CONST mode_t
NOTHROW(KCALL GDB_ModeDecode)(gdb_mode_t mode) {
	mode_t result = 0;
	if (mode & GDB_S_IXOTH)
		result |= S_IXOTH;
	if (mode & GDB_S_IWOTH)
		result |= S_IWOTH;
	if (mode & GDB_S_IROTH)
		result |= S_IROTH;
	if (mode & GDB_S_IXGRP)
		result |= S_IXGRP;
	if (mode & GDB_S_IWGRP)
		result |= S_IWGRP;
	if (mode & GDB_S_IRGRP)
		result |= S_IRGRP;
	if (mode & GDB_S_IXUSR)
		result |= S_IXUSR;
	if (mode & GDB_S_IWUSR)
		result |= S_IWUSR;
	if (mode & GDB_S_IRUSR)
		result |= S_IRUSR;
	if (mode & GDB_S_IFDIR)
		result |= S_IFDIR;
	if (mode & GDB_S_IFREG)
		result |= S_IFREG;
	return result;
}


/* Encode a given KOS errno for GDB */
INTERN NOBLOCK ATTR_CONST gdb_errno_t
NOTHROW(KCALL GDB_ErrnoEncode)(errno_t error) {
	gdb_errno_t result;
	switch (error) {

	case EPERM:
		result = GDB_EPERM;
		break;

	case ENOENT:
		result = GDB_ENOENT;
		break;

	case EINTR:
		result = GDB_EINTR;
		break;

	case EBADF:
		result = GDB_EBADF;
		break;

	case EACCES:
		result = GDB_EACCES;
		break;

	case EFAULT:
		result = GDB_EFAULT;
		break;

	case EBUSY:
		result = GDB_EBUSY;
		break;

	case EEXIST:
		result = GDB_EEXIST;
		break;

	case ENODEV:
		result = GDB_ENODEV;
		break;

	case ENOTDIR:
		result = GDB_ENOTDIR;
		break;

	case EISDIR:
		result = GDB_EISDIR;
		break;

	case EINVAL:
		result = GDB_EINVAL;
		break;

	case ENFILE:
		result = GDB_ENFILE;
		break;

	case EMFILE:
		result = GDB_EMFILE;
		break;

	case EFBIG:
		result = GDB_EFBIG;
		break;

	case ENOSPC:
		result = GDB_ENOSPC;
		break;

	case ESPIPE:
		result = GDB_ESPIPE;
		break;

	case EROFS:
		result = GDB_EROFS;
		break;

	case ENAMETOOLONG:
		result = GDB_ENAMETOOLONG;
		break;

	default:
		result = GDB_EUNKNOWN;
		break;
	}
	return result;
}




/* GDB filesystem access control. */
INTERN struct fsio_struct GDBFs = { NULL, 0, NULL };

/* Finalize the file-system sub-system */
INTERN NOBLOCK void NOTHROW(KCALL GDBFs_Fini)(void) {
	if (GDBFs.fi_fs) {
		REF struct fs *f;
		f           = GDBFs.fi_fs;
		GDBFs.fi_fs = NULL;
		decref_unlikely(f);
	}
	if (GDBFs.fi_hvector) {
		unsigned int count;
		struct handle *vec;
		vec   = GDBFs.fi_hvector;
		count = GDBFs.fi_halloc;
		GDBFs.fi_hvector = NULL;
		GDBFs.fi_halloc  = 0;
		while (count) {
			--count;
			decref(vec[count]);
		}
		kfree(vec);
	} else {
		assert(!GDBFs.fi_halloc);
	}
}


/* Returns -1 memory could not be allocated. */
INTERN WUNUSED fd_t
NOTHROW(KCALL GDBFs_RegisterHandle)(/*inherit(on_success)*/ REF struct handle const *__restrict hnd) {
	unsigned int result, new_count;
	struct handle *vec;
	vec = GDBFs.fi_hvector;
	for (result = 0; result < GDBFs.fi_halloc; ++result) {
		if (vec[result].h_type == HANDLE_TYPE_UNDEFINED)
			goto use_result;
	}
	/* Allocate more vector memory. */
	new_count = GDBFs.fi_halloc + GDBFS_HANDLE_RESIZE_THRESHOLD;
	vec = (struct handle *)krealloc_nx(vec,
	                                   new_count * sizeof(struct handle),
	                                   GFP_NORMAL | GFP_CALLOC);
	if unlikely(!vec) {
		static_assert(HANDLE_TYPE_UNDEFINED == 0,
		              "We pass `GFP_CALLOC' because of this");
		new_count = GDBFs.fi_halloc + 1;
		vec = (struct handle *)krealloc_nx(GDBFs.fi_hvector,
		                                   new_count * sizeof(struct handle),
		                                   GFP_NORMAL | GFP_CALLOC);
		if unlikely(!vec)
			return -1; /* Allocation failed. */
	}
	result = GDBFs.fi_halloc;
	GDBFs.fi_hvector = vec;
	GDBFs.fi_halloc  = new_count;
use_result:
	/* Use this slot. */
	vec[result] = *hnd;
	return (fd_t)result;
}


/* Delete a previously registered handle. */
INTERN bool
NOTHROW(KCALL GDBFs_DeleteHandle)(fd_t fdno) {
	unsigned int i;
	struct handle oh;
	if unlikely((unsigned int)fdno >= GDBFs.fi_halloc)
		goto badfd;
	if unlikely(GDBFs.fi_hvector[(unsigned int)fdno].h_type == HANDLE_TYPE_UNDEFINED)
		goto badfd;
	oh = GDBFs.fi_hvector[(unsigned int)fdno];
	GDBFs.fi_hvector[(unsigned int)fdno].h_type = HANDLE_TYPE_UNDEFINED;
	/* Check if we can truncate the vector. */
	for (i = (unsigned int)fdno + 1; i < GDBFs.fi_halloc; ++i) {
		if (GDBFs.fi_hvector[i].h_type != HANDLE_TYPE_UNDEFINED)
			goto done;
	}
	i = (unsigned int)fdno;
	while (i && GDBFs.fi_hvector[i - 1].h_type == HANDLE_TYPE_UNDEFINED)
		--i;
	if (i == 0) {
		kfree(GDBFs.fi_hvector);
		GDBFs.fi_halloc  = 0;
		GDBFs.fi_hvector = NULL;
	} else if (GDBFs.fi_halloc >= i + (GDBFS_HANDLE_RESIZE_THRESHOLD + 1)) {
		/* Try to truncate the vector. */
		struct handle *vec;
		vec = (struct handle *)krealloc_nx(GDBFs.fi_hvector,
		                                   i * sizeof(struct handle),
		                                   GFP_NORMAL | GFP_CALLOC);
		if likely(vec) {
			GDBFs.fi_halloc  = i;
			GDBFs.fi_hvector = vec;
		}
	}
done:
	decref(oh);
	return true;
badfd:
	return false;
}

LOCAL ATTR_PURE WUNUSED bool
NOTHROW(KCALL GDBFs_HasMountedFileSystem)(void) {
	if unlikely(!GDBFs.fi_fs)
		return false; /* No filesystem loaded. */
	if unlikely(!ATOMIC_READ(GDBFs.fi_fs->fs_vfs->vf_root))
		return false; /* The root filesystem hasn't been mounted, yet. */
	return true;
}


/* Open a file handle for GDB (returns 0 on success) */
INTERN WUNUSED gdb_errno_t
NOTHROW(KCALL GDBFs_Open)(char const *filename,
                          gdb_oflag_t oflags, gdb_mode_t mode,
                          struct handle *__restrict result) {
	/* Validate flags */
	if unlikely(oflags & ~(GDB_O_ACCMODE | GDB_O_APPEND |
	                       GDB_O_CREAT | GDB_O_TRUNC | GDB_O_EXCL)) {
		GDB_DEBUG("[gdb] Cannot open(%q, %#x, %#x): Invalid `oflags' passed\n",
		          filename, (unsigned int)oflags, (unsigned int)mode);
		return GDB_EINVAL;
	}
	if unlikely(mode & ~(GDB_S_IXOTH | GDB_S_IWOTH | GDB_S_IROTH |
	                     GDB_S_IXGRP | GDB_S_IWGRP | GDB_S_IRGRP |
	                     GDB_S_IXUSR | GDB_S_IWUSR | GDB_S_IRUSR |
	                     GDB_S_IFDIR | GDB_S_IFREG)) {
		GDB_DEBUG("[gdb] Cannot open(%q, %#x, %#x): Invalid `mode' passed\n",
		          filename, (unsigned int)oflags, (unsigned int)mode);
		return GDB_EINVAL;
	}

	/* Ensure that a filesystem has been loaded. */
	if unlikely(!GDBFs_HasMountedFileSystem()) {
		GDB_DEBUG("[gdb] Cannot open(%q, %#x, %#x): No filesystem mounted\n",
		          filename, (unsigned int)oflags, (unsigned int)mode);
		return GDB_ENOENT;
	}
	GDB_DEBUG("[gdb] vFile:open(%q, %#x, %#x)\n",
	          filename, (unsigned int)oflags, (unsigned int)mode);
	/* Set the I/O mode. */
	TRY {
		oflag_t os_oflags;
		if ((oflags & GDB_O_ACCMODE) == GDB_O_RDONLY) {
			os_oflags = O_RDONLY;
		} else if ((oflags & GDB_O_ACCMODE) == GDB_O_WRONLY) {
			os_oflags = O_WRONLY;
		} else if ((oflags & GDB_O_ACCMODE) == GDB_O_RDWR) {
			os_oflags = O_RDWR;
		} else {
			return GDB_EINVAL;
		}
		if (oflags & GDB_O_APPEND)
			os_oflags |= O_APPEND;
		if (oflags & GDB_O_CREAT)
			os_oflags |= O_CREAT;
		if (oflags & GDB_O_TRUNC)
			os_oflags |= O_TRUNC;
		if (oflags & GDB_O_EXCL)
			os_oflags |= O_EXCL;

		/* Open the file */
		{
			REF struct fs *saved_fs = task_setfs(GDBFs.fi_fs);
			RAII_FINALLY { decref_unlikely(task_setfs(saved_fs)); };
			*result = path_open(AT_FDROOT, filename, os_oflags, mode);
		}
	} EXCEPT {
		errno_t error;
		error = except_as_errno(except_data());
		return GDB_ErrnoEncode(error);
	}
	return 0;
}

/* Delete the file associated with `filename' */
INTERN WUNUSED gdb_errno_t
NOTHROW(KCALL GDBFs_Unlink)(char const *filename) {
	/* Ensure that a filesystem has been loaded. */
	if unlikely(!GDBFs_HasMountedFileSystem()) {
		GDB_DEBUG("[gdb] Cannot unlink(%q): No filesystem mounted\n", filename);
		return GDB_ENOENT;
	}
	GDB_DEBUG("[gdb] vFile:unlink(%q)\n", filename);
	TRY {
		char const *last_seg;
		u16 last_seglen;
		REF struct path *p;
		atflag_t atflags;
		REF struct fs *saved_fs = task_setfs(GDBFs.fi_fs);
		RAII_FINALLY { decref_unlikely(task_setfs(saved_fs)); };
		atflags = fs_atflags(0) | AT_REMOVEREG;
		p       = path_traverse(AT_FDCWD, filename, &last_seg, &last_seglen, atflags);
		FINALLY_DECREF_UNLIKELY(p);
		path_remove(p, last_seg, last_seglen, atflags);
	} EXCEPT {
		errno_t error;
		error = except_as_errno(except_data());
		return GDB_ErrnoEncode(error);
	}
	return 0;
}


/* Resolve a symbolic link (don't include trailing NUL-characters, though...)
 * @param: pbuflen: [IN]  Available buffer size in `buf'
 *                  [OUT] Number of bytes written to `buf' */
INTERN WUNUSED gdb_errno_t
NOTHROW(KCALL GDBFs_Readlink)(char const *filename, char *buf,
                              size_t *__restrict pbuflen) {
	/* Ensure that a filesystem has been loaded. */
	if unlikely(!GDBFs_HasMountedFileSystem()) {
		GDB_DEBUG("[gdb] Cannot readlink(%q): No filesystem mounted\n", filename);
		return GDB_ENOENT;
	}
	GDB_DEBUG("[gdb] vFile:readlink(%q)\n", filename);
	TRY {
		size_t avail, used;
		REF struct flnknode *lnk;
		REF struct fs *saved_fs = task_setfs(GDBFs.fi_fs);
		RAII_FINALLY { decref_unlikely(task_setfs(saved_fs)); };
		lnk = (REF struct flnknode *)path_traversefull(AT_FDCWD, filename, fs_atflags(0));
		FINALLY_DECREF_UNLIKELY(lnk);
		/* Check that the named INode is actually a symbolic link. */
		if unlikely(!fnode_islnk(lnk))
			return GDB_ENOENT; /* THROW(E_FSERROR_NOT_A_SYMBOLIC_LINK); */
		/* Read the contents of the symbolic link. */
		avail = *pbuflen;
		used  = flnknode_readlink(lnk, buf, avail);
		if unlikely(used > avail)
			used = avail; /* Posix semantics (ugh...) */
		*pbuflen = used;
	} EXCEPT {
		errno_t error;
		error = except_as_errno(except_data());
		return GDB_ErrnoEncode(error);
	}
	return 0;
}



DECL_END

#endif /* !GUARD_MODGDBSERVER_FSIO_C */
