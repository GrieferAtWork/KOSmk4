/* HASH CRC-32:0x94d9e8a0 */
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
#ifndef _I386_KOS_KOS_ASM_EXCEPT_H
#define _I386_KOS_KOS_ASM_EXCEPT_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <features.h>
#ifdef __USE_KOS_KERNEL
#include <kos/kernel/cpu-state.h>
#endif /* __USE_KOS_KERNEL */

#undef __ERROR_REGISTER_STATE_TYPE
#define __ERROR_REGISTER_STATE_TYPE    struct kcpustate
#ifdef __USE_KOS_KERNEL
#define __SIZEOF_ERROR_REGISTER_STATE  SIZEOF_KCPUSTATE
#endif /* __USE_KOS_KERNEL */
#ifdef __x86_64__
#define __ERROR_REGISTER_STATE_TYPE_RDPC(x)                       ((x).kcs_rip)
#define __ERROR_REGISTER_STATE_TYPE_WRPC(x, value)                ((x).kcs_rip=(value))
#define __ERROR_REGISTER_STATE_TYPE_RDSP(x)                       ((x).kcs_gpregs.gp_rsp)
#define __ERROR_REGISTER_STATE_TYPE_WRSP(x, value)                ((x).kcs_gpregs.gp_rsp=(value))
#define __ERROR_REGISTER_STATE_TYPE_RD_UNWIND_EXCEPTION(x)        ((x).kcs_gpregs.gp_rax)
#define __ERROR_REGISTER_STATE_TYPE_WR_UNWIND_EXCEPTION(x, value) ((x).kcs_gpregs.gp_rax=(value))
#else /* __x86_64__ */
#define __ERROR_REGISTER_STATE_TYPE_RDPC(x)                       ((x).kcs_eip)
#define __ERROR_REGISTER_STATE_TYPE_WRPC(x, value)                ((x).kcs_eip=(value))
#define __ERROR_REGISTER_STATE_TYPE_RDSP(x)                       ((x).kcs_gpregs.gp_esp)
#define __ERROR_REGISTER_STATE_TYPE_WRSP(x, value)                ((x).kcs_gpregs.gp_esp=(value))
#define __ERROR_REGISTER_STATE_TYPE_RD_UNWIND_EXCEPTION(x)        ((x).kcs_gpregs.gp_eax)
#define __ERROR_REGISTER_STATE_TYPE_WR_UNWIND_EXCEPTION(x, value) ((x).kcs_gpregs.gp_eax=(value))
#endif /* !__x86_64__ */


/* System exception classes.
 * NOTE: Many of these are never actually thrown, and those that are also
 *       exist as `E_*' classes below. Also note that some exceptions may
 *       be merged with others, while allowing for differentiation using
 *      `error_info()'. */
#define X86_E_SYSTEM_DE   (0xff00) /* Divide-by-zero. */
#define X86_E_SYSTEM_DB   (0xff01) /* Debug. */
#define X86_E_SYSTEM_NMI  (0xff02) /* Non-maskable Interrupt. */
#define X86_E_SYSTEM_BP   (0xff03) /* Breakpoint. */
#define X86_E_SYSTEM_OF   (0xff04) /* Overflow. */
#define X86_E_SYSTEM_BR   (0xff05) /* Bound Range Exceeded. */
#define X86_E_SYSTEM_UD   (0xff06) /* Invalid Opcode. */
#define X86_E_SYSTEM_NM   (0xff07) /* Device Not Available. */
#define X86_E_SYSTEM_DF   (0xff08) /* Double Fault. */
/*      X86_E_SYSTEM_     (0xff09)  */
#define X86_E_SYSTEM_TS   (0xff0a) /* Invalid TSS. */
#define X86_E_SYSTEM_NP   (0xff0b) /* Segment Not Present. */
#define X86_E_SYSTEM_SS   (0xff0c) /* Stack-Segment Fault. */
#define X86_E_SYSTEM_GP   (0xff0d) /* General Protection Fault. */
#define X86_E_SYSTEM_PF   (0xff0e) /* Page Fault. */
/*      X86_E_SYSTEM_     (0xff0f)  */
#define X86_E_SYSTEM_MF   (0xff10) /* x87 Floating-Point Exception. */
#define X86_E_SYSTEM_AC   (0xff11) /* Alignment Check. */
#define X86_E_SYSTEM_MC   (0xff12) /* Machine Check. */
#define X86_E_SYSTEM_XM   (0xff13) /* SIMD Floating-Point Exception. */
#define X86_E_SYSTEM_VE   (0xff14) /* Virtualization Exception. */
/*      X86_E_SYSTEM_     (0xff15)  */
/*                         ....     */
/*      X86_E_SYSTEM_     (0xff1d)  */
#define X86_E_SYSTEM_SX   (0xff1e) /* Security Exception. */
/*      X86_E_SYSTEM_     (0xff1f)  */
#define X86_E_SYSTEM_XF   X86_E_SYSTEM_XM /* Alias */


