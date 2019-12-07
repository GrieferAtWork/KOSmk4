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
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state-compat.h>
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


PRIVATE ATTR_DBGTEXT WUNUSED ATTR_PURE unsigned int
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


/* Get/set a register, given its (arch-specific) name
 * NOTE: When `return > buflen', then
 *       dbg_getregbyname: The contents of `buf' are undefined.
 *       dbg_setregbyname: The register was not written.
 * @return: * : The required buffer size, or 0 when `name' isn't recognized. */
PUBLIC ATTR_DBGTEXT size_t
NOTHROW(KCALL dbg_getregbyname)(unsigned int level, char const *__restrict name,
                                size_t namelen, void *__restrict buf, size_t buflen) {
	uintptr_t value;
	unsigned int id = name2regid(name, namelen);
	if (id == REG_INVALID)
		return 0;
	(void)level; /* TODO */
	switch (id) {

#define REGISTER(name, get, set) \
	case __REG_UNIQUE:           \
		value = get;             \
		break;
#include "register-enum.c.inl"

	default: __builtin_unreachable();
	}
	if (buflen >= sizeof(uintptr_t))
		memcpy(buf, &value, sizeof(uintptr_t));
	return sizeof(uintptr_t);
}


PUBLIC ATTR_DBGTEXT size_t
NOTHROW(KCALL dbg_setregbyname)(unsigned int level, char const *__restrict name,
                                size_t namelen, void const *__restrict buf, size_t buflen) {
	unsigned int id = name2regid(name, namelen);
	uintptr_t value;
	if (id == REG_INVALID)
		return 0;
	(void)level; /* TODO */
	if (buflen < sizeof(uintptr_t))
		return sizeof(uintptr_t);
	memcpy(&value, buf, sizeof(uintptr_t));
	switch (id) {

#define REGISTER(name, get, set) \
	case __REG_UNIQUE:           \
		set;                     \
		break;
#include "register-enum.c.inl"

	default: __builtin_unreachable();
	}
	return sizeof(uintptr_t);
}



/* Apply changes made to the viewed register state
 * to the current thread's return location. */
PUBLIC void NOTHROW(FCALL dbg_applyview)(void) {
	if (dbg_current == THIS_TASK) {
		/* The original thread is being used.
		 * In this case, copying the view-state into
		 * the exit-state is already sufficient. */
		memcpy(&x86_dbg_exitstate,
		       &x86_dbg_viewstate,
		       sizeof(x86_dbg_exitstate));
	} else {
		struct scpustate *state;
		/* Some foreign thread.
		 * In this case, we must update the thread's
		 * return-state to the viewed register state. */
		state = dbg_current->t_sched.s_state;
		state = (struct scpustate *)((byte_t *)state + scpustate_sizeof(state));
		state = fcpustate_to_scpustate_p(&x86_dbg_viewstate, state);
		dbg_current->t_sched.s_state = state;
	}
	memcpy(&x86_dbg_origstate,
	       &x86_dbg_viewstate,
	       sizeof(x86_dbg_origstate));
}


/* Get/set all registers. */
PUBLIC void
NOTHROW(KCALL dbg_getallregs)(unsigned int level,
                              struct fcpustate *__restrict state) {
	(void)level; /* TODO */
	*state = x86_dbg_viewstate;
}

PUBLIC void
NOTHROW(KCALL dbg_setallregs)(unsigned int level,
                              struct fcpustate const *__restrict state) {
	(void)level; /* TODO */
	x86_dbg_viewstate = *state;
}


/* Get/Set debugger register for some given level.
 * NOTE: These functions are written to be compatible with `unwind_getreg_t' / `unwind_setreg_t'
 * @param: arg: One of `DBG_REGLEVEL_*', cast as `(void *)(uintptr_t)DBG_REGLEVEL_*' */
PUBLIC bool
NOTHROW(LIBUNWIND_CC dbg_getreg)(/*uintptr_t level*/ void const *arg,
                                 uintptr_half_t regno, void *__restrict buf) {
	(void)arg;
	(void)regno;
	(void)buf;
	/* TODO */
	return false;
}

PUBLIC bool
NOTHROW(LIBUNWIND_CC dbg_setreg)(/*uintptr_t level*/ void *arg,
                                 uintptr_half_t regno, void const *__restrict buf) {
	(void)arg;
	(void)regno;
	(void)buf;
	/* TODO */
	return false;
}


DECL_END
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_C */
