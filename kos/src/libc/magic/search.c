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
%(c_prefix){
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/search.h) */
/* (#) Portability: DJGPP         (/include/search.h) */
/* (#) Portability: DragonFly BSD (/include/search.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/search.h) */
/* (#) Portability: FreeBSD       (/include/search.h) */
/* (#) Portability: GNU C Library (/misc/search.h) */
/* (#) Portability: GNU Hurd      (/usr/include/search.h) */
/* (#) Portability: MSVC          (/include/search.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/search.h) */
/* (#) Portability: NetBSD        (/include/search.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/search.h) */
/* (#) Portability: OpenBSD       (/include/search.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/search.h) */
/* (#) Portability: Windows Kits  (/ucrt/search.h) */
/* (#) Portability: diet libc     (/include/search.h) */
/* (#) Portability: libc4/5       (/include/search.h) */
/* (#) Portability: libc6         (/include/search.h) */
/* (#) Portability: mintlib       (/include/search.h) */
/* (#) Portability: musl libc     (/include/search.h) */
/* (#) Portability: uClibc        (/include/search.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(pid_t = __pid_t)]
%[default:section(".text.crt{|.dos}.utility.search")]

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

/* Separately, the implementation is also derived from Glibc */
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
}
%[define(DEFINE_ACTION =
@@pp_ifndef __ACTION_defined@@
#define __ACTION_defined
typedef enum {
	@FIND@  = 0,
	@ENTER@ = 1
} ACTION;
@@pp_endif@@
)]
%[insert:prefix(DEFINE_ACTION)]
%[define_type_class(ACTION = "TD")]

%{

/* For tsearch */
}
%[define(DEFINE_VISIT =
@@pp_ifndef __VISIT_defined@@
#define __VISIT_defined
typedef enum {
	@preorder@  = 0,
	@postorder@ = 1,
	@endorder@  = 2,
	@leaf@      = 3
} VISIT;
@@pp_endif@@
)]
%[insert:prefix(DEFINE_VISIT)]
%[define_type_class(VISIT = "TD")]

%{


#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __USE_GNU
/* Prototype structure for a linked-list data structure. This
 * is the type used by  the `insque' and `remque'  functions. */
struct qelem {
	struct qelem *q_forw;     /* [0..1] Forward link */
	struct qelem *q_back;     /* [0..1] Backward link */
	char          q_data[1];  /* Element data */
};
#endif /* __USE_GNU */

}

@@>> insque(3)
@@Insert ELEM into a doubly-linked list, after PREV
void insque([[out]] void *__restrict elem, [[inout_opt]] void *prev) {
	struct __queue_link {
		struct __queue_link *l_forw; /* [0..1] Forward link */
		struct __queue_link *l_back; /* [0..1] Backward link */
	};
	if (prev) {
		struct __queue_link *next;
		next = ((struct __queue_link *)prev)->l_forw;
		((struct __queue_link *)elem)->l_back = (struct __queue_link *)prev;
		((struct __queue_link *)elem)->l_forw = next;
		((struct __queue_link *)prev)->l_forw = (struct __queue_link *)elem;
		if (next)
			next->l_back = (struct __queue_link *)elem;
	} else {
		((struct __queue_link *)elem)->l_back = NULL;
		((struct __queue_link *)elem)->l_forw = NULL;
	}
}

@@>> remque(3)
@@Unlink ELEM from the doubly-linked list that it is in
void remque([[inout]] void *__restrict elem) {
	struct __queue_link {
		struct __queue_link *l_forw; /* [0..1] Forward link */
		struct __queue_link *l_back; /* [0..1] Backward link */
	};
	struct __queue_link *prev, *next;
	prev = ((struct __queue_link *)elem)->l_back;
	next = ((struct __queue_link *)elem)->l_forw;
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
#define ____compar_fn_t_defined
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#endif /* !____compar_fn_t_defined */
#ifdef __USE_GNU
typedef __compar_fn_t comparison_fn_t;
#endif /* __USE_GNU */
#endif /* __COMPAR_FN_T */

#ifndef __ENTRY_defined
#define __ENTRY_defined
typedef struct entry {
	char *key;
	void *data;
} ENTRY;
#endif /* !__ENTRY_defined */

/* Opaque type for internal use. */
struct _ENTRY;

/* Family of hash table  handling functions. The functions  also
 * have reentrant counterparts ending with _r. The non-reentrant
 * functions all work on a signle internal hashing table. */

}

