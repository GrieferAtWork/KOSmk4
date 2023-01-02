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
/* (#) Portability: DragonFly BSD (/sys/sys/ttycom.h) */
/* (#) Portability: FreeBSD       (/sys/sys/ttycom.h) */
/* (#) Portability: NetBSD        (/sys/sys/ttycom.h) */
/* (#) Portability: OpenBSD       (/sys/sys/ttycom.h) */
/* (#) Portability: OpenSolaris   (/usr/src/lib/libbc/inc/include/sys/ttycom.h) */
#ifndef _SYS_TTYCOM_H
#define _SYS_TTYCOM_H 1

#include <__stdinc.h>
#include <features.h>

#include <asm/os/termios.h>
#include <asm/os/tty.h>
#include <bits/os/termio.h> /* struct winsize */
#include <sys/ioccom.h>
#include <sys/syslimits.h>

#ifndef _PATH_PTMDEV
#define _PATH_PTMDEV "/dev/ptm"
#endif /* !_PATH_PTMDEV */

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
#if !defined(TIOCM_DCD) && defined(__TIOCM_CAR)
#define TIOCM_DCD __TIOCM_CAR /* Alias */
#endif /* !TIOCM_DCD && __TIOCM_CAR */
#if !defined(TIOCM_RI) && defined(__TIOCM_RNG)
#define TIOCM_RI  __TIOCM_RNG /* Alias */
#endif /* !TIOCM_RI && __TIOCM_RNG */


#if !defined(TIOCEXCL) && defined(__TIOCEXCL)
#define TIOCEXCL  __TIOCEXCL    /* ... */
#endif /* !TIOCEXCL && __TIOCEXCL */
#if !defined(TIOCNXCL) && defined(__TIOCNXCL)
#define TIOCNXCL  __TIOCNXCL    /* ... */
#endif /* !TIOCNXCL && __TIOCNXCL */
#if !defined(TIOCGPTN) && defined(__TIOCGPTN)
#define TIOCGPTN  __TIOCGPTN    /* ... */
#endif /* !TIOCGPTN && __TIOCGPTN */
#if !defined(TIOCFLUSH) && defined(__TIOCFLUSH)
#define TIOCFLUSH  __TIOCFLUSH    /* ... */
#endif /* !TIOCFLUSH && __TIOCFLUSH */
#if !defined(TIOCGETA) && defined(__TCGETA)
#define TIOCGETA  __TCGETA  /* [struct termios *arg] Get terminal attributes */
#endif /* !TIOCGETA && __TCGETA */
#if !defined(TIOCSETA) && defined(__TCSETA)
#define TIOCSETA  __TCSETA  /* [struct termios const *arg] Set terminal attributes */
#endif /* !TIOCSETA && __TCSETA */
#if !defined(TIOCSETAW) && defined(__TCSETAW)
#define TIOCSETAW __TCSETAW /* [struct termios const *arg] Wait for all unwritten data to be transmitted, discard all unread data, then set terminal attributes */
#endif /* !TIOCSETAW && __TCSETAW */
#if !defined(TIOCSETAF) && defined(__TCSETAF)
#define TIOCSETAF __TCSETAF /* [struct termios const *arg] Wait for all unwritten data to be transmitted, then set terminal attributes */
#endif /* !TIOCSETAF && __TCSETAF */
#if !defined(TIOCGETD) && defined(__TIOCGETD)
#define TIOCGETD    __TIOCGETD      /* [int *result] Store the terminal's line discipline in *result */
#endif /* !TIOCGETD && __TIOCGETD */
#if !defined(TIOCSETD) && defined(__TIOCSETD)
#define TIOCSETD    __TIOCSETD      /* [int const *ld] Set the terminal's line discipline to *ld */
#endif /* !TIOCSETD && __TIOCSETD */
#if !defined(TIOCPTMASTER) && defined(__TIOCPTMASTER)
#define TIOCPTMASTER __TIOCPTMASTER /* ... */
#endif /* !TIOCPTMASTER && __TIOCPTMASTER */


#ifndef __linedn_t_defined
#define __linedn_t_defined
#if defined(__TIOCGLINED) || defined(__TIOCSLINED)
#ifndef TTLINEDNAMELEN
#define TTLINEDNAMELEN 32
#endif /* !TTLINEDNAMELEN */
#ifdef __CC__
__DECL_BEGIN
typedef char linedn_t[TTLINEDNAMELEN];
__DECL_END
#endif /* __CC__ */
#endif /* __TIOCGLINED || __TIOCSLINED */
#endif /* !__linedn_t_defined */

