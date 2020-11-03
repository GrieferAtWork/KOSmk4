/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

#include "../../__stdinc.h"
#include "../compiler.h"
#include "atree.h"
#if (!defined(ATREE_ASSERT) || !defined(ATREE_ASSERTF))
#include "../__assert.h"
#endif /* !ATREE_ASSERT || !ATREE_ASSERTF */

__DECL_BEGIN

#ifndef ATREE
#ifdef __INTELLISENSE__

#define ATREE(x)    x
#define Tkey        uintptr_t
#define T           struct my_node
#define N_NODEPATH  N_NODEPATH

struct my_node {
	int                              foo;
	ATREE_NODE(struct my_node, Tkey) N_NODEPATH;
	int                              bar;
};

#endif /* __INTELLISENSE__ */
#endif /* !ATREE */

#ifndef ATREE_DEBUG
#ifndef NDEBUG
#define ATREE_DEBUG 1
#else /* !NDEBUG */
#define ATREE_DEBUG 0
#endif /* NDEBUG */
#endif /* !ATREE_DEBUG */
#ifndef ATREE_CALL
#define ATREE_CALL /* nothing */
#endif /* !ATREE_CALL */
#ifndef ATREE_NULL
#define ATREE_NULL __NULLPTR
#endif /* !ATREE_NULL */
#ifndef ATREE_FUN
#define ATREE_FUN  PRIVATE
#endif /* !ATREE_FUN */
#ifndef ATREE_IMP
#define ATREE_IMP  PRIVATE
#endif /* !ATREE_IMP */
#ifndef ATREE_ASSERT
#define ATREE_ASSERT __hybrid_assert
#endif /* !ATREE_ASSERT */
#ifndef ATREE_ASSERTF
#define ATREE_ASSERTF __hybrid_assertf
#endif /* !ATREE_ASSERTF */
#ifndef ATREE_NOTHROW
#define ATREE_NOTHROW __NOTHROW_NCX
#endif /* !ATREE_NOTHROW */
#ifdef ATREE_SINGLE
#ifndef ATREE_NODE_ADDR
#define ATREE_NODE_ADDR(x) ((x)->N_NODEPATH.a_vaddr)
#endif /* !ATREE_NODE_ADDR */
#else /* ATREE_SINGLE */
#ifndef ATREE_NODE_MIN
#define ATREE_NODE_MIN(x) ((x)->N_NODEPATH.a_vmin)
#endif /* !ATREE_NODE_MIN */
#ifndef ATREE_NODE_MAX
#define ATREE_NODE_MAX(x) ((x)->N_NODEPATH.a_vmax)
#endif /* !ATREE_NODE_MAX */
#endif /* !ATREE_SINGLE */
#ifndef ATREE_LOCAL_SEMI0
#define ATREE_LOCAL_SEMI0(Tkey)  ATREE_SEMI0(Tkey)
#endif /* !ATREE_LOCAL_SEMI0 */
#ifndef ATREE_LOCAL_LEVEL0
#define ATREE_LOCAL_LEVEL0(Tkey) ATREE_LEVEL0(Tkey)
#endif /* !ATREE_LOCAL_LEVEL0 */



#ifndef ATREE_IMPLEMENTATION_ONLY
/* Tries to insert_at the given leaf.
 * @return: true:  Successfully inserted the given leaf.
 * @return: false: The key range described by `newleaf' is already mapped. */
ATREE_FUN __ATTR_UNUSED __BOOL
ATREE_NOTHROW(ATREE_CALL ATREE(tryinsert_at))(T **__restrict proot, T *__restrict newleaf,
                                              ATREE_SEMI_T(Tkey) addr_semi,
                                              ATREE_LEVEL_T addr_level);

/* Similar to 'addrtree_tryinsert', but causes undefined behavior
 * if the key range covered by the given leaf already existed. */
ATREE_FUN __ATTR_UNUSED void
ATREE_NOTHROW(ATREE_CALL ATREE(insert_at))(T **__restrict proot, T *__restrict newleaf,
                                           ATREE_SEMI_T(Tkey) addr_semi,
                                           ATREE_LEVEL_T addr_level);

ATREE_FUN __ATTR_UNUSED T **
ATREE_NOTHROW(ATREE_CALL ATREE(pinsert_at))(T **__restrict proot, T *__restrict newleaf,
                                            ATREE_SEMI_T(Tkey) *paddr_semi,
                                            ATREE_LEVEL_T *paddr_level);

/* Returns the old '*proot' and replaces it with either its min, or max branch.
 * Special handling is performed to determine the perfect match when
 * '*proot' has both a min and a max branch. */
ATREE_FUN __ATTR_NONNULL((1)) __ATTR_UNUSED T *
ATREE_NOTHROW(ATREE_CALL ATREE(pop_at))(T **__restrict proot,
                                        ATREE_SEMI_T(Tkey) addr_semi,
                                        ATREE_LEVEL_T addr_level);

/* Remove and return the leaf associated with the given key.
 * >> This is a combination of 'plocate_at' and `pop_at' */
ATREE_FUN __ATTR_NONNULL((1)) __ATTR_UNUSED T *
ATREE_NOTHROW(ATREE_CALL ATREE(remove_at))(T **__restrict proot, Tkey key,
                                           ATREE_SEMI_T(Tkey) addr_semi,
                                           ATREE_LEVEL_T addr_level);
ATREE_FUN __ATTR_NONNULL((1)) __ATTR_UNUSED T *
ATREE_NOTHROW(ATREE_CALL ATREE(rremove_at))(T **__restrict proot,
                                            Tkey key_min, Tkey key_max,
                                            ATREE_SEMI_T(Tkey) addr_semi,
                                            ATREE_LEVEL_T addr_level);

/* Locate the leaf associated with a given `key'.
 * @return: ATREE_NULL: No leaf associated with the given `key'.
 * NOTE: 'plocate_at' will update 'addr_semi' and 'addr_level'. */
ATREE_FUN __ATTR_UNUSED T *
ATREE_NOTHROW(ATREE_CALL ATREE(locate_at))(T *root, Tkey key,
                                           ATREE_SEMI_T(Tkey) addr_semi,
                                           ATREE_LEVEL_T addr_level);
ATREE_FUN __ATTR_UNUSED T **
ATREE_NOTHROW(ATREE_CALL ATREE(plocate_at))(T **__restrict proot, Tkey key,
                                            ATREE_SEMI_T(Tkey) *__restrict paddr_semi,
                                            ATREE_LEVEL_T *__restrict paddr_level);

/* Locate the first leaf overlapping with the given range.
 * @return: ATREE_NULL: No leaf is overlapping with the given range.
 * NOTE: 'prlocate_at' will update 'addr_semi' and 'addr_level'. */
