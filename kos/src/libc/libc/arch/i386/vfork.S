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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_VFORK_S
#define GUARD_LIBC_LIBC_ARCH_I386_VFORK_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include <asm/cfi.h>
#include <asm/instr/compat.h>
#include <sys/syscall.h>

#include <errno.h> /* ELIMIT */


.section .text.crt.sched.access
INTERN_FUNCTION(libc_vfork)
	.cfi_startproc
	popP_cfi  %Pdx /* Return address */
	.cfi_register %Pip, %Pdx

	/* Invoke the vfork() system call. */
	movP   $(SYS_vfork), %Pax
#ifdef __x86_64__
	syscall
#else /* __x86_64__ */
	int    $(0x80)
#endif /* !__x86_64__ */

	/* Push the return address back onto the stack. */
	pushP_cfi %Pdx
	.cfi_rel_offset %Pip, 0

	/* Check for errors. */
	cmpP   $(-ELIMIT), %Pax
	ja     .Lvfork_error

	/* Return to our caller.
	 * HINT: If something went wrong in the child thread _after_ vfork()
	 *       already succeeded, there's a good chance that information
	 *       about that error is stored in our `errno' _right_ _now_! */
	ret

.Lvfork_error:
	/* Vfork error (within the parent)
	 * Note that we only get here when the vfork() _itself_ fails.
	 * We _dont_ get here if something within the child after the
	 * vfork() fails. */
	negP   %Pax
	movP   %Pax, %R_fcall0P
	EXTERN(libc_seterrno)
	call   libc_seterrno /* Returns -1 unconditionally in %Pax */
	ret

	.cfi_endproc
END(libc_vfork)

DEFINE_PUBLIC_ALIAS(vfork, libc_vfork)
DEFINE_PUBLIC_ALIAS(__vfork, libc_vfork)


.section .text.crt.except.sched.access
INTERN_FUNCTION(libc_VFork)
	.cfi_startproc
	popP_cfi  %Pdx /* Return address */
	.cfi_register %Pip, %Pdx

	/* Invoke the vfork() system call. */
	movP   $(SYS_vfork), %Pax
	std /* Enable exceptions */
#ifdef __x86_64__
	syscall
#else /* __x86_64__ */
	int    $(0x80)
#endif /* !__x86_64__ */
	cld /* Disable exceptions */

	/* Return to the caller. */
	jmpP   *%Pdx
	.cfi_endproc
END(libc_VFork)

DEFINE_PUBLIC_ALIAS(VFork, libc_VFork)



#endif /* !GUARD_LIBC_LIBC_ARCH_I386_VFORK_S */
