/* HASH CRC-32:0x74e42977 */
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
#ifndef __local_c16rchr_defined
#define __local_c16rchr_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16rchr) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16rchr))(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle) {
	__CHAR16_TYPE__ const *__result = __NULLPTR;
	for (;; ++__haystack) {
		__CHAR16_TYPE__ __ch = *__haystack;
		if __unlikely((__CHAR16_TYPE__)__ch == (__CHAR16_TYPE__)__needle)
			__result = __haystack;
		if (!__ch)
			break;
	}
	return (__CHAR16_TYPE__ *)__result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16rchr_defined
#define __local___localdep_c16rchr_defined
#define __localdep_c16rchr __LIBC_LOCAL_NAME(c16rchr)
#endif /* !__local___localdep_c16rchr_defined */
#endif /* !__local_c16rchr_defined */