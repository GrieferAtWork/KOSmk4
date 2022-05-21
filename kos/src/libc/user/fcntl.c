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
#ifndef GUARD_LIBC_USER_FCNTL_C
#define GUARD_LIBC_USER_FCNTL_C 1

#include "../api.h"
#include "fcntl.h"

#include <sys/stat.h>
#include <kos/syscalls.h>
#include <stdarg.h>

DECL_BEGIN

#define DOS_O_APPEND     0x00008 /* Same as `O_APPEND' */
#define DOS_O_TEMPORARY  0x00040 /* Same as `O_TMPFILE' */
#define DOS_O_NOINHERIT  0x00080 /* Same as `O_CLOEXEC' */
#define DOS_O_CREAT      0x00100 /* Same as `O_CREAT' */
#define DOS_O_TRUNC      0x00200 /* Same as `O_TRUNC' */
#define DOS_O_EXCL       0x00400 /* Same as `O_EXCL' */
#define DOS_O_OBTAIN_DIR 0x02000 /* Similar to `O_DIRECTORY'  (while `O_DIRECTORY'  requires that  the
                                  * named file be a  directory, this flag will  _allow_ it to be  one)
                                  * However, when it comes to the use-cases, this flag usually ends up
                                  * being used in the same places. */


PRIVATE ATTR_SECTION(".text.crt.dos.io.access") oflag_t
NOTHROW(LIBCCALL oflag_dos2kos)(oflag_t dos_oflags) {
	oflag_t result;
	result = dos_oflags & (O_ACCMODE | O_TRUNC);
	if (dos_oflags & DOS_O_APPEND)
		result |= O_APPEND;
	if (dos_oflags & DOS_O_TEMPORARY)
		result |= O_TMPFILE;
	if (dos_oflags & DOS_O_NOINHERIT)
		result |= O_CLOEXEC;
	if (dos_oflags & DOS_O_CREAT)
		result |= O_CREAT;
	if (dos_oflags & DOS_O_TRUNC)
		result |= O_TRUNC;
	if (dos_oflags & DOS_O_EXCL)
		result |= O_EXCL;
#if 0 /* This flag ~allows~ the named file to be a  directory.
       * With this in mind, it still isn't required to be one,
       * so for full compatibility, we'll have to ensure  that
       * we _didn't_ open a  directory when this flag  _isn't_
       * given. */
	if (dos_oflags & DOS_O_OBTAIN_DIR)
		result |= O_DIRECTORY;
#endif
	result |= libd_O_DOSPATH;
	return result;
}




/*[[[head:libd_open,hash:CRC-32=0x8ac6bddf]]]*/
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.io.access") WUNUSED ATTR_ACCESS_RO(1) fd_t
NOTHROW_RPC(VLIBDCALL libd_open)(char const *filename,
                                 oflag_t oflags,
                                 ...)
/*[[[body:libd_open]]]*/
{
	fd_t result;
	oflag_t kos_oflags;
	va_list args;
	kos_oflags = oflag_dos2kos(oflags);
	va_start(args, oflags);
	result = libc_open(filename, kos_oflags, va_arg(args, mode_t));
	va_end(args);
	if unlikely(E_ISERR(result))
		return libc_seterrno_neg(result);
	if (!(oflags & DOS_O_OBTAIN_DIR)) {
		/* Make sure that the opened file isn't a directory. */
		struct stat st;
		if (E_ISOK(sys_kfstat(result, &st)) && S_ISDIR(st.st_mode)) {
			sys_close(result);
			return libc_seterrno(EISDIR);
		}
	}
	return result;
}
/*[[[end:libd_open]]]*/

/*[[[head:libc_open,hash:CRC-32=0x623e2432]]]*/
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
INTERN ATTR_SECTION(".text.crt.io.access") WUNUSED ATTR_ACCESS_RO(1) fd_t
NOTHROW_RPC(VLIBCCALL libc_open)(char const *filename,
                                 oflag_t oflags,
                                 ...)
/*[[[body:libc_open]]]*/
{
	fd_t result;
	va_list args;
	va_start(args, oflags);
#ifdef __NR_open
	result = sys_open(filename, oflags, va_arg(args, mode_t));
#else /* __NR_open */
	result = sys_openat(AT_FDCWD, filename, oflags, va_arg(args, mode_t));
#endif /* !__NR_open */
	va_end(args);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_open]]]*/

