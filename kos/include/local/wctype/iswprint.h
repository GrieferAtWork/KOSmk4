/* HASH CRC-32:0xce948103 */
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
#ifndef __local_iswprint_defined
#define __local_iswprint_defined 1
/* Dependency: "isprint" from "ctype" */
#ifndef ____localdep_isprint_defined
#define ____localdep_isprint_defined 1
#if __has_builtin(__builtin_isprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isprint)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isprint)(int __ch) { return __builtin_isprint(__ch); }
#elif defined(__CRT_HAVE_isprint)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isprint,(int __ch),isprint,(__ch))
#else /* LIBC: isprint */
#include <local/ctype/isprint.h>
#define __localdep_isprint (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprint))
#endif /* isprint... */
#endif /* !____localdep_isprint_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(iswprint) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(iswprint))(__WINT_TYPE__ __wc) {
#line 143 "kos/src/libc/magic/wctype.c"
	return __localdep_isprint((int)__wc);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_iswprint_defined */
