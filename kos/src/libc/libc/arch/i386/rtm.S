/* HASH CRC-32:0x6bb53aea */
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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_RTM_S
#define GUARD_LIBC_LIBC_ARCH_I386_RTM_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <hybrid/host.h>
#include <hybrid/wordbits.h>

#include <asm/cfi.h>
#include <asm/instr/compat.h>
#include <asm/instr/movzxq.h>
#include <asm/rtm.h>

#include <syscall.h>


/* TODO: On x86_64, the self-modifying code needed for hardware
 *       RTM support is currently the only reason why libc.so needs
 *       a .xdata section (on i386, .xdata is also needed for the
 *       self-modifying base-code used for invoking system calls)
 * -> As such, .xdata on x86_64 slows down libc initialization!
 *    We can fix this by placing all of the RTM xdata-related code
 *    in a seperate, page-aligned section, which we then mprotect()
 *    at runtime to add write permissions, thus resulting in one
 *    less program header needing to be mapped when libc is loaded! */

/* TODO: The assembly used on x86_64 ended up being significantly
 *       different from the assembly used on i386. As such, the amount
 *       of `#ifdef __x86_64__' is way too high in this file, and the
 *       contents of this file should once again be split into rtm32.S
 *       and rtm64.S, leaving this file to be deleted. */

/* Enable support for hardware RTM (s.a. `CPUID_7B_RTM') */
#undef CONFIG_SUPPORT_HARDWARE_RTM
#if 1
#define CONFIG_SUPPORT_HARDWARE_RTM 1
#endif


#ifdef CONFIG_SUPPORT_HARDWARE_RTM
#include <asm/cpu-cpuid.h>
#endif /* CONFIG_SUPPORT_HARDWARE_RTM */


#ifndef __x86_64__
#define syscall         call libc___i386_syscall
#define syscall_and_ret jmp libc___i386_syscall
#else /* !__x86_64__ */
#define syscall_and_ret syscall; ret
#endif /* __x86_64__ */

#ifdef CONFIG_SUPPORT_HARDWARE_RTM
.section .xdata.crt.system.rtm, "awx"
#else /* CONFIG_SUPPORT_HARDWARE_RTM */
.section .text.crt.system.rtm
#endif /* !CONFIG_SUPPORT_HARDWARE_RTM */

#ifdef __x86_64__
#define R_PC32 R_X86_64_PC32
#else /* __x86_64__ */
#define R_PC32 R_386_PC32
#endif /* !__x86_64__ */


/* Begin an RTM operation. Note that if the arch-specific RTM driver
 * wasn't already loaded into the kernel, it will be loaded automatically,
 * though any error that may happen during this will result in `RTM_NOSYS'
 * begin returned.
 * Note that while an RTM operation is in progress, only a very small hand
 * full of system calls are allowed to be used. Attempting to use arbitrary
 * system calls, or attempting to access too much system memory in general
 * will result in this function returning with `RTM_ABORT_CAPACITY', rather
 * than succeeding. The following is a list of system calls which are
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
#ifdef CONFIG_SUPPORT_HARDWARE_RTM
#ifdef __x86_64__
	.byte 0x48            /* movq $(-1), %rax */
	.byte 0xc7
	.byte 0xc0
#else /* __x86_64__ */
	.byte 0xb8            /* movl $(-1), %eax */
#endif /* __x86_64__ */
.Lrtm_begin_maybe_syscall:
	.long 0xffffffff
	/* The following 2 bytes will get overwritten with `xbegin' if
	 * hardware RTM support is found to be available. */
.Lrtm_begin_maybe_xbegin:
	.byte  0x90 /* nop */
	.byte  0xe9 /* jmp (with 32-bit operand) */
	.reloc ., R_PC32, libc_rtm_begin_init;
	.long  -4;
	/* Hardware RTM entered. */
.Lrtm_begin_do_return:
	ret
#else /* CONFIG_SUPPORT_HARDWARE_RTM */
	movP   $(SYS_rtm_begin), %Pax
	clc
	syscall_and_ret
#endif /* !CONFIG_SUPPORT_HARDWARE_RTM */
	.cfi_endproc
END(libc_rtm_begin)
DEFINE_PUBLIC_ALIAS(rtm_begin, libc_rtm_begin)



/* Abort the current transaction by having `rtm_begin()' return with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no transaction was in progress, behave as a no-op. Otherwise, this
 * function does not return normally, but returns from the original `rtm_begin()' */
