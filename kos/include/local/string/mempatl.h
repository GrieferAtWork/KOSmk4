/* HASH CRC-32:0xb0516bb4 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_mempatl_defined
#define __local_mempatl_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <hybrid/__wordbits.h>
/* Dependency: "mempsetl" from "string" */
#ifndef ____localdep_mempsetl_defined
#define ____localdep_mempsetl_defined 1
#ifdef __fast_mempsetl_defined
/* Same as `memsetl', but return `DST+N_DWORDS', rather than `DST' */
#define __localdep_mempsetl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempsetl))
#elif defined(__CRT_HAVE_mempsetl)
/* Same as `memsetl', but return `DST+N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),mempsetl,(__dst,__dword,__n_dwords))
#else /* LIBC: mempsetl */
#include <local/string/mempsetl.h>
/* Same as `memsetl', but return `DST+N_DWORDS', rather than `DST' */
#define __localdep_mempsetl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetl))
#endif /* mempsetl... */
#endif /* !____localdep_mempsetl_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `memsetl', but repeat a 4-byte pattern on aligned addresses. */
__LOCAL_LIBC(mempatl) __ATTR_RETNONNULL __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempatl))(void *__restrict __dst,
                                                     __UINT32_TYPE__ __pattern,
                                                     __SIZE_TYPE__ __n_bytes) {
#line 2434 "kos/src/libc/magic/string.c"
	__BYTE_TYPE__ *__iter = (__BYTE_TYPE__ *)__dst;
	for (; __n_bytes && (__UINTPTR_TYPE__)__iter & 3; ++__iter, --__n_bytes)
		*__iter = __INT32_BYTE(__pattern, (__UINTPTR_TYPE__)__iter & 3);
	__iter = (__BYTE_TYPE__ *)__localdep_mempsetl(__iter, __pattern, __n_bytes / 4);
	for (__n_bytes &= 3; __n_bytes; ++__iter, --__n_bytes)
		*__iter = __INT32_BYTE(__pattern, (__UINTPTR_TYPE__)__iter & 3);
	return __dst;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_mempatl_defined */
