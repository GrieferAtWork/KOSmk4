/* HASH CRC-32:0xfefa8f6f */
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
#ifndef __local_shexec_defined
#define __local_shexec_defined
#include <__crt.h>
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_execl_defined
#define __local___localdep_execl_defined
#if __has_builtin(__builtin_execl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execl) && __has_builtin(__builtin_va_arg_pack)
__CEIREDIRECT(__ATTR_SENTINEL __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_execl,(char const *__restrict __path, char const *__args, ...),execl,{ return __builtin_execl(__path, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execl)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL __localdep_execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME("execl");
#elif defined(__CRT_HAVE__execl)
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL __localdep_execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME("_execl");
#elif defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/execl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_execl __LIBC_LOCAL_NAME(execl)
#else /* ... */
#undef __local___localdep_execl_defined
#endif /* !... */
#endif /* !__local___localdep_execl_defined */
#ifndef __local___localdep_secure_getenv_defined
#define __local___localdep_secure_getenv_defined
#ifdef __CRT_HAVE_secure_getenv
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_secure_getenv,(char const *__varname),secure_getenv,(__varname))
#elif defined(__CRT_HAVE___secure_getenv)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_secure_getenv,(char const *__varname),__secure_getenv,(__varname))
#elif defined(__CRT_HAVE___libc_secure_getenv)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_secure_getenv,(char const *__varname),__libc_secure_getenv,(__varname))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/template/__libc_enable_secure.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_getenv) && !defined(__LOCAL___libc_enable_secure)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_secure_getenv,(char const *__varname),getenv,(__varname))
#elif defined(__LOCAL_environ) && !defined(__LOCAL___libc_enable_secure)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/getenv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_secure_getenv __LIBC_LOCAL_NAME(getenv)
#elif defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/secure_getenv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_secure_getenv __LIBC_LOCAL_NAME(secure_getenv)
#else /* ... */
#undef __local___localdep_secure_getenv_defined
#endif /* !... */
#endif /* !... */
#endif /* !__local___localdep_secure_getenv_defined */
#ifndef __local___localdep_strrchrnul_defined
#define __local___localdep_strrchrnul_defined
#ifdef __CRT_HAVE_strrchrnul
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strrchrnul,(char const *__restrict __haystack, int __needle),strrchrnul,(__haystack,__needle))
#else /* __CRT_HAVE_strrchrnul */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strrchrnul.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strrchrnul __LIBC_LOCAL_NAME(strrchrnul)
#endif /* !__CRT_HAVE_strrchrnul */
#endif /* !__local___localdep_strrchrnul_defined */
__LOCAL_LIBC(shexec) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(shexec))(char const *__command) {
	static char const __arg_sh[] = "sh";
	static char const __arg__c[] = "-c";

#if defined(__CRT_HAVE_secure_getenv) || defined(__CRT_HAVE___secure_getenv) || defined(__CRT_HAVE___libc_secure_getenv) || defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
	/* Try to make use of $SHELL, if defined and an absolute path. */
	char const *__environ_shell = (__NAMESPACE_LOCAL_SYM __localdep_secure_getenv)("SHELL");
	if (__environ_shell && *__environ_shell == '/') {
		char const *__environ_shell_sh;
		__environ_shell_sh = (__NAMESPACE_LOCAL_SYM __localdep_strrchrnul)(__environ_shell, '/') + 1;
		(__NAMESPACE_LOCAL_SYM __localdep_execl)(__environ_shell, __environ_shell_sh,
		      __arg__c, __command, (char *)__NULLPTR);
	}
#endif /* __CRT_HAVE_secure_getenv || __CRT_HAVE___secure_getenv || __CRT_HAVE___libc_secure_getenv || __CRT_HAVE_getenv || __LOCAL_environ */

#ifdef __KOS__
	/* By default, KOS uses busybox, so try to invoke that first. */
	(__NAMESPACE_LOCAL_SYM __localdep_execl)("/bin/busybox", __arg_sh, __arg__c, __command, (char *)__NULLPTR);
	(__NAMESPACE_LOCAL_SYM __localdep_execl)("/bin/sh", __arg_sh, __arg__c, __command, (char *)__NULLPTR);
	(__NAMESPACE_LOCAL_SYM __localdep_execl)("/bin/bash", __arg_sh, __arg__c, __command, (char *)__NULLPTR);
#else /* __KOS__ */
	(__NAMESPACE_LOCAL_SYM __localdep_execl)("/bin/sh", __arg_sh, __arg__c, __command, (char *)__NULLPTR);
	(__NAMESPACE_LOCAL_SYM __localdep_execl)("/bin/bash", __arg_sh, __arg__c, __command, (char *)__NULLPTR);
	(__NAMESPACE_LOCAL_SYM __localdep_execl)("/bin/busybox", __arg_sh, __arg__c, __command, (char *)__NULLPTR);
#endif /* !__KOS__ */
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shexec_defined
#define __local___localdep_shexec_defined
#define __localdep_shexec __LIBC_LOCAL_NAME(shexec)
#endif /* !__local___localdep_shexec_defined */
#else /* __CRT_HAVE_execl || __CRT_HAVE__execl || __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __LOCAL_environ) */
#undef __local_shexec_defined
#endif /* !__CRT_HAVE_execl && !__CRT_HAVE__execl && !__CRT_HAVE_execv && !__CRT_HAVE__execv && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__LOCAL_environ) */
#endif /* !__local_shexec_defined */
