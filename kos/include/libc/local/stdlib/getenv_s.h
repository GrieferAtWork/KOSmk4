/* HASH CRC-32:0xd26bcc24 */
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
#ifndef __local_getenv_s_defined
#define __local_getenv_s_defined
#include <__crt.h>
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getenv_defined
#define __local___localdep_getenv_defined
#ifdef __CRT_HAVE_getenv
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_getenv,(char const *__varname),getenv,(__varname))
#elif defined(__LOCAL_environ)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/getenv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getenv __LIBC_LOCAL_NAME(getenv)
#else /* ... */
#undef __local___localdep_getenv_defined
#endif /* !... */
#endif /* !__local___localdep_getenv_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getenv_s) __ATTR_IN(4) __ATTR_OUT(1) __ATTR_OUTS(2, 3) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getenv_s))(__SIZE_TYPE__ *__preqsize, char *__buf, __SIZE_TYPE__ __bufsize, char const *__varname) {
	__SIZE_TYPE__ __reqsize;
	char *__name = (__NAMESPACE_LOCAL_SYM __localdep_getenv)(__varname);
	if (!__name) {
		if (__preqsize)
			*__preqsize = 0;
		return __EOK;
	}
	__reqsize = ((__NAMESPACE_LOCAL_SYM __localdep_strlen)(__name) + 1) * sizeof(char);
	if (__preqsize)
		*__preqsize = __reqsize;
	if (__reqsize > __bufsize) {
#ifdef __ERANGE
		return __ERANGE;
#else /* __ERANGE */
		return 1;
#endif /* !__ERANGE */
	}
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__buf, __name, __reqsize);
	return __EOK;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getenv_s_defined
#define __local___localdep_getenv_s_defined
#define __localdep_getenv_s __LIBC_LOCAL_NAME(getenv_s)
#endif /* !__local___localdep_getenv_s_defined */
#else /* __CRT_HAVE_getenv || __LOCAL_environ */
#undef __local_getenv_s_defined
#endif /* !__CRT_HAVE_getenv && !__LOCAL_environ */
#endif /* !__local_getenv_s_defined */