/*[[[head:libd_creat,hash:CRC-32=0xd6e92df4]]]*/
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.io.access") WUNUSED ATTR_ACCESS_RO(1) fd_t
NOTHROW_RPC(LIBDCALL libd_creat)(char const *filename,
                                 mode_t mode)
/*[[[body:libd_creat]]]*/
{
	return libd_open(filename, DOS_O_CREAT | O_WRONLY | DOS_O_TRUNC, mode);
}
/*[[[end:libd_creat]]]*/

/*[[[head:libc_creat,hash:CRC-32=0x3acf255e]]]*/
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
INTERN ATTR_SECTION(".text.crt.io.access") WUNUSED ATTR_ACCESS_RO(1) fd_t
NOTHROW_RPC(LIBCCALL libc_creat)(char const *filename,
                                 mode_t mode)
/*[[[body:libc_creat]]]*/
{
	fd_t result;
#ifdef __NR_creat
	result = sys_creat(filename, mode);
#else /* __NR_creat */
	result = sys_open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode);
#endif /* !__NR_creat */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_creat]]]*/

/*[[[head:libd_openat,hash:CRC-32=0xe5b0d17a]]]*/
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.io.access") WUNUSED ATTR_ACCESS_RO(2) fd_t
NOTHROW_RPC(VLIBDCALL libd_openat)(fd_t dirfd,
                                   char const *filename,
                                   oflag_t oflags,
                                   ...)
/*[[[body:libd_openat]]]*/
{
	fd_t result;
	oflag_t kos_oflags;
	va_list args;
	kos_oflags = oflag_dos2kos(oflags);
	va_start(args, oflags);
	result = libc_openat(dirfd, filename, kos_oflags, va_arg(args, mode_t));
	va_end(args);
	if (result >= 0 && !(oflags & DOS_O_OBTAIN_DIR)) {
		/* Make sure that the opened file isn't a directory. */
		struct stat st;
		if (E_ISOK(sys_kfstat(result, &st)) && S_ISDIR(st.st_mode)) {
			sys_close(result);
			return libc_seterrno(EISDIR);
		}
	}
	return result;
}
/*[[[end:libd_openat]]]*/

/*[[[head:libc_openat,hash:CRC-32=0x33a9c83e]]]*/
/* >> open(2), open64(2), openat(2), openat64(2)
 * Open  a  new  file  handle  to  the  file  specified  by `filename'
 * When  `oflags & O_CREAT',   then  `mode'   specifies  the   initial
 * file  access  permissions with  which  the file  should  be opened.
 * On KOS, the returned handle can be anything, but is usually one of:
 *   - HANDLE_TYPE_PATH:       When `O_PATH' was given
 *   - HANDLE_TYPE_FILEHANDLE: For `S_IFREG' regular files
 *   - HANDLE_TYPE_FIFOHANDLE: For `S_IFIFO' pipe files
 *   - HANDLE_TYPE_DIRHANDLE:  For `S_IFDIR' directories
 *   - HANDLE_TYPE_MFILE:      The actual filesystem object (including device files)
 *   - *:                      Certain filesystem names can literally return anything, such
 *                             as `/proc/self/fd/1234',  which  is  more  like  `dup(1234)' */
INTERN ATTR_SECTION(".text.crt.io.access") WUNUSED ATTR_ACCESS_RO(2) fd_t
NOTHROW_RPC(VLIBCCALL libc_openat)(fd_t dirfd,
                                   char const *filename,
                                   oflag_t oflags,
                                   ...)
/*[[[body:libc_openat]]]*/
{
	fd_t result;
	va_list args;
	va_start(args, oflags);
	result = sys_openat(dirfd, filename, oflags, va_arg(args, mode_t));
	va_end(args);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_openat]]]*/


DEFINE_INTERN_ALIAS(libc_open64, libc_open);
DEFINE_INTERN_ALIAS(libd_open64, libd_open);
DEFINE_INTERN_ALIAS(libc_creat64, libc_creat);
DEFINE_INTERN_ALIAS(libd_creat64, libd_creat);
DEFINE_INTERN_ALIAS(libc_openat64, libc_openat);
DEFINE_INTERN_ALIAS(libd_openat64, libd_openat);
/*[[[impl:libd_open64]]]*/
/*[[[impl:libc_open64]]]*/
/*[[[impl:libd_creat64]]]*/
/*[[[impl:libc_creat64]]]*/
/*[[[impl:libd_openat64]]]*/
/*[[[impl:libc_openat64]]]*/




