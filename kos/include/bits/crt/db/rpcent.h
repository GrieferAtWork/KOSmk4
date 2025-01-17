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
#ifndef _BITS_CRT_DB_RPCENT_H
#define _BITS_CRT_DB_RPCENT_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>
#include <features.h>

#ifdef __CC__
__DECL_BEGIN

/* Structure of the password file. */
struct rpcent {
	/* XXX: It's unclear if r_name can be NULL! */
	char                 *r_name;    /* Name of server for this rpc program. */
	/* XXX: It's unclear if r_aliases can be NULL! (or is {NULL} when empty) */
	char                **r_aliases; /* [0..1][0..n] Alias list. (terminated by a NULL-entry) */
	__STDC_INT_AS_SSIZE_T r_number;  /* RPC program number. */
#if __SIZEOF_POINTER__ > __SIZEOF_INT__
	__BYTE_TYPE__       __r_pad[__SIZEOF_POINTER__ - __SIZEOF_INT__];
#endif /* __SIZEOF_POINTER__ > __SIZEOF_INT__ */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_RPCENT_H */
