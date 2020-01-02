/* HASH CRC-32:0x599a31ea */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16ncoll_defined
#define __local_c16ncoll_defined 1
/* Dependency: "wcsncmp" from "wchar" */
#ifndef ____localdep_c16ncmp_defined
#define ____localdep_c16ncmp_defined 1
#if defined(__CRT_HAVE_wcsncmp) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16cmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16ncmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsncmp)
/* Same as `c16cmp', but compare at most `MAXLEN' characters from either string */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16ncmp,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __SIZE_TYPE__ __maxlen),wcsncmp,(__s1,__s2,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsncmp.h>
/* Same as `c16cmp', but compare at most `MAXLEN' characters from either string */
#define __localdep_c16ncmp(s1, s2, maxlen) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))((__WCHAR_TYPE__ const *)(s1), (__WCHAR_TYPE__ const *)(s2), maxlen)
#else /* LIBC: c16ncmp */
#include <local/wchar/c16ncmp.h>
/* Same as `c16cmp', but compare at most `MAXLEN' characters from either string */
#define __localdep_c16ncmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ncmp))
#endif /* c16ncmp... */
#endif /* !____localdep_c16ncmp_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16ncoll) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16ncoll))(__CHAR16_TYPE__ const *__s1,
                                                      __CHAR16_TYPE__ const *__s2,
                                                      __SIZE_TYPE__ __maxlen) {
#line 4626 "kos/src/libc/magic/string.c"
	return __localdep_c16ncmp(__s1, __s2, __maxlen);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16ncoll_defined */
