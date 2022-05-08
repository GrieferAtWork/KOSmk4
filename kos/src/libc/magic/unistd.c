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
%(c_prefix){
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/unistd.h) */
/* (#) Portability: DJGPP         (/include/unistd.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/unistd.h) */
/* (#) Portability: FreeBSD       (/include/unistd.h) */
/* (#) Portability: GNU C Library (/posix/unistd.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/unistd.h) */
/* (#) Portability: NetBSD        (/include/unistd.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/unistd.h) */
/* (#) Portability: OpenBSD       (/include/unistd.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/unistd.h) */
/* (#) Portability: avr-libc      (/include/unistd.h) */
/* (#) Portability: diet libc     (/include/unistd.h) */
/* (#) Portability: libbsd        (/include/bsd/unistd.h) */
/* (#) Portability: libc4/5       (/include/unistd.h) */
/* (#) Portability: libc6         (/include/unistd.h) */
/* (#) Portability: libcmini      (/include/unistd.h) */
/* (#) Portability: mintlib       (/include/unistd.h) */
/* (#) Portability: musl libc     (/include/unistd.h) */
/* (#) Portability: uClibc        (/include/unistd.h) */
}

%[define_replacement(fd_t       = __fd_t)]
%[define_replacement(off_t      = "__FS_TYPE(off)")]
%[define_replacement(pos_t      = "__FS_TYPE(pos)")]
%[define_replacement(uid_t      = __uid_t)]
%[define_replacement(gid_t      = __gid_t)]
%[define_replacement(pid_t      = __pid_t)]
%[define_replacement(off32_t    = __off32_t)]
%[define_replacement(off64_t    = __off64_t)]
%[define_replacement(pos32_t    = __pos32_t)]
%[define_replacement(pos64_t    = __pos64_t)]
%[define_replacement(atflag_t   = __atflag_t)]
%[define_replacement(useconds_t = __useconds_t)]
%[define_replacement(oflag_t    = __oflag_t)]
%[define_replacement(longptr_t  = __LONGPTR_TYPE__)]
%[define_replacement(ulongptr_t = __ULONGPTR_TYPE__)]
%[define_replacement(syscall_slong_t = __syscall_slong_t)]
%[define_replacement(syscall_ulong_t = __syscall_ulong_t)]

%[assume_defined_in_kos(STDIN_FILENO = "0")]
%[assume_defined_in_kos(STDOUT_FILENO = "1")]
%[assume_defined_in_kos(STDERR_FILENO = "2")]
%[assume_defined_in_kos(__STDIN_FILENO = "0")]
%[assume_defined_in_kos(__STDOUT_FILENO = "1")]
%[assume_defined_in_kos(__STDERR_FILENO = "2")]

%[assume_defined_in_kos(F_OK, __F_OK)]
%[assume_defined_in_kos(X_OK, __X_OK)]
%[assume_defined_in_kos(W_OK, __W_OK)]
%[assume_defined_in_kos(R_OK, __R_OK)]


