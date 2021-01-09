/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_MMAN_C
#define GUARD_LIBC_USER_SYS_MMAN_C 1
#define _KOS_KERNEL_SOURCE 1 /* MAP_OFFSET64_POINTER */

#include "../api.h"
/**/

#include <asm/pkey.h>
#include <kos/syscalls.h>
#include <sys/mman.h>

#include <stdint.h>
#include <syscall.h>

#include "sys.mman.h"

DECL_BEGIN

/*[[[head:libc_mmap,hash:CRC-32=0x3938e0a4]]]*/
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_STACK | MAP_SYNC |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
INTERN ATTR_SECTION(".text.crt.heap.mman") WUNUSED void *
NOTHROW_NCX(LIBCCALL libc_mmap)(void *addr,
                                size_t len,
                                __STDC_INT_AS_UINT_T prot,
                                __STDC_INT_AS_UINT_T flags,
                                fd_t fd,
                                off_t offset)
/*[[[body:libc_mmap]]]*/
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
/*[[[end:libc_mmap]]]*/

/*[[[head:libc_munmap,hash:CRC-32=0x9a2a58aa]]]*/
/* Unmap memory from `addr...+=len' */
INTERN ATTR_SECTION(".text.crt.heap.mman") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_munmap)(void *addr,
                                  size_t len)
/*[[[body:libc_munmap]]]*/
{
	errno_t result;
	result = sys_munmap(addr, len);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_munmap]]]*/

/*[[[head:libc_mprotect,hash:CRC-32=0x6d731db2]]]*/
/* @param prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE |
 *              PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED |
 *              PROT_GROWSUP | PROT_GROWSDOWN' */
INTERN ATTR_SECTION(".text.crt.system.mman") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_mprotect)(void *addr,
                                    size_t len,
                                    __STDC_INT_AS_UINT_T prot)
/*[[[body:libc_mprotect]]]*/
{
	errno_t result;
	result = sys_mprotect(addr, len, (syscall_ulong_t)(unsigned int)prot);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mprotect]]]*/

/*[[[head:libc_msync,hash:CRC-32=0xfd7a4a5c]]]*/
/* @param flags: Set of `MS_ASYNC | MS_INVALIDATE | MS_SYNC' */
INTERN ATTR_SECTION(".text.crt.system.mman") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_msync)(void *addr,
                                 size_t len,
                                 __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_msync]]]*/
{
	errno_t result;
	result = sys_msync(addr, len, (syscall_ulong_t)(unsigned int)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_msync]]]*/

/*[[[head:libc_mlock,hash:CRC-32=0xc9f34cf2]]]*/
INTERN ATTR_SECTION(".text.crt.system.mman") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_mlock)(void const *addr,
                                 size_t len)
/*[[[body:libc_mlock]]]*/
{
	errno_t result;
#ifdef SYS_mlock
	result = sys_mlock(addr, len);
#else /* SYS_mlock */
	result = sys_mlock2(addr, len, 0);
#endif /* !SYS_mlock */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mlock]]]*/

/*[[[head:libc_munlock,hash:CRC-32=0xf01c7204]]]*/
INTERN ATTR_SECTION(".text.crt.system.mman") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_munlock)(void const *addr,
                                   size_t len)
/*[[[body:libc_munlock]]]*/
{
	errno_t result;
	result = sys_munlock(addr, len);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_munlock]]]*/

/*[[[head:libc_mlockall,hash:CRC-32=0xeb39f473]]]*/
/* @param flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
INTERN ATTR_SECTION(".text.crt.system.mman") int
NOTHROW_NCX(LIBCCALL libc_mlockall)(__STDC_INT_AS_UINT_T flags)
/*[[[body:libc_mlockall]]]*/
{
	errno_t result;
	result = sys_mlockall((syscall_ulong_t)(unsigned int)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mlockall]]]*/

/*[[[head:libc_munlockall,hash:CRC-32=0x616b898c]]]*/
INTERN ATTR_SECTION(".text.crt.system.mman") int
NOTHROW_NCX(LIBCCALL libc_munlockall)(void)
/*[[[body:libc_munlockall]]]*/
{
	errno_t result;
	result = sys_munlockall();
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_munlockall]]]*/

