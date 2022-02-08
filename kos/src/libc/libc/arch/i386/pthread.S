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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_PTHREAD_S
#define GUARD_LIBC_LIBC_ARCH_I386_PTHREAD_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include "../../../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <asm/cfi.h>
#include <asm/instr/compat.h>
#include <sys/syscall.h>

#include <pthread.h>
#include <sched.h>


#define PS __SIZEOF_POINTER__
#ifndef SIZEOF_CLONE_ARGS
#define SIZEOF_CLONE_ARGS __SIZEOF_CLONE_ARGS
#endif /* !SIZEOF_CLONE_ARGS */

#ifndef __x86_64__
#define syscall int $(0x80)
#endif /* !__x86_64__ */


#ifndef __x86_64__
.section .text.crt.sched.pthread
INTERN_FUNCTION(libc_handle)
	.cfi_startproc
	/* Hacky code to quickly get a DL handle for libc itself. */
	call   1f
	.cfi_adjust_cfa_offset PS
1:	popP_cfi %Pax
	addP   $(_GLOBAL_OFFSET_TABLE_ + (. - 1b)), %Pax

	/* The `current@tlsgd' symbol points to a `tls_index' structure,
	 * which consists of 8 bytes total, where the first 4 are filled
	 * with a module handle pointer by libdl.
	 * Note that this is a KOS-specific implementation detail. As far
	 * as the standard is concerned, libdl is allowed to make up some
	 * arbitrary module index for those 4 bytes, however KOS's  libdl
	 * simply re-uses  the regular  module handle  for this  purpose,
	 * meaning that we can simply (ab-)use that fact to quickly get a
	 * handle for libc itself. */
	INTERN(current)
	movP   current@tlsgd(,%Pax,1), %Pax
	ret
	.cfi_endproc
END(libc_handle)
#endif /* __x86_64__ */




/* Assembly-side for the process of cloning a thread. */
/* >> INTERN NONNULL((1, 2)) pid_t
 * >> NOTHROW(__FCALL libc_pthread_clone)(struct pthread_clone_args *__restrict args,
 * >>                                     struct pthread *__restrict thread); */
.section .text.crt.sched.pthread
INTERN_FUNCTION(libc_pthread_clone)
	.cfi_startproc
#ifndef __x86_64__
	pushP_cfi_r %Pbx                          /* For `R_syscall0P' */
#endif /* !__x86_64__ */

	/* Load argument 0: `struct clone_args *args' */
#ifdef __x86_64__
	movP   %R_fcall1P, %Pdx                   /* %Pdx = %Psi (struct pthread *__restrict thread) */
/*	movP   %R_fcall0P, %R_syscall0P */        /* %Pdi = %Pdi */
#else /* __x86_64__ */
/*	movP   %R_fcall1P, %Pdx */                /* %Pdx = %Pdx (struct pthread *__restrict thread) */
	movP   %R_fcall0P, %R_syscall0P           /* %Pbx = %Pcx */
#endif /* !__x86_64__ */

	/* Load argument 1: `size_t size' */
	movP   $(SIZEOF_CLONE_ARGS), %R_syscall1P

	/* Perform the system call */
	movP   $(SYS_clone3), %Pax
	syscall /* NOTE: Can't use `libc___i386_syscall', because that one needs
	         * the stack (which the child doesn't have upon syscall  return) */

	/* Load FCALL arguments for `libc_pthread_main' */
#ifdef __x86_64__
	movP   SIZEOF_CLONE_ARGS(%R_syscall0P), %R_fcall1P /* %Psi = SIZEOF_CLONE_ARGS(%Pdi) -- void *(LIBCCALL start)(void *arg) */
	movP   %Pdx,                            %R_fcall0P /* %Pdi = %Pdx                    -- struct pthread *__restrict me */
#else /* __x86_64__ */
	movP   %Pdx,                            %R_fcall0P /* %Pcx = %Pdx                    -- struct pthread *__restrict me */
	movP   SIZEOF_CLONE_ARGS(%R_syscall0P), %R_fcall1P /* %Pdx = SIZEOF_CLONE_ARGS(%Pbx) -- void *(LIBCCALL start)(void *arg) */
#endif /* !__x86_64__ */

	/* Check  if we're inside  of the child thread.
	 * If so, jump to pthread's thread entry point.
	 * Note that `%ecx' and `%edx' weren't clobbered, so the new
	 * thread will have  automatically inherited  them from  us! */
	testP  %Pax, %Pax
	INTERN(libc_pthread_main)
	jz     libc_pthread_main

#ifndef __x86_64__
	popP_cfi_r %Pbx                           /* For `R_syscall0P' */
#endif /* !__x86_64__ */
	ret
	.cfi_endproc
END(libc_pthread_clone)


.section .text.crt.sched.pthread
INTERN_FUNCTION(libc_pthread_unmap_stack_and_exit)
#ifdef __x86_64__
	/* INTDEF ATTR_NORETURN void __FCALL
	 * libc_pthread_unmap_stack_and_exit(%rdi: void *stackaddr,
	 *                                   %rsi: size_t stacksize,
	 *                                   %rdx: int exitcode); */
	movq   %rdx, %rbp          /* int exitcode */
	movq   $(SYS_munmap), %rax
	syscall                    /* unmap our own stack. */
	/* WARNING: No more accessing stack memory from here on! */

	movq   %rbp,        %rdi   /* int exitcode */
	movq   $(SYS_exit), %rax
	syscall
#else /* __x86_64__ */
	/* INTDEF ATTR_NORETURN void __FCALL
	 * libc_pthread_unmap_stack_and_exit(void *stackaddr,
	 *                                   size_t stacksize,
	 *                                   int    exitcode); */
	/* NOTE: We  must use `int 80h' for syscalls here, since the (more efficient)
	 *       method of using `__i386_syscall()' would require use of stack memory
	 *       _after_ we've already unmapped the stack. */
	movl   4(%esp), %esp       /* int exitcode */
	movl   %ecx,          %ebx /* munmap:addr = void *stackaddr */
	movl   %edx,          %ecx /* munmap:len  = size_t stacksize */
	movl   $(SYS_munmap), %eax
	int    $(0x80)             /* unmap our own stack. */
	/* WARNING: No more accessing stack memory from here on! */

	movl   %esp,        %ebx   /* int exitcode */
	movl   $(SYS_exit), %eax
	int    $(0x80)
#endif /* !__x86_64__ */
	/* -unreachable- */
	hlt
END(libc_pthread_unmap_stack_and_exit)

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_PTHREAD_S */
