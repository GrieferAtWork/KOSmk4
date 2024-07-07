/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_PTRACE_C
#define GUARD_LIBC_USER_SYS_PTRACE_C 1

#include "../api.h"
#include "sys.ptrace.h"

#include <kos/syscalls.h>

DECL_BEGIN

/*[[[head:libc_ptrace,hash:CRC-32=0xd2da63a1]]]*/
INTERN ATTR_SECTION(".text.crt.system.ptrace") longptr_t
NOTHROW_NCX(VLIBCCALL libc_ptrace)(__ptrace_request_t request,
                                   ...)
/*[[[body:libc_ptrace]]]*/
{
	syscall_slong_t result;
	va_list args;
	pid_t pid;
	void *addr, *data;
	va_start(args, request);
	pid  = va_arg(args, pid_t);
	addr = va_arg(args, void *);
	data = va_arg(args, void *);
	va_end(args);
	result = sys_ptrace(request, pid, addr, data);
	return (long int)libc_seterrno_syserr(result);
}
/*[[[end:libc_ptrace]]]*/





/*[[[start:exports,hash:CRC-32=0x9ab373fc]]]*/
DEFINE_PUBLIC_ALIAS_P(ptrace,libc_ptrace,,longptr_t,NOTHROW_NCX,VLIBCCALL,(__ptrace_request_t request, ...),(request,));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_PTRACE_C */
