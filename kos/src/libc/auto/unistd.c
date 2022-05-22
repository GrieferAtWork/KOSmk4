/* HASH CRC-32:0x5c1c2efc */
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
#include "string.h"
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int
NOTHROW_RPC(LIBDCALL libd_execv)(char const *__restrict path,
                                 __TARGV) {
	return libd_execve(path, ___argv, __LOCAL_environ);
}
#include <libc/template/environ.h>
/* >> execv(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int
NOTHROW_RPC(LIBCCALL libc_execv)(char const *__restrict path,
                                 __TARGV) {
	return libc_execve(path, ___argv, __LOCAL_environ);
}
#include <libc/template/environ.h>
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int
NOTHROW_RPC(LIBDCALL libd_execvp)(char const *__restrict file,
                                  __TARGV) {
	return libd_execvpe(file, ___argv, __LOCAL_environ);
}
#include <libc/template/environ.h>
/* >> execvp(3)
 * Replace the calling  process with  the application  image referred  to by  `path' /  `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) int
NOTHROW_RPC(LIBCCALL libc_execvp)(char const *__restrict file,
                                  __TARGV) {
	return libc_execvpe(file, ___argv, __LOCAL_environ);
}
#include <parts/redirect-exec.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_SENTINEL ATTR_ACCESS_RO(1) ATTR_ACCESS_RO_OPT(2) int
NOTHROW_RPC(VLIBDCALL libd_execl)(char const *__restrict path,
                                  char const *args,
                                  ...) {
	__REDIRECT_EXECL(char, libd_execv, path, args)
}
#include <parts/redirect-exec.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_SENTINEL ATTR_ACCESS_RO(1) ATTR_ACCESS_RO_OPT(2) int
NOTHROW_RPC(VLIBCCALL libc_execl)(char const *__restrict path,
                                  char const *args,
                                  ...) {
	__REDIRECT_EXECL(char, libc_execv, path, args)
}
#include <parts/redirect-exec.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_ACCESS_RO(1) ATTR_ACCESS_RO_OPT(2) ATTR_SENTINEL_O(1) int
NOTHROW_RPC(VLIBDCALL libd_execle)(char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_EXECLE(char, libd_execve, path, args)
}
#include <parts/redirect-exec.h>
/* >> execle(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_ACCESS_RO(1) ATTR_ACCESS_RO_OPT(2) ATTR_SENTINEL_O(1) int
NOTHROW_RPC(VLIBCCALL libc_execle)(char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_EXECLE(char, libc_execve, path, args)
}
#include <parts/redirect-exec.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_SENTINEL ATTR_ACCESS_RO(1) ATTR_ACCESS_RO_OPT(2) int
NOTHROW_RPC(VLIBDCALL libd_execlp)(char const *__restrict file,
                                   char const *args,
                                   ...) {
	__REDIRECT_EXECL(char, libd_execvp, file, args)
}
#include <parts/redirect-exec.h>
/* >> execlp(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's  `main()' method,  passing the list  of NULL-terminated  `args'-list */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_SENTINEL ATTR_ACCESS_RO(1) ATTR_ACCESS_RO_OPT(2) int
NOTHROW_RPC(VLIBCCALL libc_execlp)(char const *__restrict file,
                                   char const *args,
                                   ...) {
	__REDIRECT_EXECL(char, libc_execvp, file, args)
}
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__dos_execvpe_impl) __ATTR_NOINLINE __ATTR_NONNULL((1, 3, 5, 6)) int
(__LIBCCALL __dos_execvpe_impl)(char const *__restrict path, size_t path_len,
                                char const *__restrict file, size_t file_len,
                                __TARGV, __TENVP) {
	char *fullpath, *dst;
	while (path_len && (path[path_len - 1] == '/' ||
	                    path[path_len - 1] == '\\'))
		--path_len;
	fullpath = (char *)__hybrid_alloca((path_len + 1 + file_len + 1) *
	                                   sizeof(char));
	dst = (char *)libc_mempcpyc(fullpath, path, path_len, sizeof(char));
	*dst++ = '/';
	dst = (char *)libc_mempcpyc(dst, file, file_len, sizeof(char));
	*dst = '\0';
	return libd_execve(fullpath, ___argv, ___envp);
}
__NAMESPACE_LOCAL_END
/* >> execvpe(3)
 * Replace the  calling process  with the  application  image referred  to by  `file'  and
 * execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) ATTR_ACCESS_RO(3) int
NOTHROW_RPC(LIBDCALL libd_execvpe)(char const *__restrict file,
                                   __TARGV,
                                   __TENVP) {
	char *env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the  specified
	 * pathname is executed.
	 * [...] */
	if (libc_strchr(file, '/') || libc_strchr(file, '\\'))
		return libc_execve(file, ___argv, ___envp);
	env_path = libc_getenv("PATH");
	if (env_path && *env_path) {
		size_t filelen;
		filelen = libc_strlen(file);
		for (;;) {
			char *path_end;
			path_end = libc_strchrnul(env_path, ';');
			(__NAMESPACE_LOCAL_SYM __dos_execvpe_impl)(env_path, (size_t)(path_end - env_path),
			                                           file, filelen, ___argv, ___envp);
			if (!*path_end)
				break;
			env_path = path_end + 1;
		}
	} else {

		(void)libc_seterrno(ENOENT);

	}
	return -1;
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
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_ACCESS_RO(1) ATTR_ACCESS_RO(2) ATTR_ACCESS_RO(3) int
NOTHROW_RPC(LIBCCALL libc_execvpe)(char const *__restrict file,
                                   __TARGV,
                                   __TENVP) {
	char *env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the  specified
	 * pathname is executed.
	 * [...] */




	if (libc_strchr(file, '/'))
		return libc_execve(file, ___argv, ___envp);

	env_path = libc_getenv("PATH");
	if (env_path && *env_path) {
		size_t filelen;
		filelen = libc_strlen(file);
		for (;;) {
			char *path_end;



			path_end = libc_strchrnul(env_path, ':');

			(__NAMESPACE_LOCAL_SYM __execvpe_impl)(env_path, (size_t)(path_end - env_path),
			                                       file, filelen, ___argv, ___envp);
			if (!*path_end)
				break;
			env_path = path_end + 1;
		}
	} else {

		(void)libc_seterrno(ENOENT);

	}
	return -1;
}
#include <parts/redirect-exec.h>
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.exec.exec") ATTR_ACCESS_RO(1) ATTR_ACCESS_RO_OPT(2) ATTR_SENTINEL_O(1) int
NOTHROW_RPC(VLIBDCALL libd_execlpe)(char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_EXECLE(char, libd_execvpe, file, args)
}
#include <parts/redirect-exec.h>
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and  execute it's `main()'  method, passing the  list of NULL-terminated `args'-list,
 * and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_ACCESS_RO(1) ATTR_ACCESS_RO_OPT(2) ATTR_SENTINEL_O(1) int
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
	if likely(libc_ttyname_r(fd, buf, COMPILER_LENOF(buf)) == 0)
		return buf;
	return NULL;
}
/* >> getlogin(3)
 * Return the login name for the current user, or `NULL' on error.
 * s.a. `getlogin_r()' and `cuserid()' */
