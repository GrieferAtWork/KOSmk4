/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_DB_NETDB_H
#define _BITS_CRT_DB_NETDB_H 1

#include <__stdinc.h>
#include <stdint.h>

__SYSDECL_BEGIN

#ifndef __netent_defined
#define __netent_defined 1
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
struct netent {
	char    *n_name;     /* Official name of network. */
	char   **n_aliases;  /* Alias list. */
	int      n_addrtype; /* Net address type. */
	uint32_t n_net;      /* Network number. */
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("n_net")
#pragma pop_macro("n_addrtype")
#pragma pop_macro("n_aliases")
#pragma pop_macro("n_name")
#pragma pop_macro("netent")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* !__netent_defined */

__SYSDECL_END

#endif /* !_BITS_CRT_DB_NETDB_H */
