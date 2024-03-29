/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_UTMP_C
#define GUARD_LIBC_USER_UTMP_C 1

#include "../api.h"
#include "utmp.h"

DECL_BEGIN

/*[[[head:libc_login,hash:CRC-32=0xdfff61b6]]]*/
/* >> login(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") ATTR_IN(1) void
NOTHROW_RPC_KOS(LIBCCALL libc_login)(struct utmp const *entry)
/*[[[body:libc_login]]]*/
/*AUTO*/{
	(void)entry;
	CRT_UNIMPLEMENTEDF("login(entry: %p)", entry); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_login]]]*/

/*[[[head:libc_logout,hash:CRC-32=0xb2784cb8]]]*/
/* >> logout(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") ATTR_IN(1) int
NOTHROW_RPC_KOS(LIBCCALL libc_logout)(char const *ut_line)
/*[[[body:libc_logout]]]*/
/*AUTO*/{
	(void)ut_line;
	CRT_UNIMPLEMENTEDF("logout(ut_line: %q)", ut_line); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_logout]]]*/

/*[[[head:libc_logwtmp,hash:CRC-32=0xaffc193f]]]*/
/* >> logwtmp(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) void
NOTHROW_RPC_KOS(LIBCCALL libc_logwtmp)(char const *ut_line,
                                       char const *ut_name,
                                       char const *ut_host)
/*[[[body:libc_logwtmp]]]*/
/*AUTO*/{
	(void)ut_line;
	(void)ut_name;
	(void)ut_host;
	CRT_UNIMPLEMENTEDF("logwtmp(ut_line: %q, ut_name: %q, ut_host: %q)", ut_line, ut_name, ut_host); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_logwtmp]]]*/

/*[[[head:libc_updwtmp,hash:CRC-32=0xe3b8ecb5]]]*/
/* >> updwtmp(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") ATTR_IN(1) ATTR_IN(2) void
NOTHROW_RPC_KOS(LIBCCALL libc_updwtmp)(char const *wtmp_file,
                                       struct utmp const *utmp)
/*[[[body:libc_updwtmp]]]*/
/*AUTO*/{
	(void)wtmp_file;
	(void)utmp;
	CRT_UNIMPLEMENTEDF("updwtmp(wtmp_file: %q, utmp: %p)", wtmp_file, utmp); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_updwtmp]]]*/

/*[[[head:libc_utmpname,hash:CRC-32=0x9fcf61a9]]]*/
/* >> utmpname(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") ATTR_IN(1) int
NOTHROW_RPC_KOS(LIBCCALL libc_utmpname)(char const *file)
/*[[[body:libc_utmpname]]]*/
/*AUTO*/{
	(void)file;
	CRT_UNIMPLEMENTEDF("utmpname(file: %q)", file); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_utmpname]]]*/

/*[[[head:libc_getutent,hash:CRC-32=0x917692fe]]]*/
/* >> getutent(3), getutent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") struct utmp *
NOTHROW_RPC_KOS(LIBCCALL libc_getutent)(void)
/*[[[body:libc_getutent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("getutent"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getutent]]]*/

/*[[[head:libc_setutent,hash:CRC-32=0xf093775c]]]*/
/* >> setutent(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") void
NOTHROW_RPC_KOS(LIBCCALL libc_setutent)(void)
/*[[[body:libc_setutent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("setutent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_setutent]]]*/

/*[[[head:libc_endutent,hash:CRC-32=0x5bf87579]]]*/
/* >> endutent(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") void
NOTHROW_NCX(LIBCCALL libc_endutent)(void)
/*[[[body:libc_endutent]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("endutent"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_endutent]]]*/

/*[[[head:libc_getutid,hash:CRC-32=0x189bd4d]]]*/
/* >> getutid(3), getutid_r(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") ATTR_IN(1) struct utmp *
NOTHROW_RPC_KOS(LIBCCALL libc_getutid)(struct utmp const *id)
/*[[[body:libc_getutid]]]*/
/*AUTO*/{
	(void)id;
	CRT_UNIMPLEMENTEDF("getutid(id: %p)", id); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getutid]]]*/

/*[[[head:libc_getutline,hash:CRC-32=0x8fd28bc1]]]*/
/* >> getutline(3), getutline_r(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") ATTR_IN(1) struct utmp *
NOTHROW_RPC_KOS(LIBCCALL libc_getutline)(struct utmp const *line)
/*[[[body:libc_getutline]]]*/
/*AUTO*/{
	(void)line;
	CRT_UNIMPLEMENTEDF("getutline(line: %p)", line); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_getutline]]]*/

