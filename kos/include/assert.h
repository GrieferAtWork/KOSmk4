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
#ifndef __assertion_failed
#include "parts/assert.h"
#endif /* !__assertion_failed */

/* Undef the old assert definition to allow for re-definitions! (mandated by the C standard) */
#undef assert      /* Regular STD-C assert (with optional retry extension) */
#undef __asserta   /* Assert + assume */
#undef __assert0   /* Same as `assert', but noreturn when condition fails */
#undef __assertf   /* Assert + printf-like message */
#undef __assertaf  /* Assert + assume + printf-like message */
#undef __assert0f  /* Same as `__assertf', but noreturn when condition fails */
#ifdef __USE_KOS
#undef assert0     /* Alias for `__assert0' */
#undef asserta     /* Alias for `__asserta' */
#undef assertf     /* Alias for `__assertf' */
#undef assert0f    /* Alias for `__assert0f' */
#undef assertaf    /* Alias for `__assertaf' */
#endif /* __USE_KOS */

#ifdef __INTELLISENSE__
#define assert        __NAMESPACE_INT_SYM __check_assertion
#define __assert0     __NAMESPACE_INT_SYM __check_assertion
#define __asserta     __NAMESPACE_INT_SYM __check_assertion
#define __assertf     __NAMESPACE_INT_SYM __check_assertionf
#define __assertaf    __NAMESPACE_INT_SYM __check_assertionf
#ifdef __USE_KOS
#define asserta       __NAMESPACE_INT_SYM __check_assertion
#define assertf       __NAMESPACE_INT_SYM __check_assertionf
#define assert0f      __NAMESPACE_INT_SYM __check_assertionf
#define assertaf      __NAMESPACE_INT_SYM __check_assertionf
#endif /* __USE_KOS */
#elif !defined(NDEBUG)
#if defined(__USE_KOS_KERNEL) && defined(__assertion_check) && !defined(__NO_XBLOCK)
#ifdef __NO_builtin_expect
#define assert(expr)         __XBLOCK({do if __untraced(expr)break;while __untraced(__assertion_check(#expr));(void)0;})
#define __assert0(expr)      (void)(!!(expr) || (__assertion_failed(#expr),0))
#define __asserta(expr)      __XBLOCK({do if __untraced(expr)break;while __untraced(__assertion_check(#expr));(void)0;})
#define __assertf(expr, ...) __XBLOCK({do if __untraced(expr)break;while __untraced(__assertion_checkf(#expr,__VA_ARGS__));(void)0;})
#define __assert0f(expr, ...)(void)(!!(expr) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#define __assertaf(expr, ...)__XBLOCK({do if __untraced(expr)break;while __untraced(__assertion_checkf(#expr,__VA_ARGS__));(void)0;})
#ifdef __USE_KOS
#define assert0(expr)        (void)(!!(expr) || (__assertion_failed(#expr),0))
#define asserta(expr)        __XBLOCK({do if __untraced(expr)break;while __untraced(__assertion_check(#expr));(void)0;})
#define assertf(expr, ...)   __XBLOCK({do if __untraced(expr)break;while __untraced(__assertion_checkf(#expr,__VA_ARGS__));(void)0;})
#define assert0f(expr, ...)  (void)(!!(expr) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#define assertaf(expr, ...)  __XBLOCK({do if __untraced(expr)break;while __untraced(__assertion_checkf(#expr,__VA_ARGS__));(void)0;})
#endif /* __USE_KOS */
#else /* __NO_builtin_expect */
#define assert(expr)         __XBLOCK({do if __untraced(__builtin_expect(!!(expr),1))break;while __untraced(__assertion_check(#expr));(void)0;})
#define __assert0(expr)      (void)(__builtin_expect(!!(expr),1) || (__assertion_failed(#expr),0))
#define __asserta(expr)      __XBLOCK({do if __untraced(__builtin_expect(!!(expr),1))break;while __untraced(__assertion_check(#expr));(void)0;})
#define __assertf(expr, ...) __XBLOCK({do if __untraced(__builtin_expect(!!(expr),1))break;while __untraced(__assertion_checkf(#expr,__VA_ARGS__));(void)0;})
#define __assert0f(expr, ...)(void)(__builtin_expect(!!(expr),1) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#define __assertaf(expr, ...)__XBLOCK({do if __untraced(__builtin_expect(!!(expr),1))break;while __untraced(__assertion_checkf(#expr,__VA_ARGS__));(void)0;})
#ifdef __USE_KOS
#define assert0(expr)        (void)(__builtin_expect(!!(expr),1) || (__assertion_failed(#expr),0))
#define asserta(expr)        __XBLOCK({do if __untraced(__builtin_expect(!!(expr),1))break;while __untraced(__assertion_check(#expr));(void)0;})
#define assertf(expr, ...)   __XBLOCK({do if __untraced(__builtin_expect(!!(expr),1))break;while __untraced(__assertion_checkf(#expr,__VA_ARGS__));(void)0;})
#define assert0f(expr, ...)  (void)(__builtin_expect(!!(expr),1) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#define assertaf(expr, ...)  __XBLOCK({do if __untraced(__builtin_expect(!!(expr),1))break;while __untraced(__assertion_checkf(#expr,__VA_ARGS__));(void)0;})
#endif /* __USE_KOS */
#endif /* !__NO_builtin_expect */
#else /* __USE_KOS_KERNEL */
#ifdef __NO_builtin_expect
#define assert(expr)         (void)(!!(expr) || (__assertion_failed(#expr),0))
#define __assert0(expr)      (void)(!!(expr) || (__assertion_failed(#expr),0))
#define __asserta(expr)      (void)(!!(expr) || (__assertion_failed(#expr),0))
#define __assertf(expr, ...) (void)(!!(expr) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#define __assertaf(expr, ...)(void)(!!(expr) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#ifdef __USE_KOS
#define assert0(expr)        (void)(!!(expr) || (__assertion_failed(#expr),0))
#define asserta(expr)        (void)(!!(expr) || (__assertion_failed(#expr),0))
#define assertf(expr, ...)   (void)(!!(expr) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#define assert0f(expr, ...)  (void)(!!(expr) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#define assertaf(expr, ...)  (void)(!!(expr) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#endif /* __USE_KOS */
#else /* __NO_builtin_expect */
#define assert(expr)         (void)(__builtin_expect(!!(expr),1) || (__assertion_failed(#expr),0))
#define __assert0(expr)      (void)(__builtin_expect(!!(expr),1) || (__assertion_failed(#expr),0))
#define __asserta(expr)      (void)(__builtin_expect(!!(expr),1) || (__assertion_failed(#expr),0))
#define __assertf(expr, ...) (void)(__builtin_expect(!!(expr),1) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#define __assert0f(expr, ...)(void)(__builtin_expect(!!(expr),1) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#define __assertaf(expr, ...)(void)(__builtin_expect(!!(expr),1) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#ifdef __USE_KOS
#define assert0(expr)        (void)(__builtin_expect(!!(expr),1) || (__assertion_failed(#expr),0))
#define asserta(expr)        (void)(__builtin_expect(!!(expr),1) || (__assertion_failed(#expr),0))
#define assertf(expr, ...)   (void)(__builtin_expect(!!(expr),1) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#define assert0f(expr, ...)  (void)(__builtin_expect(!!(expr),1) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#define assertaf(expr, ...)  (void)(__builtin_expect(!!(expr),1) || (__assertion_failedf(#expr,__VA_ARGS__),0))
#endif /* __USE_KOS */
#endif /* !__NO_builtin_expect */
#endif /* !__USE_KOS_KERNEL */
#elif !defined(__NO_builtin_assume)
#if defined(CONFIG_ASSERT_ASSUME_EVERYTHING) || defined(ASSERT_ASSUME_EVERYTHING)
#define assert(expr)         __builtin_assume(!!(expr))
#define __assert0(expr)      __builtin_assume(!!(expr))
#define __asserta(expr)      __builtin_assume(!!(expr))
#define __assertf(expr, ...) __builtin_assume(!!(expr))
#define __assert0f(expr, ...)__builtin_assume(!!(expr))
#define __assertaf(expr, ...)__builtin_assume(!!(expr))
#ifdef __USE_KOS
#define assert0(expr)        __builtin_assume(!!(expr))
#define asserta(expr)        __builtin_assume(!!(expr))
#define assertf(expr, ...)   __builtin_assume(!!(expr))
#define assert0f(expr, ...)  __builtin_assume(!!(expr))
#define assertaf(expr, ...)  __builtin_assume(!!(expr))
#endif /* __USE_KOS */
#else /* CONFIG_ASSERT_ASSUME_EVERYTHING || ASSERT_ASSUME_EVERYTHING */
#define assert(expr)         (void)0
#define __assert0(expr)      (void)0
#define __asserta(expr)      __builtin_assume(!!(expr))
#define __assertf(expr, ...) (void)0
#define __assert0f(expr, ...)(void)0
#define __assertaf(expr, ...)__builtin_assume(!!(expr))
#ifdef __USE_KOS
#define assert0(expr)        (void)0
#define asserta(expr)        __builtin_assume(!!(expr))
#define assertf(expr, ...)   (void)0
#define assert0f(expr, ...)  (void)0
#define assertaf(expr, ...)  __builtin_assume(!!(expr))
#endif /* __USE_KOS */
#endif /* !CONFIG_ASSERT_ASSUME_EVERYTHING && !ASSERT_ASSUME_EVERYTHING */
#else
#define assert(expr)         (void)0
#define __assert0(expr)      (void)0
#define __asserta(expr)      (void)0
#define __assertf(expr, ...) (void)0
#define __assert0f(expr, ...)(void)0
#define __assertaf(expr, ...)(void)0
#ifdef __USE_KOS
#define assert0(expr)        (void)0
#define asserta(expr)        (void)0
#define assertf(expr, ...)   (void)0
#define assert0f(expr, ...)  (void)0
#define assertaf(expr, ...)  (void)0
#endif /* __USE_KOS */
#endif /* !NDEBUG */