#if !defined(TIOCGLINED) && defined(__TIOCGLINED)
#define TIOCGLINED    __TIOCGLINED /* [linedn_t arg] Get line discipline */
#endif /* !TIOCGLINED && __TIOCGLINED */
#if !defined(TIOCSLINED) && defined(__TIOCSLINED)
#define TIOCSLINED    __TIOCSLINED /* [linedn_t arg] Set line discipline */
#endif /* !TIOCSLINED && __TIOCSLINED */
#if !defined(TIOCSBRK) && defined(__TIOCSBRK)
#define TIOCSBRK    __TIOCSBRK      /* BSD compatibility */
#endif /* !TIOCSBRK && __TIOCSBRK */
#if !defined(TIOCCBRK) && defined(__TIOCCBRK)
#define TIOCCBRK    __TIOCCBRK      /* BSD compatibility */
#endif /* !TIOCCBRK && __TIOCCBRK */
#if !defined(TIOCSDTR) && defined(__TIOCSDTR)
#define TIOCSDTR    __TIOCSDTR      /* ... */
#endif /* !TIOCSDTR && __TIOCSDTR */
#if !defined(TIOCCDTR) && defined(__TIOCCDTR)
#define TIOCCDTR    __TIOCCDTR      /* ... */
#endif /* !TIOCCDTR && __TIOCCDTR */
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
#if !defined(TIOCNOTTY) && defined(__TIOCNOTTY)
#define TIOCNOTTY    __TIOCNOTTY    /* Given up control over this CTTY */
#endif /* !TIOCNOTTY && __TIOCNOTTY */

