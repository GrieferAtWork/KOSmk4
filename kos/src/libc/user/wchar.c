/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_WCHAR_C
#define GUARD_LIBC_USER_WCHAR_C 1

#include "../api.h"
/**/

#include <stdio.h>
#include <string.h>
#include <uchar.h>
#include <unicode.h>

#include <libc/unicode.h>

#include "../auto/parts.wchar.format-printer.h"
#include "../libc/globals.h"
#include "../libc/uchar.h"
#include "malloc.h"
#include "stdio-api.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "wchar.h"

DECL_BEGIN

#define file_print16 libd_file_wprinter_unlocked
#define file_print32 libc_file_wprinter_unlocked

/* The DOS version of wcstok() doesn't take the 3rd safe-ptr argument,
 * but rather only takes 2  arguments (under DOS, the 3-argument  form
 * carries the name `wcstok_s')
 * Define this special variant manually, since magic wouldn't  understand
 * some weird function that only exists in DOS-mode, but uses a name that
 * is bound to a different function in KOS-mode... */
PRIVATE ATTR_SECTION(".bss.crt.dos.wchar.string.memory")
char16_t *wcstok_safe_ptr = NULL;

DEFINE_PUBLIC_ALIAS(DOS$wcstok, libd_wcstok_nosafe);
INTERN ATTR_SECTION(".text.crt.dos.wchar.string.memory") NONNULL((2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_wcstok_nosafe)(char16_t *string,
                                         char16_t const *__restrict delim) {
	return libd_wcstok(string, delim, &wcstok_safe_ptr);
}





/*[[[head:libc_fgetwc_unlocked,hash:CRC-32=0x839ec077]]]*/
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.getc") NONNULL((1)) wint32_t
(LIBKCALL libc_fgetwc_unlocked)(FILE *__restrict stream) THROWS(...)
/*[[[body:libc_fgetwc_unlocked]]]*/
{
	wint32_t result;
	struct iofile_data *ex;
	assert(stream);
	ex = stream->if_exdata;
	assert(ex);
	/* Try to complete an in-progress utf-8 sequence. */
	for (;;) {
		size_t error;
		char buf[1];
		char32_t ch32;
		int ch;
		ch = file_getc(stream);
		if (ch == EOF) {
			result = WEOF32;
			goto done;
		}
		buf[0] = (char)(unsigned char)(unsigned int)ch;
		error  = unicode_c8toc32(&ch32, buf, 1, &ex->io_mbs);
		result = (wint32_t)ch32;
		if likely(error > 0) /* Completed sequence. */
			goto done;
		if unlikely(error == (size_t)-1) {
			/* Unicode error. */
			libc_seterrno(EILSEQ);
			stream->if_flag |= IO_ERR;
			result = WEOF32;
			goto done;
		}
		/* Incomplete sequence (continue reading...) */
	}
done:
	return result;
}
/*[[[end:libc_fgetwc_unlocked]]]*/

/*[[[head:libd_fgetwc_unlocked,hash:CRC-32=0xe139aa1c]]]*/
/* >> getwc_unlocked(3), fgetwc_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.getc") NONNULL((1)) wint16_t
(LIBDCALL libd_fgetwc_unlocked)(FILE *__restrict stream) THROWS(...)
/*[[[body:libd_fgetwc_unlocked]]]*/
{
	wint16_t result;
	struct iofile_data *ex;
	assert(stream);
	ex = stream->if_exdata;
	assert(ex);
	/* Check for a pending surrogate */
	if ((ex->io_mbs.__mb_word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_WR_UTF16_LO) {
		result = (char16_t)(0xdc00 + (ex->io_mbs.__mb_word & 0x000003ff));
		ex->io_mbs.__mb_word = __MBSTATE_TYPE_EMPTY;
		goto done;
	}
	/* Try to complete an in-progress utf-8 sequence. */
	for (;;) {
		size_t error;
		char buf[1];
		char16_t ch16;
		int ch;
		ch = file_getc(stream);
		if (ch == EOF) {
			result = WEOF16;
			goto done;
		}
		buf[0] = (char)(unsigned char)(unsigned int)ch;
		error  = unicode_c8toc16(&ch16, buf, 1, &ex->io_mbs);
		result = (wint16_t)ch16;
		if likely(error > 0) /* Completed sequence. */
			goto done;
		if unlikely(error == 0) {
			/* Shouldn't happen (a surrogate was written) */
			if (file_ungetc(stream, (unsigned char)buf[0]) == EOF)
				result = WEOF16;
			goto done;
		}
		if unlikely(error == (size_t)-1) {
			/* Unicode error. */
			libc_seterrno(EILSEQ);
			stream->if_flag |= IO_ERR;
			result = WEOF16;
			goto done;
		}
		/* Incomplete sequence (continue reading...) */
	}
done:
	return result;
}
/*[[[end:libd_fgetwc_unlocked]]]*/

/*[[[head:libc_fgetwc,hash:CRC-32=0xacc4c7b5]]]*/
/* >> fgetwc(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.getc") NONNULL((1)) wint32_t
(LIBKCALL libc_fgetwc)(FILE *__restrict stream) THROWS(...)
/*[[[body:libc_fgetwc]]]*/
{
	wint32_t result;
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = libc_fgetwc_unlocked(stream);
		file_lock_endwrite(stream);
	} else {
		result = libc_fgetwc_unlocked(stream);
	}
	return result;
}
/*[[[end:libc_fgetwc]]]*/

/*[[[head:libd_fgetwc,hash:CRC-32=0xf509c84]]]*/
/* >> fgetwc(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.getc") NONNULL((1)) wint16_t
(LIBDCALL libd_fgetwc)(FILE *__restrict stream) THROWS(...)
/*[[[body:libd_fgetwc]]]*/
{
	wint16_t result;
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = libd_fgetwc_unlocked(stream);
		file_lock_endwrite(stream);
	} else {
		result = libd_fgetwc_unlocked(stream);
	}
	return result;
}
/*[[[end:libd_fgetwc]]]*/

