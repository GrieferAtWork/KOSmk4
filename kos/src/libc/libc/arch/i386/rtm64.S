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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_RTM64_S
#define GUARD_LIBC_LIBC_ARCH_I386_RTM64_S 1
#define __ASSEMBLER__ 1

#include "rtm.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/host.h>
#include <hybrid/wordbits.h>

#include <asm/cfi.h>
#include <asm/instr/movzxq.h>
#include <asm/instr/ttest.h>
#include <asm/rtm.h>
#include <sys/mman.h>

#include <syscall.h>


#ifdef CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
#include <asm/cpu-cpuid.h>
#endif /* CONFIG_LIBC_SUPPORTS_HARDWARE_RTM */


.section .text.crt.system.rtm
#ifdef CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
PRIVATE_LABEL(rtm_selfmod_start):
#endif /* CONFIG_LIBC_SUPPORTS_HARDWARE_RTM */

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
	.byte 0x48 /* movq $(-1), %rax */
	.byte 0xc7
	.byte 0xc0
.Lrtm_begin_maybe_syscall:
	.long 0xffffffff
	/* The following 2 bytes will get overwritten with `xbegin' if
	 * hardware   RTM   support   is   found   to   be  available. */
.Lrtm_begin_maybe_xbegin:
	.byte  0x90 /* nop */
	.byte  0xe9 /* jmp (with 32-bit operand) */
	.reloc ., R_X86_64_PC32, libc_rtm_begin_init - 4;
	.long  0;
	/* Hardware RTM entered. */
.Lrtm_begin_do_return:
	ret
#else /* CONFIG_LIBC_SUPPORTS_HARDWARE_RTM */
	movq   $(SYS_rtm_begin), %rax
	syscall
	ret
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
	.byte  0x48, 0xc7, 0xc0       /* movq $(SYS_rtm_abort), %rax */
	.long  (SYS_rtm_abort & 0xffffffff)
	syscall
	ret
	.cfi_endproc
END(libc_rtm_abort)
DEFINE_PUBLIC_ALIAS(rtm_abort, libc_rtm_abort)



/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
INTERN_FUNCTION(libc_rtm_test)
	.cfi_startproc
	.byte  0x48             /* movq $(SYS_rtm_test), %rax */
.Lrtm_test_redirection:
	.byte  0xc7, 0xc0       /* ... */
	.long  (SYS_rtm_test & 0xffffffff) /* ... */
	.byte  0x0f, 0x05       /* syscall */
	.byte  0xc3             /* ret */
	.cfi_endproc
END(libc_rtm_test)
DEFINE_PUBLIC_ALIAS(rtm_test, libc_rtm_test)


#ifdef CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
/* Check if a transaction is currently in progress
 * @return: ZF=1 : No RTM operation in progress
 * @return: ZF=0 : An RTM operation is currently in progress */
INTERN_FUNCTION(libc___x86_rtm_xtest)
	.cfi_startproc
	movq   $(SYS_rtm_test), %rax
	syscall
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
PRIVATE_LABEL(rtm_selfmod_end):
#endif /* CONFIG_LIBC_SUPPORTS_HARDWARE_RTM */




#ifdef CONFIG_LIBC_SUPPORTS_HARDWARE_RTM
.section .text.crt.system.rtm
PRIVATE_FUNCTION(libc_hw_rtm_abort)
	.cfi_startproc
	movzbq %dil, %rdi
	leaq   .Lxabort_base(%rip), %rax
	leaq   (%rax, %rdi, 4), %rax
	jmpq   *%rax
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


.section .bss.crt.system.rtm
/* RTM self-modifying code state:
 *   - 0: Uninitialized (rtm_begin() will do the self-modifications;
 *                       all other functions use system calls)
 *   - 1: In progress or complete (some thread is currently modifying code) */
PRIVATE_OBJECT(rtm_selfmod_state)
	.int 0
END(rtm_selfmod_state)

.section .text.crt.system.rtm
	.cfi_startproc
PRIVATE_FUNCTION(rtm_begin_emulated_after_mprotect_fail)
	movl   $(0), rtm_selfmod_state(%rip)
	movq   $(SYS_rtm_begin), %rax
	syscall
	ret
END(rtm_begin_emulated_after_mprotect_fail)

