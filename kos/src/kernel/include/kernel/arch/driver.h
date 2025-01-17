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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_ARCH_DRIVER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_ARCH_DRIVER_H 1

#include <kernel/compiler.h>

/************************************************************************/
/* Default kernel driver name, and on-disk file location                */
/************************************************************************/
#ifndef KERNEL_DRIVER_NAME
#define KERNEL_DRIVER_NAME "kernel"
#endif /* !KERNEL_DRIVER_NAME */
#ifndef KERNEL_DRIVER_FILENAME
#define KERNEL_DRIVER_FILENAME "/boot/kernel.bin"
#endif /* !KERNEL_DRIVER_FILENAME */


/************************************************************************/
/* Set default values to be identical to user-space programs            */
/************************************************************************/
#ifndef KERNEL_DRIVER_REQUIRED_CLASS
#include <kos/exec/elf.h>
#define KERNEL_DRIVER_REQUIRED_CLASS ELF_ARCH_CLASS
#endif /* !KERNEL_DRIVER_REQUIRED_CLASS */
#ifndef KERNEL_DRIVER_REQUIRED_MACHINE
#include <kos/exec/elf.h>
#define KERNEL_DRIVER_REQUIRED_MACHINE ELF_ARCH_MACHINE
#endif /* !KERNEL_DRIVER_REQUIRED_MACHINE */
#ifndef KERNEL_DRIVER_REQUIRED_DATA
#include <kos/exec/elf.h>
#define KERNEL_DRIVER_REQUIRED_DATA ELF_ARCH_DATA
#endif /* !KERNEL_DRIVER_REQUIRED_DATA */


/************************************************************************/
/* Substitute missing string representations                            */
/************************************************************************/
#ifndef KERNEL_DRIVER_REQUIRED_CLASS_S
#include <elf.h>
#define KERNEL_DRIVER_REQUIRED_CLASS_S \
	__ELF_CLASSNAME(KERNEL_DRIVER_REQUIRED_CLASS)
#endif /* !KERNEL_DRIVER_REQUIRED_CLASS_S */
#ifndef KERNEL_DRIVER_REQUIRED_MACHINE_S
#include <elf.h>
#define KERNEL_DRIVER_REQUIRED_MACHINE_S \
	__ELF_EMNAME(KERNEL_DRIVER_REQUIRED_MACHINE)
#endif /* !KERNEL_DRIVER_REQUIRED_MACHINE_S */
#ifndef KERNEL_DRIVER_REQUIRED_DATA_S
#include <elf.h>
#define KERNEL_DRIVER_REQUIRED_DATA_S \
	__ELF_DATANAME(KERNEL_DRIVER_REQUIRED_DATA)
#endif /* !KERNEL_DRIVER_REQUIRED_DATA_S */


/************************************************************************/
/* Default limit for program headers defined by drivers                 */
/************************************************************************/
#ifndef KERNEL_DRIVER_MAXPROGRAMHEADERCOUNT
#define KERNEL_DRIVER_MAXPROGRAMHEADERCOUNT 64
#endif /* !KERNEL_DRIVER_MAXPROGRAMHEADERCOUNT */


#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_ARCH_DRIVER_H */