%(auto_source){
#include "../libc/globals.h"
}

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

}%[insert:prefix(
#include <asm/crt/confname.h>
)]%[insert:prefix(
#include <asm/os/stdio.h>
)]%[insert:prefix(
#include <asm/os/vfork.h> /* os-specific vfork(2) caveats: __ARCH_HAVE_*_VFORK */
)]%[insert:prefix(
#include <asm/pagesize.h>
)]%[insert:prefix(
#include <bits/posix_opt.h>
)]%[insert:prefix(
#include <bits/crt/sys_errlist.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

#ifdef __USE_GNU
#include <linux/close_range.h>
#endif /* __USE_GNU */

#if defined(__CRT_GLC) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL)
#include <asm/unistd.h>
#endif /* __CRT_GLC || __CRT_KOS || __CRT_KOS_KERNEL */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
#include <bits/crt/environments.h>
#endif /* __USE_UNIX98 || __USE_XOPEN2K */

#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_POSIX))
#include <asm/os/fcntl.h> /* __F_ULOCK, __F_LOCK, __F_TLOCK, __F_TEST */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_POSIX) */

#ifdef __USE_NETBSD
#include <asm/os/signal.h> /* __NSIG */
#include <asm/crt/getpassfd.h> /* __GETPASS_* */
#endif /* __USE_NETBSD */

#ifdef __USE_KOS
#include <bits/crt/format-printer.h> /* __FORMATPRINTER_CC */
#endif /* __USE_KOS */

#ifdef __USE_SOLARIS
#include <getopt.h>
#define GF_PATH "/etc/group"
#define PF_PATH "/etc/passwd"
#endif /* __USE_SOLARIS */


#ifdef __USE_XOPEN2K8
#define _POSIX_VERSION 200809L
#elif defined(__USE_XOPEN2K)
#define _POSIX_VERSION 200112L
#elif defined(__USE_POSIX199506)
#define _POSIX_VERSION 199506L
#elif defined(__USE_POSIX199309)
#define _POSIX_VERSION 199309L
#else /* ... */
#define _POSIX_VERSION 199009L
#endif /* !... */

#ifdef __USE_XOPEN2K8
#define __POSIX2_THIS_VERSION 200809L
#elif defined(__USE_XOPEN2K)
#define __POSIX2_THIS_VERSION 200112L
#elif defined(__USE_POSIX199506)
#define __POSIX2_THIS_VERSION 199506L
#else /* ... */
#define __POSIX2_THIS_VERSION 199209L
#endif /* !... */

#define _POSIX2_VERSION   __POSIX2_THIS_VERSION
#define _POSIX2_C_VERSION __POSIX2_THIS_VERSION
#define _POSIX2_C_BIND    __POSIX2_THIS_VERSION
#define _POSIX2_C_DEV     __POSIX2_THIS_VERSION
#define _POSIX2_SW_DEV    __POSIX2_THIS_VERSION
#define _POSIX2_LOCALEDEF __POSIX2_THIS_VERSION

#ifdef __USE_XOPEN2K8
#define _XOPEN_VERSION 700
#elif defined(__USE_XOPEN2K)
#define _XOPEN_VERSION 600
#elif defined(__USE_UNIX98)
#define _XOPEN_VERSION 500
#else /* ... */
#define _XOPEN_VERSION 4
#endif /* !... */
#define _XOPEN_XCU_VERSION 4
#define _XOPEN_XPG2        1
#define _XOPEN_XPG3        1
#define _XOPEN_XPG4        1
#define _XOPEN_UNIX        1
#define _XOPEN_CRYPT       1
#define _XOPEN_ENH_I18N    1
#define _XOPEN_LEGACY      1


#ifdef __STDIN_FILENO
#define STDIN_FILENO  __STDIN_FILENO  /* Standard input. */
#endif /* __STDIN_FILENO */
#ifdef __STDOUT_FILENO
#define STDOUT_FILENO __STDOUT_FILENO /* Standard output. */
#endif /* __STDOUT_FILENO */
#ifdef __STDERR_FILENO
#define STDERR_FILENO __STDERR_FILENO /* Standard error output. */
#endif /* __STDERR_FILENO */

#if !defined(R_OK) && defined(__R_OK)
#define R_OK __R_OK /* Test for read permission. */
#endif /* !R_OK && __R_OK */
#if !defined(W_OK) && defined(__W_OK)
#define W_OK __W_OK /* Test for write permission. */
#endif /* !W_OK && __W_OK */
#if !defined(X_OK) && defined(__X_OK)
#define X_OK __X_OK /* Test for execute permission. */
#endif /* !X_OK && __X_OK */
#if !defined(F_OK) && defined(__F_OK)
#define F_OK __F_OK /* Test for existence. */
#endif /* !F_OK && __F_OK */

#if !defined(SEEK_SET) && defined(__SEEK_SET)
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#endif /* !SEEK_SET && __SEEK_SET */
#if !defined(SEEK_CUR) && defined(__SEEK_CUR)
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#endif /* !SEEK_CUR && __SEEK_CUR */
#if !defined(SEEK_END) && defined(__SEEK_END)
#define SEEK_END __SEEK_END /* Seek from end of file. */
#endif /* !SEEK_END && __SEEK_END */
#if defined(__USE_GNU) || defined(__USE_SOLARIS)
#if !defined(SEEK_DATA) && defined(__SEEK_DATA)
#define SEEK_DATA __SEEK_DATA /* Seek to next data. */
#endif /* !SEEK_DATA && __SEEK_DATA */
#if !defined(SEEK_HOLE) && defined(__SEEK_HOLE)
#define SEEK_HOLE __SEEK_HOLE /* Seek to next hole. */
#endif /* !SEEK_HOLE && __SEEK_HOLE */
#endif /* __USE_GNU || __USE_SOLARIS */

#ifdef __USE_MISC
#if !defined(L_SET) && defined(__SEEK_SET)
#define L_SET  __SEEK_SET /* Seek from beginning of file. */
#endif /* !L_SET && __SEEK_SET */
#if !defined(L_CURR) && defined(__SEEK_CUR)
#define L_CURR __SEEK_CUR /* Seek from current position. */
#endif /* !L_CURR && __SEEK_CUR */
#if !defined(L_INCR) && defined(__SEEK_CUR)
#define L_INCR __SEEK_CUR /* Seek from current position. */
#endif /* !L_INCR && __SEEK_CUR */
#if !defined(L_XTND) && defined(__SEEK_END)
#define L_XTND __SEEK_END /* Seek from end of file. */
#endif /* !L_XTND && __SEEK_END */
#endif /* __USE_MISC */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __gid_t_defined
#define __gid_t_defined
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */
#ifndef __uid_t_defined
#define __uid_t_defined
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
#ifndef __off_t_defined
#define __off_t_defined
typedef __FS_TYPE(off) off_t;
#endif /* !__off_t_defined */
#ifndef __useconds_t_defined
#define __useconds_t_defined
typedef __useconds_t useconds_t;
#endif /* !__useconds_t_defined */
#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#ifdef __USE_LARGEFILE64
#ifndef __off64_t_defined
#define __off64_t_defined
typedef __off64_t off64_t;
#endif /* !__off64_t_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#ifndef __intptr_t_defined
#define __intptr_t_defined
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef __socklen_t_defined
#define __socklen_t_defined
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */

#ifndef __environ
#if defined(environ)
#define __environ environ
#elif defined(_environ)
#define __environ _environ
#elif defined(__LOCAL_environ)
#define __environ __LOCAL_environ
#elif defined(__CRT_HAVE_environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,environ)
#define environ   environ
#define __environ environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,__environ,environ)
#define __environ __environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE__environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,_environ)
#define _environ  _environ
#define __environ _environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,__environ,_environ)
#define __environ __environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___environ)
__CSDECLARE(,char **,__environ)
#define __environ __environ
#elif defined(____p__environ_defined)
#define __environ (*__p__environ())
#elif defined(__CRT_HAVE___p__environ)
#define ____p__environ_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#define __environ (*__p__environ())
#elif defined(__CRT_HAVE__get_environ)
#ifndef ___get_environ_defined
#define ___get_environ_defined
__CDECLARE(,int,__NOTHROW,_get_environ,(char ***__p_environ),())
#endif /* !___get_environ_defined */
#ifndef _____get_environ_wrapper_defined
#define _____get_environ_wrapper_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST char **
__NOTHROW(__LIBCCALL ___get_environ_wrapper)(void) {
	char **__result;
	if __unlikely(_get_environ(&__result) != 0)
		__result = __NULLPTR;
	return __result;
}
#endif /* !_____get_environ_wrapper_defined */
#define __environ ___get_environ_wrapper()
#endif /* !... */
#endif /* !__environ */

}

%(user){
#ifndef __KERNEL__
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char ***NOTHROW(LIBCCALL libc_p_environ)(void);
#endif /* !__KERNEL__ */
};

%[default:section(".text.crt{|.dos}.fs.exec.exec")];

%[define(DEFINE_TARGV =
@@pp_ifndef __TARGV@@
@@pp_ifdef __USE_DOS_ALTERATIONS@@
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
@@pp_else@@
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
@@pp_endif@@
@@pp_endif@@
)]


@@>> execv(3)
@@Replace the calling  process with  the application  image referred  to by  `path' /  `file'
@@and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
[[cp, guard, dos_export_alias("_execv"), argument_names(path, ___argv)]]
[[if(__has_builtin(__builtin_execv) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(execv, { return __builtin_execv(path, (char *const *)___argv); })]]
[[requires_include("<libc/template/environ.h>"), requires($has_function(execve) && defined(__LOCAL_environ))]]
[[impl_include("<libc/template/environ.h>"), crt_dos_variant]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
int execv([[nonnull]] char const *__restrict path, [[nonnull]] __TARGV) {
	return execve(path, ___argv, __LOCAL_environ);
}

@@>> execve(2)
@@Replace the calling  process with  the application  image referred  to by  `path' /  `file'
@@and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
[[cp, guard, dos_export_alias("_execve"), export_alias("__execve", "__libc_execve"), argument_names(path, ___argv, ___envp)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV), crt_dos_variant]]
[[if(__has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(execve, { return __builtin_execve(path, (char *const *)___argv, (char *const *)___envp); })]]
int execve([[nonnull]] char const *__restrict path, [[nonnull]] __TARGV, [[nonnull]] __TENVP);

@@>> execvp(3)
@@Replace the calling  process with  the application  image referred  to by  `path' /  `file'
@@and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
[[cp, guard, dos_export_alias("_execvp"), argument_names(file, ___argv)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV), crt_dos_variant]]
[[if(__has_builtin(__builtin_execvp) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(execvp, { return __builtin_execvp(file, (char *const *)___argv); })]]
[[requires_include("<libc/template/environ.h>"), requires($has_function(execvpe) && defined(__LOCAL_environ))]]
[[impl_include("<libc/template/environ.h>")]]
int execvp([[nonnull]] char const *__restrict file, [[nonnull]] __TARGV) {
	return execvpe(file, ___argv, __LOCAL_environ);
}


@@>> execl(3)
@@Replace the calling process with the application image referred to by `path' / `file'
@@and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list
[[cp, guard, ATTR_SENTINEL, dos_export_alias("_execl"), impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function(execv), crtbuiltin, crt_dos_variant]]
int execl([[nonnull]] char const *__restrict path, char const *args, ... /*, (char *)NULL*/) {
	__REDIRECT_EXECL(char, execv, path, args)
}

@@>> execle(3)
@@Replace the calling process with the application image referred to by `path' / `file'
@@and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
@@and setting `environ' to a `char **' passed after the NULL sentinel
[[cp, guard, impl_include("<parts/redirect-exec.h>"), dos_export_alias("_execle"), crtbuiltin]]
[[requires_dependent_function(execve), ATTR_SENTINEL_O(1), crt_dos_variant]]
int execle([[nonnull]] char const *__restrict path, char const *args, ... /*, (char *)NULL, (char **)environ*/) {
	__REDIRECT_EXECLE(char, execve, path, args)
}

@@>> execlp(3)
@@Replace the calling process with the application image referred to by `path' / `file'
@@and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list
[[cp, guard, impl_include("<parts/redirect-exec.h>"), dos_export_alias("_execlp")]]
[[requires_dependent_function(execvp), ATTR_SENTINEL, crtbuiltin, crt_dos_variant]]
int execlp([[nonnull]] char const *__restrict file, char const *args, ... /*, (char *)NULL*/) {
	__REDIRECT_EXECL(char, execvp, file, args)
}

%
%#if defined(__USE_KOS) || defined(__USE_DOS) || defined(__USE_GNU) || defined(__USE_NETBSD)
@@>> execvpe(3)
@@Replace the  calling process  with the  application  image referred  to by  `file'  and
@@execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
[[cp, guard, dos_export_alias("_execvpe"), argument_names(file, ___argv, ___envp)]]
[[requires_include("<hybrid/__alloca.h>"), dependency(mempcpyc)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV)]]
[[requires($has_function(getenv) && $has_function(execve) && defined(__hybrid_alloca))]]
[[crt_dos_variant({
prefix: {
@@push_namespace(local)@@
__LOCAL_LIBC(__dos_execvpe_impl) __ATTR_NOINLINE __ATTR_NONNULL((1, 3, 5, 6)) int
(__LIBCCALL __dos_execvpe_impl)(char const *__restrict path, $size_t path_len,
                                char const *__restrict file, $size_t file_len,
                                __TARGV, __TENVP) {
	char *fullpath, *dst;
	while (path_len && (path[path_len - 1] == '/' ||
	                    path[path_len - 1] == '\\'))
		--path_len;
	fullpath = (char *)__hybrid_alloca((path_len + 1 + file_len + 1) *
	                                   sizeof(char));
	dst = (char *)mempcpyc(fullpath, path, path_len, sizeof(char));
	*dst++ = '/';
	dst = (char *)mempcpyc(dst, file, file_len, sizeof(char));
	*dst = '\0';
	return libd_execve(fullpath, ___argv, ___envp);
}
@@pop_namespace@@
},
impl: {
	char *env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the  specified
	 * pathname is executed.
	 * [...] */
	if (strchr(file, '/') || strchr(file, '\\'))
		return execve(file, ___argv, ___envp);
	env_path = getenv("PATH");
	if (env_path && *env_path) {
		size_t filelen;
		filelen = strlen(file);
		for (;;) {
			char *path_end;
			path_end = strchrnul(env_path, ';');
			(__NAMESPACE_LOCAL_SYM __dos_execvpe_impl)(env_path, (size_t)(path_end - env_path),
			                                           file, filelen, ___argv, ___envp);
			if (!*path_end)
				break;
			env_path = path_end + 1;
		}
	} else {
@@pp_ifdef ENOENT@@
		(void)libc_seterrno(ENOENT);
@@pp_endif@@
	}
	return -1;
}
})]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_include("<libc/errno.h>")]]
[[impl_prefix(
@@push_namespace(local)@@
__LOCAL_LIBC(__execvpe_impl) __ATTR_NOINLINE __ATTR_NONNULL((1, 3, 5, 6)) int
(__LIBCCALL __execvpe_impl)(char const *__restrict path, $size_t path_len,
                            char const *__restrict file, $size_t file_len,
                            __TARGV, __TENVP) {
	char *fullpath, *dst;
@@pp_ifdef _WIN32@@
	while (path_len && (path[path_len - 1] == '/' ||
	                    path[path_len - 1] == '\\'))
		--path_len;
@@pp_else@@
	while (path_len && path[path_len - 1] == '/')
		--path_len;
@@pp_endif@@
	fullpath = (char *)__hybrid_alloca((path_len + 1 + file_len + 1) *
	                                   sizeof(char));
	dst = (char *)mempcpyc(fullpath, path, path_len, sizeof(char));
	*dst++ = '/';
	dst = (char *)mempcpyc(dst, file, file_len, sizeof(char));
	*dst = '\0';
	return execve(fullpath, ___argv, ___envp);
}
@@pop_namespace@@
)]]
int execvpe([[nonnull]] char const *__restrict file,
            [[nonnull]] __TARGV, [[nonnull]] __TENVP) {
	char *env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the  specified
	 * pathname is executed.
	 * [...] */
@@pp_ifdef _WIN32@@
	if (strchr(file, '/') || strchr(file, '\\'))
		return execve(file, ___argv, ___envp);
@@pp_else@@
	if (strchr(file, '/'))
		return execve(file, ___argv, ___envp);
@@pp_endif@@
	env_path = getenv("PATH");
	if (env_path && *env_path) {
		size_t filelen;
		filelen = strlen(file);
		for (;;) {
			char *path_end;
@@pp_ifdef _WIN32@@
			path_end = strchrnul(env_path, ';');
@@pp_else@@
			path_end = strchrnul(env_path, ':');
@@pp_endif@@
			(__NAMESPACE_LOCAL_SYM __execvpe_impl)(env_path, (size_t)(path_end - env_path),
			                                       file, filelen, ___argv, ___envp);
			if (!*path_end)
				break;
			env_path = path_end + 1;
		}
	} else {
@@pp_ifdef ENOENT@@
		(void)libc_seterrno(ENOENT);
@@pp_endif@@
	}
	return -1;
}

%#endif /* __USE_KOS || __USE_DOS || __USE_GNU || __USE_NETBSD */

%
%#if defined(__USE_KOS) || defined(__USE_DOS) || defined(__USE_NETBSD)
@@>> execlpe(3)
@@Replace the calling process with the application image referred to by `path' / `file'
@@and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
@@and setting `environ' to a `char **' passed after the NULL sentinel
[[cp, guard, impl_include("<parts/redirect-exec.h>"), dos_export_alias("_execlpe")]]
[[requires_dependent_function(execvpe), ATTR_SENTINEL_O(1), crt_dos_variant]]
int execlpe([[nonnull]] char const *__restrict file, char const *args, ... /*, (char *)NULL, (char **)environ*/) {
	__REDIRECT_EXECLE(char, execvpe, file, args)
}
%#endif /* __USE_KOS || __USE_DOS || __USE_NETBSD */

%[default:section(".text.crt{|.dos}.sched.process")]

@@>> getpid(2)
@@Return the PID of the calling process (that is the TID of the calling thread group's leader)
@@THIS_THREAD->LEADER->PID
[[guard, const, wunused, nothrow]]
[[dos_only_export_alias("_getpid"), export_alias("__getpid", "__libc_getpid")]]
$pid_t getpid();

%#ifdef __USE_KOS
@@>> gettid(2)
@@Return the TID of the calling thread
@@THIS_THREAD->PID
[[guard, const, wunused, nothrow]]
[[section(".text.crt{|.dos}.sched.thread")]]
[[dos_only_export_alias("__threadid", "?GetCurrentThreadId@platform@details@Concurrency@@YAJXZ")]]
$pid_t gettid();
%#endif /* __USE_KOS */

[[ignore, nocrt, alias("_pipe")]]
[[decl_include("<bits/types.h>")]]
int dos_pipe([[nonnull]] $fd_t pipedes[2],
             $uint32_t pipesize, $oflag_t textmode);

@@>> pipe(2)
@@Create a new pair of connected pipes ([0] = reader, [1] = writer)
@@@param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
@@@return: 0:  Success
@@@return: -1: Error (s.a. `errno')
[[section(".text.crt{|.dos}.io.access"), export_alias("__pipe", "__libc_pipe")]]
[[userimpl, requires_function(dos_pipe)]]
[[decl_include("<bits/types.h>")]]
int pipe([[nonnull]] $fd_t pipedes[2]) {
	return dos_pipe(pipedes, 4096, 0x8000); /* O_BINARY */
}

@@>> sleep(3)
@@Sleep for up to `seconds' seconds
@@@return: 0 : Timeout expired
@@@return: * : You were interrupted, and this many seconds were still left on the timeout
[[cp, guard, section(".text.crt{|.dos}.system.utility")]]
[[userimpl, requires($has_function(nanosleep) || $has_function(_sleep))]]
[[impl_include("<bits/os/timespec.h>")]]
[[impl_include("<libc/errno.h>")]]
unsigned int sleep(unsigned int seconds) {
@@pp_if $has_function(nanosleep)@@
	struct timespec ts, rem;
	ts.@tv_sec@   = seconds;
	ts.@tv_nsec@  = 0;
	rem.@tv_sec@  = 0;
	rem.@tv_nsec@ = 0;
	if (nanosleep(&ts, &rem) == 0) {
		rem.@tv_sec@ = 0;
	} else {
@@pp_if defined(__libc_geterrno) && defined(EINTR)@@
		if (__libc_geterrno() != EINTR)
			rem.@tv_sec@ = 0;
@@pp_endif@@
	}
	return (unsigned int)rem.@tv_sec@;
@@pp_else@@
	_sleep((uint32_t)seconds * 1000);
	return 0;
@@pp_endif@@
}

@@>> fsync(2)
@@Synchronize a file (including its descriptor which contains timestamps, and its size),
@@meaning  that  changes   to  its   data  and/or   descriptor  are   written  to   disk
[[cp, decl_include("<bits/types.h>")]]
[[dos_only_export_alias("_commit")]]
[[export_alias("__fsync", "__libc_fsync")]]
[[alias("fdatasync", "__fdatasync")]]
[[userimpl, section(".text.crt{|.dos}.io.sync")]]
int fsync($fd_t fd) {
	(void)fd;
	/* NO-OP */
	return 0;
}


@@>> getppid(2)
@@Return the PID of the calling process's parent.
@@(That is the TID of the leader of the parent of the calling thread's leader)
@@THIS_THREAD->LEADER->PARENT->LEADER->PID
[[wunused, decl_include("<bits/types.h>")]]
[[export_alias("__getppid", "__libc_getppid")]]
$pid_t getppid();


@@>> getpgrp(2)
@@Return the ID of the calling process's process group.
@@(That is the TID of the leader of the process group of the calling thread's leader)
@@THIS_THREAD->LEADER->GROUP_LEADER->PID
[[wunused, decl_include("<bits/types.h>")]]
[[export_alias("__getpgrp", "__libc_getpgrp")]]
$pid_t getpgrp();

%[insert:function(__getpgid = getpgid)]

@@>> setpgid(2)
@@Change  the ID of  the process group  associated with `pid's process.
@@(That is the TID of the leader of the process group of `pid's leader)
@@THREAD[PID]->LEADER->GROUP_LEADER = THREAD[PGID]
@@When `pid' is ZERO(0), use `gettid()' for it instead.
@@When `pgid' is ZERO(0), use `pid' (after it was substituted) for instead
[[decl_include("<bits/types.h>")]]
[[export_alias("__setpgid", "__libc_setpgid")]]
int setpgid($pid_t pid, $pid_t pgid);

@@>> setsid(2)
@@Make the calling thread's process the leader of its associated
@@process group, before also making  it its own session  leader.
@@Then return the TID of that new session leader, which is also the PID of the calling process.
@@ - THIS_THREAD->LEADER->GROUP_LEADER                 = THIS_THREAD->LEADER;
@@ - THIS_THREAD->LEADER->GROUP_LEADER->SESSION_LEADER = THIS_THREAD->LEADER->GROUP_LEADER;
@@ - return THIS_THREAD->LEADER->PID;
[[decl_include("<bits/types.h>")]]
[[export_alias("__setsid", "__libc_setsid")]]
$pid_t setsid();

%[default:section(".text.crt{|.dos}.sched.user")]

@@>> getuid(2)
@@Return the real user ID of the calling process
[[wunused, decl_include("<bits/types.h>")]]
[[export_alias("__getuid", "__libc_getuid")]]
$uid_t getuid();

@@>> getgid(2)
@@Return the real group ID of the calling process
[[wunused, decl_include("<bits/types.h>")]]
[[export_alias("__getgid", "__libc_getgid")]]
$gid_t getgid();

@@>> geteuid(2)
@@Return the effective user ID of the calling process
[[wunused, decl_include("<bits/types.h>")]]
[[export_alias("__geteuid", "__libc_geteuid")]]
$uid_t geteuid();

@@>> getegid(2)
@@Return the effective group ID of the calling process
[[wunused, decl_include("<bits/types.h>")]]
[[export_alias("__getegid", "__libc_getegid")]]
$gid_t getegid();

@@>> getgroups(2)
@@@return: * : [count == 0] The required number of groups
@@@return: * : [count != 0] The number of groups that were actually returned
@@@return: -1: [errno == -EINVAL && count != 0] There are more than `count' groups
[[decl_include("<bits/types.h>")]]
[[export_alias("__getgroups", "__libc_getgroups")]]
int getgroups(int size, $gid_t list[]);

@@>> setuid(2)
@@Set the effective user ID of the calling process
@@@return: 0 : Success
@@@return: -1: [errno=EINVAL] : The given `uid' is invalid
@@@return: -1: [errno=EPERM]  : The current user is not privileged
[[decl_include("<bits/types.h>")]]
[[export_alias("__setuid", "__libc_setuid")]]
int setuid($uid_t uid);

@@>> setgid(2)
@@Set the effective group ID of the calling process
@@@return: 0 : Success
@@@return: -1: [errno=EINVAL] : The given `gid' is invalid
@@@return: -1: [errno=EPERM]  : The current user is not privileged
[[decl_include("<bits/types.h>")]]
[[export_alias("__setgid", "__libc_setgid")]]
int setgid($gid_t gid);


@@>> fork(2)
@@Clone the calling thread into a second process and return twice, once
@@in  the parent process where this function returns the (non-zero) PID
@@of  the forked child process, and a  second time in the child process
@@itself, where ZERO(0) is returned.
@@The child then usually proceeds by calling `exec(2)' to replace its
@@application image with  that of another  program that the  original
@@parent can then `wait(2)' for. (s.a. `vfork(2)')
@@@return: 0 : You're the new process that was created
@@@return: * : The `return' value is the pid of your new child process
[[crtbuiltin, wunused, export_alias("__fork", "__libc_fork")]]
[[section(".text.crt{|.dos}.sched.access")]]
[[decl_include("<bits/types.h>")]]
$pid_t fork();


%[default:section(".text.crt{|.dos}.system.utility")]

@@>> alarm(2)
@@@return: 0 : No alarm was scheduled before.
@@@return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
@@Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
@@You may pass `0' for `seconds' to disable a previously scheduled alarm
[[export_alias("__alarm", "__libc_alarm")]]
unsigned int alarm(unsigned int seconds);

@@>> pause(2)
@@Suspend execution until the delivery of a POSIX_SIGNAL
[[cp]]
[[export_alias("__pause", "__libc_pause")]]
int pause();

@@>> fpathconf(2)
@@@param: name: One   of    `_PC_*'    from    <asm/crt/confname.h>
@@Return a path configuration value associated with `name' for `fd'
@@return: * : The configuration limit associated with `name' for `fd'
@@return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `fd'
@@return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option
[[cp, wunused, decl_include("<features.h>", "<bits/types.h>")]]
[[export_alias("__fpathconf"), section(".text.crt{|.dos}.fs.property")]]
$longptr_t fpathconf($fd_t fd, __STDC_INT_AS_UINT_T name);

%[default:section(".text.crt{|.dos}.io.tty")]

@@>> ttyname(3)
@@Return the name of a TTY given its file descriptor
[[guard, cp, wunused, decl_include("<bits/types.h>")]]
[[export_alias("__ttyname"), requires_function(ttyname_r)]]
char *ttyname($fd_t fd) {
	static char buf[32];
	if likely(ttyname_r(fd, buf, sizeof(buf)) == 0)
		return buf;
	return NULL;
}

@@>> ttyname_r(3)
@@Return the name of a TTY given its file descriptor
[[cp, decl_include("<bits/types.h>")]]
int ttyname_r($fd_t fd, [[outp(buflen)]] char *buf, size_t buflen);

@@>> tcgetpgrp(2)
@@Return the foreground process group of a given TTY file descriptor
[[wunused, decl_include("<bits/types.h>")]]
$pid_t tcgetpgrp($fd_t fd);

@@>> tcsetpgrp(2)
@@Set the foreground process group of a given TTY file descriptor
[[decl_include("<bits/types.h>")]]
int tcsetpgrp($fd_t fd, $pid_t pgrp_id);

@@>> getlogin(3)
@@Return the login name for the current user, or `NULL' on error.
@@s.a. `getlogin_r()' and `cuserid()'
[[section(".text.crt{|.dos}.io.tty")]]
[[guard, wunused, requires($has_function(getenv) || $has_function(cuserid))]]
char *getlogin() {
@@pp_if $has_function(getenv) && $has_function(cuserid)@@
	char *result = getenv("LOGNAME");
	if (!result)
		result = cuserid(NULL);
	return result;
@@pp_elif $has_function(getenv)@@
	return getenv("LOGNAME");
@@pp_else@@
	return cuserid(NULL);
@@pp_endif@@
}

%[default:section(".text.crt{|.dos}.fs.modify")]

@@>> chown(2)
@@Change the ownership of a given `file' to `group:owner'
[[crt_dos_variant, cp, decl_include("<bits/types.h>")]]
[[userimpl, requires_include("<asm/os/fcntl.h>"), export_alias("__chown", "__libc_chown")]]
[[requires(defined(__AT_FDCWD) && $has_function(fchownat))]]
int chown([[nonnull]] char const *file, $uid_t owner, $gid_t group) {
	return fchownat(__AT_FDCWD, file, owner, group, 0);
}

@@>> pathconf(2)
@@@param: name: One of `_PC_*' from <asm/crt/confname.h>
@@Return a path configuration value associated with `name' for `path'
@@return: * : The configuration limit associated with `name' for `path'
@@return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
@@return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option
[[crt_dos_variant, cp, section(".text.crt{|.dos}.fs.property"), decl_include("<features.h>")]]
[[userimpl, requires_include("<asm/os/oflags.h>"), export_alias("__pathconf")]]
[[requires($has_function(fpathconf) && $has_function(open) && defined(__O_RDONLY))]]
$longptr_t pathconf([[nonnull]] char const *path, __STDC_INT_AS_UINT_T name) {
	fd_t fd;
	longptr_t result;
	fd = open(path, O_RDONLY);
	if unlikely(fd < 0)
		return -1;
	result = fpathconf(fd, name);
@@pp_if $has_function(close)@@
	close(fd);
@@pp_endif@@
	return result;
}

@@>> link(2)
@@Create a hard link from `from', leading to `to'
[[cp, userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(linkat))]]
[[crt_dos_variant, export_alias("__link", "__libc_link")]]
int link([[nonnull]] char const *from, [[nonnull]] char const *to) {
	/* TODO: Header-implementation for `link()' on DOS (using the windows API) */
	return linkat(__AT_FDCWD, from, __AT_FDCWD, to, 0);
}

%[default:section(".text.crt{|.dos}.sched.access")]
%[insert:extern(exit)]
%[default:section(".text.crt{|.dos}.fs.modify")]

@@>> read(2)
@@Read up to `bufsize' bytes from `fd' into `buf'
@@When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
@@available at the time the call was made, and throw E_WOULDBLOCK if no data
@@was available at the time.
@@@return: <= bufsize: The actual amount of read bytes
@@@return: 0         : EOF
[[dos_only_export_alias("_read"), export_alias("__read", "__libc_read")]]
[[cp, guard, decl_include("<bits/types.h>"), section(".text.crt{|.dos}.io.read")]]
ssize_t read($fd_t fd, [[outp(bufsize)]] void *buf, size_t bufsize);

@@>> write(2)
@@Write up to `bufsize' bytes from `buf' into `fd'
@@When `fd' has the `O_NONBLOCK' flag set, only write as much  data
@@as possible at the time the call was made, and throw E_WOULDBLOCK
@@if no data could be written at the time.
@@@return: <= bufsize: The actual amount of written bytes
@@@return: 0         : No more data can be written
[[dos_only_export_alias("_write"), export_alias("__write", "__libc_write")]]
[[cp, guard, decl_include("<bits/types.h>"), section(".text.crt{|.dos}.io.write")]]
ssize_t write($fd_t fd, [[inp(bufsize)]] void const *buf, size_t bufsize);

%#ifdef __USE_KOS
@@>> readall(3)
@@Same  as `read(2)', however  keep on reading until  `read()' indicates EOF (causing
@@`readall()' to immediately return `0') or the entirety of the given buffer has been
@@filled (in which case `bufsize' is returned).
@@If  an error occurs before all data could be read, try to use SEEK_CUR to rewind
@@the file descriptor by the amount of data that had already been loaded. - Errors
@@during this phase are silently ignored and don't cause `errno' to change
[[cp, guard, section(".text.crt{|.dos}.io.read"), impl_include("<libc/errno.h>")]]
[[userimpl, requires_function(read, lseek), decl_include("<bits/types.h>")]]
ssize_t readall($fd_t fd, [[outp(bufsize)]] void *buf, size_t bufsize) {
	ssize_t result, temp;
	result = read(fd, buf, bufsize);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = read(fd,
			            (byte_t *)buf + (size_t)result,
			            bufsize - (size_t)result);
			if (temp <= 0) {
@@pp_ifdef __libc_geterrno@@
				int old_error = __libc_geterrno();
@@pp_endif@@
				/* Try to un-read data that had already been loaded. */
				lseek(fd, -(off_t)(pos_t)result, SEEK_CUR);
@@pp_ifdef __libc_geterrno@@
				(void)libc_seterrno(old_error);
@@pp_endif@@
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}

@@>> writeall(3)
@@Same as `write(2)', however keep on  writing until `write()' indicates EOF  (causing
@@`writeall()' to immediately return `0') or the entirety of the given buffer has been
@@written (in which case `bufsize' is returned).
[[cp, guard, section(".text.crt{|.dos}.io.write"), impl_include("<libc/errno.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>", "<bits/crt/format-printer.h>")defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__), export_alias("write_printer")]]
[[userimpl, requires_function(write)]]
[[decl_include("<bits/types.h>")]]
ssize_t writeall($fd_t fd, [[inp(bufsize)]] void const *buf, size_t bufsize) {
	ssize_t result, temp;
	result = write(fd, buf, bufsize);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = write(fd,
			             (byte_t *)buf + (size_t)result,
			             bufsize - (size_t)result);
			if (temp <= 0) {
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}

@@>> write_printer(3)
@@A pformatprinter-compatible consumer that dumps all input data into `fd' by use
@@of `writeall(3)'. The given `fd' should be encoded by  `WRITE_PRINTER_ARG(fd)'.
@@@return: * : Same as `writeall(3)'
[[cp, section(".text.crt{|.dos}.io.write"), decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
[[requires_function(writeall), no_crt_dos_wrapper, cc(__FORMATPRINTER_CC), impl_include("<bits/types.h>")]]
[[crt_impl_if($extended_include_prefix("<hybrid/typecore.h>", "<bits/crt/format-printer.h>")!defined(__KERNEL__) && (!defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__))]]
[[if($extended_include_prefix("<hybrid/typecore.h>", "<bits/crt/format-printer.h>")defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__), preferred_alias("writeall")]]
ssize_t write_printer(/*fd_t*/ void *fd,
                      [[inp(bufsize)]] char const *__restrict buf,
                      size_t bufsize) {
	return writeall((fd_t)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))(uintptr_t)fd, buf, bufsize);
}

%(auto_header){
#if !defined(__KERNEL__) && (defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__)
/* Define the libc internal header variant as an alias for writeall() when it would otherwise not be defined. */
INTDEF NONNULL((2)) ssize_t NOTHROW_RPC(__FORMATPRINTER_CC libc_write_printer)(void *fd, char const *__restrict buf, size_t bufsize) ASMNAME("libc_writeall");
#endif /* !__KERNEL__ && (__LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_INT__ == __SIZEOF_POINTER__) */
}

%{
#define WRITE_PRINTER_ARG(fd) ((void *)(__UINTPTR_TYPE__)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))(fd))
}

%#endif /* __USE_KOS */
%

[[doc_alias("lseek"), ignore, nocrt, alias("lseek", "_lseek", "__lseek", "__libc_lseek")]]
[[decl_include("<bits/types.h>", "<features.h>")]]
$off32_t lseek32($fd_t fd, $off32_t offset, __STDC_INT_AS_UINT_T whence);

@@>> lseek(2), lseek64(2)
@@Change the position of the file read/write pointer within a file referred to by `fd'
[[guard, decl_include("<features.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("lseek", "_lseek", "__lseek", "__libc_lseek")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("lseek64", "llseek", "__llseek", "_lseeki64")]]
[[userimpl, requires($has_function(lseek32) || $has_function(lseek64))]]
[[section(".text.crt{|.dos}.io.seek"), dos_only_export_as("_lseek"), export_as("__lseek", "__libc_lseek")]]
$off_t lseek($fd_t fd, $off_t offset, __STDC_INT_AS_UINT_T whence) {
@@pp_if $has_function(lseek32)@@
	return lseek32(fd, ($off32_t)offset, whence);
@@pp_else@@
	return lseek64(fd, ($off64_t)offset, whence);
@@pp_endif@@
}

@@>> isatty(2)
@@Check if the given file handle `fd' refers to a TTY
@@@return: 1: Is a tty
@@@return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY')
[[guard, wunused, decl_include("<bits/types.h>")]]
[[dos_only_export_alias("_isatty"), export_alias("__isatty")]]
[[requires_include("<asm/os/tty.h>")]] /* __TCGETA */
[[requires($has_function(tcgetattr) || ($has_function(ioctl) && defined(__TCGETA)))]]
[[section(".text.crt{|.dos}.io.tty")]]
[[impl_include("<bits/os/termios.h>")]]
int isatty($fd_t fd) {
	struct termios ios;
@@pp_if $has_function(ioctl) && defined(__TCGETA)@@
	return ioctl(fd, __TCGETA, &ios) < 0 ? 0 : 1;
@@pp_else@@
	return tcgetattr(fd, &ios) != 0 ? 0 : 1;
@@pp_endif@@
}

@@>> dup2(2)
@@@return: newfd: Returns the new handle upon success.
@@Duplicate a file referred to by `oldfd' into `newfd'
[[guard, decl_include("<bits/types.h>")]]
[[crt_dos_variant, section(".text.crt{|.dos}.io.access")]]
[[dos_only_export_alias("_dup2"), export_alias("__dup2", "__libc_dup2")]]
$fd_t dup2($fd_t oldfd, $fd_t newfd);

@@>> dup(2)
@@@return: * : Returns the new handle upon success.
@@Duplicate a file referred to by `fd' and return its duplicated handle number
[[guard, wunused, decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.io.access")]]
[[dos_only_export_alias("_dup"), export_alias("__dup", "__libc_dup")]]
$fd_t dup($fd_t fd);

@@>> close(2)
@@Close a given file descriptor/handle `fd'
[[guard, decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.io.access")]]
[[dos_only_export_alias("_close"), export_alias("__close", "__libc_close")]]
int close($fd_t fd);

@@>> access(2)
@@@param: type: Set of `X_OK | W_OK | R_OK'
@@Test for access to the specified file `file', testing for `type'
[[cp, guard, wunused, crt_dos_variant, decl_include("<features.h>")]]
[[dos_only_export_alias("_access"), section(".text.crt{|.dos}.fs.property")]]
[[export_alias("__access", "__libc_access"), userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(faccessat))]]
int access([[nonnull]] char const *file, __STDC_INT_AS_UINT_T type) {
	return faccessat(__AT_FDCWD, file, type, 0);
}

@@>> chdir(2)
@@Change the current working directory to `path'
[[cp, guard, dos_export_alias("_chdir"), export_alias("__chdir", "__libc_chdir")]]
[[crt_dos_variant, section(".text.crt{|.dos}.fs.basic_property")]]
int chdir([[nonnull]] char const *path);

@@>> getcwd(2)
@@Return the path of the current working directory, relative to the filesystem root set by `chdir(2)'
[[cp, guard, dos_export_alias("_getcwd")]]
[[section(".text.crt{|.dos}.fs.basic_property")]]
[[crt_dos_variant, decl_include("<hybrid/typecore.h>")]]
char *getcwd([[outp_opt(bufsize)]] char *buf, size_t bufsize);

%[default:section(".text.crt{|.dos}.fs.modify")]

@@>> unlink(2)
@@Remove a file, symbolic link, device or FIFO referred to by `file'
[[cp, guard, dos_export_alias("_unlink"), export_alias("__unlink", "__libc_unlink")]]
[[crt_dos_variant, userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(unlinkat))]]
int unlink([[nonnull]] char const *file) {
	return unlinkat(__AT_FDCWD, file, 0);
}

@@>> rmdir(2)
@@Remove a directory referred to by `path'
[[cp, guard, dos_export_alias("_rmdir"), export_alias("__rmdir", "__libc_rmdir")]]
[[crt_dos_variant, userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && $has_function(unlinkat))]]
int rmdir([[nonnull]] char const *path) {
	return unlinkat(__AT_FDCWD, path, __AT_REMOVEDIR);
}

%[default:section(".text.crt{|.dos}.fs.property")];

%#ifdef __USE_GNU
@@>> euidaccess(2)
@@@param: type: Set of `X_OK | W_OK | R_OK'
@@Test for access to the specified file `file', testing for `type', using the effective filesystem ids
[[crt_dos_variant, decl_include("<features.h>")]]
[[cp, wunused, export_alias("eaccess")]]
[[if(defined(__CRT_DOS)), alias("_access")]]
[[userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && defined(__AT_EACCESS) && $has_function(faccessat))]]
int euidaccess([[nonnull]] char const *file, __STDC_INT_AS_UINT_T type) {
	return faccessat(__AT_FDCWD, file, type, __AT_EACCESS);
}

@@>> eaccess(2)
@@@param: type: Set of `X_OK | W_OK | R_OK'
@@Test for access to the specified file `file', testing for `type', using the effective filesystem ids
[[guard]]
eaccess(*) = euidaccess;

%#endif /* __USE_GNU */

%
%#ifdef __USE_ATFILE
@@>> faccessat(2)
@@@param: type: Set of `X_OK | W_OK | R_OK'
@@Test for access to the specified file `dfd:file', testing for `type'
[[crt_dos_variant, cp, decl_include("<features.h>", "<bits/types.h>")]]
int faccessat($fd_t dfd, [[nonnull]] char const *file,
              __STDC_INT_AS_UINT_T type, $atflag_t flags);

%[default:section(".text.crt{|.dos}.fs.modify")];

@@>> fchownat(2)
@@Change the ownership of a given `dfd:file' to `group:owner'
[[crt_dos_variant, cp, decl_include("<bits/types.h>")]]
int fchownat($fd_t dfd, [[nonnull]] char const *file,
             $uid_t owner, $gid_t group, $atflag_t flags);

@@>> linkat(2)
@@Create a hard link from `fromfd:from', leading to `tofd:to'
[[crt_dos_variant, cp, decl_include("<bits/types.h>")]]
int linkat($fd_t fromfd, [[nonnull]] char const *from,
           $fd_t tofd, [[nonnull]] char const *to, $atflag_t flags);

@@>> symlinkat(3)
@@Create  a  new  symbolic  link  loaded  with  `link_text'  as link
@@text, at the filesystem location referred to by `tofd:target_path'
[[crt_dos_variant, cp, decl_include("<bits/types.h>")]]
[[userimpl, requires_function(fsymlinkat)]]
int symlinkat([[nonnull]] char const *link_text, $fd_t tofd,
              [[nonnull]] char const *target_path) {
	return fsymlinkat(link_text, tofd, target_path, 0);
}

%[default:section(".text.crt{|.dos}.fs.property")];

@@>> readlinkat(2)
@@Read the text of a symbolic link under `dfd:path' into the provided buffer.
@@WARNING: This  function is badly designed and will neither append a trailing
@@         NUL-character to the buffer, nor will it return the required buffer
@@         size. Instead, it will return the written size, and the caller must
@@         keep on over allocating until the function indicates that it didn't
@@         make use of the buffer in its entirety.
@@When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'.
[[crt_dos_variant, cp, decl_include("<bits/types.h>")]]
[[userimpl, requires_function(freadlinkat)]]
ssize_t readlinkat($fd_t dfd, [[nonnull]] char const *path,
                   [[outp(buflen)]] char *buf, size_t buflen) {
	return freadlinkat(dfd, path, buf, buflen, 0);
}

%#ifdef __USE_KOS
@@>> fsymlinkat(3)
@@Create  a  new  symbolic  link  loaded  with  `link_text'  as link
@@text, at the filesystem location referred to by `tofd:target_path'
@@@param flags: Set of `0 | AT_DOSPATH'
[[crt_dos_variant, cp, decl_include("<bits/types.h>")]]
int fsymlinkat([[nonnull]] char const *link_text, $fd_t tofd,
               [[nonnull]] char const *target_path, $atflag_t flags);

@@>> freadlinkat(2)
@@Read the text of a symbolic link under `dfd:path' into the provided buffer.
@@@param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE'
[[crt_dos_variant, cp, decl_include("<bits/types.h>")]]
ssize_t freadlinkat($fd_t dfd, [[nonnull]] char const *path,
                    [[outp(buflen)]] char *buf, size_t buflen,
                    $atflag_t flags);
%#endif /* __USE_KOS */

%[default:section(".text.crt{|.dos}.fs.modify")];

@@>> unlinkat(2)
@@Remove a file, symbolic link, device or FIFO referred to by `dfd:name'
[[crt_dos_variant, cp, decl_include("<bits/types.h>")]]
int unlinkat($fd_t dfd, [[nonnull]] char const *name, $atflag_t flags);
%#endif /* __USE_ATFILE */

%
%#ifdef __USE_LARGEFILE64
[[decl_include("<bits/types.h>")]]
[[preferred_off64_variant_of(lseek), doc_alias("lseek")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), preferred_alias("_lseek", "__lseek", "__libc_lseek")]]
[[dos_only_export_alias("_lseeki64"), export_alias("llseek", "__llseek")]]
[[userimpl, requires_function(lseek32)]]
[[section(".text.crt{|.dos}.io.large.seek")]]
$off64_t lseek64($fd_t fd, $off64_t offset, __STDC_INT_AS_UINT_T whence) {
	return lseek32(fd, (__off32_t)offset, whence);
}
%#endif /* __USE_LARGEFILE64 */

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
%[define(DEFINE_PIO_OFFSET =
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(@pos@)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(@off@)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
)]

%[insert:prefix(DEFINE_PIO_OFFSET)]

@@>> pread(2), pread64(2)
@@Read data from a file at a specific `offset', rather than the current R/W position
@@@return: <= bufsize: The actual amount of read bytes
[[cp, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import, export_as("__libc_pread")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pread", "__libc_pread")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pread64", "__pread64")]]
[[userimpl, requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(pread64) ||
           ($has_function(lseek, read) && defined(__SEEK_SET) && defined(__SEEK_CUR)))]]
[[section(".text.crt{|.dos}.io.read")]]
ssize_t pread($fd_t fd, [[outp(bufsize)]] void *buf,
              size_t bufsize, __PIO_OFFSET offset) {
@@pp_if $has_function(pread64)@@
	return pread64(fd, buf, bufsize, (__PIO_OFFSET64)offset);
@@pp_else@@
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off_t oldpos;
	ssize_t result;
	oldpos = lseek(fd, 0, __SEEK_CUR);
	if __unlikely(oldpos < 0)
		return -1;
	if __unlikely(lseek(fd, (__FS_TYPE(@off@))offset, __SEEK_SET) < 0)
		return -1;
	result = read(fd, buf, bufsize);
	lseek(fd, oldpos, __SEEK_SET);
	return result;
@@pp_endif@@
}

@@>> pwrite(2), pwrite64(2)
@@Write data to a file at a specific `offset', rather than the current R/W position
@@@return: <= bufsize: The actual amount of written bytes
[[cp, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import, export_as("__libc_pwrite")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pwrite", "__libc_pwrite")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pwrite64", "__pwrite64")]]
[[userimpl, requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(pwrite64) ||
           ($has_function(lseek, write) && defined(__SEEK_SET) && defined(__SEEK_CUR)))]]
[[section(".text.crt{|.dos}.io.write")]]
ssize_t pwrite($fd_t fd, [[inp(bufsize)]] void const *buf,
               size_t bufsize, __PIO_OFFSET offset) {
@@pp_if $has_function(pwrite64)@@
	return pwrite64(fd, buf, bufsize, (__PIO_OFFSET64)offset);
@@pp_else@@
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off_t oldpos;
	ssize_t result;
	oldpos = lseek(fd, 0, __SEEK_CUR);
	if __unlikely(oldpos < 0)
		return -1;
	if __unlikely(lseek(fd, (off_t)offset, __SEEK_SET) < 0)
		return -1;
	result = write(fd, buf, bufsize);
	lseek(fd, oldpos, __SEEK_SET);
	return result;
@@pp_endif@@
}


%
%#ifdef __USE_KOS
@@>> preadall(3), preadall64(3)
@@Same as `readall(3)', but using `pread(2)' instead of `read()'
[[cp, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("preadall")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("preadall64")]]
[[impl_include("<libc/errno.h>")]]
[[userimpl, requires_function(preadall64)]]
[[section(".text.crt{|.dos}.io.read")]]
ssize_t preadall($fd_t fd, [[outp(bufsize)]] void *buf,
                 size_t bufsize, __PIO_OFFSET offset) {
	return preadall64(fd, buf, bufsize, (__PIO_OFFSET64)offset);
}

@@>> pwriteall(3), pwriteall64(3)
@@Same as `writeall(3)', but using `pwrite(2)' instead of `write()'
[[cp, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pwriteall")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pwriteall64")]]
[[impl_include("<libc/errno.h>")]]
[[userimpl, requires_function(pwriteall64)]]
[[section(".text.crt{|.dos}.io.write")]]
ssize_t pwriteall($fd_t fd, [[inp(bufsize)]] void const *buf,
                  size_t bufsize, __PIO_OFFSET offset) {
	return pwriteall64(fd, buf, bufsize, (__PIO_OFFSET64)offset);
}
%#endif /* __USE_KOS */



%
%#ifdef __USE_LARGEFILE64

[[cp, ignore, nocrt, alias("pread"), doc_alias("pread")]]
[[decl_include("<bits/types.h>")]]
ssize_t crt_pread32($fd_t fd, [[outp(bufsize)]] void *buf,
                    size_t bufsize, $pos32_t offset);

[[cp, ignore, nocrt, alias("pwrite"), doc_alias("pwrite")]]
[[decl_include("<bits/types.h>")]]
ssize_t crt_pwrite32($fd_t fd, [[inp(bufsize)]] void const *buf,
                     size_t bufsize, $pos32_t offset);

[[cp, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET)]]
[[preferred_off64_variant_of(pread), doc_alias("pread"), export_alias("__pread64")]]
[[userimpl, requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(crt_pread32) ||
           ($has_function(lseek, read) && defined(__SEEK_CUR) && defined(__SEEK_SET)))]]
[[section(".text.crt{|.dos}.io.large.read")]]
ssize_t pread64($fd_t fd, [[outp(bufsize)]] void *buf,
                size_t bufsize, __PIO_OFFSET64 offset) {
@@pp_if $has_function(crt_pread32)@@
	return crt_pread32(fd, buf, bufsize, (pos32_t)offset);
@@pp_elif $has_function(lseek64)@@
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off64_t oldpos;
	ssize_t result;
	oldpos = lseek64(fd, 0, __SEEK_CUR);
	if __unlikely(oldpos < 0)
		return -1;
	if __unlikely(lseek64(fd, (off64_t)offset, __SEEK_SET) < 0)
		return -1;
	result = read(fd, buf, bufsize);
	lseek64(fd, oldpos, __SEEK_SET);
	return result;
@@pp_else@@
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off32_t oldpos;
	ssize_t result;
	oldpos = lseek32(fd, 0, __SEEK_CUR);
	if __unlikely(oldpos < 0)
		return -1;
	if __unlikely(lseek32(fd, (off32_t)offset, __SEEK_SET) < 0)
		return -1;
	result = read(fd, buf, bufsize);
	lseek32(fd, oldpos, __SEEK_SET);
	return result;
@@pp_endif@@
}

[[cp, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET)]]
[[preferred_off64_variant_of(pwrite), doc_alias("pwrite"), export_alias("__pwrite64")]]
[[userimpl, requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(crt_pwrite32) ||
           ($has_function(lseek, write) && defined(__SEEK_CUR) && defined(__SEEK_SET)))]]
[[section(".text.crt{|.dos}.io.large.write")]]
ssize_t pwrite64($fd_t fd, [[inp(bufsize)]] void const *buf,
                 size_t bufsize, __PIO_OFFSET64 offset) {
@@pp_if $has_function(crt_pwrite32)@@
	return crt_pwrite32(fd, buf, bufsize, (pos32_t)offset);
@@pp_elif $has_function(lseek64)@@
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off64_t oldpos;
	ssize_t result;
	oldpos = lseek64(fd, 0, SEEK_CUR);
	if __unlikely(oldpos < 0)
		return -1;
	if __unlikely(lseek64(fd, (off64_t)offset, SEEK_SET) < 0)
		return -1;
	result = write(fd, buf, bufsize);
	lseek64(fd, oldpos, SEEK_SET);
	return result;
@@pp_else@@
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off32_t oldpos;
	ssize_t result;
	oldpos = lseek32(fd, 0, SEEK_CUR);
	if __unlikely(oldpos < 0)
		return -1;
	if __unlikely(lseek32(fd, (off32_t)offset, SEEK_SET) < 0)
		return -1;
	result = write(fd, buf, bufsize);
	lseek32(fd, oldpos, SEEK_SET);
	return result;
@@pp_endif@@
}

%
%#ifdef __USE_KOS
[[cp, preferred_off64_variant_of(preadall), doc_alias("preadall")]]
[[userimpl, requires_function(pread64), decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.io.large.read")]]
ssize_t preadall64($fd_t fd, [[inp(bufsize)]] void *buf,
                   size_t bufsize, __PIO_OFFSET64 offset) {
	ssize_t result, temp;
	result = pread64(fd, buf, bufsize, offset);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = pread64(fd,
			               (byte_t *)buf + (size_t)result,
			               bufsize - (size_t)result,
			               offset + (size_t)result);
			if (temp <= 0) {
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}

[[cp, preferred_off64_variant_of(pwriteall), doc_alias("pwriteall")]]
[[userimpl, requires_function(pwrite64), decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.io.large.write")]]
ssize_t pwriteall64($fd_t fd, [[inp(bufsize)]] void const *buf,
                    size_t bufsize, __PIO_OFFSET64 offset) {
	ssize_t result, temp;
	result = pwrite64(fd, buf, bufsize, offset);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = pwrite64(fd,
			                (byte_t const *)buf + (size_t)result,
			                bufsize - (size_t)result,
			                offset + (size_t)result);
			if (temp <= 0) {
				result = temp;
				break;
			}
			result += temp;
			if ((size_t)result >= bufsize)
				break;
		}
	}
	return result;
}
%#endif /* __USE_KOS */

%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

%
%#if defined(__USE_GNU) || defined(__USE_NETBSD)
[[userimpl, requires_function(dup2)]]
[[crt_dos_variant, decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.io.access")]]
$fd_t dup3($fd_t oldfd, $fd_t newfd, $oflag_t flags) {
	/* TODO: Document which `flags' actually do anything */
	/* TODO: Emulate using dup2()+fcntl() */
	(void)flags;
	return newfd != oldfd ? dup2(oldfd, newfd) : -1;
}

@@>> pipe2(2)
@@Construct a [reader,writer]-pair of pipes
@@@param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
@@@param: flags:   Set of `O_CLOEXEC | O_CLOFORK | O_NONBLOCK | O_DIRECT'
@@@return: 0:  Success
@@@return: -1: Error (s.a. `errno')
[[userimpl, requires_function(pipe)]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.io.access")]]
int pipe2([[nonnull]] $fd_t pipedes[2], $oflag_t flags) {
	/* TODO: Document which `flags' actually do anything */
	/* TODO: Emulate using pipe()+fcntl() */
	(void)flags;
	return pipe(pipedes);
}
%#endif /* __USE_GNU || __USE_NETBSD */


%
%#ifdef __USE_GNU

%{
#ifndef environ
#ifdef __CRT_HAVE_environ
__CSDECLARE(,char **,environ)
#define environ environ
#elif defined(_environ)
#define environ _environ
#elif defined(__environ)
#define environ __environ
#elif defined(__LOCAL_environ)
#define environ __LOCAL_environ
#elif defined(__CRT_HAVE__environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,_environ)
#define _environ _environ
#define environ  _environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,environ,_environ)
#define environ environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___environ)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,char **,__environ)
#define __environ _environ
#define environ   __environ
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,char **,environ,__environ)
#define environ environ
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(____p__environ_defined)
#define environ (*__p__environ())
#elif defined(__CRT_HAVE___p__environ)
#define ____p__environ_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char ***,__NOTHROW,__p__environ,(void),())
#define environ (*__p__environ())
#elif defined(__CRT_HAVE__get_environ)
#ifndef ___get_environ_defined
#define ___get_environ_defined
__CDECLARE(,int,__NOTHROW,_get_environ,(char ***__p_environ),())
#endif /* !___get_environ_defined */
#ifndef _____get_environ_wrapper_defined
#define _____get_environ_wrapper_defined
__FORCELOCAL __ATTR_WUNUSED __ATTR_CONST char **
__NOTHROW(__LIBCCALL ___get_environ_wrapper)(void) {
	char const **__result;
	if __unlikely(_get_environ(&__result) != 0)
		__result = __NULLPTR;
	return __result;
}
#endif /* !_____get_environ_wrapper_defined */
#define environ ___get_environ_wrapper()
#endif /* !... */
#endif /* !environ */
}


@@>> get_current_dir_name(3)
@@Return an malloc(3)'d string  representing the current working  directory
@@This is usually the same  as `getcwd(NULL, 0)', however standards  caused
@@this function to be badly designed, as iff `$PWD' is defined and correct,
@@it is strdup(3)'d  and returned (correctness  is determined by  comparing
@@`stat($PWD)' against `stat(".")').
@@Due to the mandatory dependency on `getenv(3)', this function can't be
@@made thread-safe, so try not to use this one.
[[crt_dos_variant, cp, wunused, ATTR_MALLOC]]
[[requires_function(getcwd), dependency(stat)]]
[[impl_include("<bits/os/stat.h>")]]
[[section(".text.crt{|.dos}.fs.basic_property")]]
char *get_current_dir_name() {
@@pp_if $has_function(getenv) && $has_function(stat) && $has_function(strdup)@@
	/* Specs require us to return a duplicate of $PWD iff it's correct
	 *   ***Author's comment: DUMB!***
	 */
	char *pwd = getenv("PWD");
	if (pwd && *pwd) {
		struct @stat@ st_pwd, st_cwd;
		if (stat(pwd, &st_pwd) == 0 &&
		    stat(".", &st_cwd) == 0) {
			if (st_pwd.@st_dev@ == st_cwd.@st_dev@ &&
			    st_pwd.@st_ino@ == st_cwd.@st_ino@)
				return strdup(pwd);
		}
	}
@@pp_endif@@
	return getcwd(NULL, 0);
}

[[cp, decl_include("<bits/types.h>")]]
[[userimpl, section(".text.crt{|.dos}.fs.modify")]]
int syncfs($fd_t fd) {
	(void)fd;
	/* NO-OP */
	return 0;
}

%[default:section(".text.crt{|.dos}.sched.user")];

@@>> group_member(3)
@@Check if `gid' is an element of `getgroups(2)'
@@@return:  1: Yes, it's a member
@@@return:  0: No, it's not a member
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
[[requires_include("<hybrid/__alloca.h>", "<libc/errno.h>")]]
[[requires($has_function(getgroups) && defined(__hybrid_alloca) &&
           defined(__libc_geterrno) && defined(__EINVAL))]]
[[impl_include("<hybrid/__alloca.h>", "<asm/os/limits.h>", "<libc/errno.h>")]]
[[impl_prefix(
@@push_namespace(local)@@
__LOCAL_LIBC(__group_member_impl) __ATTR_NOINLINE int
(__LIBCCALL __group_member_impl)($gid_t gid, unsigned int bufsize) {
	unsigned int i;
	gid_t *groups = (gid_t *)__hybrid_alloca(bufsize * sizeof(*groups));
	int n         = getgroups((int)bufsize, groups);
	if unlikely(n < 0)
		return n;
	for (i = 0; i < (unsigned int)n; ++i) {
		if (groups[i] == gid)
			return 1;
	}
	return 0;
}
@@pop_namespace@@
)]]
int group_member($gid_t gid) {
	int result;
@@pp_if !defined(__NGROUPS_MAX) || __NGROUPS_MAX <= 0 || __NGROUPS_MAX >= 32@@
	unsigned int size = 32;
@@pp_else@@
	unsigned int size = __NGROUPS_MAX;
@@pp_endif@@
	for (;;) {
		result = (__NAMESPACE_LOCAL_SYM __group_member_impl)(gid, size);
		if (result >= 0)
			break;
		if (__libc_geterrno() != __EINVAL)
			break;
		/* Try again with a larger buffer. */
		size *= 2;
	}
	return result;
}

@@>> getresuid(2)
@@Get the real, effective, and saved UID of the calling thread.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
int getresuid($uid_t *ruid, $uid_t *euid, $uid_t *suid);

@@>> getresgid(2)
@@Get the real, effective, and saved GID of the calling thread.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
int getresgid($gid_t *rgid, $gid_t *egid, $gid_t *sgid);

@@>> setresuid(2)
@@@return: 0 : Success
@@Set the real, effective, and saved UID of the calling thread.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
int setresuid($uid_t ruid, $uid_t euid, $uid_t suid);

@@>> setresgid(2)
@@Set the real, effective, and saved GID of the calling thread.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
int setresgid($gid_t rgid, $gid_t egid, $gid_t sgid);
%#endif /* __USE_GNU */

%#if (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)) || defined(__USE_MISC)

@@Hidden function exported by DOS that allows for millisecond precision
[[cp, ignore, nocrt, alias("__crtSleep", "delay")]]
void __crtSleep($uint32_t msecs);


@@>> usleep(3)
@@Sleep for `useconds' microseconds (1/1.000.000 seconds)
[[cp, decl_include("<bits/types.h>")]]
[[requires($has_function(nanosleep) || $has_function(__crtSleep))]]
[[impl_include("<bits/os/timespec.h>", "<bits/types.h>")]]
[[section(".text.crt{|.dos}.system.utility")]]
int usleep($useconds_t useconds) {
@@pp_if $has_function(nanosleep)@@
	struct timespec ts;
	ts.@tv_sec@  = (time_t)(useconds / USEC_PER_SEC);
	ts.@tv_nsec@ = (syscall_ulong_t)(useconds % USEC_PER_SEC) * NSEC_PER_USEC;
	return nanosleep(&ts, NULL);
@@pp_else@@
	__crtSleep(useconds / 1000l); /*USEC_PER_MSEC*/
	return 0;
@@pp_endif@@
}

@@>> getwd(3)
@@Deprecated, alternate variant  of `getcwd()'.  It
@@should be obvious why you shouldn't use this one.
@@And  if it isn't, take a look at the arguments of
@@this function, compared to `getcwd()'
[[crt_dos_variant, cp, deprecated("Use getcwd()")]]
[[requires_function(getcwd)]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.fs.basic_property")]]
char *getwd([[nonnull]] char *buf) {
	return getcwd(buf, (size_t)-1);
}

[[decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/itimer.h>")]]
[[requires(defined(__ITIMER_REAL) && $has_function(setitimer))]]
[[impl_include("<asm/os/itimer.h>", "<bits/os/itimerval.h>")]]
[[section(".text.crt{|.dos}.system.utility")]]
$useconds_t ualarm($useconds_t value, $useconds_t interval) {
	struct itimerval timer, otimer;
	timer.@it_value@.@tv_sec@     = value / 1000000;
	timer.@it_value@.@tv_usec@    = value % 1000000;
	timer.@it_interval@.@tv_sec@  = interval / 1000000;
	timer.@it_interval@.@tv_usec@ = interval % 1000000;
	if unlikely(setitimer((__itimer_which_t)__ITIMER_REAL, &timer, &otimer) < 0)
		goto err;
	return (otimer.@it_value@.@tv_sec@ * 1000000) +
	       (otimer.@it_value@.@tv_usec@);
err:
	return (useconds_t)-1;
}

@@>> vfork(2)
@@Same as `fork(2)', but the child process may be executed within in the same VM
@@as the parent process, with the  parent process remaining suspended until  the
@@child process invokes one of the following system calls:
@@  - `_exit(2)'  Terminate the child process. Be sure to use `_exit' (or `_Exit')
@@                instead of the regular `exit(3)', since the later would  include
@@                the invocation of `atexit(3)' handlers, which would then run  in
@@                the context of a VM that isn't actually about to be destroyed.
@@  - `execve(2)' Create a new VM that is populated with the specified process
@@                image. The parent process will  only be resumed in case  the
@@                new  program image could  be loaded successfully. Otherwise,
@@                the call  to  `execve(2)'  returns normally  in  the  child.
@@                Other functions from the exec()-family behave the same
@@
@@Care  must be taken when using this system call, since you have to make sure that
@@the  child process doesn't clobber any part of its (shared) stack that may be re-
@@used once execution resumes in  the parent process. The  same also goes for  heap
@@functions,  but generally speaking:  you really shouldn't  do anything that isn't
@@reentrant after calling any one of the fork() functions (since anything but would
@@rely on underlying implementations making proper use of pthread_atfork(3),  which
@@is something that KOS intentionally doesn't do,  since I feel like doing so  only
@@adds unnecessary bloat to code that doesn't rely on this)
@@
@@Additionally, this system call may be implemented as an alias for `fork(2)', in
@@which  case the parent process will not  actually get suspended until the child
@@process performs any of the actions above.
[[guard, export_alias("__vfork", "__libc_vfork")]]
[[returns_twice, wunused, decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.sched.access")]]
$pid_t vfork();
%#endif /* (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) || __USE_MISC */

@@>> fchown(2)
@@Change the ownership of a given `fd' to `group:owner'
[[cp, decl_include("<bits/types.h>")]]
[[export_alias("__fchown", "__libc_fchown")]]
[[section(".text.crt{|.dos}.fs.modify")]]
int fchown($fd_t fd, $uid_t owner, $gid_t group);

@@>> chdir(2)
@@Change the current working directory to `path'
[[cp, decl_include("<bits/types.h>")]]
[[export_alias("__fchdir", "__libc_fchdir")]]
[[section(".text.crt{|.dos}.fs.basic_property")]]
int fchdir($fd_t fd);

@@>> getpgid(2)
@@Return  the ID of  the process group  associated with `pid's process.
@@(That is the TID of the leader of the process group of `pid's leader)
@@THREAD[PID]->LEADER->GROUP_LEADER->PID
@@When `pid' is ZERO(0), use `gettid()' for it instead
[[wunused, decl_include("<bits/types.h>")]]
[[export_alias("__getpgid", "__libc_getpgid", "__bsd_getpgrp")]]
[[section(".text.crt{|.dos}.sched.user")]]
$pid_t getpgid($pid_t pid);

@@>> getsid(2)
@@Return the ID of the session which a process `pid' is apart of.
@@return  THREAD[PID]->LEADER->GROUP_LEADER->SESSION_LEADER->PID;
[[wunused, decl_include("<bits/types.h>")]]
[[export_alias("__getsid", "__libc_getsid")]]
[[section(".text.crt{|.dos}.sched.process")]]
$pid_t getsid($pid_t pid);

@@>> lchown(2)
@@Change the ownership of a given `file' to `group:owner',
@@but don't reference it if  that file is a symbolic  link
[[cp, decl_include("<bits/types.h>")]]
[[crt_dos_variant, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && $has_function(fchownat))]]
[[userimpl, section(".text.crt{|.dos}.fs.modify")]]
int lchown([[nonnull]] char const *file, $uid_t owner, $gid_t group) {
	return fchownat(__AT_FDCWD, file, owner, group, __AT_SYMLINK_NOFOLLOW);
}


%
%{
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
}

[[ignore, nocrt, decl_include("<bits/types.h>"), doc_alias("truncate")]]
[[alias("truncate", "__truncate", "__libc_truncate")]]
int crt_truncate32([[nonnull]] char const *file, $pos32_t length);


@@>> truncate(2), truncate64(2)
@@Truncate the given file `file' to a length of `length'
[[crt_dos_variant, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("truncate", "__truncate", "__libc_truncate")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("truncate64")]]
[[export_as("__truncate", "__libc_truncate")]]
[[userimpl, requires($has_function(truncate64) || $has_function(crt_truncate32) ||
                     $has_function(open, ftruncate))]]
[[section(".text.crt{|.dos}.fs.modify")]]
int truncate([[nonnull]] char const *file, __PIO_OFFSET length) {
@@pp_if $has_function(crt_truncate32)@@
	return crt_truncate32(file, (pos32_t)length);
@@pp_elif $has_function(truncate64)@@
	return truncate64(file, (__PIO_OFFSET64)length);
@@pp_else@@
	int result;
	fd_t fd;
	fd = open(file, 1); /* O_WRONLY */
	if __unlikely(fd < 0)
		return -1;
	result = ftruncate(fd, length);
@@pp_if $has_function(close)@@
	close(fd);
@@pp_endif@@
	return result;
@@pp_endif@@
}

%
%#ifdef __USE_LARGEFILE64
[[crt_dos_variant, preferred_off64_variant_of(truncate), doc_alias("truncate"), decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), preferred_alias("__truncate", "__libc_truncate")]]
[[impl_include("<features.h>"), impl_prefix(DEFINE_PIO_OFFSET)]]
[[userimpl, requires($has_function(crt_truncate32) ||
                     $has_function(open64, ftruncate64))]]
[[section(".text.crt{|.dos}.fs.modify")]]
int truncate64([[nonnull]] char const *file, __PIO_OFFSET64 length) {
@@pp_if $has_function(crt_truncate32)@@
	return crt_truncate32(file, (__PIO_OFFSET)length);
@@pp_else@@
	int result;
	$fd_t fd;
	fd = open64(file, 1); /* O_WRONLY */
	if __unlikely(fd < 0)
		return -1;
	result = ftruncate64(fd, length);
@@pp_if $has_function(close)@@
	close(fd);
@@pp_endif@@
	return result;
@@pp_endif@@
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
%
%#ifdef __USE_XOPEN2K8

@@>> fexecve(2)
@@Replace the calling process with the application image referred
@@to by `execfd'  and execute it's  `main()' method, passing  the
@@given `argv', and setting `environ' to `envp'.
[[cp, guard, argument_names(execfd, ___argv, ___envp)]]
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_TARGV)]]
[[requires_include("<asm/os/features.h>")]]
[[requires(defined(__OS_HAVE_PROCFS_SELF_FD) && $has_function(execve))]]
[[impl_include("<hybrid/typecore.h>")]]
[[userimpl, section(".text.crt{|.dos}.fs.exec.exec")]]
int fexecve($fd_t execfd, [[nonnull]] __TARGV, [[nonnull]] __TENVP) {
@@pp_if __SIZEOF_INT__ == 4@@
	char buf[COMPILER_LNEOF("/proc/self/fd/-2147483648")];
@@pp_elif __SIZEOF_INT__ == 8@@
	char buf[COMPILER_LNEOF("/proc/self/fd/-9223372036854775808")];
@@pp_elif __SIZEOF_INT__ == 2@@
	char buf[COMPILER_LNEOF("/proc/self/fd/-32768")];
@@pp_else@@
	char buf[COMPILER_LNEOF("/proc/self/fd/-128")];
@@pp_endif@@
	sprintf(buf, "/proc/self/fd/%d", execfd);
	return execve(buf, ___argv, ___envp);
}

[[cp, hidden, nocrt, argument_names(fd, ___argv, ___envp), alias("fexecve")]]
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_TARGV)]]
int crt_fexecve($fd_t fd, [[nonnull]] __TARGV, [[nonnull]] __TENVP);

%#endif /* __USE_XOPEN2K8 */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN)
[[export_alias("__nice", "__libc_nice")]]
[[userimpl, section(".text.crt{|.dos}.sched.param")]]
int nice(int inc) {
	(void)inc;
	/* It should be sufficient to emulate this is a no-op. */
	return 0;
}
%#endif /* __USE_MISC || __USE_XOPEN */

%
%[insert:guarded_function(_exit = _Exit)]


%
%#ifdef __USE_POSIX2

@@Retrieve a system configuration string specified by `name'
@@@param: name:   One of `_CS_*' from <asm/crt/confname.h>
@@@param: buf:    Target buffer
@@@param: buflen: Available buffer size (including a trailing \0-character)
@@@return: * :    Required buffer size (including a trailing \0-character)
@@@return: 1 :    Empty configuration string.
@@@return: 0 :    [errno=EINVAL] Bad configuration `name'.
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.system.configuration")]]
size_t confstr(__STDC_INT_AS_UINT_T name, char *buf, size_t buflen);

%{
#if !defined(optarg) && defined(__CRT_HAVE_optarg)
__CSDECLARE(,char *,optarg)
#define optarg optarg
#endif /* !optarg && __CRT_HAVE_optarg */
#if !defined(optind) && defined(__CRT_HAVE_optind)
__CSDECLARE(,int,optind)
#define optind optind
#endif /* !optind && __CRT_HAVE_optind */
#if !defined(opterr) && defined(__CRT_HAVE_opterr)
__CSDECLARE(,int,opterr)
#define opterr opterr
#endif /* !opterr && __CRT_HAVE_opterr */
#if !defined(optopt) && defined(__CRT_HAVE_optopt)
__CSDECLARE(,int,optopt)
#define optopt optopt
#endif /* !optopt && __CRT_HAVE_optopt */
}
%


[[guard, wunused, no_crt_impl, crt_name("getopt"), exposed_name("getopt")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_POSIX2) &&
                                            !defined(__USE_POSIX_IMPLICITLY) &&
                                            !defined(__USE_GNU)),
  preferred_alias("__posix_getopt")]]
int unistd_getopt(int argc, char *const argv[], char const *shortopts);

%#endif /* __USE_POSIX2 */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)

@@>> sync(2)
@@Synchronize all disk  operations of  all mounted file  systems and  flush
@@unwritten buffers down to the hardware layer, ensuring that modifications
@@made become visible on the underlying, persistent media
[[cp, export_alias("__sync", "__libc_sync")]]
[[userimpl, section(".text.crt{|.dos}.fs.modify")]]
void sync() {
	/* NO-OP */
}

@@>> setpgrp(3)
@@Move the calling process into its own process group.
@@Equivalent to `setpgid(0, 0)'
[[section(".text.crt{|.dos}.sched.process")]]
int setpgrp();

@@>> setreuid(2)
@@Set the real and effective UID of the calling thread.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
[[export_alias("__setreuid", "__libc_setreuid")]]
[[section(".text.crt{|.dos}.sched.user")]]
int setreuid($uid_t ruid, $uid_t euid);

@@>> setregid(2)
@@Set the real and effective GID of the calling thread.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
[[export_alias("__setregid", "__libc_setregid")]]
[[section(".text.crt{|.dos}.sched.user")]]
int setregid($gid_t rgid, $gid_t egid);

@@>> gethostid(3)
[[wunused]]
[[section(".text.crt{|.dos}.system.configuration")]]
$longptr_t gethostid();

%#if defined(__USE_MISC) || !defined(__USE_XOPEN2K)
@@>> getpagesize(3)
@@Return the size of a PAGE (in bytes)
[[decl_include("<features.h>")]]
[[libc, const, wunused, nothrow, forceinline, export_alias("__getpagesize")]]
[[if($extended_include_prefix("<asm/pagesize.h>")defined(__ARCH_PAGESIZE)),
  preferred_fast_extern_inline("getpagesize", { return __ARCH_PAGESIZE; })]]
[[if($extended_include_prefix("<asm/pagesize.h>")defined(__ARCH_PAGESIZE)),
  preferred_fast_extern_inline("__getpagesize", { return __ARCH_PAGESIZE; })]]
[[requires_include("<asm/pagesize.h>"), requires(defined(__ARCH_PAGESIZE))]]
[[impl_include("<asm/pagesize.h>")]]
[[section(".text.crt{|.dos}.system.configuration")]]
__STDC_INT_AS_SIZE_T getpagesize() {
	return __ARCH_PAGESIZE;
}

%{
#ifdef __ARCH_PAGESIZE
/* If known to be a compile-time  constant, use macros to make  sure
 * that our `getpagesize()' function is _as_ _fast_ as possible, and
 * also allows for _as_ _many_ compiler optimization as possible! */
#define getpagesize() __ARCH_PAGESIZE
#endif /* __ARCH_PAGESIZE */
}

@@>> getdtablesize(3)
[[const, wunused, nothrow, decl_include("<features.h>")]]
[[export_alias("__getdtablesize")]]
[[section(".text.crt{|.dos}.system.configuration")]]
__STDC_INT_AS_SIZE_T getdtablesize() {
@@pp_if defined(__KOS__)@@
	return 0x7fffffff; /* INT_MAX */
@@pp_elif defined(__linux__) || defined(__linux) || defined(@linux@)@@
	return 0x10000;    /* UINT16_MAX + 1 */
@@pp_else@@
	return 256;        /* UINT8_MAX + 1 */
@@pp_endif@@
}

%#endif /* __USE_MISC || !__USE_XOPEN2K */
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#ifdef __USE_XOPEN2K

@@>> seteuid(2)
@@Set the effective user ID of the calling process
@@@return: 0 : Success
@@@return: -1: [errno=EINVAL] : The given `euid' is invalid
@@@return: -1: [errno=EPERM]  : The current user is not privileged
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.sched.user")]]
int seteuid($uid_t euid);

@@>> setegid(2)
@@Set the effective group ID of the calling process
@@@return: 0 : Success
@@@return: -1: [errno=EINVAL] : The given `egid' is invalid
@@@return: -1: [errno=EPERM]  : The current user is not privileged
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.sched.user")]]
int setegid($gid_t egid);

%#endif /* __USE_XOPEN2K */

%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_UNIX98))

