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

/*[[[head:process_vm_readv,hash:CRC-32=0xa24e8111]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.process_vm_readv") ssize_t
NOTHROW_RPC(LIBCCALL libc_process_vm_readv)(pid_t pid,
                                            struct iovec const *local_iov,
                                            unsigned long int liovcnt,
                                            struct iovec const *remote_iov,
                                            unsigned long int riovcnt,
                                            unsigned long int flags)
/*[[[body:process_vm_readv]]]*/
{
	ssize_t result;
	result = sys_process_vm_readv(pid,
	                              local_iov, (size_t)liovcnt,
	                              remote_iov, (size_t)riovcnt,
	                              (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:process_vm_readv]]]*/

/*[[[head:process_vm_writev,hash:CRC-32=0x89f6b70c]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.process_vm_writev") ssize_t
NOTHROW_RPC(LIBCCALL libc_process_vm_writev)(pid_t pid,
                                             struct iovec const *local_iov,
                                             unsigned long int liovcnt,
                                             struct iovec const *remote_iov,
                                             unsigned long int riovcnt,
                                             unsigned long int flags)
/*[[[body:process_vm_writev]]]*/
{
	ssize_t result;
	result = sys_process_vm_writev(pid,
	                               local_iov, (size_t)liovcnt,
	                               remote_iov, (size_t)riovcnt,
	                               (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:process_vm_writev]]]*/

/*[[[head:readv,hash:CRC-32=0x6ee8bfb7]]]*/
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.readv") ssize_t
NOTHROW_RPC(LIBCCALL libc_readv)(fd_t fd,
                                 struct iovec const *iov,
                                 __STDC_INT_AS_SIZE_T count)
/*[[[body:readv]]]*/
{
	ssize_t result;
	result = sys_readv(fd, iov, (size_t)count);
	return libc_seterrno_syserr(result);
}
/*[[[end:readv]]]*/

/*[[[head:writev,hash:CRC-32=0xb863f233]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.writev") ssize_t
NOTHROW_RPC(LIBCCALL libc_writev)(fd_t fd,
                                  struct iovec const *iov,
                                  __STDC_INT_AS_SIZE_T count)
/*[[[body:writev]]]*/
{
	ssize_t result;
	result = sys_writev(fd, iov, (size_t)count);
	return libc_seterrno_syserr(result);
}
/*[[[end:writev]]]*/

/*[[[head:preadv,hash:CRC-32=0xb149e47]]]*/
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.preadv") ssize_t
NOTHROW_RPC(LIBCCALL libc_preadv)(fd_t fd,
                                  struct iovec const *iov,
                                  __STDC_INT_AS_SIZE_T count,
                                  off_t offset)
/*[[[body:preadv]]]*/
{
	ssize_t result;
	result = sys_preadv(fd, iov, (size_t)count, (uint64_t)(pos_t)offset);
	return libc_seterrno_syserr(result);
}
/*[[[end:preadv]]]*/

/*[[[head:pwritev,hash:CRC-32=0xb5b4f3c]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.pwritev") ssize_t
NOTHROW_RPC(LIBCCALL libc_pwritev)(fd_t fd,
                                   struct iovec const *iov,
                                   __STDC_INT_AS_SIZE_T count,
                                   off_t offset)
/*[[[body:pwritev]]]*/
{
	ssize_t result;
	result = sys_pwritev(fd, iov, (size_t)count, (uint64_t)(pos_t)offset);
	return libc_seterrno_syserr(result);
}
/*[[[end:pwritev]]]*/

/*[[[head:preadv64,hash:CRC-32=0xf9f05abc]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_preadv64, libc_preadv);
#else
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.preadv64") ssize_t
NOTHROW_RPC(LIBCCALL libc_preadv64)(fd_t fd,
                                    struct iovec const *iov,
                                    __STDC_INT_AS_SIZE_T count,
                                    off64_t offset)
/*[[[body:preadv64]]]*/
{
	ssize_t result;
	result = sys_preadv(fd, iov, (size_t)count, (uint64_t)(pos64_t)offset);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:preadv64]]]*/

/*[[[head:pwritev64,hash:CRC-32=0x439a375d]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_pwritev64, libc_pwritev);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.pwritev64") ssize_t
NOTHROW_RPC(LIBCCALL libc_pwritev64)(fd_t fd,
                                     struct iovec const *iov,
                                     __STDC_INT_AS_SIZE_T count,
                                     off64_t offset)
/*[[[body:pwritev64]]]*/
{
	ssize_t result;
	result = sys_pwritev(fd, iov, (size_t)count, (uint64_t)(pos64_t)offset);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:pwritev64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x3af7381a]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(process_vm_readv, libc_process_vm_readv);
DEFINE_PUBLIC_WEAK_ALIAS(process_vm_writev, libc_process_vm_writev);
DEFINE_PUBLIC_WEAK_ALIAS(readv, libc_readv);
DEFINE_PUBLIC_WEAK_ALIAS(writev, libc_writev);
DEFINE_PUBLIC_WEAK_ALIAS(preadv, libc_preadv);
DEFINE_PUBLIC_WEAK_ALIAS(pwritev, libc_pwritev);
DEFINE_PUBLIC_WEAK_ALIAS(preadv64, libc_preadv64);
DEFINE_PUBLIC_WEAK_ALIAS(pwritev64, libc_pwritev64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_UIO_C */
