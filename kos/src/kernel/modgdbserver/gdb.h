/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODGDBSERVER_GDB_H
#define GUARD_MODGDBSERVER_GDB_H 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/types.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <bits/crt/format-printer.h>
#include <kos/kernel/gdb-cpu-state.h>

DECL_BEGIN

struct mman;
struct gdb_cpustate;

typedef struct gdb_thread_stop_event GDBThreadStopEvent;

/* Cpu state kind codes */
#define CPUSTATE_KIND_ICPUSTATE 0
#define CPUSTATE_KIND_SCPUSTATE 1
#define CPUSTATE_KIND_UCPUSTATE 2
#define CPUSTATE_KIND_KCPUSTATE 3
#define CPUSTATE_KIND_LCPUSTATE 4
#define CPUSTATE_KIND_FCPUSTATE 5

struct gdb_thread_stop_event {
	/* Descriptor for async thread stop events / Chain of currently stopped threads. */
	GDBThreadStopEvent      *tse_next;      /* [0..1] Next stopped thread. */
	struct debugtrap_reason *tse_reason;    /* [0..1] Stop reason (or NULL if the thread was suspended with `GDBThread_Stop()') */
	struct task             *tse_thread;    /* [1..1] The thread that was stopped */
	void                    *tse_state;     /* [1..1] Resume cpu state. */
	uintptr_half_t           tse_statekind; /* The kind of resume cpu state (one of `CPUSTATE_KIND_?CPUSTATE') */
#define GDB_THREAD_MAYRESUME_STOP   0       /* The thread must remain stopped */
#define GDB_THREAD_MAYRESUME_NASYNC 1       /* The thread must remain stopped, but GDB was informed of it having stopped
	                                         * This state is only set in non-stop mode in order to inform the thread
	                                         * that it should no longer attempt to become the GDB host thread, but rather
	                                         * just wait until `GDB_THREAD_MAYRESUME_RESUME' and resume execution.
	                                         * This is also the resume-state for threads stopped by `GDBThread_Stop()' */
#define GDB_THREAD_MAYRESUME_RESUME 2       /* The thread may resume execution. */
	uintptr_quarter_t        tse_mayresume; /* Set to non-zero if this thread's stop notification was delivered. */
	uintptr_quarter_t        tse_isacpu;    /* non-zero if this stop event describes an entire CPU. */
	struct sig               tse_sigresume; /* Signal broadcast when this thread should be resumed (aka. `GDB_THREAD_MAYRESUME_RESUME' is set). */
	struct task_connections  tse_oldcon;    /* Saved task connections. */
};

/* [0..1][lock(PRIVATE(<GDB_HOST_THREAD>))]
 * Chain of stopped threads (always includes the GDB host thread)
 * May be `NULL' if called from the GDB fallback host thread,  in
 * response to the GDB remote sending a command.
 * All threads in this chain are `GDB_THREAD_MAYRESUME_NASYNC' */
INTDEF GDBThreadStopEvent *GDBThread_Stopped;

/* [0..1][lock(append(ATOMIC), remove(<GDB_HOST_THREAD>))]
 * Chain of pending async stop notifications
 * All threads in this chain are `GDB_THREAD_MAYRESUME_STOP' */
INTDEF GDBThreadStopEvent *GDBThread_AsyncNotifStopEvents;

/* Signal broadcast when `GDBThread_AsyncNotifStopEvents' becomes non-empty. */
INTDEF struct sig GDBThread_AsyncNotifStopEventsAdded;

/* [1..1][lock(PRIVATE(<GDB_HOST_THREAD>))]
 * The thread that is hosting the GDB server (== THIS_TASK). */
INTDEF struct task *GDBServer_Host;

/* Signal broadcast when `GDBServer_Host' becomes  unlocked
 * (aka. `NULL') as  the result  of `GDB_Main()'  returning
 * Used  by `GDBServer_FallbackHost' to wait for the active
 * host  to go away in order to not constantly be connected
 * to `GDBServer_FallbackHostOnByte', which would slow down
 * remote data processing when each byte would re-awake the
 * fallback host thread. */
