/*[[[magic
// Disable optimizations in this file! We do some shady stuff below to call
// external functions, and we can't have the compiler screw with assumptions
// made that can be broken when optimizations are enabled.
local opt = options.setdefault("GCC.options", []);
opt.removeif(e -> e.startswith("-O"));
]]]*/
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
#ifndef GUARD_MODDBX_CEXPR_C
#define GUARD_MODDBX_CEXPR_C 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

#include <debugger/rt.h>
#include <kernel/mman.h>
#include <kernel/paging.h>
#include <sched/pertask.h>

#include <hybrid/align.h>
#include <hybrid/host.h>

#include <kos/except.h>
#include <kos/kernel/cpu-state.h>
#include <kos/types.h>

#include <cfi.h>
#include <intrin.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libcpustate/apply.h>

/**/
#include "include/cexpr.h"
#include "include/ctype.h"
#include "include/error.h"

#if defined(__x86_64__) || defined(__i386__)
#include <kos/kernel/x86/gdt.h>
#endif /* __x86_64__ || __i386__ */

DECL_BEGIN

/* Low-level implementation for `cfunction_call' */
PRIVATE NONNULL((4, 5)) dbx_errno_t
NOTHROW(KCALL cfunction_call_impl)(void const *func_address, uintptr_half_t cc,
                                   size_t argc, struct cvalue *argv,
                                   struct ctype *__restrict return_type,
                                   void *__restrict return_buf) {
	/************************************************************************/
	/* X86_64                                                               */
	/************************************************************************/
#ifdef __x86_64__
	/* TODO */
#endif /* __x86_64__ */

	/************************************************************************/
	/* I386                                                                 */
	/************************************************************************/
#if !defined(__x86_64__) && defined(__i386__)
#define HAVE_CFUNCTION_CALL
	dbx_errno_t error;
	size_t i, argv_space;
	struct ucpustate uc;
	byte_t *orig_sp, *sp, *sp_writer;
	uint64_t result;
	bool return_is_injected_argument;
#define is_double_wide_argument(typ)                        \
	(CTYPE_KIND_ISINT_OR_BOOL_OR_POINTER((typ)->ct_kind) && \
	 ((typ)->ct_kind & CTYPE_KIND_SIZEMASK) > 4)

	/* Figure out how much space we need for arguments. */
	argv_space = 0;
	return_is_injected_argument = !CTYPE_KIND_ISVOID(return_type->ct_kind) &&
	                              !CTYPE_KIND_ISINT_OR_BOOL_OR_POINTER(return_type->ct_kind);
	if (return_is_injected_argument)
		argv_space += 4; /* Inject a leading argument that is the return-pointer */
	for (i = 0; i < argc; ++i) {
		struct ctype *arg_type = argv[i].cv_type.ct_typ;
		if (CTYPE_KIND_ISARRAY_OR_STRUCT(arg_type->ct_kind)) {
			/* Inline struct argument */
			argv_space += ctype_sizeof(arg_type);
			argv_space = CEIL_ALIGN(argv_space, 4);
		} else {
			argv_space += 4;
			if (is_double_wide_argument(arg_type))
				argv_space += 4; /* Double-wide argument */
		}
	}
	argv_space += 4; /* +4 for saved %eip */
	argv_space += 4; /* +4 for saved %ebx */
	argv_space += 4; /* +4 for saved %edi */
	argv_space += 4; /* +4 for saved %esi */
	argv_space += 4; /* +4 for saved %ebp */

	/* Allocate stack memory.
	 * Note that we can't use `alloca()' here since we have to ensure that `%esp == sp' */
	orig_sp = (byte_t *)__builtin_stack_save();
	sp      = (byte_t *)orig_sp - argv_space;
	__builtin_stack_restore(sp);
	sp_writer = sp;
	if (return_is_injected_argument) {
		*(uint32_t *)sp_writer = (uint32_t)return_buf;
		sp_writer += 4;
	}

	/* Load arguments onto the stack. */
	for (i = 0; i < argc; ++i) {
		byte_t *arg_data;
		size_t arg_size, param_size;
		struct ctype *arg_type;
		arg_type = argv[i].cv_type.ct_typ;
		error = cexpr_getdata_ex(&argv[i], &arg_data);
		if unlikely(error != DBX_EOK) {
			__builtin_stack_restore(sp);
			return error;
		}
		arg_size   = cexpr_getsize_ex(&argv[i]);
		param_size = 4;
		if (CTYPE_KIND_ISARRAY_OR_STRUCT(arg_type->ct_kind)) {
			param_size = ctype_sizeof(arg_type); /* Inline struct argument */
			param_size = CEIL_ALIGN(param_size, 4);
		} else if (is_double_wide_argument(arg_type)) {
			param_size = 8; /* Double-wide register */
		}
		if (arg_size > param_size)
			arg_size = param_size;
		bzero(sp_writer, param_size);
		memcpy(sp_writer, arg_data, arg_size);
		sp_writer += param_size;
	}

	/* Also pass the first 2 arguments in registers */
	bzero(&uc, sizeof(uc));
	uc.ucs_gpregs.gp_ecx = ((uint32_t *)sp)[0]; /* For `__attribute__((fastcall))' */
	uc.ucs_gpregs.gp_edx = ((uint32_t *)sp)[1]; /* For `__attribute__((fastcall))' */
	uc.ucs_gpregs.gp_eax = ((uint32_t *)sp)[0]; /* For `__attribute__((regparm(1)))' */

	/* For FASTCALL, the first 2 arguments aren't passed via the stack. */
	if (cc == CTYPE_KIND_FUNPROTO_CC_FASTCALL) {
		if (argc >= 2) {
			sp += 8;
		} else if (argc >= 1) {
			sp += 4;
		}
	}

	/* Fill in fixed registers. */
	uc.ucs_gpregs.gp_esp = (uint32_t)sp - 4;    /* -4 addend needed for return address. */
	uc.ucs_gpregs.gp_ebp = (uint32_t)sp_writer; /* Needed so we can restore registers. */
	uc.ucs_sgregs.sg_ds  = SEGMENT_USER_DATA_RPL;
	uc.ucs_sgregs.sg_es  = SEGMENT_USER_DATA_RPL;
	uc.ucs_sgregs.sg_fs  = SEGMENT_KERNEL_FSBASE;
	uc.ucs_sgregs.sg_gs  = SEGMENT_USER_GSBASE_RPL;
	uc.ucs_ss            = SEGMENT_KERNEL_DATA;
	uc.ucs_cs            = SEGMENT_KERNEL_CODE;
	uc.ucs_eflags        = __rdflags();
	uc.ucs_eip           = (uint32_t)func_address;

	/* TODO: Instead of trying to do the context restore
	 *       here dynamically, why not do so statically?
	 * - The debugger is single-threaded, so we can use a global state
	 * - By using a global state, we wouldn't rely on the called function preserving `%ebp'
	 */
	TRY {
		__asm__ __volatile__(".pushsection .text.cold\n"
		                     ".global __dbx_i386_invoke_cfunction\n"
		                     ".hidden __dbx_i386_invoke_cfunction\n"
		                     "__dbx_i386_invoke_cfunction:\n"
		                     "	.cfi_startproc\n"
		                     "	movl  %ebx, 4(%eax)\n"  /* Save registers */
		                     "	movl  %edi, 8(%eax)\n"  /* *ditto* */
		                     "	movl  %esi, 12(%eax)\n" /* *ditto* */
		                     "	movl  %ebp, 16(%eax)\n" /* *ditto* */
		                     "	.cfi_reg_offset %ebp, 16, %eax\n"
		                     "	movl  0(%esp), %ebp\n"
		                     "	movl  %ebp, 0(%eax)\n"  /* Save C return address */
		                     "	movl  %eax, %ebp\n"     /* Load `%ebp' as it *should* be after the call (so we can set CFI unwind inf) */
		                     "	.cfi_reg_offset %eip, 0, %ebp\n"
		                     "	.cfi_reg_offset %ebx, 4, %ebp\n"
		                     "	.cfi_reg_offset %edi, 8, %ebp\n"
		                     "	.cfi_reg_offset %esi, 12, %ebp\n"
		                     "	.cfi_reg_offset %ebp, 16, %ebp\n"
		                     "	movl  $1f, 0(%esp)\n"   /* Set return address for invoked function to 1f */
		                     "	.extern cpu_apply_ucpustate\n"
		                     "	jmp   cpu_apply_ucpustate\n" /* <<<<<<<<< Invoke function */
		                     "1:\n"                     /* Return address */
		                     "	pushl 0(%ebp)\n"
		                     "	movl  4(%ebp), %ebx\n"  /* Restore registers */
		                     "	movl  8(%ebp), %edi\n"  /* *ditto* */
		                     "	movl  12(%ebp), %esi\n" /* *ditto* */
		                     "	movl  16(%ebp), %ebp\n" /* *ditto* */
		                     "	ret\n"
		                     "	.cfi_endproc\n"
		                     ".size __dbx_i386_invoke_cfunction, . - __dbx_i386_invoke_cfunction\n"
		                     ".popsection");
		extern uint64_t __attribute__((regparm(3)))
		__dbx_i386_invoke_cfunction(byte_t /*     */ *eax_sp_writer,
		                            void /*       */ *edx_unused,
		                            struct ucpustate *ecx_uc)
				THROWS(...);

		/* Invoke the wrapper for calling the external function. */
		result = __dbx_i386_invoke_cfunction(sp_writer, NULL, &uc);
	} EXCEPT {
		__builtin_stack_restore(orig_sp);
		return DBX_EFAULT;
	}
	__builtin_stack_restore(orig_sp);

	/* Write-back a register-based return value. */
	if (!return_is_injected_argument) {
		size_t return_size = ctype_sizeof(return_type);
		bzero(return_buf, return_size);
		if (return_size > 8)
			return_size = 8;
		memcpy(return_buf, &result, return_size);
	}
	return DBX_EOK;
#endif /* !__x86_64__ && __i386__ */

	/************************************************************************/
	/* ARM                                                                  */
	/************************************************************************/
#ifdef __arm__
	/* TODO */
#endif /* __arm__ */

#ifndef HAVE_CFUNCTION_CALL
	/* Not implemented :( */
	(void)func_address;
	(void)cc;
	(void)argc;
	(void)argv;
	(void)return_type;
	(void)return_buf;
	COMPILER_IMPURE();
	return DBX_EINTERN;
#endif /* !HAVE_CFUNCTION_CALL */
}

