/* HASH CRC-32:0x26816520 */
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
#ifndef __local_svis_defined
#define __local_svis_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_snvis_defined
#define __local___localdep_snvis_defined
#ifdef __CRT_HAVE_snvis
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(6) __ATTR_OUTS(1, 2),char *,__NOTHROW_NCX,__localdep_snvis,(char *__dst, __SIZE_TYPE__ __dstsize, int __c, int __flags, int __nextc, char const *__mbextra),snvis,(__dst,__dstsize,__c,__flags,__nextc,__mbextra))
#else /* __CRT_HAVE_snvis */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/snvis.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_snvis __LIBC_LOCAL_NAME(snvis)
#endif /* !__CRT_HAVE_snvis */
#endif /* !__local___localdep_snvis_defined */
__LOCAL_LIBC(svis) __ATTR_IN(5) __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(svis))(char *__dst, int __c, int __flags, int __nextc, char const *__mbextra) {
	return (__NAMESPACE_LOCAL_SYM __localdep_snvis)(__dst, 5, __c, __flags, __nextc, __mbextra);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_svis_defined
#define __local___localdep_svis_defined
#define __localdep_svis __LIBC_LOCAL_NAME(svis)
#endif /* !__local___localdep_svis_defined */
#endif /* !__local_svis_defined */
