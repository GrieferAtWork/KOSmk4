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
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_ENTRY_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_ENTRY_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <kernel/types.h>

#include <stdbool.h>

DECL_BEGIN

#define OFFSET_DBG_ENTRY_INFO_ENTRY   0
#define OFFSET_DBG_ENTRY_INFO_ARGC    __SIZEOF_POINTER__
#define OFFSET_DBG_ENTRY_INFO_ARGV(i) (__SIZEOF_POINTER__ * ((i) + 2))
#ifdef __CC__

struct fcpustate;
struct ucpustate;
struct lcpustate;
struct kcpustate;
struct icpustate;
struct scpustate;

typedef void (KCALL *dbg_entry_t)();
struct dbg_entry_info {
	dbg_entry_t                     ei_entry; /* [1..1] Debugger entry point */
	size_t                          ei_argc;  /* Number of pointer-arguments taken by `ei_entry' */
	COMPILER_FLEXIBLE_ARRAY(void *, ei_argv); /* [ei_argc] Arguments to pass to `ei_entry' */
};

#define STRUCT_DBG_ENTRY_INFO(argc)                                                      \
	struct {                                                                             \
		dbg_entry_t ei_entry;      /* [1..1] Debugger entry point */                     \
		size_t      ei_argc;       /* Number of pointer-arguments taken by `ei_entry' */ \
		void       *ei_argv[argc]; /* [ei_argc] Arguments to pass to `ei_entry' */       \
	}

#define STRUCT_DBG_ENTRY_INFO0                                                           \
	struct {                                                                             \
		dbg_entry_t ei_entry;      /* [1..1] Debugger entry point */                     \
		size_t      ei_argc;       /* Number of pointer-arguments taken by `ei_entry' */ \
	}

/* Set to true while the debugger is currently active.
 * NOTE: This variable may be used to test if the system is being debugged. */
DATDEF bool dbg_active;

/* The default debugger main entry function.
 * This function is used as entry when `dbg()' is
 * called, or the `info' of `dbg_enter()' is `NULL' */
FUNDEF void KCALL dbg_main(uintptr_t show_welcome);

/* Exit debugger mode (same as returning from a `dbg_entry_t' function) */
FUNDEF ATTR_NORETURN void KCALL dbg_exit(void);

/* A special debugger entry function that can be used to quickly enter
 * debugger mode at an arbitrary code location, and greet the user with
 * a CLI-based interface for querying the system state.
 * NOTE: This function preserves _all_ registers! */
FUNDEF void KCALL dbg(void);

/* Debugger entry functions
 * NOTE: All of these functions preserve _all_ registers (except for the return register!)
 * NOTE: When `info' is `NULL', enter the default debugger function. */
