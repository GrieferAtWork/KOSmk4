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
#ifndef _CXX_BITS_DECAY_H
#define _CXX_BITS_DECAY_H 1

#include <__stdcxx.h>

#include "add_pointer.h"
#include "integral_constant.h"
#include "is_array.h"
#include "is_function.h"
#include "remove_cv.h"
#include "remove_extent.h"

__CXXDECL_BEGIN
__NAMESPACE_INT_BEGIN
template<class __T, bool __IsArray, bool __IsFunction> struct __decay_selector;
template<class __T> struct __decay_selector<__T, false, false> {
	typedef typename __NAMESPACE_STD_SYM remove_cv<__T>::type __type;
};
template<class __T> struct __decay_selector<__T, true, false> {
	typedef typename __NAMESPACE_STD_SYM remove_extent<__T>::type *__type;
};
template<class __T> struct __decay_selector<__T, false, true> {
	typedef typename __NAMESPACE_STD_SYM add_pointer<__T>::type __type;
};
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct decay {
private:
	typedef typename remove_reference<__T>::type __noref_type;
public:
	typedef typename __NAMESPACE_INT_SYM __decay_selector<__noref_type,
	                                                      is_array<__noref_type>::value,
	                                                      is_function<__noref_type>::value>::__type type;
};
#ifndef __std_reference_wrapper_defined
#define __std_reference_wrapper_defined
template<class __T> class reference_wrapper;
#endif /* !__std_reference_wrapper_defined */
__NAMESPACE_STD_END
__NAMESPACE_INT_BEGIN
template<class __T> struct __strip_reference_wrapper {
	typedef __T __type;
};
template<class __T> struct __strip_reference_wrapper<__NAMESPACE_STD_SYM reference_wrapper<__T> > {
	typedef __T &__type;
};
template<class __T> struct __decay_and_strip {
	typedef typename __strip_reference_wrapper<typename __NAMESPACE_STD_SYM decay<__T>::type>::__type __type;
};
__NAMESPACE_INT_END
__CXXDECL_END

#endif /* !_CXX_BITS_DECAY_H */
