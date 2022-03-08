/* HASH CRC-32:0x1712466 */
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
#ifndef __local_twalk_r_defined
#define __local_twalk_r_defined
#include <__crt.h>
#include <kos/anno.h>
#ifndef __VISIT_defined
#define __VISIT_defined
typedef enum {
	preorder  = 0,
	postorder = 1,
	endorder  = 2,
	leaf      = 3
} VISIT;
#endif /* !__VISIT_defined */
__NAMESPACE_LOCAL_BEGIN
/* Walk the nodes of a tree.
 * `root' is the root of the tree to be walked, `action' the function to be
 * called at each node. `level'  is the level of  `root' in the whole  tree */
__LOCAL_LIBC(__trecurse) __ATTR_NONNULL((1, 2)) void
(__LIBC_LOCAL_NAME(__trecurse))(void const *__root,
                              void (__LIBCCALL *__action)(void const *__nodep, VISIT ___value, int __level, void *__arg),
                              void *__arg, int __level) {
	void *__l, *__r;
	__l = ((void **)__root)[1];
	__r = ((void **)__root)[2];
	if (!__l && !__r) {
		(*__action)(__root, leaf, __level, __arg);
	} else {
		(*__action)(__root, preorder, __level, __arg);
		if (__l != __NULLPTR)
			__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__trecurse)(__l, __action, __arg, __level + 1);
		(*__action)(__root, postorder, __level, __arg);
		if (__r != __NULLPTR)
			__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__trecurse)(__r, __action, __arg, __level + 1);
		(*__action)(__root, endorder, __level, __arg);
	}
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(twalk_r) void
(__LIBCCALL __LIBC_LOCAL_NAME(twalk_r))(void const *__root, void (__LIBCCALL *__action)(void const *__nodep, VISIT ___value, int __level, void *__arg), void *__arg) __THROWS(...) {
	if (__root && __action)
		(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__trecurse))(__root, __action, __arg, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_twalk_r_defined
#define __local___localdep_twalk_r_defined
#define __localdep_twalk_r __LIBC_LOCAL_NAME(twalk_r)
#endif /* !__local___localdep_twalk_r_defined */
#endif /* !__local_twalk_r_defined */
