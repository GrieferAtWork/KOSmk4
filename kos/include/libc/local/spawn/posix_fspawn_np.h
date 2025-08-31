/* HASH CRC-32:0x2384de19 */
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
#ifndef __local_posix_fspawn_np_defined
#define __local_posix_fspawn_np_defined
#include <__crt.h>
#include <asm/os/features.h>
#include <asm/crt/posix_spawn.h>
#include <asm/os/vfork.h>
#if (((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC))) && defined(__POSIX_SPAWN_USE_KOS) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve))))) || (defined(__OS_HAVE_PROCFS_SELF_FD) && defined(__CRT_HAVE_posix_spawn))
#include <bits/crt/posix_spawn.h>
#include <bits/types.h>
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
#if !defined(__local___localdep_crt_posix_spawn_defined) && defined(__CRT_HAVE_posix_spawn)
#define __local___localdep_crt_posix_spawn_defined
__CREDIRECT(__ATTR_IN(2) __ATTR_IN(5) __ATTR_IN(6) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_OUT(1),__errno_t,__NOTHROW_RPC,__localdep_crt_posix_spawn,(__pid_t *__restrict __pid, char const *__restrict __path, struct __posix_spawn_file_actions const *__file_actions, struct __posix_spawnattr const *__attrp, __TARGV, __TENVP),posix_spawn,(__pid,__path,__file_actions,__attrp,___argv,___envp))
#endif /* !__local___localdep_crt_posix_spawn_defined && __CRT_HAVE_posix_spawn */
#if !defined(__local___localdep_posix_spawn_impl_defined) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC))) && defined(__POSIX_SPAWN_USE_KOS) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))
#define __local___localdep_posix_spawn_impl_defined
__NAMESPACE_LOCAL_END
#include <libc/local/spawn/posix_spawn_impl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_posix_spawn_impl __LIBC_LOCAL_NAME(posix_spawn_impl)
#endif /* !__local___localdep_posix_spawn_impl_defined && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC)) && __POSIX_SPAWN_USE_KOS && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) */
#ifndef __local___localdep_sprintf_defined
#define __local___localdep_sprintf_defined
#if __has_builtin(__builtin_sprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf) && __has_builtin(__builtin_va_arg_pack)
__CEIREDIRECT(__ATTR_IN(2) __ATTR_LIBC_PRINTF(2, 3) __ATTR_OUT(1),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_sprintf,(char *__restrict __buf, char const *__restrict __format, ...),sprintf,{ return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sprintf)
__LIBC __ATTR_IN(2) __ATTR_LIBC_PRINTF(2, 3) __ATTR_OUT(1) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("sprintf");
#elif defined(__CRT_HAVE__IO_sprintf)
__LIBC __ATTR_IN(2) __ATTR_LIBC_PRINTF(2, 3) __ATTR_OUT(1) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("_IO_sprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/sprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sprintf __LIBC_LOCAL_NAME(sprintf)
#endif /* !... */
#endif /* !__local___localdep_sprintf_defined */
__LOCAL_LIBC(posix_fspawn_np) __ATTR_FDREAD(2) __ATTR_IN(5) __ATTR_IN(6) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_OUT(1) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(posix_fspawn_np))(__pid_t *__restrict __pid, __fd_t __execfd, struct __posix_spawn_file_actions const *__file_actions, struct __posix_spawnattr const *__attrp, __TARGV, __TENVP) {
#if ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE___libc_pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC))) && defined(__POSIX_SPAWN_USE_KOS) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)) && (defined(__CRT_HAVE_fexecve) || (defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve))))
	return (__NAMESPACE_LOCAL_SYM __localdep_posix_spawn_impl)(__pid, 2, (void *)(__UINTPTR_TYPE__)__execfd, __file_actions, __attrp, ___argv, ___envp);
#else /* ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC)) && __POSIX_SPAWN_USE_KOS && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve))) */
#if __SIZEOF_INT__ == 4
	char __buf[__COMPILER_LNEOF("/proc/self/fd/-2147483648")];
#elif __SIZEOF_INT__ == 8
	char __buf[__COMPILER_LNEOF("/proc/self/fd/-9223372036854775808")];
#elif __SIZEOF_INT__ == 2
	char __buf[__COMPILER_LNEOF("/proc/self/fd/-32768")];
#else /* ... */
	char __buf[__COMPILER_LNEOF("/proc/self/fd/-128")];
#endif /* !... */
	(__NAMESPACE_LOCAL_SYM __localdep_sprintf)(__buf, "/proc/self/fd/%d", __execfd);
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_posix_spawn)(__pid, __buf, __file_actions, __attrp, ___argv, ___envp);
#endif /* ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC)) || !__POSIX_SPAWN_USE_KOS || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) || (!__CRT_HAVE_fexecve && (!__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve))) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_fspawn_np_defined
#define __local___localdep_posix_fspawn_np_defined
#define __localdep_posix_fspawn_np __LIBC_LOCAL_NAME(posix_fspawn_np)
#endif /* !__local___localdep_posix_fspawn_np_defined */
#else /* (((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE___libc_pipe || __CRT_HAVE__pipe) && __O_CLOEXEC)) && __POSIX_SPAWN_USE_KOS && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) && (__CRT_HAVE_fexecve || (__OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve)))) || (__OS_HAVE_PROCFS_SELF_FD && __CRT_HAVE_posix_spawn) */
#undef __local_posix_fspawn_np_defined
#endif /* (((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close && !__CRT_HAVE___libc_close) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE___libc_pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC)) || !__POSIX_SPAWN_USE_KOS || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) || (!__CRT_HAVE_fexecve && (!__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve)))) && (!__OS_HAVE_PROCFS_SELF_FD || !__CRT_HAVE_posix_spawn) */
#endif /* !__local_posix_fspawn_np_defined */
