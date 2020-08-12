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
#ifndef GUARD_LIBC_USER_UTMPX_C
#define GUARD_LIBC_USER_UTMPX_C 1

#include "../api.h"
#include "utmpx.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_setutxent,hash:CRC-32=0xaa3ffd17]]]*/
/* Open user accounting database */
INTERN ATTR_SECTION(".text.crt.database.utmpx") void
NOTHROW_RPC(LIBCCALL libc_setutxent)(void)
/*[[[body:libc_setutxent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("setutxent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setutxent]]]*/

/*[[[head:libc_endutxent,hash:CRC-32=0xa269e300]]]*/
/* Close user accounting database */
INTERN ATTR_SECTION(".text.crt.database.utmpx") void
NOTHROW_RPC_NOKOS(LIBCCALL libc_endutxent)(void)
/*[[[body:libc_endutxent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endutxent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endutxent]]]*/

/*[[[head:libc_getutxent,hash:CRC-32=0xadc1a678]]]*/
/* Get the next entry from the user accounting database */
INTERN ATTR_SECTION(".text.crt.database.utmpx") struct utmpx *
NOTHROW_RPC(LIBCCALL libc_getutxent)(void)
/*[[[body:libc_getutxent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getutxent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getutxent]]]*/

/*[[[head:libc_getutxid,hash:CRC-32=0x9cdc536e]]]*/
/* Get the user accounting database entry corresponding to ID */
INTERN ATTR_SECTION(".text.crt.database.utmpx") struct utmpx *
NOTHROW_RPC(LIBCCALL libc_getutxid)(struct utmpx const *id)
/*[[[body:libc_getutxid]]]*/
/*AUTO*/{
	(void)id;
	CRT_UNIMPLEMENTEDF("getutxid(%p)", id); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getutxid]]]*/

/*[[[head:libc_getutxline,hash:CRC-32=0x16c819a7]]]*/
/* Get the user accounting database entry corresponding to LINE */
INTERN ATTR_SECTION(".text.crt.database.utmpx") struct utmpx *
NOTHROW_RPC(LIBCCALL libc_getutxline)(struct utmpx const *line)
/*[[[body:libc_getutxline]]]*/
/*AUTO*/{
	(void)line;
	CRT_UNIMPLEMENTEDF("getutxline(%p)", line); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getutxline]]]*/

/*[[[head:libc_pututxline,hash:CRC-32=0x25e30005]]]*/
/* Write the entry UTMPX into the user accounting database */
INTERN ATTR_SECTION(".text.crt.database.utmpx") struct utmpx *
NOTHROW_RPC(LIBCCALL libc_pututxline)(struct utmpx const *utmpx)
/*[[[body:libc_pututxline]]]*/
/*AUTO*/{
	(void)utmpx;
	CRT_UNIMPLEMENTEDF("pututxline(%p)", utmpx); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_pututxline]]]*/

/*[[[head:libc_utmpxname,hash:CRC-32=0x86d75556]]]*/
/* Change name of the utmpx file to be examined.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.utmpx") int
NOTHROW_RPC(LIBCCALL libc_utmpxname)(char const *file)
/*[[[body:libc_utmpxname]]]*/
/*AUTO*/{
	(void)file;
	CRT_UNIMPLEMENTEDF("utmpxname(%q)", file); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_utmpxname]]]*/

/*[[[head:libc_updwtmpx,hash:CRC-32=0x5d0f5568]]]*/
/* Append entry UTMP to the wtmpx-like file WTMPX_FILE.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.utmpx") void
NOTHROW_RPC(LIBCCALL libc_updwtmpx)(char const *wtmpx_file,
                                    struct utmpx const *utmpx)
/*[[[body:libc_updwtmpx]]]*/
/*AUTO*/{
	(void)wtmpx_file;
	(void)utmpx;
	CRT_UNIMPLEMENTEDF("updwtmpx(%q, %p)", wtmpx_file, utmpx); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_updwtmpx]]]*/

/*[[[head:libc_getutmp,hash:CRC-32=0x340a01bf]]]*/
/* Copy the information in UTMPX to UTMP.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.utmpx") void
NOTHROW_RPC(LIBCCALL libc_getutmp)(struct utmpx const *utmpx,
                                   struct utmp *utmp)
/*[[[body:libc_getutmp]]]*/
/*AUTO*/{
	(void)utmpx;
	(void)utmp;
	CRT_UNIMPLEMENTEDF("getutmp(%p, %p)", utmpx, utmp); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_getutmp]]]*/

/*[[[head:libc_getutmpx,hash:CRC-32=0x85da6b1d]]]*/
/* Copy the information in UTMP to UTMPX.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.database.utmpx") void
NOTHROW_RPC(LIBCCALL libc_getutmpx)(struct utmp const *utmp,
                                    struct utmpx *utmpx)
/*[[[body:libc_getutmpx]]]*/
/*AUTO*/{
	(void)utmp;
	(void)utmpx;
	CRT_UNIMPLEMENTEDF("getutmpx(%p, %p)", utmp, utmpx); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_getutmpx]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x570fae3d]]]*/
DEFINE_PUBLIC_ALIAS(setutxent, libc_setutxent);
DEFINE_PUBLIC_ALIAS(endutxent, libc_endutxent);
DEFINE_PUBLIC_ALIAS(getutxent, libc_getutxent);
DEFINE_PUBLIC_ALIAS(getutxid, libc_getutxid);
DEFINE_PUBLIC_ALIAS(getutxline, libc_getutxline);
DEFINE_PUBLIC_ALIAS(pututxline, libc_pututxline);
DEFINE_PUBLIC_ALIAS(utmpxname, libc_utmpxname);
DEFINE_PUBLIC_ALIAS(updwtmpx, libc_updwtmpx);
DEFINE_PUBLIC_ALIAS(getutmp, libc_getutmp);
DEFINE_PUBLIC_ALIAS(getutmpx, libc_getutmpx);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_UTMPX_C */
