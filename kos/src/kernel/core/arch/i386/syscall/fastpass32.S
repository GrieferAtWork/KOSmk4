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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_FASTPASS32_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_FASTPASS32_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kernel/syscall.h>
#include <kernel/x86/syscall-tables.h>

#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>
#include <kos/kernel/paging.h>

#include <fcntl.h>
#include <syscall.h>

#ifndef __INTELLISENSE__
#define SYSCALL_DEFMODE_INT80 1
#include "fastpass32-impl.S.inl"
#define SYSCALL_DEFMODE_SYSENTER 1
#include "fastpass32-impl.S.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_FASTPASS32_S */
