/* HASH CRC-32:0xafea8742 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_STDBIT_H
#define GUARD_LIBC_AUTO_STDBIT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <stdbit.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_leading_zeros_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_leading_zeros_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_leading_zeros_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_leading_zeros_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_leading_zeros_ui)(unsigned int x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_leading_zeros_ui)(unsigned int x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_leading_zeros_ul)(unsigned long x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_leading_zeros_ul)(unsigned long x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_leading_ones_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_leading_ones_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_leading_ones_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_leading_ones_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_leading_ones_ui)(unsigned int x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_leading_ones_ui)(unsigned int x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_leading_ones_ul)(unsigned long x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_leading_ones_ul)(unsigned long x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_trailing_zeros_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_trailing_zeros_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_trailing_zeros_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_trailing_zeros_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_trailing_zeros_ui)(unsigned int x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_trailing_zeros_ui)(unsigned int x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_trailing_zeros_ul)(unsigned long x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_trailing_zeros_ul)(unsigned long x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_trailing_ones_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_trailing_ones_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_trailing_ones_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_trailing_ones_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_trailing_ones_ui)(unsigned int x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_trailing_ones_ui)(unsigned int x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_trailing_ones_ul)(unsigned long x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_trailing_ones_ul)(unsigned long x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_leading_one_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_leading_one_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_leading_one_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_leading_one(3) (type-generic)
 * >> stdc_first_leading_one_uc(3), stdc_first_leading_one_us(3), stdc_first_leading_one_ui(3)
 * >> stdc_first_leading_one_ul(3), stdc_first_leading_one_ull(3)
 * Find first set (1-based, returning `0' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_leading_one_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_leading_zero_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_leading_zero_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_leading_zero_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_leading_zero_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_leading_zero_ui)(unsigned int x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_leading_zero_ui)(unsigned int x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_leading_zero_ul)(unsigned long x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_leading_zero_ul)(unsigned long x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_trailing_zero_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_trailing_zero_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_trailing_zero_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_trailing_zero_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_trailing_zero_ui)(unsigned int x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_trailing_zero_ui)(unsigned int x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_trailing_zero_ul)(unsigned long x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_trailing_zero_ul)(unsigned long x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_trailing_one_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_trailing_one_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_trailing_one_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_trailing_one_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_trailing_one_ui)(unsigned int x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_trailing_one_ui)(unsigned int x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_trailing_one_ul)(unsigned long x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_trailing_one_ul)(unsigned long x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_count_ones_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_count_ones_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_count_ones_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_count_ones(3) (type-generic)
 * >> stdc_count_ones_uc(3), stdc_count_ones_us(3), stdc_count_ones_ui(3)
 * >> stdc_count_ones_ul(3), stdc_count_ones_ull(3)
 * Popcount */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_count_ones_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_count_zeros_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_count_zeros_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_count_zeros_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_count_zeros_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_count_zeros_ui)(unsigned int x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_count_zeros_ui)(unsigned int x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_count_zeros_ul)(unsigned long x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_count_zeros_ul)(unsigned long x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTDEF ATTR_CONST WUNUSED bool NOTHROW(LIBDCALL libd_stdc_has_single_bit_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTDEF ATTR_CONST WUNUSED bool NOTHROW(LIBCCALL libc_stdc_has_single_bit_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTDEF ATTR_CONST WUNUSED bool NOTHROW(LIBDCALL libd_stdc_has_single_bit_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTDEF ATTR_CONST WUNUSED bool NOTHROW(LIBCCALL libc_stdc_has_single_bit_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTDEF ATTR_CONST WUNUSED bool NOTHROW(LIBDCALL libd_stdc_has_single_bit_ui)(unsigned int x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTDEF ATTR_CONST WUNUSED bool NOTHROW(LIBCCALL libc_stdc_has_single_bit_ui)(unsigned int x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTDEF ATTR_CONST WUNUSED bool NOTHROW(LIBDCALL libd_stdc_has_single_bit_ul)(unsigned long x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTDEF ATTR_CONST WUNUSED bool NOTHROW(LIBCCALL libc_stdc_has_single_bit_ul)(unsigned long x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_bit_width_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_bit_width_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_bit_width_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_bit_width_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_bit_width_ui)(unsigned int x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_bit_width_ui)(unsigned int x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_bit_width_ul)(unsigned long x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_bit_width_ul)(unsigned long x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTDEF ATTR_CONST WUNUSED unsigned char NOTHROW(LIBDCALL libd_stdc_bit_floor_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTDEF ATTR_CONST WUNUSED unsigned char NOTHROW(LIBCCALL libc_stdc_bit_floor_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTDEF ATTR_CONST WUNUSED unsigned short NOTHROW(LIBDCALL libd_stdc_bit_floor_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTDEF ATTR_CONST WUNUSED unsigned short NOTHROW(LIBCCALL libc_stdc_bit_floor_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_bit_floor_ui)(unsigned int x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_bit_floor_ui)(unsigned int x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTDEF ATTR_CONST WUNUSED unsigned long NOTHROW(LIBDCALL libd_stdc_bit_floor_ul)(unsigned long x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTDEF ATTR_CONST WUNUSED unsigned long NOTHROW(LIBCCALL libc_stdc_bit_floor_ul)(unsigned long x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTDEF ATTR_CONST WUNUSED unsigned char NOTHROW(LIBDCALL libd_stdc_bit_ceil_uc)(unsigned char x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTDEF ATTR_CONST WUNUSED unsigned char NOTHROW(LIBCCALL libc_stdc_bit_ceil_uc)(unsigned char x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTDEF ATTR_CONST WUNUSED unsigned short NOTHROW(LIBDCALL libd_stdc_bit_ceil_us)(unsigned short x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTDEF ATTR_CONST WUNUSED unsigned short NOTHROW(LIBCCALL libc_stdc_bit_ceil_us)(unsigned short x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_bit_ceil_ui)(unsigned int x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_bit_ceil_ui)(unsigned int x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTDEF ATTR_CONST WUNUSED unsigned long NOTHROW(LIBDCALL libd_stdc_bit_ceil_ul)(unsigned long x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTDEF ATTR_CONST WUNUSED unsigned long NOTHROW(LIBCCALL libc_stdc_bit_ceil_ul)(unsigned long x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_leading_zeros_ull)(__ULONGLONG x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_leading_zeros(3) (type-generic)
 * >> stdc_leading_zeros_uc(3), stdc_leading_zeros_us(3), stdc_leading_zeros_ui(3)
 * >> stdc_leading_zeros_ul(3), stdc_leading_zeros_ull(3)
 * Count leading zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_leading_zeros_ull)(__ULONGLONG x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_leading_ones_ull)(__ULONGLONG x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_leading_ones(3) (type-generic)
 * >> stdc_leading_ones_uc(3), stdc_leading_ones_us(3), stdc_leading_ones_ui(3)
 * >> stdc_leading_ones_ul(3), stdc_leading_ones_ull(3)
 * Count leading ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_leading_ones_ull)(__ULONGLONG x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_trailing_zeros_ull)(__ULONGLONG x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_trailing_zeros(3) (type-generic)
 * >> stdc_trailing_zeros_uc(3), stdc_trailing_zeros_us(3), stdc_trailing_zeros_ui(3)
 * >> stdc_trailing_zeros_ul(3), stdc_trailing_zeros_ull(3)
 * Count trailing zeros (returning `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_trailing_zeros_ull)(__ULONGLONG x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_trailing_ones_ull)(__ULONGLONG x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_trailing_ones(3) (type-generic)
 * >> stdc_trailing_ones_uc(3), stdc_trailing_ones_us(3), stdc_trailing_ones_ui(3)
 * >> stdc_trailing_ones_ul(3), stdc_trailing_ones_ull(3)
 * Count trailing ones (returning `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_trailing_ones_ull)(__ULONGLONG x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_leading_zero_ull)(__ULONGLONG x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_leading_zero(3) (type-generic)
 * >> stdc_first_leading_zero_uc(3), stdc_first_leading_zero_us(3), stdc_first_leading_zero_ui(3)
 * >> stdc_first_leading_zero_ul(3), stdc_first_leading_zero_ull(3)
 * Find first clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_leading_zero_ull)(__ULONGLONG x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_trailing_zero_ull)(__ULONGLONG x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_trailing_zero(3) (type-generic)
 * >> stdc_first_trailing_zero_uc(3), stdc_first_trailing_zero_us(3), stdc_first_trailing_zero_ui(3)
 * >> stdc_first_trailing_zero_ul(3), stdc_first_trailing_zero_ull(3)
 * Find last clear (1-based, returning `0' when `x == (typeof(x))-1' and `sizeof(x) * CHAR_BIT' when `x == 0') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_trailing_zero_ull)(__ULONGLONG x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_first_trailing_one_ull)(__ULONGLONG x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_first_trailing_one(3) (type-generic)
 * >> stdc_first_trailing_one_uc(3), stdc_first_trailing_one_us(3), stdc_first_trailing_one_ui(3)
 * >> stdc_first_trailing_one_ul(3), stdc_first_trailing_one_ull(3)
 * Find last set (1-based, returning `0' when `x == 0' and `sizeof(x) * CHAR_BIT' when `x == (typeof(x))-1') */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_first_trailing_one_ull)(__ULONGLONG x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_count_zeros_ull)(__ULONGLONG x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_count_zeros(3) (type-generic)
 * >> stdc_count_zeros_uc(3), stdc_count_zeros_us(3), stdc_count_zeros_ui(3)
 * >> stdc_count_zeros_ul(3), stdc_count_zeros_ull(3)
 * Popcount (zeros) */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_count_zeros_ull)(__ULONGLONG x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTDEF ATTR_CONST WUNUSED bool NOTHROW(LIBDCALL libd_stdc_has_single_bit_ull)(__ULONGLONG x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_has_single_bit(3) (type-generic)
 * >> stdc_has_single_bit_uc(3), stdc_has_single_bit_us(3), stdc_has_single_bit_ui(3)
 * >> stdc_has_single_bit_ul(3), stdc_has_single_bit_ull(3)
 * Is power of 2 (and not zero) */
INTDEF ATTR_CONST WUNUSED bool NOTHROW(LIBCCALL libc_stdc_has_single_bit_ull)(__ULONGLONG x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBDCALL libd_stdc_bit_width_ull)(__ULONGLONG x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_width(3) (type-generic)
 * >> stdc_bit_width_uc(3), stdc_bit_width_us(3), stdc_bit_width_ui(3)
 * >> stdc_bit_width_ul(3), stdc_bit_width_ull(3)
 * Number of bits needed to represent `x' */
INTDEF ATTR_CONST WUNUSED unsigned int NOTHROW(LIBCCALL libc_stdc_bit_width_ull)(__ULONGLONG x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTDEF ATTR_CONST WUNUSED __ULONGLONG NOTHROW(LIBDCALL libd_stdc_bit_floor_ull)(__ULONGLONG x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_floor(3) (type-generic)
 * >> stdc_bit_floor_uc(3), stdc_bit_floor_us(3), stdc_bit_floor_ui(3)
 * >> stdc_bit_floor_ul(3), stdc_bit_floor_ull(3)
 * Mask for the most significant bit set in `x', or `0' when `x == 0' */
INTDEF ATTR_CONST WUNUSED __ULONGLONG NOTHROW(LIBCCALL libc_stdc_bit_floor_ull)(__ULONGLONG x);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTDEF ATTR_CONST WUNUSED __ULONGLONG NOTHROW(LIBDCALL libd_stdc_bit_ceil_ull)(__ULONGLONG x);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> stdc_bit_ceil(3) (type-generic)
 * >> stdc_bit_ceil_uc(3), stdc_bit_ceil_us(3), stdc_bit_ceil_ui(3)
 * >> stdc_bit_ceil_ul(3), stdc_bit_ceil_ull(3)
 * Returns the next power-of-2 that is `>= x' */
INTDEF ATTR_CONST WUNUSED __ULONGLONG NOTHROW(LIBCCALL libc_stdc_bit_ceil_ull)(__ULONGLONG x);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_STDBIT_H */
