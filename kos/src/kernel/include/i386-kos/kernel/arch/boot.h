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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_BOOT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_BOOT_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <kos/kernel/cpu-state32.h> /* fcpustate32 */
#include <kos/kernel/paging.h>

DECL_BEGIN

/* Minimum amount of ram to detect during early boot.
 * If less than this amount is detected, keep trying to find ways of
 * locating more (using different BIOS functions, or by simply guessing) */
#define X86_BOOT_MINIMUM_AVAILABLE_RAM \
	VM_ADDR2PAGE(0x100000) /* 1MB */


#ifdef __CC__
/* The CPU context when the hosting CPU was originally started. */
DATDEF struct fcpustate32 boot_cpustate;

struct boot_device_info {
	u8 bdi_biosdev;           /* [valid_if(bdi_partition != 0xff)] int 13h - compatible device number */
	u8 bdi_partition;         /* 0-based index of the partition from which the kernel was loaded
	                           * If no boot device information is available, then this is 0xff */
	u8 bdi_sub_partition;     /* 0-based index of the sub-partition from which the kernel was loaded
	                           * If not available, set to 0xff. */
	u8 bdi_sub_sub_partition; /* 0-based index of the sub-sub-partition from which the kernel was loaded
	                           * If not available, set to 0xff. */
};
DATDEF struct boot_device_info boot_device;
#define have_boot_device()    (boot_device.bdi_partition != 0xff)



#ifdef CONFIG_BUILDING_KERNEL_CORE
INTDEF FREE void NOTHROW(KCALL x86_initialize_paging)(void);
INTDEF FREE void NOTHROW(KCALL x86_load_mb1info)(PHYS u32 info);
INTDEF FREE void NOTHROW(KCALL x86_load_mb2info)(PHYS u32 info);
INTDEF FREE void NOTHROW(KCALL x86_initialize_default_memory_banks)(void);
INTDEF FREE void NOTHROW(KCALL x86_initialize_memory_via_bios)(void);
INTDEF FREE void NOTHROW(KCALL x86_initialize_smp)(void);
INTDEF FREE void NOTHROW(KCALL x86_initialize_acpi)(void);
INTDEF FREE void NOTHROW(KCALL x86_initialize_apic)(void);
INTDEF FREE void NOTHROW(KCALL x86_initialize_kernel_vm)(void);
INTDEF FREE void NOTHROW(KCALL x86_initialize_kernel_vm_readonly)(void);
INTDEF FREE void NOTHROW(KCALL x86_initialize_sysenter)(void);
INTDEF FREE void NOTHROW(KCALL x86_initialize_rand_entropy)(void);
#ifndef CONFIG_NO_FPU
INTDEF FREE void NOTHROW(KCALL x86_initialize_fpu)(void);
#endif /* !CONFIG_NO_FPU */
#ifndef CONFIG_NO_USERKERN_SEGMENT
#ifdef __x86_64__
INTDEF uintptr_t NOTHROW(KCALL x86_this_userkern_init)(void);
#endif /* __x86_64__ */
#endif /* !CONFIG_NO_USERKERN_SEGMENT */
INTDEF FREE void NOTHROW(KCALL x86_initialize_commandline_himem)(void);
INTDEF FREE void NOTHROW(KCALL x86_initialize_bootloader_drivers)(void);
#endif /* CONFIG_BUILDING_KERNEL_CORE */
#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_BOOT_H */
