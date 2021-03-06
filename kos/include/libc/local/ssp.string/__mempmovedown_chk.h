/* HASH CRC-32:0x11a3dcda */
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
#ifndef __local___mempmovedown_chk_defined
#define __local___mempmovedown_chk_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mempmovedown from string */
#ifndef __local___localdep_mempmovedown_defined
#define __local___localdep_mempmovedown_defined 1
#ifdef __CRT_HAVE_mempmovedown
/* Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmovedown,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_mempmove)
/* Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempmovedown.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memmovedown', but return `dst + n_bytes', rather than `dst' (assumes that `dst <= src || !n_bytes') */
#define __localdep_mempmovedown __LIBC_LOCAL_NAME(mempmovedown)
#endif /* !... */
#endif /* !__local___localdep_mempmovedown_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mempmovedown_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mempmovedown_chk))(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes, __SIZE_TYPE__ __dst_objsize) {
	__ssp_chk_dstbuf("mempmovedown", __dst, __n_bytes, __dst_objsize);
	return __localdep_mempmovedown(__dst, __src, __n_bytes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___mempmovedown_chk_defined
#define __local___localdep___mempmovedown_chk_defined 1
#define __localdep___mempmovedown_chk __LIBC_LOCAL_NAME(__mempmovedown_chk)
#endif /* !__local___localdep___mempmovedown_chk_defined */
#endif /* !__local___mempmovedown_chk_defined */
