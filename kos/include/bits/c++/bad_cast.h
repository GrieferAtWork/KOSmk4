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
#ifndef _BITS_CXX_BAD_CAST_H
#define _BITS_CXX_BAD_CAST_H 1

#include <__stdcxx.h>

#include "exception.h"

__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN

class bad_cast: public exception {
public:
	__LIBCCALL bad_cast() __CXX_NOEXCEPT {}
	virtual __LIBCCALL ~bad_cast() __CXX_NOEXCEPT;
	virtual char const *__LIBCCALL what() const __CXX_NOEXCEPT;
};

__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_BITS_CXX_BAD_CAST_H */
