/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBCPUSTATE_ARCH_I386_REGISTER_C
#define GUARD_LIBCPUSTATE_ARCH_I386_REGISTER_C 1
#define _KOS_KERNEL_SOURCE 1

#include "../../api.h"
/**/
#include <hybrid/unaligned.h>

#include <asm/registers-compat.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/fpu-state-helpers.h>
#include <kos/kernel/fpu-state.h>
#include <kos/kernel/types.h>
#include <kos/types.h>

#include <string.h>

#include <libcpustate/register.h>

#include "register.h"


#ifdef __GNUC__
/* Suppress warnings about accessing unaligned pointers in `struct desctab' */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waddress-of-packed-member"
#endif /* __GNUC__ */

#ifdef __x86_64__
#define IRREGS_LOADSELF(T) /* nothing */
#define IRREGS_SELF        self
#define IRREGS_INDIRECTION *
#define IRREGS_NAME(x)     x
#else /* __x86_64__ */
#define IRREGS_LOADSELF(T) T *self = *pself;
#define IRREGS_SELF        pself
#define IRREGS_INDIRECTION **
#define IRREGS_NAME(x)     x##_p
#endif /* !__x86_64__ */

DECL_BEGIN

PRIVATE size_t
NOTHROW_NCX(CC getregval)(uintptr_t value, unsigned int regno,
                          void *__restrict buf, size_t buflen) {
	switch (regno & X86_REGISTER_SIZEMASK) {

	case X86_REGISTER_SIZEMASK_1BYTE:
		if (buflen >= 1)
			*(u8 *)buf = (u8)value;
		return 1;

	case X86_REGISTER_SIZEMASK_2BYTE:
		if (buflen >= 2)
			UNALIGNED_SET16((u16 *)buf, (u16)value);
		return 2;

	case X86_REGISTER_SIZEMASK_4BYTE:
		if (buflen >= 4)
			UNALIGNED_SET32((u32 *)buf, (u32)value);
		return 4;

#ifdef __x86_64__
	case X86_REGISTER_SIZEMASK_8BYTE:
		if (buflen >= 8)
			UNALIGNED_SET64((u64 *)buf, (u64)value);
		return 8;
#endif /* __x86_64__ */

	default: break;
	}
	return 0;
}

PRIVATE size_t
NOTHROW_NCX(CC setregptr)(void *__restrict pvalue, unsigned int regno,
                          void const *__restrict buf, size_t buflen) {
	switch (regno & X86_REGISTER_SIZEMASK) {

	case X86_REGISTER_SIZEMASK_1BYTE:
		if (buflen >= 1)
			*(u8 *)pvalue = *(u8 *)buf;
		return 1;

	case X86_REGISTER_SIZEMASK_2BYTE:
		if (buflen >= 2)
			*(u16 *)pvalue = UNALIGNED_GET16((u16 *)buf);
		return 2;

	case X86_REGISTER_SIZEMASK_4BYTE:
		if (buflen >= 4) {
			/* Set a pointer-sized register here, thus zero-extending to 64-bit on x86_64 */
			*(uintptr_t *)pvalue = UNALIGNED_GET32((u32 *)buf);
		}
		return 4;

#ifdef __x86_64__
	case X86_REGISTER_SIZEMASK_8BYTE:
		if (buflen >= 8)
			*(u64 *)pvalue = UNALIGNED_GET64((u64 *)buf);
		return 8;
#endif /* __x86_64__ */

	default: break;
	}
	return 0;
}

PRIVATE size_t
NOTHROW_NCX(CC setregptr16p)(uintptr_t *__restrict pvalue, unsigned int regno,
                             void const *__restrict buf, size_t buflen) {
	switch (regno & X86_REGISTER_SIZEMASK) {

	case X86_REGISTER_SIZEMASK_2BYTE:
	case X86_REGISTER_SIZEMASK_4BYTE:
#ifdef __x86_64__
	case X86_REGISTER_SIZEMASK_8BYTE:
#endif /* __x86_64__ */
		if (buflen >= 2)
			*pvalue = (uintptr_t)UNALIGNED_GET16((u16 *)buf);
		return 2;

	default: break;
	}
	return 0;
}

PRIVATE size_t
NOTHROW_NCX(CC setregptrp)(uintptr_t *__restrict pvalue, unsigned int regno,
                           void const *__restrict buf, size_t buflen) {
	switch (regno & X86_REGISTER_SIZEMASK) {

	case X86_REGISTER_SIZEMASK_2BYTE:
		if (buflen >= 2)
			*pvalue = (uintptr_t)UNALIGNED_GET16((u16 *)buf);
		return 2;

	case X86_REGISTER_SIZEMASK_4BYTE:
		if (buflen >= 4)
			*pvalue = (uintptr_t)UNALIGNED_GET32((u32 *)buf);
		return 4;

#ifdef __x86_64__
	case X86_REGISTER_SIZEMASK_8BYTE:
		if (buflen >= 8)
			*pvalue = (uintptr_t)UNALIGNED_GET64((u64 *)buf);
		return 8;
#endif /* __x86_64__ */

	default: break;
	}
	return 0;
}



/* Get/set the value of a given register `regno' (one of `X86_REGISTER_*' from <asm/register.h>)
 * NOTE: When `return > buflen', then
 *       getreg_*: The contents of `buf' are undefined.
 *       setreg_*: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of `X86_REGISTER_*' (from <asm/registers.h>)
 * @return: * :   The required buffer size, or 0 when `name' isn't recognized. */
INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_gpregs)(struct gpregs const *__restrict self, unsigned int regno,
                                     void *__restrict buf, size_t buflen) {
	uintptr_t value;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_GENERAL_PURPOSE)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case (X86_REGISTER_GENERAL_PURPOSE_PAX & X86_REGISTER_IDMASK):
		value = self->gp_pax;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PCX & X86_REGISTER_IDMASK):
		value = self->gp_pcx;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PDX & X86_REGISTER_IDMASK):
		value = self->gp_pdx;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PBX & X86_REGISTER_IDMASK):
		value = self->gp_pbx;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PSP & X86_REGISTER_IDMASK):
		value = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		        ? (self->gp_pax >> 8)
		        : self->gp_psp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PBP & X86_REGISTER_IDMASK):
		value = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		        ? (self->gp_pcx >> 8)
		        : self->gp_pbp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PSI & X86_REGISTER_IDMASK):
		value = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		        ? (self->gp_pdx >> 8)
		        : self->gp_psi;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PDI & X86_REGISTER_IDMASK):
		value = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		        ? (self->gp_pbx >> 8)
		        : self->gp_pdi;
		break;

#ifdef __x86_64__
	case (X86_REGISTER_GENERAL_PURPOSE_P8 & X86_REGISTER_IDMASK):
		value = self->gp_r8;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P9 & X86_REGISTER_IDMASK):
		value = self->gp_r9;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P10 & X86_REGISTER_IDMASK):
		value = self->gp_r10;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P11 & X86_REGISTER_IDMASK):
		value = self->gp_r11;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P12 & X86_REGISTER_IDMASK):
		value = self->gp_r12;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P13 & X86_REGISTER_IDMASK):
		value = self->gp_r13;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P14 & X86_REGISTER_IDMASK):
		value = self->gp_r14;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P15 & X86_REGISTER_IDMASK):
		value = self->gp_r15;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_SPL & X86_REGISTER_IDMASK):
		value = self->gp_psp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_BPL & X86_REGISTER_IDMASK):
		value = self->gp_pbp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_SIL & X86_REGISTER_IDMASK):
		value = self->gp_psi;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_DIL & X86_REGISTER_IDMASK):
		value = self->gp_pdi;
		break;
#endif /* __x86_64__ */

	default:
nope:
		return 0;
	}
	return getregval(value, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_gpregs)(struct gpregs *__restrict self, unsigned int regno,
                                     void const *__restrict buf, size_t buflen) {
	void *pvalue;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_GENERAL_PURPOSE)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case (X86_REGISTER_GENERAL_PURPOSE_PAX & X86_REGISTER_IDMASK):
		pvalue = &self->gp_pax;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PCX & X86_REGISTER_IDMASK):
		pvalue = &self->gp_pcx;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PDX & X86_REGISTER_IDMASK):
		pvalue = &self->gp_pdx;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PBX & X86_REGISTER_IDMASK):
		pvalue = &self->gp_pbx;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PSP & X86_REGISTER_IDMASK):
		pvalue = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		         ? (void *)((byte_t *)&self->gp_pax + 1)
		         : (void *)&self->gp_psp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PBP & X86_REGISTER_IDMASK):
		pvalue = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		         ? (void *)((byte_t *)&self->gp_pcx + 1)
		         : (void *)&self->gp_pbp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PSI & X86_REGISTER_IDMASK):
		pvalue = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		         ? (void *)((byte_t *)&self->gp_pdx + 1)
		         : (void *)&self->gp_psi;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PDI & X86_REGISTER_IDMASK):
		pvalue = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		         ? (void *)((byte_t *)&self->gp_pbx + 1)
		         : (void *)&self->gp_pdi;
		break;

