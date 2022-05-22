/* HASH CRC-32:0x9cdb662 */
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
#ifndef __local_argz_next_defined
#define __local_argz_next_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__LOCAL_LIBC(argz_next) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_IN_OPT(3) __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(argz_next))(char const *__restrict __argz, __SIZE_TYPE__ __argz_len, char const *__restrict __entry) {
	char const *__argz_end;
	if (!__entry)
		return __argz_len ? (char *)__argz : __NULLPTR;
	__argz_end = __argz + __argz_len;
	if (__entry < __argz_end)
		__entry = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__entry) + 1;
	if (__entry >= __argz_end)
		return __NULLPTR;
	return (char *)__entry;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_argz_next_defined
#define __local___localdep_argz_next_defined
#define __localdep_argz_next __LIBC_LOCAL_NAME(argz_next)
#endif /* !__local___localdep_argz_next_defined */
#endif /* !__local_argz_next_defined */
