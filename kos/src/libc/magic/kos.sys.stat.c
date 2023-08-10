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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(atflag_t = __atflag_t)]
%[define_replacement(mode_t = __mode_t)]
%[define_replacement(dev_t = __dev_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(time_t = "__time_t")]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]
%[define_replacement(stat64 = __stat64)]
%[default:nodos]

%[define_decl_include_implication("<bits/os/stat.h>" => ["<bits/types.h>"])]
%[define_decl_include("<bits/os/stat.h>": ["struct stat", "struct stat64", "struct __stat64"])]

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

[[throws, doc_alias("stat"), nocrt, decl_include("<bits/os/stat.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>") defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KStat")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>")!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KStat64")]]
void Stat([[in]] char const *__restrict filename, [[out]] struct stat *__restrict buf);

%
[[throws, doc_alias("fstat"), nocrt, decl_include("<bits/os/stat.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>") defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KFStat")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>")!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KFStat64")]]
void FStat([[fdarg]] $fd_t fd, [[out]] struct stat *__restrict buf);

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[[throws, doc_alias("lstat"), nocrt, decl_include("<bits/os/stat.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>") defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KLStat")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>")!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KLStat64")]]
void LStat([[in]] char const *__restrict filename,
           [[out]] struct stat *__restrict buf);
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%
%#ifdef __USE_LARGEFILE64
[[throws, nocrt, doc_alias("stat64")]]
[[decl_include("<bits/os/stat.h>")]]
[[preferred_stat64_variant_of(KFStatAt), alias("KStat64")]]
void Stat64([[in]] char const *__restrict filename,
            [[out]] struct stat64 *__restrict buf);

[[throws, nocrt, doc_alias("fstat64")]]
[[decl_include("<bits/os/stat.h>")]]
[[preferred_stat64_variant_of(KFStatAt), alias("KFStat64")]]
void FStat64([[fdarg]] $fd_t fd, [[out]] struct stat64 *__restrict buf);

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[[throws, nocrt, doc_alias("lstat64")]]
[[decl_include("<bits/os/stat.h>")]]
[[preferred_stat64_variant_of(KFStatAt), alias("KLStat64")]]
void LStat64([[in]] char const *__restrict filename,
             [[out]] struct stat64 *__restrict buf);
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */
%#endif /* __USE_LARGEFILE64 */

%
%


%
%#ifdef __USE_ATFILE

[[throws, doc_alias("fstatat"), nocrt, decl_include("<bits/os/stat.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>") defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KFStatAt")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/stat.h>")!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64)), alias("KFStatAt64")]]
void FStatAt([[dirfd]] $fd_t dirfd, [[in]] char const *__restrict filename,
             [[out]] struct stat *__restrict buf, $atflag_t flags);

%#ifdef __USE_LARGEFILE64
[[throws, nocrt, doc_alias("fstatat64"), decl_include("<bits/os/stat.h>")]]
[[preferred_stat64_variant_of(KFStatAt), alias("KFStatAt64")]]
void FStatAt64([[dirfd]] $fd_t dirfd, [[in]] char const *__restrict filename,
               [[out]] struct stat64 *__restrict buf, $atflag_t flags);
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_ATFILE */

%[default:section(".text.crt{|.dos}.except.fs.modify")]

[[cp, throws, doc_alias("mkdir"), decl_include("<bits/types.h>")]]
void MkDir([[in]] char const *pathname, $mode_t mode);

[[cp, throws, doc_alias("chmod"), decl_include("<bits/types.h>")]]
void ChMod([[in]] char const *filename, $mode_t mode);


%
%#ifdef __USE_MISC

[[cp, throws, doc_alias("lchmod"), decl_include("<bits/types.h>")]]
void LChMod([[in]] char const *filename, $mode_t mode);

%#endif /* __USE_MISC */

%[default:section(".text.crt{|.dos}.except.fs.modify")]

%
%#if defined(__USE_KOS) && defined(__USE_ATFILE)

[[cp, throws, doc_alias("fmkdirat"), decl_include("<bits/types.h>")]]
void FMkDirAt([[dirfd]] $fd_t dirfd, [[in]] char const *pathname,
              $mode_t mode, $atflag_t flags);

[[cp, throws, doc_alias("fmknodat"), decl_include("<bits/types.h>")]]
void FMkNodAt([[dirfd]] $fd_t dirfd, [[in]] char const *nodename,
              $mode_t mode, $dev_t dev, $atflag_t flags);

%#endif /* __USE_KOS && __USE_ATFILE */


[[cp, throws, doc_alias("mkfifo"), decl_include("<bits/types.h>")]]
void MkFiFo([[in]] char const *fifoname, $mode_t mode);


%
%#ifdef __USE_ATFILE

[[cp, throws, doc_alias("fchmodat"), decl_include("<bits/types.h>")]]
void FChModAt([[dirfd]] $fd_t dirfd, [[in]] char const *filename,
              $mode_t mode, $atflag_t flags);

