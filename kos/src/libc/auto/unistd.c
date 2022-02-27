/* HASH CRC-32:0x11eb2ded */
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
#ifndef GUARD_LIBC_AUTO_UNISTD_C
#define GUARD_LIBC_AUTO_UNISTD_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/unistd.h"
#include "../user/ctype.h"
#include "../user/fcntl.h"
#include "../user/pwd.h"
#include "readpassphrase.h"
#include "../user/signal.h"
#include "../user/stdlib.h"
#include "../user/string.h"
#include "../user/sys.ioctl.h"
#include "../user/sys.poll.h"
#include "../user/sys.socket.h"
#include "../user/sys.time.h"
#include "termios.h"
#include "../user/time.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
#include <libc/template/environ.h>
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_execv)(char const *__restrict path,
                                 __TARGV) {
	return libc_execve(path, ___argv, __LOCAL_environ);
}
#include <libc/template/environ.h>
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_execvp)(char const *__restrict file,
                                  __TARGV) {
	return libc_execvpe(file, ___argv, __LOCAL_environ);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_execl)(char const *__restrict path,
                                  char const *args,
                                  ...) {
	__REDIRECT_EXECL(char, libc_execv, path, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBCCALL libc_execl)(char const *__restrict path,
                                  char const *args,
                                  ...) {
	__REDIRECT_EXECL(char, libc_execv, path, args)
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_execle)(char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_EXECLE(char, libc_execve, path, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBCCALL libc_execle)(char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_EXECLE(char, libc_execve, path, args)
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_execlp)(char const *__restrict file,
                                   char const *args,
                                   ...) {
	__REDIRECT_EXECL(char, libc_execvp, file, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBCCALL libc_execlp)(char const *__restrict file,
                                   char const *args,
                                   ...) {
	__REDIRECT_EXECL(char, libc_execvp, file, args)
}
#include <hybrid/typecore.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__execvpe_impl) __ATTR_NOINLINE __ATTR_NONNULL((1, 3, 5, 6)) int
(__LIBCCALL __execvpe_impl)(char const *__restrict path, size_t path_len,
                            char const *__restrict file, size_t file_len,
                            __TARGV, __TENVP) {
	char *fullpath, *dst;
#ifdef _WIN32
	while (path_len && (path[path_len - 1] == '/' ||
	                    path[path_len - 1] == '\\'))
		--path_len;
#else /* _WIN32 */
	while (path_len && path[path_len - 1] == '/')
		--path_len;
#endif /* !_WIN32 */
	fullpath = (char *)__hybrid_alloca((path_len + 1 + file_len + 1) *
	                                   sizeof(char));
	dst = (char *)libc_mempcpyc(fullpath, path, path_len, sizeof(char));
	*dst++ = '/';
	dst = (char *)libc_mempcpyc(dst, file, file_len, sizeof(char));
	*dst = '\0';
	return libc_execve(fullpath, ___argv, ___envp);
}
__NAMESPACE_LOCAL_END
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBCCALL libc_execvpe)(char const *__restrict file,
                                   __TARGV,
                                   __TENVP) {
	char *env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the  specified
	 * pathname is executed.
	 * [...] */
#ifdef _WIN32
	if (libc_strchr(file, '/') || libc_strchr(file, '\\'))
		return libc_execve(file, ___argv, ___envp);
#else /* _WIN32 */
	if (libc_strchr(file, '/'))
		return libc_execve(file, ___argv, ___envp);
#endif /* !_WIN32 */
	env_path = libc_getenv("PATH");
	if (env_path && *env_path) {
		size_t filelen;
		filelen = libc_strlen(file);
		for (;;) {
			char *path_end;
#ifdef _WIN32
			path_end = libc_strchrnul(env_path, ';');
#else /* _WIN32 */
			path_end = libc_strchrnul(env_path, ':');
#endif /* !_WIN32 */
			(__NAMESPACE_LOCAL_SYM __execvpe_impl)(env_path, (size_t)(path_end - env_path),
			                                       file, filelen, ___argv, ___envp);
			if (!*path_end)
				break;
			env_path = path_end + 1;
		}
	} else {
#ifdef ENOENT
		(void)libc_seterrno(ENOENT);
#endif /* ENOENT */
	}
	return -1;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_execlpe)(char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_EXECLE(char, libc_execvpe, file, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBCCALL libc_execlpe)(char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_EXECLE(char, libc_execvpe, file, args)
}
/* >> ttyname(3)
 * Return the name of a TTY given its file descriptor */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_ttyname)(fd_t fd) {
	static char buf[32];
	if likely(libc_ttyname_r(fd, buf, sizeof(buf)) == 0)
		return buf;
	return NULL;
}
/* >> getlogin(3)
 * Return the login name for the current user, or `NULL' on error.
 * s.a. `getlogin_r()' and `cuserid()' */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_getlogin)(void) {
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
	char *result = libc_getenv("LOGNAME");
	if (!result)
		result = libc_cuserid(NULL);
	return result;


#else /* __CRT_HAVE_getenv || __LOCAL_environ */
	return libc_cuserid(NULL);
#endif /* !__CRT_HAVE_getenv && !__LOCAL_environ */
}
#endif /* !__KERNEL__ */
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if !defined(__KERNEL__) && (!defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__)
#include <bits/types.h>
/* >> write_printer(3)
 * A pformatprinter-compatible consumer that dumps all input data into `fd' by use
 * of `writeall(3)'. The given `fd' should be encoded by  `WRITE_PRINTER_ARG(fd)'.
 * @return: * : Same as `writeall(3)' */
INTERN ATTR_SECTION(".text.crt.io.write") NONNULL((2)) ssize_t
NOTHROW_RPC(__FORMATPRINTER_CC libc_write_printer)(void *fd,
                                                   char const *__restrict buf,
                                                   size_t bufsize) {
	return libc_writeall((fd_t)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))(uintptr_t)fd, buf, bufsize);
}
#endif /* !__KERNEL__ && (!__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__) */
#ifndef __KERNEL__
#include <bits/os/termios.h>
/* >> isatty(2)
 * Check if the given file handle `fd' refers to a TTY
 * @return: 1: Is a tty
 * @return: 0: Not a tty (`errno' was modified, and is usually set to `ENOTTY') */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED int
NOTHROW_NCX(LIBCCALL libc_isatty)(fd_t fd) {
	struct termios ios;
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA)
	return libc_ioctl(fd, __TCGETA, &ios) < 0 ? 0 : 1;
#else /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA */
	return libc_tcgetattr(fd, &ios) != 0 ? 0 : 1;
