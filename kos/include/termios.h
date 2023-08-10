/* HASH CRC-32:0x6a73a232 */
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
/* (>) Standard: POSIX.1c (Issue 3, IEEE Std 1003.1c-1995) */
/* (#) Portability: Cygwin        (/newlib/libc/include/termios.h) */
/* (#) Portability: DJGPP         (/include/termios.h) */
/* (#) Portability: DragonFly BSD (/include/termios.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/termios.h) */
/* (#) Portability: FreeBSD       (/include/termios.h) */
/* (#) Portability: GNU C Library (/termios/termios.h) */
/* (#) Portability: GNU Hurd      (/usr/include/termios.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/termios.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/termios.h) */
/* (#) Portability: diet libc     (/include/termios.h) */
/* (#) Portability: libc4/5       (/include/termios.h) */
/* (#) Portability: libc6         (/include/termios.h) */
/* (#) Portability: mintlib       (/include/termios.h) */
/* (#) Portability: musl libc     (/include/termios.h) */
/* (#) Portability: uClibc        (/include/termios.h) */
#ifndef _TERMIOS_H
#define _TERMIOS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/termios.h>
#include <bits/os/termio.h>
#include <bits/os/termios.h>

#ifdef __USE_GLIBC_BLOAT
#include <sys/ioctl.h>
#endif /* __USE_GLIBC_BLOAT */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#include <bits/types.h>
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#if defined(__USE_MISC) || defined(__USE_KOS) || defined(__USE_BSD)
#include <sys/ttydefaults.h>
#endif /* __USE_MISC || __USE_KOS || __USE_BSD */


/* Sources for comments:
 *   - http://man7.org/linux/man-pages/man3/tcflow.3.html
 *   - https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_node/libc_355.html
 *   - Came up with them myself, or altered them significantly. */

#ifndef __VDISABLE
#define __VDISABLE '\0' /* `c_cc' member of `struct termios' structure can be disabled by using the value `__VDISABLE'. */
#endif /* !__VDISABLE */

#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE __VDISABLE /* `c_cc' member of `struct termios' structure can be disabled by using the value `_POSIX_VDISABLE'. */
#endif /* !_POSIX_VDISABLE */

/* c_cc characters */
#if !defined(VINTR) && defined(__VINTR)
#define VINTR    __VINTR    /* ^C: Send SIGINT to the foreground process (requires `ISIG') */
#endif /* !VINTR && __VINTR */
#if !defined(VQUIT) && defined(__VQUIT)
#define VQUIT    __VQUIT    /* ^\: Send SIGQUIT to the foreground process (requires `ISIG') */
#endif /* !VQUIT && __VQUIT */
#if !defined(VERASE) && defined(__VERASE)
#define VERASE   __VERASE   /* ^H (aka. \b): Erase the last character from the input canon (requires `ECHOE') */
#endif /* !VERASE && __VERASE */
#if !defined(VKILL) && defined(__VKILL)
#define VKILL    __VKILL    /* ^U: Clear the entire input canon (requires `ECHOK') */
#endif /* !VKILL && __VKILL */
#if !defined(VEOF) && defined(__VEOF)
#define VEOF     __VEOF     /* ^D: Cause read(2) from the TTY to return 0 once (thus indicating input EOF) */
#endif /* !VEOF && __VEOF */
#if !defined(VTIME) && defined(__VTIME)
#define VTIME    __VTIME    /* ... */
#endif /* !VTIME && __VTIME */
#if !defined(VMIN) && defined(__VMIN)
#define VMIN     __VMIN     /* Minimum number of input bytes to-be returned by read(2) from the TTY */
#endif /* !VMIN && __VMIN */
#if !defined(VSWTCH) && defined(__VSWTCH)
#define VSWTCH   __VSWTCH   /* ... */
#endif /* !VSWTCH && __VSWTCH */
#if !defined(VSTART) && defined(__VSTART)
#define VSTART   __VSTART   /* ^Q: Restart stopped output (After VSTOP; causes pending TTY output to be flushed) */
#endif /* !VSTART && __VSTART */
#if !defined(VSTOP) && defined(__VSTOP)
#define VSTOP    __VSTOP    /* ^S: Suspend TTY display output until `VSTART' */
#endif /* !VSTOP && __VSTOP */
#if !defined(VSUSP) && defined(__VSUSP)
#define VSUSP    __VSUSP    /* ^Z: Send SIGTSTP to the foreground process (requires `ISIG') */
#endif /* !VSUSP && __VSUSP */
#if !defined(VEOL) && defined(__VEOL)
#define VEOL     __VEOL     /* \0: An additional end-of-line character used to flush the canon (by default, only \n is recognized) */
#endif /* !VEOL && __VEOL */
#if !defined(VREPRINT) && defined(__VREPRINT)
#define VREPRINT __VREPRINT /* ^R: Re-echo the current contents of the input canon (requires `IEXTEN') */
#endif /* !VREPRINT && __VREPRINT */
#if !defined(VDISCARD) && defined(__VDISCARD)
#define VDISCARD __VDISCARD /* <UNSUPPORTED> */
#endif /* !VDISCARD && __VDISCARD */
#if !defined(VWERASE) && defined(__VWERASE)
#define VWERASE  __VWERASE  /* ^W: Erase the last-written word (while (isspace(last)) erase(); while (!isspace(last)) erase()) (Requires `ECHOE' and `IEXTEN') */
#endif /* !VWERASE && __VWERASE */
#if !defined(VLNEXT) && defined(__VLNEXT)
#define VLNEXT   __VLNEXT   /* ^V: The next input character is escaped, in that any special meaning it would normally have is dismissed */
#endif /* !VLNEXT && __VLNEXT */
#if !defined(VEOL2) && defined(__VEOL2)
#define VEOL2    __VEOL2    /* \0: An additional end-of-line character used to flush the canon (by default, only \n is recognized) */
#endif /* !VEOL2 && __VEOL2 */
#ifdef __USE_BSD
#if !defined(VERASE2) && defined(__VERASE2)
#define VERASE2  __VERASE2 /* ... */
#endif /* !VERASE2 && __VERASE2 */
#if !defined(VDSUSP) && defined(__VDSUSP)
#define VDSUSP  __VDSUSP
#endif /* !VDSUSP && __VDSUSP */
#if !defined(VSTATUS) && defined(__VSTATUS)
#define VSTATUS __VSTATUS
#endif /* !VSTATUS && __VSTATUS */
#endif /* __USE_BSD */