/*[[[head:libc_ungetwc_unlocked,hash:CRC-32=0xd5d3a3ce]]]*/
/* >> ungetwc_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.putc") NONNULL((2)) wint32_t
NOTHROW_NCX(LIBKCALL libc_ungetwc_unlocked)(wint32_t ch,
                                            FILE *__restrict stream)
/*[[[body:libc_ungetwc_unlocked]]]*/
{
	wint32_t result = ch;
	char buf[UNICODE_UTF8_CURLEN], *end;
	end = unicode_writeutf8(buf, (char32_t)ch);
	assert(end > buf);
	do {
		--end;
		if (file_ungetc(stream, (unsigned char)*end) == EOF) {
			result = WEOF32;
			break;
		}
	} while (end > buf);
	return result;
}
/*[[[end:libc_ungetwc_unlocked]]]*/

/*[[[head:libd_ungetwc_unlocked,hash:CRC-32=0x5e19cd15]]]*/
/* >> ungetwc_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.putc") NONNULL((2)) wint16_t
NOTHROW_NCX(LIBDCALL libd_ungetwc_unlocked)(wint16_t ch,
                                            FILE *__restrict stream)
/*[[[body:libd_ungetwc_unlocked]]]*/
{
	char32_t unget_char;
	wint16_t result = ch;
	struct iofile_data *ex;
	assert(stream);
	ex = stream->if_exdata;
	assert(ex);
	/* Check for a pending surrogate */
	if ((ex->io_mbs.__mb_word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_WR_UTF16_LO) {
		char16_t lo_surrogate;
		if unlikely((char16_t)ch < UTF16_HIGH_SURROGATE_MIN ||
		            (char16_t)ch > UTF16_HIGH_SURROGATE_MAX) {
set_ilseq:
			libc_seterrno(EILSEQ);
			stream->if_flag |= IO_ERR;
			result = WEOF16;
			goto done;
		}
		lo_surrogate = (char16_t)(0xdc00 + (ex->io_mbs.__mb_word & 0x000003ff));
		ex->io_mbs.__mb_word = __MBSTATE_TYPE_EMPTY;
		unget_char = (char32_t)(char16_t)ch;
		unget_char -= 0xd800;
		unget_char <<= 10;
		unget_char += 0x10000 - 0xdc00;
		unget_char += lo_surrogate;
	} else {
		if unlikely((char16_t)ch >= UTF16_HIGH_SURROGATE_MIN &&
		            (char16_t)ch <= UTF16_HIGH_SURROGATE_MAX)
			goto set_ilseq;
		unget_char = (char32_t)(char16_t)ch;
	}
	if (libc_ungetwc_unlocked(unget_char, stream) == WEOF32)
		result = WEOF16;
done:
	return result;
}
/*[[[end:libd_ungetwc_unlocked]]]*/

/*[[[head:libc_ungetwc,hash:CRC-32=0x683303b7]]]*/
/* >> ungetwc(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.putc") NONNULL((2)) wint32_t
NOTHROW_NCX(LIBKCALL libc_ungetwc)(wint32_t wc,
                                   FILE *stream)
/*[[[body:libc_ungetwc]]]*/
{
	wint32_t result;
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = libc_ungetwc_unlocked(wc, stream);
		file_lock_endwrite(stream);
	} else {
		result = libc_ungetwc_unlocked(wc, stream);
	}
	return result;
}
/*[[[end:libc_ungetwc]]]*/

/*[[[head:libd_ungetwc,hash:CRC-32=0x1f731a9c]]]*/
/* >> ungetwc(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.putc") NONNULL((2)) wint16_t
NOTHROW_NCX(LIBDCALL libd_ungetwc)(wint16_t wc,
                                   FILE *stream)
/*[[[body:libd_ungetwc]]]*/
{
	wint16_t result;
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		result = libd_ungetwc_unlocked(wc, stream);
		file_lock_endwrite(stream);
	} else {
		result = libd_ungetwc_unlocked(wc, stream);
	}
	return result;
}
/*[[[end:libd_ungetwc]]]*/

