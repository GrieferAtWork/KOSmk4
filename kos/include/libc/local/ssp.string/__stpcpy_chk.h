/* HASH CRC-32:0xffe0d84f */
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
#ifndef __local___stpcpy_chk_defined
#define __local___stpcpy_chk_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_stpcpy_defined
#define __local___localdep_stpcpy_defined
#if __has_builtin(__builtin_stpcpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_stpcpy)
__CEIREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_stpcpy,(char *__restrict __buf, char const *__restrict __src),stpcpy,{ return __builtin_stpcpy(__buf, __src); })
#elif defined(__CRT_HAVE_stpcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_stpcpy,(char *__restrict __buf, char const *__restrict __src),stpcpy,(__buf,__src))
#elif defined(__CRT_HAVE___stpcpy)
__CREDIRECT(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUT(1),char *,__NOTHROW_NCX,__localdep_stpcpy,(char *__restrict __buf, char const *__restrict __src),__stpcpy,(__buf,__src))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/stpcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_stpcpy __LIBC_LOCAL_NAME(stpcpy)
#endif /* !... */
#endif /* !__local___localdep_stpcpy_defined */
__NAMESPACE_LOCAL_END
#include <ssp/chk.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__stpcpy_chk) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__stpcpy_chk))(char *__restrict __dst, char const *__restrict __src, __SIZE_TYPE__ __dst_objsize) {
	(void)__dst_objsize; /* TODO */;
	return (__NAMESPACE_LOCAL_SYM __localdep_stpcpy)(__dst, __src);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___stpcpy_chk_defined
#define __local___localdep___stpcpy_chk_defined
#define __localdep___stpcpy_chk __LIBC_LOCAL_NAME(__stpcpy_chk)
#endif /* !__local___localdep___stpcpy_chk_defined */
#endif /* !__local___stpcpy_chk_defined */
