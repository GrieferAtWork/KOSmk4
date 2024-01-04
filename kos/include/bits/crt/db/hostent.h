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
#ifndef _BITS_CRT_DB_HOSTENT_H
#define _BITS_CRT_DB_HOSTENT_H 1

#include <__stdinc.h>
#include <features.h>

#ifdef __CC__
__DECL_BEGIN


/* Description of data base entry for a single host. */
struct hostent {
	/* XXX: It's unclear if h_name can be NULL! */
	char                   *h_name;      /* [0..1] Official name of host. */
	/* XXX: It's unclear if h_aliases can be NULL! (or is {NULL} when empty) */
	char                  **h_aliases;   /* [0..1][0..n] Alias list. (List is terminated by a NULL-entry) */
	int                     h_addrtype;  /* Host address type (One of `AF_*'; e.g. AF_INET or AF_INET6). */
	__STDC_INT_AS_SIZE_T    h_length;    /* Length of the address (in bytes). */
#ifdef __USE_MISC
#ifdef __INTELLISENSE__ /* Better syntax highlighting */
	union {
		char              **h_addr_list; /* [0..1][1..n] List of addresses from name server. (List is terminated by a NULL-entry) */
		char               *h_addr;      /* [1..1] Address, for backward compatibility. */
	};
#else /* __INTELLISENSE__ */
	char                  **h_addr_list; /* [0..1][1..n] List of addresses from name server. (List is terminated by a NULL-entry) */
#define                     h_addr       h_addr_list[0] /* [1..1] Address, for backward compatibility. */
#endif /* !__INTELLISENSE__ */
#else /* __USE_MISC */
	char                  **h_addr_list; /* [0..1][1..n] List of addresses from name server. (List is terminated by a NULL-entry) */
#endif /* !__USE_MISC */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_HOSTENT_H */
