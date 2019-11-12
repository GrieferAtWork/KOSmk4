/* HASH CRC-32:0xea5b4b3d */
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
#ifndef __local_c32ncasecoll_defined
#define __local_c32ncasecoll_defined 1
/* Dependency: "wcsncasecmp" from "wchar" */
#ifndef ____localdep_c32ncasecmp_defined
#define ____localdep_c32ncasecmp_defined 1
#if defined(__CRT_HAVE_wcsncasecmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32ncasecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32ncasecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c32ncasecmp,(__CHAR32_TYPE__ const *__s1, __CHAR32_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsncasecmp.h>
#define __localdep_c32ncasecmp(s1, s2, maxlen) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))((__WCHAR_TYPE__ const *)(s1), (__WCHAR_TYPE__ const *)(s2), maxlen)
#else /* LIBC: c32ncasecmp */
#include <local/wchar/c32ncasecmp.h>
#define __localdep_c32ncasecmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ncasecmp))
#endif /* c32ncasecmp... */
#endif /* !____localdep_c32ncasecmp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32ncasecoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32ncasecoll))(__CHAR32_TYPE__ const *__s1,
                                                          __CHAR32_TYPE__ const *__s2,
                                                          __SIZE_TYPE__ __maxlen) {
#line 4225 "kos/src/libc/magic/string.c"
	return __localdep_c32ncasecmp(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32ncasecoll_defined */