@@>> ttyslot(3)
[[wunused]]
[[section(".text.crt{|.dos}.io.tty")]]
int ttyslot();

%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_UNIX98) */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)

@@>> symlink(3)
@@Create  a new  symbolic link  loaded with  `link_text' as link
@@text, at the filesystem location referred to by `target_path'.
@@Same as `symlinkat(link_text, AT_FDCWD, target_path)'
[[cp, export_alias("__symlink", "__libc_symlink")]]
[[crt_dos_variant, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(symlinkat))]]
[[userimpl, section(".text.crt{|.dos}.fs.modify")]]
int symlink([[nonnull]] char const *link_text,
            [[nonnull]] char const *target_path) {
	/* TODO: Header-implementation for `symlink()' on DOS (using the windows API) */
	return symlinkat(link_text, __AT_FDCWD, target_path);
}

@@>> readlink(3)
@@Read the text of a symbolic link under `path' into the provided buffer.
@@Same as `readlinkat(AT_FDCWD, path, buf, buflen)'
@@WARNING: This  function is badly designed and will neither append a trailing
@@         NUL-character to the buffer, nor will it return the required buffer
@@         size. Instead, it will return the written size, and the caller must
@@         keep on over allocating until the function indicates that it didn't
@@         make use of the buffer in its entirety.
@@When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'
[[cp, crt_dos_variant, decl_include("<hybrid/typecore.h>")]]
[[requires_include("<asm/os/fcntl.h>"), export_alias("__readlink", "__libc_readlink")]]
[[requires(defined(__AT_FDCWD) && $has_function(readlinkat))]]
[[userimpl, section(".text.crt{|.dos}.fs.property")]]
ssize_t readlink([[nonnull]] char const *path,
                 [[outp(buflen)]] char *buf,
                 size_t buflen) {
	return readlinkat(__AT_FDCWD, path, buf, buflen);
}

