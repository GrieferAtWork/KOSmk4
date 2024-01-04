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
#ifndef _KOS_KERNEL_MEMORY_H
#define _KOS_KERNEL_MEMORY_H 1

#include <__stdinc.h>

#include <asm/pagesize.h>
#include <bits/types.h>

/* Type  declarations  and  helper  macros   for
 * working with physical memory addresses/pages. */

#ifdef __CC__
__DECL_BEGIN

#ifndef __physaddr_t_defined
#define __physaddr_t_defined
#ifdef __KERNEL__
#include <hybrid/__altint.h>
__HYBRID_ALTINT_TYPEDEF(__physaddr_t, physaddr_t, false); /* Physical memory address (== physpage_t * PAGESIZE) */
#else /* __KERNEL__ */
typedef __physaddr_t physaddr_t; /* Physical memory address (== physpage_t * PAGESIZE) */
#endif /* !__KERNEL__ */
#endif /* !__physaddr_t_defined */

#ifndef __physpage_t_defined
#define __physpage_t_defined
#ifdef __KERNEL__
#include <hybrid/__altint.h>
__HYBRID_ALTINT_TYPEDEF(__physpage_t, physpage_t, false); /* Physical page address (== physaddr_t / PAGESIZE) */
#else /* __KERNEL__ */
typedef __physpage_t physpage_t; /* Physical page address (== physaddr_t / PAGESIZE) */
#endif /* !__KERNEL__ */
#endif /* !__physpage_t_defined */


/* Convert to/from physical addresses and physical page indices. */
#ifdef __ARCH_PAGESIZE
#if defined(__INTELLISENSE__) && defined(__CC__) && defined(__cplusplus)
extern "C++" {
physaddr_t (physpage2addr)(physpage_t __pageptr_);
physpage_t (physaddr2page)(physaddr_t __physaddr_);
physpage_t (physaddr2page)(__uintptr_t __physaddr_);
__UINT32_TYPE__ (physpage2addr32)(physpage_t __pageptr_);
}
#define physpage2addr   physpage2addr
#define physaddr2page   physaddr2page
#define physpage2addr32 physpage2addr32
#else /* __INTELLISENSE__ && __CC__ && __cplusplus */
#ifdef __ARCH_PAGESHIFT
#define physpage2addr(pageptr)   (__CCAST(physaddr_t)(pageptr) << __ARCH_PAGESHIFT)
#define physaddr2page(physaddr)  (__CCAST(physpage_t)((physaddr) >> __ARCH_PAGESHIFT))
#define physpage2addr32(pageptr) (__CCAST(__UINT32_TYPE__)(pageptr) << __ARCH_PAGESHIFT)
#else /* __ARCH_PAGESHIFT */
#define physpage2addr(pageptr)   (__CCAST(physaddr_t)(pageptr) * __ARCH_PAGESIZE)
#define physaddr2page(physaddr)  (__CCAST(physpage_t)((physaddr) / __ARCH_PAGESIZE))
#define physpage2addr32(pageptr) (__CCAST(__UINT32_TYPE__)(pageptr) * __ARCH_PAGESIZE)
#endif /* !__ARCH_PAGESHIFT */
#endif /* !__INTELLISENSE__ || !__CC__ || !__cplusplus */
#endif /* __ARCH_PAGESIZE */

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_KERNEL_MEMORY_H */
