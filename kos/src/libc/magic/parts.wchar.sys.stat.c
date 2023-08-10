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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[default:section(".text.crt{|.dos}.wchar.fs.stat")]

%[insert:prefix(
#include <features.h>
)]%{
#ifndef _SYS_STAT_H
#include <sys/stat.h>
#endif /* !_SYS_STAT_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

}

%[default:section(".text.crt{|.dos}.fs.modify")];

[[wchar, cp, ignore, nocrt, alias("_wmkdir"), decl_include("<hybrid/typecore.h>")]]
int dos_wmkdir([[in]] wchar_t const *pathname);

[[ignore]] dos_c16mkdir(*) %{uchar16("dos_wmkdir")}
[[ignore]] dos_c32mkdir(*) %{uchar32("dos_wmkdir")}

[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/fcntl.h>"), impl_include("<asm/os/fcntl.h>")]]
[[requires((defined(__CRT_DOS_PRIMARY) && $has_function(dos_wmkdir)) ||
           (defined(__AT_FDCWD) && $has_function(wmkdirat)) ||
           $has_function(mkdir, convert_wcstombs))]]
int wmkdir([[in]] wchar_t const *pathname, $mode_t mode) {
@@pp_if defined(__CRT_DOS_PRIMARY) && $has_function(dos_wmkdir)@@
	(void)mode;
	return dos_wmkdir(pathname);
@@pp_elif $has_function(wmkdirat)@@
	return wmkdirat(__AT_FDCWD, pathname, mode);
@@pp_else@@
	int result;
	char *utf8_pathname;
	utf8_pathname = convert_wcstombs(pathname);
	if unlikely(!utf8_pathname)
		return -1;
	result = mkdir(utf8_pathname, mode);
@@pp_if $has_function(free)@@
	free(utf8_pathname);
@@pp_endif@@
	return result;
@@pp_endif@@
}


[[wchar, cp, decl_include("<bits/types.h>"), dos_export_alias("_wchmod")]]
[[requires_include("<asm/os/fcntl.h>"), impl_include("<asm/os/fcntl.h>")]]
[[requires((defined(__AT_FDCWD) && $has_function(wfchmodat)) ||
           $has_function(chmod, convert_wcstombs))]]
int wchmod([[in]] wchar_t const *filename, $mode_t mode) {
@@pp_if defined(__AT_FDCWD) && $has_function(wfchmodat)@@
	return wfchmodat(__AT_FDCWD, filename, mode, 0);
@@pp_else@@
	int result;
	char *utf8_filename;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = chmod(utf8_filename, mode);
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
	return result;
@@pp_endif@@
}


%
%#ifdef __USE_MISC
[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/fcntl.h>"), impl_include("<asm/os/fcntl.h>")]]
[[requires((defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && $has_function(wfchmodat)) ||
           $has_function(lchmod, convert_wcstombs))]]
int wlchmod([[in]] wchar_t const *filename, $mode_t mode) {
@@pp_if defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && $has_function(wfchmodat)@@
	return wfchmodat(__AT_FDCWD, filename, mode, __AT_SYMLINK_NOFOLLOW);
@@pp_else@@
	int result;
	char *utf8_filename;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = lchmod(utf8_filename, mode);
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
	return result;
@@pp_endif@@
}
%#endif /* __USE_MISC */



%
%#if defined(__USE_KOS) && defined(__USE_ATFILE)
[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires_function(fmkdirat, convert_wcstombs)]]
int wfmkdirat([[dirfd]] $fd_t dirfd,
              [[in]] wchar_t const *pathname,
              $mode_t mode, $atflag_t flags) {
	int result;
	char *utf8_pathname;
	utf8_pathname = convert_wcstombs(pathname);
	if unlikely(!utf8_pathname)
		return -1;
	result = fmkdirat(dirfd, utf8_pathname, mode, flags);
@@pp_if $has_function(free)@@
	free(utf8_pathname);
@@pp_endif@@
	return result;
}

[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires_function(fmknodat, convert_wcstombs)]]
int wfmknodat([[dirfd]] $fd_t dirfd, [[in]] wchar_t const *nodename,
              $mode_t mode, $dev_t dev, $atflag_t flags) {
	int result;
	char *utf8_nodename;
	utf8_nodename = convert_wcstombs(nodename);
	if unlikely(!utf8_nodename)
		return -1;
	result = fmknodat(dirfd, utf8_nodename, mode, dev, flags);
@@pp_if $has_function(free)@@
	free(utf8_nodename);
@@pp_endif@@
	return result;
}
%#endif /* __USE_KOS && __USE_ATFILE */


