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
#ifndef GUARD_LIBC_USER_ALIASES_C
#define GUARD_LIBC_USER_ALIASES_C 1

#include "../api.h"
#include "aliases.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:setaliasent,hash:CRC-32=0x7aa4e8c]]]*/
/* Open alias data base files */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.aliases.setaliasent") void
NOTHROW_RPC_KOS(LIBCCALL libc_setaliasent)(void)
/*[[[body:setaliasent]]]*/
{
	CRT_UNIMPLEMENTED("setaliasent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:setaliasent]]]*/

/*[[[head:endaliasent,hash:CRC-32=0x18c47f61]]]*/
/* Close alias data base files */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.aliases.endaliasent") void
NOTHROW_NCX(LIBCCALL libc_endaliasent)(void)
/*[[[body:endaliasent]]]*/
{
	CRT_UNIMPLEMENTED("endaliasent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:endaliasent]]]*/

/*[[[head:getaliasent,hash:CRC-32=0x6c2cef2f]]]*/
/* Get the next entry from the alias data base */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.aliases.getaliasent") struct aliasent *
NOTHROW_RPC_KOS(LIBCCALL libc_getaliasent)(void)
/*[[[body:getaliasent]]]*/
{
	CRT_UNIMPLEMENTED("getaliasent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getaliasent]]]*/

/*[[[head:getaliasent_r,hash:CRC-32=0x617dd09e]]]*/
/* Get the next entry from the alias data base and put it in RESULT_BUF */
INTERN NONNULL((1, 2, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.database.aliases.getaliasent_r") int
NOTHROW_RPC_KOS(LIBCCALL libc_getaliasent_r)(struct aliasent *__restrict result_buf,
                                             char *__restrict buffer,
                                             size_t buflen,
                                             struct aliasent **__restrict result)
/*[[[body:getaliasent_r]]]*/
{
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("getaliasent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getaliasent_r]]]*/

/*[[[head:getaliasbyname,hash:CRC-32=0x592b56f1]]]*/
/* Get alias entry corresponding to NAME */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.aliases.getaliasbyname") struct aliasent *
NOTHROW_RPC_KOS(LIBCCALL libc_getaliasbyname)(char const *name)
/*[[[body:getaliasbyname]]]*/
{
	(void)name;
	CRT_UNIMPLEMENTED("getaliasbyname"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getaliasbyname]]]*/

/*[[[head:getaliasbyname_r,hash:CRC-32=0xacfc38d0]]]*/
/* Get alias entry corresponding to NAME and put it in RESULT_BUF */
INTERN NONNULL((1, 2, 3, 5))
ATTR_WEAK ATTR_SECTION(".text.crt.database.aliases.getaliasbyname_r") int
NOTHROW_RPC_KOS(LIBCCALL libc_getaliasbyname_r)(char const *__restrict name,
                                                struct aliasent *__restrict result_buf,
                                                char *__restrict buffer,
                                                size_t buflen,
                                                struct aliasent **__restrict result)
/*[[[body:getaliasbyname_r]]]*/
{
	(void)name;
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTED("getaliasbyname_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getaliasbyname_r]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x26b82686]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(setaliasent, libc_setaliasent);
DEFINE_PUBLIC_WEAK_ALIAS(endaliasent, libc_endaliasent);
DEFINE_PUBLIC_WEAK_ALIAS(getaliasent, libc_getaliasent);
DEFINE_PUBLIC_WEAK_ALIAS(getaliasent_r, libc_getaliasent_r);
DEFINE_PUBLIC_WEAK_ALIAS(getaliasbyname, libc_getaliasbyname);
DEFINE_PUBLIC_WEAK_ALIAS(getaliasbyname_r, libc_getaliasbyname_r);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ALIASES_C */
