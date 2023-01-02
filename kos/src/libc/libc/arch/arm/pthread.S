/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ARCH_ARM_PTHREAD_S
#define GUARD_LIBC_LIBC_ARCH_ARM_PTHREAD_S 1
#define __ASSEMBLER__ 1

#include "../../../api.h"
/**/

#include <hybrid/compiler.h>

#include <asm/arm.h>
#include <sys/syscall.h>

#include <cfi.h>


/* Assembly-side for the process of cloning a thread. */
/* >> INTERN NONNULL((1, 2)) pid_t
 * >> NOTHROW(__FCALL libc_pthread_clone)(struct pthread_clone_args *__restrict args,
 * >>                                     struct pthread *__restrict thread); */
.section .text.crt.sched.pthread
INTERN_FUNCTION(libc_pthread_clone)
	.cfi_startproc
	b      . /* TODO */
	.cfi_endproc
END(libc_pthread_clone)


/* >> INTDEF ATTR_NORETURN void FCALL
 * >> libc_pthread_unmap_stack_and_exit(void  *stackaddr,
 * >>                                   size_t stacksize,
 * >>                                   int    exitcode); */
.section .text.crt.sched.pthread
INTERN_FUNCTION(libc_pthread_unmap_stack_and_exit)
	mov    r7, #SYS_munmap
	swi    #0                    /* unmap our own stack. */

	/* WARNING: No more accessing stack memory from here on! */

	mov    r0, r2                /* int exitcode */
	mov    r7, #SYS_exit
	swi    #0

	/* -unreachable- */
	b      .
END(libc_pthread_unmap_stack_and_exit)

#endif /* !GUARD_LIBC_LIBC_ARCH_ARM_PTHREAD_S */
