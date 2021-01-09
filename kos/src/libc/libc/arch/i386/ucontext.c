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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT_C
#define GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT_C 1

#include "../../../api.h"
/**/

#include <hybrid/host.h>

#include <kos/types.h>

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>
/**/

DECL_BEGIN

DEFINE_PUBLIC_ALIAS(makecontext, libc_makecontext);
INTERN ATTR_SECTION(".text.crt.cpu.ucontext") NONNULL((1, 2)) void
NOTHROW_NCX(VLIBCCALL libc_makecontext)(ucontext_t *ucp,
                                        __makecontext_func_t func,
                                        __STDC_INT_AS_SIZE_T argc,
                                        ...) {
#ifdef __x86_64__
	(void)ucp;
	(void)func;
	(void)argc;
	/* TODO */
	abort();
#else /* __x86_64__ */
	byte_t *sp;
	extern byte_t const libc_x86_setcontext_edi[];      /* setcontext(%edi); */
	extern byte_t const libc_makecontext_exit_thread[]; /* pthread_exit(NULL); */
	/* We want to achieve the following layout:
	 *
	 * [...]       -- Available for use by `func'
	 * -(argc * 4) &libc_x86_setcontext_edi     (Return-handler)
	 * -(i * 4)    Function arguments.
	 */
	sp = (byte_t *)ucp->uc_stack.ss_sp + ucp->uc_stack.ss_size;
	sp -= argc * 4;
	/* Copy arguments onto the target stack. */
	sp = (byte_t *)memcpyl(sp, &argc + 1, argc);
	sp -= 4;
	*(u32 *)sp = (u32)libc_makecontext_exit_thread;
	if (ucp->uc_link) {
		*(u32 *)sp = (u32)libc_x86_setcontext_edi;
		/* Fill in %edi, which is required by `libc_x86_setcontext_edi()' */
		ucp->uc_mcontext.mc_context.ucs_gpregs.gp_edi = (u32)ucp->uc_link;
	}
	/* Assign the %eip and %esp registers. */
	ucp->uc_mcontext.mc_context.ucs_gpregs.gp_esp = (u32)(void *)sp;
	ucp->uc_mcontext.mc_context.ucs_eip           = (u32)(void *)func;
#endif /* !__x86_64__ */
}



DECL_END

#endif /* GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT_C */
