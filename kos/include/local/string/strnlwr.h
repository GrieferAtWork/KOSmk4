/* HASH CRC-32:0x24fe9673 */
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
#ifndef __local_strnlwr_defined
#define __local_strnlwr_defined 1
/* Dependency: "tolower" from "ctype" */
#ifndef ____localdep_tolower_defined
#define ____localdep_tolower_defined 1
#if __has_builtin(__builtin_tolower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tolower)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_tolower)(int __ch) { return __builtin_tolower(__ch); }
#elif defined(__CRT_HAVE_tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,(__ch))
#elif defined(__CRT_HAVE__tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),_tolower,(__ch))
#else /* LIBC: tolower */
#include <local/ctype/tolower.h>
#define __localdep_tolower (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower))
#endif /* tolower... */
#endif /* !____localdep_tolower_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strnlwr) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnlwr))(char *__restrict __str,
                                                     __SIZE_TYPE__ __maxlen) {
#line 4648 "kos/src/libc/magic/string.c"
	char *__iter, __ch;
	for (__iter = __str; __maxlen-- && (__ch = *__iter) != '\0'; ++__iter)
		*__iter = __localdep_tolower(__ch);
	return __str;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strnlwr_defined */
