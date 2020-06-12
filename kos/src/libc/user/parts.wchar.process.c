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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_PROCESS_C
#define GUARD_LIBC_USER_PARTS_WCHAR_PROCESS_C 1

#include "../api.h"
/**/

#include <unistd.h>
#include <process.h>
#include <malloc.h>
#include <stdarg.h>
#include <hybrid/host.h>
#include "../libc/uchar.h"
#include "../libc/capture-varargs.h"
#include "parts.wchar.process.h"

DECL_BEGIN

#undef environ
#ifndef __environ_defined
#define __environ_defined 1
extern char **environ;
#endif /* !__environ_defined */
DECLARE_NOREL_GLOBAL_META(char **, environ);
#define environ  GET_NOREL_GLOBAL(environ)


INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.do_c16exec") int
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

INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.do_c32exec") int
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

INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.do_c16spawn") pid_t
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

INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.do_c32spawn") pid_t
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

/*[[[start:implementation]]]*/

/*[[[head:libc_wexecv,hash:CRC-32=0xdfb5cd73]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBKCALL libc_wexecv)(char32_t const *__restrict path,
                                  __T32ARGV)
/*[[[body:libc_wexecv]]]*/
{
	return libc_do_c32exec(path, ___argv, NULL, false);
}
/*[[[end:libc_wexecv]]]*/

/*[[[head:libd__wexecv,hash:CRC-32=0x687152da]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd__wexecv)(char16_t const *__restrict path,
                                   __T16ARGV)
/*[[[body:libd__wexecv]]]*/
{
	return libc_do_c16exec(path, ___argv, NULL, false);
}
/*[[[end:libd__wexecv]]]*/

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

/*[[[head:libd__wexecve,hash:CRC-32=0x79655806]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd__wexecve)(char16_t const *__restrict path,
                                    __T16ARGV,
                                    __T16ENVP)
/*[[[body:libd__wexecve]]]*/
{
	return libc_do_c16exec(path, ___argv, ___envp, false);
}
/*[[[end:libd__wexecve]]]*/

/*[[[head:libc_wexecvp,hash:CRC-32=0x5c287c25]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBKCALL libc_wexecvp)(char32_t const *__restrict file,
                                   __T32ARGV)
/*[[[body:libc_wexecvp]]]*/
{
	return libc_do_c32exec(file, ___argv, NULL, true);
}
/*[[[end:libc_wexecvp]]]*/

/*[[[head:libd__wexecvp,hash:CRC-32=0x33300fdc]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd__wexecvp)(char16_t const *__restrict file,
                                    __T16ARGV)
/*[[[body:libd__wexecvp]]]*/
{
	return libc_do_c16exec(file, ___argv, NULL, true);
}
/*[[[end:libd__wexecvp]]]*/

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

/*[[[head:libd__wexecvpe,hash:CRC-32=0xc28396a2]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") NONNULL((1, 2, 3)) int
NOTHROW_RPC(LIBDCALL libd__wexecvpe)(char16_t const *__restrict file,
                                     __T16ARGV,
                                     __T16ENVP)
/*[[[body:libd__wexecvpe]]]*/
{
	return libc_do_c16exec(file, ___argv, ___envp, true);
}
/*[[[end:libd__wexecvpe]]]*/

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

/*[[[head:libd__wexecl,hash:CRC-32=0x30938f9e]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd__wexecl)(char16_t const *__restrict path,
                                    char16_t const *args,
                                    ...)
/*[[[body:libd__wexecl]]]*/
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
/*[[[end:libd__wexecl]]]*/

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

/*[[[head:libd__wexecle,hash:CRC-32=0x1cb5a6a2]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd__wexecle)(char16_t const *__restrict path,
                                     char16_t const *args,
                                     ...)
/*[[[body:libd__wexecle]]]*/
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
/*[[[end:libd__wexecle]]]*/

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

/*[[[head:libd__wexeclp,hash:CRC-32=0xc1e46331]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd__wexeclp)(char16_t const *__restrict file,
                                     char16_t const *args,
                                     ...)
/*[[[body:libd__wexeclp]]]*/
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
/*[[[end:libd__wexeclp]]]*/

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

/*[[[head:libd__wexeclpe,hash:CRC-32=0x5445750f]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec") ATTR_SENTINEL_O(1) NONNULL((1)) int
NOTHROW_RPC(VLIBDCALL libd__wexeclpe)(char16_t const *__restrict file,
                                      char16_t const *args,
                                      ...)
/*[[[body:libd__wexeclpe]]]*/
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
/*[[[end:libd__wexeclpe]]]*/

