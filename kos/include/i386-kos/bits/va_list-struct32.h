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
#ifndef _I386_KOS_BITS_VA_LIST_STRUCT32_H
#define _I386_KOS_BITS_VA_LIST_STRUCT32_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

/* typedef struct va_list_struct *va_list; */
#ifndef __x86_64__
#define i386_va_list_struct va_list_struct
#endif /* !__x86_64__ */

#ifdef __CC__
__DECL_BEGIN

struct i386_va_list_struct {
	/* Inline array of  4-byte-aligned arguments.  - va_arg() modifies  the value  of the  given
	 * va_list object itself (which is a pointer) to point to the next argument before returning
	 * the previous one. - The size of  any given argument `T' is always  `(sizeof(T) + 3) & ~3' */
	__UINT32_TYPE__ vl_args[1024];
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_BITS_VA_LIST_STRUCT32_H */
