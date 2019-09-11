/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_LIBC_USER_WCHAR_C
#define GUARD_LIBC_USER_WCHAR_C 1

#include "../api.h"
/**/

#include "../libc/uchar.h"
#include "../auto/parts.wchar.format-printer.h"
#include "wchar.h"
#include "malloc.h"
#include "string.h"
#include "stdio.h"
#include <uchar.h>
#include <stdio.h>
#include <string.h>

DECL_BEGIN

#undef stdin
#undef stdout
#undef stderr
DECLARE_NOREL_GLOBAL_META(FILE *, stdin);
DECLARE_NOREL_GLOBAL_META(FILE *, stdout);
DECLARE_NOREL_GLOBAL_META(FILE *, stderr);
#define stdin  GET_NOREL_GLOBAL(stdin)
#define stdout GET_NOREL_GLOBAL(stdout)
#define stderr GET_NOREL_GLOBAL(stderr)

#undef __LOCAL_stdin
#undef __LOCAL_stdout
#undef __LOCAL_stderr
#define __LOCAL_stdin   stdin
#define __LOCAL_stdout  stdout
#define __LOCAL_stderr  stderr

#undef __WEOF
#define __WEOF WEOF


INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcstok_s") char16_t *
(LIBDCALL libd_wcstok)(char16_t *string,
                       char16_t const *__restrict delim,
                       char16_t **__restrict save_ptr) {
	char16_t *end;
	if (!string)
		string = *save_ptr;
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	string += libd_wcsspn(string, delim);
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	end = string + libd_wcscspn(string, delim);
	if (!*end) {
		*save_ptr = end;
		return string;
	}
	*end      = '\0';
	*save_ptr = end + 1;
	return string;
}

PRIVATE ATTR_SECTION(".bss.crt.dos.wchar.string.memory.wcstok_safe_ptr")
char16_t *wcstok_safe_ptr = NULL;

INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.string.memory.wcstok") char16_t *
(LIBDCALL libd_wcstok_nosafe)(char16_t *string,
                              char16_t const *__restrict delim) {
	return libd_wcstok(string, delim, &wcstok_safe_ptr);
}


INTERN NONNULL((2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.string.memory.wcstok") char32_t *
(LIBCCALL libc_wcstok)(char32_t *string,
                       char32_t const *__restrict delim,
                       char32_t **__restrict save_ptr) {
	char32_t *end;
	if (!string)
		string = *save_ptr;
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	string += libc_wcsspn(string, delim);
	if (!*string) {
		*save_ptr = string;
		return NULL;
	}
	end = string + libc_wcscspn(string, delim);
	if (!*end) {
		*save_ptr = end;
		return string;
	}
	*end      = '\0';
	*save_ptr = end + 1;
	return string;
}

DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstok_s, libd_wcstok);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcstok, libd_wcstok_nosafe);
DEFINE_PUBLIC_WEAK_ALIAS(wcstok_s, libc_wcstok);
DEFINE_PUBLIC_WEAK_ALIAS(wcstok, libc_wcstok);



/*[[[start:implementation]]]*/




/*[[[head:fgetwc_unlocked,hash:0x174a13ae]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.getc.fgetwc_unlocked") wint_t
(LIBCCALL libc_fgetwc_unlocked)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fgetwc_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("fgetwc_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:fgetwc_unlocked]]]*/

/*[[[head:DOS$fgetwc_unlocked,hash:0x13ce1a19]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.getc.fgetwc_unlocked") wint_t
(LIBDCALL libd_fgetwc_unlocked)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:DOS$fgetwc_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("fgetwc_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$fgetwc_unlocked]]]*/

/*[[[head:fputwc_unlocked,hash:0x32b1d096]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.putc.fputwc_unlocked") wint_t
(LIBCCALL libc_fputwc_unlocked)(char32_t wc,
                                FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fputwc_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("fputwc_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:fputwc_unlocked]]]*/

/*[[[head:DOS$fputwc_unlocked,hash:0xdcc0bafe]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.putc.fputwc_unlocked") wint_t
(LIBDCALL libd_fputwc_unlocked)(char16_t wc,
                                FILE *__restrict stream)
		__THROWS(...)
/*[[[body:DOS$fputwc_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("fputwc_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$fputwc_unlocked]]]*/

/*[[[head:fgetwc,hash:0xd167b836]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.read.getc.fgetwc") wint_t
(LIBCCALL libc_fgetwc)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fgetwc]]]*/
{
	CRT_UNIMPLEMENTED("fgetwc"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:fgetwc]]]*/

/*[[[head:fputwc,hash:0xd460394b]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.putc.fputwc") wint_t
(LIBCCALL libc_fputwc)(char32_t wc,
                       FILE *stream)
		__THROWS(...)
/*[[[body:fputwc]]]*/
{
	CRT_UNIMPLEMENTED("fputwc"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:fputwc]]]*/

/*[[[head:DOS$fputwc,hash:0x3e9d96af]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.putc.fputwc") wint_t
(LIBDCALL libd_fputwc)(char16_t wc,
                       FILE *stream)
		__THROWS(...)
/*[[[body:DOS$fputwc]]]*/
{
	CRT_UNIMPLEMENTED("fputwc"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$fputwc]]]*/

/*[[[head:DOS$fgetwc,hash:0x3e815adc]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.getc.fgetwc") wint_t
(LIBDCALL libd_fgetwc)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:DOS$fgetwc]]]*/
{
	CRT_UNIMPLEMENTED("fgetwc"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$fgetwc]]]*/

/*[[[head:ungetwc,hash:0xc5937147]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.putc.ungetwc") wint_t
NOTHROW_NCX(LIBCCALL libc_ungetwc)(wint_t wc,
                                   FILE *stream)
/*[[[body:ungetwc]]]*/
{
	CRT_UNIMPLEMENTED("ungetwc"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:ungetwc]]]*/