%[define_replacement(ENTRY = "struct entry")]
%[define_replacement(VISIT = VISIT)]
%[define_replacement(ACTION = ACTION)]


%[define(DEFINE_HSEARCH_DATA =
@@pp_ifndef __hsearch_data_defined@@
#define __hsearch_data_defined
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
#define __local_htab_defined
@@push_namespace(local)@@
__LOCAL_LIBC_DATA(htab) struct hsearch_data htab = { NULL, 0, 0 };
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_SEARCH_ENTRY =
@@pp_ifndef __ENTRY_defined@@
#define __ENTRY_defined
typedef struct entry {
	char *@key@;
	void *@data@;
} @ENTRY@;
@@pp_endif@@
)]

@@>> hsearch(3)
@@Search for entry matching `item.key' in internal hash table.
@@If `action' is `FIND' return found entry or signal error by returning `NULL'.
@@If  `action'  is  `ENTER' replace  existing  data (if  any)  with `item.data'
[[decl_prefix(struct entry;), decl_prefix(DEFINE_ACTION)]]
[[impl_prefix(DEFINE_HSEARCH_DATA), impl_prefix(DEFINE_HSEARCH_HTAB)]]
[[requires_function(hsearch_r)]]
ENTRY *hsearch(ENTRY item, ACTION action) {
	ENTRY *result;
	hsearch_r(item, action, &result, &__NAMESPACE_LOCAL_SYM htab);
	return result;
}

@@>> hcreate(3)
@@Create a new hashing table which will at most contain `nel' elements
[[impl_prefix(DEFINE_HSEARCH_DATA), impl_prefix(DEFINE_HSEARCH_HTAB)]]
[[requires_function(hcreate_r), decl_include("<hybrid/typecore.h>")]]
int hcreate(size_t nel) {
	return hcreate_r(nel, &__NAMESPACE_LOCAL_SYM htab);
}

@@>> hdestroy(3)
@@Destroy current internal hashing table
[[impl_prefix(DEFINE_HSEARCH_DATA), impl_prefix(DEFINE_HSEARCH_HTAB)]]
[[requires_function(hdestroy_r)]]
void hdestroy() {
	hdestroy_r(&__NAMESPACE_LOCAL_SYM htab);
}

%{
#ifdef __USE_GNU
/* Data type for reentrant functions.  */
#ifndef __hsearch_data_defined
#define __hsearch_data_defined
struct hsearch_data {
	struct _ENTRY *table;
	unsigned int   size;
	unsigned int   filled;
};
#endif /* !__hsearch_data_defined */
}

