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
#ifndef GUARD_LIBC_USER_SYS_SYSLOG_C
#define GUARD_LIBC_USER_SYS_SYSLOG_C 1

#include "../api.h"
#include "sys.syslog.h"

#include <format-printer.h>
#include <kos/syscalls.h>

DECL_BEGIN

/*[[[head:libc_closelog,hash:CRC-32=0x68d099ce]]]*/
INTERN ATTR_SECTION(".text.crt.system.syslog") void
NOTHROW_NCX(LIBCCALL libc_closelog)(void)
/*[[[body:libc_closelog]]]*/
/*AUTO*/{
	CRT_UNIMPLEMENTED("closelog"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_closelog]]]*/

/*[[[head:libc_openlog,hash:CRC-32=0x417f05be]]]*/
INTERN ATTR_SECTION(".text.crt.system.syslog") void
NOTHROW_RPC(LIBCCALL libc_openlog)(char const *ident,
                                   __STDC_INT_AS_UINT_T option,
                                   __STDC_INT_AS_UINT_T facility)
/*[[[body:libc_openlog]]]*/
/*AUTO*/{
	(void)ident;
	(void)option;
	(void)facility;
	CRT_UNIMPLEMENTEDF("openlog(%q, %x, %x)", ident, option, facility); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:libc_openlog]]]*/

/*[[[head:libc_setlogmask,hash:CRC-32=0xdc24a181]]]*/
INTERN ATTR_SECTION(".text.crt.system.syslog") int
NOTHROW_NCX(LIBCCALL libc_setlogmask)(__STDC_INT_AS_UINT_T mask)
/*[[[body:libc_setlogmask]]]*/
/*AUTO*/{
	(void)mask;
	CRT_UNIMPLEMENTEDF("setlogmask(%x)", mask); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_setlogmask]]]*/

/*[[[head:libc_syslog_printer,hash:CRC-32=0x8e30a73c]]]*/
/* Helper functions for printing to the system log */
INTERN ATTR_SECTION(".text.crt.system.syslog") ATTR_ACCESS_ROS(2, 3) ssize_t
NOTHROW_RPC(__FORMATPRINTER_CC libc_syslog_printer)(void *arg,
                                                    char const *__restrict data,
                                                    size_t datalen)
/*[[[body:libc_syslog_printer]]]*/
{
	ssize_t result;
	result = sys_syslog((syscall_ulong_t)(uintptr_t)arg,
	                    data,
	                    datalen);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_syslog_printer]]]*/





/*[[[start:exports,hash:CRC-32=0x730b2bf7]]]*/
DEFINE_PUBLIC_ALIAS(closelog, libc_closelog);
DEFINE_PUBLIC_ALIAS(openlog, libc_openlog);
DEFINE_PUBLIC_ALIAS(setlogmask, libc_setlogmask);
DEFINE_PUBLIC_ALIAS(syslog_printer, libc_syslog_printer);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SYSLOG_C */
