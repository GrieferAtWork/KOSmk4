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
%(c_prefix){
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/ioctl.h) */
/* (#) Portability: DJGPP         (/include/sys/ioctl.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/ioctl.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/ioctl.h) */
/* (#) Portability: FreeBSD       (/sys/sys/ioctl.h) */
/* (#) Portability: GNU C Library (/misc/sys/ioctl.h) */
/* (#) Portability: NetBSD        (/sys/sys/ioctl.h) */
/* (#) Portability: OpenBSD       (/sys/sys/ioctl.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/ioctl.h) */
/* (#) Portability: diet libc     (/include/sys/ioctl.h) */
/* (#) Portability: libc4/5       (/include/sys/ioctl.h) */
/* (#) Portability: mintlib       (/include/sys/ioctl.h) */
/* (#) Portability: musl libc     (/include/sys/ioctl.h) */
/* (#) Portability: uClibc        (/include/sys/ioctl.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(ulongptr_t = __ULONGPTR_TYPE__)]
%[default:section(".text.crt{|.dos}.io.utility")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/ioctl.h>
)]%[insert:prefix(
#include <asm/os/socket-ioctls.h>
)]%[insert:prefix(
#include <asm/os/tty.h>
)]%[insert:prefix(
#include <bits/os/termio.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <sys/ttydefaults.h>
)]%{


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
#define TIOCMBIS   __TIOCMBIS   /* [unsigned int const *argp] Enable modem bits (bits |= *argp) (set of `TIOCM_*') */
#endif /* !TIOCMBIS && __TIOCMBIS */
#if !defined(TIOCMBIC) && defined(__TIOCMBIC)
#define TIOCMBIC   __TIOCMBIC   /* [unsigned int const *argp] Clear modem bits (bits &= ~*argp) (set of `TIOCM_*') */
#endif /* !TIOCMBIC && __TIOCMBIC */
#if !defined(TIOCMSET) && defined(__TIOCMSET)
#define TIOCMSET   __TIOCMSET   /* [unsigned int const *argp] Set modem bits (bits = *argp) (set of `TIOCM_*') */
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
#define FIONBIO      __FIONBIO      /* [int *arg] Set (*arg != 0) or clear (*arg == 0) O_NONBLOCK / IO_NONBLOCK */
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
#define TCGETS2     __TCGETS2       /* [struct termios2 *arg] ... */
#endif /* !TCGETS2 && __TCGETS2 */
#if !defined(TCSETS2) && defined(__TCSETS2)
#define TCSETS2     __TCSETS2       /* [struct termios2 const *arg] ... */
#endif /* !TCSETS2 && __TCSETS2 */
#if !defined(TCSETSW2) && defined(__TCSETSW2)
#define TCSETSW2    __TCSETSW2      /* [struct termios2 const *arg] ... */
#endif /* !TCSETSW2 && __TCSETSW2 */
#if !defined(TCSETSF2) && defined(__TCSETSF2)
#define TCSETSF2    __TCSETSF2      /* [struct termios2 const *arg] ... */
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
#define TCGETX      __TCGETX        /* [struct termiox *arg] SYS5 TCGETX compatibility */
#endif /* !TCGETX && __TCGETX */
#if !defined(TCSETX) && defined(__TCSETX)
#define TCSETX      __TCSETX        /* [struct termiox const *arg] ... */
#endif /* !TCSETX && __TCSETX */
#if !defined(TCSETXF) && defined(__TCSETXF)
#define TCSETXF     __TCSETXF       /* [struct termiox const *arg] ... */
#endif /* !TCSETXF && __TCSETXF */
#if !defined(TCSETXW) && defined(__TCSETXW)
#define TCSETXW     __TCSETXW       /* [struct termiox const *arg] ... */
#endif /* !TCSETXW && __TCSETXW */
#if !defined(TIOCSIG) && defined(__TIOCSIG)
#define TIOCSIG     __TIOCSIG       /* pty: generate signal */
#endif /* !TIOCSIG && __TIOCSIG */
#if !defined(TIOCVHANGUP) && defined(__TIOCVHANGUP)
#define TIOCVHANGUP __TIOCVHANGUP   /* ... */
#endif /* !TIOCVHANGUP && __TIOCVHANGUP */
#if !defined(TIOCGPKT) && defined(__TIOCGPKT)
#define TIOCGPKT    __TIOCGPKT      /* [int *] Get packet mode state */
#endif /* !TIOCGPKT && __TIOCGPKT */
#if !defined(TIOCGPTLCK) && defined(__TIOCGPTLCK)
#define TIOCGPTLCK  __TIOCGPTLCK    /* [int *] Get Pty lock state */
#endif /* !TIOCGPTLCK && __TIOCGPTLCK */
#if !defined(TIOCGEXCL) && defined(__TIOCGEXCL)
#define TIOCGEXCL   __TIOCGEXCL     /* [int *] Get exclusive mode state */
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