[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/stat.h>"), impl_include("<asm/os/stat.h>")]]
[[requires(($has_function(wmknod) && defined(__S_IFIFO)) ||
           $has_function(mkfifo, convert_wcstombs))]]
int wmkfifo([[in]] wchar_t const *fifoname, $mode_t mode) {
@@pp_if $has_function(wmknod) && defined(__S_IFIFO)@@
	return wmknod(fifoname, mode | __S_IFIFO, 0);
@@pp_else@@
	int result;
	char *utf8_fifoname;
	utf8_fifoname = convert_wcstombs(fifoname);
	if unlikely(!utf8_fifoname)
		return -1;
	result = mkfifo(utf8_fifoname, mode);
@@pp_if $has_function(free)@@
	free(utf8_fifoname);
@@pp_endif@@
	return result;
@@pp_endif@@
}

%
%#ifdef __USE_ATFILE
[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires_function(fchmodat, convert_wcstombs)]]
int wfchmodat([[dirfd]] $fd_t dirfd, [[in]] wchar_t const *filename,
              $mode_t mode, $atflag_t flags) {
	int result;
	char *utf8_filename;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = fchmodat(dirfd, utf8_filename, mode, flags);
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
	return result;
}

[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires($has_function(wfmkdirat) ||
           $has_function(mkdirat, convert_wcstombs))]]
int wmkdirat([[dirfd]] $fd_t dirfd, [[in]] wchar_t const *pathname, $mode_t mode) {
@@pp_if $has_function(wfmkdirat)@@
	return wfmkdirat(dirfd, pathname, mode, 0);
@@pp_else@@
	int result;
	char *utf8_pathname;
	utf8_pathname = convert_wcstombs(pathname);
	if unlikely(!utf8_pathname)
		return -1;
	result = mkdirat(dirfd, utf8_pathname, mode);
@@pp_if $has_function(free)@@
	free(utf8_pathname);
@@pp_endif@@
	return result;
@@pp_endif@@
}

[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/stat.h>"), impl_include("<asm/os/stat.h>")]]
[[requires(($has_function(wmknodat) && defined(__S_IFIFO)) ||
           $has_function(mkfifoat, convert_wcstombs))]]
int wmkfifoat([[dirfd]] $fd_t dirfd, [[in]] wchar_t const *fifoname, $mode_t mode) {
@@pp_if $has_function(wmknodat) && defined(__S_IFIFO)@@
	return wmknodat(dirfd, fifoname, mode | __S_IFIFO, 0);
@@pp_else@@
	int result;
	char *utf8_fifoname;
	utf8_fifoname = convert_wcstombs(fifoname);
	if unlikely(!utf8_fifoname)
		return -1;
	result = mkfifoat(dirfd, utf8_fifoname, mode);
@@pp_if $has_function(free)@@
	free(utf8_fifoname);
@@pp_endif@@
	return result;
@@pp_endif@@
}

%#endif /* __USE_ATFILE */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/fcntl.h>"), impl_include("<asm/os/fcntl.h>")]]
[[requires(($has_function(wmknodat) && defined(__AT_FDCWD)) ||
           $has_function(mknod, convert_wcstombs))]]
int wmknod([[in]] wchar_t const *nodename, $mode_t mode, $dev_t dev) {
@@pp_if $has_function(wmknodat) && defined(__AT_FDCWD)@@
	return wmknodat(__AT_FDCWD, nodename, mode, dev);
@@pp_else@@
	int result;
	char *utf8_nodename;
	utf8_nodename = convert_wcstombs(nodename);
	if unlikely(!utf8_nodename)
		return -1;
	result = mknod(utf8_nodename, mode, dev);
@@pp_if $has_function(free)@@
	free(utf8_nodename);
@@pp_endif@@
	return result;
@@pp_endif@@
}

%#ifdef __USE_ATFILE
[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires($has_function(wfmknodat) ||
           $has_function(mknodat, convert_wcstombs))]]
int wmknodat([[dirfd]] $fd_t dirfd, [[in]] wchar_t const *nodename,
             $mode_t mode, $dev_t dev) {
@@pp_if $has_function(wfmknodat)@@
	return wfmknodat(dirfd, nodename, mode, dev, 0);
@@pp_else@@
	int result;
	char *utf8_nodename;
	utf8_nodename = convert_wcstombs(nodename);
	if unlikely(!utf8_nodename)
		return -1;
	result = mknodat(dirfd, utf8_nodename, mode, dev);
@@pp_if $has_function(free)@@
	free(utf8_nodename);
@@pp_endif@@
	return result;
@@pp_endif@@
}
%#endif /* __USE_ATFILE */
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%[default:section(".text.crt{|.dos}.fs.modify_time")];

[[cp, ignore, doc_alias("wutimensat"), nocrt, alias("wutimensat")]]
[[wchar, decl_include("<bits/os/timespec.h>", "<bits/types.h>")]]
int crt_wutimensat32([[dirfd]] $fd_t dirfd, [[in]] wchar_t const *filename,
                     [[in_opt]] struct $timespec32 const times[2 /*or:3*/],
                     $atflag_t flags);
[[cp, ignore, doc_alias("wutimensat"), nocrt, alias("wutimensat64")]]
[[wchar, decl_include("<bits/os/timespec.h>", "<bits/types.h>")]]
int crt_wutimensat64([[dirfd]] $fd_t dirfd, [[in]] wchar_t const *filename,
                     [[in_opt]] struct $timespec64 const times[2 /*or:3*/],
                     $atflag_t flags);

