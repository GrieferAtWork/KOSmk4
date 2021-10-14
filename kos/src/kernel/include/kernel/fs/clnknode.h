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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_CLNKNODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_CLNKNODE_H 1

#include <kernel/compiler.h>

/* Special sub-class of `struct flnknode' with a fixed (constant) string expansion. */

#ifndef CONFIG_USE_NEW_FS
#include <fs/node.h>
#else /* !CONFIG_USE_NEW_FS */
#include <kernel/fs/lnknode.h>

#ifdef __CC__
DECL_BEGIN

struct fclnknode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : flnknode                          /* Underlying symlink-node */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct flnknode         lnc_lnode;    /* Underlying symlink-node */
#define _fclnknode_lnode_       lnc_lnode.
#define _fclnknode_aslnknode(x) &(x)->lnc_lnode
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _fclnknode_lnode_       /* nothing */
#define _fclnknode_aslnknode(x) x
#endif /* !__cplusplus */
	COMPILER_FLEXIBLE_ARRAY(char, lnc_text); /* [(_fclnknode_lnode_ _flnknode_node_ _fnode_file_ mf_fsize / sizeof(char)) + 1]
	                                          * NUL-terminated link constant-link node text. */
};


/************************************************************************/
/* Default operators for `struct fclnknode'                             */
/************************************************************************/
FUNDEF WUNUSED NONNULL((1)) size_t KCALL
fclnknode_v_readlink(struct flnknode *__restrict self,
                     USER CHECKED /*utf-8*/ char *buf,
                     size_t bufsize)
		THROWS(E_SEGFAULT);
FUNDEF ATTR_CONST ATTR_RETNONNULL WUNUSED NONNULL((1)) char const *
NOTHROW(KCALL fclnknode_v_linkstr)(struct flnknode *__restrict self);
#define fclnknode_v_destroy fnode_v_destroy
/************************************************************************/



/* Allocate a new constant-link node expanding to exactly `text_length' text characters.
 * The caller must still copy the actual textual contents to `return->lnc_text',  though
 * note that this function will have already written the trailing NUL-character, meaning
 * that _exactly_ `text_length' characters must still be initialized.
 *
 * The caller must still initialize:
 *  - return->_fclnknode_lnode_ _flnknode_node_ _fnode_file_ mf_ops     (using `fclnknode_v_*' operators)
 *  - return->_fclnknode_lnode_ _flnknode_node_ _fnode_file_ mf_atime
 *  - return->_fclnknode_lnode_ _flnknode_node_ _fnode_file_ mf_mtime
 *  - return->_fclnknode_lnode_ _flnknode_node_ _fnode_file_ mf_ctime
 *  - return->_fclnknode_lnode_ _flnknode_node_ fn_uid
 *  - return->_fclnknode_lnode_ _flnknode_node_ fn_gid
 *  - return->_fclnknode_lnode_ _flnknode_node_ fn_allnodes
 *  - return->_fclnknode_lnode_ _flnknode_node_ fn_supent
 *  - return->_fclnknode_lnode_ _flnknode_node_ fn_nlink
 *  - return->_fclnknode_lnode_ _flnknode_node_ fn_ino
 *  - return->_fclnknode_lnode_ _flnknode_node_ fn_mode (with something or'd with S_IFLNK)
 *  - return->lnc_text[0 ... text_length-1]    (exactly `text_length' characters; trailing NUL was already initialized) */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fclnknode *FCALL
_fclnknode_alloc(struct fsuper *__restrict super, size_t text_length) THROWS(E_BADALLOC);

/* Helper-wrapper for `_fclnknode_alloc()' that will populate the
 * link-node with  `text_length' characters  copied from  `text'. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fclnknode *FCALL
_fclnknode_new(struct fsuper *__restrict super,
               USER CHECKED char const *text, size_t text_length)
		THROWS(E_BADALLOC, E_SEGFAULT);


#ifndef ____os_free_defined
#define ____os_free_defined
FUNDEF NOBLOCK void NOTHROW(KCALL __os_free)(VIRT void *ptr) ASMNAME("kfree");
#endif /* !____os_free_defined */

/* Destroy a partially initialized `struct fclnknode' (as returned by `_fclnknode_alloc()' and `_fclnknode_new()') */
#define _fclnknode_destroy(self) \
	(_flnknode_fini(_fclnknode_aslnknode(self)), __os_free(self))

DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_FS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_CLNKNODE_H */
