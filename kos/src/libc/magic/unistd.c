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
%(c_prefix){
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/unistd.h) */
/* (#) Portability: DJGPP         (/include/unistd.h) */
/* (#) Portability: DragonFly BSD (/include/unistd.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/unistd.h) */
/* (#) Portability: FreeBSD       (/include/unistd.h) */
/* (#) Portability: GNU C Library (/posix/unistd.h) */
/* (#) Portability: GNU Hurd      (/usr/include/unistd.h) */
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
/*!always_includes <bits/types/NULL.h>*/
/*!always_includes <bits/types/size_t.h>*/
/*!always_includes <bits/types/ssize_t.h>*/
}

%[define_replacement(fd_t       = __fd_t)]
%[define_replacement(off_t      = "__off_t")]
%[define_replacement(pos_t      = "__pos_t")]
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

#ifdef __INTELLISENSE__
#include <bits/types/NULL.h>
#include <bits/types/size_t.h>
#include <bits/types/ssize_t.h>
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#include <bits/types/gid_t.h>
#include <bits/types/uid_t.h>
#include <bits/types/off_t.h>
#include <bits/types/useconds_t.h>
#include <bits/types/pid_t.h>
#ifdef __USE_LARGEFILE64
#include <bits/types/off64_t.h>
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN || __USE_XOPEN2K */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#include <bits/types/intptr_t.h>
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */
#if defined(__USE_MISC) || defined(__USE_XOPEN)
#include <bits/types/socklen_t.h>
#endif /* __USE_MISC || __USE_XOPEN */
#endif /* __INTELLISENSE__ */

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

/* susv4-2018: Inclusion  of  the  <unistd.h>  header  may  make  visible  all
 *             symbols from the headers <stddef.h>, <stdint.h>, and <stdio.h>. */
#ifdef __USE_POSIX_BLOAT
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#endif /* __USE_POSIX_BLOAT */

#ifdef __USE_SOLARIS
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

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

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
typedef __off_t off_t;
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
__CDECLARE(,int,__NOTHROW_NCX,_get_environ,(char ***__p_environ),())
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
[[section(".text.crt{|.dos}.fs.exec.exec")]]
int execv([[in]] char const *__restrict path, [[in]] __TARGV) {
	return execve(path, ___argv, __LOCAL_environ);
}

