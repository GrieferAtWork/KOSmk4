/* HASH CRC-32:0x7e718eee */
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
/* (#) Portability: Cygwin (/newlib/libc/include/sys/config.h) */
/* (#) Portability: DJGPP  (/include/sys/config.h) */
/* (#) Portability: Newlib (/newlib/libc/include/sys/config.h) */
#ifndef _SYS_CONFIG_H
#define _SYS_CONFIG_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

/* This one's kind-of a weird header, in that there's no real standard out there
 * that defines what should go in here... And I'm also not entirely sure if this
 * is actually a ~real~ header that is meant to be exposed in any way, shape, or
 * form.
 * However, I've seen it as part of djgpp, but I think it has to do with autoconf,
 * and I kind-of like the idea behind this kind of header.
 * Anyways: What can be found below should be fairly self-explanatory.
 * Also:  With  magic, it's  fairly  easy to  automate  this header... */

#include <features.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>
#include <asm/os/limits.h>
#include <bits/types.h>

#undef STDC_HEADERS
#define STDC_HEADERS 1

#undef HAVE_AR_H
#undef HAVE_ASSERT_H
#undef HAVE_COFF_H
#undef HAVE_CTYPE_H
#undef DIRENT
#undef HAVE_DIRENT_H
#undef HAVE_ERRNO_H
#undef HAVE_FCNTL_H
#undef HAVE_FLOAT_H
#undef HAVE_FNMATCH_H
#undef HAVE_FTW_H
#undef HAVE_GLOB_H
#undef HAVE_GRP_H
#undef HAVE_IO_H
#undef HAVE_LIMITS_H
#undef HAVE_LOCALE_H
#undef HAVE_MATH_H
#undef HAVE_MNTENT_H
#undef HAVE_PWD_H
#undef HAVE_SEARCH_H
#undef HAVE_SETJMP_H
#undef HAVE_SIGNAL_H
#undef HAVE_STDARG_H
#undef HAVE_STDDEF_H
#undef HAVE_STDIO_H
#undef HAVE_STDLIB_H
#undef HAVE_STRING_H
#undef HAVE_TERMIOS_H
#undef HAVE_TIME_H
#undef HAVE_SYS_TIME_H
#undef HAVE_UNISTD_H
#undef HAVE_UTIME_H
#undef HAVE_VALUES_H
#undef HAVE_VARARGS_H
#undef HAVE_NETINET_IN_H
#undef HAVE_SYS_FILE_H
#undef HAVE_SYS_IOCTL_H
#undef HAVE_SYS_PARAM_H
#undef HAVE_SYS_RESOURCE_H
#undef HAVE_SYS_STAT_H
#undef HAVE_SYS_TIME_H
#undef HAVE_SYS_TIMEB_H
#undef HAVE_SYS_TIMES_H
#undef HAVE_SYS_TYPES_H
#undef HAVE_SYS_UTSNAME_H
#undef HAVE_SYS_VFS_H
#undef HAVE_SYS_WAIT_H

