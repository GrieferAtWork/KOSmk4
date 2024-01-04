/* HASH CRC-32:0xf3ad1721 */
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
#ifndef GUARD_LIBC_AUTO_UTIL_H
#define GUARD_LIBC_AUTO_UTIL_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <util.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> opendev(3)
 * @param: dflags: Set of `0 | OPENDEV_PART | OPENDEV_BLCK' */
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT_OPT(4) fd_t NOTHROW_RPC(LIBDCALL libd_opendev)(char const *path, oflag_t oflags, __STDC_INT_AS_UINT_T dflags, char **realpath);
/* >> fparseln(3)
 * Parse one line of text from `stream', whilst accounting for
 * special character escapes, as well as custom line-comments.
 * @param: plen:    When non-NULL, store `strlen(return)' here
 * @param: plineno: When non-NULL, incremented for every line-feed read from `stream'
 * @param: delim:   Special characters (use NUL to disable, and NULL to use defaults)
 *                     delim[0]: The escape character (defaults to '\\')
 *                     delim[1]: The line-continuation character (defaults to '\\')
 *                     delim[2]: The line-comment character (defaults to '#')
 * @param: flags:   Set of `FPARSELN_UNESC*'
 * @return: * :     Pointer to a heap-allocated, and pre-escaped (according to `flags')
 *                  line,  that must  be `free(3)'ed by  the caller once  they are done
 *                  using it.
 *                  If the result would be empty  as the result of `feof(stream)'  upon
 *                  return of this function, `strdup("")' will be returned. (i.e.  NULL
 *                  is only returned in case of an error; _NOT_ in case of end-of-file)
 * @return: NULL:   Error (s.a. `errno' and `ferror(stream)') */
INTDEF WUNUSED ATTR_INOUT(1) ATTR_INOUT_OPT(3) ATTR_IN_OPT(4) ATTR_OUT_OPT(2) char *NOTHROW_CB_NCX(LIBDCALL libd_fparseln)(FILE *stream, size_t *plen, size_t *plineno, char const delim[3], __STDC_INT_AS_UINT_T flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fparseln(3)
 * Parse one line of text from `stream', whilst accounting for
 * special character escapes, as well as custom line-comments.
 * @param: plen:    When non-NULL, store `strlen(return)' here
 * @param: plineno: When non-NULL, incremented for every line-feed read from `stream'
 * @param: delim:   Special characters (use NUL to disable, and NULL to use defaults)
 *                     delim[0]: The escape character (defaults to '\\')
 *                     delim[1]: The line-continuation character (defaults to '\\')
 *                     delim[2]: The line-comment character (defaults to '#')
 * @param: flags:   Set of `FPARSELN_UNESC*'
 * @return: * :     Pointer to a heap-allocated, and pre-escaped (according to `flags')
 *                  line,  that must  be `free(3)'ed by  the caller once  they are done
 *                  using it.
 *                  If the result would be empty  as the result of `feof(stream)'  upon
 *                  return of this function, `strdup("")' will be returned. (i.e.  NULL
 *                  is only returned in case of an error; _NOT_ in case of end-of-file)
 * @return: NULL:   Error (s.a. `errno' and `ferror(stream)') */
INTDEF WUNUSED ATTR_INOUT(1) ATTR_INOUT_OPT(3) ATTR_IN_OPT(4) ATTR_OUT_OPT(2) char *NOTHROW_CB_NCX(LIBCCALL libc_fparseln)(FILE *stream, size_t *plen, size_t *plineno, char const delim[3], __STDC_INT_AS_UINT_T flags);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_UTIL_H */
