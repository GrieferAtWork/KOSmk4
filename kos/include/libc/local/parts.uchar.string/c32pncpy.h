/* HASH CRC-32:0x6d907a35 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32pncpy_defined
#define __local_c32pncpy_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32nlen_defined
#define __local___localdep_c32nlen_defined
#if defined(__CRT_HAVE_wcsnlen) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32nlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$wcsnlen)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32nlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___wcsncnt) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32nlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#elif defined(__CRT_HAVE_KOS$__wcsncnt)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32nlen,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32nlen __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__),__SIZE_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__),wcsnlen)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32nlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32nlen __LIBC_LOCAL_NAME(c32nlen)
#endif /* !... */
#endif /* !__local___localdep_c32nlen_defined */
#ifndef __local___localdep_memcpyl_defined
#define __local___localdep_memcpyl_defined
#ifdef __CRT_HAVE_memcpyl
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),memcpyl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemcpy) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmemcpy,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemcpy) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memcpyl,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_dwords),KOS$wmemcpy,(__dst,__src,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpyl __LIBC_LOCAL_NAME(memcpyl)
#endif /* !... */
#endif /* !__local___localdep_memcpyl_defined */
#ifndef __local___localdep_mempsetl_defined
#define __local___localdep_mempsetl_defined
#ifdef __CRT_HAVE_mempsetl
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),mempsetl,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmempset,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempset) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmempset,(__dst,__dword,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempsetl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempsetl __LIBC_LOCAL_NAME(mempsetl)
#endif /* !... */
#endif /* !__local___localdep_mempsetl_defined */
__LOCAL_LIBC(c32pncpy) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32pncpy))(__CHAR32_TYPE__ *__restrict __buf, __CHAR32_TYPE__ const *__restrict __src, __SIZE_TYPE__ __buflen) {
	__SIZE_TYPE__ __srclen = (__NAMESPACE_LOCAL_SYM __localdep_c32nlen)(__src, __buflen);
	(__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_memcpyl)(__buf, __src, __srclen);
	return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_mempsetl)(__buf + __srclen, (__CHAR32_TYPE__)'\0', __buflen - __srclen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32pncpy_defined
#define __local___localdep_c32pncpy_defined
#define __localdep_c32pncpy __LIBC_LOCAL_NAME(c32pncpy)
#endif /* !__local___localdep_c32pncpy_defined */
#endif /* !__local_c32pncpy_defined */