#ifdef __x86_64__
	case (X86_REGISTER_GENERAL_PURPOSE_P8 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r8;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P9 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r9;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P10 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r10;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P11 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r11;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P12 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r12;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P13 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r13;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P14 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r14;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P15 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r15;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_SPL & X86_REGISTER_IDMASK):
		pvalue = &self->gp_psp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_BPL & X86_REGISTER_IDMASK):
		pvalue = &self->gp_pbp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_SIL & X86_REGISTER_IDMASK):
		pvalue = &self->gp_psi;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_DIL & X86_REGISTER_IDMASK):
		pvalue = &self->gp_pdi;
		break;
#endif /* __x86_64__ */

	default:
nope:
		return 0;
	}
	return setregptr(pvalue, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_sgregs)(struct sgregs const *__restrict self, unsigned int regno,
                                     void *__restrict buf, size_t buflen) {
	u16 value;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_SEGMENT)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case (X86_REGISTER_SEGMENT_ES & X86_REGISTER_IDMASK):
		value = self->sg_es16;
		break;

	case (X86_REGISTER_SEGMENT_DS & X86_REGISTER_IDMASK):
		value = self->sg_ds16;
		break;

	case (X86_REGISTER_SEGMENT_FS & X86_REGISTER_IDMASK):
		value = self->sg_fs16;
		break;

	case (X86_REGISTER_SEGMENT_GS & X86_REGISTER_IDMASK):
		value = self->sg_gs16;
		break;

	default:
nope:
		return 0;
	}
	return getregval(value, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_sgregs)(struct sgregs *__restrict self, unsigned int regno,
                                     void const *__restrict buf, size_t buflen) {
	uintptr_t *pvalue;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_SEGMENT)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case (X86_REGISTER_SEGMENT_ES & X86_REGISTER_IDMASK):
		pvalue = &self->sg_es;
		break;

	case (X86_REGISTER_SEGMENT_DS & X86_REGISTER_IDMASK):
		pvalue = &self->sg_ds;
		break;

	case (X86_REGISTER_SEGMENT_FS & X86_REGISTER_IDMASK):
		pvalue = &self->sg_fs;
		break;

	case (X86_REGISTER_SEGMENT_GS & X86_REGISTER_IDMASK):
		pvalue = &self->sg_gs;
		break;

	default:
nope:
		return 0;
	}
	return setregptr16p(pvalue, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_coregs)(struct coregs const *__restrict self, unsigned int regno,
                                     void *__restrict buf, size_t buflen) {
	uintptr_t value;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_CONTROL)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case (X86_REGISTER_CONTROL_CR0 & X86_REGISTER_IDMASK):
		value = self->co_cr0;
		break;

	case (X86_REGISTER_CONTROL_CR2 & X86_REGISTER_IDMASK):
		value = (uintptr_t)self->co_cr2;
		break;

	case (X86_REGISTER_CONTROL_CR3 & X86_REGISTER_IDMASK):
		value = self->co_cr3;
		break;

	case (X86_REGISTER_CONTROL_CR4 & X86_REGISTER_IDMASK):
		value = self->co_cr4;
		break;

	default:
nope:
		return 0;
	}
	return getregval(value, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_coregs)(struct coregs *__restrict self, unsigned int regno,
                                     void const *__restrict buf, size_t buflen) {
	uintptr_t *pvalue;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_CONTROL)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case (X86_REGISTER_CONTROL_CR0 & X86_REGISTER_IDMASK):
		pvalue = &self->co_cr0;
		break;

	case (X86_REGISTER_CONTROL_CR2 & X86_REGISTER_IDMASK):
		pvalue = (uintptr_t *)&self->co_cr2;
		break;

	case (X86_REGISTER_CONTROL_CR3 & X86_REGISTER_IDMASK):
		pvalue = &self->co_cr3;
		break;

	case (X86_REGISTER_CONTROL_CR4 & X86_REGISTER_IDMASK):
		pvalue = &self->co_cr4;
		break;

	default:
nope:
		return 0;
	}
	return setregptrp(pvalue, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_drregs)(struct drregs const *__restrict self, unsigned int regno,
                                     void *__restrict buf, size_t buflen) {
	uintptr_t value;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_CONTROL)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case (X86_REGISTER_DEBUG_DR0 & X86_REGISTER_IDMASK):
		value = (uintptr_t)self->dr_dr0;
		break;

	case (X86_REGISTER_DEBUG_DR1 & X86_REGISTER_IDMASK):
		value = (uintptr_t)self->dr_dr1;
		break;

	case (X86_REGISTER_DEBUG_DR2 & X86_REGISTER_IDMASK):
		value = (uintptr_t)self->dr_dr2;
		break;

	case (X86_REGISTER_DEBUG_DR3 & X86_REGISTER_IDMASK):
		value = (uintptr_t)self->dr_dr3;
		break;

	case (X86_REGISTER_DEBUG_DR6 & X86_REGISTER_IDMASK):
		value = self->dr_dr6;
		break;

	case (X86_REGISTER_DEBUG_DR7 & X86_REGISTER_IDMASK):
		value = self->dr_dr7;
		break;

	default:
nope:
		return 0;
	}
	return getregval(value, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_drregs)(struct drregs *__restrict self, unsigned int regno,
                                     void const *__restrict buf, size_t buflen) {
	uintptr_t *pvalue;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_DEBUG)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case (X86_REGISTER_DEBUG_DR0 & X86_REGISTER_IDMASK):
		pvalue = (uintptr_t *)&self->dr_dr0;
		break;

	case (X86_REGISTER_DEBUG_DR1 & X86_REGISTER_IDMASK):
		pvalue = (uintptr_t *)&self->dr_dr1;
		break;

	case (X86_REGISTER_DEBUG_DR2 & X86_REGISTER_IDMASK):
		pvalue = (uintptr_t *)&self->dr_dr2;
		break;

	case (X86_REGISTER_DEBUG_DR3 & X86_REGISTER_IDMASK):
		pvalue = (uintptr_t *)&self->dr_dr3;
		break;

	case (X86_REGISTER_DEBUG_DR6 & X86_REGISTER_IDMASK):
		pvalue = &self->dr_dr6;
		break;

	case (X86_REGISTER_DEBUG_DR7 & X86_REGISTER_IDMASK):
		pvalue = &self->dr_dr7;
		break;

	default:
nope:
		return 0;
	}
	return setregptrp(pvalue, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_ucpustate)(struct ucpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	size_t result;
	result = libcpu_getreg_gpregs(&self->ucs_gpregs, regno, buf, buflen);
	if (result != 0)
		goto done;
	result = libcpu_getreg_sgregs(&self->ucs_sgregs, regno, buf, buflen);
	if (result != 0)
		goto done;
#ifdef __x86_64__
	result = libcpu_getreg_sgbase(&self->ucs_sgbase, regno, buf, buflen);
	if (result != 0)
		goto done;
#endif /* __x86_64__ */
	switch (regno) {

#ifdef __x86_64__
	case X86_REGISTER_MISC_RFLAGS:
		if (buflen >= 8)
			UNALIGNED_SET64((u64 *)buf, (u64)self->ucs_pflags);
		return 8;

	case X86_REGISTER_MISC_RIP:
		if (buflen >= 8)
			UNALIGNED_SET64((u64 *)buf, (u64)self->ucs_pip);
		return 8;
#endif /* __x86_64__ */

	case X86_REGISTER_MISC_EFLAGS:
		if (buflen >= 4)
			UNALIGNED_SET32((u32 *)buf, (u32)self->ucs_pflags);
		return 4;

	case X86_REGISTER_MISC_FLAGS:
		if (buflen >= 2)
			UNALIGNED_SET16((u16 *)buf, (u16)self->ucs_pflags);
		return 2;

	case X86_REGISTER_MISC_EIP:
		if (buflen >= 4)
			UNALIGNED_SET32((u32 *)buf, (u32)self->ucs_pip);
		return 4;

	case X86_REGISTER_MISC_IP:
		if (buflen >= 2)
			UNALIGNED_SET16((u16 *)buf, (u16)self->ucs_pip);
		return 2;

	case X86_REGISTER_SEGMENT_CS:
		if (buflen >= 2)
			UNALIGNED_SET16((u16 *)buf, self->ucs_cs16);
		return 2;

	case X86_REGISTER_SEGMENT_SS:
		if (buflen >= 2)
			UNALIGNED_SET16((u16 *)buf, self->ucs_ss16);
		return 2;

	default:
		break;
	}
done:
	return result;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_ucpustate)(struct ucpustate *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	size_t result;
	result = libcpu_setreg_gpregs(&self->ucs_gpregs, regno, buf, buflen);
	if (result != 0)
		goto done;
	result = libcpu_setreg_sgregs(&self->ucs_sgregs, regno, buf, buflen);
	if (result != 0)
		goto done;
#ifdef __x86_64__
	result = libcpu_setreg_sgbase(&self->ucs_sgbase, regno, buf, buflen);
	if (result != 0)
		goto done;
#endif /* __x86_64__ */
	switch (regno) {

#ifdef __x86_64__
	case X86_REGISTER_MISC_RFLAGS:
		if (buflen >= 8)
			self->ucs_pflags = UNALIGNED_GET64((u64 *)buf);
		return 8;

	case X86_REGISTER_MISC_RIP:
		if (buflen >= 8)
			self->ucs_pip = UNALIGNED_GET64((u64 *)buf);
		return 8;
#endif /* __x86_64__ */

	case X86_REGISTER_MISC_EFLAGS:
		if (buflen >= 4)
			self->ucs_pflags = UNALIGNED_GET32((u32 *)buf);
		return 4;

	case X86_REGISTER_MISC_FLAGS:
		if (buflen >= 2)
			self->ucs_pflags = UNALIGNED_GET16((u16 *)buf);
		return 2;

	case X86_REGISTER_MISC_EIP:
		if (buflen >= 4)
			self->ucs_pip = UNALIGNED_GET32((u32 *)buf);
		return 4;

	case X86_REGISTER_MISC_IP:
		if (buflen >= 2)
			self->ucs_pip = UNALIGNED_GET16((u16 *)buf);
		return 2;

	case X86_REGISTER_SEGMENT_CS:
		if (buflen >= 2)
			self->ucs_cs = UNALIGNED_GET16((u16 *)buf);
		return 2;

	case X86_REGISTER_SEGMENT_SS:
		if (buflen >= 2)
			self->ucs_ss = UNALIGNED_GET16((u16 *)buf);
		return 2;

	default:
		break;
	}
done:
	return result;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_lcpustate)(struct lcpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	uintptr_t value;
	switch (regno & ~X86_REGISTER_SIZEMASK) {

#ifdef __x86_64__
	case (X86_REGISTER_GENERAL_PURPOSE_R15 & ~X86_REGISTER_SIZEMASK):
		value = self->lcs_r15;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_R14 & ~X86_REGISTER_SIZEMASK):
		value = self->lcs_r14;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_R13 & ~X86_REGISTER_SIZEMASK):
		value = self->lcs_r13;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_R12 & ~X86_REGISTER_SIZEMASK):
		value = self->lcs_r12;
		break;
