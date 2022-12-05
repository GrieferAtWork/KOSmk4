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
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_ENTRY_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_ENTRY_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <kernel/types.h>

#include <kos/kernel/cpu-state.h>

#include <stdbool.h>

DECL_BEGIN

#define OFFSET_DBG_ENTRY_INFO_ENTRY   0
#define OFFSET_DBG_ENTRY_INFO_ARGC    __SIZEOF_POINTER__
#define OFFSET_DBG_ENTRY_INFO_ARGV(i) (__SIZEOF_POINTER__ * ((i) + 2))
#ifdef __CC__

typedef void (KCALL *dbg_entry_t)(/*...*/);
typedef void (KCALL *dbg_entry_c_t)(void *arg);

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
#ifndef __dbg_active_defined
#define __dbg_active_defined
DATDEF bool dbg_active;
#endif /* !__dbg_active_defined */

/* The  default  debugger   main  entry   function.
 * This function is used  as entry when `dbg()'  is
 * called, or the `info' of `dbg_enter()' is `NULL' */
FUNDEF void KCALL dbg_main(uintptr_t show_welcome);

/* Exit debugger mode (same as returning from a `dbg_entry_t' function) */
FUNDEF ABNORMAL_RETURN ATTR_NORETURN void KCALL dbg_exit(void);

/* A special debugger entry function that can be used to quickly  enter
 * debugger mode at an arbitrary code location, and greet the user with
 * a CLI-based interface for querying the system state.
 * NOTE: This function preserves _all_ registers! */
FUNDEF void KCALL dbg(void);

/* Debugger entry functions
 * NOTE: All of these functions preserve _all_ registers (except for the return register!)
 * NOTE: When `info' is `NULL', enter the default debugger function. */
FUNDEF void FCALL dbg_enter_here(struct dbg_entry_info const *info);
FUNDEF NONNULL((1, 2)) void FCALL dbg_enter_here_c(dbg_entry_c_t entry, void const *data, size_t num_bytes);

FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_ucpustate(struct dbg_entry_info const *info, struct ucpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct ucpustate *FCALL dbg_enter_ucpustate_r(struct dbg_entry_info const *info, struct ucpustate *__restrict state);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter_ucpustate_c(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct ucpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct ucpustate *FCALL dbg_enter_ucpustate_cr(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct ucpustate *__restrict state);

#ifdef LCPUSTATE_ALIAS
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_lcpustate(struct dbg_entry_info const *info, struct lcpustate *__restrict state) ASMNAME("dbg_enter_" LCPUSTATE_ALIAS_STR);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct lcpustate *FCALL dbg_enter_lcpustate_r(struct dbg_entry_info const *info, struct lcpustate *__restrict state) ASMNAME("dbg_enter_" LCPUSTATE_ALIAS_STR "_r");
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter_lcpustate_c(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct lcpustate *__restrict state) ASMNAME("dbg_enter_" LCPUSTATE_ALIAS_STR "_c");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct lcpustate *FCALL dbg_enter_lcpustate_cr(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct lcpustate *__restrict state) ASMNAME("dbg_enter_" LCPUSTATE_ALIAS_STR "_cr");
#else /* LCPUSTATE_ALIAS */
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_lcpustate(struct dbg_entry_info const *info, struct lcpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct lcpustate *FCALL dbg_enter_lcpustate_r(struct dbg_entry_info const *info, struct lcpustate *__restrict state);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter_lcpustate_c(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct lcpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct lcpustate *FCALL dbg_enter_lcpustate_cr(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct lcpustate *__restrict state);
#endif /* !LCPUSTATE_ALIAS */

#ifdef KCPUSTATE_ALIAS
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_kcpustate(struct dbg_entry_info const *info, struct kcpustate *__restrict state) ASMNAME("dbg_enter_" KCPUSTATE_ALIAS_STR);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct kcpustate *FCALL dbg_enter_kcpustate_r(struct dbg_entry_info const *info, struct kcpustate *__restrict state) ASMNAME("dbg_enter_" KCPUSTATE_ALIAS_STR "_r");
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter_kcpustate_c(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct kcpustate *__restrict state) ASMNAME("dbg_enter_" KCPUSTATE_ALIAS_STR "_c");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct kcpustate *FCALL dbg_enter_kcpustate_cr(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct kcpustate *__restrict state) ASMNAME("dbg_enter_" KCPUSTATE_ALIAS_STR "_cr");
#else /* KCPUSTATE_ALIAS */
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_kcpustate(struct dbg_entry_info const *info, struct kcpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct kcpustate *FCALL dbg_enter_kcpustate_r(struct dbg_entry_info const *info, struct kcpustate *__restrict state);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter_kcpustate_c(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct kcpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct kcpustate *FCALL dbg_enter_kcpustate_cr(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct kcpustate *__restrict state);
#endif /* !KCPUSTATE_ALIAS */

#ifdef ICPUSTATE_ALIAS
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_icpustate(struct dbg_entry_info const *info, struct icpustate *__restrict state) ASMNAME("dbg_enter_" ICPUSTATE_ALIAS_STR);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct icpustate *FCALL dbg_enter_icpustate_r(struct dbg_entry_info const *info, struct icpustate *__restrict state) ASMNAME("dbg_enter_" ICPUSTATE_ALIAS_STR "_r");
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter_icpustate_c(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct icpustate *__restrict state) ASMNAME("dbg_enter_" ICPUSTATE_ALIAS_STR "_c");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct icpustate *FCALL dbg_enter_icpustate_cr(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct icpustate *__restrict state) ASMNAME("dbg_enter_" ICPUSTATE_ALIAS_STR "_cr");
#else /* ICPUSTATE_ALIAS */
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_icpustate(struct dbg_entry_info const *info, struct icpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct icpustate *FCALL dbg_enter_icpustate_r(struct dbg_entry_info const *info, struct icpustate *__restrict state);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter_icpustate_c(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct icpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct icpustate *FCALL dbg_enter_icpustate_cr(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct icpustate *__restrict state);
#endif /* !ICPUSTATE_ALIAS */

#ifdef SCPUSTATE_ALIAS
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_scpustate(struct dbg_entry_info const *info, struct scpustate *__restrict state) ASMNAME("dbg_enter_" SCPUSTATE_ALIAS_STR);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct scpustate *FCALL dbg_enter_scpustate_r(struct dbg_entry_info const *info, struct scpustate *__restrict state) ASMNAME("dbg_enter_" SCPUSTATE_ALIAS_STR "_r");
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter_scpustate_c(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct scpustate *__restrict state) ASMNAME("dbg_enter_" SCPUSTATE_ALIAS_STR "_c");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct scpustate *FCALL dbg_enter_scpustate_cr(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct scpustate *__restrict state) ASMNAME("dbg_enter_" SCPUSTATE_ALIAS_STR "_cr");
#else /* SCPUSTATE_ALIAS */
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_scpustate(struct dbg_entry_info const *info, struct scpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct scpustate *FCALL dbg_enter_scpustate_r(struct dbg_entry_info const *info, struct scpustate *__restrict state);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter_scpustate_c(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct scpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct scpustate *FCALL dbg_enter_scpustate_cr(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct scpustate *__restrict state);
#endif /* !SCPUSTATE_ALIAS */

#ifdef FCPUSTATE_ALIAS
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_fcpustate(struct dbg_entry_info const *info, struct fcpustate *__restrict state) ASMNAME("dbg_enter_" FCPUSTATE_ALIAS_STR);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct fcpustate *FCALL dbg_enter_fcpustate_r(struct dbg_entry_info const *info, struct fcpustate *__restrict state) ASMNAME("dbg_enter_" FCPUSTATE_ALIAS_STR "_r");
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter_fcpustate_c(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct fcpustate *__restrict state) ASMNAME("dbg_enter_" FCPUSTATE_ALIAS_STR "_c");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct fcpustate *FCALL dbg_enter_fcpustate_cr(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct fcpustate *__restrict state) ASMNAME("dbg_enter_" FCPUSTATE_ALIAS_STR "_cr");
#else /* FCPUSTATE_ALIAS */
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((2)) void FCALL dbg_enter_fcpustate(struct dbg_entry_info const *info, struct fcpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((2)) struct fcpustate *FCALL dbg_enter_fcpustate_r(struct dbg_entry_info const *info, struct fcpustate *__restrict state);
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter_fcpustate_c(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct fcpustate *__restrict state);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct fcpustate *FCALL dbg_enter_fcpustate_cr(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct fcpustate *__restrict state);
#endif /* !FCPUSTATE_ALIAS */

#ifdef __cplusplus
extern "C++" {
FUNDEF NONNULL((1)) void FCALL dbg_enter(struct dbg_entry_info const *info) ASMNAME("dbg_enter_here");
LOCAL ATTR_ARTIFICIAL NONNULL((1)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_here((struct dbg_entry_info *)&info); }
LOCAL ATTR_ARTIFICIAL NONNULL((1)) void FCALL dbg_enter(void (KCALL *main)(void)) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_here((struct dbg_entry_info *)&info); }
FUNDEF NONNULL((1, 2)) void FCALL dbg_enter(dbg_entry_c_t entry, void const *data, size_t num_bytes) ASMNAME("dbg_enter_here_c");

FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct dbg_entry_info const *info, struct ucpustate *__restrict state) ASMNAME("dbg_enter_ucpustate");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct ucpustate *FCALL dbg_enter_r(struct dbg_entry_info const *info, struct ucpustate *__restrict state) ASMNAME("dbg_enter_ucpustate_r");
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct ucpustate *__restrict state) ASMNAME("dbg_enter_ucpustate_c");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct ucpustate *FCALL dbg_enter_r(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct ucpustate *__restrict state) ASMNAME("dbg_enter_ucpustate_cr");
LOCAL ABNORMAL_RETURN ATTR_ARTIFICIAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg, struct ucpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_ucpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct ucpustate *FCALL dbg_enter_r(void (KCALL *main)(void *arg), void *arg, struct ucpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; return dbg_enter_ucpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ABNORMAL_RETURN ATTR_ARTIFICIAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void), struct ucpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_ucpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct ucpustate *FCALL dbg_enter_r(void (KCALL *main)(void), struct ucpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; return dbg_enter_ucpustate_r((struct dbg_entry_info *)&info, state); }

#ifndef LCPUSTATE_ALIAS
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct dbg_entry_info const *info, struct lcpustate *__restrict state) ASMNAME("dbg_enter_lcpustate");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct lcpustate *FCALL dbg_enter_r(struct dbg_entry_info const *info, struct lcpustate *__restrict state) ASMNAME("dbg_enter_lcpustate_r");
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct lcpustate *__restrict state) ASMNAME("dbg_enter_lcpustate_c");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct lcpustate *FCALL dbg_enter_r(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct lcpustate *__restrict state) ASMNAME("dbg_enter_lcpustate_cr");
LOCAL ABNORMAL_RETURN ATTR_ARTIFICIAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg, struct lcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_lcpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct lcpustate *FCALL dbg_enter_r(void (KCALL *main)(void *arg), void *arg, struct lcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; return dbg_enter_lcpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ABNORMAL_RETURN ATTR_ARTIFICIAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void), struct lcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_lcpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct lcpustate *FCALL dbg_enter_r(void (KCALL *main)(void), struct lcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; return dbg_enter_lcpustate_r((struct dbg_entry_info *)&info, state); }
#endif /* !LCPUSTATE_ALIAS */

#ifndef KCPUSTATE_ALIAS
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct dbg_entry_info const *info, struct kcpustate *__restrict state) ASMNAME("dbg_enter_kcpustate");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct kcpustate *FCALL dbg_enter_r(struct dbg_entry_info const *info, struct kcpustate *__restrict state) ASMNAME("dbg_enter_kcpustate_r");
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct kcpustate *__restrict state) ASMNAME("dbg_enter_kcpustate_c");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct kcpustate *FCALL dbg_enter_r(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct kcpustate *__restrict state) ASMNAME("dbg_enter_kcpustate_cr");
LOCAL ABNORMAL_RETURN ATTR_ARTIFICIAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg, struct kcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_kcpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct kcpustate *FCALL dbg_enter_r(void (KCALL *main)(void *arg), void *arg, struct kcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; return dbg_enter_kcpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ABNORMAL_RETURN ATTR_ARTIFICIAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void), struct kcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_kcpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct kcpustate *FCALL dbg_enter_r(void (KCALL *main)(void), struct kcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; return dbg_enter_kcpustate_r((struct dbg_entry_info *)&info, state); }
#endif /* !KCPUSTATE_ALIAS */

#ifndef ICPUSTATE_ALIAS
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct dbg_entry_info const *info, struct icpustate *__restrict state) ASMNAME("dbg_enter_icpustate");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL dbg_enter_r(struct dbg_entry_info const *info, struct icpustate *__restrict state) ASMNAME("dbg_enter_icpustate_r");
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct icpustate *__restrict state) ASMNAME("dbg_enter_icpustate_c");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct icpustate *FCALL dbg_enter_r(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct icpustate *__restrict state) ASMNAME("dbg_enter_icpustate_cr");
LOCAL ABNORMAL_RETURN ATTR_ARTIFICIAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg, struct icpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_icpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL dbg_enter_r(void (KCALL *main)(void *arg), void *arg, struct icpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; return dbg_enter_icpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ABNORMAL_RETURN ATTR_ARTIFICIAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void), struct icpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_icpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL dbg_enter_r(void (KCALL *main)(void), struct icpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; return dbg_enter_icpustate_r((struct dbg_entry_info *)&info, state); }
#endif /* !ICPUSTATE_ALIAS */

#ifndef SCPUSTATE_ALIAS
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct dbg_entry_info const *info, struct scpustate *__restrict state) ASMNAME("dbg_enter_scpustate");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct scpustate *FCALL dbg_enter_r(struct dbg_entry_info const *info, struct scpustate *__restrict state) ASMNAME("dbg_enter_scpustate_r");
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct scpustate *__restrict state) ASMNAME("dbg_enter_scpustate_c");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct scpustate *FCALL dbg_enter_r(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct scpustate *__restrict state) ASMNAME("dbg_enter_scpustate_cr");
LOCAL ABNORMAL_RETURN ATTR_ARTIFICIAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg, struct scpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_scpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct scpustate *FCALL dbg_enter_r(void (KCALL *main)(void *arg), void *arg, struct scpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; return dbg_enter_scpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ABNORMAL_RETURN ATTR_ARTIFICIAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void), struct scpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_scpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct scpustate *FCALL dbg_enter_r(void (KCALL *main)(void), struct scpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; return dbg_enter_scpustate_r((struct dbg_entry_info *)&info, state); }
#endif /* !SCPUSTATE_ALIAS */

#ifndef FCPUSTATE_ALIAS
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct dbg_entry_info const *info, struct fcpustate *__restrict state) ASMNAME("dbg_enter_fcpustate");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct fcpustate *FCALL dbg_enter_r(struct dbg_entry_info const *info, struct fcpustate *__restrict state) ASMNAME("dbg_enter_fcpustate_r");
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2, 4)) void FCALL dbg_enter(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct fcpustate *__restrict state) ASMNAME("dbg_enter_fcpustate_c");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 4)) struct fcpustate *FCALL dbg_enter_r(dbg_entry_c_t entry, void const *data, size_t num_bytes, struct fcpustate *__restrict state) ASMNAME("dbg_enter_fcpustate_cr");
LOCAL ABNORMAL_RETURN ATTR_ARTIFICIAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg, struct fcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; dbg_enter_fcpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct fcpustate *FCALL dbg_enter_r(void (KCALL *main)(void *arg), void *arg, struct fcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO(1) info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 1; info.ei_argv[0] = arg; return dbg_enter_fcpustate_r((struct dbg_entry_info *)&info, state); }
LOCAL ABNORMAL_RETURN ATTR_ARTIFICIAL ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(void (KCALL *main)(void), struct fcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; dbg_enter_fcpustate((struct dbg_entry_info *)&info, state); }
LOCAL ATTR_ARTIFICIAL ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct fcpustate *FCALL dbg_enter_r(void (KCALL *main)(void), struct fcpustate *__restrict state) { STRUCT_DBG_ENTRY_INFO0 info; info.ei_entry = (void (KCALL *)())main; info.ei_argc = 0; return dbg_enter_fcpustate_r((struct dbg_entry_info *)&info, state); }
#endif /* !FCPUSTATE_ALIAS */

} /* extern "C++" */
#endif /* __cplusplus */
#endif /* __CC__ */


