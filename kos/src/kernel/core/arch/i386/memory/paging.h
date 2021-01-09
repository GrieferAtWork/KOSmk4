/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING_H
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>

#include <hybrid/align.h>

#include <bits/crt/inttypes.h>

#include <assert.h>


#if !defined(NDEBUG) && 0
#include <kernel/printk.h>
#define PG_TRACE_PREPARE(addr, num_bytes)      \
	printk(KERN_TRACE "[pd] +prepare:%p-%p\n", \
	       addr, (byte_t *)(addr) + (num_bytes)-1)
#define PG_TRACE_UNPREPARE(addr, num_bytes)    \
	printk(KERN_TRACE "[pd] -prepare:%p-%p\n", \
	       addr, (byte_t *)(addr) + (num_bytes)-1)
#define PG_TRACE_PREPARE_IF(cond, addr, num_bytes) \
	(!(cond) || (PG_TRACE_PREPARE(addr, num_bytes), 0))
#else /* !NDEBUG */
#define PG_TRACE_PREPARE(addr, num_bytes)          (void)0
#define PG_TRACE_UNPREPARE(addr, num_bytes)        (void)0
#define PG_TRACE_PREPARE_IF(cond, addr, num_bytes) (void)0
#endif /* NDEBUG */

#if !defined(NDEBUG) && 0
#include <kernel/printk.h>
#define PG_TRACE_MAP(addr, num_bytes, phys, perm)                                       \
	printk(KERN_TRACE "[pd] +mmap:%p-%p " __PRINP(__SIZEOF_PHYSADDR_T__) " %c%c%c%c\n", \
	       addr, (byte_t *)(addr) + (num_bytes)-1, (physaddr_t)(phys),                  \
	       perm & PAGEDIR_MAP_FEXEC ? 'x' : '-',                                        \
	       perm & PAGEDIR_MAP_FWRITE ? 'w' : '-',                                       \
	       perm & PAGEDIR_MAP_FREAD ? 'r' : '-',                                        \
	       perm & PAGEDIR_MAP_FUSER ? 'u' : '-')
#define PG_TRACE_UNMAP(addr, num_bytes)     \
	printk(KERN_TRACE "[pd] -mmap:%p-%p\n", \
	       addr, (byte_t *)(addr) + (num_bytes)-1)
#else /* !NDEBUG */
#define PG_TRACE_MAP(addr, num_bytes, phys, perm) (void)0
#define PG_TRACE_UNMAP(addr, num_bytes) (void)0
#endif /* NDEBUG */

#define PG_ASSERT_ALIGNED_ADDRESS(addr) \
	__assertf(IS_ALIGNED((uintptr_t)(addr), 4096), "addr = %p", addr)
#define PG_ASSERT_ALIGNED_ADDRESS_RANGE(addr, num_bytes)                \
	(__assertf(IS_ALIGNED((uintptr_t)(addr), 4096), "addr = %p", addr), \
	 __assertf(IS_ALIGNED((uintptr_t)(num_bytes), 4096),                \
	           "num_bytes = %#" __PRIN_PREFIX(__SIZEOF_SIZE_T__) "x",   \
	           num_bytes),                                              \
	 __assertf((uintptr_t)(addr) + (num_bytes) >= (uintptr_t)(addr) ||  \
	           (uintptr_t)(addr) + (num_bytes) == 0,                    \
	           "Invalid range %p...%p",                                 \
	           (addr), (uintptr_t)(addr) + (num_bytes)-1))


#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING_H */
