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

/*[[[head:wexecv,hash:CRC-32=0x268e1466]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexecv") int
NOTHROW_RPC(LIBCCALL libc_wexecv)(char32_t const *__restrict path,
                                  __T32ARGV)
/*[[[body:wexecv]]]*/
{
	return libc_do_c32exec(path, ___argv, NULL, false);
}
/*[[[end:wexecv]]]*/

/*[[[head:DOS$wexecv,hash:CRC-32=0x2417b608]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexecv") int
NOTHROW_RPC(LIBDCALL libd_wexecv)(char16_t const *__restrict path,
                                  __T16ARGV)
/*[[[body:DOS$wexecv]]]*/
{
	return libc_do_c16exec(path, ___argv, NULL, false);
}
/*[[[end:DOS$wexecv]]]*/

/*[[[head:wexecve,hash:CRC-32=0x94034cd2]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexecve") int
NOTHROW_RPC(LIBCCALL libc_wexecve)(char32_t const *__restrict path,
                                   __T32ARGV,
                                   __T32ENVP)
/*[[[body:wexecve]]]*/
{
	return libc_do_c32exec(path, ___argv, ___envp, false);
}
/*[[[end:wexecve]]]*/

/*[[[head:DOS$wexecve,hash:CRC-32=0xb0746e8b]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexecve") int
NOTHROW_RPC(LIBDCALL libd_wexecve)(char16_t const *__restrict path,
                                   __T16ARGV,
                                   __T16ENVP)
/*[[[body:DOS$wexecve]]]*/
{
	return libc_do_c16exec(path, ___argv, ___envp, false);
}
/*[[[end:DOS$wexecve]]]*/

/*[[[head:wexecvp,hash:CRC-32=0xbc4f78a4]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexecvp") int
NOTHROW_RPC(LIBCCALL libc_wexecvp)(char32_t const *__restrict file,
                                   __T32ARGV)
/*[[[body:wexecvp]]]*/
{
	return libc_do_c32exec(file, ___argv, NULL, true);
}
/*[[[end:wexecvp]]]*/

/*[[[head:DOS$wexecvp,hash:CRC-32=0x9601ca1]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexecvp") int
NOTHROW_RPC(LIBDCALL libd_wexecvp)(char16_t const *__restrict file,
                                   __T16ARGV)
/*[[[body:DOS$wexecvp]]]*/
{
	return libc_do_c16exec(file, ___argv, NULL, true);
}
/*[[[end:DOS$wexecvp]]]*/

/*[[[head:wexecvpe,hash:CRC-32=0xcb98311e]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexecvpe") int
NOTHROW_RPC(LIBCCALL libc_wexecvpe)(char32_t const *__restrict file,
                                    __T32ARGV,
                                    __T32ENVP)
/*[[[body:wexecvpe]]]*/
{
	return libc_do_c32exec(file, ___argv, ___envp, true);
}
/*[[[end:wexecvpe]]]*/

/*[[[head:DOS$wexecvpe,hash:CRC-32=0x9ae47d70]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexecvpe") int
NOTHROW_RPC(LIBDCALL libd_wexecvpe)(char16_t const *__restrict file,
                                    __T16ARGV,
                                    __T16ENVP)
/*[[[body:DOS$wexecvpe]]]*/
{
	return libc_do_c16exec(file, ___argv, ___envp, true);
}
/*[[[end:DOS$wexecvpe]]]*/

/*[[[head:wexecl,hash:CRC-32=0x65662067]]]*/
INTERN ATTR_SENTINEL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexecl") int
NOTHROW_RPC(VLIBCCALL libc_wexecl)(char32_t const *__restrict path,
                                   char32_t const *args,
                                   ... /*, (wchar_t *)NULL*/)
/*[[[body:wexecl]]]*/
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
/*[[[end:wexecl]]]*/

/*[[[head:DOS$wexecl,hash:CRC-32=0x6a918260]]]*/
INTERN ATTR_SENTINEL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexecl") int
NOTHROW_RPC(VLIBDCALL libd_wexecl)(char16_t const *__restrict path,
                                   char16_t const *args,
                                   ... /*, (wchar_t *)NULL*/)
/*[[[body:DOS$wexecl]]]*/
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
/*[[[end:DOS$wexecl]]]*/

/*[[[head:wexecle,hash:CRC-32=0xd764a989]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexecle") int
NOTHROW_RPC(VLIBCCALL libc_wexecle)(char32_t const *__restrict path,
                                    char32_t const *args,
                                    ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:wexecle]]]*/
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
/*[[[end:wexecle]]]*/