%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%
%#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
@@>> getlogin_r(3)
@@Reentrant version of `getlogin()'. May truncate the name if it's longer than `name_len'
@@s.a. `getlogin()' and `cuserid()'
[[cp, decl_include("<hybrid/typecore.h>")]]
[[requires($has_function(getenv) || $has_function(getpwuid_r, geteuid))]]
[[impl_include("<bits/crt/db/passwd.h>")]] /* struct passwd */
[[section(".text.crt{|.dos}.io.tty")]]
int getlogin_r([[outp(name_len)]] char *name, size_t name_len) {
@@pp_if $has_function(getpwuid_r) && $has_function(geteuid)@@
	char buf[1024]; /* NSS_BUFLEN_PASSWD */
	struct passwd pwent, *pwptr;
@@pp_endif@@
	char *pwname;
@@pp_if $has_function(getenv)@@
	pwname = getenv("LOGNAME");
@@pp_if $has_function(getpwuid_r) && $has_function(geteuid)@@
	if (!pwname)
@@pp_endif@@
@@pp_endif@@
@@pp_if $has_function(getpwuid_r) && $has_function(geteuid)@@
	{
		if (getpwuid_r(geteuid(), &pwent, buf,
		               sizeof(buf), &pwptr) ||
		    pwptr == NULL)
			return -1;
		pwname = pwptr->@pw_name@;
		if (!pwname)
			return -1;
	}
@@pp_endif@@
	if (name_len) {
		name[name_len - 1] = '\0';
		strncpy(name, pwname, name_len - 1);
	}
	return 0;
}
%#endif /* __USE_REENTRANT || __USE_POSIX199506 */

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
@@>> gethostname(3)
@@Return the name assigned to the hosting machine, as set by `sethostname(2)'
[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__gethostname")]] /* Yes: no `__libc_gethostname' alias for this one... */
[[section(".text.crt{|.dos}.system.configuration")]]
int gethostname([[outp(buflen)]] char *name, size_t buflen);
%#endif /* __USE_UNIX98 || __USE_XOPEN2K */

