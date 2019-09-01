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
#ifndef GUARD_LIBC_USER_DIRECT_C
#define GUARD_LIBC_USER_DIRECT_C 1

#include "../api.h"
#include "direct.h"

#include <fcntl.h>
#include <kos/syscalls.h>
#include <stdlib.h>
#include <unistd.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:_getdcwd,hash:0x9e02b79f]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.property._getdcwd") char *
NOTHROW_RPC(LIBCCALL libc__getdcwd)(int drive,
                                    char *buf,
                                    size_t size)
/*[[[body:_getdcwd]]]*/
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
/*[[[end:_getdcwd]]]*/

/*[[[head:_chdrive,hash:0x794703cd]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.property._chdrive") int
NOTHROW_RPC(LIBCCALL libc__chdrive)(int drive)
/*[[[body:_chdrive]]]*/
{
	drive = toupper(drive);
	if unlikely(drive < AT_DOS_DRIVEMIN || drive > AT_DOS_DRIVEMAX)
		return (int)libc_seterrno(EINVAL);
	return fchdir(AT_FDDRIVE_ROOT(drive));
}
/*[[[end:_chdrive]]]*/

/*[[[head:_getdrive,hash:0x80582a40]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.property._getdrive") int
NOTHROW_RPC(LIBCCALL libc__getdrive)(void)
/*[[[body:_getdrive]]]*/
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
/*[[[end:_getdrive]]]*/

/*[[[head:_getdrives,hash:0xcf16dc01]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.property._getdrives") __ULONG32_TYPE__
NOTHROW_RPC(LIBCCALL libc__getdrives)(void)
/*[[[body:_getdrives]]]*/
{
	syscall_slong_t result;
	result = sys_getdrives();
	if (E_ISERR(result)) {
		libc_seterrno(-result);
		result = 0;
	}
	return (__ULONG32_TYPE__)(syscall_ulong_t)result;
}
/*[[[end:_getdrives]]]*/

/*[[[head:_getdiskfree,hash:0x4d5f9cc6]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.property._getdiskfree") unsigned int
NOTHROW_RPC(LIBCCALL libc__getdiskfree)(unsigned int drive,
                                        struct _diskfree_t *diskfree)
/*[[[body:_getdiskfree]]]*/
{
	CRT_UNIMPLEMENTED("_getdiskfree"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_getdiskfree]]]*/

/*[[[head:_mkdir,hash:0x9682bc92]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.fs.modify._mkdir") int
NOTHROW_RPC(LIBCCALL libc__mkdir)(char const *path)
/*[[[body:_mkdir]]]*/
{
	errno_t result;
	result = sys_mkdir(path, 0755);
	return libc_seterrno_syserr(result);
}
/*[[[end:_mkdir]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x2f3ab5ca]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(_getdcwd, libc__getdcwd);
DEFINE_PUBLIC_WEAK_ALIAS(_chdrive, libc__chdrive);
DEFINE_PUBLIC_WEAK_ALIAS(_getdrive, libc__getdrive);
DEFINE_PUBLIC_WEAK_ALIAS(_getdrives, libc__getdrives);
DEFINE_PUBLIC_WEAK_ALIAS(_getdiskfree, libc__getdiskfree);
DEFINE_PUBLIC_WEAK_ALIAS(_mkdir, libc__mkdir);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_DIRECT_C */
