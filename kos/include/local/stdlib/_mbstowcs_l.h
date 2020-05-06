/* HASH CRC-32:0x3d405e28 */
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
#ifndef __local__mbstowcs_l_defined
#define __local__mbstowcs_l_defined 1
#include <__crt.h>
/* Dependency: "mbstowcs" from "stdlib" */
#ifndef ____localdep_mbstowcs_defined
#define ____localdep_mbstowcs_defined 1
#ifdef __CRT_HAVE_mbstowcs
__CREDIRECT(,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbstowcs,(__WCHAR_TYPE__ *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dstlen),mbstowcs,(__dst,__src,__dstlen))
#else /* LIBC: mbstowcs */
#include <local/stdlib/mbstowcs.h>
#define __localdep_mbstowcs (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbstowcs))
#endif /* mbstowcs... */
#endif /* !____localdep_mbstowcs_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mbstowcs_l) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbstowcs_l))(__WCHAR_TYPE__ *__dst,
                                                         char const *__src,
                                                         __SIZE_TYPE__ __dstlen,
                                                         __locale_t __locale) {
#line 2595 "kos/src/libc/magic/stdlib.c"
	(void)__locale;
	return __localdep_mbstowcs(__dst, __src, __dstlen);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__mbstowcs_l_defined */
