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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_BREAKPOINT_C
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_BREAKPOINT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman.h>
#include <kernel/types.h>
#include <kernel/x86/breakpoint.h>
#include <sched/pertask.h>

#include <hybrid/host.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>

#include <assert.h>

DECL_BEGIN

/* Per-MMan debug registers. (lazily loaded during task switches)
 * NOTE: When  setting  a debug  register (using  __wrdrN()), you
 *       must  also update these fields accordingly. - Otherwise,
 *       any changes made will become lost the next time the mman
 *       is changed.
 * NOTE: These fields are _NOT_ inherited during `mman_fork()'! */
PUBLIC ATTR_PERMMAN ATTR_ALIGN(void *) thismman_x86_dr0    = 0;
PUBLIC ATTR_PERMMAN ATTR_ALIGN(void *) thismman_x86_dr1    = 0;
PUBLIC ATTR_PERMMAN ATTR_ALIGN(void *) thismman_x86_dr2    = 0;
PUBLIC ATTR_PERMMAN ATTR_ALIGN(void *) thismman_x86_dr3    = 0;
PUBLIC ATTR_PERMMAN ATTR_ALIGN(uintptr_t) thismman_x86_dr7 = 0;


#define thismman_x86_drN(n) (*thismman_x86_drN_impl(n))
LOCAL ATTR_CONST WUNUSED void **
NOTHROW(KCALL thismman_x86_drN_impl)(unsigned int n) {
	void **result;
	switch (n) {

	case 0:
		result = &thismman_x86_dr0;
		break;
	case 1:
		result = &thismman_x86_dr1;
		break;
	case 2:
		result = &thismman_x86_dr2;
		break;
	case 3:
		result = &thismman_x86_dr3;
		break;

	default: __builtin_unreachable();
	}
	return result;
}

LOCAL ATTR_PURE void *KCALL __rddrN0123(unsigned int n) {
	void *result;
	switch (n) {

	case 0:
		result = __rddr0();
		break;
	case 1:
		result = __rddr1();
		break;
	case 2:
		result = __rddr2();
		break;
	case 3:
		result = __rddr3();
		break;

	default: __builtin_unreachable();
	}
	return result;
}

LOCAL void KCALL __wrdrN0123(unsigned int n, void *value) {
	switch (n) {

	case 0:
		__wrdr0(value);
		break;
	case 1:
		__wrdr1(value);
		break;
	case 2:
		__wrdr2(value);
		break;
	case 3:
		__wrdr3(value);
		break;

	default: __builtin_unreachable();
	}
}



/* Add/Remove a local hardware breakpoint to the given VM.
 * @param: br_size: Breakpoint size (One of `DR_S(1|2|4|8)')
 * @param: br_cond: Breakpoint condition (One of `DR_C(EXEC|WRITE|READWRITE)')
 * @return: true:   Successfully added/deleted the breakpoint.
 * @return: false:  No unused breakpoints exist / the given breakpoint doesn't exist * */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL mman_addhwbreak)(struct mman *__restrict self,
                               void *addr,
                               unsigned int br_cond,
                               unsigned int br_size) {
	bool result = false;
	uintptr_t dr7;
	unsigned int i;
#ifdef __x86_64__
	assert(br_cond == DR_CEXEC || br_cond == DR_CWRITE ||
	       br_cond == DR_CREADWRITE);
#else /* __x86_64__ */
	assert(br_cond == DR_CEXEC || br_cond == DR_CWRITE ||
	       br_cond == DR_CREADWRITE || br_cond == DR_CIO);
#endif /* !__x86_64__ */
	assert(br_size == DR_S1 || br_size == DR_S2 ||
	       br_size == DR_S4 || br_size == DR_S8);
	dr7 = FORMMAN(self, thismman_x86_dr7);
	for (i = 0; i < DR7_BREAKPOINT_COUNT; ++i) {
		if (dr7 & (DR7_LN(i) | DR7_GN(i)))
			continue; /* Already in use */
		dr7 |= DR7_LN(i);
		dr7 &= ~(DR7_CN(i) | DR7_SN(i));
		dr7 |= br_cond << DR7_CN_SHIFT(i);
		dr7 |= br_size << DR7_SN_SHIFT(i);
		FORMMAN(self, thismman_x86_drN(i)) = addr;
		FORMMAN(self, thismman_x86_dr7) = dr7;
		if (self == THIS_MMAN) {
			/* Activate the breakpoint. */
			__wrdrN0123(i, addr);
			__wrdr7(dr7);
		}
		result = true;
		break;
	}
	return result;
}


PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL mman_delhwbreak)(struct mman *__restrict self,
                               void *addr,
                               unsigned int br_cond,
                               unsigned int br_size) {
	bool result = false;
	uintptr_t dr7;
	unsigned int i;
#ifdef __x86_64__
	assert(br_cond == DR_CEXEC || br_cond == DR_CWRITE ||
	       br_cond == DR_CREADWRITE);
#else /* __x86_64__ */
	assert(br_cond == DR_CEXEC || br_cond == DR_CWRITE ||
	       br_cond == DR_CREADWRITE || br_cond == DR_CIO);
#endif /* !__x86_64__ */
	assert(br_size == DR_S1 || br_size == DR_S2 ||
	       br_size == DR_S4 || br_size == DR_S8);
	dr7 = FORMMAN(self, thismman_x86_dr7);
	for (i = 0; i < DR7_BREAKPOINT_COUNT; ++i) {
		void *br_addr;
		if (!(dr7 & DR7_LN(i)))
			continue; /* unused */
		br_addr = FORMMAN(self, thismman_x86_drN(i));
		if (br_addr != addr)
			continue; /* Different address. */
		if (((dr7 & DR7_CN(i)) >> DR7_CN_SHIFT(i)) != br_cond)
			continue; /* Different break conditions. */
		if (((dr7 & DR7_SN(i)) >> DR7_SN_SHIFT(i)) != br_size)
			continue; /* Different breakpoint size. */
		/* Found it! */
		dr7 &= ~DR7_LN(i);
		FORMMAN(self, thismman_x86_dr7) = dr7;
		if (self == THIS_MMAN) {
			/* Deactivate the breakpoint. */
			__wrdr7(dr7);
		}
		result = true;
		break;
	}
	return result;
}

/* Clear all hardware breakpoints from `self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mman_clrhwbreak)(struct mman *__restrict self) {
	uintptr_t dr7;
	dr7 = FORMMAN(self, thismman_x86_dr7);
	dr7 &= ~(DR7_L0 | DR7_L1 | DR7_L2 | DR7_L3);
	FORMMAN(self, thismman_x86_dr7) = dr7;
	if (self == THIS_MMAN)
		__wrdr7(dr7);
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_BREAKPOINT_C */
