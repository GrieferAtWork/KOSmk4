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
#ifndef GUARD_KERNEL_CORE_FILESYS_CONSTDIR_C
#define GUARD_KERNEL_CORE_FILESYS_CONSTDIR_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/constdir.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/node.h>
#include <kernel/malloc.h>

#include <hybrid/atomic.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

DECL_BEGIN

/* Assert that fields of `struct constdirent' are binary compatible with `fdirent' starting at `cd_refcnt' */
static_assert((offsetof(struct constdirent, cd_refcnt) - offsetof(struct constdirent, cd_refcnt)) == offsetof(struct fdirent, fd_refcnt));
static_assert((offsetof(struct constdirent, cd_ops) - offsetof(struct constdirent, cd_refcnt)) == offsetof(struct fdirent, fd_ops));
static_assert((offsetof(struct constdirent, cd_ino) - offsetof(struct constdirent, cd_refcnt)) == offsetof(struct fdirent, fd_ino));
static_assert((offsetof(struct constdirent, cd_hash) - offsetof(struct constdirent, cd_refcnt)) == offsetof(struct fdirent, fd_hash));
static_assert((offsetof(struct constdirent, cd_namelen) - offsetof(struct constdirent, cd_refcnt)) == offsetof(struct fdirent, fd_namelen));
static_assert((offsetof(struct constdirent, cd_type) - offsetof(struct constdirent, cd_refcnt)) == offsetof(struct fdirent, fd_type));
static_assert((offsetof(struct constdirent, cd_name) - offsetof(struct constdirent, cd_refcnt)) == offsetof(struct fdirent, fd_name));

/* Operators used to facilitate `struct constdirent' */
PUBLIC_CONST struct fdirent_ops const constdirent_ops = {
	.fdo_destroy  = &constdirent_v_destroy,
	.fdo_opennode = &constdirent_v_opennode,
};

PUBLIC NOBLOCK NONNULL((1)) void /* decref(me->cd_node) + _constdirent_free(me) */
NOTHROW(KCALL constdirent_v_destroy)(struct fdirent *__restrict self) {
	struct constdirent *me = fdirent_asconst(self);
	decref_unlikely(me->cd_node);
	_constdirent_free(me);
}

PUBLIC WUNUSED NONNULL((1, 2)) REF struct fnode *
NOTHROW(KCALL constdirent_v_opennode)(struct fdirent *__restrict self, /* return incref(me->cd_node); */
                                      struct fdirnode *__restrict UNUSED(dir)) {
	struct constdirent *me = fdirent_asconst(self);
	return mfile_asnode(incref(me->cd_node));
}




/* Operators for `struct constdirenum' */
PUBLIC_CONST struct fdirenum_ops const constdirenum_ops = {
	.deo_fini    = &constdirenum_v_fini,
	.deo_readdir = &constdirenum_v_readdir,
	.deo_seekdir = &constdirenum_v_seekdir,
};

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL constdirenum_v_fini)(struct fdirenum *__restrict UNUSED(self)) {
	(void)0; /* No-op */
}

