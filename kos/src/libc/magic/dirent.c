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
%(c_prefix){
/* (>) Standard: POSIX.1b (Issue 2, IEEE Std 1003.1b-1993) */
/* (#) Portability: Cygwin        (/newlib/libc/include/dirent.h) */
/* (#) Portability: DJGPP         (/include/dirent.h) */
/* (#) Portability: FreeBSD       (/include/dirent.h) */
/* (#) Portability: GNU C Library (/dirent/dirent.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/dirent.h) */
/* (#) Portability: NetBSD        (/include/dirent.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/dirent.h) */
/* (#) Portability: OpenBSD       (/include/dirent.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/dirent.h) */
/* (#) Portability: diet libc     (/include/dirent.h) */
/* (#) Portability: libc4/5       (/include/dirent.h) */
/* (#) Portability: libc6         (/include/dirent.h) */
/* (#) Portability: musl libc     (/include/dirent.h) */
/* (#) Portability: uClibc        (/include/dirent.h) */
}

%[define_replacement(fd_t       = __fd_t)]
%[define_replacement(off_t      = "__FS_TYPE(off)")]
%[define_replacement(pos_t      = "__FS_TYPE(pos)")]
%[define_replacement(off32_t    = __off32_t)]
%[define_replacement(off64_t    = __off64_t)]
%[define_replacement(pos32_t    = __pos32_t)]
%[define_replacement(pos64_t    = __pos64_t)]
%[define_replacement(atflag_t   = __atflag_t)]
%[define_replacement(oflag_t    = __oflag_t)]
%[define_replacement(longptr_t  = __LONGPTR_TYPE__)]
%[define_replacement(DIR        = "struct __dirstream")]
%[default:section(".text.crt{|.dos}.fs.dir")]


