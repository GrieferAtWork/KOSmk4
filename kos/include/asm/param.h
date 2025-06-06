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
/* (#) Portability: Linux (/usr/include/[...]/asm/param.h) */
/*!always_includes <asm/os/limits.h>*/
/*!always_includes <asm/pagesize.h>*/
#ifndef _ASM_PARAM_H
#define _ASM_PARAM_H 1

#include <asm/os/limits.h>
#include <asm/pagesize.h>

#if !defined(__EXEC_PAGESIZE) && defined(__ARCH_PAGESIZE)
#define __EXEC_PAGESIZE __ARCH_PAGESIZE
#endif /* !__EXEC_PAGESIZE && __ARCH_PAGESIZE */

/* System memory page size */
#if !defined(EXEC_PAGESIZE) && defined(__EXEC_PAGESIZE)
#define EXEC_PAGESIZE __EXEC_PAGESIZE
#endif /* !EXEC_PAGESIZE && __EXEC_PAGESIZE */

/* Scheduler frequency */
#if !defined(HZ) && defined(__HZ)
#define HZ __HZ
#endif /* !HZ && __HZ != -1 */

/* NOGROUP: Alias for `NGROUPS_MAX' */
#ifndef NOGROUP
#if defined(__NGROUPS_MAX) && (__NGROUPS_MAX + 0) != -1
#define NOGROUP __NGROUPS_MAX
#else /* ... */
#define NOGROUP (-1)
#endif /* !... */
#endif /* !NOGROUP */

/* MAXHOSTNAMELEN: Alias for `HOST_NAME_MAX' */
#ifndef MAXHOSTNAMELEN
#if defined(__HOST_NAME_MAX) && (__HOST_NAME_MAX + 0) != -1
#define MAXHOSTNAMELEN __HOST_NAME_MAX
#endif /* ... */
#endif /* !MAXHOSTNAMELEN */

#endif /* !_ASM_PARAM_H */
