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
#ifndef GUARD_LIBCPUSTATE_ARCH_I386_REGISTER_C
#define GUARD_LIBCPUSTATE_ARCH_I386_REGISTER_C 1

#include "../../api.h"
/**/
#include <hybrid/unaligned.h>

#include <asm/registers-compat.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/types.h>
#include <kos/types.h>

#include <libcpustate/register.h>

#include "register.h"

DECL_BEGIN

/* Get/set the value of a given register `regno' (one of `X86_REGISTER_*' from <asm/register.h>)
 * NOTE: When `return > buflen', then
 *       getreg_*: The contents of `buf' are undefined.
 *       setreg_*: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of `X86_REGISTER_*' (from <asm/registers.h>) or one of `X86_DBGREGISTER_*'
 * @return: * :   The required buffer size, or 0 when `name' isn't recognized. */
INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_gpregs)(struct gpregs const *__restrict self, unsigned int regno,
                                     void *__restrict buf, size_t buflen) {
	uintptr_t value;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_GENERAL_PURPOSE)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case X86_REGISTER_GENERAL_PURPOSE_PAX & X86_REGISTER_IDMASK: value = self->gp_pax; break;
	case X86_REGISTER_GENERAL_PURPOSE_PCX & X86_REGISTER_IDMASK: value = self->gp_pcx; break;
	case X86_REGISTER_GENERAL_PURPOSE_PDX & X86_REGISTER_IDMASK: value = self->gp_pdx; break;
	case X86_REGISTER_GENERAL_PURPOSE_PBX & X86_REGISTER_IDMASK: value = self->gp_pbx; break;
	case X86_REGISTER_GENERAL_PURPOSE_PSP & X86_REGISTER_IDMASK: value = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE) ? (self->gp_pax >> 8) : self->gp_psp; break;
	case X86_REGISTER_GENERAL_PURPOSE_PBP & X86_REGISTER_IDMASK: value = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE) ? (self->gp_pcx >> 8) : self->gp_pbp; break;
	case X86_REGISTER_GENERAL_PURPOSE_PSI & X86_REGISTER_IDMASK: value = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE) ? (self->gp_pdx >> 8) : self->gp_psi; break;
	case X86_REGISTER_GENERAL_PURPOSE_PDI & X86_REGISTER_IDMASK: value = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE) ? (self->gp_pbx >> 8) : self->gp_pdi; break;
#ifdef __x86_64__
	case X86_REGISTER_GENERAL_PURPOSE_P8 & X86_REGISTER_IDMASK:  value = self->gp_r8; break;
	case X86_REGISTER_GENERAL_PURPOSE_P9 & X86_REGISTER_IDMASK:  value = self->gp_r9; break;
	case X86_REGISTER_GENERAL_PURPOSE_P10 & X86_REGISTER_IDMASK: value = self->gp_r10; break;
	case X86_REGISTER_GENERAL_PURPOSE_P11 & X86_REGISTER_IDMASK: value = self->gp_r11; break;
	case X86_REGISTER_GENERAL_PURPOSE_P12 & X86_REGISTER_IDMASK: value = self->gp_r12; break;
	case X86_REGISTER_GENERAL_PURPOSE_P13 & X86_REGISTER_IDMASK: value = self->gp_r13; break;
	case X86_REGISTER_GENERAL_PURPOSE_P14 & X86_REGISTER_IDMASK: value = self->gp_r14; break;
	case X86_REGISTER_GENERAL_PURPOSE_P15 & X86_REGISTER_IDMASK: value = self->gp_r15; break;
	case X86_REGISTER_GENERAL_PURPOSE_SPL & X86_REGISTER_IDMASK: value = self->gp_psp; break;
	case X86_REGISTER_GENERAL_PURPOSE_BPL & X86_REGISTER_IDMASK: value = self->gp_pbp; break;
	case X86_REGISTER_GENERAL_PURPOSE_SIL & X86_REGISTER_IDMASK: value = self->gp_psi; break;
	case X86_REGISTER_GENERAL_PURPOSE_DIL & X86_REGISTER_IDMASK: value = self->gp_pdi; break;
#endif /* __x86_64__ */

	default:
