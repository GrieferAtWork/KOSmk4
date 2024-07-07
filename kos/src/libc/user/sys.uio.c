/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_UIO_C
#define GUARD_LIBC_USER_SYS_UIO_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include "sys.uio.h"

DECL_BEGIN

/*[[[head:libc_process_vm_readv,hash:CRC-32=0x9fd04935]]]*/
/* >> process_vm_readv(2)
 * Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
INTERN ATTR_SECTION(".text.crt.unsorted") WUNUSED ATTR_INS(2, 3) ATTR_INS(4, 5) ssize_t
NOTHROW_RPC(LIBCCALL libc_process_vm_readv)(pid_t pid,
                                            struct iovec const *local_iov,
                                            ulongptr_t liovcnt,
                                            struct iovec const *remote_iov,
                                            ulongptr_t riovcnt,
                                            ulongptr_t flags)
/*[[[body:libc_process_vm_readv]]]*/
{
	ssize_t result;
	result = sys_process_vm_readv(pid,
	                              local_iov, (size_t)liovcnt,
	                              remote_iov, (size_t)riovcnt,
	                              (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_process_vm_readv]]]*/

/*[[[head:libc_process_vm_writev,hash:CRC-32=0xe079e1bb]]]*/
/* >> process_vm_writev(2)
 * Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_INS(2, 3) ATTR_INS(4, 5) ssize_t
NOTHROW_RPC(LIBCCALL libc_process_vm_writev)(pid_t pid,
                                             struct iovec const *local_iov,
                                             ulongptr_t liovcnt,
                                             struct iovec const *remote_iov,
                                             ulongptr_t riovcnt,
                                             ulongptr_t flags)
/*[[[body:libc_process_vm_writev]]]*/
{
	ssize_t result;
	result = sys_process_vm_writev(pid,
	                               local_iov, (size_t)liovcnt,
	                               remote_iov, (size_t)riovcnt,
	                               (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_process_vm_writev]]]*/

/*[[[head:libc_readv,hash:CRC-32=0xa38ec213]]]*/
/* >> readv(2)
 * Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read  data into `count'  separate buffers, though  still return the actual
 * number of read bytes.
 * When `fd' has the  `O_NONBLOCK' flag set,  only read as  much data as  was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
INTERN ATTR_SECTION(".text.crt.unsorted") WUNUSED ATTR_FDREAD(1) ATTR_INS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_readv)(fd_t fd,
                                 struct iovec const *iov,
                                 __STDC_INT_AS_SIZE_T count)
/*[[[body:libc_readv]]]*/
{
	ssize_t result;
	result = sys_readv(fd, iov, (size_t)count);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_readv]]]*/

/*[[[head:libc_writev,hash:CRC-32=0x11eab354]]]*/
/* >> writev(2)
 * Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write  data from `count'  separate buffers, though  still return the actual
 * number of written bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only write as much  data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_FDWRITE(1) ATTR_INS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_writev)(fd_t fd,
                                  struct iovec const *iov,
                                  __STDC_INT_AS_SIZE_T count)
/*[[[body:libc_writev]]]*/
{
	ssize_t result;
	result = sys_writev(fd, iov, (size_t)count);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_writev]]]*/

/*[[[head:libc_preadv,hash:CRC-32=0x55182df6]]]*/
/* >> preadv(2), preadv64(2)
 * Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
INTERN ATTR_SECTION(".text.crt.unsorted") WUNUSED ATTR_FDREAD(1) ATTR_INS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_preadv)(fd_t fd,
                                  struct iovec const *iov,
                                  __STDC_INT_AS_SIZE_T count,
                                  off_t offset)
/*[[[body:libc_preadv]]]*/
{
	ssize_t result;
	result = sys_preadv(fd, iov, (size_t)count,
	                    (uint64_t)(pos_t)offset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_preadv]]]*/

/*[[[head:libc_pwritev,hash:CRC-32=0x94fa20bd]]]*/
/* >> pwritev(2), pwritev64(2)
 * Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_FDWRITE(1) ATTR_INS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwritev)(fd_t fd,
                                   struct iovec const *iov,
                                   __STDC_INT_AS_SIZE_T count,
                                   off_t offset)
/*[[[body:libc_pwritev]]]*/
{
	ssize_t result;
	result = sys_pwritev(fd, iov, (size_t)count,
	                     (uint64_t)(pos_t)offset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_pwritev]]]*/

/*[[[head:libc_preadv64,hash:CRC-32=0xe5c2cd1b]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_preadv64, libc_preadv);
#else /* MAGIC:alias */
/* >> preadv(2), preadv64(2)
 * Same as  `readv(2)', but  read data  from a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
INTERN ATTR_SECTION(".text.crt.unsorted") WUNUSED ATTR_FDREAD(1) ATTR_INS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_preadv64)(fd_t fd,
                                    struct iovec const *iov,
                                    __STDC_INT_AS_SIZE_T count,
                                    off64_t offset)
/*[[[body:libc_preadv64]]]*/
{
	ssize_t result;
	result = sys_preadv(fd, iov, (size_t)count,
	                    (uint64_t)(pos64_t)offset);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_preadv64]]]*/