/*[[[head:DOS$ungetwc,hash:0x5d1d4dc0]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.putc.ungetwc") wint_t
NOTHROW_NCX(LIBDCALL libd_ungetwc)(wint_t wc,
                                   FILE *stream)
/*[[[body:DOS$ungetwc]]]*/
{
	CRT_UNIMPLEMENTED("ungetwc"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$ungetwc]]]*/

/*[[[head:ungetwc_unlocked,hash:0x9b95a713]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.putc.ungetwc_unlocked") wint_t
NOTHROW_NCX(LIBCCALL libc_ungetwc_unlocked)(wint_t ch,
                                            FILE *__restrict stream)
/*[[[body:ungetwc_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("ungetwc_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:ungetwc_unlocked]]]*/

/*[[[head:DOS$ungetwc_unlocked,hash:0xa1418bfa]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.putc.ungetwc_unlocked") wint_t
NOTHROW_NCX(LIBDCALL libd_ungetwc_unlocked)(wint_t ch,
                                            FILE *__restrict stream)
/*[[[body:DOS$ungetwc_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("ungetwc_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$ungetwc_unlocked]]]*/


/*[[[head:open_wmemstream,hash:0x20df9586]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.access.open_wmemstream") FILE *
NOTHROW_NCX(LIBCCALL libc_open_wmemstream)(char32_t **bufloc,
                                           size_t *sizeloc)
/*[[[body:open_wmemstream]]]*/
{
	CRT_UNIMPLEMENTED("open_wmemstream"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:open_wmemstream]]]*/

/*[[[head:DOS$open_wmemstream,hash:0xe6a8ca52]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access.open_wmemstream") FILE *
NOTHROW_NCX(LIBDCALL libd_open_wmemstream)(char16_t **bufloc,
                                           size_t *sizeloc)
/*[[[body:DOS$open_wmemstream]]]*/
{
	CRT_UNIMPLEMENTED("open_wmemstream"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$open_wmemstream]]]*/










/*[[[head:getwchar,hash:0x14d923a5]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.read.getc.getwchar") wint_t
(LIBCCALL libc_getwchar)(void)
		__THROWS(...)
/*[[[body:getwchar]]]*/
/*AUTO*/{
	return libc_fgetwc(__LOCAL_stdin);
}
/*[[[end:getwchar]]]*/

/*[[[head:DOS$getwchar,hash:0x416d5d3f]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.getc.getwchar") wint_t
(LIBDCALL libd_getwchar)(void)
		__THROWS(...)
/*[[[body:DOS$getwchar]]]*/
/*AUTO*/{
	return libd_fgetwc(__LOCAL_stdin);
}
/*[[[end:DOS$getwchar]]]*/

/*[[[head:putwchar,hash:0x9b3b1cd1]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.putc.putwchar") wint_t
(LIBCCALL libc_putwchar)(char32_t wc)
		__THROWS(...)
/*[[[body:putwchar]]]*/
/*AUTO*/{
	return libc_fputwc(wc, __LOCAL_stdout);
}
/*[[[end:putwchar]]]*/

/*[[[head:DOS$putwchar,hash:0x7c0ab7fc]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.putc.putwchar") wint_t
(LIBDCALL libd_putwchar)(char16_t wc)
		__THROWS(...)
/*[[[body:DOS$putwchar]]]*/
/*AUTO*/{
	return libd_fputwc(wc, __LOCAL_stdout);
}
/*[[[end:DOS$putwchar]]]*/

