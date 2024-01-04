/* HASH CRC-32:0x20f6487e */
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
#ifndef GUARD_LIBC_AUTO_TERMIOS_C
#define GUARD_LIBC_AUTO_TERMIOS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "termios.h"
#include "string.h"
#include "../user/sys.ioctl.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/termios.h>
#include <bits/os/termios.h>
/* >> cfgetospeed(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_PURE WUNUSED ATTR_IN(1) speed_t
NOTHROW_NCX(LIBCCALL libc_cfgetospeed)(struct termios const *__restrict termios_p) {
#ifdef __CBAUD
	return termios_p->c_cflag & __CBAUD;
#elif defined(_HAVE_STRUCT_TERMIOS_C_OSPEED)
	return termios_p->c_ospeed;
#else /* ... */
	(void)termios_p;
	COMPILER_IMPURE();
	return 0;
#endif /* !... */
}
#include <asm/os/termios.h>
#include <bits/os/termios.h>
/* >> cfgetispeed(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_PURE WUNUSED ATTR_IN(1) speed_t
NOTHROW_NCX(LIBCCALL libc_cfgetispeed)(struct termios const *__restrict termios_p) {
#if defined(__IBAUD0) && defined(__CBAUD)
	return (termios_p->c_iflag & __IBAUD0) ? 0 : (termios_p->c_cflag & __CBAUD);
#elif defined(_HAVE_STRUCT_TERMIOS_C_ISPEED)
	return termios_p->c_ispeed;
#else /* ... */
	(void)termios_p;
	COMPILER_IMPURE();
	return 0;
#endif /* !... */
}
#include <asm/os/termios.h>
#include <bits/os/termios.h>
#include <libc/errno.h>
/* >> cfsetospeed(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_cfsetospeed)(struct termios *__restrict termios_p,
                                       speed_t speed) {
#ifdef __CBAUD
	if unlikely(speed & ~__CBAUD) {

		return __libc_seterrno(EINVAL);



	}
	termios_p->c_cflag &= ~__CBAUD;
	termios_p->c_cflag |= speed;
#endif /* __CBAUD */

	/* If present, store in the dedicated ospeed field. */
#ifdef _HAVE_STRUCT_TERMIOS_C_OSPEED
	termios_p->c_ospeed = speed;
#endif /* _HAVE_STRUCT_TERMIOS_C_OSPEED */
	(void)termios_p;
	(void)speed;
	return 0;
}
#include <asm/os/termios.h>
#include <libc/errno.h>
/* >> cfsetispeed(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_cfsetispeed)(struct termios *__restrict termios_p,
                                       speed_t speed) {
#if defined(__IBAUD0) && defined(__CBAUD)
	if unlikely(speed & ~__CBAUD) {

		return __libc_seterrno(EINVAL);



	}
	if (speed == 0) {
		termios_p->c_iflag |= __IBAUD0;
	} else {
		termios_p->c_iflag &= ~__IBAUD0;
		termios_p->c_cflag &= ~__CBAUD;
		termios_p->c_cflag |= speed;
	}
#elif defined(__CBAUD) && defined(__IBSHIFT)
	speed_t used_speed;
	if unlikely(speed & ~__CBAUD) {

		return __libc_seterrno(EINVAL);



	}
	used_speed = speed;
	if (speed == 0)
		used_speed = termios_p->c_cflag & __CBAUD;
	termios_p->c_cflag &= ~(__CBAUD << __IBSHIFT);
	termios_p->c_cflag |= used_speed << __IBSHIFT;
#endif /* ... */

	/* If present, store in the dedicated ispeed field. */
#ifdef _HAVE_STRUCT_TERMIOS_C_ISPEED
	termios_p->c_ispeed = speed;
