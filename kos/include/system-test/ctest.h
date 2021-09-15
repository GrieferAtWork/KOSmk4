/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _SYSTEM_TEST_CTEST_H
#define _SYSTEM_TEST_CTEST_H 1

#include <__stdinc.h>

#if defined(__KOS__) && defined(__KERNEL__)
#include <kernel/selftest.h>
#else /* __KOS__ && __KERNEL__ */

#undef NDEBUG /* We can't have assertions be disabled! */

#include "api.h"

#include <__crt.h>

#include <hybrid/__assert.h>

#if !defined(__INSIDE_LIBTEST) && !defined(__DEEMON__)
#error "Only include this file from within *.ctest files that are apart of /bin/system-test"
#endif /* __INSIDE_LIBTEST */


#ifdef __CC__
__DECL_BEGIN

struct testdecl {
	char const       *td_name;         /* [1..1] Test name */
	char const       *td_file;         /* [1..1] Test filename */
	unsigned int      td_line;         /* Test line number */
	void (__LIBKCALL *td_func)(void);  /* [1..1] Test function */
};

#define DEFINE_TEST(name)                                      \
	__PRIVATE __ATTR_USED void __LIBKCALL test_##name(void);   \
	__PRIVATE __ATTR_USED __ATTR_SECTION(".data.system_tests") \
	struct testdecl __decl_##name = {                          \
		.td_name = #name,                                      \
		.td_file = __FILE__,                                   \
		.td_line = __LINE__,                                   \
		.td_func = &test_##name,                               \
	};                                                         \
	__PRIVATE __ATTR_USED void __LIBKCALL test_##name(void)

__INTDEF void __NOTHROW_NCX(__VLIBKCALL ctest_subtestf)(char const *__restrict __format, ...);
__INTDEF void __NOTHROW_NCX(__LIBKCALL ctest_vsubtestf)(char const *__restrict __format, __builtin_va_list __args);
__INTDEF void __NOTHROW_NCX(__VLIBKCALL ctest_substatf)(char const *__restrict __format, ...);
__INTDEF void __NOTHROW_NCX(__LIBKCALL ctest_vsubstatf)(char const *__restrict __format, __builtin_va_list __args);


__DECL_END
#endif /* __CC__ */
#endif /* !__KOS__ || !__KERNEL__ */

/************************************************************************/
/* Assertion check helpers                                              */
/************************************************************************/

#include <parts/assert-failed.h>
#ifdef __assertion_checkf
#define _OPt(a, op, b, T, PRIt)                                                         \
	do {                                                                                \
		for (;;) {                                                                      \
			T _a = (T)(a), _b = (T)(b);                                                 \
			if (_a op _b)                                                               \
				break;                                                                  \
			if (!__assertion_checkf(#a " " #op " " #b,                                  \
			                        #a " " #op " " #b " (%" PRIt " " #op " %" PRIt ")", \
			                        _a, _b))                                            \
				break;                                                                  \
		}                                                                               \
	}	__WHILE0
#else /* __assertion_checkf */
#include <parts/assert.h>
#ifdef __do_assertf
#define _OPt(a, op, b, T, PRIt, a_str, b_str)                                  \
	do {                                                                       \
		T _a = (T)(a), _b = (T)(b);                                            \
		__do_assertf(_a op _b, a_str " " #op " " b_str,                        \
		             a_str " " #op " " b_str " (%" PRIt " " #op " %" PRIt ")", \
		             _a, _b);                                                  \
	}	__WHILE0
#else /* __do_assertf */
#include <assert.h>
#define _OPt(a, op, b, T, PRIt) assert((T)(a) op (T)(b))
#endif /* !__do_assertf */
#endif /* !__assertion_checkf */

#include <inttypes.h>

