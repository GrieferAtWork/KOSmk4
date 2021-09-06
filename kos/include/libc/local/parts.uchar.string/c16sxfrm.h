/* HASH CRC-32:0x5adb7eae */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16sxfrm_defined
#define __local_c16sxfrm_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16snlen_defined
#define __local___localdep_c16snlen_defined 1
#if defined(__CRT_HAVE_wcsnlen) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16snlen,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnlen)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16snlen,(__CHAR16_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16snlen (*(__SIZE_TYPE__(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wcsnlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16snlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16snlen __LIBC_LOCAL_NAME(c16snlen)
#endif /* !... */
#endif /* !__local___localdep_c16snlen_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined 1
#ifdef __CRT_HAVE_memcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
__LOCAL_LIBC(c16sxfrm) __ATTR_NONNULL((2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16sxfrm))(__CHAR16_TYPE__ *__dst, __CHAR16_TYPE__ const *__restrict __src, __SIZE_TYPE__ __maxlen) {
	/* XXX: Implement me */
	__SIZE_TYPE__ __n = __localdep_c16snlen(__src, __maxlen);
	__localdep_memcpy(__dst, __src, __n * sizeof(__CHAR16_TYPE__));
	return __n;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16sxfrm_defined
#define __local___localdep_c16sxfrm_defined 1
#define __localdep_c16sxfrm __LIBC_LOCAL_NAME(c16sxfrm)
#endif /* !__local___localdep_c16sxfrm_defined */
#endif /* !__local_c16sxfrm_defined */
