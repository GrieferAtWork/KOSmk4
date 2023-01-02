/* HASH CRC-32:0xb134f4f7 */
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
#ifndef __local_mempatw_defined
#define __local_mempatw_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempsetw_defined
#define __local___localdep_mempsetw_defined
#ifdef __CRT_HAVE_mempsetw
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),mempsetw,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmempset,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempset) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_mempsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmempset,(__dst,__word,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempsetw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempsetw __LIBC_LOCAL_NAME(mempsetw)
#endif /* !... */
#endif /* !__local___localdep_mempsetw_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/__wordbits.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(mempatw) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mempatw))(void *__restrict __dst, __UINT16_TYPE__ __pattern, __SIZE_TYPE__ __n_bytes) {
	__BYTE_TYPE__ *__iter = (__BYTE_TYPE__ *)__dst;
	if (__n_bytes && (__UINTPTR_TYPE__)__iter & 1) {
		*__iter = __INT16_BYTE(__pattern, 1);
		++__iter;
		--__n_bytes;
	}
	__iter = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_mempsetw)(__iter, __pattern, __n_bytes / 2);
	if (__n_bytes & 1)
		*__iter = __INT16_BYTE(__pattern, 0);
	return __dst;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mempatw_defined
#define __local___localdep_mempatw_defined
#define __localdep_mempatw __LIBC_LOCAL_NAME(mempatw)
#endif /* !__local___localdep_mempatw_defined */
#endif /* !__local_mempatw_defined */
