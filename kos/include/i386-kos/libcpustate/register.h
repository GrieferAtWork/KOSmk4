/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_LIBCPUSTATE_REGISTER_H
#define _I386_KOS_LIBCPUSTATE_REGISTER_H 1

#include <bits/types.h>

#include <libcpustate/api.h>

__SYSDECL_BEGIN

#ifdef __CC__

struct gpregs;
struct sgregs;
struct coregs;
struct drregs;
struct ucpustate;
struct lcpustate;
struct kcpustate;
struct fcpustate;
struct sfpuenv;
struct sfpustate;
struct xfpustate;
#ifdef __x86_64__
struct gpregsnsp;
struct sgbase;
#endif /* __x86_64__ */
#ifndef __KERNEL__
struct mcontext;
struct ucontext;
#endif /* !__KERNEL__ */

#ifdef __KERNEL__
#ifdef __x86_64__
#define __LIBCPUSTATE_IRREGS_STRUCT_TYPE struct irregs
#else /* __x86_64__ */
#define __LIBCPUSTATE_IRREGS_STRUCT_TYPE struct irregs_kernel
#endif /* !__x86_64__ */
__LIBCPUSTATE_IRREGS_STRUCT_TYPE;
struct icpustate;
struct scpustate;
#endif /* __KERNEL__ */


