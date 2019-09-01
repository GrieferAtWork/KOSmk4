/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_LIBC_USER_RPC_NETDB_C
#define GUARD_LIBC_USER_RPC_NETDB_C 1

#include "../api.h"
#include "rpc.netdb.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:setrpcent,hash:0xab02e582]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.rpc.setrpcent") void
NOTHROW_RPC_KOS(LIBCCALL libc_setrpcent)(int stayopen)
/*[[[body:setrpcent]]]*/
{
	CRT_UNIMPLEMENTED("setrpcent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:setrpcent]]]*/

/*[[[head:endrpcent,hash:0xfb0674bd]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.rpc.endrpcent") void
NOTHROW_NCX(LIBCCALL libc_endrpcent)(void)
/*[[[body:endrpcent]]]*/
{
	CRT_UNIMPLEMENTED("endrpcent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:endrpcent]]]*/

/*[[[head:getrpcbyname,hash:0x4581a157]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.rpc.getrpcbyname") struct rpcent *
NOTHROW_RPC_KOS(LIBCCALL libc_getrpcbyname)(char const *name)
/*[[[body:getrpcbyname]]]*/
{
	CRT_UNIMPLEMENTED("getrpcbyname"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getrpcbyname]]]*/

/*[[[head:getrpcbynumber,hash:0x32a57e33]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.rpc.getrpcbynumber") struct rpcent *
NOTHROW_RPC_KOS(LIBCCALL libc_getrpcbynumber)(int number)
/*[[[body:getrpcbynumber]]]*/
{
	CRT_UNIMPLEMENTED("getrpcbynumber"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getrpcbynumber]]]*/

/*[[[head:getrpcent,hash:0x2a995cba]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.rpc.getrpcent") struct rpcent *
NOTHROW_RPC_KOS(LIBCCALL libc_getrpcent)(void)
/*[[[body:getrpcent]]]*/
{
	CRT_UNIMPLEMENTED("getrpcent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getrpcent]]]*/

/*[[[head:getrpcbyname_r,hash:0xeb7e2784]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.rpc.getrpcbyname_r") int
NOTHROW_RPC_KOS(LIBCCALL libc_getrpcbyname_r)(char const *name,
                                              struct rpcent *result_buf,
                                              char *buffer,
                                              size_t buflen,
                                              struct rpcent **result)
/*[[[body:getrpcbyname_r]]]*/
{
	CRT_UNIMPLEMENTED("getrpcbyname_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getrpcbyname_r]]]*/

/*[[[head:getrpcbynumber_r,hash:0xf2fdaa07]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.rpc.getrpcbynumber_r") int
NOTHROW_RPC_KOS(LIBCCALL libc_getrpcbynumber_r)(int number,
                                                struct rpcent *result_buf,
                                                char *buffer,
                                                size_t buflen,
                                                struct rpcent **result)
/*[[[body:getrpcbynumber_r]]]*/
{
	CRT_UNIMPLEMENTED("getrpcbynumber_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getrpcbynumber_r]]]*/

/*[[[head:getrpcent_r,hash:0xd080ce5e]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.rpc.getrpcent_r") int
NOTHROW_RPC_KOS(LIBCCALL libc_getrpcent_r)(struct rpcent *result_buf,
                                           char *buffer,
                                           size_t buflen,
                                           struct rpcent **result)
/*[[[body:getrpcent_r]]]*/
{
	CRT_UNIMPLEMENTED("getrpcent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getrpcent_r]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x45275b21]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(setrpcent, libc_setrpcent);
DEFINE_PUBLIC_WEAK_ALIAS(endrpcent, libc_endrpcent);
DEFINE_PUBLIC_WEAK_ALIAS(getrpcbyname, libc_getrpcbyname);
DEFINE_PUBLIC_WEAK_ALIAS(getrpcbynumber, libc_getrpcbynumber);
DEFINE_PUBLIC_WEAK_ALIAS(getrpcent, libc_getrpcent);
DEFINE_PUBLIC_WEAK_ALIAS(getrpcbyname_r, libc_getrpcbyname_r);
DEFINE_PUBLIC_WEAK_ALIAS(getrpcbynumber_r, libc_getrpcbynumber_r);
DEFINE_PUBLIC_WEAK_ALIAS(getrpcent_r, libc_getrpcent_r);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_RPC_NETDB_C */
