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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_SYSCALL_BASE32_S
#define GUARD_LIBC_LIBC_ARCH_I386_SYSCALL_BASE32_S 1
#define __ASSEMBLER__ 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#include <hybrid/wordbits.h>

#include <cfi.h>
#include <asm/cpu-cpuid.h>
#include <asm/instr/ttest.h>
#include <sys/syscall.h>

#include <errno.h>

#include <libdebuginfo/dwarf.h>
#include <libunwind/cfi.h>
#include <libunwind/dwarf.h>


/* ========= __i386_syscall design =========
 *
 * Before sysenter compatibility check:
 *     >>     nop                          // 0x90
 *     >> __i386_syscall:
 *     >>     pushl  %ebp                  // 0x55
 *     >>     pushl  %edi                  // 0x57
 *     >>     call   libc_x86_syscall_init // 0xe8, ?, ?, ?, ?
 *     >>     popl   %edi
 *     >>     popl   %ebp
 *     >>     ret
 *     >> __i386_Xsyscall:
 *     >>     std                          // 0xfd
 *     >>     pushl  %ebp                  // 0x55
 *     >>     pushl  %edi                  // 0x57
 *     >>     call   libc_x86_syscall_init // 0xe8, ?, ?, ?, ?
 *     >>     popl   %edi
 *     >>     popl   %ebp
 *     >>     cld
 *     >>     ret
 *
 * With sysenter:
 *     >>     nop                          // 0x90
 *     >> __i386_syscall:
 *     >>     pushl  %ebp                  // 0x55
 *     >>     pushl  %edi                  // 0x57
 *     >>     call   libc_x86_sysenter_common
 *     >>     popl   %edi
 *     >>     popl   %ebp
 *     >>     ret
 *     >> __i386_Xsyscall:
 *     >>     std                          // 0xfd
 *     >>     pushl  %ebp                  // 0x55
 *     >>     pushl  %edi                  // 0x57
 *     >>     call   libc_x86_sysenter_common
 *     >>     popl   %edi
 *     >>     popl   %ebp
 *     >>     cld
 *     >>     ret
 *
 * Without sysenter:
 *     >>     nop                          // 0x90
 *     >> __i386_syscall:
 *     >>     int    $0x80                 // 0xcd, 0x80
 *     >>     ret                          // 0xc3
 *     >>     nop
 *     >>     FAULTY*
 *     >> __i386_Xsyscall:
 *     >>     std                          // 0xfd
 *     >>     int    $0x80                 // 0xcd, 0x80
 *     >>     cld                          // 0xfc
 *     >>     ret                          // 0xc3
 *     >>     FAULTY*
 *
 * As such, `libc_x86_syscall_init' can be implemented as:
 * >> return_pc = 0(%esp);
 * >> if (SYSENTER_AVAILABLE) {
 * >>     *(s32 *)(return_pc - 4) = libc_x86_sysenter_common - return_pc;
 * >> } else {
 * >>     if (*(u8 *)(return_pc - 8) == 0xfd) { // std
 * >>         *(u32 *)(return_pc - 7) = ENCODE_INT32(0xcd, 0x80, 0xfc, 0xc3); // int $0x80; cld; ret;
 * >>     } else {
 * >>         *(u32 *)(return_pc - 7) = ENCODE_INT32(0xcd, 0x80, 0xc3, 0x90); // int $0x80; ret; nop;
 * >>     }
 * >> }
 * >> RESTORE_REGISTERS(WITHOUT: EFLAGS_DF);
 * >> JUMP_TO(PC: return_pc - 7);
 *
 * How to encode CFI instrumentation?
 * The only real way I see is to use:
 * >> .cfi_escape DW_OP_GNU_encoded_addr, DW_EH_PE_funcrel | DW_EH_PE_uleb128, 0 // or 1
 * >> .cfi_escape DW_OP_deref_size, 1  // *(u8 *)__i386_syscall
 * >> .cfi_escape DW_OP_const1u, 0xcd  // *(u8 *)__i386_syscall, 0xcd
 * >> .cfi_escape DW_OP_eq             // *(u8 *)__i386_syscall == 0xcd ? 1 : 0
 * >> .cfi_escape DW_OP_bra, ?, ?      // JUMP_IF_INT80_MODE_ENABLED
 *
 * Then,  custom CFI expressions can be encoded to restore %esp, and
 * unwind %ebp and %edi  conditionally for those PC-locations  where
 * the INT80 and SYSENTER variants overlap, and don't share the same
 * register unwind / sp-offset behavior.
 */

