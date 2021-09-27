/* HASH CRC-32:0x50f396ac */
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
#ifndef __local___mempmovec_chk_defined
#define __local___mempmovec_chk_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempmovec_defined
#define __local___localdep_mempmovec_defined
#ifdef __CRT_HAVE_mempmovec
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempmovec,(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempmovec,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempmovec */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempmovec.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempmovec __LIBC_LOCAL_NAME(mempmovec)
#endif /* !__CRT_HAVE_mempmovec */
#endif /* !__local___localdep_mempmovec_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mempmovec_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mempmovec_chk))(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size, __SIZE_TYPE__ __dst_objsize) {
	__ssp_chk_dstbuf("mempmovec", __dst, __elem_count * __elem_size, __dst_objsize);
	return (__NAMESPACE_LOCAL_SYM __localdep_mempmovec)(__dst, __src, __elem_count, __elem_size);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___mempmovec_chk_defined
#define __local___localdep___mempmovec_chk_defined
#define __localdep___mempmovec_chk __LIBC_LOCAL_NAME(__mempmovec_chk)
#endif /* !__local___localdep___mempmovec_chk_defined */
#endif /* !__local___mempmovec_chk_defined */
