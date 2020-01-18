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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_GPF_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_GPF_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/fault.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/except-handler.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/unaligned.h>

#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/intrin.h>
#include <asm/registers-compat.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/paging.h>

#include <stdbool.h>
#include <string.h>

#include <libinstrlen/instrlen.h>

#include "decode.h"

DECL_BEGIN

PRIVATE struct icpustate *FCALL
x86_handle_gpf_impl(struct icpustate *__restrict state,
                    uintptr_t ecode, bool is_ss);

INTERN struct icpustate *FCALL
x86_handle_stackfault(struct icpustate *__restrict state, uintptr_t ecode) {
	return x86_handle_gpf_impl(state, ecode, true);
}

INTERN struct icpustate *FCALL
x86_handle_gpf(struct icpustate *__restrict state, uintptr_t ecode) {
	return x86_handle_gpf_impl(state, ecode, false);
}

#ifdef __x86_64__
DATDEF byte_t x86_memcpy_nopf_rep_pointer[];
DATDEF byte_t x86_memcpy_nopf_ret_pointer[];
#endif /* __x86_64__ */

PRIVATE struct icpustate *FCALL
x86_handle_gpf_impl(struct icpustate *__restrict state, uintptr_t ecode, bool is_ss) {
	byte_t *orig_pc, *pc;
	u32 opcode;
	op_flag_t op_flags;
	struct modrm mod;
	u16 effective_segment_value;
	unsigned int i;
	pc = (byte_t *)state->ics_irregs.ir_pip;
	COMPILER_READ_BARRIER();
	/* Re-enable interrupts if they were enabled before. */
	if (state->ics_irregs.ir_pflags & EFLAGS_IF)
		__sti();
	orig_pc = pc;
#define isuser() icpustate_isuser(state)

#ifdef __x86_64__
	if unlikely(ADDR_IS_NONCANON(pc)) {
		/* Special case: Non-canonical program counter
		 * Just like with #PF for `%cr2 == %rip', handle this case by trying to
		 * restore the original RIP-value from `0(%rsp)', assuming that the RIP
		 * register ended up getting corrupted due to a bad `call', rather than
		 * a bad `jmp' */
		uintptr_t callsite_pc;
		uintptr_t sp = icpustate_getsp(state);
		unsigned int i;
		bool is_compat;
		callsite_pc = (uintptr_t)pc;
		if (sp >= KERNELSPACE_BASE && isuser())
			goto set_noncanon_pc_exception;
		is_compat = icpustate_is32bit(state);
		TRY {
			if (is_compat) {
				callsite_pc = (uintptr_t)*(u32 *)sp;
			} else {
				callsite_pc = *(uintptr_t *)sp;
			}
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT)) {
				if (isuser())
					PERTASK_SET(this_exception_faultaddr, (void *)pc);
				RETHROW();
			}
			goto set_noncanon_pc_exception;
		}
		if (isuser() ? (callsite_pc >= USERSPACE_END)
		             : (callsite_pc < KERNELSPACE_BASE)) {
			callsite_pc = (uintptr_t)pc;
			goto set_noncanon_pc_exception;
		}
		icpustate_setpc(state, callsite_pc);
		icpustate_setsp(state, is_compat ? sp + 4 : sp + 8);
		TRY {
			void const *call_instr;
			call_instr = instruction_pred((void *)callsite_pc);
			if likely(call_instr)
				callsite_pc = (uintptr_t)call_instr;
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT)) {
				if (isuser())
					PERTASK_SET(this_exception_faultaddr, (void *)pc);
				RETHROW();
			}
			/* Discard read-from-callsite_pc exception... */
		}
set_noncanon_pc_exception:
		PERTASK_SET(this_exception_faultaddr, (void *)callsite_pc);
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE));
		PERTASK_SET(this_exception_pointers[0], (uintptr_t)pc);
		PERTASK_SET(this_exception_pointers[1],
		            (uintptr_t)(E_SEGFAULT_CONTEXT_USERCODE |
		                        E_SEGFAULT_CONTEXT_NONCANON));
		if (!isuser())
			PERTASK_SET(this_exception_pointers[1], (uintptr_t)E_SEGFAULT_CONTEXT_NONCANON);
		for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
		printk(KERN_DEBUG "[segfault] PC-Fault at %p [pc=%p,%p] [ecode=%#x] [#GPF] [tid=%u]\n",
		       pc, callsite_pc, icpustate_getpc(state),
		       ecode, (unsigned int)task_getroottid_s());
		goto unwind_state;
	}
