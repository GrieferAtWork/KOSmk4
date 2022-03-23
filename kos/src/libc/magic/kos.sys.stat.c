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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(atflag_t = __atflag_t)]
%[define_replacement(mode_t = __mode_t)]
%[define_replacement(dev_t = __dev_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(time_t = "__TM_TYPE(time)")]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]
%[default:nodos]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <sys/stat.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%[insert:prefix(
#include <bits/os/stat.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

%[default:section(".text.crt{|.dos}.except.fs.stat")]

[[throws, doc_alias("stat"), nocrt]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>") defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KStat")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>")!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KStat64")]]
void Stat([[nonnull]] char const *__restrict filename, [[nonnull]] struct stat *__restrict buf);

%
[[throws, doc_alias("fstat"), nocrt]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>") defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KFStat")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>")!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KFStat64")]]
void FStat($fd_t fd, [[nonnull]] struct stat *__restrict buf);

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[[throws, doc_alias("lstat"), nocrt]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>") defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KLStat")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>")!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KLStat64")]]
void LStat([[nonnull]] char const *__restrict filename,
           [[nonnull]] struct stat *__restrict buf);
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%
%#ifdef __USE_LARGEFILE64
[[throws, nocrt, doc_alias("stat64"), preferred_stat64_variant_of(KFStatAt), alias("KStat64")]]
void Stat64([[nonnull]] char const *__restrict filename,
            [[nonnull]] struct stat64 *__restrict buf);

[[throws, nocrt, doc_alias("fstat64"), preferred_stat64_variant_of(KFStatAt), alias("KFStat64")]]
void FStat64($fd_t fd, [[nonnull]] struct stat64 *__restrict buf);

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[[throws, nocrt, doc_alias("lstat64"), preferred_stat64_variant_of(KFStatAt), alias("KLStat64")]]
void LStat64([[nonnull]] char const *__restrict filename,
             [[nonnull]] struct stat64 *__restrict buf);
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */
%#endif /* __USE_LARGEFILE64 */

%
%


%
%#ifdef __USE_ATFILE

[[throws, doc_alias("fstatat"), nocrt]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>") defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KFStatAt")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>")!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KFStatAt64")]]
void FStatAt($fd_t dirfd, [[nonnull]] char const *__restrict filename,
             [[nonnull]] struct stat *__restrict buf, $atflag_t flags);

%#ifdef __USE_LARGEFILE64
[[throws, nocrt, doc_alias("fstatat64"), preferred_stat64_variant_of(KFStatAt), alias("KFStatAt64")]]
void FStatAt64($fd_t dirfd, [[nonnull]] char const *__restrict filename,
               [[nonnull]] struct stat64 *__restrict buf, $atflag_t flags);
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_ATFILE */

%[default:section(".text.crt{|.dos}.except.fs.modify")]

[[cp, throws, doc_alias("mkdir")]]
void Mkdir([[nonnull]] char const *pathname, $mode_t mode);

[[cp, throws, doc_alias("chmod")]]
void Chmod([[nonnull]] char const *filename, $mode_t mode);


%
%#ifdef __USE_MISC

[[cp, throws, doc_alias("lchmod")]]
void LChmod([[nonnull]] char const *filename, $mode_t mode);

%#endif /* __USE_MISC */

%[default:section(".text.crt{|.dos}.except.fs.modify")]

%
%#if defined(__USE_KOS) && defined(__USE_ATFILE)

[[cp, throws, doc_alias("fmkdirat")]]
void FMkdirAt($fd_t dirfd, [[nonnull]] char const *pathname,
              $mode_t mode, $atflag_t flags);

[[cp, throws, doc_alias("fmknodat")]]
void FMknodAt($fd_t dirfd, [[nonnull]] char const *nodename,
              $mode_t mode, $dev_t dev, $atflag_t flags);

%#endif /* __USE_KOS && __USE_ATFILE */


[[cp, throws, doc_alias("mkfifo")]]
void Mkfifo([[nonnull]] char const *fifoname, $mode_t mode);


%
%#ifdef __USE_ATFILE

[[cp, throws, doc_alias("fchmodat")]]
void FChmodAt($fd_t dirfd, [[nonnull]] char const *filename,
              $mode_t mode, $atflag_t flags);

