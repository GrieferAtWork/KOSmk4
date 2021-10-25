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
#ifndef GUARD_KERNEL_CORE_FILESYS_DIRHANDLE_C
#define GUARD_KERNEL_CORE_FILESYS_DIRHANDLE_C 1

#include <kernel/compiler.h>

#include <fs/vfs.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirhandle.h>
#include <kernel/fs/super.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/handle.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

/* Destroy the given dirhandle object. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL dirhandle_destroy)(struct dirhandle *__restrict self) {
	fdirenum_fini(&self->dh_enum);
	xdecref_unlikely(self->dh_path);
	xdecref_unlikely(self->dh_dirent);
	kfree(self);
}

/* Allocate and return a new  directory enumeration wrapper for  the
 * given directory node `self'. This  function is used to  implement
 * `fdirnode_v_open' (the default open-operator for directory files)
 *
 * The  returned handle object implements `readdir(2)' and `lseek(2)'
 * for seeking within the directory. Normal read(2) and write(2) ops,
 * as  well  as fsync(2),  fdatasync(2),  ftruncate(2), fallocate(2),
 * mmap(2) and poll(2) are not  implemented, but all other  operators
 * stat(2), ioctl(2), hop(2) and <mfile_utryas> are forwarded to  the
 * associated directory node (obtained via `fdirenum_getdir()')
 *
 * The returned object also implements readdir(2) such that "."  and
 * ".." directory entries are enumerated (so-long as the  associated
 * directory has a parent node; iow: isn't the filesystem root), and
 * `READDIR_SKIPREL' isn't given to prevent this. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct dirhandle *KCALL
dirhandle_new(struct fdirnode *__restrict self,
              struct path *access_path,
              struct fdirent *access_dent) {
	REF struct dirhandle *result;
	result = (REF struct dirhandle *)kmalloc(sizeof(REF struct dirhandle),
	                                         GFP_NORMAL);
	/* Construct a directory enumerator. */
	TRY {
		fdirnode_enum(self, &result->dh_enum);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	/* Fill in remaining fields. */
	result->dh_refcnt = 1;
	result->dh_path   = xincref(access_path);
	result->dh_dirent = xincref(access_dent);
	result->dh_dots   = 0;
	return result;
}



/************************************************************************/
/* Handle operators for `HANDLE_TYPE_DIRHANDLE'                         */
/************************************************************************/
DEFINE_HANDLE_REFCNT_FUNCTIONS(dirhandle, struct dirhandle);

/* Handle operators for `HANDLE_TYPE_DIRHANDLE' (`struct dirhandle') */
INTDEF WUNUSED NONNULL((1)) size_t KCALL
handle_dirhandle_readdir(struct dirhandle *__restrict self,
                         USER CHECKED struct dirent *buf, size_t bufsize,
                         readdir_mode_t readdir_mode, iomode_t mode) THROWS(...) {
	uintptr_t dots;
again_dots:
	dots = ATOMIC_READ(self->dh_dots);
	if (dots < 2) {
		if (readdir_mode & READDIR_SKIPREL) {
			if (!ATOMIC_CMPXCH_WEAK(self->dh_dots, dots, 2))
				goto again_dots;
		} else {
			ino_t ino;
			ssize_t result;
			struct fdirnode *mydir;
			mydir = self->dh_enum.de_dir;

			/* Try to emit "." */
			if (dots == 0) {
				uintptr_t newdots;

				/* Figure out of we should later skip the ".." entry. */
				newdots = fdirnode_issuper(mydir) ? 1 : 2;

				/* Read the directory's INode number. */
				mfile_tslock_acquire(mydir);
				ino = mydir->fn_ino;
				mfile_tslock_release(mydir);

				/* Feed the special "." entry */
				result = fdirenum_feedent(buf, bufsize, readdir_mode,
				                          ino, DT_DIR, 1, ".");
				if (result < 0)
					return (size_t)~result;
				if (!ATOMIC_CMPXCH(self->dh_dots, dots, newdots))
					goto again_dots;
				return (size_t)result;
			}
			assert(dots == 1);

			/* Try to emit ".." */
			if unlikely(fdirnode_issuper(mydir)) {
				/* Superblock roots don't have parent nodes, and thus no ".." entry. */
				if (!ATOMIC_CMPXCH(self->dh_dots, dots, 2))
					goto again_dots;
				goto read_normal_entry;
			}

			/* (Try to) read the parent directory's Inode number. */
			ino = 0;
			if (self->dh_path) {
				struct fdirnode *parent = self->dh_path->p_dir;
				if (parent->fn_super == mydir->fn_super) {
					mfile_tslock_acquire(parent);
					ino = parent->fn_ino;
					mfile_tslock_release(parent);
				}
			}

			/* Feed the special ".." entry */
			result = fdirenum_feedent(buf, bufsize, readdir_mode,
			                          ino, DT_DIR, 2, "..");
			if (result < 0)
				return (size_t)~result;
			if (!ATOMIC_CMPXCH(self->dh_dots, dots, 2))
				goto again_dots;
			return (size_t)result;
		}
	}

read_normal_entry:
	/* Read a "normal" directory entry. */
	return fdirenum_readdir(&self->dh_enum, buf, bufsize, readdir_mode, mode);
}


#define dirhandle_isfsroot(self) \
	fdirnode_issuper((self)->dh_enum.de_dir)