#if !defined(TIOCPKT) && defined(__TIOCPKT)
#define TIOCPKT      __TIOCPKT      /* ... */
#endif /* !TIOCPKT && __TIOCPKT */
#if !defined(TIOCSTOP) && defined(__TIOCSTOP)
#define TIOCSTOP     __TIOCSTOP     /* Emulate ^S */
#endif /* !TIOCSTOP && __TIOCSTOP */
#if !defined(TIOCSTART) && defined(__TIOCSTART)
#define TIOCSTART    __TIOCSTART    /* Emulate ^Q */
#endif /* !TIOCSTART && __TIOCSTART */
#if !defined(TIOCMSET) && defined(__TIOCMSET)
#define TIOCMSET   __TIOCMSET   /* [unsigned int *argp] Set modem bits (bits = *argp) (set of `TIOCM_*') */
#endif /* !TIOCMSET && __TIOCMSET */
#if !defined(TIOCMBIS) && defined(__TIOCMBIS)
#define TIOCMBIS   __TIOCMBIS   /* [unsigned int *argp] Enable modem bits (bits |= *argp) (set of `TIOCM_*') */
#endif /* !TIOCMBIS && __TIOCMBIS */
#if !defined(TIOCMBIC) && defined(__TIOCMBIC)
#define TIOCMBIC   __TIOCMBIC   /* [unsigned int *argp] Clear modem bits (bits &= ~*argp) (set of `TIOCM_*') */
#endif /* !TIOCMBIC && __TIOCMBIC */
#if !defined(TIOCMGET) && defined(__TIOCMGET)
#define TIOCMGET   __TIOCMGET   /* [unsigned int *argp] Get status of modem bits (set of `TIOCM_*') */
#endif /* !TIOCMGET && __TIOCMGET */
#if !defined(TIOCREMOTE) && defined(__TIOCREMOTE)
#define TIOCREMOTE __TIOCREMOTE      /* ... */
#endif /* !TIOCREMOTE && __TIOCREMOTE */
#if !defined(TIOCGWINSZ) && defined(__TIOCGWINSZ)
#define TIOCGWINSZ __TIOCGWINSZ /* [struct winsize *arg] Get the window size */
#endif /* !TIOCGWINSZ && __TIOCGWINSZ */
#if !defined(TIOCSWINSZ) && defined(__TIOCSWINSZ)
#define TIOCSWINSZ __TIOCSWINSZ /* [struct winsize const *arg] Set the window size */
#endif /* !TIOCSWINSZ && __TIOCSWINSZ */
#if !defined(TIOCUCNTL) && defined(__TIOCUCNTL)
#define TIOCUCNTL  __TIOCUCNTL /* ... */
#endif /* !TIOCUCNTL && __TIOCUCNTL */
#if !defined(TIOCSTAT) && defined(__TIOCSTAT)
#define TIOCSTAT   __TIOCSTAT /* ... */
#endif /* !TIOCSTAT && __TIOCSTAT */
#if !defined(UIOCCMD) && defined(__UIOCCMD)
#define UIOCCMD    __UIOCCMD /* ... */
#endif /* !UIOCCMD && __UIOCCMD */
#if !defined(TIOCGSID) && defined(__TIOCGSID)
#define TIOCGSID    __TIOCGSID /* [pid_t *arg] Return the session ID of a tty */
#endif /* !TIOCGSID && __TIOCGSID */
#if !defined(TIOCCONS) && defined(__TIOCCONS)
#define TIOCCONS     __TIOCCONS     /* ... */
#endif /* !TIOCCONS && __TIOCCONS */
#if !defined(TIOCSCTTY) && defined(__TIOCSCTTY)
#define TIOCSCTTY __TIOCSCTTY /* [int steal_if_necessary] Make this terminal the controlling terminal of the calling process */
#endif /* !TIOCSCTTY && __TIOCSCTTY */
#if !defined(TIOCEXT) && defined(__TIOCEXT)
#define TIOCEXT     __TIOCEXT /* ... */
#endif /* !TIOCEXT && __TIOCEXT */
#if !defined(TIOCSIG) && defined(__TIOCSIG)
#define TIOCSIG     __TIOCSIG /* pty: generate signal */
#endif /* !TIOCSIG && __TIOCSIG */
#if !defined(TIOCGDRAINWAIT) && defined(__TIOCGDRAINWAIT)
#define TIOCGDRAINWAIT __TIOCGDRAINWAIT /* [int *arg] ... */
#endif /* !TIOCGDRAINWAIT && __TIOCGDRAINWAIT */
#if !defined(TIOCSDRAINWAIT) && defined(__TIOCSDRAINWAIT)
#define TIOCSDRAINWAIT __TIOCSDRAINWAIT /* [int *arg] ... */
#endif /* !TIOCSDRAINWAIT && __TIOCSDRAINWAIT */
#if !defined(TIOCTIMESTAMP) && defined(__TIOCTIMESTAMP)
#define TIOCTIMESTAMP  __TIOCTIMESTAMP  /* [struct timeval *arg] ... */
#endif /* !TIOCTIMESTAMP && __TIOCTIMESTAMP */
#if !defined(TIOCMGDTRWAIT) && defined(__TIOCMGDTRWAIT)
#define TIOCMGDTRWAIT  __TIOCMGDTRWAIT  /* [int *arg] ... */
#endif /* !TIOCMGDTRWAIT && __TIOCMGDTRWAIT */
#if !defined(TIOCMSDTRWAIT) && defined(__TIOCMSDTRWAIT)
#define TIOCMSDTRWAIT  __TIOCMSDTRWAIT  /* [int *arg] ... */
#endif /* !TIOCMSDTRWAIT && __TIOCMSDTRWAIT */
#if !defined(TIOCDRAIN) && defined(__TIOCDRAIN)
#define TIOCDRAIN   __TIOCDRAIN /* ... */
#endif /* !TIOCDRAIN && __TIOCDRAIN */
#if !defined(TIOCGFLAGS) && defined(__TIOCGFLAGS)
#define TIOCGFLAGS  __TIOCGFLAGS /* ... */
#endif /* !TIOCGFLAGS && __TIOCGFLAGS */
#if !defined(TIOCSFLAGS) && defined(__TIOCSFLAGS)
#define TIOCSFLAGS  __TIOCSFLAGS /* ... */
#endif /* !TIOCSFLAGS && __TIOCSFLAGS */
#if !defined(TIOCFLAG_SOFTCAR) && defined(__TIOCFLAG_SOFTCAR)
#define TIOCFLAG_SOFTCAR __TIOCFLAG_SOFTCAR /* ... */
#endif /* !TIOCFLAG_SOFTCAR && __TIOCFLAG_SOFTCAR */
#if !defined(TIOCFLAG_CLOCAL) && defined(__TIOCFLAG_CLOCAL)
#define TIOCFLAG_CLOCAL  __TIOCFLAG_CLOCAL  /* ... */
#endif /* !TIOCFLAG_CLOCAL && __TIOCFLAG_CLOCAL */
#if !defined(TIOCFLAG_CRTSCTS) && defined(__TIOCFLAG_CRTSCTS)
#define TIOCFLAG_CRTSCTS __TIOCFLAG_CRTSCTS /* ... */
#endif /* !TIOCFLAG_CRTSCTS && __TIOCFLAG_CRTSCTS */
#if !defined(TIOCFLAG_MDMBUF) && defined(__TIOCFLAG_MDMBUF)
#define TIOCFLAG_MDMBUF  __TIOCFLAG_MDMBUF  /* ... */
#endif /* !TIOCFLAG_MDMBUF && __TIOCFLAG_MDMBUF */
#if !defined(TIOCFLAG_CDTRCTS) && defined(__TIOCFLAG_CDTRCTS)
#define TIOCFLAG_CDTRCTS __TIOCFLAG_CDTRCTS /* ... */
#endif /* !TIOCFLAG_CDTRCTS && __TIOCFLAG_CDTRCTS */
#if !defined(TIOCDCDTIMESTAMP) && defined(__TIOCDCDTIMESTAMP)
#define TIOCDCDTIMESTAMP __TIOCDCDTIMESTAMP /* ... */
#endif /* !TIOCDCDTIMESTAMP && __TIOCDCDTIMESTAMP */
#if !defined(TIOCRCVFRAME) && defined(__TIOCRCVFRAME)
#define TIOCRCVFRAME __TIOCRCVFRAME /* ... */
#endif /* !TIOCRCVFRAME && __TIOCRCVFRAME */
#if !defined(TIOCXMTFRAME) && defined(__TIOCXMTFRAME)
#define TIOCXMTFRAME __TIOCXMTFRAME /* ... */
#endif /* !TIOCXMTFRAME && __TIOCXMTFRAME */
#if !defined(TIOCPTMGET) && defined(__TIOCPTMGET)
#define TIOCPTMGET  __TIOCPTMGET /* ... */
#endif /* !TIOCPTMGET && __TIOCPTMGET */
#if !defined(TIOCGRANTPT) && defined(__TIOCGRANTPT)
#define TIOCGRANTPT __TIOCGRANTPT /* ... */
#endif /* !TIOCGRANTPT && __TIOCGRANTPT */
#if !defined(TIOCPTSNAME) && defined(__TIOCPTSNAME)
#define TIOCPTSNAME __TIOCPTSNAME /* ... */
#endif /* !TIOCPTSNAME && __TIOCPTSNAME */
#if !defined(TIOCSQSIZE) && defined(__TIOCSQSIZE)
#define TIOCSQSIZE  __TIOCSQSIZE /* ... */
#endif /* !TIOCSQSIZE && __TIOCSQSIZE */
#if !defined(TIOCGQSIZE) && defined(__TIOCGQSIZE)
#define TIOCGQSIZE  __TIOCGQSIZE /* ... */
#endif /* !TIOCGQSIZE && __TIOCGQSIZE */

