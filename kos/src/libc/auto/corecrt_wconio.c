/* HASH CRC-32:0xe569a126 */
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
#ifndef GUARD_LIBC_AUTO_CORECRT_WCONIO_C
#define GUARD_LIBC_AUTO_CORECRT_WCONIO_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "corecrt_wconio.h"
#include "../user/corecrt_wstdio.h"
#include "parts.wchar.format-printer.h"
#include "../user/stdio.h"
#include "string.h"
#include "termios.h"
#include "../user/wchar.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
#include <libc/template/stdtty.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED wint16_t
NOTHROW_NCX(LIBDCALL libd__getwch)(void) {
	wint16_t result;

	FILE *fp = stdtty;
	libc_flockfile(fp);

	result = libd__getwch_nolock();

	libc_funlockfile(fp);

	return result;
}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED wint32_t
NOTHROW_NCX(LIBKCALL libc__getwch)(void) {
	wint32_t result;

	FILE *fp = stdtty;
	libc_flockfile(fp);

	result = libc__getwch_nolock();

	libc_funlockfile(fp);

	return result;
}
#include <bits/types.h>
#include <asm/os/termios.h>
#include <bits/os/termios.h>
#include <libc/template/stdtty.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED wint16_t
NOTHROW_NCX(LIBDCALL libd__getwch_nolock)(void) {
	wint16_t result;
	struct termios oios, nios;
	FILE *fp = stdtty;
	fd_t fd  = libc_fileno(fp);
	libc_tcgetattr(fd, &oios);
	libc_memcpy(&nios, &oios, sizeof(nios));
	nios.c_lflag &= ~__ECHO;
	libc_tcsetattr(fd, __TCSANOW, &nios);
	result = libd_fgetwc_unlocked(fp);
	libc_tcsetattr(fd, __TCSANOW, &oios);
	return result;
}
#include <bits/types.h>
#include <asm/os/termios.h>
#include <bits/os/termios.h>
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED wint32_t
NOTHROW_NCX(LIBKCALL libc__getwch_nolock)(void) {
	wint32_t result;
	struct termios oios, nios;
	FILE *fp = stdtty;
	fd_t fd  = libc_fileno(fp);
	libc_tcgetattr(fd, &oios);
	libc_memcpy(&nios, &oios, sizeof(nios));
	nios.c_lflag &= ~__ECHO;
	libc_tcsetattr(fd, __TCSANOW, &nios);
	result = libc_fgetwc_unlocked(fp);
	libc_tcsetattr(fd, __TCSANOW, &oios);
	return result;
}
#include <libc/template/stdtty.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED wint16_t
NOTHROW_NCX(LIBDCALL libd__getwche)(void) {
	wint16_t result;

	FILE *fp = stdtty;
	libc_flockfile(fp);

	result = libd__getwche_nolock();

	libc_funlockfile(fp);

	return result;
}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED wint32_t
NOTHROW_NCX(LIBKCALL libc__getwche)(void) {
	wint32_t result;

	FILE *fp = stdtty;
	libc_flockfile(fp);

	result = libc__getwche_nolock();

	libc_funlockfile(fp);

	return result;
}
#include <bits/types.h>
#include <asm/os/termios.h>
#include <bits/os/termios.h>
#include <libc/template/stdtty.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED wint16_t
NOTHROW_NCX(LIBDCALL libd__getwche_nolock)(void) {
	wint16_t result;
	struct termios oios, nios;
	FILE *fp = stdtty;
	fd_t fd  = libc_fileno(fp);
	libc_tcgetattr(fd, &oios);
	libc_memcpy(&nios, &oios, sizeof(nios));
	nios.c_lflag |= __ECHO;
	libc_tcsetattr(fd, __TCSANOW, &nios);
	result = libd_fgetwc_unlocked(fp);
	libc_tcsetattr(fd, __TCSANOW, &oios);
	return result;
}
#include <bits/types.h>
#include <asm/os/termios.h>
#include <bits/os/termios.h>
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED wint32_t
NOTHROW_NCX(LIBKCALL libc__getwche_nolock)(void) {
	wint32_t result;
	struct termios oios, nios;
	FILE *fp = stdtty;
	fd_t fd  = libc_fileno(fp);
	libc_tcgetattr(fd, &oios);
	libc_memcpy(&nios, &oios, sizeof(nios));
	nios.c_lflag |= __ECHO;
	libc_tcsetattr(fd, __TCSANOW, &nios);
	result = libc_fgetwc_unlocked(fp);
	libc_tcsetattr(fd, __TCSANOW, &oios);
	return result;
}
#include <libc/template/stdtty.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") wint16_t
NOTHROW_NCX(LIBDCALL libd__putwch)(char16_t ch) {
	return libd_fputwc(ch, stdtty);
}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") wint32_t
NOTHROW_NCX(LIBKCALL libc__putwch)(char32_t ch) {
	return libc_fputwc(ch, stdtty);
}
#include <libc/template/stdtty.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") wint16_t
NOTHROW_NCX(LIBDCALL libd__putwch_nolock)(char16_t ch) {
	return libd_fputwc_unlocked(ch, stdtty);
}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") wint32_t
NOTHROW_NCX(LIBKCALL libc__putwch_nolock)(char32_t ch) {
	return libc_fputwc_unlocked(ch, stdtty);
}
#include <libc/template/stdtty.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") wint16_t
NOTHROW_NCX(LIBDCALL libd__ungetwch)(wint16_t ch) {
	return libd_ungetwc(ch, stdtty);
}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") wint32_t
NOTHROW_NCX(LIBKCALL libc__ungetwch)(wint32_t ch) {
	return libc_ungetwc(ch, stdtty);
}
#include <libc/template/stdtty.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") wint16_t
NOTHROW_NCX(LIBDCALL libd__ungetwch_nolock)(wint16_t ch) {
	return libd_ungetwc_unlocked(ch, stdtty);
}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") wint32_t
NOTHROW_NCX(LIBKCALL libc__ungetwch_nolock)(wint32_t ch) {
	return libc_ungetwc_unlocked(ch, stdtty);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RW(1) char16_t *
NOTHROW_NCX(LIBDCALL libd__cgetws)(char16_t *__restrict buf) {
	char16_t *result = buf + 2;
	size_t readsize;
	if (libd__cgetws_s(result, buf[0], &readsize) != 0)
		result = NULL;
	buf[1] = (char16_t)readsize;
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RW(1) char32_t *
NOTHROW_NCX(LIBKCALL libc__cgetws)(char32_t *__restrict buf) {
	char32_t *result = buf + 2;
	size_t readsize;
	if (libc__cgetws_s(result, buf[0], &readsize) != 0)
		result = NULL;
	buf[1] = (char32_t)readsize;
	return result;
}
#include <asm/crt/stdio.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_WR(3) ATTR_ACCESS_WRS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__cgetws_s)(char16_t *buf,
                                     size_t bufsize,
                                     size_t *__restrict p_readsize) {
	char16_t ch;
	if unlikely(!bufsize)
		return 28;
	buf[0]      = (char16_t)'\0';
	*p_readsize = 0;
	--bufsize;
	while (bufsize && (ch = libd__getwche()) != __WEOF16) {
		if (ch == (char16_t)'\r') {
			ch = libd__getwche();
			if (ch != __WEOF16 && ch != (char16_t)'\n')
				libd__ungetwch(ch);
			break;
		}
		if (ch == (char16_t)'\n')
			break;
		*buf++ = ch;
		*buf   = (char16_t)'\0';
		++*p_readsize;
		--bufsize;
	}
	return 0;
}
#include <asm/crt/stdio.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_WR(3) ATTR_ACCESS_WRS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc__cgetws_s)(char32_t *buf,
                                     size_t bufsize,
                                     size_t *__restrict p_readsize) {
	char32_t ch;
	if unlikely(!bufsize)
		return ENOSPC;
	buf[0]      = (char32_t)'\0';
	*p_readsize = 0;
	--bufsize;
	while (bufsize && (ch = libc__getwche()) != __WEOF32) {
		if (ch == (char32_t)'\r') {
			ch = libc__getwche();
			if (ch != __WEOF32 && ch != (char32_t)'\n')
				libc__ungetwch(ch);
			break;
		}
		if (ch == (char32_t)'\n')
			break;
		*buf++ = ch;
		*buf   = (char32_t)'\0';
		++*p_readsize;
		--bufsize;
	}
	return 0;
}
#include <libc/template/stdtty.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) int
NOTHROW_NCX(LIBDCALL libd__cputws)(char16_t const *__restrict str) {





	for (;;) {
		char16_t ch = *str++;
		if (!ch)
			break;
		if (libd__putwch(ch) == __WEOF16)
			return -1;
	}
	return 0;

}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) int
NOTHROW_NCX(LIBKCALL libc__cputws)(char32_t const *__restrict str) {





	for (;;) {
		char32_t ch = *str++;
		if (!ch)
			break;
		if (libc__putwch(ch) == __WEOF32)
			return -1;
	}
	return 0;

}
#include <libc/template/stdtty.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(2) ATTR_LIBC_C16PRINTF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd___conio_common_vcwprintf)(uint64_t options,
                                                    char16_t const *format,
                                                    locale_t locale,
                                                    va_list args) {
	return libd___stdio_common_vfwprintf(options, stdtty, format, locale, args);
}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(2) ATTR_LIBC_C32PRINTF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc___conio_common_vcwprintf)(uint64_t options,
                                                    char32_t const *format,
                                                    locale_t locale,
                                                    va_list args) {
	return libc___stdio_common_vfwprintf(options, stdtty, format, locale, args);
}
#include <libc/template/stdtty.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(2) ATTR_LIBC_C16PRINTF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd___conio_common_vcwprintf_s)(uint64_t options,
                                                      char16_t const *format,
                                                      locale_t locale,
                                                      va_list args) {
	return libd___stdio_common_vfwprintf_s(options, stdtty, format, locale, args);
}
#include <libc/template/stdtty.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(2) ATTR_LIBC_C32PRINTF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc___conio_common_vcwprintf_s)(uint64_t options,
                                                      char32_t const *format,
                                                      locale_t locale,
                                                      va_list args) {
	return libc___stdio_common_vfwprintf_s(options, stdtty, format, locale, args);
}
DEFINE_INTERN_ALIAS(libd___conio_common_vcwprintf_p, libd___conio_common_vcwprintf);
DEFINE_INTERN_ALIAS(libc___conio_common_vcwprintf_p, libc___conio_common_vcwprintf);
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(conio_common_vcc16scanf_getc) __format_word_t
(__FORMATPRINTER_CC conio_common_vcc16scanf_getc)(void *__UNUSED(arg)) {
	return (__format_word_t)libd__getwche();
}
__LOCAL_LIBC(conio_common_vcc16scanf_ungetc) ssize_t
(__FORMATPRINTER_CC conio_common_vcc16scanf_ungetc)(void *__UNUSED(arg), __format_word_t word) {
	return libd__ungetwch((wint16_t)word);
}
__NAMESPACE_LOCAL_END
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(2) ATTR_LIBC_C16SCANF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd___conio_common_vcwscanf)(uint64_t options,
                                                   char16_t const *format,
                                                   locale_t locale,
                                                   va_list args) {
	(void)options;
	(void)locale;
	return libd_format_vwscanf(&__NAMESPACE_LOCAL_SYM conio_common_vcc16scanf_getc,
	                      &__NAMESPACE_LOCAL_SYM conio_common_vcc16scanf_ungetc,
	                      NULL, format, args);
}
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(conio_common_vcc32scanf_getc) __format_word_t
(__FORMATPRINTER_CC conio_common_vcc32scanf_getc)(void *__UNUSED(arg)) {
	return (__format_word_t)libc__getwche();
}
__LOCAL_LIBC(conio_common_vcc32scanf_ungetc) ssize_t
(__FORMATPRINTER_CC conio_common_vcc32scanf_ungetc)(void *__UNUSED(arg), __format_word_t word) {
	return libc__ungetwch((wint32_t)word);
}
__NAMESPACE_LOCAL_END
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(2) ATTR_LIBC_C32SCANF(2, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc___conio_common_vcwscanf)(uint64_t options,
                                                   char32_t const *format,
                                                   locale_t locale,
                                                   va_list args) {
	(void)options;
	(void)locale;
	return libc_format_vwscanf(&__NAMESPACE_LOCAL_SYM conio_common_vcc32scanf_getc,
	                      &__NAMESPACE_LOCAL_SYM conio_common_vcc32scanf_ungetc,
	                      NULL, format, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vcwprintf_l)(char16_t const *format,
                                        locale_t locale,
                                        va_list args) {
	return libd___conio_common_vcwprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vcwprintf_l)(char32_t const *format,
                                        locale_t locale,
                                        va_list args) {
	return libc___conio_common_vcwprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vcwprintf_s_l)(char16_t const *format,
                                          locale_t locale,
                                          va_list args) {
	return libd___conio_common_vcwprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vcwprintf_s_l)(char32_t const *format,
                                          locale_t locale,
                                          va_list args) {
	return libc___conio_common_vcwprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}
DEFINE_INTERN_ALIAS(libd__vcwprintf_p_l, libd__vcwprintf_l);
DEFINE_INTERN_ALIAS(libc__vcwprintf_p_l, libc__vcwprintf_l);
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C16SCANF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vcwscanf_l)(char16_t const *format,
                                       locale_t locale,
                                       va_list args) {
	return libd___conio_common_vcwscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C32SCANF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vcwscanf_l)(char32_t const *format,
                                       locale_t locale,
                                       va_list args) {
	return libc___conio_common_vcwscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C16SCANF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vcwscanf_s_l)(char16_t const *format,
                                         locale_t locale,
                                         va_list args) {
	return libd___conio_common_vcwscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS |
	                               1,
	                               format, locale, args);
}
#include <corecrt_stdio_config.h>
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C32SCANF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vcwscanf_s_l)(char32_t const *format,
                                         locale_t locale,
                                         va_list args) {
	return libc___conio_common_vcwscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS |
	                               1,
	                               format, locale, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vcwprintf)(char16_t const *format,
                                      va_list args) {
	return libd__vcwprintf_l(format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vcwprintf)(char32_t const *format,
                                      va_list args) {
	return libc__vcwprintf_l(format, NULL, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C16PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vcwprintf_s)(char16_t const *format,
                                        va_list args) {
	return libd__vcwprintf_s_l(format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C32PRINTF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vcwprintf_s)(char32_t const *format,
                                        va_list args) {
	return libc__vcwprintf_s_l(format, NULL, args);
}
DEFINE_INTERN_ALIAS(libd__vcwprintf_p, libd__vcwprintf);
DEFINE_INTERN_ALIAS(libc__vcwprintf_p, libc__vcwprintf);
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C16SCANF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vcwscanf)(char16_t const *format,
                                     va_list args) {
	return libd__vcwscanf_l(format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C32SCANF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vcwscanf)(char32_t const *format,
                                     va_list args) {
	return libc__vcwscanf_l(format, NULL, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C16SCANF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd__vcwscanf_s)(char16_t const *format,
                                       va_list args) {
	return libd__vcwscanf_s_l(format, NULL, args);
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C32SCANF(1, 0) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc__vcwscanf_s)(char32_t const *format,
                                       va_list args) {
	return libc__vcwscanf_s_l(format, NULL, args);
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C16PRINTF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cwprintf)(char16_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vcwprintf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C32PRINTF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__cwprintf)(char32_t const *format,
                                      ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vcwprintf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C16PRINTF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cwprintf_l)(char16_t const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vcwprintf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C32PRINTF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__cwprintf_l)(char32_t const *format,
                                        locale_t locale,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vcwprintf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C16PRINTF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cwprintf_s)(char16_t const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vcwprintf_s(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C32PRINTF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__cwprintf_s)(char32_t const *format,
                                        ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vcwprintf_s(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C16PRINTF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cwprintf_s_l)(char16_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vcwprintf_s_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") ATTR_ACCESS_RO(1) ATTR_LIBC_C32PRINTF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__cwprintf_s_l)(char32_t const *format,
                                          locale_t locale,
                                          ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vcwprintf_s_l(format, locale, args);
	va_end(args);
	return result;
}
DEFINE_INTERN_ALIAS(libd__cwprintf_p, libd__cwprintf);
DEFINE_INTERN_ALIAS(libc__cwprintf_p, libc__cwprintf);
DEFINE_INTERN_ALIAS(libd__cwprintf_p_l, libd__cwprintf_l);
DEFINE_INTERN_ALIAS(libc__cwprintf_p_l, libc__cwprintf_l);
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C16SCANF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cwscanf)(char16_t const *format,
                                     ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vcwscanf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C32SCANF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__cwscanf)(char32_t const *format,
                                     ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vcwscanf(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C16SCANF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cwscanf_l)(char16_t const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vcwscanf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C32SCANF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__cwscanf_l)(char32_t const *format,
                                       locale_t locale,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vcwscanf_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C16SCANF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cwscanf_s)(char16_t const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd__vcwscanf_s(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C32SCANF(1, 2) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__cwscanf_s)(char32_t const *format,
                                       ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc__vcwscanf_s(format, args);
	va_end(args);
	return result;
}
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C16SCANF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBDCALL libd__cwscanf_s_l)(char16_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libd__vcwscanf_s_l(format, locale, args);
	va_end(args);
	return result;
}
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_ACCESS_RO(1) ATTR_LIBC_C32SCANF(1, 3) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(VLIBKCALL libc__cwscanf_s_l)(char32_t const *format,
                                         locale_t locale,
                                         ...) {
	__STDC_INT_AS_SSIZE_T result;
	va_list args;
	va_start(args, locale);
	result = libc__vcwscanf_s_l(format, locale, args);
	va_end(args);
	return result;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(DOS$_getwch, libd__getwch);
DEFINE_PUBLIC_ALIAS(_getwch, libc__getwch);
DEFINE_PUBLIC_ALIAS(DOS$_getwch_nolock, libd__getwch_nolock);
DEFINE_PUBLIC_ALIAS(_getwch_nolock, libc__getwch_nolock);
DEFINE_PUBLIC_ALIAS(DOS$_getwche, libd__getwche);
DEFINE_PUBLIC_ALIAS(_getwche, libc__getwche);
DEFINE_PUBLIC_ALIAS(DOS$_getwche_nolock, libd__getwche_nolock);
DEFINE_PUBLIC_ALIAS(_getwche_nolock, libc__getwche_nolock);
DEFINE_PUBLIC_ALIAS(DOS$_putwch, libd__putwch);
DEFINE_PUBLIC_ALIAS(_putwch, libc__putwch);
DEFINE_PUBLIC_ALIAS(DOS$_putwch_nolock, libd__putwch_nolock);
DEFINE_PUBLIC_ALIAS(_putwch_nolock, libc__putwch_nolock);
DEFINE_PUBLIC_ALIAS(DOS$_ungetwch, libd__ungetwch);
DEFINE_PUBLIC_ALIAS(_ungetwch, libc__ungetwch);
DEFINE_PUBLIC_ALIAS(DOS$_ungetwch_nolock, libd__ungetwch_nolock);
DEFINE_PUBLIC_ALIAS(_ungetwch_nolock, libc__ungetwch_nolock);
DEFINE_PUBLIC_ALIAS(DOS$_cgetws, libd__cgetws);
DEFINE_PUBLIC_ALIAS(_cgetws, libc__cgetws);
DEFINE_PUBLIC_ALIAS(DOS$_cgetws_s, libd__cgetws_s);
DEFINE_PUBLIC_ALIAS(_cgetws_s, libc__cgetws_s);
DEFINE_PUBLIC_ALIAS(DOS$_cputws, libd__cputws);
DEFINE_PUBLIC_ALIAS(_cputws, libc__cputws);
DEFINE_PUBLIC_ALIAS(DOS$__conio_common_vcwprintf, libd___conio_common_vcwprintf);
DEFINE_PUBLIC_ALIAS(__conio_common_vcwprintf, libc___conio_common_vcwprintf);
DEFINE_PUBLIC_ALIAS(DOS$__conio_common_vcwprintf_s, libd___conio_common_vcwprintf_s);
DEFINE_PUBLIC_ALIAS(__conio_common_vcwprintf_s, libc___conio_common_vcwprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$__conio_common_vcwprintf_p, libd___conio_common_vcwprintf_p);
DEFINE_PUBLIC_ALIAS(__conio_common_vcwprintf_p, libc___conio_common_vcwprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$__conio_common_vcwscanf, libd___conio_common_vcwscanf);
DEFINE_PUBLIC_ALIAS(__conio_common_vcwscanf, libc___conio_common_vcwscanf);
DEFINE_PUBLIC_ALIAS(DOS$_vcwprintf_l, libd__vcwprintf_l);
DEFINE_PUBLIC_ALIAS(_vcwprintf_l, libc__vcwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vcwprintf_s_l, libd__vcwprintf_s_l);
DEFINE_PUBLIC_ALIAS(_vcwprintf_s_l, libc__vcwprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vcwprintf_p_l, libd__vcwprintf_p_l);
DEFINE_PUBLIC_ALIAS(_vcwprintf_p_l, libc__vcwprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_vcwscanf_l, libd__vcwscanf_l);
DEFINE_PUBLIC_ALIAS(_vcwscanf_l, libc__vcwscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_vcwscanf_s_l, libd__vcwscanf_s_l);
DEFINE_PUBLIC_ALIAS(_vcwscanf_s_l, libc__vcwscanf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_vcwprintf, libd__vcwprintf);
DEFINE_PUBLIC_ALIAS(_vcwprintf, libc__vcwprintf);
DEFINE_PUBLIC_ALIAS(DOS$_vcwprintf_s, libd__vcwprintf_s);
DEFINE_PUBLIC_ALIAS(_vcwprintf_s, libc__vcwprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$_vcwprintf_p, libd__vcwprintf_p);
DEFINE_PUBLIC_ALIAS(_vcwprintf_p, libc__vcwprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_vcwscanf, libd__vcwscanf);
DEFINE_PUBLIC_ALIAS(_vcwscanf, libc__vcwscanf);
DEFINE_PUBLIC_ALIAS(DOS$_vcwscanf_s, libd__vcwscanf_s);
DEFINE_PUBLIC_ALIAS(_vcwscanf_s, libc__vcwscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$_cwprintf, libd__cwprintf);
DEFINE_PUBLIC_ALIAS(_cwprintf, libc__cwprintf);
DEFINE_PUBLIC_ALIAS(DOS$_cwprintf_l, libd__cwprintf_l);
DEFINE_PUBLIC_ALIAS(_cwprintf_l, libc__cwprintf_l);
DEFINE_PUBLIC_ALIAS(DOS$_cwprintf_s, libd__cwprintf_s);
DEFINE_PUBLIC_ALIAS(_cwprintf_s, libc__cwprintf_s);
DEFINE_PUBLIC_ALIAS(DOS$_cwprintf_s_l, libd__cwprintf_s_l);
DEFINE_PUBLIC_ALIAS(_cwprintf_s_l, libc__cwprintf_s_l);
DEFINE_PUBLIC_ALIAS(DOS$_cwprintf_p, libd__cwprintf_p);
DEFINE_PUBLIC_ALIAS(_cwprintf_p, libc__cwprintf_p);
DEFINE_PUBLIC_ALIAS(DOS$_cwprintf_p_l, libd__cwprintf_p_l);
DEFINE_PUBLIC_ALIAS(_cwprintf_p_l, libc__cwprintf_p_l);
DEFINE_PUBLIC_ALIAS(DOS$_cwscanf, libd__cwscanf);
DEFINE_PUBLIC_ALIAS(_cwscanf, libc__cwscanf);
DEFINE_PUBLIC_ALIAS(DOS$_cwscanf_l, libd__cwscanf_l);
DEFINE_PUBLIC_ALIAS(_cwscanf_l, libc__cwscanf_l);
DEFINE_PUBLIC_ALIAS(DOS$_cwscanf_s, libd__cwscanf_s);
DEFINE_PUBLIC_ALIAS(_cwscanf_s, libc__cwscanf_s);
DEFINE_PUBLIC_ALIAS(DOS$_cwscanf_s_l, libd__cwscanf_s_l);
DEFINE_PUBLIC_ALIAS(_cwscanf_s_l, libc__cwscanf_s_l);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_CORECRT_WCONIO_C */