INTDEF struct sig GDBServer_HostUnlocked;

/* [1..1][const]
 * The fallback host thread used to drive the GDB server in the event
 * of the GDB remote being the one to instigate an exchange (such  as
 * sending a \3-byte to stop system-wide execution) */
INTDEF REF struct task *GDBServer_FallbackHost;

/* Main function for the GDB fallback host thread */
INTDEF void NOTHROW(KCALL GDBFallbackHost_Main)(void);

/* `true'   if  `GDB_Main()'   was  called   in  non-stop   mode  (`false'  otherwise)
 * When  in non-stop mode, `GDBThread_IsStopped()' only returned true for threads that
 * have previously been suspended, and `GDBThread_Stop()' and `GDBThread_Resume()' are
 * no longer no-ops.
 * You may call `GDBThread_StopAllCpus()' to set `GDBThread_IsNonStopModeActive = false'
 * and  continue  in  all-stop  mode  until  the  next  vCont-  (or  similar)   command. */
INTDEF bool GDBThread_IsNonStopModeActive;
#define GDBThread_IsAllStopModeActive   (!GDBThread_IsNonStopModeActive)



/* Check if the given `thread' has been stopped by the GDB server */
INTDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL GDBThread_IsStopped)(struct task const *__restrict thread);

/* Same as `GDBThread_IsStopped()', but the thread doesn't count as truly
 * stopped, unless it was stopped explicitly (rather than implicitly,  as
 * would be the case when `GDBThread_IsAllStopModeActive == true') */
INTDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL GDBThread_IsStoppedExplicitly)(struct task const *__restrict thread);

/* Check if the given `thread' has terminated */
INTDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL GDBThread_HasTerminated)(struct task const *__restrict thread);

/* Check if the given `thread' is considered to be a kernel thread */
INTDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL GDBThread_IsKernelThread)(struct task const *__restrict thread);

/* Stop/Resume execution of the given thread
 * Note that when `GDBThread_IsNonStopModeActive' is false, `GDBThread_Resume()' becomes
 * a no-op, and  the thread  will not  be resumed until  the current  GDB session  ends.
 * @param: generateAsyncStopEvents: When true, the thread is stopped with an async notification of SIG=0
 * @return: true:  Successfully stopped the given thread, or the given thread was already stopped.
 * @return: false: The given thread has already terminated and can no longer be stopped. */
INTDEF NONNULL((1)) bool NOTHROW(FCALL GDBThread_Stop)(struct task *__restrict thread, bool generateAsyncStopEvents DFL(false));
INTDEF NONNULL((1)) void NOTHROW(FCALL GDBThread_Resume)(struct task *__restrict thread);

/* Same as above, but stop/resume every thread apart of the process that `thread' is apart of. */
INTDEF NONNULL((1)) void NOTHROW(FCALL GDBThread_StopProcess)(struct task *__restrict thread, bool generateAsyncStopEvents DFL(false));
INTDEF NONNULL((1)) void NOTHROW(FCALL GDBThread_ResumeProcess)(struct task *__restrict thread);

/* When already  in all-stop  mode (after  `GDBThread_StopAllCpus()' was  called),
 * create  a missing async  stop notification for  `thread', meaning that `thread'
 * will continue to remain suspended, even after `GDBThread_ResumeEverything()' is
 * called. */
INTDEF NONNULL((1)) bool
NOTHROW(FCALL GDBThread_CreateMissingAsyncStopNotification)(struct task *__restrict thread);


/* Find   and  return  the  stop  event  for  `thread'
 * If the thread hasn't been stopped, or has a pending
 * async  stop  notification,  return  NULL   instead. */
INTDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) GDBThreadStopEvent *
NOTHROW(FCALL GDBThread_FindStopEvent)(struct task const *__restrict thread);

