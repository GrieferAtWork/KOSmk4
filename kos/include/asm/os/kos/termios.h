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
/*!replace_with_include <asm/os/termios.h>*/
#ifndef _ASM_OS_KOS_TERMIOS_H
#define _ASM_OS_KOS_TERMIOS_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

/* Sources for comments:
 *   - http://man7.org/linux/man-pages/man3/tcflow.3.html
 *   - https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_node/libc_355.html
 *   - Came up with them myself, or altered them significantly. */


/* c_cc characters */
#define __VINTR    0  /* ^C: Send SIGINT to the foreground process (requires `ISIG') */
#define __VQUIT    1  /* ^\: Send SIGQUIT to the foreground process (requires `ISIG') */
#define __VERASE   2  /* ^H (aka. \b): Erase the last character from the input canon (requires `ECHOE') */
#define __VKILL    3  /* ^U: Clear the entire input canon (requires `ECHOK') */
#define __VEOF     4  /* ^D: Cause read(2) from the TTY to return 0 once (thus indicating input EOF) */
#define __VTIME    5  /* ... */
#define __VMIN     6  /* Minimum number of input bytes to-be returned by read(2) from the TTY */
#define __VSWTCH   7  /* ... */
#define __VSTART   8  /* ^Q: Restart stopped output (After VSTOP; causes pending TTY output to be flushed) */
#define __VSTOP    9  /* ^S: Suspend TTY display output until `VSTART' */
#define __VSUSP    10 /* ^Z: Send SIGTSTP to the foreground process (requires `ISIG') */
#define __VEOL     11 /* \0: An additional end-of-line character used to flush the canon (by default, only \n is recognized) */
#define __VREPRINT 12 /* ^R: Re-echo the current contents of the input canon (requires `IEXTEN') */
#define __VDISCARD 13 /* <UNSUPPORTED> */
#define __VWERASE  14 /* ^W: Erase the last-written word (while (isspace(last)) erase(); while (!isspace(last)) erase()) (Requires `ECHOE' and `IEXTEN') */
#define __VLNEXT   15 /* ^V: The next input character is escaped, in that any special meaning it would normally have is dismissed */
#define __VEOL2    16 /* \0: An additional end-of-line character used to flush the canon (by default, only \n is recognized) */