/*[[[head:DOS$wexecle,hash:CRC-32=0x6cc3e456]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexecle") int
NOTHROW_RPC(VLIBDCALL libd_wexecle)(char16_t const *__restrict path,
                                    char16_t const *args,
                                    ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:DOS$wexecle]]]*/
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
/*[[[end:DOS$wexecle]]]*/

/*[[[head:wexeclp,hash:CRC-32=0xb1930363]]]*/
INTERN ATTR_SENTINEL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexeclp") int
NOTHROW_RPC(VLIBCCALL libc_wexeclp)(char32_t const *__restrict file,
                                    char32_t const *args,
                                    ... /*, (wchar_t *)NULL*/)
/*[[[body:wexeclp]]]*/
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
/*[[[end:wexeclp]]]*/

/*[[[head:DOS$wexeclp,hash:CRC-32=0x9eaa14d2]]]*/
INTERN ATTR_SENTINEL NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexeclp") int
NOTHROW_RPC(VLIBDCALL libd_wexeclp)(char16_t const *__restrict file,
                                    char16_t const *args,
                                    ... /*, (wchar_t *)NULL*/)
/*[[[body:DOS$wexeclp]]]*/
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
/*[[[end:DOS$wexeclp]]]*/

/*[[[head:wexeclpe,hash:CRC-32=0x95579611]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.exec.wexeclpe") int
NOTHROW_RPC(VLIBCCALL libc_wexeclpe)(char32_t const *__restrict file,
                                     char32_t const *args,
                                     ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:wexeclpe]]]*/
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
/*[[[end:wexeclpe]]]*/

/*[[[head:DOS$wexeclpe,hash:CRC-32=0xa31fed53]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.exec.wexeclpe") int
NOTHROW_RPC(VLIBDCALL libd_wexeclpe)(char16_t const *__restrict file,
                                     char16_t const *args,
                                     ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:DOS$wexeclpe]]]*/
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
/*[[[end:DOS$wexeclpe]]]*/

/*[[[head:wspawnv,hash:CRC-32=0xc0986f2a]]]*/
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnv") pid_t
NOTHROW_RPC(LIBCCALL libc_wspawnv)(int mode,
                                   char32_t const *__restrict path,
                                   __T32ARGV)
/*[[[body:wspawnv]]]*/
{
	return libc_do_c32spawn(mode, path, ___argv, NULL, false);
}
/*[[[end:wspawnv]]]*/

/*[[[head:DOS$wspawnv,hash:CRC-32=0x34e391aa]]]*/
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnv") pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnv)(int mode,
                                   char16_t const *__restrict path,
                                   __T16ARGV)
/*[[[body:DOS$wspawnv]]]*/
{
	return libc_do_c16spawn(mode, path, ___argv, NULL, false);
}
/*[[[end:DOS$wspawnv]]]*/

