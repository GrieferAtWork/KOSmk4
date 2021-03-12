/* HASH CRC-32:0x8411dfa9 */
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
#ifndef __local_mempsetq_defined
#define __local_mempsetq_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memsetq from string */
#ifndef __local___localdep_memsetq_defined
#define __local___localdep_memsetq_defined 1
#ifdef __CRT_HAVE_memsetq
/* Fill memory with a given qword */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),memsetq,(__dst,__qword,__n_qwords))
#else /* __CRT_HAVE_memsetq */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memsetq.h>
__NAMESPACE_LOCAL_BEGIN
/* Fill memory with a given qword */
#define __localdep_memsetq __LIBC_LOCAL_NAME(memsetq)
#endif /* !__CRT_HAVE_memsetq */
#endif /* !__local___localdep_memsetq_defined */
/* Same as `memsetq', but return `dst + n_qwords', rather than `dst' */
__LOCAL_LIBC(mempsetq) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT64_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempsetq))(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords) {
	return (__UINT64_TYPE__ *)__localdep_memsetq(__dst, __qword, __n_qwords) + __n_qwords;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mempsetq_defined
#define __local___localdep_mempsetq_defined 1
#define __localdep_mempsetq __LIBC_LOCAL_NAME(mempsetq)
#endif /* !__local___localdep_mempsetq_defined */
#endif /* !__local_mempsetq_defined */
