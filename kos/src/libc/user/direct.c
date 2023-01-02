/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_DIRECT_C
#define GUARD_LIBC_USER_DIRECT_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "direct.h"

DECL_BEGIN

/*[[[head:libc__getdrive,hash:CRC-32=0xa2abfff3]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.property") int
NOTHROW_RPC(LIBCCALL libc__getdrive)(void)
/*[[[body:libc__getdrive]]]*/
{
	char buf[2];
	ssize_t error;
	error = sys_frealpath4(AT_FDCWD, buf, 2,
	                       AT_READLINK_REQSIZE |
	                       AT_DOSPATH);
	if (error < 2 || buf[1] != ':' ||
	    buf[0] < AT_DOS_DRIVEMIN ||
	    buf[0] > AT_DOS_DRIVEMAX) {
		if (error >= 0)
			libc_seterrno(EBADF);
		return -1;
	}
	return (int)(buf[0] - AT_DOS_DRIVEMIN);
}
/*[[[end:libc__getdrive]]]*/

/*[[[head:libc__getdrives,hash:CRC-32=0x1f5628c4]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.property") __ULONG32_TYPE__
NOTHROW_RPC(LIBCCALL libc__getdrives)(void)
/*[[[body:libc__getdrives]]]*/
{
	syscall_slong_t result;
	result = sys_getdrives();
	if (E_ISERR(result)) {
		libc_seterrno_neg(result);
		result = 0;
	}
	return (__ULONG32_TYPE__)(syscall_ulong_t)result;
}
/*[[[end:libc__getdrives]]]*/

/*[[[head:libc__getdiskfree,hash:CRC-32=0xab12c346]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.property") ATTR_OUT(2) unsigned int
NOTHROW_RPC(LIBCCALL libc__getdiskfree)(unsigned int drive,
                                        struct _diskfree_t *diskfree)
/*[[[body:libc__getdiskfree]]]*/
/*AUTO*/{
	(void)drive;
	(void)diskfree;
	CRT_UNIMPLEMENTEDF("_getdiskfree(drive: %x, diskfree: %p)", drive, diskfree); /* TODO */
	return (unsigned int)libc_seterrno(ENOSYS);
}
/*[[[end:libc__getdiskfree]]]*/





/*[[[start:exports,hash:CRC-32=0x1671125]]]*/
DEFINE_PUBLIC_ALIAS(_getdrive, libc__getdrive);
DEFINE_PUBLIC_ALIAS(_getdrives, libc__getdrives);
DEFINE_PUBLIC_ALIAS(_getdiskfree, libc__getdiskfree);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_DIRECT_C */
