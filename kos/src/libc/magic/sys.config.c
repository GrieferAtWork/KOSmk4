/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: Cygwin (/newlib/libc/include/sys/config.h) */
/* (#) Portability: DJGPP  (/include/sys/config.h) */
/* (#) Portability: Newlib (/newlib/libc/include/sys/config.h) */
}

%{
/* This one's kind-of a weird header, in that there's no real standard out there
 * that defines what should go in here... And I'm also not entirely sure if this
 * is actually a ~real~ header that is meant to be exposed in any way, shape, or
 * form.
 * However, I've seen it as part of djgpp, but I think it has to do with autoconf,
 * and I kind-of like the idea behind this kind of header.
 * Anyways: What can be found below should be fairly self-explanatory.
 * Also:  With  magic, it's  fairly  easy to  automate  this header... */

}%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/host.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <asm/os/limits.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

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
}%[insert:pp_if(defined(__CRT_HAVE_sys_siglist) || defined(__CRT_HAVE__sys_siglist) || $has_function(__p_sys_siglist))]%{
#define HAVE_SYS_SIGLIST 1
}%[insert:pp_endif]%{





#ifdef __KOS_SYSTEM_HEADERS__
}
/*[[[deemon
function define_feature(macro, condition) {
	print("%#undef ", macro);
	print("%[insert:pp_if(", condition, ")]");
	print("%#define ", macro, " 1");
	print("%[insert:pp_endif]");
}
function define_has_function(name) {
	define_feature("HAVE_" + name.upper(), f"$has_function({name})");
}

define_has_function("bcmp");
define_has_function("bcopy");
define_has_function("closedir");
define_has_function("dup2");
define_has_function("endgrent");
define_has_function("endpwent");
define_has_function("fnmatch");
define_has_function("frexp");
define_has_function("ftime");
define_has_function("ftruncate");
define_has_function("ftw");
define_has_function("getcwd");
define_has_function("getdtablesize");
define_has_function("getgroups");
define_has_function("gethostname");
define_has_function("getmntent");
define_has_function("getpagesize");
define_has_function("gettimeofday");
define_has_function("glob");
define_has_function("isascii");
define_has_function("memchr");
define_has_function("memcpy");
define_has_function("mkdir");
define_has_function("mkfifo");
define_has_function("mktime");
define_has_function("pow");
define_has_function("putenv");
define_has_function("random");
define_has_function("rename");
define_has_function("rmdir");
define_has_function("setenv");
define_has_function("setlinebuf");
define_has_function("setlocale");
define_has_function("sigaction");
define_has_function("stpcpy");
define_has_function("strcasecmp");
define_has_function("strchr");
define_has_function("strrchr");
define_has_function("strcoll");
define_has_function("strdup");
define_has_function("strftime");
define_has_function("strerror");
define_has_function("vprintf");
define_has_function("waitpid");
define_feature("GETPGRP_VOID", "$has_function(getpgrp)");         // 0-argument getpgrp() version
define_feature("MOUNTED_GETMNTENT1", "$has_function(getmntent)"); // 1-argument getmntent() version
define_feature("STAT_STATFS2_BSIZE", "$has_function(statfs)");    // Actually requires that statfs() takes 2 arguments,
                                                                  // and that `struct statfs::f_bsize' exists!
define_feature("HAVE_UTIME_NULL", "$has_function(utime)");        // Second argument to utime() can be NULL for current time

]]]*/
%#undef HAVE_BCMP
%[insert:pp_if($has_function(bcmp))]
%#define HAVE_BCMP 1
%[insert:pp_endif]
%#undef HAVE_BCOPY
%[insert:pp_if($has_function(bcopy))]
%#define HAVE_BCOPY 1
%[insert:pp_endif]
%#undef HAVE_CLOSEDIR
%[insert:pp_if($has_function(closedir))]
%#define HAVE_CLOSEDIR 1
%[insert:pp_endif]
%#undef HAVE_DUP2
%[insert:pp_if($has_function(dup2))]
%#define HAVE_DUP2 1
%[insert:pp_endif]
%#undef HAVE_ENDGRENT
%[insert:pp_if($has_function(endgrent))]
%#define HAVE_ENDGRENT 1
%[insert:pp_endif]
%#undef HAVE_ENDPWENT
%[insert:pp_if($has_function(endpwent))]
%#define HAVE_ENDPWENT 1
%[insert:pp_endif]
%#undef HAVE_FNMATCH
%[insert:pp_if($has_function(fnmatch))]
%#define HAVE_FNMATCH 1
%[insert:pp_endif]
%#undef HAVE_FREXP
%[insert:pp_if($has_function(frexp))]
%#define HAVE_FREXP 1
%[insert:pp_endif]
%#undef HAVE_FTIME
%[insert:pp_if($has_function(ftime))]
%#define HAVE_FTIME 1
%[insert:pp_endif]
%#undef HAVE_FTRUNCATE
%[insert:pp_if($has_function(ftruncate))]
%#define HAVE_FTRUNCATE 1
%[insert:pp_endif]
%#undef HAVE_FTW
%[insert:pp_if($has_function(ftw))]
%#define HAVE_FTW 1
%[insert:pp_endif]
%#undef HAVE_GETCWD
%[insert:pp_if($has_function(getcwd))]
%#define HAVE_GETCWD 1
%[insert:pp_endif]
%#undef HAVE_GETDTABLESIZE
%[insert:pp_if($has_function(getdtablesize))]
%#define HAVE_GETDTABLESIZE 1
%[insert:pp_endif]
%#undef HAVE_GETGROUPS
%[insert:pp_if($has_function(getgroups))]
%#define HAVE_GETGROUPS 1
%[insert:pp_endif]
%#undef HAVE_GETHOSTNAME
%[insert:pp_if($has_function(gethostname))]
%#define HAVE_GETHOSTNAME 1
%[insert:pp_endif]
%#undef HAVE_GETMNTENT
%[insert:pp_if($has_function(getmntent))]
%#define HAVE_GETMNTENT 1
%[insert:pp_endif]
%#undef HAVE_GETPAGESIZE
%[insert:pp_if($has_function(getpagesize))]
%#define HAVE_GETPAGESIZE 1
%[insert:pp_endif]
%#undef HAVE_GETTIMEOFDAY
%[insert:pp_if($has_function(gettimeofday))]
%#define HAVE_GETTIMEOFDAY 1
%[insert:pp_endif]
%#undef HAVE_GLOB
%[insert:pp_if($has_function(glob))]
%#define HAVE_GLOB 1
%[insert:pp_endif]
%#undef HAVE_ISASCII
%[insert:pp_if($has_function(isascii))]
%#define HAVE_ISASCII 1
%[insert:pp_endif]
%#undef HAVE_MEMCHR
%[insert:pp_if($has_function(memchr))]
%#define HAVE_MEMCHR 1
%[insert:pp_endif]
%#undef HAVE_MEMCPY
%[insert:pp_if($has_function(memcpy))]
%#define HAVE_MEMCPY 1
%[insert:pp_endif]
%#undef HAVE_MKDIR
%[insert:pp_if($has_function(mkdir))]
%#define HAVE_MKDIR 1
%[insert:pp_endif]
%#undef HAVE_MKFIFO
%[insert:pp_if($has_function(mkfifo))]
%#define HAVE_MKFIFO 1
%[insert:pp_endif]
%#undef HAVE_MKTIME
%[insert:pp_if($has_function(mktime))]
%#define HAVE_MKTIME 1
%[insert:pp_endif]
%#undef HAVE_POW
%[insert:pp_if($has_function(pow))]
%#define HAVE_POW 1
%[insert:pp_endif]
%#undef HAVE_PUTENV
%[insert:pp_if($has_function(putenv))]
%#define HAVE_PUTENV 1
%[insert:pp_endif]
%#undef HAVE_RANDOM
%[insert:pp_if($has_function(random))]
%#define HAVE_RANDOM 1
%[insert:pp_endif]
%#undef HAVE_RENAME
%[insert:pp_if($has_function(rename))]
%#define HAVE_RENAME 1
%[insert:pp_endif]
%#undef HAVE_RMDIR
%[insert:pp_if($has_function(rmdir))]
%#define HAVE_RMDIR 1
%[insert:pp_endif]
%#undef HAVE_SETENV
%[insert:pp_if($has_function(setenv))]
%#define HAVE_SETENV 1
%[insert:pp_endif]
%#undef HAVE_SETLINEBUF
%[insert:pp_if($has_function(setlinebuf))]
%#define HAVE_SETLINEBUF 1
%[insert:pp_endif]
%#undef HAVE_SETLOCALE
%[insert:pp_if($has_function(setlocale))]
%#define HAVE_SETLOCALE 1
%[insert:pp_endif]
%#undef HAVE_SIGACTION
%[insert:pp_if($has_function(sigaction))]
%#define HAVE_SIGACTION 1
%[insert:pp_endif]
%#undef HAVE_STPCPY
%[insert:pp_if($has_function(stpcpy))]
%#define HAVE_STPCPY 1
%[insert:pp_endif]
%#undef HAVE_STRCASECMP
%[insert:pp_if($has_function(strcasecmp))]
%#define HAVE_STRCASECMP 1
%[insert:pp_endif]
%#undef HAVE_STRCHR
%[insert:pp_if($has_function(strchr))]
%#define HAVE_STRCHR 1
%[insert:pp_endif]
%#undef HAVE_STRRCHR
%[insert:pp_if($has_function(strrchr))]
%#define HAVE_STRRCHR 1
%[insert:pp_endif]
%#undef HAVE_STRCOLL
%[insert:pp_if($has_function(strcoll))]
%#define HAVE_STRCOLL 1
%[insert:pp_endif]
%#undef HAVE_STRDUP
%[insert:pp_if($has_function(strdup))]
%#define HAVE_STRDUP 1
%[insert:pp_endif]
%#undef HAVE_STRFTIME
%[insert:pp_if($has_function(strftime))]
%#define HAVE_STRFTIME 1
%[insert:pp_endif]
%#undef HAVE_STRERROR
%[insert:pp_if($has_function(strerror))]
%#define HAVE_STRERROR 1
%[insert:pp_endif]
%#undef HAVE_VPRINTF
%[insert:pp_if($has_function(vprintf))]
%#define HAVE_VPRINTF 1
%[insert:pp_endif]
%#undef HAVE_WAITPID
%[insert:pp_if($has_function(waitpid))]
%#define HAVE_WAITPID 1
%[insert:pp_endif]
%#undef GETPGRP_VOID
%[insert:pp_if($has_function(getpgrp))]
%#define GETPGRP_VOID 1
%[insert:pp_endif]
%#undef MOUNTED_GETMNTENT1
%[insert:pp_if($has_function(getmntent))]
%#define MOUNTED_GETMNTENT1 1
%[insert:pp_endif]
%#undef STAT_STATFS2_BSIZE
%[insert:pp_if($has_function(statfs))]
%#define STAT_STATFS2_BSIZE 1
%[insert:pp_endif]
%#undef HAVE_UTIME_NULL
%[insert:pp_if($has_function(utime))]
%#define HAVE_UTIME_NULL 1
%[insert:pp_endif]
/*[[[end]]]*/

