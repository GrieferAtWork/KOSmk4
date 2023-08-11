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
#ifndef _BITS_CRT_IF_NAMEINDEX_H
#define _BITS_CRT_IF_NAMEINDEX_H 1

#include <__stdinc.h>
#include <features.h>

#ifdef __CC__
__DECL_BEGIN

struct if_nameindex {
	__STDC_UINT_AS_SIZE_T if_index; /* Interface index */
	char                 *if_name;  /* [1..1] Interface name (e.g. "eth0"). List is terminated by NULL-entry */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_IF_NAMEINDEX_H */
