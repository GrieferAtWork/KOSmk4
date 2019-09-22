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
#ifndef GUARD_LIBC_USER_UTMPX_C
#define GUARD_LIBC_USER_UTMPX_C 1

#include "../api.h"
#include "utmpx.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:setutxent,hash:CRC-32=0x916e0b96]]]*/
/* Open user accounting database */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.setutxent") void
NOTHROW_RPC(LIBCCALL libc_setutxent)(void)
/*[[[body:setutxent]]]*/
{
	CRT_UNIMPLEMENTED("setutxent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:setutxent]]]*/

/*[[[head:endutxent,hash:CRC-32=0x46023aad]]]*/
/* Close user accounting database */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.endutxent") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endutxent)(void)
/*[[[body:endutxent]]]*/
{
	CRT_UNIMPLEMENTED("endutxent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:endutxent]]]*/

/*[[[head:getutxent,hash:CRC-32=0x1c775566]]]*/
/* Get the next entry from the user accounting database */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.getutxent") struct utmpx *
NOTHROW_RPC(LIBCCALL libc_getutxent)(void)
/*[[[body:getutxent]]]*/
{
	CRT_UNIMPLEMENTED("getutxent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getutxent]]]*/

/*[[[head:getutxid,hash:CRC-32=0xb4f04635]]]*/
/* Get the user accounting database entry corresponding to ID */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.getutxid") struct utmpx *
NOTHROW_RPC(LIBCCALL libc_getutxid)(struct utmpx const *id)
/*[[[body:getutxid]]]*/
{
	CRT_UNIMPLEMENTED("getutxid"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getutxid]]]*/

/*[[[head:getutxline,hash:CRC-32=0x7eec4e9]]]*/
/* Get the user accounting database entry corresponding to LINE */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.getutxline") struct utmpx *
NOTHROW_RPC(LIBCCALL libc_getutxline)(struct utmpx const *line)
/*[[[body:getutxline]]]*/
{
	CRT_UNIMPLEMENTED("getutxline"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getutxline]]]*/

/*[[[head:pututxline,hash:CRC-32=0xad8e9fb6]]]*/
/* Write the entry UTMPX into the user accounting database */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.pututxline") struct utmpx *
NOTHROW_RPC(LIBCCALL libc_pututxline)(struct utmpx const *utmpx)
/*[[[body:pututxline]]]*/
{
	CRT_UNIMPLEMENTED("pututxline"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:pututxline]]]*/

/*[[[head:utmpxname,hash:CRC-32=0xce16f6c1]]]*/
/* Change name of the utmpx file to be examined.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.utmpxname") int
NOTHROW_RPC(LIBCCALL libc_utmpxname)(char const *file)
/*[[[body:utmpxname]]]*/
{
	CRT_UNIMPLEMENTED("utmpxname"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:utmpxname]]]*/

/*[[[head:updwtmpx,hash:CRC-32=0xb764f48b]]]*/
/* Append entry UTMP to the wtmpx-like file WTMPX_FILE.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.updwtmpx") void
NOTHROW_RPC(LIBCCALL libc_updwtmpx)(char const *wtmpx_file,
                                    struct utmpx const *utmpx)
/*[[[body:updwtmpx]]]*/
{
	CRT_UNIMPLEMENTED("updwtmpx"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:updwtmpx]]]*/

/*[[[head:getutmp,hash:CRC-32=0xf848fddb]]]*/
/* Copy the information in UTMPX to UTMP.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.getutmp") void
NOTHROW_RPC(LIBCCALL libc_getutmp)(struct utmpx const *utmpx,
                                   struct utmp *utmp)
/*[[[body:getutmp]]]*/
{
	CRT_UNIMPLEMENTED("getutmp"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:getutmp]]]*/

/*[[[head:getutmpx,hash:CRC-32=0xad602cbc]]]*/
/* Copy the information in UTMP to UTMPX.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmpx.getutmpx") void
NOTHROW_RPC(LIBCCALL libc_getutmpx)(struct utmp const *utmp,
                                    struct utmpx *utmpx)
/*[[[body:getutmpx]]]*/
{
	CRT_UNIMPLEMENTED("getutmpx"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:getutmpx]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xee1a6167]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(setutxent, libc_setutxent);
DEFINE_PUBLIC_WEAK_ALIAS(endutxent, libc_endutxent);
DEFINE_PUBLIC_WEAK_ALIAS(getutxent, libc_getutxent);
DEFINE_PUBLIC_WEAK_ALIAS(getutxid, libc_getutxid);
DEFINE_PUBLIC_WEAK_ALIAS(getutxline, libc_getutxline);
DEFINE_PUBLIC_WEAK_ALIAS(pututxline, libc_pututxline);
DEFINE_PUBLIC_WEAK_ALIAS(utmpxname, libc_utmpxname);
DEFINE_PUBLIC_WEAK_ALIAS(updwtmpx, libc_updwtmpx);
DEFINE_PUBLIC_WEAK_ALIAS(getutmp, libc_getutmp);
DEFINE_PUBLIC_WEAK_ALIAS(getutmpx, libc_getutmpx);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_UTMPX_C */
