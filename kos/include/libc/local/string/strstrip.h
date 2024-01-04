/* HASH CRC-32:0xc2ca3c68 */
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
#ifndef __local_strstrip_defined
#define __local_strstrip_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strlstrip_defined
#define __local___localdep_strlstrip_defined
#ifdef __CRT_HAVE_strlstrip
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strlstrip,(char const *__str),strlstrip,(__str))
#else /* __CRT_HAVE_strlstrip */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlstrip.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlstrip __LIBC_LOCAL_NAME(strlstrip)
#endif /* !__CRT_HAVE_strlstrip */
#endif /* !__local___localdep_strlstrip_defined */
#ifndef __local___localdep_strrstrip_defined
#define __local___localdep_strrstrip_defined
#ifdef __CRT_HAVE_strrstrip
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strrstrip,(char *__str),strrstrip,(__str))
#else /* __CRT_HAVE_strrstrip */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strrstrip.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strrstrip __LIBC_LOCAL_NAME(strrstrip)
#endif /* !__CRT_HAVE_strrstrip */
#endif /* !__local___localdep_strrstrip_defined */
__LOCAL_LIBC(strstrip) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strstrip))(char *__str) {
	__str = (__NAMESPACE_LOCAL_SYM __localdep_strlstrip)(__str);
	__str = (__NAMESPACE_LOCAL_SYM __localdep_strrstrip)(__str);
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strstrip_defined
#define __local___localdep_strstrip_defined
#define __localdep_strstrip __LIBC_LOCAL_NAME(strstrip)
#endif /* !__local___localdep_strstrip_defined */
#endif /* !__local_strstrip_defined */
