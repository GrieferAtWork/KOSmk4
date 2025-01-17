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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_RTM32_S
#define GUARD_LIBC_LIBC_ARCH_I386_RTM32_S 1
#define __ASSEMBLER__ 1

#include "rtm.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/host.h>
#include <hybrid/wordbits.h>

#include <cfi.h>
#include <asm/instr/ttest.h>
#include <asm/rtm.h>

#include <syscall.h>

#ifdef CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
#include <asm/cpu-cpuid.h>
#endif /* CONFIG_LIBC_SUPPORTS_HARDWARE_RTM */


#ifdef CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
.section .xdata, "awx"
#else /* CONFIG_LIBC_SUPPORTS_HARDWARE_RTM */
.section .text.crt.system.rtm
#endif /* !CONFIG_LIBC_SUPPORTS_HARDWARE_RTM */


/* Begin  an  RTM operation.  Note that  if  the arch-specific  RTM driver
 * wasn't already loaded into the kernel, it will be loaded automatically,
 * though any error that may happen during this will result in `RTM_NOSYS'
 * begin returned.
 * Note  that while an RTM operation is in progress, only a very small hand
 * full of system calls are allowed to be used. Attempting to use arbitrary
 * system calls, or attempting to access too much system memory in  general
 * will result in this function returning with `RTM_ABORT_CAPACITY', rather
 * than  succeeding.  The following  is a  list of  system calls  which are
 * whitelisted for use during a transaction:
 *   - rtm_begin:  Nested RTM operation
 *   - rtm_end:    End an RTM operation
 *   - rtm_abort:  Abort an RTM operation
 *   - rtm_test:   Check if an RTM operation is in progress (always returns `1')
 * Anything else will most likely result in this system call returning `RTM_ABORT_FAILED'
 * @return: RTM_STARTED : RTM operation was started.
 * @return: RTM_NOSYS   : RTM isn't supposed because the associated driver is missing, or cannot be loaded.
 * @return: RTM_ABORT_* : RTM operation failed (s.a. code from `<kos/rtm.h>') */
INTERN_FUNCTION(libc_rtm_begin)
	.cfi_startproc
#ifdef CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
	.byte 0xb8            /* movl $(-1), %eax */
.Lrtm_begin_maybe_syscall:
	.long 0xffffffff
	/* The following 2 bytes will get overwritten with `xbegin' if
	 * hardware   RTM   support   is   found   to   be  available. */
.Lrtm_begin_maybe_xbegin:
	.byte  0x90 /* nop */
	.byte  0xe9 /* jmp (with 32-bit operand) */
	.reloc ., R_386_PC32, libc_rtm_begin_init;
	.long  -4;
	/* Hardware RTM entered. */
.Lrtm_begin_do_return:
	ret
#else /* CONFIG_LIBC_SUPPORTS_HARDWARE_RTM */
	movl   $(SYS_rtm_begin), %eax
	EXTERN(libc___i386_syscall)
	jmp    libc___i386_syscall
#endif /* !CONFIG_LIBC_SUPPORTS_HARDWARE_RTM */
	.cfi_endproc
END(libc_rtm_begin)
DEFINE_PUBLIC_ALIAS(rtm_begin, libc_rtm_begin)



/* Abort  the   current  transaction   by   having  `rtm_begin()'   return   with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no  transaction  was  in  progress, behave  as  a  no-op.  Otherwise,  this
 * function does not return normally, but returns from the original `rtm_begin()' */
INTERN_FUNCTION(libc_rtm_abort)
	.cfi_startproc
#ifdef CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
	.byte  0xe9       /* jmp 1f; 1: */
.Lrtm_abort_redirection:
	.long  0x00000000
#endif /* CONFIG_LIBC_SUPPORTS_HARDWARE_RTM */
	pushl_cfi_r %ebx
	movl   %ecx, %ebx /* code */
	movl   $(SYS_rtm_abort), %eax
	int    $(0x80)
	popl_cfi_r %ebx
	ret
	.cfi_endproc
END(libc_rtm_abort)
DEFINE_PUBLIC_ALIAS(rtm_abort, libc_rtm_abort)



/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
	.cfi_startproc
.Lrtm_test_redirection_target:
	xorl   %eax, %eax
	xtest
	setz   %al
	ret
INTERN_FUNCTION(libc_rtm_test)
	.byte 0xeb /* jmp8 1f; 1: */
.Lrtm_test_redirection:
	.byte 0x00
	movl   $(SYS_rtm_test), %eax
	int    $(0x80)
	ret
	.cfi_endproc
END(libc_rtm_test)
DEFINE_PUBLIC_ALIAS(rtm_test, libc_rtm_test)


#ifdef CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
/* Check if a transaction is currently in progress
 * @return: ZF=1 : No RTM operation in progress
 * @return: ZF=0 : An RTM operation is currently in progress */
