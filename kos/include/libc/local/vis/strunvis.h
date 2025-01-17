/* HASH CRC-32:0x8d321d04 */
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
#ifndef __local_strunvis_defined
#define __local_strunvis_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strnunvis_defined
#define __local___localdep_strnunvis_defined
#if defined(__CRT_HAVE_strnunvis) && !defined(__CRT_NETBSD)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUTS(1, 3),int,__NOTHROW_NCX,__localdep_strnunvis,(char *__dst, char const *__src, __SIZE_TYPE__ __dstsize),strnunvis,(__dst,__src,__dstsize))
#else /* __CRT_HAVE_strnunvis && !__CRT_NETBSD */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/strnunvis.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strnunvis __LIBC_LOCAL_NAME(strnunvis)
#endif /* !__CRT_HAVE_strnunvis || __CRT_NETBSD */
#endif /* !__local___localdep_strnunvis_defined */
#ifndef __local___localdep_strnunvis_netbsd_defined
#define __local___localdep_strnunvis_netbsd_defined
#if defined(__CRT_HAVE_strnunvis) && defined(__CRT_NETBSD)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,__localdep_strnunvis_netbsd,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src),strnunvis,(__dst,__dstsize,__src))
#elif defined(__CRT_HAVE_strnunvis_netbsd)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,__localdep_strnunvis_netbsd,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src),strnunvis_netbsd,(__dst,__dstsize,__src))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/strnunvis_netbsd.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strnunvis_netbsd __LIBC_LOCAL_NAME(strnunvis_netbsd)
#endif /* !... */
#endif /* !__local___localdep_strnunvis_netbsd_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strunvis) __ATTR_IN(2) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strunvis))(char *__dst, char const *__src) {

	return (__NAMESPACE_LOCAL_SYM __localdep_strnunvis)(__dst, __src, (__SIZE_TYPE__)-1);



}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strunvis_defined
#define __local___localdep_strunvis_defined
#define __localdep_strunvis __LIBC_LOCAL_NAME(strunvis)
#endif /* !__local___localdep_strunvis_defined */
#endif /* !__local_strunvis_defined */
