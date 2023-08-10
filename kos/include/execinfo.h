/* HASH CRC-32:0x71fcb21e */
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
/* (#) Portability: GNU C Library (/debug/execinfo.h) */
/* (#) Portability: GNU Hurd      (/usr/include/execinfo.h) */
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

#include <features.h>
#include <bits/types.h>

#ifdef __USE_KOS
#include <bits/crt/format-printer.h>
#endif /* __USE_KOS */

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
 * Same as `backtrace_symbols_fmt(array, size, NULL)'
 *
 * The returned  pointer is  a size-element  long vector  of  strings
 * describing the  addresses  from  `array', and  should  be  freed()
 * using `free(3)'. Note however that you must _ONLY_ `free(return)',
 * and not the individual strings pointed-to by that vector!
 * @return: * :   A heap pointer to a vector of function names
 * @return: NULL: Insufficient heap memory available */
__CDECLARE(__ATTR_INS(1, 2),char **,__NOTHROW_NCX,backtrace_symbols,(void *const *__array, __STDC_INT_AS_SIZE_T __size),(__array,__size))
#elif defined(__CRT_HAVE___backtrace_symbols)
/* >> backtrace_symbols(3)
 * Same as `backtrace_symbols_fmt(array, size, NULL)'
 *
 * The returned  pointer is  a size-element  long vector  of  strings
 * describing the  addresses  from  `array', and  should  be  freed()
 * using `free(3)'. Note however that you must _ONLY_ `free(return)',
 * and not the individual strings pointed-to by that vector!
 * @return: * :   A heap pointer to a vector of function names
 * @return: NULL: Insufficient heap memory available */
__CREDIRECT(__ATTR_INS(1, 2),char **,__NOTHROW_NCX,backtrace_symbols,(void *const *__array, __STDC_INT_AS_SIZE_T __size),__backtrace_symbols,(__array,__size))
#elif defined(__CRT_HAVE_backtrace_symbols_fmt) || (defined(__CRT_HAVE_backtrace_symbol_printf) && (defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/execinfo/backtrace_symbols.h>
/* >> backtrace_symbols(3)
 * Same as `backtrace_symbols_fmt(array, size, NULL)'
 *
 * The returned  pointer is  a size-element  long vector  of  strings
 * describing the  addresses  from  `array', and  should  be  freed()
 * using `free(3)'. Note however that you must _ONLY_ `free(return)',
 * and not the individual strings pointed-to by that vector!
 * @return: * :   A heap pointer to a vector of function names
 * @return: NULL: Insufficient heap memory available */
__NAMESPACE_LOCAL_USING_OR_IMPL(backtrace_symbols, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(1, 2) char **__NOTHROW_NCX(__LIBCCALL backtrace_symbols)(void *const *__array, __STDC_INT_AS_SIZE_T __size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(backtrace_symbols))(__array, __size); })
#endif /* ... */
#ifdef __CRT_HAVE_backtrace_symbols_fd
/* >> backtrace_symbols_fd(3)
 * Same as `backtrace_symbols_fd_fmt(array, size, fd, NULL)'
 * @return: 0 : Success
 * @return: -1: Error */
__CDECLARE(__ATTR_FDWRITE(3) __ATTR_INS(1, 2),int,__NOTHROW_NCX,backtrace_symbols_fd,(void *const *__array, __STDC_INT_AS_SIZE_T __size, __fd_t __fd),(__array,__size,__fd))
#elif defined(__CRT_HAVE___backtrace_symbols_fd)
/* >> backtrace_symbols_fd(3)
 * Same as `backtrace_symbols_fd_fmt(array, size, fd, NULL)'
 * @return: 0 : Success
 * @return: -1: Error */