INTERN_FUNCTION(libc___x86_rtm_xtest)
	.cfi_startproc
	movl   $(SYS_rtm_test), %eax
	/* Directly  make  use  of `int80h'  here,  thus reducing  the  overhead in
	 * in case we actually  are executing in the  context of an RTM  operation.
	 * In that  case, by  directly invoking  int80, the  emulator can  directly
	 * branch to the rtm-test code, without having to also emulate the contents
	 * of the `__i386_syscall' function. (where  doing so might actually  cause
	 * problems since it contains self-modifying  code, which the RTM  emulator
	 * isn't designed to deal with) */
	int    $(0x80)
	/* NOTE: The `SYS_rtm_test' system call has some special handling in how
	 *       it returns its result, in that in addition to setting %eax,  it
	 *       also  fills  in  EFLAGS.ZF in  the  same way  that  the `xtest'
	 *       instruction does! */
	ret
	.cfi_endproc
END(libc___x86_rtm_xtest)
DEFINE_PUBLIC_ALIAS(__x86_rtm_xtest, libc___x86_rtm_xtest)
#endif /* CONFIG_LIBC_SUPPORTS_HARDWARE_RTM */




#ifdef CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
.pushsection .text.crt.system.rtm
PRIVATE_FUNCTION(libc_hw_rtm_abort)
	.cfi_startproc
	movzbl %cl, %ecx
	call   1f
	.cfi_adjust_cfa_offset 4
1:	popl_cfi %eax
	addl   $(_GLOBAL_OFFSET_TABLE_ + (. - 1b)), %eax
	leal   .Lxabort_base@GOTOFF(%eax, %ecx, 4), %eax
	jmpl   *%eax
END(libc_hw_rtm_abort)
PRIVATE_FUNCTION(.Lxabort_base)
	.Lxabort_imm = 0
.rept 256
	.byte 0xc6 /* xabort $.Lxabort_imm */
	.byte 0xf8
	.byte .Lxabort_imm
.Lxabort_imm = .Lxabort_imm + 1
	.byte 0xcb /* ret */
.endr
	.cfi_endproc
END(.Lxabort_base)
.popsection

.pushsection .text.crt.system.rtm
PRIVATE_FUNCTION(libc_rtm_begin_init)
	.cfi_startproc
	/* We get here in 2 situations:
	 *   - We're yet to check if hardware RTM is supported (likely)
	 *   - Hardware RTM was failed (%eax != _XBEGIN_STARTED) */
	cmpl   $(-1), %eax
	jne    .Lrtm_begin_do_return_or_try_again

	/* Check if hardware RTM is supported */
	pushl_cfi_r %ebx

	/* Check for the `ENVIRON_HW_RTM' variable */
#ifdef ENVIRON_HW_RTM
	.pushsection .rodata.crt.system.rtm
	PRIVATE_OBJECT(str_ENVIRON_HW_RTM)
		.asciz ENVIRON_HW_RTM
	END(str_ENVIRON_HW_RTM)
	.popsection
	call   1f
	.cfi_adjust_cfa_offset 4
1:	popl_cfi %ebx
	addl   $(_GLOBAL_OFFSET_TABLE_ + (. - 1b)), %ebx
	leal   str_ENVIRON_HW_RTM@GOTOFF(%ebx), %ebx
	pushl_cfi %ebx
	EXTERN(libc_getenv)
	call   libc_getenv
	addl   $(4), %esp
	.cfi_adjust_cfa_offset -4
	testl  %eax, %eax
	jz     1f
	cmpb   $(0), 0(%eax)
	jz     1f /* strlen(%eax) == 1 */
	cmpb   $(0), 1(%eax)
	jnz    1f /* strlen(%eax) != 1 */
	movb   0(%eax), %al
	cmpb   $('1'), %al
	je     .Lrtm_begin_modify_supported     /* Force-enabled */
	cmpb   $('0'), %al
	je     .Lrtm_begin_modify_not_supported /* Force-disabled */
1:	/* Fallthru */
#endif /* ENVIRON_HW_RTM */
	movl   $(7), %eax
	cpuid
	ttest  mask=CPUID_7B_RTM, loc=%ebx
	jz     .Lrtm_begin_modify_not_supported
#ifdef ENVIRON_HW_RTM
.Lrtm_begin_modify_supported:
#endif /* ENVIRON_HW_RTM */

	.cfi_remember_state
	call   1f
	.cfi_adjust_cfa_offset 4