INTERN ATTR_SECTION(".text.crt.io.tty") WUNUSED char *
NOTHROW_NCX(LIBCCALL libc_getlogin)(void) {

	char *result = libc_getenv("LOGNAME");
	if (!result)
		result = libc_cuserid(NULL);
	return result;





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
INTERN ATTR_SECTION(".text.crt.io.write") ATTR_ACCESS_ROS(2, 3) ssize_t
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

	return libc_ioctl(fd, __TCGETA, &ios) < 0 ? 0 : 1;



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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.basic_property") ATTR_MALLOC WUNUSED char *
NOTHROW_RPC(LIBDCALL libd_get_current_dir_name)(void) {

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

	struct timespec ts;
	ts.tv_sec  = (time_t)(useconds / __UINT32_C(1000000));
	ts.tv_nsec = (syscall_ulong_t)(useconds % __UINT32_C(1000000)) * __UINT16_C(1000);
	return libc_nanosleep(&ts, NULL);




}
/* >> getwd(3)
 * Deprecated, alternate variant  of `getcwd()'.  It
 * should be obvious why you shouldn't use this one.
 * And  if it isn't, take a look at the arguments of
 * this function, compared to `getcwd()' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.basic_property") ATTR_ACCESS_WR(1) ATTR_DEPRECATED("Use getcwd()") char *
NOTHROW_RPC(LIBDCALL libd_getwd)(char *buf) {
	return libd_getcwd(buf, (size_t)-1);
}
/* >> getwd(3)
 * Deprecated, alternate variant  of `getcwd()'.  It
 * should be obvious why you shouldn't use this one.
 * And  if it isn't, take a look at the arguments of
 * this function, compared to `getcwd()' */
INTERN ATTR_SECTION(".text.crt.fs.basic_property") ATTR_ACCESS_WR(1) ATTR_DEPRECATED("Use getcwd()") char *
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
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_ACCESS_WRS(1, 2) int
NOTHROW_RPC(LIBCCALL libc_getlogin_r)(char *name,
                                      size_t name_len) {

	char buf[1024]; /* NSS_BUFLEN_PASSWD */
	struct passwd pwent, *pwptr;

	char *pwname;

	pwname = libc_getenv("LOGNAME");

	if (!pwname)



	{
		if (libc_getpwuid_r(libc_geteuid(), &pwent, buf,
		               sizeof(buf), &pwptr) ||
		    pwptr == NULL)
			return -1;
		pwname = pwptr->pw_name;
		if (!pwname)
			return -1;
	}

	if (name_len) {
		name[name_len - 1] = '\0';
		libc_strncpy(name, pwname, name_len - 1);
	}
	return 0;
}
#include <bits/os/sigaction.h>
#include <asm/os/signal.h>
/* >> daemon_setup(3)
 * Do the common setup required by `daemon(3)' and `daemonfd(3)' */
INTERN ATTR_SECTION(".text.crt.system.utility") int
NOTHROW_RPC(LIBCCALL libc_daemon_setup)(void) {
	int result;

	int has_old_sa;
	struct sigaction new_sa, old_sa;
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
	libc_sigemptyset(&new_sa.sa_mask);
	new_sa.sa_handler = (__sighandler_t)__SIG_IGN;
	new_sa.sa_flags   = 0;
	has_old_sa = libc_sigaction(__SIGHUP, &new_sa, &old_sa);

	{
		pid_t cpid = libc_fork();
		if unlikely(cpid < 0)
			return cpid;
		if (cpid != 0)
			libc__Exit(0); /* The parent process dies. */
	}
	result = libc_setsid();

	if (has_old_sa == 0)
		libc_sigaction(__SIGHUP, &old_sa, NULL);

	return result;
}
#include <paths.h>
/* >> daemon(3), daemonfd(3) */
INTERN ATTR_SECTION(".text.crt.system.utility") int
NOTHROW_RPC(LIBCCALL libc_daemon)(int nochdir,
                                  int noclose) {
	int error = libc_daemon_setup();
	if likely(error == 0) {
		if (!nochdir)
			(void)libc_chdir("/");
		if (!noclose) {
			fd_t i, nul = libc_open(_PATH_DEVNULL, O_RDWR);
			if unlikely(nul < 0)
				return nul;
			/* NOTE: Glibc does an additional check to ensure that `nul'  really
			 *       is a character-device with the  correct dev_t. We could  do
			 *       that as well, however I'd consider a system where /dev/null
			 *       isn't actually /dev/null to  already be broken... (and  the
			 *       check only adds unnecessary overhead if you ask me) */
			for (i = 0; i < 3; ++i) {
				if (nul != i)
					(void)libc_dup2(nul, i);
			}

			if (nul >= 3)
				(void)libc_close(nul);

		}
	}
	return error;
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
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_ACCESS_ROS(1, 3) ATTR_ACCESS_WRS(2, 3) void
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
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_ACCESS_WR_OPT(1) char *
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
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED ATTR_ACCESS_RO_OPT(1) ATTR_ACCESS_RO_OPT(4) ATTR_ACCESS_WR_OPT(2) char *
NOTHROW_RPC(LIBCCALL libc_getpassfd)(char const *prompt,
                                     char *buf,
                                     size_t buflen,
                                     fd_t fds[3],
                                     __STDC_INT_AS_UINT_T flags,
                                     int timeout_in_seconds) {








	bool heap_buf;

	char *result;
	fd_t default_fds[3];
	signo_t interrupt_signo;

	/* Initialize locals. */

	struct termios old_ios, new_ios;
	libc_memset(&old_ios, -1, sizeof(old_ios));
	libc_memset(&new_ios, -1, sizeof(new_ios));

	result          = NULL;
	interrupt_signo = 0;
	default_fds[0]  = __STDIN_FILENO;

	/* Allocate a dynamic buffer if none was given by the caller. */

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

	if (buflen < 1) {
		/* Invalid buffer length */

		(void)libc_seterrno(EINVAL);

		goto out;
	}

	/* Open input files if not provided by the caller. */
	if (!fds) {
		fds = default_fds;


#define __PRIVATE_GETPASSFD_O_CLOEXEC __O_CLOEXEC




#define __PRIVATE_GETPASSFD_O_CLOFORK __O_CLOFORK




#define __PRIVATE_GETPASSFD_O_RDWR __O_RDWR




#define __PRIVATE_GETPASSFD_O_NONBLOCK __O_NONBLOCK



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

		{
			default_fds[1] = __STDERR_FILENO;
			default_fds[2] = __STDERR_FILENO;
		}
	}

	/* Load terminal settings. */

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

#ifdef __TCSASOFT
		if (libc_tcsetattr(fds[0], __TCSAFLUSH | __TCSASOFT, &new_ios) != 0)
#else /* __TCSASOFT */
		if (libc_tcsetattr(fds[0], __TCSAFLUSH, &new_ios) != 0)


#endif /* !__TCSASOFT */
		{
			goto out;
		}
	} else {
		if (flags & __GETPASS_NEED_TTY)
			goto out; /* tcgetattr() should have already set errno=ENOTTY */
	}





	/* Print the given prompt */

	if (prompt && *prompt) {
		if (libc_write(fds[1], prompt, libc_strlen(prompt)) == -1)
			goto out;
	}




	/* The actual interpreter loop for the password reader: */
	{
		unsigned char ch, *dst, *bufend;
#ifdef __VLNEXT
		bool escape; /* Set to `true' if the next character is escaped. */
		escape = false;
#endif /* __VLNEXT */
		dst    = (unsigned char *)buf;
		bufend = (unsigned char *)buf + buflen - 1;
		for (;;) {


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

					(void)libc_seterrno(ETIMEDOUT);



					goto out; /* Timeout... */
				}
				/* Assume that data can be read now! */
			}




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

						(void)libc_seterrno(ENODATA);

						goto out;
					}
					break;
				}
			}

