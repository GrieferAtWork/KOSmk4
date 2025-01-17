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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_ARCH_PRCTL_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_ARCH_PRCTL_C 1

#include <kernel/compiler.h>

#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/x86/gdt.h>
#include <sched/task.h>

#include <asm/cpu-msr.h>
#include <asm/intrin.h>
#include <asm/prctl.h>
#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <errno.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/types.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

#ifdef __x86_64__
/* NOTE: When the access originates from user-space, we must write to `IA32_KERNEL_GS_BASE',
 *       since  the kernel has  executed `swapgs' upon exiting  user-space. Because of this,
 *       the current  %gs.base  is  `THIS_TASK', while  `IA32_KERNEL_GS_BASE'  contains  the
 *       saved user-space %gs.base! */
#define GET_USER_FSBASE()  __rdmsr(IA32_FS_BASE)
#define GET_USER_GSBASE()  __rdmsr(IA32_KERNEL_GS_BASE)
#define SET_USER_FSBASE(v) __wrmsr(IA32_FS_BASE, (uintptr_t)(v))
#define SET_USER_GSBASE(v) __wrmsr(IA32_KERNEL_GS_BASE, (uintptr_t)(v))
#else /* __x86_64__ */
#define GET_USER_FSBASE()  PERTASK_GET(this_x86_user_fsbase)
#define GET_USER_GSBASE()  PERTASK_GET(this_x86_user_gsbase)
#define SET_USER_FSBASE(v) x86_set_user_fsbase((uintptr_t)(v))
#define SET_USER_GSBASE(v) x86_set_user_gsbase((uintptr_t)(v))
#endif /* !__x86_64__ */


#if (defined(__ARCH_WANT_SYSCALL_ARCH_PRCTL) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_ARCH_PRCTL))
PRIVATE bool KCALL arch_get_cpuid(void) {
	/* TODO: Actually implemented if supported by hardware */
	COMPILER_IMPURE();
	return true;
}

PRIVATE void KCALL arch_set_cpuid(bool enabled) {
	/* TODO: Actually implemented if supported by hardware */
	COMPILER_IMPURE();
	if (!enabled)
		THROW(E_UNSUPPORTED_DEVICE);
}
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_ARCH_PRCTL
DEFINE_SYSCALL2(syscall_slong_t, arch_prctl,
                unsigned int, command,
                NCX UNCHECKED uintptr_t *, addr) {
	/* Predict (and optimize for) the use by libdl, which uses
	 * this system call to assign  the address of the  initial
	 * TLS segment.
	 * s.a. <kos/bits/thread.h>: `__x86_fast_wr(fs|gs)base()' */
#ifdef __x86_64__
	switch (__builtin_expect(command, ARCH_SET_FS))
#else /* __x86_64__ */
	switch (__builtin_expect(command, ARCH_SET_GS))
#endif /* !__x86_64__ */
	{

	case ARCH_SET_GS:
		SET_USER_GSBASE(addr);
		break;

	case ARCH_SET_FS:
		SET_USER_FSBASE(addr);
		break;

	case ARCH_GET_FS:
		*(NCX uintptr_t *)validate_writable(addr, sizeof(uintptr_t)) = GET_USER_FSBASE();
		break;

	case ARCH_GET_GS:
		*(NCX uintptr_t *)validate_writable(addr, sizeof(uintptr_t)) = GET_USER_GSBASE();
		break;

	case ARCH_GET_CPUID:
		return arch_get_cpuid() ? 1 : 0;

	case ARCH_SET_CPUID:
		arch_set_cpuid(addr != 0);
		break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_ARCH_PRCTL_COMMAND,
		      command);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_ARCH_PRCTL */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_ARCH_PRCTL
DEFINE_COMPAT_SYSCALL2(syscall_slong_t, arch_prctl,
                       unsigned int, command,
                       NCX UNCHECKED compat_uintptr_t *, addr) {
	/* Predict (and optimize for) the use by libdl, which uses
	 * this system call to assign  the address of the  initial
	 * TLS segment.
	 * s.a. <kos/bits/thread.h>: `__x86_fast_wrgsbase()' */
	switch (__builtin_expect(command, ARCH_SET_GS)) {

	case ARCH_SET_GS:
		SET_USER_GSBASE(addr);
		break;

	case ARCH_SET_FS:
		SET_USER_FSBASE(addr);
		break;

	case ARCH_GET_FS:
		*(NCX compat_uintptr_t *)compat_validate_writable(addr, sizeof(compat_uintptr_t)) = GET_USER_FSBASE();
		break;

	case ARCH_GET_GS:
		*(NCX compat_uintptr_t *)compat_validate_writable(addr, sizeof(compat_uintptr_t)) = GET_USER_GSBASE();
		break;

	case ARCH_GET_CPUID:
		return arch_get_cpuid() ? 1 : 0;

	case ARCH_SET_CPUID:
		arch_set_cpuid(addr != 0);
		break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_ARCH_PRCTL_COMMAND,
		      command);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_ARCH_PRCTL */

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_ARCH_PRCTL_C */
