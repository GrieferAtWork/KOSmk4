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

#if !defined(__INSIDE_LIBTEST) && !defined(__DEEMON__) && !defined(__LCLINT__)
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

#ifdef __INTELLISENSE__
#define __OP(makevars, cond, cond_novars, expr_str, ...)       (void)(cond_novars)
#define _OPtPOS(v, v_str)                                      (void)((v) >= 0)
#define _OPtPOSf(v, v_str, ...)                                (void)((v) >= 0)
#define _OPtCMP(a, op, b, a_str, b_str)                        (void)((a)op(b))
#define _OPtCMPf(a, op, b, a_str, b_str, format, ...)          (void)((a)op(b))
#define _OPtBITON(bitmask, word, bitmask_str, word_str)        (void)(((word) & (bitmask)) == (bitmask))
#define _OPtBITOFF(bitmask, word, bitmask_str, word_str)       (void)(((word) & (bitmask)) == 0)
#define _OPtBITONf(bitmask, word, bitmask_str, word_str, ...)  (void)(((word) & (bitmask)) == (bitmask))
#define _OPtBITOFFf(bitmask, word, bitmask_str, word_str, ...) (void)(((word) & (bitmask)) == 0)
#else /* __INTELLISENSE__ */
#include <parts/assert-failed.h>
#ifdef __assertion_checkf
#define __OPEXPAND(...) __VA_ARGS__
#define __OP(makevars, cond, cond_novars, expr_str, ...) \
	do {                                                 \
		__OPEXPAND makevars;                             \
		if (cond)                                        \
			break;                                       \
		if (!__assertion_checkf(expr_str, __VA_ARGS__))  \
			break;                                       \
	}	__WHILE1
#else /* __assertion_checkf */
#include <parts/assert.h>
#ifdef __do_assertf
#define __OPEXPAND(...) __VA_ARGS__
#define __OP(makevars, cond, cond_novars, expr_str, ...) \
	do {                                                 \
		__OPEXPAND makevars;                             \
		__do_assertf(cond, expr_str, __VA_ARGS__);       \
	}	__WHILE0
#else /* __do_assertf */
#include <assert.h>
#define __OP(makevars, cond, cond_novars, expr_str, ...) assert(cond_novars)
#endif /* !__do_assertf */
#endif /* !__assertion_checkf */

#include <bits/crt/inttypes.h>
#ifdef __NO_FPU
#define _TPRIfmt(Tob, fmtS, fmtU, fmtF, fmtP, ...)                                                                                                    \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), int),           fmtS("", __VA_ARGS__),                                  \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), unsigned),      fmtU("", __VA_ARGS__),                                  \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), long),          fmtS(__PRIN_PREFIX(__SIZEOF_LONG__), __VA_ARGS__),      \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), unsigned long), fmtU(__PRIN_PREFIX(__SIZEOF_LONG__), __VA_ARGS__),      \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), __LONGLONG),    fmtS(__PRIN_PREFIX(__SIZEOF_LONG_LONG__), __VA_ARGS__), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), __ULONGLONG),   fmtU(__PRIN_PREFIX(__SIZEOF_LONG_LONG__), __VA_ARGS__), \
	                      /*                                                               */ fmtP(__PRIP_PREFIX, __VA_ARGS__)))))))
#elif defined(__COMPILER_HAVE_LONGDOUBLE)
#define _TPRIfmt(Tob, fmtS, fmtU, fmtF, fmtP, ...)                                                                                                    \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), int),           fmtS("", __VA_ARGS__),                                  \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), unsigned),      fmtU("", __VA_ARGS__),                                  \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), long),          fmtS(__PRIN_PREFIX(__SIZEOF_LONG__), __VA_ARGS__),      \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), unsigned long), fmtU(__PRIN_PREFIX(__SIZEOF_LONG__), __VA_ARGS__),      \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), __LONGLONG),    fmtS(__PRIN_PREFIX(__SIZEOF_LONG_LONG__), __VA_ARGS__), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), __ULONGLONG),   fmtU(__PRIN_PREFIX(__SIZEOF_LONG_LONG__), __VA_ARGS__), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), float) ||                                                               \
	                      __builtin_types_compatible_p(__typeof__((Tob) + 0), double),        fmtF("", __VA_ARGS__),                                  \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), __LONGDOUBLE),  fmtF("L", __VA_ARGS__),                                 \
	                      /*                                                               */ fmtP(__PRIP_PREFIX, __VA_ARGS__)))))))))