[[cp, throws, doc_alias("mkdirat")]]
void MkdirAt($fd_t dirfd, [[nonnull]] char const *pathname, $mode_t mode);

[[cp, throws, doc_alias("mkfifoat")]]
void MkfifoAt($fd_t dirfd, [[nonnull]] char const *fifoname, $mode_t mode);

%#endif /* __USE_ATFILE */


%
%#ifdef __USE_POSIX

[[cp, throws, doc_alias("fchmod")]]
void FChmod($fd_t fd, $mode_t mode);

%#endif /* __USE_POSIX */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)

[[cp, throws, doc_alias("mknod")]]
void Mknod([[nonnull]] char const *nodename,
           $mode_t mode, $dev_t dev);

%#ifdef __USE_ATFILE

[[cp, throws, doc_alias("mknodat")]]
void MknodAt($fd_t dirfd, [[nonnull]] char const *nodename,
             $mode_t mode, $dev_t dev);

%#endif /* __USE_ATFILE */
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%[default:section(".text.crt{|.dos}.except.fs.modify_time")];

[[cp, throws, doc_alias("utimensat32"), ignore, nocrt, alias("UTimensAt")]]
void UTimensAt32($fd_t dirfd, [[nonnull]] char const *filename,
                 [[nullable]] struct timespec const times[2 /*or:3*/], $atflag_t flags);

%
%#ifdef __USE_ATFILE

