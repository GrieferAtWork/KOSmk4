/* HASH CRC-32:0xb2afc6b2 */
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
#ifndef __local_strsvis_defined
#define __local_strsvis_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strsnvis_defined
#define __local___localdep_strsnvis_defined
#ifdef __CRT_HAVE_strsnvis
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(5) __ATTR_IN_OPT(3) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,__localdep_strsnvis,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, int __flags, char const *__mbextra),strsnvis,(__dst,__dstsize,__src,__flags,__mbextra))
#else /* __CRT_HAVE_strsnvis */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/strsnvis.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strsnvis __LIBC_LOCAL_NAME(strsnvis)
#endif /* !__CRT_HAVE_strsnvis */
#endif /* !__local___localdep_strsnvis_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strsvis) __ATTR_IN(4) __ATTR_IN_OPT(2) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strsvis))(char *__dst, char const *__src, int __flags, char const *__mbextra) {
	return (__NAMESPACE_LOCAL_SYM __localdep_strsnvis)(__dst, (__SIZE_TYPE__)-1, __src, __flags, __mbextra);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strsvis_defined
#define __local___localdep_strsvis_defined
#define __localdep_strsvis __LIBC_LOCAL_NAME(strsvis)
#endif /* !__local___localdep_strsvis_defined */
#endif /* !__local_strsvis_defined */