/*[[[head:fgetws,hash:0xab91c166]]]*/
INTERN WUNUSED NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.read.read.fgetws") char32_t *
(LIBCCALL libc_fgetws)(char32_t *__restrict buf,
                       __STDC_INT_AS_SIZE_T bufsize,
                       FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fgetws]]]*/
{
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
		libc_seterrno(ERANGE);
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = libc_fgetwc(stream);
		if (ch == WEOF) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libc_fgetwc(stream);
			if (ch == WEOF) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libc_ungetwc(ch, stream);
			break;
		}
		buf[n] = (char32_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
/*[[[end:fgetws]]]*/

/*[[[head:DOS$fgetws,hash:0x54978139]]]*/
INTERN WUNUSED NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.read.fgetws") char16_t *
(LIBDCALL libd_fgetws)(char16_t *__restrict buf,
                       __STDC_INT_AS_SIZE_T bufsize,
                       FILE *__restrict stream)
		__THROWS(...)
/*[[[body:DOS$fgetws]]]*/
{
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
		libc_seterrno(ERANGE);
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = libd_fgetwc(stream);
		if (ch == WEOF) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libd_fgetwc(stream);
			if (ch == WEOF) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libd_ungetwc(ch, stream);
			break;
		}
		buf[n] = (char16_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
/*[[[end:DOS$fgetws]]]*/

/*[[[head:fgetws_unlocked,hash:0x28810471]]]*/
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.read.fgetws_unlocked") char32_t *
(LIBCCALL libc_fgetws_unlocked)(char32_t *__restrict buf,
                                __STDC_INT_AS_SIZE_T bufsize,
                                FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fgetws_unlocked]]]*/
{
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
		libc_seterrno(ERANGE);
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = libc_fgetwc_unlocked(stream);
		if (ch == WEOF) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libc_fgetwc_unlocked(stream);
			if (ch == WEOF) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libc_ungetwc_unlocked(ch, stream);
			break;
		}
		buf[n] = (char32_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
/*[[[end:fgetws_unlocked]]]*/

/*[[[head:DOS$fgetws_unlocked,hash:0x5de88c1c]]]*/
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.read.fgetws_unlocked") char16_t *
(LIBDCALL libd_fgetws_unlocked)(char16_t *__restrict buf,
                                __STDC_INT_AS_SIZE_T bufsize,
                                FILE *__restrict stream)
		__THROWS(...)
/*[[[body:DOS$fgetws_unlocked]]]*/
{
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
		libc_seterrno(ERANGE);
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = libd_fgetwc_unlocked(stream);
		if (ch == WEOF) {
			if (n == 0 || libc_ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = libd_fgetwc_unlocked(stream);
			if (ch == WEOF) {
				if (n == 0 || libc_ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			libd_ungetwc_unlocked(ch, stream);
			break;
		}
		buf[n] = (char16_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}
/*[[[end:DOS$fgetws_unlocked]]]*/

/*[[[head:fputws,hash:0xbc254fc8]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.write.fputws") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_fputws)(char32_t const *__restrict string,
                       FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fputws]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	result = libc_file_wprinter(stream, string, libc_wcslen(string));
	return result;
}
/*[[[end:fputws]]]*/

/*[[[head:DOS$fputws,hash:0x49f9011d]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.write.fputws") __STDC_INT_AS_SIZE_T
(LIBDCALL libd_fputws)(char16_t const *__restrict string,
                       FILE *__restrict stream)
		__THROWS(...)
/*[[[body:DOS$fputws]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	result = libd_file_wprinter(stream, string, libd_wcslen(string));
	return result;
}
/*[[[end:DOS$fputws]]]*/

/*[[[head:DOS$fwscanf,hash:0x3200cee4]]]*/
INTERN ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf.fwscanf") __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fwscanf)(FILE *__restrict stream,
                         char16_t const *__restrict format,
                         ...)
		__THROWS(...)
/*[[[body:DOS$fwscanf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwscanf(stream, format, args);
	va_end(args);
	return result;
}
/*[[[end:DOS$fwscanf]]]*/

/*[[[head:vwscanf,hash:0xcd7f3f65]]]*/
INTERN WUNUSED ATTR_LIBC_WSCANF(1, 0) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf.vwscanf") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vwscanf)(char32_t const *__restrict format,
                        va_list args)
		__THROWS(...)
/*[[[body:vwscanf]]]*/
/*AUTO*/{
	return libc_vfwscanf(__LOCAL_stdin, format, args);
}
/*[[[end:vwscanf]]]*/



/*[[[head:DOS$wscanf,hash:0x543ab34f]]]*/
INTERN ATTR_LIBC_WSCANF(1, 2) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf.wscanf") __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_wscanf)(char16_t const *__restrict format,
                        ...)
		__THROWS(...)
/*[[[body:DOS$wscanf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwscanf(format, args);
	va_end(args);
	return result;
}
/*[[[end:DOS$wscanf]]]*/

/*[[[head:wscanf,hash:0x5adf2a73]]]*/
INTERN ATTR_LIBC_WSCANF(1, 2) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf.wscanf") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_wscanf)(char32_t const *__restrict format,
                        ...)
		__THROWS(...)
/*[[[body:wscanf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwscanf(format, args);
	va_end(args);
	return result;
}
/*[[[end:wscanf]]]*/

/*[[[head:DOS$wprintf,hash:0x3692041b]]]*/
INTERN ATTR_LIBC_WPRINTF(1, 2) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf.wprintf") __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_wprintf)(char16_t const *__restrict format,
                         ...)
		__THROWS(...)
/*[[[body:DOS$wprintf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwprintf(format, args);
	va_end(args);
	return result;
}
/*[[[end:DOS$wprintf]]]*/

/*[[[head:wprintf,hash:0x4b41a5b5]]]*/
INTERN ATTR_LIBC_WPRINTF(1, 2) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf.wprintf") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_wprintf)(char32_t const *__restrict format,
                         ...)
		__THROWS(...)
/*[[[body:wprintf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwprintf(format, args);
	va_end(args);
	return result;
}
/*[[[end:wprintf]]]*/

/*[[[head:fwscanf,hash:0x5f4b60da]]]*/
INTERN ATTR_LIBC_WSCANF(2, 3) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf.fwscanf") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_fwscanf)(FILE *__restrict stream,
                         char32_t const *__restrict format,
                         ...)
		__THROWS(...)
/*[[[body:fwscanf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwscanf(stream, format, args);
	va_end(args);
	return result;
}
/*[[[end:fwscanf]]]*/

/*[[[head:vfwscanf,hash:0x81c3acd]]]*/
INTERN WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf.vfwscanf") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vfwscanf)(FILE *__restrict stream,
                         char32_t const *__restrict format,
                         va_list args)
		__THROWS(...)
/*[[[body:vfwscanf]]]*/
{
	CRT_UNIMPLEMENTED("vfwscanf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:vfwscanf]]]*/

/*[[[head:DOS$vwprintf,hash:0xdfd94f38]]]*/
INTERN ATTR_LIBC_WPRINTF(1, 0) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf.vwprintf") __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vwprintf)(char16_t const *__restrict format,
                         va_list args)
		__THROWS(...)
/*[[[body:DOS$vwprintf]]]*/
/*AUTO*/{
	return libd_vfwprintf(__LOCAL_stdout, format, args);
}
/*[[[end:DOS$vwprintf]]]*/

/*[[[head:vwprintf,hash:0xd521d3bc]]]*/
INTERN ATTR_LIBC_WPRINTF(1, 0) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf.vwprintf") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vwprintf)(char32_t const *__restrict format,
                         va_list args)
		__THROWS(...)
/*[[[body:vwprintf]]]*/
/*AUTO*/{
	return libc_vfwprintf(__LOCAL_stdout, format, args);
}
/*[[[end:vwprintf]]]*/


/*[[[head:DOS$vfwscanf,hash:0xc25e2dcb]]]*/
INTERN WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf.vfwscanf") __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vfwscanf)(FILE *__restrict stream,
                         char16_t const *__restrict format,
                         va_list args)
		__THROWS(...)
