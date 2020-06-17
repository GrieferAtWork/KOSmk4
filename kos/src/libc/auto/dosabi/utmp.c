/* HASH CRC-32:0x3df37c95 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_UTMP_C
#define GUARD_LIBC_AUTO_DOSABI_UTMP_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/utmp.h"

DECL_BEGIN

/* Make FD be the controlling terminal, stdin, stdout, and stderr;
 * then close FD. Returns 0 on success, nonzero on error */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") int
NOTHROW_RPC_KOS(LIBDCALL libd_login_tty)(fd_t fd) {
	return libc_login_tty(fd);
}
/* Write the given entry into utmp and wtmp */
INTERN ATTR_SECTION(".text.crt.dos.database.utmp") NONNULL((1)) void
NOTHROW_RPC_KOS(LIBDCALL libd_login)(struct utmp const *entry) {
	libc_login(entry);
}
/* Write the utmp entry to say the user on UT_LINE has logged out */
INTERN ATTR_SECTION(".text.crt.dos.database.utmp") NONNULL((1)) int
NOTHROW_RPC_KOS(LIBDCALL libd_logout)(char const *ut_line) {
	return libc_logout(ut_line);
}
/* Append to wtmp an entry for the current time and the given info */
INTERN ATTR_SECTION(".text.crt.dos.database.utmp") NONNULL((1, 2, 3)) void
NOTHROW_RPC_KOS(LIBDCALL libd_logwtmp)(char const *ut_line,
                                       char const *ut_name,
                                       char const *ut_host) {
	libc_logwtmp(ut_line, ut_name, ut_host);
}
/* Append entry UTMP to the wtmp-like file WTMP_FILE */
INTERN ATTR_SECTION(".text.crt.dos.database.utmp") NONNULL((1, 2)) void
NOTHROW_RPC_KOS(LIBDCALL libd_updwtmp)(char const *wtmp_file,
                                       struct utmp const *utmp) {
	libc_updwtmp(wtmp_file, utmp);
}
/* Change name of the utmp file to be examined */
INTERN ATTR_SECTION(".text.crt.dos.database.utmp") NONNULL((1)) int
NOTHROW_RPC_KOS(LIBDCALL libd_utmpname)(char const *file) {
	return libc_utmpname(file);
}
/* Search forward from the current point in the utmp file
 * until the next entry with a ut_type matching ID->ut_type */
INTERN ATTR_SECTION(".text.crt.dos.database.utmp") NONNULL((1)) struct utmp *
NOTHROW_RPC_KOS(LIBDCALL libd_getutid)(struct utmp const *id) {
	return libc_getutid(id);
}
/* Search forward from the current point in the utmp file
 * until the next entry with a ut_line matching LINE->ut_line */
INTERN ATTR_SECTION(".text.crt.dos.database.utmp") NONNULL((1)) struct utmp *
NOTHROW_RPC_KOS(LIBDCALL libd_getutline)(struct utmp const *line) {
	return libc_getutline(line);
}
/* Write out entry pointed to by UTMP_PTR into the utmp file */
INTERN ATTR_SECTION(".text.crt.dos.database.utmp") NONNULL((1)) struct utmp *
NOTHROW_RPC_KOS(LIBDCALL libd_pututline)(struct utmp const *utmp_ptr) {
	return libc_pututline(utmp_ptr);
}
/* Reentrant versions of the file for handling utmp files */
INTERN ATTR_SECTION(".text.crt.dos.database.utmp") NONNULL((1, 2)) int
NOTHROW_RPC_KOS(LIBDCALL libd_getutent_r)(struct utmp *buffer,
                                          struct utmp **result) {
	return libc_getutent_r(buffer, result);
}
/* Reentrant versions of the file for handling utmp files */
INTERN ATTR_SECTION(".text.crt.dos.database.utmp") NONNULL((1, 2, 3)) int
NOTHROW_RPC_KOS(LIBDCALL libd_getutid_r)(struct utmp const *id,
                                         struct utmp *buffer,
                                         struct utmp **result) {
	return libc_getutid_r(id, buffer, result);
}
/* Reentrant versions of the file for handling utmp files */
INTERN ATTR_SECTION(".text.crt.dos.database.utmp") NONNULL((1, 2, 3)) int
NOTHROW_RPC_KOS(LIBDCALL libd_getutline_r)(struct utmp const *line,
                                           struct utmp *buffer,
                                           struct utmp **result) {
	return libc_getutline_r(line, buffer, result);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$login_tty, libd_login_tty);
DEFINE_PUBLIC_ALIAS(DOS$login, libd_login);
DEFINE_PUBLIC_ALIAS(DOS$logout, libd_logout);
DEFINE_PUBLIC_ALIAS(DOS$logwtmp, libd_logwtmp);
DEFINE_PUBLIC_ALIAS(DOS$updwtmp, libd_updwtmp);
DEFINE_PUBLIC_ALIAS(DOS$utmpname, libd_utmpname);
DEFINE_PUBLIC_ALIAS(DOS$getutid, libd_getutid);
DEFINE_PUBLIC_ALIAS(DOS$getutline, libd_getutline);
DEFINE_PUBLIC_ALIAS(DOS$pututline, libd_pututline);
DEFINE_PUBLIC_ALIAS(DOS$getutent_r, libd_getutent_r);
DEFINE_PUBLIC_ALIAS(DOS$getutid_r, libd_getutid_r);
DEFINE_PUBLIC_ALIAS(DOS$getutline_r, libd_getutline_r);

#endif /* !GUARD_LIBC_AUTO_DOSABI_UTMP_C */