#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<ar.h>)
#define HAVE_AR_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<ar.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<assert.h>)
#define HAVE_ASSERT_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<assert.h>) */
#if __has_include(<coff.h>)
#define HAVE_COFF_H 1
#endif /* __has_include(<coff.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<ctype.h>)
#define HAVE_CTYPE_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<ctype.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<dirent.h>)
#define DIRENT        1
#define HAVE_DIRENT_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<dirent.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<errno.h>)
#define HAVE_ERRNO_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<errno.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<fcntl.h>)
#define HAVE_FCNTL_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<fcntl.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<float.h>)
#define HAVE_FLOAT_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<float.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<fnmatch.h>)
#define HAVE_FNMATCH_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<fnmatch.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<ftw.h>)
#define HAVE_FTW_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<ftw.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<glob.h>)
#define HAVE_GLOB_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<glob.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<grp.h>)
#define HAVE_GRP_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<grp.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<io.h>)
#define HAVE_IO_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<io.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<limits.h>)
#define HAVE_LIMITS_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<limits.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<locale.h>)
#define HAVE_LOCALE_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<locale.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<math.h>)
#define HAVE_MATH_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<math.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<mntent.h>)
#define HAVE_MNTENT_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<mntent.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<pwd.h>)
#define HAVE_PWD_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<pwd.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<search.h>)
#define HAVE_SEARCH_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<search.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<setjmp.h>)
#define HAVE_SETJMP_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<setjmp.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<signal.h>)
#define HAVE_SIGNAL_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<signal.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<stdarg.h>)
#define HAVE_STDARG_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<stdarg.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<stddef.h>)
#define HAVE_STDDEF_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<stddef.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<stdio.h>)
#define HAVE_STDIO_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<stdio.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<stdlib.h>)
#define HAVE_STDLIB_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<stdlib.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<string.h>)
#define HAVE_STRING_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<string.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<termios.h>)
#define HAVE_TERMIOS_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<termios.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<time.h>)
#define HAVE_TIME_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<time.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<sys/time.h>)
#define HAVE_SYS_TIME_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<sys/time.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<unistd.h>)
#define HAVE_UNISTD_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<unistd.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<utime.h>)
#define HAVE_UTIME_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<utime.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<values.h>)
#define HAVE_VALUES_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<values.h>) */
#if __has_include(<varargs.h>)
#define HAVE_VARARGS_H 1
#endif /* __has_include(<varargs.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<netinet/in.h>)
#define HAVE_NETINET_IN_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<netinet/in.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<sys/file.h>)
#define HAVE_SYS_FILE_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<sys/file.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<sys/ioctl.h>)
#define HAVE_SYS_IOCTL_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<sys/ioctl.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<sys/param.h>)
#define HAVE_SYS_PARAM_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<sys/param.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<sys/resource.h>)
#define HAVE_SYS_RESOURCE_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<sys/resource.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<sys/stat.h>)
#define HAVE_SYS_STAT_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<sys/stat.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<sys/time.h>)
#define HAVE_SYS_TIME_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<sys/time.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<sys/timeb.h>)
#define HAVE_SYS_TIMEB_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<sys/timeb.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<sys/times.h>)
#define HAVE_SYS_TIMES_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<sys/times.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<sys/types.h>)
#define HAVE_SYS_TYPES_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<sys/types.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<sys/utsname.h>)
#define HAVE_SYS_UTSNAME_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<sys/utsname.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<sys/vfs.h>)
#define HAVE_SYS_VFS_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<sys/vfs.h>) */
#if defined(__KOS_SYSTEM_HEADERS__) || __has_include(<sys/wait.h>)
#define HAVE_SYS_WAIT_H 1
#endif /* __KOS_SYSTEM_HEADERS__ || __has_include(<sys/wait.h>) */

#undef TIME_WITH_SYS_TIME
#if defined(__KOS_SYSTEM_HEADERS__) || 1
#define TIME_WITH_SYS_TIME 1 /* <time.h> and <sys/time.h> work together. */
#endif /* __KOS_SYSTEM_HEADERS__ || 1 */

#undef HAVE_SYS_SIGLIST
#if defined(__CRT_HAVE_sys_siglist) || defined(__CRT_HAVE__sys_siglist) || defined(__CRT_HAVE___p_sys_siglist)
#define HAVE_SYS_SIGLIST 1
#endif /* __CRT_HAVE_sys_siglist || __CRT_HAVE__sys_siglist || __CRT_HAVE___p_sys_siglist */





#ifdef __KOS_SYSTEM_HEADERS__
#undef HAVE_BCMP
#define HAVE_BCMP 1

#undef HAVE_BCOPY
#define HAVE_BCOPY 1

#undef HAVE_CLOSEDIR
#if defined(__CRT_HAVE_closedir) || defined(__CRT_HAVE___libc_closedir)
#define HAVE_CLOSEDIR 1
#endif /* __CRT_HAVE_closedir || __CRT_HAVE___libc_closedir */

#undef HAVE_DUP2
#if defined(__CRT_HAVE_dup2) || defined(__CRT_HAVE__dup2) || defined(__CRT_HAVE___dup2) || defined(__CRT_HAVE___libc_dup2)
#define HAVE_DUP2 1
#endif /* __CRT_HAVE_dup2 || __CRT_HAVE__dup2 || __CRT_HAVE___dup2 || __CRT_HAVE___libc_dup2 */

#undef HAVE_ENDGRENT
#ifdef __CRT_HAVE_endgrent
#define HAVE_ENDGRENT 1
#endif /* __CRT_HAVE_endgrent */

#undef HAVE_ENDPWENT
#ifdef __CRT_HAVE_endpwent
#define HAVE_ENDPWENT 1
#endif /* __CRT_HAVE_endpwent */

#undef HAVE_FNMATCH
#define HAVE_FNMATCH 1