%
%#ifdef __USE_MISC
@@>> setlogin(3)
[[section(".text.crt{|.dos}.io.tty")]]
int setlogin([[nonnull]] char const *name);

@@>> sethostname(2)
@@Set the name of the hosting machine
[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__sethostname", "__libc_sethostname")]]
[[section(".text.crt{|.dos}.system.configuration")]]
int sethostname([[inp(len)]] char const *name, size_t len);

@@>> sethostid(3)
[[section(".text.crt{|.dos}.system.configuration")]]
int sethostid($longptr_t id);

@@>> getdomainname(3)
@@Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)'
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.system.configuration")]]
int getdomainname([[outp(buflen)]] char *name, size_t buflen);

@@>> setdomainname(2)
@@Set the name of the hosting machine's domain
[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__setdomainname", "__libc_setdomainname")]]
[[section(".text.crt{|.dos}.system.configuration")]]
int setdomainname([[inp(len)]] char const *name, size_t len);

@@>> vhangup(3)
[[export_alias("__vhangup", "__libc_vhangup")]]
[[section(".text.crt{|.dos}.io.tty")]]
int vhangup();

@@>> profil(3)
[[decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.system.utility")]]
int profil([[nonnull]] $uint16_t *sample_buffer,
           size_t size, size_t offset,
           unsigned int scale);

@@>> getusershell(3)
[[cp, wunused]]
[[section(".text.crt{|.dos}.database.shell")]]
char *getusershell();

@@>> endusershell(3)
[[section(".text.crt{|.dos}.database.shell")]]
void endusershell();

@@>> setusershell(3)
[[cp]]
[[section(".text.crt{|.dos}.database.shell")]]
void setusershell();

@@>> daemon(3)
[[cp, guard, decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.system.utility")]]
int daemon(__STDC_INT_AS_UINT_T nochdir,
           __STDC_INT_AS_UINT_T noclose);

@@>> revoke(3)
[[cp]]
[[section(".text.crt{|.dos}.fs.modify")]]
int revoke([[nonnull]] char const *file);

%[insert:extern(acct)]

@@>> syscall(2), syscall64(2)
[[cp, libc, decl_include("<bits/types.h>")]]
[[vartypes($syscall_ulong_t, $syscall_ulong_t, $syscall_ulong_t,
           $syscall_ulong_t, $syscall_ulong_t, $syscall_ulong_t)]]
[[section(".text.crt{|.dos}.system.utility")]]
$longptr_t syscall($longptr_t sysno, ...);

%
%#ifdef __USE_KOS
[[cp, libc, doc_alias("syscall"), decl_include("<bits/types.h>")]]
[[preferred_alias("syscall"), export_alias("__syscall")]]
[[vartypes($syscall_ulong_t, $syscall_ulong_t, $syscall_ulong_t,
           $syscall_ulong_t, $syscall_ulong_t, $syscall_ulong_t)]]
[[section(".text.crt{|.dos}.system.utility")]]
__LONG64_TYPE__ syscall64($syscall_ulong_t sysno, ...);
%#endif /* __USE_KOS */
%

%[insert:extern(getentropy)]
%#endif /* __USE_MISC */

%
%#if (defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
@@>> chroot(2)
@@Change  the root directory of the calling `CLONE_FS' group of threads
@@(usually the process) to a path that was previously address by `path'
[[crt_dos_variant, cp]]
[[export_alias("__chroot", "__libc_chroot")]]
[[section(".text.crt{|.dos}.fs.utility")]]
int chroot([[nonnull]] char const *__restrict path);

@@>> getpass(3), getpassphrase(3)
[[guard, cp, wunused, export_alias("getpassphrase")]]
[[requires_function(getpass_r)]]
[[impl_include("<asm/crt/readpassphrase.h>")]]
[[section(".text.crt{|.dos}.io.tty")]]
char *getpass([[nullable]] char const *__restrict prompt) {
	static char buf[257]; /* `getpassphrase()' requires passwords at least this long! */
//	static char buf[129]; /* 129 == _PASSWORD_LEN + 1 */
	return getpass_r(prompt, buf, sizeof(buf));
}
%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

%
%#if defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)

[[ignore, nocrt, doc_alias("ftruncate"), decl_include("<bits/types.h>")]]
[[alias("ftruncate", "__ftruncate", "__libc_ftruncate", "_chsize", "chsize")]]
int crt_ftruncate32($fd_t fd, $pos32_t length);

@@>> ftruncate(2), ftruncate64(2)
@@Truncate the given file `fd' to a length of `length'
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("ftruncate", "__ftruncate", "__libc_ftruncate", "_chsize", "chsize")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("ftruncate64", "_chsize_s")]]
[[requires($has_function(crt_ftruncate32) || $has_function(ftruncate64))]]
[[dos_only_export_as("_chsize"), export_as("__ftruncate", "__libc_ftruncate", "chsize")]]
[[userimpl, section(".text.crt{|.dos}.io.write")]]
int ftruncate($fd_t fd, __PIO_OFFSET length) {
@@pp_if $has_function(crt_ftruncate32)@@
	return crt_ftruncate32(fd, (pos32_t)length);
@@pp_else@@
	return ftruncate64(fd, (pos64_t)length);
@@pp_endif@@
}

%
%#ifdef __USE_LARGEFILE64
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET)]]
[[preferred_off64_variant_of(ftruncate), doc_alias("ftruncate")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), preferred_alias("__ftruncate", "__libc_ftruncate", "_chsize", "chsize")]]
[[dos_only_export_alias("_chsize_s")]]
[[requires_function(crt_ftruncate32)]]
[[userimpl, section(".text.crt{|.dos}.io.large.write")]]
int ftruncate64($fd_t fd, __PIO_OFFSET64 length) {
	return crt_ftruncate32(fd, (pos32_t)length);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%
%#if (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K)) || defined(__USE_MISC)
@@>> brk(2), sbrk(2)
@@Change the  program  break,  allowing  for a  rudimentary  implementation  of  a  heap.
@@It is recommended to use the much more advanced functions found in <sys/mman.h> instead
[[export_alias("__brk")]]
[[section(".text.crt{|.dos}.heap.utility")]]
int brk(void *addr);

[[export_alias("__sbrk"), doc_alias("brk")]]
[[section(".text.crt{|.dos}.heap.utility")]]
void *sbrk(intptr_t delta);
%#endif /* (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K) || __USE_MISC */

%
%#if defined(__USE_POSIX199309) || defined(__USE_UNIX98)
@@>> fdatasync(2)
@@Synchronize only the data of a file (not its descriptor which contains
@@timestamps,  and its size),  meaning that changes  are written to disk
[[cp, decl_include("<bits/types.h>")]]
[[export_alias("__fdatasync", "__libc_fdatasync")]]
[[alias("fsync", "__fsync", "_commit")]]
[[userimpl, section(".text.crt{|.dos}.io.sync")]]
int fdatasync($fd_t fd) {
	(void)fd;
	/* NO-OP */
	return 0;
}
%#endif /* __USE_POSIX199309 || __USE_UNIX98 */

%
%#ifdef __USE_XOPEN
%[insert:extern(crypt)]
%[insert:extern(encrypt)]

@@>> swab(3)
@@Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
@@exchanging the order of even and odd bytes ("123456" --> "214365")
@@When `n_bytes <= 1', don't do anything and return immediately
[[guard, decl_include("<features.h>")]]
[[dos_only_export_alias("_swab")]]
[[section(".text.crt{|.dos}.string.memory")]]
void swab([[nonnull]] void const *__restrict from,
          [[nonnull]] void *__restrict to,
          __STDC_INT_AS_SSIZE_T n_bytes) {
	n_bytes &= ~1;
	while (n_bytes >= 2) {
		byte_t a, b;
		a = ((byte_t *)from)[--n_bytes];
		b = ((byte_t *)from)[--n_bytes];
		((byte_t *)to)[n_bytes+0] = a;
		((byte_t *)to)[n_bytes+1] = b;
	}
}

%#endif /* __USE_XOPEN */

%
%
%#if defined(_EVERY_SOURCE) || defined(__USE_SOLARIS) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
@@>> ctermid(3)
@@Writes the string "/dev/tty" to `s', or returns a pointer to
@@a writable  data location  that contains  that same  string.
[[guard, nonnull]]
[[section(".text.crt{|.dos}.io.tty")]]
char *ctermid([[nullable]] char *s) {
@@pp_ifdef _WIN32@@
	static char buf[4];
	if (s == NULL)
		s = buf;
	return strcpy(s, "CON");
@@pp_else@@
	static char buf[9];
	if (s == NULL)
		s = buf;
	return strcpy(s, "/dev/tty");
@@pp_endif@@
}

@@>> cuserid(3)
@@Return the name of the current user (`$LOGNAME' or `getpwuid(geteuid())'), storing
@@that  name  in  `s'.  When  `s'  is   NULL,  a  static  buffer  is  used   instead
@@When  given,   `s'   must  be   a   buffer   of  at   least   `L_cuserid'   bytes.
@@If the actual  username is longer  than this,  it may be  truncated, and  programs
@@that wish to support longer usernames  should make use of `getlogin_r()'  instead.
@@s.a. `getlogin()' and `getlogin_r()'
[[guard, requires_function(getlogin_r)]]
[[impl_include("<asm/crt/stdio.h>")]] /* __L_cuserid */
[[section(".text.crt{|.dos}.io.tty")]]
char *cuserid(char *s) {
@@pp_ifdef __L_cuserid@@
	static char cuserid_buffer[__L_cuserid];
	if (!s)
		s = cuserid_buffer;
	return getlogin_r(s, __L_cuserid) ? NULL : s;
@@pp_else@@
	static char cuserid_buffer[9];
	if (!s)
		s = cuserid_buffer;
	return getlogin_r(s, 9) ? NULL : s;
@@pp_endif@@
}
%#endif /* _EVERY_SOURCE || __USE_SOLARIS || (__USE_XOPEN && !__USE_XOPEN2K) */


%
%#ifdef __USE_NETBSD
%{
#ifndef sys_siglist
#ifdef _sys_siglist
#define sys_siglist _sys_siglist
#else /* _sys_siglist */
}
%[insert:extern(__p_sys_siglist)]
%{
#ifdef ____p_sys_siglist_defined
#define sys_siglist  __p_sys_siglist()
#define _sys_siglist __p_sys_siglist()
#endif /* ____p_sys_siglist_defined */
#ifndef _sys_siglist
#ifdef __CRT_HAVE_sys_siglist
#ifdef __NSIG
__CSDECLARE2(,char const *const sys_siglist[__NSIG],sys_siglist)
#else /* __NSIG */
__CSDECLARE2(,char const *const sys_siglist[],sys_siglist)
#endif /* !__NSIG */
#define sys_siglist  sys_siglist
#define _sys_siglist sys_siglist
#elif defined(__CRT_HAVE__sys_siglist)
#ifdef __NSIG
__CSDECLARE2(,char const *const _sys_siglist[__NSIG],_sys_siglist)
#else /* __NSIG */
__CSDECLARE2(,char const *const _sys_siglist[],_sys_siglist)
#endif /* !__NSIG */
#define sys_siglist  _sys_siglist
#define _sys_siglist _sys_siglist
#endif /* sys_siglist... */
#endif /* !_sys_siglist */
#endif /* !_sys_siglist */
#endif /* !sys_siglist */

#ifndef __sa_family_t_defined
#define __sa_family_t_defined
typedef __sa_family_t sa_family_t; /* One of `AF_*' */
#endif /* !__sa_family_t_defined */
}

%[insert:extern(getgrouplist)]
%[insert:extern(initgroups)]
%[insert:extern(mkstemps)]
%[insert:extern(psignal)]
%[insert:extern(rcmd)]
%[insert:extern(rresvport)]
%[insert:extern(setgroups)]
%[insert:extern(ruserok)]
%[insert:extern(strmode)]
%[insert:extern(strsignal)]
%[insert:extern(rcmd_af)]

%{

/* Flags for NetBSD's `getpassfd(3)' function */
#if !defined(GETPASS_NEED_TTY) && defined(__GETPASS_NEED_TTY)
#define GETPASS_NEED_TTY    __GETPASS_NEED_TTY    /* RPP_REQUIRE_TTY: Error out if `!isatty()' */
#endif /* !GETPASS_NEED_TTY && __GETPASS_NEED_TTY */
#if !defined(GETPASS_FAIL_EOF) && defined(__GETPASS_FAIL_EOF)
#define GETPASS_FAIL_EOF    __GETPASS_FAIL_EOF    /* Input EOF is an error */
#endif /* !GETPASS_FAIL_EOF && __GETPASS_FAIL_EOF */
#if !defined(GETPASS_BUF_LIMIT) && defined(__GETPASS_BUF_LIMIT)
#define GETPASS_BUF_LIMIT   __GETPASS_BUF_LIMIT   /* BEEP when typing after buffer limit is reached */
#endif /* !GETPASS_BUF_LIMIT && __GETPASS_BUF_LIMIT */
#if !defined(GETPASS_NO_SIGNAL) && defined(__GETPASS_NO_SIGNAL)
#define GETPASS_NO_SIGNAL   __GETPASS_NO_SIGNAL   /* When a control character (such as ^C) causes password
                                                   * reading  to  be aborted  (with  `errno=EINTR'), don't
                                                   * raise(3) the  signal associated  with that  character
                                                   * before returning from `getpassfd()' */
#endif /* !GETPASS_NO_SIGNAL && __GETPASS_NO_SIGNAL */
#if !defined(GETPASS_NO_BEEP) && defined(__GETPASS_NO_BEEP)
#define GETPASS_NO_BEEP     __GETPASS_NO_BEEP     /* Don't BEEP */
#endif /* !GETPASS_NO_BEEP && __GETPASS_NO_BEEP */
#if !defined(GETPASS_ECHO) && defined(__GETPASS_ECHO)
#define GETPASS_ECHO        __GETPASS_ECHO        /* RPP_ECHO_ON: Don't disable echo (but leave it on). */
#endif /* !GETPASS_ECHO && __GETPASS_ECHO */
#if !defined(GETPASS_ECHO_STAR) && defined(__GETPASS_ECHO_STAR)
#define GETPASS_ECHO_STAR   __GETPASS_ECHO_STAR   /* Print '*' instead for typed characters */
#endif /* !GETPASS_ECHO_STAR && __GETPASS_ECHO_STAR */
#if !defined(GETPASS_7BIT) && defined(__GETPASS_7BIT)
#define GETPASS_7BIT        __GETPASS_7BIT        /* RPP_SEVENBIT: Mask input with `0x7f' */
#endif /* !GETPASS_7BIT && __GETPASS_7BIT */
#if !defined(GETPASS_FORCE_LOWER) && defined(__GETPASS_FORCE_LOWER)
#define GETPASS_FORCE_LOWER __GETPASS_FORCE_LOWER /* RPP_FORCELOWER: Force all input to be lower-case. */
#endif /* !GETPASS_FORCE_LOWER && __GETPASS_FORCE_LOWER */
#if !defined(GETPASS_FORCE_UPPER) && defined(__GETPASS_FORCE_UPPER)
#define GETPASS_FORCE_UPPER __GETPASS_FORCE_UPPER /* RPP_FORCEUPPER: Force all input to be upper-case. */
#endif /* !GETPASS_FORCE_UPPER && __GETPASS_FORCE_UPPER */
#if !defined(GETPASS_ECHO_NL) && defined(__GETPASS_ECHO_NL)
#define GETPASS_ECHO_NL     __GETPASS_ECHO_NL     /* Print a '\n' after the password was read */
#endif /* !GETPASS_ECHO_NL && __GETPASS_ECHO_NL */
}

@@>> getpassfd(3)
@@This function behaves  similar to `readpassphrase(3)',  but is  still
@@quite  distinct from that  function in how this  one behaves, vs. how
@@that other function behaves. In general, this function is a bit  more
@@user-friendly, in  that it  offers more  (but different)  `flags'  to
@@control how the password prompt is generated, with the main advantage
@@of this function  being that it  implements some "advanced"  readline
@@functionality, such as deleting  typed characters without relying  on
@@the  system  TTY canonical  buffer (which  `readpassphrase(3)' needs,
@@since it doesn't include support  for _any_ control characters  other
@@that CR/LF as indicators to stop reading text)
@@Which of the 2 functions should be used is a matter of taste, but
@@personally,   I   prefer  this   one   over  `readpassphrase(3)'.
@@@param: prompt:  [0..1]      Text-prompt to display to the user, or `NULL'
@@@param: buf:     [0..buflen] Buffer that will receive the user's password.
@@                             When set to  `NULL', a dynamically  allocated
@@                             buffer will be used and returned.
@@@param: buflen:              Size of `buf' (in characters) (ignored when `buf == NULL')
@@@param: fds:     [0..1]      When non-NULL,  an [stdin,stdout,stderr]  triple
@@                             of files, used for [read,write,beep] operations.
@@                             When  `NULL', try to use `/dev/tty' instead, and
@@                             if that fails, use  `STDIN_FILENO,STDERR_FILENO,
@@                             STDERR_FILENO' as final fallback.
@@                             When `GETPASS_NEED_TTY' is set, the  function
@@                             will fail with `errno=ENOTTY' if the actually
@@                             used `fds[0]' (iow: stdin) isn't a TTY device
@@                             s.a. `isatty(3)'
@@@param: flags:               Set of `GETPASS_*' flags (from <unistd.h>)
@@@param: timeout_in_seconds:  When non-0, timeout (in  seconds) to wait for  the
@@                             user to type each character of their password.  If
@@                             this timeout expires, fail with  `errno=ETIMEDOUT'
@@                             Negative values result in weak undefined behavior.
@@@return: * :   [buf == NULL] Success (dynamically allocated buffer; must be `free(3)'d)
@@@return: buf:                Success
@@@return: NULL: [ETIMEDOUT]   The given `timeout_in_seconds' has expired.
@@@return: NULL: [EINVAL]      `buf' is non-`NULL', but `buflen' is `0'
@@@return: NULL: [ENOTTY]      `GETPASS_NEED_TTY' was given, but not a tty
@@@return: NULL: [ENOMEM]      Insufficient memory
@@@return: NULL: [ENODATA]     End-of-file while reading, and `GETPASS_FAIL_EOF' was set.
@@@return: NULL: [*]           Error
[[cp, wunused, decl_include("<features.h>", "<bits/types.h>")]]
[[requires_function(read)]]
[[impl_include("<bits/types.h>", "<asm/os/stdio.h>", "<asm/os/oflags.h>")]]
[[impl_include("<libc/errno.h>", "<paths.h>", "<asm/crt/getpassfd.h>")]]
[[impl_include("<asm/os/termios.h>", "<bits/os/termios.h>")]]
[[impl_include("<asm/os/signal.h>", "<bits/os/pollfd.h>")]]
[[impl_include("<asm/os/poll.h>", "<libc/strings.h>")]]
char *getpassfd([[nullable]] char const *prompt,
                [[nullable]] char *buf, size_t buflen,
                [[nullable]] $fd_t fds[3],
                __STDC_INT_AS_UINT_T flags,
                int timeout_in_seconds) {
@@pp_ifndef __STDIN_FILENO@@
#define __STDIN_FILENO 0
@@pp_endif@@
@@pp_ifndef __STDERR_FILENO@@
#define __STDERR_FILENO 2
@@pp_endif@@

@@pp_if $has_function(malloc)@@
	bool heap_buf;
@@pp_endif@@
	char *result;
	fd_t default_fds[3];
	signo_t interrupt_signo;

	/* Initialize locals. */
@@pp_if $has_function(tcgetattr) && $has_function(tcsetattr)@@
	struct termios old_ios, new_ios;
	memset(&old_ios, -1, sizeof(old_ios));
	memset(&new_ios, -1, sizeof(new_ios));
@@pp_endif@@
	result          = NULL;
	interrupt_signo = 0;
	default_fds[0]  = __STDIN_FILENO;

	/* Allocate a dynamic buffer if none was given by the caller. */
@@pp_if $has_function(malloc)@@
	heap_buf = false;
	if (!buf) {
		buflen = 512;
		buf = (char *)malloc(buflen * sizeof(char));
		if unlikely(!buf) {
			buflen = 1;
			buf = (char *)malloc(buflen * sizeof(char));
			if unlikely(!buf)
				goto out;
		}
		heap_buf = true;
	} else
@@pp_endif@@
	if (buflen < 1) {
		/* Invalid buffer length */
@@pp_ifdef EINVAL@@
		(void)libc_seterrno(EINVAL);
@@pp_endif@@
		goto out;
	}

	/* Open input files if not provided by the caller. */
	if (!fds) {
		fds = default_fds;
@@pp_if $has_function(open)@@
@@pp_ifdef __O_CLOEXEC@@
#define __PRIVATE_GETPASSFD_O_CLOEXEC __O_CLOEXEC
@@pp_else@@
#define __PRIVATE_GETPASSFD_O_CLOEXEC 0
@@pp_endif@@
@@pp_ifdef __O_CLOFORK@@
#define __PRIVATE_GETPASSFD_O_CLOFORK __O_CLOFORK
@@pp_else@@
#define __PRIVATE_GETPASSFD_O_CLOFORK 0
@@pp_endif@@
@@pp_ifdef __O_RDWR@@
#define __PRIVATE_GETPASSFD_O_RDWR __O_RDWR
@@pp_else@@
#define __PRIVATE_GETPASSFD_O_RDWR 0
@@pp_endif@@
@@pp_if defined(__O_NONBLOCK) && $has_function(poll)@@
#define __PRIVATE_GETPASSFD_O_NONBLOCK __O_NONBLOCK
@@pp_else@@
#define __PRIVATE_GETPASSFD_O_NONBLOCK 0
@@pp_endif@@
@@pp_ifdef _PATH_TTY@@
#define __PRIVATE_GETPASSFD_PATH_TTY _PATH_TTY
@@pp_elif defined(_WIN32)@@
#define __PRIVATE_GETPASSFD_PATH_TTY "CON"
@@pp_else@@
#define __PRIVATE_GETPASSFD_PATH_TTY "/dev/tty"
@@pp_endif@@
#if __PRIVATE_GETPASSFD_O_NONBLOCK != 0
		default_fds[2] = open(__PRIVATE_GETPASSFD_PATH_TTY,
		                      __PRIVATE_GETPASSFD_O_CLOEXEC |
		                      __PRIVATE_GETPASSFD_O_CLOFORK |
		                      __PRIVATE_GETPASSFD_O_RDWR |
		                      (timeout_in_seconds != 0 ? __PRIVATE_GETPASSFD_O_NONBLOCK : 0));
#else /* __PRIVATE_GETPASSFD_O_NONBLOCK != 0 */
		default_fds[2] = open(__PRIVATE_GETPASSFD_PATH_TTY,
		                      __PRIVATE_GETPASSFD_O_CLOEXEC |
		                      __PRIVATE_GETPASSFD_O_CLOFORK |
		                      __PRIVATE_GETPASSFD_O_RDWR);
#endif /* __PRIVATE_GETPASSFD_O_NONBLOCK == 0 */
		if (default_fds[2] != -1) {
			default_fds[0] = default_fds[2];
			default_fds[1] = default_fds[2];
		} else
@@pp_endif@@
		{
			default_fds[1] = __STDERR_FILENO;
			default_fds[2] = __STDERR_FILENO;
		}
	}

	/* Load terminal settings. */
@@pp_if $has_function(tcgetattr) && $has_function(tcsetattr)@@
	if (tcgetattr(fds[0], &old_ios) == 0) {
		memcpy(&new_ios, &old_ios, sizeof(struct termios));

		/* Configure new settings. */
@@pp_if defined(__ECHO) || defined(__ECHOK) || defined(__ECHOE) || defined(__ECHOKE) || defined(__ECHOCTL) || defined(__ISIG) || defined(__ICANON)@@
		new_ios.@c_lflag@ &= ~(0 |
@@pp_ifdef __ECHO@@
		                       __ECHO |
@@pp_endif@@
@@pp_ifdef __ECHOK@@
		                       __ECHOK |
@@pp_endif@@
@@pp_ifdef __ECHOE@@
		                       __ECHOE |
@@pp_endif@@
@@pp_ifdef __ECHOKE@@
		                       __ECHOKE |
@@pp_endif@@
@@pp_ifdef __ECHOCTL@@
		                       __ECHOCTL |
@@pp_endif@@
@@pp_ifdef __ISIG@@
		                       __ISIG |
@@pp_endif@@
@@pp_ifdef __ICANON@@
		                       __ICANON
@@pp_endif@@
		                       );
@@pp_endif@@

@@pp_ifdef __VMIN@@
		new_ios.@c_cc@[__VMIN] = 1;
@@pp_endif@@
@@pp_ifdef __VTIME@@
		new_ios.@c_cc@[__VTIME] = 0;
@@pp_endif@@

@@pp_if defined(__TCSAFLUSH) && defined(__TCSASOFT)@@
		if (tcsetattr(fds[0], __TCSAFLUSH | __TCSASOFT, &new_ios) != 0)
@@pp_elif defined(__TCSAFLUSH)@@
		if (tcsetattr(fds[0], __TCSAFLUSH, &new_ios) != 0)
@@pp_else@@
		if (tcsetattr(fds[0], 0, &new_ios) != 0)
@@pp_endif@@
		{
			goto out;
		}
	} else {
		if (flags & __GETPASS_NEED_TTY)
			goto out; /* tcgetattr() should have already set errno=ENOTTY */
	}
@@pp_elif $has_function(isatty)@@
	if ((flags & __GETPASS_NEED_TTY) && !isatty(fds[0]))
		goto out; /* isatty() should have already set errno=ENOTTY */
@@pp_endif@@

	/* Print the given prompt */
@@pp_if $has_function(write)@@
	if (prompt && *prompt) {
		if (write(fds[1], prompt, strlen(prompt)) == -1)
			goto out;
	}
@@pp_else@@
	(void)prompt;
@@pp_endif@@

	/* The actual interpreter loop for the password reader: */
	{
		unsigned char ch, *dst, *bufend;
@@pp_if $has_function(tcgetattr) && $has_function(tcsetattr) && defined(__VLNEXT)@@
		bool escape; /* Set to `true' if the next character is escaped. */
		escape = false;
@@pp_endif@@
		dst    = (unsigned char *)buf;
		bufend = (unsigned char *)buf + buflen - 1;
		for (;;) {

@@pp_if $has_function(poll)@@
			if (timeout_in_seconds != 0) {
				int status;
				struct pollfd pfd;
				pfd.@fd@      = fds[0];
@@pp_if defined(__POLLIN) && defined(__POLLRDNORM)@@
				pfd.@events@  = __POLLIN | __POLLRDNORM;
@@pp_elif defined(__POLLIN)@@
				pfd.@events@  = __POLLIN;
@@pp_else@@
				pfd.@events@  = 0;
@@pp_endif@@
				status = poll(&pfd, 1, timeout_in_seconds * 1000);
				if unlikely(status == -1)
					goto out; /* Error... */
				if unlikely(status == 0) {
@@pp_ifdef ETIMEDOUT@@
					(void)libc_seterrno(ETIMEDOUT);
@@pp_else@@
					(void)libc_seterrno(1);
@@pp_endif@@
					goto out; /* Timeout... */
				}
				/* Assume that data can be read now! */
			}
@@pp_else@@
			(void)timeout_in_seconds;
@@pp_endif@@

			/* Actually read the next character. */
			{
				ssize_t status;
				status = read(fds[0], &ch, sizeof(ch));
				if (status < (ssize_t)sizeof(char)) {
					if (status < 0)
						goto out; /* Error */
@@pp_ifdef __VEOF@@
handle_eof:
@@pp_endif@@
					if (flags & __GETPASS_FAIL_EOF) {
						/* Error out on regular, old EOF */
@@pp_ifdef ENODATA@@
						(void)libc_seterrno(ENODATA);
@@pp_endif@@
						goto out;
					}
					break;
				}
			}

@@pp_if $has_function(tcgetattr) && $has_function(tcsetattr) && defined(__VLNEXT)@@
			if (escape) {
				/* Unconditionally add `ch' */
				escape = false;
			} else
@@pp_endif@@
			{
@@pp_if $has_function(tcgetattr) && $has_function(tcsetattr)@@
@@pp_if __VDISABLE == '\0'@@
#define __PRIVATE_GETPASSFD_CTRL(index, defl) \
	(new_ios.@c_cc@[index] != '\0' ? new_ios.@c_cc@[index] : __CTRL(defl))
@@pp_else@@
#define __PRIVATE_GETPASSFD_CTRL(index, defl) \
	((new_ios.@c_cc@[index] != '\0' && new_ios.@c_cc@[index] != __VDISABLE) ? new_ios.@c_cc@[index] : __CTRL(defl))
@@pp_endif@@

				/* Check for control characters that should be ignored. */
@@pp_ifdef __VREPRINT@@
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VREPRINT, 'R'))
					continue;
@@pp_endif@@

@@pp_ifdef __VSTART@@
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VSTART, 'Q'))
					continue;
@@pp_endif@@

@@pp_ifdef __VSTOP@@
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VSTOP, 'S'))
					continue;
@@pp_endif@@

@@pp_ifdef __VSTATUS@@
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VSTATUS, 'T'))
					continue;