#else /* __x86_64__ */
	case (X86_REGISTER_GENERAL_PURPOSE_PSI & ~X86_REGISTER_SIZEMASK):
		if ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
			goto nope;
		value = self->lcs_psi;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PDI & ~X86_REGISTER_SIZEMASK):
		value = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		        ? (self->lcs_pbx >> 8)
		        : self->lcs_pdi;
		break;
#endif /* !__x86_64__ */

	case (X86_REGISTER_GENERAL_PURPOSE_PSP & ~X86_REGISTER_SIZEMASK):
		if ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
			goto nope;
		value = self->lcs_psp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PBP & ~X86_REGISTER_SIZEMASK):
		if ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
			goto nope;
		value = self->lcs_pbp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PBX & ~X86_REGISTER_SIZEMASK):
		value = self->lcs_pbx;
		break;

	case (X86_REGISTER_MISC_PIP & ~X86_REGISTER_SIZEMASK):
		value = self->lcs_pip;
		break;

	default:
nope:
		return 0;
	}
	return getregval(value, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_lcpustate)(struct lcpustate *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	void *pvalue;
	switch (regno & ~X86_REGISTER_SIZEMASK) {

#ifdef __x86_64__
	case (X86_REGISTER_GENERAL_PURPOSE_R15 & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->lcs_r15;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_R14 & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->lcs_r14;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_R13 & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->lcs_r13;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_R12 & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->lcs_r12;
		break;
#else /* __x86_64__ */
	case (X86_REGISTER_GENERAL_PURPOSE_PSI & ~X86_REGISTER_SIZEMASK):
		if ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
			goto nope;
		pvalue = &self->lcs_psi;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PDI & ~X86_REGISTER_SIZEMASK):
		pvalue = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		         ? (void *)((byte_t *)&self->lcs_pbx + 1)
		         : (void *)&self->lcs_pdi;
		break;
#endif /* !__x86_64__ */

	case (X86_REGISTER_GENERAL_PURPOSE_PBX & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->lcs_pbx;
		break;
	case (X86_REGISTER_GENERAL_PURPOSE_PSP & ~X86_REGISTER_SIZEMASK):
		if ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
			goto nope;
		pvalue = &self->lcs_psp;
		break;
	case (X86_REGISTER_GENERAL_PURPOSE_PBP & ~X86_REGISTER_SIZEMASK):
		if ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
			goto nope;
		pvalue = &self->lcs_pbp;
		break;
	case (X86_REGISTER_MISC_PIP & ~X86_REGISTER_SIZEMASK):
		return setregptrp(&self->lcs_pip, regno, buf, buflen);

	default:
nope:
		return 0;
	}
	return setregptr(pvalue, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_kcpustate)(struct kcpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	size_t result;
	result = libcpu_getreg_gpregs(&self->kcs_gpregs, regno, buf, buflen);
	if (result != 0)
		goto done;
	switch (regno) {

#ifdef __x86_64__
	case X86_REGISTER_MISC_RFLAGS:
		if (buflen >= 8)
			UNALIGNED_SET64((u64 *)buf, (u64)self->kcs_pflags);
		return 8;

	case X86_REGISTER_MISC_RIP:
		if (buflen >= 8)
			UNALIGNED_SET64((u64 *)buf, (u64)self->kcs_pip);
		return 8;
#endif /* __x86_64__ */

	case X86_REGISTER_MISC_EFLAGS:
		if (buflen >= 4)
			UNALIGNED_SET32((u32 *)buf, (u32)self->kcs_pflags);
		return 4;

	case X86_REGISTER_MISC_FLAGS:
		if (buflen >= 2)
			UNALIGNED_SET16((u16 *)buf, (u16)self->kcs_pflags);
		return 2;

	case X86_REGISTER_MISC_EIP:
		if (buflen >= 4)
			UNALIGNED_SET32((u32 *)buf, (u32)self->kcs_pip);
		return 4;

	case X86_REGISTER_MISC_IP:
		if (buflen >= 2)
			UNALIGNED_SET16((u16 *)buf, (u16)self->kcs_pip);
		return 2;

	default:
		break;
	}
done:
	return result;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_kcpustate)(struct kcpustate *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	size_t result;
	result = libcpu_setreg_gpregs(&self->kcs_gpregs, regno, buf, buflen);
	if (result != 0)
		goto done;
	switch (regno) {

#ifdef __x86_64__
	case X86_REGISTER_MISC_RFLAGS:
		if (buflen >= 8)
			self->kcs_pflags = UNALIGNED_GET64((u64 *)buf);
		return 8;

	case X86_REGISTER_MISC_RIP:
		if (buflen >= 8)
			self->kcs_pip = UNALIGNED_GET64((u64 *)buf);
		return 8;
#endif /* __x86_64__ */

	case X86_REGISTER_MISC_EFLAGS:
		if (buflen >= 4)
			self->kcs_pflags = UNALIGNED_GET32((u32 *)buf);
		return 4;

	case X86_REGISTER_MISC_FLAGS:
		if (buflen >= 2)
			self->kcs_pflags = UNALIGNED_GET16((u16 *)buf);
		return 2;

	case X86_REGISTER_MISC_EIP:
		if (buflen >= 4)
			self->kcs_pip = UNALIGNED_GET32((u32 *)buf);
		return 4;

	case X86_REGISTER_MISC_IP:
		if (buflen >= 2)
			self->kcs_pip = UNALIGNED_GET16((u16 *)buf);
		return 2;

	default:
		break;
	}
done:
	return result;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_fcpustate)(struct fcpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	uintptr_t value;
	size_t result;
	result = libcpu_getreg_gpregs(&self->fcs_gpregs, regno, buf, buflen);
	if (result != 0)
		goto done;
	result = libcpu_getreg_coregs(&self->fcs_coregs, regno, buf, buflen);
	if (result != 0)
		goto done;
	result = libcpu_getreg_drregs(&self->fcs_drregs, regno, buf, buflen);
	if (result != 0)
		goto done;
#ifdef __x86_64__
	result = libcpu_getreg_sgbase(&self->fcs_sgbase, regno, buf, buflen);
	if (result != 0)
		goto done;
#endif /* __x86_64__ */
	switch (regno & ~X86_REGISTER_SIZEMASK) {

	case (X86_REGISTER_MISC_PFLAGS & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_pflags;
		break;

	case (X86_REGISTER_MISC_PIP & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_pip;
		break;

	case (X86_REGISTER_SEGMENT_ES & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_sgregs.sg_es16;
		break;

	case (X86_REGISTER_SEGMENT_CS & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_sgregs.sg_cs16;
		break;

	case (X86_REGISTER_SEGMENT_SS & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_sgregs.sg_ss16;
		break;

	case (X86_REGISTER_SEGMENT_DS & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_sgregs.sg_ds16;
		break;

	case (X86_REGISTER_SEGMENT_FS & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_sgregs.sg_fs16;
		break;

	case (X86_REGISTER_SEGMENT_GS & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_sgregs.sg_gs16;
		break;

	case (X86_REGISTER_MISC_TR & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_sgregs.sg_tr16;
		break;

	case (X86_REGISTER_MISC_LDT & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_sgregs.sg_ldt16;
		break;

	case (X86_REGISTER_MISC_GDT_LIMIT & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_gdt.dt_limit;
		break;

	case (X86_REGISTER_MISC_GDT_BASE & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_gdt.dt_base;
		break;

	case (X86_REGISTER_MISC_IDT_LIMIT & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_idt.dt_limit;
		break;

	case (X86_REGISTER_MISC_IDT_BASE & ~X86_REGISTER_SIZEMASK):
		value = self->fcs_idt.dt_base;
		break;

	default:
		goto done;
	}
	result = getregval(value, regno, buf, buflen);
done:
	return result;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_fcpustate)(struct fcpustate *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	uintptr_t *pvalue;
	size_t result;
	result = libcpu_setreg_gpregs(&self->fcs_gpregs, regno, buf, buflen);
	if (result != 0)
		goto done;
	result = libcpu_setreg_coregs(&self->fcs_coregs, regno, buf, buflen);
	if (result != 0)
		goto done;
	result = libcpu_setreg_drregs(&self->fcs_drregs, regno, buf, buflen);
	if (result != 0)
		goto done;
#ifdef __x86_64__
	result = libcpu_setreg_sgbase(&self->fcs_sgbase, regno, buf, buflen);
	if (result != 0)
		goto done;
#endif /* __x86_64__ */
	switch (regno & ~X86_REGISTER_SIZEMASK) {

	case (X86_REGISTER_MISC_PFLAGS & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->fcs_pflags;
		break;

	case (X86_REGISTER_MISC_PIP & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->fcs_pip;
		break;

	case (X86_REGISTER_SEGMENT_ES & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->fcs_sgregs.sg_es;
		goto do_set_reg16;

	case (X86_REGISTER_SEGMENT_CS & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->fcs_sgregs.sg_cs;
		goto do_set_reg16;

	case (X86_REGISTER_SEGMENT_SS & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->fcs_sgregs.sg_ss;
		goto do_set_reg16;

	case (X86_REGISTER_SEGMENT_DS & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->fcs_sgregs.sg_ds;
		goto do_set_reg16;

	case (X86_REGISTER_SEGMENT_FS & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->fcs_sgregs.sg_fs;
		goto do_set_reg16;

	case (X86_REGISTER_SEGMENT_GS & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->fcs_sgregs.sg_gs;
		goto do_set_reg16;

	case (X86_REGISTER_MISC_TR & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->fcs_sgregs.sg_tr;
		goto do_set_reg16;

	case (X86_REGISTER_MISC_LDT & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->fcs_sgregs.sg_ldt;
do_set_reg16:
		result = setregptr16p(pvalue, regno, buf, buflen);
		goto done;

	case (X86_REGISTER_MISC_GDT_BASE & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->fcs_gdt.dt_base;
		break;

	case (X86_REGISTER_MISC_IDT_BASE & ~X86_REGISTER_SIZEMASK):
		pvalue = &self->fcs_idt.dt_base;
		break;

	case (X86_REGISTER_MISC_GDT_LIMIT & ~X86_REGISTER_SIZEMASK): {
		u16 *pvalue16;
		pvalue16 = &self->fcs_gdt.dt_limit;
		goto do_set_reg16_real;
	case (X86_REGISTER_MISC_IDT_LIMIT & ~X86_REGISTER_SIZEMASK):
		pvalue16 = &self->fcs_idt.dt_limit;
do_set_reg16_real:
		if ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_2BYTE) {
			if (buflen >= 2)
				*pvalue16 = (uintptr_t)UNALIGNED_GET16((u16 *)buf);
			result = 2;
		}
	}	goto done;

	default:
		goto done;
	}
	result = setregptr(pvalue, regno, buf, buflen);
done:
	return result;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_sfpuenv)(struct sfpuenv const *__restrict self, unsigned int regno,
                                      void *__restrict buf, size_t buflen) {
	uintptr_t value;
	switch (regno & ~X86_REGISTER_SIZEMASK) {

	case (X86_REGISTER_MISC_FCW & ~X86_REGISTER_SIZEMASK):
		value = self->fe_fcw;
		break;

	case (X86_REGISTER_MISC_FSW & ~X86_REGISTER_SIZEMASK):
		value = self->fe_fsw;
		break;

	case (X86_REGISTER_MISC_FTW & ~X86_REGISTER_SIZEMASK):
		value = self->fe_ftw;
		break;

	case (X86_REGISTER_MISC_FTWX & ~X86_REGISTER_SIZEMASK):
		value = fpustate_ftw2ftwx(self->fe_ftw);
		break;

	case (X86_REGISTER_MISC_FOP & ~X86_REGISTER_SIZEMASK):
		value = self->fe_fop & ((1 << 11) - 1);
		break;

	case (X86_REGISTER_MISC_FIP & ~X86_REGISTER_SIZEMASK):
		value = self->fe_fip;
		break;

	case (X86_REGISTER_MISC_FCS & ~X86_REGISTER_SIZEMASK):
		value = self->fe_fcs;
		break;

	case (X86_REGISTER_MISC_FDP & ~X86_REGISTER_SIZEMASK):
		value = self->fe_fdp;
		break;

	case (X86_REGISTER_MISC_FDS & ~X86_REGISTER_SIZEMASK):
		value = self->fe_fds;
		break;

	default:
		return 0;
	}
	return getregval(value, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_sfpuenv)(struct sfpuenv *__restrict self, unsigned int regno,
                                      void const *__restrict buf, size_t buflen) {
	size_t result;
	uintptr_t value;
	switch (regno & X86_REGISTER_SIZEMASK) {

	case X86_REGISTER_SIZEMASK_1BYTE:
		result = 1;
		if (buflen < 1)
			goto done;
		value = *(u8 *)buf;
		break;

	case X86_REGISTER_SIZEMASK_2BYTE:
		result = 2;
		if (buflen < 2)
			goto done;
		value = UNALIGNED_GET16((u16 *)buf);
		break;

	case X86_REGISTER_SIZEMASK_4BYTE:
		result = 4;
		if (buflen < 4)
			goto done;
		value = UNALIGNED_GET32((u32 *)buf);
		break;

#ifdef __x86_64__
	case X86_REGISTER_SIZEMASK_8BYTE:
		result = 8;
		if (buflen < 8)
			goto done;
		value = UNALIGNED_GET64((u64 *)buf);
		break;
#endif /* __x86_64__ */

	default: goto nope;
	}

	switch (regno & ~X86_REGISTER_SIZEMASK) {

	case (X86_REGISTER_MISC_FCW & ~X86_REGISTER_SIZEMASK):
		self->fe_fcw = (u16)value;
		break;

	case (X86_REGISTER_MISC_FSW & ~X86_REGISTER_SIZEMASK):
		self->fe_fsw = (u16)value;
		break;

	case (X86_REGISTER_MISC_FTW & ~X86_REGISTER_SIZEMASK):
		self->fe_ftw = (u16)value;
		break;

	case (X86_REGISTER_MISC_FTWX & ~X86_REGISTER_SIZEMASK):
		if (value != fpustate_ftw2ftwx(self->fe_ftw))
			goto nope;
		break;

	case (X86_REGISTER_MISC_FOP & ~X86_REGISTER_SIZEMASK):
		self->fe_fop = (u16)(value & ((1 << 11) - 1));
		break;

	case (X86_REGISTER_MISC_FIP & ~X86_REGISTER_SIZEMASK):
		self->fe_fip = (u32)value;
		break;

	case (X86_REGISTER_MISC_FCS & ~X86_REGISTER_SIZEMASK):
		self->fe_fcs = (u16)value;
		break;

	case (X86_REGISTER_MISC_FDP & ~X86_REGISTER_SIZEMASK):
		self->fe_fdp = (u32)value;
		break;

	case (X86_REGISTER_MISC_FDS & ~X86_REGISTER_SIZEMASK):
		self->fe_fds = (u16)value;
		break;

	default:
nope:
		return 0;
	}
done:
	return result;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_sfpustate)(struct sfpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	if ((regno & X86_REGISTER_CLASSMASK) == X86_REGISTER_FLOAT &&
	    (regno & X86_REGISTER_IDMASK) <= 7) {
		if (buflen >= 10)
			memcpy(buf, &self->fs_regs[regno & X86_REGISTER_IDMASK], 10);
		return 10;
	}
	return libcpu_getreg_sfpuenv(&self->fs_env, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_sfpustate)(struct sfpustate *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	size_t result;
	if ((regno & X86_REGISTER_CLASSMASK) == X86_REGISTER_FLOAT &&
	    (regno & X86_REGISTER_IDMASK) <= 7) {
		if (buflen >= 10)
			memcpy(&self->fs_regs[regno & X86_REGISTER_IDMASK], buf, 10);
		return 10;
	}
	result = libcpu_setreg_sfpuenv(&self->fs_env, regno, buf, buflen);
	if (result == 0 &&
	    (regno & ~X86_REGISTER_SIZEMASK) == (X86_REGISTER_MISC_FTWX & ~X86_REGISTER_SIZEMASK)) {
		uintptr_t value;
		switch (regno & X86_REGISTER_SIZEMASK) {

		case X86_REGISTER_SIZEMASK_1BYTE:
			result = 1;
			if (buflen < 1)
				goto done;
			value = *(u8 *)buf;
			break;

		case X86_REGISTER_SIZEMASK_2BYTE:
			result = 2;
			if (buflen < 2)
				goto done;
			value = UNALIGNED_GET16((u16 *)buf);
			break;

		case X86_REGISTER_SIZEMASK_4BYTE:
			result = 4;
			if (buflen < 4)
				goto done;
			value = UNALIGNED_GET32((u32 *)buf);
			break;

#ifdef __x86_64__
		case X86_REGISTER_SIZEMASK_8BYTE:
			result = 8;
			if (buflen < 8)
				goto done;
			value = UNALIGNED_GET64((u64 *)buf);
			break;
#endif /* __x86_64__ */

		default: goto done;
		}
		/* Decompress the register state. */
		self->fs_ftw = fpustate_ftwx2ftw((u8)value, self->fs_regs);
	}
done:
	return result;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_xfpustate)(struct xfpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	uintptr_t value;
	switch (regno & ~X86_REGISTER_SIZEMASK) {

	case (X86_REGISTER_FLOAT_ST0 & ~X86_REGISTER_SIZEMASK)...(X86_REGISTER_FLOAT_ST7 & ~X86_REGISTER_SIZEMASK):
		if (buflen >= 10)
			memcpy(buf, &self->fx_regs[regno & X86_REGISTER_IDMASK], 10);
		return 10;

	case (X86_REGISTER_MMX_MM0 & ~X86_REGISTER_SIZEMASK)...(X86_REGISTER_MMX_MM7 & ~X86_REGISTER_SIZEMASK):
		if (buflen >= 16)
			memcpy(buf, &self->fx_regs[regno & X86_REGISTER_IDMASK], 16);
		return 16;

#ifdef __x86_64__
	case (X86_REGISTER_XMM_XMM0 & ~X86_REGISTER_SIZEMASK)...(X86_REGISTER_XMM_XMM15 & ~X86_REGISTER_SIZEMASK):
	case (X86_REGISTER_YMM_YMM0 & ~X86_REGISTER_SIZEMASK)...(X86_REGISTER_YMM_YMM15 & ~X86_REGISTER_SIZEMASK):
#else /* __x86_64__ */
	case (X86_REGISTER_XMM_XMM0 & ~X86_REGISTER_SIZEMASK)...(X86_REGISTER_XMM_XMM7 & ~X86_REGISTER_SIZEMASK):
	case (X86_REGISTER_YMM_YMM0 & ~X86_REGISTER_SIZEMASK)...(X86_REGISTER_YMM_YMM7 & ~X86_REGISTER_SIZEMASK):
#endif /* !__x86_64__ */
		if (buflen >= 16)
			memcpy(buf, &self->fx_xmm[regno & X86_REGISTER_IDMASK], 16);
		return 16;

	case (X86_REGISTER_MISC_FCW & ~X86_REGISTER_SIZEMASK):
		value = self->fx_fcw;
		break;

	case (X86_REGISTER_MISC_FSW & ~X86_REGISTER_SIZEMASK):
		value = self->fx_fsw;
		break;

	case (X86_REGISTER_MISC_FTW & ~X86_REGISTER_SIZEMASK):
		value = fpustate_ftwx2ftw(self->fx_ftw, self->fx_regs);
		break;

	case (X86_REGISTER_MISC_FTWX & ~X86_REGISTER_SIZEMASK):
		value = self->fx_ftw;
		break;

	case (X86_REGISTER_MISC_FOP & ~X86_REGISTER_SIZEMASK):
		value = self->fx_fop & ((1 << 11) - 1);
		break;

	case (X86_REGISTER_MISC_FIP & ~X86_REGISTER_SIZEMASK):
		value = self->fx_fip;
		break;

	case (X86_REGISTER_MISC_FDP & ~X86_REGISTER_SIZEMASK):
		value = self->fx_fdp;
		break;

#ifdef __x86_64__
	case (X86_REGISTER_MISC_FCS & ~X86_REGISTER_SIZEMASK):
		value = 0;
		break;

	case (X86_REGISTER_MISC_FDS & ~X86_REGISTER_SIZEMASK):
		value = 0;
		break;
#else /* __x86_64__ */
	case (X86_REGISTER_MISC_FCS & ~X86_REGISTER_SIZEMASK):
		value = self->fx_fcs;
		break;

	case (X86_REGISTER_MISC_FDS & ~X86_REGISTER_SIZEMASK):
		value = self->fx_fds;
		break;
#endif /* !__x86_64__ */

	case (X86_REGISTER_MISC_MXCSR & ~X86_REGISTER_SIZEMASK):
		value = self->fx_mxcsr;
		break;

	case (X86_REGISTER_MISC_MXCSR_MASK & ~X86_REGISTER_SIZEMASK):
		value = self->fx_mxcsr_mask;
		break;

	default:
		return 0;
	}
	return getregval(value, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_xfpustate)(struct xfpustate *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	size_t result;
	uintptr_t value;
	switch (regno & ~X86_REGISTER_SIZEMASK) {

	case (X86_REGISTER_FLOAT_ST0 & ~X86_REGISTER_SIZEMASK)...(X86_REGISTER_FLOAT_ST7 & ~X86_REGISTER_SIZEMASK):
		if (buflen >= 10) {
			memcpy(&self->fx_regs[regno & X86_REGISTER_IDMASK], buf, 10);
			memset((byte_t *)&self->fx_regs[regno & X86_REGISTER_IDMASK] + 10, 0, 6);
		}
		return 10;

	case (X86_REGISTER_MMX_MM0 & ~X86_REGISTER_SIZEMASK)...(X86_REGISTER_MMX_MM7 & ~X86_REGISTER_SIZEMASK):
		if (buflen >= 16)
			memcpy(&self->fx_regs[regno & X86_REGISTER_IDMASK], buf, 16);
		return 16;

#ifdef __x86_64__
	case (X86_REGISTER_XMM_XMM0 & ~X86_REGISTER_SIZEMASK)...(X86_REGISTER_XMM_XMM15 & ~X86_REGISTER_SIZEMASK):
	case (X86_REGISTER_YMM_YMM0 & ~X86_REGISTER_SIZEMASK)...(X86_REGISTER_YMM_YMM15 & ~X86_REGISTER_SIZEMASK):
#else /* __x86_64__ */
	case (X86_REGISTER_XMM_XMM0 & ~X86_REGISTER_SIZEMASK)...(X86_REGISTER_XMM_XMM7 & ~X86_REGISTER_SIZEMASK):
	case (X86_REGISTER_YMM_YMM0 & ~X86_REGISTER_SIZEMASK)...(X86_REGISTER_YMM_YMM7 & ~X86_REGISTER_SIZEMASK):
#endif /* !__x86_64__ */
		if (buflen >= 16)
			memcpy(&self->fx_xmm[regno & X86_REGISTER_IDMASK], buf, 16);
		return 16;

	default: break;
	}
	switch (regno & X86_REGISTER_SIZEMASK) {

	case X86_REGISTER_SIZEMASK_1BYTE:
		result = 1;
		if (buflen < 1)
			goto done;
		value = *(u8 *)buf;
		break;

	case X86_REGISTER_SIZEMASK_2BYTE:
		result = 2;
		if (buflen < 2)
			goto done;
		value = UNALIGNED_GET16((u16 *)buf);
		break;

	case X86_REGISTER_SIZEMASK_4BYTE:
		result = 4;
		if (buflen < 4)
			goto done;
		value = UNALIGNED_GET32((u32 *)buf);
		break;

#ifdef __x86_64__
	case X86_REGISTER_SIZEMASK_8BYTE:
		result = 8;
		if (buflen < 8)
			goto done;
		value = UNALIGNED_GET64((u64 *)buf);
		break;
#endif /* __x86_64__ */

	default: goto nope;
	}
	switch (regno & ~X86_REGISTER_SIZEMASK) {

	case (X86_REGISTER_MISC_FCW & ~X86_REGISTER_SIZEMASK):
		self->fx_fcw = (u16)value;
		break;

	case (X86_REGISTER_MISC_FSW & ~X86_REGISTER_SIZEMASK):
		self->fx_fsw = (u16)value;
		break;

	case (X86_REGISTER_MISC_FTW & ~X86_REGISTER_SIZEMASK):
		self->fx_ftw = fpustate_ftw2ftwx((u16)value);
		break;

	case (X86_REGISTER_MISC_FTWX & ~X86_REGISTER_SIZEMASK):
		self->fx_ftw = (u8)value;
		break;

	case (X86_REGISTER_MISC_FOP & ~X86_REGISTER_SIZEMASK):
		self->fx_fop = (u16)(value & ((1 << 11) - 1));
		break;

	case (X86_REGISTER_MISC_FIP & ~X86_REGISTER_SIZEMASK):
		self->fx_fip = (uintptr_t)value;
		break;

	case (X86_REGISTER_MISC_FDP & ~X86_REGISTER_SIZEMASK):
		self->fx_fdp = (uintptr_t)value;
		break;

#ifdef __x86_64__
	case (X86_REGISTER_MISC_FCS & ~X86_REGISTER_SIZEMASK):
		if (value != 0)
			goto nope;
		break;

	case (X86_REGISTER_MISC_FDS & ~X86_REGISTER_SIZEMASK):
		if (value != 0)
			goto nope;
		break;
#else /* __x86_64__ */
	case (X86_REGISTER_MISC_FCS & ~X86_REGISTER_SIZEMASK):
		self->fx_fcs = (u16)value;
		break;

	case (X86_REGISTER_MISC_FDS & ~X86_REGISTER_SIZEMASK):
		self->fx_fds = (u16)value;
		break;
#endif /* !__x86_64__ */

	case (X86_REGISTER_MISC_MXCSR & ~X86_REGISTER_SIZEMASK):
		self->fx_mxcsr = (u32)value;
		break;

	case (X86_REGISTER_MISC_MXCSR_MASK & ~X86_REGISTER_SIZEMASK):
		self->fx_mxcsr_mask = (u32)value;
		break;

	default:
nope:
		return 0;
	}
done:
	return result;
}

#ifdef __x86_64__
INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_gpregsnsp)(struct gpregsnsp const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	uintptr_t value;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_GENERAL_PURPOSE)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case (X86_REGISTER_GENERAL_PURPOSE_PAX & X86_REGISTER_IDMASK):
		value = self->gp_pax;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PCX & X86_REGISTER_IDMASK):
		value = self->gp_pcx;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PDX & X86_REGISTER_IDMASK):
		value = self->gp_pdx;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PBX & X86_REGISTER_IDMASK):
		value = self->gp_pbx;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PSP & X86_REGISTER_IDMASK):
		if ((regno & X86_REGISTER_SIZEMASK) != X86_REGISTER_SIZEMASK_1BYTE)
			goto nope;
		value = self->gp_pax >> 8;
		break;
	case (X86_REGISTER_GENERAL_PURPOSE_PBP & X86_REGISTER_IDMASK):
		value = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		        ? (self->gp_pcx >> 8)
		        : self->gp_pbp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PSI & X86_REGISTER_IDMASK):
		value = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		        ? (self->gp_pdx >> 8)
		        : self->gp_psi;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PDI & X86_REGISTER_IDMASK):
		value = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		        ? (self->gp_pbx >> 8)
		        : self->gp_pdi;
		break;

#ifdef __x86_64__
	case (X86_REGISTER_GENERAL_PURPOSE_P8 & X86_REGISTER_IDMASK):
		value = self->gp_r8;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P9 & X86_REGISTER_IDMASK):
		value = self->gp_r9;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P10 & X86_REGISTER_IDMASK):
		value = self->gp_r10;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P11 & X86_REGISTER_IDMASK):
		value = self->gp_r11;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P12 & X86_REGISTER_IDMASK):
		value = self->gp_r12;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P13 & X86_REGISTER_IDMASK):
		value = self->gp_r13;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P14 & X86_REGISTER_IDMASK):
		value = self->gp_r14;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P15 & X86_REGISTER_IDMASK):
		value = self->gp_r15;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_BPL & X86_REGISTER_IDMASK):
		value = self->gp_pbp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_SIL & X86_REGISTER_IDMASK):
		value = self->gp_psi;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_DIL & X86_REGISTER_IDMASK):
		value = self->gp_pdi;
		break;
#endif /* __x86_64__ */

	default:
nope:
		return 0;
	}
	return getregval(value, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_gpregsnsp)(struct gpregsnsp *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	void *pvalue;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_GENERAL_PURPOSE)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case (X86_REGISTER_GENERAL_PURPOSE_PAX & X86_REGISTER_IDMASK):
		pvalue = &self->gp_pax;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PCX & X86_REGISTER_IDMASK):
		pvalue = &self->gp_pcx;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PDX & X86_REGISTER_IDMASK):
		pvalue = &self->gp_pdx;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PBX & X86_REGISTER_IDMASK):
		pvalue = &self->gp_pbx;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PSP & X86_REGISTER_IDMASK):
		if ((regno & X86_REGISTER_SIZEMASK) != X86_REGISTER_SIZEMASK_1BYTE)
			goto nope;
		pvalue = (void *)((byte_t *)&self->gp_pax + 1);
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PBP & X86_REGISTER_IDMASK):
		pvalue = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		         ? (void *)((byte_t *)&self->gp_pcx + 1)
		         : (void *)&self->gp_pbp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PSI & X86_REGISTER_IDMASK):
		pvalue = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		         ? (void *)((byte_t *)&self->gp_pdx + 1)
		         : (void *)&self->gp_psi;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PDI & X86_REGISTER_IDMASK):
		pvalue = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE)
		         ? (void *)((byte_t *)&self->gp_pbx + 1)
		         : (void *)&self->gp_pdi;
		break;

#ifdef __x86_64__
	case (X86_REGISTER_GENERAL_PURPOSE_P8 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r8;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P9 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r9;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P10 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r10;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P11 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r11;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P12 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r12;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P13 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r13;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P14 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r14;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_P15 & X86_REGISTER_IDMASK):
		pvalue = &self->gp_r15;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_BPL & X86_REGISTER_IDMASK):
		pvalue = &self->gp_pbp;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_SIL & X86_REGISTER_IDMASK):
		pvalue = &self->gp_psi;
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_DIL & X86_REGISTER_IDMASK):
		pvalue = &self->gp_pdi;
		break;