/* c_iflag bits */
#define __IGNBRK   __UINT32_C(0x00000001) /* break? */
#define __BRKINT   __UINT32_C(0x00000002) /* break? */
#define __IGNPAR   __UINT32_C(0x00000004) /* Ignore framing errors and parity errors. */
#define __PARMRK   __UINT32_C(0x00000008) /* Encode faulty bytes as `\377\0\...' - `\377' is encoded as `\377\377' */
#define __INPCK    __UINT32_C(0x00000010) /* Enable input parity checking. */
#define __ISTRIP   __UINT32_C(0x00000020) /* Clear the eighth bit. */
#define __INLCR    __UINT32_C(0x00000040) /* Translate NL to CR on input. */
#define __IGNCR    __UINT32_C(0x00000080) /* Ignore carriage return on input. */
#define __ICRNL    __UINT32_C(0x00000100) /* Translate carriage return to newline on input (unless IGNCR is set). */
#define __IUCLC    __UINT32_C(0x00000200) /* Map uppercase characters to lowercase on input (requires `IEXTEN'). */
#define __IXON     __UINT32_C(0x00000400) /* Enable support for `VSTOP' to disable TTY output transmission. */
#define __IXANY    __UINT32_C(0x00000800) /* Any input character has the behavior of `VSTART' */
#define __IXOFF    __UINT32_C(0x00001000) /* Status bit for `VSTOP' / `VSTART': Don't transmit pending  TTY output until this bit is cleared. When  set,
                                           * tty output is instead stored in a secondary buffer (s.a. `TTYIO_OPEND_GETLIMIT' and `TTYIO_OPEND_SETLIMIT') */
#define __IMAXBEL  __UINT32_C(0x00002000) /* Ring bell when input queue is full (KOS-SPECIFIC: The bell also gets triggered when the queue is empty and a delete character is received) */
#define __IUTF8    __UINT32_C(0x00004000) /* Input is UTF8 */
/*      __I        __UINT32_C(0x00008000)  * ... */
/*      __I        __UINT32_C(0x00010000)  * ... */
/*      __I        __UINT32_C(0x00020000)  * ... */
/*      __I        __UINT32_C(0x00040000)  * ... */
/*      __I        __UINT32_C(0x00080000)  * ... */
#define __IIOFF    __UINT32_C(0x00100000) /* Status bit for `TCIOFF' / `TCION': When set, redirect input to a secondary buffer. (s.a. `TTYIO_IPEND_GETLIMIT' and `TTYIO_IPEND_SETLIMIT') */
/*      __I        __UINT32_C(0x00200000)  * ... */
/*      __I        __UINT32_C(0x00400000)  * ... */
/*      __I        __UINT32_C(0x00800000)  * ... */
/*      __I        __UINT32_C(0x01000000)  * ... */
/*      __I        __UINT32_C(0x02000000)  * ... */
/*      __I        __UINT32_C(0x04000000)  * ... */
/*      __I        __UINT32_C(0x08000000)  * ... */
/*      __I        __UINT32_C(0x10000000)  * ... */
/*      __I        __UINT32_C(0x20000000)  * ... */
/*      __I        __UINT32_C(0x40000000)  * ... */
#define __IBAUD0   __UINT32_C(0x80000000) /* Hack used by `cfsetispeed(3)' */

/* c_oflag bits */
#define __OPOST    __UINT32_C(0x00000001) /* Enable implementation-defined output processing */
#define __OLCUC    __UINT32_C(0x00000002) /* Map lowercase characters to uppercase on output. */
#define __ONLCR    __UINT32_C(0x00000004) /* Map NL to CR-NL on output. */
#define __OCRNL    __UINT32_C(0x00000008) /* Map CR to NL on output. (Ignored when `ONLRET' is set) (When combined with `ONLCR', output CR as CRNL) */
#define __ONOCR    __UINT32_C(0x00000010) /* Don't output CR at column 0. */
#define __ONLRET   __UINT32_C(0x00000020) /* Don't output CR. */
#define __OFILL    __UINT32_C(0x00000040) /* ??? */
#define __OFDEL    __UINT32_C(0x00000080) /* ??? */
#define __NLDLY    __UINT32_C(0x00000100) /* ??? */
#define   __NL0    __UINT32_C(0x00000000) /* ??? */
#define   __NL1    __UINT32_C(0x00000100) /* ??? */
#define __CRDLY    __UINT32_C(0x00000600) /* ??? */
#define   __CR0    __UINT32_C(0x00000000) /* ??? */
#define   __CR1    __UINT32_C(0x00000200) /* ??? */
#define   __CR2    __UINT32_C(0x00000400) /* ??? */
#define   __CR3    __UINT32_C(0x00000600) /* ??? */
#define __TABDLY   __UINT32_C(0x00001800) /* ??? */
#define   __TAB0   __UINT32_C(0x00000000) /* ??? */
#define   __TAB1   __UINT32_C(0x00000800) /* ??? */
#define   __TAB2   __UINT32_C(0x00001000) /* ??? */
#define   __TAB3   __UINT32_C(0x00001800) /* ??? */
#define __BSDLY    __UINT32_C(0x00002000) /* ??? */
#define   __BS0    __UINT32_C(0x00000000) /* ??? */
#define   __BS1    __UINT32_C(0x00002000) /* ??? */
#define __FFDLY    __UINT32_C(0x00008000) /* ??? */
#define   __FF0    __UINT32_C(0x00000000) /* ??? */
#define   __FF1    __UINT32_C(0x00008000) /* ??? */
#define __VTDLY    __UINT32_C(0x00004000) /* ??? */
#define   __VT0    __UINT32_C(0x00000000) /* ??? */
#define   __VT1    __UINT32_C(0x00004000) /* ??? */
#define __XTABS    __UINT32_C(0x00001800) /* ??? */

/* c_cflag bit meaning */
#define __CBAUD    __UINT32_C(0x0000100f) /* ??? */
#define __B0       __UINT32_C(0x00000000) /* hang up */
#define __B50      __UINT32_C(0x00000001) /* ??? */
#define __B75      __UINT32_C(0x00000002) /* ??? */
#define __B110     __UINT32_C(0x00000003) /* ??? */
#define __B134     __UINT32_C(0x00000004) /* ??? */
#define __B150     __UINT32_C(0x00000005) /* ??? */
#define __B200     __UINT32_C(0x00000006) /* ??? */
#define __B300     __UINT32_C(0x00000007) /* ??? */
#define __B600     __UINT32_C(0x00000008) /* ??? */
#define __B1200    __UINT32_C(0x00000009) /* ??? */
#define __B1800    __UINT32_C(0x0000000a) /* ??? */
#define __B2400    __UINT32_C(0x0000000b) /* ??? */
#define __B4800    __UINT32_C(0x0000000c) /* ??? */
#define __B9600    __UINT32_C(0x0000000d) /* ??? */
#define __B19200   __UINT32_C(0x0000000e) /* ??? */
#define __B38400   __UINT32_C(0x0000000f) /* ??? */
#define __EXTA     __B19200               /* ??? */
#define __EXTB     __B38400               /* ??? */
#define __CSIZE    __UINT32_C(0x00000030) /* Mask for the character size (in bits) */
#define   __CS5    __UINT32_C(0x00000000) /* 5-bit characters */
#define   __CS6    __UINT32_C(0x00000010) /* 6-bit characters */
#define   __CS7    __UINT32_C(0x00000020) /* 7-bit characters */
#define   __CS8    __UINT32_C(0x00000030) /* 8-bit characters */
#define __CSTOPB   __UINT32_C(0x00000040) /* ??? */
#define __CREAD    __UINT32_C(0x00000080) /* ??? */
#define __PARENB   __UINT32_C(0x00000100) /* ??? */
#define __PARODD   __UINT32_C(0x00000200) /* ??? */
#define __HUPCL    __UINT32_C(0x00000400) /* ??? */
#define __CLOCAL   __UINT32_C(0x00000800) /* ??? */
#define __CBAUDEX  __UINT32_C(0x00001000) /* ??? */
#define __BOTHER   __UINT32_C(0x00001000) /* ??? */
#define __B57600   __UINT32_C(0x00001001) /* ??? */
#define __B115200  __UINT32_C(0x00001002) /* ??? */
#define __B230400  __UINT32_C(0x00001003) /* ??? */
#define __B460800  __UINT32_C(0x00001004) /* ??? */
#define __B500000  __UINT32_C(0x00001005) /* ??? */
#define __B576000  __UINT32_C(0x00001006) /* ??? */
#define __B921600  __UINT32_C(0x00001007) /* ??? */
#define __B1000000 __UINT32_C(0x00001008) /* ??? */
#define __B1152000 __UINT32_C(0x00001009) /* ??? */
#define __B1500000 __UINT32_C(0x0000100a) /* ??? */
#define __B2000000 __UINT32_C(0x0000100b) /* ??? */
#define __B2500000 __UINT32_C(0x0000100c) /* ??? */
#define __B3000000 __UINT32_C(0x0000100d) /* ??? */
#define __B3500000 __UINT32_C(0x0000100e) /* ??? */
#define __B4000000 __UINT32_C(0x0000100f) /* ??? */
#define __MAX_BAUD __B4000000             /* ??? */
#define __CIBAUD   __UINT32_C(0x100f0000) /* input baud rate (not used) */
/*                 __UINT32_C(0x00100000)  * ... */
/*                 __UINT32_C(0x00200000)  * ... */
/*                 __UINT32_C(0x00400000)  * ... */
/*                 __UINT32_C(0x00800000)  * ... */
/*                 __UINT32_C(0x01000000)  * ... */
/*                 __UINT32_C(0x02000000)  * ... */
/*                 __UINT32_C(0x04000000)  * ... */
/*                 __UINT32_C(0x08000000)  * ... */
/*                 __UINT32_C(0x20000000)  * ... */
#define __CMSPAR   __UINT32_C(0x40000000) /* mark or space (stick) parity */
#define __CRTSCTS  __UINT32_C(0x80000000) /* flow control */
#define __IBSHIFT  16                     /* Bit-shift to convert from `CBAUD' to `CIBAUD' */

/* c_lflag bits */
#define __ISIG      __UINT32_C(0x00000001) /* When any of the characters INTR, QUIT, SUSP, or DSUSP are received, generate the corresponding signal. */
#define __ICANON    __UINT32_C(0x00000002) /* Enable canonical mode */
#define __XCASE     __UINT32_C(0x00000004) /* If ICANON is also set, terminal is uppercase only. Input is converted to lowercase,
                                            * except for characters preceded by \.  On output, uppercase characters are  preceded
                                            * by \ and lowercase characters are converted to uppercase. */
#define __ECHO      __UINT32_C(0x00000008) /* Echo input characters */
#define __ECHOE     __UINT32_C(0x00000010) /* If ICANON is also set, the VERASE character erases the preceding input character, and VWERASE erases the preceding word */
#define __ECHOK     __UINT32_C(0x00000020) /* If ICANON is also set, the VKILL character erases the current line */
#define __ECHONL    __UINT32_C(0x00000040) /* If   ICANON  is  also  set,  echo  the  NL  character  even  if  ECHO  is  not  set
                                            * NOTE: for this purpose, the NL character(s) recognized are '\n', `VEOL' and `VEOL2' */
#define __NOFLSH    __UINT32_C(0x00000080) /* Disable flushing the input and output queues when generating signals for the INT, QUIT, and SUSP characters */
#define __TOSTOP    __UINT32_C(0x00000100) /* Send the SIGTTOU signal to the process group of a background process which tries to write to its controlling terminal */
#define __ECHOCTL   __UINT32_C(0x00000200) /* If ECHO is also set, terminal special characters other than TAB(\t), NL(\n),
                                            * START,  and STOP are echoed as ^X, where  X is the character with ASCII code
                                            * 0x40  greater than the  special character. For  example, character 0x08 (BS)
                                            * is echoed as ^H */
#define __ECHOPRT   __UINT32_C(0x00000400) /* This bit is like ECHOE, enables display of the ERASE character in a way that
                                            * is geared to a hardcopy terminal. When  you type the ERASE character, a  `\'
                                            * character is  printed followed  by the  first character  erased. Typing  the
                                            * ERASE  character  again just  prints the  next  character erased.  Then, the
                                            * next  time  you  type  a  normal  character,  a  `/'  character  is  printed
                                            * before the character echoes. */
#define __ECHOKE    __UINT32_C(0x00000800) /* If ICANON is also set, KILL is echoed by erasing each character on the line, as specified by ECHOE and ECHOPRT */
#define __FLUSHO    __UINT32_C(0x00001000) /* Output is being flushed. This flag is toggled by typing the DISCARD character */
/*      __          __UINT32_C(0x00002000)  * ... */
#define __PENDIN    __UINT32_C(0x00004000) /* ??? */
#define __IEXTEN    __UINT32_C(0x00008000) /* Enable implementation-defined input processing. This flag, as
                                            * well  as ICANON  must be  enabled for  the special characters
                                            * EOL2, LNEXT, REPRINT, WERASE to  be interpreted, and for  the
                                            * IUCLC flag to be effective */
#define __EXTPROC   __UINT32_C(0x00010000) /* Skip handling of: `PARMRK', `ECHO' and `IXON'+`IXANY', as well as `c_cc[*]' */
/*      __          __UINT32_C(0x00020000)  * ... */
/*      __          __UINT32_C(0x00040000)  * ... */
/*      __          __UINT32_C(0x00080000)  * ... */
#define __IERASING  __UINT32_C(0x00100000) /* Status bit for `ECHOPRT' */
#define __IXCASEING __UINT32_C(0x00200000) /* Status bit for `XCASE' (the previous character was \) */
#define __IEOFING   __UINT32_C(0x00400000) /* Status bit for a pending `VEOF' character
                                            * When  set,  the next  time input  is attempted  to be  read from  the TTY,
                                            * and the operation would have blocked, read(2) instead returns immediately,
                                            * thus  indicating an  END-OF-FILE within  the TTY.  (shell programs usually
                                            * interpret this as the user wishing to logout) */
#define __IESCAPING __UINT32_C(0x00800000) /* Status bit for `VLNEXT': The next input character is escaped. */
/*      __          __UINT32_C(0x01000000)  * ... */
/*      __          __UINT32_C(0x02000000)  * ... */
/*      __          __UINT32_C(0x04000000)  * ... */
/*      __          __UINT32_C(0x08000000)  * ... */
/*      __          __UINT32_C(0x10000000)  * ... */
/*      __          __UINT32_C(0x20000000)  * ... */
/*      __          __UINT32_C(0x40000000)  * ... */
/*      __          __UINT32_C(0x80000000)  * ... */

/* tcflow() and TCXONC use these */
#define __TCOOFF 0 /* Suspends output. */
#define __TCOON  1 /* Restarts suspended output. */
#define __TCIOFF 2 /* Suspends input. */
#define __TCION  3 /* Restarts suspended input. */

/* tcflush() and TCFLSH use these */
#define __TCIFLUSH  0
#define __TCOFLUSH  1
#define __TCIOFLUSH 2

/* tcsetattr uses these */
#define __TCSANOW   0 /* Set terminal attributes (s.a. `TCSETA') */
#define __TCSADRAIN 1 /* Wait for all unwritten data to be transmitted, discard all unread data, then set terminal attributes (s.a. `TCSETAW') */
#define __TCSAFLUSH 2 /* Wait for all unwritten data to be transmitted, then set terminal attributes (s.a. `TCSETAF') */

#endif /* !_ASM_OS_KOS_TERMIOS_H */