/*[[[head:libc_fputwc_unlocked,hash:CRC-32=0x7885a901]]]*/
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.putc") NONNULL((2)) wint32_t
(LIBKCALL libc_fputwc_unlocked)(char32_t wc,
                                FILE *__restrict stream) THROWS(...)
/*[[[body:libc_fputwc_unlocked]]]*/
{
	wint32_t result = (wint32_t)wc;
	if (file_print32(stream, &wc, 1) <= 0)
		result = WEOF32;
	return result;
}
/*[[[end:libc_fputwc_unlocked]]]*/

/*[[[head:libd_fputwc_unlocked,hash:CRC-32=0x5d2c7ae4]]]*/
/* >> putwc_unlocked(3), fputwc_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.putc") NONNULL((2)) wint16_t
(LIBDCALL libd_fputwc_unlocked)(char16_t wc,
                                FILE *__restrict stream) THROWS(...)
/*[[[body:libd_fputwc_unlocked]]]*/
{
	wint16_t result = (wint16_t)wc;
	if (file_print16(stream, &wc, 1) <= 0)
		result = WEOF16;
	return result;
}
/*[[[end:libd_fputwc_unlocked]]]*/

/*[[[head:libc_fputwc,hash:CRC-32=0xd77eafab]]]*/
/* >> fputwc(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.putc") NONNULL((2)) wint32_t
(LIBKCALL libc_fputwc)(char32_t wc,
                       FILE *stream) THROWS(...)
/*[[[body:libc_fputwc]]]*/
{
	ssize_t error;
	wint32_t result = (wint32_t)wc;
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		error = file_print32(stream, &wc, 1);
		file_lock_endwrite(stream);
	} else {
		error = file_print32(stream, &wc, 1);
	}
	if (error <= 0)
		result = WEOF32;
	return result;
}
/*[[[end:libc_fputwc]]]*/

/*[[[head:libd_fputwc,hash:CRC-32=0xcf157d9e]]]*/
/* >> fputwc(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.putc") NONNULL((2)) wint16_t
(LIBDCALL libd_fputwc)(char16_t wc,
                       FILE *stream) THROWS(...)
/*[[[body:libd_fputwc]]]*/
{
	ssize_t error;
	wint16_t result = (wint16_t)wc;
	if (FMUSTLOCK(stream)) {
		file_lock_write(stream);
		error = file_print16(stream, &wc, 1);
		file_lock_endwrite(stream);
	} else {
		error = file_print16(stream, &wc, 1);
	}
	if (error <= 0)
		result = WEOF16;
	return result;
}
/*[[[end:libd_fputwc]]]*/

/*[[[head:libc_open_wmemstream,hash:CRC-32=0xf53c4d2d]]]*/
/* >> open_wmemstream(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.access") FILE *
NOTHROW_NCX(LIBKCALL libc_open_wmemstream)(char32_t **bufloc,
                                           size_t *sizeloc)
/*[[[body:libc_open_wmemstream]]]*/
/*AUTO*/{
	(void)bufloc;
	(void)sizeloc;
	CRT_UNIMPLEMENTEDF("open_wmemstream(%p, %p)", bufloc, sizeloc); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_open_wmemstream]]]*/

/*[[[head:libd_open_wmemstream,hash:CRC-32=0x22f94cc1]]]*/
/* >> open_wmemstream(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") FILE *
NOTHROW_NCX(LIBDCALL libd_open_wmemstream)(char16_t **bufloc,
                                           size_t *sizeloc)
/*[[[body:libd_open_wmemstream]]]*/
/*AUTO*/{
	(void)bufloc;
	(void)sizeloc;
	CRT_UNIMPLEMENTEDF("DOS$open_wmemstream(%p, %p)", bufloc, sizeloc); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd_open_wmemstream]]]*/











/*[[[head:libc_vfwscanf_unlocked,hash:CRC-32=0x3782c23a]]]*/
/* >> vfwscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vfwscanf_unlocked)(FILE *__restrict stream,
                                  char32_t const *__restrict format,
                                  va_list args) THROWS(...)
/*[[[body:libc_vfwscanf_unlocked]]]*/
/*AUTO*/{
	(void)stream;
	(void)format;
	(void)args;
	CRT_UNIMPLEMENTEDF("vfwscanf_unlocked(%p, %p, %p)", stream, format, args); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_vfwscanf_unlocked]]]*/

/*[[[head:libd_fgetwln,hash:CRC-32=0xb2994bf0]]]*/
/* >> fgetwln(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.locale.memory") WUNUSED NONNULL((1, 2)) char16_t *
NOTHROW_NCX(LIBDCALL libd_fgetwln)(FILE *__restrict fp,
                                   size_t *__restrict lenp)
/*[[[body:libd_fgetwln]]]*/
/*AUTO*/{
	(void)fp;
	(void)lenp;
	CRT_UNIMPLEMENTEDF("DOS$fgetwln(%p, %p)", fp, lenp); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd_fgetwln]]]*/