/*[[[body:DOS$vfwscanf]]]*/
{
	CRT_UNIMPLEMENTED("vfwscanf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$vfwscanf]]]*/

/*[[[head:DOS$vwscanf,hash:0xbcbd9716]]]*/
INTERN WUNUSED ATTR_LIBC_WSCANF(1, 0) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf.vwscanf") __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vwscanf)(char16_t const *__restrict format,
                        va_list args)
		__THROWS(...)
/*[[[body:DOS$vwscanf]]]*/
/*AUTO*/{
	return libd_vfwscanf(__LOCAL_stdin, format, args);
}
/*[[[end:DOS$vwscanf]]]*/

/*[[[head:wcswidth,hash:0xd43dd4de]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wcswidth") int
NOTHROW_NCX(LIBCCALL libc_wcswidth)(char32_t const *__restrict string,
                                    size_t num_chars)
/*[[[body:wcswidth]]]*/
{
	CRT_UNIMPLEMENTED("wcswidth"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wcswidth]]]*/

/*[[[head:putwchar_unlocked,hash:0xfd70c637]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.putc.putwchar_unlocked") wint_t
(LIBCCALL libc_putwchar_unlocked)(char32_t wc)
		__THROWS(...)
/*[[[body:putwchar_unlocked]]]*/
/*AUTO*/{
	return libc_fputwc_unlocked(wc, __LOCAL_stdin);
}
/*[[[end:putwchar_unlocked]]]*/

/*[[[head:DOS$wcsnrtombs,hash:0xa1802129]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.wcsnrtombs") size_t
NOTHROW_NCX(LIBDCALL libd_wcsnrtombs)(char *dst,
                                      char16_t const **__restrict psrc,
                                      size_t nwc,
                                      size_t len,
                                      mbstate_t *ps)
/*[[[body:DOS$wcsnrtombs]]]*/
{
	CRT_UNIMPLEMENTED("wcsnrtombs"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$wcsnrtombs]]]*/


/*[[[head:DOS$wcswidth,hash:0xeb77117a]]]*/
INTERN WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.wcswidth") int
NOTHROW_NCX(LIBDCALL libd_wcswidth)(char16_t const *__restrict string,
                                    size_t num_chars)
/*[[[body:DOS$wcswidth]]]*/
{
	CRT_UNIMPLEMENTED("wcswidth"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wcswidth]]]*/

/*[[[head:DOS$wcwidth,hash:0x26ae6e77]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.wcwidth") int
NOTHROW_NCX(LIBDCALL libd_wcwidth)(char16_t ch)
/*[[[body:DOS$wcwidth]]]*/
{
	CRT_UNIMPLEMENTED("wcwidth"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:DOS$wcwidth]]]*/

/*[[[head:fputws_unlocked,hash:0xe12f40ca]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.write.fputws_unlocked") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_fputws_unlocked)(char32_t const *__restrict string,
                                FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fputws_unlocked]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	result = libc_file_wprinter_unlocked(stream, string, libc_wcslen(string));
	return result;
}
/*[[[end:fputws_unlocked]]]*/

/*[[[head:wcsnrtombs,hash:0x5259bdda]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wcsnrtombs") size_t
NOTHROW_NCX(LIBCCALL libc_wcsnrtombs)(char *dst,
                                      char32_t const **__restrict psrc,
                                      size_t nwc,
                                      size_t len,
                                      mbstate_t *ps)
/*[[[body:wcsnrtombs]]]*/
{
	CRT_UNIMPLEMENTED("wcsnrtombs"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:wcsnrtombs]]]*/

/*[[[head:getwchar_unlocked,hash:0x6042171a]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.getc.getwchar_unlocked") wint_t
(LIBCCALL libc_getwchar_unlocked)(void)
		__THROWS(...)
/*[[[body:getwchar_unlocked]]]*/
/*AUTO*/{
	return libc_fgetwc_unlocked(__LOCAL_stdin);
}
/*[[[end:getwchar_unlocked]]]*/

/*[[[head:wcsdup,hash:0xa55a3cc2]]]*/
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.heap.strdup.wcsdup") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsdup)(char32_t const *__restrict string)
/*[[[body:wcsdup]]]*/
/*AUTO*/{
	size_t resultsize = (libc_wcslen(string) + 1) * sizeof(char32_t);
	char32_t *result = (char32_t *)libc_malloc(resultsize);
	if likely(result)
		memcpy(result, string, resultsize);
	return result;
}
/*[[[end:wcsdup]]]*/

/*[[[head:mbsnrtowcs,hash:0x4e0883c4]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.mbsnrtowcs") size_t
NOTHROW_NCX(LIBCCALL libc_mbsnrtowcs)(char32_t *dst,
                                      char const **__restrict psrc,
                                      size_t nmc,
                                      size_t len,
                                      mbstate_t *ps)
/*[[[body:mbsnrtowcs]]]*/
{
	CRT_UNIMPLEMENTED("mbsnrtowcs"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:mbsnrtowcs]]]*/



/*[[[head:DOS$wcsdup,hash:0xf289760a]]]*/
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.heap.strdup.wcsdup") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsdup)(char16_t const *__restrict string)
/*[[[body:DOS$wcsdup]]]*/
/*AUTO*/{
	size_t resultsize = (libd_wcslen(string) + 1) * sizeof(char16_t);
	char16_t *result = (char16_t *)libc_malloc(resultsize);
	if likely(result)
		libc_memcpy(result, string, resultsize);
	return result;
}
/*[[[end:DOS$wcsdup]]]*/

/*[[[head:wcwidth,hash:0x5afd12ed]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wcwidth") int
NOTHROW_NCX(LIBCCALL libc_wcwidth)(char32_t ch)
/*[[[body:wcwidth]]]*/
{
	CRT_UNIMPLEMENTED("wcwidth"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:wcwidth]]]*/


