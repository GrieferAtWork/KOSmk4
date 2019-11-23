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
#ifndef __do_assert
#include "assert-failed.h"

#ifndef NDEBUG
#include "../features.h"

/* Need KOS extensions for compile-time `assert()' support.
 * STDC-compliant code is allowed to use `assert(0)' as an alias for `abort()',
 * however with this compile-time assert extension, such code can no longer
 * be compiled (which is intentional, and the whole purpose of this extension),
 * meaning that this behavior has to be opt-in, which it is by use of _KOS_SOURCE
 * or _KOS_KERNEL_SOURCE, or simply being apart of the kernel core, or a driver
 * module to-be loaded into the KOS kernel. */
#undef __do_cassert_wrapper
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
#if !defined(__NO_builtin_choose_expr) && \
    !defined(__NO_builtin_constant_p) && 0 /* This one doesn't seem to work... */
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
/* NOTE: The VLA assertion must be wrapped in an expression-block.
 *       Otherwise, the vla-array-size-expression will be assembled, despite
 *       being apart of a head branch. (s.a. the following but report which
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
#define __do_assert(expr, expr_str)        __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_check(expr_str)); (void)0; }))
#define __do_assert0(expr, expr_str)       __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failed(expr_str), 0)))
#define __do_asserta(expr, expr_str)       __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_check(expr_str)); (void)0; }))
#define __do_assertf(expr, expr_str, ...)  __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; }))
#define __do_assert0f(expr, expr_str, ...) __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#define __do_assertaf(expr, expr_str, ...) __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; }))
#else /* __NO_builtin_expect */
#define __do_assert(expr, expr_str)        __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_check(expr_str)); (void)0; }))
#define __do_assert0(expr, expr_str)       __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0)))
#define __do_asserta(expr, expr_str)       __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_check(expr_str)); (void)0; }))
#define __do_assertf(expr, expr_str, ...)  __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; }))
#define __do_assert0f(expr, expr_str, ...) __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#define __do_assertaf(expr, expr_str, ...) __do_cassert_wrapper(expr, expr_str, __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; }))
#endif /* !__NO_builtin_expect */
#else /* __USE_KOS_KERNEL */
#ifdef __NO_builtin_expect
#define __do_assert(expr, expr_str)        __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failed(expr_str), 0)))
#define __do_assert0(expr, expr_str)       __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failed(expr_str), 0)))
#define __do_asserta(expr, expr_str)       __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failed(expr_str), 0)))
#define __do_assertf(expr, expr_str, ...)  __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#define __do_assertaf(expr, expr_str, ...) __do_cassert_wrapper(expr, expr_str, (void)(!!(expr) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#else /* __NO_builtin_expect */
#define __do_assert(expr, expr_str)        __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0)))
#define __do_assert0(expr, expr_str)       __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0)))
#define __do_asserta(expr, expr_str)       __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0)))
#define __do_assertf(expr, expr_str, ...)  __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#define __do_assert0f(expr, expr_str, ...) __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#define __do_assertaf(expr, expr_str, ...) __do_cassert_wrapper(expr, expr_str, (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0)))
#endif /* !__NO_builtin_expect */
#endif /* !__USE_KOS_KERNEL */
#else /* __do_cassert_wrapper */
#if defined(__USE_KOS_KERNEL) && defined(__assertion_check) && !defined(__NO_XBLOCK)
#ifdef __NO_builtin_expect
#define __do_assert(expr, expr_str)        __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_check(expr_str)); (void)0; })
#define __do_assert0(expr, expr_str)       (void)(!!(expr) || (__assertion_failed(expr_str), 0))
#define __do_asserta(expr, expr_str)       __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_check(expr_str)); (void)0; })
#define __do_assertf(expr, expr_str, ...)  __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; })
#define __do_assert0f(expr, expr_str, ...) (void)(!!(expr) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#define __do_assertaf(expr, expr_str, ...) __XBLOCK({ do if __untraced(expr) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; })
#else /* __NO_builtin_expect */
#define __do_assert(expr, expr_str)        __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_check(expr_str)); (void)0; })
#define __do_assert0(expr, expr_str)       (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0))
#define __do_asserta(expr, expr_str)       __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_check(expr_str)); (void)0; })
#define __do_assertf(expr, expr_str, ...)  __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; })
#define __do_assert0f(expr, expr_str, ...) (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#define __do_assertaf(expr, expr_str, ...) __XBLOCK({ do if __untraced(__builtin_expect(!!(expr), 1)) break; while __untraced(__assertion_checkf(expr_str, __VA_ARGS__)); (void)0; })
#endif /* !__NO_builtin_expect */
#else /* __USE_KOS_KERNEL */
#ifdef __NO_builtin_expect
#define __do_assert(expr, expr_str)        (void)(!!(expr) || (__assertion_failed(expr_str), 0))
#define __do_assert0(expr, expr_str)       (void)(!!(expr) || (__assertion_failed(expr_str), 0))
#define __do_asserta(expr, expr_str)       (void)(!!(expr) || (__assertion_failed(expr_str), 0))
#define __do_assertf(expr, expr_str, ...)  (void)(!!(expr) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#define __do_assertaf(expr, expr_str, ...) (void)(!!(expr) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#else /* __NO_builtin_expect */
#define __do_assert(expr, expr_str)        (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0))
#define __do_assert0(expr, expr_str)       (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0))
#define __do_asserta(expr, expr_str)       (void)(__builtin_expect(!!(expr), 1) || (__assertion_failed(expr_str), 0))
#define __do_assertf(expr, expr_str, ...)  (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#define __do_assert0f(expr, expr_str, ...) (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#define __do_assertaf(expr, expr_str, ...) (void)(__builtin_expect(!!(expr), 1) || (__assertion_failedf(expr_str, __VA_ARGS__), 0))
#endif /* !__NO_builtin_expect */
#endif /* !__USE_KOS_KERNEL */
#endif /* !__do_cassert_wrapper */


