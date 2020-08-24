/* HASH CRC-32:0x8280fc89 */
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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT64_S
#define GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT64_S 1
#define _GNU_SOURCE 1
#define __ASSEMBLER__ 1

#include "../../../api.h"
/**/
#include <hybrid/compiler.h>

#include <asm/cfi.h>
#include <asm/cpu-cpuid.h>
#include <asm/instr/ttest.h>
#include <asm/pagesize.h>
#include <bits/mcontext64.h>
#include <bits/ucontext64.h>

#include <pthread.h>
#include <signal.h>
#include <syscall.h>
#include <ucontext.h>

#include "ucontext.h"
/**/


#ifdef ENVIRON_HW_SSE
.section .rodata.crt.cpu.ucontext
PRIVATE_OBJECT(str_HW_SSE)
	.asciz ENVIRON_HW_SSE
END(str_HW_SSE)
#endif /* ENVIRON_HW_SSE */

.section .text.crt.cpu.ucontext
INTERN_FUNCTION(libc_getcontext)
	.cfi_startproc
	/* TODO */
	hlt
	.cfi_endproc
END(libc_getcontext)



.section .text.crt.cpu.ucontext
INTERN_FUNCTION(libc_setcontext)
	.cfi_startproc
	/* TODO */
	hlt
	.cfi_endproc
END(libc_setcontext)



.section .text.crt.cpu.ucontext
INTERN_FUNCTION(libc_swapcontext)
	.cfi_startproc
	/* TODO */
	hlt
	.cfi_endproc
END(libc_swapcontext)





DEFINE_PUBLIC_ALIAS(getcontext, libc_getcontext)
DEFINE_PUBLIC_ALIAS(setcontext, libc_setcontext)
DEFINE_PUBLIC_ALIAS(swapcontext, libc_swapcontext)


#endif /* GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT64_S */
