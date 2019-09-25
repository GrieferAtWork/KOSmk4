/* HASH CRC-32:0x22c98b55 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wcsncoll_defined
#define __local_wcsncoll_defined 1
/* Dependency: "wcsncmp" from "wchar" */
#ifndef ____localdep_wcsncmp_defined
#define ____localdep_wcsncmp_defined 1
#ifdef __std___localdep_wcsncmp_defined
__NAMESPACE_STD_USING(__localdep_wcsncmp)
#elif defined(__CRT_HAVE_wcsncmp)
/* Same as `wcscmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcsncmp,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#else /* LIBC: wcsncmp */
#include <local/wchar/wcsncmp.h>
/* Same as `wcscmp', but compare at most `MAXLEN' characters from either string */
#define __localdep_wcsncmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))
#endif /* wcsncmp... */
#endif /* !____localdep_wcsncmp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcsncoll) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsncoll))(__WCHAR_TYPE__ const *__s1,
                                                      __WCHAR_TYPE__ const *__s2,
                                                      __SIZE_TYPE__ __maxlen) {
#line 4028 "kos/src/libc/magic/string.c"
	return __localdep_wcsncmp(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcsncoll_defined */
