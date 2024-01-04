/* HASH CRC-32:0x46d93993 */
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
#ifndef __local_vis_defined
#define __local_vis_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_nvis_defined
#define __local___localdep_nvis_defined
#ifdef __CRT_HAVE_nvis
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUTS(1, 2),char *,__NOTHROW_NCX,__localdep_nvis,(char *__dst, __SIZE_TYPE__ __dstsize, int __c, int __flags, int __nextc),nvis,(__dst,__dstsize,__c,__flags,__nextc))
#else /* __CRT_HAVE_nvis */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/nvis.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_nvis __LIBC_LOCAL_NAME(nvis)
#endif /* !__CRT_HAVE_nvis */
#endif /* !__local___localdep_nvis_defined */
__LOCAL_LIBC(vis) __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vis))(char *__dst, int __c, int __flags, int __nextc) {
	return (__NAMESPACE_LOCAL_SYM __localdep_nvis)(__dst, 5, __c, __flags, __nextc);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vis_defined
#define __local___localdep_vis_defined
#define __localdep_vis __LIBC_LOCAL_NAME(vis)
#endif /* !__local___localdep_vis_defined */
#endif /* !__local_vis_defined */
