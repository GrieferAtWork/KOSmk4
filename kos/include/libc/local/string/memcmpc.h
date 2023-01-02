/* HASH CRC-32:0x9fac2474 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_memcmpc_defined
#define __local_memcmpc_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcmp_defined
#define __local___localdep_memcmp_defined
#ifdef __CRT_HAVE_memcmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE___gcc_bcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),__gcc_bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcmp __LIBC_LOCAL_NAME(memcmp)
#endif /* !... */
#endif /* !__local___localdep_memcmp_defined */
#ifndef __local___localdep_memcmpl_defined
#define __local___localdep_memcmpl_defined
#ifdef __CRT_HAVE_memcmpl
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpl,(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_wmemcmp) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),wmemcmp,(__s1,__s2,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemcmp) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__LIBCCALL,__localdep_memcmpl,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),KOS$wmemcmp,(__s1,__s2,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmpl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcmpl __LIBC_LOCAL_NAME(memcmpl)
#endif /* !... */
#endif /* !__local___localdep_memcmpl_defined */
#ifndef __local___localdep_memcmpq_defined
#define __local___localdep_memcmpq_defined
#ifdef __CRT_HAVE_memcmpq
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_memcmpq,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_dwords),memcmpq,(__s1,__s2,__n_dwords))
#else /* __CRT_HAVE_memcmpq */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmpq.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcmpq __LIBC_LOCAL_NAME(memcmpq)
#endif /* !__CRT_HAVE_memcmpq */
#endif /* !__local___localdep_memcmpq_defined */
#ifndef __local___localdep_memcmpw_defined
#define __local___localdep_memcmpw_defined
#ifdef __CRT_HAVE_memcmpw
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),memcmpw,(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_wmemcmp) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),wmemcmp,(__s1,__s2,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemcmp) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__LIBCCALL,__localdep_memcmpw,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_words),DOS$wmemcmp,(__s1,__s2,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmpw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcmpw __LIBC_LOCAL_NAME(memcmpw)
#endif /* !... */
#endif /* !__local___localdep_memcmpw_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/byteorder.h>
#include <hybrid/host.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memcmpc) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memcmpc))(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) {
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
	switch (__elem_size) {

	case 1:
		return (__NAMESPACE_LOCAL_SYM __localdep_memcmp)(__s1, __s2, __elem_count);

	case 2:
		return (__NAMESPACE_LOCAL_SYM __localdep_memcmpw)(__s1, __s2, __elem_count);

	case 4:
		return (__NAMESPACE_LOCAL_SYM __localdep_memcmpl)(__s1, __s2, __elem_count);

	case 8:
		return (__NAMESPACE_LOCAL_SYM __localdep_memcmpq)(__s1, __s2, __elem_count);

	default:
		break;
	}
#endif /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (__NAMESPACE_LOCAL_SYM __localdep_memcmp)(__s1, __s2, __elem_count * __elem_size);
#else /* __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ */
	/* Complicated case: we must compare elem_size-large unsigned integers,
	 * but because host endian is LITTLE, we can't just compare bytes  from
	 * lowest address -> highest address (because the most significant byte
	 * comes last in a LITTLE-ENDIAN data-word) */
	while (__elem_count--) {
		__SIZE_TYPE__ __i;
		__BYTE_TYPE__ const *__s1_iter, *__s2_iter;
		__s1      = (__BYTE_TYPE__ const *)__s1 + __elem_size;
		__s2      = (__BYTE_TYPE__ const *)__s2 + __elem_size;
		__s1_iter = (__BYTE_TYPE__ const *)__s1;
		__s2_iter = (__BYTE_TYPE__ const *)__s2;
		__i = __elem_size;
		while (__i--) {
			__BYTE_TYPE__ __v1, __v2;
			__v1 = *--__s1_iter;
			__v2 = *--__s2_iter;
			if (__v1 != __v2) {
#if __SIZEOF_INT__ >= 2
				return (int)(unsigned int)__v1 -
				       (int)(unsigned int)__v2;
#else /* __SIZEOF_INT__ >= 2 */
				return __v1 < __v2 ? -1 : 1;
#endif /* __SIZEOF_INT__ < 2 */
			}
		}
	}
	return 0;
#endif /* __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memcmpc_defined
#define __local___localdep_memcmpc_defined
#define __localdep_memcmpc __LIBC_LOCAL_NAME(memcmpc)
#endif /* !__local___localdep_memcmpc_defined */
#endif /* !__local_memcmpc_defined */
