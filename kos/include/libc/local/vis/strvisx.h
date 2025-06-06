/* HASH CRC-32:0x276c3b40 */
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
#ifndef __local_strvisx_defined
#define __local_strvisx_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strnvisx_defined
#define __local___localdep_strnvisx_defined
#ifdef __CRT_HAVE_strnvisx
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,__localdep_strnvisx,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __srclen, int __flags),strnvisx,(__dst,__dstsize,__src,__srclen,__flags))
#else /* __CRT_HAVE_strnvisx */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/strnvisx.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strnvisx __LIBC_LOCAL_NAME(strnvisx)
#endif /* !__CRT_HAVE_strnvisx */
#endif /* !__local___localdep_strnvisx_defined */
__LOCAL_LIBC(strvisx) __ATTR_INS(2, 3) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strvisx))(char *__dst, char const *__src, __SIZE_TYPE__ __srclen, int __flags) {
	return (__NAMESPACE_LOCAL_SYM __localdep_strnvisx)(__dst, (__SIZE_TYPE__)-1, __src, __srclen, __flags);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strvisx_defined
#define __local___localdep_strvisx_defined
#define __localdep_strvisx __LIBC_LOCAL_NAME(strvisx)
#endif /* !__local___localdep_strvisx_defined */
#endif /* !__local_strvisx_defined */
