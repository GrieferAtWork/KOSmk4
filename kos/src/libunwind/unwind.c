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
#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <kos/anno.h>

#include <assert.h>
#include <dlfcn.h>
#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#endif /* !__KERNEL__ */

DECL_BEGIN


#ifndef __KERNEL__

/************************************************************************/
/* FDE Caching                                                          */
/************************************************************************/
struct fde_cache_entry {
	unwind_fde_t                   fce_fde;    /* [const] The FDE entry being  cached.
	                                            * Where `f_pcstart...f_pcend' range is
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
#define RBTREE_GETMAXKEY(self) ((byte_t const *)(self)->fce_fde.f_pcend - 1)
#define RBTREE_REDFIELD        fce_fde.f_sigframe
#define RBTREE_REDBIT          0x80
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

/* [0..n][lock(fde_cache_lock)] The FDE cache tree */
PRIVATE LLRBTREE_ROOT(fde_cache_entry) fde_cache = NULL;
PRIVATE struct atomic_rwlock fde_cache_lock = ATOMIC_RWLOCK_INIT;

/* Helpers for accessing `fde_cache_lock' */
#define _fde_cache_reap()      (void)0
#define fde_cache_reap()       (void)0
#define fde_cache_mustreap()   0
#define fde_cache_write()      atomic_rwlock_write(&fde_cache_lock)
#define fde_cache_trywrite()   atomic_rwlock_trywrite(&fde_cache_lock)
#define fde_cache_endwrite()   (atomic_rwlock_endwrite(&fde_cache_lock), fde_cache_reap())
#define _fde_cache_endwrite()  atomic_rwlock_endwrite(&fde_cache_lock)
#define fde_cache_read()       atomic_rwlock_read(&fde_cache_lock)
#define fde_cache_tryread()    atomic_rwlock_tryread(&fde_cache_lock)
#define _fde_cache_endread()   atomic_rwlock_endread(&fde_cache_lock)
#define fde_cache_endread()    (void)(atomic_rwlock_endread(&fde_cache_lock) && (fde_cache_reap(), 0))
#define _fde_cache_end()       atomic_rwlock_end(&fde_cache_lock)
#define fde_cache_end()        (void)(atomic_rwlock_end(&fde_cache_lock) && (fde_cache_reap(), 0))
#define fde_cache_upgrade()    atomic_rwlock_upgrade(&fde_cache_lock)
#define fde_cache_tryupgrade() atomic_rwlock_tryupgrade(&fde_cache_lock)
#define fde_cache_downgrade()  atomic_rwlock_downgrade(&fde_cache_lock)
#define fde_cache_reading()    atomic_rwlock_reading(&fde_cache_lock)
#define fde_cache_writing()    atomic_rwlock_writing(&fde_cache_lock)
#define fde_cache_canread()    atomic_rwlock_canread(&fde_cache_lock)
#define fde_cache_canwrite()   atomic_rwlock_canwrite(&fde_cache_lock)

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



/************************************************************************/
/* __register_frame API (lazily aliased by libc)                        */
/************************************************************************/
#ifndef LIBCCALL
#define LIBCCALL __LIBCCALL
#endif /* !LIBCCALL */

typedef struct __ATTR_PACKED __ATTR_ALIGNED(__SIZEOF_POINTER__) {
	/* This structure exists  as a (not  100% correct, as  length=0xffffffff
	 * is indicative of an additional 64-bit length field immediately after)
	 * struct representation of what is found in .eh_frame
	 *
	 * The actual layout is documented in <libunwind/eh_frame.h> */
	uint32_t length;
	int32_t  CIE_delta;
	COMPILER_FLEXIBLE_ARRAY(byte_t, pc_begin);
} rf_fde;

struct rf_object {
	union {
		rf_fde const        *ro_eh_frame;       /* [1..1] Pointer to .eh_frame */
		rf_fde const *const *ro_eh_frame_array; /* [0..1][1..N] NULL-terminated array. */
	};
	void const              *ro_tbase;    /* [0..1] .text base address override. */
	void const              *ro_dbase;    /* [0..1] .data base address override. */
	SLIST_ENTRY(rf_object)   ro_link;     /* Link between objects. */
	bool                     ro_isarray;  /* True if this is an array */
};

static_assert(sizeof(struct rf_object) <= 6 * sizeof(void *));

struct dwarf_eh_bases {
	void const *deb_tbase; /* [0..1] .text base address */
	void const *deb_dbase; /* [0..1] .data base address */
	void const *deb_func;  /* [0..1] function base address */
};

INTDEF NONNULL((2)) void LIBCCALL libuw___register_frame_info_bases(/*nullable*/ rf_fde const *begin, struct rf_object *__restrict ob, void const *tbase, void const *dbase);
INTDEF NONNULL((1, 2)) void LIBCCALL libuw___register_frame_info_table_bases(rf_fde const *const *begin, struct rf_object *__restrict ob, void const *tbase, void const *dbase);
INTDEF struct rf_object *NOTHROW(LIBCCALL libuw___deregister_frame_info)(/*nullable*/ void const *begin);
INTDEF NONNULL((1, 2)) rf_fde const *NOTHROW_NCX(LIBCCALL libuw__Unwind_Find_FDE)(void const *pc, /*out*/ struct dwarf_eh_bases *__restrict bases);

SLIST_HEAD(rf_object_slist, rf_object);

/* [0..n] Auxiliary list of eh_frame data data registrations. */
PRIVATE struct rf_object_slist register_frame_aux_list = SLIST_HEAD_INITIALIZER(register_frame_aux_list);
PRIVATE struct atomic_rwlock register_frame_aux_lock   = ATOMIC_RWLOCK_INIT;

/* Helpers for accessing `fde_cache_lock' */
#define _register_frame_aux_reap()      (void)0
#define register_frame_aux_reap()       (void)0
#define register_frame_aux_mustreap()   0
#define register_frame_aux_write()      atomic_rwlock_write(&register_frame_aux_lock)
#define register_frame_aux_trywrite()   atomic_rwlock_trywrite(&register_frame_aux_lock)
#define register_frame_aux_endwrite()   (atomic_rwlock_endwrite(&register_frame_aux_lock), register_frame_aux_reap())
#define _register_frame_aux_endwrite()  atomic_rwlock_endwrite(&register_frame_aux_lock)
#define register_frame_aux_read()       atomic_rwlock_read(&register_frame_aux_lock)
#define register_frame_aux_tryread()    atomic_rwlock_tryread(&register_frame_aux_lock)
#define _register_frame_aux_endread()   atomic_rwlock_endread(&register_frame_aux_lock)
#define register_frame_aux_endread()    (void)(atomic_rwlock_endread(&register_frame_aux_lock) && (register_frame_aux_reap(), 0))
#define _register_frame_aux_end()       atomic_rwlock_end(&register_frame_aux_lock)
#define register_frame_aux_end()        (void)(atomic_rwlock_end(&register_frame_aux_lock) && (register_frame_aux_reap(), 0))
#define register_frame_aux_upgrade()    atomic_rwlock_upgrade(&register_frame_aux_lock)
#define register_frame_aux_tryupgrade() atomic_rwlock_tryupgrade(&register_frame_aux_lock)
#define register_frame_aux_downgrade()  atomic_rwlock_downgrade(&register_frame_aux_lock)
#define register_frame_aux_reading()    atomic_rwlock_reading(&register_frame_aux_lock)
#define register_frame_aux_writing()    atomic_rwlock_writing(&register_frame_aux_lock)
#define register_frame_aux_canread()    atomic_rwlock_canread(&register_frame_aux_lock)
#define register_frame_aux_canwrite()   atomic_rwlock_canwrite(&register_frame_aux_lock)



/* Implementation */
INTERN NONNULL((2)) void LIBCCALL
libuw___register_frame_info_bases(/*nullable*/ rf_fde const *begin, struct rf_object *__restrict ob,
                                  void const *tbase, void const *dbase) {
	if (!begin || begin->length == 0)
		return; /* Special case: empty .eh_frame section */
	ob->ro_eh_frame = begin;
	ob->ro_tbase    = tbase;
	ob->ro_dbase    = dbase;
	ob->ro_isarray  = false;

	/* Insert into the list of auxiliary objects */
	register_frame_aux_write();
	SLIST_INSERT(&register_frame_aux_list, ob, ro_link);
	register_frame_aux_endwrite();
}

INTERN NONNULL((1, 2)) void LIBCCALL
libuw___register_frame_info_table_bases(rf_fde const *const *begin, struct rf_object *__restrict ob,
                                        void const *tbase, void const *dbase) {
	ob->ro_eh_frame_array = begin;
	ob->ro_tbase          = tbase;
	ob->ro_dbase          = dbase;
	ob->ro_isarray        = true;

	/* Insert into the list of auxiliary objects */
	register_frame_aux_write();
	SLIST_INSERT(&register_frame_aux_list, ob, ro_link);
	register_frame_aux_endwrite();
}


/* Remove all cache references to FDE entries from `eh_frame' */
PRIVATE void
NOTHROW(LIBCCALL remove_cache_references)(byte_t const *eh_frame,
                                          void const *tbase,
                                          void const *dbase) {
	unwind_errno_t error;
	unwind_fde_t fde;
	for (;;) {
		fde.f_tbase = tbase;
		fde.f_dbase = dbase;
		error = libuw_unwind_fde_load(&eh_frame, (byte_t *)-1, &fde, sizeof(void *));
		if (error != UNWIND_SUCCESS)
			break;
		/* Try to remove entries from this range. */
		if likely((byte_t const *)fde.f_pcstart <
		          (byte_t const *)fde.f_pcend) {
			struct fde_cache_entry *cent;
			while ((cent = fde_cache_tree_rremove(&fde_cache,
			                                      (byte_t const *)fde.f_pcstart,
			                                      (byte_t const *)fde.f_pcend - 1)))
				fde_cache_entry_destroy(cent);
		}
	}
}

INTERN struct rf_object *
NOTHROW(LIBCCALL libuw___deregister_frame_info)(/*nullable*/ void const *begin) {
	struct rf_object *result;
	if (!begin || *(uint32_t const *)begin == 0)
		return NULL;

	/* Try to remove an entry for the given eh_frame base from the list. */
	register_frame_aux_write();
	SLIST_TRYREMOVE_IF(&register_frame_aux_list, &result, ro_link,
	                   result->ro_eh_frame == (rf_fde const *)begin,
	                   { result = NULL; });
	register_frame_aux_endwrite();

	/* Upon success, we must also remove all FDE caches associated with
	 * entries FDE descriptors  for the object  that was just  removed. */
	if (result != NULL) {
		fde_cache_write();
		if (result->ro_isarray) {
			size_t i;
			for (i = 0;; ++i) {
				rf_fde const *eh_frame;
				eh_frame = result->ro_eh_frame_array[i];
				if (!eh_frame)
					break;
				remove_cache_references((byte_t const *)eh_frame,
				                        result->ro_tbase,
				                        result->ro_dbase);
			}
		} else {
			remove_cache_references((byte_t const *)result->ro_eh_frame,
			                        result->ro_tbase,
			                        result->ro_dbase);
		}
		fde_cache_endwrite();
	}

	return result;
}

PRIVATE NONNULL((4)) rf_fde const *
NOTHROW_NCX(CC fde_locate_pc)(void const *absolute_pc,
                              byte_t const *eh_frame_start,
                              byte_t const *eh_frame_end,
                              struct dwarf_eh_bases *__restrict bases) {
	unwind_errno_t error;
	unwind_fde_t fde;
	fde.f_dbase = bases->deb_dbase;
	fde.f_tbase = bases->deb_tbase;
	for (;;) {
		rf_fde const *result;
		result = (rf_fde const *)eh_frame_start;
		error  = libuw_unwind_fde_load(&eh_frame_start, eh_frame_end, &fde, sizeof(void *));
		if (error != UNWIND_SUCCESS)
			break;
		/* Check if this FDE contained what we're looking for */
		if (absolute_pc >= fde.f_pcstart &&
		    absolute_pc < fde.f_pcend) {
			bases->deb_dbase = fde.f_dbase;
			bases->deb_tbase = fde.f_tbase;
			bases->deb_func  = fde.f_pcstart;
			return result;
		}
	}
	return NULL;
}


INTERN NONNULL((1, 2)) rf_fde const *
NOTHROW_NCX(LIBCCALL libuw__Unwind_Find_FDE)(void const *pc, /*out*/ struct dwarf_eh_bases *__restrict bases) {
	rf_fde const *result;
	void *dlmod;
	struct dl_section *eh_frame_sect;
	struct rf_object *obj;

	/* Check if we can find the FDE by searching for a module and loading that module's .eh_frame section. */
	dlmod = dlgethandle(pc, DLGETHANDLE_FNORMAL);
	if (dlmod == NULL)
		goto no_dl_info;
	eh_frame_sect = dllocksection(dlmod, ".eh_frame", DLLOCKSECTION_FNODATA);
	if (eh_frame_sect == NULL) {
		/* TODO: Support for: `.eh_frame_hdr' (and its alias: `PT_GNU_EH_FRAME') */
		goto no_dl_info;
	}
	if (eh_frame_sect->ds_data != (void *)-1) {
		/* Search through this modules .eh_frame section. */
		bases->deb_tbase = NULL;
		bases->deb_dbase = NULL;
		result = fde_locate_pc(pc,
		                       (byte_t const *)eh_frame_sect->ds_data,
		                       (byte_t const *)eh_frame_sect->ds_data + eh_frame_sect->ds_size,
		                       bases);
		if (result != NULL) {
			if (bases->deb_tbase == NULL)
				bases->deb_tbase = dlauxctrl(dlmod, DLAUXCTRL_GET_TEXTBASE);
			if (bases->deb_dbase == NULL)
				bases->deb_dbase = dlauxctrl(dlmod, DLAUXCTRL_GET_DATABASE);
			dlunlocksection(eh_frame_sect);
			return result;
		}
	}
	dlunlocksection(eh_frame_sect);
no_dl_info:

	/* If that failed, search through auxillary information given by `__register_frame_info_bases()' */
	result = NULL;
	register_frame_aux_read();
	SLIST_FOREACH (obj, &register_frame_aux_list, ro_link) {
		bases->deb_tbase = obj->ro_tbase;
		bases->deb_dbase = obj->ro_dbase;
		if (obj->ro_isarray) {
			size_t i;
			for (i = 0;; ++i) {
				rf_fde const *eh_frame;
				eh_frame = obj->ro_eh_frame_array[i];
				if (!eh_frame)
					break;
				result = fde_locate_pc(pc, (byte_t const *)eh_frame, (byte_t const *)-1, bases);
			}
		} else {
			result = fde_locate_pc(pc, (byte_t const *)obj->ro_eh_frame, (byte_t const *)-1, bases);
		}
		if (result != NULL) {
			register_frame_aux_endread();
			return result;
		}
	}
	register_frame_aux_endread();

	/* Nothing found :( */
	return NULL;
}

/* Exports */
DEFINE_PUBLIC_ALIAS(__register_frame_info_bases, libuw___register_frame_info_bases);
DEFINE_PUBLIC_ALIAS(__register_frame_info_table_bases, libuw___register_frame_info_table_bases);
DEFINE_PUBLIC_ALIAS(__deregister_frame_info, libuw___deregister_frame_info);
DEFINE_PUBLIC_ALIAS(_Unwind_Find_FDE, libuw__Unwind_Find_FDE);




/* Search auxiliary eh_frame sections registered via `__register_frame()'
 * and  friends for  FDE entries  containing `absolute_pc'.  Used when we
 * were unable to find FDE data through normal means. */
PRIVATE NONNULL((2)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_find_rf)(void const *absolute_pc,
                                         unwind_fde_t *__restrict result) {
	unwind_errno_t error = UNWIND_NO_FRAME;
	struct rf_object *obj;
	register_frame_aux_read();
	/* Go through all explicitly registered register-frame objects
	 * and see if one of them happens to contain the requested PC. */
	SLIST_FOREACH (obj, &register_frame_aux_list, ro_link) {
		if (obj->ro_isarray) {
			size_t i;
			for (i = 0;; ++i) {
				rf_fde const *eh_frame;
				eh_frame = obj->ro_eh_frame_array[i];
				if (!eh_frame)
					break;
				result->f_bases.ub_tbase = obj->ro_tbase;
				result->f_bases.ub_dbase = obj->ro_dbase;
				error = libuw_unwind_fde_scan((byte_t const *)eh_frame, (byte_t const *)-1,
				                              absolute_pc, result, sizeof(void *));
				if (error != UNWIND_NO_FRAME)
					goto done;
			}
		} else {
			result->f_bases.ub_tbase = obj->ro_tbase;
			result->f_bases.ub_dbase = obj->ro_dbase;
			error = libuw_unwind_fde_scan((byte_t const *)obj->ro_eh_frame, (byte_t const *)-1,
			                              absolute_pc, result, sizeof(void *));
			if (error != UNWIND_NO_FRAME)
				goto done;
		}
	}
done:
	register_frame_aux_endread();
	return error;
}


/* NOTE: In kernel-space, `libuw_unwind_fde_find()'  is
 *       in `/kos/src/kernel/core/memory/mman/driver.c' */
PRIVATE NONNULL((1, 3)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_find_new)(void *dlmod, void const *absolute_pc,
                                          unwind_fde_t *__restrict result) {
	unwind_errno_t error;
	struct dl_section *eh_frame_sect;

	/* Lock the module's .eh_frame section into memory. */
	eh_frame_sect = dllocksection(dlmod, ".eh_frame", DLLOCKSECTION_FNODATA);
	if unlikely(eh_frame_sect == NULL || eh_frame_sect->ds_data == (void *)-1) {
		/* TODO: Support for: `.eh_frame_hdr' (and its alias: `PT_GNU_EH_FRAME') */
		ERROR(err_no_section);
	}

	/* Scan the .eh_frame section of the associated module. */
	result->f_bases.ub_tbase = NULL; /* Lazily loaded */
	result->f_bases.ub_dbase = NULL; /* Lazily loaded */
	error = libuw_unwind_fde_scan((byte_t const *)eh_frame_sect->ds_data,
	                              (byte_t const *)eh_frame_sect->ds_data +
	                              /*           */ eh_frame_sect->ds_size,
	                              absolute_pc, result, sizeof(void *));
	dlunlocksection(eh_frame_sect);

	return error;
err_no_section:
	return UNWIND_NO_FRAME;
}




/* Lookup FDE information  associated with a  given program counter  position.
 * Using integration with KOS's DL extension APIs, this function automatically
 * accesses the `.eh_frame' sections of  the module associated with the  given
 * address, as well as  keep track of a  lazily allocated address-tree of  FDE
 * caches for quick (O(log2)) repeated access to an FDE located within a known
 * function. */
INTERN NONNULL((2)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_find)(void const *absolute_pc,
                                      unwind_fde_t *__restrict result) {
	struct fde_cache_entry *fce;
	void *dlmod;
	unwind_errno_t error;

	/* Try to search the FDE-cache.
	 * NOTE: To prevent deadlocks upon re-entrance, only
	 *       _try_ to acquire locks here, and ignore the
	 *       cache if we're unable to acquire them! */
	if (fde_cache_tryread()) {
		fce = fde_cache_tree_locate(fde_cache, absolute_pc);
		if (fce) {
			if likely(dlauxctrl(fce->fce_dlhand, DLAUXCTRL_MOD_NOTDESTROYED) != NULL) {
				memcpy(result, &fce->fce_fde, sizeof(unwind_fde_t));
				fde_cache_endread();
				result->f_sigframe &= ~0x80; /* 0x80 is (ab-)used as R/B-bit */
				return UNWIND_SUCCESS;
			}

			/* Module  was  deleted in  the  mean time...
			 * Try to get rid of the stale cache entry... */
			if (fde_cache_tryupgrade()) {
				fde_cache_tree_removenode(&fde_cache, fce);
				fde_cache_endwrite();
				fde_cache_entry_destroy(fce);
				goto do_lookup_fde;
			}
		}
		fde_cache_endread();
	}

do_lookup_fde:

	/* Lookup the module associated with the given program counter position. */
	dlmod = dlgethandle(absolute_pc, DLGETHANDLE_FNORMAL);
	if likely(dlmod != NULL) {
		/* Lookup through normal means (iow: via dllocksection(".eh_frame")) */
		error = libuw_unwind_fde_find_new(dlmod, absolute_pc, result);
	} else {
		error = UNWIND_NO_FRAME;
	}

	/* Lookup through auxiliary means (iow: via `__register_frame()') */
	if unlikely(error == UNWIND_NO_FRAME) {
		error = libuw_unwind_fde_find_rf(absolute_pc, result);
		if (error == UNWIND_SUCCESS) {
			/* For auxiliary frame listings,  we still need some  kind
			 * of module handle for use with the cache. Because  these
			 * types of cache entries can only be removed manually  by
			 * unregistering the  frame  listing,  it  doesn't  matter
			 * which module we  link against cache  entries. The  only
			 * thing that matters is that the module doesn't ever  get
			 * destroyed, which case easily achieve by linking against
			 * the base application. */
			dlmod = dlopen(NULL, 0);
			assert(dlmod);
		}
	}

	/* Check if we succeeded */
	if unlikely(error != UNWIND_SUCCESS)
		goto done;

	/* (try to) cache the results */
#ifndef __OPTIMIZE_SIZE__
	if unlikely(!fde_cache_canwrite())
		goto done; /* Bypass malloc() if acquiring the lock would likely fail. */
#endif /* !__OPTIMIZE_SIZE__ */

	fce = (struct fde_cache_entry *)malloc(sizeof(struct fde_cache_entry)); /* XXX: malloc_nonblock? */
	if unlikely(fce == NULL)
		goto done;
	memcpy(&fce->fce_fde, result, sizeof(unwind_fde_t));
	fce->fce_dlhand = dlauxctrl(dlmod, DLAUXCTRL_MOD_WEAKINCREF);

	if unlikely(!fde_cache_trywrite()) {
destroy_new_fce:
		fde_cache_entry_destroy(fce);
		goto done;
	}
	if unlikely(!fde_cache_tree_tryinsert(&fde_cache, fce)) {
		struct fde_cache_entry *existing_fce;

		/* Try to remove the existing cache entry. */
		existing_fce = fde_cache_tree_rremove(&fde_cache, result->f_pcstart,
		                                      (byte_t *)result->f_pcend - 1);
		assert(existing_fce);
		if likely(dlauxctrl(fce->fce_dlhand, DLAUXCTRL_MOD_NOTDESTROYED) != NULL) {
			/* Entry isn't stale...
			 * This might happen if another thread created this entry while
			 * we  created  ours, but  after  we checked  for  another pre-
			 * existing above! */
			memcpy(result, &existing_fce->fce_fde, sizeof(unwind_fde_t));
			fde_cache_tree_insert(&fde_cache, existing_fce);
			fde_cache_endwrite();
			result->f_sigframe &= ~0x80; /* 0x80 is (ab-)used as R/B-bit */
			goto destroy_new_fce;
		}

		/* Force-insert the new cache entry. */
		fde_cache_tree_insert(&fde_cache, fce);
		fde_cache_endwrite();

		/* Destroy the (stale) old cache entry. */
		fde_cache_entry_destroy(existing_fce);
	} else {
		fde_cache_endwrite();
	}
done:
	return error;
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
INTERN NONNULL((2, 4)) unwind_errno_t CC
linuw_unwind(void const *absolute_pc,
             unwind_getreg_t reg_getter, void const *reg_getter_arg,
             unwind_setreg_t reg_setter, void *reg_setter_arg) {
	unwind_errno_t result;
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
