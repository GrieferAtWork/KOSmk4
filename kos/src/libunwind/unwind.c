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
#ifndef GUARD_LIBUNWIND_UNWIND_C
#define GUARD_LIBUNWIND_UNWIND_C 1
#define _KOS_SOURCE 1

#include "unwind.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <stdbool.h>

#include <libdebuginfo/api.h> /* LIBDEBUGINFO_CC_IS_LIBUNWIND_CC */
#include <libunwind/unwind.h>

#include "eh_frame.h"

#ifndef __KERNEL__
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/anno.h>

#include <assert.h>
#include <dlfcn.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>
#endif /* !__KERNEL__ */

DECL_BEGIN


/* NOTE: In kernel-space, `libuw_unwind_fde_find()'  is
 *       in `/kos/src/kernel/core/memory/mman/driver.c' */
#ifndef __KERNEL__
PRIVATE NONNULL((1, 3)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_find_new)(void *dlmod, void const *absolute_pc,
                                          unwind_fde_t *__restrict result) {
	unsigned int error;
	struct dl_section *eh_frame_sect;
	/* Lock the module's .eh_frame section into memory. */
	eh_frame_sect = dllocksection(dlmod,
	                              ".eh_frame",
	                              DLLOCKSECTION_FNORMAL);
	if unlikely(!eh_frame_sect)
		ERROR(err);
	/* Scan the .eh_frame section of the associated module. */
	error = libuw_unwind_fde_scan((byte_t const *)eh_frame_sect->ds_data,
	                              (byte_t const *)eh_frame_sect->ds_data + eh_frame_sect->ds_size,
	                              absolute_pc,
	                              result,
	                              sizeof(void *));
	dlunlocksection(eh_frame_sect);
	return error;
err:
	return UNWIND_NO_FRAME;
}

struct fde_cache_entry {
	unwind_fde_t                   fce_fde;    /* [const] The FDE entry being cached.
	                                            * When `f_pcstart...f_pcend' range is
	                                            * used as key-pair for the LLRB-tree */
	__WEAK __REF void             *fce_dlhand; /* [const] Weak reference for the  dl-handle of the library  that
	                                            * is backing this slot. This weakref is used to detect when  the
	                                            * associated module has been dlclose'd, at which point this will
	                                            * point to a wasdestroyed()-object. */
	LLRBTREE_NODE(fde_cache_entry) fce_link;   /* Tree of cached FDE entries. */
};

DECL_END

#define RBTREE_LEFT_LEANING
#define RBTREE_WANT_TRYINSERT
#define RBTREE_WANT_RREMOVE
#define RBTREE_OMIT_REMOVE
#define RBTREE_DECL            PRIVATE
#define RBTREE_IMPL            PRIVATE
#define RBTREE(name)           fde_cache_tree_##name
#define RBTREE_T               struct fde_cache_entry
#define RBTREE_Tkey            void const *
#define RBTREE_GETNODE(self)   (self)->fce_link
#define RBTREE_GETMINKEY(self) ((self)->fce_fde.f_pcstart)
#define RBTREE_GETMAXKEY(self) ((byte_t *)(self)->fce_fde.f_pcend - 1)
#define RBTREE_ISRED(self)     ((self)->fce_fde.f_sigframe & 0x80)
#define RBTREE_SETRED(self)    ((self)->fce_fde.f_sigframe |= 0x80)
#define RBTREE_SETBLACK(self)  ((self)->fce_fde.f_sigframe &= ~0x80)
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

/* [0..n][lock(fde_cache_lock)] The FDE cache tree */
PRIVATE LLRBTREE_ROOT(fde_cache_entry) fde_cache = NULL;
PRIVATE struct atomic_rwlock fde_cache_lock = ATOMIC_RWLOCK_INIT;

PRIVATE NONNULL((1)) void CC
fde_cache_entry_destroy(struct fde_cache_entry *__restrict self) {
	dlauxctrl(self->fce_dlhand, DLAUXCTRL_MOD_WEAKDECREF);
	free(self);
}

PRIVATE NONNULL((1)) void CC
uw_clear_cache_tree(struct fde_cache_entry *__restrict root) {
	struct fde_cache_entry *lhs, *rhs;
again:
	lhs = root->fce_link.rb_lhs;
	rhs = root->fce_link.rb_rhs;
	fde_cache_entry_destroy(root);
	if (lhs) {
		if (rhs)
			uw_clear_cache_tree(rhs);
		root = lhs;
		goto again;
	}
	if (rhs) {
		root = rhs;
		goto again;
	}
}

/* Library finalizer (called by -Wl,-fini=libuw_fini) */
INTERN void libuw_fini(void) {
	/* Clear the FDE cache, and drop all references */
	if (fde_cache)
		uw_clear_cache_tree(fde_cache);
}



/* Lookup FDE information  associated with a  given program counter  position.
 * Using integration with KOS's DL extension APIs, this function automatically
 * accesses the `.eh_frame' sections of  the module associated with the  given
 * address, as well as  keep track of a  lazily allocated address-tree of  FDE
 * caches for quick (O(1))  repeated access to an  FDE located within a  known
 * function. */