/* c_iflag bits */
#if !defined(IGNBRK) && defined(__IGNBRK)
#define IGNBRK  __IGNBRK  /* break? */
#endif /* !IGNBRK && __IGNBRK */
#if !defined(BRKINT) && defined(__BRKINT)
#define BRKINT  __BRKINT  /* break? */
#endif /* !BRKINT && __BRKINT */
#if !defined(IGNPAR) && defined(__IGNPAR)
#define IGNPAR  __IGNPAR  /* Ignore framing errors and parity errors. */
#endif /* !IGNPAR && __IGNPAR */
#if !defined(PARMRK) && defined(__PARMRK)
#define PARMRK  __PARMRK  /* Encode faulty bytes as `\377\0\...' - `\377' is encoded as `\377\377' */
#endif /* !PARMRK && __PARMRK */
#if !defined(INPCK) && defined(__INPCK)
#define INPCK   __INPCK   /* Enable input parity checking. */
#endif /* !INPCK && __INPCK */
#if !defined(ISTRIP) && defined(__ISTRIP)
#define ISTRIP  __ISTRIP  /* Clear the eighth bit. */
#endif /* !ISTRIP && __ISTRIP */
#if !defined(INLCR) && defined(__INLCR)
#define INLCR   __INLCR   /* Translate NL to CR on input. */
#endif /* !INLCR && __INLCR */
#if !defined(IGNCR) && defined(__IGNCR)
#define IGNCR   __IGNCR   /* Ignore carriage return on input. */
#endif /* !IGNCR && __IGNCR */
#if !defined(ICRNL) && defined(__ICRNL)
#define ICRNL   __ICRNL   /* Translate carriage return to newline on input (unless IGNCR is set). */
#endif /* !ICRNL && __ICRNL */
#if !defined(IUCLC) && defined(__IUCLC)
#define IUCLC   __IUCLC   /* Map uppercase characters to lowercase on input (requires `IEXTEN'). */
#endif /* !IUCLC && __IUCLC */
#if !defined(IXON) && defined(__IXON)
#define IXON    __IXON    /* Enable support for `VSTOP' to disable TTY output transmission. */
#endif /* !IXON && __IXON */
#if !defined(IXANY) && defined(__IXANY)
#define IXANY   __IXANY   /* Any input character has the behavior of `VSTART' */
#endif /* !IXANY && __IXANY */
#if !defined(IXOFF) && defined(__IXOFF)
#define IXOFF   __IXOFF   /* Status  bit  for   `VSTOP'  /   `VSTART':  Don't   transmit  pending   TTY  output   until  this   bit  is   cleared.
                           * When set, tty output is instead stored in a secondary buffer (s.a. `TTYIO_OPEND_GETLIMIT' and `TTYIO_OPEND_SETLIMIT') */
#endif /* !IXOFF && __IXOFF */
#if !defined(IMAXBEL) && defined(__IMAXBEL)
#define IMAXBEL __IMAXBEL /* Ring bell when input queue is full (KOS-SPECIFIC: The bell also gets triggered when the queue is empty and a delete character is received) */
#endif /* !IMAXBEL && __IMAXBEL */
#if !defined(IUTF8) && defined(__IUTF8)
#define IUTF8   __IUTF8   /* Input is UTF8 */
#endif /* !IUTF8 && __IUTF8 */

/* c_oflag bits */
#if !defined(OPOST) && defined(__OPOST)
#define OPOST       __OPOST  /* Enable implementation-defined output processing */
#endif /* !OPOST && __OPOST */
#if !defined(OLCUC) && defined(__OLCUC)
#define OLCUC       __OLCUC  /* Map lowercase characters to uppercase on output. */
#endif /* !OLCUC && __OLCUC */
#if !defined(ONLCR) && defined(__ONLCR)
#define ONLCR       __ONLCR  /* Map NL to CR-NL on output. */
#endif /* !ONLCR && __ONLCR */
#if !defined(OCRNL) && defined(__OCRNL)
#define OCRNL       __OCRNL  /* Map CR to NL on output. (Ignored when `ONLRET' is set) (When combined with `ONLCR', output CR as CRNL) */
#endif /* !OCRNL && __OCRNL */
#if !defined(ONOCR) && defined(__ONOCR)
#define ONOCR       __ONOCR  /* Don't output CR at column 0. */
#endif /* !ONOCR && __ONOCR */
#if !defined(ONLRET) && defined(__ONLRET)
#define ONLRET      __ONLRET /* Don't output CR. */
#endif /* !ONLRET && __ONLRET */
#if !defined(OFILL) && defined(__OFILL)
#define OFILL       __OFILL  /* ??? */
#endif /* !OFILL && __OFILL */
#if !defined(OFDEL) && defined(__OFDEL)
#define OFDEL       __OFDEL  /* ??? */
#endif /* !OFDEL && __OFDEL */
#if defined(__USE_MISC) || defined(__USE_XOPEN)
#if !defined(NLDLY) && defined(__NLDLY)
#define NLDLY       __NLDLY  /* ??? */
#endif /* !NLDLY && __NLDLY */
#if !defined(NL0) && defined(__NL0)
#define   NL0       __NL0    /* ??? */
#endif /* !NL0 && __NL0 */
#if !defined(NL1) && defined(__NL1)
#define   NL1       __NL1    /* ??? */
#endif /* !NL1 && __NL1 */
#if !defined(CRDLY) && defined(__CRDLY)
#define CRDLY       __CRDLY  /* ??? */
#endif /* !CRDLY && __CRDLY */
#if !defined(CR0) && defined(__CR0)
#define   CR0       __CR0    /* ??? */
#endif /* !CR0 && __CR0 */
#if !defined(CR1) && defined(__CR1)
#define   CR1       __CR1    /* ??? */
#endif /* !CR1 && __CR1 */
#if !defined(CR2) && defined(__CR2)
#define   CR2       __CR2    /* ??? */
#endif /* !CR2 && __CR2 */
#if !defined(CR3) && defined(__CR3)
#define   CR3       __CR3    /* ??? */
#endif /* !CR3 && __CR3 */
#if !defined(TABDLY) && defined(__TABDLY)
#define TABDLY      __TABDLY /* ??? */
#endif /* !TABDLY && __TABDLY */
#if !defined(TAB0) && defined(__TAB0)
#define   TAB0      __TAB0   /* ??? */
#endif /* !TAB0 && __TAB0 */
#if !defined(TAB1) && defined(__TAB1)
#define   TAB1      __TAB1   /* ??? */
#endif /* !TAB1 && __TAB1 */
#if !defined(TAB2) && defined(__TAB2)
#define   TAB2      __TAB2   /* ??? */
#endif /* !TAB2 && __TAB2 */
#if !defined(TAB3) && defined(__TAB3)
#define   TAB3      __TAB3   /* ??? */
#endif /* !TAB3 && __TAB3 */
#if !defined(BSDLY) && defined(__BSDLY)
#define BSDLY       __BSDLY  /* ??? */
#endif /* !BSDLY && __BSDLY */
#if !defined(BS0) && defined(__BS0)
#define   BS0       __BS0    /* ??? */
#endif /* !BS0 && __BS0 */
#if !defined(BS1) && defined(__BS1)
#define   BS1       __BS1    /* ??? */
#endif /* !BS1 && __BS1 */
#if !defined(FFDLY) && defined(__FFDLY)
#define FFDLY       __FFDLY  /* ??? */
#endif /* !FFDLY && __FFDLY */
#if !defined(FF0) && defined(__FF0)
#define   FF0       __FF0    /* ??? */
#endif /* !FF0 && __FF0 */
#if !defined(FF1) && defined(__FF1)
#define   FF1       __FF1    /* ??? */
#endif /* !FF1 && __FF1 */
#endif /* __USE_MISC || __USE_XOPEN */
#if !defined(VTDLY) && defined(__VTDLY)
#define VTDLY       __VTDLY  /* ??? */
#endif /* !VTDLY && __VTDLY */
#if !defined(VT0) && defined(__VT0)
#define   VT0       __VT0    /* ??? */
#endif /* !VT0 && __VT0 */
#if !defined(VT1) && defined(__VT1)
#define   VT1       __VT1    /* ??? */
#endif /* !VT1 && __VT1 */
#ifdef __USE_MISC
#if !defined(XTABS) && defined(__XTABS)
#define XTABS       __XTABS  /* ??? */
#endif /* !XTABS && __XTABS */
#endif /* __USE_MISC */
#ifdef __USE_BSD
#if !defined(ONOEOT) && defined(__ONOEOT)
#define ONOEOT __ONOEOT
#endif /* !ONOEOT && __ONOEOT */
#endif /* __USE_BSD */

/* c_cflag bit meaning */
#ifdef __USE_MISC
#if !defined(CBAUD) && defined(__CBAU)
#define CBAUD     __CBAUD
#endif /* !CBAUD && __CBAU */
#endif /* __USE_MISC */
#if !defined(B0) && defined(__B0)
#define B0        __B0 /* hang up */
#endif /* !B0 && __B0 */
#if !defined(B50) && defined(__B50)
#define B50       __B50
#endif /* !B50 && __B50 */
#if !defined(B75) && defined(__B75)
#define B75       __B75
#endif /* !B75 && __B75 */
#if !defined(B110) && defined(__B110)
#define B110      __B110
#endif /* !B110 && __B110 */
#if !defined(B134) && defined(__B134)
#define B134      __B134
#endif /* !B134 && __B134 */
#if !defined(B150) && defined(__B150)
#define B150      __B150
#endif /* !B150 && __B150 */
#if !defined(B200) && defined(__B200)
#define B200      __B200
#endif /* !B200 && __B200 */
#if !defined(B300) && defined(__B300)
#define B300      __B300
#endif /* !B300 && __B300 */
#if !defined(B600) && defined(__B600)
#define B600      __B600
#endif /* !B600 && __B600 */
#if !defined(B1200) && defined(__B1200)
#define B1200     __B1200
#endif /* !B1200 && __B1200 */
#if !defined(B1800) && defined(__B1800)
#define B1800     __B1800
#endif /* !B1800 && __B1800 */
#if !defined(B2400) && defined(__B2400)
#define B2400     __B2400
#endif /* !B2400 && __B2400 */
#if !defined(B4800) && defined(__B4800)
#define B4800     __B4800
#endif /* !B4800 && __B4800 */
#if !defined(B9600) && defined(__B9600)
#define B9600     __B9600
#endif /* !B9600 && __B9600 */
#if !defined(B19200) && defined(__B19200)
#define B19200    __B19200
#endif /* !B19200 && __B19200 */
#if !defined(B38400) && defined(__B38400)
#define B38400    __B38400
#endif /* !B38400 && __B38400 */
#ifdef __USE_MISC
#if !defined(EXTA) && defined(__EXTA)
#define EXTA      __EXTA
#endif /* !EXTA && __EXTA */
#if !defined(EXTB) && defined(__EXTB)
#define EXTB      __EXTB
#endif /* !EXTB && __EXTB */
#endif /* __USE_MISC */
#if !defined(CSIZE) && defined(__CSIZE)
#define CSIZE     __CSIZE /* Mask for the character size (in bits) */
#endif /* !CSIZE && __CSIZE */
#if !defined(CS5) && defined(__CS5)
#define   CS5     __CS5   /* 5-bit characters */
#endif /* !CS5 && __CS5 */
#if !defined(CS6) && defined(__CS6)
#define   CS6     __CS6   /* 6-bit characters */
#endif /* !CS6 && __CS6 */
#if !defined(CS7) && defined(__CS7)
#define   CS7     __CS7   /* 7-bit characters */
#endif /* !CS7 && __CS7 */
#if !defined(CS8) && defined(__CS8)
#define   CS8     __CS8   /* 8-bit characters */
#endif /* !CS8 && __CS8 */
#if !defined(CSTOPB) && defined(__CSTOPB)
#define CSTOPB    __CSTOPB
#endif /* !CSTOPB && __CSTOPB */
#if !defined(CREAD) && defined(__CREAD)
#define CREAD     __CREAD
#endif /* !CREAD && __CREAD */
#if !defined(PARENB) && defined(__PARENB)
#define PARENB    __PARENB
#endif /* !PARENB && __PARENB */
#if !defined(PARODD) && defined(__PARODD)
#define PARODD    __PARODD
#endif /* !PARODD && __PARODD */
#if !defined(HUPCL) && defined(__HUPCL)
#define HUPCL     __HUPCL
#endif /* !HUPCL && __HUPCL */
#if !defined(CLOCAL) && defined(__CLOCAL)
#define CLOCAL    __CLOCAL
#endif /* !CLOCAL && __CLOCAL */
#ifdef __USE_MISC
#if !defined(CBAUDEX) && defined(__CBAUDEX)
#define CBAUDEX   __CBAUDEX
#endif /* !CBAUDEX && __CBAUDEX */
#endif /* __USE_MISC */
#if !defined(B57600) && defined(__B57600)
#define B57600    __B57600
#endif /* !B57600 && __B57600 */
#if !defined(B115200) && defined(__B115200)
#define B115200   __B115200
#endif /* !B115200 && __B115200 */
#if !defined(B230400) && defined(__B230400)
#define B230400   __B230400
#endif /* !B230400 && __B230400 */
#if !defined(B460800) && defined(__B460800)
#define B460800   __B460800
#endif /* !B460800 && __B460800 */
#if !defined(B500000) && defined(__B500000)
#define B500000   __B500000
#endif /* !B500000 && __B500000 */
#if !defined(B576000) && defined(__B576000)
#define B576000   __B576000
#endif /* !B576000 && __B576000 */
#if !defined(B921600) && defined(__B921600)
#define B921600   __B921600
#endif /* !B921600 && __B921600 */
#if !defined(B1000000) && defined(__B1000000)
#define B1000000  __B1000000
#endif /* !B1000000 && __B1000000 */
#if !defined(B1152000) && defined(__B1152000)
#define B1152000  __B1152000
#endif /* !B1152000 && __B1152000 */
#if !defined(B1500000) && defined(__B1500000)
#define B1500000  __B1500000
#endif /* !B1500000 && __B1500000 */
#if !defined(B2000000) && defined(__B2000000)
#define B2000000  __B2000000
#endif /* !B2000000 && __B2000000 */
#if !defined(B2500000) && defined(__B2500000)
#define B2500000  __B2500000
#endif /* !B2500000 && __B2500000 */
#if !defined(B3000000) && defined(__B3000000)
#define B3000000  __B3000000
#endif /* !B3000000 && __B3000000 */
#if !defined(B3500000) && defined(__B3500000)
#define B3500000  __B3500000
#endif /* !B3500000 && __B3500000 */
#if !defined(B4000000) && defined(__B4000000)
#define B4000000  __B4000000
#endif /* !B4000000 && __B4000000 */
#if !defined(B7200) && defined(__B7200)
#define B7200 __B7200
#endif /* !B7200 && __B7200 */
#if !defined(B14400) && defined(__B14400)
#define B14400 __B14400
#endif /* !B14400 && __B14400 */
#if !defined(B28800) && defined(__B28800)
#define B28800 __B28800
#endif /* !B28800 && __B28800 */
#if !defined(B76800) && defined(__B76800)
#define B76800 __B76800
#endif /* !B76800 && __B76800 */

#ifdef __USE_MISC
#if !defined(CIBAUD) && defined(__CIBAUD)
#define CIBAUD    __CIBAUD /* input baud rate (not used) */
#endif /* !CIBAUD && __CIBAUD */
#if !defined(CMSPAR) && defined(__CMSPAR)
#define CMSPAR    __CMSPAR /* mark or space (stick) parity */
#endif /* !CMSPAR && __CMSPAR */
#if !defined(CRTSCTS) && defined(__CRTSCTS)
#define CRTSCTS   __CRTSCTS /* flow control */
#endif /* !CRTSCTS && __CRTSCTS */
#endif /* __USE_MISC */
#ifdef __USE_BSD
#if !defined(CIGNORE) && defined(__CIGNORE)
#define CIGNORE __CIGNORE
#endif /* !CIGNORE && __CIGNORE */
#if !defined(CCTS_OFLOW) && defined(__CCTS_OFLOW)
#define CCTS_OFLOW __CCTS_OFLOW
#endif /* !CCTS_OFLOW && __CCTS_OFLOW */
#if !defined(CRTS_IFLOW) && defined(__CRTS_IFLOW)
#define CRTS_IFLOW __CRTS_IFLOW
#endif /* !CRTS_IFLOW && __CRTS_IFLOW */
#if !defined(CDTR_IFLOW) && defined(__CDTR_IFLOW)
#define CDTR_IFLOW __CDTR_IFLOW
#endif /* !CDTR_IFLOW && __CDTR_IFLOW */
#if !defined(CDSR_OFLOW) && defined(__CDSR_OFLOW)
#define CDSR_OFLOW __CDSR_OFLOW
#endif /* !CDSR_OFLOW && __CDSR_OFLOW */
#if !defined(CCAR_OFLOW) && defined(__CCAR_OFLOW)
#define CCAR_OFLOW __CCAR_OFLOW
#endif /* !CCAR_OFLOW && __CCAR_OFLOW */
#if !defined(CNO_RTSDTR) && defined(__CNO_RTSDTR)
#define CNO_RTSDTR __CNO_RTSDTR
#endif /* !CNO_RTSDTR && __CNO_RTSDTR */
#endif /* __USE_BSD */

/* c_lflag bits */
#if !defined(ISIG) && defined(__ISIG)
#define ISIG        __ISIG    /* When any of the characters INTR, QUIT, SUSP, or DSUSP are received, generate the corresponding signal. */
#endif /* !ISIG && __ISIG */
#if !defined(ICANON) && defined(__ICANON)
#define ICANON      __ICANON  /* Enable canonical mode */
#endif /* !ICANON && __ICANON */
#if defined(__USE_MISC) || defined(__USE_XOPEN)
#if !defined(XCASE) && defined(__XCASE)
#define XCASE       __XCASE   /* If ICANON is also set, terminal is uppercase only. Input is converted to lowercase,
                               * except for characters preceded by \.  On output, uppercase characters are  preceded
                               * by \ and lowercase characters are converted to uppercase. */
#endif /* !XCASE && __XCASE */
#endif /* __USE_MISC || __USE_XOPEN */
#if !defined(ECHO) && defined(__ECHO)
#define ECHO        __ECHO    /* Echo input characters */
#endif /* !ECHO && __ECHO */
#if !defined(ECHOE) && defined(__ECHOE)
#define ECHOE       __ECHOE   /* If ICANON is also set, the VERASE character erases the preceding input character, and VWERASE erases the preceding word */
#endif /* !ECHOE && __ECHOE */
#if !defined(ECHOK) && defined(__ECHOK)
#define ECHOK       __ECHOK   /* If ICANON is also set, the VKILL character erases the current line */
#endif /* !ECHOK && __ECHOK */
#if !defined(ECHONL) && defined(__ECHONL)
#define ECHONL      __ECHONL  /* If   ICANON  is  also  set,  echo  the  NL  character  even  if  ECHO  is  not  set
                               * NOTE: for this purpose, the NL character(s) recognized are '\n', `VEOL' and `VEOL2' */
#endif /* !ECHONL && __ECHONL */
#if !defined(NOFLSH) && defined(__NOFLSH)
#define NOFLSH      __NOFLSH  /* Disable flushing the input and output queues when generating signals for the INT, QUIT, and SUSP characters */
#endif /* !NOFLSH && __NOFLSH */
#if !defined(TOSTOP) && defined(__TOSTOP)
#define TOSTOP      __TOSTOP  /* Send the SIGTTOU signal to the process group of a background process which tries to write to its controlling terminal */
#endif /* !TOSTOP && __TOSTOP */
#ifdef __USE_MISC
#if !defined(ECHOCTL) && defined(__ECHOCTL)
#define ECHOCTL     __ECHOCTL /* If ECHO is also set, terminal special characters other than TAB(\t), NL(\n),
                               * START,  and STOP are echoed as ^X, where  X is the character with ASCII code
                               * 0x40  greater than the  special character. For  example, character 0x08 (BS)
                               * is echoed as ^H */
#endif /* !ECHOCTL && __ECHOCTL */
#if !defined(ECHOPRT) && defined(__ECHOPRT)
#define ECHOPRT     __ECHOPRT /* This bit is like ECHOE, enables display of the ERASE character in a way that
                               * is geared to a hardcopy terminal. When  you type the ERASE character, a  `\'
                               * character is  printed followed  by the  first character  erased. Typing  the
                               * ERASE  character  again just  prints the  next  character erased.  Then, the
                               * next  time  you  type  a  normal  character,  a  `/'  character  is  printed
                               * before the character echoes. */
#endif /* !ECHOPRT && __ECHOPRT */
#if !defined(ECHOKE) && defined(__ECHOKE)
#define ECHOKE      __ECHOKE  /* If ICANON is also set, KILL is echoed by erasing each character on the line, as specified by ECHOE and ECHOPRT */
#endif /* !ECHOKE && __ECHOKE */
#if !defined(FLUSHO) && defined(__FLUSHO)
#define FLUSHO      __FLUSHO  /* Output is being flushed. This flag is toggled by typing the DISCARD character */
#endif /* !FLUSHO && __FLUSHO */
#if !defined(PENDIN) && defined(__PENDIN)
#define PENDIN      __PENDIN  /* ??? */
#endif /* !PENDIN && __PENDIN */
#endif /* __USE_MISC */
#if !defined(IEXTEN) && defined(__IEXTEN)
#define IEXTEN      __IEXTEN  /* Enable implementation-defined input processing. This flag, as
                               * well  as ICANON  must be  enabled for  the special characters
                               * EOL2, LNEXT, REPRINT, WERASE to  be interpreted, and for  the
                               * IUCLC flag to be effective */
#endif /* !IEXTEN && __IEXTEN */
#ifdef __USE_MISC
#if !defined(EXTPROC) && defined(__EXTPROC)
#define EXTPROC     __EXTPROC /* Skip handling of: `PARMRK', `ECHO' and `IXON'+`IXANY', as well as `c_cc[*]' */
#endif /* !EXTPROC && __EXTPROC */
#endif /* __USE_MISC */
#if !defined(ALTWERASE) && defined(__ALTWERASE)
#define ALTWERASE __ALTWERASE
#endif /* !ALTWERASE && __ALTWERASE */
#ifdef __USE_BSD
#if !defined(NOKERNINFO) && defined(__NOKERNINFO)
#define NOKERNINFO __NOKERNINFO
#endif /* !NOKERNINFO && __NOKERNINFO */
#endif /* __USE_BSD */


/* tcflow() and TCXONC use these */
#if !defined(TCOOFF) && defined(__TCOOFF)
#define TCOOFF __TCOOFF /* Suspends output. */
#endif /* !TCOOFF && __TCOOFF */
#if !defined(TCOON) && defined(__TCOON)
#define TCOON  __TCOON  /* Restarts suspended output. */
#endif /* !TCOON && __TCOON */
#if !defined(TCIOFF) && defined(__TCIOFF)
#define TCIOFF __TCIOFF /* Suspends input. */
#endif /* !TCIOFF && __TCIOFF */
#if !defined(TCION) && defined(__TCION)
#define TCION  __TCION  /* Restarts suspended input. */
#endif /* !TCION && __TCION */

/* tcflush() and TCFLSH use these */
#if !defined(TCIFLUSH) && defined(__TCIFLUSH)
#define TCIFLUSH  __TCIFLUSH
#endif /* !TCIFLUSH && __TCIFLUSH */
#if !defined(TCOFLUSH) && defined(__TCOFLUSH)
#define TCOFLUSH  __TCOFLUSH
#endif /* !TCOFLUSH && __TCOFLUSH */
#if !defined(TCIOFLUSH) && defined(__TCIOFLUSH)
#define TCIOFLUSH __TCIOFLUSH
#endif /* !TCIOFLUSH && __TCIOFLUSH */

/* tcsetattr uses these */
#if !defined(TCSANOW) && defined(__TCSANOW)
#define TCSANOW   __TCSANOW   /* Set terminal attributes (s.a. `TCSETA') */
#endif /* !TCSANOW && __TCSANOW */
#if !defined(TCSADRAIN) && defined(__TCSADRAIN)
#define TCSADRAIN __TCSADRAIN /* Wait for all unwritten data to be transmitted, discard all unread data, then set terminal attributes (s.a. `TCSETAW') */
#endif /* !TCSADRAIN && __TCSADRAIN */
#if !defined(TCSAFLUSH) && defined(__TCSAFLUSH)
#define TCSAFLUSH __TCSAFLUSH /* Wait for all unwritten data to be transmitted, then set terminal attributes (s.a. `TCSETAF') */
#endif /* !TCSAFLUSH && __TCSAFLUSH */
#ifdef __USE_BSD
#if defined(TCSASOFT) && defined(__TCSASOFT)
#define TCSASOFT __TCSASOFT /* Only modify the software state. */
#endif /* TCSASOFT && !__TCSASOFT */
#endif /* __USE_BSD */


#ifdef __USE_BSD
#ifndef OXTABS
#ifdef __OXTABS
#define OXTABS __OXTABS
#elif defined(__TAB3)
#define OXTABS __TAB3
#endif /* ... */
#endif /* !OXTABS */
#if !defined(MDMBUF) && defined(__CCAR_OFLOW)
#define MDMBUF __CCAR_OFLOW
#endif /* !MDMBUF && __CCAR_OFLOW */
#endif /* __USE_BSD */

#if !defined(CDTRCTS) && defined(__CDTRCTS)
#define CDTRCTS __CDTRCTS
#endif /* !CDTRCTS && __CDTRCTS */
#if !defined(CHWFLOW) && defined(__CHWFLOW)
#define CHWFLOW __CHWFLOW
#endif /* !CHWFLOW && __CHWFLOW */



#ifdef __CC__
__SYSDECL_BEGIN

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#ifdef __CRT_HAVE_cfgetospeed
/* >> cfgetospeed(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),speed_t,__NOTHROW_NCX,cfgetospeed,(struct termios const *__restrict __termios_p),(__termios_p))
#else /* __CRT_HAVE_cfgetospeed */
#include <libc/local/termios/cfgetospeed.h>
/* >> cfgetospeed(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(cfgetospeed, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) speed_t __NOTHROW_NCX(__LIBCCALL cfgetospeed)(struct termios const *__restrict __termios_p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfgetospeed))(__termios_p); })
#endif /* !__CRT_HAVE_cfgetospeed */
#ifdef __CRT_HAVE_cfgetispeed
/* >> cfgetispeed(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),speed_t,__NOTHROW_NCX,cfgetispeed,(struct termios const *__restrict __termios_p),(__termios_p))
#else /* __CRT_HAVE_cfgetispeed */
#include <libc/local/termios/cfgetispeed.h>
/* >> cfgetispeed(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(cfgetispeed, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) speed_t __NOTHROW_NCX(__LIBCCALL cfgetispeed)(struct termios const *__restrict __termios_p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfgetispeed))(__termios_p); })
#endif /* !__CRT_HAVE_cfgetispeed */
#ifdef __CRT_HAVE_cfsetospeed
/* >> cfsetospeed(3) */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,cfsetospeed,(struct termios *__restrict __termios_p, speed_t __speed),(__termios_p,__speed))
#else /* __CRT_HAVE_cfsetospeed */
#include <libc/local/termios/cfsetospeed.h>
/* >> cfsetospeed(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(cfsetospeed, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL cfsetospeed)(struct termios *__restrict __termios_p, speed_t __speed) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfsetospeed))(__termios_p, __speed); })
#endif /* !__CRT_HAVE_cfsetospeed */
#ifdef __CRT_HAVE_cfsetispeed
/* >> cfsetispeed(3) */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,cfsetispeed,(struct termios *__restrict __termios_p, speed_t __speed),(__termios_p,__speed))
#else /* __CRT_HAVE_cfsetispeed */
#include <libc/local/termios/cfsetispeed.h>
/* >> cfsetispeed(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(cfsetispeed, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL cfsetispeed)(struct termios *__restrict __termios_p, speed_t __speed) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfsetispeed))(__termios_p, __speed); })
#endif /* !__CRT_HAVE_cfsetispeed */
#ifdef __CRT_HAVE_tcgetattr
/* >> tcgetattr(3)
 * Get terminal attributes */