INTERN_FUNCTION(libc_rtm_abort)
	.cfi_startproc
#ifndef __x86_64__
#ifdef CONFIG_SUPPORT_HARDWARE_RTM
	.byte  0xe9       /* jmp 1f; 1: */
.Lrtm_abort_redirection:
	.long  0x00000000
#endif /* CONFIG_SUPPORT_HARDWARE_RTM */
	pushl_cfi_r %ebx
	movl   %ecx, %ebx /* code */
	movl   $(SYS_rtm_abort), %eax
#else /* !__x86_64__ */
	.byte  0x48
.Lrtm_abort_redirection:
	.byte  0xc7, 0xc0 /* movq $(SYS_rtm_abort), %rax */
	.long  (SYS_rtm_abort & 0xffffffff)
#endif /* __x86_64__ */
	.byte  0xf8             /* clc */
	syscall
#ifndef __x86_64__
	popl_cfi_r %ebx
#endif /* !__x86_64__ */
	ret
	.cfi_endproc
END(libc_rtm_abort)
DEFINE_PUBLIC_ALIAS(rtm_abort, libc_rtm_abort)



/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
INTERN_FUNCTION(libc_rtm_test)
	.cfi_startproc
	movP   $(SYS_rtm_test), %Pax
	clc
	syscall_and_ret
	xorP   %Pax, %Pax
	xtest
	setz   %al
	ret
	.cfi_endproc
END(libc_rtm_test)
DEFINE_PUBLIC_ALIAS(rtm_test, libc_rtm_test)


#ifdef CONFIG_SUPPORT_HARDWARE_RTM
/* Check if a transaction is currently in progress
 * @return: ZF=1 : No RTM operation in progress
 * @return: ZF=0 : An RTM operation is currently in progress */
INTERN_FUNCTION(libc___x86_rtm_xtest)
	.cfi_startproc
	movP   $(SYS_rtm_test), %Pax
	clc
	syscall
	/* TODO: Extend the ABI behavior of `SYS_rtm_test' in the context
	 *       of being invoked via `int80', `sysenter' or `syscall' to
	 *       set/clear EFLAGS.ZF such that the behavior matches that
	 *       of `xtest'
	 * i.e. The assembly wrappers for this system call set EFLAGS.ZF
	 *      within the associated IRET tail. */
	/* Must transform:
	 *    %Pax == 0 -> ZF=1
	 *    %Pax != 0 -> ZF=0 */
	notP   %Pax
	testP  %Pax, %Pax
	ret
	.cfi_endproc
END(libc___x86_rtm_xtest)
DEFINE_PUBLIC_ALIAS(__x86_rtm_xtest, libc___x86_rtm_xtest)
#endif /* CONFIG_SUPPORT_HARDWARE_RTM */




#ifdef CONFIG_SUPPORT_HARDWARE_RTM
.pushsection .text.crt.system.rtm
PRIVATE_FUNCTION(libc_hw_rtm_abort)
	.cfi_startproc
#ifdef __x86_64__
	movzbq %dil, %rdi
	leaq   .Lxabort_base(%rip), %rax
	leaq   (%rax, %rdi, 4), %rax
	jmpq   *%rax
#else /* __x86_64__ */
	movzbl %cl, %ecx
	call   1f
	.cfi_adjust_cfa_offset 4
1:	popl_cfi %eax
	addl   $(_GLOBAL_OFFSET_TABLE_ - (. - 1b)), %eax
	leal   .Lxabort_base@GOTOFF(%eax, %ecx, 4), %eax
	jmpl   *%eax
#endif /* !__x86_64__ */
	.cfi_endproc
END(libc_hw_rtm_abort)


PRIVATE_FUNCTION(.Lxabort_base)
	.cfi_startproc
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
	cmpP   $(-1), %Pax
#ifdef __x86_64__
	jne    .Lrtm_begin_do_return
#else /* __x86_64__ */
	jne    .Lrtm_begin_do_return_or_try_again
#endif /* !__x86_64__ */
	/* Check if hardware RTM is supported */
	pushP_cfi_r %Pbx
	movl   $(7), %eax
	cpuid
	testl  $(CPUID_7B_RTM), %ebx
	jz     .Lrtm_begin_modify_not_supported
	.cfi_remember_state
#ifndef __x86_64__
	call   1f
	.cfi_adjust_cfa_offset 4
1:	popl   %ebx
	addl   $(_GLOBAL_OFFSET_TABLE_ - (. - 1b)), %ebx