__CREDIRECT(__ATTR_FDWRITE(3) __ATTR_INS(1, 2),int,__NOTHROW_NCX,backtrace_symbols_fd,(void *const *__array, __STDC_INT_AS_SIZE_T __size, __fd_t __fd),__backtrace_symbols_fd,(__array,__size,__fd))
#else /* ... */
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if defined(__CRT_HAVE_backtrace_symbols_fd_fmt) || ((defined(__CRT_HAVE_write_printer) || defined(__CRT_HAVE_writeall) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__CRT_HAVE_backtrace_symbol_printf))
#include <libc/local/execinfo/backtrace_symbols_fd.h>
/* >> backtrace_symbols_fd(3)
 * Same as `backtrace_symbols_fd_fmt(array, size, fd, NULL)'
 * @return: 0 : Success
 * @return: -1: Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(backtrace_symbols_fd, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(3) __ATTR_INS(1, 2) int __NOTHROW_NCX(__LIBCCALL backtrace_symbols_fd)(void *const *__array, __STDC_INT_AS_SIZE_T __size, __fd_t __fd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(backtrace_symbols_fd))(__array, __size, __fd); })
#endif /* __CRT_HAVE_backtrace_symbols_fd_fmt || ((__CRT_HAVE_write_printer || __CRT_HAVE_writeall || __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && __CRT_HAVE_backtrace_symbol_printf) */
#endif /* !... */
#ifdef __CRT_HAVE_backtrace_symbols_fmt
/* >> backtrace_symbols_fmt(3)
 * Format the given `array' of addresses into backtrace strings,
 * where   each  line  is  constructed  according  to  `format':
 *  - '%a': printf("%p", array[i])
 *  - '%n': printf("%s", NAME_OF_CONTAINING_FUNCTION(array[i]))
 *  - '%d': off = array[i] - START_OF_CONTAINING_FUNCTION(array[i]); printf("%#tx", off)
 *  - '%D': off = array[i] - START_OF_CONTAINING_FUNCTION(array[i]); if (off) printf("%+#tx", off)
 *  - '%f': printf("%s", dlmodulename(dlgethandle(array[i])))
 *  - '%%': A single '%'
 *  - ...:  Anything else is copied from `format' as-is.
 * When `format == NULL', use "%a <%n%D> at %f" instead
 *
 * The returned  pointer is  a size-element  long vector  of  strings
 * describing the  addresses  from  `array', and  should  be  freed()
 * using `free(3)'. Note however that you must _ONLY_ `free(return)',
 * and not the individual strings pointed-to by that vector!
 * @return: * :   A heap pointer to a vector of function names
 * @return: NULL: Insufficient heap memory available */
__CDECLARE(__ATTR_INS(1, 2) __ATTR_IN_OPT(3),char **,__NOTHROW_NCX,backtrace_symbols_fmt,(void *const *__array, __STDC_INT_AS_SIZE_T __size, char const *__format),(__array,__size,__format))
#elif defined(__CRT_HAVE___backtrace_symbols)
/* >> backtrace_symbols_fmt(3)
 * Format the given `array' of addresses into backtrace strings,
 * where   each  line  is  constructed  according  to  `format':
 *  - '%a': printf("%p", array[i])
 *  - '%n': printf("%s", NAME_OF_CONTAINING_FUNCTION(array[i]))
 *  - '%d': off = array[i] - START_OF_CONTAINING_FUNCTION(array[i]); printf("%#tx", off)
 *  - '%D': off = array[i] - START_OF_CONTAINING_FUNCTION(array[i]); if (off) printf("%+#tx", off)
 *  - '%f': printf("%s", dlmodulename(dlgethandle(array[i])))
 *  - '%%': A single '%'
 *  - ...:  Anything else is copied from `format' as-is.
 * When `format == NULL', use "%a <%n%D> at %f" instead
 *
 * The returned  pointer is  a size-element  long vector  of  strings
 * describing the  addresses  from  `array', and  should  be  freed()
 * using `free(3)'. Note however that you must _ONLY_ `free(return)',
 * and not the individual strings pointed-to by that vector!
 * @return: * :   A heap pointer to a vector of function names
 * @return: NULL: Insufficient heap memory available */
__CREDIRECT(__ATTR_INS(1, 2) __ATTR_IN_OPT(3),char **,__NOTHROW_NCX,backtrace_symbols_fmt,(void *const *__array, __STDC_INT_AS_SIZE_T __size, char const *__format),__backtrace_symbols,(__array,__size,__format))
#elif defined(__CRT_HAVE_backtrace_symbol_printf) && (defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/execinfo/backtrace_symbols_fmt.h>
/* >> backtrace_symbols_fmt(3)
 * Format the given `array' of addresses into backtrace strings,
 * where   each  line  is  constructed  according  to  `format':
 *  - '%a': printf("%p", array[i])
 *  - '%n': printf("%s", NAME_OF_CONTAINING_FUNCTION(array[i]))
 *  - '%d': off = array[i] - START_OF_CONTAINING_FUNCTION(array[i]); printf("%#tx", off)
 *  - '%D': off = array[i] - START_OF_CONTAINING_FUNCTION(array[i]); if (off) printf("%+#tx", off)
 *  - '%f': printf("%s", dlmodulename(dlgethandle(array[i])))
 *  - '%%': A single '%'
 *  - ...:  Anything else is copied from `format' as-is.
 * When `format == NULL', use "%a <%n%D> at %f" instead
 *
 * The returned  pointer is  a size-element  long vector  of  strings
 * describing the  addresses  from  `array', and  should  be  freed()
 * using `free(3)'. Note however that you must _ONLY_ `free(return)',
 * and not the individual strings pointed-to by that vector!
 * @return: * :   A heap pointer to a vector of function names
 * @return: NULL: Insufficient heap memory available */
