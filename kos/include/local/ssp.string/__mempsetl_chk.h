/* HASH CRC-32:0x69e63e19 */
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
#ifndef __local___mempsetl_chk_defined
#define __local___mempsetl_chk_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mempsetl from string */
#ifndef __local___localdep_mempsetl_defined
#define __local___localdep_mempsetl_defined 1
#ifdef __CRT_HAVE_mempsetl
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),mempsetl,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 4
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmempset,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempset) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmempset,(__dst,__dword,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/mempsetl.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memsetl', but return `DST + N_DWORDS', rather than `DST' */
#define __localdep_mempsetl __LIBC_LOCAL_NAME(mempsetl)
#endif /* !... */
#endif /* !__local___localdep_mempsetl_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mempsetl_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) __UINT32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mempsetl_chk))(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords, __SIZE_TYPE__ __dst_objsize) {
	__ssp_chk_dstbuf("mempsetl", __dst, __n_dwords * 4, __dst_objsize);
	return __localdep_mempsetl(__dst, __dword, __n_dwords);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___mempsetl_chk_defined
#define __local___localdep___mempsetl_chk_defined 1
#define __localdep___mempsetl_chk __LIBC_LOCAL_NAME(__mempsetl_chk)
#endif /* !__local___localdep___mempsetl_chk_defined */
#endif /* !__local___mempsetl_chk_defined */
