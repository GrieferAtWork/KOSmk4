/* HASH CRC-32:0x616e7022 */
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
/* (#) Portability: GNU C Library (/debug/execinfo.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/execinfo.h) */
/* (#) Portability: libc6         (/include/execinfo.h) */
/* (#) Portability: uClibc        (/include/execinfo.h) */
#ifndef _EXECINFO_H
#define _EXECINFO_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h> /* __STDC_INT_AS_UINT_T */

#include <bits/types.h> /* $fd_t */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_backtrace
/* >> backtrace(3)
 * Create a  traceback of  up to  `size' instruction  pointers  from
 * the  calling function, their  caller, and so  forth. On KOS, this
 * information is constructed with the help of CFI  instrumentation,
 * and  the  functions  from  `<libunwind/...>'.  However,  on other
 * systems, this function is fairly dumb and relies on all traversed
 * code having been compiled with function frames enabled.
 * @return: * : The actual number of pointers written to `array' (always `<= size') */
__CDECLARE(__ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,backtrace,(void **__array, __STDC_INT_AS_SIZE_T __size),(__array,__size))
#elif defined(__CRT_HAVE___backtrace)
/* >> backtrace(3)
 * Create a  traceback of  up to  `size' instruction  pointers  from
 * the  calling function, their  caller, and so  forth. On KOS, this
 * information is constructed with the help of CFI  instrumentation,
 * and  the  functions  from  `<libunwind/...>'.  However,  on other
 * systems, this function is fairly dumb and relies on all traversed
 * code having been compiled with function frames enabled.
 * @return: * : The actual number of pointers written to `array' (always `<= size') */
__CREDIRECT(__ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,backtrace,(void **__array, __STDC_INT_AS_SIZE_T __size),__backtrace,(__array,__size))
#endif /* ... */
#ifdef __CRT_HAVE_backtrace_symbols
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
__CDECLARE(__ATTR_INS(1, 2),char **,__NOTHROW_NCX,backtrace_symbols,(void *const *__array, __STDC_INT_AS_SIZE_T __size),(__array,__size))
#elif defined(__CRT_HAVE___backtrace_symbols)
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
__CREDIRECT(__ATTR_INS(1, 2),char **,__NOTHROW_NCX,backtrace_symbols,(void *const *__array, __STDC_INT_AS_SIZE_T __size),__backtrace_symbols,(__array,__size))
#endif /* ... */
#ifdef __CRT_HAVE_backtrace_symbols_fd
/* >> backtrace_symbols_fd(3)
 * Same as `backtrace_symbols()', but rather than return a vector
 * of symbol names, print the  names directly to `fd', such  that
 * one  function name will be written per line, with `size' lines
 * written in total. */
__CDECLARE_VOID(__ATTR_INS(1, 2),__NOTHROW_NCX,backtrace_symbols_fd,(void *const *__array, __STDC_INT_AS_SIZE_T __size, __fd_t __fd),(__array,__size,__fd))
#elif defined(__CRT_HAVE___backtrace_symbols_fd)
/* >> backtrace_symbols_fd(3)
 * Same as `backtrace_symbols()', but rather than return a vector
 * of symbol names, print the  names directly to `fd', such  that
 * one  function name will be written per line, with `size' lines
 * written in total. */
__CREDIRECT_VOID(__ATTR_INS(1, 2),__NOTHROW_NCX,backtrace_symbols_fd,(void *const *__array, __STDC_INT_AS_SIZE_T __size, __fd_t __fd),__backtrace_symbols_fd,(__array,__size,__fd))
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_EXECINFO_H */