#endif /* __x86_64__ */

	default:
nope:
		return 0;
	}
	return setregptr(pvalue, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_sgbase)(struct sgbase const *__restrict self, unsigned int regno,
                                     void *__restrict buf, size_t buflen) {
	uintptr_t value;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_MISC)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case (X86_REGISTER_MISC_FSBASE & X86_REGISTER_IDMASK):
		value = self->sg_fsbase;
		break;

	case (X86_REGISTER_MISC_GSBASE & X86_REGISTER_IDMASK):
		value = self->sg_gsbase;
		break;

	default:
nope:
		return 0;
	}
	return getregval(value, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_sgbase)(struct sgbase *__restrict self, unsigned int regno,
                                     void const *__restrict buf, size_t buflen) {
	uintptr_t *pvalue;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_MISC)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case (X86_REGISTER_MISC_FSBASE & X86_REGISTER_IDMASK):
		pvalue = &self->sg_fsbase;
		break;

	case (X86_REGISTER_MISC_GSBASE & X86_REGISTER_IDMASK):
		pvalue = &self->sg_gsbase;
		break;

	default:
nope:
		return 0;
	}
	return setregptrp(pvalue, regno, buf, buflen);
}

#endif /* __x86_64__ */

#if !defined(__KERNEL__) || defined(__INTELLISENSE__)
INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_mcontext)(struct mcontext const *__restrict self, unsigned int regno,
                                       void *__restrict buf, size_t buflen) {
	size_t result;
	result = libcpu_getreg_ucpustate(&self->mc_context, regno, buf, buflen);
	if (result != 0)
		goto done;
	if (self->mc_flags & __MCONTEXT_FLAG_HAVEXFPU) {
		result = libcpu_getreg_xfpustate(&self->mc_fpu.f_xsave, regno, buf, buflen);
		if (result != 0)
			goto done;
	} else if (self->mc_flags & __MCONTEXT_FLAG_HAVESFPU) {
		result = libcpu_getreg_sfpustate(&self->mc_fpu.f_ssave, regno, buf, buflen);
		if (result != 0)
			goto done;
	}
	if (((regno & ~X86_REGISTER_SIZEMASK) == X86_REGISTER_CONTROL_CR2) &&
	    (self->mc_flags & __MCONTEXT_FLAG_HAVECR2))
		return getregval(self->mc_cr2, regno, buf, buflen);
done:
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_mcontext)(struct mcontext *__restrict self, unsigned int regno,
                                       void const *__restrict buf, size_t buflen) {
	size_t result;
	result = libcpu_setreg_ucpustate(&self->mc_context, regno, buf, buflen);
	if (result != 0)
		goto done;
	if (self->mc_flags & __MCONTEXT_FLAG_HAVEXFPU) {
		result = libcpu_setreg_xfpustate(&self->mc_fpu.f_xsave, regno, buf, buflen);
		if (result != 0)
			goto done;
	} else if (self->mc_flags & __MCONTEXT_FLAG_HAVESFPU) {
		result = libcpu_setreg_sfpustate(&self->mc_fpu.f_ssave, regno, buf, buflen);
		if (result != 0)
			goto done;
	}
	if ((regno & ~X86_REGISTER_SIZEMASK) == X86_REGISTER_CONTROL_CR2) {
		result = setregptrp((uintptr_t *)&self->mc_cr2, regno, buf, buflen);
		if (result != 0)
			self->mc_flags |= __MCONTEXT_FLAG_HAVECR2;
		return result;
	}
done:
	return 0;
}

