/*[[[magic
// Optimize this file for size
local opt = options.setdefault("GCC.options",[]);
opt.removeif([](e) -> e.startswith("-O"));
opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_VIO_C
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_VIO_C 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/vm.h>

#ifdef CONFIG_VIO

#include <kernel/except.h>
#include <kernel/gdt.h>
#include <kernel/printk.h>
#include <kernel/user.h>
#include <kernel/vio.h>
#include <kernel/vm86.h>
#include <sched/except-handler.h>
#include <sched/task.h>

#include <hybrid/bit.h>
#include <hybrid/overflow.h>

#include <asm/cpu-flags.h>
#include <asm/intrin-arith.h>
#include <asm/intrin.h>
#include <asm/registers.h>
#include <kos/except-inval.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <sys/io.h>

#include <stdint.h>
#include <string.h>

#include <libinstrlen/instrlen.h>

#include "decode.h"
#include "handle_illegal_instruction-bitops.h"
#include "vio.h"

DECL_BEGIN

#pragma GCC diagnostic ignored "-Waddress-of-packed-member"


#ifdef __x86_64__
#undef CONFIG_NO_VM86
#define CONFIG_NO_VM86 1
#define IFELSE_X86_64(i386, x86_64)  x86_64
#define IF_X86_64(...)  __VA_ARGS__
#define NIF_X86_64(...) /* nothing */
#else
#define IFELSE_X86_64(i386, x86_64)  i386
#define IF_X86_64(...)  /* nothing */
#define NIF_X86_64(...) __VA_ARGS__
#endif

#ifndef CONFIG_NO_VM86
#define IF_CONFIG_VM86(...) __VA_ARGS__
#else /* !CONFIG_NO_VM86 */
#define IF_CONFIG_VM86(...) /* nothing */
#endif /* CONFIG_NO_VM86 */


#if !defined(NDEBUG) && 0
#define VIO_PRINT(...) printk(KERN_DEBUG __VA_ARGS__)
#else
#define VIO_PRINT(...) (void)0
#endif

#define CF EFLAGS_CF
#define PF EFLAGS_PF
#define AF EFLAGS_AF
#define ZF EFLAGS_ZF
#define SF EFLAGS_SF
#define TF EFLAGS_TF
#define IF EFLAGS_IF
#define DF EFLAGS_DF
#define OF EFLAGS_OF

#define PRIVATE_TYPEFOR_b  u8
#define PRIVATE_TYPEFOR_w  u16
#define PRIVATE_TYPEFOR_l  u32
#define PRIVATE_TYPEFOR_q  u64
#define PRIVATE_STYPEFOR_b s8
#define PRIVATE_STYPEFOR_w s16
#define PRIVATE_STYPEFOR_l s32
#define PRIVATE_STYPEFOR_q s64
#define PRIVATE_TYPEFOR(x)  PRIVATE_TYPEFOR_##x
#define PRIVATE_STYPEFOR(x) PRIVATE_STYPEFOR_##x
#define TYPEFOR(x)  PRIVATE_TYPEFOR(x)
#define STYPEFOR(x) PRIVATE_STYPEFOR(x)

#define FUNCFOR2(fun,w) fun ## w
#define FUNCFOR(fun,w) FUNCFOR2(fun,w)

#define PRIVATE_REGISTER_CONSTRAINT_b "q"
#define PRIVATE_REGISTER_CONSTRAINT_w "r"
#define PRIVATE_REGISTER_CONSTRAINT_l "r"
#define PRIVATE_REGISTER_CONSTRAINT_q "r"
#define PRIVATE_REGISTER_CONSTRAINT(w) PRIVATE_REGISTER_CONSTRAINT_##w
#define REGISTER_CONSTRAINT(w) PRIVATE_REGISTER_CONSTRAINT(w)

#define PRIVATE_MODRM_CONSTRAINT_b    "qm"
#define PRIVATE_MODRM_CONSTRAINT_w    "g"
#define PRIVATE_MODRM_CONSTRAINT_l    "g"
#define PRIVATE_MODRM_CONSTRAINT_q    "g"
#define PRIVATE_MODRM_CONSTRAINT(w) PRIVATE_MODRM_CONSTRAINT_##w
#define MODRM_CONSTRAINT(w) PRIVATE_MODRM_CONSTRAINT(w)

#define PRIVATE_OPERAND_SIZE_b    "b"
#define PRIVATE_OPERAND_SIZE_w    "w"
#define PRIVATE_OPERAND_SIZE_l    "k"
#define PRIVATE_OPERAND_SIZE_q    "q"
#define PRIVATE_OPERAND_SIZE(w) PRIVATE_OPERAND_SIZE_##w
#define OPERAND_SIZE(w) PRIVATE_OPERAND_SIZE(w)

#ifdef __x86_64__
#define INSTR_PUSHFP   "pushfq\n\t"
#define TAIL_POPP_OP0  "popq %0"
#else /* __x86_64__ */
#define INSTR_PUSHFP   "pushfl\n\t"
#define TAIL_POPP_OP0  "popl %0"
#endif /* !__x86_64__ */


#define VIO_BINARY_WRITE(w, name, flags)                                                             \
	do_##name##w##_write: {                                                                          \
		TYPEFOR(w)                                                                                   \
		oldval;                                                                                      \
		oldval = FUNCFOR(vio_##name, w)(&args->ma_args, vio_addr, (TYPEFOR(w))(value), IS_ATOMIC()); \
		__asm__(#name #w " %" OPERAND_SIZE(w) "1, %" OPERAND_SIZE(w) "2\n\t"                         \
		        INSTR_PUSHFP                                                                         \
		        TAIL_POPP_OP0                                                                        \
		        : "=g" (temp), "+" MODRM_CONSTRAINT(w)(oldval)                                       \
		        : REGISTER_CONSTRAINT(w)((TYPEFOR(w))(value))                                        \
		        : "cc");                                                                             \
		SET_PFLAGS(temp, flags);                                                                     \
	}
#define VIO_BINARY_READ(w, name, flags)                                      \
	/*do_##name##w##_read:*/ {                                               \
		TYPEFOR(w)                                                           \
		addend;                                                              \
		addend = FUNCFOR(vio_read, w)(&args->ma_args, vio_addr);             \
		__asm__(#name #w " %" OPERAND_SIZE(w) "1, %" OPERAND_SIZE(w) "2\n\t" \
		        INSTR_PUSHFP                                                 \
		        TAIL_POPP_OP0                                                \
		        : "=g" (temp)                                                \
		        , "+" MODRM_CONSTRAINT(w)(value)                             \
		        : REGISTER_CONSTRAINT(w)(addend)                             \
		        : "cc");                                                     \
		SET_PFLAGS(temp, flags);                                             \
	}

#define VIO_ADD_WRITE(w) VIO_BINARY_WRITE(w, add, OF | SF | ZF | AF | CF | PF)
#define VIO_ADD_READ(w) VIO_BINARY_READ(w, add, OF | SF | ZF | AF | CF | PF)
#define VIO_OR_WRITE(w) VIO_BINARY_WRITE(w, or, OF | CF | SF | ZF | PF)
#define VIO_OR_READ(w) VIO_BINARY_READ(w, or, OF | CF | SF | ZF | PF)
#define VIO_ADC_WRITE(w)        \
	do_adc##w##_write: {        \
		if (RD_PFLAGS() & CF)   \
			++value;            \
		goto do_add##w##_write; \
	}
#define VIO_ADC_READ(w)                                                      \
	/*do_adc##w##_read:*/ {                                                  \
		TYPEFOR(w)                                                           \
		addend;                                                              \
		addend = FUNCFOR(vio_read, w)(&args->ma_args, vio_addr);             \
		if (RD_PFLAGS() & CF)                                                \
			++addend;                                                        \
		__asm__("add" #w " %" OPERAND_SIZE(w) "1, %" OPERAND_SIZE(w) "2\n\t" \
		        INSTR_PUSHFP                                                 \
		        TAIL_POPP_OP0                                                \
		        : "=g" (temp), "+" MODRM_CONSTRAINT(w)(value)                \
		        : REGISTER_CONSTRAINT(w)(addend)                             \
		        : "cc");                                                     \
		SET_PFLAGS(temp, OF | SF | ZF | AF | CF | PF);                       \
	}
#define VIO_SBB_WRITE(w)        \
	do_sbb##w##_write: {        \
		if (RD_PFLAGS() & CF)   \
			++value;            \
		goto do_sub##w##_write; \
	}
#define VIO_SBB_READ(w)                                                      \
	/*do_sbb##w##_read:*/ {                                                  \
		TYPEFOR(w)                                                           \
		addend;                                                              \
		addend = FUNCFOR(vio_read, w)(&args->ma_args, vio_addr);             \
		if (RD_PFLAGS() & CF)                                                \
			++addend;                                                        \
		__asm__("sub" #w " %" OPERAND_SIZE(w) "1, %" OPERAND_SIZE(w) "2\n\t" \
		        INSTR_PUSHFP                                                 \
		        TAIL_POPP_OP0                                                \
		        : "=g" (temp), "+" MODRM_CONSTRAINT(w)(value)                \
		        : REGISTER_CONSTRAINT(w)(addend)                             \
		        : "cc");                                                     \
		SET_PFLAGS(temp, OF | SF | ZF | AF | CF | PF);                       \
	}
#define VIO_AND_WRITE(w) VIO_BINARY_WRITE(w, and, OF | CF | SF | ZF | PF)
#define VIO_AND_READ(w) VIO_BINARY_READ(w, and, OF | CF | SF | ZF | PF)
#define VIO_SUB_WRITE(w) VIO_BINARY_WRITE(w, sub, OF | SF | ZF | AF | CF | PF)
#define VIO_SUB_READ(w) VIO_BINARY_READ(w, sub, OF | SF | ZF | AF | CF | PF)
#define VIO_XOR_WRITE(w) VIO_BINARY_WRITE(w, xor, OF | CF | SF | ZF | PF)
#define VIO_XOR_READ(w) VIO_BINARY_READ(w, xor, OF | CF | SF | ZF | PF)
#define VIO_CMP_WRITE(w)                                                     \
	do_cmp##w##_write: {                                                     \
		TYPEFOR(w)                                                           \
		oldval;                                                              \
		oldval = FUNCFOR(vio_read, w)(&args->ma_args, vio_addr);             \
		__asm__("cmp" #w " %" OPERAND_SIZE(w) "1, %" OPERAND_SIZE(w) "2\n\t" \
		        INSTR_PUSHFP                                                 \
		        TAIL_POPP_OP0                                                \
		        : "=g" (temp)                                                \
		        : MODRM_CONSTRAINT(w)(oldval)                                \
		        , REGISTER_CONSTRAINT(w)((TYPEFOR(w))(value))                \
		        : "cc");                                                     \
		SET_PFLAGS(temp, CF | OF | SF | ZF | AF | PF);                       \
	}
#define VIO_CMP_READ(w)                                                      \
	/*do_cmp##w##_read:*/ {                                                  \
		TYPEFOR(w)                                                           \
		addend;                                                              \
		addend = FUNCFOR(vio_read, w)(&args->ma_args, vio_addr);             \
		__asm__("cmp" #w " %" OPERAND_SIZE(w) "1, %" OPERAND_SIZE(w) "2\n\t" \
		        INSTR_PUSHFP                                                 \
		        TAIL_POPP_OP0                                                \
		        : "=g" (temp)                                                \
		        : MODRM_CONSTRAINT(w)(value)                                 \
		        , REGISTER_CONSTRAINT(w)(addend)                             \
		        : "cc");                                                     \
		SET_PFLAGS(temp, CF | OF | SF | ZF | AF | PF);                       \
	}


FORCELOCAL ATTR_NORETURN void
NOTHROW(KCALL cleanup_and_unwind_interrupt)(/*inherit(always)*/ vio_main_args_t *__restrict args,
                                            struct icpustate *__restrict state) {
	decref_unlikely(args->ma_args.va_block);
	decref_unlikely(args->ma_args.va_part);
	task_popconnections(args->ma_oldcons);
	x86_userexcept_unwind_interrupt(state);
}



