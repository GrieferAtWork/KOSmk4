/* HASH CRC-32:0x37bfd19b */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strvis_defined
#define __local_strvis_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strnvis_defined
#define __local___localdep_strnvis_defined
#if defined(__CRT_HAVE_strnvis) && !defined(__CRT_NETBSD)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(1, 3),int,__NOTHROW_NCX,__localdep_strnvis,(char *__dst, char const *__src, __SIZE_TYPE__ __dstsize, int __flags),strnvis,(__dst,__src,__dstsize,__flags))
#else /* __CRT_HAVE_strnvis && !__CRT_NETBSD */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/strnvis.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strnvis __LIBC_LOCAL_NAME(strnvis)
#endif /* !__CRT_HAVE_strnvis || __CRT_NETBSD */
#endif /* !__local___localdep_strnvis_defined */
#ifndef __local___localdep_strnvis_netbsd_defined
#define __local___localdep_strnvis_netbsd_defined
#if defined(__CRT_HAVE_strnvis) && defined(__CRT_NETBSD)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(1, 2),int,__NOTHROW_NCX,__localdep_strnvis_netbsd,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, int __flags),strnvis,(__dst,__dstsize,__src,__flags))
#elif defined(__CRT_HAVE_strnvis_netbsd)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(1, 2),int,__NOTHROW_NCX,__localdep_strnvis_netbsd,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, int __flags),strnvis_netbsd,(__dst,__dstsize,__src,__flags))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/strnvis_netbsd.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strnvis_netbsd __LIBC_LOCAL_NAME(strnvis_netbsd)
#endif /* !... */
#endif /* !__local___localdep_strnvis_netbsd_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strvis) __ATTR_IN(2) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strvis))(char *__dst, char const *__src, int __flags) {

	return (__NAMESPACE_LOCAL_SYM __localdep_strnvis)(__dst, __src, (__SIZE_TYPE__)-1, __flags);



}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strvis_defined
#define __local___localdep_strvis_defined
#define __localdep_strvis __LIBC_LOCAL_NAME(strvis)
#endif /* !__local___localdep_strvis_defined */
#endif /* !__local_strvis_defined */
