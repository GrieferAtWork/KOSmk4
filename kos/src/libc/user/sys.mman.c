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
#ifndef GUARD_LIBC_USER_SYS_MMAN_C
#define GUARD_LIBC_USER_SYS_MMAN_C 1
#define _KOS_KERNEL_SOURCE 1 /* MAP_OFFSET64_POINTER */

#include "../api.h"
#include "sys.mman.h"

#include <kos/syscalls.h>
#include <stdint.h>
#include <sys/mman.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:mmap,hash:CRC-32=0x2a06ccc8]]]*/
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.heap.mman.mmap") void *
NOTHROW_NCX(LIBCCALL libc_mmap)(void *addr,
                                size_t len,
                                int prot,
                                int flags,
                                fd_t fd,
                                off_t offset)
/*[[[body:mmap]]]*/
{
	void *result;
	result = sys_mmap(addr,
	                  len,
	                  (syscall_ulong_t)(unsigned int)prot,
	                  (syscall_ulong_t)(unsigned int)flags,
	                  fd,
	                  (syscall_ulong_t)(syscall_slong_t)offset);
	return libc_seterrno_syserr2(result, MAP_FAILED);
}
/*[[[end:mmap]]]*/

/*[[[head:munmap,hash:CRC-32=0xfdc6d560]]]*/
/* Unmap memory from `addr...+=len' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.heap.mman.munmap") int
NOTHROW_NCX(LIBCCALL libc_munmap)(void *addr,
                                  size_t len)
/*[[[body:munmap]]]*/
{
	errno_t result;
	result = sys_munmap(addr,
	                    len);
	return libc_seterrno_syserr(result);
}
/*[[[end:munmap]]]*/

/*[[[head:mprotect,hash:CRC-32=0x2ac89ff1]]]*/
/* @param prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|
 *              PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED|PROT_GROWSUP|
 *              PROT_GROWSDOWN' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.system.mman.mprotect") int
NOTHROW_NCX(LIBCCALL libc_mprotect)(void *addr,
                                    size_t len,
                                    int prot)
/*[[[body:mprotect]]]*/
{
	errno_t result;
	result = sys_mprotect(addr,
	                      len,
	                      (syscall_ulong_t)(unsigned int)prot);
	return libc_seterrno_syserr(result);
}
/*[[[end:mprotect]]]*/

/*[[[head:msync,hash:CRC-32=0x7508ff65]]]*/
/* @param flags: Set of `MS_ASYNC|MS_INVALIDATE|MS_SYNC' */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.system.mman.msync") int
NOTHROW_RPC(LIBCCALL libc_msync)(void *addr,
                                 size_t len,
                                 int flags)
/*[[[body:msync]]]*/
{
	errno_t result;
	result = sys_msync(addr,
	                   len,
	                   (syscall_ulong_t)(unsigned int)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:msync]]]*/

/*[[[head:mlock,hash:CRC-32=0x28267a22]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.system.mman.mlock") int
NOTHROW_NCX(LIBCCALL libc_mlock)(void const *addr,
                                 size_t len)
/*[[[body:mlock]]]*/
{
	errno_t result;
	result = sys_mlock(addr,
	                   len);
	return libc_seterrno_syserr(result);
}
/*[[[end:mlock]]]*/

/*[[[head:munlock,hash:CRC-32=0xdb208ffe]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.system.mman.munlock") int
NOTHROW_NCX(LIBCCALL libc_munlock)(void const *addr,
                                   size_t len)
/*[[[body:munlock]]]*/
{
	errno_t result;
	result = sys_munlock(addr,
	                     len);
	return libc_seterrno_syserr(result);
}
/*[[[end:munlock]]]*/

/*[[[head:mlockall,hash:CRC-32=0x259b4078]]]*/
/* @param flags: Set of `MCL_CURRENT|MCL_FUTURE|MCL_ONFAULT' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.mman.mlockall") int
NOTHROW_NCX(LIBCCALL libc_mlockall)(int flags)
/*[[[body:mlockall]]]*/
{
	errno_t result;
	result = sys_mlockall((syscall_ulong_t)(unsigned int)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:mlockall]]]*/

/*[[[head:munlockall,hash:CRC-32=0xc4a643fc]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.mman.munlockall") int
NOTHROW_NCX(LIBCCALL libc_munlockall)(void)
/*[[[body:munlockall]]]*/
{
	errno_t result;
	result = sys_munlockall();
	return libc_seterrno_syserr(result);
}
/*[[[end:munlockall]]]*/

/*[[[head:shm_open,hash:CRC-32=0xf5e38312]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.system.mman.shm_open") int
NOTHROW_RPC(LIBCCALL libc_shm_open)(char const *name,
                                    oflag_t oflags,
                                    mode_t mode)
/*[[[body:shm_open]]]*/
{
	CRT_UNIMPLEMENTED("shm_open"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:shm_open]]]*/

/*[[[head:shm_unlink,hash:CRC-32=0x25c99c5]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.system.mman.shm_unlink") int
NOTHROW_RPC(LIBCCALL libc_shm_unlink)(char const *name)
/*[[[body:shm_unlink]]]*/
{
	CRT_UNIMPLEMENTED("shm_unlink"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:shm_unlink]]]*/

/*[[[head:madvise,hash:CRC-32=0xf32e87f2]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.system.mman.madvise") int
NOTHROW_NCX(LIBCCALL libc_madvise)(void *addr,
                                   size_t len,
                                   int advice)
/*[[[body:madvise]]]*/
{
	errno_t result;
	result = sys_madvise(addr,
	                     len,
	                     (syscall_ulong_t)(unsigned int)advice);
	return libc_seterrno_syserr(result);
}
/*[[[end:madvise]]]*/

