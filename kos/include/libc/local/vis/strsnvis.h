/* HASH CRC-32:0x6c8811e1 */
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
#ifndef __local_strsnvis_defined
#define __local_strsnvis_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
#ifndef __local___localdep_strsnvisx_defined
#define __local___localdep_strsnvisx_defined
#ifdef __CRT_HAVE_strsnvisx
__CREDIRECT(__ATTR_IN(6) __ATTR_INS(3, 4) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,__localdep_strsnvisx,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __srclen, int __flags, char const *__mbextra),strsnvisx,(__dst,__dstsize,__src,__srclen,__flags,__mbextra))
#else /* __CRT_HAVE_strsnvisx */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/strsnvisx.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strsnvisx __LIBC_LOCAL_NAME(strsnvisx)
#endif /* !__CRT_HAVE_strsnvisx */
#endif /* !__local___localdep_strsnvisx_defined */
__LOCAL_LIBC(strsnvis) __ATTR_IN(5) __ATTR_IN_OPT(3) __ATTR_OUTS(1, 2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strsnvis))(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, int __flags, char const *__mbextra) {
	return (__NAMESPACE_LOCAL_SYM __localdep_strsnvisx)(__dst, __dstsize, __src, __src ? (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__src) : 0, __flags, __mbextra);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strsnvis_defined
#define __local___localdep_strsnvis_defined
#define __localdep_strsnvis __LIBC_LOCAL_NAME(strsnvis)
#endif /* !__local___localdep_strsnvis_defined */
#endif /* !__local_strsnvis_defined */
