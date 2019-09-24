/* HASH CRC-32:0x5e90fab8 */
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
#ifndef __local_wcsftime_l_defined
#define __local_wcsftime_l_defined 1
/* Dependency: "wcsftime" from "wchar" */
#ifndef ____localdep_wcsftime_defined
#define ____localdep_wcsftime_defined 1
#ifdef __std___localdep_wcsftime_defined
__NAMESPACE_STD_USING(__localdep_wcsftime)
#elif defined(__CRT_HAVE_wcsftime)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsftime,(__WCHAR_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __WCHAR_TYPE__ const *__restrict __format, struct tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#else /* LIBC: wcsftime */
#include <local/wchar/wcsftime.h>
#define __localdep_wcsftime (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime))
#endif /* wcsftime... */
#endif /* !____localdep_wcsftime_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcsftime_l) __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsftime_l))(__WCHAR_TYPE__ *__restrict __buf,
                                                        __SIZE_TYPE__ __maxsize,
                                                        __WCHAR_TYPE__ const *__restrict __format,
                                                        struct tm const *__restrict __tp,
                                                        __locale_t __locale) {
#line 982 "kos/src/libc/magic/wchar.c"
	(void)__locale;
	return __localdep_wcsftime(__buf, __maxsize, __format, __tp);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcsftime_l_defined */