/*[[[head:libc_wspawnv,hash:CRC-32=0xc0de62ce]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBKCALL libc_wspawnv)(int mode,
                                   char32_t const *__restrict path,
                                   __T32ARGV)
/*[[[body:libc_wspawnv]]]*/
{
	return libc_do_c32spawn(mode, path, ___argv, NULL, false);
}
/*[[[end:libc_wspawnv]]]*/

/*[[[head:libd__wspawnv,hash:CRC-32=0xaabf98c6]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBDCALL libd__wspawnv)(int mode,
                                    char16_t const *__restrict path,
                                    __T16ARGV)
/*[[[body:libd__wspawnv]]]*/
{
	return libc_do_c16spawn(mode, path, ___argv, NULL, false);
}
/*[[[end:libd__wspawnv]]]*/

/*[[[head:libc_wspawnve,hash:CRC-32=0xab809fc2]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBKCALL libc_wspawnve)(int mode,
                                    char32_t const *__restrict path,
                                    __T32ARGV,
                                    __T32ENVP)
/*[[[body:libc_wspawnve]]]*/
{
	return libc_do_c32spawn(mode, path, ___argv, ___envp, false);
}
/*[[[end:libc_wspawnve]]]*/

/*[[[head:libd__wspawnve,hash:CRC-32=0xfa14149]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBDCALL libd__wspawnve)(int mode,
                                     char16_t const *__restrict path,
                                     __T16ARGV,
                                     __T16ENVP)
/*[[[body:libd__wspawnve]]]*/
{
	return libc_do_c16spawn(mode, path, ___argv, ___envp, false);
}
/*[[[end:libd__wspawnve]]]*/

/*[[[head:libc_wspawnvp,hash:CRC-32=0xabd8f3df]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBKCALL libc_wspawnvp)(int mode,
                                    char32_t const *__restrict file,
                                    __T32ARGV)
/*[[[body:libc_wspawnvp]]]*/
{
	return libc_do_c32spawn(mode, file, ___argv, NULL, true);
}
/*[[[end:libc_wspawnvp]]]*/

/*[[[head:libd__wspawnvp,hash:CRC-32=0x333ddf32]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") NONNULL((2, 3)) pid_t
NOTHROW_RPC(LIBDCALL libd__wspawnvp)(int mode,
                                     char16_t const *__restrict file,
                                     __T16ARGV)
/*[[[body:libd__wspawnvp]]]*/
{
	return libc_do_c16spawn(mode, file, ___argv, NULL, true);
}
/*[[[end:libd__wspawnvp]]]*/

/*[[[head:libc_wspawnvpe,hash:CRC-32=0x3b69b4f6]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBKCALL libc_wspawnvpe)(int mode,
                                     char32_t const *__restrict file,
                                     __T32ARGV,
                                     __T32ENVP)
/*[[[body:libc_wspawnvpe]]]*/
{
	return libc_do_c32spawn(mode, file, ___argv, ___envp, true);
}
/*[[[end:libc_wspawnvpe]]]*/

/*[[[head:libd__wspawnvpe,hash:CRC-32=0x7da48b56]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") NONNULL((2, 3, 4)) pid_t
NOTHROW_RPC(LIBDCALL libd__wspawnvpe)(int mode,
                                      char16_t const *__restrict file,
                                      __T16ARGV,
                                      __T16ENVP)
/*[[[body:libd__wspawnvpe]]]*/
{
	return libc_do_c16spawn(mode, file, ___argv, ___envp, true);
}
/*[[[end:libd__wspawnvpe]]]*/

/*[[[head:libc_wspawnl,hash:CRC-32=0xd85badaf]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnl)(int mode,
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

/*[[[head:libd__wspawnl,hash:CRC-32=0xf4d7f94a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd__wspawnl)(int mode,
                                     char16_t const *__restrict path,
                                     char16_t const *args,
                                     ...)
/*[[[body:libd__wspawnl]]]*/
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
/*[[[end:libd__wspawnl]]]*/

/*[[[head:libc_wspawnle,hash:CRC-32=0x2fb9a924]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnle)(int mode,
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

/*[[[head:libd__wspawnle,hash:CRC-32=0xcfe21cb8]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd__wspawnle)(int mode,
                                      char16_t const *__restrict path,
                                      char16_t const *args,
                                      ...)
/*[[[body:libd__wspawnle]]]*/
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
/*[[[end:libd__wspawnle]]]*/

