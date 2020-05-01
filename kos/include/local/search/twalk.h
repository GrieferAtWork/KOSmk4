/* HASH CRC-32:0x3b76d247 */
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
/* Dependency: "trecurse" from "search" */
#ifndef ____localdep_trecurse_defined
#define ____localdep_trecurse_defined 1
#ifdef __CRT_HAVE_trecurse
/* Walk the nodes of a tree.
 * ROOT is the root of the tree to be walked, ACTION the function to be
 * called at each node. LEVEL is the level of ROOT in the whole tree */
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_trecurse,(void const *__root, __action_fn_t __action, int __level),trecurse,(__root,__action,__level))
#else /* LIBC: trecurse */
#include <local/search/trecurse.h>
/* Walk the nodes of a tree.
 * ROOT is the root of the tree to be walked, ACTION the function to be
 * called at each node. LEVEL is the level of ROOT in the whole tree */
#define __localdep_trecurse (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(trecurse))
#endif /* trecurse... */
#endif /* !____localdep_trecurse_defined */

__NAMESPACE_LOCAL_BEGIN
/* Walk through the whole tree and call the ACTION callback for every node or leaf */
__LOCAL_LIBC(twalk) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(twalk))(void const *__root,
                                                   __action_fn_t __action) {
#line 735 "kos/src/libc/magic/search.c"
	if (__root && __action)
		__localdep_trecurse(__root, __action, 0);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_twalk_defined */
