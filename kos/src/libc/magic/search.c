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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(pid_t = __pid_t)]
%[default_impl_section(".text.crt.utility.search")]

%{
#include <features.h>
#include <hybrid/typecore.h>

/* Documentation taken from Glibc /usr/include/search.h */
/* Declarations for System V style searching functions.
   Copyright (C) 1995-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* Seperately, the implementation is also derived from Glibc */
/* Copyright (C) 1993-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@gnu.ai.mit.edu>, 1993.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


__SYSDECL_BEGIN

}%[push_macro @undef { preorder postorder endorder leaf VISIT }]%{

/* Action which shall be performed in the call the hsearch. */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum {
	FIND  = 0,
	ENTER = 1
} ACTION;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define FIND  FIND
#define ENTER ENTER
#else /* __COMPILER_PREFERR_ENUMS */
#define FIND  0
#define ENTER 1
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/* For tsearch */
/*[[[enum]]]*/
#ifdef __CC__
typedef enum {
	preorder  = 0,
	postorder = 1,
	endorder  = 2,
	leaf      = 3
} VISIT;
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define preorder  preorder
#define postorder postorder
#define endorder  endorder
#define leaf      leaf
#else /* __COMPILER_PREFERR_ENUMS */
#define preorder  0
#define postorder 1
#define endorder  2
#define leaf      3
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __USE_GNU
/* Prototype structure for a linked-list data structure. This
 * is the type used by the `insque' and `remque' functions. */
struct qelem {
	struct qelem *q_forw;     /* [0..1] Forward link */
	struct qelem *q_back;     /* [0..1] Backward link */
	char          q_data[1];  /* Element data */
};
#endif /* __USE_GNU */

}

@@Insert ELEM into a doubly-linked list, after PREV
void insque([[nonnull]] void *__restrict elem, void *prev) {
	struct link {
		struct link *l_forw; /* [0..1] Forward link */
		struct link *l_back; /* [0..1] Backward link */
	};
	if (prev) {
		struct link *next;
		next = ((struct link *)prev)->l_forw;
		((struct link *)elem)->l_back = (struct link *)prev;
		((struct link *)elem)->l_forw = next;
		((struct link *)prev)->l_forw = (struct link *)elem;
		if (next)
			next->l_back = (struct link *)elem;
	} else {
		((struct link *)elem)->l_back = NULL;
		((struct link *)elem)->l_forw = NULL;
	}
}

@@Unlink ELEM from the doubly-linked list that it is in
void remque([[nonnull]] void *__restrict elem) {
	struct link {
		struct link *l_forw; /* [0..1] Forward link */
		struct link *l_back; /* [0..1] Backward link */
	};
	struct link *prev, *next;
	prev = ((struct link *)elem)->l_back;
	next = ((struct link *)elem)->l_forw;
	if (prev)
		prev->l_forw = next;
	if (next)
		next->l_back = prev;
}
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%{
/* For use with hsearch(3).  */
#ifndef __COMPAR_FN_T
#define __COMPAR_FN_T 1
#ifndef ____compar_fn_t_defined
#define ____compar_fn_t_defined 1
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#endif /* !____compar_fn_t_defined */
#ifdef __USE_GNU
typedef __compar_fn_t comparison_fn_t;
#endif /* __USE_GNU */
#endif /* __COMPAR_FN_T */

#ifndef __ENTRY_defined
#define __ENTRY_defined 1
typedef struct entry {
	char *key;
	void *data;
} ENTRY;
#endif /* !__ENTRY_defined */

/* Opaque type for internal use. */
struct _ENTRY;

/* Family of hash table handling functions. The functions also
 * have reentrant counterparts ending with _r. The non-reentrant
 * functions all work on a signle internal hashing table. */

}

%[define_replacement(ENTRY = "struct entry")]
%[define_replacement(VISIT = int)]
%[define_replacement(ACTION = int)]

%[define(FIND      = 0)]
%[define(ENTER     = 1)]
%[define(preorder  = 0)]
%[define(postorder = 1)]
%[define(endorder  = 2)]
%[define(leaf      = 3)]


%[define(DEFINE_HSEARCH_DATA =
@@pp_ifndef __hsearch_data_defined@@
#define __hsearch_data_defined 1
struct _ENTRY;
struct hsearch_data {
	struct _ENTRY  *@table@;
	__UINT32_TYPE__ @size@;
	__UINT32_TYPE__ @filled@;
};
@@pp_endif@@
)]

