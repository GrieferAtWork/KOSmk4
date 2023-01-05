/* HASH CRC-32:0xd42df438 */
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
#ifndef __local_strnvisx_defined
#define __local_strnvisx_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strenvisx_defined
#define __local___localdep_strenvisx_defined
#ifdef __CRT_HAVE_strenvisx
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_OUTS(1, 2) __ATTR_OUT_OPT(6),int,__NOTHROW_NCX,__localdep_strenvisx,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __srclen, int __flags, int *__cerr_ptr),strenvisx,(__dst,__dstsize,__src,__srclen,__flags,__cerr_ptr))
#else /* __CRT_HAVE_strenvisx */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/strenvisx.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strenvisx __LIBC_LOCAL_NAME(strenvisx)
#endif /* !__CRT_HAVE_strenvisx */
#endif /* !__local___localdep_strenvisx_defined */
__LOCAL_LIBC(strnvisx) __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnvisx))(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __srclen, int __flags) {
	return (__NAMESPACE_LOCAL_SYM __localdep_strenvisx)(__dst, __dstsize, __src, __srclen, __flags, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strnvisx_defined
#define __local___localdep_strnvisx_defined
#define __localdep_strnvisx __LIBC_LOCAL_NAME(strnvisx)
#endif /* !__local___localdep_strnvisx_defined */
#endif /* !__local_strnvisx_defined */
