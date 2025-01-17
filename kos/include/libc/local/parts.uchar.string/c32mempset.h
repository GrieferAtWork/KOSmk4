/* HASH CRC-32:0xed709591 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32mempset_defined
#define __local_c32mempset_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempset_defined
#define __local___localdep_mempset_defined
#ifdef __CRT_HAVE_mempset
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_mempset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),mempset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_mempset */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempset __LIBC_LOCAL_NAME(mempset)
#endif /* !__CRT_HAVE_mempset */
#endif /* !__local___localdep_mempset_defined */
#ifndef __local___localdep_mempsetl_defined
#define __local___localdep_mempsetl_defined
#ifdef __CRT_HAVE_mempsetl
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),mempsetl,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmempset) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmempset,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmempset) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_mempsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmempset,(__dst,__dword,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempsetl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempsetl __LIBC_LOCAL_NAME(mempsetl)
#endif /* !... */
#endif /* !__local___localdep_mempsetl_defined */
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
__LOCAL_LIBC(c32mempset) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32mempset))(__CHAR32_TYPE__ *__dst, __CHAR32_TYPE__ __filler, __SIZE_TYPE__ __num_chars) {



	return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_mempsetl)(__dst, (__UINT32_TYPE__)__filler, __num_chars);



}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32mempset_defined
#define __local___localdep_c32mempset_defined
#define __localdep_c32mempset __LIBC_LOCAL_NAME(c32mempset)
#endif /* !__local___localdep_c32mempset_defined */
#endif /* !__local_c32mempset_defined */
