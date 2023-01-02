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
#ifndef _CXX_BITS_IS_CONVERTIBLE_H
#define _CXX_BITS_IS_CONVERTIBLE_H 1

#include <__stdcxx.h>
#include <features.h>

#include "declval.h"
#include "integral_constant.h"
#include "is_array.h"
#include "is_function.h"
#include "is_void.h"

__CXXDECL_BEGIN
__NAMESPACE_INT_BEGIN
template<class __To1> static void __is_convertible_test_aux(__To1);
template<class __From1, class __To1,
         class __Sel = decltype(__is_convertible_test_aux<__To1>(__NAMESPACE_STD_SYM declval<__From1>()))>
static __NAMESPACE_STD_SYM true_type __is_convertible_test(int);
template<class __From1, class __To1> static __NAMESPACE_STD_SYM false_type __is_convertible_test(...);
template<class __From, class __To,
         bool __Sel = __or_<__NAMESPACE_STD_SYM is_void<__From>,
                            __NAMESPACE_STD_SYM is_function<__To>,
                            __NAMESPACE_STD_SYM is_array<__To> >::value>
struct __is_convertible_helper: __NAMESPACE_STD_SYM is_void<__To> {};
template<class __From, class __To> struct __is_convertible_helper<__From, __To, false> {
	typedef decltype(__is_convertible_test<__From, __To>(0)) type;
};
#ifdef __COMPILER_HAVE_CXX11_NOEXCEPT
template<typename __To1> void __is_nothrow_convertible_test_aux(__To1) noexcept;
template<typename __From1, typename __To1> __NAMESPACE_STD_SYM integral_constant<bool, noexcept(__is_nothrow_convertible_test_aux<__To1>(__NAMESPACE_STD_SYM declval<__From1>()))> __is_nothrow_convertible_test(int);
template<typename __From1, typename __To1> __NAMESPACE_STD_SYM false_type __is_nothrow_convertible_test(...);
template<class __From, class __To,
         bool __Sel = __or_<__NAMESPACE_STD_SYM is_void<__From>,
                            __NAMESPACE_STD_SYM is_function<__To>,
                            __NAMESPACE_STD_SYM is_array<__To> >::value>
struct __is_nothrow_convertible_helper: __NAMESPACE_STD_SYM is_void<__To> {};
template<class __From, class __To> struct __is_nothrow_convertible_helper<__From, __To, false> {
	typedef decltype(__is_nothrow_convertible_test<__From, __To>(0)) type;
};
#endif /* __COMPILER_HAVE_CXX11_NOEXCEPT */
__NAMESPACE_INT_END

__NAMESPACE_STD_BEGIN
template<class __From, class __To> struct is_convertible
    : public __NAMESPACE_INT_SYM __is_convertible_helper<__From, __To>::type {};
#ifdef __COMPILER_HAVE_CXX11_NOEXCEPT
template<class __From, class __To> struct is_nothrow_convertible
    : public __NAMESPACE_INT_SYM __is_nothrow_convertible_helper<__From, __To>::type {};
#else /* __COMPILER_HAVE_CXX11_NOEXCEPT */
template<class __From, class __To> struct is_nothrow_convertible
    : public __NAMESPACE_STD_SYM false_type {}; /* XXX: Integer/float types are noexcept convertible! */
#endif /* !__COMPILER_HAVE_CXX11_NOEXCEPT */
__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_IS_CONVERTIBLE_H */
