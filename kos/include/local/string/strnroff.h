/* HASH CRC-32:0x7f9f1a76 */
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
#ifndef __local_strnroff_defined
#define __local_strnroff_defined 1
/* Dependency: "strnrchrnul" from "string" */
#ifndef ____localdep_strnrchrnul_defined
#define ____localdep_strnrchrnul_defined 1
#ifdef __CRT_HAVE_strnrchrnul
/* Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strnrchrnul,(char const *__restrict __haystack, int __needle, __SIZE_TYPE__ __maxlen),strnrchrnul,(__haystack,__needle,__maxlen))
#else /* LIBC: strnrchrnul */
#include <local/string/strnrchrnul.h>
/* Same as `strnrchr', but return `STR - 1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_strnrchrnul (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strnrchrnul))
#endif /* strnrchrnul... */
#endif /* !____localdep_strnrchrnul_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `strnrchrnul', but return the offset from `STR', rather than the actual address */
__LOCAL_LIBC(strnroff) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnroff))(char const *__restrict __haystack,
                                                      int __needle,
                                                      __SIZE_TYPE__ __maxlen) {
#line 2609 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_strnrchrnul(__haystack, __needle, __maxlen) - __haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strnroff_defined */
