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
%[default_impl_section(".text.crt.io.utility")]

%[define_replacement(fd_t    = __fd_t)]
%[define_replacement(off_t   = "__FS_TYPE(off)")]
%[define_replacement(pos_t   = "__FS_TYPE(pos)")]
%[define_replacement(off32_t = __off32_t)]
%[define_replacement(off64_t = __off64_t)]
%[define_replacement(pos32_t = __pos32_t)]
%[define_replacement(pos64_t = __pos64_t)]
%[define_replacement(oflag_t = __oflag_t)]



%[define_replacement(O_ACCMODE   = __O_ACCMODE)]
%[define_replacement(O_RDONLY    = __O_RDONLY)]
%[define_replacement(O_WRONLY    = __O_WRONLY)]
%[define_replacement(O_RDWR      = __O_RDWR)]
%[define_replacement(O_TRUNC     = __O_TRUNC)]
%[define_replacement(O_CREAT     = __O_CREAT)]
%[define_replacement(O_EXCL      = __O_EXCL)]
%[define_replacement(O_NOCTTY    = __O_NOCTTY)]
%[define_replacement(O_APPEND    = __O_APPEND)]
%[define_replacement(O_NONBLOCK  = __O_NONBLOCK)]
%[define_replacement(O_SYNC      = __O_SYNC)]
%[define_replacement(O_DSYNC     = __O_DSYNC)]
%[define_replacement(O_ASYNC     = __O_ASYNC)]
%[define_replacement(O_DIRECT    = __O_DIRECT)]
%[define_replacement(O_LARGEFILE = __O_LARGEFILE)]
%[define_replacement(O_DIRECTORY = __O_DIRECTORY)]
%[define_replacement(O_NOFOLLOW  = __O_NOFOLLOW)]
%[define_replacement(O_NOATIME   = __O_NOATIME)]
%[define_replacement(O_CLOEXEC   = __O_CLOEXEC)]
%[define_replacement(O_PATH      = __O_PATH)]
%[define_replacement(O_TMPFILE   = __O_TMPFILE)]
%[define_replacement(O_CLOFORK   = __O_CLOFORK)]
%[define_replacement(O_SYMLINK   = __O_SYMLINK)]
%[define_replacement(O_DOSPATH   = __O_DOSPATH)]
%[define_replacement(O_ANYTHING  = __O_ANYTHING)]



%{
#include <features.h>

#include <bits/fcntl.h>
#include <bits/types.h>
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <asm/stdio.h>
#include <bits/stat.h>
#include <bits/timespec.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

__SYSDECL_BEGIN

#ifdef __O_TMPFILE
#   define __OPEN_NEEDS_MODE(oflags) (((oflags)&O_CREAT) || ((oflags)&__O_TMPFILE) == __O_TMPFILE)
#else /* __O_TMPFILE */
#   define __OPEN_NEEDS_MODE(oflags)  ((oflags)&O_CREAT)
#endif /* !__O_TMPFILE */

/* For XPG all symbols from <sys/stat.h> should also be available. */
#if !defined(S_IFMT) && (defined(__USE_XOPEN) || defined(__USE_XOPEN2K8))
#define S_IFMT     __S_IFMT
#define S_IFDIR    __S_IFDIR
#define S_IFCHR    __S_IFCHR
#define S_IFBLK    __S_IFBLK
#define S_IFREG    __S_IFREG
#ifdef __S_IFIFO
#define S_IFIFO __S_IFIFO
#endif /* __S_IFIFO */
#ifdef __S_IFLNK
#define S_IFLNK __S_IFLNK
#endif /* __S_IFLNK */
#if (defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)) && defined(__S_IFSOCK)
#define S_IFSOCK __S_IFSOCK
#endif /* (__USE_UNIX98 || __USE_XOPEN2K8) && __S_IFSOCK */
#define S_ISUID __S_ISUID /* Set user ID on execution. */
#define S_ISGID __S_ISGID /* Set group ID on execution. */
#if defined(__USE_MISC) || defined(__USE_XOPEN)
#define S_ISVTX __S_ISVTX
#endif /* __USE_MISC || __USE_XOPEN */
#define S_IRUSR  __S_IREAD  /* Read by owner. */
#define S_IWUSR  __S_IWRITE /* Write by owner. */
#define S_IXUSR  __S_IEXEC  /* Execute by owner. */
#define S_IRWXU (__S_IREAD|__S_IWRITE|__S_IEXEC)
#define S_IRGRP (S_IRUSR >> 3) /* Read by group. */
#define S_IWGRP (S_IWUSR >> 3) /* Write by group. */
#define S_IXGRP (S_IXUSR >> 3) /* Execute by group. */
#define S_IRWXG (S_IRWXU >> 3)
#define S_IROTH (S_IRGRP >> 3) /* Read by others. */
#define S_IWOTH (S_IWGRP >> 3) /* Write by others. */
#define S_IXOTH (S_IXGRP >> 3) /* Execute by others. */
#define S_IRWXO (S_IRWXG >> 3)
#endif /* !S_IFMT && (__USE_XOPEN || __USE_XOPEN2K8) */


#ifdef __USE_MISC
#ifndef R_OK
#define R_OK 4 /* Test for read permission. */
#define W_OK 2 /* Test for write permission. */
#define X_OK 1 /* Test for execute permission. */
#define F_OK 0 /* Test for existence. */
#endif /* !R_OK */
#endif /* __USE_MISC */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#ifndef SEEK_SET
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#define SEEK_END __SEEK_END /* Seek from end of file. */
#ifdef __USE_GNU
#ifdef __SEEK_DATA
#define SEEK_DATA __SEEK_DATA /* Seek to next data. */
#endif /* __SEEK_DATA */
#ifdef __SEEK_HOLE
#define SEEK_HOLE __SEEK_HOLE /* Seek to next hole. */
#endif /* __SEEK_HOLE */
#endif /* __USE_GNU */
#endif /* !SEEK_SET */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */


#ifdef __CC__

}



