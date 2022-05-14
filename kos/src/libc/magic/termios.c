/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: POSIX.1c (Issue 3, IEEE Std 1003.1c-1995) */
/* (#) Portability: Cygwin        (/newlib/libc/include/termios.h) */
/* (#) Portability: DJGPP         (/include/termios.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/termios.h) */
/* (#) Portability: FreeBSD       (/include/termios.h) */
/* (#) Portability: GNU C Library (/termios/termios.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/termios.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/termios.h) */
/* (#) Portability: diet libc     (/include/termios.h) */
/* (#) Portability: libc4/5       (/include/termios.h) */
/* (#) Portability: libc6         (/include/termios.h) */
/* (#) Portability: mintlib       (/include/termios.h) */
/* (#) Portability: musl libc     (/include/termios.h) */
/* (#) Portability: uClibc        (/include/termios.h) */
}

%[define_replacement(fd_t     = __fd_t)]
%[define_replacement(pid_t    = __pid_t)]
%[define_replacement(cc_t     = __UINT8_TYPE__)]
%[define_replacement(speed_t  = __UINT32_TYPE__)]
%[define_replacement(tcflag_t = __UINT32_TYPE__)]

%[define_decl_include("<bits/os/termios.h>": ["struct termios"])]

%[default:section(".text.crt{|.dos}.io.tty")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/os/termios.h>
)]%[insert:prefix(
#include <bits/os/termios.h>
)]%{
/*#include <sys/ioctl.h>*/

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



}
%#ifdef __CC__
%{
__SYSDECL_BEGIN

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

}

@@>> cfgetospeed(3)
[[pure, wunused, decl_include("<bits/os/termios.h>", "<bits/types.h>")]]
speed_t cfgetospeed([[nonnull]] struct termios const *__restrict termios_p) {
	return termios_p->@c_ospeed@;
}

@@>> cfgetispeed(3)
[[pure, wunused, decl_include("<bits/os/termios.h>", "<bits/types.h>")]]
speed_t cfgetispeed([[nonnull]] struct termios const *__restrict termios_p) {
	return termios_p->@c_ispeed@;
}

@@>> cfsetospeed(3)
[[decl_include("<bits/os/termios.h>", "<bits/types.h>")]]
int cfsetospeed([[nonnull]] struct termios *__restrict termios_p, speed_t speed) {
	termios_p->@c_ospeed@ = speed;
	return 0;
}

@@>> cfsetispeed(3)
[[decl_include("<bits/os/termios.h>", "<bits/types.h>")]]
int cfsetispeed([[nonnull]] struct termios *__restrict termios_p, speed_t speed) {
	termios_p->@c_ispeed@ = speed;
	return 0;
}

%[assume_defined_in_kos(TCGETA, __TCGETA)]
%[assume_defined_in_kos(TCSETA, __TCSETA, TCSANOW, __TCSANOW)]
%[assume_defined_in_kos(TCSETAW, __TCSETAW, TCSADRAIN, __TCSADRAIN)]
%[assume_defined_in_kos(TCSETAF, __TCSETAF, TCSAFLUSH, __TCSAFLUSH)]

@@>> tcgetattr(3)
@@Get terminal attributes
[[decl_include("<bits/os/termios.h>", "<bits/types.h>"), export_alias("__tcgetattr")]]
[[requires_include("<asm/os/tty.h>")]] /* __TCGETA */
[[requires($has_function(ioctl) && defined(__TCGETA))]]
int tcgetattr($fd_t fd, [[nonnull]] struct termios *__restrict termios_p) {
	return (int)ioctl(fd, __TCGETA, termios_p);
}