INTERN struct icpustate *
NOTHROW(FCALL x86_vio_main)(/*inherit(always)*/ vio_main_args_t *__restrict args,
                            uintptr_t cr2, uintptr_t ecode) {
	/* Exceptions always point to the instruction _after_ the faulting one! */
	byte_t *orig_pc, *pc;
	vm_daddr_t vio_addr;
	struct modrm mod;
	struct icpustate *state = args->ma_args.va_state;
	uintptr_t value, temp;
	u32 opcode;
	op_flag_t op_flags;
	bool isuser;
	isuser  = icpustate_isuser(state);
	orig_pc = (byte_t *)icpustate_getpc(state);
	vio_addr = (vm_daddr_t)cr2;
	vio_addr -= (vm_daddr_t)args->ma_args.va_access_pageaddr * PAGESIZE;
	vio_addr += (vm_daddr_t)args->ma_args.va_access_partoff;
	TRY {
		pc     = orig_pc;
		opcode = x86_decode_instruction(state, &pc, &op_flags);
		switch (opcode) {
#define MOD_DECODE() pc = x86_decode_modrm(pc, &mod, op_flags)

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

#define RD_VIOB()  vio_readb(&args->ma_args, vio_addr)
#define WR_VIOB(v) vio_writeb(&args->ma_args, vio_addr, v)
#define RD_VIOW()  vio_readw(&args->ma_args, vio_addr)
#define WR_VIOW(v) vio_writew(&args->ma_args, vio_addr, v)
#define RD_VIOL()  vio_readl(&args->ma_args, vio_addr)
#define WR_VIOL(v) vio_writel(&args->ma_args, vio_addr, v)
#ifdef __x86_64__
#define RD_VIOQ()  vio_readq(&args->ma_args, vio_addr)
#define WR_VIOQ(v) vio_writeq(&args->ma_args, vio_addr, v)
#define RD_VIO()   vio_readq(&args->ma_args, vio_addr)
#define WR_VIO(v)  vio_writeq(&args->ma_args, vio_addr, v)
#else /* __x86_64__ */
#define RD_VIO()   vio_readl(&args->ma_args, vio_addr)
#define WR_VIO(v)  vio_writel(&args->ma_args, vio_addr, v)
#endif /* !__x86_64__ */

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

#define RD_VEXREG()   x86_icpustate_get(state, (u8)((op_flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S))
#define WR_VEXREG(v)  x86_icpustate_set(state, (u8)((op_flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S), v)
#define RD_VEXREGB()  x86_icpustate_get8(state, (u8)((op_flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S))
#define WR_VEXREGB(v) x86_icpustate_set8(state, (u8)((op_flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S), v)
#define RD_VEXREGW()  x86_icpustate_get16(state, (u8)((op_flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S))
#define WR_VEXREGW(v) x86_icpustate_set16(state, (u8)((op_flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S), v)
#define RD_VEXREGL()  x86_icpustate_get32(state, (u8)((op_flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S))
#define WR_VEXREGL(v) x86_icpustate_set32(state, (u8)((op_flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S), v)
#ifdef __x86_64__
#define RD_VEXREGQ()  x86_icpustate_get64(state, (u8)((op_flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S))
#define WR_VEXREGQ(v) x86_icpustate_set64(state, (u8)((op_flags & F_VEX_VVVV_M) >> F_VEX_VVVV_S), v)
#endif /* __x86_64__ */


#define RD_PFLAGS()         irregs_rdflags(&state->ics_irregs)
#define WR_PFLAGS(v)        irregs_wrflags(&state->ics_irregs, v)

#ifdef __x86_64__
#define RD_USP()  irregs_rdsp(&state->ics_irregs)
#define WR_USP(v) irregs_wrsp(&state->ics_irregs, v)
#else /* __x86_64__ */
#define RD_USP()  ((u32)state->ics_irregs_u.ir_esp)
#define WR_USP(v) (void)(state->ics_irregs_u.ir_esp = (v))
#endif /* !__x86_64__ */

#define IS_ATOMIC()        (op_flags & F_LOCK)
#define IS_MODVIO()        (mod.mi_type == MODRM_MEMORY && x86_decode_modrmgetmem(state, &mod, op_flags) == cr2)
#define SET_PFLAGS(v, mask) WR_PFLAGS((RD_PFLAGS() & ~(mask)) | ((v) & (mask)))

#ifdef __x86_64__
#define RD_AL()    (*(u8 const *)&state->ics_gpregs.gp_rax)
#define RD_AX()    ((u16)state->ics_gpregs.gp_rax)
#define RD_EAX()   ((u32)state->ics_gpregs.gp_rax)
#define RD_RAX()   ((u64)state->ics_gpregs.gp_rax)
#define RD_CL()    (*(u8 const *)&state->ics_gpregs.gp_rcx)
#define RD_ECX()   ((u32)state->ics_gpregs.gp_rcx)
#define RD_RCX()   ((u64)state->ics_gpregs.gp_rcx)
#define RD_PCX()   ((u64)state->ics_gpregs.gp_rcx)
#define RD_DX()    ((u16)state->ics_gpregs.gp_rdx)
#define RD_EDX()   ((u32)state->ics_gpregs.gp_rdx)
#define RD_RDX()   ((u64)state->ics_gpregs.gp_rdx)
#define RD_EBX()   ((u32)state->ics_gpregs.gp_rbx)
#define RD_PDI()   ((u64)state->ics_gpregs.gp_rdi)
#define RD_PSI()   ((u64)state->ics_gpregs.gp_rsi)
#define WR_AL(v)   (*(u8 *)&state->ics_gpregs.gp_rax = (u8)(v))
#define WR_AX(v)   (state->ics_gpregs.gp_rax = (u64)(u16)(v))
#define WR_EAX(v)  (state->ics_gpregs.gp_rax = (u64)(u32)(v))
#define WR_RAX(v)  (state->ics_gpregs.gp_rax = (u64)(v))
#define WR_ECX(v)  (state->ics_gpregs.gp_rcx = (u64)(u32)(v))
#define WR_RCX(v)  (state->ics_gpregs.gp_rcx = (u64)(v))
#define WR_PCX(v)  (state->ics_gpregs.gp_rcx = (u64)(v))
#define WR_DX(v)   (state->ics_gpregs.gp_rdx = (u64)(u16)(v))
#define WR_EDX(v)  (state->ics_gpregs.gp_rdx = (u64)(u32)(v))
#define WR_RDX(v)  (state->ics_gpregs.gp_rdx = (u64)(v))
#define WR_EBX(v)  (state->ics_gpregs.gp_rbx = (u64)(u32)(v))
#define WR_PDI(v)  (state->ics_gpregs.gp_rdi = (u64)(v))
#define WR_PSI(v)  (state->ics_gpregs.gp_rsi = (u64)(v))
#else /* __x86_64__ */
#define RD_AL()    (*(u8 const *)&state->ics_gpregs.gp_eax)
#define RD_AX()    ((u16)state->ics_gpregs.gp_eax)
#define RD_EAX()   ((u32)state->ics_gpregs.gp_eax)
#define RD_CL()    (*(u8 const *)&state->ics_gpregs.gp_ecx)
#define RD_ECX()   ((u32)state->ics_gpregs.gp_ecx)
#define RD_PCX()   ((u32)state->ics_gpregs.gp_ecx)
#define RD_DX()    ((u16)state->ics_gpregs.gp_edx)
#define RD_EDX()   ((u32)state->ics_gpregs.gp_edx)
#define RD_EBX()   ((u32)state->ics_gpregs.gp_ebx)
#define RD_PDI()   ((u32)state->ics_gpregs.gp_edi)
#define RD_PSI()   ((u32)state->ics_gpregs.gp_esi)
#define WR_AL(v)   (*(u8 *)&state->ics_gpregs.gp_eax = (u8)(v))
#define WR_AX(v)   (state->ics_gpregs.gp_eax = (u32)(u16)(v))
#define WR_EAX(v)  (state->ics_gpregs.gp_eax = (u32)(v))
#define WR_ECX(v)  (state->ics_gpregs.gp_ecx = (u32)(v))
#define WR_PCX(v)  (state->ics_gpregs.gp_ecx = (u32)(v))
#define WR_DX(v)   (state->ics_gpregs.gp_edx = (u32)(u16)(v))
#define WR_EDX(v)  (state->ics_gpregs.gp_edx = (u32)(v))
#define WR_EBX(v)  (state->ics_gpregs.gp_ebx = (u32)(v))
#define WR_PDI(v)  (state->ics_gpregs.gp_edi = (u32)(v))
#define WR_PSI(v)  (state->ics_gpregs.gp_esi = (u32)(v))
#endif /* !__x86_64__ */
#define F_ATOMIC       (!!(op_flags & F_LOCK))

#if !defined(__INTELLISENSE__) || 0

		/* ======================================================================== */
		/*    MOV                                                                   */
		/* ======================================================================== */
		case 0x88:
			/* 88 /r      MOV r/m8,r8      Move r8 to r/m8 */
			MOD_DECODE();
			if (IS_MODVIO()) {
				WR_VIOB(RD_REGB());
				goto done;
			}
			break;


		case 0x89:
			/* 89 /r      MOV r/m16,r16      Move r16 to r/m16 */
			/* 89 /r      MOV r/m32,r32      Move r32 to r/m32 */
			MOD_DECODE();
			if (IS_MODVIO()) {
				IF_X86_64(if (op_flags & F_REX_W) {
					WR_VIOQ(RD_REGQ());
				} else) if (op_flags & F_OP16) {
					WR_VIOW(RD_REGW());
				} else {
					WR_VIOL(RD_REGL());
				}
				goto done;
			}
			break;


		case 0x8a:
			/* 8A /r      MOV r8,r/m8      Move r/m8 to r8 */
			MOD_DECODE();
			if (IS_MODVIO()) {
				WR_REGB(RD_VIOB());
				goto done;
			}
			break;


		case 0x8b:
			/* 8B /r      MOV r16,r/m16      Move r/m16 to r16 */
			/* 8B /r      MOV r32,r/m32      Move r/m32 to r32 */
			MOD_DECODE();
			if (IS_MODVIO()) {
				IF_X86_64(if (op_flags & F_REX_W) {
					WR_REGQ(RD_VIOQ());
				} else) if (op_flags & F_OP16) {
					WR_REGW(RD_VIOW());
				} else {
					WR_REGL(RD_VIOL());
				}
				goto done;
			}
			break;


		case 0x8c:
			/*         8C /r     MOV r/m16,Sreg**           MR  Valid Valid Move segment register to r/m16.
			 * REX.W + 8C /r     MOV r16/r32/m16, Sreg**    MR  Valid Valid Move zero extended 16-bit segment register to r16/r32/r64/m16.
			 * REX.W + 8C /r     MOV r64/m16, Sreg**        MR  Valid Valid Move zero extended 16-bit segment register to r64/m16. */
			MOD_DECODE();
			if (IS_MODVIO()) {
				if (mod.mi_reg < 6) {
					u16 value;
					switch (mod.mi_reg) {
					case 0: value = icpustate_getes(state); break;
					case 1: value = icpustate_getcs(state); break;
					case 2: value = icpustate_getss(state); break;
					case 3: value = icpustate_getds(state); break;
					case 4: value = icpustate_getfs(state); break;
					case 5: value = icpustate_getgs(state); break;
					default: __builtin_unreachable();
					}
					IF_X86_64(if (op_flags & F_REX_W) {
						WR_REGQ(value);
					} else) if (op_flags & F_OP16) {
						WR_REGW(value);
					} else {
						WR_REGL(value);
					}
					goto done;
				}
			}
			break;


		case 0x8e:
			/*         8E /r      MOV Sreg,r/m16** RM Valid Valid Move r/m16 to segment register.
			 * REX.W + 8E /r      MOV Sreg,r/m64** RM Valid Valid Move lower 16 bits of r/m64 to segment register. */
			MOD_DECODE();
			if (IS_MODVIO()) {
				if (mod.mi_reg < 6) {
					u16 value = RD_VIOW();
#ifndef __x86_64__
					if (irregs_isvm86(&state->ics_irregs)) {
						/*value &= 0xffff;*/
						switch (mod.mi_reg) {
						case 0: state->ics_irregs_v.ir_es = value; break;
						case 1: state->ics_irregs_v.ir_cs = value; break;
						case 2: state->ics_irregs_v.ir_ss = value; break;
						case 3: state->ics_irregs_v.ir_ds = value; break;
						case 4: state->ics_irregs_v.ir_fs = value; break;
						case 5: state->ics_irregs_v.ir_gs = value; break;
						default: __builtin_unreachable();
						}
					} else
#endif /* !__x86_64__ */
					{
						if ((mod.mi_reg == 1 ? !SEGMENT_IS_VALID_USERCODE(value)
						                     : !SEGMENT_IS_VALID_USERDATA(value)) &&
						    isuser) {
							THROW(E_INVALID_ARGUMENT_BAD_VALUE,
							      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
							      X86_REGISTER_SEGMENT_ES + mod.mi_reg, value);
						}
						switch (mod.mi_reg) {
						case 0: icpustate_setes_novm86(state, value); break;
						case 1: icpustate_setcs(state, value); break;
						case 2: icpustate_setuserss(state, value); break;
						case 3: icpustate_setds_novm86(state, value); break;
						case 4: icpustate_setfs_novm86(state, value); break;
						case 5: icpustate_setgs_novm86(state, value); break;
						default: __builtin_unreachable();
						}
					}
					goto done;
				}
			}
			break;


		case 0xa0:
			/* A0      MOV AL,moffs8*      Move byte at (seg:offset) to AL */
			if (op_flags & F_AD16) {
				value = *(u16 *)pc;
				pc += 2;
			} else {
				value = *(u32 *)pc;
				pc += 4;
			}
			if (value == cr2) {
				WR_AL(RD_VIOB());
				goto done;
			}
			break;


		case 0xa1:
			/* A1      MOV AX,moffs16*      Move word at (seg:offset) to AX */
			/* A1      MOV EAX,moffs32*      Move doubleword at (seg:offset) to EAX */
			if (op_flags & F_AD16) {
				value = *(u16 *)pc;
				pc += 2;
			} else {
				value = *(u32 *)pc;
				pc += 4;
			}
			if (value == cr2) {
				IF_X86_64(if (op_flags & F_REX_W) {
					WR_RAX(RD_VIOQ());
				} else) if (op_flags & F_OP16) {
					WR_AX(RD_VIOW());
				} else {
					WR_EAX(RD_VIOL());
				}
				goto done;
			}
			break;


		case 0xa2:
			/* A2      MOV moffs8*,AL      Move AL to (seg:offset) */
			if (op_flags & F_AD16) {
				value = *(u16 *)pc;
				pc += 2;
			} else {
				value = *(u32 *)pc;
				pc += 4;
			}
			if (value == cr2) {
				WR_VIOB(RD_AL());
				goto done;
			}
			break;


		case 0xa3:
			/* A3      MOV moffs16*,AX      Move AX to (seg:offset) */
			/* A3      MOV moffs32*,EAX      Move EAX to (seg:offset) */
			if (op_flags & F_AD16) {
				value = *(u16 *)pc;
				pc += 2;
			} else {
				value = *(u32 *)pc;
				pc += 4;
			}
			if (value == cr2) {
				IF_X86_64(if (op_flags & F_REX_W) {
					WR_VIOQ(RD_RAX());
				} else) if (op_flags & F_OP16) {
					WR_VIOW(RD_AX());
				} else {
					WR_VIOL(RD_EAX());
				}
				goto done;
			}
			break;


		case 0xc6:
			MOD_DECODE();
			switch (mod.mi_reg) {

			case 0:
				/* C6 /0      MOV r/m8,imm8      Move imm8 to r/m8 */
				value = *(u8 *)pc;
				pc += 1;
				if (IS_MODVIO()) {
					WR_VIOB((u8)value);
					goto done;
				}
				break;

			default: goto undefined_instruction;
			}
			break;


		case 0xc7:
			MOD_DECODE();
			switch (mod.mi_reg) {

			case 0:
				/* C7 /0      MOV r/m16,imm16      Move imm16 to r/m16 */
				/* C7 /0      MOV r/m32,imm32      Move imm32 to r/m32 */
				IF_X86_64(if (op_flags & F_REX_W) {
					value = (u64)(s64)*(s32 *)pc;
					pc += 4;
				} else) if (op_flags & F_OP16) {
					value = *(u16 *)pc;
					pc += 2;
				} else {
					value = *(u32 *)pc;
					pc += 4;
				}
				if (IS_MODVIO()) {
					IF_X86_64(if (op_flags & F_REX_W) {
						WR_VIOQ((u64)value);
					} else) if (op_flags & F_OP16) {
						WR_VIOW((u16)value);
					} else {
						WR_VIOL((u32)value);
					}
					goto done;
				}
				break;

			default: goto undefined_instruction;
			}
			break;


		/* ======================================================================== */
		/*    BINARY ARITHMATIC                                                     */
		/* ======================================================================== */
		case 0x80:
			MOD_DECODE();
			value = *(u8 *)pc;
			pc += 1;
			if (IS_MODVIO())
				switch (mod.mi_reg) {
				case 0: VIO_ADD_WRITE(b); goto done; /* 80 /0 ib      ADD r/m8,imm8      Add imm8 to r/m8 */
				case 1: VIO_OR_WRITE(b); goto done;  /* 80 /1 ib      OR r/m8,imm8       r/m8 OR imm8 */
				case 2: VIO_ADC_WRITE(b); goto done; /* 80 /2 ib      ADC r/m8,imm8      Add with carry imm8 to r/m8 */
				case 3: VIO_SBB_WRITE(b); goto done; /* 80 /3 ib      SBB r/m8,imm8      Subtract with borrow imm8 from r/m8 */
				case 4: VIO_AND_WRITE(b); goto done; /* 80 /4 ib      AND r/m8,imm8      r/m8 AND imm8 */
				case 5: VIO_SUB_WRITE(b); goto done; /* 80 /5 ib      SUB r/m8,imm8      Subtract imm8 from r/m8 */
				case 6: VIO_XOR_WRITE(b); goto done; /* 80 /6 ib      XOR r/m8,imm8      r/m8 XOR imm8 */
				case 7: VIO_CMP_WRITE(b); goto done; /* 80 /7 ib      CMP r/m8,imm8      Compare imm8 with r/m8 */
				default: goto undefined_instruction;
				}
			break;


		case 0x81:
			MOD_DECODE();
#ifdef __x86_64__
			if (op_flags & F_REX_W) {
				value = (u64)(s64)*(s32 *)pc;
				pc += 2;
				if (IS_MODVIO())
					switch (mod.mi_reg) {
					case 0: VIO_ADD_WRITE(q); goto done; /* 81 /0 iq      ADD r/m64,Simm32      Add Simm32 to r/m64 */
					case 1: VIO_OR_WRITE(q); goto done;  /* 81 /1 iq      OR r/m64,Simm32       r/m64 OR Simm32 */
					case 2: VIO_ADC_WRITE(q); goto done; /* 81 /2 iq      ADC r/m64,Simm32      Add with carry Simm32 to r/m64 */
					case 3: VIO_SBB_WRITE(q); goto done; /* 81 /3 iq      SBB r/m64,Simm32      Subtract with borrow Simm32 from r/m64 */
					case 4: VIO_AND_WRITE(q); goto done; /* 81 /4 iq      AND r/m64,Simm32      r/m64 AND Simm32 */
					case 5: VIO_SUB_WRITE(q); goto done; /* 81 /5 iq      SUB r/m64,Simm32      Subtract Simm32 from r/m64 */
					case 6: VIO_XOR_WRITE(q); goto done; /* 81 /6 iq      XOR r/m64,Simm32      r/m64 XOR Simm32 */
					case 7: VIO_CMP_WRITE(q); goto done; /* 81 /7 iq      CMP r/m64,Simm32      Compare Simm32 with r/m64 */
					default: goto undefined_instruction;
					}
			} else
#endif /* __x86_64__ */
			if (op_flags & F_OP16) {
				value = *(u16 *)pc;
				pc += 2;
				if (IS_MODVIO())
					switch (mod.mi_reg) {
					case 0: VIO_ADD_WRITE(w); goto done; /* 81 /0 iw      ADD r/m16,imm16      Add imm16 to r/m16 */
					case 1: VIO_OR_WRITE(w); goto done;  /* 81 /1 iw      OR r/m16,imm16       r/m16 OR imm16 */
					case 2: VIO_ADC_WRITE(w); goto done; /* 81 /2 iw      ADC r/m16,imm16      Add with carry imm16 to r/m16 */
					case 3: VIO_SBB_WRITE(w); goto done; /* 81 /3 iw      SBB r/m16,imm16      Subtract with borrow imm16 from r/m16 */
					case 4: VIO_AND_WRITE(w); goto done; /* 81 /4 iw      AND r/m16,imm16      r/m16 AND imm16 */
					case 5: VIO_SUB_WRITE(w); goto done; /* 81 /5 iw      SUB r/m16,imm16      Subtract imm16 from r/m16 */
					case 6: VIO_XOR_WRITE(w); goto done; /* 81 /6 iw      XOR r/m16,imm16      r/m16 XOR imm16 */
					case 7: VIO_CMP_WRITE(w); goto done; /* 81 /7 iw      CMP r/m16,imm16      Compare imm16 with r/m16 */
					default: goto undefined_instruction;
					}
			} else {
				value = *(u32 *)pc;
				pc += 4;
				if (IS_MODVIO())
					switch (mod.mi_reg) {
					case 0: VIO_ADD_WRITE(l); goto done; /* 81 /0 id      ADD r/m32,imm32      Add imm32 to r/m32 */
					case 1: VIO_OR_WRITE(l); goto done;  /* 81 /1 id      OR r/m32,imm32       r/m32 OR imm32 */
					case 2: VIO_ADC_WRITE(l); goto done; /* 81 /2 id      ADC r/m32,imm32      Add with CF imm32 to r/m32 */
					case 3: VIO_SBB_WRITE(l); goto done; /* 81 /3 id      SBB r/m32,imm32      Subtract with borrow imm32 from r/m32 */
					case 4: VIO_AND_WRITE(l); goto done; /* 81 /4 id      AND r/m32,imm32      r/m32 AND imm32 */
					case 5: VIO_SUB_WRITE(l); goto done; /* 81 /5 id      SUB r/m32,imm32      Subtract imm32 from r/m32 */
					case 6: VIO_XOR_WRITE(l); goto done; /* 81 /6 id      XOR r/m32,imm32      r/m32 XOR imm32 */
					case 7: VIO_CMP_WRITE(l); goto done; /* 81 /7 id      CMP r/m32,imm32      Compare imm32 with r/m32 */
					default: goto undefined_instruction;
					}
			}
			break;


		case 0x83:
			MOD_DECODE();
			value = (uintptr_t)(intptr_t) * (s8 *)pc;
			pc += 1;
			if (!IS_MODVIO())
				break;
			if (op_flags & F_OP16) {
				switch (mod.mi_reg) {
				case 0: goto do_addw_write; /* 83 /0 ib      ADD r/m16,Simm8      Add sign-extended imm8 to r/m16 */
				case 1: goto do_orw_write;  /* 83 /1 ib      OR r/m16,Simm8       r/m16 OR imm8 (sign-extended) */
				case 2: goto do_adcw_write; /* 83 /2 ib      ADC r/m16,Simm8      Add with CF sign-extended imm8 to r/m16 */
				case 3: goto do_sbbw_write; /* 83 /3 ib      SBB r/m16,Simm8      Subtract with borrow sign-extended imm8 from r/m16 */
				case 4: goto do_andw_write; /* 83 /4 ib      AND r/m16,Simm8      r/m16 AND imm8 (sign-extended) */
				case 5: goto do_subw_write; /* 83 /5 ib      SUB r/m16,Simm8      Subtract sign-extended imm8 from r/m16 */
				case 6: goto do_xorw_write; /* 83 /6 ib      XOR r/m16,Simm8      r/m16 XOR imm8 (sign-extended) */
				case 7: goto do_cmpw_write; /* 83 /7 ib      CMP r/m16,Simm8      Compare imm8 with r/m16 */
				default: goto undefined_instruction;
				}
			} else {
				switch (mod.mi_reg) {
				case 0: goto do_addl_write; /* 83 /0 ib      ADD r/m32,Simm8      Add sign-extended imm8 to r/m32 */
				case 1: goto do_orl_write;  /* 83 /1 ib      OR r/m32,Simm8       r/m32 OR imm8 (sign-extended) */
				case 2: goto do_adcl_write; /* 83 /2 ib      ADC r/m32,Simm8      Add with CF sign-extended imm8 into r/m32 */
				case 3: goto do_sbbl_write; /* 83 /3 ib      SBB r/m32,Simm8      Subtract with borrow sign-extended imm8 from r/m32 */
				case 4: goto do_andl_write; /* 83 /4 ib      AND r/m32,Simm8      r/m32 AND imm8 (sign-extended) */
				case 5: goto do_subl_write; /* 83 /5 ib      SUB r/m32,Simm8      Subtract sign-extended imm8 from r/m32 */
				case 6: goto do_xorl_write; /* 83 /6 ib      XOR r/m32,Simm8      r/m32 XOR imm8 (sign-extended) */
				case 7: goto do_cmpl_write; /* 83 /7 ib      CMP r/m32,Simm8      Compare imm8 with r/m32 */
				default: goto undefined_instruction;
				}
			}
			break;
#define DEFINE_REGISTER_MEMORY_INSTRUCTIONS(start, name, NAME, if_writeback) \
		case start + 0x00:                                                   \
			MOD_DECODE();                                                    \
			if (!IS_MODVIO())                                                \
				break;                                                       \
			value = RD_REGB();                                               \
			goto do_##name##b_write;                                         \
		case start + 0x01:                                                   \
			MOD_DECODE();                                                    \
			if (!IS_MODVIO())                                                \
				break;                                                       \
			IF_X86_64(if (op_flags & F_REX_W) {                              \
				value = RD_REGQ();                                           \
				goto do_##name##q_write;                                     \
			})                                                               \
			if (op_flags & F_OP16) {                                         \
				value = RD_REGW();                                           \
				goto do_##name##w_write;                                     \
			}                                                                \
			value = RD_REGL();                                               \
			goto do_##name##l_write;                                         \
		case start + 0x02:                                                   \
			if (!IS_MODVIO())                                                \
				break;                                                       \
			value = RD_REGB();                                               \
			VIO_##NAME##_READ(b);                                            \
			if_writeback(WR_REGB((u8)value));                                \
			goto done;                                                       \
		case start + 0x03:                                                   \
			if (!IS_MODVIO())                                                \
				break;                                                       \
			IF_X86_64(if (op_flags & F_REX_W) {                              \
				value = RD_REGQ();                                           \
				VIO_##NAME##_READ(q);                                        \
				if_writeback(WR_REGQ((u64)value);)                           \
			} else) if (op_flags & F_OP16) {                                 \
				value = RD_REGW();                                           \
				VIO_##NAME##_READ(w);                                        \
				if_writeback(WR_REGW((u16)value);)                           \
			} else {                                                         \
				value = RD_REGL();                                           \
				VIO_##NAME##_READ(l);                                        \
				if_writeback(WR_REGL((u32)value);)                           \
			}                                                                \
			goto done;
#define I1(x) x
#define I0(x) /* nothing */
		/* 00 /r      ADD r/m8, r8        Add r8 to r/m8 */
		/* 01 /r      ADD r/m16, r16      Add r16 to r/m16 */
		/* 01 /r      ADD r/m32, r32      Add r32 to r/m32 */
		/* 02 /r      ADD r8, r/m8        Add r/m8 to r8 */
		/* 03 /r      ADD r16, r/m16      Add r/m16 to r16 */
		/* 03 /r      ADD r32, r/m32      Add r/m32 to r32 */
		DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x00, add, ADD, I1)

		/* 08 /r      OR r/m8,r8        r/m8 OR r8 */
		/* 09 /r      OR r/m16,r16      r/m16 OR r16 */
		/* 09 /r      OR r/m32,r32      r/m32 OR r32 */
		/* 0A /r      OR r8,r/m8        r8 OR r/m8 */
		/* 0B /r      OR r16,r/m16      r16 OR r/m16 */
		/* 0B /r      OR r32,r/m32      r32 OR r/m32 */
		DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x08, or, OR, I1)

		/* 10 /r      ADC r/m8, r8        Add with carry byte register to r/m8 */
		/* 11 /r      ADC r/m16, r16      Add with carry r16 to r/m16 */
		/* 11 /r      ADC r/m32, r32      Add with CF r32 to r/m32 */
		/* 12 /r      ADC r8, r/m8        Add with carry r/m8 to byte register */
		/* 13 /r      ADC r16, r/m16      Add with carry r/m16 to r16 */
		/* 13 /r      ADC r32, r/m32      Add with CF r/m32 to r32 */
		DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x10, adc, ADC, I1)

		/* 18 /r      SBB r/m8,r8        Subtract with borrow r8 from r/m8 */
		/* 19 /r      SBB r/m16,r16      Subtract with borrow r16 from r/m16 */
		/* 19 /r      SBB r/m32,r32      Subtract with borrow r32 from r/m32 */
		/* 1A /r      SBB r8,r/m8        Subtract with borrow r/m8 from r8 */
		/* 1B /r      SBB r16,r/m16      Subtract with borrow r/m16 from r16 */
		/* 1B /r      SBB r32,r/m32      Subtract with borrow r/m32 from r32 */
		DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x18, sbb, SBB, I1)

		/* 20 /r      AND r/m8, r8        r/m8 AND r8 */
		/* 21 /r      AND r/m16, r16      r/m16 AND r16 */
		/* 21 /r      AND r/m32, r32      r/m32 AND r32 */
		/* 22 /r      AND r8, r/m8        r8 AND r/m8 */
		/* 23 /r      AND r16, r/m16      r16 AND r/m16 */
		/* 23 /r      AND r32, r/m32      r32 AND r/m32 */
		DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x20, and, AND, I1)

		/* 28 /r      SUB r/m8,r8        Subtract r8 from r/m8 */
		/* 29 /r      SUB r/m16,r16      Subtract r16 from r/m16 */
		/* 29 /r      SUB r/m32,r32      Subtract r32 from r/m32 */
		/* 2A /r      SUB r8,r/m8        Subtract r/m8 from r8 */
		/* 2B /r      SUB r16,r/m16      Subtract r/m16 from r16 */
		/* 2B /r      SUB r32,r/m32      Subtract r/m32 from r32 */
		DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x28, sub, SUB, I1)

		/* 30 /r      XOR r/m8,r8        r/m8 XOR r8 */
		/* 31 /r      XOR r/m16,r16      r/m16 XOR r16 */
		/* 31 /r      XOR r/m32,r32      r/m32 XOR r32 */
		/* 32 /r      XOR r8,r/m8        r8 XOR r/m8 */
		/* 33 /r      XOR r16,r/m16      r16 XOR r/m16 */
		/* 33 /r      XOR r32,r/m32      r32 XOR r/m32 */
		DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x30, xor, XOR, I1)

		/* 38 /r      CMP r/m8,r8        Compare r8 with r/m8 */
		/* 39 /r      CMP r/m16,r16      Compare r16 with r/m16 */
		/* 39 /r      CMP r/m32,r32      Compare r32 with r/m32 */
		/* 3A /r      CMP r8,r/m8        Compare r/m8 with r8 */
		/* 3B /r      CMP r16,r/m16      Compare r/m16 with r16 */
		/* 3B /r      CMP r32,r/m32      Compare r/m32 with r32 */
		DEFINE_REGISTER_MEMORY_INSTRUCTIONS(0x38, cmp, CMP, I0)
