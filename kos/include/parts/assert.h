/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __do_assert
#include "assert-failed.h"
#include "../features.h"
#include "../__stdinc.h"

/* Define `static_assert()', optionally with  no-message
 * overload when KOS or isoc++17 extensions are enabled. */
#if !defined(static_assert) && (defined(__USE_ISOC11) || defined(__USE_ISOCXX11) || defined(__USE_KOS))
#if (defined(__STATIC_ASSERT_IS_static_assert) || \
     (defined(__cpp_static_assert) && __cpp_static_assert + 0 >= 201411))
/* the message argument is already optional! */
#elif defined(__USE_KOS) || defined(__USE_ISOCXX17)
/* Emulate `static_assert()' such that the message becomes optional. */
#include <hybrid/pp/__va_nargs.h>
#ifdef __HYBRID_PP_VA_OVERLOAD
#ifdef __STATIC_ASSERT_IS_static_assert
#define __PRIVATE_static_assert_1(a) static_assert(a)
#else /* __STATIC_ASSERT_IS_static_assert */
#define __PRIVATE_static_assert_1(a) __STATIC_ASSERT(a)
#endif /* !__STATIC_ASSERT_IS_static_assert */
#ifdef __STATIC_ASSERT_MSG_IS_static_assert
#define __PRIVATE_static_assert_2(a, msg) static_assert(a, msg)
#define __PRIVATE_static_assert_3(a, b, msg) static_assert((a, b), msg)
#define __PRIVATE_static_assert_4(a, b, c, msg) static_assert((a, b, c), msg)
#define __PRIVATE_static_assert_5(a, b, c, d, msg) static_assert((a, b, c, d), msg)
#define __PRIVATE_static_assert_6(a, b, c, d, e, msg) static_assert((a, b, c, d, e), msg)
#define __PRIVATE_static_assert_7(a, b, c, d, e, f, msg) static_assert((a, b, c, d, e, f), msg)
#define __PRIVATE_static_assert_8(a, b, c, d, e, f, g, msg) static_assert((a, b, c, d, e, f, g), msg)
#define __PRIVATE_static_assert_9(a, b, c, d, e, f, g, h, msg) static_assert((a, b, c, d, e, f, g, h), msg)
#else /* __STATIC_ASSERT_MSG_IS_static_assert */
#define __PRIVATE_static_assert_2(a, msg) __STATIC_ASSERT_MSG(a, msg)
#define __PRIVATE_static_assert_3(a, b, msg) __STATIC_ASSERT_MSG((a, b), msg)
#define __PRIVATE_static_assert_4(a, b, c, msg) __STATIC_ASSERT_MSG((a, b, c), msg)
#define __PRIVATE_static_assert_5(a, b, c, d, msg) __STATIC_ASSERT_MSG((a, b, c, d), msg)
#define __PRIVATE_static_assert_6(a, b, c, d, e, msg) __STATIC_ASSERT_MSG((a, b, c, d, e), msg)
#define __PRIVATE_static_assert_7(a, b, c, d, e, f, msg) __STATIC_ASSERT_MSG((a, b, c, d, e, f), msg)
#define __PRIVATE_static_assert_8(a, b, c, d, e, f, g, msg) __STATIC_ASSERT_MSG((a, b, c, d, e, f, g), msg)
#define __PRIVATE_static_assert_9(a, b, c, d, e, f, g, h, msg) __STATIC_ASSERT_MSG((a, b, c, d, e, f, g, h), msg)
#endif /* !__STATIC_ASSERT_MSG_IS_static_assert */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define static_assert(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_static_assert_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define static_assert(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_static_assert_, (args))(args)
#else /* ... */
#define static_assert __STATIC_ASSERT_MSG
#endif /* !... */
#else /* __HYBRID_PP_VA_OVERLOAD */
#define static_assert __STATIC_ASSERT_MSG
#endif /* !__HYBRID_PP_VA_OVERLOAD */
#elif (__has_feature(cxx_static_assert) ||                                                                \
       (defined(__cpp_static_assert) && __cpp_static_assert + 0 != 0) ||                                  \
       (__GCC_VERSION_NUM >= 40300 && (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)) || \
       (defined(__IBMCPP_STATIC_ASSERT) && __IBMCPP_STATIC_ASSERT + 0) ||                                 \
       (defined(__cplusplus) &&                                                                           \
        ((defined(__BORLANDC__) && defined(__CODEGEAR_0X_SUPPORT__) && __BORLANDC__ + 0 >= 0x610) ||      \
         (defined(__CODEGEARC__) && __CODEGEARC__ + 0 > 0x620) ||                                         \
         (defined(_MSC_VER) && _MSC_VER >= 1600))))
/* `static_assert' is defined by the compiler! (don't re-define it) */
#else /* Builtin... */
#define static_assert __STATIC_ASSERT_MSG
#endif /* Emulated... */
#endif /* !static_assert */

