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
#ifndef _SYSTEM_TEST_CTEST_H
#define _SYSTEM_TEST_CTEST_H 1
#undef NDEBUG /* We can't have assertions be disabled! */

#include "api.h"

#include <__crt.h>

#include <hybrid/__assert.h>

#ifndef __INSIDE_LIBTEST
#error "Only include this file from within *.ctest files that are apart of /bin/system-test"
#endif /* __INSIDE_LIBTEST */


#ifdef __CC__
__DECL_BEGIN

struct testdecl {
	char const  *td_name;         /* [1..1] Test name */
	char const  *td_file;         /* [1..1] Test filename */
	unsigned int td_line;         /* Test line number */
	void       (*td_func)(void);  /* [1..1] Test function */
};

#define DEFINE_TEST(name)                                                                        \
	__PRIVATE __ATTR_USED void test_##name(void);                                                \
	__PRIVATE __ATTR_USED __ATTR_SECTION(".data.system_tests") struct testdecl __decl_##name = { \
		.td_name = #name,                                                                        \
		.td_file = __FILE__,                                                                     \
		.td_line = __LINE__,                                                                     \
		.td_func = &test_##name,                                                                 \
	};                                                                                           \
	__PRIVATE __ATTR_USED void test_##name(void)

__INTDEF void __NOTHROW_NCX(__VLIBCCALL ctest_subtestf)(char const *__restrict __format, ...);
__INTDEF void __NOTHROW_NCX(__LIBCCALL ctest_vsubtestf)(char const *__restrict __format, __builtin_va_list __args);
__INTDEF void __NOTHROW_NCX(__VLIBCCALL ctest_substatf)(char const *__restrict __format, ...);
__INTDEF void __NOTHROW_NCX(__LIBCCALL ctest_vsubstatf)(char const *__restrict __format, __builtin_va_list __args);


__DECL_END
#endif /* __CC__ */


#endif /* !_SYSTEM_TEST_CTEST_H */
