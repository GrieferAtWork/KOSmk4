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
#ifndef _CXX_BITS_IS_REFERENCE_H
#define _CXX_BITS_IS_REFERENCE_H 1

#include <__stdcxx.h>

#include "andor.h"
#include "integral_constant.h"
#include "remove_cv.h"

__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN

template<class __T> struct is_lvalue_reference: public false_type {};
template<class __T> struct is_lvalue_reference<__T &>: public true_type {};
template<class __T> struct is_rvalue_reference: public false_type {};
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
template<class __T> struct is_rvalue_reference<__T &&>: public true_type {};
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
template<class __T> struct is_reference
    : public __NAMESPACE_INT_SYM __or_<is_lvalue_reference<__T>,
                                       is_rvalue_reference<__T> >::type {};

__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_IS_REFERENCE_H */
