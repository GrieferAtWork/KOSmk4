/* HASH CRC-32:0x7debdb14 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strrstr_defined
#define __local_strrstr_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strrstr) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strrstr))(char const *__haystack, char const *__needle) {
	char *__result = __NULLPTR;
	char __ch, __needle_start = *__needle++;
	while ((__ch = *__haystack++) != '\0') {
		if (__ch == __needle_start) {
			char const *__hay2, *__ned_iter;
			__hay2     = __haystack;
			__ned_iter = __needle;
			while ((__ch = *__ned_iter++) != '\0') {
				if (*__hay2++ != __ch)
					goto __miss;
			}
			__result = (char *)__haystack - 1;
		}
__miss:
		;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strrstr_defined
#define __local___localdep_strrstr_defined
#define __localdep_strrstr __LIBC_LOCAL_NAME(strrstr)
#endif /* !__local___localdep_strrstr_defined */
#endif /* !__local_strrstr_defined */
