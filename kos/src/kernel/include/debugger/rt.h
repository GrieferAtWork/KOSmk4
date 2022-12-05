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
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_RT_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_RT_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/arch/rt.h>
#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/__assert.h>

#include <asm/intrin.h> /* __rdsp() */
#include <asm/isa.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/paging.h> /* KERNEL_DEBUG_STACKSIZE */

#include <stdbool.h>

#include <libcpustate/register.h> /* cpu_regno_t */
#include <libunwind/cfi.h>
#include <libunwind/errno.h>

DECL_BEGIN

#ifdef __CC__

/* The stack from which debug code is executed. */
#ifndef __dbg_stack_defined
#define __dbg_stack_defined
DATDEF byte_t dbg_stack[KERNEL_DEBUG_STACKSIZE];
#endif /* !__dbg_stack_defined */

/* Set to true while the debugger is currently active.
 * NOTE: This variable may be used to test if the system is being debugged. */
#ifndef __dbg_active_defined
#define __dbg_active_defined
DATDEF bool const dbg_active;
#endif /* !__dbg_active_defined */

/* [1..1] The cpu that is hosting the debugger (== THIS_TASK->t_cpu).
 *        Set to non-NULL  before `dbg_active' becomes  `true',
 *        and set to `NULL' before `dbg_active' becomes `false' */
DATDEF struct cpu *const dbg_cpu;

/* [1..1] The thread that is currently being viewed. */
DATDEF struct task *dbg_current;


/* Check if the caller is running on the debugger stack. */
FORCELOCAL WUNUSED bool NOTHROW(FCALL dbg_onstack)(void) {
	void *sp = __rdsp();
	return sp >= dbg_stack &&
	       sp <= dbg_stack + KERNEL_DEBUG_STACKSIZE;
}



/* DBG register access level:
 * dbg_enter()        --> DBG_RT_REGLEVEL_EXIT
 *                         |
 *                         v
 * dbg_enter_r(state) --> DBG_RT_REGLEVEL_TRAP
 *                         |
 *                         v
 * SET(dbg_current)   --> DBG_RT_REGLEVEL_ORIG
 *                         |        ^ apply
 *                 up/undo v        |
 *                        DBG_RT_REGLEVEL_VIEW
 */
#define DBG_RT_REGLEVEL_EXIT 0 /* The register  state to-be  loaded when  exiting debugger  mode.
                                * When `dbg_current == THIS_TASK', same as `DBG_RT_REGLEVEL_ORIG' */
#define DBG_RT_REGLEVEL_TRAP 1 /* The register state passed to `dbg_enter_r()', or `DBG_RT_REGLEVEL_EXIT'. */
#define DBG_RT_REGLEVEL_ORIG 2 /* The register state loaded by `dbg_current' when it resumes. */
#define DBG_RT_REGLEVEL_VIEW 3 /* The register state currently being viewed (for the purpose of unwinding) */

/* Get/Set debugger register for some given level.
 * NOTE: These functions are written to be compatible with `unwind_getreg_t' / `unwind_setreg_t'
 * @param: arg: One of `DBG_RT_REGLEVEL_*', cast as `(void *)(uintptr_t)DBG_RT_REGLEVEL_*' */
FUNDEF unwind_errno_t NOTHROW(LIBUNWIND_CC dbg_getreg)(/*uintptr_t level*/ void const *arg, uintptr_half_t cfi_regno, void *__restrict buf);
FUNDEF unwind_errno_t NOTHROW(LIBUNWIND_CC dbg_setreg)(/*uintptr_t level*/ void *arg, uintptr_half_t cfi_regno, void const *__restrict buf);

/* Get/Set the PC/SP registers of a given register level. */
#define dbg_getpcreg(level)        (byte_t const *)dbg_getregp(level, CFI_UNWIND_REGISTER_PC(sizeof(void *)))
#define dbg_setpcreg(level, value) dbg_setregp(level, CFI_UNWIND_REGISTER_PC(sizeof(void *)), (uintptr_t)(value))
#define dbg_getspreg(level)        (byte_t *)dbg_getregp(level, CFI_UNWIND_REGISTER_SP(sizeof(void *)))
#define dbg_setspreg(level, value) dbg_setregp(level, CFI_UNWIND_REGISTER_SP(sizeof(void *)), (uintptr_t)(value))

