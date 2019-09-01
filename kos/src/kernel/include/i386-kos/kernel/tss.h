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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_TSS_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_TSS_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <hybrid/host.h>
#include <kos/kernel/tss.h>

DECL_BEGIN

#ifdef __CC__
/* The PER-cpu TSS descriptor. */
DATDEF ATTR_PERCPU struct tss x86_cputss;

#ifndef CONFIG_NO_SMP
/* VM node & datapart describing the #DF stack of the current CPU.
 * WARNING: These structures for the boot CPU are not actually part of the kernel VM! */
DATDEF ATTR_PERCPU struct vm_node const x86_this_dfstack;
DATDEF ATTR_PERCPU struct vm_datapart const x86_this_dfstack_part;
#endif /* !CONFIG_NO_SMP */


#ifndef __x86_64__
/* A special task segment that is linked to the #DF (Double Fault)
 * exception of each CPU, allowing the kernel to still perform do
 * exception handling when in an extraordinarily broken state (and
 * possibly even recover)
 * This is (e.g.) how the kernel is able to deal with Stack Overflows
 * that occur within kernel-space itself. */
DATDEF ATTR_PERCPU struct tss x86_cputss_df;
#endif

#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_TSS_H */
