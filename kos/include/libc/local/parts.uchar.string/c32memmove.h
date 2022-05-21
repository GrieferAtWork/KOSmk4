/* HASH CRC-32:0xdcb17cde */
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
#ifndef __local_c32memmove_defined
#define __local_c32memmove_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memmove_defined
#define __local___localdep_memmove_defined
#ifdef __CRT_HAVE_memmove
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memmove */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmove.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmove __LIBC_LOCAL_NAME(memmove)
#endif /* !__CRT_HAVE_memmove */
#endif /* !__local___localdep_memmove_defined */
#ifndef __local___localdep_memmovel_defined
#define __local___localdep_memmovel_defined
#ifdef __CRT_HAVE_memmovel
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemmove) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memmovel,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,(__dst,__src,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmovel.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmovel __LIBC_LOCAL_NAME(memmovel)
#endif /* !... */
#endif /* !__local___localdep_memmovel_defined */
#ifndef __local___localdep_memmovew_defined
#define __local___localdep_memmovew_defined
#ifdef __CRT_HAVE_memmovew
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemmove) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,(__dst,__src,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmovew.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmovew __LIBC_LOCAL_NAME(memmovew)
#endif /* !... */
#endif /* !__local___localdep_memmovew_defined */
__LOCAL_LIBC(c32memmove) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32memmove))(__CHAR32_TYPE__ *__dst, __CHAR32_TYPE__ const *__src, __SIZE_TYPE__ __num_chars) {



	return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_memmovel)(__dst, __src, __num_chars);



}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32memmove_defined
#define __local___localdep_c32memmove_defined
#define __localdep_c32memmove __LIBC_LOCAL_NAME(c32memmove)
#endif /* !__local___localdep_c32memmove_defined */
#endif /* !__local_c32memmove_defined */
