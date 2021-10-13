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
#ifndef GUARD_KERNEL_CORE_FILESYS_LNKNODE_C
#define GUARD_KERNEL_CORE_FILESYS_LNKNODE_C 1

#include <kernel/compiler.h>

#include <kernel/fs/clnknode.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/super.h>
#include <kernel/malloc.h>
#include <sched/atomic64.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* Default implementation for  `flnknode_ops::lno_readlink' that may  be used  when
 * the alternate `lno_linkstr' operator is implemented, in which case said operator
 * is invoked before the returned string is copied into the supplied buffer. */
PUBLIC WUNUSED NONNULL((1)) size_t KCALL
flnknode_v_readlink_default(struct flnknode *__restrict self,
                            USER CHECKED /*utf-8*/ char *buf,
                            size_t bufsize)
			THROWS(E_SEGFAULT, E_IOERROR, ...) {
	size_t result;
	char const *linkstr;
	assert(flnknode_haslinkstr(self));
	linkstr = flnknode_getlinkstr(self);
	assert(linkstr);

	/* Load the link text length and assert that it is correct. */
	COMPILER_READ_BARRIER();
	result = (size_t)__atomic64_val(self->mf_filesize);
	assert(result >= strlen(linkstr) * sizeof(char));

	/* Copy link text into user-space buffer. */
	if (bufsize > result)
		bufsize = result;
	memcpy(buf, linkstr, result);
	return result;
}

/************************************************************************/
/* Operators for `struct fclnknode'                                     */
/************************************************************************/
#ifndef __OPTIMIZE_SIZE__
PUBLIC WUNUSED NONNULL((1)) size_t KCALL
fclnknode_v_readlink(struct flnknode *__restrict self,
                     USER CHECKED /*utf-8*/ char *buf,
                     size_t bufsize)
		THROWS(E_SEGFAULT) {
	struct fclnknode *me;
	size_t result;
	me     = (struct fclnknode *)self;
	result = (size_t)__atomic64_val(me->mf_filesize);
	if (bufsize > result)
		bufsize = result;
	memcpy(buf, me->lnc_text, bufsize);
	return result;
}
#else /* !__OPTIMIZE_SIZE__ */
DEFINE_PUBLIC_ALIAS(fclnknode_v_readlink, flnknode_v_readlink_default);
#endif /* __OPTIMIZE_SIZE__ */

PUBLIC ATTR_CONST ATTR_RETNONNULL WUNUSED NONNULL((1)) char const *
NOTHROW(KCALL fclnknode_v_linkstr)(struct flnknode *__restrict self) {
	struct fclnknode *me;
	me = (struct fclnknode *)self;
	return me->lnc_text;
}
/************************************************************************/


/* Allocate a new constant-link node expanding to exactly `text_length' text characters.
 * The caller must still copy the actual textual contents to `return->lnc_text',  though
 * note that this function will have already written the trailing NUL-character, meaning
 * that _exactly_ `text_length' characters must still be initialized.
 *
 * The caller must still initialize:
 *  - return->_fclnknode_lnode_ _flnknode_node_ _fnode_file_ mf_ops
 *  - return->_fclnknode_lnode_ _flnknode_node_ _fnode_file_ mf_atime
 *  - return->_fclnknode_lnode_ _flnknode_node_ _fnode_file_ mf_mtime
 *  - return->_fclnknode_lnode_ _flnknode_node_ _fnode_file_ mf_ctime
 *  - return->_fclnknode_lnode_ _flnknode_node_ fn_uid
 *  - return->_fclnknode_lnode_ _flnknode_node_ fn_gid
 *  - return->_fclnknode_lnode_ _flnknode_node_ fn_allnodes
 *  - return->_fclnknode_lnode_ _flnknode_node_ fn_supent
 *  - return->_fclnknode_lnode_ _flnknode_node_ fn_ino
 *  - return->_fclnknode_lnode_ _flnknode_node_ fn_mode (with something or'd with S_IFLNK)
 *  - return->lnc_text[0 ... text_length-1]    (exactly `text_length' characters; trailing NUL was already initialized) */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fclnknode *FCALL
_fclnknode_alloc(struct fsuper *__restrict super, size_t text_length) THROWS(E_BADALLOC) {
	REF struct fclnknode *result;
	result = (struct fclnknode *)kmalloc(offsetof(struct fclnknode, lnc_text) +
	                                     (text_length + 1) * sizeof(char),
	                                     GFP_NORMAL);
	/* Initialize all common fields. */
	_mfile_init_common(result);
	result->mf_parts = MFILE_PARTS_ANONYMOUS;
	result->mf_flags = ((super)->fs_root.mf_flags & (MFILE_F_DELETED | MFILE_F_PERSISTENT |
	                                                 MFILE_F_NOATIME | MFILE_F_NOMTIME)) |
	                   (MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE |
	                    MFILE_F_NOUSRMMAP | MFILE_F_NOUSRIO);
	result->mf_blockshift = (super)->fs_root.mf_blockshift;
	result->mf_part_amask = (super)->fs_root.mf_part_amask;
	result->fn_nlink      = 1;
	result->fn_super      = incref(super);
	atomic64_init(&result->mf_filesize, text_length);
	result->lnc_text[text_length] = '\0';
	return result;
}

/* Helper-wrapper for `_fclnknode_alloc()' that will populate the
 * link-node with  `text_length' characters  copied from  `text'. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fclnknode *FCALL
_fclnknode_new(struct fsuper *__restrict super,
               USER CHECKED char const *text, size_t text_length)
		THROWS(E_BADALLOC, E_SEGFAULT) {
	REF struct fclnknode *result;
	result = _fclnknode_alloc(super, text_length);
	/* Copy the given text into the clnknode's buffer. */
	TRY {
		memcpy(result->lnc_text, text, text_length);
	} EXCEPT {
		_fclnknode_destroy(result);
		RETHROW();
	}
	return result;
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_LNKNODE_C */