ATREE_FUN __ATTR_UNUSED T *
ATREE_NOTHROW(ATREE_CALL ATREE(rlocate_at))(T *root, Tkey key_min, Tkey key_max,
                                            ATREE_SEMI_T(Tkey) addr_semi,
                                            ATREE_LEVEL_T addr_level);
ATREE_FUN __ATTR_UNUSED T **
ATREE_NOTHROW(ATREE_CALL ATREE(prlocate_at))(T **__restrict proot, Tkey key_min, Tkey key_max,
                                             ATREE_SEMI_T(Tkey) *__restrict paddr_semi,
                                             ATREE_LEVEL_T *__restrict paddr_level);

typedef struct {
	T    *mm_min;     /* [0..1] Lowest branch. */
	T    *mm_max;     /* [0..1] Greatest branch. */
#ifdef ATREE_SINGLE
	Tkey  mm_min_min; /* == ATREE_NODE_ADDR(ni_min). */
	Tkey  mm_max_max; /* == ATREE_NODE_ADDR(ni_max). */
#else /* ATREE_SINGLE */
	Tkey  mm_min_min; /* == ATREE_NODE_MIN(ni_min). */
	Tkey  mm_max_max; /* == ATREE_NODE_MAX(ni_max). */
#endif /* !ATREE_SINGLE */
} ATREE(minmax_t);

/* Load the lowest and greatest nodes that are overlapping with the given key-range. */
ATREE_FUN __ATTR_UNUSED void
ATREE_NOTHROW(ATREE_CALL ATREE(minmaxlocate_at))(T *root, Tkey key_min, Tkey key_max,
                                                 ATREE_SEMI_T(Tkey) addr_semi,
                                                 ATREE_LEVEL_T addr_level,
                                                 ATREE(minmax_t) *__restrict result);



#ifndef ATREE_NO_CONVENIENCE
/* Convenience functions. */
__LOCAL __ATTR_UNUSED __BOOL ATREE_NOTHROW(ATREE_CALL ATREE(tryinsert))(T **__restrict proot, T *__restrict newleaf) { return ATREE(tryinsert_at)(proot, newleaf, ATREE_LOCAL_SEMI0(Tkey), ATREE_LOCAL_LEVEL0(Tkey)); }
__LOCAL __ATTR_UNUSED void ATREE_NOTHROW(ATREE_CALL ATREE(insert))(T **__restrict proot, T *__restrict newleaf) { ATREE(insert_at)(proot, newleaf, ATREE_LOCAL_SEMI0(Tkey), ATREE_LOCAL_LEVEL0(Tkey)); }
__LOCAL __ATTR_UNUSED __ATTR_NONNULL((1)) T *ATREE_NOTHROW(ATREE_CALL ATREE(pop))(T **__restrict proot) { return ATREE(pop_at)(proot, ATREE_LOCAL_SEMI0(Tkey), ATREE_LOCAL_LEVEL0(Tkey)); }
__LOCAL __ATTR_UNUSED __ATTR_NONNULL((1)) T *ATREE_NOTHROW(ATREE_CALL ATREE(remove))(T **__restrict proot, Tkey key) { return ATREE(remove_at)(proot, key, ATREE_LOCAL_SEMI0(Tkey), ATREE_LOCAL_LEVEL0(Tkey)); }
__LOCAL __ATTR_UNUSED T *ATREE_NOTHROW(ATREE_CALL ATREE(locate))(T *root, Tkey key) { return ATREE(locate_at)(root, key, ATREE_LOCAL_SEMI0(Tkey), ATREE_LOCAL_LEVEL0(Tkey)); }
__LOCAL __ATTR_UNUSED T *ATREE_NOTHROW(ATREE_CALL ATREE(rlocate))(T *root, Tkey key_min, Tkey key_max) { return ATREE(rlocate_at)(root, key_min, key_max, ATREE_LOCAL_SEMI0(Tkey), ATREE_LOCAL_LEVEL0(Tkey)); }
__LOCAL __ATTR_UNUSED __ATTR_NONNULL((1)) T *ATREE_NOTHROW(ATREE_CALL ATREE(rremove))(T **__restrict proot, Tkey key_min, Tkey key_max) { return ATREE(rremove_at)(proot, key_min, key_max, ATREE_LOCAL_SEMI0(Tkey), ATREE_LOCAL_LEVEL0(Tkey)); }
__LOCAL __ATTR_UNUSED void ATREE_NOTHROW(ATREE_CALL ATREE(minmaxlocate))(T *root, Tkey key_min, Tkey key_max, ATREE(minmax_t) *__restrict result) { ATREE(minmaxlocate_at)(root, key_min, key_max, ATREE_LOCAL_SEMI0(Tkey), ATREE_LOCAL_LEVEL0(Tkey), result); }
#endif /* !ATREE_NO_CONVENIENCE */
#endif /* !ATREE_IMPLEMENTATION_ONLY */










/* 0================================================================0 */
/* 0                         IMPLEMENTATION                         0 */
/* 0================================================================0 */
#ifndef ATREE_HEADER_ONLY

#define ATREE_PTR(key) ((uintptr_t)(key))

PRIVATE __ATTR_UNUSED void
ATREE_NOTHROW(ATREE_CALL ATREE(priv_reinsertall))(T **__restrict proot, T *__restrict insert_root,
                                                  ATREE_SEMI_T(Tkey) addr_semi, ATREE_LEVEL_T addr_level) {
	T *min_node, *max_node;
	min_node = insert_root->N_NODEPATH.a_min;
	max_node = insert_root->N_NODEPATH.a_max;
	ATREE(insert_at)(proot, insert_root, addr_semi, addr_level);
	if (min_node != ATREE_NULL)
		ATREE(priv_reinsertall)(proot, min_node, addr_semi, addr_level);
	if (max_node != ATREE_NULL)
		ATREE(priv_reinsertall)(proot, max_node, addr_semi, addr_level);
}

