/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _CXX_BITS_IS_INVOCABLE_H
#define _CXX_BITS_IS_INVOCABLE_H 1

#include <__stdcxx.h>

#include "andor.h"
#include "declval.h"
#include "is_convertible.h"
#include "is_member.h"
#include "is_void.h"
#include "remove_reference.h"
#include "result_of.h"

__CXXDECL_BEGIN
__NAMESPACE_INT_BEGIN
template<class __ResultOf> __NAMESPACE_STD_SYM true_type __is_invocable_test(typename __ResultOf::type *);
template<class __ResultOf> __NAMESPACE_STD_SYM false_type __is_invocable_test(...);
template<class __ResultOf> struct __is_invocable_impl { typedef decltype(__is_invocable_test<__ResultOf>(0)) type; };
template<class __ResultOf, class __ReturnType,
         bool __Sel = __is_invocable_impl<__ResultOf>::type::value>
struct __is_invocable_r_impl: __NAMESPACE_STD_SYM false_type {};
template<class __ResultOf, class __ReturnType>
struct __is_invocable_r_impl<__ResultOf, __ReturnType, true>
    : __NAMESPACE_STD_SYM is_convertible<typename __ResultOf::type, __ReturnType> {};
#ifdef __COMPILER_HAVE_CXX11_NOEXCEPT
template<class __ResultOf, class __ReturnType,
         bool __Sel = __is_invocable_impl<__ResultOf>::type::value>
struct __is_nothrow_invocable_r_impl: __NAMESPACE_STD_SYM false_type {};
template<class __ResultOf, class __ReturnType>
struct __is_nothrow_invocable_r_impl<__ResultOf, __ReturnType, true>
    : __NAMESPACE_STD_SYM is_nothrow_convertible<typename __ResultOf::type, __ReturnType> {};
template<class __Function, class... __ArgumentTypes> struct __is_nothrow_invocable_impl
    : __NAMESPACE_STD_SYM integral_constant<bool, noexcept(
                                                  __NAMESPACE_STD_SYM declval<__Function>()(
                                                  __NAMESPACE_STD_SYM declval<__ArgumentTypes>()...))> {};
#endif /* __COMPILER_HAVE_CXX11_NOEXCEPT */
__NAMESPACE_INT_END

__NAMESPACE_STD_BEGIN
#define __cpp_lib_is_invocable 201703

template<class __Function, class... __ArgumentTypes> struct invoke_result
    : public __NAMESPACE_INT_SYM __result_of_impl<
      is_member_object_pointer<typename remove_reference<__Function>::type>::value,
      is_member_function_pointer<typename remove_reference<__Function>::type>::value,
      __Function, __ArgumentTypes...>::type {};
template<class __Function, class... __ArgumentTypes> struct is_invocable
    : public __NAMESPACE_INT_SYM __is_invocable_impl<invoke_result<__Function, __ArgumentTypes...> >::type {};
template<class __ReturnType, class __Function, class... __ArgumentTypes> struct is_invocable_r
    : public __NAMESPACE_INT_SYM __is_invocable_r_impl<invoke_result<__Function, __ArgumentTypes...>, __ReturnType> {};
#ifdef __COMPILER_HAVE_CXX11_NOEXCEPT
template<class __Function, class... __ArgumentTypes> struct is_nothrow_invocable
    : public __NAMESPACE_INT_SYM __and_<
      __NAMESPACE_INT_SYM __is_invocable_impl<invoke_result<__Function, __ArgumentTypes...> >,
      __NAMESPACE_INT_SYM __is_nothrow_invocable_impl<__Function, __ArgumentTypes...> >::type {};
template<class __ReturnType, class __Function, class... __ArgumentTypes> struct is_nothrow_invocable_r
    : public __NAMESPACE_INT_SYM __and_<
      __NAMESPACE_INT_SYM __is_nothrow_invocable_r_impl<invoke_result<__Function, __ArgumentTypes...>, __ReturnType>,
      __NAMESPACE_INT_SYM __is_nothrow_invocable_impl<__Function, __ArgumentTypes...> >::type {};
#endif /* __COMPILER_HAVE_CXX11_NOEXCEPT */

#ifdef __COMPILER_HAVE_CXX_TEMPLATE_USING
template<class __Function, class... __ArgumentTypes>
using invoke_result_t = typename invoke_result<__Function, __ArgumentTypes...>::type;
#endif /* __COMPILER_HAVE_CXX_TEMPLATE_USING */

#ifdef __COMPILER_HAVE_CXX_TEMPLATE_CONSTEXPR
template<typename __Function, typename... __ArgumentTypes> inline constexpr bool is_invocable_v = is_invocable<__Function, __ArgumentTypes...>::value;
template<typename __Function, typename... __ArgumentTypes> inline constexpr bool is_nothrow_invocable_v = is_nothrow_invocable<__Function, __ArgumentTypes...>::value;
template<class __ReturnType, typename __Function, typename... __ArgumentTypes> inline constexpr bool is_invocable_r_v = is_invocable_r<__ReturnType, __Function, __ArgumentTypes...>::value;
template<class __ReturnType, typename __Function, typename... __ArgumentTypes> inline constexpr bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<__ReturnType, __Function, __ArgumentTypes...>::value;
#endif /* __COMPILER_HAVE_CXX_TEMPLATE_CONSTEXPR */

__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_IS_INVOCABLE_H */
