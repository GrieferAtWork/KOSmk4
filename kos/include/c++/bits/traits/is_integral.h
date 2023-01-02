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
#ifndef _CXX_BITS_IS_INTEGRAL_H
#define _CXX_BITS_IS_INTEGRAL_H 1

#include <__stdcxx.h>

#include "integral_constant.h"
#include "remove_cv.h"

__CXXDECL_BEGIN
__NAMESPACE_INT_BEGIN
template<class __T> struct __is_integral_helper: public __NAMESPACE_STD_SYM false_type {};
template<> struct __is_integral_helper<bool>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<char>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<signed char>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<unsigned char>: public __NAMESPACE_STD_SYM true_type {};
#ifdef __native_wchar_t_defined
template<> struct __is_integral_helper<wchar_t>: public __NAMESPACE_STD_SYM true_type {};
#endif /* __native_wchar_t_defined */
#ifdef __native_char16_t_defined
template<> struct __is_integral_helper<char16_t>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<char32_t>: public __NAMESPACE_STD_SYM true_type {};
#endif /* __native_char16_t_defined */
template<> struct __is_integral_helper<short>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<unsigned short>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<int>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<unsigned int>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<long>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<unsigned long>: public __NAMESPACE_STD_SYM true_type {};
#ifdef __COMPILER_HAVE_LONGLONG
template<> struct __is_integral_helper<__LONGLONG>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<__ULONGLONG>: public __NAMESPACE_STD_SYM true_type {};
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
template<> struct __is_integral_helper<__int8>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<unsigned __int8>: public __NAMESPACE_STD_SYM true_type {};
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
template<> struct __is_integral_helper<__int16>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<unsigned __int16>: public __NAMESPACE_STD_SYM true_type {};
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
template<> struct __is_integral_helper<__int32>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<unsigned __int32>: public __NAMESPACE_STD_SYM true_type {};
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
template<> struct __is_integral_helper<__int64>: public __NAMESPACE_STD_SYM true_type {};
template<> struct __is_integral_helper<unsigned __int64>: public __NAMESPACE_STD_SYM true_type {};
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_integral: public __NAMESPACE_INT_SYM __is_integral_helper<typename remove_cv<__T>::type>::type {};
__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_IS_INTEGRAL_H */
