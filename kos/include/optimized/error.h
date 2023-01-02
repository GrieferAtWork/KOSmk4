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
#ifndef _OPTIMIZED_ERROR_H
#define _OPTIMIZED_ERROR_H 1

#include <__stdinc.h>

#if (!defined(__NO_ATTR_FORCEINLINE) &&   \
     !defined(__NO_builtin_constant_p) && \
     __has_builtin(__builtin_va_arg_pack))
#include <libc/core/error.h>

__SYSDECL_BEGIN
__NAMESPACE_FAST_BEGIN

#if !defined(__fast_error_defined) && defined(____libc_slow_error_defined)
#define __fast_error_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(3, 4) void
(__VLIBCCALL __LIBC_FAST_NAME(error))(int __status, __errno_t __errnum,
                                      const char *__format, ...) {
	__libc_slow_error(__status, __errnum, __format, __builtin_va_arg_pack());
	/* Allow the compiler to detect the error() calls that don't return. */
	if __untraced(__builtin_constant_p(__status) && __status != 0)
		__builtin_unreachable();
}
#endif /* !__fast_error_defined && ____libc_slow_error_defined */

#if !defined(__fast_error_at_line_defined) && defined(____libc_slow_error_at_line_defined)
#define __fast_error_at_line_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_PRINTF(5, 6) void
(__VLIBCCALL __LIBC_FAST_NAME(error_at_line))(int __status, __errno_t __errnum,
                                              char const *__filename, unsigned int __line,
                                              char const *__format, ...) {
	__libc_slow_error_at_line(__status, __errnum, __filename, __line, __format, __builtin_va_arg_pack());
	/* Allow the compiler to detect the error_at_line() calls that don't return. */
	if __untraced(__builtin_constant_p(__status) && __status != 0)
		__builtin_unreachable();
}
#endif /* !__fast_error_at_line_defined && ____libc_slow_error_at_line_defined */

__NAMESPACE_FAST_END
__SYSDECL_END
#endif /* !__NO_ATTR_FORCEINLINE && !__NO_builtin_constant_p && __has_builtin(__builtin_va_arg_pack) */

#endif /* !_OPTIMIZED_ERROR_H */
