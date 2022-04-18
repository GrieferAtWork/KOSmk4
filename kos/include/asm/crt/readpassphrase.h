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
#ifndef _ASM_CRT_READPASSPHRASE_H
#define _ASM_CRT_READPASSPHRASE_H 1

#include <__crt.h>

/* Flags for OpenBSD's `readpassphrase(3)' function */
#define __RPP_ECHO_OFF    0x00 /* Disable echo. */
#define __RPP_ECHO_ON     0x01 /* Don't disable echo (but leave it on). */
#define __RPP_REQUIRE_TTY 0x02 /* Error out if `!isatty()' */
#define __RPP_FORCELOWER  0x04 /* Force all input to be lower-case. */
#define __RPP_FORCEUPPER  0x08 /* Force all input to be upper-case. */
#define __RPP_SEVENBIT    0x10 /* Mask input with `0x7f' */
#define __RPP_STDIN       0x20 /* Use `STDIN_FILENO' as input and `STDERR_FILENO' as output, rather than `/dev/tty' */

#endif /* !_ASM_CRT_READPASSPHRASE_H */