/* System (Hardware-generated) exception classes. */
/* Segmentation fault (invalid memory access) */
#define E_SEGFAULT (X86_E_SYSTEM_PF)
/* Attempted to access a faulty memory location
 * 	@@The virtual memory address where the fault happened
 * 	member addr: void *;
 * 	@@Fault context (Set of `E_SEGFAULT_CONTEXT_*')
 * 	member context: uintptr_t; */
#define E_SEGFAULT_UNMAPPED (E_SEGFAULT,0x0001)
/* Attempted to write to a read-only memory location
 * 	@@The virtual memory address where the fault happened
 * 	member addr: void *;
 * 	@@Fault context (Set of `E_SEGFAULT_CONTEXT_*')
 * 	member context: uintptr_t; */
#define E_SEGFAULT_READONLY (E_SEGFAULT,0x0002)
/* Attempted to read from a memory location that is not readable
 * 	@@The virtual memory address where the fault happened
 * 	member addr: void *;
 * 	@@Fault context (Set of `E_SEGFAULT_CONTEXT_*')
 * 	member context: uintptr_t; */
#define E_SEGFAULT_NOTREADABLE (E_SEGFAULT,0x0003)
/* Attempted to execute a non-executable memory location
 * 	@@The virtual memory address where the fault happened
 * 	member addr: void *;
 * 	@@Fault context (Set of `E_SEGFAULT_CONTEXT_*')
 * 	member context: uintptr_t; */
#define E_SEGFAULT_NOTEXECUTABLE (E_SEGFAULT,0x0004)
/* Attempted to perform an impossible atomic operation
 * 	@@The virtual memory address where the access was attempted
 * 	member addr: void *;
 * 	@@Fault context (Set of `E_SEGFAULT_CONTEXT_*')
 * 	member context: uintptr_t;
 * 	@@The number of consecutive bytes accessed
 * 	member size: size_t;
 * 	@@Low data word of the expected old value
 * 	member oldval_lo: uintptr_t;
 * 	@@High data word of the expected old value
 * 	member oldval_hi: uintptr_t;
 * 	@@Low data word of the intended new value
 * 	member newval_lo: uintptr_t;
 * 	@@High data word of the intended new value
 * 	member newval_hi: uintptr_t;
 */
#define E_SEGFAULT_NOTATOMIC (E_SEGFAULT,0x0005)
/* Attempted to access an unaligned pointer
 * 	@@The (unaligned) virtual memory address accessed
 * 	member addr: void *;
 * 	@@Fault context (Set of `E_SEGFAULT_CONTEXT_*')
 * 	member context: uintptr_t;
 * 	@@The required alignment of `addr' (power-of-2)
 * 	member required_alignemnt: size_t; */
#define E_SEGFAULT_UNALIGNED (E_SEGFAULT,0x0006)

/* Faulty address */
#define E_SEGFAULT_CONTEXT_FAULT 0x0001
/* FLAG: The fault happened during a write operation */
#define E_SEGFAULT_CONTEXT_WRITING 0x0002
/* FLAG: The access was performed for user-space */
#define E_SEGFAULT_CONTEXT_USERCODE 0x0004
/* Non-canonical address */
#define E_SEGFAULT_CONTEXT_NONCANON 0x0008
/* The instruction pointer's location caused the fault */
#define E_SEGFAULT_CONTEXT_EXEC 0x0010
/* Attempted to unmap an undefined memory address */
#define E_SEGFAULT_CONTEXT_UNMAP 0x4000
/* FLAG: The access was perform by VIO */
#define E_SEGFAULT_CONTEXT_VIO 0x8000




/* Breakpoint */
#define E_BREAKPOINT (X86_E_SYSTEM_BP)




/* Divide by zero */
#define E_DIVIDE_BY_ZERO (X86_E_SYSTEM_DE)




/* Overflow */
#define E_OVERFLOW (X86_E_SYSTEM_OF)




/* Illegal/privileged/restricted instruction/register/operand/addressing mode or trap encountered */
#define E_ILLEGAL_INSTRUCTION (X86_E_SYSTEM_UD)
/* The instruction opcode was not recognized
 * 	@@The opcode that caused the exception
 * 	@@NOTE: This field should be decoded using `E_ILLEGAL_INSTRUCTION_X86_OPCODE_*'
 * 	member opcode: uintptr_t;
 * 	@@Opcode flags (set of `EMU86_F_*')
 * 	member op_flags: uintptr_t; */
