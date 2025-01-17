/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODGDBSERVER_ARCH_I386_REGISTER_C
#define GUARD_MODGDBSERVER_ARCH_I386_REGISTER_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fpu.h>
#include <sched/group.h>
#include <sched/task.h>

#include <hybrid/unaligned.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/fpu-state.h>
#include <kos/kernel/gdb-cpu-state.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <string.h>

#include "../../gdb.h"
#include "../../server.h"

DECL_BEGIN

#ifdef __x86_64__
#define FLAGS_REGNO GDB_REGISTER_X86_64_RFLAGS
#else /* __x86_64__ */
#define FLAGS_REGNO GDB_REGISTER_I386_EFLAGS
#endif /* !__x86_64__ */

/* Get/Set the single-step mode that is active when execution of the current thread resumes. */
INTERN bool
NOTHROW(FCALL GDB_GetSingleStep)(struct task *__restrict thread,
                                 bool *__restrict penabled) {
	uintptr_t flags;
	if (!GDB_GetRegister(thread, FLAGS_REGNO, &flags, sizeof(flags)))
		return false;
	*penabled = flags & EFLAGS_TF;
	return true;
}

INTERN bool
NOTHROW(FCALL GDB_SetSingleStep)(struct task *__restrict thread,
                                 bool enabled) {
	u32 flags, new_flags;
	if (!GDB_GetRegister(thread, FLAGS_REGNO,
	                     &flags, sizeof(flags)))
		return false;
	new_flags = flags & ~EFLAGS_TF;
	if (enabled)
		new_flags |= EFLAGS_TF;
	GDB_DEBUG("[gdb] GDB_SetSingleStep(%p("
	          "%" PRIuN(__SIZEOF_PID_T__) "."
	          "%" PRIuN(__SIZEOF_PID_T__) "), "
	          "%s) (was: %s)\n",
	          thread,
	          task_getrootpid_of(thread),
	          task_getroottid_of(thread),
	          (new_flags & EFLAGS_TF) ? "true" : "false",
	          (flags & EFLAGS_TF) ? "true" : "false");
	if (new_flags != flags) {
		if (GDB_SetRegister(thread, FLAGS_REGNO,
		                    &new_flags, sizeof(new_flags)) != sizeof(new_flags))
			return false;
#ifndef NDEBUG
		assert(GDB_GetRegister(thread, FLAGS_REGNO, &flags, sizeof(flags)));
		assertf((flags & EFLAGS_TF) == (new_flags & EFLAGS_TF),
		        "EFLAGS.TF was not applied properly:\n"
		        "flags     = %#" PRIx32 "\n"
		        "new_flags = %#" PRIx32 "\n",
		        flags, new_flags);
#endif /* !NDEBUG */
	}
	return true;
}

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(FCALL GDB_GetRegisterName)(uintptr_t regno) {
	char const *result;
	switch (regno) {

#define CASE(id, name) case id: result = name; break
#ifdef __x86_64__
	CASE(GDB_REGISTER_X86_64_RAX,    "rax");
	CASE(GDB_REGISTER_X86_64_RBX,    "rbx");
	CASE(GDB_REGISTER_X86_64_RCX,    "rcx");
	CASE(GDB_REGISTER_X86_64_RDX,    "rdx");
	CASE(GDB_REGISTER_X86_64_RSI,    "rsi");
	CASE(GDB_REGISTER_X86_64_RDI,    "rdi");
	CASE(GDB_REGISTER_X86_64_RBP,    "rbp");
	CASE(GDB_REGISTER_X86_64_RSP,    "rsp");
	CASE(GDB_REGISTER_X86_64_R8,     "r8");
	CASE(GDB_REGISTER_X86_64_R9,     "r9");
	CASE(GDB_REGISTER_X86_64_R10,    "r10");
	CASE(GDB_REGISTER_X86_64_R11,    "r11");
	CASE(GDB_REGISTER_X86_64_R12,    "r12");
	CASE(GDB_REGISTER_X86_64_R13,    "r13");
	CASE(GDB_REGISTER_X86_64_R14,    "r14");
	CASE(GDB_REGISTER_X86_64_R15,    "r15");
	CASE(GDB_REGISTER_X86_64_RIP,    "rip");
	CASE(GDB_REGISTER_X86_64_RFLAGS, "rflags");
	CASE(GDB_REGISTER_X86_64_CS,     "cs");
	CASE(GDB_REGISTER_X86_64_SS,     "ss");
	CASE(GDB_REGISTER_X86_64_DS,     "ds");
	CASE(GDB_REGISTER_X86_64_ES,     "es");
	CASE(GDB_REGISTER_X86_64_FS,     "fs");
	CASE(GDB_REGISTER_X86_64_GS,     "gs");
	CASE(GDB_REGISTER_X86_64_ST0,    "st(0)");
	CASE(GDB_REGISTER_X86_64_ST1,    "st(1)");
	CASE(GDB_REGISTER_X86_64_ST2,    "st(2)");
	CASE(GDB_REGISTER_X86_64_ST3,    "st(3)");
	CASE(GDB_REGISTER_X86_64_ST4,    "st(4)");
	CASE(GDB_REGISTER_X86_64_ST5,    "st(5)");
	CASE(GDB_REGISTER_X86_64_ST6,    "st(6)");
	CASE(GDB_REGISTER_X86_64_ST7,    "st(7)");
	CASE(GDB_REGISTER_X86_64_FCW,    "fcw");
	CASE(GDB_REGISTER_X86_64_FSW,    "fsw");
	CASE(GDB_REGISTER_X86_64_FTW,    "ftw");
	CASE(GDB_REGISTER_X86_64_FCS,    "fcs");
	CASE(GDB_REGISTER_X86_64_FIP,    "fip");
	CASE(GDB_REGISTER_X86_64_FDS,    "fds");
	CASE(GDB_REGISTER_X86_64_FDP,    "fdp");
	CASE(GDB_REGISTER_X86_64_FOP,    "fop");
	CASE(GDB_REGISTER_X86_64_XMM0,   "xmm0");
	CASE(GDB_REGISTER_X86_64_XMM1,   "xmm1");
	CASE(GDB_REGISTER_X86_64_XMM2,   "xmm2");
	CASE(GDB_REGISTER_X86_64_XMM3,   "xmm3");
	CASE(GDB_REGISTER_X86_64_XMM4,   "xmm4");
	CASE(GDB_REGISTER_X86_64_XMM5,   "xmm5");
	CASE(GDB_REGISTER_X86_64_XMM6,   "xmm6");
	CASE(GDB_REGISTER_X86_64_XMM7,   "xmm7");
	CASE(GDB_REGISTER_X86_64_XMM8,   "xmm8");
	CASE(GDB_REGISTER_X86_64_XMM9,   "xmm9");
	CASE(GDB_REGISTER_X86_64_XMM10,  "xmm10");
	CASE(GDB_REGISTER_X86_64_XMM11,  "xmm11");
	CASE(GDB_REGISTER_X86_64_XMM12,  "xmm12");
	CASE(GDB_REGISTER_X86_64_XMM13,  "xmm13");
	CASE(GDB_REGISTER_X86_64_XMM14,  "xmm14");
	CASE(GDB_REGISTER_X86_64_XMM15,  "xmm15");
	CASE(GDB_REGISTER_X86_64_MXCSR,  "mxcsr");
	CASE(GDB_REGISTER_X86_64_FSBASE, "fs.base");
	CASE(GDB_REGISTER_X86_64_GSBASE, "gs.base");
#else /* __x86_64__ */
	CASE(GDB_REGISTER_I386_EAX,    "eax");
	CASE(GDB_REGISTER_I386_ECX,    "ecx");
	CASE(GDB_REGISTER_I386_EDX,    "edx");
	CASE(GDB_REGISTER_I386_EBX,    "ebx");
	CASE(GDB_REGISTER_I386_ESP,    "esp");
	CASE(GDB_REGISTER_I386_EBP,    "ebp");
	CASE(GDB_REGISTER_I386_ESI,    "esi");
	CASE(GDB_REGISTER_I386_EDI,    "edi");
	CASE(GDB_REGISTER_I386_EIP,    "eip");
	CASE(GDB_REGISTER_I386_EFLAGS, "eflags");
	CASE(GDB_REGISTER_I386_CS,     "cs");
	CASE(GDB_REGISTER_I386_SS,     "ss");
	CASE(GDB_REGISTER_I386_DS,     "ds");
	CASE(GDB_REGISTER_I386_ES,     "es");
	CASE(GDB_REGISTER_I386_FS,     "fs");
	CASE(GDB_REGISTER_I386_GS,     "gs");
	CASE(GDB_REGISTER_I386_ST0,    "st(0)");
	CASE(GDB_REGISTER_I386_ST1,    "st(1)");
	CASE(GDB_REGISTER_I386_ST2,    "st(2)");
	CASE(GDB_REGISTER_I386_ST3,    "st(3)");
	CASE(GDB_REGISTER_I386_ST4,    "st(4)");
	CASE(GDB_REGISTER_I386_ST5,    "st(5)");
	CASE(GDB_REGISTER_I386_ST6,    "st(6)");
	CASE(GDB_REGISTER_I386_ST7,    "st(7)");
	CASE(GDB_REGISTER_I386_FCW,    "fcw");
	CASE(GDB_REGISTER_I386_FSW,    "fsw");
	CASE(GDB_REGISTER_I386_FTW,    "ftw");
	CASE(GDB_REGISTER_I386_FCS,    "fcs");
	CASE(GDB_REGISTER_I386_FIP,    "fip");
	CASE(GDB_REGISTER_I386_FDS,    "fds");
	CASE(GDB_REGISTER_I386_FDP,    "fdp");
	CASE(GDB_REGISTER_I386_FOP,    "fop");
	CASE(GDB_REGISTER_I386_XMM0,   "xmm0");
	CASE(GDB_REGISTER_I386_XMM1,   "xmm1");
	CASE(GDB_REGISTER_I386_XMM2,   "xmm2");
	CASE(GDB_REGISTER_I386_XMM3,   "xmm3");
	CASE(GDB_REGISTER_I386_XMM4,   "xmm4");
	CASE(GDB_REGISTER_I386_XMM5,   "xmm5");
	CASE(GDB_REGISTER_I386_XMM6,   "xmm6");
	CASE(GDB_REGISTER_I386_XMM7,   "xmm7");
	CASE(GDB_REGISTER_I386_MXCSR,  "mxcsr");
	CASE(GDB_REGISTER_I386_FSBASE, "fs.base");
	CASE(GDB_REGISTER_I386_GSBASE, "gs.base");
#endif /* !__x86_64__ */
#undef CASE

	default:
		result = NULL;
		break;
	}
	return result;
}