/*[[[head:wspawnve,hash:CRC-32=0x181a5ef0]]]*/
INTERN NONNULL((2, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnve") pid_t
NOTHROW_RPC(LIBCCALL libc_wspawnve)(int mode,
                                    char32_t const *__restrict path,
                                    __T32ARGV,
                                    __T32ENVP)
/*[[[body:wspawnve]]]*/
{
	return libc_do_c32spawn(mode, path, ___argv, ___envp, false);
}
/*[[[end:wspawnve]]]*/

/*[[[head:DOS$wspawnve,hash:CRC-32=0x18bbc8d7]]]*/
INTERN NONNULL((2, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnve") pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnve)(int mode,
                                    char16_t const *__restrict path,
                                    __T16ARGV,
                                    __T16ENVP)
/*[[[body:DOS$wspawnve]]]*/
{
	return libc_do_c16spawn(mode, path, ___argv, ___envp, false);
}
/*[[[end:DOS$wspawnve]]]*/

/*[[[head:wspawnvp,hash:CRC-32=0xe4276940]]]*/
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnvp") pid_t
NOTHROW_RPC(LIBCCALL libc_wspawnvp)(int mode,
                                    char32_t const *__restrict file,
                                    __T32ARGV)
/*[[[body:wspawnvp]]]*/
{
	return libc_do_c32spawn(mode, file, ___argv, NULL, true);
}
/*[[[end:wspawnvp]]]*/

/*[[[head:DOS$wspawnvp,hash:CRC-32=0xd97ba375]]]*/
INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnvp") pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnvp)(int mode,
                                    char16_t const *__restrict file,
                                    __T16ARGV)
/*[[[body:DOS$wspawnvp]]]*/
{
	return libc_do_c16spawn(mode, file, ___argv, NULL, true);
}
/*[[[end:DOS$wspawnvp]]]*/

/*[[[head:wspawnvpe,hash:CRC-32=0xc86d3bb6]]]*/
INTERN NONNULL((2, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnvpe") pid_t
NOTHROW_RPC(LIBCCALL libc_wspawnvpe)(int mode,
                                     char32_t const *__restrict file,
                                     __T32ARGV,
                                     __T32ENVP)
/*[[[body:wspawnvpe]]]*/
{
	return libc_do_c32spawn(mode, file, ___argv, ___envp, true);
}
/*[[[end:wspawnvpe]]]*/

/*[[[head:DOS$wspawnvpe,hash:CRC-32=0xd0df20a4]]]*/
INTERN NONNULL((2, 3, 4))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnvpe") pid_t
NOTHROW_RPC(LIBDCALL libd_wspawnvpe)(int mode,
                                     char16_t const *__restrict file,
                                     __T16ARGV,
                                     __T16ENVP)
/*[[[body:DOS$wspawnvpe]]]*/
{
	return libc_do_c16spawn(mode, file, ___argv, ___envp, true);
}
/*[[[end:DOS$wspawnvpe]]]*/

/*[[[head:wspawnl,hash:CRC-32=0xccd275a0]]]*/
INTERN ATTR_SENTINEL NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnl") pid_t
NOTHROW_RPC(VLIBCCALL libc_wspawnl)(int mode,
                                    char32_t const *__restrict path,
                                    char32_t const *args,
                                    ... /*, (wchar_t *)NULL*/)
/*[[[body:wspawnl]]]*/
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
/*[[[end:wspawnl]]]*/

/*[[[head:DOS$wspawnl,hash:CRC-32=0xd6e83385]]]*/
INTERN ATTR_SENTINEL NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnl") pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnl)(int mode,
                                    char16_t const *__restrict path,
                                    char16_t const *args,
                                    ... /*, (wchar_t *)NULL*/)
/*[[[body:DOS$wspawnl]]]*/
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
/*[[[end:DOS$wspawnl]]]*/

/*[[[head:wspawnle,hash:CRC-32=0x806ceda8]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnle") pid_t
NOTHROW_RPC(VLIBCCALL libc_wspawnle)(int mode,
                                     char32_t const *__restrict path,
                                     char32_t const *args,
                                     ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:wspawnle]]]*/
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
/*[[[end:wspawnle]]]*/

/*[[[head:DOS$wspawnle,hash:CRC-32=0x2d1d427b]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnle") pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnle)(int mode,
                                     char16_t const *__restrict path,
                                     char16_t const *args,
                                     ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:DOS$wspawnle]]]*/
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
/*[[[end:DOS$wspawnle]]]*/

/*[[[head:wspawnlp,hash:CRC-32=0x804d31eb]]]*/
INTERN ATTR_SENTINEL NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnlp") pid_t
NOTHROW_RPC(VLIBCCALL libc_wspawnlp)(int mode,
                                     char32_t const *__restrict file,
                                     char32_t const *args,
                                     ... /*, (wchar_t *)NULL*/)
/*[[[body:wspawnlp]]]*/
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
/*[[[end:wspawnlp]]]*/

/*[[[head:DOS$wspawnlp,hash:CRC-32=0xef6dab6]]]*/
INTERN ATTR_SENTINEL NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnlp") pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnlp)(int mode,
                                     char16_t const *__restrict file,
                                     char16_t const *args,
                                     ... /*, (wchar_t *)NULL*/)
/*[[[body:DOS$wspawnlp]]]*/
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
/*[[[end:DOS$wspawnlp]]]*/

/*[[[head:wspawnlpe,hash:CRC-32=0xb33f601c]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.spawn.wspawnlpe") pid_t
NOTHROW_RPC(VLIBCCALL libc_wspawnlpe)(int mode,
                                      char32_t const *__restrict file,
                                      char32_t const *args,
                                      ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:wspawnlpe]]]*/
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
/*[[[end:wspawnlpe]]]*/

/*[[[head:DOS$wspawnlpe,hash:CRC-32=0xb99d6296]]]*/
INTERN ATTR_SENTINEL_O(1) NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.spawn.wspawnlpe") pid_t
NOTHROW_RPC(VLIBDCALL libd_wspawnlpe)(int mode,
                                      char16_t const *__restrict file,
                                      char16_t const *args,
                                      ... /*, (wchar_t *)NULL, wchar_t **environ*/)
/*[[[body:DOS$wspawnlpe]]]*/
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
/*[[[end:DOS$wspawnlpe]]]*/

/*[[[head:wsystem,hash:CRC-32=0xceaf1ad0]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.fs.exec.system.wsystem") int
NOTHROW_RPC(LIBCCALL libc_wsystem)(char32_t const *cmd)
/*[[[body:wsystem]]]*/
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
/*[[[end:wsystem]]]*/

/*[[[head:DOS$wsystem,hash:CRC-32=0xeef624e3]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.exec.system.wsystem") int
NOTHROW_RPC(LIBDCALL libd_wsystem)(char16_t const *cmd)
/*[[[body:DOS$wsystem]]]*/
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
/*[[[end:DOS$wsystem]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xc6531083]]]*/
#undef wexecl
#undef _wexecl
#undef wexeclp
#undef _wexeclp
#undef wexecle
#undef _wexecle
#undef wexeclpe
#undef _wexeclpe
#undef wspawnl
#undef _wspawnl
#undef wspawnlp
#undef _wspawnlp
#undef wspawnle
#undef _wspawnle
#undef wspawnlpe
#undef _wspawnlpe
DEFINE_PUBLIC_WEAK_ALIAS(wexecv, libc_wexecv);
DEFINE_PUBLIC_WEAK_ALIAS(_wexecv, libc_wexecv);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecv, libd_wexecv);
DEFINE_PUBLIC_WEAK_ALIAS(wexecve, libc_wexecve);
DEFINE_PUBLIC_WEAK_ALIAS(_wexecve, libc_wexecve);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecve, libd_wexecve);
DEFINE_PUBLIC_WEAK_ALIAS(wexecvp, libc_wexecvp);
DEFINE_PUBLIC_WEAK_ALIAS(_wexecvp, libc_wexecvp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecvp, libd_wexecvp);
DEFINE_PUBLIC_WEAK_ALIAS(wexecvpe, libc_wexecvpe);
DEFINE_PUBLIC_WEAK_ALIAS(_wexecvpe, libc_wexecvpe);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecvpe, libd_wexecvpe);
DEFINE_PUBLIC_WEAK_ALIAS(wexecl, libc_wexecl);
DEFINE_PUBLIC_WEAK_ALIAS(_wexecl, libc_wexecl);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecl, libd_wexecl);
DEFINE_PUBLIC_WEAK_ALIAS(wexeclp, libc_wexeclp);
DEFINE_PUBLIC_WEAK_ALIAS(_wexeclp, libc_wexeclp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexeclp, libd_wexeclp);
DEFINE_PUBLIC_WEAK_ALIAS(wexecle, libc_wexecle);
DEFINE_PUBLIC_WEAK_ALIAS(_wexecle, libc_wexecle);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecle, libd_wexecle);
DEFINE_PUBLIC_WEAK_ALIAS(wexeclpe, libc_wexeclpe);
DEFINE_PUBLIC_WEAK_ALIAS(_wexeclpe, libc_wexeclpe);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wexecle, libd_wexeclpe);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnv, libc_wspawnv);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnv, libc_wspawnv);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnv, libd_wspawnv);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnve, libc_wspawnve);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnve, libc_wspawnve);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnve, libd_wspawnve);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnvp, libc_wspawnvp);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnvp, libc_wspawnvp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnvp, libd_wspawnvp);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnvpe, libc_wspawnvpe);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnvpe, libc_wspawnvpe);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnvpe, libd_wspawnvpe);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnl, libc_wspawnl);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnl, libc_wspawnl);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnl, libd_wspawnl);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnlp, libc_wspawnlp);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnlp, libc_wspawnlp);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnlp, libd_wspawnlp);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnle, libc_wspawnle);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnle, libc_wspawnle);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnle, libd_wspawnle);
DEFINE_PUBLIC_WEAK_ALIAS(wspawnlpe, libc_wspawnlpe);
DEFINE_PUBLIC_WEAK_ALIAS(_wspawnlpe, libc_wspawnlpe);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wspawnle, libd_wspawnlpe);
DEFINE_PUBLIC_WEAK_ALIAS(wsystem, libc_wsystem);
DEFINE_PUBLIC_WEAK_ALIAS(_wsystem, libc_wsystem);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wsystem, libd_wsystem);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_PROCESS_C */