#define E_ILLEGAL_INSTRUCTION_BAD_OPCODE (E_ILLEGAL_INSTRUCTION,0x0001)
/* An unsupported prefix byte was encountered
 * 	@@The opcode that caused the exception
 * 	@@NOTE: This field should be decoded using `E_ILLEGAL_INSTRUCTION_X86_OPCODE_*'
 * 	member opcode: uintptr_t;
 * 	@@Opcode flags (set of `EMU86_F_*')
 * 	member op_flags: uintptr_t; */
#define E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX (E_ILLEGAL_INSTRUCTION,0x0002)
/* The instruction's opcode is not supported by the host (not thrown if the instruction was emulated)
 * 	@@The opcode that caused the exception
 * 	@@NOTE: This field should be decoded using `E_ILLEGAL_INSTRUCTION_X86_OPCODE_*'
 * 	member opcode: uintptr_t;
 * 	@@Opcode flags (set of `EMU86_F_*')
 * 	member op_flags: uintptr_t; */
#define E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE (E_ILLEGAL_INSTRUCTION,0x0003)
/* Including all prefixes, the instruction is too long
 * 	@@The opcode that caused the exception
 * 	@@NOTE: This field should be decoded using `E_ILLEGAL_INSTRUCTION_X86_OPCODE_*'
 * 	member opcode: uintptr_t;
 * 	@@Opcode flags (set of `EMU86_F_*')
 * 	member op_flags: uintptr_t; */
#define E_ILLEGAL_INSTRUCTION_X86_TOO_LONG (E_ILLEGAL_INSTRUCTION,0x0004)
/* The calling code does not have the necessary privilege to invoke the instruction `opcode'
 * 	@@The opcode that caused the exception
 * 	@@NOTE: This field should be decoded using `E_ILLEGAL_INSTRUCTION_X86_OPCODE_*'
 * 	member opcode: uintptr_t;
 * 	@@Opcode flags (set of `EMU86_F_*')
 * 	member op_flags: uintptr_t; */
#define E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE (E_ILLEGAL_INSTRUCTION,0x0005)
/* A kernel-space instruction has caused an unhandled #GP or #SS
 * 	@@The opcode that caused the exception
 * 	@@NOTE: This field should be decoded using `E_ILLEGAL_INSTRUCTION_X86_OPCODE_*'
 * 	member opcode: uintptr_t;
 * 	@@Opcode flags (set of `EMU86_F_*')
 * 	member op_flags: uintptr_t;
 * 	@@The system interrupt that occurred
 * 	member intno: uintptr_t;
 * 	@@The error code associated with that interrupt
 * 	member ecode: uintptr_t;
 * 	@@The segment value of the segment in question
 * 	member segval: uintptr_t; */
#define E_ILLEGAL_INSTRUCTION_X86_INTERRUPT (E_ILLEGAL_INSTRUCTION,0x000f)
/* An operand of the instruction is invalid
 * 	@@The opcode that caused the exception
 * 	@@NOTE: This field should be decoded using `E_ILLEGAL_INSTRUCTION_X86_OPCODE_*'
 * 	member opcode: uintptr_t;
 * 	@@Opcode flags (set of `EMU86_F_*')
 * 	member op_flags: uintptr_t;
 * 	@@For what reason was the operand invalid (One of `E_ILLEGAL_INSTRUCTION_BAD_OPERAND_*')
 * 	member what: uintptr_t;
 * 	@@The accessed register index
 * 	@@NOTE: When set to `X86_REGISTER_MSR', then the next 3
 * 	@@      pointers are index(%ecx), loval(%eax), hival(%edx)
 * 	member regno: uintptr_t;
 * 	@@An offset applied to the register (set in case of an illegal lcall/ljmp; 0 otherwise)
 * 	@@In case an MSR register was accessed, this is the MSR index
 * 	member offset: uintptr_t;
 * 	@@The associated register value
 * 	member regval: uintptr_t;
 * 	@@The associated register value (high 32 bits in case of an MSR write)
 * 	member regval2: uintptr_t;
 */
