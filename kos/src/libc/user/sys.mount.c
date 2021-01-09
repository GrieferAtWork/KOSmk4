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
#ifndef GUARD_LIBC_USER_SYS_MOUNT_C
#define GUARD_LIBC_USER_SYS_MOUNT_C 1

#include "../api.h"
#include "sys.mount.h"

#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_mount,hash:CRC-32=0x4b9f2946]]]*/
/* @param: mountflags: Set of `MS_*' from <sys/mount.h> */
INTERN ATTR_SECTION(".text.crt.fs.mount") int
NOTHROW_RPC(LIBCCALL libc_mount)(char const *special_file,
                                 char const *dir,
                                 char const *fstype,
                                 ulongptr_t mountflags,
                                 void const *data)
/*[[[body:libc_mount]]]*/
{
	errno_t result;
	result = sys_mount(special_file,
	                   dir,
	                   fstype,
	                   (syscall_ulong_t)mountflags,
	                   data);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mount]]]*/

/*[[[head:libc_umount,hash:CRC-32=0xd87f66f7]]]*/
INTERN ATTR_SECTION(".text.crt.fs.mount") int
NOTHROW_RPC(LIBCCALL libc_umount)(char const *special_file)
/*[[[body:libc_umount]]]*/
{
	errno_t result;
#ifdef __NR_umount
	result = sys_umount(special_file);
#else /* __NR_umount */
	result = sys_umount2(special_file, 0);
#endif /* !__NR_umount */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_umount]]]*/

/*[[[head:libc_umount2,hash:CRC-32=0x396c6760]]]*/
/* @param: flags: Set of `MNT_FORCE | MNT_DETACH | MNT_EXPIRE | UMOUNT_NOFOLLOW' */
INTERN ATTR_SECTION(".text.crt.fs.mount") int
NOTHROW_RPC(LIBCCALL libc_umount2)(char const *special_file,
                                   __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_umount2]]]*/
{
	errno_t result;
	result = sys_umount2(special_file,
	                     (syscall_ulong_t)(unsigned int)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_umount2]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x5bf6184c]]]*/
DEFINE_PUBLIC_ALIAS(mount, libc_mount);
DEFINE_PUBLIC_ALIAS(umount, libc_umount);
DEFINE_PUBLIC_ALIAS(umount2, libc_umount2);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_MOUNT_C */
