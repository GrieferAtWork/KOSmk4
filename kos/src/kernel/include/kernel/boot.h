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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_BOOT_H
#define GUARD_KERNEL_INCLUDE_KERNEL_BOOT_H 1

#include <kernel/compiler.h>

#include <kernel/arch/boot.h>
#include <kernel/selftest.h> /* CONFIG_HAVE_KERNEL_SELFTEST */
#include <kernel/types.h>

DECL_BEGIN

/* A collection of functions called as part of boot initialization. */

#ifdef BUILDING_KERNEL_CORE

struct icpustate;

INTDEF FREE void NOTHROW(KCALL kernel_initialize_scheduler)(void);
INTDEF FREE void NOTHROW(KCALL kernel_initialize_scheduler_after_smp)(void);
INTDEF FREE void NOTHROW(KCALL kernel_initialize_commandline_options_very_early)(void);
INTDEF FREE void NOTHROW(KCALL kernel_initialize_commandline_options_early)(void);
INTDEF FREE void NOTHROW(KCALL kernel_initialize_commandline_options_stable)(void);
INTDEF FREE void NOTHROW(KCALL kernel_initialize_commandline_options_late)(void);

/* Allocate and set a new mman for /bin/init during booting.
 * This function is used to assign a new mman for the initial user-space process,
 * so-as not to launch that process in the context of the special  `mman_kernel',
 * which shouldn't contain mappings for anything user-space related. */
INTDEF FREE void NOTHROW(KCALL kernel_initialize_user_mman)(void);

/* Initialize  (link,  relocate &  initialize)  all drivers
 * loaded via the kernel commandline as bootloader modules.
 * This  is done as a separate step from the actual loading
 * of  drivers so-as to allow for inter-driver dependencies
 * to be resolved correctly. */
INTDEF FREE void NOTHROW(KCALL kernel_initialize_loaded_drivers)(void);

/* Initialize builtin core drivers. */
INTDEF FREE void NOTHROW(KCALL kernel_initialize_ide_driver)(void);
INTDEF FREE void NOTHROW(KCALL kernel_initialize_fat_driver)(void);
INTDEF FREE void NOTHROW(KCALL kernel_initialize_rootfs)(void);

#ifdef CONFIG_HAVE_KERNEL_SELFTEST
INTDEF FREE void NOTHROW(KCALL kernel_initialize_selftest)(void);
#endif /* CONFIG_HAVE_KERNEL_SELFTEST */

/* Update the given cpu state to start executing /bin/init, or whatever
 * was passed as  argument in a  `init=...' kernel commandline  option. */
INTDEF FREE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(KCALL kernel_initialize_exec_init)(struct icpustate *__restrict state);

#endif /* BUILDING_KERNEL_CORE */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_BOOT_H */
