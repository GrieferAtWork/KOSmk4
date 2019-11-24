/* HASH CRC-32:0x8b0639f8 */
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
#ifndef __local_c32nlen_defined
#define __local_c32nlen_defined 1
/* Dependency: "wcsnend" from "wchar" */
#ifndef ____localdep_c32nend_defined
#define ____localdep_c32nend_defined 1
#if defined(__CRT_HAVE_wcsnend) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32nend,(__CHAR32_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnend.h>
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
#define __localdep_c32nend(string, maxlen) (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)(string), maxlen)
#else /* LIBC: c32nend */
#include <local/wchar/c32nend.h>
/* Same as `STR+c32nlen(STR, MAX_CHARS)' */
#define __localdep_c32nend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nend))
#endif /* c32nend... */
#endif /* !____localdep_c32nend_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `c32len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__LOCAL_LIBC(c32nlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32nlen))(__CHAR32_TYPE__ const *__restrict __string,
                                                     __SIZE_TYPE__ __maxlen) {
#line 452 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_c32nend(__string, __maxlen) - __string);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32nlen_defined */
