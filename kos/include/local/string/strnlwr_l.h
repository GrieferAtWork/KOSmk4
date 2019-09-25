/* HASH CRC-32:0x80f373b3 */
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
#ifndef __local_strnlwr_l_defined
#define __local_strnlwr_l_defined 1
/* Dependency: "tolower_l" from "ctype" */
#ifndef ____localdep_tolower_l_defined
#define ____localdep_tolower_l_defined 1
#if defined(__CRT_HAVE_tolower_l)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),tolower_l,(__ch,__locale))
#else /* LIBC: tolower_l */
#include <local/ctype/tolower_l.h>
#define __localdep_tolower_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower_l))
#endif /* tolower_l... */
#endif /* !____localdep_tolower_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strnlwr_l) __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnlwr_l))(char *__restrict __str,
                                                       __SIZE_TYPE__ __maxlen,
                                                       __locale_t __locale) {
#line 4102 "kos/src/libc/magic/string.c"
	char *__iter, __ch;
	for (__iter = __str; __maxlen-- && (__ch = *__iter) != '\0'; ++__iter)
		*__iter = __localdep_tolower_l(__ch, __locale);
	return __str;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strnlwr_l_defined */