#ifdef __VLNEXT
			if (escape) {
				/* Unconditionally add `ch' */
				escape = false;
			} else
#endif /* __VLNEXT */
			{

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

					if (flags & (__GETPASS_ECHO | __GETPASS_ECHO_STAR)) {
						while (dst > (unsigned char *)buf) {
							if (libc_write(fds[1], "\b \b", 3 * sizeof(char)) == -1)
								goto out;
							--dst;
						}
					}

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
#ifdef __VINTR
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VINTR, 'C')) {
					interrupt_signo = __SIGINT;
					goto out;
				}
#endif /* __VINTR */

#ifdef __VQUIT
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VQUIT, '\\')) {
					interrupt_signo = __SIGQUIT;
					goto out;
				}
#endif /* __VQUIT */

#if defined(__VSUSP) || defined(__VDSUSP)
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
#endif /* __VSUSP || __VDSUSP */

				/* Check for custom newline characters. */
#ifdef __VEOL
				if (new_ios.c_cc[__VEOL] != __VDISABLE && ch == new_ios.c_cc[__VEOL])
					break;
#endif /* __VEOL */
#ifdef __VEOL2
				if (new_ios.c_cc[__VEOL2] != __VDISABLE && ch == new_ios.c_cc[__VEOL2])
					break;
