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
#ifndef GUARD_LIBC_USER_SYS_UIO_C
#define GUARD_LIBC_USER_SYS_UIO_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include "sys.uio.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_process_vm_readv,hash:CRC-32=0xc26f2aac]]]*/
INTERN WUNUSED ssize_t
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

/*[[[head:libc_process_vm_writev,hash:CRC-32=0x3c46a5ca]]]*/
INTERN ssize_t
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

/*[[[head:libc_readv,hash:CRC-32=0x4908ae4]]]*/
INTERN WUNUSED NONNULL((2)) ssize_t
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

/*[[[head:libc_writev,hash:CRC-32=0x77ed705a]]]*/
INTERN NONNULL((2)) ssize_t
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

/*[[[head:libc_preadv,hash:CRC-32=0xa405a0aa]]]*/
INTERN WUNUSED NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_preadv)(fd_t fd,
                                  struct iovec const *iov,
                                  __STDC_INT_AS_SIZE_T count,
                                  off_t offset)
/*[[[body:libc_preadv]]]*/
{
	ssize_t result;
	result = sys_preadv(fd, iov, (size_t)count, (uint64_t)(pos_t)offset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_preadv]]]*/

/*[[[head:libc_pwritev,hash:CRC-32=0x1549d233]]]*/
INTERN NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwritev)(fd_t fd,
                                   struct iovec const *iov,
                                   __STDC_INT_AS_SIZE_T count,
                                   off_t offset)
/*[[[body:libc_pwritev]]]*/
{
	ssize_t result;
	result = sys_pwritev(fd, iov, (size_t)count, (uint64_t)(pos_t)offset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_pwritev]]]*/

/*[[[head:libc_preadv64,hash:CRC-32=0x69e14d66]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_preadv64, libc_preadv);
#else /* MAGIC:alias */
INTERN WUNUSED NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_preadv64)(fd_t fd,
                                    struct iovec const *iov,
                                    __STDC_INT_AS_SIZE_T count,
                                    off64_t offset)
/*[[[body:libc_preadv64]]]*/
{
	ssize_t result;
	result = sys_preadv(fd, iov, (size_t)count, (uint64_t)(pos64_t)offset);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_preadv64]]]*/

/*[[[head:libc_pwritev64,hash:CRC-32=0x5b3cc165]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_pwritev64, libc_pwritev);
#else /* MAGIC:alias */
INTERN NONNULL((2)) ssize_t
NOTHROW_RPC(LIBCCALL libc_pwritev64)(fd_t fd,
                                     struct iovec const *iov,
                                     __STDC_INT_AS_SIZE_T count,
                                     off64_t offset)
/*[[[body:libc_pwritev64]]]*/
{
	ssize_t result;
	result = sys_pwritev(fd, iov, (size_t)count, (uint64_t)(pos64_t)offset);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_pwritev64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x7a599e53]]]*/
DEFINE_PUBLIC_ALIAS(process_vm_readv, libc_process_vm_readv);
DEFINE_PUBLIC_ALIAS(process_vm_writev, libc_process_vm_writev);
DEFINE_PUBLIC_ALIAS(readv, libc_readv);
DEFINE_PUBLIC_ALIAS(writev, libc_writev);
DEFINE_PUBLIC_ALIAS(preadv, libc_preadv);
DEFINE_PUBLIC_ALIAS(pwritev, libc_pwritev);
DEFINE_PUBLIC_ALIAS(preadv64, libc_preadv64);
DEFINE_PUBLIC_ALIAS(pwritev64, libc_pwritev64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_UIO_C */