/* Same  as  `GDBThread_FindStopEvent()', but  unlink  the event
 * from the chain of stopped threads. (The caller is responsible
 * for re-adding the thread back to said chain at a later  point
 * in time)
 * This can be used to exclude specific threads from calls to
 * `GDBThread_ResumeEverything()', which is something that is
 * required for implementing full `vCont' support. */
INTDEF WUNUSED NONNULL((1)) GDBThreadStopEvent *
NOTHROW(FCALL GDBThread_PopStopEvent)(struct task *__restrict thread);

/* Same   as  `GDBThread_PopStopEvent()',  but   return  a  chain  of
 * stop  events (with the last one being stored in `*plastevent') for
 * all stopped threads that are apart of the same process as `thread' */
INTDEF WUNUSED NONNULL((1, 2)) GDBThreadStopEvent *
NOTHROW(FCALL GDBThread_PopStopEventProcess)(struct task *__restrict thread,
                                             GDBThreadStopEvent **__restrict plastevent);

/* Enter all-stop mode (no-op if already in all-stop mode) */
INTDEF void NOTHROW(FCALL GDBThread_StopAllCpus)(void);

/* Enter  non-stop  mode  (no-op  if  already  in  non-stop  mode)
 * This is done by resuming all stop events with `tse_isacpu != 0' */
INTDEF void NOTHROW(FCALL GDBThread_ResumeAllCpus)(void);

/* Stop  execution in all threads by sending async RPCs to every
 * running thread on the system, and having them report back via
 * the `GDBThread_AsyncNotifStopEvents' chain.
 * Essentially, this function does:
 * >> GDBThread_StopAllCpus();
 * >> FOREACH(thread IN System.AllThreads) {
 * >>     GDBThread_CreateMissingAsyncStopNotification(thread);
 * >> }
 * @return: * : The total number of newly created async thread events. */
INTDEF size_t NOTHROW(FCALL GDBThread_StopAllAndGenerateAsyncStopEvents)(void);

/* Resume all threads for which no pending async notifications exist.
 * Also: Resume execution on all suspended CPUs. */
INTDEF void NOTHROW(FCALL GDBThread_ResumeEverything)(void);

/* Discard all pending async notification events. */
INTDEF void NOTHROW(FCALL GDBThread_DiscardAllAsyncNotifEvents)(void);

/* Restore async stop events for all currently stopped threads. */
INTDEF void NOTHROW(FCALL GDBThread_RestoreAllAsyncNotifEvents)(void);

/* Consume a pending async notification event, or return NULL if none are pending. */
INTDEF WUNUSED GDBThreadStopEvent *
NOTHROW(FCALL GDBThread_ConsumeAsyncNotifEvent)(void);

/* Kill the kernel. (== shutdown()) */
INTDEF ATTR_NORETURN void NOTHROW(FCALL GDBThread_KillKernel)(void);

/* Set a hint to the GDB backend to ignore single-step events
 * for   instruction   pointers    `>= start_pc && < end_pc'.
 * Only  a single such  hint can exist at  any point in time. */
INTDEF void
NOTHROW(FCALL GDB_SetSingleStepIgnoredRange)(struct task const *thread,
                                             VIRT void const *start_pc,
                                             VIRT void const *end_pc);
INTDEF void NOTHROW(FCALL GDB_DelSingleStepIgnoredRange)(void);


INTERN FREE void FCALL GDBInterrupt_Init(void);
INTERN void FCALL GDBInterrupt_Fini(void);


/* Get/Set a register for the current thread.
 * @param: regno: One of `GDB_REGISTER_<ARCH>_*'
 * @return: * : The required buffer size.
 *              NOTE: In the case of  `GDB_SetRegister()', `bufsize' has to  match
 *                    this value exactly (it's not allowed to be larger), else the
 *                    set operation will not have written the register value.
 * @return: 0 : Invalid `regno', or `thread' has terminated. */