ATREE_IMP __ATTR_UNUSED __BOOL
ATREE_NOTHROW(ATREE_CALL ATREE(tryinsert_at))(T **__restrict proot, T *__restrict newleaf,
                                              ATREE_SEMI_T(Tkey) addr_semi, ATREE_LEVEL_T addr_level) {
	T *iter;
#ifdef ATREE_SINGLE
	ATREE_SEMI_T(Tkey) newleaf_addr;
	newleaf_addr = ATREE_NODE_ADDR(newleaf);
#define newleaf_min newleaf_addr
#define newleaf_max newleaf_addr
#else /* ATREE_SINGLE */
	ATREE_SEMI_T(Tkey) newleaf_min, newleaf_max;
	newleaf_min = ATREE_NODE_MIN(newleaf);
	newleaf_max = ATREE_NODE_MAX(newleaf);
#endif /* !ATREE_SINGLE */
again:
	/* Make sure that the given entry can truly be inserted somewhere within this branch. */
#ifndef ATREE_SINGLE
	ATREE_ASSERTF(newleaf_max >= newleaf_min,
	              "The new leaf (%p...%p) has an invalid address configuration (min(%p) < max(%p)) (addr_semi %p; level %u)",
	              ATREE_PTR(newleaf_min), ATREE_PTR(newleaf_max),
	              ATREE_PTR(newleaf_min), ATREE_PTR(newleaf_max),
	              ATREE_PTR(addr_semi), addr_level);
#endif /* !ATREE_SINGLE */
	ATREE_ASSERTF(newleaf_min >= ATREE_MAPMIN(Tkey, addr_semi, addr_level),
	              "The given leaf (%p...%p) cannot be inserted within this branch (%p < %p) (addr_semi %p; level %u)",
	              ATREE_PTR(newleaf_min), ATREE_PTR(newleaf_max),
	              ATREE_PTR(newleaf_min), ATREE_PTR(ATREE_MAPMIN(Tkey, addr_semi, addr_level)),
	              ATREE_PTR(addr_semi), addr_level);
	ATREE_ASSERTF(newleaf_max <= ATREE_MAPMAX(Tkey, addr_semi, addr_level),
	              "The given leaf (%p...%p) cannot be inserted within this branch (%p > %p) (addr_semi %p; level %u)",
	              ATREE_PTR(newleaf_min), ATREE_PTR(newleaf_max),
	              ATREE_PTR(newleaf_max), ATREE_PTR(ATREE_MAPMAX(Tkey, addr_semi, addr_level)),
	              ATREE_PTR(addr_semi), addr_level);
	if ((iter = *proot) == ATREE_NULL) {
		/* Simple case: First leaf. */
		newleaf->N_NODEPATH.a_min = ATREE_NULL;
		newleaf->N_NODEPATH.a_max = ATREE_NULL;
		*proot = newleaf;
got_it:
		ATREE_ASSERT(newleaf_min >= ATREE_MAPMIN(Tkey, addr_semi, addr_level));
		ATREE_ASSERT(newleaf_max <= ATREE_MAPMAX(Tkey, addr_semi, addr_level));
		return 1;
	}
	/* Special case: Check if the given branch overlaps with our current. */
#ifdef ATREE_SINGLE
	if (unlikely(newleaf_addr == ATREE_NODE_ADDR(iter)))
#else /* ATREE_SINGLE */
	if (unlikely(newleaf_min <= ATREE_NODE_MAX(iter) &&
	             newleaf_max >= ATREE_NODE_MIN(iter)))
#endif /* !ATREE_SINGLE */
	{
		/* ERROR: Requested key range is already covered. */
		return 0;
	}
	/* Special case: Our new leaf covers this exact branch.
	 * --> Must move the existing leaf and replace '*proot' */
#ifdef ATREE_SINGLE
	if (newleaf_addr == addr_semi)
#else /* ATREE_SINGLE */
	if (newleaf_min <= addr_semi &&
	    newleaf_max >= addr_semi)
#endif /* !ATREE_SINGLE */
	{
		/* Check if there exists some overlapping leaf and return `0' if so. */
		T *overlap;
#ifdef ATREE_SINGLE
		overlap = ATREE(locate_at)(iter,
		                           newleaf_addr,
		                           addr_semi,
		                           addr_level);
#else /* ATREE_SINGLE */
		overlap = ATREE(rlocate_at)(iter,
		                            newleaf_min,
		                            newleaf_max,
		                            addr_semi,
		                            addr_level);
#endif /* !ATREE_SINGLE */
		if (overlap)
			return 0;
#ifndef ATREE_SINGLE
		ATREE_ASSERTF(ATREE_NODE_MAX(iter) <= addr_semi ||
		              ATREE_NODE_MIN(iter) >= addr_semi,
		              "But that would mean we are overlapping...");
#endif /* !ATREE_SINGLE */
		/* Override a given branch with a new node.
		 * This is a pretty complicated process, because we
		 * can't simply shift the entire tree down one level.
		 * >> Some of the underlying branches may have been
		 *    perfect fits before (aka. addr_semi-fits), yet
		 *    if we were to shift them directly, they would
		 *    reside in invalid and unexpected locations,
		 *    causing the entire tree to break.
		 * >> Instead we must recursively re-insert_at all
		 *    underlying branches, even though that might
		 *    seem extremely inefficient. */
		newleaf->N_NODEPATH.a_min = ATREE_NULL;
		newleaf->N_NODEPATH.a_max = ATREE_NULL;
		*proot = newleaf;
		ATREE(priv_reinsertall)(proot, iter, addr_semi, addr_level);
		goto got_it;
	}
	/* We are not a perfect fit for this leaf because
	 * we're not covering its addr_semi.
	 * -> Instead, we are either located entirely below,
	 *    or entirely above the semi-point. */
	if (newleaf_max < addr_semi) {
		/* We are located below. */
		ATREE_WALKMIN(Tkey, addr_semi, addr_level);
		proot = &iter->N_NODEPATH.a_min;
	} else {
		/* We are located above. */
		ATREE_ASSERTF(newleaf_min > addr_semi,
		              "We checked above if we're covering the semi!");
		ATREE_WALKMAX(Tkey, addr_semi, addr_level);
		proot = &iter->N_NODEPATH.a_max;
	}
	goto again;
#undef newleaf_min
#undef newleaf_max
}