/* Return the size of a pointer within the context of `dbg_current' */
#ifndef dbg_current_sizeof_pointer
#define dbg_current_sizeof_pointer() __SIZEOF_POINTER__
#endif /* !dbg_current_sizeof_pointer */

/* Return the fault program counter position
 * That is: the address of the last-executed instruction */
#define dbg_getfaultpcreg(level) \
	dbg_instruction_trypred(dbg_getpcreg(level), dbg_rt_getisa(level))


LOCAL uintptr_t
NOTHROW(KCALL dbg_getregp)(unsigned int level, uintptr_half_t cfi_regno) {
	uintptr_t result;
#ifdef NDEBUG
	dbg_getreg((void *)(uintptr_t)level, cfi_regno, &result);
#else  /* NDEBUG */
	unwind_errno_t error;
	__hybrid_assert(CFI_REGISTER_SIZE(sizeof(void *), cfi_regno) == sizeof(uintptr_t));
	error = dbg_getreg((void *)(uintptr_t)level, cfi_regno, &result);
	__hybrid_assert(error == UNWIND_SUCCESS);
#endif /* !NDEBUG */
	return result;
}

LOCAL void
NOTHROW(KCALL dbg_setregp)(unsigned int level, uintptr_half_t cfi_regno, uintptr_t value) {
#ifdef NDEBUG
	dbg_setreg((void *)(uintptr_t)level, cfi_regno, &value);
#else  /* NDEBUG */
	unwind_errno_t error;
	__hybrid_assert(CFI_REGISTER_SIZE(sizeof(void *), cfi_regno) == sizeof(uintptr_t));
	error = dbg_setreg((void *)(uintptr_t)level, cfi_regno, &value);
	__hybrid_assert(error == UNWIND_SUCCESS);
#endif /* !NDEBUG */
}


/* Get/set a register, given its ID
 * NOTE: When `return > buflen', then
 *       dbg_rt_getregbyname: The contents of `buf' are undefined.
 *       dbg_rt_setregbyname:  The  register   was  not   written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of the values from <asm/registers.h>
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
FUNDEF size_t NOTHROW(KCALL dbg_rt_getregbyid)(unsigned int level, cpu_regno_t regno, void *__restrict buf, size_t buflen);
FUNDEF size_t NOTHROW(KCALL dbg_rt_setregbyid)(unsigned int level, cpu_regno_t regno, void const *__restrict buf, size_t buflen);

/* Get/Set a pointer-sized register, given its ID */
FUNDEF ATTR_PURE WUNUSED uintptr_t NOTHROW(KCALL dbg_rt_getregbyidp)(unsigned int level, cpu_regno_t regno);
FUNDEF bool NOTHROW(KCALL dbg_rt_setregbyidp)(unsigned int level, cpu_regno_t regno, uintptr_t value);


/* Get/set a register, given its (arch-specific) name
 * NOTE: When `return > buflen', then
 *       dbg_rt_getregbyname: The contents of `buf' are undefined.
 *       dbg_rt_setregbyname:  The  register   was  not   written.
 * @return: * : The required buffer size, or 0 when `name' isn't recognized. */
FUNDEF size_t NOTHROW(KCALL dbg_rt_getregbyname)(unsigned int level, char const *__restrict name, size_t namelen, void *__restrict buf, size_t buflen);
FUNDEF size_t NOTHROW(KCALL dbg_rt_setregbyname)(unsigned int level, char const *__restrict name, size_t namelen, void const *__restrict buf, size_t buflen);
FUNDEF bool NOTHROW(KCALL dbg_rt_getregbynamep)(unsigned int level, char const *__restrict name, size_t namelen, uintptr_t *__restrict result);
FUNDEF bool NOTHROW(KCALL dbg_rt_setregbynamep)(unsigned int level, char const *__restrict name, size_t namelen, uintptr_t value);

struct fcpustate;

/* Get/set all registers. */
FUNDEF void NOTHROW(KCALL dbg_rt_getallregs)(unsigned int level, struct fcpustate *__restrict state);
FUNDEF void NOTHROW(KCALL dbg_rt_setallregs)(unsigned int level, struct fcpustate const *__restrict state);

/* Return the ISA code for use with libinstrlen */
FUNDEF ATTR_PURE WUNUSED isa_t
NOTHROW(KCALL dbg_rt_getisa)(unsigned int level);

