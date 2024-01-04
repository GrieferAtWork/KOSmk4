/* HASH CRC-32:0xa677956f */
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
#ifndef __local_strchrnul_defined
#define __local_strchrnul_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strchrnul) __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strchrnul))(char const *__restrict __haystack, int __needle) {
	for (; *__haystack; ++__haystack) {
		if ((unsigned char)*__haystack == (unsigned char)__needle)
			break;
	}
	return (char *)__haystack;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strchrnul_defined
#define __local___localdep_strchrnul_defined
#define __localdep_strchrnul __LIBC_LOCAL_NAME(strchrnul)
#endif /* !__local___localdep_strchrnul_defined */
#endif /* !__local_strchrnul_defined */
