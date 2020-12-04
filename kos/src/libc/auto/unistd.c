/* HASH CRC-32:0x9630f162 */
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
#ifndef GUARD_LIBC_AUTO_UNISTD_C
#define GUARD_LIBC_AUTO_UNISTD_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/unistd.h"
#include "../user/fcntl.h"
#include "../user/pwd.h"
#include "../user/stdlib.h"
#include "../user/string.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
#include <libc/local/environ.h>
/* >> execv(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_execv)(char const *__restrict path,
                                 __TARGV) {
	return libc_execve(path, ___argv, __LOCAL_environ);
}
#include <libc/local/environ.h>
/* >> execvp(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_execvp)(char const *__restrict file,
                                  __TARGV) {
	return libc_execvpe(file, ___argv, __LOCAL_environ);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
/* >> execl(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
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
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
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
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
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
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list,
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
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
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
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list */
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
 * Replace the calling process with the application image referred to by `FILE'
 * and execute it's `main()' method, passing the given `ARGV', and setting `environ' to `ENVP' */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBCCALL libc_execvpe)(char const *__restrict file,
                                   __TARGV,
                                   __TENVP) {
	char *env_path;
	/* [...]
	 * If the specified filename includes a slash character,
	 * then $PATH is ignored, and the file at the specified
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
		__libc_seterrno(ENOENT);
#endif /* ENOENT */
	}
	return -1;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
/* >> execlpe(3)
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
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
 * Replace the calling process with the application image referred to by `PATH' / `FILE'
 * and execute it's `main()' method, passing the list of NULL-terminated `ARGS'-list, and setting `environ' to a `char **' passed after the NULL sentinel */
INTERN ATTR_SECTION(".text.crt.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBCCALL libc_execlpe)(char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_EXECLE(char, libc_execvpe, file, args)
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
/* >> getpagesize(3)
 * Return the size of a PAGE (in bytes) */
INTERN ATTR_SECTION(".text.crt.system.configuration") ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_getpagesize)(void) {
	return __ARCH_PAGESIZE;
}
INTERN ATTR_SECTION(".text.crt.system.configuration") ATTR_CONST WUNUSED __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_getdtablesize)(void) {
#if defined(__KOS__)
	return 0x7fffffff; /* INT_MAX */
#elif defined(__linux__) || defined(__linux) || defined(linux)
	return 0x10000;    /* UINT16_MAX + 1 */
#else
	return 256;        /* UINT8_MAX + 1 */
#endif
}
#include <bits/crt/db/passwd.h>
/* >> getlogin_r(3)
 * Reentrant version of `getlogin()'. May truncate the name if it's longer than `name_len'
 * s.a. `getlogin()' and `cuserid()' */
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_getlogin_r)(char *name,
                                      size_t name_len) {
#if defined(__CRT_HAVE_getpwuid_r) && defined(__CRT_HAVE_geteuid)
	char buf[1024]; /* NSS_BUFLEN_PASSWD */
	struct passwd pwent, *pwptr;
#endif /* __CRT_HAVE_getpwuid_r && __CRT_HAVE_geteuid */
	char *pwname;
#if defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)
	pwname = libc_getenv("LOGNAME");
#if defined(__CRT_HAVE_getpwuid_r) && defined(__CRT_HAVE_geteuid)
	if (!pwname)
#endif /* __CRT_HAVE_getpwuid_r && __CRT_HAVE_geteuid */
#endif /* __CRT_HAVE_getenv || __LOCAL_environ */
#if defined(__CRT_HAVE_getpwuid_r) && defined(__CRT_HAVE_geteuid)
	{
		if (libc_getpwuid_r(libc_geteuid(), &pwent, buf,
		               sizeof(buf), &pwptr) ||
		    pwptr == NULL)
			return -1;
		pwname = pwptr->pw_name;
		if (!pwname)
			return -1;
	}
#endif /* __CRT_HAVE_getpwuid_r && __CRT_HAVE_geteuid */
	if (name_len) {
		name[name_len - 1] = '\0';
		libc_strncpy(name, pwname, name_len - 1);
	}
	return 0;
}
/* Copy `n_bytes & ~1' (FLOOR_ALIGN(n_bytes, 2)) from `from' to `to',
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
 * a writable data location that contains that same string. */
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
 * that name in `s'. When `s' is NULL, a static buffer is used instead
 * When given, `s' must be a buffer of at least `L_cuserid' bytes.
 * If the actual username is longer than this, it may be truncated, and programs
 * that wish to support longer usernames should make use of `getlogin_r()' instead.
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
/* Close all file descriptors with indices `>= lowfd' (s.a. `fcntl(F_CLOSEM)') */
INTERN ATTR_SECTION(".text.crt.bsd.io.access") void
NOTHROW_NCX(LIBCCALL libc_closefrom)(fd_t lowfd) {
	libc_fcntl(lowfd, __F_CLOSEM);
}
#include <asm/os/fcntl.h>
/* Change the root directory to `fd'. If `fd' was opened before a prior call to `chroot()',
 * and referrs to a directory, then this function can be used to escape a chroot() jail.
 * No special permissions are required to use this function, since a malicious application
 * could achieve the same behavior by use of `*at' system calls, using `fd' as `dfd' argument. */
