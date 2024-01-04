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
/* (#) Portability: Linux (/usr/include/[...]/asm/ioctls.h) */
#ifndef _ASM_IOCTLS_H
#define _ASM_IOCTLS_H 1

#include <asm/os/tty.h>
#include <linux/ioctl.h>

/************************************************************************/
/* TTY IOCTLS                                                           */
/************************************************************************/

#if !defined(TCGETS) && defined(__TCGETS)
#define TCGETS  __TCGETS  /* [struct termio *arg] Get terminal attributes */
#endif /* !TCGETS && __TCGETS */
#if !defined(TCSETS) && defined(__TCSETS)
#define TCSETS  __TCSETS  /* [struct termio const *arg] Set terminal attributes */
#endif /* !TCSETS && __TCSETS */
#if !defined(TCSETSW) && defined(__TCSETSW)
#define TCSETSW __TCSETSW /* [struct termio const *arg] Wait for all unwritten data to be transmitted, discard all unread data, then set terminal attributes */
#endif /* !TCSETSW && __TCSETSW */
#if !defined(TCSETSF) && defined(__TCSETSF)
#define TCSETSF __TCSETSF /* [struct termio const *arg] Wait for all unwritten data to be transmitted, then set terminal attributes */
#endif /* !TCSETSF && __TCSETSF */
#if !defined(TCGETA) && defined(__TCGETA)
#define TCGETA  __TCGETA  /* [struct termios *arg] Get terminal attributes */
#endif /* !TCGETA && __TCGETA */
#if !defined(TCSETA) && defined(__TCSETA)
#define TCSETA  __TCSETA  /* [struct termios const *arg] Set terminal attributes */
#endif /* !TCSETA && __TCSETA */
#if !defined(TCSETAW) && defined(__TCSETAW)
#define TCSETAW __TCSETAW /* [struct termios const *arg] Wait for all unwritten data to be transmitted, discard all unread data, then set terminal attributes */
#endif /* !TCSETAW && __TCSETAW */
#if !defined(TCSETAF) && defined(__TCSETAF)
#define TCSETAF __TCSETAF /* [struct termios const *arg] Wait for all unwritten data to be transmitted, then set terminal attributes */
#endif /* !TCSETAF && __TCSETAF */
#if !defined(TCSBRK) && defined(__TCSBRK)
#define TCSBRK  __TCSBRK  /* [int arg] Send a break (arg should be 0 for portability, but is ignored when non-zero) */
#endif /* !TCSBRK && __TCSBRK */
#if !defined(TCXONC) && defined(__TCXONC)
#define TCXONC  __TCXONC  /* [int arg = { TCOOFF, TCOON, TCIOFF, TCION }] */
#endif /* !TCXONC && __TCXONC */
#if !defined(TCFLSH) && defined(__TCFLSH)
#define TCFLSH  __TCFLSH  /* [int arg = { TCIFLUSH, TCOFLUSH, TCIOFLUSH }] */
#endif /* !TCFLSH && __TCFLSH */

