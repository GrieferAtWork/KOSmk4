/* HASH CRC-32:0xc392a61e */
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
#ifndef __local_strnupr_defined
#define __local_strnupr_defined 1
/* Dependency: "toupper" from "ctype" */
#ifndef ____localdep_toupper_defined
#define ____localdep_toupper_defined 1
#if __has_builtin(__builtin_toupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_toupper)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_toupper)(int __ch) { return __builtin_toupper(__ch); }
#elif defined(__CRT_HAVE_toupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_toupper,(int __ch),toupper,(__ch))
#elif defined(__CRT_HAVE__toupper)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_toupper,(int __ch),_toupper,(__ch))
#else /* LIBC: toupper */
#include <local/ctype/toupper.h>
#define __localdep_toupper (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toupper))
#endif /* toupper... */
#endif /* !____localdep_toupper_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strnupr) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnupr))(char *__restrict __str,
                                                     __SIZE_TYPE__ __maxlen) {
#line 4656 "kos/src/libc/magic/string.c"
	char *__iter, __ch;
	for (__iter = __str; __maxlen-- && (__ch = *__iter) != '\0'; ++__iter)
		*__iter = __localdep_toupper(__ch);
	return __str;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strnupr_defined */
