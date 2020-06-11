/* HASH CRC-32:0xdf33f8fb */
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
#ifndef __local_c16nlen_defined
#define __local_c16nlen_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16nend from parts.uchar.string */
#ifndef __local___localdep_c16nend_defined
#define __local___localdep_c16nend_defined 1
#if defined(__CRT_HAVE_wcsnend) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__LIBDCALL,__localdep_c16nend,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnend)
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16nend,(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string,__maxlen))
#elif (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsnend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
#define __localdep_c16nend (*(__CHAR16_TYPE__ *(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wcsnend))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c16nend.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
#define __localdep_c16nend (*(__CHAR16_TYPE__ *(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(c16nend))
#endif /* !... */
#endif /* !__local___localdep_c16nend_defined */
/* Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__LOCAL_LIBC(c16nlen) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16nlen))(__CHAR16_TYPE__ const *__restrict __string, __SIZE_TYPE__ __maxlen) {
	return (__SIZE_TYPE__)(__localdep_c16nend(__string, __maxlen) - __string);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16nlen_defined
#define __local___localdep_c16nlen_defined 1
#define __localdep_c16nlen __LIBC_LOCAL_NAME(c16nlen)
#endif /* !__local___localdep_c16nlen_defined */
#endif /* !__local_c16nlen_defined */