/*[[[head:libc_fgetwln,hash:CRC-32=0xde0af731]]]*/
/* >> fgetwln(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.locale.memory") WUNUSED NONNULL((1, 2)) char32_t *
NOTHROW_NCX(LIBKCALL libc_fgetwln)(FILE *__restrict fp,
                                   size_t *__restrict lenp)
/*[[[body:libc_fgetwln]]]*/
/*AUTO*/{
	(void)fp;
	(void)lenp;
	CRT_UNIMPLEMENTEDF("fgetwln(%p, %p)", fp, lenp); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_fgetwln]]]*/

/*[[[head:libd_vfwscanf_unlocked,hash:CRC-32=0xd9ad7ce7]]]*/
/* >> vfwscanf_unlocked(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf") WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vfwscanf_unlocked)(FILE *__restrict stream,
                                  char16_t const *__restrict format,
                                  va_list args) THROWS(...)
/*[[[body:libd_vfwscanf_unlocked]]]*/
/*AUTO*/{
	(void)stream;
	(void)format;
	(void)args;
	CRT_UNIMPLEMENTEDF("DOS$vfwscanf_unlocked(%p, %p, %p)", stream, format, args); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd_vfwscanf_unlocked]]]*/

/*[[[head:libc_vfwscanf,hash:CRC-32=0xdd6b097e]]]*/
/* >> vfwscanf(3) */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBKCALL libc_vfwscanf)(FILE *__restrict stream,
                         char32_t const *__restrict format,
                         va_list args) THROWS(...)
/*[[[body:libc_vfwscanf]]]*/
/*AUTO*/{
	(void)stream;
	(void)format;
	(void)args;
	CRT_UNIMPLEMENTEDF("vfwscanf(%p, %p, %p)", stream, format, args); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_vfwscanf]]]*/

/*[[[head:libd_vfwscanf,hash:CRC-32=0x1cd69c77]]]*/
/* >> vfwscanf(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf") WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2)) __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vfwscanf)(FILE *__restrict stream,
                         char16_t const *__restrict format,
                         va_list args) THROWS(...)
/*[[[body:libd_vfwscanf]]]*/
/*AUTO*/{
	(void)stream;
	(void)format;
	(void)args;
	CRT_UNIMPLEMENTEDF("DOS$vfwscanf(%p, %p, %p)", stream, format, args); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd_vfwscanf]]]*/


/*[[[head:libc_file_wprinter,hash:CRC-32=0xa52798dc]]]*/
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.locked.write.write") NONNULL((1, 2)) ssize_t
(LIBKCALL libc_file_wprinter)(void *arg,
                              char32_t const *__restrict data,
                              size_t datalen) THROWS(...)
/*[[[body:libc_file_wprinter]]]*/
{
	ssize_t result;
	FILE *me = (FILE *)arg;
	if (FMUSTLOCK(me)) {
		file_lock_write(me);
		result = file_print32(arg, data, datalen);
		file_lock_endwrite(me);
	} else {
		result = file_print32(arg, data, datalen);
	}
	return result;
}
/*[[[end:libc_file_wprinter]]]*/

/*[[[head:libc_file_wprinter_unlocked,hash:CRC-32=0xd8bf6604]]]*/
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
INTERN ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.write") NONNULL((1, 2)) ssize_t
(LIBKCALL libc_file_wprinter_unlocked)(void *arg,
                                       char32_t const *__restrict data,
                                       size_t datalen) THROWS(...)
/*[[[body:libc_file_wprinter_unlocked]]]*/
{
	struct format_32to8_data format;
	format.fd_printer = &libc_file_printer_unlocked;
	format.fd_arg     = arg;
	return format_32to8(&format, data, datalen);
}
/*[[[end:libc_file_wprinter_unlocked]]]*/

/*[[[head:libd_file_wprinter,hash:CRC-32=0xdde447d8]]]*/
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.write") NONNULL((1, 2)) ssize_t
(LIBDCALL libd_file_wprinter)(void *arg,
                              char16_t const *__restrict data,
                              size_t datalen) THROWS(...)
/*[[[body:libd_file_wprinter]]]*/
{
	ssize_t result;
	FILE *me = (FILE *)arg;
	if (FMUSTLOCK(me)) {
		file_lock_write(me);
		result = file_print16(arg, data, datalen);
		file_lock_endwrite(me);
	} else {
		result = file_print16(arg, data, datalen);
	}
	return result;
}
/*[[[end:libd_file_wprinter]]]*/

/*[[[head:libd_file_wprinter_unlocked,hash:CRC-32=0x10448251]]]*/
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.write") NONNULL((1, 2)) ssize_t
(LIBDCALL libd_file_wprinter_unlocked)(void *arg,
                                       char16_t const *__restrict data,
                                       size_t datalen) THROWS(...)
