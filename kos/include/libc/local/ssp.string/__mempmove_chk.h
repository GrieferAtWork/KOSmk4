/* HASH CRC-32:0x3cc31c73 */
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
#ifndef __local___mempmove_chk_defined
#define __local___mempmove_chk_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempmove_defined
#define __local___localdep_mempmove_defined
#ifdef __CRT_HAVE_mempmove
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_mempmove */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempmove.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempmove __LIBC_LOCAL_NAME(mempmove)
#endif /* !__CRT_HAVE_mempmove */
#endif /* !__local___localdep_mempmove_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mempmove_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mempmove_chk))(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) {
	__ssp_chk_dstbuf("mempmove", __dst, __n_bytes, __dst_objsize);
	return (__NAMESPACE_LOCAL_SYM __localdep_mempmove)(__dst, __src, __n_bytes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___mempmove_chk_defined
#define __local___localdep___mempmove_chk_defined
#define __localdep___mempmove_chk __LIBC_LOCAL_NAME(__mempmove_chk)
#endif /* !__local___localdep___mempmove_chk_defined */
#endif /* !__local___mempmove_chk_defined */
