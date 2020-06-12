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
#ifndef GUARD_LIBC_USER_FCNTL_C
#define GUARD_LIBC_USER_FCNTL_C 1

#include "../api.h"
#include "fcntl.h"

#include <sys/stat.h>
#include <kos/syscalls.h>
#include <stdarg.h>

DECL_BEGIN


PRIVATE ATTR_SECTION(".text.crt.dos.io.access.oflag_dos2kos")
oflag_t NOTHROW(LIBCCALL oflag_dos2kos)(oflag_t dos_oflags) {
	oflag_t result;
	result = dos_oflags & (O_ACCMODE | O_TRUNC);
	if (dos_oflags & __DOS_O_APPEND)
		result |= O_APPEND;
	if (dos_oflags & __DOS_O_TEMPORARY)
		result |= O_TMPFILE;
	if (dos_oflags & __DOS_O_NOINHERIT)
		result |= O_CLOEXEC;
	if (dos_oflags & __DOS_O_CREAT)
		result |= O_CREAT;
	if (dos_oflags & __DOS_O_TRUNC)
		result |= O_TRUNC;
	if (dos_oflags & __DOS_O_EXCL)
		result |= O_EXCL;
#if 0 /* This flag ~allows~ the named file to be a directory.
       * With this in mind, it still isn't required to be one,
       * so for full compatibility, we'll have to ensure that
       * we _didn't_ open a directory when this flag _isn't_
       * given.  */
	if (dos_oflags & __DOS_O_OBTAIN_DIR)
		result |= O_DIRECTORY;
#endif
	return result;
}


DEFINE_PUBLIC_ALIAS(DOS$open, libd_open);
DEFINE_PUBLIC_ALIAS(DOS$_open, libd_open);
INTERN WUNUSED NONNULL((1))
ATTR_SECTION(".text.crt.dos.io.access.open") fd_t
NOTHROW_RPC(VLIBDCALL libd_open)(char const *filename, oflag_t oflags, ...) {
	fd_t result;
	oflag_t kos_oflags;
	va_list args;
	kos_oflags = oflag_dos2kos(oflags);
	va_start(args, oflags);
#ifdef __NR_open
	result = sys_open(filename,
	                  kos_oflags,
	                  va_arg(args, mode_t));
#else /* __NR_open */
	result = sys_openat(AT_FDCWD,
	                    filename,
	                    kos_oflags,
	                    va_arg(args, mode_t));
#endif /* !__NR_open */
	va_end(args);
	if unlikely(E_ISERR(result)) {
		libc_seterrno(-result);
		return -1;
	}
	if (!(oflags & __DOS_O_OBTAIN_DIR)) {
		/* Make sure that the opened file isn't a directory. */
		struct stat st;
		if (E_ISOK(sys_kfstat(result, &st)) && S_ISDIR(st.st_mode)) {
			sys_close(result);
			libc_seterrno(EISDIR);
			return -1;
		}
	}
	return result;
}


DEFINE_PUBLIC_ALIAS(DOS$creat, libd_creat);
DEFINE_PUBLIC_ALIAS(DOS$_creat, libd_creat);
INTERN WUNUSED NONNULL((1))
ATTR_SECTION(".text.crt.dos.io.access.creat") fd_t
NOTHROW_RPC(LIBDCALL libd_creat)(char const *filename, mode_t mode){
	return libd_open(filename,
	                 __DOS_O_CREAT | O_WRONLY | __DOS_O_TRUNC,
	                 mode);
}




/*[[[start:implementation]]]*/

/*[[[head:libc_open,hash:CRC-32=0xba1315d6]]]*/
INTERN ATTR_SECTION(".text.crt.io.access") WUNUSED NONNULL((1)) fd_t
NOTHROW_RPC(VLIBCCALL libc_open)(char const *filename,
                                 oflag_t oflags,
                                 ...)
