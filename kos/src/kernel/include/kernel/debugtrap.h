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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_DEBUGTRAP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_DEBUGTRAP_H 1

#include <kernel/compiler.h>

#include <kos/debugtrap.h>
#include <kernel/types.h>
#include <stdbool.h>

DECL_BEGIN

#ifdef __CC__
struct icpustate;
struct scpustate;
struct ucpustate;
struct kcpustate;
struct lcpustate;
struct fcpustate;

struct kernel_debugtraps {
	/* NOTE: Either all callbacks from this structure are defined, or none of them are. */
	ATTR_RETNONNULL_T NONNULL_T((1, 2)) struct icpustate *(FCALL *dt_trap_icpustate)(struct icpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
	ATTR_RETNONNULL_T NONNULL_T((1, 2)) struct scpustate *(FCALL *dt_trap_scpustate)(struct scpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
	ATTR_RETNONNULL_T NONNULL_T((1, 2)) struct ucpustate *(FCALL *dt_trap_ucpustate)(struct ucpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
	ATTR_RETNONNULL_T NONNULL_T((1, 2)) struct kcpustate *(FCALL *dt_trap_kcpustate)(struct kcpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
	ATTR_RETNONNULL_T NONNULL_T((1, 2)) struct lcpustate *(FCALL *dt_trap_lcpustate)(struct lcpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
	ATTR_RETNONNULL_T NONNULL_T((1, 2)) struct fcpustate *(FCALL *dt_trap_fcpustate)(struct fcpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
};


#define KERNEL_DEBUGTRAP_ON_ILLEGAL_INSTRUCTION 0x0001 /* Trap on E_ILLEGAL_INSTRUCTION */
#define KERNEL_DEBUGTRAP_ON_SEGFAULT            0x0002 /* Trap on E_SEGFAULT */
#define KERNEL_DEBUGTRAP_ON_UNHANDLED_EXCEPT    0x0004 /* Trap on unhandled kernel exceptions */
#define KERNEL_DEBUGTRAP_ON_COREDUMP            0x0008 /* Trap on creation of coredumps */
#define KERNEL_DEBUGTRAP_ON_UNHANDLED_INTERRUPT 0x0010 /* Trap on unhandled interrupts */
#define KERNEL_DEBUGTRAP_ON_DRIVER_INIT_FAILURE 0x0020 /* Trap on driver initialization failure */
#define KERNEL_DEBUGTRAP_ON_KERNEL_BREAKPOINT   0x0040 /* Trap on hitting a breakpoint instruction (within the kernel) */
#define KERNEL_DEBUGTRAP_ON_USER_BREAKPOINT     0x0080 /* Trap on hitting a breakpoint instruction (within user-space) */
#define KERNEL_DEBUGTRAP_ON_DEFAULT            \
	(KERNEL_DEBUGTRAP_ON_UNHANDLED_EXCEPT |    \
	 KERNEL_DEBUGTRAP_ON_COREDUMP |            \
	 KERNEL_DEBUGTRAP_ON_UNHANDLED_INTERRUPT | \
	 KERNEL_DEBUGTRAP_ON_DRIVER_INIT_FAILURE | \
	 KERNEL_DEBUGTRAP_ON_KERNEL_BREAKPOINT |   \
	 KERNEL_DEBUGTRAP_ON_USER_BREAKPOINT)

/* Set of `KERNEL_DEBUGTRAP_ON_*', specifying events for which to trigger traps. */
DATDEF uintptr_t volatile kernel_debugtrap_on;


/* Install/uninstall the given set of trap handlers.
 * @return: true:  Successfully installed/uninstalled trap handlers
 * @return: false: Another set of handlers was already installed / a different set of handlers is installed. */
FUNDEF NONNULL((1)) bool FCALL
kernel_debugtraps_install(struct kernel_debugtraps const *__restrict handlers)
	THROWS(E_WOULDBLOCK);
FUNDEF NONNULL((1)) bool FCALL
kernel_debugtraps_uninstall(struct kernel_debugtraps const *__restrict handlers)
	THROWS(E_WOULDBLOCK);

/* Get the currently installed debug traps (or return `false' if none are installed) */
FUNDEF WUNUSED NONNULL((1)) bool FCALL
kernel_debugtraps_get(struct kernel_debugtraps *__restrict handlers)
	THROWS(E_WOULDBLOCK);

/* Check if debug traps are enabled. */
FUNDEF NOBLOCK WUNUSED bool NOTHROW(FCALL kernel_debugtrap_enabled)(void);

/* Check if the kernel should trep on `on' (one of `KERNEL_DEBUGTRAP_ON_*') */
#define kernel_debugtrap_shouldtrap(on) \
	(((kernel_debugtrap_on & (on)) != 0) && kernel_debugtrap_enabled())

/* Trigger a debug trap at the calling source location. */
FUNDEF void FCALL kernel_debugtrap(struct debugtrap_reason const *__restrict reason);

/* Debug trap invocation.
 * NOTE: `trap_regs' is written as `NAME:VALUE;NAME:VALUE;...'
 * @param: trapno: Signal number (One of `SIG*') */
FUNDEF ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap_icpustate(struct icpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
FUNDEF ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap_scpustate(struct scpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
FUNDEF ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap_ucpustate(struct ucpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
FUNDEF ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap_kcpustate(struct kcpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
FUNDEF ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap_lcpustate(struct lcpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
FUNDEF ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap_fcpustate(struct fcpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL kernel_debugtrap_r_icpustate(struct icpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct scpustate *FCALL kernel_debugtrap_r_scpustate(struct scpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct ucpustate *FCALL kernel_debugtrap_r_ucpustate(struct ucpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct kcpustate *FCALL kernel_debugtrap_r_kcpustate(struct kcpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct lcpustate *FCALL kernel_debugtrap_r_lcpustate(struct lcpustate *__restrict state, struct debugtrap_reason const *__restrict reason);
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct fcpustate *FCALL kernel_debugtrap_r_fcpustate(struct fcpustate *__restrict state, struct debugtrap_reason const *__restrict reason);

#ifdef __cplusplus
extern "C++" {
FUNDEF ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap(struct icpustate *__restrict state, struct debugtrap_reason const *__restrict reason) ASMNAME("kernel_debugtrap_icpustate");
FUNDEF ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap(struct scpustate *__restrict state, struct debugtrap_reason const *__restrict reason) ASMNAME("kernel_debugtrap_scpustate");
FUNDEF ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap(struct ucpustate *__restrict state, struct debugtrap_reason const *__restrict reason) ASMNAME("kernel_debugtrap_ucpustate");
FUNDEF ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap(struct kcpustate *__restrict state, struct debugtrap_reason const *__restrict reason) ASMNAME("kernel_debugtrap_kcpustate");
FUNDEF ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap(struct lcpustate *__restrict state, struct debugtrap_reason const *__restrict reason) ASMNAME("kernel_debugtrap_lcpustate");
FUNDEF ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap(struct fcpustate *__restrict state, struct debugtrap_reason const *__restrict reason) ASMNAME("kernel_debugtrap_fcpustate");
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL kernel_debugtrap_r(struct icpustate *__restrict state, struct debugtrap_reason const *__restrict reason) ASMNAME("kernel_debugtrap_r_icpustate");
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct scpustate *FCALL kernel_debugtrap_r(struct scpustate *__restrict state, struct debugtrap_reason const *__restrict reason) ASMNAME("kernel_debugtrap_r_scpustate");
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct ucpustate *FCALL kernel_debugtrap_r(struct ucpustate *__restrict state, struct debugtrap_reason const *__restrict reason) ASMNAME("kernel_debugtrap_r_ucpustate");
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct kcpustate *FCALL kernel_debugtrap_r(struct kcpustate *__restrict state, struct debugtrap_reason const *__restrict reason) ASMNAME("kernel_debugtrap_r_kcpustate");
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct lcpustate *FCALL kernel_debugtrap_r(struct lcpustate *__restrict state, struct debugtrap_reason const *__restrict reason) ASMNAME("kernel_debugtrap_r_lcpustate");
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct fcpustate *FCALL kernel_debugtrap_r(struct fcpustate *__restrict state, struct debugtrap_reason const *__restrict reason) ASMNAME("kernel_debugtrap_r_fcpustate");
LOCAL void FCALL kernel_debugtrap(syscall_ulong_t signo) { struct debugtrap_reason r; r.dtr_signo = signo; r.dtr_reason = DEBUGTRAP_REASON_NONE; kernel_debugtrap(&r); }
LOCAL ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap(struct icpustate *__restrict state, syscall_ulong_t signo) { struct debugtrap_reason r; r.dtr_signo = signo; r.dtr_reason = DEBUGTRAP_REASON_NONE; kernel_debugtrap(state, &r); }
LOCAL ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap(struct scpustate *__restrict state, syscall_ulong_t signo) { struct debugtrap_reason r; r.dtr_signo = signo; r.dtr_reason = DEBUGTRAP_REASON_NONE; kernel_debugtrap(state, &r); }
LOCAL ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap(struct ucpustate *__restrict state, syscall_ulong_t signo) { struct debugtrap_reason r; r.dtr_signo = signo; r.dtr_reason = DEBUGTRAP_REASON_NONE; kernel_debugtrap(state, &r); }
LOCAL ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap(struct kcpustate *__restrict state, syscall_ulong_t signo) { struct debugtrap_reason r; r.dtr_signo = signo; r.dtr_reason = DEBUGTRAP_REASON_NONE; kernel_debugtrap(state, &r); }
LOCAL ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap(struct lcpustate *__restrict state, syscall_ulong_t signo) { struct debugtrap_reason r; r.dtr_signo = signo; r.dtr_reason = DEBUGTRAP_REASON_NONE; kernel_debugtrap(state, &r); }
LOCAL ATTR_NORETURN NONNULL((1)) void FCALL kernel_debugtrap(struct fcpustate *__restrict state, syscall_ulong_t signo) { struct debugtrap_reason r; r.dtr_signo = signo; r.dtr_reason = DEBUGTRAP_REASON_NONE; kernel_debugtrap(state, &r); }
LOCAL ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL kernel_debugtrap_r(struct icpustate *__restrict state, syscall_ulong_t signo) { struct debugtrap_reason r; r.dtr_signo = signo; r.dtr_reason = DEBUGTRAP_REASON_NONE; return kernel_debugtrap_r(state, &r); }
LOCAL ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct scpustate *FCALL kernel_debugtrap_r(struct scpustate *__restrict state, syscall_ulong_t signo) { struct debugtrap_reason r; r.dtr_signo = signo; r.dtr_reason = DEBUGTRAP_REASON_NONE; return kernel_debugtrap_r(state, &r); }
LOCAL ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct ucpustate *FCALL kernel_debugtrap_r(struct ucpustate *__restrict state, syscall_ulong_t signo) { struct debugtrap_reason r; r.dtr_signo = signo; r.dtr_reason = DEBUGTRAP_REASON_NONE; return kernel_debugtrap_r(state, &r); }
LOCAL ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct kcpustate *FCALL kernel_debugtrap_r(struct kcpustate *__restrict state, syscall_ulong_t signo) { struct debugtrap_reason r; r.dtr_signo = signo; r.dtr_reason = DEBUGTRAP_REASON_NONE; return kernel_debugtrap_r(state, &r); }
LOCAL ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct lcpustate *FCALL kernel_debugtrap_r(struct lcpustate *__restrict state, syscall_ulong_t signo) { struct debugtrap_reason r; r.dtr_signo = signo; r.dtr_reason = DEBUGTRAP_REASON_NONE; return kernel_debugtrap_r(state, &r); }
LOCAL ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct fcpustate *FCALL kernel_debugtrap_r(struct fcpustate *__restrict state, syscall_ulong_t signo) { struct debugtrap_reason r; r.dtr_signo = signo; r.dtr_reason = DEBUGTRAP_REASON_NONE; return kernel_debugtrap_r(state, &r); }
}
#endif /* __cplusplus */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_DEBUGTRAP_H */
