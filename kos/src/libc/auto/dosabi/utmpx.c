/* HASH CRC-32:0x57bf4e69 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_UTMPX_C
#define GUARD_LIBC_AUTO_DOSABI_UTMPX_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/utmpx.h"

DECL_BEGIN

/* Get the user accounting database entry corresponding to ID */
INTERN ATTR_SECTION(".text.crt.dos.database.utmpx") struct utmpx *
NOTHROW_RPC(LIBDCALL libd_getutxid)(struct utmpx const *id) {
	return libc_getutxid(id);
}
/* Get the user accounting database entry corresponding to LINE */
INTERN ATTR_SECTION(".text.crt.dos.database.utmpx") struct utmpx *
NOTHROW_RPC(LIBDCALL libd_getutxline)(struct utmpx const *line) {
	return libc_getutxline(line);
}
/* Write the entry UTMPX into the user accounting database */
INTERN ATTR_SECTION(".text.crt.dos.database.utmpx") struct utmpx *
NOTHROW_RPC(LIBDCALL libd_pututxline)(struct utmpx const *utmpx) {
	return libc_pututxline(utmpx);
}
/* Change name of the utmpx file to be examined.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.database.utmpx") int
NOTHROW_RPC(LIBDCALL libd_utmpxname)(char const *file) {
	return libc_utmpxname(file);
}
/* Append entry UTMP to the wtmpx-like file WTMPX_FILE.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.database.utmpx") void
NOTHROW_RPC(LIBDCALL libd_updwtmpx)(char const *wtmpx_file,
                                    struct utmpx const *utmpx) {
	libc_updwtmpx(wtmpx_file, utmpx);
}
/* Copy the information in UTMPX to UTMP.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.database.utmpx") void
NOTHROW_RPC(LIBDCALL libd_getutmp)(struct utmpx const *utmpx,
                                   struct utmp *utmp) {
	libc_getutmp(utmpx, utmp);
}
/* Copy the information in UTMP to UTMPX.
 * This function is not part of POSIX and therefore no official cancellation point */
INTERN ATTR_SECTION(".text.crt.dos.database.utmpx") void
NOTHROW_RPC(LIBDCALL libd_getutmpx)(struct utmp const *utmp,
                                    struct utmpx *utmpx) {
	libc_getutmpx(utmp, utmpx);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$getutxid, libd_getutxid);
DEFINE_PUBLIC_ALIAS(DOS$getutxline, libd_getutxline);
DEFINE_PUBLIC_ALIAS(DOS$pututxline, libd_pututxline);
DEFINE_PUBLIC_ALIAS(DOS$utmpxname, libd_utmpxname);
DEFINE_PUBLIC_ALIAS(DOS$updwtmpx, libd_updwtmpx);
DEFINE_PUBLIC_ALIAS(DOS$getutmp, libd_getutmp);
DEFINE_PUBLIC_ALIAS(DOS$getutmpx, libd_getutmpx);

#endif /* !GUARD_LIBC_AUTO_DOSABI_UTMPX_C */
