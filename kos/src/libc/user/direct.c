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
#ifndef GUARD_LIBC_USER_DIRECT_C
#define GUARD_LIBC_USER_DIRECT_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "direct.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc__getdcwd,hash:CRC-32=0x887f4d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.property") char *
NOTHROW_RPC(LIBCCALL libc__getdcwd)(int drive,
                                    char *buf,
                                    size_t size)
/*[[[body:libc__getdcwd]]]*/
{
	if unlikely(drive < AT_DOS_DRIVEMIN || drive > AT_DOS_DRIVEMAX) {
		libc_seterrno(EINVAL);
		return NULL;
	}
	return frealpath4(AT_FDDRIVE_CWD(drive),
	                  buf,
	                  size,
	                  0);
}
/*[[[end:libc__getdcwd]]]*/

/*[[[head:libc__chdrive,hash:CRC-32=0xb48bbfa2]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.property") int
NOTHROW_RPC(LIBCCALL libc__chdrive)(int drive)
/*[[[body:libc__chdrive]]]*/
{
	drive = toupper(drive);
	if unlikely(drive < AT_DOS_DRIVEMIN || drive > AT_DOS_DRIVEMAX)
		return (int)libc_seterrno(EINVAL);
	return fchdir(AT_FDDRIVE_ROOT(drive));
}
/*[[[end:libc__chdrive]]]*/

/*[[[head:libc__getdrive,hash:CRC-32=0xa2abfff3]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.property") int
NOTHROW_RPC(LIBCCALL libc__getdrive)(void)
/*[[[body:libc__getdrive]]]*/
{
	char buf[2];
	ssize_t error;
	error = sys_frealpath4(AT_FDROOT,
	                       buf,
	                       2,
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
		libc_seterrno(-result);
		result = 0;
	}
	return (__ULONG32_TYPE__)(syscall_ulong_t)result;
}
/*[[[end:libc__getdrives]]]*/

/*[[[head:libc__getdiskfree,hash:CRC-32=0x62358abe]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.property") unsigned int
NOTHROW_RPC(LIBCCALL libc__getdiskfree)(unsigned int drive,
                                        struct _diskfree_t *diskfree)
/*[[[body:libc__getdiskfree]]]*/
/*AUTO*/{
	(void)drive;
	(void)diskfree;
	CRT_UNIMPLEMENTED("_getdiskfree"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc__getdiskfree]]]*/

/*[[[head:libc__mkdir,hash:CRC-32=0xa805db12]]]*/
INTERN ATTR_SECTION(".text.crt.dos.fs.modify") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc__mkdir)(char const *path)
/*[[[body:libc__mkdir]]]*/
{
	errno_t result;
	result = sys_mkdir(path, 0755);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc__mkdir]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xaa2dc853]]]*/
DEFINE_PUBLIC_ALIAS(_getdcwd, libc__getdcwd);
DEFINE_PUBLIC_ALIAS(_chdrive, libc__chdrive);
DEFINE_PUBLIC_ALIAS(_getdrive, libc__getdrive);
DEFINE_PUBLIC_ALIAS(_getdrives, libc__getdrives);
DEFINE_PUBLIC_ALIAS(_getdiskfree, libc__getdiskfree);
DEFINE_PUBLIC_ALIAS(_mkdir, libc__mkdir);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_DIRECT_C */