/* modem lines */
#if !defined(TIOCM_LE) && defined(__TIOCM_LE)
#define TIOCM_LE  __TIOCM_LE  /* ??? */
#endif /* !TIOCM_LE && __TIOCM_LE */
#if !defined(TIOCM_DTR) && defined(__TIOCM_DTR)
#define TIOCM_DTR __TIOCM_DTR /* ??? */
#endif /* !TIOCM_DTR && __TIOCM_DTR */
#if !defined(TIOCM_RTS) && defined(__TIOCM_RTS)
#define TIOCM_RTS __TIOCM_RTS /* ??? */
#endif /* !TIOCM_RTS && __TIOCM_RTS */
#if !defined(TIOCM_ST) && defined(__TIOCM_ST)
#define TIOCM_ST  __TIOCM_ST  /* ??? */
#endif /* !TIOCM_ST && __TIOCM_ST */
#if !defined(TIOCM_SR) && defined(__TIOCM_SR)
#define TIOCM_SR  __TIOCM_SR  /* ??? */
#endif /* !TIOCM_SR && __TIOCM_SR */
#if !defined(TIOCM_CTS) && defined(__TIOCM_CTS)
#define TIOCM_CTS __TIOCM_CTS /* ??? */
#endif /* !TIOCM_CTS && __TIOCM_CTS */
#if !defined(TIOCM_CAR) && defined(__TIOCM_CAR)
#define TIOCM_CAR __TIOCM_CAR /* ??? */
#endif /* !TIOCM_CAR && __TIOCM_CAR */
#if !defined(TIOCM_RNG) && defined(__TIOCM_RNG)
#define TIOCM_RNG __TIOCM_RNG /* ??? */
#endif /* !TIOCM_RNG && __TIOCM_RNG */
#if !defined(TIOCM_DSR) && defined(__TIOCM_DSR)
#define TIOCM_DSR __TIOCM_DSR /* ??? */
#endif /* !TIOCM_DSR && __TIOCM_DSR */
#if !defined(TIOCM_CD) && defined(__TIOCM_CAR)
#define TIOCM_CD  __TIOCM_CAR /* Alias */
#endif /* !TIOCM_CD && __TIOCM_CAR */
#if !defined(TIOCM_RI) && defined(__TIOCM_RNG)
#define TIOCM_RI  __TIOCM_RNG /* Alias */
#endif /* !TIOCM_RI && __TIOCM_RNG */




/************************************************************************/
/* SOCKET IOCTLS                                                        */
/************************************************************************/
#if !defined(SIOCINQ) && defined(__TIOCINQ)
#define SIOCINQ  __TIOCINQ  /* [int *count] Save the number of pending input bytes */
#endif /* !SIOCINQ && __TIOCINQ */
#if !defined(SIOCOUTQ) && defined(__TIOCOUTQ)
#define SIOCOUTQ __TIOCOUTQ /* output queue size (not sent + not acked) */
#endif /* !SIOCOUTQ && __TIOCOUTQ */

