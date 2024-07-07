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
#ifndef GUARD_LIBC_USER_SYS_PRCTL_C
#define GUARD_LIBC_USER_SYS_PRCTL_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <errno.h>
#include <stdarg.h>

#include "sys.prctl.h"

DECL_BEGIN

/*[[[head:libc_prctl,hash:CRC-32=0x6ea976e8]]]*/
/* >> prctl(2)
 * System process control interface. (Linux compatible)
 * @param: command: One of `PR_*' (from <linux/prctl.h>)
 * @param: ... :    Up  to 4 additional arguments (dependent on `command')
 *                  Note that some control codes  require you to pass  `0'
 *                  for  all seemingly "unused" arguments. In these cases,
 *                  the documentation for that command includes the number
 *                  of unused, but required trailing 0s in its comment.
 * @return: * :     Return value depends on `command'
 * @return: -1:     Error (s.a. `errno'; depends on `command')
 * @return: -1:     [errno=EINVAL] Unsupported `command' (including unsupported-on-this-arch) */
INTERN ATTR_SECTION(".text.crt.unsorted") int
NOTHROW_NCX(VLIBCCALL libc_prctl)(__STDC_INT_AS_UINT_T command,
                                  ...)
/*[[[body:libc_prctl]]]*/
{
	syscall_slong_t result;
	syscall_ulong_t arg2, arg3, arg4, arg5;
	va_list args;
	va_start(args, command);
	arg2 = va_arg(args, syscall_ulong_t);
	arg3 = va_arg(args, syscall_ulong_t);
	arg4 = va_arg(args, syscall_ulong_t);
	arg5 = va_arg(args, syscall_ulong_t);
	va_end(args);
	result = sys_prctl(command, arg2, arg3, arg4, arg5);
	if unlikely(E_ISERR(result))
		result = libc_seterrno_neg(result);
	return (int)result;
}
/*[[[end:libc_prctl]]]*/

/*[[[start:exports,hash:CRC-32=0x98db17f2]]]*/
DEFINE_PUBLIC_ALIAS_P(prctl,libc_prctl,,int,NOTHROW_NCX,VLIBCCALL,(__STDC_INT_AS_UINT_T command, ...),(command,));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_PRCTL_C */