#undef I0
#undef I1
#undef DEFINE_REGISTER_MEMORY_INSTRUCTIONS

#ifndef __x86_64__
		case 0x62:
			/* 62 /r      BOUND r16, m16&16      Check if r16 (array index) is within bounds specified by m16&16 */
			/* 62 /r      BOUND r32, m32&32      Check if r32 (array index) is within bounds specified by m32&32 */
			MOD_DECODE();
			if (IS_MODVIO()) {
				s32 bound_idx, bound_min, bound_max;
				if (op_flags & F_OP16) {
					bound_min = (s32)RD_VIOL();
					bound_max = (s32)(((u32)bound_min & 0xffff0000) >> 16);
					bound_min = (s32)(((u32)bound_min & 0xffff));
					bound_idx = (s32)RD_REGW();
				} else {
					bound_min = (s32)RD_VIOL();
					bound_max = (s32)vio_readl(&args->ma_args, vio_addr + 4);
					bound_idx = (s32)RD_REGL();
				}
				if (!(bound_idx >= bound_min && bound_idx <= bound_max))
					THROW(E_INDEX_ERROR_OUT_OF_BOUNDS, bound_idx, bound_min, bound_max);
				goto done;
			}
			break;
#endif /* !__x86_64__ */

		case 0x0fbc:
			MOD_DECODE();
			if (IS_MODVIO()) {
				if (op_flags & F_REP) {
					/* F3 0F BC /r       TZCNT r16, r/m16   A   V/V      BMI1   Count the number of trailing zero bits in r/m16, return result in r16.
					 * F3 0F BC /r       TZCNT r32, r/m32   A   V/V      BMI1   Count the number of trailing zero bits in r/m32, return result in r32.
					 * F3 REX.W 0F BC /r TZCNT r64, r/m64   A   V/N.E.   BMI1   Count the number of trailing zero bits in r/m64, return result in r64. */
					uintptr_t flags = RD_PFLAGS();
					IF_X86_64(if (op_flags & F_REX_W) {
						WR_REGQ(simple_tzcnt64(RD_VIOQ(), &flags));
					} else) if (!(op_flags & F_OP16)) {
						WR_REGL(simple_tzcnt32(RD_VIOL(), &flags));
					} else {
						WR_REGW(simple_tzcnt16(RD_VIOW(), &flags));
					}
					WR_PFLAGS(flags);
				} else {
					/* 0F BC      BSF r16, r/m16      Bit scan forward on r/m16 */
					/* 0F BC      BSF r32, r/m32      Bit scan forward on r/m32 */
					IF_X86_64(if (op_flags & F_REX_W) {
						value = RD_VIOQ();
					} else) if (op_flags & F_OP16) {
						value = RD_VIOW();
					} else {
						value = RD_VIOL();
					}
					if (!value) {
						WR_PFLAGS(RD_PFLAGS() | ZF);
					} else {
						WR_PFLAGS(RD_PFLAGS() & ~ZF);
						__asm__("bsf %1, %0"
						        : "=r" (value)
						        : "g" (value));
						WR_REGL(value);
					}
				}
				goto done;
			}
			break;


		case 0x0fbd:
			MOD_DECODE();
			if (IS_MODVIO()) {
				if (op_flags & F_REP) {
					/* F3 0F BD /r        LZCNT r16, r/m16
					 * F3 0F BD /r        LZCNT r32, r/m32
					 * F3 REX.W 0F BD /r  LZCNT r64, r/m64 */
					uintptr_t flags = RD_PFLAGS();
					IF_X86_64(if (op_flags & F_REX_W) {
						WR_REGQ(simple_lzcnt64(RD_VIOQ(), &flags));
					} else) if (!(op_flags & F_OP16)) {
						WR_REGL(simple_lzcnt32(RD_VIOL(), &flags));
					} else {
						WR_REGW(simple_lzcnt16(RD_VIOW(), &flags));
					}
					WR_PFLAGS(flags);
				} else {
					/* 0F BD      BSR r16, r/m16      Bit scan reverse on r/m16 */
					/* 0F BD      BSR r32, r/m32      Bit scan reverse on r/m32 */
					IF_X86_64(if (op_flags & F_REX_W) {
						value = RD_VIOQ();
					} else) if (op_flags & F_OP16) {
						value = RD_VIOW();
					} else {
						value = RD_VIOL();
					}
					if (!value) {
						WR_PFLAGS(RD_PFLAGS() | ZF);
					} else {
						WR_PFLAGS(RD_PFLAGS() & ~ZF);
						__asm__("bsr %1, %0"
						        : "=r" (value)
						        : "g" (value));
						WR_REGL(value);
					}
				}
				goto done;
			}
			break;


		case 0x0fa3:
			/* 0F A3      BT r/m16, r16      Store selected bit in CF flag */
			/* 0F A3      BT r/m32, r32      Store selected bit in CF flag */
			MOD_DECODE();
			if (IS_MODVIO()) {
				IF_X86_64(if (op_flags & F_REX_W) {
					value = RD_VIOQ();
					value &= (u64)1 << (RD_REGQ() % 64);
				} else) if (op_flags & F_OP16) {
					value = RD_VIOW();
					value &= (u16)1 << (RD_REGW() % 16);
				} else {
					value = RD_VIOL();
					value &= (u32)1 << (RD_REGL() % 32);
				}
set_cf_is_value_nonzero:
				if (value) {
					WR_PFLAGS(RD_PFLAGS() | ZF);
				} else {
					WR_PFLAGS(RD_PFLAGS() & ~ZF);
				}
				goto done;
			}
			break;


		case 0x0fbb:
			/* 0F BB      BTC r/m16, r16      Store selected bit in CF flag and complement */
			/* 0F BB      BTC r/m32, r32      Store selected bit in CF flag and complement */
			MOD_DECODE();
			if (IS_MODVIO()) {
				IF_X86_64(if (op_flags & F_REX_W) {
					temp = (u64)1 << (RD_REGQ() % 64);
do_btc_temp_q:
					do {
						value = RD_VIOQ();
					} while (vio_cmpxch_or_writel(&args->ma_args, vio_addr, value, value ^ temp, IS_ATOMIC()));
				} else) if (op_flags & F_OP16) {
					temp = (u16)1 << (RD_REGW() % 16);
do_btc_temp_w:
					do {
						value = RD_VIOW();
					} while (vio_cmpxch_or_writew(&args->ma_args, vio_addr, value, value ^ temp, IS_ATOMIC()));
				} else {
					temp = (u32)1 << (RD_REGL() % 32);
do_btc_temp_l:
					do {
						value = RD_VIOL();
					} while (vio_cmpxch_or_writel(&args->ma_args, vio_addr, value, value ^ temp, IS_ATOMIC()));
				}
				value &= temp;
				goto set_cf_is_value_nonzero;
			}
			break;


		case 0x0fb3:
			/* 0F B3      BTR r/m16, r16      Store selected bit in CF flag and clear */
			/* 0F B3      BTR r/m32, r32      Store selected bit in CF flag and clear */
			MOD_DECODE();
			if (IS_MODVIO()) {
				IF_X86_64(if (op_flags & F_REX_W) {
					temp = (u64)1 << (RD_REGQ() % 64);
do_btr_temp_q:
					do {
						value = RD_VIOQ();
					} while (vio_cmpxch_or_writeq(&args->ma_args, vio_addr, value, value & ~temp, IS_ATOMIC()));
				} else) if (op_flags & F_OP16) {
					temp = (u16)1 << (RD_REGW() % 16);
do_btr_temp_w:
					do {
						value = RD_VIOW();
					} while (vio_cmpxch_or_writew(&args->ma_args, vio_addr, value, value & ~temp, IS_ATOMIC()));
				} else {
					temp = (u32)1 << (RD_REGL() % 32);
do_btr_temp_l:
					do {
						value = RD_VIOL();
					} while (vio_cmpxch_or_writel(&args->ma_args, vio_addr, value, value & ~temp, IS_ATOMIC()));
				}
				value &= temp;
				goto set_cf_is_value_nonzero;
			}
			break;


		case 0x0fab:
			/* 0F AB      BTS r/m16, r16      Store selected bit in CF flag and set */
			/* 0F AB      BTS r/m32, r32      Store selected bit in CF flag and set */
			MOD_DECODE();
			if (IS_MODVIO()) {
				IF_X86_64(if (op_flags & F_REX_W) {
					temp = (u64)1 << (RD_REGQ() % 64);
do_bts_temp_q:
					do {
						value = RD_VIOQ();
					} while (vio_cmpxch_or_writeq(&args->ma_args, vio_addr, value, value | temp, IS_ATOMIC()));
				} else) if (op_flags & F_OP16) {
					temp = (u16)1 << (RD_REGW() % 16);
do_bts_temp_w:
					do {
						value = RD_VIOW();
					} while (vio_cmpxch_or_writew(&args->ma_args, vio_addr, value, value | temp, IS_ATOMIC()));
				} else {
					temp = (u32)1 << (RD_REGL() % 32);
do_bts_temp_l:
					do {
						value = RD_VIOL();
					} while (vio_cmpxch_or_writel(&args->ma_args, vio_addr, value, value | temp, IS_ATOMIC()));
				}
				value &= temp;
				goto set_cf_is_value_nonzero;
			}
			break;


		case 0x0fba:
			MOD_DECODE();
			value = *(u8 *)pc;
			value &= IF_X86_64((op_flags & F_REX_W) ? 0x3f : )(op_flags & F_OP16) ? 0xf : 0x1f;
			value = (uintptr_t)1 << value;
			pc += 1;
			if (!IS_MODVIO())
				break; /* All of these instructions required MODVIO */
			switch (mod.mi_reg) {

			case 4:
				/* 0F BA /4 ib      BT r/m16,imm8      Store selected bit in CF flag */
				/* 0F BA /4 ib      BT r/m32,imm8      Store selected bit in CF flag */
				IF_X86_64(if (op_flags & F_REX_W) {
					value &= RD_VIOQ();
				} else) if (op_flags & F_OP16) {
					value &= RD_VIOW();
				} else {
					value &= RD_VIOL();
				}
				goto set_cf_is_value_nonzero;

			case 5:
				/* 0F BA /5 ib      BTS r/m16,imm8      Store selected bit in CF flag and set */
				/* 0F BA /5 ib      BTS r/m32,imm8      Store selected bit in CF flag and set */
				temp = value;
#ifdef __x86_64__
				if (op_flags & F_REX_W)
					goto do_bts_temp_q;
#endif /* __x86_64__ */
				if (op_flags & F_OP16)
					goto do_bts_temp_w;
				goto do_bts_temp_l;

			case 6:
				/* 0F BA /6 ib      BTR r/m16,imm8      Store selected bit in CF flag and clear */
				/* 0F BA /6 ib      BTR r/m32,imm8      Store selected bit in CF flag and clear */
				temp = value;
#ifdef __x86_64__
				if (op_flags & F_REX_W)
					goto do_btr_temp_q;
#endif /* __x86_64__ */
				if (op_flags & F_OP16)
					goto do_btr_temp_w;
				goto do_btr_temp_l;

			case 7:
				/* 0F BA /7 ib      BTC r/m16,imm8      Store selected bit in CF flag and complement */
				/* 0F BA /7 ib      BTC r/m32,imm8      Store selected bit in CF flag and complement */
				temp = value;
#ifdef __x86_64__
				if (op_flags & F_REX_W)
					goto do_btc_temp_q;
#endif /* __x86_64__ */
				if (op_flags & F_OP16)
					goto do_btc_temp_w;
				goto do_btc_temp_l;

			default: goto undefined_instruction;
			}
			break;


		case 0xfe:
			MOD_DECODE();
			switch (mod.mi_reg) {

			case 0:
				/* FE /0      INC r/m8      Increment r/m byte by 1 */
				if (IS_MODVIO()) {
					temp = RD_PFLAGS();
					temp &= ~(OF | SF | ZF | AF | PF);
					value = vio_addw(&args->ma_args, vio_addr, 1, IS_ATOMIC());
					temp |= __cmpb((u8)value, 0) & (OF | SF | ZF | AF | PF);
					WR_PFLAGS(temp);
					goto done;
				}
				break;

			case 1:
				/* FE /1      DEC r/m8      Decrement r/m8 by 1 */
				if (IS_MODVIO()) {
					temp = RD_PFLAGS();
					temp &= ~(OF | SF | ZF | AF | PF);
					value = vio_subw(&args->ma_args, vio_addr, 1, IS_ATOMIC());
					temp |= __cmpb((u8)value, 0) & (OF | SF | ZF | AF | PF);
					WR_PFLAGS(temp);
					goto done;
				}
				break;

			default: goto undefined_instruction;
			}
			break;


		case 0xff:
			MOD_DECODE();
			switch (mod.mi_reg) {

			case 0:
				/* FF /0      INC r/m16      Increment r/m word by 1 */
				/* FF /0      INC r/m32      Increment r/m doubleword by 1 */
				if (IS_MODVIO()) {
					uintptr_t flags = RD_PFLAGS();
					flags &= ~(OF | SF | ZF | AF | PF);
					IF_X86_64(if (op_flags & F_REX_W) {
						u64 value = vio_addq(&args->ma_args, vio_addr, 1, IS_ATOMIC());
						flags |= __cmpq(value, 0) & (OF | SF | ZF | AF | PF);
					} else) if (op_flags & F_OP16) {
						u16 value = vio_addw(&args->ma_args, vio_addr, 1, IS_ATOMIC());
						flags |= __cmpw(value, 0) & (OF | SF | ZF | AF | PF);
					} else {
						u32 value = vio_addl(&args->ma_args, vio_addr, 1, IS_ATOMIC());
						flags |= __cmpl(value, 0) & (OF | SF | ZF | AF | PF);
					}
					WR_PFLAGS(flags);
					goto done;
				}
				break;

			case 1:
				/* FF /1      DEC r/m16      Decrement r/m16 by 1 */
				/* FF /1      DEC r/m32      Decrement r/m32 by 1 */
				if (IS_MODVIO()) {
					uintptr_t flags = RD_PFLAGS();
					flags &= ~(OF | SF | ZF | AF | PF);
					IF_X86_64(if (op_flags & F_REX_W) {
						u64 value = vio_subq(&args->ma_args, vio_addr, 1, IS_ATOMIC());
						flags |= __cmpq(value, 0) & (OF | SF | ZF | AF | PF);
					} else) if (op_flags & F_OP16) {
						u16 value = vio_subw(&args->ma_args, vio_addr, 1, IS_ATOMIC());
						flags |= __cmpw(value, 0) & (OF | SF | ZF | AF | PF);
					} else {
						u32 value = vio_subl(&args->ma_args, vio_addr, 1, IS_ATOMIC());
						flags |= __cmpl(value, 0) & (OF | SF | ZF | AF | PF);
					}
					WR_PFLAGS(flags);
					goto done;
				}
				break;

			case 2:
				/* FF /2      CALL r/m16      Call near, absolute indirect, address given in r/m16 */
				/* FF /2      CALL r/m32      Call near, absolute indirect, address given in r/m32 */
				if (op_flags & F_OP16)
					break; /* 16-bit calls aren't emulated. */
				if (IS_MODVIO()) {
					uintptr_t target_pc, sp;
					target_pc = RD_VIOL();
					value = irregs_rdip(&state->ics_irregs);
#ifndef __x86_64__
					if (!isuser) {
						irregs_wrip(&state->ics_irregs, target_pc);
						goto do_push_value_2_4_kernel_sp;
					}
#endif /* !__x86_64__ */
					sp = RD_USP();
					IF_X86_64(if (op_flags & F_REX_W) {
						validate_writable((byte_t *)sp - 8, 8);
						((u64 *)sp)[-1] = (u64)value;
						WR_USP(sp - 8);
					} else) {
						validate_writable((byte_t *)sp - 4, 4);
						((u32 *)sp)[-1] = (u32)value;
						WR_USP(sp - 4);
					}
					irregs_wrip(&state->ics_irregs, target_pc);
					goto done;
				} else NIF_X86_64(if (isuser)) {
					/* VIO target stack. */
					uintptr_t target_pc = RD_RML();
					uintptr_t sp = RD_USP();
					IF_X86_64(if (op_flags & F_REX_W) {
						if (sp - 8 == cr2) {
							if (isuser)
								validate_writable((byte_t *)sp - 8, 8);
							WR_VIOQ(irregs_rdip(&state->ics_irregs));
							irregs_wrip(&state->ics_irregs, target_pc);
							WR_USP(sp - 8);
							goto done;
						}
					} else) {
						if (sp - 4 == cr2) {
							IF_X86_64(if (isuser)) {
								validate_writable((byte_t *)sp - 4, 4);
							}
							WR_VIOL((u32)irregs_rdip(&state->ics_irregs));
							irregs_wrip(&state->ics_irregs, target_pc);
							WR_USP(sp - 4);
							goto done;
						}
					}
				}
				break;

			case 4:
				/* FF /4      JMP r/m16      Jump near, absolute indirect, address given in r/m16 */
				/* FF /4      JMP r/m32      Jump near, absolute indirect, address given in r/m32 */
				if (IS_MODVIO()) {
					uintptr_t target_pc;
					IF_X86_64(if (op_flags & F_REX_W) {
						target_pc = RD_VIOQ();
					} else) if (op_flags & F_OP16) {
						target_pc = RD_VIOW();
					} else {
						target_pc = RD_VIOL();
					}
					irregs_wrip(&state->ics_irregs, target_pc);
					goto done;
				}
				break;

			case 6:
				/* FF /6      PUSH r/m16      Push r/m16 */
				/* FF /6      PUSH r/m32      Push r/m32 */
				if (IS_MODVIO()) {
					/* Push VIO value into stack */
					uintptr_t sp;
					value = op_flags & F_OP16
					        ? RD_VIOW()
					        : RD_VIOL();
#ifndef __x86_64__
					if (!isuser)
						goto do_push_value_2_4_kernel_sp;
#endif /* !__x86_64__ */
					sp = RD_USP();
					IF_X86_64(if (op_flags & F_REX_W) {
						if (isuser)
							validate_writable((byte_t *)sp - 8, 8);
						((u64 *)sp)[-1] = (u64)value;
						WR_USP(sp - 8);
					} else) if (op_flags & F_OP16) {
						IF_X86_64(if (isuser)) {
							validate_writable((byte_t *)sp - 2, 2);
						}
						((u16 *)sp)[-1] = (u16)value;
						WR_USP(sp - 2);
					} else {
						IF_X86_64(if (isuser)) {
							validate_writable((byte_t *)sp - 4, 4);
						}
						((u32 *)sp)[-1] = (u32)value;
						WR_USP(sp - 4);
					}
					goto done;
				}
				NIF_X86_64(if (isuser)) {
					/* Push regular value onto user-space VIO stack */
					uintptr_t sp;
user_push_value_vio_stack_2_4_8:
					sp = RD_USP();
					IF_X86_64(if (op_flags & F_REX_W) {
						if (sp - 8 == cr2) {
							WR_VIOQ(RD_RMQ());
							WR_USP(sp - 8);
							goto done;
						}
					} else) if (op_flags & F_OP16) {
						if (sp - 2 == cr2) {
							WR_VIOW(RD_RMW());
							WR_USP(sp - 2);
							goto done;
						}
					} else {
						if (sp - 4 == cr2) {
							WR_VIOL(RD_RML());
							WR_USP(sp - 4);
							goto done;
						}
					}
				}
				break;

			default: goto undefined_instruction;
			}
			break;


		case 0x50 ... 0x57:
			/* 50+rw      PUSH r16      Push r16. */
			/* 50+rd      PUSH r32      Push r32. */
			NIF_X86_64(if (isuser)) {
				value = x86_icpustate_get(state, opcode - 0x50);
				goto user_push_value_vio_stack_2_4_8;
			}
			break;

		case 0x6a:
			/* 6A      PUSH imm8      Push imm8. */
			value = (uintptr_t)*(u8 *)pc;
			pc += 1;
			NIF_X86_64(if (isuser)) {
				goto user_push_value_vio_stack_2_4_8;
			}
			break;


		case 0x68:
			/* 68      PUSH imm16      Push imm16. */
			/* 68      PUSH imm32      Push imm32. */
			if (op_flags & F_OP16) {
				value = (uintptr_t)*(u16 *)pc;
				pc += 2;
			} else {
				value = (uintptr_t)*(u32 *)pc;
				pc += 4;
			}
			NIF_X86_64(if (isuser)) {
				goto user_push_value_vio_stack_2_4_8;
			}
			break;


