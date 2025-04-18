/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!replace_with_include <asm/os/tty.h>*/
#ifndef _ASM_OS_KOS_TTY_H
#define _ASM_OS_KOS_TTY_H 1

#include <asm/ioctl.h>

#define __TCGETS              _IO('T', 0x01) /* [struct termio *arg] Get terminal attributes */
#define __TCSETS              _IO('T', 0x02) /* [struct termio const *arg] Set terminal attributes */
#define __TCSETSW             _IO('T', 0x03) /* [struct termio const *arg] Wait for all unwritten data to be transmitted, discard all unread data, then set terminal attributes */
#define __TCSETSF             _IO('T', 0x04) /* [struct termio const *arg] Wait for all unwritten data to be transmitted, then set terminal attributes */
#define __TCGETA              _IO('T', 0x05) /* [struct termios *arg] Get terminal attributes */
#define __TCSETA              _IO('T', 0x06) /* [struct termios const *arg] Set terminal attributes */
#define __TCSETAW             _IO('T', 0x07) /* [struct termios const *arg] Wait for all unwritten data to be transmitted, discard all unread data, then set terminal attributes */
#define __TCSETAF             _IO('T', 0x08) /* [struct termios const *arg] Wait for all unwritten data to be transmitted, then set terminal attributes */
#define __TCSBRK              _IO('T', 0x09) /* [int arg] Send a break (arg should be 0 for portability, but is ignored when non-zero) */
#define __TCXONC              _IO('T', 0x0a) /* [int arg = { TCOOFF, TCOON, TCIOFF, TCION }] */
#define __TCFLSH              _IO('T', 0x0b) /* [int arg = { TCIFLUSH, TCOFLUSH, TCIOFLUSH }] */

#define __TIOCEXCL            _IO('T', 0x0c) /* ... */
#define __TIOCNXCL            _IO('T', 0x0d) /* ... */
#define __TIOCSCTTY           _IO('T', 0x0e) /* [int steal_if_necessary] Make this terminal the controlling terminal of the calling process */
#define __TIOCGPGRP           _IO('T', 0x0f) /* [pid_t *arg] Store the PID of the foreground process group in arg */
#define __TIOCSPGRP           _IO('T', 0x10) /* [pid_t const *arg] Load the PID of the foreground process group from arg */
#define __TIOCOUTQ            _IO('T', 0x11) /* [int *count] Save the number of pending output bytes */
#define __TIOCSTI             _IO('T', 0x12) /* [char const *byte] Insert the given byte in the input queue. */
#define __TIOCGWINSZ          _IO('T', 0x13) /* [struct winsize *arg] Get the window size */
#define __TIOCSWINSZ          _IO('T', 0x14) /* [struct winsize const *arg] Set the window size */
#define __TIOCMGET            _IO('T', 0x15) /* [unsigned int *argp] Get status of modem bits (set of `TIOCM_*') */
#define __TIOCMBIS            _IO('T', 0x16) /* [unsigned int const *argp] Enable modem bits (bits |= *argp) (set of `TIOCM_*') */
#define __TIOCMBIC            _IO('T', 0x17) /* [unsigned int const *argp] Clear modem bits (bits &= ~*argp) (set of `TIOCM_*') */
#define __TIOCMSET            _IO('T', 0x18) /* [unsigned int const *argp] Set modem bits (bits = *argp) (set of `TIOCM_*') */

#define __TIOCGSOFTCAR        _IO('T', 0x19) /* [int *arg] Get the state of `termios::c_cflag::CLOCAL'. */
#define __TIOCSSOFTCAR        _IO('T', 0x1a) /* [int const *arg] Set the state of `termios::c_cflag::CLOCAL'. */
#define __TIOCINQ             _IO('T', 0x1b) /* [int *count] Save the number of pending input bytes */
#define __TIOCLINUX           _IO('T', 0x1c) /* ... */
#define __TIOCCONS            _IO('T', 0x1d) /* ... */
#define __TIOCGSERIAL         _IO('T', 0x1e) /* ... */
#define __TIOCSSERIAL         _IO('T', 0x1f) /* ... */
#define __TIOCPKT             _IO('T', 0x20) /* ... */
#define __FIONBIO             _IO('T', 0x21) /* [int *arg] Set (*arg != 0) or clear (*arg == 0) O_NONBLOCK / IO_NONBLOCK */
#define __TIOCNOTTY           _IO('T', 0x22) /* Given up control over this CTTY */
#define __TIOCSETD            _IO('T', 0x23) /* [int const *ld] Set the terminal's line discipline to *ld */
#define __TIOCGETD            _IO('T', 0x24) /* [int *result] Store the terminal's line discipline in *result */
#define __TCSBRKP             _IO('T', 0x25) /* [int deciseconds] Needed for POSIX tcsendbreak() */
#define __TIOCSBRK            _IO('T', 0x27) /* BSD compatibility */
#define __TIOCCBRK            _IO('T', 0x28) /* BSD compatibility */
#define __TIOCGSID            _IO('T', 0x29) /* [pid_t *arg] Return the session ID of a tty */
#define __TCGETS2            _IOR('T', 0x2a, struct termios2) /* [struct termios2 *arg] ... */
#define __TCSETS2            _IOW('T', 0x2b, struct termios2) /* [struct termios2 const *arg] ... */
#define __TCSETSW2           _IOW('T', 0x2c, struct termios2) /* [struct termios2 const *arg] ... */
#define __TCSETSF2           _IOW('T', 0x2d, struct termios2) /* [struct termios2 const *arg] ... */
#define __TIOCGRS485          _IO('T', 0x2e) /* ... */
#define __TIOCSRS485          _IO('T', 0x2f) /* ... */
#define __TIOCGPTN           _IOR('T', 0x30, unsigned int) /* Get Pty Number (of pty-mux device) */
#define __TIOCSPTLCK         _IOW('T', 0x31, int)  /* Lock/unlock Pty */
#define __TIOCGDEV           _IOR('T', 0x32, unsigned int) /* Get primary device node of /dev/console */
#define __TCGETX              _IO('T', 0x32) /* [struct termiox *arg] SYS5 TCGETX compatibility */
#define __TCSETX              _IO('T', 0x33) /* [struct termiox const *arg] ... */
#define __TCSETXF             _IO('T', 0x34) /* [struct termiox const *arg] ... */
#define __TCSETXW             _IO('T', 0x35) /* [struct termiox const *arg] ... */
#define __TIOCSIG            _IOW('T', 0x36, __signo_t) /* pty: generate signal */
#define __TIOCVHANGUP         _IO('T', 0x37) /* ... */
#define __TIOCGPKT           _IOR('T', 0x38, int) /* [int *] Get packet mode state */
#define __TIOCGPTLCK         _IOR('T', 0x39, int) /* [int *] Get Pty lock state */
#define __TIOCGEXCL          _IOR('T', 0x40, int) /* [int *] Get exclusive mode state */

