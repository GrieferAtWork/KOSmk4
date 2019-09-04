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
#ifndef GUARD_MODGDB_GDB_H
#define GUARD_MODGDB_GDB_H 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/driver.h>
#include <kernel/interrupt.h>
#include <kernel/types.h>

#include <hybrid/typecore.h>

#include <kos/debugtrap.h>
#include <kos/kernel/gdb-cpu-state.h>

#include <format-printer.h>
#include <stdbool.h>

/* NOTES:
 *   - Multi-process support is implemented as:
 *     - The kernel is its own process
 *     - The kernel core and its drivers are implemented specially
 *       by emulating the behavior of being shared libraries automatically
 *       loaded into every new process immediately after that process has
 *       start execution.
 *     - This might be somewhat expensive, but it is the only way to properly
 *       support multi-process debugging.
 *     - Separately, the kernel core also appears as its own process
 *       - As leader of the kernel core, `_bootidle' is used
 *       - Any thread with the `TASK_FKERNTHREAD' flag set is considered
 *         to be apart of the kernel core.
 *     - With all of this, GDB is able to simply view kernel->user tracebacks
 *       as though they simply were library calls.
 */

#undef HAVE_GDB_DEBUG
#if 1
#include <kernel/printk.h>
#define HAVE_GDB_DEBUG 1
#define GDB_DEBUG(...) printk(KERN_DEBUG __VA_ARGS__)
#else
#define GDB_DEBUG(...) (void)0
#endif


DECL_BEGIN

typedef struct {
	uintptr_t        eti_state;  /* Enumeration state (internal) */
	REF struct task *eti_next;   /* [0..1] Enumeration task (internal) */
	uintptr_t        eti_state2; /* Enumeration state (internal) */
} GDBEnumThreadsIterator;

typedef struct {
	uintptr_t        epi_index; /* Enumeration state (internal) */
} GDBEnumProcessIterator;

/* Initialize a thread/process enumerator. */
INTDEF NONNULL((1)) void NOTHROW(FCALL GDBEnumThreads_Init)(GDBEnumThreadsIterator *__restrict self);
INTDEF NONNULL((1)) void NOTHROW(FCALL GDBEnumProcess_Init)(GDBEnumProcessIterator *__restrict self);
INTDEF NONNULL((1)) void NOTHROW(FCALL GDBEnumThreads_Fini)(GDBEnumThreadsIterator *__restrict self);
INTDEF NONNULL((1)) void NOTHROW(FCALL GDBEnumProcess_Fini)(GDBEnumProcessIterator *__restrict self);

/* Yield the next thread/process from a given thread/process enumerator.
 * NOTE: In the case of `GDBEnumProcess_Next()', only processes leaders are enumerated,
 *       when `&_bootidle' is returned as the placeholder for a leader for the kernel
 *       core process.
 * @return: NULL: All threads/processes have already been enumerated. */
INTDEF WUNUSED NONNULL((1)) REF struct task *NOTHROW(FCALL GDBEnumThreads_Next)(GDBEnumThreadsIterator *__restrict self);
INTDEF WUNUSED NONNULL((1)) REF struct task *NOTHROW(FCALL GDBEnumProcess_Next)(GDBEnumProcessIterator *__restrict self);

/* Get/Set the GDB thread that is currently being debugged.
 * Note that this is also used to control the enumeration of
 * threads apart of some given process.
 * @return: false: [GDB_SetCurrentThread] The specified thread could not be suspended,
 *                                        because it has already terminated. */
INTDEF WUNUSED ATTR_RETNONNULL struct task *NOTHROW(FCALL GDB_GetCurrentThread)(void);
INTDEF NONNULL((1)) bool NOTHROW(FCALL GDB_SetCurrentThread)(struct task *__restrict thread);

/* Initialize/Finalize the current-thread sub-system */
INTDEF void NOTHROW(FCALL GDB_InitializeCurrentThread)(void);
INTDEF void NOTHROW(FCALL GDB_FinalizeCurrentThread)(void);

/* Return the current process leader.
 * if the currently thread is a kernel-thread, `&_bootidle' is returned. */