%[define(DEFINE_HSEARCH_HTAB =
@@pp_ifndef __local_htab_defined@@
#define __local_htab_defined 1
@@push_namespace(local)@@
__LOCAL_LIBC_DATA(htab) struct hsearch_data htab = {NULL, 0, 0};
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_SEARCH_ENTRY =
@@pp_ifndef __ENTRY_defined@@
#define __ENTRY_defined 1
typedef struct entry {
	char *@key@;
	void *@data@;
} @ENTRY@;
@@pp_endif@@
)]


@@Search for entry matching ITEM.key in internal hash table.
@@If ACTION is `FIND' return found entry or signal error by returning NULL.
@@If ACTION is `ENTER' replace existing data (if any) with ITEM.data
[[impl_prefix(DEFINE_HSEARCH_DATA), impl_prefix(DEFINE_HSEARCH_HTAB)]]
[[userimpl, requires_function(hsearch_r)]]
ENTRY *hsearch(ENTRY item, ACTION action) {
	ENTRY *result;
	hsearch_r(item, action, &result, &htab);
	return result;
}

@@Create a new hashing table which will at most contain NEL elements
[[impl_prefix(DEFINE_HSEARCH_DATA), impl_prefix(DEFINE_HSEARCH_HTAB)]]
[[userimpl, requires_function(hcreate_r)]]
int hcreate(size_t nel) {
	return hcreate_r(nel, &htab);
}

@@Destroy current internal hashing table
[[impl_prefix(DEFINE_HSEARCH_DATA), impl_prefix(DEFINE_HSEARCH_HTAB)]]
[[userimpl, requires_function(hdestroy_r)]]
void hdestroy() {
	hdestroy_r(&htab);
}

%{
#ifdef __USE_GNU
/* Data type for reentrant functions.  */
#ifndef __hsearch_data_defined
#define __hsearch_data_defined 1
struct hsearch_data {
	struct _ENTRY *table;
	unsigned int   size;
	unsigned int   filled;
};
#endif /* !__hsearch_data_defined */
}

@@For the used double hash method the table size has to be a prime. To
@@correct the user given table size we need a prime test.  This trivial
@@algorithm is adequate because
@@a)  the code is (most probably) called a few times per program run and
@@b)  the number is small because the table must fit in the core
[[static, inline, nocrt, ATTR_CONST]]
int isprime(unsigned int number) {
	/* no even number will be passed */
	for (unsigned int div = 3; div <= number / div; div += 2) {
		if (number % div == 0)
			return 0;
	}
	return 1;
}

@@Reentrant versions which can handle multiple hashing tables at the same time
[[decl_prefix(struct entry;)]]
[[impl_include("<parts/errno.h>")]]
[[impl_prefix(DEFINE_HSEARCH_DATA)]]
[[impl_prefix(DEFINE_SEARCH_ENTRY)]]
int hsearch_r(ENTRY item, ACTION action,
              [[nonnull]] ENTRY **retval,
              [[nonnull]] struct hsearch_data *htab) {
	typedef struct {
		unsigned int used;
		ENTRY        entry;
	} entry_type;
	unsigned int hval, count, idx;
	unsigned int len = strlen(item.@key@);
	hval = count = len;
	while (count-- > 0) {
		hval <<= 4;
		hval += item.@key@[count];
	}
	if (hval == 0)
		++hval;
	idx = hval % htab->@size@ + 1;
	if (((entry_type *)htab->@table@)[idx].used) {
		unsigned int hval2, first_idx;
		if (((entry_type *)htab->@table@)[idx].used == hval &&
		    strcmp(item.@key@, ((entry_type *)htab->@table@)[idx].entry.@key@) == 0) {
			*retval = &((entry_type *)htab->@table@)[idx].entry;
			return 1;
		}
		hval2 = 1 + hval % (htab->@size@ - 2);
		first_idx = idx;
		do {
			if (idx <= hval2)
				idx = htab->@size@ + idx - hval2;
			else
				idx -= hval2;
			if (idx == first_idx)
				break;
			if (((entry_type *)htab->@table@)[idx].used == hval &&
			    strcmp(item.@key@, ((entry_type *)htab->@table@)[idx].entry.@key@) == 0) {
				*retval = &((entry_type *)htab->@table@)[idx].entry;
				return 1;
			}
		} while (((entry_type *)htab->@table@)[idx].used);
	}
	if (action == ENTER) {
		if (htab->@filled@ == htab->@size@) {
@@pp_ifdef ENOMEM@@
			__libc_seterrno(ENOMEM);
@@pp_endif@@
			*retval = NULL;
			return 0;
		}
		((entry_type *)htab->@table@)[idx].used  = hval;
		((entry_type *)htab->@table@)[idx].entry = item;
		++htab->@filled@;
		*retval = &((entry_type *)htab->@table@)[idx].entry;
		return 1;
	}
@@pp_ifdef ESRCH@@
	__libc_seterrno(ESRCH);
@@pp_endif@@
	*retval = NULL;
	return 0;
}

