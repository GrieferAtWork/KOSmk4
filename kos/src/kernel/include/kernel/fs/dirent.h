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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_DIRENT_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_DIRENT_H 1

#include <kernel/compiler.h>

#include <kernel/fs/notify.h> /* dnotify_controller_bindchild() */
#include <kernel/types.h>

#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#ifdef __CC__
DECL_BEGIN

struct fnode;
struct fdirent;
struct fdirnode;

struct fdirent_ops {
	/* [1..1] Destroy callback. */
	NOBLOCK NONNULL((1)) void /*NOTHROW*/
	(KCALL *fdo_destroy)(struct fdirent *__restrict self);

	/* [1..1] Open the node  associated with  this directory  entry.
	 * If the entry has already been deleted, return `NULL' instead.
	 * @param: dir: The directory that contains `self'
	 * @return: NULL: `self'  was  deleted and  you must  re-query the
	 *                containing directory `dir' for the proper entry. */
	BLOCKING WUNUSED NONNULL((1, 2)) REF struct fnode *
	(KCALL *fdo_opennode)(struct fdirent *__restrict self,
	                      struct fdirnode *__restrict dir)
			THROWS(E_BADALLOC, E_IOERROR, ...);

	/* [0..1] Optional override for dynamically calculated `fd_ino' values.
	 * When this operator is defined, _IT_ must be used instead of `fd_ino' */
	BLOCKING WUNUSED NONNULL((1, 2)) ino_t
	(FCALL *fdo_getino)(struct fdirent *__restrict self,
	                    struct fdirnode *__restrict dir)
			THROWS(E_IOERROR, ...);
};

struct fdirent {
	/* Additional fs-specific  data usually  goes here  (iow: at  negative
	 * offsets, such that the  filesystem layer will use  `container_of()'
	 * to access the container structure). Alternatively, data could  also
	 * go at  `fd_name[fd_namelen]', however  this is  less likely,  since
	 * doing this would require making use of non-constant struct offsets. */
	WEAK refcnt_t                           fd_refcnt;   /* Reference counter. */
	struct fdirent_ops const               *fd_ops;      /* [1..1][const] Operators. */
	ino_t                                   fd_ino;      /* [const][valid_if(fd_ops->fdo_getino == NULL)] INode number of this directory
	                                                      * entry. WARNING: This  value becomes  invalid if the  entry/file is  deleted! */
	uintptr_t                               fd_hash;     /* [const][== fdirent_hash(fd_name, fd_namelen)] Hash of this directory entry. */
	u16                                     fd_namelen;  /* [const][!0] Length of the directory entry name (in characters). */
	unsigned char                           fd_type;     /* [const] Directory entry type (one of `DT_*') */
	COMPILER_FLEXIBLE_ARRAY(/*utf-8*/ char, fd_name);    /* [const][fd_namelen] Directory entry name. (NUL-terminated) */
};

#define fdirent_destroy(self) ((*(self)->fd_ops->fdo_destroy)(self))
DEFINE_REFCOUNT_FUNCTIONS(struct fdirent, fd_refcnt, fdirent_destroy)

/* Open the node associated with this directory entry. */
#ifdef CONFIG_HAVE_FS_NOTIFY
#define fdirent_opennode(self, dir) dnotify_controller_bindchild(dir, self, (*(self)->fd_ops->fdo_opennode)(self, dir))
#else /* CONFIG_HAVE_FS_NOTIFY */
#define fdirent_opennode(self, dir) ((*(self)->fd_ops->fdo_opennode)(self, dir))
#endif /* !CONFIG_HAVE_FS_NOTIFY */

/* Return the INode number of `self', potentially invoking the override operator. */
#define fdirent_getino(self, dir)                                          \
	((self)->fd_ops->fdo_getino ? (*(self)->fd_ops->fdo_getino)(self, dir) \
	                            : (self)->fd_ino)


/* Return the hash of a given directory entry name.
 * This function is used by various APIs related to file lookup.
 * @throw: E_SEGFAULT: Failed to access the given `text'. */
FUNDEF ATTR_PURE WUNUSED uintptr_t FCALL
fdirent_hash(CHECKED USER /*utf-8*/ char const *text, u16 textlen)
		THROWS(E_SEGFAULT);
#define FDIRENT_EMPTY_HASH 0 /* == fdirent_hash("", 0) */

#if __SIZEOF_POINTER__ == 4 && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define FDIRENT_HASH_INIT(le32, le64, be32, be64) __UINT32_C(le32)
#elif __SIZEOF_POINTER__ == 8 && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define FDIRENT_HASH_INIT(le32, le64, be32, be64) __UINT64_C(le64)
#elif __SIZEOF_POINTER__ == 4 && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define FDIRENT_HASH_INIT(le32, le64, be32, be64) __UINT32_C(be32)
#elif __SIZEOF_POINTER__ == 8 && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define FDIRENT_HASH_INIT(le32, le64, be32, be64) __UINT64_C(be64)
#else /* __SIZEOF_POINTER__ == ... && __BYTE_ORDER__ == ... */
#error "Invalid configuration"
#endif /* __SIZEOF_POINTER__ != ... || __BYTE_ORDER__ != ... */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_DIRENT_H */
