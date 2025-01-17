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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_SYSEXCEPT_C
#define GUARD_APPS_SYSTEM_TEST_TEST_SYSEXCEPT_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/except.h>
#include <kos/kernel/paging.h>
#include <kos/syscalls.h>
#include <kos/types.h>
#include <kos/ukern.h>
#include <kos/unistd.h>
#include <sys/syscall-proto.h>
#include <sys/syscall.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <syslog.h>

#if defined(__i386__) || defined(__x86_64__)
#include <cfi.h>
#endif /* __i386__ || __x86_64__ */

DECL_BEGIN

/*[[[deemon
import assemble from ....misc.libgen.cfi.comp;
print("#define I386_CFI_CLEARDF   ", repr(",".join(assemble('i386', '%eflags', r'
	push %eflags
	and  ~$EFLAGS_DF
'))));
print("#define X86_64_CFI_CLEARDF ", repr(",".join(assemble('x86_64', '%rflags', r'
	push %rflags
	and  ~$EFLAGS_DF
'))));
]]]*/
#define I386_CFI_CLEARDF   "22,9,6,121,0,11,255,251,26"
#define X86_64_CFI_CLEARDF "22,49,7,146,49,0,11,255,251,26"
/*[[[end]]]*/

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
	/* NOTE: sysenter  is emulated by the kernel if unsupported by the CPU,
	 *       so this should  always work. However,  when unavailable,  that
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
	                     ".cfi_startcapsule\n\t"
#ifdef __x86_64__
	                     ".cfi_escape " X86_64_CFI_CLEARDF "\n\t"
#else /* __x86_64__ */
	                     ".cfi_escape " I386_CFI_CLEARDF "\n\t"
#endif /* !__x86_64__ */
	                     "int $0x80\n\t" /* Do the syscall */
	                     "cld\n\t"       /* Disable exceptions */
	                     ".cfi_endcapsule"
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

#define assert_thrown(code) \
	assertf(was_thrown(code), "except_code(): %#Ix", except_code())



DEFINE_TEST(system_exceptions_work_correctly) {
	/* Test all 3 ways in which an exception can be thrown:
	 *  - syscall  (including all arch-specific, as well as generic variants)
	 *  - THROW()
	 *  - user-space fault
	 */

	/* The    regular    exception-enabled,
	 * portable user-space wrapper function */
	ctest_subtestf("Pipe() works");
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		Pipe(fds);
		NE(-1, fds[0]);
		NE(-1, fds[1]);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	ctest_subtestf("Pipe(NULL) breaks");
	TRY {
		int *volatile null = NULL;
		Pipe(null);
		assert_failed("syscall:libc: Shouldn't get here!");
	} EXCEPT {
		assert_thrown(E_SEGFAULT);
	}
#ifdef KERNELSPACE_BASE
	ctest_subtestf("Pipe(KERNELSPACE_BASE) breaks");
	TRY {
		int *volatile kbase = (int *)KERNELSPACE_BASE;
		Pipe(kbase);
		assert_failed("syscall:libc: Shouldn't get here!");
	} EXCEPT {
		assert_thrown(E_SEGFAULT);
	}
	ctest_subtestf("Pipe(KERNELSPACE_BASE-1) breaks");
	TRY {
		int *volatile kbase = (int *)((uintptr_t)KERNELSPACE_BASE - 1);
		Pipe(kbase);
		assert_failed("syscall:libc: Shouldn't get here!");
	} EXCEPT {
		assert_thrown(E_SEGFAULT);
	}
#if defined(__i386__) || defined(__x86_64__)
	ctest_subtestf("Pipe(KERNEL_CORE_BASE+X) breaks");
	{
		static uint32_t const offsets[] = {
			0x00000000, 0x00000200, 0x00100000, 0x00100200,
			0x00110000, 0x00110200, 0x00120000, 0x00120200,
			0x00130000, 0x00130200, 0x00140000, 0x00140200,
		};
		unsigned int i;
		for (i = 0; i < lengthof(offsets); ++i) {
			TRY {
				int *volatile kbase = (int *)(KERNEL_CORE_BASE + offsets[i]);
				Pipe(kbase);
				assert_failed("syscall:libc: Shouldn't get here! [addr:%p]", kbase);
			} EXCEPT {
				assert_thrown(E_SEGFAULT);
			}
		}
	}
#endif /* __i386__ || __x86_64__ */
#endif /* KERNELSPACE_BASE */


	/* The libc direct syscall function */
	ctest_subtestf("sys_Xpipe() works");
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		sys_Xpipe(fds);
		NE(-1, fds[0]);
		NE(-1, fds[1]);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	ctest_subtestf("sys_Xpipe(NULL) breaks");
	TRY {
		sys_Xpipe(NULL);
		assert_failed("syscall:libc:sysX: Shouldn't get here!");
	} EXCEPT {
		assert_thrown(E_SEGFAULT);
	}

	/* Also make sure  that ukern system  calls _can_  work
	 * Note  that these are exception-enabled system calls,
	 * so if anything went wrong in here, the kernel  would
	 * throw an exception  that'd cause libc  to trigger  a
	 * coredump when it couldn't find an exception handler. */
	ctest_subtestf("userkern_Syscall(pipe) works");
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		userkern_Syscall(userkern_self(), pipe)(fds);
		NE(-1, fds[0]);
		NE(-1, fds[1]);
		userkern_Syscall(userkern_self(), close)(fds[1]);
		userkern_Syscall(userkern_self(), close)(fds[0]);
	}
	ctest_subtestf("userkern_Syscall(pipe(NULL)) breaks");
	TRY {
		userkern_Syscall(userkern_self(), pipe)(NULL);
		assert_failed("syscall:useg: Shouldn't get here!");
	} EXCEPT {
		assert_thrown(E_SEGFAULT);
	}

