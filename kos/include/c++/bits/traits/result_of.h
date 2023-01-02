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
#ifndef _CXX_BITS_RESULT_OF_H
#define _CXX_BITS_RESULT_OF_H 1

#include <__stdcxx.h>

#ifndef __std_result_of_defined
#if defined(__COMPILER_HAVE_CXX_DECLTYPE) && \
defined(__COMPILER_HAVE_CXX_VARIABLE_TEMPLATES)
#include "andor.h"
#include "conditional.h"
#include "decay.h"
#include "declval.h"
#include "is_base_of.h"
#include "is_member.h"
#include "is_member_pointer.h"
#include "is_same.h"
#include "remove_cv.h"
#include "remove_reference.h"

#define __cpp_lib_result_of_sfinae 201210

__CXXDECL_BEGIN
#ifndef __std_reference_wrapper_defined
#define __std_reference_wrapper_defined
__NAMESPACE_STD_BEGIN
template<class __T> class reference_wrapper;
__NAMESPACE_STD_END
#endif /* !__std_reference_wrapper_defined */
__NAMESPACE_INT_BEGIN
#ifndef __int_success_failure_type_defined
#define __int_success_failure_type_defined
template<class __T> struct __success_type { typedef __T type; };
struct __failure_type {};
#endif /* !__int_success_failure_type_defined */
struct __invoke_memfun_ref {};
struct __invoke_memfun_deref {};
struct __invoke_memobj_ref {};
struct __invoke_memobj_deref {};
struct __invoke_other {};
template<class __T, class __Tag> struct __result_of_success
    : public __success_type<__T> {
	typedef __Tag __invoke_type;
};
struct __result_of_memfun_ref_impl {
	template<class __F, class __T1, class... __Args>
	static __result_of_success<decltype((
	                           __NAMESPACE_STD_SYM declval<__T1>().*__NAMESPACE_STD_SYM declval<__F>())(
	                           __NAMESPACE_STD_SYM declval<__Args>()...)),
	                           __invoke_memfun_ref>
	__test(int);
	template<class... __Types>
	static __failure_type __test(...);
};
struct __result_of_memfun_deref_impl {
	template<class __F, class __T1, class... __Args>
	static __result_of_success<decltype((
	                           (*__NAMESPACE_STD_SYM declval<__T1>()).*__NAMESPACE_STD_SYM declval<__F>())(
	                           __NAMESPACE_STD_SYM declval<__Args>()...)),
	                           __invoke_memfun_deref>
	__test(int);
	template<class... __Types>
	static __failure_type __test(...);
};
struct __result_of_memobj_ref_impl {
	template<class __F, class __T1>
	static __result_of_success<decltype(
	                           __NAMESPACE_STD_SYM declval<__T1>().*__NAMESPACE_STD_SYM declval<__F>()),
	                           __invoke_memobj_ref>
	__test(int);
	template<class __F, class __T1>
	static __failure_type __test(...);
};
struct __result_of_memobj_deref_impl {
	template<class __F, class __T1>
	static __result_of_success<decltype(
	                           (*__NAMESPACE_STD_SYM declval<__T1>()).*__NAMESPACE_STD_SYM declval<__F>()),
	                           __invoke_memobj_deref>
	__test(int);
	template<class __F, class __T1>
	static __failure_type __test(...);
};
template<class __MemberPointer, class __Arg, class... __Args> struct __result_of_memfun_ref
    : private __result_of_memfun_ref_impl {
	typedef decltype(__test<__MemberPointer, __Arg, __Args...>(0)) type;
};
template<class __MemberPointer, class __Arg, class... __Args> struct __result_of_memfun_deref
    : private __result_of_memfun_deref_impl {
	typedef decltype(__test<__MemberPointer, __Arg, __Args...>(0)) type;
};
template<class __MemberPointer, class __Arg> struct __result_of_memobj_ref
    : private __result_of_memobj_ref_impl {
	typedef decltype(__test<__MemberPointer, __Arg>(0)) type;
};
template<class __MemberPointer, class __Arg> struct __result_of_memobj_deref
    : private __result_of_memobj_deref_impl {
	typedef decltype(__test<__MemberPointer, __Arg>(0)) type;
};
template<class __MemberPointer, class __Arg> struct __result_of_memobj;
template<class _Res, class _Class, class __Arg> struct __result_of_memobj<_Res _Class::*, __Arg> {
	typedef typename __NAMESPACE_STD_SYM remove_cv<
	typename __NAMESPACE_STD_SYM remove_reference<__Arg>::type>::type _Argval;
	typedef _Res _Class::*__MemberPointer;
	typedef typename __NAMESPACE_STD_SYM conditional<
	__or_<__NAMESPACE_STD_SYM is_same<_Argval, _Class>,
	      __NAMESPACE_STD_SYM is_base_of<_Class, _Argval> >::value,
	__result_of_memobj_ref<__MemberPointer, __Arg>,
	__result_of_memobj_deref<__MemberPointer, __Arg> >::type::type type;
};
template<class __MemberPointer, class __Arg, class... __Args> struct __result_of_memfun;
template<class _Res, class _Class, class __Arg, class... __Args>
struct __result_of_memfun<_Res _Class::*, __Arg, __Args...> {
	typedef typename __NAMESPACE_STD_SYM remove_cv<
	typename __NAMESPACE_STD_SYM remove_reference<__Arg>::type>::type _Argval;
	typedef _Res _Class::*__MemberPointer;
	typedef typename __NAMESPACE_STD_SYM conditional<
	__or_<__NAMESPACE_STD_SYM is_same<_Argval, _Class>,
	      __NAMESPACE_STD_SYM is_base_of<_Class, _Argval> >::value,
	__result_of_memfun_ref<__MemberPointer, __Arg, __Args...>,
	__result_of_memfun_deref<__MemberPointer, __Arg, __Args...> >::type::type type;
};
template<class _Res, class _Class, class __Arg>
struct __result_of_memobj<_Res _Class::*, __NAMESPACE_STD_SYM reference_wrapper<__Arg> >
    : public __result_of_memobj_ref<_Res _Class::*, __Arg &> {};
