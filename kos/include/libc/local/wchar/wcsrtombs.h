/* HASH CRC-32:0xc12e8230 */
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
#ifndef __local_wcsrtombs_defined
#define __local_wcsrtombs_defined
#include <__crt.h>
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcsnrtombs_defined
#define __local___localdep_wcsnrtombs_defined
#ifdef __CRT_HAVE_wcsnrtombs
__CREDIRECT(__ATTR_ACCESS_RW(2) __ATTR_ACCESS_RW_OPT(5) __ATTR_ACCESS_WR_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnrtombs,(char *__dst, __WCHAR_TYPE__ const **__restrict __psrc, __SIZE_TYPE__ __nwc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),wcsnrtombs,(__dst,__psrc,__nwc,__dstlen,__mbs))
#else /* __CRT_HAVE_wcsnrtombs */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnrtombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcsnrtombs __LIBC_LOCAL_NAME(wcsnrtombs)
#endif /* !__CRT_HAVE_wcsnrtombs */
#endif /* !__local___localdep_wcsnrtombs_defined */
__LOCAL_LIBC(wcsrtombs) __ATTR_ACCESS_RW(2) __ATTR_ACCESS_RW_OPT(4) __ATTR_ACCESS_WR_OPT(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsrtombs))(char *__dst, __WCHAR_TYPE__ const **__restrict __psrc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) {
	return (__NAMESPACE_LOCAL_SYM __localdep_wcsnrtombs)(__dst, __psrc, (__SIZE_TYPE__)-1, __dstlen, __mbs);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcsrtombs_defined
#define __local___localdep_wcsrtombs_defined
#define __localdep_wcsrtombs __LIBC_LOCAL_NAME(wcsrtombs)
#endif /* !__local___localdep_wcsrtombs_defined */
#endif /* !__local_wcsrtombs_defined */