ATREE_IMP __ATTR_UNUSED void
ATREE_NOTHROW(ATREE_CALL ATREE(insert_at))(T **__restrict proot, T *__restrict newleaf,
                                           ATREE_SEMI_T(Tkey) addr_semi, ATREE_LEVEL_T addr_level) {
	T *iter;
#ifdef ATREE_SINGLE
	ATREE_SEMI_T(Tkey) newleaf_addr;
#define newleaf_min newleaf_addr
#define newleaf_max newleaf_addr
#else /* ATREE_SINGLE */
	ATREE_SEMI_T(Tkey) newleaf_min, newleaf_max;
#endif /* !ATREE_SINGLE */
#ifdef ATREE_SINGLE
	newleaf_addr = ATREE_NODE_ADDR(newleaf);
#else /* ATREE_SINGLE */
	newleaf_min = ATREE_NODE_MIN(newleaf);
	newleaf_max = ATREE_NODE_MAX(newleaf);
#endif /* !ATREE_SINGLE */
again:
	/* Make sure that the given entry can truly be inserted somewhere within this branch. */
#ifndef ATREE_SINGLE
	ATREE_ASSERTF(newleaf_max >= newleaf_min,
	              "The new leaf (%p...%p) has an invalid address configuration (min(%p) < max(%p)) (addr_semi %p; level %u)",
	              ATREE_PTR(newleaf_min), ATREE_PTR(newleaf_max),
	              ATREE_PTR(newleaf_min), ATREE_PTR(newleaf_max),
	              ATREE_PTR(addr_semi), addr_level);
#endif /* !ATREE_SINGLE */
	ATREE_ASSERTF(newleaf_min >= ATREE_MAPMIN(Tkey, addr_semi, addr_level),
	              "The given leaf (%p...%p) cannot be inserted within this branch (%p < %p) (addr_semi %p; level %u)",
	              ATREE_PTR(newleaf_min), ATREE_PTR(newleaf_max),
	              ATREE_PTR(newleaf_min), ATREE_PTR(ATREE_MAPMIN(Tkey, addr_semi, addr_level)),
	              ATREE_PTR(addr_semi), addr_level);
	ATREE_ASSERTF(newleaf_max <= ATREE_MAPMAX(Tkey, addr_semi, addr_level),
	              "The given leaf leaf (%p...%p) cannot be inserted within this branch (%p > %p) (addr_semi %p; level %u)",
	              ATREE_PTR(newleaf_min), ATREE_PTR(newleaf_max),
	              ATREE_PTR(newleaf_max), ATREE_PTR(ATREE_MAPMAX(Tkey, addr_semi, addr_level)),
	              ATREE_PTR(addr_semi), addr_level);
	if ((iter = *proot) == ATREE_NULL) {
		/* Simple case: First leaf. */
		newleaf->N_NODEPATH.a_min = ATREE_NULL;
		newleaf->N_NODEPATH.a_max = ATREE_NULL;
		*proot = newleaf;
got_it:
		ATREE_ASSERT(newleaf_min >= ATREE_MAPMIN(Tkey, addr_semi, addr_level));
		ATREE_ASSERT(newleaf_max <= ATREE_MAPMAX(Tkey, addr_semi, addr_level));
		return;
	}
	/* Special case: Check if the given branch overlaps with our current. */
#ifndef ATREE_SINGLE
	ATREE_ASSERTF(!(newleaf_min <= ATREE_NODE_MAX(iter) &&
	                newleaf_max >= ATREE_NODE_MIN(iter)),
	              "ERROR: Requested key range %p...%p is already covered by %p...%p",
	              ATREE_PTR(newleaf_min),
	              ATREE_PTR(newleaf_max),
	              ATREE_PTR(ATREE_NODE_MIN(iter)),
	              ATREE_PTR(ATREE_NODE_MAX(iter)));
#endif /* !ATREE_SINGLE */
	/* Special case: Our new leaf covers this exact branch.
	 * --> Must move the existing leaf and replace '*proot' */
#ifdef ATREE_SINGLE
	if (newleaf_addr == addr_semi)
#else /* ATREE_SINGLE */
	if (newleaf_min <= addr_semi &&
	    newleaf_max >= addr_semi)
#endif /* !ATREE_SINGLE */
	{
#ifndef ATREE_SINGLE
		ATREE_ASSERTF(ATREE_NODE_MAX(iter) <= addr_semi ||
		              ATREE_NODE_MIN(iter) >= addr_semi,
		              "But that would mean we are overlapping...");
#endif /* !ATREE_SINGLE */
		/* Override a given branch with a new node.
		 * This is a pretty complicated process, because we
		 * can't simply shift the entire tree down one level.
		 * >> Some of the underlying branches may have been
		 *    perfect fits before (aka. addr_semi-fits), yet
		 *    if we were to shift them directly, they would
		 *    reside in invalid and unexpected locations,
		 *    causing the entire tree to break.
		 * >> Instead we must recursively re-insert_at all
		 *    underlying branches, even though that might
		 *    seem extremely inefficient. */
		newleaf->N_NODEPATH.a_min = ATREE_NULL;
		newleaf->N_NODEPATH.a_max = ATREE_NULL;
		*proot = newleaf;
		ATREE(priv_reinsertall)(proot, iter, addr_semi, addr_level);
		goto got_it;
	}
	/* We are not a perfect fit for this leaf because
	 * we're not covering its addr_semi.
	 * -> Instead, we are either located entirely below,
	 *    or entirely above the semi-point. */
	if (newleaf_max < addr_semi) {
		/* We are located below. */
		ATREE_WALKMIN(Tkey, addr_semi, addr_level);
		proot = &iter->N_NODEPATH.a_min;
	} else {
		/* We are located above. */
		ATREE_ASSERTF(newleaf_min > addr_semi,
		              "We checked above if we're covering the semi!");
		ATREE_WALKMAX(Tkey, addr_semi, addr_level);
		proot = &iter->N_NODEPATH.a_max;
	}
	goto again;
#undef newleaf_min
#undef newleaf_max
}

