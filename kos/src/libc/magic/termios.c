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

%[define_replacement(fd_t     = __fd_t)]
%[define_replacement(pid_t    = __pid_t)]
%[define_replacement(cc_t     = __UINT8_TYPE__)]
%[define_replacement(speed_t  = __UINT32_TYPE__)]
%[define_replacement(tcflag_t = __UINT32_TYPE__)]

%[default:section(".text.crt{|.dos}.io.tty")]

%{
#include <features.h>
#include <sys/ioctl.h>
#include <bits/os/termios.h>

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#include <bits/types.h>
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#if defined(__USE_MISC) || defined(__USE_KOS) || defined(__USE_BSD)
#include <sys/ttydefaults.h>
#endif /* __USE_MISC || __USE_KOS || __USE_BSD */

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

}

[[wunused, ATTR_PURE, decl_include("<bits/os/termios.h>", "<bits/types.h>")]]
speed_t cfgetospeed([[nonnull]] struct termios const *__restrict termios_p) {
	return termios_p->@c_ospeed@;
}

[[wunused, ATTR_PURE, decl_include("<bits/os/termios.h>", "<bits/types.h>")]]
speed_t cfgetispeed([[nonnull]] struct termios const *__restrict termios_p) {
	return termios_p->@c_ispeed@;
}

[[decl_include("<bits/os/termios.h>", "<bits/types.h>")]]
int cfsetospeed([[nonnull]] struct termios *__restrict termios_p, speed_t speed) {
	termios_p->@c_ospeed@ = speed;
	return 0;
}

[[decl_include("<bits/os/termios.h>", "<bits/types.h>")]]
int cfsetispeed([[nonnull]] struct termios *__restrict termios_p, speed_t speed) {
	termios_p->@c_ispeed@ = speed;
	return 0;
}

@@Get terminal attributes
[[decl_include("<bits/os/termios.h>")]]
int tcgetattr($fd_t fd, [[nonnull]] struct termios *__restrict termios_p);

@@Set terminal attributes
@@@param: optional_actions: One of `TCSANOW', `TCSADRAIN' or `TCSAFLUSH'
[[decl_include("<features.h>", "<bits/os/termios.h>")]]
int tcsetattr($fd_t fd, __STDC_INT_AS_UINT_T optional_actions,
              [[nonnull]] struct termios const *__restrict termios_p);

int tcsendbreak($fd_t fd, int duration);

[[cp]]
int tcdrain($fd_t fd);

@@@param: queue_selector: One of `TCIFLUSH', `TCOFLUSH' or `TCIOFLUSH'
[[decl_include("<features.h>")]]
int tcflush($fd_t fd, __STDC_INT_AS_UINT_T queue_selector);