FUNDEF void FCALL dbg_enter_here(struct dbg_entry_info const *info);
FUNDEF ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_fcpustate(struct dbg_entry_info const *info, struct fcpustate *__restrict state);
FUNDEF ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_ucpustate(struct dbg_entry_info const *info, struct ucpustate *__restrict state);
FUNDEF ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_lcpustate(struct dbg_entry_info const *info, struct lcpustate *__restrict state);
FUNDEF ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_kcpustate(struct dbg_entry_info const *info, struct kcpustate *__restrict state);
FUNDEF ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_icpustate(struct dbg_entry_info const *info, struct icpustate *__restrict state);
FUNDEF ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_scpustate(struct dbg_entry_info const *info, struct scpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct fcpustate *FCALL dbg_enter_fcpustate_r(struct dbg_entry_info const *info, struct fcpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct ucpustate *FCALL dbg_enter_ucpustate_r(struct dbg_entry_info const *info, struct ucpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct lcpustate *FCALL dbg_enter_lcpustate_r(struct dbg_entry_info const *info, struct lcpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct kcpustate *FCALL dbg_enter_kcpustate_r(struct dbg_entry_info const *info, struct kcpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct icpustate *FCALL dbg_enter_icpustate_r(struct dbg_entry_info const *info, struct icpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct scpustate *FCALL dbg_enter_scpustate_r(struct dbg_entry_info const *info, struct scpustate *__restrict state);

#ifdef __cplusplus
extern "C++" {
FUNDEF NONNULL((1)) void FCALL dbg_enter(struct dbg_entry_info const *info) ASMNAME("dbg_enter_here");
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct dbg_entry_info const *info, struct fcpustate *__restrict state) ASMNAME("dbg_enter_fcpustate");
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct dbg_entry_info const *info, struct ucpustate *__restrict state) ASMNAME("dbg_enter_ucpustate");
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct dbg_entry_info const *info, struct lcpustate *__restrict state) ASMNAME("dbg_enter_lcpustate");
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct dbg_entry_info const *info, struct kcpustate *__restrict state) ASMNAME("dbg_enter_kcpustate");
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct dbg_entry_info const *info, struct icpustate *__restrict state) ASMNAME("dbg_enter_icpustate");
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct dbg_entry_info const *info, struct scpustate *__restrict state) ASMNAME("dbg_enter_scpustate");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct fcpustate *FCALL dbg_enter_r(struct dbg_entry_info const *info, struct fcpustate *__restrict state) ASMNAME("dbg_enter_fcpustate_r");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct ucpustate *FCALL dbg_enter_r(struct dbg_entry_info const *info, struct ucpustate *__restrict state) ASMNAME("dbg_enter_ucpustate_r");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct lcpustate *FCALL dbg_enter_r(struct dbg_entry_info const *info, struct lcpustate *__restrict state) ASMNAME("dbg_enter_lcpustate_r");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct kcpustate *FCALL dbg_enter_r(struct dbg_entry_info const *info, struct kcpustate *__restrict state) ASMNAME("dbg_enter_kcpustate_r");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL dbg_enter_r(struct dbg_entry_info const *info, struct icpustate *__restrict state) ASMNAME("dbg_enter_icpustate_r");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct scpustate *FCALL dbg_enter_r(struct dbg_entry_info const *info, struct scpustate *__restrict state) ASMNAME("dbg_enter_scpustate_r");
LOCAL NONNULL((1)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_here((struct dbg_entry_info *)&info); }
LOCAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg, struct fcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_fcpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg, struct ucpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_ucpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg, struct lcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_lcpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg, struct kcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_kcpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg, struct icpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_icpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg, struct scpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_scpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct fcpustate *FCALL dbg_enter_r(void (KCALL *main)(void *arg), void *arg, struct fcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; return dbg_enter_fcpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct ucpustate *FCALL dbg_enter_r(void (KCALL *main)(void *arg), void *arg, struct ucpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; return dbg_enter_ucpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct lcpustate *FCALL dbg_enter_r(void (KCALL *main)(void *arg), void *arg, struct lcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; return dbg_enter_lcpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct kcpustate *FCALL dbg_enter_r(void (KCALL *main)(void *arg), void *arg, struct kcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; return dbg_enter_kcpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL dbg_enter_r(void (KCALL *main)(void *arg), void *arg, struct icpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; return dbg_enter_icpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct scpustate *FCALL dbg_enter_r(void (KCALL *main)(void *arg), void *arg, struct scpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; return dbg_enter_scpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL NONNULL((1)) void FCALL dbg_enter(void (KCALL *main)(void)) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_here((struct dbg_entry_info *)&info); }
LOCAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void), struct fcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_fcpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void), struct ucpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_ucpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void), struct lcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_lcpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void), struct kcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_kcpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void), struct icpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_icpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void), struct scpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_scpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct fcpustate *FCALL dbg_enter_r(void (KCALL *main)(void), struct fcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; return dbg_enter_fcpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct ucpustate *FCALL dbg_enter_r(void (KCALL *main)(void), struct ucpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; return dbg_enter_ucpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct lcpustate *FCALL dbg_enter_r(void (KCALL *main)(void), struct lcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; return dbg_enter_lcpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct kcpustate *FCALL dbg_enter_r(void (KCALL *main)(void), struct kcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; return dbg_enter_kcpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL dbg_enter_r(void (KCALL *main)(void), struct icpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; return dbg_enter_icpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct scpustate *FCALL dbg_enter_r(void (KCALL *main)(void), struct scpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; return dbg_enter_scpustate_r((struct dbg_entry_info *)&info, state); }
}
#endif /* __cplusplus */


#endif /* __CC__ */

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_ENTRY_H */
