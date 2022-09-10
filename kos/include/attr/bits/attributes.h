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
#ifndef _ATTR_BITS_ATTRIBUTES_H
#define _ATTR_BITS_ATTRIBUTES_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

struct attrlist {
	__INT32_TYPE__ al_count;     /* ??? */
	__INT32_TYPE__ al_more;      /* ??? */
	__INT32_TYPE__ al_offset[1]; /* ??? */
};

struct attrlist_ent {
	__UINT32_TYPE__ a_valuelen; /* ??? */
	char            a_name[1];  /* ??? */
};

struct attrlist_cursor {
	__UINT32_TYPE__ opaque[4]; /* ??? */
};

struct attr_multiop {
	__INT32_TYPE__ am_opcode;    /* ??? */
	__INT32_TYPE__ am_error;     /* ??? */
	char          *am_attrname;  /* ??? */
	char          *am_attrvalue; /* ??? */
	__INT32_TYPE__ am_length;    /* ??? */
	__INT32_TYPE__ am_flags;     /* ??? */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_ATTR_BITS_ATTRIBUTES_H */