#if !defined(TIOCEXCL) && defined(__TIOCEXCL)
#define TIOCEXCL  __TIOCEXCL    /* ... */
#endif /* !TIOCEXCL && __TIOCEXCL */
#if !defined(TIOCNXCL) && defined(__TIOCNXCL)
#define TIOCNXCL  __TIOCNXCL    /* ... */
#endif /* !TIOCNXCL && __TIOCNXCL */
#if !defined(TIOCSCTTY) && defined(__TIOCSCTTY)
#define TIOCSCTTY __TIOCSCTTY   /* [int steal_if_necessary] Make this terminal the controlling terminal of the calling process */
#endif /* !TIOCSCTTY && __TIOCSCTTY */
#if !defined(TIOCGPGRP) && defined(__TIOCGPGRP)
#define TIOCGPGRP  __TIOCGPGRP  /* [pid_t *arg] Store the PID of the foreground process group in arg */
#endif /* !TIOCGPGRP && __TIOCGPGRP */
#if !defined(TIOCSPGRP) && defined(__TIOCSPGRP)
#define TIOCSPGRP  __TIOCSPGRP  /* [pid_t const *arg] Load the PID of the foreground process group from arg */
#endif /* !TIOCSPGRP && __TIOCSPGRP */
#if !defined(TIOCOUTQ) && defined(__TIOCOUTQ)
#define TIOCOUTQ   __TIOCOUTQ   /* [int *count] Save the number of pending output bytes */
#endif /* !TIOCOUTQ && __TIOCOUTQ */
#if !defined(TIOCSTI) && defined(__TIOCSTI)
#define TIOCSTI    __TIOCSTI    /* [char const *byte] Insert the given byte in the input queue. */
#endif /* !TIOCSTI && __TIOCSTI */
#if !defined(TIOCGWINSZ) && defined(__TIOCGWINSZ)
#define TIOCGWINSZ __TIOCGWINSZ /* [struct winsize *arg] Get the window size */
#endif /* !TIOCGWINSZ && __TIOCGWINSZ */
#if !defined(TIOCSWINSZ) && defined(__TIOCSWINSZ)
#define TIOCSWINSZ __TIOCSWINSZ /* [struct winsize const *arg] Set the window size */
#endif /* !TIOCSWINSZ && __TIOCSWINSZ */
#if !defined(TIOCMGET) && defined(__TIOCMGET)
#define TIOCMGET   __TIOCMGET   /* [unsigned int *argp] Get status of modem bits (set of `TIOCM_*') */
#endif /* !TIOCMGET && __TIOCMGET */
#if !defined(TIOCMBIS) && defined(__TIOCMBIS)
#define TIOCMBIS   __TIOCMBIS   /* [unsigned int *argp] Enable modem bits (bits |= *argp) (set of `TIOCM_*') */
#endif /* !TIOCMBIS && __TIOCMBIS */
#if !defined(TIOCMBIC) && defined(__TIOCMBIC)
#define TIOCMBIC   __TIOCMBIC   /* [unsigned int *argp] Clear modem bits (bits &= ~*argp) (set of `TIOCM_*') */
#endif /* !TIOCMBIC && __TIOCMBIC */
#if !defined(TIOCMSET) && defined(__TIOCMSET)
#define TIOCMSET   __TIOCMSET   /* [unsigned int *argp] Set modem bits (bits = *argp) (set of `TIOCM_*') */
#endif /* !TIOCMSET && __TIOCMSET */