@@pp_endif@@

@@pp_ifdef __VDISCARD@@
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VDISCARD, 'O'))
					continue;
@@pp_endif@@

				/* Check for ^V */
@@pp_ifdef __VLNEXT@@
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VLNEXT, 'V')) {
					escape = true;
					continue;
				}
@@pp_endif@@

				/* Both line- and word-kill are treated as a full reset. */
@@pp_if defined(__VKILL) || defined(__VWERASE)@@
				if (
@@pp_ifdef __VKILL@@
				    ch == __PRIVATE_GETPASSFD_CTRL(__VKILL, 'U')
@@pp_endif@@
@@pp_if defined(__VKILL) && defined(__VWERASE)@@
				    ||
@@pp_endif@@
@@pp_ifdef __VWERASE@@
				    ch == __PRIVATE_GETPASSFD_CTRL(__VWERASE, 'W')
@@pp_endif@@
				    )
				{
					__libc_explicit_bzero(buf, buflen * sizeof(char));
@@pp_if $has_function(write)@@
					if (flags & (__GETPASS_ECHO | __GETPASS_ECHO_STAR)) {
						while (dst > (unsigned char *)buf) {
							if (write(fds[1], "\b \b", 3 * sizeof(char)) == -1)
								goto out;
							--dst;
						}
					}
@@pp_endif@@
					dst = (unsigned char *)buf;
					continue;
				}