#else /* ... */
#define _TPRIfmt(Tob, fmtS, fmtU, fmtF, fmtP, ...)                                                                                                    \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), int),           fmtS("", __VA_ARGS__),                                  \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), unsigned),      fmtU("", __VA_ARGS__),                                  \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), long),          fmtS(__PRIN_PREFIX(__SIZEOF_LONG__), __VA_ARGS__),      \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), unsigned long), fmtU(__PRIN_PREFIX(__SIZEOF_LONG__), __VA_ARGS__),      \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), __LONGLONG),    fmtS(__PRIN_PREFIX(__SIZEOF_LONG_LONG__), __VA_ARGS__), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), __ULONGLONG),   fmtU(__PRIN_PREFIX(__SIZEOF_LONG_LONG__), __VA_ARGS__), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((Tob) + 0), float) ||                                                               \
	                      __builtin_types_compatible_p(__typeof__((Tob) + 0), double),        fmtF("", __VA_ARGS__),                                  \
	                      /*                                                               */ fmtP(__PRIP_PREFIX, __VA_ARGS__))))))))
#endif /* !... */
#define __TPRIfmtposS(PRInPREFIX, _) "%" PRInPREFIX "d >= 0"
#define __TPRIfmtposU(PRInPREFIX, _) "%1$" PRInPREFIX "u[%#1$" PRInPREFIX "x] >= 0"
#define __TPRIfmtposF(PRInPREFIX, _) "%" PRInPREFIX "f >= 0.0"
#define __TPRIfmtposP(PRInPREFIX, _) "%p >= 0"
#define _OPtPOS(v, v_str)                                                             \
	__OP((__typeof__(v) _v = (v)), _v >= 0, (v) >= 0,                                 \
	     v_str " >= 0",                                                               \
	     _TPRIfmt(_v, __TPRIfmtposS, __TPRIfmtposU, __TPRIfmtposF, __TPRIfmtposP, ~), \
	     _v)
#define _OPtPOSf(v, v_str, ...) _OPtPOS(v, v_str) /* TODO */

