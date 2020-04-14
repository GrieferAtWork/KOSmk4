/* HASH CRC-32:0x53878ce5 */
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
#ifndef __local_strupr_l_defined
#define __local_strupr_l_defined 1
/* Dependency: "toupper_l" from "ctype" */
#ifndef ____localdep_toupper_l_defined
#define ____localdep_toupper_l_defined 1
#ifdef __CRT_HAVE_toupper_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_toupper_l,(int __ch, __locale_t __locale),toupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE__toupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_toupper_l,(int __ch, __locale_t __locale),_toupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE___toupper_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_toupper_l,(int __ch, __locale_t __locale),__toupper_l,(__ch,__locale))
#else /* LIBC: toupper_l */
#include <local/ctype/toupper_l.h>
#define __localdep_toupper_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toupper_l))
#endif /* toupper_l... */
#endif /* !____localdep_toupper_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strupr_l) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strupr_l))(char *__restrict __str,
                                                      __locale_t __locale) {
#line 4789 "kos/src/libc/magic/string.c"
	char *__iter, __ch;
	for (__iter = __str; (__ch = *__iter) != '\0'; ++__iter)
		*__iter = __localdep_toupper_l(__ch, __locale);
	return __str;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strupr_l_defined */
