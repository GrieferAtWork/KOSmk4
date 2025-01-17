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
#ifndef _CXX_BITS_ANDOR_H
#define _CXX_BITS_ANDOR_H 1

#include <__stdcxx.h>

#include <c++/bits/varargs-template.h>

#include "conditional.h"
#include "integral_constant.h"

__CXXDECL_BEGIN
__NAMESPACE_INT_BEGIN
template<__CXX_VARARGS_TEMPLATE_ARGS_DEF(class, __Conditions, void)> struct __or_;
template<__CXX_VARARGS_TEMPLATE_ARGS_DEF(class, __Conditions, void)> struct __and_;
template<> struct __or_<>: public __NAMESPACE_STD_SYM false_type {};
template<> struct __and_<>: public __NAMESPACE_STD_SYM true_type {};
template<class __C1> struct __or_<__C1>: public __C1 {};
template<class __C1> struct __and_<__C1>: public __C1 {};
template<class __C1, class __C2> struct __or_<__C1, __C2>
    : public __NAMESPACE_STD_SYM conditional<__C1::value, __C1, __C2>::type {};
template<class __C1, class __C2> struct __and_<__C1, __C2>
    : public __NAMESPACE_STD_SYM conditional<__C1::value, __C2, __C1>::type {};
template<class __C1, class __C2, class __C3, __CXX_VARARGS_TEMPLATE_ARGS(class, __CN)>
struct __or_<__C1, __C2, __C3, __CXX_VARARGS_TYPENAME_ARGS(__CN)>
    : public __NAMESPACE_STD_SYM conditional<__C1::value, __C1, __or_<__C2, __C3, __CXX_VARARGS_TYPENAME_ARGS(__CN)> >::type {};
template<class __C1, class __C2, class __C3, __CXX_VARARGS_TEMPLATE_ARGS(class, __CN)>
struct __and_<__C1, __C2, __C3, __CXX_VARARGS_TYPENAME_ARGS(__CN)>
    : public __NAMESPACE_STD_SYM conditional<__C1::value, __and_<__C2, __C3, __CXX_VARARGS_TYPENAME_ARGS(__CN)>, __C1>::type {};
template<class __C> struct __not_
    : public __NAMESPACE_STD_SYM integral_constant<bool, !(bool)__C::value> {};
__NAMESPACE_INT_END
__CXXDECL_END

#endif /* !_CXX_BITS_ANDOR_H */
