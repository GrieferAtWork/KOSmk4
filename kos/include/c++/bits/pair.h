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
#ifndef _CXX_BITS_PAIR_H
#define _CXX_BITS_PAIR_H 1

#include <__stdcxx.h>

#include <hybrid/typecore.h>

#include "forward.h"
#include "move.h"
#include "traits/__is_swappable.h"
#include "traits/add_cv.h"
#include "traits/andor.h"
#include "traits/decay.h"
#include "traits/declval.h"
#include "traits/enable_if.h"
#include "traits/integral_constant.h"
#include "traits/is_assignable.h"
#include "traits/is_constructible.h"
#include "traits/is_convertible.h"
#include "traits/is_same.h"
#include "varargs-template.h"

__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN
#ifndef __std_tuple_fwd_defined
#define __std_tuple_fwd_defined
template<__CXX_VARARGS_TEMPLATE_ARGS_DEF(class, __Types, void)> class tuple;
#endif /* !__std_tuple_fwd_defined */

#ifdef __USE_ISOCXX11
#ifdef __COMPILER_HAVE_CXX_DEFAULT_FUNCTIONS
struct piecewise_construct_t { explicit __CXX_DEFAULT_CTOR(piecewise_construct_t); };
#else /* __COMPILER_HAVE_CXX_DEFAULT_FUNCTIONS */
struct piecewise_construct_t { };
#endif /* !__COMPILER_HAVE_CXX_DEFAULT_FUNCTIONS */
static __CXX11_CONSTEXPR piecewise_construct_t piecewise_construct = piecewise_construct_t();
__NAMESPACE_STD_END
__NAMESPACE_INT_BEGIN
#ifndef __int___Index_tuple_defined
#define __int___Index_tuple_defined
template<__SIZE_TYPE__ ...__Indexes> struct __Index_tuple {};
#endif /* !__int___Index_tuple_defined */
template<class __T1, class __T2, class __U1, class __U2>
struct _ConstructiblePair: public __and_<__or_<
	__NAMESPACE_STD_SYM is_same<typename __NAMESPACE_STD_SYM decay<__T1>::type,
	                            typename __NAMESPACE_STD_SYM decay<__U1>::type>,
	__NAMESPACE_STD_SYM is_constructible<__T1,__U1 const &> >,__or_ <
	__NAMESPACE_STD_SYM is_same<typename __NAMESPACE_STD_SYM decay<__T2>::type,
	                            typename __NAMESPACE_STD_SYM decay<__U2>::type>,
	__NAMESPACE_STD_SYM is_constructible<__T2,__U2 const &> > >::type {};
template<class __T1, class __T2, class __U1, class __U2>
struct _ImplicitlyConvertiblePair: public __and_<__or_<
	__NAMESPACE_STD_SYM is_same<typename __NAMESPACE_STD_SYM decay<__T1>::type,
	                            typename __NAMESPACE_STD_SYM decay<__U1>::type>,
	__NAMESPACE_STD_SYM is_convertible<__U1 const &,__T1> >,__or_<
	__NAMESPACE_STD_SYM is_same<typename __NAMESPACE_STD_SYM decay<__T2>::type,
	                            typename __NAMESPACE_STD_SYM decay<__U2>::type>,
	__NAMESPACE_STD_SYM is_convertible<__U2 const &,__T2> > >::type {};
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
template<class __T1, class __T2, class __U1, class __U2>
struct _MoveConstructiblePair: public __and_<__or_<
	__NAMESPACE_STD_SYM is_same<typename __NAMESPACE_STD_SYM decay<__T1>::type,
	                            typename __NAMESPACE_STD_SYM decay<__U1>::type>,
	__NAMESPACE_STD_SYM is_constructible<__T1,__U1 &&> >,__or_<
	__NAMESPACE_STD_SYM is_same<typename __NAMESPACE_STD_SYM decay<__T2>::type,
	                            typename __NAMESPACE_STD_SYM decay<__U2>::type>,
	__NAMESPACE_STD_SYM is_constructible<__T2,__U2 &&> > >::type {};
