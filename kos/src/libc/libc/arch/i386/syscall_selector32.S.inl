/* HASH 0xf7cd9da1 */
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

#include <hybrid/compiler.h>
#include <asm/cfi.h>
#include <asm/unistd.h>
#include <asm/cpu-flags.h>
#include <asm/cpu-cpuid.h>
#include <sys/syscall.h>


.section .text.crt.syscall.selector
INTERN_FUNCTION(libc_x86_syscall_check_sysenter)
	.cfi_startproc
	pushl_cfi_r %eax
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx
	movl   $1, %eax
	cpuid
	movl   16(%esp), %ebx /* Return address */
	testl  $CPUID_1D_SEP, %edx
	jz    .Lnot_supported
	/* if (Family == 6 && Model < 3 && Stepping < 3)
	 *     goto .Lnot_supported; */
	movl   %eax, %ecx
	andl   $CPUID_1A_FAMILY_M, %ecx
	cmpl   $(6 << CPUID_1A_FAMILY_S), %ecx
	jne    .Lis_supported  /* if (Family != 6) goto .Lis_supported; */
	movl   %eax, %ecx
	andl   $CPUID_1A_MODEL_M, %ecx
#if CPUID_1A_MODEL_S
	shrl   $CPUID_1A_MODEL_S, %ecx
#endif
	cmpl   $3, %ecx
	jae    .Lis_supported  /* if (Model >= 3) goto .Lis_supported; */
	movl   %eax, %ecx
	andl   $CPUID_1A_STEPPING_M, %ecx
#if CPUID_1A_STEPPING_S
	shrl   $CPUID_1A_STEPPING_S, %ecx
#endif
	cmpl   $3, %ecx
	/* if (Stepping >= 3) goto .Lis_supported; */
	/* if (Stepping < 3) goto .Lnot_supported; */
	jb     .Lnot_supported
.Lis_supported:
	.cfi_remember_state
	/* Override call to this function:
	 * ORIGNAL (8 bytes of code):
	 *    E8    ?? ?? ?? ??    # call  libc_x86_syscall_check_sysenter
	 * %ebx:
	 *    74    ??             # jz    1f
	 *    ??                   # ...
	 * OVERRIDE:
	 *    90    90 90 90 90    # nop ...
	 * %ebx:
	 *    90    90             # nop ...
	 *    ??
	 */
	movzbl 2(%ebx), %eax
	shll   $24, %eax
	orl    $0x00909090, %eax
	pushl_cfi  %eax
	pushl_cfi  $0x90909090
	fildll (%esp)
	fistpll -5(%ebx) /* Override the selector code */
	addl  $8, %esp
	.cfi_adjust_cfa_offset -8
	/* Adjust the return address */
	addl  $2, 16(%esp)
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi_r %eax
	ret
.Lnot_supported:
	.cfi_restore_state
	/* Override call to this function:
	 * ORIGNAL (8 bytes of code):
	 *    E8    ?? ?? ?? ??    # call  libc_x86_syscall_check_sysenter
	 * %ebx:
	 *    74    ??             # jz    1f
	 *    ??                   # ...
	 * OVERRIDE:
	 *    EB    ??             # jmp   1f
	 *    00    00 00 00 00 00 # ...
	 */
	xorl  %eax, %eax
	movb  1(%ebx), %ah   /* Operand of `jz' */
	addb  $5, %ah        /* Adjust for additional offset */
	movb  $0xeb, %al
	pushl_cfi $0
	pushl_cfi %eax
	/* Atomically re-write the call to our function. */
	fildll (%esp)
	fistpll -5(%ebx) /* Override the selector code */
	addl  $8, %esp
	.cfi_adjust_cfa_offset -8
	/* Adjust the return address */
	subb  $4, %ah
	movzbl %ah, %eax
	addl  %eax, 16(%esp)
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi_r %eax
	ret
	.cfi_endproc
END(libc_x86_syscall_check_sysenter)
















