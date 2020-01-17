/* HASH CRC-32:0x43931498 */
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
#ifndef __local_iswpunct_defined
#define __local_iswpunct_defined 1
/* Dependency: "ispunct" from "ctype" */
#ifndef ____localdep_ispunct_defined
#define ____localdep_ispunct_defined 1
#if __has_builtin(__builtin_ispunct) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ispunct)
__EXTERNINLINE __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_ispunct)(int __ch) { return __builtin_ispunct(__ch); }
#elif defined(__CRT_HAVE_ispunct)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_ispunct,(int __ch),ispunct,(__ch))
#else /* LIBC: ispunct */
#include <local/ctype/ispunct.h>
#define __localdep_ispunct (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ispunct))
#endif /* ispunct... */
#endif /* !____localdep_ispunct_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(iswpunct) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(iswpunct))(__WINT_TYPE__ __wc) {
#line 148 "kos/src/libc/magic/wctype.c"
	return __localdep_ispunct((int)__wc);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_iswpunct_defined */
