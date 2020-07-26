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
#ifndef GUARD_LIBCPUSTATE_ARCH_I386_REGISTER_H
#define GUARD_LIBCPUSTATE_ARCH_I386_REGISTER_H 1

#include "../../api.h"
/**/

#include <hybrid/host.h>
#include <kos/types.h>

#include <kos/kernel/cpu-state.h>

#include <libcpustate/register.h>

#ifndef __KERNEL__
#include <bits/mcontext.h> /* struct mcontext */
#include <bits/ucontext.h> /* struct ucontext */
#endif /* !__KERNEL__ */

#ifdef __x86_64__
#define LIBCPUSTATE_IRREGS_STRUCT_TYPE struct irregs
#else /* __x86_64__ */
#define LIBCPUSTATE_IRREGS_STRUCT_TYPE struct irregs_kernel
#endif /* !__x86_64__ */


DECL_BEGIN

/* Get/set the value of a given register `regno' (one of `X86_REGISTER_*' from <asm/register.h>)
 * NOTE: When `return > buflen', then
 *       getreg_*: The contents of `buf' are undefined.
 *       setreg_*: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of `X86_REGISTER_*' (from <asm/registers.h>) or one of `X86_DBGREGISTER_*'
 * @return: * :   The required buffer size, or 0 when `name' isn't recognized. */
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_gpregs)(struct gpregs const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_gpregs)(struct gpregs *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_sgregs)(struct sgregs const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_sgregs)(struct sgregs *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_coregs)(struct coregs const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_coregs)(struct coregs *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_drregs)(struct drregs const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_drregs)(struct drregs *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_ucpustate)(struct ucpustate const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_ucpustate)(struct ucpustate *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_lcpustate)(struct lcpustate const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_lcpustate)(struct lcpustate *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_kcpustate)(struct kcpustate const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_kcpustate)(struct kcpustate *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_fcpustate)(struct fcpustate const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_fcpustate)(struct fcpustate *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_sfpuenv)(struct sfpuenv const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_sfpuenv)(struct sfpuenv *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_sfpustate)(struct sfpustate const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_sfpustate)(struct sfpustate *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_xfpustate)(struct xfpustate const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_xfpustate)(struct xfpustate *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
#ifdef __x86_64__
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_gpregsnsp)(struct gpregsnsp const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_gpregsnsp)(struct gpregsnsp *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_sgbase)(struct sgbase const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_sgbase)(struct sgbase *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
#endif /* __x86_64__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_mcontext)(struct mcontext const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_mcontext)(struct mcontext *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_ucontext)(struct ucontext const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_ucontext)(struct ucontext *__restrict self, unsigned int regno, void const *__restrict buf, size_t buflen);
#else /* !__KERNEL__ */
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_irregs)(LIBCPUSTATE_IRREGS_STRUCT_TYPE const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_irregs_p)(LIBCPUSTATE_IRREGS_STRUCT_TYPE **__restrict pself, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_icpustate)(struct icpustate const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_icpustate_p)(struct icpustate **__restrict pself, unsigned int regno, void const *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_getreg_scpustate)(struct scpustate const *__restrict self, unsigned int regno, void *__restrict buf, size_t buflen);
INTDEF NONNULL((1)) size_t NOTHROW_NCX(CC libcpu_setreg_scpustate_p)(struct scpustate **__restrict pself, unsigned int regno, void const *__restrict buf, size_t buflen);
#endif /* __KERNEL__ */

DECL_END

#endif /* !GUARD_LIBCPUSTATE_ARCH_I386_REGISTER_H */
