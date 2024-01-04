/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_LIBUNWIND_ASM_FEATURES_H
#define _I386_KOS_LIBUNWIND_ASM_FEATURES_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#define LIBUNWIND_HAVE_GETSETREG_UCPUSTATE
#define LIBUNWIND_HAVE_GETSETREG_LCPUSTATE
#define LIBUNWIND_HAVE_GETSETREG_KCPUSTATE
#define LIBUNWIND_HAVE_GETSETREG_FCPUSTATE
#ifdef __KERNEL__
#define LIBUNWIND_HAVE_GETSETREG_ICPUSTATE
#define LIBUNWIND_HAVE_GETSETREG_SCPUSTATE
#ifndef __x86_64__
#define LIBUNWIND_HAVE_GETSETREG_ICPUSTATE_P
#define LIBUNWIND_HAVE_GETSETREG_SCPUSTATE_P
#endif /* !__x86_64__ */
#else /* __KERNEL__ */
#define LIBUNWIND_HAVE_GETSETREG_MCONTEXT
#define LIBUNWIND_HAVE_GETSETREG_UCONTEXT
#endif /* !__KERNEL__ */
#define LIBUNWIND_HAVE_GETSETREG_FPUSTATE


/* Because x86_64 uses different register indices for x86_64, we
 * need a wrapper mechanism for converting i386 register indices
 * to x86_64, and use this mechanism when unwind-ing 32-bit user
 * modules. */
#if defined(__x86_64__) && defined(__KERNEL__)
/* Only provided for kernel-space (for now); User-space support
 * could also be provided, but isn't needed and would  therefor
 * only add unnecessary bloat!
 * Even in kernel-space, we technically only need it for debug
 * support in the  builtin debugger, but  no mandatory  system
 * features. */
#define LIBUNWIND_HAVE_GETSETREG_COMPAT
#endif /* __x86_64__ && __KERNEL__ */

#endif /* !_I386_KOS_LIBUNWIND_ASM_FEATURES_H */
