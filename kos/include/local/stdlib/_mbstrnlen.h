/* HASH CRC-32:0xe7ff1655 */
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
#ifndef __local__mbstrnlen_defined
#define __local__mbstrnlen_defined 1
#include <__crt.h>
/* Dependency: "unicode_readutf8_n" from "unicode" */
#ifndef ____localdep_unicode_readutf8_n_defined
#define ____localdep_unicode_readutf8_n_defined 1
#ifdef __CRT_HAVE_unicode_readutf8_n
/* Same as `unicode_readutf8()', but don't read past `text_end' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__CHAR32_TYPE__,__NOTHROW_NCX,__localdep_unicode_readutf8_n,(/*utf-8*/ char const **__restrict __ptext, char const *__text_end),unicode_readutf8_n,(__ptext,__text_end))
#else /* LIBC: unicode_readutf8_n */
#include <local/unicode/unicode_readutf8_n.h>
/* Same as `unicode_readutf8()', but don't read past `text_end' */
#define __localdep_unicode_readutf8_n (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(unicode_readutf8_n))
#endif /* unicode_readutf8_n... */
#endif /* !____localdep_unicode_readutf8_n_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mbstrnlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbstrnlen))(char const *__str,
                                                        __SIZE_TYPE__ __maxlen) {
#line 2627 "kos/src/libc/magic/stdlib.c"
	__SIZE_TYPE__ __result = 0;
	char const *__endptr = __str + __maxlen;
	while (__localdep_unicode_readutf8_n((char const **)&__str, __endptr))
		++__result;
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__mbstrnlen_defined */