/*[[[body:libc_open]]]*/
{
	fd_t result;
	va_list args;
	va_start(args, oflags);
#ifdef __NR_open
	result = sys_open(filename,
	                  oflags,
	                  va_arg(args, mode_t));
#else /* __NR_open */
	result = sys_openat(AT_FDCWD,
	                    filename,
	                    oflags,
	                    va_arg(args, mode_t));
#endif /* !__NR_open */
	va_end(args);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_open]]]*/

/*[[[head:libc_creat,hash:CRC-32=0xaaefe2d]]]*/
INTERN ATTR_SECTION(".text.crt.io.access") WUNUSED NONNULL((1)) fd_t
NOTHROW_RPC(LIBCCALL libc_creat)(char const *filename,
                                 mode_t mode)
/*[[[body:libc_creat]]]*/
{
	fd_t result;
#ifdef __NR_creat
	result = sys_creat(filename, mode);
#else /* __NR_creat */
	result = sys_open(filename,
	                  O_CREAT | O_WRONLY | O_TRUNC,
	                  mode);
#endif /* !__NR_creat */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_creat]]]*/

/*[[[head:libc_openat,hash:CRC-32=0x3cf66674]]]*/
INTERN ATTR_SECTION(".text.crt.io.access") WUNUSED NONNULL((2)) fd_t
NOTHROW_RPC(VLIBCCALL libc_openat)(fd_t dirfd,
                                   char const *filename,
                                   oflag_t oflags,
                                   ...)
/*[[[body:libc_openat]]]*/
{
	fd_t result;
	va_list args;
	va_start(args, oflags);
	result = sys_openat(dirfd,
	                    filename,
	                    oflags,
	                    va_arg(args, mode_t));
	va_end(args);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_openat]]]*/


DEFINE_INTERN_ALIAS(libc_open64, libc_open);
DEFINE_INTERN_ALIAS(libc_creat64, libc_creat);
DEFINE_INTERN_ALIAS(libc_openat64, libc_openat);
/*[[[impl:libc_open64]]]*/
/*[[[impl:libc_creat64]]]*/
/*[[[impl:libc_openat64]]]*/



/*[[[head:libc_readahead,hash:CRC-32=0xb9ac1666]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ssize_t
NOTHROW_NCX(LIBCCALL libc_readahead)(fd_t fd,
                                     off64_t offset,
                                     size_t count)
/*[[[body:libc_readahead]]]*/
{
	ssize_t result;
	result = sys_readahead(fd, offset, count);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_readahead]]]*/

/*[[[head:libc_sync_file_range,hash:CRC-32=0x42c546a0]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") int
NOTHROW_NCX(LIBCCALL libc_sync_file_range)(fd_t fd,
                                           off64_t offset,
                                           off64_t count,
                                           unsigned int flags)
/*[[[body:libc_sync_file_range]]]*/
{
	errno_t result;
	result = sys_sync_file_range(fd,
	                             offset,
	                             count,
	                             (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sync_file_range]]]*/

/*[[[head:libc_vmsplice,hash:CRC-32=0x2d137f1e]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ssize_t
NOTHROW_RPC(LIBCCALL libc_vmsplice)(fd_t fdout,
                                    struct iovec const *iov,
                                    size_t count,
                                    unsigned int flags)
/*[[[body:libc_vmsplice]]]*/
{
	ssize_t result;
	result = sys_vmsplice(fdout, iov, count, (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_vmsplice]]]*/

/*[[[head:libc_splice,hash:CRC-32=0x4f6c19da]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ssize_t
NOTHROW_RPC(LIBCCALL libc_splice)(fd_t fdin,
                                  off64_t *offin,
                                  fd_t fdout,
                                  off64_t *offout,
                                  size_t length,
                                  unsigned int flags)
/*[[[body:libc_splice]]]*/
{
	ssize_t result;
	result = sys_splice(fdin,
	                    (uint64_t *)offin,
	                    fdout,
	                    (uint64_t *)offout,
	                    length,
	                    (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_splice]]]*/

/*[[[head:libc_tee,hash:CRC-32=0x92f24953]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ssize_t
NOTHROW_RPC(LIBCCALL libc_tee)(fd_t fdin,
                               fd_t fdout,
                               size_t length,
                               unsigned int flags)
/*[[[body:libc_tee]]]*/
{
	ssize_t result;
	result = sys_tee(fdin,
	                 fdout,
	                 length,
	                 (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_tee]]]*/

