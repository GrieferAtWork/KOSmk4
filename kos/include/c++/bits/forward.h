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
#ifndef _CXX_BITS_FORWARD_H
#define _CXX_BITS_FORWARD_H 1

#include <__stdcxx.h>

#include "__addressof.h"
#include "traits/remove_reference.h"

__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN

#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
template<class __T> __CXX_CLASSMEMBER __CXX14_CONSTEXPR __T &&
forward(typename remove_reference<__T>::type &__t) __CXX_NOEXCEPT {
	return *(__T *)__NAMESPACE_INT_SYM __addressof(__t);
}
template<class __T> __CXX_CLASSMEMBER __CXX14_CONSTEXPR __T &&
forward(typename remove_reference<__T>::type &&__t) __CXX_NOEXCEPT {
	return *(__T *)__NAMESPACE_INT_SYM __addressof(__t);
}
#endif /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */


__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_FORWARD_H */