#ifdef __USE_TIME_BITS64
#if !defined(SIOCGSTAMP) && defined(__SIOCGSTAMP64)
#define SIOCGSTAMP   __SIOCGSTAMP64   /* [struct timeval *arg] Get stamp */
#endif /* !SIOCGSTAMP && __SIOCGSTAMP64 */
#if !defined(SIOCGSTAMPNS) && defined(__SIOCGSTAMPNS64)
#define SIOCGSTAMPNS __SIOCGSTAMPNS64 /* [struct timespec *arg] Get stamp */
#endif /* !SIOCGSTAMPNS && __SIOCGSTAMPNS64 */
#else /* __USE_TIME_BITS64 */
#if !defined(SIOCGSTAMP) && defined(__SIOCGSTAMP32)
#define SIOCGSTAMP   __SIOCGSTAMP32   /* [struct timeval *arg] Get stamp */
#endif /* !SIOCGSTAMP && __SIOCGSTAMP32 */
#if !defined(SIOCGSTAMPNS) && defined(__SIOCGSTAMPNS32)
#define SIOCGSTAMPNS __SIOCGSTAMPNS32 /* [struct timespec *arg] Get stamp */
#endif /* !SIOCGSTAMPNS && __SIOCGSTAMPNS32 */
#endif /* !__USE_TIME_BITS64 */

#ifdef __USE_KOS
#if !defined(SIOCGSTAMP32) && defined(__SIOCGSTAMP32)
#define SIOCGSTAMP32   __SIOCGSTAMP32   /* [struct timeval32 *arg] Get stamp */
#endif /* !SIOCGSTAMP32 && __SIOCGSTAMP32 */
#if !defined(SIOCGSTAMPNS32) && defined(__SIOCGSTAMPNS32)
#define SIOCGSTAMPNS32 __SIOCGSTAMPNS32 /* [struct timespec32 *arg] Get stamp */
#endif /* !SIOCGSTAMPNS32 && __SIOCGSTAMPNS32 */
#endif /* __USE_KOS */

#ifdef __USE_TIME64
#if !defined(SIOCGSTAMP64) && defined(__SIOCGSTAMP64)
#define SIOCGSTAMP64   __SIOCGSTAMP64   /* [struct timeval64 *arg] Get stamp */
#endif /* !SIOCGSTAMP64 && __SIOCGSTAMP64 */
#if !defined(SIOCGSTAMPNS64) && defined(__SIOCGSTAMPNS64)
#define SIOCGSTAMPNS64 __SIOCGSTAMPNS64 /* [struct timespec64 *arg] Get stamp */
#endif /* !SIOCGSTAMPNS64 && __SIOCGSTAMPNS64 */
#endif /* __USE_TIME64 */

#if !defined(FIOSETOWN) && defined(__FIOSETOWN)
#define FIOSETOWN  __FIOSETOWN  /* ... */
#endif /* !FIOSETOWN && __FIOSETOWN */
#if !defined(SIOCSPGRP) && defined(__SIOCSPGRP)
#define SIOCSPGRP  __SIOCSPGRP  /* ... */
#endif /* !SIOCSPGRP && __SIOCSPGRP */
#if !defined(FIOGETOWN) && defined(__FIOGETOWN)
#define FIOGETOWN  __FIOGETOWN  /* ... */
#endif /* !FIOGETOWN && __FIOGETOWN */
#if !defined(SIOCGPGRP) && defined(__SIOCGPGRP)
#define SIOCGPGRP  __SIOCGPGRP  /* ... */
#endif /* !SIOCGPGRP && __SIOCGPGRP */
#if !defined(SIOCATMARK) && defined(__SIOCATMARK)
#define SIOCATMARK __SIOCATMARK /* ... */
#endif /* !SIOCATMARK && __SIOCATMARK */

