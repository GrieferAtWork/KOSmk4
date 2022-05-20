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
#ifndef _I386_KOS_LIBREGDUMP_CPU_STATE_H
#define _I386_KOS_LIBREGDUMP_CPU_STATE_H 1

#include <libregdump/api.h>
#include <libregdump/printer.h>

/* Print a human-readable dump of all of the registers within the given cpu-state/context. */

#ifdef __CC__
__DECL_BEGIN

struct regdump_printer;
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

/* Dump the contents of the given register state in a human-readable format.
 * @return: * : The usual pformatprinter return value rules... */
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_UCPUSTATE)(struct regdump_printer *__restrict __self, struct ucpustate const *__restrict __data);
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_LCPUSTATE)(struct regdump_printer *__restrict __self, struct lcpustate const *__restrict __data);
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_KCPUSTATE)(struct regdump_printer *__restrict __self, struct kcpustate const *__restrict __data);
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_FCPUSTATE)(struct regdump_printer *__restrict __self, struct fcpustate const *__restrict __data);
#ifdef __KERNEL__
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_ICPUSTATE)(struct regdump_printer *__restrict __self, struct icpustate const *__restrict __data);
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_SCPUSTATE)(struct regdump_printer *__restrict __self, struct scpustate const *__restrict __data);
#else /* __KERNEL__ */
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_UCONTEXT)(struct regdump_printer *__restrict __self, struct ucontext const *__restrict __data);
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_MCONTEXT)(struct regdump_printer *__restrict __self, struct mcontext const *__restrict __data);
#endif /* !__KERNEL__ */

#ifdef LIBREGDUMP_WANT_PROTOTYPES
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_ucpustate(struct regdump_printer *__restrict __self, struct ucpustate const *__restrict __data);
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_lcpustate(struct regdump_printer *__restrict __self, struct lcpustate const *__restrict __data);
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_kcpustate(struct regdump_printer *__restrict __self, struct kcpustate const *__restrict __data);
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_fcpustate(struct regdump_printer *__restrict __self, struct fcpustate const *__restrict __data);
#ifdef __KERNEL__
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_icpustate(struct regdump_printer *__restrict __self, struct icpustate const *__restrict __data);
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_scpustate(struct regdump_printer *__restrict __self, struct scpustate const *__restrict __data);
#else /* __KERNEL__ */
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_ucontext(struct regdump_printer *__restrict __self, struct ucontext const *__restrict __data);
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_mcontext(struct regdump_printer *__restrict __self, struct mcontext const *__restrict __data);
#endif /* !__KERNEL__ */

#ifdef __cplusplus
extern "C++" {
#ifdef __NO_ASMNAME
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct ucpustate const *__restrict __data) { return regdump_ucpustate(__self, __data); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct lcpustate const *__restrict __data) { return regdump_lcpustate(__self, __data); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct kcpustate const *__restrict __data) { return regdump_kcpustate(__self, __data); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct fcpustate const *__restrict __data) { return regdump_fcpustate(__self, __data); }
#ifdef __KERNEL__
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct icpustate const *__restrict __data) { return regdump_icpustate(__self, __data); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct scpustate const *__restrict __data) { return regdump_scpustate(__self, __data); }
#else /* __KERNEL__ */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct ucontext const *__restrict __data) { return regdump_ucontext(__self, __data); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct mcontext const *__restrict __data) { return regdump_mcontext(__self, __data); }
#endif /* !__KERNEL__ */
#else /* __NO_ASMNAME */
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct ucpustate const *__restrict __data) __ASMNAME("regdump_ucpustate");
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct lcpustate const *__restrict __data) __ASMNAME("regdump_lcpustate");
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct kcpustate const *__restrict __data) __ASMNAME("regdump_kcpustate");
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct fcpustate const *__restrict __data) __ASMNAME("regdump_fcpustate");
#ifdef __KERNEL__
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct icpustate const *__restrict __data) __ASMNAME("regdump_icpustate");
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct scpustate const *__restrict __data) __ASMNAME("regdump_scpustate");
#else /* __KERNEL__ */
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct ucontext const *__restrict __data) __ASMNAME("regdump_ucontext");
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump(struct regdump_printer *__restrict __self, struct mcontext const *__restrict __data) __ASMNAME("regdump_mcontext");
#endif /* !__KERNEL__ */
#endif /* !__NO_ASMNAME */
}
#endif /* __cplusplus */
#endif /* LIBREGDUMP_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_LIBREGDUMP_CPU_STATE_H */
