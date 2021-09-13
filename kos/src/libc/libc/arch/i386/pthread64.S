/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ARCH_I386_PTHREAD64_S
#define GUARD_LIBC_LIBC_ARCH_I386_PTHREAD64_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include "../../../api.h"
/**/

#include <hybrid/compiler.h>

#include <asm/cfi.h>
#include <sys/syscall.h>

#include <pthread.h>
#include <sched.h>


/* Assembly-side for the process of cloning a thread.
 * This function  simply  clones  the  calling  thread  before  invoking
 * `libc_pthread_main()' within the context of the newly spawned thread.
 * NOTE: This function also fills in `thread->pt_tid' */
/* INTDEF errno_t NOTHROW(__FCALL libc_pthread_clone)(struct pthread *__restrict thread,
 *                                                    void *(LIBCCALL start)(void *arg)); */
.section .text.crt.sched.pthread
INTERN_FUNCTION(libc_pthread_clone)
	.cfi_startproc

	/* We use %r14 and %r15 to pass arguments to the new thread,
	 * since those registers aren't used by the system call, and
	 * also don't get clobbered */
	pushq_cfi_r %r14
	pushq_cfi_r %r15
	movq   %rdi, %r14 /* struct pthread *__restrict thread */
	movq   %rsi, %r15 /* void *(LIBCCALL start)(void *arg) */

	movq   __OFFSET_PTHREAD_TLS(%rdi), %r8        /* void *newtls */
#if __OFFSET_PTHREAD_TID == 0
	movq   %rdi, %rdx                             /* pid_t *ptid */
#else /* __OFFSET_PTHREAD_TID == 0 */
	leaq   __OFFSET_PTHREAD_TID(%rdi), %rdx       /* pid_t *ptid */
#endif /* __OFFSET_PTHREAD_TID != 0 */
	movq   %rdx, %r10                             /* pid_t *ctid */
	movq   __OFFSET_PTHREAD_STACKADDR(%rdi), %rsi
	addq   __OFFSET_PTHREAD_STACKSIZE(%rdi), %rsi /* void *child_stack */
	movq   $(CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | \
	         CLONE_PARENT | CLONE_THREAD | CLONE_SYSVSEM | CLONE_SETTLS |       \
	         CLONE_CHILD_CLEARTID | CLONE_DETACHED  | CLONE_CHILD_SETTID |      \
	         CLONE_IO | CLONE_PARENT_SETTID | CLONE_CRED), \
	       %rdi /* int flags */
	/* pid_t clone(syscall_ulong_t flags, void *child_stack, pid_t *ptid, pid_t *ctid, uintptr_t newtls) */
	movq   $(SYS_clone), %rax
	syscall

	/* Check  if we're inside  of the child thread.
	 * If so, jump to pthread's thread entry point. */
	testq  %rax, %rax
	jnz    1f
	movq   %r14, %rdi /* struct pthread *__restrict thread */
	movq   %r15, %rsi /* void *(LIBCCALL start)(void *arg) */
	INTERN(libc_pthread_main)
	jmp    libc_pthread_main

1:	popq_cfi_r %r15
	popq_cfi_r %r14
	ret
	.cfi_endproc
END(libc_pthread_clone)


/* INTDEF ATTR_NORETURN void __FCALL
 * libc_pthread_unmap_stack_and_exit(%rdi: void *stackaddr,
 *                                   %rsi: size_t stacksize,
 *                                   %rdx: int exitcode); */
.section .text.crt.sched.pthread
INTERN_FUNCTION(libc_pthread_unmap_stack_and_exit)
	movq   %rdx, %rbp          /* int exitcode */
	movq   $(SYS_munmap), %rax
	syscall                    /* unmap our own stack. */
	/* WARNING: No more accessing stack memory from here on! */

	movq   %rbp,        %rdi   /* int exitcode */
	movq   $(SYS_exit), %rax
	syscall
	/* -unreachable- */
	hlt
END(libc_pthread_unmap_stack_and_exit)

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_PTHREAD64_S */