template<class __T1, class __T2, class __U1, class __U2>
struct _ImplicitlyMoveConvertiblePair: public __and_<__or_<
	__NAMESPACE_STD_SYM is_same<typename __NAMESPACE_STD_SYM decay<__T1>::type,
	                            typename __NAMESPACE_STD_SYM decay<__U1>::type>,
	__NAMESPACE_STD_SYM is_convertible<__U1 &&,__T1> >,__or_<
	__NAMESPACE_STD_SYM is_same<typename __NAMESPACE_STD_SYM decay<__T2>::type,
	                            typename __NAMESPACE_STD_SYM decay<__U2>::type>,
	__NAMESPACE_STD_SYM is_convertible<__U2 &&,__T2> > >::type {};
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
#endif /* __USE_ISOCXX11 */

template<class __T1, class __T2> struct pair {
	typedef __T1 first_type;
	typedef __T2 second_type;
	__T1 first;
	__T2 second;
#ifdef __USE_ISOCXX11
	template<class __U1 = __T1, class __U2 = __T2,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	__NAMESPACE_INT_SYM __is_implicitly_default_constructible<__U1>,
	         	__NAMESPACE_INT_SYM __is_implicitly_default_constructible<__U2>
	         >::value,bool>::type __Sel = true>
#endif /* __USE_ISOCXX11 */
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair()
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1()) &&
	                  __CXX_NOEXCEPT_IS(__T2()))
	    : first()
	    , second()
	{}
#ifdef __USE_ISOCXX11
	template<class __U1 = __T1, class __U2 = __T2,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	is_default_constructible<__U1>,
	         	is_default_constructible<__U2>,
	         	__NAMESPACE_INT_SYM __not_<
	         		__NAMESPACE_INT_SYM __and_<
	         			__NAMESPACE_INT_SYM __is_implicitly_default_constructible<__U1>,
	         			__NAMESPACE_INT_SYM __is_implicitly_default_constructible<__U2>
	         		>
	         	>
	         >::value,bool>::type __Sel = false>
	explicit __CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair()
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1()) &&
	                  __CXX_NOEXCEPT_IS(__T2()))
	    : first()
	    , second()
	{}
#endif /* __USE_ISOCXX11 */

#ifndef __USE_ISOCXX11
	pair(const __T1& __a, const __T2& __b)
	: first(__a),second(__b) {}
#else /* !__USE_ISOCXX11 */
	template<class __U1 = __T1, class __U2 = __T2,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	__NAMESPACE_INT_SYM _ConstructiblePair<__T1,__T2,__U1,__U2>,
	         	__NAMESPACE_INT_SYM _ImplicitlyConvertiblePair<__T1,__T2,__U1,__U2>
	         >::value,bool>::type __Sel = true>
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair(__T1 const &__a, __T2 const &__b)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1(__a)) &&
	                  __CXX_NOEXCEPT_IS(__T2(__b)))
	    : first(__a)
	    , second(__b)
	{}
	template<class __U1 = __T1, class __U2 = __T2,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	__NAMESPACE_INT_SYM _ConstructiblePair<__T1,__T2,__U1,__U2>,
	         	__NAMESPACE_INT_SYM __not_< __NAMESPACE_INT_SYM _ImplicitlyConvertiblePair<__T1,__T2,__U1,__U2> >
	         >::value,bool>::type __Sel = false>
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL
	pair(__T1 const &__a, __T2 const &__b)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1(__a)) &&
	                  __CXX_NOEXCEPT_IS(__T2(__b)))
	    : first(__a)
	    , second(__b)
	{}
#endif /* __USE_ISOCXX11 */

#ifndef __USE_ISOCXX11
	template<class __U1, class __U2>
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair(pair<__U1, __U2> const &__other)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1(__other.first)) &&
	                  __CXX_NOEXCEPT_IS(__T2(__other.second)))
	    : first(__other.first)
	    , second(__other.second)
	{}
