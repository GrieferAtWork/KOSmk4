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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_PROCESS_C
#define GUARD_LIBC_USER_PARTS_WCHAR_PROCESS_C 1

#include "../api.h"
/**/

#include <hybrid/host.h>

#include <malloc.h>
#include <process.h>
#include <stdarg.h>
#include <unistd.h>

#include "../libc/capture-varargs.h"
#include "../libc/globals.h"
#include "../libc/uchar.h"
#include "parts.wchar.process.h"

DECL_BEGIN


INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_do_c16exec)(char16_t const *__restrict file_or_path,
                                      char16_t const *const *__restrict argv,
                                      char16_t const *const *envp,
                                      bool search_path) {
	int result = -1;
	char *used_file, **used_argv, **used_envp;
	used_file = libc_uchar_c16tombs(file_or_path);
	if unlikely(!used_file)
		goto done;
	used_argv = libc_uchar_c16tombsv(argv);
	if unlikely(!used_argv)
		goto done_file;
	if (envp) {
		used_envp = libc_uchar_c16tombsv(envp);
		if unlikely(!used_envp)
			goto done_argv;
		result = search_path
		         ? execvpe(used_file, used_argv, used_envp)
		         : execve(used_file, used_argv, used_envp);
		libc_uchar_freev(used_envp);
	} else {
		result = search_path
		         ? execvp(used_file, used_argv)
		         : execv(used_file, used_argv);
	}
done_argv:
	libc_uchar_freev(used_argv);
done_file:
	free(used_file);
done:
	return result;
}

INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_do_c32exec)(char32_t const *__restrict file_or_path,
                                      char32_t const *const *__restrict argv,
                                      char32_t const *const *envp,
                                      bool search_path) {
	int result = -1;
	char *used_file, **used_argv, **used_envp;
	used_file = libc_uchar_c32tombs(file_or_path);
	if unlikely(!used_file)
		goto done;
	used_argv = libc_uchar_c32tombsv(argv);
	if unlikely(!used_argv)
		goto done_file;
	if (envp) {
		used_envp = libc_uchar_c32tombsv(envp);
		if unlikely(!used_envp)
			goto done_argv;
		result = search_path
		         ? execvpe(used_file, used_argv, used_envp)
		         : execve(used_file, used_argv, used_envp);
		libc_uchar_freev(used_envp);
	} else {
		result = search_path
		         ? execvp(used_file, used_argv)
		         : execv(used_file, used_argv);
	}
done_argv:
	libc_uchar_freev(used_argv);
done_file:
	free(used_file);
done:
	return result;
}

INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBCCALL libc_do_c16spawn)(int mode,
                                       char16_t const *__restrict file_or_path,
                                       char16_t const *const *__restrict argv,
                                       char16_t const *const *envp,
                                       bool search_path) {
	int result = -1;
	char *used_file, **used_argv, **used_envp;
	used_file = libc_uchar_c16tombs(file_or_path);
	if unlikely(!used_file)
		goto done;
	used_argv = libc_uchar_c16tombsv(argv);
	if unlikely(!used_argv)
		goto done_file;
	if (envp) {
		used_envp = libc_uchar_c16tombsv(envp);
		if unlikely(!used_envp)
			goto done_argv;
		result = search_path
		         ? spawnvpe(mode, used_file, used_argv, used_envp)
		         : spawnve(mode, used_file, used_argv, used_envp);
		libc_uchar_freev(used_envp);
	} else {
		result = search_path
		         ? spawnvp(mode, used_file, used_argv)
		         : spawnv(mode, used_file, used_argv);
	}
done_argv:
	libc_uchar_freev(used_argv);
done_file:
	free(used_file);
done:
	return result;
}

INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBCCALL libc_do_c32spawn)(int mode,
                                       char32_t const *__restrict file_or_path,
                                       char32_t const *const *__restrict argv,
                                       char32_t const *const *envp,
                                       bool search_path) {
	int result = -1;
	char *used_file, **used_argv, **used_envp;
	used_file = libc_uchar_c32tombs(file_or_path);
	if unlikely(!used_file)
		goto done;
	used_argv = libc_uchar_c32tombsv(argv);
	if unlikely(!used_argv)
		goto done_file;
	if (envp) {
		used_envp = libc_uchar_c32tombsv(envp);
		if unlikely(!used_envp)
			goto done_argv;
		result = search_path
		         ? spawnvpe(mode, used_file, used_argv, used_envp)
		         : spawnve(mode, used_file, used_argv, used_envp);
		libc_uchar_freev(used_envp);
	} else {
		result = search_path
		         ? spawnvp(mode, used_file, used_argv)
		         : spawnv(mode, used_file, used_argv);
	}
done_argv:
	libc_uchar_freev(used_argv);
done_file:
	free(used_file);
done:
	return result;
}



