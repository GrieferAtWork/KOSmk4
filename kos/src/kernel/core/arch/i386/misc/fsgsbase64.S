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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_FSGSBASE64_S
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_FSGSBASE64_S 1

#include <kernel/compiler.h>
#include <cfi.h>
#include <asm/cpu-flags.h>

#ifndef CONFIG_ASSUME_CPU_SUPPORTS_FSGSBASE
#ifndef __INTELLISENSE__

#define TARGET_REGISTER rax
#define TARGET_REGISTER_IS_RAX 1
#include "fsgsbase64-impl.S.inl"

#define TARGET_REGISTER rcx
#define TARGET_REGISTER_IS_RCX 1
#include "fsgsbase64-impl.S.inl"

#define TARGET_REGISTER rdx
#define TARGET_REGISTER_IS_RDX 1
#include "fsgsbase64-impl.S.inl"

#define TARGET_REGISTER rbx
#include "fsgsbase64-impl.S.inl"

#define TARGET_REGISTER rbp
#include "fsgsbase64-impl.S.inl"

/* Don't include rsp. - Even  though it's a GP  register, I can't see  any
 * situation where one could reasonable argue that using the stack pointer
 * for something like this is a good idead... */
/* #define TARGET_REGISTER rsp */
/* #include "fsgsbase64-impl.S.inl" */

#define TARGET_REGISTER rsi
#include "fsgsbase64-impl.S.inl"

#define TARGET_REGISTER rdi
#include "fsgsbase64-impl.S.inl"

#define TARGET_REGISTER r8
#include "fsgsbase64-impl.S.inl"

#define TARGET_REGISTER r9
#include "fsgsbase64-impl.S.inl"

#define TARGET_REGISTER r10
#include "fsgsbase64-impl.S.inl"

#define TARGET_REGISTER r11
#include "fsgsbase64-impl.S.inl"

#define TARGET_REGISTER r12
#include "fsgsbase64-impl.S.inl"

#define TARGET_REGISTER r13
#include "fsgsbase64-impl.S.inl"

#define TARGET_REGISTER r14
#include "fsgsbase64-impl.S.inl"

#define TARGET_REGISTER r15
#include "fsgsbase64-impl.S.inl"

#endif /* !__INTELLISENSE__ */
#endif /* !CONFIG_ASSUME_CPU_SUPPORTS_FSGSBASE */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_FSGSBASE64_S */
