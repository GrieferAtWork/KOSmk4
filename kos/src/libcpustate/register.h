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
#ifndef GUARD_LIBCPUSTATE_REGISTER_H
#define GUARD_LIBCPUSTATE_REGISTER_H 1

#include "api.h"
/**/

#include <kos/types.h>

#include <libcpustate/register.h>

DECL_BEGIN

#ifdef LIBCPUSTATE_HAVE_UCPUSTATE
INTDEF WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_get_ucpustate)(struct ucpustate const *__restrict state, cpu_regno_t regno,
                                              void *__restrict buf, size_t buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_ucpustate_p)(struct ucpustate **__restrict __p_state, cpu_regno_t regno,
                                                void const *__restrict buf, size_t buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE */
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_ucpustate)(struct ucpustate *__restrict state, cpu_regno_t regno,
                                              void const *__restrict buf, size_t buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_UCPUSTATE_P_STATE */
#endif /* LIBCPUSTATE_HAVE_UCPUSTATE */

#if defined(LIBCPUSTATE_HAVE_LCPUSTATE) && !defined(LCPUSTATE_ALIAS)
INTDEF WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_get_lcpustate)(struct lcpustate const *__restrict state, cpu_regno_t regno,
                                              void *__restrict buf, size_t buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_lcpustate_p)(struct lcpustate **__restrict __p_state, cpu_regno_t regno,
                                                void const *__restrict buf, size_t buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_lcpustate)(struct lcpustate *__restrict state, cpu_regno_t regno,
                                              void const *__restrict buf, size_t buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_LCPUSTATE_P_STATE */
#endif /* LIBCPUSTATE_HAVE_LCPUSTATE && !LCPUSTATE_ALIAS */

#if defined(LIBCPUSTATE_HAVE_KCPUSTATE) && !defined(KCPUSTATE_ALIAS)
INTDEF WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_get_kcpustate)(struct kcpustate const *__restrict state, cpu_regno_t regno,
                                              void *__restrict buf, size_t buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_kcpustate_p)(struct kcpustate **__restrict __p_state, cpu_regno_t regno,
                                                void const *__restrict buf, size_t buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_kcpustate)(struct kcpustate *__restrict state, cpu_regno_t regno,
                                              void const *__restrict buf, size_t buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_KCPUSTATE_P_STATE */
#endif /* LIBCPUSTATE_HAVE_KCPUSTATE && !KCPUSTATE_ALIAS */

#if defined(LIBCPUSTATE_HAVE_ICPUSTATE) && !defined(ICPUSTATE_ALIAS)
INTDEF WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_get_icpustate)(struct icpustate const *__restrict state, cpu_regno_t regno,
                                              void *__restrict buf, size_t buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_icpustate_p)(struct icpustate **__restrict __p_state, cpu_regno_t regno,
                                                void const *__restrict buf, size_t buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_icpustate)(struct icpustate *__restrict state, cpu_regno_t regno,
                                              void const *__restrict buf, size_t buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_ICPUSTATE_P_STATE */
#endif /* LIBCPUSTATE_HAVE_ICPUSTATE && !ICPUSTATE_ALIAS */

#if defined(LIBCPUSTATE_HAVE_SCPUSTATE) && !defined(SCPUSTATE_ALIAS)
INTDEF WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_get_scpustate)(struct scpustate const *__restrict state, cpu_regno_t regno,
                                              void *__restrict buf, size_t buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_scpustate_p)(struct scpustate **__restrict __p_state, cpu_regno_t regno,
                                                void const *__restrict buf, size_t buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_scpustate)(struct scpustate *__restrict state, cpu_regno_t regno,
                                              void const *__restrict buf, size_t buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_SCPUSTATE_P_STATE */
#endif /* LIBCPUSTATE_HAVE_SCPUSTATE && !SCPUSTATE_ALIAS */

#if defined(LIBCPUSTATE_HAVE_FCPUSTATE) && !defined(FCPUSTATE_ALIAS)
INTDEF WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_get_fcpustate)(struct fcpustate const *__restrict state, cpu_regno_t regno,
                                              void *__restrict buf, size_t buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_fcpustate_p)(struct fcpustate **__restrict __p_state, cpu_regno_t regno,
                                                void const *__restrict buf, size_t buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_fcpustate)(struct fcpustate *__restrict state, cpu_regno_t regno,
                                              void const *__restrict buf, size_t buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_FCPUSTATE_P_STATE */
#endif /* LIBCPUSTATE_HAVE_FCPUSTATE && !FCPUSTATE_ALIAS */

#ifdef LIBCPUSTATE_HAVE_MCONTEXT
INTDEF WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_get_mcontext)(struct mcontext const *__restrict state, cpu_regno_t regno,
                                             void *__restrict buf, size_t buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_mcontext_p)(struct mcontext **__restrict __p_state, cpu_regno_t regno,
                                               void const *__restrict buf, size_t buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE */
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_mcontext)(struct mcontext *__restrict state, cpu_regno_t regno,
                                             void const *__restrict buf, size_t buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_MCONTEXT_P_STATE */
#endif /* LIBCPUSTATE_HAVE_MCONTEXT */

#ifdef LIBCPUSTATE_HAVE_UCONTEXT
INTDEF WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_get_ucontext)(struct ucontext const *__restrict state, cpu_regno_t regno,
                                             void *__restrict buf, size_t buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_ucontext_p)(struct ucontext **__restrict __p_state, cpu_regno_t regno,
                                               void const *__restrict buf, size_t buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE */
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_ucontext)(struct ucontext *__restrict state, cpu_regno_t regno,
                                             void const *__restrict buf, size_t buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_UCONTEXT_P_STATE */
#endif /* LIBCPUSTATE_HAVE_UCONTEXT */

#ifdef LIBCPUSTATE_HAVE_FPUSTATE
INTDEF WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_get_fpustate)(struct fpustate const *__restrict state, cpu_regno_t regno,
                                             void *__restrict buf, size_t buflen);
