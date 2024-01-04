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
#ifndef _CXX_BITS_IS_CONSTRUCTIBLE_H
#define _CXX_BITS_IS_CONSTRUCTIBLE_H 1

#include <__stdcxx.h>

#include "__is_referenceable.h"
#include "integral_constant.h"
#if !(defined(_MSC_VER) || defined(__INTELLISENSE__) || \
      !defined(__COMPILER_HAVE_CXX_DECLTYPE))
#include <c++/bits/operator_new.h>

#include "__is_array_bounds.h"
#include "andor.h"
#include "conditional.h"
#include "declval.h"
#include "is_array.h"
#include "is_base_of.h"
#include "is_destructible.h"
#include "is_function.h"
#include "is_same.h"
#include "is_void.h"
#include "remove_all_extents.h"
#include "remove_cv.h"
#include "remove_reference.h"
#endif

__CXXDECL_BEGIN
#if defined(_MSC_VER) || defined(__INTELLISENSE__) || \
!defined(__COMPILER_HAVE_CXX_DECLTYPE)
__NAMESPACE_STD_BEGIN
template<class __T> struct is_default_constructible
    : public integral_constant<bool, __is_constructible(__T)>::type {};
template<class __T, class... __Args> struct is_constructible
    : public integral_constant<bool, __is_constructible(__T, __Args...)>::type {};
__NAMESPACE_STD_END
#else /* !... */
__NAMESPACE_INT_BEGIN
struct __do_is_default_constructible_impl {
	template<class __T, class __Sel = decltype(__T())>
	static __NAMESPACE_STD_SYM true_type __test(int);
	template<class __T> static __NAMESPACE_STD_SYM false_type __test(...);
};
template<class __T> struct __is_default_constructible_impl
    : public __do_is_default_constructible_impl {
	typedef decltype(__test<__T>(0)) type;
};
template<class __T> struct __is_default_constructible_atom
    : public __and_<__not_<__NAMESPACE_STD_SYM is_void<__T> >,
                    __is_default_constructible_impl<__T> > {};
template<class __T, bool __Sel> struct __is_default_constructible_safe;
template<class __T> struct __is_default_constructible_safe<__T, true>
    : public __and_<__is_array_known_bounds<__T>,
                    __is_default_constructible_atom<typename __NAMESPACE_STD_SYM remove_all_extents<__T>::type> > {};