#define E_ILLEGAL_INSTRUCTION_BAD_OPERAND (E_ILLEGAL_INSTRUCTION,0x0010)
/* Unexpectedly, the instruction has a memory operand (the memory operand's address is stored in `offset') */
#define E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY 0x0001
/* Unexpectedly, the instruction has a register operand (register and its value is stored in `regno' and `regval') */
#define E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER 0x0002
/* A register operand has a bad value */
#define E_ILLEGAL_INSTRUCTION_BAD_OPERAND_VALUE 0x0003
/* Attempted to access an invalid register `regno' (one of `<ARCH>_REGISTER_*')
 * 	@@The opcode that caused the exception
 * 	@@NOTE: This field should be decoded using `E_ILLEGAL_INSTRUCTION_X86_OPCODE_*'
 * 	member opcode: uintptr_t;
 * 	@@Opcode flags (set of `EMU86_F_*')
 * 	member op_flags: uintptr_t;
 * 	@@How was the register accessed (One of `E_ILLEGAL_INSTRUCTION_REGISTER_*')
 * 	member how: uintptr_t;
 * 	@@The accessed register index
 * 	@@NOTE: When set to `X86_REGISTER_MSR', then the next 3
 * 	@@      pointers are index(%ecx), loval(%eax), hival(%edx)
 * 	member regno: uintptr_t;
 * 	@@An offset applied to the register (set in case of an illegal lcall/ljmp; 0 otherwise)
 * 	@@In case an MSR register was accessed, this is the MSR index
 * 	member offset: uintptr_t;
 * 	@@The associated register value (or 0 for read operations)
 * 	member regval: uintptr_t;
 * 	@@The associated register value (or 0 for read operations) (high 32 bits in case of an MSR write)
 * 	member regval2: uintptr_t;
 */
#define E_ILLEGAL_INSTRUCTION_REGISTER (E_ILLEGAL_INSTRUCTION,0x0011)
/* Read from invalid register */
#define E_ILLEGAL_INSTRUCTION_REGISTER_RDINV 0x0001
/* Read from privileged register */
#define E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV 0x0002
/* Write to invalid register */
#define E_ILLEGAL_INSTRUCTION_REGISTER_WRINV 0x0011
/* Write to privileged register */
#define E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV 0x0012
/* Bad value written to register */
#define E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD 0x0013
/* Attempted to assign a non-present segment */
#define E_ILLEGAL_INSTRUCTION_REGISTER_WRNPSEG 0x0014

/* Helper macros to encode/decode the `opcode' field of `E_ILLEGAL_INSTRUCTION'
 * NOTE: If the instruction doesn't depend on `modrm_reg', set it directly. */
#ifdef __x86_64__
#define E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, modrm_reg) ((__UINT64_TYPE__)(opcode) | (__UINT64_TYPE__)(modrm_reg) << 60 | __UINT64_C(0x0800000000000000))
#define E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETOPC(v)          ((__UINT64_TYPE__)(v) & __UINT64_C(0x07ffffffffffffff))
#define E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETREG(v)          ((__UINT8_TYPE__)((__UINT64_TYPE__)(v) >> 60))
#define E_ILLEGAL_INSTRUCTION_X86_OPCODE_HASREG(v)          ((__UINT64_TYPE__)(v) & __UINT64_C(0x0800000000000000))
#else /* __x86_64__ */
#define E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, modrm_reg) ((__UINT32_TYPE__)(opcode) | (__UINT32_TYPE__)(modrm_reg) << 29 | __UINT32_C(0x10000000))
#define E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETOPC(v)          ((__UINT32_TYPE__)(v) & __UINT32_C(0x0fffffff))
#define E_ILLEGAL_INSTRUCTION_X86_OPCODE_GETREG(v)          ((__UINT8_TYPE__)((__UINT32_TYPE__)(v) >> 29))
#define E_ILLEGAL_INSTRUCTION_X86_OPCODE_HASREG(v)          ((__UINT32_TYPE__)(v) & __UINT32_C(0x10000000))
#endif /* !__x86_64__ */





/* Thrown in kernel space when: #PF->#DF with ESP/RSP below stack_base
 * Thrown in user space when:   #PF ontop of a guard page with no remaining funds */
#define E_STACK_OVERFLOW (X86_E_SYSTEM_DF)




/* The BOUND instruction was executed with an out-of-bounds index */
#define E_INDEX_ERROR (X86_E_SYSTEM_BR)
/* An index was outside of the min/max bounds
 * 	@@The addressed index
 * 	member index: intptr_t;
 * 	@@The low bound of valid indices
 * 	member min: intptr_t;
 * 	@@The high bound of valid indices
 * 	member max: intptr_t; */
#define E_INDEX_ERROR_OUT_OF_BOUNDS (E_INDEX_ERROR,0x0001)





#endif /* !_I386_KOS_KOS_ASM_EXCEPT_H */
