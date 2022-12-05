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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_ENTRY_C
#define GUARD_KERNEL_SRC_DEBUGGER_ENTRY_C 1
#define DISABLE_BRANCH_PROFILING

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/entry.h>
#include <debugger/hook.h>

#include <libcpustate/apply.h>

DECL_BEGIN

/* Set of `KERNEL_DEBUGTRAP_ON_*', specifying events for which to trigger traps. */
PUBLIC ATTR_DBGDATA uintptr_t volatile kernel_debug_on = KERNEL_DEBUG_ON_DEFAULT;


ATTR_WEAK ATTR_DBGTEXT_S("dbg_enter_ucpustate_c")
PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_ucpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct ucpustate *__restrict state) {
	struct ucpustate *new_state;
	new_state = dbg_enter_ucpustate_cr(entry, data, num_bytes, state);
	cpu_apply_ucpustate(new_state);
}

#ifndef LCPUSTATE_ALIAS
ATTR_WEAK ATTR_DBGTEXT_S("dbg_enter_lcpustate_c")
PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_lcpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct lcpustate *__restrict state) {
	struct lcpustate *new_state;
	new_state = dbg_enter_lcpustate_cr(entry, data, num_bytes, state);
	cpu_apply_lcpustate(new_state);
}
#endif /* !LCPUSTATE_ALIAS */

#ifndef KCPUSTATE_ALIAS
ATTR_WEAK ATTR_DBGTEXT_S("dbg_enter_kcpustate_c")
PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_kcpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct kcpustate *__restrict state) {
	struct kcpustate *new_state;
	new_state = dbg_enter_kcpustate_cr(entry, data, num_bytes, state);
	cpu_apply_kcpustate(new_state);
}
#endif /* !KCPUSTATE_ALIAS */

#ifndef ICPUSTATE_ALIAS
ATTR_WEAK ATTR_DBGTEXT_S("dbg_enter_icpustate_c")
PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_icpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct icpustate *__restrict state) {
	struct icpustate *new_state;
	new_state = dbg_enter_icpustate_cr(entry, data, num_bytes, state);
	cpu_apply_icpustate(new_state);
}
#endif /* !ICPUSTATE_ALIAS */

#ifndef SCPUSTATE_ALIAS
ATTR_WEAK ATTR_DBGTEXT_S("dbg_enter_scpustate_c")
PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_scpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct scpustate *__restrict state) {
	struct scpustate *new_state;
	new_state = dbg_enter_scpustate_cr(entry, data, num_bytes, state);
	cpu_apply_scpustate(new_state);
}
#endif /* !SCPUSTATE_ALIAS */

#ifndef FCPUSTATE_ALIAS
ATTR_WEAK ATTR_DBGTEXT_S("dbg_enter_fcpustate_c")
PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL
dbg_enter_fcpustate_c(dbg_entry_c_t entry, void const *data,
                      size_t num_bytes, struct fcpustate *__restrict state) {
	struct fcpustate *new_state;
	new_state = dbg_enter_fcpustate_cr(entry, data, num_bytes, state);
	cpu_apply_fcpustate(new_state);
}
#endif /* !FCPUSTATE_ALIAS */

DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_ENTRY_C */
