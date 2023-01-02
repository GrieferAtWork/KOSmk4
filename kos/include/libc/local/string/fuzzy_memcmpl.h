/* HASH CRC-32:0xbc930c7f */
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
#ifndef __local_fuzzy_memcmpl_defined
#define __local_fuzzy_memcmpl_defined
#include <__crt.h>
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcpyc_defined
#define __local___localdep_memcpyc_defined
#ifdef __CRT_HAVE_memcpyc
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpyc __LIBC_LOCAL_NAME(memcpyc)
#endif /* !__CRT_HAVE_memcpyc */
#endif /* !__local___localdep_memcpyc_defined */
__LOCAL_LIBC(fuzzy_memcmpl) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(3) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_memcmpl))(void const *__s1, __SIZE_TYPE__ __s1_dwords, void const *__s2, __SIZE_TYPE__ __s2_dwords) {
	__SIZE_TYPE__ *__v0, *__v1, __i, __j, __cost, __temp;
	if __unlikely(!__s1_dwords)
		return __s2_dwords;
	if __unlikely(!__s2_dwords)
		return __s1_dwords;
	if (__s2_dwords > __s1_dwords) {
		{
			void const *__temp;
			__temp = __s1;
			__s1   = __s2;
			__s2   = __temp;
		}
		{
			__SIZE_TYPE__ __temp;
			__temp      = __s1_dwords;
			__s1_dwords = __s2_dwords;
			__s2_dwords = __temp;
		}
	}
	__malloca_tryhard(__v0, (__s2_dwords+1) * sizeof(__SIZE_TYPE__));
#ifdef __malloca_tryhard_mayfail
	if __unlikely(!__v0)
		return (__SIZE_TYPE__)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(__v1, (__s2_dwords+1) * sizeof(__SIZE_TYPE__));
#ifdef __malloca_tryhard_mayfail
	if __unlikely(!__v1) {
		__freea(__v0);
		return (__SIZE_TYPE__)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (__i = 0; __i < __s2_dwords; ++__i)
		__v0[__i] = __i;
	for (__i = 0; __i < __s1_dwords; ++__i) {
		__v1[0] = __i + 1;
		for (__j = 0; __j < __s2_dwords; __j++) {
			__cost  = ((__UINT32_TYPE__ *)__s1)[__i] != ((__UINT32_TYPE__ *)__s2)[__j];
			__cost += __v0[__j];
			__temp  = __v1[__j] + 1;
			if (__cost > __temp)
				__cost = __temp;
			__temp  = __v0[__j + 1] + 1;
			if (__cost > __temp)
				__cost = __temp;
			__v1[__j + 1] = __cost;
		}
		(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__v0, __v1, __s2_dwords, sizeof(__SIZE_TYPE__));
	}
	__temp = __v1[__s2_dwords];
	__freea(__v1);
	__freea(__v0);
	return __temp;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fuzzy_memcmpl_defined
#define __local___localdep_fuzzy_memcmpl_defined
#define __localdep_fuzzy_memcmpl __LIBC_LOCAL_NAME(fuzzy_memcmpl)
#endif /* !__local___localdep_fuzzy_memcmpl_defined */
#else /* !__NO_MALLOCA */
#undef __local_fuzzy_memcmpl_defined
#endif /* __NO_MALLOCA */
#endif /* !__local_fuzzy_memcmpl_defined */
