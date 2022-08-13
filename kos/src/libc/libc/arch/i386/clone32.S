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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_CLONE32_S
#define GUARD_LIBC_LIBC_ARCH_I386_CLONE32_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <cfi.h>
#include <sys/syscall.h>

#include <errno.h> /* ELIMIT */

/* >> INTERN NONNULL((1)) ATTR_SECTION(".text.crt.sched.access.clone") pid_t
 * >> NOTHROW_NCX(VLIBCCALL libc_clone)(__clone_func_t fn, void *child_stack,
 * >>                                   int flags, void *arg, pid_t *ptid,
 * >>                                   void *newtls, pid_t *ctid) */
.section .text.crt.sched.access
INTERN_FUNCTION(libc_clone)
	.cfi_startproc

	/* NOTE: Don't  use %eax for  argument passing! That register
	 *       is the only one that gets clobbered by lcall7, since
	 *       it will be set to 0 for the child thread. */
	movl   4(%esp),  %ecx /* __clone_func_t fn */
	movl   16(%esp), %edx /* void *arg */

	/* Perform the system call with `lcall',  since `int $0x80' would clobber all  registers
	 * except for %ebp, however we need 2 registers to pass both `fn' and `arg' to the child
	 * thread. */
	pushl_cfi  32(%esp) /* pid_t *ctid */
	pushl_cfi  32(%esp) /* void *newtls */
	pushl_cfi  32(%esp) /* pid_t *ptid */
	pushl_cfi  24(%esp) /* void *child_stack */
	pushl_cfi  32(%esp) /* int flags */
	lcall  $(7), $(SYS_clone)

	/* Check if we're inside of the child thread */
	testl  %eax, %eax
	jz     .Lthread_entry

	addl   $(20), %esp  /* lcall-arguments */
	.cfi_adjust_cfa_offset -20

	/* Check for errors. */
	cmpl   $(-ELIMIT), %eax
	ja     .Lthread_clone_error

	ret
.Lthread_clone_error:
	movl   %eax, %ecx
	INTERN(libc_seterrno_neg)
	call   libc_seterrno_neg
	ret
	.cfi_endproc

.Lthread_entry:
	/* %ecx: __clone_func_t fn */
	/* %edx: void          *arg */
	pushl  %edx              /* arg. */
	call   *%ecx             /* Invoke the thread's main function */
	movl   %eax, 0(%esp)     /* Thread exit code */
	call   libc_exit_thread  /* Exit the current thread */
END(libc_clone)

DEFINE_PUBLIC_ALIAS(clone, libc_clone)
DEFINE_PUBLIC_ALIAS(__clone, libc_clone)

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_CLONE32_S */
