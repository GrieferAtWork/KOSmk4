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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_FDIRNODE_DYNAMIC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_FDIRNODE_DYNAMIC_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/fdirnode.h>
#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

/* Pre-defined directory access helper node for dynamically
 * constructed directories.
 *
 * A directory of this type may be used for  dynamically
 * generated directories, such as those found in `/proc'
 */


/*  */
typedef NONNULL((5)) __BOOL
(KCALL *fdyndir_enum_callback_t)(void *cookie, ino_t ino, unsigned char type,
                                 u16 namelen, char const *__restrict name);

struct fdyndirnode_ops {
#define _fdyndirnode_ops_firstfield(prefix)  _fdirnode_ops_firstfield(prefix)
#define fdyndirnode_ops_as_fdirnode_ops(ops) ((struct fdirnode_ops const *)&(ops)->_fdirnode_ops_firstfield(ddno_))
#define fdyndirnode_ops_as_fnode_ops(ops)    ((struct fnode_ops const *)&(ops)->_fnode_ops_firstfield(ddno_))
#define fdyndirnode_ops_as_mfile_ops(ops)    ((struct mfile_ops const *)&(ops)->_mfile_ops_firstfield(ddno_))
#define FDYNDIRNODE_OPS_FIELDS(prefix, T)                                             \
	FDIRNODE_OPS_FIELDS(prefix, T);                                                   \
	                                                                                  \
	/* [1..1] Enumerate all files within the directory, calling `cb' for each         \
	 * Enumeration is allowed (but not required) to stop prematurely when the         \
	 * given `cb' returns `false'. Otherwise, _all_ files must be enumerated. */      \
	WUNUSED NONNULL((1, 2)) void                                                      \
	(KCALL *prefix##enumdir)(T *__restrict self,                                      \
	                         fdyndir_enum_callback_t cb, void *cookie)

	/* Operators... */
	FDYNDIRNODE_OPS_FIELDS(ddno_, struct fdyndirnode);
};


struct fdyndirnode
#ifdef __cplusplus
    : fdirnode                       /* Underlying directory-node */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct fdirnode      ldn_dir;    /* Underlying directory-node */
#endif /* !__cplusplus */
};

/* Return a pointer to dynamic-directory-node operators of `self' */
#define fdyndirnode_getops(self) \
	((struct fdyndirnode_ops const *)__COMPILER_REQTYPE(struct fdyndirnode const *, self)->mf_ops)
#define fdyndirnode_enumdir(self, cb, cookie) \
	(*fdyndirnode_getops(self)->ddno_enumdir)(self, cb, cookie)


/* Default callback for `fdyndirnode_ops::ddno_lookup' */
FUNDEF WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
fdyndirnode_lookup(struct fdyndirnode *__restrict self,
                   struct flookup_info *__restrict info);

/* Default callback for `fdyndirnode_ops::ddno_enum' */
FUNDEF NONNULL((1, 2)) void KCALL
fdyndirnode_enum(struct fdyndirnode *__restrict self,
                 struct fdirenum *__restrict result);



DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_FDIRNODE_DYNAMIC_H */
