/* HASH CRC-32:0x244474c6 */
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
#ifndef __local_mbstowcs_defined
#define __local_mbstowcs_defined 1
#include <__crt.h>
/* Dependency: "mbsrtowcs" from "wchar" */
#ifndef ____localdep_mbsrtowcs_defined
#define ____localdep_mbsrtowcs_defined 1
#ifdef __CRT_HAVE_mbsrtowcs
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsrtowcs,(__WCHAR_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, __mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#else /* LIBC: mbsrtowcs */
#include <local/wchar/mbsrtowcs.h>
#define __localdep_mbsrtowcs (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsrtowcs))
#endif /* mbsrtowcs... */
#endif /* !____localdep_mbsrtowcs_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(mbstowcs) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mbstowcs))(__WCHAR_TYPE__ *__restrict __dst,
                                                      char const *__restrict __src,
                                                      __SIZE_TYPE__ __dstlen) {
#line 713 "kos/src/libc/magic/stdlib.c"
	return __localdep_mbsrtowcs(__dst, (char const **)&__src, __dstlen, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mbstowcs_defined */