#if !defined(TTYDISC) && defined(__TTYDISC)
#define TTYDISC   __TTYDISC   /* ... */
#endif /* !TTYDISC && __TTYDISC */
#if !defined(TABLDISC) && defined(__TABLDISC)
#define TABLDISC  __TABLDISC  /* ... */
#endif /* !TABLDISC && __TABLDISC */
#if !defined(SLIPDISC) && defined(__SLIPDISC)
#define SLIPDISC  __SLIPDISC  /* ... */
#endif /* !SLIPDISC && __SLIPDISC */
#if !defined(PPPDISC) && defined(__PPPDISC)
#define PPPDISC   __PPPDISC   /* ... */
#endif /* !PPPDISC && __PPPDISC */
#if !defined(STRIPDISC) && defined(__STRIPDISC)
#define STRIPDISC __STRIPDISC /* ... */
#endif /* !STRIPDISC && __STRIPDISC */
#if !defined(HDLCDISC) && defined(__HDLCDISC)
#define HDLCDISC  __HDLCDISC  /* ... */
#endif /* !HDLCDISC && __HDLCDISC */
#if !defined(NETGRAPHDISC) && defined(__NETGRAPHDISC)
#define NETGRAPHDISC __NETGRAPHDISC /* ... */
#endif /* !NETGRAPHDISC && __NETGRAPHDISC */
#if !defined(H4DISC) && defined(__H4DISC)
#define H4DISC    __H4DISC /* ... */
#endif /* !H4DISC && __H4DISC */


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

#endif /* !_SYS_TTYCOM_H */
