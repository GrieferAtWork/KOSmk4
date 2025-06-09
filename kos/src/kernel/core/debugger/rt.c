/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_RT_C
#define GUARD_KERNEL_SRC_DEBUGGER_RT_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/rt.h>
#include <sched/cpu.h>
#include <sched/pertask.h>

#include <hybrid/byteorder.h>

#include <asm/isa.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/paging.h>
#include <kos/types.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libcpustate/register.h>

DECL_BEGIN

/* The stack from which debug code is executed. */
PUBLIC ATTR_DBGBSS byte_t dbg_stack[KERNEL_DEBUG_STACKSIZE] = {};

/* Set to true while the debugger is currently active.
 * NOTE: This variable may be used to test if the system is being debugged. */
DATDEF ATTR_DBGBSS bool dbg_active_ ASMNAME("dbg_active");
PUBLIC ATTR_DBGBSS bool dbg_active_ = false;

/* [1..1] The thread that is currently being viewed. */
PUBLIC ATTR_DBGBSS struct task *dbg_current = NULL;

/* [1..1] The cpu that is hosting the debugger (== THIS_TASK->t_cpu).
 *        Set to non-NULL  before `dbg_active' becomes  `true',
 *        and set to `NULL' before `dbg_active' becomes `false' */
DATDEF ATTR_DBGBSS struct cpu *dbg_cpu_ ASMNAME("dbg_cpu");
PUBLIC ATTR_DBGBSS struct cpu *dbg_cpu_ = NULL;


/* DBG trap state information. */
PUBLIC ATTR_DBGBSS void *dbg_rt_trapstate            = NULL;
PUBLIC ATTR_DBGBSS unsigned int dbg_rt_trapstatekind = DBG_RT_STATEKIND_NONE;
PUBLIC ATTR_DBGBSS bool dbg_rt_trapstate_istrap      = false;

DBG_INIT(reset_dbg_rt_trapstate_istrap) {
	dbg_rt_trapstate_istrap = false;
}


/* Apply changes made to `DBG_RT_REGLEVEL_VIEW' onto `DBG_RT_REGLEVEL_ORIG'. */
PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_rt_applyview")
void NOTHROW(FCALL dbg_rt_applyview)(void) {
	struct fcpustate fst;
	dbg_rt_getallregs(DBG_RT_REGLEVEL_VIEW, &fst);
	dbg_rt_setallregs(DBG_RT_REGLEVEL_ORIG, &fst);
}

/* Check if the register view has been changed. */
PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_rt_changedview")
ATTR_PURE WUNUSED bool NOTHROW(FCALL dbg_rt_changedview)(void) {
	struct fcpustate view, orig;
	dbg_rt_getallregs(DBG_RT_REGLEVEL_ORIG, &orig);
	dbg_rt_getallregs(DBG_RT_REGLEVEL_VIEW, &view);
	return bcmp(&view, &orig, sizeof(struct fcpustate)) != 0;
}

/* Get/Set a pointer-sized register, given its ID */
PUBLIC ATTR_WEAK ATTR_PURE WUNUSED ATTR_DBGTEXT_S("dbg_rt_getregbyidp") uintptr_t
NOTHROW(KCALL dbg_rt_getregbyidp)(unsigned int level, cpu_regno_t regno) {
	uintptr_t result;
	size_t reqlen;
	reqlen = dbg_rt_getregbyid(level, regno, &result, sizeof(result));
	assert(reqlen && reqlen <= sizeof(result));
	if (reqlen < sizeof(result)) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		bzero((byte_t *)&result + reqlen, sizeof(result) - reqlen);
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
		memmoveup((byte_t *)&result + sizeof(result) - reqlen,
		          &result, sizeof(result) - reqlen);
		bzero(&result, sizeof(result) - reqlen);
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
	}
	return result;
}

PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_rt_setregbyidp") bool
NOTHROW(KCALL dbg_rt_setregbyidp)(unsigned int level, cpu_regno_t regno, uintptr_t value) {
	size_t reqlen;
	reqlen = dbg_rt_setregbyid(level, regno, &value, sizeof(value));
	return reqlen && reqlen <= sizeof(value);
}


