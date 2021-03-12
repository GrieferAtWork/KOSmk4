/* HASH CRC-32:0xdc4d4171 */
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
#ifndef __local___mempmovew_chk_defined
#define __local___mempmovew_chk_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mempmovew from string */
#ifndef __local___localdep_mempmovew_defined
#define __local___localdep_mempmovew_defined 1
#ifdef __CRT_HAVE_mempmovew
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),mempmovew,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmempmove) && __SIZEOF_WCHAR_T__ == 2
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),wmempmove,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmempmove) && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_mempmovew,(void *__dst, void const *__src, __SIZE_TYPE__ __n_words),DOS$wmempmove,(__dst,__src,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempmovew.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memmovew', but return `dst + N_WORDS', rather than `dst' */
#define __localdep_mempmovew __LIBC_LOCAL_NAME(mempmovew)
#endif /* !... */
#endif /* !__local___localdep_mempmovew_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mempmovew_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __UINT16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mempmovew_chk))(void *__dst, void const *__src, __SIZE_TYPE__ __n_words, __SIZE_TYPE__ __dst_objsize) {
	__ssp_chk_dstbuf("mempmovew", __dst, __n_words * 2, __dst_objsize);
	return __localdep_mempmovew(__dst, __src, __n_words);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___mempmovew_chk_defined
#define __local___localdep___mempmovew_chk_defined 1
#define __localdep___mempmovew_chk __LIBC_LOCAL_NAME(__mempmovew_chk)
#endif /* !__local___localdep___mempmovew_chk_defined */
#endif /* !__local___mempmovew_chk_defined */
