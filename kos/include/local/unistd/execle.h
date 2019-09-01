/* HASH 0xc6a32853 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_execle_defined
#if ((__has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)) || defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve))
#define __local_execle_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "execve" */
#ifndef ____localdep_execve_defined
#define ____localdep_execve_defined 1
#if __has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__FORCELOCAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_RPC(__LIBCCALL __localdep_execve)(char const *__restrict __path, __TARGV, __TENVP) { return __builtin_execve(__path, (char *const *)___argv, (char *const *)___envp); }
#elif defined(__CRT_HAVE_execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),execve,(__path, ___argv, ___envp))
#elif defined(__CRT_HAVE__execve)
/* >> execve(2)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),_execve,(__path, ___argv, ___envp))
#else /* LIBC: execve */
#undef ____localdep_execve_defined
#endif /* execve... */
#endif /* !____localdep_execve_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> execle(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinal */
__LOCAL_LIBC(execle) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(execle))(char const *__restrict __path,
                                                     char const *__args,
                                                     ... /*, (char *)NULL, (char **)environ*/) {
#line 274 "kos/src/libc/magic/unistd.c"
	__REDIRECT_EXECLE(char, __localdep_execve, __path, __args)
}
__NAMESPACE_LOCAL_END
#endif /* ((__has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)) || defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) */
#endif /* !__local_execle_defined */
