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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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





/*[[[start:implementation]]]*/

/*[[[head:closelog,hash:CRC-32=0x54f0e523]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.syslog.closelog") void
NOTHROW_NCX(LIBCCALL libc_closelog)(void)
/*[[[body:closelog]]]*/
{
	CRT_UNIMPLEMENTED("closelog"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:closelog]]]*/

/*[[[head:openlog,hash:CRC-32=0x716b33f5]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.syslog.openlog") void
NOTHROW_RPC(LIBCCALL libc_openlog)(char const *ident,
                                   int option,
                                   int facility)
/*[[[body:openlog]]]*/
{
	(void)ident;
	(void)option;
	(void)facility;
	CRT_UNIMPLEMENTED("openlog"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:openlog]]]*/

/*[[[head:setlogmask,hash:CRC-32=0xccb38207]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.syslog.setlogmask") int
NOTHROW_NCX(LIBCCALL libc_setlogmask)(int mask)
/*[[[body:setlogmask]]]*/
{
	(void)mask;
	CRT_UNIMPLEMENTED("setlogmask"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:setlogmask]]]*/

/*[[[head:syslog,hash:CRC-32=0xbf8640b3]]]*/
INTERN NONNULL((2)) ATTR_LIBC_PRINTF(2,3)
ATTR_WEAK ATTR_SECTION(".text.crt.system.syslog.syslog") void
NOTHROW_RPC(VLIBCCALL libc_syslog)(int level,
                                   char const *format,
                                   ...)
/*[[[body:syslog]]]*/
{
	va_list args;
	va_start(args, format);
	format_vprintf(&syslog_printer,
	               (void *)(uintptr_t)(unsigned int)level,
	               format,
	               args);
	va_end(args);
}
/*[[[end:syslog]]]*/

/*[[[head:vsyslog,hash:CRC-32=0xbe66ccac]]]*/
INTERN NONNULL((2)) ATTR_LIBC_PRINTF(2,0)
ATTR_WEAK ATTR_SECTION(".text.crt.system.syslog.vsyslog") void
NOTHROW_RPC(LIBCCALL libc_vsyslog)(int level,
                                   char const *format,
                                   va_list args)
/*[[[body:vsyslog]]]*/
{
	format_vprintf(&syslog_printer,
	               (void *)(uintptr_t)(unsigned int)level,
	               format,
	               args);
}
/*[[[end:vsyslog]]]*/

/*[[[head:syslog_printer,hash:CRC-32=0x90817ab9]]]*/
/* Helper functions for printing to the system log */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.system.syslog.syslog_printer") ssize_t
NOTHROW_RPC(LIBCCALL libc_syslog_printer)(void *arg,
                                          char const *__restrict data,
                                          size_t datalen)
/*[[[body:syslog_printer]]]*/
{
	ssize_t result;
	result = sys_syslog((syscall_ulong_t)(uintptr_t)arg,
	                    data,
	                    datalen);
	return libc_seterrno_syserr(result);
}
/*[[[end:syslog_printer]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xbfbd2114]]]*/
#undef syslog
DEFINE_PUBLIC_WEAK_ALIAS(closelog, libc_closelog);
DEFINE_PUBLIC_WEAK_ALIAS(openlog, libc_openlog);
DEFINE_PUBLIC_WEAK_ALIAS(setlogmask, libc_setlogmask);
DEFINE_PUBLIC_WEAK_ALIAS(syslog, libc_syslog);
DEFINE_PUBLIC_WEAK_ALIAS(vsyslog, libc_vsyslog);
DEFINE_PUBLIC_WEAK_ALIAS(syslog_printer, libc_syslog_printer);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SYSLOG_C */