/*[[[body:libd_file_wprinter_unlocked]]]*/
{
	ssize_t result;
	struct format_16to8_data format;
	struct iofile_data *ex;
	FILE *me = (FILE *)arg;
	assert(me);
	ex = me->if_exdata;
	assert(ex);
	format.fd_arg       = arg;
	format.fd_printer   = &libc_file_printer_unlocked;
	format.fd_surrogate = 0;
	/* Check for a the pending surrogate pair */
	if ((ex->io_mbs.__mb_word & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_UTF16_LO) {
		format.fd_surrogate = 0xdc00 + (ex->io_mbs.__mb_word & 0x000003ff);
		ex->io_mbs.__mb_word = __MBSTATE_TYPE_EMPTY;
	}
	result = format_16to8(&format, data, datalen);
	/* Update the pending surrogate pair */
	if (format.fd_surrogate)
		ex->io_mbs.__mb_word = __MBSTATE_TYPE_UTF16_LO | (format.fd_surrogate - 0xdc00);
	return result;
}
/*[[[end:libd_file_wprinter_unlocked]]]*/

/*[[[head:libd_wcsnrtombs,hash:CRC-32=0x2b436ea4]]]*/
/* >> wcsnrtombs(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) size_t
NOTHROW_NCX(LIBDCALL libd_wcsnrtombs)(char *dst,
                                      char16_t const **__restrict psrc,
                                      size_t nwc,
                                      size_t len,
                                      mbstate_t *mbs)
/*[[[body:libd_wcsnrtombs]]]*/
/*AUTO*/{
	(void)dst;
	(void)psrc;
	(void)nwc;
	(void)len;
	(void)mbs;
	CRT_UNIMPLEMENTEDF("DOS$wcsnrtombs(%q, %p, %Ix, %Ix, %p)", dst, psrc, nwc, len, mbs); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd_wcsnrtombs]]]*/

/*[[[head:libc_wcsnrtombs,hash:CRC-32=0x63ea54c8]]]*/
/* >> wcsnrtombs(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((2)) size_t
NOTHROW_NCX(LIBKCALL libc_wcsnrtombs)(char *dst,
                                      char32_t const **__restrict psrc,
                                      size_t nwc,
                                      size_t len,
                                      mbstate_t *mbs)
/*[[[body:libc_wcsnrtombs]]]*/
/*AUTO*/{
	(void)dst;
	(void)psrc;
	(void)nwc;
	(void)len;
	(void)mbs;
	CRT_UNIMPLEMENTEDF("wcsnrtombs(%q, %p, %Ix, %Ix, %p)", dst, psrc, nwc, len, mbs); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_wcsnrtombs]]]*/

/*[[[head:libc_mbsnrtowcs,hash:CRC-32=0x244f802]]]*/
/* >> mbsnrtowcs(3) */
INTERN ATTR_SECTION(".text.crt.wchar.unicode.static.mbs") NONNULL((2)) size_t
NOTHROW_NCX(LIBKCALL libc_mbsnrtowcs)(char32_t *dst,
                                      char const **__restrict psrc,
                                      size_t nmc,
                                      size_t len,
                                      mbstate_t *mbs)
/*[[[body:libc_mbsnrtowcs]]]*/
/*AUTO*/{
	(void)dst;
	(void)psrc;
	(void)nmc;
	(void)len;
	(void)mbs;
	CRT_UNIMPLEMENTEDF("mbsnrtowcs(%p, %p, %Ix, %Ix, %p)", dst, psrc, nmc, len, mbs); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_mbsnrtowcs]]]*/

/*[[[head:libd_mbsnrtowcs,hash:CRC-32=0xa4daea5b]]]*/
/* >> mbsnrtowcs(3) */
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") NONNULL((2)) size_t
NOTHROW_NCX(LIBDCALL libd_mbsnrtowcs)(char16_t *dst,
                                      char const **__restrict psrc,
                                      size_t nmc,
                                      size_t len,
                                      mbstate_t *mbs)
/*[[[body:libd_mbsnrtowcs]]]*/
/*AUTO*/{
	(void)dst;
	(void)psrc;
	(void)nmc;
	(void)len;
	(void)mbs;
	CRT_UNIMPLEMENTEDF("DOS$mbsnrtowcs(%p, %p, %Ix, %Ix, %p)", dst, psrc, nmc, len, mbs); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd_mbsnrtowcs]]]*/


/*[[[head:libc__wcserror_s,hash:CRC-32=0xa0cf5e1f]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") errno_t
NOTHROW_NCX(LIBKCALL libc__wcserror_s)(char32_t *buf,
                                       size_t bufsize,
                                       int errno_value)
/*[[[body:libc__wcserror_s]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)errno_value;
	CRT_UNIMPLEMENTEDF("_wcserror_s(%p, %Ix, %x)", buf, bufsize, errno_value); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__wcserror_s]]]*/

/*[[[head:libd__wcserror_s,hash:CRC-32=0x53717418]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") errno_t
NOTHROW_NCX(LIBDCALL libd__wcserror_s)(char16_t *buf,
                                       size_t bufsize,
                                       int errno_value)
/*[[[body:libd__wcserror_s]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)errno_value;
	CRT_UNIMPLEMENTEDF("DOS$_wcserror_s(%p, %Ix, %x)", buf, bufsize, errno_value); /* TODO */
	return ENOSYS;
}
/*[[[end:libd__wcserror_s]]]*/

