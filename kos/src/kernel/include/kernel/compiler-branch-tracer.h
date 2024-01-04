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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_COMPILER_BRANCH_TRACER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_COMPILER_BRANCH_TRACER_H 1

#include <hybrid/compiler.h>

#include <hybrid/__atomic.h>
#include <hybrid/typecore.h>

/*[[[config CONFIG_HAVE_KERNEL_BRANCH_PROFILING = false
 * Disable (for now...)
 * ]]]*/
#ifdef CONFIG_NO_KERNEL_BRANCH_PROFILING
#undef CONFIG_HAVE_KERNEL_BRANCH_PROFILING
#elif !defined(CONFIG_HAVE_KERNEL_BRANCH_PROFILING)
#define CONFIG_NO_KERNEL_BRANCH_PROFILING
#elif (-CONFIG_HAVE_KERNEL_BRANCH_PROFILING - 1) == -1
#undef CONFIG_HAVE_KERNEL_BRANCH_PROFILING
#define CONFIG_NO_KERNEL_BRANCH_PROFILING
#endif /* ... */
/*[[[end]]]*/

#ifdef __CC__

#if defined(CONFIG_NO_KERNEL_BRANCH_PROFILING) || \
    defined(DISABLE_BRANCH_PROFILING) || \
    defined(__INTELLISENSE__)
#else /* Branch profiling disabled... */
#include <kernel/arch/compiler-branch-tracer.h>
#if defined(CONFIG_NO_KERNEL_BRANCH_PROFILING) || \
    defined(DISABLE_BRANCH_PROFILING)
#else /* Disabled... */

#define traced(...)                                                   \
	(__builtin_constant_p((__VA_ARGS__)) ? !!(__VA_ARGS__) : XBLOCK({ \
		__BOOL ______expr = !!(__VA_ARGS__);                          \
		__predict_dotrace(".data.profile_branch", ______expr, 1);     \
		XRETURN ______expr;                                           \
	}))

#ifndef CONFIG_NO_FULL_BRANCH_PROFILING
#define if(...) if traced(__VA_ARGS__)
#endif /* !CONFIG_NO_FULL_BRANCH_PROFILING */


#if defined(__NO_builtin_expect) && !defined(__COMPILER_HAVE_AUTOTYPE)
#define __predict_trace(expr, expected)                                            \
	XBLOCK({                                                                       \
		__typeof__(expr) ______expr = (expr);                                      \
		__predict_dotrace(".data.profile_branch_annotated", ______expr, expected); \
		XRETURN(______expr);                                                       \
	})
#elif defined(__NO_builtin_expect)
#define __predict_trace(expr, expected)                                            \
	XBLOCK({                                                                       \
		__auto_type ______expr = (expr);                                           \
		__predict_dotrace(".data.profile_branch_annotated", ______expr, expected); \
		XRETURN(______expr);                                                       \
	})
#elif !defined(__COMPILER_HAVE_AUTOTYPE)
#define __predict_trace(expr, expected)                                            \
	XBLOCK({                                                                       \
		__typeof__(expr) ______expr = (expr);                                      \
		__predict_dotrace(".data.profile_branch_annotated", ______expr, expected); \
		XRETURN __builtin_expect(______expr, expected);                            \
	})
#else /* ... */
#define __predict_trace(expr, expected)                                            \
	XBLOCK({                                                                       \
		__auto_type ______expr = (expr);                                           \
		__predict_dotrace(".data.profile_branch_annotated", ______expr, expected); \
		XRETURN __builtin_expect(______expr, expected);                            \
	})
#endif /* !... */

#ifdef __NO_builtin_constant_p
#define __predict(expr,expected) (__predict_trace(expr,expected))
#else /* __NO_builtin_constant_p */
#define __predict(expr,expected) (__builtin_constant_p(expr)?(expr):__predict_trace(expr,expected))
#endif /* !__NO_builtin_constant_p */

#undef __likely
#undef __unlikely
#define __likely(expr)              __predict(!!(expr),1)
#define __unlikely(expr)            __predict(!!(expr),0)
#ifdef __NO_builtin_expect
#define __likely_untraced           /* nothing */
#define __unlikely_untraced         /* nothing */
#else /* __NO_builtin_expect */
#define __likely_untraced(expr)    (__builtin_expect(!!(expr),1))
#define __unlikely_untraced(expr)  (__builtin_expect(!!(expr),0))
#endif /* !__NO_builtin_expect */


#endif /* Enabled... */
#endif /* Branch profiling enabled... */
#endif /* __CC__ */


#ifndef __predict
#ifdef __NO_builtin_expect
#define __predict(expr,expected) (expr)
#else /* __NO_builtin_expect */
#define __predict(expr,expected) __builtin_expect(expr,expected)
#endif /* !__NO_builtin_expect */
#endif /* !__predict */
#ifndef __likely_untraced
#define __likely_untraced        __likely
#endif /* !__likely_untraced */
#ifndef __unlikely_untraced
#define __unlikely_untraced      __unlikely
#endif /* !__unlikely_untraced */


#ifndef traced
#define traced    /* Annotation used as `if traced(foo)'
                   * -> Explicitly request the if-branch to be considered for tracing */
#endif /* !traced */

/* Untraced variants of likely/unlikely */
#define likely_untraced    __likely_untraced
#define unlikely_untraced  __unlikely_untraced


#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_COMPILER_BRANCH_TRACER_H */