/*[[[head:libc_wexecv,hash:CRC-32=0xdfb5cd73]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBKCALL libc_wexecv)(char32_t const *__restrict path,
                                  __T32ARGV)
/*[[[body:libc_wexecv]]]*/
{
	return libc_do_c32exec(path, ___argv, NULL, false);
}
/*[[[end:libc_wexecv]]]*/

/*[[[head:libd_wexecv,hash:CRC-32=0x2e0d2bbc]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_wexecv)(char16_t const *__restrict path,
                                  __T16ARGV)
/*[[[body:libd_wexecv]]]*/
{
	return libc_do_c16exec(path, ___argv, NULL, false);
}
/*[[[end:libd_wexecv]]]*/

/*[[[head:libc_wexecve,hash:CRC-32=0x1ff8312]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBKCALL libc_wexecve)(char32_t const *__restrict path,
                                   __T32ARGV,
                                   __T32ENVP)
/*[[[body:libc_wexecve]]]*/
{
	return libc_do_c32exec(path, ___argv, ___envp, false);
}
/*[[[end:libc_wexecve]]]*/

/*[[[head:libd_wexecve,hash:CRC-32=0xa5066b1c]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd_wexecve)(char16_t const *__restrict path,
                                   __T16ARGV,
                                   __T16ENVP)
/*[[[body:libd_wexecve]]]*/
{
	return libc_do_c16exec(path, ___argv, ___envp, false);
}
/*[[[end:libd_wexecve]]]*/

/*[[[head:libc_wexecvp,hash:CRC-32=0x5c287c25]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBKCALL libc_wexecvp)(char32_t const *__restrict file,
                                   __T32ARGV)
/*[[[body:libc_wexecvp]]]*/
{
	return libc_do_c32exec(file, ___argv, NULL, true);
}
/*[[[end:libc_wexecvp]]]*/

/*[[[head:libd_wexecvp,hash:CRC-32=0x3e2cd550]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_wexecvp)(char16_t const *__restrict file,
                                   __T16ARGV)
/*[[[body:libd_wexecvp]]]*/
{
	return libc_do_c16exec(file, ___argv, NULL, true);
}
/*[[[end:libd_wexecvp]]]*/

/*[[[head:libc_wexecvpe,hash:CRC-32=0xc5184416]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBKCALL libc_wexecvpe)(char32_t const *__restrict file,
                                    __T32ARGV,
                                    __T32ENVP)
/*[[[body:libc_wexecvpe]]]*/
{
	return libc_do_c32exec(file, ___argv, ___envp, true);
}
/*[[[end:libc_wexecvpe]]]*/

/*[[[head:libd_wexecvpe,hash:CRC-32=0xabff78c4]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd_wexecvpe)(char16_t const *__restrict file,
                                    __T16ARGV,
                                    __T16ENVP)
/*[[[body:libd_wexecvpe]]]*/
{
	return libc_do_c16exec(file, ___argv, ___envp, true);
}
/*[[[end:libd_wexecvpe]]]*/

/*[[[head:libc_wexecl,hash:CRC-32=0xdf11541a]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBKCALL libc_wexecl)(char32_t const *__restrict path,
                                   char32_t const *args,
                                   ...)
/*[[[body:libc_wexecl]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	return libc_do_c32exec(path, (char32_t const *const *)&args, NULL, false);
#else
	va_list vargs;
	char32_t **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char32_t, vector, vargs, args);
	va_end(vargs);
	return libc_do_c32exec(path, (char32_t const *const *)vector, NULL, false);
#endif
}
/*[[[end:libc_wexecl]]]*/

/*[[[head:libd_wexecl,hash:CRC-32=0x4d3369b4]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_wexecl)(char16_t const *__restrict path,
                                   char16_t const *args,
                                   ...)
/*[[[body:libd_wexecl]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	return libc_do_c16exec(path, (char16_t const *const *)&args, NULL, false);
#else
	va_list vargs;
	char16_t **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char16_t, vector, vargs, args);
	va_end(vargs);
	return libc_do_c16exec(path, (char16_t const *const *)vector, NULL, false);
#endif
}
/*[[[end:libd_wexecl]]]*/

