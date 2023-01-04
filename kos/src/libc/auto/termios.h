/* HASH CRC-32:0x2c0a7601 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
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

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cfgetospeed(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) speed_t NOTHROW_NCX(LIBDCALL libd_cfgetospeed)(struct termios const *__restrict termios_p);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cfgetospeed(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) speed_t NOTHROW_NCX(LIBCCALL libc_cfgetospeed)(struct termios const *__restrict termios_p);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cfgetispeed(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) speed_t NOTHROW_NCX(LIBDCALL libd_cfgetispeed)(struct termios const *__restrict termios_p);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cfgetispeed(3) */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) speed_t NOTHROW_NCX(LIBCCALL libc_cfgetispeed)(struct termios const *__restrict termios_p);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cfsetospeed(3) */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_cfsetospeed)(struct termios *__restrict termios_p, speed_t speed);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cfsetospeed(3) */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_cfsetospeed)(struct termios *__restrict termios_p, speed_t speed);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cfsetispeed(3) */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_cfsetispeed)(struct termios *__restrict termios_p, speed_t speed);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cfsetispeed(3) */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_cfsetispeed)(struct termios *__restrict termios_p, speed_t speed);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tcgetattr(3)
 * Get terminal attributes */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_tcgetattr)(fd_t fd, struct termios *__restrict termios_p);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tcgetattr(3)
 * Get terminal attributes */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBCCALL libc_tcgetattr)(fd_t fd, struct termios *__restrict termios_p);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tcsetattr(3)
 * Set terminal attributes
 * @param: optional_actions: One of `TCSANOW', `TCSADRAIN' or `TCSAFLUSH' */
INTDEF ATTR_IN(3) int NOTHROW_NCX(LIBDCALL libd_tcsetattr)(fd_t fd, __STDC_INT_AS_UINT_T optional_actions, struct termios const *__restrict termios_p);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tcsetattr(3)
 * Set terminal attributes
 * @param: optional_actions: One of `TCSANOW', `TCSADRAIN' or `TCSAFLUSH' */
INTDEF ATTR_IN(3) int NOTHROW_NCX(LIBCCALL libc_tcsetattr)(fd_t fd, __STDC_INT_AS_UINT_T optional_actions, struct termios const *__restrict termios_p);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tcsendbreak(3) */
INTDEF int NOTHROW_NCX(LIBDCALL libd_tcsendbreak)(fd_t fd, int duration);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tcsendbreak(3) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_tcsendbreak)(fd_t fd, int duration);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tcdrain(3) */
INTDEF int NOTHROW_RPC(LIBDCALL libd_tcdrain)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tcdrain(3) */
INTDEF int NOTHROW_RPC(LIBCCALL libc_tcdrain)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tcflush(3)
 * @param: queue_selector: One of `TCIFLUSH', `TCOFLUSH' or `TCIOFLUSH' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_tcflush)(fd_t fd, __STDC_INT_AS_UINT_T queue_selector);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tcflush(3)
 * @param: queue_selector: One of `TCIFLUSH', `TCOFLUSH' or `TCIOFLUSH' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_tcflush)(fd_t fd, __STDC_INT_AS_UINT_T queue_selector);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tcflow(3)
 * @param: action: One of `TCOOFF', `TCOON', `TCIOFF', `TCION' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_tcflow)(fd_t fd, __STDC_INT_AS_UINT_T action);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tcflow(3)
 * @param: action: One of `TCOOFF', `TCOON', `TCIOFF', `TCION' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_tcflow)(fd_t fd, __STDC_INT_AS_UINT_T action);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tcgetsid(3) */
INTDEF pid_t NOTHROW_NCX(LIBDCALL libd_tcgetsid)(fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tcgetsid(3) */
INTDEF pid_t NOTHROW_NCX(LIBCCALL libc_tcgetsid)(fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tcsetsid(3) */
INTDEF int NOTHROW_NCX(LIBDCALL libd_tcsetsid)(fd_t fd, pid_t pid);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tcsetsid(3) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_tcsetsid)(fd_t fd, pid_t pid);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cfsetspeed(3) */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_cfsetspeed)(struct termios *__restrict termios_p, speed_t speed);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cfsetspeed(3) */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_cfsetspeed)(struct termios *__restrict termios_p, speed_t speed);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cfmakeraw(3)
 * Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
 * This entails the CANON and all control characters being disabled, as well as
 * any sort of input/output text processing no longer taking place. */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBDCALL libd_cfmakeraw)(struct termios *__restrict termios_p);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cfmakeraw(3)
 * Set ~raw~ mode for the given `termios_p' (in/out; meaning that `termios_p' must already be initialized)
 * This entails the CANON and all control characters being disabled, as well as
 * any sort of input/output text processing no longer taking place. */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBCCALL libc_cfmakeraw)(struct termios *__restrict termios_p);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cfmakesane(3)
 * Set ~sane~ mode for the given `termios_p' (out-only; meaning that `termios_p' gets initialized by this function)
 * Sane here  refers  to  setting  all values  to  their  defaults,  as they  are  defined  in  <sys/ttydefaults.h> */
INTDEF ATTR_OUT(1) void NOTHROW_NCX(LIBDCALL libd_cfmakesane)(struct termios *__restrict termios_p);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> cfmakesane(3)
 * Set ~sane~ mode for the given `termios_p' (out-only; meaning that `termios_p' gets initialized by this function)
 * Sane here  refers  to  setting  all values  to  their  defaults,  as they  are  defined  in  <sys/ttydefaults.h> */
INTDEF ATTR_OUT(1) void NOTHROW_NCX(LIBCCALL libc_cfmakesane)(struct termios *__restrict termios_p);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tcgetwinsize(3) */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_tcgetwinsize)(fd_t fd, struct winsize *winsize_p);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tcgetwinsize(3) */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBCCALL libc_tcgetwinsize)(fd_t fd, struct winsize *winsize_p);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> tcsetwinsize(3) */
INTDEF ATTR_IN(2) int NOTHROW_NCX(LIBDCALL libd_tcsetwinsize)(fd_t fd, struct winsize const *winsize_p);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> tcsetwinsize(3) */
INTDEF ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_tcsetwinsize)(fd_t fd, struct winsize const *winsize_p);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_TERMIOS_H */