/* Need KOS extensions for compile-time `assert()' support.
 * STDC-compliant code is allowed to use  `assert(0)' as an alias for  `abort()',
 * however  with  this compile-time  assert extension,  such  code can  no longer
 * be compiled (which is intentional, and  the whole purpose of this  extension),
 * meaning that this behavior has to be opt-in, which it is by use of _KOS_SOURCE
 * or  _KOS_KERNEL_SOURCE, or simply being apart of  the kernel core, or a driver
 * module to-be loaded into the KOS kernel. */
#undef __do_cassert_wrapper
#if (defined(__USE_KOS) || defined(__USE_KOS_KERNEL)) && \
     0 /* I keep having problems with this. - GCC seems to be unable to fully deal with this... */
#if !defined(__NO_builtin_choose_expr) && \
    !defined(__NO_builtin_constant_p) && 0
/* This  one  doesn't seem  to work...  Apparently,  GCC won't  evaluate the
 * expression not chosen,  however it  will still compile  it, meaning  that
 * static_assert() with a  non-constant expression will  produce a  compiler
 * error. I guess I can live with that, given that `__builtin_choose_expr()'
 * is a GCC extension,  it stands to  reason that GCC  is allowed to  decide
 * what can and what cannot be done with it. */
/************************************************************************
 * Compile-time assert support:                                         *
 * __builtin_choose_expr(__builtin_constant_p(...),                     *
 *                       ({ static_assert(...) }),                      *
 *                       runtime_assert(...))                           *
 ************************************************************************/
#ifndef __NO_XBLOCK
#define __do_cassert_wrapper(expr, expr_str, rassert) \
	__builtin_choose_expr(__builtin_constant_p(!!(expr)), __XBLOCK({ __STATIC_ASSERT_MSG(expr, expr_str); (void)0; }), rassert)
#else /* __NO_XBLOCK */
#define __do_cassert_wrapper(expr, expr_str, rassert) \
	__builtin_choose_expr(__builtin_constant_p(!!(expr)), (void)sizeof(int[(expr) ? 1 : -1]), rassert)
#endif /* !__NO_XBLOCK */
#elif defined(__COMPILER_HAVE_VARIABLE_LENGTH_ARRAYS) && !defined(__NO_XBLOCK)
/************************************************************************
 * Compile-time assert support:                                         *
 * (0 ? (int(*)[(...) ? 1 : -1])0 : runtime_assert(...))                *
 ************************************************************************/
/* NOTE: The  VLA  assertion  must   be  wrapped  in  an   expression-block.
 *       Otherwise, the vla-array-size-expression will be assembled, despite
 *       being apart of a dead branch. (s.a. the following bug report  which
 *       I've submitted: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92641) */
#ifndef __NO_builtin_constant_p
#define __do_cassert_wrapper(expr, expr_str, rassert) \
	(__builtin_constant_p(expr) ? (0 ? __XBLOCK({ (void)(int(*)[(expr) ? 1 : -1])0; }) : (void)0) : rassert)
#else /* !__NO_builtin_constant_p */
#define __do_cassert_wrapper(expr, expr_str, rassert) \
	(0 ? __XBLOCK({ (void)(int(*)[(expr) ? 1 : -1])0; }) : rassert)
#endif /* __NO_builtin_constant_p */
#endif /* compile-time-assert... */
#endif /* __USE_KOS || __USE_KOS_KERNEL */

