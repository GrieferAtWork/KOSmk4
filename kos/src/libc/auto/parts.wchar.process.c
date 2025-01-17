/* HASH CRC-32:0x323056ea */
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_IN(1) ATTR_IN(2) int
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
	result = libd_execv(utf8_path, utf8_argv);

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_path);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_IN(1) ATTR_IN(2) int
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

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_path);

done:
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) int
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
	result = libd_execve(utf8_path, utf8_argv, utf8_envp);

	libc_convert_freev(utf8_envp);

done_argv:

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_path);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) int
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

	libc_convert_freev(utf8_envp);

done_argv:

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_path);

done:
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_IN(1) ATTR_IN(2) int
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
	result = libd_execvp(utf8_file, utf8_argv);

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_file);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_IN(1) ATTR_IN(2) int
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

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_file);

done:
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) int
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
	result = libd_execvpe(utf8_file, utf8_argv, utf8_envp);

	libc_convert_freev(utf8_envp);

done_argv:

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_file);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_IN(1) ATTR_IN(2) ATTR_IN(3) int
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

	libc_convert_freev(utf8_envp);

done_argv:

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_file);

done:
	return result;
}
#include <parts/redirect-exec.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(VLIBDCALL libd_wexecl)(char16_t const *__restrict path,
                                   char16_t const *args,
                                   ...) {
	__REDIRECT_EXECL(char16_t, libd_wexecv, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(VLIBKCALL libc_wexecl)(char32_t const *__restrict path,
                                   char32_t const *args,
                                   ...) {
	__REDIRECT_EXECL(char32_t, libc_wexecv, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) int
NOTHROW_RPC(VLIBDCALL libd_wexecle)(char16_t const *__restrict path,
                                    char16_t const *args,
                                    ...) {
	__REDIRECT_EXECLE(char16_t, libd_wexecve, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) int
NOTHROW_RPC(VLIBKCALL libc_wexecle)(char32_t const *__restrict path,
                                    char32_t const *args,
                                    ...) {
	__REDIRECT_EXECLE(char32_t, libc_wexecve, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(VLIBDCALL libd_wexeclp)(char16_t const *__restrict file,
                                    char16_t const *args,
                                    ...) {
	__REDIRECT_EXECL(char16_t, libd_wexecvp, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2) int
NOTHROW_RPC(VLIBKCALL libc_wexeclp)(char32_t const *__restrict file,
                                    char32_t const *args,
                                    ...) {
	__REDIRECT_EXECL(char32_t, libc_wexecvp, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) int
NOTHROW_RPC(VLIBDCALL libd_wexeclpe)(char16_t const *__restrict file,
                                     char16_t const *args,
                                     ...) {
	__REDIRECT_EXECLE(char16_t, libd_wexecvpe, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1) int
NOTHROW_RPC(VLIBKCALL libc_wexeclpe)(char32_t const *__restrict file,
                                     char32_t const *args,
                                     ...) {
	__REDIRECT_EXECLE(char32_t, libc_wexecvpe, file, args)
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) pid_t
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
	result = libd_spawnv(mode, utf8_path, utf8_argv);

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_path);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) pid_t
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

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_path);

done:
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) pid_t
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
	result = libd_spawnve(mode, utf8_path, utf8_argv, utf8_envp);

	libc_convert_freev(utf8_envp);

done_argv:

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_path);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) pid_t
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

	libc_convert_freev(utf8_envp);

done_argv:

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_path);

done:
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) pid_t
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
	result = libd_spawnvp(mode, utf8_file, utf8_argv);

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_file);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) pid_t
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

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_file);

done:
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) pid_t
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
	result = libd_spawnvpe(mode, utf8_file, utf8_argv, utf8_envp);

	libc_convert_freev(utf8_envp);

done_argv:

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_file);

done:
	return result;
}
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_IN(2) ATTR_IN(3) ATTR_IN(4) pid_t
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

	libc_convert_freev(utf8_envp);

done_argv:

	libc_convert_freev(utf8_argv);

