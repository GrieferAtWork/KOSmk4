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
/* (#) Portability: libc4/5 (/include/bsd/sgtty.h) */
#ifndef _BSD_SGTTY_H
#define _BSD_SGTTY_H 1

#include <__stdinc.h>
#include <asm/os/tty.h>

#include <sgtty.h>
#include <termios.h>

#if !defined(TIOCGETP) && defined(__TIOCGETP)
#define TIOCGETP  __TIOCGETP  /* ???: 0x5481 */
#endif /* !TIOCGETP && __TIOCGETP */
#if !defined(TIOCSETP) && defined(__TIOCSETP)
#define TIOCSETP  __TIOCSETP  /* ???: 0x5482 */
#endif /* !TIOCSETP && __TIOCSETP */
#if !defined(TIOCGETC) && defined(__TIOCGETC)
#define TIOCGETC  __TIOCGETC  /* ???: 0x5483 */
#endif /* !TIOCGETC && __TIOCGETC */
#if !defined(TIOCSETC) && defined(__TIOCSETC)
#define TIOCSETC  __TIOCSETC  /* ???: 0x5484 */
#endif /* !TIOCSETC && __TIOCSETC */
#if !defined(TIOCGLTC) && defined(__TIOCGLTC)
#define TIOCGLTC  __TIOCGLTC  /* ???: 0x5485 */
#endif /* !TIOCGLTC && __TIOCGLTC */
#if !defined(TIOCSLTC) && defined(__TIOCSLTC)
#define TIOCSLTC  __TIOCSLTC  /* ???: 0x5486 */
#endif /* !TIOCSLTC && __TIOCSLTC */
#if !defined(TIOCLGET) && defined(__TIOCLGET)
#define TIOCLGET  __TIOCLGET  /* ???: 0x5487 */
#endif /* !TIOCLGET && __TIOCLGET */
#if !defined(TIOCLSET) && defined(__TIOCLSET)
#define TIOCLSET  __TIOCLSET  /* ???: 0x5488 */
#endif /* !TIOCLSET && __TIOCLSET */
#if !defined(TIOCFLUSH) && defined(__TIOCFLUSH)
#define TIOCFLUSH __TIOCFLUSH /* ???: 0x5489 */
#endif /* !TIOCFLUSH && __TIOCFLUSH */
#if !defined(TIOCSETN) && defined(__TIOCSETN)
#define TIOCSETN  __TIOCSETN  /* ???: 0x548a */
#endif /* !TIOCSETN && __TIOCSETN */


#if 0 /* ??? */

struct sgttyb {
	unsigned short sg_flags;
	char           sg_ispeed;
	char           sg_ospeed;
	char           sg_erase;
	char           sg_kill;
	struct termios t;
	int            check;
};

struct tchars {
	char t_intrc;
	char t_quitc;
	char t_eofc;
	char t_startc;
	char t_stopc;
	char t_brkc;
};

struct ltchars {
	char t_werasc;
	char t_suspc;
	char t_dsuspc;
	char t_rprntc;
	char t_flushc;
	char t_lnextc;
};

#define O_RAW     1
#define O_LCASE   2
#define O_CRMOD   4
#define O_ECHO    8
#define O_ODDP    16
#define O_EVENP   32
#define O_CBREAK  64
#define O_TBDELAY 0
#define O_LLITOUT 0
#define O_XTABS   0
#define O_ANYP    0

#ifndef _SGTTY_SOURCE
#undef ioctl
#define ioctl bsd_ioctl

#undef RAW
#undef LCASE
#undef ECHO
#undef CRMOD
#undef ODDP
#undef EVENP
#undef CBREAK
#undef TBDELAY
#undef LLITOUT
#undef XTABS
#undef ANYP
#define RAW     O_RAW
#define LCASE   O_LCASE
#define ECHO    O_ECHO
#define CRMOD   O_CRMOD
#define ODDP    O_ODDP
#define EVENP   O_EVENP
#define CBREAK  O_CBREAK
#define TBDELAY O_TBDELAY
#define LLITOUT O_LLITOUT
#define XTABS   O_XTABS
#define ANYP    O_ANYP
#endif /*!_SGTTY_SOURCE */

#endif /* 0 */

#endif /* !_BSD_SGTTY_H */
