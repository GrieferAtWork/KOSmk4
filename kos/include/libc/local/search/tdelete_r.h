/* HASH CRC-32:0x61669344 */
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
#ifndef __local_tdelete_r_defined
#define __local_tdelete_r_defined
#include <__crt.h>
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_memcpyc_defined
#define __local___localdep_memcpyc_defined
#ifdef __CRT_HAVE_memcpyc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpyc __LIBC_LOCAL_NAME(memcpyc)
#endif /* !__CRT_HAVE_memcpyc */
#endif /* !__local___localdep_memcpyc_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <parts/malloca.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tdelete_r) __ATTR_ACCESS_RO_OPT(1) __ATTR_ACCESS_RW_OPT(2) __ATTR_NONNULL((3)) void *
(__LIBCCALL __LIBC_LOCAL_NAME(tdelete_r))(void const *__restrict __key, void **__restrict __vrootp, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg) __THROWS(...) {
	typedef struct __node_struct {
		void const           *__key;
		struct __node_struct *__left_node;
		struct __node_struct *__right_node;
		__UINTPTR_TYPE__      __is_red;
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
	__nodestack = (__node **)__malloca(sizeof(__node *) * __stacksize);
	if __unlikely(!__nodestack)
		return __NULLPTR;
	__root = __p;
	while ((__cmp = (*__compar)(__key, __root->__key, __arg)) != 0) {
		if (__sp == __stacksize) {
			__node **__newstack;
			__stacksize += 20;
			__newstack = (__node **)__malloca(sizeof(__node *) * __stacksize);
			if __unlikely(!__newstack) {
				__retval = __NULLPTR;
				goto __done;
			}
			(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__newstack, __nodestack, __sp, sizeof(__node *));
			__freea(__nodestack);
			__nodestack = __newstack;
		}
		__nodestack[__sp++] = __rootp;
		__p = *__rootp;
		__rootp = __cmp < 0 ? &__p->__left_node
		                : &__p->__right_node;
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
				__newstack = (__node **)__malloca(sizeof(__node *) * __stacksize);
				if __unlikely(!__newstack) {
					__retval = __NULLPTR;
					goto __done;
				}
				(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__newstack, __nodestack, __sp, sizeof(__node *));
				__freea(__nodestack);
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
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__unchained);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
__done:
	__freea(__nodestack);
	return __retval;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_tdelete_r_defined
#define __local___localdep_tdelete_r_defined
#define __localdep_tdelete_r __LIBC_LOCAL_NAME(tdelete_r)
#endif /* !__local___localdep_tdelete_r_defined */
#endif /* !__local_tdelete_r_defined */