#elif !defined(__NO_builtin_assume)

#if defined(CONFIG_ASSERT_ASSUME_EVERYTHING) || defined(ASSERT_ASSUME_EVERYTHING)
#define __do_assert(expr, expr_str)        __builtin_assume(!!(expr))
#define __do_assert0(expr, expr_str)       __builtin_assume(!!(expr))
#define __do_asserta(expr, expr_str)       __builtin_assume(!!(expr))
#define __do_assertf(expr, expr_str, ...)  __builtin_assume(!!(expr))
#define __do_assert0f(expr, expr_str, ...) __builtin_assume(!!(expr))
#define __do_assertaf(expr, expr_str, ...) __builtin_assume(!!(expr))
#else /* CONFIG_ASSERT_ASSUME_EVERYTHING || ASSERT_ASSUME_EVERYTHING */
#define __do_assert(expr, expr_str)        (void)0
#define __do_assert0(expr, expr_str)       (void)0
#define __do_asserta(expr, expr_str)       __builtin_assume(!!(expr))
#define __do_assertf(expr, expr_str, ...)  (void)0
#define __do_assert0f(expr, expr_str, ...) (void)0
#define __do_assertaf(expr, expr_str, ...) __builtin_assume(!!(expr))
#endif /* !CONFIG_ASSERT_ASSUME_EVERYTHING && !ASSERT_ASSUME_EVERYTHING */

#else

#define __do_assert(expr, expr_str)        (void)0
#define __do_assert0(expr, expr_str)       (void)0
#define __do_asserta(expr, expr_str)       (void)0
#define __do_assertf(expr, expr_str, ...)  (void)0
#define __do_assert0f(expr, expr_str, ...) (void)0
#define __do_assertaf(expr, expr_str, ...) (void)0

#endif /* !NDEBUG */

#endif /* !__do_assert */
