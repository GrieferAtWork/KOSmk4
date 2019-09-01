/* HASH 0x24c038a1 */
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
#ifndef __local_c16len_defined
#define __local_c16len_defined 1
/* Dependency: "wcsend" from "wchar" */
#ifndef ____localdep_c16end_defined
#define ____localdep_c16end_defined 1
#if defined(__CRT_HAVE_wcsend) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `STR+c16len(STR)' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16end,(__CHAR16_TYPE__ const *__restrict __string),wcsend,(__string))
#elif defined(__CRT_HAVE_DOS$wcsend)
/* Same as `STR+c16len(STR)' */
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16end,(__CHAR16_TYPE__ const *__restrict __string),wcsend,(__string))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsend.h>
/* Same as `STR+c16len(STR)' */
#define __localdep_c16end(string) (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))((__WCHAR_TYPE__ const *)(string))
#else /* LIBC: c16end */
#include <local/wchar/c16end.h>
/* Same as `STR+c16len(STR)' */
#define __localdep_c16end (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16end))
#endif /* c16end... */
#endif /* !____localdep_c16end_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__LOCAL_LIBC(c16len) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c16len))(__CHAR16_TYPE__ const *__restrict __string) {
#line 206 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_c16end(__string) - __string);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16len_defined */