.section .text.crt.syscalls.selector
INTERN_FUNCTION(libc_x86_syscall_init)
	.cfi_startproc
	/* Right now, our stack looks like this:
	 *    sp[...]      -- Unrelated / undefined
	 *    sp[0xc..0xf] -- Return address of `libc___i386_syscall' or `libc___i386_Xsyscall'
	 *    sp[0x8..0xb] -- Copy of `%ebp'
	 *    sp[0x4..0x7] -- Copy of `%edi'
	 *    sp[0x0..0x3] -- Either `libc___i386_syscall + 7' or `libc___i386_Xsyscall + 8'
	 *
	 * All other registers are already set-up for an int80-compatible system call.
	 *
	 * Because our caller eventually intends to perform a system call, we must also
	 * make sure to save _all_ registers (including %eflags) which we may otherwise
	 * clobber, so do this first! */
	pushfl_cfi_r
	pushl_cfi_r %eax
	pushl_cfi_r %ecx
	pushl_cfi_r %edx
	pushl_cfi_r %ebx

	/* Check if the CPU has support for `sysenter' */
	movl   $(1), %eax
	cpuid
	ttest  mask=CPUID_1D_SEP, loc=%edx
	jz     .Lenable_int80h                               /* if (!CPUID_1D_SEP) goto .Lenable_int80h; */

	/* Deal with the special case documented in the Intel manuals:
	 * >> if (Family == 6 && Model < 3 && Stepping < 3)
	 * >>     SYSENTER_ACTUALLY_NOT_SUPPORTED();
	 */
	movl   %eax, %ecx
	andl   $(CPUID_1A_FAMILY_M), %ecx
	cmpl   $(6 << CPUID_1A_FAMILY_S), %ecx
	jne    .Lenable_sysenter                             /* if (Family != 6) goto .Lenable_sysenter; */
	movl   %eax, %ecx
	andl   $(CPUID_1A_MODEL_M), %ecx
#if CPUID_1A_MODEL_S != 0
	shrl   $(CPUID_1A_MODEL_S), %ecx
#endif /* CPUID_1A_MODEL_S != 0 */
	cmpl   $(3), %ecx
	jae    .Lenable_sysenter                             /* if (Model >= 3) goto .Lenable_sysenter; */
	movl   %eax, %ecx
	andl   $(CPUID_1A_STEPPING_M), %ecx
#if CPUID_1A_STEPPING_S != 0
	shrl   $(CPUID_1A_STEPPING_S), %ecx
#endif /* CPUID_1A_STEPPING_S != 0 */
	cmpl   $(3), %ecx

	/* if (Stepping >= 3) goto .Lenable_sysenter; */
	/* if (Stepping < 3) goto .Lenable_int80h; */
	jb     .Lenable_int80h


	/* Enable support for `sysenter' */
	.cfi_remember_state
.Lenable_sysenter:
	call   1f
	.cfi_adjust_cfa_offset 4
1:	popl_cfi %ebx
	addl   $(_GLOBAL_OFFSET_TABLE_ + (. - 1b)), %ebx     /* %ebx = &_GLOBAL_OFFSET_TABLE_; */
	leal   libc_x86_sysenter_common@GOTOFF(%ebx), %eax   /* %eax = &libc_x86_sysenter_common; */
	movl   20(%esp), %edx                                /* %edx = return_pc; */
	subl   %edx, %eax                                    /* %eax = &libc_x86_sysenter_common - return_pc; */
	/* Re-write the target of the `call' instruction that got us
	 * here  to instead link up with `libc_x86_sysenter_common',
	 * thus causing all future calls to bypass our function, and
	 * immediately invoke `sysenter' */
	movl   %eax, -4(%edx)                                /* *(s32 *)(return_pc - 4) = (&libc_x86_sysenter_common - return_pc); */
	cpuid                                                /* __flush_instruction_cache(); */
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi_r %eax
	popfl_cfi_r
	jmp    libc_x86_sysenter_common

	/* Use int80h to implement syscall support. */
	.cfi_restore_state