#undef HAVE_FREXP
#include <ieee754.h>
#if defined(__CRT_HAVE_frexp) || defined(__CRT_HAVE___frexp) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#define HAVE_FREXP 1
#endif /* __CRT_HAVE_frexp || __CRT_HAVE___frexp || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */

#undef HAVE_FTIME
#if defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime64) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE_ftime64)
#define HAVE_FTIME 1
#endif /* __CRT_HAVE__ftime32_s || __CRT_HAVE__ftime64_s || __CRT_HAVE__ftime32 || __CRT_HAVE__ftime64 || __CRT_HAVE_ftime || __CRT_HAVE_ftime64 */

#undef HAVE_FTRUNCATE
#if defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)
#define HAVE_FTRUNCATE 1
#endif /* __CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize */

#undef HAVE_FTW
#include <bits/os/stat.h>
#if (defined(__CRT_HAVE_ftw) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))) || (defined(__CRT_HAVE_ftw64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)))
#define HAVE_FTW 1
#endif /* (__CRT_HAVE_ftw && (!__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) || (__CRT_HAVE_ftw64 && (__USE_FILE_OFFSET64 || __STAT32_MATCHES_STAT64)) */

#undef HAVE_GETCWD
#if defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
#define HAVE_GETCWD 1
#endif /* __CRT_HAVE_getcwd || __CRT_HAVE__getcwd */

#undef HAVE_GETDTABLESIZE
#define HAVE_GETDTABLESIZE 1

#undef HAVE_GETGROUPS
#if defined(__CRT_HAVE_getgroups) || defined(__CRT_HAVE___getgroups) || defined(__CRT_HAVE___libc_getgroups)
#define HAVE_GETGROUPS 1
#endif /* __CRT_HAVE_getgroups || __CRT_HAVE___getgroups || __CRT_HAVE___libc_getgroups */

#undef HAVE_GETHOSTNAME
#if defined(__CRT_HAVE_gethostname) || defined(__CRT_HAVE___gethostname)
#define HAVE_GETHOSTNAME 1
#endif /* __CRT_HAVE_gethostname || __CRT_HAVE___gethostname */

#undef HAVE_GETMNTENT
#if defined(__CRT_HAVE_getmntent) || defined(__CRT_HAVE_getmntent_r) || defined(__CRT_HAVE___getmntent_r) || defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE__IO_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))
#define HAVE_GETMNTENT 1
#endif /* __CRT_HAVE_getmntent || __CRT_HAVE_getmntent_r || __CRT_HAVE___getmntent_r || __CRT_HAVE_fgets || __CRT_HAVE__IO_fgets || __CRT_HAVE_fgets_unlocked || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked)) */

#undef HAVE_GETPAGESIZE
#include <asm/pagesize.h>
#if defined(__CRT_HAVE_getpagesize) || defined(__CRT_HAVE___getpagesize) || defined(__ARCH_PAGESIZE)
#define HAVE_GETPAGESIZE 1
#endif /* __CRT_HAVE_getpagesize || __CRT_HAVE___getpagesize || __ARCH_PAGESIZE */

#undef HAVE_GETTIMEOFDAY
#if defined(__CRT_HAVE_gettimeofday64) || defined(__CRT_HAVE_gettimeofday) || defined(__CRT_HAVE___gettimeofday) || defined(__CRT_HAVE___libc_gettimeofday)
#define HAVE_GETTIMEOFDAY 1
#endif /* __CRT_HAVE_gettimeofday64 || __CRT_HAVE_gettimeofday || __CRT_HAVE___gettimeofday || __CRT_HAVE___libc_gettimeofday */

#undef HAVE_GLOB
#define HAVE_GLOB 1

#undef HAVE_ISASCII
#define HAVE_ISASCII 1

#undef HAVE_MEMCHR
#define HAVE_MEMCHR 1

#undef HAVE_MEMCPY
#define HAVE_MEMCPY 1

#undef HAVE_MKDIR
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_mkdir) || defined(__CRT_HAVE___mkdir) || defined(__CRT_HAVE___libc_mkdir) || (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)))
#define HAVE_MKDIR 1
#endif /* __CRT_HAVE_mkdir || __CRT_HAVE___mkdir || __CRT_HAVE___libc_mkdir || (__CRT_DOS_PRIMARY && __CRT_HAVE__mkdir) || (__AT_FDCWD && (__CRT_HAVE_mkdirat || __CRT_HAVE_fmkdirat)) */

