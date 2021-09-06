/* HASH CRC-32:0x4efe9ce1 */
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
#ifndef __local___memmoveup_chk_defined
#define __local___memmoveup_chk_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memmoveup_defined
#define __local___localdep_memmoveup_defined 1
#ifdef __CRT_HAVE_memmoveup
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmoveup,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_memmove)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmoveup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmoveup __LIBC_LOCAL_NAME(memmoveup)
#endif /* !... */
#endif /* !__local___localdep_memmoveup_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__memmoveup_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__memmoveup_chk))(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) {
	__ssp_chk_dstbuf("memmoveup", __dst, __n_bytes, __dst_objsize);
	return __localdep_memmoveup(__dst, __src, __n_bytes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___memmoveup_chk_defined
#define __local___localdep___memmoveup_chk_defined 1
#define __localdep___memmoveup_chk __LIBC_LOCAL_NAME(__memmoveup_chk)
#endif /* !__local___localdep___memmoveup_chk_defined */
#endif /* !__local___memmoveup_chk_defined */
