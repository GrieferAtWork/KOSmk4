/* HASH CRC-32:0x76863080 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strpbrk_defined
#define __local_strpbrk_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__LOCAL_LIBC(strpbrk) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strpbrk))(char const *__haystack, char const *__accept) {
	char __haych, __ch;
	while ((__haych = *__haystack++) != '\0') {
		char const *__ned_iter;
		__ned_iter = __accept;
		while ((__ch = *__ned_iter++) != '\0') {
			if (__haych == __ch)
				return (char *)__haystack - 1;
		}
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strpbrk_defined
#define __local___localdep_strpbrk_defined 1
#define __localdep_strpbrk __LIBC_LOCAL_NAME(strpbrk)
#endif /* !__local___localdep_strpbrk_defined */
#endif /* !__local_strpbrk_defined */