/*[[[head:DOS$mbsnrtowcs,hash:0x4847aa7d]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.mbsnrtowcs") size_t
NOTHROW_NCX(LIBDCALL libd_mbsnrtowcs)(char16_t *dst,
                                      char const **__restrict psrc,
                                      size_t nmc,
                                      size_t len,
                                      mbstate_t *ps)
/*[[[body:DOS$mbsnrtowcs]]]*/
{
	CRT_UNIMPLEMENTED("mbsnrtowcs"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$mbsnrtowcs]]]*/

/*[[[head:__wcserror_s,hash:0xaf5245e]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno.__wcserror_s") errno_t
NOTHROW_NCX(LIBCCALL libc___wcserror_s)(char32_t *buf,
                                        size_t bufsize,
                                        char32_t const *message)
/*[[[body:__wcserror_s]]]*/
{
	CRT_UNIMPLEMENTED("__wcserror_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:__wcserror_s]]]*/

/*[[[head:_wcserror_s,hash:0xd89be10b]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno._wcserror_s") errno_t
NOTHROW_NCX(LIBCCALL libc__wcserror_s)(char32_t *buf,
                                       size_t bufsize,
                                       int errno_value)
/*[[[body:_wcserror_s]]]*/
{
	CRT_UNIMPLEMENTED("_wcserror_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_wcserror_s]]]*/

/*[[[head:DOS$_wcserror_s,hash:0x4e0267d]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno._wcserror_s") errno_t
NOTHROW_NCX(LIBDCALL libd__wcserror_s)(char16_t *buf,
                                       size_t bufsize,
                                       int errno_value)
/*[[[body:DOS$_wcserror_s]]]*/
{
	CRT_UNIMPLEMENTED("_wcserror_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$_wcserror_s]]]*/

/*[[[head:DOS$_wcserror,hash:0x48442ea6]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno._wcserror") char16_t *
NOTHROW_NCX(LIBDCALL libd__wcserror)(int errno_value)
/*[[[body:DOS$_wcserror]]]*/
{
	CRT_UNIMPLEMENTED("_wcserror"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$_wcserror]]]*/

/*[[[head:__wcserror,hash:0xefc20bf6]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno.__wcserror") char32_t *
NOTHROW_NCX(LIBCCALL libc___wcserror)(char32_t const *message)
/*[[[body:__wcserror]]]*/
{
	CRT_UNIMPLEMENTED("__wcserror"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__wcserror]]]*/

/*[[[head:DOS$__wcserror,hash:0x3700b31f]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno.__wcserror") char16_t *
NOTHROW_NCX(LIBDCALL libd___wcserror)(char16_t const *message)
/*[[[body:DOS$__wcserror]]]*/
{
	CRT_UNIMPLEMENTED("__wcserror"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$__wcserror]]]*/

/*[[[head:DOS$__wcserror_s,hash:0x1fccf114]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno.__wcserror_s") errno_t
NOTHROW_NCX(LIBDCALL libd___wcserror_s)(char16_t *buf,
                                        size_t bufsize,
                                        char16_t const *message)
/*[[[body:DOS$__wcserror_s]]]*/
{
	CRT_UNIMPLEMENTED("__wcserror_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$__wcserror_s]]]*/

/*[[[head:_wcserror,hash:0xbe521e5e]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno._wcserror") char32_t *
NOTHROW_NCX(LIBCCALL libc__wcserror)(int errno_value)
/*[[[body:_wcserror]]]*/
{
	CRT_UNIMPLEMENTED("_wcserror"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:_wcserror]]]*/

/*[[[head:DOS$getwchar_unlocked,hash:0x983cf62c]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.getc.getwchar_unlocked") wint_t
(LIBDCALL libd_getwchar_unlocked)(void)
		__THROWS(...)
/*[[[body:DOS$getwchar_unlocked]]]*/
/*AUTO*/{
	return libd_fgetwc_unlocked(__LOCAL_stdin);
}
/*[[[end:DOS$getwchar_unlocked]]]*/

/*[[[head:DOS$putwchar_unlocked,hash:0x39bb6367]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.putc.putwchar_unlocked") wint_t
(LIBDCALL libd_putwchar_unlocked)(char16_t wc)
		__THROWS(...)
/*[[[body:DOS$putwchar_unlocked]]]*/
/*AUTO*/{
	return libd_fputwc_unlocked(wc, __LOCAL_stdin);
}
/*[[[end:DOS$putwchar_unlocked]]]*/



/*[[[head:DOS$fputws_unlocked,hash:0x456ac196]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.write.fputws_unlocked") __STDC_INT_AS_SIZE_T
(LIBDCALL libd_fputws_unlocked)(char16_t const *__restrict string,
                                FILE *__restrict stream)
		__THROWS(...)
/*[[[body:DOS$fputws_unlocked]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	result = libd_file_wprinter_unlocked(stream, string, libd_wcslen(string));
	return result;
}
/*[[[end:DOS$fputws_unlocked]]]*/

/*[[[head:wcsndup,hash:0x22f9e085]]]*/
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.heap.strdup.wcsndup") char32_t *
NOTHROW_NCX(LIBCCALL libc_wcsndup)(char32_t const *__restrict string,
                                   size_t max_chars)
/*[[[body:wcsndup]]]*/
/*AUTO*/{
	size_t resultlen = libc_wcsnlen(string, max_chars);
	char32_t *result = (char32_t *)libc_malloc((resultlen + 1) * sizeof(char32_t));
	if likely(result)
		*libc_wmempcpy(result, string, resultlen) = '\0';
	return result;
}
/*[[[end:wcsndup]]]*/

/*[[[head:DOS$wcsndup,hash:0x8caba3c8]]]*/
INTERN WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.heap.strdup.wcsndup") char16_t *
NOTHROW_NCX(LIBDCALL libd_wcsndup)(char16_t const *__restrict string,
                                   size_t max_chars)
/*[[[body:DOS$wcsndup]]]*/
/*AUTO*/{
	size_t resultlen = libd_wcsnlen(string, max_chars);
	char16_t *result = (char16_t *)libc_malloc((resultlen + 1) * sizeof(char16_t));
	if likely(result)
		*libd_wmempcpy(result, string, resultlen) = '\0';
	return result;
}
/*[[[end:DOS$wcsndup]]]*/


/*[[[head:file_wprinter,hash:0xcdbe64f0]]]*/
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.write.file_wprinter") ssize_t
(LIBCCALL libc_file_wprinter)(void *arg,
                              char32_t const *__restrict data,
                              size_t datalen)
		__THROWS(...)
/*[[[body:file_wprinter]]]*/
/*AUTO*/{
	size_t i;
	for (i = 0; i < datalen; ++i) {
		if (libc_fputwc(data[i], (FILE *)arg) == __WEOF)
			break;
	}
	return (ssize_t)i;
}
/*[[[end:file_wprinter]]]*/

/*[[[head:wprintf_unlocked,hash:0x2c6f9a8e]]]*/
INTERN ATTR_LIBC_WPRINTF(1, 2) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf.wprintf_unlocked") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_wprintf_unlocked)(char32_t const *__restrict format,
                                  ...)
		__THROWS(...)
/*[[[body:wprintf_unlocked]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vwprintf_unlocked(format, args);
	va_end(args);
	return result;
}
/*[[[end:wprintf_unlocked]]]*/

/*[[[head:DOS$wprintf_unlocked,hash:0xc1db1645]]]*/
INTERN ATTR_LIBC_WPRINTF(1, 2) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf.wprintf_unlocked") __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_wprintf_unlocked)(char16_t const *__restrict format,
                                  ...)
		__THROWS(...)
/*[[[body:DOS$wprintf_unlocked]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vwprintf_unlocked(format, args);
	va_end(args);
	return result;
}
/*[[[end:DOS$wprintf_unlocked]]]*/

/*[[[head:vwprintf_unlocked,hash:0xf8aa98a6]]]*/
INTERN ATTR_LIBC_WPRINTF(1, 0) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf.vwprintf_unlocked") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vwprintf_unlocked)(char32_t const *__restrict format,
                                  va_list args)
		__THROWS(...)
/*[[[body:vwprintf_unlocked]]]*/
/*AUTO*/{
	return libc_vfwprintf_unlocked(__LOCAL_stdout, format, args);
}
/*[[[end:vwprintf_unlocked]]]*/

/*[[[head:DOS$vwprintf_unlocked,hash:0x201529b]]]*/
INTERN ATTR_LIBC_WPRINTF(1, 0) NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf.vwprintf_unlocked") __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vwprintf_unlocked)(char16_t const *__restrict format,
                                  va_list args)
		__THROWS(...)
