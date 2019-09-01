/* HASH 0x331d4b65 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_SEARCH_C
#define GUARD_LIBC_AUTO_SEARCH_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "search.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
/* Insert ELEM into a doubly-linked list, after PREV */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.insque") void
NOTHROW_NCX(LIBCCALL libc_insque)(void *__restrict elem,
                                  void *prev) {
#line 108 "kos/src/libc/magic/search.c"
	struct libc_link {
		struct libc_link *l_forw; /* [0..1] Forward link */
		struct libc_link *l_back; /* [0..1] Backward link */
	};
	if (prev) {
		struct libc_link *next;
		next = ((struct libc_link *)prev)->l_forw;
		((struct libc_link *)elem)->l_back = (struct libc_link *)prev;
		((struct libc_link *)elem)->l_forw = next;
		((struct libc_link *)prev)->l_forw = (struct libc_link *)elem;
		if (next)
			next->l_back = (struct libc_link *)elem;
	} else {
		((struct libc_link *)elem)->l_back = NULL;
		((struct libc_link *)elem)->l_forw = NULL;
	}
}

/* Unlink ELEM from the doubly-linked list that it is in */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.remque") void
NOTHROW_NCX(LIBCCALL libc_remque)(void *__restrict elem) {
#line 128 "kos/src/libc/magic/search.c"
	struct libc_link {
		struct libc_link *l_forw; /* [0..1] Forward link */
		struct libc_link *l_back; /* [0..1] Backward link */
	};
	struct libc_link *prev, *next;
	prev = ((struct libc_link *)elem)->l_back;
	next = ((struct libc_link *)elem)->l_forw;
	if (prev)
		prev->l_forw = next;
	if (next)
		next->l_back = prev;
}

/* For the used double hash method the table size has to be a prime. To
 * correct the user given table size we need a prime test.  This trivial
 * algorithm is adequate because
 * a)  the code is (most probably) called a few times per program run and
 * b)  the number is small because the table must fit in the core */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.isprime") int
NOTHROW_NCX(LIBCCALL libc_isprime)(unsigned int number) {
#line 255 "kos/src/libc/magic/search.c"
	/* no even number will be passed */
	for (unsigned int libc_div = 3; libc_div <= number / libc_div; libc_div += 2)
		if (number % libc_div == 0)
			return 0;
	return 1;
}

#include <parts/errno.h>
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.hsearch_r") int
NOTHROW_NCX(LIBCCALL libc_hsearch_r)(ENTRY item,
                                     ACTION action,
                                     ENTRY **retval,
                                     struct hsearch_data *htab) {
#line 265 "kos/src/libc/magic/search.c"
	typedef struct {
		unsigned int used;
		ENTRY        entry;
	} entry_type;
	unsigned int hval, count, idx;
	unsigned int len = libc_strlen(item.key);
	hval = count = len;
	while (count-- > 0) {
		hval <<= 4;
		hval += item.key[count];
	}
	if (hval == 0)
		++hval;
	idx = hval % htab->size + 1;
	if (((entry_type *)htab->table)[idx].used) {
		unsigned int hval2, first_idx;
		if (((entry_type *)htab->table)[idx].used == hval &&
		    libc_strcmp(item.key, ((entry_type *)htab->table)[idx].entry.key) == 0) {
			*retval = &((entry_type *)htab->table)[idx].entry;
			return 1;
		}
		hval2 = 1 + hval % (htab->size - 2);
		first_idx = idx;
		do {
			if (idx <= hval2)
				idx = htab->size + idx - hval2;
			else
				idx -= hval2;
			if (idx == first_idx)
				break;
			if (((entry_type *)htab->table)[idx].used == hval &&
			    libc_strcmp(item.key, ((entry_type *)htab->table)[idx].entry.key) == 0) {
				*retval = &((entry_type *)htab->table)[idx].entry;
				return 1;
			}
		} while (((entry_type *)htab->table)[idx].used);
	}
	if (action == ENTER) {
		if (htab->filled == htab->size) {
#ifdef __ENOMEM
			__libc_seterrno(__ENOMEM);
#endif /* __ENOMEM */
			*retval = NULL;
			return 0;
		}
		((entry_type *)htab->table)[idx].used  = hval;
		((entry_type *)htab->table)[idx].entry = item;
		++htab->filled;
		*retval = &((entry_type *)htab->table)[idx].entry;
		return 1;
	}
#ifdef __ESRCH
	__libc_seterrno(__ESRCH);
#endif /* __ESRCH */
	*retval = NULL;
	return 0;
}

/* Possibly "split" a node with two red successors, and/or fix up two red
 * edges in a row. ROOTP is a pointer to the lowest node we visited, PARENTP
 * and GPARENTP pointers to its parent/grandparent. P_R and GP_R contain the
 * comparison values that determined which way was taken in the tree to reach
 * ROOTP. MODE is 1 if we need not do the split, but must check for two red
 * edges between GPARENTP and ROOTP */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.maybe_split_for_insert") void
