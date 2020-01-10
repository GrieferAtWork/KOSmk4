/* HASH CRC-32:0x1459fa4b */
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
#ifndef __local__mbtowc_l_defined
#define __local__mbtowc_l_defined 1
/* Dependency: "mbtowc" from "stdlib" */
#ifndef ____localdep_mbtowc_defined
#define ____localdep_mbtowc_defined 1
#ifdef __CRT_HAVE_mbtowc
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_mbtowc,(__WCHAR_TYPE__ *__restrict __pwc, char const *__restrict __str, __SIZE_TYPE__ __maxlen),mbtowc,(__pwc,__str,__maxlen))
#else /* LIBC: mbtowc */
#include <local/stdlib/mbtowc.h>
#define __localdep_mbtowc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbtowc))
#endif /* mbtowc... */
#endif /* !____localdep_mbtowc_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mbtowc_l) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbtowc_l))(__WCHAR_TYPE__ *__dst,
                                                       char const *__src,
                                                       __SIZE_TYPE__ __srclen,
                                                       __locale_t __locale) {
#line 2425 "kos/src/libc/magic/stdlib.c"
	(void)__locale;
	return __localdep_mbtowc(__dst, __src, __srclen);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__mbtowc_l_defined */
