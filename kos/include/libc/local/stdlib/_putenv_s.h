/* HASH CRC-32:0xee045621 */
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
#ifndef __local__putenv_s_defined
#define __local__putenv_s_defined
#include <__crt.h>
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_setenv) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && defined(__CRT_HAVE__putenv_s))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_setenv_defined
#define __local___localdep_setenv_defined
#ifdef __CRT_HAVE_setenv
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_setenv,(char const *__varname, char const *__val, int __replace),setenv,(__varname,__val,__replace))
#elif (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && defined(__CRT_HAVE__putenv_s)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/setenv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_setenv __LIBC_LOCAL_NAME(setenv)
#else /* ... */
#undef __local___localdep_setenv_defined
#endif /* !... */
#endif /* !__local___localdep_setenv_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_putenv_s) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_putenv_s))(char const *__varname, char const *__val) {
	return (__NAMESPACE_LOCAL_SYM __localdep_setenv)(__varname, __val, 1)
#ifdef __EINVAL
	       ? __libc_geterrno_or(__EINVAL)
#else /* __EINVAL */
	       ? __libc_geterrno_or(1)
#endif /* !__EINVAL */
	       : 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__putenv_s_defined
#define __local___localdep__putenv_s_defined
#define __localdep__putenv_s __LIBC_LOCAL_NAME(_putenv_s)
#endif /* !__local___localdep__putenv_s_defined */
#else /* __CRT_HAVE_setenv || ((__CRT_HAVE_getenv || __LOCAL_environ) && __CRT_HAVE__putenv_s) */
#undef __local__putenv_s_defined
#endif /* !__CRT_HAVE_setenv && ((!__CRT_HAVE_getenv && !__LOCAL_environ) || !__CRT_HAVE__putenv_s) */
#endif /* !__local__putenv_s_defined */
