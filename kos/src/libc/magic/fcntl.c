/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%[default_impl_section(.text.crt.io.utility)]

%[define_replacement(fd_t    = __fd_t)]
%[define_replacement(off_t   = __FS_TYPE(off))]
%[define_replacement(pos_t   = __FS_TYPE(pos))]
%[define_replacement(off32_t = __off32_t)]
%[define_replacement(off64_t = __off64_t)]
%[define_replacement(pos32_t = __pos32_t)]
%[define_replacement(pos64_t = __pos64_t)]
%[define_replacement(oflag_t = __oflag_t)]


%{
#include <features.h>
#include <bits/fcntl.h>
#include <bits/types.h>
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <bits/timespec.h>
#include <bits/stat.h>
#endif

__SYSDECL_BEGIN

#ifdef __O_TMPFILE
#   define __OPEN_NEEDS_MODE(oflags) (((oflags)&O_CREAT) || ((oflags)&__O_TMPFILE) == __O_TMPFILE)
#else
#   define __OPEN_NEEDS_MODE(oflags)  ((oflags)&O_CREAT)
#endif

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
#endif
#endif /* __USE_MISC */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#ifndef SEEK_SET
#   define SEEK_SET  0 /* Seek from beginning of file.  */
#   define SEEK_CUR  1 /* Seek from current position.  */
#   define SEEK_END  2 /* Seek from end of file.  */
#if defined(__USE_GNU) && (defined(__CRT_KOS) || defined(__CRT_GLC))
#   define SEEK_DATA 3 /* Seek to next data.  */
#   define SEEK_HOLE 4 /* Seek to next hole.  */
#endif /* __USE_GNU && (__CRT_KOS || __CRT_GLC) */
#endif
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */


#ifdef __CC__

}



%#ifdef __USE_GNU
[noexport]
[decl_include(<bits/types.h>)]
readahead:($fd_t fd, $off64_t offset, $size_t count) -> $ssize_t {
	(void)fd;
	(void)offset;
	return count;
}
[noexport]
[decl_include(<bits/types.h>)]
sync_file_range:($fd_t fd, $off64_t offset, $off64_t count, unsigned int flags) -> int {
	(void)fd;
	(void)offset;
	(void)count;
	(void)flags;
	return 0;
}
%struct iovec;

[decl_include(<bits/types.h>)]
[cp] vmsplice:($fd_t fdout, struct iovec const *iov, $size_t count, unsigned int flags) -> $ssize_t;
[decl_include(<bits/types.h>)]
[cp] splice:($fd_t fdin, $off64_t *offin, $fd_t fdout, $off64_t *offout, $size_t length, unsigned int flags) -> $ssize_t;
[decl_include(<bits/types.h>)]
[cp] tee:($fd_t fdin, $fd_t fdout, $size_t length, unsigned int flags) -> $ssize_t;
[decl_include(<bits/types.h>)]
[cp] name_to_handle_at:($fd_t dirfd, char const *name, struct file_handle *handle, int *mnt_id, int flags) -> int;
[decl_include(<bits/types.h>)]
[cp] open_by_handle_at:($fd_t mountdirfd, struct file_handle *handle, int flags) -> $fd_t;

[ignore][noexport]
[decl_include(<bits/types.h>)]
fallocate32:($fd_t fd, int mode, $off64_t offset, $off64_t length) -> int = fallocate?;