#ifdef __OPTIMIZE_SIZE__
#define rtm_begin_emulated_spin libc_rtm_begin
#else /* __OPTIMIZE_SIZE__ */
PRIVATE_FUNCTION(rtm_begin_emulated_spin)
	EXTERN(libc_sys_sched_yield)
	call   libc_sys_sched_yield
	jmp    libc_rtm_begin
END(rtm_begin_emulated_spin)
#endif /* !__OPTIMIZE_SIZE__ */

PRIVATE_FUNCTION(libc_rtm_begin_init)
	/* We get here in 2 situations:
	 *   - We're yet to check if hardware RTM is supported (likely)
	 *   - Hardware RTM was failed (%eax != _XBEGIN_STARTED) */
	cmpq   $(-1), %rax
	jne    .Lrtm_begin_do_return

	/* Acquire the RTM self-modifying code initialization lock. */
	movl   $(1), %eax
	lock   xchgl rtm_selfmod_state(%rip), %eax
	testl  %eax, %eax
	jnz    rtm_begin_emulated_spin /* Some other thread is already doing the init */

	/* Enable write-access */
	leaq   rtm_selfmod_start(%rip),                %rdi /* sys_mprotect:addr */
	movq   $(rtm_selfmod_end - rtm_selfmod_start), %rsi /* sys_mprotect:length */
	movq   $(PROT_READ | PROT_WRITE | PROT_EXEC),  %rdx /* sys_mprotect:prot */
	movq   $(SYS_mprotect), %rax
	syscall
	testq  %rax, %rax
	jnz    rtm_begin_emulated_after_mprotect_fail /* Fallback: Use RTM emulation (so the initial function state matches) */


	/* Check if hardware RTM is supported */
	pushq_cfi_r %rbx

	/* Check for the `ENVIRON_HW_RTM' variable */
#ifdef ENVIRON_HW_RTM
	.pushsection .rodata.crt.system.rtm
	PRIVATE_OBJECT(str_ENVIRON_HW_RTM)
		.asciz ENVIRON_HW_RTM
	END(str_ENVIRON_HW_RTM)
	.popsection
	leaq   str_ENVIRON_HW_RTM(%rip), %rdi
	EXTERN(libc_getenv)
	call   libc_getenv
	testq  %rax, %rax
	jz     1f
	cmpb   $(0), 0(%rax)
	jz     1f /* strlen(%rax) == 0 */
	cmpb   $(0), 1(%rax)
	jnz    1f /* strlen(%rax) != 1 */
	movb   0(%rax), %al
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

	/* Hardware RTM is supported! */

	/* Re-write helper function: `rtm_abort()' */
	leaq   (libc_hw_rtm_abort)(%rip), %rcx
	leaq   (libc_rtm_abort + 5)(%rip), %rax
	subq   %rax, %rcx
	shlq   $(8), %rcx
	movabs $(ENCODE_INT64(0xe9, /* jmp libc_hw_rtm_abort */          \
	                      0x00, /* ... */                            \
	                      0x00, /* ... */                            \
	                      0x00, /* ... */                            \
	                      0x00, /* ... */                            \
	                      INT64_BYTE(SYS_rtm_abort & 0xffffffff, 2), \
	                      INT64_BYTE(SYS_rtm_abort & 0xffffffff, 3), \
	                      0x0f  /* INSTR("syscall").bytes[0] */      \
	       )), %rdx
	orq    %rcx, %rdx /* Fill in the jump-offset to `libc_hw_rtm_abort' */
	/* Re-write the first 8 bytes of `rtm_abort()' to become `jmp libc_hw_rtm_abort' */
	movq   %rdx, -5(%rax)

	/* Re-write helper function: `__x86_rtm_xtest' to become `xtest; ret' */
	movl   $(ENCODE_INT32(0x0f, 0x01, 0xd6, /* xtest */ \
	                      0xc3              /* ret */   \
	       )), libc___x86_rtm_xtest(%rip)

	/* Re-write helper function: `rtm_test()'
	 *   0x48    movq $(SYS_rtm_test), %rax  -> .      xorq %rax, %rax
	 *   0xc7    ...                         -> 0x31   ...
	 *   0xc0    ...                         -> 0xc0   ...
	 *   ????    ...                         -> 0x0f   xtest
	 *   ????    ...                         -> 0x01   ...
	 *   ????    ...                         -> 0xd6   ...
	 *   ????    ...                         -> 0x0f   sete %al
	 *   0x0f    syscall                     -> 0x94   ...
	 *   0x05    ...                         -> 0xc0   ...
	 *   0xc3    ret
	 * This byte sequence has been painstaikingly engineered to only
	 * require 8 bytes of text to be modified, so-as to prevent  any
	 * problems  related with race conditions (meaning that updating
	 * code happens entirely atomic)
	 */
	movabs $(ENCODE_INT64(0x31, /* ... (xorq %rax, %rax) */ \
	                      0xc0, /* ... */                   \
	                      0x0f, /* xtest */                 \
	                      0x01, /* ... */                   \
	                      0xd6, /* ... */                   \
	                      0x0f, /* sete %al */              \
	                      0x94, /* ... */                   \
	                      0xc0  /* ... */                   \
	       )), %rax
	movq   %rax, .Lrtm_test_redirection(%rip)

	/* Re-write   the   first   2   bytes   at   `.Lrtm_begin_maybe_xbegin'
	 * with {0xc7, 0xf8} (which are the bytes corresponding to the `xbegin'
	 * instruction),  and in a second step, write  all zeroes to the next 4
	 * bytes in order to modify the failure-branch to point to `ret' above. */

	/* `movl $.Lrtm_begin_maybe_xbegin, %rax' */
	leaq   .Lrtm_begin_maybe_xbegin(%rip), %rax

	/* Write the `xbegin' instruction */
	movw   $(ENCODE_INT16(0xc7, 0xf8)), 0(%rax) /* Replace nop+jmp with `xbegin' */
	movl   $(0),                        2(%rax) /* Clear out the jump-offset operand */

	cpuid /* Serializing instruction is needed to flush the instruction cache. */