#endif /* (!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA */
}
#include <bits/os/stat.h>
/* >> get_current_dir_name(3)
 * Return an malloc(3)'d string  representing the current working  directory
 * This is usually the same  as `getcwd(NULL, 0)', however standards  caused
 * this function to be badly designed, as iff `$PWD' is defined and correct,
 * it is strdup(3)'d  and returned (correctness  is determined by  comparing
 * `stat($PWD)' against `stat(".")').
 * Due to the mandatory dependency on `getenv(3)', this function can't be
 * made thread-safe, so try not to use this one. */
INTERN ATTR_SECTION(".text.crt.dos.fs.basic_property") ATTR_MALLOC WUNUSED char *
NOTHROW_RPC(LIBDCALL libd_get_current_dir_name)(void) {
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && ((defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_stat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))) && (defined(__CRT_HAVE_strdup) || defined(__CRT_HAVE__strdup) || defined(__CRT_HAVE___strdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign))
	/* Specs require us to return a duplicate of $PWD iff it's correct
	 *   ***Author's comment: DUMB!***
	 */
	char *pwd = libd_getenv("PWD");
	if (pwd && *pwd) {
		struct stat st_pwd, st_cwd;
		if (stat(pwd, &st_pwd) == 0 &&
		    stat(".", &st_cwd) == 0) {
			if (st_pwd.st_dev == st_cwd.st_dev &&
			    st_pwd.st_ino == st_cwd.st_ino)
				return libc_strdup(pwd);
		}
	}
#endif /* (__CRT_HAVE_getenv || __LOCAL_environ) && ((__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_stat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64))) && (__CRT_HAVE_strdup || __CRT_HAVE__strdup || __CRT_HAVE___strdup || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) */
	return libd_getcwd(NULL, 0);
}
#include <bits/os/stat.h>
/* >> get_current_dir_name(3)
 * Return an malloc(3)'d string  representing the current working  directory
 * This is usually the same  as `getcwd(NULL, 0)', however standards  caused
 * this function to be badly designed, as iff `$PWD' is defined and correct,
 * it is strdup(3)'d  and returned (correctness  is determined by  comparing
 * `stat($PWD)' against `stat(".")').
 * Due to the mandatory dependency on `getenv(3)', this function can't be
 * made thread-safe, so try not to use this one. */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") ATTR_MALLOC WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_get_current_dir_name)(void) {
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && ((defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)) || (defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)) || (defined(__CRT_HAVE_stat) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_stat64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))) && (defined(__CRT_HAVE_strdup) || defined(__CRT_HAVE__strdup) || defined(__CRT_HAVE___strdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign))
	/* Specs require us to return a duplicate of $PWD iff it's correct
	 *   ***Author's comment: DUMB!***
	 */
	char *pwd = libc_getenv("PWD");
	if (pwd && *pwd) {
		struct stat st_pwd, st_cwd;
		if (stat(pwd, &st_pwd) == 0 &&
		    stat(".", &st_cwd) == 0) {
			if (st_pwd.st_dev == st_cwd.st_dev &&
			    st_pwd.st_ino == st_cwd.st_ino)
				return libc_strdup(pwd);
		}
	}
#endif /* (__CRT_HAVE_getenv || __LOCAL_environ) && ((__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || (__CRT_HAVE__stat64 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stat64i32 && __CRT_DOS_PRIMARY && __USE_TIME_BITS64) || (__CRT_HAVE__stati64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat32i64 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && __USE_FILE_OFFSET64) || (__CRT_HAVE__stat && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE__stat32 && __CRT_DOS_PRIMARY && !__USE_TIME_BITS64 && !__USE_FILE_OFFSET64) || (__CRT_HAVE_stat && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_stat64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64))) && (__CRT_HAVE_strdup || __CRT_HAVE__strdup || __CRT_HAVE___strdup || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) */
	return libc_getcwd(NULL, 0);
}
#include <hybrid/__alloca.h>
#include <asm/os/limits.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__group_member_impl) __ATTR_NOINLINE int
(__LIBCCALL __group_member_impl)(gid_t gid, unsigned int bufsize) {
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
__NAMESPACE_LOCAL_END
/* >> group_member(3)
 * Check if `gid' is an element of `getgroups(2)'
 * @return:  1: Yes, it's a member
 * @return:  0: No, it's not a member
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_group_member)(gid_t gid) {
	int result;
#if !defined(__NGROUPS_MAX) || __NGROUPS_MAX <= 0 || __NGROUPS_MAX >= 32
	unsigned int size = 32;
#else /* !__NGROUPS_MAX || __NGROUPS_MAX <= 0 || __NGROUPS_MAX >= 32 */
	unsigned int size = __NGROUPS_MAX;
#endif /* __NGROUPS_MAX && __NGROUPS_MAX > 0 && __NGROUPS_MAX < 32 */
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
#include <bits/os/timespec.h>
#include <bits/types.h>
/* >> usleep(3)
 * Sleep for `useconds' microseconds (1/1.000.000 seconds) */
INTERN ATTR_SECTION(".text.crt.system.utility") int
NOTHROW_RPC(LIBCCALL libc_usleep)(useconds_t useconds) {
#if defined(__CRT_HAVE_nanosleep64) || defined(__CRT_HAVE_nanosleep) || defined(__CRT_HAVE___nanosleep) || defined(__CRT_HAVE___libc_nanosleep)
	struct timespec ts;
	ts.tv_sec  = (time_t)(useconds / __UINT32_C(1000000));
	ts.tv_nsec = (syscall_ulong_t)(useconds % __UINT32_C(1000000)) * __UINT16_C(1000);
	return libc_nanosleep(&ts, NULL);
#else /* __CRT_HAVE_nanosleep64 || __CRT_HAVE_nanosleep || __CRT_HAVE___nanosleep || __CRT_HAVE___libc_nanosleep */
	__crtSleep(useconds / 1000l); /*USEC_PER_MSEC*/
	return 0;
#endif /* !__CRT_HAVE_nanosleep64 && !__CRT_HAVE_nanosleep && !__CRT_HAVE___nanosleep && !__CRT_HAVE___libc_nanosleep */
}
/* >> getwd(3)
 * Deprecated, alternate variant  of `getcwd()'.  It
 * should be obvious why you shouldn't use this one.
 * And  if it isn't, take a look at the arguments of
 * this function, compared to `getcwd()' */
INTERN ATTR_SECTION(".text.crt.dos.fs.basic_property") ATTR_DEPRECATED("Use getcwd()") NONNULL((1)) char *
NOTHROW_RPC(LIBDCALL libd_getwd)(char *buf) {
	return libd_getcwd(buf, (size_t)-1);
}
/* >> getwd(3)
 * Deprecated, alternate variant  of `getcwd()'.  It
 * should be obvious why you shouldn't use this one.
 * And  if it isn't, take a look at the arguments of
 * this function, compared to `getcwd()' */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") ATTR_DEPRECATED("Use getcwd()") NONNULL((1)) char *
NOTHROW_RPC(LIBCCALL libc_getwd)(char *buf) {
	return libc_getcwd(buf, (size_t)-1);
}
#include <asm/os/itimer.h>
#include <bits/os/itimerval.h>
INTERN ATTR_SECTION(".text.crt.system.utility") useconds_t
NOTHROW_NCX(LIBCCALL libc_ualarm)(useconds_t value,
                                  useconds_t interval) {
	struct itimerval timer, otimer;
	timer.it_value.tv_sec     = value / 1000000;
	timer.it_value.tv_usec    = value % 1000000;
	timer.it_interval.tv_sec  = interval / 1000000;
	timer.it_interval.tv_usec = interval % 1000000;
	if unlikely(libc_setitimer((__itimer_which_t)__ITIMER_REAL, &timer, &otimer) < 0)
		goto err;
	return (otimer.it_value.tv_sec * 1000000) +
	       (otimer.it_value.tv_usec);
err:
	return (useconds_t)-1;
}
#include <asm/pagesize.h>
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
INTERN ATTR_SECTION(".text.crt.system.configuration") ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T
NOTHROW(LIBCCALL libc_getpagesize)(void) {
	return __ARCH_PAGESIZE;
}
/* >> getdtablesize(3) */
INTERN ATTR_SECTION(".text.crt.system.configuration") ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T
NOTHROW(LIBCCALL libc_getdtablesize)(void) {

	return 0x7fffffff; /* INT_MAX */





}
#include <bits/crt/db/passwd.h>
/* >> getlogin_r(3)
 * Reentrant version of `getlogin()'. May truncate the name if it's longer than `name_len'
 * s.a. `getlogin()' and `cuserid()' */
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_getlogin_r)(char *name,
                                      size_t name_len) {
#if defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid))
	char buf[1024]; /* NSS_BUFLEN_PASSWD */
	struct passwd pwent, *pwptr;
#endif /* __CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid) */
	char *pwname;
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
	pwname = libc_getenv("LOGNAME");
#if defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid))
	if (!pwname)
#endif /* __CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid) */
#endif /* __CRT_HAVE_getenv || __LOCAL_environ */
#if defined(__CRT_HAVE_getpwuid_r) && (defined(__CRT_HAVE_geteuid) || defined(__CRT_HAVE___geteuid) || defined(__CRT_HAVE___libc_geteuid))
	{
		if (libc_getpwuid_r(libc_geteuid(), &pwent, buf,
		               sizeof(buf), &pwptr) ||
		    pwptr == NULL)
			return -1;
		pwname = pwptr->pw_name;
		if (!pwname)
			return -1;
	}
#endif /* __CRT_HAVE_getpwuid_r && (__CRT_HAVE_geteuid || __CRT_HAVE___geteuid || __CRT_HAVE___libc_geteuid) */
	if (name_len) {
		name[name_len - 1] = '\0';
		libc_strncpy(name, pwname, name_len - 1);
	}
	return 0;
}
#include <asm/crt/readpassphrase.h>
/* >> getpass(3), getpassphrase(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_getpass)(char const *__restrict prompt) {
	static char buf[257]; /* `getpassphrase()' requires passwords at least this long! */
