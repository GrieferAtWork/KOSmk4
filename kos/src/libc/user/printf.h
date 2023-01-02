/* HASH CRC-32:0xf36240ea */
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
#ifndef GUARD_LIBC_USER_PRINTF_H
#define GUARD_LIBC_USER_PRINTF_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <printf.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> register_printf_specifier(3), register_printf_function(3)
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_register_printf_specifier)(__STDC_INT_AS_UINT_T spec, printf_function *func, printf_arginfo_size_function *arginfo);
/* >> register_printf_specifier(3), register_printf_function(3)
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_register_printf_function)(__STDC_INT_AS_UINT_T spec, printf_function *func, printf_arginfo_function *arginfo);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_register_printf_modifier)(__WCHAR32_TYPE__ const *str);
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_register_printf_type)(printf_va_arg_function *fct);
INTDEF ATTR_OUTS(3, 2) NONNULL((1)) size_t NOTHROW_NCX(LIBCCALL libc_parse_printf_format)(char const *__restrict fmt, size_t n, int *__restrict argtypes);
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc_printf_size)(FILE *__restrict fp, struct printf_info const *info, void const *const *__restrict args);
INTDEF NONNULL((1, 3)) int NOTHROW_NCX(LIBCCALL libc_printf_size_info)(struct printf_info const *__restrict info, size_t n, int *__restrict argtypes);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_PRINTF_H */
