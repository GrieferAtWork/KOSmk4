/* HASH CRC-32:0xfc8a3f2 */
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
#ifndef __local_system_defined
#define __local_system_defined
#include <__crt.h>
#include <libc/template/environ.h>
#if (defined(__CRT_HAVE_shexec) || defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork) || defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__Exit_defined
#define __local___localdep__Exit_defined
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__CEIREDIRECT(__ATTR_NORETURN,void,,__localdep__Exit,(int __status),_Exit,{ __builtin__Exit(__status); })
#elif __has_builtin(__builtin__exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__exit)
__CEIREDIRECT(__ATTR_NORETURN,void,,__localdep__Exit,(int __status),_exit,{ __builtin__exit(__status); })
#elif defined(__CRT_HAVE__Exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep__Exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE__exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep__Exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE_quick_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep__Exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE_exit)
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep__Exit,(int __status),exit,(__status))
#else /* ... */
#undef __local___localdep__Exit_defined
#endif /* !... */
#endif /* !__local___localdep__Exit_defined */
#ifndef __local___localdep_fork_defined
#define __local___localdep_fork_defined
#if __has_builtin(__builtin_fork) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fork)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),fork,{ return __builtin_fork(); })
#elif defined(__CRT_HAVE_fork)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),fork,())
#elif defined(__CRT_HAVE___fork)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),__fork,())
#elif defined(__CRT_HAVE___libc_fork)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),__libc_fork,())
#else /* ... */
#undef __local___localdep_fork_defined
#endif /* !... */
#endif /* !__local___localdep_fork_defined */
#ifndef __local___localdep_shexec_defined
#define __local___localdep_shexec_defined
#ifdef __CRT_HAVE_shexec
__CREDIRECT(__ATTR_IN_OPT(1),int,__NOTHROW_RPC,__localdep_shexec,(char const *__command),shexec,(__command))
#elif defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/shexec.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_shexec __LIBC_LOCAL_NAME(shexec)
#else /* ... */
#undef __local___localdep_shexec_defined
#endif /* !... */
#endif /* !__local___localdep_shexec_defined */
#ifndef __local___localdep_vfork_defined
#define __local___localdep_vfork_defined
#ifdef __CRT_HAVE_vfork
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_vfork,(void),vfork,())
#elif defined(__CRT_HAVE___vfork)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_vfork,(void),__vfork,())
#elif defined(__CRT_HAVE___libc_vfork)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETURNS_TWICE __ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_vfork,(void),__libc_vfork,())
#else /* ... */
#undef __local___localdep_vfork_defined
#endif /* !... */
#endif /* !__local___localdep_vfork_defined */
#ifndef __local___localdep_waitpid_defined
#define __local___localdep_waitpid_defined
#ifdef __CRT_HAVE_waitpid
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <features.h>
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),waitpid,(__pid,__stat_loc,__options))
#elif defined(__CRT_HAVE___waitpid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <features.h>
#include <parts/waitmacros.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__pid_t,__NOTHROW_RPC,__localdep_waitpid,(__pid_t __pid, __WAIT_STATUS __stat_loc, __STDC_INT_AS_UINT_T __options),__waitpid,(__pid,__stat_loc,__options))
#else /* ... */
#undef __local___localdep_waitpid_defined
#endif /* !... */
#endif /* !__local___localdep_waitpid_defined */
__LOCAL_LIBC(system) __ATTR_IN_OPT(1) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(system))(char const *__command) {
	int __status;
	__pid_t __cpid, __error;
#if defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork)
	__cpid = (__NAMESPACE_LOCAL_SYM __localdep_vfork)();
#else /* __CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork */
	__cpid = (__NAMESPACE_LOCAL_SYM __localdep_fork)();
#endif /* !__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork */
	if (__cpid == 0) {
		(__NAMESPACE_LOCAL_SYM __localdep_shexec)(__command);
		/* NOTE: system() must return ZERO(0) if no command processor is available. */
		(__NAMESPACE_LOCAL_SYM __localdep__Exit)(__command ? 127 : 0);
	}
	if (__cpid < 0)
		return -1;
	for (;;) {
		__error = (__NAMESPACE_LOCAL_SYM __localdep_waitpid)(__cpid, &__status, 0);
		if (__error == __cpid)
			break;
		if (__error >= 0)
			continue;
#if defined(__libc_geterrno) && defined(__EINTR)
		if (__libc_geterrno() != __EINTR)
			return -1;
#else /* __libc_geterrno && __EINTR */
		return -1;
#endif /* !__libc_geterrno || !__EINTR */
	}
	return __status;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_system_defined
#define __local___localdep_system_defined
#define __localdep_system __LIBC_LOCAL_NAME(system)
#endif /* !__local___localdep_system_defined */
#else /* (__CRT_HAVE_shexec || __CRT_HAVE_execl || __CRT_HAVE__execl || __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __LOCAL_environ)) && (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork || __CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) */
#undef __local_system_defined
#endif /* (!__CRT_HAVE_shexec && !__CRT_HAVE_execl && !__CRT_HAVE__execl && !__CRT_HAVE_execv && !__CRT_HAVE__execv && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__LOCAL_environ)) || (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork && !__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) */
#endif /* !__local_system_defined */
