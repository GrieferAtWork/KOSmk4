/* HASH CRC-32:0xc76425da */
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
#ifndef __local_wcstombs_defined
#define __local_wcstombs_defined 1
#include <__crt.h>
/* Dependency: "wcsrtombs" from "wchar" */
#ifndef ____localdep_wcsrtombs_defined
#define ____localdep_wcsrtombs_defined 1
#ifdef __CRT_HAVE_wcsrtombs
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsrtombs,(char *__dst, __WCHAR_TYPE__ const **__restrict __psrc, __SIZE_TYPE__ __dstlen, __mbstate_t *__mbs),wcsrtombs,(__dst,__psrc,__dstlen,__mbs))
#else /* LIBC: wcsrtombs */
#include <local/wchar/wcsrtombs.h>
#define __localdep_wcsrtombs (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrtombs))
#endif /* wcsrtombs... */
#endif /* !____localdep_wcsrtombs_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcstombs) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcstombs))(char *__restrict __dst,
                                                      __WCHAR_TYPE__ const *__restrict __src,
                                                      __SIZE_TYPE__ __dstlen) {
#line 718 "kos/src/libc/magic/stdlib.c"
	return __localdep_wcsrtombs(__dst, (__WCHAR_TYPE__ const **)&__src, __dstlen, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcstombs_defined */
