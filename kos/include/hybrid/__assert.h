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
#ifndef __GUARD_HYBRID___ASSERT_H
#define __GUARD_HYBRID___ASSERT_H 1

#include "../__stdinc.h"

#ifndef __hybrid_assert
#ifdef __INTELLISENSE__
__NAMESPACE_INT_BEGIN
extern void (__hybrid_check_assertion)(__BOOL __expr);
extern void (__hybrid_check_assertionf)(__BOOL __expr, char const *__restrict __format, ...);
__NAMESPACE_INT_END
#define __hybrid_assert  __NAMESPACE_INT_SYM __hybrid_check_assertion
#define __hybrid_assertf __NAMESPACE_INT_SYM __hybrid_check_assertionf
#elif defined(NDEBUG)
#ifdef __NO_builtin_assume
#define __hybrid_assert __builtin_assume
#else /* __NO_builtin_assume */
#define __hybrid_assert(expr) (void)0
#endif /* !__NO_builtin_assume */
#else /* NDEBUG */
#include <assert.h>
#define __hybrid_assert  assert
#ifdef __assertf
#define __hybrid_assertf __assertf
#elif defined(assertf)
#define __hybrid_assertf assertf
#endif /* ... */
#ifdef __assertion_failed
#define __hybrid_assertion_failed __assertion_failed
#endif /* __assertion_failed */
#ifdef __assertion_failedf
#define __hybrid_assertion_failedf __assertion_failedf
#endif /* __assertion_failedf */
#endif /* !NDEBUG */
#ifndef __hybrid_assertf
#define __hybrid_assertf(expr, ...) __hybrid_assert(expr)
#endif /* !__hybrid_assertf */
#endif /* !__hybrid_assert */

#ifndef __hybrid_assertion_failed
#define __hybrid_assertion_failed(message) __hybrid_assert(!message)
#endif /* !__hybrid_assertion_failed */
#ifndef __hybrid_assertion_failedf
#define __hybrid_assertion_failedf(message, ...) __hybrid_assertf(!message, __VA_ARGS__)
#endif /* !__hybrid_assertion_failedf */


#endif /* !__GUARD_HYBRID___ASSERT_H */
