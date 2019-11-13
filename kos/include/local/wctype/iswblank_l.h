/* HASH CRC-32:0x7106e3b7 */
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
#ifndef __local_iswblank_l_defined
#define __local_iswblank_l_defined 1
/* Dependency: "iswblank" from "wctype" */
#ifndef ____localdep_iswblank_defined
#define ____localdep_iswblank_defined 1
#ifdef __std___localdep_iswblank_defined
__NAMESPACE_STD_USING(__localdep_iswblank)
#elif __has_builtin(__builtin_iswblank) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswblank)
__FORCELOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_iswblank)(__WINT_TYPE__ __wc) { return __builtin_iswblank(__wc); }
#elif defined(__CRT_HAVE_iswblank)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswblank,(__WINT_TYPE__ __wc),iswblank,(__wc))
#else /* LIBC: iswblank */
#include <local/wctype/iswblank.h>
#define __localdep_iswblank (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswblank))
#endif /* iswblank... */
#endif /* !____localdep_iswblank_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(iswblank_l) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(iswblank_l))(__WINT_TYPE__ __wc,
                                                        __locale_t __locale) {
#line 301 "kos/src/libc/magic/wctype.c"
	(void)__locale;
	__COMPILER_IMPURE();
	return __localdep_iswblank(__wc);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_iswblank_l_defined */
