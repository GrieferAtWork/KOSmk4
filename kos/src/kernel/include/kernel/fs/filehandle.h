/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FILEHANDLE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FILEHANDLE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/atomic64.h>

#ifdef __CC__
DECL_BEGIN

/* File handle objects  are used  to implement  seeking
 * functionality on-top of some generic `struct mfile'.
 *
 * This is the type of object that is returned by `mfile_v_open()' */
struct mfile;
struct path;
struct fdirent;

struct filehandle {
	/* [HANDLE_TYPE(HANDLE_TYPE_FILEHANDLE, HANDLE_TYPE_TEMPHANDLE)] */
	WEAK refcnt_t       fh_refcnt; /* File reference counter. */
	REF struct mfile   *fh_file;   /* [1..1][const] The opened file INode. */
	REF struct path    *fh_path;   /* [0..1][const] The path from which `fh_file' was opened (if any). */
	REF struct fdirent *fh_dirent; /* [0..1][const] The directory entry associated with `fh_file' (if any). */
	WEAK atomic64_t     fh_offset; /* File I/O read/write position. */
};

/* Destroy the given filehandle object. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL filehandle_destroy)(struct filehandle *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct filehandle, fh_refcnt, filehandle_destroy)

/* Allocate and return a new file handle wrapper for the given  file.
 * This function is used to implement `mfile_v_open()', which is  the
 * fallback open operator for mfile-s to implement seek capabilities.
 *
 * Handle operates invoked on the returned object are forwarded to the
 * relevant `mfile_u*' functions, lseek(2) is implemented locally, and
 * `read(2)' and `write(2)' are implemented via `pread(2)'+`pwrite(2)' */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct filehandle *KCALL
filehandle_new(struct mfile *__restrict self,
               struct path *access_path,
               struct fdirent *access_dent)
		THROWS(E_BADALLOC);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FILEHANDLE_H */
