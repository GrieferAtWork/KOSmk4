/* HASH CRC-32:0x2a0b9a90 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_memmovedownc_defined
#define __local_memmovedownc_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memmovedown from string */
#ifndef __local___localdep_memmovedown_defined
#define __local___localdep_memmovedown_defined 1
#ifdef __CRT_HAVE_memmovedown
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmovedown,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE_memmove)
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memmovedown,(void *__dst, void const *__src, __SIZE_TYPE__ __n_bytes),memmove,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memmovedown.h>
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !N_BYTES')
 * @return: * : Always re-returns `dst' */
#define __localdep_memmovedown __LIBC_LOCAL_NAME(memmovedown)
#endif /* !... */
#endif /* !__local___localdep_memmovedown_defined */
/* Dependency: memmovedownl from string */
#ifndef __local___localdep_memmovedownl_defined
#define __local___localdep_memmovedownl_defined 1
#ifdef __CRT_HAVE_memmovedownl
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovedownl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_memmovel)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),memmovel,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 4
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),wmemmove,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemmove) && defined(__LIBCCALL_IS_LIBKCALL)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memmovedownl,(void *__dst, void const *__src, __SIZE_TYPE__ __n_dwords),KOS$wmemmove,(__dst,__src,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memmovedownl.h>
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_DWORDS') */
#define __localdep_memmovedownl __LIBC_LOCAL_NAME(memmovedownl)
#endif /* !... */
#endif /* !__local___localdep_memmovedownl_defined */
/* Dependency: memmovedownq from string */
#ifndef __local___localdep_memmovedownq_defined
#define __local___localdep_memmovedownq_defined 1
#ifdef __CRT_HAVE_memmovedownq
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmovedownq,(__dst,__src,__n_qwords))
#elif defined(__CRT_HAVE_memmoveq)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownq,(void *__dst, void const *__src, __SIZE_TYPE__ __n_qwords),memmoveq,(__dst,__src,__n_qwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memmovedownq.h>
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_QWORDS') */
#define __localdep_memmovedownq __LIBC_LOCAL_NAME(memmovedownq)
#endif /* !... */
#endif /* !__local___localdep_memmovedownq_defined */
/* Dependency: memmovedownw from string */
#ifndef __local___localdep_memmovedownw_defined
#define __local___localdep_memmovedownw_defined 1
#ifdef __CRT_HAVE_memmovedownw
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovedownw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_memmovew)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),memmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemmove) && __SIZEOF_WCHAR_T__ == 2
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmemmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemmove) && defined(__LIBCCALL_IS_LIBDCALL)
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memmovedownw,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmemmove,(__dst,__src,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memmovedownw.h>
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks. (assumes that `DST <= SRC || !N_WORDS') */
#define __localdep_memmovedownw __LIBC_LOCAL_NAME(memmovedownw)
#endif /* !... */
#endif /* !__local___localdep_memmovedownw_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/host.h>
__NAMESPACE_LOCAL_BEGIN
/* Move memory between potentially overlapping memory blocks (assumes that `DST <= SRC || !ELEM_COUNT || !ELEM_SIZE')
 * @return: * : Always re-returns `dst' */
__LOCAL_LIBC(memmovedownc) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memmovedownc))(void *__dst, void const *__src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (__elem_size) {

	case 1:
		return __localdep_memmovedown(__dst, __src, __elem_count);

	case 2:
		return __localdep_memmovedownw(__dst, __src, __elem_count);

	case 4:
		return __localdep_memmovedownl(__dst, __src, __elem_count);

#ifdef __UINT64_TYPE__
	case 8:
		return __localdep_memmovedownq(__dst, __src, __elem_count);
#endif /* __UINT64_TYPE__ */

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
	return __localdep_memmovedown(__dst, __src, __elem_count * __elem_size);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memmovedownc_defined
#define __local___localdep_memmovedownc_defined 1
#define __localdep_memmovedownc __LIBC_LOCAL_NAME(memmovedownc)
#endif /* !__local___localdep_memmovedownc_defined */
#endif /* !__local_memmovedownc_defined */
