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
#ifndef GUARD_LIBC_LIBC_ARCH_ARM_CLONE_S
#define GUARD_LIBC_LIBC_ARCH_ARM_CLONE_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <asm/arm.h>

#include <cfi.h>

/* >> INTERN NONNULL((1)) ATTR_SECTION(".text.crt.sched.access.clone") pid_t
 * >> NOTHROW_NCX(VLIBCCALL libc_clone)(__clone_func_t fn, void *child_stack,
 * >>                                   int flags, void *arg, pid_t *ptid,
 * >>                                   void *newtls, pid_t *ctid) */
.section .text.crt.sched.access
INTERN_FUNCTION(libc_clone)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_clone)

DEFINE_PUBLIC_ALIAS(clone, libc_clone)
DEFINE_PUBLIC_ALIAS(__clone, libc_clone)

#endif /* !GUARD_LIBC_LIBC_ARCH_ARM_CLONE_S */
