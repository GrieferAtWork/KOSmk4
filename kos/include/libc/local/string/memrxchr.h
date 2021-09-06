/* HASH CRC-32:0xe68e3405 */
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
#ifndef __local_memrxchr_defined
#define __local_memrxchr_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memrxchr) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrxchr))(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes) {
	__BYTE_TYPE__ *__iter = (__BYTE_TYPE__ *)__haystack + __n_bytes;
	while (__n_bytes--) {
		if __unlikely(*--__iter != (__BYTE_TYPE__)__needle)
			return __iter;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memrxchr_defined
#define __local___localdep_memrxchr_defined 1
#define __localdep_memrxchr __LIBC_LOCAL_NAME(memrxchr)
#endif /* !__local___localdep_memrxchr_defined */
#endif /* !__local_memrxchr_defined */
