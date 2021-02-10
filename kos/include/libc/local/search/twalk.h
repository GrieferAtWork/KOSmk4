/* HASH CRC-32:0xa5514748 */
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
#ifndef __local_twalk_defined
#define __local_twalk_defined 1
#include <__crt.h>
#ifndef __ACTION_FN_T
#define __ACTION_FN_T 1
typedef void (__LIBKCALL *__action_fn_t)(void const *__nodep, int __value, int __level);
#endif /* !__ACTION_FN_T */
__NAMESPACE_LOCAL_BEGIN
/* Walk the nodes of a tree.
 * ROOT is the root of the tree to be walked, ACTION the function to be
 * called at each node. LEVEL  is the level of  ROOT in the whole  tree */
__LOCAL_LIBC(__trecurse) __ATTR_NONNULL((1, 2)) void
__LIBC_LOCAL_NAME(__trecurse)(void const *__root, __action_fn_t __action, int __level) {
	void *__l, *__r;
	__l = ((void **)__root)[1];
	__r = ((void **)__root)[2];
	if (!__l && !__r) {
		(*__action)(__root, (VISIT)3, __level);
	} else {
		(*__action)(__root, (VISIT)0, __level);
		if (__l != __NULLPTR)
			__trecurse(__l, __action, __level + 1);
		(*__action)(__root, (VISIT)1, __level);
		if (__r != __NULLPTR)
			__trecurse(__r, __action, __level + 1);
		(*__action)(__root, (VISIT)2, __level);
	}
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
/* Walk through the whole tree and call the ACTION callback for every node or leaf */
__LOCAL_LIBC(twalk) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(twalk))(void const *__root, __action_fn_t __action) {
	if (__root && __action)
		__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__trecurse)(__root, __action, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_twalk_defined
#define __local___localdep_twalk_defined 1
#define __localdep_twalk __LIBC_LOCAL_NAME(twalk)
#endif /* !__local___localdep_twalk_defined */
#endif /* !__local_twalk_defined */