1:	popl_cfi %ebx
	addl   $(_GLOBAL_OFFSET_TABLE_ + (. - 1b)), %ebx

	/* Hardware RTM is supported! */

	/* Re-write helper function: `rtm_abort()' */
	leal   (libc_hw_rtm_abort@GOTOFF)(%ebx), %ecx
	leal   (.Lrtm_abort_redirection@GOTOFF + 4)(%ebx), %eax
	subl   %eax, %ecx
	movl   %ecx, 0(%eax) /* Re-direct `rtm_abort()' */

	/* Re-write helper function: `__x86_rtm_xtest' to become `xtest; ret' */
	movl   $(ENCODE_INT32(0x0f, 0x01, 0xd6, /* xtest */ \
	                      0xc3              /* ret */   \
	       )), libc___x86_rtm_xtest@GOTOFF(%ebx)

	/* Redirect `rtm_test()' to use `xtest' */
	movb   $((.Lrtm_test_redirection + 1) -   \
	          .Lrtm_test_redirection_target), \
	       .Lrtm_test_redirection@GOTOFF(%ebx)

	/* Re-write   the   first   2   bytes   at   `.Lrtm_begin_maybe_xbegin'
	 * with {0xc7, 0xf8} (which are the bytes corresponding to the `xbegin'
	 * instruction),  and in a second step, write  all zeroes to the next 4
	 * bytes in order to modify the failure-branch to point to `ret' above.
	 */

	/* `movl $.Lrtm_begin_maybe_xbegin, %eax' */
	leal   .Lrtm_begin_maybe_xbegin@GOTOFF(%ebx), %eax

	/* Write the `xbegin' instruction */
	movw   $(ENCODE_INT16(0xc7, 0xf8)), 0(%eax) /* Replace nop+jmp with `xbegin' */
	movl   $(0),                        2(%eax) /* Clear out the jump-offset operand */

	cpuid /* Serializing instruction is needed to flush the instruction cache. */
	popl_cfi_r %ebx
	jmp    libc_rtm_begin
.Lrtm_begin_do_return_or_try_again:
	cmpl   $(SYS_rtm_begin), %eax
	jne    .Lrtm_begin_do_return /* RTM failure */
	/* Race condition: Some  other thread is currently re-writing the entry
	 *                 code for `rtm_begin()', but has yet to get around to
	 *                 re-directing the `jmp' above, so instead of pointing
	 *                 to `libc___i386_syscall', it still points to here.
	 * -> Handle this case by manaully jumping to the intended target.
	 * NOTE: This can only happen when some other thread is currently modifying
	 *       the code that caused us to get here! */
	EXTERN(libc___i386_syscall)
	jmp    libc___i386_syscall

	.cfi_restore_state
.Lrtm_begin_modify_not_supported:
	/* Re-write the above code by doing the following (in order):
	 * >> *(u32 *)(.Lrtm_begin_maybe_syscall)    = SYS_rtm_begin;
	 * >> *(u32 *)(.Lrtm_begin_maybe_xbegin + 2) = RELPTR(libc___i386_syscall);
	 * Doing   this  will   re-write  the   code  of   `rtm_begin'  to  become:
	 * >> movl  $SYS_rtm_begin, %eax
	 * >> jmp   libc___i386_syscall
	 */
	call   1f
	.cfi_adjust_cfa_offset 4
1:	popl_cfi %ebx
	addl   $(_GLOBAL_OFFSET_TABLE_ + (. - 1b)), %ebx
	leal   .Lrtm_begin_maybe_syscall@GOTOFF(%ebx), %eax
	EXTERN(libc___i386_syscall)
	leal   (libc___i386_syscall@GOTOFF - ((.Lrtm_begin_do_return - .Lrtm_begin_maybe_syscall)))(%ebx), %ecx
	subl   %eax, %ecx /* %ecx = OFFSET_FROM(".Lrtm_begin_do_return" TO "libc___i386_syscall") */
	/* Modfy code. */
	movl   $(SYS_rtm_begin), 0(%eax)
	movl   %ecx, ((.Lrtm_begin_maybe_xbegin - .Lrtm_begin_maybe_syscall) + 2)(%eax) /* jmp    libc___i386_syscall */

	cpuid  /* Serializing instruction is needed to flush the instruction cache. */
	popl_cfi_r %ebx
	jmp    libc_rtm_begin
	.cfi_endproc
END(libc_rtm_begin_init)
.popsection
#endif /* CONFIG_LIBC_SUPPORTS_HARDWARE_RTM */






.section .text.crt.system.rtm
/* End a transaction
 * If the transaction was successful, return normally
 * If the transaction failed, `rtm_begin()' returns `RTM_ABORT_*'
 * If no transaction was in progress, an `E_ILLEGAL_OPERATION' exception is thrown */
INTERN_FUNCTION(libc_rtm_end)
	.cfi_startproc
	/* Since we can assume that we're already inside of an RTM operation,
	 * we   know  that  we   can  only  get   here  in  2  circumstances:
	 *   - The real hardware has support for RTM, in which case it should
	 *     also   be   able   to   recognize   the   `xend'  instruction.
	 *   - We're  being emulated by  the `rtm' driver,  in which case its
	 *     instruction decoder is able to detect the `xend'  instruction,
	 *     and handle it as an alias for the `sys_rtm_end()' system call. */
	xend
	/* RTM operation successfully completed! */
	ret
	.cfi_endproc
END(libc_rtm_end)
DEFINE_PUBLIC_ALIAS(rtm_end, libc_rtm_end)




#endif /* GUARD_LIBC_LIBC_ARCH_I386_RTM32_S */
