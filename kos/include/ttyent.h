/* HASH CRC-32:0x7a5f7425 */
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
/* (#) Portability: FreeBSD       (/include/ttyent.h) */
/* (#) Portability: GNU C Library (/misc/ttyent.h) */
/* (#) Portability: NetBSD        (/include/ttyent.h) */
/* (#) Portability: uClibc        (/include/ttyent.h) */
#ifndef _TTYENT_H
#define _TTYENT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/crt/ttyent.h>
#include <bits/crt/db/ttyent.h>

#define _PATH_TTYS   "/etc/ttys"
#define _TTYS_OFF    "off"
#define _TTYS_ON     "on"
#define _TTYS_SECURE "secure"
#define _TTYS_WINDOW "window"

#ifdef __TTY_ON
#define TTY_ON __TTY_ON /* enable logins (start ty_getty program) */
#endif /* __TTY_ON */
#ifdef __TTY_SECURE
#define TTY_SECURE __TTY_SECURE /* allow uid of 0 to login */
#endif /* __TTY_SECURE */

__SYSDECL_BEGIN

#ifdef __CC__

__CDECLARE_OPT(,struct ttyent *,__NOTHROW_RPC_KOS,getttyent,(void),())
__CDECLARE_OPT(__ATTR_NONNULL((1)),struct ttyent *,__NOTHROW_RPC_KOS,getttynam,(char const *__tty),(__tty))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,setttyent,(void),())
__CDECLARE_OPT(,int,__NOTHROW_NCX,endttyent,(void),())
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_TTYENT_H */
