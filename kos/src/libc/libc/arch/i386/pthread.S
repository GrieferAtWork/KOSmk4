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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_PTHREAD_S
#define GUARD_LIBC_LIBC_ARCH_I386_PTHREAD_S 1
#define __ASSEMBLER__ 1
#define _KOS_KERNEL_SOURCE 1

#include "../../../api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <cfi.h>
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
.section .text.crt.sched.pthread.core.thread
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
#if 1 /* https://sourceware.org/pipermail/binutils-cvs/2024-September/065790.html
       * TODO: Figure out a way to work around this! */
	movP   %Pax, %Pcx
	leaP   current@tlsgd(%Pcx), %Pax
	movP   (%Pax), %Pax
#else
	movP   current@tlsgd(,%Pax,1), %Pax
#endif
	ret
	.cfi_endproc
END(libc_handle)
#endif /* __x86_64__ */




/* Assembly-side for the process of cloning a thread. */
/* >> INTERN NONNULL((1, 2)) pid_t
 * >> NOTHROW(__FCALL libc_pthread_clone)(struct pthread_clone_args *__restrict args,
 * >>                                     struct pthread *__restrict thread); */
.section .text.crt.sched.pthread.core.thread
INTERN_FUNCTION(libc_pthread_clone)
	.cfi_startproc
#ifndef __x86_64__
	pushP_cfi_r %Pbx /* For `R_syscall0P' */
	pushP_cfi_r %Pdi /* For `void *(LIBCCALL start)(void *arg)' */
#endif /* !__x86_64__ */

	/* Load argument 0: `struct clone_args *args' */
#ifdef __x86_64__
	movP   %R_fcall1P,                    %Pdx /* %Pdx = %Psi                    -- struct pthread *__restrict thread */
	movP   SIZEOF_CLONE_ARGS(%R_fcall0P), %r8  /* %r10 = SIZEOF_CLONE_ARGS(%Pdi) -- void *(LIBCCALL start)(void *arg) */
/*	movP   %R_fcall0P, %R_syscall0P */         /* %Pdi = %Pdi */
#else /* __x86_64__ */
/*	movP   %R_fcall1P, %Pdx */                 /* %Pdx = %Pdx                    -- struct pthread *__restrict thread */
	movP   SIZEOF_CLONE_ARGS(%R_fcall0P), %Pdi /* %Pdi = SIZEOF_CLONE_ARGS(%Pdi) -- void *(LIBCCALL start)(void *arg) */
	movP   %R_fcall0P, %R_syscall0P            /* %Pbx = %Pcx */
#endif /* !__x86_64__ */

	/* Load argument 1: `size_t size' */
	movP   $(SIZEOF_CLONE_ARGS), %R_syscall1P

	/* Perform the system call */
	movP   $(SYS_clone3), %Pax
	syscall /* NOTE: Can't use `libc___i386_syscall', because that one needs
	         * the stack (which the child doesn't have upon syscall  return) */

#ifndef __x86_64__
	/* Load missing FCALL argument for `libc_pthread_main': */
	movP   %Pdi, %Pcx /* %Pcx = void *(LIBCCALL start)(void *arg) */
#endif /* !__x86_64__ */

	/* Check  if we're inside  of the child thread.
	 * If so, jump to pthread's thread entry point.
	 * Note that `%ecx' and `%edx' weren't clobbered, so the new
	 * thread will have  automatically inherited  them from  us! */
	testP  %Pax, %Pax
	INTERN(libc_pthread_main)
	jz     libc_pthread_main

#ifndef __x86_64__
	popP_cfi_r %Pdi /* For `void *(LIBCCALL start)(void *arg)' */
	popP_cfi_r %Pbx /* For `R_syscall0P' */
#endif /* !__x86_64__ */
	ret
	.cfi_endproc
END(libc_pthread_clone)


/* >> INTDEF ATTR_NORETURN void FCALL
 * >> libc_pthread_unmap_stack_and_exit(void  *stackaddr,
 * >>                                   size_t stacksize,
 * >>                                   int    exitcode); */
.section .text.crt.sched.pthread.core.exit
INTERN_FUNCTION(libc_pthread_unmap_stack_and_exit)
	/* NOTE: We  must use `int 80h' for syscalls here, since the (more efficient)
	 *       method of using `__i386_syscall()' would require use of stack memory
	 *       _after_ we've already unmapped the stack. */

#ifdef __x86_64__
	movq   %R_sysvabi2P, %Psp          /* %Psp = %Pdx -- int exitcode */
#else /* __x86_64__ */
	movP   PS(%Psp), %Psp              /* %Psp = ...  -- int exitcode */
#endif /* !__x86_64__ */

#ifdef __x86_64__
//	movP   %R_sysvabi0P, %R_syscall0P  /* %Pdi = %Pdi -- munmap:addr = void *stackaddr */
//	movP   %R_sysvabi1P, %R_syscall1P  /* %Psi = %Psi -- munmap:len  = size_t stacksize */
#else /* __x86_64__ */
	movP   %R_fcall0P, %R_syscall0P    /* %Pbx = %Pcx -- munmap:addr = void *stackaddr */
	movP   %R_fcall1P, %R_syscall1P    /* %Pcx = %Pdx -- munmap:len  = size_t stacksize */
#endif /* !__x86_64__ */

	movP   $(SYS_munmap), %Pax
	syscall                    /* unmap our own stack. */

	/* WARNING: No more accessing stack memory from here on! */

1:	movP   %Psp,        %R_syscall0P /* int exitcode */
	movP   $(SYS_exit), %Pax
	syscall

	/* -unreachable- */
	hlt
	jmp    1b
END(libc_pthread_unmap_stack_and_exit)

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_PTHREAD_S */
