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
#define LCPUSTATE_ALIAS     ucpustate
#define LCPUSTATE_ALIAS_STR "ucpustate"
#endif /* LCPUSTATE_IS_UCPUSTATE */

#ifdef KCPUSTATE_IS_UCPUSTATE)
#define KCPUSTATE_ALIAS     ucpustate
#define KCPUSTATE_ALIAS_STR "ucpustate"
#elif defined(KCPUSTATE_IS_LCPUSTATE)
#define KCPUSTATE_ALIAS     lcpustate
#define KCPUSTATE_ALIAS_STR "lcpustate"
#endif /* ... */

#ifdef ICPUSTATE_IS_UCPUSTATE
#define ICPUSTATE_ALIAS     ucpustate
#define ICPUSTATE_ALIAS_STR "ucpustate"
#elif defined(ICPUSTATE_IS_LCPUSTATE)
#define ICPUSTATE_ALIAS     lcpustate
#define ICPUSTATE_ALIAS_STR "lcpustate"
#elif defined(ICPUSTATE_IS_KCPUSTATE)
#define ICPUSTATE_ALIAS     kcpustate
#define ICPUSTATE_ALIAS_STR "kcpustate"
#endif /* ICPUSTATE_IS_?CPUSTATE */

#ifdef SCPUSTATE_IS_UCPUSTATE
#define SCPUSTATE_ALIAS     ucpustate
#define SCPUSTATE_ALIAS_STR "ucpustate"
#elif defined(SCPUSTATE_IS_LCPUSTATE)
#define SCPUSTATE_ALIAS     lcpustate
#define SCPUSTATE_ALIAS_STR "lcpustate"
#elif defined(SCPUSTATE_IS_KCPUSTATE)
#define SCPUSTATE_ALIAS     kcpustate
#define SCPUSTATE_ALIAS_STR "kcpustate"
#elif defined(SCPUSTATE_IS_ICPUSTATE)
#define SCPUSTATE_ALIAS     icpustate
#define SCPUSTATE_ALIAS_STR "icpustate"
#endif /* SCPUSTATE_IS_?CPUSTATE */

#ifdef FCPUSTATE_IS_UCPUSTATE
#define FCPUSTATE_ALIAS     ucpustate
#define FCPUSTATE_ALIAS_STR "ucpustate"
#elif defined(FCPUSTATE_IS_LCPUSTATE)
#define FCPUSTATE_ALIAS     lcpustate
#define FCPUSTATE_ALIAS_STR "lcpustate"
#elif defined(FCPUSTATE_IS_KCPUSTATE)
#define FCPUSTATE_ALIAS     kcpustate
#define FCPUSTATE_ALIAS_STR "kcpustate"
#elif defined(FCPUSTATE_IS_ICPUSTATE)
#define FCPUSTATE_ALIAS     icpustate
#define FCPUSTATE_ALIAS_STR "icpustate"
#elif defined(FCPUSTATE_IS_SCPUSTATE)
#define FCPUSTATE_ALIAS     scpustate
#define FCPUSTATE_ALIAS_STR "scpustate"
#endif /* FCPUSTATE_IS_?CPUSTATE */


/************************************************************************/
/* Define transitive aliasing helper macros                             */
/************************************************************************/
#if (((defined(KCPUSTATE_IS_LCPUSTATE) || defined(ICPUSTATE_IS_LCPUSTATE) ||  \
       defined(SCPUSTATE_IS_LCPUSTATE) || defined(FCPUSTATE_IS_LCPUSTATE)) && \
      defined(LCPUSTATE_ALIAS)) ||                                          \
     ((defined(ICPUSTATE_IS_KCPUSTATE) || defined(SCPUSTATE_IS_KCPUSTATE) ||  \
       defined(FCPUSTATE_IS_KCPUSTATE)) &&                                    \
      defined(KCPUSTATE_ALIAS)) ||                                          \
     ((defined(SCPUSTATE_IS_ICPUSTATE) || defined(FCPUSTATE_IS_ICPUSTATE)) && \
      defined(ICPUSTATE_ALIAS)) ||                                          \
     (defined(FCPUSTATE_IS_SCPUSTATE) && defined(SCPUSTATE_ALIAS)))
#error "Don't define transitive cpu-state aliasing macros (always-, and only reference the lowest-most alias)"
#endif /* ... */

#ifdef LCPUSTATE_IS_UCPUSTATE
#define LCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#endif /* LCPUSTATE_IS_UCPUSTATE */
#ifdef KCPUSTATE_IS_UCPUSTATE
#define KCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#endif /* KCPUSTATE_IS_UCPUSTATE */
#ifdef ICPUSTATE_IS_UCPUSTATE
#define ICPUSTATE_IS_TRANSITIVE_UCPUSTATE
#endif /* ICPUSTATE_IS_UCPUSTATE */
#ifdef SCPUSTATE_IS_UCPUSTATE
#define SCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#endif /* SCPUSTATE_IS_UCPUSTATE */
#ifdef FCPUSTATE_IS_UCPUSTATE
#define FCPUSTATE_IS_TRANSITIVE_UCPUSTATE
#endif /* FCPUSTATE_IS_UCPUSTATE */