#endif /* _HAVE_STRUCT_TERMIOS_C_ISPEED */
	(void)termios_p;
	(void)speed;
	return 0;
}
/* >> tcgetattr(3)
 * Get terminal attributes */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_FDARG(1) ATTR_OUT(2) int
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
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_FDARG(1) ATTR_IN(3) int
NOTHROW_NCX(LIBCCALL libc_tcsetattr)(fd_t fd,
                                     __STDC_INT_AS_UINT_T optional_actions,
                                     struct termios const *__restrict termios_p) {
	int cmd;
	switch (optional_actions) {


	case __TCSANOW:
		cmd = __TCSETA;
		break;



	case __TCSADRAIN:
		cmd = __TCSETAW;
		break;



	case __TCSAFLUSH:
		cmd = __TCSETAF;
		break;


	default:

		return libc_seterrno(EINVAL);



	}
	return (int)libc_ioctl(fd, cmd, termios_p);
}
/* >> tcsendbreak(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_FDARG(1) int
NOTHROW_NCX(LIBCCALL libc_tcsendbreak)(fd_t fd,
                                       int duration) {
	return (int)libc_ioctl(fd, __TCSBRKP, duration);
}
/* >> tcdrain(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_FDARG(1) int
NOTHROW_RPC(LIBCCALL libc_tcdrain)(fd_t fd) {
	return (int)libc_ioctl(fd, __TCSBRK, 1);
}
/* >> tcflush(3)
 * @param: queue_selector: One of `TCIFLUSH', `TCOFLUSH' or `TCIOFLUSH' */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_FDARG(1) int
NOTHROW_NCX(LIBCCALL libc_tcflush)(fd_t fd,
                                   __STDC_INT_AS_UINT_T queue_selector) {
	return (int)libc_ioctl(fd, __TCFLSH, queue_selector);
}
/* >> tcflow(3)
 * @param: action: One of `TCOOFF', `TCOON', `TCIOFF', `TCION' */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_FDARG(1) int
NOTHROW_NCX(LIBCCALL libc_tcflow)(fd_t fd,
                                  __STDC_INT_AS_UINT_T action) {
	return (int)libc_ioctl(fd, __TCXONC, action);
}
/* >> tcgetsid(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_FDARG(1) pid_t
NOTHROW_NCX(LIBCCALL libc_tcgetsid)(fd_t fd) {
	pid_t result;
	if unlikely(libc_ioctl(fd, __TIOCGSID, &result) < 0)
		result = -1;
	return result;
}
#include <libc/errno.h>
/* >> tcsetsid(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_FDARG(1) int
NOTHROW_NCX(LIBCCALL libc_tcsetsid)(fd_t fd,
                                    pid_t pid) {
	int result;
	if unlikely(pid != libc_getsid(0)) {

		result = libc_seterrno(EINVAL);



	} else {
		result = libc_ioctl(fd, __TIOCSCTTY, NULL);
	}
	return result;
}
/* >> cfsetspeed(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_INOUT(1) int
NOTHROW_NCX(LIBCCALL libc_cfsetspeed)(struct termios *__restrict termios_p,
                                      speed_t speed) {
	return libc_cfsetispeed(termios_p, speed) |
	       libc_cfsetospeed(termios_p, speed);
}
#include <asm/os/termios.h>
/* >> cfmakeraw(3)
 * Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
 * This entails the CANON and all control characters being disabled, as well as
 * any sort of input/output text processing no longer taking place. */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_INOUT(1) void
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
	local head = f"termios_p->@{field}@ {add ? "|= " : "&= ~"}(";
	print("	", head, "0");
	head = " " * #head;
	for (local f: flags) {
		print("@@pp_ifdef __", f, "@@");
		print("	", head, "| __", f);
		print("@@pp_endif@@");
	}
	print("	", head, ");");
	print("@@pp_endif@@");
	print;
}
]]]*/
	/* c_iflag (remove) */
#if defined(__IGNBRK) || defined(__BRKINT) || defined(__PARMRK) || defined(__ISTRIP) || defined(__INLCR) || defined(__IGNCR) || defined(__ICRNL) || defined(__IXON) || defined(__IXOFF)
	termios_p->c_iflag &= ~(0
#ifdef __IGNBRK
	                          | __IGNBRK
#endif /* __IGNBRK */
#ifdef __BRKINT
	                          | __BRKINT
#endif /* __BRKINT */
#ifdef __PARMRK
	                          | __PARMRK
#endif /* __PARMRK */
#ifdef __ISTRIP
	                          | __ISTRIP
#endif /* __ISTRIP */
#ifdef __INLCR
	                          | __INLCR
#endif /* __INLCR */
#ifdef __IGNCR
	                          | __IGNCR
#endif /* __IGNCR */
#ifdef __ICRNL
	                          | __ICRNL
#endif /* __ICRNL */
#ifdef __IXON
	                          | __IXON
#endif /* __IXON */
#ifdef __IXOFF
	                          | __IXOFF
#endif /* __IXOFF */
	                          );
