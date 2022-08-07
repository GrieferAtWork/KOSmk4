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
#ifndef _KOS_KERNEL_CPU_STATE_H
#define _KOS_KERNEL_CPU_STATE_H 1

#include <kos/kernel/bits/cpu-state.h>

/* Define helper macros to test for aliases between different cpu states */
#ifdef LCPUSTATE_IS_UCPUSTATE
#define LCPUSTATE_ISALIAS
#endif /* LCPUSTATE_IS_?CPUSTATE */
#if (defined(KCPUSTATE_IS_UCPUSTATE) || \
     defined(KCPUSTATE_IS_LCPUSTATE))
#define KCPUSTATE_ISALIAS
#endif /* KCPUSTATE_IS_?CPUSTATE */
#if (defined(ICPUSTATE_IS_UCPUSTATE) || \
     defined(ICPUSTATE_IS_LCPUSTATE) || \
     defined(ICPUSTATE_IS_KCPUSTATE))
#define ICPUSTATE_ISALIAS
#endif /* ICPUSTATE_IS_?CPUSTATE */
#if (defined(SCPUSTATE_IS_UCPUSTATE) || \
     defined(SCPUSTATE_IS_LCPUSTATE) || \
     defined(SCPUSTATE_IS_KCPUSTATE) || \
     defined(SCPUSTATE_IS_ICPUSTATE))
#define SCPUSTATE_ISALIAS
#endif /* SCPUSTATE_IS_?CPUSTATE */
#if (defined(FCPUSTATE_IS_UCPUSTATE) || \
     defined(FCPUSTATE_IS_LCPUSTATE) || \
     defined(FCPUSTATE_IS_KCPUSTATE) || \
     defined(FCPUSTATE_IS_ICPUSTATE) || \
     defined(FCPUSTATE_IS_SCPUSTATE))
#define FCPUSTATE_ISALIAS
#endif /* FCPUSTATE_IS_?CPUSTATE */


#endif /* !_KOS_KERNEL_CPU_STATE_H */