/*[[[head:libc_wexecle,hash:CRC-32=0xbe97d97f]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBKCALL libc_wexecle)(char32_t const *__restrict path,
                                    char32_t const *args,
                                    ...)
/*[[[body:libc_wexecle]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char32_t ***penvp = (char32_t ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	return libc_do_c32exec(path,
	                       (char32_t const *const *)&args,
	                       (char32_t const *const *)*penvp,
	                       false);
#else
	va_list vargs;
	char32_t **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char32_t, vector, vargs, args);
	envp = va_arg(vargs, char32_t **);
	va_end(vargs);
	return libc_do_c32exec(path,
	                       (char32_t const *const *)vector,
	                       (char32_t const *const *)envp,
	                       false);
#endif
}
/*[[[end:libc_wexecle]]]*/

/*[[[head:libd_wexecle,hash:CRC-32=0x72a00632]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_wexecle)(char16_t const *__restrict path,
                                    char16_t const *args,
                                    ...)
/*[[[body:libd_wexecle]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char16_t ***penvp = (char16_t ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	return libc_do_c16exec(path,
	                       (char16_t const *const *)&args,
	                       (char16_t const *const *)*penvp,
	                       false);
#else
	va_list vargs;
	char16_t **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char16_t, vector, vargs, args);
	envp = va_arg(vargs, char16_t **);
	va_end(vargs);
	return libc_do_c16exec(path,
	                       (char16_t const *const *)vector,
	                       (char16_t const *const *)envp,
	                       false);
#endif
}
/*[[[end:libd_wexecle]]]*/

/*[[[head:libc_wexeclp,hash:CRC-32=0x12ae08e0]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBKCALL libc_wexeclp)(char32_t const *__restrict file,
                                    char32_t const *args,
                                    ...)
/*[[[body:libc_wexeclp]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	return libc_do_c32exec(file, (char32_t const *const *)&args, NULL, true);
#else
	va_list vargs;
	char32_t **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char32_t, vector, vargs, args);
	va_end(vargs);
	return libc_do_c32exec(file, (char32_t const *const *)vector, NULL, true);
#endif
}
/*[[[end:libc_wexeclp]]]*/

/*[[[head:libd_wexeclp,hash:CRC-32=0x73f4be76]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_wexeclp)(char16_t const *__restrict file,
                                    char16_t const *args,
                                    ...)
/*[[[body:libd_wexeclp]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	return libc_do_c16exec(file, (char16_t const *const *)&args, NULL, true);
#else
	va_list vargs;
	char16_t **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char16_t, vector, vargs, args);
	va_end(vargs);
	return libc_do_c16exec(file, (char16_t const *const *)vector, NULL, true);
#endif
}
/*[[[end:libd_wexeclp]]]*/

/*[[[head:libc_wexeclpe,hash:CRC-32=0x2aaa8313]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBKCALL libc_wexeclpe)(char32_t const *__restrict file,
                                     char32_t const *args,
                                     ...)
/*[[[body:libc_wexeclpe]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char32_t ***penvp = (char32_t ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	return libc_do_c32exec(file,
	                       (char32_t const *const *)&args,
	                       (char32_t const *const *)*penvp,
	                       true);
#else
	va_list vargs;
	char32_t **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char32_t, vector, vargs, args);
	envp = va_arg(vargs, char32_t **);
	va_end(vargs);
	return libc_do_c32exec(file,
	                       (char32_t const *const *)vector,
	                       (char32_t const *const *)envp,
	                       true);
#endif
}
/*[[[end:libc_wexeclpe]]]*/

/*[[[head:libd_wexeclpe,hash:CRC-32=0x853dcccc]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd_wexeclpe)(char16_t const *__restrict file,
                                     char16_t const *args,
                                     ...)
/*[[[body:libd_wexeclpe]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char16_t ***penvp = (char16_t ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	return libc_do_c16exec(file,
	                       (char16_t const *const *)&args,
	                       (char16_t const *const *)*penvp,
	                       true);
#else
	va_list vargs;
	char16_t **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char16_t, vector, vargs, args);
	envp = va_arg(vargs, char16_t **);
	va_end(vargs);
	return libc_do_c16exec(file,
	                       (char16_t const *const *)vector,
	                       (char16_t const *const *)envp,
	                       true);
#endif
}
/*[[[end:libd_wexeclpe]]]*/

