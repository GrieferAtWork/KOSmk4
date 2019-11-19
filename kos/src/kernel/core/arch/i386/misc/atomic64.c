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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_ATOMIC64_C
#define GUARD_KERNEL_CORE_ARCH_I386_ATOMIC64_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/host.h>

#ifndef __x86_64__
#include <asm/cpu-cpuid.h>
#include <kernel/boot.h>
#include <kernel/cpuid.h>
#include <sched/atomic64.h>
#include <assert.h>

DECL_BEGIN

INTDEF NOBLOCK ATTR_LEAF WUNUSED NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_read)(struct atomic64 *__restrict self);
INTDEF NOBLOCK ATTR_LEAF WUNUSED NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_read_r)(struct atomic64 *__restrict self);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) void NOTHROW(FCALL emulated_atomic64_write)(struct atomic64 *__restrict self, u64 value);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) void NOTHROW(FCALL emulated_atomic64_write_r)(struct atomic64 *__restrict self, u64 value);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) bool NOTHROW(FCALL emulated_atomic64_cmpxch)(struct atomic64 *__restrict self, u64 oldval, u64 newval);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) bool NOTHROW(FCALL emulated_atomic64_cmpxch_r)(struct atomic64 *__restrict self, u64 oldval, u64 newval);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_cmpxch_val)(struct atomic64 *__restrict self, u64 oldval, u64 newval);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_cmpxch_val_r)(struct atomic64 *__restrict self, u64 oldval, u64 newval);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_xch)(struct atomic64 *__restrict self, u64 value);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_xch_r)(struct atomic64 *__restrict self, u64 value);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_fetchadd)(struct atomic64 *__restrict self, u64 value);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_fetchadd_r)(struct atomic64 *__restrict self, u64 value);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_fetchand)(struct atomic64 *__restrict self, u64 value);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_fetchand_r)(struct atomic64 *__restrict self, u64 value);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_fetchor)(struct atomic64 *__restrict self, u64 value);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_fetchor_r)(struct atomic64 *__restrict self, u64 value);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_fetchxor)(struct atomic64 *__restrict self, u64 value);
INTDEF NOBLOCK ATTR_LEAF NONNULL((1)) u64 NOTHROW(FCALL emulated_atomic64_fetchxor_r)(struct atomic64 *__restrict self, u64 value);

LOCAL ATTR_FREETEXT NOBLOCK void
NOTHROW(FCALL install_jmp)(void *redirection_addr,
                           void const *redirection_target) {
	byte_t *dst = (byte_t *)redirection_addr;
	*(u8 *)(dst + 0) = 0xe9;
	*(s32 *)(dst + 1) = ((s32)(uintptr_t)redirection_target -
	                     (s32)(uintptr_t)(dst + 5));
}



/* Initialize the atomic64 configuration */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_atomic64)(void) {
	if (x86_bootcpu_cpuid.ci_1d & CPUID_1D_CX8) {
		/* Machine has native 64-bit atomic support. */
	} else {
		/* Must use the 64-bit atomic emulation. */
		install_jmp((void *)&atomic64_read, (void *)&emulated_atomic64_read);
		install_jmp((void *)&atomic64_read_r, (void *)&emulated_atomic64_read_r);
		install_jmp((void *)&atomic64_write, (void *)&emulated_atomic64_write);
		install_jmp((void *)&atomic64_write_r, (void *)&emulated_atomic64_write_r);
		install_jmp((void *)&atomic64_cmpxch, (void *)&emulated_atomic64_cmpxch);
		install_jmp((void *)&atomic64_cmpxch_r, (void *)&emulated_atomic64_cmpxch_r);
		install_jmp((void *)&atomic64_cmpxch_val, (void *)&emulated_atomic64_cmpxch_val);
		install_jmp((void *)&atomic64_cmpxch_val_r, (void *)&emulated_atomic64_cmpxch_val_r);
		install_jmp((void *)&atomic64_xch, (void *)&emulated_atomic64_xch);
		install_jmp((void *)&atomic64_xch_r, (void *)&emulated_atomic64_xch_r);
		install_jmp((void *)&atomic64_fetchadd, (void *)&emulated_atomic64_fetchadd);
		install_jmp((void *)&atomic64_fetchadd_r, (void *)&emulated_atomic64_fetchadd_r);
		install_jmp((void *)&atomic64_fetchand, (void *)&emulated_atomic64_fetchand);
		install_jmp((void *)&atomic64_fetchand_r, (void *)&emulated_atomic64_fetchand_r);
		install_jmp((void *)&atomic64_fetchor, (void *)&emulated_atomic64_fetchor);
		install_jmp((void *)&atomic64_fetchor_r, (void *)&emulated_atomic64_fetchor_r);
		install_jmp((void *)&atomic64_fetchxor, (void *)&emulated_atomic64_fetchxor);
		install_jmp((void *)&atomic64_fetchxor_r, (void *)&emulated_atomic64_fetchxor_r);
	}

#if !defined(NDEBUG) && 1
	{
		struct atomic64 a = ATOMIC64_INIT(16);
		assert(atomic64_read(&a) == 16);
		atomic64_write(&a, 12);
		assert(atomic64_read(&a) == 12);
		assert(atomic64_cmpxch_val(&a, 12, 14) == 12);
		assert(atomic64_cmpxch_val(&a, 12, 14) == 14);
		assert(atomic64_cmpxch(&a, 14, 13) == true);
		assert(atomic64_cmpxch(&a, 14, 13) == false);
		assert(atomic64_fetchadd(&a, 7) == 13);
		assert(atomic64_read(&a) == 20);
	}
#endif
}



DECL_END

#endif /* !__x86_64__ */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_ATOMIC64_C */