#endif /* __VEOL2 */


				/* Check for single-character erase (backspace) */
#ifdef __VERASE
				if (ch == __PRIVATE_GETPASSFD_CTRL(__VERASE, 'H'))
#else /* __VERASE */
				if (ch == '\b')
#endif /* !__VERASE */
				{
					if (dst > (unsigned char *)buf) {
						--dst;
						__libc_explicit_bzero(dst, sizeof(char));

						if (flags & (__GETPASS_ECHO | __GETPASS_ECHO_STAR)) {
							if (libc_write(fds[1], "\b \b", 3 * sizeof(char)) == -1)
								goto out;
						}

						continue;
					}
maybe_beep:

					if (!(flags & __GETPASS_NO_BEEP)) {
						if (libc_write(fds[2], "\7" /*BEL*/, sizeof(char)) == -1)
							goto out;
					}

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

					libc_free(buf);

					dst    = (unsigned char *)new_buf + (size_t)(dst - (unsigned char *)buf);
					bufend = (unsigned char *)new_buf + new_buflen - 1;
					buf    = new_buf;
				} else

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


			if (flags & __GETPASS_ECHO_STAR) {
				if (libc_write(fds[1], "*", sizeof(char)) == -1)
					goto out;
			} else if (flags & __GETPASS_ECHO) {
				if (!libc_isprint((char)ch))
					ch = (unsigned char)'?';
				if (libc_write(fds[1], &ch, sizeof(char)) == -1)
					goto out;
			}


		} /* for (;;) */

		/* If requested to do so by the caller, write a trailing '\n' upon success. */

		if (flags & __GETPASS_ECHO_NL) {
			if (libc_write(fds[1], "\n", 1) == -1)
				goto out;
		}


		/* Force NUL-termination of the password buffer. */
		*dst = '\0';


		if (heap_buf && dst < bufend) {
			/* Try to release unused buffer memory. */
			size_t new_buflen;
			char *new_buf;
			new_buflen = (size_t)((dst + 1) - (unsigned char *)buf);
			new_buf    = (char *)libc_malloc(new_buflen * sizeof(char));
			if likely(new_buf) {
				libc_memcpyc(new_buf, buf, new_buflen, sizeof(char));
				__libc_explicit_bzero(buf, buflen * sizeof(char));

				libc_free(buf);

				buf    = new_buf;
				buflen = new_buflen;
			}
		}


		/* Indicate success! */
		result = buf;
	}