[if(defined(__USE_FILE_OFFSET64)), preferred_alias(fallocate64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(fallocate)]
[alias_args(fallocate64:($fd_t fd, int mode, $off64_t offset, $off64_t length) -> int)]
[alias_args(fallocate:($fd_t fd, int mode, $off32_t offset, $off32_t length) -> int)]
[noexport][decl_include(<bits/types.h>)]
fallocate:($fd_t fd, int mode, $off_t offset, $off_t length) -> int {
#ifdef __CRT_HAVE_fallocate64
	return fallocate64(fd, mode, ($off64_t)offset, ($off64_t)length);
#elif defined(__CRT_HAVE_fallocate)
	return fallocate32(fd, mode, ($off32_t)offset, ($off32_t)length);
#else /* __CRT_HAVE_fallocate */
	(void)fd;
	(void)mode;
	(void)offset;
	(void)length;
	return 0;
#endif /* !__CRT_HAVE_fallocate */
}

%#ifdef __USE_LARGEFILE64
[noexport][off64_variant_of(fallocate)]
[decl_include(<bits/types.h>)]
fallocate64:($fd_t fd, int mode, $off64_t offset, $off64_t length) -> int {
#ifdef __CRT_HAVE_fallocate
	return fallocate(fd, mode, ($off32_t)offset, ($off32_t)length);
#else /* __CRT_HAVE_fallocate */
	(void)fd;
	(void)mode;
	(void)offset;
	(void)length;
	return 0;
#endif /* !__CRT_HAVE_fallocate */
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_GNU */


[vartypes(void *)][guard]
[decl_include(<bits/types.h>)]
fcntl:($fd_t fd, int cmd, ...) -> __STDC_INT_AS_SSIZE_T;

%[default_impl_section(.text.crt.io.access)]

[cp][guard][ATTR_WUNUSED][noexport][vartypes($mode_t)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(open64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(open)]
[decl_include(<bits/types.h>)]
[alias(_open)][requires(defined(__CRT_HAVE_open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat) || defined(__CRT_HAVE_openat64))))]
open:([nonnull] char const *filename, $oflag_t oflags, ...) -> $fd_t {
	$fd_t result;
	va_list args;
	va_start(args, oflags);
#ifdef __CRT_HAVE_open64
	result = open64(filename, oflags, va_arg(args, mode_t));
#else
	result = openat(__CRT_AT_FDCWD, filename, oflags, va_arg(args, mode_t));
#endif
	va_end(args);
	return result;
}

[cp][guard][ATTR_WUNUSED]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(creat64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(creat)][alias(_creat)]
[requires(defined(__CRT_HAVE_open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open))]
[dependency_include(<bits/fcntl.h>)][noexport]
[decl_include(<bits/types.h>)]
creat:([nonnull] char const *filename, $mode_t mode) -> $fd_t {
	return open(filename, @O_CREAT@|@O_WRONLY@|@O_TRUNC@, mode);
}

%
%#ifdef __USE_LARGEFILE64
[cp][noexport][vartypes($mode_t)]
[ATTR_WUNUSED][largefile64_variant_of(open)]
[if(!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0),alias(_open)]
[requires(defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open))]
[dependency_include(<bits/fcntl.h>)]
[decl_include(<bits/types.h>)]
open64:([nonnull] char const *filename, $oflag_t oflags, ...) -> $fd_t {
	$fd_t result;
	va_list args;
	va_start(args, oflags);
#ifdef @__O_LARGEFILE@
	result = open(filename, oflags, va_arg(args, mode_t));
#else
	result = open(filename, oflags|@__O_LARGEFILE@, va_arg(args, mode_t));
#endif
	va_end(args);
	return result;
}

[cp][noexport][guard]
[ATTR_WUNUSED][largefile64_variant_of(creat)]
[if(!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0),alias(_creat)]
[requires(defined(__CRT_HAVE_open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open))]
[dependency_include(<bits/fcntl.h>)]
[decl_include(<bits/types.h>)]
creat64:([nonnull] char const *filename, $mode_t mode) -> $fd_t {
	return open64(filename, @O_CREAT@|@O_WRONLY@|@O_TRUNC@, mode);
}
%#endif /* __USE_LARGEFILE64 */
%
%#ifdef __USE_ATFILE

[cp][ignore][ATTR_WUNUSED][vartypes($mode_t)][decl_include(<bits/types.h>)]
openat32:($fd_t dirfd, [nonnull] char const *filename, $oflag_t oflags, ...) -> $fd_t = openat?;

