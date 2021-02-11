/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ARCH_I386_SYSCALL_BASE32_S
#define GUARD_LIBC_LIBC_ARCH_I386_SYSCALL_BASE32_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <asm/cfi.h>
#include <asm/cpu-cpuid.h>
#include <asm/instr/ttest.h>
#include <sys/syscall.h>

.section .text.crt.syscall.selector
INTERN_FUNCTION(libc_x86_syscall_check_sysenter)
	.cfi_startproc
	pushl_cfi_r %eax
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx
	movl   $(1), %eax
	cpuid
	movl   16(%esp), %ebx /* Return address */
	ttest  mask=CPUID_1D_SEP, loc=%edx
	jz    .Lnot_supported
	/* if (Family == 6 && Model < 3 && Stepping < 3)
	 *     goto .Lnot_supported; */
	movl   %eax, %ecx
	andl   $(CPUID_1A_FAMILY_M), %ecx
	cmpl   $(6 << CPUID_1A_FAMILY_S), %ecx
	jne    .Lis_supported  /* if (Family != 6) goto .Lis_supported; */
	movl   %eax, %ecx
	andl   $(CPUID_1A_MODEL_M), %ecx
#if CPUID_1A_MODEL_S != 0
	shrl   $(CPUID_1A_MODEL_S), %ecx
#endif /* CPUID_1A_MODEL_S != 0 */
	cmpl   $(3), %ecx
	jae    .Lis_supported  /* if (Model >= 3) goto .Lis_supported; */
	movl   %eax, %ecx
	andl   $(CPUID_1A_STEPPING_M), %ecx
#if CPUID_1A_STEPPING_S != 0
	shrl   $(CPUID_1A_STEPPING_S), %ecx
#endif /* CPUID_1A_STEPPING_S != 0 */
	cmpl   $(3), %ecx
	/* if (Stepping >= 3) goto .Lis_supported; */
	/* if (Stepping < 3) goto .Lnot_supported; */
	jb     .Lnot_supported
.Lis_supported:
	.cfi_remember_state
	/* Override call to this function:
	 * ORIGNAL  (8  bytes  of   code):
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
	shll   $(24), %eax
	orl    $(0x00909090), %eax
	pushl_cfi  %eax
	pushl_cfi  $(0x90909090)
	fildll (%esp)
	fistpll -5(%ebx) /* Override the selector code */
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	/* Adjust the return address */
	addl   $(2), 16(%esp)
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi_r %eax
	ret
.Lnot_supported:
	.cfi_restore_state
	/* Override call to this function:
	 * ORIGNAL  (8  bytes  of   code):
	 *    E8    ?? ?? ?? ??    # call  libc_x86_syscall_check_sysenter
	 * %ebx:
	 *    74    ??             # jz    1f
	 *    ??                   # ...
	 * OVERRIDE:
	 *    EB    ??             # jmp   1f
	 *    00    00 00 00 00 00 # ...
	 */
	xorl   %eax, %eax
	movb   1(%ebx), %ah   /* Operand of `jz' */
	addb   $(5), %ah        /* Adjust for additional offset */
	movb   $(0xeb), %al
	pushl_cfi $(0)
	pushl_cfi %eax
	/* Atomically re-write the call to our function. */
	fildll (%esp)
	fistpll -5(%ebx) /* Override the selector code */
	addl   $(8), %esp
	.cfi_adjust_cfa_offset -8
	/* Adjust the return address */
	subb   $(4), %ah
	movzbl %ah, %eax
	addl   %eax, 16(%esp)
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi_r %eax
	ret
	.cfi_endproc
END(libc_x86_syscall_check_sysenter)



.section .text.crt.syscall.x86_sysenter_common
INTERN_FUNCTION(libc_x86_sysenter_common)
	.cfi_startproc
	popl_cfi %edi     /* EDI = RETURN_PC */
	.cfi_register %eip, %edi
	movl   %esp, %ebp /* EBP = RETURN_SP */
	sysenter
	.cfi_endproc
END(libc_x86_sysenter_common)


INTERN(libc_x86_syscall_check_sysenter)

.section .xdata.crt.syscall.__i386_syscall, "awx"
INTERN_FUNCTION(libc___i386_syscall)
	.cfi_startproc
	/* Check  if host supports the `sysenter' instruction,
	 * and re-write this code during the first invocation. */
	call   libc_x86_syscall_check_sysenter
	.byte  0x74
	.reloc ., R_386_PC8, 1f
	.byte  0xff /* jz 1f */

	pushl_cfi_r %ebp
	pushl_cfi_r %edi

	call   libc_x86_sysenter_common

	popl_cfi_r %edi
	popl_cfi_r %ebp

	ret