#if !defined(TIOCGSOFTCAR) && defined(__TIOCGSOFTCAR)
#define TIOCGSOFTCAR __TIOCGSOFTCAR /* [int *arg] Get the state of `termios::c_cflag::CLOCAL'. */
#endif /* !TIOCGSOFTCAR && __TIOCGSOFTCAR */
#if !defined(TIOCSSOFTCAR) && defined(__TIOCSSOFTCAR)
#define TIOCSSOFTCAR __TIOCSSOFTCAR /* [int const *arg] Set the state of `termios::c_cflag::CLOCAL'. */
#endif /* !TIOCSSOFTCAR && __TIOCSSOFTCAR */
#if !defined(TIOCINQ) && defined(__TIOCINQ)
#define TIOCINQ      __TIOCINQ      /* [int *count] Save the number of pending input bytes */
#endif /* !TIOCINQ && __TIOCINQ */
#if !defined(FIONREAD) && defined(__TIOCINQ)
#define FIONREAD     __TIOCINQ      /* [int *count] Save the number of pending input bytes */
#endif /* !FIONREAD && __TIOCINQ */
#if !defined(TIOCLINUX) && defined(__TIOCLINUX)
#define TIOCLINUX    __TIOCLINUX    /* ... */
#endif /* !TIOCLINUX && __TIOCLINUX */
#if !defined(TIOCCONS) && defined(__TIOCCONS)
#define TIOCCONS     __TIOCCONS     /* ... */
#endif /* !TIOCCONS && __TIOCCONS */
#if !defined(TIOCGSERIAL) && defined(__TIOCGSERIAL)
#define TIOCGSERIAL  __TIOCGSERIAL  /* ... */
#endif /* !TIOCGSERIAL && __TIOCGSERIAL */
#if !defined(TIOCSSERIAL) && defined(__TIOCSSERIAL)
#define TIOCSSERIAL  __TIOCSSERIAL  /* ... */
#endif /* !TIOCSSERIAL && __TIOCSSERIAL */
#if !defined(TIOCPKT) && defined(__TIOCPKT)
#define TIOCPKT      __TIOCPKT      /* ... */
#endif /* !TIOCPKT && __TIOCPKT */
#if !defined(FIONBIO) && defined(__FIONBIO)
#define FIONBIO      __FIONBIO      /* [int const *arg] Set (*arg != 0) or clear (*arg == 0) O_NONBLOCK / IO_NONBLOCK */
#endif /* !FIONBIO && __FIONBIO */
#if !defined(TIOCNOTTY) && defined(__TIOCNOTTY)
#define TIOCNOTTY    __TIOCNOTTY    /* Given up control over this CTTY */
#endif /* !TIOCNOTTY && __TIOCNOTTY */
#if !defined(TIOCSETD) && defined(__TIOCSETD)
#define TIOCSETD    __TIOCSETD      /* [int const *ld] Set the terminal's line discipline to *ld */
#endif /* !TIOCSETD && __TIOCSETD */
#if !defined(TIOCGETD) && defined(__TIOCGETD)
#define TIOCGETD    __TIOCGETD      /* [int *result] Store the terminal's line discipline in *result */
#endif /* !TIOCGETD && __TIOCGETD */
#if !defined(TCSBRKP) && defined(__TCSBRKP)
#define TCSBRKP     __TCSBRKP       /* [int deciseconds] Needed for POSIX tcsendbreak() */
#endif /* !TCSBRKP && __TCSBRKP */
#if !defined(TIOCSBRK) && defined(__TIOCSBRK)
#define TIOCSBRK    __TIOCSBRK      /* BSD compatibility */
#endif /* !TIOCSBRK && __TIOCSBRK */
#if !defined(TIOCCBRK) && defined(__TIOCCBRK)
#define TIOCCBRK    __TIOCCBRK      /* BSD compatibility */
#endif /* !TIOCCBRK && __TIOCCBRK */
#if !defined(TIOCGSID) && defined(__TIOCGSID)
#define TIOCGSID    __TIOCGSID      /* [pid_t *arg] Return the session ID of a tty */
#endif /* !TIOCGSID && __TIOCGSID */
#if !defined(TCGETS2) && defined(__TCGETS2)
#define TCGETS2     __TCGETS2       /* ... */
#endif /* !TCGETS2 && __TCGETS2 */
#if !defined(TCSETS2) && defined(__TCSETS2)
#define TCSETS2     __TCSETS2       /* ... */
#endif /* !TCSETS2 && __TCSETS2 */
#if !defined(TCSETSW2) && defined(__TCSETSW2)
#define TCSETSW2    __TCSETSW2      /* ... */
#endif /* !TCSETSW2 && __TCSETSW2 */
#if !defined(TCSETSF2) && defined(__TCSETSF2)
#define TCSETSF2    __TCSETSF2      /* ... */
#endif /* !TCSETSF2 && __TCSETSF2 */
#if !defined(TIOCGRS485) && defined(__TIOCGRS485)
#define TIOCGRS485  __TIOCGRS485    /* ... */
#endif /* !TIOCGRS485 && __TIOCGRS485 */
#if !defined(TIOCSRS485) && defined(__TIOCSRS485)
#define TIOCSRS485  __TIOCSRS485    /* ... */
#endif /* !TIOCSRS485 && __TIOCSRS485 */
#if !defined(TIOCGPTN) && defined(__TIOCGPTN)
#define TIOCGPTN    __TIOCGPTN      /* Get Pty Number (of pty-mux device) */
#endif /* !TIOCGPTN && __TIOCGPTN */
#if !defined(TIOCSPTLCK) && defined(__TIOCSPTLCK)
#define TIOCSPTLCK  __TIOCSPTLCK    /* Lock/unlock Pty */
#endif /* !TIOCSPTLCK && __TIOCSPTLCK */
#if !defined(TIOCGDEV) && defined(__TIOCGDEV)
#define TIOCGDEV    __TIOCGDEV      /* Get primary device node of /dev/console */
#endif /* !TIOCGDEV && __TIOCGDEV */
#if !defined(TCGETX) && defined(__TCGETX)
#define TCGETX      __TCGETX        /* SYS5 TCGETX compatibility */
#endif /* !TCGETX && __TCGETX */
#if !defined(TCSETX) && defined(__TCSETX)
#define TCSETX      __TCSETX        /* ... */
#endif /* !TCSETX && __TCSETX */
#if !defined(TCSETXF) && defined(__TCSETXF)
#define TCSETXF     __TCSETXF       /* ... */
#endif /* !TCSETXF && __TCSETXF */
#if !defined(TCSETXW) && defined(__TCSETXW)
#define TCSETXW     __TCSETXW       /* ... */
#endif /* !TCSETXW && __TCSETXW */
#if !defined(TIOCSIG) && defined(__TIOCSIG)
#define TIOCSIG     __TIOCSIG       /* pty: generate signal */
#endif /* !TIOCSIG && __TIOCSIG */
#if !defined(TIOCVHANGUP) && defined(__TIOCVHANGUP)
#define TIOCVHANGUP __TIOCVHANGUP   /* ... */
#endif /* !TIOCVHANGUP && __TIOCVHANGUP */
#if !defined(TIOCGPKT) && defined(__TIOCGPKT)
#define TIOCGPKT    __TIOCGPKT      /* Get packet mode state */
#endif /* !TIOCGPKT && __TIOCGPKT */
#if !defined(TIOCGPTLCK) && defined(__TIOCGPTLCK)
#define TIOCGPTLCK  __TIOCGPTLCK    /* Get Pty lock state */
#endif /* !TIOCGPTLCK && __TIOCGPTLCK */
#if !defined(TIOCGEXCL) && defined(__TIOCGEXCL)
#define TIOCGEXCL   __TIOCGEXCL     /* Get exclusive mode state */
#endif /* !TIOCGEXCL && __TIOCGEXCL */