NOTHROW_NCX(LIBCCALL libc_maybe_split_for_insert)(void **rootp,
                                                  void **parentp,
                                                  void **gparentp,
                                                  int p_r,
                                                  int gp_r,
                                                  int mode) {
#line 390 "kos/src/libc/magic/search.c"
	typedef struct node_struct {
		void const         *key;
		struct node_struct *left_node;
		struct node_struct *right_node;
		__UINTPTR_TYPE__    is_red;
	} *node;
	node root = *(node *)rootp;
	node *rp, *lp;
	node rpn, lpn;
	rp = &root->right_node;
	rpn = root->right_node;
	lp = &root->left_node;
	lpn = root->left_node;
	if (mode == 1 || (rpn != NULL && lpn != NULL && rpn->is_red && lpn->is_red)) {
		root->is_red = 1;
		if (rpn)
			rpn->is_red = 0;
		if (lpn)
			lpn->is_red = 0;
		if (parentp != NULL && (*(node *)parentp)->is_red) {
			node gp = *((node *)gparentp);
			node p = *((node *)parentp);
			if ((p_r > 0) != (gp_r > 0)) {
				p->is_red = 1;
				gp->is_red = 1;
				root->is_red = 0;
				if (p_r < 0) {
					p->left_node = rpn;
					*rp = p;
					gp->right_node = lpn;
					*lp = gp;
				} else {
					p->right_node = lpn;
					*lp = p;
					gp->left_node = rpn;
					*rp = gp;
				}
				*(node *)gparentp = root;
			} else {
				*(node *)gparentp = p;
				p->is_red = 0;
				gp->is_red = 1;
				if (p_r < 0) {
					gp->left_node = p->right_node;
					p->right_node = gp;
				} else {
					gp->right_node = p->left_node;
					p->left_node = gp;
				}
			}
		}
	}
}

/* Search for an entry matching the given KEY in the tree pointed
 * to by *ROOTP. If no matching entry is available return NULL */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.tfind") void *
NOTHROW_NCX(LIBCCALL libc_tfind)(void const *key,
                                 void *const *vrootp,
                                 __compar_fn_t compar) {
#line 499 "kos/src/libc/magic/search.c"
	typedef struct node_struct {
		void const         *key;
		struct node_struct *left_node;
		struct node_struct *right_node;
		__UINTPTR_TYPE__    is_red;
	} *node;
	node root, *rootp = (node *)vrootp;
	if (rootp == NULL)
		return NULL;
	while ((root = *rootp) != NULL) {
		int r = (*compar)(key, root->key);
		if (r == 0)
			return root;
		rootp = r < 0
			? &root->left_node
			: &root->right_node
			;
	}
	return NULL;
}

/* Walk the nodes of a tree.
 * ROOT is the root of the tree to be walked, ACTION the function to be
 * called at each node. LEVEL is the level of ROOT in the whole tree */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.trecurse") void
NOTHROW_NCX(LIBCCALL libc_trecurse)(void const *root,
                                    __action_fn_t action,
                                    int level) {
#line 713 "kos/src/libc/magic/search.c"
	void *l, *r;
	l = ((void **)root)[1];
	r = ((void **)root)[2];
	if (!l && !r)
		(*action)(root, (VISIT)leaf, level);
	else {
		(*action)(root, (VISIT)preorder, level);
		if (l != NULL)
			libc_trecurse(l, action, level+1);
		(*action)(root, (VISIT)postorder, level);
		if (r != NULL)
			libc_trecurse(r, action, level+1);
		(*action)(root, (VISIT)endorder, level);
	}
}

/* Walk through the whole tree and call the ACTION callback for every node or leaf */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.twalk") void
NOTHROW_NCX(LIBCCALL libc_twalk)(void const *root,
                                 __action_fn_t action) {
#line 731 "kos/src/libc/magic/search.c"
	if (root && action)
		libc_trecurse(root, action, 0);
}

/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.lfind") void *
NOTHROW_NCX(LIBCCALL libc_lfind)(void const *key,
                                 void const *base,
                                 size_t *nmemb,
                                 size_t size,
                                 __compar_fn_t compar) {
#line 772 "kos/src/libc/magic/search.c"
	size_t i, count = *nmemb;
	void const *result = base;
	for (i = 0; i < count; ++i) {
		if ((*compar)(key, result) == 0)
			return (void *)result;
		result = (byte_t *)result + size;
	}
	return NULL;
}

/* Perform linear search for KEY by comparing by COMPAR function
 * in array [BASE, BASE+NMEMB*SIZE) and insert entry if not found */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.lsearch") void *
NOTHROW_NCX(LIBCCALL libc_lsearch)(void const *key,
                                   void *base,
                                   size_t *nmemb,
                                   size_t size,
                                   __compar_fn_t compar) {
#line 785 "kos/src/libc/magic/search.c"
	void *result;
	result = libc_lfind(key, base, nmemb, size, compar);
	if (result == NULL) {
		result = memcpy((byte_t *)base + (*nmemb) * size, key, size);
		++(*nmemb);
	}
	return result;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(insque, libc_insque);
DEFINE_PUBLIC_WEAK_ALIAS(remque, libc_remque);
DEFINE_PUBLIC_WEAK_ALIAS(hsearch_r, libc_hsearch_r);
DEFINE_PUBLIC_WEAK_ALIAS(tfind, libc_tfind);
DEFINE_PUBLIC_WEAK_ALIAS(twalk, libc_twalk);
DEFINE_PUBLIC_WEAK_ALIAS(lfind, libc_lfind);
DEFINE_PUBLIC_WEAK_ALIAS(lsearch, libc_lsearch);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SEARCH_C */
