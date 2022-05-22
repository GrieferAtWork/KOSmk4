/* HASH CRC-32:0x38b3b1c9 */
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
#ifndef __local_memrevq_defined
#define __local_memrevq_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memrevq) __ATTR_LEAF __ATTR_INOUT(1) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrevq))(void *__restrict __base, __SIZE_TYPE__ __n_qwords) {
	__UINT64_TYPE__ *__iter, *__end;
	__end = (__iter = (__UINT64_TYPE__ *)__base) + __n_qwords;
	while (__iter < __end) {
		__UINT64_TYPE__ __temp = *__iter;
		*__iter++ = *--__end;
		*__end = __temp;
	}
	return (__UINT64_TYPE__ *)__base;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memrevq_defined
#define __local___localdep_memrevq_defined
#define __localdep_memrevq __LIBC_LOCAL_NAME(memrevq)
#endif /* !__local___localdep_memrevq_defined */
#endif /* !__local_memrevq_defined */
