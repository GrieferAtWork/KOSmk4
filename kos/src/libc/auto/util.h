/* HASH CRC-32:0xde37cee0 */
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
#ifndef GUARD_LIBC_AUTO_UTIL_H
#define GUARD_LIBC_AUTO_UTIL_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <util.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param: dflags: Set of `0 | OPENDEV_PART | OPENDEV_BLCK' */
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(LIBDCALL libd_opendev)(char const *path, oflag_t oflags, __STDC_INT_AS_UINT_T dflags, char **realpath);
/* Parse one line of text from `stream', whilst accounting for
 * special character escapes, as well as custom line-comments.
 * @param: plen:    When non-NULL, store `strlen(return)' here
 * @param: plineno: When non-NULL, incremented for every line-feed read from `stream'
 * @param: delim:   Special characters (use NUL to disable, and NULL to use defaults)
 *                     delim[0]: The escape character (defaults to '\\')
 *                     delim[1]: The line-continuation character (defaults to '\\')
 *                     delim[2]: The line-comment character (defaults to '#')
 * @param: flags:   Set of `FPARSELN_UNESC*'
 * @return: * : */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBDCALL libd_fparseln)(FILE *stream, size_t *plen, size_t *plineno, char const delim[3], __STDC_INT_AS_UINT_T flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Parse one line of text from `stream', whilst accounting for
 * special character escapes, as well as custom line-comments.
 * @param: plen:    When non-NULL, store `strlen(return)' here
 * @param: plineno: When non-NULL, incremented for every line-feed read from `stream'
 * @param: delim:   Special characters (use NUL to disable, and NULL to use defaults)
 *                     delim[0]: The escape character (defaults to '\\')
 *                     delim[1]: The line-continuation character (defaults to '\\')
 *                     delim[2]: The line-comment character (defaults to '#')
 * @param: flags:   Set of `FPARSELN_UNESC*'
 * @return: * : */
INTDEF WUNUSED NONNULL((1)) char *NOTHROW_RPC(LIBCCALL libc_fparseln)(FILE *stream, size_t *plen, size_t *plineno, char const delim[3], __STDC_INT_AS_UINT_T flags);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_UTIL_H */
