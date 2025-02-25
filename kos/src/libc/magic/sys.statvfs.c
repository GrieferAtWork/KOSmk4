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
%(c_prefix){
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/statvfs.h) */
/* (#) Portability: DJGPP         (/include/sys/statvfs.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/statvfs.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/statvfs.h) */
/* (#) Portability: FreeBSD       (/sys/sys/statvfs.h) */
/* (#) Portability: GNU C Library (/io/sys/statvfs.h) */
/* (#) Portability: NetBSD        (/sys/sys/statvfs.h) */
/* (#) Portability: OpenBSD       (/sys/sys/statvfs.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/statvfs.h) */
/* (#) Portability: diet libc     (/include/sys/statvfs.h) */
/* (#) Portability: mintlib       (/include/sys/statvfs.h) */
/* (#) Portability: musl libc     (/include/sys/statvfs.h) */
/* (#) Portability: uClibc        (/include/sys/statvfs.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[default:section(".text.crt{|.dos}.fs.statfs.statvfs")]

%[define_decl_include_implication("<bits/os/statvfs.h>" => ["<bits/types.h>"])]
%[define_decl_include("<bits/os/statvfs.h>": ["struct statvfs", "struct statvfs64"])]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/statvfs.h>  /* __ST_* */
)]%[insert:prefix(
#include <bits/os/statvfs.h> /* struct statvfs, struct statvfs64 */
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#if !defined(ST_RDONLY) && defined(__ST_RDONLY)
#define ST_RDONLY      __ST_RDONLY /* Disallow all file writes */
#endif /* !ST_RDONLY && __ST_RDONLY */
#if !defined(ST_NOSUID) && defined(__ST_NOSUID)
#define ST_NOSUID      __ST_NOSUID /* Ignore `S_ISUID' and `S_ISGID' */
#endif /* !ST_NOSUID && __ST_NOSUID */
#ifdef __USE_GNU
#if !defined(ST_NODEV) && defined(__ST_NODEV)
#define ST_NODEV       __ST_NODEV       /* ??? */
#endif /* !ST_NODEV && __ST_NODEV */
#if !defined(ST_NOEXEC) && defined(__ST_NOEXEC)
#define ST_NOEXEC      __ST_NOEXEC      /* ??? */
#endif /* !ST_NOEXEC && __ST_NOEXEC */
#if !defined(ST_SYNCHRONOUS) && defined(__ST_SYNCHRONOUS)
#define ST_SYNCHRONOUS __ST_SYNCHRONOUS /* ??? */
#endif /* !ST_SYNCHRONOUS && __ST_SYNCHRONOUS */
#if !defined(ST_MANDLOCK) && defined(__ST_MANDLOCK)
#define ST_MANDLOCK    __ST_MANDLOCK    /* ??? */
#endif /* !ST_MANDLOCK && __ST_MANDLOCK */
#if !defined(ST_WRITE) && defined(__ST_WRITE)
#define ST_WRITE       __ST_WRITE       /* ??? */
#endif /* !ST_WRITE && __ST_WRITE */
#if !defined(ST_APPEND) && defined(__ST_APPEND)
#define ST_APPEND      __ST_APPEND      /* ??? */
#endif /* !ST_APPEND && __ST_APPEND */
#if !defined(ST_IMMUTABLE) && defined(__ST_IMMUTABLE)
#define ST_IMMUTABLE   __ST_IMMUTABLE   /* ??? */
#endif /* !ST_IMMUTABLE && __ST_IMMUTABLE */
#if !defined(ST_NOATIME) && defined(__ST_NOATIME)
#define ST_NOATIME     __ST_NOATIME     /* ??? */
#endif /* !ST_NOATIME && __ST_NOATIME */
#if !defined(ST_NODIRATIME) && defined(__ST_NODIRATIME)
#define ST_NODIRATIME  __ST_NODIRATIME  /* ??? */
#endif /* !ST_NODIRATIME && __ST_NODIRATIME */
#if !defined(ST_RELATIME) && defined(__ST_RELATIME)
#define ST_RELATIME    __ST_RELATIME    /* ??? */
#endif /* !ST_RELATIME && __ST_RELATIME */
#endif /* __USE_GNU */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __fsblkcnt_t_defined
#define __fsblkcnt_t_defined
typedef __fsblkcnt_t fsblkcnt_t; /* Type to count file system blocks.  */
#endif /* !__fsblkcnt_t_defined */
#ifndef __fsfilcnt_t_defined
#define __fsfilcnt_t_defined
typedef __fsfilcnt_t fsfilcnt_t; /* Type to count file system inodes.  */
#endif /* !__fsfilcnt_t_defined */

}


[[decl_include("<bits/os/statvfs.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("statvfs")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("statvfs64")]]
int statvfs([[in]] char const *file, [[out]] struct statvfs *buf);

[[decl_include("<bits/os/statvfs.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("fstatvfs")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("fstatvfs64")]]
int fstatvfs([[fdarg]] $fd_t filedes, [[out]] struct statvfs *buf);

%
%#ifdef __USE_LARGEFILE64
%#ifndef statvfs64
[[decl_include("<bits/os/statvfs.h>")]]
[[preferred_off64_variant_of(statvfs), doc_alias("statvfs")]]
int statvfs64([[in]] const char *file, [[out]] struct statvfs64 *buf);
%#endif /* !statvfs64 */

[[decl_include("<bits/os/statvfs.h>")]]
[[preferred_off64_variant_of(fstatvfs), doc_alias("fstatvfs")]]
int fstatvfs64([[fdarg]] $fd_t filedes, [[out]] struct statvfs64 *buf);
%#endif /* __USE_LARGEFILE64 */


%{

__SYSDECL_END
#endif /* __CC__ */

}