/*[[[head:libc_pwritev64,hash:CRC-32=0x8438b47f]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_pwritev64, libc_pwritev);
#else /* MAGIC:alias */
/* >> pwritev(2), pwritev64(2)
 * Same as  `writev(2)', but  write data  to a  file at  a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
INTERN ATTR_SECTION(".text.crt.unsorted") ATTR_FDWRITE(1) ATTR_INS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwritev64)(fd_t fd,
                                     struct iovec const *iov,
                                     __STDC_INT_AS_SIZE_T count,
                                     off64_t offset)
/*[[[body:libc_pwritev64]]]*/
{
	ssize_t result;
	result = sys_pwritev(fd, iov, (size_t)count,
	                     (uint64_t)(pos64_t)offset);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pwritev64]]]*/





/*[[[start:exports,hash:CRC-32=0xbcd35752]]]*/
DEFINE_PUBLIC_ALIAS_P(process_vm_readv,libc_process_vm_readv,WUNUSED ATTR_INS(2, 3) ATTR_INS(4, 5),ssize_t,NOTHROW_RPC,LIBCCALL,(pid_t pid, struct iovec const *local_iov, ulongptr_t liovcnt, struct iovec const *remote_iov, ulongptr_t riovcnt, ulongptr_t flags),(pid,local_iov,liovcnt,remote_iov,riovcnt,flags));
DEFINE_PUBLIC_ALIAS_P(process_vm_writev,libc_process_vm_writev,ATTR_INS(2, 3) ATTR_INS(4, 5),ssize_t,NOTHROW_RPC,LIBCCALL,(pid_t pid, struct iovec const *local_iov, ulongptr_t liovcnt, struct iovec const *remote_iov, ulongptr_t riovcnt, ulongptr_t flags),(pid,local_iov,liovcnt,remote_iov,riovcnt,flags));
DEFINE_PUBLIC_ALIAS_P(__readv,libc_readv,WUNUSED ATTR_FDREAD(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count),(fd,iov,count));
DEFINE_PUBLIC_ALIAS_P(syscall_readv,libc_readv,WUNUSED ATTR_FDREAD(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count),(fd,iov,count));
DEFINE_PUBLIC_ALIAS_P(__syscall_readv,libc_readv,WUNUSED ATTR_FDREAD(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count),(fd,iov,count));
DEFINE_PUBLIC_ALIAS_P(__libc_syscall_readv,libc_readv,WUNUSED ATTR_FDREAD(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count),(fd,iov,count));
DEFINE_PUBLIC_ALIAS_P(__libc_readv,libc_readv,WUNUSED ATTR_FDREAD(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count),(fd,iov,count));
DEFINE_PUBLIC_ALIAS_P(readv,libc_readv,WUNUSED ATTR_FDREAD(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count),(fd,iov,count));
DEFINE_PUBLIC_ALIAS_P(__writev,libc_writev,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count),(fd,iov,count));
DEFINE_PUBLIC_ALIAS_P(__libc_writev,libc_writev,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count),(fd,iov,count));
DEFINE_PUBLIC_ALIAS_P(syscall_writev,libc_writev,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count),(fd,iov,count));
DEFINE_PUBLIC_ALIAS_P(__syscall_writev,libc_writev,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count),(fd,iov,count));
DEFINE_PUBLIC_ALIAS_P(__libc_syscall_writev,libc_writev,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count),(fd,iov,count));
DEFINE_PUBLIC_ALIAS_P(writev,libc_writev,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count),(fd,iov,count));
DEFINE_PUBLIC_ALIAS_P(preadv,libc_preadv,WUNUSED ATTR_FDREAD(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count, off_t offset),(fd,iov,count,offset));
DEFINE_PUBLIC_ALIAS_P(pwritev,libc_pwritev,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count, off_t offset),(fd,iov,count,offset));
DEFINE_PUBLIC_ALIAS_P(preadv64,libc_preadv64,WUNUSED ATTR_FDREAD(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count, off64_t offset),(fd,iov,count,offset));
DEFINE_PUBLIC_ALIAS_P(pwritev64,libc_pwritev64,ATTR_FDWRITE(1) ATTR_INS(2, 3),ssize_t,NOTHROW_RPC,LIBCCALL,(fd_t fd, struct iovec const *iov, __STDC_INT_AS_SIZE_T count, off64_t offset),(fd,iov,count,offset));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_UIO_C */
