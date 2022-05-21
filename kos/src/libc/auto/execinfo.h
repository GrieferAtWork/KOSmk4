/* HASH CRC-32:0x38e407ab */
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
#ifndef GUARD_LIBC_AUTO_EXECINFO_H
#define GUARD_LIBC_AUTO_EXECINFO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <execinfo.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> backtrace(3)
 * Create a  traceback of  up to  `size' instruction  pointers  from
 * the  calling function, their  caller, and so  forth. On KOS, this
 * information is constructed with the help of CFI  instrumentation,
 * and  the  functions  from  `<libunwind/...>'.  However,  on other
 * systems, this function is fairly dumb and relies on all traversed
 * code having been compiled with function frames enabled.
 * @return: * : The actual number of pointers written to `array' (always `<= size') */
INTDEF ATTR_ACCESS_WRS(1, 2) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_backtrace)(void **array, __STDC_INT_AS_SIZE_T size);
/* >> backtrace_symbols(3)
 * Return  an  array  of  exactly  `size'  elements  that  contains  the
 * names   associated  with  program-counters  from  the  given  `array'
 * This  function  is meant  to  be used  together  with `backtrace(3)'.
 * On KOS,  the  names  of  functions are  gathered  with  the  help  of
 * functions  from  `<libdebuginfo/...>', meaning  that many  sources of
 * function names are looked  at, including `.dynsym' and  `.debug_info'
 * On other systems,  this function  is fairly  dumb and  only looks  at
 * names from `.dynsym', meaning that functions not declared as `PUBLIC'
 * would not show up.
 * The returned pointer  is a size-element  long vector of  strings
 * describing the names of functions,  and should be freed()  using
 * `free(3)'. Note however that you must _ONLY_ `free(return)', and
 * not the individual strings pointed-to by that vector!
 * @return: * :   A heap pointer to a vector of function names
 * @return: NULL: Insufficient heap memory available */
INTDEF ATTR_ACCESS_ROS(1, 2) char **NOTHROW_NCX(LIBDCALL libd_backtrace_symbols)(void *const *array, __STDC_INT_AS_SIZE_T size);
/* >> backtrace_symbols_fd(3)
 * Same as `backtrace_symbols()', but rather than return a vector
 * of symbol names, print the  names directly to `fd', such  that
 * one  function name will be written per line, with `size' lines
 * written in total. */
INTDEF ATTR_ACCESS_ROS(1, 2) void NOTHROW_NCX(LIBDCALL libd_backtrace_symbols_fd)(void *const *array, __STDC_INT_AS_SIZE_T size, fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_EXECINFO_H */
