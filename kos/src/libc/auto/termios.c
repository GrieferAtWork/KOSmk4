/* HASH CRC-32:0xed2ae6d6 */
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
#ifndef GUARD_LIBC_AUTO_TERMIOS_C
#define GUARD_LIBC_AUTO_TERMIOS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "termios.h"
#include "../user/string.h"
#include "../user/sys.ioctl.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_PURE WUNUSED NONNULL((1)) speed_t
NOTHROW_NCX(LIBCCALL libc_cfgetospeed)(struct termios const *__restrict termios_p) {
	return termios_p->c_ospeed;
}
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_PURE WUNUSED NONNULL((1)) speed_t
NOTHROW_NCX(LIBCCALL libc_cfgetispeed)(struct termios const *__restrict termios_p) {
	return termios_p->c_ispeed;
}
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_cfsetospeed)(struct termios *__restrict termios_p,
                                       speed_t speed) {
	termios_p->c_ospeed = speed;
	return 0;
}
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_cfsetispeed)(struct termios *__restrict termios_p,
                                       speed_t speed) {
	termios_p->c_ispeed = speed;
	return 0;
}
/* >> tcgetattr(3)
 * Get terminal attributes */
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_tcgetattr)(fd_t fd,
                                     struct termios *__restrict termios_p) {
	return (int)libc_ioctl(fd, __TCGETA, termios_p);
}
#include <asm/os/tty.h>
#include <asm/os/termios.h>
#include <libc/errno.h>
/* >> tcsetattr(3)
 * Set terminal attributes
 * @param: optional_actions: One of `TCSANOW', `TCSADRAIN' or `TCSAFLUSH' */
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((3)) int
NOTHROW_NCX(LIBCCALL libc_tcsetattr)(fd_t fd,
                                     __STDC_INT_AS_UINT_T optional_actions,
                                     struct termios const *__restrict termios_p) {
	int cmd;
	switch (optional_actions) {

#if defined(__TCSANOW) && defined(__TCSETA)
	case __TCSANOW:
		cmd = __TCSETA;
		break;
#endif /* __TCSANOW && __TCSETA */

#if defined(__TCSADRAIN) && defined(__TCSETAW)
	case __TCSADRAIN:
		cmd = __TCSETAW;
		break;
#endif /* __TCSADRAIN && __TCSETAW */

#if defined(__TCSAFLUSH) && defined(__TCSETAF)
	case __TCSAFLUSH:
		cmd = __TCSETAF;
		break;
#endif /* __TCSAFLUSH && __TCSETAF */

	default:
#ifdef EINVAL
		return __libc_seterrno(EINVAL);
#else /* EINVAL */
		return __libc_seterrno(1);
#endif /* !EINVAL */
	}
	return (int)libc_ioctl(fd, cmd, termios_p);
}
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_tcsendbreak)(fd_t fd,
                                       int duration) {
	return (int)libc_ioctl(fd, __TCSBRKP, duration);
}
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_RPC(LIBCCALL libc_tcdrain)(fd_t fd) {
	return (int)libc_ioctl(fd, __TCSBRK, 1);
}
/* @param: queue_selector: One of `TCIFLUSH', `TCOFLUSH' or `TCIOFLUSH' */
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_tcflush)(fd_t fd,
                                   __STDC_INT_AS_UINT_T queue_selector) {
	return (int)libc_ioctl(fd, __TCFLSH, queue_selector);
}
/* @param: action: One of `TCOOFF', `TCOON', `TCIOFF', `TCION' */
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_tcflow)(fd_t fd,
                                  __STDC_INT_AS_UINT_T action) {
	return (int)libc_ioctl(fd, __TCXONC, action);
}
INTERN ATTR_SECTION(".text.crt.io.tty") pid_t
NOTHROW_NCX(LIBCCALL libc_tcgetsid)(fd_t fd) {
	pid_t result;
	if unlikely(libc_ioctl(fd, __TIOCGSID, &result) < 0)
		result = -1;
	return result;
}
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.io.tty") int
NOTHROW_NCX(LIBCCALL libc_tcsetsid)(fd_t fd,
                                    pid_t pid) {
	int result;
	if unlikely(pid != libc_getsid(0)) {
#ifdef EINVAL
		result = __libc_seterrno(EINVAL);
#else /* EINVAL */
		result = __libc_seterrno(1);
#endif /* !EINVAL */
	} else {
		result = libc_ioctl(fd, __TIOCSCTTY, NULL);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_cfsetspeed)(struct termios *__restrict termios_p,
                                      speed_t speed) {
	termios_p->c_ospeed = speed;
	termios_p->c_ispeed = speed;
	return 0;
}
#include <asm/os/termios.h>
/* >> cfmakeraw(3)
 * Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
 * This entails the CANON and all control characters being disabled, as well as
 * any sort of input/output text processing no longer taking place. */
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_cfmakeraw)(struct termios *__restrict termios_p) {
	/* As documented here: http://man7.org/linux/man-pages/man3/termios.3.html
	 * Note that the following additions were made:
	 *  - Clear `IXOFF' (ensuring that TTY output can be streamed)
	 *  - Always set `CREAD' (ensuring that data can be received) */

/*[[[deemon
local ops = {
	("c_iflag", false, ["IGNBRK", "BRKINT", "PARMRK", "ISTRIP", "INLCR", "IGNCR", "ICRNL", "IXON", "IXOFF"]),
	("c_oflag", false, ["OPOST"]),
	("c_lflag", false, ["ECHO", "ECHONL", "ICANON", "ISIG", "IEXTEN"]),
	("c_cflag", false, ["CSIZE", "PARENB"]),
	("c_cflag", true,  ["CS8", "CREAD"]),
};
for (local field, add, flags: ops) {
	print("	/" "* ", field, " (", add ? "addend" : "remove", ")", " *" "/");
	print("@@pp_if "),;
	print(" || ".join(for (local f: flags) "defined(__" + f + ")"), "@@");
	for (local f: flags) {
		print("@@pp_ifndef __PRIVATE_", f, "@@");
		print("@@pp_ifdef __", f, "@@");
		print("#define __PRIVATE_", f, " __", f);
		print("@@pp_else@@");
		print("#define __PRIVATE_", f, " 0");
		print("@@pp_endif@@");
		print("@@pp_endif@@");
	}
	print("	termios_p->@", field, "@ ", add ? "|= " : "&= ~", "("),;
	print(" | ".join(for (local f: flags) "__PRIVATE_" + f), ");");
	print("@@pp_endif@@");
	print;
}
]]]*/
	/* c_iflag (remove) */
#if defined(__IGNBRK) || defined(__BRKINT) || defined(__PARMRK) || defined(__ISTRIP) || defined(__INLCR) || defined(__IGNCR) || defined(__ICRNL) || defined(__IXON) || defined(__IXOFF)
#ifndef __PRIVATE_IGNBRK
#ifdef __IGNBRK
#define __PRIVATE_IGNBRK __IGNBRK
#else /* __IGNBRK */
#define __PRIVATE_IGNBRK 0
#endif /* !__IGNBRK */
#endif /* !__PRIVATE_IGNBRK */
#ifndef __PRIVATE_BRKINT
#ifdef __BRKINT
#define __PRIVATE_BRKINT __BRKINT
#else /* __BRKINT */
#define __PRIVATE_BRKINT 0
#endif /* !__BRKINT */
#endif /* !__PRIVATE_BRKINT */
#ifndef __PRIVATE_PARMRK
#ifdef __PARMRK
#define __PRIVATE_PARMRK __PARMRK
#else /* __PARMRK */
#define __PRIVATE_PARMRK 0
#endif /* !__PARMRK */
#endif /* !__PRIVATE_PARMRK */
#ifndef __PRIVATE_ISTRIP
#ifdef __ISTRIP
#define __PRIVATE_ISTRIP __ISTRIP
#else /* __ISTRIP */
#define __PRIVATE_ISTRIP 0
#endif /* !__ISTRIP */
#endif /* !__PRIVATE_ISTRIP */
#ifndef __PRIVATE_INLCR
#ifdef __INLCR
#define __PRIVATE_INLCR __INLCR
#else /* __INLCR */
#define __PRIVATE_INLCR 0
#endif /* !__INLCR */
#endif /* !__PRIVATE_INLCR */
#ifndef __PRIVATE_IGNCR
#ifdef __IGNCR
#define __PRIVATE_IGNCR __IGNCR
#else /* __IGNCR */
#define __PRIVATE_IGNCR 0
#endif /* !__IGNCR */
#endif /* !__PRIVATE_IGNCR */
#ifndef __PRIVATE_ICRNL
#ifdef __ICRNL
#define __PRIVATE_ICRNL __ICRNL
#else /* __ICRNL */
#define __PRIVATE_ICRNL 0
#endif /* !__ICRNL */
#endif /* !__PRIVATE_ICRNL */
#ifndef __PRIVATE_IXON
#ifdef __IXON
#define __PRIVATE_IXON __IXON
#else /* __IXON */
#define __PRIVATE_IXON 0
#endif /* !__IXON */
#endif /* !__PRIVATE_IXON */
#ifndef __PRIVATE_IXOFF
#ifdef __IXOFF
#define __PRIVATE_IXOFF __IXOFF
#else /* __IXOFF */
#define __PRIVATE_IXOFF 0
#endif /* !__IXOFF */
#endif /* !__PRIVATE_IXOFF */
	termios_p->c_iflag &= ~(__PRIVATE_IGNBRK | __PRIVATE_BRKINT | __PRIVATE_PARMRK | __PRIVATE_ISTRIP | __PRIVATE_INLCR | __PRIVATE_IGNCR | __PRIVATE_ICRNL | __PRIVATE_IXON | __PRIVATE_IXOFF);
#endif /* __IGNBRK || __BRKINT || __PARMRK || __ISTRIP || __INLCR || __IGNCR || __ICRNL || __IXON || __IXOFF */

	/* c_oflag (remove) */
#ifdef __OPOST
#ifndef __PRIVATE_OPOST

#define __PRIVATE_OPOST __OPOST



#endif /* !__PRIVATE_OPOST */
	termios_p->c_oflag &= ~(__PRIVATE_OPOST);
#endif /* __OPOST */

	/* c_lflag (remove) */
#if defined(__ECHO) || defined(__ECHONL) || defined(__ICANON) || defined(__ISIG) || defined(__IEXTEN)
#ifndef __PRIVATE_ECHO
#ifdef __ECHO
#define __PRIVATE_ECHO __ECHO
#else /* __ECHO */
#define __PRIVATE_ECHO 0
#endif /* !__ECHO */
#endif /* !__PRIVATE_ECHO */
#ifndef __PRIVATE_ECHONL
#ifdef __ECHONL
#define __PRIVATE_ECHONL __ECHONL
#else /* __ECHONL */
#define __PRIVATE_ECHONL 0
#endif /* !__ECHONL */
#endif /* !__PRIVATE_ECHONL */
#ifndef __PRIVATE_ICANON
#ifdef __ICANON
#define __PRIVATE_ICANON __ICANON
#else /* __ICANON */
#define __PRIVATE_ICANON 0
#endif /* !__ICANON */
#endif /* !__PRIVATE_ICANON */
#ifndef __PRIVATE_ISIG
#ifdef __ISIG
#define __PRIVATE_ISIG __ISIG
#else /* __ISIG */
#define __PRIVATE_ISIG 0
#endif /* !__ISIG */
#endif /* !__PRIVATE_ISIG */
#ifndef __PRIVATE_IEXTEN
#ifdef __IEXTEN
#define __PRIVATE_IEXTEN __IEXTEN
#else /* __IEXTEN */
#define __PRIVATE_IEXTEN 0
#endif /* !__IEXTEN */
#endif /* !__PRIVATE_IEXTEN */
	termios_p->c_lflag &= ~(__PRIVATE_ECHO | __PRIVATE_ECHONL | __PRIVATE_ICANON | __PRIVATE_ISIG | __PRIVATE_IEXTEN);
#endif /* __ECHO || __ECHONL || __ICANON || __ISIG || __IEXTEN */

	/* c_cflag (remove) */
#if defined(__CSIZE) || defined(__PARENB)
#ifndef __PRIVATE_CSIZE
#ifdef __CSIZE
#define __PRIVATE_CSIZE __CSIZE
#else /* __CSIZE */
#define __PRIVATE_CSIZE 0
#endif /* !__CSIZE */
#endif /* !__PRIVATE_CSIZE */
#ifndef __PRIVATE_PARENB
#ifdef __PARENB
#define __PRIVATE_PARENB __PARENB
#else /* __PARENB */
#define __PRIVATE_PARENB 0
#endif /* !__PARENB */
#endif /* !__PRIVATE_PARENB */
	termios_p->c_cflag &= ~(__PRIVATE_CSIZE | __PRIVATE_PARENB);
#endif /* __CSIZE || __PARENB */

	/* c_cflag (addend) */
#if defined(__CS8) || defined(__CREAD)
#ifndef __PRIVATE_CS8
#ifdef __CS8
#define __PRIVATE_CS8 __CS8
#else /* __CS8 */
#define __PRIVATE_CS8 0
#endif /* !__CS8 */
#endif /* !__PRIVATE_CS8 */
#ifndef __PRIVATE_CREAD
#ifdef __CREAD
#define __PRIVATE_CREAD __CREAD
#else /* __CREAD */
#define __PRIVATE_CREAD 0
#endif /* !__CREAD */
#endif /* !__PRIVATE_CREAD */
	termios_p->c_cflag |= (__PRIVATE_CS8 | __PRIVATE_CREAD);
#endif /* __CS8 || __CREAD */
/*[[[end]]]*/

	/* c_cc[VMIN] */
#ifdef __VMIN
#ifdef __CMIN
	termios_p->c_cc[__VMIN] = __CMIN;
#else /* __CMIN */
	termios_p->c_cc[__VMIN] = 1; /* Read returns when one byte was read. */
#endif /* !__CMIN */
#endif /* __VMIN */

	/* c_cc[VTIME] */
#ifdef __VTIME
#ifdef __CTIME
	termios_p->c_cc[__VTIME] = __CTIME;
#else /* __CTIME */
	termios_p->c_cc[__VTIME] = 0;
#endif /* !__CTIME */
#endif /* __VTIME */
}
#endif /* !__KERNEL__ */
#include <bits/posix_opt.h>
#include <asm/os/termios.h>
/* >> cfmakesane(3)
 * Set ~sane~ mode for the given `termios_p' (out-only; meaning that `termios_p' gets initialized by this function)
 * Sane here refers to setting all values to their defaults, as they are defined in <sys/ttydefaults.h> */
