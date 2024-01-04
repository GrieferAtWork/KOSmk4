/* HASH CRC-32:0xd344ae07 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_mempatq_defined
#define __local_mempatq_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempsetq_defined
#define __local___localdep_mempsetq_defined
#ifdef __CRT_HAVE_mempsetq
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetq,(void *__restrict __dst, __UINT64_TYPE__ __qword, __SIZE_TYPE__ __n_qwords),mempsetq,(__dst,__qword,__n_qwords))
#else /* __CRT_HAVE_mempsetq */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempsetq.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempsetq __LIBC_LOCAL_NAME(mempsetq)
#endif /* !__CRT_HAVE_mempsetq */
#endif /* !__local___localdep_mempsetq_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__wordbits.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(mempatq) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempatq))(void *__restrict __dst, __UINT64_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) {
	__BYTE_TYPE__ *__iter = (__BYTE_TYPE__ *)__dst;
	for (; __n_bytes && (__UINTPTR_TYPE__)__iter & 7; ++__iter, --__n_bytes)
		*__iter = __INT64_BYTE(__pattern, (__UINTPTR_TYPE__)__iter & 7);
	__iter = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_mempsetq)(__iter, __pattern, __n_bytes / 8);
	for (__n_bytes &= 7; __n_bytes; ++__iter, --__n_bytes)
		*__iter = __INT64_BYTE(__pattern, (__UINTPTR_TYPE__)__iter & 7);
	return __dst;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mempatq_defined
#define __local___localdep_mempatq_defined
#define __localdep_mempatq __LIBC_LOCAL_NAME(mempatq)
#endif /* !__local___localdep_mempatq_defined */
#endif /* !__local_mempatq_defined */