/*[[[head:libc_wspawnv,hash:CRC-32=0xb3987a4c]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBKCALL libc_wspawnv)(__STDC_INT_AS_UINT_T mode,
                                   char32_t const *__restrict path,
                                   __T32ARGV)
/*[[[body:libc_wspawnv]]]*/
{
	return libc_do_c32spawn(mode, path, ___argv, NULL, false);
}
/*[[[end:libc_wspawnv]]]*/

/*[[[head:libd_wspawnv,hash:CRC-32=0x344084d5]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnv)(__STDC_INT_AS_UINT_T mode,
                                   char16_t const *__restrict path,
                                   __T16ARGV)
/*[[[body:libd_wspawnv]]]*/
{
	return libc_do_c16spawn(mode, path, ___argv, NULL, false);
}
/*[[[end:libd_wspawnv]]]*/

/*[[[head:libc_wspawnve,hash:CRC-32=0x8bdebcaf]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBKCALL libc_wspawnve)(__STDC_INT_AS_UINT_T mode,
                                    char32_t const *__restrict path,
                                    __T32ARGV,
                                    __T32ENVP)
/*[[[body:libc_wspawnve]]]*/
{
	return libc_do_c32spawn(mode, path, ___argv, ___envp, false);
}
/*[[[end:libc_wspawnve]]]*/

/*[[[head:libd_wspawnve,hash:CRC-32=0x61824ba]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnve)(__STDC_INT_AS_UINT_T mode,
                                    char16_t const *__restrict path,
                                    __T16ARGV,
                                    __T16ENVP)
/*[[[body:libd_wspawnve]]]*/
{
	return libc_do_c16spawn(mode, path, ___argv, ___envp, false);
}
/*[[[end:libd_wspawnve]]]*/

/*[[[head:libc_wspawnvp,hash:CRC-32=0xe32f9a4c]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBKCALL libc_wspawnvp)(__STDC_INT_AS_UINT_T mode,
                                    char32_t const *__restrict file,
                                    __T32ARGV)
/*[[[body:libc_wspawnvp]]]*/
{
	return libc_do_c32spawn(mode, file, ___argv, NULL, true);
}
/*[[[end:libc_wspawnvp]]]*/

/*[[[head:libd_wspawnvp,hash:CRC-32=0xe532999e]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnvp)(__STDC_INT_AS_UINT_T mode,
                                    char16_t const *__restrict file,
                                    __T16ARGV)
/*[[[body:libd_wspawnvp]]]*/
{
	return libc_do_c16spawn(mode, file, ___argv, NULL, true);
}
/*[[[end:libd_wspawnvp]]]*/

/*[[[head:libc_wspawnvpe,hash:CRC-32=0x6019aee1]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBKCALL libc_wspawnvpe)(__STDC_INT_AS_UINT_T mode,
                                     char32_t const *__restrict file,
                                     __T32ARGV,
                                     __T32ENVP)
/*[[[body:libc_wspawnvpe]]]*/
{
	return libc_do_c32spawn(mode, file, ___argv, ___envp, true);
}
/*[[[end:libc_wspawnvpe]]]*/

/*[[[head:libd_wspawnvpe,hash:CRC-32=0xedbeb8a3]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnvpe)(__STDC_INT_AS_UINT_T mode,
                                     char16_t const *__restrict file,
                                     __T16ARGV,
                                     __T16ENVP)
/*[[[body:libd_wspawnvpe]]]*/
{
	return libc_do_c16spawn(mode, file, ___argv, ___envp, true);
}
/*[[[end:libd_wspawnvpe]]]*/

/*[[[head:libc_wspawnl,hash:CRC-32=0x6dd208d7]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnl)(__STDC_INT_AS_UINT_T mode,
                                    char32_t const *__restrict path,
                                    char32_t const *args,
                                    ...)
/*[[[body:libc_wspawnl]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	return libc_do_c32spawn(mode, path, (char32_t const *const *)&args, NULL, false);
#else
	va_list vargs;
	char32_t **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char32_t, vector, vargs, args);
	va_end(vargs);
	return libc_do_c32spawn(mode, path, (char32_t const *const *)vector, NULL, false);
#endif
}
/*[[[end:libc_wspawnl]]]*/