/*[[[head:libc_wspawnlp,hash:CRC-32=0x78d35334]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnlp)(int mode,
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

/*[[[head:libd__wspawnlp,hash:CRC-32=0x3be6e3ca]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd__wspawnlp)(int mode,
                                      char16_t const *__restrict file,
                                      char16_t const *args,
                                      ...)
/*[[[body:libd__wspawnlp]]]*/
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
/*[[[end:libd__wspawnlp]]]*/

/*[[[head:libc_wspawnlpe,hash:CRC-32=0x8b9cda]]]*/
INTERN ATTR_SECTION(".text.crt.wchar.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBKCALL libc_wspawnlpe)(int mode,
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

/*[[[head:libd__wspawnlpe,hash:CRC-32=0x4a1e7f3a]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn") ATTR_SENTINEL_O(1) NONNULL((2)) pid_t
NOTHROW_RPC(VLIBDCALL libd__wspawnlpe)(int mode,
                                       char16_t const *__restrict file,
                                       char16_t const *args,
                                       ...)
/*[[[body:libd__wspawnlpe]]]*/
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
/*[[[end:libd__wspawnlpe]]]*/

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

/*[[[head:libd__wsystem,hash:CRC-32=0x157a87b2]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.exec.system") int
NOTHROW_RPC(LIBDCALL libd__wsystem)(char16_t const *cmd)
/*[[[body:libd__wsystem]]]*/
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
/*[[[end:libd__wsystem]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xa34189c4]]]*/
DEFINE_PUBLIC_ALIAS(DOS$_wexecv, libd__wexecv);
DEFINE_PUBLIC_ALIAS(wexecv, libc_wexecv);
DEFINE_PUBLIC_ALIAS(DOS$_wexecve, libd__wexecve);
DEFINE_PUBLIC_ALIAS(wexecve, libc_wexecve);
DEFINE_PUBLIC_ALIAS(DOS$_wexecvp, libd__wexecvp);
DEFINE_PUBLIC_ALIAS(wexecvp, libc_wexecvp);
DEFINE_PUBLIC_ALIAS(DOS$_wexecvpe, libd__wexecvpe);
DEFINE_PUBLIC_ALIAS(wexecvpe, libc_wexecvpe);
DEFINE_PUBLIC_ALIAS(DOS$_wexecl, libd__wexecl);
DEFINE_PUBLIC_ALIAS(wexecl, libc_wexecl);
DEFINE_PUBLIC_ALIAS(DOS$_wexeclp, libd__wexeclp);
DEFINE_PUBLIC_ALIAS(wexeclp, libc_wexeclp);
DEFINE_PUBLIC_ALIAS(DOS$_wexecle, libd__wexecle);
DEFINE_PUBLIC_ALIAS(wexecle, libc_wexecle);
DEFINE_PUBLIC_ALIAS(DOS$_wexeclpe, libd__wexeclpe);
DEFINE_PUBLIC_ALIAS(wexeclpe, libc_wexeclpe);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnv, libd__wspawnv);
DEFINE_PUBLIC_ALIAS(wspawnv, libc_wspawnv);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnve, libd__wspawnve);
DEFINE_PUBLIC_ALIAS(wspawnve, libc_wspawnve);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnvp, libd__wspawnvp);
DEFINE_PUBLIC_ALIAS(wspawnvp, libc_wspawnvp);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnvpe, libd__wspawnvpe);
DEFINE_PUBLIC_ALIAS(wspawnvpe, libc_wspawnvpe);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnl, libd__wspawnl);
DEFINE_PUBLIC_ALIAS(wspawnl, libc_wspawnl);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnlp, libd__wspawnlp);
DEFINE_PUBLIC_ALIAS(wspawnlp, libc_wspawnlp);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnle, libd__wspawnle);
DEFINE_PUBLIC_ALIAS(wspawnle, libc_wspawnle);
DEFINE_PUBLIC_ALIAS(DOS$_wspawnlpe, libd__wspawnlpe);
DEFINE_PUBLIC_ALIAS(wspawnlpe, libc_wspawnlpe);
DEFINE_PUBLIC_ALIAS(DOS$_wsystem, libd__wsystem);
DEFINE_PUBLIC_ALIAS(wsystem, libc_wsystem);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_PROCESS_C */
