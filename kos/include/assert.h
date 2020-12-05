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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/assert.h) */
/* (#) Portability: DJGPP         (/include/assert.h) */
/* (#) Portability: FreeBSD       (/include/assert.h) */
/* (#) Portability: GNU C Library (/assert/assert.h) */
/* (#) Portability: MSVC          (/include/assert.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/assert.h) */
/* (#) Portability: NetBSD        (/include/assert.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/assert.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/assert.h) */
/* (#) Portability: diet libc     (/include/assert.h) */
/* (#) Portability: musl libc     (/include/assert.h) */
/* (#) Portability: uClibc        (/include/assert.h) */
/**/

/* Undef the old assert definition to allow for re-definitions! (mandated by the C standard) */
#undef assert      /* Regular STD-C assert (with optional retry extension) */
#undef __asserta   /* Assert + assume */
#undef __assert0   /* Same as `assert', but noreturn when condition fails */
#undef __assertf   /* Assert + printf-like message */
#undef __assertaf  /* Assert + assume + printf-like message */
#undef __assert0f  /* Same as `__assertf', but noreturn when condition fails */
#ifdef __USE_KOS
#undef assert0  /* Alias for `__assert0' */
#undef asserta  /* Alias for `__asserta' */
#undef assertf  /* Alias for `__assertf' */
#undef assert0f /* Alias for `__assert0f' */
#undef assertaf /* Alias for `__assertaf' */
#undef assert_failed
#endif /* __USE_KOS */

#ifdef __INTELLISENSE__
#ifndef __do_assert
#include "parts/assert.h"
#endif /* !__do_assert */

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
#define assert_failed(...) __assertion_failedf(__NULLPTR, __VA_ARGS__)
#endif /* __USE_KOS */
#elif defined(NDEBUG)
#ifdef __NO_builtin_assume
#define assert(expr)    (void)0
#define __assert0(expr) (void)0
#define __asserta(expr) (void)0
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __assertf(expr, ...)  (void)0
#define __assertaf(expr, ...) (void)0
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __assertf(expr, format...)  (void)0
#define __assertaf(expr, format...) (void)0
#endif /* ... */
#ifdef __USE_KOS
#define assert0(expr) (void)0
#define asserta(expr) (void)0
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define assertf(expr, ...)  (void)0
#define assertaf(expr, ...) (void)0
#define assert_failed(...)  __builtin_unreachable()
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define assertf(expr, format...)  (void)0
#define assertaf(expr, format...) (void)0
#define assert_failed(format...)  __builtin_unreachable()
#endif /* ... */
#endif /* __USE_KOS */
#else /* __NO_builtin_assume */
#if defined(CONFIG_ASSERT_ASSUME_EVERYTHING) || defined(ASSERT_ASSUME_EVERYTHING)
#define assert(expr)         __builtin_assume(!!(expr))
#define __assert0(expr)      __builtin_assume(!!(expr))
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __assertf(expr, ...) __builtin_assume(!!(expr))
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __assertf(expr, format...) __builtin_assume(!!(expr))
#endif /* ... */
#ifdef __USE_KOS
#define assert0(expr)      __builtin_assume(!!(expr))
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define assertf(expr, ...) __builtin_assume(!!(expr))
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define assertf(expr, format...) __builtin_assume(!!(expr))
#endif /* ... */
#endif /* __USE_KOS */
#else /* CONFIG_ASSERT_ASSUME_EVERYTHING || ASSERT_ASSUME_EVERYTHING */
#define assert(expr)    (void)0
#define __assert0(expr) (void)0
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __assertf(expr, ...) (void)0
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __assertf(expr, format...) (void)0
#endif /* ... */
#ifdef __USE_KOS
#define assert0(expr) (void)0
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define assertf(expr, ...) (void)0
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define assertf(expr, format...) (void)0
#endif /* ... */
#endif /* __USE_KOS */
#endif /* !CONFIG_ASSERT_ASSUME_EVERYTHING && !ASSERT_ASSUME_EVERYTHING */
#define __asserta(expr) __builtin_assume(!!(expr))
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __assertaf(expr, ...) __builtin_assume(!!(expr))
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __assertaf(expr, format...) __builtin_assume(!!(expr))
#endif /* ... */
#ifdef __USE_KOS
#define asserta(expr) __builtin_assume(!!(expr))
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define assertaf(expr, ...) __builtin_assume(!!(expr))
#define assert_failed(...)  __builtin_unreachable()
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define assertaf(expr, format...) __builtin_assume(!!(expr))
#define assert_failed(format...)  __builtin_unreachable()
#endif /* ... */
#endif /* __USE_KOS */
#endif /* !__NO_builtin_assume */
#else /* NDEBUG */
#ifndef __do_assert
#include "parts/assert.h"
#endif /* !__do_assert */
#define assert(expr)    __do_assert(expr, #expr)
#define __assert0(expr) __do_assert0(expr, #expr)
#define __asserta(expr) __do_asserta(expr, #expr)
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __assertf(expr, ...)  __do_assertf(expr, #expr, __VA_ARGS__)
#define __assertaf(expr, ...) __do_assertaf(expr, #expr, __VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __assertf(expr, format...)  __do_assertf(expr, #expr, format)
#define __assertaf(expr, format...) __do_assertaf(expr, #expr, format)
#endif /* ... */
#ifdef __USE_KOS
#define assert0(expr) __do_assert0(expr, #expr)
#define asserta(expr) __do_asserta(expr, #expr)
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define assertf(expr, ...)  __do_assertf(expr, #expr, __VA_ARGS__)
#define assertaf(expr, ...) __do_assertaf(expr, #expr, __VA_ARGS__)
#define assert_failed(...)  __assertion_failedf(__NULLPTR, __VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define assertf(expr, format...)  __do_assertf(expr, #expr, format)
#define assertaf(expr, format...) __do_assertaf(expr, #expr, format)
#define assert_failed(format...)  __assertion_failedf(__NULLPTR, format)
#endif /* ... */
#endif /* __USE_KOS */
#endif /* !NDEBUG */



