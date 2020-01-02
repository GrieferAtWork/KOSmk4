/* HASH CRC-32:0x3571fb63 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_RPC_NETDB_H
#define GUARD_LIBC_USER_RPC_NETDB_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <rpc/netdb.h>

DECL_BEGIN

INTDEF void NOTHROW_RPC_KOS(LIBCCALL libc_setrpcent)(int stayopen);
INTDEF void NOTHROW_NCX(LIBCCALL libc_endrpcent)(void);
INTDEF struct rpcent *NOTHROW_RPC_KOS(LIBCCALL libc_getrpcbyname)(char const *name);
INTDEF struct rpcent *NOTHROW_RPC_KOS(LIBCCALL libc_getrpcbynumber)(int number);
INTDEF struct rpcent *NOTHROW_RPC_KOS(LIBCCALL libc_getrpcent)(void);
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_getrpcbyname_r)(char const *name, struct rpcent *result_buf, char *buffer, size_t buflen, struct rpcent **result);
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_getrpcbynumber_r)(int number, struct rpcent *result_buf, char *buffer, size_t buflen, struct rpcent **result);
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_getrpcent_r)(struct rpcent *result_buf, char *buffer, size_t buflen, struct rpcent **result);

DECL_END

#endif /* !GUARD_LIBC_USER_RPC_NETDB_H */