#endif /* !__x86_64__ */

#ifdef __x86_64__
#define LOADSYM_SYM(s) s
#define LOADSYM_REG    %rip
#else /* __x86_64__ */
#define LOADSYM_SYM(s) s@GOTOFF
#define LOADSYM_REG    %ebx
#endif /* !__x86_64__ */

	/* Hardware RTM is supported! */

	/* Re-write helper function: `rtm_abort()' */
	leaP   (LOADSYM_SYM(libc_hw_rtm_abort))(LOADSYM_REG), %Pcx
	leaP   (LOADSYM_SYM(.Lrtm_abort_redirection) + 4)(LOADSYM_REG), %Pax
	subP   %Pax, %Pcx
#ifdef __x86_64__
	shlq   $(8), %rcx
	movabs $(ENCODE_INT64(0xe9, /* jmp libc_hw_rtm_abort */          \
	                      0x00, /* ... */                            \
	                      0x00, /* ... */                            \
	                      0x00, /* ... */                            \
	                      0x00, /* ... */                            \
	                      INT64_BYTE(SYS_rtm_abort & 0xffffffff, 2), \
	                      INT64_BYTE(SYS_rtm_abort & 0xffffffff, 3), \
	                      0xf8  /* clc */                            \
	       )), %rdx
	orq    %rcx, %rdx /* Fill in the jump-offset to `libc_hw_rtm_abort' */
	/* Re-write the first 8 bytes of `rtm_abort()' to become `jmp libc_hw_rtm_abort' */
	movq   %rdx, -1(%rax)
#else /* __x86_64__ */
	movl   %ecx, 0(%eax) /* Re-direct `rtm_abort()' */
#endif /* !__x86_64__ */

	/* Re-write helper function: `__x86_rtm_xtest' to become `xtest; ret' */
	movl   $(ENCODE_INT32(0x0f, 0x01, 0xd6, /* xtest */ \
	                      0xc3              /* ret */   \
	       )), LOADSYM_SYM(libc___x86_rtm_xtest)(LOADSYM_REG)

	/* TODO: rtm_test must become:
	 *     xorP   %Pax, %Pax
	 *     xtest
	 *     setz   %al
	 *     ret
	 */


	/* Re-write the first 2 bytes at `.Lrtm_begin_maybe_xbegin'
	 * with {0xc7, 0xf8} (which are the bytes corresponding to the `xbegin'
	 * instruction), and in a second step, write all zeroes to the next 4
	 * bytes in order to modify the failure-branch to point to `ret' above.
	 */

	/* `movl $.Lrtm_begin_maybe_xbegin, %Pax' */
#ifdef __x86_64__
	leaq   .Lrtm_begin_maybe_xbegin(%rip), %rax
#else /* __x86_64__ */
	leal   .Lrtm_begin_maybe_xbegin@GOTOFF(%ebx), %eax
#endif /* !__x86_64__ */

	/* Write the `xbegin' instruction */
	movw   $(ENCODE_INT16(0xc7, 0xf8)), 0(%Pax) /* Replace nop+jmp with `xbegin' */
	movl   $(0),                        2(%Pax) /* Clear out the jump-offset operand */

	cpuid /* Serializing instruction is needed to flush the instruction cache. */
	popP_cfi_r %Pbx
	jmp    libc_rtm_begin
#ifndef __x86_64__
.Lrtm_begin_do_return_or_try_again:
	cmpl   $(SYS_rtm_begin), %eax
	jne    .Lrtm_begin_do_return /* RTM failure */
	/* Race condition: Some other thread is currently re-writing the entry
	 *                 code for `rtm_begin()', but has yet to get around to
	 *                 re-directing the `jmp' above, so instead of pointing
	 *                 to `libc___i386_syscall', it still points to here.
	 * -> Handle this case by manaully jumping to the intended target.
	 * NOTE: This can only happen when some other thread is currently modifying
	 *       the code that caused us to get here! */
	jmp    libc___i386_syscall
#endif /* !__x86_64__ */

	.cfi_restore_state