#if !defined(FIONCLEX) && defined(__FIONCLEX)
#define FIONCLEX        __FIONCLEX        /* Clear O_CLOEXEC / IO_CLOEXEC */
#endif /* !FIONCLEX && __FIONCLEX */
#if !defined(FIOCLEX) && defined(__FIOCLEX)
#define FIOCLEX         __FIOCLEX         /* Set O_CLOEXEC / IO_CLOEXEC */
#endif /* !FIOCLEX && __FIOCLEX */
#if !defined(FIOASYNC) && defined(__FIOASYNC)
#define FIOASYNC        __FIOASYNC        /* [int const *arg] Set (*arg != 0) or clear (*arg == 0) O_ASYNC / IO_ASYNC */
#endif /* !FIOASYNC && __FIOASYNC */
#if !defined(TIOCSERCONFIG) && defined(__TIOCSERCONFIG)
#define TIOCSERCONFIG   __TIOCSERCONFIG   /* ... */
#endif /* !TIOCSERCONFIG && __TIOCSERCONFIG */
#if !defined(TIOCSERGWILD) && defined(__TIOCSERGWILD)
#define TIOCSERGWILD    __TIOCSERGWILD    /* ... */
#endif /* !TIOCSERGWILD && __TIOCSERGWILD */
#if !defined(TIOCSERSWILD) && defined(__TIOCSERSWILD)
#define TIOCSERSWILD    __TIOCSERSWILD    /* ... */
#endif /* !TIOCSERSWILD && __TIOCSERSWILD */
#if !defined(TIOCGLCKTRMIOS) && defined(__TIOCGLCKTRMIOS)
#define TIOCGLCKTRMIOS  __TIOCGLCKTRMIOS  /* ... */
#endif /* !TIOCGLCKTRMIOS && __TIOCGLCKTRMIOS */
#if !defined(TIOCSLCKTRMIOS) && defined(__TIOCSLCKTRMIOS)
#define TIOCSLCKTRMIOS  __TIOCSLCKTRMIOS  /* ... */
#endif /* !TIOCSLCKTRMIOS && __TIOCSLCKTRMIOS */
#if !defined(TIOCSERGSTRUCT) && defined(__TIOCSERGSTRUCT)
#define TIOCSERGSTRUCT  __TIOCSERGSTRUCT  /* For debugging only */
#endif /* !TIOCSERGSTRUCT && __TIOCSERGSTRUCT */
#if !defined(TIOCSERGETLSR) && defined(__TIOCSERGETLSR)
#define TIOCSERGETLSR   __TIOCSERGETLSR   /* Get line status register */
#endif /* !TIOCSERGETLSR && __TIOCSERGETLSR */
#if !defined(TIOCSERGETMULTI) && defined(__TIOCSERGETMULTI)
#define TIOCSERGETMULTI __TIOCSERGETMULTI /* Get multiport config  */
#endif /* !TIOCSERGETMULTI && __TIOCSERGETMULTI */
#if !defined(TIOCSERSETMULTI) && defined(__TIOCSERSETMULTI)
#define TIOCSERSETMULTI __TIOCSERSETMULTI /* Set multiport config */
#endif /* !TIOCSERSETMULTI && __TIOCSERSETMULTI */
#if !defined(TIOCMIWAIT) && defined(__TIOCMIWAIT)
#define TIOCMIWAIT      __TIOCMIWAIT      /* wait for a change on serial input line(s) */
#endif /* !TIOCMIWAIT && __TIOCMIWAIT */
#if !defined(TIOCGICOUNT) && defined(__TIOCGICOUNT)
#define TIOCGICOUNT     __TIOCGICOUNT     /* read serial port inline interrupt counts */
#endif /* !TIOCGICOUNT && __TIOCGICOUNT */
#if !defined(FIOQSIZE) && defined(__FIOQSIZE)
#define FIOQSIZE        __FIOQSIZE        /* [loff_t *arg] Return object data-size */
#endif /* !FIOQSIZE && __FIOQSIZE */