INTDEF NONNULL((1, 3)) size_t NOTHROW(FCALL GDB_GetRegister)(struct task *__restrict thread, uintptr_t regno, void *buf, size_t bufsize);
INTDEF NONNULL((1, 3)) size_t NOTHROW(FCALL GDB_SetRegister)(struct task *__restrict thread, uintptr_t regno, void const *buf, size_t bufsize);
INTDEF NONNULL((2)) ssize_t NOTHROW(FCALL GDB_PrintRegisterName)(uintptr_t regno, __pformatprinter printer, void *arg);

/* Enumerate/print special OS registers. */
INTDEF NONNULL((1)) bool NOTHROW(FCALL GDB_HasOsRegister)(struct task *__restrict thread, uintptr_t os_regno);
INTDEF NONNULL((1, 3)) ssize_t NOTHROW(FCALL GDB_PrintOsRegisterName)(struct task *__restrict thread, uintptr_t os_regno, __pformatprinter printer, void *arg);
INTDEF NONNULL((1, 3)) ssize_t NOTHROW(FCALL GDB_PrintOsRegisterValue)(struct task *__restrict thread, uintptr_t os_regno, __pformatprinter printer, void *arg);

/* Enumerate/print special Arch registers. */
INTDEF NONNULL((1)) bool NOTHROW(FCALL GDB_HasArchRegister)(struct task *__restrict thread, uintptr_t arch_regno);
INTDEF NONNULL((1, 3)) ssize_t NOTHROW(FCALL GDB_PrintArchRegisterName)(struct task *__restrict thread, uintptr_t arch_regno, __pformatprinter printer, void *arg);
INTDEF NONNULL((1, 3)) ssize_t NOTHROW(FCALL GDB_PrintArchRegisterValue)(struct task *__restrict thread, uintptr_t arch_regno, __pformatprinter printer, void *arg);

#ifdef __INTELLISENSE__
/* Get/Set the program counter register.
 * @return: true:  Successfully read/wrote the register file.
 * @return: false: The given `thread' has already terminated. */
INTDEF NONNULL((1, 2)) bool NOTHROW(FCALL GDB_GetPC)(struct task *__restrict thread, void **__restrict ppc);
INTDEF NONNULL((1)) bool NOTHROW(FCALL GDB_SetPC)(struct task *__restrict thread, void *pc);
#else /* __INTELLISENSE__ */
#define GDB_GetPC(thread, ppc) (GDB_GetRegister(thread, GDB_REGISTER_PC, ppc, sizeof(void *)) != 0)
FORCELOCAL ATTR_ARTIFICIAL NONNULL((1)) bool
NOTHROW(FCALL GDB_SetPC)(struct task *__restrict thread, void *pc) {
	return GDB_SetRegister(thread, GDB_REGISTER_PC, &pc, sizeof(void *)) != 0;
}
#endif /* !__INTELLISENSE__ */

/* Get/Set the full GDB cpustate.
 * @return: true:  Successfully read/wrote the register file.
 * @return: false: The given `thread' has already terminated. */
INTDEF NONNULL((1, 2)) bool NOTHROW(FCALL GDB_GetRegisters)(struct task *__restrict thread, struct gdb_cpustate *buf);
INTDEF NONNULL((1, 2)) bool NOTHROW(FCALL GDB_SetRegisters)(struct task *__restrict thread, struct gdb_cpustate const *buf);

/* Get/Set the single-step mode for `thread'.
 * @return: true:  Successfully read/wrote the register file.
 * @return: false: The given `thread' has already terminated. */
INTDEF bool NOTHROW(FCALL GDB_GetSingleStep)(struct task *__restrict thread, bool *__restrict penabled);
INTDEF bool NOTHROW(FCALL GDB_SetSingleStep)(struct task *__restrict thread, bool enabled);

/* Breakpoint types. */
#define GDB_BREAKPOINT_TYPE_SWBREAK   0 /* int3 */
#define GDB_BREAKPOINT_TYPE_HWBREAK   1 /* DRn-breakpoint */
#define GDB_BREAKPOINT_TYPE_WRITE     2 /* Break on write to `addr' */
#define GDB_BREAKPOINT_TYPE_READ      3 /* Break on read from `addr' */
#define GDB_BREAKPOINT_TYPE_READWRITE 4 /* Break on read or write to/from `addr' */

