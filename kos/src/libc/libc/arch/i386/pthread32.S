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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_PTHREAD32_S
#define GUARD_LIBC_LIBC_ARCH_I386_PTHREAD32_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include "../../pthread.h"
/**/

#include <hybrid/compiler.h>
#include <sched.h>
#include <asm/cfi.h>
#include <sys/syscall.h>



/* Assembly-side for the process of cloning a thread.
 * This function simply clones the calling thread before invoking
 * `libc_pthread_main()' within the context of the newly spawned thread.
 * NOTE: This function also fills in `thread->pt_tid' */
/* INTDEF errno_t NOTHROW(__FCALL libc_pthread_clone)(struct pthread *__restrict thread,
 *                                                    __pthread_start_routine_t start); */
.section .text.crt.sched.pthread.pthread_clone
INTERN_FUNCTION(libc_pthread_clone)
	.cfi_startproc

	/* Perform the system call with `lcall', since `int $0x80' would clobber all registers
	 * except for %ebp, however we need 2 registers to pass both `fn' and `arg' to the child
	 * thread. */
	leal   OFFSET_PTHREAD_TID(%ecx), %eax /* pid_t *ctid */
	pushl_cfi %eax                        /* ... */
	pushl_cfi OFFSET_PTHREAD_TLS(%ecx)    /* void *newtls */
	pushl_cfi %eax                        /* pid_t *ptid */
	movl   OFFSET_PTHREAD_STACKADDR(%ecx), %eax
	addl   OFFSET_PTHREAD_STACKSIZE(%ecx), %eax
	pushl_cfi %eax                        /* void *child_stack */
	/* int flags */
	pushl_cfi $(CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | \
	            CLONE_PARENT | CLONE_THREAD | CLONE_SYSVSEM | CLONE_SETTLS |       \
	            CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_CHILD_SETTID |       \
	            CLONE_IO | CLONE_PARENT_SETTID)
	lcall  $(7), $(SYS_clone)

	/* Check if we're inside of the child thread
	 * If so, just to pthread's thread entry point.
	 * Note that `%ecx' and `%edx' weren't clobbered, so the new
	 * thread will have automatically inherited them from us! */
	testl  %eax, %eax
	INTERN(libc_pthread_main)
	jz     libc_pthread_main

	addl   $(20), %esp  /* lcall-arguments */
	.cfi_adjust_cfa_offset -20

	ret
	.cfi_endproc
END(libc_pthread_clone)


/* INTDEF ATTR_NORETURN void __FCALL
 * libc_pthread_unmap_stack_and_exit(void *stackaddr,
 *                                   size_t stacksize,
 *                                   int exitcode); */
.section .text.crt.sched.pthread.pthread_unmap_stack_and_exit
INTERN_FUNCTION(libc_pthread_unmap_stack_and_exit)
	movl   4(%esp), %esp       /* int exitcode */
	movl   %ecx,          %ebx /* munmap:addr = void *stackaddr */
	movl   %edx,          %ecx /* munmap:len  = size_t stacksize */
	movl   $(SYS_munmap), %eax
	int    $(0x80)             /* unmap our own stack. */
	/* WARNING: No more accessing stack memory from here on! */

	movl   %esp,        %ebx   /* int exitcode */
	movl   $(SYS_exit), %eax
	int    $(0x80)
	/* -unreachable- */
END(libc_pthread_unmap_stack_and_exit)

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_PTHREAD32_S */