/* Return the page directory of `dbg_current' */
FUNDEF ATTR_PURE WUNUSED pagedir_phys_t NOTHROW(KCALL dbg_rt_getpagedir)(void);

/* Verify that the given page directory isn't corrupt. */
FUNDEF ATTR_PURE WUNUSED bool NOTHROW(KCALL dbg_rt_verifypagedir)(pagedir_phys_t pdir);

/* [default(true)]
 * Allow managed memory access to be performed by  `dbg_(read|write)memory'
 * and friends. What this means is that (so-long as the kernel hasn't  been
 * poisoned, and this field is set to `true' (which it is during a debugger
 * reset))  the below functions  can be used to  load lazy memory mappings,
 * and initiate the regular copy-on-write semantics expected by  high-level
 * memory access, and as would  also be done if  the access was being  done
 * directly, rather than through the below functions.
 * This  in turn is mainly useful when debugging user-space programs, where
 * this functionality allows one to  view memory that hasn't been  accessed
 * by the user-space program, yet, or was at one point off-loaded into swap
 * memory. But note  that this field  is ignored once  the kernel has  been
 * poisoned,  as this kind  of functionality may  cause the debugger memory
 * primitives  to call into  possibly faulty kernel  code (such as possibly
 * faulty disk drivers).
 * Also note that VIO memory is _never_ dispatched while in debugger  mode,
 * not  even when accessed  directly. Instead, any  VIO region will instead
 * result in a SEGFAULT, with the exception of the userkern segment,  which
 * simply acts as though it  didn't exist, allowing pass-through access  to
 * the actual kernel (meaning that when passed a kernel-space address, then
 * the below functions will instead read/write memory to/from kernel-space) */
DATDEF bool dbg_memory_managed;

/* Get/set memory in the context of `dbg_current'
 * NOTE: These functions will not make use  of copy-on-write or lazy memory  allocations,
 *       but will instead indicate an error, or (in when `force' is true), write directly
 *       to the physical memory backing of the underlying page directory.
 * @return: * : The number of trailing bytes that could not be copied. */
FUNDEF size_t NOTHROW(KCALL dbg_readmemory)(void const *addr, void *__restrict buf, size_t num_bytes);
FUNDEF size_t NOTHROW(KCALL dbg_writememory)(void *addr, void const *__restrict buf, size_t num_bytes, bool force);
FUNDEF size_t NOTHROW(KCALL dbg_setmemory)(void *addr, byte_t byte, size_t num_bytes, bool force);
/* Move memory from `src', and write it back to `dst' */
FUNDEF size_t NOTHROW(KCALL dbg_movememory)(void *dst, void const *src, size_t num_bytes, bool force);
#define dbg_movememorydown dbg_movememory
#define dbg_movememoryup   dbg_movememory

/* Apply changes made to `DBG_RT_REGLEVEL_VIEW' onto `DBG_RT_REGLEVEL_ORIG'. */
FUNDEF void NOTHROW(FCALL dbg_rt_applyview)(void);

/* Check if the register view has been changed. */
FUNDEF ATTR_PURE WUNUSED bool NOTHROW(FCALL dbg_rt_changedview)(void);

#endif /* __CC__ */


/************************************************************************/
/* Debugger exit state                                                  */
/************************************************************************/

/* CPU state kind codes. */
#define DBG_RT_STATEKIND_NONE 0 /* No DBG_RT_REGLEVEL_TRAP-level CPU state */