out:

	/* Restore old terminal settings. */

	if (libc_memcmp(&old_ios, &new_ios, sizeof(struct termios)) != 0) {
#ifdef __TCSASOFT
		(void)libc_tcsetattr(fds[0], __TCSAFLUSH | __TCSASOFT, &old_ios);
#else /* __TCSASOFT */
		(void)libc_tcsetattr(fds[0], __TCSAFLUSH, &old_ios);


#endif /* !__TCSASOFT */
	}


	/* Close our file handle to /dev/tty */

	if (default_fds[0] != __STDIN_FILENO)
		libc_close(default_fds[0]);


	/* Error-only cleanup... */
	if (!result) {

		/* Don't leave a (possibly incomplete) password dangling in-memory! */
		__libc_explicit_bzero(buf, buflen * sizeof(char));

		/* Free a dynamically allocated password buffer. */

		if (heap_buf)
			libc_free(buf);


		/* Raise the signal of a given control character, and/or set
		 * `errno'  to indicate that the password-read operation was
		 * interrupted. */
		if (interrupt_signo != 0) {

			if (!(flags & __GETPASS_NO_SIGNAL))
				(void)libc_raise(interrupt_signo);


			(void)libc_seterrno(EINTR);

		}
	}
	return result;
}
#include <asm/crt/getpassfd.h>
#include <asm/crt/readpassphrase.h>
/* >> getpass_r(3) */
INTERN ATTR_SECTION(".text.crt.sched.user") WUNUSED ATTR_ACCESS_RO_OPT(1) ATTR_ACCESS_WR_OPT(2) char *
NOTHROW_RPC(LIBCCALL libc_getpass_r)(char const *prompt,
                                     char *buf,
                                     size_t bufsize) {

	/* Prefer using `getpassfd(3)' because I feel like that one's more
	 * user-friendly.  - But if it's not available, fall back on using
	 * the regular, old `readpassphrase(3)' */
#ifdef __GETPASS_ECHO_NL
	return libc_getpassfd(prompt, buf, bufsize, NULL, __GETPASS_ECHO_NL, 0);
#else /* __GETPASS_ECHO_NL */
	return libc_getpassfd(prompt, buf, bufsize, NULL, 0, 0);
#endif /* !__GETPASS_ECHO_NL */







}
#include <bits/os/ucred.h>
#include <libc/errno.h>
/* >> getpeereid(3)
 * Convenience wrapper for `getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED)' */
