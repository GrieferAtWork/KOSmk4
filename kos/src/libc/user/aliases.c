/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_ALIASES_C
#define GUARD_LIBC_USER_ALIASES_C 1

#include "../api.h"
#include "aliases.h"

DECL_BEGIN

/*[[[head:libc_setaliasent,hash:CRC-32=0x27a2b301]]]*/
/* >> setaliasent(3)
 * Rewind/Open the internal mail alias database file (which is located in `/etc/aliases') */
INTERN ATTR_SECTION(".text.crt.database.aliases") void
NOTHROW_RPC_KOS(LIBCCALL libc_setaliasent)(void)
/*[[[body:libc_setaliasent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("setaliasent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setaliasent]]]*/

/*[[[head:libc_endaliasent,hash:CRC-32=0x79cc160a]]]*/
/* >> endaliasent(3)
 * Close the internal mail alias database file (s.a. `setaliasent(3)') */
INTERN ATTR_SECTION(".text.crt.database.aliases") void
NOTHROW_NCX(LIBCCALL libc_endaliasent)(void)
/*[[[body:libc_endaliasent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endaliasent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endaliasent]]]*/

/*[[[head:libc_getaliasent,hash:CRC-32=0x2915d42d]]]*/
/* >> getaliasent(3)
 * Read  the  entry entry  from  the mail  alias  alias database.
 * If the database hadn't already been opened, this function will
 * open  it the same  way that a  call to `setaliasent(3)' would.
 * @return: * :   A pointer to an internal, statically allocated structure
 * @return: NULL: [errno=<unchanged>] Database end has been reached
 * @return: NULL: [errno=ENOENT]      Database end has been reached
 * @return: NULL: [errno=*]           Error */
INTERN ATTR_SECTION(".text.crt.database.aliases") WUNUSED struct aliasent *
NOTHROW_RPC_KOS(LIBCCALL libc_getaliasent)(void)
/*[[[body:libc_getaliasent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getaliasent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getaliasent]]]*/

/*[[[head:libc_getaliasent_r,hash:CRC-32=0x78c1f1fd]]]*/
/* >> getaliasent_r(3)
 * Reentrant variant of `getaliasent(3)' (s.a. similar functions such as `getpwent_r(3)') */
INTERN ATTR_SECTION(".text.crt.database.aliases") ATTR_ACCESS_WR(1) ATTR_ACCESS_WR(4) ATTR_ACCESS_WRS(2, 3) errno_t
NOTHROW_RPC_KOS(LIBCCALL libc_getaliasent_r)(struct aliasent *__restrict result_buf,
                                             char *__restrict buffer,
                                             size_t buflen,
                                             struct aliasent **__restrict result)
/*[[[body:libc_getaliasent_r]]]*/
/*AUTO*/{
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getaliasent_r(%p, %q, %Ix, %p)", result_buf, buffer, buflen, result); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_getaliasent_r]]]*/

/*[[[head:libc_getaliasbyname,hash:CRC-32=0x620b8a7f]]]*/
/* >> getaliasbyname(3)
 * Find a database entry associated with the given `name'
 * @return: * :   A pointer to an internal, statically allocated structure
 * @return: NULL: [errno=ENOENT] No entry matching `name'
 * @return: NULL: [errno=*]      Error */
INTERN ATTR_SECTION(".text.crt.database.aliases") WUNUSED ATTR_ACCESS_RO(1) struct aliasent *
NOTHROW_RPC_KOS(LIBCCALL libc_getaliasbyname)(char const *name)
/*[[[body:libc_getaliasbyname]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTEDF("getaliasbyname(%q)", name); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getaliasbyname]]]*/

/*[[[head:libc_getaliasbyname_r,hash:CRC-32=0x579244cf]]]*/
/* >> getaliasbyname_r(3)
 * Reentrant variant of `getaliasbyname(3)' (s.a. similar functions such as `getpwnam_r(3)') */
INTERN ATTR_SECTION(".text.crt.database.aliases") ATTR_ACCESS_RO(1) ATTR_ACCESS_WR(2) ATTR_ACCESS_WR(5) ATTR_ACCESS_WRS(3, 4) errno_t
NOTHROW_RPC_KOS(LIBCCALL libc_getaliasbyname_r)(char const *__restrict name,
                                                struct aliasent *__restrict result_buf,
                                                char *__restrict buffer,
                                                size_t buflen,
                                                struct aliasent **__restrict result)
/*[[[body:libc_getaliasbyname_r]]]*/
/*AUTO*/{
	(void)name;
	(void)result_buf;
	(void)buffer;
	(void)buflen;
	(void)result;
	CRT_UNIMPLEMENTEDF("getaliasbyname_r(%q, %p, %q, %Ix, %p)", name, result_buf, buffer, buflen, result); /* TODO */
	return ENOSYS;
}
/*[[[end:libc_getaliasbyname_r]]]*/





/*[[[start:exports,hash:CRC-32=0x6b7992dd]]]*/
DEFINE_PUBLIC_ALIAS(setaliasent, libc_setaliasent);
DEFINE_PUBLIC_ALIAS(endaliasent, libc_endaliasent);
DEFINE_PUBLIC_ALIAS(getaliasent, libc_getaliasent);
DEFINE_PUBLIC_ALIAS(getaliasent_r, libc_getaliasent_r);
DEFINE_PUBLIC_ALIAS(getaliasbyname, libc_getaliasbyname);
DEFINE_PUBLIC_ALIAS(getaliasbyname_r, libc_getaliasbyname_r);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ALIASES_C */