/*[[[head:libc_name_to_handle_at,hash:CRC-32=0x8e5aca4f]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") int
NOTHROW_RPC(LIBCCALL libc_name_to_handle_at)(fd_t dirfd,
                                             char const *name,
                                             struct file_handle *handle,
                                             int *mnt_id,
                                             int flags)
/*[[[body:libc_name_to_handle_at]]]*/
{
	errno_t result;
	result = sys_name_to_handle_at(dirfd,
	                               name,
	                               handle,
	                               mnt_id,
	                               (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_name_to_handle_at]]]*/

/*[[[head:libc_open_by_handle_at,hash:CRC-32=0x3524d10]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") fd_t
NOTHROW_RPC(LIBCCALL libc_open_by_handle_at)(fd_t mountdirfd,
                                             struct file_handle *handle,
                                             int flags)
/*[[[body:libc_open_by_handle_at]]]*/
{
	fd_t result;
	result = sys_open_by_handle_at(mountdirfd,
	                               handle,
	                               (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_open_by_handle_at]]]*/

/*[[[head:libc_fallocate,hash:CRC-32=0xb1b8db98]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") int
NOTHROW_NCX(LIBCCALL libc_fallocate)(fd_t fd,
                                     int mode,
                                     off_t offset,
                                     off_t length)
/*[[[body:libc_fallocate]]]*/
{
	errno_t result;
	result = sys_fallocate(fd,
	                       (syscall_ulong_t)mode,
	                       (uint32_t)offset,
	                       (uint32_t)length);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fallocate]]]*/

/*[[[head:libc_fallocate64,hash:CRC-32=0x24d8e4a1]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fallocate64, libc_fallocate);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.utility") int
NOTHROW_NCX(LIBCCALL libc_fallocate64)(fd_t fd,
                                       int mode,
                                       off64_t offset,
                                       off64_t length)
/*[[[body:libc_fallocate64]]]*/
{
	errno_t result;
	result = sys_fallocate64(fd,
	                         (syscall_ulong_t)mode,
	                         (uint64_t)offset,
	                         (uint64_t)length);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_fallocate64]]]*/

/*[[[head:libc_fcntl,hash:CRC-32=0x9ee9436b]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc_fcntl)(fd_t fd,
                                  int cmd,
                                  ...)
/*[[[body:libc_fcntl]]]*/
{
	syscall_slong_t result;
	va_list args;
	va_start(args, cmd);
	result = sys_fcntl(fd,
	                   (syscall_ulong_t)cmd,
	                   va_arg(args, void *));
	va_end(args);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fcntl]]]*/

/*[[[head:libc_posix_fadvise,hash:CRC-32=0xdc94db4e]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") int
NOTHROW_NCX(LIBCCALL libc_posix_fadvise)(fd_t fd,
                                         off_t offset,
                                         off_t length,
                                         int advise)
/*[[[body:libc_posix_fadvise]]]*/
{
	return libc_posix_fadvise64(fd,
	                            (off64_t)offset,
	                            (off64_t)length,
	                            advise);
}
/*[[[end:libc_posix_fadvise]]]*/

/*[[[head:libc_posix_fallocate,hash:CRC-32=0xa96cf38]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") int
NOTHROW_NCX(LIBCCALL libc_posix_fallocate)(fd_t fd,
                                           off_t offset,
                                           off_t length)
/*[[[body:libc_posix_fallocate]]]*/
{
	return libc_posix_fallocate64(fd,
	                              (off64_t)offset,
	                              (off64_t)length);
}
/*[[[end:libc_posix_fallocate]]]*/