#else /* __USE_ISOCXX11 */
	template<class __U1, class __U2,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	__NAMESPACE_INT_SYM _ConstructiblePair<__T1,__T2,__U1,__U2>,
	         	__NAMESPACE_INT_SYM _ImplicitlyConvertiblePair<__T1,__T2,__U1,__U2>
	         >::value,bool>::type __Sel = true>
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair(pair<__U1,__U2> const &__other)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1(__other.first)) &&
	                  __CXX_NOEXCEPT_IS(__T2(__other.second)))
	    : first(__other.first)
	    , second(__other.second)
	{}
	template<class __U1, class __U2,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	__NAMESPACE_INT_SYM _ConstructiblePair<__T1,__T2,__U1,__U2>,
	         	__NAMESPACE_INT_SYM __not_< __NAMESPACE_INT_SYM _ImplicitlyConvertiblePair<__T1,__T2,__U1,__U2> >
	         >::value,bool>::type __Sel = false>
	explicit __CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair(pair<__U1,__U2> const &__other)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1(__other.first)) &&
	                  __CXX_NOEXCEPT_IS(__T2(__other.second)))
	    : first(__other.first)
	    , second(__other.second)
	{}

#ifdef __COMPILER_HAVE_CXX_DEFAULT_FUNCTIONS
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	__CXX11_CONSTEXPR pair(pair &&__other) = default;
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
	__CXX11_CONSTEXPR pair(pair const &__other) = default;
#endif /* __COMPILER_HAVE_CXX_DEFAULT_FUNCTIONS */

