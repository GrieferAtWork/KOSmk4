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
#ifndef GUARD_LIBC_USER_UTMP_C
#define GUARD_LIBC_USER_UTMP_C 1

#include "../api.h"
#include "utmp.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:login_tty,hash:CRC-32=0x1bf4e7e3]]]*/
/* Make FD be the controlling terminal, stdin, stdout, and stderr;
 * then close FD. Returns 0 on success, nonzero on error */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.login_tty") int
NOTHROW_RPC_KOS(LIBCCALL libc_login_tty)(fd_t fd)
/*[[[body:login_tty]]]*/
{
	CRT_UNIMPLEMENTED("login_tty"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:login_tty]]]*/

/*[[[head:login,hash:CRC-32=0x865e839a]]]*/
/* Write the given entry into utmp and wtmp */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.login") void
NOTHROW_RPC_KOS(LIBCCALL libc_login)(struct utmp const *entry)
/*[[[body:login]]]*/
{
	CRT_UNIMPLEMENTED("login"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:login]]]*/

/*[[[head:logout,hash:CRC-32=0x232da6a6]]]*/
/* Write the utmp entry to say the user on UT_LINE has logged out */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.logout") int
NOTHROW_RPC_KOS(LIBCCALL libc_logout)(char const *ut_line)
/*[[[body:logout]]]*/
{
	CRT_UNIMPLEMENTED("logout"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:logout]]]*/

/*[[[head:logwtmp,hash:CRC-32=0x8fe820d9]]]*/
/* Append to wtmp an entry for the current time and the given info */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.logwtmp") void
NOTHROW_RPC_KOS(LIBCCALL libc_logwtmp)(char const *ut_line,
                                       char const *ut_name,
                                       char const *ut_host)
/*[[[body:logwtmp]]]*/
{
	CRT_UNIMPLEMENTED("logwtmp"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:logwtmp]]]*/

/*[[[head:updwtmp,hash:CRC-32=0x14e3ef78]]]*/
/* Append entry UTMP to the wtmp-like file WTMP_FILE */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.updwtmp") void
NOTHROW_RPC_KOS(LIBCCALL libc_updwtmp)(char const *wtmp_file,
                                       struct utmp const *utmp)
/*[[[body:updwtmp]]]*/
{
	CRT_UNIMPLEMENTED("updwtmp"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:updwtmp]]]*/

/*[[[head:utmpname,hash:CRC-32=0x7e197479]]]*/
/* Change name of the utmp file to be examined */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.utmpname") int
NOTHROW_RPC_KOS(LIBCCALL libc_utmpname)(char const *file)
/*[[[body:utmpname]]]*/
{
	CRT_UNIMPLEMENTED("utmpname"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:utmpname]]]*/

