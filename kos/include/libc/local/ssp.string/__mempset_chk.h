/* HASH CRC-32:0x27097d2e */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local___mempset_chk_defined
#define __local___mempset_chk_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempset_defined
#define __local___localdep_mempset_defined
#ifdef __CRT_HAVE_mempset
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_mempset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),mempset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_mempset */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempset __LIBC_LOCAL_NAME(mempset)
#endif /* !__CRT_HAVE_mempset */
#endif /* !__local___localdep_mempset_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mempset_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mempset_chk))(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) {
	__ssp_chk_dstbuf("mempset", __dst, __n_bytes, __dst_objsize);
	return (__NAMESPACE_LOCAL_SYM __localdep_mempset)(__dst, __byte, __n_bytes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___mempset_chk_defined
#define __local___localdep___mempset_chk_defined
#define __localdep___mempset_chk __LIBC_LOCAL_NAME(__mempset_chk)
#endif /* !__local___localdep___mempset_chk_defined */
#endif /* !__local___mempset_chk_defined */