.Lrtm_begin_modify_not_supported:
#ifdef __x86_64__
#if !(SYS_rtm_begin & __UINT64_C(0x8000000000000000))
#error "The sysno of `SYS_rtm_begin' must be negative!"
#endif /* !(SYS_rtm_begin & __UINT64_C(0x8000000000000000)) */
	/* Atomically write 8 bytes at `.Lrtm_begin_maybe_syscall':
	 * [0] = (SYS_rtm_begin & 0x000000ff)
	 * [1] = (SYS_rtm_begin & 0x0000ff00) >> 8
	 * [2] = (SYS_rtm_begin & 0x00ff0000) >> 16
	 * [3] = (SYS_rtm_begin & 0xff000000) >> 24
	 * [4] = 0xf8   // clc
	 * [5] = 0x0f
	 * [6] = 0x05   // syscall
	 * [7] = 0xc3   // retq
	 *
	 * By doing this, the function `rtm_begin()' gets re-written
	 * such that it will invoke the system call used for emulation
	 * of RTM operations. */
	movabs $(ENCODE_INT64(/* [0] = */ (SYS_rtm_begin & 0x000000ff),       \
	                      /* [1] = */ (SYS_rtm_begin & 0x0000ff00) >> 8,  \
	                      /* [2] = */ (SYS_rtm_begin & 0x00ff0000) >> 16, \
	                      /* [3] = */ (SYS_rtm_begin & 0xff000000) >> 24, \
	                      /* [4] = */ 0xf8, /* clc */                     \
	                      /* [5] = */ 0x0f,                               \
	                      /* [6] = */ 0x05, /* syscall */                 \
	                      /* [7] = */ 0xc3  /* retq */                    \
	       )), %rax
	movq   %rax, .Lrtm_begin_maybe_syscall(%rip)
#else /* __x86_64__ */
	/* Re-write the above code by doing the following (in order):
	 * >> *(u32 *)(.Lrtm_begin_maybe_syscall)    = SYS_rtm_begin;
	 * >> *(u32 *)(.Lrtm_begin_maybe_xbegin + 0) = 0xf8;
	 * >> *(u32 *)(.Lrtm_begin_maybe_xbegin + 2) = RELPTR(libc___i386_syscall);
	 * Doing this will re-write the code of `rtm_begin' to become:
	 * >> movl  $SYS_rtm_begin, %eax
	 * >> clc
	 * >> jmp   libc___i386_syscall
	 */
	call   1f
	.cfi_adjust_cfa_offset 4
1:	popl   %ebx
	addl   $(_GLOBAL_OFFSET_TABLE_ - (. - 1b)), %ebx
	leal   .Lrtm_begin_maybe_syscall@GOTOFF(%ebx), %eax
	leal   (libc___i386_syscall@GOTOFF - ((.Lrtm_begin_do_return - .Lrtm_begin_maybe_syscall)))(%ebx), %ecx
	subl   %eax, %ecx /* %ecx = OFFSET_FROM(".Lrtm_begin_do_return" TO "libc___i386_syscall") */
	/* Modfy code. */
	movl   $(SYS_rtm_begin), 0(%eax)
	movb   $(0xf8), ((.Lrtm_begin_maybe_xbegin - .Lrtm_begin_maybe_syscall) + 0)(%eax) /* clc */
	movl   %ecx,    ((.Lrtm_begin_maybe_xbegin - .Lrtm_begin_maybe_syscall) + 2)(%eax) /* jmp libc___i386_syscall */
#endif /* !__x86_64__ */

	cpuid  /* Serializing instruction is needed to flush the instruction cache. */
	popP_cfi_r %Pbx
	jmp    libc_rtm_begin
	.cfi_endproc
END(libc_rtm_begin_init)
.popsection
#endif /* CONFIG_SUPPORT_HARDWARE_RTM */






.section .text.crt.system.rtm
/* End a transaction
 * If the transaction was successful, return normally
 * If the transaction failed, `rtm_begin()' returns `RTM_ABORT_*'
 * If no transaction was in progress, an `E_ILLEGAL_OPERATION' exception is thrown */
INTERN_FUNCTION(libc_rtm_end)
	.cfi_startproc
	/* Since we can assume that we're already inside of an RTM operation,
	 * we know that we can only get here in 2 circumstances:
	 *   - The real hardware has support for RTM, in which case it should
	 *     also be able to recognize the `xend' instruction.
	 *   - We're being emulated by the `rtm' driver, in which case its
	 *     instruction decoder is able to detect the `xend' instruction,
	 *     and handle it as an alias for the `sys_rtm_end()' system call. */
	xend
	/* RTM operation successfully completed! */
	ret
	.cfi_endproc
END(libc_rtm_end)
DEFINE_PUBLIC_ALIAS(rtm_end, libc_rtm_end)




#endif /* GUARD_LIBC_LIBC_ARCH_I386_RTM_S */