.Lpop_rbx_disable_writable_and_begin_rtm:
	/* Re-enable write-protect for the now-modified code. */

	leaq   rtm_selfmod_start(%rip),                %rdi /* sys_mprotect:addr */
	movq   $(rtm_selfmod_end - rtm_selfmod_start), %rsi /* sys_mprotect:length */
	movq   $(PROT_READ | PROT_EXEC),               %rdx /* sys_mprotect:prot */
	movq   $(SYS_mprotect), %rax
	syscall

	popq_cfi_r %rbx
	jmp    libc_rtm_begin

	.cfi_restore_state
.Lrtm_begin_modify_not_supported:
#if !(SYS_rtm_begin & __UINT64_C(0x8000000000000000))
#error "The sysno of `SYS_rtm_begin' must be negative!"
#endif /* !(SYS_rtm_begin & __UINT64_C(0x8000000000000000)) */
	/* Atomically write 8 bytes at `.Lrtm_begin_maybe_syscall':
	 * [0] = (SYS_rtm_begin & 0x000000ff)
	 * [1] = (SYS_rtm_begin & 0x0000ff00) >> 8
	 * [2] = (SYS_rtm_begin & 0x00ff0000) >> 16
	 * [3] = (SYS_rtm_begin & 0xff000000) >> 24
	 * [4] = 0x0f
	 * [5] = 0x05   // syscall
	 * [6] = 0xc3   // retq
	 * [7] = 0x90   // nop
	 *
	 * By  doing this, the  function `rtm_begin()' gets re-written
	 * such that it will invoke the system call used for emulation
	 * of RTM operations. */
	movabs $(ENCODE_INT64(/* [0] = */ (SYS_rtm_begin & 0x000000ff),       \
	                      /* [1] = */ (SYS_rtm_begin & 0x0000ff00) >> 8,  \
	                      /* [2] = */ (SYS_rtm_begin & 0x00ff0000) >> 16, \
	                      /* [3] = */ (SYS_rtm_begin & 0xff000000) >> 24, \
	                      /* [4] = */ 0x0f,                               \
	                      /* [5] = */ 0x05, /* syscall */                 \
	                      /* [6] = */ 0xc3, /* retq */                    \
	                      /* [7] = */ 0x90  /* nop */                     \
	       )), %rax
	movq   %rax, .Lrtm_begin_maybe_syscall(%rip)

	cpuid  /* Serializing instruction is needed to flush the instruction cache. */
	jmp    .Lpop_rbx_disable_writable_and_begin_rtm
	.cfi_endproc
END(libc_rtm_begin_init)
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




#endif /* GUARD_LIBC_LIBC_ARCH_I386_RTM64_S */