#ifdef __do_cassert_wrapper
#if defined(__USE_KOS_KERNEL) && defined(__assertion_check) && !defined(__NO_XBLOCK)
#ifdef __NO_builtin_expect
#define __do_assert(expr, expr_str)          __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_check(expr_str)); (void)0; }))
#define __do_assert_noreturn(expr, expr_str) __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failed(expr_str), 0)))
#define __do_assert_assume(expr, expr_str)   __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_check(expr_str)); (void)0; }))
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __do_assertf(expr, expr_str, ...)          __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; }))
#define __do_assert_noreturnf(expr, expr_str, ...) __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#define __do_assert_assumef(expr, expr_str, ...)   __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; }))
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __do_assertf(expr, expr_str, format...)          __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_checkf(expr_str, format)); (void)0; }))
#define __do_assert_noreturnf(expr, expr_str, format...) __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failedf(expr_str, format), 0)))
#define __do_assert_assumef(expr, expr_str, format...)   __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_checkf(expr_str, format)); (void)0; }))
#endif /* ... */
#else /* __NO_builtin_expect */
#define __do_assert(expr, expr_str)          __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_check(expr_str)); (void)0; }))
#define __do_assert_noreturn(expr, expr_str) __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0)))
#define __do_assert_assume(expr, expr_str)   __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_check(expr_str)); (void)0; }))
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __do_assertf(expr, expr_str, ...)          __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; }))
#define __do_assert_noreturnf(expr, expr_str, ...) __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#define __do_assert_assumef(expr, expr_str, ...)   __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; }))
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __do_assertf(expr, expr_str, format...)          __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_checkf(expr_str, format)); (void)0; }))
#define __do_assert_noreturnf(expr, expr_str, format...) __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, format), 0)))
#define __do_assert_assumef(expr, expr_str, format...)   __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_checkf(expr_str, format)); (void)0; }))
#endif /* ... */
#endif /* !__NO_builtin_expect */
#else /* __USE_KOS_KERNEL */
#ifdef __NO_builtin_expect
#define __do_assert(expr, expr_str)          __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failed(expr_str), 0)))
#define __do_assert_noreturn(expr, expr_str) __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failed(expr_str), 0)))
#define __do_assert_assume(expr, expr_str)   __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failed(expr_str), 0)))
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __do_assertf(expr, expr_str, ...)        __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#define __do_assert_assumef(expr, expr_str, ...) __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __do_assertf(expr, expr_str, format...)        __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failedf(expr_str, format), 0)))
#define __do_assert_assumef(expr, expr_str, format...) __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failedf(expr_str, format), 0)))
#endif /* ... */
#else /* __NO_builtin_expect */
#define __do_assert(expr, expr_str)          __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0)))
#define __do_assert_noreturn(expr, expr_str) __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0)))
#define __do_assert_assume(expr, expr_str)   __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0)))
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __do_assertf(expr, expr_str, ...)          __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#define __do_assert_noreturnf(expr, expr_str, ...) __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#define __do_assert_assumef(expr, expr_str, ...)   __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __do_assertf(expr, expr_str, format...)          __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, format), 0)))
#define __do_assert_noreturnf(expr, expr_str, format...) __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, format), 0)))
#define __do_assert_assumef(expr, expr_str, format...)   __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, format), 0)))
#endif /* ... */
#endif /* !__NO_builtin_expect */
#endif /* !__USE_KOS_KERNEL */
#else /* __do_cassert_wrapper */
#if defined(__USE_KOS_KERNEL) && defined(__assertion_check) && !defined(__NO_XBLOCK)
#ifdef __NO_builtin_expect
#define __do_assert(expr, expr_str)          __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_check(expr_str)); (void)0; })
#define __do_assert_noreturn(expr, expr_str) (void)(!!(expr) || (__assertion_failed(expr_str), 0))
#define __do_assert_assume(expr, expr_str)   __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_check(expr_str)); (void)0; })
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __do_assertf(expr, expr_str, ...)          __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; })
#define __do_assert_noreturnf(expr, expr_str, ...) (void)(!!(expr) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#define __do_assert_assumef(expr, expr_str, ...)   __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; })
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __do_assertf(expr, expr_str, format...)          __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_checkf(expr_str, format)); (void)0; })
#define __do_assert_noreturnf(expr, expr_str, format...) (void)(!!(expr) || (__assertion_failedf(expr_str, format), 0))
#define __do_assert_assumef(expr, expr_str, format...)   __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_checkf(expr_str, format)); (void)0; })
#endif /* ... */
#else /* __NO_builtin_expect */
#define __do_assert(expr, expr_str)          __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_check(expr_str)); (void)0; })
#define __do_assert_noreturn(expr, expr_str) (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0))
#define __do_assert_assume(expr, expr_str)   __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_check(expr_str)); (void)0; })
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __do_assertf(expr, expr_str, ...)          __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; })
#define __do_assert_noreturnf(expr, expr_str, ...) (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#define __do_assert_assumef(expr, expr_str, ...)   __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; })
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __do_assertf(expr, expr_str, format...)          __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_checkf(expr_str, format)); (void)0; })
#define __do_assert_noreturnf(expr, expr_str, format...) (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, format), 0))
#define __do_assert_assumef(expr, expr_str, format...)   __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_checkf(expr_str, format)); (void)0; })
#endif /* ... */
#endif /* !__NO_builtin_expect */
#else /* __USE_KOS_KERNEL */
#ifdef __NO_builtin_expect
#define __do_assert(expr, expr_str)          (void)(!!(expr) || (__assertion_failed(expr_str), 0))
#define __do_assert_noreturn(expr, expr_str) (void)(!!(expr) || (__assertion_failed(expr_str), 0))
#define __do_assert_assume(expr, expr_str)   (void)(!!(expr) || (__assertion_failed(expr_str), 0))
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __do_assertf(expr, expr_str, ...)        (void)(!!(expr) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#define __do_assert_assumef(expr, expr_str, ...) (void)(!!(expr) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __do_assertf(expr, expr_str, format...)        (void)(!!(expr) || (__assertion_failedf(expr_str, format), 0))
#define __do_assert_assumef(expr, expr_str, format...) (void)(!!(expr) || (__assertion_failedf(expr_str, format), 0))
#endif /* ... */
#else /* __NO_builtin_expect */
#define __do_assert(expr, expr_str)          (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0))
#define __do_assert_noreturn(expr, expr_str) (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0))
#define __do_assert_assume(expr, expr_str)   (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0))
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __do_assertf(expr, expr_str, ...)          (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#define __do_assert_noreturnf(expr, expr_str, ...) (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#define __do_assert_assumef(expr, expr_str, ...)   (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __do_assertf(expr, expr_str, format...)          (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, format), 0))
#define __do_assert_noreturnf(expr, expr_str, format...) (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, format), 0))
#define __do_assert_assumef(expr, expr_str, format...)   (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, format), 0))
#endif /* ... */
#endif /* !__NO_builtin_expect */
#endif /* !__USE_KOS_KERNEL */
#endif /* !__do_cassert_wrapper */
#endif /* !__do_assert */
