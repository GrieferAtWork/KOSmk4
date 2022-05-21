/* HASH CRC-32:0x5612b4f9 */
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
#ifndef __local_mempcpyq_defined
#define __local_mempcpyq_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcpyq_defined
#define __local___localdep_memcpyq_defined
#ifdef __CRT_HAVE_memcpyq
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),memcpyq,(__dst,__src,__n_qwords))
#else /* __CRT_HAVE_memcpyq */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyq.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpyq __LIBC_LOCAL_NAME(memcpyq)
#endif /* !__CRT_HAVE_memcpyq */
#endif /* !__local___localdep_memcpyq_defined */
__LOCAL_LIBC(mempcpyq) __ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempcpyq))(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords) {
	return (__UINT64_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_memcpyq)(__dst, __src, __n_qwords) + __n_qwords;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mempcpyq_defined
#define __local___localdep_mempcpyq_defined
#define __localdep_mempcpyq __LIBC_LOCAL_NAME(mempcpyq)
#endif /* !__local___localdep_mempcpyq_defined */
#endif /* !__local_mempcpyq_defined */
