/* HASH CRC-32:0x95fd2da2 */
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
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_PROCESS_C
#define GUARD_LIBC_AUTO_PARTS_WCHAR_PROCESS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "parts.wchar.process.h"
#include "../user/process.h"
#include "../user/stdlib.h"
#include "uchar.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_wexecv)(char16_t const *__restrict path,
                                  __T16ARGV) {
	int result = -1;
	char *utf8_path, **utf8_argv;
	utf8_path = libd_convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto done;
	utf8_argv = libd_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	result = libc_execv(utf8_path, utf8_argv);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBKCALL libc_wexecv)(char32_t const *__restrict path,
                                  __T32ARGV) {
	int result = -1;
	char *utf8_path, **utf8_argv;
	utf8_path = libc_convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto done;
	utf8_argv = libc_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	result = libc_execv(utf8_path, utf8_argv);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd_wexecve)(char16_t const *__restrict path,
                                   __T16ARGV,
                                   __T16ENVP) {
	int result = -1;
	char *utf8_path, **utf8_argv, **utf8_envp;
	utf8_path = libd_convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto done;
	utf8_argv = libd_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	utf8_envp = NULL;
	if unlikely(___envp && (utf8_envp = libd_convert_wcstombsv(___envp)) == NULL)
		goto done_argv;
	result = libc_execve(utf8_path, utf8_argv, utf8_envp);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_envp);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_argv:
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBKCALL libc_wexecve)(char32_t const *__restrict path,
                                   __T32ARGV,
                                   __T32ENVP) {
	int result = -1;
	char *utf8_path, **utf8_argv, **utf8_envp;
	utf8_path = libc_convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto done;
	utf8_argv = libc_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	utf8_envp = NULL;
	if unlikely(___envp && (utf8_envp = libc_convert_wcstombsv(___envp)) == NULL)
		goto done_argv;
	result = libc_execve(utf8_path, utf8_argv, utf8_envp);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_envp);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_argv:
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_wexecvp)(char16_t const *__restrict file,
                                   __T16ARGV) {
	int result = -1;
	char *utf8_file, **utf8_argv;
	utf8_file = libd_convert_wcstombs(file);
	if unlikely(!utf8_file)
		goto done;
	utf8_argv = libd_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	result = libc_execvp(utf8_file, utf8_argv);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_file);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBKCALL libc_wexecvp)(char32_t const *__restrict file,
                                   __T32ARGV) {
	int result = -1;
	char *utf8_file, **utf8_argv;
	utf8_file = libc_convert_wcstombs(file);
	if unlikely(!utf8_file)
		goto done;
	utf8_argv = libc_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	result = libc_execvp(utf8_file, utf8_argv);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_file);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd_wexecvpe)(char16_t const *__restrict file,
                                    __T16ARGV,
                                    __T16ENVP) {
	int result = -1;
	char *utf8_file, **utf8_argv, **utf8_envp;
	utf8_file = libd_convert_wcstombs(file);
	if unlikely(!utf8_file)
		goto done;
	utf8_argv = libd_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	utf8_envp = NULL;
	if unlikely(___envp && (utf8_envp = libd_convert_wcstombsv(___envp)) == NULL)
		goto done_argv;
	result = libc_execvpe(utf8_file, utf8_argv, utf8_envp);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_envp);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_argv:
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_file);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBKCALL libc_wexecvpe)(char32_t const *__restrict file,
                                    __T32ARGV,
                                    __T32ENVP) {
	int result = -1;
	char *utf8_file, **utf8_argv, **utf8_envp;
	utf8_file = libc_convert_wcstombs(file);
	if unlikely(!utf8_file)
		goto done;
	utf8_argv = libc_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	utf8_envp = NULL;
	if unlikely(___envp && (utf8_envp = libc_convert_wcstombsv(___envp)) == NULL)
		goto done_argv;
	result = libc_execvpe(utf8_file, utf8_argv, utf8_envp);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_envp);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_argv:
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_file);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_wexecl)(char16_t const *__restrict path,
                                   char16_t const *args,
                                   ...) {
	__REDIRECT_EXECL(char16_t, libd_wexecv, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBKCALL libc_wexecl)(char32_t const *__restrict path,
                                   char32_t const *args,
                                   ...) {
	__REDIRECT_EXECL(char32_t, libc_wexecv, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_wexecle)(char16_t const *__restrict path,
                                    char16_t const *args,
                                    ...) {
	__REDIRECT_EXECLE(char16_t, libd_wexecve, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBKCALL libc_wexecle)(char32_t const *__restrict path,
                                    char32_t const *args,
                                    ...) {
	__REDIRECT_EXECLE(char32_t, libc_wexecve, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_wexeclp)(char16_t const *__restrict file,
                                    char16_t const *args,
                                    ...) {
	__REDIRECT_EXECL(char16_t, libd_wexecvp, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBKCALL libc_wexeclp)(char32_t const *__restrict file,
                                    char32_t const *args,
                                    ...) {
	__REDIRECT_EXECL(char32_t, libc_wexecvp, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_wexeclpe)(char16_t const *__restrict file,
                                     char16_t const *args,
                                     ...) {
	__REDIRECT_EXECLE(char16_t, libd_wexecvpe, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBKCALL libc_wexeclpe)(char32_t const *__restrict file,
                                     char32_t const *args,
                                     ...) {
	__REDIRECT_EXECLE(char32_t, libc_wexecvpe, file, args)
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnv)(__STDC_INT_AS_UINT_T mode,
                                   char16_t const *__restrict path,
                                   __T16ARGV) {
	int result = -1;
	char *utf8_path, **utf8_argv;
	utf8_path = libd_convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto done;
	utf8_argv = libd_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	result = libc_spawnv(mode, utf8_path, utf8_argv);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBKCALL libc_wspawnv)(__STDC_INT_AS_UINT_T mode,
                                   char32_t const *__restrict path,
                                   __T32ARGV) {
	int result = -1;
	char *utf8_path, **utf8_argv;
	utf8_path = libc_convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto done;
	utf8_argv = libc_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	result = libc_spawnv(mode, utf8_path, utf8_argv);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnve)(__STDC_INT_AS_UINT_T mode,
                                    char16_t const *__restrict path,
                                    __T16ARGV,
                                    __T16ENVP) {
	int result = -1;
	char *utf8_path, **utf8_argv, **utf8_envp;
	utf8_path = libd_convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto done;
	utf8_argv = libd_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	utf8_envp = NULL;
	if unlikely(___envp && (utf8_envp = libd_convert_wcstombsv(___envp)) == NULL)
		goto done_argv;
	result = libc_spawnve(mode, utf8_path, utf8_argv, utf8_envp);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_envp);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_argv:
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBKCALL libc_wspawnve)(__STDC_INT_AS_UINT_T mode,
                                    char32_t const *__restrict path,
                                    __T32ARGV,
                                    __T32ENVP) {
	int result = -1;
	char *utf8_path, **utf8_argv, **utf8_envp;
	utf8_path = libc_convert_wcstombs(path);
	if unlikely(!utf8_path)
		goto done;
	utf8_argv = libc_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	utf8_envp = NULL;
	if unlikely(___envp && (utf8_envp = libc_convert_wcstombsv(___envp)) == NULL)
		goto done_argv;
	result = libc_spawnve(mode, utf8_path, utf8_argv, utf8_envp);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_envp);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_argv:
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_path);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnvp)(__STDC_INT_AS_UINT_T mode,
                                    char16_t const *__restrict file,
                                    __T16ARGV) {
	int result = -1;
	char *utf8_file, **utf8_argv;
	utf8_file = libd_convert_wcstombs(file);
	if unlikely(!utf8_file)
		goto done;
	utf8_argv = libd_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	result = libc_spawnvp(mode, utf8_file, utf8_argv);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_file);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBKCALL libc_wspawnvp)(__STDC_INT_AS_UINT_T mode,
                                    char32_t const *__restrict file,
                                    __T32ARGV) {
	int result = -1;
	char *utf8_file, **utf8_argv;
	utf8_file = libc_convert_wcstombs(file);
	if unlikely(!utf8_file)
		goto done;
	utf8_argv = libc_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	result = libc_spawnvp(mode, utf8_file, utf8_argv);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_file);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnvpe)(__STDC_INT_AS_UINT_T mode,
                                     char16_t const *__restrict file,
                                     __T16ARGV,
                                     __T16ENVP) {
	int result = -1;
	char *utf8_file, **utf8_argv, **utf8_envp;
	utf8_file = libd_convert_wcstombs(file);
	if unlikely(!utf8_file)
		goto done;
	utf8_argv = libd_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	utf8_envp = NULL;
	if unlikely(___envp && (utf8_envp = libd_convert_wcstombsv(___envp)) == NULL)
		goto done_argv;
	result = libc_spawnvpe(mode, utf8_file, utf8_argv, utf8_envp);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_envp);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_argv:
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_file);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBKCALL libc_wspawnvpe)(__STDC_INT_AS_UINT_T mode,
                                     char32_t const *__restrict file,
                                     __T32ARGV,
                                     __T32ENVP) {
	int result = -1;
	char *utf8_file, **utf8_argv, **utf8_envp;
	utf8_file = libc_convert_wcstombs(file);
	if unlikely(!utf8_file)
		goto done;
	utf8_argv = libc_convert_wcstombsv(___argv);
	if unlikely(!utf8_argv)
		goto done_file;
	utf8_envp = NULL;
	if unlikely(___envp && (utf8_envp = libc_convert_wcstombsv(___envp)) == NULL)
		goto done_argv;
	result = libc_spawnvpe(mode, utf8_file, utf8_argv, utf8_envp);
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_envp);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_argv:
#if defined(__CRT_HAVE_convert_freev) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_convert_freev(utf8_argv);
#endif /* __CRT_HAVE_convert_freev || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done_file:
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	libc_free(utf8_file);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
done:
	return result;
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnl)(__STDC_INT_AS_UINT_T mode,
                                    char16_t const *__restrict path,
                                    char16_t const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char16_t, libd_wspawnv, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnl)(__STDC_INT_AS_UINT_T mode,
                                    char32_t const *__restrict path,
                                    char32_t const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char32_t, libc_wspawnv, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnle)(__STDC_INT_AS_UINT_T mode,
                                     char16_t const *__restrict path,
                                     char16_t const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char16_t, libd_wspawnve, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnle)(__STDC_INT_AS_UINT_T mode,
                                     char32_t const *__restrict path,
                                     char32_t const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char32_t, libc_wspawnve, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnlp)(__STDC_INT_AS_UINT_T mode,
                                     char16_t const *__restrict file,
                                     char16_t const *args,
                                     ...) {
	__REDIRECT_SPAWNL(char16_t, libd_wspawnvp, mode, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnlp)(__STDC_INT_AS_UINT_T mode,
                                     char32_t const *__restrict file,
                                     char32_t const *args,
                                     ...) {
	__REDIRECT_SPAWNL(char32_t, libc_wspawnvp, mode, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnlpe)(__STDC_INT_AS_UINT_T mode,
                                      char16_t const *__restrict file,
                                      char16_t const *args,
                                      ...) {
	__REDIRECT_SPAWNLE(char16_t, libd_wspawnvpe, mode, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnlpe)(__STDC_INT_AS_UINT_T mode,
                                      char32_t const *__restrict file,
                                      char32_t const *args,
                                      ...) {
	__REDIRECT_SPAWNLE(char32_t, libc_wspawnvpe, mode, file, args)
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_wexecv, libd_wexecv);
DEFINE_PUBLIC_ALIAS(DOS$wexecv, libd_wexecv);
DEFINE_PUBLIC_ALIAS(wexecv, libc_wexecv);
DEFINE_PUBLIC_ALIAS(DOS$_wexecve, libd_wexecve);
DEFINE_PUBLIC_ALIAS(DOS$wexecve, libd_wexecve);
DEFINE_PUBLIC_ALIAS(wexecve, libc_wexecve);
DEFINE_PUBLIC_ALIAS(DOS$_wexecvp, libd_wexecvp);
DEFINE_PUBLIC_ALIAS(DOS$wexecvp, libd_wexecvp);
DEFINE_PUBLIC_ALIAS(wexecvp, libc_wexecvp);
DEFINE_PUBLIC_ALIAS(DOS$_wexecvpe, libd_wexecvpe);
DEFINE_PUBLIC_ALIAS(DOS$wexecvpe, libd_wexecvpe);
DEFINE_PUBLIC_ALIAS(wexecvpe, libc_wexecvpe);
DEFINE_PUBLIC_ALIAS(DOS$_wexecl, libd_wexecl);
DEFINE_PUBLIC_ALIAS(DOS$wexecl, libd_wexecl);
DEFINE_PUBLIC_ALIAS(wexecl, libc_wexecl);
DEFINE_PUBLIC_ALIAS(DOS$_wexecle, libd_wexecle);
DEFINE_PUBLIC_ALIAS(DOS$wexecle, libd_wexecle);
DEFINE_PUBLIC_ALIAS(wexecle, libc_wexecle);
DEFINE_PUBLIC_ALIAS(DOS$_wexeclp, libd_wexeclp);
DEFINE_PUBLIC_ALIAS(DOS$wexeclp, libd_wexeclp);
DEFINE_PUBLIC_ALIAS(wexeclp, libc_wexeclp);
DEFINE_PUBLIC_ALIAS(DOS$_wexeclpe, libd_wexeclpe);
DEFINE_PUBLIC_ALIAS(DOS$wexeclpe, libd_wexeclpe);
DEFINE_PUBLIC_ALIAS(wexeclpe, libc_wexeclpe);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnv, libd_wspawnv);
DEFINE_PUBLIC_ALIAS(DOS$wspawnv, libd_wspawnv);
DEFINE_PUBLIC_ALIAS(wspawnv, libc_wspawnv);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnve, libd_wspawnve);
DEFINE_PUBLIC_ALIAS(DOS$wspawnve, libd_wspawnve);
DEFINE_PUBLIC_ALIAS(wspawnve, libc_wspawnve);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnvp, libd_wspawnvp);
DEFINE_PUBLIC_ALIAS(DOS$wspawnvp, libd_wspawnvp);
DEFINE_PUBLIC_ALIAS(wspawnvp, libc_wspawnvp);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnvpe, libd_wspawnvpe);
DEFINE_PUBLIC_ALIAS(DOS$wspawnvpe, libd_wspawnvpe);
DEFINE_PUBLIC_ALIAS(wspawnvpe, libc_wspawnvpe);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnl, libd_wspawnl);
DEFINE_PUBLIC_ALIAS(DOS$wspawnl, libd_wspawnl);
DEFINE_PUBLIC_ALIAS(wspawnl, libc_wspawnl);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnle, libd_wspawnle);
DEFINE_PUBLIC_ALIAS(DOS$wspawnle, libd_wspawnle);
DEFINE_PUBLIC_ALIAS(wspawnle, libc_wspawnle);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnlp, libd_wspawnlp);
DEFINE_PUBLIC_ALIAS(DOS$wspawnlp, libd_wspawnlp);
DEFINE_PUBLIC_ALIAS(wspawnlp, libc_wspawnlp);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnlpe, libd_wspawnlpe);
DEFINE_PUBLIC_ALIAS(DOS$wspawnlpe, libd_wspawnlpe);
DEFINE_PUBLIC_ALIAS(wspawnlpe, libc_wspawnlpe);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_PROCESS_C */