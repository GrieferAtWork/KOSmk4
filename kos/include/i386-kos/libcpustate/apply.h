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
#ifndef _I386_KOS_LIBCPUSTATE_APPLY_H
#define _I386_KOS_LIBCPUSTATE_APPLY_H 1

#include <bits/types.h>
#include <kos/anno.h>

#include <libcpustate/api.h>

#ifdef __CC__
__DECL_BEGIN

struct ucpustate;
struct lcpustate;
struct kcpustate;
struct fcpustate;
#ifdef __KERNEL__
struct icpustate;
struct scpustate;
#else /* __KERNEL__ */
struct ucontext;
struct mcontext;
#endif /* !__KERNEL__ */

/* Load the given CPU state and resume execute at its location. */
typedef __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_UCPUSTATE)(struct ucpustate const *__restrict __state);
typedef __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_LCPUSTATE)(struct lcpustate const *__restrict __state);
typedef __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_KCPUSTATE)(struct kcpustate const *__restrict __state);
typedef __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_FCPUSTATE)(struct fcpustate const *__restrict __state);
#ifdef __KERNEL__
typedef __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_ICPUSTATE)(struct icpustate const *__restrict __state);
typedef __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_SCPUSTATE)(struct scpustate const *__restrict __state);
#else /* __KERNEL__ */
typedef __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_UCONTEXT)(struct ucontext const *__restrict __state);
typedef __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW_T(LIBCPUSTATE_CC *PCPU_APPLY_MCONTEXT)(struct mcontext const *__restrict __state);
#endif /* !__KERNEL__ */

#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply_ucpustate)(struct ucpustate const *__restrict __state);
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply_lcpustate)(struct lcpustate const *__restrict __state);
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply_kcpustate)(struct kcpustate const *__restrict __state);
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply_fcpustate)(struct fcpustate const *__restrict __state);
#ifdef __KERNEL__
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply_icpustate)(struct icpustate const *__restrict __state);
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply_scpustate)(struct scpustate const *__restrict __state);
#else /* __KERNEL__ */
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply_ucontext)(struct ucontext const *__restrict __state);
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply_mcontext)(struct mcontext const *__restrict __state);
#endif /* !__KERNEL__ */

#ifdef __cplusplus
extern "C++" {
#ifdef __NO_ASMNAME
__FORCELOCAL __ATTR_ARTIFICIAL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct ucpustate const *__restrict __state) { cpu_apply_ucpustate(__state); }
__FORCELOCAL __ATTR_ARTIFICIAL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct lcpustate const *__restrict __state) { cpu_apply_lcpustate(__state); }
__FORCELOCAL __ATTR_ARTIFICIAL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct kcpustate const *__restrict __state) { cpu_apply_kcpustate(__state); }
__FORCELOCAL __ATTR_ARTIFICIAL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct fcpustate const *__restrict __state) { cpu_apply_fcpustate(__state); }
#ifdef __KERNEL__
__FORCELOCAL __ATTR_ARTIFICIAL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct icpustate const *__restrict __state) { cpu_apply_icpustate(__state); }
__FORCELOCAL __ATTR_ARTIFICIAL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct scpustate const *__restrict __state) { cpu_apply_scpustate(__state); }
#else /* __KERNEL__ */
__FORCELOCAL __ATTR_ARTIFICIAL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct ucontext const *__restrict __state) { cpu_apply_ucontext(__state); }
__FORCELOCAL __ATTR_ARTIFICIAL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct mcontext const *__restrict __state) { cpu_apply_mcontext(__state); }
#endif /* !__KERNEL__ */
#else /* __NO_ASMNAME */
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct ucpustate const *__restrict __state) __ASMNAME("cpu_apply_ucpustate");
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct lcpustate const *__restrict __state) __ASMNAME("cpu_apply_lcpustate");
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct kcpustate const *__restrict __state) __ASMNAME("cpu_apply_kcpustate");
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct fcpustate const *__restrict __state) __ASMNAME("cpu_apply_fcpustate");
#ifdef __KERNEL__
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct icpustate const *__restrict __state) __ASMNAME("cpu_apply_icpustate");
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct scpustate const *__restrict __state) __ASMNAME("cpu_apply_scpustate");
#else /* __KERNEL__ */
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct ucontext const *__restrict __state) __ASMNAME("cpu_apply_ucontext");
LIBCPUSTATE_DECL __ABNORMAL_RETURN __ATTR_NORETURN __ATTR_NONNULL((1)) void __NOTHROW(LIBCPUSTATE_CC cpu_apply)(struct mcontext const *__restrict __state) __ASMNAME("cpu_apply_mcontext");
#endif /* !__KERNEL__ */
#endif /* !__NO_ASMNAME */
}
#endif /* __cplusplus */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_LIBCPUSTATE_APPLY_H */
