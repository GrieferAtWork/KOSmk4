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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(pid_t = __pid_t)]
%[default_impl_section(.text.crt.io.tty)]

%{
#include <features.h>
#include <sys/ioctl.h>
#include <bits/termios.h>

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#include <bits/types.h>
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#ifdef __USE_MISC
#include <sys/ttydefaults.h>
#endif /* __USE_MISC */

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

}

[ATTR_WUNUSED]
cfgetospeed:([nonnull] struct termios const *__restrict termios_p) -> speed_t {
	return termios_p->@c_ospeed@;
}
[ATTR_WUNUSED]
cfgetispeed:([nonnull] struct termios const *__restrict termios_p) -> speed_t {
	return termios_p->@c_ispeed@;
}
cfsetospeed:([nonnull] struct termios *__restrict termios_p, speed_t speed) -> int {
	termios_p->@c_ospeed@ = speed;
	return 0;
}
cfsetispeed:([nonnull] struct termios *__restrict termios_p, speed_t speed) -> int {
	termios_p->@c_ispeed@ = speed;
	return 0;
}

tcgetattr:($fd_t fd, [nonnull] struct termios *__restrict termios_p) -> int;
tcsetattr:($fd_t fd, int optional_actions, [nonnull] struct termios const *__restrict termios_p) -> int;

tcsendbreak:($fd_t fd, int duration) -> int;
[cp] tcdrain:($fd_t fd) -> int;
tcflush:($fd_t fd, int queue_selector) -> int;
tcflow:($fd_t fd, int action) -> int;

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
tcgetsid:($fd_t fd) -> $pid_t;
%#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

%
%#ifdef __USE_MISC
cfsetspeed:([nonnull] struct termios *__restrict termios_p, speed_t speed) -> int {
	termios_p->@c_ospeed@ = speed;
	termios_p->@c_ispeed@ = speed;
	return 0;
}
cfmakeraw:([nonnull] struct termios *__restrict termios_p) {
	termios_p->@c_iflag@ &= ~(@IGNBRK@|@BRKINT@|@PARMRK@|@ISTRIP@|@INLCR@|@IGNCR@|@ICRNL@|@IXON@);
	termios_p->@c_oflag@ &= ~(@OPOST@);
	termios_p->@c_lflag@ &= ~(@ECHO@|@ECHONL@|@ICANON@|@ISIG@|@IEXTEN@);
	termios_p->@c_cflag@ &= ~(@CSIZE@|@PARENB@);
	termios_p->@c_cflag@ |= @CS8@;
	termios_p->@c_cc@[@VMIN@]  = 1; /* Read returns when one byte was read. */
	termios_p->@c_cc@[@VTIME@] = 0;
}
%#endif /* __USE_MISC */


%{
#endif /* __CC__ */

#ifdef __USE_MISC
#define CCEQ(val, c)   ((c) == (val) && (val) != _POSIX_VDISABLE)
#endif /* __USE_MISC */

__SYSDECL_END

}