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
#ifndef _KOS_EXCEPT_REASON_NET_H
#define _KOS_EXCEPT_REASON_NET_H 1

#include <__stdinc.h>

__DECL_BEGIN

/* Context codes for `E_INVALID_HANDLE_NET_OPERATION' exceptions */

/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_NET_ADDRESS_IN_USE_CONTEXT_GENERIC,
	E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT, /* Address already in use during `connect(2)' */
	E_NET_ADDRESS_IN_USE_CONTEXT_BIND,    /* Address already in use during `bind(2)' */
	E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN,  /* Address already in use during `listen(2)' (after `bind(2)') */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_NET_ADDRESS_IN_USE_CONTEXT_GENERIC E_NET_ADDRESS_IN_USE_CONTEXT_GENERIC
#define E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT /* Address already in use during `connect(2)' */
#define E_NET_ADDRESS_IN_USE_CONTEXT_BIND    E_NET_ADDRESS_IN_USE_CONTEXT_BIND    /* Address already in use during `bind(2)' */
#define E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN  E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN  /* Address already in use during `listen(2)' (after `bind(2)') */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_NET_ADDRESS_IN_USE_CONTEXT_GENERIC 0
#define E_NET_ADDRESS_IN_USE_CONTEXT_CONNECT 1 /* Address already in use during `connect(2)' */
#define E_NET_ADDRESS_IN_USE_CONTEXT_BIND    2 /* Address already in use during `bind(2)' */
#define E_NET_ADDRESS_IN_USE_CONTEXT_LISTEN  3 /* Address already in use during `listen(2)' (after `bind(2)') */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_NET_OPERATION_NONE,
	E_NET_OPERATION_LISTEN, /* This type of socket does not allow listen(2) operations */
	E_NET_OPERATION_ACCEPT, /* This type of socket does not allow accept(2) operations */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_NET_OPERATION_NONE   E_NET_OPERATION_NONE
#define E_NET_OPERATION_LISTEN E_NET_OPERATION_LISTEN /* This type of socket does not allow listen(2) operations */
#define E_NET_OPERATION_ACCEPT E_NET_OPERATION_ACCEPT /* This type of socket does not allow accept(2) operations */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_NET_OPERATION_NONE   0
#define E_NET_OPERATION_LISTEN 1 /* This type of socket does not allow listen(2) operations */
#define E_NET_OPERATION_ACCEPT 2 /* This type of socket does not allow accept(2) operations */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/



__DECL_END

#endif /* !_KOS_EXCEPT_REASON_NET_H */
