/* HASH CRC-32:0x4820f2aa */
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
#ifndef __local_mbstoc32s_defined
#define __local_mbstoc32s_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mbsrtoc32 from parts.uchar.wchar */
#ifndef __local___localdep_mbsrtoc32_defined
#define __local___localdep_mbsrtoc32_defined 1
#if defined(__CRT_HAVE_mbsrtowcs) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsrtoc32,(__CHAR32_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, __mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_KOS$mbsrtowcs)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsrtoc32,(__CHAR32_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, __mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/mbsrtowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbsrtoc32 (*(__SIZE_TYPE__(__LIBKCALL *)(__CHAR32_TYPE__ *__restrict, char const **__restrict, __SIZE_TYPE__, __mbstate_t *))&__LIBC_LOCAL_NAME(mbsrtowcs))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.wchar/mbsrtoc32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbsrtoc32 __LIBC_LOCAL_NAME(mbsrtoc32)
#endif /* !... */
#endif /* !__local___localdep_mbsrtoc32_defined */
__LOCAL_LIBC(mbstoc32s) __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(mbstoc32s))(__CHAR32_TYPE__ *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dstlen) {
	return __localdep_mbsrtoc32(__dst, (char const **)&__src, __dstlen, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mbstoc32s_defined
#define __local___localdep_mbstoc32s_defined 1
#define __localdep_mbstoc32s __LIBC_LOCAL_NAME(mbstoc32s)
#endif /* !__local___localdep_mbstoc32s_defined */
#endif /* !__local_mbstoc32s_defined */