%#ifdef __USE_GNU
[[userimpl, decl_include("<bits/types.h>")]]
readahead:($fd_t fd, $off64_t offset, $size_t count) -> $ssize_t {
	(void)fd;
	(void)offset;
	return count;
}
[[userimpl, decl_include("<bits/types.h>")]]
int sync_file_range($fd_t fd, $off64_t offset, $off64_t count, unsigned int flags) {
	(void)fd;
	(void)offset;
	(void)count;
	(void)flags;
	return 0;
}
%struct iovec;

[[cp, decl_include("<bits/types.h>")]]
$ssize_t vmsplice($fd_t fdout, struct iovec const *iov, $size_t count, unsigned int flags);
[[cp, decl_include("<bits/types.h>")]]
$ssize_t splice($fd_t fdin, $off64_t *offin, $fd_t fdout, $off64_t *offout, $size_t length, unsigned int flags);
[[cp, decl_include("<bits/types.h>")]]
$ssize_t tee($fd_t fdin, $fd_t fdout, $size_t length, unsigned int flags);
[[cp, decl_include("<bits/types.h>")]]
int name_to_handle_at($fd_t dirfd, char const *name, struct file_handle *handle, int *mnt_id, int flags);
[[cp, decl_include("<bits/types.h>")]]
$fd_t open_by_handle_at($fd_t mountdirfd, struct file_handle *handle, int flags);

[[ignore, nocrt, alias(fallocate), decl_include("<bits/types.h>")]]
int fallocate32($fd_t fd, int mode, $off64_t offset, $off64_t length);

[[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fallocate64)]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(fallocate)]]
[[userimpl, decl_include("<bits/types.h>"), no_crt_self_import]]
int fallocate($fd_t fd, int mode, $off_t offset, $off_t length) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)fd;
	(void)mode;
	(void)offset;
	(void)length;
	return 0;
@@pp_elif $has_function(fallocate64)@@
	return fallocate64(fd, mode, ($off64_t)offset, ($off64_t)length);
@@pp_elif $has_function(fallocate32)@@
	return fallocate32(fd, mode, ($off32_t)offset, ($off32_t)length);
@@pp_else@@
	(void)fd;
	(void)mode;
	(void)offset;
	(void)length;
	return 0;
@@pp_endif@@
}

%#ifdef __USE_LARGEFILE64
[[userimpl, off64_variant_of(fallocate), decl_include("<bits/types.h>")]]
int fallocate64($fd_t fd, int mode, $off64_t offset, $off64_t length) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)fd;
	(void)mode;
	(void)offset;
	(void)length;
	return 0;
@@pp_elif $has_function(fallocate32)@@
	return fallocate32(fd, mode, ($off32_t)offset, ($off32_t)length);
@@pp_else@@
	(void)fd;
	(void)mode;
	(void)offset;
	(void)length;
	return 0;
@@pp_endif@@
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_GNU */


[[vartypes(void *), guard, decl_include("<bits/types.h>"), export_alias("__fcntl")]]
__STDC_INT_AS_SSIZE_T fcntl($fd_t fd, int cmd, ...);

%[default_impl_section(".text.crt.io.access")]

[[ignore, vartypes($mode_t), decl_include("<bits/types.h>")]]
[[nocrt, alias(open, _open, __open), cp, ATTR_WUNUSED]]
$fd_t open32([[nonnull]] char const *filename, $oflag_t oflags, ...);