#undef HAVE_MKFIFO
#include <asm/os/stat.h>
#if defined(__CRT_HAVE_mkfifo) || ((defined(__CRT_HAVE_mknod) || ((defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && defined(__AT_FDCWD))) && defined(__S_IFIFO))
#define HAVE_MKFIFO 1
#endif /* __CRT_HAVE_mkfifo || ((__CRT_HAVE_mknod || ((__CRT_HAVE_mknodat || __CRT_HAVE_fmknodat) && __AT_FDCWD)) && __S_IFIFO) */

#undef HAVE_MKTIME
#define HAVE_MKTIME 1

#undef HAVE_POW
#if defined(__CRT_HAVE_pow) || defined(__CRT_HAVE___pow) || defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)
#define HAVE_POW 1
#endif /* __CRT_HAVE_pow || __CRT_HAVE___pow || __IEEE754_DOUBLE_TYPE_IS_DOUBLE__ || __IEEE754_FLOAT_TYPE_IS_DOUBLE__ || __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ */

#undef HAVE_PUTENV
#if defined(__CRT_HAVE_putenv) || defined(__CRT_HAVE__putenv)
#define HAVE_PUTENV 1
#endif /* __CRT_HAVE_putenv || __CRT_HAVE__putenv */

#undef HAVE_RANDOM
#define HAVE_RANDOM 1

#undef HAVE_RENAME
#if defined(__CRT_HAVE_rename) || defined(__CRT_HAVE___rename) || defined(__CRT_HAVE___libc_rename) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_renameat) || defined(__CRT_HAVE_renameat2)))
#define HAVE_RENAME 1
#endif /* __CRT_HAVE_rename || __CRT_HAVE___rename || __CRT_HAVE___libc_rename || (__AT_FDCWD && (__CRT_HAVE_renameat || __CRT_HAVE_renameat2)) */

#undef HAVE_RMDIR
#if defined(__CRT_HAVE_rmdir) || defined(__CRT_HAVE__rmdir) || defined(__CRT_HAVE___rmdir) || defined(__CRT_HAVE___libc_rmdir) || (defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && defined(__CRT_HAVE_unlinkat))
#define HAVE_RMDIR 1
#endif /* __CRT_HAVE_rmdir || __CRT_HAVE__rmdir || __CRT_HAVE___rmdir || __CRT_HAVE___libc_rmdir || (__AT_FDCWD && __AT_REMOVEDIR && __CRT_HAVE_unlinkat) */

#undef HAVE_SETENV
#include <libc/template/environ.h>
#if defined(__CRT_HAVE_setenv) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && defined(__CRT_HAVE__putenv_s))
#define HAVE_SETENV 1
#endif /* __CRT_HAVE_setenv || ((__CRT_HAVE_getenv || __LOCAL_environ) && __CRT_HAVE__putenv_s) */

#undef HAVE_SETLINEBUF
#if defined(__CRT_HAVE_setlinebuf) || defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked)
#define HAVE_SETLINEBUF 1
#endif /* __CRT_HAVE_setlinebuf || __CRT_HAVE_setvbuf || __CRT_HAVE__IO_setvbuf || __CRT_HAVE_setvbuf_unlocked */

#undef HAVE_SETLOCALE
#ifdef __CRT_HAVE_setlocale
#define HAVE_SETLOCALE 1
#endif /* __CRT_HAVE_setlocale */

#undef HAVE_SIGACTION
#if defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)
#define HAVE_SIGACTION 1
#endif /* __CRT_HAVE_sigaction || __CRT_HAVE___sigaction */

#undef HAVE_STPCPY
#define HAVE_STPCPY 1

#undef HAVE_STRCASECMP
#define HAVE_STRCASECMP 1

#undef HAVE_STRCHR
#define HAVE_STRCHR 1

#undef HAVE_STRRCHR
#define HAVE_STRRCHR 1

#undef HAVE_STRCOLL
#define HAVE_STRCOLL 1

#undef HAVE_STRDUP
#if defined(__CRT_HAVE_strdup) || defined(__CRT_HAVE__strdup) || defined(__CRT_HAVE___strdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#define HAVE_STRDUP 1
#endif /* __CRT_HAVE_strdup || __CRT_HAVE__strdup || __CRT_HAVE___strdup || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */

#undef HAVE_STRFTIME
#define HAVE_STRFTIME 1

#undef HAVE_STRERROR
#define HAVE_STRERROR 1

