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
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_RT_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_RT_H 1

#include <kernel/compiler.h>
#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/__assert.h>

#include <debugger/arch/rt.h>
#include <kos/kernel/paging.h> /* KERNEL_DEBUG_STACKSIZE */

#include <stdbool.h>

#include <libunwind/api.h>
#include <libunwind/cfi.h>

DECL_BEGIN

#ifdef __CC__

/* The stack from which debug code is executed. */
DATDEF byte_t dbg_stack[KERNEL_DEBUG_STACKSIZE];

/* Set to true while the debugger is currently active.
 * NOTE: This variable may be used to test if the system is being debugged. */
DATDEF bool dbg_active;

/* [1..1] The thread that is currently being viewed. */
DATDEF struct task *dbg_current;

/* DBG register access level:
 * dbg_enter()        --> DBG_REGLEVEL_EXIT
 *                         |
 *                         v
 * dbg_enter_r(state) --> DBG_REGLEVEL_TRAP
 *                         |
 *                         v
 * SET(dbg_current)   --> DBG_REGLEVEL_ORIG
 *                         |        ^ apply
 *                 up/undo v        |
 *                        DBG_REGLEVEL_VIEW
 */
#define DBG_REGLEVEL_EXIT 0 /* The register state to-be loaded when exiting debugger mode.
                             * When `dbg_current != THIS_TASK', same as `DBG_REGLEVEL_ORIG' */
#define DBG_REGLEVEL_TRAP 1 /* The register state passed to `dbg_enter_r()', or `DBG_REGLEVEL_EXIT'.
                             * When `dbg_current != THIS_TASK', same as `DBG_REGLEVEL_ORIG' */
#define DBG_REGLEVEL_ORIG 2 /* The register state loaded by `dbg_current' when it resumes. */
#define DBG_REGLEVEL_VIEW 3 /* The register state currently being viewed (for the purpose of unwinding) */

/* Get/Set debugger register for some given level.
 * NOTE: These functions are written to be compatible with `unwind_getreg_t' / `unwind_setreg_t'
 * @param: arg: One of `DBG_REGLEVEL_*', cast as `(void *)(uintptr_t)DBG_REGLEVEL_*' */
FUNDEF bool NOTHROW(LIBUNWIND_CC dbg_getreg)(/*uintptr_t level*/ void const *arg, uintptr_half_t cfi_regno, void *__restrict buf);
FUNDEF bool NOTHROW(LIBUNWIND_CC dbg_setreg)(/*uintptr_t level*/ void *arg, uintptr_half_t cfi_regno, void const *__restrict buf);

/* Get/Set the PC/SP registers of a given register level. */
#define dbg_getpcreg(level)        dbg_getregp(level, CFI_UNWIND_REGISTER_PC)
#define dbg_setpcreg(level, value) dbg_setregp(level, CFI_UNWIND_REGISTER_PC, value)
#define dbg_getspreg(level)        dbg_getregp(level, CFI_UNWIND_REGISTER_SP)
#define dbg_setspreg(level, value) dbg_setregp(level, CFI_UNWIND_REGISTER_SP, value)

LOCAL uintptr_t
NOTHROW(KCALL dbg_getregp)(unsigned int level, uintptr_half_t cfi_regno) {
	uintptr_t result;
#ifdef NDEBUG
	dbg_getreg((void *)(uintptr_t)level, cfi_regno, &result);
#else /* NDEBUG */
	bool ok;
	__hybrid_assert(CFI_REGISTER_SIZE(cfi_regno) == sizeof(uintptr_t));
	ok = dbg_getreg((void *)(uintptr_t)level, cfi_regno, &result);
	__hybrid_assert(ok);
#endif /* !NDEBUG */
	return result;
}

LOCAL void
NOTHROW(KCALL dbg_setregp)(unsigned int level, uintptr_half_t cfi_regno, uintptr_t value) {
#ifdef NDEBUG
	dbg_setreg((void *)(uintptr_t)level, cfi_regno, &value);
#else /* NDEBUG */
	bool ok;
	__hybrid_assert(CFI_REGISTER_SIZE(cfi_regno) == sizeof(uintptr_t));
	ok = dbg_setreg((void *)(uintptr_t)level, cfi_regno, &value);
	__hybrid_assert(ok);
#endif /* !NDEBUG */
}

/* Get/set a register, given its (arch-specific) name
 * NOTE: When `return > buflen', then
 *       dbg_getregbyname: The contents of `buf' are undefined.
 *       dbg_setregbyname: The register was not written.
 * @return: * : The required buffer size, or 0 when `name' isn't recognized. */
FUNDEF size_t NOTHROW(KCALL dbg_getregbyname)(unsigned int level, char const *__restrict name, size_t namelen, void *__restrict buf, size_t buflen);
FUNDEF size_t NOTHROW(KCALL dbg_setregbyname)(unsigned int level, char const *__restrict name, size_t namelen, void const *__restrict buf, size_t buflen);
FUNDEF bool NOTHROW(KCALL dbg_getregbynamep)(unsigned int level, char const *__restrict name, size_t namelen, uintptr_t *__restrict result);
FUNDEF bool NOTHROW(KCALL dbg_setregbynamep)(unsigned int level, char const *__restrict name, size_t namelen, uintptr_t value);

struct fcpustate;
struct ucpustate;

/* Get/set all registers. */
FUNDEF void NOTHROW(KCALL dbg_getallregs)(unsigned int level, struct fcpustate *__restrict state);
FUNDEF void NOTHROW(KCALL dbg_setallregs)(unsigned int level, struct fcpustate const *__restrict state);

/* Return the page directory of `dbg_current' */
FUNDEF ATTR_PURE WUNUSED PAGEDIR_P_SELFTYPE NOTHROW(KCALL dbg_getpagedir)(void);

/* Verify that the given page directory isn't corrupt. */
FUNDEF ATTR_PURE WUNUSED bool NOTHROW(KCALL dbg_verifypagedir)(PAGEDIR_P_SELFTYPE pdir);

/* Get/set memory in the context of `dbg_current'
 * NOTE: These functions will not make use of copy-on-write or lazy memory allocations,
 *       but will instead indicate an error, or (in when `force' is true), write directly
 *       to the physical memory backing of the underlying page directory.
 * @return: * : The number of trailing bytes that could not be copied. */
FUNDEF size_t NOTHROW(KCALL dbg_readmemory)(void const *addr, void *__restrict buf, size_t num_bytes);
FUNDEF size_t NOTHROW(KCALL dbg_writememory)(void *addr, void const *__restrict buf, size_t num_bytes, bool force);

/* Apply changes made to `DBG_REGLEVEL_VIEW' onto `DBG_REGLEVEL_ORIG'. */
FUNDEF void NOTHROW(FCALL dbg_applyview)(void);

/* Check if the register view has been changed. */
FUNDEF ATTR_PURE WUNUSED bool NOTHROW(FCALL dbg_changedview)(void);

#endif /* __CC__ */

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_RT_H */
