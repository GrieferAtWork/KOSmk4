/* HASH CRC-32:0x274eb69 */
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
#ifndef _KOS_ASM_EXCEPT_H
#define _KOS_ASM_EXCEPT_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

/* System (Hardware-generated) exception classes. */
/* Segmentation fault (invalid memory access) */
#define E_SEGFAULT (0xff00)
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
/* Faulty address */
#define E_SEGFAULT_CONTEXT_FAULT 0x0001
/* FLAG: The fault happened during a write operation */
#define E_SEGFAULT_CONTEXT_WRITING 0x0002
/* FLAG: The access was performed for user-space */
#define E_SEGFAULT_CONTEXT_USERCODE 0x0004
/* Non-canonical address */
#define E_SEGFAULT_CONTEXT_NONCANON 0x0008
/* Attempted to unmap an undefined memory address */
#define E_SEGFAULT_CONTEXT_UNMAP 0x0010




/* Breakpoint */
#define E_BREAKPOINT (0xff01)




/* Divide by zero */
#define E_DIVIDE_BY_ZERO (0xff02)




/* Overflow */
#define E_OVERFLOW (0xff03)




/* Illegal/privileged/restricted instruction/register/operand/addressing mode or trap encountered */
#define E_ILLEGAL_INSTRUCTION (0xff04)
/* The instruction opcode was not recognized
 * 	@@The opcode that caused the exception
 * 	member opcode: uintptr_t; */
#define E_ILLEGAL_INSTRUCTION_BAD_OPCODE (E_ILLEGAL_INSTRUCTION,0x0001)
/* The instruction's opcode is not supported by the host (not thrown if the instruction was emulated)
 * 	@@The opcode that caused the exception
 * 	member opcode: uintptr_t; */
#define E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE (E_ILLEGAL_INSTRUCTION,0x0002)
/* The calling code does not have the necessary privilege to invoke the instruction `opcode'
 * 	@@The opcode that caused the exception
 * 	member opcode: uintptr_t; */
#define E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE (E_ILLEGAL_INSTRUCTION,0x0003)
/* An operand of the instruction is invalid
 * 	@@The opcode that caused the exception
 * 	member opcode: uintptr_t;
 * 	@@For what reason was the operand invalid (One of `E_ILLEGAL_INSTRUCTION_BAD_OPERAND_*')
 * 	member what: uintptr_t; */
#define E_ILLEGAL_INSTRUCTION_BAD_OPERAND (E_ILLEGAL_INSTRUCTION,0x0010)
/* Invalid addressing mode used with the instruction */
#define E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE 0x0001
/* Attempted to access an invalid register `regno' (one of `<ARCH>_REGISTER_*')
 * 	@@The opcode that caused the exception
 * 	member opcode: uintptr_t;
 * 	@@How was the register accessed (One of `E_ILLEGAL_INSTRUCTION_REGISTER_*')
 * 	member how: uintptr_t;
 * 	@@The accessed register index
 * 	member regno: uintptr_t;
 * 	@@The associated register value (or 0 for read operations)
 * 	member regval: uintptr_t; */
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
/* The memory-accessing instruction was is not recognized for use in VIO
 * 	@@The opcode that caused the exception
 * 	member opcode: uintptr_t;
 * 	@@The virtual memory address that was accessed (or `NULL' if unknown)
 * 	member addr: void *; */
#define E_ILLEGAL_INSTRUCTION_VIO_UNRECOGNIZED (E_ILLEGAL_INSTRUCTION,0x1001)
/* The memory location addressed by a lock-prefixed instruction cannot operation as a `size'-wide atomic operation
 * 	@@The opcode that caused the exception
 * 	member opcode: uintptr_t;
 * 	@@The virtual memory address that was accessed
 * 	member addr: void *;
 * 	@@The number of bytes that were accessed atomically (usually one of 1,2,4 or 8)
 * 	member size: size_t; */
#define E_ILLEGAL_INSTRUCTION_VIO_NONATOMIC_OPERAND (E_ILLEGAL_INSTRUCTION,0x1002)
/* Attempted to set a kernel-space ESP to an invalid value during a VIO operation (can only be thrown when the kernel accesses VIO memory)
 * 	@@The opcode that caused the exception
 * 	member opcode: uintptr_t;
 * 	@@The kernel SP value that was attempted to be assigned
 * 	member value: uintptr_t; */
#define E_ILLEGAL_INSTRUCTION_VIO_INVALID_KERNEL_SP (E_ILLEGAL_INSTRUCTION,0x1011)




/* Thrown in kernel space when: #PF->#DF with ESP/RSP below stack_base
 * Thrown in user space when:   #PF ontop of a guard page with no remaining funds */
#define E_STACK_OVERFLOW (0xff05)




/* The BOUND instruction was executed with an out-of-bounds index */
#define E_INDEX_ERROR (0xff06)
/* An index was outside of the min/max bounds
 * 	@@The addressed index
 * 	member index: intptr_t;
 * 	@@The low bound of valid indices
 * 	member min: intptr_t;
 * 	@@The high bound of valid indices
 * 	member max: intptr_t; */
#define E_INDEX_ERROR_OUT_OF_BOUNDS (E_INDEX_ERROR,0x0001)




/* The alignment of an operand was not valid */
#define E_INVALID_ALIGNMENT (0xff07)
/* 	member addr: void *;
 * 	member req_alignment: size_t; */
#define E_INVALID_ALIGNMENT_POINTER (E_INVALID_ALIGNMENT,0x0001)

#endif /* !_KOS_ASM_EXCEPT_H */
