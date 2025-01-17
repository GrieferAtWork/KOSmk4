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
#ifndef GUARD_LIBC_LIBC_SYSCALLS_C
#define GUARD_LIBC_LIBC_SYSCALLS_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <errno.h>
#include <stdarg.h>

/* TODO: Replace this file with /kos/src/libc/user/kos.ksysctl.c
 *       -> Consequently, also generate other related files! */

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.kos.syscalls") syscall_slong_t
NOTHROW_NCX(VLIBCCALL libc_ksysctl)(syscall_ulong_t cmd, ... /*, void *arg*/) {
	syscall_slong_t result;
	va_list args;
	va_start(args, cmd);
	result = sys_ksysctl(cmd, va_arg(args, void *));
	va_end(args);
	if (E_ISERR(result))
		result = libc_seterrno_neg((errno_t)result);
	return result;
}

DEFINE_PUBLIC_ALIAS(ksysctl, libc_ksysctl);

DECL_END

#endif /* !GUARD_LIBC_LIBC_SYSCALLS_C */
