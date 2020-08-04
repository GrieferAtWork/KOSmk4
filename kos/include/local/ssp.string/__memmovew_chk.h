/* HASH CRC-32:0x1f942233 */
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
#ifndef __local___memmovew_chk_defined
#define __local___memmovew_chk_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memmovew from string */
#ifndef __local___localdep_memmovew_defined
#define __local___localdep_memmovew_defined 1
#ifdef __CRT_HAVE_memmovew
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 2
/* Move memory between potentially overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemmove) && defined(__LIBCCALL_IS_LIBDCALL)
/* Move memory between potentially overlapping memory blocks. */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,(__dst,__src,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memmovew.h>
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks. */
#define __localdep_memmovew __LIBC_LOCAL_NAME(memmovew)
#endif /* !... */
#endif /* !__local___localdep_memmovew_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__memmovew_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__memmovew_chk))(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) {
	__ssp_chk_dstbuf("memmovew", __dst, __n_words * 2, __dst_objsize);
	return __localdep_memmovew(__dst, __src, __n_words);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___memmovew_chk_defined
#define __local___localdep___memmovew_chk_defined 1
#define __localdep___memmovew_chk __LIBC_LOCAL_NAME(__memmovew_chk)
#endif /* !__local___localdep___memmovew_chk_defined */
#endif /* !__local___memmovew_chk_defined */
