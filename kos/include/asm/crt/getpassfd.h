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
#ifndef _ASM_CRT_GETPASSFD_H
#define _ASM_CRT_GETPASSFD_H 1

#include <__crt.h>

/* Flags for NetBSD's `getpassfd(3)' function */
#define __GETPASS_NEED_TTY    0x001 /* RPP_REQUIRE_TTY: Error out if `!isatty()' */
#define __GETPASS_FAIL_EOF    0x002 /* Input EOF is an error */
#define __GETPASS_BUF_LIMIT   0x004 /* BEEP when typing after buffer limit is reached */
#define __GETPASS_NO_SIGNAL   0x008 /* When a control character (such as ^C) causes password
                                     * reading  to  be aborted  (with  `errno=EINTR'), don't
                                     * raise(3) the  signal associated  with that  character
                                     * before returning from `getpassfd()' */
#define __GETPASS_NO_BEEP     0x010 /* Don't BEEP */
#define __GETPASS_ECHO        0x020 /* RPP_ECHO_ON: Don't disable echo (but leave it on). */
#define __GETPASS_ECHO_STAR   0x040 /* Print '*' instead for typed characters */
#define __GETPASS_7BIT        0x080 /* RPP_SEVENBIT: Mask input with `0x7f' */
#define __GETPASS_FORCE_LOWER 0x100 /* RPP_FORCELOWER: Force all input to be lower-case. */
#define __GETPASS_FORCE_UPPER 0x200 /* RPP_FORCEUPPER: Force all input to be upper-case. */
#define __GETPASS_ECHO_NL     0x400 /* Print a '\n' after the password was read */

#endif /* !_ASM_CRT_GETPASSFD_H */
