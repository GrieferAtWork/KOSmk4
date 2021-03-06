/* HASH CRC-32:0xff635b8f */
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
#ifndef __local_consttime_memequal_defined
#define __local_consttime_memequal_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: timingsafe_memcmp from string */
#ifndef __local___localdep_timingsafe_memcmp_defined
#define __local___localdep_timingsafe_memcmp_defined 1
#ifdef __CRT_HAVE_timingsafe_memcmp
/* >> timingsafe_memcmp(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: <  0: Block `s1' should be considered less than `s2'
 * @return: == 0: Memory blocks are equal.
 * @return: >  0: Block `s1' should be considered greater than `s2' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_timingsafe_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),timingsafe_memcmp,(__s1,__s2,__n_bytes))
#else /* __CRT_HAVE_timingsafe_memcmp */
__NAMESPACE_LOCAL_END
#include <libc/local/string/timingsafe_memcmp.h>
__NAMESPACE_LOCAL_BEGIN
/* >> timingsafe_memcmp(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: <  0: Block `s1' should be considered less than `s2'
 * @return: == 0: Memory blocks are equal.
 * @return: >  0: Block `s1' should be considered greater than `s2' */
#define __localdep_timingsafe_memcmp __LIBC_LOCAL_NAME(timingsafe_memcmp)
#endif /* !__CRT_HAVE_timingsafe_memcmp */
#endif /* !__local___localdep_timingsafe_memcmp_defined */
/* >> consttime_memequal(3)
 * Compare `s1...+=n_bytes' with `s2...+=n_bytes' in constant, armored `O(n_bytes)'-time
 * @return: == 0: Memory blocks are non-equal.
 * @return: != 0: Memory blocks are equal. */
__LOCAL_LIBC(consttime_memequal) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(consttime_memequal))(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes) {
	return __localdep_timingsafe_memcmp(__s1, __s2, __n_bytes) == 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_consttime_memequal_defined
#define __local___localdep_consttime_memequal_defined 1
#define __localdep_consttime_memequal __LIBC_LOCAL_NAME(consttime_memequal)
#endif /* !__local___localdep_consttime_memequal_defined */
#endif /* !__local_consttime_memequal_defined */