/*[[[head:libd_wspawnl,hash:CRC-32=0x4017b754]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnl)(__STDC_INT_AS_UINT_T mode,
                                    char16_t const *__restrict path,
                                    char16_t const *args,
                                    ...)
/*[[[body:libd_wspawnl]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	return libc_do_c16spawn(mode, path, (char16_t const *const *)&args, NULL, false);
#else
	va_list vargs;
	char16_t **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char16_t, vector, vargs, args);
	va_end(vargs);
	return libc_do_c16spawn(mode, path, (char16_t const *const *)vector, NULL, false);
#endif
}
/*[[[end:libd_wspawnl]]]*/

/*[[[head:libc_wspawnle,hash:CRC-32=0x7228affb]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnle)(__STDC_INT_AS_UINT_T mode,
                                     char32_t const *__restrict path,
                                     char32_t const *args,
                                     ...)
/*[[[body:libc_wspawnle]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char32_t ***penvp = (char32_t ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	return libc_do_c32spawn(mode, path,
	                        (char32_t const *const *)&args,
	                        (char32_t const *const *)*penvp,
	                        false);
#else
	va_list vargs;
	char32_t **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char32_t, vector, vargs, args);
	envp = va_arg(vargs, char32_t **);
	va_end(vargs);
	return libc_do_c32spawn(mode, path,
	                        (char32_t const *const *)vector,
	                        (char32_t const *const *)envp,
	                        false);
#endif
}
/*[[[end:libc_wspawnle]]]*/

/*[[[head:libd_wspawnle,hash:CRC-32=0x9df65f8e]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnle)(__STDC_INT_AS_UINT_T mode,
                                     char16_t const *__restrict path,
                                     char16_t const *args,
                                     ...)
/*[[[body:libd_wspawnle]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char16_t ***penvp = (char16_t ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	return libc_do_c16spawn(mode, path,
	                        (char16_t const *const *)&args,
	                        (char16_t const *const *)*penvp,
	                        false);
#else
	va_list vargs;
	char16_t **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char16_t, vector, vargs, args);
	envp = va_arg(vargs, char16_t **);
	va_end(vargs);
	return libc_do_c16spawn(mode, path,
	                        (char16_t const *const *)vector,
	                        (char16_t const *const *)envp,
	                        false);
#endif
}
/*[[[end:libd_wspawnle]]]*/

/*[[[head:libc_wspawnlp,hash:CRC-32=0x2b4fb368]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnlp)(__STDC_INT_AS_UINT_T mode,
                                     char32_t const *__restrict file,
                                     char32_t const *args,
                                     ...)
/*[[[body:libc_wspawnlp]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	return libc_do_c32spawn(mode, file, (char32_t const *const *)&args, NULL, true);
#else
	va_list vargs;
	char32_t **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char32_t, vector, vargs, args);
	va_end(vargs);
	return libc_do_c32spawn(mode, file, (char32_t const *const *)vector, NULL, true);
#endif
}
/*[[[end:libc_wspawnlp]]]*/

/*[[[head:libd_wspawnlp,hash:CRC-32=0x86b29d25]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnlp)(__STDC_INT_AS_UINT_T mode,
                                     char16_t const *__restrict file,
                                     char16_t const *args,
                                     ...)
/*[[[body:libd_wspawnlp]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	return libc_do_c16spawn(mode, file, (char16_t const *const *)&args, NULL, true);
#else
	va_list vargs;
	char16_t **vector;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char16_t, vector, vargs, args);
	va_end(vargs);
	return libc_do_c16spawn(mode, file, (char16_t const *const *)vector, NULL, true);
#endif
}
/*[[[end:libd_wspawnlp]]]*/

/*[[[head:libc_wspawnlpe,hash:CRC-32=0x7a2f6774]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnlpe)(__STDC_INT_AS_UINT_T mode,
                                      char32_t const *__restrict file,
                                      char32_t const *args,
                                      ...)
/*[[[body:libc_wspawnlpe]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char32_t ***penvp = (char32_t ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	return libc_do_c32spawn(mode, file,
	                        (char32_t const *const *)&args,
	                        (char32_t const *const *)*penvp,
	                        true);
#else
	va_list vargs;
	char32_t **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char32_t, vector, vargs, args);
	envp = va_arg(vargs, char32_t **);
	va_end(vargs);
	return libc_do_c32spawn(mode, file,
	                        (char32_t const *const *)vector,
	                        (char32_t const *const *)envp,
	                        true);
#endif
}
/*[[[end:libc_wspawnlpe]]]*/