/* Used for packet mode */
#if !defined(TIOCPKT_DATA) && defined(__TIOCPKT_DATA)
#define TIOCPKT_DATA       __TIOCPKT_DATA       /* ??? */
#endif /* !TIOCPKT_DATA && __TIOCPKT_DATA */
#if !defined(TIOCPKT_FLUSHREAD) && defined(__TIOCPKT_FLUSHREAD)
#define TIOCPKT_FLUSHREAD  __TIOCPKT_FLUSHREAD  /* ??? */
#endif /* !TIOCPKT_FLUSHREAD && __TIOCPKT_FLUSHREAD */
#if !defined(TIOCPKT_FLUSHWRITE) && defined(__TIOCPKT_FLUSHWRITE)
#define TIOCPKT_FLUSHWRITE __TIOCPKT_FLUSHWRITE /* ??? */
#endif /* !TIOCPKT_FLUSHWRITE && __TIOCPKT_FLUSHWRITE */
#if !defined(TIOCPKT_STOP) && defined(__TIOCPKT_STOP)
#define TIOCPKT_STOP       __TIOCPKT_STOP       /* ??? */
#endif /* !TIOCPKT_STOP && __TIOCPKT_STOP */
#if !defined(TIOCPKT_START) && defined(__TIOCPKT_START)
#define TIOCPKT_START      __TIOCPKT_START      /* ??? */
#endif /* !TIOCPKT_START && __TIOCPKT_START */
#if !defined(TIOCPKT_NOSTOP) && defined(__TIOCPKT_NOSTOP)
#define TIOCPKT_NOSTOP     __TIOCPKT_NOSTOP     /* ??? */
#endif /* !TIOCPKT_NOSTOP && __TIOCPKT_NOSTOP */
#if !defined(TIOCPKT_DOSTOP) && defined(__TIOCPKT_DOSTOP)
#define TIOCPKT_DOSTOP     __TIOCPKT_DOSTOP     /* ??? */
#endif /* !TIOCPKT_DOSTOP && __TIOCPKT_DOSTOP */
#if !defined(TIOCPKT_IOCTL) && defined(__TIOCPKT_IOCTL)
#define TIOCPKT_IOCTL      __TIOCPKT_IOCTL      /* ??? */
#endif /* !TIOCPKT_IOCTL && __TIOCPKT_IOCTL */

#if !defined(TIOCSER_TEMT) && defined(__TIOCSER_TEMT)
#define TIOCSER_TEMT __TIOCSER_TEMT /* Transmitter physically empty */
#endif /* !TIOCSER_TEMT && __TIOCSER_TEMT */

/* ??? */
#if !defined(TIOCGPTPEER) && defined(__TIOCGPTPEER)
#define TIOCGPTPEER  __TIOCGPTPEER  /* ??? */
#endif /* !TIOCGPTPEER && __TIOCGPTPEER */
#if !defined(TIOCGISO7816) && defined(__TIOCGISO7816)
#define TIOCGISO7816 __TIOCGISO7816 /* ??? */
#endif /* !TIOCGISO7816 && __TIOCGISO7816 */
#if !defined(TIOCSISO7816) && defined(__TIOCSISO7816)
#define TIOCSISO7816 __TIOCSISO7816 /* ??? */
#endif /* !TIOCSISO7816 && __TIOCSISO7816 */

#endif /* !_ASM_IOCTLS_H */
