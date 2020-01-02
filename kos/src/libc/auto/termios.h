/* HASH CRC-32:0x1074fbf9 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_TERMIOS_H
#define GUARD_LIBC_AUTO_TERMIOS_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <termios.h>

DECL_BEGIN

/* Set ~sane~ mode for the given `termios_p' (out-only; meaning that `termios_p' gets initialized by this function)
 * Sane here refers to setting all values to their defaults, as they are defined in <sys/ttydefaults.h> */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_cfmakesane)(struct termios *__restrict termios_p);
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) speed_t NOTHROW_NCX(LIBCCALL libc_cfgetospeed)(struct termios const *__restrict termios_p);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) speed_t NOTHROW_NCX(LIBCCALL libc_cfgetispeed)(struct termios const *__restrict termios_p);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_cfsetospeed)(struct termios *__restrict termios_p, speed_t speed);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_cfsetispeed)(struct termios *__restrict termios_p, speed_t speed);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_cfsetspeed)(struct termios *__restrict termios_p, speed_t speed);
/* Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
 * This entails the CANON and all control characters being disabled, as well as
 * any sort of input/output text processing no longer taking place. */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_cfmakeraw)(struct termios *__restrict termios_p);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_TERMIOS_H */