INTDEF WUNUSED ATTR_RETNONNULL struct task *NOTHROW(FCALL GDB_GetCurrentProcess)(void);

/* Get/Set a register for the current thread.
 * @param: regno: One of `GDB_REGISTER_<ARCH>_*'
 * @return: * : The required buffer size.
 *              NOTE: In the case of `GDB_SetRegister()', `bufsize' has to match
 *                    this value exactly (it's not allowed to be larger), else the
 *                    set operation will not have written the register value.
 * @return: 0 : Invalid `regno'. */
INTDEF NONNULL((2)) size_t NOTHROW(FCALL GDB_GetRegister)(uintptr_t regno, void *buf, size_t bufsize);
INTDEF NONNULL((2)) size_t NOTHROW(FCALL GDB_SetRegister)(uintptr_t regno, void const *buf, size_t bufsize);

/* Get/Set the full GDB cpustate. */
INTDEF NONNULL((1)) void NOTHROW(FCALL GDB_GetRegisters)(struct gdb_cpustate *buf);
INTDEF NONNULL((1)) void NOTHROW(FCALL GDB_SetRegisters)(struct gdb_cpustate const *buf);

/* Get/Set the single-step mode that is active when execution of the current thread resumes. */
INTDEF WUNUSED bool NOTHROW(FCALL GDB_GetSingleStep)(void);
INTDEF void NOTHROW(FCALL GDB_SetSingleStep)(bool enabled);

/* Set/clear a special address range and/or thread (when `thread' is NULL, apply to any thread)
 * inside of which single-step breakpoints should not cause a debugger trap, but simply continue
 * stepping. */
INTDEF void NOTHROW(FCALL GDB_SetSingleStepIgnoredRange)(struct task *thread, void *start_pc, void *end_pc);
INTDEF void NOTHROW(FCALL GDB_ClearSingleStepIgnoredRange)(void);

/* Get/Set a register of the cpu state with which GDB was entered. (aka.
 * the `state' argument passed to the original `GDB_Trap*CpuState()' function) */
INTDEF NONNULL((2, 4)) size_t NOTHROW(FCALL GDB_GetTrapRegister)(uintptr_t regno, void *buf, size_t bufsize, struct task *__restrict thread);
INTDEF NONNULL((2, 4)) size_t NOTHROW(FCALL GDB_SetTrapRegister)(uintptr_t regno, void const *buf, size_t bufsize, struct task *__restrict thread);

/* Kill the kernel. (== shutdown()) */
INTDEF ATTR_NORETURN void NOTHROW(FCALL GDB_KillKernel)(void);

/* Read/Write virtual memory in the context of the current thread.
 * Note that these functions are able to by-pass the usual access restrictions
 * imposed on memory, allowing writes to read-only memory and the like.
 * @param: allow_faults: When true, memory may be faulted in order to emulate the access.
 *                       This includes copy-on-write and load-on-access, as well as VIO
 *                       memory access.
 * @return: * : The number of bytes that could not be copied due to being faulty.
 *              Even when `allow_faults' is `true', this may be non-zero when the
 *              given `addr' isn't mapped, or accessing it causes some other kind
 *              of error. */
INTDEF NONNULL((2)) size_t NOTHROW(FCALL GDB_ReadMemory)(vm_virt_t addr, void *buf, size_t bufsize, bool allow_faults);
INTDEF NONNULL((2)) size_t NOTHROW(FCALL GDB_WriteMemory)(vm_virt_t addr, void const *buf, size_t bufsize, bool allow_faults);
INTDEF NONNULL((2)) size_t NOTHROW(FCALL GDB_ReadMemoryWithoutSwBreak)(vm_virt_t addr, void *buf, size_t bufsize, bool allow_faults);
INTDEF NONNULL((2)) size_t NOTHROW(FCALL GDB_WriteMemoryWithoutSwBreak)(vm_virt_t addr, void *buf, size_t bufsize, bool allow_faults);

