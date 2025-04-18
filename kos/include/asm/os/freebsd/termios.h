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
#ifndef _ASM_OS_FREEBSD_TERMIOS_H
#define _ASM_OS_FREEBSD_TERMIOS_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h> /* __UINT32_C */

#define __VEOF       0
#define __VEOL       1
#define __VEOL2      2
#define __VERASE     3
#define __VWERASE    4
#define __VKILL      5
#define __VREPRINT   6
#define __VERASE2    7
#define __VINTR      8
#define __VQUIT      9
#define __VSUSP      10
#define __VDSUSP     11
#define __VSTART     12
#define __VSTOP      13
#define __VLNEXT     14
#define __VDISCARD   15
#define __VMIN       16
#define __VTIME      17
#define __VSTATUS    18
#define __VDISABLE   0xff
#define __IGNBRK     0x00000001
#define __BRKINT     0x00000002
#define __IGNPAR     0x00000004
#define __PARMRK     0x00000008
#define __INPCK      0x00000010
#define __ISTRIP     0x00000020
#define __INLCR      0x00000040
#define __IGNCR      0x00000080
#define __ICRNL      0x00000100
#define __IXON       0x00000200
#define __IXOFF      0x00000400
#define __IXANY      0x00000800
#define __IMAXBEL    0x00002000
#define __OPOST      0x00000001
#define __ONLCR      0x00000002
#define __TABDLY     0x00000004
#define __TAB0       0x00000000
#define __TAB3       0x00000004
#define __ONOEOT     0x00000008
#define __OCRNL      0x00000010
#define __ONOCR      0x00000020
#define __ONLRET     0x00000040
#define __CIGNORE    0x00000001
#define __CSIZE      0x00000300
#define __CS5        0x00000000
#define __CS6        0x00000100
#define __CS7        0x00000200
#define __CS8        0x00000300
#define __CSTOPB     0x00000400
#define __CREAD      0x00000800
#define __PARENB     0x00001000
#define __PARODD     0x00002000
#define __HUPCL      0x00004000
#define __CLOCAL     0x00008000
#define __CCTS_OFLOW 0x00010000
#define __CRTS_IFLOW 0x00020000
#define __CRTSCTS    (__CCTS_OFLOW | __CRTS_IFLOW)
#define __CDTR_IFLOW 0x00040000
#define __CDSR_OFLOW 0x00080000
#define __CCAR_OFLOW 0x00100000
#define __CNO_RTSDTR 0x00200000
#define __ECHOKE     0x00000001
#define __ECHOE      0x00000002
#define __ECHOK      0x00000004
#define __ECHO       0x00000008
#define __ECHONL     0x00000010
#define __ECHOPRT    0x00000020
#define __ECHOCTL    0x00000040
#define __ISIG       0x00000080
#define __ICANON     0x00000100
#define __ALTWERASE  0x00000200
#define __IEXTEN     0x00000400
#define __EXTPROC    0x00000800
#define __TOSTOP     0x00400000
#define __FLUSHO     0x00800000
#define __NOKERNINFO 0x02000000
#define __PENDIN     0x20000000
#define __NOFLSH     0x80000000
#define __B0         0
#define __B50        50
#define __B75        75
#define __B110       110
#define __B134       134
#define __B150       150
#define __B200       200
#define __B300       300
#define __B600       600
#define __B1200      1200
#define __B1800      1800
#define __B2400      2400
#define __B4800      4800
#define __B9600      9600
#define __B19200     19200
#define __B38400     38400
#define __B7200      7200
#define __B14400     14400
#define __B28800     28800
#define __B57600     57600
#define __B76800     76800
#define __B115200    115200
#define __B230400    230400
#define __B460800    460800
#define __B921600    921600
#define __EXTA       19200
#define __EXTB       38400
#define __TCSANOW    0
#define __TCSADRAIN  1
#define __TCSAFLUSH  2
#define __TCSASOFT   0x10
#define __TCIFLUSH   1
#define __TCOFLUSH   2
#define __TCIOFLUSH  3
#define __TCOOFF     1
#define __TCOON      2
#define __TCIOFF     3
#define __TCION      4

#endif /* !_ASM_OS_FREEBSD_TERMIOS_H */
