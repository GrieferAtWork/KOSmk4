/* HASH CRC-32:0x70573518 */
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
#ifndef __local_execl_defined
#if defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv)
#define __local_execl_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "execv" */
#ifndef ____localdep_execv_defined
#define ____localdep_execv_defined 1
#if __has_builtin(__builtin_execv) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_RPC(__LIBCCALL __localdep_execv)(char const *__restrict __path, __TARGV) { return __builtin_execv(__path, (char *const *)___argv); }
#elif defined(__CRT_HAVE_execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_execv,(char const *__restrict __path, __TARGV),execv,(__path,___argv))
#elif defined(__CRT_HAVE__execv)
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,__localdep_execv,(char const *__restrict __path, __TARGV),_execv,(__path,___argv))
#else /* LIBC: execv */
#undef ____localdep_execv_defined
#endif /* execv... */
#endif /* !____localdep_execv_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LOCAL_LIBC(execl) __ATTR_SENTINEL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(execl))(char const *__restrict __path,
                                                    char const *__args,
                                                    ... /*, (char *)NULL*/) {
#line 268 "kos/src/libc/magic/unistd.c"
	__REDIRECT_EXECL(char, __localdep_execv, __path, __args)
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_execv || __CRT_HAVE__execv */
#endif /* !__local_execl_defined */
