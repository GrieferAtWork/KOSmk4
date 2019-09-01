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
#ifndef GUARD_LIBC_USER_SYS_MOUNT_C
#define GUARD_LIBC_USER_SYS_MOUNT_C 1

#include "../api.h"
#include "sys.mount.h"

#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:mount,hash:0x358c883d]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.mount.mount") int
NOTHROW_RPC(LIBCCALL libc_mount)(char const *special_file,
                                 char const *dir,
                                 char const *fstype,
                                 unsigned long int rwflag,
                                 void const *data)
/*[[[body:mount]]]*/
{
	errno_t result;
	result = sys_mount(special_file,
	                   dir,
	                   fstype,
	                   (syscall_ulong_t)rwflag,
	                   data);
	return libc_seterrno_syserr(result);
}
/*[[[end:mount]]]*/

/*[[[head:umount,hash:0xb4aa087a]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.mount.umount") int
NOTHROW_RPC(LIBCCALL libc_umount)(char const *special_file)
/*[[[body:umount]]]*/
{
	errno_t result;
#ifdef __NR_umount
	result = sys_umount(special_file);
#else /* __NR_umount */
	result = sys_umount2(special_file, 0);
#endif /* !__NR_umount */
	return libc_seterrno_syserr(result);
}
/*[[[end:umount]]]*/

/*[[[head:umount2,hash:0x49c6d6aa]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.fs.mount.umount2") int
NOTHROW_RPC(LIBCCALL libc_umount2)(char const *special_file,
                                   int flags)
/*[[[body:umount2]]]*/
{
	errno_t result;
	result = sys_umount2(special_file,
	                     (syscall_ulong_t)(unsigned int)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:umount2]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x32b69eb8]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(mount, libc_mount);
DEFINE_PUBLIC_WEAK_ALIAS(umount, libc_umount);
DEFINE_PUBLIC_WEAK_ALIAS(umount2, libc_umount2);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_MOUNT_C */
