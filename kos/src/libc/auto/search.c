/* HASH CRC-32:0x88d8b256 */
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
#ifndef GUARD_LIBC_AUTO_SEARCH_C
#define GUARD_LIBC_AUTO_SEARCH_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "search.h"
#include "../user/stdlib.h"
#include "../user/string.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> insque(3)
 * Insert ELEM into a doubly-linked list, after PREV */
INTERN ATTR_SECTION(".text.crt.utility.search") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_insque)(void *__restrict elem,
                                  void *prev) {
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
/* >> remque(3)
 * Unlink ELEM from the doubly-linked list that it is in */
INTERN ATTR_SECTION(".text.crt.utility.search") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_remque)(void *__restrict elem) {
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
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY  *table;
	__UINT32_TYPE__ size;
	__UINT32_TYPE__ filled;
};
#endif /* !__hsearch_data_defined */
#ifndef __local_htab_defined
#define __local_htab_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(htab) struct hsearch_data htab = { NULL, 0, 0 };
__NAMESPACE_LOCAL_END
#endif /* !__local_htab_defined */
/* >> hsearch(3)
 * Search for entry matching `item.key' in internal hash table.
 * If `action' is `FIND' return found entry or signal error by returning `NULL'.
 * If `action' is `ENTER' replace existing data (if any) with `item.data' */
INTERN ATTR_SECTION(".text.crt.utility.search") ENTRY *
NOTHROW_NCX(LIBCCALL libc_hsearch)(ENTRY item,
                                   ACTION action) {
	ENTRY *result;
	libc_hsearch_r(item, action, &result, &__NAMESPACE_LOCAL_SYM htab);
	return result;
}
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY  *table;
	__UINT32_TYPE__ size;
	__UINT32_TYPE__ filled;
};
#endif /* !__hsearch_data_defined */
#ifndef __local_htab_defined
#define __local_htab_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(htab) struct hsearch_data htab = { NULL, 0, 0 };
__NAMESPACE_LOCAL_END
#endif /* !__local_htab_defined */
/* >> hcreate(3)
 * Create a new hashing table which will at most contain `nel' elements */
INTERN ATTR_SECTION(".text.crt.utility.search") int
NOTHROW_NCX(LIBCCALL libc_hcreate)(size_t nel) {
	return libc_hcreate_r(nel, &__NAMESPACE_LOCAL_SYM htab);
}
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY  *table;
	__UINT32_TYPE__ size;
	__UINT32_TYPE__ filled;
};
#endif /* !__hsearch_data_defined */
#ifndef __local_htab_defined
#define __local_htab_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC_DATA(htab) struct hsearch_data htab = { NULL, 0, 0 };
__NAMESPACE_LOCAL_END
#endif /* !__local_htab_defined */
/* >> hdestroy(3)
 * Destroy current internal hashing table */
INTERN ATTR_SECTION(".text.crt.utility.search") void
NOTHROW_NCX(LIBCCALL libc_hdestroy)(void) {
	libc_hdestroy_r(&__NAMESPACE_LOCAL_SYM htab);
}
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY  *table;
	__UINT32_TYPE__ size;
	__UINT32_TYPE__ filled;
};
#endif /* !__hsearch_data_defined */
#ifndef __ENTRY_defined
#define __ENTRY_defined 1
typedef struct entry {
	char *key;
	void *data;
} ENTRY;
#endif /* !__ENTRY_defined */
#include <libc/errno.h>
/* >> hsearch_r(3)
 * Reentrant versions which can handle multiple hashing tables at the same time */