/*[[[head:libc_madvise,hash:CRC-32=0x6ab3bd0b]]]*/
INTERN ATTR_SECTION(".text.crt.system.mman") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_madvise)(void *addr,
                                   size_t len,
                                   __STDC_INT_AS_UINT_T advice)
/*[[[body:libc_madvise]]]*/
{
	errno_t result;
	result = sys_madvise(addr,
	                     len,
	                     (syscall_ulong_t)(unsigned int)advice);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_madvise]]]*/

/*[[[head:libc_mincore,hash:CRC-32=0xb92dc176]]]*/
INTERN ATTR_SECTION(".text.crt.system.mman") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_mincore)(void *start,
                                   size_t len,
                                   unsigned char *vec)
/*[[[body:libc_mincore]]]*/
{
	errno_t result;
	result = sys_mincore(start,
	                     len,
	                     (uint8_t *)vec);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mincore]]]*/

/*[[[head:libc_mmap64,hash:CRC-32=0x67d67e81]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_mmap64, libc_mmap);
#else /* MAGIC:alias */
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_STACK | MAP_SYNC |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
INTERN ATTR_SECTION(".text.crt.heap.mman") WUNUSED void *
NOTHROW_NCX(LIBCCALL libc_mmap64)(void *addr,
                                  size_t len,
                                  __STDC_INT_AS_UINT_T prot,
                                  __STDC_INT_AS_UINT_T flags,
                                  fd_t fd,
                                  off64_t offset)
/*[[[body:libc_mmap64]]]*/
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
#endif /* __SIZEOF_SYSCALL_LONG_T__ < 8 */
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
/*[[[end:libc_mmap64]]]*/

/*[[[head:libc_posix_madvise,hash:CRC-32=0xb62b9980]]]*/
INTERN ATTR_SECTION(".text.crt.system.mman") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_posix_madvise)(void *addr,
                                         size_t len,
                                         __STDC_INT_AS_UINT_T advice)
/*[[[body:libc_posix_madvise]]]*/
/*AUTO*/{
	/* Implement as a no-op, since this function is merely meant as a hint */
	COMPILER_IMPURE();
	(void)addr;
	(void)len;
	(void)advice;
	return 0;
}
/*[[[end:libc_posix_madvise]]]*/


/*[[[head:libc_mremap,hash:CRC-32=0x31cbe7cb]]]*/
/* @param flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
INTERN ATTR_SECTION(".text.crt.heap.mman") void *
NOTHROW_NCX(VLIBCCALL libc_mremap)(void *addr,
                                   size_t old_len,
                                   size_t new_len,
                                   __STDC_INT_AS_UINT_T flags,
                                   ...)
/*[[[body:libc_mremap]]]*/
{
	void *result;
	va_list args;
	va_start(args, flags);
	result = sys_mremap(addr, old_len, new_len,
	                    (syscall_ulong_t)(unsigned int)flags,
	                    va_arg(args, void *));
	va_end(args);
	return libc_seterrno_syserr2(result, MAP_FAILED);
}
/*[[[end:libc_mremap]]]*/

/*[[[head:libc_remap_file_pages,hash:CRC-32=0xd51bfd2e]]]*/
INTERN ATTR_SECTION(".text.crt.system.mman") int
NOTHROW_NCX(LIBCCALL libc_remap_file_pages)(void *start,
                                            size_t size,
                                            __STDC_INT_AS_UINT_T prot,
                                            size_t pgoff,
                                            __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_remap_file_pages]]]*/
{
	errno_t result;
	result = sys_remap_file_pages(start,
	                              size,
	                              (syscall_ulong_t)(unsigned int)prot,
	                              pgoff,
	                              (syscall_ulong_t)(unsigned int)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_remap_file_pages]]]*/

/*[[[head:libc_memfd_create,hash:CRC-32=0xb3c4f089]]]*/
INTERN ATTR_SECTION(".text.crt.system.mman") fd_t
NOTHROW_NCX(LIBCCALL libc_memfd_create)(char const *name,
                                        unsigned int flags)
/*[[[body:libc_memfd_create]]]*/
{
	fd_t result;
	result = sys_memfd_create(name, (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_memfd_create]]]*/