/*[[[deemon
import * from deemon;
local STATES = [
	"ucpustate",
	"lcpustate",
	"kcpustate",
	"icpustate",
	"scpustate",
	"fcpustate",
];
function getPossibleAliasesForState(state: string): {string...} {
	return STATES[:STATES.index(state)];
}

for (local state: STATES) {
	local name = state.rsstrip("state").upper();
	print("/" "* #define DBG_RT_STATEKIND_", name, " ... *" "/");
	local aliases = getPossibleAliasesForState(state);
	local isFirst = true;
	for (local alias: aliases) {
		local aliasName = alias.rsstrip("state").upper();
		local isAlias = f"{state.upper()}_IS_{alias.upper()}";
		if (isFirst) {
			isFirst = false;
			print("#ifdef ", isAlias);
		} else {
			print("#elif defined(", isAlias, ")");
		}
		print("#define DBG_RT_STATEKIND_", name, "_ISALIAS");
		print("#define DBG_RT_STATEKIND_", name, " DBG_RT_STATEKIND_", aliasName);
	}
	local lowerAliasCount = " + ".join(for (local a: aliases[1:]) f"defined({a.upper()}_ALIAS)");
	for (local n: [1:#aliases]) {
		local eqN = #aliases - n;
		if (isFirst) {
			if ("+" !in lowerAliasCount && eqN == 1) {
				print("#ifdef ", lowerAliasCount.lsstrip("defined(").rsstrip(")"));
			} else {
				print("#if (", lowerAliasCount, ") == ", eqN);
			}
			isFirst = false;
		} else if ("+" !in lowerAliasCount && eqN == 1) {
			print("#elif ", lowerAliasCount);
		} else {
			print("#elif (", lowerAliasCount, ") == ", eqN);
		}
		print("#define DBG_RT_STATEKIND_", name, " ", (n + 1));
	}

	if (!isFirst)
		print("#else /" "* ... *" "/");
	print("#define DBG_RT_STATEKIND_", name, " ", (#aliases + 1));
	if (!isFirst)
		print("#endif /" "* !... *" "/");
	print;
}
]]]*/
/* #define DBG_RT_STATEKIND_UCPU ... */
#define DBG_RT_STATEKIND_UCPU 1

/* #define DBG_RT_STATEKIND_LCPU ... */
#ifdef LCPUSTATE_IS_UCPUSTATE
#define DBG_RT_STATEKIND_LCPU_ISALIAS
#define DBG_RT_STATEKIND_LCPU DBG_RT_STATEKIND_UCPU
#else /* ... */
#define DBG_RT_STATEKIND_LCPU 2
#endif /* !... */

/* #define DBG_RT_STATEKIND_KCPU ... */
#ifdef KCPUSTATE_IS_UCPUSTATE
#define DBG_RT_STATEKIND_KCPU_ISALIAS
#define DBG_RT_STATEKIND_KCPU DBG_RT_STATEKIND_UCPU
#elif defined(KCPUSTATE_IS_LCPUSTATE)
#define DBG_RT_STATEKIND_KCPU_ISALIAS
#define DBG_RT_STATEKIND_KCPU DBG_RT_STATEKIND_LCPU
#elif defined(LCPUSTATE_ALIAS)
#define DBG_RT_STATEKIND_KCPU 2
#else /* ... */
#define DBG_RT_STATEKIND_KCPU 3
#endif /* !... */

/* #define DBG_RT_STATEKIND_ICPU ... */
#ifdef ICPUSTATE_IS_UCPUSTATE
#define DBG_RT_STATEKIND_ICPU_ISALIAS
#define DBG_RT_STATEKIND_ICPU DBG_RT_STATEKIND_UCPU
#elif defined(ICPUSTATE_IS_LCPUSTATE)
#define DBG_RT_STATEKIND_ICPU_ISALIAS
#define DBG_RT_STATEKIND_ICPU DBG_RT_STATEKIND_LCPU
#elif defined(ICPUSTATE_IS_KCPUSTATE)
#define DBG_RT_STATEKIND_ICPU_ISALIAS
#define DBG_RT_STATEKIND_ICPU DBG_RT_STATEKIND_KCPU
#elif (defined(LCPUSTATE_ALIAS) + defined(KCPUSTATE_ALIAS)) == 2
#define DBG_RT_STATEKIND_ICPU 2
#elif (defined(LCPUSTATE_ALIAS) + defined(KCPUSTATE_ALIAS)) == 1
#define DBG_RT_STATEKIND_ICPU 3
#else /* ... */
#define DBG_RT_STATEKIND_ICPU 4
#endif /* !... */

