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

#include <kernel/compiler.h>
#include <hybrid/host.h>


/* Include the 32-bit router for compatibility mode. */
#include "router32.S"

/* Define `x86_sysrouteN_asm64_syscall' */
.section .rodata.x86.syscall64.route_syscall
EXTERN(__x86_asm64_syscall_break)
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC_OBJECT(x86_sysroute##table_id##_asm64_syscall)
#define __SYSCALL(name)         EXTERN(__x86_asm64_syscall_##name); .quad __x86_asm64_syscall_##name;
#define __SYSCALL_UNUSED(sysno) .quad __x86_asm64_syscall_break;
#define __TSYSCALL_TABLE_END(table_id, ...) \
	END(x86_sysroute##table_id##_asm64_syscall)
#include "../../../../../../include/i386-kos/asm/ls-syscalls64.h"


/* Define `x86_sysrouteN_c' */
.section .rodata.x86.syscall64.route_c
EXTERN(sys_break)
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC_OBJECT(x86_sysroute##table_id##_c)
#define __SYSCALL(name)         EXTERN(sys_##name); .quad sys_##name;
#define __SYSCALL_UNUSED(sysno) .quad sys_break;
#define __TSYSCALL_TABLE_END(table_id, ...) \
	END(x86_sysroute##table_id##_c)
#include "../../../../../../include/i386-kos/asm/ls-syscalls64.h"



