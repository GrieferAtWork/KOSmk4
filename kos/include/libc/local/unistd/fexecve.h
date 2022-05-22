/* HASH CRC-32:0xb1e0bf6b */
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
#ifndef __local_fexecve_defined
#define __local_fexecve_defined
#include <__crt.h>
#include <asm/os/features.h>
#if defined(__OS_HAVE_PROCFS_SELF_FD) && (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve))
#include <features.h>
#include <bits/types.h>
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
#ifndef __local___localdep_execve_defined
#define __local___localdep_execve_defined
#if __has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_execve)
__CEIREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),execve,{ return __builtin_execve(__path, (char *const *)___argv, (char *const *)___envp); })
#elif defined(__CRT_HAVE_execve)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE__execve)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),_execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE___execve)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),__execve,(__path,___argv,___envp))
#elif defined(__CRT_HAVE___libc_execve)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO(3),int,__NOTHROW_RPC,__localdep_execve,(char const *__restrict __path, __TARGV, __TENVP),__libc_execve,(__path,___argv,___envp))
#else /* ... */
#undef __local___localdep_execve_defined
#endif /* !... */
#endif /* !__local___localdep_execve_defined */
#ifndef __local___localdep_sprintf_defined
#define __local___localdep_sprintf_defined
#if __has_builtin(__builtin_sprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf) && __has_builtin(__builtin_va_arg_pack)
__CEIREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __ATTR_LIBC_PRINTF(2, 3),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_sprintf,(char *__restrict __buf, char const *__restrict __format, ...),sprintf,{ return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sprintf)
__LIBC __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("sprintf");
#elif defined(__CRT_HAVE__IO_sprintf)
__LIBC __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __ATTR_LIBC_PRINTF(2, 3) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("_IO_sprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/sprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sprintf __LIBC_LOCAL_NAME(sprintf)
#endif /* !... */
#endif /* !__local___localdep_sprintf_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fexecve) __ATTR_ACCESS_RO(2) __ATTR_ACCESS_RO(3) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(fexecve))(__fd_t __execfd, __TARGV, __TENVP) {
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
	return (__NAMESPACE_LOCAL_SYM __localdep_execve)(__buf, ___argv, ___envp);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fexecve_defined
#define __local___localdep_fexecve_defined
#define __localdep_fexecve __LIBC_LOCAL_NAME(fexecve)
#endif /* !__local___localdep_fexecve_defined */
#else /* __OS_HAVE_PROCFS_SELF_FD && (__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) */
#undef __local_fexecve_defined
#endif /* !__OS_HAVE_PROCFS_SELF_FD || (!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) */
#endif /* !__local_fexecve_defined */
