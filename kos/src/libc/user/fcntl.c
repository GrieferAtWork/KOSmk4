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
#ifndef GUARD_LIBC_USER_FCNTL_C
#define GUARD_LIBC_USER_FCNTL_C 1

#include "../api.h"
/**/

#include "fcntl.h"
/**/

#include <sys/stat.h>

#include <stdarg.h>

#include "../libc/syscalls.h"

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




/*[[[head:libd_open,hash:CRC-32=0x479dfc4b]]]*/
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.io.access") WUNUSED ATTR_IN(1) fd_t
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
			(void)sys_close(result);
			return libc_seterrno(EISDIR);
		}
	}
	return result;
}
/*[[[end:libd_open]]]*/

/*[[[head:libc_open,hash:CRC-32=0x74e61786]]]*/
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
INTERN ATTR_SECTION(".text.crt.io.access") WUNUSED ATTR_IN(1) fd_t
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

/*[[[head:libd_creat,hash:CRC-32=0xe4db7b86]]]*/
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.io.access") WUNUSED ATTR_IN(1) fd_t
NOTHROW_RPC(LIBDCALL libd_creat)(char const *filename,
                                 mode_t mode)
/*[[[body:libd_creat]]]*/
{
	return libd_open(filename, DOS_O_CREAT | O_WRONLY | DOS_O_TRUNC, mode);
}
/*[[[end:libd_creat]]]*/

/*[[[head:libc_creat,hash:CRC-32=0x66d7aff0]]]*/
/* >> creat(2), creat64(2)
 * Alias for `open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode)' */
INTERN ATTR_SECTION(".text.crt.io.access") WUNUSED ATTR_IN(1) fd_t
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

/*[[[head:libd_openat,hash:CRC-32=0x6daf104f]]]*/
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
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.io.access") WUNUSED ATTR_IN(2) fd_t
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
			(void)sys_close(result);
			return libc_seterrno(EISDIR);
		}
	}
	return result;
}
/*[[[end:libd_openat]]]*/

/*[[[head:libc_openat,hash:CRC-32=0xdf30d763]]]*/
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
INTERN ATTR_SECTION(".text.crt.io.access") WUNUSED ATTR_IN(2) fd_t
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




/*[[[head:libc_readahead,hash:CRC-32=0x10139077]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_FDREAD(1) ssize_t
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

/*[[[head:libc_sync_file_range,hash:CRC-32=0xfd59442]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_FDWRITE(1) int
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

/*[[[head:libc_vmsplice,hash:CRC-32=0xd66dc921]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_FDWRITE(1) ssize_t
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

/*[[[head:libc_splice,hash:CRC-32=0xe969bc22]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_FDREAD(1) ATTR_FDWRITE(3) ATTR_INOUT(2) ATTR_INOUT(4) ssize_t
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

/*[[[head:libc_tee,hash:CRC-32=0x50283e7c]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_FDREAD(1) ATTR_FDWRITE(2) ssize_t
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

/*[[[head:libc_name_to_handle_at,hash:CRC-32=0xcdb231e8]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_OUT(3) int
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

/*[[[head:libc_open_by_handle_at,hash:CRC-32=0x19c4a7d6]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_FDARG(1) ATTR_IN(2) fd_t
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

/*[[[head:libc_fallocate,hash:CRC-32=0xddbfcdf2]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_FDARG(1) int
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

/*[[[head:libc_fallocate64,hash:CRC-32=0x546d6f24]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_fallocate64, libc_fallocate);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_FDWRITE(1) int
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


/*[[[head:libc_fcntl,hash:CRC-32=0xeca6e4fc]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_FDARG(1) __STDC_INT_AS_SSIZE_T
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

/*[[[head:libc_posix_fadvise,hash:CRC-32=0x1bf4c09a]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_FDARG(1) int
NOTHROW_NCX(LIBCCALL libc_posix_fadvise)(fd_t fd,
                                         __PIO_OFFSET offset,
                                         __PIO_OFFSET length,
                                         __STDC_INT_AS_UINT_T advise)
/*[[[body:libc_posix_fadvise]]]*/
{
	return libc_posix_fadvise64(fd, (off64_t)offset, (off64_t)length, advise);
}
/*[[[end:libc_posix_fadvise]]]*/

/*[[[head:libc_posix_fallocate,hash:CRC-32=0x310d8b73]]]*/
INTERN ATTR_SECTION(".text.crt.io.utility") ATTR_FDARG(1) int
NOTHROW_NCX(LIBCCALL libc_posix_fallocate)(fd_t fd,
                                           __PIO_OFFSET offset,
                                           __PIO_OFFSET length)
/*[[[body:libc_posix_fallocate]]]*/
{
	return libc_posix_fallocate64(fd, (off64_t)offset, (off64_t)length);
}
/*[[[end:libc_posix_fallocate]]]*/