/*[[[head:libc__wcserror,hash:CRC-32=0x77616da6]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") char32_t *
NOTHROW_NCX(LIBKCALL libc__wcserror)(int errno_value)
/*[[[body:libc__wcserror]]]*/
/*AUTO*/{
	(void)errno_value;
	CRT_UNIMPLEMENTEDF("_wcserror(%x)", errno_value); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wcserror]]]*/

/*[[[head:libd__wcserror,hash:CRC-32=0x8f600bcb]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") char16_t *
NOTHROW_NCX(LIBDCALL libd__wcserror)(int errno_value)
/*[[[body:libd__wcserror]]]*/
/*AUTO*/{
	(void)errno_value;
	CRT_UNIMPLEMENTEDF("DOS$_wcserror(%x)", errno_value); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__wcserror]]]*/

/*[[[head:libc___wcserror,hash:CRC-32=0xda75d073]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") char32_t *
NOTHROW_NCX(LIBKCALL libc___wcserror)(char32_t const *message)
/*[[[body:libc___wcserror]]]*/
/*AUTO*/{
	(void)message;
	CRT_UNIMPLEMENTEDF("__wcserror(%p)", message); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___wcserror]]]*/

/*[[[head:libd___wcserror,hash:CRC-32=0x94426558]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") char16_t *
NOTHROW_NCX(LIBDCALL libd___wcserror)(char16_t const *message)
/*[[[body:libd___wcserror]]]*/
/*AUTO*/{
	(void)message;
	CRT_UNIMPLEMENTEDF("DOS$__wcserror(%p)", message); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd___wcserror]]]*/

/*[[[head:libc___wcserror_s,hash:CRC-32=0x896e8dd0]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") errno_t
NOTHROW_NCX(LIBKCALL libc___wcserror_s)(char32_t *buf,
                                        size_t bufsize,
                                        char32_t const *message)
/*[[[body:libc___wcserror_s]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)message;
	CRT_UNIMPLEMENTEDF("__wcserror_s(%p, %Ix, %p)", buf, bufsize, message); /* TODO */
	return ENOSYS;
}
/*[[[end:libc___wcserror_s]]]*/

/*[[[head:libd___wcserror_s,hash:CRC-32=0x1c1899a8]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") errno_t
NOTHROW_NCX(LIBDCALL libd___wcserror_s)(char16_t *buf,
                                        size_t bufsize,
                                        char16_t const *message)
/*[[[body:libd___wcserror_s]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)message;
	CRT_UNIMPLEMENTEDF("DOS$__wcserror_s(%p, %Ix, %p)", buf, bufsize, message); /* TODO */
	return ENOSYS;
}
/*[[[end:libd___wcserror_s]]]*/







/*[[[head:libc__wfsopen,hash:CRC-32=0xc201095f]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBKCALL libc__wfsopen)(char32_t const *filename,
                                    char32_t const *mode,
                                    __STDC_INT_AS_UINT_T sh_flag)
/*[[[body:libc__wfsopen]]]*/
/*AUTO*/{
	(void)filename;
	(void)mode;
	(void)sh_flag;
	CRT_UNIMPLEMENTEDF("_wfsopen(%p, %p, %x)", filename, mode, sh_flag); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wfsopen]]]*/

/*[[[head:libd__wfsopen,hash:CRC-32=0xd879952b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((1, 2)) FILE *
NOTHROW_NCX(LIBDCALL libd__wfsopen)(char16_t const *filename,
                                    char16_t const *mode,
                                    __STDC_INT_AS_UINT_T sh_flag)
/*[[[body:libd__wfsopen]]]*/
/*AUTO*/{
	(void)filename;
	(void)mode;
	(void)sh_flag;
	CRT_UNIMPLEMENTEDF("DOS$_wfsopen(%p, %p, %x)", filename, mode, sh_flag); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__wfsopen]]]*/

/*[[[head:libc__wfdopen,hash:CRC-32=0x4ccfddcb]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((2)) FILE *
NOTHROW_NCX(LIBKCALL libc__wfdopen)(fd_t fd,
                                    char32_t const *mode)
/*[[[body:libc__wfdopen]]]*/
/*AUTO*/{
	(void)fd;
	(void)mode;
	CRT_UNIMPLEMENTEDF("_wfdopen(%" PRIxN(__SIZEOF_FD_T__) ", %p)", fd, mode); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wfdopen]]]*/

/*[[[head:libd__wfdopen,hash:CRC-32=0xbd1e6774]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") WUNUSED NONNULL((2)) FILE *
NOTHROW_NCX(LIBDCALL libd__wfdopen)(fd_t fd,
                                    char16_t const *mode)
/*[[[body:libd__wfdopen]]]*/
/*AUTO*/{
	(void)fd;
	(void)mode;
	CRT_UNIMPLEMENTEDF("DOS$_wfdopen(%" PRIxN(__SIZEOF_FD_T__) ", %p)", fd, mode); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__wfdopen]]]*/





