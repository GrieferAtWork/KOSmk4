/* HASH CRC-32:0xe074f3bc */
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
#ifndef __local_strsnvisx_defined
#define __local_strsnvisx_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strsenvisx_defined
#define __local___localdep_strsenvisx_defined
#ifdef __CRT_HAVE_strsenvisx
__CREDIRECT(__ATTR_IN(6) __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,__localdep_strsenvisx,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __srclen, int __flags, char const *__mbextra, int *__cerr_ptr),strsenvisx,(__dst,__dstsize,__src,__srclen,__flags,__mbextra,__cerr_ptr))
#else /* __CRT_HAVE_strsenvisx */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/strsenvisx.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strsenvisx __LIBC_LOCAL_NAME(strsenvisx)
#endif /* !__CRT_HAVE_strsenvisx */
#endif /* !__local___localdep_strsenvisx_defined */
__LOCAL_LIBC(strsnvisx) __ATTR_IN(6) __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strsnvisx))(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __srclen, int __flags, char const *__mbextra) {
	return (__NAMESPACE_LOCAL_SYM __localdep_strsenvisx)(__dst, __dstsize, __src, __srclen, __flags, __mbextra, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strsnvisx_defined
#define __local___localdep_strsnvisx_defined
#define __localdep_strsnvisx __LIBC_LOCAL_NAME(strsnvisx)
#endif /* !__local___localdep_strsnvisx_defined */
#endif /* !__local_strsnvisx_defined */
