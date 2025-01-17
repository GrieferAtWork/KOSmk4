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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_TSS_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_TSS_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/host.h>

#include <kos/kernel/x86/tss.h>

DECL_BEGIN

#ifdef __CC__

/* The PER-cpu TSS descriptor. */
DATDEF ATTR_PERCPU struct tss thiscpu_x86_tss;

/* Mapping for the currently used I/O permissions bitmap
 * Lazily updated to always be mapped to the calling thread's `THIS_X86_IOPERM_BITMAP'
 * WARNING: Accessing  this  array is  _only_ allowed  while  preemption is  disabled, or
 *          the  TASK_FKEEPCORE  flag is  set.  Accessing this  array  at any  other time
 *          may lead to a kernel panic within the pagefault handler (note that user-space
 *          accessing  this array will simply be dismissed since user-space isn't allowed
 *          to access kernel-space structures in any case)
 *          Also  note that in case of a write-access, if the calling thread doesn't already
 *          have its own IOB allocated, accessing this vector will lazily allocate said IOB,
 *          meaning that write-access may also cause `E_BADALLOC' and `E_WOULDBLOCK'. */
DATDEF ATTR_PERCPU u8 thiscpu_x86_iob[65536 / 8];

/* The VM node used to represent the IOB mapping of the current CPU */
DATDEF ATTR_PERCPU struct mnode thiscpu_x86_iobnode;

#ifdef BUILDING_KERNEL_CORE
/* [1..1][const] Page directory identity pointer for unmapping the IOB vector of the current CPU. */
INTDEF ATTR_PERCPU void *thiscpu_x86_iobnode_pagedir_identity;
#endif /* BUILDING_KERNEL_CORE */



/* ioperm() bitmap.
 * KOS implements the io permissions bitmap using lazy page mappings:
 * During preemption:
 *     >> if (OLD_THREAD->IOPERM_BITMAP != NEW_THREAD->IOPERM_BITMAP &&
 *     >>     IS_IOPERM_BITMAP_LOADED(THIS_CPU)) {
 *     >>     pagedir_unmap(THIS_CPU:thiscpu_x86_iob, 2 * PAGESIZE);
 *     >>     pagedir_sync(THIS_CPU:thiscpu_x86_iob, 2 * PAGESIZE);
 *     >>     SET_IOPERM_BITMAP_LOADED(THIS_CPU, false);
 *     >> }
 * During #PF handling:
 *     >> if (CR2 in THIS_CPU:thiscpu_x86_iob) {
 *     >>     struct ioperm_bitmap *iob;
 *     >>     iob = PERTASK_GET(this_x86_ioperm_bitmap);
 *     >>     if (!iob) {
 *     >>         iob = incref(ioperm_bitmap_getempty());
 *     >>         PERTASK_SET(this_x86_ioperm_bitmap, iob);
 *     >>     } else if (IS_WRITING() && isshared(iob)) {
 *     >>         iob = ioperm_bitmap_copy(iob);
 *     >>         PERTASK_SET(this_x86_ioperm_bitmap, iob);
 *     >>     }
 *     >>     pagedir_map(THIS_CPU:thiscpu_x86_iob, 2 * PAGESIZE,
 *     >>                 iob->ib_pages, IS_WRITING() ? (PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE)
 *     >>                                             : PAGEDIR_PROT_READ);
 *     >>     SET_IOPERM_BITMAP_LOADED(THIS_CPU, true);
 *     >>     return;
 *     >> }
 * Within ioperm():
 *     >> struct ioperm_bitmap *iob;
 *     >> iob = PERTASK_GET(this_x86_ioperm_bitmap);
 *     >> if (!iob)
 *     >>     iob = ioperm_bitmap_alloc();
 *     >> else if (isshared(iob)) {
 *     >>     iob = ioperm_bitmap_copy(iob);
 *     >> }
 *     >> update_bits(iob->bitmap, from, to, turn_on);
 * NOTE: The entire ioperm bitmap needs exactly 2 pages of memory:
 *   - 0x10000 (65536) ports / 8 bits-per-byte -> 0x2000 (8192) bytes
 *     8192 bytes / 4096 bytes-per-page == 2 pages
 *   - According to intel  specs, the processor  may access +1  additional
 *     byte past the end of the ioperm bitmap which is expected to contain
 *     all 1-bits. As such, the 2 ioperm bitmaps must be followed by  some
 *     data page, who's first byte is a constant 0xff.
 *
 * With all of this in mind, the TSS in memory looks like this:
 *
 * 0 ... SIZEOF_TSS32 - 1:  struct tss
 *    NOTE: thiscpu_x86_tss.t_iomap == CEIL_ALIGN((uintptr_t)&thiscpu_x86_tss +
 *                                                SIZEOF_TSS32 +
 *                                                SIZEOF_INTERRUPT_REDIRECTION_BITMAP,
 *                                                4096) -  (uintptr_t)&thiscpu_x86_tss
 *          -> Meaning  that  it  points  to  the  first  page  boundry  following
 *             the TSS, leaving enough space for the interrupt redirection bitmap.
 *
 * IOBM = (uintptr_t)&thiscpu_x86_tss + thiscpu_x86_tss.t_iomap = thiscpu_x86_iob;
 * IOBM + 0 * PAGESIZE: Either unmapped memory, or mapped to `PERTASK_GET(this_x86_ioperm_bitmap)->ib_pages + 0 * PAGESIZE'
 * IOBM + 1 * PAGESIZE: Either unmapped memory, or mapped to `PERTASK_GET(this_x86_ioperm_bitmap)->ib_pages + 1 * PAGESIZE'
 * IOBM + 2 * PAGESIZE: The continuation of ATTR_PERCPU data, with the first byte being a const `0xff'
 *
 * And the GDT entry for the TSS looks like this:
 * GDT[SEGMENT_CPU_TSS].base  =  &thiscpu_x86_tss
 * GDT[SEGMENT_CPU_TSS].limit = ((IOBM - (uintptr_t)&thiscpu_x86_tss) + 2 * 4096 + 1) - 1;
 */


#ifndef CONFIG_NO_SMP
/* Mem node & part describing the #DF stack of the current CPU.
 * WARNING: These structures for the boot CPU are not actually part of the kernel mman! */
DATDEF ATTR_PERCPU struct mnode const thiscpu_x86_dfstacknode;
DATDEF ATTR_PERCPU struct mpart const thiscpu_x86_dfstackpart;
#endif /* !CONFIG_NO_SMP */


#ifndef __x86_64__
/* A special task segment that is linked to the #DF (Double Fault)
 * exception  of each CPU, allowing the kernel to still perform do
 * exception handling when in an extraordinarily broken state (and
 * possibly even recover)
 * This is (e.g.) how the kernel is able to deal with Stack Overflows
 * that occur within kernel-space itself. */
DATDEF ATTR_PERCPU struct tss thiscpu_x86_tssdf;
#endif /* !__x86_64__ */

#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_TSS_H */
