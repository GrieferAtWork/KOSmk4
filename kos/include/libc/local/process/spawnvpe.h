/* HASH CRC-32:0xfdb96553 */
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
#ifndef __local_spawnvpe_defined
#define __local_spawnvpe_defined 1
#include <__crt.h>
#include <hybrid/__alloca.h>
#include <libc/local/environ.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <asm/os/vfork.h>
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve) || ((defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)))))) && defined(__hybrid_alloca)
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
/* Dependency: getenv from stdlib */
#ifndef __local___localdep_getenv_defined
#define __local___localdep_getenv_defined 1
#ifdef __CRT_HAVE_getenv
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_getenv,(char const *__varname),getenv,(__varname))
#elif defined(__LOCAL_environ)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/getenv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getenv __LIBC_LOCAL_NAME(getenv)
#else /* ... */
#undef __local___localdep_getenv_defined
#endif /* !... */
#endif /* !__local___localdep_getenv_defined */
/* Dependency: spawnve from process */
#ifndef __local___localdep_spawnve_defined
#define __local___localdep_spawnve_defined 1
#ifdef __CRT_HAVE_spawnve
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_spawnve,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV, __TENVP),spawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE__spawnve)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_spawnve,(__STDC_INT_AS_UINT_T __mode, char const *__restrict __path, __TARGV, __TENVP),_spawnve,(__mode,__path,___argv,___envp))
#elif (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))) && (defined(__CRT_HAVE_fspawnve) || ((defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && ((defined(__ARCH_HAVE_SHARED_VM_VFORK) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork))) || ((defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork)) && (defined(__CRT_HAVE_pipe2) || defined(__CRT_HAVE_pipe) || defined(__CRT_HAVE___pipe) || defined(__CRT_HAVE__pipe)) && defined(__O_CLOEXEC) && (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) && (defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)) && (defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close)))) && defined(__CRT_HAVE_fexecve) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid))))
__NAMESPACE_LOCAL_END
#include <libc/local/process/spawnve.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_spawnve __LIBC_LOCAL_NAME(spawnve)
#else /* ... */
#undef __local___localdep_spawnve_defined
#endif /* !... */
#endif /* !__local___localdep_spawnve_defined */
/* Dependency: strchr from string */
#ifndef __local___localdep_strchr_defined
#define __local___localdep_strchr_defined 1
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
#elif __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
#elif defined(__CRT_HAVE_strchr)
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#elif defined(__CRT_HAVE_index)
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strchr.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
#define __localdep_strchr __LIBC_LOCAL_NAME(strchr)
#endif /* !... */
#endif /* !__local___localdep_strchr_defined */
/* Dependency: strchrnul from string */
#ifndef __local___localdep_strchrnul_defined
#define __local___localdep_strchrnul_defined 1
#ifdef __CRT_HAVE_strchrnul
/* >> strchrnul(3)
 * Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchrnul,(char const *__restrict __haystack, int __needle),strchrnul,(__haystack,__needle))
#else /* __CRT_HAVE_strchrnul */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strchrnul.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strchrnul(3)
 * Same as `strchr', but return `strend(str)', rather than `NULL' if `needle' wasn't found. */
#define __localdep_strchrnul __LIBC_LOCAL_NAME(strchrnul)
#endif /* !__CRT_HAVE_strchrnul */
#endif /* !__local___localdep_strchrnul_defined */
/* Dependency: strlen from string */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__spawnvpe_impl) __ATTR_NOINLINE __ATTR_NONNULL((2, 4, 6, 7)) __pid_t
(__LIBCCALL __spawnvpe_impl)(__STDC_INT_AS_UINT_T __mode,
                             char const *__restrict __path, __SIZE_TYPE__ __path_len,
                             char const *__restrict __file, __SIZE_TYPE__ __file_len,
                             __TARGV, __TENVP) {
	char *__fullpath, *__dst;
#ifdef _WIN32
	while (__path_len && (__path[__path_len - 1] == '/' ||
	                    __path[__path_len - 1] == '\\'))
		--__path_len;
#else /* _WIN32 */
	while (__path_len && __path[__path_len - 1] == '/')
		--__path_len;
#endif /* !_WIN32 */
	__fullpath = (char *)__hybrid_alloca((__path_len + 1 + __file_len + 1) *
	                                   sizeof(char));
	__dst = (char *)__mempcpyc(__fullpath, __path, __path_len, sizeof(char));
	*__dst++ = '/';
	__dst = (char *)__mempcpyc(__dst, __file, __file_len, sizeof(char));
	*__dst = '\0';
	return (__NAMESPACE_LOCAL_SYM __localdep_spawnve)(__mode, __fullpath, ___argv, ___envp);
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(spawnvpe) __ATTR_NONNULL((2, 3, 4)) __pid_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(spawnvpe))(__STDC_INT_AS_UINT_T __mode, char const *__restrict __file, __TARGV, __TENVP) {
	char *__env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the  specified
	 * pathname is executed.
	 * [...] */
#ifdef _WIN32
	if (__localdep_strchr(__file, '/') || __localdep_strchr(__file, '\\'))
		return __localdep_spawnve(__mode, __file, ___argv, ___envp);
#else /* _WIN32 */
	if (__localdep_strchr(__file, '/'))
		return __localdep_spawnve(__mode, __file, ___argv, ___envp);
#endif /* !_WIN32 */
	__env_path = __localdep_getenv("PATH");
	if (__env_path && *__env_path) {
		__SIZE_TYPE__ __filelen;
		__filelen  = __localdep_strlen(__file);
		for (;;) {
			__pid_t __result;
			char *__path_end;
#ifdef _WIN32
			__path_end = __localdep_strchrnul(__env_path, ';');
#else /* _WIN32 */
			__path_end = __localdep_strchrnul(__env_path, ':');
#endif /* !_WIN32 */
			__result = (__NAMESPACE_LOCAL_SYM __spawnvpe_impl)(__mode, __env_path, (__SIZE_TYPE__)(__path_end - __env_path),
			                                                 __file, __filelen, ___argv, ___envp);
			if (__result >= 0)
				return __result;
			if (!*__path_end)
				break;
			__env_path = __path_end + 1;
		}
	} else {
#ifdef __ENOENT
		__libc_seterrno(__ENOENT);
#endif /* __ENOENT */
	}
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_spawnvpe_defined
#define __local___localdep_spawnvpe_defined 1
#define __localdep_spawnvpe __LIBC_LOCAL_NAME(spawnvpe)
#endif /* !__local___localdep_spawnvpe_defined */
#else /* (__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve || ((__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) && (__CRT_HAVE_fspawnve || ((__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && ((__ARCH_HAVE_SHARED_VM_VFORK && (__CRT_HAVE_vfork || __CRT_HAVE___vfork)) || ((__CRT_HAVE_fork || __CRT_HAVE___fork) && (__CRT_HAVE_pipe2 || __CRT_HAVE_pipe || __CRT_HAVE___pipe || __CRT_HAVE__pipe) && __O_CLOEXEC && (__CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read) && (__CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write) && (__CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close))) && __CRT_HAVE_fexecve && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid))))) && __hybrid_alloca */
#undef __local_spawnvpe_defined
#endif /* (!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve && ((!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) || (!__CRT_HAVE_fspawnve && ((!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || ((!__ARCH_HAVE_SHARED_VM_VFORK || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork)) && ((!__CRT_HAVE_fork && !__CRT_HAVE___fork) || (!__CRT_HAVE_pipe2 && !__CRT_HAVE_pipe && !__CRT_HAVE___pipe && !__CRT_HAVE__pipe) || !__O_CLOEXEC || (!__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read) || (!__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write) || (!__CRT_HAVE_close && !__CRT_HAVE__close && !__CRT_HAVE___close))) || !__CRT_HAVE_fexecve || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid))))) || !__hybrid_alloca */
#endif /* !__local_spawnvpe_defined */