/*[[[head:libc__wfopen_s,hash:CRC-32=0xfd293a6d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBKCALL libc__wfopen_s)(FILE **pstream,
                                     char32_t const *filename,
                                     char32_t const *mode)
/*[[[body:libc__wfopen_s]]]*/
/*AUTO*/{
	(void)pstream;
	(void)filename;
	(void)mode;
	CRT_UNIMPLEMENTEDF("_wfopen_s(%p, %p, %p)", pstream, filename, mode); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__wfopen_s]]]*/

/*[[[head:libd__wfopen_s,hash:CRC-32=0xe928135b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBDCALL libd__wfopen_s)(FILE **pstream,
                                     char16_t const *filename,
                                     char16_t const *mode)
/*[[[body:libd__wfopen_s]]]*/
/*AUTO*/{
	(void)pstream;
	(void)filename;
	(void)mode;
	CRT_UNIMPLEMENTEDF("DOS$_wfopen_s(%p, %p, %p)", pstream, filename, mode); /* TODO */
	return ENOSYS;
}
/*[[[end:libd__wfopen_s]]]*/

/*[[[head:libc__wfreopen_s,hash:CRC-32=0x8d8f311b]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBKCALL libc__wfreopen_s)(FILE **pstream,
                                       char32_t const *filename,
                                       char32_t const *mode,
                                       FILE *stream)
/*[[[body:libc__wfreopen_s]]]*/
/*AUTO*/{
	(void)pstream;
	(void)filename;
	(void)mode;
	(void)stream;
	CRT_UNIMPLEMENTEDF("_wfreopen_s(%p, %p, %p, %p)", pstream, filename, mode, stream); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__wfreopen_s]]]*/

/*[[[head:libd__wfreopen_s,hash:CRC-32=0xbde1c414]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access") NONNULL((1, 2, 3)) errno_t
NOTHROW_NCX(LIBDCALL libd__wfreopen_s)(FILE **pstream,
                                       char16_t const *filename,
                                       char16_t const *mode,
                                       FILE *stream)
/*[[[body:libd__wfreopen_s]]]*/
/*AUTO*/{
	(void)pstream;
	(void)filename;
	(void)mode;
	(void)stream;
	CRT_UNIMPLEMENTEDF("DOS$_wfreopen_s(%p, %p, %p, %p)", pstream, filename, mode, stream); /* TODO */
	return ENOSYS;
}
/*[[[end:libd__wfreopen_s]]]*/

/*[[[head:libc__wtempnam,hash:CRC-32=0xdf74d60d]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") WUNUSED char32_t *
NOTHROW_NCX(LIBKCALL libc__wtempnam)(char32_t const *directory,
                                     char32_t const *file_prefix)
/*[[[body:libc__wtempnam]]]*/
/*AUTO*/{
	(void)directory;
	(void)file_prefix;
	CRT_UNIMPLEMENTEDF("_wtempnam(%p, %p)", directory, file_prefix); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wtempnam]]]*/

/*[[[head:libd__wtempnam,hash:CRC-32=0xc2e4bfc6]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") WUNUSED char16_t *
NOTHROW_NCX(LIBDCALL libd__wtempnam)(char16_t const *directory,
                                     char16_t const *file_prefix)
/*[[[body:libd__wtempnam]]]*/
/*AUTO*/{
	(void)directory;
	(void)file_prefix;
	CRT_UNIMPLEMENTEDF("DOS$_wtempnam(%p, %p)", directory, file_prefix); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__wtempnam]]]*/





/*[[[head:libc__wtmpnam_s,hash:CRC-32=0xf4219000]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBKCALL libc__wtmpnam_s)(char32_t *dst,
                                      size_t wchar_count)
/*[[[body:libc__wtmpnam_s]]]*/
/*AUTO*/{
	(void)dst;
	(void)wchar_count;
	CRT_UNIMPLEMENTEDF("_wtmpnam_s(%p, %Ix)", dst, wchar_count); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__wtmpnam_s]]]*/

/*[[[head:libd__wtmpnam_s,hash:CRC-32=0x3cf6b66]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") NONNULL((1)) errno_t
NOTHROW_NCX(LIBDCALL libd__wtmpnam_s)(char16_t *dst,
                                      size_t wchar_count)
/*[[[body:libd__wtmpnam_s]]]*/
/*AUTO*/{
	(void)dst;
	(void)wchar_count;
	CRT_UNIMPLEMENTEDF("DOS$_wtmpnam_s(%p, %Ix)", dst, wchar_count); /* TODO */
	return ENOSYS;
}
/*[[[end:libd__wtmpnam_s]]]*/





