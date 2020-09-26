/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_ALTERNATIVE_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_ALTERNATIVE_C 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */

#include <kernel/compiler.h>

#include <kernel/boot.h>
#include <kernel/driver.h>
#include <kernel/x86/alternative.h>
#include <kernel/x86/cpuid.h>

#include <asm/cpu-feature.h>
#include <asm/intrin.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

/* Check if the machine supports a given `feature' */
PRIVATE ATTR_COLDTEXT NOBLOCK WUNUSED bool
NOTHROW(FCALL has_feature)(u32 feature) {
	bool result = false;
	switch (feature & X86_FEATURE_TYPMASK) {

	case X86_FEATURE_TYP_CPUID: {
		u32 word = 0;
		STATIC_ASSERT(X86_FEATURE_TYP_CPUID == 0);
		/* Use the boot-cpu's cpuid feature table (since that one
		 * can be overwritten, unlike the actual cpuid instruction) */
		switch (feature & ~X86_FEATURE_BITMASK) {

		case X86_FEATURE(0, A, 0):
			word = bootcpu_x86_cpuid.ci_0a;
			goto do_generic_cpuid;

		case X86_FEATURE(0, C, 0):
			word = bootcpu_x86_cpuid.ci_0c;
			goto do_generic_cpuid;

		case X86_FEATURE(0, D, 0):
			word = bootcpu_x86_cpuid.ci_0d;
			goto do_generic_cpuid;

		case X86_FEATURE(0, B, 0):
			word = bootcpu_x86_cpuid.ci_0b;
			goto do_generic_cpuid;

		case X86_FEATURE(1, A, 0):
			word = bootcpu_x86_cpuid.ci_1a;
			goto do_generic_cpuid;

		case X86_FEATURE(1, C, 0):
			word = bootcpu_x86_cpuid.ci_1c;
			goto do_generic_cpuid;

		case X86_FEATURE(1, D, 0):
			word = bootcpu_x86_cpuid.ci_1d;
			goto do_generic_cpuid;

		case X86_FEATURE(1, B, 0):
			word = bootcpu_x86_cpuid.ci_1b;
			goto do_generic_cpuid;

		case X86_FEATURE(7, C, 0):
			word = bootcpu_x86_cpuid.ci_7c;
			goto do_generic_cpuid;

		case X86_FEATURE(7, D, 0):
			word = bootcpu_x86_cpuid.ci_7d;
			goto do_generic_cpuid;

		case X86_FEATURE(7, B, 0):
			word = bootcpu_x86_cpuid.ci_7b;
			goto do_generic_cpuid;

		case X86_FEATURE(0x80000000, A, 0):
			word = bootcpu_x86_cpuid.ci_80000000a;
			goto do_generic_cpuid;

		case X86_FEATURE(0x80000001, C, 0):
			word = bootcpu_x86_cpuid.ci_80000001c;
			goto do_generic_cpuid;

		case X86_FEATURE(0x80000001, D, 0):
			word = bootcpu_x86_cpuid.ci_80000001d;
			goto do_generic_cpuid;

		default:
			/* Actually invoke cpuid. */
do_generic_cpuid:
			if (X86_HAVE_CPUID) {
				u32 regs[4];
				__cpuid(X86_FEATURE_GETEAX(feature),
				        &regs[0], &regs[1],
				        &regs[2], &regs[3]);
				/* Test the requested bit. */
				word = regs[X86_FEATURE_GETREG(feature)];
			}
			break;
		}
		result = (word & ((u32)1 << X86_FEATURE_GETBIT(feature))) != 0;
	}	break;

	case X86_FEATURE_TYP_MISC: {
#ifdef __x86_64__
		result = true; /* All misc. feature are currently supported unconditionally on x86_64! */
#else /* __x86_64__ */
		STATIC_ASSERT((X86_FEAT_486 & ~X86_FEATURE_TYPMASK) == CPU_FEATURE_FI486);
		result = (bootcpu_x86_cpufeatures & (feature & ~X86_FEATURE_TYPMASK)) != 0;
#endif /* !__x86_64__ */
	}	break;

	case X86_FEATURE_TYP_CONST:
		result = feature == X86_FEAT_TRUE;
		break;

	default:
		break;
	}
	return result;
}

PRIVATE ATTR_COLDTEXT void FCALL
init_alternatives(struct x86_alternative const *start,
                  struct x86_alternative const *end,
                  uintptr_t loadaddr) {
	for (; start < end; ++start) {
		uintptr_t start_offset;
		uintptr_t end_offset;
		size_t total_len;
		void *dest;
		if (!has_feature(start->xa_feature))
			continue; /* Not supported. */
		start_offset = start->xa_start;
		end_offset   = start->xa_end;
		total_len    = end_offset - start_offset;
		assert(end_offset >= start_offset);
		assert(start->xa_altlen <= total_len);
		/* Copy alternative code. */
		dest = mempcpy((byte_t *)loadaddr + start_offset,
		               (byte_t *)loadaddr + start->xa_altcode,
		               start->xa_altlen);
		/* Pad with nop-instructions. */
		memset(dest, 0x90, total_len - start->xa_altlen);
		/* Skip additional alternatives for the same region. */
		do {
			++start;
		} while (start < end &&
		         start->xa_start == start_offset &&
		         start->xa_end == end_offset);
	}
}


/* Perform arch-specific driver initialization.
 * On x86, this function handles code alternatives, as
 * defined via the optional `.alternatives' section. */
INTERN ATTR_COLDTEXT NONNULL((1)) void KCALL
arch_driver_initialize(struct driver *__restrict self) {
	REF struct driver_section *sect;
	sect = driver_section_lock(self, ".alternatives");
	if (!sect)
		return;
	FINALLY_DECREF_UNLIKELY(sect);
	init_alternatives((struct x86_alternative const *)(sect->ds_data),
	                  (struct x86_alternative const *)((byte_t *)sect->ds_data + sect->ds_size),
	                  self->d_loadaddr);
}

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_alternatives)(void) {
	/* Initialize alternatives for the kernel core. */
	init_alternatives(__x86_alternatives_start,
	                  __x86_alternatives_end,
	                  0);
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_ALTERNATIVE_C */