__CDECLARE(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,tcgetattr,(__fd_t __fd, struct termios *__restrict __termios_p),(__fd,__termios_p))
#elif defined(__CRT_HAVE___tcgetattr)
/* >> tcgetattr(3)
 * Get terminal attributes */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,tcgetattr,(__fd_t __fd, struct termios *__restrict __termios_p),__tcgetattr,(__fd,__termios_p))
#else /* ... */
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCGETA)
#include <libc/local/termios/tcgetattr.h>
/* >> tcgetattr(3)
 * Get terminal attributes */
__NAMESPACE_LOCAL_USING_OR_IMPL(tcgetattr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL tcgetattr)(__fd_t __fd, struct termios *__restrict __termios_p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tcgetattr))(__fd, __termios_p); })
#endif /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCGETA */
#endif /* !... */
#ifdef __CRT_HAVE_tcsetattr
/* >> tcsetattr(3)
 * Set terminal attributes
 * @param: optional_actions: One of `TCSANOW', `TCSADRAIN' or `TCSAFLUSH' */
__CDECLARE(__ATTR_FDARG(1) __ATTR_IN(3),int,__NOTHROW_NCX,tcsetattr,(__fd_t __fd, __STDC_INT_AS_UINT_T __optional_actions, struct termios const *__restrict __termios_p),(__fd,__optional_actions,__termios_p))
#elif defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)
#include <libc/local/termios/tcsetattr.h>
/* >> tcsetattr(3)
 * Set terminal attributes
 * @param: optional_actions: One of `TCSANOW', `TCSADRAIN' or `TCSAFLUSH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(tcsetattr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_IN(3) int __NOTHROW_NCX(__LIBCCALL tcsetattr)(__fd_t __fd, __STDC_INT_AS_UINT_T __optional_actions, struct termios const *__restrict __termios_p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tcsetattr))(__fd, __optional_actions, __termios_p); })
#endif /* ... */
#ifdef __CRT_HAVE_tcsendbreak
/* >> tcsendbreak(3) */
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_NCX,tcsendbreak,(__fd_t __fd, int __duration),(__fd,__duration))
#else /* __CRT_HAVE_tcsendbreak */
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCSBRKP)
#include <libc/local/termios/tcsendbreak.h>
/* >> tcsendbreak(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(tcsendbreak, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) int __NOTHROW_NCX(__LIBCCALL tcsendbreak)(__fd_t __fd, int __duration) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tcsendbreak))(__fd, __duration); })
#endif /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCSBRKP */
#endif /* !__CRT_HAVE_tcsendbreak */
#ifdef __CRT_HAVE_tcdrain
/* >> tcdrain(3) */
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_RPC,tcdrain,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_tcdrain */
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCSBRK)
#include <libc/local/termios/tcdrain.h>
/* >> tcdrain(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(tcdrain, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) int __NOTHROW_RPC(__LIBCCALL tcdrain)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tcdrain))(__fd); })
#endif /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCSBRK */
#endif /* !__CRT_HAVE_tcdrain */
#ifdef __CRT_HAVE_tcflush
/* >> tcflush(3)
 * @param: queue_selector: One of `TCIFLUSH', `TCOFLUSH' or `TCIOFLUSH' */
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_NCX,tcflush,(__fd_t __fd, __STDC_INT_AS_UINT_T __queue_selector),(__fd,__queue_selector))
#else /* __CRT_HAVE_tcflush */
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCFLSH)
#include <libc/local/termios/tcflush.h>
/* >> tcflush(3)
 * @param: queue_selector: One of `TCIFLUSH', `TCOFLUSH' or `TCIOFLUSH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(tcflush, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) int __NOTHROW_NCX(__LIBCCALL tcflush)(__fd_t __fd, __STDC_INT_AS_UINT_T __queue_selector) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tcflush))(__fd, __queue_selector); })
#endif /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCFLSH */
#endif /* !__CRT_HAVE_tcflush */
#ifdef __CRT_HAVE_tcflow
/* >> tcflow(3)
 * @param: action: One of `TCOOFF', `TCOON', `TCIOFF', `TCION' */
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_NCX,tcflow,(__fd_t __fd, __STDC_INT_AS_UINT_T __action),(__fd,__action))
#else /* __CRT_HAVE_tcflow */
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TCXONC)
#include <libc/local/termios/tcflow.h>
/* >> tcflow(3)
 * @param: action: One of `TCOOFF', `TCOON', `TCIOFF', `TCION' */