[cp][guard][noexport][vartypes($mode_t)][ATTR_WUNUSED]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(openat64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(openat)]
[requires(defined(__CRT_HAVE_openat64))]
[dependency_include(<bits/fcntl.h>)]
[decl_include(<bits/types.h>)]
openat:($fd_t dirfd, [nonnull] char const *filename, $oflag_t oflags, ...) -> $fd_t {
	$fd_t result;
	va_list args;
	va_start(args, oflags);
	result = openat64(dirfd, filename, oflags, va_arg(args, mode_t));
	va_end(args);
	return result;
}
%#ifdef __USE_LARGEFILE64
[cp][guard][noexport][vartypes($mode_t)][ATTR_WUNUSED]
[largefile64_variant_of(openat)]
[requires(defined(__CRT_HAVE_openat))]
[decl_include(<bits/types.h>)]
openat64:($fd_t dirfd, [nonnull] char const *filename, $oflag_t oflags, ...) -> $fd_t {
	$fd_t result;
	va_list args;
	va_start(args, oflags);
#ifdef @__O_LARGEFILE@
	result = openat32(dirfd, filename, oflags|@__O_LARGEFILE@, va_arg(args, mode_t));
#else
	result = openat32(dirfd, filename, oflags, va_arg(args, mode_t));
#endif
	va_end(args);
	return result;
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_ATFILE */
%
%#ifdef __USE_XOPEN2K

[ignore][decl_include(<bits/types.h>)][section(.text.crt.io.utility)]
posix_fadvise32:($fd_t fd, $off32_t offset, $off32_t length, int advise) -> int = posix_fadvise?;

[noexport]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(posix_fadvise64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(posix_fadvise)]
[alias_args(posix_fadvise64:($fd_t fd, $off64_t offset, $off64_t length, int advise) -> int)]
[alias_args(posix_fadvise:($fd_t fd, $off32_t offset, $off32_t length, int advise) -> int)]
[decl_include(<bits/types.h>)][section(.text.crt.io.utility)]
posix_fadvise:($fd_t fd, $off_t offset, $off_t length, int advise) -> int {
#ifdef __CRT_HAVE_posix_fadvise64
	return posix_fadvise64(fd, ($off64_t)offset, ($off64_t)length, advise);
#elif defined(__CRT_HAVE_posix_fadvise)
	return posix_fadvise32(fd, ($off32_t)offset, ($off32_t)length, advise);
#else /* __CRT_HAVE_posix_fadvise64 */
	(void)fd;
	(void)offset;
	(void)length;
	(void)advise;
	return 0;
#endif /* !__CRT_HAVE_posix_fadvise64 */
}

[ignore]
[decl_include(<bits/types.h>)][section(.text.crt.io.utility)]
posix_fallocate32:($fd_t fd, $off32_t offset, $off32_t length) -> int = posix_fallocate?;

[noexport]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(posix_fallocate64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(posix_fallocate)]
[alias_args(posix_fallocate64:($fd_t fd, $off64_t offset, $off64_t length) -> int)]
[alias_args(posix_fallocate:($fd_t fd, $off32_t offset, $off32_t length) -> int)]
[decl_include(<bits/types.h>)][section(.text.crt.io.utility)]
posix_fallocate:($fd_t fd, $off_t offset, $off_t length) -> int {
#ifdef __CRT_HAVE_posix_fallocate64
	return posix_fallocate64(fd, ($off64_t)offset, ($off64_t)length);
#elif defined(__CRT_HAVE_posix_fallocate)
	return posix_fallocate32(fd, ($off32_t)offset, ($off32_t)length);
#else /* __CRT_HAVE_posix_fallocate64 */
	(void)fd;
	(void)offset;
	(void)length;
	return 0;
#endif /* !__CRT_HAVE_posix_fallocate64 */
}

%#ifdef __USE_LARGEFILE64
[noexport][off64_variant_of(posix_fadvise)]
[decl_include(<bits/types.h>)][section(.text.crt.io.large.utility)]
posix_fadvise64:($fd_t fd, $off64_t offset, $off64_t length, int advise) -> int {
#ifdef __CRT_HAVE_posix_fadvise
	return posix_fadvise32(fd, ($off32_t)offset, ($off32_t)length, advise);
#else /* __CRT_HAVE_posix_fadvise */
	(void)fd;
	(void)offset;
	(void)length;
	(void)advise;
	return 0;
#endif /* !__CRT_HAVE_posix_fadvise */
}

[noexport][off64_variant_of(posix_fallocate)]
[decl_include(<bits/types.h>)][section(.text.crt.io.large.utility)]
posix_fallocate64:($fd_t fd, $off64_t offset, $off64_t length) -> int {
#ifdef __CRT_HAVE_posix_fallocate
	return posix_fallocate32(fd, ($off32_t)offset, ($off32_t)length);
#else /* __CRT_HAVE_posix_fallocate */
	(void)fd;
	(void)offset;
	(void)length;
	return 0;
#endif /* !__CRT_HAVE_posix_fallocate */
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

[cp][ignore][alias(locking)][decl_include(<bits/types.h>)][section(.text.crt.dos.io.lock)]
crt_locking:($fd_t fd, int cmd, $off32_t length) -> int = _locking?;
[cp][ignore][decl_include(<bits/types.h>)][section(.text.crt.dos.io.lock)]
lockf32:($fd_t fd, int cmd, $off32_t length) -> int = lockf?;

[cp][guard][noexport][alternate_names(_locking, locking)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(lockf64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(lockf, _locking, locking)]
[alias_args(lockf64:($fd_t fd, int cmd, $off64_t length) -> int)]
[alias_args(lockf:($fd_t fd, int cmd, $off32_t length) -> int)]
[requires(defined(__CRT_HAVE_lockf64) || defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE__locking) || defined(__CRT_HAVE_locking))]
[decl_include(<bits/types.h>)][section(.text.crt.io.lock)]
lockf:($fd_t fd, int cmd, $off_t length) -> int {
#ifdef __CRT_HAVE_lockf64
	return lockf64(fd, cmd, (__off64_t)length);
#elif defined(__CRT_HAVE_lockf)
	return lockf32(fd, cmd, (__off32_t)length);
#else /* __CRT_HAVE_lockf64 */
	return crt_locking(fd, cmd, (__off32_t)length);
#endif
}

%#ifdef __USE_LARGEFILE64
[cp][guard][noexport][off64_variant_of(lockf)]
[requires(defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE__locking) || defined(__CRT_HAVE_locking))]
[decl_include(<bits/types.h>)][section(.text.crt.io.large.lock)]
lockf64:($fd_t fd, int cmd, $off64_t length) -> int {
#ifdef __CRT_HAVE_lockf
	return lockf32(fd, cmd, ($off64_t)length);
#else /* __CRT_HAVE_lockf */
	return crt_locking(fd, cmd, ($off32_t)length);
#endif /* !__CRT_HAVE_lockf */
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_POSIX) */


%{

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_FCNTL_H)
#include <parts/uchar/fcntl.h>
#endif
#endif /* __USE_UTF */

}