#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	template<class __U1,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	__NAMESPACE_INT_SYM _ConstructiblePair<__T2,__T2,__T2,__T2>,
	         	__NAMESPACE_INT_SYM _MoveConstructiblePair<__T1,__T2,__U1,__T2>,
	         	__NAMESPACE_INT_SYM _ImplicitlyConvertiblePair<__T2,__T2,__T2,__T2>,
	         	__NAMESPACE_INT_SYM _ImplicitlyMoveConvertiblePair<__T1,__T2,__U1,__T2>
	         >::value,bool>::type __Sel = true>
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair(__U1 &&__x, __T2 const &__y)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1(forward<__U1>(__x))) &&
	                  __CXX_NOEXCEPT_IS(__T2(__y)))
	    : first(forward<__U1>(__x))
	    , second(__y)
	{}

	template<class __U1,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	__NAMESPACE_INT_SYM _ConstructiblePair<__T2,__T2,__T2,__T2>,
	         	__NAMESPACE_INT_SYM _MoveConstructiblePair<__T1,__T2,__U1,__T2>,
	         	__NAMESPACE_INT_SYM __or_<
	         		__NAMESPACE_INT_SYM __not_< __NAMESPACE_INT_SYM _ImplicitlyConvertiblePair<__T2,__T2,__T2,__T2> >,
	         		__NAMESPACE_INT_SYM __not_< __NAMESPACE_INT_SYM _ImplicitlyMoveConvertiblePair<__T1,__T2,__U1,__T2> > >
	         >::value,bool>::type __Sel = false>
	explicit __CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair(__U1 &&__x, __T2 const &__y)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1(forward<__U1>(__x))) &&
	                  __CXX_NOEXCEPT_IS(__T2(__y)))
	    : first(forward<__U1>(__x))
	    , second(__y)
	{}

	template<class __U2,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	__NAMESPACE_INT_SYM _ConstructiblePair<__T1,__T1,__T1,__T1>,
	         	__NAMESPACE_INT_SYM _MoveConstructiblePair<__T1,__T2,__T1,__U2>,
	         	__NAMESPACE_INT_SYM _ImplicitlyConvertiblePair<__T1,__T1,__T1,__T1>,
	         	__NAMESPACE_INT_SYM _ImplicitlyMoveConvertiblePair<__T1,__T2,__T1,__U2>
	         >::value,bool>::type __Sel = true>
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair(__T1 const &__x, __U2 &&__y)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1(__x)) &&
	                  __CXX_NOEXCEPT_IS(__T2(forward<__U2>(__y))))
	    : first(__x)
	    , second(forward<__U2>(__y))
	{}

	template<class __U2,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	__NAMESPACE_INT_SYM _ConstructiblePair<__T1,__T1,__T1,__T1>,
	         	__NAMESPACE_INT_SYM _MoveConstructiblePair<__T1,__T2,__T1,__U2>,
	         	__NAMESPACE_INT_SYM __or_<
	         		__NAMESPACE_INT_SYM __not_< __NAMESPACE_INT_SYM _ImplicitlyConvertiblePair<__T1,__T1,__T1,__T1> >,
	         		__NAMESPACE_INT_SYM __not_< __NAMESPACE_INT_SYM _ImplicitlyMoveConvertiblePair<__T1,__T2,__T1,__U2> > >
	         >::value,bool>::type __Sel = false>
	explicit __CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair(__T1 const &__x, __U2 &&__y)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1(__x)) &&
	                  __CXX_NOEXCEPT_IS(__T2(forward<__U2>(__y))))
	    : first(__x)
	    , second(forward<__U2>(__y))
	{}

	template<class __U1, class __U2,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	__NAMESPACE_INT_SYM _MoveConstructiblePair<__T1,__T2,__U1,__U2>,
	         	__NAMESPACE_INT_SYM _ImplicitlyMoveConvertiblePair<__T1,__T2,__U1,__U2>
	         >::value,bool>::type __Sel = true>
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair(__U1 &&__x, __U2 &&__y)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1(forward<__U1>(__x))) &&
	                  __CXX_NOEXCEPT_IS(__T2(forward<__U2>(__y))))
	    : first(forward<__U1>(__x))
	    , second(forward<__U2>(__y))
	{}

	template<class __U1, class __U2,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	__NAMESPACE_INT_SYM _MoveConstructiblePair<__T1,__T2,__U1,__U2>,
	         	__NAMESPACE_INT_SYM __not_< __NAMESPACE_INT_SYM _ImplicitlyMoveConvertiblePair<__T1,__T2,__U1,__U2> >
	         >::value,bool>::type __Sel = false>
	explicit __CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair(__U1 &&__x, __U2 &&__y)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1(forward<__U1>(__x))) &&
	                  __CXX_NOEXCEPT_IS(__T2(forward<__U2>(__y))))
	    : first(forward<__U1>(__x))
	    , second(forward<__U2>(__y))
	{}

	template<class __U1, class __U2,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	__NAMESPACE_INT_SYM _MoveConstructiblePair<__T1,__T2,__U1,__U2>,
	         	__NAMESPACE_INT_SYM _ImplicitlyMoveConvertiblePair<__T1,__T2,__U1,__U2>
	         >::value,bool>::type __Sel = true>
	__CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair(pair<__U1,__U2> &&__other)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1(forward<__U1>(__other.first))) &&
	                  __CXX_NOEXCEPT_IS(__T2(forward<__U2>(__other.second))))
	    : first(forward<__U1>(__other.first))
	    , second(forward<__U2>(__other.second))
	{}

	template<class __U1, class __U2,
	         typename enable_if< __NAMESPACE_INT_SYM __and_<
	         	__NAMESPACE_INT_SYM _MoveConstructiblePair<__T1,__T2,__U1,__U2>,
	         	__NAMESPACE_INT_SYM __not_< __NAMESPACE_INT_SYM _ImplicitlyMoveConvertiblePair<__T1,__T2,__U1,__U2> >
	         >::value,bool>::type __Sel = false>
	explicit __CXX_CLASSMEMBER __CXX11_CONSTEXPR __LIBCCALL pair(pair<__U1,__U2> &&__other)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(__T1(forward<__U1>(__other.first))) &&
	                  __CXX_NOEXCEPT_IS(__T2(forward<__U2>(__other.second))))
	    : first(forward<__U1>(__other.first))
	    , second(forward<__U2>(__other.second))
	{}
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */

	template<__CXX_VARARGS_TEMPLATE_ARGS(class, __Types1),
	         __CXX_VARARGS_TEMPLATE_ARGS(class, __Types2)>
	pair(piecewise_construct_t,
	     tuple<__CXX_VARARGS_TYPENAME_ARGS(__Types1)>,
	     tuple<__CXX_VARARGS_TYPENAME_ARGS(__Types2)>);
	__CXX_CLASSMEMBER pair &__LIBCCALL operator = (pair const &__other)
	__CXX_NOEXCEPT_IF((__NAMESPACE_INT_SYM __and_<is_nothrow_copy_assignable<__T1>,
	                                              is_nothrow_copy_assignable<__T2> >::value))
	{
		this->first  = __other.first;
		this->second = __other.second;
		return *this;
	}
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	__CXX_CLASSMEMBER pair &__LIBCCALL operator = (pair &&__other)
	__CXX_NOEXCEPT_IF((__NAMESPACE_INT_SYM __and_<is_nothrow_move_assignable<__T1>,
	                                              is_nothrow_move_assignable<__T2> >::value))
	{
		this->first  = forward<first_type>(__other.first);
		this->second = forward<second_type>(__other.second);
		return *this;
	}
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */

	template<class __U1, class __U2>
	__CXX_CLASSMEMBER pair &__LIBCCALL operator = (pair<__U1,__U2> const &__other)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(declval<__T1 &>() = __other.first) &&
	                  __CXX_NOEXCEPT_IS(declval<__T2 &>() = __other.second))
	{
		this->first  = __other.first;
		this->second = __other.second;
		return *this;
	}

