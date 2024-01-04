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
#ifndef _CXX_BITS_COMMON_TYPE_H
#define _CXX_BITS_COMMON_TYPE_H 1

#include <__stdcxx.h>

#include "decay.h"
#include "declval.h"

#ifndef __std_common_type_defined
#if defined(__COMPILER_HAVE_CXX_DECLTYPE) && \
defined(__COMPILER_HAVE_CXX_VARIABLE_TEMPLATES)
__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN
#define __std_common_type_defined
template<class... __T> struct common_type;
__NAMESPACE_STD_END
__NAMESPACE_INT_BEGIN
#ifndef __int_success_failure_type_defined
#define __int_success_failure_type_defined
template<class __T> struct __success_type { typedef __T type; };
struct __failure_type {};
#endif /* !__int_success_failure_type_defined */
struct __do_common_type_impl {
	template<class __T, class __U> static __success_type<
	typename __NAMESPACE_STD_SYM decay<decltype(true
	                                            ? __NAMESPACE_STD_SYM declval<__T>()
	                                            : __NAMESPACE_STD_SYM declval<__U>())>::type>
	__test(int);
	template<class __T, class __U> static __failure_type __test(...);
};
template<class __T, class __U> struct __common_type_impl
    : private __do_common_type_impl {
	typedef decltype(__test<__T, __U>(0)) type;
};
struct __do_member_type_wrapper {
	template<class __T> static __success_type<typename __T::type> __test(int);
	template<class __T> static __failure_type __test(...);
};
template<class __T> struct __member_type_wrapper
    : private __do_member_type_wrapper {
	typedef decltype(__test<__T>(0)) type;
};
template<class __C, class... __Args> struct __expanded_common_type_wrapper {
	typedef __NAMESPACE_STD_SYM common_type<typename __C::type, __Args...> type;
};
template<class... __Args>
struct __expanded_common_type_wrapper<__failure_type, __Args...> {
	typedef __failure_type type;
};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct common_type<__T> {
	typedef typename decay<__T>::type type;
};
template<class __T, class __U> struct common_type<__T, __U>
    : public __NAMESPACE_INT_SYM __common_type_impl<__T, __U>::type {};
template<class __T, class __U, class... __V> struct common_type<__T, __U, __V...>
    : public __NAMESPACE_INT_SYM __expanded_common_type_wrapper<
      typename __NAMESPACE_INT_SYM __member_type_wrapper<common_type<__T, __U> >::type, __V...>::type {};
__NAMESPACE_STD_END
__CXXDECL_END
#endif /* ... */
#endif /* !__std_common_type_defined */

#endif /* !_CXX_BITS_COMMON_TYPE_H */