DEFINE_INTERN_ALIAS(libcpu_getreg_ucontext, libcpu_getreg_mcontext);
DEFINE_INTERN_ALIAS(libcpu_setreg_ucontext, libcpu_setreg_mcontext);

#endif /* !__KERNEL__ */


#if defined(__KERNEL__) || defined(__INTELLISENSE__)

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_irregs)(LIBCPUSTATE_IRREGS_STRUCT_TYPE const *__restrict self,
                                     unsigned int regno, void *__restrict buf, size_t buflen) {
	uintptr_t value;
	switch (regno & ~X86_REGISTER_SIZEMASK) {

	case (X86_REGISTER_MISC_PIP & ~X86_REGISTER_SIZEMASK):
		value = irregs_getpc(self);
		break;

	case (X86_REGISTER_SEGMENT_CS & ~X86_REGISTER_SIZEMASK):
		value = irregs_getcs(self);
		break;

	case (X86_REGISTER_MISC_PFLAGS & ~X86_REGISTER_SIZEMASK):
		value = irregs_getpflags(self);
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PSP & ~X86_REGISTER_SIZEMASK):
		value = irregs_getsp(self);
		break;

	case (X86_REGISTER_SEGMENT_SS & ~X86_REGISTER_SIZEMASK):
		value = irregs_getss(self);
		break;

#ifndef __x86_64__
	case (X86_REGISTER_SEGMENT_DS & ~X86_REGISTER_SIZEMASK):
		value = irregs_getds(self);
		break;

	case (X86_REGISTER_SEGMENT_ES & ~X86_REGISTER_SIZEMASK):
		value = irregs_getes(self);
		break;

	case (X86_REGISTER_SEGMENT_FS & ~X86_REGISTER_SIZEMASK):
		value = irregs_getfs(self);
		break;

	case (X86_REGISTER_SEGMENT_GS & ~X86_REGISTER_SIZEMASK):
		value = irregs_getgs(self);
		break;
#endif /* !__x86_64__ */

	default:
		return 0;
	}
	return getregval(value, regno, buf, buflen);
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC IRREGS_NAME(libcpu_setreg_irregs))(LIBCPUSTATE_IRREGS_STRUCT_TYPE IRREGS_INDIRECTION __restrict IRREGS_SELF,
                                                  unsigned int regno, void const *__restrict buf, size_t buflen) {
	size_t result;
	uintptr_t value;
	IRREGS_LOADSELF(LIBCPUSTATE_IRREGS_STRUCT_TYPE)
	switch (regno & X86_REGISTER_SIZEMASK) {

	case X86_REGISTER_SIZEMASK_1BYTE:
		result = 1;
		if (buflen < 1)
			goto done;
		value = *(u8 *)buf;
		break;

	case X86_REGISTER_SIZEMASK_2BYTE:
		result = 2;
		if (buflen < 2)
			goto done;
		value = UNALIGNED_GET16((u16 *)buf);
		break;

	case X86_REGISTER_SIZEMASK_4BYTE:
		result = 4;
		if (buflen < 4)
			goto done;
		value = UNALIGNED_GET32((u32 *)buf);
		break;

#ifdef __x86_64__
	case X86_REGISTER_SIZEMASK_8BYTE:
		result = 8;
		if (buflen < 8)
			goto done;
		value = UNALIGNED_GET64((u64 *)buf);
		break;
#endif /* __x86_64__ */

	default: goto nope;
	}

	switch (regno & ~X86_REGISTER_SIZEMASK) {

	case (X86_REGISTER_MISC_PIP & ~X86_REGISTER_SIZEMASK):
		irregs_setpc(self, value);
		break;

	case (X86_REGISTER_SEGMENT_CS & ~X86_REGISTER_SIZEMASK):
		irregs_setcs(self, value);
		break;

	case (X86_REGISTER_MISC_PFLAGS & ~X86_REGISTER_SIZEMASK):
		irregs_setpflags(self, value);
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PSP & ~X86_REGISTER_SIZEMASK):
#ifdef __x86_64__
		irregs_setuserpsp(self, value);
#else /* __x86_64__ */
		if (irregs_isuser(self))
			irregs_setuserpsp(self, value);
		else {
			struct irregs_kernel *new_irregs;
			new_irregs = (struct irregs_kernel *)(value - SIZEOF_IRREGS32_KERNEL);
			memcpy(new_irregs, self, SIZEOF_IRREGS32_KERNEL);
			*pself = new_irregs;
		}
#endif /* !__x86_64__ */
		break;

	case (X86_REGISTER_SEGMENT_SS & ~X86_REGISTER_SIZEMASK):
		if (!irregs_trysetss(self, value))
			goto nope;
		break;

#ifndef __x86_64__
	case (X86_REGISTER_SEGMENT_DS & ~X86_REGISTER_SIZEMASK):
		if (!irregs_trysetds(self, value))
			goto nope;
		break;

	case (X86_REGISTER_SEGMENT_ES & ~X86_REGISTER_SIZEMASK):
		if (!irregs_trysetes(self, value))
			goto nope;
		break;

	case (X86_REGISTER_SEGMENT_FS & ~X86_REGISTER_SIZEMASK):
		if (!irregs_trysetfs(self, value))
			goto nope;
		break;

	case (X86_REGISTER_SEGMENT_GS & ~X86_REGISTER_SIZEMASK):
		if (!irregs_trysetgs(self, value))
			goto nope;
		break;
#endif /* !__x86_64__ */

	default:
nope:
		return 0;
	}