[[cp, guard, ATTR_WUNUSED, vartypes($mode_t), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("open64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("open", "_open", "__open")]]
[[decl_include("<bits/types.h>"), export_as("__open")]]
[[userimpl, requires($has_function(open64) || (defined(__CRT_AT_FDCWD) && $has_function(openat)))]]
$fd_t open([[nonnull]] char const *filename, $oflag_t oflags, ...) {
	$fd_t result;
	va_list args;
	va_start(args, oflags);
@@pp_if $has_function(open64)@@
	result = open64(filename, oflags, va_arg(args, mode_t));
@@pp_else@@
	result = openat(__CRT_AT_FDCWD, filename, oflags, va_arg(args, mode_t));
@@pp_endif@@
	va_end(args);
	return result;
}

[[cp, guard, ATTR_WUNUSED, no_crt_self_import, alias("_creat")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("creat64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("creat")]]
[[userimpl, requires_function(creat64, open)]]
[[impl_include("<bits/fcntl.h>"), decl_include("<bits/types.h>")]]
$fd_t creat([[nonnull]] char const *filename, $mode_t mode) {
@@pp_if $has_function(creat64)@@
	return creat64(filename, mode);
@@pp_else@
	return open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode);
@@pp_endif@@
}

%
%#ifdef __USE_LARGEFILE64
[[vartypes($mode_t), export_alias("__open64"), largefile64_variant_of(open)]]
[[decl_include("<bits/types.h>"), impl_include("<bits/fcntl.h>")]]
[[if(!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("open", "_open")]]
[[cp, ATTR_WUNUSED, userimpl, requires_function(open32)]]
$fd_t open64([[nonnull]] char const *filename, $oflag_t oflags, ...) {
	$fd_t result;
	va_list args;
	mode_t mode;
	va_start(args, oflags);
	mode = va_arg(args, mode_t);
@@pp_ifdef O_LARGEFILE@@
	result = open32(filename, oflags | O_LARGEFILE, mode);
@@pp_else@@
	result = open32(filename, oflags, mode);
@@pp_endif@@
	va_end(args);
	return result;
}

[[guard, largefile64_variant_of(creat)]]
[[decl_include("<bits/types.h>"), impl_include("<bits/fcntl.h>")]]
[[if(!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("creat", "_creat")]]
[[cp, ATTR_WUNUSED, userimpl, requires_function(open64)]]
$fd_t creat64([[nonnull]] char const *filename, $mode_t mode) {
	return open64(filename, O_CREAT | O_WRONLY | O_TRUNC, mode);
}
%#endif /* __USE_LARGEFILE64 */
%
%#ifdef __USE_ATFILE

[[cp, ignore, nocrt, alias("openat")]]
[[ATTR_WUNUSED, vartypes($mode_t), decl_include("<bits/types.h>")]]
$fd_t openat32($fd_t dirfd, [[nonnull]] char const *filename, $oflag_t oflags, ...);

[[cp, ATTR_WUNUSED, guard, vartypes($mode_t), no_crt_self_import]]
[[decl_include("<bits/types.h>"), impl_include("<bits/fcntl.h>")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("openat64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("openat")]]
[[userimpl, requires_function(openat64)]]
$fd_t openat($fd_t dirfd, [[nonnull]] char const *filename, $oflag_t oflags, ...) {
	$fd_t result;
	va_list args;
	va_start(args, oflags);
	result = openat64(dirfd, filename, oflags, va_arg(args, mode_t));
	va_end(args);
	return result;
}

%#ifdef __USE_LARGEFILE64
[[cp, ATTR_WUNUSED, guard, vartypes($mode_t)]]
[[decl_include("<bits/types.h>"), largefile64_variant_of(openat)]]
[[userimpl, requires_function(openat32)]]
$fd_t openat64($fd_t dirfd, [[nonnull]] char const *filename, $oflag_t oflags, ...) {
	fd_t result;
	va_list args;
	mode_t mode;
	va_start(args, oflags);
	mode = va_arg(args, mode_t);
#ifdef O_LARGEFILE
	result = openat32(dirfd, filename, oflags | O_LARGEFILE, mode);
#else /* O_LARGEFILE */
	result = openat32(dirfd, filename, oflags, mode);
#endif /* !O_LARGEFILE */
	va_end(args);
	return result;
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_ATFILE */
%
%#ifdef __USE_XOPEN2K

[[decl_include("<bits/types.h>"), ignore, nocrt, alias("posix_fadvise")]]
int posix_fadvise32($fd_t fd, $off32_t offset, $off32_t length, int advise);


[[decl_include("<bits/types.h>"), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("posix_fadvise64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("posix_fadvise")]]
[[userimpl, section(".text.crt.io.utility")]]
posix_fadvise:($fd_t fd, $off_t offset, $off_t length, int advise) -> int {
@@pp_ifdef __BUILDING_LIBC@@
	(void)fd;
	(void)offset;
	(void)length;
	(void)advise;
	return 0;
@@pp_elif $has_function(posix_fadvise64)@@
	return posix_fadvise64(fd, ($off64_t)offset, ($off64_t)length, advise);
@@pp_elif $has_function(posix_fadvise32)@@
	return posix_fadvise32(fd, ($off32_t)offset, ($off32_t)length, advise);
@@pp_else@@
	(void)fd;
	(void)offset;
	(void)length;
	(void)advise;
	return 0;
@@pp_endif@@
}

[[decl_include("<bits/types.h>"), ignore, nocrt, alias("posix_fallocate")]]
int posix_fallocate32($fd_t fd, $off32_t offset, $off32_t length);

[[decl_include("<bits/types.h>"), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("posix_fallocate64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("posix_fallocate")]]
[[userimpl, section(".text.crt.io.utility")]]
int posix_fallocate($fd_t fd, $off_t offset, $off_t length) {
@@pp_ifdef __BUILDING_LIBC@@
	(void)fd;
	(void)offset;
	(void)length;
	return 0;
@@pp_elif $has_function(posix_fallocate64)@@
	return posix_fallocate64(fd, ($off64_t)offset, ($off64_t)length);
@@pp_elif $has_function(posix_fallocate32)@@
	return posix_fallocate32(fd, ($off32_t)offset, ($off32_t)length);
@@pp_else@@
	(void)fd;
	(void)offset;
	(void)length;
	return 0;
@@pp_endif@@
}

%#ifdef __USE_LARGEFILE64
[[off64_variant_of(posix_fadvise), decl_include("<bits/types.h>")]]
[[userimpl, section(".text.crt.io.large.utility")]]
int posix_fadvise64($fd_t fd, $off64_t offset, $off64_t length, int advise) {
@@pp_if $has_function(posix_fadvise32)@@
	return posix_fadvise32(fd, ($off32_t)offset, ($off32_t)length, advise);
@@pp_else@@
	(void)fd;
	(void)offset;
	(void)length;
	(void)advise;
	return 0;
@@pp_endif@@
}

[[off64_variant_of(posix_fallocate), decl_include("<bits/types.h>")]]
[[userimpl, section(".text.crt.io.large.utility")]]
int posix_fallocate64($fd_t fd, $off64_t offset, $off64_t length) {
@@pp_if $has_function(posix_fallocate32)@@
	return posix_fallocate32(fd, ($off32_t)offset, ($off32_t)length);
@@pp_else@@
	(void)fd;
	(void)offset;
	(void)length;
	return 0;
@@pp_endif@@
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN2K */
%

%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_POSIX))
%#ifndef F_LOCK
%#define F_ULOCK 0 /* Unlock a previously locked region. */
%#define F_LOCK  1 /* Lock a region for exclusive use. */
%#define F_TLOCK 2 /* Test and lock a region for exclusive use. */
%#define F_TEST  3 /* Test a region for other processes locks. */
%#endif /* !F_LOCK */

[[cp, decl_include("<bits/types.h>"), ignore, nocrt, alias("locking", "_locking")]]
int crt_locking($fd_t fd, int cmd, $off32_t length);

[[cp, decl_include("<bits/types.h>"), ignore, nocrt, alias("lockf")]]
int lockf32($fd_t fd, int cmd, $off32_t length);

[[cp, guard, export_as("_locking", "locking"), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("lockf64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("lockf", "_locking", "locking")]]
[[decl_include("<bits/types.h>"), section(".text.crt.io.lock")]]
[[userimpl, requires($has_function(lockf64) || $has_function(lockf32) || $has_function(crt_locking))]]
int lockf($fd_t fd, int cmd, $off_t length) {
@@pp_if $has_function(lockf64)@@
	return lockf64(fd, cmd, (off64_t)length);
@@pp_elif $has_function(lockf32)@@
	return lockf32(fd, cmd, (off32_t)length);
@@pp_elif $has_function(crt_locking)@@
	return crt_locking(fd, cmd, (off32_t)length);
@@pp_endif@@
}

%#ifdef __USE_LARGEFILE64
[[cp, guard, off64_variant_of(lockf)]]
[[decl_include("<bits/types.h>"), section(".text.crt.io.large.lock")]]
[[userimpl, requires($has_function(lockf32) || $has_function(crt_locking))]]
int lockf64($fd_t fd, int cmd, $off64_t length) {
@@pp_if $has_function(lockf32)@@
	return lockf32(fd, cmd, (off64_t)length);
@@pp_else@@
	return crt_locking(fd, cmd, (off32_t)length);
@@pp_endif@@
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_POSIX) */


%{

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_FCNTL_H)
#include <parts/uchar/fcntl.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_FCNTL_H */
#endif /* __USE_UTF */

}

