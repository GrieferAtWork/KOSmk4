/* HASH CRC-32:0x8f151de9 */
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
#ifndef __local_getlogin_r_defined
#define __local_getlogin_r_defined
#include <__crt.h>
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid)))
#include <hybrid/typecore.h>
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
#ifndef __local___localdep_geteuid_defined
#define __local___localdep_geteuid_defined
#ifdef __CRT_HAVE_geteuid
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,__localdep_geteuid,(void),geteuid,())
#elif defined(__CRT_HAVE___geteuid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,__localdep_geteuid,(void),__geteuid,())
#elif defined(__CRT_HAVE___libc_geteuid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,__localdep_geteuid,(void),__libc_geteuid,())
#else /* ... */
#undef __local___localdep_geteuid_defined
#endif /* !... */
#endif /* !__local___localdep_geteuid_defined */
#if !defined(__local___localdep_getpwuid_r_defined) && defined(__CRT_HAVE_getpwuid_r)
#define __local___localdep_getpwuid_r_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/db/passwd.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(2) __ATTR_OUT(5) __ATTR_OUTS(3, 4),__errno_t,__NOTHROW_RPC,__localdep_getpwuid_r,(__uid_t __uid, struct passwd *__restrict __resultbuf, char *__restrict __buffer, __SIZE_TYPE__ __buflen, struct passwd **__restrict __result),getpwuid_r,(__uid,__resultbuf,__buffer,__buflen,__result))
#endif /* !__local___localdep_getpwuid_r_defined && __CRT_HAVE_getpwuid_r */
#ifndef __local___localdep_strncpy_defined
#define __local___localdep_strncpy_defined
#if __has_builtin(__builtin_strncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncpy)
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),strncpy,{ return __builtin_strncpy(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_strncpy)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),strncpy,(__buf,__src,__buflen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strncpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strncpy __LIBC_LOCAL_NAME(strncpy)
#endif /* !... */
#endif /* !__local___localdep_strncpy_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/db/passwd.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getlogin_r) __ATTR_OUTS(1, 2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getlogin_r))(char *__name, __SIZE_TYPE__ __name_len) {
#if defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid))
	char __buf[1024]; /* NSS_BUFLEN_PASSWD */
	struct passwd __pwent, *__pwptr;
#endif /* __CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid) */
	char *__pwname;
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
	__pwname = (__NAMESPACE_LOCAL_SYM __localdep_getenv)("LOGNAME");
#if defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid))
	if (!__pwname)
#endif /* __CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid) */
#endif /* __CRT_HAVE_getenv || __LOCAL_environ */
#if defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid))
	{
		if ((__NAMESPACE_LOCAL_SYM __localdep_getpwuid_r)((__NAMESPACE_LOCAL_SYM __localdep_geteuid)(), &__pwent, __buf,
		               sizeof(__buf), &__pwptr) ||
		    __pwptr == __NULLPTR)
			return -1;
		__pwname = __pwptr->pw_name;
		if (!__pwname)
			return -1;
	}
#endif /* __CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid) */
	if (__name_len) {
		__name[__name_len - 1] = '\0';
		(__NAMESPACE_LOCAL_SYM __localdep_strncpy)(__name, __pwname, __name_len - 1);
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getlogin_r_defined
#define __local___localdep_getlogin_r_defined
#define __localdep_getlogin_r __LIBC_LOCAL_NAME(getlogin_r)
#endif /* !__local___localdep_getlogin_r_defined */
#else /* __CRT_HAVE_getenv || __LOCAL_environ || (__CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid)) */
#undef __local_getlogin_r_defined
#endif /* !__CRT_HAVE_getenv && !__LOCAL_environ && (!__CRT_HAVE_getpwuid_r || (!__CRT_HAVE_geteuid && !__CRT_HAVE___geteuid && !__CRT_HAVE___libc_geteuid)) */
#endif /* !__local_getlogin_r_defined */
