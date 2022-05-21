/* HASH CRC-32:0xee4c6fff */
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
#ifndef __local_memmoveupc_defined
#define __local_memmoveupc_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memmoveup_defined
#define __local___localdep_memmoveup_defined
#ifdef __CRT_HAVE_memmoveup
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmoveup,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_memmove)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmoveup,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmoveup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmoveup __LIBC_LOCAL_NAME(memmoveup)
#endif /* !... */
#endif /* !__local___localdep_memmoveup_defined */
#ifndef __local___localdep_memmoveupl_defined
#define __local___localdep_memmoveupl_defined
#ifdef __CRT_HAVE_memmoveupl
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmoveupl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_memmovel)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemmove) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memmoveupl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,(__dst,__src,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmoveupl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmoveupl __LIBC_LOCAL_NAME(memmoveupl)
#endif /* !... */
#endif /* !__local___localdep_memmoveupl_defined */
#ifndef __local___localdep_memmoveupq_defined
#define __local___localdep_memmoveupq_defined
#ifdef __CRT_HAVE_memmoveupq
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveupq,(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_memmoveq)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmoveupq.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmoveupq __LIBC_LOCAL_NAME(memmoveupq)
#endif /* !... */
#endif /* !__local___localdep_memmoveupq_defined */
#ifndef __local___localdep_memmoveupw_defined
#define __local___localdep_memmoveupw_defined
#ifdef __CRT_HAVE_memmoveupw
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmoveupw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_memmovew)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemmove) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memmoveupw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,(__dst,__src,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memmoveupw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memmoveupw __LIBC_LOCAL_NAME(memmoveupw)
#endif /* !... */
#endif /* !__local___localdep_memmoveupw_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/host.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memmoveupc) __ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memmoveupc))(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (__elem_size) {

	case 1:
		return (__NAMESPACE_LOCAL_SYM __localdep_memmoveup)(__dst, __src, __elem_count);

	case 2:
		return (__NAMESPACE_LOCAL_SYM __localdep_memmoveupw)(__dst, __src, __elem_count);

	case 4:
		return (__NAMESPACE_LOCAL_SYM __localdep_memmoveupl)(__dst, __src, __elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return (__NAMESPACE_LOCAL_SYM __localdep_memmoveupq)(__dst, __src, __elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return (__NAMESPACE_LOCAL_SYM __localdep_memmoveup)(__dst, __src, __elem_count * __elem_size);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memmoveupc_defined
#define __local___localdep_memmoveupc_defined
#define __localdep_memmoveupc __LIBC_LOCAL_NAME(memmoveupc)
#endif /* !__local___localdep_memmoveupc_defined */
#endif /* !__local_memmoveupc_defined */