%{



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
#define HAVE_ST_RDEV 1 /* `struct stat::st_rdev' */
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
}%[insert:pp_if($has_function(getgroups))]%{
#define GETGROUPS_T __gid_t /* Vector element type of `getgroups()' */
}%[insert:pp_endif]%{

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
#define SIZEOF_CHAR    __SIZEOF_CHAR__    /* `sizeof(char)' */
#define SIZEOF_CHAR_P  __SIZEOF_POINTER__ /* `sizeof(char *)' */
#define SIZEOF_SHORT   __SIZEOF_SHORT__   /* `sizeof(short)' */
#define SIZEOF_SHORT_P __SIZEOF_POINTER__ /* `sizeof(short *)' */
#define SIZEOF_INT     __SIZEOF_INT__     /* `sizeof(int)' */
#define SIZEOF_INT_P   __SIZEOF_POINTER__ /* `sizeof(int *)' */
#define SIZEOF_LONG    __SIZEOF_LONG__    /* `sizeof(long)' */
#define SIZEOF_LONG_P  __SIZEOF_POINTER__ /* `sizeof(long *)' */
#ifdef __SIZEOF_LONG_LONG__
#define SIZEOF_LONG_LONG   __SIZEOF_LONG_LONG__ /* `sizeof(long long)' */
#define SIZEOF_LONG_LONG_P __SIZEOF_POINTER__   /* `sizeof(long long *)' */
#endif /* __SIZEOF_LONG_LONG__ */
#ifndef __NO_FPU
#define SIZEOF_FLOAT    __SIZEOF_FLOAT__   /* `sizeof(float)' */
#define SIZEOF_FLOAT_P  __SIZEOF_POINTER__ /* `sizeof(float *)' */
#define SIZEOF_DOUBLE   __SIZEOF_DOUBLE__  /* `sizeof(double)' */
#define SIZEOF_DOUBLE_P __SIZEOF_POINTER__ /* `sizeof(double *)' */
#ifdef __SIZEOF_LONG_DOUBLE__
#define SIZEOF_LONG_DOUBLE   __SIZEOF_LONG_DOUBLE__ /* `sizeof(long double)' */
#define SIZEOF_LONG_DOUBLE_P __SIZEOF_POINTER__     /* `sizeof(long double *)' */
#endif /* __SIZEOF_LONG_DOUBLE__ */
#endif /* !__NO_FPU */
#define SIZEOF_VOID_P __SIZEOF_POINTER__ /* `sizeof(void *)' */


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

}
