/* HASH CRC-32:0xd4d3c6d6 */
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
#ifndef GUARD_LIBC_USER_ARPA_INET_H
#define GUARD_LIBC_USER_ARPA_INET_H 1

#include "../api.h"
#include "../auto/arpa.inet.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <arpa/inet.h>

DECL_BEGIN

#ifndef __KERNEL__
/* TODO: Implement & document */
INTDEF char *NOTHROW_RPC_KOS(LIBCCALL libc_inet_net_ntop)(int af, void const *cp, int bits, char *buf, size_t len);
/* TODO: Implement & document */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet_net_pton)(int af, char const *cp, void *buf, size_t len);
/* TODO: Implement & document */
INTDEF unsigned int NOTHROW_RPC_KOS(LIBCCALL libc_inet_nsap_addr)(char const *cp, unsigned char *buf, int len);
/* TODO: Implement & document */
INTDEF char *NOTHROW_RPC_KOS(LIBCCALL libc_inet_nsap_ntoa)(int len, unsigned char const *cp, char *buf);
/* TODO: Implement & document */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet_pton)(int af, char const *__restrict cp, void *__restrict buf);
/* TODO: Implement & document */
INTDEF char const *NOTHROW_RPC_KOS(LIBCCALL libc_inet_ntop)(int af, void const *__restrict cp, char *__restrict buf, socklen_t len);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_ARPA_INET_H */