/* Routing table functions. */
#if !defined(SIOCADDRT) && defined(__SIOCADDRT)
#define SIOCADDRT __SIOCADDRT /* ??? */
#endif /* !SIOCADDRT && __SIOCADDRT */
#if !defined(SIOCDELRT) && defined(__SIOCDELRT)
#define SIOCDELRT __SIOCDELRT /* ??? */
#endif /* !SIOCDELRT && __SIOCDELRT */
#if !defined(SIOCRTMSG) && defined(__SIOCRTMSG)
#define SIOCRTMSG __SIOCRTMSG /* ??? */
#endif /* !SIOCRTMSG && __SIOCRTMSG */

/* Socket configuration functions. */
#if !defined(SIOCGIFNAME) && defined(__SIOCGIFNAME)
#define SIOCGIFNAME        __SIOCGIFNAME        /* ??? */
#endif /* !SIOCGIFNAME && __SIOCGIFNAME */
#if !defined(SIOCSIFLINK) && defined(__SIOCSIFLINK)
#define SIOCSIFLINK        __SIOCSIFLINK        /* ??? */
#endif /* !SIOCSIFLINK && __SIOCSIFLINK */
#if !defined(SIOCGIFCONF) && defined(__SIOCGIFCONF)
#define SIOCGIFCONF        __SIOCGIFCONF        /* ??? */
#endif /* !SIOCGIFCONF && __SIOCGIFCONF */
#if !defined(SIOCGIFFLAGS) && defined(__SIOCGIFFLAGS)
#define SIOCGIFFLAGS       __SIOCGIFFLAGS       /* ??? */
#endif /* !SIOCGIFFLAGS && __SIOCGIFFLAGS */
#if !defined(SIOCSIFFLAGS) && defined(__SIOCSIFFLAGS)
#define SIOCSIFFLAGS       __SIOCSIFFLAGS       /* ??? */
#endif /* !SIOCSIFFLAGS && __SIOCSIFFLAGS */
#if !defined(SIOCGIFADDR) && defined(__SIOCGIFADDR)
#define SIOCGIFADDR        __SIOCGIFADDR        /* ??? */
#endif /* !SIOCGIFADDR && __SIOCGIFADDR */
#if !defined(SIOCSIFADDR) && defined(__SIOCSIFADDR)
#define SIOCSIFADDR        __SIOCSIFADDR        /* ??? */
#endif /* !SIOCSIFADDR && __SIOCSIFADDR */
#if !defined(SIOCGIFDSTADDR) && defined(__SIOCGIFDSTADDR)
#define SIOCGIFDSTADDR     __SIOCGIFDSTADDR     /* ??? */
#endif /* !SIOCGIFDSTADDR && __SIOCGIFDSTADDR */
#if !defined(SIOCSIFDSTADDR) && defined(__SIOCSIFDSTADDR)
#define SIOCSIFDSTADDR     __SIOCSIFDSTADDR     /* ??? */
#endif /* !SIOCSIFDSTADDR && __SIOCSIFDSTADDR */
#if !defined(SIOCGIFBRDADDR) && defined(__SIOCGIFBRDADDR)
#define SIOCGIFBRDADDR     __SIOCGIFBRDADDR     /* ??? */
#endif /* !SIOCGIFBRDADDR && __SIOCGIFBRDADDR */
#if !defined(SIOCSIFBRDADDR) && defined(__SIOCSIFBRDADDR)
#define SIOCSIFBRDADDR     __SIOCSIFBRDADDR     /* ??? */
#endif /* !SIOCSIFBRDADDR && __SIOCSIFBRDADDR */
#if !defined(SIOCGIFNETMASK) && defined(__SIOCGIFNETMASK)
#define SIOCGIFNETMASK     __SIOCGIFNETMASK     /* ??? */
#endif /* !SIOCGIFNETMASK && __SIOCGIFNETMASK */
#if !defined(SIOCSIFNETMASK) && defined(__SIOCSIFNETMASK)
#define SIOCSIFNETMASK     __SIOCSIFNETMASK     /* ??? */
#endif /* !SIOCSIFNETMASK && __SIOCSIFNETMASK */
#if !defined(SIOCGIFMETRIC) && defined(__SIOCGIFMETRIC)
#define SIOCGIFMETRIC      __SIOCGIFMETRIC      /* ??? */
#endif /* !SIOCGIFMETRIC && __SIOCGIFMETRIC */
#if !defined(SIOCSIFMETRIC) && defined(__SIOCSIFMETRIC)
#define SIOCSIFMETRIC      __SIOCSIFMETRIC      /* ??? */
#endif /* !SIOCSIFMETRIC && __SIOCSIFMETRIC */
#if !defined(SIOCGIFMEM) && defined(__SIOCGIFMEM)
#define SIOCGIFMEM         __SIOCGIFMEM         /* ??? */
#endif /* !SIOCGIFMEM && __SIOCGIFMEM */
#if !defined(SIOCSIFMEM) && defined(__SIOCSIFMEM)
#define SIOCSIFMEM         __SIOCSIFMEM         /* ??? */
#endif /* !SIOCSIFMEM && __SIOCSIFMEM */
#if !defined(SIOCGIFMTU) && defined(__SIOCGIFMTU)
#define SIOCGIFMTU         __SIOCGIFMTU         /* ??? */
#endif /* !SIOCGIFMTU && __SIOCGIFMTU */
#if !defined(SIOCSIFMTU) && defined(__SIOCSIFMTU)
#define SIOCSIFMTU         __SIOCSIFMTU         /* ??? */
#endif /* !SIOCSIFMTU && __SIOCSIFMTU */
#if !defined(SIOCSIFNAME) && defined(__SIOCSIFNAME)
#define SIOCSIFNAME        __SIOCSIFNAME        /* ??? */
#endif /* !SIOCSIFNAME && __SIOCSIFNAME */
#if !defined(SIOCSIFHWADDR) && defined(__SIOCSIFHWADDR)
#define SIOCSIFHWADDR      __SIOCSIFHWADDR      /* ??? */
#endif /* !SIOCSIFHWADDR && __SIOCSIFHWADDR */
#if !defined(SIOCGIFENCAP) && defined(__SIOCGIFENCAP)
#define SIOCGIFENCAP       __SIOCGIFENCAP       /* ??? */
#endif /* !SIOCGIFENCAP && __SIOCGIFENCAP */
#if !defined(SIOCSIFENCAP) && defined(__SIOCSIFENCAP)
#define SIOCSIFENCAP       __SIOCSIFENCAP       /* ??? */
#endif /* !SIOCSIFENCAP && __SIOCSIFENCAP */
#if !defined(SIOCGIFHWADDR) && defined(__SIOCGIFHWADDR)
#define SIOCGIFHWADDR      __SIOCGIFHWADDR      /* ??? */
#endif /* !SIOCGIFHWADDR && __SIOCGIFHWADDR */
#if !defined(SIOCGIFSLAVE) && defined(__SIOCGIFSLAVE)
#define SIOCGIFSLAVE       __SIOCGIFSLAVE       /* ??? */
#endif /* !SIOCGIFSLAVE && __SIOCGIFSLAVE */
#if !defined(SIOCSIFSLAVE) && defined(__SIOCSIFSLAVE)
#define SIOCSIFSLAVE       __SIOCSIFSLAVE       /* ??? */
#endif /* !SIOCSIFSLAVE && __SIOCSIFSLAVE */
#if !defined(SIOCADDMULTI) && defined(__SIOCADDMULTI)
#define SIOCADDMULTI       __SIOCADDMULTI       /* ??? */
#endif /* !SIOCADDMULTI && __SIOCADDMULTI */
#if !defined(SIOCDELMULTI) && defined(__SIOCDELMULTI)
#define SIOCDELMULTI       __SIOCDELMULTI       /* ??? */
#endif /* !SIOCDELMULTI && __SIOCDELMULTI */
#if !defined(SIOCGIFINDEX) && defined(__SIOCGIFINDEX)
#define SIOCGIFINDEX       __SIOCGIFINDEX       /* ??? */
#endif /* !SIOCGIFINDEX && __SIOCGIFINDEX */
#if !defined(SIOGIFINDEX) && defined(__SIOCGIFINDEX)
#define SIOGIFINDEX        __SIOCGIFINDEX       /* Alias */
#endif /* !SIOGIFINDEX && __SIOCGIFINDEX */
#if !defined(SIOCSIFPFLAGS) && defined(__SIOCSIFPFLAGS)
#define SIOCSIFPFLAGS      __SIOCSIFPFLAGS      /* ??? */
#endif /* !SIOCSIFPFLAGS && __SIOCSIFPFLAGS */
#if !defined(SIOCGIFPFLAGS) && defined(__SIOCGIFPFLAGS)
#define SIOCGIFPFLAGS      __SIOCGIFPFLAGS      /* ??? */
#endif /* !SIOCGIFPFLAGS && __SIOCGIFPFLAGS */
#if !defined(SIOCDIFADDR) && defined(__SIOCDIFADDR)
#define SIOCDIFADDR        __SIOCDIFADDR        /* ??? */
#endif /* !SIOCDIFADDR && __SIOCDIFADDR */
#if !defined(SIOCSIFHWBROADCAST) && defined(__SIOCSIFHWBROADCAST)
#define SIOCSIFHWBROADCAST __SIOCSIFHWBROADCAST /* ??? */
#endif /* !SIOCSIFHWBROADCAST && __SIOCSIFHWBROADCAST */
#if !defined(SIOCGIFCOUNT) && defined(__SIOCGIFCOUNT)
#define SIOCGIFCOUNT       __SIOCGIFCOUNT       /* ??? */
#endif /* !SIOCGIFCOUNT && __SIOCGIFCOUNT */