/* Include (insert) or exclude (remove) SwBreak instruction overrides
 * defined within the range `addr...+=bufsize' with the given `buf'
 * This is used to hide/expose software breakpoint bytes from GDB, since
 * I have seen cases where GDB will first set a breakpoint, then read the
 * memory location, reading back `0xcc', then remove the breakpoint, and
 * finally trick itself into thinking that the target memory location was
 * actually an 0xcc byte all along (causing it to adjust PC=ADDR+1 when
 * resuming from the memory location, thus breaking execution by placing
 * the instruction pointer in the middle of the actual instruction)
 * NOTE: When calling `GDB_IncludeSwBreak()', saved restore memory for
 *       software breakpoints is overwritten with memory taken from `buf',
 *       meaning that when using these functions along side read/write,
 *       writing overtop of a software breakpoint will actually write into
 *       the restore buffer and only into main memory once the breakpoint
 *       is removed. */
INTDEF NONNULL((2)) void NOTHROW(FCALL GDB_IncludeSwBreak)(vm_virt_t addr, void *buf, size_t bufsize);
INTDEF NONNULL((2)) void NOTHROW(FCALL GDB_ExcludeSwBreak)(vm_virt_t addr, void *buf, size_t bufsize);

#undef GDB_HAVE_READMEMORY_MEMMEM
//#define GDB_HAVE_READMEMORY_MEMMEM 1

#ifdef GDB_HAVE_READMEMORY_MEMMEM
/* Perform a memory search for `pattern...+=pattern_length' within the given address range.
 * @return: * :            The base address where a matching pattern was found.
 * @return: (vm_virt_t)-1: The pattern could not be located.
 * @return: (vm_virt_t)-2: A faulty memory location was encountered. */
INTDEF vm_virt_t
NOTHROW(FCALL GDB_ReadMemory_memmem)(vm_virt_t addr, size_t length,
                                     void const *pattern, size_t pattern_length,
                                     bool allow_faults);
#endif /* GDB_HAVE_READMEMORY_MEMMEM */

/* Trigger GDB from the calling thread with the given register state.
 * GDB may update the given register state before returning its updated form to the caller. */
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *NOTHROW(FCALL GDB_TrapICpuState)(struct icpustate *__restrict state, syscall_ulong_t trapNo, char const *trapRegs);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) struct scpustate *NOTHROW(FCALL GDB_TrapSCpuState)(struct scpustate *__restrict state, syscall_ulong_t trapNo, char const *trapRegs);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) struct ucpustate *NOTHROW(FCALL GDB_TrapUCpuState)(struct ucpustate *__restrict state, syscall_ulong_t trapNo, char const *trapRegs);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) struct kcpustate *NOTHROW(FCALL GDB_TrapKCpuState)(struct kcpustate *__restrict state, syscall_ulong_t trapNo, char const *trapRegs);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) struct lcpustate *NOTHROW(FCALL GDB_TrapLCpuState)(struct lcpustate *__restrict state, syscall_ulong_t trapNo, char const *trapRegs);
INTDEF NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) struct fcpustate *NOTHROW(FCALL GDB_TrapFCpuState)(struct fcpustate *__restrict state, syscall_ulong_t trapNo, char const *trapRegs);
/* Try to trap into GDB, but return `NULL' if GDB is already active. */
INTDEF NOBLOCK WUNUSED NONNULL((1)) struct icpustate *NOTHROW(FCALL GDB_TryTrapICpuState)(struct icpustate *__restrict state, syscall_ulong_t trapNo, char const *trapRegs);

/* Arch-specific: Get/Set the value of a given register `regno'
 * @return: 0 : Invalid `regno'. */
