/* HASH CRC-32:0xc81e41e3 */
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
#ifndef GUARD_LIBC_AUTO_CONIO_H
#define GUARD_LIBC_AUTO_CONIO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <conio.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> _getch(3), _getch_nolock(3)
 * Read a character from the console, without echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__getch)(void);
/* >> _getch(3), _getch_nolock(3)
 * Read a character from the console, without echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__getch_nolock)(void);
/* >> _getche(3), _getche_nolock(3)
 * Read a character from the console, whilst also echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__getche)(void);
/* >> _getche(3), _getche_nolock(3)
 * Read a character from the console, whilst also echoing it on-screen
 * @return: * : The character read from the console
 * @return: -1: End-of-file on console */
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__getche_nolock)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd__putch)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc__putch)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd__putch_nolock)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc__putch_nolock)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd__ungetch)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc__ungetch)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd__ungetch_nolock)(int ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc__ungetch_nolock)(int ch);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) char *NOTHROW_NCX(LIBDCALL libd__cgets)(char *__restrict buf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc__cgets)(char *__restrict buf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBDCALL libd__cgets_s)(char *buf, size_t bufsize, size_t *__restrict p_readsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 3)) errno_t NOTHROW_NCX(LIBCCALL libc__cgets_s)(char *buf, size_t bufsize, size_t *__restrict p_readsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd__cputs)(char const *__restrict str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc__cputs)(char const *__restrict str);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___conio_common_vcprintf)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc___conio_common_vcprintf)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___conio_common_vcprintf_s)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc___conio_common_vcprintf_s)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___conio_common_vcprintf_p)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc___conio_common_vcprintf_p)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___conio_common_vcscanf)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc___conio_common_vcscanf)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcprintf_l)(char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcprintf_l)(char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcprintf_s_l)(char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcprintf_s_l)(char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcprintf_p_l)(char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcprintf_p_l)(char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcscanf_l)(char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcscanf_l)(char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcscanf_s_l)(char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcscanf_s_l)(char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcprintf)(char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcprintf)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcprintf_s)(char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcprintf_s)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcprintf_p)(char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcprintf_p)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcscanf)(char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcscanf)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcscanf_s)(char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcscanf_s)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cprintf)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cprintf)(char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cprintf_l)(char const *format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cprintf_l)(char const *format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cprintf_s)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cprintf_s)(char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cprintf_s_l)(char const *format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cprintf_s_l)(char const *format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cprintf_p)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cprintf_p)(char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cprintf_p_l)(char const *format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_LIBC_PRINTF_P(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cprintf_p_l)(char const *format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cscanf)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cscanf)(char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cscanf_l)(char const *format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cscanf_l)(char const *format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cscanf_s)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cscanf_s)(char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cscanf_s_l)(char const *format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cscanf_s_l)(char const *format, locale_t locale, ...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CONIO_H */
