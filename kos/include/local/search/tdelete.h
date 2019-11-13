/* HASH CRC-32:0xc448700a */
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
#ifndef __local_tdelete_defined
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#define __local_tdelete_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <hybrid/typecore.h>

#include <malloca.h>
/* Dependency: "memcpy" from "string" */
#ifndef ____localdep_memcpy_defined
#define ____localdep_memcpy_defined 1
#ifdef __fast_memcpy_defined
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* LIBC: memcpy */
#include <local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))
#endif /* memcpy... */
#endif /* !____localdep_memcpy_defined */

/* Dependency: "free" */
#ifndef ____localdep_free_defined
#define ____localdep_free_defined 1
#ifdef __std___localdep_free_defined
__NAMESPACE_STD_USING(__localdep_free)
#elif __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__FORCELOCAL void __NOTHROW_NCX(__LIBCCALL __localdep_free)(void *__mallptr) { return __builtin_free(__mallptr); }
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* LIBC: free */
#undef ____localdep_free_defined
#endif /* free... */
#endif /* !____localdep_free_defined */

__NAMESPACE_LOCAL_BEGIN
/* Remove the element matching KEY from the tree pointed to by *ROOTP */
__LOCAL_LIBC(tdelete) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(tdelete))(void const *__restrict __key,
                                                     void **__restrict __vrootp,
                                                     __compar_fn_t __compar) {
#line 527 "kos/src/libc/magic/search.c"
	typedef struct __node_struct {
		void const         *__key;
		struct __node_struct *__left_node;
		struct __node_struct *__right_node;
		__UINTPTR_TYPE__    __is_red;
	} *__node;
	__node __p, __q, __r, __retval;
	__node __root, __unchained;
	__node *__rootp = (__node *)__vrootp;
	int __cmp, __stacksize = 40, __sp = 0;
	__node **__nodestack;
	if (__rootp == __NULLPTR)
		return __NULLPTR;
	__p = *__rootp;
	if (__p == __NULLPTR)
		return __NULLPTR;
	__nodestack = (__node **)malloca(sizeof(__node *)*__stacksize);
	if __unlikely(!__nodestack)
		return __NULLPTR;
	__root = __p;
	while ((__cmp = (*__compar)(__key, __root->__key)) != 0) {
		if (__sp == __stacksize) {
			__node **__newstack;
			__stacksize += 20;
			__newstack = (__node **)__malloca(sizeof(__node *)*__stacksize);
			if __unlikely(!__newstack) {
				__retval = __NULLPTR;
				goto __done;
			}
			__localdep_memcpy(__newstack, __nodestack, __sp*sizeof(__node *));
			freea(__nodestack);
			__nodestack = __newstack;
		}
		__nodestack[__sp++] = __rootp;
		__p = *__rootp;
		__rootp = __cmp < 0
			? &__p->__left_node
			: &__p->__right_node
			;
		__root = *__rootp;
		if (__root == __NULLPTR)
			return __NULLPTR;
	}
	__retval = __p;
	__root = *__rootp;
	__r = __root->__right_node;
	__q = __root->__left_node;
	if (__q == __NULLPTR || __r == __NULLPTR)
		__unchained = __root;
	else {
		__node *__parentp = __rootp, *__up = &__root->__right_node;
		__node __upn;
		for (;;) {
			if (__sp == __stacksize) {
				__node **__newstack;
				__stacksize += 20;
				__newstack = (__node **)__malloca(sizeof(__node *)*__stacksize);
				if __unlikely(!__newstack) {
					__retval = __NULLPTR;
					goto __done;
				}
				__localdep_memcpy(__newstack, __nodestack, __sp*sizeof(__node *));
				freea(__nodestack);
				__nodestack = __newstack;
			}
			__nodestack[__sp++] = __parentp;
			__parentp = __up;
			__upn = *__up;
			if (__upn->__left_node == __NULLPTR)
				break;
			__up = &__upn->__left_node;
		}
		__unchained = *__up;
	}
	__r = __unchained->__left_node;
	if (__r == __NULLPTR)
		__r = __unchained->__right_node;
	if (__sp == 0)
		*__rootp = __r;
	else {
		__q = *__nodestack[__sp-1];
		if (__unchained == __q->__right_node)
			__q->__right_node = __r;
		else
			__q->__left_node = __r;
	}
	if (__unchained != __root)
		__root->__key = __unchained->__key;
	if (!__unchained->__is_red) {
		while (__sp > 0 && (__r == __NULLPTR || !__r->__is_red)) {
			__node *__pp = __nodestack[__sp - 1];
			__p = *__pp;
			if (__r == __p->__left_node) {
				__q = __p->__right_node;
				if (__q->__is_red) {
					__q->__is_red = 0;
					__p->__is_red = 1;
					__p->__right_node = __q->__left_node;
					__q->__left_node = __p;
					*__pp = __q;
					__nodestack[__sp++] = __pp = &__q->__left_node;
					__q = __p->__right_node;
				}
				if ((__q->__left_node == __NULLPTR || !__q->__left_node->__is_red) &&
					(__q->__right_node == __NULLPTR || !__q->__right_node->__is_red)) {
					__q->__is_red = 1;
					__r = __p;
				} else {
					if (__q->__right_node == __NULLPTR || !__q->__right_node->__is_red) {
						__node __q2 = __q->__left_node;
						__q2->__is_red = __p->__is_red;
						__p->__right_node = __q2->__left_node;
						__q->__left_node = __q2->__right_node;
						__q2->__right_node = __q;
						__q2->__left_node = __p;
						*__pp = __q2;
						__p->__is_red = 0;
					} else {
						__q->__is_red = __p->__is_red;
						__p->__is_red = 0;
						__q->__right_node->__is_red = 0;
						__p->__right_node = __q->__left_node;
						__q->__left_node = __p;
						*__pp = __q;
					}
					__sp = 1;
					__r = __NULLPTR;
				}
			} else {
				__q = __p->__left_node;
				if (__q->__is_red) {
					__q->__is_red = 0;
					__p->__is_red = 1;
					__p->__left_node = __q->__right_node;
					__q->__right_node = __p;
					*__pp = __q;
					__nodestack[__sp++] = __pp = &__q->__right_node;
					__q = __p->__left_node;
				}
				if ((__q->__right_node == __NULLPTR || !__q->__right_node->__is_red) &&
					(__q->__left_node == __NULLPTR || !__q->__left_node->__is_red)) {
					__q->__is_red = 1;
					__r = __p;
				} else {
					if (__q->__left_node == __NULLPTR || !__q->__left_node->__is_red) {
						__node __q2 = __q->__right_node;
						__q2->__is_red = __p->__is_red;
						__p->__left_node = __q2->__right_node;
						__q->__right_node = __q2->__left_node;
						__q2->__left_node = __q;
						__q2->__right_node = __p;
						*__pp = __q2;
						__p->__is_red = 0;
					} else {
						__q->__is_red = __p->__is_red;
						__p->__is_red = 0;
						__q->__left_node->__is_red = 0;
						__p->__left_node = __q->__right_node;
						__q->__right_node = __p;
						*__pp = __q;
					}
					__sp = 1;
					__r = __NULLPTR;
				}
			}
			--__sp;
		}
		if (__r != __NULLPTR)
			__r->__is_red = 0;
	}
	__localdep_free(__unchained);
__done:
	freea(__nodestack);
	return __retval;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) */
#endif /* !__local_tdelete_defined */
