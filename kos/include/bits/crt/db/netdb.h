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
#ifndef _BITS_CRT_DB_NETDB_H
#define _BITS_CRT_DB_NETDB_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("netent")
#pragma push_macro("n_name")
#pragma push_macro("n_aliases")
#pragma push_macro("n_addrtype")
#pragma push_macro("n_net")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef netent
#undef n_name
#undef n_aliases
#undef n_addrtype
#undef n_net

/*
 * C structure for describing a netword database entry from /etc/networks
 *
 * Every line from /etc/networks that isn't empty, or a comment will match
 * exactly one of the following formats:
 *
 *    n_name n_net
 *    n_name n_net n_aliases[0][ n_aliases[1][ ...[ n_aliases[N]]]]
 *
 * Where `n_net' is written in dot-notation (e.g. `127.0.0.0')
 *
 * For processing, libc uses `fparseln()' with default with `delim = "\0\0#"'
 *
 * FILES:
 *   - /etc/networks
 */
struct netent {
	char           *n_name;     /* [1..1] Official name of network. */
	char          **n_aliases;  /* [0..1][0..N] Alias list (terminated by NULL-entry). */
	int             n_addrtype; /* Net address type (always `AF_INET'). */
	__UINT32_TYPE__ n_net;      /* Network number. */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("n_net")
#pragma pop_macro("n_addrtype")
#pragma pop_macro("n_aliases")
#pragma pop_macro("n_name")
#pragma pop_macro("netent")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_NETDB_H */