/*[[[head:libc_posix_fadvise64,hash:CRC-32=0x2819d435]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_posix_fadvise64, libc_posix_fadvise);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.large.utility") int
NOTHROW_NCX(LIBCCALL libc_posix_fadvise64)(fd_t fd,
                                           off64_t offset,
                                           off64_t length,
                                           int advise)
/*[[[body:libc_posix_fadvise64]]]*/
{
	(void)fd;
	(void)offset;
	(void)length;
	(void)advise;
	CRT_UNIMPLEMENTED("posix_fadvise64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:libc_posix_fadvise64]]]*/

/*[[[head:libc_posix_fallocate64,hash:CRC-32=0xf4ed2e86]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_posix_fallocate64, libc_posix_fallocate);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.large.utility") int
NOTHROW_NCX(LIBCCALL libc_posix_fallocate64)(fd_t fd,
                                             off64_t offset,
                                             off64_t length)
/*[[[body:libc_posix_fallocate64]]]*/
{
	(void)fd;
	(void)offset;
	(void)length;
	CRT_UNIMPLEMENTED("posix_fallocate64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:libc_posix_fallocate64]]]*/

/*[[[head:libc_lockf,hash:CRC-32=0xd233a69d]]]*/
INTERN ATTR_SECTION(".text.crt.io.lock") int
NOTHROW_RPC(LIBCCALL libc_lockf)(fd_t fd,
                                 int cmd,
                                 off_t length)
/*[[[body:libc_lockf]]]*/
{
	return libc_lockf64(fd, cmd, (off64_t)length);
}
/*[[[end:libc_lockf]]]*/

/*[[[head:libc_lockf64,hash:CRC-32=0xcf2acb7e]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_lockf64, libc_lockf);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.large.lock") int
NOTHROW_RPC(LIBCCALL libc_lockf64)(fd_t fd,
                                   int cmd,
                                   off64_t length)
/*[[[body:libc_lockf64]]]*/
{
	(void)fd;
	(void)cmd;
	(void)length;
	CRT_UNIMPLEMENTED("lockf64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:libc_lockf64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xe25f67f1]]]*/
DEFINE_PUBLIC_ALIAS(readahead, libc_readahead);
DEFINE_PUBLIC_ALIAS(sync_file_range, libc_sync_file_range);
DEFINE_PUBLIC_ALIAS(vmsplice, libc_vmsplice);
DEFINE_PUBLIC_ALIAS(splice, libc_splice);
DEFINE_PUBLIC_ALIAS(tee, libc_tee);
DEFINE_PUBLIC_ALIAS(name_to_handle_at, libc_name_to_handle_at);
DEFINE_PUBLIC_ALIAS(open_by_handle_at, libc_open_by_handle_at);
DEFINE_PUBLIC_ALIAS(fallocate, libc_fallocate);
DEFINE_PUBLIC_ALIAS(fallocate64, libc_fallocate64);
DEFINE_PUBLIC_ALIAS(__fcntl, libc_fcntl);
DEFINE_PUBLIC_ALIAS(fcntl, libc_fcntl);
DEFINE_PUBLIC_ALIAS(__open, libc_open);
DEFINE_PUBLIC_ALIAS(open, libc_open);
DEFINE_PUBLIC_ALIAS(creat, libc_creat);
DEFINE_PUBLIC_ALIAS(__open64, libc_open64);
DEFINE_PUBLIC_ALIAS(open64, libc_open64);
DEFINE_PUBLIC_ALIAS(creat64, libc_creat64);
DEFINE_PUBLIC_ALIAS(openat, libc_openat);
DEFINE_PUBLIC_ALIAS(openat64, libc_openat64);
DEFINE_PUBLIC_ALIAS(posix_fadvise, libc_posix_fadvise);
DEFINE_PUBLIC_ALIAS(posix_fallocate, libc_posix_fallocate);
DEFINE_PUBLIC_ALIAS(posix_fadvise64, libc_posix_fadvise64);
DEFINE_PUBLIC_ALIAS(posix_fallocate64, libc_posix_fallocate64);
DEFINE_PUBLIC_ALIAS(_locking, libc_lockf);
DEFINE_PUBLIC_ALIAS(locking, libc_lockf);
DEFINE_PUBLIC_ALIAS(lockf, libc_lockf);
DEFINE_PUBLIC_ALIAS(lockf64, libc_lockf64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_FCNTL_C */
