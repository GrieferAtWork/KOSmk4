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
#ifndef _KOS_BITS_GUID_H
#define _KOS_BITS_GUID_H 1

#include <__stdinc.h>

#include <bits/types.h>


#define __OFFSET_GUID_A 0
#define __OFFSET_GUID_B 4
#define __OFFSET_GUID_C 6
#define __OFFSET_GUID_D 8
#define __OFFSET_GUID_E 10
#define __SIZEOF_GUID   16


#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("g_guid")
#pragma push_macro("g_a")
#pragma push_macro("g_b")
#pragma push_macro("g_c")
#pragma push_macro("g_d")
#pragma push_macro("g_e_1")
#pragma push_macro("g_e_2")
#pragma push_macro("g_data")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef g_guid
#undef g_a
#undef g_b
#undef g_c
#undef g_d
#undef g_e_1
#undef g_e_2
#undef g_data

/* Example: "054b1def-b2ae-4d99-a99c-54b9730c3dc3" */
typedef union __ATTR_PACKED {
	__u8       g_guid[16]; /* GUID */
	struct {
		__be32 g_a;
		__be16 g_b;
		__be16 g_c;
		__be16 g_d;
		__be32 g_e_1;
		__be16 g_e_2;
	}          g_data;
} __guid_t;

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("g_data")
#pragma pop_macro("g_e_2")
#pragma pop_macro("g_e_1")
#pragma pop_macro("g_d")
#pragma pop_macro("g_c")
#pragma pop_macro("g_b")
#pragma pop_macro("g_a")
#pragma pop_macro("g_guid")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

/* Length of the string representation of a GUID */
#define __GUID_STRLEN 36

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_BITS_GUID_H */