ATREE_IMP __ATTR_UNUSED T **
ATREE_NOTHROW(ATREE_CALL ATREE(pinsert_at))(T **__restrict proot, T *__restrict newleaf,
                                            ATREE_SEMI_T(Tkey) *paddr_semi, ATREE_LEVEL_T *paddr_level) {
	T *iter;
#ifdef ATREE_SINGLE
	ATREE_SEMI_T(Tkey) newleaf_addr;
#define newleaf_min newleaf_addr
#define newleaf_max newleaf_addr
#else /* ATREE_SINGLE */
	ATREE_SEMI_T(Tkey) newleaf_min, newleaf_max;
#endif /* !ATREE_SINGLE */
#ifdef ATREE_SINGLE
	newleaf_addr = ATREE_NODE_ADDR(newleaf);
#else /* ATREE_SINGLE */
	newleaf_min = ATREE_NODE_MIN(newleaf);
	newleaf_max = ATREE_NODE_MAX(newleaf);
#endif /* !ATREE_SINGLE */
again:
	/* Make sure that the given entry can truly be inserted somewhere within this branch. */
#ifndef ATREE_SINGLE
	ATREE_ASSERTF(newleaf_max >= newleaf_min,
	              "The new leaf (%p...%p) has an invalid address configuration (min(%p) < max(%p)) (semi %p; level %u)",
	              ATREE_PTR(newleaf_min), ATREE_PTR(newleaf_max),
	              ATREE_PTR(newleaf_min), ATREE_PTR(newleaf_max),
	              ATREE_PTR(*paddr_semi), *paddr_level);
#endif /* !ATREE_SINGLE */
	ATREE_ASSERTF(newleaf_min >= ATREE_MAPMIN(Tkey, *paddr_semi, *paddr_level),
	              "The given leaf (%p...%p) cannot be inserted within this branch (%p < %p) (addr_semi %p; level %u)",
	              ATREE_PTR(newleaf_min), ATREE_PTR(newleaf_max),
	              ATREE_PTR(newleaf_min), ATREE_PTR(ATREE_MAPMIN(Tkey, *paddr_semi, *paddr_level)),
	              ATREE_PTR(*paddr_semi), *paddr_level);
	ATREE_ASSERTF(newleaf_max <= ATREE_MAPMAX(Tkey, *paddr_semi, *paddr_level),
	              "The given leaf (%p...%p) cannot be inserted within this branch (%p > %p) (addr_semi %p; level %u)",
	              ATREE_PTR(newleaf_min), ATREE_PTR(newleaf_max),
	              ATREE_PTR(newleaf_max), ATREE_PTR(ATREE_MAPMAX(Tkey, *paddr_semi, *paddr_level)),
	              ATREE_PTR(*paddr_semi), *paddr_level);
	if ((iter = *proot) == ATREE_NULL) {
		/* Simple case: First leaf. */
		newleaf->N_NODEPATH.a_min = ATREE_NULL;
		newleaf->N_NODEPATH.a_max = ATREE_NULL;
		*proot = newleaf;
got_it:
		ATREE_ASSERT(newleaf_min >= ATREE_MAPMIN(Tkey, *paddr_semi, *paddr_level));
		ATREE_ASSERT(newleaf_max <= ATREE_MAPMAX(Tkey, *paddr_semi, *paddr_level));
		return proot;
	}
	ATREE_ASSERT(iter != iter->N_NODEPATH.a_min);
	ATREE_ASSERT(iter != iter->N_NODEPATH.a_max);
	/* Special case: Check if the given branch overlaps with our current. */
#ifndef ATREE_SINGLE
	ATREE_ASSERTF(!(newleaf_min <= ATREE_NODE_MAX(iter) &&
	                newleaf_max >= ATREE_NODE_MIN(iter)),
	              "ERROR: Requested key range %p...%p is already covered by %p...%p",
	              ATREE_PTR(newleaf_min),
	              ATREE_PTR(newleaf_max),
	              ATREE_PTR(ATREE_NODE_MIN(iter)),
	              ATREE_PTR(ATREE_NODE_MAX(iter)));
#endif /* !ATREE_SINGLE */
	/* Special case: Our new leaf covers this exact branch.
	 * --> Must move the existing leaf and replace '*proot' */
#ifdef ATREE_SINGLE
	if (newleaf_addr == *paddr_semi)
#else /* ATREE_SINGLE */
	if (newleaf_min <= *paddr_semi &&
	    newleaf_max >= *paddr_semi)
#endif /* !ATREE_SINGLE */
	{
#ifndef ATREE_SINGLE
		ATREE_ASSERTF(ATREE_NODE_MAX(iter) <= *paddr_semi ||
		              ATREE_NODE_MIN(iter) >= *paddr_semi,
		              "But that would mean we are overlapping...");
#endif /* !ATREE_SINGLE */
		/* Override a given branch with a new node.
		 * This is a pretty complicated process, because we
		 * can't simply shift the entire tree down one level.
		 * >> Some of the underlying branches may have been
		 *    perfect fits before (aka. addr_semi-fits), yet
		 *    if we were to shift them directly, they would
		 *    reside in invalid and unexpected locations,
		 *    causing the entire tree to break.
		 * >> Instead we must recursively re-insert_at all
		 *    underlying branches, even though that might
		 *    seem extremely inefficient. */
		newleaf->N_NODEPATH.a_min = ATREE_NULL;
		newleaf->N_NODEPATH.a_max = ATREE_NULL;
		*proot = newleaf;
		ATREE(priv_reinsertall)(proot, iter, *paddr_semi, *paddr_level);
		goto got_it;
	}
	/* We are not a perfect fit for this leaf because
	 * we're not covering its addr_semi.
	 * -> Instead, we are either located entirely below,
	 *    or entirely above the semi-point. */
	if (newleaf_max < *paddr_semi) {
		/* We are located below. */
		ATREE_WALKMIN(Tkey, *paddr_semi, *paddr_level);
		proot = &iter->N_NODEPATH.a_min;
	} else {
		/* We are located above. */
		ATREE_ASSERTF(newleaf_min > *paddr_semi,
		              "We checked above if we're covering the semi!");
		ATREE_WALKMAX(Tkey, *paddr_semi, *paddr_level);
		proot = &iter->N_NODEPATH.a_max;
	}
	goto again;
#undef newleaf_min
#undef newleaf_max
}

ATREE_IMP __ATTR_UNUSED __ATTR_NONNULL((1)) T *
ATREE_NOTHROW(ATREE_CALL ATREE(pop_at))(T **__restrict proot,
                                        ATREE_SEMI_T(Tkey) addr_semi,
                                        ATREE_LEVEL_T addr_level) {
	T *root;
	root = *proot;
	*proot = ATREE_NULL;
	if (root->N_NODEPATH.a_min != ATREE_NULL)
		ATREE(priv_reinsertall)(proot, root->N_NODEPATH.a_min, addr_semi, addr_level);
	if (root->N_NODEPATH.a_max != ATREE_NULL)
		ATREE(priv_reinsertall)(proot, root->N_NODEPATH.a_max, addr_semi, addr_level);
	return root;
}

ATREE_IMP __ATTR_UNUSED __ATTR_NONNULL((1)) T *
ATREE_NOTHROW(ATREE_CALL ATREE(remove_at))(T **__restrict proot, Tkey key,
                                           ATREE_SEMI_T(Tkey) addr_semi,
                                           ATREE_LEVEL_T addr_level) {
	T **remove_head;
	remove_head = ATREE(plocate_at)(proot, key, &addr_semi, &addr_level);
	return remove_head != ATREE_NULL
	       ? ATREE(pop_at)(remove_head, addr_semi, addr_level)
	       : ATREE_NULL;
}

ATREE_IMP __ATTR_UNUSED __ATTR_NONNULL((1)) T *
ATREE_NOTHROW(ATREE_CALL ATREE(rremove_at))(T **__restrict proot,
                                            Tkey key_min, Tkey key_max,
                                            ATREE_SEMI_T(Tkey) addr_semi,
                                            ATREE_LEVEL_T addr_level) {
	T **remove_head;
	remove_head = ATREE(prlocate_at)(proot, key_min, key_max, &addr_semi, &addr_level);
	return remove_head != ATREE_NULL
	       ? ATREE(pop_at)(remove_head, addr_semi, addr_level)
	       : ATREE_NULL;
}