INTERN ATTR_SECTION(".text.crt.sched.user") ATTR_ACCESS_WR(2) ATTR_ACCESS_WR(3) int
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

			result = libc_seterrno(ENOPROTOOPT);



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

	libc_fcntl(lowfd, __F_CLOSEM);



}
#include <libc/template/__libc_enable_secure.h>
/* >> issetugid(3)
 * Check if the calling program is running under setuid-mode
 * Hint: simply returns the value of `__libc_enable_secure(3)'. */
INTERN ATTR_SECTION(".text.crt.sched.user") ATTR_PURE WUNUSED int
NOTHROW_NCX(LIBCCALL libc_issetugid)(void) {
	return __LOCAL___libc_enable_secure;
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.solaris") ATTR_ACCESS_RO(1) ATTR_ACCESS_WRS(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd_resolvepath)(char const *filename,
                                       char *resolved,
                                       size_t buflen) {
	__STDC_INT_AS_SSIZE_T retval;
	char *result;
	result = libd_frealpathat(__AT_FDCWD, filename, resolved, buflen, 0);
	if unlikely(!result)
		return -1;
	retval = (__STDC_INT_AS_SSIZE_T)libc_strlen(result);

	if unlikely(!resolved)
		libc_free(result);

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
INTERN ATTR_SECTION(".text.crt.solaris") ATTR_ACCESS_RO(1) ATTR_ACCESS_WRS(2, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc_resolvepath)(char const *filename,
                                       char *resolved,
                                       size_t buflen) {
	__STDC_INT_AS_SSIZE_T retval;
	char *result;
	result = libc_frealpathat(__AT_FDCWD, filename, resolved, buflen, 0);
	if unlikely(!result)
		return -1;
	retval = (__STDC_INT_AS_SSIZE_T)libc_strlen(result);

	if unlikely(!resolved)
		libc_free(result);

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
DEFINE_PUBLIC_ALIAS(DOS$_execv, libd_execv);
DEFINE_PUBLIC_ALIAS(DOS$execv, libd_execv);
DEFINE_PUBLIC_ALIAS(execv, libc_execv);
DEFINE_PUBLIC_ALIAS(DOS$_execvp, libd_execvp);
DEFINE_PUBLIC_ALIAS(DOS$execvp, libd_execvp);
DEFINE_PUBLIC_ALIAS(execvp, libc_execvp);
DEFINE_PUBLIC_ALIAS(DOS$_execl, libd_execl);
DEFINE_PUBLIC_ALIAS(DOS$execl, libd_execl);
DEFINE_PUBLIC_ALIAS(execl, libc_execl);
DEFINE_PUBLIC_ALIAS(DOS$_execle, libd_execle);
DEFINE_PUBLIC_ALIAS(DOS$execle, libd_execle);
DEFINE_PUBLIC_ALIAS(execle, libc_execle);
DEFINE_PUBLIC_ALIAS(DOS$_execlp, libd_execlp);
DEFINE_PUBLIC_ALIAS(DOS$execlp, libd_execlp);
DEFINE_PUBLIC_ALIAS(execlp, libc_execlp);
DEFINE_PUBLIC_ALIAS(DOS$_execvpe, libd_execvpe);
DEFINE_PUBLIC_ALIAS(DOS$execvpe, libd_execvpe);
DEFINE_PUBLIC_ALIAS(execvpe, libc_execvpe);
DEFINE_PUBLIC_ALIAS(DOS$_execlpe, libd_execlpe);
DEFINE_PUBLIC_ALIAS(DOS$execlpe, libd_execlpe);
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
DEFINE_PUBLIC_ALIAS(daemon, libc_daemon);
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
DEFINE_PUBLIC_ALIAS(issetugid, libc_issetugid);
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
