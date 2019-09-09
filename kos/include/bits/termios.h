/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_TERMIOS_H
#define _BITS_TERMIOS_H 1

#include <__stdinc.h>

/* termios type and macro definitions.  Linux version.
   Copyright (C) 1993-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__SYSDECL_BEGIN

#ifdef __CC__
typedef __UINT8_TYPE__  cc_t;
typedef __UINT32_TYPE__ speed_t;
typedef __UINT32_TYPE__ tcflag_t;
#endif /* __CC__ */

#define NCCS 32
#ifdef __CC__
struct termios {
	tcflag_t c_iflag;    /* input mode flags. */
	tcflag_t c_oflag;    /* output mode flags. */
	tcflag_t c_cflag;    /* control mode flags. */
	tcflag_t c_lflag;    /* local mode flags. */
	cc_t     c_line;     /* line discipline. */
	cc_t     c_cc[NCCS]; /* control characters. */
	speed_t  c_ispeed;   /* input speed. */
	speed_t  c_ospeed;   /* output speed. */
};
struct termios2 {
	tcflag_t c_iflag;    /* input mode flags. */
	tcflag_t c_oflag;    /* output mode flags. */
	tcflag_t c_cflag;    /* control mode flags. */
	tcflag_t c_lflag;    /* local mode flags. */
	cc_t     c_line;     /* line discipline. */
	cc_t     c_cc[19];   /* control characters. */
	speed_t  c_ispeed;   /* input speed. */
	speed_t  c_ospeed;   /* output speed. */
};
#endif /* __CC__ */
#define _HAVE_STRUCT_TERMIOS_C_ISPEED 1
#define _HAVE_STRUCT_TERMIOS_C_OSPEED 1

/* NOTE: Some of the comments are taken from here:
 *   http://man7.org/linux/man-pages/man3/tcflow.3.html
 *   https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_node/libc_355.html
 */


/* c_cc characters */
#define VINTR    0  /* ^C: Send SIGINT to the foreground process (requires `ISIG') */
#define VQUIT    1  /* ^\: Send SIGQUIT to the foreground process (requires `ISIG') */
#define VERASE   2  /* \b: Erase the last character from the input canon (requires `ECHOE') */
#define VKILL    3  /* ^U: Clear the entire input canon (requires `ECHOK') */
#define VEOF     4  /* ^D: Cause read(2) from the TTY to return 0 once (thus indicating input EOF) */
#define VTIME    5  /* ... */
#define VMIN     6  /* Minimum number of input bytes to-be returned by read(2) from the TTY */
#define VSWTCH   7  /* ... */
#define VSTART   8  /* ^Q: Restart stopped output (After VSTOP; causes pending TTY output to be flushed) */
#define VSTOP    9  /* ^S: Suspend TTY display output until `VSTART' */
#define VSUSP    10 /* ^Z: Send SIGTSTP to the foreground process (requires `ISIG') */
#define VEOL     11 /* \0: An additional end-of-line character used to flush the canon (by default, only \n is recognized) */
#define VREPRINT 12 /* ^R: Re-echo the current contents of the input canon (requires `IEXTEN') */
#define VDISCARD 13 /* <UNSUPPORTED> */
#define VWERASE  14 /* ^W: Erase the last-written word (while (isspace(last)) erase(); while (!isspace(last)) erase()) (Requires `ECHOE' and `IEXTEN') */
#define VLNEXT   15 /* ^V: The next input character is escaped, in that any special meaning it would normally have is dismissed */
#define VEOL2    16 /* \0: An additional end-of-line character used to flush the canon (by default, only \n is recognized) */