#endif /* __x86_64__ */

	opcode = x86_decode_instruction(state, &pc, &op_flags);

	/* TODO: Some instructions (such as `XSAVEC') raise #GP if their operands are miss-aligned.
	 *       KOS has a dedicated exception for this (`E_SEGFAULT_UNALIGNED') that should be
	 *       thrown in such cases! */

	TRY {
#define MOD_DECODE() (pc = x86_decode_modrm(pc, &mod, op_flags))

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
#endif /* !__x86_64__ */

		if (is_ss) {
			effective_segment_value = icpustate_getss(state);
		} else {
			switch (op_flags & F_SEGMASK) {
			case F_SEGFS: effective_segment_value = icpustate_getfs(state); break;
			case F_SEGGS: effective_segment_value = icpustate_getgs(state); break;
#ifndef __x86_64__
			case F_SEGDS: effective_segment_value = icpustate_getds(state); break;
			case F_SEGES: effective_segment_value = icpustate_getes(state); break;
			case F_SEGCS: effective_segment_value = icpustate_getcs(state); break;
			case F_SEGSS: effective_segment_value = icpustate_getss(state); break;
			default: __builtin_unreachable(); break;
#else /* !__x86_64__ */
			default: effective_segment_value = icpustate_getds(state); break;
#endif /* !__x86_64__ */
			}
		}

#if defined(__x86_64__)
		/* Check for #GPFs caused by non-canonical memory accesses. */
		if (ecode == 0 && !is_ss) {
			uintptr_t nc_addr;
			byte_t *pc_after_opcode = pc;
			switch (opcode) {

			case 0x88:    /* MOV r/m8,r8 */
			case 0x89:    /* MOV r/m16,r16; MOV r/m32,r32; MOV r/m64,r64 */
			case 0x8c:    /* MOV r/m16,Sreg** */
			case 0xc6:    /* MOV r/m8, imm8 */
			case 0xc7:    /* MOV r/m16, imm16; MOV r/m32, imm32; MOV r/m64, imm32 */
			case 0x80:    /* ADC r/m8, imm8 */
			case 0x81:    /* ADC r/m16, imm16; ADC r/m32, imm32; ADC r/m64, imm32 */
			case 0x83:    /* ADC r/m16, imm8; ADC r/m32, imm8; ADC r/m64, imm8 */
			case 0x0f97:  /* seta r/m8 */
			case 0x0f93:  /* setae r/m8 */
			case 0x0f92:  /* setb r/m8 */
			case 0x0f96:  /* setbe r/m8 */
			case 0x0f94:  /* sete r/m8 */
			case 0x0f9f:  /* setg r/m8 */
			case 0x0f9d:  /* setge r/m8 */
			case 0x0f9c:  /* setl r/m8 */
			case 0x0f9e:  /* setle r/m8 */
			case 0x0f95:  /* setne r/m8 */
			case 0x0f91:  /* setno r/m8 */
			case 0x0f9b:  /* setnp r/m8 */
			case 0x0f99:  /* setns r/m8 */
			case 0x0f9a:  /* setp r/m8 */
			case 0x0f98:  /* sets r/m8 */
			case 0x0f47:  /* cmova r/m16, r16 */
			case 0x0f43:  /* cmovae r/m16, r16 */
			case 0x0f42:  /* cmovb r/m16, r16 */
			case 0x0f46:  /* cmovbe r/m16, r16 */
			case 0x0f44:  /* cmove r/m16, r16 */
			case 0x0f4f:  /* cmovg r/m16, r16 */
			case 0x0f4d:  /* cmovge r/m16, r16 */
			case 0x0f4c:  /* cmovl r/m16, r16 */
			case 0x0f4e:  /* cmovle r/m16, r16 */
			case 0x0f45:  /* cmovne r/m16, r16 */
			case 0x0f41:  /* cmovno r/m16, r16 */
			case 0x0f4b:  /* cmovnp r/m16, r16 */
			case 0x0f49:  /* cmovns r/m16, r16 */
			case 0x0f40:  /* cmovo r/m16, r16 */
			case 0x0f4a:  /* cmovp r/m16, r16 */
			case 0x0f48:  /* cmovs r/m16, r16 */
			case 0x0fc3:  /* movnti r32, m32 */
			case 0x0f29:  /* movapd xmm2/m128, xmm1 / movaps xmm2/m128, xmm1 */
			case 0x0f6e:  /* movd r/m32, mm / movd r/m32, xmm */
			case 0x0f12:  /* movddup xmm2/m64, xmm1 / movhlps xmm2, xmm1
			               * movlpd m64, xmm / movlps m64, xmm / movsldup xmm2/m128, xmm1 */
			case 0x0f6f:  /* movdqa xmm2/m128, xmm1 / movdqu xmm2/m128, xmm1
			               * movq mm/m64, mm */
				MOD_DECODE();
				if (mod.mi_type != MODRM_MEMORY)
					break;
				nc_addr = x86_decode_modrmgetmem(state, &mod, op_flags);
				goto noncanon_write;

			case 0x8a:    /* MOV r8,r/m8 */
			case 0x8b:    /* MOV r16,r/m16; MOV r32,r/m32; MOV r64,r/m64 */
			case 0x8e:    /* MOV Sreg,r/m16** */
			case 0x0fbe:  /* movsx r/m8, r16 / movsx r/m8, r32 */
			case 0x0fbf:  /* movsx r/m16, r32 */
			case 0x0fb6:  /* movzx r/m8, r16 / movzx r/m8, r32 */
			case 0x0fb7:  /* movzx r/m16, r32 */
			case 0x63:    /* movsx r/m16, r16 / movsx r/m32, r32 / movsx r/m32, r64 */
			/* All of the following are technically read+write, but since the read comes first... */
			case 0x12:    /* adc r/m8, r8 */
			case 0x13:    /* adc r/m16, r16 / adc r/m32, r32 */
			case 0x02:    /* add r/m8, r8 */
			case 0x03:    /* add r/m16, r16 / add r/m32, r32 */
			case 0x22:    /* and r/m8, r8 */
			case 0x23:    /* and r/m16, r16 / and r/m32, r32 */
			case 0x6b:    /* imul $imm8, r/m16, %r16 / imul $imm8, r/m32, %r32 */
			case 0x69:    /* imul $imm16, r/m16, %r16 / imul $imm32, r/m32, %r32 */
			case 0x10:    /* adc r8, r/m8 */
			case 0x11:    /* adc r16, r/m16 / adc r32, r/m32 */
			case 0x00:    /* add r8, r/m8 */
			case 0x01:    /* add r16, r/m16 / add r32, r/m32 */
			case 0x20:    /* and r8, r/m8 */
			case 0x21:    /* and r16, r/m16 / and r32, r/m32 */
			case 0xc0:    /* rcl $imm8, r/m8 / rcr $imm8, r/m8
			               * rol $imm8, r/m8 / ror $imm8, r/m8
			               * sal $imm8, r/m8 / sar $imm8, r/m8
			               * shl $imm8, r/m8 / shr $imm8, r/m8 */
			case 0xc1:    /* rcl $imm8, r/m16 / rcl $imm8, r/m32 / rcr $imm8, r/m16 / rcr $imm8, r/m32
			               * rol $imm8, r/m16 / rol $imm8, r/m32 / ror $imm8, r/m16 / ror $imm8, r/m32
			               * sal $imm8, r/m16 / sal $imm8, r/m32 / sar $imm8, r/m16 / sar $imm8, r/m32
			               * shl $imm8, r/m16 / shl $imm8, r/m32 / shr $imm8, r/m16 / shr $imm8, r/m32 */
			case 0xf6:    /* div r/m8 / idiv r/m8 / mul r/m8 / imul r/m8 / neg r/m8 / not r/m8 */
			case 0xf7:    /* div r/m16 / div r/m32 / idiv r/m16 / idiv r/m32
			               * mul r/m16 / mul r/m32 / imul r/m16 / imul r/m32
			               * neg r/m16 / neg r/m32 / not r/m16 / not r/m32 */
			case 0xff:    /* call *r/m16 / call *r/m32 / dec r/m16 / dec r/m32 / inc r/m16 / inc r/m32
			               * jmp *r/m16 / jmp *r/m32 / ljmp m16 / ljmp m32 */
			case 0x38:    /* cmp r8, r/m8 */
			case 0x39:    /* cmp r16, r/m16 / cmp r32, r/m32 */
			case 0x3a:    /* cmp r/m8, r8 */
			case 0x3b:    /* cmp r/m16, r16 / cmp r/m32, r32 */
			case 0xfe:    /* dec r/m8 / inc r/m8 */
			 /* Floating point (st(i)-operations) prefix bytes */
			case 0xd8: case 0xd9: case 0xda: case 0xdb:
			case 0xdc: case 0xdd: case 0xde: case 0xdf:
			case 0xc5:    /* lds m16, r16 / lds m32, r32 */
			case 0xc4:    /* les m16, r16 / les m32, r32 */
			case 0x8d:    /* lea m, r16 / lea m, r32 */
			case 0x08:    /* or r8, r/m8 */
			case 0x09:    /* or r16, r/m16 / or r32, r/m32 */
			case 0x0a:    /* or r/m8, r8 */
			case 0x0b:    /* or r/m16, r16 / or r/m32, r32 */
			case 0x8f:    /* pop r/m16 / pop r/m32 */
			case 0xd0:    /* rcl r/m8 / rcr r/m8
			               * rol r/m8 / ror r/m8
			               * sal r/m8 / sar r/m8
			               * shl r/m8 / shr r/m8 */
			case 0xd1:    /* rcl r/m16 / rcl r/m32 / rcr r/m16 / rcr r/m32
			               * rol r/m16 / rol r/m32 / ror r/m16 / ror r/m32
			               * sal r/m16 / sal r/m32 / sar r/m16 / sar r/m32
			               * shl r/m16 / shl r/m32 / shr r/m16 / shr r/m32 */
			case 0xd2:    /* rcl %cl, r/m8 / rcr %cl, r/m8
			               * rol %cl, r/m8 / ror %cl, r/m8
			               * sal %cl, r/m8 / sar %cl, r/m8
			               * shl %cl, r/m8 / shr %cl, r/m8 */
			case 0xd3:    /* rcl %cl, r/m16 / rcl %cl, r/m32 / rcr %cl, r/m16 / rcr %cl, r/m32
			               * rol %cl, r/m16 / rol %cl, r/m32 / ror %cl, r/m16 / ror %cl, r/m32
			               * sal %cl, r/m16 / sal %cl, r/m32 / sar %cl, r/m16 / sar %cl, r/m32
			               * shl %cl, r/m16 / shl %cl, r/m32 / shr %cl, r/m16 / shr %cl, r/m32 */
			case 0x18:    /* sbb r8, r/m8 */
			case 0x19:    /* sbb r16, r/m16 / sbb r32, r/m32 */
			case 0x1a:    /* sbb r/m8, r8 */
			case 0x1b:    /* sbb r/m16, r16 / sbb r/m32, r32 */
			case 0x28:    /* sub r8, r/m8 */
			case 0x29:    /* sub r16, r/m16 / sub r32, r/m32 */
			case 0x2a:    /* sub r/m8, r8 */
			case 0x2b:    /* sub r/m16, r16 / sub r/m32, r32 */
			case 0x84:    /* test r8, r/m8 */
			case 0x85:    /* test r16, r/m16 / test r32, r/m32 */
			case 0x86:    /* xchg %r8, r/m8 / xchg r/m8, %r8 */
			case 0x87:    /* xchg %r16, r/m16 / xchg r/m16, %r16
			               * xchg %r32, r/m32 / xchg r/m32, %r32 */
			case 0x30:    /* xor r8, r/m8 */
			case 0x31:    /* xor r16, r/m16 / xor r32, r/m32 */
			case 0x32:    /* xor r/m8, r8 */
			case 0x33:    /* xor r/m16, r16 / xor r/m32, r32 */
			case 0x0f58:  /* addpd xmm2/m128, xmm1 */
			case 0x0fd0:  /* addsubpd xmm2/m128, xmm1 */
			case 0x0f54:  /* andpd xmm2/m128, xmm1 */
			case 0x0f55:  /* andnpd xmm2/m128, xmm1 */
			case 0x0fbc:  /* bsf r/m16, r16 */
			case 0x0fbd:  /* bsr r/m16, r16 */
			case 0x0fa3:  /* bt r16, r/m16 / bt r32, r/m32 */
			case 0x0fbb:  /* btc r16, r/m16 / btc r32, r/m32 */
			case 0x0fb3:  /* btr r16, r/m16 / btr r32, r/m32 */
			case 0x0fab:  /* bts r16, r/m16 / bts r32, r/m32 */
			case 0x0fb0:  /* cmpxch r8, r/m8 */
			case 0x0fb1:  /* cmpxch r16, r/m16 / cmpxch r32, r/m32 */
			case 0x0fc7:  /* cmpxchg8b m64 */
			case 0x0f2f:  /* comisd xmm2/m64, xmm1 */
			case 0x0fe6:  /* cvtdq2pd xmm2/m64, xmm1 */
			case 0x0f5b:  /* cvtdq2ps xmm2/m128, xmm1 */
			case 0x0f5a:  /* cvtpd2ps xmm2/m128, xmm1 / cvtsd2ss xmm2/m64, xmm1 */
			case 0x0f2a:  /* cvtpi2pd mm/m64, xmm */
			case 0x0f2d:  /* cvtps2pi xmm/m64, mm */
			case 0x0f2c:  /* cvttpd2pi xmm/m128, mm */
			case 0x0f5e:  /* divpd xmm2/m128, xmm1 */
			case 0x0f7c:  /* haddpd xmm2/m128, xmm1 / haddps xmm2/m128, xmm1 */
			case 0x0f7d:  /* hsubpd xmm2/m128, xmm1 / hsubps xmm2/m128, xmm1 */
			case 0x0faf:  /* imul r/m16, %r16 / imul r/m32, %r32 */
			case 0x0f02:  /* lar r/m16, r16 / lar r/m32, r32 */
			case 0x0ff0:  /* lddqu m128, xmm */
			case 0x0fb2:  /* lss m16, r16 / lss m32, r32 */
			case 0x0fb4:  /* lfs m16, r16 / lfs m32, r32 */
			case 0x0fb5:  /* lgs m16, r16 / lgs m32, r32 */
			case 0x0f00:  /* lldt r/m16 / ltr r/m16 / sldt r/m16 / str r/m16
			               * verr r/m16 / verw r/m16 */
			case 0x0f03:  /* lsl r/m16, %r16 / lsl r/m32, %r32 */
			case 0x0ff7:  /* maskmovdqu xmm2, xmm1 / maskmovq mm2, mm1 */
			case 0x0f5f:  /* maxpd xmm2/m128, xmm1 / maxps xmm2/m128, xmm1
			               * maxpd xmm2/m64, xmm1 / maxps xmm2/m64, xmm1 */
			case 0x0f5d:  /* minpd xmm2/m128, xmm1 / minps xmm2/m128, xmm1
			               * minpd xmm2/m64, xmm1 / minps xmm2/m64, xmm1 */
			case 0x0f28:  /* movapd xmm1, xmm2/m128 / movaps xmm1, xmm2/m128 */
			case 0x0f7e:  /* movd mm, r/m32  / movd xmm, r/m32
			               * movq xmm/m64, xmm */
			case 0x0f13:  /* movlpd xmm, m64 / movlps xmm, m64 */
			case 0x0f7f:  /* movdqa xmm1, xmm2/m128 / movdqu xmm1, xmm2/m128
			               * movq mm, mm/m64 */
			case 0x0fd6:  /* movdq2q xmm, mm / movq xmm, xmm/m64 / movq2dq mm, xmm */
			case 0x0f16:  /* movhpd m64, xmm / movhps m64, xmm / movlhps xmm2, xmm1 / movshdup xmm2/m128, xmm1 */
			case 0x0f17:  /* movhpd xmm, m64 / movhps xmm, m64 */
			case 0x0f50:  /* movmskpd xmm, r32 / movmskps xmm, r32 */
			case 0x0fe7:  /* movntdq xmm, m128 / movntq mm, m64 */
			case 0x0f2b:  /* movntpd xmm, m128 / movntps xmm, m128 */
			case 0x0f10:  /* movsd xmm2/m64, xmm1 / movss xmm2/m32, xmm1
			               * movapd xmm2/m128, xmm1 / movups xmm2/m128, xmm1 */
			case 0x0f11:  /* movsd xmm1, xmm2/m64 / movss xmm1, xmm2/m32
			               * movapd xmm1, xmm2/m128 / movups xmm1, xmm2/m128 */
			case 0x0f59:  /* mulpd xmm2/m128, xmm1 / mulps xmm2/m128, xmm1
			               * mulsd xmm2/m64, xmm1 / mulss xmm2/m64, xmm1 */
			case 0x0f56:  /* orpd xmm2/m128, xmm1 / orps xmm2/m128, xmm1 */
			case 0x0f63:  /* packsswb mm2/m64, mm1 / packsswb xmm2/m128, xmm1 */
			case 0x0f6b:  /* packssdw mm2/m64, mm1 / packssdw xmm2/m128, xmm1 */
			case 0x0f67:  /* packuswb mm2/m64, mm1 / packuswb xmm2/m128, xmm1 */
			case 0x0ffc:  /* paddb mm2/m64, mm1 / paddb xmm2/m128, xmm1 */
			case 0x0ffd:  /* paddw mm2/m64, mm1 / paddw xmm2/m128, xmm1 */
			case 0x0ffe:  /* paddl mm2/m64, mm1 / paddl xmm2/m128, xmm1 */
			case 0x0fd4:  /* paddq mm2/m64, mm1 / paddq xmm2/m128, xmm1 */
			case 0x0fec:  /* paddsb mm2/m64, mm1 / paddsb xmm2/m128, xmm1 */
			case 0x0fed:  /* paddsw mm2/m64, mm1 / paddsw xmm2/m128, xmm1 */
			case 0x0fdc:  /* paddusb mm2/m64, mm1 / paddusb xmm2/m128, xmm1 */
			case 0x0fdd:  /* paddusw mm2/m64, mm1 / paddusw xmm2/m128, xmm1 */
			case 0x0fdb:  /* pand mm2/m64, mm1 / pand xmm2/m128, xmm1 */
			case 0x0fdf:  /* pandn mm2/m64, mm1 / pandn xmm2/m128, xmm1 */
			case 0x0fe0:  /* pavgbb mm2/m64, mm1 / pavgbb xmm2/m128, xmm1 */
			case 0x0fe3:  /* pavgbw mm2/m64, mm1 / pavgbw xmm2/m128, xmm1 */
			case 0x0f74:  /* pcmpeqb mm2/m64, mm1 / pcmpeqb xmm2/m128, xmm1 */
			case 0x0f75:  /* pcmpeqw mm2/m64, mm1 / pcmpeqw xmm2/m128, xmm1 */
			case 0x0f76:  /* pcmpeql mm2/m64, mm1 / pcmpeql xmm2/m128, xmm1 */
			case 0x0f64:  /* pcmpgtb mm2/m64, mm1 / pcmpgtb xmm2/m128, xmm1 */
			case 0x0f65:  /* pcmpgtw mm2/m64, mm1 / pcmpgtw xmm2/m128, xmm1 */
			case 0x0f66:  /* pcmpgtl mm2/m64, mm1 / pcmpgtl xmm2/m128, xmm1 */
			case 0x0ff5:  /* pmaddwd mm2/m64, mm1 / pmaddwd xmm2/m128, xmm1 */
			case 0x0fee:  /* pmaxsw mm2/m64, mm1 / pmaxsw xmm2/m128, xmm1 */
			case 0x0fde:  /* pmaxub mm2/m64, mm1 / pmaxub xmm2/m128, xmm1 */
			case 0x0fea:  /* pminsw mm2/m64, mm1 / pminsw xmm2/m128, xmm1 */
			case 0x0fda:  /* pminub mm2/m64, mm1 / pminub xmm2/m128, xmm1 */
			case 0x0fd7:  /* pmovmskb r32, mm1 / pmovmskb r32, xmm1 */
			case 0x0fe4:  /* pmulhuw mm2/m64, mm1 / pmulhuw xmm2/m128, xmm1 */
			case 0x0fe5:  /* pmulhw mm2/m64, mm1 / pmulhw xmm2/m128, xmm1 */
			case 0x0fd5:  /* pmullw mm2/m64, mm1 / pmullw xmm2/m128, xmm1 */
			case 0x0ff4:  /* pmuludq mm2/m64, mm1 / pmuludq xmm2/m128, xmm1 */
			case 0x0feb:  /* por mm2/m64, mm1 / por xmm2/m128, xmm1 */
			case 0x0f18:  /* prefetcht(0|1|2: m8 / prefetchnta m8 */
			case 0x0ff6:  /* psadbw mm2/m64, mm1 / psadbw xmm2/m128, xmm1 */
			case 0x0ff1:  /* psllw mm2/m64, mm1 / psllw xmm2/m128, xmm1 */
			case 0x0ff2:  /* pslld mm2/m64, mm1 / pslld xmm2/m128, xmm1 */
			case 0x0ff3:  /* psllq mm2/m64, mm1 / psllq xmm2/m128, xmm1 */
			case 0x0fe1:  /* psraw mm2/m64, mm1 / psraw xmm2/m128, xmm1 */
			case 0x0fe2:  /* psrad mm2/m64, mm1 / psrad xmm2/m128, xmm1 */
			case 0x0fd1:  /* psrlw mm2/m64, mm1 / psrlw xmm2/m128, xmm1 */
			case 0x0fd2:  /* psrld mm2/m64, mm1 / psrld xmm2/m128, xmm1 */
			case 0x0fd3:  /* psrlq mm2/m64, mm1 / psrlq xmm2/m128, xmm1 */
			case 0x0ff8:  /* psubb mm2/m64, mm1 / psubb xmm2/m128, xmm1 */
			case 0x0ff9:  /* psubw mm2/m64, mm1 / psubw xmm2/m128, xmm1  */
			case 0x0ffa:  /* psubd mm2/m64, mm1 / psubd xmm2/m128, xmm1  */
			case 0x0ffb:  /* psubq mm2/m64, mm1 / psubq xmm2/m128, xmm1  */
			case 0x0fe8:  /* psubsb mm2/m64, mm1 / psubsb xmm2/m128, xmm1 */
			case 0x0fe9:  /* psubsw mm2/m64, mm1 / psubsw xmm2/m128, xmm1 */
			case 0x0fd8:  /* psubusb mm2/m64, mm1 / psubusb xmm2/m128, xmm1 */
			case 0x0fd9:  /* psubusw mm2/m64, mm1 / psubusw xmm2/m128, xmm1 */
			case 0x0f68:  /* punpckhbw mm2/m64, mm1 / punpckhbw xmm2/m128, xmm1 */
			case 0x0f69:  /* punpckhbd mm2/m64, mm1 / punpckhbd xmm2/m128, xmm1 */
			case 0x0f6a:  /* punpckhbq mm2/m64, mm1 / punpckhbq xmm2/m128, xmm1 */
			case 0x0f6d:  /* punpckhqdq xmm2/m128, xmm1 */
			case 0x0f60:  /* punpcklbw mm2/m64, mm1 / punpcklbw xmm2/m128, xmm1 */
			case 0x0f61:  /* punpcklbd mm2/m64, mm1 / punpcklbd xmm2/m128, xmm1 */
			case 0x0f62:  /* punpcklbq mm2/m64, mm1 / punpcklbq xmm2/m128, xmm1 */
			case 0x0f6c:  /* punpcklqdq xmm2/m128, xmm1 */
			case 0x0fef:  /* pxor mm2/m64, mm1 / pxor xmm2/m128, xmm1 */
			case 0x0f53:  /* rcpps xmm2/m128, xmm1 / rcpss xmm2/m32, xmm1 */
			case 0x0f52:  /* rsqrtps xmm2/m128, xmm1 / rsqrtss xmm2/m128, xmm1 */
			case 0x0fa5:  /* shld %cl, %r16, r/m16 / shld %cl, %r32, r/m32 */
			case 0x0fad:  /* shrd %cl, %r16, r/m16 / shrd %cl, %r32, r/m32 */
			case 0x0f51:  /* sqrtpd xmm2/m128, xmm1 / sqrtps xmm2/m128, xmm1
			               * sqrtsd xmm2/m64, xmm1 / sqrtss xmm2/m32, xmm1 */
			case 0x0f5c:  /* subpd xmm2/m128, xmm1 / subps xmm2/m128, xmm1
			               * subsd xmm2/m64, xmm1 / subss xmm2/m32, xmm1 */
			case 0x0f2e:  /* ucomisd xmm2/m64, xmm1 / ucomiss xmm2/m64, xmm1 */
			case 0x0f15:  /* unpckhpd xmm2/m128, xmm1 / unpckhps xmm2/m128, xmm1 */
			case 0x0f14:  /* unpcklpd xmm2/m128, xmm1 / unpcklps xmm2/m128, xmm1 */
			case 0x0fc0:  /* xadd %r8, r/m8 */
			case 0x0fc1:  /* xadd %r16, r/m16 / xadd %r32, r/m32 */
			case 0x0f57:  /* xorpd xmm2/m128, xmm1 / xorps xmm2/m128, xmm1 */
			case 0x0fc5:  /* pextrw $imm8, mm, r32 / pextrw $imm8, xmm, r32 */
			case 0x0fc4:  /* pinsrw $imm8, r/m32, mm / pinsrw $imm8, r/m32, xmm */
			case 0x0f70:  /* pshufw $imm8, mm2/m64, mm1 / pshufd $imm8, xmm2/m128, xmm1
			               * pshufhw $imm8, xmm2/m128, xmm1 / pshuflw $imm8, xmm2/m128, xmm1 */
			case 0x0f71:  /* psllw $imm8, mm / psllw $imm8, xmm
			               * psraw $imm8, mm1 / psraw $imm8, xmm1
			               * psrlw $imm8, mm / psrlw $imm8, xmm */
			case 0x0f72:  /* pslld $imm8, mm1 / pslld $imm8, xmm1
			               * psrad $imm8, mm1 / psrad $imm8, xmm1
			               * psrld $imm8, mm1 / psrld $imm8, xmm1 */
			case 0x0f73:  /* psllq $imm8, mm1 / psllq $imm8, xmm1
			               * pslldq $imm8, xmm1 / psrldq $imm8, xmm1
			               * psrlq $imm8, mm1 / psrlq $imm8, xmm1 */
			case 0x0fa4:  /* shld $imm8, %r16, r/m16 / shld $imm8, %r32, r/m32 */
			case 0x0fac:  /* shrd $imm8, %r16, r/m16 / shrd $imm8, %r32, r/m32 */
			case 0x0fc6:  /* shufpd $imm8, xmm2/m128, xmm1 / shufps $imm8, xmm2/m128, xmm1 */
			case 0x0fba:  /* bt $imm8, r/m16 / bt $imm8, r/m32
			               * btc $imm8, r/m16 / btc $imm8, r/m32
			               * bts $imm8, r/m16 / bts $imm8, r/m32
			               * btr $imm8, r/m16 / btr $imm8, r/m32 */
			case 0x0fc2:  /* cmppd $imm8, xmm2/m128, xmm1 */
			case 0x0f3882:/* invpcid r32/r64, m128 */
				MOD_DECODE();
				if (mod.mi_type != MODRM_MEMORY)
					break;
				nc_addr = x86_decode_modrmgetmem(state, &mod, op_flags);
				goto noncanon_read;

			case 0xa0:  /* MOV AL,moffs8* */
				nc_addr = *(u8 *)pc;
				pc += 1;
				nc_addr += x86_decode_segmentbase(state, op_flags);
				goto noncanon_read;
			case 0xa1: /* MOV AX,moffs16*; MOV EAX,moffs32*; MOV RAX,moffs64* */
				if (op_flags & F_AD64) {
					nc_addr = *(u64 *)pc;
					pc += 8;
				} else {
					nc_addr = *(u32 *)pc;
					pc += 4;
				}
				nc_addr += x86_decode_segmentbase(state, op_flags);
				goto noncanon_read;

			case 0x0f01: /* invlpg m / lgdt m48 / lidt m48 / lmsw r/m16
			              * monitor / mwait / sgdt m48 / sidt m48
			              * smsw r/m16 / smsw r32/m16 */
				MOD_DECODE();
				if (mod.mi_type != MODRM_MEMORY)
					break;
				nc_addr = x86_decode_modrmgetmem(state, &mod, op_flags);
				if (mod.mi_reg == 0)
					goto noncanon_write; /* sgdt */
				if (mod.mi_reg == 1)
					goto noncanon_write; /* sidt */
				if (mod.mi_reg == 4)
					goto noncanon_write; /* smsw */
				goto noncanon_read;

			case 0x0fae: /* clflush m8 / fxrstor m512byte / fxsave m512byte
			              * ldmxcsr m32 / lfence / mfence / sfence
			              * stmxcsr m32 */
				MOD_DECODE();
				if (mod.mi_type != MODRM_MEMORY)
					break;
				nc_addr = x86_decode_modrmgetmem(state, &mod, op_flags);
				if (mod.mi_reg == 1)
					goto noncanon_write; /* fxrstor */
				if (mod.mi_reg == 2)
					goto noncanon_write; /* ldmxcsr */
				goto noncanon_read;

			case 0xa2: /* MOV moffs8*,AL */
				nc_addr = *(u8 *)pc;
				pc += 1;
				nc_addr += x86_decode_segmentbase(state, op_flags);
				goto noncanon_write;
			case 0xa3: /* MOV moffs16*,AX; MOV moffs32*,EAX; MOV moffs64*,RAX */
				if (op_flags & F_AD64) {
					nc_addr = *(u64 *)pc;
					pc += 8;
				} else {
					nc_addr = *(u32 *)pc;
					pc += 4;
				}
				nc_addr += x86_decode_segmentbase(state, op_flags);
				goto noncanon_write;

			case 0xac: /* lodsb */
			case 0xad: /* lodsw / lodsl / lodsq */
			case 0x6e: /* outsb */
			case 0x6f: /* outsw / outsl / outsq */
				nc_addr = state->ics_gpregs.gp_rsi;
				goto noncanon_read;

			case 0x6c: /* insb */
			case 0x6d: /* insw / insl / insq */
			case 0xaa: /* stosb */
			case 0xab: /* stosw / stosl / stosq */
			case 0xae: /* scasb */
			case 0xaf: /* scasw / scasl / scasq */
				nc_addr = state->ics_gpregs.gp_rdi;
				goto noncanon_write;

			case 0xa4: /* movsb */
				/* Check for special case: `memcpy_nopf()' was used with non-canonical pointers.
				 * In this case, we mustn't throw an exception (or even clobber exception pointers),
				 * but instead have to directly resume execution at `x86_memcpy_nopf_ret_pointer' */
				if (orig_pc == x86_memcpy_nopf_rep_pointer) {
					icpustate64_setrip(state, (uintptr_t)x86_memcpy_nopf_ret_pointer);
					return state;
				}
				ATTR_FALLTHROUGH
			case 0xa5: /* movsw / movsl / movsq */
				nc_addr = state->ics_gpregs.gp_rsi;
				if (ADDR_IS_NONCANON(nc_addr) ||
				    ADDR_IS_NONCANON(nc_addr + 8))
					goto noncanon_read;
				nc_addr = state->ics_gpregs.gp_rdi;
				goto noncanon_write;

			default: break;
			}
			__IF0 {
noncanon_read:
				if (!ADDR_IS_NONCANON(nc_addr) && !ADDR_IS_NONCANON(nc_addr + 8))
					goto done_noncanon_check;
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_SEGFAULT_CONTEXT_NONCANON);
				goto do_noncanon;
noncanon_write:
				if (!ADDR_IS_NONCANON(nc_addr) && !ADDR_IS_NONCANON(nc_addr + 8))
					goto done_noncanon_check;
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_SEGFAULT_CONTEXT_NONCANON | E_SEGFAULT_CONTEXT_WRITING);
do_noncanon:
				PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_UNMAPPED));
				PERTASK_SET(this_exception_pointers[0], (uintptr_t)nc_addr);
				if (isuser()) {
					PERTASK_SET(this_exception_pointers[1],
					            (uintptr_t)PERTASK_GET(this_exception_pointers[1]) |
					            E_SEGFAULT_CONTEXT_USERCODE);
				}
				for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
					PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
				printk(KERN_DEBUG "[segfault] Fault at %p [pc=%p,%p] [#GPF] [tid=%u]\n",
				       nc_addr, orig_pc, pc, (unsigned int)task_getroottid_s());
				goto unwind_state;
			}