/*[[[body:DOS$vwprintf_unlocked]]]*/
/*AUTO*/{
	return libd_vfwprintf_unlocked(__LOCAL_stdout, format, args);
}
/*[[[end:DOS$vwprintf_unlocked]]]*/

/*[[[head:vwscanf_unlocked,hash:0x6a77852d]]]*/
INTERN ATTR_LIBC_SCANF(1, 0) WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf.vwscanf_unlocked") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vwscanf_unlocked)(char32_t const *__restrict format,
                                 va_list args)
		__THROWS(...)
/*[[[body:vwscanf_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("vwscanf_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:vwscanf_unlocked]]]*/

/*[[[head:fwscanf_unlocked,hash:0xedc2051]]]*/
INTERN ATTR_LIBC_SCANF(2, 3) WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf.fwscanf_unlocked") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_fwscanf_unlocked)(FILE *__restrict stream,
                                  char32_t const *__restrict format,
                                  ...)
		__THROWS(...)
/*[[[body:fwscanf_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("fwscanf_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:fwscanf_unlocked]]]*/

/*[[[head:wscanf_unlocked,hash:0xb7786398]]]*/
INTERN ATTR_LIBC_SCANF(1, 2) WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf.wscanf_unlocked") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_wscanf_unlocked)(char32_t const *__restrict format,
                                 ...)
		__THROWS(...)
/*[[[body:wscanf_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("wscanf_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:wscanf_unlocked]]]*/

/*[[[head:file_wprinter_unlocked,hash:0xfd9a3c4a]]]*/
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.write.file_wprinter_unlocked") ssize_t
(LIBCCALL libc_file_wprinter_unlocked)(void *arg,
                                       char32_t const *__restrict data,
                                       size_t datalen)
		__THROWS(...)
/*[[[body:file_wprinter_unlocked]]]*/
/*AUTO*/{
	size_t i;
	for (i = 0; i < datalen; ++i) {
		if (libc_fputwc_unlocked(data[i], (FILE *)arg) == __WEOF)
			break;
	}
	return (ssize_t)i;
}
/*[[[end:file_wprinter_unlocked]]]*/

/*[[[head:DOS$file_wprinter,hash:0x7b7b0de9]]]*/
/* For use with `format_printf()' and friends: Prints to a `$FILE *' closure argument */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.write.file_wprinter") ssize_t
(LIBDCALL libd_file_wprinter)(void *arg,
                              char16_t const *__restrict data,
                              size_t datalen)
		__THROWS(...)
/*[[[body:DOS$file_wprinter]]]*/
/*AUTO*/{
	size_t i;
	for (i = 0; i < datalen; ++i) {
		if (libd_fputwc(data[i], (FILE *)arg) == __WEOF)
			break;
	}
	return (ssize_t)i;
}
/*[[[end:DOS$file_wprinter]]]*/

/*[[[head:DOS$file_wprinter_unlocked,hash:0xb10329e1]]]*/
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.write.file_wprinter_unlocked") ssize_t
(LIBDCALL libd_file_wprinter_unlocked)(void *arg,
                                       char16_t const *__restrict data,
                                       size_t datalen)
		__THROWS(...)
