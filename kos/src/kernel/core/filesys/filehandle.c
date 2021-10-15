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
#ifndef GUARD_KERNEL_CORE_FILESYS_FILEHANDLE_C
#define GUARD_KERNEL_CORE_FILESYS_FILEHANDLE_C 1

#include <kernel/compiler.h>

#include <fs/vfs.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/filehandle.h>
#include <kernel/handle-proto.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>

DECL_BEGIN

/* Destroy the given filehandle object. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL filehandle_destroy)(struct filehandle *__restrict self) {
	decref_unlikely(self->fh_file);
	xdecref_unlikely(self->fh_path);
	xdecref_unlikely(self->fh_dirent);
	kfree(self);
}

/* Allocate and return a new file handle wrapper for the given  file.
 * This function is used to implement `mfile_v_open()', which is  the
 * fallback open operator for mfile-s to implement seek capabilities.
 *
 * Handle operates invoked on the returned object are forwarded to the
 * relevant `mfile_u*' functions, lseek(2) is implemented locally, and
 * `read(2)' and `write(2)' are implemented via `pread(2)'+`pwrite(2)' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct filehandle *KCALL
filehandle_new(struct mfile *__restrict self,
               struct path *access_path,
               struct fdirent *access_dent) {
	REF struct filehandle *result;
	result = (REF struct filehandle *)kmalloc(sizeof(struct filehandle), GFP_NORMAL);
	result->fh_refcnt = 1;
	result->fh_file   = incref(self);
	result->fh_path   = xincref(access_path);
	result->fh_dirent = xincref(access_dent);
	atomic64_init(&result->fh_offset, 0);
}


/************************************************************************/
/* Handle operators for `HANDLE_TYPE_FILEHANDLE'                        */
/************************************************************************/

/* TODO */


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_FILEHANDLE_C */