#define __TPRIfmtcmpS(PRInPREFIX, op_str) "%" PRInPREFIX "d " op_str " %" PRInPREFIX "d"
#define __TPRIfmtcmpU(PRInPREFIX, op_str) "%1$" PRInPREFIX "u[%#1$" PRInPREFIX "x] " op_str " %2$" PRInPREFIX "u[%#2$" PRInPREFIX "x]"
#define __TPRIfmtcmpF(PRInPREFIX, op_str) "%" PRInPREFIX "f " op_str " %" PRInPREFIX "f"
#define __TPRIfmtcmpP(PRInPREFIX, op_str) "%p " op_str " %p"
#define _OPtCMP(a, op, b, a_str, b_str)                                                 \
	__OP((__typeof__(1 ? (a) : (b)) _a = (a), _b = (b)), _a op _b, (a)op(b),            \
	     a_str " " #op " " b_str,                                                       \
	     _TPRIfmt(_a, __TPRIfmtcmpS, __TPRIfmtcmpU, __TPRIfmtcmpF, __TPRIfmtcmpP, #op), \
	     _a, _b)
#define _OPtCMPf(a, op, b, a_str, b_str, format, ...) \
	_OPtCMP(a, op, b, a_str, b_str) /* TODO */

#define __TPRIfmtbitX(PRInPREFIX, _) "%1$" PRInPREFIX "u[%#1$" PRInPREFIX "x] & %2$" PRInPREFIX "u[%#2$" PRInPREFIX "x] = %3$" PRInPREFIX "u[%#3$" PRInPREFIX "x]"
#define _OPtBITON(bitmask, word, bitmask_str, word_str)                                  \
	__OP((__typeof__((bitmask) & (word)) _bitmask = (bitmask), _word = (word)),          \
	     (_bitmask & _word) == _bitmask, ((bitmask) & (word)) == (bitmask),              \
	     bitmask_str " & " word_str " == " bitmask_str,                                  \
	     _TPRIfmt(_word, __TPRIfmtbitX, __TPRIfmtbitX, __TPRIfmtbitX, __TPRIfmtbitX, ~), \
	     _bitmask, _word, _bitmask & _word)
#define _OPtBITOFF(bitmask, word, bitmask_str, word_str)                                 \
	__OP((__typeof__((bitmask) & (word)) _bitmask = (bitmask), _word = (word)),          \
	     !(_bitmask & _word), !((bitmask) & (word)),                                     \
	     bitmask_str " & " word_str " == 0",                                             \
	     _TPRIfmt(_word, __TPRIfmtbitX, __TPRIfmtbitX, __TPRIfmtbitX, __TPRIfmtbitX, ~), \
	     _bitmask, _word, _bitmask & _word)

#define __TPRIfmtbitXf(PRInPREFIX, _) "%" PRInPREFIX "u[%#" PRInPREFIX "x] & %" PRInPREFIX "u[%#" PRInPREFIX "x] = %" PRInPREFIX "u[%#" PRInPREFIX "x]"
#define _OPtBITONf(bitmask, word, bitmask_str, word_str, format, ...)                                    \
	__OP((__typeof__((bitmask) & (word)) _bitmask = (bitmask), _word = (word)),                          \
	     (_bitmask & _word) == _bitmask, ((bitmask) & (word)) == (bitmask),                              \
	     bitmask_str " & " word_str " == " bitmask_str,                                                  \
	     _TPRIfmt(_word, __TPRIfmtbitXf, __TPRIfmtbitXf, __TPRIfmtbitXf, __TPRIfmtbitXf, ~) "\n" format, \
	     _bitmask, _bitmask, _word, _word, _bitmask & _word, _bitmask & _word, ##__VA_ARGS__)
#define _OPtBITOFFf(bitmask, word, bitmask_str, word_str, format, ...)                                   \
	__OP((__typeof__((bitmask) & (word)) _bitmask = (bitmask), _word = (word)),                          \
	     !(_bitmask & _word), !((bitmask) & (word)),                                                     \
	     bitmask_str " & " word_str " == 0",                                                             \
	     _TPRIfmt(_word, __TPRIfmtbitXf, __TPRIfmtbitXf, __TPRIfmtbitXf, __TPRIfmtbitXf, ~) "\n" format, \
	     _bitmask, _bitmask, _word, _word, _bitmask & _word, _bitmask & _word, ##__VA_ARGS__)
#endif /* !__INTELLISENSE__ */

#include <libc/errno.h>
#include <libc/string.h>

#define _OPtSTR(a, op, b, a_str, b_str)            \
	__OP((char const *_a = (a), *_b = (b);         \
	      int _diff = __libc_strcmp(_a, _b)),      \
	     _diff op 0, __libc_strcmp(a, b) op 0,     \
	     "strcmp(" a_str ", " b_str ") " #op " 0", \
	     "strcmp(%1$p, %2$p) == %3$d\n"            \
	     "lhs: %1$q\n"                             \
	     "rhs: %2$q",                              \
	     _a, _b, _diff)
#define _OPtMEM(a, op, b, num_bytes, a_str, b_str, num_bytes_str)             \
	__OP((void const *_a = (a), *_b = (b); __size_t _num_bytes = (num_bytes); \
	      int _diff = __libc_memcmp(_a, _b, _num_bytes)),                     \
	     _diff op 0, __libc_memcmp(a, b, num_bytes) op 0,                     \
	     "memcmp(" a_str ", " b_str ", " num_bytes_str ") " #op " 0",         \
	     "memcmp(%1$p, %2$p, %3$" __PRIP_PREFIX "u) == %4$d\n"                \
	     "MEM[" a_str "]:\n"                                                  \
	     "%$3$1$[hex]\n"                                                      \
	     "MEM[" b_str "]:\n"                                                  \
	     "%$3$2$[hex]",                                                       \
	     _a, _b, _num_bytes, _diff)
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * HINT: "%$3$2$[hex]\n" is decoded as:#
 *         ||/|/|  /
 *         || | |-/
 *         || | |
 *         || | \- Output as hex
 *         || \--- Pointer operand    = args[2 - 1]
 *         |\----- Fixed-buffer width = args[3 - 1]
 *         \------ Fixed-buffer width prefix */
#define _OPtSTRf(a, op, b, a_str, b_str, format, ...) \
	__OP((char const *_a = (a), *_b = (b);            \
	      int _diff = __libc_strcmp(_a, _b)),         \
	     _diff op 0, __libc_strcmp(a, b) op 0,        \
	     "strcmp(" a_str ", " b_str ") " #op " 0",    \
	     "strcmp(%p, %p) == %d\n"                     \
	     "lhs: %q\n"                                  \
	     "rhs: %q\n" format,                          \
	     _a, _b, _diff, _a, _b, ##__VA_ARGS__)
#define _OPtMEMf(a, op, b, num_bytes, a_str, b_str, num_bytes_str, format, ...) \
	__OP((void const *_a = (a), *_b = (b); __size_t _num_bytes = (num_bytes);   \
	      int _diff = __libc_memcmp(_a, _b, _num_bytes)),                       \
	     _diff op 0, __libc_memcmp(a, b, num_bytes) op 0,                       \
	     "memcmp(" a_str ", " b_str ", " num_bytes_str ") " #op " 0",           \
	     "memcmp(%p, %p, %" __PRIP_PREFIX "u) == %d\n"                          \
	     "MEM[" a_str "]:\n"                                                    \
	     "%$[hex]\n"                                                            \
	     "MEM[" b_str "]:\n"                                                    \
	     "%$[hex]\n" format,                                                    \
	     _a, _b, _num_bytes, _diff, _num_bytes, _a, _num_bytes, _b, ##__VA_ARGS__)



/* Generic integer/pointer/float compare */
#define EQ(expected, actual)   _OPtCMP(expected, ==, actual, #expected, #actual)
#define NE(unexpected, actual) _OPtCMP(unexpected, !=, actual, #unexpected, #actual)
#define LO(lhs, rhs)           _OPtCMP(lhs, <, rhs, #lhs, #rhs)
#define LE(lhs, rhs)           _OPtCMP(lhs, <=, rhs, #lhs, #rhs)
#define GR(lhs, rhs)           _OPtCMP(lhs, >, rhs, #lhs, #rhs)
#define GE(lhs, rhs)           _OPtCMP(lhs, >=, rhs, #lhs, #rhs)

/* Generic integer/pointer/float compare (with extra message addend) */
#define EQf(expected, actual, format, ...)   _OPtCMPf(expected, ==, actual, #expected, #actual, format, __VA_ARGS__)
#define NEf(unexpected, actual, format, ...) _OPtCMPf(unexpected, !=, actual, #unexpected, #actual, format, __VA_ARGS__)
#define LOf(lhs, rhs, format, ...)           _OPtCMPf(lhs, <, rhs, #lhs, #rhs, format, __VA_ARGS__)
#define LEf(lhs, rhs, format, ...)           _OPtCMPf(lhs, <=, rhs, #lhs, #rhs, format, __VA_ARGS__)
#define GRf(lhs, rhs, format, ...)           _OPtCMPf(lhs, >, rhs, #lhs, #rhs, format, __VA_ARGS__)
#define GEf(lhs, rhs, format, ...)           _OPtCMPf(lhs, >=, rhs, #lhs, #rhs, format, __VA_ARGS__)

/* Assert: `{p} == NULL' or `{p} != NULL' */
#define __ISnull_FMT(p)                                                                    \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((p) + 0), char *) ||     \
	                      __builtin_types_compatible_p(__typeof__((p) + 0), char const *), \
	                      "Not null: %1$p (%1$q)",                                         \
	                      "Not null: %p")
#define ISnull(p)          __OP((void const *_p = (p)), !_p, !(p), #p " == NULL", __ISnull_FMT(p), _p)
#define ISnullf(p, ...)    __OP((void const *_p = (p)), !_p, !(p), #p " == NULL", __ISnull_FMT(p), _p) /* TODO */
#define ISnonnull(p)       __OP((void const *_p = (p)), _p, (p), #p " != NULL", __NULLPTR)
#define ISnonnullf(p, ...) __OP((void const *_p = (p)), _p, (p), #p " != NULL", __VA_ARGS__)

/* Assert: `{v} >= 0' */
#define ISpos(v)       _OPtPOS(v, #v)
#define ISposf(v, ...) _OPtPOSf(v, #v, __VA_ARGS__)

/* Assert: `errno == {expected_errno}' */
#define EQerrno(expected_errno)                                                           \
	__OP((__errno_t _expected_errno = (expected_errno), _errno_libc = __libc_geterrno()), \
	     _expected_errno == _errno_libc, (expected_errno) == __libc_geterrno(),           \
	     "errno == " #expected_errno,                                                     \
	     "%d[%s] == %d[%s]",                                                              \
	     _errno_libc, __libc_strerrorname_np(_errno_libc),                                \
	     _expected_errno, __libc_strerrorname_np(_expected_errno))
#define EQerrnof(expected_errno, format, ...)                                             \
	__OP((__errno_t _expected_errno = (expected_errno), _errno_libc = __libc_geterrno()), \
	     _expected_errno == _errno_libc, (expected_errno) == __libc_geterrno(),           \
	     "errno == " #expected_errno,                                                     \
	     "%d[%s] == %d[%s]\n" format,                                                     \
	     _errno_libc, __libc_strerrorname_np(_errno_libc),                                \
	     _expected_errno, __libc_strerrorname_np(_expected_errno), ##__VA_ARGS__)

/* Assert that a given bitset is all 1s or 0s in `word' */
#define ISbiton(set_bitmask, word)          _OPtBITON(set_bitmask, word, #set_bitmask, #word)
#define ISbitoff(clear_bitmask, word)       _OPtBITOFF(clear_bitmask, word, #clear_bitmask, #word)
#define ISbitonf(set_bitmask, word, ...)    _OPtBITONf(set_bitmask, word, #set_bitmask, #word, __VA_ARGS__)
#define ISbitofff(clear_bitmask, word, ...) _OPtBITOFFf(clear_bitmask, word, #clear_bitmask, #word, __VA_ARGS__)


/* Compare the contents of string (s.a. `strcmp(3)') */
#define EQstr(expected_strp, actual_strp) \
	_OPtSTR(expected_strp, ==, actual_strp, #expected_strp, #actual_strp)
#define NEstr(unexpected_strp, actual_strp) \
	_OPtSTR(unexpected_strp, !=, actual_strp, #unexpected_strp, #actual_strp)
#define LOstr(lhs, rhs) _OPtSTR(lhs, <, rhs, #lhs, #rhs)
#define LEstr(lhs, rhs) _OPtSTR(lhs, <=, rhs, #lhs, #rhs)
#define GRstr(lhs, rhs) _OPtSTR(lhs, >, rhs, #lhs, #rhs)
#define GEstr(lhs, rhs) _OPtSTR(lhs, >=, rhs, #lhs, #rhs)
#define EQstrf(expected_strp, actual_strp, ...) \
	_OPtSTRf(expected_strp, ==, actual_strp, #expected_strp, #actual_strp, __VA_ARGS__)
#define NEstrf(unexpected_strp, actual_strp, ...) \
	_OPtSTRf(unexpected_strp, !=, actual_strp, #unexpected_strp, #actual_strp, __VA_ARGS__)
#define LOstrf(lhs, rhs, ...) _OPtSTRf(lhs, <, rhs, #lhs, #rhs, __VA_ARGS__)
#define LEstrf(lhs, rhs, ...) _OPtSTRf(lhs, <=, rhs, #lhs, #rhs, __VA_ARGS__)
#define GRstrf(lhs, rhs, ...) _OPtSTRf(lhs, >, rhs, #lhs, #rhs, __VA_ARGS__)
#define GEstrf(lhs, rhs, ...) _OPtSTRf(lhs, >=, rhs, #lhs, #rhs, __VA_ARGS__)


/* Compare the contents of memory (s.lhs. `memcmp(3)') */
#define EQmem(expected_baseptr, actual_baseptr, num_bytes) \
	_OPtMEM(expected_baseptr, ==, actual_baseptr, num_bytes, #expected_baseptr, #actual_baseptr, #num_bytes)
#define NEmem(unexpected_baseptr, actual_baseptr, num_bytes) \
	_OPtMEM(unexpected_baseptr, !=, actual_baseptr, num_bytes, #unexpected_baseptr, #actual_baseptr, #num_bytes)
#define LOmem(lhs, rhs, num_bytes) _OPtMEM(lhs, <, rhs, num_bytes, #lhs, #rhs, #num_bytes)
#define LEmem(lhs, rhs, num_bytes) _OPtMEM(lhs, <=, rhs, num_bytes, #lhs, #rhs, #num_bytes)
#define GRmem(lhs, rhs, num_bytes) _OPtMEM(lhs, >, rhs, num_bytes, #lhs, #rhs, #num_bytes)
#define GEmem(lhs, rhs, num_bytes) _OPtMEM(lhs, >=, rhs, num_bytes, #lhs, #rhs, #num_bytes)
#define EQmemf(expected_baseptr, actual_baseptr, num_bytes, ...) \
	_OPtMEMf(expected_baseptr, ==, actual_baseptr, num_bytes, #expected_baseptr, #actual_baseptr, #num_bytes, __VA_ARGS__)
#define NEmemf(unexpected_baseptr, actual_baseptr, num_bytes, ...) \
	_OPtMEMf(unexpected_baseptr, !=, actual_baseptr, num_bytes, #unexpected_baseptr, #actual_baseptr, #num_bytes, __VA_ARGS__)
#define LOmemf(lhs, rhs, num_bytes, ...) _OPtMEMf(lhs, <, rhs, num_bytes, #lhs, #rhs, #num_bytes, __VA_ARGS__)
#define LEmemf(lhs, rhs, num_bytes, ...) _OPtMEMf(lhs, <=, rhs, num_bytes, #lhs, #rhs, #num_bytes, __VA_ARGS__)
#define GRmemf(lhs, rhs, num_bytes, ...) _OPtMEMf(lhs, >, rhs, num_bytes, #lhs, #rhs, #num_bytes, __VA_ARGS__)
#define GEmemf(lhs, rhs, num_bytes, ...) _OPtMEMf(lhs, >=, rhs, num_bytes, #lhs, #rhs, #num_bytes, __VA_ARGS__)


#endif /* !_SYSTEM_TEST_CTEST_H */
