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
/* (#) Portability: Linux (/usr/include/[...]/asm/termbits.h) */
#ifndef _ASM_TERMBITS_H
#define _ASM_TERMBITS_H 1

#include <__stdinc.h>

#include <asm/os/termios.h>
#include <bits/os/termios.h>

#define ktermios termios2 /* Alias */

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
/* vvv Typo??? -- In <termios.h>, this one's defined as `VSWTCH' */
#if !defined(VSWTC) && defined(__VSWTCH)
#define VSWTC    __VSWTCH   /* ... */
#endif /* !VSWTC && __VSWTCH */

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
#if !defined(VTDLY) && defined(__VTDLY)
#define VTDLY       __VTDLY  /* ??? */
#endif /* !VTDLY && __VTDLY */
#if !defined(VT0) && defined(__VT0)
#define   VT0       __VT0    /* ??? */
#endif /* !VT0 && __VT0 */
#if !defined(VT1) && defined(__VT1)
#define   VT1       __VT1    /* ??? */
#endif /* !VT1 && __VT1 */
#if !defined(XTABS) && defined(__XTABS)
#define XTABS       __XTABS  /* ??? */
#endif /* !XTABS && __XTABS */


/* c_cflag bit meaning */
#if !defined(CBAUD) && defined(__CBAU)
#define CBAUD     __CBAUD
#endif /* !CBAUD && __CBAU */
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
#if !defined(EXTA) && defined(__EXTA)
#define EXTA      __EXTA
#endif /* !EXTA && __EXTA */
#if !defined(EXTB) && defined(__EXTB)
#define EXTB      __EXTB
#endif /* !EXTB && __EXTB */
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
#if !defined(CBAUDEX) && defined(__CBAUDEX)
#define CBAUDEX   __CBAUDEX
#endif /* !CBAUDEX && __CBAUDEX */
#if !defined(BOTHER) && defined(__BOTHER)
#define BOTHER    __BOTHER
#endif /* !BOTHER && __BOTHER */
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
#if !defined(CIBAUD) && defined(__CIBAUD)
#define CIBAUD    __CIBAUD /* input baud rate (not used) */
#endif /* !CIBAUD && __CIBAUD */
#if !defined(CMSPAR) && defined(__CMSPAR)
#define CMSPAR    __CMSPAR /* mark or space (stick) parity */
#endif /* !CMSPAR && __CMSPAR */
#if !defined(CRTSCTS) && defined(__CRTSCTS)
#define CRTSCTS   __CRTSCTS /* flow control */
#endif /* !CRTSCTS && __CRTSCTS */
#if !defined(IBSHIFT) && defined(__IBSHIFT)
#define IBSHIFT   __IBSHIFT /* Bit-shift to convert from `CBAUD' to `CIBAUD' */
#endif /* !IBSHIFT && __IBSHIFT */

/* c_lflag bits */
#if !defined(ISIG) && defined(__ISIG)
#define ISIG        __ISIG    /* When any of the characters INTR, QUIT, SUSP, or DSUSP are received, generate the corresponding signal. */
#endif /* !ISIG && __ISIG */
#if !defined(ICANON) && defined(__ICANON)
#define ICANON      __ICANON  /* Enable canonical mode */
#endif /* !ICANON && __ICANON */
#if !defined(XCASE) && defined(__XCASE)
#define XCASE       __XCASE   /* If ICANON is also set, terminal is uppercase only. Input is converted to lowercase,
                               * except for characters preceded by \.  On output, uppercase characters are  preceded
                               * by \ and lowercase characters are converted to uppercase. */
#endif /* !XCASE && __XCASE */
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
#if !defined(IEXTEN) && defined(__IEXTEN)
#define IEXTEN      __IEXTEN  /* Enable implementation-defined input processing. This flag, as
                               * well  as ICANON  must be  enabled for  the special characters
                               * EOL2, LNEXT, REPRINT, WERASE to  be interpreted, and for  the
                               * IUCLC flag to be effective */
#endif /* !IEXTEN && __IEXTEN */
#if !defined(EXTPROC) && defined(__EXTPROC)
#define EXTPROC     __EXTPROC /* Skip handling of: `PARMRK', `ECHO' and `IXON'+`IXANY', as well as `c_cc[*]' */
#endif /* !EXTPROC && __EXTPROC */

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

#endif /* !_ASM_TERMBITS_H */