INTERN ATTR_SECTION(".text.crt.utility.search") NONNULL((3, 4)) int
NOTHROW_NCX(LIBCCALL libc_hsearch_r)(ENTRY item,
                                     ACTION action,
                                     ENTRY **retval,
                                     struct hsearch_data *htab) {
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
	if (action == 1) {
		if (htab->filled == htab->size) {
#ifdef ENOMEM
			__libc_seterrno(ENOMEM);
#endif /* ENOMEM */
			*retval = NULL;
			return 0;
		}
		((entry_type *)htab->table)[idx].used  = hval;
		((entry_type *)htab->table)[idx].entry = item;
		++htab->filled;
		*retval = &((entry_type *)htab->table)[idx].entry;
		return 1;
	}
#ifdef ESRCH
	__libc_seterrno(ESRCH);
#endif /* ESRCH */
	*retval = NULL;
	return 0;
}
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY  *table;
	__UINT32_TYPE__ size;
	__UINT32_TYPE__ filled;
};
#endif /* !__hsearch_data_defined */
#ifndef __ENTRY_defined
#define __ENTRY_defined 1
typedef struct entry {
	char *key;
	void *data;
} ENTRY;
#endif /* !__ENTRY_defined */
#include <hybrid/limitcore.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* For the used double hash method the table size has to be a prime. To
 * correct the user given table size we need a prime test. This trivial
 * algorithm is adequate because
 * a) the code is (most probably) called a few times per program run and
 * b)  the  number is  small  because the  table  must fit  in  the core */
__LOCAL_LIBC(isprime) ATTR_CONST int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(isprime))(unsigned int number) {
	/* no even number will be passed */
	for (unsigned int div = 3; div <= number / div; div += 2) {
		if (number % div == 0)
			return 0;
	}
	return 1;
}
__NAMESPACE_LOCAL_END
/* >> hcreate_r(3) */
INTERN ATTR_SECTION(".text.crt.utility.search") int
NOTHROW_NCX(LIBCCALL libc_hcreate_r)(size_t nel,
                                     struct hsearch_data *htab) {
	typedef struct {
		unsigned int used;
		ENTRY        entry;
	} entry_type;
	if (htab == NULL) {
#ifdef EINVAL
		__libc_seterrno(EINVAL);
#endif /* EINVAL */
		return 0;
	}
	if (htab->table != NULL)
		return 0;
	if (nel < 3)
		nel = 3;
	for (nel |= 1; ; nel += 2) {
		if (UINT_MAX - 2 < nel) {
#ifdef ENOMEM
			__libc_seterrno(ENOMEM);
#endif /* ENOMEM */
			return 0;
		}
		if (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprime)(nel))
			break;
	}
	htab->size   = nel;
	htab->filled = 0;
	htab->table  = (struct _ENTRY *)libc_calloc(htab->size + 1, sizeof(entry_type));
	if (htab->table == NULL)
		return 0;
	return 1;
}
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY  *table;
	__UINT32_TYPE__ size;
	__UINT32_TYPE__ filled;
};
#endif /* !__hsearch_data_defined */
#include <libc/errno.h>
/* >> hdestroy_r(3) */
INTERN ATTR_SECTION(".text.crt.utility.search") void
NOTHROW_NCX(LIBCCALL libc_hdestroy_r)(struct hsearch_data *htab) {
	if (htab == NULL) {
#ifdef EINVAL
		__libc_seterrno(EINVAL);
#endif /* EINVAL */
		return;
	}
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	libc_free(htab->table);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	htab->table = NULL;
}
__NAMESPACE_LOCAL_BEGIN
/* Possibly  "split" a node with two red  successors, and/or fix up two red
 * edges in a  row. `rootp' is  a pointer  to the lowest  node we  visited,
 * `parentp' and `gparentp' pointers  to its parent/grandparent. `p_r'  and
 * `gp_r' contain the comparison values that determined which way was taken
 * in  the tree to reach `rootp'. `mode' is  1 if we need not do the split,
 * but must check for two red edges between `gparentp' and `rootp' */