/*[[[deemon
for (local name, op: {
	("LO", "<"),
	("LE", "<="),
	("EQ", "=="),
	("NE", "!="),
	("GR", ">"),
	("GE", ">="),
}) {
	for (local i, T, PRIt: {
		("d", "int", "\"d\""),
		("u", "unsigned int", "\"u\""),
		("x", "unsigned int", "\"x\""),
		("s", "size_t", "PRIuSIZ"),
		("ss", "ssize_t", "PRIdSIZ"),
		("p", "uintptr_t", "\"p\""),
		("x32", "uint32_t", "PRIx32"),
		("u32", "uint32_t", "PRIu32"),
		("d32", "int32_t", "PRId32"),
		("x64", "uint64_t", "PRIx64"),
		("u64", "uint64_t", "PRIu64"),
		("d64", "int64_t", "PRId64"),
	}) {
		print("#define ", name, i, "(a, b) _OPt(a, ", op, ", b, ", T, ", ", PRIt, ", #a, #b)");
	}
	print;
}
]]]*/
#define LOd(a, b) _OPt(a, <, b, int, "d", #a, #b)
#define LOu(a, b) _OPt(a, <, b, unsigned int, "u", #a, #b)
#define LOx(a, b) _OPt(a, <, b, unsigned int, "x", #a, #b)
#define LOs(a, b) _OPt(a, <, b, size_t, PRIuSIZ, #a, #b)
#define LOss(a, b) _OPt(a, <, b, ssize_t, PRIdSIZ, #a, #b)
#define LOp(a, b) _OPt(a, <, b, uintptr_t, "p", #a, #b)
#define LOx32(a, b) _OPt(a, <, b, uint32_t, PRIx32, #a, #b)
#define LOu32(a, b) _OPt(a, <, b, uint32_t, PRIu32, #a, #b)
#define LOd32(a, b) _OPt(a, <, b, int32_t, PRId32, #a, #b)
#define LOx64(a, b) _OPt(a, <, b, uint64_t, PRIx64, #a, #b)
#define LOu64(a, b) _OPt(a, <, b, uint64_t, PRIu64, #a, #b)
#define LOd64(a, b) _OPt(a, <, b, int64_t, PRId64, #a, #b)

#define LEd(a, b) _OPt(a, <=, b, int, "d", #a, #b)
#define LEu(a, b) _OPt(a, <=, b, unsigned int, "u", #a, #b)
#define LEx(a, b) _OPt(a, <=, b, unsigned int, "x", #a, #b)
#define LEs(a, b) _OPt(a, <=, b, size_t, PRIuSIZ, #a, #b)
#define LEss(a, b) _OPt(a, <=, b, ssize_t, PRIdSIZ, #a, #b)
#define LEp(a, b) _OPt(a, <=, b, uintptr_t, "p", #a, #b)
#define LEx32(a, b) _OPt(a, <=, b, uint32_t, PRIx32, #a, #b)
#define LEu32(a, b) _OPt(a, <=, b, uint32_t, PRIu32, #a, #b)
#define LEd32(a, b) _OPt(a, <=, b, int32_t, PRId32, #a, #b)
#define LEx64(a, b) _OPt(a, <=, b, uint64_t, PRIx64, #a, #b)
#define LEu64(a, b) _OPt(a, <=, b, uint64_t, PRIu64, #a, #b)
#define LEd64(a, b) _OPt(a, <=, b, int64_t, PRId64, #a, #b)

#define EQd(a, b) _OPt(a, ==, b, int, "d", #a, #b)
#define EQu(a, b) _OPt(a, ==, b, unsigned int, "u", #a, #b)
#define EQx(a, b) _OPt(a, ==, b, unsigned int, "x", #a, #b)
#define EQs(a, b) _OPt(a, ==, b, size_t, PRIuSIZ, #a, #b)
#define EQss(a, b) _OPt(a, ==, b, ssize_t, PRIdSIZ, #a, #b)
#define EQp(a, b) _OPt(a, ==, b, uintptr_t, "p", #a, #b)
#define EQx32(a, b) _OPt(a, ==, b, uint32_t, PRIx32, #a, #b)
#define EQu32(a, b) _OPt(a, ==, b, uint32_t, PRIu32, #a, #b)
#define EQd32(a, b) _OPt(a, ==, b, int32_t, PRId32, #a, #b)
#define EQx64(a, b) _OPt(a, ==, b, uint64_t, PRIx64, #a, #b)
#define EQu64(a, b) _OPt(a, ==, b, uint64_t, PRIu64, #a, #b)
#define EQd64(a, b) _OPt(a, ==, b, int64_t, PRId64, #a, #b)

