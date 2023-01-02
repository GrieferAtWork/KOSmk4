/* HASH CRC-32:0x8e79341a */
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
INTDEF ATTR_INOUT(1) char *NOTHROW_NCX(LIBDCALL libd__cgets)(char *__restrict buf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_INOUT(1) char *NOTHROW_NCX(LIBCCALL libc__cgets)(char *__restrict buf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_OUT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__cgets_s)(char *buf, size_t bufsize, size_t *__restrict p_readsize);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_OUT(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__cgets_s)(char *buf, size_t bufsize, size_t *__restrict p_readsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd__cputs)(char const *__restrict str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc__cputs)(char const *__restrict str);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___conio_common_vcprintf)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc___conio_common_vcprintf)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___conio_common_vcprintf_s)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc___conio_common_vcprintf_s)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(2) ATTR_LIBC_PRINTF_P(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___conio_common_vcprintf_p)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(2) ATTR_LIBC_PRINTF_P(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc___conio_common_vcprintf_p)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(2) ATTR_LIBC_SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd___conio_common_vcscanf)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(2) ATTR_LIBC_SCANF(2, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc___conio_common_vcscanf)(uint64_t options, char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcprintf_l)(char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcprintf_l)(char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcprintf_s_l)(char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcprintf_s_l)(char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcprintf_p_l)(char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcprintf_p_l)(char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcscanf_l)(char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcscanf_l)(char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcscanf_s_l)(char const *format, locale_t locale, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcscanf_s_l)(char const *format, locale_t locale, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcprintf)(char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcprintf)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcprintf_s)(char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcprintf_s)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcprintf_p)(char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcprintf_p)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcscanf)(char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcscanf)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBDCALL libd__vcscanf_s)(char const *format, va_list args);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(LIBCCALL libc__vcscanf_s)(char const *format, va_list args);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cprintf)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cprintf)(char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cprintf_l)(char const *format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cprintf_l)(char const *format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cprintf_s)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cprintf_s)(char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cprintf_s_l)(char const *format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cprintf_s_l)(char const *format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cprintf_p)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cprintf_p)(char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cprintf_p_l)(char const *format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_LIBC_PRINTF_P(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cprintf_p_l)(char const *format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cscanf)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cscanf)(char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cscanf_l)(char const *format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cscanf_l)(char const *format, locale_t locale, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cscanf_s)(char const *format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 2) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cscanf_s)(char const *format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBDCALL libd__cscanf_s_l)(char const *format, locale_t locale, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) ATTR_LIBC_SCANF(1, 3) __STDC_INT_AS_SSIZE_T NOTHROW_NCX(VLIBCCALL libc__cscanf_s_l)(char const *format, locale_t locale, ...);
/* >> clreol(3)
 * Clear all cells from the cursor (inclusive) until the end
 * of the  current  line.  (s.a.  `AC_EL(ANSITTY_EL_AFTER)') */
INTDEF void NOTHROW_NCX(LIBCCALL libc_clreol)(void);
/* >> clrscr(3)
 * Clear the entire screen (s.a. `AC_ED(ANSITTY_CLS_ALL)') */
