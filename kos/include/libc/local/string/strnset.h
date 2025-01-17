/* HASH CRC-32:0x372e4655 */
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
#ifndef __local_strnset_defined
#define __local_strnset_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strnset) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnset))(char *__restrict __str, int __ch, __SIZE_TYPE__ __maxlen) {
	char *__iter;
	for (__iter = __str; __maxlen-- && *__iter; ++__iter)
		*__iter = (char)__ch;
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strnset_defined
#define __local___localdep_strnset_defined
#define __localdep_strnset __LIBC_LOCAL_NAME(strnset)
#endif /* !__local___localdep_strnset_defined */
#endif /* !__local_strnset_defined */