#endif /* __IGNBRK || __BRKINT || __PARMRK || __ISTRIP || __INLCR || __IGNCR || __ICRNL || __IXON || __IXOFF */

	/* c_oflag (remove) */
#ifdef __OPOST
	termios_p->c_oflag &= ~(0

	                          | __OPOST

	                          );
#endif /* __OPOST */

	/* c_lflag (remove) */
#if defined(__ECHO) || defined(__ECHONL) || defined(__ICANON) || defined(__ISIG) || defined(__IEXTEN)
	termios_p->c_lflag &= ~(0
#ifdef __ECHO
	                          | __ECHO
#endif /* __ECHO */
#ifdef __ECHONL
	                          | __ECHONL
#endif /* __ECHONL */
#ifdef __ICANON
	                          | __ICANON
#endif /* __ICANON */
#ifdef __ISIG
	                          | __ISIG
#endif /* __ISIG */
#ifdef __IEXTEN
	                          | __IEXTEN
#endif /* __IEXTEN */
	                          );
#endif /* __ECHO || __ECHONL || __ICANON || __ISIG || __IEXTEN */

	/* c_cflag (remove) */
#if defined(__CSIZE) || defined(__PARENB)
	termios_p->c_cflag &= ~(0
#ifdef __CSIZE
	                          | __CSIZE
#endif /* __CSIZE */
#ifdef __PARENB
	                          | __PARENB
#endif /* __PARENB */
	                          );
#endif /* __CSIZE || __PARENB */

	/* c_cflag (addend) */
#if defined(__CS8) || defined(__CREAD)
	termios_p->c_cflag |= (0
#ifdef __CS8
	                         | __CS8
#endif /* __CS8 */
#ifdef __CREAD
	                         | __CREAD
#endif /* __CREAD */
	                         );
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
 * Sane here  refers  to  setting  all values  to  their  defaults,  as they  are  defined  in  <sys/ttydefaults.h> */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_OUT(1) void
