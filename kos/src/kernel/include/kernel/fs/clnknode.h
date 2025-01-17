/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_FS_CLNKNODE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_FS_CLNKNODE_H 1

#include <kernel/compiler.h>

#include <kernel/fs/lnknode.h>

/* Special sub-class of `struct flnknode' with a fixed (constant) string expansion. */

#ifdef __CC__
DECL_BEGIN

struct clnknode
#ifndef __WANT_FS_INLINE_STRUCTURES
    : flnknode                          /* Underlying symlink-node */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct flnknode         lnc_lnode;    /* Underlying symlink-node */
#define _clnknode_lnode_       lnc_lnode.
#define _clnknode_aslnknode(x) &(x)->lnc_lnode
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _clnknode_lnode_       /* nothing */
#define _clnknode_aslnknode(x) x
#endif /* !__cplusplus */
	COMPILER_FLEXIBLE_ARRAY(char, lnc_text); /* [(_clnknode_lnode_ _flnknode_node_ _fnode_file_ mf_fsize / sizeof(char)) + 1]
	                                          * NUL-terminated link constant-link node text. */
};


/************************************************************************/
/* Default operators for `struct clnknode'                             */
/************************************************************************/
FUNDEF WUNUSED NONNULL((1)) size_t KCALL
clnknode_v_readlink(struct flnknode *__restrict self,
                    NCX /*utf-8*/ char *buf,
                    size_t bufsize)
		THROWS(E_SEGFAULT);
FUNDEF ATTR_CONST ATTR_RETNONNULL WUNUSED NONNULL((1)) char const *
NOTHROW(KCALL clnknode_v_linkstr)(struct flnknode *__restrict self);
#define clnknode_v_changed flnknode_v_changed
#define clnknode_v_destroy flnknode_v_destroy
/************************************************************************/



/* Allocate a new constant-link node expanding to exactly `text_length' text characters.
 * The caller must still copy the actual textual contents to `return->lnc_text',  though
 * note that this function will have already written the trailing NUL-character, meaning
 * that _exactly_ `text_length' characters must still be initialized.
 *
 * The caller must still initialize:
 *  - return->_clnknode_lnode_ _flnknode_node_ _fnode_file_ mf_ops     (using `clnknode_v_*' operators)
 *  - return->_clnknode_lnode_ _flnknode_node_ _fnode_file_ mf_atime
 *  - return->_clnknode_lnode_ _flnknode_node_ _fnode_file_ mf_mtime
 *  - return->_clnknode_lnode_ _flnknode_node_ _fnode_file_ mf_ctime
 *  - return->_clnknode_lnode_ _flnknode_node_ _fnode_file_ mf_btime
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_uid
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_gid
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_allnodes
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_supent
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_nlink
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_ino
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_mode (with something or'd with S_IFLNK)
 *  - return->lnc_text[0 ... text_length-1]    (exactly `text_length' characters; trailing NUL was already initialized) */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct clnknode *FCALL
_clnknode_alloc(struct fsuper *__restrict super, size_t text_length)
		THROWS(E_BADALLOC);

/* Helper-wrapper for `_clnknode_alloc()' that will populate the
 * link-node with `text_length'  characters copied from  `text'.
 *
 * The caller must still initialize:
 *  - return->_clnknode_lnode_ _flnknode_node_ _fnode_file_ mf_ops     (using `clnknode_v_*' operators)
 *  - return->_clnknode_lnode_ _flnknode_node_ _fnode_file_ mf_atime
 *  - return->_clnknode_lnode_ _flnknode_node_ _fnode_file_ mf_mtime
 *  - return->_clnknode_lnode_ _flnknode_node_ _fnode_file_ mf_ctime
 *  - return->_clnknode_lnode_ _flnknode_node_ _fnode_file_ mf_btime
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_uid
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_gid
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_allnodes
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_supent
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_nlink
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_ino
 *  - return->_clnknode_lnode_ _flnknode_node_ fn_mode (with something or'd with S_IFLNK) */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct clnknode *FCALL
_clnknode_new(struct fsuper *__restrict super,
              NCX char const *text, size_t text_length)
		THROWS(E_BADALLOC, E_SEGFAULT);


#ifndef ____os_free_defined
#define ____os_free_defined
FUNDEF NOBLOCK void NOTHROW(KCALL __os_free)(VIRT void *ptr) ASMNAME("kfree");
#endif /* !____os_free_defined */

/* Destroy a partially initialized `struct clnknode' (as returned by `_clnknode_alloc()' and `_clnknode_new()') */
#define _clnknode_destroy(self) \
	(_flnknode_fini(_clnknode_aslnknode(self)), __os_free(self))

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_FS_CLNKNODE_H */