/*[[[head:libc_readahead,hash:CRC-32=0x8181d1ce]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ssize_t
NOTHROW_NCX(LIBCCALL libc_readahead)(fd_t fd,
                                     __PIO_OFFSET64 offset,
                                     size_t count)
/*[[[body:libc_readahead]]]*/
{
	ssize_t result;
	result = sys_readahead(fd, offset, count);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_readahead]]]*/

/*[[[head:libc_sync_file_range,hash:CRC-32=0xc18c119a]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") int
NOTHROW_NCX(LIBCCALL libc_sync_file_range)(fd_t fd,
                                           __PIO_OFFSET64 offset,
                                           __PIO_OFFSET64 count,
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

/*[[[head:libc_splice,hash:CRC-32=0xa0e243bd]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_ACCESS_RW(2) ATTR_ACCESS_RW(4) ssize_t
NOTHROW_RPC(LIBCCALL libc_splice)(fd_t fdin,
                                  __PIO_OFFSET64 *offin,
                                  fd_t fdout,
                                  __PIO_OFFSET64 *offout,
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
	result = sys_tee(fdin, fdout, length, (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_tee]]]*/

/*[[[head:libc_name_to_handle_at,hash:CRC-32=0xd2a3af00]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_ACCESS_WR(3) int
NOTHROW_RPC(LIBCCALL libc_name_to_handle_at)(fd_t dirfd,
                                             char const *name,
                                             struct file_handle *handle,
                                             int *mnt_id,
                                             int flags)
/*[[[body:libc_name_to_handle_at]]]*/
{
	errno_t result;
	result = sys_name_to_handle_at(dirfd, name, handle, mnt_id,
	                               (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_name_to_handle_at]]]*/

/*[[[head:libc_open_by_handle_at,hash:CRC-32=0x5019cf78]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_ACCESS_RO(2) fd_t
NOTHROW_RPC(LIBCCALL libc_open_by_handle_at)(fd_t mountdirfd,
                                             struct file_handle *handle,
                                             int flags)
/*[[[body:libc_open_by_handle_at]]]*/
{
	fd_t result;
	result = sys_open_by_handle_at(mountdirfd, handle,
	                               (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_open_by_handle_at]]]*/

/*[[[head:libc_fallocate,hash:CRC-32=0x126a7d9c]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") int
NOTHROW_NCX(LIBCCALL libc_fallocate)(fd_t fd,
                                     __STDC_INT_AS_UINT_T mode,
                                     __PIO_OFFSET offset,
                                     __PIO_OFFSET length)
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

/*[[[head:libc_fallocate64,hash:CRC-32=0xa250b385]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fallocate64, libc_fallocate);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.utility") int
NOTHROW_NCX(LIBCCALL libc_fallocate64)(fd_t fd,
                                       __STDC_INT_AS_UINT_T mode,
                                       __PIO_OFFSET64 offset,
                                       __PIO_OFFSET64 length)
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


/*[[[head:libc_fcntl,hash:CRC-32=0x57021137]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc_fcntl)(fd_t fd,
                                  fcntl_t cmd,
                                  ...)
/*[[[body:libc_fcntl]]]*/
{
	syscall_slong_t result;
	va_list args;
	va_start(args, cmd);
	result = sys_fcntl(fd, (syscall_ulong_t)cmd, va_arg(args, void *));
	va_end(args);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_fcntl]]]*/

/*[[[head:libc_posix_fadvise,hash:CRC-32=0x5865caf1]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") int
NOTHROW_NCX(LIBCCALL libc_posix_fadvise)(fd_t fd,
                                         __PIO_OFFSET offset,
                                         __PIO_OFFSET length,
                                         __STDC_INT_AS_UINT_T advise)
/*[[[body:libc_posix_fadvise]]]*/
{
	return libc_posix_fadvise64(fd, (off64_t)offset, (off64_t)length, advise);
}
/*[[[end:libc_posix_fadvise]]]*/

/*[[[head:libc_posix_fallocate,hash:CRC-32=0x698a865b]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") int
NOTHROW_NCX(LIBCCALL libc_posix_fallocate)(fd_t fd,
                                           __PIO_OFFSET offset,
                                           __PIO_OFFSET length)
/*[[[body:libc_posix_fallocate]]]*/
{
	return libc_posix_fallocate64(fd, (off64_t)offset, (off64_t)length);
}
/*[[[end:libc_posix_fallocate]]]*/

