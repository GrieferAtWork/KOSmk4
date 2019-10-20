/* HASH CRC-32:0xd613e456 */
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
#ifndef __local_trecurse_defined
#define __local_trecurse_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Walk the nodes of a tree.
 * ROOT is the root of the tree to be walked, ACTION the function to be
 * called at each node. LEVEL is the level of ROOT in the whole tree */
__LOCAL_LIBC(trecurse) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(trecurse))(void const *__root,
                                                      __action_fn_t __action,
                                                      int __level) {
#line 714 "kos/src/libc/magic/search.c"
	void *__l, *__r;
	__l = ((void **)__root)[1];
	__r = ((void **)__root)[2];
	if (!__l && !__r)
		(*__action)(__root, (VISIT)leaf, __level);
	else {
		(*__action)(__root, (VISIT)preorder, __level);
		if (__l != __NULLPTR)
			__LIBC_LOCAL_NAME(trecurse)(__l, __action, __level+1);
		(*__action)(__root, (VISIT)postorder, __level);
		if (__r != __NULLPTR)
			__LIBC_LOCAL_NAME(trecurse)(__r, __action, __level+1);
		(*__action)(__root, (VISIT)endorder, __level);
	}
}
__NAMESPACE_LOCAL_END
#endif /* !__local_trecurse_defined */
