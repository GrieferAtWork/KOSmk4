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
#ifndef GUARD_LIBC_USER_KOS_FD_C
#define GUARD_LIBC_USER_KOS_FD_C 1

#include "../api.h"
/**/

#include <hybrid/overflow.h>

#include <kos/io.h>
#include <kos/ioctl/fd.h>
#include <kos/ioctl/file.h>
#include <sys/ioctl.h>

#include <errno.h>
#include <string.h>

#include "kos.fd.h"

DECL_BEGIN

/*[[[head:libc_fd_polltest,hash:CRC-32=0x2fa23725]]]*/
/* >> fd_polltest(3)
 * Convenience wrapper  around `FD_IOC_POLLTEST',  used to  test which  (if
 * any) operations applicable may be performed without blocking right  now.
 * Poll  testing is primarily used internally by the kernel for `ppoll(2)',
 * `pselect(2)', `select(2)', etc., but you can also check what can be done
 * right now using this function. Note however that the info returned  here
 * may already be out-of-date by the time this function returns.
 *
 * @param: what: What to test for (set of `POLL')
 * @return: * : What can be done without blocking (may not longer be up-to-date) */
INTERN ATTR_SECTION(".text.crt.io.utility.kos") WUNUSED ATTR_FDARG(1) poll_mode_t
NOTHROW_NCX(LIBCCALL libc_fd_polltest)(fd_t fd,
                                       poll_mode_t what)
/*[[[body:libc_fd_polltest]]]*/
{
	if unlikely(ioctl(fd, FD_IOC_POLLTEST, &what) < 0)
		return (poll_mode_t)-1;
	return what;
}
/*[[[end:libc_fd_polltest]]]*/

/*[[[head:libc_fd_cast,hash:CRC-32=0x96b94105]]]*/
/* >> fd_cast(3)
 * Convenience wrapper around `FD_IOC_CAST', used to cast the object behind
 * a  given file descriptor  `fd' into another,  related kernel object, and
 * store the result in a new file descriptor.
 * For example: you can cast a file as returned by `open(2)' into various sub-objects:
 *  - HANDLE_TYPE_MFILE:  Memory-file / inode descriptor
 *  - HANDLE_TYPE_DIRENT: Directory entry name (file-path descriptor w/o leading path)
 *  - HANDLE_TYPE_PATH:   Filename path (file-path descriptor w/o trailing filename)
 * @param: fd:   The file descriptor to cast
 * @param: type: Wanted cast target type (one of `HANDLE_TYPE_*')
 * @param: mode: Set of `IO_CLOEXEC | IO_CLOFORK'
 * @return: * :  The new file descriptor
 * @return: -1:  [errno=ENOTSOCK] Given `fd' cannot be cast to `type' (which was `HANDLE_TYPE_SOCKET')
 * @return: -1:  [errno=EBADFD] Given `fd' cannot be cast to specified `type' */
INTERN ATTR_SECTION(".text.crt.io.utility.kos") WUNUSED ATTR_FDARG(1) fd_t
NOTHROW_NCX(LIBCCALL libc_fd_cast)(fd_t fd,
                                   uint32_t type,
                                   iomode_t mode)
/*[[[body:libc_fd_cast]]]*/
{
	struct fdcast cast;
	bzero(&cast, sizeof(cast));
	cast.fc_rqtyp          = type;
	cast.fc_resfd.of_mode  = OPENFD_MODE_AUTO;
	cast.fc_resfd.of_flags = mode;
	if unlikely(ioctl(fd, FD_IOC_CAST, &cast) < 0)
		goto err;
	return cast.fc_resfd.of_hint;
err:
	return -1;
}
/*[[[end:libc_fd_cast]]]*/

/*[[[head:libc_fd_msalign,hash:CRC-32=0xe18be7f3]]]*/
/* >> fd_msalign(3)
 * Convenience wrapper around `FILE_IOC_MSALIGN', used to create a  miss-aligned,
 * mmap'able  alias of  the backing data  of `fd'. For  this purpose, `*p_offset'
 * is  allowed to be any arbitrary value on entry, and the alias returned by this
 * function  will contain data  offset by `*p_offset & (getpagesize() - 1)'. This
 * offset is then returned from `*p_offset' upon return, meaning that you may re-
 * use `OUT(*p_offset)' as an argument to `mmap(2)' and have the contents of  the
 * original file appear shifted to the start of a page.
 *
 * For more information, see the description on `struct file_msalign'
 *
 * @param: mode: Set of `IO_CLOEXEC | IO_CLOFORK'
 * @return: * : A file descriptor for the newly created misaligned wrapper
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.io.utility.kos") WUNUSED ATTR_FDARG(1) ATTR_INOUT(2) fd_t
NOTHROW_NCX(LIBCCALL libc_fd_msalign)(fd_t fd,
                                      uint64_t *p_offset,
                                      iomode_t mode)
/*[[[body:libc_fd_msalign]]]*/
{
	struct file_msalign msalign;
	bzero(&msalign, sizeof(msalign));
	msalign.fmsa_offset = *p_offset;
	msalign.fmsa_resfd.of_mode  = OPENFD_MODE_AUTO;
	msalign.fmsa_resfd.of_flags = mode;
	if unlikely(ioctl(fd, FILE_IOC_MSALIGN, &msalign) < 0)
		goto err;
	*p_offset = msalign.fmsa_offset;
	return msalign.fmsa_resfd.of_hint;
err:
	return -1;
}
/*[[[end:libc_fd_msalign]]]*/