INTDEF NONNULL((2, 4, 5)) size_t NOTHROW(FCALL GDB_GetICpuStateRegister)(uintptr_t regno, void *buf, size_t bufsize, struct task *__restrict thread, struct icpustate const *__restrict state);
INTDEF NONNULL((2, 4, 5)) size_t NOTHROW(FCALL GDB_GetSCpuStateRegister)(uintptr_t regno, void *buf, size_t bufsize, struct task *__restrict thread, struct scpustate const *__restrict state);
INTDEF NONNULL((2, 4, 5)) size_t NOTHROW(FCALL GDB_GetUCpuStateRegister)(uintptr_t regno, void *buf, size_t bufsize, struct task *__restrict thread, struct ucpustate const *__restrict state);
INTDEF NONNULL((2, 4, 5)) size_t NOTHROW(FCALL GDB_GetKCpuStateRegister)(uintptr_t regno, void *buf, size_t bufsize, struct task *__restrict thread, struct kcpustate const *__restrict state);
INTDEF NONNULL((2, 4, 5)) size_t NOTHROW(FCALL GDB_GetLCpuStateRegister)(uintptr_t regno, void *buf, size_t bufsize, struct task *__restrict thread, struct lcpustate const *__restrict state);
INTDEF NONNULL((2, 4, 5)) size_t NOTHROW(FCALL GDB_GetFCpuStateRegister)(uintptr_t regno, void *buf, size_t bufsize, struct task *__restrict thread, struct fcpustate const *__restrict state);
INTDEF NONNULL((2, 4, 5)) size_t NOTHROW(FCALL GDB_SetICpuStateRegister)(uintptr_t regno, void const *buf, size_t bufsize, struct task *__restrict thread, struct icpustate **__restrict pstate);
INTDEF NONNULL((2, 4, 5)) size_t NOTHROW(FCALL GDB_SetSCpuStateRegister)(uintptr_t regno, void const *buf, size_t bufsize, struct task *__restrict thread, struct scpustate **__restrict pstate);
INTDEF NONNULL((2, 4, 5)) size_t NOTHROW(FCALL GDB_SetUCpuStateRegister)(uintptr_t regno, void const *buf, size_t bufsize, struct task *__restrict thread, struct ucpustate **__restrict pstate);
INTDEF NONNULL((2, 4, 5)) size_t NOTHROW(FCALL GDB_SetKCpuStateRegister)(uintptr_t regno, void const *buf, size_t bufsize, struct task *__restrict thread, struct kcpustate **__restrict pstate);
INTDEF NONNULL((2, 4, 5)) size_t NOTHROW(FCALL GDB_SetLCpuStateRegister)(uintptr_t regno, void const *buf, size_t bufsize, struct task *__restrict thread, struct lcpustate **__restrict pstate);
INTDEF NONNULL((2, 4, 5)) size_t NOTHROW(FCALL GDB_SetFCpuStateRegister)(uintptr_t regno, void const *buf, size_t bufsize, struct task *__restrict thread, struct fcpustate **__restrict pstate);

/* Suspend all other CPUs now in order to enter full-stop mode.
 * No-Op if `GDB_DidSuspendOtherCPUs' was already set to `true' */
INTDEF void NOTHROW(FCALL GDB_SuspendAllOtherCPUsNow)(void);

/* Main function called to transmit the trap reason,
 * before entering the GDB interpreter loop.
 * The interpreter loop itself is executed  */
INTDEF void NOTHROW(FCALL GDB_Main)(void);

/* The trap number (SIG*) and additional registers ([0..1])
 * that describe the reason as to why GDB was entered. */
INTDEF syscall_ulong_t GDBReason_TrapNo;
INTDEF char const     *GDBReason_Registers;

INTDEF u32 GDB_Features; /* Set of `GDB_FEATURE_*' */
#define GDB_FEATURE_NONSTOP_MODE 0x0001 /* Enable non-stop mode. */
#define GDB_FEATURE_NOACK_MODE   0x0002 /* Disable sending/processing of ACK/NACK indicators. */

INTDEF u32 GDB_RemoteFeatures; /* Set of `GDB_REMOTEFEATURE_*' */
#define GDB_REMOTEFEATURE_ATTACHED     0x0001 /* GDB remote has been attached */
#define GDB_REMOTEFEATURE_MULTIPROCESS 0x0002 /* `multiprocess+' */
#define GDB_REMOTEFEATURE_SWBREAK      0x0004 /* `swbreak+' */
#define GDB_REMOTEFEATURE_HWBREAK      0x0008 /* `hwbreak+' */
#define GDB_REMOTEFEATURE_FORK_EVENTS  0x0010 /* `fork-events+' */
#define GDB_REMOTEFEATURE_VFORK_EVENTS 0x0020 /* `vfork-events+' */
#define GDB_REMOTEFEATURE_EXEC_EVENTS  0x0040 /* `exec-events+' */

