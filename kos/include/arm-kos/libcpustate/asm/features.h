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
#ifndef _ARM_KOS_LIBCPUSTATE_ASM_FEATURES_H
#define _ARM_KOS_LIBCPUSTATE_ASM_FEATURES_H 1

#include <__stdinc.h>

#define LIBCPUSTATE_HAVE_UCPUSTATE
#define LIBCPUSTATE_HAVE_LCPUSTATE
#define LIBCPUSTATE_HAVE_KCPUSTATE
#define LIBCPUSTATE_HAVE_ICPUSTATE
#define LIBCPUSTATE_HAVE_SCPUSTATE
#ifdef __KERNEL__
#define LIBCPUSTATE_HAVE_FCPUSTATE
#else /* __KERNEL__ */
#define LIBCPUSTATE_HAVE_MCONTEXT
#define LIBCPUSTATE_HAVE_UCONTEXT
#endif /* !__KERNEL__ */
#define LIBCPUSTATE_HAVE_FPUSTATE

#endif /* !_ARM_KOS_LIBCPUSTATE_ASM_FEATURES_H */
