/* HASH CRC-32:0x50464127 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_CONIO_H
#define GUARD_LIBC_USER_CONIO_H 1

#include "../api.h"
#include "../auto/conio.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <conio.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__kbhit)(void);
/* >> _getch(3), _getch_nolock(3)
 * Read a character from the console, without echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__getch)(void);
/* >> _getch(3), _getch_nolock(3)
 * Read a character from the console, without echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__getch_nolock)(void);
/* >> _getche(3), _getche_nolock(3)
 * Read a character from the console, whilst also echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__getche)(void);
/* >> _getche(3), _getche_nolock(3)
 * Read a character from the console, whilst also echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__getche_nolock)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_CONIO_H */