INTDEF NONNULL((1)) pos_t KCALL
handle_dirhandle_seek(struct dirhandle *__restrict self,
                      off_t offset, unsigned int whence) THROWS(...) {
	pos_t result;
	switch (whence) {

	case SEEK_SET:
		if ((pos_t)offset <= 1) {
			/* Simple case (including rewinddir(3)): seek into guarantied dots portion. */
			ATOMIC_WRITE(self->dh_dots, (uintptr_t)(pos_t)offset);
			fdirenum_seekdir(&self->dh_enum, 0, SEEK_SET);
			result = (pos_t)offset;
			break;
		}
		if (offset == 2) {
			/* Special case: Either seek after the ".." entry, or after the first "real" entry. */
			if (dirhandle_isfsroot(self)) {
				/* Seek after first "real" entry. */
				result = fdirenum_seekdir(&self->dh_enum, (off_t)1, SEEK_SET) + 1;
				ATOMIC_WRITE(self->dh_dots, 2);
				break;
			}
			/* Seek after ".." entry. */
			ATOMIC_WRITE(self->dh_dots, 2);
			result = (pos_t)2;
			break;
		}
		goto do_normal_seek;

	case SEEK_CUR: {
		uintptr_t dots;
again_seek_cur_dots:
		dots = ATOMIC_READ(self->dh_dots);
		if (dots < 2) {
			if (offset == 0) {
				result = (pos_t)dots;
				break;
			}
			if (offset < 0) {
				/* We're  at the very start, or after "." (with ".." following),
				 * and the seek offset is negative. In all cases, go back to the
				 * very start! */
				if (!ATOMIC_CMPXCH(self->dh_dots, dots, 0))
					goto again_seek_cur_dots;
				result = (pos_t)0;
				break;
			}
			if (dots == 0) {
				bool isfsroot;
				/* Positive offset at start of directory. */
				if (offset <= 1) {
					if (!ATOMIC_CMPXCH(self->dh_dots, dots, 1))
						goto again_seek_cur_dots;
					result = (pos_t)1;
					break;
				}
				/* Offset to skip the dots portion. */
				assert(offset >= 2);
				if (!ATOMIC_CMPXCH(self->dh_dots, dots, 2))
					goto again_seek_cur_dots;
				--offset;
				isfsroot = dirhandle_isfsroot(self);
				if (isfsroot)
					--offset;
				if (offset == 0) {
					result = (pos_t)1;
					if (isfsroot)
						++result;
					break;
				}
			} else {
				/* Seek to (possibly) skip the second dots entry. */
				assert(dots == 1);
				assert(offset >= 1);
				if (dirhandle_isfsroot(self)) {
					/* There is no second dots-entry. */
					ATOMIC_CMPXCH(self->dh_dots, dots, 2);
					goto again_seek_cur_dots;
				}
				assert(!dirhandle_isfsroot(self));
				if (!ATOMIC_CMPXCH(self->dh_dots, dots, 2))
					goto again_seek_cur_dots;
				--offset;
				if (offset == 0) {
					/* Simplified case: seek until after dots portion. */
					result = (pos_t)2;
					break;
				}
			}
			/* Fallthru to do a normal seek from the start of the "real" directory. */
			whence = SEEK_SET;
		}
		/* Fallback: only seek within the "real" directory.
		 * As documented, it's impossible to seek back into
		 * the dots portion here. */
	}	ATTR_FALLTHROUGH
	case SEEK_END:
do_normal_seek:
		result = fdirenum_seekdir(&self->dh_enum, offset, whence);

		/* Unconditionally go beyond the dots.
		 * As documented, it's impossible to seek back into
		 * the dots portion here. */
		ATOMIC_WRITE(self->dh_dots, 2);

		/* When not the filesystem root, ++result x2. */
		++result;
		if (!dirhandle_isfsroot(self))
			++result;
		break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
		break;
	}
	return result;
}

INTDEF NONNULL((1)) syscall_slong_t KCALL
handle_dirhandle_ioctl(struct dirhandle *__restrict self, syscall_ulong_t cmd,
                       USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	return mfile_uioctl(self->dh_enum.de_dir, cmd, arg, mode);
}

INTDEF NONNULL((1)) void KCALL
handle_dirhandle_stat(struct dirhandle *__restrict self,
                      USER CHECKED struct stat *result) THROWS(...) {
	return mfile_ustat(self->dh_enum.de_dir, result);
}

INTDEF NONNULL((1)) syscall_slong_t KCALL
handle_dirhandle_hop(struct dirhandle *__restrict self, syscall_ulong_t cmd,
                     USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	/* XXX: dirhandle-specific HOPs? */
	return mfile_uhop(self->dh_enum.de_dir, cmd, arg, mode);
}

INTDEF NONNULL((1)) REF void *KCALL
handle_dirhandle_tryas(struct dirhandle *__restrict self,
                       uintptr_half_t wanted_type) THROWS(E_WOULDBLOCK) {
	switch (wanted_type) {
	case HANDLE_TYPE_MFILE:
		return incref(self->dh_enum.de_dir);
	case HANDLE_TYPE_FDIRENT:
		return xincref(self->dh_dirent);
	case HANDLE_TYPE_PATH:
		return xincref(self->dh_path);
	default: break;
	}
	return mfile_utryas(self->dh_enum.de_dir, wanted_type);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_DIRHANDLE_C */
