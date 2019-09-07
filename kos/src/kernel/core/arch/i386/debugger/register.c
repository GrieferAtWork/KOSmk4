/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/debugger.h>

#ifndef CONFIG_NO_DEBUGGER
#include <string.h>
#include <asm/cpu-flags.h>
#include <sched/task.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>

DECL_BEGIN


struct regdesc {
	char rd_name[12];
};
enum{
#define __REG_UNIQUE  PP_CAT2(X86_DBG_REGID,__LINE__)
#define REGISTER(name, get, set) __REG_UNIQUE,
#include "register-enum.c.inl"
	REG_INVALID
};


PRIVATE ATTR_DBGRODATA struct regdesc const known_regs[] = {
#define REGISTER(name, get, set) [__REG_UNIQUE] = { name },
#include "register-enum.c.inl"
};


PRIVATE ATTR_DBGTEXT unsigned int
NOTHROW(FCALL name2regid)(char const *__restrict name,
                          size_t namelen) {
	unsigned int result;
	if (namelen >= COMPILER_LENOF(known_regs[0].rd_name))
		return REG_INVALID;
	for (result = 0; result < REG_INVALID; ++result) {
		if (memcasecmp(known_regs[result].rd_name, name, namelen) == 0)
			break;
	}
	return result;
}


/* Try to get/set the value of a given register from `dbg_viewstate', given its name.
 * Note that registers with values larger than pointer-size are usually split up into
 * two or more different registers.
 * @return: true:  Success.
 * @return: false: Invalid register name. */
PUBLIC ATTR_DBGTEXT bool
NOTHROW(FCALL dbg_getreg)(char const *__restrict name,
                          size_t namelen, uintptr_t *__restrict presult) {
	uintptr_t value;
	unsigned int id = name2regid(name, namelen);
	if (id == REG_INVALID)
		return false;
	switch (id) {

#define REGISTER(name, get, set) \
	case __REG_UNIQUE:           \
		value = get;             \
		break;
#include "register-enum.c.inl"

	default: __builtin_unreachable();
	}
	*presult = value;
	return true;
}


PUBLIC ATTR_DBGTEXT bool
NOTHROW(FCALL dbg_setreg)(char const *__restrict name,
                          size_t namelen, uintptr_t value) {
	unsigned int id = name2regid(name, namelen);
	if (id == REG_INVALID)
		return false;
	switch (id) {

#define REGISTER(name, get, set) \
	case __REG_UNIQUE:           \
		set;                     \
		break;
#include "register-enum.c.inl"

	default: __builtin_unreachable();
	}
	return true;
}



/* Apply changes made to the viewed register state
 * to the current thread's return location. */
PUBLIC void NOTHROW(FCALL dbg_applyreg)(void) {
	struct task *me = THIS_TASK;
	if (me == debug_original_thread) {
		/* The original thread is being used.
		 * In this case, copying the view-state into
		 * the exit-state is already sufficient. */
		memcpy(&dbg_exitstate,
		       &dbg_viewstate,
		       sizeof(dbg_exitstate));
	} else {
		struct scpustate *state;
		/* Some foreign thread.
		 * In this case, we must update the thread's
		 * return-state to the viewed register state. */
#ifdef __x86_64__
		/* TODO */
#else /* __x86_64__ */
		if (dbg_viewstate.fcs_eflags & EFLAGS_VM) {
			state = (struct scpustate *)((byte_t *)me->t_sched.s_state + SCPUSTATE_SIZEOF(*state));
			state = (struct scpustate *)((byte_t *)state - (OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_VM86));
			state->scs_sgregs.sg_ds   = SEGMENT_USER_DATA_RPL;
			state->scs_sgregs.sg_es   = SEGMENT_USER_DATA_RPL;
			state->scs_sgregs.sg_fs   = SEGMENT_USER_FSBASE_RPL;
			state->scs_sgregs.sg_gs   = SEGMENT_USER_GSBASE_RPL;
			state->scs_irregs_v.ir_es = dbg_viewstate.fcs_sgregs.sg_es;
			state->scs_irregs_v.ir_ds = dbg_viewstate.fcs_sgregs.sg_ds;
			state->scs_irregs_v.ir_fs = dbg_viewstate.fcs_sgregs.sg_fs;
			state->scs_irregs_v.ir_gs = dbg_viewstate.fcs_sgregs.sg_gs;
			goto set_user_specific_registers;
		} else {
			if (dbg_viewstate.fcs_sgregs.sg_cs & 3) {
				state = (struct scpustate *)((byte_t *)me->t_sched.s_state + SCPUSTATE_SIZEOF(*state));
				state = (struct scpustate *)((byte_t *)state - (OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_USER));
				state->scs_sgregs.sg_ds = dbg_viewstate.fcs_sgregs.sg_ds;
				state->scs_sgregs.sg_es = dbg_viewstate.fcs_sgregs.sg_es;
				state->scs_sgregs.sg_fs = dbg_viewstate.fcs_sgregs.sg_fs;
				state->scs_sgregs.sg_gs = dbg_viewstate.fcs_sgregs.sg_gs;
set_user_specific_registers:
				state->scs_irregs_u.ir_esp = dbg_viewstate.fcs_gpregs.gp_esp;
				state->scs_irregs_u.ir_ss  = dbg_viewstate.fcs_sgregs.sg_ss;
			} else {
				/* Kernel-space state (must allocate) */
				state = (struct scpustate *)(dbg_viewstate.fcs_gpregs.gp_esp -
				                             (OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL));
			}
			state->scs_sgregs.sg_ds = dbg_viewstate.fcs_sgregs.sg_ds;
			state->scs_sgregs.sg_es = dbg_viewstate.fcs_sgregs.sg_es;
			state->scs_sgregs.sg_fs = dbg_viewstate.fcs_sgregs.sg_fs;
			state->scs_sgregs.sg_gs = dbg_viewstate.fcs_sgregs.sg_gs;
		}
		state->scs_irregs_k.ir_eflags = dbg_viewstate.fcs_eflags;
		state->scs_irregs_k.ir_cs     = dbg_viewstate.fcs_sgregs.sg_cs;
		state->scs_irregs_k.ir_eip    = dbg_viewstate.fcs_eip;
		state->scs_gpregs             = dbg_viewstate.fcs_gpregs;
		me->t_sched.s_state = state;
#endif /* !__x86_64__ */
	}
	memcpy(&dbg_origstate,
	       &dbg_viewstate,
	       sizeof(dbg_origstate));
}



DECL_END
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_C */
