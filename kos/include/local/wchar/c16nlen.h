/* HASH CRC-32:0xfc55f0c2 */
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
#ifndef __local_c16nlen_defined
#define __local_c16nlen_defined 1
/* Dependency: "wcsnend" from "wchar" */
#ifndef ____localdep_c16nend_defined
#define ____localdep_c16nend_defined 1
#if defined(__CRT_HAVE_wcsnend) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16nend,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnend)
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16nend,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnend.h>
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
#define __localdep_c16nend(string, maxlen) (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))((__WCHAR_TYPE__ const *)(string), maxlen)
#else /* LIBC: c16nend */
#include <local/wchar/c16nend.h>
/* Same as `STR+c16nlen(STR, MAX_CHARS)' */
#define __localdep_c16nend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nend))
#endif /* c16nend... */
#endif /* !____localdep_c16nend_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `c16len', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__LOCAL_LIBC(c16nlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16nlen))(__CHAR16_TYPE__ const *__restrict __string,
                                                     __SIZE_TYPE__ __maxlen) {
#line 438 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_c16nend(__string, __maxlen) - __string);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16nlen_defined */
