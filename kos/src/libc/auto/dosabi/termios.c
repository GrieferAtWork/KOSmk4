/* HASH CRC-32:0x302f39b7 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_TERMIOS_C
#define GUARD_LIBC_AUTO_DOSABI_TERMIOS_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/termios.h"

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.dos.io.tty") ATTR_PURE WUNUSED NONNULL((1)) speed_t
NOTHROW_NCX(LIBDCALL libd_cfgetospeed)(struct termios const *__restrict termios_p) {
	return libc_cfgetospeed(termios_p);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") ATTR_PURE WUNUSED NONNULL((1)) speed_t
NOTHROW_NCX(LIBDCALL libd_cfgetispeed)(struct termios const *__restrict termios_p) {
	return libc_cfgetispeed(termios_p);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_cfsetospeed)(struct termios *__restrict termios_p,
                                       speed_t speed) {
	return libc_cfsetospeed(termios_p, speed);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_cfsetispeed)(struct termios *__restrict termios_p,
                                       speed_t speed) {
	return libc_cfsetispeed(termios_p, speed);
}
/* Get terminal attributes */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") NONNULL((2)) int
NOTHROW_NCX(LIBDCALL libd_tcgetattr)(fd_t fd,
                                     struct termios *__restrict termios_p) {
	return libc_tcgetattr(fd, termios_p);
}
/* Set terminal attributes
 * @param: optional_actions: One of `TCSANOW', `TCSADRAIN' or `TCSAFLUSH' */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") NONNULL((3)) int
NOTHROW_NCX(LIBDCALL libd_tcsetattr)(fd_t fd,
                                     __STDC_INT_AS_UINT_T optional_actions,
                                     struct termios const *__restrict termios_p) {
	return libc_tcsetattr(fd, optional_actions, termios_p);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") int
NOTHROW_NCX(LIBDCALL libd_tcsendbreak)(fd_t fd,
                                       int duration) {
	return libc_tcsendbreak(fd, duration);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") int
NOTHROW_RPC(LIBDCALL libd_tcdrain)(fd_t fd) {
	return libc_tcdrain(fd);
}
/* @param: queue_selector: One of `TCIFLUSH', `TCOFLUSH' or `TCIOFLUSH' */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") int
NOTHROW_NCX(LIBDCALL libd_tcflush)(fd_t fd,
                                   __STDC_INT_AS_UINT_T queue_selector) {
	return libc_tcflush(fd, queue_selector);
}
/* @param: action: One of `TCOOFF', `TCOON', `TCIOFF', `TCION' */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") int
NOTHROW_NCX(LIBDCALL libd_tcflow)(fd_t fd,
                                  __STDC_INT_AS_UINT_T action) {
	return libc_tcflow(fd, action);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") pid_t
NOTHROW_NCX(LIBDCALL libd_tcgetsid)(fd_t fd) {
	return libc_tcgetsid(fd);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") int
NOTHROW_NCX(LIBDCALL libd_tcsetsid)(fd_t fd,
                                    pid_t pid) {
	return libc_tcsetsid(fd, pid);
}
INTERN ATTR_SECTION(".text.crt.dos.io.tty") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_cfsetspeed)(struct termios *__restrict termios_p,
                                      speed_t speed) {
	return libc_cfsetspeed(termios_p, speed);
}
/* Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
 * This entails the CANON and all control characters being disabled, as well as
 * any sort of input/output text processing no longer taking place. */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_cfmakeraw)(struct termios *__restrict termios_p) {
	libc_cfmakeraw(termios_p);
}
/* Set ~sane~ mode for the given `termios_p' (out-only; meaning that `termios_p' gets initialized by this function)
 * Sane here refers to setting all values to their defaults, as they are defined in <sys/ttydefaults.h> */
INTERN ATTR_SECTION(".text.crt.dos.io.tty") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_cfmakesane)(struct termios *__restrict termios_p) {
	libc_cfmakesane(termios_p);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$cfgetospeed, libd_cfgetospeed);
DEFINE_PUBLIC_ALIAS(DOS$cfgetispeed, libd_cfgetispeed);
DEFINE_PUBLIC_ALIAS(DOS$cfsetospeed, libd_cfsetospeed);
DEFINE_PUBLIC_ALIAS(DOS$cfsetispeed, libd_cfsetispeed);
DEFINE_PUBLIC_ALIAS(DOS$tcgetattr, libd_tcgetattr);
DEFINE_PUBLIC_ALIAS(DOS$tcsetattr, libd_tcsetattr);
DEFINE_PUBLIC_ALIAS(DOS$tcsendbreak, libd_tcsendbreak);
DEFINE_PUBLIC_ALIAS(DOS$tcdrain, libd_tcdrain);
DEFINE_PUBLIC_ALIAS(DOS$tcflush, libd_tcflush);
DEFINE_PUBLIC_ALIAS(DOS$tcflow, libd_tcflow);
DEFINE_PUBLIC_ALIAS(DOS$tcgetsid, libd_tcgetsid);
DEFINE_PUBLIC_ALIAS(DOS$tcsetsid, libd_tcsetsid);
DEFINE_PUBLIC_ALIAS(DOS$cfsetspeed, libd_cfsetspeed);
DEFINE_PUBLIC_ALIAS(DOS$cfmakeraw, libd_cfmakeraw);
DEFINE_PUBLIC_ALIAS(DOS$cfmakesane, libd_cfmakesane);

#endif /* !GUARD_LIBC_AUTO_DOSABI_TERMIOS_C */
