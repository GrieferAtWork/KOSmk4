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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_RT_C
#define GUARD_KERNEL_SRC_DEBUGGER_RT_C 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/function.h>
#include <debugger/rt.h>

DECL_BEGIN

/* The stack from which debug code is executed. */
PUBLIC ATTR_DBGBSS byte_t dbg_stack[KERNEL_DEBUG_STACKSIZE] = {};

/* Set to true while the debugger is currently active.
 * NOTE: This variable may be used to test if the system is being debugged. */
PUBLIC ATTR_DBGBSS bool dbg_active = false;

/* [1..1] The thread that is currently being viewed. */
PUBLIC ATTR_DBGBSS struct task *dbg_current = NULL;

/* Apply changes made to `DBG_REGLEVEL_VIEW' onto `DBG_REGLEVEL_ORIG'. */
PUBLIC ATTR_DBGTEXT_S("dbg_applyview") ATTR_WEAK
void NOTHROW(FCALL dbg_applyview)(void) {
	struct fcpustate fst;
	dbg_getallregs(DBG_REGLEVEL_VIEW, &fst);
	dbg_setallregs(DBG_REGLEVEL_ORIG, &fst);
}


DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_RT_C */
