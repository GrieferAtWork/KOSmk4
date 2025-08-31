/* HASH CRC-32:0x89653994 */
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
#ifndef __local_posix_xspawn_np_defined
#define __local_posix_xspawn_np_defined
#include <__crt.h>
#include <asm/crt/posix_spawn.h>
#include <asm/os/vfork.h>
#include <asm/os/features.h>
#include <hybrid/__alloca.h>
#include <libc/template/environ.h>
#if ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC))) && defined(__POSIX_SPAWN_USE_KOS) && (defined(__CRT_HAVE_fexecve) || defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve) || defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe)) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))
#include <bits/crt/posix_spawn.h>
#include <bits/types.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_posix_spawn_impl_defined
#define __local___localdep_posix_spawn_impl_defined
__NAMESPACE_LOCAL_END
#include <libc/local/spawn/posix_spawn_impl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_posix_spawn_impl __LIBC_LOCAL_NAME(posix_spawn_impl)
#endif /* !__local___localdep_posix_spawn_impl_defined */
__LOCAL_LIBC(posix_xspawn_np) __ATTR_IN_OPT(2) __ATTR_IN_OPT(3) __ATTR_IN_OPT(5) __ATTR_OUT(1) __ATTR_NONNULL((4)) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(posix_xspawn_np))(__pid_t *__restrict __pid, struct __posix_spawn_file_actions const *__file_actions, struct __posix_spawnattr const *__attrp, __errno_t (__LIBCCALL *__exec_fn)(void *), void *__exec_arg) {
#ifdef __USE_DOS_ALTERATIONS
	return (__NAMESPACE_LOCAL_SYM __localdep_posix_spawn_impl)(__pid, 3, (void *)__exec_fn, __file_actions, __attrp, (char const *const *)__exec_arg, __NULLPTR);
#else /* __USE_DOS_ALTERATIONS */
	return (__NAMESPACE_LOCAL_SYM __localdep_posix_spawn_impl)(__pid, 3, (void *)__exec_fn, __file_actions, __attrp, (char *const *)__exec_arg, __NULLPTR);
#endif /* !__USE_DOS_ALTERATIONS */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_xspawn_np_defined
#define __local___localdep_posix_xspawn_np_defined
#define __localdep_posix_xspawn_np __LIBC_LOCAL_NAME(posix_xspawn_np)
#endif /* !__local___localdep_posix_xspawn_np_defined */
#else /* ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC)) && __POSIX_SPAWN_USE_KOS && (__CRT_HAVE_fexecve || __CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve || __CRT_HAVE_execvpe || __CRT_HAVE__execvpe) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) */
#undef __local_posix_xspawn_np_defined
#endif /* ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC)) || !__POSIX_SPAWN_USE_KOS || (!__CRT_HAVE_fexecve && !__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve && !__CRT_HAVE_execvpe && !__CRT_HAVE__execvpe) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) */
#endif /* !__local_posix_xspawn_np_defined */