/*[[[head:libc_mlock2,hash:CRC-32=0xa7787755]]]*/
INTERN ATTR_SECTION(".text.crt.system.mman") int
NOTHROW_NCX(LIBCCALL libc_mlock2)(void const *addr,
                                  size_t length,
                                  unsigned int flags)
/*[[[body:libc_mlock2]]]*/
{
	errno_t result;
	result = sys_mlock2(addr, length, (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mlock2]]]*/

/*[[[head:libc_pkey_alloc,hash:CRC-32=0xc828dc13]]]*/
#ifdef __ARCH_HAVE_PKEY
INTERN ATTR_SECTION(".text.crt.system.mman") int
NOTHROW_NCX(LIBCCALL libc_pkey_alloc)(unsigned int flags,
                                      unsigned int access_rights)
/*[[[body:libc_pkey_alloc]]]*/
{
	syscall_slong_t result;
	result = sys_pkey_alloc((syscall_ulong_t)flags,
	                        (syscall_ulong_t)access_rights);
	return (int)libc_seterrno_syserr(result);
}
#endif /* MAGIC:impl_if */
/*[[[end:libc_pkey_alloc]]]*/



/*[[[head:libc_pkey_free,hash:CRC-32=0x75ef0f67]]]*/
#ifdef __ARCH_HAVE_PKEY
INTERN ATTR_SECTION(".text.crt.system.mman") int
NOTHROW_NCX(LIBCCALL libc_pkey_free)(int pkey)
/*[[[body:libc_pkey_free]]]*/
{
	errno_t error;
	error = sys_pkey_free((syscall_ulong_t)(unsigned int)pkey);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:impl_if */
/*[[[end:libc_pkey_free]]]*/

/*[[[head:libc_pkey_mprotect,hash:CRC-32=0x51b21a55]]]*/
#ifdef __ARCH_HAVE_PKEY
INTERN ATTR_SECTION(".text.crt.system.mman") int
NOTHROW_NCX(LIBCCALL libc_pkey_mprotect)(void *addr,
                                         size_t len,
                                         __STDC_INT_AS_UINT_T prot,
                                         int pkey)
/*[[[body:libc_pkey_mprotect]]]*/
{
	errno_t error;
	error = sys_pkey_mprotect(addr, len, (syscall_ulong_t)prot,
	                          (syscall_ulong_t)(unsigned int)pkey);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:impl_if */
/*[[[end:libc_pkey_mprotect]]]*/



/*[[[start:exports,hash:CRC-32=0x5df15eb4]]]*/
DEFINE_PUBLIC_ALIAS(mmap, libc_mmap);
DEFINE_PUBLIC_ALIAS(munmap, libc_munmap);
DEFINE_PUBLIC_ALIAS(mprotect, libc_mprotect);
DEFINE_PUBLIC_ALIAS(msync, libc_msync);
DEFINE_PUBLIC_ALIAS(mlock, libc_mlock);
DEFINE_PUBLIC_ALIAS(munlock, libc_munlock);
DEFINE_PUBLIC_ALIAS(mlockall, libc_mlockall);
DEFINE_PUBLIC_ALIAS(munlockall, libc_munlockall);
DEFINE_PUBLIC_ALIAS(__madvise, libc_madvise);
DEFINE_PUBLIC_ALIAS(madvise, libc_madvise);
DEFINE_PUBLIC_ALIAS(mincore, libc_mincore);
DEFINE_PUBLIC_ALIAS(mmap64, libc_mmap64);
DEFINE_PUBLIC_ALIAS(posix_madvise, libc_posix_madvise);
DEFINE_PUBLIC_ALIAS(mremap, libc_mremap);
DEFINE_PUBLIC_ALIAS(remap_file_pages, libc_remap_file_pages);
DEFINE_PUBLIC_ALIAS(memfd_create, libc_memfd_create);
DEFINE_PUBLIC_ALIAS(mlock2, libc_mlock2);
#include <asm/pkey.h>
#ifdef __ARCH_HAVE_PKEY
DEFINE_PUBLIC_ALIAS(pkey_alloc, libc_pkey_alloc);
DEFINE_PUBLIC_ALIAS(pkey_free, libc_pkey_free);
DEFINE_PUBLIC_ALIAS(pkey_mprotect, libc_pkey_mprotect);
#endif /* __ARCH_HAVE_PKEY */
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_MMAN_C */
