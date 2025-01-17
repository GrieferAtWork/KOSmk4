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
#ifndef _BITS_OS_KOS_TERMIOX_H
#define _BITS_OS_KOS_TERMIOX_H 1

#include <__stdinc.h>

#define NFF 5

#ifdef __CC__
#include <hybrid/typecore.h>
__DECL_BEGIN

struct termiox {
	/* Argument used by `TCGETX', `TCSETX', `TCSETXF' and `TCSETXW' */
	__UINT16_TYPE__ x_hflag;
	__UINT16_TYPE__ x_cflag;
	__UINT16_TYPE__ x_rflag[NFF];
	__UINT16_TYPE__ x_sflag;
};

__DECL_END
#endif /* __CC__ */

/* XXX: Where are these flags used?
 *      Are they used in by one of the fields of the struct above?
 * Here are some docs for it?
 *  - https://docs.oracle.com/cd/E86824_01/html/E54777/termiox-7i.html
 *  - https://docstore.mik.ua/manuals/hp-ux/en/B2355-60130/termiox.7.html
 */
#define RTSXOFF 0x0001 /* RTS flow control on input */
#define CTSXON  0x0002 /* CTS flow control on output */
#define DTRXOFF 0x0004 /* DTR flow control on input */
#define DSRXON  0x0008 /* DCD flow control on output */

#endif /* !_BITS_OS_KOS_TERMIOX_H */