/*[[[head:mincore,hash:CRC-32=0xe025e057]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.system.mman.mincore") int
NOTHROW_NCX(LIBCCALL libc_mincore)(void *start,
                                   size_t len,
                                   unsigned char *vec)
/*[[[body:mincore]]]*/
{
	errno_t result;
	result = sys_mincore(start,
	                     len,
	                     (uint8_t *)vec);
	return libc_seterrno_syserr(result);
}
/*[[[end:mincore]]]*/

/*[[[head:mmap64,hash:CRC-32=0xf1bcecd8]]]*/
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_mmap64, libc_mmap);
#else
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.heap.mman.mmap64") void *
NOTHROW_NCX(LIBCCALL libc_mmap64)(void *addr,
                                  size_t len,
                                  int prot,
                                  int flags,
                                  fd_t fd,
                                  off64_t offset)
/*[[[body:mmap64]]]*/
{
	void *result;
#if __SIZEOF_SYSCALL_LONG_T__ < 8
	if ((pos64_t)offset > UINT32_MAX) {
		uint64_t offset64 = (uint64_t)offset;
		result = sys_mmap(addr,
		                  len,
		                  (syscall_ulong_t)(unsigned int)prot,
		                  (syscall_ulong_t)(unsigned int)flags | MAP_OFFSET64_POINTER,
		                  fd,
		                  (syscall_ulong_t)&offset64);
	} else
#endif
	{
		result = sys_mmap(addr,
		                  len,
		                  (syscall_ulong_t)(unsigned int)prot,
		                  (syscall_ulong_t)(unsigned int)flags,
		                  fd,
		                  (syscall_ulong_t)(syscall_slong_t)offset);
	}
	return libc_seterrno_syserr2(result, MAP_FAILED);
}
#endif /* MAGIC:alias */
/*[[[end:mmap64]]]*/

/*[[[head:posix_madvise,hash:CRC-32=0x3cbcf0e2]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.system.mman.posix_madvise") int
NOTHROW_NCX(LIBCCALL libc_posix_madvise)(void *addr,
                                         size_t len,
                                         int advice)
/*[[[body:posix_madvise]]]*/
{
	CRT_UNIMPLEMENTED("posix_madvise"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:posix_madvise]]]*/

/*[[[head:mremap,hash:CRC-32=0xd559c1d0]]]*/
/* @param flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.heap.mman.mremap") void *
NOTHROW_NCX(VLIBCCALL libc_mremap)(void *addr,
                                   size_t old_len,
                                   size_t new_len,
                                   int flags,
                                   ... /* void *new_address */)
/*[[[body:mremap]]]*/
{
	void *result;
	va_list args;
	va_start(args, flags);
	result = sys_mremap(addr,
	                    old_len,
	                    new_len,
	                    (syscall_ulong_t)(unsigned int)flags,
	                    va_arg(args, void *));
	va_end(args);
	return libc_seterrno_syserr2(result, MAP_FAILED);
}
/*[[[end:mremap]]]*/

/*[[[head:remap_file_pages,hash:CRC-32=0xd5e4d222]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.system.mman.remap_file_pages") int
NOTHROW_NCX(LIBCCALL libc_remap_file_pages)(void *start,
                                            size_t size,
                                            int prot,
                                            size_t pgoff,
                                            int flags)
/*[[[body:remap_file_pages]]]*/
{
	errno_t result;
	result = sys_remap_file_pages(start,
	                              size,
	                              (syscall_ulong_t)(unsigned int)prot,
	                              pgoff,
	                              (syscall_ulong_t)(unsigned int)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:remap_file_pages]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xf9f23ecd]]]*/
#undef mremap
DEFINE_PUBLIC_WEAK_ALIAS(mmap, libc_mmap);
DEFINE_PUBLIC_WEAK_ALIAS(munmap, libc_munmap);
DEFINE_PUBLIC_WEAK_ALIAS(mprotect, libc_mprotect);
DEFINE_PUBLIC_WEAK_ALIAS(msync, libc_msync);
DEFINE_PUBLIC_WEAK_ALIAS(mlock, libc_mlock);
DEFINE_PUBLIC_WEAK_ALIAS(munlock, libc_munlock);
DEFINE_PUBLIC_WEAK_ALIAS(mlockall, libc_mlockall);
DEFINE_PUBLIC_WEAK_ALIAS(munlockall, libc_munlockall);
DEFINE_PUBLIC_WEAK_ALIAS(shm_open, libc_shm_open);
DEFINE_PUBLIC_WEAK_ALIAS(shm_unlink, libc_shm_unlink);
DEFINE_PUBLIC_WEAK_ALIAS(madvise, libc_madvise);
DEFINE_PUBLIC_WEAK_ALIAS(__madvise, libc_madvise);
DEFINE_PUBLIC_WEAK_ALIAS(mincore, libc_mincore);
DEFINE_PUBLIC_WEAK_ALIAS(mmap64, libc_mmap64);
DEFINE_PUBLIC_WEAK_ALIAS(posix_madvise, libc_posix_madvise);
DEFINE_PUBLIC_WEAK_ALIAS(mremap, libc_mremap);
DEFINE_PUBLIC_WEAK_ALIAS(remap_file_pages, libc_remap_file_pages);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_MMAN_C */