@@>> tcsetattr(3)
@@Set terminal attributes
@@@param: optional_actions: One of `TCSANOW', `TCSADRAIN' or `TCSAFLUSH'
[[impl_include("<asm/os/tty.h>", "<asm/os/termios.h>", "<libc/errno.h>")]]
[[decl_include("<features.h>", "<bits/os/termios.h>", "<bits/types.h>")]]
[[requires_function(ioctl)]]
int tcsetattr($fd_t fd, __STDC_INT_AS_UINT_T optional_actions,
              [[nonnull]] struct termios const *__restrict termios_p) {
	int cmd;
	switch (optional_actions) {

@@pp_if defined(__TCSANOW) && defined(__TCSETA)@@
	case __TCSANOW:
		cmd = __TCSETA;
		break;
@@pp_endif@@

@@pp_if defined(__TCSADRAIN) && defined(__TCSETAW)@@
	case __TCSADRAIN:
		cmd = __TCSETAW;
		break;
@@pp_endif@@

@@pp_if defined(__TCSAFLUSH) && defined(__TCSETAF)@@
	case __TCSAFLUSH:
		cmd = __TCSETAF;
		break;
@@pp_endif@@

	default:
@@pp_ifdef EINVAL@@
		return libc_seterrno(EINVAL);
@@pp_else@@
		return libc_seterrno(1);
@@pp_endif@@
	}
	return (int)ioctl(fd, cmd, termios_p);
}


