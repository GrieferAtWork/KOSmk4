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
#ifndef _CXX_BITS___IS_ARRAY_BOUNDS_H
#define _CXX_BITS___IS_ARRAY_BOUNDS_H 1

#include <__stdcxx.h>

#include "andor.h"
#include "extent.h"
#include "integral_constant.h"
#include "is_array.h"

__CXXDECL_BEGIN
__NAMESPACE_INT_BEGIN

template<class __T> struct __is_array_known_bounds
    : public __NAMESPACE_STD_SYM integral_constant<bool, (__NAMESPACE_STD_SYM extent<__T>::value > 0)> {};
template<class __T> struct __is_array_unknown_bounds
    : public __and_<__NAMESPACE_STD_SYM is_array<__T>,
                    __not_<__NAMESPACE_STD_SYM extent<__T> > > {};

__NAMESPACE_INT_END
__CXXDECL_END

#endif /* !_CXX_BITS___IS_ARRAY_BOUNDS_H */
