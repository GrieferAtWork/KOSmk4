/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT__DISKFREE_T_H
#define _BITS_CRT__DISKFREE_T_H 1

#include <__stdinc.h>

#ifdef __CC__
#ifndef _DISKFREE_T_DEFINED
#define _DISKFREE_T_DEFINED 1
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("total_clusters")
#pragma push_macro("avail_clusters")
#pragma push_macro("sectors_per_cluster")
#pragma push_macro("bytes_per_sector")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef total_clusters
#undef avail_clusters
#undef sectors_per_cluster
#undef bytes_per_sector

#include <hybrid/typecore.h>
__DECL_BEGIN

struct _diskfree_t {
	__UINT32_TYPE__ total_clusters;
	__UINT32_TYPE__ avail_clusters;
	__UINT32_TYPE__ sectors_per_cluster;
	__UINT32_TYPE__ bytes_per_sector;
};

__DECL_END

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("bytes_per_sector")
#pragma pop_macro("sectors_per_cluster")
#pragma pop_macro("avail_clusters")
#pragma pop_macro("total_clusters")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !_DISKFREE_T_DEFINED */
#endif /* __CC__ */

#endif /* !_BITS_CRT__DISKFREE_T_H */