/*[[[head:libc_pututline,hash:CRC-32=0x8e63caa7]]]*/
/* >> pututline(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") ATTR_IN(1) struct utmp *
NOTHROW_RPC_KOS(LIBCCALL libc_pututline)(struct utmp const *utmp_ptr)
/*[[[body:libc_pututline]]]*/
/*AUTO*/{
	(void)utmp_ptr;
	CRT_UNIMPLEMENTEDF("pututline(utmp_ptr: %p)", utmp_ptr); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_pututline]]]*/

/*[[[head:libc_getutent_r,hash:CRC-32=0xe33a94a]]]*/
/* >> getutent(3), getutent_r(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") ATTR_OUT(1) ATTR_OUT(2) int
NOTHROW_RPC_KOS(LIBCCALL libc_getutent_r)(struct utmp *buffer,
                                          struct utmp **result)
/*[[[body:libc_getutent_r]]]*/
/*AUTO*/{
	(void)buffer;
	(void)result;
	CRT_UNIMPLEMENTEDF("getutent_r(buffer: %p, result: %p)", buffer, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getutent_r]]]*/

/*[[[head:libc_getutid_r,hash:CRC-32=0x8d95a869]]]*/
/* >> getutid(3), getutid_r(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(3) int
NOTHROW_RPC_KOS(LIBCCALL libc_getutid_r)(struct utmp const *id,
                                         struct utmp *buffer,
                                         struct utmp **result)
/*[[[body:libc_getutid_r]]]*/
/*AUTO*/{
	(void)id;
	(void)buffer;
	(void)result;
	CRT_UNIMPLEMENTEDF("getutid_r(id: %p, buffer: %p, result: %p)", id, buffer, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getutid_r]]]*/

/*[[[head:libc_getutline_r,hash:CRC-32=0xae57a40]]]*/
/* >> getutline(3), getutline_r(3) */
INTERN ATTR_SECTION(".text.crt.database.utmp") ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(3) int
NOTHROW_RPC_KOS(LIBCCALL libc_getutline_r)(struct utmp const *line,
                                           struct utmp *buffer,
                                           struct utmp **result)
/*[[[body:libc_getutline_r]]]*/
/*AUTO*/{
	(void)line;
	(void)buffer;
	(void)result;
	CRT_UNIMPLEMENTEDF("getutline_r(line: %p, buffer: %p, result: %p)", line, buffer, result); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_getutline_r]]]*/





/*[[[start:exports,hash:CRC-32=0x3a847ee8]]]*/
DEFINE_PUBLIC_ALIAS(login, libc_login);
DEFINE_PUBLIC_ALIAS(logout, libc_logout);
DEFINE_PUBLIC_ALIAS(logwtmp, libc_logwtmp);
DEFINE_PUBLIC_ALIAS(updwtmp, libc_updwtmp);
DEFINE_PUBLIC_ALIAS(__utmpname, libc_utmpname);
DEFINE_PUBLIC_ALIAS(utmpname, libc_utmpname);
DEFINE_PUBLIC_ALIAS(getutent, libc_getutent);
DEFINE_PUBLIC_ALIAS(__setutent, libc_setutent);
DEFINE_PUBLIC_ALIAS(setutent, libc_setutent);
DEFINE_PUBLIC_ALIAS(__endutent, libc_endutent);
DEFINE_PUBLIC_ALIAS(endutent, libc_endutent);
DEFINE_PUBLIC_ALIAS(getutid, libc_getutid);
DEFINE_PUBLIC_ALIAS(getutline, libc_getutline);
DEFINE_PUBLIC_ALIAS(_pututline, libc_pututline);
DEFINE_PUBLIC_ALIAS(__pututline, libc_pututline);
DEFINE_PUBLIC_ALIAS(pututline, libc_pututline);
DEFINE_PUBLIC_ALIAS(__getutent_r, libc_getutent_r);
DEFINE_PUBLIC_ALIAS(getutent_r, libc_getutent_r);
DEFINE_PUBLIC_ALIAS(__getutid_r, libc_getutid_r);
DEFINE_PUBLIC_ALIAS(getutid_r, libc_getutid_r);
DEFINE_PUBLIC_ALIAS(__getutline_r, libc_getutline_r);
DEFINE_PUBLIC_ALIAS(getutline_r, libc_getutline_r);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_UTMP_C */