#define NEd(a, b) _OPt(a, !=, b, int, "d", #a, #b)
#define NEu(a, b) _OPt(a, !=, b, unsigned int, "u", #a, #b)
#define NEx(a, b) _OPt(a, !=, b, unsigned int, "x", #a, #b)
#define NEs(a, b) _OPt(a, !=, b, size_t, PRIuSIZ, #a, #b)
#define NEss(a, b) _OPt(a, !=, b, ssize_t, PRIdSIZ, #a, #b)
#define NEp(a, b) _OPt(a, !=, b, uintptr_t, "p", #a, #b)
#define NEx32(a, b) _OPt(a, !=, b, uint32_t, PRIx32, #a, #b)
#define NEu32(a, b) _OPt(a, !=, b, uint32_t, PRIu32, #a, #b)
#define NEd32(a, b) _OPt(a, !=, b, int32_t, PRId32, #a, #b)
#define NEx64(a, b) _OPt(a, !=, b, uint64_t, PRIx64, #a, #b)
#define NEu64(a, b) _OPt(a, !=, b, uint64_t, PRIu64, #a, #b)
#define NEd64(a, b) _OPt(a, !=, b, int64_t, PRId64, #a, #b)

#define GRd(a, b) _OPt(a, >, b, int, "d", #a, #b)
#define GRu(a, b) _OPt(a, >, b, unsigned int, "u", #a, #b)
#define GRx(a, b) _OPt(a, >, b, unsigned int, "x", #a, #b)
#define GRs(a, b) _OPt(a, >, b, size_t, PRIuSIZ, #a, #b)
#define GRss(a, b) _OPt(a, >, b, ssize_t, PRIdSIZ, #a, #b)
#define GRp(a, b) _OPt(a, >, b, uintptr_t, "p", #a, #b)
#define GRx32(a, b) _OPt(a, >, b, uint32_t, PRIx32, #a, #b)
#define GRu32(a, b) _OPt(a, >, b, uint32_t, PRIu32, #a, #b)
#define GRd32(a, b) _OPt(a, >, b, int32_t, PRId32, #a, #b)
#define GRx64(a, b) _OPt(a, >, b, uint64_t, PRIx64, #a, #b)
#define GRu64(a, b) _OPt(a, >, b, uint64_t, PRIu64, #a, #b)
#define GRd64(a, b) _OPt(a, >, b, int64_t, PRId64, #a, #b)

#define GEd(a, b) _OPt(a, >=, b, int, "d", #a, #b)
#define GEu(a, b) _OPt(a, >=, b, unsigned int, "u", #a, #b)
#define GEx(a, b) _OPt(a, >=, b, unsigned int, "x", #a, #b)
#define GEs(a, b) _OPt(a, >=, b, size_t, PRIuSIZ, #a, #b)
#define GEss(a, b) _OPt(a, >=, b, ssize_t, PRIdSIZ, #a, #b)
#define GEp(a, b) _OPt(a, >=, b, uintptr_t, "p", #a, #b)
#define GEx32(a, b) _OPt(a, >=, b, uint32_t, PRIx32, #a, #b)
#define GEu32(a, b) _OPt(a, >=, b, uint32_t, PRIu32, #a, #b)
#define GEd32(a, b) _OPt(a, >=, b, int32_t, PRId32, #a, #b)
#define GEx64(a, b) _OPt(a, >=, b, uint64_t, PRIx64, #a, #b)
#define GEu64(a, b) _OPt(a, >=, b, uint64_t, PRIu64, #a, #b)
#define GEd64(a, b) _OPt(a, >=, b, int64_t, PRId64, #a, #b)
/*[[[end]]]*/


#endif /* !_SYSTEM_TEST_CTEST_H */