#if !defined(SIOCGIFBR) && defined(__SIOCGIFBR)
#define SIOCGIFBR __SIOCGIFBR /* ??? */
#endif /* !SIOCGIFBR && __SIOCGIFBR */
#if !defined(SIOCSIFBR) && defined(__SIOCSIFBR)
#define SIOCSIFBR __SIOCSIFBR /* ??? */
#endif /* !SIOCSIFBR && __SIOCSIFBR */

#if !defined(SIOCGIFTXQLEN) && defined(__SIOCGIFTXQLEN)
#define SIOCGIFTXQLEN __SIOCGIFTXQLEN /* ??? */
#endif /* !SIOCGIFTXQLEN && __SIOCGIFTXQLEN */
#if !defined(SIOCSIFTXQLEN) && defined(__SIOCSIFTXQLEN)
#define SIOCSIFTXQLEN __SIOCSIFTXQLEN /* ??? */
#endif /* !SIOCSIFTXQLEN && __SIOCSIFTXQLEN */

#if !defined(SIOCETHTOOL) && defined(__SIOCETHTOOL)
#define SIOCETHTOOL __SIOCETHTOOL /* ??? */
#endif /* !SIOCETHTOOL && __SIOCETHTOOL */
#if !defined(SIOCGMIIPHY) && defined(__SIOCGMIIPHY)
#define SIOCGMIIPHY __SIOCGMIIPHY /* ??? */
#endif /* !SIOCGMIIPHY && __SIOCGMIIPHY */
#if !defined(SIOCGMIIREG) && defined(__SIOCGMIIREG)
#define SIOCGMIIREG __SIOCGMIIREG /* ??? */
#endif /* !SIOCGMIIREG && __SIOCGMIIREG */
#if !defined(SIOCSMIIREG) && defined(__SIOCSMIIREG)
#define SIOCSMIIREG __SIOCSMIIREG /* ??? */
#endif /* !SIOCSMIIREG && __SIOCSMIIREG */
#if !defined(SIOCWANDEV) && defined(__SIOCWANDEV)
#define SIOCWANDEV  __SIOCWANDEV  /* ??? */
#endif /* !SIOCWANDEV && __SIOCWANDEV */
#if !defined(SIOCOUTQNSD) && defined(__SIOCOUTQNSD)
#define SIOCOUTQNSD __SIOCOUTQNSD /* ??? */
#endif /* !SIOCOUTQNSD && __SIOCOUTQNSD */

