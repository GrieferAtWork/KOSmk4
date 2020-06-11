/* HASH CRC-32:0xc4df79a8 */
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
#ifndef __local_twalk_defined
#define __local_twalk_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: trecurse from search */
#ifndef __local___localdep_trecurse_defined
#define __local___localdep_trecurse_defined 1
/* Walk the nodes of a tree.
 * ROOT is the root of the tree to be walked, ACTION the function to be
 * called at each node. LEVEL is the level of ROOT in the whole tree */
__LOCAL __ATTR_NONNULL((1, 2)) void __NOTHROW_NCX(__LIBCCALL __localdep_trecurse)(void const *__root, __action_fn_t __action, int __level) { void *__l, *__r; __l = ((void **)__root)[1]; __r = ((void **)__root)[2]; if (!__l && !__r) (*__action)(__root, (VISIT)leaf, __level); else { (*__action)(__root, (VISIT)preorder, __level); if (__l != __NULLPTR) __localdep_trecurse(__l, __action, __level+1); (*__action)(__root, (VISIT)postorder, __level); if (__r != __NULLPTR) __localdep_trecurse(__r, __action, __level+1); (*__action)(__root, (VISIT)endorder, __level); } }
#endif /* !__local___localdep_trecurse_defined */
/* Walk through the whole tree and call the ACTION callback for every node or leaf */
__LOCAL_LIBC(twalk) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(twalk))(void const *__root, __action_fn_t __action) {
	if (__root && __action)
		__localdep_trecurse(__root, __action, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_twalk_defined
#define __local___localdep_twalk_defined 1
#define __localdep_twalk __LIBC_LOCAL_NAME(twalk)
#endif /* !__local___localdep_twalk_defined */
#endif /* !__local_twalk_defined */