[[ignore]] crt_c16utimensat32(*) %{uchar16("crt_wutimensat32")}
[[ignore]] crt_c32utimensat32(*) %{uchar32("crt_wutimensat32")}
[[ignore]] crt_c16utimensat64(*) %{uchar16("crt_wutimensat64")}
[[ignore]] crt_c32utimensat64(*) %{uchar32("crt_wutimensat64")}


%
%#ifdef __USE_ATFILE
[[wchar, cp, decl_include("<bits/os/timespec.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("wutimensat")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("wutimensat64")]]
[[requires($has_function(crt_wutimensat64) ||
           $has_function(crt_wutimensat32) ||
           $has_function(utimensat, convert_wcstombs))]]
[[impl_include("<asm/os/fcntl.h>")]]
int wutimensat([[dirfd]] $fd_t dirfd, [[in]] wchar_t const *filename,
               [[in_opt]] struct timespec const times[2 /*or:3*/],
               $atflag_t flags) {
@@pp_if $has_function(crt_wutimensat32) && !defined(__BUILDING_LIBC)@@
@@pp_ifdef __AT_CHANGE_BTIME@@
	struct timespec32 tms[3];
	if (!times)
		return crt_wutimensat32(dirfd, filename, NULL, flags);
	tms[0].@tv_sec@  = (time32_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (time32_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	if (flags & __AT_CHANGE_BTIME) {
		tms[2].@tv_sec@  = (time32_t)times[2].@tv_sec@;
		tms[2].@tv_nsec@ = times[2].@tv_nsec@;
	}
	return crt_wutimensat32(dirfd, filename, tms, flags);
@@pp_else@@
	struct timespec32 tms[2];
	if (!times)
		return crt_wutimensat32(dirfd, filename, NULL, flags);
	tms[0].@tv_sec@  = (time32_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (time32_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	return crt_wutimensat32(dirfd, filename, tms, flags);
@@pp_endif@@
@@pp_elif $has_function(crt_wutimensat64) && (!defined(__BUILDING_LIBC) || __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__)@@
@@pp_ifdef __AT_CHANGE_BTIME@@
	struct timespec64 tms[3];
	if (!times)
		return wutimensat64(dirfd, filename, NULL, flags);
	tms[0].@tv_sec@  = (time64_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (time64_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	if (flags & __AT_CHANGE_BTIME) {
		tms[2].@tv_sec@  = (time64_t)times[2].@tv_sec@;
		tms[2].@tv_nsec@ = times[2].@tv_nsec@;
	}
	return wutimensat64(dirfd, filename, tms, flags);
@@pp_else@@
	struct timespec64 tms[2];
	if (!times)
		return wutimensat64(dirfd, filename, NULL, flags);
	tms[0].@tv_sec@  = (time64_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (time64_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	return wutimensat64(dirfd, filename, tms, flags);
@@pp_endif@@
@@pp_else@@
	int result;
	char *utf8_filename;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = utimensat(dirfd, utf8_filename, times, flags);
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
	return result;
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[wchar, cp, decl_include("<bits/os/timespec.h>", "<bits/types.h>")]]
[[preferred_time64_variant_of(wutimensat), doc_alias("wutimensat")]]
[[requires($has_function(utimensat64, convert_wcstombs) ||
           $has_function(crt_wutimensat32))]]
[[impl_include("<asm/os/fcntl.h>")]]
int wutimensat64([[dirfd]] $fd_t dirfd, [[in]] wchar_t const *filename,
                 [[in_opt]] struct timespec64 const times[2 /*or:3*/],
                 $atflag_t flags) {
@@pp_if $has_function(utimensat64, convert_wcstombs)@@
	int result;
	char *utf8_filename;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = utimensat64(dirfd, utf8_filename, times, flags);
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
	return result;
@@pp_else@@
@@pp_ifdef __AT_CHANGE_BTIME@@
	struct timespec32 tms[3];
	if (!times)
		return crt_wutimensat32(dirfd, filename, NULL, flags);
	tms[0].@tv_sec@  = (time32_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (time32_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	if (flags & __AT_CHANGE_BTIME) {
		tms[2].@tv_sec@  = (time32_t)times[2].@tv_sec@;
		tms[2].@tv_nsec@ = times[2].@tv_nsec@;
	}
	return crt_wutimensat32(dirfd, filename, tms, flags);
@@pp_else@@
	struct timespec32 tms[2];
	if (!times)
		return crt_wutimensat32(dirfd, filename, NULL, flags);
	tms[0].@tv_sec@  = (time32_t)times[0].@tv_sec@;
	tms[0].@tv_nsec@ = times[0].@tv_nsec@;
	tms[1].@tv_sec@  = (time32_t)times[1].@tv_sec@;
	tms[1].@tv_nsec@ = times[1].@tv_nsec@;
	return crt_wutimensat32(dirfd, filename, tms, flags);
@@pp_endif@@
@@pp_endif@@
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_ATFILE */



%{

__SYSDECL_END
#endif /* __CC__ */

}
