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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_ROUTER32_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_ROUTER32_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <hybrid/host.h>

#ifdef __x86_64__
#define PTR  .quad
#else /* __x86_64__ */
#define PTR  .long
#endif /* !__x86_64__ */

/* Define `x86_sysrouteN_asm32_int80' */
.section .rodata.x86.syscall32.route_int80
EXTERN(__x86_asm32_int80_break)
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC_OBJECT(x86_sysroute##table_id##_asm32_int80)
#define __SYSCALL(name)         EXTERN(__x86_asm32_int80_##name); PTR __x86_asm32_int80_##name;
#define __SYSCALL_UNUSED(sysno) PTR __x86_asm32_int80_break;
#define __TSYSCALL_TABLE_END(table_id, ...) \
	END(x86_sysroute##table_id##_asm32_int80)
#include "../../../../../../include/i386-kos/asm/ls-syscalls32.h"


/* Define `x86_sysrouteN_asm32_sysenter' */
.section .rodata.x86.syscall32.route_sysenter
EXTERN(__x86_asm32_sysenter_break)
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC_OBJECT(x86_sysroute##table_id##_asm32_sysenter)
#define __SYSCALL(name)         EXTERN(__x86_asm32_sysenter_##name); PTR __x86_asm32_sysenter_##name;
#define __SYSCALL_UNUSED(sysno) PTR __x86_asm32_sysenter_break;
#define __TSYSCALL_TABLE_END(table_id, ...) \
	END(x86_sysroute##table_id##_asm32_sysenter)
#include "../../../../../../include/i386-kos/asm/ls-syscalls32.h"


/* Define `x86_sysrouteN_c' or `x86_sysrouteN_c32' */
.section .rodata.x86.syscall32.route_c
#ifdef __x86_64__
EXTERN(sys32_break)
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC_OBJECT(x86_sysroute##table_id##_c32)
#define __SYSCALL(name)         EXTERN(sys32_##name); PTR sys32_##name;
#define __SYSCALL_UNUSED(sysno) PTR sys32_break;
#define __TSYSCALL_TABLE_END(table_id, ...) \
	END(x86_sysroute##table_id##_c32)
#else /* __x86_64__ */
EXTERN(sys_break)
#define __TSYSCALL_TABLE_BEGIN(table_id, ...) \
	PUBLIC_OBJECT(x86_sysroute##table_id##_c)
#define __SYSCALL(name)         EXTERN(sys_##name); PTR sys_##name;
#define __SYSCALL_UNUSED(sysno) PTR sys_break;
#define __TSYSCALL_TABLE_END(table_id, ...) \
	END(x86_sysroute##table_id##_c)
#endif /* !__x86_64__ */
#include "../../../../../../include/i386-kos/asm/ls-syscalls32.h"

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_ROUTER32_S */
