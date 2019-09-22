/* HASH CRC-32:0xef722f46 */
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
#ifndef GUARD_LIBC_AUTO_TERMIOS_C
#define GUARD_LIBC_AUTO_TERMIOS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "termios.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.cfgetospeed") speed_t
NOTHROW_NCX(LIBCCALL libc_cfgetospeed)(struct termios const *__restrict termios_p) {
#line 52 "kos/src/libc/magic/termios.c"
	return termios_p->c_ospeed;
}

INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.cfgetispeed") speed_t
NOTHROW_NCX(LIBCCALL libc_cfgetispeed)(struct termios const *__restrict termios_p) {
#line 56 "kos/src/libc/magic/termios.c"
	return termios_p->c_ispeed;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.cfsetospeed") int
NOTHROW_NCX(LIBCCALL libc_cfsetospeed)(struct termios *__restrict termios_p,
                                       speed_t speed) {
#line 59 "kos/src/libc/magic/termios.c"
	termios_p->c_ospeed = speed;
	return 0;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.cfsetispeed") int
NOTHROW_NCX(LIBCCALL libc_cfsetispeed)(struct termios *__restrict termios_p,
                                       speed_t speed) {
#line 63 "kos/src/libc/magic/termios.c"
	termios_p->c_ispeed = speed;
	return 0;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.cfsetspeed") int
NOTHROW_NCX(LIBCCALL libc_cfsetspeed)(struct termios *__restrict termios_p,
                                      speed_t speed) {
#line 83 "kos/src/libc/magic/termios.c"
	termios_p->c_ospeed = speed;
	termios_p->c_ispeed = speed;
	return 0;
}

INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.io.tty.cfmakeraw") void
NOTHROW_NCX(LIBCCALL libc_cfmakeraw)(struct termios *__restrict termios_p) {
#line 88 "kos/src/libc/magic/termios.c"
	termios_p->c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
	termios_p->c_oflag &= ~(OPOST);
	termios_p->c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
	termios_p->c_cflag &= ~(CSIZE|PARENB);
	termios_p->c_cflag |= CS8;
	termios_p->c_cc[VMIN]  = 1; /* Read returns when one byte was read. */
	termios_p->c_cc[VTIME] = 0;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(cfgetospeed, libc_cfgetospeed);
DEFINE_PUBLIC_WEAK_ALIAS(cfgetispeed, libc_cfgetispeed);
DEFINE_PUBLIC_WEAK_ALIAS(cfsetospeed, libc_cfsetospeed);
DEFINE_PUBLIC_WEAK_ALIAS(cfsetispeed, libc_cfsetispeed);
DEFINE_PUBLIC_WEAK_ALIAS(cfsetspeed, libc_cfsetspeed);
DEFINE_PUBLIC_WEAK_ALIAS(cfmakeraw, libc_cfmakeraw);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_TERMIOS_C */
