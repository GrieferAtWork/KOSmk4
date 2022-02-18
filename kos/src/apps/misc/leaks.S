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
#ifndef GUARD_APPS_MISC_LEAKS_S
#define GUARD_APPS_MISC_LEAKS_S 1
#define __ASSEMBLER__ 1

#include <hybrid/host.h>

#include <asm/instr/compat.h>
#include <kos/ksysctl.h>

#include <syscall.h>

#ifndef __x86_64__
#define syscall int $0x80
#endif /* __x86_64__ */

.section .text
.global _start
.type _start, @function
_start:
	movP  $(KSYSCTL_SYSTEM_MEMORY_DUMP_LEAKS), %R_syscall0P
	movP  $(SYS_ksysctl), %Pax
	std
	syscall
	cmpP  $(0), %Pax
	je    .Lexit
	int3
.Lexit:
	movP  $(0),        %R_syscall0P
	movP  $(SYS_exit), %Pax
	std
	syscall
	jmp   .Lexit
.size _start, . - _start

#endif /* !GUARD_APPS_MISC_LEAKS_S */