/* GDB breakpoint API
 * @param: kind: arch-specific
 * @return: EOK:      Success
 * @return: ENOSYS:   The specified breakpoint type isn't supported, or breakpoints aren't supported in general
 * @return: EALREADY: [GDB_AddBreak] A breakpoint already exists for the specified location.
 * @return: ENOMEM:   [GDB_AddBreak] Failed to add the breakpoint (too many breakpoints already defined)
 * @return: EFAULT:   [GDB_AddBreak] Attempted to define a software-breakpoint at a faulty memory location.
 * @return: ENOENT:   [GDB_DelBreak] The specified breakpoint doesn't exist. */
INTDEF WUNUSED errno_t NOTHROW(FCALL GDB_AddBreak)(struct task *__restrict thread, unsigned int type, VIRT void *addr, unsigned int kind);
INTDEF WUNUSED errno_t NOTHROW(FCALL GDB_DelBreak)(struct task *__restrict thread, unsigned int type, VIRT void *addr, unsigned int kind);
INTDEF WUNUSED errno_t NOTHROW(FCALL GDB_MMan_AddBreak)(struct mman *__restrict effective_mm, unsigned int type, VIRT void *addr, unsigned int kind);
INTDEF WUNUSED errno_t NOTHROW(FCALL GDB_MMan_DelBreak)(struct mman *__restrict effective_mm, unsigned int type, VIRT void *addr, unsigned int kind);

/* Remove all breakpoints from any sort of MMan */
INTDEF void NOTHROW(FCALL GDB_RemoveAllBreakpoints)(void);

/* Delete all internal knowledge of breakpoints concerning `effective_mm'.
 * Note  that this function may be called  from threads other than the GDB
 * host thread, as it is invoked as part of `mman_onfini_callbacks()'! */
INTDEF void NOTHROW(FCALL GDB_ClearAllBreakpointsOfMMan)(struct mman *__restrict effective_mm);

/* Copy all breakpoint definitions of `oldmm' to also exist in `newmm' (called during `mman_fork()') */
INTDEF void NOTHROW(FCALL GDB_CloneAllBreakpointsFromMMan)(struct mman *__restrict newmm, struct mman *__restrict oldmm);

/* Read/Write memory
 * WARNING: `GDB_WriteMemory()' and `GDB_MMan_WriteMemory()' may modify the contents of the given `buf'!
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transferred.
 *              The affected memory ranges are:
 *               - `addr + num_bytes - return ... addr + num_bytes - 1'
 *               - `buf + num_bytes - return ... buf + num_bytes - 1' */
INTDEF NONNULL((1, 3)) size_t NOTHROW(FCALL GDB_ReadMemory)(struct task *__restrict thread, VIRT void const *addr, void *buf, size_t num_bytes);
INTDEF NONNULL((1, 3)) size_t NOTHROW(FCALL GDB_WriteMemory)(struct task *__restrict thread, VIRT void *addr, void *buf, size_t num_bytes);
INTDEF NONNULL((1, 3)) size_t NOTHROW(FCALL GDB_ReadMemoryWithoutSwBreak)(struct task *__restrict thread, VIRT void const *addr, void *buf, size_t num_bytes);
INTDEF NONNULL((1, 3)) size_t NOTHROW(FCALL GDB_WriteMemoryWithoutSwBreak)(struct task *__restrict thread, VIRT void *addr, void const *buf, size_t num_bytes);
INTDEF NONNULL((1, 3)) size_t NOTHROW(FCALL GDB_MMan_ReadMemory)(struct mman *__restrict effective_mm, VIRT void const *addr, void *buf, size_t num_bytes);
INTDEF NONNULL((1, 3)) size_t NOTHROW(FCALL GDB_MMan_WriteMemory)(struct mman *__restrict effective_mm, VIRT void *addr, void *buf, size_t num_bytes);
INTDEF NONNULL((1, 3)) size_t NOTHROW(FCALL GDB_MMan_ReadMemoryWithoutSwBreak)(struct mman *__restrict effective_mm, VIRT void const *addr, void *buf, size_t num_bytes);
INTDEF NONNULL((1, 3)) size_t NOTHROW(FCALL GDB_MMan_WriteMemoryWithoutSwBreak)(struct mman *__restrict effective_mm, VIRT void *addr, void const *buf, size_t num_bytes);

