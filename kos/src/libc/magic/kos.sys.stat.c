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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(atflag_t = __atflag_t)]
%[define_replacement(mode_t = __mode_t)]
%[define_replacement(dev_t = __dev_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(time_t = __TM_TYPE(time))]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]

%{
#include <features.h>
#include <sys/stat.h>

__SYSDECL_BEGIN

#ifdef __CC__

}

%[default_impl_section(.text.crt.except.fs.stat)]

[[throws, nocrt, doc_alias(stat), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias(KStat)]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(KStat64)]]
Stat:([[nonnull]] char const *__restrict filename, [[nonnull]] struct stat *__restrict buf);

%
[[throws, nocrt, doc_alias(fstat), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias(KFStat)]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(KFStat64)]]
FStat:($fd_t fd, [[nonnull]] struct stat *__restrict buf);

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[[throws, nocrt, doc_alias(lstat), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias(KLStat)]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(KLStat64)]]
LStat:([[nonnull]] char const *__restrict filename, [[nonnull]] struct stat *__restrict buf);
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%
%#ifdef __USE_LARGEFILE64
[[throws, nocrt, doc_alias(stat64), preferred_alias(KStat64)]]
Stat64:([[nonnull]] char const *__restrict filename, [[nonnull]] struct stat64 *__restrict buf);

[[throws, nocrt, doc_alias(fstat64), preferred_alias(KFStat64)]]
FStat64:($fd_t fd, [[nonnull]] struct stat64 *__restrict buf);

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[[throws, nocrt, doc_alias(lstat64), preferred_alias(KLStat64)]]
LStat64:([[nonnull]] char const *__restrict filename, [[nonnull]] struct stat64 *__restrict buf);
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */
%#endif /* __USE_LARGEFILE64 */

%
%


%
%#ifdef __USE_ATFILE

[[throws, nocrt, doc_alias(fstatat), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias(KFStatAt)]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(KFStatAt64)]]
FStatAt:($fd_t dirfd, [[nonnull]] char const *__restrict filename,
         [[nonnull]] struct stat *__restrict buf, $atflag_t flags);

%#ifdef __USE_LARGEFILE64
[[throws, nocrt, doc_alias(fstatat64), preferred_alias(KFStatAt64)]]
FStatAt64:($fd_t dirfd, [[nonnull]] char const *__restrict filename,
           [[nonnull]] struct stat64 *__restrict buf, $atflag_t flags);
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_ATFILE */

%[default_impl_section(.text.crt.except.fs.modify)]

%
[throws][cp][noexport][doc_alias(mkdir)]
Mkdir:([[nonnull]] char const *pathname, $mode_t mode);

%
[throws][cp][doc_alias(chmod)]
Chmod:([[nonnull]] char const *filename, $mode_t mode);


%
%#ifdef __USE_MISC
[throws][cp][doc_alias(lchmod)]
LChmod:([[nonnull]] char const *filename, $mode_t mode);
%#endif /* __USE_MISC */

%[default_impl_section(.text.crt.except.fs.modify)]

%
%#if defined(__USE_KOS) && defined(__USE_ATFILE)
[throws][doc_alias(fmkdirat)][cp]
FMkdirAt:($fd_t dirfd, [[nonnull]] char const *pathname, $mode_t mode, $atflag_t flags);

[throws][doc_alias(fmknodat)][cp]
FMknodAt:($fd_t dirfd, [[nonnull]] char const *nodename, $mode_t mode, $dev_t dev, $atflag_t flags);
%#endif /* __USE_KOS && __USE_ATFILE */


%
[throws][cp][doc_alias(mkfifo)]
Mkfifo:([[nonnull]] char const *fifoname, $mode_t mode);

%
%#ifdef __USE_ATFILE
[throws][doc_alias(fchmodat)][cp] FChmodAt:($fd_t dirfd, [[nonnull]] char const *filename, $mode_t mode, $atflag_t flags);
[throws][doc_alias(mkdirat)][cp]  MkdirAt:($fd_t dirfd, [[nonnull]] char const *pathname, $mode_t mode);
[throws][doc_alias(mkfifoat)][cp] MkfifoAt:($fd_t dirfd, [[nonnull]] char const *fifoname, $mode_t mode);
%#endif /* __USE_ATFILE */