done_noncanon_check:
			pc = pc_after_opcode;
		}
#endif /* __x86_64__ */

		/* Check for #GP caused by privileged instructions or illegal registers */
		switch (opcode) {

#ifdef __x86_64__
			/* Because the default #GPF cause assumption on x86_64 is a non-canonical
			 * memory access, all #GPF causes related to privileged instructions must
			 * be checked for explicitly. */
		case 0x6e: /* outsb */
		case 0x6f: /* outsw / outsl / outsq */
		case 0x6c: /* insb */
		case 0x6d: /* insw / insl / insq */
		case 0xec: /* inb */
		case 0xed: /* inw / inl */
		case 0xee: /* outb */
		case 0xef: /* outw / outl */
		case 0xfa: /* cli */
		case 0xfb: /* sti */
		case 0x0f06: /* clts */
		case 0xf4: /* hlt */
		case 0xcc: /* int3 (shouldn't appear here) */
		case 0xce: /* into (shouldn't appear here) */
		case 0xf1: /* int1 */
		case 0x0f35: /* sysexit */
		case 0x0f07: /* sysret */
		case 0x0f08: /* invd */
		case 0x0f09: /* wbinvd */
			goto generic_privileged_instruction_if_user;
		case 0xe4: /* inb */
		case 0xe5: /* inw / inl */
		case 0xe6: /* outb */
		case 0xe7: /* outw / outl */
		case 0xcd: /* int $n */
			pc += 1;
			goto generic_privileged_instruction_if_user;
		case 0x0f3882: /* invpcid */
			MOD_DECODE();
			goto generic_privileged_instruction_if_user;

#endif /* __x86_64__ */


		case 0x9a: {
			u16 segment;
			u32 offset;
			/* CALL ptr16:16 D Invalid Valid Call far, absolute, address given in operand.
			 * CALL ptr16:32 D Invalid Valid Call far, absolute, address given in operand. */
#ifdef __x86_64__
			/* This instruction only exists in compatibility mode! */
			if (!(op_flags & F_IS_X32))
				goto unsupported_instruction;
#endif /* __x86_64__ */
			if (op_flags & F_OP16) {
				offset = UNALIGNED_GET16((u16 *)pc);
				pc += 2;
			} else {
				offset = UNALIGNED_GET32((u32 *)pc);
				pc += 4;
			}
			segment = UNALIGNED_GET16((u16 *)pc);
			pc += 2;
			/* Invalid use of the lcall instruction. */
			PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_pointers[0], (uintptr_t)opcode);
			PERTASK_SET(this_exception_pointers[1],
			            !(segment & 3) && !isuser()
			            ? (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV
			            : (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
			PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_CS);
			PERTASK_SET(this_exception_pointers[3], (uintptr_t)segment);
			PERTASK_SET(this_exception_pointers[4], (uintptr_t)offset);
			for (i = 5; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
		}	goto unwind_state;


		case 0xff:
			MOD_DECODE();
			if (mod.mi_reg == 3 && mod.mi_type == MODRM_MEMORY) {
				u16 segment;
				uintptr_t offset;
				byte_t *addr;
				addr = (byte_t *)x86_decode_modrmgetmem(state, &mod, op_flags);
				if (isuser())
					validate_readable(addr, 1);
#ifdef __x86_64__
				if (op_flags & F_REX_W) {
					segment = UNALIGNED_GET16((u16 *)(addr + 0));
					offset  = UNALIGNED_GET64((u64 *)(addr + 2));
				} else
#endif /* __x86_64__ */
				if (!(op_flags & F_OP16)) {
					segment = UNALIGNED_GET16((u16 *)(addr + 0));
					offset  = UNALIGNED_GET32((u32 *)(addr + 2));
				} else {
					segment = UNALIGNED_GET16((u16 *)(addr + 0));
					offset  = UNALIGNED_GET16((u16 *)(addr + 2));
				}
				/* Invalid use of the lcall instruction. */
				PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
				PERTASK_SET(this_exception_pointers[0],
				            E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
				PERTASK_SET(this_exception_pointers[1],
				            !(segment & 3) && !isuser()
				            ? (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV
				            : (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
				PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_CS);
				PERTASK_SET(this_exception_pointers[3], (uintptr_t)segment);
				PERTASK_SET(this_exception_pointers[4], (uintptr_t)offset);
				for (i = 5; i < EXCEPTION_DATA_POINTERS; ++i)
					PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
				goto unwind_state;
			}
			goto generic_failure;

		case 0x0fae:
			MOD_DECODE();
			switch (mod.mi_reg) {

			case 2:
				if (mod.mi_type == MODRM_MEMORY) {
					/* ldmxcsr m32 (attempted to set a reserved bit) */
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
					PERTASK_SET(this_exception_pointers[0], E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
					PERTASK_SET(this_exception_pointers[1], (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
					PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_MISC_MXCSR);
					PERTASK_SET(this_exception_pointers[3], (uintptr_t)RD_RML());
					for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
						PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
					goto unwind_state;
				}
#ifdef __x86_64__
				else {
					/* F3       0F AE /2 WRFSBASE r32     Load the FS base address with the 32-bit value in the source register.
					 * F3 REX.W 0F AE /2 WRFSBASE r64     Load the FS base address with the 64-bit value in the source register. */
					goto check_x86_64_noncanon_fsgsbase;
				}
#endif /* __x86_64__ */
				break;

#ifdef __x86_64__
			case 3:
				if (mod.mi_type == MODRM_REGISTER) {
					/* F3       0F AE /3 WRGSBASE r32     Load the GS base address with the 32-bit value in the source register.
					 * F3 REX.W 0F AE /3 WRGSBASE r64     Load the GS base address with the 64-bit value in the source register. */
check_x86_64_noncanon_fsgsbase:
					/* The wr(fs|gs)base instructions will raise #GF if the operand is a non-canonical pointer. */
					if (op_flags & F_REX_W) {
						u64 nc_addr = RD_RMREGQ();
						if (ADDR_IS_NONCANON(nc_addr)) {
							printk(KERN_DEBUG "[segfault] Non-canonical wr%csbase with %p [pc=%p,%p] [#GPF] [tid=%u]\n",
							       mod.mi_reg == 2 ? 'f' : 'g', nc_addr,
							       orig_pc, pc, (unsigned int)task_getroottid_s());
							PERTASK_SET(this_exception_pointers[0], (uintptr_t)nc_addr);
							goto set_x86_64_non_canon_special;
						}
					} else {
						/* 32-bit operand can never be non-canonical */
					}
				}
				break;
#endif /* __x86_64__ */


#ifdef __x86_64__
			case 5: /* xrstor */
				goto generic_privileged_instruction_if_user;

			case 6: /* tpause */
				goto generic_privileged_instruction_if_user;
#endif /* __x86_64__ */

			default:
				break;
			}
			goto generic_failure;

#ifdef __x86_64__
		case 0x0fc3:
			MOD_DECODE();
			if (mod.mi_reg == 3) /* xrstors */
				goto generic_privileged_instruction_if_user;
			goto generic_failure;
#endif /* __x86_64__ */

		case 0x0f22:
			/* MOV CRx,r32 */
			MOD_DECODE();
			for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
			PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_pointers[0], E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
			PERTASK_SET(this_exception_pointers[2], (uintptr_t)(X86_REGISTER_CONTROL + mod.mi_reg));
			PERTASK_SET(this_exception_pointers[3], (uintptr_t)RD_REG());
#ifdef __x86_64__
			if (mod.mi_reg == 1 || (mod.mi_reg > 4 && mod.mi_reg != 8))
#else /* __x86_64__ */
			if (mod.mi_reg == 1 || mod.mi_reg > 4)
#endif /* !__x86_64__ */
			{
				/* Error was caused because CR* doesn't exist */
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRINV);
			} else if (isuser()) {
				/* Error was caused because CR* are privileged */
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV);
			} else {
				/* Error was caused because value written must be invalid. */
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
			}
			goto unwind_state;


		case 0x0f20:
			/* MOV r32,CRx */
			MOD_DECODE();
			for (i = 3; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
			PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_pointers[0], E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
			PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_CONTROL + mod.mi_reg);
#ifdef __x86_64__
			if (mod.mi_reg == 1 || (mod.mi_reg > 4 && mod.mi_reg != 8))
#else /* __x86_64__ */
			if (mod.mi_reg == 1 || mod.mi_reg > 4)
#endif /* !__x86_64__ */
			{
				/* Undefined control register. */
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDINV);
			} else {
				/* Userspace tried to read from an control register. */
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV);
			}
			goto unwind_state;


		case 0x0f21:
		case 0x0f23:
			/* MOV r32, DR0-DR7 */
			/* MOV DR0-DR7, r32 */
			MOD_DECODE();
			/* Userspace tried to access an control register. */
			for (i = 3; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
			PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_pointers[0], E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
			PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_CONTROL + mod.mi_reg);
			if (opcode == 0x0f23) {
				/* Save the value user-space tried to write. */
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV);
				PERTASK_SET(this_exception_pointers[3],
				            (uintptr_t)RD_REG());
			} else {
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV);
			}
			break;


		case 0x0f00:
			MOD_DECODE();
			if (effective_segment_value == 0)
				goto null_segment_error;
			PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_pointers[0],
			            E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
			for (i = 3; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_pointers[i],
				            (uintptr_t)0);
			if (mod.mi_reg == 3) {
				/* LTR r/m16 */
				PERTASK_SET(this_exception_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_TR);
			} else if (mod.mi_reg == 2) {
				/* LLDT r/m16 */
				PERTASK_SET(this_exception_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_LDT);
			} else if (mod.mi_reg == 0) {
				/* SLDT r/m16 */
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV);
				PERTASK_SET(this_exception_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_LDT);
				goto unwind_state;
			} else {
				goto generic_failure;
			}
			PERTASK_SET(this_exception_pointers[3], (uintptr_t)RD_RMW());
			if (ecode != 0 && !isuser()) {
				/* Invalid operand for this opcode. */
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
			} else {
				/* User-space use of a privileged instruction. */
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV);
			}
			goto unwind_state;


		case 0x0f01:
			MOD_DECODE();
			if (effective_segment_value == 0)
				goto null_segment_error;
			PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_pointers[0],
			            E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
			for (i = 3; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_pointers[i],
				            (uintptr_t)0);
			if (mod.mi_reg == 2) {
				/* LGDT m16&32 */
				PERTASK_SET(this_exception_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_GDT_BASE);
			} else if (mod.mi_reg == 3) {
				/* LIDT m16&32 */
				PERTASK_SET(this_exception_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_IDT_BASE);
			} else if (mod.mi_reg == 0) {
				/* SGDT r/m16 */
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV);
				PERTASK_SET(this_exception_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_GDT_BASE);
				goto unwind_state;
			} else if (mod.mi_reg == 1) {
				/* SIDT r/m16 */
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV);
				PERTASK_SET(this_exception_pointers[2],
				            (uintptr_t)X86_REGISTER_MISC_IDT_BASE);
				goto unwind_state;
			} else if (mod.mi_reg == 4) {
				/* SMSW r/m16 */
				/* SMSW r/m32 */
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV);
				PERTASK_SET(this_exception_pointers[2],
				            (uintptr_t)X86_REGISTER_CONTROL_CR0);
				goto unwind_state;
			} else if (mod.mi_reg == 6) {
				/* LMSW r/m16 */
				PERTASK_SET(this_exception_pointers[1],
				            isuser() ? (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV
				                     : (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
				PERTASK_SET(this_exception_pointers[2],
				            (uintptr_t)X86_REGISTER_CONTROL_CR0);
				PERTASK_SET(this_exception_pointers[3],
				            (uintptr_t)RD_RMW());
				goto unwind_state;
#ifdef __x86_64__
			} else if (mod.mi_reg) {
				/* TODO: 0x0f01c8: monitor */
				/* TODO: 0x0f01c9: mwait */
				/* TODO: 0x0f01f8: swapgs */
				/* TODO: 0x0f01ef: wrpkru */
				/* TODO: 0x0f01d0: xgetbv */
				/* TODO: 0x0f01d1: xsetbv */
#endif /* __x86_64__ */
			} else {
				goto generic_failure;
			}
			/* LGDT m16&32 */
			/* LIDT m16&32 */
			if (mod.mi_type != MODRM_MEMORY) {
				PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND));
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE);
				for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
					PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
				goto unwind_state;
			}
			{
				u8 buf[2 + sizeof(uintptr_t)];
				byte_t *addr = (byte_t *)x86_decode_modrmgetmem(state, &mod, op_flags);
				if (isuser()) {
					validate_readable(addr, sizeof(buf));
					PERTASK_SET(this_exception_pointers[1],
					            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV);
				} else {
					PERTASK_SET(this_exception_pointers[1],
					            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
				}
				memcpy(buf, addr, sizeof(buf));
				PERTASK_SET(this_exception_pointers[3], (uintptr_t)*(u16 *)(buf + 0));
				PERTASK_SET(this_exception_pointers[4], *(uintptr_t *)(buf + 2));
			}
			goto unwind_state;

		case 0x8c:
			/* MOV r/m16,Sreg** */
			MOD_DECODE();
			if (mod.mi_reg >= 6) {
				/* Non-existent segment register */
				PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
				PERTASK_SET(this_exception_pointers[0], E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
				PERTASK_SET(this_exception_pointers[1], (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDINV);
				PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_ES + mod.mi_reg);
				for (i = 3; i < EXCEPTION_DATA_POINTERS; ++i)
					PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
				goto unwind_state;
			}
			goto generic_failure;

		case 0x8e:
			/* MOV Sreg**,r/m16 */
			MOD_DECODE();
			PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_pointers[0], E_ILLEGAL_INSTRUCTION_X86_OPCODE(opcode, mod.mi_reg));
			PERTASK_SET(this_exception_pointers[1], (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
			PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_ES + mod.mi_reg);
			PERTASK_SET(this_exception_pointers[3], (uintptr_t)RD_RMW());
			for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
			/* Invalid segment index. */
			if (mod.mi_reg > 5) {
				/* Non-existent segment register */
				PERTASK_SET(this_exception_pointers[1],
				            (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRINV);
			}
			goto unwind_state;

		case 0x0f31: /* rdtsc */
		case 0x0f32: /* rdmsr */
		case 0x0f33: /* rdpmc */
			PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_pointers[0], (uintptr_t)opcode);
			PERTASK_SET(this_exception_pointers[1],
			            isuser() ? (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV
			                     : (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_RDINV);
			PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_MSR);
			PERTASK_SET(this_exception_pointers[3], (uintptr_t)(u32)gpregs_getpcx(&state->ics_gpregs));
			if (opcode == 0x0f31) {
				PERTASK_SET(this_exception_pointers[3],
				            (uintptr_t)IA32_TIME_STAMP_COUNTER);
			}
			for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
			goto unwind_state;

		case 0x0f30: /* wrmsr */
#ifdef __x86_64__
			/* A couple of MSR registers can throw #GP if the written value
			 * is a non-canonical pointer. Since KOS throws `E_SEGFAULT' for
			 * this case, manually check if we're dealing with one of these MSRs,
			 * and the written value is such a pointer.
			 * s.a. Intel instruction set reference for `WRMSR' (Vol. 2C) */
			if ((u32)gpregs_getpcx(&state->ics_gpregs) == IA32_DS_AREA ||
			    (u32)gpregs_getpcx(&state->ics_gpregs) == IA32_FS_BASE ||
			    (u32)gpregs_getpcx(&state->ics_gpregs) == IA32_GS_BASE ||
			    (u32)gpregs_getpcx(&state->ics_gpregs) == IA32_KERNEL_GS_BASE ||
			    (u32)gpregs_getpcx(&state->ics_gpregs) == IA32_LSTAR ||
			    (u32)gpregs_getpcx(&state->ics_gpregs) == IA32_SYSENTER_EIP ||
			    (u32)gpregs_getpcx(&state->ics_gpregs) == IA32_SYSENTER_ESP) {
				u64 nc_addr;
				nc_addr = ((u64)(u32)gpregs_getpax(&state->ics_gpregs)) |
				          ((u64)(u32)gpregs_getpdx(&state->ics_gpregs) << 32);
				if (ADDR_IS_NONCANON(nc_addr)) {
					PERTASK_SET(this_exception_pointers[0], (uintptr_t)nc_addr);
					printk(KERN_DEBUG "[segfault] Non-canonical write to msr#%#I32x with %p [pc=%p,%p] [#GPF] [tid=%u]\n",
					       (u32)gpregs_getpcx(&state->ics_gpregs), nc_addr,
					       orig_pc, pc, (unsigned int)task_getroottid_s());
set_x86_64_non_canon_special:
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_UNMAPPED));
					PERTASK_SET(this_exception_pointers[1], (uintptr_t)E_SEGFAULT_CONTEXT_NONCANON);
					if (isuser()) {
						PERTASK_SET(this_exception_pointers[1],
						            (uintptr_t)(E_SEGFAULT_CONTEXT_NONCANON |
						                        E_SEGFAULT_CONTEXT_USERCODE));
					}
					for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
						PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
					goto unwind_state;
				}
			}
#endif /* __x86_64__ */
			PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
			PERTASK_SET(this_exception_pointers[0], (uintptr_t)opcode);
			PERTASK_SET(this_exception_pointers[1],
			            isuser() ? (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV
			                     : (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRINV);
			PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_MSR);
			PERTASK_SET(this_exception_pointers[3], (uintptr_t)(u32)gpregs_getpcx(&state->ics_gpregs));
			PERTASK_SET(this_exception_pointers[4], (uintptr_t)(u32)gpregs_getpax(&state->ics_gpregs));
			PERTASK_SET(this_exception_pointers[5], (uintptr_t)(u32)gpregs_getpdx(&state->ics_gpregs));
			goto unwind_state;

		default: {
			void const *next_pc;
#ifdef __x86_64__
unsupported_instruction:
#endif /* __x86_64__ */
			next_pc = instruction_succ(orig_pc);
			if (next_pc)
				pc = (byte_t *)next_pc;
			goto generic_failure;
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
	icpustate_setpc(state, (uintptr_t)pc);
	return state;
generic_failure:
	/* Fallback: Choose between a NULL-segment and generic error. */
	if (!effective_segment_value) {
null_segment_error:
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER));
		PERTASK_SET(this_exception_pointers[0], (uintptr_t)opcode);
		PERTASK_SET(this_exception_pointers[1], (uintptr_t)E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD);
		PERTASK_SET(this_exception_pointers[3], (uintptr_t)effective_segment_value);
		for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
		switch (op_flags & F_SEGMASK) {
		default:      PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_DS); break;
		case F_SEGFS: PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_FS); break;
		case F_SEGGS: PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_GS); break;
