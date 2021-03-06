/* HASH CRC-32:0xa19bc867 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getlogin_defined
#define __local_getlogin_defined 1
#include <__crt.h>
#include <libc/local/environ.h>
#if defined(__CRT_HAVE_cuserid) || defined(__CRT_HAVE_getlogin_r) || defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && defined(__CRT_HAVE_geteuid))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: cuserid from unistd */
#ifndef __local___localdep_cuserid_defined
#define __local___localdep_cuserid_defined 1
#ifdef __CRT_HAVE_cuserid
/* >> cuserid(3)
 * Return the name of the current user (`$LOGNAME' or `getpwuid(geteuid())'), storing
 * that name in `s'. When `s' is NULL, a static buffer is used instead
 * When given, `s' must be a buffer of at least `L_cuserid' bytes.
 * If the actual username is longer than this, it may be truncated, and programs
 * that wish to support longer usernames should make use of `getlogin_r()' instead.
 * s.a. `getlogin()' and `getlogin_r()' */
__CREDIRECT(,char *,__NOTHROW_NCX,__localdep_cuserid,(char *__s),cuserid,(__s))
#elif defined(__CRT_HAVE_getlogin_r) || defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && defined(__CRT_HAVE_geteuid))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/cuserid.h>
__NAMESPACE_LOCAL_BEGIN
/* >> cuserid(3)
 * Return the name of the current user (`$LOGNAME' or `getpwuid(geteuid())'), storing
 * that name in `s'. When `s' is NULL, a static buffer is used instead
 * When given, `s' must be a buffer of at least `L_cuserid' bytes.
 * If the actual username is longer than this, it may be truncated, and programs
 * that wish to support longer usernames should make use of `getlogin_r()' instead.
 * s.a. `getlogin()' and `getlogin_r()' */
#define __localdep_cuserid __LIBC_LOCAL_NAME(cuserid)
#else /* ... */
#undef __local___localdep_cuserid_defined
#endif /* !... */
#endif /* !__local___localdep_cuserid_defined */
/* Dependency: getenv from stdlib */
#ifndef __local___localdep_getenv_defined
#define __local___localdep_getenv_defined 1
#ifdef __CRT_HAVE_getenv
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_getenv,(char const *__varname),getenv,(__varname))
#elif defined(__LOCAL_environ)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/getenv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getenv __LIBC_LOCAL_NAME(getenv)
#else /* ... */
#undef __local___localdep_getenv_defined
#endif /* !... */
#endif /* !__local___localdep_getenv_defined */
/* >> getlogin(3)
 * Return the login name for the current user, or `NULL' on error.
 * s.a. `getlogin_r()' and `cuserid()' */
__LOCAL_LIBC(getlogin) __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getlogin))(void) {
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
	char *__result = __localdep_getenv("LOGNAME");
	if (!__result)
		__result = __localdep_cuserid(__NULLPTR);
	return __result;


#else /* __CRT_HAVE_getenv || __LOCAL_environ */
	return __localdep_cuserid(__NULLPTR);
#endif /* !__CRT_HAVE_getenv && !__LOCAL_environ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getlogin_defined
#define __local___localdep_getlogin_defined 1
#define __localdep_getlogin __LIBC_LOCAL_NAME(getlogin)
#endif /* !__local___localdep_getlogin_defined */
#else /* __CRT_HAVE_cuserid || __CRT_HAVE_getlogin_r || __CRT_HAVE_getenv || __LOCAL_environ || (__CRT_HAVE_getpwuid_r && __CRT_HAVE_geteuid) */
#undef __local_getlogin_defined
#endif /* !__CRT_HAVE_cuserid && !__CRT_HAVE_getlogin_r && !__CRT_HAVE_getenv && !__LOCAL_environ && (!__CRT_HAVE_getpwuid_r || !__CRT_HAVE_geteuid) */
#endif /* !__local_getlogin_defined */