ATREE_IMP __ATTR_UNUSED T *
ATREE_NOTHROW(ATREE_CALL ATREE(locate_at))(T *root, Tkey key,
                                           ATREE_SEMI_T(Tkey) addr_semi,
                                           ATREE_LEVEL_T addr_level) {
	/* addr_semi is the center point splitting the max
	 * ranges of the underlying sb_min/sb_max branches. */
	while (root != ATREE_NULL) {
#if ATREE_DEBUG
		{ /* Assert that the current branch has a valid min/max key range. */
			Tkey addr_min = ATREE_MAPMIN(Tkey, addr_semi, addr_level);
			Tkey addr_max = ATREE_MAPMAX(Tkey, addr_semi, addr_level);
#ifdef ATREE_SINGLE
			ATREE_ASSERTF(ATREE_NODE_ADDR(root) >= addr_min,
			              "Unexpected branch min key (%p < %p; max: %p; looking for %p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(addr_min),
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(key),
			              ATREE_PTR(addr_semi), addr_level);
			ATREE_ASSERTF(ATREE_NODE_ADDR(root) <= addr_max,
			              "Unexpected branch max key (%p > %p; min: %p; looking for %p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(addr_max),
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(key),
			              ATREE_PTR(addr_semi), addr_level);
#else /* ATREE_SINGLE */
			ATREE_ASSERTF(ATREE_NODE_MIN(root) <= ATREE_NODE_MAX(root),
			              "Branch has invalid min/max configuration (min(%p) > max(%p)) (semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_MIN(root)),
			              ATREE_PTR(ATREE_NODE_MAX(root)),
			              ATREE_PTR(addr_semi), addr_level);
			ATREE_ASSERTF(ATREE_NODE_MIN(root) >= addr_min,
			              "Unexpected branch min key (%p < %p; max: %p; looking for %p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_MIN(root)), ATREE_PTR(addr_min),
			              ATREE_PTR(ATREE_NODE_MAX(root)), ATREE_PTR(key),
			              ATREE_PTR(addr_semi), addr_level);
			ATREE_ASSERTF(ATREE_NODE_MAX(root) <= addr_max,
			              "Unexpected branch max key (%p > %p; min: %p; looking for %p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_MAX(root)), ATREE_PTR(addr_max),
			              ATREE_PTR(ATREE_NODE_MIN(root)), ATREE_PTR(key),
			              ATREE_PTR(addr_semi), addr_level);
#endif /* !ATREE_SINGLE */
		}
#endif /* ATREE_DEBUG */
		/* Check if the given key lies within this branch. */
#ifdef ATREE_SINGLE
		if (key == ATREE_NODE_ADDR(root))
			break;
#else /* ATREE_SINGLE */
		if (key >= ATREE_NODE_MIN(root) &&
		    key <= ATREE_NODE_MAX(root))
			break;
#endif /* !ATREE_SINGLE */
		ATREE_ASSERT(addr_level != (ATREE_LEVEL_T)-1);
		if (key < addr_semi) {
			/* Continue with min-branch */
			ATREE_WALKMIN(Tkey, addr_semi, addr_level);
			root = root->N_NODEPATH.a_min;
		} else {
			/* Continue with max-branch */
			ATREE_WALKMAX(Tkey, addr_semi, addr_level);
			root = root->N_NODEPATH.a_max;
		}
	}
	return root;
}

ATREE_IMP __ATTR_UNUSED T **
ATREE_NOTHROW(ATREE_CALL ATREE(plocate_at))(T **__restrict proot, Tkey key,
                                            ATREE_SEMI_T(Tkey) *__restrict paddr_semi,
                                            ATREE_LEVEL_T *__restrict paddr_level) {
	T *root;
	ATREE_SEMI_T(Tkey) addr_semi = *paddr_semi;
	ATREE_LEVEL_T addr_level = *paddr_level;
	/* addr_semi is the center point splitting the max
	 * ranges of the underlying sb_min/sb_max branches. */
	while ((root = *proot) != ATREE_NULL) {
#if ATREE_DEBUG
		{ /* Assert that the current branch has a valid min/max key range. */
			Tkey addr_min = ATREE_MAPMIN(Tkey, addr_semi, addr_level);
			Tkey addr_max = ATREE_MAPMAX(Tkey, addr_semi, addr_level);
#ifdef ATREE_SINGLE
			ATREE_ASSERTF(ATREE_NODE_ADDR(root) >= addr_min,
			              "Unexpected branch min key (%p < %p; max: %p; looking for %p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(addr_min),
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(key),
			              ATREE_PTR(addr_semi), addr_level);
			ATREE_ASSERTF(ATREE_NODE_ADDR(root) <= addr_max,
			              "Unexpected branch max key (%p > %p; min: %p; looking for %p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(addr_max),
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(key),
			              ATREE_PTR(addr_semi), addr_level);
#else /* ATREE_SINGLE */
			ATREE_ASSERTF(ATREE_NODE_MIN(root) <= ATREE_NODE_MAX(root),
			              "Branch has invalid min/max configuration (min(%p) > max(%p)) (semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_MIN(root)),
			              ATREE_PTR(ATREE_NODE_MAX(root)),
			              ATREE_PTR(addr_semi), addr_level);
			ATREE_ASSERTF(ATREE_NODE_MIN(root) >= addr_min,
			              "Unexpected branch min key (%p < %p; max: %p; looking for %p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_MIN(root)), ATREE_PTR(addr_min),
			              ATREE_PTR(ATREE_NODE_MAX(root)), ATREE_PTR(key),
			              ATREE_PTR(addr_semi), addr_level);
			ATREE_ASSERTF(ATREE_NODE_MAX(root) <= addr_max,
			              "Unexpected branch max key (%p > %p; min: %p; looking for %p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_MAX(root)), ATREE_PTR(addr_max),
			              ATREE_PTR(ATREE_NODE_MIN(root)), ATREE_PTR(key),
			              ATREE_PTR(addr_semi), addr_level);
#endif /* !ATREE_SINGLE */
		}
#endif /* ATREE_DEBUG */
		/* Check if the given key lies within this branch. */
#ifdef ATREE_SINGLE
		if (key == ATREE_NODE_ADDR(root))
#else /* ATREE_SINGLE */
		if (key >= ATREE_NODE_MIN(root) &&
		    key <= ATREE_NODE_MAX(root))
#endif /* !ATREE_SINGLE */
		{
			*paddr_semi  = addr_semi;
			*paddr_level = addr_level;
			return proot;
		}
		ATREE_ASSERTF(addr_level != (ATREE_LEVEL_T)-1,
		              "proot      = %p\n"
		              "*proot     = %p\n"
		              "key        = %p\n"
		              "addr_semi  = %p\n",
		              proot, *proot,
		              ATREE_PTR(key),
		              ATREE_PTR(addr_semi));
		if (key < addr_semi) {
			/* Continue with min-branch */
			ATREE_WALKMIN(Tkey, addr_semi, addr_level);
			proot = &root->N_NODEPATH.a_min;
		} else {
			/* Continue with max-branch */
			ATREE_WALKMAX(Tkey, addr_semi, addr_level);
			proot = &root->N_NODEPATH.a_max;
		}
	}
	return ATREE_NULL;
}

