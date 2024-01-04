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
#ifndef _LIBCMDLINE_ENCODE_H
#define _LIBCMDLINE_ENCODE_H 1

#include "api.h"
/**/

#include <bits/crt/format-printer.h>
#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN


/* Encode  the  given `arg_start'  argument by  escaping characters
 * that would  confuse  the  commandline  decoder,  and  print  the
 * resulting   string   using  the   given  `printer'   with  `arg'
 * The caller is still responsible to insert space-separators  with
 * a width of at least  1 space-character (' ') between  successive
 * arguments. Alternatively, you may also use `cmdline_encode()' to
 * encode an entire commandline at once.
 * @return: * : The sum of return values of `printer'
 * @return: <0: The propagation of the first negative return value of `printer' (if any) */
typedef __ATTR_NONNULL_T((1, 3)) __ssize_t
(LIBCMDLINE_CC *PCMDLINE_ENCODE_ARGUMENT)(__pformatprinter printer, void *arg,
                                          char const *arg_start, __size_t arg_len);
#ifdef LIBCMDLINE_WANT_PROTOTYPES
LIBCMDLINE_DECL __ATTR_NONNULL((1, 3)) __ssize_t LIBCMDLINE_CC
cmdline_encode_argument(__pformatprinter printer, void *arg,
                        char const *arg_start, __size_t arg_len);
#endif /* LIBCMDLINE_WANT_PROTOTYPES */

/* Encode an entire commandline given by `argc' pointers found within
 * the  given  `argv'   vector.  (s.a.   `cmdline_encode_argument()')
 * @return: * : The sum of return values of `printer'
 * @return: <0: The propagation of the first negative return value of `printer' (if any) */
typedef __ATTR_NONNULL_T((1, 4)) __ssize_t
(LIBCMDLINE_CC *PCMDLINE_ENCODE)(__pformatprinter printer, void *arg,
                                 __size_t argc, char const *const *argv);
#ifdef LIBCMDLINE_WANT_PROTOTYPES
LIBCMDLINE_DECL __ATTR_NONNULL((1, 4)) __ssize_t LIBCMDLINE_CC
cmdline_encode(__pformatprinter printer, void *arg,
               __size_t argc, char const *const *argv);
#endif /* LIBCMDLINE_WANT_PROTOTYPES */



__DECL_END
#endif /* __CC__ */

#endif /* !_LIBCMDLINE_ENCODE_H */