/*[[[start:exports,hash:CRC-32=0xbdbcfd2f]]]*/
DEFINE_PUBLIC_ALIAS(DOS$getwc, libd_fgetwc);
DEFINE_PUBLIC_ALIAS(DOS$fgetwc, libd_fgetwc);
DEFINE_PUBLIC_ALIAS(getwc, libc_fgetwc);
DEFINE_PUBLIC_ALIAS(fgetwc, libc_fgetwc);
DEFINE_PUBLIC_ALIAS(DOS$putwc, libd_fputwc);
DEFINE_PUBLIC_ALIAS(DOS$fputwc, libd_fputwc);
DEFINE_PUBLIC_ALIAS(putwc, libc_fputwc);
DEFINE_PUBLIC_ALIAS(fputwc, libc_fputwc);
DEFINE_PUBLIC_ALIAS(DOS$ungetwc, libd_ungetwc);
DEFINE_PUBLIC_ALIAS(ungetwc, libc_ungetwc);
DEFINE_PUBLIC_ALIAS(DOS$vfwscanf, libd_vfwscanf);
DEFINE_PUBLIC_ALIAS(vfwscanf, libc_vfwscanf);
DEFINE_PUBLIC_ALIAS(DOS$mbsnrtowcs, libd_mbsnrtowcs);
DEFINE_PUBLIC_ALIAS(mbsnrtowcs, libc_mbsnrtowcs);
DEFINE_PUBLIC_ALIAS(DOS$wcsnrtombs, libd_wcsnrtombs);
DEFINE_PUBLIC_ALIAS(wcsnrtombs, libc_wcsnrtombs);
DEFINE_PUBLIC_ALIAS(DOS$open_wmemstream, libd_open_wmemstream);
DEFINE_PUBLIC_ALIAS(open_wmemstream, libc_open_wmemstream);
DEFINE_PUBLIC_ALIAS(DOS$_fgetwc_nolock, libd_fgetwc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fgetwc_unlocked, libd_fgetwc_unlocked);
DEFINE_PUBLIC_ALIAS(fgetwc_unlocked, libc_fgetwc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_fputwc_nolock, libd_fputwc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fputwc_unlocked, libd_fputwc_unlocked);
DEFINE_PUBLIC_ALIAS(fputwc_unlocked, libc_fputwc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$file_wprinter, libd_file_wprinter);
DEFINE_PUBLIC_ALIAS(file_wprinter, libc_file_wprinter);
DEFINE_PUBLIC_ALIAS(DOS$file_wprinter_unlocked, libd_file_wprinter_unlocked);
DEFINE_PUBLIC_ALIAS(file_wprinter_unlocked, libc_file_wprinter_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$_ungetwc_nolock, libd_ungetwc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$ungetwc_unlocked, libd_ungetwc_unlocked);
DEFINE_PUBLIC_ALIAS(ungetwc_unlocked, libc_ungetwc_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$vfwscanf_unlocked, libd_vfwscanf_unlocked);
DEFINE_PUBLIC_ALIAS(vfwscanf_unlocked, libc_vfwscanf_unlocked);
DEFINE_PUBLIC_ALIAS(DOS$fgetwln, libd_fgetwln);
DEFINE_PUBLIC_ALIAS(fgetwln, libc_fgetwln);
DEFINE_PUBLIC_ALIAS(DOS$_wcserror, libd__wcserror);
DEFINE_PUBLIC_ALIAS(_wcserror, libc__wcserror);
DEFINE_PUBLIC_ALIAS(DOS$_wcserror_s, libd__wcserror_s);
DEFINE_PUBLIC_ALIAS(_wcserror_s, libc__wcserror_s);
DEFINE_PUBLIC_ALIAS(DOS$__wcserror, libd___wcserror);
DEFINE_PUBLIC_ALIAS(__wcserror, libc___wcserror);
DEFINE_PUBLIC_ALIAS(DOS$__wcserror_s, libd___wcserror_s);
DEFINE_PUBLIC_ALIAS(__wcserror_s, libc___wcserror_s);
DEFINE_PUBLIC_ALIAS(DOS$_wfsopen, libd__wfsopen);
DEFINE_PUBLIC_ALIAS(_wfsopen, libc__wfsopen);
DEFINE_PUBLIC_ALIAS(DOS$_wfdopen, libd__wfdopen);
DEFINE_PUBLIC_ALIAS(_wfdopen, libc__wfdopen);
DEFINE_PUBLIC_ALIAS(DOS$_wfopen_s, libd__wfopen_s);
DEFINE_PUBLIC_ALIAS(_wfopen_s, libc__wfopen_s);
DEFINE_PUBLIC_ALIAS(DOS$_wfreopen_s, libd__wfreopen_s);
DEFINE_PUBLIC_ALIAS(_wfreopen_s, libc__wfreopen_s);
DEFINE_PUBLIC_ALIAS(DOS$_wtempnam, libd__wtempnam);
DEFINE_PUBLIC_ALIAS(_wtempnam, libc__wtempnam);
DEFINE_PUBLIC_ALIAS(DOS$_wtmpnam_s, libd__wtmpnam_s);
DEFINE_PUBLIC_ALIAS(_wtmpnam_s, libc__wtmpnam_s);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_WCHAR_C */
