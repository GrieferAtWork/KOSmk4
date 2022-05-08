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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_DIRHANDLE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_DIRHANDLE_H 1

#include <kernel/compiler.h>

#include <kernel/fs/dirnode.h> /* struct fdirenum */
#include <kernel/types.h>
#include <sched/atomic64.h>

#ifdef __CC__
DECL_BEGIN

/* File  handle objects are  used to implement seeking
 * functionality on-top of some generic `struct mdir'.
 *
 * This is the type of object that is returned by `mdir_v_open()' */
struct mdir;
struct path;
struct fdirent;

struct dirhandle {
	/* [HANDLE_TYPE(HANDLE_TYPE_DIRHANDLE)] */
	WEAK refcnt_t       dh_refcnt; /* File reference counter. */
	uintptr_t           dh_dots;   /* [lock(ATOMIC)] 0: Neither was read; 1: "." was read; 2: ".." was read. */
	REF struct path    *dh_path;   /* [0..1][const] The path from which `fh_dir' was opened (if any). */
	REF struct fdirent *dh_dirent; /* [0..1][const] The directory entry associated with `fh_dir' (if any). */
	/* NOTE: When seeking within the actual directory using SEEK_CUR or SEEK_END, it's not
	 *       possible  to rewind back to where `dh_dots'  will be emitted once again. Only
	 *       SEEK_SET (as used by `rewinddir(3)') can go back to that point.
	 * Also  note that readdir(2) on its own is entirely thread-safe when it comes to every
	 * entry (including "." and "..") only being read once, but when combined with seeking,
	 * there are some situations where an unexpected entry may be read by concurrent reads. */
	struct fdirenum     dh_enum;   /* Directory enumerator. (Flexible size) */
};

/* Destroy the given dirhandle object. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL dirhandle_destroy)(struct dirhandle *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct dirhandle, dh_refcnt, dirhandle_destroy)

/* Allocate and return a new  directory enumeration wrapper for  the
 * given directory node `self'. This  function is used to  implement
 * `fdirnode_v_open' (the default open-operator for directory files)
 *
 * The  returned handle object implements `readdir(2)' and `lseek(2)'
 * for seeking within the directory. Normal read(2) and write(2) ops,
 * as  well  as fsync(2),  fdatasync(2),  ftruncate(2), fallocate(2),
 * mmap(2) and poll(2) are not  implemented, but all other  operators
 * stat(2),   ioctl(2)  and  <mfile_utryas>   are  forwarded  to  the
 * associated  directory  node  (obtained  via   `fdirenum_getdir()')
 *
 * The returned object also implements readdir(2) such that "."  and
 * ".." directory entries are enumerated (so-long as the  associated
 * directory has a parent node; iow: isn't the filesystem root), and
 * `READDIR_SKIPREL' isn't given to prevent this. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct dirhandle *KCALL
dirhandle_new(struct fdirnode *__restrict self,
              struct path *access_path,
              struct fdirent *access_dent)
		THROWS(E_BADALLOC);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_DIRHANDLE_H */
