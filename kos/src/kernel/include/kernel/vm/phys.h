/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_PHYS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_PHYS_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <sched/pertask.h> /* PERTASK_GET() */

/* Helper functions for accessing physical memory */

DECL_BEGIN

/* Copy memory to/from the physical address space. */
FUNDEF void KCALL vm_copyfromphys(USER CHECKED void *dst, PHYS vm_phys_t src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF void KCALL vm_copytophys(PHYS vm_phys_t dst, USER CHECKED void const *src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_copyinphys)(PHYS vm_phys_t dst, PHYS vm_phys_t src, size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_memsetphys)(PHYS vm_phys_t dst, int byte, size_t num_bytes);

/* no-#PF variants of `vm_copy(from|to)phys()'.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transfered.
 *              The affected memory range is:
 *               - `(dst|src) + num_bytes - return ... (dst|src) + num_bytes - 1' */
FUNDEF NOBLOCK size_t NOTHROW(KCALL vm_copyfromphys_nopf)(USER CHECKED void *dst, PHYS vm_phys_t src, size_t num_bytes);
FUNDEF NOBLOCK size_t NOTHROW(KCALL vm_copytophys_nopf)(PHYS vm_phys_t dst, USER CHECKED void const *src, size_t num_bytes);


/* A single page of virtual memory in the kernel VM, that is always
 * prepared for being used for whatever purposes a thread has in mind.
 * NOTE: This page is also used by PAGEFAULTS, though it will
 *       restore a previous mapping, if such a mapping existed.
 * NOTE: Because this page is unique for each thread, the user is not
 *       required to acquire a lock to the kernel VM when wishing to
 *       map something at this location! */
DATDEF ATTR_PERTASK vm_vpage_t _this_trampoline_page;
#define THIS_TRAMPOLINE_PAGE PERTASK_GET(_this_trampoline_page)

#ifdef CONFIG_BUILDING_KERNEL_CORE
/* A data part used to describe a single, reserved page. */
INTDEF ATTR_PERTASK struct vm_node _this_trampoline_node;
#endif /* CONFIG_BUILDING_KERNEL_CORE */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_PHYS_H */