__LOCAL_LIBC(maybe_split_for_insert) NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(maybe_split_for_insert))(void **rootp, /*nullable*/ void **parentp,
                                                                    void **gparentp, int p_r, int gp_r, int mode) {
	typedef struct __node_struct {
		void const           *key;
		struct __node_struct *left_node;
		struct __node_struct *right_node;
		__UINTPTR_TYPE__      is_red;
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
__NAMESPACE_LOCAL_END
/* >> tsearch(3)
 * Search for an entry matching the given `key' in the tree
 * pointed to by `*rootp' and insert a new element if not found */
INTERN ATTR_SECTION(".text.crt.utility.search") NONNULL((3)) void *
NOTHROW_NCX(LIBCCALL libc_tsearch)(void const *key,
                                   void **vrootp,
                                   __compar_fn_t compar) {
	typedef struct __node_struct {
		void const           *key;
		struct __node_struct *left_node;
		struct __node_struct *right_node;
		__UINTPTR_TYPE__      is_red;
	} *node;
	node q, root;
	node *parentp = NULL, *gparentp = NULL;
	node *rootp = (node *)vrootp;
	node *nextp;
	int r = 0, p_r = 0, gp_r = 0;
	if (rootp == NULL)
		return NULL;
	root = *rootp;
	if (root != NULL)
		root->is_red = 0;
	nextp = rootp;
	while (*nextp != NULL) {
		root = *rootp;
		r = (*compar)(key, root->key);
		if (r == 0)
			return root;
		__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(maybe_split_for_insert)((void **)rootp,
		                                                                (void **)parentp,
		                                                                (void **)gparentp,
		                                                                p_r, gp_r, 0);
		nextp = r < 0 ? &root->left_node
		              : &root->right_node;
		if (*nextp == NULL)
			break;
		gparentp = parentp;
		parentp = rootp;
		rootp = nextp;
		gp_r = p_r;
		p_r = r;
	}
	q = (node)libc_malloc(sizeof(struct __node_struct));
	if (q != NULL) {
		*nextp = q;
		q->key = key;
		q->is_red = 1;
		q->left_node = NULL;
		q->right_node = NULL;
		if (nextp != rootp) {
			__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(maybe_split_for_insert)((void **)nextp,
			                                                                (void **)rootp,
			                                                                (void **)parentp,
			                                                                r, p_r, 1);
		}
	}
	return q;
}
/* >> tfind(3)
 * Search for an entry matching the given `key' in the tree pointed
 * to by `*rootp'. If no matching entry is available return `NULL' */
INTERN ATTR_SECTION(".text.crt.utility.search") NONNULL((3)) void *
NOTHROW_NCX(LIBCCALL libc_tfind)(void const *key,
                                 void *const *vrootp,
                                 __compar_fn_t compar) {
	typedef struct __node_struct {
		void const           *key;
		struct __node_struct *left_node;
		struct __node_struct *right_node;
		__UINTPTR_TYPE__      is_red;
	} *node;
	node root, *rootp = (node *)vrootp;
	if (rootp == NULL)
		return NULL;
	while ((root = *rootp) != NULL) {
		int r = (*compar)(key, root->key);
		if (r == 0)
			return root;
		rootp = r < 0 ? &root->left_node
		              : &root->right_node;
	}
	return NULL;
}
#include <hybrid/typecore.h>
#include <parts/malloca.h>
/* >> tdelete(3)
 * Remove the element matching `key' from the tree pointed to by `*rootp' */
INTERN ATTR_SECTION(".text.crt.utility.search") NONNULL((3)) void *
NOTHROW_NCX(LIBCCALL libc_tdelete)(void const *__restrict key,
                                   void **__restrict vrootp,
                                   __compar_fn_t compar) {
	typedef struct __node_struct {
		void const           *key;
		struct __node_struct *left_node;
		struct __node_struct *right_node;
		__UINTPTR_TYPE__      is_red;
	} *node;
	node p, q, r, retval;
	node root, unchained;
	node *rootp = (node *)vrootp;
	int cmp, stacksize = 40, sp = 0;
	node **nodestack;
	if (rootp == NULL)
		return NULL;
	p = *rootp;
	if (p == NULL)
		return NULL;
	nodestack = (node **)__malloca(sizeof(node *) * stacksize);
	if unlikely(!nodestack)
		return NULL;
	root = p;
	while ((cmp = (*compar)(key, root->key)) != 0) {
		if (sp == stacksize) {
			node **newstack;
			stacksize += 20;
			newstack = (node **)__malloca(sizeof(node *) * stacksize);
			if unlikely(!newstack) {
				retval = NULL;
				goto done;
			}
			libc_memcpyc(newstack, nodestack, sp, sizeof(node *));
			__freea(nodestack);
			nodestack = newstack;
		}
		nodestack[sp++] = rootp;
		p = *rootp;
		rootp = cmp < 0 ? &p->left_node
		                : &p->right_node;
		root = *rootp;
		if (root == NULL)
			return NULL;
	}
	retval = p;
	root = *rootp;
	r = root->right_node;
	q = root->left_node;
	if (q == NULL || r == NULL)
		unchained = root;
	else {
		node *parentp = rootp, *up = &root->right_node;
		node upn;
		for (;;) {
			if (sp == stacksize) {
				node **newstack;
				stacksize += 20;
				newstack = (node **)__malloca(sizeof(node *) * stacksize);
				if unlikely(!newstack) {
					retval = NULL;
					goto done;
				}
				libc_memcpyc(newstack, nodestack, sp, sizeof(node *));
				__freea(nodestack);
				nodestack = newstack;
			}
			nodestack[sp++] = parentp;
			parentp = up;
			upn = *up;
			if (upn->left_node == NULL)
				break;
			up = &upn->left_node;
		}
		unchained = *up;
	}
	r = unchained->left_node;
	if (r == NULL)
		r = unchained->right_node;
	if (sp == 0)
		*rootp = r;
	else {
		q = *nodestack[sp-1];
		if (unchained == q->right_node)
			q->right_node = r;
		else
			q->left_node = r;
	}
	if (unchained != root)
		root->key = unchained->key;
	if (!unchained->is_red) {
		while (sp > 0 && (r == NULL || !r->is_red)) {
			node *pp = nodestack[sp - 1];
			p = *pp;
			if (r == p->left_node) {
				q = p->right_node;
				if (q->is_red) {
					q->is_red = 0;
					p->is_red = 1;
					p->right_node = q->left_node;
					q->left_node = p;
					*pp = q;
					nodestack[sp++] = pp = &q->left_node;
					q = p->right_node;
				}
				if ((q->left_node == NULL || !q->left_node->is_red) &&
					(q->right_node == NULL || !q->right_node->is_red)) {
					q->is_red = 1;
					r = p;
				} else {
					if (q->right_node == NULL || !q->right_node->is_red) {
						node q2 = q->left_node;
						q2->is_red = p->is_red;
						p->right_node = q2->left_node;
						q->left_node = q2->right_node;
						q2->right_node = q;
						q2->left_node = p;
						*pp = q2;
						p->is_red = 0;
					} else {
						q->is_red = p->is_red;
						p->is_red = 0;
						q->right_node->is_red = 0;
						p->right_node = q->left_node;
						q->left_node = p;
						*pp = q;
					}
					sp = 1;
					r = NULL;
				}
			} else {
				q = p->left_node;
				if (q->is_red) {
					q->is_red = 0;
					p->is_red = 1;
					p->left_node = q->right_node;
					q->right_node = p;
					*pp = q;
					nodestack[sp++] = pp = &q->right_node;
					q = p->left_node;
				}
				if ((q->right_node == NULL || !q->right_node->is_red) &&
				    (q->left_node == NULL || !q->left_node->is_red)) {
					q->is_red = 1;
					r = p;
				} else {
					if (q->left_node == NULL || !q->left_node->is_red) {
						node q2 = q->right_node;
						q2->is_red = p->is_red;
						p->left_node = q2->right_node;
						q->right_node = q2->left_node;
						q2->left_node = q;
						q2->right_node = p;
						*pp = q2;
						p->is_red = 0;
					} else {
						q->is_red = p->is_red;
						p->is_red = 0;
						q->left_node->is_red = 0;
						p->left_node = q->right_node;
						q->right_node = p;
						*pp = q;
					}
					sp = 1;
					r = NULL;
				}
			}
			--sp;
		}
		if (r != NULL)
			r->is_red = 0;
	}
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	libc_free(unchained);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
done:
	__freea(nodestack);
	return retval;
}
__NAMESPACE_LOCAL_BEGIN
/* Walk the nodes of a tree.
 * `root' is the root of the tree to be walked, `action' the function to be
 * called at each node. `level'  is the level of  `root' in the whole  tree */
__LOCAL_LIBC(trecurse) NONNULL((1, 2)) void
__LIBC_LOCAL_NAME(trecurse)(void const *root, __action_fn_t action, int level) {
	void *l, *r;
	l = ((void **)root)[1];
	r = ((void **)root)[2];
	if (!l && !r) {
		(*action)(root, (VISIT)3, level);
	} else {
		(*action)(root, (VISIT)0, level);
		if (l != NULL)
			trecurse(l, action, level + 1);
		(*action)(root, (VISIT)1, level);
		if (r != NULL)
			trecurse(r, action, level + 1);
		(*action)(root, (VISIT)2, level);
	}
}
__NAMESPACE_LOCAL_END
/* >> twalk(3)
 * Walk through the whole tree and call the `action' callback for every node or leaf */
INTERN ATTR_SECTION(".text.crt.utility.search") void
NOTHROW_NCX(LIBCCALL libc_twalk)(void const *root,
                                 __action_fn_t action) {
	if (root && action)
		__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(trecurse)(root, action, 0);
}
/* >> tdestroy(3)
 * Destroy the whole tree, call `freefct' for each node or leaf */
INTERN ATTR_SECTION(".text.crt.utility.search") NONNULL((2)) void
NOTHROW_NCX(LIBCCALL libc_tdestroy)(void *root,
                                    __free_fn_t freefct) {
again:
	if (root) {
		void *l, *r;
		l = ((void **)root)[1];
		r = ((void **)root)[2];
		(*freefct)(((void **)root)[0]);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
		libc_free(root);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
		if (l) {
			if (r)
				libc_tdestroy(r, freefct);
			root = l;
			goto again;
		}
		if (r) {
			root = r;
			goto again;
		}
	}
}
/* >> lfind(3)
 * Perform linear search for `key' by comparing by `compar' in an array [base, base+nmemb*size) */
INTERN ATTR_SECTION(".text.crt.utility.search") NONNULL((2, 3, 5)) void *
NOTHROW_NCX(LIBCCALL libc_lfind)(void const *key,
                                 void const *base,
                                 size_t __KOS_FIXED_CONST *nmemb,
                                 size_t size,
                                 __compar_fn_t compar) {
	size_t i, count = *nmemb;
	void const *result = base;
	for (i = 0; i < count; ++i) {
		if ((*compar)(key, result) == 0)
			return (void *)result;
		result = (byte_t *)result + size;
	}
	return NULL;
}
/* >> lsearch(3)
 * Perform linear search for `key' by comparing by `compar' function
 * in array [base, base+nmemb*size) and insert entry if not found */
INTERN ATTR_SECTION(".text.crt.utility.search") NONNULL((2, 3, 5)) void *
NOTHROW_NCX(LIBCCALL libc_lsearch)(void const *key,
                                   void *base,
                                   size_t *nmemb,
                                   size_t size,
                                   __compar_fn_t compar) {
	void *result;
	result = libc_lfind(key, base, nmemb, size, compar);
	if (result == NULL) {
		result = libc_memcpy((byte_t *)base + (*nmemb) * size, key, size);
		++(*nmemb);
	}
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(insque, libc_insque);
DEFINE_PUBLIC_ALIAS(remque, libc_remque);
DEFINE_PUBLIC_ALIAS(hsearch, libc_hsearch);
DEFINE_PUBLIC_ALIAS(hcreate, libc_hcreate);
DEFINE_PUBLIC_ALIAS(hdestroy, libc_hdestroy);
DEFINE_PUBLIC_ALIAS(hsearch_r, libc_hsearch_r);
DEFINE_PUBLIC_ALIAS(hcreate_r, libc_hcreate_r);
DEFINE_PUBLIC_ALIAS(hdestroy_r, libc_hdestroy_r);
DEFINE_PUBLIC_ALIAS(__tsearch, libc_tsearch);
DEFINE_PUBLIC_ALIAS(tsearch, libc_tsearch);
DEFINE_PUBLIC_ALIAS(__tfind, libc_tfind);
DEFINE_PUBLIC_ALIAS(tfind, libc_tfind);
DEFINE_PUBLIC_ALIAS(__tdelete, libc_tdelete);
DEFINE_PUBLIC_ALIAS(tdelete, libc_tdelete);
DEFINE_PUBLIC_ALIAS(__twalk, libc_twalk);
DEFINE_PUBLIC_ALIAS(twalk, libc_twalk);
DEFINE_PUBLIC_ALIAS(tdestroy, libc_tdestroy);
DEFINE_PUBLIC_ALIAS(lfind, libc_lfind);
DEFINE_PUBLIC_ALIAS(lsearch, libc_lsearch);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SEARCH_C */
