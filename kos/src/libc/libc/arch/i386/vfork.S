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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_VFORK_S
#define GUARD_LIBC_LIBC_ARCH_I386_VFORK_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include <cfi.h>
#include <asm/instr/compat.h>
#include <sys/syscall.h>

#include <errno.h> /* ELIMIT */

#ifndef __x86_64__
#define syscall int $(0x80)
#endif /* !__x86_64__ */


.section .text.crt.sched.access
INTERN_FUNCTION(libc_vfork)
	.cfi_startproc
	popP_cfi  %Pdx /* Return address */
	.cfi_register %Pip, %Pdx

	/* Invoke the vfork() system call. */
	movP   $(SYS_vfork), %Pax
	syscall

	/* Push the return address back onto the stack. */
	pushP_cfi %Pdx
	.cfi_rel_offset %Pip, 0

	/* Check for errors. */
	cmpP   $(-ELIMIT), %Pax
	ja     .Lvfork_error

	/* Return to our caller.
	 * HINT: If something went wrong in the child thread _after_ vfork()
	 *       already  succeeded, there's a  good chance that information
	 *       about that error is stored in our `errno' _right_ _now_! */
	ret

.Lvfork_error:
	/* Vfork error (within the parent)
	 * Note that we only get here when the vfork() _itself_ fails.
	 * We  _dont_ get here if something within the child after the
	 * vfork() fails. */
	movP   %Pax, %R_fcall0P
	EXTERN(libc_seterrno_neg)
	call   libc_seterrno_neg /* Returns -1 unconditionally in %Pax */
	ret

	.cfi_endproc
END(libc_vfork)

DEFINE_PUBLIC_ALIAS(vfork, libc_vfork)
DEFINE_PUBLIC_ALIAS(__vfork, libc_vfork)
DEFINE_PUBLIC_ALIAS(__libc_vfork, libc_vfork)


.section .text.crt.except.sched.access
INTERN_FUNCTION(libc_VFork)
	.cfi_startproc
	/* Encode CFI to clear EFLAGS.DF on exit
	 * Since exceptions are  enabled (thanks  to EFLAGS.DF=1),  the
	 * int80/syscall can result in an exception being thrown, which
	 * we must handle by  clearing `EFLAGS.DF' before returning  to
	 * our caller. (otherwise, stuff like `memcpy(3)' will break if
	 * the caller tries to use them) */
/*[[[cfi{register = '%Pflags'} push %Pflags; and ~$EFLAGS_DF]]]*/
#ifdef __x86_64__
	.cfi_escape 22,49,7,146,49,0,11,255,251,26
#else /* __x86_64__ */
	.cfi_escape 22,9,6,121,0,11,255,251,26
#endif /* !__x86_64__ */
/*[[[end]]]*/

	popP_cfi  %Pdx /* Return address */
	.cfi_register %Pip, %Pdx

	/* Invoke the vfork() system call. */
	movP   $(SYS_vfork), %Pax
	std /* Enable exceptions */
	syscall
	cld /* Disable exceptions */

	/* Return to the caller. */
	jmpP   *%Pdx
	.cfi_endproc
END(libc_VFork)

DEFINE_PUBLIC_ALIAS(VFork, libc_VFork)



#endif /* !GUARD_LIBC_LIBC_ARCH_I386_VFORK_S */
