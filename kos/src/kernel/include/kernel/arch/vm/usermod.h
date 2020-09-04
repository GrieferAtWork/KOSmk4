/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_ARCH_VM_USERMOD_H
#define GUARD_KERNEL_INCLUDE_KERNEL_ARCH_VM_USERMOD_H 1

#include <kernel/compiler.h>

#include <kos/exec/elf.h> /* ELF_ARCH_CLASS */

#include <elf.h> /* ELF_ARCH_CLASS */

/* Default user-module type codes. */
#if ELF_ARCH_CLASS == ELFCLASS32
#define USERMOD_TYPE_ELF32      0
#define USERMOD_TYPE_ISELF32(x) 1
#elif ELF_ARCH_CLASS == ELFCLASS64
#define USERMOD_TYPE_ELF64      0
#define USERMOD_TYPE_ISELF64(x) 1
#else /* ELF_ARCH_CLASS == ... */
#error "Unsupported `ELF_ARCH_CLASS'"
#endif /* ELF_ARCH_CLASS != ... */
#define USERMOD_TYPE_ARCHMAX  0
#define USERMOD_TYPE_ISELF(x) 1

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_ARCH_VM_USERMOD_H */
