/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_RT_C
#define GUARD_KERNEL_SRC_DEBUGGER_RT_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/entry.h>
#include <debugger/hook.h>
#include <debugger/rt.h>

#include <hybrid/align.h>
#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>

#include <asm/registers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <stdint.h>
#include <string.h>

#include <libcpustate/register.h>

#if defined(__x86_64__) || defined(__i386__)
#include <asm/registers-compat.h>
#endif /* __x86_64__ || __i386__ */

DECL_BEGIN

PUBLIC uintptr_t volatile kernel_debug_on = KERNEL_DEBUG_ON_DEFAULT;

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

/* Apply changes made to `DBG_REGLEVEL_VIEW' onto `DBG_REGLEVEL_ORIG'. */
PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_applyview")
void NOTHROW(FCALL dbg_applyview)(void) {
	struct fcpustate fst;
	dbg_getallregs(DBG_REGLEVEL_VIEW, &fst);
	dbg_setallregs(DBG_REGLEVEL_ORIG, &fst);
}

/* Check if the register view has been changed. */
PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_changedview")
ATTR_PURE WUNUSED bool NOTHROW(FCALL dbg_changedview)(void) {
	struct fcpustate view, orig;
	dbg_getallregs(DBG_REGLEVEL_ORIG, &orig);
	dbg_getallregs(DBG_REGLEVEL_VIEW, &view);
	return bcmp(&view, &orig, sizeof(struct fcpustate)) != 0;
}

/* Get/Set a pointer-sized register, given its ID */
PUBLIC ATTR_WEAK ATTR_PURE WUNUSED ATTR_DBGTEXT_S("dbg_getregbyidp") uintptr_t
NOTHROW(KCALL dbg_getregbyidp)(unsigned int level, cpu_regno_t regno) {
	uintptr_t result;
	size_t reqlen;
	reqlen = dbg_getregbyid(level, regno, &result, sizeof(result));
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

PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_setregbyidp") bool
NOTHROW(KCALL dbg_setregbyidp)(unsigned int level, cpu_regno_t regno, uintptr_t value) {
	size_t reqlen;
	reqlen = dbg_setregbyid(level, regno, &value, sizeof(value));
	return reqlen && reqlen <= sizeof(value);
}


/* Get/set a register, given its ID
 * NOTE: When `return > buflen', then
 *       dbg_getregbyname: The contents of `buf' are undefined.
 *       dbg_setregbyname:  The  register   was  not   written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of the values from <asm/registers.h>
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_getregbyid") size_t
NOTHROW(KCALL dbg_getregbyid)(unsigned int level, cpu_regno_t regno,
                              void *__restrict buf, size_t buflen) {
	size_t result;
	struct fcpustate cs;
	dbg_getallregs(level, &cs);
	result = register_get_fcpustate(&cs, regno, buf, buflen);
	return result;
}

PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_setregbyid") size_t
NOTHROW(KCALL dbg_setregbyid)(unsigned int level, cpu_regno_t regno,
                              void const *__restrict buf, size_t buflen) {
	size_t result;
	struct fcpustate cs;
	dbg_getallregs(level, &cs);
	result = register_set_fcpustate(&cs, regno, buf, buflen);
	if (result && result <= buflen)
		dbg_setallregs(level, &cs);
	return result;
}



/* Get/set a register, given its (arch-specific) name
 * NOTE: When `return > buflen', then
 *       dbg_getregbyname: The contents of `buf' are undefined.
 *       dbg_setregbyname: The register was not written.
 * @return: * : The required buffer size, or 0 when `name' isn't recognized. */
PUBLIC ATTR_DBGTEXT_S("dbg_getregbyname") size_t
NOTHROW(KCALL dbg_getregbyname)(unsigned int level, char const *__restrict name,
                                size_t namelen, void *__restrict buf, size_t buflen) {
	instrlen_isa_t isa = dbg_instrlen_isa(level);
	cpu_regno_t regno  = register_byname(isa, name, namelen);
	if unlikely(regno == CPU_REGISTER_NONE)
		return 0;
	return dbg_getregbyid(level, regno, buf, buflen);
}

PUBLIC ATTR_DBGTEXT_S("dbg_setregbyname") size_t
NOTHROW(KCALL dbg_setregbyname)(unsigned int level, char const *__restrict name,
                                size_t namelen, void const *__restrict buf, size_t buflen) {
	instrlen_isa_t isa = dbg_instrlen_isa(level);
	cpu_regno_t regno  = register_byname(isa, name, namelen);
	if unlikely(regno == CPU_REGISTER_NONE)
		return 0;
	return dbg_setregbyid(level, regno, buf, buflen);
}


PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_getregbynamep") bool
NOTHROW(KCALL dbg_getregbynamep)(unsigned int level, char const *__restrict name,
                                 size_t namelen, uintptr_t *__restrict result) {
	instrlen_isa_t isa = dbg_instrlen_isa(level);
	cpu_regno_t regno  = register_byname(isa, name, namelen);
	if unlikely(regno == CPU_REGISTER_NONE)
		return false;
	*result = dbg_getregbyidp(level, regno);
	return true;
}

PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_setregbynamep") bool
NOTHROW(KCALL dbg_setregbynamep)(unsigned int level, char const *__restrict name,
                                 size_t namelen, uintptr_t value) {
	instrlen_isa_t isa = dbg_instrlen_isa(level);
	cpu_regno_t regno  = register_byname(isa, name, namelen);
	if unlikely(regno == CPU_REGISTER_NONE)
		return false;
	return dbg_setregbyid(level, regno, &value, sizeof(value)) != 0;
}

/* Return the ISA code for use with libinstrlen */
PUBLIC ATTR_PURE WUNUSED ATTR_WEAK ATTR_DBGTEXT_S("dbg_instrlen_isa") instrlen_isa_t
NOTHROW(KCALL dbg_instrlen_isa)(unsigned int level) {
	instrlen_isa_t result;
	struct fcpustate cs;
	dbg_getallregs(level, &cs);
	result = instrlen_isa_from_fcpustate(&cs);
	return result;
}


DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_RT_C */