INTERN ATTR_SECTION(".text.crt.io.tty") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_cfmakesane)(struct termios *__restrict termios_p) {
	/* Set sane values. */
	libc_memset(termios_p, 0, sizeof(*termios_p));
#ifdef __TTYDEF_CFLAG
	termios_p->c_cflag  = __TTYDEF_CFLAG;
#endif /* __TTYDEF_CFLAG */
#ifdef __TTYDEF_IFLAG
	termios_p->c_iflag  = __TTYDEF_IFLAG;
#endif /* __TTYDEF_IFLAG */
#ifdef __TTYDEF_LFLAG
	termios_p->c_lflag  = __TTYDEF_LFLAG;
#endif /* __TTYDEF_LFLAG */
#ifdef __TTYDEF_OFLAG
	termios_p->c_oflag  = __TTYDEF_OFLAG;
#endif /* __TTYDEF_OFLAG */
#ifdef __TTYDEF_SPEED
	termios_p->c_ispeed = __TTYDEF_SPEED;
	termios_p->c_ospeed = __TTYDEF_SPEED;
#endif /* __TTYDEF_SPEED */
#ifndef __VDISABLE
#define __VDISABLE '\0'
#endif /* !__VDISABLE */
#ifdef __VINTR
#ifdef __CINTR
	termios_p->c_cc[__VINTR] = __CINTR;
#elif __VDISABLE
	termios_p->c_cc[__VINTR] = __VDISABLE;
#endif /* ... */
#endif /* __VINTR */
#ifdef __VQUIT
#ifdef __CQUIT
	termios_p->c_cc[__VQUIT] = __CQUIT;
#elif __VDISABLE
	termios_p->c_cc[__VQUIT] = __VDISABLE;
#endif /* ... */
#endif /* __VQUIT */
#ifdef __VERASE
#ifdef __CERASE
	termios_p->c_cc[__VERASE] = __CERASE;
#elif __VDISABLE
	termios_p->c_cc[__VERASE] = __VDISABLE;
#endif /* ... */
#endif /* __VERASE */
#ifdef __VKILL
#ifdef __CKILL
	termios_p->c_cc[__VKILL] = __CKILL;
#elif __VDISABLE
	termios_p->c_cc[__VKILL] = __VDISABLE;
#endif /* ... */
#endif /* __VKILL */
#ifdef __VEOF
#ifdef __CEOF
	termios_p->c_cc[__VEOF] = __CEOF;
#elif __VDISABLE
	termios_p->c_cc[__VEOF] = __VDISABLE;
#endif /* ... */
#endif /* __VEOF */
#ifdef __VTIME
#ifdef __CTIME
	termios_p->c_cc[__VTIME] = __CTIME;
#elif __VDISABLE
	termios_p->c_cc[__VTIME] = __VDISABLE;
#endif /* ... */
#endif /* __VTIME */
#ifdef __VMIN
#ifdef __CMIN
	termios_p->c_cc[__VMIN] = __CMIN;
#elif __VDISABLE
	termios_p->c_cc[__VMIN] = __VDISABLE;
#endif /* ... */
#endif /* __VMIN */
#ifdef __VSWTCH
#ifdef __CSWTCH
	termios_p->c_cc[__VSWTCH] = __CSWTCH;
#elif __VDISABLE
	termios_p->c_cc[__VSWTCH] = __VDISABLE;
#endif /* ... */
#endif /* __VSWTCH */
#ifdef __VSTART
#ifdef __CSTART
	termios_p->c_cc[__VSTART] = __CSTART;
#elif __VDISABLE
	termios_p->c_cc[__VSTART] = __VDISABLE;
#endif /* ... */
#endif /* __VSTART */
#ifdef __VSTOP
#ifdef __CSTOP
	termios_p->c_cc[__VSTOP] = __CSTOP;
#elif __VDISABLE
	termios_p->c_cc[__VSTOP] = __VDISABLE;
#endif /* ... */
#endif /* __VSTOP */
#ifdef __VSUSP
#ifdef __CSUSP
	termios_p->c_cc[__VSUSP] = __CSUSP;
#elif __VDISABLE
	termios_p->c_cc[__VSUSP] = __VDISABLE;
#endif /* ... */
#endif /* __VSUSP */
#ifdef __VEOL
#ifdef __CEOL
	termios_p->c_cc[__VEOL] = __CEOL;
#elif __VDISABLE
	termios_p->c_cc[__VEOL] = __VDISABLE;
#endif /* ... */
#endif /* __VEOL */
#ifdef __VREPRINT
#ifdef __CREPRINT
	termios_p->c_cc[__VREPRINT] = __CREPRINT;
#elif __VDISABLE
	termios_p->c_cc[__VREPRINT] = __VDISABLE;
#endif /* ... */
#endif /* __VREPRINT */
#ifdef __VDISCARD
#ifdef __CDISCARD
	termios_p->c_cc[__VDISCARD] = __CDISCARD;
#elif __VDISABLE
	termios_p->c_cc[__VDISCARD] = __VDISABLE;
#endif /* ... */
#endif /* __VDISCARD */
#ifdef __VWERASE
#ifdef __CWERASE
	termios_p->c_cc[__VWERASE] = __CWERASE;
#elif __VDISABLE
	termios_p->c_cc[__VWERASE] = __VDISABLE;
#endif /* ... */
#endif /* __VWERASE */
#ifdef __VLNEXT
#ifdef __CLNEXT
	termios_p->c_cc[__VLNEXT] = __CLNEXT;
#elif __VDISABLE
	termios_p->c_cc[__VLNEXT] = __VDISABLE;
#endif /* ... */
#endif /* __VLNEXT */
#ifdef __VEOL2
#ifdef __CEOL2
	termios_p->c_cc[__VEOL2] = __CEOL2;
#elif __VDISABLE
	termios_p->c_cc[__VEOL2] = __VDISABLE;
#endif /* ... */
#endif /* __VEOL2 */
#ifdef __VDSUSP
#ifdef __CDSUSP
	termios_p->c_cc[__VDSUSP] = __CDSUSP;
#elif __VDISABLE
	termios_p->c_cc[__VDSUSP] = __VDISABLE;
#endif /* ... */
#endif /* __VDSUSP */
#ifdef __VSTATUS
#ifdef __CSTATUS
	termios_p->c_cc[__VSTATUS] = __CSTATUS;
#elif __VDISABLE
	termios_p->c_cc[__VSTATUS] = __VDISABLE;
#endif /* ... */
#endif /* __VSTATUS */
}

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(cfgetospeed, libc_cfgetospeed);
DEFINE_PUBLIC_ALIAS(cfgetispeed, libc_cfgetispeed);
DEFINE_PUBLIC_ALIAS(cfsetospeed, libc_cfsetospeed);
DEFINE_PUBLIC_ALIAS(cfsetispeed, libc_cfsetispeed);
DEFINE_PUBLIC_ALIAS(tcgetattr, libc_tcgetattr);
DEFINE_PUBLIC_ALIAS(tcsetattr, libc_tcsetattr);
DEFINE_PUBLIC_ALIAS(tcsendbreak, libc_tcsendbreak);
DEFINE_PUBLIC_ALIAS(tcdrain, libc_tcdrain);
DEFINE_PUBLIC_ALIAS(tcflush, libc_tcflush);
DEFINE_PUBLIC_ALIAS(tcflow, libc_tcflow);
DEFINE_PUBLIC_ALIAS(tcgetsid, libc_tcgetsid);
DEFINE_PUBLIC_ALIAS(tcsetsid, libc_tcsetsid);
DEFINE_PUBLIC_ALIAS(cfsetspeed, libc_cfsetspeed);
DEFINE_PUBLIC_ALIAS(cfmakeraw, libc_cfmakeraw);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(cfmakesane, libc_cfmakesane);

#endif /* !GUARD_LIBC_AUTO_TERMIOS_C */
