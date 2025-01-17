/* HASH CRC-32:0x7c175d4 */
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
#ifndef __local_secure_getenv_defined
#define __local_secure_getenv_defined
#include <__crt.h>
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
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
__NAMESPACE_LOCAL_END
#include <libc/template/__libc_enable_secure.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(secure_getenv) __ATTR_WUNUSED __ATTR_IN(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(secure_getenv))(char const *__varname) {
#ifdef __LOCAL___libc_enable_secure
	if (__LOCAL___libc_enable_secure)
		return __NULLPTR; /* Unconditionally return `NULL' for setuid() programs */
#endif /* __LOCAL___libc_enable_secure */
	return (__NAMESPACE_LOCAL_SYM __localdep_getenv)(__varname);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_secure_getenv_defined
#define __local___localdep_secure_getenv_defined
#define __localdep_secure_getenv __LIBC_LOCAL_NAME(secure_getenv)
#endif /* !__local___localdep_secure_getenv_defined */
#else /* __CRT_HAVE_getenv || __LOCAL_environ */
#undef __local_secure_getenv_defined
#endif /* !__CRT_HAVE_getenv && !__LOCAL_environ */
#endif /* !__local_secure_getenv_defined */