/* Set to true if all other CPUs were suspended, and preemptive
 * interrupts were disabled alongside preemption on the hosting
 * CPU, before `GDB_Main()' was called.
 * This is the case when `GDB_FEATURE_NONSTOP_MODE' was disabled
 * at the time when a GDB trap was triggered */
INTDEF bool GDB_DidSuspendOtherCPUs;

/* Check if the GDB sub-system is active.
 * This, alongside the `GDB_Trap*CpuState' are the only functions
 * which may be called from a context other than the active GDB thread.
 * The main purpose of this function is for the communications driver
 * to check if GDB is already running, and generate an explicit trap
 * if it isn't. */
INTDEF WUNUSED bool FCALL GDB_IsActive(void);

/* GDB remote communications API */
typedef struct {
	NONNULL((1)) void (FCALL *gr_putdata)(void const *buf, size_t bufsize);
} GDBRemoteAPI;

INTDEF GDBRemoteAPI GDBRemote_API;


/* Receive (and wait for) a byte from the GDB remote. */
INTDEF byte_t NOTHROW(FCALL GDBRemote_GetByte)(void);

/* Same as `GDBRemote_GetByte()', but fail after a configurable timeout by returning `-1' */
INTDEF int NOTHROW(FCALL GDBRemote_TimedGetByte)(void);

/* Try to receive a byte from the GDB remote (returns `-1' if nothing was available) */
INTDEF int NOTHROW(FCALL GDBRemote_TryGetByte)(void);

/* Clear the buffer of pending bytes (called before
 * preemption is enabled when a GDB trap is triggered) */
INTDEF void NOTHROW(FCALL GDBRemote_ClearBuffer)(void);

/* Send data to the GDB remote. */
FORCELOCAL NONNULL((1)) void NOTHROW(FCALL GDBRemote_PutData)(void const *buf, size_t bufsize) {
	(*GDBRemote_API.gr_putdata)(buf, bufsize);
}


/* Place a given `byte' within the GDB input buffer queue.
 * If the byte is `0x03' and GDB isn't already running, a
 * GDB interrupt is triggered in order to respond to said
 * byte using the given `state', in which case the function
 * will only return once execution should be resumed.
 * Note that in the later case, 
 * This function should  */
INTDEF NONNULL((1)) struct icpustate *
NOTHROW(FCALL GDBRemote_PutByte)(struct icpustate *__restrict state, byte_t byte);

/* Same as `GDBRemote_PutByte()', but using the current CPU state.
 * This function is mainly intended for use by communications initializers,
 * where it can happen that an already pending byte must be handled without
 * the help of an interrupt. */
INTDEF void NOTHROW(FCALL GDBRemote_PutByteFromHere)(byte_t byte);


/* GDB packet API */
#define GDB_PACKET_MAXLEN (1 << 14) /* Max length of packet data (number of writable bytes returned by `GDBPacket_Start()') */
/* Start a new packet and return a pointer to the base of the packet buffer. */
INTDEF WUNUSED ATTR_RETNONNULL char *NOTHROW(FCALL GDBPacket_Start)(void);
/* Calculate and return the checksum for the given memory block. */
INTDEF WUNUSED NONNULL((1)) byte_t NOTHROW(KCALL GDBPacket_GetCheckSum)(void const *__restrict buf, size_t buflen);
/* Transmit a packet ending at `endptr'
 * @return: true:  Packet successfully transmitted.
 * @return: false: Transmit failed (timeout, or `GDBPacket_RetryTransmitLimit' was exceeded) */
INTDEF WUNUSED NONNULL((1)) bool NOTHROW(FCALL GDBPacket_Transmit)(char *endptr);
/* Transmit a notification packet (same as `GDBPacket_Transmit()', but the first byte is `%' instead of `$') */
INTDEF NONNULL((1)) void NOTHROW(FCALL GDBPacket_TransmitNotification)(char *endptr);
/* Same as `GDBPacket_Transmit()', but escape special characters in the response string.
 * This is used to implement the transmission of raw binary data. */
