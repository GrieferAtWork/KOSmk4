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
#ifndef GUARD_LIBC_USER_SYS_PERM_C
#define GUARD_LIBC_USER_SYS_PERM_C 1

#include "../api.h"
/**/

#include <syscall.h>
#include <kos/syscalls.h>

#include "sys.perm.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:ioperm,hash:CRC-32=0x30acde48]]]*/
/* Change I/O port permissions for a specific I/O port range */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.ioperm.ioperm") int
NOTHROW_NCX(LIBCCALL libc_ioperm)(ulongptr_t from,
                                  ulongptr_t num,
                                  int turn_on)
/*[[[body:ioperm]]]*/
{
#ifdef SYS_ioperm
	errno_t error;
	error = sys_ioperm((syscall_ulong_t)from,
	                   (syscall_ulong_t)num,
	                   (syscall_ulong_t)(unsigned int)turn_on);
	return libc_seterrno_syserr(error);
#else /* SYS_ioperm */
	libc_seterrno(ENOSYS);
	return -1;
#endif /* !SYS_ioperm */
}
/*[[[end:ioperm]]]*/

/*[[[head:iopl,hash:CRC-32=0x6b54d9b4]]]*/
/* Change I/O port permissions for all I/O ports */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.ioperm.iopl") int
NOTHROW_NCX(LIBCCALL libc_iopl)(int level)
/*[[[body:iopl]]]*/
{
#ifdef SYS_iopl
	errno_t error;
	error = sys_iopl((syscall_ulong_t)(unsigned int)level);
	return libc_seterrno_syserr(error);
#else /* SYS_iopl */
	libc_seterrno(ENOSYS);
	return -1;
#endif /* !SYS_iopl */
}
/*[[[end:iopl]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xe65fa090]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(ioperm, libc_ioperm);
DEFINE_PUBLIC_WEAK_ALIAS(iopl, libc_iopl);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_PERM_C */