//	static char buf[129]; /* 129 == _PASSWORD_LEN + 1 */
	return libc_getpass_r(prompt, buf, sizeof(buf));
}
/* >> swab(3)
 * Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
 * exchanging the order of even and odd bytes ("123456" --> "214365")
 * When `n_bytes <= 1', don't do anything and return immediately */
INTERN ATTR_SECTION(".text.crt.string.memory") NONNULL((1, 2)) void
NOTHROW_NCX(LIBCCALL libc_swab)(void const *__restrict from,
                                void *__restrict to,
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
/* >> ctermid(3)
 * Writes the string "/dev/tty" to `s', or returns a pointer to
 * a writable  data location  that contains  that same  string. */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_RETNONNULL char *
NOTHROW_NCX(LIBCCALL libc_ctermid)(char *s) {
	static char buf[9];
	if (s == NULL)
		s = buf;
	return libc_strcpy(s, "/dev/tty");
}
#include <asm/crt/stdio.h>
/* >> cuserid(3)
 * Return the name of the current user (`$LOGNAME' or `getpwuid(geteuid())'), storing
 * that  name  in  `s'.  When  `s'  is   NULL,  a  static  buffer  is  used   instead
 * When  given,   `s'   must  be   a   buffer   of  at   least   `L_cuserid'   bytes.
 * If the actual  username is longer  than this,  it may be  truncated, and  programs
 * that wish to support longer usernames  should make use of `getlogin_r()'  instead.
 * s.a. `getlogin()' and `getlogin_r()' */
INTERN ATTR_SECTION(".text.crt.io.tty") char *
NOTHROW_NCX(LIBCCALL libc_cuserid)(char *s) {
#ifdef __L_cuserid
	static char cuserid_buffer[__L_cuserid];
	if (!s)
		s = cuserid_buffer;
	return libc_getlogin_r(s, __L_cuserid) ? NULL : s;
#else /* __L_cuserid */
	static char cuserid_buffer[9];
	if (!s)
		s = cuserid_buffer;
	return libc_getlogin_r(s, 9) ? NULL : s;
#endif /* !__L_cuserid */
}
#include <bits/types.h>
#include <asm/os/stdio.h>
#include <asm/os/oflags.h>
#include <libc/errno.h>
#include <paths.h>
#include <asm/crt/getpassfd.h>
#include <asm/os/termios.h>
#include <bits/os/termios.h>
#include <asm/os/signal.h>
#include <bits/os/pollfd.h>
#include <asm/os/poll.h>
#include <libc/strings.h>
/* >> getpassfd(3)
 * This function behaves  similar to `readpassphrase(3)',  but is  still
 * quite  distinct from that  function in how this  one behaves, vs. how
 * that other function behaves. In general, this function is a bit  more
 * user-friendly, in  that it  offers more  (but different)  `flags'  to
 * control how the password prompt is generated, with the main advantage
 * of this function  being that it  implements some "advanced"  readline
 * functionality, such as deleting  typed characters without relying  on
 * the  system  TTY canonical  buffer (which  `readpassphrase(3)' needs,
 * since it doesn't include support  for _any_ control characters  other
 * that CR/LF as indicators to stop reading text)
 * Which of the 2 functions should be used is a matter of taste, but
 * personally,   I   prefer  this   one   over  `readpassphrase(3)'.
 * @param: prompt:  [0..1]      Text-prompt to display to the user, or `NULL'
 * @param: buf:     [0..buflen] Buffer that will receive the user's password.
 *                              When set to  `NULL', a dynamically  allocated
 *                              buffer will be used and returned.
 * @param: buflen:              Size of `buf' (in characters) (ignored when `buf == NULL')
 * @param: fds:     [0..1]      When non-NULL,  an [stdin,stdout,stderr]  triple
 *                              of files, used for [read,write,beep] operations.
 *                              When  `NULL', try to use `/dev/tty' instead, and
 *                              if that fails, use  `STDIN_FILENO,STDERR_FILENO,
 *                              STDERR_FILENO' as final fallback.
 *                              When `GETPASS_NEED_TTY' is set, the  function
 *                              will fail with `errno=ENOTTY' if the actually
 *                              used `fds[0]' (iow: stdin) isn't a TTY device
 *                              s.a. `isatty(3)'
 * @param: flags:               Set of `GETPASS_*' flags (from <unistd.h>)
 * @param: timeout_in_seconds:  When non-0, timeout (in  seconds) to wait for  the
 *                              user to type each character of their password.  If
 *                              this timeout expires, fail with  `errno=ETIMEDOUT'
 *                              Negative values result in weak undefined behavior.
 * @return: * :   [buf == NULL] Success (dynamically allocated buffer; must be `free(3)'d)
 * @return: buf:                Success
 * @return: NULL: [ETIMEDOUT]   The given `timeout_in_seconds' has expired.
 * @return: NULL: [EINVAL]      `buf' is non-`NULL', but `buflen' is `0'
 * @return: NULL: [ENOTTY]      `GETPASS_NEED_TTY' was given, but not a tty
 * @return: NULL: [ENOMEM]      Insufficient memory
 * @return: NULL: [ENODATA]     End-of-file while reading, and `GETPASS_FAIL_EOF' was set.
 * @return: NULL: [*]           Error */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_getpassfd)(char const *prompt,
                                     char *buf,
                                     size_t buflen,
                                     fd_t fds[3],
                                     __STDC_INT_AS_UINT_T flags,
                                     int timeout_in_seconds) {
#ifndef __STDIN_FILENO
#define __STDIN_FILENO 0
#endif /* !__STDIN_FILENO */
#ifndef __STDERR_FILENO
#define __STDERR_FILENO 2
#endif /* !__STDERR_FILENO */

#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
	bool heap_buf;
#endif /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
	char *result;
	fd_t default_fds[3];
	signo_t interrupt_signo;

	/* Initialize locals. */
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	struct termios old_ios, new_ios;
	libc_memset(&old_ios, -1, sizeof(old_ios));
	libc_memset(&new_ios, -1, sizeof(new_ios));
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */
	result          = NULL;
	interrupt_signo = 0;
	default_fds[0]  = __STDIN_FILENO;

	/* Allocate a dynamic buffer if none was given by the caller. */
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
	heap_buf = false;
	if (!buf) {
		buflen = 512;
		buf = (char *)libc_malloc(buflen * sizeof(char));
		if unlikely(!buf) {
			buflen = 1;
			buf = (char *)libc_malloc(buflen * sizeof(char));
			if unlikely(!buf)
				goto out;
		}
		heap_buf = true;
	} else
#endif /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
	if (buflen < 1) {
		/* Invalid buffer length */
#ifdef EINVAL
		(void)libc_seterrno(EINVAL);
#endif /* EINVAL */
		goto out;
	}

	/* Open input files if not provided by the caller. */
	if (!fds) {
		fds = default_fds;
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#ifdef __O_CLOEXEC
#define __PRIVATE_GETPASSFD_O_CLOEXEC __O_CLOEXEC
#else /* __O_CLOEXEC */
#define __PRIVATE_GETPASSFD_O_CLOEXEC 0
#endif /* !__O_CLOEXEC */
#ifdef __O_CLOFORK
#define __PRIVATE_GETPASSFD_O_CLOFORK __O_CLOFORK
#else /* __O_CLOFORK */
#define __PRIVATE_GETPASSFD_O_CLOFORK 0
#endif /* !__O_CLOFORK */
#ifdef __O_RDWR
#define __PRIVATE_GETPASSFD_O_RDWR __O_RDWR
#else /* __O_RDWR */
#define __PRIVATE_GETPASSFD_O_RDWR 0
#endif /* !__O_RDWR */
#if defined(__O_NONBLOCK) && (defined(__CRT_HAVE_poll) || defined(__CRT_HAVE___poll))
#define __PRIVATE_GETPASSFD_O_NONBLOCK __O_NONBLOCK
#else /* __O_NONBLOCK && (__CRT_HAVE_poll || __CRT_HAVE___poll) */
#define __PRIVATE_GETPASSFD_O_NONBLOCK 0
#endif /* !__O_NONBLOCK || (!__CRT_HAVE_poll && !__CRT_HAVE___poll) */
#ifdef _PATH_TTY
#define __PRIVATE_GETPASSFD_PATH_TTY _PATH_TTY
#else /* _PATH_TTY */
#define __PRIVATE_GETPASSFD_PATH_TTY "/dev/tty"
#endif /* !_PATH_TTY */
#if __PRIVATE_GETPASSFD_O_NONBLOCK != 0
		default_fds[2] = libc_open(__PRIVATE_GETPASSFD_PATH_TTY,
		                      __PRIVATE_GETPASSFD_O_CLOEXEC |
		                      __PRIVATE_GETPASSFD_O_CLOFORK |
		                      __PRIVATE_GETPASSFD_O_RDWR |
		                      (timeout_in_seconds != 0 ? __PRIVATE_GETPASSFD_O_NONBLOCK : 0));
#else /* __PRIVATE_GETPASSFD_O_NONBLOCK != 0 */
		default_fds[2] = libc_open(__PRIVATE_GETPASSFD_PATH_TTY,
		                      __PRIVATE_GETPASSFD_O_CLOEXEC |
		                      __PRIVATE_GETPASSFD_O_CLOFORK |
		                      __PRIVATE_GETPASSFD_O_RDWR);
#endif /* __PRIVATE_GETPASSFD_O_NONBLOCK == 0 */
		if (default_fds[2] != -1) {
			default_fds[0] = default_fds[2];
			default_fds[1] = default_fds[2];
		} else
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
		{
			default_fds[1] = __STDERR_FILENO;
			default_fds[2] = __STDERR_FILENO;
		}
	}

	/* Load terminal settings. */
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	if (libc_tcgetattr(fds[0], &old_ios) == 0) {
		libc_memcpy(&new_ios, &old_ios, sizeof(struct termios));

		/* Configure new settings. */
#if defined(__ECHO) || defined(__ECHOK) || defined(__ECHOE) || defined(__ECHOKE) || defined(__ECHOCTL) || defined(__ISIG) || defined(__ICANON)
		new_ios.c_lflag &= ~(0 |
#ifdef __ECHO
		                       __ECHO |
#endif /* __ECHO */
#ifdef __ECHOK
		                       __ECHOK |
#endif /* __ECHOK */
#ifdef __ECHOE
		                       __ECHOE |
#endif /* __ECHOE */
#ifdef __ECHOKE
		                       __ECHOKE |
#endif /* __ECHOKE */
#ifdef __ECHOCTL
		                       __ECHOCTL |
#endif /* __ECHOCTL */
#ifdef __ISIG
		                       __ISIG |
#endif /* __ISIG */
#ifdef __ICANON
		                       __ICANON
#endif /* __ICANON */
		                       );
#endif /* __ECHO || __ECHOK || __ECHOE || __ECHOKE || __ECHOCTL || __ISIG || __ICANON */

#ifdef __VMIN
		new_ios.c_cc[__VMIN] = 1;
#endif /* __VMIN */
#ifdef __VTIME
		new_ios.c_cc[__VTIME] = 0;
#endif /* __VTIME */

#if defined(__TCSAFLUSH) && defined(__TCSASOFT)
		if (libc_tcsetattr(fds[0], __TCSAFLUSH | __TCSASOFT, &new_ios) != 0)
#elif defined(__TCSAFLUSH)
		if (libc_tcsetattr(fds[0], __TCSAFLUSH, &new_ios) != 0)
#else /* ... */
		if (libc_tcsetattr(fds[0], 0, &new_ios) != 0)
#endif /* !... */
		{
			goto out;
		}
	} else {
		if (flags & __GETPASS_NEED_TTY)
			goto out; /* tcgetattr() should have already set errno=ENOTTY */
	}
#elif defined(__CRT_HAVE_isatty) || defined(__CRT_HAVE__isatty) || defined(__CRT_HAVE___isatty) || defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))
	if ((flags & __GETPASS_NEED_TTY) && !libc_isatty(fds[0]))
		goto out; /* isatty() should have already set errno=ENOTTY */
#endif /* ... */

	/* Print the given prompt */
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
	if (prompt && *prompt) {
		if (libc_write(fds[1], prompt, libc_strlen(prompt)) == -1)
			goto out;
	}
#else /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */
	(void)prompt;
#endif /* !__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write */

	/* The actual interpreter loop for the password reader: */
	{
		unsigned char ch, *dst, *bufend;
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__VLNEXT)
		bool escape; /* Set to `true' if the next character is escaped. */
		escape = false;
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __VLNEXT */
		dst    = (unsigned char *)buf;
		bufend = (unsigned char *)buf + buflen - 1;
		for (;;) {

#if defined(__CRT_HAVE_poll) || defined(__CRT_HAVE___poll)
			if (timeout_in_seconds != 0) {
				int status;
				struct pollfd pfd;
				pfd.fd      = fds[0];
#if defined(__POLLIN) && defined(__POLLRDNORM)
				pfd.events  = __POLLIN | __POLLRDNORM;
#elif defined(__POLLIN)
				pfd.events  = __POLLIN;
#else /* ... */
				pfd.events  = 0;
#endif /* !... */
				status = libc_poll(&pfd, 1, timeout_in_seconds * 1000);
				if unlikely(status == -1)
					goto out; /* Error... */
				if unlikely(status == 0) {
#ifdef ETIMEDOUT
					(void)libc_seterrno(ETIMEDOUT);
#else /* ETIMEDOUT */
					(void)libc_seterrno(1);
#endif /* !ETIMEDOUT */
					goto out; /* Timeout... */
				}
				/* Assume that data can be read now! */
			}
#else /* __CRT_HAVE_poll || __CRT_HAVE___poll */
			(void)timeout_in_seconds;
#endif /* !__CRT_HAVE_poll && !__CRT_HAVE___poll */

			/* Actually read the next character. */
			{
				ssize_t status;
				status = libc_read(fds[0], &ch, sizeof(ch));
				if (status < (ssize_t)sizeof(char)) {
					if (status < 0)
						goto out; /* Error */
#ifdef __VEOF
handle_eof:
#endif /* __VEOF */
					if (flags & __GETPASS_FAIL_EOF) {
						/* Error out on regular, old EOF */
#ifdef ENODATA
						(void)libc_seterrno(ENODATA);
#endif /* ENODATA */
						goto out;
					}
					break;
				}
			}

#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__VLNEXT)
			if (escape) {
				/* Unconditionally add `ch' */
				escape = false;
			} else
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __VLNEXT */
			{
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
#if !__VDISABLE
#define __PRIVATE_GETPASSFD_CTRL(index, defl) \
	(new_ios.c_cc[index] != '\0' ? new_ios.c_cc[index] : __CTRL(defl))
#else /* !__VDISABLE */
#define __PRIVATE_GETPASSFD_CTRL(index, defl) \
	((new_ios.c_cc[index] != '\0' && new_ios.c_cc[index] != __VDISABLE) ? new_ios.c_cc[index] : __CTRL(defl))
#endif /* __VDISABLE */

				/* Check for control characters that should be ignored. */
#ifdef __VREPRINT
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VREPRINT, 'R'))
					continue;
#endif /* __VREPRINT */

#ifdef __VSTART
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VSTART, 'Q'))
					continue;