ATREE_IMP __ATTR_UNUSED T *
ATREE_NOTHROW(ATREE_CALL ATREE(rlocate_at))(T *root, Tkey key_min, Tkey key_max,
                                            ATREE_SEMI_T(Tkey) addr_semi,
                                            ATREE_LEVEL_T addr_level) {
	/* addr_semi is the center point splitting the max
	 * ranges of the underlying sb_min/sb_max branches. */
	while (root != ATREE_NULL) {
#if ATREE_DEBUG
		{ /* Assert that the current branch has a valid min/max key range. */
			Tkey addr_min = ATREE_MAPMIN(Tkey, addr_semi, addr_level);
			Tkey addr_max = ATREE_MAPMAX(Tkey, addr_semi, addr_level);
#ifdef ATREE_SINGLE
			ATREE_ASSERTF(ATREE_NODE_ADDR(root) >= addr_min,
			              "Unexpected branch min key (%p < %p; max: %p; looking for %p...%p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(addr_min),
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(key_min), ATREE_PTR(key_max),
			              ATREE_PTR(addr_semi), addr_level);
			ATREE_ASSERTF(ATREE_NODE_ADDR(root) <= addr_max,
			              "Unexpected branch max key (%p > %p; min: %p; looking for %p...%p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(addr_max),
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(key_min), ATREE_PTR(key_max),
			              ATREE_PTR(addr_semi), addr_level);
#else /* ATREE_SINGLE */
			ATREE_ASSERTF(ATREE_NODE_MIN(root) <= ATREE_NODE_MAX(root),
			              "Branch has invalid min/max configuration (min(%p) > max(%p)) (semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_MIN(root)),
			              ATREE_PTR(ATREE_NODE_MAX(root)),
			              ATREE_PTR(addr_semi), addr_level);
			ATREE_ASSERTF(ATREE_NODE_MIN(root) >= addr_min,
			              "Unexpected branch min key (%p < %p; max: %p; looking for %p...%p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_MIN(root)), ATREE_PTR(addr_min),
			              ATREE_PTR(ATREE_NODE_MAX(root)), ATREE_PTR(key_min), ATREE_PTR(key_max),
			              ATREE_PTR(addr_semi), addr_level);
			ATREE_ASSERTF(ATREE_NODE_MAX(root) <= addr_max,
			              "Unexpected branch max key (%p > %p; min: %p; looking for %p...%p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_MAX(root)), ATREE_PTR(addr_max),
			              ATREE_PTR(ATREE_NODE_MIN(root)), ATREE_PTR(key_min), ATREE_PTR(key_max),
			              ATREE_PTR(addr_semi), addr_level);
#endif /* !ATREE_SINGLE */
		}
#endif /* ATREE_DEBUG */
		/* Check if the given range lies within this branch. */
#ifdef ATREE_SINGLE
		if (key_min <= ATREE_NODE_ADDR(root) &&
		    key_max >= ATREE_NODE_ADDR(root))
			break;
#else /* ATREE_SINGLE */
		if (key_max >= ATREE_NODE_MIN(root) &&
		    key_min <= ATREE_NODE_MAX(root))
			break;
#endif /* !ATREE_SINGLE */
		ATREE_ASSERT(addr_level != (ATREE_LEVEL_T)-1);
		if (key_min < addr_semi) {
			if (key_max >= addr_semi) {
				T *result;
				/* Also search the max-branch */
				ATREE_SEMI_T(Tkey) temp_semi = addr_semi;
				ATREE_LEVEL_T temp_level = addr_level;
				ATREE_WALKMAX(Tkey, temp_semi, temp_level);
				result = ATREE(rlocate_at)(root->N_NODEPATH.a_max, key_min, key_max, temp_semi, temp_level);
				if (result != ATREE_NULL)
					return result;
			}
			/* Continue with min-branch */
			ATREE_WALKMIN(Tkey, addr_semi, addr_level);
			root = root->N_NODEPATH.a_min;
		} else {
			/* Continue with max-branch */
			ATREE_WALKMAX(Tkey, addr_semi, addr_level);
			root = root->N_NODEPATH.a_max;
		}
	}
	return root;
}

