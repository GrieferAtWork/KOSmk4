/* HASH CRC-32:0x3c870155 */
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
#ifndef __local_bzerow_defined
#define __local_bzerow_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memsetw_defined
#define __local___localdep_memsetw_defined
#ifdef __CRT_HAVE_memsetw
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),memsetw,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_wmemset) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),wmemset,(__dst,__word,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemset) && defined(__LIBCCALL_IS_LIBDCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_ACCESS_WR(1),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memsetw,(void *__restrict __dst, __UINT16_TYPE__ __word, __SIZE_TYPE__ __n_words),DOS$wmemset,(__dst,__word,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memsetw.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memsetw __LIBC_LOCAL_NAME(memsetw)
#endif /* !... */
#endif /* !__local___localdep_memsetw_defined */
__LOCAL_LIBC(bzerow) __ATTR_LEAF __ATTR_ACCESS_WR(1) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(bzerow))(void *__restrict __dst, __SIZE_TYPE__ __num_words) {
	(__NAMESPACE_LOCAL_SYM __localdep_memsetw)(__dst, 0, __num_words);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_bzerow_defined
#define __local___localdep_bzerow_defined
#define __localdep_bzerow __LIBC_LOCAL_NAME(bzerow)
#endif /* !__local___localdep_bzerow_defined */
#endif /* !__local_bzerow_defined */