__NAMESPACE_LOCAL_USING_OR_IMPL(backtrace_symbols_fmt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(1, 2) __ATTR_IN_OPT(3) char **__NOTHROW_NCX(__LIBCCALL backtrace_symbols_fmt)(void *const *__array, __STDC_INT_AS_SIZE_T __size, char const *__format) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(backtrace_symbols_fmt))(__array, __size, __format); })
#endif /* ... */
#ifdef __CRT_HAVE_backtrace_symbols_fd_fmt
/* >> backtrace_symbols_fd_fmt(3)
 * Same as `backtrace_symbols_fmt()', but rather than return a vector
 * of  symbol  names, print  the names  directly  to `fd',  such that
 * one function  name will  be written  per line,  with `size'  lines
 * written in total.
 * @return: 0 : Success
 * @return: -1: Error */
__CDECLARE(__ATTR_FDWRITE(3) __ATTR_INS(1, 2) __ATTR_IN_OPT(4),int,__NOTHROW_NCX,backtrace_symbols_fd_fmt,(void *const *__array, __STDC_INT_AS_SIZE_T __size, __fd_t __fd, char const *__format),(__array,__size,__fd,__format))
#elif defined(__CRT_HAVE___backtrace_symbols_fd)
/* >> backtrace_symbols_fd_fmt(3)
 * Same as `backtrace_symbols_fmt()', but rather than return a vector
 * of  symbol  names, print  the names  directly  to `fd',  such that
 * one function  name will  be written  per line,  with `size'  lines
 * written in total.
 * @return: 0 : Success
 * @return: -1: Error */
__CREDIRECT(__ATTR_FDWRITE(3) __ATTR_INS(1, 2) __ATTR_IN_OPT(4),int,__NOTHROW_NCX,backtrace_symbols_fd_fmt,(void *const *__array, __STDC_INT_AS_SIZE_T __size, __fd_t __fd, char const *__format),__backtrace_symbols_fd,(__array,__size,__fd,__format))
#else /* ... */
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if (defined(__CRT_HAVE_write_printer) || defined(__CRT_HAVE_writeall) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__CRT_HAVE_backtrace_symbol_printf)
#include <libc/local/execinfo/backtrace_symbols_fd_fmt.h>
/* >> backtrace_symbols_fd_fmt(3)
 * Same as `backtrace_symbols_fmt()', but rather than return a vector
 * of  symbol  names, print  the names  directly  to `fd',  such that
 * one function  name will  be written  per line,  with `size'  lines
 * written in total.
 * @return: 0 : Success
 * @return: -1: Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(backtrace_symbols_fd_fmt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDWRITE(3) __ATTR_INS(1, 2) __ATTR_IN_OPT(4) int __NOTHROW_NCX(__LIBCCALL backtrace_symbols_fd_fmt)(void *const *__array, __STDC_INT_AS_SIZE_T __size, __fd_t __fd, char const *__format) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(backtrace_symbols_fd_fmt))(__array, __size, __fd, __format); })
#endif /* (__CRT_HAVE_write_printer || __CRT_HAVE_writeall || __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && __CRT_HAVE_backtrace_symbol_printf */
#endif /* !... */

#ifdef __USE_KOS
#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */
/* >> backtrace_symbol_printf(3)
 * Print the formatted representation of `address' to `printer'
 *  - The used format is `format' (or "%a <%n%D> at %f" if NULL)
 *  - No trailing linefeed is printed
 *  - If debug information could not be loaded, use "???" for strings
 * @return: * : pformatprinter-compatible return value */
__CDECLARE_OPT(__ATTR_IN_OPT(4) __ATTR_NONNULL((1)),ssize_t,__NOTHROW_NCX,backtrace_symbol_printf,(__pformatprinter __printer, void *__arg, void const *__address, char const *__format),(__printer,__arg,__address,__format))
#endif /* __USE_KOS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_EXECINFO_H */
