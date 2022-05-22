/* HASH CRC-32:0x5602ec49 */
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
#ifndef __local___memmovec_chk_defined
#define __local___memmovec_chk_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memmovec_defined
#define __local___localdep_memmovec_defined
#ifdef __CRT_HAVE_memmovec
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__localdep_memmovec,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memmovec,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memmovec */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmovec.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmovec __LIBC_LOCAL_NAME(memmovec)
#endif /* !__CRT_HAVE_memmovec */
#endif /* !__local___localdep_memmovec_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__memmovec_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__memmovec_chk))(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) {
	__ssp_chk_dstbuf("memmovec", __dst, __elem_count * __elem_size, __dst_objsize);
	return (__NAMESPACE_LOCAL_SYM __localdep_memmovec)(__dst, __src, __elem_count, __elem_size);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___memmovec_chk_defined
#define __local___localdep___memmovec_chk_defined
#define __localdep___memmovec_chk __LIBC_LOCAL_NAME(__memmovec_chk)
#endif /* !__local___localdep___memmovec_chk_defined */
#endif /* !__local___memmovec_chk_defined */