/* c_iflag bits */
#define IGNBRK   0000001 /* break? */
#define BRKINT   0000002 /* break? */
#define IGNPAR   0000004 /* Ignore framing errors and parity errors. */
#define PARMRK   0000010 /* Encode faulty bytes as `\377\0\...' - `\377' is encoded as `\377\377' */
#define INPCK    0000020 /* Enable input parity checking. */
#define ISTRIP   0000040 /* Clear the eighth bit. */
#define INLCR    0000100 /* Translate NL to CR on input. */
#define IGNCR    0000200 /* Ignore carriage return on input. */
#define ICRNL    0000400 /* Translate carriage return to newline on input (unless IGNCR is set). */
#define IUCLC    0001000 /* Map uppercase characters to lowercase on input (requires `IEXTEN'). */
#define IXON     0002000 /* Enable support for `VSTOP' to disable TTY output transmission. */
#define IXANY    0004000 /* Any input character has the behavior of `VSTART' */
#define IXOFF    0010000 /* Status bit for `VSTOP' / `VSTART': Don't transmit pending TTY output until this bit is cleared. */
#define IMAXBEL  0020000 /* Ring bell when input queue is full (KOS-SPECIFIC: The bell also gets triggered when is empty, and a delete character is received) */
#define IUTF8    0040000 /* Input is UTF8 */
#define __IIOFF 04000000 /* Status bit for `TCIOFF' / `TCION': When set, disable enqueuing of new input. */

/* c_oflag bits */
#define OPOST       0000001 /* Enable implementation-defined output processing */
#define OLCUC       0000002 /* Map lowercase characters to uppercase on output. */
#define ONLCR       0000004 /* Map NL to CR-NL on output. */
#define OCRNL       0000010 /* Map CR to NL on output. (Ignored when `ONLRET' is set) (When combined with `ONLCR', output CR as CRNL) */
#define ONOCR       0000020 /* Don't output CR at column 0. */
#define ONLRET      0000040 /* Don't output CR. */
#define OFILL       0000100 /* ??? */
#define OFDEL       0000200 /* ??? */
#if defined(__USE_MISC) || defined(__USE_XOPEN)
#   define NLDLY    0000400 /* ??? */
#   define   NL0    0000000 /* ??? */
#   define   NL1    0000400 /* ??? */
#   define CRDLY    0003000 /* ??? */
#   define   CR0    0000000 /* ??? */
#   define   CR1    0001000 /* ??? */
#   define   CR2    0002000 /* ??? */
#   define   CR3    0003000 /* ??? */
#   define TABDLY   0014000 /* ??? */
#   define   TAB0   0000000 /* ??? */
#   define   TAB1   0004000 /* ??? */
#   define   TAB2   0010000 /* ??? */
#   define   TAB3   0014000 /* ??? */
#   define BSDLY    0020000 /* ??? */
#   define   BS0    0000000 /* ??? */
#   define   BS1    0020000 /* ??? */
#   define FFDLY    0100000 /* ??? */
#   define   FF0    0000000 /* ??? */
#   define   FF1    0100000 /* ??? */
#endif
#define VTDLY       0040000 /* ??? */
#define   VT0       0000000 /* ??? */
#define   VT1       0040000 /* ??? */
#ifdef __USE_MISC
#   define XTABS    0014000 /* ??? */
#endif

/* c_cflag bit meaning */
#ifdef __USE_MISC
#   define CBAUD    0010017
#endif
#define B0        0000000 /* hang up */
#define B50       0000001
#define B75       0000002
#define B110      0000003
#define B134      0000004
#define B150      0000005
#define B200      0000006
#define B300      0000007
#define B600      0000010
#define B1200     0000011
#define B1800     0000012
#define B2400     0000013
#define B4800     0000014
#define B9600     0000015
#define B19200    0000016
#define B38400    0000017
#ifdef __USE_MISC
#   define EXTA   B19200
#   define EXTB   B38400
#endif
#define CSIZE     0000060
#define   CS5     0000000
#define   CS6     0000020
#define   CS7     0000040
#define   CS8     0000060
#define CSTOPB    0000100
#define CREAD     0000200
#define PARENB    0000400
#define PARODD    0001000
#define HUPCL     0002000
#define CLOCAL    0004000
#ifdef __USE_MISC
#   define CBAUDEX 0010000
#endif
#define B57600    0010001
#define B115200   0010002
#define B230400   0010003
#define B460800   0010004
#define B500000   0010005
#define B576000   0010006
#define B921600   0010007
#define B1000000  0010010
#define B1152000  0010011
#define B1500000  0010012
#define B2000000  0010013
#define B2500000  0010014
#define B3000000  0010015
#define B3500000  0010016
#define B4000000  0010017
#define __MAX_BAUD B4000000
#ifdef __USE_MISC
#   define CIBAUD  002003600000 /* input baud rate (not used) */
#   define CMSPAR  010000000000 /* mark or space (stick) parity */
#   define CRTSCTS 020000000000 /* flow control */
#endif