INTDEF void NOTHROW_NCX(LIBCCALL libc_clrscr)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> gotoxy(3)
 * Set the cursor {x,y} position (s.a. `AC_CUP(y, x)') */
INTDEF void NOTHROW_NCX(LIBDCALL libd_gotoxy)(int x, int y);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> gotoxy(3)
 * Set the cursor {x,y} position (s.a. `AC_CUP(y, x)') */
INTDEF void NOTHROW_NCX(LIBCCALL libc_gotoxy)(int x, int y);
/* >> delline(3)
 * Delete the line at the current cursor position, moving  the
 * screen contents underneath up one line. (s.a. `AC_DL("1")') */
INTDEF void NOTHROW_NCX(LIBCCALL libc_delline)(void);
/* >> insline(3)
 * Insert a blank line at the current cursor position, moving the
 * screen  contents underneath down one line. (s.a. `AC_IL("1")') */
INTDEF void NOTHROW_NCX(LIBCCALL libc_insline)(void);
/* >> highvideo(3)
 * Brighten text foreground color (s.a. `AC_FGBRIGHT') */
INTDEF void NOTHROW_NCX(LIBCCALL libc_highvideo)(void);
/* >> lowvideo(3)
 * Darken text foreground color (s.a. `AC_FGDARK') */
INTDEF void NOTHROW_NCX(LIBCCALL libc_lowvideo)(void);
/* >> normvideo(3)
 * Reset all graphics attributes to normal (s.a. `AC_DEFATTR') */
INTDEF void NOTHROW_NCX(LIBCCALL libc_normvideo)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> textcolor(3)
 * @param: color: Color code (s.a. constants in `<conio.h>') */
INTDEF void NOTHROW_NCX(LIBDCALL libd_textcolor)(int color);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> textcolor(3)
 * @param: color: Color code (s.a. constants in `<conio.h>') */
INTDEF void NOTHROW_NCX(LIBCCALL libc_textcolor)(int color);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> textbackground(3)
 * @param: color: Color code (s.a. constants in `<conio.h>') */
INTDEF void NOTHROW_NCX(LIBDCALL libd_textbackground)(int color);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> textbackground(3)
 * @param: color: Color code (s.a. constants in `<conio.h>') */
INTDEF void NOTHROW_NCX(LIBCCALL libc_textbackground)(int color);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> textattr(3)
 * Set text attributes: `textcolor(attr & 0x0f)' and `textbackground((attr & 0xf0) >> 8)' */
INTDEF void NOTHROW_NCX(LIBDCALL libd_textattr)(int attr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> textattr(3)
 * Set text attributes: `textcolor(attr & 0x0f)' and `textbackground((attr & 0xf0) >> 8)' */
INTDEF void NOTHROW_NCX(LIBCCALL libc_textattr)(int attr);
/* >> clearkeybuf(3)
 * Flush all unread input (usually keyboard) data pending on the terminal */
INTDEF void NOTHROW_NCX(LIBCCALL libc_clearkeybuf)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> _conio_getpass(3)
 * CONIO version of getpass(3). But note the slightly different variant from `<unistd.h>' */
INTDEF ATTR_IN(1) ATTR_INOUT(2) char *NOTHROW_NCX(LIBDCALL libd__conio_getpass)(const char *prompt, char *str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> _conio_getpass(3)
 * CONIO version of getpass(3). But note the slightly different variant from `<unistd.h>' */
INTDEF ATTR_IN(1) ATTR_INOUT(2) char *NOTHROW_NCX(LIBCCALL libc__conio_getpass)(const char *prompt, char *str);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> cputsxy(3)
 * Combination of `gotoxy(3)' and `cputs(3)' */
INTDEF ATTR_IN(3) void NOTHROW_NCX(LIBDCALL libd_cputsxy)(int x, int y, char __KOS_FIXED_CONST *str);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> cputsxy(3)
 * Combination of `gotoxy(3)' and `cputs(3)' */
INTDEF ATTR_IN(3) void NOTHROW_NCX(LIBCCALL libc_cputsxy)(int x, int y, char __KOS_FIXED_CONST *str);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> putchxy(3)
 * Combination of `gotoxy(3)' and `putch(3)' */
INTDEF void NOTHROW_NCX(LIBDCALL libd_putchxy)(int x, int y, char ch);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> putchxy(3)
 * Combination of `gotoxy(3)' and `putch(3)' */
INTDEF void NOTHROW_NCX(LIBCCALL libc_putchxy)(int x, int y, char ch);
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc__conio_wherexy)(uint16_t xy[2]);
/* >> wherex(3)
 * Return the current cursor 'X' position (1-based) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_wherex)(void);
/* >> wherey(3)
 * Return the current cursor 'Y' position (1-based) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_wherey)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> window(3)
 * Set scroll range and margains to the specified rectangle (1-based) */
INTDEF void NOTHROW_NCX(LIBDCALL libd_window)(int left, int top, int right, int bottom);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> window(3)
 * Set scroll range and margains to the specified rectangle (1-based) */
INTDEF void NOTHROW_NCX(LIBCCALL libc_window)(int left, int top, int right, int bottom);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> movetext(3)
 * Duplicate a  given rectangle  (1-based)  of on-screen  text  at
 * another location. Overlapping rectangles are handled correctly. */
INTDEF int NOTHROW_NCX(LIBDCALL libd_movetext)(int left, int top, int right, int bottom, int destleft, int desttop);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> movetext(3)
 * Duplicate a  given rectangle  (1-based)  of on-screen  text  at
 * another location. Overlapping rectangles are handled correctly. */
INTDEF int NOTHROW_NCX(LIBCCALL libc_movetext)(int left, int top, int right, int bottom, int destleft, int desttop);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CONIO_H */
