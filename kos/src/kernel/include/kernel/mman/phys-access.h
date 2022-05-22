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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_PHYS_ACCESS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_PHYS_ACCESS_H 1

#include <kernel/compiler.h>

#include <kernel/arch/paging.h> /* `pagedir_pushval_t' */
#include <kernel/memory.h>      /* `physpage2addr()' */
#include <kernel/mman/phys.h>
#include <kernel/paging.h> /* `pagedir_push_mapone()' */

#include <kos/kernel/paging.h> /* `PHYS_IS_IDENTITY()' */

#ifdef __CC__
DECL_BEGIN

/* Low-level physical memory access helpers. */

#ifdef NO_PHYS_IDENTITY
#define IF_HAVE_PHYS_IDENTITY(...)               /* nothing */
#define IF_PHYS_IDENTITY(addr, num_bytes, ...)   (void)0
#define IF_PHYS_IDENTITY_PAGE(addr_of_page, ...) (void)0
#else /* NO_PHYS_IDENTITY */
#define IF_HAVE_PHYS_IDENTITY(...) __VA_ARGS__
#define IF_PHYS_IDENTITY(addr, num_bytes, ...)         \
	do {                                               \
		if likely(PHYS_IS_IDENTITY(addr, num_bytes)) { \
			__VA_ARGS__;                               \
		}                                              \
	}	__WHILE0
#define IF_PHYS_IDENTITY_PAGE(addr_of_page, ...)                        \
	do {                                                                \
		if likely(PHYS_IS_IDENTITY_PAGE(physaddr2page(addr_of_page))) { \
			__VA_ARGS__;                                                \
		}                                                               \
	}	__WHILE0
#endif /* !NO_PHYS_IDENTITY */

/* Declare variables needed by macros below. */
#define PHYS_VARS                           \
	PAGEDIR_PAGEALIGNED byte_t *trampoline; \
	pagedir_pushval_t _pp_oldval

/* Save the calling thread's trampoline mapping and re-map it to `addr_of_page'
 * @return: * : The base address of the calling thread's trampoline (== vaddr of `addr_of_page') */
#define phys_pushpage(addr_of_page)                             \
	(trampoline = THIS_TRAMPOLINE, COMPILER_BARRIER(),          \
	 _pp_oldval = pagedir_push_mapone(trampoline, addr_of_page, \
	                                  PAGEDIR_PROT_READ |       \
	                                  PAGEDIR_PROT_WRITE),      \
	 pagedir_syncone(trampoline), COMPILER_BARRIER(), trampoline)

/* Re-map the calling thread's trampoline to `addr_of_page'
 * @return: * : The base address of the calling thread's trampoline (== vaddr of `addr_of_page') */
#define phys_loadpage(addr_of_page)                          \
	(COMPILER_BARRIER(),                                     \
	 pagedir_mapone(trampoline, addr_of_page,                \
	                PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE), \
	 pagedir_syncone(trampoline),                            \
	 COMPILER_BARRIER(), trampoline)

/* Same as `phys_pushpage' / `phys_loadpage', but map the page containing a given address
 * @return: * : The  virtual address at which `addr' can be found. Not at the size of this
 *              mapping spans until the next page-boundary (though at least 1 byte will be
 *              available) */
#define phys_pushaddr(addr) (phys_pushpage((addr) & ~PAGEMASK) + (uintptr_t)((addr) & PAGEMASK))
#define phys_loadaddr(addr) (phys_loadpage((addr) & ~PAGEMASK) + (uintptr_t)((addr) & PAGEMASK))

/* Re-map the calling thread's trampoline to `addr_of_page' */
#define phys_pop() pagedir_pop_mapone(trampoline, _pp_oldval)

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_PHYS_ACCESS_H */