#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	template<class __U1, class __U2>
	__CXX_CLASSMEMBER pair &__LIBCCALL operator=(pair<__U1, __U2> &&__other)
	__CXX_NOEXCEPT_IF(__CXX_NOEXCEPT_IS(declval<__T1 &>() = forward<__U1>(__other.first)) &&
	                  __CXX_NOEXCEPT_IS(declval<__T2 &>() = forward<__U2>(__other.second)))
	{
		this->first  = forward<__U1>(__other.first);
		this->second = forward<__U2>(__other.second);
		return *this;
	}
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */

	void swap(pair &__other)
	__CXX_NOEXCEPT(__NAMESPACE_INT_SYM __is_nothrow_swappable<__T1>::value &&
	               __NAMESPACE_INT_SYM __is_nothrow_swappable<__T2>::value) {
		using std::swap;
		swap(first,__other.first);
		swap(second,__other.second);
	}
private:
	template<__CXX_VARARGS_TEMPLATE_ARGS(class, __Types1),
	         __CXX_VARARGS_TEMPLATE_ARGS(__SIZE_TYPE__, __Indices1),
	         __CXX_VARARGS_TEMPLATE_ARGS(class, __Types2),
	         __CXX_VARARGS_TEMPLATE_ARGS(__SIZE_TYPE__, __Indices2)>
	pair(tuple<__CXX_VARARGS_TYPENAME_ARGS(__Types1)> &,
	     tuple<__CXX_VARARGS_TYPENAME_ARGS(__Types2)> &,
	     __NAMESPACE_INT_SYM __Index_tuple<__CXX_VARARGS_TYPENAME_ARGS(__Indices1)>,
	     __NAMESPACE_INT_SYM __Index_tuple<__CXX_VARARGS_TYPENAME_ARGS(__Indices2)>);
#endif /* !__USE_ISOCXX11 */
};

template<class __T1, class __T2> __CXX_FORCEINLINE __CXX11_CONSTEXPR bool __LIBCCALL
operator==(pair<__T1, __T2> const &__lhs, pair<__T1, __T2> const &__rhs)
__CXX_NOEXCEPT_IFNX((bool)(__lhs.first == __rhs.first && __lhs.second == __rhs.second))
{ return __lhs.first == __rhs.first && __lhs.second == __rhs.second; }
template<class __T1, class __T2> __CXX_FORCEINLINE __CXX11_CONSTEXPR bool __LIBCCALL
operator<(pair<__T1, __T2> const &__lhs, pair<__T1, __T2> const &__rhs)
__CXX_NOEXCEPT_IFNX((bool)(__lhs.first < __rhs.first || (!(__rhs.first < __lhs.first) && __lhs.second < __rhs.second)))
{ return __lhs.first < __rhs.first || (!(__rhs.first < __lhs.first) && __lhs.second < __rhs.second); }
template<class __T1, class __T2> __CXX_FORCEINLINE __CXX11_CONSTEXPR bool __LIBCCALL
operator!=(pair<__T1, __T2> const &__lhs, pair<__T1, __T2> const &__rhs)
__CXX_NOEXCEPT_IFNX((bool)(!(__lhs == __rhs)))
{ return !(__lhs == __rhs); }
template<class __T1, class __T2> __CXX_FORCEINLINE __CXX11_CONSTEXPR bool __LIBCCALL
operator>(pair<__T1, __T2> const &__lhs, pair<__T1, __T2> const &__rhs)
__CXX_NOEXCEPT_IFNX((bool)(__rhs < __lhs))
{ return __rhs < __lhs; }
template<class __T1, class __T2> __CXX_FORCEINLINE __CXX11_CONSTEXPR bool __LIBCCALL
operator<=(pair<__T1, __T2> const &__lhs, pair<__T1, __T2> const &__rhs)
__CXX_NOEXCEPT_IFNX((bool)(!(__rhs < __lhs)))
{ return !(__rhs < __lhs); }
template<class __T1, class __T2> __CXX_FORCEINLINE __CXX11_CONSTEXPR bool __LIBCCALL
operator>=(pair<__T1, __T2> const &__lhs, pair<__T1, __T2> const &__rhs)
__CXX_NOEXCEPT_IFNX((bool)(!(__lhs < __rhs)))
{ return !(__lhs < __rhs); }

