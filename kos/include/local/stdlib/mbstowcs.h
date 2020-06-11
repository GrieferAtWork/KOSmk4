/* HASH CRC-32:0xef4199d1 */
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
#ifndef __local_mbstowcs_defined
#define __local_mbstowcs_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mbsrtowcs from wchar */
#ifndef __local___localdep_mbsrtowcs_defined
#define __local___localdep_mbsrtowcs_defined 1
#ifdef __CRT_HAVE_mbsrtowcs
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsrtowcs,(__WCHAR_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, __mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbsrtowcs) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsrtowcs,(__CHAR32_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, __mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#elif defined(__CRT_HAVE_DOS$mbsrtowcs) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_mbsrtowcs,(__CHAR16_TYPE__ *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __dstlen, __mbstate_t *__mbs),mbsrtowcs,(__dst,__psrc,__dstlen,__mbs))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wchar/mbsrtowcs.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mbsrtowcs __LIBC_LOCAL_NAME(mbsrtowcs)
#endif /* !... */
#endif /* !__local___localdep_mbsrtowcs_defined */
__LOCAL_LIBC(mbstowcs) __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mbstowcs))(__WCHAR_TYPE__ *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dstlen) {
	return __localdep_mbsrtowcs(__dst, (char const **)&__src, __dstlen, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mbstowcs_defined
#define __local___localdep_mbstowcs_defined 1
#define __localdep_mbstowcs __LIBC_LOCAL_NAME(mbstowcs)
#endif /* !__local___localdep_mbstowcs_defined */
#endif /* !__local_mbstowcs_defined */
