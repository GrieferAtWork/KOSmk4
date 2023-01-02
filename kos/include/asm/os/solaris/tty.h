/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_SOLARIS_TTY_H
#define _ASM_OS_SOLARIS_TTY_H 1

#include <asm/ioctl.h>

#define __TIOC         ('T' << 8)
#define __TCGETA       _IO('T', 1)
#define __TCSETA       _IO('T', 2)
#define __TCSETAW      _IO('T', 3)
#define __TCSETAF      _IO('T', 4)
#define __TCSBRK       _IO('T', 5)
#define __TCXONC       _IO('T', 6)
#define __TCFLSH       _IO('T', 7)
#define __TIOCKBON     _IO('T', 8)
#define __TIOCKBOF     _IO('T', 9)
#define __KBENABLED    _IO('T', 10)
#define __IOCTYPE      0xff00
#define __TCDSET       _IO('T', 32)
#define __RTS_TOG      _IO('T', 33)
#define __TIOCGWINSZ   _IO('T', 104)
#define __TIOCSWINSZ   _IO('T', 103)
#define __TIOCGSOFTCAR _IO('T', 105)
#define __TIOCSSOFTCAR _IO('T', 106)
#define __TCGETS       _IO('T', 13)
#define __TCSETS       _IO('T', 14)
#define __TCSANOW      _IO('T', 14)
#define __TCSETSW      _IO('T', 15)
#define __TCSADRAIN    _IO('T', 15)
#define __TCSETSF      _IO('T', 16)
#define __TIOCSETLD    _IO('T', 123)
#define __TIOCGETLD    _IO('T', 124)
#define __TIOCGPPS     _IO('T', 125)
#define __TIOCSPPS     _IO('T', 126)
#define __TIOCGPPSEV   _IO('T', 127)
#define __TCSAFLUSH    _IO('T', 16)
#define __tIOC         ('t' << 8)
#define __TIOCGETD     _IO('t', 0)
#define __TIOCSETD     _IO('t', 1)
#define __TIOCHPCL     _IO('t', 2)
#define __TIOCGETP     _IO('t', 8)
#define __TIOCSETP     _IO('t', 9)
#define __TIOCSETN     _IO('t', 10)
#define __TIOCEXCL     _IO('t', 13)
#define __TIOCNXCL     _IO('t', 14)
#define __TIOCFLUSH    _IO('t', 16)
#define __TIOCSETC     _IO('t', 17)
#define __TIOCGETC     _IO('t', 18)
#define __TIOCLBIS     _IO('t', 127)
#define __TIOCLBIC     _IO('t', 126)
#define __TIOCLSET     _IO('t', 125)
#define __TIOCLGET     _IO('t', 124)
#define __TIOCSBRK     _IO('t', 123)
#define __TIOCCBRK     _IO('t', 122)
#define __TIOCSDTR     _IO('t', 121)
#define __TIOCCDTR     _IO('t', 120)
#define __TIOCSLTC     _IO('t', 117)
#define __TIOCGLTC     _IO('t', 116)
#define __TIOCOUTQ     _IO('t', 115)
#define __TIOCNOTTY    _IO('t', 113)
#define __TIOCSCTTY    _IO('t', 132)
#define __TIOCSTOP     _IO('t', 111) /* Emulate ^S */
#define __TIOCSTART    _IO('t', 110) /* Emulate ^Q */
#define __TIOCSILOOP   _IO('t', 109)
#define __TIOCGPGRP    _IO('t', 20)
#define __TIOCSPGRP    _IO('t', 21)
#define __TIOCGSID     _IO('t', 22)
#define __TIOCSTI      _IO('t', 23)
#define __TIOCMSET     _IO('t', 26)
#define __TIOCMBIS     _IO('t', 27)
#define __TIOCMBIC     _IO('t', 28)
#define __TIOCMGET     _IO('t', 29)
#define __TIOCM_LE     0001
#define __TIOCM_DTR    0002
#define __TIOCM_RTS    0004
#define __TIOCM_ST     0010
#define __TIOCM_SR     0020
#define __TIOCM_CTS    0040
#define __TIOCM_CAR    0100
#define __TIOCM_CD     __TIOCM_CAR
#define __TIOCM_RNG    0200
#define __TIOCM_RI     __TIOCM_RNG
#define __TIOCM_DSR    0400
#define __TIOCREMOTE   _IO('t', 30)
#define __TIOCSIGNAL   _IO('t', 31)
#define __LDIOC        ('D' << 8)
#define __LDOPEN       _IO('D', 0)
#define __LDCLOSE      _IO('D', 1)
#define __LDCHG        _IO('D', 2)
#define __LDGETT       _IO('D', 8)
#define __LDSETT       _IO('D', 9)
#define __LDSMAP       _IO('D', 110)
#define __LDGMAP       _IO('D', 111)
#define __LDNMAP       _IO('D', 112)
#define __LDEMAP       _IO('D', 113)
#define __LDDMAP       _IO('D', 114)
#define __DIOC         ('d' << 8)
#define __DIOCGETP     _IO('d', 8)
#define __DIOCSETP     _IO('d', 9)
#define __FIORDCHK     (('f' << 8) | 3)

#ifdef __CC__
__DECL_BEGIN

struct lx_cc {
	unsigned char veof;
	unsigned char veol;
	unsigned char vmin;
	unsigned char vtime;
};

//struct ppsclockev {
//	struct timeval tv;
//	uint_t     serial;
//};

__DECL_END
#endif

#endif /* !_ASM_OS_SOLARIS_TTY_H */