__NAMESPACE_LOCAL_USING_OR_IMPL(tcflow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) int __NOTHROW_NCX(__LIBCCALL tcflow)(__fd_t __fd, __STDC_INT_AS_UINT_T __action) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tcflow))(__fd, __action); })
#endif /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TCXONC */
#endif /* !__CRT_HAVE_tcflow */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifdef __CRT_HAVE_tcgetsid
/* >> tcgetsid(3) */
__CDECLARE(__ATTR_FDARG(1),__pid_t,__NOTHROW_NCX,tcgetsid,(__fd_t __fd),(__fd))
#else /* __CRT_HAVE_tcgetsid */
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TIOCGSID)
#include <libc/local/termios/tcgetsid.h>
/* >> tcgetsid(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(tcgetsid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __pid_t __NOTHROW_NCX(__LIBCCALL tcgetsid)(__fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tcgetsid))(__fd); })
#endif /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TIOCGSID */
#endif /* !__CRT_HAVE_tcgetsid */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#if defined(__USE_BSD)
#ifdef __CRT_HAVE_tcsetsid
/* >> tcsetsid(3) */
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_NCX,tcsetsid,(__fd_t __fd, __pid_t __pid),(__fd,__pid))
#else /* __CRT_HAVE_tcsetsid */
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TIOCSCTTY)
#include <libc/local/termios/tcsetsid.h>
/* >> tcsetsid(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(tcsetsid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) int __NOTHROW_NCX(__LIBCCALL tcsetsid)(__fd_t __fd, __pid_t __pid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tcsetsid))(__fd, __pid); })
#endif /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TIOCSCTTY */
#endif /* !__CRT_HAVE_tcsetsid */
#endif /* __USE_BSD */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_cfsetspeed
/* >> cfsetspeed(3) */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,cfsetspeed,(struct termios *__restrict __termios_p, speed_t __speed),(__termios_p,__speed))
#else /* __CRT_HAVE_cfsetspeed */
#include <libc/local/termios/cfsetspeed.h>
/* >> cfsetspeed(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(cfsetspeed, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL cfsetspeed)(struct termios *__restrict __termios_p, speed_t __speed) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfsetspeed))(__termios_p, __speed); })
#endif /* !__CRT_HAVE_cfsetspeed */
#ifdef __CRT_HAVE_cfmakeraw
/* >> cfmakeraw(3)
 * Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
 * This entails the CANON and all control characters being disabled, as well as
 * any sort of input/output text processing no longer taking place. */
