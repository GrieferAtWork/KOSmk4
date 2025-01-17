/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_MALLINFO_H
#define _BITS_CRT_MALLINFO_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#undef _MALLINFO_MATCHES_MALLINFO2
#if __SIZEOF_INT__ == __SIZEOF_SIZE_T__
#define _MALLINFO_MATCHES_MALLINFO2
#endif /* __SIZEOF_INT__ == __SIZEOF_SIZE_T__ */

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("arena")
#pragma push_macro("ordblks")
#pragma push_macro("smblks")
#pragma push_macro("hblks")
#pragma push_macro("hblkhd")
#pragma push_macro("usmblks")
#pragma push_macro("fsmblks")
#pragma push_macro("uordblks")
#pragma push_macro("fordblks")
#pragma push_macro("keepcost")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef arena
#undef ordblks
#undef smblks
#undef hblks
#undef hblkhd
#undef usmblks
#undef fsmblks
#undef uordblks
#undef fordblks
#undef keepcost

#ifndef _STRUCT_MALLINFO
#define _STRUCT_MALLINFO
struct mallinfo {
	int arena;    /* non-mmapped space allocated from system */
	int ordblks;  /* number of free chunks */
	int smblks;   /* always 0 */
	int hblks;    /* always 0 */
	int hblkhd;   /* space in mmapped regions */
	int usmblks;  /* maximum total allocated space */
	int fsmblks;  /* always 0 */
	int uordblks; /* total allocated space */
	int fordblks; /* total free space */
	int keepcost; /* releasable (via malloc_trim) space */
};
#endif /* !_STRUCT_MALLINFO */

#ifndef _STRUCT_MALLINFO2
#define _STRUCT_MALLINFO2
struct mallinfo2 {
	__SIZE_TYPE__ arena;    /* non-mmapped space allocated from system (bytes) */
	__SIZE_TYPE__ ordblks;  /* number of free chunks */
	__SIZE_TYPE__ smblks;   /* always 0 */
	__SIZE_TYPE__ hblks;    /* always 0 */
	__SIZE_TYPE__ hblkhd;   /* space in mmapped regions (bytes) */
	__SIZE_TYPE__ usmblks;  /* maximum total allocated space */
	__SIZE_TYPE__ fsmblks;  /* always 0 */
	__SIZE_TYPE__ uordblks; /* total allocated space (bytes) */
	__SIZE_TYPE__ fordblks; /* total free space (bytes) */
	__SIZE_TYPE__ keepcost; /* releasable (via malloc_trim) space (bytes) */
};
#endif /* !_STRUCT_MALLINFO2 */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("keepcost")
#pragma pop_macro("fordblks")
#pragma pop_macro("uordblks")
#pragma pop_macro("fsmblks")
#pragma pop_macro("usmblks")
#pragma pop_macro("hblkhd")
#pragma pop_macro("hblks")
#pragma pop_macro("smblks")
#pragma pop_macro("ordblks")
#pragma pop_macro("arena")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_MALLINFO_H */