/* Get/set a register, given its ID
 * NOTE: When `return > buflen', then
 *       dbg_rt_getregbyname: The contents of `buf' are undefined.
 *       dbg_rt_setregbyname:  The  register   was  not   written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of the values from <asm/registers.h>
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_rt_getregbyid") size_t
NOTHROW(KCALL dbg_rt_getregbyid)(unsigned int level, cpu_regno_t regno,
                              void *__restrict buf, size_t buflen) {
	size_t result;
	struct fcpustate cs;
	dbg_rt_getallregs(level, &cs);
	result = register_get_fcpustate(&cs, regno, buf, buflen);
	return result;
}

PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_rt_setregbyid") size_t
NOTHROW(KCALL dbg_rt_setregbyid)(unsigned int level, cpu_regno_t regno,
                              void const *__restrict buf, size_t buflen) {
	size_t result;
	struct fcpustate cs;
	dbg_rt_getallregs(level, &cs);
	result = register_set_fcpustate(&cs, regno, buf, buflen);
	if (result && result <= buflen)
		dbg_rt_setallregs(level, &cs);
	return result;
}



/* Get/set a register, given its (arch-specific) name
 * NOTE: When `return > buflen', then
 *       dbg_rt_getregbyname: The contents of `buf' are undefined.
 *       dbg_rt_setregbyname: The register was not written.
 * @return: * : The required buffer size, or 0 when `name' isn't recognized. */
PUBLIC ATTR_DBGTEXT_S("dbg_rt_getregbyname") size_t
NOTHROW(KCALL dbg_rt_getregbyname)(unsigned int level, char const *__restrict name,
                                size_t namelen, void *__restrict buf, size_t buflen) {
	isa_t isa = dbg_rt_getisa(level);
	cpu_regno_t regno  = register_byname(isa, name, namelen);
	if unlikely(regno == CPU_REGISTER_NONE)
		return 0;
	return dbg_rt_getregbyid(level, regno, buf, buflen);
}

PUBLIC ATTR_DBGTEXT_S("dbg_rt_setregbyname") size_t
NOTHROW(KCALL dbg_rt_setregbyname)(unsigned int level, char const *__restrict name,
                                size_t namelen, void const *__restrict buf, size_t buflen) {
	isa_t isa = dbg_rt_getisa(level);
	cpu_regno_t regno  = register_byname(isa, name, namelen);
	if unlikely(regno == CPU_REGISTER_NONE)
		return 0;
	return dbg_rt_setregbyid(level, regno, buf, buflen);
}


PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_rt_getregbynamep") bool
NOTHROW(KCALL dbg_rt_getregbynamep)(unsigned int level, char const *__restrict name,
                                 size_t namelen, uintptr_t *__restrict result) {
	isa_t isa = dbg_rt_getisa(level);
	cpu_regno_t regno  = register_byname(isa, name, namelen);
	if unlikely(regno == CPU_REGISTER_NONE)
		return false;
	*result = dbg_rt_getregbyidp(level, regno);
	return true;
}

PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_rt_setregbynamep") bool
NOTHROW(KCALL dbg_rt_setregbynamep)(unsigned int level, char const *__restrict name,
                                 size_t namelen, uintptr_t value) {
	isa_t isa = dbg_rt_getisa(level);
	cpu_regno_t regno  = register_byname(isa, name, namelen);
	if unlikely(regno == CPU_REGISTER_NONE)
		return false;
	return dbg_rt_setregbyid(level, regno, &value, sizeof(value)) != 0;
}

/* Return the ISA code for use with libinstrlen */
PUBLIC ATTR_PURE WUNUSED ATTR_WEAK ATTR_DBGTEXT_S("dbg_rt_getisa") isa_t
NOTHROW(KCALL dbg_rt_getisa)(unsigned int level) {
	isa_t result;
	struct fcpustate cs;
	dbg_rt_getallregs(level, &cs);
	result = fcpustate_getisa(&cs);
	return result;
}


/* Check if "level"s PC points *at* the faulting instruction (rather than after it) */
PUBLIC ATTR_PURE WUNUSED bool
NOTHROW(FCALL dbg_rt_attrap)(unsigned int level) {
	if (dbg_current != THIS_TASK)
		return true; /* All other threads were interrupted -> their PCs point *at* their next instr */
	switch (level) {
	case DBG_RT_REGLEVEL_TRAP:
	case DBG_RT_REGLEVEL_ORIG:
		return dbg_rt_trapstate_istrap;
	case DBG_RT_REGLEVEL_VIEW:
		return dbg_rt_trapstate_istrap && !dbg_rt_changedview();
	case DBG_RT_REGLEVEL_EXIT:
	default:
		return false;
	}
	__builtin_unreachable();
}



DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_RT_C */
