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
#ifndef _CXX_BITS_IS_ASSIGNABLE_H
#define _CXX_BITS_IS_ASSIGNABLE_H 1

#include <__stdcxx.h>

#include "__is_referenceable.h"
#include "declval.h"
#include "integral_constant.h"

__CXXDECL_BEGIN
__NAMESPACE_INT_BEGIN
template<class __To, class __From> class __is_assignable_helper {
	template<class __To1, class __From1,
	         class __Sel = decltype(__NAMESPACE_STD_SYM declval<__To1>() = __NAMESPACE_STD_SYM declval<__From1>())>
	static __NAMESPACE_STD_SYM true_type __test(int);
	template<class __To1, class __From1> static __NAMESPACE_STD_SYM false_type __test(...);

public:
	typedef decltype(__test<__To, __From>(0)) type;
};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __To, class __From> struct is_assignable
    : public __NAMESPACE_INT_SYM __is_assignable_helper<__To, __From>::type {};
__NAMESPACE_STD_END
__NAMESPACE_INT_BEGIN
template<class __T, bool __Sel> struct __is_copy_assignable_impl;
template<class __T> struct __is_copy_assignable_impl<__T, false>
    : public __NAMESPACE_STD_SYM false_type {};
template<class __T> struct __is_copy_assignable_impl<__T, true>
    : public __NAMESPACE_STD_SYM is_assignable<__T &, __T const &>::type {};
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
template<class __T, bool __Sel> struct __is_move_assignable_impl;
template<class __T> struct __is_move_assignable_impl<__T, false>
    : public __NAMESPACE_STD_SYM false_type {};
template<class __T> struct __is_move_assignable_impl<__T, true>
    : public __NAMESPACE_STD_SYM is_assignable<__T &, __T &&> {};
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_copy_assignable
    : public __NAMESPACE_INT_SYM __is_copy_assignable_impl<__T, __NAMESPACE_INT_SYM __is_referenceable<__T>::value> {};
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
template<class __T> struct is_move_assignable
    : public __NAMESPACE_INT_SYM __is_move_assignable_impl<__T, __NAMESPACE_INT_SYM __is_referenceable<__T>::value> {};
#else /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
template<class __T> struct is_move_assignable
    : public false_type {};
#endif /* !__COMPILER_HAVE_CXX_RVALUE_REFERENCE */
#if !defined(__COMPILER_HAVE_CXX11_NOEXCEPT) || \
defined(__INTELLISENSE__) || defined(_MSC_VER)
template<class __To, class __From> struct is_nothrow_assignable
    : public integral_constant<bool, __is_nothrow_assignable(__To, __From)>> {};
#else /* __COMPILER_HAVE_CXX11_NOEXCEPT */
__NAMESPACE_STD_END
__NAMESPACE_INT_BEGIN
template<class __To, class __From> struct __is_nt_assignable_impl
    : public __NAMESPACE_STD_SYM integral_constant<bool, noexcept(__NAMESPACE_STD_SYM declval<__To>() = __NAMESPACE_STD_SYM declval<__From>())> {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __To, class __From> struct is_nothrow_assignable
    : public __NAMESPACE_INT_SYM __and_<is_assignable<__To, __From>, __NAMESPACE_INT_SYM __is_nt_assignable_impl<__To, __From> > {};
#endif /* !__COMPILER_HAVE_CXX11_NOEXCEPT */
__NAMESPACE_STD_END
__NAMESPACE_INT_BEGIN
template<class __T, bool __Sel> struct __is_nt_copy_assignable_impl;
template<class __T> struct __is_nt_copy_assignable_impl<__T, false>
    : public __NAMESPACE_STD_SYM false_type {};
template<class __T> struct __is_nt_copy_assignable_impl<__T, true>
    : public __NAMESPACE_STD_SYM is_nothrow_assignable<__T &, __T const &> {};
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
template<class __T, bool __Sel> struct __is_nt_move_assignable_impl;
template<class __T> struct __is_nt_move_assignable_impl<__T, false>
    : public __NAMESPACE_STD_SYM false_type {};
template<class __T> struct __is_nt_move_assignable_impl<__T, true>
    : public __NAMESPACE_STD_SYM is_nothrow_assignable<__T &, __T &&> {};
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_nothrow_copy_assignable
    : public __NAMESPACE_INT_SYM __is_nt_copy_assignable_impl<__T, __NAMESPACE_INT_SYM __is_referenceable<__T>::value> {};
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
template<class __T> struct is_nothrow_move_assignable
    : public __NAMESPACE_INT_SYM __is_nt_move_assignable_impl<__T, __NAMESPACE_INT_SYM __is_referenceable<__T>::value> {};
#else /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
template<class __T> struct is_nothrow_move_assignable
    : public false_type {};
#endif /* !__COMPILER_HAVE_CXX_RVALUE_REFERENCE */
#if !defined(__GNUC__) || defined(__INTELLISENSE__)
template<class __To, class __From> struct is_trivially_assignable
    : public integral_constant<bool, __is_trivially_assignable(__To, __From)> {};
template<class __T> struct is_trivially_copy_assignable
    : public integral_constant<bool, __is_trivially_assignable(__T &, __T const &)> {};
template<class __T> struct is_trivially_move_assignable
    : public integral_constant<bool, __is_trivially_assignable(__T &, __T &&)> {};
#else
template<class __To, class __From> struct is_trivially_assignable
    : public __NAMESPACE_INT_SYM __and_<is_assignable<__To, __From>, integral_constant<bool, __is_trivially_assignable(__To, __From)> > {};
template<class __T> struct is_trivially_copy_assignable
    : public __NAMESPACE_INT_SYM __and_<is_copy_assignable<__T>, integral_constant<bool, __is_trivially_assignable(__T &, __T const &)> > {};
template<class __T> struct is_trivially_move_assignable
    : public __NAMESPACE_INT_SYM __and_<is_move_assignable<__T>, integral_constant<bool, __is_trivially_assignable(__T &, __T &&)> > {};
#endif
template<class __T> struct has_trivial_copy_assign
    : public integral_constant<bool, __has_trivial_assign(__T)> {};
__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_IS_ASSIGNABLE_H */
