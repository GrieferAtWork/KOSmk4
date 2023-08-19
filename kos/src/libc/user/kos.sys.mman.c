/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_KOS_SYS_MMAN_C
#define GUARD_LIBC_USER_KOS_SYS_MMAN_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

/**/
#include "kos.sys.mman.h"

DECL_BEGIN

/*[[[skip:libc_MMap]]]*/
/*[[[skip:libc_MUnmap]]]*/
/*[[[skip:libc_MProtect]]]*/
/*[[[skip:libc_MSync]]]*/
/*[[[skip:libc_MLock]]]*/
/*[[[skip:libc_MUnlock]]]*/
/*[[[skip:libc_MLockAll]]]*/
/*[[[skip:libc_MUnlockAll]]]*/
/*[[[skip:libc_MAdvise]]]*/
/*[[[skip:libc_MInCore]]]*/
/*[[[skip:libc_MMap64]]]*/
/*[[[skip:libc_MRemap]]]*/
/*[[[skip:libc_RemapFilePages]]]*/
/*[[[skip:libc_MemFdCreate]]]*/
/*[[[skip:libc_MLock2]]]*/
/*[[[skip:libc_PKeyAlloc]]]*/
/*[[[skip:libc_PKeyFree]]]*/
/*[[[skip:libc_PKeyMProtect]]]*/

#if __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__
DEFINE_PUBLIC_ALIAS(MMap64, libc_MMap64);
INTERN ATTR_SECTION(".text.crt.except.heap.mman") WUNUSED void *
(LIBCCALL libc_MMap64)(void *addr, size_t len,
                       __STDC_INT_AS_UINT_T prot,
                       __STDC_INT_AS_UINT_T flags, fd_t fd,
                       pos64_t offset) THROWS(...) {
	void *result;
#if __SIZEOF_SYSCALL_LONG_T__ < 8
	if ((pos64_t)offset > UINT32_MAX) {
		result = sys_Xmmap(addr,
		                   len,
		                   (syscall_ulong_t)(unsigned int)prot,
		                   (syscall_ulong_t)(unsigned int)flags | MAP_OFFSET64_POINTER,
		                   fd,
		                   (syscall_ulong_t)&offset);
	} else
#endif /* __SIZEOF_SYSCALL_LONG_T__ < 8 */
	{
		result = sys_Xmmap(addr,
		                   len,
		                   (syscall_ulong_t)(unsigned int)prot,
		                   (syscall_ulong_t)(unsigned int)flags,
		                   fd,
		                   (syscall_ulong_t)(syscall_slong_t)offset);
	}
	return result;
}
#endif /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */


/*[[[head:libc_PosixMAdvise,hash:CRC-32=0xa6496edc]]]*/
/* >> posix_madvise(3)
 * Wrapper around `madvise(2)'
 * @param: advice: One of `POSIX_MADV_*' */
INTERN ATTR_SECTION(".text.crt.except.system.mman") ATTR_ACCESS_NONE(1) void
(LIBCCALL libc_PosixMAdvise)(void *addr,
                             size_t len,
                             __STDC_INT_AS_UINT_T advice) THROWS(...)
/*[[[body:libc_PosixMAdvise]]]*/
/*AUTO*/{
	/* Implement as a no-op, since this function is merely meant as a hint */
	COMPILER_IMPURE();
	(void)addr;
	(void)len;
	(void)advice;
}
/*[[[end:libc_PosixMAdvise]]]*/

/*[[[start:exports,hash:CRC-32=0x378d1d]]]*/
DEFINE_PUBLIC_ALIAS(PosixMAdvise, libc_PosixMAdvise);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_SYS_MMAN_C */
