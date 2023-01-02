/* HASH CRC-32:0xccd8a45b */
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
#ifndef __local_getlogin_defined
#define __local_getlogin_defined
#include <__crt.h>
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_cuserid) || defined(__CRT_HAVE_getlogin_r) || defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid) || defined(__CRT_HAVE_getresuid)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_cuserid_defined
#define __local___localdep_cuserid_defined
#ifdef __CRT_HAVE_cuserid
__CREDIRECT(__ATTR_OUT_OPT(1),char *,__NOTHROW_NCX,__localdep_cuserid,(char *__s),cuserid,(__s))
#elif defined(__CRT_HAVE_getlogin_r) || defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid) || defined(__CRT_HAVE_getresuid)))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/cuserid.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_cuserid __LIBC_LOCAL_NAME(cuserid)
#else /* ... */
#undef __local___localdep_cuserid_defined
#endif /* !... */
#endif /* !__local___localdep_cuserid_defined */
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
__LOCAL_LIBC(getlogin) __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getlogin))(void) {
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
	char *__result = (__NAMESPACE_LOCAL_SYM __localdep_getenv)("LOGNAME");
	if (!__result)
		__result = (__NAMESPACE_LOCAL_SYM __localdep_cuserid)(__NULLPTR);
	return __result;


#else /* __CRT_HAVE_getenv || __LOCAL_environ */
	return (__NAMESPACE_LOCAL_SYM __localdep_cuserid)(__NULLPTR);
#endif /* !__CRT_HAVE_getenv && !__LOCAL_environ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getlogin_defined
#define __local___localdep_getlogin_defined
#define __localdep_getlogin __LIBC_LOCAL_NAME(getlogin)
#endif /* !__local___localdep_getlogin_defined */
#else /* __CRT_HAVE_cuserid || __CRT_HAVE_getlogin_r || __CRT_HAVE_getenv || __LOCAL_environ || (__CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid || __CRT_HAVE_getresuid)) */
#undef __local_getlogin_defined
#endif /* !__CRT_HAVE_cuserid && !__CRT_HAVE_getlogin_r && !__CRT_HAVE_getenv && !__LOCAL_environ && (!__CRT_HAVE_getpwuid_r || (!__CRT_HAVE_geteuid && !__CRT_HAVE___geteuid && !__CRT_HAVE___libc_geteuid && !__CRT_HAVE_getresuid)) */
#endif /* !__local_getlogin_defined */
