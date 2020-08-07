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
#ifndef _BITS_IOCTLS_TERMIOS_H
#define _BITS_IOCTLS_TERMIOS_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

#if defined(__KOS__) || defined(__linux__)
__DECL_BEGIN

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
#define IGNBRK   0x000001 /* break? */
#define BRKINT   0x000002 /* break? */
#define IGNPAR   0x000004 /* Ignore framing errors and parity errors. */
#define PARMRK   0x000008 /* Encode faulty bytes as `\377\0\...' - `\377' is encoded as `\377\377' */
#define INPCK    0x000010 /* Enable input parity checking. */
#define ISTRIP   0x000020 /* Clear the eighth bit. */
#define INLCR    0x000040 /* Translate NL to CR on input. */
#define IGNCR    0x000080 /* Ignore carriage return on input. */
#define ICRNL    0x000100 /* Translate carriage return to newline on input (unless IGNCR is set). */
#define IUCLC    0x000200 /* Map uppercase characters to lowercase on input (requires `IEXTEN'). */
#define IXON     0x000400 /* Enable support for `VSTOP' to disable TTY output transmission. */
#define IXANY    0x000800 /* Any input character has the behavior of `VSTART' */
#define IXOFF    0x001000 /* Status bit for `VSTOP' / `VSTART': Don't transmit pending TTY output until this bit is cleared.
                           * When set, tty output is instead stored in a secondary buffer (s.a. `TTYIO_OPEND_GETLIMIT' and `TTYIO_OPEND_SETLIMIT') */
#define IMAXBEL  0x002000 /* Ring bell when input queue is full (KOS-SPECIFIC: The bell also gets triggered when the queue is empty and a delete character is received) */
#define IUTF8    0x004000 /* Input is UTF8 */
#define __IIOFF  0x100000 /* Status bit for `TCIOFF' / `TCION': When set, redirect input to a secondary buffer. (s.a. `TTYIO_IPEND_GETLIMIT' and `TTYIO_IPEND_SETLIMIT') */

/* c_oflag bits */
#define OPOST       0x00001 /* Enable implementation-defined output processing */
#define OLCUC       0x00002 /* Map lowercase characters to uppercase on output. */
#define ONLCR       0x00004 /* Map NL to CR-NL on output. */
#define OCRNL       0x00008 /* Map CR to NL on output. (Ignored when `ONLRET' is set) (When combined with `ONLCR', output CR as CRNL) */
#define ONOCR       0x00010 /* Don't output CR at column 0. */
#define ONLRET      0x00020 /* Don't output CR. */
#define OFILL       0x00040 /* ??? */
#define OFDEL       0x00080 /* ??? */
#if defined(__USE_MISC) || defined(__USE_XOPEN)
#   define NLDLY    0x00100 /* ??? */
#   define   NL0    0x00000 /* ??? */
#   define   NL1    0x00100 /* ??? */
#   define CRDLY    0x00600 /* ??? */
#   define   CR0    0x00000 /* ??? */
#   define   CR1    0x00200 /* ??? */
#   define   CR2    0x00400 /* ??? */
#   define   CR3    0x00600 /* ??? */
#   define TABDLY   0x01800 /* ??? */
#   define   TAB0   0x00000 /* ??? */
#   define   TAB1   0x00800 /* ??? */
#   define   TAB2   0x01000 /* ??? */
#   define   TAB3   0x01800 /* ??? */
#   define BSDLY    0x02000 /* ??? */
#   define   BS0    0x00000 /* ??? */
#   define   BS1    0x02000 /* ??? */
#   define FFDLY    0x08000 /* ??? */
#   define   FF0    0x00000 /* ??? */
#   define   FF1    0x08000 /* ??? */
#endif /* __USE_MISC || __USE_XOPEN */
#define VTDLY       0x04000 /* ??? */
#define   VT0       0x00000 /* ??? */
#define   VT1       0x04000 /* ??? */
#ifdef __USE_MISC
#define XTABS       0x01800 /* ??? */
#endif /* __USE_MISC */

/* c_cflag bit meaning */
#ifdef __USE_MISC
#define CBAUD     0x100f
#endif /* __USE_MISC */
#define B0        0x0000 /* hang up */
#define B50       0x0001
#define B75       0x0002
#define B110      0x0003
#define B134      0x0004
#define B150      0x0005
#define B200      0x0006
#define B300      0x0007
#define B600      0x0008
#define B1200     0x0009
#define B1800     0x000a
#define B2400     0x000b
#define B4800     0x000c
#define B9600     0x000d
#define B19200    0x000e
#define B38400    0x000f
#ifdef __USE_MISC
#define EXTA      B19200
#define EXTB      B38400
#endif /* __USE_MISC */
#define CSIZE     0x00030
#define   CS5     0x00000
#define   CS6     0x00010
#define   CS7     0x00020
#define   CS8     0x00030
#define CSTOPB    0x00040
#define CREAD     0x00080
#define PARENB    0x00100
#define PARODD    0x00200
#define HUPCL     0x00400
#define CLOCAL    0x00800
#ifdef __USE_MISC
#define CBAUDEX   0x01000
#endif /* __USE_MISC */
#define B57600    0x01001
#define B115200   0x01002
#define B230400   0x01003
#define B460800   0x01004
#define B500000   0x01005
#define B576000   0x01006
#define B921600   0x01007
#define B1000000  0x01008
#define B1152000  0x01009
#define B1500000  0x0100a
#define B2000000  0x0100b
#define B2500000  0x0100c
#define B3000000  0x0100d
#define B3500000  0x0100e
#define B4000000  0x0100f
#define __MAX_BAUD B4000000
#ifdef __USE_MISC
#define CIBAUD    0x100f0000 /* input baud rate (not used) */
#define CMSPAR    0x40000000 /* mark or space (stick) parity */
#define CRTSCTS   0x80000000 /* flow control */
#endif /* __USE_MISC */

/* c_lflag bits */
#define ISIG        0x000001 /* When any of the characters INTR, QUIT, SUSP, or DSUSP are received, generate the corresponding signal. */
#define ICANON      0x000002 /* Enable canonical mode */
#if defined(__USE_MISC) || defined(__USE_XOPEN)
#define XCASE       0x000004 /* If ICANON is also set, terminal is uppercase only. Input is converted to lowercase,
                              * except for characters preceded by \. On output, uppercase characters are preceded
                              * by \ and lowercase characters are converted to uppercase. */
#endif /* __USE_MISC || __USE_XOPEN */
#define ECHO        0x000008 /* Echo input characters */
#define ECHOE       0x000010 /* If ICANON is also set, the VERASE character erases the preceding input character, and VWERASE erases the preceding word */
#define ECHOK       0x000020 /* If ICANON is also set, the VKILL character erases the current line */
#define ECHONL      0x000040 /* If ICANON is also set, echo the NL character even if ECHO is not set
                              * NOTE: for this purpose, the NL character(s) recognized are '\n', `VEOL' and `VEOL2' */
#define NOFLSH      0x000080 /* Disable flushing the input and output queues when generating signals for the INT, QUIT, and SUSP characters */
#define TOSTOP      0x000100 /* Send the SIGTTOU signal to the process group of a background process which tries to write to its controlling terminal */
#ifdef __USE_MISC
#define ECHOCTL     0x000200 /* If ECHO is also set, terminal special characters other than TAB(\t), NL(\n),
                              * START, and STOP are echoed as ^X, where X is the character with ASCII code
                              * 0x40 greater than the special character. For example, character 0x08 (BS)
                              * is echoed as ^H */
#define ECHOPRT     0x000400 /* This bit is like ECHOE, enables display of the ERASE character in a way that
                              * is geared to a hardcopy terminal. When you type the ERASE character, a `\'
                              * character is printed followed by the first character erased. Typing the
                              * ERASE character again just prints the next character erased. Then, the
                              * next time you type a normal character, a `/' character is printed
                              * before the character echoes. */
#define ECHOKE      0x000800 /* If ICANON is also set, KILL is echoed by erasing each character on the line, as specified by ECHOE and ECHOPRT */
#define FLUSHO      0x001000 /* Output is being flushed. This flag is toggled by typing the DISCARD character */
#define PENDIN      0x004000 /* ??? */
#endif /* __USE_MISC */
#define IEXTEN      0x008000 /* Enable implementation-defined input processing. This flag, as
                              * well as ICANON must be enabled for the special characters
                              * EOL2, LNEXT, REPRINT, WERASE to be interpreted, and for the
                              * IUCLC flag to be effective */
#ifdef __USE_MISC
#define EXTPROC     0x010000 /* Skip handling of: `PARMRK', `ECHO' and `IXON'+`IXANY', as well as `c_cc[*]' */
#endif /* __USE_MISC */
#define __IERASING  0x100000 /* Status bit for `ECHOPRT' */
#define __IXCASEING 0x200000 /* Status bit for `XCASE' (the previous character was \) */
#define __IEOFING   0x400000 /* Status bit for a pending `VEOF' character
                              * When set, the next time input is attempted to be read from the TTY,
                              * and the operation would have blocked, read(2) instead returns immediately,
                              * thus indicating an END-OF-FILE within the TTY. (shell programs usually
                              * interpret this as the user wishing to logout) */
#define __IESCAPING 0x800000 /* Status bit for `VLNEXT': The next input character is escaped. */

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
#define TCSANOW    0 /* Set terminal attributes (s.a. `TCSETA') */
#define TCSADRAIN  1 /* Wait for all unwritten data to be transmitted, discard all unread data, then set terminal attributes (s.a. `TCSETAW') */
#define TCSAFLUSH  2 /* Wait for all unwritten data to be transmitted, then set terminal attributes (s.a. `TCSETAF') */

#define _IOT_termios /* Hurd ioctl type field. */ \
	_IOT(_IOTS(cflag_t), 4, _IOTS(cc_t), NCCS, _IOTS(speed_t), 2)

__DECL_END
#endif /* __KOS__ || __linux__ */

#endif /* !_BITS_IOCTLS_TERMIOS_H */
