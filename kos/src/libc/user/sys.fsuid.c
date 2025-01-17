/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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

/*[[[head:libc_setfsuid,hash:CRC-32=0xddd3be13]]]*/
/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setfsuid)(uid_t uid)
/*[[[body:libc_setfsuid]]]*/
{
	errno_t result;
#ifdef SYS_setfsuid32
	result = sys_setfsuid32((u32)uid);
#else /* SYS_setfsuid32 */
	result = sys_setfsuid(uid);
#endif /* !SYS_setfsuid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setfsuid]]]*/

/*[[[head:libc_setfsgid,hash:CRC-32=0xef55724b]]]*/
/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_setfsgid)(gid_t gid)
/*[[[body:libc_setfsgid]]]*/
{
	errno_t result;
#ifdef SYS_setfsgid32
	result = sys_setfsgid32((u32)gid);
#else /* SYS_setfsgid32 */
	result = sys_setfsgid(gid);
#endif /* !SYS_setfsgid32 */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_setfsgid]]]*/





/*[[[start:exports,hash:CRC-32=0xf2510ba1]]]*/
DEFINE_PUBLIC_ALIAS_P(__setfsuid,libc_setfsuid,,int,NOTHROW_NCX,LIBCCALL,(uid_t uid),(uid));
DEFINE_PUBLIC_ALIAS_P(__libc_setfsuid,libc_setfsuid,,int,NOTHROW_NCX,LIBCCALL,(uid_t uid),(uid));
DEFINE_PUBLIC_ALIAS_P(setfsuid,libc_setfsuid,,int,NOTHROW_NCX,LIBCCALL,(uid_t uid),(uid));
DEFINE_PUBLIC_ALIAS_P(__setfsgid,libc_setfsgid,,int,NOTHROW_NCX,LIBCCALL,(gid_t gid),(gid));
DEFINE_PUBLIC_ALIAS_P(__libc_setfsgid,libc_setfsgid,,int,NOTHROW_NCX,LIBCCALL,(gid_t gid),(gid));
DEFINE_PUBLIC_ALIAS_P(setfsgid,libc_setfsgid,,int,NOTHROW_NCX,LIBCCALL,(gid_t gid),(gid));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_FSUID_C */
