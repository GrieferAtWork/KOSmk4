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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_FASTPASS64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_FASTPASS64_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#ifndef __INTELLISENSE__
/* 32-bit  in80h  has  the  most  restrictive  behavior  for   `SC_IRET'.
 * As such, we _must_ define it first, such that `SC_BEGIN_ALL_NOTHROW()'
 * system calls don't clobber registers that they are not allowed to when
 * call from 32-bit int80h! */
#define SYSCALL_FASTPASS_KIND_SYS32_INT80 1
#include "fastpass-impl.S"

#define SYSCALL_FASTPASS_KIND_SYS64 1
#include "fastpass-impl.S"

#define SYSCALL_FASTPASS_KIND_SYS32_SYSENTER 1
#include "fastpass-impl.S"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_FASTPASS64_S */