#ifndef __x86_64__
		case 0x06:
			/* 0E      PUSH ES      Push ES. */
			NIF_X86_64(if (isuser)) {
				value = IFELSE_X86_64(state->ics_es16, __rdes());
				goto user_push_value_vio_stack_2_4_8;
			}
			break;
#endif /* !__x86_64__ */


#ifndef __x86_64__
		case 0x0e:
			/* 0E      PUSH CS      Push CS. */
			NIF_X86_64(if (isuser)) {
				value = irregs_rdcs(&state->ics_irregs);
				goto user_push_value_vio_stack_2_4_8;
			}
			break;
#endif /* !__x86_64__ */


#ifndef __x86_64__
		case 0x16:
			/* 16      PUSH SS      Push SS. */
			NIF_X86_64(if (isuser)) {
				value = IFELSE_X86_64(state->ics_irregs_u.ir_ss16,
				                      irregs_rdss(&state->ics_irregs));
				goto user_push_value_vio_stack_2_4_8;
			}
			break;
#endif /* !__x86_64__ */


#ifndef __x86_64__
		case 0x1e:
			/* 1E      PUSH DS      Push DS. */
			NIF_X86_64(if (isuser)) {
				value = IFELSE_X86_64(state->ics_ds16, __rdds());
				goto user_push_value_vio_stack_2_4_8;
			}
			break;
#endif /* !__x86_64__ */


		case 0x0fa0:
			/* 0F A0      PUSH FS      Push FS. */
			if (isuser) {
				value = IFELSE_X86_64(state->ics_fs16, __rdfs());
				goto user_push_value_vio_stack_2_4_8;
			}
			break;


		case 0x0fa8:
			/* 0F A8      PUSH GS      Push GS. */
			if (isuser) {
				value = __rdgs();
				goto user_push_value_vio_stack_2_4_8;
			}
			break;


		case 0x9c:
			/* PUSHF      Push lower 16 bits of EFLAGS.
			 * PUSHFD     Push EFLAGS. */
			NIF_X86_64(if (isuser)) {
				value = irregs_rdflags(&state->ics_irregs);
#ifndef __x86_64__
				if (value & EFLAGS_VM) {
					/* TODO: Set EFLAGS.IF to what VM86 mode should be thinking. */
				}
#endif /* !__x86_64__ */
				value &= 0xfcffff;
				if (op_flags & F_OP16)
					value &= 0xffff;
				goto user_push_value_vio_stack_2_4_8;
			}
			break;


#ifndef __x86_64__
		case 0x60:
			/* 60      PUSHA      Push AX, CX, DX, BX, original SP, BP, SI, and DI.
			 * 60      PUSHAD     Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI. */
			if (isuser) {
				u32 mask = (u32)-1;
				validate_writable((byte_t *)state->ics_irregs_u.ir_esp - 32, 32);
				if (op_flags & F_OP16)
					mask = 0xffff;
				/* NOTE: Use regular writes to allow for recursion, thus functioning properly,
				 *       even when only part of the target stack range is located within VIO
				 *       memory. */
				writel(&((u32 *)state->ics_irregs_u.ir_esp)[-1], state->ics_gpregs.gp_eax & mask);
				writel(&((u32 *)state->ics_irregs_u.ir_esp)[-1], state->ics_gpregs.gp_ecx & mask);
				writel(&((u32 *)state->ics_irregs_u.ir_esp)[-1], state->ics_gpregs.gp_edx & mask);
				writel(&((u32 *)state->ics_irregs_u.ir_esp)[-1], state->ics_gpregs.gp_ebx & mask);
				writel(&((u32 *)state->ics_irregs_u.ir_esp)[-1], state->ics_irregs_u.ir_esp & mask);
				writel(&((u32 *)state->ics_irregs_u.ir_esp)[-1], state->ics_gpregs.gp_ebp & mask);
				writel(&((u32 *)state->ics_irregs_u.ir_esp)[-1], state->ics_gpregs.gp_esi & mask);
				writel(&((u32 *)state->ics_irregs_u.ir_esp)[-1], state->ics_gpregs.gp_edi & mask);
				state->ics_irregs_u.ir_esp -= 32;
				goto done;
			}
			break;
#endif /* !__x86_64__ */


		case 0x8f:
			MOD_DECODE();
			switch (mod.mi_reg) {

			case 0:
				/* 8F /0      POP r/m16      Pop top of stack into m16; increment stack pointer */
				/* 8F /0      POP r/m32      Pop top of stack into m32; increment stack pointer */
				if (IS_MODVIO()) {
					uintptr_t sp;
					/* Pop stack into VIO value */
#ifndef __x86_64__
					if (!isuser)
						goto do_pop_value_2_4_kernel_sp;
#endif /* !__x86_64__ */
					sp = RD_USP();
					IF_X86_64(if (op_flags & F_REX_W) {
						u64 value;
						IF_X86_64(if (isuser)) {
							validate_readable((byte_t *)sp, 8);
						}
						value = ((u64 *)sp)[0];
						WR_VIOQ((u64)value);
						WR_USP(sp + 8);
					} else) if (op_flags & F_OP16) {
						u16 value;
						IF_X86_64(if (isuser)) {
							validate_readable((byte_t *)sp, 2);
						}
						value = ((u16 *)sp)[0];
						WR_VIOW((u16)value);
						WR_USP(sp + 2);
					} else {
						u32 value;
						IF_X86_64(if (isuser)) {
							validate_readable((byte_t *)sp, 4);
						}
						value = ((u32 *)sp)[0];
						WR_VIOL((u32)value);
						WR_USP(sp + 4);
					}
					goto done;
				}
				if (NIF_X86_64(isuser &&) RD_USP() == cr2) {
					/* Pop user-space VIO stack into regular memory */
					IF_X86_64(if (op_flags & F_REX_W) {
						WR_RMQ(RD_VIOQ());
						WR_USP(cr2 + 8);
					} else) if (op_flags & F_OP16) {
						WR_RMW(RD_VIOW());
						WR_USP(cr2 + 2);
					} else {
						WR_RML(RD_VIOL());
						WR_USP(cr2 + 4);
					}
					goto done;
				}
				break;

			default: goto undefined_instruction;
			}
			break;



		case 0x58 ... 0x5f:
			/* 58+ rw      POP r16      Pop top of stack into r16; increment stack pointer.
			 * 58+ rd      POP r32      Pop top of stack into r32; increment stack pointer. */
			if (NIF_X86_64(isuser &&) RD_USP() == cr2) {
				uintptr_t value;
				IF_X86_64(if (op_flags & F_REX_W) {
					value = RD_VIOQ();
					WR_USP(cr2 + 8);
				} else) if (op_flags & F_OP16) {
					value = RD_VIOW();
					WR_USP(cr2 + 2);
				} else {
					value = RD_VIOL();
					WR_USP(cr2 + 4);
				}
				x86_icpustate_set(state, opcode - 0x58, value);
				goto done;
			}
			break;


		case 0x1f:
			/* 1F      POP DS      Pop top of stack into DS; increment stack pointer. */
			if (NIF_X86_64(isuser &&) RD_USP() == cr2) {
				u16 value;
				IF_X86_64(if (op_flags & F_REX_W) {
					value = (u16)RD_VIOQ();
					WR_USP(cr2 + 8);
				} else) if (op_flags & F_OP16) {
					value = (u16)RD_VIOW();
					WR_USP(cr2 + 2);
				} else {
					value = (u16)RD_VIOL();
					WR_USP(cr2 + 4);
				}
#ifndef __x86_64__
				if (irregs_isvm86(&state->ics_irregs)) {
					state->ics_irregs_v.ir_ds = value;
				} else
#endif /* !__x86_64__ */
				{
					if (!SEGMENT_IS_VALID_USERDATA(value) IF_X86_64(&&isuser)) {
						THROW(E_INVALID_ARGUMENT_BAD_VALUE,
						      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
						      X86_REGISTER_SEGMENT_DS, value);
					}
					icpustate_setds_novm86(state, value);
				}
				goto done;
			}
			break;


		case 0x07:
			/* 07      POP ES      Pop top of stack into ES; increment stack pointer. */
			if (NIF_X86_64(isuser &&) RD_USP() == cr2) {
				u16 value;
				IF_X86_64(if (op_flags & F_REX_W) {
					value = (u16)RD_VIOQ();
					WR_USP(cr2 + 8);
				} else) if (op_flags & F_OP16) {
					value = (u16)RD_VIOW();
					WR_USP(cr2 + 2);
				} else {
					value = (u16)RD_VIOL();
					WR_USP(cr2 + 4);
				}
#ifndef __x86_64__
				if (irregs_isvm86(&state->ics_irregs)) {
					state->ics_irregs_v.ir_es = value;
				} else
#endif /* !__x86_64__ */
				{
					if (!SEGMENT_IS_VALID_USERDATA(value) IF_X86_64(&&isuser)) {
						THROW(E_INVALID_ARGUMENT_BAD_VALUE,
						      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
						      X86_REGISTER_SEGMENT_ES, value);
					}
					icpustate_setes_novm86(state, value);
				}
				goto done;
			}
			break;


		case 0x17:
			/* 17      POP SS      Pop top of stack into SS; increment stack pointer. */
			if (NIF_X86_64(isuser &&) RD_USP() == cr2) {
				u16 value;
				IF_X86_64(if (op_flags & F_REX_W) {
					value = (u16)RD_VIOQ();
					WR_USP(cr2 + 8);
				} else) if (op_flags & F_OP16) {
					value = (u16)RD_VIOW();
					WR_USP(cr2 + 2);
				} else {
					value = (u16)RD_VIOL();
					WR_USP(cr2 + 4);
				}
				if (!SEGMENT_IS_VALID_USERDATA(value)
				    IF_X86_64(&&isuser)
				    NIF_X86_64(&&!irregs_isvm86(&state->ics_irregs))) {
					THROW(E_INVALID_ARGUMENT_BAD_VALUE,
					      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
					      X86_REGISTER_SEGMENT_SS, value);
				}
				IFELSE_X86_64(state->ics_irregs_u.ir_ss = value,
				              irregs_wrss(&state->ics_irregs, value));
				goto done;
			}
			break;


		case 0x0fa1:
			/* 0F A1      POP FS      Pop top of stack into FS; increment stack pointer. */
			if (NIF_X86_64(isuser &&) RD_USP() == cr2) {
				u16 value;
				IF_X86_64(if (op_flags & F_REX_W) {
					value = (u16)RD_VIOQ();
					WR_USP(cr2 + 8);
				} else) if (op_flags & F_OP16) {
					value = (u16)RD_VIOW();
					WR_USP(cr2 + 2);
				} else {
					value = (u16)RD_VIOL();
					WR_USP(cr2 + 4);
				}
#ifndef __x86_64__
				if (irregs_isvm86(&state->ics_irregs)) {
					state->ics_irregs_v.ir_fs = value;
				} else
#endif /* !__x86_64__ */
				{
					if (!SEGMENT_IS_VALID_USERDATA(value) IF_X86_64(&&isuser)) {
						THROW(E_INVALID_ARGUMENT_BAD_VALUE,
						      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
						      X86_REGISTER_SEGMENT_FS, value);
					}
					icpustate_setfs_novm86(state, value);
				}
				goto done;
			}
			break;


		case 0x0fa9:
			/* 0F A9      POP GS      Pop top of stack into GS; increment stack pointer. */
			if (NIF_X86_64(isuser &&) RD_USP() == cr2) {
				u16 value;
				IF_X86_64(if (op_flags & F_REX_W) {
					value = (u16)RD_VIOQ();
					WR_USP(cr2 + 8);
				} else) if (op_flags & F_OP16) {
					value = (u16)RD_VIOW();
					WR_USP(cr2 + 2);
				} else {
					value = (u16)RD_VIOL();
					WR_USP(cr2 + 4);
				}
#ifndef __x86_64__
				if (irregs_isvm86(&state->ics_irregs)) {
					state->ics_irregs_v.ir_gs = value;
				} else
#endif /* !__x86_64__ */
				{
					if (!SEGMENT_IS_VALID_USERDATA(value) IF_X86_64(&&isuser)) {
						THROW(E_INVALID_ARGUMENT_BAD_VALUE,
						      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
						      X86_REGISTER_SEGMENT_GS, value);
					}
					icpustate_setgs_novm86(state, value);
				}
				goto done;
			}
			break;

		case 0x0fae:
			MOD_DECODE();
			switch (mod.mi_reg) {

			case 7:
				/* 0F AE /7      CLFLUSH m8      Flushes cache line containing m8 */
				if (IS_MODVIO())
					goto done;
				break;

			default: goto undefined_instruction;
			}
			break;

#define DEFINE_MOVcc(opcode, cond_expr)                 \
		case opcode:                                    \
			MOD_DECODE();                               \
			if (IS_MODVIO()) {                          \
				if (cond_expr) {                        \
					IF_X86_64(if (op_flags & F_REX_W) { \
						u64 value = RD_VIOQ();          \
						WR_REGQ(value);                 \
					} else) if (op_flags & F_OP16) {    \
						u16 value = RD_VIOW();          \
						WR_REGW(value);                 \
					} else {                            \
						u32 value = RD_VIOL();          \
						WR_REGL(value);                 \
					}                                   \
				}                                       \
				goto done;                              \
			}                                           \
			break;                                      \
		case opcode + 0x50:                             \
			MOD_DECODE();                               \
			if (IS_MODVIO()) {                          \
				WR_VIOB((cond_expr) ? 1 : 0);           \
				goto done;                              \
			}                                           \
			break;


		/* 0F 40      CMOVO r16, r/m16        Move if overflow (OF=1) */
		/* 0F 40      CMOVO r32, r/m32        Move if overflow (OF=1) */
		DEFINE_MOVcc(0x0f40,RD_PFLAGS() & OF)

		/* 0F 41      CMOVNO r16, r/m16       Move if not overflow (OF=0) */
		/* 0F 41      CMOVNO r32, r/m32       Move if not overflow (OF=0) */
		DEFINE_MOVcc(0x0f41,!(RD_PFLAGS() & OF))

		/* 0F 42      CMOVB r16, r/m16        Move if below (CF=1) */
		/* 0F 42      CMOVB r32, r/m32        Move if below (CF=1) */
		/* 0F 42      CMOVC r16, r/m16        Move if carry (CF=1) */
		/* 0F 42      CMOVC r32, r/m32        Move if carry (CF=1) */
		/* 0F 42      CMOVNAE r16, r/m16      Move if not above or equal (CF=1) */
		/* 0F 42      CMOVNAE r32, r/m32      Move if not above or equal (CF=1) */
		DEFINE_MOVcc(0x0f42,RD_PFLAGS() & CF)

		/* 0F 43      CMOVAE r16, r/m16       Move if above or equal (CF=0) */
		/* 0F 43      CMOVAE r32, r/m32       Move if above or equal (CF=0) */
		/* 0F 43      CMOVNB r16, r/m16       Move if not below (CF=0) */
		/* 0F 43      CMOVNB r32, r/m32       Move if not below (CF=0) */
		/* 0F 43      CMOVNC r16, r/m16       Move if not carry (CF=0) */
		/* 0F 43      CMOVNC r32, r/m32       Move if not carry (CF=0) */
		DEFINE_MOVcc(0x0f43,!(RD_PFLAGS() & CF))

		/* 0F 44      CMOVE r16, r/m16        Move if equal (ZF=1) */
		/* 0F 44      CMOVE r32, r/m32        Move if equal (ZF=1) */
		/* 0F 44      CMOVZ r16, r/m16        Move if zero (ZF=1) */
		/* 0F 44      CMOVZ r32, r/m32        Move if zero (ZF=1) */
		DEFINE_MOVcc(0x0f44,RD_PFLAGS() & ZF)

		/* 0F 45      CMOVNE r16, r/m16       Move if not equal (ZF=0) */
		/* 0F 45      CMOVNE r32, r/m32       Move if not equal (ZF=0) */
		/* 0F 45      CMOVNZ r16, r/m16       Move if not zero (ZF=0) */
		/* 0F 45      CMOVNZ r32, r/m32       Move if not zero (ZF=0) */
		DEFINE_MOVcc(0x0f45,!(RD_PFLAGS() & ZF))

		/* 0F 46      CMOVBE r16, r/m16       Move if below or equal (CF=1 or ZF=1) */
		/* 0F 46      CMOVBE r32, r/m32       Move if below or equal (CF=1 or ZF=1) */
		/* 0F 46      CMOVNA r16, r/m16       Move if not above (CF=1 or ZF=1) */
		/* 0F 46      CMOVNA r32, r/m32       Move if not above (CF=1 or ZF=1) */
		DEFINE_MOVcc(0x0f46,RD_PFLAGS() & (CF|ZF))

		/* 0F 47      CMOVA r16, r/m16        Move if above (CF=0 and ZF=0) */
		/* 0F 47      CMOVA r32, r/m32        Move if above (CF=0 and ZF=0) */
		/* 0F 47      CMOVNBE r16, r/m16      Move if not below or equal (CF=0 and ZF=0) */
		/* 0F 47      CMOVNBE r32, r/m32      Move if not below or equal (CF=0 and ZF=0) */
		DEFINE_MOVcc(0x0f47,!(RD_PFLAGS() & (CF|ZF)))

		/* 0F 48      CMOVS r16, r/m16        Move if sign (SF=1) */
		/* 0F 48      CMOVS r32, r/m32        Move if sign (SF=1) */
		DEFINE_MOVcc(0x0f48,RD_PFLAGS() & SF)

		/* 0F 49      CMOVNS r16, r/m16       Move if not sign (SF=0) */
		/* 0F 49      CMOVNS r32, r/m32       Move if not sign (SF=0) */
		DEFINE_MOVcc(0x0f49,!(RD_PFLAGS() & SF))

		/* 0F 4A      CMOVP r16, r/m16        Move if parity (PF=1) */
		/* 0F 4A      CMOVP r32, r/m32        Move if parity (PF=1) */
		/* 0F 4A      CMOVPE r16, r/m16       Move if parity even (PF=1) */
		/* 0F 4A      CMOVPE r32, r/m32       Move if parity even (PF=1) */
		DEFINE_MOVcc(0x0f4a,RD_PFLAGS() & PF)

		/* 0F 4B      CMOVNP r16, r/m16       Move if not parity (PF=0) */
		/* 0F 4B      CMOVNP r32, r/m32       Move if not parity (PF=0) */
		/* 0F 4B      CMOVPO r16, r/m16       Move if parity odd (PF=0) */
		/* 0F 4B      CMOVPO r32, r/m32       Move if parity odd (PF=0) */
		DEFINE_MOVcc(0x0f4b,!(RD_PFLAGS() & PF))

		/* 0F 4C      CMOVL r16, r/m16        Move if less (SF<>OF) */
		/* 0F 4C      CMOVL r32, r/m32        Move if less (SF<>OF) */
		/* 0F 4C      CMOVNGE r16, r/m16      Move if not greater or equal (SF<>OF) */
		/* 0F 4C      CMOVNGE r32, r/m32      Move if not greater or equal (SF<>OF) */
		DEFINE_MOVcc(0x0f4c,!!(RD_PFLAGS() & SF) != !!(RD_PFLAGS() & OF))

		/* 0F 4D      CMOVGE r16, r/m16       Move if greater or equal (SF=OF) */
		/* 0F 4D      CMOVGE r32, r/m32       Move if greater or equal (SF=OF) */
		/* 0F 4D      CMOVNL r16, r/m16       Move if not less (SF=OF) */
		/* 0F 4D      CMOVNL r32, r/m32       Move if not less (SF=OF) */
		DEFINE_MOVcc(0x0f4d,!!(RD_PFLAGS() & SF) == !!(RD_PFLAGS() & OF))

		/* 0F 4E      CMOVLE r16, r/m16       Move if less or equal (ZF=1 or SF<>OF) */
		/* 0F 4E      CMOVLE r32, r/m32       Move if less or equal (ZF=1 or SF<>OF) */
		/* 0F 4E      CMOVNG r16, r/m16       Move if not greater (ZF=1 or SF<>OF) */
		/* 0F 4E      CMOVNG r32, r/m32       Move if not greater (ZF=1 or SF<>OF) */
		DEFINE_MOVcc(0x0f4e,(RD_PFLAGS() & ZF) || (!!(RD_PFLAGS() & SF) != !!(RD_PFLAGS() & OF)))

		/* 0F 4F      CMOVG r16, r/m16        Move if greater (ZF=0 and SF=OF) */
		/* 0F 4F      CMOVG r32, r/m32        Move if greater (ZF=0 and SF=OF) */
		/* 0F 4F      CMOVNLE r16, r/m16      Move if not less or equal (ZF=0 and SF=OF) */
		/* 0F 4F      CMOVNLE r32, r/m32      Move if not less or equal (ZF=0 and SF=OF) */
		DEFINE_MOVcc(0x0f4f,!(RD_PFLAGS() & ZF) && (!!(RD_PFLAGS() & SF) == !!(RD_PFLAGS() & OF)))

