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
#ifndef GUARD_LIBC_USER_SEARCH_C
#define GUARD_LIBC_USER_SEARCH_C 1

#include "../api.h"
#include "search.h"
#include "malloc.h"

#include <string.h>
#include <malloca.h>
#include <parts/errno.h>
#include <hybrid/limitcore.h>

DECL_BEGIN

#undef __libc_seterrno
#define __libc_seterrno libc_seterrno



PRIVATE ATTR_SECTION(".bss.crt.utility.htab")
struct hsearch_data htab = { NULL, 0, 0 };


/*[[[start:implementation]]]*/

/*[[[head:hsearch,hash:0xe66a70b7]]]*/
/* Search for entry matching ITEM.key in internal hash table.
 * If ACTION is `FIND' return found entry or signal error by returning NULL.
 * If ACTION is `ENTER' replace existing data (if any) with ITEM.data */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.hsearch") ENTRY *
NOTHROW_NCX(LIBCCALL libc_hsearch)(ENTRY item,
                                   ACTION action)
/*[[[body:hsearch]]]*/
/*AUTO*/{
	ENTRY *result;
	libc_hsearch_r(item, action, &result, &htab);
	return result;
}
/*[[[end:hsearch]]]*/

/*[[[head:hcreate,hash:0xec5f9327]]]*/
/* Create a new hashing table which will at most contain NEL elements */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.hcreate") int
NOTHROW_NCX(LIBCCALL libc_hcreate)(size_t nel)
/*[[[body:hcreate]]]*/
/*AUTO*/{
	return libc_hcreate_r(nel, &htab);
}
/*[[[end:hcreate]]]*/

/*[[[head:hdestroy,hash:0x2648b7f8]]]*/
/* Destroy current internal hashing table */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.hdestroy") void
NOTHROW_NCX(LIBCCALL libc_hdestroy)(void)
/*[[[body:hdestroy]]]*/
/*AUTO*/{
	libc_hdestroy_r(&htab);
}
/*[[[end:hdestroy]]]*/

/*[[[head:hcreate_r,hash:0x5f2009ca]]]*/
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.hcreate_r") int
NOTHROW_NCX(LIBCCALL libc_hcreate_r)(size_t nel,
                                     struct hsearch_data *htab)
/*[[[body:hcreate_r]]]*/
/*AUTO*/{
	typedef struct {
		unsigned int used;
		ENTRY        entry;
	} entry_type;
	if (htab == NULL) {
#ifdef __EINVAL
		__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
		return 0;
	}
	if (htab->table != NULL)
		return 0;
	if (nel < 3)
		nel = 3;
	for (nel |= 1; ; nel += 2) {
		if (__UINT_MAX__ - 2 < nel) {
#ifdef __ENOMEM
			__libc_seterrno(__ENOMEM);
#endif /* __ENOMEM */
			return 0;
		}
		if (libc_isprime(nel))
			break;
	}
	htab->size   = nel;
	htab->filled = 0;
	htab->table  = (struct _ENTRY *)libc_calloc(htab->size+1, sizeof(entry_type));
	if (htab->table == NULL)
		return 0;
	return 1;
}
/*[[[end:hcreate_r]]]*/

/*[[[head:hdestroy_r,hash:0xfd902bfb]]]*/
/* Reentrant versions which can handle multiple hashing tables at the same time */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.hdestroy_r") void
NOTHROW_NCX(LIBCCALL libc_hdestroy_r)(struct hsearch_data *htab)
/*[[[body:hdestroy_r]]]*/
/*AUTO*/{
	if (htab == NULL) {
#ifdef __EINVAL
		__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
		return;
	}
	libc_free(htab->table);
	htab->table = NULL;
}
/*[[[end:hdestroy_r]]]*/

/*[[[head:tsearch,hash:0xe2603b58]]]*/
/* Search for an entry matching the given KEY in the tree
 * pointed to by *ROOTP and insert a new element if not found */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.tsearch") void *
NOTHROW_NCX(LIBCCALL libc_tsearch)(void const *key,
                                   void **vrootp,
                                   __compar_fn_t compar)