/* Search memory for a specific need
 * This function behaves identical to `memmem()'
 * @return: true:  Found the needle at `*presult'
 * @return: false: The needle wasn't found. */
INTDEF NONNULL((1, 4)) bool
NOTHROW(FCALL GDB_FindMemory)(struct task *__restrict thread,
                              VIRT void const *haystack, size_t haystack_length,
                              void const *needle, size_t needle_length,
                              VIRT void const **__restrict presult);

/* Calculate  the CRC32  checksum for  the given  region of memory.
 * If access to anything with the given range fail, return `false'.
 * Otherwise, return `true' and store  the CRC value in  `*presult' */
INTDEF NONNULL((1, 4)) bool
NOTHROW(FCALL GDB_CalculateCRC32)(struct task *__restrict thread,
                                  VIRT void const *addr, size_t length,
                                  u32 *__restrict presult);

/* Include  (insert)  or exclude  (remove) SwBreak  instruction overrides
 * defined within  the  range  `addr...+=bufsize' with  the  given  `buf'
 * This  is used to hide/expose software breakpoint bytes from GDB, since
 * I have seen cases where GDB will first set a breakpoint, then read the
 * memory location, reading back `0xcc', then remove the breakpoint,  and
 * finally trick itself into thinking that the target memory location was
 * actually an 0xcc byte all along  (causing it to adjust PC=ADDR+1  when
 * resuming from the memory location, thus breaking execution by  placing
 * the instruction pointer in the middle of the overwritten  instruction)
 * NOTE: When  calling  `GDB_IncludeSwBreak()', saved  restore  memory for
 *       software breakpoints is overwritten with memory taken from `buf',
 *       meaning that when  using these functions  along side  read/write,
 *       writing overtop of a software breakpoint will actually write into
 *       the  restore buffer and only into main memory once the breakpoint
 *       is removed. */
INTDEF NONNULL((1, 3)) void
NOTHROW(FCALL GDB_IncludeSwBreak)(struct mman *__restrict effective_mm,
                                  VIRT void const *addr, void *buf, size_t bufsize);
INTDEF NONNULL((1, 3)) void
NOTHROW(FCALL GDB_ExcludeSwBreak)(struct mman *__restrict effective_mm,
                                  VIRT void const *addr, void *buf, size_t bufsize);


/* Arch-specific: Get/Set the value of a given register `regno'
 * NOTE: These functions are allowed to assume that `GDBThread_IsStopped(thread)'
 * @param: kind: One of `CPUSTATE_KIND_?CPUSTATE'
 * @return: 0 : Invalid `regno'. */
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_GetCpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void *buf, size_t bufsize, void const *__restrict state, unsigned int state_kind);
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_SetCpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void const *buf, size_t bufsize, void **__restrict pstate, unsigned int state_kind);
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_GetICpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void *buf, size_t bufsize, struct icpustate const *__restrict state);
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_GetSCpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void *buf, size_t bufsize, struct scpustate const *__restrict state);
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_GetUCpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void *buf, size_t bufsize, struct ucpustate const *__restrict state);
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_GetKCpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void *buf, size_t bufsize, struct kcpustate const *__restrict state);
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_GetLCpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void *buf, size_t bufsize, struct lcpustate const *__restrict state);
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_GetFCpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void *buf, size_t bufsize, struct fcpustate const *__restrict state);
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_SetICpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void const *buf, size_t bufsize, struct icpustate **__restrict pstate);
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_SetSCpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void const *buf, size_t bufsize, struct scpustate **__restrict pstate);
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_SetUCpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void const *buf, size_t bufsize, struct ucpustate **__restrict pstate);
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_SetKCpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void const *buf, size_t bufsize, struct kcpustate **__restrict pstate);
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_SetLCpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void const *buf, size_t bufsize, struct lcpustate **__restrict pstate);
INTDEF NONNULL((1, 3, 5)) size_t NOTHROW(FCALL GDB_SetFCpuStateRegister)(struct task *__restrict thread, uintptr_t regno, void const *buf, size_t bufsize, struct fcpustate **__restrict pstate);