ATREE_IMP __ATTR_UNUSED T **
ATREE_NOTHROW(ATREE_CALL ATREE(prlocate_at))(T **__restrict proot, Tkey key_min, Tkey key_max,
                                             ATREE_SEMI_T(Tkey) *__restrict paddr_semi,
                                             ATREE_LEVEL_T *__restrict paddr_level) {
	T *root;
	ATREE_SEMI_T(Tkey) addr_semi = *paddr_semi;
	ATREE_LEVEL_T addr_level = *paddr_level;
	/* addr_semi is the center point splitting the max
	 * ranges of the underlying sb_min/sb_max branches. */
	while ((root = *proot) != ATREE_NULL) {
#if ATREE_DEBUG
		{ /* Assert that the current branch has a valid min/max key range. */
			Tkey addr_min = ATREE_MAPMIN(Tkey, addr_semi, addr_level);
			Tkey addr_max = ATREE_MAPMAX(Tkey, addr_semi, addr_level);
#ifdef ATREE_SINGLE
			ATREE_ASSERTF(ATREE_NODE_ADDR(root) >= addr_min,
			              "Unexpected branch min key (%p < %p; max: %p; looking for %p...%p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(addr_min),
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(key_min), ATREE_PTR(key_max),
			              ATREE_PTR(addr_semi), addr_level);
			ATREE_ASSERTF(ATREE_NODE_ADDR(root) <= addr_max,
			              "Unexpected branch max key (%p > %p; min: %p; looking for %p...%p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(addr_max),
			              ATREE_PTR(ATREE_NODE_ADDR(root)), ATREE_PTR(key_min), ATREE_PTR(key_max),
			              ATREE_PTR(addr_semi), addr_level);
#else /* ATREE_SINGLE */
			ATREE_ASSERTF(ATREE_NODE_MIN(root) <= ATREE_NODE_MAX(root),
			              "Branch has invalid min/max configuration (min(%p) > max(%p)) (semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_MIN(root)),
			              ATREE_PTR(ATREE_NODE_MAX(root)),
			              ATREE_PTR(addr_semi), addr_level);
			ATREE_ASSERTF(ATREE_NODE_MIN(root) >= addr_min,
			              "Unexpected branch min key (%p < %p; max: %p; looking for %p...%p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_MIN(root)), ATREE_PTR(addr_min),
			              ATREE_PTR(ATREE_NODE_MAX(root)), ATREE_PTR(key_min), ATREE_PTR(key_max),
			              ATREE_PTR(addr_semi), addr_level);
			ATREE_ASSERTF(ATREE_NODE_MAX(root) <= addr_max,
			              "Unexpected branch max key (%p > %p; min: %p; looking for %p...%p; semi %p; level %u)",
			              ATREE_PTR(ATREE_NODE_MAX(root)), ATREE_PTR(addr_max),
			              ATREE_PTR(ATREE_NODE_MIN(root)), ATREE_PTR(key_min), ATREE_PTR(key_max),
			              ATREE_PTR(addr_semi), addr_level);
#endif /* !ATREE_SINGLE */
		}
#endif /* ATREE_DEBUG */
		/* Check if the given key lies within this branch. */
#ifdef ATREE_SINGLE
		if (key_min <= ATREE_NODE_ADDR(root) &&
		    key_max >= ATREE_NODE_ADDR(root))
#else /* ATREE_SINGLE */
		if (key_max >= ATREE_NODE_MIN(root) &&
		    key_min <= ATREE_NODE_MAX(root))
#endif /* !ATREE_SINGLE */
		{
			*paddr_semi  = addr_semi;
			*paddr_level = addr_level;
			return proot;
		}
		ATREE_ASSERTF(addr_level != (ATREE_LEVEL_T)-1,
		              "proot      = %p\n"
		              "*proot     = %p\n"
		              "key_min    = %p\n"
		              "key_max    = %p\n"
		              "addr_semi  = %p\n",
		              proot, *proot,
		              ATREE_PTR(key_min),
		              ATREE_PTR(key_max),
		              ATREE_PTR(addr_semi));
		if (key_min < addr_semi) {
			if (key_max >= addr_semi) {
				T **result;
				/* Also search the max-branch */
				ATREE_SEMI_T(Tkey) temp_semi = addr_semi;
				ATREE_LEVEL_T temp_level = addr_level;
				ATREE_WALKMAX(Tkey, temp_semi, temp_level);
				result = ATREE(prlocate_at)(&root->N_NODEPATH.a_max, key_min, key_max, &temp_semi, &temp_level);
				if (result != ATREE_NULL) {
					*paddr_semi  = temp_semi;
					*paddr_level = temp_level;
					return result;
				}
			}
			/* Continue with min-branch */
			ATREE_WALKMIN(Tkey, addr_semi, addr_level);
			proot = &root->N_NODEPATH.a_min;
		} else {
			/* Continue with max-branch */
			ATREE_WALKMAX(Tkey, addr_semi, addr_level);
			proot = &root->N_NODEPATH.a_max;
		}
	}
	return ATREE_NULL;
}

ATREE_IMP __ATTR_UNUSED void
ATREE_NOTHROW(ATREE_CALL ATREE(minmaxlocate_at))(T *root, Tkey key_min, Tkey key_max,
                                                 ATREE_SEMI_T(Tkey) addr_semi,
                                                 ATREE_LEVEL_T addr_level,
                                                 ATREE(minmax_t) *__restrict result) {
	if (root == ATREE_NULL)
		return;
again:
#ifdef ATREE_SINGLE
	if (key_min <= ATREE_NODE_ADDR(root) &&
	    key_max >= ATREE_NODE_ADDR(root))
#else /* ATREE_SINGLE */
	if (key_min <= ATREE_NODE_MAX(root) &&
	    key_max >= ATREE_NODE_MIN(root))
#endif /* !ATREE_SINGLE */
	{
		/* Found a matching entry!
		 * NOTE: Since the caller already split branches
		 *       near borders, we are allowed to simply
		 *       update this entire branch! */
#ifdef ATREE_SINGLE
		if ((result->mm_min == ATREE_NULL) || ATREE_NODE_ADDR(root) < result->mm_min_min) {
			result->mm_min     = root;
			result->mm_min_min = ATREE_NODE_ADDR(root);
		}
		if ((result->mm_max == ATREE_NULL) || ATREE_NODE_ADDR(root) > result->mm_max_max) {
			result->mm_max     = root;
			result->mm_max_max = ATREE_NODE_ADDR(root);
		}
#else /* ATREE_SINGLE */
		if ((result->mm_min == ATREE_NULL) || ATREE_NODE_MIN(root) < result->mm_min_min) {
			result->mm_min     = root;
			result->mm_min_min = ATREE_NODE_MIN(root);
		}
		if ((result->mm_max == ATREE_NULL) || ATREE_NODE_MAX(root) > result->mm_max_max) {
			result->mm_max     = root;
			result->mm_max_max = ATREE_NODE_MAX(root);
		}
#endif /* !ATREE_SINGLE */
	}
	if (key_min < addr_semi && root->N_NODEPATH.a_min) {
		/* Recursively continue searching left. */
		if (key_max >= addr_semi && root->N_NODEPATH.a_max) {
			ATREE_SEMI_T(Tkey) temp_semi = addr_semi;
			ATREE_LEVEL_T temp_level = addr_level;
			ATREE_WALKMAX(Tkey, temp_semi, temp_level);
			ATREE(minmaxlocate_at)(root->N_NODEPATH.a_max,
			                       key_min,
			                       key_max,
			                       temp_semi,
			                       temp_level,
			                       result);
		}
		ATREE_WALKMIN(Tkey, addr_semi, addr_level);
		root = root->N_NODEPATH.a_min;
		goto again;
	} else if (key_max >= addr_semi && root->N_NODEPATH.a_max) {
		/* Recursively continue searching right. */
		ATREE_WALKMAX(Tkey, addr_semi, addr_level);
		root = root->N_NODEPATH.a_max;
		goto again;
	}
}


#endif /* !ATREE_HEADER_ONLY */

__DECL_END

#undef ATREE_LOCAL_LEVEL0
#undef ATREE_LOCAL_SEMI0
#undef ATREE_PTR
#undef ATREE_NODE_MAX
#undef ATREE_NODE_MIN
#undef ATREE_DEBUG
#undef ATREE_NOTHROW
#undef ATREE_ASSERTF
#undef ATREE_ASSERT
#undef ATREE_IMP
#undef ATREE_FUN
#undef ATREE_NULL
#undef ATREE_CALL
#undef N_NODEPATH
#undef T
#undef Tkey
#undef ATREE

