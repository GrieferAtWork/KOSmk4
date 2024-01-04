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
#ifndef _BITS_CRT_DOS__CRTMEMSTATE_H
#define _BITS_CRT_DOS__CRTMEMSTATE_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

#define _BLOCK_TYPE(block)    ((block) & 0xffff)
#define _BLOCK_SUBTYPE(block) ((block) >> 16 & 0xffff)

#define _FREE_BLOCK   0
#define _NORMAL_BLOCK 1
#define _CRT_BLOCK    2
#define _IGNORE_BLOCK 3
#define _CLIENT_BLOCK 4
#define _MAX_BLOCKS   5

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("pBlockHeader")
#pragma push_macro("lCounts")
#pragma push_macro("lSizes")
#pragma push_macro("lHighWaterCount")
#pragma push_macro("lTotalCount")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef pBlockHeader
#undef lCounts
#undef lSizes
#undef lHighWaterCount
#undef lTotalCount
struct _CrtMemBlockHeader;
typedef struct _CrtMemState {
	struct _CrtMemBlockHeader *pBlockHeader;
	__SIZE_TYPE__              lCounts[_MAX_BLOCKS];
	__SIZE_TYPE__              lSizes[_MAX_BLOCKS];
	__SIZE_TYPE__              lHighWaterCount;
	__SIZE_TYPE__              lTotalCount;
} _CrtMemState;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("lTotalCount")
#pragma pop_macro("lHighWaterCount")
#pragma pop_macro("lSizes")
#pragma pop_macro("lCounts")
#pragma pop_macro("pBlockHeader")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DOS__CRTMEMSTATE_H */
