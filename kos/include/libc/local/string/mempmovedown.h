/* HASH CRC-32:0x27556261 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_mempmovedown_defined
#define __local_mempmovedown_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memmovedown_defined
#define __local___localdep_memmovedown_defined
#ifdef __CRT_HAVE_memmovedown
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmovedown,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_memmove)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmovedown.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmovedown __LIBC_LOCAL_NAME(memmovedown)
#endif /* !... */
#endif /* !__local___localdep_memmovedown_defined */
__LOCAL_LIBC(mempmovedown) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempmovedown))(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes) {
	return (void *)((__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_memmovedown)(__dst, __src, __n_bytes) + __n_bytes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mempmovedown_defined
#define __local___localdep_mempmovedown_defined
#define __localdep_mempmovedown __LIBC_LOCAL_NAME(mempmovedown)
#endif /* !__local___localdep_mempmovedown_defined */
#endif /* !__local_mempmovedown_defined */
