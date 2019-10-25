/* HASH CRC-32:0x4687dfff */
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
#ifndef __local_tsearch_defined
#if ((defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc))
#define __local_tsearch_defined 1
/* Dependency: "maybe_split_for_insert" from "search" */
#ifndef ____localdep_maybe_split_for_insert_defined
#define ____localdep_maybe_split_for_insert_defined 1
#if defined(__CRT_HAVE_maybe_split_for_insert)
/* Possibly "split" a node with two red successors, and/or fix up two red
 * edges in a row. ROOTP is a pointer to the lowest node we visited, PARENTP
 * and GPARENTP pointers to its parent/grandparent. P_R and GP_R contain the
 * comparison values that determined which way was taken in the tree to reach
 * ROOTP. MODE is 1 if we need not do the split, but must check for two red
 * edges between GPARENTP and ROOTP */
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_maybe_split_for_insert,(void **__rootp, void **__parentp, void **__gparentp, int __p_r, int __gp_r, int __mode),maybe_split_for_insert,(__rootp,__parentp,__gparentp,__p_r,__gp_r,__mode))
#else /* LIBC: maybe_split_for_insert */
#include <local/search/maybe_split_for_insert.h>
/* Possibly "split" a node with two red successors, and/or fix up two red
 * edges in a row. ROOTP is a pointer to the lowest node we visited, PARENTP
 * and GPARENTP pointers to its parent/grandparent. P_R and GP_R contain the
 * comparison values that determined which way was taken in the tree to reach
 * ROOTP. MODE is 1 if we need not do the split, but must check for two red
 * edges between GPARENTP and ROOTP */
#define __localdep_maybe_split_for_insert (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(maybe_split_for_insert))
#endif /* maybe_split_for_insert... */
#endif /* !____localdep_maybe_split_for_insert_defined */

/* Dependency: "malloc" from "stdlib" */
#ifndef ____localdep_malloc_defined
#define ____localdep_malloc_defined 1
#ifdef __std___localdep_malloc_defined
__NAMESPACE_STD_USING(__localdep_malloc)
#elif __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL __localdep_malloc)(__SIZE_TYPE__ __n_bytes) { return __builtin_malloc(__n_bytes); }
#elif defined(__CRT_HAVE_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __n_bytes),malloc,(__n_bytes))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc))
#include <local/stdlib/malloc.h>
#define __localdep_malloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc))
#else /* CUSTOM: malloc */
#undef ____localdep_malloc_defined
#endif /* malloc... */
#endif /* !____localdep_malloc_defined */

__NAMESPACE_LOCAL_BEGIN
/* Search for an entry matching the given KEY in the tree
 * pointed to by *ROOTP and insert a new element if not found */
__LOCAL_LIBC(tsearch) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tsearch))(void const *__key,
                                                     void **__vrootp,
                                                     __compar_fn_t __compar) {
#line 448 "kos/src/libc/magic/search.c"
	typedef struct __node_struct {
		void const         *__key;
		struct __node_struct *__left_node;
		struct __node_struct *__right_node;
		__UINTPTR_TYPE__    __is_red;
	} *__node;
	__node __q, __root;
	__node *__parentp = __NULLPTR, *__gparentp = __NULLPTR;
	__node *__rootp = (__node *)__vrootp;
	__node *__nextp;
	int __r = 0, __p_r = 0, __gp_r = 0;
	if (__rootp == __NULLPTR)
		return __NULLPTR;
	__root = *__rootp;
	if (__root != __NULLPTR)
		__root->__is_red = 0;
	__nextp = __rootp;
	while (*__nextp != __NULLPTR) {
		__root = *__rootp;
		__r = (*__compar) (__key, __root->__key);
		if (__r == 0)
			return __root;
		__localdep_maybe_split_for_insert((void **)__rootp, (void **)__parentp, (void **)__gparentp, __p_r, __gp_r, 0);
		__nextp = __r < 0
			? &__root->__left_node
			: &__root->__right_node
			;
		if (*__nextp == __NULLPTR)
			break;
		__gparentp = __parentp;
		__parentp = __rootp;
		__rootp = __nextp;
		__gp_r = __p_r;
		__p_r = __r;
	}
	__q = (__node)__localdep_malloc(sizeof(struct __node_struct));
	if (__q != __NULLPTR) {
		*__nextp = __q;
		__q->__key = __key;
		__q->__is_red = 1;
		__q->__left_node = __NULLPTR;
		__q->__right_node = __NULLPTR;
		if (__nextp != __rootp)
			__localdep_maybe_split_for_insert((void **)__nextp, (void **)__rootp, (void **)__parentp, __r, __p_r, 1);
	}
	return __q;
}
__NAMESPACE_LOCAL_END
#endif /* ((defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc)) */
#endif /* !__local_tsearch_defined */