#undef HAVE_VPRINTF
#include <libc/template/stdstreams.h>
#if defined(__CRT_HAVE_vprintf) || defined(__CRT_HAVE_vprintf_s) || defined(__CRT_HAVE_vprintf_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)))
#define HAVE_VPRINTF 1
#endif /* __CRT_HAVE_vprintf || __CRT_HAVE_vprintf_s || __CRT_HAVE_vprintf_unlocked || (__LOCAL_stdout && (__CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock)) */

#undef HAVE_WAITPID
#if defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)
#define HAVE_WAITPID 1
#endif /* __CRT_HAVE_waitpid || __CRT_HAVE___waitpid */

#undef GETPGRP_VOID
#if defined(__CRT_HAVE_getpgrp) || defined(__CRT_HAVE___getpgrp) || defined(__CRT_HAVE___libc_getpgrp)
#define GETPGRP_VOID 1 /* 0-argument getpgrp() version */
#endif /* __CRT_HAVE_getpgrp || __CRT_HAVE___getpgrp || __CRT_HAVE___libc_getpgrp */

#undef MOUNTED_GETMNTENT1
#if defined(__CRT_HAVE_getmntent) || defined(__CRT_HAVE_getmntent_r) || defined(__CRT_HAVE___getmntent_r) || defined(__CRT_HAVE_fgets) || defined(__CRT_HAVE__IO_fgets) || defined(__CRT_HAVE_fgets_unlocked) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))
#define MOUNTED_GETMNTENT1 1 /* 1-argument getmntent() version */
#endif /* __CRT_HAVE_getmntent || __CRT_HAVE_getmntent_r || __CRT_HAVE___getmntent_r || __CRT_HAVE_fgets || __CRT_HAVE__IO_fgets || __CRT_HAVE_fgets_unlocked || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked)) */

#undef STAT_STATFS2_BSIZE
#if (defined(__CRT_HAVE_statfs) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE___statfs) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE___libc_statfs) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (defined(__CRT_HAVE_statfs64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__))
#define STAT_STATFS2_BSIZE 1 /* Actually requires that statfs() takes 2 arguments,
                              * and    that    `struct statfs::f_bsize'    exists! */
#endif /* (__CRT_HAVE_statfs && (!__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (__CRT_HAVE___statfs && (!__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (__CRT_HAVE___libc_statfs && (!__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) || (__CRT_HAVE_statfs64 && (__USE_FILE_OFFSET64 || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)) */

#undef HAVE_UTIME_NULL
#if defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime32) || defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64)
#define HAVE_UTIME_NULL 1 /* Second argument to utime() can be NULL for current time. */
#endif /* __CRT_HAVE_utime || __CRT_HAVE___utime || __CRT_HAVE___libc_utime || __CRT_HAVE__utime32 || __CRT_HAVE_utime64 || __CRT_HAVE__utime64 */



#include <bits/os/stat.h> /* _STATBUF_ST_xxx */
#undef HAVE_ST_BLKSIZE
#ifdef _STATBUF_ST_BLKSIZE
#define HAVE_ST_BLKSIZE 1 /* `struct stat::st_blksize' */
#endif /* _STATBUF_ST_BLKSIZE */

#undef HAVE_ST_BLOCKS
#ifdef _STATBUF_ST_BLOCKS
#define HAVE_ST_BLOCKS 1 /* `struct stat::st_blocks' */
#endif /* _STATBUF_ST_BLOCKS */

#undef HAVE_ST_RDEV
#ifdef _STATBUF_ST_RDEV
#define HAVE_ST_RDEV 1
#endif /* _STATBUF_ST_RDEV */

#undef HAVE_STRUCT_UTIMBUF
#define HAVE_STRUCT_UTIMBUF 1

#undef HAVE_TIMEVAL
#define HAVE_TIMEVAL 1

#undef HAVE_TM_ZONE
#include <bits/crt/tm.h>
#ifdef __STRUCT_TM_HAVE_TM_ZONE
#define HAVE_TM_ZONE 1 /* `struct tm::tm_zone' exists. */
#endif /* __STRUCT_TM_HAVE_TM_ZONE */




#undef GETGROUPS_T
#if defined(__CRT_HAVE_getgroups) || defined(__CRT_HAVE___getgroups) || defined(__CRT_HAVE___libc_getgroups)
#define GETGROUPS_T __gid_t /* Vector element type of `getgroups()' */
#endif /* __CRT_HAVE_getgroups || __CRT_HAVE___getgroups || __CRT_HAVE___libc_getgroups */

