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
#ifndef _CXX_BITS_TUPLE_H
#define _CXX_BITS_TUPLE_H 1

#include <__stdcxx.h>
#include <features.h>

#include <hybrid/typecore.h>

#include "traits/add_cv.h"
#include "traits/integral_constant.h"
#ifdef __USE_ISOCXX11
#include "integer_sequence.h"
#endif /* __USE_ISOCXX11 */

__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN

#ifndef __std_tuple_size_fwd_defined
#define __std_tuple_size_fwd_defined
template<class __T> struct tuple_size;
#endif /* !__std_tuple_size_fwd_defined */
template<class __T> struct tuple_size<__T const>: public integral_constant<__SIZE_TYPE__, tuple_size<__T>::value> {};
template<class __T> struct tuple_size<__T volatile>: public integral_constant<__SIZE_TYPE__, tuple_size<__T>::value> {};
template<class __T> struct tuple_size<__T const volatile>: public integral_constant<__SIZE_TYPE__, tuple_size<__T>::value> {};
template<__SIZE_TYPE__ __i, class __T> struct tuple_element;
template<__SIZE_TYPE__ __i, class __T> struct tuple_element<__i, __T const> { typedef typename add_const<typename tuple_element<__i, __T>::type>::type type; };
template<__SIZE_TYPE__ __i, class __T> struct tuple_element<__i, __T volatile> { typedef typename add_volatile<typename tuple_element<__i, __T>::type>::type type; };
template<__SIZE_TYPE__ __i, class __T> struct tuple_element<__i, __T const volatile> { typedef typename add_cv<typename tuple_element<__i, __T>::type>::type type; };
#ifdef __USE_ISOCXX11
#ifdef __COMPILER_HAVE_CXX_TEMPLATE_USING
#define __cpp_lib_tuple_element_t 201402
template<__SIZE_TYPE__ __i, class __T> using tuple_element_t = typename tuple_element<__i, __T>::type;
#endif /* __COMPILER_HAVE_CXX_TEMPLATE_USING */
#endif

#ifdef __USE_ISOCXX11
#define __cpp_lib_integer_sequence 201304
#ifdef __COMPILER_HAVE_CXX_TEMPLATE_USING
__NAMESPACE_STD_END
__NAMESPACE_INT_BEGIN
#ifndef __int___Index_tuple_defined
#define __int___Index_tuple_defined
template<__SIZE_TYPE__... __Indexes> struct __Index_tuple {};
#endif /* !__int___Index_tuple_defined */
template<class __ITuple1, class __ITuple2> struct __Itup_cat;
template<__SIZE_TYPE__... __Index1, __SIZE_TYPE__... __Index2> struct __Itup_cat<__Index_tuple<__Index1...>, __Index_tuple<__Index2...> > { typedef __Index_tuple<__Index1..., (__Index2 + sizeof...(__Index1))...> __type; };
template<__SIZE_TYPE__ __Num> struct __Build_index_tuple: public __Itup_cat<typename __Build_index_tuple<__Num / 2>::__type, typename __Build_index_tuple<__Num - __Num / 2>::__type> {};
template<> struct __Build_index_tuple<1> { typedef __Index_tuple<0> __type; };
template<> struct __Build_index_tuple<0> { typedef __Index_tuple<> __type; };
template<class __T, __T __Num, class __ISeq = typename __NAMESPACE_INT_SYM __Build_index_tuple<__Num>::__type>
struct __Make_integer_sequence;
template<class __T, __T __Num, __SIZE_TYPE__... __Index>
struct __Make_integer_sequence<__T, __Num, __NAMESPACE_INT_SYM __Index_tuple<__Index...> > {
	static_assert(__Num >= 0, "Cannot make integer sequence of negative length");
	typedef __NAMESPACE_STD_SYM integer_sequence<__T, static_cast<__T>(__Index)...> __type;
};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T, __T __Num> using make_integer_sequence = typename __NAMESPACE_INT_SYM __Make_integer_sequence<__T, __Num>::__type;
template<__SIZE_TYPE__... __Index> using index_sequence    = integer_sequence<__SIZE_TYPE__, __Index...>;
template<__SIZE_TYPE__ __Num> using make_index_sequence    = make_integer_sequence<__SIZE_TYPE__, __Num>;
template<class... __Types> using index_sequence_for        = make_index_sequence<sizeof...(__Types)>;
#endif /* __COMPILER_HAVE_CXX_TEMPLATE_USING */
#endif /* __USE_ISOCXX11 */

__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_TUPLE_H */
