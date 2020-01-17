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
#ifndef _LINUX_TERMIOS_H
#define _LINUX_TERMIOS_H 1

#include <__stdinc.h>
#include <asm/termios.h>
#include <linux/types.h>

__DECL_BEGIN

#define NFF 5

#ifdef __CC__
struct termiox {
	/* Argument used by `TCGETX', `TCSETX', `TCSETXF' and `TCSETXW' */
	__u16 x_hflag;
	__u16 x_cflag;
	__u16 x_rflag[NFF];
	__u16 x_sflag;
};
#endif /* __CC__ */

/* XXX: Where are these flags used?
 *      Are they used in by one of the fields of the struct above? */
#define RTSXOFF 0x0001 /* RTS flow control on input */
#define CTSXON  0x0002 /* CTS flow control on output */
#define DTRXOFF 0x0004 /* DTR flow control on input */
#define DSRXON  0x0008 /* DCD flow control on output */

__DECL_END

#endif /* !_LINUX_TERMIOS_H */
