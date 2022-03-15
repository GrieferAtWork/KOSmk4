/* HASH CRC-32:0x1d352488 */
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
#ifndef GUARD_LIBC_AUTO_CONIO_C
#define GUARD_LIBC_AUTO_CONIO_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/conio.h"
#include "../user/corecrt_wconio.h"
#include "format-printer.h"
#include "../user/stdio.h"
#include "../user/string.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.conio") int
NOTHROW_NCX(LIBCCALL libc__putch)(int ch) {
	return libc_fputc(ch, stdtty);
}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.conio") int
NOTHROW_NCX(LIBCCALL libc__putch_nolock)(int ch) {
	return libc_fputc_unlocked(ch, stdtty);
}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.conio") int
NOTHROW_NCX(LIBCCALL libc__ungetch)(int ch) {
	return libc_ungetc(ch, stdtty);
}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.conio") int
NOTHROW_NCX(LIBCCALL libc__ungetch_nolock)(int ch) {
	return libc_ungetc_unlocked(ch, stdtty);
}
INTERN ATTR_SECTION(".text.crt.dos.conio") NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc__cgets)(char *__restrict buf) {
	char *result = buf + 2;
	size_t readsize;
	if (libc__cgets_s(result, buf[0], &readsize) != 0)
		result = NULL;
	buf[1] = (char)(unsigned char)readsize;
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.conio") NONNULL((1, 3)) errno_t
NOTHROW_NCX(LIBCCALL libc__cgets_s)(char *buf,
                                    size_t bufsize,
                                    size_t *__restrict p_readsize) {
	int ch;
	if unlikely(!bufsize)
		return 28;
	buf[0]      = '\0';
	*p_readsize = 0;
	--bufsize;
	while (bufsize && (ch = libc__getche()) != -1) {
		if (ch == '\r') {
			ch = libc__getche();
			if (ch != -1 && ch != '\n')
				libc__ungetch(ch);
			break;
		}
		if (ch == '\n')
			break;
		*buf++ = (char)(unsigned char)(unsigned int)ch;
		*buf   = '\0';
		++*p_readsize;
		--bufsize;
	}
	return 0;
}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.conio") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc__cputs)(char const *__restrict str) {





	int result = 0;
	do {
		char ch = *str++;
		if (!ch)
			break;
		result = libc__putch(ch);
	} while (result != -1);
	return result;

}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc___conio_common_vcprintf)(uint64_t options,
                                                   char const *format,
                                                   locale_t locale,
                                                   va_list args) {
	return libc___stdio_common_vfprintf(options, stdtty, format, locale, args);
}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc___conio_common_vcprintf_s)(uint64_t options,
                                                     char const *format,
                                                     locale_t locale,
                                                     va_list args) {
	return libc___stdio_common_vfprintf_s(options, stdtty, format, locale, args);
}
DEFINE_INTERN_ALIAS(libc___conio_common_vcprintf_p, libc___conio_common_vcprintf);
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__conio_common_vcscanf_getc) ssize_t
(__FORMATPRINTER_CC __conio_common_vcscanf_getc)(void *__UNUSED(arg)) {
	return (ssize_t)libc__getwche();
}
__LOCAL_LIBC(__conio_common_vcscanf_ungetc) ssize_t
(__FORMATPRINTER_CC __conio_common_vcscanf_ungetc)(void *arg, char32_t ch) {
	return libc__ungetwch((int)(unsigned int)ch);
}
__NAMESPACE_LOCAL_END
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED ATTR_LIBC_SCANF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc___conio_common_vcscanf)(uint64_t options,
                                                  char const *format,
                                                  locale_t locale,
                                                  va_list args) {
	(void)options;
	(void)locale;
	return libc_format_vscanf(&__NAMESPACE_LOCAL_SYM __conio_common_vcscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM __conio_common_vcscanf_ungetc,
	                     NULL, format, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vcprintf_l)(char const *format,
                                       locale_t locale,
                                       va_list args) {
	return libc___conio_common_vcprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vcprintf_s_l)(char const *format,
                                         locale_t locale,
                                         va_list args) {
	return libc___conio_common_vcprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}
DEFINE_INTERN_ALIAS(libc__vcprintf_p_l, libc__vcprintf_l);
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vcscanf_l)(char const *format,
                                      locale_t locale,
                                      va_list args) {
	return libc___conio_common_vcscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vcscanf_s_l)(char const *format,
                                        locale_t locale,
                                        va_list args) {
	return libc___conio_common_vcscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS |
	                              1,
	                              format, locale, args);
}
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vcprintf)(char const *format,
                                     va_list args) {
	return libc__vcprintf_l(format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vcprintf_s)(char const *format,
                                       va_list args) {
	return libc__vcprintf_s_l(format, NULL, args);
}
DEFINE_INTERN_ALIAS(libc__vcprintf_p, libc__vcprintf);
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vcscanf)(char const *format,
                                    va_list args) {
	return libc__vcscanf_l(format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED ATTR_LIBC_SCANF(1, 0) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBCCALL libc__vcscanf_s)(char const *format,
                                      va_list args) {
	return libc__vcscanf_s_l(format, NULL, args);
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cprintf)(char const *format,
                                     ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vcprintf(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__cprintf)(char const *format,
                                     ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vcprintf(format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cprintf_l)(char const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vcprintf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__cprintf_l)(char const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vcprintf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cprintf_s)(char const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vcprintf_s(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__cprintf_s)(char const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vcprintf_s(format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cprintf_s_l)(char const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vcprintf_s_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.conio") ATTR_LIBC_PRINTF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__cprintf_s_l)(char const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vcprintf_s_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_INTERN_ALIAS(libd__cprintf_p, libd__cprintf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_INTERN_ALIAS(libc__cprintf_p, libc__cprintf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_INTERN_ALIAS(libd__cprintf_p_l, libd__cprintf_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_INTERN_ALIAS(libc__cprintf_p_l, libc__cprintf_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cscanf)(char const *format,
                                    ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vcscanf(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__cscanf)(char const *format,
                                    ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vcscanf(format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cscanf_l)(char const *format,
                                      locale_t locale,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vcscanf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__cscanf_l)(char const *format,
                                      locale_t locale,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vcscanf_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cscanf_s)(char const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vcscanf_s(format, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED ATTR_LIBC_SCANF(1, 2) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__cscanf_s)(char const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vcscanf_s(format, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cscanf_s_l)(char const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vcscanf_s_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTERN ATTR_SECTION(".text.crt.dos.conio") WUNUSED ATTR_LIBC_SCANF(1, 3) NONNULL((1)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBCCALL libc__cscanf_s_l)(char const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vcscanf_s_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_putch, libc__putch);
DEFINE_PUBLIC_ALIAS(_putch_nolock, libc__putch_nolock);
DEFINE_PUBLIC_ALIAS(_ungetch, libc__ungetch);
DEFINE_PUBLIC_ALIAS(_ungetch_nolock, libc__ungetch_nolock);
DEFINE_PUBLIC_ALIAS(_cgets, libc__cgets);
DEFINE_PUBLIC_ALIAS(_cgets_s, libc__cgets_s);
DEFINE_PUBLIC_ALIAS(_cputs, libc__cputs);
DEFINE_PUBLIC_ALIAS(__conio_common_vcprintf, libc___conio_common_vcprintf);
DEFINE_PUBLIC_ALIAS(__conio_common_vcprintf_s, libc___conio_common_vcprintf_s);
DEFINE_PUBLIC_ALIAS(__conio_common_vcprintf_p, libc___conio_common_vcprintf_p);
DEFINE_PUBLIC_ALIAS(__conio_common_vcscanf, libc___conio_common_vcscanf);
DEFINE_PUBLIC_ALIAS(_vcprintf_l, libc__vcprintf_l);
DEFINE_PUBLIC_ALIAS(_vcprintf_s_l, libc__vcprintf_s_l);
DEFINE_PUBLIC_ALIAS(_vcprintf_p_l, libc__vcprintf_p_l);
DEFINE_PUBLIC_ALIAS(_vcscanf_l, libc__vcscanf_l);
DEFINE_PUBLIC_ALIAS(_vcscanf_s_l, libc__vcscanf_s_l);
DEFINE_PUBLIC_ALIAS(_vcprintf, libc__vcprintf);
DEFINE_PUBLIC_ALIAS(_vcprintf_s, libc__vcprintf_s);
DEFINE_PUBLIC_ALIAS(_vcprintf_p, libc__vcprintf_p);
DEFINE_PUBLIC_ALIAS(_vcscanf, libc__vcscanf);
DEFINE_PUBLIC_ALIAS(_vcscanf_s, libc__vcscanf_s);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_cprintf, libd__cprintf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_cprintf, libc__cprintf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_cprintf_l, libd__cprintf_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_cprintf_l, libc__cprintf_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_cprintf_s, libd__cprintf_s);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_cprintf_s, libc__cprintf_s);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_cprintf_s_l, libd__cprintf_s_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_cprintf_s_l, libc__cprintf_s_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_cprintf_p, libd__cprintf_p);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_cprintf_p, libc__cprintf_p);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_cprintf_p_l, libd__cprintf_p_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_cprintf_p_l, libc__cprintf_p_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_cscanf, libd__cscanf);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_cscanf, libc__cscanf);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_cscanf_l, libd__cscanf_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_cscanf_l, libc__cscanf_l);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_cscanf_s, libd__cscanf_s);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_cscanf_s, libc__cscanf_s);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
DEFINE_PUBLIC_ALIAS(DOS$_cscanf_s_l, libd__cscanf_s_l);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_cscanf_s_l, libc__cscanf_s_l);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CONIO_C */