/* #define DBG_RT_STATEKIND_SCPU ... */
#ifdef SCPUSTATE_IS_UCPUSTATE
#define DBG_RT_STATEKIND_SCPU_ISALIAS
#define DBG_RT_STATEKIND_SCPU DBG_RT_STATEKIND_UCPU
#elif defined(SCPUSTATE_IS_LCPUSTATE)
#define DBG_RT_STATEKIND_SCPU_ISALIAS
#define DBG_RT_STATEKIND_SCPU DBG_RT_STATEKIND_LCPU
#elif defined(SCPUSTATE_IS_KCPUSTATE)
#define DBG_RT_STATEKIND_SCPU_ISALIAS
#define DBG_RT_STATEKIND_SCPU DBG_RT_STATEKIND_KCPU
#elif defined(SCPUSTATE_IS_ICPUSTATE)
#define DBG_RT_STATEKIND_SCPU_ISALIAS
#define DBG_RT_STATEKIND_SCPU DBG_RT_STATEKIND_ICPU
#elif (defined(LCPUSTATE_ALIAS) + defined(KCPUSTATE_ALIAS) + defined(ICPUSTATE_ALIAS)) == 3
#define DBG_RT_STATEKIND_SCPU 2
#elif (defined(LCPUSTATE_ALIAS) + defined(KCPUSTATE_ALIAS) + defined(ICPUSTATE_ALIAS)) == 2
#define DBG_RT_STATEKIND_SCPU 3
#elif (defined(LCPUSTATE_ALIAS) + defined(KCPUSTATE_ALIAS) + defined(ICPUSTATE_ALIAS)) == 1
#define DBG_RT_STATEKIND_SCPU 4
#else /* ... */
#define DBG_RT_STATEKIND_SCPU 5
#endif /* !... */

/* #define DBG_RT_STATEKIND_FCPU ... */
#ifdef FCPUSTATE_IS_UCPUSTATE
#define DBG_RT_STATEKIND_FCPU_ISALIAS
#define DBG_RT_STATEKIND_FCPU DBG_RT_STATEKIND_UCPU
#elif defined(FCPUSTATE_IS_LCPUSTATE)
#define DBG_RT_STATEKIND_FCPU_ISALIAS
#define DBG_RT_STATEKIND_FCPU DBG_RT_STATEKIND_LCPU
#elif defined(FCPUSTATE_IS_KCPUSTATE)
#define DBG_RT_STATEKIND_FCPU_ISALIAS
#define DBG_RT_STATEKIND_FCPU DBG_RT_STATEKIND_KCPU
#elif defined(FCPUSTATE_IS_ICPUSTATE)
#define DBG_RT_STATEKIND_FCPU_ISALIAS
#define DBG_RT_STATEKIND_FCPU DBG_RT_STATEKIND_ICPU
#elif defined(FCPUSTATE_IS_SCPUSTATE)
#define DBG_RT_STATEKIND_FCPU_ISALIAS
#define DBG_RT_STATEKIND_FCPU DBG_RT_STATEKIND_SCPU
#elif (defined(LCPUSTATE_ALIAS) + defined(KCPUSTATE_ALIAS) + defined(ICPUSTATE_ALIAS) + defined(SCPUSTATE_ALIAS)) == 4
#define DBG_RT_STATEKIND_FCPU 2
#elif (defined(LCPUSTATE_ALIAS) + defined(KCPUSTATE_ALIAS) + defined(ICPUSTATE_ALIAS) + defined(SCPUSTATE_ALIAS)) == 3
#define DBG_RT_STATEKIND_FCPU 3
#elif (defined(LCPUSTATE_ALIAS) + defined(KCPUSTATE_ALIAS) + defined(ICPUSTATE_ALIAS) + defined(SCPUSTATE_ALIAS)) == 2
#define DBG_RT_STATEKIND_FCPU 4
#elif (defined(LCPUSTATE_ALIAS) + defined(KCPUSTATE_ALIAS) + defined(ICPUSTATE_ALIAS) + defined(SCPUSTATE_ALIAS)) == 1
#define DBG_RT_STATEKIND_FCPU 5
#else /* ... */
#define DBG_RT_STATEKIND_FCPU 6
#endif /* !... */
/*[[[end]]]*/


#ifdef __CC__
/* DBG trap state information. */
/* [valid_if(dbg_rt_trapstatekind != DBG_RT_STATEKIND_NONE)]
 * This is a `struct Xcpustate *' (depending on `dbg_rt_trapstatekind') */
DATDEF void *dbg_rt_trapstate;

/* The kind of state stored in `dbg_rt_trapstate' (one of `DBG_RT_STATEKIND_*') */
DATDEF unsigned int dbg_rt_trapstatekind;
#endif /* __CC__ */


DECL_END

#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
#ifndef __dbg_active_defined
#define __dbg_active_defined
#define dbg_active 0
#endif /* !__dbg_active_defined */
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_RT_H */
