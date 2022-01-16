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
#ifndef _CXX_BITS_IS_NULL_POINTER_H
#define _CXX_BITS_IS_NULL_POINTER_H 1

#include <__stdcxx.h>

#include "integral_constant.h"

__CXXDECL_BEGIN
#define __cpp_lib_is_null_pointer 201309
#if defined(__COMPILER_HAVE_CXX_DECLTYPE) && \
defined(__COMPILER_HAVE_CXX_NULLPTR)
__NAMESPACE_INT_BEGIN
template<class __T> struct __is_null_pointer_helper: public __NAMESPACE_STD_SYM false_type {};
template<> struct __is_null_pointer_helper<decltype(nullptr)>: public __NAMESPACE_STD_SYM true_type {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_null_pointer: public __NAMESPACE_INT_SYM __is_null_pointer_helper<typename remove_cv<__T>::type>::type {};
__NAMESPACE_STD_END
#else
__NAMESPACE_STD_BEGIN
template<class __T> struct is_null_pointer: public false_type {};
__NAMESPACE_STD_END
#endif
__CXXDECL_END

#endif /* !_CXX_BITS_IS_NULL_POINTER_H */
