/* HASH CRC-32:0xb5795197 */
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
#ifndef __local_strnstr_defined
#define __local_strnstr_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strnstr) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INS(1, 3) __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnstr))(char const *__haystack, char const *__needle, __SIZE_TYPE__ __haystack_maxlen) {
	char __ch, __needle_start = *__needle++;
	while (__haystack_maxlen-- && (__ch = *__haystack++) != '\0') {
		if (__ch == __needle_start) {
			char const *__hay2, *__ned_iter;
			__SIZE_TYPE__ __maxlen2;
			__hay2     = __haystack;
			__ned_iter = __needle;
			__maxlen2  = __haystack_maxlen;
			while ((__ch = *__ned_iter++) != '\0') {
				if (!__maxlen2-- || *__hay2++ != __ch)
					goto __miss;
			}
			return (char *)__haystack - 1;
		}
__miss:
		;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strnstr_defined
#define __local___localdep_strnstr_defined
#define __localdep_strnstr __LIBC_LOCAL_NAME(strnstr)
#endif /* !__local___localdep_strnstr_defined */
#endif /* !__local_strnstr_defined */