#if defined(__i386__) && !defined(__x86_64__)
	/* Manually invoke: lcall $7 */
	ctest_subtestf("lcall7_Pipe() works");
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		lcall7_Pipe(fds);
		NE(-1, fds[0]);
		NE(-1, fds[1]);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	ctest_subtestf("lcall7_Pipe(NULL) breaks");
	TRY {
		lcall7_Pipe(NULL);
		assert_failed("syscall:lcall7: Shouldn't get here!");
	} EXCEPT {
		assert_thrown(E_SEGFAULT);
	}
	/* Manually invoke: sysenter */
	ctest_subtestf("sysenter_Pipe() works");
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		sysenter_Pipe(fds);
		NE(-1, fds[0]);
		NE(-1, fds[1]);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	ctest_subtestf("sysenter_Pipe(NULL) breaks");
	TRY {
		sysenter_Pipe(NULL);
		assert_failed("syscall:sysenter: Shouldn't get here!");
	} EXCEPT {
		assert_thrown(E_SEGFAULT);
	}
#endif /* __i386__ && !__x86_64 */

#if defined(__i386__) || defined(__x86_64__)
	/* Manually invoke: int $0x80 */
	ctest_subtestf("int80_Pipe() works");
	{
		fd_t fds[2];
		fds[0] = fds[1] = -1;
		int80_Pipe(fds);
		NE(-1, fds[0]);
		NE(-1, fds[1]);
		sys_Xclose(fds[1]);
		sys_Xclose(fds[0]);
	}
	ctest_subtestf("int80_Pipe(NULL) breaks");
	TRY {
		int80_Pipe(NULL);
		assert_failed("syscall:int80: Shouldn't get here!");
	} EXCEPT {
		assert_thrown(E_SEGFAULT);
	}
#endif /* __i386__ || __x86_64__ */

	/* Throw an exception manually by using the THROW() macro. */
	assert_thrown(E_OK);
	ctest_subtestf("THROW(X) works");
	TRY {
		THROW(E_DIVIDE_BY_ZERO);
		assert_failed("THROW(): Shouldn't get here!");
	} EXCEPT {
		assert_thrown(E_DIVIDE_BY_ZERO);
	}

	/* Throw an exception manually by using the THROW() macro (with additional pointers). */
	assert_thrown(E_OK);
	ctest_subtestf("THROW(X, Y, Z) works");
	TRY {
		THROW(E_DIVIDE_BY_ZERO, 1, 2, 3);
		assert_failed("THROW(): Shouldn't get here!");
	} EXCEPT {
		unsigned int i;
		struct exception_data *data;
		assert_thrown(E_DIVIDE_BY_ZERO);
		data = except_data();
		EQ(1, data->e_args.e_pointers[0]);
		EQ(2, data->e_args.e_pointers[1]);
		EQ(3, data->e_args.e_pointers[2]);
		for (i = 3; i < lengthof(data->e_args.e_pointers); ++i)
			EQf(0, data->e_args.e_pointers[i], "i = %u", i);
	}

	/* Do something that causes  the kernel to throw  an
	 * exception due to performing an illegal operation. */
	assert_thrown(E_OK);
	ctest_subtestf("E_DIVIDE_BY_ZERO works");
	TRY {
		static volatile int x = 10;
		static volatile int y = 0;
		static volatile int z;
		z = x / y;
		assert_failed("usfault: Shouldn't get here!");
		x = z; /* Suppress warning: z set, but not used */
	} EXCEPT {
		assert_thrown(E_DIVIDE_BY_ZERO);
	}
	assert_thrown(E_OK);
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_SYSEXCEPT_C */