@@>> tcsendbreak(3)
[[decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/tty.h>")]]
[[requires($has_function(ioctl) && defined(__TCSBRKP))]]
int tcsendbreak($fd_t fd, int duration) {
	return (int)ioctl(fd, __TCSBRKP, duration);
}

@@>> tcdrain(3)
[[decl_include("<bits/types.h>")]]
[[cp, requires_include("<asm/os/tty.h>")]]
[[requires($has_function(ioctl) && defined(__TCSBRK))]]
int tcdrain($fd_t fd) {
	return (int)ioctl(fd, __TCSBRK, 1);
}

%[assume_defined_in_kos(TCFLSH, __TCFLSH)]
%[assume_defined_in_kos(TCIFLUSH, TCOFLUSH, TCIOFLUSH)]
%[assume_defined_in_kos(__TCIFLUSH, __TCOFLUSH, __TCIOFLUSH)]

@@>> tcflush(3)
@@@param: queue_selector: One of `TCIFLUSH', `TCOFLUSH' or `TCIOFLUSH'
[[decl_include("<features.h>", "<bits/types.h>")]]
[[requires_include("<asm/os/tty.h>")]]
[[requires($has_function(ioctl) && defined(__TCFLSH))]]
int tcflush($fd_t fd, __STDC_INT_AS_UINT_T queue_selector) {
	return (int)ioctl(fd, __TCFLSH, queue_selector);
}

@@>> tcflow(3)
@@@param: action: One of `TCOOFF', `TCOON', `TCIOFF', `TCION'
[[decl_include("<features.h>", "<bits/types.h>")]]
[[requires_include("<asm/os/tty.h>")]]
[[requires($has_function(ioctl) && defined(__TCXONC))]]
int tcflow($fd_t fd, __STDC_INT_AS_UINT_T action) {
	return (int)ioctl(fd, __TCXONC, action);
}

%[assume_defined_in_kos(TIOCGSID, __TIOCGSID)]

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
@@>> tcgetsid(3)
[[decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/tty.h>")]]
[[requires($has_function(ioctl) && defined(__TIOCGSID))]]
$pid_t tcgetsid($fd_t fd) {
	pid_t result;
	if unlikely(ioctl(fd, __TIOCGSID, &result) < 0)
		result = -1;
	return result;
}
%#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

%[assume_defined_in_kos(TIOCSCTTY, __TIOCSCTTY)]

%
%#if defined(__USE_BSD)
@@>> tcsetsid(3)
[[decl_include("<bits/types.h>")]]
[[impl_include("<libc/errno.h>")]]
[[requires_include("<asm/os/tty.h>")]]
[[requires($has_function(ioctl) && defined(__TIOCSCTTY))]]
int tcsetsid($fd_t fd, $pid_t pid) {
	int result;
	if unlikely(pid != getsid(0)) {
@@pp_ifdef EINVAL@@
		result = libc_seterrno(EINVAL);
@@pp_else@@
		result = libc_seterrno(1);
@@pp_endif@@
	} else {
		result = ioctl(fd, __TIOCSCTTY, NULL);
	}
	return result;
}
%#endif /* __USE_BSD */

%
%#ifdef __USE_MISC
@@>> cfsetspeed(3)
[[decl_include("<bits/os/termios.h>", "<bits/types.h>")]]
int cfsetspeed([[nonnull]] struct termios *__restrict termios_p, speed_t speed) {
	termios_p->@c_ospeed@ = speed;
	termios_p->@c_ispeed@ = speed;
	return 0;
}

@@>> cfmakeraw(3)
@@Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
@@This entails the CANON and all control characters being disabled, as well as
@@any sort of input/output text processing no longer taking place.
[[impl_include("<asm/os/termios.h>"), decl_include("<bits/os/termios.h>")]]
void cfmakeraw([[nonnull]] struct termios *__restrict termios_p) {
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
	local head = "termios_p->@{}@ {}(" .format({ field, add ? "|= " : "&= ~" });
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
@@pp_if defined(__IGNBRK) || defined(__BRKINT) || defined(__PARMRK) || defined(__ISTRIP) || defined(__INLCR) || defined(__IGNCR) || defined(__ICRNL) || defined(__IXON) || defined(__IXOFF)@@
	termios_p->@c_iflag@ &= ~(0
@@pp_ifdef __IGNBRK@@
	                          | __IGNBRK
@@pp_endif@@
@@pp_ifdef __BRKINT@@
	                          | __BRKINT
@@pp_endif@@
@@pp_ifdef __PARMRK@@
	                          | __PARMRK
@@pp_endif@@
@@pp_ifdef __ISTRIP@@
	                          | __ISTRIP
@@pp_endif@@
@@pp_ifdef __INLCR@@
	                          | __INLCR
@@pp_endif@@
@@pp_ifdef __IGNCR@@
	                          | __IGNCR
@@pp_endif@@
@@pp_ifdef __ICRNL@@
	                          | __ICRNL
@@pp_endif@@
@@pp_ifdef __IXON@@
	                          | __IXON
@@pp_endif@@
@@pp_ifdef __IXOFF@@
	                          | __IXOFF
@@pp_endif@@
	                          );
@@pp_endif@@

	/* c_oflag (remove) */
@@pp_if defined(__OPOST)@@
	termios_p->@c_oflag@ &= ~(0
@@pp_ifdef __OPOST@@
	                          | __OPOST
@@pp_endif@@
	                          );
@@pp_endif@@

	/* c_lflag (remove) */
@@pp_if defined(__ECHO) || defined(__ECHONL) || defined(__ICANON) || defined(__ISIG) || defined(__IEXTEN)@@
	termios_p->@c_lflag@ &= ~(0
@@pp_ifdef __ECHO@@
	                          | __ECHO
@@pp_endif@@
@@pp_ifdef __ECHONL@@
	                          | __ECHONL
@@pp_endif@@
@@pp_ifdef __ICANON@@
	                          | __ICANON
@@pp_endif@@
@@pp_ifdef __ISIG@@
	                          | __ISIG
@@pp_endif@@
@@pp_ifdef __IEXTEN@@
	                          | __IEXTEN
@@pp_endif@@
	                          );
@@pp_endif@@

	/* c_cflag (remove) */
@@pp_if defined(__CSIZE) || defined(__PARENB)@@
	termios_p->@c_cflag@ &= ~(0
@@pp_ifdef __CSIZE@@
	                          | __CSIZE
@@pp_endif@@
@@pp_ifdef __PARENB@@
	                          | __PARENB
@@pp_endif@@
	                          );
@@pp_endif@@

	/* c_cflag (addend) */
@@pp_if defined(__CS8) || defined(__CREAD)@@
	termios_p->@c_cflag@ |= (0
@@pp_ifdef __CS8@@
	                         | __CS8
@@pp_endif@@
@@pp_ifdef __CREAD@@
	                         | __CREAD
@@pp_endif@@
	                         );
@@pp_endif@@
/*[[[end]]]*/

	/* c_cc[VMIN] */
@@pp_ifdef __VMIN@@
@@pp_ifdef __CMIN@@
	termios_p->@c_cc@[__VMIN] = __CMIN;
@@pp_else@@
	termios_p->@c_cc@[__VMIN] = 1; /* Read returns when one byte was read. */
@@pp_endif@@
@@pp_endif@@

	/* c_cc[VTIME] */
@@pp_ifdef __VTIME@@
@@pp_ifdef __CTIME@@
	termios_p->@c_cc@[__VTIME] = __CTIME;
@@pp_else@@
	termios_p->@c_cc@[__VTIME] = 0;
@@pp_endif@@
@@pp_endif@@
}
%#endif /* __USE_MISC */

%
%#if defined(__USE_KOS) || defined(__USE_BSD)
@@>> cfmakesane(3)
@@Set ~sane~ mode for the given `termios_p' (out-only; meaning that `termios_p' gets initialized by this function)
@@Sane here  refers  to  setting  all values  to  their  defaults,  as they  are  defined  in  <sys/ttydefaults.h>
[[kernel, impl_include("<bits/posix_opt.h>")]]
[[impl_include("<asm/os/termios.h>"), decl_include("<bits/os/termios.h>")]]
void cfmakesane([[nonnull]] struct termios *__restrict termios_p) {
	/* Default everything to ZERO */
	bzero(termios_p, sizeof(*termios_p));

	/* Set sane flag values. */
@@pp_if defined(__TTYDEF_CFLAG) && __TTYDEF_CFLAG != 0@@
	termios_p->@c_cflag@  = @__TTYDEF_CFLAG@;
@@pp_endif@@
@@pp_if defined(__TTYDEF_IFLAG) && __TTYDEF_IFLAG != 0@@
	termios_p->@c_iflag@  = @__TTYDEF_IFLAG@;
@@pp_endif@@
@@pp_if defined(__TTYDEF_LFLAG) && __TTYDEF_LFLAG != 0@@
	termios_p->@c_lflag@  = @__TTYDEF_LFLAG@;
@@pp_endif@@
@@pp_if defined(__TTYDEF_OFLAG) && __TTYDEF_OFLAG != 0@@
	termios_p->@c_oflag@  = @__TTYDEF_OFLAG@;
@@pp_endif@@
@@pp_if defined(__TTYDEF_SPEED) && __TTYDEF_SPEED != 0@@
	termios_p->@c_ispeed@ = @__TTYDEF_SPEED@;
@@pp_endif@@
@@pp_if defined(__TTYDEF_SPEED) && __TTYDEF_SPEED != 0@@
	termios_p->@c_ospeed@ = @__TTYDEF_SPEED@;
@@pp_endif@@

	/* ^C: Send SIGINT to the foreground process (requires `ISIG') */
@@pp_ifdef __VINTR@@
@@pp_ifdef __CINTR@@
	termios_p->@c_cc@[__VINTR] = __CINTR;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VINTR] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ^\: Send SIGQUIT to the foreground process (requires `ISIG') */
@@pp_ifdef __VQUIT@@
@@pp_ifdef __CQUIT@@
	termios_p->@c_cc@[__VQUIT] = __CQUIT;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VQUIT] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ^H (aka. \b): Erase the last character from the input canon (requires `ECHOE') */
@@pp_ifdef __VERASE@@
@@pp_ifdef __CERASE@@
	termios_p->@c_cc@[__VERASE] = __CERASE;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VERASE] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ^U: Clear the entire input canon (requires `ECHOK') */
@@pp_ifdef __VKILL@@
@@pp_ifdef __CKILL@@
	termios_p->@c_cc@[__VKILL] = __CKILL;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VKILL] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ^D: Cause read(2) from the TTY to return 0 once (thus indicating input EOF) */
@@pp_ifdef __VEOF@@
@@pp_ifdef __CEOF@@
	termios_p->@c_cc@[__VEOF] = __CEOF;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VEOF] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ... */
@@pp_ifdef __VTIME@@
@@pp_ifdef __CTIME@@
	termios_p->@c_cc@[__VTIME] = __CTIME;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VTIME] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* Minimum number of input bytes to-be returned by read(2) from the TTY */
@@pp_ifdef __VMIN@@
@@pp_ifdef __CMIN@@
	termios_p->@c_cc@[__VMIN] = __CMIN;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VMIN] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ... */
@@pp_ifdef __VSWTCH@@
@@pp_ifdef __CSWTCH@@
	termios_p->@c_cc@[__VSWTCH] = __CSWTCH;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VSWTCH] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ^Q: Restart stopped output (After VSTOP; causes pending TTY output to be flushed) */
@@pp_ifdef __VSTART@@
@@pp_ifdef __CSTART@@
	termios_p->@c_cc@[__VSTART] = __CSTART;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VSTART] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ^S: Suspend TTY display output until `VSTART' */
@@pp_ifdef __VSTOP@@
@@pp_ifdef __CSTOP@@
	termios_p->@c_cc@[__VSTOP] = __CSTOP;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VSTOP] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ^Z: Send SIGTSTP to the foreground process (requires `ISIG') */
@@pp_ifdef __VSUSP@@
@@pp_ifdef __CSUSP@@
	termios_p->@c_cc@[__VSUSP] = __CSUSP;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VSUSP] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* \0: An additional end-of-line character used to flush the canon (by default, only \n is recognized) */
@@pp_ifdef __VEOL@@
@@pp_ifdef __CEOL@@
	termios_p->@c_cc@[__VEOL] = __CEOL;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VEOL] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ^R: Re-echo the current contents of the input canon (requires `IEXTEN') */
@@pp_ifdef __VREPRINT@@
@@pp_ifdef __CREPRINT@@
	termios_p->@c_cc@[__VREPRINT] = __CREPRINT;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VREPRINT] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* <UNSUPPORTED> */
@@pp_ifdef __VDISCARD@@
@@pp_ifdef __CDISCARD@@
	termios_p->@c_cc@[__VDISCARD] = __CDISCARD;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VDISCARD] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ^W: Erase the last-written word (while (isspace(last)) erase(); while (!isspace(last)) erase()) (Requires `ECHOE' and `IEXTEN') */
@@pp_ifdef __VWERASE@@
@@pp_ifdef __CWERASE@@
	termios_p->@c_cc@[__VWERASE] = __CWERASE;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VWERASE] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ^V: The next input character is escaped, in that any special meaning it would normally have is dismissed */