#define __FIONCLEX            _IO('T', 0x50) /* Clear O_CLOEXEC / IO_CLOEXEC */
#define __FIOCLEX             _IO('T', 0x51) /* Set O_CLOEXEC / IO_CLOEXEC */
#define __FIOASYNC            _IO('T', 0x52) /* [int const *arg] Set (*arg != 0) or clear (*arg == 0) O_ASYNC / IO_ASYNC */
#define __TIOCSERCONFIG       _IO('T', 0x53) /* ... */
#define __TIOCSERGWILD        _IO('T', 0x54) /* ... */
#define __TIOCSERSWILD        _IO('T', 0x55) /* ... */
#define __TIOCGLCKTRMIOS      _IO('T', 0x56) /* ... */
#define __TIOCSLCKTRMIOS      _IO('T', 0x57) /* ... */
#define __TIOCSERGSTRUCT      _IO('T', 0x58) /* For debugging only */
#define __TIOCSERGETLSR       _IO('T', 0x59) /* Get line status register */
#define __TIOCSERGETMULTI     _IO('T', 0x5a) /* Get multiport config  */
#define __TIOCSERSETMULTI     _IO('T', 0x5b) /* Set multiport config */
#define __TIOCMIWAIT          _IO('T', 0x5c) /* wait for a change on serial input line(s) */
#define __TIOCGICOUNT         _IO('T', 0x5d) /* read serial port inline interrupt counts */
#define __FIOQSIZE            _IO('T', 0x60) /* [loff_t *arg] Return object data-size */

/* Used for packet mode */
#define __TIOCPKT_DATA       0x0000 /* ??? */
#define __TIOCPKT_FLUSHREAD  0x0001 /* ??? */
#define __TIOCPKT_FLUSHWRITE 0x0002 /* ??? */
#define __TIOCPKT_STOP       0x0004 /* ??? */
#define __TIOCPKT_START      0x0008 /* ??? */
#define __TIOCPKT_NOSTOP     0x0010 /* ??? */
#define __TIOCPKT_DOSTOP     0x0020 /* ??? */
#define __TIOCPKT_IOCTL      0x0040 /* ??? */

#define __TIOCSER_TEMT 0x01 /* Transmitter physically empty */

/* modem lines */
#define __TIOCM_LE   0x0001 /* ??? */
#define __TIOCM_DTR  0x0002 /* ??? */
#define __TIOCM_RTS  0x0004 /* ??? */
#define __TIOCM_ST   0x0008 /* ??? */
#define __TIOCM_SR   0x0010 /* ??? */
#define __TIOCM_CTS  0x0020 /* ??? */
#define __TIOCM_CAR  0x0040 /* ??? */
#define __TIOCM_RNG  0x0080 /* ??? */
#define __TIOCM_DSR  0x0100 /* ??? */
#define __TIOCM_OUT1 0x2000 /* ??? */
#define __TIOCM_OUT2 0x4000 /* ??? */
#define __TIOCM_LOOP 0x8000 /* ??? */


/************************************************************************/
/* Additional stuff normally only found on BSD                          */
/************************************************************************/
#ifdef __KOS__

/* Possible values for `FIODTYPE' */
#define __D_TAPE 0x0001 /* *unused* */
#define __D_DISK 0x0002 /* /dev/hda */
#define __D_TTY  0x0004 /* isatty() */
#define __D_MEM  0x0008 /* /dev/mem and /dev/kmem */

#define __FIODTYPE _IOR('f', 122, int) /* Returns set of `__D_*' */
#endif /* __KOS__ */

/* ??? */
#define __TIOCGPTPEER  _IO('T', 0x41)                          /* ??? */
#define __TIOCGISO7816 _IOR('T', 0x42, struct serial_iso7816)  /* ??? */
#define __TIOCSISO7816 _IOWR('T', 0x43, struct serial_iso7816) /* ??? */

#endif /* !_ASM_OS_KOS_TTY_H */
