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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_CLONE64_S
#define GUARD_LIBC_LIBC_ARCH_I386_CLONE64_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include <hybrid/compiler.h>

#include <cfi.h>
#include <sys/syscall.h>

#include <errno.h> /* ELIMIT */

/* >> INTERN NONNULL((1)) ATTR_SECTION(".text.crt.sched.access.clone") pid_t
 * >> NOTHROW_NCX(VLIBCCALL libc_clone)(%rdi:    __clone_func_t fn,
 * >>                                   %rsi:    void *child_stack,
 * >>                                   %rdx:    int flags,
 * >>                                   %rcx:    void *arg,
 * >>                                   %r8:     pid_t *ptid,
 * >>                                   %r9:     void *newtls,
 * >>                                   8(%rsp): pid_t *ctid) */
.section .text.crt.sched.access
INTERN_FUNCTION(libc_clone)
	.cfi_startproc
	/* We use %r14 and %r15 to pass arguments to the new thread,
	 * since those registers aren't used by the system call, and
	 * also don't get clobbered */
	pushq_cfi_r %r14
	pushq_cfi_r %r15
	movq   %rdi, %r14 /* __clone_func_t fn */
	movq   %rcx, %r15 /* void *arg */

	/* Transform arguments for the system call. */
	movq   %rdx,    %rdi /* flags */
/*	movq   %rsi,    %rsi  * void *child_stack */
	movq   %r8,     %rdx /* ptid */
	movq   8(%rsp), %r10 /* ctid */
	movq   %r9,     %r8  /* newtls */

	/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, pid_t *ctid, uintptr_t newtls) */
	movq   $(SYS_clone), %rax
	syscall

	/* Check if we're inside of the child thread */
	testq  %rax, %rax
	jz     .Lthread_entry

	popq_cfi_r %r15
	popq_cfi_r %r14

	/* Check for errors. */
	cmpq   $(-ELIMIT), %rax
	ja     .Lthread_clone_error

	ret
.Lthread_clone_error:
	movq   %rax, %rdi
	INTERN(libc_seterrno_neg)
	call   libc_seterrno_neg
	ret
	.cfi_endproc

.Lthread_entry:
	/* %r14: __clone_func_t fn */
	/* %r15: void *arg */
	movq   %r15, %rdi       /* arg. */
	call   *%r14            /* Invoke the thread's main function */
	movq   %rax, %rdi       /* Thread exit code */
	call   libc_exit_thread /* Exit the current thread */
END(libc_clone)

DEFINE_PUBLIC_ALIAS(clone, libc_clone)
DEFINE_PUBLIC_ALIAS(__clone, libc_clone)

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_CLONE64_S */
