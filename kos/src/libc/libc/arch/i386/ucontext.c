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

INTERN ATTR_SECTION(".text.crt.cpu.ucontext") NONNULL((1, 2)) void
NOTHROW_NCX(VLIBCCALL libc_makecontext)(ucontext_t *ucp,
                                        void (LIBKCALL *func)(void),
                                        __STDC_INT_AS_SIZE_T argc,
                                        ...) {
#ifdef __x86_64__
	byte_t *sp;
	va_list args;
	extern byte_t const libc_x86_setcontext_rbp[];      /* setcontext(%rbx); */
	extern byte_t const libc_makecontext_exit_thread[]; /* pthread_exit(NULL); */
	sp = (byte_t *)ucp->uc_stack.ss_sp + ucp->uc_stack.ss_size;
	va_start(args, argc);
	/* Load arguments into registers/push onto the stack.
	 * NOTE: POSIX requires us to  load int-values, but binary  compatibility
	 *       can also be ensured if we instead load 64-bit (and thus: pointer
	 *       sized)  values, thus allowing  non-portable programs to directly
	 *       pass pointers to makecontext callback functions. */
	if (argc) {
		ucp->uc_mcontext.mc_context.ucs_gpregs.gp_rdi = va_arg(args, u64);
		--argc;
	}
	if (argc) {
		ucp->uc_mcontext.mc_context.ucs_gpregs.gp_rsi = va_arg(args, u64);
		--argc;
	}
	if (argc) {
		ucp->uc_mcontext.mc_context.ucs_gpregs.gp_rdx = va_arg(args, u64);
		--argc;
	}
	if (argc) {
		ucp->uc_mcontext.mc_context.ucs_gpregs.gp_rcx = va_arg(args, u64);
		--argc;
	}
	if (argc) {
		ucp->uc_mcontext.mc_context.ucs_gpregs.gp_r8 = va_arg(args, u64);
		--argc;
	}
	if (argc) {
		ucp->uc_mcontext.mc_context.ucs_gpregs.gp_r9 = va_arg(args, u64);
		--argc;
	}
	/* All  remaining  arguments   must  be  pushed   onto  the   stack.
	 * Because `va_arg()' enumerates in forward order, we must also push
	 * arguments in that same order, too! */
	if (argc) {
		unsigned int i;
		sp -= argc * 8;
		for (i = 0; i < argc; ++i) {
			((u64 *)sp)[i] = va_arg(args, u64);
		}
	}
	va_end(args);

	/* Arguments have been loaded into the appropriate locations! */
	sp -= 8; /* Return address */
	*(u64 *)sp = (u64)libc_makecontext_exit_thread;
	if (ucp->uc_link) {
		*(u64 *)sp = (u64)libc_x86_setcontext_rbp;
		/* Fill in `%rbp', which is required by `libc_x86_setcontext_rbp()' */
		ucp->uc_mcontext.mc_context.ucs_gpregs.gp_rbp = (u64)ucp->uc_link;
	}

	/* Assign the %rip and %rsp registers. */
	ucp->uc_mcontext.mc_context.ucs_gpregs.gp_rsp = (u64)(void *)sp;
	ucp->uc_mcontext.mc_context.ucs_rip           = (u64)(void *)func;
#else /* __x86_64__ */
	byte_t *sp;
	extern byte_t const libc_x86_setcontext_ebp[];      /* setcontext(%ebp); */
	extern byte_t const libc_makecontext_exit_thread[]; /* pthread_exit(NULL); */
	/* We want to achieve the following layout:
	 *
	 * [...]       -- Available for use by `func'
	 * -(argc * 4) &libc_x86_setcontext_ebp     (Return-handler)
	 * -(i * 4)    Function arguments.
	 */
	sp = (byte_t *)ucp->uc_stack.ss_sp + ucp->uc_stack.ss_size;
	sp -= argc * 4;
	/* Copy arguments onto the target stack. */
	{
		void const *p = &argc + 1;
		COMPILER_DELETE_ASSUMPTIONS(p); /* We're not supposed to do this, so /hush/ */
		sp = (byte_t *)memcpyl(sp, p, argc);
	}
	sp -= 4;
	*(u32 *)sp = (u32)libc_makecontext_exit_thread;
	if (ucp->uc_link) {
		*(u32 *)sp = (u32)libc_x86_setcontext_ebp;
		/* Fill in `%ebp', which is required by `libc_x86_setcontext_ebp()' */
		ucp->uc_mcontext.mc_context.ucs_gpregs.gp_ebp = (u32)ucp->uc_link;
	}
	/* Assign the %eip and %esp registers. */
	ucp->uc_mcontext.mc_context.ucs_gpregs.gp_esp = (u32)(void *)sp;
	ucp->uc_mcontext.mc_context.ucs_eip           = (u32)(void *)func;
#endif /* !__x86_64__ */
}

DEFINE_PUBLIC_ALIAS(makecontext, libc_makecontext);

DECL_END

#endif /* GUARD_LIBC_LIBC_ARCH_I386_UCONTEXT_C */