%
%#ifdef __USE_POSIX
[throws][doc_alias(fchmod)][cp] FChmod:($fd_t fd, $mode_t mode);
%#endif /* __USE_POSIX */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
[throws][doc_alias(mknod)][cp] Mknod:([[nonnull]] char const *nodename, $mode_t mode, $dev_t dev);
%#ifdef __USE_ATFILE
[throws][doc_alias(mknodat)][cp] MknodAt:($fd_t dirfd, [[nonnull]] char const *nodename, $mode_t mode, $dev_t dev);
%#endif /* __USE_ATFILE */
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%[default_impl_section(.text.crt.except.fs.modify_time)]

[throws][doc_alias(utimensat32)][cp][ignore]
UTimensAt32:($fd_t dirfd, [[nonnull]] char const *filename,
             [[nullable]] struct timespec const times[2 /*or:3*/], $atflag_t flags) = UTimensAt?;

%
%#ifdef __USE_ATFILE
[[cp, throws, doc_alias(utimensat), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(UTimensAt64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(UTimensAt)]]
[[userimpl, requires(defined(__CRT_HAVE_UTimensAt) || defined(__CRT_HAVE_UTimensAt64))]]
UTimensAt:($fd_t dirfd, [[nonnull]] char const *filename,
           [[nullable]] struct timespec const times[2 /*or:3*/], $atflag_t flags) {
#ifdef __CRT_HAVE_UTimensAt64
#if defined(__KOS__) && __KOS_VERSION__ >= 300
	struct timespec64 tms[3];
	if (!times) {
		UTimensAt64(dirfd, filename, NULL, flags);
	} else {
		tms[0].@tv_sec@  = (__time64_t)times[0].@tv_sec@;
		tms[0].@tv_nsec@ = times[0].@tv_nsec@;
		tms[1].@tv_sec@  = (__time64_t)times[1].@tv_sec@;
		tms[1].@tv_nsec@ = times[1].@tv_nsec@;
		if (flags & 0x0200) /* AT_CHANGE_CTIME */ {
			tms[2].@tv_sec@  = (__time64_t)times[2].@tv_sec@;
			tms[2].@tv_nsec@ = times[2].@tv_nsec@;
		}
		UTimensAt64(dirfd, filename, tms, flags);
	}
#else /* __KOS__ && __KOS_VERSION__ >= 300 */
	struct timespec64 tms[2];
	if (!times) {
		UTimensAt64(dirfd, filename, NULL, flags);
	} else {
		tms[0].@tv_sec@  = (__time64_t)times[0].@tv_sec@;
		tms[0].@tv_nsec@ = times[0].@tv_nsec@;
		tms[1].@tv_sec@  = (__time64_t)times[1].@tv_sec@;
		tms[1].@tv_nsec@ = times[1].@tv_nsec@;
		UTimensAt64(dirfd, filename, tms, flags);
	}
#endif /* !__KOS__ || __KOS_VERSION__ < 300 */
#else /* __CRT_HAVE_UTimensAt64 */
#if defined(__KOS__) && __KOS_VERSION__ >= 300
	struct @__timespec32@ tms[3];
	if (!times) {
		UTimensAt32(dirfd, filename, NULL, flags);
	} else {
		tms[0].@tv_sec@  = (__time32_t)times[0].@tv_sec@;
		tms[0].@tv_nsec@ = times[0].@tv_nsec@;
		tms[1].@tv_sec@  = (__time32_t)times[1].@tv_sec@;
		tms[1].@tv_nsec@ = times[1].@tv_nsec@;
		if (flags & 0x0200) /* AT_CHANGE_CTIME */ {
			tms[2].@tv_sec@  = (__time32_t)times[2].@tv_sec@;
			tms[2].@tv_nsec@ = times[2].@tv_nsec@;
		}
		UTimensAt32(dirfd, filename, tms, flags);
	}
#else /* __KOS__ && __KOS_VERSION__ >= 300 */
	struct @__timespec32@ tms[2];
	if (!times) {
		UTimensAt32(dirfd, filename, NULL, flags);
	} else {
		tms[0].@tv_sec@  = (__time32_t)times[0].@tv_sec@;
		tms[0].@tv_nsec@ = times[0].@tv_nsec@;
		tms[1].@tv_sec@  = (__time32_t)times[1].@tv_sec@;
		tms[1].@tv_nsec@ = times[1].@tv_nsec@;
		UTimensAt32(dirfd, filename, tms, flags);
	}
#endif /* !__KOS__ || __KOS_VERSION__ < 300 */
#endif /* !__CRT_HAVE_UTimensAt64 */
}

%#ifdef __USE_TIME64
[throws][time64_variant_of(UTimensAt)][doc_alias(utimensat)]
[cp][noexport][requires(defined(__CRT_HAVE_UTimensAt))]
UTimensAt64:($fd_t dirfd, [[nonnull]] char const *filename,
             [[nullable]] struct timespec64 const times[2 /*or:3*/], $atflag_t flags) {
#if defined(__KOS__) && __KOS_VERSION__ >= 300
	struct timespec32 tms[3];
	if (!times) {
		UTimensAt32(dirfd, filename, NULL, flags);
	} else {
		tms[0].@tv_sec@  = (__time32_t)times[0].@tv_sec@;
		tms[0].@tv_nsec@ = times[0].@tv_nsec@;
		tms[1].@tv_sec@  = (__time32_t)times[1].@tv_sec@;
		tms[1].@tv_nsec@ = times[1].@tv_nsec@;
		if (flags & 0x0200) /* AT_CHANGE_CTIME */ {
			tms[2].@tv_sec@  = (__time32_t)times[2].@tv_sec@;
			tms[2].@tv_nsec@ = times[2].@tv_nsec@;
		}
		UTimensAt32(dirfd, filename, tms, flags);
	}
#else /* __KOS__ && __KOS_VERSION__ >= 300 */
	struct timespec32 tms[2];
	if (!times) {
		UTimensAt32(dirfd, filename, NULL, flags);
	} else {
		tms[0].@tv_sec@  = (__time32_t)times[0].@tv_sec@;
		tms[0].@tv_nsec@ = times[0].@tv_nsec@;
		tms[1].@tv_sec@  = (__time32_t)times[1].@tv_sec@;
		tms[1].@tv_nsec@ = times[1].@tv_nsec@;
		UTimensAt32(dirfd, filename, tms, flags);
	}
#endif /* !__KOS__ || __KOS_VERSION__ < 300 */
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_ATFILE */

[[throws, cp, ignore, doc_alias(futimens32), nocrt, alias(FUtimens)]]
FUtimens32:($fd_t fd, [[nullable]] struct timespec const times[2 /*or:3*/]);

%
%#ifdef __USE_XOPEN2K8
[[throws, cp, noexport, doc_alias(futimens), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(FUtimens64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(FUtimens)]]
[[userimpl, requires(defined(__CRT_HAVE_FUtimens) || defined(__CRT_HAVE_FUtimens64))]]
FUtimens:($fd_t fd, [[nullable]] struct timespec const times[2 /*or:3*/]) {
#ifdef __CRT_HAVE_UTimensAt64
	struct timespec64 tms[2];
	if (!times) {
		FUtimens64(fd, NULL);
	} else {
		tms[0].@tv_sec@  = (__time64_t)times[0].@tv_sec@;
		tms[0].@tv_nsec@ = times[0].@tv_nsec@;
		tms[1].@tv_sec@  = (__time64_t)times[1].@tv_sec@;
		tms[1].@tv_nsec@ = times[1].@tv_nsec@;
		FUtimens64(fd, tms);
	}
#else /* __CRT_HAVE_UTimensAt64 */
	struct timespec32 tms[2];
	if (!times) {
		FUtimens32(fd, NULL);
	} else {
		tms[0].@tv_sec@  = (__time32_t)times[0].@tv_sec@;
		tms[0].@tv_nsec@ = times[0].@tv_nsec@;
		tms[1].@tv_sec@  = (__time32_t)times[1].@tv_sec@;
		tms[1].@tv_nsec@ = times[1].@tv_nsec@;
		FUtimens32(fd, tms);
	}
#endif /* !__CRT_HAVE_UTimensAt64 */
}

%#ifdef __USE_TIME64
[throws][time64_variant_of(FUtimens)][doc_alias(futimens)]
[cp][noexport][requires(defined(__CRT_HAVE_FUtimens))]
FUtimens64:($fd_t fd, [[nullable]] struct timespec64 const times[2 /*or:3*/]) {
	struct timespec32 tms[2];
	if (!times) {
		FUtimens32(fd, NULL);
	} else {
		tms[0].@tv_sec@  = (__time32_t)times[0].@tv_sec@;
		tms[0].@tv_nsec@ = times[0].@tv_nsec@;
		tms[1].@tv_sec@  = (__time32_t)times[1].@tv_sec@;
		tms[1].@tv_nsec@ = times[1].@tv_nsec@;
		FUtimens32(fd, tms);
	}
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_XOPEN2K8 */


%{

#endif /* __CC__ */

__SYSDECL_END

}