/* HASH CRC-32:0xe7b146ae */
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
#ifndef __local_wcsstr_defined
#define __local_wcsstr_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__LOCAL_LIBC(wcsstr) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsstr))(__WCHAR_TYPE__ const *__haystack, __WCHAR_TYPE__ const *__needle) {
	__WCHAR_TYPE__ __ch, __needle_start = *__needle++;
	while ((__ch = *__haystack++) != '\0') {
		if (__ch == __needle_start) {
			__WCHAR_TYPE__ const *__hay2, *__ned_iter;
			__hay2     = __haystack;
			__ned_iter = __needle;
			while ((__ch = *__ned_iter++) != '\0') {
				if (*__hay2++ != __ch)
					goto __miss;
			}
			return (__WCHAR_TYPE__ *)__haystack - 1;
		}
__miss:
		;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcsstr_defined
#define __local___localdep_wcsstr_defined 1
#define __localdep_wcsstr __LIBC_LOCAL_NAME(wcsstr)
#endif /* !__local___localdep_wcsstr_defined */
#endif /* !__local_wcsstr_defined */