template<class _Res, class _Class, class __Arg>
struct __result_of_memobj<_Res _Class::*, __NAMESPACE_STD_SYM reference_wrapper<__Arg> &>
    : public __result_of_memobj_ref<_Res _Class::*, __Arg &> {};
template<class _Res, class _Class, class __Arg>
struct __result_of_memobj<_Res _Class::*, __NAMESPACE_STD_SYM reference_wrapper<__Arg> const &>
    : public __result_of_memobj_ref<_Res _Class::*, __Arg &> {};
template<class _Res, class _Class, class __Arg>
struct __result_of_memobj<_Res _Class::*, __NAMESPACE_STD_SYM reference_wrapper<__Arg> &&>
    : public __result_of_memobj_ref<_Res _Class::*, __Arg &> {};
template<class _Res, class _Class, class __Arg>
struct __result_of_memobj<_Res _Class::*, __NAMESPACE_STD_SYM reference_wrapper<__Arg> const &&>
    : public __result_of_memobj_ref<_Res _Class::*, __Arg &> {};
template<class _Res, class _Class, class __Arg, class... __Args>
struct __result_of_memfun<_Res _Class::*, __NAMESPACE_STD_SYM reference_wrapper<__Arg>, __Args...>
    : public __result_of_memfun_ref<_Res _Class::*, __Arg &, __Args...> {};
template<class _Res, class _Class, class __Arg, class... __Args>
struct __result_of_memfun<_Res _Class::*, __NAMESPACE_STD_SYM reference_wrapper<__Arg> &, __Args...>
    : public __result_of_memfun_ref<_Res _Class::*, __Arg &, __Args...> {};
template<class _Res, class _Class, class __Arg, class... __Args>
struct __result_of_memfun<_Res _Class::*, __NAMESPACE_STD_SYM reference_wrapper<__Arg> const &, __Args...>
    : public __result_of_memfun_ref<_Res _Class::*, __Arg &, __Args...> {};
template<class _Res, class _Class, class __Arg, class... __Args>
struct __result_of_memfun<_Res _Class::*, __NAMESPACE_STD_SYM reference_wrapper<__Arg> &&, __Args...>
    : public __result_of_memfun_ref<_Res _Class::*, __Arg &, __Args...> {};
template<class _Res, class _Class, class __Arg, class... __Args>
struct __result_of_memfun<_Res _Class::*, __NAMESPACE_STD_SYM reference_wrapper<__Arg> const &&, __Args...>
    : public __result_of_memfun_ref<_Res _Class::*, __Arg &, __Args...> {};
template<bool __Sel1, bool __Sel2, class __Function, class... __ArgumentTypes>
struct __result_of_impl { typedef __failure_type type; };
template<class __MemberPointer, class __Arg>
struct __result_of_impl<true, false, __MemberPointer, __Arg>
    : public __result_of_memobj<typename __NAMESPACE_STD_SYM decay<__MemberPointer>::type, __Arg> {};
template<class __MemberPointer, class __Arg, class... __Args>
struct __result_of_impl<false, true, __MemberPointer, __Arg, __Args...>
    : public __result_of_memfun<typename __NAMESPACE_STD_SYM decay<__MemberPointer>::type, __Arg, __Args...> {};
struct __result_of_other_impl {
	template<class _Fn, class... __Args>
	static __result_of_success<decltype(
	                           __NAMESPACE_STD_SYM declval<_Fn>()(__NAMESPACE_STD_SYM declval<__Args>()...)),
	                           __invoke_other>
	__test(int);
	template<class... __Types> static __failure_type __test(...);
};
template<class __Function, class... __ArgumentTypes>
struct __result_of_impl<false, false, __Function, __ArgumentTypes...>
    : private __result_of_other_impl {
	typedef decltype(__test<__Function, __ArgumentTypes...>(0)) type;
};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
#define __std_result_of_defined
template<class __Signature> struct result_of;
template<class __Function, class... __ArgumentTypes>
struct result_of<__Function(__ArgumentTypes...)>
    : public __NAMESPACE_INT_SYM __result_of_impl<
      is_member_object_pointer<typename remove_reference<__Function>::type>::value,
      is_member_function_pointer<typename remove_reference<__Function>::type>::value,
      __Function, __ArgumentTypes...>::type {};
__NAMESPACE_STD_END
__CXXDECL_END
#endif /* ... */
#endif /* !__std_result_of_defined */

#endif /* !_CXX_BITS_RESULT_OF_H */