/* Get/set the value of a given register `regno' (one of `X86_REGISTER_*' from <asm/register.h>)
 * NOTE: When `return > buflen', then
 *       getreg_*: The contents of `buf' are undefined.
 *       setreg_*: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of `X86_REGISTER_*' (from <asm/registers.h>)
 * @return: * :   The required buffer size, or 0 when `name' isn't recognized. */
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_GPREGS)(struct gpregs const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_GPREGS)(struct gpregs *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_SGREGS)(struct sgregs const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_SGREGS)(struct sgregs *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_COREGS)(struct coregs const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_COREGS)(struct coregs *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_DRREGS)(struct drregs const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_DRREGS)(struct drregs *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_UCPUSTATE)(struct ucpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_UCPUSTATE)(struct ucpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_LCPUSTATE)(struct lcpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_LCPUSTATE)(struct lcpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_KCPUSTATE)(struct kcpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_KCPUSTATE)(struct kcpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_FCPUSTATE)(struct fcpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_FCPUSTATE)(struct fcpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_SFPUENV)(struct sfpuenv const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_SFPUENV)(struct sfpuenv *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_SFPUSTATE)(struct sfpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_SFPUSTATE)(struct sfpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_XFPUSTATE)(struct xfpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_XFPUSTATE)(struct xfpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_gpregs)(struct gpregs const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_gpregs)(struct gpregs *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_sgregs)(struct sgregs const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_sgregs)(struct sgregs *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_coregs)(struct coregs const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_coregs)(struct coregs *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_drregs)(struct drregs const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_drregs)(struct drregs *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_ucpustate)(struct ucpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_ucpustate)(struct ucpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_lcpustate)(struct lcpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_lcpustate)(struct lcpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_kcpustate)(struct kcpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_kcpustate)(struct kcpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_fcpustate)(struct fcpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_fcpustate)(struct fcpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_sfpuenv)(struct sfpuenv const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_sfpuenv)(struct sfpuenv *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_sfpustate)(struct sfpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_sfpustate)(struct sfpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_xfpustate)(struct xfpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_xfpustate)(struct xfpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */

#ifdef __x86_64__
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_GPREGSNSP)(struct gpregsnsp const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_GPREGSNSP)(struct gpregsnsp *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_SGBASE)(struct sgbase const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_SGBASE)(struct sgbase *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_gpregsnsp)(struct gpregsnsp const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_gpregsnsp)(struct gpregsnsp *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_sgbase)(struct sgbase const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_sgbase)(struct sgbase *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* __x86_64__ */

#ifndef __KERNEL__
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_MCONTEXT)(struct mcontext const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_MCONTEXT)(struct mcontext *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_UCONTEXT)(struct ucontext const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_UCONTEXT)(struct ucontext *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_mcontext)(struct mcontext const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_mcontext)(struct mcontext *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_ucontext)(struct ucontext const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_ucontext)(struct ucontext *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#else /* !__KERNEL__ */
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_IRREGS)(__LIBCPUSTATE_IRREGS_STRUCT_TYPE const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_ICPUSTATE)(struct icpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PGETREG_SCPUSTATE)(struct scpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
#ifdef __x86_64__
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_IRREGS)(__LIBCPUSTATE_IRREGS_STRUCT_TYPE *__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_ICPUSTATE)(struct icpustate *__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_SCPUSTATE)(struct scpustate *__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
#else /* __x86_64__ */
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_IRREGS_P)(__LIBCPUSTATE_IRREGS_STRUCT_TYPE **__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_ICPUSTATE_P)(struct icpustate **__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
typedef __ATTR_NONNULL_T((1)) __size_t __NOTHROW_NCX_T(LIBCPUSTATE_CC *PSETREG_SCPUSTATE_P)(struct scpustate **__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
#endif /* !__x86_64__ */
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_irregs)(__LIBCPUSTATE_IRREGS_STRUCT_TYPE const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_icpustate)(struct icpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC getreg_scpustate)(struct scpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen);
#ifdef __x86_64__
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_irregs)(__LIBCPUSTATE_IRREGS_STRUCT_TYPE *__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_icpustate)(struct icpustate *__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_scpustate)(struct scpustate *__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
#else /* __x86_64__ */
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_irregs_p)(__LIBCPUSTATE_IRREGS_STRUCT_TYPE **__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_icpustate_p)(struct icpustate **__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
LIBCPUSTATE_DECL __ATTR_NONNULL((1)) __size_t __NOTHROW_NCX(LIBCPUSTATE_CC setreg_scpustate_p)(struct scpustate **__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen);
#endif /* !__x86_64__ */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* __KERNEL__ */



#ifdef __cplusplus
#ifdef LIBCPUSTATE_WANT_PROTOTYPES
extern "C++" {
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct gpregs const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_gpregs,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct gpregs const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),setreg_gpregs,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct sgregs const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_sgregs,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct sgregs *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_sgregs,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct coregs const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_coregs,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct coregs *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_coregs,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct drregs const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_drregs,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct drregs *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_drregs,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct ucpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_ucpustate,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct ucpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_ucpustate,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct lcpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_lcpustate,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct lcpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_lcpustate,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct kcpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_kcpustate,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct kcpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_kcpustate,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct fcpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_fcpustate,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct fcpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_fcpustate,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct sfpuenv const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_sfpuenv,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct sfpuenv *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_sfpuenv,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct sfpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_sfpustate,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct sfpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_sfpustate,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct xfpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_xfpustate,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct xfpustate *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_xfpustate,(__self,__regno,__buf,__buflen))
#ifdef __x86_64__
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct gpregsnsp const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_gpregsnsp,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct gpregsnsp *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_gpregsnsp,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct sgbase const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_sgbase,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct sgbase *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_sgbase,(__self,__regno,__buf,__buflen))
#endif /* __x86_64__ */
#ifndef __KERNEL__
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct mcontext const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_mcontext,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct mcontext *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_mcontext,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct ucontext const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_ucontext,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct ucontext *__restrict __self, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_ucontext,(__self,__regno,__buf,__buflen))
#else /* !__KERNEL__ */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(__LIBCPUSTATE_IRREGS_STRUCT_TYPE const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_irregs,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct icpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_icpustate,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,getreg,(struct scpustate const *__restrict __self, unsigned int __regno, void *__restrict __buf, __size_t __buflen),getreg_scpustate,(__self,__regno,__buf,__buflen))
#ifdef __x86_64__
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(__LIBCPUSTATE_IRREGS_STRUCT_TYPE *__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_irregs,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct icpustate *__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_icpustate,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct scpustate *__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_scpustate,(__self,__regno,__buf,__buflen))
#else /* __x86_64__ */
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(__LIBCPUSTATE_IRREGS_STRUCT_TYPE **__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_irregs_p,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct icpustate **__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_icpustate_p,(__self,__regno,__buf,__buflen))
__COMPILER_REDIRECT(LIBCPUSTATE_DECL,__ATTR_NONNULL((1)),__size_t,__NOTHROW_NCX,LIBCPUSTATE_CC,setreg,(struct scpustate **__restrict __pself, unsigned int __regno, void const *__restrict __buf, __size_t __buflen),setreg_scpustate_p,(__self,__regno,__buf,__buflen))
#endif /* !__x86_64__ */
#endif /* __KERNEL__ */
}
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */
#endif /* __cplusplus */


#ifdef __KERNEL__
#undef __LIBCPUSTATE_IRREGS_STRUCT_TYPE
#endif /* __KERNEL__ */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_LIBCPUSTATE_REGISTER_H */