INTERN NONNULL((2)) ssize_t
NOTHROW(FCALL GDB_PrintRegisterName)(uintptr_t regno,
                                     pformatprinter printer,
                                     void *arg) {
	ssize_t result;
	char const *name;
	name = GDB_GetRegisterName(regno);
	if (!name)
		return 0;
	result = (*printer)(arg, "%", 1);
	if (result >= 0) {
		ssize_t temp;
		temp = (*printer)(arg, name, strlen(name));
		if (temp < 0) {
			result = temp;
		} else {
			result += temp;
		}
	}
	return result;
}

#ifdef __x86_64__
#define ARCH_REGISTER_KERNEL_GS_BASE 0
#else /* __x86_64__ */
#define ARCH_REGISTER_KERNEL_FS_BASE 0
#endif /* !__x86_64__ */
#define ARCH_REGISTER_COUNT 1


PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(FCALL GDB_GetArchRegisterName)(uintptr_t arch_regno) {
	char const *result;
	switch (arch_regno) {

#ifdef ARCH_REGISTER_KERNEL_GS_BASE
	case ARCH_REGISTER_KERNEL_GS_BASE:
		result = "kernel_gs_base";
		break;
#endif /* ARCH_REGISTER_KERNEL_GS_BASE */

#ifdef ARCH_REGISTER_KERNEL_FS_BASE
	case ARCH_REGISTER_KERNEL_FS_BASE:
		result = "kernel_fs_base";
		break;
#endif /* ARCH_REGISTER_KERNEL_FS_BASE */

	default:
		result = NULL;
		break;
	}
	return result;
}