[[impl_prefix(DEFINE_HSEARCH_DATA)]]
[[impl_prefix(DEFINE_SEARCH_ENTRY)]]
[[userimpl, requires_function(calloc), doc_alias("hsearch_r")]]
[[impl_include("<hybrid/limitcore.h>", "<parts/errno.h>")]]
int hcreate_r(size_t nel, struct hsearch_data *htab) {
	typedef struct {
		unsigned int used;
		ENTRY        entry;
	} entry_type;
	if (htab == NULL) {
@@pp_ifdef EINVAL@@
		__libc_seterrno(EINVAL);
@@pp_endif@@
		return 0;
	}
	if (htab->@table@ != NULL)
		return 0;
	if (nel < 3)
		nel = 3;
	for (nel |= 1; ; nel += 2) {
		if (UINT_MAX - 2 < nel) {
@@pp_ifdef ENOMEM@@
			__libc_seterrno(ENOMEM);
@@pp_endif@@
			return 0;
		}
		if (isprime(nel))
			break;
	}
	htab->@size@   = nel;
	htab->@filled@ = 0;
	htab->@table@  = (struct _ENTRY *)calloc(htab->size+1, sizeof(entry_type));
	if (htab->@table@ == NULL)
		return 0;
	return 1;
}

[[impl_prefix(DEFINE_HSEARCH_DATA)]]
[[doc_alias("hsearch_r"), impl_include("<parts/errno.h>")]]
[[userimpl, requires_function(free)]]
void hdestroy_r(struct hsearch_data *htab) {
	if (htab == NULL) {
@@pp_ifdef EINVAL@@
		__libc_seterrno(EINVAL);
@@pp_endif@@
		return;
	}
	free(htab->@table@);
	htab->@table@ = NULL;
}
%#endif /* __USE_GNU */

%{
/* The tsearch routines are very interesting. They make many
 * assumptions about the compiler. It assumes that the first
 * field in node must be the "key" field, which points to the
 * datum. Everything depends on that. */
}


