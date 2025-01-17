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
#ifndef _CXX_BITS_IS_DESTRUCTIBLE_H
#define _CXX_BITS_IS_DESTRUCTIBLE_H 1

#include <__stdcxx.h>

#include "integral_constant.h"

#if !(defined(__INTELLISENSE__) || defined(_MSC_VER) || \
      !defined(__COMPILER_HAVE_CXX11_NOEXCEPT) ||       \
      !defined(__COMPILER_HAVE_CXX_DECLTYPE))
#include "__is_array_bounds.h"
#include "declval.h"
#include "is_function.h"
#include "is_reference.h"
#include "is_scalar.h"
#include "is_void.h"
#include "remove_all_extents.h"
#endif /* ... */

__CXXDECL_BEGIN

#if defined(__INTELLISENSE__) || defined(_MSC_VER) || !defined(__COMPILER_HAVE_CXX_DECLTYPE)
__NAMESPACE_STD_BEGIN
template<class __T> struct is_destructible
    : public integral_constant<bool, __is_destructible(__T)> {};
__NAMESPACE_STD_END
#else
__NAMESPACE_INT_BEGIN
struct __do_is_destructible_impl {
	template<class __T,
	         class __Sel = decltype(__NAMESPACE_STD_SYM declval<__T &>().~__T())>
	static __NAMESPACE_STD_SYM true_type __test(int);
	template<class __T> static __NAMESPACE_STD_SYM false_type __test(...);
};
template<class __T> struct __is_destructible_impl
    : public __do_is_destructible_impl {
	typedef decltype(__test<__T>(0)) type;
};
template<class __T,
         bool __Sel1 = __or_<__NAMESPACE_STD_SYM is_void<__T>,
                             __is_array_unknown_bounds<__T>,
                             __NAMESPACE_STD_SYM is_function<__T> >::value,
         bool __Sel2 = __or_<__NAMESPACE_STD_SYM is_reference<__T>,
                             __NAMESPACE_STD_SYM is_scalar<__T> >::value>
struct __is_destructible_safe;
template<class __T> struct __is_destructible_safe<__T, false, false>
    : public __is_destructible_impl<typename __NAMESPACE_STD_SYM remove_all_extents<__T>::type>::type {};
template<class __T> struct __is_destructible_safe<__T, true, false>
    : public __NAMESPACE_STD_SYM false_type {};
template<class __T> struct __is_destructible_safe<__T, false, true>
    : public __NAMESPACE_STD_SYM true_type {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_destructible
    : public __NAMESPACE_INT_SYM __is_destructible_safe<__T>::type {};
__NAMESPACE_STD_END
#endif

#if defined(__INTELLISENSE__) || defined(_MSC_VER) || \
   !defined(__COMPILER_HAVE_CXX11_NOEXCEPT) || !defined(__COMPILER_HAVE_CXX_DECLTYPE)
__NAMESPACE_STD_BEGIN
template<class __T> struct is_nothrow_destructible
    : public integral_constant<bool, __is_nothrow_destructible(__T)> {};
__NAMESPACE_STD_END
#else
__NAMESPACE_INT_BEGIN
struct __do_is_nt_destructible_impl {
	template<class __T> static __NAMESPACE_STD_SYM integral_constant<bool, noexcept(__NAMESPACE_STD_SYM declval<__T &>().~__T())> __test(int);
	template<class __T> static __NAMESPACE_STD_SYM false_type __test(...);
};
template<class __T> struct __is_nt_destructible_impl
    : public __do_is_nt_destructible_impl {
	typedef decltype(__test<__T>(0)) type;
};
template<class __T,
         bool __Sel1 = __or_<__NAMESPACE_STD_SYM is_void<__T>,
                             __is_array_unknown_bounds<__T>,
                             __NAMESPACE_STD_SYM is_function<__T> >::value,
         bool __Sel2 = __or_<__NAMESPACE_STD_SYM is_reference<__T>,
                             __NAMESPACE_STD_SYM is_scalar<__T> >::value>
struct __is_nt_destructible_safe;
template<class __T> struct __is_nt_destructible_safe<__T, false, false>
    : public __is_nt_destructible_impl<typename __NAMESPACE_STD_SYM remove_all_extents<__T>::type>::type {};
template<class __T> struct __is_nt_destructible_safe<__T, true, false>
    : public __NAMESPACE_STD_SYM false_type {};
template<class __T> struct __is_nt_destructible_safe<__T, false, true>
    : public __NAMESPACE_STD_SYM true_type {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_nothrow_destructible
    : public __NAMESPACE_INT_SYM __is_nt_destructible_safe<__T>::type {};
__NAMESPACE_STD_END
#endif
__NAMESPACE_STD_BEGIN
#if !defined(__GNUC__) || defined(__INTELLISENSE__)
template<class __T> struct is_trivially_destructible
    : public integral_constant<bool, __has_trivial_destructor(__T)> {};
#else
template<class __T> struct is_trivially_destructible
    : public __NAMESPACE_INT_SYM __and_<is_destructible<__T>, integral_constant<bool, __has_trivial_destructor(__T)> > {};
#endif
template<class __T> struct has_virtual_destructor
    : public integral_constant<bool, __has_virtual_destructor(__T)> {};
__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_IS_DESTRUCTIBLE_H */
