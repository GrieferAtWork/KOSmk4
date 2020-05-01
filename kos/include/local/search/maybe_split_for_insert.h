/* HASH CRC-32:0x16fb949d */
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
#ifndef __local_maybe_split_for_insert_defined
#define __local_maybe_split_for_insert_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Possibly "split" a node with two red successors, and/or fix up two red
 * edges in a row. ROOTP is a pointer to the lowest node we visited, PARENTP
 * and GPARENTP pointers to its parent/grandparent. P_R and GP_R contain the
 * comparison values that determined which way was taken in the tree to reach
 * ROOTP. MODE is 1 if we need not do the split, but must check for two red
 * edges between GPARENTP and ROOTP */
__LOCAL_LIBC(maybe_split_for_insert) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(maybe_split_for_insert))(void **__rootp,
                                                                    void **__parentp,
                                                                    void **__gparentp,
                                                                    int __p_r,
                                                                    int __gp_r,
                                                                    int __mode) {
#line 392 "kos/src/libc/magic/search.c"
	typedef struct __node_struct {
		void const         *__key;
		struct __node_struct *__left_node;
		struct __node_struct *__right_node;
		__UINTPTR_TYPE__    __is_red;
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
#endif /* !__local_maybe_split_for_insert_defined */