#ifdef __USE_ISOCXX11
template<class __T1, class __T2> __CXX_FORCEINLINE void __LIBCCALL
swap(pair<__T1, __T2> &__lhs, pair<__T1, __T2> &__rhs)
__CXX_NOEXCEPT_IFNX(__lhs.swap(__rhs))
{ __lhs.swap(__rhs); }
#endif /* __USE_ISOCXX11 */

#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
template<class __T1, class __T2>
__CXX_FORCEINLINE __CXX11_CONSTEXPR
pair<typename __NAMESPACE_INT_SYM __decay_and_strip<__T1>::__type,
     typename __NAMESPACE_INT_SYM __decay_and_strip<__T2>::__type>
__LIBCCALL make_pair(__T1 &&__first, __T2 &&__second)
	__CXX_NOEXCEPT_IF((__NAMESPACE_INT_SYM __and_<
	                   is_nothrow_move_constructible<typename __NAMESPACE_INT_SYM __decay_and_strip<__T1>::__type>,
	                   is_nothrow_move_constructible<typename __NAMESPACE_INT_SYM __decay_and_strip<__T2>::__type> >::value))
{
	typedef typename __NAMESPACE_INT_SYM __decay_and_strip<__T1>::__type __ds_type1;
	typedef typename __NAMESPACE_INT_SYM __decay_and_strip<__T2>::__type __ds_type2;
	typedef pair<__ds_type1, __ds_type2> __pair_type;
	return __pair_type(forward<__T1>(__first), forward<__T2>(__second));
}
#else /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
template<class __T1, class __T2>
__CXX_FORCEINLINE __CXX11_CONSTEXPR pair<__T1,__T2>
__LIBCCALL make_pair(__T1 __first, __T2 __second)
	__CXX_NOEXCEPT_IF((__NAMESPACE_INT_SYM __and_<
	                   is_nothrow_copy_constructible<__T1>,
	                   is_nothrow_copy_constructible<__T2> >::value))
{
	return pair<__T1,__T2>(__first,__second);
}
#endif /* !__COMPILER_HAVE_CXX_RVALUE_REFERENCE */



#ifndef __std_tuple_size_fwd_defined
#define __std_tuple_size_fwd_defined
template<class __T> struct tuple_size;
#endif /* !__std_tuple_size_fwd_defined */

