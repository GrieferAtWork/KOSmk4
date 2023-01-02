/* HASH CRC-32:0x4ab1835 */
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
#ifndef GUARD_LIBC_AUTO_EXECINFO_H
#define GUARD_LIBC_AUTO_EXECINFO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <execinfo.h>

DECL_BEGIN

#include <format-printer.h>
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> backtrace(3)
 * Create a  traceback of  up to  `size' instruction  pointers  from
 * the  calling function, their  caller, and so  forth. On KOS, this
 * information is constructed with the help of CFI  instrumentation,
 * and  the  functions  from  `<libunwind/...>'.  However,  on other
 * systems, this function is fairly dumb and relies on all traversed
 * code having been compiled with function frames enabled.
 * @return: * : The actual number of pointers written to `array' (always `<= size') */
INTDEF ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBDCALL libd_backtrace)(void **array, __STDC_INT_AS_SIZE_T size);
/* >> backtrace_symbols(3)
 * Same as `backtrace_symbols_fmt(array, size, NULL)'
 *
 * The returned  pointer is  a size-element  long vector  of  strings
 * describing the  addresses  from  `array', and  should  be  freed()
 * using `free(3)'. Note however that you must _ONLY_ `free(return)',
 * and not the individual strings pointed-to by that vector!
 * @return: * :   A heap pointer to a vector of function names
 * @return: NULL: Insufficient heap memory available */
INTDEF ATTR_INS(1, 2) char **NOTHROW_NCX(LIBDCALL libd_backtrace_symbols)(void *const *array, __STDC_INT_AS_SIZE_T size);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> backtrace_symbols(3)
 * Same as `backtrace_symbols_fmt(array, size, NULL)'
 *
 * The returned  pointer is  a size-element  long vector  of  strings
 * describing the  addresses  from  `array', and  should  be  freed()
 * using `free(3)'. Note however that you must _ONLY_ `free(return)',
 * and not the individual strings pointed-to by that vector!
 * @return: * :   A heap pointer to a vector of function names
 * @return: NULL: Insufficient heap memory available */
INTDEF ATTR_INS(1, 2) char **NOTHROW_NCX(LIBCCALL libc_backtrace_symbols)(void *const *array, __STDC_INT_AS_SIZE_T size);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> backtrace_symbols_fd(3)
 * Same as `backtrace_symbols_fd_fmt(array, size, fd, NULL)'
 * @return: 0 : Success
 * @return: -1: Error */
INTDEF ATTR_INS(1, 2) int NOTHROW_NCX(LIBDCALL libd_backtrace_symbols_fd)(void *const *array, __STDC_INT_AS_SIZE_T size, fd_t fd);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> backtrace_symbols_fd(3)
 * Same as `backtrace_symbols_fd_fmt(array, size, fd, NULL)'
 * @return: 0 : Success
 * @return: -1: Error */
INTDEF ATTR_INS(1, 2) int NOTHROW_NCX(LIBCCALL libc_backtrace_symbols_fd)(void *const *array, __STDC_INT_AS_SIZE_T size, fd_t fd);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
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
INTDEF ATTR_INS(1, 2) ATTR_IN_OPT(3) char **NOTHROW_NCX(LIBDCALL libd_backtrace_symbols_fmt)(void *const *array, __STDC_INT_AS_SIZE_T size, char const *format);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
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
INTDEF ATTR_INS(1, 2) ATTR_IN_OPT(3) char **NOTHROW_NCX(LIBCCALL libc_backtrace_symbols_fmt)(void *const *array, __STDC_INT_AS_SIZE_T size, char const *format);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> backtrace_symbols_fd_fmt(3)
 * Same as `backtrace_symbols_fmt()', but rather than return a vector
 * of  symbol  names, print  the names  directly  to `fd',  such that
 * one function  name will  be written  per line,  with `size'  lines
 * written in total.
 * @return: 0 : Success
 * @return: -1: Error */
INTDEF ATTR_INS(1, 2) ATTR_IN_OPT(4) int NOTHROW_NCX(LIBDCALL libd_backtrace_symbols_fd_fmt)(void *const *array, __STDC_INT_AS_SIZE_T size, fd_t fd, char const *format);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> backtrace_symbols_fd_fmt(3)
 * Same as `backtrace_symbols_fmt()', but rather than return a vector
 * of  symbol  names, print  the names  directly  to `fd',  such that
 * one function  name will  be written  per line,  with `size'  lines
 * written in total.
 * @return: 0 : Success
 * @return: -1: Error */
INTDEF ATTR_INS(1, 2) ATTR_IN_OPT(4) int NOTHROW_NCX(LIBCCALL libc_backtrace_symbols_fd_fmt)(void *const *array, __STDC_INT_AS_SIZE_T size, fd_t fd, char const *format);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> backtrace_symbol_printf(3)
 * Print the formatted representation of `address' to `printer'
 *  - The used format is `format' (or "%a <%n%D> at %f" if NULL)
 *  - No trailing linefeed is printed
 *  - If debug information could not be loaded, use "???" for strings
 * @return: * : pformatprinter-compatible return value */
INTDEF ATTR_IN_OPT(4) NONNULL((1)) ssize_t NOTHROW_NCX(LIBDCALL libd_backtrace_symbol_printf)(pformatprinter printer, void *arg, void const *address, char const *format);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_EXECINFO_H */