.Lenable_int80h:
	movl   20(%esp), %edx                                /* %edx = return_pc; */
	movl   $(ENCODE_INT32(0xcd, 0x80, 0xc3, 0x90)), %eax /* %eax = { int $0x80; ret; nop; }; */
	movl   $(ENCODE_INT32(0xcd, 0x80, 0xfc, 0xc3)), %ecx /* %ecx = { int $0x80; cld; ret; }; */
	cmpb   $(0xfd), -8(%edx)                             /* return_pc[-8] == 0xfd; // NOTE: 0xfd == `std' (set EFLAGS.DF=1) */
	cmove  %ecx, %eax                                    /* if (return_pc[-8] == 0xfd) %eax = { int $0x80; cld; ret; }; */
	/* Rewrite the `pushl %ebp'  and `pushl %edi',  as well as  the first  2
	 * bytes of the `call' instruction of `libc_x86_syscall_init()' with the
	 * instruction sequence  `int $0x80; ret; nop' or  `int $0x80; cld; ret' */
	movl   %eax, -7(%edx)                                /* return_pc[-7...-4] = %eax; */
	cpuid                                                /* __flush_instruction_cache(); */
	popl_cfi_r %ebx
	popl_cfi_r %edx
	popl_cfi_r %ecx
	popl_cfi_r %eax
	popfl_cfi_r
	popl_cfi %ebp         /* %ebp = return_pc */
	/* Adjust this function's return_pc to point at the `int $0x80' instruction that we just wrote! */
	leal   -7(%ebp), %ebp /* %ebp = return_pc-7 */
	popl_cfi %edi         /* %edi = CALLER_SAVED_EDI */
	xchgl  %ebp, 0(%esp)  /* %ebp = CALLER_SAVED_EBP */
	ret                   /* Return to `return_pc-7' */
	.cfi_endproc
END(libc_x86_syscall_init)


.section .text.crt.syscalls.x86_sysenter_common
INTERN_FUNCTION(libc_x86_sysenter_common)
	.cfi_startproc
	popl_cfi %edi     /* EDI = RETURN_PC */
	.cfi_register %eip, %edi
	movl   %esp, %ebp /* EBP = RETURN_SP */
	sysenter
	.cfi_endproc
END(libc_x86_sysenter_common)

/* Restore: `%esp = INT80_ENABLED ? (%esp + int80_sp_offset) : (%esp + sysenter_sp_offset)' */
#define CFI_RESTORE_ESP(int80_sp_offset, sysenter_sp_offset)                                                   \
	.cfi_escape DW_CFA_val_expression, CFI_386_UNWIND_REGISTER_ESP, 15;                                        \
	.cfi_escape DW_OP_breg0 + CFI_386_UNWIND_REGISTER_ESP, int80_sp_offset; /* CFI: [%esp+*] */                \
	.cfi_escape DW_OP_GNU_encoded_addr, DW_EH_PE_funcrel | DW_EH_PE_uleb128, _CFI_FUNBASE_OFFSET;              \
	                                                      /* CFI: [%esp+*, libc___i386_Xsyscall + 1] */        \
	.cfi_escape DW_OP_deref_size, 1;                      /* CFI: [%esp+*, libc___i386_Xsyscall[1]] */         \
	.cfi_escape DW_OP_const1u, 0xcd;                      /* CFI: [%esp+*, libc___i386_Xsyscall[1], 0xcd] */   \
	.cfi_escape DW_OP_eq;                                 /* CFI: [%esp+*, libc___i386_Xsyscall[1] == 0xcd] */ \
	.cfi_escape DW_OP_bra, 0x02, 0x00;                    /* if (INT80_ENABLED) goto 1f; */                    \
	.cfi_escape DW_OP_plus_uconst, (sysenter_sp_offset - int80_sp_offset) /* CFI: [%esp+*] */