/*[[[body:DOS$file_wprinter_unlocked]]]*/
/*AUTO*/{
	size_t i;
	for (i = 0; i < datalen; ++i) {
		if (libd_fputwc_unlocked(data[i], (FILE *)arg) == __WEOF)
			break;
	}
	return (ssize_t)i;
}
/*[[[end:DOS$file_wprinter_unlocked]]]*/

/*[[[head:DOS$vwscanf_unlocked,hash:0x85ec3861]]]*/
INTERN ATTR_LIBC_SCANF(1, 0) WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf.vwscanf_unlocked") __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vwscanf_unlocked)(char16_t const *__restrict format,
                                 va_list args)
		__THROWS(...)
/*[[[body:DOS$vwscanf_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("vwscanf_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$vwscanf_unlocked]]]*/

/*[[[head:DOS$fwscanf_unlocked,hash:0xcfc460ba]]]*/
INTERN ATTR_LIBC_SCANF(2, 3) WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf.fwscanf_unlocked") __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fwscanf_unlocked)(FILE *__restrict stream,
                                  char16_t const *__restrict format,
                                  ...)
		__THROWS(...)
/*[[[body:DOS$fwscanf_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("fwscanf_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$fwscanf_unlocked]]]*/

/*[[[head:DOS$wscanf_unlocked,hash:0x2c860daa]]]*/
INTERN ATTR_LIBC_SCANF(1, 2) WUNUSED NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf.wscanf_unlocked") __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_wscanf_unlocked)(char16_t const *__restrict format,
                                 ...)
		__THROWS(...)
/*[[[body:DOS$wscanf_unlocked]]]*/
{
	CRT_UNIMPLEMENTED("wscanf_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$wscanf_unlocked]]]*/

/*[[[head:fwprintf,hash:0xca4b8819]]]*/
INTERN ATTR_LIBC_WPRINTF(2, 3) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf.fwprintf") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_fwprintf)(FILE *__restrict stream,
                          char32_t const *__restrict format,
                          ...)
		__THROWS(...)
/*[[[body:fwprintf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwprintf(stream, format, args);
	va_end(args);
	return result;
}
/*[[[end:fwprintf]]]*/

/*[[[head:DOS$fwprintf,hash:0xf5a5e914]]]*/
INTERN ATTR_LIBC_WPRINTF(2, 3) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf.fwprintf") __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fwprintf)(FILE *__restrict stream,
                          char16_t const *__restrict format,
                          ...)
		__THROWS(...)
/*[[[body:DOS$fwprintf]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwprintf(stream, format, args);
	va_end(args);
	return result;
}
/*[[[end:DOS$fwprintf]]]*/

/*[[[head:vfwprintf,hash:0xbd554a62]]]*/
INTERN ATTR_LIBC_WPRINTF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.printf.vfwprintf") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vfwprintf)(FILE *__restrict stream,
                          char32_t const *__restrict format,
                          va_list args)
		__THROWS(...)
/*[[[body:vfwprintf]]]*/
/*AUTO*/{
	return (__STDC_INT_AS_SSIZE_T)libc_format_vwprintf(&libc_file_wprinter, stream, format, args);
}
/*[[[end:vfwprintf]]]*/

/*[[[head:DOS$vfwprintf,hash:0x27e6e35a]]]*/
INTERN ATTR_LIBC_WPRINTF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.printf.vfwprintf") __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vfwprintf)(FILE *__restrict stream,
                          char16_t const *__restrict format,
                          va_list args)
		__THROWS(...)
/*[[[body:DOS$vfwprintf]]]*/
/*AUTO*/{
	return (__STDC_INT_AS_SSIZE_T)libd_format_vwprintf(&libd_file_wprinter, stream, format, args);
}
/*[[[end:DOS$vfwprintf]]]*/

/*[[[head:vfwprintf_unlocked,hash:0xea3a17cd]]]*/
INTERN ATTR_LIBC_WPRINTF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf.vfwprintf_unlocked") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vfwprintf_unlocked)(FILE *__restrict stream,
                                   char32_t const *__restrict format,
                                   va_list args)
		__THROWS(...)
/*[[[body:vfwprintf_unlocked]]]*/
/*AUTO*/{
	return (__STDC_INT_AS_SSIZE_T)libc_format_vwprintf(&libc_file_wprinter_unlocked, stream, format, args);
}
/*[[[end:vfwprintf_unlocked]]]*/

/*[[[head:DOS$vfwprintf_unlocked,hash:0xa573f594]]]*/
INTERN ATTR_LIBC_WPRINTF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf.vfwprintf_unlocked") __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vfwprintf_unlocked)(FILE *__restrict stream,
                                   char16_t const *__restrict format,
                                   va_list args)
		__THROWS(...)
/*[[[body:DOS$vfwprintf_unlocked]]]*/
/*AUTO*/{
	return (__STDC_INT_AS_SSIZE_T)libd_format_vwprintf(&libd_file_wprinter_unlocked, stream, format, args);
}
/*[[[end:DOS$vfwprintf_unlocked]]]*/

/*[[[head:fwprintf_unlocked,hash:0xdcd96ee2]]]*/
INTERN ATTR_LIBC_WPRINTF(2, 3) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.printf.fwprintf_unlocked") __STDC_INT_AS_SIZE_T
(VLIBCCALL libc_fwprintf_unlocked)(FILE *__restrict stream,
                                   char32_t const *__restrict format,
                                   ...)
		__THROWS(...)
/*[[[body:fwprintf_unlocked]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libc_vfwprintf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
/*[[[end:fwprintf_unlocked]]]*/

/*[[[head:DOS$fwprintf_unlocked,hash:0x58a576a7]]]*/
INTERN ATTR_LIBC_WPRINTF(2, 3) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.printf.fwprintf_unlocked") __STDC_INT_AS_SIZE_T
(VLIBDCALL libd_fwprintf_unlocked)(FILE *__restrict stream,
                                   char16_t const *__restrict format,
                                   ...)
		__THROWS(...)
