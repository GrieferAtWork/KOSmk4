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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_APIC_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_APIC_H 1

#include <kernel/compiler.h>

#include <bits/types.h>
#include <hw/ic/apic.h>
#include <sys/mmio.h>

#ifdef __CC__
DECL_BEGIN

/* [const] Virtual  base  addresses  of  the  local  (per-cpu) APIC.
 * HINT: APIC stands for Advanced Programmable Interrupt Controller. */
DATDEF VIRT volatile __byte_t *const x86_lapicbase;
#define X86_HAVE_LAPIC             (x86_lapicbase != __NULLPTR)
#define lapic_read(offset)         peekl(x86_lapicbase + (offset))
#define lapic_write(offset, value) pokel(x86_lapicbase + (offset), value)

/* [valid_if(X86_HAVE_LAPIC)] The LAPIC ID of the controller associated with the CPU. */
DATDEF ATTR_PERCPU __u8 const thiscpu_x86_lapicid;

/* [valid_if(X86_HAVE_LAPIC)] The LAPIC version of the controller associated with the CPU.
 *                            This is one of `APICVER_*' from `<sched/smp.h>' */
DATDEF ATTR_PERCPU __u8 const thiscpu_x86_lapicversion;

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_APIC_H */
