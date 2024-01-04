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
#ifndef _BITS_CRT_DB_SERVENT_H
#define _BITS_CRT_DB_SERVENT_H 1

#include <__stdinc.h>

#ifdef __CC__
__DECL_BEGIN

/* Description of data base entry for a single service. */
struct servent {
	/* XXX: It's unclear if s_name can be NULL! */
	char                  *s_name;    /* [0..1] Official service name. */
	/* XXX: It's unclear if s_aliases can be NULL! (or is {NULL} when empty) */
	char                 **s_aliases; /* [0..1][0..n] Alias list. (List is terminated by a NULL-entry) */
	__STDC_INT32_AS_SIZE_T s_port;    /* Port number. */
	/* XXX: It's unclear if s_proto can be NULL! */
	char                  *s_proto;   /* [0..1] Protocol to use. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_SERVENT_H */
