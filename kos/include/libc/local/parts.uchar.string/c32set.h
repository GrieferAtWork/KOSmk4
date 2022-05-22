/* HASH CRC-32:0x673918a2 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32set_defined
#define __local_c32set_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32set) __ATTR_LEAF __ATTR_INOUT(1) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32set))(__CHAR32_TYPE__ *__restrict __str, int __ch) {
	__CHAR32_TYPE__ *__iter;
	for (__iter = __str; *__iter; ++__iter)
		*__iter = (__CHAR32_TYPE__)__ch;
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32set_defined
#define __local___localdep_c32set_defined
#define __localdep_c32set __LIBC_LOCAL_NAME(c32set)
#endif /* !__local___localdep_c32set_defined */
#endif /* !__local_c32set_defined */
