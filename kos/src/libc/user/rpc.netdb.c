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
#ifndef GUARD_LIBC_USER_RPC_NETDB_C
#define GUARD_LIBC_USER_RPC_NETDB_C 1

#include "../api.h"
#include "rpc.netdb.h"

DECL_BEGIN

/*[[[head:libc_setrpcent,hash:CRC-32=0xfcccd260]]]*/
INTERN ATTR_SECTION(".text.crt.net.rpc") void
NOTHROW_RPC_KOS(LIBCCALL libc_setrpcent)(int stayopen)
/*[[[body:libc_setrpcent]]]*/
/*AUTO*/{
	(void)stayopen;
	CRT_UNIMPLEMENTEDF("setrpcent(stayopen: %x)", stayopen); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setrpcent]]]*/

/*[[[head:libc_endrpcent,hash:CRC-32=0x296c9808]]]*/
INTERN ATTR_SECTION(".text.crt.net.rpc") void
NOTHROW_NCX(LIBCCALL libc_endrpcent)(void)
/*[[[body:libc_endrpcent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endrpcent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endrpcent]]]*/

/*[[[head:libc_getrpcbyname,hash:CRC-32=0x9aa80533]]]*/
INTERN ATTR_SECTION(".text.crt.net.rpc") struct rpcent *
NOTHROW_RPC_KOS(LIBCCALL libc_getrpcbyname)(char const *name)
/*[[[body:libc_getrpcbyname]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTEDF("getrpcbyname(name: %q)", name); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getrpcbyname]]]*/

/*[[[head:libc_getrpcbynumber,hash:CRC-32=0xb4c23cfa]]]*/
INTERN ATTR_SECTION(".text.crt.net.rpc") struct rpcent *
NOTHROW_RPC_KOS(LIBCCALL libc_getrpcbynumber)(int number)
/*[[[body:libc_getrpcbynumber]]]*/
/*AUTO*/{
	(void)number;
	CRT_UNIMPLEMENTEDF("getrpcbynumber(number: %x)", number); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getrpcbynumber]]]*/

/*[[[head:libc_getrpcent,hash:CRC-32=0x45fa2115]]]*/
INTERN ATTR_SECTION(".text.crt.net.rpc") struct rpcent *
NOTHROW_RPC_KOS(LIBCCALL libc_getrpcent)(void)
/*[[[body:libc_getrpcent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getrpcent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getrpcent]]]*/

/*[[[head:libc_getrpcbyname_r,hash:CRC-32=0x13ac95b]]]*/
INTERN ATTR_SECTION(".text.crt.net.rpc") int
NOTHROW_RPC_KOS(LIBCCALL libc_getrpcbyname_r)(char const *name,
                                              struct rpcent *result_buf,
                                              char *buffer,
                                              size_t buflen,
                                              struct rpcent **result)
/*[[[body:libc_getrpcbyname_r]]]*/
/*AUTO*/{
	(void)name;
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getrpcbyname_r(name: %q, result_buf: %p, buffer: %q, buflen: %Ix, result: %p)", name, result_buf, buffer, buflen, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getrpcbyname_r]]]*/

/*[[[head:libc_getrpcbynumber_r,hash:CRC-32=0xb9740fdd]]]*/
INTERN ATTR_SECTION(".text.crt.net.rpc") int
NOTHROW_RPC_KOS(LIBCCALL libc_getrpcbynumber_r)(int number,
                                                struct rpcent *result_buf,
                                                char *buffer,
                                                size_t buflen,
                                                struct rpcent **result)
/*[[[body:libc_getrpcbynumber_r]]]*/
/*AUTO*/{
	(void)number;
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getrpcbynumber_r(number: %x, result_buf: %p, buffer: %q, buflen: %Ix, result: %p)", number, result_buf, buffer, buflen, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getrpcbynumber_r]]]*/

/*[[[head:libc_getrpcent_r,hash:CRC-32=0x6b222198]]]*/
INTERN ATTR_SECTION(".text.crt.net.rpc") int
NOTHROW_RPC_KOS(LIBCCALL libc_getrpcent_r)(struct rpcent *result_buf,
                                           char *buffer,
                                           size_t buflen,
                                           struct rpcent **result)
/*[[[body:libc_getrpcent_r]]]*/
/*AUTO*/{
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getrpcent_r(result_buf: %p, buffer: %q, buflen: %Ix, result: %p)", result_buf, buffer, buflen, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getrpcent_r]]]*/





/*[[[start:exports,hash:CRC-32=0x697e5077]]]*/
DEFINE_PUBLIC_ALIAS_P_VOID(setrpcent,libc_setrpcent,,NOTHROW_RPC_KOS,LIBCCALL,(int stayopen),(stayopen));
DEFINE_PUBLIC_ALIAS_P_VOID(endrpcent,libc_endrpcent,,NOTHROW_NCX,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(getrpcbyname,libc_getrpcbyname,,struct rpcent *,NOTHROW_RPC_KOS,LIBCCALL,(char const *name),(name));
DEFINE_PUBLIC_ALIAS_P(getrpcbynumber,libc_getrpcbynumber,,struct rpcent *,NOTHROW_RPC_KOS,LIBCCALL,(int number),(number));
DEFINE_PUBLIC_ALIAS_P(getrpcent,libc_getrpcent,,struct rpcent *,NOTHROW_RPC_KOS,LIBCCALL,(void),());
DEFINE_PUBLIC_ALIAS_P(__getrpcbyname_r,libc_getrpcbyname_r,,int,NOTHROW_RPC_KOS,LIBCCALL,(char const *name, struct rpcent *result_buf, char *buffer, size_t buflen, struct rpcent **result),(name,result_buf,buffer,buflen,result));
DEFINE_PUBLIC_ALIAS_P(getrpcbyname_r,libc_getrpcbyname_r,,int,NOTHROW_RPC_KOS,LIBCCALL,(char const *name, struct rpcent *result_buf, char *buffer, size_t buflen, struct rpcent **result),(name,result_buf,buffer,buflen,result));
DEFINE_PUBLIC_ALIAS_P(__getrpcbynumber_r,libc_getrpcbynumber_r,,int,NOTHROW_RPC_KOS,LIBCCALL,(int number, struct rpcent *result_buf, char *buffer, size_t buflen, struct rpcent **result),(number,result_buf,buffer,buflen,result));
DEFINE_PUBLIC_ALIAS_P(getrpcbynumber_r,libc_getrpcbynumber_r,,int,NOTHROW_RPC_KOS,LIBCCALL,(int number, struct rpcent *result_buf, char *buffer, size_t buflen, struct rpcent **result),(number,result_buf,buffer,buflen,result));
DEFINE_PUBLIC_ALIAS_P(__getrpcent_r,libc_getrpcent_r,,int,NOTHROW_RPC_KOS,LIBCCALL,(struct rpcent *result_buf, char *buffer, size_t buflen, struct rpcent **result),(result_buf,buffer,buflen,result));
DEFINE_PUBLIC_ALIAS_P(getrpcent_r,libc_getrpcent_r,,int,NOTHROW_RPC_KOS,LIBCCALL,(struct rpcent *result_buf, char *buffer, size_t buflen, struct rpcent **result),(result_buf,buffer,buflen,result));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_RPC_NETDB_C */
