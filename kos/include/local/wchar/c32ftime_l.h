/* HASH CRC-32:0xc54bd09 */
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
#ifndef __local_c32ftime_l_defined
#define __local_c32ftime_l_defined 1
/* Dependency: "wcsftime" from "wchar" */
#ifndef ____localdep_c32ftime_defined
#define ____localdep_c32ftime_defined 1
#if defined(__CRT_HAVE_wcsftime) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32ftime,(__CHAR32_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __CHAR32_TYPE__ const *__restrict __format, struct tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsftime.h>
#define __localdep_c32ftime(buf, buflen, format, tp) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime))((__WCHAR_TYPE__ *)(buf), buflen, (__WCHAR_TYPE__ const *)(format), tp)
#else /* LIBC: c32ftime */
#include <local/wchar/c32ftime.h>
#define __localdep_c32ftime (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ftime))
#endif /* c32ftime... */
#endif /* !____localdep_c32ftime_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32ftime_l) __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32ftime_l))(__CHAR32_TYPE__ *__restrict __buf,
                                                        __SIZE_TYPE__ __maxsize,
                                                        __CHAR32_TYPE__ const *__restrict __format,
                                                        struct tm const *__restrict __tp,
                                                        __locale_t __locale) {
#line 983 "kos/src/libc/magic/wchar.c"
	(void)__locale;
	return __localdep_c32ftime(__buf, __maxsize, __format, __tp);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32ftime_l_defined */