INTERN ATTR_SECTION(".text.crt.solaris") int
NOTHROW_NCX(LIBCCALL libc_fchroot)(fd_t fd) {
	fd_t result;
	result = libc_dup2(fd, __AT_FDROOT);
	if likely(result >= 0)
		result = 0;
	return result;
}
#include <libc/errno.h>
/* Similar to `frealpathat(2)' (though use the later for more options)
 * Also note that this function appears to have a weird rule (which KOS simply
 * ignores) that is related to this function not writing more than `PATH_MAX'
 * bytes to `buf'. (Why??? I mean: The whole point of having a `buflen' argument
 * is to be able to handle names of arbitrary lengths)
 * Additionally, the online docs don't mention what happens when `buflen' is too
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
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	if unlikely(!resolved)
		libc_free(result);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return retval;
}
#include <asm/os/stdio.h>
/* Return the current file position (alias for `lseek(fd, 0, SEEK_CUR)') */
INTERN ATTR_SECTION(".text.crt.solaris") WUNUSED off_t
NOTHROW_NCX(LIBCCALL libc_tell)(fd_t fd) {
	return libc_lseek(fd, 0, SEEK_CUR);
}
#include <asm/os/stdio.h>
/* Return the current file position (alias for `lseek64(fd, 0, SEEK_CUR)') */
INTERN ATTR_SECTION(".text.crt.solaris") WUNUSED off64_t
NOTHROW_NCX(LIBCCALL libc_tell64)(fd_t fd) {
	return libc_lseek64(fd, 0, __SEEK_CUR);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_execv, libc_execv);
DEFINE_PUBLIC_ALIAS(execv, libc_execv);
DEFINE_PUBLIC_ALIAS(_execvp, libc_execvp);
DEFINE_PUBLIC_ALIAS(execvp, libc_execvp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_execl, libd_execl);
DEFINE_PUBLIC_ALIAS(DOS$execl, libd_execl);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_execl, libc_execl);
DEFINE_PUBLIC_ALIAS(execl, libc_execl);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_execle, libd_execle);
DEFINE_PUBLIC_ALIAS(DOS$execle, libd_execle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_execle, libc_execle);
DEFINE_PUBLIC_ALIAS(execle, libc_execle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_execlp, libd_execlp);
DEFINE_PUBLIC_ALIAS(DOS$execlp, libd_execlp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_execlp, libc_execlp);
DEFINE_PUBLIC_ALIAS(execlp, libc_execlp);
DEFINE_PUBLIC_ALIAS(_execvpe, libc_execvpe);
DEFINE_PUBLIC_ALIAS(execvpe, libc_execvpe);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_execlpe, libd_execlpe);
DEFINE_PUBLIC_ALIAS(DOS$execlpe, libd_execlpe);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_execlpe, libc_execlpe);
DEFINE_PUBLIC_ALIAS(execlpe, libc_execlpe);
DEFINE_PUBLIC_ALIAS(getlogin, libc_getlogin);
DEFINE_PUBLIC_ALIAS(__getpagesize, libc_getpagesize);
DEFINE_PUBLIC_ALIAS(getpagesize, libc_getpagesize);
DEFINE_PUBLIC_ALIAS(getdtablesize, libc_getdtablesize);
DEFINE_PUBLIC_ALIAS(getlogin_r, libc_getlogin_r);
DEFINE_PUBLIC_ALIAS(_swab, libc_swab);
DEFINE_PUBLIC_ALIAS(swab, libc_swab);
DEFINE_PUBLIC_ALIAS(ctermid, libc_ctermid);
DEFINE_PUBLIC_ALIAS(cuserid, libc_cuserid);
DEFINE_PUBLIC_ALIAS(closefrom, libc_closefrom);
DEFINE_PUBLIC_ALIAS(fchroot, libc_fchroot);
DEFINE_PUBLIC_ALIAS(resolvepath, libc_resolvepath);
DEFINE_PUBLIC_ALIAS(_tell, libc_tell);
DEFINE_PUBLIC_ALIAS(tell, libc_tell);
DEFINE_PUBLIC_ALIAS(_telli64, libc_tell64);
DEFINE_PUBLIC_ALIAS(tell64, libc_tell64);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_UNISTD_C */
