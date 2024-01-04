/* HASH CRC-32:0x81a533b3 */
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
#ifndef GUARD_LIBC_AUTO_PTY_H
#define GUARD_LIBC_AUTO_PTY_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <pty.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_IN_OPT(4) ATTR_IN_OPT(5) ATTR_OUT(1) ATTR_OUT(2) ATTR_OUT_OPT(3) int NOTHROW_NCX(LIBDCALL libd_openpty)(fd_t *amaster, fd_t *aslave, char *name, struct termios const *termp, struct winsize const *winp);
/* >> forkpty(3)
 * A helper for combining `openpty(2)' with `fork(2)' and `login_tty(3)',
 * such  that  the newly  created PTY  is open  under all  std-handles in
 * the newly created child process.
 * Aside from this, this function returns the same as fork(2), that  is
 * it returns in  both the  parent and child  processes, returning  `0'
 * for the child, and the child's PID for the parent (or -1 in only the
 * parent if something went wrong) */
INTDEF ATTR_IN(3) ATTR_IN(4) ATTR_OUT(1) ATTR_OUT_OPT(2) pid_t NOTHROW_NCX(LIBDCALL libd_forkpty)(fd_t *amaster, char *name, struct termios const *termp, struct winsize const *winp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> forkpty(3)
 * A helper for combining `openpty(2)' with `fork(2)' and `login_tty(3)',
 * such  that  the newly  created PTY  is open  under all  std-handles in
 * the newly created child process.
 * Aside from this, this function returns the same as fork(2), that  is
 * it returns in  both the  parent and child  processes, returning  `0'
 * for the child, and the child's PID for the parent (or -1 in only the
 * parent if something went wrong) */
INTDEF ATTR_IN(3) ATTR_IN(4) ATTR_OUT(1) ATTR_OUT_OPT(2) pid_t NOTHROW_NCX(LIBCCALL libc_forkpty)(fd_t *amaster, char *name, struct termios const *termp, struct winsize const *winp);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PTY_H */
