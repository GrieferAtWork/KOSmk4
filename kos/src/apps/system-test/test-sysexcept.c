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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_SYSEXCEPT_C
#define GUARD_APPS_SYSTEM_TEST_TEST_SYSEXCEPT_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <kos/except.h>
#include <kos/unistd.h>
#include <kos/syscalls.h>
#include <sys/syscall.h>
#include <sys/syscall-proto.h>
#include <stdio.h>
#include <syslog.h>
#include <kos/ukern.h>
#include <system-test/ctest.h>

#include <assert.h>

DECL_BEGIN

/*[[[deemon
import * from ....misc.libgen.cfi.compiler;
local bytes = compileExpressionEx('i386', '%eflags', r'
	push %eflags     # %eflags
	push $EFLAGS_DF  # %eflags, EFLAGS_DF
	not              # %eflags, ~EFLAGS_DF
	and              # (%eflags & ~EFLAGS_DF)
', deref_after: false);
print("#define I386_CFI_CLEARDF   ", repr(", ".join(for (local b: bytes) "0x" + b.hex()[2:].zfill(2))));
local bytes = compileExpressionEx('x86_64', '%rflags', r'
	push %rflags     # %rflags
	push $EFLAGS_DF  # %rflags, EFLAGS_DF
	not              # %rflags, ~EFLAGS_DF
	and              # (%rflags & ~EFLAGS_DF)
', deref_after: false);
print("#define X86_64_CFI_CLEARDF ", repr(", ".join(for (local b: bytes) "0x" + b.hex()[2:].zfill(2))));
]]]*/
#define I386_CFI_CLEARDF   "0x16, 0x09, 0x06, 0x59, 0x0a, 0x00, 0x04, 0x20, 0x1a"
#define X86_64_CFI_CLEARDF "0x16, 0x31, 0x07, 0x90, 0x31, 0x0a, 0x00, 0x04, 0x20, 0x1a"
/*[[[end]]]*/

#define assert_error_code(code) \
	assertf(was_thrown(code), "error_code(): %I#x", error_code())

#if defined(__i386__) && !defined(__x86_64__)
INTDEF void lcall7_Pipe(fd_t fd[2]);
__asm__(
".pushsection .text\n"
"lcall7_Pipe:\n"
"	.cfi_startproc\n"
"	.cfi_escape " I386_CFI_CLEARDF "\n"
"	movl   4(%esp), %eax\n"
"	pushl  %eax\n"
"	.cfi_adjust_cfa_offset 4\n"
"	std\n" /* Enable exceptions */
"	lcall  $7, $" PP_STR(SYS_pipe) "\n"
"	cld\n" /* Disable exceptions */
"	addl   $4, %esp\n"
"	.cfi_adjust_cfa_offset -4\n"
"	ret\n"
"	.cfi_endproc\n"
".size lcall7_Pipe, . - lcall7_Pipe\n"
"\n"
"sysenter_common:\n"
"	.cfi_startproc\n"
"	popl   %edi\n"
"	.cfi_adjust_cfa_offset -4\n"
"	.cfi_register %eip, %edi\n"
"	movl   %esp, %ebp\n"
"	sysenter\n"
"	.cfi_endproc\n"
".size sysenter_common, . - sysenter_common\n"
"\n"
"sysenter_common2:\n"
"	.cfi_startproc\n"
"	pushl  %ebp\n"
"	.cfi_adjust_cfa_offset 4\n"
"	.cfi_rel_offset %ebp, 0\n"
"	call   sysenter_common\n"
"	popl   %ebp\n"
"	.cfi_adjust_cfa_offset -4\n"
"	.cfi_restore %ebp\n"
"	ret\n"
"	.cfi_endproc\n"
".size sysenter_common2, . - sysenter_common2\n"
".popsection\n"
);

