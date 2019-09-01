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
#ifndef _I386_KOS_LIBCPUSTATE_APPLY_H
#define _I386_KOS_LIBCPUSTATE_APPLY_H 1

#include <libcpustate/api.h>
#include <bits/types.h>

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
typedef __ATTR_NORETURN void (LIBCPUSTATE_CC *PCPU_APPLY_UCPUSTATE)(struct ucpustate *__restrict __state);
typedef __ATTR_NORETURN void (LIBCPUSTATE_CC *PCPU_APPLY_LCPUSTATE)(struct lcpustate *__restrict __state);
typedef __ATTR_NORETURN void (LIBCPUSTATE_CC *PCPU_APPLY_KCPUSTATE)(struct kcpustate *__restrict __state);
typedef __ATTR_NORETURN void (LIBCPUSTATE_CC *PCPU_APPLY_FCPUSTATE)(struct fcpustate *__restrict __state);
#ifdef __KERNEL__
typedef __ATTR_NORETURN void (LIBCPUSTATE_CC *PCPU_APPLY_ICPUSTATE)(struct icpustate *__restrict __state);
typedef __ATTR_NORETURN void (LIBCPUSTATE_CC *PCPU_APPLY_SCPUSTATE)(struct scpustate *__restrict __state);
#else /* __KERNEL__ */
typedef __ATTR_NORETURN void (LIBCPUSTATE_CC *PCPU_APPLY_UCONTEXT)(struct ucontext *__restrict __state);
typedef __ATTR_NORETURN void (LIBCPUSTATE_CC *PCPU_APPLY_MCONTEXT)(struct mcontext *__restrict __state);
#endif /* !__KERNEL__ */

#ifdef LIBCPUSTATE_WANT_PROTOTYPES
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply_ucpustate(struct ucpustate *__restrict __state);
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply_lcpustate(struct lcpustate *__restrict __state);
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply_kcpustate(struct kcpustate *__restrict __state);
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply_fcpustate(struct fcpustate *__restrict __state);
#ifdef __KERNEL__
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply_icpustate(struct icpustate *__restrict __state);
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply_scpustate(struct scpustate *__restrict __state);
#else /* __KERNEL__ */
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply_ucontext(struct ucontext *__restrict __state);
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply_mcontext(struct mcontext *__restrict __state);
#endif /* !__KERNEL__ */

#ifdef __cplusplus
extern "C++" {
#ifdef __NO_ASMNAME
__FORCELOCAL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct ucpustate *__restrict __state) { cpu_apply_ucpustate(__state); }
__FORCELOCAL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct lcpustate *__restrict __state) { cpu_apply_lcpustate(__state); }
__FORCELOCAL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct kcpustate *__restrict __state) { cpu_apply_kcpustate(__state); }
__FORCELOCAL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct fcpustate *__restrict __state) { cpu_apply_fcpustate(__state); }
#ifdef __KERNEL__
__FORCELOCAL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct icpustate *__restrict __state) { cpu_apply_icpustate(__state); }
__FORCELOCAL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct scpustate *__restrict __state) { cpu_apply_scpustate(__state); }
#else /* __KERNEL__ */
__FORCELOCAL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct ucontext *__restrict __state) { cpu_apply_ucontext(__state); }
__FORCELOCAL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct mcontext *__restrict __state) { cpu_apply_mcontext(__state); }
#endif /* !__KERNEL__ */
#else /* __NO_ASMNAME */
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct ucpustate *__restrict __state) __ASMNAME("cpu_apply_ucpustate");
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct lcpustate *__restrict __state) __ASMNAME("cpu_apply_lcpustate");
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct kcpustate *__restrict __state) __ASMNAME("cpu_apply_kcpustate");
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct fcpustate *__restrict __state) __ASMNAME("cpu_apply_fcpustate");
#ifdef __KERNEL__
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct icpustate *__restrict __state) __ASMNAME("cpu_apply_icpustate");
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct scpustate *__restrict __state) __ASMNAME("cpu_apply_scpustate");
#else /* __KERNEL__ */
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct ucontext *__restrict __state) __ASMNAME("cpu_apply_ucontext");
LIBCPUSTATE_DECL __ATTR_NORETURN void LIBCPUSTATE_CC cpu_apply(struct mcontext *__restrict __state) __ASMNAME("cpu_apply_mcontext");
#endif /* !__KERNEL__ */
#endif /* !__NO_ASMNAME */
}
#endif /* __cplusplus */
#endif /* LIBCPUSTATE_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBCPUSTATE_APPLY_H */