/* Restore: `%regno = INT80_ENABLED ? *(u32 *)(%esp + sysenter_sp_offset) : *(u32 *)(%esp + sp_offset)' */
#define CFI_RESTORE_FROM_ESP(regno, int80_sp_offset, sysenter_sp_offset)                                     \
	.cfi_escape DW_CFA_expression, regno, 15;                                                                \
	.cfi_escape DW_OP_breg0 + CFI_386_UNWIND_REGISTER_ESP, int80_sp_offset; /* CFI: [%esp] */                \
	.cfi_escape DW_OP_GNU_encoded_addr, DW_EH_PE_funcrel | DW_EH_PE_uleb128, _CFI_FUNBASE_OFFSET;            \
	                                                      /* CFI: [%esp, libc___i386_Xsyscall + 1] */        \
	.cfi_escape DW_OP_deref_size, 1;                      /* CFI: [%esp, libc___i386_Xsyscall[1]] */         \
	.cfi_escape DW_OP_const1u, 0xcd;                      /* CFI: [%esp, libc___i386_Xsyscall[1], 0xcd] */   \
	.cfi_escape DW_OP_eq;                                 /* CFI: [%esp, libc___i386_Xsyscall[1] == 0xcd] */ \
	.cfi_escape DW_OP_bra, 0x02, 0x00;                    /* if (INT80_ENABLED) goto 1f; */                  \
	.cfi_escape DW_OP_plus_uconst, (sysenter_sp_offset - int80_sp_offset) /* CFI: [%esp + *] */

/* Restore: `%regno = INT80_ENABLED ? %regno : *(u32 *)(%esp + sp_offset)' */
#define CFI_SYSENTER_RESTORE_FROM_ESP(regno, sp_offset)                                                        \
	.cfi_escape DW_CFA_val_expression, regno, 17;                                                              \
	.cfi_escape DW_OP_breg0 + regno, 0;                   /* CFI: [%regno] */                                  \
	.cfi_escape DW_OP_GNU_encoded_addr, DW_EH_PE_funcrel | DW_EH_PE_uleb128, _CFI_FUNBASE_OFFSET;              \
	                                                      /* CFI: [%regno, libc___i386_Xsyscall + 1] */        \
	.cfi_escape DW_OP_deref_size, 1;                      /* CFI: [%regno, libc___i386_Xsyscall[1]] */         \
	.cfi_escape DW_OP_const1u, 0xcd;                      /* CFI: [%regno, libc___i386_Xsyscall[1], 0xcd] */   \
	.cfi_escape DW_OP_eq;                                 /* CFI: [%regno, libc___i386_Xsyscall[1] == 0xcd] */ \
	.cfi_escape DW_OP_bra, 0x04, 0x00;                    /* if (INT80_ENABLED) goto 1f; */                    \
	.cfi_escape DW_OP_drop;                               /* CFI: [] */                                        \
	.cfi_escape DW_OP_breg0 + CFI_386_UNWIND_REGISTER_ESP, sp_offset;                                          \
	                                                      /* CFI: [%esp + sp_offset] */                        \
	.cfi_escape DW_OP_deref                               /* CFI: [*(u32 *)%esp] */


.section .xdata, "awx"
	.align 16                /* Align by a whole cacheline */
	/* NOTE: Technically, this `0x90' only has to be something that isn't `0xfd'! */
	.byte  0x90              /* nop                             nop           */
