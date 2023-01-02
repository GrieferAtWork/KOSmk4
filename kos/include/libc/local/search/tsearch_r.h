/* HASH CRC-32:0xf6ce678b */
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
#ifndef __local_tsearch_r_defined
#define __local_tsearch_r_defined
#include <__crt.h>
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),__libc_malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#else /* ... */
#undef __local___localdep_malloc_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
/* Possibly  "split" a node with two red  successors, and/or fix up two red
 * edges in a  row. `rootp' is  a pointer  to the lowest  node we  visited,
 * `parentp' and `gparentp' pointers  to its parent/grandparent. `p_r'  and
 * `gp_r' contain the comparison values that determined which way was taken
 * in  the tree to reach `rootp'. `mode' is  1 if we need not do the split,
 * but must check for two red edges between `gparentp' and `rootp' */
__LOCAL_LIBC(__maybe_split_for_insert) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__maybe_split_for_insert))(void **__rootp, /*nullable*/ void **__parentp,
                                                                    void **__gparentp, int __p_r, int __gp_r, int __mode) {
	typedef struct __node_struct {
		void const           *__key;
		struct __node_struct *__left_node;
		struct __node_struct *__right_node;
		__UINTPTR_TYPE__      __is_red;
	} *__node;
	__node __root = *(__node *)__rootp;
	__node *__rp, *__lp;
	__node __rpn, __lpn;
	__rp = &__root->__right_node;
	__rpn = __root->__right_node;
	__lp = &__root->__left_node;
	__lpn = __root->__left_node;
	if (__mode == 1 || (__rpn != __NULLPTR && __lpn != __NULLPTR && __rpn->__is_red && __lpn->__is_red)) {
		__root->__is_red = 1;
		if (__rpn)
			__rpn->__is_red = 0;
		if (__lpn)
			__lpn->__is_red = 0;
		if (__parentp != __NULLPTR && (*(__node *)__parentp)->__is_red) {
			__node __gp = *((__node *)__gparentp);
			__node __p = *((__node *)__parentp);
			if ((__p_r > 0) != (__gp_r > 0)) {
				__p->__is_red = 1;
				__gp->__is_red = 1;
				__root->__is_red = 0;
				if (__p_r < 0) {
					__p->__left_node = __rpn;
					*__rp = __p;
					__gp->__right_node = __lpn;
					*__lp = __gp;
				} else {
					__p->__right_node = __lpn;
					*__lp = __p;
					__gp->__left_node = __rpn;
					*__rp = __gp;
				}
				*(__node *)__gparentp = __root;
			} else {
				*(__node *)__gparentp = __p;
				__p->__is_red = 0;
				__gp->__is_red = 1;
				if (__p_r < 0) {
					__gp->__left_node = __p->__right_node;
					__p->__right_node = __gp;
				} else {
					__gp->__right_node = __p->__left_node;
					__p->__left_node = __gp;
				}
			}
		}
	}
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tsearch_r) __ATTR_INOUT_OPT(2) __ATTR_IN_OPT(1) __ATTR_NONNULL((3)) void *
(__LIBCCALL __LIBC_LOCAL_NAME(tsearch_r))(void const *__key, void **__vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg) __THROWS(...) {
	typedef struct __node_struct {
		void const           *__key;
		struct __node_struct *__left_node;
		struct __node_struct *__right_node;
		__UINTPTR_TYPE__      __is_red;
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
		__r = (*__compar)(__key, __root->__key, __arg);
		if (__r == 0)
			return __root;
		__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__maybe_split_for_insert)((void **)__rootp,
		                                                                (void **)__parentp,
		                                                                (void **)__gparentp,
		                                                                __p_r, __gp_r, 0);
		__nextp = __r < 0 ? &__root->__left_node
		              : &__root->__right_node;
		if (*__nextp == __NULLPTR)
			break;
		__gparentp = __parentp;
		__parentp = __rootp;
		__rootp = __nextp;
		__gp_r = __p_r;
		__p_r = __r;
	}
	__q = (__node)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(sizeof(struct __node_struct));
	if (__q != __NULLPTR) {
		*__nextp = __q;
		__q->__key = __key;
		__q->__is_red = 1;
		__q->__left_node = __NULLPTR;
		__q->__right_node = __NULLPTR;
		if (__nextp != __rootp) {
			__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__maybe_split_for_insert)((void **)__nextp,
			                                                                (void **)__rootp,
			                                                                (void **)__parentp,
			                                                                __r, __p_r, 1);
		}
	}
	return __q;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tsearch_r_defined
#define __local___localdep_tsearch_r_defined
#define __localdep_tsearch_r __LIBC_LOCAL_NAME(tsearch_r)
#endif /* !__local___localdep_tsearch_r_defined */
#else /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
#undef __local_tsearch_r_defined
#endif /* !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
#endif /* !__local_tsearch_r_defined */
