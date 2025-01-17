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
#ifndef GUARD_LIBC_USER_SYS_EVENTFD_C
#define GUARD_LIBC_USER_SYS_EVENTFD_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include "sys.eventfd.h"

DECL_BEGIN

/*[[[head:libc_eventfd,hash:CRC-32=0xbb3ee8f0]]]*/
/* >> eventfd(2)
 * Construct a new kernel event object, and return a handle for it.
 * @param: count: The initial # of available events.
 * @param: flags: Set of `EFD_*'
 * @return: * : The newly constructed file handle. */
INTERN ATTR_SECTION(".text.crt.sched.eventfd") WUNUSED fd_t
NOTHROW_NCX(LIBCCALL libc_eventfd)(__STDC_UINT_AS_SIZE_T count,
                                   __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_eventfd]]]*/
{
	fd_t result;
	result = sys_eventfd2((syscall_ulong_t)count,
	                      (syscall_ulong_t)flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_eventfd]]]*/

/*[[[start:exports,hash:CRC-32=0x21ee4a3a]]]*/
DEFINE_PUBLIC_ALIAS_P(eventfd,libc_eventfd,WUNUSED,fd_t,NOTHROW_NCX,LIBCCALL,(__STDC_UINT_AS_SIZE_T count, __STDC_INT_AS_UINT_T flags),(count,flags));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_EVENTFD_C */
