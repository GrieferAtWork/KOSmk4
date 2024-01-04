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
#ifndef _CXX_BITS_IS_MEMBER_H
#define _CXX_BITS_IS_MEMBER_H 1

#include <__stdcxx.h>

#include "integral_constant.h"
#include "is_function.h"
#include "remove_cv.h"

__CXXDECL_BEGIN
__NAMESPACE_INT_BEGIN
template<class __T> struct __is_member_object_pointer_helper: public __NAMESPACE_STD_SYM false_type {};
template<class __T, class __C> struct __is_member_object_pointer_helper<__T __C::*>: public __NAMESPACE_STD_SYM integral_constant<bool, !__NAMESPACE_STD_SYM is_function<__T>::value> {};
template<class __T> struct __is_member_function_pointer_helper: public __NAMESPACE_STD_SYM false_type {};
template<class __T, class __C> struct __is_member_function_pointer_helper<__T __C::*>: public __NAMESPACE_STD_SYM is_function<__T> {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_member_object_pointer: public __NAMESPACE_INT_SYM __is_member_object_pointer_helper<typename remove_cv<__T>::type>::type {};
template<class __T> struct is_member_function_pointer: public __NAMESPACE_INT_SYM __is_member_function_pointer_helper<typename remove_cv<__T>::type>::type {};
__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_IS_MEMBER_H */