/*[[[body:DOS$fwprintf_unlocked]]]*/
/*AUTO*/{
	__STDC_INT_AS_SIZE_T result;
	va_list args;
	va_start(args, format);
	result = libd_vfwprintf_unlocked(stream, format, args);
	va_end(args);
	return result;
}
/*[[[end:DOS$fwprintf_unlocked]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x419319c0]]]*/
#undef fwprintf
#undef wprintf
#undef fwscanf
#undef fwscanf_unlocked
#undef wscanf
#undef wscanf_unlocked
#undef fwprintf_unlocked
#undef wprintf_unlocked
#undef fwscanf_unlocked
#undef wscanf_unlocked
DEFINE_PUBLIC_WEAK_ALIAS(getwchar, libc_getwchar);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$getwchar, libd_getwchar);
DEFINE_PUBLIC_WEAK_ALIAS(fgetwc, libc_fgetwc);
DEFINE_PUBLIC_WEAK_ALIAS(getwc, libc_fgetwc);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fgetwc, libd_fgetwc);
DEFINE_PUBLIC_WEAK_ALIAS(putwchar, libc_putwchar);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$putwchar, libd_putwchar);
DEFINE_PUBLIC_WEAK_ALIAS(fputwc, libc_fputwc);
DEFINE_PUBLIC_WEAK_ALIAS(putwc, libc_fputwc);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fputwc, libd_fputwc);
DEFINE_PUBLIC_WEAK_ALIAS(fgetws, libc_fgetws);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fgetws, libd_fgetws);
DEFINE_PUBLIC_WEAK_ALIAS(fputws, libc_fputws);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fputws, libd_fputws);
DEFINE_PUBLIC_WEAK_ALIAS(ungetwc, libc_ungetwc);
DEFINE_PUBLIC_WEAK_ALIAS(ungetwc_unlocked, libc_ungetwc);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$ungetwc, libd_ungetwc);
DEFINE_PUBLIC_WEAK_ALIAS(fwprintf, libc_fwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fwprintf, libd_fwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vfwprintf, libc_vfwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vfwprintf, libd_vfwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(wprintf, libc_wprintf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wprintf, libd_wprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vwprintf, libc_vwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vwprintf, libd_vwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(fwscanf, libc_fwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(fwscanf_unlocked, libc_fwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fwscanf, libd_fwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(wscanf, libc_wscanf);
DEFINE_PUBLIC_WEAK_ALIAS(wscanf_unlocked, libc_wscanf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wscanf, libd_wscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vfwscanf, libc_vfwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vfwscanf_unlocked, libc_vfwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vfwscanf, libd_vfwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vwscanf, libc_vwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vwscanf_unlocked, libc_vwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vwscanf, libd_vwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(mbsnrtowcs, libc_mbsnrtowcs);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$mbsnrtowcs, libd_mbsnrtowcs);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnrtombs, libc_wcsnrtombs);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnrtombs, libd_wcsnrtombs);
DEFINE_PUBLIC_WEAK_ALIAS(open_wmemstream, libc_open_wmemstream);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$open_wmemstream, libd_open_wmemstream);
DEFINE_PUBLIC_WEAK_ALIAS(wcsdup, libc_wcsdup);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsdup, libc_wcsdup);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsdup, libd_wcsdup);
DEFINE_PUBLIC_WEAK_ALIAS(wcwidth, libc_wcwidth);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcwidth, libd_wcwidth);
DEFINE_PUBLIC_WEAK_ALIAS(wcswidth, libc_wcswidth);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcswidth, libd_wcswidth);
DEFINE_PUBLIC_WEAK_ALIAS(getwchar_unlocked, libc_getwchar_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$getwchar_unlocked, libd_getwchar_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(putwchar_unlocked, libc_putwchar_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$putwchar_unlocked, libd_putwchar_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fgetwc_unlocked, libc_fgetwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(getwc_unlocked, libc_fgetwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fgetwc_unlocked, libd_fgetwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fputwc_unlocked, libc_fputwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(putwc_unlocked, libc_fputwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fputwc_unlocked, libd_fputwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fgetws_unlocked, libc_fgetws_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fgetws_unlocked, libd_fgetws_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fputws_unlocked, libc_fputws_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fputws_unlocked, libd_fputws_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(file_wprinter, libc_file_wprinter);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$file_wprinter, libd_file_wprinter);
DEFINE_PUBLIC_WEAK_ALIAS(file_wprinter_unlocked, libc_file_wprinter_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$file_wprinter_unlocked, libd_file_wprinter_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(ungetwc_unlocked, libc_ungetwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$ungetwc_unlocked, libd_ungetwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vfwprintf_unlocked, libc_vfwprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vfwprintf_unlocked, libd_vfwprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fwprintf_unlocked, libc_fwprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fwprintf_unlocked, libd_fwprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(wprintf_unlocked, libc_wprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wprintf_unlocked, libd_wprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vwprintf_unlocked, libc_vwprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vwprintf_unlocked, libd_vwprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vwscanf_unlocked, libc_vwscanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vwscanf_unlocked, libd_vwscanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fwscanf_unlocked, libc_fwscanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fwscanf_unlocked, libd_fwscanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(wscanf_unlocked, libc_wscanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wscanf_unlocked, libd_wscanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(wcsndup, libc_wcsndup);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsndup, libd_wcsndup);
DEFINE_PUBLIC_WEAK_ALIAS(_wcserror, libc__wcserror);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wcserror, libd__wcserror);
DEFINE_PUBLIC_WEAK_ALIAS(_wcserror_s, libc__wcserror_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wcserror_s, libd__wcserror_s);
DEFINE_PUBLIC_WEAK_ALIAS(__wcserror, libc___wcserror);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$__wcserror, libd___wcserror);
DEFINE_PUBLIC_WEAK_ALIAS(__wcserror_s, libc___wcserror_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$__wcserror_s, libd___wcserror_s);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_WCHAR_C */
