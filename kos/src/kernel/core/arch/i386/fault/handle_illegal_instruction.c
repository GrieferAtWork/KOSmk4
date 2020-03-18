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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_HANDLE_ILLEGAL_INSTRUCTION_C
#define GUARD_KERNEL_CORE_ARCH_I386_HANDLE_ILLEGAL_INSTRUCTION_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/arch/cpuid.h>
#include <kernel/debugtrap.h>
#include <kernel/emulock.h>
#include <kernel/except.h>
#include <kernel/fault.h>
#include <kernel/fpu.h>
#include <kernel/gdt.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/except-handler.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/bit.h>
#include <hybrid/byteswap.h>

#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/intrin-arith.h>
#include <asm/intrin.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>

#include <libinstrlen/instrlen.h>

#include "decode.h"
#include "handle_illegal_instruction-bitops.h"

#define CF EFLAGS_CF
#define PF EFLAGS_PF
#define AF EFLAGS_AF
#define ZF EFLAGS_ZF
#define SF EFLAGS_SF
#define TF EFLAGS_TF
#define IF EFLAGS_IF
#define DF EFLAGS_DF
#define OF EFLAGS_OF

#pragma GCC diagnostic ignored "-Waddress-of-packed-member"

DECL_BEGIN

#ifdef __x86_64__
#define IF_X86_64(...)  __VA_ARGS__
#define NIF_X86_64(...) /* nothing */
#else /* __x86_64__ */
#define IF_X86_64(...)  /* nothing */
#define NIF_X86_64(...) __VA_ARGS__
#endif /* !__x86_64__ */



typedef union {
	u32 lohi[2];
	u64 val64;
} LOHI64;

