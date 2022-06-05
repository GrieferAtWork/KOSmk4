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
#ifndef _CXX_BITS___IS_SWAPPABLE_H
#define _CXX_BITS___IS_SWAPPABLE_H 1

#include <__stdcxx.h>

#include <hybrid/typecore.h>

#include "andor.h"
#include "declval.h"
#include "enable_if.h"
#include "integral_constant.h"
#include "is_assignable.h"
#include "is_constructible.h"

__CXXDECL_BEGIN
__NAMESPACE_INT_BEGIN
#if (defined(__COMPILER_HAVE_CXX_DECLTYPE) && \
     defined(__COMPILER_HAVE_CXX11_NOEXCEPT))
template<class __T> struct __is_swappable;
template<class __T> struct __is_nothrow_swappable;
#else
template<class __T> struct __is_swappable: public __NAMESPACE_STD_SYM false_type {};
template<class __T> struct __is_nothrow_swappable: public __NAMESPACE_STD_SYM false_type {};
#endif
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> inline
typename enable_if<__NAMESPACE_INT_SYM __and_<is_move_constructible<__T>,
                                              is_move_assignable<__T> >::value>::type
swap(__T &__lhs, __T &__rhs)
	__CXX_NOEXCEPT_IF((__NAMESPACE_INT_SYM __and_<
	                   is_nothrow_move_constructible<__T>,
	                   is_nothrow_move_assignable<__T> >::value));
#ifndef __clang_tidy__ /* FIXME */
template<class __T, __SIZE_TYPE__ __Count> inline
typename enable_if<__NAMESPACE_INT_SYM __is_swappable<__T>::value>::type
swap(__T (&__lhs)[__Count], __T (&__rhs)[__Count])
	__CXX_NOEXCEPT_IF(__NAMESPACE_INT_SYM __is_nothrow_swappable<__T>::value);
#endif /* !__clang_tidy__ */
__NAMESPACE_STD_END

#if defined(__COMPILER_HAVE_CXX_DECLTYPE) && defined(__COMPILER_HAVE_CXX11_NOEXCEPT)
__NAMESPACE_INT_BEGIN
namespace __swappable_details {
using std::swap;
struct __do_is_swappable_impl {
	template<class __T, class __Sel = decltype(swap(__NAMESPACE_STD_SYM declval<__T &>(),
	                                                __NAMESPACE_STD_SYM declval<__T &>()))>
	static __NAMESPACE_STD_SYM true_type __test(int);
	template<class> static __NAMESPACE_STD_SYM false_type __test(...);
};
struct __do_is_nothrow_swappable_impl {
	template<class __T>
	static __NAMESPACE_STD_SYM integral_constant<
	bool, __CXX_NOEXCEPT_IS(swap(__NAMESPACE_STD_SYM declval<__T &>(),
	                             __NAMESPACE_STD_SYM declval<__T &>()))>
	__test(int);
	template<class __T> static __NAMESPACE_STD_SYM false_type __test(...);
};
} /* namespace __swappable_details */
template<class __T> struct __is_swappable_impl
    : public __swappable_details::__do_is_swappable_impl {
	typedef decltype(__test<__T>(0)) type;
};
template<class __T> struct __is_nothrow_swappable_impl
    : public __swappable_details::__do_is_nothrow_swappable_impl {
	typedef decltype(__test<__T>(0)) type;
};
template<class __T> struct __is_swappable
    : public __is_swappable_impl<__T>::type {};
template<class __T> struct __is_nothrow_swappable
    : public __is_nothrow_swappable_impl<__T>::type {};
__NAMESPACE_INT_END
#endif
__CXXDECL_END

#endif /* !_CXX_BITS___IS_SWAPPABLE_H */