/* Enumerate/print special ARCH registers. */
INTERN ATTR_CONST NONNULL((1)) bool
NOTHROW(FCALL GDB_HasArchRegister)(struct task *__restrict thread, uintptr_t arch_regno) {
	(void)thread;
	return arch_regno < ARCH_REGISTER_COUNT;
}

INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDB_PrintArchRegisterName)(struct task *__restrict thread, uintptr_t arch_regno,
                                         pformatprinter printer, void *arg) {
	ssize_t result = 0;
	char const *name;
	(void)thread;
	name = GDB_GetArchRegisterName(arch_regno);
	if (name)
		result = (*printer)(arg, name, strlen(name));
	return result;
}

INTERN NONNULL((1, 3)) ssize_t
NOTHROW(FCALL GDB_PrintArchRegisterValue)(struct task *__restrict thread, uintptr_t arch_regno,
                                          pformatprinter printer, void *arg) {
	ssize_t result;
	switch (arch_regno) {

#ifdef ARCH_REGISTER_KERNEL_GS_BASE
	case ARCH_REGISTER_KERNEL_GS_BASE:
#endif /* ARCH_REGISTER_KERNEL_GS_BASE */
#ifdef ARCH_REGISTER_KERNEL_FS_BASE
	case ARCH_REGISTER_KERNEL_FS_BASE:
#endif /* ARCH_REGISTER_KERNEL_FS_BASE */
		result = format_printf(printer, arg, "%p", thread);
		break;

	default:
		result = 0;
		break;
	}
	return result;
}

DECL_END

#ifndef __INTELLISENSE__
#define GET_REGISTER 1
#include "register-impl.c.inl"
#define SET_REGISTER 1
#include "register-impl.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_MODGDBSERVER_ARCH_I386_REGISTER_C */