INTERN_FUNCTION(libc___i386_syscall)
#define _CFI_FUNBASE_OFFSET 0 /* Offset from `.cfi_startproc' to 0x55 (`pushl %ebp') or 0xcd (`int $0x80') */
	.cfi_startproc

	.byte  0x55              /* pushl  %ebp                     int $0x80     */
	CFI_SYSENTER_RESTORE_FROM_ESP(CFI_386_UNWIND_REGISTER_EBP, 0)  /* CFI: %ebp = INT80_ENABLED ? %ebp : *(u32 *)(%esp + 0) */
	CFI_RESTORE_FROM_ESP(CFI_386_UNWIND_REGISTER_EIP, 0, 4)        /* CFI: %eip = INT80_ENABLED ? *(u32 *)(%esp + 0) : *(u32 *)(%esp + 4) */
	CFI_RESTORE_ESP(4, 8)                                          /* CFI: %esp = INT80_ENABLED ? %esp+4 : %esp+8 */

	.byte  0x57              /* pushl  %edi                     ...           */
	CFI_SYSENTER_RESTORE_FROM_ESP(CFI_386_UNWIND_REGISTER_EDI, 0)  /* CFI: %edi = INT80_ENABLED ? %edi : *(u32 *)(%esp + 0) */
	CFI_SYSENTER_RESTORE_FROM_ESP(CFI_386_UNWIND_REGISTER_EBP, 4)  /* CFI: %ebp = INT80_ENABLED ? %ebp : *(u32 *)(%esp + 4) */
	CFI_RESTORE_FROM_ESP(CFI_386_UNWIND_REGISTER_EIP, 0, 8)        /* CFI: %eip = INT80_ENABLED ? *(u32 *)(%esp + 0) : *(u32 *)(%esp + 8) */
	CFI_RESTORE_ESP(4, 12)                                         /* CFI: %esp = INT80_ENABLED ? %esp+4 : %esp+12 */

	.byte  0xe8              /* call libc_x86_syscall_init      ret           */
	.reloc ., R_386_PC32, libc_x86_syscall_init
	.byte  -4                /* ...                             nop           */
#ifndef __OPTIMIZE_SIZE__
	/* From this point forth, the remainder of the function is SYSENTER-only!
	 * And because we haven't reached  the "normal" return address used  when
	 * unwinding system calls that  throw exceptions, assign CFI  expressions
	 * to unwind registers that can be executed faster than the above! */
	.cfi_reg_offset %edi, 0, %esp  /* %edi = [%esp + 0] */
	.cfi_reg_offset %ebp, 4, %esp  /* %ebp = [%esp + 4] */
	.cfi_reg_offset %eip, 8, %esp  /* %eip = [%esp + 8] */
	.cfi_reg_value  %esp, 12, %esp /* %esp = %esp + 12 */
#endif /* __OPTIMIZE_SIZE__ */
	.byte  0xff              /* ...                                           */
	.byte  0xff              /* ...                                           */
	.byte  0xff              /* ...                                           */

	popl   %edi
	.cfi_same_value %edi
	.cfi_reg_offset %ebp, 0, %esp  /* %ebp = [%esp + 0] */
	.cfi_reg_offset %eip, 4, %esp  /* %eip = [%esp + 4] */
	.cfi_reg_value  %esp, 8, %esp  /* %esp = %esp + 8 */
	popl   %ebp
	.cfi_same_value %edi
	.cfi_reg_offset %eip, 0, %esp  /* %eip = [%esp + 0] */
	.cfi_reg_value  %esp, 4, %esp  /* %esp = %esp + 4 */
	ret
	.cfi_endproc
#undef _CFI_FUNBASE_OFFSET
END(libc___i386_syscall)

.section .xdata, "awx"
	.align 16                /* Align by a whole cacheline */
INTERN_FUNCTION(libc___i386_Xsyscall)
#define _CFI_FUNBASE_OFFSET 1 /* Offset from `.cfi_startproc' to 0x55 (`pushl %ebp') or 0xcd (`int $0x80') */
	.cfi_startproc
/*[[[cfi{register='%eflags'} push %eflags; and ~$EFLAGS_DF]]]*/
	.cfi_escape 22,9,6,121,0,11,255,251,26
