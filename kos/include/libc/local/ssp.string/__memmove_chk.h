/* HASH CRC-32:0xd030e2b9 */
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
#ifndef __local___memmove_chk_defined
#define __local___memmove_chk_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memmove_defined
#define __local___localdep_memmove_defined 1
#ifdef __CRT_HAVE_memmove
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmove,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memmove */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmove.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmove __LIBC_LOCAL_NAME(memmove)
#endif /* !__CRT_HAVE_memmove */
#endif /* !__local___localdep_memmove_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__memmove_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__memmove_chk))(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) {
	__ssp_chk_dstbuf("memmove", __dst, __n_bytes, __dst_objsize);
	return __localdep_memmove(__dst, __src, __n_bytes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___memmove_chk_defined
#define __local___localdep___memmove_chk_defined 1
#define __localdep___memmove_chk __LIBC_LOCAL_NAME(__memmove_chk)
#endif /* !__local___localdep___memmove_chk_defined */
#endif /* !__local___memmove_chk_defined */
