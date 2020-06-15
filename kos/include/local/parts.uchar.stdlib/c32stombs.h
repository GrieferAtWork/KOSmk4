/* HASH CRC-32:0xd9b4bb78 */
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
#ifndef __local_c32stombs_defined
#define __local_c32stombs_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32rtombs from parts.uchar.wchar */
#ifndef __local___localdep_c32rtombs_defined
#define __local___localdep_c32rtombs_defined 1
#if defined(__CRT_HAVE_wcsrtombs) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32rtombs,(char *__dst, __CHAR32_TYPE__ const **__restrict __psrc, __SIZE_TYPE__ __dstlen, __mbstate_t *__mbs),wcsrtombs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_KOS$wcsrtombs)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32rtombs,(char *__dst, __CHAR32_TYPE__ const **__restrict __psrc, __SIZE_TYPE__ __dstlen, __mbstate_t *__mbs),wcsrtombs,(__dst,__psrc,__dstlen,__mbs))
#elif (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcsrtombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32rtombs (*(__SIZE_TYPE__(__LIBKCALL *)(char *, __CHAR32_TYPE__ const **__restrict, __SIZE_TYPE__, __mbstate_t *))&__LIBC_LOCAL_NAME(wcsrtombs))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.wchar/c32rtombs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32rtombs __LIBC_LOCAL_NAME(c32rtombs)
#endif /* !... */
#endif /* !__local___localdep_c32rtombs_defined */
__LOCAL_LIBC(c32stombs) __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32stombs))(char *__restrict __dst, __CHAR32_TYPE__ const *__restrict __src, __SIZE_TYPE__ __dstlen) {
	return __localdep_c32rtombs(__dst, (__CHAR32_TYPE__ const **)&__src, __dstlen, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32stombs_defined
#define __local___localdep_c32stombs_defined 1
#define __localdep_c32stombs __LIBC_LOCAL_NAME(c32stombs)
#endif /* !__local___localdep_c32stombs_defined */
#endif /* !__local_c32stombs_defined */
