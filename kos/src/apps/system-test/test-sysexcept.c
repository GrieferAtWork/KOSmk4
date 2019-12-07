/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_SYSEXCEPT_C
#define GUARD_APPS_SYSTEM_TEST_TEST_SYSEXCEPT_C 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <kos/except.h>
#include <kos/unistd.h>
#include <kos/syscalls.h>
#include <sys/syscall.h>
#include <sys/syscall-proto.h>
#include <stdio.h>
#include <kos/ukern.h>
#include <system-test/ctest.h>

#include <assert.h>

DECL_BEGIN

#define assert_error_code(code) \
	assertf(was_thrown(code), "error_code(): %I#x", error_code())

#if defined(__i386__) && !defined(__x86_64__)
INTDEF void lcall7_Pipe(fd_t fd[2]);
__asm__(
".pushsection .text\n"
"lcall7_Pipe:\n"
"	.cfi_startproc\n"
"	movl   4(%esp), %eax\n"
"	pushl  %eax\n"
"	.cfi_adjust_cfa_offset 4\n"
"	stc\n"
"	lcall  $7, $" PP_STR(SYS_pipe) "\n"
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
	__asm__ __volatile__("stc\n\t"
	                     "call sysenter_common2\n\t"
	                     :
	                     : "a" (SYS_pipe)
	                     , "b" (&fd[0])
	                     : "cc", "memory"
	                     , "edi");
}
#endif /* __i386__ && !__x86_64 */

#if defined(__i386__) || defined(__x86_64__)
PRIVATE ATTR_NOINLINE void int80_Pipe(fd_t fd[2]) {
	__asm__ __volatile__("stc\n\t"
	                     "int $0x80"
	                     :
	                     : "a" (SYS_pipe)
	                     , "b" (&fd[0])
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
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		Pipe(fds);
		assert(fds[0] != -1);
		assert(fds[1] != -1);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	TRY {
		Pipe(NULL);
		assert_failed("syscall:libc: Shouldn't get here!\n");
	} EXCEPT {
		assert_error_code(E_SEGFAULT);
	}

	/* The libc direct syscall function */
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		sys_Xpipe(fds);
		assert(fds[0] != -1);
		assert(fds[1] != -1);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	TRY {
		Pipe(NULL);
		assert_failed("syscall:libc:sysX: Shouldn't get here!\n");
	} EXCEPT {
		assert_error_code(E_SEGFAULT);
	}

	/* Also make sure that ukern system calls _can_ work
	 * Note that these are exception-enabled system calls,
	 * so if anything went wrong in here, the kernel would
	 * throw an exception that'd cause libc to trigger a
	 * coredump when it couldn't find an exception handler. */
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		userkern_Syscall(userkern_self(), pipe)(fds);
		assert(fds[0] != -1);
		assert(fds[1] != -1);
		userkern_Syscall(userkern_self(), close)(fds[1]);
		userkern_Syscall(userkern_self(), close)(fds[0]);
	}
	TRY {
		userkern_Syscall(userkern_self(), pipe)(NULL);
		assert_failed("syscall:useg: Shouldn't get here!\n");
	} EXCEPT {
		assert_error_code(E_SEGFAULT);
	}

#if defined(__i386__) && !defined(__x86_64__)
	/* Manually invoke: lcall $7 */
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		lcall7_Pipe(fds);
		assert(fds[0] != -1);
		assert(fds[1] != -1);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	TRY {
		lcall7_Pipe(NULL);
		assert_failed("syscall:lcall7: Shouldn't get here!\n");
	} EXCEPT {
		assert_error_code(E_SEGFAULT);
	}
	/* Manually invoke: sysenter */
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		sysenter_Pipe(fds);
		assert(fds[0] != -1);
		assert(fds[1] != -1);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	TRY {
		sysenter_Pipe(NULL);
		assert_failed("syscall:sysenter: Shouldn't get here!\n");
	} EXCEPT {
		assert_error_code(E_SEGFAULT);
	}
#endif /* __i386__ && !__x86_64 */

#if defined(__i386__) || defined(__x86_64__)
	/* Manually invoke: int $0x80 */
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		int80_Pipe(fds);
		assert(fds[0] != -1);
		assert(fds[1] != -1);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	TRY {
		int80_Pipe(NULL);
		assert_failed("syscall:int80: Shouldn't get here!\n");
	} EXCEPT {
		assert_error_code(E_SEGFAULT);
	}
#endif /* __i386__ || __x86_64__ */

	/* Throw an exception manually by using the THROW() macro. */
	assert_error_code(E_OK);
	TRY {
		THROW(E_DIVIDE_BY_ZERO);
		assert_failed("THROW(): Shouldn't get here!\n");
	} EXCEPT {
		assert_error_code(E_DIVIDE_BY_ZERO);
	}

	/* Do something that causes the kernel to throw an
	 * exception due to performing an illegal operation. */
	assert_error_code(E_OK);
	TRY {
		static volatile int x = 10;
		static volatile int y = 0;
		static volatile int z;
		z = x / y;
		assert_failed("usfault: Shouldn't get here!\n");
		x = z; /* Suppress warning: z set, but not used */
	} EXCEPT {
		assert_error_code(E_DIVIDE_BY_ZERO);
	}
	assert_error_code(E_OK);
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_SYSEXCEPT_C */
