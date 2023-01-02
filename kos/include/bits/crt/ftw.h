/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_FTW_H
#define _BITS_CRT_FTW_H 1

#include <__stdinc.h>
#include <features.h>

/* Values for `typeflag', as passed to ftw-callbacks */
#define __FTW_F   0 /* ??? */
#define __FTW_D   1 /* ??? */
#define __FTW_DNR 2 /* ??? */
#define __FTW_NS  3 /* ??? */
#define __FTW_SL  4 /* ??? */
#define __FTW_DP  5 /* ??? Only for nftw(3) */
#define __FTW_SLN 6 /* ??? Only for nftw(3) */

/* Values returned by user-defined callbacks (e.g. `__ftw_func_t'). */
#define __FTW_CONTINUE      0 /* ??? */
#define __FTW_STOP          1 /* ??? */
#define __FTW_SKIP_SUBTREE  2 /* ??? */
#define __FTW_SKIP_SIBLINGS 3 /* ??? */

/* Values for `nftw(3)::descriptors' */
#define __FTW_PHYS         0x01 /* ??? */
#define __FTW_MOUNT        0x02 /* ??? */
#define __FTW_CHDIR        0x04 /* ??? */
#define __FTW_DEPTH        0x08 /* ??? */
#define __FTW_ACTIONRETVAL 0x10 /* ??? */

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("base")
#pragma push_macro("level")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef base
#undef level

#ifdef __USE_XOPEN_EXTENDED
#define __FTW FTW
struct FTW
#else /* __USE_XOPEN_EXTENDED */
struct __FTW
#endif /* !__USE_XOPEN_EXTENDED */
{
	int base;
	int level;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("level")
#pragma pop_macro("base")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_FTW_H */
