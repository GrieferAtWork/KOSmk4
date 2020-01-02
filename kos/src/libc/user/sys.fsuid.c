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
#ifndef GUARD_LIBC_USER_SYS_FSUID_C
#define GUARD_LIBC_USER_SYS_FSUID_C 1

#include "../api.h"
#include "sys.fsuid.h"
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:setfsuid,hash:CRC-32=0x882ccb24]]]*/
/* Change uid used for file access control to UID, without affecting
 * other privileges (such as who can send signals at the process) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.user.setfsuid") int
NOTHROW_NCX(LIBCCALL libc_setfsuid)(uid_t uid)
/*[[[body:setfsuid]]]*/
{
	errno_t result;
#ifdef SYS_setfsuid32
	result = sys_setfsuid32((u32)uid);
#else /* SYS_setfsuid32 */
	result = sys_setfsuid(uid);
#endif /* !SYS_setfsuid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:setfsuid]]]*/

/*[[[head:setfsgid,hash:CRC-32=0x8d9425e7]]]*/
/* Ditto for group id */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.user.setfsgid") int
NOTHROW_NCX(LIBCCALL libc_setfsgid)(gid_t gid)
/*[[[body:setfsgid]]]*/
{
	errno_t result;
#ifdef SYS_setfsgid32
	result = sys_setfsgid32((u32)gid);
#else /* SYS_setfsgid32 */
	result = sys_setfsgid(gid);
#endif /* !SYS_setfsgid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:setfsgid]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x2ca593b6]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(setfsuid, libc_setfsuid);
DEFINE_PUBLIC_WEAK_ALIAS(setfsgid, libc_setfsgid);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_FSUID_C */
