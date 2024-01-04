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
#ifndef GUARD_LIBC_USER_PTY_C
#define GUARD_LIBC_USER_PTY_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>

#include "pty.h"

DECL_BEGIN

/*[[[head:libc_openpty,hash:CRC-32=0x65da3c1]]]*/
/* >> openpty(2)
 * Create  a  new  ptty (psuedo  tty),  storing the  handles  for the
 * master/slave adapters in  `*amaster' and `*aslave'.  Additionally,
 * the caller  may specific  the  initial terminal  settings  `termp'
 * and  window size  `winp', as well  as a location  where the kernel
 * should store the  filename of  the PTY master  socket (as  already
 * returned in `*amaster'). Note that the max length of this filename
 * is implementation defined, with no way for the use to specify  how
 * much space is available in the passed buffer. As such, a  portable
 * application can only ever pass `NULL' for this value.
 *
 * On KOS, the value written to `name' is the absolute filename of
 * the master-device in the `/dev' filesystem, which usually means
 * that the written filename is something like `/dev/ptyp0'.
 *
 * NOTE: On KOS, this function is a system call, though in other
 *       operating system it is often implemented via `open(2)',
 *       possibly combined with `ioctl(2)'. */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_OUT(1) ATTR_OUT(2) ATTR_OUT_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_openpty)(fd_t *amaster,
                                   fd_t *aslave,
                                   char *name,
                                   struct termios const *termp,
                                   struct winsize const *winp)
/*[[[body:libc_openpty]]]*/
{
	errno_t result;
	result = sys_openpty(amaster,
	                     aslave,
	                     name,
	                     termp,
	                     winp);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_openpty]]]*/



/*[[[start:exports,hash:CRC-32=0x624b46dc]]]*/
DEFINE_PUBLIC_ALIAS(openpty, libc_openpty);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_PTY_C */
