/* HASH CRC-32:0xdc890af3 */
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
#ifndef __local_c32pcpy_defined
#define __local_c32pcpy_defined 1
/* Dependency: "wmempcpy" from "wchar" */
#ifndef ____localdep_c32mempcpy_defined
#define ____localdep_c32mempcpy_defined 1
#if defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32mempcpy,(__CHAR32_TYPE__ *__restrict __dst, __CHAR32_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyl)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32mempcpy,(__CHAR32_TYPE__ *__restrict __dst, __CHAR32_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyl,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wmempcpy.h>
#define __localdep_c32mempcpy(dst, src, num_chars) (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempcpy))((__WCHAR_TYPE__ *)(dst), (__WCHAR_TYPE__ const *)(src), num_chars)
#else /* LIBC: c32mempcpy */
#include <local/wchar/c32mempcpy.h>
#define __localdep_c32mempcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32mempcpy))
#endif /* c32mempcpy... */
#endif /* !____localdep_c32mempcpy_defined */

/* Dependency: "wcslen" from "wchar" */
#ifndef ____localdep_c32len_defined
#define ____localdep_c32len_defined 1
#if defined(__CRT_HAVE_wcslen) && (__SIZEOF_WCHAR_T__ == 4)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32len,(__CHAR32_TYPE__ const *__restrict __string),wcslen,(__string))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcslen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c32len(string) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))((__WCHAR_TYPE__ const *)(string))
#else /* LIBC: c32len */
#include <local/wchar/c32len.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_c32len (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32len))
#endif /* c32len... */
#endif /* !____localdep_c32len_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as wcscpy, but return a pointer after the last written character */
__LOCAL_LIBC(c32pcpy) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32pcpy))(__CHAR32_TYPE__ *__restrict __buf,
                                                     __CHAR32_TYPE__ const *__restrict __src) {
#line 1344 "kos/src/libc/magic/wchar.c"
	return __localdep_c32mempcpy(__buf, __src, __localdep_c32len(__src) + 1);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32pcpy_defined */