[[cp, throws, doc_alias("utimensat"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("UTimensAt")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("UTimensAt64")]]
[[userimpl, requires($has_function(UTimensAt32) || $has_function(UTimensAt64))]]
[[impl_include("<asm/os/fcntl.h>")]]
void UTimensAt($fd_t dirfd, [[nonnull]] char const *filename,
               [[nullable]] struct timespec const times[2 /*or:3*/], $atflag_t flags) {
@@pp_if $has_function(UTimensAt64)@@
@@pp_ifdef       __AT_CHANGE_BTIME@@
	struct timespec64 tms[3];
	if (!times) {
		UTimensAt64(dirfd, filename, NULL, flags);
	} else {
		tms[0].tv_sec  = (time64_t)times[0].tv_sec;
		tms[0].tv_nsec = times[0].tv_nsec;
		tms[1].tv_sec  = (time64_t)times[1].tv_sec;
		tms[1].tv_nsec = times[1].tv_nsec;
		if (flags & __AT_CHANGE_BTIME) {
			tms[2].tv_sec  = (time64_t)times[2].tv_sec;
			tms[2].tv_nsec = times[2].tv_nsec;
		}
		UTimensAt64(dirfd, filename, tms, flags);
	}
@@pp_else@@
	struct timespec64 tms[2];
	if (!times) {
		UTimensAt64(dirfd, filename, NULL, flags);
	} else {
		tms[0].tv_sec  = (time64_t)times[0].tv_sec;
		tms[0].tv_nsec = times[0].tv_nsec;
		tms[1].tv_sec  = (time64_t)times[1].tv_sec;
		tms[1].tv_nsec = times[1].tv_nsec;
		UTimensAt64(dirfd, filename, tms, flags);
	}
@@pp_endif@@
@@pp_else@@
@@pp_ifdef __AT_CHANGE_BTIME@@
	struct timespec32 tms[3];
	if (!times) {
		UTimensAt32(dirfd, filename, NULL, flags);
	} else {
		tms[0].tv_sec  = (time32_t)times[0].tv_sec;
		tms[0].tv_nsec = times[0].tv_nsec;
		tms[1].tv_sec  = (time32_t)times[1].tv_sec;
		tms[1].tv_nsec = times[1].tv_nsec;
		if (flags & __AT_CHANGE_BTIME) {
			tms[2].tv_sec  = (time32_t)times[2].tv_sec;
			tms[2].tv_nsec = times[2].tv_nsec;
		}
		UTimensAt32(dirfd, filename, tms, flags);
	}
@@pp_else@@
	struct timespec32 tms[2];
	if (!times) {
		UTimensAt32(dirfd, filename, NULL, flags);
	} else {
		tms[0].tv_sec  = (time32_t)times[0].tv_sec;
		tms[0].tv_nsec = times[0].tv_nsec;
		tms[1].tv_sec  = (time32_t)times[1].tv_sec;
		tms[1].tv_nsec = times[1].tv_nsec;
		UTimensAt32(dirfd, filename, tms, flags);
	}
@@pp_endif@@
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[cp, throws]]
[[preferred_time64_variant_of(UTimensAt), doc_alias("utimensat")]]
[[userimpl, requires_function(UTimensAt32)]]
[[impl_include("<asm/os/fcntl.h>")]]
void UTimensAt64($fd_t dirfd, [[nonnull]] char const *filename,
                 [[nullable]] struct timespec64 const times[2 /*or:3*/], $atflag_t flags) {
@@pp_ifdef __AT_CHANGE_BTIME@@
	struct timespec32 tms[3];
	if (!times) {
		UTimensAt32(dirfd, filename, NULL, flags);
	} else {
		tms[0].tv_sec  = (time32_t)times[0].tv_sec;
		tms[0].tv_nsec = times[0].tv_nsec;
		tms[1].tv_sec  = (time32_t)times[1].tv_sec;
		tms[1].tv_nsec = times[1].tv_nsec;
		if (flags & __AT_CHANGE_BTIME) {
			tms[2].tv_sec  = (time32_t)times[2].tv_sec;
			tms[2].tv_nsec = times[2].tv_nsec;
		}
		UTimensAt32(dirfd, filename, tms, flags);
	}
@@pp_else@@
	struct timespec32 tms[2];
	if (!times) {
		UTimensAt32(dirfd, filename, NULL, flags);
	} else {
		tms[0].tv_sec  = (time32_t)times[0].tv_sec;
		tms[0].tv_nsec = times[0].tv_nsec;
		tms[1].tv_sec  = (time32_t)times[1].tv_sec;
		tms[1].tv_nsec = times[1].tv_nsec;
		UTimensAt32(dirfd, filename, tms, flags);
	}
@@pp_endif@@
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_ATFILE */

[[cp, throws, doc_alias("futimens32"), ignore, nocrt, alias("FUtimens")]]
void FUtimens32($fd_t fd, [[nullable]] struct timespec const times[2 /*or:3*/]);

%
%#ifdef __USE_XOPEN2K8
[[cp, throws, doc_alias("futimens"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("FUtimens")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("FUtimens64")]]
[[userimpl, requires($has_function(FUtimens32) || $has_function(FUtimens64))]]
FUtimens:($fd_t fd, [[nullable]] struct timespec const times[2 /*or:3*/]) {
@@pp_if $has_function(UTimensAt64)@@
	struct timespec64 tms[2];
	if (!times) {
		FUtimens64(fd, NULL);
	} else {
		tms[0].tv_sec  = (time64_t)times[0].tv_sec;
		tms[0].tv_nsec = times[0].tv_nsec;
		tms[1].tv_sec  = (time64_t)times[1].tv_sec;
		tms[1].tv_nsec = times[1].tv_nsec;
		FUtimens64(fd, tms);
	}
@@pp_else@@
	struct timespec32 tms[2];
	if (!times) {
		FUtimens32(fd, NULL);
	} else {
		tms[0].tv_sec  = (time32_t)times[0].tv_sec;
		tms[0].tv_nsec = times[0].tv_nsec;
		tms[1].tv_sec  = (time32_t)times[1].tv_sec;
		tms[1].tv_nsec = times[1].tv_nsec;
		FUtimens32(fd, tms);
	}
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[cp, throws]]
[[preferred_time64_variant_of(FUtimens), doc_alias("futimens")]]
[[userimpl, requires_function(FUtimens32)]]
void FUtimens64($fd_t fd, [[nullable]] struct timespec64 const times[2 /*or:3*/]) {
	struct timespec32 tms[2];
	if (!times) {
		FUtimens32(fd, NULL);
	} else {
		tms[0].tv_sec  = (time32_t)times[0].tv_sec;
		tms[0].tv_nsec = times[0].tv_nsec;
		tms[1].tv_sec  = (time32_t)times[1].tv_sec;
		tms[1].tv_nsec = times[1].tv_nsec;
		FUtimens32(fd, tms);
	}
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_XOPEN2K8 */


%{

__SYSDECL_END
#endif /* __CC__ */

}