#undef DEFINE_MOVcc
#endif




#if !defined(__INTELLISENSE__) || 0
		case 0x0fb0:
			/* 0F B0 /r      CMPXCHG r/m8,r8      Compare AL with r/m8. If equal, ZF is set and r8 is loaded into r/m8. Else, clear ZF and load r/m8 into AL */
			MOD_DECODE();
			if (IS_MODVIO()) {
				u8 temp  = RD_AL();
				u8 value = vio_cmpxchb(&args->ma_args, vio_addr, temp, RD_REGB(), IS_ATOMIC());
				SET_PFLAGS(__cmpb(temp, value), ZF | CF | PF | AF | SF | OF);
				goto done;
			}
			break;


		case 0x0fb1:
			/* 0F B1 /r      CMPXCHG r/m16,r16    Compare AX with r/m16. If equal, ZF is set and r16 is loaded into r/m16. Else, clear ZF and load r/m16 into AX */
			/* 0F B1 /r      CMPXCHG r/m32,r32    Compare EAX with r/m32. If equal, ZF is set and r32 is loaded into r/m32. Else, clear ZF and load r/m32 into EAX */
			MOD_DECODE();
			if (IS_MODVIO()) {
				IF_X86_64(if (op_flags & F_REX_W) {
					u64 temp  = RD_RAX();
					u64 value = vio_cmpxchq(&args->ma_args, vio_addr, temp, RD_REGQ(), IS_ATOMIC());
					SET_PFLAGS(__cmpq(temp, value), ZF | CF | PF | AF | SF | OF);
				} else) if (op_flags & F_OP16) {
					u16 temp  = RD_AX();
					u16 value = vio_cmpxchw(&args->ma_args, vio_addr, temp, RD_REGW(), IS_ATOMIC());
					SET_PFLAGS(__cmpw(temp, value), ZF | CF | PF | AF | SF | OF);
				} else {
					u32 temp  = RD_EAX();
					u32 value = vio_cmpxchl(&args->ma_args, vio_addr, temp, RD_REGL(), IS_ATOMIC());
					SET_PFLAGS(__cmpl(temp, value), ZF | CF | PF | AF | SF | OF);
				}
				goto done;
			}
			break;


		case 0x0fc7:
			MOD_DECODE();
			switch (mod.mi_reg) {

			case 1:
				/* 0F C7 /1 m64      CMPXCHG8B m64      Compare EDX:EAX with m64. If equal, set ZF and load ECX:EBX into m64. Else, clear ZF and load m64 into EDX:EAX */
				if (IS_MODVIO()) {
					u64 old_value;
					u64 real_old_value;
					old_value = ((u64)RD_EDX() << 32) |
					            ((u64)RD_EAX());
					real_old_value = vio_cmpxchq(&args->ma_args, vio_addr,
					                             old_value,
					                             ((u64)RD_ECX() << 32) |
					                             ((u64)RD_EBX()),
					                             IS_ATOMIC());
					if (real_old_value == old_value) {
						SET_PFLAGS(ZF, ZF);
					} else {
						SET_PFLAGS(0, ZF);
						WR_EDX((u32)(real_old_value >> 32));
						WR_EAX((u32)real_old_value);
					}
					goto done;
				}
				break;

			default: goto undefined_instruction;
			}
			break;


		case 0xf6: {
			u8 value;
			MOD_DECODE();
			if (!IS_MODVIO())
				break;
again_0xf6:
			value = RD_VIOB();
			switch (mod.mi_reg) {

			case 0:
			case 1: /* Undocumented alias */
			{
				u8 temp;
				/* F6 /0 ib      TEST r/m8,imm8      AND imm8 with r/m8; set SF, ZF, PF according to result */
				temp = *(u8 *)pc;
				pc += 1;
				SET_PFLAGS(__testb(value, temp), OF | CF | SF | ZF | PF);
			}	goto done;

			case 2:
				/* F6 /2      NOT r/m8      Reverse each bit of r/m8 */
				if (vio_cmpxch_or_writeb(&args->ma_args, vio_addr, value,
				                         ~value, IS_ATOMIC()) != value)
					goto again_0xf6;
				goto done;

			case 3:
				/* F6 /3      NEG r/m8      Two's complement negate r/m8 */
				if (vio_cmpxch_or_writeb(&args->ma_args, vio_addr, value,
				                         0 - value, IS_ATOMIC()) != value)
					goto again_0xf6;
				temp = RD_PFLAGS() & ~(CF | OF | SF | ZF | AF | PF);
				if (value)
					temp |= CF;
				temp |= __cmpb(value, 0) & (OF | SF | ZF | AF | PF);
				WR_PFLAGS(temp);
				goto done;

			case 4: {
				u16 res;
				/* F6 /4      MUL r/m8      Unsigned multiply (AX = AL * r/m8) */
				__asm__("mulb %b3\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (temp)
				        , "=a" (res)
				        : "a" (RD_AL())
				        , "q" (value)
				        : "cc");
				WR_AX(res);
				SET_PFLAGS(temp, CF | OF);
			}	goto done;

			case 5: {
				u16 res;
				/* F6 /5      IMUL r/m8      AX = AL * r/m byte */
				__asm__("imulb %b3\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (temp)
				        , "=a" (res)
				        : "a" (RD_AL())
				        , "q" (value)
				        : "cc");
				WR_AX(res);
				SET_PFLAGS(temp, CF | OF);
			}	goto done;

			case 6: {
				u16 temp;
				/* F6 /6      DIV r/m8      Unsigned divide AX by r/m8, with result stored in AL = Quotient, AH = Remainder */
				temp = RD_AX();
				WR_AX(((u16)((u8)(temp / value)) |
				       (u16)((u8)(temp % value)) << 8));
			}	goto done;

			case 7: {
				s16 temp;
				/* F6 /7      IDIV r/m8      Signed divide AX by r/m8, with result stored in AL = Quotient, AH = Remainder */
				temp = (s16)RD_AX();
				WR_AX(((u16)((u8)(temp / (s8)value)) |
				       (u16)((u8)(temp % (s8)value)) << 8));
			}	goto done;

			default: goto undefined_instruction;
			}
		}	break;


		case 0xf7:
			MOD_DECODE();
			if (!IS_MODVIO())
				break;
