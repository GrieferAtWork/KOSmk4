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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_SYSTEM_TEST_MAIN_C
#define GUARD_APPS_SYSTEM_TEST_MAIN_C 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#include <kos/types.h>
#include <sys/syslog.h>
#include <system-test/ctest.h>

#include <format-printer.h>
#include <stdarg.h>
#include <stdio.h>

DECL_BEGIN

INTDEF struct testdecl __system_tests_begin[];
INTDEF struct testdecl __system_tests_end[];

PRIVATE struct testdecl *ctest_current_test = NULL;

INTERN void
NOTHROW_NCX(__LIBCCALL ctest_vsubtestf)(char const *__restrict format,
                                        va_list args) {
	va_list args_copy;
	syslog(LOG_DEBUG, "[test:%s] %s:%d: ",
	       ctest_current_test->td_name,
	       ctest_current_test->td_file,
	       ctest_current_test->td_line);
	va_copy(args_copy, args);
	format_vprintf(&syslog_printer, (void *)(uintptr_t)LOG_DEBUG, format, args_copy);
	va_end(args_copy);
	syslog_printer((void *)(uintptr_t)LOG_DEBUG, "\n", 1);
	printf("\tTesting if: ");
	vprintf(format, args);
	putchar('\n');
}

INTERN void
NOTHROW_NCX(__VLIBCCALL ctest_subtestf)(char const *__restrict format, ...) {
	va_list args;
	va_start(args, format);
	ctest_vsubtestf(format, args);
	va_end(args);
}



PRIVATE void run_all_tests(void) {
	struct testdecl *iter;
	for (iter = __system_tests_begin; iter < __system_tests_end; ++iter) {
		ctest_current_test = iter;
		syslog(LOG_DEBUG, "[test:%s] %s:%d\n",
		       iter->td_name,
		       iter->td_file,
		       iter->td_line);
		printf("test:%s\n", iter->td_name);
		(*iter->td_func)();
	}
}

int main(int argc, char *argv[], char *envp[]) {
	/* A special application who's sole purpose is to perform a series of
	 * automated system tests to ensure that the various sub-systems of
	 * KOS are functioning properly. */
	(void)argc;
	(void)argv;
	(void)envp;

	run_all_tests();
	printf("All tests OK\n");
	return 0;
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_MAIN_C */
