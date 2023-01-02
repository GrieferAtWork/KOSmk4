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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_MEMFD_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_MEMFD_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mfile.h>

/*
 * Mem-fd objects (for `memfd_create(2)')
 */

#ifdef __CC__
DECL_BEGIN

struct fdirent;
struct memfd
#ifdef __cplusplus
    : mfile                       /* Underlying mem-file */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct mfile        mfd_file; /* Underlying mem-file */
#endif /* !__cplusplus */
	REF struct fdirent *mfd_name; /* [1..1][const] Memfd name (only used for procfs fd-
	                               * symlinks, but also when trying to exec() a  memfd)
	                               * This is the `name' passed to `memfd_create(2)' */
};

#define mfile_asmemfd(self) ((struct memfd *)(self))
#define mfile_ismemfd(self) ((self)->mf_ops == &memfd_ops)

/* Operators used for memfd files. */
DATDEF struct mfile_ops const memfd_ops;

/* Construct a new mem-fd object (s.a. `memfd_create(2)')
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE:E_INVALID_ARGUMENT_CONTEXT_MEMFD_CREATE_NAME_TOO_LONG: [...] */
FUNDEF ATTR_RETNONNULL WUNUSED REF struct memfd *FCALL
memfd_new(USER CHECKED char const *name)
		THROWS(E_SEGFAULT, E_BADALLOC, E_INVALID_ARGUMENT_BAD_VALUE);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_MEMFD_H */
