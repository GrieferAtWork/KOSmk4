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

#include <kernel/compiler.h>

#include <kernel/cpuid.h>
#include <kernel/paging.h>

#include <kos/kernel/gdt.h>
#include <kos/kernel/tss.h>

#define EXPORT_AS_OBJECT(name) \
	.type name, @object;       \
	.global name;
#define EXPORT_AS_OBJECT_EX(name, size_) \
	EXPORT_AS_OBJECT(name)               \
	.size name, size_;
EXPORT_AS_OBJECT(vm_kernel)
EXPORT_AS_OBJECT(_this_idle)
EXPORT_AS_OBJECT(_bootcpu)
EXPORT_AS_OBJECT(_bootidle)
EXPORT_AS_OBJECT(_boottask)
EXPORT_AS_OBJECT_EX(x86_cputss, SIZEOF_TSS)
EXPORT_AS_OBJECT_EX(x86_cpuiob, 8192)
EXPORT_AS_OBJECT_EX(pagedir_kernel, PAGEDIR_SIZE)
EXPORT_AS_OBJECT_EX(pagedir_kernel_phys, PAGEDIR_SIZE)
EXPORT_AS_OBJECT_EX(jiffies, 8)
EXPORT_AS_OBJECT_EX(__x86_bootcpu_features, 2)
EXPORT_AS_OBJECT_EX(__x86_bootcpu_idfeatures, SIZEOF_CPUID_CPUINFO)
#undef EXPORT_AS_OBJECT_EX
#undef EXPORT_AS_OBJECT


