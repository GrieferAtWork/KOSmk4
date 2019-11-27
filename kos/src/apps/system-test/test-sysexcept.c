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
#include <sys/syscall.h>
#include <sys/syscall-proto.h>
#include <kos/ukern.h>
#include <system-test/ctest.h>

#include <assert.h>

DECL_BEGIN

#define assert_error_code(code) \
	assertf(was_thrown(code), "error_code(): %I#x", error_code())

DEFINE_TEST(system_exceptions_work_correctly) {
	/* Test all 3 ways in which an exception can be thrown:
	 *  - syscall
	 *  - THROW()
	 *  - user-space fault
	 */
	TRY {
		Pipe(NULL);
		assert_failed("syscall: Shouldn't get here!\n");
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
		assert_failed("syscall: Shouldn't get here! (useg)\n");
	} EXCEPT {
		assert_error_code(E_SEGFAULT);
	}
	/* TODO: Manually invoke: lcall $7 */
	/* TODO: Manually invoke: int $0x80 */
	/* TODO: Manually invoke: sysenter */
	TRY {
		THROW(E_DIVIDE_BY_ZERO);
		assert_failed("THROW(): Shouldn't get here!\n");
	} EXCEPT {
		assert_error_code(E_DIVIDE_BY_ZERO);
	}
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
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_SYSEXCEPT_C */
