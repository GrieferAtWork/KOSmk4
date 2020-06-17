/* HASH CRC-32:0x66ed68e2 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_RPC_NETDB_C
#define GUARD_LIBC_AUTO_DOSABI_RPC_NETDB_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/rpc.netdb.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.net.rpc") void
NOTHROW_RPC_KOS(LIBDCALL libd_setrpcent)(int stayopen) {
	libc_setrpcent(stayopen);
}
INTERN ATTR_SECTION(".text.crt.dos.net.rpc") struct rpcent *
NOTHROW_RPC_KOS(LIBDCALL libd_getrpcbyname)(char const *name) {
	return libc_getrpcbyname(name);
}
INTERN ATTR_SECTION(".text.crt.dos.net.rpc") struct rpcent *
NOTHROW_RPC_KOS(LIBDCALL libd_getrpcbynumber)(int number) {
	return libc_getrpcbynumber(number);
}
INTERN ATTR_SECTION(".text.crt.dos.net.rpc") int
NOTHROW_RPC_KOS(LIBDCALL libd_getrpcbyname_r)(char const *name,
                                              struct rpcent *result_buf,
                                              char *buffer,
                                              size_t buflen,
                                              struct rpcent **result) {
	return libc_getrpcbyname_r(name, result_buf, buffer, buflen, result);
}
INTERN ATTR_SECTION(".text.crt.dos.net.rpc") int
NOTHROW_RPC_KOS(LIBDCALL libd_getrpcbynumber_r)(int number,
                                                struct rpcent *result_buf,
                                                char *buffer,
                                                size_t buflen,
                                                struct rpcent **result) {
	return libc_getrpcbynumber_r(number, result_buf, buffer, buflen, result);
}
INTERN ATTR_SECTION(".text.crt.dos.net.rpc") int
NOTHROW_RPC_KOS(LIBDCALL libd_getrpcent_r)(struct rpcent *result_buf,
                                           char *buffer,
                                           size_t buflen,
                                           struct rpcent **result) {
	return libc_getrpcent_r(result_buf, buffer, buflen, result);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$setrpcent, libd_setrpcent);
DEFINE_PUBLIC_ALIAS(DOS$getrpcbyname, libd_getrpcbyname);
DEFINE_PUBLIC_ALIAS(DOS$getrpcbynumber, libd_getrpcbynumber);
DEFINE_PUBLIC_ALIAS(DOS$getrpcbyname_r, libd_getrpcbyname_r);
DEFINE_PUBLIC_ALIAS(DOS$getrpcbynumber_r, libd_getrpcbynumber_r);
DEFINE_PUBLIC_ALIAS(DOS$getrpcent_r, libd_getrpcent_r);

#endif /* !GUARD_LIBC_AUTO_DOSABI_RPC_NETDB_C */