#ifdef LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_fpustate_p)(struct fpustate **__restrict __p_state, cpu_regno_t regno,
                                               void const *__restrict buf, size_t buflen);
#else /* LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE */
INTDEF NONNULL((1)) size_t
NOTHROW_NCX(CC libcpu_register_set_fpustate)(struct fpustate *__restrict state, cpu_regno_t regno,
                                             void const *__restrict buf, size_t buflen);
#endif /* !LIBCPUSTATE_HAVE_REGISTER_SET_FPUSTATE_P_STATE */
#endif /* LIBCPUSTATE_HAVE_FPUSTATE */



/* Return the size of a given CPU register (in bytes) */
INTDEF WUNUSED ATTR_CONST size_t
NOTHROW_NCX(CC libcpu_register_sizeof)(cpu_regno_t regno);

/* Return the flags of a given CPU register */
INTDEF WUNUSED ATTR_CONST cpu_regno_flags_t
NOTHROW_NCX(CC libcpu_register_flags)(cpu_regno_t regno);

/* Return an arch-specific register constant, given its name
 * @param: isa: Instruction-set-assembly to which the given name belongs
 * @return: CPU_REGISTER_NONE: No such register. */
INTDEF WUNUSED ATTR_PURE NONNULL((2)) cpu_regno_t
NOTHROW_NCX(CC libcpu_register_byname)(instrlen_isa_t isa,
                                       char const *__restrict name,
                                       size_t namelen);

/* Enumerate all register names that are accepted by `register_byname'
 * @return: >= 0: Sum of return values of `cb'
 * @return: <  0: First negative return value of `cb' (enumerate was aborted) */
INTDEF NONNULL((1)) ssize_t
NOTHROW_NCX(CC libcpu_register_listnames)(pregister_listnames_callback_t cb,
                                          void *cookie);


DECL_END

#endif /* !GUARD_LIBCPUSTATE_REGISTER_H */