@@pp_endif@@

				/* Check for end-of-file (via ^D) */
@@pp_ifdef __VEOF@@
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VEOF, 'D'))
					goto handle_eof;
@@pp_endif@@

				/* Check for TTY signal characters. */
@@pp_if defined(__VINTR) && defined(__SIGINT)@@
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VINTR, 'C')) {
					interrupt_signo = __SIGINT;
					goto out;
				}
@@pp_endif@@

@@pp_if defined(__VQUIT) && defined(__SIGQUIT)@@
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VQUIT, '\\')) {
					interrupt_signo = __SIGQUIT;
					goto out;
				}
@@pp_endif@@

@@pp_if (defined(__VSUSP) || defined(__VDSUSP)) && defined(__SIGTSTP)@@
				if (
@@pp_ifdef __VSUSP@@
				    ch == __PRIVATE_GETPASSFD_CTRL(__VSUSP, 'Z')
@@pp_endif@@
@@pp_if defined(__VSUSP) && defined(__VDSUSP)@@
				    ||
@@pp_endif@@
@@pp_ifdef __VDSUSP@@
				    ch == __PRIVATE_GETPASSFD_CTRL(__VDSUSP, 'Y')
@@pp_endif@@
				    ) {
					interrupt_signo = __SIGTSTP;
					goto out;
				}
@@pp_endif@@

				/* Check for custom newline characters. */
@@pp_ifdef __VEOL@@
				if (new_ios.@c_cc@[__VEOL] != __VDISABLE && ch == new_ios.@c_cc@[__VEOL])
					break;
@@pp_endif@@
@@pp_ifdef __VEOL2@@
				if (new_ios.@c_cc@[__VEOL2] != __VDISABLE && ch == new_ios.@c_cc@[__VEOL2])
					break;
@@pp_endif@@
@@pp_endif@@

				/* Check for single-character erase (backspace) */
@@pp_if $has_function(tcgetattr) && $has_function(tcsetattr) && defined(__VERASE)@@
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VERASE, 'H'))
@@pp_else@@
				if (ch == '\b')
@@pp_endif@@
				{
					if (dst > (unsigned char *)buf) {
						--dst;
						__libc_explicit_bzero(dst, sizeof(char));
@@pp_if $has_function(write)@@
						if (flags & (__GETPASS_ECHO | __GETPASS_ECHO_STAR)) {
							if (write(fds[1], "\b \b", 3 * sizeof(char)) == -1)
								goto out;
						}
@@pp_endif@@
						continue;
					}
maybe_beep:
@@pp_if $has_function(write)@@
					if (!(flags & __GETPASS_NO_BEEP)) {
						if (write(fds[2], "\7" /*BEL*/, sizeof(char)) == -1)
							goto out;
					}
@@pp_endif@@
					continue;
				}

				/* Check for generic newline characters. */
				if (ch == '\r' || ch == '\n')
					break;

			} /* if (!escape) */

			/* Special case: _always_ stop when a NUL-character would be appended.
			 * Note  that this is  undocumented behavior, but  is also mirrored by
			 * what is done by NetBSD's implementation in this case. */
			if (ch == '\0')
				break;

			/* Check if the buffer is full. */
			if (dst >= bufend) {
@@pp_if $has_function(malloc)@@
				if (heap_buf) {
					/* Allocate more space. */
					size_t new_buflen;
					char *new_buf;
					new_buflen = buflen * 2;
					new_buf = (char *)malloc(new_buflen * sizeof(char));
					if unlikely(!new_buf) {
						new_buflen = buflen + 1;
						new_buf = (char *)malloc(new_buflen * sizeof(char));
						if unlikely(!new_buf)
							goto out;
					}
					memcpyc(new_buf, buf, buflen, sizeof(char));
					__libc_explicit_bzero(buf, buflen * sizeof(char));
@@pp_if $has_function(free)@@
					free(buf);
@@pp_endif@@
					dst    = (unsigned char *)new_buf + (size_t)(dst - (unsigned char *)buf);
					bufend = (unsigned char *)new_buf + new_buflen - 1;
					buf    = new_buf;
				} else
@@pp_endif@@
				{
					if (flags & __GETPASS_BUF_LIMIT)
						goto maybe_beep;
					continue;
				}
			}

			/* Deal with special character conversions. */
			if (flags & __GETPASS_7BIT)
				ch &= 0x7f;
			if (flags & __GETPASS_FORCE_LOWER)
				ch = (unsigned char)tolower((char)ch);
			if (flags & __GETPASS_FORCE_UPPER)
				ch = (unsigned char)toupper((char)ch);

			/* Append to the result buffer. */
			*dst++ = ch;