template<class __T> struct __is_default_constructible_safe<__T, false>
    : public __is_default_constructible_atom<__T>::type {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_default_constructible
    : public __NAMESPACE_INT_SYM __is_default_constructible_safe<__T, is_array<__T>::value>::type {};
__NAMESPACE_STD_END
__NAMESPACE_INT_BEGIN
struct __do_is_static_castable_impl {
	template<class __From, class __To, class __Sel = decltype(static_cast<__To>(__NAMESPACE_STD_SYM declval<__From>()))> static __NAMESPACE_STD_SYM true_type __test(int);
	template<class __From, class __To> static __NAMESPACE_STD_SYM false_type __test(...);
};
template<class __From, class __To> struct __is_static_castable_impl
    : public __do_is_static_castable_impl { typedef decltype(__test<__From, __To>(0)) type; };
template<class __From, class __To> struct __is_static_castable_safe
    : public __is_static_castable_impl<__From, __To>::type {};
template<class __From, class __To> struct __is_static_castable
    : public __NAMESPACE_STD_SYM integral_constant<bool, (__is_static_castable_safe<__From, __To>::value)> {};
struct __do_is_direct_constructible_impl {
	template<class __T, class __Arg, class __Sel = decltype(::new __T(__NAMESPACE_STD_SYM declval<__Arg>()))>
	static __NAMESPACE_STD_SYM true_type __test(int);
	template<class __T, class __Arg> static __NAMESPACE_STD_SYM false_type __test(...);
};
template<class __T, class __Arg> struct __is_direct_constructible_impl
    : public __do_is_direct_constructible_impl { typedef decltype(__test<__T, __Arg>(0)) type; };
template<class __T, class __Arg> struct __is_direct_constructible_new_safe
    : public __and_<__NAMESPACE_STD_SYM is_destructible<__T>, __is_direct_constructible_impl<__T, __Arg> > {};
template<class __From, class __To, bool __Sel = __not_<__or_<__NAMESPACE_STD_SYM is_void<__From>, __NAMESPACE_STD_SYM is_function<__From> > >::value>
struct __is_base_to_derived_ref;
template<class __From, class __To>
struct __is_base_to_derived_ref<__From, __To, true> {
	typedef typename __NAMESPACE_STD_SYM remove_cv<typename __NAMESPACE_STD_SYM remove_reference<__From>::type>::type __src_t;
	typedef typename __NAMESPACE_STD_SYM remove_cv<typename __NAMESPACE_STD_SYM remove_reference<__To>::type>::type __dst_t;
	typedef __and_<__not_<__NAMESPACE_STD_SYM is_same<__src_t, __dst_t> >, __NAMESPACE_STD_SYM is_base_of<__src_t, __dst_t> > type;
	__CXX_STATIC_CONST(bool, value = type::value);
};
template<class __From, class __To> struct __is_base_to_derived_ref<__From, __To, false>
    : public __NAMESPACE_STD_SYM false_type {};
template<class __From, class __To, bool __Sel = __and_<__NAMESPACE_STD_SYM is_lvalue_reference<__From>, __NAMESPACE_STD_SYM is_rvalue_reference<__To> >::value>
struct __is_lvalue_to_rvalue_ref;
template<class __From, class __To> struct __is_lvalue_to_rvalue_ref<__From, __To, true> {
	typedef typename __NAMESPACE_STD_SYM remove_cv<typename __NAMESPACE_STD_SYM remove_reference<__From>::type>::type __src_t;
	typedef typename __NAMESPACE_STD_SYM remove_cv<typename __NAMESPACE_STD_SYM remove_reference<__To>::type>::type __dst_t;
	typedef __and_<__not_<__NAMESPACE_STD_SYM is_function<__src_t> >, __or_<__NAMESPACE_STD_SYM is_same<__src_t, __dst_t>, __NAMESPACE_STD_SYM is_base_of<__dst_t, __src_t> > > type;
	__CXX_STATIC_CONST(bool, value = type::value);
};
template<class __From, class __To> struct __is_lvalue_to_rvalue_ref<__From, __To, false>
    : public __NAMESPACE_STD_SYM false_type {};
template<class __T, class __Arg> struct __is_direct_constructible_ref_cast
    : public __and_<__is_static_castable<__Arg, __T>, __not_<__or_<__is_base_to_derived_ref<__Arg, __T>, __is_lvalue_to_rvalue_ref<__Arg, __T> > > > {};
template<class __T, class __Arg> struct __is_direct_constructible_new
    : public __NAMESPACE_STD_SYM conditional<__NAMESPACE_STD_SYM is_reference<__T>::value, __is_direct_constructible_ref_cast<__T, __Arg>, __is_direct_constructible_new_safe<__T, __Arg> >::type {};
template<class __T, class __Arg> struct __is_direct_constructible
    : public __is_direct_constructible_new<__T, __Arg>::type {};
struct __do_is_nary_constructible_impl {
	template<class __T, class... __Args, typename __Sel = decltype(__T(__NAMESPACE_STD_SYM declval<__Args>()...))>
	static __NAMESPACE_STD_SYM true_type __test(int);
	template<class __T, class... __Args>
	static __NAMESPACE_STD_SYM false_type __test(...);
};
template<class __T, class... __Args> struct __is_nary_constructible_impl
    : public __do_is_nary_constructible_impl { typedef decltype(__test<__T, __Args...>(0)) type; };
template<class __T, class... __Args> struct __is_nary_constructible
    : public __is_nary_constructible_impl<__T, __Args...>::type {
	static_assert(sizeof...(__Args) > 1, "Only useful for > 1 arguments");
};
template<class __T, class... __Args> struct __is_constructible_impl
    : public __is_nary_constructible<__T, __Args...> {};
template<class __T, class __Arg> struct __is_constructible_impl<__T, __Arg>
    : public __is_direct_constructible<__T, __Arg> {};
template<class __T> struct __is_constructible_impl<__T>
    : public __NAMESPACE_STD_SYM is_default_constructible<__T> {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T, class... __Args> struct is_constructible
    : public __NAMESPACE_INT_SYM __is_constructible_impl<__T, __Args...>::type {};
__NAMESPACE_STD_END
#endif /* ... */
__NAMESPACE_INT_BEGIN
template<class __T, bool __Sel> struct __is_copy_constructible_impl;
template<class __T> struct __is_copy_constructible_impl<__T, false>
    : public __NAMESPACE_STD_SYM false_type {};
template<class __T> struct __is_copy_constructible_impl<__T, true>
    : public __NAMESPACE_STD_SYM is_constructible<__T, __T const &> {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_copy_constructible
    : public __NAMESPACE_INT_SYM __is_copy_constructible_impl<__T, __NAMESPACE_INT_SYM __is_referenceable<__T>::value> {};
__NAMESPACE_STD_END
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
__NAMESPACE_INT_BEGIN
template<class __T, bool __Sel> struct __is_move_constructible_impl;
template<class __T> struct __is_move_constructible_impl<__T, false>
    : public __NAMESPACE_STD_SYM false_type {};
template<class __T> struct __is_move_constructible_impl<__T, true>
    : public __NAMESPACE_STD_SYM is_constructible<__T, __T &&> {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_move_constructible
    : public __NAMESPACE_INT_SYM __is_move_constructible_impl<__T, __NAMESPACE_INT_SYM __is_referenceable<__T>::value> {};
__NAMESPACE_STD_END
#else /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
__NAMESPACE_STD_BEGIN
template<class __T> struct is_move_constructible: public false_type {};
__NAMESPACE_STD_END
#endif /* !__COMPILER_HAVE_CXX_RVALUE_REFERENCE */
#if !defined(__COMPILER_HAVE_CXX11_NOEXCEPT) || \
defined(_MSC_VER) || defined(__INTELLISENSE__)
__NAMESPACE_STD_BEGIN
template<class __T> struct is_nothrow_default_constructible
    : public integral_constant<bool, __is_nothrow_constructible(__T)> {};
template<class __T, class... __Args> struct is_nothrow_constructible
    : public integral_constant<bool, __is_nothrow_constructible(__T, __Args...)> {};
__NAMESPACE_STD_END
#else /* !... */
__NAMESPACE_INT_BEGIN
template<class __T> struct __is_nt_default_constructible_atom
    : public __NAMESPACE_STD_SYM integral_constant<bool, noexcept(__T())> {};
template<class __T, bool __Sel> struct __is_nt_default_constructible_impl;
template<class __T> struct __is_nt_default_constructible_impl<__T, true>
    : public __and_<__is_array_known_bounds<__T>,
                    __is_nt_default_constructible_atom<typename __NAMESPACE_STD_SYM remove_all_extents<__T>::type> > {};
template<class __T> struct __is_nt_default_constructible_impl<__T, false>
    : public __is_nt_default_constructible_atom<__T> {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_nothrow_default_constructible
    : public __NAMESPACE_INT_SYM __and_<is_default_constructible<__T>,
                                        __NAMESPACE_INT_SYM __is_nt_default_constructible_impl<__T, is_array<__T>::value> > {};
__NAMESPACE_STD_END
__NAMESPACE_INT_BEGIN
template<class __T, class... __Args> struct __is_nt_constructible_impl
    : public __NAMESPACE_STD_SYM integral_constant<bool, noexcept(__T(__NAMESPACE_STD_SYM declval<__Args>()...))> {};
template<class __T, class __Arg> struct __is_nt_constructible_impl<__T, __Arg>
    : public __NAMESPACE_STD_SYM integral_constant<bool, noexcept(static_cast<__T>(__NAMESPACE_STD_SYM declval<__Arg>()))> {};
template<class __T> struct __is_nt_constructible_impl<__T>
    : public __NAMESPACE_STD_SYM is_nothrow_default_constructible<__T> {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T, class... __Args> struct is_nothrow_constructible
    : public __NAMESPACE_INT_SYM __and_<is_constructible<__T, __Args...>,
                                        __NAMESPACE_INT_SYM __is_nt_constructible_impl<__T, __Args...> > {};
__NAMESPACE_STD_END
#endif /* ... */
__NAMESPACE_INT_BEGIN
template<class __T, bool __Sel> struct __is_nothrow_copy_constructible_impl;
template<class __T> struct __is_nothrow_copy_constructible_impl<__T, false>
    : public __NAMESPACE_STD_SYM false_type {};
template<class __T> struct __is_nothrow_copy_constructible_impl<__T, true>
    : public __NAMESPACE_STD_SYM is_nothrow_constructible<__T, __T const &> {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_nothrow_copy_constructible
    : public __NAMESPACE_INT_SYM __is_nothrow_copy_constructible_impl<__T, __NAMESPACE_INT_SYM __is_referenceable<__T>::value> {};
__NAMESPACE_STD_END
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
__NAMESPACE_INT_BEGIN
template<class __T, bool __Sel> struct __is_nothrow_move_constructible_impl;
template<class __T> struct __is_nothrow_move_constructible_impl<__T, false>
    : public __NAMESPACE_STD_SYM false_type {};
template<class __T> struct __is_nothrow_move_constructible_impl<__T, true>
    : public __NAMESPACE_STD_SYM is_nothrow_constructible<__T, __T &&> {};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_nothrow_move_constructible
    : public __NAMESPACE_INT_SYM __is_nothrow_move_constructible_impl<__T, __NAMESPACE_INT_SYM __is_referenceable<__T>::value> {};
__NAMESPACE_STD_END
#else /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
__NAMESPACE_STD_BEGIN
template<class __T> struct is_nothrow_move_constructible: public false_type {};
__NAMESPACE_STD_END
#endif /* !__COMPILER_HAVE_CXX_RVALUE_REFERENCE */
__NAMESPACE_STD_BEGIN
#if !defined(__GNUC__) || defined(__INTELLISENSE__)
template<class __T, class... __Args> struct is_trivially_constructible
    : public integral_constant<bool, __is_trivially_constructible(__T, __Args...)> {};
#else /* !... */
template<class __T, class... __Args> struct is_trivially_constructible
    : public __NAMESPACE_INT_SYM __and_<is_constructible<__T, __Args...>,
                                        integral_constant<bool, __is_trivially_constructible(__T, __Args...)> > {};
#endif /* ... */
template<class __T> struct is_trivially_default_constructible
    : public is_trivially_constructible<__T>::type {};
__NAMESPACE_STD_END
__NAMESPACE_STD_BEGIN
template<class __T> struct is_trivially_copy_constructible
    : public __NAMESPACE_INT_SYM __and_<is_copy_constructible<__T>,
                                        integral_constant<bool, __is_trivially_constructible(__T, __T const &)> > {};
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
template<class __T> struct is_trivially_move_constructible
    : public __NAMESPACE_INT_SYM __and_<is_move_constructible<__T>,
                                        integral_constant<bool, __is_trivially_constructible(__T, __T &&)> > {};
#else /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
template<class __T> struct is_trivially_move_constructible: public false_type {};
#endif /* !__COMPILER_HAVE_CXX_RVALUE_REFERENCE */
template<class __T> struct has_trivial_default_constructor
    : public integral_constant<bool, __has_trivial_constructor(__T)> {};
template<class __T> struct has_trivial_copy_constructor
    : public integral_constant<bool, __has_trivial_copy(__T)> {};
__NAMESPACE_STD_END

#if 1
__NAMESPACE_INT_BEGIN
struct __do_is_implicitly_default_constructible_impl {
	template<class __T> static void __helper(__T const &);
	template<class __T> static __NAMESPACE_STD_SYM true_type __test(__T const &, decltype(__helper<__T const &>({})) * = 0);
	static __NAMESPACE_STD_SYM false_type __test(...);
};
template<class __T> struct __is_implicitly_default_constructible_impl
    : public __do_is_implicitly_default_constructible_impl {
	typedef decltype(__test(__NAMESPACE_STD_SYM declval<__T>())) type;
};
template<class __T> struct __is_implicitly_default_constructible_safe
    : public __is_implicitly_default_constructible_impl<__T>::type {};
template<class __T> struct __is_implicitly_default_constructible
    : public __and_<__NAMESPACE_STD_SYM is_default_constructible<__T>,
                    __is_implicitly_default_constructible_safe<__T> > {};
__NAMESPACE_INT_END
#endif
__CXXDECL_END

#endif /* !_CXX_BITS_IS_CONSTRUCTIBLE_H */