INTDEF WUNUSED NONNULL((1)) bool NOTHROW(FCALL GDBPacket_TransmitEscape)(char *endptr);
/* Max # of times to attempt to transmit a packet before giving up. */
INTDEF unsigned int GDBPacket_RetryTransmitLimit;
/* Convenience wrappers for sending packets. */
INTDEF WUNUSED bool NOTHROW(FCALL GDBPacket_SendEmpty)(void);
INTDEF WUNUSED NONNULL((1)) bool NOTHROW(FCALL GDBPacket_Send)(char const *__restrict text);
INTDEF WUNUSED NONNULL((1)) bool NOTHROW(VCALL GDBPacket_Sendf)(char const *__restrict format, ...);
INTDEF WUNUSED NONNULL((1)) bool NOTHROW(FCALL GDBPacket_VSendf)(char const *__restrict format, __builtin_va_list args);
INTDEF WUNUSED bool NOTHROW(FCALL GDBPacket_SendError)(u8 error_code);


#undef fromhex
#undef tohex
INTDEF char const GDB_HexChars[16];
INTDEF u8 const GDB_HexValues[256];
#define fromhex(ch) GDB_HexValues[(u8)(ch)]
#define tohex(ord)  GDB_HexChars[(u8)(ord)]



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
INTDEF WUNUSED errno_t NOTHROW(FCALL GDB_AddBreak)(unsigned int type, void *addr, unsigned int kind);
INTDEF WUNUSED errno_t NOTHROW(FCALL GDB_DelBreak)(unsigned int type, void *addr, unsigned int kind);
INTDEF void NOTHROW(FCALL GDB_RemoveAllBreakpoints)(void);

/* Remove all saved user-space breakpoints from the given VM.
 * However, don't actually modify memory (since this function
 * is only called during exec()) */
INTDEF void NOTHROW(FCALL GDB_ClearAllKernelAndUserBreakpointsFromVM)(struct vm *__restrict effective_vm);

/* Prototype for the GDB remote interrupt handler.
 * @return: NULL: Unhandled interrupt (call original handler)
 * @return: * :   The CPU state that should be restored. */
typedef WUNUSED NONNULL((1)) struct icpustate *(FCALL *PGDBREMOTE_INTERRUPT_HANDLER)(struct icpustate *__restrict state);

/* Register/Unregister the interrupt handler used by the communications driver.
 * Note that only a single handler can ever be registered! */
INTDEF NONNULL((2)) void FCALL GDBRemote_RegisterInterruptHandler(isr_vector_t vector, PGDBREMOTE_INTERRUPT_HANDLER func);
INTDEF void FCALL GDBRemote_UnregisterInterruptHandler(isr_vector_t vector);

/* Initialize/Finalize GDB remote communication. */
INTDEF void FCALL GDBRemote_Initialize(void);
INTDEF void FCALL GDBRemote_Finalize(void);

/* Initialize/Finalize GDB interrupt handling. */
INTDEF void FCALL GDBInterrupt_Initialize(void);
INTDEF void FCALL GDBInterrupt_Finalize(void);

/* Initialize/Finalize the GDB driver. */
INTDEF void KCALL GDB_Initialize(void);
INTDEF void KCALL GDB_Finalize(void);


/* GDB Info sub-system */

/* Special PID value used to identify the kernel core in multi-process mode. */
#define GDB_MULTIPROCESS_KERNEL_PID 0x7c000000

/* Make sure that `thread' is a valid thread. If it isn't, return NULL. */
INTDEF WUNUSED REF struct task *NOTHROW(FCALL GDB_VerifyThreadAndIncref)(struct task *thread);
INTDEF WUNUSED REF struct task *NOTHROW(FCALL GDB_GetProcessByPID)(upid_t pid);
#define GDB_ENCODETHREADID_MAXCHARS 18 /* p12345678.12345678 */
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW(FCALL GDB_EncodeThreadID)(char *ptr, struct task *__restrict thread, bool need_p_prefix DFL(true));
INTDEF WUNUSED NONNULL((1)) REF struct task *NOTHROW(FCALL GDB_DecodeThreadID)(char **__restrict pptr, bool need_p_prefix DFL(true));