/* Arch-specific handler to perform a function call to a C function
 * !!!CAUTION!!! This *actually* executes the function in the context
 *               of the built-in debugger, and there is a good chance
 *               that if you randomly  try to execute functions  that
 *               weren't  meant for something like this, you'll cause
 *               the system to hang, or possible even worse.
 * @param: func_address: The address of the function to call (in the context of `dbg_current')
 * @param: cc:           One of `CTYPE_KIND_FUNPROTO_CC_*'
 * @param: argc:         Number of arguments to pass
 * @param: argv:         Vector of arguments to pass
 * @param: return_type:  The type of value that is returned by the function
 * @param: return_buf:   A caller-provided buffer to fill with the function's return value
 * @return: DBX_EOK:     Success.
 * @return: DBX_EFAULT:  Unhandled exception while trying to execute the function.
 * @return: DBX_EINTERN: Function calling is not implemented for the architecture. */
PUBLIC NONNULL((4, 5)) dbx_errno_t
NOTHROW(KCALL cfunction_call)(void const *func_address, uintptr_half_t cc,
                              size_t argc, struct cvalue *argv,
                              struct ctype *__restrict return_type,
                              void *__restrict return_buf) {
#ifdef HAVE_CFUNCTION_CALL
	dbx_errno_t result;
	pagedir_phys_t old_pdir, req_pdir;

	/* Set the page directory that is relevant for the task currently being debugged. */
	old_pdir = pagedir_get();
	req_pdir = old_pdir;
	if (dbg_current && !wasdestroyed(FORTASK(dbg_current, this_mman)))
		req_pdir = FORTASK(dbg_current, this_mman)->mm_pagedir_p;
	if (old_pdir != req_pdir) {
		if unlikely(!dbg_rt_verifypagedir(req_pdir))
			return DBX_EFAULT;
		pagedir_set(req_pdir);
	}

	/* TODO: Execute functions in a context that is more closely derived from `dbg_current':
	 * - GDT values for SEGMENT_KERNEL_FSBASE, SEGMENT_USER_FSBASE, SEGMENT_USER_GSBASE
	 *   should be set as `dbg_current',  `FORTASK(dbg_current, this_x86_user_fsbase)',
	 *   and `FORTASK(dbg_current, this_x86_user_gsbase)' resp.
	 * - this_x86_kernel_psp0 should be set as required by `dbg_current'
	 */

	/* Call the underlying implementation. */
	result = cfunction_call_impl(func_address, cc, argc, argv,
	                             return_type, return_buf);

	/* Restore context */
	if (old_pdir != req_pdir)
		pagedir_set(old_pdir);
	return result;
#else /* HAVE_CFUNCTION_CALL */
	return cfunction_call_impl(func_address, cc, argc, argv,
	                           return_type, return_buf);
#endif /* !HAVE_CFUNCTION_CALL */
}


DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_MODDBX_CEXPR_C */
