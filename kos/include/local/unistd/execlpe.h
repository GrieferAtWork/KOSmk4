/* HASH CRC-32:0x48d4aee1 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_execlpe_defined
#define __local_execlpe_defined 1
#include <__crt.h>
#include <hybrid/__alloca.h>
#include <local/environ.h>
#if defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__hybrid_alloca))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: execvpe from unistd */
#ifndef __local___localdep_execvpe_defined
#define __local___localdep_execvpe_defined 1
#ifdef __CRT_HAVE_execvpe
__NAMESPACE_LOCAL_END
#ifndef __TARGV
#ifdef __USE_DOS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_execvpe,(char const *__restrict __file, __TARGV, __TENVP),execvpe,(__file,___argv,___envp))
#elif defined(__CRT_HAVE__execvpe)
__NAMESPACE_LOCAL_END
#ifndef __TARGV
#ifdef __USE_DOS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_execvpe,(char const *__restrict __file, __TARGV, __TENVP),_execvpe,(__file,___argv,___envp))
#elif (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__hybrid_alloca)
__NAMESPACE_LOCAL_END
#include <local/unistd/execvpe.h>
__NAMESPACE_LOCAL_BEGIN
/* >> execvpe(3)
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
#define __localdep_execvpe __LIBC_LOCAL_NAME(execvpe)
#else /* ... */
#undef __local___localdep_execvpe_defined
#endif /* !... */
#endif /* !__local___localdep_execvpe_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
__LOCAL_LIBC(execlpe) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(execlpe))(char const *__restrict __file, char const *__args, ...) {
	__REDIRECT_EXECLE(char, __localdep_execvpe, __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_execlpe_defined
#define __local___localdep_execlpe_defined 1
#define __localdep_execlpe __LIBC_LOCAL_NAME(execlpe)
#endif /* !__local___localdep_execlpe_defined */
#else /* __CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_execve || __CRT_HAVE__execve) && __hybrid_alloca) */
#undef __local_execlpe_defined
#endif /* !__CRT_HAVE_execvpe && !__CRT_HAVE__execvpe && ((!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_execve && !__CRT_HAVE__execve) || !__hybrid_alloca) */
#endif /* !__local_execlpe_defined */