/* Debug trap entry points. */
INTDEF struct kernel_debugtraps const GDBServer_DebugTraps;
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) void *FCALL
GDBServer_TrapCpuState(void *__restrict state,
                       struct debugtrap_reason const *__restrict reason,
                       unsigned int state_kind);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
GDBServer_TrapICpuState(struct icpustate *__restrict state,
                        struct debugtrap_reason const *__restrict reason);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct scpustate *FCALL
GDBServer_TrapSCpuState(struct scpustate *__restrict state,
                        struct debugtrap_reason const *__restrict reason);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct ucpustate *FCALL
GDBServer_TrapUCpuState(struct ucpustate *__restrict state,
                        struct debugtrap_reason const *__restrict reason);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct kcpustate *FCALL
GDBServer_TrapKCpuState(struct kcpustate *__restrict state,
                        struct debugtrap_reason const *__restrict reason);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct lcpustate *FCALL
GDBServer_TrapLCpuState(struct lcpustate *__restrict state,
                        struct debugtrap_reason const *__restrict reason);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct fcpustate *FCALL
GDBServer_TrapFCpuState(struct fcpustate *__restrict state,
                        struct debugtrap_reason const *__restrict reason);



/* Remote communications back-end API */

/* Signal  that  gets  broadcast  with  whenever  the
 * connection back-end data buffer becomes non-empty. */
INTDEF struct sig GDBServer_RemoteDataAvailable;

/* Check if there are any pending bytes in the remote communications pipe. */
INTDEF NOBLOCK WUNUSED bool NOTHROW(FCALL GDBRemote_HasPendingBytes)(void);

/* Post a given byte `b' to the remote data input queue.
 * NOTE: May only be called  while preemption is disabled,  and
 *       only from the designated CPU for interrupts concerning
 *       incoming remote data! */
INTDEF NOBLOCK NOPREEMPT void
NOTHROW(FCALL GDBRemote_PostByte)(byte_t b);

/* Read a byte from the remote data input queue.
 * NOTE: These functions may only be called by the GDB host thread!
 * @return: -1: No data available / timed out. */
INTDEF byte_t NOTHROW(FCALL GDBRemote_GetByte)(void);
INTDEF int NOTHROW(FCALL GDBRemote_TimedGetByte)(void);
INTDEF NOBLOCK int NOTHROW(FCALL GDBRemote_TryGetByte)(void);

/* Initialize/finalize the GDB remote API */
INTDEF FREE void FCALL GDBRemote_Init(void);
INTDEF void FCALL GDBRemote_Fini(void);
INTDEF void (FCALL *PGDBRemote_Fini)(void);

/* Send data to the GDB remote. */
INTDEF NONNULL_T((1)) void (FCALL *PGDBRemote_PutData)(void const *buf, size_t bufsize);
#define GDBRemote_PutData(buf, bufsize) (*PGDBRemote_PutData)(buf, bufsize)


/* Remote backend API: SERIAL */
INTDEF NONNULL((1)) void NOTHROW(FCALL GDBSerial_PutData)(void const *buf, size_t bufsize);
INTDEF void FCALL GDBSerial_Init(char *args);
INTDEF void FCALL GDBSerial_Fini(void);



DECL_END

#endif /* !GUARD_MODGDBSERVER_GDB_H */
