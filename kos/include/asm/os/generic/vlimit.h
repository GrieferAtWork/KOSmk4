/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_GENERIC_VLIMIT_H
#define _ASM_OS_GENERIC_VLIMIT_H 1

#include <__stdinc.h>

#include <asm/os/resource.h>

#define __LIM_NORAISE 0 /* Unsupported */
#define __LIM_TO_RLIMIT(x)   ((x) - 1)
#define __LIM_FROM_RLIMIT(x) ((x) + 1)

#ifdef __RLIMIT_CPU
#define __LIM_CPU __LIM_FROM_RLIMIT(__RLIMIT_CPU) /* s.a. `RLIMIT_CPU' */
#endif /* __RLIMIT_CPU */
#ifdef __RLIMIT_FSIZE
#define __LIM_FSIZE __LIM_FROM_RLIMIT(__RLIMIT_FSIZE) /* s.a. `RLIMIT_FSIZE' */
#endif /* __RLIMIT_FSIZE */
#ifdef __RLIMIT_DATA
#define __LIM_DATA __LIM_FROM_RLIMIT(__RLIMIT_DATA) /* s.a. `RLIMIT_DATA' */
#endif /* __RLIMIT_DATA */
#ifdef __RLIMIT_STACK
#define __LIM_STACK __LIM_FROM_RLIMIT(__RLIMIT_STACK) /* s.a. `RLIMIT_STACK' */
#endif /* __RLIMIT_STACK */
#ifdef __RLIMIT_CORE
#define __LIM_CORE __LIM_FROM_RLIMIT(__RLIMIT_CORE) /* s.a. `RLIMIT_CORE' */
#endif /* __RLIMIT_CORE */
#ifdef __RLIMIT_RSS
#define __LIM_MAXRSS __LIM_FROM_RLIMIT(__RLIMIT_RSS) /* s.a. `RLIMIT_RSS' */
#endif /* __RLIMIT_RSS */

#if 1
/* This is what Glibc defines for this constant... */
#define __VLIMIT_INFINITY 0x7fffffff
#else
/* ... But given the implementation being a wrapper for `setrlimit(2)',
 * which uses `RLIM_INFINITY == (rlim_t)-1' for this meaning, it stands
 * to reason to that _this_ would be the correct value... */
#define __VLIMIT_INFINITY (-1)
#endif


#endif /* !_ASM_OS_GENERIC_VLIMIT_H */
