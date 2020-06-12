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
#ifndef GUARD_LIBC_USER_ALIASES_C
#define GUARD_LIBC_USER_ALIASES_C 1

#include "../api.h"
#include "aliases.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_setaliasent,hash:CRC-32=0x42de9768]]]*/
/* Open alias data base files */
INTERN ATTR_SECTION(".text.crt.database.aliases") void
NOTHROW_RPC_KOS(LIBCCALL libc_setaliasent)(void)
/*[[[body:libc_setaliasent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("setaliasent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setaliasent]]]*/

/*[[[head:libc_endaliasent,hash:CRC-32=0x8947e081]]]*/
/* Close alias data base files */
INTERN ATTR_SECTION(".text.crt.database.aliases") void
NOTHROW_NCX(LIBCCALL libc_endaliasent)(void)
/*[[[body:libc_endaliasent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endaliasent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endaliasent]]]*/

/*[[[head:libc_getaliasent,hash:CRC-32=0xe63b925a]]]*/
/* Get the next entry from the alias data base */
INTERN ATTR_SECTION(".text.crt.database.aliases") struct aliasent *
NOTHROW_RPC_KOS(LIBCCALL libc_getaliasent)(void)
/*[[[body:libc_getaliasent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getaliasent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getaliasent]]]*/

/*[[[head:libc_getaliasent_r,hash:CRC-32=0x27b9befb]]]*/
/* Get the next entry from the alias data base and put it in RESULT_BUF */
INTERN ATTR_SECTION(".text.crt.database.aliases") NONNULL((1, 2, 4)) int
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
	CRT_UNIMPLEMENTED("getaliasent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getaliasent_r]]]*/

/*[[[head:libc_getaliasbyname,hash:CRC-32=0x809747b6]]]*/
/* Get alias entry corresponding to NAME */
INTERN ATTR_SECTION(".text.crt.database.aliases") NONNULL((1)) struct aliasent *
NOTHROW_RPC_KOS(LIBCCALL libc_getaliasbyname)(char const *name)
/*[[[body:libc_getaliasbyname]]]*/
/*AUTO*/{
	(void)name;
	CRT_UNIMPLEMENTED("getaliasbyname"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getaliasbyname]]]*/

/*[[[head:libc_getaliasbyname_r,hash:CRC-32=0x63e77e66]]]*/
/* Get alias entry corresponding to NAME and put it in RESULT_BUF */
INTERN ATTR_SECTION(".text.crt.database.aliases") NONNULL((1, 2, 3, 5)) int
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
	CRT_UNIMPLEMENTED("getaliasbyname_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_getaliasbyname_r]]]*/

/*[[[end:implementation]]]*/



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