#endif /* __VSTART */

#ifdef __VSTOP
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VSTOP, 'S'))
					continue;
#endif /* __VSTOP */

#ifdef __VSTATUS
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VSTATUS, 'T'))
					continue;
#endif /* __VSTATUS */

#ifdef __VDISCARD
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VDISCARD, 'O'))
					continue;
#endif /* __VDISCARD */

				/* Check for ^V */
#ifdef __VLNEXT
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VLNEXT, 'V')) {
					escape = true;
					continue;
				}
#endif /* __VLNEXT */

				/* Both line- and word-kill are treated as a full reset. */
#if defined(__VKILL) || defined(__VWERASE)
				if (
#ifdef __VKILL
				    ch == __PRIVATE_GETPASSFD_CTRL(__VKILL, 'U')
#endif /* __VKILL */
#if defined(__VKILL) && defined(__VWERASE)
				    ||
#endif /* __VKILL && __VWERASE */
#ifdef __VWERASE
				    ch == __PRIVATE_GETPASSFD_CTRL(__VWERASE, 'W')
#endif /* __VWERASE */
				    )
				{
					__libc_explicit_bzero(buf, buflen * sizeof(char));
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
					if (flags & (__GETPASS_ECHO | __GETPASS_ECHO_STAR)) {
						while (dst > (unsigned char *)buf) {
							if (libc_write(fds[1], "\b \b", 3 * sizeof(char)) == -1)
								goto out;
							--dst;
						}
					}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */
					dst = (unsigned char *)buf;
					continue;
				}