template<class __T1, class __T2> struct tuple_size<pair<__T1, __T2> >: public integral_constant<__SIZE_TYPE__, 2> {};
template<__SIZE_TYPE__ __i, class __T> struct tuple_element;
template<class __T1, class __T2> struct tuple_element<0, pair<__T1, __T2> > { typedef __T1 type; };
template<class __T1, class __T2> struct tuple_element<1, pair<__T1, __T2> > { typedef __T2 type; };
__NAMESPACE_STD_END
__NAMESPACE_INT_BEGIN
template<__SIZE_TYPE__ __Int> struct __pair_get;
template<> struct __pair_get<0> {
	template<class __T1, class __T2> static __CXX_FORCEINLINE __CXX11_CONSTEXPR __T1 &__LIBCCALL __get(__NAMESPACE_STD_SYM pair<__T1, __T2> &__pair) __CXX_NOEXCEPT { return __pair.first; }
	template<class __T1, class __T2> static __CXX_FORCEINLINE __CXX11_CONSTEXPR __T1 const &__LIBCCALL __const_get(const std::pair<__T1, __T2> &__pair) __CXX_NOEXCEPT { return __pair.first; }
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	template<class __T1, class __T2> static __CXX_FORCEINLINE __CXX11_CONSTEXPR __T1 &&__LIBCCALL __move_get(__NAMESPACE_STD_SYM pair<__T1, __T2> &&__pair) __CXX_NOEXCEPT { return __NAMESPACE_STD_SYM forward<__T1>(__pair.first); }
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
};
template<> struct __pair_get<1> {
	template<class __T1, class __T2> static __CXX_FORCEINLINE __CXX11_CONSTEXPR __T1 &__LIBCCALL __get(__NAMESPACE_STD_SYM pair<__T1, __T2> &__pair) __CXX_NOEXCEPT { return __pair.second; }
	template<class __T1, class __T2> static __CXX_FORCEINLINE __CXX11_CONSTEXPR __T1 const &__LIBCCALL __const_get(const std::pair<__T1, __T2> &__pair) __CXX_NOEXCEPT { return __pair.second; }
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
	template<class __T1, class __T2> static __CXX_FORCEINLINE __CXX11_CONSTEXPR __T1 &&__LIBCCALL __move_get(__NAMESPACE_STD_SYM pair<__T1, __T2> &&__pair) __CXX_NOEXCEPT { return __NAMESPACE_STD_SYM forward<__T1>(__pair.second); }
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<__SIZE_TYPE__ __Int, class __T1, class __T2> __CXX_FORCEINLINE __CXX11_CONSTEXPR typename tuple_element<__Int, pair<__T1, __T2> >::type &__LIBCCALL get(pair<__T1, __T2> &__self) __CXX_NOEXCEPT { return __NAMESPACE_INT_SYM __pair_get<__Int>::__get(__self); }
template<__SIZE_TYPE__ __Int, class __T1, class __T2> __CXX_FORCEINLINE __CXX11_CONSTEXPR typename tuple_element<__Int, pair<__T1, __T2> >::type const &__LIBCCALL get(pair<__T1, __T2> const &__self) __CXX_NOEXCEPT { return __NAMESPACE_INT_SYM __pair_get<__Int>::__const_get(__self); }
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
template<__SIZE_TYPE__ __Int, class __T1, class __T2> __CXX_FORCEINLINE __CXX11_CONSTEXPR typename tuple_element<__Int, pair<__T1, __T2> >::type &&__LIBCCALL get(std::pair<__T1, __T2> &&__self) __CXX_NOEXCEPT { return __NAMESPACE_INT_SYM __pair_get<__Int>::__move_get(move(__self)); }
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */

#ifdef __USE_ISOCXX11
#define __cpp_lib_tuples_by_type 201304
template<class __T, class __U> __CXX_FORCEINLINE __CXX11_CONSTEXPR __T &__LIBCCALL get(pair<__T, __U> &__self) __CXX_NOEXCEPT { return __self.first; }
template<class __T, class __U> __CXX_FORCEINLINE __CXX11_CONSTEXPR __T const &__LIBCCALL get(pair<__T, __U> const &__self) __CXX_NOEXCEPT { return __self.first; }
template<class __T, class __U> __CXX_FORCEINLINE __CXX11_CONSTEXPR __T &__LIBCCALL get(pair<__U, __T> &__self) __CXX_NOEXCEPT { return __self.second; }
template<class __T, class __U> __CXX_FORCEINLINE __CXX11_CONSTEXPR __T const &__LIBCCALL get(pair<__U, __T> const &__self) __CXX_NOEXCEPT { return __self.second; }
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
template<class __T, class __U> __CXX_FORCEINLINE __CXX11_CONSTEXPR __T &&__LIBCCALL get(pair<__T, __U> &&__self) __CXX_NOEXCEPT { return move(__self.first); }
template<class __T, class __U> __CXX_FORCEINLINE __CXX11_CONSTEXPR __T &&__LIBCCALL get(pair<__U, __T> &&__self) __CXX_NOEXCEPT { return move(__self.second); }
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */

#endif /* __USE_ISOCXX11 */

__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_PAIR_H */