#undef RETSIGTYPE
#define RETSIGTYPE void /* Return type of `sighandler_t' callbacks */
#endif /* __KOS_SYSTEM_HEADERS__ */

#undef HAVE_SIZE_T
#define HAVE_SIZE_T 1 /* There's always `__SIZE_TYPE__' from `<hybrid/typecore.h>' */

#undef HAVE_LONG_DOUBLE
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define HAVE_LONG_DOUBLE 1
#endif /* __COMPILER_HAVE_LONGDOUBLE */

/* Sizes of built-in types and pointers known to the compiler.  */
#define SIZEOF_CHAR          __SIZEOF_CHAR__
#define SIZEOF_CHAR_P        __SIZEOF_POINTER__
#define SIZEOF_SHORT         __SIZEOF_SHORT__
#define SIZEOF_SHORT_P       __SIZEOF_POINTER__
#define SIZEOF_INT           __SIZEOF_INT__
#define SIZEOF_INT_P         __SIZEOF_POINTER__
#define SIZEOF_LONG          __SIZEOF_LONG__
#define SIZEOF_LONG_P        __SIZEOF_POINTER__
#ifdef __SIZEOF_LONG_LONG__
#define SIZEOF_LONG_LONG     __SIZEOF_LONG_LONG__
#define SIZEOF_LONG_LONG_P   __SIZEOF_POINTER__
#endif /* __SIZEOF_LONG_LONG__ */
#ifndef __NO_FPU
#define SIZEOF_FLOAT         __SIZEOF_FLOAT__
#define SIZEOF_FLOAT_P       __SIZEOF_POINTER__
#define SIZEOF_DOUBLE        __SIZEOF_DOUBLE__
#define SIZEOF_DOUBLE_P      __SIZEOF_POINTER__
#ifdef __SIZEOF_LONG_DOUBLE__
#define SIZEOF_LONG_DOUBLE   __SIZEOF_LONG_DOUBLE__
#define SIZEOF_LONG_DOUBLE_P __SIZEOF_POINTER__
#endif /* __SIZEOF_LONG_DOUBLE__ */
#endif /* !__NO_FPU */
#define SIZEOF_VOID_P        __SIZEOF_POINTER__


#undef STACK_DIRECTION
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
#define STACK_DIRECTION (-1) /* < 0 -> grows toward lower addresses */
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
#define STACK_DIRECTION 1    /* > 0 -> grows toward higher addresses */
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */

#undef NULL_DEVICE
#if (defined(__WINDOWS__) || defined(_WIN16) || defined(WIN16) ||    \
     defined(_WIN32) || defined(WIN32) || defined(_WIN64) ||         \
     defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || \
     defined(_WIN32_WCE) || defined(WIN32_WCE))
#define NULL_DEVICE "NUL"
#else /* ... */
#define NULL_DEVICE "/dev/null"
#endif /* !... */

#undef HAVE_LONG_FILE_NAMES
#if defined(__PATH_MAX) && ((__PATH_MAX < 0) || __PATH_MAX > 256)
#define HAVE_LONG_FILE_NAMES 1
#endif /* __PATH_MAX < 0 || __PATH_MAX > 256 */




/* Cygwin also has a header of the same name, so here is
 * an  approximation of its contents (adjusted for KOS). */
#undef __DYNAMIC_REENT__
#undef __LINUX_ERRNO_EXTENSIONS__
#define __DYNAMIC_REENT__          1
#define __LINUX_ERRNO_EXTENSIONS__ 1

#undef _READ_WRITE_RETURN_TYPE
#undef _READ_WRITE_BUFSIZE_TYPE
#ifdef __KOS_SYSTEM_HEADERS__
#define _READ_WRITE_RETURN_TYPE  __SSIZE_TYPE__
#define _READ_WRITE_BUFSIZE_TYPE __SIZE_TYPE__
#else /* __KOS_SYSTEM_HEADERS__ */
#define _READ_WRITE_RETURN_TYPE  __STDC_INT_AS_SSIZE_T
#define _READ_WRITE_BUFSIZE_TYPE __STDC_INT_AS_SIZE_T
#endif /* !__KOS_SYSTEM_HEADERS__ */

#ifdef __CC__
#ifndef __size_t_defined
#define __size_t_defined
__DECL_BEGIN
typedef __SIZE_TYPE__ size_t;
__DECL_END
#endif /* !__size_t_defined */
#endif /* __CC__ */

#endif /* !_SYS_CONFIG_H */
