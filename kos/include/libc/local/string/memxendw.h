/* HASH CRC-32:0x6e6e85a */
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
#ifndef __local_memxendw_defined
#define __local_memxendw_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memxendw) __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memxendw))(void const *__restrict __haystack, __UINT16_TYPE__ __needle, __SIZE_TYPE__ __n_words) {
	__UINT16_TYPE__ *__result = (__UINT16_TYPE__ *)__haystack;
	for (; __n_words--; ++__result) {
		if __unlikely(*__result != __needle)
			break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memxendw_defined
#define __local___localdep_memxendw_defined
#define __localdep_memxendw __LIBC_LOCAL_NAME(memxendw)
#endif /* !__local___localdep_memxendw_defined */
#endif /* !__local_memxendw_defined */