/* ARP cache control calls. */
#if !defined(SIOCDARP) && defined(__SIOCDARP)
#define SIOCDARP __SIOCDARP /* ??? */
#endif /* !SIOCDARP && __SIOCDARP */
#if !defined(SIOCGARP) && defined(__SIOCGARP)
#define SIOCGARP __SIOCGARP /* ??? */
#endif /* !SIOCGARP && __SIOCGARP */
#if !defined(SIOCSARP) && defined(__SIOCSARP)
#define SIOCSARP __SIOCSARP /* ??? */
#endif /* !SIOCSARP && __SIOCSARP */
/* RARP cache control calls. */
#if !defined(SIOCDRARP) && defined(__SIOCDRARP)
#define SIOCDRARP __SIOCDRARP /* ??? */
#endif /* !SIOCDRARP && __SIOCDRARP */
#if !defined(SIOCGRARP) && defined(__SIOCGRARP)
#define SIOCGRARP __SIOCGRARP /* ??? */
#endif /* !SIOCGRARP && __SIOCGRARP */
#if !defined(SIOCSRARP) && defined(__SIOCSRARP)
#define SIOCSRARP __SIOCSRARP /* ??? */
#endif /* !SIOCSRARP && __SIOCSRARP */
/* Driver configuration calls */
#if !defined(SIOCGIFMAP) && defined(__SIOCGIFMAP)
#define SIOCGIFMAP __SIOCGIFMAP /* ??? */
#endif /* !SIOCGIFMAP && __SIOCGIFMAP */
#if !defined(SIOCSIFMAP) && defined(__SIOCSIFMAP)
#define SIOCSIFMAP __SIOCSIFMAP /* ??? */
#endif /* !SIOCSIFMAP && __SIOCSIFMAP */
/* DLCI configuration calls */
#if !defined(SIOCADDDLCI) && defined(__SIOCADDDLCI)
#define SIOCADDDLCI __SIOCADDDLCI /* ??? */
#endif /* !SIOCADDDLCI && __SIOCADDDLCI */
#if !defined(SIOCDELDLCI) && defined(__SIOCDELDLCI)
#define SIOCDELDLCI __SIOCDELDLCI /* ??? */
#endif /* !SIOCDELDLCI && __SIOCDELDLCI */
#if !defined(SIOCGIFVLAN) && defined(__SIOCGIFVLAN)
#define SIOCGIFVLAN __SIOCGIFVLAN /* ??? */
#endif /* !SIOCGIFVLAN && __SIOCGIFVLAN */
#if !defined(SIOCSIFVLAN) && defined(__SIOCSIFVLAN)
#define SIOCSIFVLAN __SIOCSIFVLAN /* ??? */
#endif /* !SIOCSIFVLAN && __SIOCSIFVLAN */
/* bonding calls */
#if !defined(SIOCBONDENSLAVE) && defined(__SIOCBONDENSLAVE)
#define SIOCBONDENSLAVE        __SIOCBONDENSLAVE        /* ??? */
#endif /* !SIOCBONDENSLAVE && __SIOCBONDENSLAVE */
#if !defined(SIOCBONDRELEASE) && defined(__SIOCBONDRELEASE)
#define SIOCBONDRELEASE        __SIOCBONDRELEASE        /* ??? */
#endif /* !SIOCBONDRELEASE && __SIOCBONDRELEASE */
#if !defined(SIOCBONDSETHWADDR) && defined(__SIOCBONDSETHWADDR)
#define SIOCBONDSETHWADDR      __SIOCBONDSETHWADDR      /* ??? */
#endif /* !SIOCBONDSETHWADDR && __SIOCBONDSETHWADDR */
#if !defined(SIOCBONDSLAVEINFOQUERY) && defined(__SIOCBONDSLAVEINFOQUERY)
#define SIOCBONDSLAVEINFOQUERY __SIOCBONDSLAVEINFOQUERY /* ??? */
#endif /* !SIOCBONDSLAVEINFOQUERY && __SIOCBONDSLAVEINFOQUERY */
#if !defined(SIOCBONDINFOQUERY) && defined(__SIOCBONDINFOQUERY)
#define SIOCBONDINFOQUERY      __SIOCBONDINFOQUERY      /* ??? */
#endif /* !SIOCBONDINFOQUERY && __SIOCBONDINFOQUERY */
#if !defined(SIOCBONDCHANGEACTIVE) && defined(__SIOCBONDCHANGEACTIVE)
#define SIOCBONDCHANGEACTIVE   __SIOCBONDCHANGEACTIVE   /* ??? */
#endif /* !SIOCBONDCHANGEACTIVE && __SIOCBONDCHANGEACTIVE */
/* bridge calls */
#if !defined(SIOCBRADDBR) && defined(__SIOCBRADDBR)
#define SIOCBRADDBR __SIOCBRADDBR /* ??? */
#endif /* !SIOCBRADDBR && __SIOCBRADDBR */
#if !defined(SIOCBRDELBR) && defined(__SIOCBRDELBR)
#define SIOCBRDELBR __SIOCBRDELBR /* ??? */
#endif /* !SIOCBRDELBR && __SIOCBRDELBR */
#if !defined(SIOCBRADDIF) && defined(__SIOCBRADDIF)
#define SIOCBRADDIF __SIOCBRADDIF /* ??? */
#endif /* !SIOCBRADDIF && __SIOCBRADDIF */
#if !defined(SIOCBRDELIF) && defined(__SIOCBRDELIF)
#define SIOCBRDELIF __SIOCBRDELIF /* ??? */
#endif /* !SIOCBRDELIF && __SIOCBRDELIF */
/* hardware time stamping */
#if !defined(SIOCSHWTSTAMP) && defined(__SIOCSHWTSTAMP)
#define SIOCSHWTSTAMP __SIOCSHWTSTAMP /* ???*/
#endif /* !SIOCSHWTSTAMP && __SIOCSHWTSTAMP */
#if !defined(SIOCGHWTSTAMP) && defined(__SIOCGHWTSTAMP)
#define SIOCGHWTSTAMP __SIOCGHWTSTAMP /* ??? */
#endif /* !SIOCGHWTSTAMP && __SIOCGHWTSTAMP */