@@Possibly "split" a node with two red successors, and/or fix up two red
@@edges in a row. ROOTP is a pointer to the lowest node we visited, PARENTP
@@and GPARENTP pointers to its parent/grandparent. P_R and GP_R contain the
@@comparison values that determined which way was taken in the tree to reach
@@ROOTP. MODE is 1 if we need not do the split, but must check for two red
@@edges between GPARENTP and ROOTP
[[static, inline, nocrt]]
void maybe_split_for_insert([[nonnull]] void **rootp, [[nullable]] void **parentp,
                            /*[[if(rootp != NULL), nonnull]]*/ void **gparentp,
                            int p_r, int gp_r, int mode) {
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

%[define(DEFINE_COMPAR_FN_T =
@@pp_ifndef ____compar_fn_t_defined@@
#define ____compar_fn_t_defined 1
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
@@pp_endif@@
)]

@@Search for an entry matching the given KEY in the tree
@@pointed to by *ROOTP and insert a new element if not found
[[decl_prefix(DEFINE_COMPAR_FN_T)]]
[[userimpl, requires_function(malloc), export_alias("__tsearch")]]
void *tsearch(void const *key,
              [[nullable]] void **vrootp,
              [[nonnull]] __compar_fn_t compar) {
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
		maybe_split_for_insert((void **)rootp,
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
	q = (node)malloc(sizeof(struct __node_struct));
	if (q != NULL) {
		*nextp = q;
		q->key = key;
		q->is_red = 1;
		q->left_node = NULL;
		q->right_node = NULL;
		if (nextp != rootp) {
			maybe_split_for_insert((void **)nextp,
			                       (void **)rootp,
			                       (void **)parentp,
			                       r, p_r, 1);
		}
	}
	return q;
}

@@Search for an entry matching the given KEY in the tree pointed
@@to by *ROOTP. If no matching entry is available return NULL
[[decl_prefix(DEFINE_COMPAR_FN_T)]]
[[export_alias("__tfind")]]
void *tfind(void const *key,
            [[nullable]] void *const *vrootp,
            [[nonnull]] __compar_fn_t compar) {
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

@@Remove the element matching KEY from the tree pointed to by *ROOTP
[[decl_prefix(DEFINE_COMPAR_FN_T)]]
[[export_alias("__tdelete")]]
[[impl_include("<hybrid/typecore.h>", "<parts/malloca.h>")]]
[[userimpl, requires_function(free)]]
void *tdelete(void const *__restrict key,
              [[nullable]] void **__restrict vrootp,
              [[nonnull]] __compar_fn_t compar) {
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
			memcpyc(newstack, nodestack, sp, sizeof(node *));
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
				memcpyc(newstack, nodestack, sp, sizeof(node *));
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
	free(unchained);
done:
	__freea(nodestack);
	return retval;
}

%{
#ifndef __ACTION_FN_T
#define __ACTION_FN_T 1
typedef void (__LIBCCALL *__action_fn_t)(void const *nodep, VISIT value, int level);
#endif /* !__ACTION_FN_T */
}

@@Walk the nodes of a tree.
@@ROOT is the root of the tree to be walked, ACTION the function to be
@@called at each node. LEVEL is the level of ROOT in the whole tree
[[static, inline, nocrt]]
void trecurse([[nonnull]] void const *root,
              [[nonnull]] __action_fn_t action, int level) {
	void *l, *r;
	l = ((void **)root)[1];
	r = ((void **)root)[2];
	if (!l && !r)
		(*action)(root, (@VISIT@)@leaf@, level);
	else {
		(*action)(root, (@VISIT@)@preorder@, level);
		if (l != NULL)
			trecurse(l, action, level+1);
		(*action)(root, (@VISIT@)@postorder@, level);
		if (r != NULL)
			trecurse(r, action, level+1);
		(*action)(root, (@VISIT@)@endorder@, level);
	}
}

@@Walk through the whole tree and call the ACTION callback for every node or leaf
[[export_alias("__twalk")]]
void twalk([[nullable]] void const *root,
           [[nullable]] __action_fn_t action) {
	if (root && action)
		trecurse(root, action, 0);
}

%{
#ifdef __USE_GNU
/* Callback type for function to free a tree node.
 * If the keys are atomic data this function should do nothing.  */
typedef void (*__free_fn_t) (void *__nodep);
}

@@Destroy the whole tree, call FREEFCT for each node or leaf
[[userimpl, requires_function(free)]]
void tdestroy([[nullable]] void *root,
              [[nonnull]] __free_fn_t freefct) {
again:
	if (root) {
		void *l, *r;
		l = ((void **)root)[1];
		r = ((void **)root)[2];
		(*freefct)(((void **)root)[0]);
		free(root);
		if (l) {
			if (r)
				tdestroy(r, freefct);
			root = l;
			goto again;
		}
		if (r) {
			root = r;
			goto again;
		}
	}
}
%#endif /* __USE_GNU */

%[define_c_language_keyword(__KOS_FIXED_CONST)]

@@Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE)
[[decl_prefix(DEFINE_COMPAR_FN_T), decl_include("<features.h>")]]
void *lfind:(void const *key, [[nonnull]] void const *base, [[nonnull]] size_t __KOS_FIXED_CONST *nmemb, size_t size, [[nonnull]] __compar_fn_t compar)
	[(void const *key, [[nonnull]] void *base, [[nonnull]] size_t __KOS_FIXED_CONST *nmemb, size_t size, [[nonnull]] __compar_fn_t compar): void *]
	[(void const *key, [[nonnull]] void const *base, [[nonnull]] size_t __KOS_FIXED_CONST *nmemb, size_t size, [[nonnull]] __compar_fn_t compar): void const *]
{
	size_t i, count = *nmemb;
	void const *result = base;
	for (i = 0; i < count; ++i) {
		if ((*compar)(key, result) == 0)
			return (void *)result;
		result = (byte_t *)result + size;
	}
	return NULL;
}

@@Perform linear search for KEY by comparing by COMPAR function
@@in array [BASE, BASE+NMEMB*SIZE) and insert entry if not found
void *lsearch(void const *key, [[nonnull]] void *base,
              [[nonnull]] size_t *nmemb,
              size_t size, [[nonnull]] __compar_fn_t compar) {
	void *result;
	result = lfind(key, base, nmemb, size, compar);
	if (result == NULL) {
		result = memcpy((byte_t *)base + (*nmemb) * size, key, size);
		++(*nmemb);
	}
	return result;
}


%{

#endif /* __CC__ */

}%[pop_macro]%{

__SYSDECL_END

}