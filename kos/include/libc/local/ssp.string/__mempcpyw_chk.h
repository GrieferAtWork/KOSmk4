/* HASH CRC-32:0x8a4a251f */
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
#ifndef __local___mempcpyw_chk_defined
#define __local___mempcpyw_chk_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempcpyw_defined
#define __local___localdep_mempcpyw_defined
#ifdef __CRT_HAVE_mempcpyw
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),mempcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempcpy) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmempcpy,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempcpy) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_mempcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmempcpy,(__dst,__src,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpyw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpyw __LIBC_LOCAL_NAME(mempcpyw)
#endif /* !... */
#endif /* !__local___localdep_mempcpyw_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mempcpyw_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mempcpyw_chk))(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) {
	__ssp_chk_dstbuf("mempcpyw", __dst, __n_words * 2, __dst_objsize);
	return (__NAMESPACE_LOCAL_SYM __localdep_mempcpyw)(__dst, __src, __n_words);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___mempcpyw_chk_defined
#define __local___localdep___mempcpyw_chk_defined
#define __localdep___mempcpyw_chk __LIBC_LOCAL_NAME(__mempcpyw_chk)
#endif /* !__local___localdep___mempcpyw_chk_defined */
#endif /* !__local___mempcpyw_chk_defined */
