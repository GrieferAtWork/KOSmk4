/* HASH CRC-32:0x54ea3a31 */
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
#ifndef __local_mempmovedownc_defined
#define __local_mempmovedownc_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempmovedown_defined
#define __local___localdep_mempmovedown_defined
#ifdef __CRT_HAVE_mempmovedown
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmovedown,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_mempmove)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),mempmove,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempmovedown.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempmovedown __LIBC_LOCAL_NAME(mempmovedown)
#endif /* !... */
#endif /* !__local___localdep_mempmovedown_defined */
#ifndef __local___localdep_mempmovedownl_defined
#define __local___localdep_mempmovedownl_defined
#ifdef __CRT_HAVE_mempmovedownl
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),mempmovedownl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_mempmovel)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),mempmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmempmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempmove) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_mempmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmempmove,(__dst,__src,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempmovedownl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempmovedownl __LIBC_LOCAL_NAME(mempmovedownl)
#endif /* !... */
#endif /* !__local___localdep_mempmovedownl_defined */
#ifndef __local___localdep_mempmovedownq_defined
#define __local___localdep_mempmovedownq_defined
#ifdef __CRT_HAVE_mempmovedownq
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmovedownq,(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_mempmoveq)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownq,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_qwords),mempmoveq,(__dst,__src,__n_qwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempmovedownq.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempmovedownq __LIBC_LOCAL_NAME(mempmovedownq)
#endif /* !... */
#endif /* !__local___localdep_mempmovedownq_defined */
#ifndef __local___localdep_mempmovedownw_defined
#define __local___localdep_mempmovedownw_defined
#ifdef __CRT_HAVE_mempmovedownw
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmovedownw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_mempmovew)
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempmove) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_mempmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,(__dst,__src,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempmovedownw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempmovedownw __LIBC_LOCAL_NAME(mempmovedownw)
#endif /* !... */
#endif /* !__local___localdep_mempmovedownw_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/host.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(mempmovedownc) __ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempmovedownc))(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (__elem_size) {

	case 1:
		return (__NAMESPACE_LOCAL_SYM __localdep_mempmovedown)(__dst, __src, __elem_count);

	case 2:
		return (__NAMESPACE_LOCAL_SYM __localdep_mempmovedownw)(__dst, __src, __elem_count);

	case 4:
		return (__NAMESPACE_LOCAL_SYM __localdep_mempmovedownl)(__dst, __src, __elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return (__NAMESPACE_LOCAL_SYM __localdep_mempmovedownq)(__dst, __src, __elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return (__NAMESPACE_LOCAL_SYM __localdep_mempmovedown)(__dst, __src, __elem_count * __elem_size);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mempmovedownc_defined
#define __local___localdep_mempmovedownc_defined
#define __localdep_mempmovedownc __LIBC_LOCAL_NAME(mempmovedownc)
#endif /* !__local___localdep_mempmovedownc_defined */
#endif /* !__local_mempmovedownc_defined */