INTERN struct icpustate *FCALL
x86_handle_illegal_instruction(struct icpustate *__restrict state) {
	byte_t const *orig_pc, *pc;
	u32 opcode;
	op_flag_t op_flags;
	struct emu86_modrm mod;
	pc = (byte_t *)state->ics_irregs.ir_pip;
	COMPILER_READ_BARRIER();
	/* Re-enable interrupts if they were enabled before. */
	if (state->ics_irregs.ir_pflags & EFLAGS_IF)
		__sti();
	orig_pc  = pc;
	op_flags = emu86_opflagsof_icpustate(state);
	pc       = emu86_opcode_decode(pc, &opcode, &op_flags);
	TRY {
		if unlikely((pc - orig_pc) > 16) {
			uintptr_t next_pc;
			next_pc = (uintptr_t)orig_pc;
			next_pc = (uintptr_t)instruction_succ((void const *)next_pc);
			if (next_pc && next_pc > (uintptr_t)pc)
				pc = (byte_t *)next_pc;
			goto e_instruction_too_long;
		}
#ifdef __x86_64__
		if (opcode != 0xf05) /* `syscall' (prevent spam if unsupported...) */
#endif /* __x86_64__ */
		{
			printk(KERN_DEBUG "Illegal instruction %#I32x (from %p in %u)\n",
			       opcode, orig_pc, task_getroottid_s());
		}
		switch (opcode) {

#define get_al()       (u8)gpregs_getpax(&state->ics_gpregs)
#define set_al(value)  (*(u8 *)&state->ics_gpregs.gp_pax = (u8)(value)) /* Special case: Don't clobber %ah */
#define get_ax()       (u16)gpregs_getpax(&state->ics_gpregs)
#define set_ax(value)  gpregs_setpax(&state->ics_gpregs, (u16)(value))
#define get_eax()      (u32)gpregs_getpax(&state->ics_gpregs)
#define set_eax(value) gpregs_setpax(&state->ics_gpregs, (u32)(value))
#define get_ecx()      (u32)gpregs_getpcx(&state->ics_gpregs)
#define set_ecx(value) gpregs_setpcx(&state->ics_gpregs, (u32)(value))
#define get_edx()      (u32)gpregs_getpdx(&state->ics_gpregs)
#define set_edx(value) gpregs_setpdx(&state->ics_gpregs, (u32)(value))
#define get_ebx()      (u32)gpregs_getpbx(&state->ics_gpregs)
#define set_ebx(value) gpregs_setpbx(&state->ics_gpregs, (u32)(value))
#define get_eaxedx()   ((u64)get_eax() | (u64)get_edx() << 32)
#define get_ebxecx()   ((u64)get_ebx() | (u64)get_ecx() << 32)

#define isuser()                icpustate_isuser(state)
#define get_pflags()            icpustate_getpflags(state)
#define set_pflags(value)       icpustate_setpflags(state, value)
#define msk_pflags(mask, value) icpustate_mskpflags(state, mask, value)
#define add_pflags(mask)        msk_pflags(~0, mask)
#define del_pflags(mask)        msk_pflags(~(mask), 0)
#define set_pflags_mask(value, mask) \
	msk_pflags(~(mask), (value) & (mask))
#define MOD_DECODE() (pc = emu86_modrm_decode(pc, &mod, op_flags))

#define RD_RMB()  modrm_getrmb(state, &mod, op_flags)
#define WR_RMB(v) modrm_setrmb(state, &mod, op_flags, v)
#define RD_RMW()  modrm_getrmw(state, &mod, op_flags)
#define WR_RMW(v) modrm_setrmw(state, &mod, op_flags, v)
#define RD_RML()  modrm_getrml(state, &mod, op_flags)
#define WR_RML(v) modrm_setrml(state, &mod, op_flags, v)
#ifdef __x86_64__
#define RD_RMQ()  modrm_getrmq(state, &mod, op_flags)
#define WR_RMQ(v) modrm_setrmq(state, &mod, op_flags, v)
#endif /* __x86_64__ */

#define RD_RMREGB()  modrm_getrmregb(state, &mod, op_flags)
#define WR_RMREGB(v) modrm_setrmregb(state, &mod, op_flags, v)
#define RD_RMREGW()  modrm_getrmregw(state, &mod, op_flags)
#define WR_RMREGW(v) modrm_setrmregw(state, &mod, op_flags, v)
#define RD_RMREGL()  modrm_getrmregl(state, &mod, op_flags)
#define WR_RMREGL(v) modrm_setrmregl(state, &mod, op_flags, v)
#ifdef __x86_64__
#define RD_RMREGQ()  modrm_getrmregq(state, &mod, op_flags)
#define WR_RMREGQ(v) modrm_setrmregq(state, &mod, op_flags, v)
#endif /* __x86_64__ */

#define RD_REG()   modrm_getreg(state, &mod, op_flags)
#define WR_REG(v)  modrm_setreg(state, &mod, op_flags, v)
#define RD_REGB()  modrm_getregb(state, &mod, op_flags)
#define WR_REGB(v) modrm_setregb(state, &mod, op_flags, v)
#define RD_REGW()  modrm_getregw(state, &mod, op_flags)
#define WR_REGW(v) modrm_setregw(state, &mod, op_flags, v)
#define RD_REGL()  modrm_getregl(state, &mod, op_flags)
#define WR_REGL(v) modrm_setregl(state, &mod, op_flags, v)
#ifdef __x86_64__
#define RD_REGQ()  modrm_getregq(state, &mod, op_flags)
#define WR_REGQ(v) modrm_setregq(state, &mod, op_flags, v)
#endif /* __x86_64__ */

#define RD_VEXREG()   x86_icpustate_get(state, (u8)EMU86_F_VEX_VVVVV(op_flags))
#define WR_VEXREG(v)  x86_icpustate_set(state, (u8)EMU86_F_VEX_VVVVV(op_flags), v)
#define RD_VEXREGB()  x86_icpustate_get8(state, (u8)EMU86_F_VEX_VVVVV(op_flags))
#define WR_VEXREGB(v) x86_icpustate_set8(state, (u8)EMU86_F_VEX_VVVVV(op_flags), v)
#define RD_VEXREGW()  x86_icpustate_get16(state, (u8)EMU86_F_VEX_VVVVV(op_flags))
#define WR_VEXREGW(v) x86_icpustate_set16(state, (u8)EMU86_F_VEX_VVVVV(op_flags), v)
#define RD_VEXREGL()  x86_icpustate_get32(state, (u8)EMU86_F_VEX_VVVVV(op_flags))
#define WR_VEXREGL(v) x86_icpustate_set32(state, (u8)EMU86_F_VEX_VVVVV(op_flags), v)
#ifdef __x86_64__
#define RD_VEXREGQ()  x86_icpustate_get64(state, (u8)EMU86_F_VEX_VVVVV(op_flags))
#define WR_VEXREGQ(v) x86_icpustate_set64(state, (u8)EMU86_F_VEX_VVVVV(op_flags), v)
#endif /* __x86_64__ */


		/* Emulate syscall invocation methods not supported by the host */

		case 0x0f34:
			/* 0F 34       SYSENTER       Fast call to privilege level 0 system procedures. */
#ifdef __x86_64__
			if unlikely(!(op_flags & F_IS_X32)) {
				/* Only allowed from 32-bit user-space. */
				goto e_unsupported_instruction;
			}
			assert(isuser());
#else /* __x86_64__ */
			if unlikely(!isuser())
				goto e_unsupported_instruction; /* Not allowed from kernel-space. */
#endif /* !__x86_64__ */
			/* sysenter emulation */
			icpustate_setpc(state, (uintptr_t)pc);
			x86_syscall_emulate32_sysenter_r(state);

		case 0x0f05:
			/* 0F 05       SYSCALL        Fast call to privilege level 0 system procedures. */
#ifdef __x86_64__
			if unlikely(icpustate_getcs(state) != SEGMENT_USER_CODE64_RPL) { /* isuser32() */
				/* Only allowed from 64-bit user-space. */
				goto e_unsupported_instruction;
			}
			assert(!(op_flags & F_IS_X32));
			/* syscall emulation */
			icpustate_setpc(state, (uintptr_t)pc);
			x86_syscall_emulate64_int80h_r(state);
#else /* __x86_64__ */
			goto e_unsupported_instruction;
#endif /* !__x86_64__ */


#ifndef __x86_64__
		case 0x0fb0: {
			u8 temp, value, newvalue;
			MOD_DECODE();
			if (op_flags & (F_OP16 | F_AD16 | F_REP | F_REPNE))
				goto e_bad_prefix;
			/* 0F B0 /r      CMPXCHG r/m8,r8      Compare AL with r/m8. If equal, ZF is set and r8 is loaded into r/m8. Else, clear ZF and load r/m8 into AL */
			value    = get_al();
			newvalue = RD_REGB();
			if (EMU86_MODRM_ISREG(mod.mi_type)) {
				temp = RD_RMREGB();
				if (temp == value)
					WR_RMREGB(newvalue);
			} else {
				uintptr_t addr;
				addr = x86_decode_modrmgetmem(state, &mod, op_flags);
				if (op_flags & F_LOCK) {
					temp = x86_emulock_cmpxchg8((struct icpustate **)&state,
					                            (u8 *)addr, value, newvalue);
				} else {
					temp = *(u8 volatile *)addr;
					if (temp == value)
						*(u8 volatile *)addr = newvalue;
				}
			}
			set_al(temp);
			set_pflags_mask(__cmpb(value, temp),
			                ZF | CF | PF | AF | SF | OF);
		}	break;

		case 0x0fb1: {
			MOD_DECODE();
			if (op_flags & (F_AD16 | F_REP | F_REPNE))
				goto e_bad_prefix;
			/* 0F B1 /r      CMPXCHG r/m16,r16    Compare AX with r/m16. If equal, ZF is set and r16 is loaded into r/m16. Else, clear ZF and load r/m16 into AX */
			/* 0F B1 /r      CMPXCHG r/m32,r32    Compare EAX with r/m32. If equal, ZF is set and r32 is loaded into r/m32. Else, clear ZF and load r/m32 into EAX */
			if (op_flags & F_OP16) {
				u16 temp, value, newvalue;
				value    = get_ax();
				newvalue = RD_REGW();
				if (EMU86_MODRM_ISREG(mod.mi_type)) {
					temp = RD_RMREGW();
					if (temp == value)
						WR_RMREGW((u16)newvalue);
				} else {
					uintptr_t addr;
					addr = x86_decode_modrmgetmem(state, &mod, op_flags);
					if (op_flags & F_LOCK) {
						temp = x86_emulock_cmpxchg16((struct icpustate **)&state,
						                             (u16 *)addr, value, newvalue);
					} else {
						temp = *(u16 volatile *)addr;
						if (temp == value)
							*(u16 volatile *)addr = newvalue;
					}
				}
				set_ax(temp);
				set_pflags_mask(__cmpw((u16)value, temp),
				                ZF | CF | PF | AF | SF | OF);
			} else {
				u32 temp, value, newvalue;
				value    = get_eax();
				newvalue = RD_REGL();
				if (EMU86_MODRM_ISREG(mod.mi_type)) {
					temp = RD_RMREGL();
					if (temp == value)
						WR_RMREGL((u32)newvalue);
				} else {
					uintptr_t addr;
					addr = x86_decode_modrmgetmem(state, &mod, op_flags);
					if (op_flags & F_LOCK) {
						temp = x86_emulock_cmpxchg32((struct icpustate **)&state,
						                             (u32 *)addr, value, newvalue);
					} else {
						temp = *(u32 volatile *)addr;
						if ((u32)temp == value)
							*(u32 volatile *)addr = newvalue;
					}
				}
				set_eax(temp);
				set_pflags_mask(__cmpl(value, temp),
				                ZF | CF | PF | AF | SF | OF);
			}
		}	break;

		case 0x0fc7:
			MOD_DECODE();
			switch (mod.mi_reg) {

			case 1: {
				u64 old_value;
				u64 new_value;
				u64 real_old_value;
				uintptr_t addr;
				if (op_flags & (F_OP16 | F_AD16 | F_REP | F_REPNE))
					goto e_bad_prefix;
				if unlikely(!EMU86_MODRM_ISMEM(mod.mi_type))
					goto e_bad_operand_addrmode;
				/* 0F C7 /1 m64      CMPXCHG8B m64      Compare EDX:EAX with m64. If equal, set ZF and load ECX:EBX into m64. Else, clear ZF and load m64 into EDX:EAX */
				old_value = get_eaxedx();
				new_value = get_ebxecx();
				addr      = x86_decode_modrmgetmem(state, &mod, op_flags);
				if (op_flags & F_LOCK) {
					real_old_value = x86_emulock_cmpxchg64((struct icpustate **)&state,
					                                       (u64 *)addr, old_value, new_value);
				} else {
					real_old_value = *(u64 volatile *)addr;
					if (real_old_value == old_value)
						*(u64 volatile *)addr = new_value;
				}
				if (real_old_value == old_value) {
					add_pflags(ZF);
				} else {
					del_pflags(ZF);
					set_edx((u32)(real_old_value >> 32));
					set_eax((u32)real_old_value);
				}
			}	break;

			default: goto e_unknown_instruction;
			}
			break;

		case 0x0fc0: {
			u8 value, temp;
			uintptr_t new_eflags;
			/* 0F C0 /r      XADD r/m8, r8      Exchange r8 and r/m8; load sum into r/m8 */
			MOD_DECODE();
			if (op_flags & (F_OP16 | F_AD16 | F_REP | F_REPNE))
				goto e_bad_prefix;
			temp = RD_REGB();
			if (EMU86_MODRM_ISREG(mod.mi_type)) {
				value = RD_RMREGB();
				WR_RMREGB(value + temp);
			} else {
				uintptr_t addr;
				addr = x86_decode_modrmgetmem(state, &mod, op_flags);
				if (op_flags & F_LOCK) {
					u8 real_old_value;
					value = ATOMIC_READ(*(u8 *)addr);
					while ((real_old_value = x86_emulock_cmpxchg8((struct icpustate **)&state,
					                                              (u8 *)addr, value, value + temp)))
						value = real_old_value;
				} else {
					value = *(u8 volatile *)addr;
					*(u8 volatile *)addr = value + temp;
				}
			}
			WR_REGB((u8)value);
			new_eflags = __addb_ff(value, temp);
			set_pflags_mask(new_eflags, CF | PF | AF | SF | ZF | OF);
		}	break;

		case 0x0fc1: {
			uintptr_t new_eflags;
			/* 0F C1 /r      XADD r/m16, r16      Exchange r16 and r/m16; load sum into r/m16 */
			/* 0F C1 /r      XADD r/m32, r32      Exchange r32 and r/m32; load sum into r/m32 */
			MOD_DECODE();
			if (op_flags & (F_AD16 | F_REP | F_REPNE))
				goto e_bad_prefix;
			if (op_flags & F_OP16) {
				u16 value, temp;
				temp = RD_REGW();
				if (EMU86_MODRM_ISREG(mod.mi_type)) {
					value = RD_RMREGW();
					WR_RMREGW((u16)value + (u16)temp);
				} else {
					uintptr_t addr;
					addr = x86_decode_modrmgetmem(state, &mod, op_flags);
					if (op_flags & F_LOCK) {
						u16 real_old_value;
						value = ATOMIC_READ(*(u16 *)addr);
						while ((real_old_value = x86_emulock_cmpxchg16((struct icpustate **)&state,
						                                               (u16 *)addr, value, value + temp)))
							value = real_old_value;
					} else {
						value = *(u16 volatile *)addr;
						*(u16 volatile *)addr = value + temp;
					}
				}
				WR_REGW((u16)value);
				new_eflags = __addw_ff(value, temp);
			} else {
				u32 value, temp;
				temp = RD_REGL();
				if (EMU86_MODRM_ISREG(mod.mi_type)) {
					value = RD_RMREGL();
					WR_RMREGL((u32)value + (u32)temp);
				} else {
					uintptr_t addr;
					addr = x86_decode_modrmgetmem(state, &mod, op_flags);
					if (op_flags & F_LOCK) {
						u32 real_old_value;
						value = ATOMIC_READ(*(u32 *)addr);
						while ((real_old_value = x86_emulock_cmpxchg32((struct icpustate **)&state,
						                                               (u32 *)addr, value, value + temp)))
							value = real_old_value;
					} else {
						value = *(u32 volatile *)addr;
						*(u32 volatile *)addr = value + temp;
					}
				}
				WR_REGL((u32)value);
				new_eflags = __addl_ff(value, temp);
			}
			set_pflags_mask(new_eflags, CF | PF | AF | SF | ZF | OF);
		}	break;

		case 0x0fc8 ... 0x0fcf: {
			/* BSWAP r32  -- Added with 80486 */
			if (op_flags & (F_OP16 | F_AD16 | F_LOCK | F_REP | F_REPNE))
				goto e_bad_prefix;
#ifdef __x86_64__
			if (op_flags & F_REX_W) {
				/* volatile to prevent the compiler from optimizing into another `bswap' instruction! */
				volatile u64 tempval;
				tempval = x86_icpustate_get64(state, op_flags & F_REX_R
					                                 ? (opcode - 0x0fc8) + 8
					                                 : (opcode - 0x0fc8));
				tempval = BSWAP64_C(tempval);
				x86_icpustate_set64(state, op_flags & F_REX_R ? (opcode - 0x0fc8) + 8 : (opcode - 0x0fc8),
					                tempval);
			} else
#endif /* __x86_64__ */
			{
				u32 value;
				__register u16 temp;
#ifdef __x86_64__
				value = x86_icpustate_get32(state,
				                            op_flags & F_REX_R
				                            ? (opcode - 0x0fc8) + 8
				                            : (opcode - 0x0fc8));
#else /* __x86_64__ */
				value = x86_icpustate_get32(state, opcode - 0x0fc8);
#endif /* !__x86_64__ */
				/* Use inline assembly so GCC doesn't optimize by
				 * using the instruction we're trying to emulate. */
				__asm__ __volatile__("movw  0+%0, %1\n\t" /* x = lo; */
					                 "xchgb %b1, %h1\n\t" /* x = x << 8 | x >> 8; */
					                 "xchgw 2+%0, %1\n\t" /* temp = hi,hi = x,x = temp; */
					                 "xchgb %b1, %h1\n\t" /* x = x << 8 | x >> 8; */
					                 "movw  %1, 0+%0"     /* lo = x; */
					                 : "+m" (value)
					                 , "=&q" (temp));
#ifdef __x86_64__
				x86_icpustate_set32(state,
				                    op_flags & F_REX_R
				                    ? (opcode - 0x0fc8) + 8
				                    : (opcode - 0x0fc8),
				                   (u32)value);
#else /* __x86_64__ */
				x86_icpustate_set32(state,
				                    opcode - 0x0fc8,
				                    (u32)value);
#endif /* !__x86_64__ */
			}
		}	break;

#define DEFINE_MOVcc(opcode, cond_expr)                         \
		case opcode: {                                          \
			uintptr_t pflags;                                   \
			MOD_DECODE();                                       \
			if (op_flags & (F_AD16 | F_LOCK | F_REP | F_REPNE)) \
				goto e_bad_prefix;                              \
			pflags = get_pflags();                              \
			if (cond_expr) {                                    \
				if (op_flags & F_OP16) {                        \
					WR_REGW(RD_RMW());                          \
				} else {                                        \
					WR_REGL(RD_RML());                          \
				}                                               \
			}                                                   \
		}	break

		/* 0F 40      CMOVO r16, r/m16        Move if overflow (OF=1) */
		/* 0F 40      CMOVO r32, r/m32        Move if overflow (OF=1) */
		DEFINE_MOVcc(0x0f40, pflags & OF);

		/* 0F 41      CMOVNO r16, r/m16       Move if not overflow (OF=0) */
		/* 0F 41      CMOVNO r32, r/m32       Move if not overflow (OF=0) */
		DEFINE_MOVcc(0x0f41, !(pflags & OF));

		/* 0F 42      CMOVB r16, r/m16        Move if below (CF=1) */
		/* 0F 42      CMOVB r32, r/m32        Move if below (CF=1) */
		/* 0F 42      CMOVC r16, r/m16        Move if carry (CF=1) */
		/* 0F 42      CMOVC r32, r/m32        Move if carry (CF=1) */
		/* 0F 42      CMOVNAE r16, r/m16      Move if not above or equal (CF=1) */
		/* 0F 42      CMOVNAE r32, r/m32      Move if not above or equal (CF=1) */
		DEFINE_MOVcc(0x0f42, pflags & CF);

		/* 0F 43      CMOVAE r16, r/m16       Move if above or equal (CF=0) */
		/* 0F 43      CMOVAE r32, r/m32       Move if above or equal (CF=0) */
		/* 0F 43      CMOVNB r16, r/m16       Move if not below (CF=0) */
		/* 0F 43      CMOVNB r32, r/m32       Move if not below (CF=0) */
		/* 0F 43      CMOVNC r16, r/m16       Move if not carry (CF=0) */
		/* 0F 43      CMOVNC r32, r/m32       Move if not carry (CF=0) */
		DEFINE_MOVcc(0x0f43, !(pflags & CF));

		/* 0F 44      CMOVE r16, r/m16        Move if equal (ZF=1) */
		/* 0F 44      CMOVE r32, r/m32        Move if equal (ZF=1) */
		/* 0F 44      CMOVZ r16, r/m16        Move if zero (ZF=1) */
		/* 0F 44      CMOVZ r32, r/m32        Move if zero (ZF=1) */
		DEFINE_MOVcc(0x0f44, pflags & ZF);

		/* 0F 45      CMOVNE r16, r/m16       Move if not equal (ZF=0) */
		/* 0F 45      CMOVNE r32, r/m32       Move if not equal (ZF=0) */
		/* 0F 45      CMOVNZ r16, r/m16       Move if not zero (ZF=0) */
		/* 0F 45      CMOVNZ r32, r/m32       Move if not zero (ZF=0) */
		DEFINE_MOVcc(0x0f45, !(pflags & ZF));

		/* 0F 46      CMOVBE r16, r/m16       Move if below or equal (CF=1 or ZF=1) */
		/* 0F 46      CMOVBE r32, r/m32       Move if below or equal (CF=1 or ZF=1) */
		/* 0F 46      CMOVNA r16, r/m16       Move if not above (CF=1 or ZF=1) */
		/* 0F 46      CMOVNA r32, r/m32       Move if not above (CF=1 or ZF=1) */
		DEFINE_MOVcc(0x0f46, pflags & (CF|ZF));

		/* 0F 47      CMOVA r16, r/m16        Move if above (CF=0 and ZF=0) */
		/* 0F 47      CMOVA r32, r/m32        Move if above (CF=0 and ZF=0) */
		/* 0F 47      CMOVNBE r16, r/m16      Move if not below or equal (CF=0 and ZF=0) */
		/* 0F 47      CMOVNBE r32, r/m32      Move if not below or equal (CF=0 and ZF=0) */
		DEFINE_MOVcc(0x0f47, !(pflags & (CF|ZF)));

		/* 0F 48      CMOVS r16, r/m16        Move if sign (SF=1) */
		/* 0F 48      CMOVS r32, r/m32        Move if sign (SF=1) */
		DEFINE_MOVcc(0x0f48, pflags & SF);

		/* 0F 49      CMOVNS r16, r/m16       Move if not sign (SF=0) */
		/* 0F 49      CMOVNS r32, r/m32       Move if not sign (SF=0) */
		DEFINE_MOVcc(0x0f49, !(pflags & SF));

		/* 0F 4A      CMOVP r16, r/m16        Move if parity (PF=1) */
		/* 0F 4A      CMOVP r32, r/m32        Move if parity (PF=1) */
		/* 0F 4A      CMOVPE r16, r/m16       Move if parity even (PF=1) */
		/* 0F 4A      CMOVPE r32, r/m32       Move if parity even (PF=1) */
		DEFINE_MOVcc(0x0f4a, pflags & PF);

		/* 0F 4B      CMOVNP r16, r/m16       Move if not parity (PF=0) */
		/* 0F 4B      CMOVNP r32, r/m32       Move if not parity (PF=0) */
		/* 0F 4B      CMOVPO r16, r/m16       Move if parity odd (PF=0) */
		/* 0F 4B      CMOVPO r32, r/m32       Move if parity odd (PF=0) */
		DEFINE_MOVcc(0x0f4b, !(pflags & PF));

		/* 0F 4C      CMOVL r16, r/m16        Move if less (SF<>OF) */
		/* 0F 4C      CMOVL r32, r/m32        Move if less (SF<>OF) */
		/* 0F 4C      CMOVNGE r16, r/m16      Move if not greater or equal (SF<>OF) */
		/* 0F 4C      CMOVNGE r32, r/m32      Move if not greater or equal (SF<>OF) */
		DEFINE_MOVcc(0x0f4c, !!(pflags & SF) != !!(pflags & OF));

		/* 0F 4D      CMOVGE r16, r/m16       Move if greater or equal (SF=OF) */
		/* 0F 4D      CMOVGE r32, r/m32       Move if greater or equal (SF=OF) */
		/* 0F 4D      CMOVNL r16, r/m16       Move if not less (SF=OF) */
		/* 0F 4D      CMOVNL r32, r/m32       Move if not less (SF=OF) */
		DEFINE_MOVcc(0x0f4d, !!(pflags & SF) == !!(pflags & OF));

		/* 0F 4E      CMOVLE r16, r/m16       Move if less or equal (ZF=1 or SF<>OF) */
		/* 0F 4E      CMOVLE r32, r/m32       Move if less or equal (ZF=1 or SF<>OF) */
		/* 0F 4E      CMOVNG r16, r/m16       Move if not greater (ZF=1 or SF<>OF) */
		/* 0F 4E      CMOVNG r32, r/m32       Move if not greater (ZF=1 or SF<>OF) */
		DEFINE_MOVcc(0x0f4e, (pflags & ZF) || (!!(pflags & SF) != !!(pflags & OF)));

		/* 0F 4F      CMOVG r16, r/m16        Move if greater (ZF=0 and SF=OF) */
		/* 0F 4F      CMOVG r32, r/m32        Move if greater (ZF=0 and SF=OF) */
		/* 0F 4F      CMOVNLE r16, r/m16      Move if not less or equal (ZF=0 and SF=OF) */
		/* 0F 4F      CMOVNLE r32, r/m32      Move if not less or equal (ZF=0 and SF=OF) */
		DEFINE_MOVcc(0x0f4f, !(pflags & ZF) && (!!(pflags & SF) == !!(pflags & OF)));
#undef DEFINE_MOVcc

		case 0x0f31: {
			qtime_t now;
			u64 result;
			/* 0F 31       RDTSC       Read time-stamp counter into EDX:EAX */
			if ((__rdcr4() & CR4_TSD) && isuser())
				goto e_privileged_instruction;
			now    = cpu_quantum_time();
			result = (u64)now.q_jtime * now.q_qsize;
			result += (u64)now.q_qtime;
			set_eax((u32)result);
			set_edx((u32)(result >> 32));
		} break;

#endif /* !__x86_64__ */


#ifndef X86_ALWAYS_HAVE_CPUID
		case 0x0fa2: {
			struct cpuinfo const *info;
			/* CPUID */
			info = &CURRENT_X86_CPUID;
			switch (get_eax()) {

			case 0:
				set_eax(info->ci_0a);
				set_ebx(info->ci_0b);
				set_ecx(info->ci_0c);
				set_edx(info->ci_0d);
				break;

			case 1:
				set_eax(info->ci_1a);
				set_ebx(info->ci_1b);
				set_ecx(info->ci_1c);
				set_edx(info->ci_1d);
				break;

			case 7:
				set_eax(0);
				set_ebx(info->ci_7b);
				set_ecx(info->ci_7c);
				set_edx(info->ci_7d);
				break;

			case 0x80000000:
				set_eax(info->ci_80000000a);
#if 1
				set_ebx(info->ci_0b);
				set_ecx(info->ci_0c);
				set_edx(info->ci_0d);
#else
				set_ebx(0);
				set_ecx(0);
				set_edx(0);
#endif
				break;

			case 0x80000001:
				set_eax(0);
				set_ebx(0);
				set_ecx(info->ci_80000001c);
				set_edx(info->ci_80000001d);
				break;

			case 0x80000002:
				set_eax(info->ci_80000002a);
				set_ebx(info->ci_80000002b);
				set_ecx(info->ci_80000002c);
				set_edx(info->ci_80000002d);
				break;

			case 0x80000003:
				set_eax(info->ci_80000003a);
				set_ebx(info->ci_80000003b);
				set_ecx(info->ci_80000003c);
				set_edx(info->ci_80000003d);
				break;

			case 0x80000004:
				set_eax(info->ci_80000004a);
				set_ebx(info->ci_80000004b);
				set_ecx(info->ci_80000004c);
				set_edx(info->ci_80000004d);
				break;

			default:
				set_eax(0);
				set_ecx(0);
				set_edx(0);
				set_ebx(0);
				break;
			}
		}	break;
#endif /* !X86_ALWAYS_HAVE_CPUID */



		case 0x0fae:
			MOD_DECODE();
			switch (mod.mi_reg) {

#if 1
#define TRACE_SEGMENT_BASE_ACCESS(...) printk(KERN_DEBUG "[x86] emu: " __VA_ARGS__)
#else
#define TRACE_SEGMENT_BASE_ACCESS(...) (void)0
#endif

			case 0:
				/* rdfsbase */
				if ((op_flags & (F_AD16 | F_OP16 | F_LOCK | F_REPNE | F_REP)) != F_REP) {
					uintptr_t addr;
					if (op_flags & (F_LOCK))
						goto e_bad_prefix;
					if (!EMU86_MODRM_ISMEM(mod.mi_type))
						goto e_bad_operand_addrmode;
					/* FXSAVE m512byte */
					addr = x86_decode_modrmgetmem(state, &mod, op_flags);
					if (isuser())
						validate_writable((void *)addr, 512);
					x86_fxsave((USER CHECKED struct xfpustate *)(void *)addr);
					break;
				}
				if (!EMU86_MODRM_ISREG(mod.mi_type))
					goto e_bad_operand_addrmode;
#ifndef __x86_64__
				{
					u16 myfs = state->ics_fs16 & ~3;
					u32 base;
					if (myfs == SEGMENT_USER_FSBASE) {
						base = get_user_fsbase();
					} else if (myfs == SEGMENT_USER_GSBASE) {
						base = get_user_gsbase();
					} else {
						base = 0;
					}
					TRACE_SEGMENT_BASE_ACCESS("rdfsbase():%#Ix\n", base);
					WR_RMREGL(base);
				}
#else /* !__x86_64__ */
				{
					LOHI64 temp;
					if (op_flags & F_REX_W) {
						/* rdfsbase %r64 */
						temp.val64 = __rdmsr(IA32_FS_BASE);
					} else {
						/* rdfsbase %r32 */
						temp.lohi[0] = __rdmsr32(IA32_FS_BASE);
						temp.lohi[1] = 0;
					}
					TRACE_SEGMENT_BASE_ACCESS("rdfsbase():%#Ix\n", temp.val64);
					WR_RMREGQ(temp.val64);
				}
#endif /* __x86_64__ */
				break;

			case 1:
				/* rdgsbase */
				if ((op_flags & (F_AD16 | F_OP16 | F_LOCK | F_REPNE | F_REP)) != F_REP) {
					uintptr_t addr;
					if (op_flags & (F_LOCK))
						goto e_bad_prefix;
					if (!EMU86_MODRM_ISMEM(mod.mi_type))
						goto e_bad_operand_addrmode;
					/* FXRSTOR m512byte */
					addr = x86_decode_modrmgetmem(state, &mod, op_flags);
					if (isuser())
						validate_readable((void *)addr, 512);
					x86_fxrstor((USER CHECKED struct xfpustate *)(void *)addr);
					break;
				}
				if (!EMU86_MODRM_ISREG(mod.mi_type))
					goto e_bad_operand_addrmode;
#ifndef __x86_64__
				{
					u16 mygs = __rdgs() & ~3;
					u32 base;
					if (mygs == SEGMENT_USER_GSBASE) {
						base = get_user_gsbase();
					} else if (mygs == SEGMENT_USER_FSBASE) {
						base = get_user_fsbase();
					} else {
						base = 0;
					}
					TRACE_SEGMENT_BASE_ACCESS("user:rdgsbase():%#Ix\n", base);
					WR_RMREGL(base);
				}
#else /* !__x86_64__ */
				{
					LOHI64 temp;
					/* NOTE: We must load `IA32_KERNEL_GS_BASE', since the `swapgs' invoked upon
					 *       entry into kernel-space has caused the actual user-space GS to be
					 *       saved within the `IA32_KERNEL_GS_BASE' msr */
					u32 msr = isuser() ? IA32_KERNEL_GS_BASE : IA32_GS_BASE;
					if (op_flags & F_REX_W) {
						/* rdgsbase %r64 */
						temp.val64 = __rdmsr(msr);
					} else {
						/* rdgsbase %r32 */
						temp.lohi[0] = __rdmsr32(msr);
						temp.lohi[1] = 0;
					}
					TRACE_SEGMENT_BASE_ACCESS("%s:rdgsbase():%#Ix\n",
					                          msr == IA32_KERNEL_GS_BASE
					                          ? "user"
					                          : "kernel",
					                          temp.val64);
					WR_RMREGQ(temp.val64);
				}
#endif /* __x86_64__ */
				break;

			case 2:
				/* wrfsbase */
				if (!(op_flags & F_REP))
					goto generic_illegal_instruction;
				if (!EMU86_MODRM_ISREG(mod.mi_type))
					goto e_bad_operand_addrmode;
#ifndef __x86_64__
				{
					u16 myfs = state->ics_fs16 & ~3;
					u32 val  = RD_RMREGL();
					TRACE_SEGMENT_BASE_ACCESS("wrfsbase(%#Ix)\n", val);
					/* Check which segment `%fs' actually refers to */
					if (myfs == SEGMENT_USER_FSBASE)
						set_user_fsbase(val);
					else if (myfs == SEGMENT_USER_GSBASE) {
						set_user_gsbase(val);
						update_user_fsbase(); /* Force a segment reload */
					} else {
						/* Don't allow user-space to set the bases of any other segment.
						 * As such, throw an exception indicating a privileged register (which SOME_SEGMENT.base is) */
						PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
						PERTASK_SET(this_exception_pointers[1], (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV);
						PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_FS);
						PERTASK_SET(this_exception_pointers[3], (uintptr_t)val);
						goto set_generic_illegal_instruction_4;
					}
				}
#else /* !__x86_64__ */
				{
					LOHI64 temp;
					temp.val64 = RD_RMREGQ();
					/* wrfsbase %r32 / %r64 */
					if (!(op_flags & F_REX_W))
						temp.lohi[1] = 0;
					TRACE_SEGMENT_BASE_ACCESS("wrfsbase(%#Ix)\n", temp.val64);
					__wrmsr(IA32_FS_BASE, temp.val64);
				}
#endif /* __x86_64__ */
				break;

			case 3:
				/* wrgsbase */
				if (!(op_flags & F_REP))
					goto generic_illegal_instruction;
				if (!EMU86_MODRM_ISREG(mod.mi_type))
					goto e_bad_operand_addrmode;
				/* XXX: Check if `%gs == SEGMENT_USER_GSBASE_RPL' */
#ifndef __x86_64__
				/* Check which segment `%gs' actually refers to */
				{
					u16 mygs = __rdgs() & ~3;
					u32 val = RD_RMREGL();
					TRACE_SEGMENT_BASE_ACCESS("user:wrgsbase(%#Ix)\n", val);
					if (mygs == SEGMENT_USER_GSBASE)
						set_user_gsbase(val);
					else if (mygs == SEGMENT_USER_FSBASE) {
						set_user_fsbase(val);
						update_user_gsbase(); /* Force a segment reload */
					} else {
						/* Don't allow user-space to set the bases of any other segment.
						 * As such, throw an exception indicating a privileged register (which SOME_SEGMENT.base is) */
						PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
						PERTASK_SET(this_exception_pointers[1], (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV);
						PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_GS);
						PERTASK_SET(this_exception_pointers[3], (uintptr_t)val);
						goto set_generic_illegal_instruction_4;
					}
				}
#else /* !__x86_64__ */
				{
					LOHI64 temp;
					/* NOTE: We must write `IA32_KERNEL_GS_BASE', since the `swapgs' invoked upon
					 *       entry into kernel-space has caused the actual user-space GS to be
					 *       saved within the `IA32_KERNEL_GS_BASE' msr */
					u32 msr = isuser() ? IA32_KERNEL_GS_BASE : IA32_GS_BASE;
					temp.val64 = RD_RMREGQ();
					/* wrgsbase %r32 / %r64 */
					if (!(op_flags & F_REX_W))
						temp.lohi[1] = 0;
					TRACE_SEGMENT_BASE_ACCESS("%s:wrgsbase(%#Ix)\n",
					                          msr == IA32_KERNEL_GS_BASE
					                          ? "user"
					                          : "kernel",
					                          temp.val64);
					__wrmsr(msr, temp.val64);
				}
#endif /* __x86_64__ */
				break;

			case 7:
				/* sfence, lfence, mfence */
				if (op_flags & (F_AD16 | F_LOCK | F_REP | F_REPNE))
					goto e_bad_prefix;
				/* Serialize memory by executing an atomic instruction. */
				{
					static int volatile atom = 0;
					__asm__ __volatile__("xchgl %0, %1"
					                     : "+m" (atom)
					                     : "r" (1)
					                     : "memory");
				}
				break;

			default:
				goto generic_illegal_instruction;
			}
			break;

		case 0x0f01:
			MOD_DECODE();
			if (op_flags & (F_LOCK | F_REP | F_REPNE))
				goto e_bad_prefix;
			if (mod.mi_reg == 0) {
				if (EMU86_MODRM_ISREG(mod.mi_type)) {
					switch (mod.mi_rm) {
					case 1: /* VMCALL */
					case 2: /* VMLAUNCH */
					case 3: /* VMRESUME */
					case 4: /* VMXOFF */
						if (isuser())
							goto e_privileged_instruction;
						goto e_unsupported_instruction;
					default:
						goto e_unknown_instruction;
					}
				}
				if (isuser())
					goto e_privileged_instruction;
				goto e_bad_operand_addrmode; /* SGDT m16&32 */
			}
			if (mod.mi_reg == 1) {
				if (EMU86_MODRM_ISREG(mod.mi_type)) {
					switch (mod.mi_rm) {

					case 2: /* CLAC */
#if !(EFLAGS_UMASK & EFLAGS_AC)
						if (isuser())
							goto e_privileged_instruction;
#endif /* !(EFLAGS_UMASK & EFLAGS_AC) */
						del_pflags(EFLAGS_AC);
						goto done;

					case 3: /* STAC */
#if !(EFLAGS_UMASK & EFLAGS_AC)
						if (isuser())
							goto e_privileged_instruction;
#endif /* !(EFLAGS_UMASK & EFLAGS_AC) */
						add_pflags(EFLAGS_AC);
						goto done;

					case 0: /* MONITOR */
					case 1: /* MWAIT */
					case 7: /* ENCLS */
						if (isuser())
							goto e_privileged_instruction;
						goto e_unsupported_instruction;

					default:
						goto e_unknown_instruction;
					}
				}
				if (isuser())
					goto e_privileged_instruction;
				goto e_bad_operand_addrmode; /* SIDT m16&32 */
			}
			if (mod.mi_reg == 2) {
				if (EMU86_MODRM_ISREG(mod.mi_type)) {
					switch (mod.mi_rm) {

					case 0: /* XGETBV */
					case 1: /* XSETBV */
					case 4: /* VMFUNC */
					case 5: /* VMFUNC */
					case 6: /* XTEST */
					case 7: /* ENCLU */
						if (isuser())
							goto e_privileged_instruction;
						goto e_unsupported_instruction;

					default:
						goto e_unknown_instruction;
					}
				}
				goto e_bad_operand_addrmode; /* LGDT m16&32 */
			}
			if (mod.mi_reg == 3) {
				if (EMU86_MODRM_ISREG(mod.mi_type))
					goto e_bad_operand_addrmode; /* LIDT m16&32 */
				if (isuser())
					goto e_privileged_instruction;
				goto e_unknown_instruction;
			}
			if (mod.mi_reg == 7) {
				/* INVLPG m */
				if (!EMU86_MODRM_ISMEM(mod.mi_type)) {
					switch (mod.mi_rm) {

					case 0:
						/* SWAPGS */
						if (isuser())
							goto e_privileged_instruction;
#ifdef __x86_64__
						{
							u64 temp = __rdmsr(IA32_KERNEL_GS_BASE);
							__wrmsr(IA32_KERNEL_GS_BASE, __rdmsr(IA32_GS_BASE));
							__wrmsr(IA32_KERNEL_GS_BASE, temp);
						}
						goto done;
#else /* __x86_64__ */
						goto e_unsupported_instruction;
#endif /* !__x86_64__ */

					case 1:
						/* RDTSCP */
						goto e_unsupported_instruction;

					default:
						goto e_unknown_instruction;
					}
				}
				if (isuser())
					goto e_privileged_instruction;
				/* Without INVLPG, we can only flush the entire page directory. */
				{
					__register uintptr_t temp;
					__asm__ __volatile__("mov %%cr3, %0\n\t"
					                     "mov %0, %%cr3"
					                     : "=&r" (temp)
					                     :
					                     : "memory");
				}
				goto done;
			}
			goto e_unknown_instruction;

		case 0x90:
			/* 90       NOP       No operation. */
			/* F3 90    PAUSE     Gives hint to processor that improves performance of spin-wait loops. */
			if (op_flags & (F_AD16 | F_REPNE))
				goto e_bad_prefix;
			break;

		case 0x0f32: /* RDMSR */
			if (op_flags & (F_AD16 | F_LOCK | F_REP | F_REPNE))
				goto e_bad_prefix;
			PERTASK_SET(this_exception_pointers[1],
			            isuser() ? (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV
			                      : (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDINV);
			PERTASK_SET(this_exception_pointers[4], (uintptr_t)0);
			PERTASK_SET(this_exception_pointers[5], (uintptr_t)0);
			goto e_bad_msr_regno;

		case 0x0f30: /* WRMSR */
			if (op_flags & (F_AD16 | F_LOCK | F_REP | F_REPNE))
				goto e_bad_prefix;
			PERTASK_SET(this_exception_pointers[1],
			            isuser() ? (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV
			                      : (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRINV);
			PERTASK_SET(this_exception_pointers[4], (uintptr_t)get_eax());
			PERTASK_SET(this_exception_pointers[5], (uintptr_t)get_edx());
			goto e_bad_msr_regno;


		case 0x0fc3:
			/* MOVNTI m32, r32 */
			MOD_DECODE();
			if (op_flags & (F_AD16 | F_LOCK | F_REP | F_REPNE))
				goto e_bad_prefix;
			if (!EMU86_MODRM_ISMEM(mod.mi_type))
				goto e_bad_operand_addrmode;
			IF_X86_64(if (op_flags & F_REX_W) {
				WR_RMQ(RD_REGQ());
			} else) {
				WR_RML(RD_REGL());
			}
			break;

		case 0x0f18:
			MOD_DECODE();
			if (op_flags & (F_AD16 | F_LOCK | F_REP | F_REPNE))
				goto e_bad_prefix;
			if (!EMU86_MODRM_ISMEM(mod.mi_type))
				goto e_bad_operand_addrmode;
			if (mod.mi_reg > 3)
				goto generic_illegal_instruction;
			/* PREFETCHT0 m8 */
			/* PREFETCHT1 m8 */
			/* PREFETCHT2 m8 */
			/* PREFETCHNTA m8 */
			break;

		case 0x0f38f0:
			/*         0F 38 F0 /r MOVBE r16, m16 RM      Reverse byte order in m16 and move to r16.
			 *         0F 38 F0 /r MOVBE r32, m32 RM      Reverse byte order in m32 and move to r32.
			 * REX.W + 0F 38 F0 /r MOVBE r64, m64 RM      Reverse byte order in m64 and move to r64. */
			MOD_DECODE();
			if (op_flags & (F_AD16 | F_LOCK | F_REP | F_REPNE))
				goto e_bad_prefix;
			IF_X86_64(if (op_flags & F_REX_W) {
				WR_REGQ(__bswapq(RD_RMQ()));
			} else) if (!(op_flags & F_OP16)) {
				WR_REGL(__bswapl(RD_RML()));
			} else {
				WR_REGW(__bswapw(RD_RMW()));
			}
			break;

		case 0x0f38f1:
			/*         0F 38 F1 /r MOVBE m16, r16 MR      Reverse byte order in r16 and move to m16.
			 *         0F 38 F1 /r MOVBE m32, r32 MR      Reverse byte order in r32 and move to m32.
			 * REX.W + 0F 38 F1 /r MOVBE m64, r64 MR      Reverse byte order in r64 and move to m64. */
			MOD_DECODE();
			if (op_flags & (F_AD16 | F_LOCK | F_REP | F_REPNE))
				goto e_bad_prefix;
			IF_X86_64(if (op_flags & F_REX_W) {
				WR_RMQ(__bswapq(RD_REGQ()));
			} else) if (!(op_flags & F_OP16)) {
				WR_RML(__bswapl(RD_REGL()));
			} else {
				WR_RMW(__bswapw(RD_REGW()));
			}
			break;


		case 0x0f38f7:
			/* VEX.LZ.F3.0F38.W0 F7 /r SARX r32a, r/m32, r32b     Shift r/m32 arithmetically right with count specified in r32b.
			 * VEX.LZ.66.0F38.W0 F7 /r SHLX r32a, r/m32, r32b     Shift r/m32 logically left with count specified in r32b.
			 * VEX.LZ.F2.0F38.W0 F7 /r SHRX r32a, r/m32, r32b     Shift r/m32 logically right with count specified in r32b.
			 * VEX.LZ.F3.0F38.W1 F7 /r SARX r64a, r/m64, r64b     Shift r/m64 arithmetically right with count specified in r64b.
			 * VEX.LZ.66.0F38.W1 F7 /r SHLX r64a, r/m64, r64b     Shift r/m64 logically left with count specified in r64b.
			 * VEX.LZ.F2.0F38.W1 F7 /r SHRX r64a, r/m64, r64b     Shift r/m64 logically right with count specified in r64b. */
			MOD_DECODE();
			if (op_flags & (F_AD16 | F_VEX_LL_M NIF_X86_64(| F_VEX_W)))
				goto e_bad_prefix;
			if (op_flags & F_f3) {
				/* SARX */
				IF_X86_64(if (op_flags & F_VEX_W) {
					WR_VEXREGQ(__sarq(RD_RMQ(), RD_REGQ()));
				} else) {
					WR_VEXREGL(__sarl(RD_RML(), RD_REGL()));
				}
			} else if (op_flags & F_66) {
				/* SHLX */
				IF_X86_64(if (op_flags & F_VEX_W) {
					WR_VEXREGQ(__shlq(RD_RMQ(), RD_REGQ()));
				} else) {
					WR_VEXREGL(__shll(RD_RML(), RD_REGL()));
				}
			} else if (op_flags & F_f2) {
				/* SHRX */
				IF_X86_64(if (op_flags & F_VEX_W) {
					WR_VEXREGQ(__shrq(RD_RMQ(), RD_REGQ()));
				} else) {
					WR_VEXREGL(__shrl(RD_RML(), RD_REGL()));
				}
			} else {
				goto e_unknown_instruction;
			}
			break;

		case 0x0f3af0: {
			u8 temp;
			/* VEX.LZ.F2.0F3A.W0 F0 /r ib RORX r32, r/m32, imm8     Rotate 32-bit r/m32 right imm8 times without affecting arithmetic flags.
			 * VEX.LZ.F2.0F3A.W1 F0 /r ib RORX r64, r/m64, imm8     Rotate 64-bit r/m64 right imm8 times without affecting arithmetic flags. */
			MOD_DECODE();
			if (op_flags & (F_AD16 | F_LOCK | F_REPNE) || !(op_flags & F_REP))
				goto e_bad_prefix;
			temp = *pc++;
			IF_X86_64(if (op_flags & F_VEX_W) {
				WR_REGQ(__rorq(RD_RMQ(), (u8)temp));
			} else) {
				WR_REGL(__rorl(RD_RML(), (u8)temp));
			}
		}	break;

		case 0x0fb8: {
			/* F3 0F B8 /r        POPCNT r16, r/m16     POPCNT on r/m16
			 * F3 0F B8 /r        POPCNT r32, r/m32     POPCNT on r/m32
			 * F3 REX.W 0F B8 /r  POPCNT r64, r/m64     POPCNT on r/m64 */
			uintptr_t pflags;
			MOD_DECODE();
			if (op_flags & (F_AD16 | F_LOCK | F_REPNE) || !(op_flags & F_REP))
				goto e_bad_prefix;
			pflags = get_pflags();
			IF_X86_64(if (op_flags & F_REX_W) {
				WR_REGQ(simple_popcnt64(RD_RMQ(), &pflags));
			} else) if (!(op_flags & F_OP16)) {
				WR_REGL(simple_popcnt32(RD_RML(), &pflags));
			} else {
				WR_REGW(simple_popcnt16(RD_RMW(), &pflags));
			}
			set_pflags(pflags);
		}	break;

		case 0x0fbc: {
			uintptr_t pflags;
			/* F3 0F BC /r       TZCNT r16, r/m16   A   V/V      BMI1   Count the number of trailing zero bits in r/m16, return result in r16.
			 * F3 0F BC /r       TZCNT r32, r/m32   A   V/V      BMI1   Count the number of trailing zero bits in r/m32, return result in r32.
			 * F3 REX.W 0F BC /r TZCNT r64, r/m64   A   V/N.E.   BMI1   Count the number of trailing zero bits in r/m64, return result in r64. */
			MOD_DECODE();
			if (op_flags & (F_AD16 | F_LOCK | F_REPNE) || !(op_flags & F_REP))
				goto e_bad_prefix;
			pflags = get_pflags();
			IF_X86_64(if (op_flags & F_REX_W) {
				WR_REGQ(simple_tzcnt64(RD_RMQ(), &pflags));
			} else) if (!(op_flags & F_OP16)) {
				WR_REGL(simple_tzcnt32(RD_RML(), &pflags));
			} else {
				WR_REGW(simple_tzcnt16(RD_RMW(), &pflags));
			}
			set_pflags(pflags);
		}	break;

		case 0x0fbd: {
			uintptr_t pflags;
			/* F3 0F BD /r        LZCNT r16, r/m16
			 * F3 0F BD /r        LZCNT r32, r/m32
			 * F3 REX.W 0F BD /r  LZCNT r64, r/m64 */
			MOD_DECODE();
			if (op_flags & (F_AD16 | F_LOCK | F_REPNE) || !(op_flags & F_REP))
				goto e_bad_prefix;
			pflags = get_pflags();
			IF_X86_64(if (op_flags & F_REX_W) {
				WR_REGQ(simple_lzcnt64(RD_RMQ(), &pflags));
			} else) if (!(op_flags & F_OP16)) {
				WR_REGL(simple_lzcnt32(RD_RML(), &pflags));
			} else {
				WR_REGW(simple_lzcnt16(RD_RMW(), &pflags));
			}
			set_pflags(pflags);
		}	break;

		case 0x0f38f5:
			MOD_DECODE();
			if (op_flags & (F_AD16 | F_LOCK | F_VEX_LL_M))
				goto e_bad_prefix;
			if (op_flags & F_f3) {
				/* VEX.LZ.F3.0F38.W0 F5 /r PEXT r32a, r32b, r/m32         RVM         V/V         BMI2         Parallel extract of bits from r32b using mask in r/m32, result is written to r32a.
				 * VEX.LZ.F3.0F38.W1 F5 /r PEXT r64a, r64b, r/m64         RVM         V/N.E.         BMI2         Parallel extract of bits from r64b using mask in r/m64, result is written to r64a. */
				IF_X86_64(if (op_flags & F_REX_W) {
					WR_REGQ(PEXT(RD_VEXREGQ(), RD_RMQ()));
				} else) {
					WR_REGL(PEXT(RD_VEXREGL(), RD_RML()));
				}
			} else if (op_flags & F_f2) {
				/* VEX.LZ.F2.0F38.W0 F5 /r PDEP r32a, r32b, r/m32         RVM         V/V         BMI2         Parallel deposit of bits from r32b using mask in r/m32, result is written to r32a.
				 * VEX.LZ.F2.0F38.W1 F5 /r PDEP r64a, r64b, r/m64         RVM         V/N.E.         BMI2         Parallel deposit of bits from r64b using mask in r/m64, result is written to r64a. */
				IF_X86_64(if (op_flags & F_REX_W) {
					WR_REGQ(PDEP(RD_VEXREGQ(), RD_RMQ()));
				} else) {
					WR_REGL(PDEP(RD_VEXREGL(), RD_RML()));
				}
			} else {
				/* VEX.LZ.0F38.W0 F5 /r BZHI r32a, r/m32, r32b         RMV         V/V         BMI2         Zero bits in r/m32 starting with the position in r32b, write result to r32a.
				 * VEX.LZ.0F38.W1 F5 /r BZHI r64a, r/m64, r64b         RMV         V/N.E.         BMI2         Zero bits in r/m64 starting with the position in r64b, write result to r64a. */
				uint8_t n = (uint8_t)RD_VEXREG();
				uintptr_t pflags;
				pflags = get_pflags();
				IF_X86_64(if (op_flags & F_VEX_W) {
					u64 temp;
					temp = RD_RMQ();
					if (n < 64)
						temp &= (((u64)1 << n) - 1);
					WR_REGQ((u64)temp);
					pflags &= ~(OF | CF | SF | ZF);
					if (n > 63)
						pflags |= CF;
					pflags |= __testq((u64)temp, (u64)temp) & (SF | ZF);
				} else) {
					u32 temp;
					temp = RD_RML();
					if (n < 32)
						temp &= (((u32)1 << n) - 1);
					WR_REGL((u32)temp);
					pflags &= ~(OF | CF | SF | ZF);
					if (n > 31)
						pflags |= CF;
					pflags |= __testl((u32)temp, (u32)temp) & (SF | ZF);
				}
				set_pflags(pflags);
			}
			break;

		case 0x0f38f2: {
			uintptr_t pflags;
			MOD_DECODE();
			if (op_flags & (F_AD16 | F_LOCK | F_REP | F_REPNE | F_VEX_LL_M))
				goto e_bad_prefix;
			/* VEX.LZ.0F38.W0 F2 /r ANDN r32a, r32b, r/m32         RVM         V/V         BMI1         Bitwise AND of inverted r32b with r/m32, store result in r32a.
			 * VEX.LZ.0F38.W1 F2 /r ANDN r64a, r64b, r/m64         RVM         V/NE         BMI1         Bitwise AND of inverted r64b with r/m64, store result in r64a. */
			pflags = get_pflags();
			IF_X86_64(if (op_flags & F_VEX_W) {
				u64 temp;
				temp = (~RD_VEXREGQ()) & RD_RMQ();
				WR_REGQ((u64)temp);
				pflags &= ~(SF | ZF | OF | CF);
				if (!(u64)temp)
					pflags |= ZF;
				if ((u64)temp & UINT64_C(0x8000000000000000))
					pflags |= SF;
			} else) {
				u32 temp;
				temp = (~RD_VEXREGL()) & RD_RML();
				WR_REGL((u32)temp);
				pflags &= ~(SF | ZF | OF | CF);
				if (!(u32)temp)
					pflags |= ZF;
				if ((u32)temp & UINT32_C(0x80000000))
					pflags |= SF;
			}
			set_pflags(pflags);
		}	break;


//TODO: VEX.LZ.0F38.W0 F3 /1 BLSR r32, r/m32         VM         V/V         BMI1         Reset lowest set bit of r/m32, keep all other bits of r/m32 and write result to r32.
//TODO: VEX.LZ.0F38.W1 F3 /1 BLSR r64, r/m64         VM         V/N.E.         BMI1         Reset lowest set bit of r/m64, keep all other bits of r/m64 and write result to r64.
//TODO: VEX.LZ.0F38.W0 F3 /2 BLSMSK r32, r/m32         VM         V/V         BMI1         Set all lower bits in r32 to “1” starting from bit 0 to lowest set bit in r/m32.
//TODO: VEX.LZ.0F38.W1 F3 /2 BLSMSK r64, r/m64         VM         V/N.E.         BMI1         Set all lower bits in r64 to “1” starting from bit 0 to lowest set bit in r/m64.
//TODO: VEX.LZ.0F38.W0 F3 /3 BLSI r32, r/m32         VM         V/V         BMI1         Extract lowest set bit from r/m32 and set that bit in r32.
//TODO: VEX.LZ.0F38.W1 F3 /3 BLSI r64, r/m64         VM         V/N.E.         BMI1         Extract lowest set bit from r/m64, and set that bit in r64.

//TODO: VEX.LZ.F2.0F38.W0 F6 /r MULX r32a, r32b, r/m32         RVM         V/V         BMI2         Unsigned multiply of r/m32 with EDX without affecting arithmetic flags.
//TODO: VEX.LZ.F2.0F38.W1 F6 /r MULX r64a, r64b, r/m64         RVM         V/N.E.         BMI2         Unsigned multiply of r/m64 with RDX without affecting arithmetic flags.
//TODO: 66 0F 38 F6 /r ADCX r32, r/m32         RM         V/V         ADX         Unsigned addition of r32 with CF, r/m32 to r32, writes CF.
//TODO: 66 REX.w 0F 38 F6 /r ADCX r64, r/m64         RM         V/NE         ADX         Unsigned addition of r64 with CF, r/m64 to r64, writes CF.
//TODO: F3 0F 38 F6 /r ADOX r32, r/m32         RM         V/V         ADX         Unsigned addition of r32 with OF, r/m32 to r32, writes OF.
//TODO: F3 REX.w 0F 38 F6 /r ADOX r64, r/m64         RM         V/NE         ADX         Unsigned addition of r64 with OF, r/m64 to r64, writes OF.

//TODO: VEX.LZ.0F38.W0 F7 /r BEXTR r32a, r/m32, r32b         RMV         V/V         BMI1         Contiguous bitwise extract from r/m32 using r32b as control; store result in r32a.
//TODO: VEX.LZ.0F38.W1 F7 /r BEXTR r64a, r/m64, r64b         RMV         V/N.E.         BMI1         Contiguous bitwise extract from r/m64 using r64b as control; store result in r64a

  /* TODO: Emulate Intel's new set of bound instructions: */
//TODO:66 0F 1A /r BNDMOV bnd1, bnd2/m64         RM         NE/V         MPX         Move lower and upper bound from bnd2/m64 to bound register bnd1.
//TODO:66 0F 1A /r BNDMOV bnd1, bnd2/m128         RM         V/NE         MPX         Move lower and upper bound from bnd2/m128 to bound register bnd1.
//TODO:66 0F 1B /r BNDMOV bnd1/m64, bnd2         MR         NE/V         MPX         Move lower and upper bound from bnd2 to bnd1/m64.
//TODO:66 0F 1B /r BNDMOV bnd1/m128, bnd2         MR         V/NE         MPX         Move lower and upper bound from bnd2 to bound register bnd1/m128.

		default: {
			uintptr_t next_pc;
e_unknown_instruction:
			next_pc = icpustate_getpc(state);
			next_pc = (uintptr_t)instruction_succ((void const *)next_pc);
			if (next_pc)
				pc = (byte_t *)next_pc;
			goto generic_illegal_instruction;
		}	break;
		}
	} EXCEPT {
		if (was_thrown(E_ILLEGAL_INSTRUCTION) &&
		    PERTASK_GET(this_exception_pointers[0]) == 0) {
			PERTASK_SET(this_exception_pointers[0], (uintptr_t)opcode);
			PERTASK_SET(this_exception_faultaddr, (void *)orig_pc);
		} else if (isuser()) {
			PERTASK_SET(this_exception_faultaddr, (void *)orig_pc);
		}
		icpustate_setpc(state, (uintptr_t)pc);
		RETHROW();
	}
done:
	icpustate_setpc(state, (uintptr_t)pc);
	return state;
	{
		unsigned int i;
e_bad_msr_regno:
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
		PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_MSR);
		PERTASK_SET(this_exception_pointers[3], (uintptr_t)get_ecx());
		i = 6;
		goto set_generic_illegal_instruction;
e_bad_operand_addrmode:
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND));
		PERTASK_SET(this_exception_pointers[1], (uintptr_t)E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE);
		i = 2;
		goto set_generic_illegal_instruction;
#ifndef __x86_64__
set_generic_illegal_instruction_4:
		i = 4;
		goto set_generic_illegal_instruction;
#endif /* !__x86_64__ */
e_privileged_instruction:
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE));
		i = 1;
		goto set_generic_illegal_instruction;
e_unsupported_instruction:
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE));
		i = 1;
		goto set_generic_illegal_instruction;
