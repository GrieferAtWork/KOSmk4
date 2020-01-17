/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_RT_C
#define GUARD_KERNEL_SRC_DEBUGGER_RT_C 1
#define DISABLE_BRANCH_PROFILING 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/function.h>
#include <debugger/rt.h>
#include <kernel/vm.h>

#include <hybrid/byteorder.h>

#include <string.h>

DECL_BEGIN

/* The stack from which debug code is executed. */
PUBLIC ATTR_DBGBSS byte_t dbg_stack[KERNEL_DEBUG_STACKSIZE] = {};

/* Set to true while the debugger is currently active.
 * NOTE: This variable may be used to test if the system is being debugged. */
PUBLIC ATTR_DBGBSS bool dbg_active = false;

/* [1..1] The thread that is currently being viewed. */
PUBLIC ATTR_DBGBSS struct task *dbg_current = NULL;

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
	return memcmp(&view, &orig, sizeof(struct fcpustate)) != 0;
}

PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_getregbynamep") bool
NOTHROW(KCALL dbg_getregbynamep)(unsigned int level, char const *__restrict name,
                                 size_t namelen, uintptr_t *__restrict result) {
	size_t reqlen;
	reqlen = dbg_getregbyname(level, name, namelen,
	                          result, sizeof(*result));
	if (!reqlen || reqlen > sizeof(*result))
		return false;
	if (reqlen < sizeof(*result)) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		memset((byte_t *)result + reqlen, 0, sizeof(*result) - reqlen);
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
		memmoveup((byte_t *)result + sizeof(*result) - reqlen,
		          result, sizeof(*result) - reqlen);
		memset(result, 0, sizeof(*result) - reqlen);
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
	}
	return true;
}

PUBLIC ATTR_WEAK ATTR_DBGTEXT_S("dbg_setregbynamep") bool
NOTHROW(KCALL dbg_setregbynamep)(unsigned int level, char const *__restrict name,
                                 size_t namelen, uintptr_t value) {
	size_t reqlen;
	reqlen = dbg_setregbyname(level, name, namelen,
	                          &value, sizeof(value));
	if (!reqlen || reqlen > sizeof(value))
		return false;
	return true;
}



DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_RT_C */
