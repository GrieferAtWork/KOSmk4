/* HASH CRC-32:0xf4dab2e1 */
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
#ifndef __local_execv_defined
#define __local_execv_defined 1
#include <__crt.h>
#include <libc/local/environ.h>
#if (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__LOCAL_environ)
#include <features.h>
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
/* Dependency: execve from unistd */
#ifndef __local___localdep_execve_defined
#define __local___localdep_execve_defined 1
#if __has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CEIREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),execve,{ return __builtin_execve(__path, (char *const *)___argv, (char *const *)___envp); })
#elif defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),_execve,(__path,___argv,___envp))
#else /* ... */
#undef __local___localdep_execve_defined
#endif /* !... */
#endif /* !__local___localdep_execve_defined */
/* >> execv(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__LOCAL_LIBC(execv) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(execv))(char const *__restrict __path, __TARGV) {
	return __localdep_execve(__path, ___argv, __LOCAL_environ);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_execv_defined
#define __local___localdep_execv_defined 1
#define __localdep_execv __LIBC_LOCAL_NAME(execv)
#endif /* !__local___localdep_execv_defined */
#else /* (__CRT_HAVE_execve || __CRT_HAVE__execve) && __LOCAL_environ */
#undef __local_execv_defined
#endif /* (!__CRT_HAVE_execve && !__CRT_HAVE__execve) || !__LOCAL_environ */
#endif /* !__local_execv_defined */
