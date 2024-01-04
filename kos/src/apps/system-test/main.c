/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_SYSTEM_TEST_MAIN_C
#define GUARD_APPS_SYSTEM_TEST_MAIN_C 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>

#include <kos/ksysctl.h>
#include <kos/types.h>
#include <sys/syslog.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <format-printer.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DECL_BEGIN

INTDEF struct testdecl __system_tests_begin[];
INTDEF struct testdecl __system_tests_end[];

PRIVATE struct testdecl *ctest_current_test = NULL;

#define EL "\e[K" /* EL(ANSITTY_EL_AFTER); */

PRIVATE void
NOTHROW_NCX(__LIBKCALL do_ctest_vsubtestf)(char const *__restrict format,
                                           va_list args, bool is_status) {
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
	if (is_status) {
		printf(EL "\r");
	} else {
		printf(EL "\n");
	}
}

INTERN void
NOTHROW_NCX(__LIBKCALL ctest_vsubtestf)(char const *__restrict format,
                                        va_list args) {
	do_ctest_vsubtestf(format, args, false);
}

INTERN void
NOTHROW_NCX(__VLIBKCALL ctest_subtestf)(char const *__restrict format, ...) {
	va_list args;
	va_start(args, format);
	ctest_vsubtestf(format, args);
	va_end(args);
}

INTERN void
NOTHROW_NCX(__LIBKCALL ctest_vsubstatf)(char const *__restrict format,
                                        va_list args) {
	do_ctest_vsubtestf(format, args, true);
}

INTERN void
NOTHROW_NCX(__VLIBKCALL ctest_substatf)(char const *__restrict format, ...) {
	va_list args;
	va_start(args, format);
	ctest_vsubstatf(format, args);
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
		printf("test:%s" EL "\n", iter->td_name);
		(*iter->td_func)();
	}
}

PRIVATE bool run_specific_test(char const *name) {
	struct testdecl *iter;
	for (iter = __system_tests_begin; iter < __system_tests_end; ++iter) {
		if (strcmp(iter->td_name, name) != 0)
			continue;
		ctest_current_test = iter;
		syslog(LOG_DEBUG, "[test:%s] %s:%d\n",
		       iter->td_name,
		       iter->td_file,
		       iter->td_line);
		printf("test:%s" EL "\n", iter->td_name);
		(*iter->td_func)();
		return true;
	}
	return false;
}

int main(int argc, char *argv[], char *envp[]) {
	/* A special application who's sole purpose is to perform a series of
	 * automated system tests to ensure  that the various sub-systems  of
	 * KOS are functioning properly. */
	(void)argc;
	(void)argv;
	(void)envp;

	/* Like below, but also clear caches before we start.
	 *
	 * This way, we make the system state a bit more consistent,
	 * meaning  that while we  may not catch  some bugs that are
	 * the result of problems with caches, bugs that are related
	 * to caches can be reproduced consistently! */
	KSysctl(KSYSCTL_SYSTEM_CLEARCACHES);

	/* Actually run all of the tests. */
	if (argc <= 1) {
		run_all_tests();
	} else {
		int i;
		for (i = 1; i < argc; ++i) {
			if (!run_specific_test(argv[i])) {
				fprintf(stderr, "Unknown test: %q", argv[i]);
				return EXIT_FAILURE;
			}
		}
	}

	/* Make sure that we didn't end up with any memory leaks. */
	assertf(KSysctl(KSYSCTL_SYSTEM_MEMORY_DUMP_LEAKS) == 0,
	        "Memory leaks detected (see system log)");

	/* Clear system caches in order to touch all of the various
	 * systems that doing so affects,  making sure that all  of
	 * them function correctly. */
	KSysctl(KSYSCTL_SYSTEM_CLEARCACHES);

	/* Assert no-leaks a second time (in case CLEARCACHES caused some) */
	assertf(KSysctl(KSYSCTL_SYSTEM_MEMORY_DUMP_LEAKS) == 0,
	        "Memory leaks detected (see system log)");

	printf("All tests OK" EL "\n");
	return EXIT_SUCCESS;
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_MAIN_C */