NOTHROW_NCX(LIBCCALL libc_cfmakesane)(struct termios *__restrict termios_p) {
	/* Default everything to ZERO */
	libc_bzero(termios_p, sizeof(*termios_p));

	/* Set sane flag values. */
#if defined(__TTYDEF_CFLAG) && __TTYDEF_CFLAG
	termios_p->c_cflag  = __TTYDEF_CFLAG;
#endif /* __TTYDEF_CFLAG && __TTYDEF_CFLAG */
#if defined(__TTYDEF_IFLAG) && __TTYDEF_IFLAG
	termios_p->c_iflag  = __TTYDEF_IFLAG;
#endif /* __TTYDEF_IFLAG && __TTYDEF_IFLAG */
#if defined(__TTYDEF_LFLAG) && __TTYDEF_LFLAG
	termios_p->c_lflag  = __TTYDEF_LFLAG;
#endif /* __TTYDEF_LFLAG && __TTYDEF_LFLAG */
#if defined(__TTYDEF_OFLAG) && __TTYDEF_OFLAG
	termios_p->c_oflag  = __TTYDEF_OFLAG;
#endif /* __TTYDEF_OFLAG && __TTYDEF_OFLAG */
#if defined(__TTYDEF_SPEED) && __TTYDEF_SPEED
	termios_p->c_ispeed = __TTYDEF_SPEED;
	termios_p->c_ospeed = __TTYDEF_SPEED;
#endif /* __TTYDEF_SPEED && __TTYDEF_SPEED */

	/* ^C: Send SIGINT to the foreground process (requires `ISIG') */
#ifdef __VINTR
#ifdef __CINTR
	termios_p->c_cc[__VINTR] = __CINTR;
#elif __VDISABLE
	termios_p->c_cc[__VINTR] = __VDISABLE;
#endif /* ... */
#endif /* __VINTR */

	/* ^\: Send SIGQUIT to the foreground process (requires `ISIG') */
#ifdef __VQUIT
#ifdef __CQUIT
	termios_p->c_cc[__VQUIT] = __CQUIT;
#elif __VDISABLE
	termios_p->c_cc[__VQUIT] = __VDISABLE;
#endif /* ... */
#endif /* __VQUIT */

	/* ^H (aka. \b): Erase the last character from the input canon (requires `ECHOE') */
#ifdef __VERASE
#ifdef __CERASE
	termios_p->c_cc[__VERASE] = __CERASE;
#elif __VDISABLE
	termios_p->c_cc[__VERASE] = __VDISABLE;
#endif /* ... */
#endif /* __VERASE */

	/* ^U: Clear the entire input canon (requires `ECHOK') */
#ifdef __VKILL
#ifdef __CKILL
	termios_p->c_cc[__VKILL] = __CKILL;
#elif __VDISABLE
	termios_p->c_cc[__VKILL] = __VDISABLE;
#endif /* ... */
#endif /* __VKILL */

	/* ^D: Cause read(2) from the TTY to return 0 once (thus indicating input EOF) */
#ifdef __VEOF
#ifdef __CEOF
	termios_p->c_cc[__VEOF] = __CEOF;
#elif __VDISABLE
	termios_p->c_cc[__VEOF] = __VDISABLE;
#endif /* ... */
#endif /* __VEOF */

	/* ... */
#ifdef __VTIME
#ifdef __CTIME
	termios_p->c_cc[__VTIME] = __CTIME;
#elif __VDISABLE
	termios_p->c_cc[__VTIME] = __VDISABLE;
#endif /* ... */
#endif /* __VTIME */

	/* Minimum number of input bytes to-be returned by read(2) from the TTY */
#ifdef __VMIN
#ifdef __CMIN
	termios_p->c_cc[__VMIN] = __CMIN;
#elif __VDISABLE
	termios_p->c_cc[__VMIN] = __VDISABLE;
#endif /* ... */
#endif /* __VMIN */

	/* ... */
#ifdef __VSWTCH
#ifdef __CSWTCH
	termios_p->c_cc[__VSWTCH] = __CSWTCH;
#elif __VDISABLE
	termios_p->c_cc[__VSWTCH] = __VDISABLE;
#endif /* ... */
#endif /* __VSWTCH */

	/* ^Q: Restart stopped output (After VSTOP; causes pending TTY output to be flushed) */
#ifdef __VSTART
#ifdef __CSTART
	termios_p->c_cc[__VSTART] = __CSTART;
#elif __VDISABLE
	termios_p->c_cc[__VSTART] = __VDISABLE;
#endif /* ... */
#endif /* __VSTART */

	/* ^S: Suspend TTY display output until `VSTART' */
#ifdef __VSTOP
#ifdef __CSTOP
	termios_p->c_cc[__VSTOP] = __CSTOP;
#elif __VDISABLE
	termios_p->c_cc[__VSTOP] = __VDISABLE;
#endif /* ... */
#endif /* __VSTOP */

	/* ^Z: Send SIGTSTP to the foreground process (requires `ISIG') */
#ifdef __VSUSP
#ifdef __CSUSP
	termios_p->c_cc[__VSUSP] = __CSUSP;
#elif __VDISABLE
	termios_p->c_cc[__VSUSP] = __VDISABLE;
#endif /* ... */
#endif /* __VSUSP */

	/* \0: An additional end-of-line character used to flush the canon (by default, only \n is recognized) */
#ifdef __VEOL
#ifdef __CEOL
	termios_p->c_cc[__VEOL] = __CEOL;
#elif __VDISABLE
	termios_p->c_cc[__VEOL] = __VDISABLE;
#endif /* ... */
#endif /* __VEOL */

	/* ^R: Re-echo the current contents of the input canon (requires `IEXTEN') */
#ifdef __VREPRINT
#ifdef __CREPRINT
	termios_p->c_cc[__VREPRINT] = __CREPRINT;
#elif __VDISABLE
	termios_p->c_cc[__VREPRINT] = __VDISABLE;
#endif /* ... */
#endif /* __VREPRINT */

	/* <UNSUPPORTED> */
#ifdef __VDISCARD
#ifdef __CDISCARD
	termios_p->c_cc[__VDISCARD] = __CDISCARD;
#elif __VDISABLE
	termios_p->c_cc[__VDISCARD] = __VDISABLE;
#endif /* ... */
#endif /* __VDISCARD */

	/* ^W: Erase the last-written word (while (isspace(last)) erase(); while (!isspace(last)) erase()) (Requires `ECHOE' and `IEXTEN') */
#ifdef __VWERASE
#ifdef __CWERASE
	termios_p->c_cc[__VWERASE] = __CWERASE;
#elif __VDISABLE
	termios_p->c_cc[__VWERASE] = __VDISABLE;
#endif /* ... */
#endif /* __VWERASE */

	/* ^V: The next input character is escaped, in that any special meaning it would normally have is dismissed */
#ifdef __VLNEXT
#ifdef __CLNEXT
	termios_p->c_cc[__VLNEXT] = __CLNEXT;
#elif __VDISABLE
	termios_p->c_cc[__VLNEXT] = __VDISABLE;
#endif /* ... */
#endif /* __VLNEXT */

	/* \0: An additional end-of-line character used to flush the canon (by default, only \n is recognized) */
#ifdef __VEOL2
#ifdef __CEOL2
	termios_p->c_cc[__VEOL2] = __CEOL2;
#elif __VDISABLE
	termios_p->c_cc[__VEOL2] = __VDISABLE;
#endif /* ... */
#endif /* __VEOL2 */

	/* ... */
#ifdef __VDSUSP
#ifdef __CDSUSP
	termios_p->c_cc[__VDSUSP] = __CDSUSP;
#elif __VDISABLE
	termios_p->c_cc[__VDSUSP] = __VDISABLE;
#endif /* ... */
#endif /* __VDSUSP */

	/* ... */
#ifdef __VSTATUS
#ifdef __CSTATUS
	termios_p->c_cc[__VSTATUS] = __CSTATUS;
#elif __VDISABLE
	termios_p->c_cc[__VSTATUS] = __VDISABLE;
#endif /* ... */
#endif /* __VSTATUS */
}
#ifndef __KERNEL__
/* >> tcgetwinsize(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_FDARG(1) ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_tcgetwinsize)(fd_t fd,
                                        struct winsize *winsize_p) {
	return libc_ioctl(fd, __TIOCGWINSZ, winsize_p);
}
/* >> tcsetwinsize(3) */
INTERN ATTR_SECTION(".text.crt.io.tty") ATTR_FDARG(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_tcsetwinsize)(fd_t fd,
                                        struct winsize const *winsize_p) {
	return libc_ioctl(fd, __TIOCSWINSZ, winsize_p);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(cfgetospeed, libc_cfgetospeed);
DEFINE_PUBLIC_ALIAS(cfgetispeed, libc_cfgetispeed);
DEFINE_PUBLIC_ALIAS(cfsetospeed, libc_cfsetospeed);
DEFINE_PUBLIC_ALIAS(cfsetispeed, libc_cfsetispeed);
DEFINE_PUBLIC_ALIAS(__tcgetattr, libc_tcgetattr);
DEFINE_PUBLIC_ALIAS(tcgetattr, libc_tcgetattr);
DEFINE_PUBLIC_ALIAS(tcsetattr, libc_tcsetattr);
DEFINE_PUBLIC_ALIAS(tcsendbreak, libc_tcsendbreak);
DEFINE_PUBLIC_ALIAS(__libc_tcdrain, libc_tcdrain);
DEFINE_PUBLIC_ALIAS(tcdrain, libc_tcdrain);
DEFINE_PUBLIC_ALIAS(tcflush, libc_tcflush);
DEFINE_PUBLIC_ALIAS(tcflow, libc_tcflow);
DEFINE_PUBLIC_ALIAS(tcgetsid, libc_tcgetsid);
DEFINE_PUBLIC_ALIAS(tcsetsid, libc_tcsetsid);
DEFINE_PUBLIC_ALIAS(cfsetspeed, libc_cfsetspeed);
DEFINE_PUBLIC_ALIAS(cfmakeraw, libc_cfmakeraw);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(cfmakesane, libc_cfmakesane);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(tcgetwinsize, libc_tcgetwinsize);
DEFINE_PUBLIC_ALIAS(tcsetwinsize, libc_tcsetwinsize);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_TERMIOS_C */