done:
	return result;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_icpustate)(struct icpustate const *__restrict self,
                                        unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	size_t result;
#ifdef __x86_64__
	result = libcpu_getreg_irregs(&self->ics_irregs, regno, buf, buflen);
	if (result != 0)
		goto done;
	result = libcpu_getreg_gpregsnsp(&self->ics_gpregs, regno, buf, buflen);
#else /* __x86_64__ */
	uintptr_t value;
	switch (regno & ~X86_REGISTER_SIZEMASK) {

	case (X86_REGISTER_SEGMENT_DS & ~X86_REGISTER_SIZEMASK):
		value = icpustate_getds(self);
		break;

	case (X86_REGISTER_SEGMENT_ES & ~X86_REGISTER_SIZEMASK):
		value = icpustate_getes(self);
		break;

	case (X86_REGISTER_SEGMENT_FS & ~X86_REGISTER_SIZEMASK):
		value = icpustate_getfs(self);
		break;

	case (X86_REGISTER_SEGMENT_GS & ~X86_REGISTER_SIZEMASK):
		value = icpustate_getgs(self);
		break;

	default:
		result = libcpu_getreg_gpregs(&self->ics_gpregs, regno, buf, buflen);
		if (result != 0)
			goto done;
		result = libcpu_getreg_irregs(&self->ics_irregs, regno, buf, buflen);
		goto done;
	}
	result = getregval(value, regno, buf, buflen);
#endif /* !__x86_64__ */
done:
	return result;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC IRREGS_NAME(libcpu_setreg_icpustate))(struct icpustate IRREGS_INDIRECTION __restrict IRREGS_SELF,
                                                     unsigned int regno,
                                                     void const *__restrict buf,
                                                     size_t buflen) {
	size_t result;
	uintptr_t value;
	IRREGS_LOADSELF(struct icpustate)
	switch (regno & X86_REGISTER_SIZEMASK) {

	case X86_REGISTER_SIZEMASK_1BYTE:
		result = 1;
		if (buflen < 1)
			goto done;
		value = *(u8 *)buf;
		break;

	case X86_REGISTER_SIZEMASK_2BYTE:
		result = 2;
		if (buflen < 2)
			goto done;
		value = UNALIGNED_GET16((u16 *)buf);
		break;

	case X86_REGISTER_SIZEMASK_4BYTE:
		result = 4;
		if (buflen < 4)
			goto done;
		value = UNALIGNED_GET32((u32 *)buf);
		break;

#ifdef __x86_64__
	case X86_REGISTER_SIZEMASK_8BYTE:
		result = 8;
		if (buflen < 8)
			goto done;
		value = UNALIGNED_GET64((u64 *)buf);
		break;
#endif /* __x86_64__ */

	default: goto nope;
	}

	switch (regno & ~X86_REGISTER_SIZEMASK) {

	case (X86_REGISTER_MISC_PIP & ~X86_REGISTER_SIZEMASK):
		icpustate_setpc(self, value);
		break;

	case (X86_REGISTER_SEGMENT_CS & ~X86_REGISTER_SIZEMASK):
		icpustate_setcs(self, value);
		break;

	case (X86_REGISTER_MISC_PFLAGS & ~X86_REGISTER_SIZEMASK):
		icpustate_setpflags(self, value);
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PSP & ~X86_REGISTER_SIZEMASK):
#ifdef __x86_64__
		icpustate64_setrsp(self, value);
#else /* __x86_64__ */
		*pself = icpustate_setsp_p(self, value);
#endif /* !__x86_64__ */
		break;

	case (X86_REGISTER_SEGMENT_SS & ~X86_REGISTER_SIZEMASK):
		if (!icpustate_trysetss(self, value))
			goto nope;
		break;

#ifndef __x86_64__
	case (X86_REGISTER_SEGMENT_DS & ~X86_REGISTER_SIZEMASK):
		icpustate_setds(self, value);
		break;

	case (X86_REGISTER_SEGMENT_ES & ~X86_REGISTER_SIZEMASK):
		icpustate_setes(self, value);
		break;

	case (X86_REGISTER_SEGMENT_FS & ~X86_REGISTER_SIZEMASK):
		icpustate_setfs(self, value);
		break;

	case (X86_REGISTER_SEGMENT_GS & ~X86_REGISTER_SIZEMASK):
		if (!icpustate_trysetgs(self, value))
			goto nope;
		break;
#endif /* !__x86_64__ */

	default:
nope:
#ifdef __x86_64__
		result = libcpu_setreg_gpregsnsp(&self->ics_gpregs, regno, buf, buflen);
#else /* __x86_64__ */
		result = libcpu_setreg_gpregs(&self->ics_gpregs, regno, buf, buflen);
#endif /* !__x86_64__ */
		break;
	}
