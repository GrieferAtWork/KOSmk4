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
#ifndef GUARD_LIBC_USER_SYS_FILE_C
#define GUARD_LIBC_USER_SYS_FILE_C 1

#include "../api.h"
#include "sys.file.h"

#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_flock,hash:CRC-32=0x9beb2afa]]]*/
/* Apply or remove an advisory lock, according to OPERATION, on the file FD refers to */
INTERN int
NOTHROW_RPC(LIBCCALL libc_flock)(fd_t fd,
                                 __STDC_INT_AS_UINT_T operation)
/*[[[body:libc_flock]]]*/
{
	errno_t result;
	result = sys_flock(fd, operation);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_flock]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x69d162ac]]]*/
DEFINE_PUBLIC_ALIAS(flock, libc_flock);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_FILE_C */
