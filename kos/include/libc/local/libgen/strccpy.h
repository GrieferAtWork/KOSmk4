/* HASH CRC-32:0x88baaef7 */
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
#ifndef __local_strccpy_defined
#define __local_strccpy_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strcadd_defined
#define __local___localdep_strcadd_defined
#ifdef __CRT_HAVE_strcadd
__CREDIRECT(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_strcadd,(char *__dstbuf, char const *__string),strcadd,(__dstbuf,__string))
#else /* __CRT_HAVE_strcadd */
__NAMESPACE_LOCAL_END
#include <libc/local/libgen/strcadd.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcadd __LIBC_LOCAL_NAME(strcadd)
#endif /* !__CRT_HAVE_strcadd */
#endif /* !__local___localdep_strcadd_defined */
__LOCAL_LIBC(strccpy) __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strccpy))(char *__dstbuf, char const *__string) {
	(__NAMESPACE_LOCAL_SYM __localdep_strcadd)(__dstbuf, __string);
	return __dstbuf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strccpy_defined
#define __local___localdep_strccpy_defined
#define __localdep_strccpy __LIBC_LOCAL_NAME(strccpy)
#endif /* !__local___localdep_strccpy_defined */
#endif /* !__local_strccpy_defined */
