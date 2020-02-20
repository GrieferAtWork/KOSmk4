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
#ifndef _BITS_SOCKADDR_STRUCT_H
#define _BITS_SOCKADDR_STRUCT_H 1

#include <__stdinc.h>

/* Structure describing a generic socket address. */
#ifdef __CC__
#ifndef __sockaddr_defined
#define __sockaddr_defined 1
#include <bits/sockaddr.h>
__DECL_BEGIN
struct sockaddr {
	__SOCKADDR_COMMON(sa_); /* Common data: address family and length. */
	char sa_data[14];       /* Address data. */
};
__DECL_END
#endif /* !__sockaddr_defined */
#endif /* __CC__ */

#endif /* !_BITS_SOCKADDR_STRUCT_H */
