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

#include <kos/kernel/paging.h> /* KERNEL_DEBUG_STACKSIZE */

#include <stdbool.h>

#include <libinstrlen/bits/isa.h>
#include <libunwind/api.h>
#include <libunwind/cfi.h>

DECL_BEGIN

#ifdef __CC__

/* The stack from which debug code is executed. */
#ifndef __dbg_stack_defined
#define __dbg_stack_defined
DATDEF byte_t dbg_stack[KERNEL_DEBUG_STACKSIZE];
#endif /* !__dbg_stack_defined */

#ifndef __dbg_active_defined
#define __dbg_active_defined
/* Set to true while the debugger is currently active.
 * NOTE: This variable may be used to test if the system is being debugged. */
DATDEF bool const dbg_active;
#endif /* !__dbg_active_defined */

/* [1..1] The thread that is currently being viewed. */
DATDEF struct task *dbg_current;

/* [1..1] The cpu that is hosting the debugger (== THIS_TASK->t_cpu).
 *        Set to non-NULL before `dbg_active' becomes `true', and set
 *        to   `NULL'    before    `dbg_active'    becomes    `false' */
DATDEF struct cpu *const dbg_cpu;

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
#define DBG_REGLEVEL_EXIT 0 /* The register state to-be loaded when exiting debugger  mode.
                             * When `dbg_current == THIS_TASK', same as `DBG_REGLEVEL_ORIG' */
#define DBG_REGLEVEL_TRAP 1 /* The register state passed to `dbg_enter_r()', or `DBG_REGLEVEL_EXIT'. */
#define DBG_REGLEVEL_ORIG 2 /* The register state loaded by `dbg_current' when it resumes. */
#define DBG_REGLEVEL_VIEW 3 /* The register state currently being viewed (for the purpose of unwinding) */

/* Get/Set debugger register for some given level.
 * NOTE: These functions are written to be compatible with `unwind_getreg_t' / `unwind_setreg_t'
 * @param: arg: One of `DBG_REGLEVEL_*', cast as `(void *)(uintptr_t)DBG_REGLEVEL_*' */
FUNDEF unsigned int NOTHROW(LIBUNWIND_CC dbg_getreg)(/*uintptr_t level*/ void const *arg, uintptr_half_t cfi_regno, void *__restrict buf);
FUNDEF unsigned int NOTHROW(LIBUNWIND_CC dbg_setreg)(/*uintptr_t level*/ void *arg, uintptr_half_t cfi_regno, void const *__restrict buf);

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
	dbg_instruction_trypred(dbg_getpcreg(level), dbg_instrlen_isa(level))


LOCAL uintptr_t
NOTHROW(KCALL dbg_getregp)(unsigned int level, uintptr_half_t cfi_regno) {
	uintptr_t result;
#ifdef NDEBUG
	dbg_getreg((void *)(uintptr_t)level, cfi_regno, &result);
#else /* NDEBUG */
	unsigned int error;
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
#else /* NDEBUG */
	unsigned int error;
	__hybrid_assert(CFI_REGISTER_SIZE(sizeof(void *), cfi_regno) == sizeof(uintptr_t));
	error = dbg_setreg((void *)(uintptr_t)level, cfi_regno, &value);
	__hybrid_assert(error == UNWIND_SUCCESS);
#endif /* !NDEBUG */
}

/* Get/set a register, given its (arch-specific) name
 * NOTE: When `return > buflen', then
 *       dbg_getregbyname: The contents of `buf' are undefined.
 *       dbg_setregbyname:  The  register   was  not   written.
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

/* Return the ISA code for use with libinstrlen */
#ifndef ARCH_DEBUGGER_RT_HAVE_DBG_INSTRLEN_ISA
LOCAL ATTR_PURE WUNUSED instrlen_isa_t
NOTHROW(KCALL dbg_instrlen_isa)(unsigned int level) {
	instrlen_isa_t result;
	struct fcpustate cs;
	dbg_getallregs(level, &cs);
	result = instrlen_isa_from_fcpustate(&cs);
	return result;
}
#endif /* !ARCH_DEBUGGER_RT_HAVE_DBG_INSTRLEN_ISA */

/* Return the page directory of `dbg_current' */
FUNDEF ATTR_PURE WUNUSED pagedir_phys_t NOTHROW(KCALL dbg_getpagedir)(void);

/* Verify that the given page directory isn't corrupt. */
FUNDEF ATTR_PURE WUNUSED bool NOTHROW(KCALL dbg_verifypagedir)(pagedir_phys_t pdir);

/* [default(true)]
 * Allow managed memory access to be performed by  `dbg_(read|write)memory'
 * and friends. What this means is that (so-long as the kernel hasn't  been
 * poisoned, and this field is set to `true' (which is is during a debugger
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

/* Apply changes made to `DBG_REGLEVEL_VIEW' onto `DBG_REGLEVEL_ORIG'. */
FUNDEF void NOTHROW(FCALL dbg_applyview)(void);

/* Check if the register view has been changed. */
FUNDEF ATTR_PURE WUNUSED bool NOTHROW(FCALL dbg_changedview)(void);

#endif /* __CC__ */

DECL_END
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
#ifndef __dbg_active_defined
#define __dbg_active_defined
#define dbg_active 0
#endif /* !__dbg_active_defined */
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_RT_H */
