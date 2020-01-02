/* HASH CRC-32:0x7db470a8 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBC_ERROR_H
#define _LIBC_ERROR_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/error.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include "slow/error.h"

#ifndef ____libc_error_defined
#define ____libc_error_defined 1
#ifdef __fast_error_defined
/* Helper function for printing an error message to `stderr' and possibly exiting the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `STATUS' is non-zero, follow up with a call to `exit(status)' */
#define __libc_error (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(error))
#elif defined(____libc_slow_error_defined)
/* Helper function for printing an error message to `stderr' and possibly exiting the program
 * The message is printed as: `<program_invocation_short_name>: <format...>[: <strerror(errnum)>]\n'
 * Also note that `stdout' is flushed before the message is printed.
 * If `STATUS' is non-zero, follow up with a call to `exit(status)' */
#define __libc_error __libc_slow_error
#else /* error... */
#undef ____libc_error_defined
#endif /* !error... */
#endif /* !____libc_error_defined */
#ifndef ____libc_error_at_line_defined
#define ____libc_error_at_line_defined 1
#ifdef __fast_error_at_line_defined
/* Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally, when `error_one_per_line' is non-zero, consecutive calls to this function that
 * pass the same values for `filename' and `line' will not produce the error message. */
#define __libc_error_at_line (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(error_at_line))
#elif defined(____libc_slow_error_at_line_defined)
/* Same as `error()', but also include the given filename in the error message.
 * The message is printed as: `<program_invocation_short_name>:<filename>:<line>: <format...>[: <strerror(errnum)>]\n'
 * Additionally, when `error_one_per_line' is non-zero, consecutive calls to this function that
 * pass the same values for `filename' and `line' will not produce the error message. */
#define __libc_error_at_line __libc_slow_error_at_line
#else /* error_at_line... */
#undef ____libc_error_at_line_defined
#endif /* !error_at_line... */
#endif /* !____libc_error_at_line_defined */

#endif /* __CC__ */

#endif /* !_LIBC_ERROR_H */
