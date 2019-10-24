/* HASH CRC-32:0x2a842529 */
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
#ifndef __local_strxfrm_l_defined
#if 1
#define __local_strxfrm_l_defined 1
/* Dependency: "strxfrm" from "string" */
#ifndef ____localdep_strxfrm_defined
#define ____localdep_strxfrm_defined 1
#if defined(__CRT_HAVE_strxfrm)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strxfrm,(char *__dst, char const *__restrict __src, __SIZE_TYPE__ __maxlen),strxfrm,(__dst,__src,__maxlen))
#else /* LIBC: strxfrm */
#include <local/string/strxfrm.h>
#define __localdep_strxfrm (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strxfrm))
#endif /* strxfrm... */
#endif /* !____localdep_strxfrm_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strxfrm_l) __ATTR_NONNULL((2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strxfrm_l))(char *__dst,
                                                       char const *__restrict __src,
                                                       __SIZE_TYPE__ __maxlen,
                                                       __locale_t __locale) {
#line 438 "kos/src/libc/magic/string.c"
	(void)__locale;
	return __localdep_strxfrm(__dst, __src, __maxlen);
}
__NAMESPACE_LOCAL_END
#endif /* 1 */
#endif /* !__local_strxfrm_l_defined */
