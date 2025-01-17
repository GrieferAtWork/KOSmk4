/* HASH CRC-32:0xdd7afd22 */
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
#ifndef __local_execl_defined
#define __local_execl_defined
#include <__crt.h>
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_execv_defined
#define __local___localdep_execv_defined
#if __has_builtin(__builtin_execv) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execv)
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,__localdep_execv,(char const *__restrict __path, __TARGV),execv,{ return __builtin_execv(__path, (char *const *)___argv); })
#elif defined(__CRT_HAVE_execv)
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,__localdep_execv,(char const *__restrict __path, __TARGV),execv,(__path,___argv))
#elif defined(__CRT_HAVE__execv)
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_RPC,__localdep_execv,(char const *__restrict __path, __TARGV),_execv,(__path,___argv))
#elif (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/execv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_execv __LIBC_LOCAL_NAME(execv)
#else /* ... */
#undef __local___localdep_execv_defined
#endif /* !... */
#endif /* !__local___localdep_execv_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(execl) __ATTR_SENTINEL __ATTR_IN(1) __ATTR_IN_OPT(2) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(execl))(char const *__restrict __path, char const *__args, ...) {
	__REDIRECT_EXECL(char, (__NAMESPACE_LOCAL_SYM __localdep_execv), __path, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_execl_defined
#define __local___localdep_execl_defined
#define __localdep_execl __LIBC_LOCAL_NAME(execl)
#endif /* !__local___localdep_execl_defined */
#else /* __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __LOCAL_environ) */
#undef __local_execl_defined
#endif /* !__CRT_HAVE_execv && !__CRT_HAVE__execv && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__LOCAL_environ) */
#endif /* !__local_execl_defined */
