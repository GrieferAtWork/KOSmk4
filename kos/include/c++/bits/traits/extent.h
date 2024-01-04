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
#ifndef _CXX_BITS_EXTENT_H
#define _CXX_BITS_EXTENT_H 1

#include <__stdcxx.h>

#include <hybrid/typecore.h>

#include "integral_constant.h"

__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN

template<class __T, unsigned int __Level = 0> struct extent
    : public integral_constant<__SIZE_TYPE__, 0> {};
template<class __T, unsigned int __Level, __SIZE_TYPE__ __Size>
struct extent<__T[__Size], __Level>
    : public integral_constant<__SIZE_TYPE__, __Level == 0 ? __Size : extent<__T, __Level - 1>::value> {};
template<class __T, unsigned int __Level> struct extent<__T[], __Level>
    : public integral_constant<__SIZE_TYPE__, __Level == 0 ? 0 : extent<__T, __Level - 1>::value> {};

__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_EXTENT_H */