#if !defined(SIOCDEVPRIVATE) && defined(__SIOCDEVPRIVATE)
#define SIOCDEVPRIVATE   __SIOCDEVPRIVATE   /* Device-private ioctls. */
#endif /* !SIOCDEVPRIVATE && __SIOCDEVPRIVATE */
#if !defined(SIOCPROTOPRIVATE) && defined(__SIOCPROTOPRIVATE)
#define SIOCPROTOPRIVATE __SIOCPROTOPRIVATE /* Protocol-private ioctls. */
#endif /* !SIOCPROTOPRIVATE && __SIOCPROTOPRIVATE */



#ifdef __CC__
__SYSDECL_BEGIN

}

@@>> ioctl(2)
@@Perform the  I/O control  operation specified  by `request'  on  `fd'.
@@Many I/O  control operations  except  an additional  argument,  though
@@this argument's type and meaning  depends on `REQUEST'. If used,  it's
@@usually either a pointer to a larger argument structure, or an integer
@@that fits into a single register.
@@@return: * : The return value depends on the given `request'.
@@@return: 0 : A zero return-value usually indicates success.
@@@return: -1: All ioctl operations use this to indicate error (s.a. `errno')
[[cp, guard, vartypes(void *), decl_include("<features.h>", "<bits/types.h>")]]
[[export_alias("__ioctl", "__libc_ioctl")]]
__STDC_INT_AS_SSIZE_T ioctl([[fdarg]] $fd_t fd, $ioctl_t request, ...);

%{

__SYSDECL_END
#endif /* __CC__ */

}
