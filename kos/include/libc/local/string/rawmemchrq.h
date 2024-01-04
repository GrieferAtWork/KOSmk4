/* HASH CRC-32:0x14f498ad */
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
#ifndef __local_rawmemchrq_defined
#define __local_rawmemchrq_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(rawmemchrq) __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemchrq))(void const *__restrict __haystack, __UINT64_TYPE__ __needle) {
	__UINT64_TYPE__ *__iter = (__UINT64_TYPE__ *)__haystack;
	for (;; ++__iter) {
		if __unlikely(*__iter == __needle)
			break;
	}
	return __iter;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_rawmemchrq_defined
#define __local___localdep_rawmemchrq_defined
#define __localdep_rawmemchrq __LIBC_LOCAL_NAME(rawmemchrq)
#endif /* !__local___localdep_rawmemchrq_defined */
#endif /* !__local_rawmemchrq_defined */
