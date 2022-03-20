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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_POSITIONAL_PRINTF_C
#define GUARD_APPS_SYSTEM_TEST_TEST_POSITIONAL_PRINTF_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <system-test/ctest.h>

#include <assert.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>

DECL_BEGIN

PRIVATE NONNULL((1, 2)) void
assert_printf_equals(char const *expected,
                     char const *format, ...) {
	va_list args;
	char *actual;
	va_start(args, format);
	actual = vstrdupf(format, args);
	va_end(args);
	assertf(strcmp(expected, actual) == 0,
	        "expected: %q\n"
	        "actual:   %q\n",
	        expected, actual);
	free(actual);
}

DEFINE_TEST(positional_printf) {
	/* Do some sanity checking on  printf (though if this breaks,  it's
	 * actually a wonder that the system was able to get to this point) */
	assert_printf_equals("42", "%d", 42);
	assert_printf_equals("-42", "%d", -42);
	assert_printf_equals("+42", "%+d", 42);

	/* The actual meat of this test: positional printf arguments. */
	assert_printf_equals("<42 42 42 42>", "<%1$d %1$d %1$d %1$d>", 42);
	assert_printf_equals("<40 30 20 10>", "<%4$d %3$d %2$d %1$d>", 10, 20, 30, 40);
	assert_printf_equals("<00000042>", "<%1$0*2$d>", 42, 8);
	assert_printf_equals("<00000042>", "<%2$0*1$d>", 8, 42);
	assert_printf_equals("<00000042>", "<%1$0*2$lld>", 42ll, 8);
	assert_printf_equals("<00000042>", "<%2$0*1$lld>", 8, 42ll);
	assert_printf_equals("<      42>", "<%1$*2$d>", 42, 8);
	assert_printf_equals("<      42>", "<%2$*1$d>", 8, 42);
	assert_printf_equals("<      42>", "<%1$*2$lld>", 42ll, 8);
	assert_printf_equals("<      42>", "<%2$*1$lld>", 8, 42ll);
	assert_printf_equals("<42      >", "<%1$-*2$d>", 42, 8);
	assert_printf_equals("<42      >", "<%2$-*1$d>", 8, 42);
	assert_printf_equals("<42      >", "<%1$-*2$lld>", 42ll, 8);
	assert_printf_equals("<42      >", "<%2$-*1$lld>", 8, 42ll);

	/* This used to break due to a (now-fixed) bug with positional argument pre-loading. */
	assert_printf_equals("PRE\"Foobar\"MID00001234POST",
	                     "PRE%2$.6qMID%1$0.8xPOST", 0x1234, "Foobar");
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_POSITIONAL_PRINTF_C */