@@@param: action: One of `TCOOFF', `TCOON', `TCIOFF', `TCION'
[[decl_include("<features.h>")]]
int tcflow($fd_t fd, __STDC_INT_AS_UINT_T action);

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
$pid_t tcgetsid($fd_t fd);
%#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

%
%#if defined(__USE_BSD)
int tcsetsid($fd_t fd, $pid_t pid);
%#endif /* __USE_BSD */

%
%#ifdef __USE_MISC
[[decl_include("<bits/os/termios.h>", "<bits/types.h>")]]
int cfsetspeed([[nonnull]] struct termios *__restrict termios_p, speed_t speed) {
	termios_p->@c_ospeed@ = speed;
	termios_p->@c_ispeed@ = speed;
	return 0;
}

@@Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
@@This entails the CANON and all control characters being disabled, as well as
@@any sort of input/output text processing no longer taking place.
[[decl_include("<bits/os/termios.h>")]]
void cfmakeraw([[nonnull]] struct termios *__restrict termios_p) {
	/* As documented here: http://man7.org/linux/man-pages/man3/termios.3.html
	 * Note that the following additions were made:
	 *  - Clear `IXOFF' (ensuring that TTY output can be streamed)
	 *  - Always set `CREAD' (ensuring that data can be received) */
	termios_p->@c_iflag@ &= ~(@IGNBRK@ | @BRKINT@ | @PARMRK@ | @ISTRIP@ |
	                          @INLCR@ | @IGNCR@ | @ICRNL@ | @IXON@ | @IXOFF@);
	termios_p->@c_oflag@ &= ~(@OPOST@);
	termios_p->@c_lflag@ &= ~(@ECHO@ | @ECHONL@ | @ICANON@ | @ISIG@ | @IEXTEN@);
	termios_p->@c_cflag@ &= ~(@CSIZE@ | @PARENB@);
	termios_p->@c_cflag@ |= @CS8@ | @CREAD@;
	termios_p->@c_cc@[@VMIN@]  = 1; /* Read returns when one byte was read. */
	termios_p->@c_cc@[@VTIME@] = 0;
}
%#endif /* __USE_MISC */

%
%#if defined(__USE_KOS) || defined(__USE_BSD)
@@Set ~sane~ mode for the given `termios_p' (out-only; meaning that `termios_p' gets initialized by this function)
@@Sane here refers to setting all values to their defaults, as they are defined in <sys/ttydefaults.h>
[[kernel, decl_include("<bits/os/termios.h>")]]
[[impl_include("<sys/ttydefaults.h>", "<bits/posix_opt.h>")]]
void cfmakesane([[nonnull]] struct termios *__restrict termios_p) {
	/* Set sane values. */
	memset(termios_p, 0, sizeof(*termios_p));
#ifdef @TTYDEF_CFLAG@
	termios_p->@c_cflag@  = @TTYDEF_CFLAG@;
#endif /* TTYDEF_CFLAG */
#ifdef @TTYDEF_IFLAG@
	termios_p->@c_iflag@  = @TTYDEF_IFLAG@;
#endif /* TTYDEF_IFLAG */
#ifdef @TTYDEF_LFLAG@
	termios_p->@c_lflag@  = @TTYDEF_LFLAG@;
#endif /* TTYDEF_LFLAG */
#ifdef @TTYDEF_OFLAG@
	termios_p->@c_oflag@  = @TTYDEF_OFLAG@;
#endif /* TTYDEF_OFLAG */
#ifdef @TTYDEF_SPEED@
	termios_p->@c_ispeed@ = @TTYDEF_SPEED@;
	termios_p->@c_ospeed@ = @TTYDEF_SPEED@;
#endif /* TTYDEF_SPEED */
#ifndef @_POSIX_VDISABLE@
#define @_POSIX_VDISABLE@ '\0'
#endif /* !condition */
#ifdef @VINTR@
#ifdef @CINTR@
	termios_p->@c_cc@[@VINTR@] = @CINTR@;
#else /* CINTR */
	termios_p->@c_cc@[@VINTR@] = @_POSIX_VDISABLE@;
#endif /* !CINTR */
#endif /* VINTR */
#ifdef @VQUIT@
#ifdef @CQUIT@
	termios_p->@c_cc@[@VQUIT@] = @CQUIT@;
#else /* CQUIT */
	termios_p->@c_cc@[@VQUIT@] = @_POSIX_VDISABLE@;
#endif /* !CQUIT */
#endif /* VQUIT */
#ifdef @VERASE@
#ifdef @CERASE@
	termios_p->@c_cc@[@VERASE@] = @CERASE@;
#else /* CERASE */
	termios_p->@c_cc@[@VERASE@] = @_POSIX_VDISABLE@;
#endif /* !CERASE */
#endif /* VERASE */
#ifdef @VKILL@
#ifdef @CKILL@
	termios_p->@c_cc@[@VKILL@] = @CKILL@;
#else /* CKILL */
	termios_p->@c_cc@[@VKILL@] = @_POSIX_VDISABLE@;
#endif /* !CKILL */
#endif /* VKILL */
#ifdef @VEOF@
#ifdef @CEOF@
	termios_p->@c_cc@[@VEOF@] = @CEOF@;
#else /* CEOF */
	termios_p->@c_cc@[@VEOF@] = @_POSIX_VDISABLE@;
#endif /* !CEOF */
#endif /* VEOF */
#ifdef @VTIME@
#ifdef @CTIME@
	termios_p->@c_cc@[@VTIME@] = @CTIME@;
#else /* CTIME */
	termios_p->@c_cc@[@VTIME@] = @_POSIX_VDISABLE@;
#endif /* !CTIME */
#endif /* VTIME */
#ifdef @VMIN@
#ifdef @CMIN@
	termios_p->@c_cc@[@VMIN@] = @CMIN@;
#else /* CMIN */
	termios_p->@c_cc@[@VMIN@] = @_POSIX_VDISABLE@;
#endif /* !CMIN */
#endif /* VMIN */
#ifdef @VSWTCH@
#ifdef @CSWTCH@
	termios_p->@c_cc@[@VSWTCH@] = @CSWTCH@;
#else /* CSWTCH */
	termios_p->@c_cc@[@VSWTCH@] = @_POSIX_VDISABLE@;
#endif /* !CSWTCH */
#endif /* VSWTCH */
#ifdef @VSTART@
#ifdef @CSTART@
	termios_p->@c_cc@[@VSTART@] = @CSTART@;
#else /* CSTART */
	termios_p->@c_cc@[@VSTART@] = @_POSIX_VDISABLE@;
#endif /* !CSTART */
#endif /* VSTART */
#ifdef @VSTOP@
#ifdef @CSTOP@
	termios_p->@c_cc@[@VSTOP@] = @CSTOP@;
#else /* CSTOP */
	termios_p->@c_cc@[@VSTOP@] = @_POSIX_VDISABLE@;
#endif /* !CSTOP */
#endif /* VSTOP */
#ifdef @VSUSP@
#ifdef @CSUSP@
	termios_p->@c_cc@[@VSUSP@] = @CSUSP@;
#else /* CSUSP */
	termios_p->@c_cc@[@VSUSP@] = @_POSIX_VDISABLE@;
#endif /* !CSUSP */
#endif /* VSUSP */
#ifdef @VEOL@
#ifdef @CEOL@
	termios_p->@c_cc@[@VEOL@] = @CEOL@;
#else /* CEOL */
	termios_p->@c_cc@[@VEOL@] = @_POSIX_VDISABLE@;
#endif /* !CEOL */
#endif /* VEOL */
#ifdef @VREPRINT@
#ifdef @CREPRINT@
	termios_p->@c_cc@[@VREPRINT@] = @CREPRINT@;
#else /* CREPRINT */
	termios_p->@c_cc@[@VREPRINT@] = @_POSIX_VDISABLE@;
#endif /* !CREPRINT */
#endif /* VREPRINT */
#ifdef @VDISCARD@
#ifdef @CDISCARD@
	termios_p->@c_cc@[@VDISCARD@] = @CDISCARD@;
#else /* CDISCARD */
	termios_p->@c_cc@[@VDISCARD@] = @_POSIX_VDISABLE@;
#endif /* !CDISCARD */
#endif /* VDISCARD */
#ifdef @VWERASE@
#ifdef @CWERASE@
	termios_p->@c_cc@[@VWERASE@] = @CWERASE@;
#else /* CWERASE */
	termios_p->@c_cc@[@VWERASE@] = @_POSIX_VDISABLE@;
#endif /* !CWERASE */
#endif /* VWERASE */
#ifdef @VLNEXT@
#ifdef @CLNEXT@
	termios_p->@c_cc@[@VLNEXT@] = @CLNEXT@;
#else /* CLNEXT */
	termios_p->@c_cc@[@VLNEXT@] = @_POSIX_VDISABLE@;
#endif /* !CLNEXT */
#endif /* VLNEXT */
#ifdef @VEOL2@
#ifdef @CEOL2@
	termios_p->@c_cc@[@VEOL2@] = @CEOL2@;
#else /* CEOL2 */
	termios_p->@c_cc@[@VEOL2@] = @_POSIX_VDISABLE@;
#endif /* !CEOL2 */
#endif /* VEOL2 */
#ifdef @VDSUSP@
#ifdef @CDSUSP@
	termios_p->@c_cc@[@VDSUSP@] = @CDSUSP@;
#else /* CDSUSP */
	termios_p->@c_cc@[@VDSUSP@] = @_POSIX_VDISABLE@;
#endif /* !CDSUSP */
#endif /* VDSUSP */
#ifdef @VSTATUS@
#ifdef @CSTATUS@
	termios_p->@c_cc@[@VSTATUS@] = @CSTATUS@;
#else /* CSTATUS */
	termios_p->@c_cc@[@VSTATUS@] = @_POSIX_VDISABLE@;
#endif /* !CSTATUS */
#endif /* VSTATUS */
}
%#endif /* __USE_KOS || __USE_BSD */


%{
#endif /* __CC__ */

#ifdef __USE_MISC
#define CCEQ(val, c) ((c) == (val) && (val) != _POSIX_VDISABLE)
#endif /* __USE_MISC */

__SYSDECL_END

}