/*[[[end]]]*/
	.byte  0xfd              /* std                             std           */

	.byte  0x55              /* pushl  %ebp                     int $0x80     */
	CFI_SYSENTER_RESTORE_FROM_ESP(CFI_386_UNWIND_REGISTER_EBP, 0)  /* CFI: %ebp = INT80_ENABLED ? %ebp : *(u32 *)(%esp + 0) */
	CFI_RESTORE_FROM_ESP(CFI_386_UNWIND_REGISTER_EIP, 0, 4)        /* CFI: %eip = INT80_ENABLED ? *(u32 *)(%esp + 0) : *(u32 *)(%esp + 4) */
	CFI_RESTORE_ESP(4, 8)                                          /* CFI: %esp = INT80_ENABLED ? %esp+4 : %esp+8 */

	.byte  0x57              /* pushl  %edi                     ...           */
	CFI_SYSENTER_RESTORE_FROM_ESP(CFI_386_UNWIND_REGISTER_EDI, 0)  /* CFI: %edi = INT80_ENABLED ? %edi : *(u32 *)(%esp + 0) */
	CFI_SYSENTER_RESTORE_FROM_ESP(CFI_386_UNWIND_REGISTER_EBP, 4)  /* CFI: %ebp = INT80_ENABLED ? %ebp : *(u32 *)(%esp + 4) */
	CFI_RESTORE_FROM_ESP(CFI_386_UNWIND_REGISTER_EIP, 0, 8)        /* CFI: %eip = INT80_ENABLED ? *(u32 *)(%esp + 0) : *(u32 *)(%esp + 8) */
	CFI_RESTORE_ESP(4, 12)                                         /* CFI: %esp = INT80_ENABLED ? %esp+4 : %esp+12 */

	.byte  0xe8              /* call libc_x86_syscall_init      cld           */
	.reloc ., R_386_PC32, libc_x86_syscall_init
	.byte  -4                /* ...                             ret           */
#ifndef __OPTIMIZE_SIZE__
	/* From this point forth, the remainder of the function is SYSENTER-only!
	 * And because we haven't reached  the "normal" return address used  when
	 * unwinding system calls that  throw exceptions, assign CFI  expressions
	 * to unwind registers that can be executed faster than the above! */
	.cfi_reg_offset %edi, 0, %esp  /* %edi = [%esp + 0] */
	.cfi_reg_offset %ebp, 4, %esp  /* %ebp = [%esp + 4] */
	.cfi_reg_offset %eip, 8, %esp  /* %eip = [%esp + 8] */
	.cfi_reg_value  %esp, 12, %esp /* %esp = %esp + 12 */
#endif /* __OPTIMIZE_SIZE__ */
	.byte  0xff              /* ...                                           */
	.byte  0xff              /* ...                                           */
	.byte  0xff              /* ...                                           */

	popl   %edi
	.cfi_same_value %edi
	.cfi_reg_offset %ebp, 0, %esp  /* %ebp = [%esp + 0] */
	.cfi_reg_offset %eip, 4, %esp  /* %eip = [%esp + 4] */
	.cfi_reg_value  %esp, 8, %esp  /* %esp = %esp + 8 */
	popl   %ebp
	.cfi_same_value %edi
	.cfi_reg_offset %eip, 0, %esp  /* %eip = [%esp + 0] */
	.cfi_reg_value  %esp, 4, %esp  /* %esp = %esp + 4 */
	cld
	ret
	.cfi_endproc
#undef _CFI_FUNBASE_OFFSET
END(libc___i386_Xsyscall)

#undef CFI_SYSENTER_RESTORE_FROM_ESP
#undef CFI_RESTORE_FROM_ESP
#undef CFI_RESTORE_ESP






.section .text.crt.system.utility
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
	call   libc___i386_syscall
	cmpl   $(-ELIMIT), %eax /* Check for error. */
	ja     1f
	.cfi_remember_state
	popl_cfi_r %ebp
	popl_cfi_r %edi
	popl_cfi_r %esi
	popl_cfi_r %ebx
	ret
	.cfi_restore_state
1:	movl   %eax, %ecx
	INTERN(libc_seterrno_neg)
	call   libc_seterrno_neg /* errno = -return */
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
DEFINE_PUBLIC_ALIAS(syscall64, libc_syscall64)
DEFINE_PUBLIC_ALIAS(__syscall, libc_syscall64)


.section .text.crt.except.system.utility
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
	call   libc___i386_Xsyscall
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
