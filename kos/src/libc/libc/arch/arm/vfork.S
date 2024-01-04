/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ARCH_ARM_VFORK_S
#define GUARD_LIBC_LIBC_ARCH_ARM_VFORK_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <asm/arm.h>
#include <kos/asm/syscall.h>
#include <sys/syscall.h>

#include <cfi.h>
#include <errno.h> /* ELIMIT */


.section ".text.crt.sched.access"
INTERN_FUNCTION(libc_vfork)
	.cfi_startproc
	/* Invoke the vfork() system call. */
	mov    r7, #SYS_vfork
	swi    #0

	/* Check for errors. */
	cmp    r0, #-ELIMIT
	bxlo   lr /* if ((unsigned)r0 < -ELIMIT) return r0; */

	/* Vfork error (within the parent)
	 * Note that we only get here when the vfork() _itself_ fails.
	 * We  _dont_ get here if something within the child after the
	 * vfork() fails. */
	EXTERN(libc_seterrno_neg)
	b      libc_seterrno_neg /* Returns -1 unconditionally in r0 */
	.cfi_endproc
END(libc_vfork)

DEFINE_PUBLIC_ALIAS(vfork, libc_vfork)
DEFINE_PUBLIC_ALIAS(__vfork, libc_vfork)
DEFINE_PUBLIC_ALIAS(__libc_vfork, libc_vfork)


.section ".text.crt.except.sched.access"
INTERN_FUNCTION(libc_VFork)
	.cfi_startproc
	ldreg  r7, ARM_XSYSCALL(SYS_vfork)
	swi    #0
	bx     lr
	.cfi_endproc
END(libc_VFork)
DEFINE_PUBLIC_ALIAS(VFork, libc_VFork)


#endif /* !GUARD_LIBC_LIBC_ARCH_ARM_VFORK_S */
