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
#ifndef _CXX_BITS_INTEGRAL_CONSTANT_H
#define _CXX_BITS_INTEGRAL_CONSTANT_H 1

#include <__stdcxx.h>

__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN

template<class __T, __T __v>
struct integral_constant {
	__CXX_STATIC_CONST(__T, value = __v);
	typedef __T                         value_type;
	typedef integral_constant<__T, __v> type;
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR operator value_type() const __CXX_NOEXCEPT {
		return __v;
	}
#ifdef __USE_ISOCXX11
#define __cpp_lib_integral_constant_callable 201304
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR value_type operator()() const __CXX_NOEXCEPT {
		return __v;
	}
#endif /* __USE_ISOCXX11 */
};

#ifdef __COMPILER_HAVE_CXX_STATIC_CONST
template<class __T, __T __v>
__CXX11_CONSTEXPR __T integral_constant<__T, __v>::value;
#endif /* __COMPILER_HAVE_CXX_STATIC_CONST */

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_INTEGRAL_CONSTANT_H */