nope:
		return 0;
	}
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

	default: goto nope;
	}
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_gpregs)(struct gpregs *__restrict self, unsigned int regno,
                                     void const *__restrict buf, size_t buflen) {
	void *pvalue;
	if ((regno & X86_REGISTER_CLASSMASK) != X86_REGISTER_GENERAL_PURPOSE)
		goto nope;
	switch (regno & X86_REGISTER_IDMASK) {

	case X86_REGISTER_GENERAL_PURPOSE_PAX & X86_REGISTER_IDMASK: pvalue = &self->gp_pax; break;
	case X86_REGISTER_GENERAL_PURPOSE_PCX & X86_REGISTER_IDMASK: pvalue = &self->gp_pcx; break;
	case X86_REGISTER_GENERAL_PURPOSE_PDX & X86_REGISTER_IDMASK: pvalue = &self->gp_pdx; break;
	case X86_REGISTER_GENERAL_PURPOSE_PBX & X86_REGISTER_IDMASK: pvalue = &self->gp_pbx; break;
	case X86_REGISTER_GENERAL_PURPOSE_PSP & X86_REGISTER_IDMASK: pvalue = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE) ? (void *)((byte_t *)&self->gp_pax + 1) : (void *)&self->gp_psp; break;
	case X86_REGISTER_GENERAL_PURPOSE_PBP & X86_REGISTER_IDMASK: pvalue = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE) ? (void *)((byte_t *)&self->gp_pcx + 1) : (void *)&self->gp_pbp; break;
	case X86_REGISTER_GENERAL_PURPOSE_PSI & X86_REGISTER_IDMASK: pvalue = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE) ? (void *)((byte_t *)&self->gp_pdx + 1) : (void *)&self->gp_psi; break;
	case X86_REGISTER_GENERAL_PURPOSE_PDI & X86_REGISTER_IDMASK: pvalue = ((regno & X86_REGISTER_SIZEMASK) == X86_REGISTER_SIZEMASK_1BYTE) ? (void *)((byte_t *)&self->gp_pbx + 1) : (void *)&self->gp_pdi; break;
#ifdef __x86_64__
	case X86_REGISTER_GENERAL_PURPOSE_P8 & X86_REGISTER_IDMASK:  pvalue = &self->gp_r8; break;
	case X86_REGISTER_GENERAL_PURPOSE_P9 & X86_REGISTER_IDMASK:  pvalue = &self->gp_r9; break;
	case X86_REGISTER_GENERAL_PURPOSE_P10 & X86_REGISTER_IDMASK: pvalue = &self->gp_r10; break;
	case X86_REGISTER_GENERAL_PURPOSE_P11 & X86_REGISTER_IDMASK: pvalue = &self->gp_r11; break;
	case X86_REGISTER_GENERAL_PURPOSE_P12 & X86_REGISTER_IDMASK: pvalue = &self->gp_r12; break;
	case X86_REGISTER_GENERAL_PURPOSE_P13 & X86_REGISTER_IDMASK: pvalue = &self->gp_r13; break;
	case X86_REGISTER_GENERAL_PURPOSE_P14 & X86_REGISTER_IDMASK: pvalue = &self->gp_r14; break;
	case X86_REGISTER_GENERAL_PURPOSE_P15 & X86_REGISTER_IDMASK: pvalue = &self->gp_r15; break;
	case X86_REGISTER_GENERAL_PURPOSE_SPL & X86_REGISTER_IDMASK: pvalue = &self->gp_psp; break;
	case X86_REGISTER_GENERAL_PURPOSE_BPL & X86_REGISTER_IDMASK: pvalue = &self->gp_pbp; break;
	case X86_REGISTER_GENERAL_PURPOSE_SIL & X86_REGISTER_IDMASK: pvalue = &self->gp_psi; break;
	case X86_REGISTER_GENERAL_PURPOSE_DIL & X86_REGISTER_IDMASK: pvalue = &self->gp_pdi; break;
#endif /* __x86_64__ */

	default:
