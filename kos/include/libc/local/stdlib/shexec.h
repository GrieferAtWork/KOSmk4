/* HASH CRC-32:0x818ba438 */
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
#ifndef __local_shexec_defined
#define __local_shexec_defined 1
#include <__crt.h>
#include <libc/local/environ.h>
#if defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__LOCAL_environ))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: execl from unistd */
#ifndef __local___localdep_execl_defined
#define __local___localdep_execl_defined 1
#if __has_builtin(__builtin_execl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execl) && __has_builtin(__builtin_va_arg_pack)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__CEIREDIRECT(__ATTR_SENTINEL __ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_execl,(char const *__restrict __path, char const *__args, ...),execl,{ return __builtin_execl(__path, __args, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_execl)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL __localdep_execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME("execl");
#elif defined(__CRT_HAVE__execl)
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL __localdep_execl)(char const *__restrict __path, char const *__args, ...) __CASMNAME("_execl");
#elif defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__LOCAL_environ))
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/execl.h>
__NAMESPACE_LOCAL_BEGIN
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
#define __localdep_execl __LIBC_LOCAL_NAME(execl)
#else /* ... */
#undef __local___localdep_execl_defined
#endif /* !... */
#endif /* !__local___localdep_execl_defined */
/* >> shexec(3)
 * Execute command with the system interpreter (such as: `/bin/sh -c $command')
 * This function is used to implement `system(3)' and `popen(3)', and may be
 * used to invoke the system interpreter.
 * This function only returns on failure (similar to exec(2)), and will never
 * return on success (since in that case, the calling program will have been
 * replaced by the system shell) */
__LOCAL_LIBC(shexec) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(shexec))(char const *__command) {
	static char const __arg_sh[] = "sh";
	static char const __arg__c[] = "-c";
#ifdef __KOS__
	/* By default, KOS uses busybox, so try to invoke that first. */
	__localdep_execl("/bin/busybox", __arg_sh, __arg__c, __command, (char *)__NULLPTR);
	__localdep_execl("/bin/sh", __arg_sh, __arg__c, __command, (char *)__NULLPTR);
	__localdep_execl("/bin/bash", __arg_sh, __arg__c, __command, (char *)__NULLPTR);
#else /* __KOS__ */
	__localdep_execl("/bin/sh", __arg_sh, __arg__c, __command, (char *)__NULLPTR);
	__localdep_execl("/bin/bash", __arg_sh, __arg__c, __command, (char *)__NULLPTR);
	__localdep_execl("/bin/busybox", __arg_sh, __arg__c, __command, (char *)__NULLPTR);
#endif /* !__KOS__ */
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shexec_defined
#define __local___localdep_shexec_defined 1
#define __localdep_shexec __LIBC_LOCAL_NAME(shexec)
#endif /* !__local___localdep_shexec_defined */
#else /* __CRT_HAVE_execl || __CRT_HAVE__execl || __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve) && __LOCAL_environ) */
#undef __local_shexec_defined
#endif /* !__CRT_HAVE_execl && !__CRT_HAVE__execl && !__CRT_HAVE_execv && !__CRT_HAVE__execv && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve) || !__LOCAL_environ) */
#endif /* !__local_shexec_defined */