done:
	return result;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_scpustate)(struct scpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	size_t result;
#ifdef __x86_64__
	result = libcpu_getreg_irregs(&self->scs_irregs, regno, buf, buflen);
	if (result != 0)
		goto done;
	result = libcpu_getreg_gpregsnsp(&self->scs_gpregs, regno, buf, buflen);
	if (result != 0)
		goto done;
	result = libcpu_getreg_sgregs(&self->scs_sgregs, regno, buf, buflen);
	if (result != 0)
		goto done;
	result = libcpu_getreg_sgbase(&self->scs_sgbase, regno, buf, buflen);
#else /* __x86_64__ */
	uintptr_t value;
	switch (regno & ~X86_REGISTER_SIZEMASK) {

	case (X86_REGISTER_SEGMENT_DS & ~X86_REGISTER_SIZEMASK):
		value = scpustate_getds(self);
		break;

	case (X86_REGISTER_SEGMENT_ES & ~X86_REGISTER_SIZEMASK):
		value = scpustate_getes(self);
		break;

	case (X86_REGISTER_SEGMENT_FS & ~X86_REGISTER_SIZEMASK):
		value = scpustate_getfs(self);
		break;

	case (X86_REGISTER_SEGMENT_GS & ~X86_REGISTER_SIZEMASK):
		value = scpustate_getgs(self);
		break;

	default:
		result = libcpu_getreg_gpregs(&self->scs_gpregs, regno, buf, buflen);
		if (result != 0)
			goto done;
		result = libcpu_getreg_irregs(&self->scs_irregs, regno, buf, buflen);
		goto done;
	}
	result = getregval(value, regno, buf, buflen);
#endif /* !__x86_64__ */
done:
	return result;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC IRREGS_NAME(libcpu_setreg_scpustate))(struct scpustate IRREGS_INDIRECTION __restrict IRREGS_SELF,
                                                     unsigned int regno,
                                                     void const *__restrict buf,
                                                     size_t buflen) {
	size_t result;
	uintptr_t value;
	IRREGS_LOADSELF(struct scpustate)
	switch (regno & X86_REGISTER_SIZEMASK) {

	case X86_REGISTER_SIZEMASK_1BYTE:
		result = 1;
		if (buflen < 1)
			goto done;
		value = *(u8 *)buf;
		break;

	case X86_REGISTER_SIZEMASK_2BYTE:
		result = 2;
		if (buflen < 2)
			goto done;
		value = UNALIGNED_GET16((u16 *)buf);
		break;

	case X86_REGISTER_SIZEMASK_4BYTE:
		result = 4;
		if (buflen < 4)
			goto done;
		value = UNALIGNED_GET32((u32 *)buf);
		break;

#ifdef __x86_64__
	case X86_REGISTER_SIZEMASK_8BYTE:
		result = 8;
		if (buflen < 8)
			goto done;
		value = UNALIGNED_GET64((u64 *)buf);
		break;
#endif /* __x86_64__ */

	default: goto nope;
	}

	switch (regno & ~X86_REGISTER_SIZEMASK) {

	case (X86_REGISTER_MISC_PIP & ~X86_REGISTER_SIZEMASK):
		scpustate_setpc(self, value);
		break;

	case (X86_REGISTER_SEGMENT_CS & ~X86_REGISTER_SIZEMASK):
		scpustate_setcs(self, value);
		break;

	case (X86_REGISTER_MISC_PFLAGS & ~X86_REGISTER_SIZEMASK):
		scpustate_setpflags(self, value);
		break;

	case (X86_REGISTER_GENERAL_PURPOSE_PSP & ~X86_REGISTER_SIZEMASK):
#ifdef __x86_64__
		scpustate64_setrsp(self, value);
#else /* __x86_64__ */
		*pself = scpustate_setsp_p(self, value);
#endif /* !__x86_64__ */
		break;

	case (X86_REGISTER_SEGMENT_SS & ~X86_REGISTER_SIZEMASK):
		if (!scpustate_trysetss(self, value))
			goto nope;
		break;

	case (X86_REGISTER_SEGMENT_DS & ~X86_REGISTER_SIZEMASK):
		scpustate_setds(self, value);
		break;

	case (X86_REGISTER_SEGMENT_ES & ~X86_REGISTER_SIZEMASK):
		scpustate_setes(self, value);
		break;

	case (X86_REGISTER_SEGMENT_FS & ~X86_REGISTER_SIZEMASK):
		scpustate_setfs(self, value);
		break;

	case (X86_REGISTER_SEGMENT_GS & ~X86_REGISTER_SIZEMASK):
		scpustate_setgs(self, value);
		break;

	default:
nope:
#ifdef __x86_64__
		result = libcpu_setreg_gpregsnsp(&self->scs_gpregs, regno, buf, buflen);
		if (result != 0)
			goto done;
		result = libcpu_setreg_sgbase(&self->scs_sgbase, regno, buf, buflen);
#else /* __x86_64__ */
		result = libcpu_setreg_gpregs(&self->scs_gpregs, regno, buf, buflen);
#endif /* !__x86_64__ */
		break;
	}
done:
	return result;
}