PUBLIC NONNULL((1)) size_t KCALL
constdirenum_v_readdir(struct fdirenum *__restrict self, USER CHECKED struct dirent *buf,
                       size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(...) {
	size_t index;
	ssize_t result;
	struct constdirenum *me = (struct constdirenum *)self;
	struct fdirent *ent;

again:
	/* Read current index. */
	index = ATOMIC_READ(me->cde_index);

	/* Check for EOF */
	if (index >= me->cde_entc)
		return 0;

	/* Emit entry. */
	ent    = me->cde_entv[index];
	result = fdirenum_feedent(buf, bufsize, readdir_mode, ent, me->de_dir);
	if (result < 0)
		return (size_t)~result; /* Don't advance directory position. */

	/* Advance directory position. */
	if (!ATOMIC_CMPXCH(me->cde_index, index, index + 1))
		goto again;
	return (size_t)result;
}

PUBLIC NONNULL((1)) pos_t KCALL
constdirenum_v_seekdir(struct fdirenum *__restrict self,
                       off_t offset, unsigned int whence)
		THROWS(E_OVERFLOW, E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	size_t newpos;
	struct constdirenum *me = (struct constdirenum *)self;
	switch (whence) {
	case SEEK_SET:
#if __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__
		if unlikely((pos_t)offset >= SIZE_MAX)
			THROW(E_OVERFLOW);
#endif /* __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__ */
		newpos = (size_t)(pos_t)offset;
		ATOMIC_WRITE(me->cde_index, newpos);
		break;

	case SEEK_CUR: {
		size_t oldpos;
		do {
			oldpos = ATOMIC_READ(me->cde_index);
			newpos = oldpos + (ssize_t)offset;
			if unlikely(offset < 0 ? newpos > oldpos
			                       : newpos < oldpos)
				THROW(E_OVERFLOW);
		} while (!ATOMIC_CMPXCH_WEAK(me->cde_index, oldpos, newpos));
	}	break;

	case SEEK_END: {
		size_t dirsiz;
		dirsiz = me->cde_entc;
		newpos = dirsiz + (ssize_t)offset;
		if unlikely(offset < 0 ? newpos > dirsiz
		                       : newpos < dirsiz)
			THROW(E_OVERFLOW);
		ATOMIC_WRITE(me->cde_index, newpos);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
	}
	return (pos_t)newpos;
}




/* Default operators for `struct constdir' */
PUBLIC WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
constdir_v_lookup(struct fdirnode *__restrict self,
                  struct flookup_info *__restrict info)
		THROWS(E_SEGFAULT) {
	struct fdirent *result;
	struct constdir *me = fdirnode_asconst(self);
	size_t lo, hi;
	lo = 0;
	hi = me->cd_entc;
	while (lo < hi) {
		size_t i;
		int cmp;
		i      = (lo + hi) / 2;
		result = me->cd_entv[i];
		cmp    = strcmpz(result->fd_name, info->flu_name, info->flu_namelen);
		if (cmp > 0) {
			hi = i;
		} else if (cmp < 0) {
			lo = i + 1;
		} else {
			/* Found it! */
			return incref(result);
		}
	}
	/* Check if we're also supposed to do a case-insensitive lookup. */
	if (info->flu_flags & AT_DOSPATH) {
		size_t i;
		for (i = 0; i < me->cd_entc; ++i) {
			result = me->cd_entv[i];
			if (result->fd_namelen != info->flu_namelen)
				continue;
			if (memcasecmp(result->fd_name, info->flu_name,
			               info->flu_namelen * sizeof(char)) != 0)
				continue;
			/* Found it! */
			return incref(result);
		}
	}
	return NULL;
}


PUBLIC NONNULL((1)) void
NOTHROW(KCALL constdir_v_enum)(struct fdirenum *__restrict result) {
	struct constdir *dir;
	struct constdirenum *ret;
	ret = (struct constdirenum *)result;
	dir = fdirnode_asconst(ret->de_dir);
	ret->de_ops    = &constdirenum_ops;
	ret->cde_index = 0;
	ret->cde_entc  = dir->cd_entc;
	ret->cde_entv  = dir->cd_entv;
}

/* Default operators for `struct constdir' (using the functions above) */
PUBLIC_CONST struct fdirnode_ops const constdir_ops = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &constdir_v_destroy,
			.mo_changed = &constdir_v_changed,
			.mo_stream  = &constdir_v_stream_ops,
		},
		.no_wrattr = &constdir_v_wrattr,
	},
	.dno_lookup = &constdir_v_lookup,
	.dno_enumsz = constdir_v_enumsz,
	.dno_enum   = &constdir_v_enum,
};




DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_CONSTDIR_C */
