/* HASH CRC-32:0x5ce51cf8 */
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
#ifndef __local_wcpncpy_defined
#define __local_wcpncpy_defined 1
/* Dependency: "wcsnlen" from "wchar" */
#ifndef ____localdep_wcsnlen_defined
#define ____localdep_wcsnlen_defined 1
#if defined(__CRT_HAVE_wcsnlen)
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(__WCHAR_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnlen,(__string,__maxlen))
#else /* LIBC: wcsnlen */
#include <local/wchar/wcsnlen.h>
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_wcsnlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))
#endif /* wcsnlen... */
#endif /* !____localdep_wcsnlen_defined */

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

/* Dependency: "wmemset" from "wchar" */
#ifndef ____localdep_wmemset_defined
#define ____localdep_wmemset_defined 1
#if defined(__CRT_HAVE_wmemset)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),wmemset,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetw) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetl) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemset,(__WCHAR_TYPE__ *__dst, __WCHAR_TYPE__ __filler, __SIZE_TYPE__ __num_chars),memsetl,(__dst,__filler,__num_chars))
#else /* LIBC: wmemset */
#include <local/wchar/wmemset.h>
#define __localdep_wmemset (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemset))
#endif /* wmemset... */
#endif /* !____localdep_wmemset_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcpncpy) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcpncpy))(__WCHAR_TYPE__ *__restrict __buf,
                                                     __WCHAR_TYPE__ const *__restrict __src,
                                                     __SIZE_TYPE__ __buflen) {
#line 739 "kos/src/libc/magic/wchar.c"
	__SIZE_TYPE__ __srclen = __localdep_wcsnlen(__src, __buflen);
	__localdep_wmemcpy(__buf, __src, __srclen);
	__localdep_wmemset(__buf + __srclen, '\0', (__SIZE_TYPE__)(__buflen - __srclen));
	return __buf + __srclen;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcpncpy_defined */