done_file:

	libc_free(utf8_file);

done:
	return result;
}
#include <parts/redirect-exec.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3) pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnl)(__STDC_INT_AS_UINT_T mode,
                                    char16_t const *__restrict path,
                                    char16_t const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char16_t, libd_wspawnv, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnl)(__STDC_INT_AS_UINT_T mode,
                                    char32_t const *__restrict path,
                                    char32_t const *args,
                                    ...) {
	__REDIRECT_SPAWNL(char32_t, libc_wspawnv, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1) pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnle)(__STDC_INT_AS_UINT_T mode,
                                     char16_t const *__restrict path,
                                     char16_t const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char16_t, libd_wspawnve, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnle)(__STDC_INT_AS_UINT_T mode,
                                     char32_t const *__restrict path,
                                     char32_t const *args,
                                     ...) {
	__REDIRECT_SPAWNLE(char32_t, libc_wspawnve, mode, path, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3) pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnlp)(__STDC_INT_AS_UINT_T mode,
                                     char16_t const *__restrict file,
                                     char16_t const *args,
                                     ...) {
	__REDIRECT_SPAWNL(char16_t, libd_wspawnvp, mode, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnlp)(__STDC_INT_AS_UINT_T mode,
                                     char32_t const *__restrict file,
                                     char32_t const *args,
                                     ...) {
	__REDIRECT_SPAWNL(char32_t, libc_wspawnvp, mode, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1) pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnlpe)(__STDC_INT_AS_UINT_T mode,
                                      char16_t const *__restrict file,
                                      char16_t const *args,
                                      ...) {
	__REDIRECT_SPAWNLE(char16_t, libd_wspawnvpe, mode, file, args)
}
#include <parts/redirect-exec.h>
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnlpe)(__STDC_INT_AS_UINT_T mode,
                                      char32_t const *__restrict file,
                                      char32_t const *args,
                                      ...) {
	__REDIRECT_SPAWNLE(char32_t, libc_wspawnvpe, mode, file, args)
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(DOS$_wexecv,libd_wexecv,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict path, __T16ARGV),(path,___argv));
DEFINE_PUBLIC_ALIAS_P(DOS$wexecv,libd_wexecv,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict path, __T16ARGV),(path,___argv));
DEFINE_PUBLIC_ALIAS_P(wexecv,libc_wexecv,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBKCALL,(char32_t const *__restrict path, __T32ARGV),(path,___argv));
DEFINE_PUBLIC_ALIAS_P(DOS$_wexecve,libd_wexecve,ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict path, __T16ARGV, __T16ENVP),(path,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(DOS$wexecve,libd_wexecve,ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict path, __T16ARGV, __T16ENVP),(path,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(wexecve,libc_wexecve,ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBKCALL,(char32_t const *__restrict path, __T32ARGV, __T32ENVP),(path,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(DOS$_wexecvp,libd_wexecvp,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict file, __T16ARGV),(file,___argv));
DEFINE_PUBLIC_ALIAS_P(DOS$wexecvp,libd_wexecvp,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict file, __T16ARGV),(file,___argv));
DEFINE_PUBLIC_ALIAS_P(wexecvp,libc_wexecvp,ATTR_IN(1) ATTR_IN(2),int,NOTHROW_RPC,LIBKCALL,(char32_t const *__restrict file, __T32ARGV),(file,___argv));
DEFINE_PUBLIC_ALIAS_P(DOS$_wexecvpe,libd_wexecvpe,ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict file, __T16ARGV, __T16ENVP),(file,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(DOS$wexecvpe,libd_wexecvpe,ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBDCALL,(char16_t const *__restrict file, __T16ARGV, __T16ENVP),(file,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(wexecvpe,libc_wexecvpe,ATTR_IN(1) ATTR_IN(2) ATTR_IN(3),int,NOTHROW_RPC,LIBKCALL,(char32_t const *__restrict file, __T32ARGV, __T32ENVP),(file,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(DOS$_wexecl,libd_wexecl,ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,VLIBDCALL,(char16_t const *__restrict path, char16_t const *args, ...),(path,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$wexecl,libd_wexecl,ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,VLIBDCALL,(char16_t const *__restrict path, char16_t const *args, ...),(path,args,));
DEFINE_PUBLIC_ALIAS_P(wexecl,libc_wexecl,ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,VLIBKCALL,(char32_t const *__restrict path, char32_t const *args, ...),(path,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$_wexecle,libd_wexecle,ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1),int,NOTHROW_RPC,VLIBDCALL,(char16_t const *__restrict path, char16_t const *args, ...),(path,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$wexecle,libd_wexecle,ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1),int,NOTHROW_RPC,VLIBDCALL,(char16_t const *__restrict path, char16_t const *args, ...),(path,args,));
DEFINE_PUBLIC_ALIAS_P(wexecle,libc_wexecle,ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1),int,NOTHROW_RPC,VLIBKCALL,(char32_t const *__restrict path, char32_t const *args, ...),(path,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$_wexeclp,libd_wexeclp,ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,VLIBDCALL,(char16_t const *__restrict file, char16_t const *args, ...),(file,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$wexeclp,libd_wexeclp,ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,VLIBDCALL,(char16_t const *__restrict file, char16_t const *args, ...),(file,args,));
DEFINE_PUBLIC_ALIAS_P(wexeclp,libc_wexeclp,ATTR_SENTINEL ATTR_IN(1) ATTR_IN_OPT(2),int,NOTHROW_RPC,VLIBKCALL,(char32_t const *__restrict file, char32_t const *args, ...),(file,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$_wexeclpe,libd_wexeclpe,ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1),int,NOTHROW_RPC,VLIBDCALL,(char16_t const *__restrict file, char16_t const *args, ...),(file,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$wexeclpe,libd_wexeclpe,ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1),int,NOTHROW_RPC,VLIBDCALL,(char16_t const *__restrict file, char16_t const *args, ...),(file,args,));
DEFINE_PUBLIC_ALIAS_P(wexeclpe,libc_wexeclpe,ATTR_IN(1) ATTR_IN_OPT(2) ATTR_SENTINEL_O(1),int,NOTHROW_RPC,VLIBKCALL,(char32_t const *__restrict file, char32_t const *args, ...),(file,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$_wspawnv,libd_wspawnv,ATTR_IN(2) ATTR_IN(3),pid_t,NOTHROW_RPC,LIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict path, __T16ARGV),(mode,path,___argv));
DEFINE_PUBLIC_ALIAS_P(DOS$wspawnv,libd_wspawnv,ATTR_IN(2) ATTR_IN(3),pid_t,NOTHROW_RPC,LIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict path, __T16ARGV),(mode,path,___argv));
DEFINE_PUBLIC_ALIAS_P(wspawnv,libc_wspawnv,ATTR_IN(2) ATTR_IN(3),pid_t,NOTHROW_RPC,LIBKCALL,(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict path, __T32ARGV),(mode,path,___argv));
DEFINE_PUBLIC_ALIAS_P(DOS$_wspawnve,libd_wspawnve,ATTR_IN(2) ATTR_IN(3) ATTR_IN(4),pid_t,NOTHROW_RPC,LIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict path, __T16ARGV, __T16ENVP),(mode,path,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(DOS$wspawnve,libd_wspawnve,ATTR_IN(2) ATTR_IN(3) ATTR_IN(4),pid_t,NOTHROW_RPC,LIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict path, __T16ARGV, __T16ENVP),(mode,path,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(wspawnve,libc_wspawnve,ATTR_IN(2) ATTR_IN(3) ATTR_IN(4),pid_t,NOTHROW_RPC,LIBKCALL,(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict path, __T32ARGV, __T32ENVP),(mode,path,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(DOS$_wspawnvp,libd_wspawnvp,ATTR_IN(2) ATTR_IN(3),pid_t,NOTHROW_RPC,LIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict file, __T16ARGV),(mode,file,___argv));
DEFINE_PUBLIC_ALIAS_P(DOS$wspawnvp,libd_wspawnvp,ATTR_IN(2) ATTR_IN(3),pid_t,NOTHROW_RPC,LIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict file, __T16ARGV),(mode,file,___argv));
DEFINE_PUBLIC_ALIAS_P(wspawnvp,libc_wspawnvp,ATTR_IN(2) ATTR_IN(3),pid_t,NOTHROW_RPC,LIBKCALL,(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict file, __T32ARGV),(mode,file,___argv));
DEFINE_PUBLIC_ALIAS_P(DOS$_wspawnvpe,libd_wspawnvpe,ATTR_IN(2) ATTR_IN(3) ATTR_IN(4),pid_t,NOTHROW_RPC,LIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict file, __T16ARGV, __T16ENVP),(mode,file,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(DOS$wspawnvpe,libd_wspawnvpe,ATTR_IN(2) ATTR_IN(3) ATTR_IN(4),pid_t,NOTHROW_RPC,LIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict file, __T16ARGV, __T16ENVP),(mode,file,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(wspawnvpe,libc_wspawnvpe,ATTR_IN(2) ATTR_IN(3) ATTR_IN(4),pid_t,NOTHROW_RPC,LIBKCALL,(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict file, __T32ARGV, __T32ENVP),(mode,file,___argv,___envp));
DEFINE_PUBLIC_ALIAS_P(DOS$_wspawnl,libd_wspawnl,ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3),pid_t,NOTHROW_RPC,VLIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict path, char16_t const *args, ...),(mode,path,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$wspawnl,libd_wspawnl,ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3),pid_t,NOTHROW_RPC,VLIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict path, char16_t const *args, ...),(mode,path,args,));
DEFINE_PUBLIC_ALIAS_P(wspawnl,libc_wspawnl,ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3),pid_t,NOTHROW_RPC,VLIBKCALL,(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict path, char32_t const *args, ...),(mode,path,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$_wspawnle,libd_wspawnle,ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1),pid_t,NOTHROW_RPC,VLIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict path, char16_t const *args, ...),(mode,path,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$wspawnle,libd_wspawnle,ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1),pid_t,NOTHROW_RPC,VLIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict path, char16_t const *args, ...),(mode,path,args,));
DEFINE_PUBLIC_ALIAS_P(wspawnle,libc_wspawnle,ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1),pid_t,NOTHROW_RPC,VLIBKCALL,(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict path, char32_t const *args, ...),(mode,path,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$_wspawnlp,libd_wspawnlp,ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3),pid_t,NOTHROW_RPC,VLIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict file, char16_t const *args, ...),(mode,file,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$wspawnlp,libd_wspawnlp,ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3),pid_t,NOTHROW_RPC,VLIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict file, char16_t const *args, ...),(mode,file,args,));
DEFINE_PUBLIC_ALIAS_P(wspawnlp,libc_wspawnlp,ATTR_SENTINEL ATTR_IN(2) ATTR_IN_OPT(3),pid_t,NOTHROW_RPC,VLIBKCALL,(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict file, char32_t const *args, ...),(mode,file,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$_wspawnlpe,libd_wspawnlpe,ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1),pid_t,NOTHROW_RPC,VLIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict file, char16_t const *args, ...),(mode,file,args,));
DEFINE_PUBLIC_ALIAS_P(DOS$wspawnlpe,libd_wspawnlpe,ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1),pid_t,NOTHROW_RPC,VLIBDCALL,(__STDC_INT_AS_UINT_T mode, char16_t const *__restrict file, char16_t const *args, ...),(mode,file,args,));
DEFINE_PUBLIC_ALIAS_P(wspawnlpe,libc_wspawnlpe,ATTR_IN(2) ATTR_IN_OPT(3) ATTR_SENTINEL_O(1),pid_t,NOTHROW_RPC,VLIBKCALL,(__STDC_INT_AS_UINT_T mode, char32_t const *__restrict file, char32_t const *args, ...),(mode,file,args,));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_PROCESS_C */