__CDECLARE_VOID(__ATTR_INOUT(1),__NOTHROW_NCX,cfmakeraw,(struct termios *__restrict __termios_p),(__termios_p))
#else /* __CRT_HAVE_cfmakeraw */
#include <libc/local/termios/cfmakeraw.h>
/* >> cfmakeraw(3)
 * Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
 * This entails the CANON and all control characters being disabled, as well as
 * any sort of input/output text processing no longer taking place. */
__NAMESPACE_LOCAL_USING_OR_IMPL(cfmakeraw, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) void __NOTHROW_NCX(__LIBCCALL cfmakeraw)(struct termios *__restrict __termios_p) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfmakeraw))(__termios_p); })
#endif /* !__CRT_HAVE_cfmakeraw */
#endif /* __USE_MISC */

#if defined(__USE_KOS) || defined(__USE_BSD)
#ifdef __CRT_HAVE_cfmakesane
/* >> cfmakesane(3)
 * Set ~sane~ mode for the given `termios_p' (out-only; meaning that `termios_p' gets initialized by this function)
 * Sane here  refers  to  setting  all values  to  their  defaults,  as they  are  defined  in  <sys/ttydefaults.h> */
__CDECLARE_VOID(__ATTR_OUT(1),__NOTHROW_NCX,cfmakesane,(struct termios *__restrict __termios_p),(__termios_p))
#else /* __CRT_HAVE_cfmakesane */
#include <libc/local/termios/cfmakesane.h>
/* >> cfmakesane(3)
 * Set ~sane~ mode for the given `termios_p' (out-only; meaning that `termios_p' gets initialized by this function)
 * Sane here  refers  to  setting  all values  to  their  defaults,  as they  are  defined  in  <sys/ttydefaults.h> */