nope:
		return 0;
	}
	switch (regno & X86_REGISTER_SIZEMASK) {

	case X86_REGISTER_SIZEMASK_1BYTE:
		if (buflen == 1)
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

	default: goto nope;
	}
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_sgregs)(struct sgregs const *__restrict self, unsigned int regno,
                                     void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_sgregs)(struct sgregs *__restrict self, unsigned int regno,
                                     void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_coregs)(struct coregs const *__restrict self, unsigned int regno,
                                     void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_coregs)(struct coregs *__restrict self, unsigned int regno,
                                     void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_drregs)(struct drregs const *__restrict self, unsigned int regno,
                                     void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_drregs)(struct drregs *__restrict self, unsigned int regno,
                                     void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_ucpustate)(struct ucpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_ucpustate)(struct ucpustate *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_lcpustate)(struct lcpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_lcpustate)(struct lcpustate *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_kcpustate)(struct kcpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_kcpustate)(struct kcpustate *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_fcpustate)(struct fcpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_fcpustate)(struct fcpustate *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_sfpuenv)(struct sfpuenv const *__restrict self, unsigned int regno,
                                      void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_sfpuenv)(struct sfpuenv *__restrict self, unsigned int regno,
                                      void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_sfpustate)(struct sfpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_sfpustate)(struct sfpustate *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_xfpustate)(struct xfpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_xfpustate)(struct xfpustate *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

#ifdef __x86_64__
INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_gpregsnsp)(struct gpregsnsp const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_gpregsnsp)(struct gpregsnsp *__restrict self, unsigned int regno,
                                        void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_sgbase)(struct sgbase const *__restrict self, unsigned int regno,
                                     void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_sgbase)(struct sgbase *__restrict self, unsigned int regno,
                                     void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

#endif /* __x86_64__ */
#ifndef __KERNEL__
INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_mcontext)(struct mcontext const *__restrict self, unsigned int regno,
                                       void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_mcontext)(struct mcontext *__restrict self, unsigned int regno,
                                       void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_ucontext)(struct ucontext const *__restrict self, unsigned int regno,
                                       void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_ucontext)(struct ucontext *__restrict self, unsigned int regno,
                                       void const *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

#else /* !__KERNEL__ */

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_irregs)(LIBCPUSTATE_IRREGS_STRUCT_TYPE const *__restrict self, unsigned int regno,
                                     void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_irregs_p)(LIBCPUSTATE_IRREGS_STRUCT_TYPE **__restrict pself, unsigned int regno,
                                       void const *__restrict buf, size_t buflen) {
	(void)pself;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_icpustate)(struct icpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_icpustate_p)(struct icpustate **__restrict pself, unsigned int regno,
                                          void const *__restrict buf, size_t buflen) {
	(void)pself;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_getreg_scpustate)(struct scpustate const *__restrict self, unsigned int regno,
                                        void *__restrict buf, size_t buflen) {
	(void)self;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
}

INTERN NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_setreg_scpustate_p)(struct scpustate **__restrict pself, unsigned int regno,
                                          void const *__restrict buf, size_t buflen) {
	(void)pself;
	(void)regno;
	(void)buf;
	(void)buflen;
	/* TODO */
	return 0;
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
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(getreg_mcontext, libcpu_getreg_mcontext);
DEFINE_PUBLIC_ALIAS(setreg_mcontext, libcpu_setreg_mcontext);
DEFINE_PUBLIC_ALIAS(getreg_ucontext, libcpu_getreg_ucontext);
DEFINE_PUBLIC_ALIAS(setreg_ucontext, libcpu_setreg_ucontext);
#else /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(getreg_irregs, libcpu_getreg_irregs);
DEFINE_PUBLIC_ALIAS(setreg_irregs_p, libcpu_setreg_irregs_p);
DEFINE_PUBLIC_ALIAS(getreg_icpustate, libcpu_getreg_icpustate);
DEFINE_PUBLIC_ALIAS(setreg_icpustate_p, libcpu_setreg_icpustate_p);
DEFINE_PUBLIC_ALIAS(getreg_scpustate, libcpu_getreg_scpustate);
DEFINE_PUBLIC_ALIAS(setreg_scpustate_p, libcpu_setreg_scpustate_p);
#endif /* __KERNEL__ */

DECL_END

#endif /* !GUARD_LIBCPUSTATE_ARCH_I386_REGISTER_C */
