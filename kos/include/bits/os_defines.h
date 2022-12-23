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
#ifndef _BITS_OS_DEFINES_H
/* This header only does something when it's included from libstdc++'s "c++config.h" header! */
#ifdef _GLIBCXX_CXX_CONFIG_H
#define _BITS_OS_DEFINES_H 1

/* This header is used to better integrate libstdc++ into the KOS header system. */
#include <__stdinc.h>
#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

#undef _GLIBCXX_BEGIN_EXTERN_C
#undef _GLIBCXX_END_EXTERN_C
#define _GLIBCXX_BEGIN_EXTERN_C __DECL_BEGIN
#define _GLIBCXX_END_EXTERN_C   __DECL_END


#include <hybrid/__assert.h>
#undef __glibcxx_assert
#undef __glibcxx_assert_impl
#define __glibcxx_assert      __hybrid_assert
#define __glibcxx_assert_impl __hybrid_assert

#undef _GLIBCXX_DEPRECATED
#if defined(__DEPRECATED) && (__cplusplus >= 201103L)
#define _GLIBCXX_DEPRECATED __ATTR_DEPRECATED_
#else
#define _GLIBCXX_DEPRECATED
#endif

#undef _GLIBCXX17_DEPRECATED
#if defined(__DEPRECATED) && (__cplusplus >= 201703L)
#define _GLIBCXX17_DEPRECATED __ATTR_DEPRECATED_
#else
#define _GLIBCXX17_DEPRECATED
#endif


#undef _GLIBCXX_PURE
#define _GLIBCXX_PURE __ATTR_PURE

#undef _GLIBCXX_CONST
#define _GLIBCXX_CONST __ATTR_CONST

#undef _GLIBCXX_NORETURN
#define _GLIBCXX_NORETURN __ATTR_NORETURN

#undef _GLIBCXX_NODISCARD
#define _GLIBCXX_NODISCARD __ATTR_WUNUSED

#undef _GLIBCXX_VISIBILITY
#define _GLIBCXX_VISIBILITY(x) __ATTR_VISIBILITY(#x)

#undef _GLIBCXX_HAVE_ATTRIBUTE_VISIBILITY
#define _GLIBCXX_HAVE_ATTRIBUTE_VISIBILITY 1


#define _GLIBCXX_GTHREAD_USE_WEAK 0

#endif /* _GLIBCXX_CXX_CONFIG_H */
#endif /* !_BITS_OS_DEFINES_H */