again_0xf7:
			switch (mod.mi_reg) {

			case 0:
			case 1: /* Undocumented alias */
			{
				/* F7 /0 iw      TEST r/m16,imm16      AND imm16 with r/m16; set SF, ZF, PF according to result */
				/* F7 /0 id      TEST r/m32,imm32      AND imm32 with r/m32; set SF, ZF, PF according to result */
				enum { EFLAGS_MASK = OF | CF | SF | ZF | PF };
				IF_X86_64(if (op_flags & F_REX_W) {
					u64 value = RD_VIOQ();
					u64 temp  = (u64)(s64)*(s32 *)pc;
					pc += 8;
					SET_PFLAGS(__testq(value, temp), EFLAGS_MASK);
				} else) if (op_flags & F_OP16) {
					u16 value = RD_VIOW();
					u16 temp  = *(u16 *)pc;
					pc += 2;
					SET_PFLAGS(__testw(value, temp), EFLAGS_MASK);
				} else {
					u32 value = RD_VIOL();
					u32 temp  = *(u32 *)pc;
					pc += 4;
					SET_PFLAGS(__testl(value, temp), EFLAGS_MASK);
				}
			}	goto done;

			case 2:
				/* F7 /2      NOT r/m16      Reverse each bit of r/m16 */
				/* F7 /2      NOT r/m32      Reverse each bit of r/m32 */
				IF_X86_64(if (op_flags & F_REX_W) {
					u64 value = RD_VIOQ();
					if (vio_cmpxch_or_writeq(&args->ma_args, vio_addr, value, ~value, IS_ATOMIC()) != value)
						goto again_0xf7;
				} else) if (op_flags & F_OP16) {
					u16 value = RD_VIOW();
					if (vio_cmpxch_or_writew(&args->ma_args, vio_addr, value, ~value, IS_ATOMIC()) != value)
						goto again_0xf7;
				} else {
					u32 value = RD_VIOL();
					if (vio_cmpxch_or_writel(&args->ma_args, vio_addr, value, ~value, IS_ATOMIC()) != value)
						goto again_0xf7;
				}
				goto done;

			case 3: {
				/* F7 /3      NEG r/m16      Two's complement negate r/m16 */
				/* F7 /3      NEG r/m32      Two's complement negate r/m32 */
				uintptr_t temp;
				enum { EFLAGS_MASK = CF | OF | SF | ZF | AF | PF };
				temp = RD_PFLAGS() & ~EFLAGS_MASK;
				IF_X86_64(if (op_flags & F_REX_W) {
					u64 value = RD_VIOQ();
					if (vio_cmpxch_or_writeq(&args->ma_args, vio_addr, value, 0 - value, IS_ATOMIC()) != value)
						goto again_0xf7;
					temp |= __cmpq((u16)value, 0) & (EFLAGS_MASK & ~CF);
					if (value)
						temp |= CF;
				} else) if (op_flags & F_OP16) {
					u16 value = RD_VIOW();
					if (vio_cmpxch_or_writew(&args->ma_args, vio_addr, value, 0 - value, IS_ATOMIC()) != value)
						goto again_0xf7;
					temp |= __cmpw((u16)value, 0) & (EFLAGS_MASK & ~CF);
					if (value)
						temp |= CF;
				} else {
					u32 value = RD_VIOL();
					if (vio_cmpxch_or_writel(&args->ma_args, vio_addr, value, 0 - value, IS_ATOMIC()) != value)
						goto again_0xf7;
					temp |= __cmpl((u8)value, 0) & (EFLAGS_MASK & ~CF);
					if (value)
						temp |= CF;
				}
				WR_PFLAGS(temp);
			}	goto done;

			case 4: {
				uintptr_t temp;
				/* F7 /4      MUL r/m16      Unsigned multiply (DX:AX = AX * r/m16) */
				/* F7 /4      MUL r/m32      Unsigned multiply (EDX:EAX = EAX * r/m32) */
				IF_X86_64(if (op_flags & F_REX_W) {
					u64 res_ax, res_dx;
					u64 value = RD_VIOQ();
					__asm__("mulq %q5\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (temp)
					        , "=a" (res_ax)
					        , "=d" (res_dx)
					        : "a" (RD_RAX())
					        , "d" (RD_RDX())
					        , "g" (value)
					        : "cc");
					WR_RAX(res_ax);
					WR_RDX(res_dx);
				} else) if (op_flags & F_OP16) {
					u16 res_ax, res_dx;
					u16 value = RD_VIOW();
					__asm__("mulw %w5\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (temp)
					        , "=a" (res_ax)
					        , "=d" (res_dx)
					        : "a" (RD_AX())
					        , "d" (RD_DX())
					        , "g" (value)
					        : "cc");
					WR_AX(res_ax);
					WR_DX(res_dx);
				} else {
					u32 res_ax, res_dx;
					u32 value = RD_VIOL();
					__asm__("mull %k5\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (temp)
					        , "=a" (res_ax)
					        , "=d" (res_dx)
					        : "a" (RD_EAX())
					        , "d" (RD_EDX())
					        , "g" (value)
					        : "cc");
					WR_EAX(res_ax);
					WR_EDX(res_dx);
				}
				SET_PFLAGS(temp, CF | OF);
			}	goto done;

			case 5:
				/* F7 /5      IMUL r/m16      DX:AX = AX * r/m word */
				/* F7 /5      IMUL r/m32      EDX:EAX = EAX * r/m doubleword */
				IF_X86_64(if (op_flags & F_REX_W) {
					u64 res_ax, res_dx;
					u64 value = RD_VIOQ();
					__asm__("imulq %q5\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (temp)
					        , "=a" (res_ax)
					        , "=d" (res_dx)
					        : "a" (RD_RAX())
					        , "d" (RD_RDX())
					        , "g" (value)
					        : "cc");
					WR_RAX(res_ax);
					WR_RDX(res_dx);
				} else) if (op_flags & F_OP16) {
					u16 res_ax, res_dx;
					u16 value = RD_VIOW();
					__asm__("imulw %w5\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (temp)
					        , "=a" (res_ax)
					        , "=d" (res_dx)
					        : "a" (RD_AX())
					        , "d" (RD_DX())
					        , "g" (value)
					        : "cc");
					WR_AX(res_ax);
					WR_DX(res_dx);
				} else {
					u32 res_ax, res_dx;
					u32 value = RD_VIOL();
					__asm__("imull %k5\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (temp)
					        , "=a" (res_ax)
					        , "=d" (res_dx)
					        : "a" (RD_EAX())
					        , "d" (RD_EDX())
					        , "g" (value)
					        : "cc");
					WR_EAX(res_ax);
					WR_EDX(res_dx);
				}
				SET_PFLAGS(temp, CF | OF);
				goto done;

			case 6:
				/* F7 /6      DIV r/m16      Unsigned divide DX:AX by r/m16, with result stored in AX = Quotient, DX = Remainder */
				/* F7 /6      DIV r/m32      Unsigned divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder */
				IF_X86_64(if (op_flags & F_REX_W) {
					u64 value = RD_VIOQ();
					__asm__("divq %2"
					        : "+a" (state->ics_gpregs.gp_rax)
					        , "+d" (state->ics_gpregs.gp_rdx)
					        : "g" (value)
					        : "cc");
				} else) if (op_flags & F_OP16) {
					u16 value;
					u32 temp;
					value = RD_VIOW();
					temp  = ((u32)RD_AX() << 16) |
					        ((u32)RD_DX());
					WR_AX((u16)(temp / value));
					WR_DX((u16)(temp % value));
				} else {
					u32 value;
					u64 temp;
					value = RD_VIOL();
					temp = ((u64)RD_EDX() << 32) |
					       ((u64)RD_EAX());
					WR_EAX((u32)(temp / value));
					WR_EDX((u32)(temp % value));
				}
				goto done;

			case 7:
				/* F7 /7      IDIV r/m16      Signed divide DX:AX by r/m16, with result stored in AX = Quotient, DX = Remainder */
				/* F7 /7      IDIV r/m32      Signed divide EDX:EAX by r/m32, with result stored in EAX = Quotient, EDX = Remainder */
				IF_X86_64(if (op_flags & F_REX_W) {
					u64 value = RD_VIOQ();
					__asm__("idivq %2"
					        : "+a" (state->ics_gpregs.gp_rax)
					        , "+d" (state->ics_gpregs.gp_rdx)
					        : "g" (value)
					        : "cc");
				} else) if (op_flags & F_OP16) {
					s32 temp;
					s16 value;
					value = (s16)RD_VIOW();
					temp = (s32)(((u32)RD_DX() << 16) |
					             ((u32)RD_AX()));
					WR_AX((u16)(temp / value));
					WR_DX((u16)(temp % value));
				} else {
					s64 temp;
					s32 value;
					value = (s32)RD_VIOL();
					temp  = ((u64)RD_EDX() << 32) |
					        ((u64)RD_EAX());
					WR_EAX((u32)(temp / value));
					WR_EDX((u32)(temp % value));
				}
				goto done;

			default: goto undefined_instruction;
			}
			break;

		case 0x84:
			/* 84 /r      TEST r/m8,r8      AND r8 with r/m8; set SF, ZF, PF according to result */
			MOD_DECODE();
			if (IS_MODVIO()) {
				u8 value = RD_VIOB();
				u8 temp  = RD_REGB();
				SET_PFLAGS(__testb(value, temp), OF | CF | SF | ZF | PF);
				goto done;
			}
			break;

		case 0x85:
			/* 85 /r      TEST r/m16,r16      AND r16 with r/m16; set SF, ZF, PF according to result */
			/* 85 /r      TEST r/m32,r32      AND r32 with r/m32; set SF, ZF, PF according to result */
			MOD_DECODE();
			if (IS_MODVIO()) {
				IF_X86_64(if (op_flags & F_REX_W) {
					u64 value = RD_VIOW();
					u64 temp  = RD_REGW();
					SET_PFLAGS(__testq(value, temp), OF | CF | SF | ZF | PF);
				} else) if (op_flags & F_OP16) {
					u16 value = RD_VIOW();
					u16 temp  = RD_REGW();
					SET_PFLAGS(__testw(value, temp), OF | CF | SF | ZF | PF);
				} else {
					u32 value = RD_VIOL();
					u32 temp  = RD_REGL();
					SET_PFLAGS(__testl(value, temp), OF | CF | SF | ZF | PF);
				}
				goto done;
			}
			break;


		case 0x0faf:
			/* imul r16,r/m16 */
			/* imul r32,r/m32 */
			MOD_DECODE();
			if (IS_MODVIO()) {
				uintptr_t temp = RD_PFLAGS() & ~(OF | CF);
				IF_X86_64(if (op_flags & F_REX_W) {
					s64 result;
					s64 value = (s64)RD_VIOQ();
					if (OVERFLOW_SMUL((s64)RD_REGQ(), value, &result))
						temp |= (OF | CF), result = (s64)RD_REGQ() * value;
					WR_REGQ((u64)result);
				} else) if (op_flags & F_OP16) {
					s16 result;
					s16 value = (s16)RD_VIOW();
					if (OVERFLOW_SMUL((s16)RD_REGW(), value, &result))
						temp |= (OF | CF), result = (s16)RD_REGW() * value;
					WR_REGW((u16)result);
				} else {
					s32 result;
					s32 value = (s32)RD_VIOL();
					if (OVERFLOW_SMUL((s32)RD_REGL(), value, &result))
						temp |= (OF | CF), result = (s32)RD_REGL() * value;
					WR_REGL((u32)result);
				}
				WR_PFLAGS(temp);
				goto done;
			}
			break;

		case 0x6b:
			/* imul r16,r/m16,imm8 */
			/* imul r32,r/m32,imm8 */
			MOD_DECODE();
			if (IS_MODVIO()) {
				u8 operand;
				temp    = RD_PFLAGS() & ~(OF | CF);
				operand = *(u8 *)pc;
				pc += 1;
				IF_X86_64(if (op_flags & F_REX_W) {
					s64 result;
					value = RD_VIOQ();
					if (OVERFLOW_SMUL((s64)(u64)value, (s64)(u64)operand, &result))
						temp |= (OF | CF), result = (s64)(u64)value * (u64)operand;
					WR_REGQ((u64)result);
				} else) if (op_flags & F_OP16) {
					s16 result;
					value = RD_VIOW();
					if (OVERFLOW_SMUL((s16)(u16)value, (s16)(u16)operand, &result))
						temp |= (OF | CF), result = (s16)(u16)value * (u16)operand;
					WR_REGW((u16)result);
				} else {
					s32 result;
					value = RD_VIOL();
					if (OVERFLOW_SMUL((s32)(u32)value, (s32)(u32)operand, &result))
						temp |= (OF | CF), result = (s32)(u32)value * (u32)operand;
					WR_REGL((u32)result);
				}
				WR_PFLAGS(temp);
				goto done;
			}
			break;

		case 0x69:
			/* imul r16,r/m16,imm16 */
			/* imul r32,r/m32,imm32 */
			MOD_DECODE();
			if (IS_MODVIO()) {
				temp = RD_PFLAGS() & ~(OF | CF);
				IF_X86_64(if (op_flags & F_REX_W) {
					u64 operand;
					s64 result, value = (s64)RD_VIOQ();
					operand = (u64)(s64)*(s32 *)pc, pc += 4;
					if (OVERFLOW_SMUL(value, (s64)operand, &result))
						temp |= (OF | CF), result = value * operand;
					WR_REGQ((u64)result);
				} else) if (op_flags & F_OP16) {
					u16 operand;
					s16 result, value = (s16)RD_VIOW();
					operand = *(u16 *)pc, pc += 2;
					if (OVERFLOW_SMUL(value, (s16)operand, &result))
						temp |= (OF | CF), result = value * operand;
					WR_REGW((u16)result);
				} else {
					u32 operand;
					s32 result, value = RD_VIOL();
					operand = *(u32 *)pc, pc += 4;
					if (OVERFLOW_SMUL(value, (s32)operand, &result))
						temp |= (OF | CF), result = value * operand;
					WR_REGL((u32)result);
				}
				WR_PFLAGS(temp);
				goto done;
			}
			break;

		case 0x86:
			/* 86 /r      XCHG r/m8, r8      Exchange r8 (byte register) with byte from r/m8 */
			/* 86 /r      XCHG r8, r/m8      Exchange byte from r/m8 with r8 (byte register) */
			MOD_DECODE();
			if (IS_MODVIO()) {
				value = vio_xchb(&args->ma_args, vio_addr, RD_REGB(), true); /* Always atomic! */
				WR_REGB((u8)value);
				goto done;
			}
			break;

		case 0x87:
			/* 87 /r      XCHG r/m16, r16      Exchange r16 with word from r/m16 */
			/* 87 /r      XCHG r16, r/m16      Exchange word from r/m16 with r16 */
			/* 87 /r      XCHG r/m32, r32      Exchange r32 with doubleword from r/m32 */
			/* 87 /r      XCHG r32, r/m32      Exchange doubleword from r/m32 with r32 */
			MOD_DECODE();
			if (IS_MODVIO()) {
				IF_X86_64(if (op_flags & F_REX_W) {
					u64 value = vio_xchq(&args->ma_args, vio_addr, RD_REGQ(), true); /* Always atomic! */
					WR_REGQ(value);
				} else) if (op_flags & F_OP16) {
					u16 value = vio_xchw(&args->ma_args, vio_addr, RD_REGW(), true); /* Always atomic! */
					WR_REGW(value);
				} else {
					u32 value = vio_xchl(&args->ma_args, vio_addr, RD_REGL(), true); /* Always atomic! */
					WR_REGL(value);
				}
				goto done;
			}
			break;

		case 0x0fc0:
			/* 0F C0 /r      XADD r/m8, r8      Exchange r8 and r/m8; load sum into r/m8 */
			MOD_DECODE();
			if (IS_MODVIO()) {
				uintptr_t new_eflags;
				u8 temp  = RD_REGB();
				u8 value = vio_addb(&args->ma_args, vio_addr, temp, IS_ATOMIC());
				WR_REGB(value);
				__asm__("addb %b1, %b2\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "+q" (value)
				        : "q" (temp)
				        : "cc");
				SET_PFLAGS(new_eflags, CF | PF | AF | SF | ZF | OF);
				goto done;
			}
			break;

		case 0x0fc1:
			/* 0F C1 /r      XADD r/m16, r16      Exchange r16 and r/m16; load sum into r/m16 */
			/* 0F C1 /r      XADD r/m32, r32      Exchange r32 and r/m32; load sum into r/m32 */
			MOD_DECODE();
			if (IS_MODVIO()) {
				uintptr_t new_eflags;
				IF_X86_64(if (op_flags & F_REX_W) {
					u64 temp  = RD_REGQ();
					u64 value = vio_addq(&args->ma_args, vio_addr, temp, IS_ATOMIC());
					WR_REGQ((u64)value);
					__asm__("addq %q1, %q2\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "+g" (value)
					        : "r" (temp)
					        : "cc");
				} else) if (op_flags & F_OP16) {
					u16 temp  = RD_REGW();
					u16 value = vio_addw(&args->ma_args, vio_addr, temp, IS_ATOMIC());
					WR_REGW((u16)value);
					__asm__("addw %w1, %w2\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "+g" (value)
					        : "r" (temp)
					        : "cc");
				} else {
					u32 temp  = RD_REGL();
					u32 value = vio_addl(&args->ma_args, vio_addr, temp, IS_ATOMIC());
					WR_REGL((u32)value);
					__asm__("addl %k1, %k2\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "+g" (value)
					        : "r" (temp)
					        : "cc");
				}
				SET_PFLAGS(new_eflags, CF | PF | AF | SF | ZF | OF);
				goto done;
			}
			break;


		{
			uintptr_t new_eflags;
			u8 value, temp, newvalue;
		case 0xd2:
			MOD_DECODE();
			/* D2 /4      SAL r/m8,CL      Multiply r/m8 by 2, CL times */
			/* D2 /4      SHL r/m8,CL      Multiply r/m8 by 2, CL times */
			/* D2 /5      SHR r/m8,CL      Unsigned divide r/m8 by 2, CL times */
			/* D2 /7      SAR r/m8,CL      Signed divide* r/m8 by 2, CL times */
			/* D2 /0      ROL r/m8,CL      Rotate 8 bits r/m8 left CL times */
			/* D2 /1      ROR r/m8,CL      Rotate 8 bits r/m8 right CL times */
			/* D2 /2      RCL r/m8,CL      Rotate 9 bits (CF, r/m8) left CL times */
			/* D2 /3      RCR r/m8,CL      Rotate 9 bits (CF, r/m8) right CL times */
			temp = RD_CL();
			goto do_0xc0;
		case 0xc0:
			MOD_DECODE();
			temp = *(u8 *)pc;
			pc += 1;
do_0xc0:
			if (!IS_MODVIO())
				break;
again_0xc0:
			value = RD_VIOB();
			switch (mod.mi_reg) {

			case 0:
				/* C0 /0 ib      ROL r/m8,imm8      Rotate 8 bits r/m8 left imm8 times */
				__asm__("rolb %%cl, %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "c" (temp)
				        , "1" (value)
				        : "cc");
				new_eflags &= ~(SF | ZF | PF);
				new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
				break;

			case 1:
				/* C0 /1 ib      ROR r/m8,imm8      Rotate 8 bits r/m16 right imm8 times */
				__asm__("rorb %%cl, %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "c" (temp)
				        , "1" (value)
				        : "cc");
				new_eflags &= ~(SF | ZF | PF);
				new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
				break;

			case 2:
				/* C0 /2 ib      RCL r/m8,imm8      Rotate 9 bits (CF, r/m8) left imm8 times */
				__asm__("sahf\n\t"
				        "rclb %%cl, %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "c" (temp)
				        , "1" (value)
				        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
				        : "cc");
				new_eflags &= ~(SF | ZF | PF);
				new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
				break;

			case 3:
				/* C0 /3 ib      RCR r/m8,imm8      Rotate 9 bits (CF, r/m8) right imm8 times */
				__asm__("sahf\n\t"
				        "rcrb %%cl, %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "c" (temp)
				        , "1" (value)
				        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
				        : "cc");
				new_eflags &= ~(SF | ZF | PF);
				new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
				break;

			case 4:
				/* C0 /4 ib      SAL r/m8,imm8      Multiply r/m8 by 2, imm8 times */
				/* C0 /4 ib      SHL r/m8,imm8      Multiply r/m8 by 2, imm8 times */
				__asm__("shlb %%cl, %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "c" (temp)
				        , "1" (value)
				        : "cc");
				break;

			case 5:
				/* C0 /5 ib      SHR r/m8,imm8      Unsigned divide r/m8 by 2, imm8 times */
				__asm__("shrb %%cl, %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "c" (temp)
				        , "1" (value)
				        : "cc");
				break;

			case 7:
				/* C0 /7 ib      SAR r/m8,imm8      Signed divide* r/m8 by 2, imm8 times */
				__asm__("sarb %%cl, %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "c" (temp)
				        , "1" (value)
				        : "cc");
				break;

			default: goto undefined_instruction;
			}
			if (vio_cmpxch_or_writeb(&args->ma_args, vio_addr, value, newvalue, IS_ATOMIC()) != value)
				goto again_0xc0;
			if (temp)
				SET_PFLAGS(new_eflags, CF | SF | ZF | PF);
		}	goto done;

		{
			uintptr_t new_eflags;
			u8 temp;
		case 0xd3:
			MOD_DECODE();
			/* D3 /4      SAL r/m16,CL      Multiply r/m16 by 2, CL times */
			/* D3 /4      SAL r/m32,CL      Multiply r/m32 by 2, CL times */
			/* D3 /4      SHL r/m16,CL      Multiply r/m16 by 2, CL times */
			/* D3 /4      SHL r/m32,CL      Multiply r/m32 by 2, CL times */
			/* D3 /5      SHR r/m16,CL      Unsigned divide r/m16 by 2, CL times */
			/* D3 /5      SHR r/m32,CL      Unsigned divide r/m32 by 2, CL times */
			/* D3 /7      SAR r/m16,CL      Signed divide* r/m16 by 2, CL times */
			/* D3 /7      SAR r/m32,CL      Signed divide* r/m32 by 2, CL times */
			/* D3 /0      ROL r/m16,CL      Rotate 16 bits r/m16 left CL times */
			/* D3 /0      ROL r/m32,CL      Rotate 32 bits r/m32 left CL times */
			/* D3 /1      ROR r/m16,CL      Rotate 16 bits r/m16 right CL times */
			/* D3 /1      ROR r/m32,CL      Rotate 32 bits r/m32 right CL times */
			/* D3 /2      RCL r/m16,CL      Rotate 17 bits (CF, r/m16) left CL times */
			/* D3 /2      RCL r/m32,CL      Rotate 33 bits (CF, r/m32) left CL times */
			/* D3 /3      RCR r/m16,CL      Rotate 17 bits (CF, r/m16) right CL times */
			/* D3 /3      RCR r/m32,CL      Rotate 33 bits (CF, r/m32) right CL times */
			temp = RD_CL();
			goto do_0xc1;
		case 0xc1:
			MOD_DECODE();
			temp = *(u8 *)pc;
			pc += 1;
do_0xc1:
			if (!IS_MODVIO())
				break;
			IF_X86_64(if (op_flags & F_REX_W) {
				u64 value, newvalue;
again_0xc1_op64:
				value = RD_VIOQ();
				switch (mod.mi_reg) {

				case 0:
					/* C1 /0 ib      ROL r/m16,imm8      Rotate 16 bits r/m16 left imm8 times. */
					__asm__("rolq %%cl, %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 1:
					/* C1 /1 ib      ROR r/m16,imm8      Rotate 16 bits r/m16 right imm8 times */
					__asm__("rorq %%cl, %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 2:
					/* C1 /2 ib      RCL r/m16,imm8      Rotate 17 bits (CF, r/m16) left imm8 times */
					__asm__("sahf\n\t"
					        "rclq %%cl, %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 3:
					/* C1 /3 ib      RCR r/m16,imm8      Rotate 17 bits (CF, r/m16) right imm8 times */
					__asm__("sahf\n\t"
					        "rcrq %%cl, %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 4:
					/* C1 /4 ib      SAL r/m16,imm8      Multiply r/m16 by 2, imm8 times */
					/* C1 /4 ib      SHL r/m16,imm8      Multiply r/m16 by 2, imm8 times */
					__asm__("shlq %%cl, %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					break;

				case 5:
					/* C1 /5 ib      SHR r/m16,imm8      Unsigned divide r/m16 by 2, imm8 times */
					__asm__("shrq %%cl, %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					break;

				case 7:
					/* C1 /7 ib      SAR r/m16,imm8      Signed divide* r/m16 by 2, imm8 times */
					__asm__("sarq %%cl, %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					break;

				default: goto undefined_instruction;
				}
				if (vio_cmpxch_or_writeq(&args->ma_args, vio_addr, value, newvalue, IS_ATOMIC()) != value)
					goto again_0xc1_op64;
			} else) if (op_flags & F_OP16) {
				u16 value, newvalue;
again_0xc1_op16:
				value = RD_VIOW();
				switch (mod.mi_reg) {

				case 0:
					/* C1 /0 ib      ROL r/m16,imm8      Rotate 16 bits r/m16 left imm8 times. */
					__asm__("rolw %%cl, %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 1:
					/* C1 /1 ib      ROR r/m16,imm8      Rotate 16 bits r/m16 right imm8 times */
					__asm__("rorw %%cl, %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 2:
					/* C1 /2 ib      RCL r/m16,imm8      Rotate 17 bits (CF, r/m16) left imm8 times */
					__asm__("sahf\n\t"
					        "rclw %%cl, %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 3:
					/* C1 /3 ib      RCR r/m16,imm8      Rotate 17 bits (CF, r/m16) right imm8 times */
					__asm__("sahf\n\t"
					        "rcrw %%cl, %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 4:
					/* C1 /4 ib      SAL r/m16,imm8      Multiply r/m16 by 2, imm8 times */
					/* C1 /4 ib      SHL r/m16,imm8      Multiply r/m16 by 2, imm8 times */
					__asm__("shlw %%cl, %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					break;

				case 5:
					/* C1 /5 ib      SHR r/m16,imm8      Unsigned divide r/m16 by 2, imm8 times */
					__asm__("shrw %%cl, %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					break;

				case 7:
					/* C1 /7 ib      SAR r/m16,imm8      Signed divide* r/m16 by 2, imm8 times */
					__asm__("sarw %%cl, %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					break;

				default: goto undefined_instruction;
				}
				if (vio_cmpxch_or_writew(&args->ma_args, vio_addr, value, newvalue, IS_ATOMIC()) != value)
					goto again_0xc1_op16;
			} else {
				u32 value, newvalue;
again_0xc1:
				value = RD_VIOL();
				switch (mod.mi_reg) {

				case 0:
					/* C1 /0 ib      ROL r/m32,imm8      Rotate 32 bits r/m32 left imm8 times */
					__asm__("roll %%cl, %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 1:
					/* C1 /1 ib      ROR r/m32,imm8      Rotate 32 bits r/m32 right imm8 times */
					__asm__("rorl %%cl, %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 2:
					/* C1 /2 ib      RCL r/m32,imm8      Rotate 33 bits (CF, r/m32) left imm8 times */
					__asm__("sahf\n\t"
					        "rcll %%cl, %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 3:
					/* C1 /3 ib      RCR r/m32,imm8      Rotate 33 bits (CF, r/m32) right imm8 times */
					__asm__("sahf\n\t"
					        "rcrl %%cl, %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 4:
					/* C1 /4 ib      SAL r/m32,imm8      Multiply r/m32 by 2, imm8 times */
					/* C1 /4 ib      SHL r/m32,imm8      Multiply r/m32 by 2, imm8 times */
					__asm__("shll %%cl, %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					break;

				case 5:
					/* C1 /5 ib      SHR r/m32,imm8      Unsigned divide r/m32 by 2, imm8 times */
					__asm__("shrl %%cl, %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					break;

				case 7:
					/* C1 /7 ib      SAR r/m32,imm8      Signed divide* r/m32 by 2, imm8 times */
					__asm__("sarl %%cl, %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "c" (temp)
					        , "1" (value)
					        : "cc");
					break;

				default: goto undefined_instruction;
				}
				if (vio_cmpxch_or_writel(&args->ma_args,
					                     vio_addr,
					                     value,
					                     newvalue,
					                     IS_ATOMIC()) != value)
					goto again_0xc1;
			}
			if (temp)
				SET_PFLAGS(new_eflags, CF | SF | ZF | PF);
			goto done;
		}

		case 0xd0: {
			uintptr_t new_eflags;
			u8 value, newvalue;
			MOD_DECODE();
			if (!IS_MODVIO())
				break;
again_0xd0:
			value = RD_VIOB();
			switch (mod.mi_reg) {

			case 0:
				/* D0 /0      ROL r/m8, 1      Rotate 8 bits r/m8 left once */
				__asm__("rolb %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "1" (value)
				        : "cc");
				new_eflags &= ~(SF | ZF | PF);
				new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
				break;

			case 1:
				/* D0 /1      ROR r/m8, 1      Rotate 8 bits r/m8 right once */
				__asm__("rorb %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "1" (value)
				        : "cc");
				new_eflags &= ~(SF | ZF | PF);
				new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
				break;

			case 2:
				/* D0 /2      RCL r/m8, 1      Rotate 9 bits (CF, r/m8) left once */
				__asm__("sahf\n\t"
				        "rclb %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "1" (value)
				        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
				        : "cc");
				new_eflags &= ~(SF | ZF | PF);
				new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
				break;

			case 3:
				/* D0 /3      RCR r/m8, 1      Rotate 9 bits (CF, r/m8) right once */
				__asm__("sahf\n\t"
				        "rcrb %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "1" (value)
				        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
				        : "cc");
				new_eflags &= ~(SF | ZF | PF);
				new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
				break;

			case 4:
				/* D0 /4      SAL r/m8      Multiply r/m8 by 2, 1 time */
				/* D0 /4      SHL r/m8      Multiply r/m8 by 2, 1 time */
				__asm__("shlb %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "1" (value)
				        : "cc");
				break;

			case 5:
				/* D0 /5      SHR r/m8      Unsigned divide r/m8 by 2, 1 time */
				__asm__("shrb %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "1" (value)
				        : "cc");
				break;

			case 7:
				/* D0 /7      SAR r/m8      Signed divide* r/m8 by 2, 1 times */
				__asm__("sarb %b1\n\t"
				        INSTR_PUSHFP
				        TAIL_POPP_OP0
				        : "=g" (new_eflags)
				        , "=qm" (newvalue)
				        : "1" (value)
				        : "cc");
				break;

			default: goto undefined_instruction;
			}
			if (vio_cmpxch_or_writeb(&args->ma_args, vio_addr, value, newvalue, IS_ATOMIC()) != value)
				goto again_0xd0;
			SET_PFLAGS(new_eflags, CF | OF | SF | ZF | PF);
		}	goto done;

		case 0xd1: {
			uintptr_t new_eflags;
			MOD_DECODE();
			IF_X86_64(if (op_flags & F_REX_W) {
				u64 value, newvalue;
again_0xd1_op64:
				value = RD_VIOQ();
				switch (mod.mi_reg) {

				case 0:
					/* D1 /0      ROL r/m16, 1      Rotate 16 bits r/m16 left once */
					__asm__("rolq %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 1:
					/* D1 /1      ROR r/m16, 1      Rotate 16 bits r/m16 right once */
					__asm__("rorq %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 2:
					/* D1 /2      RCL r/m16, 1      Rotate 17 bits (CF, r/m16) left once */
					__asm__("sahf\n\t"
					        "rclq %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 3:
					/* D1 /3      RCR r/m16, 1      Rotate 17 bits (CF, r/m16) right once */
					__asm__("sahf\n\t"
					        "rcrq %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 4:
					/* D1 /4      SAL r/m16      Multiply r/m16 by 2, 1 time */
					/* D1 /4      SHL r/m16      Multiply r/m16 by 2, 1 time */
					__asm__("shlq %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					break;

				case 5:
					/* D1 /5      SHR r/m16      Unsigned divide r/m16 by 2, 1 time */
					__asm__("shrq %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					break;

				case 7:
					/* D1 /7      SAR r/m16      Signed divide* r/m16 by 2, 1 time */
					__asm__("sarq %q1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					break;

				default: goto undefined_instruction;
				}
				if (vio_cmpxch_or_writeq(&args->ma_args, vio_addr,
				                         value, newvalue, IS_ATOMIC()) != value)
					goto again_0xd1_op64;
			} else) if (op_flags & F_OP16) {
				u16 value, newvalue;
again_0xd1_op16:
				value = RD_VIOW();
				switch (mod.mi_reg) {

				case 0:
					/* D1 /0      ROL r/m16, 1      Rotate 16 bits r/m16 left once */
					__asm__("rolw %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 1:
					/* D1 /1      ROR r/m16, 1      Rotate 16 bits r/m16 right once */
					__asm__("rorw %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 2:
					/* D1 /2      RCL r/m16, 1      Rotate 17 bits (CF, r/m16) left once */
					__asm__("sahf\n\t"
					        "rclw %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 3:
					/* D1 /3      RCR r/m16, 1      Rotate 17 bits (CF, r/m16) right once */
					__asm__("sahf\n\t"
					        "rcrw %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 4:
					/* D1 /4      SAL r/m16      Multiply r/m16 by 2, 1 time */
					/* D1 /4      SHL r/m16      Multiply r/m16 by 2, 1 time */
					__asm__("shlw %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					break;

				case 5:
					/* D1 /5      SHR r/m16      Unsigned divide r/m16 by 2, 1 time */
					__asm__("shrw %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					break;

				case 7:
					/* D1 /7      SAR r/m16      Signed divide* r/m16 by 2, 1 time */
					__asm__("sarw %w1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					break;

				default: goto undefined_instruction;
				}
				if (vio_cmpxch_or_writew(&args->ma_args, vio_addr,
				                         value, newvalue, IS_ATOMIC()) != value)
					goto again_0xd1_op16;
			} else {
				u32 value, newvalue;
again_0xd1:
				value = RD_VIOL();
				switch (mod.mi_reg) {

				case 0:
					/* D1 /0      ROL r/m32, 1      Rotate 32 bits r/m32 left once */
					__asm__("roll %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 1:
					/* D1 /1      ROR r/m32, 1      Rotate 32 bits r/m32 right once */
					__asm__("rorl %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 2:
					/* D1 /2      RCL r/m32, 1      Rotate 33 bits (CF, r/m32) left once */
					__asm__("sahf\n\t"
					        "rcll %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 3:
					/* D1 /3      RCR r/m32, 1      Rotate 33 bits (CF, r/m32) right once */
					__asm__("sahf\n\t"
					        "rcrl %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        , "a" ((u16)(RD_PFLAGS() & CF) << 8)
					        : "cc");
					new_eflags &= ~(SF | ZF | PF);
					new_eflags |= RD_PFLAGS() & (SF | ZF | PF);
					break;

				case 4:
					/* D1 /4      SAL r/m32      Multiply r/m32 by 2, 1 time */
					/* D1 /4      SHL r/m32      Multiply r/m32 by 2, 1 time */
					__asm__("shll %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					break;

				case 5:
					/* D1 /5      SHR r/m32      Unsigned divide r/m32 by 2, 1 time */
					__asm__("shrl %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					break;

				case 7:
					/* D1 /7      SAR r/m32      Signed divide* r/m32 by 2, 1 time */
					__asm__("sarl %k1\n\t"
					        INSTR_PUSHFP
					        TAIL_POPP_OP0
					        : "=g" (new_eflags)
					        , "=g" (newvalue)
					        : "1" (value)
					        : "cc");
					break;

				default: goto undefined_instruction;
				}
				if (vio_cmpxch_or_writel(&args->ma_args, vio_addr,
				                         value, newvalue, IS_ATOMIC()) != value)
					goto again_0xd1;
			}
			SET_PFLAGS(new_eflags, CF | OF | SF | ZF | PF);
		}	goto done;

		{
			uintptr_t new_eflags;
			u8 temp;
		case 0x0fa5:
			/* 0F A5      SHLD r/m16, r16, CL      Shift r/m16 to left CL places while shifting bits from r16 in from the right */
			/* 0F A5      SHLD r/m32, r32, CL      Shift r/m32 to left CL places while shifting bits from r32 in from the right */
			MOD_DECODE();
			temp = RD_CL();
			goto do_0x0fa4;
		case 0x0fa4:
			/* 0F A4      SHLD r/m16, r16, imm8      Shift r/m16 to left imm8 places while shifting bits from r16 in from the right */
			/* 0F A4      SHLD r/m32, r32, imm8      Shift r/m32 to left imm8 places while shifting bits from r32 in from the right */
			MOD_DECODE();
			temp = *(u8 *)pc;
			pc += 1;
do_0x0fa4:
			if (!IS_MODVIO())
				break;
			IF_X86_64(if (op_flags & F_REX_W) {
				u64 value, newvalue;
				temp %= 64;
				if (!temp)
					goto done;
again_0x0fa4_op64:
				value    = RD_VIOQ();
				newvalue = value << temp;
				newvalue |= RD_REGQ() >> (64 - temp);
				if (vio_cmpxch_or_writeq(&args->ma_args, vio_addr, value, newvalue, IS_ATOMIC()) != value)
					goto again_0x0fa4_op64;
				new_eflags = RD_PFLAGS();
				new_eflags &= ~(CF | SF | ZF | PF | OF);
				new_eflags |= __cmpq((u16)newvalue, 0) & (SF | ZF | PF);
				if ((value << (temp - 1)) & __UINT64_C(0x8000000000000000))
					new_eflags |= CF;
				if ((temp == 1) && ((s64)(u64)value < 0) != ((s64)(u64)newvalue < 0))
					new_eflags |= OF;
			} else) if (op_flags & F_OP16) {
				u16 value, newvalue;
				temp %= 16;
				if (!temp)
					goto done;
again_0x0fa4_op16:
				value    = RD_VIOW();
				newvalue = value << temp;
				newvalue |= RD_REGW() >> (16 - temp);
				if (vio_cmpxch_or_writew(&args->ma_args, vio_addr, value, newvalue, IS_ATOMIC()) != value)
					goto again_0x0fa4_op16;
				new_eflags = RD_PFLAGS();
				new_eflags &= ~(CF | SF | ZF | PF | OF);
				new_eflags |= __cmpw((u16)newvalue, 0) & (SF | ZF | PF);
				if ((value << (temp - 1)) & __UINT16_C(0x8000))
					new_eflags |= CF;
				if ((temp == 1) && ((s16)(u16)value < 0) != ((s16)(u16)newvalue < 0))
					new_eflags |= OF;
			} else {
				u32 value, newvalue;
				temp %= 32;
				if (!temp)
					goto done;
again_0x0fa4:
				value    = RD_VIOL();
				newvalue = value << temp;
				newvalue |= RD_REGL() >> (32 - temp);
				if (vio_cmpxch_or_writel(&args->ma_args, vio_addr, value, newvalue, IS_ATOMIC()) != value)
					goto again_0x0fa4;
				new_eflags = RD_PFLAGS();
				new_eflags &= ~(CF | SF | ZF | PF | OF);
				new_eflags |= __cmpl((u32)newvalue, 0) & (SF | ZF | PF);
				if ((value << (temp - 1)) & __UINT32_C(0x80000000))
					new_eflags |= CF;
				if ((temp == 1) && ((s32)(u32)value < 0) != ((s32)(u32)newvalue < 0))
					new_eflags |= OF;
			}
			WR_PFLAGS(new_eflags);
			goto done;
		}

		{
			uintptr_t new_eflags;
			u8 temp;
		case 0x0fad:
			/* 0F AD      SHRD r/m16, r16, CL      Shift r/m16 to right CL places while shifting bits from r16 in from the left */
			/* 0F AD      SHRD r/m32, r32, CL      Shift r/m32 to right CL places while shifting bits from r32 in from the left */
			MOD_DECODE();
			temp = RD_CL();
			goto do_0x0fac;
		case 0x0fac:
			/* 0F AC      SHRD r/m16, r16, imm8      Shift r/m16 to right imm8 places while shifting bits from r16 in from the left */
			/* 0F AC      SHRD r/m32, r32, imm8      Shift r/m32 to right imm8 places while shifting bits from r32 in from the left */
			MOD_DECODE();
			temp = *(u8 *)pc;
			pc += 1;
do_0x0fac:
			if (!IS_MODVIO())
				break;
			IF_X86_64(if (op_flags & F_REX_W) {
				u64 value, newvalue;
				temp %= 64;
				if (!temp)
					goto done;
again_0x0fac_op64:
				value    = RD_VIOQ();
				newvalue = value >> temp;
				newvalue |= RD_REGQ() << (64 - temp);
				if (vio_cmpxch_or_writeq(&args->ma_args, vio_addr, value, newvalue, IS_ATOMIC()) != value)
					goto again_0x0fac_op64;
				new_eflags = RD_PFLAGS();
				new_eflags &= ~(CF | SF | ZF | PF | OF);
				new_eflags |= __cmpq((u64)newvalue, 0) & (SF | ZF | PF);
				if ((value >> (temp - 1)) & 1)
					new_eflags |= CF;
				if ((temp == 1) && ((s64)(u64)value < 0) != ((s64)(u64)newvalue < 0))
					new_eflags |= OF;
			} else) if (op_flags & F_OP16) {
				u16 value, newvalue;
				temp %= 16;
				if (!temp)
					goto done;
again_0x0fac_op16:
				value    = RD_VIOW();
				newvalue = value >> temp;
				newvalue |= RD_REGW() << (16 - temp);
				if (vio_cmpxch_or_writew(&args->ma_args, vio_addr, value, newvalue, IS_ATOMIC()) != value)
					goto again_0x0fac_op16;
				new_eflags = RD_PFLAGS();
				new_eflags &= ~(CF | SF | ZF | PF | OF);
				new_eflags |= __cmpw((u16)newvalue, 0) & (SF | ZF | PF);
				if ((value >> (temp - 1)) & 1)
					new_eflags |= CF;
				if ((temp == 1) && ((s16)(u16)value < 0) != ((s16)(u16)newvalue < 0))
					new_eflags |= OF;
			} else {
				u32 value, newvalue;
				temp %= 32;
				if (!temp)
					goto done;
again_0x0fac:
				value    = RD_VIOL();
				newvalue = value >> temp;
				newvalue |= RD_REGL() << (32 - temp);
				if (vio_cmpxch_or_writel(&args->ma_args, vio_addr, value, newvalue, IS_ATOMIC()) != value)
					goto again_0x0fac;
				new_eflags = RD_PFLAGS();
				new_eflags &= ~(CF | SF | ZF | PF | OF);
				new_eflags |= __cmpl((u32)newvalue, 0) & (SF | ZF | PF);
				if ((value >> (temp - 1)) & 1)
					new_eflags |= CF;
				if ((temp == 1) && ((s32)(u32)value < 0) != ((s32)(u32)newvalue < 0))
					new_eflags |= OF;
			}
			WR_PFLAGS(new_eflags);
		}	goto done;


		case 0x6c: {
			uintptr_t flags;
			u8 value;
			/* 6C       INS m8, DX  Input byte from I/O port specified in DX into memory location specified in ES:(E)DI */
			/* 6C       INSB        Input byte from I/O port specified in DX into memory location specified with ES:(E)DI */
			if (RD_PDI() != cr2)
				break;
			if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
				goto done;
			flags = RD_PFLAGS();
			if ((irregs_rdcs(&state->ics_irregs) & 3) > EFLAGS_GTIOPL(flags)
			    IF_CONFIG_VM86(&& !(flags & EFLAGS_VM)))
				THROW(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE, opcode);
			IF_CONFIG_VM86(if (flags & EFLAGS_VM) {
				value = x86_vm86_inb(state, RD_DX());
			} else) {
				value = __inb(RD_DX());
			}
			WR_VIOB(value);
			if (flags & DF) {
				WR_PDI(cr2 - 1);
			} else {
				WR_PDI(cr2 + 1);
			}
			if (op_flags & (F_REP | F_REPNE)) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0)
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
		}	goto done;


		case 0x6d: {
			uintptr_t flags;
			/* 6D       INS m16, DX  Input word from I/O port specified in DX into memory location specified in ES:(E)DI */
			/* 6D       INSW         Input word from I/O port specified in DX into memory location specified in ES:(E)DI */
			/* 6D       INS m32, DX  Input doubleword from I/O port specified in DX into memory location specified in ES:(E)DI */
			/* 6D       INSD         Input doubleword from I/O port specified in DX into memory location specified in ES:(E)DI */
			if (RD_PDI() != cr2)
				break;
			if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
				goto done;
			flags = RD_PFLAGS();
			if ((irregs_rdcs(&state->ics_irregs) & 3) > EFLAGS_GTIOPL(flags)
			    IF_CONFIG_VM86(&& !(flags & EFLAGS_VM)))
				THROW(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE, opcode);
			if (op_flags & F_OP16) {
				u16 value;
				IF_CONFIG_VM86(if (flags & EFLAGS_VM) {
					value = x86_vm86_inw(state, RD_DX());
				} else) {
					value = __inw(RD_DX());
				}
				WR_VIOW(value);
				WR_PDI(flags & DF ? cr2 - 2 : cr2 + 2);
			} else {
				u32 value;
				IF_CONFIG_VM86(if (flags & EFLAGS_VM) {
					value = x86_vm86_inl(state, RD_DX());
				} else) {
					value = __inl(RD_DX());
				}
				WR_VIOL(value);
				WR_PDI(flags & DF ? cr2 - 4 : cr2 + 4);
			}
			if (op_flags & (F_REP | F_REPNE)) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0)
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
		}	goto done;


		case 0x6e: {
			u8 value;
			uintptr_t flags;
			/* 6E      OUTS DX, m8  Output byte from memory location specified in DS:(E)SI to I/O port specified in DX */
			/* 6E      OUTSB        Output byte from memory location specified in DS:(E)SI to I/O port specified in DX */
			if (RD_PSI() != cr2)
				break;
			if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
				goto done;
			flags = RD_PFLAGS();
			if ((irregs_rdcs(&state->ics_irregs) & 3) > EFLAGS_GTIOPL(flags)
			    IF_CONFIG_VM86(&& !(flags & EFLAGS_VM)))
				THROW(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE, opcode);
			value = RD_VIOB();
			IF_CONFIG_VM86(if (flags & EFLAGS_VM) {
				x86_vm86_outb(state, RD_DX(), value);
			} else) {
				__outb(RD_DX(), value);
			}
			WR_PSI(flags & DF ? cr2 - 1 : cr2 + 1);
			if (op_flags & (F_REP | F_REPNE)) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0)
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
		}	goto done;

		case 0x6f: {
			uintptr_t flags;
			/* 6F      OUTS DX, m16  Output word from memory location specified in DS:(E)SI to I/O port specified in DX */
			/* 6F      OUTSW         Output word from memory location specified in DS:(E)SI to I/O port specified in DX */
			/* 6F      OUTS DX, m32  Output doubleword from memory location specified in DS:(E)SI to I/O port specified in DX */
			/* 6F      OUTSD         Output doubleword from memory location specified in DS:(E)SI to I/O port specified in DX */
			if (RD_PSI() != cr2)
				break;
			if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
				goto done;
			flags = RD_PFLAGS();
			if ((irregs_rdcs(&state->ics_irregs) & 3) > EFLAGS_GTIOPL(flags)
			    IF_CONFIG_VM86(&& !(flags & EFLAGS_VM)))
				THROW(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE, opcode);
			if (op_flags & F_OP16) {
				u16 value = RD_VIOW();
				IF_CONFIG_VM86(if (flags & EFLAGS_VM) {
					x86_vm86_outw(state, RD_DX(), value);
				} else) {
					__outw(RD_DX(), value);
				}
				WR_PSI(flags & DF ? cr2 - 2 : cr2 + 2);
			} else {
				value = RD_VIOL();
				IF_CONFIG_VM86(if (flags & EFLAGS_VM) {
					x86_vm86_outl(state, RD_DX(), (u32)value);
				} else) {
					__outl(RD_DX(), (u32)value);
				}
				WR_PSI(flags & DF ? cr2 - 4 : cr2 + 4);
			}
			if (op_flags & (F_REP | F_REPNE)) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0)
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
		}	goto done;

		case 0xac:
			/* AC      LODS m8    Load byte at address DS:(E)SI into AL */
			/* AC      LODSB      Load byte at address DS:(E)SI into AL */
			if (RD_PSI() != cr2)
				break;
			if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
				goto done;
			WR_AL(RD_VIOB());
			WR_PSI(RD_PFLAGS() & DF ? cr2 - 1 : cr2 + 1);
			if (op_flags & (F_REP | F_REPNE)) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0)
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
			goto done;

		case 0xad:
			/* AD      LODS m16   Load word at address DS:(E)SI into AX */
			/* AD      LODSW      Load word at address DS:(E)SI into AX */
			/* AD      LODS m32   Load doubleword at address DS:(E)SI into EAX */
			/* AD      LODSD      Load doubleword at address DS:(E)SI into EAX */
			if (RD_PSI() != cr2)
				break;
			if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
				goto done;
			IF_X86_64(if (op_flags & F_REX_W) {
				WR_RAX(RD_VIOQ());
				WR_PSI(RD_PFLAGS() & DF ? cr2 - 8 : cr2 + 8);
			} else) if (op_flags & F_OP16) {
				WR_AX(RD_VIOW());
				WR_PSI(RD_PFLAGS() & DF ? cr2 - 2 : cr2 + 2);
			} else {
				WR_EAX(RD_VIOL());
				WR_PSI(RD_PFLAGS() & DF ? cr2 - 4 : cr2 + 4);
			}
			if (op_flags & (F_REP | F_REPNE)) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0)
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
			goto done;

		case 0xa4: {
			uintptr_t psi, pdi;
			u8 value;
			/* A4      MOVS m8, m8  Move byte at address DS:(E)SI to address ES:(E)DI. */
			/* A4      MOVSB        Move byte at address DS:(E)SI to address ES:(E)DI. */
			psi = RD_PSI();
			pdi = RD_PDI();
			if (psi == cr2) {
				if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
					goto done;
				value = RD_VIOB();
				if (isuser)
					validate_writable((void *)pdi, 1);
				COMPILER_WRITE_BARRIER();
				*(u8 *)pdi = (u8)value;
			} else if (pdi == cr2) {
				if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
					goto done;
				if (isuser)
					validate_readable((void *)psi, 1);
				COMPILER_READ_BARRIER();
				value = *(u8 *)psi;
				WR_VIOB((u8)value);
			} else {
				break;
			}
			if (RD_PFLAGS() & DF) {
				WR_PSI(psi - 1);
				WR_PDI(pdi - 1);
			} else {
				WR_PSI(psi + 1);
				WR_PDI(pdi + 1);
			}
			if (op_flags & (F_REP | F_REPNE)) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0)
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
		}	goto done;


		case 0xa5: {
			uintptr_t psi, pdi;
			/* A5      MOVS m16, m16  Move word at address DS:(E)SI to address ES:(E)DI. */
			/* A5      MOVSW          Move word at address DS:(E)SI to address ES:(E)DI. */
			/* A5      MOVS m32, m32  Move doubleword at address DS:(E)SI to address ES:(E)DI. */
			/* A5      MOVSD          Move doubleword at address DS:(E)SI to address */
			psi = RD_PSI();
			pdi = RD_PDI();
			IF_X86_64(if (op_flags & F_REX_W) {
				u64 value;
				if (psi == cr2) {
					if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
						goto done;
					value = RD_VIOQ();
					if (isuser)
						validate_writable((void *)pdi, 8);
					COMPILER_WRITE_BARRIER();
					*(u64 *)pdi = value;
				} else if (pdi == cr2) {
					if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
						goto done;
					if (isuser)
						validate_readable((void *)psi, 8);
					COMPILER_READ_BARRIER();
					value = *(u64 *)psi;
					WR_VIOQ(value);
				} else {
					break;
				}
				if (RD_PFLAGS() & DF) {
					WR_PSI(psi - 8);
					WR_PDI(pdi - 8);
				} else {
					WR_PSI(psi + 8);
					WR_PDI(pdi + 8);
				}
			} else) if (op_flags & F_OP16) {
				u16 value;
				if (psi == cr2) {
					if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
						goto done;
					value = RD_VIOW();
					if (isuser)
						validate_writable((void *)pdi, 2);
					COMPILER_WRITE_BARRIER();
					*(u16 *)pdi = value;
				} else if (pdi == cr2) {
					if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
						goto done;
					if (isuser)
						validate_readable((void *)psi, 2);
					COMPILER_READ_BARRIER();
					value = *(u16 *)psi;
					WR_VIOW(value);
				} else {
					break;
				}
				if (RD_PFLAGS() & DF) {
					WR_PSI(psi - 2);
					WR_PDI(pdi - 2);
				} else {
					WR_PSI(psi + 2);
					WR_PDI(pdi + 2);
				}
			} else {
				u32 value;
				if (psi == cr2) {
					if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
						goto done;
					value = RD_VIOL();
					if (isuser)
						validate_writable((void *)pdi, 4);
					COMPILER_WRITE_BARRIER();
					*(u32 *)pdi = value;
				} else if (pdi == cr2) {
					if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
						goto done;
					if (isuser)
						validate_readable((void *)psi, 4);
					COMPILER_READ_BARRIER();
					value = *(u32 *)psi;
					WR_VIOL(value);
				} else {
					break;
				}
				if (RD_PFLAGS() & DF) {
					WR_PSI(psi - 4);
					WR_PDI(pdi - 4);
				} else {
					WR_PSI(psi + 4);
					WR_PDI(pdi + 4);
				}
			}
			if (op_flags & (F_REP | F_REPNE)) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0)
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
		}	goto done;


		case 0xaa:
			/* AA      STOS m8  Store AL at address ES:(E)DI */
			/* AA      STOSB    Store AL at address ES:(E)DI */
			if (RD_PDI() != cr2)
				break;
			if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
				goto done;
			WR_VIOB(RD_AL());
			/* NOTE: Despite online documentation, STOS will _NOT_ modify ESI! - Only EDI is modified! */
			WR_PDI(RD_PFLAGS() & DF ? cr2 - 1 : cr2 + 1);
			if (op_flags & (F_REP | F_REPNE)) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0)
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
			goto done;


		case 0xab:
			/* AB      STOS m16  Store AX at address ES:(E)DI */
			/* AB      STOSW     Store AX at address ES:(E)DI */
			/* AB      STOS m32  Store EAX at address ES:(E)DI */
			/* AB      STOSD     Store EAX at address ES:(E)DI */
			if (RD_PDI() != cr2)
				break;
			if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
				goto done;
			/* NOTE: Despite online documentation, STOS will _NOT_ modify ESI! - Only EDI is modified! */
			IF_X86_64(if (op_flags & F_REX_W) {
				WR_VIOQ(RD_RAX());
				WR_PDI(RD_PFLAGS() & DF ? cr2 - 8 : cr2 + 8);
			} else) if (op_flags & F_OP16) {
				WR_VIOW(RD_AX());
				WR_PDI(RD_PFLAGS() & DF ? cr2 - 2 : cr2 + 2);
			} else {
				WR_VIOL(RD_EAX());
				WR_PDI(RD_PFLAGS() & DF ? cr2 - 4 : cr2 + 4);
			}
			if (op_flags & (F_REP | F_REPNE)) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0)
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
			goto done;


		case 0xae: {
			u8 value;
			uintptr_t flags;
			/* AE      SCAS m8  Compare AL with byte at ES:(E)DI and set status op_flags */
			/* AE      SCASB    Compare AL with byte at ES:(E)DI and set status op_flags */
			if (RD_PDI() != cr2)
				break;
			if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
				goto done;
			value = RD_VIOB();
			flags = RD_PFLAGS();
			/* NOTE: Despite online documentation, SCAS will _NOT_ modify ESI! - Only EDI is modified! */
			WR_PDI(flags & DF ? cr2 - 1 : cr2 + 1);
			flags &= ~(OF | SF | ZF | AF | PF | CF);
			flags |= __cmpb(RD_AL(), (u8)value) & (OF | SF | ZF | AF | PF | CF);
			WR_PFLAGS(flags);
			if (op_flags & F_REP) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0 && !(flags & ZF))
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			} else if (op_flags & F_REPNE) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0 && (flags & ZF))
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
		}	goto done;


		case 0xaf: {
			uintptr_t flags;
			/* AF      SCAS m16  Compare AX with word at ES:(E)DI and set status op_flags */
			/* AF      SCASW     Compare AX with word at ES:(E)DI and set status op_flags */
			/* AF      SCAS m32  Compare EAX with doubleword at ES(E)DI and set status op_flags */
			/* AF      SCASD     Compare EAX with doubleword at ES:(E)DI and set status op_flags */
			if (RD_PDI() != cr2)
				break;
			if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
				goto done;
			flags = RD_PFLAGS();
			/* NOTE: Despite online documentation, SCAS will _NOT_ modify ESI! - Only EDI is modified! */
			IF_X86_64(if (op_flags & F_REX_W) {
				u64 value = RD_VIOQ();
				WR_PDI(flags & DF ? cr2 - 8 : cr2 + 8);
				flags &= ~(OF | SF | ZF | AF | PF | CF);
				flags |= __cmpq(RD_RAX(), value) & (OF | SF | ZF | AF | PF | CF);
			} else) if (op_flags & F_OP16) {
				u16 value = RD_VIOW();
				WR_PDI(flags & DF ? cr2 - 2 : cr2 + 2);
				flags &= ~(OF | SF | ZF | AF | PF | CF);
				flags |= __cmpw(RD_AX(), value) & (OF | SF | ZF | AF | PF | CF);
			} else {
				u32 value = RD_VIOL();
				WR_PDI(flags & DF ? cr2 - 4 : cr2 + 4);
				flags &= ~(OF | SF | ZF | AF | PF | CF);
				flags |= __cmpl(RD_EAX(), value) & (OF | SF | ZF | AF | PF | CF);
			}
			WR_PFLAGS(flags);
			if (op_flags & F_REP) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0 && !(flags & ZF))
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			} else if (op_flags & F_REPNE) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0 && (flags & ZF))
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
		}	goto done;


		case 0xa6: {
			uintptr_t psi, pdi;
			uintptr_t flags;
			u8 lhs, rhs;
			enum { EFLAGS_MASK = CF | OF | SF | ZF | AF | PF };
			/* A6      CMPS m8, m8  Compares byte at address DS:(E)SI with byte at address ES:(E)DI and sets the status op_flags accordingly */
			/* A6      CMPSB        Compares byte at address DS:(E)SI with byte at address ES:(E)DI and sets the status op_flags accordingly */
			psi = RD_PSI();
			pdi = RD_PDI();
			if (psi == cr2) {
				if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
					goto done;
				if (isuser)
					validate_readable((void *)pdi, 1);
				COMPILER_READ_BARRIER();
				lhs = RD_VIOB();
				rhs = *(u8 *)pdi;
			} else if (pdi == cr2) {
				if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
					goto done;
				if (isuser)
					validate_readable((void *)psi, 1);
				COMPILER_READ_BARRIER();
				lhs = *(u8 *)psi;
				rhs = RD_VIOB();
			} else {
				break;
			}
			flags = RD_PFLAGS();
			if (flags & DF) {
				WR_PSI(psi - 1);
				WR_PDI(pdi - 1);
			} else {
				WR_PSI(psi + 1);
				WR_PDI(pdi + 1);
			}
			flags &= ~EFLAGS_MASK;
			flags |= __cmpb(lhs, rhs) & EFLAGS_MASK;
			WR_PFLAGS(flags);
			if (op_flags & F_REP) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0 && !(flags & ZF))
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			} else if (op_flags & F_REPNE) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0 && (flags & ZF))
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
		}	goto done;


		case 0xa7: {
			uintptr_t flags;
			uintptr_t psi, pdi;
			enum { EFLAGS_MASK = CF | OF | SF | ZF | AF | PF };
			/* A7      CMPS m16, m16  Compares word at address DS:(E)SI with word at address ES:(E)DI and sets the status op_flags accordingly */
			/* A7      CMPSW          Compares word at address DS:(E)SI with word at address ES:(E)DI and sets the status op_flags accordingly */
			/* A7      CMPS m32, m32  Compares doubleword at address DS:(E)SI with doubleword at address ES:(E)DI and sets the status op_flags accordingly */
			/* A7      CMPSD          Compares doubleword at address DS:(E)SI with doubleword at address ES:(E)DI and sets the status op_flags accordingly */
			flags = RD_PFLAGS();
			psi = RD_PSI();
			pdi = RD_PDI();
			IF_X86_64(if (op_flags & F_REX_W) {
				u64 lhs, rhs;
				if (cr2 == psi) {
					if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
						goto done;
					if (isuser)
						validate_readable((void *)pdi, 8);
					COMPILER_READ_BARRIER();
					lhs = RD_VIOQ();
					rhs = *(u64 *)pdi;
				} else if (cr2 == pdi) {
					if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
						goto done;
					if (isuser)
						validate_readable((void *)psi, 8);
					COMPILER_READ_BARRIER();
					lhs = *(u64 *)psi;
					rhs = RD_VIOQ();
				} else {
					break;
				}
				if (flags & DF) {
					WR_PSI(psi - 8);
					WR_PDI(pdi - 8);
				} else {
					WR_PSI(psi + 8);
					WR_PDI(pdi + 8);
				}
				flags &= ~EFLAGS_MASK;
				flags |= __cmpq(lhs, rhs) & EFLAGS_MASK;
			} else) if (op_flags & F_OP16) {
				u16 lhs, rhs;
				if (cr2 == psi) {
					if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
						goto done;
					if (isuser)
						validate_readable((void *)pdi, 2);
					COMPILER_READ_BARRIER();
					lhs = RD_VIOW();
					rhs = *(u16 *)pdi;
				} else if (cr2 == pdi) {
					if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
						goto done;
					if (isuser)
						validate_readable((void *)psi, 2);
					COMPILER_READ_BARRIER();
					lhs = *(u16 *)psi;
					rhs = RD_VIOW();
				} else {
					break;
				}
				if (flags & DF) {
					WR_PSI(psi - 2);
					WR_PDI(pdi - 2);
				} else {
					WR_PSI(psi + 2);
					WR_PDI(pdi + 2);
				}
				flags &= ~EFLAGS_MASK;
				flags |= __cmpw(lhs, rhs) & EFLAGS_MASK;
			} else {
				u32 lhs, rhs;
				if (cr2 == psi) {
					if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
						goto done;
					if (isuser)
						validate_readable((void *)pdi, 4);
					COMPILER_READ_BARRIER();
					lhs = RD_VIOL();
					rhs = *(u32 *)pdi;
				} else if (cr2 == pdi) {
					if ((op_flags & (F_REP | F_REPNE)) && !RD_PCX())
						goto done;
					if (isuser)
						validate_readable((void *)psi, 4);
					COMPILER_READ_BARRIER();
					lhs = *(u32 *)psi;
					rhs = RD_VIOL();
				} else {
					break;
				}
				if (flags & DF) {
					WR_PSI(psi - 1);
					WR_PDI(pdi - 1);
				} else {
					WR_PSI(psi + 1);
					WR_PDI(pdi + 1);
				}
				flags &= ~EFLAGS_MASK;
				flags |= __cmpl(lhs, rhs) & EFLAGS_MASK;
			}
			WR_PFLAGS(flags);
			if (op_flags & F_REP) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0 && !(flags & ZF))
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			} else if (op_flags & F_REPNE) {
				uintptr_t pcx = RD_PCX();
				--pcx;
				WR_PCX(pcx);
				if (pcx != 0 && (flags & ZF))
					pc = (byte_t *)irregs_rdip(&state->ics_irregs);
			}
		}	goto done;
#endif


		case 0x0f38f0:
			/*         0F 38 F0 /r MOVBE r16, m16 RM      Reverse byte order in m16 and move to r16.
			 *         0F 38 F0 /r MOVBE r32, m32 RM      Reverse byte order in m32 and move to r32.
			 * REX.W + 0F 38 F0 /r MOVBE r64, m64 RM      Reverse byte order in m64 and move to r64. */
			MOD_DECODE();
			if (!IS_MODVIO())
				break;
			IF_X86_64(if (op_flags & F_REX_W) {
				WR_REGQ(__bswapq(RD_VIOQ()));
			} else) if (!(op_flags & F_OP16)) {
				WR_REGL(__bswapl(RD_VIOL()));
			} else {
				WR_REGW(__bswapw(RD_VIOW()));
			}
			goto done;


		case 0x0f38f1:
			/*         0F 38 F1 /r MOVBE m16, r16 MR      Reverse byte order in r16 and move to m16.
			 *         0F 38 F1 /r MOVBE m32, r32 MR      Reverse byte order in r32 and move to m32.
			 * REX.W + 0F 38 F1 /r MOVBE m64, r64 MR      Reverse byte order in r64 and move to m64. */
			MOD_DECODE();
			if (!IS_MODVIO())
				break;
			IF_X86_64(if (op_flags & F_REX_W) {
				WR_VIOQ(__bswapq(RD_REGQ()));
			} else) if (!(op_flags & F_OP16)) {
				WR_VIOL(__bswapl(RD_REGL()));
			} else {
				WR_VIOW(__bswapw(RD_REGW()));
			}
			goto done;


		case 0x0f38f7:
			/* VEX.LZ.F3.0F38.W0 F7 /r SARX r32a, r/m32, r32b     Shift r/m32 arithmetically right with count specified in r32b.
			 * VEX.LZ.66.0F38.W0 F7 /r SHLX r32a, r/m32, r32b     Shift r/m32 logically left with count specified in r32b.
			 * VEX.LZ.F2.0F38.W0 F7 /r SHRX r32a, r/m32, r32b     Shift r/m32 logically right with count specified in r32b.
			 * VEX.LZ.F3.0F38.W1 F7 /r SARX r64a, r/m64, r64b     Shift r/m64 arithmetically right with count specified in r64b.
			 * VEX.LZ.66.0F38.W1 F7 /r SHLX r64a, r/m64, r64b     Shift r/m64 logically left with count specified in r64b.
			 * VEX.LZ.F2.0F38.W1 F7 /r SHRX r64a, r/m64, r64b     Shift r/m64 logically right with count specified in r64b. */
			MOD_DECODE();
			if (!IS_MODVIO())
				break;
			if (op_flags & F_f3) {
				/* SARX */
				IF_X86_64(if (op_flags & F_VEX_W) {
					WR_VEXREGQ(__sarq(RD_VIOQ(), RD_REGQ()));
				} else) {
					WR_VEXREGL(__sarl(RD_VIOL(), RD_REGL()));
				}
				goto done;
			}
			if (op_flags & F_66) {
				/* SHLX */
				IF_X86_64(if (op_flags & F_VEX_W) {
					WR_VEXREGQ(__shlq(RD_VIOQ(), RD_REGQ()));
				} else) {
					WR_VEXREGL(__shll(RD_VIOL(), RD_REGL()));
				}
				goto done;
			}
			if (op_flags & F_f2) {
				/* SHRX */
				IF_X86_64(if (op_flags & F_VEX_W) {
					WR_VEXREGQ(__shrq(RD_VIOQ(), RD_REGQ()));
				} else) {
					WR_VEXREGL(__shrl(RD_VIOL(), RD_REGL()));
				}
				goto done;
			}
			break;


		case 0x0f3af0:
			/* VEX.LZ.F2.0F3A.W0 F0 /r ib RORX r32, r/m32, imm8     Rotate 32-bit r/m32 right imm8 times without affecting arithmetic flags.
			 * VEX.LZ.F2.0F3A.W1 F0 /r ib RORX r64, r/m64, imm8     Rotate 64-bit r/m64 right imm8 times without affecting arithmetic flags. */
			MOD_DECODE();
			if (!IS_MODVIO())
				break;
			temp = *pc++;
			IF_X86_64(if (op_flags & F_VEX_W) {
				WR_REGQ(__rorq(RD_VIOQ(), (u8)temp));
			} else) {
				WR_REGL(__rorl(RD_VIOL(), (u8)temp));
			}
			goto done;


		case 0x0fb8: {
			uintptr_t flags;
			/* F3 0F B8 /r        POPCNT r16, r/m16     POPCNT on r/m16
			 * F3 0F B8 /r        POPCNT r32, r/m32     POPCNT on r/m32
			 * F3 REX.W 0F B8 /r  POPCNT r64, r/m64     POPCNT on r/m64 */
			MOD_DECODE();
			if (!IS_MODVIO())
				break;
			flags = RD_PFLAGS();
			IF_X86_64(if (op_flags & F_REX_W) {
				WR_REGQ(simple_popcnt64(RD_VIOQ(), &flags));
			} else) if (!(op_flags & F_OP16)) {
				WR_REGL(simple_popcnt32(RD_VIOL(), &flags));
			} else {
				WR_REGW(simple_popcnt16(RD_VIOW(), &flags));
			}
			WR_PFLAGS(flags);
		}	goto done;


		case 0x0f38f5:
			MOD_DECODE();
			if (!IS_MODVIO())
				break;
			if (op_flags & F_f3) {
				/* VEX.LZ.F3.0F38.W0 F5 /r PEXT r32a, r32b, r/m32         RVM         V/V         BMI2         Parallel extract of bits from r32b using mask in r/m32, result is written to r32a.
				 * VEX.LZ.F3.0F38.W1 F5 /r PEXT r64a, r64b, r/m64         RVM         V/N.E.      BMI2         Parallel extract of bits from r64b using mask in r/m64, result is written to r64a. */
				IF_X86_64(if (op_flags & F_REX_W) {
					WR_REGQ(PEXT(RD_VEXREGQ(), RD_VIOQ()));
				} else) {
					WR_REGL(PEXT(RD_VEXREGL(), RD_VIOL()));
				}
			} else if (op_flags & F_f3) {
				/* VEX.LZ.F2.0F38.W0 F5 /r PDEP r32a, r32b, r/m32         RVM         V/V         BMI2         Parallel deposit of bits from r32b using mask in r/m32, result is written to r32a.
				 * VEX.LZ.F2.0F38.W1 F5 /r PDEP r64a, r64b, r/m64         RVM         V/N.E.      BMI2         Parallel deposit of bits from r64b using mask in r/m64, result is written to r64a. */
				IF_X86_64(if (op_flags & F_REX_W) {
					WR_REGQ(PDEP(RD_VEXREGQ(), RD_VIOQ()));
				} else) {
					WR_REGL(PDEP(RD_VEXREGL(), RD_VIOL()));
				}
			} else {
				/* VEX.LZ.0F38.W0 F5 /r BZHI r32a, r/m32, r32b         RMV         V/V         BMI2         Zero bits in r/m32 starting with the position in r32b, write result to r32a.
				 * VEX.LZ.0F38.W1 F5 /r BZHI r64a, r/m64, r64b         RMV         V/N.E.      BMI2         Zero bits in r/m64 starting with the position in r64b, write result to r64a. */
				u8 n = (u8)RD_VEXREG();
				uintptr_t flags = RD_PFLAGS();
				IF_X86_64(if (op_flags & F_VEX_W) {
					u64 temp = RD_VIOQ();
					if (n < 64)
						temp &= (((u64)1 << n) - 1);
					WR_REGQ(temp);
					flags &= ~(OF | CF | SF | ZF);
					if (n > 63)
						flags |= CF;
					flags |= __testq(temp, temp) & (SF | ZF);
				} else) {
					u32 temp = RD_VIOL();
					if (n < 32)
						temp &= (((u32)1 << n) - 1);
					WR_REGL(temp);
					flags &= ~(OF | CF | SF | ZF);
					if (n > 31)
						flags |= CF;
					flags |= __testl(temp, temp) & (SF | ZF);
				}
				WR_PFLAGS(flags);
			}
			goto done;

		case 0x0f38f2: {
			uintptr_t flags;
			MOD_DECODE();
			if (!IS_MODVIO())
				break;
			/* VEX.LZ.0F38.W0 F2 /r ANDN r32a, r32b, r/m32         RVM         V/V         BMI1         Bitwise AND of inverted r32b with r/m32, store result in r32a.
			 * VEX.LZ.0F38.W1 F2 /r ANDN r64a, r64b, r/m64         RVM         V/NE        BMI1         Bitwise AND of inverted r64b with r/m64, store result in r64a. */
			flags = RD_PFLAGS();
			IF_X86_64(if (op_flags & F_VEX_W) {
				u64 temp = (~RD_VEXREGQ()) & RD_VIOQ();
				WR_REGQ(temp);
				flags &= ~(SF | ZF | OF | CF);
				if (!temp)
					flags |= ZF;
				if (temp & UINT64_C(0x8000000000000000))
					flags |= SF;
			} else) {
				u32 temp = (~RD_VEXREGL()) & RD_VIOL();
				WR_REGL(temp);
				flags &= ~(SF | ZF | OF | CF);
				if (!temp)
					flags |= ZF;
				if (temp & UINT32_C(0x80000000))
					flags |= SF;
			}
			WR_PFLAGS(flags);
		}	goto done;


		/* TODO: BEXTR */
		/* TODO: BLSR */
		/* TODO: BLSI */
		/* TODO: BLSMSK */

		/* TODO: MULX */

		/* TODO: `call'  (with a VIO stack) */
		/* TODO: `ret'   (with a VIO stack) */
		/* TODO: `enter' (with a VIO stack) */
		/* TODO: `leave' (with a VIO stack) */


		default: break;
		}
undefined_instruction:
		/* XXX: Emulate every x86 instruction as a one-on-one direct emulation here.
		 *      If we did this, it would become possible to run VIO memory as code.
		 *   -> This could be especially useful since it would allow us to implement
		 *      general purpose support for int3-like read/write breakpoints via VIO! */

		{
			uintptr_t fixed_pc;
			byte_t *end_pc;
			unsigned int i;
			end_pc   = (byte_t *)irregs_rdip(&state->ics_irregs);
			fixed_pc = (uintptr_t)instruction_succ((void const *)end_pc);
			if (fixed_pc > (uintptr_t)end_pc)
				end_pc = (byte_t *)fixed_pc;
			irregs_wrip(&state->ics_irregs, (uintptr_t)end_pc);
			PERTASK_SET(_this_exception_info.ei_code,
			            (error_code_t)ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_VIO_UNRECOGNIZED));
			PERTASK_SET(_this_exception_info.ei_data.e_pointers[0], (uintptr_t)opcode);
			PERTASK_SET(_this_exception_info.ei_data.e_pointers[1], (uintptr_t)cr2);
			for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
				PERTASK_SET(_this_exception_info.ei_data.e_pointers[i], (uintptr_t)0);
#if EXCEPT_BACKTRACE_SIZE != 0
			for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
				PERTASK_SET(_this_exception_info.ei_trace[i], (void *)0);
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
			PERTASK_SET(_this_exception_info.ei_data.e_faultaddr, (void *)orig_pc);
			cleanup_and_unwind_interrupt(args, state);
		}
done:
		irregs_wrip(&state->ics_irregs, (uintptr_t)pc);
	} EXCEPT {
		PERTASK_SET(_this_exception_info.ei_data.e_faultaddr, (void *)orig_pc);
		cleanup_and_unwind_interrupt(args, state);
	}
	decref_unlikely(args->ma_args.va_block);
	decref_unlikely(args->ma_args.va_part);
	task_popconnections(args->ma_oldcons);
	return state;
#ifndef __x86_64__
do_push_value_2_4_kernel_sp:
	decref_unlikely(args->ma_args.va_block);
	decref_unlikely(args->ma_args.va_part);
	task_popconnections(args->ma_oldcons);
	if (op_flags & F_OP16) {
		memmove((byte_t *)state - 2,
		        (byte_t *)state,
		        OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL);
		state = (struct icpustate *)((byte_t *)state - 2);
		*(u16 *)((byte_t *)state + OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL) = (u16)value;
	} else {
		memmove((byte_t *)state - 4,
		        (byte_t *)state,
		        OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL);
		state = (struct icpustate *)((byte_t *)state - 4);
		*(u32 *)((byte_t *)state + OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL) = (u32)value;
	}
	return state;
do_pop_value_2_4_kernel_sp:
	value = op_flags & F_OP16
	        ? *(u16 *)((byte_t *)state + OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL)
	        : *(u32 *)((byte_t *)state + OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL);
	TRY {
		if (op_flags & F_OP16)
			WR_VIOW((u16)value);
		else {
			WR_VIOL((u32)value);
		}
	} EXCEPT {
		PERTASK_SET(_this_exception_info.ei_data.e_faultaddr, (void *)orig_pc);
		cleanup_and_unwind_interrupt(args, state);
	}
	decref_unlikely(args->ma_args.va_block);
	decref_unlikely(args->ma_args.va_part);
	task_popconnections(args->ma_oldcons);
	if (op_flags & F_OP16) {
		memmove((byte_t *)state + 2,
		        (byte_t *)state,
		         OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL);
		state = (struct icpustate *)((byte_t *)state + 2);
	} else {
		memmove((byte_t *)state + 4,
		        (byte_t *)state,
		        OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL);
		state = (struct icpustate *)((byte_t *)state + 4);
	}
	return state;
#endif /* !__x86_64__ */
}

DECL_END

#endif /* CONFIG_VIO */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_VIO_C */
