/* HASH 0x5d854235 */
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
#include <sys/syscall.h>

#if defined(CONFIG_SYSCALL_USING_SYSENTER) || \
    defined(CONFIG_SYSCALL_USING_INT80) || \
    defined(CONFIG_SYSCALL_OPTIMIZE_SIZE)
#include "syscall_selector32.S.inl"
#endif /* ... */

#if !(defined(CONFIG_SYSCALL_USING_SYSENTER) || \
    (!defined(CONFIG_SYSCALL_USING_INT80) && \
     !defined(CONFIG_SYSCALL_OPTIMIZE_SIZE))) || \
      defined(CONFIG_SYSCALL_EXCLUDE_WITHOUTEXCEPT)
.section .text.crt.syscall.x86_sysenter_common
INTERN_FUNCTION(libc_x86_sysenter_common)
	.cfi_startproc
	popl_cfi %edi     /* EDI = RETURN_PC */
	.cfi_register %eip, %edi
	movl   %esp, %ebp /* EBP = RETURN_SP */
	clc
	sysenter
	.cfi_endproc
END(libc_x86_sysenter_common)
#endif /* ... */
#if !(defined(CONFIG_SYSCALL_USING_SYSENTER) || \
    (!defined(CONFIG_SYSCALL_USING_INT80) && \
     !defined(CONFIG_SYSCALL_OPTIMIZE_SIZE))) || \
      defined(CONFIG_SYSCALL_EXCLUDE_WITHEXCEPT)
.section .text.crt.syscall.x86_sysenter_Xcommon
INTERN_FUNCTION(libc_x86_sysenter_Xcommon)
	.cfi_startproc
	popl_cfi %edi     /* EDI = RETURN_PC */
	.cfi_register %eip, %edi
	movl   %esp, %ebp /* EBP = RETURN_SP */
	stc
	sysenter
	.cfi_endproc
END(libc_x86_sysenter_Xcommon)
#endif /* ... */


INTERN(libc_x86_syscall_check_sysenter)

.section .xdata.crt.syscall.__i386_syscall0, "awx"
INTERN_FUNCTION(libc___i386_syscall0)
	.cfi_startproc
	/* Check if host supports the `sysenter' instruction,
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

1:	clc
	int    $0x80
	ret
	.cfi_endproc
END(libc___i386_syscall0)

.section .xdata.crt.syscall.__i386_syscall5, "awx"
INTERN_FUNCTION(libc___i386_syscall5)
	.cfi_startproc
	/* Check if host supports the `sysenter' instruction,
	 * and re-write this code during the first invocation. */
	call   libc_x86_syscall_check_sysenter
	.byte  0x74
	.reloc ., R_386_PC8, 1f
	.byte  0xff /* jz 1f */

	pushl_cfi_r %ebp   /* ARG#5 */
	pushl_cfi_r %edi   /* ARG#4 */

	movl   %esp, %ebp  /* Extended argument-list pointer */
	call   libc_x86_sysenter_common

	popl_cfi_r %edi
	popl_cfi_r %ebp

	ret

1:	clc
	int    $0x80
	ret
	.cfi_endproc
END(libc___i386_syscall5)

.section .xdata.crt.syscall.__i386_Xsyscall0, "awx"
INTERN_FUNCTION(libc___i386_Xsyscall0)
	.cfi_startproc
	/* Check if host supports the `sysenter' instruction,
	 * and re-write this code during the first invocation. */
	call   libc_x86_syscall_check_sysenter
	.byte  0x74
	.reloc ., R_386_PC8, 1f
	.byte  0xff /* jz 1f */

	pushl_cfi_r %edi
	pushl_cfi_r %ebp

	call   libc_x86_sysenter_Xcommon

	popl_cfi_r %ebp
	popl_cfi_r %edi

	ret

1:	stc
	int    $0x80
	ret
	.cfi_endproc
END(libc___i386_Xsyscall0)

.section .xdata.crt.syscall.__i386_Xsyscall5, "awx"
INTERN_FUNCTION(libc___i386_Xsyscall5)
	.cfi_startproc
	/* Check if host supports the `sysenter' instruction,
	 * and re-write this code during the first invocation. */
	call   libc_x86_syscall_check_sysenter
	.byte  0x74
	.reloc ., R_386_PC8, 1f
	.byte  0xff /* jz 1f */

	pushl_cfi_r %ebp   /* ARG#5 */
	pushl_cfi_r %edi   /* ARG#4 */

	movl   %esp, %ebp  /* Extended argument-list pointer */
	call   libc_x86_sysenter_Xcommon

	popl_cfi_r %edi
	popl_cfi_r %ebp

	ret

1:	stc
	int    $0x80
	ret
	.cfi_endproc
END(libc___i386_Xsyscall5)


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
	clc
	int    $0x80
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
	stc
	int    $0x80
	popl_cfi_r %ebp
	popl_cfi_r %edi
	popl_cfi_r %esi
	popl_cfi_r %ebx
	ret
	.cfi_endproc
END(libc_Syscall)
DEFINE_INTERN_ALIAS(libc_Syscall64, libc_Syscall)
DEFINE_PUBLIC_ALIAS(Syscall, libc_Syscall)
DEFINE_PUBLIC_ALIAS(Syscall64, libc_Syscall)


/* Provide CRT support for inline system calls
 * These functions behave identical to invoking a system call
 * using `int 80h', in that arguments are passed through the
 * same registers.
 * Note however that system calls taking 0...4 argument registers
 * need to call `__i386_syscall0', whilst calls with 5...6 registers
 * need to call `__i386_syscall5'.
 * The number of registers taken by a system call can be determined
 * by loading `__WANT_SYSCALL_ARGUMENT_COUNT_386' information, and
 * expanding the `__NRAC386_*' macro associated with some given
 * system call.
 */
#ifndef CONFIG_SYSCALL_NO_EXPORTS
DEFINE_PUBLIC_ALIAS(__i386_syscall0, libc___i386_syscall0)
DEFINE_PUBLIC_ALIAS(__i386_syscall5, libc___i386_syscall5)
DEFINE_PUBLIC_ALIAS(__i386_Xsyscall0, libc___i386_Xsyscall0)
DEFINE_PUBLIC_ALIAS(__i386_Xsyscall5, libc___i386_Xsyscall5)
#endif /* !CONFIG_SYSCALL_NO_EXPORTS */