#endif /* __VKILL || __VWERASE */

				/* Check for end-of-file (via ^D) */
#ifdef __VEOF
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VEOF, 'D'))
					goto handle_eof;
#endif /* __VEOF */

				/* Check for TTY signal characters. */
#if defined(__VINTR) && defined(__SIGINT)
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VINTR, 'C')) {
					interrupt_signo = __SIGINT;
					goto out;
				}
#endif /* __VINTR && __SIGINT */

#if defined(__VQUIT) && defined(__SIGQUIT)
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VQUIT, '\\')) {
					interrupt_signo = __SIGQUIT;
					goto out;
				}
#endif /* __VQUIT && __SIGQUIT */

#if (defined(__VSUSP) || defined(__VDSUSP)) && defined(__SIGTSTP)
				if (
#ifdef __VSUSP
				    ch == __PRIVATE_GETPASSFD_CTRL(__VSUSP, 'Z')
#endif /* __VSUSP */
#if defined(__VSUSP) && defined(__VDSUSP)
				    ||
#endif /* __VSUSP && __VDSUSP */
#ifdef __VDSUSP
				    ch == __PRIVATE_GETPASSFD_CTRL(__VDSUSP, 'Y')
#endif /* __VDSUSP */
				    ) {
					interrupt_signo = __SIGTSTP;
					goto out;
				}