1:	int    $(0x80)
	ret
	.cfi_endproc
END(libc___i386_syscall)

.section .xdata.crt.syscall.__i386_Xsyscall, "awx"
INTERN_FUNCTION(libc___i386_Xsyscall)
	.cfi_startproc
	/* Check  if host supports the `sysenter' instruction,
	 * and re-write this code during the first invocation. */
	call   libc_x86_syscall_check_sysenter
	.byte  0x74
	.reloc ., R_386_PC8, 1f
	.byte  0xff /* jz 1f */

	pushl_cfi_r %edi
	pushl_cfi_r %ebp

	std /* Enable exceptions */
	call   libc_x86_sysenter_common
	cld /* Disable exceptions */

	popl_cfi_r %ebp
	popl_cfi_r %edi

	ret

1:	std /* Enable exceptions */
	int    $(0x80)
	cld /* Disable exceptions */
	ret
	.cfi_endproc
END(libc___i386_Xsyscall)

.section .text.crt.system.utility.syscall
INTERN_FUNCTION(libc_syscall)
	.cfi_startproc
	pushl_cfi_r %ebx
	pushl_cfi_r %esi
	pushl_cfi_r %edi
	pushl_cfi_r %ebp
	movl   20(%esp), %eax /* sysno */
	movl   24(%esp), %ebx /* arg #0 */
	movl   28(%esp), %ecx /* arg #1 */
	movl   32(%esp), %edx /* arg #2 */
	movl   36(%esp), %esi /* arg #3 */
	movl   40(%esp), %edi /* arg #4 */
	movl   44(%esp), %ebp /* arg #5 */
	int    $(0x80)
	cmpl   $-4096, %eax /* Check for error. */
	ja     1f
	.cfi_remember_state
	popl_cfi_r %ebp
	popl_cfi_r %edi
	popl_cfi_r %esi
	popl_cfi_r %ebx
	ret
	.cfi_restore_state
1:	negl   %eax
	movl   %eax, %ecx
	INTERN(libc_seterrno)
	call   libc_seterrno /* errno = -return */
	movl   %eax, %edx /* Extend to 64 bits. */
	popl_cfi_r %ebp
	popl_cfi_r %edi
	popl_cfi_r %esi
	popl_cfi_r %ebx
	ret
	.cfi_endproc
END(libc_syscall)
DEFINE_INTERN_ALIAS(libc_syscall64, libc_syscall)
DEFINE_PUBLIC_ALIAS(syscall, libc_syscall)
DEFINE_PUBLIC_ALIAS(syscall64, libc_syscall)


.section .text.crt.except.system.utility.Syscall
INTERN_FUNCTION(libc_Syscall)
	.cfi_startproc
	pushl_cfi_r %ebx
	pushl_cfi_r %esi
	pushl_cfi_r %edi
	pushl_cfi_r %ebp
	movl   20(%esp), %eax /* sysno */
	movl   24(%esp), %ebx /* arg #0 */
	movl   28(%esp), %ecx /* arg #1 */
	movl   32(%esp), %edx /* arg #2 */
	movl   36(%esp), %esi /* arg #3 */
	movl   40(%esp), %edi /* arg #4 */
	movl   44(%esp), %ebp /* arg #5 */
	std /* Enable exceptions */
	int    $(0x80)
	cld /* Disable exceptions */
	popl_cfi_r %ebp
	popl_cfi_r %edi
	popl_cfi_r %esi
	popl_cfi_r %ebx
	ret
	.cfi_endproc
END(libc_Syscall)
DEFINE_PUBLIC_ALIAS(Syscall, libc_Syscall)

/* Because we don't save/restore EDX, the regular system call is already 64-bit capable! */
DEFINE_INTERN_ALIAS(libc_Syscall64, libc_Syscall)
DEFINE_PUBLIC_ALIAS(Syscall64, libc_Syscall)


/* Provide CRT support for inline system calls
 * These functions behave identical to invoking a system call
 * using `int 80h', in that arguments are passed through  the
 * same registers.
 * The number of registers taken by a system call can be determined
 * by  loading  `__WANT_SYSCALL_REGISTER_COUNT'  information,   and
 * expanding  the  `__NRRC_*'  macro  associated  with  some  given
 * system call. */
DEFINE_PUBLIC_ALIAS(__i386_syscall, libc___i386_syscall)
DEFINE_PUBLIC_ALIAS(__i386_Xsyscall, libc___i386_Xsyscall)

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_SYSCALL_BASE32_S */
