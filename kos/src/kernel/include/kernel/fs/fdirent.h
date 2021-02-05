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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FDIRENT_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FDIRENT_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

struct fdirent;
struct fdirent {
	/* Additional fs-specific data usually goes here (i.e. at negative offsets,
	 * such that the filesystem layer will use `container_of()' to access the
	 * container structure). Alternatively, data could also go at `fd_name[fd_namelen]',
	 * however this is less likely, since doing this would require making use
	 * of non-constant struct offsets. */
	WEAK refcnt_t           fd_refcnt;   /* Reference counter. */
	NOBLOCK NONNULL((1)) void /*NOTHROW*/
	(FCALL                 *fd_destroy)(struct fdirent *__restrict self); /* [1..1] Destroy callback. */
	size_t                  fd_heapsize; /* [const] Allocated heap size. */
	ino_t                   fd_ino;      /* [const] INode number of this directory entry. */
	uintptr_t               fd_hash;     /* [const] Hash of this directory entry. */
	u16                     fd_namelen;  /* [const][!0] Length of the directory entry name (in characters). */
	unsigned char           fd_type;     /* [const] Directory entry type (one of `DT_*') */
	COMPILER_FLEXIBLE_ARRAY(/*utf-8*/ char,
	                        fd_name);    /* [const][de_namelen] Directory entry name. (NUL-terminated) */
};

#define fdirent_destroy(self) ((*(self)->fd_destroy)(self))
DEFINE_REFCOUNT_FUNCTIONS(struct fdirent, fd_refcnt, fdirent_destroy)


DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FDIRENT_H */