PRIVATE ATTR_NOINLINE void sysenter_Pipe(fd_t fd[2]) {
	/* NOTE: sysenter is emulated by the kernel if unsupported by the CPU,
	 *       so this should always work. However, when unavailable, that
	 *       emulation is quite slow and expensive, so it's if unavailable,
	 *       libc would fall back to using int 80h at runtime. */
	__asm__ __volatile__("std\n\t" /* Enable exceptions */
	                     ".cfi_remember_state\n\t"
	                     ".cfi_escape " I386_CFI_CLEARDF "\n\t"
	                     "call sysenter_common2\n\t" /* Do the syscall */
	                     "cld\n\t"                   /* Disable exceptions */
	                     ".cfi_restore_state"
	                     :
	                     : "a" (SYS_pipe)
	                     , "b" (&fd[0])
	                     : "cc", "memory"
	                     , "%edi");
}
#endif /* __i386__ && !__x86_64 */

#if defined(__i386__) || defined(__x86_64__)
LOCAL void int80_Pipe(fd_t fd[2]) {
	__asm__ __volatile__("std\n\t" /* Enable exceptions */
	                     ".cfi_remember_state\n\t"
#ifdef __x86_64__
	                     ".cfi_escape " X86_64_CFI_CLEARDF "\n\t"
#else /* __x86_64__ */
	                     ".cfi_escape " I386_CFI_CLEARDF "\n\t"
#endif /* !__x86_64__ */
	                     "int $0x80\n\t" /* Do the syscall */
	                     "cld\n\t"       /* Disable exceptions */
	                     ".cfi_restore_state"
	                     :
	                     : "a" (SYS_pipe)
#ifdef __x86_64__
	                     , "D" (&fd[0])
#else /* __x86_64__ */
	                     , "b" (&fd[0])
#endif /* !__x86_64__ */
	                     : "cc", "memory");
}
#endif /* __i386__ || __x86_64__ */


DEFINE_TEST(system_exceptions_work_correctly) {
	/* Test all 3 ways in which an exception can be thrown:
	 *  - syscall  (including all arch-specific, as well as generic variants)
	 *  - THROW()
	 *  - user-space fault
	 */

	/* The regular exception-enabled,
	 * portable user-space wrapper function */
	ctest_subtestf("Pipe() works");
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		Pipe(fds);
		assert(fds[0] != -1);
		assert(fds[1] != -1);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	ctest_subtestf("Pipe(NULL) breaks");
	TRY {
		Pipe(NULL);
		assert_failed("syscall:libc: Shouldn't get here!");
	} EXCEPT {
		assert_error_code(E_SEGFAULT);
	}

	/* The libc direct syscall function */
	ctest_subtestf("sys_Xpipe() works");
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		sys_Xpipe(fds);
		assert(fds[0] != -1);
		assert(fds[1] != -1);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	ctest_subtestf("sys_Xpipe(NULL) breaks");
	TRY {
		sys_Xpipe(NULL);
		assert_failed("syscall:libc:sysX: Shouldn't get here!");
	} EXCEPT {
		assert_error_code(E_SEGFAULT);
	}

	/* Also make sure that ukern system calls _can_ work
	 * Note that these are exception-enabled system calls,
	 * so if anything went wrong in here, the kernel would
	 * throw an exception that'd cause libc to trigger a
	 * coredump when it couldn't find an exception handler. */
	ctest_subtestf("userkern_Syscall(pipe) works");
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		userkern_Syscall(userkern_self(), pipe)(fds);
		assert(fds[0] != -1);
		assert(fds[1] != -1);
		userkern_Syscall(userkern_self(), close)(fds[1]);
		userkern_Syscall(userkern_self(), close)(fds[0]);
	}
	ctest_subtestf("userkern_Syscall(pipe(NULL)) breaks");
	TRY {
		userkern_Syscall(userkern_self(), pipe)(NULL);
		assert_failed("syscall:useg: Shouldn't get here!");
	} EXCEPT {
		assert_error_code(E_SEGFAULT);
	}

