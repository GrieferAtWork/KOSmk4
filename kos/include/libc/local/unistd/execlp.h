/* HASH CRC-32:0xdff4a664 */
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
#ifndef __local_execlp_defined
#define __local_execlp_defined
#include <__crt.h>
#include <libc/template/environ.h>
#include <hybrid/__alloca.h>
#if defined(__CRT_HAVE_execvp) || defined(__CRT_HAVE__execvp) || ((defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_execvp_defined
#define __local___localdep_execvp_defined
#if __has_builtin(__builtin_execvp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execvp)
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
__CEIREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_execvp,(char const *__restrict __file, __TARGV),execvp,{ return __builtin_execvp(__file, (char *const *)___argv); })
#elif defined(__CRT_HAVE_execvp)
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
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_execvp,(char const *__restrict __file, __TARGV),execvp,(__file,___argv))
#elif defined(__CRT_HAVE__execvp)
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
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_execvp,(char const *__restrict __file, __TARGV),_execvp,(__file,___argv))
#elif (defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/execvp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_execvp __LIBC_LOCAL_NAME(execvp)
#else /* ... */
#undef __local___localdep_execvp_defined
#endif /* !... */
#endif /* !__local___localdep_execvp_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(execlp) __ATTR_SENTINEL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(execlp))(char const *__restrict __file, char const *__args, ...) {
	__REDIRECT_EXECL(char, (__NAMESPACE_LOCAL_SYM __localdep_execvp), __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_execlp_defined
#define __local___localdep_execlp_defined
#define __localdep_execlp __LIBC_LOCAL_NAME(execlp)
#endif /* !__local___localdep_execlp_defined */
#else /* __CRT_HAVE_execvp || __CRT_HAVE__execvp || ((__CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __hybrid_alloca)) && __LOCAL_environ) */
#undef __local_execlp_defined
#endif /* !__CRT_HAVE_execvp && !__CRT_HAVE__execvp && ((!__CRT_HAVE_execvpe && !__CRT_HAVE__execvpe && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__hybrid_alloca)) || !__LOCAL_environ) */
#endif /* !__local_execlp_defined */
