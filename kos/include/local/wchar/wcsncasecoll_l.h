/* HASH CRC-32:0x585534bc */
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
#ifndef __local_wcsncasecoll_l_defined
#define __local_wcsncasecoll_l_defined 1
/* Dependency: "wcsncasecoll" from "wchar" */
#ifndef ____localdep_wcsncasecoll_defined
#define ____localdep_wcsncasecoll_defined 1
#if defined(__CRT_HAVE_wcsncasecoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcsncasecoll,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcsncasecoll,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcsncasecoll,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcsncasecoll,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcsncasecoll,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* LIBC: wcsncasecoll */
#include <local/wchar/wcsncasecoll.h>
#define __localdep_wcsncasecoll (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))
#endif /* wcsncasecoll... */
#endif /* !____localdep_wcsncasecoll_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcsncasecoll_l) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsncasecoll_l))(__WCHAR_TYPE__ const *__s1,
                                                            __WCHAR_TYPE__ const *__s2,
                                                            __SIZE_TYPE__ __maxlen,
                                                            __locale_t __locale) {
#line 4085 "kos/src/libc/magic/string.c"
	(void)__locale;
	return __localdep_wcsncasecoll(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcsncasecoll_l_defined */