INTERN NONNULL((2)) unsigned int
NOTHROW_NCX(CC libuw_unwind_fde_find)(void const *absolute_pc,
                                      unwind_fde_t *__restrict result) {
	struct fde_cache_entry *fce;
	void *dlmod;
	unsigned int error;
	/* Try to search the FDE-cache.
	 * NOTE: To prevent deadlocks upon re-entrance, only
	 *       _try_ to acquire locks here, and ignore the
	 *       cache if we're unable to acquire them! */
	if (atomic_rwlock_tryread(&fde_cache_lock)) {
		fce = fde_cache_tree_locate(fde_cache, absolute_pc);
		if (fce) {
			if likely(dlauxctrl(fce->fce_dlhand, DLAUXCTRL_MOD_NOTDESTROYED) != NULL) {
				memcpy(result, &fce->fce_fde, sizeof(unwind_fde_t));
				atomic_rwlock_endread(&fde_cache_lock);
				result->f_sigframe &= ~0x80; /* 0x80 is (ab-)used as R/B-bit */
				return UNWIND_SUCCESS;
			}
			/* Module  was  deleted in  the  mean time...
			 * Try to get rid of the stale cache entry... */
			if (atomic_rwlock_tryupgrade(&fde_cache_lock)) {
				fde_cache_tree_removenode(&fde_cache, fce);
				atomic_rwlock_endwrite(&fde_cache_lock);
				fde_cache_entry_destroy(fce);
				goto do_lookup_fde;
			}
		}
		atomic_rwlock_endread(&fde_cache_lock);
	}

do_lookup_fde:
	/* Lookup the module associated with the given program counter position. */
	dlmod = dlgethandle(absolute_pc, DLGETHANDLE_FNORMAL);
	if unlikely(!dlmod)
		ERROR(err);
	error = libuw_unwind_fde_find_new(dlmod, absolute_pc, result);
	if unlikely(error != UNWIND_SUCCESS)
		goto done;

	/* (try to) cache the results */
	fce = (struct fde_cache_entry *)malloc(sizeof(struct fde_cache_entry)); /* XXX: malloc_nonblock? */
	if unlikely(fce == NULL)
		goto done;
	memcpy(&fce->fce_fde, result, sizeof(unwind_fde_t));
	fce->fce_dlhand = dlauxctrl(dlmod, DLAUXCTRL_MOD_WEAKINCREF);
	if unlikely(!atomic_rwlock_trywrite(&fde_cache_lock)) {
destroy_new_fce:
		fde_cache_entry_destroy(fce);
		goto done;
	}
	if unlikely(!fde_cache_tree_tryinsert(&fde_cache, fce)) {
		/* TODO: Handle this by downgrading the lock and starting over. */
		struct fde_cache_entry *existing_fce;
		/* Try to remove the existing cache entry. */
		existing_fce = fde_cache_tree_rremove(&fde_cache, result->f_pcstart,
		                                      (byte_t *)result->f_pcend - 1);
		assert(existing_fce);
		if (dlauxctrl(fce->fce_dlhand, DLAUXCTRL_MOD_NOTDESTROYED) != NULL) {
			/* Entry isn't stale...
			 * This might happen if another thread created this entry while
			 * we  created  ours, but  after  we checked  for  another pre-
			 * existing above! */
			memcpy(result, &existing_fce->fce_fde, sizeof(unwind_fde_t));
			fde_cache_tree_insert(&fde_cache, existing_fce);
			atomic_rwlock_endwrite(&fde_cache_lock);
			result->f_sigframe &= ~0x80; /* 0x80 is (ab-)used as R/B-bit */
			goto destroy_new_fce;
		}

		/* Force-insert the new cache entry. */
		fde_cache_tree_insert(&fde_cache, fce);
		atomic_rwlock_endwrite(&fde_cache_lock);

		/* Destroy the (stale) old cache entry. */
		fde_cache_entry_destroy(existing_fce);
	} else {
		atomic_rwlock_endwrite(&fde_cache_lock);
	}
done:
	return error;
err:
	return UNWIND_NO_FRAME;
}

DEFINE_PUBLIC_ALIAS(unwind_fde_find, libuw_unwind_fde_find);
#endif /* !__KERNEL__ */



/* Top-level function for unwinding the specific register state, automatically
 * locating the associated FDE entry, before using it to unwind the  specified
 * register state.
 * NOTE: The given `absolute_pc' should point _to_ or _into_ the instruction that
 *       should be  unwound; Not  after it.  - i.e.  range checking  is done  as:
 *       `absolute_pc >= start && absolute_pc < end'
 * @return: * : One of `UNWIND_*' (UNWIND_SUCCESS on success, other values on failure) */
INTERN NONNULL((2, 4)) unsigned int CC
linuw_unwind(void const *absolute_pc,
             unwind_getreg_t reg_getter, void const *reg_getter_arg,
             unwind_setreg_t reg_setter, void *reg_setter_arg) {
	unsigned int result;
	unwind_fde_t fde;
	result = libuw_unwind_fde_find(absolute_pc, &fde);
	if unlikely(result != UNWIND_SUCCESS)
		goto done;
#ifndef __OPTIMIZE_SIZE__
	/* Optimization for unwinding through signal frames! */
	if (fde.f_sigframe) {
		unwind_cfa_sigframe_state_t cfa;
		result = libuw_unwind_fde_sigframe_exec(&fde, &cfa, absolute_pc);
		if unlikely(result != UNWIND_SUCCESS)
			goto done;
		result = libuw_unwind_cfa_sigframe_apply(&cfa, &fde, absolute_pc,
		                                         reg_getter, reg_getter_arg,
		                                         reg_setter, reg_setter_arg);
	} else
#endif /* !__OPTIMIZE_SIZE__ */
	{
		unwind_cfa_state_t cfa;
		result = libuw_unwind_fde_exec(&fde, &cfa, absolute_pc);
		if unlikely(result != UNWIND_SUCCESS)
			goto done;
		result = libuw_unwind_cfa_apply(&cfa, &fde, absolute_pc,
		                                reg_getter, reg_getter_arg,
		                                reg_setter, reg_setter_arg);
	}
done:
	return result;
}



DEFINE_PUBLIC_ALIAS(unwind, linuw_unwind);

DECL_END

#endif /* !GUARD_LIBUNWIND_UNWIND_C */