#if (defined(KCPUSTATE_IS_LCPUSTATE) || \
     (defined(KCPUSTATE_IS_TRANSITIVE_UCPUSTATE) && defined(LCPUSTATE_IS_TRANSITIVE_UCPUSTATE)))
#define KCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#endif /* ... */
#if (defined(ICPUSTATE_IS_LCPUSTATE) || \
     (defined(ICPUSTATE_IS_TRANSITIVE_UCPUSTATE) && defined(LCPUSTATE_IS_TRANSITIVE_UCPUSTATE)))
#define ICPUSTATE_IS_TRANSITIVE_LCPUSTATE
#endif /* ... */
#if (defined(SCPUSTATE_IS_LCPUSTATE) || \
     (defined(SCPUSTATE_IS_TRANSITIVE_UCPUSTATE) && defined(LCPUSTATE_IS_TRANSITIVE_UCPUSTATE)))
#define SCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#endif /* ... */
#if (defined(FCPUSTATE_IS_LCPUSTATE) || \
     (defined(FCPUSTATE_IS_TRANSITIVE_UCPUSTATE) && defined(LCPUSTATE_IS_TRANSITIVE_UCPUSTATE)))
#define FCPUSTATE_IS_TRANSITIVE_LCPUSTATE
#endif /* ... */


#if (defined(ICPUSTATE_IS_KCPUSTATE) ||                                                            \
     (defined(ICPUSTATE_IS_TRANSITIVE_UCPUSTATE) && defined(KCPUSTATE_IS_TRANSITIVE_UCPUSTATE)) || \
     (defined(ICPUSTATE_IS_TRANSITIVE_LCPUSTATE) && defined(KCPUSTATE_IS_TRANSITIVE_LCPUSTATE)))
#define ICPUSTATE_IS_TRANSITIVE_KCPUSTATE
#endif /* ... */
#if (defined(SCPUSTATE_IS_KCPUSTATE) ||                                                            \
     (defined(SCPUSTATE_IS_TRANSITIVE_UCPUSTATE) && defined(KCPUSTATE_IS_TRANSITIVE_UCPUSTATE)) || \
     (defined(SCPUSTATE_IS_TRANSITIVE_LCPUSTATE) && defined(KCPUSTATE_IS_TRANSITIVE_LCPUSTATE)))
#define SCPUSTATE_IS_TRANSITIVE_KCPUSTATE
#endif /* ... */
#if (defined(FCPUSTATE_IS_KCPUSTATE) ||                                                            \
     (defined(FCPUSTATE_IS_TRANSITIVE_UCPUSTATE) && defined(KCPUSTATE_IS_TRANSITIVE_UCPUSTATE)) || \
     (defined(FCPUSTATE_IS_TRANSITIVE_LCPUSTATE) && defined(KCPUSTATE_IS_TRANSITIVE_LCPUSTATE)))
#define FCPUSTATE_IS_TRANSITIVE_KCPUSTATE
#endif /* ... */

#if (defined(SCPUSTATE_IS_ICPUSTATE) ||                                                            \
     (defined(SCPUSTATE_IS_TRANSITIVE_KCPUSTATE) && defined(ICPUSTATE_IS_TRANSITIVE_KCPUSTATE)) || \
     (defined(SCPUSTATE_IS_TRANSITIVE_UCPUSTATE) && defined(ICPUSTATE_IS_TRANSITIVE_UCPUSTATE)) || \
     (defined(SCPUSTATE_IS_TRANSITIVE_LCPUSTATE) && defined(ICPUSTATE_IS_TRANSITIVE_LCPUSTATE)))
#define SCPUSTATE_IS_TRANSITIVE_ICPUSTATE
#endif /* ... */
#if (defined(FCPUSTATE_IS_ICPUSTATE) ||                                                            \
     (defined(FCPUSTATE_IS_TRANSITIVE_KCPUSTATE) && defined(ICPUSTATE_IS_TRANSITIVE_KCPUSTATE)) || \
     (defined(FCPUSTATE_IS_TRANSITIVE_UCPUSTATE) && defined(ICPUSTATE_IS_TRANSITIVE_UCPUSTATE)) || \
     (defined(FCPUSTATE_IS_TRANSITIVE_LCPUSTATE) && defined(ICPUSTATE_IS_TRANSITIVE_LCPUSTATE)))
#define FCPUSTATE_IS_TRANSITIVE_ICPUSTATE
#endif /* ... */

#if (defined(FCPUSTATE_IS_SCPUSTATE) ||                                                            \
     (defined(FCPUSTATE_IS_TRANSITIVE_ICPUSTATE) && defined(SCPUSTATE_IS_TRANSITIVE_ICPUSTATE)) || \
     (defined(FCPUSTATE_IS_TRANSITIVE_KCPUSTATE) && defined(SCPUSTATE_IS_TRANSITIVE_KCPUSTATE)) || \
     (defined(FCPUSTATE_IS_TRANSITIVE_UCPUSTATE) && defined(SCPUSTATE_IS_TRANSITIVE_UCPUSTATE)) || \
     (defined(FCPUSTATE_IS_TRANSITIVE_LCPUSTATE) && defined(SCPUSTATE_IS_TRANSITIVE_LCPUSTATE)))
#define FCPUSTATE_IS_TRANSITIVE_SCPUSTATE
#endif /* ... */

#endif /* !_KOS_KERNEL_CPU_STATE_H */