/* Extended set of conditions for which the kernel should switch to debugger-mode.
 * NOTE: Where these  overlap with  `KERNEL_DEBUGTRAP_ON_*', debug  traps
 *       will be triggered instead of the builtin debugger being entered.
 * e.g.: When  both   `KERNEL_DEBUGTRAP_ON_COREDUMP'  and   `KERNEL_DEBUG_ON_COREDUMP'
 *       are  enabled,  only a  debug  trap will  be  generated upon  a  coredump, but
 *       the builtin debugger will only be entered when `KERNEL_DEBUGTRAP_ON_COREDUMP'
 *       isn't set, or `kernel_debugtrap_enabled() == false'
 * Also note that certain conditions _always_ cause the builtin debugger to be  entered,
 * possibly even if  a debug  trap was generated  before then.  Such conditions  include
 * assertion checks/failures, stack segment faults, unhandled exceptions, and of course,
 * calls to `kernel_panic()' and `dbg()' or kernel-space instruction breakpoints  (int3) */
#define KERNEL_DEBUG_ON_COREDUMP          0x0008
#define KERNEL_DEBUG_ON_KERNEL_BREAKPOINT 0x0040
#define KERNEL_DEBUG_ON_USER_BREAKPOINT   0x0080
#define KERNEL_DEBUG_ON_DEFAULT          \
	(KERNEL_DEBUG_ON_COREDUMP |          \
	 KERNEL_DEBUG_ON_KERNEL_BREAKPOINT | \
	 KERNEL_DEBUG_ON_USER_BREAKPOINT)

#ifdef __CC__
/* Set of `KERNEL_DEBUGTRAP_ON_*', specifying events for which to trigger traps. */
DATDEF uintptr_t volatile kernel_debug_on;
#endif /* __CC__ */

DECL_END
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
#ifndef __dbg_active_defined
#define __dbg_active_defined
#define dbg_active 0
#endif /* !__dbg_active_defined */
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_ENTRY_H */
