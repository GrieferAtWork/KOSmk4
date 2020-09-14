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
#ifndef GUARD_LIBC_USER_TERMIOS_C
#define GUARD_LIBC_USER_TERMIOS_C 1

#include "../api.h"
/**/

#include <sys/ioctl.h>

#include <unistd.h>

#include "termios.h"

DECL_BEGIN

/*[[[head:libc_tcgetattr,hash:CRC-32=0x24560589]]]*/
/* Get terminal attributes */
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_tcgetattr)(fd_t fd,
                                     struct termios *__restrict termios_p)
/*[[[body:libc_tcgetattr]]]*/
{
	return (int)ioctl(fd, TCGETA, termios_p);
}
/*[[[end:libc_tcgetattr]]]*/

/*[[[head:libc_tcsetattr,hash:CRC-32=0x260b07a5]]]*/
/* Set terminal attributes
 * @param: optional_actions: One of `TCSANOW', `TCSADRAIN' or `TCSAFLUSH' */
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((3)) int
NOTHROW_NCX(LIBCCALL libc_tcsetattr)(fd_t fd,
                                     __STDC_INT_AS_UINT_T optional_actions,
                                     struct termios const *__restrict termios_p)
/*[[[body:libc_tcsetattr]]]*/
{
	int cmd;
	switch (optional_actions) {

	case TCSANOW:
		cmd = TCSETA;
		break;

	case TCSADRAIN:
		cmd = TCSETAW;
		break;

	case TCSAFLUSH:
		cmd = TCSETAF;
		break;

	default:
		return libc_seterrno(EINVAL);
	}
	return (int)ioctl(fd, cmd, termios_p);
}
/*[[[end:libc_tcsetattr]]]*/

/*[[[head:libc_tcsendbreak,hash:CRC-32=0xbb1825dc]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_tcsendbreak)(fd_t fd,
                                       int duration)
/*[[[body:libc_tcsendbreak]]]*/
{
	return (int)ioctl(fd, TCSBRKP, duration);
}
/*[[[end:libc_tcsendbreak]]]*/

/*[[[head:libc_tcdrain,hash:CRC-32=0x139938ae]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_RPC(LIBCCALL libc_tcdrain)(fd_t fd)
/*[[[body:libc_tcdrain]]]*/
{
	return (int)ioctl(fd, TCSBRK, 1);
}
/*[[[end:libc_tcdrain]]]*/

/*[[[head:libc_tcflush,hash:CRC-32=0xaf207f31]]]*/
/* @param: queue_selector: One of `TCIFLUSH', `TCOFLUSH' or `TCIOFLUSH' */
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_tcflush)(fd_t fd,
                                   __STDC_INT_AS_UINT_T queue_selector)
/*[[[body:libc_tcflush]]]*/
{
	return (int)ioctl(fd, TCFLSH, queue_selector);
}
/*[[[end:libc_tcflush]]]*/

/*[[[head:libc_tcflow,hash:CRC-32=0xdfdb05e3]]]*/
/* @param: action: One of `TCOOFF', `TCOON', `TCIOFF', `TCION' */
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_tcflow)(fd_t fd,
                                  __STDC_INT_AS_UINT_T action)
/*[[[body:libc_tcflow]]]*/
{
	return (int)ioctl(fd, TCXONC, action);
}
/*[[[end:libc_tcflow]]]*/

/*[[[head:libc_tcgetsid,hash:CRC-32=0x7dcf9df9]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") pid_t
NOTHROW_NCX(LIBCCALL libc_tcgetsid)(fd_t fd)
/*[[[body:libc_tcgetsid]]]*/
{
	pid_t result;
	if unlikely(ioctl(fd, TIOCGSID, &result) < 0)
		result = -1;
	return result;
}
/*[[[end:libc_tcgetsid]]]*/

/*[[[head:libc_tcsetsid,hash:CRC-32=0x5188e6d2]]]*/
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_tcsetsid)(fd_t fd,
                                    pid_t pid)
/*[[[body:libc_tcsetsid]]]*/
{
	int result;
	if unlikely(pid != getsid(0)) {
		result = libc_seterrno(EINVAL);
	} else {
		result = ioctl(fd, TIOCSCTTY, NULL);
	}
	return result;
}
/*[[[end:libc_tcsetsid]]]*/


/*[[[start:exports,hash:CRC-32=0x8ab10d80]]]*/
DEFINE_PUBLIC_ALIAS(tcgetattr, libc_tcgetattr);
DEFINE_PUBLIC_ALIAS(tcsetattr, libc_tcsetattr);
DEFINE_PUBLIC_ALIAS(tcsendbreak, libc_tcsendbreak);
DEFINE_PUBLIC_ALIAS(tcdrain, libc_tcdrain);
DEFINE_PUBLIC_ALIAS(tcflush, libc_tcflush);
DEFINE_PUBLIC_ALIAS(tcflow, libc_tcflow);
DEFINE_PUBLIC_ALIAS(tcgetsid, libc_tcgetsid);
DEFINE_PUBLIC_ALIAS(tcsetsid, libc_tcsetsid);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_TERMIOS_C */
