/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_OS_KOS_TERMIOS_H
#define _ASM_OS_KOS_TERMIOS_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

/* NOTE: Some of the comments are taken from here:
 *   http://man7.org/linux/man-pages/man3/tcflow.3.html
 *   https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_node/libc_355.html
 */


/* c_cc characters */
#define __VINTR    0  /* ^C: Send SIGINT to the foreground process (requires `ISIG') */
#define __VQUIT    1  /* ^\: Send SIGQUIT to the foreground process (requires `ISIG') */
#define __VERASE   2  /* \b: Erase the last character from the input canon (requires `ECHOE') */
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
#define __IGNBRK   0x000001 /* break? */
#define __BRKINT   0x000002 /* break? */
#define __IGNPAR   0x000004 /* Ignore framing errors and parity errors. */
#define __PARMRK   0x000008 /* Encode faulty bytes as `\377\0\...' - `\377' is encoded as `\377\377' */
#define __INPCK    0x000010 /* Enable input parity checking. */
#define __ISTRIP   0x000020 /* Clear the eighth bit. */
#define __INLCR    0x000040 /* Translate NL to CR on input. */
#define __IGNCR    0x000080 /* Ignore carriage return on input. */
#define __ICRNL    0x000100 /* Translate carriage return to newline on input (unless IGNCR is set). */
#define __IUCLC    0x000200 /* Map uppercase characters to lowercase on input (requires `IEXTEN'). */
#define __IXON     0x000400 /* Enable support for `VSTOP' to disable TTY output transmission. */
#define __IXANY    0x000800 /* Any input character has the behavior of `VSTART' */
#define __IXOFF    0x001000 /* Status bit for `VSTOP' / `VSTART': Don't transmit pending TTY output until this bit is cleared.
                             * When set, tty output is instead stored in a secondary buffer (s.a. `TTYIO_OPEND_GETLIMIT' and `TTYIO_OPEND_SETLIMIT') */
#define __IMAXBEL  0x002000 /* Ring bell when input queue is full (KOS-SPECIFIC: The bell also gets triggered when the queue is empty and a delete character is received) */
#define __IUTF8    0x004000 /* Input is UTF8 */
#define __IIOFF    0x100000 /* Status bit for `TCIOFF' / `TCION': When set, redirect input to a secondary buffer. (s.a. `TTYIO_IPEND_GETLIMIT' and `TTYIO_IPEND_SETLIMIT') */

/* c_oflag bits */
#define __OPOST       0x00001 /* Enable implementation-defined output processing */
#define __OLCUC       0x00002 /* Map lowercase characters to uppercase on output. */
#define __ONLCR       0x00004 /* Map NL to CR-NL on output. */
#define __OCRNL       0x00008 /* Map CR to NL on output. (Ignored when `ONLRET' is set) (When combined with `ONLCR', output CR as CRNL) */
#define __ONOCR       0x00010 /* Don't output CR at column 0. */
#define __ONLRET      0x00020 /* Don't output CR. */
#define __OFILL       0x00040 /* ??? */
#define __OFDEL       0x00080 /* ??? */
#   define __NLDLY    0x00100 /* ??? */
#   define   __NL0    0x00000 /* ??? */
#   define   __NL1    0x00100 /* ??? */
#   define __CRDLY    0x00600 /* ??? */
#   define   __CR0    0x00000 /* ??? */
#   define   __CR1    0x00200 /* ??? */
#   define   __CR2    0x00400 /* ??? */
#   define   __CR3    0x00600 /* ??? */
#   define __TABDLY   0x01800 /* ??? */
#   define   __TAB0   0x00000 /* ??? */
#   define   __TAB1   0x00800 /* ??? */
#   define   __TAB2   0x01000 /* ??? */
#   define   __TAB3   0x01800 /* ??? */
#   define __BSDLY    0x02000 /* ??? */
#   define   __BS0    0x00000 /* ??? */
#   define   __BS1    0x02000 /* ??? */
#   define __FFDLY    0x08000 /* ??? */
#   define   __FF0    0x00000 /* ??? */
#   define   __FF1    0x08000 /* ??? */
#define __VTDLY       0x04000 /* ??? */
#define   __VT0       0x00000 /* ??? */
#define   __VT1       0x04000 /* ??? */
#define __XTABS       0x01800 /* ??? */

/* c_cflag bit meaning */
#define __CBAUD     0x100f
#define __B0        0x0000 /* hang up */
#define __B50       0x0001
#define __B75       0x0002
#define __B110      0x0003
#define __B134      0x0004
#define __B150      0x0005
#define __B200      0x0006
#define __B300      0x0007
#define __B600      0x0008
#define __B1200     0x0009
#define __B1800     0x000a
#define __B2400     0x000b
#define __B4800     0x000c
#define __B9600     0x000d
#define __B19200    0x000e
#define __B38400    0x000f
#define __EXTA      B19200
#define __EXTB      B38400
#define __CSIZE     0x00030
#define   __CS5     0x00000
#define   __CS6     0x00010
#define   __CS7     0x00020
#define   __CS8     0x00030
#define __CSTOPB    0x00040
#define __CREAD     0x00080
#define __PARENB    0x00100
#define __PARODD    0x00200
#define __HUPCL     0x00400
#define __CLOCAL    0x00800
#define __CBAUDEX   0x01000
#define __B57600    0x01001
#define __B115200   0x01002
#define __B230400   0x01003
#define __B460800   0x01004
#define __B500000   0x01005
#define __B576000   0x01006
#define __B921600   0x01007
#define __B1000000  0x01008
#define __B1152000  0x01009
#define __B1500000  0x0100a
#define __B2000000  0x0100b
#define __B2500000  0x0100c
#define __B3000000  0x0100d
#define __B3500000  0x0100e
#define __B4000000  0x0100f
#define __MAX_BAUD  __B4000000
#define __CIBAUD    0x100f0000 /* input baud rate (not used) */
#define __CMSPAR    0x40000000 /* mark or space (stick) parity */
#define __CRTSCTS   0x80000000 /* flow control */

/* c_lflag bits */
#define __ISIG      0x000001 /* When any of the characters INTR, QUIT, SUSP, or DSUSP are received, generate the corresponding signal. */
#define __ICANON    0x000002 /* Enable canonical mode */
#define __XCASE     0x000004 /* If ICANON is also set, terminal is uppercase only. Input is converted to lowercase,
                              * except for characters preceded by \. On output, uppercase characters are preceded
                              * by \ and lowercase characters are converted to uppercase. */
#define __ECHO      0x000008 /* Echo input characters */
#define __ECHOE     0x000010 /* If ICANON is also set, the VERASE character erases the preceding input character, and VWERASE erases the preceding word */
#define __ECHOK     0x000020 /* If ICANON is also set, the VKILL character erases the current line */
#define __ECHONL    0x000040 /* If ICANON is also set, echo the NL character even if ECHO is not set
                              * NOTE: for this purpose, the NL character(s) recognized are '\n', `VEOL' and `VEOL2' */
#define __NOFLSH    0x000080 /* Disable flushing the input and output queues when generating signals for the INT, QUIT, and SUSP characters */
#define __TOSTOP    0x000100 /* Send the SIGTTOU signal to the process group of a background process which tries to write to its controlling terminal */
#define __ECHOCTL   0x000200 /* If ECHO is also set, terminal special characters other than TAB(\t), NL(\n),
                              * START, and STOP are echoed as ^X, where X is the character with ASCII code
                              * 0x40 greater than the special character. For example, character 0x08 (BS)
                              * is echoed as ^H */
#define __ECHOPRT   0x000400 /* This bit is like ECHOE, enables display of the ERASE character in a way that
                              * is geared to a hardcopy terminal. When you type the ERASE character, a `\'
                              * character is printed followed by the first character erased. Typing the
                              * ERASE character again just prints the next character erased. Then, the
                              * next time you type a normal character, a `/' character is printed
                              * before the character echoes. */
#define __ECHOKE    0x000800 /* If ICANON is also set, KILL is echoed by erasing each character on the line, as specified by ECHOE and ECHOPRT */
#define __FLUSHO    0x001000 /* Output is being flushed. This flag is toggled by typing the DISCARD character */
#define __PENDIN    0x004000 /* ??? */
#define __IEXTEN    0x008000 /* Enable implementation-defined input processing. This flag, as
                              * well as ICANON must be enabled for the special characters
                              * EOL2, LNEXT, REPRINT, WERASE to be interpreted, and for the
                              * IUCLC flag to be effective */
#define __EXTPROC   0x010000 /* Skip handling of: `PARMRK', `ECHO' and `IXON'+`IXANY', as well as `c_cc[*]' */
#define __IERASING  0x100000 /* Status bit for `ECHOPRT' */
#define __IXCASEING 0x200000 /* Status bit for `XCASE' (the previous character was \) */
#define __IEOFING   0x400000 /* Status bit for a pending `VEOF' character
                              * When set, the next time input is attempted to be read from the TTY,
                              * and the operation would have blocked, read(2) instead returns immediately,
                              * thus indicating an END-OF-FILE within the TTY. (shell programs usually
                              * interpret this as the user wishing to logout) */
#define __IESCAPING 0x800000 /* Status bit for `VLNEXT': The next input character is escaped. */

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
