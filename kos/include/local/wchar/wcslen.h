/* HASH CRC-32:0xbc24a81b */
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
#ifndef __local_wcslen_defined
#define __local_wcslen_defined 1
/* Dependency: "wcsend" from "wchar" */
#ifndef ____localdep_wcsend_defined
#define ____localdep_wcsend_defined 1
#ifdef __CRT_HAVE_wcsend
/* Same as `STR+wcslen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcsend,(__WCHAR_TYPE__ const *__restrict __string),wcsend,(__string))
#else /* LIBC: wcsend */
#include <local/wchar/wcsend.h>
/* Same as `STR+wcslen(STR)' */
#define __localdep_wcsend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))
#endif /* wcsend... */
#endif /* !____localdep_wcsend_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__LOCAL_LIBC(wcslen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcslen))(__WCHAR_TYPE__ const *__restrict __string) {
#line 252 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_wcsend(__string) - __string);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcslen_defined */