/* NOTE: All of the following functions return negative ERRNO values on failure. */
/* Print a human-readable name for `thread' */
INTDEF NONNULL((1, 3)) ssize_t NOTHROW(FCALL GDBInfo_PrintThreadName)(pformatprinter printer, void *arg, struct task *__restrict thread);
/* `qXfer:exec-file:read': Print the absolute filename for the original binary passed to exec() when the process of `thread' was started. (`/proc/${PID_OF(thread)}/exe') */
INTDEF NONNULL((1, 3)) ssize_t NOTHROW(FCALL GDBInfo_PrintThreadExecFile)(pformatprinter printer, void *arg, struct task *__restrict thread);
INTDEF NONNULL((1, 3)) ssize_t NOTHROW(FCALL GDBInfo_PrintVMExecFile)(pformatprinter printer, void *arg, struct vm *__restrict effective_vm);
/* `qXfer:features:read': Print the named features file `filename' */
INTDEF NONNULL((1, 3)) ssize_t NOTHROW(FCALL GDBInfo_PrintFeaturesFile)(pformatprinter printer, void *arg, char const *__restrict filename);
/* `qXfer:libraries:read': Print the list of library loaded into the current process. */
INTDEF NONNULL((1)) ssize_t NOTHROW(FCALL GDBInfo_PrintLibraryList)(pformatprinter printer, void *arg);
/* `qXfer:threads:read': Print the list of threads apart of the current process. */
INTDEF NONNULL((1)) ssize_t NOTHROW(FCALL GDBInfo_PrintThreadList)(pformatprinter printer, void *arg);
/* `qXfer:osdata:read:processes': Print the list of processes running on the system. */
INTDEF NONNULL((1)) ssize_t NOTHROW(FCALL GDBInfo_PrintProcessList)(pformatprinter printer, void *arg);




#if __SIZEOF_POINTER__ == __SIZEOF_LONG__
#define STRTOADDR(str, endp, radix)  ((void *)(uintptr_t)strtoul(str, endp, radix))
#define STRTOSIZE(str, endp, radix)  ((size_t)strtoul(str, endp, radix))
#define STRTOSSIZE(str, endp, radix) ((ssize_t)strtol(str, endp, radix))
#elif __SIZEOF_POINTER__ == __SIZEOF_LONG_LONG__
#define STRTOADDR(str, endp, radix)  ((void *)(uintptr_t)strtoull(str, endp, radix))
#define STRTOSIZE(str, endp, radix)  ((size_t)strtoull(str, endp, radix))
#define STRTOSSIZE(str, endp, radix) ((ssize_t)strtoll(str, endp, radix))
#elif __SIZEOF_POINTER__ == 4
#define STRTOADDR(str, endp, radix)  ((void *)(uintptr_t)strtou32(str, endp, radix))
#define STRTOSIZE(str, endp, radix)  ((size_t)strtou32(str, endp, radix))
#define STRTOSSIZE(str, endp, radix) ((ssize_t)strto32(str, endp, radix))
#elif __SIZEOF_POINTER__ == 8
#define STRTOADDR(str, endp, radix)  ((void *)(uintptr_t)strtou64(str, endp, radix))
#define STRTOSIZE(str, endp, radix)  ((size_t)strtou64(str, endp, radix))
#define STRTOSSIZE(str, endp, radix) ((ssize_t)strto64(str, endp, radix))
#elif __SIZEOF_POINTER__ <= 4
#define STRTOADDR(str, endp, radix)  ((void *)(uintptr_t)strtou32(str, endp, radix))
#define STRTOSIZE(str, endp, radix)  ((size_t)strtou32(str, endp, radix))
#define STRTOSSIZE(str, endp, radix) ((ssize_t)strto32(str, endp, radix))
#else
#define STRTOADDR(str, endp, radix)  ((void *)(uintptr_t)strtou64(str, endp, radix))
#define STRTOSIZE(str, endp, radix)  ((size_t)strtou64(str, endp, radix))
#define STRTOSSIZE(str, endp, radix) ((ssize_t)strto64(str, endp, radix))
#endif


DECL_END

#endif /* !GUARD_MODGDB_GDB_H */