/*[[[head:libc_posix_fadvise64,hash:CRC-32=0x6fe417cc]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_posix_fadvise64, libc_posix_fadvise);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.large.utility") ATTR_FDARG(1) int
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

/*[[[head:libc_posix_fallocate64,hash:CRC-32=0x9b47bc34]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_posix_fallocate64, libc_posix_fallocate);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.large.utility") ATTR_FDARG(1) int
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

/*[[[head:libc_lockf,hash:CRC-32=0xc3b090cd]]]*/
INTERN ATTR_SECTION(".text.crt.io.lock") ATTR_FDARG(1) int
NOTHROW_RPC(LIBCCALL libc_lockf)(fd_t fd,
                                 __STDC_INT_AS_UINT_T cmd,
                                 __PIO_OFFSET length)
/*[[[body:libc_lockf]]]*/
{
	return libc_lockf64(fd, cmd, (off64_t)length);
}
/*[[[end:libc_lockf]]]*/

/*[[[head:libc_lockf64,hash:CRC-32=0x3214e4c0]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_lockf64, libc_lockf);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.io.large.lock") ATTR_FDARG(1) int
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





/*[[[start:exports,hash:CRC-32=0x5e88c849]]]*/
DEFINE_PUBLIC_ALIAS_P(readahead,libc_readahead,ATTR_FDREAD(1),ssize_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, __PIO_OFFSET64 offset, size_t count),(fd,offset,count));
DEFINE_PUBLIC_ALIAS_P(sync_file_range,libc_sync_file_range,ATTR_FDWRITE(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __PIO_OFFSET64 offset, __PIO_OFFSET64 count, unsigned int flags),(fd,offset,count,flags));
DEFINE_PUBLIC_ALIAS_P(vmsplice,libc_vmsplice,ATTR_FDWRITE(1),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fdout, struct iovec const *iov, size_t count, unsigned int flags),(fdout,iov,count,flags));
DEFINE_PUBLIC_ALIAS_P(splice,libc_splice,ATTR_FDREAD(1) ATTR_FDWRITE(3) ATTR_INOUT(2) ATTR_INOUT(4),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fdin, __PIO_OFFSET64 *offin, fd_t fdout, __PIO_OFFSET64 *offout, size_t length, unsigned int flags),(fdin,offin,fdout,offout,length,flags));
DEFINE_PUBLIC_ALIAS_P(tee,libc_tee,ATTR_FDREAD(1) ATTR_FDWRITE(2),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fdin, fd_t fdout, size_t length, unsigned int flags),(fdin,fdout,length,flags));
DEFINE_PUBLIC_ALIAS_P(name_to_handle_at,libc_name_to_handle_at,ATTR_OUT(3),int,NOTHROW_RPC,LIBCCALL,(fd_t dirfd, char const *name, struct file_handle *handle, int *mnt_id, int flags),(dirfd,name,handle,mnt_id,flags));
DEFINE_PUBLIC_ALIAS_P(open_by_handle_at,libc_open_by_handle_at,ATTR_FDARG(1) ATTR_IN(2),fd_t,NOTHROW_RPC,LIBCCALL,(fd_t mountdirfd, struct file_handle *handle, int flags),(mountdirfd,handle,flags));
DEFINE_PUBLIC_ALIAS_P(fallocate,libc_fallocate,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __STDC_INT_AS_UINT_T mode, __PIO_OFFSET offset, __PIO_OFFSET length),(fd,mode,offset,length));
DEFINE_PUBLIC_ALIAS_P(fallocate64,libc_fallocate64,ATTR_FDWRITE(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __STDC_INT_AS_UINT_T mode, __PIO_OFFSET64 offset, __PIO_OFFSET64 length),(fd,mode,offset,length));
DEFINE_PUBLIC_ALIAS_P(__fcntl,libc_fcntl,ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(fd_t fd, fcntl_t cmd, ...),(fd,cmd,));
DEFINE_PUBLIC_ALIAS_P(__libc_fcntl,libc_fcntl,ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(fd_t fd, fcntl_t cmd, ...),(fd,cmd,));
DEFINE_PUBLIC_ALIAS_P(fcntl,libc_fcntl,ATTR_FDARG(1),__STDC_INT_AS_SSIZE_T,NOTHROW_NCX,VLIBCCALL,(fd_t fd, fcntl_t cmd, ...),(fd,cmd,));
DEFINE_PUBLIC_ALIAS_P(DOS$__open,libd_open,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBDCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_open,libd_open,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBDCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$__open_2,libd_open,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBDCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$_open,libd_open,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBDCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P("?_open@@YAHPBDHH@Z",libd_open,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBDCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_open,libd_open,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBDCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$open,libd_open,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBDCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(__open,libc_open,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBCCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(__libc_open,libc_open,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBCCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(__open_2,libc_open,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBCCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(__libc_open,libc_open,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBCCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(open,libc_open,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBCCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$_creat,libd_creat,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,LIBDCALL,(char const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$__creat,libd_creat,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,LIBDCALL,(char const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_creat,libd_creat,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,LIBDCALL,(char const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$creat,libd_creat,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,LIBDCALL,(char const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(__creat,libc_creat,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,LIBCCALL,(char const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(__libc_creat,libc_creat,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,LIBCCALL,(char const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(creat,libc_creat,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,LIBCCALL,(char const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$__open64,libd_open64,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBDCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$__open64_2,libd_open64,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBDCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$__libc_open64,libd_open64,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBDCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$open64,libd_open64,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBDCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(__open64,libc_open64,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBCCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(__open64_2,libc_open64,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBCCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(__libc_open64,libc_open64,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBCCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(open64,libc_open64,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,VLIBCCALL,(char const *filename, oflag_t oflags, ...),(filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$creat64,libd_creat64,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,LIBDCALL,(char const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(creat64,libc_creat64,WUNUSED ATTR_IN(1),fd_t,NOTHROW_RPC,LIBCCALL,(char const *filename, mode_t mode),(filename,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$__openat_2,libd_openat,WUNUSED ATTR_IN(2),fd_t,NOTHROW_RPC,VLIBDCALL,(fd_t dirfd, char const *filename, oflag_t oflags, ...),(dirfd,filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$openat,libd_openat,WUNUSED ATTR_IN(2),fd_t,NOTHROW_RPC,VLIBDCALL,(fd_t dirfd, char const *filename, oflag_t oflags, ...),(dirfd,filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(__openat_2,libc_openat,WUNUSED ATTR_IN(2),fd_t,NOTHROW_RPC,VLIBCCALL,(fd_t dirfd, char const *filename, oflag_t oflags, ...),(dirfd,filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(openat,libc_openat,WUNUSED ATTR_IN(2),fd_t,NOTHROW_RPC,VLIBCCALL,(fd_t dirfd, char const *filename, oflag_t oflags, ...),(dirfd,filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$__openat64_2,libd_openat64,WUNUSED ATTR_IN(2),fd_t,NOTHROW_RPC,VLIBDCALL,(fd_t dirfd, char const *filename, oflag_t oflags, ...),(dirfd,filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(DOS$openat64,libd_openat64,WUNUSED ATTR_IN(2),fd_t,NOTHROW_RPC,VLIBDCALL,(fd_t dirfd, char const *filename, oflag_t oflags, ...),(dirfd,filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(__openat64_2,libc_openat64,WUNUSED ATTR_IN(2),fd_t,NOTHROW_RPC,VLIBCCALL,(fd_t dirfd, char const *filename, oflag_t oflags, ...),(dirfd,filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(openat64,libc_openat64,WUNUSED ATTR_IN(2),fd_t,NOTHROW_RPC,VLIBCCALL,(fd_t dirfd, char const *filename, oflag_t oflags, ...),(dirfd,filename,oflags,));
DEFINE_PUBLIC_ALIAS_P(posix_fadvise,libc_posix_fadvise,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __PIO_OFFSET offset, __PIO_OFFSET length, __STDC_INT_AS_UINT_T advise),(fd,offset,length,advise));
DEFINE_PUBLIC_ALIAS_P(posix_fallocate,libc_posix_fallocate,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __PIO_OFFSET offset, __PIO_OFFSET length),(fd,offset,length));
DEFINE_PUBLIC_ALIAS_P(posix_fadvise64,libc_posix_fadvise64,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __PIO_OFFSET64 offset, __PIO_OFFSET64 length, __STDC_INT_AS_UINT_T advise),(fd,offset,length,advise));
DEFINE_PUBLIC_ALIAS_P(posix_fallocate64,libc_posix_fallocate64,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd, __PIO_OFFSET64 offset, __PIO_OFFSET64 length),(fd,offset,length));
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(_locking,libc_lockf,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, __STDC_INT_AS_UINT_T cmd, __PIO_OFFSET length),(fd,cmd,length));
#endif /* __LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(lockf,libc_lockf,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, __STDC_INT_AS_UINT_T cmd, __PIO_OFFSET length),(fd,cmd,length));
DEFINE_PUBLIC_ALIAS_P(lockf64,libc_lockf64,ATTR_FDARG(1),int,NOTHROW_RPC,LIBCCALL,(fd_t fd, __STDC_INT_AS_UINT_T cmd, __PIO_OFFSET64 length),(fd,cmd,length));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_FCNTL_C */
