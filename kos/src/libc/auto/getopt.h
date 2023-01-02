/* HASH CRC-32:0x58b3a228 */
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
#ifndef GUARD_LIBC_AUTO_GETOPT_H
#define GUARD_LIBC_AUTO_GETOPT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <getopt.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Return the option  character from  OPTS just read.  Return -1  when
 * there  are no  more options.  For unrecognized  options, or options
 * missing arguments, `optopt' is set to the option letter, and '?' is
 * returned.
 * - The OPTS string is a list of characters which are recognized option
 *   letters, optionally followed by colons, specifying that that letter
 *   takes an argument, to be placed in `optarg'.
 * - If a letter in OPTS is followed by two colons, its argument is
 *   optional. This  behavior  is  specific to  the  GNU  `getopt'.
 * - The  argument `--' causes  premature termination of argument
 *   scanning, explicitly telling `getopt' that there are no more
 *   options.
 * - If OPTS begins with `--', then non-option arguments are treated as
 *   arguments to the option '\0'. This behavior is specific to the GNU
 *   `getopt' */
INTDEF WUNUSED int NOTHROW_NCX(LIBDCALL libd_getopt)(int argc, char *const argv[], char const *shortopts);
/* Return the option  character from  OPTS just read.  Return -1  when
 * there  are no  more options.  For unrecognized  options, or options
 * missing arguments, `optopt' is set to the option letter, and '?' is
 * returned.
 * - The OPTS string is a list of characters which are recognized option
 *   letters, optionally followed by colons, specifying that that letter
 *   takes an argument, to be placed in `optarg'.
 * - If a letter in OPTS is followed by two colons, its argument is
 *   optional. This  behavior  is  specific to  the  GNU  `getopt'.
 * - The  argument `--' causes  premature termination of argument
 *   scanning, explicitly telling `getopt' that there are no more
 *   options.
 * - If OPTS begins with `--', then non-option arguments are treated as
 *   arguments to the option '\0'. This behavior is specific to the GNU
 *   `getopt' */
INTDEF WUNUSED int NOTHROW_NCX(LIBDCALL libd_getopt_long)(int argc, char *const argv[], char const *shortopts, struct option const *longopts, int *longind);
/* Return the option  character from  OPTS just read.  Return -1  when
 * there  are no  more options.  For unrecognized  options, or options
 * missing arguments, `optopt' is set to the option letter, and '?' is
 * returned.
 * - The OPTS string is a list of characters which are recognized option
 *   letters, optionally followed by colons, specifying that that letter
 *   takes an argument, to be placed in `optarg'.
 * - If a letter in OPTS is followed by two colons, its argument is
 *   optional. This  behavior  is  specific to  the  GNU  `getopt'.
 * - The  argument `--' causes  premature termination of argument
 *   scanning, explicitly telling `getopt' that there are no more
 *   options.
 * - If OPTS begins with `--', then non-option arguments are treated as
 *   arguments to the option '\0'. This behavior is specific to the GNU
 *   `getopt' */
INTDEF WUNUSED int NOTHROW_NCX(LIBDCALL libd_getopt_long_only)(int argc, char *const argv[], char const *shortopts, struct option const *longopts, int *longind);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_GETOPT_H */