%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/dirent.h>
)]%[insert:prefix(
#include <bits/os/dirent.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

__SYSDECL_BEGIN

#ifdef __USE_MISC
#ifndef DT_UNKNOWN
#if (defined(__DT_UNKNOWN) || defined(__DT_FIFO) || \
     defined(__DT_CHR) || defined(__DT_DIR) ||      \
     defined(__DT_BLK) || defined(__DT_REG) ||      \
     defined(__DT_LNK) || defined(__DT_SOCK) ||     \
     defined(__DT_WHT))
/*[[[enum]]]*/
#ifdef __CC__
enum {
#ifdef __DT_UNKNOWN
	DT_UNKNOWN = __DT_UNKNOWN, /* Unknown file type */
#endif /* __DT_UNKNOWN */
#ifdef __DT_FIFO
	DT_FIFO    = __DT_FIFO,    /* FistInFirstOut (pipe) file (s.a. `S_ISFIFO()', `S_IFMT & S_IFIFO') */
#endif /* __DT_FIFO */
#ifdef __DT_CHR
	DT_CHR     = __DT_CHR,     /* Character device file      (s.a. `S_ISCHR()', `S_IFMT & S_IFCHR') */
#endif /* __DT_CHR */
#ifdef __DT_DIR
	DT_DIR     = __DT_DIR,     /* Directory                  (s.a. `S_ISDIR()', `S_IFMT & S_IFDIR') */
#endif /* __DT_DIR */
#ifdef __DT_BLK
	DT_BLK     = __DT_BLK,     /* Block device file          (s.a. `S_ISBLK()', `S_IFMT & S_IFBLK') */
#endif /* __DT_BLK */
#ifdef __DT_REG
	DT_REG     = __DT_REG,     /* Regular text file          (s.a. `S_ISREG()', `S_IFMT & S_IFREG') */
#endif /* __DT_REG */
#ifdef __DT_LNK
	DT_LNK     = __DT_LNK,     /* Symbolic link              (s.a. `S_ISLNK()', `S_IFMT & S_IFLNK') */
#endif /* __DT_LNK */
#ifdef __DT_SOCK
	DT_SOCK    = __DT_SOCK,    /* Socket file                (s.a. `S_ISSOCK()', `S_IFMT & S_IFSOCK') */
#endif /* __DT_SOCK */
#ifdef __DT_WHT
	DT_WHT     = __DT_WHT,     /* Mounting point? */
#endif /* __DT_WHT */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#ifdef __DT_UNKNOWN
#define DT_UNKNOWN DT_UNKNOWN /* Unknown file type */
#endif /* __DT_UNKNOWN */
#ifdef __DT_FIFO
#define DT_FIFO    DT_FIFO    /* FistInFirstOut (pipe) file (s.a. `S_ISFIFO()', `S_IFMT & S_IFIFO') */
#endif /* __DT_FIFO */
#ifdef __DT_CHR
#define DT_CHR     DT_CHR     /* Character device file      (s.a. `S_ISCHR()', `S_IFMT & S_IFCHR') */
#endif /* __DT_CHR */
#ifdef __DT_DIR
#define DT_DIR     DT_DIR     /* Directory                  (s.a. `S_ISDIR()', `S_IFMT & S_IFDIR') */
#endif /* __DT_DIR */
#ifdef __DT_BLK
#define DT_BLK     DT_BLK     /* Block device file          (s.a. `S_ISBLK()', `S_IFMT & S_IFBLK') */
#endif /* __DT_BLK */
#ifdef __DT_REG
#define DT_REG     DT_REG     /* Regular text file          (s.a. `S_ISREG()', `S_IFMT & S_IFREG') */
#endif /* __DT_REG */
#ifdef __DT_LNK
#define DT_LNK     DT_LNK     /* Symbolic link              (s.a. `S_ISLNK()', `S_IFMT & S_IFLNK') */
#endif /* __DT_LNK */
#ifdef __DT_SOCK
#define DT_SOCK    DT_SOCK    /* Socket file                (s.a. `S_ISSOCK()', `S_IFMT & S_IFSOCK') */
#endif /* __DT_SOCK */
#ifdef __DT_WHT
#define DT_WHT     DT_WHT     /* Mounting point? */
#endif /* __DT_WHT */
#else /* __COMPILER_PREFERR_ENUMS */
#ifdef __DT_UNKNOWN
#define DT_UNKNOWN __DT_UNKNOWN /* Unknown file type */
#endif /* __DT_UNKNOWN */
#ifdef __DT_FIFO
#define DT_FIFO    __DT_FIFO    /* FistInFirstOut (pipe) file (s.a. `S_ISFIFO()', `S_IFMT & S_IFIFO') */
#endif /* __DT_FIFO */
#ifdef __DT_CHR
#define DT_CHR     __DT_CHR     /* Character device file      (s.a. `S_ISCHR()', `S_IFMT & S_IFCHR') */
#endif /* __DT_CHR */
#ifdef __DT_DIR
#define DT_DIR     __DT_DIR     /* Directory                  (s.a. `S_ISDIR()', `S_IFMT & S_IFDIR') */
#endif /* __DT_DIR */
#ifdef __DT_BLK
#define DT_BLK     __DT_BLK     /* Block device file          (s.a. `S_ISBLK()', `S_IFMT & S_IFBLK') */
#endif /* __DT_BLK */
#ifdef __DT_REG
#define DT_REG     __DT_REG     /* Regular text file          (s.a. `S_ISREG()', `S_IFMT & S_IFREG') */
#endif /* __DT_REG */
#ifdef __DT_LNK
#define DT_LNK     __DT_LNK     /* Symbolic link              (s.a. `S_ISLNK()', `S_IFMT & S_IFLNK') */
#endif /* __DT_LNK */
#ifdef __DT_SOCK
#define DT_SOCK    __DT_SOCK    /* Socket file                (s.a. `S_ISSOCK()', `S_IFMT & S_IFSOCK') */
#endif /* __DT_SOCK */
#ifdef __DT_WHT
#define DT_WHT     __DT_WHT     /* Mounting point? */
#endif /* __DT_WHT */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */
#endif /* !DT_UNKNOWN */

/* Convert between stat structure types and directory types. */
#ifndef IFTODT
#ifdef __IFTODT
#define IFTODT(mode) __IFTODT(mode)
#endif /* __IFTODT */
#ifdef __DTTOIF
#define DTTOIF(dirtype) __DTTOIF(dirtype)
#endif /* __DTTOIF */
#endif /* !IFTODT */

#if defined(__USE_XOPEN2K8) && !defined(MAXNAMLEN)
#include <asm/os/limits.h>
#if defined(__NAME_MAX) && (__NAME_MAX + 0) != -1
#define MAXNAMLEN __NAME_MAX /* Max # of chars in a file name */
#else /* __NAME_MAX != -1 */
#define MAXNAMLEN 255        /* Max # of chars in a file name */
#endif /* __NAME_MAX == -1 */
#endif /* __USE_XOPEN2K8 && !MAXNAMLEN */
#endif /* __USE_MISC */


#ifdef __CC__
#ifdef _DIRENT_HAVE_D_NAMLEN
#define _D_EXACT_NAMLEN(d) ((d)->d_namlen)
#define _D_ALLOC_NAMLEN(d) (_D_EXACT_NAMLEN(d) + 1)
#else /* _DIRENT_HAVE_D_NAMLEN */
__SYSDECL_END
#include <libc/string.h>
__SYSDECL_BEGIN
#define _D_EXACT_NAMLEN(d) __libc_strlen((d)->d_name)
#ifdef _DIRENT_HAVE_D_RECLEN
#define _D_ALLOC_NAMLEN(d) (((char *)(d) + (d)->d_reclen) - &(d)->d_name[0])
#else /* _DIRENT_HAVE_D_RECLEN */
#define _D_ALLOC_NAMLEN(d) (sizeof((d)->d_name) > 1 ? sizeof((d)->d_name) : _D_EXACT_NAMLEN(d) + 1)
#endif /* !_DIRENT_HAVE_D_RECLEN */
#endif /* !_DIRENT_HAVE_D_NAMLEN */

#ifdef __USE_XOPEN
#ifndef __ino_t_defined
#define __ino_t_defined
typedef __FS_TYPE(ino) ino_t; /* INode number */
#endif /* !__ino_t_defined */
#ifdef __USE_LARGEFILE64
#ifndef __ino64_t_defined
#define __ino64_t_defined
typedef __ino64_t ino64_t; /* INode number */
#endif /* !__ino64_t_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __DIR_defined
#define __DIR_defined
typedef struct __dirstream DIR;
#endif /* !__DIR_defined */

}

%[define(DEFINE_STRUCT_DIRSTREAM = struct __dirstream;)]

@@>> opendir(3)
@@Open and return a new directory stream for reading, referring to `name'
[[cp, wunused, decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
[[requires_include("<asm/os/fcntl.h>"), export_alias("__libc_opendir")]]
[[crt_dos_variant, userimpl, requires(defined(__AT_FDCWD) && $has_function(opendirat))]]
DIR *opendir([[nonnull]] char const *name) {
	/* TODO: Emulate using DOS's _find* functions */
	/* TODO: Emulate using fdopendir(open(name, 0)) */
	return opendirat(__AT_FDCWD, name);
}


%
%#if defined(__USE_KOS) && defined(__USE_ATFILE)
@@>> fopendirat(3)
@@Directory-handle-relative, and flags-enabled versions of `opendir(3)'
[[cp, wunused, decl_prefix(DEFINE_STRUCT_DIRSTREAM), decl_include("<bits/types.h>")]]
[[crt_dos_variant, userimpl, requires_function(fdopendir, openat)]]
DIR *fopendirat($fd_t dirfd, [[nonnull]] char const *name, $oflag_t oflags) {
	DIR *result;
	fd_t fd = openat(dirfd, name, oflags);
	if unlikely(fd < 0)
		return NULL;
	result = fdopendir(fd);
@@pp_if $has_function(close)@@
	if unlikely(!result)
		close(fd);
@@pp_endif@@
	return result;
}

@@>> opendirat(3)
@@Directory-handle-relative, and flags-enabled versions of `opendir(3)'
[[cp, wunused, decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
[[crt_dos_variant, userimpl, requires_function(fopendirat)]]
DIR *opendirat($fd_t dirfd, [[nonnull]] char const *name) {
	return fopendirat(dirfd, name, 0);
}
%#endif /* __USE_KOS && __USE_ATFILE */

%
@@>> closedir(3)
@@Close a directory stream previously returned by `opendir(3)' and friends
[[decl_prefix(DEFINE_STRUCT_DIRSTREAM), export_alias("__libc_closedir")]]
int closedir([[nonnull]] DIR *dirp);


%
%#ifdef __USE_BSD
@@>> fdclosedir(3)
@@Same as `closedir()', but instead of also closing the underlying file descriptor, return it
[[wunused, decl_prefix(DEFINE_STRUCT_DIRSTREAM), decl_include("<bits/types.h>")]]
$fd_t fdclosedir([[nonnull]] DIR *dirp);
%#endif /* __USE_BSD */

%
@@>> readdir(3), readdir64(3)
@@Read and return the next pending directory entry of the given directory stream `dirp'
@@@except: Returns `NULL' for end-of-directory; throws an error if something else went wrong
[[cp, decl_include("<bits/os/dirent.h>"), decl_prefix(DEFINE_STRUCT_DIRSTREAM), no_crt_self_import, crt_name("readdirk")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("readdirk")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__CRT_KOS) && ( defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("readdirk64")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("readdir", "__libc_readdir")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__CRT_KOS) && ( defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("readdir64")]]
struct dirent *readdir([[nonnull]] DIR *__restrict dirp);

%
@@>> rewinddir(3)
@@Rewind the given directory stream in such a way that the next call
@@to `readdir(3)' will once again  return the first directory  entry
[[decl_prefix(DEFINE_STRUCT_DIRSTREAM), export_alias("__libc_rewinddir")]]
void rewinddir([[nonnull]] DIR *__restrict dirp);

%
%#ifdef __USE_XOPEN2K8
@@>> fdopendir(3)
@@Create a new directory stream by inheriting the given `fd' as stream handle
[[wunused, decl_prefix(DEFINE_STRUCT_DIRSTREAM), decl_include("<bits/types.h>")]]
DIR *fdopendir($fd_t fd);
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_LARGEFILE64
[[cp, decl_include("<bits/os/dirent.h>"), decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
[[no_crt_self_import, crt_name("readdirk64"), doc_alias("readdir")]]
[[if($extended_include_prefix("<bits/os/dirent.h>") defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)), alias("readdirk")]]
[[if(                                               defined(__CRT_KOS)                                     ), alias("readdirk64")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")!defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)), alias("readdir", "__libc_readdir")]]
[[if(                                              !defined(__CRT_KOS)                                     ), alias("readdir64")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")defined(_DIRENT_MATCHES_DIRENT64)), crt_intern_kos_alias(libc_readdirk)]]
struct dirent64 *readdir64([[nonnull]] DIR *__restrict dirp);
%#endif /* __USE_LARGEFILE64 */


%#ifdef __USE_POSIX
@@>> readdir_r(3), readdir64_r(3)
@@Reentrant version of `readdir(3)'
@@NOTE: This ~reentrant~ version of readdir()  is strongly discouraged from being  used in KOS, as  the
@@      kernel does not impose a limit on the length of a single directory entry name (s.a. 'kreaddir')
@@>> Instead, simply use `readdir()' / `readdir64()', which will automatically (re-)allocate an internal,
@@   per-directory  buffer  of sufficient  size to  house any  directory entry  (s.a.: `READDIR_DEFAULT')
[[cp, decl_include("<bits/os/dirent.h>"), decl_prefix(DEFINE_STRUCT_DIRSTREAM), no_crt_self_import, crt_name("readdirk_r")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("readdirk_r")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__CRT_KOS) && ( defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("readdirk64_r")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("readdir_r", "__libc_readdir_r")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__CRT_KOS) && ( defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("readdir64_r")]]
int readdir_r([[nonnull]] DIR *__restrict dirp,
              [[nonnull]] struct dirent *__restrict entry,
              [[nonnull]] struct dirent **__restrict result);

%
%#ifdef __USE_LARGEFILE64
[[cp, decl_include("<bits/os/dirent.h>"), decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
[[no_crt_self_import, crt_name("readdirk64_r"), doc_alias("readdir")]]
[[if($extended_include_prefix("<bits/os/dirent.h>") defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)), alias("readdirk_r")]]
[[if(                                               defined(__CRT_KOS)                                     ), alias("readdirk64_r")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")!defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)), alias("readdir_r", "__libc_readdir_r")]]
[[if(                                              !defined(__CRT_KOS)                                     ), alias("readdir64_r")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")defined(_DIRENT_MATCHES_DIRENT64)), crt_intern_kos_alias(libc_readdirk_r)]]
int readdir64_r([[nonnull]] DIR *__restrict dirp,
                [[nonnull]] struct dirent64 *__restrict entry,
                [[nonnull]] struct dirent64 **__restrict result);
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_POSIX */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN)

@@>> seekdir(3)
@@Get the directory stream position
[[decl_prefix(DEFINE_STRUCT_DIRSTREAM), decl_include("<hybrid/typecore.h>")]]
[[export_alias("__libc_seekdir")]]
void seekdir([[nonnull]] DIR *__restrict dirp, $longptr_t pos);

@@>> telldir(3)
@@Get the directory stream position
[[decl_prefix(DEFINE_STRUCT_DIRSTREAM), decl_include("<hybrid/typecore.h>")]]
[[export_alias("__libc_telldir")]]
$longptr_t telldir([[nonnull]] DIR *__restrict dirp);

%#endif /* __USE_MISC || __USE_XOPEN */

%[define_c_language_keyword(__KOS_FIXED_CONST)]

%
%#ifdef __USE_XOPEN2K8

@@>> dirfd(3)
@@Return the underlying file descriptor of the given directory stream
[[pure, decl_include("<features.h>", "<bits/types.h>")]]
[[decl_prefix(DEFINE_STRUCT_DIRSTREAM)]]
$fd_t dirfd([[nonnull]] DIR __KOS_FIXED_CONST *__restrict dirp);

@@>> scandir(3), scandir64(3)
@@Scan a directory `dir' for all contained directory entries
[[cp, nodos, decl_include("<features.h>", "<bits/os/dirent.h>"), no_crt_self_import, crt_name("scandirk")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("scandirk")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__CRT_KOS) && ( defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("scandirk64")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("scandir")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__CRT_KOS) && ( defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("scandir64")]]
[[userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(scandirat))]]
__STDC_INT_AS_SSIZE_T scandir([[nonnull]] char const *__restrict dir,
                              [[nonnull]] struct dirent ***__restrict namelist,
                              int (LIBKCALL *selector)(struct dirent const *entry),
                              int (LIBKCALL *cmp)(struct dirent const **a, struct dirent const **b)) {
	return scandirat(__AT_FDCWD, dir, namelist, selector, cmp);
}

@@>> alphasort(3), alphasort64(3)
@@Sort the 2 given directory entries `e1' and `e2' the same way `strcmp(3)' would
[[userimpl, pure, decl_include("<bits/os/dirent.h>"), impl_include("<bits/os/dirent.h>"), no_crt_self_import, crt_name("alphasortk")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("alphasortk")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__CRT_KOS) && ( defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("alphasortk64")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("alphasort")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__CRT_KOS) && ( defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("alphasort64")]]
int alphasort([[nonnull]] struct dirent const **e1,
              [[nonnull]] struct dirent const **e2) {
	return strcoll((*e1)->@d_name@, (*e2)->@d_name@);
}

%
%#ifdef __USE_LARGEFILE64
[[userimpl, pure, decl_include("<bits/os/dirent.h>"), impl_include("<bits/os/dirent.h>")]]
[[no_crt_self_import, crt_name("alphasortk64"), doc_alias("alphasort")]]
[[if($extended_include_prefix("<bits/os/dirent.h>") defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)), alias("alphasortk")]]
[[if(                                               defined(__CRT_KOS)                                     ), alias("alphasortk64")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")!defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)), alias("alphasort")]]
[[if(                                              !defined(__CRT_KOS)                                     ), alias("alphasort64")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")defined(_DIRENT_MATCHES_DIRENT64)), crt_intern_kos_alias(libc_alphasortk)]]
int alphasort64([[nonnull]] struct dirent64 const **e1,
                [[nonnull]] struct dirent64 const **e2) {
	return strcoll((*e1)->@d_name@, (*e2)->@d_name@);
}
%#endif /* __USE_LARGEFILE64 */

%
%#ifdef __USE_GNU
@@>> scandirat(3), scandirat64(3)
@@Scan a directory `dirfd:dir' for all contained directory entries
[[cp, nodos, decl_include("<features.h>", "<bits/os/dirent.h>"), no_crt_self_import, crt_name("scandiratk")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("scandiratk")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__CRT_KOS) && ( defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("scandiratk64")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("scandirat")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__CRT_KOS) && ( defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("scandirat64")]]
__STDC_INT_AS_SSIZE_T scandirat($fd_t dirfd, [[nonnull]] char const *__restrict dir,
                                [[nonnull]] struct dirent ***__restrict namelist,
                                int (LIBKCALL *selector)(struct dirent const *entry),
                                int (LIBKCALL *cmp)(struct dirent const **a, struct dirent const **b));

%
%#ifdef __USE_LARGEFILE64

[[cp, nodos, decl_include("<features.h>", "<bits/os/dirent.h>")]]
[[no_crt_self_import, crt_name("scandirk64"), doc_alias("scandir")]]
[[if($extended_include_prefix("<bits/os/dirent.h>") defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)), alias("scandirk")]]
[[if(                                               defined(__CRT_KOS)                                     ), alias("scandirk64")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")!defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)), alias("scandir")]]
[[if(                                              !defined(__CRT_KOS)                                     ), alias("scandir64")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")defined(_DIRENT_MATCHES_DIRENT64)), crt_intern_kos_alias(libc_scandirk)]]
[[userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(scandirat64))]]
__STDC_INT_AS_SSIZE_T scandir64([[nonnull]] char const *__restrict dir,
                                [[nonnull]] struct dirent64 ***__restrict namelist,
                                int (LIBKCALL *selector)(struct dirent64 const *entry),
                                int (LIBKCALL *cmp)(struct dirent64 const **a, struct dirent64 const **b)) {
	return scandirat64(__AT_FDCWD, dir, namelist, selector, cmp);
}

[[cp, nodos, decl_include("<features.h>", "<bits/os/dirent.h>")]]
[[no_crt_self_import, crt_name("scandiratk64"), doc_alias("scandirat")]]
[[if($extended_include_prefix("<bits/os/dirent.h>") defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)), alias("scandiratk")]]
[[if(                                               defined(__CRT_KOS)                                     ), alias("scandiratk64")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")!defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)), alias("scandirat")]]
[[if(                                              !defined(__CRT_KOS)                                     ), alias("scandirat64")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")defined(_DIRENT_MATCHES_DIRENT64)), crt_intern_kos_alias(libc_scandiratk)]]
__STDC_INT_AS_SSIZE_T scandirat64($fd_t dirfd, [[nonnull]] char const *__restrict dir,
                                  [[nonnull]] struct dirent64 ***__restrict namelist,
                                  int (LIBKCALL *selector)(struct dirent64 const *entry),
                                  int (LIBKCALL *cmp)(struct dirent64 const **a, struct dirent64 const **b));

%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_GNU */
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_MISC
@@>> getdirentries(2), getdirentries64(2)
@@Linux's underlying system call for reading the entries of a directory
[[cp, decl_include("<features.h>", "<bits/types.h>"), no_crt_self_import, export_as("__getdirentries", "__libc_getdirentries")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__USE_FILE_OFFSET64) || (defined(_DIRENT_MATCHES_DIRENT64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)), alias("getdirentries", "__getdirentries", "__libc_getdirentries")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__USE_FILE_OFFSET64) || (defined(_DIRENT_MATCHES_DIRENT64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)), alias("getdirentries64")]]
$ssize_t getdirentries($fd_t fd, [[nonnull]] char *__restrict buf,
                       size_t nbytes, [[nonnull]] $off_t *__restrict basep);

%#ifdef __USE_LARGEFILE64
[[cp, decl_include("<bits/types.h>")]]
[[preferred_dirent64_variant_of(getdirentries), doc_alias("getdirentries")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")defined(_DIRENT_MATCHES_DIRENT64) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), preferred_alias("__getdirentries", "__libc_getdirentries")]]
$ssize_t getdirentries64($fd_t fd, [[nonnull]] char *__restrict buf, size_t nbytes,
                         [[nonnull]] $off64_t *__restrict basep);
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_MISC */

%
%#ifdef __USE_GNU
@@>> versionsort(3), versionsort64(3)
@@Sort the 2 given directory entries `e1' and `e2' the same way `strvercmp(3)' would.
[[userimpl, pure, decl_include("<bits/os/dirent.h>"), impl_include("<bits/os/dirent.h>"), no_crt_self_import, crt_name("versionsortk")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("versionsortk")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__CRT_KOS) && ( defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("versionsortk64")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__CRT_KOS) && (!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("versionsort")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__CRT_KOS) && ( defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64))), alias("versionsort64")]]
int versionsort([[nonnull]] struct dirent const **e1,
                [[nonnull]] struct dirent const **e2) {
	return strverscmp((*e1)->@d_name@, (*e2)->@d_name@);
}
%#ifdef __USE_LARGEFILE64
[[userimpl, pure, decl_include("<bits/os/dirent.h>"), impl_include("<bits/os/dirent.h>")]]
[[no_crt_self_import, crt_name("versionsortk64"), doc_alias("versionsort")]]
[[if($extended_include_prefix("<bits/os/dirent.h>") defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)), alias("versionsortk")]]
[[if(                                               defined(__CRT_KOS)                                     ), alias("versionsortk64")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")!defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)), alias("versionsort")]]
[[if(                                              !defined(__CRT_KOS)                                     ), alias("versionsort64")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")defined(_DIRENT_MATCHES_DIRENT64)), crt_intern_kos_alias(libc_versionsortk)]]
int versionsort64([[nonnull]] struct dirent64 const **e1,
                  [[nonnull]] struct dirent64 const **e2) {
	return strverscmp((*e1)->@d_name@, (*e2)->@d_name@);
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_GNU */



%
%#if defined(__USE_KOS) && defined(__KOS__) && defined(__CRT_KOS)
@@>> kreaddir(2), kreaddirf(2), kreaddir64(2), kreaddirf64(2)
@@The KOS-specific system call for reading a single directory entry
@@from  a file  descriptor referring  to an  open directory stream.
@@@param: mode: One of `READDIR_*' (See below)
@@@return: * : The actually required buffer size for the directory entry (in bytes)
@@             NOTE: When  `READDIR_DEFAULT' was passed for `mode', the directory
@@                   stream will only be advanced when this value is >= 'bufsize'
@@@return: 0 : The end of the directory has been reached.
@@@return: -1: Failed to read a directory entry for some reason (s.a.: `errno')
[[decl_include("<bits/os/dirent.h>", "<bits/types.h>")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")defined(_DIRENT_MATCHES_DIRENT64)), alias("kreaddir64")]]
[[cp, wunused, userimpl, requires_function(kreaddirf)]]
$ssize_t kreaddir($fd_t fd, struct dirent *buf, size_t bufsize, unsigned int mode) {
	return kreaddirf(fd, buf, bufsize, mode, 0);
}

[[cp, wunused, doc_alias("kreaddir"), decl_include("<bits/os/dirent.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>")!defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), alias("kreaddirf")]]
[[if($extended_include_prefix("<features.h>", "<bits/os/dirent.h>") defined(__USE_FILE_OFFSET64) || defined(_DIRENT_MATCHES_DIRENT64)), alias("kreaddirf64")]]
$ssize_t kreaddirf($fd_t fd, struct dirent *buf, size_t bufsize, unsigned int mode, $oflag_t flags);

%#ifdef __USE_LARGEFILE64

[[cp, wunused, decl_include("<bits/os/dirent.h>", "<bits/types.h>")]]
[[preferred_dirent64_variant_of(kreaddir), doc_alias("kreaddir")]]
[[if($extended_include_prefix("<bits/os/dirent.h>")defined(_DIRENT_MATCHES_DIRENT64)), alias("kreaddir")]]
[[userimpl, requires_function(kreaddirf64)]]
$ssize_t kreaddir64($fd_t fd, struct dirent64 *buf, size_t bufsize, unsigned int mode) {
	return kreaddirf64(fd, buf, bufsize, mode, 0);
}

[[cp, wunused, decl_include("<bits/os/dirent.h>", "<bits/types.h>")]]
[[preferred_dirent64_variant_of(kreaddirf), doc_alias("kreaddirf")]]
$ssize_t kreaddirf64($fd_t fd, struct dirent64 *buf, size_t bufsize,
                     unsigned int mode, $oflag_t flags);

%#endif /* __USE_LARGEFILE64 */

%
%{
#ifndef READDIR_DEFAULT
#define READDIR_DEFAULT  0x0000 /* Yield to next entry when `buf' was of sufficient size. */
#define READDIR_CONTINUE 0x0001 /* Always yield to next entry. */
#define READDIR_PEEK     0x0002 /* Never yield to next entry. */
#if __KOS_VERSION__ >= 300
#define READDIR_SKIPREL  0x4000 /* Skip reading the `.' and `..' directory entries. */
#define READDIR_WANTEOF  0x8000 /* Minor optimization for `READDIR_MULTIPLE':
                                 * The system is allowed to append an empty directory entry
                                 * (with  `d_namlen = 0' and `d_name[0] = '\0''; other fields are undefined).
                                 * If there isn't enough space for such an entry, no such entry will be emit.
                                 * Since no other  directory entry can  ever have a  length of ZERO(0),  this
                                 * allows  user-space  to detect  end-of-directory  without the  need  of re-
                                 * invoking  the kreaddir() system  call and inspecting  its return value for
                                 * being equal to ZERO(0).
                                 * However, that check is still required, as this flag may be ignored for no
                                 * reason immediately apparent (if the EOF entry can't fit into the  buffer,
                                 * there's  no way of knowing if there's  a missing entry that's supposed to
                                 * go into the buffer, or if it was actually an EOF entry). Additionally, no
                                 * EOF  entry may be written if kreaddir()  is invoked on a directory handle
                                 * who's stream position is at the end of the directory.
                                 * For usage, see the example below, as well as `READDIR_MULTIPLE_ISEOF()' */
#define READDIR_MODEMASK 0x001f /* Mask for the kreaddir() mode. */
#define READDIR_FLAGMASK 0xc000 /* Mask of known kreaddir() flags. */
#define READDIR_MODEMAX  0x0003 /* Mask recognized mode ID. */
#define READDIR_MULTIPLE 0x0003 /* Read as many directory entries as can fit into the buffer. If at
                                 * least one entry could be read,  return the combined size of  all
                                 * read entries (in bytes) (in this case, `return <= bufsize').  If
                                 * the buffer was too small to  contain the next entry, return  the
                                 * required size to house that  pending entry, but don't yield  it,
                                 * the  same way `READDIR_DEFAULT'  wouldn't. To enumerate multiple
                                 * directories in some buffer, use the macros below. */
#ifdef __CC__
/* READDIR_MULTIPLE buffer helpers:
 * >> for (;;) {
 * >>     char buffer[2048]; size_t bufsize;
 * >>     struct dirent *iter = (struct dirent *)buffer;
 * >>     // Read as many entries as our buffer can fit
 * >>     bufsize = kreaddir(fd, iter, sizeof(buffer),
 * >>                        READDIR_MULTIPLE|
 * >>                        READDIR_WANTEOF);
 * >>     if (!bufsize)
 * >>         break; // End of directory
 * >>     if (bufsize > sizeof(buffer)) {
 * >>         printf("The next directory entry larger than the buffer\n");
 * >>         break;
 * >>     }
 * >>     // Process successfully read entries
 * >>     do {
 * >>         // This check is only required when `READDIR_WANTEOF' is passed.
 * >>         if (READDIR_MULTIPLE_ISEOF(iter))
 * >>             goto done;
 * >>         printf("Entry: %q\n", iter->d_name);
 * >>         iter = READDIR_MULTIPLE_GETNEXT(iter);
 * >>     } while (READDIR_MULTIPLE_ISVALID(iter, buffer, bufsize));
 * >> }
 * >>done:
 */
#define READDIR_MULTIPLE_GETNEXT(p)                                      \
	((struct dirent *)(((uintptr_t)((p)->d_name + ((p)->d_namlen + 1)) + \
	                    (sizeof(__ino64_t) - 1)) &                       \
	                   ~(sizeof(__ino64_t) - 1)))
#define READDIR_MULTIPLE_ISVALID(p, buf, bufsize)                               \
	(((__BYTE_TYPE__ *)((p)->d_name)) < ((__BYTE_TYPE__ *)(buf) + (bufsize)) && \
	 ((__BYTE_TYPE__ *)((p)->d_name + (p)->d_namlen)) < ((__BYTE_TYPE__ *)(buf) + (bufsize)))
#define READDIR_MULTIPLE_ISEOF(p) ((p)->d_namlen == 0)
#ifdef __USE_LARGEFILE64
#define READDIR_MULTIPLE_GETNEXT64(p) ((struct dirent64 *)READDIR_MULTIPLE_GETNEXT(p))
#endif /* __USE_LARGEFILE64 */
#endif /* __CC__ */
#endif /* __KOS_VERSION__ >= 300 */
#endif /* !READDIR_DEFAULT */
}
%#endif /* __USE_KOS && __KOS__ && __CRT_KOS */

%{

#endif /* __CC__ */

__SYSDECL_END

}
