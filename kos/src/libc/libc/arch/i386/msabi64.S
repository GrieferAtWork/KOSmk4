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
#ifndef GUARD_LIBC_LIBC_ARCH_I386_MSABI64_S
#define GUARD_LIBC_LIBC_ARCH_I386_MSABI64_S 1

#include <hybrid/compiler.h>

#include <asm/cfi.h>
#include <bits/types.h>

#include "../../../../../include/crt-features/crt-kos-functions-attr.h"

#define ARG_PLACEHOLDER_   ,
#define ARG_PLACEHOLDER_1  ,
#define TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define TAKE_SECOND_ARG(x) TAKE_SECOND_ARG_IMPL x
#define IS_DEFINED3(...) TAKE_SECOND_ARG((__VA_ARGS__ 1,0))
#define IS_DEFINED2(x) IS_DEFINED3(ARG_PLACEHOLDER_##x)
#define IS_DEFINED(x) IS_DEFINED2(x)


#define __CRT_FUNCTION_IF_NOT_NORETURN_0(...) __VA_ARGS__
#define __CRT_FUNCTION_IF_NOT_NORETURN_1(...) /* nothing */
#define __CRT_FUNCTION_IF_NOT_NORETURN3(cond) __CRT_FUNCTION_IF_NOT_NORETURN_##cond
#define __CRT_FUNCTION_IF_NOT_NORETURN2(cond) __CRT_FUNCTION_IF_NOT_NORETURN3(cond)
#define __CRT_FUNCTION_IF_NOT_NORETURN(name, ...) \
	__CRT_FUNCTION_IF_NOT_NORETURN2(IS_DEFINED(__CRT_ATTR_NORETURN_##name))(__VA_ARGS__)


/* DOS functions use a different calling convention on x86_64.
 * For this reason, pretty much all CRT functions must be defined
 * twice, with one version taking arguments in MSABI, and the other
 * taking arguments using SYSVABI
 * This file defines all of the MSABI function wrappers that are used
 * to map registers in a comatible manner between the two calling
 * conventions, and exports all of these wrappers with the DOS$ prefix. */

/*
 * SYSVABI:
 *    Args:     rdi, rsi, rdx, rcx, r8, r9, [STACK...]
 *    Preserve: rbx, rsp, rbp, r12, r13, r14, r15
 *    Clobber:  rax, rdi, rsi, rdx, rcx, r8, r9, r10, r11
 *
 * MSABI:
 *    Args:     rcx, rdx, r8, r9, [STACK...]
 *    Preserve: rbx, rbp, rdi, rsi, rsp, r12, r13, r14, r15
 *    Clobber:  rax, rcx, rdx, r8, r9, r10, r11
 *
 * TODO: We must also account for the difference in the implementation of `va_list'!
 * TODO: We must also account for floating point arguments! (which is something that
 *       generate_headers.dee could tell us, but doesn't at the moment...)
 */


/* code generation limits (when changed, you must re-run `deemon -F <THIS_FILE>') */
#define CRT_MAX_ARGC           16
#define CRT_MAX_ALIASES        4
#define MSABI_SHADOWSPACE_SIZE 32 /* Size of the ~shadow space~ mandated by MSABI */


/*[[[deemon
local LENGTH = #r"	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) ";

for (local n: [:CRT_MAX_ARGC]) {
	print r"#define __CRT_FUNCTION_SELECT_ARGC_",;
	print n,;
	print "(name, num_intern_aliases, intern_aliases)",;
	if (n < 10)
		print " ",;
	print " \\";
if (n == 0)
	print r"__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \";
	print r"	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \";
	print r"	.section .text.crt.dos.compat.name;                                         \";
	print r"	.weak libd_##name;                                                          \";
	print r"	INTERN_FUNCTION(libd_##name);                                               \";
	print r"		.cfi_startproc;                                                         \";
	print r"		pushq_cfi_r %rdi;                                                       \";
	print r"		pushq_cfi_r %rsi;                                                       \";
	local stack_cleanup = 0;
	if (n >= 7) {
		local stack_args = n - 6;
		stack_cleanup = stack_args * 8;
		local stack_end_offset = 40 + (stack_args * 8);
		for (local stI: [:stack_args]) {
	print r"		pushq_cfi MSABI_SHADOWSPACE_SIZE + {}(%rsp);".format({ stack_end_offset }).ljust(LENGTH-3) + "\\";
		}
	}
	function argoff(i) -> stack_cleanup + 24 + (i * 8);
if (n >= 6)
	print r"		movq   MSABI_SHADOWSPACE_SIZE + {}(%rsp), %r9;".format({ argoff(1) }).ljust(LENGTH-3) + "\\";
if (n >= 5)
	print r"		movq   MSABI_SHADOWSPACE_SIZE + {}(%rsp), %r8;".format({ argoff(0) }).ljust(LENGTH-3) + "\\";
if (n >= 4)
	print r"		movq   %r9,  %rcx;                                                      \";
if (n >= 3)
	print r"		movq   %r8,  %rdx;                                                      \";
if (n >= 2)
	print r"		movq   %rdx, %rdi;                                                      \";
if (n >= 1)
	print r"		movq   %rcx, %rsi;                                                      \";
	print r"		INTERN(libc_##name);                                                    \";
	print r"		call   libc_##name;                                                     \";
if (n != 0)
	print r"__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \";
if (stack_cleanup != 0) {
	if (stack_cleanup == 8) {
	print r"		popq_cfi   %rsi; /" r"* addq $(8), %rsp; *" r"/                                 \";
	} else {
	print r"		addq   $({}), %rsp;".format({ stack_cleanup }).ljust(LENGTH-3) + "\\";
	print r"		.cfi_adjust_cfa_offset -{};".format({ stack_cleanup }).ljust(LENGTH-3) + "\\";
	}
}
	print r"		popq_cfi_r %rsi;                                                        \";
	print r"		popq_cfi_r %rdi;                                                        \";
	print r"		ret;{}                                                                   \".format({ n == 0 ? " " : ")" });
	print r"		.cfi_endproc;                                                           \";
	print r"	END(libd_##name);                                                           \";
	print r"	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \";
	print r"	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);{}".format({ n == 0 ? ")" : "" });
}
]]]*/
#define __CRT_FUNCTION_SELECT_ARGC_0(name, num_intern_aliases, intern_aliases)  \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;                                                                    \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);)
#define __CRT_FUNCTION_SELECT_ARGC_1(name, num_intern_aliases, intern_aliases)  \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_2(name, num_intern_aliases, intern_aliases)  \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_3(name, num_intern_aliases, intern_aliases)  \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		movq   %r8,  %rdx;                                                      \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_4(name, num_intern_aliases, intern_aliases)  \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		movq   %r9,  %rcx;                                                      \
		movq   %r8,  %rdx;                                                      \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_5(name, num_intern_aliases, intern_aliases)  \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		movq   MSABI_SHADOWSPACE_SIZE + 24(%rsp), %r8;                          \
		movq   %r9,  %rcx;                                                      \
		movq   %r8,  %rdx;                                                      \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_6(name, num_intern_aliases, intern_aliases)  \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		movq   MSABI_SHADOWSPACE_SIZE + 32(%rsp), %r9;                          \
		movq   MSABI_SHADOWSPACE_SIZE + 24(%rsp), %r8;                          \
		movq   %r9,  %rcx;                                                      \
		movq   %r8,  %rdx;                                                      \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_7(name, num_intern_aliases, intern_aliases)  \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 48(%rsp);                            \
		movq   MSABI_SHADOWSPACE_SIZE + 40(%rsp), %r9;                          \
		movq   MSABI_SHADOWSPACE_SIZE + 32(%rsp), %r8;                          \
		movq   %r9,  %rcx;                                                      \
		movq   %r8,  %rdx;                                                      \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		popq_cfi   %rsi; /* addq $(8), %rsp; */                                 \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_8(name, num_intern_aliases, intern_aliases)  \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 56(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 56(%rsp);                            \
		movq   MSABI_SHADOWSPACE_SIZE + 48(%rsp), %r9;                          \
		movq   MSABI_SHADOWSPACE_SIZE + 40(%rsp), %r8;                          \
		movq   %r9,  %rcx;                                                      \
		movq   %r8,  %rdx;                                                      \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		addq   $(16), %rsp;                                                     \
		.cfi_adjust_cfa_offset -16;                                             \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_9(name, num_intern_aliases, intern_aliases)  \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 64(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 64(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 64(%rsp);                            \
		movq   MSABI_SHADOWSPACE_SIZE + 56(%rsp), %r9;                          \
		movq   MSABI_SHADOWSPACE_SIZE + 48(%rsp), %r8;                          \
		movq   %r9,  %rcx;                                                      \
		movq   %r8,  %rdx;                                                      \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		addq   $(24), %rsp;                                                     \
		.cfi_adjust_cfa_offset -24;                                             \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_10(name, num_intern_aliases, intern_aliases) \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 72(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 72(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 72(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 72(%rsp);                            \
		movq   MSABI_SHADOWSPACE_SIZE + 64(%rsp), %r9;                          \
		movq   MSABI_SHADOWSPACE_SIZE + 56(%rsp), %r8;                          \
		movq   %r9,  %rcx;                                                      \
		movq   %r8,  %rdx;                                                      \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		addq   $(32), %rsp;                                                     \
		.cfi_adjust_cfa_offset -32;                                             \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_11(name, num_intern_aliases, intern_aliases) \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 80(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 80(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 80(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 80(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 80(%rsp);                            \
		movq   MSABI_SHADOWSPACE_SIZE + 72(%rsp), %r9;                          \
		movq   MSABI_SHADOWSPACE_SIZE + 64(%rsp), %r8;                          \
		movq   %r9,  %rcx;                                                      \
		movq   %r8,  %rdx;                                                      \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		addq   $(40), %rsp;                                                     \
		.cfi_adjust_cfa_offset -40;                                             \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_12(name, num_intern_aliases, intern_aliases) \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 88(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 88(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 88(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 88(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 88(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 88(%rsp);                            \
		movq   MSABI_SHADOWSPACE_SIZE + 80(%rsp), %r9;                          \
		movq   MSABI_SHADOWSPACE_SIZE + 72(%rsp), %r8;                          \
		movq   %r9,  %rcx;                                                      \
		movq   %r8,  %rdx;                                                      \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		addq   $(48), %rsp;                                                     \
		.cfi_adjust_cfa_offset -48;                                             \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_13(name, num_intern_aliases, intern_aliases) \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 96(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 96(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 96(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 96(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 96(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 96(%rsp);                            \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 96(%rsp);                            \
		movq   MSABI_SHADOWSPACE_SIZE + 88(%rsp), %r9;                          \
		movq   MSABI_SHADOWSPACE_SIZE + 80(%rsp), %r8;                          \
		movq   %r9,  %rcx;                                                      \
		movq   %r8,  %rdx;                                                      \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		addq   $(56), %rsp;                                                     \
		.cfi_adjust_cfa_offset -56;                                             \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_14(name, num_intern_aliases, intern_aliases) \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 104(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 104(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 104(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 104(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 104(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 104(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 104(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 104(%rsp);                           \
		movq   MSABI_SHADOWSPACE_SIZE + 96(%rsp), %r9;                          \
		movq   MSABI_SHADOWSPACE_SIZE + 88(%rsp), %r8;                          \
		movq   %r9,  %rcx;                                                      \
		movq   %r8,  %rdx;                                                      \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		addq   $(64), %rsp;                                                     \
		.cfi_adjust_cfa_offset -64;                                             \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
#define __CRT_FUNCTION_SELECT_ARGC_15(name, num_intern_aliases, intern_aliases) \
	__CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	.section .text.crt.dos.compat.name;                                         \
	.weak libd_##name;                                                          \
	INTERN_FUNCTION(libd_##name);                                               \
		.cfi_startproc;                                                         \
		pushq_cfi_r %rdi;                                                       \
		pushq_cfi_r %rsi;                                                       \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 112(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 112(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 112(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 112(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 112(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 112(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 112(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 112(%rsp);                           \
		pushq_cfi MSABI_SHADOWSPACE_SIZE + 112(%rsp);                           \
		movq   MSABI_SHADOWSPACE_SIZE + 104(%rsp), %r9;                         \
		movq   MSABI_SHADOWSPACE_SIZE + 96(%rsp), %r8;                          \
		movq   %r9,  %rcx;                                                      \
		movq   %r8,  %rdx;                                                      \
		movq   %rdx, %rdi;                                                      \
		movq   %rcx, %rsi;                                                      \
		INTERN(libc_##name);                                                    \
		call   libc_##name;                                                     \
__CRT_FUNCTION_IF_NOT_NORETURN(name,                                            \
		addq   $(72), %rsp;                                                     \
		.cfi_adjust_cfa_offset -72;                                             \
		popq_cfi_r %rsi;                                                        \
		popq_cfi_r %rdi;                                                        \
		ret;)                                                                   \
		.cfi_endproc;                                                           \
	END(libd_##name);                                                           \
	__CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases)   \
	DEFINE_PUBLIC_WEAK_ALIAS(DOS$##name, libd_##name);
//[[[end]]]



#define __CRT_FUNCTION_SELECT_ARGC_VA_N(...) \
	/* TODO: Varargs functions have to be emulated differently. */
#define __CRT_FUNCTION_SELECT_ARGC_VA(n) __CRT_FUNCTION_SELECT_ARGC_VA_N


#define __CRT_FUNCTION_FOREACH_INTERN_ALIAS_0(func, name, ...)
/*[[[deemon
for (local n: [1:CRT_MAX_ALIASES]) {
	print "#define __CRT_FUNCTION_FOREACH_INTERN_ALIAS_",;
	print n,;
	print "(func, name",;
	for (local i: [:n]) {
		print ", pp_cond_",;
		print i,;
		print ", name_",;
		print i,;
	}
	print ")",;
	for (local i: [:n]) {
		print " func(name, pp_cond_",;
		print i,;
		print ", name_",;
		print i,;
		print ")",;
	}
	print;
}
]]]*/
#define __CRT_FUNCTION_FOREACH_INTERN_ALIAS_1(func, name, pp_cond_0, name_0) func(name, pp_cond_0, name_0)
#define __CRT_FUNCTION_FOREACH_INTERN_ALIAS_2(func, name, pp_cond_0, name_0, pp_cond_1, name_1) func(name, pp_cond_0, name_0) func(name, pp_cond_1, name_1)
#define __CRT_FUNCTION_FOREACH_INTERN_ALIAS_3(func, name, pp_cond_0, name_0, pp_cond_1, name_1, pp_cond_2, name_2) func(name, pp_cond_0, name_0) func(name, pp_cond_1, name_1) func(name, pp_cond_2, name_2)
//[[[end]]]

#define __CRT_FUNCTION_FOREACH_PP_EXPAND(...) __VA_ARGS__
#define __CRT_FUNCTION_FOREACH_INTERN_ALIAS2(num_intern_aliases, args) \
	__CRT_FUNCTION_FOREACH_INTERN_ALIAS_##num_intern_aliases args
#define __CRT_FUNCTION_FOREACH_INTERN_ALIAS(func, name, num_intern_aliases, intern_aliases) \
	__CRT_FUNCTION_FOREACH_INTERN_ALIAS2(num_intern_aliases, (func, name, __CRT_FUNCTION_FOREACH_PP_EXPAND intern_aliases))


#define __CRT_FUNCTION_BEGIN_INTERN_ALIAS_IMPL(name, pp_cond, alias) \
	.if (pp_cond); DEFINE_INTERN_ALIAS(libd_##name, libd_##alias); .else;
#define __CRT_FUNCTION_END_INTERN_ALIAS_IMPL(name, pp_cond, alias) \
	.endif;
#define __CRT_FUNCTION_BEGIN_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	__CRT_FUNCTION_FOREACH_INTERN_ALIAS(__CRT_FUNCTION_BEGIN_INTERN_ALIAS_IMPL, name, num_intern_aliases, intern_aliases)
#define __CRT_FUNCTION_END_INTERN_ALIAS(name, num_intern_aliases, intern_aliases) \
	__CRT_FUNCTION_FOREACH_INTERN_ALIAS(__CRT_FUNCTION_END_INTERN_ALIAS_IMPL, name, num_intern_aliases, intern_aliases)



/* Enumerate all CRT functions that don't already have a dos-specific variant,
 * and select what needs to be done based on the number of arguments they take. */
#define __CRT_FUNCTION(name, num_intern_aliases, intern_aliases, argc, args, return_type, ...) \
	__CRT_FUNCTION_SELECT_ARGC_##argc(name, num_intern_aliases, intern_aliases)
#ifndef __INTELLISENSE__
#include "../../../../../include/crt-features/crt-kos-functions.h"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_LIBC_LIBC_ARCH_I386_MSABI64_S */