#endif /* (__VSUSP || __VDSUSP) && __SIGTSTP */

				/* Check for custom newline characters. */
#ifdef __VEOL
				if (new_ios.c_cc[__VEOL] != __VDISABLE && ch == new_ios.c_cc[__VEOL])
					break;
#endif /* __VEOL */
#ifdef __VEOL2
				if (new_ios.c_cc[__VEOL2] != __VDISABLE && ch == new_ios.c_cc[__VEOL2])
					break;
#endif /* __VEOL2 */
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */

				/* Check for single-character erase (backspace) */
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__VERASE)
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VERASE, 'H'))
#else /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __VERASE */
				if (ch == '\b')
#endif /* (!__CRT_HAVE_tcgetattr && !__CRT_HAVE___tcgetattr && ((!__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__TCGETA)) || (!__CRT_HAVE_tcsetattr && !__CRT_HAVE_ioctl && !__CRT_HAVE___ioctl && !__CRT_HAVE___libc_ioctl) || !__VERASE */
				{
					if (dst > (unsigned char *)buf) {
						--dst;
						__libc_explicit_bzero(dst, sizeof(char));
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
						if (flags & (__GETPASS_ECHO | __GETPASS_ECHO_STAR)) {
							if (libc_write(fds[1], "\b \b", 3 * sizeof(char)) == -1)
								goto out;
						}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */
						continue;
					}
maybe_beep:
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
					if (!(flags & __GETPASS_NO_BEEP)) {
						if (libc_write(fds[2], "\7" /*BEL*/, sizeof(char)) == -1)
							goto out;
					}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */
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
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
				if (heap_buf) {
					/* Allocate more space. */
					size_t new_buflen;
					char *new_buf;
					new_buflen = buflen * 2;
					new_buf = (char *)libc_malloc(new_buflen * sizeof(char));
					if unlikely(!new_buf) {
						new_buflen = buflen + 1;
						new_buf = (char *)libc_malloc(new_buflen * sizeof(char));
						if unlikely(!new_buf)
							goto out;
					}
					libc_memcpyc(new_buf, buf, buflen, sizeof(char));
					__libc_explicit_bzero(buf, buflen * sizeof(char));
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
					libc_free(buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
					dst    = (unsigned char *)new_buf + (size_t)(dst - (unsigned char *)buf);
					bufend = (unsigned char *)new_buf + new_buflen - 1;
					buf    = new_buf;
				} else
#endif /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
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
				ch = (unsigned char)libc_tolower((char)ch);
			if (flags & __GETPASS_FORCE_UPPER)
				ch = (unsigned char)libc_toupper((char)ch);

			/* Append to the result buffer. */
			*dst++ = ch;

#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
			if (flags & __GETPASS_ECHO_STAR) {
				if (libc_write(fds[1], "*", sizeof(char)) == -1)
					goto out;
			} else if (flags & __GETPASS_ECHO) {
				if (!libc_isprint((char)ch))
					ch = (unsigned char)'?';
				if (libc_write(fds[1], &ch, sizeof(char)) == -1)
					goto out;
			}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */

		} /* for (;;) */

		/* If requested to do so by the caller, write a trailing '\n' upon success. */
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
		if (flags & __GETPASS_ECHO_NL) {
			if (libc_write(fds[1], "\n", 1) == -1)
				goto out;
		}
#endif /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */

		/* Force NUL-termination of the password buffer. */
		*dst = '\0';

#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
		if (heap_buf && dst < bufend) {
			/* Try to release unused buffer memory. */
			size_t new_buflen;
			char *new_buf;
			new_buflen = (size_t)((dst + 1) - (unsigned char *)buf);
			new_buf    = (char *)libc_malloc(new_buflen * sizeof(char));
			if likely(new_buf) {
				libc_memcpyc(new_buf, buf, new_buflen, sizeof(char));
				__libc_explicit_bzero(buf, buflen * sizeof(char));
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
				libc_free(buf);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
				buf    = new_buf;
				buflen = new_buflen;
			}
		}
#endif /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */

		/* Indicate success! */
		result = buf;
	}
out:

	/* Restore old terminal settings. */
#if (defined(__CRT_HAVE_tcgetattr) || defined(__CRT_HAVE___tcgetattr) || ((defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA))) && (defined(__CRT_HAVE_tcsetattr) || defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl))
	if (libc_memcmp(&old_ios, &new_ios, sizeof(struct termios)) != 0) {
#if defined(__TCSAFLUSH) && defined(__TCSASOFT)
		(void)libc_tcsetattr(fds[0], __TCSAFLUSH | __TCSASOFT, &old_ios);
#elif defined(__TCSAFLUSH)
		(void)libc_tcsetattr(fds[0], __TCSAFLUSH, &old_ios);
#else /* ... */
		(void)libc_tcsetattr(fds[0], 0, &old_ios);
#endif /* !... */
	}