#ifndef __x86_64__
		case F_SEGES: PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_ES); break;
		case F_SEGCS: PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_CS); break;
		case F_SEGSS: PERTASK_SET(this_exception_pointers[2], (uintptr_t)X86_REGISTER_SEGMENT_SS); break;
#endif /* !__x86_64__ */
		}
		goto unwind_state;
	}
#ifdef __x86_64__
	/* On x86_64, a #GPF is thrown when attempting to access a non-canonical address.
	 * However, the kernel expects that the only exception that might be thrown when
	 * accessing some unchecked pointer is an E_SEGFAULT.
	 * Code above tries to inspect the source instruction to determine the faulting
	 * memory address. However there are literally thousands of different X86
	 * instructions that take a memory operand, and we can only know about so many
	 * before we run into one that may not even have existed at the time this
	 * decoder was written.
	 * So despite the fact that we haven't managed to figure out the faulting memory
	 * address, simply assume that a segment selector of ZERO(0) is indicative of a
	 * instruction that tried to access a non-canonical address.
	 * In this case, we set the first non-canonical address as faulting address.
	 * Also: we don't know if it was a write that caused the problem, so we just
	 *       always act like it was an unspecific access to an unmapped page. */
	if (ecode == 0) {
		for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_UNMAPPED));
		PERTASK_SET(this_exception_pointers[0], (uintptr_t)X86_64_ADDRBUS_NONCANON_MIN);
		if (isuser()) {
			PERTASK_SET(this_exception_pointers[1],
			            (uintptr_t)(E_SEGFAULT_CONTEXT_NONCANON |
			                        E_SEGFAULT_CONTEXT_USERCODE));
		} else {
			PERTASK_SET(this_exception_pointers[1],
			            (uintptr_t)E_SEGFAULT_CONTEXT_NONCANON);
		}
		printk(KERN_WARNING "[gpf] Assuming Segmentation fault at ? [pc=%p,%p,opcode=%I32x] [tid=%u]\n",
		       orig_pc, pc, opcode, (unsigned int)task_getroottid_s());
		goto unwind_state;
	}