/*[[[head:libc_fd_subregion,hash:CRC-32=0xe4ff5441]]]*/
/* >> fd_subregion(3)
 * Convenience wrapper around `FILE_IOC_SUBREGION', used to create a  sub-region
 * alias  of another file. Said alias can then be shared and used like any other
 * file descriptor (with the primary purpose being that it can be shared between
 * processes), whilst only  allowing access  to the specific  sub-region of  the
 * original file. Additionally:
 *  - You can also create further sub-regions of other sub-regions
 *  - You can (without  risking OOM) force-revoke  all memory mappings  and
 *    future accesses to data that used-to-be-described by some sub-region.
 *    s.a. `fd_delregion(3)'
 *  - The primary intended  use of  this function and  `fd_delregion(3)' is  to
 *    allow  a user-space  video driver/compositor  to load  some small portion
 *    of video memory, or  the display's LFB, and  share direct access to  that
 *    region  of physical  memory with  less privileged  processes, whilst also
 *    being able to revoke  that access at  a moment's notice  (such as when  a
 *    window that used to be unobstructed suddenly has another window in-front,
 *    meaning that the compositor has to  revoke direct screen access from  the
 *    window, and any process that might has live memory mappings of it).
 * @param: base:      The page-aligned starting address of the sub-region
 * @param: num_bytes: The size of the region (in bytes), starting at `base'
 * @param: mode:      Set of `IO_CLOEXEC | IO_CLOFORK'
 * @return: * : A file descriptor for the newly created sub-region
 * @return: -1: [errno=EACCES] Given `fd' was not opened for read+write
 * @return: -1: [errno=EINVAL] Given `base' / `num_bytes' are improperly aligned, or too large
 * @return: -1: [errno=EINVAL] Given `base + num_bytes' is greater than the size of `fd'
 * @return: -1: [errno=EPERM]  Given `fd' uses a custom mmap mechanism (doesn't
 *                             support "raw" I/O), and isn't another sub-region
 * @return: -1: [errno=ENOMEM] Insufficient memory */
INTERN ATTR_SECTION(".text.crt.io.utility.kos") WUNUSED ATTR_FDARG(1) fd_t
NOTHROW_NCX(LIBCCALL libc_fd_subregion)(fd_t fd,
                                        uint64_t base,
                                        uint64_t num_bytes,
                                        iomode_t mode)
/*[[[body:libc_fd_subregion]]]*/
{
	struct file_subregion sr;
	bzero(&sr, sizeof(sr));
	sr.fsr_minaddr = base;
	if (OVERFLOW_UADD(base, num_bytes - 1, &sr.fsr_maxaddr))
		goto err_inval;
	sr.fsr_resfd.of_mode  = OPENFD_MODE_AUTO;
	sr.fsr_resfd.of_flags = mode;
	if unlikely(ioctl(fd, FILE_IOC_SUBREGION, &sr) < 0)
		goto err;
	return sr.fsr_resfd.of_hint;
err_inval:
	return libc_seterrno(EINVAL);
err:
	return -1;
}
/*[[[end:libc_fd_subregion]]]*/

/*[[[head:libc_fd_delregion,hash:CRC-32=0x750cab9e]]]*/
/* >> fd_delregion(3)
 * Convenience wrapper around `FILE_IOC_DELREGION', used to system-wide force-revoke
 * all  access to  memory described by  a sub-region file  descriptor, as previously
 * created using `fd_subregion(3)':
 *  - Any  memory-mappings made using  `fd' or other  sub-regions derived from `fd'
 *    are forcefully replaced with mappings of `/dev/void' (meaning that while they
 *    are still mapped into memory and can be read/written, only garbled data  will
 *    be read, and any writes will be lost)
 *  - Any future calls to `pread(2)' or `pwrite(2)' performed on `fd' or some other
 *    sub-region derived from `fd' will similarly behave as though `fd' were a file
 *    descriptor for `/dev/void'
 *  - If `fd' itself was derived from another sub-region, that "parent" sub-region,
 *    as well as any "sibling" sub-region will *NOT* be revoked (meaning that  this
 *    function only ever revokes access from anyone that had been given `fd').
 *
 * @return: 0 : Success: access to `fd' has been revoked / replaced with `/dev/void'
 * @return: -1: [errno=EPERM] Given `fd' is a sub-region, as returned by `fd_subregion(3)' */
INTERN ATTR_SECTION(".text.crt.io.utility.kos") ATTR_FDARG(1) int
NOTHROW_NCX(LIBCCALL libc_fd_delregion)(fd_t fd)
/*[[[body:libc_fd_delregion]]]*/
{
	return ioctl(fd, FILE_IOC_DELREGION);
}
/*[[[end:libc_fd_delregion]]]*/