__NAMESPACE_LOCAL_USING_OR_IMPL(cfmakesane, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL cfmakesane)(struct termios *__restrict __termios_p) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(cfmakesane))(__termios_p); })
#endif /* !__CRT_HAVE_cfmakesane */
#endif /* __USE_KOS || __USE_BSD */

/* NetBSD doesn't actually namespace away these functions, but we do to keep everything clean. */
#ifdef __USE_NETBSD
#ifdef __CRT_HAVE_tcgetwinsize
/* >> tcgetwinsize(3) */
__CDECLARE(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,tcgetwinsize,(__fd_t __fd, struct winsize *__winsize_p),(__fd,__winsize_p))
#else /* __CRT_HAVE_tcgetwinsize */
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TIOCGWINSZ)
#include <libc/local/termios/tcgetwinsize.h>
/* >> tcgetwinsize(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(tcgetwinsize, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL tcgetwinsize)(__fd_t __fd, struct winsize *__winsize_p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tcgetwinsize))(__fd, __winsize_p); })
#endif /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TIOCGWINSZ */
#endif /* !__CRT_HAVE_tcgetwinsize */
#ifdef __CRT_HAVE_tcsetwinsize
/* >> tcsetwinsize(3) */
__CDECLARE(__ATTR_FDARG(1) __ATTR_IN(2),int,__NOTHROW_NCX,tcsetwinsize,(__fd_t __fd, struct winsize const *__winsize_p),(__fd,__winsize_p))
#else /* __CRT_HAVE_tcsetwinsize */
#include <asm/os/tty.h>
#if (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl)) && defined(__TIOCSWINSZ)
#include <libc/local/termios/tcsetwinsize.h>
/* >> tcsetwinsize(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(tcsetwinsize, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL tcsetwinsize)(__fd_t __fd, struct winsize const *__winsize_p) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tcsetwinsize))(__fd, __winsize_p); })
#endif /* (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl) && __TIOCSWINSZ */
#endif /* !__CRT_HAVE_tcsetwinsize */
#endif /* __USE_NETBSD */

__SYSDECL_END
#endif /* __CC__ */

#if defined(__USE_MISC) || defined(__USE_BSD)
#define CCEQ(val, c) ((c) == (val) && (val) != _POSIX_VDISABLE)
#endif /* __USE_MISC || __USE_BSD */

#endif /* !_TERMIOS_H */