/*[[[head:getutent,hash:CRC-32=0xe9817520]]]*/
/* Read next entry from a utmp-like file */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.getutent") struct utmp *
NOTHROW_RPC_KOS(LIBCCALL libc_getutent)(void)
/*[[[body:getutent]]]*/
{
	CRT_UNIMPLEMENTED("getutent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getutent]]]*/

/*[[[head:setutent,hash:CRC-32=0x6cb582bb]]]*/
/* Reset the input stream to the beginning of the file */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.setutent") void
NOTHROW_RPC_KOS(LIBCCALL libc_setutent)(void)
/*[[[body:setutent]]]*/
{
	CRT_UNIMPLEMENTED("setutent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:setutent]]]*/

/*[[[head:endutent,hash:CRC-32=0x6784bc4b]]]*/
/* Close the current open file */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.endutent") void
NOTHROW_NCX(LIBCCALL libc_endutent)(void)
/*[[[body:endutent]]]*/
{
	CRT_UNIMPLEMENTED("endutent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:endutent]]]*/

/*[[[head:getutid,hash:CRC-32=0x425c0421]]]*/
/* Search forward from the current point in the utmp file
 * until the next entry with a ut_type matching ID->ut_type */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.getutid") struct utmp *
NOTHROW_RPC_KOS(LIBCCALL libc_getutid)(struct utmp const *id)
/*[[[body:getutid]]]*/
{
	CRT_UNIMPLEMENTED("getutid"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getutid]]]*/

/*[[[head:getutline,hash:CRC-32=0x4ace86dd]]]*/
/* Search forward from the current point in the utmp file
 * until the next entry with a ut_line matching LINE->ut_line */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.getutline") struct utmp *
NOTHROW_RPC_KOS(LIBCCALL libc_getutline)(struct utmp const *line)
/*[[[body:getutline]]]*/
{
	CRT_UNIMPLEMENTED("getutline"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:getutline]]]*/

/*[[[head:pututline,hash:CRC-32=0x79dbc6fc]]]*/
/* Write out entry pointed to by UTMP_PTR into the utmp file */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.pututline") struct utmp *
NOTHROW_RPC_KOS(LIBCCALL libc_pututline)(struct utmp const *utmp_ptr)
/*[[[body:pututline]]]*/
{
	CRT_UNIMPLEMENTED("pututline"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:pututline]]]*/

/*[[[head:getutent_r,hash:CRC-32=0xcf0e8f9d]]]*/
/* Reentrant versions of the file for handling utmp files */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.getutent_r") int
NOTHROW_RPC_KOS(LIBCCALL libc_getutent_r)(struct utmp *buffer,
                                          struct utmp **result)
/*[[[body:getutent_r]]]*/
{
	CRT_UNIMPLEMENTED("getutent_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getutent_r]]]*/

/*[[[head:getutid_r,hash:CRC-32=0x8c7a81b1]]]*/
/* Reentrant versions of the file for handling utmp files */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.getutid_r") int
NOTHROW_RPC_KOS(LIBCCALL libc_getutid_r)(struct utmp const *id,
                                         struct utmp *buffer,
                                         struct utmp **result)
/*[[[body:getutid_r]]]*/
{
	CRT_UNIMPLEMENTED("getutid_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getutid_r]]]*/

/*[[[head:getutline_r,hash:CRC-32=0xb2d7fc9b]]]*/
/* Reentrant versions of the file for handling utmp files */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.database.utmp.getutline_r") int
NOTHROW_RPC_KOS(LIBCCALL libc_getutline_r)(struct utmp const *line,
                                           struct utmp *buffer,
                                           struct utmp **result)
/*[[[body:getutline_r]]]*/
{
	CRT_UNIMPLEMENTED("getutline_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getutline_r]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x705431a9]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(login_tty, libc_login_tty);
DEFINE_PUBLIC_WEAK_ALIAS(login, libc_login);
DEFINE_PUBLIC_WEAK_ALIAS(logout, libc_logout);
DEFINE_PUBLIC_WEAK_ALIAS(logwtmp, libc_logwtmp);
DEFINE_PUBLIC_WEAK_ALIAS(updwtmp, libc_updwtmp);
DEFINE_PUBLIC_WEAK_ALIAS(utmpname, libc_utmpname);
DEFINE_PUBLIC_WEAK_ALIAS(getutent, libc_getutent);
DEFINE_PUBLIC_WEAK_ALIAS(setutent, libc_setutent);
DEFINE_PUBLIC_WEAK_ALIAS(endutent, libc_endutent);
DEFINE_PUBLIC_WEAK_ALIAS(getutid, libc_getutid);
DEFINE_PUBLIC_WEAK_ALIAS(getutline, libc_getutline);
DEFINE_PUBLIC_WEAK_ALIAS(pututline, libc_pututline);
DEFINE_PUBLIC_WEAK_ALIAS(getutent_r, libc_getutent_r);
DEFINE_PUBLIC_WEAK_ALIAS(getutid_r, libc_getutid_r);
DEFINE_PUBLIC_WEAK_ALIAS(getutline_r, libc_getutline_r);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_UTMP_C */