@@pp_ifdef __VLNEXT@@
@@pp_ifdef __CLNEXT@@
	termios_p->@c_cc@[__VLNEXT] = __CLNEXT;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VLNEXT] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* \0: An additional end-of-line character used to flush the canon (by default, only \n is recognized) */
@@pp_ifdef __VEOL2@@
@@pp_ifdef __CEOL2@@
	termios_p->@c_cc@[__VEOL2] = __CEOL2;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VEOL2] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ... */
@@pp_ifdef __VDSUSP@@
@@pp_ifdef __CDSUSP@@
	termios_p->@c_cc@[__VDSUSP] = __CDSUSP;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VDSUSP] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@

	/* ... */
@@pp_ifdef __VSTATUS@@
@@pp_ifdef __CSTATUS@@
	termios_p->@c_cc@[__VSTATUS] = __CSTATUS;
@@pp_elif __VDISABLE != 0@@
	termios_p->@c_cc@[__VSTATUS] = __VDISABLE;
@@pp_endif@@
@@pp_endif@@
}
%#endif /* __USE_KOS || __USE_BSD */


%{

__SYSDECL_END
}
%#endif /* __CC__ */
%{

#if defined(__USE_MISC) || defined(__USE_BSD)
#define CCEQ(val, c) ((c) == (val) && (val) != _POSIX_VDISABLE)
#endif /* __USE_MISC || __USE_BSD */

}