/*[[[head:libd_wspawnlpe,hash:CRC-32=0x74c147a0]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnlpe)(__STDC_INT_AS_UINT_T mode,
                                      char16_t const *__restrict file,
                                      char16_t const *args,
                                      ...)
/*[[[body:libd_wspawnlpe]]]*/
{
#if defined(__i386__) && !defined(__x86_64__)
	char16_t ***penvp = (char16_t ***)&args;
	while (*penvp++)
		; /* Envp is located 1 after the first NULL-entry */
	return libc_do_c16spawn(mode, file,
	                        (char16_t const *const *)&args,
	                        (char16_t const *const *)*penvp,
	                        true);
#else
	va_list vargs;
	char16_t **vector, **envp;
	va_start(vargs, args);
	CAPTURE_VARARGS_PLUS_ONE(char16_t, vector, vargs, args);
	envp = va_arg(vargs, char16_t **);
	va_end(vargs);
	return libc_do_c16spawn(mode, file,
	                        (char16_t const *const *)vector,
	                        (char16_t const *const *)envp,
	                        true);
#endif
}
/*[[[end:libd_wspawnlpe]]]*/

/*[[[head:libc_wsystem,hash:CRC-32=0x9954fbd9]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.system") int
NOTHROW_RPC(LIBKCALL libc_wsystem)(char32_t const *cmd)
/*[[[body:libc_wsystem]]]*/
{
	int result;
	char *used_cmd;
	if (!cmd) {
		result = system(NULL);
	} else {
		used_cmd = libc_uchar_c32tombs(cmd);
		if unlikely(!used_cmd)
			return -1;
		result = system(used_cmd);
		free(used_cmd);
	}
	return result;
}
/*[[[end:libc_wsystem]]]*/

/*[[[head:libd_wsystem,hash:CRC-32=0x59e72be]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.system") int
NOTHROW_RPC(LIBDCALL libd_wsystem)(char16_t const *cmd)
/*[[[body:libd_wsystem]]]*/
{
	int result;
	char *used_cmd;
	if (!cmd) {
		result = system(NULL);
	} else {
		used_cmd = libc_uchar_c16tombs(cmd);
		if unlikely(!used_cmd)
			return -1;
		result = system(used_cmd);
		free(used_cmd);
	}
	return result;
}
/*[[[end:libd_wsystem]]]*/





/*[[[start:exports,hash:CRC-32=0xfd8227c7]]]*/
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
DEFINE_PUBLIC_ALIAS(DOS$_wexeclp, libd_wexeclp);
DEFINE_PUBLIC_ALIAS(DOS$wexeclp, libd_wexeclp);
DEFINE_PUBLIC_ALIAS(wexeclp, libc_wexeclp);
DEFINE_PUBLIC_ALIAS(DOS$_wexecle, libd_wexecle);
DEFINE_PUBLIC_ALIAS(DOS$wexecle, libd_wexecle);
DEFINE_PUBLIC_ALIAS(wexecle, libc_wexecle);
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
DEFINE_PUBLIC_ALIAS(DOS$_wspawnlp, libd_wspawnlp);
DEFINE_PUBLIC_ALIAS(DOS$wspawnlp, libd_wspawnlp);
DEFINE_PUBLIC_ALIAS(wspawnlp, libc_wspawnlp);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnle, libd_wspawnle);
DEFINE_PUBLIC_ALIAS(DOS$wspawnle, libd_wspawnle);
DEFINE_PUBLIC_ALIAS(wspawnle, libc_wspawnle);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnlpe, libd_wspawnlpe);
DEFINE_PUBLIC_ALIAS(DOS$wspawnlpe, libd_wspawnlpe);
DEFINE_PUBLIC_ALIAS(wspawnlpe, libc_wspawnlpe);
DEFINE_PUBLIC_ALIAS(DOS$_wsystem, libd_wsystem);
DEFINE_PUBLIC_ALIAS(DOS$wsystem, libd_wsystem);
DEFINE_PUBLIC_ALIAS(wsystem, libc_wsystem);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_PROCESS_C */