#if defined(__i386__) && !defined(__x86_64__)
	/* Manually invoke: lcall $7 */
	ctest_subtestf("lcall7_Pipe() works");
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		lcall7_Pipe(fds);
		assert(fds[0] != -1);
		assert(fds[1] != -1);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	ctest_subtestf("lcall7_Pipe(NULL) breaks");
	TRY {
		lcall7_Pipe(NULL);
		assert_failed("syscall:lcall7: Shouldn't get here!");
	} EXCEPT {
		assert_error_code(E_SEGFAULT);
	}
	/* Manually invoke: sysenter */
	ctest_subtestf("sysenter_Pipe() works");
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		sysenter_Pipe(fds);
		assert(fds[0] != -1);
		assert(fds[1] != -1);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	ctest_subtestf("sysenter_Pipe(NULL) breaks");
	TRY {
		sysenter_Pipe(NULL);
		assert_failed("syscall:sysenter: Shouldn't get here!");
	} EXCEPT {
		assert_error_code(E_SEGFAULT);
	}
#endif /* __i386__ && !__x86_64 */

#if defined(__i386__) || defined(__x86_64__)
	/* Manually invoke: int $0x80 */
	ctest_subtestf("int80_Pipe() works");
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		int80_Pipe(fds);
		assert(fds[0] != -1);
		assert(fds[1] != -1);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	ctest_subtestf("int80_Pipe(NULL) breaks");
	TRY {
		int80_Pipe(NULL);
		assert_failed("syscall:int80: Shouldn't get here!");
	} EXCEPT {
		assert_error_code(E_SEGFAULT);
	}
#endif /* __i386__ || __x86_64__ */

	/* Throw an exception manually by using the THROW() macro. */
	assert_error_code(E_OK);
	ctest_subtestf("THROW(X) works");
	TRY {
		THROW(E_DIVIDE_BY_ZERO);
		assert_failed("THROW(): Shouldn't get here!");
	} EXCEPT {
		assert_error_code(E_DIVIDE_BY_ZERO);
	}

	/* Throw an exception manually by using the THROW() macro (with additional pointers). */
	assert_error_code(E_OK);
	ctest_subtestf("THROW(X, Y, Z) works");
	TRY {
		THROW(E_DIVIDE_BY_ZERO, 1, 2, 3);
		assert_failed("THROW(): Shouldn't get here!");
	} EXCEPT {
		unsigned int i;
		struct exception_data *data;
		assert_error_code(E_DIVIDE_BY_ZERO);
		data = error_data();
		assertf(data->e_args.e_pointers[0] == 1, "data->e_args.e_pointers[0] = %p", data->e_args.e_pointers[0]);
		assertf(data->e_args.e_pointers[1] == 2, "data->e_args.e_pointers[1] = %p", data->e_args.e_pointers[1]);
		assertf(data->e_args.e_pointers[2] == 3, "data->e_args.e_pointers[2] = %p", data->e_args.e_pointers[2]);
		for (i = 3; i < COMPILER_LENOF(data->e_args.e_pointers); ++i) {
			assertf(data->e_args.e_pointers[i] == 0,
			        "data->e_args.e_pointers[%u] = %p",
			        i, data->e_args.e_pointers[i]);
		}
	}

	/* Do something that causes the kernel to throw an
	 * exception due to performing an illegal operation. */
	assert_error_code(E_OK);
	ctest_subtestf("E_DIVIDE_BY_ZERO works");
	TRY {
		static volatile int x = 10;
		static volatile int y = 0;
		static volatile int z;
		z = x / y;
		assert_failed("usfault: Shouldn't get here!");
		x = z; /* Suppress warning: z set, but not used */
	} EXCEPT {
		assert_error_code(E_DIVIDE_BY_ZERO);
	}
	assert_error_code(E_OK);
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_SYSEXCEPT_C */
