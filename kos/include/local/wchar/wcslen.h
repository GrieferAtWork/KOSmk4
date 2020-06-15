/* HASH CRC-32:0xe6c8a827 */
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
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wcsend from wchar */
#ifndef __local___localdep_wcsend_defined
#define __local___localdep_wcsend_defined 1
#ifdef __CRT_HAVE_wcsend
/* Same as `STR+wcslen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcsend,(__WCHAR_TYPE__ const *__restrict __string),wcsend,(__string))
#else /* __CRT_HAVE_wcsend */
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR+wcslen(STR)' */
#define __localdep_wcsend __LIBC_LOCAL_NAME(wcsend)
#endif /* !__CRT_HAVE_wcsend */
#endif /* !__local___localdep_wcsend_defined */
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__LOCAL_LIBC(wcslen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcslen))(__WCHAR_TYPE__ const *__restrict __string) {
	return (__SIZE_TYPE__)(__localdep_wcsend(__string) - __string);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcslen_defined
#define __local___localdep_wcslen_defined 1
#define __localdep_wcslen __LIBC_LOCAL_NAME(wcslen)
#endif /* !__local___localdep_wcslen_defined */
#endif /* !__local_wcslen_defined */