@@>> hsearch_r(3)
@@Reentrant versions which can handle multiple hashing tables at the same time
[[decl_prefix(struct entry;)]]
[[decl_prefix(struct hsearch_data;)]]
[[decl_prefix(DEFINE_ACTION)]]
[[impl_prefix(DEFINE_HSEARCH_DATA)]]
[[impl_prefix(DEFINE_SEARCH_ENTRY)]]
[[impl_include("<libc/errno.h>")]]
int hsearch_r(ENTRY item, ACTION action,
              [[out]] ENTRY **retval,
              [[inout]] struct hsearch_data *htab) {
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
			if (idx <= hval2) {
				idx = htab->@size@ + idx - hval2;
			} else {
				idx -= hval2;
			}
			if (idx == first_idx)
				break;
			if (((entry_type *)htab->@table@)[idx].used == hval &&
			    strcmp(item.@key@, ((entry_type *)htab->@table@)[idx].entry.@key@) == 0) {
				*retval = &((entry_type *)htab->@table@)[idx].entry;
				return 1;
			}
		} while (((entry_type *)htab->@table@)[idx].used);
	}
	if (action == @ENTER@) {
		if (htab->@filled@ == htab->@size@) {
@@pp_ifdef ENOMEM@@
			(void)libc_seterrno(ENOMEM);
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
	(void)libc_seterrno(ESRCH);
@@pp_endif@@
	*retval = NULL;
	return 0;
}

@@>> hcreate_r(3)
[[decl_prefix(struct hsearch_data;)]]
[[decl_include("<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE_HSEARCH_DATA)]]
[[impl_prefix(DEFINE_SEARCH_ENTRY)]]
[[requires_function(calloc)]]
[[impl_include("<hybrid/limitcore.h>", "<libc/errno.h>")]]
[[impl_prefix(
@@push_namespace(local)@@
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
@@pop_namespace@@
)]]
int hcreate_r(size_t nel, struct hsearch_data *htab) {
	typedef struct {
		unsigned int used;
		ENTRY        entry;
	} entry_type;
	if (htab == NULL) {
@@pp_ifdef EINVAL@@
		(void)libc_seterrno(EINVAL);
@@pp_endif@@
		return 0;
	}
	if (htab->@table@ != NULL)
		return 0;
	if (nel < 3)
		nel = 3;
	for (nel |= 1;; nel += 2) {
		if (UINT_MAX - 2 < nel) {
@@pp_ifdef ENOMEM@@
			(void)libc_seterrno(ENOMEM);
@@pp_endif@@
			return 0;
		}
		if (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprime)(nel))
			break;
	}
	htab->@size@   = nel;
	htab->@filled@ = 0;
	htab->@table@  = (struct _ENTRY *)calloc(htab->@size@ + 1, sizeof(entry_type));
	if (htab->@table@ == NULL)
		return 0;
	return 1;
}

@@>> hdestroy_r(3)
[[decl_prefix(struct hsearch_data;)]]
[[impl_prefix(DEFINE_HSEARCH_DATA)]]
[[impl_include("<libc/errno.h>")]]
void hdestroy_r(struct hsearch_data *htab) {
	if (htab == NULL) {
@@pp_ifdef EINVAL@@
		(void)libc_seterrno(EINVAL);
@@pp_endif@@
		return;
	}
@@pp_if $has_function(free)@@
	free(htab->@table@);
@@pp_endif@@
	htab->@table@ = NULL;
}
%#endif /* __USE_GNU */

%{
/* The tsearch routines are very interesting. They make  many
 * assumptions about the compiler. It assumes that the  first
 * field in node must be the "key" field, which points to the
 * datum. Everything depends on that. */
}




%#ifdef __USE_KOS
@@>> tsearch(3), tsearch_r(3)
@@Search for an  entry matching  the given `key'  in the  tree
@@pointed to by `*rootp' and insert a new element if not found
[[requires_function(malloc), impl_prefix(
@@push_namespace(local)@@
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
@@pop_namespace@@
), throws, crt_dos_variant(callback(
	cook: struct { auto compar = compar; auto arg = arg; },
	wrap: (void const *a, void const *b, $cook *c): int { return (*c->compar)(a, b, c->arg); },
	impl: tsearch_r(key, vrootp, (int (LIBCCALL *)(void const *, void const *, void *))&$wrap, &$cook),
))]]
void *tsearch_r([[in_opt]] void const *key, [[inout_opt]] void **vrootp,
                [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b, void *arg),
                void *arg) {
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
		r = (*compar)(key, root->key, arg);
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
	q = (node)malloc(sizeof(struct __node_struct));
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

@@>> tfind(3), tfind_r(3)
@@Search for an entry matching the given `key' in the tree pointed
@@to  by `*rootp'. If no matching entry is available return `NULL'
[[throws, crt_dos_variant(callback(
	cook: struct { auto compar = compar; auto arg = arg; },
	wrap: (void const *a, void const *b, $cook *c): int { return (*c->compar)(a, b, c->arg); },
	impl: tfind_r(key, vrootp, (int (LIBCCALL *)(void const *, void const *, void *))&$wrap, &$cook),
))]]
void *tfind_r([[in_opt]] void const *key, [[in_opt]] void *const *vrootp,
              [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b, void *arg),
              void *arg) {
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
		int r = (*compar)(key, root->key, arg);
		if (r == 0)
			return root;
		rootp = r < 0 ? &root->left_node
		              : &root->right_node;
	}
	return NULL;
}

@@>> tdelete(3), tdelete_r(3)
@@Remove the element matching `key' from the tree pointed to by `*rootp'
[[throws, impl_include("<hybrid/typecore.h>", "<parts/malloca.h>")]]
[[crt_dos_variant(callback(
	cook: struct { auto compar = compar; auto arg = arg; },
	wrap: (void const *a, void const *b, $cook *c): int { return (*c->compar)(a, b, c->arg); },
	impl: tdelete_r(key, vrootp, (int (LIBCCALL *)(void const *, void const *, void *))&$wrap, &$cook),
))]]
void *tdelete_r([[in_opt]] void const *__restrict key, [[inout_opt]] void **__restrict vrootp,
                [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b, void *arg),
                void *arg) {
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
	while ((cmp = (*compar)(key, root->key, arg)) != 0) {
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
		if (root == NULL) {
			__freea(nodestack);
			return NULL;
		}
	}
	retval = p;
	root = *rootp;
	r = root->right_node;
	q = root->left_node;
	if (q == NULL || r == NULL) {
		unchained = root;
	} else {
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
	if (sp == 0) {
		*rootp = r;
	} else {
		q = *nodestack[sp-1];
		if (unchained == q->right_node) {
			q->right_node = r;
		} else {
			q->left_node = r;
		}
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
@@pp_if $has_function(free)@@
	free(unchained);
@@pp_endif@@
done:
	__freea(nodestack);
	return retval;
}

@@>> twalk(3), twalk_r(3)
@@Walk through the whole tree and call the `action' callback for every node or leaf
[[throws, decl_prefix(DEFINE_VISIT)]]
[[export_alias("__twalk_r")]]
[[impl_prefix(
@@push_namespace(local)@@
/* Walk the nodes of a tree.
 * `root' is the root of the tree to be walked, `action' the function to be
 * called at each node. `level'  is the level of  `root' in the whole  tree */
__LOCAL_LIBC(trecurse) NONNULL((1, 2)) void
(__LIBC_LOCAL_NAME(trecurse))(void const *root,
                              void (LIBCCALL *action)(void const *nodep, VISIT value, int level, void *arg),
                              void *arg, int level) {
	void *l, *r;
	l = ((void **)root)[1];
	r = ((void **)root)[2];
	if (!l && !r) {
		(*action)(root, @leaf@, level, arg);
	} else {
		(*action)(root, @preorder@, level, arg);
		if (l != NULL)
			__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(trecurse)(l, action, arg, level + 1);
		(*action)(root, @postorder@, level, arg);
		if (r != NULL)
			__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(trecurse)(r, action, arg, level + 1);
		(*action)(root, @endorder@, level, arg);
	}
}
@@pop_namespace@@
), crt_dos_variant(callback(
	cook: struct { auto action = action; auto arg = arg; },
	wrap: (void const *nodep, VISIT value, int level, $cook *c) { (*c->action)(nodep, value, level, c->arg); },
	impl: twalk_r(root, (void (LIBCCALL *)(void const *, VISIT, int, void *))&$wrap, &$cook),
))]]
void twalk_r([[in_opt]] void const *root,
             [[nullable]] void (LIBCCALL *action)(void const *nodep, VISIT value, int level, void *arg),
             void *arg) {
	if (root && action)
		(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(trecurse))(root, action, arg, 0);
}

@@>> tdestroy(3), tdestroy_r(3)
@@Destroy the whole tree, call `freefct' for each node or leaf
[[throws, crt_dos_variant(callback(
	cook: struct { auto freefct = freefct; auto arg = arg; },
	wrap: (void *nodep, $cook *c) { (*c->freefct)(nodep, c->arg); },
	impl: tdestroy_r(root, (void (LIBCCALL *)(void *, void *))&$wrap, &$cook),
))]]
void tdestroy_r([[inout_opt]] void *root,
                [[nonnull]] void (LIBCCALL *freefct)(void *nodep, void *arg),
                void *arg) {
	if (root) {
		void *l, *r;
again:
		l = ((void **)root)[1];
		r = ((void **)root)[2];
		(*freefct)(((void **)root)[0], arg);
@@pp_if $has_function(free)@@
		free(root);
@@pp_endif@@
		if (l) {
			tdestroy_r(r, freefct, arg);
			root = l;
			goto again;
		}
		if (r) {
			root = r;
			goto again;
		}
	}
}

%#endif /* __USE_KOS */


/* HINT: `DEFINE_INVOKE_COMPARE_HELPER' is defined in `./stdlib.c' */

[[requires_function(tsearch_r)]]
[[export_alias("__tsearch"), doc_alias("tsearch_r")]]
[[impl_prefix(DEFINE_INVOKE_COMPARE_HELPER)]]
[[throws, crt_dos_variant(callback(
	cook: auto = compar,
	wrap: (void const *a, void const *b, $cook c): int { return (*c)(a, b); },
	impl: tsearch_r(key, vrootp, (int (LIBCCALL *)(void const *, void const *, void *))&$wrap, (void *)$cook),
))]]
void *tsearch([[in_opt]] void const *key, [[inout_opt]] void **vrootp,
              [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b)) {
@@pp_ifdef __LIBCCALL_CALLER_CLEANUP@@
	return tsearch_r(key, vrootp, (int (LIBCCALL *)(void const *, void const *, void *))(void *)compar, NULL);
@@pp_else@@
	return tsearch_r(key, vrootp, &__NAMESPACE_LOCAL_SYM __invoke_compare_helper, (void *)compar);
@@pp_endif@@
}

[[export_alias("__tfind"), doc_alias("tfind_r")]]
[[impl_prefix(DEFINE_INVOKE_COMPARE_HELPER)]]
[[throws, crt_dos_variant(callback(
	cook: auto = compar,
	wrap: (void const *a, void const *b, $cook c): int { return (*c)(a, b); },
	impl: tfind_r(key, vrootp, (int (LIBCCALL *)(void const *, void const *, void *))&$wrap, (void *)$cook),
))]]
void *tfind([[in_opt]] void const *key, [[in_opt]] void *const *vrootp,
            [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b)) {
@@pp_ifdef __LIBCCALL_CALLER_CLEANUP@@
	return tfind_r(key, vrootp, (int (LIBCCALL *)(void const *, void const *, void *))(void *)compar, NULL);
@@pp_else@@
	return tfind_r(key, vrootp, &__NAMESPACE_LOCAL_SYM __invoke_compare_helper, (void *)compar);
@@pp_endif@@
}

[[export_alias("__tdelete"), doc_alias("tdelete_r")]]
[[impl_prefix(DEFINE_INVOKE_COMPARE_HELPER)]]
[[throws, crt_dos_variant(callback(
	cook: auto = compar,
	wrap: (void const *a, void const *b, $cook c): int { return (*c)(a, b); },
	impl: tdelete_r(key, vrootp, (int (LIBCCALL *)(void const *, void const *, void *))&$wrap, (void *)$cook),
))]]
void *tdelete([[in_opt]] void const *__restrict key, [[inout_opt]] void **__restrict vrootp,
              [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b)) {
@@pp_ifdef __LIBCCALL_CALLER_CLEANUP@@
	return tdelete_r(key, vrootp, (int (LIBCCALL *)(void const *, void const *, void *))(void *)compar, NULL);
@@pp_else@@
	return tdelete_r(key, vrootp, &__NAMESPACE_LOCAL_SYM __invoke_compare_helper, (void *)compar);
@@pp_endif@@
}

%{
#ifndef __ACTION_FN_T
#define __ACTION_FN_T 1
typedef void (__LIBCCALL *__action_fn_t)(void const *nodep, VISIT value, int level);
#endif /* !__ACTION_FN_T */
}


%[define(DEFINE_INVOKE_TWALK_ACTION_HELPER =
@@pp_ifndef              __LIBCCALL_CALLER_CLEANUP@@
@@pp_ifndef ____invoke_twalk_action_helper_defined@@
@@push_namespace(local)@@
#define ____invoke_twalk_action_helper_defined
__LOCAL_LIBC(__invoke_twalk_action_helper) void
(__LIBCCALL __invoke_twalk_action_helper)(void const *nodep, VISIT value, int level, void *arg) {
	(*(void (LIBCCALL *)(void const *, VISIT, int))arg)(nodep, value, level);
}
@@pop_namespace@@
@@pp_endif@@
@@pp_endif@@
)]


[[export_alias("__twalk"), doc_alias("twalk_r")]]
[[decl_prefix(DEFINE_VISIT), impl_prefix(DEFINE_INVOKE_TWALK_ACTION_HELPER)]]
[[throws, crt_dos_variant(callback(
	cook: auto = action,
	wrap: (void const *nodep, VISIT value, int level, $cook c) { (*c)(nodep, value, level); },
	impl: twalk_r(root, (void (LIBCCALL *)(void const *, VISIT, int, void *))&$wrap, (void *)$cook),
))]]
void twalk([[in_opt]] void const *root,
           [[nullable]] void (LIBCCALL *action)(void const *nodep, VISIT value, int level)) {
@@pp_ifdef __LIBCCALL_CALLER_CLEANUP@@
	twalk_r(root, (void (LIBCCALL *)(void const *, VISIT, int, void *))(void *)action, NULL);
@@pp_else@@
	twalk_r(root, &__NAMESPACE_LOCAL_SYM __invoke_twalk_action_helper, (void *)action);
@@pp_endif@@
}



%{
#ifdef __USE_GNU
/* Callback type for function to free a tree node.
 * If the keys are atomic data this function should do nothing. */
#ifndef ____free_fn_t_defined
#define ____free_fn_t_defined
typedef void (__LIBCCALL *__free_fn_t)(void *__nodep);
#endif /* !____free_fn_t_defined */
}

%[define(DEFINE_INVOKE_FREE_FN_HELPER =
@@pp_ifndef         __LIBCCALL_CALLER_CLEANUP@@
@@pp_ifndef ____invoke_free_fn_helper_defined@@
@@push_namespace(local)@@
#define ____invoke_free_fn_helper_defined
__LOCAL_LIBC(__invoke_free_fn_helper) void
(__LIBCCALL __invoke_free_fn_helper)(void *nodep, void *arg) {
	(*(void (LIBCCALL *)(void *))arg)(nodep);
}
@@pop_namespace@@
@@pp_endif@@
@@pp_endif@@
)]

[[doc_alias("tdestroy_r"), throws, crt_dos_variant(callback(
	cook: auto = freefct,
	wrap: (void *nodep, $cook c) { (*c)(nodep); },
	impl: tdestroy_r(root, (void (LIBCCALL *)(void *, void *))&$wrap, (void *)$cook),
)), impl_prefix(DEFINE_INVOKE_FREE_FN_HELPER)]]
void tdestroy([[inout_opt]] void *root,
              [[nonnull]] void (LIBCCALL *freefct)(void *nodep)) {
@@pp_ifdef __LIBCCALL_CALLER_CLEANUP@@
	tdestroy_r(root, (void (LIBCCALL *)(void *, void *))(void *)freefct, NULL);
@@pp_else@@
	tdestroy_r(root, &__NAMESPACE_LOCAL_SYM __invoke_free_fn_helper, (void *)freefct);
@@pp_endif@@
}
%#endif /* __USE_GNU */

%[define_c_language_keyword(__KOS_FIXED_CONST)]



@@>> lfind(3)
@@Perform linear search for `key' by comparing by `compar' in an array [pbase, pbase+pitem_count*item_size)
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[throws, wunused, dos_only_export_alias("_lfind"), crt_dos_variant(callback(
	cook: auto = compar,
	wrap: ($cook c, void const *a, void const *b): int { return (*c)(a, b); },
	impl: _lfind_s(key, pbase, pitem_count, item_size, (int (LIBCCALL *)(void *, void const *, void const *))&$wrap, (void *)$cook),
))]]
void *lfind([[in_opt]] void const *key, [[in(*pitem_count * item_size)]] void const *pbase, [[in]] size_t __KOS_FIXED_CONST *pitem_count, size_t item_size, [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b))
	[([[in_opt]] void const *key, [[in(*pitem_count * item_size)]] void *pbase, [[in]] size_t __KOS_FIXED_CONST *pitem_count, size_t item_size, [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b)): void *]
	[([[in_opt]] void const *key, [[in(*pitem_count * item_size)]] void const *pbase, [[in]] size_t __KOS_FIXED_CONST *pitem_count, size_t item_size, [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b)): void const *]
{
	size_t i, count = *pitem_count;
	void const *result = pbase;
	for (i = 0; i < count; ++i) {
		if ((*compar)(key, result) == 0)
			return (void *)result;
		result = (byte_t *)result + item_size;
	}
	return NULL;
}

@@>> lsearch(3)
@@Perform  linear  search  for  `key'  by  comparing  by  `compar'   function
@@in array [pbase, pbase+pitem_count*item_size) and insert entry if not found
[[decl_include("<hybrid/typecore.h>")]]
[[throws, dos_only_export_alias("_lsearch"), crt_dos_variant(callback(
	cook: auto = compar,
	wrap: ($cook c, void const *a, void const *b): int { return (*c)(a, b); },
	impl: _lsearch_s(key, pbase, pitem_count, item_size, (int (LIBCCALL *)(void *, void const *, void const *))&$wrap, (void *)$cook),
))]]
void *lsearch([[in_opt]] void const *key, [[inout]] void *pbase,
              [[inout]] size_t *pitem_count, size_t item_size,
              [[nonnull]] int (LIBCCALL *compar)(void const *a, void const *b)) {
	void *result;
	result = lfind(key, pbase, pitem_count, item_size, compar);
	if (result == NULL) {
		result = memcpy((byte_t *)pbase + (*pitem_count) * item_size, key, item_size);
		++*pitem_count;
	}
	return result;
}



%
%#ifdef __USE_DOS
%{
typedef int (__LIBCCALL *_CoreCrtSecureSearchSortCompareFunction)(void *__arg, void const *__a, void const *__b);
typedef __compar_fn_t _CoreCrtMgdNonSecureSearchSortCompareFunction;
}

%[default:section(".text.crt.dos.utility.search")]


%[insert:function(_lfind = lfind)]
%[insert:function(_lsearch = lsearch)]
%[insert:extern(qsort)]
%[insert:extern(bsearch)]

[[wunused, throws, decl_include("<hybrid/typecore.h>", "<features.h>"), crt_dos_variant(callback(
	cook: struct { auto compar = compar; auto arg = arg; },
	wrap: ($cook *c, void const *a, void const *b): int { return (*c->compar)(c->arg, a, b); },
	impl: _lfind_s(key, pbase, pitem_count, item_size, (int (LIBCCALL *)(void *, void const *, void const *))&$wrap, &$cook),
))]]
void *_lfind_s([[in_opt]] void const *key, [[in(*pitem_count * item_size)]] void const *pbase, [[in]] size_t __KOS_FIXED_CONST *pitem_count, size_t item_size, [[nonnull]] int (LIBCCALL *compar)(void *arg, void const *a, void const *b), void *arg)
	[([[in_opt]] void const *key, [[in(*pitem_count * item_size)]] void *pbase, [[in]] size_t __KOS_FIXED_CONST *pitem_count, size_t item_size, [[nonnull]] int (LIBCCALL *compar)(void *arg, void const *a, void const *b), void *arg): void *]
	[([[in_opt]] void const *key, [[in(*pitem_count * item_size)]] void const *pbase, [[in]] size_t __KOS_FIXED_CONST *pitem_count, size_t item_size, [[nonnull]] int (LIBCCALL *compar)(void *arg, void const *a, void const *b), void *arg): void const *]
{
	size_t i, count = *pitem_count;
	void const *result = pbase;
	for (i = 0; i < count; ++i) {
		if ((*compar)(arg, key, result) == 0)
			return (void *)result;
		result = (byte_t *)result + item_size;
	}
	return NULL;
}


[[wunused, throws, decl_include("<hybrid/typecore.h>"), crt_dos_variant(callback(
	cook: struct { auto compar = compar; auto arg = arg; },
	wrap: ($cook *c, void const *a, void const *b): int { return (*c->compar)(c->arg, a, b); },
	impl: _lsearch_s(key, pbase, pitem_count, item_size, (int (LIBCCALL *)(void *, void const *, void const *))&$wrap, &$cook),
))]]
void *_lsearch_s([[in_opt]] void const *key, [[inout]] void *pbase,
                 [[inout]] size_t *pitem_count, size_t item_size,
                 [[nonnull]] int (LIBCCALL *compar)(void *arg, void const *a, void const *b),
                 void *arg) {
	void *result;
	result = _lfind_s(key, pbase, pitem_count, item_size, compar, arg);
	if (result == NULL) {
		result = memcpy((byte_t *)pbase + (*pitem_count) * item_size, key, item_size);
		++*pitem_count;
	}
	return result;
}



%#ifdef __USE_DOS_SLIB
%[insert:extern(qsort_s)]
%[insert:extern(bsearch_s)]
%#endif /* __USE_DOS_SLIB */
%#endif /* __USE_DOS */

%{

#endif /* __CC__ */

}%[pop_macro]%{

__SYSDECL_END

}