#endif /* (__CRT_HAVE_tcgetattr || __CRT_HAVE___tcgetattr || ((__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA)) && (__CRT_HAVE_tcsetattr || __CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) */

	/* Close our file handle to /dev/tty */
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
	if (default_fds[0] != __STDIN_FILENO)
		libc_close(default_fds[0]);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */

	/* Error-only cleanup... */
	if (!result) {

		/* Don't leave a (possibly incomplete) password dangling in-memory! */
		__libc_explicit_bzero(buf, buflen * sizeof(char));

		/* Free a dynamically allocated password buffer. */
#if (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))
		if (heap_buf)
			libc_free(buf);
#endif /* (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free) */

		/* Raise the signal of a given control character, and/or set
		 * `errno'  to indicate that the password-read operation was
		 * interrupted. */
		if (interrupt_signo != 0) {
#if defined(__CRT_HAVE_raise) || ((defined(__CRT_HAVE_pthread_kill) || defined(__CRT_HAVE_thr_kill)) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self))) || ((defined(__CRT_HAVE_kill) || defined(__CRT_HAVE___kill) || defined(__CRT_HAVE___libc_kill)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
			if (!(flags & __GETPASS_NO_SIGNAL))
				(void)libc_raise(interrupt_signo);
#endif /* __CRT_HAVE_raise || ((__CRT_HAVE_pthread_kill || __CRT_HAVE_thr_kill) && (__CRT_HAVE_pthread_self || __CRT_HAVE_thrd_current || __CRT_HAVE_thr_self)) || ((__CRT_HAVE_kill || __CRT_HAVE___kill || __CRT_HAVE___libc_kill) && (__CRT_HAVE_getpid || __CRT_HAVE__getpid || __CRT_HAVE___getpid || __CRT_HAVE___libc_getpid)) */
#ifdef EINTR
			(void)libc_seterrno(EINTR);
#endif /* EINTR */
		}
	}
	return result;
}
#include <asm/crt/getpassfd.h>
#include <asm/crt/readpassphrase.h>
/* >> getpass_r(3) */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED char *
NOTHROW_RPC(LIBCCALL libc_getpass_r)(char const *prompt,
                                     char *buf,
                                     size_t bufsize) {
#if defined(__CRT_HAVE_getpassfd) || defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read) || defined(__CRT_HAVE___libc_read)
	/* Prefer using `getpassfd(3)' because I feel like that one's more
	 * user-friendly.  - But if it's not available, fall back on using
	 * the regular, old `readpassphrase(3)' */
#ifdef __GETPASS_ECHO_NL
	return libc_getpassfd(prompt, buf, bufsize, NULL, __GETPASS_ECHO_NL, 0);
#else /* __GETPASS_ECHO_NL */
	return libc_getpassfd(prompt, buf, bufsize, NULL, 0, 0);
#endif /* !__GETPASS_ECHO_NL */
#else /* __CRT_HAVE_getpassfd || __CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read || __CRT_HAVE___libc_read */
#ifdef __RPP_ECHO_OFF
	return libc_readpassphrase(prompt, buf, bufsize, __RPP_ECHO_OFF);
#else /* __RPP_ECHO_OFF */
	return libc_readpassphrase(prompt, buf, bufsize, 0);
#endif /* !__RPP_ECHO_OFF */
#endif /* !__CRT_HAVE_getpassfd && !__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read && !__CRT_HAVE___libc_read */
}
#include <bits/os/ucred.h>
#include <libc/errno.h>
/* >> getpeereid(3)
 * Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)' */
INTERN ATTR_SECTION(".text.crt.sched.user") NONNULL((2, 3)) int
NOTHROW_NCX(LIBCCALL libc_getpeereid)(fd_t sockfd,
                                      uid_t *euid,
                                      gid_t *egid) {
	int result;
	struct ucred cred;
	socklen_t len = sizeof(cred);
	result = libc_getsockopt(sockfd, __SOL_SOCKET, __SO_PEERCRED, &cred, &len);
	if (result == 0) {
		/* Safety check that enough data was read... */
		if (len < (__COMPILER_OFFSETAFTER(struct ucred, uid) >
		           __COMPILER_OFFSETAFTER(struct ucred, gid)
		           ? __COMPILER_OFFSETAFTER(struct ucred, uid)
		           : __COMPILER_OFFSETAFTER(struct ucred, gid))) {
#ifdef ENOPROTOOPT
			result = libc_seterrno(ENOPROTOOPT);
#else /* ENOPROTOOPT */
			result = libc_seterrno(1);
#endif /* !ENOPROTOOPT */
		} else {
			*euid = cred.uid;
			*egid = cred.gid;
		}
	}
	return result;
}
/* >> closefrom(2)
 * Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
INTERN ATTR_SECTION(".text.crt.bsd.io.access") void
NOTHROW_NCX(LIBCCALL libc_closefrom)(fd_t lowfd) {
#if (defined(__CRT_HAVE_fcntl) || defined(__CRT_HAVE___fcntl) || defined(__CRT_HAVE___libc_fcntl)) && defined(__F_CLOSEM)
	libc_fcntl(lowfd, __F_CLOSEM);
#else /* (__CRT_HAVE_fcntl || __CRT_HAVE___fcntl || __CRT_HAVE___libc_fcntl) && __F_CLOSEM */
	libc_close_range((unsigned int)lowfd, (unsigned int)-1, 0);
#endif /* (!__CRT_HAVE_fcntl && !__CRT_HAVE___fcntl && !__CRT_HAVE___libc_fcntl) || !__F_CLOSEM */
}
#include <asm/os/fcntl.h>
/* >> fchroot(2)
 * Change the root directory to  `fd'. If `fd' was opened  before a prior call to  `chroot()',
 * and referrs to  a directory,  then this function  can be  used to escape  a chroot()  jail.
 * No special permissions  are required to  use this function,  since a malicious  application
 * could achieve the same behavior by use of `*at' system calls, using `fd' as `dfd' argument. */
