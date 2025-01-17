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
#ifndef _ASM_OS_SOLARIS_TERMIOS_H
#define _ASM_OS_SOLARIS_TERMIOS_H 1

#include <__stdinc.h>

#define __VINTR      0
#define __VQUIT      1
#define __VERASE     2
#define __VKILL      3
#define __VEOF       4
#define __VEOL       5
#define __VEOL2      6
#define __VMIN       4
#define __VTIME      5
#define __VSWTCH     7
#define __VSTART     8
#define __VSTOP      9
#define __VSUSP      10
#define __VDSUSP     11
#define __VREPRINT   12
#define __VDISCARD   13
#define __VWERASE    14
#define __VLNEXT     15
#define __VCEOF      8
#define __VCEOL      9
#define __CNUL       0
#define __CDEL       0177
#define __CESC       '\\'
#define __CTRL(c)    ((c)&037)
#define __CINTR      __CTRL('c')
#define __CQUIT      034
#define __CERASE     0177
#define __CKILL      __CTRL('u')
#define __CEOT       04
#define __CEOL       0
#define __CEOL2      0
#define __CEOF       04
#define __CSTART     021
#define __CSTOP      023
#define __CSWTCH     032
#define __CNSWTCH    0
#define __CSUSP      __CTRL('z')
#define __CDSUSP     __CTRL('y')
#define __CRPRNT     __CTRL('r')
#define __CFLUSH     __CTRL('o')
#define __CWERASE    __CTRL('w')
#define __CLNEXT     __CTRL('v')
#define __IGNBRK     0000001
#define __BRKINT     0000002
#define __IGNPAR     0000004
#define __PARMRK     0000010
#define __INPCK      0000020
#define __ISTRIP     0000040
#define __INLCR      0000100
#define __IGNCR      0000200
#define __ICRNL      0000400
#define __IUCLC      0001000
#define __IXON       0002000
#define __IXANY      0004000
#define __IXOFF      0010000
#define __IMAXBEL    0020000
#define __DOSMODE    0100000
#define __OPOST      0000001
#define __OLCUC      0000002
#define __ONLCR      0000004
#define __OCRNL      0000010
#define __ONOCR      0000020
#define __ONLRET     0000040
#define __OFILL      0000100
#define __OFDEL      0000200
#define __NLDLY      0000400
#define __NL0        0
#define __NL1        0000400
#define __CRDLY      0003000
#define __CR0        0
#define __CR1        0001000
#define __CR2        0002000
#define __CR3        0003000
#define __TABDLY     0014000
#define __TAB0       0
#define __TAB1       0004000
#define __TAB2       0010000
#define __TAB3       0014000
#define __XTABS      0014000
#define __BSDLY      0020000
#define __BS0        0
#define __BS1        0020000
#define __VTDLY      0040000
#define __VT0        0
#define __VT1        0040000
#define __FFDLY      0100000
#define __FF0        0
#define __FF1        0100000
#define __PAGEOUT    0200000
#define __WRAP       0400000
#define __CBAUD      0000017
#define __CSIZE      0000060
#define __CS5        0
#define __CS6        0000020
#define __CS7        0000040
#define __CS8        0000060
#define __CSTOPB     0000100
#define __CREAD      0000200
#define __PARENB     0000400
#define __PARODD     0001000
#define __HUPCL      0002000
#define __CLOCAL     0004000
#define __RCV1EN     0010000
#define __XMT1EN     0020000
#define __LOBLK      0040000
#define __XCLUDE     0100000
#define __CRTSXOFF   010000000000
#define __CRTSCTS    020000000000
#define __CIBAUD     03600000
#define __PAREXT     04000000
#define __CBAUDEXT   010000000
#define __CIBAUDEXT  020000000
#define __CRTS_IFLOW 010000000000
#define __CCTS_OFLOW 020000000000
#define __ISIG       0000001
#define __ICANON     0000002
#define __XCASE      0000004
#define __ECHO       0000010
#define __ECHOE      0000020
#define __ECHOK      0000040
#define __ECHONL     0000100
#define __NOFLSH     0000200
#define __TOSTOP     0000400
#define __ECHOCTL    0001000
#define __ECHOPRT    0002000
#define __ECHOKE     0004000
#define __DEFECHO    0010000
#define __FLUSHO     0020000
#define __PENDIN     0040000
#define __IEXTEN     0100000
#define __TCIFLUSH   0
#define __TCOFLUSH   1
#define __TCIOFLUSH  2
#define __TCOOFF     0
#define __TCOON      1
#define __TCIOFF     2
#define __TCION      3
#define __B0         0
#define __B50        1
#define __B75        2
#define __B110       3
#define __B134       4
#define __B150       5
#define __B200       6
#define __B300       7
#define __B600       8
#define __B1200      9
#define __B1800      10
#define __B2400      11
#define __B4800      12
#define __B9600      13
#define __B19200     14
#define __B38400     15
#define __B57600     16
#define __B76800     17
#define __B115200    18
#define __B153600    19
#define __B230400    20
#define __B307200    21
#define __B460800    22

#endif /* !_ASM_OS_SOLARIS_TERMIOS_H */
