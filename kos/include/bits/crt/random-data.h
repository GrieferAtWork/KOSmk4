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
#ifndef _BITS_CRT_RANDOM_DATA_H
#define _BITS_CRT_RANDOM_DATA_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

struct drand48_data {
	unsigned short __x[3];
	unsigned short __old_x[3];
	unsigned short __c;
	unsigned short __init;
	__ULONGLONG    __a;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("fptr")
#pragma push_macro("rptr")
#pragma push_macro("state")
#pragma push_macro("rand_type")
#pragma push_macro("rand_deg")
#pragma push_macro("rand_sep")
#pragma push_macro("end_ptr")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef fptr
#undef rptr
#undef state
#undef rand_type
#undef rand_deg
#undef rand_sep
#undef end_ptr

struct random_data {
	__INT32_TYPE__ *fptr;
	__INT32_TYPE__ *rptr;
	__INT32_TYPE__ *state;
	int             rand_type;
	int             rand_deg;
	int             rand_sep;
	__INT32_TYPE__ *end_ptr;
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("end_ptr")
#pragma pop_macro("rand_sep")
#pragma pop_macro("rand_deg")
#pragma pop_macro("rand_type")
#pragma pop_macro("state")
#pragma pop_macro("rptr")
#pragma pop_macro("fptr")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_RANDOM_DATA_H */