#endif /* __x86_64__ */
	/* If the error originated from user-space, default to assuming it's
	 * because of some privileged instruction not explicitly handled above. */
#ifdef __x86_64__
generic_privileged_instruction_if_user:
#endif /* __x86_64__ */
	if (isuser()) {
		for (i = 1; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE));
		PERTASK_SET(this_exception_pointers[0], (uintptr_t)opcode);
		goto unwind_state;
	}
	/* In kernel space, this one's a wee bit more complicated... */
	PERTASK_SET(this_exception_code, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_X86_INTERRUPT));
	PERTASK_SET(this_exception_pointers[0], (uintptr_t)opcode);
	PERTASK_SET(this_exception_pointers[1], is_ss ? (uintptr_t)0x0c : (uintptr_t)0x0d);
	PERTASK_SET(this_exception_pointers[2], (uintptr_t)ecode);
	PERTASK_SET(this_exception_pointers[3], (uintptr_t)effective_segment_value);
	for (i = 4; i < EXCEPTION_DATA_POINTERS; ++i)
		PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
unwind_state:
	PERTASK_SET(this_exception_faultaddr, (void *)orig_pc);
	icpustate_setpc(state, (uintptr_t)pc);
#if EXCEPT_BACKTRACE_SIZE != 0
	for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
		PERTASK_SET(this_exception_trace[i], (void *)0);
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	x86_userexcept_unwind_interrupt(state);
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_HANDLE_GPF_C */
