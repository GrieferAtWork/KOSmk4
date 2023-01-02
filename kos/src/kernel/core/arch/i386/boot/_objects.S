/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_BOOT__OBJECTS_S
#define GUARD_KERNEL_CORE_ARCH_I386_BOOT__OBJECTS_S 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/x86/cpuid.h>

#include <kos/kernel/x86/gdt.h>
#include <kos/kernel/x86/tss.h>

#define EXPORT_AS_OBJECT(name) \
	.type name, "object";      \
	.global name;
#define EXPORT_AS_OBJECT_EX(name, size_) \
	EXPORT_AS_OBJECT(name)               \
	.size name, size_;
EXPORT_AS_OBJECT(mman_kernel)
EXPORT_AS_OBJECT_EX(mman_kernel_lockops, __SIZEOF_POINTER__)
EXPORT_AS_OBJECT(thiscpu_idle)
EXPORT_AS_OBJECT(bootcpu)
EXPORT_AS_OBJECT(bootidle)
EXPORT_AS_OBJECT(boottask)
EXPORT_AS_OBJECT_EX(pagedir_kernel, PAGEDIR_SIZE)
EXPORT_AS_OBJECT_EX(pagedir_kernel_phys, PAGEDIR_SIZE)
EXPORT_AS_OBJECT_EX(thiscpu_x86_tss, SIZEOF_TSS)
EXPORT_AS_OBJECT_EX(thiscpu_x86_iob, 8192)
EXPORT_AS_OBJECT_EX(this_x86_kernel_psp0, __SIZEOF_POINTER__)
EXPORT_AS_OBJECT_EX(bootcpu_x86_cpufeatures, 2)
EXPORT_AS_OBJECT_EX(bootcpu_x86_cpuid, SIZEOF_CPUID_CPUINFO)
EXPORT_AS_OBJECT_EX(bootcpu_x86_gdt, SEGMENT_COUNT * 8)
EXPORT_AS_OBJECT_EX(thiscpu_idle_sstate, __SIZEOF_POINTER__)
EXPORT_AS_OBJECT_EX(thiscpu_idle_x86_kernel_psp0, __SIZEOF_POINTER__)
#undef EXPORT_AS_OBJECT_EX
#undef EXPORT_AS_OBJECT

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_BOOT__OBJECTS_S */
