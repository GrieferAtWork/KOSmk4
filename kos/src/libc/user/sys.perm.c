/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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

/*[[[head:libc_ioperm,hash:CRC-32=0x3342be26]]]*/
/* Change I/O port permissions for a specific I/O port range */
INTERN ATTR_SECTION(".text.crt.system.ioperm") int
NOTHROW_NCX(LIBCCALL libc_ioperm)(ulongptr_t from,
                                  ulongptr_t num,
                                  __STDC_INT_AS_UINT_T turn_on)
/*[[[body:libc_ioperm]]]*/
{
#ifdef SYS_ioperm
	errno_t error;
	error = sys_ioperm((syscall_ulong_t)from,
	                   (syscall_ulong_t)num,
	                   (syscall_ulong_t)(unsigned int)turn_on);
	return libc_seterrno_syserr(error);
#else /* SYS_ioperm */
	(void)from;
	(void)num;
	(void)turn_on;
	libc_seterrno(ENOSYS);
	return -1;
#endif /* !SYS_ioperm */
}
/*[[[end:libc_ioperm]]]*/

/*[[[head:libc_iopl,hash:CRC-32=0x4bd4f2b]]]*/
/* Change I/O port permissions for all I/O ports */
INTERN ATTR_SECTION(".text.crt.system.ioperm") int
NOTHROW_NCX(LIBCCALL libc_iopl)(__STDC_INT_AS_UINT_T level)
/*[[[body:libc_iopl]]]*/
{
#ifdef SYS_iopl
	errno_t error;
	error = sys_iopl((syscall_ulong_t)(unsigned int)level);
	return libc_seterrno_syserr(error);
#else /* SYS_iopl */
	(void)level;
	libc_seterrno(ENOSYS);
	return -1;
#endif /* !SYS_iopl */
}
/*[[[end:libc_iopl]]]*/


/*[[[start:exports,hash:CRC-32=0x8c944090]]]*/
DEFINE_PUBLIC_ALIAS(__ioperm, libc_ioperm);
DEFINE_PUBLIC_ALIAS(__libc_ioperm, libc_ioperm);
DEFINE_PUBLIC_ALIAS(ioperm, libc_ioperm);
DEFINE_PUBLIC_ALIAS(__iopl, libc_iopl);
DEFINE_PUBLIC_ALIAS(__libc_iopl, libc_iopl);
DEFINE_PUBLIC_ALIAS(iopl, libc_iopl);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_PERM_C */