e_bad_prefix:
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX));
		i = 1;
		goto set_generic_illegal_instruction;
e_instruction_too_long:
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_X86_TOO_LONG));
		i = 1;
		goto set_generic_illegal_instruction;
generic_illegal_instruction:
		/* Quick check if the #UD was triggered due to an invalid prefix. */
		if (op_flags & F_AD16)
			goto e_bad_prefix;
		if (op_flags & F_REP) {
			switch (opcode) {
			case 0x6c: /* F3 6C       REP INS m8, DX     Input (E)CX bytes from port DX into ES:[(E)DI] */
			case 0x6d: /* F3 6D       REP INS m16, DX    Input (E)CX words from port DX into ES:[(E)DI] */
			           /* F3 6D       REP INS m32, DX    Input (E)CX doublewords from port DX into ES:[(E)DI] */
			case 0xA4: /* F3 A4       REP MOVS m8, m8    Move (E)CX bytes from DS:[(E)SI] to ES:[(E)DI] */
			case 0xA5: /* F3 A5       REP MOVS m16, m16  Move (E)CX words from DS:[(E)SI] to ES:[(E)DI] */
			           /* F3 A5       REP MOVS m32, m32  Move (E)CX doublewords from DS:[(E)SI] to ES:[(E)DI] */
			case 0x6E: /* F3 6E       REP OUTS DX, r/m8  Output (E)CX bytes from DS:[(E)SI] to port DX */
			case 0x6F: /* F3 6F       REP OUTS DX, r/m16 Output (E)CX words from DS:[(E)SI] to port DX */
			           /* F3 6F       REP OUTS DX, r/m32 Output (E)CX doublewords from DS:[(E)SI] to port DX */
			case 0xAC: /* F3 AC       REP LODS AL        Load (E)CX bytes from DS:[(E)SI] to AL */
			case 0xAD: /* F3 AD       REP LODS AX        Load (E)CX words from DS:[(E)SI] to AX */
			           /* F3 AD       REP LODS EAX       Load (E)CX doublewords from DS:[(E)SI] to EAX */
			case 0xAA: /* F3 AA       REP STOS m8        Fill (E)CX bytes at ES:[(E)DI] with AL */
			case 0xAB: /* F3 AB       REP STOS m16       Fill (E)CX words at ES:[(E)DI] with AX */
			           /* F3 AB       REP STOS m32       Fill (E)CX doublewords at ES:[(E)DI] with EAX */
			case 0xA6: /* F3 A6       REPE CMPS m8, m8   Find nonmatching bytes in ES:[(E)DI] and DS:[(E)SI] */
			case 0xA7: /* F3 A7       REPE CMPS m16, m16 Find nonmatching words in ES:[(E)DI] and DS:[(E)SI] */
			           /* F3 A7       REPE CMPS m32, m32 Find nonmatching doublewords in ES:[(E)DI] and DS:[(E)SI] */
			case 0xAE: /* F3 AE       REPE SCAS m8       Find non-AL byte starting at ES:[(E)DI] */
			case 0xAF: /* F3 AF       REPE SCAS m16      Find non-AX word starting at ES:[(E)DI] */
			           /* F3 AF       REPE SCAS m32      Find non-EAX doubleword starting at ES:[(E)DI] */
			case 0x90: /* F3 90       PAUSE       Gives hint to processor that improves performance of spin-wait loops. */
				break;
			default: goto e_bad_prefix;
			}
		}
		if (op_flags & F_REPNE) {
			switch (opcode) {
			case 0xA6: /* F2 A6       REPNE CMPS m8, m8   Find matching bytes in ES:[(E)DI] and DS:[(E)SI] */
			case 0xA7: /* F2 A7       REPNE CMPS m16, m16 Find matching words in ES:[(E)DI] and DS:[(E)SI] */
			           /* F2 A7       REPNE CMPS m32, m32 Find matching doublewords in ES:[(E)DI] and DS:[(E)SI] */
			case 0xAE: /* F2 AE       REPNE SCAS m8       Find AL, starting at ES:[(E)DI] */
			case 0xAF: /* F2 AF       REPNE SCAS m16      Find AX, starting at ES:[(E)DI] */
			           /* F2 AF       REPNE SCAS m32      Find EAX, starting at ES:[(E)DI] */
				break;
			default: goto e_bad_prefix;
			}
		}
		if (op_flags & F_LOCK) {
			switch (opcode) {
			case 0x0fbb: /* 0F BB      BTC r/m16, r16      Store selected bit in CF flag and complement */
			             /* 0F BB      BTC r/m32, r32      Store selected bit in CF flag and complement */
			case 0x0fb3: /* 0F B3      BTR r/m16, r16      Store selected bit in CF flag and clear */
			             /* 0F B3      BTR r/m32, r32      Store selected bit in CF flag and clear */
			case 0x0fab: /* 0F AB      BTS r/m16, r16      Store selected bit in CF flag and set */
			             /* 0F AB      BTS r/m32, r32      Store selected bit in CF flag and set */
			case 0xfe:   /* FE /0      INC r/m8      Increment r/m byte by 1 */
			             /* FE /1      DEC r/m8      Decrement r/m8 by 1 */
			case 0xff:   /* FF /0      INC r/m16     Increment r/m word by 1 */
			             /* FF /0      INC r/m32     Increment r/m doubleword by 1 */
			             /* FF /1      DEC r/m16     Decrement r/m16 by 1 */
			             /* FF /1      DEC r/m32     Decrement r/m32 by 1 */
			case 0x0fb0: /* 0F B0 /r      CMPXCHG r/m8,r8      Compare AL with r/m8. If equal, ZF is set and r8 is loaded into r/m8. Else, clear ZF and load r/m8 into AL */
			case 0x0fb1: /* 0F B1 /r      CMPXCHG r/m16,r16    Compare AX with r/m16. If equal, ZF is set and r16 is loaded into r/m16. Else, clear ZF and load r/m16 into AX */
			             /* 0F B1 /r      CMPXCHG r/m32,r32    Compare EAX with r/m32. If equal, ZF is set and r32 is loaded into r/m32. Else, clear ZF and load r/m32 into EAX */
			case 0x0fc7: /* 0F C7 /1 m64      CMPXCHG8B m64      Compare EDX:EAX with m64. If equal, set ZF and load ECX:EBX into m64. Else, clear ZF and load m64 into EDX:EAX */
			case 0xf6:   /* F6 /2      NOT r/m8      Reverse each bit of r/m8 */
			             /* F6 /3      NEG r/m8      Two's complement negate r/m8 */
			case 0xf7:   /* F7 /2      NOT r/m16      Reverse each bit of r/m16 */
			             /* F7 /2      NOT r/m32      Reverse each bit of r/m32 */
			             /* F7 /3      NEG r/m16      Two's complement negate r/m16 */
			             /* F7 /3      NEG r/m32      Two's complement negate r/m32 */
			case 0x0fc0: /* 0F C0 /r      XADD r/m8, r8      Exchange r8 and r/m8; load sum into r/m8 */
			case 0x0fc1: /* 0F C1 /r      XADD r/m16, r16      Exchange r16 and r/m16; load sum into r/m16 */
			             /* 0F C1 /r      XADD r/m32, r32      Exchange r32 and r/m32; load sum into r/m32 */
			case 0xc0:   /* C0 /0 ib      ROL r/m8,imm8      Rotate 8 bits r/m8 left imm8 times */
			             /* C0 /1 ib      ROR r/m8,imm8      Rotate 8 bits r/m16 right imm8 times */
			             /* C0 /2 ib      RCL r/m8,imm8      Rotate 9 bits (CF, r/m8) left imm8 times */
			             /* C0 /3 ib      RCR r/m8,imm8      Rotate 9 bits (CF, r/m8) right imm8 times */
			             /* C0 /4 ib      SAL r/m8,imm8      Multiply r/m8 by 2, imm8 times */
			             /* C0 /4 ib      SHL r/m8,imm8      Multiply r/m8 by 2, imm8 times */
			             /* C0 /5 ib      SHR r/m8,imm8      Unsigned divide r/m8 by 2, imm8 times */
			             /* C0 /7 ib      SAR r/m8,imm8      Signed divide* r/m8 by 2, imm8 times */
			case 0xc1:   /* C1 /0 ib      ROL r/m16,imm8      Rotate 16 bits r/m16 left imm8 times. */
			             /* C1 /0 ib      ROL r/m32,imm8      Rotate 32 bits r/m32 left imm8 times */
			             /* C1 /1 ib      ROR r/m16,imm8      Rotate 16 bits r/m16 right imm8 times */
			             /* C1 /1 ib      ROR r/m32,imm8      Rotate 32 bits r/m32 right imm8 times */
			             /* C1 /2 ib      RCL r/m16,imm8      Rotate 17 bits (CF, r/m16) left imm8 times */
			             /* C1 /2 ib      RCL r/m32,imm8      Rotate 33 bits (CF, r/m32) left imm8 times */
			             /* C1 /3 ib      RCR r/m16,imm8      Rotate 17 bits (CF, r/m16) right imm8 times */
			             /* C1 /3 ib      RCR r/m32,imm8      Rotate 33 bits (CF, r/m32) right imm8 times */
			             /* C1 /4 ib      SAL r/m16,imm8      Multiply r/m16 by 2, imm8 times */
			             /* C1 /4 ib      SAL r/m32,imm8      Multiply r/m32 by 2, imm8 times */
			             /* C1 /4 ib      SHL r/m16,imm8      Multiply r/m16 by 2, imm8 times */
			             /* C1 /4 ib      SHL r/m32,imm8      Multiply r/m32 by 2, imm8 times */
			             /* C1 /5 ib      SHR r/m16,imm8      Unsigned divide r/m16 by 2, imm8 times */
			             /* C1 /5 ib      SHR r/m32,imm8      Unsigned divide r/m32 by 2, imm8 times */
			             /* C1 /7 ib      SAR r/m16,imm8      Signed divide* r/m16 by 2, imm8 times */
			             /* C1 /7 ib      SAR r/m32,imm8      Signed divide* r/m32 by 2, imm8 times */
			case 0xd0:   /* D0 /0      ROL r/m8, 1      Rotate 8 bits r/m8 left once */
			             /* D0 /1      ROR r/m8, 1      Rotate 8 bits r/m8 right once */
			             /* D0 /2      RCL r/m8, 1      Rotate 9 bits (CF, r/m8) left once */
			             /* D0 /3      RCR r/m8, 1      Rotate 9 bits (CF, r/m8) right once */
			             /* D0 /4      SAL r/m8      Multiply r/m8 by 2, 1 time */
			             /* D0 /4      SHL r/m8      Multiply r/m8 by 2, 1 time */
			             /* D0 /5      SHR r/m8      Unsigned divide r/m8 by 2, 1 time */
			             /* D0 /7      SAR r/m8      Signed divide* r/m8 by 2, 1 times */
			case 0xd1:   /* D1 /0      ROL r/m16, 1      Rotate 16 bits r/m16 left once */
			             /* D1 /0      ROL r/m32, 1      Rotate 32 bits r/m32 left once */
			             /* D1 /1      ROR r/m16, 1      Rotate 16 bits r/m16 right once */
			             /* D1 /1      ROR r/m32, 1      Rotate 32 bits r/m32 right once */
			             /* D1 /2      RCL r/m16, 1      Rotate 17 bits (CF, r/m16) left once */
			             /* D1 /2      RCL r/m32, 1      Rotate 33 bits (CF, r/m32) left once */
			             /* D1 /3      RCR r/m16, 1      Rotate 17 bits (CF, r/m16) right once */
			             /* D1 /3      RCR r/m32, 1      Rotate 33 bits (CF, r/m32) right once */
			             /* D1 /4      SAL r/m16      Multiply r/m16 by 2, 1 time */
			             /* D1 /4      SAL r/m32      Multiply r/m32 by 2, 1 time */
			             /* D1 /4      SHL r/m16      Multiply r/m16 by 2, 1 time */
			             /* D1 /4      SHL r/m32      Multiply r/m32 by 2, 1 time */
			             /* D1 /5      SHR r/m16      Unsigned divide r/m16 by 2, 1 time */
			             /* D1 /5      SHR r/m32      Unsigned divide r/m32 by 2, 1 time */
			             /* D1 /7      SAR r/m16      Signed divide* r/m16 by 2, 1 time */
			             /* D1 /7      SAR r/m32      Signed divide* r/m32 by 2, 1 time */
			case 0x0fa4: /* 0F A4      SHLD r/m16, r16, imm8      Shift r/m16 to left imm8 places while shifting bits from r16 in from the right */
			             /* 0F A4      SHLD r/m32, r32, imm8      Shift r/m32 to left imm8 places while shifting bits from r32 in from the right */
			case 0x0fa5: /* 0F A5      SHLD r/m16, r16, CL      Shift r/m16 to left CL places while shifting bits from r16 in from the right */
			             /* 0F A5      SHLD r/m32, r32, CL      Shift r/m32 to left CL places while shifting bits from r32 in from the right */
			case 0x0fac: /* 0F AC      SHRD r/m16, r16, imm8      Shift r/m16 to right imm8 places while shifting bits from r16 in from the left */
			             /* 0F AC      SHRD r/m32, r32, imm8      Shift r/m32 to right imm8 places while shifting bits from r32 in from the left */
			case 0x0fad: /* 0F AD      SHRD r/m16, r16, CL      Shift r/m16 to right CL places while shifting bits from r16 in from the left */
			             /* 0F AD      SHRD r/m32, r32, CL      Shift r/m32 to right CL places while shifting bits from r32 in from the left */
				break;
			default: goto e_bad_prefix;
			}
		}
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPCODE));
		i = 1;
set_generic_illegal_instruction:
		PERTASK_SET(this_exception_pointers[0], (uintptr_t)opcode);
		for (; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
#if EXCEPT_BACKTRACE_SIZE != 0
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
			PERTASK_SET(this_exception_trace[i], (void *)0);
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	}
	PERTASK_SET(this_exception_faultaddr, (void *)orig_pc);
	icpustate_setpc(state, (uintptr_t)pc);
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled() && (kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_ILLEGAL_INSTRUCTION))
		kernel_debugtrap(state, SIGILL);
	x86_userexcept_unwind_interrupt(state);
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_HANDLE_ILLEGAL_INSTRUCTION_C */