/*[[[head:libc_posix_fadvise64,hash:CRC-32=0x7405081a]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_posix_fadvise64, libc_posix_fadvise);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.large.utility") int
NOTHROW_NCX(LIBCCALL libc_posix_fadvise64)(fd_t fd,
                                           __PIO_OFFSET64 offset,
                                           __PIO_OFFSET64 length,
                                           __STDC_INT_AS_UINT_T advise)
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

/*[[[head:libc_posix_fallocate64,hash:CRC-32=0xdb734687]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_posix_fallocate64, libc_posix_fallocate);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.large.utility") int
NOTHROW_NCX(LIBCCALL libc_posix_fallocate64)(fd_t fd,
                                             __PIO_OFFSET64 offset,
                                             __PIO_OFFSET64 length)
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

/*[[[head:libc_lockf,hash:CRC-32=0x3f461c5c]]]*/
INTERN ATTR_SECTION(".text.crt.io.lock") int
NOTHROW_RPC(LIBCCALL libc_lockf)(fd_t fd,
                                 __STDC_INT_AS_UINT_T cmd,
                                 __PIO_OFFSET length)
/*[[[body:libc_lockf]]]*/
{
	return libc_lockf64(fd, cmd, (off64_t)length);
}
/*[[[end:libc_lockf]]]*/

/*[[[head:libc_lockf64,hash:CRC-32=0x9b6406bb]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_lockf64, libc_lockf);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.large.lock") int
NOTHROW_RPC(LIBCCALL libc_lockf64)(fd_t fd,
                                   __STDC_INT_AS_UINT_T cmd,
                                   __PIO_OFFSET64 length)
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





/*[[[start:exports,hash:CRC-32=0x8fdb371b]]]*/
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
DEFINE_PUBLIC_ALIAS(__libc_fcntl, libc_fcntl);
DEFINE_PUBLIC_ALIAS(fcntl, libc_fcntl);
DEFINE_PUBLIC_ALIAS(DOS$__open, libd_open);
DEFINE_PUBLIC_ALIAS(DOS$__libc_open, libd_open);
DEFINE_PUBLIC_ALIAS(DOS$_open, libd_open);
DEFINE_PUBLIC_ALIAS("?_open@@YAHPBDHH@Z", libd_open);
DEFINE_PUBLIC_ALIAS(DOS$open, libd_open);
DEFINE_PUBLIC_ALIAS(__open, libc_open);
DEFINE_PUBLIC_ALIAS(__libc_open, libc_open);
DEFINE_PUBLIC_ALIAS(open, libc_open);
DEFINE_PUBLIC_ALIAS(DOS$_creat, libd_creat);
DEFINE_PUBLIC_ALIAS(DOS$__creat, libd_creat);
DEFINE_PUBLIC_ALIAS(DOS$__libc_creat, libd_creat);
DEFINE_PUBLIC_ALIAS(DOS$creat, libd_creat);
DEFINE_PUBLIC_ALIAS(__creat, libc_creat);
DEFINE_PUBLIC_ALIAS(__libc_creat, libc_creat);
DEFINE_PUBLIC_ALIAS(creat, libc_creat);
DEFINE_PUBLIC_ALIAS(DOS$__open64, libd_open64);
DEFINE_PUBLIC_ALIAS(DOS$open64, libd_open64);
DEFINE_PUBLIC_ALIAS(__open64, libc_open64);
DEFINE_PUBLIC_ALIAS(open64, libc_open64);
DEFINE_PUBLIC_ALIAS(DOS$creat64, libd_creat64);
DEFINE_PUBLIC_ALIAS(creat64, libc_creat64);
DEFINE_PUBLIC_ALIAS(DOS$openat, libd_openat);
DEFINE_PUBLIC_ALIAS(openat, libc_openat);
DEFINE_PUBLIC_ALIAS(DOS$openat64, libd_openat64);
DEFINE_PUBLIC_ALIAS(openat64, libc_openat64);
DEFINE_PUBLIC_ALIAS(posix_fadvise, libc_posix_fadvise);
DEFINE_PUBLIC_ALIAS(posix_fallocate, libc_posix_fallocate);
DEFINE_PUBLIC_ALIAS(posix_fadvise64, libc_posix_fadvise64);
DEFINE_PUBLIC_ALIAS(posix_fallocate64, libc_posix_fallocate64);
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(_locking, libc_lockf);
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(lockf, libc_lockf);
DEFINE_PUBLIC_ALIAS(lockf64, libc_lockf64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_FCNTL_C */