/*[[[body:tsearch]]]*/
/*AUTO*/{
	typedef struct node_struct {
		void const         *key;
		struct node_struct *left_node;
		struct node_struct *right_node;
		__UINTPTR_TYPE__    is_red;
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
		r = (*compar) (key, root->key);
		if (r == 0)
			return root;
		libc_maybe_split_for_insert((void **)rootp, (void **)parentp, (void **)gparentp, p_r, gp_r, 0);
		nextp = r < 0
			? &root->left_node
			: &root->right_node
			;
		if (*nextp == NULL)
			break;
		gparentp = parentp;
		parentp = rootp;
		rootp = nextp;
		gp_r = p_r;
		p_r = r;
	}
	q = (node)libc_malloc(sizeof(struct node_struct));
	if (q != NULL) {
		*nextp = q;
		q->key = key;
		q->is_red = 1;
		q->left_node = NULL;
		q->right_node = NULL;
		if (nextp != rootp)
			libc_maybe_split_for_insert((void **)nextp, (void **)rootp, (void **)parentp, r, p_r, 1);
	}
	return q;
}
/*[[[end:tsearch]]]*/

/*[[[head:tdelete,hash:0xd462c507]]]*/
/* Remove the element matching KEY from the tree pointed to by *ROOTP */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.tdelete") void *
NOTHROW_NCX(LIBCCALL libc_tdelete)(void const *__restrict key,
                                   void **__restrict vrootp,
                                   __compar_fn_t compar)
/*[[[body:tdelete]]]*/
/*AUTO*/{
	typedef struct node_struct {
		void const         *key;
		struct node_struct *left_node;
		struct node_struct *right_node;
		__UINTPTR_TYPE__    is_red;
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
	nodestack = (node **)malloca(sizeof(node *)*stacksize);
	if unlikely(!nodestack)
		return NULL;
	root = p;
	while ((cmp = (*compar)(key, root->key)) != 0) {
		if (sp == stacksize) {
			node **newstack;
			stacksize += 20;
			newstack = (node **)malloca(sizeof(node *)*stacksize);
			if unlikely(!newstack) {
				retval = NULL;
				goto done;
			}
			memcpy(newstack, nodestack, sp*sizeof(node *));
			freea(nodestack);
			nodestack = newstack;
		}
		nodestack[sp++] = rootp;
		p = *rootp;
		rootp = cmp < 0
			? &p->left_node
			: &p->right_node
			;
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
				newstack = (node **)malloca(sizeof(node *)*stacksize);
				if unlikely(!newstack) {
					retval = NULL;
					goto done;
				}
				memcpy(newstack, nodestack, sp*sizeof(node *));
				freea(nodestack);
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
	libc_free(unchained);
done:
	freea(nodestack);
	return retval;
}
/*[[[end:tdelete]]]*/

/*[[[head:tdestroy,hash:0xfa375074]]]*/
/* Destroy the whole tree, call FREEFCT for each node or leaf */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.utility.search.tdestroy") void
NOTHROW_NCX(LIBCCALL libc_tdestroy)(void *root,
                                    __free_fn_t freefct)
/*[[[body:tdestroy]]]*/
/*AUTO*/{
again:
	if (root) {
		void *l, *r;
		l = ((void **)root)[1];
		r = ((void **)root)[2];
		(*freefct)(((void **)root)[0]);
		libc_free(root);
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
/*[[[end:tdestroy]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x4a0c18e2]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(hsearch, libc_hsearch);
DEFINE_PUBLIC_WEAK_ALIAS(hcreate, libc_hcreate);
DEFINE_PUBLIC_WEAK_ALIAS(hdestroy, libc_hdestroy);
DEFINE_PUBLIC_WEAK_ALIAS(hcreate_r, libc_hcreate_r);
DEFINE_PUBLIC_WEAK_ALIAS(hdestroy_r, libc_hdestroy_r);
DEFINE_PUBLIC_WEAK_ALIAS(tsearch, libc_tsearch);
DEFINE_PUBLIC_WEAK_ALIAS(tdelete, libc_tdelete);
DEFINE_PUBLIC_WEAK_ALIAS(tdestroy, libc_tdestroy);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SEARCH_C */
