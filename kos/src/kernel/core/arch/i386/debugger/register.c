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
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <hybrid/host.h>

#include <asm/registers-compat.h>
#include <asm/registers.h>
#include <debugger/function.h>
#include <debugger/rt.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <libunwind/cfi.h>

DECL_BEGIN

/* Get/Set debugger register for some given level.
 * NOTE: These functions are written to be compatible with `unwind_getreg_t' / `unwind_setreg_t'
 * @param: arg: One of `DBG_REGLEVEL_*', cast as `(void *)(uintptr_t)DBG_REGLEVEL_*' */
PUBLIC ATTR_DBGTEXT bool
NOTHROW(LIBUNWIND_CC dbg_getreg)(/*uintptr_t level*/ void const *arg,
                                 uintptr_half_t regno,
                                 void *__restrict buf) {
	(void)arg;
	(void)regno;
	(void)buf;
	/* TODO */
	return false;
}

PUBLIC ATTR_DBGTEXT bool
NOTHROW(LIBUNWIND_CC dbg_setreg)(/*uintptr_t level*/ void *arg,
                                 uintptr_half_t regno,
                                 void const *__restrict buf) {
	(void)arg;
	(void)regno;
	(void)buf;
	/* TODO */
	return false;
}

/* Get/set a register, given its ID
 * NOTE: When `return > buflen', then
 *       dbg_getregbyname: The contents of `buf' are undefined.
 *       dbg_setregbyname: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: id:  One of `X86_REGISTER_*' (from <asm/registers.h>) or one of `X86_DBGREGISTER_*'
 * @return: * : The required buffer size, or 0 when `name' isn't recognized. */
PUBLIC size_t
NOTHROW(KCALL x86_dbg_getregbyid)(unsigned int level, unsigned int id,
                                  void *__restrict buf, size_t buflen) {
	(void)level;
	(void)id;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

PUBLIC size_t
NOTHROW(KCALL x86_dbg_setregbyid)(unsigned int level, unsigned int id,
                                  void const *__restrict buf, size_t buflen) {
	(void)level;
	(void)id;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

/* Get/set all registers. */
PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_getallregs)(unsigned int level,
                              struct fcpustate *__restrict state) {
	(void)level;
	/* TODO */
	*state = x86_dbg_viewstate;
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_setallregs)(unsigned int level,
                              struct fcpustate const *__restrict state) {
	(void)level;
	/* TODO */
	x86_dbg_viewstate = *state;
}

/* Get/set a register, given its (arch-specific) name
 * NOTE: When `return > buflen', then
 *       dbg_getregbyname: The contents of `buf' are undefined.
 *       dbg_setregbyname: The register was not written.
 * @return: * : The required buffer size, or 0 when `name' isn't recognized. */
PUBLIC ATTR_DBGTEXT size_t
NOTHROW(KCALL dbg_getregbyname)(unsigned int level, char const *__restrict name,
                                size_t namelen, void *__restrict buf, size_t buflen) {
	size_t result;
	unsigned int nameid;
	nameid = x86_dbg_regfromname(name, namelen);
	result = x86_dbg_getregbyid(level, nameid, buf, buflen);
	return result;
}

PUBLIC ATTR_DBGTEXT size_t
NOTHROW(KCALL dbg_setregbyname)(unsigned int level, char const *__restrict name,
                                size_t namelen, void const *__restrict buf, size_t buflen) {
	size_t result;
	unsigned int nameid;
	nameid = x86_dbg_regfromname(name, namelen);
	result = x86_dbg_setregbyid(level, nameid, buf, buflen);
	return result;
}

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_C */
