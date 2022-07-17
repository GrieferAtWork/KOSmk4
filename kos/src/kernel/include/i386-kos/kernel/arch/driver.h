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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_DRIVER_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_DRIVER_H 1

#include <kernel/compiler.h>

#define KERNEL_DRIVER_NAME                 "kernel"
#define KERNEL_DRIVER_FILENAME             "/os/kernel.bin"
#define KERNEL_DRIVER_DEFAULT_LIBRARY_PATH "/os/drivers/i386:/os/drivers"

#ifdef __x86_64__
#define KERNEL_DRIVER_REQUIRED_CLASS     ELFCLASS64
#define KERNEL_DRIVER_REQUIRED_CLASS_S   "ELFCLASS64"
#define KERNEL_DRIVER_REQUIRED_MACHINE   EM_X86_64
#define KERNEL_DRIVER_REQUIRED_MACHINE_S "EM_X86_64"
#else /* __x86_64__ */
#define KERNEL_DRIVER_REQUIRED_CLASS     ELFCLASS32
#define KERNEL_DRIVER_REQUIRED_CLASS_S   "ELFCLASS32"
#define KERNEL_DRIVER_REQUIRED_MACHINE   EM_386
#define KERNEL_DRIVER_REQUIRED_MACHINE_S "EM_386"
#endif /* !__x86_64__ */
#define KERNEL_DRIVER_REQUIRED_DATA         ELFDATA2LSB
#define KERNEL_DRIVER_REQUIRED_DATA_S       "ELFDATA2LSB"
#define KERNEL_DRIVER_MAXPROGRAMHEADERCOUNT 64

#ifdef __CC__
DECL_BEGIN

#ifdef BUILDING_KERNEL_CORE
struct driver;

/* Perform   arch-specific   driver    initialization.
 * On x86, this function handles code alternatives, as
 * defined via the  optional `.alternatives'  section. */
INTDEF NONNULL((1)) void KCALL
arch_driver_initialize(struct driver *__restrict self);

#define ARCH_HAVE_ARCH_DRIVER_INITIALIZE 1
#endif /* BUILDING_KERNEL_CORE */

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_DRIVER_H */
