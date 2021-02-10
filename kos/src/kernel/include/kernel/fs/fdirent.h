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
struct fdirnode;

struct fdirent_ops {
	/* [1..1] Destroy callback. */
	NOBLOCK NONNULL((1)) void /*NOTHROW*/
	(FCALL *fdo_destroy)(struct fdirent *__restrict self);

	/* [1..1] Open the node  associated with  this directory  entry.
	 * If the entry has already been deleted, return `NULL' instead.
	 * @param: dir: The directory that contains `self' */
	WUNUSED NONNULL((1, 2)) REF struct fnode *
	(FCALL *fdo_opennode)(struct fdirent *__restrict self,
	                      struct fdirnode *__restrict dir);
};

struct fdirent {
	/* Additional  fs-specific  data  usually  goes  here  (iow:  at  negative  offsets,
	 * such   that  the  filesystem  layer  will  use  `container_of()'  to  access  the
	 * container structure). Alternatively, data could also go at `fd_name[fd_namelen]',
	 * however  this  is  less  likely,  since  doing  this  would  require  making  use
	 * of non-constant struct offsets. */
	WEAK refcnt_t           fd_refcnt;   /* Reference counter. */
	struct fdirent_ops const *fd_ops;    /* [1..1][const] Operators. */
	ino_t                   fd_ino;      /* [const] INode number of this directory entry.
	                                      * Note that this value may not be valid if the entry was deleted! */
	u16                     fd_namelen;  /* [const][!0] Length of the directory entry name (in characters). */
	unsigned char           fd_type;     /* [const] Directory entry type (one of `DT_*') */
	COMPILER_FLEXIBLE_ARRAY(/*utf-8*/ char,
	                        fd_name);    /* [const][fd_namelen] Directory entry name. (NUL-terminated) */
};

#define fdirent_destroy(self) ((*(self)->fd_ops->fdo_destroy)(self))
DEFINE_REFCOUNT_FUNCTIONS(struct fdirent, fd_refcnt, fdirent_destroy)

#define fdirent_opennode(self, dir) ((*(self)->fd_ops->fdo_opennode)(self, dir))

/* Return the hash of a given directory entry name.
 * This function is used by various APIs related to file lookup.
 * @throw: E_SEGFAULT: Failed to access the given `name'. */
FUNDEF WUNUSED NONNULL((1)) uintptr_t KCALL
fdirent_hash(CHECKED USER /*utf-8*/ char const *__restrict name, u16 namelen)
		THROWS(E_SEGFAULT);


DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FDIRENT_H */
