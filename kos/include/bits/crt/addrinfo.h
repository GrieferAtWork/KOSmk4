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
#ifndef _BITS_CRT_ADDRINFO_H
#define _BITS_CRT_ADDRINFO_H 1

#include <__stdinc.h>
#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

/* Structure to contain information about address of a service provider. */
struct sockaddr;
struct addrinfo;
struct addrinfo {
	int              ai_flags;     /* Input flags. */
	int              ai_family;    /* Protocol family for socket. */
	int              ai_socktype;  /* Socket type. */
	int              ai_protocol;  /* Protocol for socket. */
	__socklen_t      ai_addrlen;   /* Length of socket address. */
	struct sockaddr *ai_addr;      /* [0..ai_addrlen] Socket address for socket. */
	char            *ai_canonname; /* [0..1] Canonical name for service location (or NULL if not requested; s.a. `AI_CANONNAME'). */
	struct addrinfo *ai_next;      /* [0..1] Pointer to next in list. (or NULL for the last entry) */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_ADDRINFO_H */
