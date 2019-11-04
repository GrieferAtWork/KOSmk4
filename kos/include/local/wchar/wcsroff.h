/* HASH CRC-32:0x52b76eba */
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
#ifndef __local_wcsroff_defined
#define __local_wcsroff_defined 1
/* Dependency: "wcsrchrnul" from "wchar" */
#ifndef ____localdep_wcsrchrnul_defined
#define ____localdep_wcsrchrnul_defined 1
#ifdef __CRT_HAVE_wcsrchrnul
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcsrchrnul,(__WCHAR_TYPE__ const *__restrict __haystack, __WCHAR_TYPE__ __needle),wcsrchrnul,(__haystack,__needle))
#else /* LIBC: wcsrchrnul */
#include <local/wchar/wcsrchrnul.h>
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_wcsrchrnul (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))
#endif /* wcsrchrnul... */
#endif /* !____localdep_wcsrchrnul_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__LOCAL_LIBC(wcsroff) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsroff))(__WCHAR_TYPE__ const *__restrict __haystack,
                                                     __WCHAR_TYPE__ __needle) {
#line 2243 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_wcsrchrnul(__haystack, __needle) - __haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcsroff_defined */
