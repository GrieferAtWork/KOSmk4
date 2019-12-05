/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CXX___ADDRESSOF_H
#define _BITS_CXX___ADDRESSOF_H 1

#include <__crt.h>
#include <__stdcxx.h>

__CXXDECL_BEGIN
__NAMESPACE_INT_BEGIN
template<class __T> __CXX_FORCEINLINE __ATTR_CONST __T *__LIBCCALL
__addressof(__T &__obj) __CXX_NOEXCEPT {
	return reinterpret_cast<__T *>(&const_cast<char &>(reinterpret_cast<const volatile char &>(__obj)));
}
__NAMESPACE_INT_END
__CXXDECL_END

#endif /* !_BITS_CXX___ADDRESSOF_H */