[[cp, throws, doc_alias("mkdirat"), decl_include("<bits/types.h>")]]
void MkDirAt([[dirfd]] $fd_t dirfd, [[in]] char const *pathname, $mode_t mode);

[[cp, throws, doc_alias("mkfifoat"), decl_include("<bits/types.h>")]]
void MkFiFoAt([[dirfd]] $fd_t dirfd, [[in]] char const *fifoname, $mode_t mode);

%#endif /* __USE_ATFILE */


%
%#ifdef __USE_POSIX

[[cp, throws, doc_alias("fchmod"), decl_include("<bits/types.h>")]]
void FChMod([[fdarg]] $fd_t fd, $mode_t mode);

%#endif /* __USE_POSIX */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)

[[cp, throws, doc_alias("mknod"), decl_include("<bits/types.h>")]]
void MkNod([[in]] char const *nodename,
           $mode_t mode, $dev_t dev);

%#ifdef __USE_ATFILE

[[cp, throws, doc_alias("mknodat"), decl_include("<bits/types.h>")]]
void MkNodAt([[dirfd]] $fd_t dirfd, [[in]] char const *nodename,
             $mode_t mode, $dev_t dev);

%#endif /* __USE_ATFILE */
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%[default:section(".text.crt{|.dos}.except.fs.modify_time")];

[[cp, throws, doc_alias("utimensat32"), ignore, nocrt, alias("UTimensAt")]]
[[decl_include("<bits/os/timespec.h>")]]
void UTimensAt32([[dirfd]] $fd_t dirfd, [[in]] char const *filename,
                 [[in_opt]] struct timespec const times[2 /*or:3*/],
                 $atflag_t flags);

%
%#ifdef __USE_ATFILE

[[cp, throws, doc_alias("utimensat"), no_crt_self_import, decl_include("<bits/os/timespec.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("UTimensAt")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("UTimensAt64")]]
[[userimpl, requires($has_function(UTimensAt32) || $has_function(UTimensAt64))]]
[[impl_include("<asm/os/fcntl.h>")]]
void UTimensAt([[dirfd]] $fd_t dirfd, [[in]] char const *filename,
               [[in_opt]] struct timespec const times[2 /*or:3*/],
               $atflag_t flags) {
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
[[impl_include("<asm/os/fcntl.h>"), decl_include("<bits/os/timespec.h>")]]
void UTimensAt64([[dirfd]] $fd_t dirfd, [[in]] char const *filename,
                 [[in_opt]] struct timespec64 const times[2 /*or:3*/],
                 $atflag_t flags) {
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

[[cp, throws, doc_alias("futimens32"), ignore, nocrt, alias("FUTimens")]]
[[decl_include("<bits/os/timespec.h>")]]
void FUTimens32([[fdarg]] $fd_t fd, [[nullable]] struct timespec const times[2 /*or:3*/]);

%
%#ifdef __USE_XOPEN2K8
[[cp, throws, doc_alias("futimens"), no_crt_self_import, decl_include("<bits/os/timespec.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("FUTimens")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("FUTimens64")]]
[[userimpl, requires($has_function(FUTimens32) || $has_function(FUTimens64))]]
void FUTimens([[fdarg]] $fd_t fd, [[in_opt]] struct timespec const times[2 /*or:3*/]) {
@@pp_if $has_function(UTimensAt64)@@
	struct timespec64 tms[2];
	if (!times) {
		FUTimens64(fd, NULL);
	} else {
		tms[0].tv_sec  = (time64_t)times[0].tv_sec;
		tms[0].tv_nsec = times[0].tv_nsec;
		tms[1].tv_sec  = (time64_t)times[1].tv_sec;
		tms[1].tv_nsec = times[1].tv_nsec;
		FUTimens64(fd, tms);
	}
@@pp_else@@
	struct timespec32 tms[2];
	if (!times) {
		FUTimens32(fd, NULL);
	} else {
		tms[0].tv_sec  = (time32_t)times[0].tv_sec;
		tms[0].tv_nsec = times[0].tv_nsec;
		tms[1].tv_sec  = (time32_t)times[1].tv_sec;
		tms[1].tv_nsec = times[1].tv_nsec;
		FUTimens32(fd, tms);
	}
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[cp, throws, decl_include("<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(FUTimens), doc_alias("futimens")]]
[[userimpl, requires_function(FUTimens32)]]
void FUTimens64([[fdarg]] $fd_t fd, [[in_opt]] struct timespec64 const times[2 /*or:3*/]) {
	struct timespec32 tms[2];
	if (!times) {
		FUTimens32(fd, NULL);
	} else {
		tms[0].tv_sec  = (time32_t)times[0].tv_sec;
		tms[0].tv_nsec = times[0].tv_nsec;
		tms[1].tv_sec  = (time32_t)times[1].tv_sec;
		tms[1].tv_nsec = times[1].tv_nsec;
		FUTimens32(fd, tms);
	}
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_XOPEN2K8 */


%{

__SYSDECL_END
#endif /* __CC__ */

}
