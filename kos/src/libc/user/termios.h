/* HASH 0x2b79125c */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_TERMIOS_H
#define GUARD_LIBC_USER_TERMIOS_H 1

#include "../api.h"
#include "../auto/termios.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <termios.h>

DECL_BEGIN

INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_tcgetattr)(fd_t fd, struct termios *__restrict termios_p);
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBCCALL libc_tcsetattr)(fd_t fd, int optional_actions, struct termios const *__restrict termios_p);
INTDEF int NOTHROW_NCX(LIBCCALL libc_tcsendbreak)(fd_t fd, int duration);
INTDEF int NOTHROW_RPC(LIBCCALL libc_tcdrain)(fd_t fd);
INTDEF int NOTHROW_NCX(LIBCCALL libc_tcflush)(fd_t fd, int queue_selector);
INTDEF int NOTHROW_NCX(LIBCCALL libc_tcflow)(fd_t fd, int action);
INTDEF pid_t NOTHROW_NCX(LIBCCALL libc_tcgetsid)(fd_t fd);

DECL_END

#endif /* !GUARD_LIBC_USER_TERMIOS_H */
