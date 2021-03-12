/* HASH CRC-32:0x3d4065a5 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32snend_defined
#define __local_c32snend_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `str+wcsnlen(str, max_chars)' */
__LOCAL_LIBC(c32snend) __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32snend))(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen) {
	for (; __maxlen && *__str; ++__str, --__maxlen)
		;
	return (__CHAR32_TYPE__ *)__str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32snend_defined
#define __local___localdep_c32snend_defined 1
#define __localdep_c32snend __LIBC_LOCAL_NAME(c32snend)
#endif /* !__local___localdep_c32snend_defined */
#endif /* !__local_c32snend_defined */
