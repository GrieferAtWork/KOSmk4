/* HASH CRC-32:0x34b8b151 */
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
#ifndef __local_wcscat_defined
#define __local_wcscat_defined 1
/* Dependency: "wmemcpy" from "wchar" */
#ifndef ____localdep_wmemcpy_defined
#define ____localdep_wmemcpy_defined 1
#if defined(__CRT_HAVE_wmemcpy)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyw) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyl) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),memcpyl,(__dst,__src,__num_chars))
#else /* LIBC: wmemcpy */
#include <local/wchar/wmemcpy.h>
#define __localdep_wmemcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcpy))
#endif /* wmemcpy... */
#endif /* !____localdep_wmemcpy_defined */

/* Dependency: "wcsend" from "wchar" */
#ifndef ____localdep_wcsend_defined
#define ____localdep_wcsend_defined 1
#if defined(__CRT_HAVE_wcsend)
/* Same as `STR+wcslen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcsend,(__WCHAR_TYPE__ const *__restrict __string),wcsend,(__string))
#else /* LIBC: wcsend */
#include <local/wchar/wcsend.h>
/* Same as `STR+wcslen(STR)' */
#define __localdep_wcsend (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))
#endif /* wcsend... */
#endif /* !____localdep_wcsend_defined */

/* Dependency: "wcslen" from "wchar" */
#ifndef ____localdep_wcslen_defined
#define ____localdep_wcslen_defined 1
#ifdef __std___localdep_wcslen_defined
__NAMESPACE_STD_USING(__localdep_wcslen)
#elif defined(__CRT_HAVE_wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __string),wcslen,(__string))
#else /* LIBC: wcslen */
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_wcslen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))
#endif /* wcslen... */
#endif /* !____localdep_wcslen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcscat) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcscat))(__WCHAR_TYPE__ *__restrict __buf,
                                                    __WCHAR_TYPE__ const *__restrict __src) {
#line 326 "kos/src/libc/magic/wchar.c"
	__localdep_wmemcpy(__localdep_wcsend(__buf), __src, __localdep_wcslen(__src) + 1);
	return __buf;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcscat_defined */