/*[[[head:libc_fd_tailread,hash:CRC-32=0x69fab160]]]*/
/* >> fd_tailread(3)
 * Convenience wrapper around `FILE_IOC_TAILREAD', which can be used to perform a
 * so-called  "tail-read" from some given file `fd'. A tail-read essentially does
 * what is done  by `tail -f' on  the CLI, meaning  where `read(2)' /  `pread(2)'
 * would  return `0' when  trying to read past  the end of  a file, this function
 * will block until at least `1' byte could be read at `offset'.
 *
 * @param: fd:      The file to read from.
 * @param: buf:     Output buffer for read data. At most `bufsize' bytes will be read
 * @param: bufsize: Max # of bytes to read.
 * @param: offset:  Starting offset for where to start reading.
 * @return: > 0:    The actual # of bytes that were read (always `<= bufsize')
 * @return: 0 :     Nothing was read (only happens when `bufsize == 0')
 * @return: -1:     [errno=*] Failed to read data (errors are the same as for `read(2)' and `pread(2)') */
INTERN ATTR_SECTION(".text.crt.io.utility.kos") WUNUSED ATTR_FDREAD(1) ATTR_OUTS(2, 3) ssize_t
NOTHROW_NCX(LIBCCALL libc_fd_tailread)(fd_t fd,
                                       void *buf,
                                       size_t bufsize,
                                       uint64_t offset)
/*[[[body:libc_fd_tailread]]]*/
{
	struct file_tailread tr;
	bzero(&tr, sizeof(tr));
	tr.ftr_pos = offset;
	tr.ftr_siz = bufsize;
	tr.ftr_buf = buf;
	if unlikely(ioctl(fd, FILE_IOC_TAILREAD, &tr) < 0)
		goto err;
	return (ssize_t)tr.ftr_siz;
err:
	return -1;
}
/*[[[end:libc_fd_tailread]]]*/

/*[[[head:libc_fd_trim,hash:CRC-32=0x847c8d65]]]*/
/* >> fd_trim(3)
 * Convenience wrapper around `FILE_IOC_TRIM', which can be used
 * to trim/unload parts of the filesystem/mmap cache of a  file.
 *
 * @param: fd:        The file whose caches to trim.
 * @param: base:      Starting offset for where to start trimming (will be rounded down)
 * @param: num_bytes: Number of bytes that will be trimmed (will be rounded up)
 * @param: mode:      Trim-mode (one of `FILE_TRIM_MODE_*')
 * @return: * : The # of bytes that were trimmed
 * @return: (uint64_t)-1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.io.utility.kos") ATTR_FDARG(1) uint64_t
NOTHROW_NCX(LIBCCALL libc_fd_trim)(fd_t fd,
                                   uint64_t base,
                                   uint64_t num_bytes,
                                   uint32_t mode)
/*[[[body:libc_fd_trim]]]*/
{
	struct file_trim trim;
	bzero(&trim, sizeof(trim));
	trim.ft_fpos = base;
	trim.ft_size = num_bytes;
	trim.ft_mode = mode;
	if unlikely(ioctl(fd, FILE_IOC_TRIM, &trim) < 0)
		goto err;
	return trim.ft_size;
err:
	return (uint64_t)-1;
}
/*[[[end:libc_fd_trim]]]*/

/*[[[start:exports,hash:CRC-32=0x3427bee5]]]*/
DEFINE_PUBLIC_ALIAS_P(fd_polltest,libc_fd_polltest,WUNUSED ATTR_FDARG(1),poll_mode_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, poll_mode_t what),(fd,what));
DEFINE_PUBLIC_ALIAS_P(fd_cast,libc_fd_cast,WUNUSED ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, uint32_t type, iomode_t mode),(fd,type,mode));
DEFINE_PUBLIC_ALIAS_P(fd_msalign,libc_fd_msalign,WUNUSED ATTR_FDARG(1) ATTR_INOUT(2),fd_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, uint64_t *p_offset, iomode_t mode),(fd,p_offset,mode));
DEFINE_PUBLIC_ALIAS_P(fd_subregion,libc_fd_subregion,WUNUSED ATTR_FDARG(1),fd_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, uint64_t base, uint64_t num_bytes, iomode_t mode),(fd,base,num_bytes,mode));
DEFINE_PUBLIC_ALIAS_P(fd_delregion,libc_fd_delregion,ATTR_FDARG(1),int,NOTHROW_NCX,LIBCCALL,(fd_t fd),(fd));
DEFINE_PUBLIC_ALIAS_P(fd_tailread,libc_fd_tailread,WUNUSED ATTR_FDREAD(1) ATTR_OUTS(2, 3),ssize_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, void *buf, size_t bufsize, uint64_t offset),(fd,buf,bufsize,offset));
DEFINE_PUBLIC_ALIAS_P(fd_trim,libc_fd_trim,ATTR_FDARG(1),uint64_t,NOTHROW_NCX,LIBCCALL,(fd_t fd, uint64_t base, uint64_t num_bytes, uint32_t mode),(fd,base,num_bytes,mode));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_FD_C */
