/* HASH CRC-32:0xdd961f3f */
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
#ifndef GUARD_LIBC_AUTO_PROCESS_C
#define GUARD_LIBC_AUTO_PROCESS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/process.h"
#include "../user/stdlib.h"
#include "../user/string.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.sched.thread") void
NOTHROW_NCX(LIBCCALL libc__endthread)(void) {
	libc__endthreadex(0);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.process") void
(LIBCCALL libc__c_exit)(void) THROWS(...) {
}
#include <local/environ.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBCCALL libc_spawnv)(int mode,
                                  char const *__restrict path,
                                  __TARGV) {
	return libc_spawnve(mode, path, ___argv, __LOCAL_environ);
}
#include <local/environ.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBCCALL libc_spawnvp)(int mode,
                                   char const *__restrict file,
                                   __TARGV) {
	return libc_spawnvpe(mode, file, ___argv, __LOCAL_environ);
}
#include <hybrid/typecore.h>
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__spawnvpe_impl) __ATTR_NOINLINE __ATTR_NONNULL((2, 4, 6, 7)) pid_t
(__LIBCCALL __spawnvpe_impl)(int mode,
                             char const *__restrict path, size_t path_len,
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
	dst = (char *)mempcpyc(fullpath, path, path_len, sizeof(char));
	*dst++ = '/';
	dst = (char *)mempcpyc(dst, file, file_len, sizeof(char));
	*dst = '\0';
	return spawnve(mode, fullpath, ___argv, ___envp);
}
__NAMESPACE_LOCAL_END
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBCCALL libc_spawnvpe)(int mode,
                                    char const *__restrict file,
                                    __TARGV,
                                    __TENVP) {
	size_t filelen = libc_strlen(file);
	char *env_path = libc_getenv("PATH");
	if (env_path && *env_path) {
		for (;;) {
			pid_t result;
			char *path_end;
#ifdef _WIN32
			path_end = libc_strchrnul(env_path, ';');
#else /* _WIN32 */
			path_end = libc_strchrnul(env_path, ':');
#endif /* !_WIN32 */
			result = (__NAMESPACE_LOCAL_SYM __spawnvpe_impl)(mode, env_path, (size_t)(path_end - env_path),
			                                                 file, filelen, ___argv, ___envp);
			if (result >= 0)
				return result;
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
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnl)(int mode,
                                   char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_SPAWNL(char, libc_spawnv, mode, path, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnl)(int mode,
                                   char const *__restrict path,
                                   char const *args,
                                   ...) {
	__REDIRECT_SPAWNL(char, libc_spawnv, mode, path, args)
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnlp)(int mode,
                                    char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char, libc_spawnvp, mode, file, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnlp)(int mode,
                                    char const *__restrict file,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char, libc_spawnvp, mode, file, args)
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnle)(int mode,
                                    char const *__restrict path,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnve, mode, path, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnle)(int mode,
                                    char const *__restrict path,
                                    char const *args,
                                    ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnve, mode, path, args)
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_spawnlpe)(int mode,
                                     char const *__restrict file,
                                     char const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnvpe, mode, file, args)
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBCCALL libc_spawnlpe)(int mode,
                                     char const *__restrict file,
                                     char const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char, libc_spawnvpe, mode, file, args)
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_endthread, libc__endthread);
DEFINE_PUBLIC_ALIAS(_c_exit, libc__c_exit);
DEFINE_PUBLIC_ALIAS(_spawnv, libc_spawnv);
DEFINE_PUBLIC_ALIAS(spawnv, libc_spawnv);
DEFINE_PUBLIC_ALIAS(_spawnvp, libc_spawnvp);
DEFINE_PUBLIC_ALIAS(spawnvp, libc_spawnvp);
DEFINE_PUBLIC_ALIAS(_spawnvpe, libc_spawnvpe);
DEFINE_PUBLIC_ALIAS(spawnvpe, libc_spawnvpe);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_spawnl, libd_spawnl);
DEFINE_PUBLIC_ALIAS(DOS$spawnl, libd_spawnl);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_spawnl, libc_spawnl);
DEFINE_PUBLIC_ALIAS(spawnl, libc_spawnl);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_spawnlp, libd_spawnlp);
DEFINE_PUBLIC_ALIAS(DOS$spawnlp, libd_spawnlp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_spawnlp, libc_spawnlp);
DEFINE_PUBLIC_ALIAS(spawnlp, libc_spawnlp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_spawnle, libd_spawnle);
DEFINE_PUBLIC_ALIAS(DOS$spawnle, libd_spawnle);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_spawnle, libc_spawnle);
DEFINE_PUBLIC_ALIAS(spawnle, libc_spawnle);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_spawnlpe, libd_spawnlpe);
DEFINE_PUBLIC_ALIAS(DOS$spawnlpe, libd_spawnlpe);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_spawnlpe, libc_spawnlpe);
DEFINE_PUBLIC_ALIAS(spawnlpe, libc_spawnlpe);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PROCESS_C */