@@>> execve(2)
@@Replace the calling  process with  the application  image referred  to by  `path' /  `file'
@@and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
[[cp, guard, dos_export_alias("_execve"), export_alias("__execve", "__libc_execve"), argument_names(path, ___argv, ___envp)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV), crt_dos_variant]]
[[if(__has_builtin(__builtin_execve) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(execve, { return __builtin_execve(path, (char *const *)___argv, (char *const *)___envp); })]]
[[section(".text.crt{|.dos}.fs.exec.exec")]]
int execve([[in]] char const *__restrict path, [[in]] __TARGV, [[in]] __TENVP);

@@>> execvp(3)
@@Replace the calling  process with  the application  image referred  to by  `path' /  `file'
@@and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp'
[[cp, guard, dos_export_alias("_execvp"), argument_names(file, ___argv)]]
[[decl_include("<features.h>"), decl_prefix(DEFINE_TARGV), crt_dos_variant]]
[[if(__has_builtin(__builtin_execvp) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline(execvp, { return __builtin_execvp(file, (char *const *)___argv); })]]
[[requires_include("<libc/template/environ.h>"), requires($has_function(execvpe) && defined(__LOCAL_environ))]]
[[impl_include("<libc/template/environ.h>")]]
[[section(".text.crt{|.dos}.fs.exec.exec")]]
int execvp([[in]] char const *__restrict file, [[in]] __TARGV) {
	return execvpe(file, ___argv, __LOCAL_environ);
}


@@>> execl(3)
@@Replace the calling process with the application image referred to by `path' / `file'
@@and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list
[[cp, guard, ATTR_SENTINEL, dos_export_alias("_execl"), impl_include("<parts/redirect-exec.h>")]]
[[requires_dependent_function(execv), crtbuiltin, crt_dos_variant]]
[[section(".text.crt{|.dos}.fs.exec.exec")]]
int execl([[in]] char const *__restrict path, [[in_opt]] char const *args, ... /*, (char *)NULL*/) {
	__REDIRECT_EXECL(char, execv, path, args)
}

@@>> execle(3)
@@Replace the calling process with the application image referred to by `path' / `file'
@@and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
@@and setting `environ' to a `char **' passed after the NULL sentinel
[[cp, guard, impl_include("<parts/redirect-exec.h>"), dos_export_alias("_execle"), crtbuiltin]]
[[requires_dependent_function(execve), ATTR_SENTINEL_O(1), crt_dos_variant]]
[[section(".text.crt{|.dos}.fs.exec.exec")]]
int execle([[in]] char const *__restrict path, [[in_opt]] char const *args, ... /*, (char *)NULL, [[in]] (char **)environ*/) {
	__REDIRECT_EXECLE(char, execve, path, args)
}

@@>> execlp(3)
@@Replace the calling process with the application image referred to by `path' / `file'
@@and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list
[[cp, guard, impl_include("<parts/redirect-exec.h>"), dos_export_alias("_execlp")]]
[[requires_dependent_function(execvp), ATTR_SENTINEL, crtbuiltin, crt_dos_variant]]
[[section(".text.crt{|.dos}.fs.exec.exec")]]
int execlp([[in]] char const *__restrict file, [[in_opt]] char const *args, ... /*, (char *)NULL*/) {
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
[[section(".text.crt{|.dos}.fs.exec.exec")]]
int execvpe([[in]] char const *__restrict file,
            [[in]] __TARGV, [[in]] __TENVP) {
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
[[section(".text.crt{|.dos}.fs.exec.exec")]]
int execlpe([[in]] char const *__restrict file, [[in_opt]] char const *args, ... /*, (char *)NULL, [[in_opt]] (char **)environ*/) {
	__REDIRECT_EXECLE(char, execvpe, file, args)
}
%#endif /* __USE_KOS || __USE_DOS || __USE_NETBSD */

@@>> getpid(2)
@@Return the PID of the calling process (that is the TID of the calling thread group's leader)
@@THIS_THREAD->LEADER->PID
[[guard, const, wunused, nothrow, decl_include("<bits/types.h>")]]
[[dos_only_export_alias("_getpid"), export_alias("__getpid", "__libc_getpid")]]
[[section(".text.crt{|.dos}.sched.process")]]
$pid_t getpid();

%#ifdef __USE_KOS
@@>> gettid(2)
@@Return the TID of the calling thread
@@THIS_THREAD->PID
[[guard, const, wunused, nothrow, decl_include("<bits/types.h>")]]
[[dos_only_export_alias("__threadid", "?GetCurrentThreadId@platform@details@Concurrency@@YAJXZ")]]
[[export_alias("pthread_getthreadid_np")]]
[[section(".text.crt{|.dos}.sched.thread")]]
$pid_t gettid();
%#endif /* __USE_KOS */

[[ignore, nocrt, alias("_pipe")]]
[[decl_include("<bits/types.h>")]]
int dos_pipe([[out]] $fd_t pipedes[2],
             $uint32_t pipesize, $oflag_t textmode);

@@>> pipe(2)
@@Create a new pair of connected pipes ([0] = reader, [1] = writer)
@@@param: pipedes: Output for pipe fds: [0]: reader; [1]: writer
@@@return: 0:  Success
@@@return: -1: Error (s.a. `errno')
[[export_alias("__pipe", "__libc_pipe")]]
[[userimpl, requires_function(dos_pipe)]]
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.io.access")]]
int pipe([[out]] $fd_t pipedes[2]) {
	return dos_pipe(pipedes, 4096, 0x8000); /* O_BINARY */
}

@@>> sleep(3)
@@Sleep for up to `seconds' seconds
@@@return: 0 : Timeout expired
@@@return: * : You were interrupted, and this many seconds were still left on the timeout
[[cp, guard]]
[[requires($has_function(nanosleep) || $has_function(_sleep))]]
[[impl_include("<bits/os/timespec.h>")]]
[[impl_include("<libc/errno.h>")]]
[[userimpl, section(".text.crt{|.dos}.system.utility")]]
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
int fsync([[fdwrite]] $fd_t fd) {
	COMPILER_IMPURE();
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
[[section(".text.crt{|.dos}.sched.process")]]
$pid_t getppid();


@@>> getpgrp(2)
@@Return the ID of the calling process's process group.
@@(That is the TID of the leader of the process group of the calling thread's leader)
@@THIS_THREAD->LEADER->GROUP_LEADER->PID
[[wunused, decl_include("<bits/types.h>")]]
[[export_alias("__getpgrp", "__libc_getpgrp")]]
[[section(".text.crt{|.dos}.sched.process")]]
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
[[section(".text.crt{|.dos}.sched.process")]]
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
[[section(".text.crt{|.dos}.sched.process")]]
$pid_t setsid();

@@>> getuid(2)
@@Return the real user ID of the calling process
[[wunused, decl_include("<bits/types.h>")]]
[[export_alias("__getuid", "__libc_getuid")]]
[[userimpl, requires_function(getresuid)]]
[[section(".text.crt{|.dos}.sched.user")]]
$uid_t getuid() {
	uid_t result;
	if (getresuid(&result, NULL, NULL))
		result = (uid_t)-1;
	return result;
}

@@>> getgid(2)
@@Return the real group ID of the calling process
[[wunused, decl_include("<bits/types.h>")]]
[[export_alias("__getgid", "__libc_getgid")]]
[[userimpl, requires_function(getresgid)]]
[[section(".text.crt{|.dos}.sched.user")]]
$gid_t getgid() {
	gid_t result;
	if (getresgid(&result, NULL, NULL))
		result = (gid_t)-1;
	return result;
}

@@>> geteuid(2)
@@Return the effective user ID of the calling process
[[wunused, decl_include("<bits/types.h>")]]
[[export_alias("__geteuid", "__libc_geteuid")]]
[[userimpl, requires_function(getresuid)]]
[[section(".text.crt{|.dos}.sched.user")]]
$uid_t geteuid() {
	uid_t result;
	if (getresuid(NULL, &result, NULL))
		result = (uid_t)-1;
	return result;
}

@@>> getegid(2)
@@Return the effective group ID of the calling process
[[wunused, decl_include("<bits/types.h>")]]
[[export_alias("__getegid", "__libc_getegid")]]
[[userimpl, requires_function(getresgid)]]
[[section(".text.crt{|.dos}.sched.user")]]
$gid_t getegid() {
	gid_t result;
	if (getresgid(NULL, &result, NULL))
		result = (gid_t)-1;
	return result;
}

@@>> getgroups(2)
@@@return: * : [count == 0] The required number of groups
@@@return: * : [count != 0] The number of groups that were actually returned
@@@return: -1: [errno == -EINVAL && count != 0] There are more than `count' groups
[[decl_include("<bits/types.h>")]]
[[export_alias("__getgroups", "__libc_getgroups")]]
[[section(".text.crt{|.dos}.sched.user")]]
int getgroups(int size, [[out(return <= size)]] $gid_t list[]);

@@>> setuid(2)
@@Set the effective user ID of the calling process
@@@return: 0 : Success
@@@return: -1: [errno=EINVAL] : The given `uid' is invalid
@@@return: -1: [errno=EPERM]  : The current user is not privileged
[[decl_include("<bits/types.h>")]]
[[export_alias("__setuid", "__libc_setuid")]]
[[userimpl, requires_function(setreuid, seteuid)]]
[[section(".text.crt{|.dos}.sched.user")]]
int setuid($uid_t uid) {
	int result = setreuid(uid, uid);
	if (result != 0)
		result = seteuid(uid);
	return result;
}

@@>> setgid(2)
@@Set the effective group ID of the calling process
@@@return: 0 : Success
@@@return: -1: [errno=EINVAL] : The given `gid' is invalid
@@@return: -1: [errno=EPERM]  : The current user is not privileged
[[decl_include("<bits/types.h>")]]
[[export_alias("__setgid", "__libc_setgid")]]
[[userimpl, requires_function(setreuid, seteuid)]]
[[section(".text.crt{|.dos}.sched.user")]]
int setgid($gid_t gid) {
	int result = setregid(gid, gid);
	if (result != 0)
		result = setegid(gid);
	return result;
}


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
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.sched.access")]]
$pid_t fork();


@@>> alarm(2)
@@@return: 0 : No alarm was scheduled before.
@@@return: * : The number of seconds yet to pass before a previous alarm would have elapsed.
@@Schedule an to deliver a `SIGALRM' after letting `seconds' elapse.
@@You may pass `0' for `seconds' to disable a previously scheduled alarm
[[export_alias("__alarm", "__libc_alarm")]]
[[section(".text.crt{|.dos}.system.utility")]]
unsigned int alarm(unsigned int seconds);

@@>> pause(2)
@@Suspend execution until the delivery of a POSIX_SIGNAL
[[cp]]
[[export_alias("__pause", "__libc_pause")]]
[[section(".text.crt{|.dos}.system.utility")]]
int pause();

@@>> fpathconf(3)
@@@param: name: One   of    `_PC_*'    from    <asm/crt/confname.h>
@@Return a path configuration value associated with `name' for `fd'
@@return: * : The configuration limit associated with `name' for `fd'
@@return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `fd'
@@return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option
[[cp, wunused, decl_include("<features.h>", "<bits/types.h>")]]
[[export_alias("__fpathconf")]]
[[section(".text.crt{|.dos}.fs.property")]]
$longptr_t fpathconf([[fdarg]] $fd_t fd, __STDC_INT_AS_UINT_T name);

@@>> ttyname(3)
@@Return the name of a TTY given its file descriptor
[[guard, cp, wunused, decl_include("<bits/types.h>")]]
[[export_alias("__ttyname"), requires_function(ttyname_r)]]
[[impl_include("<asm/os/errno.h>")]]
[[section(".text.crt{|.dos}.io.tty")]]
char *ttyname([[fdarg]] $fd_t fd) {
@@pp_if $has_function(realloc)@@
	/* Buffer is typed as `void *' so it can be re-used for `wttyname(3)' */
	@@static void *ttyname_buf; [fini: free(ttyname_buf)]@@
	errno_t error;
@@pp_if $has_function(malloc_usable_size)@@
	size_t bufsize = malloc_usable_size(ttyname_buf) / sizeof(char);
@@pp_else@@
	size_t bufsize = ttyname_buf ? 32 : 0;
@@pp_endif@@
	if (bufsize < 32) {
		void *newbuf;
		bufsize = 32;
		newbuf  = realloc(ttyname_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		ttyname_buf = newbuf;
	}
@@pp_ifdef ERANGE@@
again:
@@pp_endif@@
	error = ttyname_r(fd, (char *)ttyname_buf, bufsize);
	if likely(error == 0) {
		/* Trim unused memory (if a certain threshold is exceeded) */
		size_t retlen = strlen((char *)ttyname_buf) + 1;
		if (retlen < 32)
			retlen = 32; /* Retain minimal buffer size */
		if likely((retlen + 32) < bufsize) {
			void *retbuf = realloc(ttyname_buf, retlen * sizeof(char));
			if likely(retbuf)
				ttyname_buf = retbuf;
		}
		return (char *)ttyname_buf;
	}
@@pp_ifdef ERANGE@@
	if (error == ERANGE && bufsize < 1024) {
		void *newbuf;
		bufsize *= 2;
		newbuf = realloc(ttyname_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		ttyname_buf = newbuf;
		goto again;
	}
@@pp_endif@@
@@pp_if $has_function(free)@@
	free(ttyname_buf);
	ttyname_buf = NULL;
@@pp_endif@@
err:
	return NULL;
@@pp_else@@
	static char ttyname_buf[32];
	if likely(ttyname_r(fd, ttyname_buf, COMPILER_LENOF(ttyname_buf)) == 0)
		return ttyname_buf;
	return NULL;
@@pp_endif@@
}

@@>> ttyname_r(3)
@@Return the name of a TTY given its file descriptor
[[cp, decl_include("<bits/types.h>")]]
[[requires_include("<paths.h>")]]
[[requires(($has_function(frealpath4)) ||
           ($has_function(opendir, readdir64, fstat64, lstat64) && defined(_PATH_DEV)))]]
[[impl_include("<bits/types.h>", "<libc/errno.h>", "<asm/os/dirent.h>", "<asm/os/stat.h>")]]
[[impl_include("<paths.h>", "<bits/os/dirent.h>", "<bits/os/stat.h>", "<asm/os/fcntl.h>")]]
[[section(".text.crt{|.dos}.io.tty")]]
[[export_as("__ttyname_r")]] /* From Glibc 2.0.4 */
$errno_t ttyname_r([[fdarg]] $fd_t fd, [[out(? <= buflen)]] char *buf, size_t buflen) {

	/* Ensure that it's actually a TTY */
@@pp_if $has_function(isatty)@@
	if unlikely(!isatty(fd)) {
@@pp_ifdef ENOTTY@@
		libc_seterrno($ENOTTY);
		return $ENOTTY;
@@pp_else@@
		libc_seterrno(1);
		return 1;
@@pp_endif@@
	}
@@pp_endif@@

	/* Simply try to realpath() the given `fd' */
@@pp_if $has_function(frealpath4)@@
	if unlikely(!buf || !buflen) {
@@pp_ifdef ERANGE@@
		libc_seterrno($ERANGE);
		return $ERANGE;
@@pp_else@@
		libc_seterrno(1);
		return 1;
@@pp_endif@@
	}
	if unlikely(frealpath4(fd, buf, buflen, 0))
		return 0; /* Found it! */
	if (libc_geterrno() == ERANGE)
		return ERANGE;
@@pp_endif@@

	/* Fallback: Search `/dev' for the proper file */
@@pp_if $has_function(opendir, readdir64, fstat64, lstat64) && defined(_PATH_DEV)@@
	{
		struct stat64 st;
		struct dirent64 *d;
		DIR *dirstream;
		dev_t rdev;
		ino64_t ino;
@@pp_ifdef __libc_geterrno@@
		errno_t saved_errno;
@@pp_endif@@
		if unlikely(buflen < COMPILER_STRLEN(_PATH_DEV) * sizeof(char)) {
			libc_seterrno(ERANGE);
			return ERANGE;
		}
		if unlikely(fstat64(fd, &st) < 0)
			return libc_geterrno();
		if ((dirstream = opendir(_PATH_DEV)) == NULL)
			return libc_geterrno();
		memcpy(buf, _PATH_DEV, COMPILER_STRLEN(_PATH_DEV) * sizeof(char));
		buflen -= COMPILER_STRLEN(_PATH_DEV) * sizeof(char);
@@pp_ifdef __libc_geterrno@@
		saved_errno = __libc_geterrno();
@@pp_endif@@
		rdev = st.@st_dev@;
		ino  = st.@st_ino@;
		while ((d = readdir64(dirstream)) != NULL) {
			size_t needed;

			/* We're looking for character devices. */
			if (d->@d_type@ != __DT_CHR)
				continue;
			if (d->@d_ino@ != ino)
				continue;

@@pp_if !defined(__KOS__)@@
			/* On KOS, these are symlinks (DT_LNK), so we've already skipped them ;) */
			if (strcmp(d->@d_name@, "stdin") == 0)
				continue; /* Ignore the /dev/std(in|out|err) aliases */
			if (strcmp(d->@d_name@, "stdout") == 0)
				continue; /* *ditto* */
			if (strcmp(d->@d_name@, "stderr") == 0)
				continue; /* *ditto* */
@@pp_endif@@

			/* Load the length of the directory entry's filename. */
@@pp_ifdef _DIRENT_HAVE_D_NAMLEN@@
			needed = d->@d_namlen@;
@@pp_else@@
			needed = strlen(d->@d_name@);
@@pp_endif@@

			/* Check that the user-supplied buffer is large enough. */
			if (needed >= buflen) {
@@pp_if $has_function(closedir)@@
				closedir(dirstream);
@@pp_endif@@
@@pp_ifdef ERANGE@@
				libc_seterrno($ERANGE);
				return $ERANGE;
@@pp_else@@
				libc_seterrno(1);
				return 1;
@@pp_endif@@
			}
			memcpy(buf + COMPILER_STRLEN(_PATH_DEV),
			       d->@d_name@, (needed + 1) * sizeof(char));

			/* Load attributes of the file being enumerated */
@@pp_if $has_function(fstatat64, dirfd) && defined(__AT_SYMLINK_NOFOLLOW)@@
			if (fstatat64(dirfd(dirstream), d->@d_name@, &st, __AT_SYMLINK_NOFOLLOW) != 0)
				continue;
@@pp_else@@
			if (lstat64(buf, &st) != 0)
				continue;
@@pp_endif@@

			/* Verify that this is the file we're looking for. */
			if (st.@st_rdev@ != rdev)
				continue;
			if unlikely(st.@st_ino@ != ino)
				continue;
			if unlikely(!__S_ISCHR(st.@st_mode@))
				continue;

			/* Found it! */
@@pp_if $has_function(closedir)@@
			closedir(dirstream);
@@pp_endif@@
@@pp_ifdef __libc_geterrno@@
			__libc_seterrno(saved_errno);
@@pp_endif@@
			return 0;
		}
@@pp_if $has_function(closedir)@@
		closedir(dirstream);
@@pp_endif@@
@@pp_ifdef __libc_geterrno@@
		__libc_seterrno(saved_errno);
@@pp_endif@@
	}
@@pp_endif@@

	/* Fallback: indicate that this isn't a terminal... */
@@pp_ifdef ENOTTY@@
	return $ENOTTY;
@@pp_else@@
	return 1;
@@pp_endif@@
}


@@>> tcgetpgrp(2)
@@Return the foreground process group of a given TTY file descriptor
[[wunused, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/tty.h>")]]
[[requires($has_function(ioctl) && defined(__TIOCGPGRP))]]
[[section(".text.crt{|.dos}.io.tty")]]
$pid_t tcgetpgrp([[fdarg]] $fd_t fd) {
	pid_t result;
	if (ioctl(fd, __TIOCGPGRP, &result) < 0)
		result = -1;
	return result;
}

@@>> tcsetpgrp(2)
@@Set the foreground process group of a given TTY file descriptor
[[decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/tty.h>")]]
[[requires($has_function(ioctl) && defined(__TIOCSPGRP))]]
[[section(".text.crt{|.dos}.io.tty")]]
int tcsetpgrp([[fdarg]] $fd_t fd, $pid_t pgrp_id) {
	return ioctl(fd, __TIOCSPGRP, &pgrp_id) < 0 ? -1 : 0;
}

@@>> getlogin(3)
@@Return the login name for the current user, or `NULL' on error.
@@s.a. `getlogin_r()' and `cuserid()'
[[guard, wunused]]
[[requires($has_function(getenv) || $has_function(cuserid))]]
[[section(".text.crt{|.dos}.io.tty")]]
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

@@>> chown(2)
@@Change the ownership of a given `file' to `group:owner'
[[crt_dos_variant, cp, decl_include("<bits/types.h>")]]
[[userimpl, requires_include("<asm/os/fcntl.h>"), export_alias("__chown", "__libc_chown")]]
[[requires(defined(__AT_FDCWD) && $has_function(fchownat))]]
[[section(".text.crt{|.dos}.fs.modify")]]
int chown([[in]] char const *file, $uid_t owner, $gid_t group) {
	return fchownat(__AT_FDCWD, file, owner, group, 0);
}

@@>> pathconf(3)
@@@param: name: One of `_PC_*' from <asm/crt/confname.h>
@@Return a path configuration value associated with `name' for `path'
@@return: * : The configuration limit associated with `name' for `path'
@@return: -1: [errno=<unchanged>] The configuration specified by `name' is unlimited for `path'
@@return: -1: [errno=EINVAL]      The given `name' isn't a recognized config option
[[crt_dos_variant, cp, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[userimpl, requires_include("<asm/os/oflags.h>"), export_alias("__pathconf")]]
[[requires($has_function(fpathconf) && $has_function(open) && defined(__O_RDONLY))]]
[[section(".text.crt{|.dos}.fs.property")]]
$longptr_t pathconf([[in]] char const *path, __STDC_INT_AS_UINT_T name) {
	fd_t fd;
	longptr_t result;
	fd = open(path, O_RDONLY | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
	if unlikely(fd < 0)
		return -1;
	result = fpathconf(fd, name);
@@pp_if $has_function(close)@@
	(void)close(fd);
@@pp_endif@@
	return result;
}

@@>> link(2)
@@Create a hard link from `from', leading to `to'
[[cp, userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(linkat))]]
[[crt_dos_variant, export_alias("__link", "__libc_link")]]
[[section(".text.crt{|.dos}.fs.modify")]]
int link([[in]] char const *from, [[in]] char const *to) {
	/* TODO: Header-implementation for `link()' on DOS (using the windows API) */
	return linkat(__AT_FDCWD, from, __AT_FDCWD, to, 0);
}

%[insert:extern(exit)]

@@>> read(2)
@@Read up to `bufsize' bytes from `fd' into `buf'
@@When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
@@available at the time the call was made, and throw E_WOULDBLOCK if no data
@@was available at the time.
@@@return: <= bufsize: The actual amount of read bytes
@@@return: 0         : EOF
[[cp, guard, decl_include("<bits/types.h>")]]
[[dos_only_export_alias("_read")]]
[[export_alias("__read", "__libc_read")]]
[[section(".text.crt{|.dos}.io.read")]]
ssize_t read([[fdread]] $fd_t fd, [[out(return <= bufsize)]] void *buf, size_t bufsize);

@@>> write(2)
@@Write up to `bufsize' bytes from `buf' into `fd'
@@When `fd' has the `O_NONBLOCK' flag set, only write as much  data
@@as possible at the time the call was made, and throw E_WOULDBLOCK
@@if no data could be written at the time.
@@@return: <= bufsize: The actual amount of written bytes
@@@return: 0         : No more data can be written
[[cp, guard, decl_include("<bits/types.h>")]]
[[dos_only_export_alias("_write")]]
[[export_alias("__write", "__libc_write")]]
[[section(".text.crt{|.dos}.io.write")]]
ssize_t write([[fdwrite]] $fd_t fd, [[in(return <= bufsize)]] void const *buf, size_t bufsize);

%#ifdef __USE_KOS
@@>> readall(3)
@@Same  as `read(2)', however  keep on reading until  `read()' indicates EOF (causing
@@`readall()' to immediately return `0') or the entirety of the given buffer has been
@@filled (in which case `bufsize' is returned).
@@If  an error occurs before all data could be read, try to use SEEK_CUR to rewind
@@the file descriptor by the amount of data that had already been loaded. - Errors
@@during this phase are silently ignored and don't cause `errno' to change
[[cp, guard, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(read, lseek) && defined(__SEEK_CUR))]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.io.read")]]
ssize_t readall([[fdread]] $fd_t fd, [[out(bufsize)]] void *buf, size_t bufsize) {
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
				errno_t old_error = __libc_geterrno();
@@pp_endif@@
				/* Try to un-read data that had already been loaded. */
@@pp_if $has_function(lseek64) && __SIZEOF_SIZE_T__ > __SIZEOF_OFF_T__@@
				lseek64(fd, -(off_t)(pos_t)(size_t)result, __SEEK_CUR);
@@pp_else@@
				lseek(fd, -(off_t)(pos_t)(size_t)result, __SEEK_CUR);
@@pp_endif@@
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
[[cp, guard, decl_include("<bits/types.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>", "<bits/crt/format-printer.h>")defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__), export_alias("write_printer")]]
[[requires_function(write)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.io.write")]]
ssize_t writeall([[fdwrite]] $fd_t fd, [[in(bufsize)]] void const *buf, size_t bufsize) {
	ssize_t result, temp;
	result = write(fd, buf, bufsize);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = write(fd,
			             (byte_t *)buf + (size_t)result,
			             bufsize - (size_t)result);
			if (temp <= 0) {
				if (temp < 0)
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
[[cp, decl_include("<bits/crt/format-printer.h>", "<hybrid/typecore.h>")]]
[[no_crt_dos_wrapper, cc(__FORMATPRINTER_CC)]]
[[crt_impl_if($extended_include_prefix("<hybrid/typecore.h>", "<bits/crt/format-printer.h>")!defined(__KERNEL__) && (!defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__))]]
[[if($extended_include_prefix("<hybrid/typecore.h>", "<bits/crt/format-printer.h>")defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__), preferred_alias("writeall")]]
[[requires_function(writeall)]]
[[impl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.io.write")]]
ssize_t write_printer(/*[[fdwrite]] fd_t*/ void *fd,
                      [[in(bufsize)]] char const *__restrict buf,
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

/* >> void *WRITE_PRINTER_ARG([[fdwrite]] fd_t fd);
 * Encode a given `fd' as an argument to `write_printer(3)' */
#define WRITE_PRINTER_ARG(fd) ((void *)(__UINTPTR_TYPE__)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))(fd))
}

%#endif /* __USE_KOS */
%

[[doc_alias("lseek"), ignore, nocrt, alias("lseek", "_lseek", "__lseek", "__libc_lseek")]]
[[decl_include("<bits/types.h>", "<features.h>")]]
$off32_t crt_lseek32([[fdarg]] $fd_t fd, $off32_t offset, __STDC_INT_AS_UINT_T whence);

@@>> lseek(2), lseek64(2)
@@Change the position of the file read/write pointer within a file referred to by `fd'
[[guard, decl_include("<features.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("lseek", "_lseek", "__lseek", "__libc_lseek")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("lseek64", "llseek", "__llseek", "_lseeki64")]]
[[dos_only_export_as("_lseek"), export_as("__lseek", "__libc_lseek")]]
[[requires($has_function(crt_lseek32) || $has_function(lseek64))]]
[[userimpl, section(".text.crt{|.dos}.io.seek")]]
$off_t lseek([[fdarg]] $fd_t fd, $off_t offset, __STDC_INT_AS_UINT_T whence) {
@@pp_if $has_function(crt_lseek32)@@
	return crt_lseek32(fd, ($off32_t)offset, whence);
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
[[impl_include("<bits/os/termios.h>")]]
[[section(".text.crt{|.dos}.io.tty")]]
int isatty([[fdarg]] $fd_t fd) {
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
[[guard, crt_dos_variant, decl_include("<bits/types.h>")]]
[[dos_only_export_alias("_dup2")]]
[[export_alias("__dup2", "__libc_dup2")]]
[[section(".text.crt{|.dos}.io.access")]]
$fd_t dup2([[fdarg]] $fd_t oldfd, [[no_fdarg]] $fd_t newfd);

@@>> dup(2)
@@@return: * : Returns the new handle upon success.
@@Duplicate a file referred to by `fd' and return its duplicated handle number
[[guard, wunused, decl_include("<bits/types.h>")]]
[[dos_only_export_alias("_dup")]]
[[export_alias("__dup", "__libc_dup")]]
[[section(".text.crt{|.dos}.io.access")]]
$fd_t dup([[fdarg]] $fd_t fd);

@@>> close(2)
@@Close a given file descriptor/handle `fd'
[[guard, decl_include("<bits/types.h>")]]
[[dos_only_export_alias("_close")]]
[[export_alias("__close", "__libc_close")]]
/* Even though we're allowed to have it be one, close(2) isn't a
 * cancellation  point on KOS, so `__close_nocancel(3)' can just
 * be an alias for the regular `close(2)' */
[[export_as("__close_nocancel")]]
[[section(".text.crt{|.dos}.io.access")]]
int close([[fdarg]] $fd_t fd);

@@>> access(2)
@@@param: type: Set of `X_OK | W_OK | R_OK'
@@Test for access to the specified file `file', testing for `type'
@@@return: 0 : Access would be granted
@@@return: -1: Access would be denied (s.a. `errno')
[[cp, guard, wunused, crt_dos_variant, decl_include("<features.h>")]]
[[dos_only_export_alias("_access")]]
[[export_alias("__access", "__libc_access")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(faccessat))]]
[[userimpl, section(".text.crt{|.dos}.fs.property")]]
int access([[in]] char const *file, __STDC_INT_AS_UINT_T type) {
	return faccessat(__AT_FDCWD, file, type, 0);
}

@@>> chdir(2)
@@Change the current working directory to `path'
[[cp, guard, crt_dos_variant]]
[[dos_export_alias("_chdir")]]
[[export_alias("__chdir", "__libc_chdir")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(fchdirat))]]
[[userimpl, section(".text.crt{|.dos}.fs.basic_property")]]
/* Hacky work-around for a bug in gnulib:
 * - When configuring a gnulib project, we tell it that:
 *   >> gl_cv_func_getcwd_path_max=yes
 *   However, normally the check for that one is gnulib assuming that
 *   systems  which define PATH_MAX  in <limits.h> implement chdir(2)
 *   such that it refuses to accept paths longer than that.
 * - We can't NOT define PATH_MAX in <limits.h> because other programs
 *   will refuse to compile at all (compiler errors) if that macro  is
 *   missing, so we HAVE to define it.
 * - And because we don't want stupid bloat in 3rd party programs, we
 *   configure  them  with  `gl_cv_func_getcwd_path_max=yes',   which
 *   prevents an unnecessary wrapper around chdir() that would  split
 *   up long paths into smaller components to work around path length
 *   limitations
 * - BUT: Here comes gnulib internal "chdir-long.h" header, which
 *        essentially does:
 *        >> #ifdef PATH_MAX
 *        >> extern int chdir_long(char *dir);
 *        >> #else
 *        >> #define chdir_long(dir) chdir(dir)
 *        >> #endif
 * - To prevent undefined symbol errors, we just export this "chdir_long"
 *   function  as well (but also see comment next to `#undef PATH_MAX' in
 *   our `<limits.h>')
 */
[[export_as("chdir_long")]]
int chdir([[in]] char const *path) {
	return fchdirat(__AT_FDCWD, path, 0);
}


@@>> getcwd(2)
@@Return the path of the current working directory, relative to the filesystem root set by `chdir(2)'
[[cp, guard, decl_include("<hybrid/typecore.h>")]]
[[crt_dos_variant, dos_export_alias("_getcwd")]]
[[section(".text.crt{|.dos}.fs.basic_property")]]
[[export_as("__getcwd")]] /* From Glibc 2.0.4 */
char *getcwd([[out_opt/*(bufsize)*/]] char *buf, size_t bufsize);

@@>> unlink(2)
@@Remove a file, symbolic link, device or FIFO referred to by `file'
[[cp, guard, crt_dos_variant]]
[[dos_export_alias("_unlink")]]
[[export_alias("__unlink", "__libc_unlink")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(unlinkat))]]
[[userimpl, section(".text.crt{|.dos}.fs.modify")]]
int unlink([[in]] char const *file) {
	return unlinkat(__AT_FDCWD, file, 0);
}


@@>> rmdir(2)
@@Remove a directory referred to by `path'
[[cp, guard, crt_dos_variant]]
[[dos_export_alias("_rmdir")]]
[[export_alias("__rmdir", "__libc_rmdir")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && $has_function(unlinkat))]]
[[userimpl, section(".text.crt{|.dos}.fs.modify")]]
int rmdir([[in]] char const *path) {
	return unlinkat(__AT_FDCWD, path, __AT_REMOVEDIR);
}

%#ifdef __USE_GNU
@@>> euidaccess(2)
@@@param: type: Set of `X_OK | W_OK | R_OK'
@@Test for access to the specified file `file', testing for `type', using the effective filesystem ids
[[cp, wunused, decl_include("<features.h>")]]
[[crt_dos_variant, export_alias("eaccess")]]
[[if(defined(__CRT_DOS)), alias("_access")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && defined(__AT_EACCESS) && $has_function(faccessat))]]
[[userimpl, section(".text.crt{|.dos}.fs.property")]]
[[export_as("__euidaccess")]] /* From Glibc 2.0.4 */
int euidaccess([[in]] char const *file, __STDC_INT_AS_UINT_T type) {
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
[[cp, decl_include("<features.h>", "<bits/types.h>")]]
[[crt_dos_variant]]
[[section(".text.crt{|.dos}.fs.property")]]
int faccessat([[dirfd]] $fd_t dfd, [[in]] char const *file,
              __STDC_INT_AS_UINT_T type, $atflag_t flags);


@@>> fchownat(2)
@@Change the ownership of a given `dfd:file' to `group:owner'
[[cp, decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[section(".text.crt{|.dos}.fs.modify")]]
int fchownat([[dirfd]] $fd_t dfd, [[in]] char const *file,
             $uid_t owner, $gid_t group, $atflag_t flags);

@@>> linkat(2)
@@Create a hard link from `fromfd:from', leading to `tofd:to'
[[cp, decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[section(".text.crt{|.dos}.fs.modify")]]
int linkat([[dirfd]] $fd_t fromfd, [[in]] char const *from,
           [[dirfd]] $fd_t tofd, [[in]] char const *to, $atflag_t flags);

@@>> symlinkat(3)
@@Create  a  new  symbolic  link  loaded  with  `link_text'  as link
@@text, at the filesystem location referred to by `tofd:target_path'
[[cp, decl_include("<bits/types.h>")]]
[[userimpl, crt_dos_variant]]
[[requires_function(fsymlinkat)]]
[[section(".text.crt{|.dos}.fs.modify")]]
int symlinkat([[in]] char const *link_text, [[dirfd]] $fd_t tofd,
              [[in]] char const *target_path) {
	return fsymlinkat(link_text, tofd, target_path, 0);
}

@@>> readlinkat(2)
@@Read the text of a symbolic link under `dfd:path' into the provided buffer.
@@WARNING: This  function is badly designed and will neither append a trailing
@@         NUL-character to the buffer, nor will it return the required buffer
@@         size. Instead, it will return the written size, and the caller must
@@         keep on over allocating until the function indicates that it didn't
@@         make use of the buffer in its entirety.
@@When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'.
[[cp, decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[userimpl, requires_function(freadlinkat)]]
[[section(".text.crt{|.dos}.fs.property")]]
ssize_t readlinkat([[dirfd]] $fd_t dfd, [[in]] char const *path,
                   [[out(return <= buflen)]] char *buf, size_t buflen) {
	return freadlinkat(dfd, path, buf, buflen, 0);
}


@@>> unlinkat(2)
@@Remove a file, symbolic link, device or FIFO referred to by `dfd:name'
[[cp, decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[section(".text.crt{|.dos}.fs.modify")]]
int unlinkat([[dirfd]] $fd_t dfd, [[in]] char const *name, $atflag_t flags);


%#ifdef __USE_KOS
@@>> fchdirat(2)
@@Change the current working directory to `dfd:path'
@@@param: flags: Set of `0 | AT_DOSPATH'
[[cp, decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[section(".text.crt{|.dos}.fs.property")]]
int fchdirat([[dirfd]] $fd_t dfd, [[in]] char const *path, $atflag_t flags);

@@>> fsymlinkat(3)
@@Create  a  new  symbolic  link  loaded  with  `link_text'  as link
@@text, at the filesystem location referred to by `tofd:target_path'
@@@param flags: Set of `0 | AT_DOSPATH'
[[cp, decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[section(".text.crt{|.dos}.fs.property")]]
int fsymlinkat([[in]] char const *link_text, [[dirfd]] $fd_t tofd,
               [[in]] char const *target_path, $atflag_t flags);

@@>> freadlinkat(2)
@@Read the text of a symbolic link under `dfd:path' into the provided buffer.
@@@param flags: Set of `AT_DOSPATH | AT_READLINK_REQSIZE'
[[cp, decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[section(".text.crt{|.dos}.fs.property")]]
ssize_t freadlinkat([[dirfd]] $fd_t dfd, [[in]] char const *path,
                    [[out(return <= buflen)]] char *buf, size_t buflen,
                    $atflag_t flags);
%#endif /* __USE_KOS */
%#endif /* __USE_ATFILE */

%
%#ifdef __USE_LARGEFILE64
[[decl_include("<bits/types.h>")]]
[[preferred_off64_variant_of(lseek), doc_alias("lseek")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), preferred_alias("_lseek", "__lseek", "__libc_lseek")]]
[[dos_only_export_alias("_lseeki64")]]
[[export_alias("llseek", "__llseek")]]
[[export_as("__libc_lseek64")]] /* From Glibc 2.3.2 */
[[export_as("__sys_llseek")]]   /* From Glibc 2.0.4 */
[[userimpl, requires_function(crt_lseek32)]]
[[section(".text.crt{|.dos}.io.large.seek")]]
$off64_t lseek64([[fdarg]] $fd_t fd, $off64_t offset, __STDC_INT_AS_UINT_T whence) {
	return crt_lseek32(fd, (__off32_t)offset, whence);
}
%#endif /* __USE_LARGEFILE64 */

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
%[define(DEFINE_PIO_OFFSET =
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
)]

%[insert:prefix(DEFINE_PIO_OFFSET)]

@@>> pread(2), pread64(2)
@@Read data from a file at a specific `offset', rather than the current R/W position
@@@return: <= bufsize: The actual amount of read bytes
[[cp, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pread", "__libc_pread")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pread64", "__pread64")]]
[[export_as("__libc_pread")]]
[[requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(pread64) ||
           ($has_function(lseek, read) && defined(__SEEK_SET) && defined(__SEEK_CUR)))]]
[[userimpl, section(".text.crt{|.dos}.io.read")]]
ssize_t pread([[fdread]] $fd_t fd, [[out(return <= bufsize)]] void *buf,
              size_t bufsize, __PIO_OFFSET offset) {
@@pp_if $has_function(pread64)@@
	return pread64(fd, buf, bufsize, (__PIO_OFFSET64)offset);
@@pp_else@@
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off_t oldpos;
	ssize_t result;
	oldpos = lseek(fd, 0, __SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	if unlikely(lseek(fd, (off_t)offset, __SEEK_SET) < 0)
		return -1;
	result = read(fd, buf, bufsize);
	lseek(fd, oldpos, __SEEK_SET);
	return result;
@@pp_endif@@
}

@@>> pwrite(2), pwrite64(2)
@@Write data to a file at a specific `offset', rather than the current R/W position
@@@return: <= bufsize: The actual amount of written bytes
[[cp, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pwrite", "__libc_pwrite")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pwrite64", "__pwrite64")]]
[[export_as("__libc_pwrite")]]
[[requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(pwrite64) ||
           ($has_function(lseek, write) && defined(__SEEK_SET) && defined(__SEEK_CUR)))]]
[[userimpl, section(".text.crt{|.dos}.io.write")]]
ssize_t pwrite([[fdwrite]] $fd_t fd, [[in(return <= bufsize)]] void const *buf,
               size_t bufsize, __PIO_OFFSET offset) {
@@pp_if $has_function(pwrite64)@@
	return pwrite64(fd, buf, bufsize, (__PIO_OFFSET64)offset);
@@pp_else@@
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off_t oldpos;
	ssize_t result;
	oldpos = lseek(fd, 0, __SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	if unlikely(lseek(fd, (off_t)offset, __SEEK_SET) < 0)
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
[[requires_function(pread)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.io.read")]]
ssize_t preadall([[fdread]] $fd_t fd, [[out(bufsize)]] void *buf,
                 size_t bufsize, __PIO_OFFSET offset) {
	ssize_t result, temp;
	result = pread(fd, buf, bufsize, offset);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on reading */
		for (;;) {
			temp = pread(fd,
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

@@>> pwriteall(3), pwriteall64(3)
@@Same as `writeall(3)', but using `pwrite(2)' instead of `write()'
[[cp, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pwriteall")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("pwriteall64")]]
[[requires_function(pwrite)]]
[[impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.io.write")]]
ssize_t pwriteall([[fdwrite]] $fd_t fd, [[in(bufsize)]] void const *buf,
                  size_t bufsize, __PIO_OFFSET offset) {
	ssize_t result, temp;
	result = pwrite(fd, buf, bufsize, offset);
	if (result > 0 && (size_t)result < bufsize) {
		/* Keep on writing */
		for (;;) {
			temp = pwrite(fd,
			              (byte_t const *)buf + (size_t)result,
			              bufsize - (size_t)result,
			              offset + (size_t)result);
			if (temp <= 0) {
				if (temp < 0)
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



%
%#ifdef __USE_LARGEFILE64

[[cp, ignore, nocrt, alias("pread"), doc_alias("pread")]]
[[decl_include("<bits/types.h>")]]
ssize_t crt_pread32([[fdread]] $fd_t fd, [[out(return <= bufsize)]] void *buf,
                    size_t bufsize, $pos32_t offset);

[[cp, ignore, nocrt, alias("pwrite"), doc_alias("pwrite")]]
[[decl_include("<bits/types.h>")]]
ssize_t crt_pwrite32([[fdwrite]] $fd_t fd, [[in(return <= bufsize)]] void const *buf,
                     size_t bufsize, $pos32_t offset);

[[cp, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET)]]
[[preferred_off64_variant_of(pread), doc_alias("pread")]]
[[export_alias("__pread64")]]
[[export_as("__libc_pread64")]] /* From Glibc 2.3.2 */
[[requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(crt_pread32) ||
           ($has_function(lseek, read) && defined(__SEEK_CUR) && defined(__SEEK_SET)))]]
[[userimpl, section(".text.crt{|.dos}.io.large.read")]]
ssize_t pread64([[fdread]] $fd_t fd, [[out(return <= bufsize)]] void *buf,
                size_t bufsize, __PIO_OFFSET64 offset) {
@@pp_if $has_function(crt_pread32)@@
	return crt_pread32(fd, buf, bufsize, (pos32_t)offset);
@@pp_elif $has_function(lseek64)@@
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off64_t oldpos;
	ssize_t result;
	oldpos = lseek64(fd, 0, __SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	if unlikely(lseek64(fd, (off64_t)offset, __SEEK_SET) < 0)
		return -1;
	result = read(fd, buf, bufsize);
	lseek64(fd, oldpos, __SEEK_SET);
	return result;
@@pp_else@@
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off32_t oldpos;
	ssize_t result;
	oldpos = crt_lseek32(fd, 0, __SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	if unlikely(crt_lseek32(fd, (off32_t)offset, __SEEK_SET) < 0)
		return -1;
	result = read(fd, buf, bufsize);
	crt_lseek32(fd, oldpos, __SEEK_SET);
	return result;
@@pp_endif@@
}

[[cp, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET)]]
[[preferred_off64_variant_of(pwrite), doc_alias("pwrite")]]
[[export_alias("__pwrite64")]]
[[export_as("__libc_pwrite64")]] /* From Glibc 2.3.2 */
[[requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(crt_pwrite32) ||
           ($has_function(lseek, write) && defined(__SEEK_CUR) && defined(__SEEK_SET)))]]
[[userimpl, section(".text.crt{|.dos}.io.large.write")]]
ssize_t pwrite64([[fdwrite]] $fd_t fd, [[in(return <= bufsize)]] void const *buf,
                 size_t bufsize, __PIO_OFFSET64 offset) {
@@pp_if $has_function(crt_pwrite32)@@
	return crt_pwrite32(fd, buf, bufsize, (pos32_t)offset);
@@pp_elif $has_function(lseek64)@@
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off64_t oldpos;
	ssize_t result;
	oldpos = lseek64(fd, 0, SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	if unlikely(lseek64(fd, (off64_t)offset, SEEK_SET) < 0)
		return -1;
	result = write(fd, buf, bufsize);
	lseek64(fd, oldpos, SEEK_SET);
	return result;
@@pp_else@@
	/* It may not be quick, and it may not be SMP-safe, but it'll still do the job! */
	off32_t oldpos;
	ssize_t result;
	oldpos = crt_lseek32(fd, 0, SEEK_CUR);
	if unlikely(oldpos < 0)
		return -1;
	if unlikely(crt_lseek32(fd, (off32_t)offset, SEEK_SET) < 0)
		return -1;
	result = write(fd, buf, bufsize);
	crt_lseek32(fd, oldpos, SEEK_SET);
	return result;
@@pp_endif@@
}

%
%#ifdef __USE_KOS
[[cp, preferred_off64_variant_of(preadall)]]
[[decl_include("<bits/types.h>"), doc_alias("preadall")]]
[[requires_function(pread64)]]
[[section(".text.crt{|.dos}.io.large.read")]]
ssize_t preadall64([[fdread]] $fd_t fd, [[out(bufsize)]] void *buf,
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

[[cp, preferred_off64_variant_of(pwriteall)]]
[[decl_include("<bits/types.h>"), doc_alias("pwriteall")]]
[[requires_function(pwrite64)]]
[[section(".text.crt{|.dos}.io.large.write")]]
ssize_t pwriteall64([[fdwrite]] $fd_t fd, [[in(bufsize)]] void const *buf,
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
[[decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[requires_function(dup2)]]
[[userimpl, section(".text.crt{|.dos}.io.access")]]
$fd_t dup3([[fdarg]] $fd_t oldfd, [[no_fdarg]] $fd_t newfd, $oflag_t flags) {
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
[[decl_include("<bits/types.h>")]]
[[requires_function(pipe)]]
[[userimpl, section(".text.crt{|.dos}.io.access")]]
int pipe2([[out]] $fd_t pipedes[2], $oflag_t flags) {
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
__CDECLARE(,int,__NOTHROW_NCX,_get_environ,(char ***__p_environ),())
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
[[cp, wunused, ATTR_MALLOC]]
[[crt_dos_variant]]
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
int syncfs([[fdwrite]] $fd_t fd) {
	COMPILER_IMPURE();
	(void)fd;
	/* NO-OP */
	return 0;
}

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
[[section(".text.crt{|.dos}.sched.user")]]
[[export_as("__group_member")]] /* From Glibc 2.0.4 */
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
[[section(".text.crt{|.dos}.sched.user")]]
int getresuid([[out_opt]] $uid_t *ruid,
              [[out_opt]] $uid_t *euid,
              [[out_opt]] $uid_t *suid);

@@>> getresgid(2)
@@Get the real, effective, and saved GID of the calling thread.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.sched.user")]]
int getresgid([[out_opt]] $gid_t *rgid,
              [[out_opt]] $gid_t *egid,
              [[out_opt]] $gid_t *sgid);

@@>> setresuid(2)
@@Set the real, effective, and saved UID of the calling thread.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.sched.user")]]
int setresuid($uid_t ruid, $uid_t euid, $uid_t suid);

@@>> setresgid(2)
@@Set the real, effective, and saved GID of the calling thread.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.sched.user")]]
int setresgid($gid_t rgid, $gid_t egid, $gid_t sgid);
%#endif /* __USE_GNU */

%#if (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8)) || defined(__USE_MISC)

@@Hidden function exported by DOS that allows for millisecond precision
[[cp, ignore, nocrt, alias("__crtSleep", "delay")]]
[[decl_include("<hybrid/typecore.h>")]]
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
[[cp, deprecated("Use getcwd()")]]
[[crt_dos_variant]]
[[requires_function(getcwd)]]
[[impl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.fs.basic_property")]]
char *getwd([[out]] char *buf) {
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
[[returns_twice, wunused, decl_include("<bits/types.h>")]]
[[guard, export_alias("__vfork", "__libc_vfork")]]
[[section(".text.crt{|.dos}.sched.access")]]
$pid_t vfork();
%#endif /* (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) || __USE_MISC */

@@>> fchown(2)
@@Change the ownership of a given `fd' to `group:owner'
[[cp, decl_include("<bits/types.h>")]]
[[export_alias("__fchown", "__libc_fchown")]]
[[section(".text.crt{|.dos}.fs.modify")]]
int fchown([[fdarg]] $fd_t fd, $uid_t owner, $gid_t group);

@@>> fchdir(2)
@@Change the current working directory to `path'
[[cp, decl_include("<bits/types.h>")]]
[[export_alias("__fchdir", "__libc_fchdir")]]
[[section(".text.crt{|.dos}.fs.basic_property")]]
int fchdir([[fdarg]] $fd_t fd);

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
[[crt_dos_variant]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && $has_function(fchownat))]]
[[userimpl, section(".text.crt{|.dos}.fs.modify")]]
[[export_as("__lchown")]] /* From Glibc 2.0.4 */
int lchown([[in]] char const *file, $uid_t owner, $gid_t group) {
	return fchownat(__AT_FDCWD, file, owner, group, __AT_SYMLINK_NOFOLLOW);
}


%
%{
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
}

[[ignore, nocrt, decl_include("<bits/types.h>"), doc_alias("truncate")]]
[[alias("truncate", "__truncate", "__libc_truncate")]]
int crt_truncate32([[in]] char const *file, $pos32_t length);


@@>> truncate(2), truncate64(2)
@@Truncate the given file `file' to a length of `length'
[[crt_dos_variant, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("truncate", "__truncate", "__libc_truncate")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("truncate64")]]
[[export_as("__truncate", "__libc_truncate")]]
[[requires_include("<asm/os/oflags.h>")]]
[[requires($has_function(truncate64) || $has_function(crt_truncate32) ||
           ($has_function(open, ftruncate) && defined(__O_WRONLY)))]]
[[userimpl, section(".text.crt{|.dos}.fs.modify")]]
int truncate([[in]] char const *file, __PIO_OFFSET length) {
@@pp_if $has_function(crt_truncate32)@@
	return crt_truncate32(file, (pos32_t)length);
@@pp_elif $has_function(truncate64)@@
	return truncate64(file, (__PIO_OFFSET64)length);
@@pp_else@@
	int result;
	fd_t fd;
	fd = open(file, O_WRONLY | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
	if unlikely(fd < 0)
		return -1;
	result = ftruncate(fd, length);
@@pp_if $has_function(close)@@
	(void)close(fd);
@@pp_endif@@
	return result;
@@pp_endif@@
}

%
%#ifdef __USE_LARGEFILE64
[[decl_prefix(DEFINE_PIO_OFFSET), decl_include("<bits/types.h>")]]
[[crt_dos_variant, preferred_off64_variant_of(truncate), doc_alias("truncate")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), preferred_alias("__truncate", "__libc_truncate")]]
[[requires($has_function(crt_truncate32) ||
           $has_function(open64, ftruncate64))]]
[[impl_include("<features.h>")]]
[[userimpl, section(".text.crt{|.dos}.fs.modify")]]
int truncate64([[in]] char const *file, __PIO_OFFSET64 length) {
@@pp_if $has_function(crt_truncate32)@@
	return crt_truncate32(file, (__PIO_OFFSET)length);
@@pp_else@@
	int result;
	fd_t fd;
	fd = open64(file, 1); /* O_WRONLY */
	if unlikely(fd < 0)
		return -1;
	result = ftruncate64(fd, length);
@@pp_if $has_function(close)@@
	(void)close(fd);
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
int fexecve([[fdread]] $fd_t execfd, [[in]] __TARGV, [[in]] __TENVP) {
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
int crt_fexecve([[fdread]] $fd_t fd, [[in]] __TARGV, [[in]] __TENVP);

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

@@>> confstr(3)
@@Retrieve a system configuration string specified by `name'
@@@param: name:   One of `_CS_*' from <asm/crt/confname.h>
@@@param: buf:    Target buffer
@@@param: buflen: Available buffer size (including a trailing \0-character)
@@@return: * :    Required buffer size (including a trailing \0-character)
@@@return: 1 :    Empty configuration string.
@@@return: 0 :    [errno=EINVAL] Bad configuration `name'.
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.system.configuration")]]
size_t confstr(__STDC_INT_AS_UINT_T name, [[out(? <= buflen)]] char *buf, size_t buflen);

%{

/* >> optarg(3)
 * Set to the argument of the option returned by `getopt(3)' (and friends).
 * When returning an option that doesn't take an argument, `optarg' is  set
 * to `NULL'.
 *
 * Pre-initialized to `NULL' */
#ifndef optarg
#ifdef __LOCAL_optarg
#define optarg __LOCAL_optarg
#elif defined(__CRT_HAVE_optarg)
__CSDECLARE(,char *,optarg)
#define optarg optarg
#endif /* ... */
#endif /* !optarg */

/* >> optind(3)
 * Index of the next `argv'-element that `getopt(3)' (and friends) should parse.
 * In order for parsing to  start over, this should be  set to `1'. In order  to
 * fully re-initialize the getopt-parser, it should be set to `0' (in which case
 * libc will re-load flags from `optstring[0]', and `$POSIXLY_CORRECT').
 *
 * Once all arguments have been processed, `getopt(3)' returns `-1', and `optind'
 * is set to the value of the first non-argument argv-element (when all  elements
 * of `argv' are arguments, it is set to `argc')
 *
 * Pre-initialized to `1' */
#ifndef optind
#ifdef __LOCAL_optind
#define optind __LOCAL_optind
#elif defined(__CRT_HAVE_optind)
__CSDECLARE(,int,optind)
#define optind optind
#endif /* ... */
#endif /* !optind */

/* >> opterr(3)
 * When non-zero, `getopt(3)' will print error messages to `stderr', unless the
 * first character of `optstring' is `:'.  Setting this global variable to  `0'
 * will suppress error messages being  printed, allowing the application to  do
 * its own error-handling without libc doing anything extra.
 *
 * Pre-initialized to `1' */
#ifndef opterr
#ifdef __LOCAL_opterr
#define opterr __LOCAL_opterr
#elif defined(__CRT_HAVE_opterr)
__CSDECLARE(,int,opterr)
#define opterr opterr
#endif /* ... */
#endif /* !opterr */

/* >> optopt(3)
 * Filled in by `getopt(3)' (and friends) with the character-code of a malformed
 * option when one is encountered (this is done alongside an error being printed
 * to `stderr' (but see `opterr'), and `?' being returned by `getopt(3)').
 *
 * In the case of long options (s.a. `getopt_long(3)'), a malformed long option
 * results in that option's `struct option::val' being written to this  global.
 *
 * Pre-initialized to `(unsigned char)'?'' */
#ifndef optopt
#ifdef __LOCAL_optopt
#define optopt __LOCAL_optopt
#elif defined(__CRT_HAVE_optopt)
__CSDECLARE(,int,optopt)
#define optopt optopt
#endif /* ... */
#endif /* !optopt */

}
%

[[guard, wunused, no_crt_impl]]
[[crt_name("getopt"), exposed_name("getopt"), doc_alias("getopt")]]
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
	COMPILER_IMPURE();
	/* NO-OP */
}

@@>> setpgrp(3)
@@Move the calling process into its own process group.
@@Equivalent to `setpgid(0, 0)'
[[requires_function(setpgid)]]
[[section(".text.crt{|.dos}.sched.process")]]
int setpgrp() {
	return setpgid(0, 0);
}

@@>> setreuid(2)
@@Set the real and effective UID of the calling thread.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
[[export_alias("__setreuid", "__libc_setreuid")]]
[[requires_function(setresuid)]]
[[userimpl, section(".text.crt{|.dos}.sched.user")]]
int setreuid($uid_t ruid, $uid_t euid) {
	return setresuid(ruid, euid, (uid_t)-1);
}

@@>> setregid(2)
@@Set the real and effective GID of the calling thread.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
[[export_alias("__setregid", "__libc_setregid")]]
[[requires_function(setresgid)]]
[[userimpl, section(".text.crt{|.dos}.sched.user")]]
int setregid($gid_t rgid, $gid_t egid) {
	return setresgid(rgid, egid, (gid_t)-1);
}

@@>> gethostid(3)
@@Get the machine's "host id" (the contents of a 4-byte file "/etc/hostid")
[[wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_include("<paths.h>")]]
[[requires($has_function(open, readall) && defined(_PATH_HOSTID))]]
[[impl_include("<paths.h>", "<bits/types.h>", "<asm/os/oflags.h>")]]
[[section(".text.crt{|.dos}.system.configuration")]]
$longptr_t gethostid() {
@@pp_ifdef O_RDONLY@@
	fd_t fd = open(_PATH_HOSTID, O_RDONLY | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
@@pp_else@@
	fd_t fd = open(_PATH_HOSTID, __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
@@pp_endif@@
	if (fd >= 0) {
		uint32_t id32;
		ssize_t count = readall(fd, &id32, 4);
@@pp_if $has_function(close)@@
		(void)close(fd);
@@pp_endif@@
		if (count == 4)
			return (longptr_t)(ulongptr_t)id32;
	}
	/* XXX: Glibc also tries to use the host's IP address here... */
	return 0;
}

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

%(auto_header){
#include <asm/pagesize.h>
#ifdef __ARCH_PAGESIZE
#define libc_getpagesize() __ARCH_PAGESIZE
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
[[requires_function(setreuid)]]
[[section(".text.crt{|.dos}.sched.user")]]
int seteuid($uid_t euid) {
	return setreuid((uid_t)-1, euid);
}

@@>> setegid(2)
@@Set the effective group ID of the calling process
@@@return: 0 : Success
@@@return: -1: [errno=EINVAL] : The given `egid' is invalid
@@@return: -1: [errno=EPERM]  : The current user is not privileged
[[decl_include("<bits/types.h>")]]
[[requires_function(setregid)]]
[[section(".text.crt{|.dos}.sched.user")]]
int setegid($gid_t egid) {
	return setregid((gid_t)-1, egid);
}

%#endif /* __USE_XOPEN2K */

%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_UNIX98))

@@>> ttyslot(3)
@@Returns the (1-based) index into  ttys returned by `getttyent(3)'  of
@@the terminal currently associated with the caller (~ala `ttyname(3)')
@@On  error, or if caller's terminal isn't listed by `getttyent(3)', we
@@instead return `0'
[[wunused]]
[[requires_function(ttyname, setttyent, getttyent)]]
[[impl_include("<libc/errno.h>", "<bits/types.h>")]]
[[impl_include("<asm/os/stdio.h>", "<bits/crt/db/ttyent.h>")]]
[[section(".text.crt{|.dos}.compat.glibc")]]
int ttyslot() {
	fd_t fd;
	__PRIVATE_FOREACH_STDFILENO(fd) {
		char const *tnam;
		int result;
		@struct ttyent@ *tty;
		if ((tnam = ttyname(fd)) == NULL)
			continue;
		tnam = strrchrnul(tnam, '/') + 1;
		setttyent();
		for (result = 1; (tty = getttyent()) != NULL; ++result) {
			if (strcmp(tty->@ty_name@, tnam) == 0) {
@@pp_if $has_function(endttyent)@@
				endttyent();
@@pp_endif@@
				return result;
			}
		}
@@pp_if $has_function(endttyent)@@
		endttyent();
@@pp_endif@@
	}
	return 0;
}

%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_UNIX98) */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)

@@>> symlink(3)
@@Create  a new  symbolic link  loaded with  `link_text' as link
@@text, at the filesystem location referred to by `target_path'.
@@Same as `symlinkat(link_text, AT_FDCWD, target_path)'
[[cp, export_alias("__symlink", "__libc_symlink")]]
[[crt_dos_variant]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(symlinkat))]]
[[userimpl, section(".text.crt{|.dos}.fs.modify")]]
int symlink([[in]] char const *link_text,
            [[in]] char const *target_path) {
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
[[cp, decl_include("<hybrid/typecore.h>")]]
[[crt_dos_variant]]
[[requires_include("<asm/os/fcntl.h>"), export_alias("__readlink", "__libc_readlink")]]
[[requires(defined(__AT_FDCWD) && $has_function(readlinkat))]]
[[userimpl, section(".text.crt{|.dos}.fs.property")]]
ssize_t readlink([[in]] char const *path,
                 [[out(return <= buflen)]] char *buf,
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
int getlogin_r([[out(? <= name_len)]] char *name, size_t name_len) {
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
[[requires_include("<bits/os/utsname.h>")]]
[[requires($has_function(uname) && defined(__OFFSET_UTSNAME_NODENAME) &&
           defined(@_UTSNAME_NODENAME_LENGTH@) && @_UTSNAME_NODENAME_LENGTH@)]]
[[impl_include("<bits/os/utsname.h>", "<libc/errno.h>", "<bits/types.h>")]]
[[section(".text.crt{|.dos}.system.configuration")]]
int gethostname([[out(? <= buflen)]] char *name, size_t buflen) {
	@struct utsname@ uts;
	int result = uname(&uts);
	if (result == 0) {
		size_t len = strnlen(uts.@nodename@, @_UTSNAME_NODENAME_LENGTH@);
		if (buflen <= len) {
			/* EINVAL For gethostname() under libc: name is NULL or name is longer than len bytes. */
@@pp_ifdef EINVAL@@
			return libc_seterrno(EINVAL);
@@pp_else@@
			return libc_seterrno(1);
@@pp_endif@@
		}
		memcpy(name, uts.@nodename@, len * sizeof(char));
		name[len] = '\0';
	}
	return result;
}
%#endif /* __USE_UNIX98 || __USE_XOPEN2K */

%
%#ifdef __USE_MISC
@@>> setlogin(3)
[[section(".text.crt{|.dos}.io.tty")]]
int setlogin([[in]] char const *name);

@@>> sethostname(2)
@@Set the name of the hosting machine
[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__sethostname", "__libc_sethostname")]]
[[section(".text.crt{|.dos}.system.configuration")]]
int sethostname([[in(len)]] char const *name, size_t len);

@@>> sethostid(3)
@@Set the machine's "host id" (the contents of a 4-byte file "/etc/hostid")
[[decl_include("<hybrid/typecore.h>")]]
[[requires_include("<asm/os/oflags.h>", "<paths.h>")]]
[[requires($has_function(open, writeall) && defined(__O_WRONLY) &&
           defined(__O_CREAT) && defined(__O_TRUNC) && defined(_PATH_HOSTID))]]
[[impl_include("<paths.h>", "<asm/os/oflags.h>")]]
[[impl_include("<libc/errno.h>", "<bits/types.h>")]]
[[section(".text.crt{|.dos}.system.configuration")]]
int sethostid($longptr_t id) {
	fd_t fd;
	ssize_t count;
	uint32_t id32;

	/* Ensure that `id' fits into 4 bytes */
@@pp_if __SIZEOF_POINTER__ > 4@@
	if (id & ~UINT32_C(0xffffffff)) {
@@pp_ifdef EOVERFLOW@@
		return libc_seterrno(EOVERFLOW);
@@pp_else@@
		return libc_seterrno(1);
@@pp_endif@@
	}
@@pp_endif@@

	/* Try to open the hostid file for writing */
	fd = open(_PATH_HOSTID, O_WRONLY | O_CREAT | O_TRUNC | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK, 0644);
	if (fd < 0) {
		/* Try to lazily create the containing directory if it's missing. */
@@pp_if $has_function(mkdir) && defined(libc_geterrno_or) && defined(ENOTDIR)@@
		if (libc_geterrno() == ENOTDIR) {
			/* Check if /etc was already created. */
@@pp_ifndef EEXIST@@
			mkdir(_PATH_HOSTID_CONTAINING_DIRECTORY, 0755);
@@pp_else@@
			if (mkdir(_PATH_HOSTID_CONTAINING_DIRECTORY, 0755) == 0 ||
			    libc_geterrno() == EEXIST)
@@pp_endif@@
			{
				fd = open(_PATH_HOSTID, O_WRONLY | O_CREAT | O_TRUNC | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK, 0644);
				if (fd >= 0)
					goto got_fd;
#define WANT_got_fd
			}
		}
@@pp_endif@@
		return fd;
	}
#ifdef WANT_got_fd
#undef WANT_got_fd
got_fd:
#endif /* WANT_got_fd */
	id32  = (uint32_t)(ulongptr_t)id;
	count = writeall(fd, &id32, 4);
@@pp_if $has_function(close)@@
	(void)close(fd);
@@pp_endif@@
	if (count != 4) {
@@pp_ifdef ENOSPC@@
		if (count >= 0)
			libc_seterrno(ENOSPC); /* ??? */
@@pp_endif@@
		return -1;
	}
	return 0;
}

@@>> getdomainname(3)
@@Return the name assigned to the hosting machine's domain, as set by `setdomainname(2)'
[[decl_include("<hybrid/typecore.h>")]]
[[requires_include("<bits/os/utsname.h>")]]
[[requires($has_function(uname) && defined(__OFFSET_UTSNAME_DOMAINNAME) &&
           defined(@_UTSNAME_DOMAIN_LENGTH@) && @_UTSNAME_DOMAIN_LENGTH@)]]
[[impl_include("<bits/os/utsname.h>", "<libc/errno.h>", "<bits/types.h>")]]
[[section(".text.crt{|.dos}.system.configuration")]]
int getdomainname([[out(? <= buflen)]] char *name, size_t buflen) {
@@pp_ifndef __PRIVATE_UTSNAME_DOMAINNAME@@
#define __PRIVATE_UTSNAME_DOMAINNAME @domainname@
@@pp_endif@@
	@struct utsname@ uts;
	int result = uname(&uts);
	if (result == 0) {
		size_t len = strnlen(uts.__PRIVATE_UTSNAME_DOMAINNAME, @_UTSNAME_DOMAIN_LENGTH@);
		if (buflen <= len) {
			/* EINVAL For getdomainname() under libc: name is NULL or name is longer than len bytes. */
@@pp_ifdef EINVAL@@
			return libc_seterrno(EINVAL);
@@pp_else@@
			return libc_seterrno(1);
@@pp_endif@@
		}
		memcpy(name, uts.__PRIVATE_UTSNAME_DOMAINNAME, len * sizeof(char));
		name[len] = '\0';
	}
	return result;
}


@@>> setdomainname(2)
@@Set the name of the hosting machine's domain
[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__setdomainname", "__libc_setdomainname")]]
[[section(".text.crt{|.dos}.system.configuration")]]
int setdomainname([[in(len)]] char const *name, size_t len);

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

@@>> daemon_setup(3)
@@Do the common setup required by `daemon(3)' and `daemonfd(3)'
[[cp, static]]
[[requires_function(fork, _Exit, setsid)]]
[[impl_include("<bits/os/sigaction.h>", "<asm/os/signal.h>")]]
[[section(".text.crt{|.dos}.system.utility")]]
int daemon_setup() {
	int result;
@@pp_if $has_function(sigaction) && defined(__SIG_IGN) && defined(__SIGHUP)@@
	int has_old_sa;
	@struct sigaction@ new_sa, old_sa;
	/* To quote POSIX (on `_Exit(2)'):
	 * """
	 * If the process  is a controlling  process, the  SIGHUP
	 * signal shall be sent to each process in the foreground
	 * process group  of the  controlling terminal  belonging
	 * to the calling process.
	 * """
	 * In other words: if our process is both the controlling
	 * process, as  well as  part of  the foreground  process
	 * group,  meaning that  our child  will also  be of said
	 * group, then it would be sent a SIGHUP which might even
	 * kill it. To prevent this from happening, ignore SIGHUP
	 * while we pass  kill ourselves and  spawn a new  child! */
	sigemptyset(&new_sa.@sa_mask@);
	new_sa.@sa_handler@ = (__sighandler_t)__SIG_IGN;
	new_sa.@sa_flags@   = 0;
	has_old_sa = sigaction(__SIGHUP, &new_sa, &old_sa);
@@pp_endif@@
	{
		pid_t cpid = fork();
		if unlikely(cpid < 0)
			return cpid;
		if (cpid != 0)
			_Exit(0); /* The parent process dies. */
	}
	result = setsid();
@@pp_if $has_function(sigaction) && defined(__SIG_IGN) && defined(__SIGHUP)@@
	if (has_old_sa == 0)
		sigaction(__SIGHUP, &old_sa, NULL);
@@pp_endif@@
	return result;
}

@@>> daemon(3), daemonfd(3)
[[cp, guard]]
[[requires_function(daemon_setup, chdir, open, dup2)]]
[[impl_include("<paths.h>")]]
[[section(".text.crt{|.dos}.system.utility")]]
int daemon(int nochdir, int noclose) {
	int error = daemon_setup();
	if likely(error == 0) {
		if (!nochdir)
			(void)chdir("/");
		if (!noclose) {
			fd_t i, nul = open(_PATH_DEVNULL, O_RDWR | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
			if unlikely(nul < 0)
				return nul;
			/* NOTE: Glibc does an additional check to ensure that `nul'  really
			 *       is a character-device with the  correct dev_t. We could  do
			 *       that as well, however I'd consider a system where /dev/null
			 *       isn't actually /dev/null to  already be broken... (and  the
			 *       check only adds unnecessary overhead if you ask me) */
			for (i = 0; i < 3; ++i) {
				if (nul != i)
					(void)dup2(nul, i);
			}
@@pp_if $has_function(close)@@
			if (nul >= 3)
				(void)close(nul);
@@pp_endif@@
		}
	}
	return error;
}


@@>> revoke(3)
[[cp]]
[[section(".text.crt{|.dos}.fs.modify")]]
int revoke([[in]] char const *file);

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
[[cp]]
[[crt_dos_variant]]
[[export_alias("__chroot", "__libc_chroot")]]
[[section(".text.crt{|.dos}.fs.utility")]]
int chroot([[in]] char const *__restrict path);

@@>> getpass(3), getpassphrase(3)
[[guard, cp, wunused]]
[[export_alias("getpassphrase")]]
[[requires_function(getpass_r)]]
[[impl_include("<asm/crt/readpassphrase.h>")]]
[[section(".text.crt{|.dos}.io.tty")]]
char *getpass([[nullable]] char const *__restrict prompt) {
@@pp_if $has_function(malloc)@@
	@@static char *getpass_buf = NULL; [fini: free(getpass_buf)]@@
	if (!getpass_buf) {
		/* Lazily allocate buffer. */
		getpass_buf = (char *)malloc(257 * sizeof(char)); /* `getpassphrase()' requires passwords at least this long! */
//		getpass_buf = (char *)malloc(129 * sizeof(char)); /* 129 == _PASSWORD_LEN + 1 */
		if unlikely(!getpass_buf)
			return NULL;
	}
@@pp_else@@
	static char getpass_buf[257]; /* `getpassphrase()' requires passwords at least this long! */
//	static char getpass_buf[129]; /* 129 == _PASSWORD_LEN + 1 */
@@pp_endif@@
	return getpass_r(prompt, getpass_buf, 257);
}
%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

%
%#if defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)

[[ignore, nocrt, doc_alias("ftruncate"), decl_include("<bits/types.h>")]]
[[alias("ftruncate", "__ftruncate", "__libc_ftruncate", "_chsize", "chsize")]]
int crt_ftruncate32([[fdwrite]] $fd_t fd, $pos32_t length);

@@>> ftruncate(2), ftruncate64(2)
@@Truncate the given file `fd' to a length of `length'
[[decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("ftruncate", "__ftruncate", "__libc_ftruncate", "_chsize", "chsize")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("ftruncate64", "_chsize_s")]]
[[dos_only_export_as("_chsize"), export_as("__ftruncate", "__libc_ftruncate", "chsize")]]
[[requires($has_function(crt_ftruncate32) || $has_function(ftruncate64))]]
[[userimpl, section(".text.crt{|.dos}.io.write")]]
int ftruncate([[fdwrite]] $fd_t fd, __PIO_OFFSET length) {
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
int ftruncate64([[fdwrite]] $fd_t fd, __PIO_OFFSET64 length) {
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

[[decl_include("<hybrid/typecore.h>")]]
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
[[export_as("__libc_fsync")]] /* From Glibc 2.3.2 */
[[userimpl, section(".text.crt{|.dos}.io.sync")]]
int fdatasync([[fdwrite]] $fd_t fd) {
	COMPILER_IMPURE();
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
void swab([[in(n_bytes)]] void const *__restrict from,
          [[out(n_bytes)]] void *__restrict to,
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
	static char ctermid_buf[4] = {0};
	if (s == NULL)
		s = ctermid_buf;
	return strcpy(s, "CON");
@@pp_else@@
	@@static char ctermid_buf[9] = {0}@@
	if (s == NULL)
		s = ctermid_buf;
	return strcpy(s, "/dev/tty");
@@pp_endif@@
}

@@>> cuserid(3)
@@Return the name of the current user (`$LOGNAME' or  `getpwuid(geteuid())'),
@@storing that name in `s'. When `s' is NULL, a static buffer is used instead
@@When given, `s' must be a buffer of at least `L_cuserid' bytes.
@@
@@If the actual username is  longer than this, it  may be truncated, and  programs
@@that wish to support longer usernames should make use of `getlogin_r()' instead.
@@s.a. `getlogin()' and `getlogin_r()'
[[guard, requires_function(getlogin_r)]]
[[impl_include("<asm/crt/stdio.h>")]] /* __L_cuserid */
[[section(".text.crt{|.dos}.io.tty")]]
char *cuserid([[out_opt]] char *s) {
@@pp_if $has_function(realloc)@@
@@pp_ifdef __L_cuserid@@
#define LOCAL___L_cuserid __L_cuserid
@@pp_else@@
#define LOCAL___L_cuserid 9
@@pp_endif@@
	/* Buffer is typed as `void *' so it can be re-used for `wcuserid(3)' */
	@@static void *cuserid_buf; [fini: free(cuserid_buf)]@@
	errno_t error;
	size_t bufsize;

	/* Special case for when the caller is providing the buffer. */
	if (s != NULL)
		return getlogin_r(s, LOCAL___L_cuserid) ? NULL : s;

	/* Use the TLS buffer. */
@@pp_if $has_function(malloc_usable_size)@@
	bufsize = malloc_usable_size(cuserid_buf) / sizeof(char);
@@pp_else@@
	bufsize = cuserid_buf ? LOCAL___L_cuserid : 0;
@@pp_endif@@
	if (bufsize < LOCAL___L_cuserid) {
		void *newbuf;
		bufsize = LOCAL___L_cuserid;
		newbuf  = realloc(cuserid_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		cuserid_buf = newbuf;
	}
@@pp_ifdef ERANGE@@
again:
@@pp_endif@@
	error = getlogin_r((char *)cuserid_buf, bufsize);
	if likely(error == 0) {
		/* Trim unused memory (if a certain threshold is exceeded) */
		size_t retlen = strlen((char *)cuserid_buf) + 1;
		if (retlen < LOCAL___L_cuserid)
			retlen = LOCAL___L_cuserid; /* Retain minimal buffer size */
		if likely((retlen + 32) < bufsize) {
			void *retbuf = realloc(cuserid_buf, retlen * sizeof(char));
			if likely(retbuf)
				cuserid_buf = retbuf;
		}
		return (char *)cuserid_buf;
	}
@@pp_ifdef ERANGE@@
	if (error == ERANGE && bufsize < 1024) {
		void *newbuf;
		bufsize *= 2;
		newbuf = realloc(cuserid_buf, bufsize * sizeof(char));
		if unlikely(!newbuf)
			goto err;
		cuserid_buf = newbuf;
		goto again;
	}
@@pp_endif@@
@@pp_if $has_function(free)@@
	free(cuserid_buf);
	cuserid_buf = NULL;
@@pp_endif@@
err:
	return NULL;
#undef LOCAL___L_cuserid
@@pp_else@@
@@pp_ifdef __L_cuserid@@
	static char cuserid_buffer[__L_cuserid];
@@pp_else@@
	static char cuserid_buffer[9];
@@pp_endif@@
	if (s == NULL)
		s = cuserid_buffer;
	return getlogin_r(s, sizeof(cuserid_buffer)) ? NULL : s;
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
@@than CR/LF as indicators to stop reading text)
@@Which of the 2 functions should be used is a matter of taste,
@@but  personally, I prefer  this one over `readpassphrase(3)'.
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
[[section(".text.crt{|.dos}.bsd")]]
char *getpassfd([[in_opt]] char const *prompt,
                [[out_opt/*(buflen)*/]] char *buf, size_t buflen,
                [[in_opt]] $fd_t fds[3],
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
		                      __PRIVATE_GETPASSFD_O_RDWR |
		                      __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK |
		                      (timeout_in_seconds != 0 ? __PRIVATE_GETPASSFD_O_NONBLOCK : 0));
#else /* __PRIVATE_GETPASSFD_O_NONBLOCK != 0 */
		default_fds[2] = open(__PRIVATE_GETPASSFD_PATH_TTY,
		                      __PRIVATE_GETPASSFD_O_RDWR |
		                      __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
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
	if (bcmp(&old_ios, &new_ios, sizeof(struct termios)) != 0) {
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
		(void)close(default_fds[0]);
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
[[cp, wunused, decl_include("<hybrid/typecore.h>")]]
[[requires($has_function(getpassfd) || $has_function(readpassphrase))]]
[[impl_include("<asm/crt/getpassfd.h>")]]
[[impl_include("<asm/crt/readpassphrase.h>")]]
[[section(".text.crt{|.dos}.bsd")]]
char *getpass_r([[in_opt]] char const *prompt, [[out_opt/*(? <= bufsize)*/]] char *buf, size_t bufsize) {
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
[[section(".text.crt{|.dos}.bsd")]]
void *setmode([[in]] char const *mode_str); /* TODO: Implement here! */

[[wunused, doc_alias("setmode"), decl_include("<bits/types.h>")]]
[[section(".text.crt{|.dos}.bsd")]]
$mode_t getmode([[in]] void const *bbox, $mode_t mode); /* TODO: Implement here! */

@@>> getpeereid(3)
@@Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)'
[[guard, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/socket.h>")]]
[[requires($has_function(getsockopt) &&
           (defined(__SOL_SOCKET) && defined(__SO_PEERCRED)))]]
[[impl_include("<bits/os/ucred.h>", "<libc/errno.h>")]]
[[section(".text.crt{|.dos}.bsd")]]
int getpeereid([[fdarg]] $fd_t sockfd,
               [[out]] uid_t *euid,
               [[out]] gid_t *egid) {
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

@@>> lpathconf(3)
@@Same as `pathconf(3)', but don't dereference `path' if it's a symbolic link
[[crt_dos_variant, cp]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires_include("<asm/os/oflags.h>")]]
[[requires($has_function(fpathconf) && $has_function(open) && defined(__O_RDONLY) &&
           defined(__O_PATH) && defined(__O_NOFOLLOW))]]
[[userimpl, section(".text.crt{|.dos}.fs.property")]]
$longptr_t lpathconf([[in]] char const *path, __STDC_INT_AS_UINT_T name) {
	fd_t fd;
	longptr_t result;
	fd = open(path, O_RDONLY | O_PATH | O_NOFOLLOW | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
	if unlikely(fd < 0)
		return -1;
	result = fpathconf(fd, name);
@@pp_if $has_function(close)@@
	(void)close(fd);
@@pp_endif@@
	return result;
}

@@>> setruid(3)
@@Set only the real UID of the calling thread.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
[[requires_function(setreuid)]]
[[section(".text.crt{|.dos}.bsd.user")]]
int setruid(uid_t ruid) {
	return setreuid(ruid, (uid_t)-1);
}

@@>> setrgid(3)
@@Set only the real GID of the calling thread.
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/types.h>")]]
[[requires_function(setregid)]]
[[section(".text.crt{|.dos}.bsd.user")]]
int setrgid(gid_t rgid) {
	return setregid(rgid, (gid_t)-1);
}

//TODO:int des_cipher(char const *, char *, long, int);
//TODO:int des_setkey(char const *);
//TODO:int exect(char const *, char *const *, char *const *);
//TODO:int fdiscard(int, off_t, off_t);
//TODO:int fsync_range(int, int, off_t, off_t);
//TODO:int getgroupmembership(char const *, gid_t, gid_t *, int, int *);
//TODO:int iruserok(uint32_t, int, char const *, char const *);
//TODO:int nfssvc(int, void *);
//TODO:int swapctl(int, void *, int);
//TODO:int undelete(char const *);
//TODO:int rresvport_af_addr(int *, int, void *);
//TODO:int iruserok_sa(const void *, int, int, char const *, char const *);

// >> int reboot(int, char *); // Incompatible w/ linux: int reboot(int)
// >> int swapon(char const *); // Incompatible w/ linux: int swapon(char const *, int)

%{

/* >> optreset(3)
 * When set to non-zero, the next call to `getopt(3)' will reset the internal
 * parser. The resulting behavior is the same as when `optind' is set to `0'.
 * Once the reset is done, this variable is set to `0' again.
 *
 * Pre-initialized to `0' */
#ifndef optreset
#ifdef __LOCAL_optreset
#define optreset __LOCAL_optreset
#elif defined(__CRT_HAVE_optreset)
__CSDECLARE(,int,optreset)
#define optreset optreset
#endif /* ... */
#endif /* !optreset */

/* >> suboptarg(3)
 * Global variable that gets assigned by `getsubopt(3)' from <stdlib.h>
 * Yes: it's weird that this variable is declared in <unistd.h>, while
 *      the function that uses it is  in <stdlib.h>; I didn't come  up
 *      with that... */
#ifndef suboptarg
#ifdef __LOCAL_suboptarg
#define suboptarg __LOCAL_suboptarg
#elif defined(__CRT_HAVE_suboptarg)
__CSDECLARE(,char *,suboptarg)
#define suboptarg suboptarg
#endif /* ... */
#endif /* !suboptarg */
}
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
[[section(".text.crt{|.dos}.io.tty")]]
char *ctermid_r([[out_opt]] char *s) {
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
[[cp, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
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
[[guard, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires(($has_function(fcntl) && defined(__F_CLOSEM)) || $has_function(close_range))]]
[[section(".text.crt{|.dos}.bsd.io.access")]]
void closefrom([[no_fdarg]] $fd_t lowfd) {
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
[[decl_include("<bits/types.h>")]]
[[crt_dos_variant]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires($has_function(dup2) && defined(__AT_FDROOT))]]
[[impl_include("<asm/os/fcntl.h>")]]
[[section(".text.crt{|.dos}.bsd")]]
int fchroot([[fdarg]] $fd_t fd) {
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

%[insert:extern(fattach)]
%[insert:extern(fdetach)]
%[insert:extern(ioctl)]
%[insert:extern(rexec_af)]
%[insert:extern(stime)]
%[insert:extern(tell)]
%[insert:function(yield = thrd_yield)]

// TODO: char *gettxt(char const *, char const *);
// TODO: int isaexec(char const *, char *const *, char *const *);
// TODO: offset_t llseek([[fdarg]] $fd_t fd, offset_t offset, __STDC_INT_AS_UINT_T whence);


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
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires($has_function(frealpathat) && defined(__AT_FDCWD))]]
[[crt_dos_variant, impl_include("<libc/errno.h>")]]
[[section(".text.crt{|.dos}.solaris")]]
__STDC_INT_AS_SSIZE_T resolvepath([[in]] char const *filename,
                                  [[out(return <= buflen)]] char *resolved,
                                  $size_t buflen) {
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
[[section(".text.crt{|.dos}.solaris")]]
$off_t tell([[fdarg]] $fd_t fd) {
	return lseek(fd, 0, SEEK_CUR);
}

%#ifdef __USE_LARGEFILE64
[[guard, wunused, decl_include("<bits/types.h>")]]
[[preferred_off64_variant_of(tell), doc_alias("tell")]]
[[requires_include("<asm/os/stdio.h>")]]
[[requires($has_function(lseek64) && defined(__SEEK_CUR))]]
[[impl_include("<asm/os/stdio.h>"), dos_only_export_alias("_telli64")]]
[[section(".text.crt{|.dos}.solaris")]]
$off64_t tell64([[fdarg]] $fd_t fd) {
	return lseek64(fd, 0, __SEEK_CUR);
}
%#endif /* __USE_LARGEFILE64 */


%{
#endif /* __USE_SOLARIS */

__SYSDECL_END
#endif /* __CC__ */

#if defined(__USE_SOLARIS) || defined(__USE_NETBSD)
#include <getopt.h>
#endif /* __USE_SOLARIS || __USE_NETBSD */

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


/* *_nocancel functions */
[[hidden, wunused, decl_include("<bits/types.h>")]]
[[requires_include("<bits/os/signal.h>")]]
[[requires(defined(__SIGRPC) && defined(__SIG_BLOCK) && defined(__SIG_SETMASK) &&
           $has_function(read, sigprocmask))]]
[[impl_include("<bits/os/sigset.h>")]]
[[section(".text.crt{|.dos}.compat.glibc")]]
ssize_t __read_nocancel([[fdread]] $fd_t fd,
                        [[out(return <= bufsize)]] void *buf,
                        size_t bufsize) {
	ssize_t result;
	struct __sigset_struct oss;
	struct __sigset_struct nss;
	(void)sigemptyset(&nss);
	(void)sigaddset(&nss, __SIGRPC);
	result = sigprocmask(__SIG_BLOCK, &nss, &oss);
	if likely(result == 0) {
		result = read(fd, buf, bufsize);
		(void)sigprocmask(__SIG_SETMASK, &oss, NULL);
	}
	return result;
}

[[hidden, wunused, decl_include("<bits/types.h>")]]
[[requires_include("<bits/os/signal.h>")]]
[[requires(defined(__SIGRPC) && defined(__SIG_BLOCK) && defined(__SIG_SETMASK) &&
           $has_function(write, sigprocmask))]]
[[impl_include("<bits/os/sigset.h>")]]
[[section(".text.crt{|.dos}.compat.glibc")]]
ssize_t __write_nocancel([[fdwrite]] $fd_t fd,
                         [[in(return <= bufsize)]] void const *buf,
                         size_t bufsize) {
	ssize_t result;
	struct __sigset_struct oss;
	struct __sigset_struct nss;
	(void)sigemptyset(&nss);
	(void)sigaddset(&nss, __SIGRPC);
	result = sigprocmask(__SIG_BLOCK, &nss, &oss);
	if likely(result == 0) {
		result = write(fd, buf, bufsize);
		(void)sigprocmask(__SIG_SETMASK, &oss, NULL);
	}
	return result;
}


[[hidden, decl_include("<features.h>", "<bits/types.h>")]]
[[decl_prefix(DEFINE_PIO_OFFSET)]]
[[requires_include("<bits/os/signal.h>")]]
[[requires(defined(__SIGRPC) && defined(__SIG_BLOCK) && defined(__SIG_SETMASK) &&
           $has_function(pread64, sigprocmask))]]
[[impl_include("<bits/os/sigset.h>")]]
[[section(".text.crt{|.dos}.compat.glibc")]]
ssize_t __pread64_nocancel([[fdread]] $fd_t fd, [[out(return <= bufsize)]] void *buf,
                           size_t bufsize, __PIO_OFFSET64 offset) {
	ssize_t result;
	struct __sigset_struct oss;
	struct __sigset_struct nss;
	(void)sigemptyset(&nss);
	(void)sigaddset(&nss, __SIGRPC);
	result = sigprocmask(__SIG_BLOCK, &nss, &oss);
	if likely(result == 0) {
		result = pread64(fd, buf, bufsize, offset);
		(void)sigprocmask(__SIG_SETMASK, &oss, NULL);
	}
	return result;
}

[[hidden]]
[[requires_include("<bits/os/signal.h>")]]
[[requires(defined(__SIGRPC) && defined(__SIG_BLOCK) && defined(__SIG_SETMASK) &&
           $has_function(pause, sigprocmask))]]
[[impl_include("<bits/os/sigset.h>")]]
[[section(".text.crt{|.dos}.compat.glibc")]]
int __pause_nocancel() {
	int result;
	struct __sigset_struct oss;
	struct __sigset_struct nss;
	(void)sigemptyset(&nss);
	(void)sigaddset(&nss, __SIGRPC);
	result = sigprocmask(__SIG_BLOCK, &nss, &oss);
	if likely(result == 0) {
		result = pause();
		(void)sigprocmask(__SIG_SETMASK, &oss, NULL);
	}
	return result;
}
