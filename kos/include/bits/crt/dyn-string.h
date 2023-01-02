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
#ifndef _BITS_CRT_DYN_STRING_H
#define _BITS_CRT_DYN_STRING_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#ifdef __CC__
__DECL_BEGIN

struct dyn_string {
	__STDC_INT_AS_SIZE_T allocated; /* Allocated space (# of characters, including NUL) */
	__STDC_INT_AS_SIZE_T length;    /* Used string length (w/o trailing NUL) */
	char                *s;         /* [1..length][owned] Associated string (never `NULL') */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DYN_STRING_H */
