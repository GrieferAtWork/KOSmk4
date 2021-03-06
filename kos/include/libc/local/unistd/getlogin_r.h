/* HASH CRC-32:0x77fa14cd */
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
#ifndef __local_getlogin_r_defined
#define __local_getlogin_r_defined 1
#include <__crt.h>
#include <libc/local/environ.h>
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ) || (defined(__CRT_HAVE_getpwuid_r) && defined(__CRT_HAVE_geteuid))
__NAMESPACE_LOCAL_BEGIN
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
/* Dependency: geteuid from unistd */
#if !defined(__local___localdep_geteuid_defined) && defined(__CRT_HAVE_geteuid)
#define __local___localdep_geteuid_defined 1
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> geteuid(2)
 * Return the effective user ID of the calling process */
__CREDIRECT(__ATTR_WUNUSED,__uid_t,__NOTHROW_NCX,__localdep_geteuid,(void),geteuid,())
#endif /* !__local___localdep_geteuid_defined && __CRT_HAVE_geteuid */
/* Dependency: getpwuid_r from pwd */
#if !defined(__local___localdep_getpwuid_r_defined) && defined(__CRT_HAVE_getpwuid_r)
#define __local___localdep_getpwuid_r_defined 1
__NAMESPACE_LOCAL_END
#include <bits/crt/db/passwd.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Search for an entry with a matching user ID
 * @return: 0 : (*result != NULL) Success
 * @return: 0 : (*result == NULL) No entry for `uid'
 * @return: * : Error (one of `E*' from `<errno.h>') */
__CREDIRECT(__ATTR_NONNULL((2, 3, 5)),__errno_t,__NOTHROW_RPC,__localdep_getpwuid_r,(__uid_t __uid, struct passwd *__restrict __resultbuf, char *__restrict __buffer, __SIZE_TYPE__ __buflen, struct passwd **__restrict __result),getpwuid_r,(__uid,__resultbuf,__buffer,__buflen,__result))
#endif /* !__local___localdep_getpwuid_r_defined && __CRT_HAVE_getpwuid_r */
/* Dependency: strncpy from string */
#ifndef __local___localdep_strncpy_defined
#define __local___localdep_strncpy_defined 1
#if __has_builtin(__builtin_strncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncpy)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strncpy(3)
 * Always write exactly `buflen' characters to `buf'. As far as
 * space for doing so is available, up to the `strlen(src)' of
 * the first characters are copied from `src'. All remaining
 * characters are always set to '\0'. Always re-returns `buf' */
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),strncpy,{ return __builtin_strncpy(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_strncpy)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strncpy(3)
 * Always write exactly `buflen' characters to `buf'. As far as
 * space for doing so is available, up to the `strlen(src)' of
 * the first characters are copied from `src'. All remaining
 * characters are always set to '\0'. Always re-returns `buf' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),strncpy,(__buf,__src,__buflen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strncpy.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strncpy(3)
 * Always write exactly `buflen' characters to `buf'. As far as
 * space for doing so is available, up to the `strlen(src)' of
 * the first characters are copied from `src'. All remaining
 * characters are always set to '\0'. Always re-returns `buf' */
#define __localdep_strncpy __LIBC_LOCAL_NAME(strncpy)
#endif /* !... */
#endif /* !__local___localdep_strncpy_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/db/passwd.h>
__NAMESPACE_LOCAL_BEGIN
/* >> getlogin_r(3)
 * Reentrant version of `getlogin()'. May truncate the name if it's longer than `name_len'
 * s.a. `getlogin()' and `cuserid()' */
__LOCAL_LIBC(getlogin_r) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getlogin_r))(char *__name, __SIZE_TYPE__ __name_len) {
#if defined(__CRT_HAVE_getpwuid_r) && defined(__CRT_HAVE_geteuid)
	char __buf[1024]; /* NSS_BUFLEN_PASSWD */
	struct passwd __pwent, *__pwptr;
#endif /* __CRT_HAVE_getpwuid_r && __CRT_HAVE_geteuid */
	char *__pwname;
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
	__pwname = __localdep_getenv("LOGNAME");
#if defined(__CRT_HAVE_getpwuid_r) && defined(__CRT_HAVE_geteuid)
	if (!__pwname)
#endif /* __CRT_HAVE_getpwuid_r && __CRT_HAVE_geteuid */
#endif /* __CRT_HAVE_getenv || __LOCAL_environ */
#if defined(__CRT_HAVE_getpwuid_r) && defined(__CRT_HAVE_geteuid)
	{
		if (__localdep_getpwuid_r(__localdep_geteuid(), &__pwent, __buf,
		               sizeof(__buf), &__pwptr) ||
		    __pwptr == __NULLPTR)
			return -1;
		__pwname = __pwptr->pw_name;
		if (!__pwname)
			return -1;
	}
#endif /* __CRT_HAVE_getpwuid_r && __CRT_HAVE_geteuid */
	if (__name_len) {
		__name[__name_len - 1] = '\0';
		__localdep_strncpy(__name, __pwname, __name_len - 1);
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getlogin_r_defined
#define __local___localdep_getlogin_r_defined 1
#define __localdep_getlogin_r __LIBC_LOCAL_NAME(getlogin_r)
#endif /* !__local___localdep_getlogin_r_defined */
#else /* __CRT_HAVE_getenv || __LOCAL_environ || (__CRT_HAVE_getpwuid_r && __CRT_HAVE_geteuid) */
#undef __local_getlogin_r_defined
#endif /* !__CRT_HAVE_getenv && !__LOCAL_environ && (!__CRT_HAVE_getpwuid_r || !__CRT_HAVE_geteuid) */
#endif /* !__local_getlogin_r_defined */