#endif /* __KERNEL__ */





DEFINE_PUBLIC_ALIAS(getreg_gpregs, libcpu_getreg_gpregs);
DEFINE_PUBLIC_ALIAS(setreg_gpregs, libcpu_setreg_gpregs);
DEFINE_PUBLIC_ALIAS(getreg_sgregs, libcpu_getreg_sgregs);
DEFINE_PUBLIC_ALIAS(setreg_sgregs, libcpu_setreg_sgregs);
DEFINE_PUBLIC_ALIAS(getreg_coregs, libcpu_getreg_coregs);
DEFINE_PUBLIC_ALIAS(setreg_coregs, libcpu_setreg_coregs);
DEFINE_PUBLIC_ALIAS(getreg_drregs, libcpu_getreg_drregs);
DEFINE_PUBLIC_ALIAS(setreg_drregs, libcpu_setreg_drregs);
DEFINE_PUBLIC_ALIAS(getreg_ucpustate, libcpu_getreg_ucpustate);
DEFINE_PUBLIC_ALIAS(setreg_ucpustate, libcpu_setreg_ucpustate);
DEFINE_PUBLIC_ALIAS(getreg_lcpustate, libcpu_getreg_lcpustate);
DEFINE_PUBLIC_ALIAS(setreg_lcpustate, libcpu_setreg_lcpustate);
DEFINE_PUBLIC_ALIAS(getreg_kcpustate, libcpu_getreg_kcpustate);
DEFINE_PUBLIC_ALIAS(setreg_kcpustate, libcpu_setreg_kcpustate);
DEFINE_PUBLIC_ALIAS(getreg_fcpustate, libcpu_getreg_fcpustate);
DEFINE_PUBLIC_ALIAS(setreg_fcpustate, libcpu_setreg_fcpustate);
DEFINE_PUBLIC_ALIAS(getreg_sfpuenv, libcpu_getreg_sfpuenv);
DEFINE_PUBLIC_ALIAS(setreg_sfpuenv, libcpu_setreg_sfpuenv);
DEFINE_PUBLIC_ALIAS(getreg_sfpustate, libcpu_getreg_sfpustate);
DEFINE_PUBLIC_ALIAS(setreg_sfpustate, libcpu_setreg_sfpustate);
DEFINE_PUBLIC_ALIAS(getreg_xfpustate, libcpu_getreg_xfpustate);
DEFINE_PUBLIC_ALIAS(setreg_xfpustate, libcpu_setreg_xfpustate);
#ifdef __x86_64__
DEFINE_PUBLIC_ALIAS(getreg_gpregsnsp, libcpu_getreg_gpregsnsp);
DEFINE_PUBLIC_ALIAS(setreg_gpregsnsp, libcpu_setreg_gpregsnsp);
DEFINE_PUBLIC_ALIAS(getreg_sgbase, libcpu_getreg_sgbase);
DEFINE_PUBLIC_ALIAS(setreg_sgbase, libcpu_setreg_sgbase);
#endif /* __x86_64__ */
#if !defined(__KERNEL__) || defined(__INTELLISENSE__)
DEFINE_PUBLIC_ALIAS(getreg_mcontext, libcpu_getreg_mcontext);
DEFINE_PUBLIC_ALIAS(setreg_mcontext, libcpu_setreg_mcontext);
DEFINE_PUBLIC_ALIAS(getreg_ucontext, libcpu_getreg_ucontext);
DEFINE_PUBLIC_ALIAS(setreg_ucontext, libcpu_setreg_ucontext);
#endif /* !__KERNEL__ || __INTELLISENSE__ */
#if defined(__KERNEL__) || defined(__INTELLISENSE__)
DEFINE_PUBLIC_ALIAS(getreg_irregs, libcpu_getreg_irregs);
DEFINE_PUBLIC_ALIAS(IRREGS_NAME(setreg_irregs), IRREGS_NAME(libcpu_setreg_irregs));
DEFINE_PUBLIC_ALIAS(getreg_icpustate, libcpu_getreg_icpustate);
DEFINE_PUBLIC_ALIAS(IRREGS_NAME(setreg_icpustate), IRREGS_NAME(libcpu_setreg_icpustate));
DEFINE_PUBLIC_ALIAS(getreg_scpustate, libcpu_getreg_scpustate);
DEFINE_PUBLIC_ALIAS(IRREGS_NAME(setreg_scpustate), IRREGS_NAME(libcpu_setreg_scpustate));
#endif /* __KERNEL__ || __INTELLISENSE__ */

#undef IRREGS_NAME
#undef IRREGS_INDIRECTION
#undef IRREGS_SELF
#undef IRREGS_LOADSELF

DECL_END

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */

#endif /* !GUARD_LIBCPUSTATE_ARCH_I386_REGISTER_C */
