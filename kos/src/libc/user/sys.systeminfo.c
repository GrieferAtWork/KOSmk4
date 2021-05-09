/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_SYSTEMINFO_C
#define GUARD_LIBC_USER_SYS_SYSTEMINFO_C 1

#include "../api.h"
/**/

#include "sys.systeminfo.h"

DECL_BEGIN

/*[[[head:libc___solaris_sysinfo,hash:CRC-32=0x65361ff3]]]*/
INTERN ATTR_SECTION(".text.crt.system.info") int
NOTHROW_NCX(LIBCCALL libc___solaris_sysinfo)(__STDC_INT_AS_UINT_T command,
                                             char *buf,
                                             __STDC_LONG_AS_SIZE_T buflen)
/*[[[body:libc___solaris_sysinfo]]]*/
/*AUTO*/{
	(void)command;
	(void)buf;
	(void)buflen;
	CRT_UNIMPLEMENTEDF("__solaris_sysinfo(%x, %q, %lx)", command, buf, buflen); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc___solaris_sysinfo]]]*/

/*[[[start:exports,hash:CRC-32=0x4865c117]]]*/
DEFINE_PUBLIC_ALIAS(__solaris_sysinfo, libc___solaris_sysinfo);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SYSTEMINFO_C */