/* c_lflag bits */
#define ISIG        0000001 /* When any of the characters INTR, QUIT, SUSP, or DSUSP are received, generate the corresponding signal. */
#define ICANON      0000002 /* Enable canonical mode */
#if defined(__USE_MISC) || defined(__USE_XOPEN)
#   define XCASE    0000004 /* If ICANON is also set, terminal is uppercase only. Input is converted to lowercase,
                             * except for characters preceded by \. On output, uppercase characters are preceded
                             * by \ and lowercase characters are converted to uppercase. */
#endif
#define ECHO        0000010 /* Echo input characters */
#define ECHOE       0000020 /* If ICANON is also set, the VERASE character erases the preceding input character, and VWERASE erases the preceding word */
#define ECHOK       0000040 /* If ICANON is also set, the VKILL character erases the current line */
#define ECHONL      0000100 /* If ICANON is also set, echo the NL character even if ECHO is not set
                             * NOTE: for this purpose, the NL character(s) recognized are '\n', `VEOL' and `VEOL2' */
#define NOFLSH      0000200 /* Disable flushing the input and output queues when generating signals for the INT, QUIT, and SUSP characters */
#define TOSTOP      0000400 /* Send the SIGTTOU signal to the process group of a background process which tries to write to its controlling terminal */
#ifdef __USE_MISC
#define ECHOCTL     0001000 /* If ECHO is also set, terminal special characters other than TAB(\t), NL(\n),
                             * START, and STOP are echoed as ^X, where X is the character with ASCII code
                             * 0x40 greater than the special character. For example, character 0x08 (BS)
                             * is echoed as ^H */
#define ECHOPRT     0002000 /* This bit is like ECHOE, enables display of the ERASE character in a way that
                             * is geared to a hardcopy terminal. When you type the ERASE character, a `\'
                             * character is printed followed by the first character erased. Typing the
                             * ERASE character again just prints the next character erased. Then, the
                             * next time you type a normal character, a `/' character is printed
                             * before the character echoes. */
#define ECHOKE      0004000 /* If ICANON is also set, KILL is echoed by erasing each character on the line, as specified by ECHOE and ECHOPRT */
#define FLUSHO      0010000 /* Output is being flushed. This flag is toggled by typing the DISCARD character */
#define PENDIN      0040000 /* ??? */
#endif /* __USE_MISC */
#define IEXTEN      0100000 /* Enable implementation-defined input processing. This flag, as
                             * well as ICANON must be enabled for the special characters
                             * EOL2, LNEXT, REPRINT, WERASE to be interpreted, and for the
                             * IUCLC flag to be effective */
#ifdef __USE_MISC
#   define EXTPROC  0200000 /* ??? */
#endif
#define __IERASING        04000000 /* Status bit for `ECHOPRT' */
#define __IXCASEING      010000000 /* Status bit for `XCASE' */
#define __IEOFING        020000000 /* Status bit for a pending `VEOF' character
                                    * When set, the next time input is attempted to be read from the TTY,
                                    * and the operation would have blocked, read(2) instead returns immediately,
                                    * thus indicating an END-OF-FILE within the TTY. (shell programs usually
                                    * interpret this as the user wishing to logout) */
#define __IESCAPING      040000000 /* Status bit for `VLNEXT': The next input character is escaped. */

/* tcflow() and TCXONC use these */
#define TCOOFF     0 /* Suspends output. */
#define TCOON      1 /* Restarts suspended output. */
#define TCIOFF     2 /* Suspends input. */
#define TCION      3 /* Restarts suspended input. */

/* tcflush() and TCFLSH use these */
#define TCIFLUSH   0
#define TCOFLUSH   1
#define TCIOFLUSH  2

/* tcsetattr uses these */
#define TCSANOW    0
#define TCSADRAIN  1
#define TCSAFLUSH  2

#define _IOT_termios /* Hurd ioctl type field. */ \
	_IOT(_IOTS(cflag_t), 4, _IOTS(cc_t), NCCS, _IOTS(speed_t), 2)

__SYSDECL_END

#endif /* !_BITS_TERMIOS_H */