@@pp_if $has_function(write)@@
			if (flags & __GETPASS_ECHO_STAR) {
				if (write(fds[1], "*", sizeof(char)) == -1)
					goto out;
			} else if (flags & __GETPASS_ECHO) {
				if (!isprint((char)ch))
					ch = (unsigned char)'?';
				if (write(fds[1], &ch, sizeof(char)) == -1)
					goto out;
			}
@@pp_endif@@

		} /* for (;;) */

		/* If requested to do so by the caller, write a trailing '\n' upon success. */
@@pp_if $has_function(write)@@
		if (flags & __GETPASS_ECHO_NL) {
			if (write(fds[1], "\n", 1) == -1)
				goto out;
		}
@@pp_endif@@

		/* Force NUL-termination of the password buffer. */
		*dst = '\0';

@@pp_if $has_function(malloc)@@
		if (heap_buf && dst < bufend) {
			/* Try to release unused buffer memory. */
			size_t new_buflen;
			char *new_buf;
			new_buflen = (size_t)((dst + 1) - (unsigned char *)buf);
			new_buf    = (char *)malloc(new_buflen * sizeof(char));
			if likely(new_buf) {
				memcpyc(new_buf, buf, new_buflen, sizeof(char));
				__libc_explicit_bzero(buf, buflen * sizeof(char));
@@pp_if $has_function(free)@@
				free(buf);
@@pp_endif@@
				buf    = new_buf;
				buflen = new_buflen;
			}
		}
@@pp_endif@@

		/* Indicate success! */
		result = buf;
	}
out:

	/* Restore old terminal settings. */
@@pp_if $has_function(tcgetattr) && $has_function(tcsetattr)@@
	if (memcmp(&old_ios, &new_ios, sizeof(struct termios)) != 0) {
@@pp_if defined(__TCSAFLUSH) && defined(__TCSASOFT)@@
		(void)tcsetattr(fds[0], __TCSAFLUSH | __TCSASOFT, &old_ios);
@@pp_elif defined(__TCSAFLUSH)@@
		(void)tcsetattr(fds[0], __TCSAFLUSH, &old_ios);
@@pp_else@@
		(void)tcsetattr(fds[0], 0, &old_ios);
@@pp_endif@@
	}
@@pp_endif@@

	/* Close our file handle to /dev/tty */
@@pp_if $has_function(close)@@
	if (default_fds[0] != __STDIN_FILENO)
		close(default_fds[0]);
@@pp_endif@@

	/* Error-only cleanup... */
	if (!result) {

		/* Don't leave a (possibly incomplete) password dangling in-memory! */
		__libc_explicit_bzero(buf, buflen * sizeof(char));

		/* Free a dynamically allocated password buffer. */
@@pp_if $has_function(malloc) && $has_function(free)@@
		if (heap_buf)
			free(buf);
@@pp_endif@@

		/* Raise the signal of a given control character, and/or set
		 * `errno'  to indicate that the password-read operation was
		 * interrupted. */
		if (interrupt_signo != 0) {
@@pp_if $has_function(raise)@@
			if (!(flags & __GETPASS_NO_SIGNAL))
				(void)raise(interrupt_signo);
@@pp_endif@@
@@pp_ifdef EINTR@@
			(void)libc_seterrno(EINTR);
@@pp_endif@@
		}
	}
	return result;
}



@@>> getpass_r(3)
[[cp, wunused]]
[[requires($has_function(getpassfd) || $has_function(readpassphrase))]]
[[impl_include("<asm/crt/getpassfd.h>")]]
[[impl_include("<asm/crt/readpassphrase.h>")]]
[[decl_include("<hybrid/typecore.h>")]]
char *getpass_r([[nullable]] char const *prompt, char *buf, size_t bufsize) {
@@pp_if $has_function(getpassfd)@@
	/* Prefer using `getpassfd(3)' because I feel like that one's more
	 * user-friendly.  - But if it's not available, fall back on using
	 * the regular, old `readpassphrase(3)' */
@@pp_ifdef __GETPASS_ECHO_NL@@
	return getpassfd(prompt, buf, bufsize, NULL, __GETPASS_ECHO_NL, 0);
@@pp_else@@
	return getpassfd(prompt, buf, bufsize, NULL, 0, 0);
@@pp_endif@@
@@pp_else@@
@@pp_ifdef __RPP_ECHO_OFF@@
	return readpassphrase(prompt, buf, bufsize, __RPP_ECHO_OFF);
@@pp_else@@
	return readpassphrase(prompt, buf, bufsize, 0);
@@pp_endif@@
@@pp_endif@@
}

%
%/* WARNING: `setmode(3)' is also a completely different DOS-specific function in <io.h>! */

@@>> setmode(3), getmode(3)
[[guard, wunused]]
void *setmode([[nonnull]] char const *mode_str); /* TODO: Implement here! */

[[wunused, doc_alias("setmode")]]
$mode_t getmode([[nonnull]] void const *bbox, $mode_t mode); /* TODO: Implement here! */

@@>> getpeereid(3)
@@Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)'
[[guard, requires_include("<asm/os/socket.h>")]]
[[requires($has_function(getsockopt) &&
           (defined(__SOL_SOCKET) && defined(__SO_PEERCRED)))]]
[[impl_include("<bits/os/ucred.h>", "<libc/errno.h>")]]
int getpeereid($fd_t sockfd,
               [[nonnull]] uid_t *euid,
               [[nonnull]] gid_t *egid) {
	int result;
	struct ucred cred;
	socklen_t len = sizeof(cred);
	result = getsockopt(sockfd, __SOL_SOCKET, __SO_PEERCRED, &cred, &len);
	if (result == 0) {
		/* Safety check that enough data was read... */
		if (len < (__COMPILER_OFFSETAFTER(struct ucred, @uid@) >
		           __COMPILER_OFFSETAFTER(struct ucred, @gid@)
		           ? __COMPILER_OFFSETAFTER(struct ucred, @uid@)
		           : __COMPILER_OFFSETAFTER(struct ucred, @gid@))) {
@@pp_ifdef ENOPROTOOPT@@
			result = libc_seterrno(ENOPROTOOPT);
@@pp_else@@
			result = libc_seterrno(1);
@@pp_endif@@
		} else {
			*euid = cred.@uid@;
			*egid = cred.@gid@;
		}
	}
	return result;
}

//TODO:int des_cipher(char const *, char *, long, int);
//TODO:int des_setkey(char const *);
//TODO:int exect(char const *, char *const *, char *const *);
//TODO:int fdiscard(int, off_t, off_t);
//TODO:int fsync_range(int, int, off_t, off_t);
//TODO:int getgroupmembership(char const *, gid_t, gid_t *, int, int *);
//TODO:int iruserok(uint32_t, int, char const *, char const *);
//TODO:long lpathconf(char const *, int);
//TODO:int nfssvc(int, void *);
//TODO:int setrgid(gid_t);
//TODO:int setruid(uid_t);
//TODO:int swapctl(int, void *, int);
//TODO:int undelete(char const *);
//TODO:int rresvport_af_addr(int *, int, void *);
//TODO:int iruserok_sa(const void *, int, int, char const *, char const *);
//TODO:extern int optreset;
//TODO:extern char *suboptarg;

//int   reboot(int,   char  *);   //   Incompatible  w/   linux:   int  reboot(int)
//int swapon(char const *); // Incompatible w/ linux: int swapon(char const *, int)
%#endif /* __USE_NETBSD */


%
%
%#if defined(_EVERY_SOURCE) || defined(__USE_SOLARIS) || (defined(__USE_UNIX98) && !defined(__USE_XOPEN2K))
%[insert:extern(pthread_atfork)]
%#endif /* _EVERY_SOURCE || __USE_SOLARIS || (__USE_UNIX98 && !__USE_XOPEN2K) */


%
%
%#if defined(__USE_REENTRANT) || defined(__USE_SOLARIS)
@@>> ctermid_r(3)
@@Same as `ctermid', but return `NULL' when `s' is `NULL'
[[guard, requires_function(ctermid)]]
[[userimpl, section(".text.crt{|.dos}.io.tty")]]
char *ctermid_r([[nullable]] char *s) {
	return s ? ctermid(s) : NULL;
}
%#endif /* __USE_REENTRANT || __USE_SOLARIS */
%
%

@@>> sysconf(2)
@@@param: name: One of `_SC_*' from <asm/crt/confname.h>
@@Return   a   system    configuration   value    `name'
@@return: * : The configuration limit associated with `name' for `path'
@@return: -1: [errno=<unchanged>] `name'  refers to a maximum or minimum
@@                                limit, and that limit is indeterminate
@@return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option
[[cp, wunused, decl_include("<features.h>")]]
[[export_alias("__sysconf")]]
[[section(".text.crt{|.dos}.system.configuration")]]
$longptr_t sysconf(__STDC_INT_AS_UINT_T name);


%
%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_POSIX))
%{
#if !defined(F_ULOCK) && defined(__F_ULOCK)
#define F_ULOCK __F_ULOCK /* Unlock a previously locked region. */
#endif /* !F_ULOCK && __F_ULOCK */
#if !defined(F_LOCK) && defined(__F_LOCK)
#define F_LOCK  __F_LOCK  /* Lock a region for exclusive use. */
#endif /* !F_LOCK && __F_LOCK */
#if !defined(F_TLOCK) && defined(__F_TLOCK)
#define F_TLOCK __F_TLOCK /* Test and lock a region for exclusive use. */
#endif /* !F_TLOCK && __F_TLOCK */
#if !defined(F_TEST) && defined(__F_TEST)
#define F_TEST  __F_TEST  /* Test a region for other processes locks. */
#endif /* !F_TEST && __F_TEST */
}
%[insert:extern(lockf)]
%#ifdef __USE_LARGEFILE64
%[insert:extern(lockf64)]
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_POSIX) */
%
%
%{
#if defined(__USE_GNU) && !defined(__NO_XBLOCK)
#ifdef __COMPILER_HAVE_TYPEOF
#define TEMP_FAILURE_RETRY(expression)                           \
	__XBLOCK({                                                   \
		__typeof__(expression) __tfr_result;                     \
		do {                                                     \
			__tfr_result = (expression);                         \
		} while (__tfr_result == (__typeof__(__tfr_result))-1 && \
		         errno == EINTR);                                \
		__XRETURN __tfr_result;                                  \
	})
#else /* __COMPILER_HAVE_TYPEOF */
#define TEMP_FAILURE_RETRY(expression)                   \
	__XBLOCK({                                           \
		long int __tfr_result;                           \
		do {                                             \
			__tfr_result = (long int)(expression);       \
		} while (__tfr_result == -1L && errno == EINTR); \
		__XRETURN __tfr_result;                          \
	})
#endif /* !__COMPILER_HAVE_TYPEOF */
#endif /* __USE_GNU && !__NO_XBLOCK */


#ifdef __USE_BSD
}

@@>> closefrom(2)
@@Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)')
[[guard, requires_include("<asm/os/fcntl.h>")]]
[[requires(($has_function(fcntl) && defined(__F_CLOSEM)) || $has_function(close_range))]]
[[section(".text.crt{|.dos}.bsd.io.access")]]
void closefrom($fd_t lowfd) {
@@pp_if $has_function(fcntl) && defined(__F_CLOSEM)@@
	fcntl(lowfd, __F_CLOSEM);
@@pp_else@@
	close_range((unsigned int)lowfd, (unsigned int)-1, 0);
@@pp_endif@@
}

@@>> close_range(2)
@@Close all files handles `>= minfd && <= maxfd' (but see `flags')
@@@param: flags: Set of `0 | CLOSE_RANGE_UNSHARE | CLOSE_RANGE_CLOEXEC'
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[guard, section(".text.crt{|.dos}.bsd.io.access")]]
int close_range(unsigned int minfd, unsigned int maxfd, unsigned int flags);

@@>> issetugid(3)
@@Check if the calling program is running under setuid-mode
@@Hint: simply returns the value of `__libc_enable_secure(3)'.
[[guard, wunused, pure]]
[[requires_include("<libc/template/__libc_enable_secure.h>")]]
[[requires(defined(__LOCAL___libc_enable_secure))]]
[[impl_include("<libc/template/__libc_enable_secure.h>")]]
[[section(".text.crt{|.dos}.sched.user")]]
int issetugid(void) {
	return __LOCAL___libc_enable_secure;
}


%{
#endif /* __USE_BSD */

#if defined(__USE_SOLARIS) || defined(__USE_NETBSD)
}

@@>> fchroot(2)
@@Change the root directory to  `fd'. If `fd' was opened  before a prior call to  `chroot()',
@@and referrs to  a directory,  then this function  can be  used to escape  a chroot()  jail.
@@No special permissions  are required to  use this function,  since a malicious  application
@@could achieve the same behavior by use of `*at' system calls, using `fd' as `dfd' argument.
[[requires($has_function(dup2) && defined(__AT_FDROOT))]]
[[requires_include("<asm/os/fcntl.h>")]]
[[impl_include("<asm/os/fcntl.h>")]]
int fchroot($fd_t fd) {
	fd_t result;
	result = dup2(fd, __AT_FDROOT);
	if likely(result >= 0)
		result = 0;
	return result;
}

%[insert:extern(rresvport_af)]

%{
#endif /* __USE_SOLARIS || __USE_NETBSD */

#ifdef __USE_SOLARIS
}
%[default:section(".text.crt{|.dos}.solaris")]

%[insert:extern(fattach)]
%[insert:extern(fdetach)]
%[insert:extern(ioctl)]
%[insert:extern(rexec_af)]
%[insert:extern(stime)]
%[insert:extern(tell)]
%[insert:function(yield = thrd_yield)]

// TODO: char *gettxt(char const *, char const *);
// TODO: int isaexec(char const *, char *const *, char *const *);
// TODO: offset_t llseek($fd_t fd, offset_t offset, __STDC_INT_AS_UINT_T whence);


@@>> resolvepath(3)
@@Similar  to  `frealpathat(2)'  (though  use  the  later  for  more   options)
@@Also note that this function appears to  have a weird rule (which KOS  simply
@@ignores)  that is related  to this function not  writing more than `PATH_MAX'
@@bytes to `buf'. (Why??? I mean: The whole point of having a `buflen' argument
@@is to be able to handle names of arbitrary lengths)
@@Additionally, the online docs don't mention what happens when `buflen' is  too
@@small, so I guess I can just make up what's supposed to happen, and I say that
@@the function will set errno=ERANGE and return -1
@@@return: * : Used buffer size (possibly including a NUL-byte, but maybe not)
@@@return: -1: Error. (s.a. `errno')
[[decl_include("<hybrid/typecore.h>")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires($has_function(frealpathat) && defined(__AT_FDCWD))]]
[[crt_dos_variant, impl_include("<libc/errno.h>")]]
__STDC_INT_AS_SSIZE_T resolvepath([[nonnull]] char const *filename,
                                  char *resolved, $size_t buflen) {
	__STDC_INT_AS_SSIZE_T retval;
	char *result;
	result = frealpathat(__AT_FDCWD, filename, resolved, buflen, 0);
	if unlikely(!result)
		return -1;
	retval = (__STDC_INT_AS_SSIZE_T)strlen(result);
@@pp_if $has_function(free)@@
	if unlikely(!resolved)
		free(result);
@@pp_endif@@
	return retval;
}


@@>> tell(3), tell64(3)
@@Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)')
[[guard, wunused, decl_include("<features.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("tell", "_tell")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("tell64", "_telli64")]]
[[requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(lseek) && defined(__SEEK_CUR))]]
[[impl_include("<asm/os/stdio.h>"), dos_only_export_as("_tell")]]
$off_t tell($fd_t fd) {
	return lseek(fd, 0, SEEK_CUR);
}

%#ifdef __USE_LARGEFILE64
[[guard, wunused, decl_include("<bits/types.h>")]]
[[preferred_off64_variant_of(tell), doc_alias("tell")]]
[[requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(lseek64) && defined(__SEEK_CUR))]]
[[impl_include("<asm/os/stdio.h>"), dos_only_export_alias("_telli64")]]
$off64_t tell64($fd_t fd) {
	return lseek64(fd, 0, __SEEK_CUR);
}
%#endif /* __USE_LARGEFILE64 */


%{
#endif /* __USE_SOLARIS */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_UNISTD_H)
#include <parts/wchar/unistd.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_UNISTD_H */
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_UNISTD_H)
#include <parts/uchar/unistd.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_UNISTD_H */
#endif /* __USE_UTF */

}
