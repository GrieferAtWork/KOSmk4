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
#ifndef _BITS_IOCTL_TYPES_H
#define _BITS_IOCTL_TYPES_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/i386-linux-gnu/bits/ioctl-types.h' */

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <asm/ioctls.h>

/* Structure types for pre-termios terminal ioctls.  Linux version.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
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
struct winsize {
	__UINT16_TYPE__ ws_row;    /* Vertical (Y) number of cells */
	__UINT16_TYPE__ ws_col;    /* Horizontal (X) number of cells */
	__UINT16_TYPE__ ws_xpixel; /* Total display width (X-size) in pixels (usually `ws_col * X' (e.g. X == 8)) */
	__UINT16_TYPE__ ws_ypixel; /* Total display height (Y-size) in pixels (usually `ws_row * X' (e.g. X == 16)) */
};
#endif /* __CC__ */

#define NCC 8
#ifdef __CC__
struct termio {
	__UINT16_TYPE__ c_iflag;   /* input mode flags. */
	__UINT16_TYPE__ c_oflag;   /* output mode flags. */
	__UINT16_TYPE__ c_cflag;   /* control mode flags. */
	__UINT16_TYPE__ c_lflag;   /* local mode flags. */
	__UINT8_TYPE__  c_line;    /* line discipline. */
	__UINT8_TYPE__  c_cc[NCC]; /* control characters. */
};
#endif /* __CC__ */

/* modem lines */
#define TIOCM_LE  0x001
#define TIOCM_DTR 0x002
#define TIOCM_RTS 0x004
#define TIOCM_ST  0x008
#define TIOCM_SR  0x010
#define TIOCM_CTS 0x020
#define TIOCM_CAR 0x040
#define TIOCM_RNG 0x080
#define TIOCM_DSR 0x100
#define TIOCM_CD  TIOCM_CAR
#define TIOCM_RI  TIOCM_RNG

/* ioctl (fd, TIOCSERGETLSR, &result) where result may be as below */

/* line disciplines */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	N_TTY,
	N_SLIP,
	N_MOUSE,
	N_PPP,
	N_STRIP,
	N_AX25,
	N_X25, /* X.25 async  */
	N_6PACK,
	N_MASC,         /* Mobitex module  */
	N_R3964,        /* Simatic R3964 module  */
	N_PROFIBUS_FDL, /* Profibus  */
	N_IRDA,         /* Linux IR  */
	N_SMSBLOCK,     /* SMS block mode  */
	N_HDLC,         /* synchronous HDLC  */
	N_SYNC_PPP,     /* synchronous PPP  */
	N_HCI,          /* Bluetooth HCI UART  */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define N_TTY          N_TTY
#define N_SLIP         N_SLIP
#define N_MOUSE        N_MOUSE
#define N_PPP          N_PPP
#define N_STRIP        N_STRIP
#define N_AX25         N_AX25
#define N_X25          N_X25          /* X.25 async  */
#define N_6PACK        N_6PACK
#define N_MASC         N_MASC         /* Mobitex module  */
#define N_R3964        N_R3964        /* Simatic R3964 module  */
#define N_PROFIBUS_FDL N_PROFIBUS_FDL /* Profibus  */
#define N_IRDA         N_IRDA         /* Linux IR  */
#define N_SMSBLOCK     N_SMSBLOCK     /* SMS block mode  */
#define N_HDLC         N_HDLC         /* synchronous HDLC  */
#define N_SYNC_PPP     N_SYNC_PPP     /* synchronous PPP  */
#define N_HCI          N_HCI          /* Bluetooth HCI UART  */
#else /* __COMPILER_PREFERR_ENUMS */
#define N_TTY          0
#define N_SLIP         1
#define N_MOUSE        2
#define N_PPP          3
#define N_STRIP        4
#define N_AX25         5
#define N_X25          6  /* X.25 async  */
#define N_6PACK        7
#define N_MASC         8  /* Mobitex module  */
#define N_R3964        9  /* Simatic R3964 module  */
#define N_PROFIBUS_FDL 10 /* Profibus  */
#define N_IRDA         11 /* Linux IR  */
#define N_SMSBLOCK     12 /* SMS block mode  */
#define N_HDLC         13 /* synchronous HDLC  */
#define N_SYNC_PPP     14 /* synchronous PPP  */
#define N_HCI          15 /* Bluetooth HCI UART  */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

__SYSDECL_END

#endif /* !_BITS_IOCTL_TYPES_H */
