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
#ifndef _ARM_KOS_LIBUNWIND_ASM_FEATURES_H
#define _ARM_KOS_LIBUNWIND_ASM_FEATURES_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#define LIBUNWIND_HAVE_GETSETREG_LCPUSTATE
#define LIBUNWIND_HAVE_GETSETREG_UCPUSTATE
#define LIBUNWIND_HAVE_GETSETREG_KCPUSTATE /* alias! */
#define LIBUNWIND_HAVE_GETSETREG_ICPUSTATE /* alias! */
#define LIBUNWIND_HAVE_GETSETREG_SCPUSTATE /* alias! */
#define LIBUNWIND_HAVE_GETSETREG_FCPUSTATE
#ifndef __KERNEL__
#define LIBUNWIND_HAVE_GETSETREG_MCONTEXT
#define LIBUNWIND_HAVE_GETSETREG_UCONTEXT
#endif /* !__KERNEL__ */
#define LIBUNWIND_HAVE_GETSETREG_FPUSTATE

/* Feature flag: we want special support for ".ARM.exidx" sections. */
#define LIBUNWIND_HAVE_ARM_EXIDX

/* Feature flag: expose the arm-specific `_Unwind_VRS_*' API */
#define LIBUNWIND_HAVE_UNWIND_VRS

#endif /* !_ARM_KOS_LIBUNWIND_ASM_FEATURES_H */