INTERN ATTR_SECTION(".text.crt.sched.user") int
NOTHROW_NCX(LIBCCALL libc_fchroot)(fd_t fd) {
	fd_t result;
	result = libc_dup2(fd, __AT_FDROOT);
	if likely(result >= 0)
		result = 0;
	return result;
}
#include <libc/errno.h>
/* >> resolvepath(3)
 * Similar  to  `frealpathat(2)'  (though  use  the  later  for  more   options)
 * Also note that this function appears to  have a weird rule (which KOS  simply
 * ignores)  that is related  to this function not  writing more than `PATH_MAX'
 * bytes to `buf'. (Why??? I mean: The whole point of having a `buflen' argument
 * is to be able to handle names of arbitrary lengths)
 * Additionally, the online docs don't mention what happens when `buflen' is  too
 * small, so I guess I can just make up what's supposed to happen, and I say that
 * the function will set errno=ERANGE and return -1
 * @return: * : Used buffer size (possibly including a NUL-byte, but maybe not)
 * @return: -1: Error. (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.dos.solaris") NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd_resolvepath)(char const *filename,
                                       char *resolved,
                                       size_t buflen) {
	__STDC_INT_AS_SSIZE_T retval;
	char *result;
	result = libd_frealpathat(__AT_FDCWD, filename, resolved, buflen, 0);
	if unlikely(!result)
		return -1;
	retval = (__STDC_INT_AS_SSIZE_T)libc_strlen(result);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	if unlikely(!resolved)
		libc_free(result);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return retval;
}
#include <libc/errno.h>
/* >> resolvepath(3)
 * Similar  to  `frealpathat(2)'  (though  use  the  later  for  more   options)
 * Also note that this function appears to  have a weird rule (which KOS  simply
 * ignores)  that is related  to this function not  writing more than `PATH_MAX'
 * bytes to `buf'. (Why??? I mean: The whole point of having a `buflen' argument
 * is to be able to handle names of arbitrary lengths)
 * Additionally, the online docs don't mention what happens when `buflen' is  too
 * small, so I guess I can just make up what's supposed to happen, and I say that
 * the function will set errno=ERANGE and return -1
 * @return: * : Used buffer size (possibly including a NUL-byte, but maybe not)
 * @return: -1: Error. (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.solaris") NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_resolvepath)(char const *filename,
                                       char *resolved,
                                       size_t buflen) {
	__STDC_INT_AS_SSIZE_T retval;
	char *result;
	result = libc_frealpathat(__AT_FDCWD, filename, resolved, buflen, 0);
	if unlikely(!result)
		return -1;
	retval = (__STDC_INT_AS_SSIZE_T)libc_strlen(result);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	if unlikely(!resolved)
		libc_free(result);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return retval;
}
#include <asm/os/stdio.h>
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
INTERN ATTR_SECTION(".text.crt.solaris") WUNUSED off_t
NOTHROW_NCX(LIBCCALL libc_tell)(fd_t fd) {
	return libc_lseek(fd, 0, SEEK_CUR);
}
#include <bits/types.h>
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_tell64, libc_tell);
#else /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
#include <asm/os/stdio.h>
/* >> tell(3), tell64(3)
 * Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
INTERN ATTR_SECTION(".text.crt.solaris") WUNUSED off64_t
NOTHROW_NCX(LIBCCALL libc_tell64)(fd_t fd) {
	return libc_lseek64(fd, 0, __SEEK_CUR);
}
#endif /* __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__ */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_execv, libc_execv);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(execv, libc_execv);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_execvp, libc_execvp);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(execvp, libc_execvp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_execl, libd_execl);
DEFINE_PUBLIC_ALIAS(DOS$execl, libd_execl);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_execl, libc_execl);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(execl, libc_execl);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_execle, libd_execle);
DEFINE_PUBLIC_ALIAS(DOS$execle, libd_execle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_execle, libc_execle);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(execle, libc_execle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_execlp, libd_execlp);
DEFINE_PUBLIC_ALIAS(DOS$execlp, libd_execlp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_execlp, libc_execlp);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(execlp, libc_execlp);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_execvpe, libc_execvpe);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(execvpe, libc_execvpe);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_execlpe, libd_execlpe);
DEFINE_PUBLIC_ALIAS(DOS$execlpe, libd_execlpe);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_execlpe, libc_execlpe);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(execlpe, libc_execlpe);
DEFINE_PUBLIC_ALIAS(__ttyname, libc_ttyname);
DEFINE_PUBLIC_ALIAS(ttyname, libc_ttyname);
DEFINE_PUBLIC_ALIAS(getlogin, libc_getlogin);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && (!defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__)
DEFINE_PUBLIC_ALIAS(write_printer, libc_write_printer);
#endif /* !__KERNEL__ && (!__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__) */
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_isatty, libc_isatty);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__isatty, libc_isatty);
DEFINE_PUBLIC_ALIAS(isatty, libc_isatty);
DEFINE_PUBLIC_ALIAS(DOS$get_current_dir_name, libd_get_current_dir_name);
DEFINE_PUBLIC_ALIAS(get_current_dir_name, libc_get_current_dir_name);
DEFINE_PUBLIC_ALIAS(group_member, libc_group_member);
DEFINE_PUBLIC_ALIAS(usleep, libc_usleep);
DEFINE_PUBLIC_ALIAS(DOS$getwd, libd_getwd);
DEFINE_PUBLIC_ALIAS(getwd, libc_getwd);
DEFINE_PUBLIC_ALIAS(ualarm, libc_ualarm);
DEFINE_PUBLIC_ALIAS(__getpagesize, libc_getpagesize);
DEFINE_PUBLIC_ALIAS(getpagesize, libc_getpagesize);
DEFINE_PUBLIC_ALIAS(__getdtablesize, libc_getdtablesize);
DEFINE_PUBLIC_ALIAS(getdtablesize, libc_getdtablesize);
DEFINE_PUBLIC_ALIAS(getlogin_r, libc_getlogin_r);
DEFINE_PUBLIC_ALIAS(getpassphrase, libc_getpass);
DEFINE_PUBLIC_ALIAS(getpass, libc_getpass);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_swab, libc_swab);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(swab, libc_swab);
DEFINE_PUBLIC_ALIAS(ctermid, libc_ctermid);
DEFINE_PUBLIC_ALIAS(cuserid, libc_cuserid);
DEFINE_PUBLIC_ALIAS(getpassfd, libc_getpassfd);
DEFINE_PUBLIC_ALIAS(getpass_r, libc_getpass_r);
DEFINE_PUBLIC_ALIAS(getpeereid, libc_getpeereid);
DEFINE_PUBLIC_ALIAS(closefrom, libc_closefrom);
DEFINE_PUBLIC_ALIAS(fchroot, libc_fchroot);
DEFINE_PUBLIC_ALIAS(DOS$resolvepath, libd_resolvepath);
DEFINE_PUBLIC_ALIAS(resolvepath, libc_resolvepath);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_tell, libc_tell);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(tell, libc_tell);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_telli64, libc_tell64);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(tell64, libc_tell64);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_UNISTD_C */
