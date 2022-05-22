/* HASH CRC-32:0xac9a2f0f */
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
#ifndef __local_strecpy_defined
#define __local_strecpy_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_streadd_defined
#define __local___localdep_streadd_defined
#ifdef __CRT_HAVE_streadd
__CREDIRECT(__ATTR_RETNONNULL __ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_ACCESS_WR(1),char *,__NOTHROW_NCX,__localdep_streadd,(char *__dstbuf, char const *__string, char const *__dont_encode),streadd,(__dstbuf,__string,__dont_encode))
#else /* __CRT_HAVE_streadd */
__NAMESPACE_LOCAL_END
#include <libc/local/libgen/streadd.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_streadd __LIBC_LOCAL_NAME(streadd)
#endif /* !__CRT_HAVE_streadd */
#endif /* !__local___localdep_streadd_defined */
__LOCAL_LIBC(strecpy) __ATTR_RETNONNULL __ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO_OPT(3) __ATTR_ACCESS_WR(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strecpy))(char *__dstbuf, char const *__string, char const *__dont_encode) {
	(__NAMESPACE_LOCAL_SYM __localdep_streadd)(__dstbuf, __string, __dont_encode);
	return __dstbuf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strecpy_defined
#define __local___localdep_strecpy_defined
#define __localdep_strecpy __LIBC_LOCAL_NAME(strecpy)
#endif /* !__local___localdep_strecpy_defined */
#endif /* !__local_strecpy_defined */
