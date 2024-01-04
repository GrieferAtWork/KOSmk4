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
#ifndef _KOS_IOCTL_TTY_H
#define _KOS_IOCTL_TTY_H 1

/* KOS-specific tty-device system interface.
 * NOTE: Stuff related  to  ansitty  devices and  `libansitty'  goes  into  "video.h"!
 *       Everything in here is more closely related to `struct termios' and `libterm'! */

#include <__stdinc.h>

#include <asm/ioctl.h>
#include <bits/types.h>

__DECL_BEGIN

#define TTYIO_IBUF_GETLIMIT   _IOR_KOS('T', 0x00, __size_t) /* Get input buffer limit (same as `_PC_MAX_INPUT') */
#define TTYIO_IBUF_SETLIMIT   _IOW_KOS('T', 0x00, __size_t) /* Set input buffer limit (requires root) */
#define TTYIO_CANON_GETLIMIT  _IOR_KOS('T', 0x01, __size_t) /* Get canonical line buffer limit (same as `_PC_MAX_CANON') */
#define TTYIO_CANON_SETLIMIT  _IOW_KOS('T', 0x01, __size_t) /* Set canonical line buffer limit (requires root)
                                                             * HINT: This buffer may be cleared with `TCFLSH, TCIFLUSH' */
#define TTYIO_OPEND_GETLIMIT  _IOR_KOS('T', 0x02, __size_t) /* Get pending-output buffer limit (used if `struct termios::c_iflag & IXOFF') */
#define TTYIO_OPEND_SETLIMIT  _IOW_KOS('T', 0x02, __size_t) /* Set pending-output buffer limit (used if `struct termios::c_iflag & IXOFF') (requires root)
                                                             * HINT: This buffer may be cleared with `TCFLSH, TCIFLUSH' */
#define TTYIO_IPEND_GETLIMIT  _IOR_KOS('T', 0x03, __size_t) /* Get pending-input buffer limit (used if `struct termios::c_iflag & __IIOFF') */
#define TTYIO_IPEND_SETLIMIT  _IOW_KOS('T', 0x03, __size_t) /* Set pending-input buffer limit (used if `struct termios::c_iflag & __IIOFF') (requires root)
                                                             * HINT: This buffer may be cleared with `TCFLSH, TCOFLUSH' */

__DECL_END

#endif /* !_KOS_IOCTL_TTY_H */
