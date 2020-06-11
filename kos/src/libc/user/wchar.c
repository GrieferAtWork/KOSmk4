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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_WCHAR_C
#define GUARD_LIBC_USER_WCHAR_C 1

#include "../api.h"
/**/

#include <libc/unicode.h>
#include <stdio.h>
#include <string.h>
#include <uchar.h>

#include "../auto/parts.wchar.format-printer.h"
#include "../libc/uchar.h"
#include "malloc.h"
#include "stdio-api.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "wchar.h"

#define libc_vswprintf_s libc_vswprintf
#define libd_vswprintf_s libd_vswprintf
#define libc_swprintf_s  libc_swprintf
#define libd_swprintf_s  libd_swprintf
#define libc_vfwprintf_s libc_vfwprintf
#define libd_vfwprintf_s libd_vfwprintf
#define libc_fwprintf_s  libc_fwprintf
#define libd_fwprintf_s  libd_fwprintf
#define libc_vwprintf_s  libc_vwprintf
#define libd_vwprintf_s  libd_vwprintf
#define libc_wprintf_s   libc_wprintf
#define libd_wprintf_s   libd_wprintf
#define libc_vswscanf_s  libc_vswscanf
#define libd_vswscanf_s  libd_vswscanf
#define libc_swscanf_s   libc_swscanf
#define libd_swscanf_s   libd_swscanf
#define libc_vfwscanf_s  libc_vfwscanf
#define libd_vfwscanf_s  libd_vfwscanf
#define libc_fwscanf_s   libc_fwscanf
#define libd_fwscanf_s   libd_fwscanf
#define libc_vwscanf_s   libc_vwscanf
#define libd_vwscanf_s   libd_vwscanf
#define libc_wscanf_s    libc_wscanf
#define libd_wscanf_s    libd_wscanf

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




/*[[[head:fgetwc_unlocked,hash:CRC-32=0xbfedb30]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.getc.fgetwc_unlocked") wint_t
(LIBCCALL libc_fgetwc_unlocked)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fgetwc_unlocked]]]*/
{
	wint_t result;
	result = (wint_t)file_getc32(stream);
	return result;
}
/*[[[end:fgetwc_unlocked]]]*/

/*[[[head:DOS$fgetwc_unlocked,hash:CRC-32=0x91bc7bac]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.getc.fgetwc_unlocked") wint_t
(LIBDCALL libd__fgetwc_nolock)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:DOS$fgetwc_unlocked]]]*/
{
	wint_t result;
	result = (wint_t)file_getc16(stream);
	return result;
}
/*[[[end:DOS$fgetwc_unlocked]]]*/

/*[[[head:fgetwc,hash:CRC-32=0xecd79f4c]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.read.getc.fgetwc") wint_t
(LIBCCALL libc_fgetwc)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fgetwc]]]*/
{
	wint_t result;
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		result = (wint_t)file_getc32(stream);
		file_endwrite(stream);
	} else {
		result = (wint_t)file_getc32(stream);
	}
	return result;
}
/*[[[end:fgetwc]]]*/

/*[[[head:DOS$fgetwc,hash:CRC-32=0x7f66f18f]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.getc.fgetwc") wint_t
(LIBDCALL libd_fgetwc)(FILE *__restrict stream)
		__THROWS(...)
/*[[[body:DOS$fgetwc]]]*/
{
	wint_t result;
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		result = (wint_t)file_getc16(stream);
		file_endwrite(stream);
	} else {
		result = (wint_t)file_getc16(stream);
	}
	return result;
}
/*[[[end:DOS$fgetwc]]]*/

/*[[[head:ungetwc_unlocked,hash:CRC-32=0x5ea5541]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.putc.ungetwc_unlocked") wint_t
NOTHROW_NCX(LIBCCALL libc_ungetwc_unlocked)(wint_t ch,
                                            FILE *__restrict stream)
/*[[[body:ungetwc_unlocked]]]*/
{
	wint_t result;
	result = (wint_t)file_ungetc32(stream, (char32_t)ch);
	return result;
}
/*[[[end:ungetwc_unlocked]]]*/

/*[[[head:DOS$ungetwc_unlocked,hash:CRC-32=0x5ce77b73]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.putc.ungetwc_unlocked") wint_t
NOTHROW_NCX(LIBDCALL libd__ungetwc_nolock)(wint_t ch,
                                            FILE *__restrict stream)
/*[[[body:DOS$ungetwc_unlocked]]]*/
{
	wint_t result;
	result = (wint_t)file_ungetc16(stream, (char16_t)ch);
	return result;
}
/*[[[end:DOS$ungetwc_unlocked]]]*/

/*[[[head:ungetwc,hash:CRC-32=0x4d6f31c9]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.putc.ungetwc") wint_t
NOTHROW_NCX(LIBCCALL libc_ungetwc)(wint_t wc,
                                   FILE *stream)
/*[[[body:ungetwc]]]*/
{
	wint_t result;
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		result = (wint_t)file_ungetc32(stream, (char32_t)wc);
		file_endwrite(stream);
	} else {
		result = (wint_t)file_ungetc32(stream, (char32_t)wc);
	}
	return result;
}
/*[[[end:ungetwc]]]*/

/*[[[head:DOS$ungetwc,hash:CRC-32=0xe419f2a5]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.putc.ungetwc") wint_t
NOTHROW_NCX(LIBDCALL libd_ungetwc)(wint_t wc,
                                   FILE *stream)
/*[[[body:DOS$ungetwc]]]*/
{
	wint_t result;
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		result = (wint_t)file_ungetc16(stream, (char16_t)wc);
		file_endwrite(stream);
	} else {
		result = (wint_t)file_ungetc16(stream, (char16_t)wc);
	}
	return result;
}
/*[[[end:DOS$ungetwc]]]*/

/*[[[head:fputwc_unlocked,hash:CRC-32=0x48be2a0a]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.putc.fputwc_unlocked") wint_t
(LIBCCALL libc_fputwc_unlocked)(char32_t wc,
                                FILE *__restrict stream)
		__THROWS(...)
/*[[[body:fputwc_unlocked]]]*/
{
	wint_t result = (wint_t)wc;
	if (file_print32(stream, &wc, 1) <= 0)
		result = (wint_t)EOF32;
	return result;
}
/*[[[end:fputwc_unlocked]]]*/

/*[[[head:DOS$fputwc_unlocked,hash:CRC-32=0x9275a7b5]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.write.putc.fputwc_unlocked") wint_t
(LIBDCALL libd__fputwc_nolock)(char16_t wc,
                                FILE *__restrict stream)
		__THROWS(...)
/*[[[body:DOS$fputwc_unlocked]]]*/
{
	wint_t result = (wint_t)wc;
	if (file_print16(stream, &wc, 1) <= 0)
		result = (wint_t)EOF16;
	return result;
}
/*[[[end:DOS$fputwc_unlocked]]]*/

/*[[[head:fputwc,hash:CRC-32=0x14c559f]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.putc.fputwc") wint_t
(LIBCCALL libc_fputwc)(char32_t wc,
                       FILE *stream)
		__THROWS(...)
/*[[[body:fputwc]]]*/
{
	ssize_t error;
	wint_t result = (wint_t)wc;
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		error = file_print32(stream, &wc, 1);
		file_endwrite(stream);
	} else {
		error = file_print32(stream, &wc, 1);
	}
	if (error <= 0)
		result = (wint_t)EOF32;
	return result;
}
/*[[[end:fputwc]]]*/

/*[[[head:DOS$fputwc,hash:CRC-32=0xd391cddc]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.write.putc.fputwc") wint_t
(LIBDCALL libd_fputwc)(char16_t wc,
                       FILE *stream)
		__THROWS(...)
/*[[[body:DOS$fputwc]]]*/
{
	ssize_t error;
	wint_t result = (wint_t)wc;
	if (FMUSTLOCK(stream)) {
		file_write(stream);
		error = file_print16(stream, &wc, 1);
		file_endwrite(stream);
	} else {
		error = file_print16(stream, &wc, 1);
	}
	if (error <= 0)
		result = (wint_t)EOF16;
	return result;
}
/*[[[end:DOS$fputwc]]]*/

/*[[[head:open_wmemstream,hash:CRC-32=0xd2c58cbd]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.access.open_wmemstream") FILE *
NOTHROW_NCX(LIBCCALL libc_open_wmemstream)(char32_t **bufloc,
                                           size_t *sizeloc)
/*[[[body:open_wmemstream]]]*/
{
	(void)bufloc;
	(void)sizeloc;
	CRT_UNIMPLEMENTED("open_wmemstream"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:open_wmemstream]]]*/

/*[[[head:DOS$open_wmemstream,hash:CRC-32=0x5bc1356d]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access.open_wmemstream") FILE *
NOTHROW_NCX(LIBDCALL libd_open_wmemstream)(char16_t **bufloc,
                                           size_t *sizeloc)
/*[[[body:DOS$open_wmemstream]]]*/
{
	(void)bufloc;
	(void)sizeloc;
	CRT_UNIMPLEMENTED("open_wmemstream"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$open_wmemstream]]]*/











/*[[[head:vfwscanf_unlocked,hash:CRC-32=0x63cf5033]]]*/
INTERN WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.read.scanf.vfwscanf_unlocked") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vfwscanf_unlocked)(FILE *__restrict stream,
                                  char32_t const *__restrict format,
                                  va_list args)
		__THROWS(...)
/*[[[body:vfwscanf_unlocked]]]*/
{
	(void)stream;
	(void)format;
	(void)args;
	CRT_UNIMPLEMENTED("vfwscanf_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:vfwscanf_unlocked]]]*/

/*[[[head:DOS$vfwscanf_unlocked,hash:CRC-32=0xdbb616]]]*/
INTERN WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.unlocked.read.scanf.vfwscanf_unlocked") __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vfwscanf_unlocked)(FILE *__restrict stream,
                                  char16_t const *__restrict format,
                                  va_list args)
		__THROWS(...)
/*[[[body:DOS$vfwscanf_unlocked]]]*/
{
	(void)stream;
	(void)format;
	(void)args;
	CRT_UNIMPLEMENTED("vfwscanf_unlocked"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$vfwscanf_unlocked]]]*/

/*[[[head:vfwscanf,hash:CRC-32=0x2b229646]]]*/
INTERN WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.read.scanf.vfwscanf") __STDC_INT_AS_SIZE_T
(LIBCCALL libc_vfwscanf)(FILE *__restrict stream,
                         char32_t const *__restrict format,
                         va_list args)
		__THROWS(...)
/*[[[body:vfwscanf]]]*/
{
	(void)stream;
	(void)format;
	(void)args;
	CRT_UNIMPLEMENTED("vfwscanf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:vfwscanf]]]*/

/*[[[head:DOS$vfwscanf,hash:CRC-32=0x67f307fd]]]*/
INTERN WUNUSED ATTR_LIBC_WSCANF(2, 0) NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.read.scanf.vfwscanf") __STDC_INT_AS_SIZE_T
(LIBDCALL libd_vfwscanf)(FILE *__restrict stream,
                         char16_t const *__restrict format,
                         va_list args)
		__THROWS(...)
/*[[[body:DOS$vfwscanf]]]*/
{
	(void)stream;
	(void)format;
	(void)args;
	CRT_UNIMPLEMENTED("vfwscanf"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$vfwscanf]]]*/


/*[[[head:file_wprinter,hash:CRC-32=0x9487ed4]]]*/
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.write.file_wprinter") ssize_t
(LIBCCALL libc_file_wprinter)(void *arg,
                              char32_t const *__restrict data,
                              size_t datalen)
		__THROWS(...)
/*[[[body:file_wprinter]]]*/
{
	ssize_t result;
	FILE *me = (FILE *)arg;
	if (FMUSTLOCK(me)) {
		file_write(me);
		result = file_print32(arg, data, datalen);
		file_endwrite(me);
	} else {
		result = file_print32(arg, data, datalen);
	}
	return result;
}
/*[[[end:file_wprinter]]]*/

/*[[[head:file_wprinter_unlocked,hash:CRC-32=0x73f2178]]]*/
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.write.file_wprinter_unlocked") ssize_t
(LIBCCALL libc_file_wprinter_unlocked)(void *arg,
                                       char32_t const *__restrict data,
                                       size_t datalen)
		__THROWS(...)
/*[[[body:file_wprinter_unlocked]]]*/
{
	ssize_t result;
	result = file_print32(arg, data, datalen);
	return result;
}
/*[[[end:file_wprinter_unlocked]]]*/

/*[[[head:DOS$file_wprinter,hash:CRC-32=0xcddb8dd4]]]*/
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.locked.write.write.file_wprinter") ssize_t
(LIBDCALL libd_file_wprinter)(void *arg,
                              char16_t const *__restrict data,
                              size_t datalen)
		__THROWS(...)
/*[[[body:DOS$file_wprinter]]]*/
{
	ssize_t result;
	FILE *me = (FILE *)arg;
	if (FMUSTLOCK(me)) {
		file_write(me);
		result = file_print16(arg, data, datalen);
		file_endwrite(me);
	} else {
		result = file_print16(arg, data, datalen);
	}
	return result;
}
/*[[[end:DOS$file_wprinter]]]*/

/*[[[head:DOS$file_wprinter_unlocked,hash:CRC-32=0x452e9602]]]*/
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.FILE.unlocked.write.write.file_wprinter_unlocked") ssize_t
(LIBDCALL libd_file_wprinter_unlocked)(void *arg,
                                       char16_t const *__restrict data,
                                       size_t datalen)
		__THROWS(...)
/*[[[body:DOS$file_wprinter_unlocked]]]*/
{
	ssize_t result;
	result = file_print16(arg, data, datalen);
	return result;
}
/*[[[end:DOS$file_wprinter_unlocked]]]*/

/*[[[head:DOS$wcsnrtombs,hash:CRC-32=0x1112edb4]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.wcsnrtombs") size_t
NOTHROW_NCX(LIBDCALL libd_wcsnrtombs)(char *dst,
                                      char16_t const **__restrict psrc,
                                      size_t nwc,
                                      size_t len,
                                      mbstate_t *mbs)
/*[[[body:DOS$wcsnrtombs]]]*/
{
	(void)dst;
	(void)psrc;
	(void)nwc;
	(void)len;
	(void)mbs;
	CRT_UNIMPLEMENTED("wcsnrtombs"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$wcsnrtombs]]]*/

/*[[[head:wcsnrtombs,hash:CRC-32=0x4de97b68]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.wcsnrtombs") size_t
NOTHROW_NCX(LIBCCALL libc_wcsnrtombs)(char *dst,
                                      char32_t const **__restrict psrc,
                                      size_t nwc,
                                      size_t len,
                                      mbstate_t *mbs)
/*[[[body:wcsnrtombs]]]*/
{
	(void)dst;
	(void)psrc;
	(void)nwc;
	(void)len;
	(void)mbs;
	CRT_UNIMPLEMENTED("wcsnrtombs"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:wcsnrtombs]]]*/

/*[[[head:mbsnrtowcs,hash:CRC-32=0x5752092c]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.wchar.unicode.static.mbs.mbsnrtowcs") size_t
NOTHROW_NCX(LIBCCALL libc_mbsnrtowcs)(char32_t *dst,
                                      char const **__restrict psrc,
                                      size_t nmc,
                                      size_t len,
                                      mbstate_t *mbs)
/*[[[body:mbsnrtowcs]]]*/
{
	(void)dst;
	(void)psrc;
	(void)nmc;
	(void)len;
	(void)mbs;
	CRT_UNIMPLEMENTED("mbsnrtowcs"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:mbsnrtowcs]]]*/

/*[[[head:DOS$mbsnrtowcs,hash:CRC-32=0x14ed023e]]]*/
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs.mbsnrtowcs") size_t
NOTHROW_NCX(LIBDCALL libd_mbsnrtowcs)(char16_t *dst,
                                      char const **__restrict psrc,
                                      size_t nmc,
                                      size_t len,
                                      mbstate_t *mbs)
/*[[[body:DOS$mbsnrtowcs]]]*/
{
	(void)dst;
	(void)psrc;
	(void)nmc;
	(void)len;
	(void)mbs;
	CRT_UNIMPLEMENTED("mbsnrtowcs"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$mbsnrtowcs]]]*/


/*[[[head:_wcserror_s,hash:CRC-32=0x8e85f7f1]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno._wcserror_s") errno_t
NOTHROW_NCX(LIBCCALL libc__wcserror_s)(char32_t *buf,
                                       size_t bufsize,
                                       int errno_value)
/*[[[body:_wcserror_s]]]*/
{
	(void)buf;
	(void)bufsize;
	(void)errno_value;
	CRT_UNIMPLEMENTED("_wcserror_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_wcserror_s]]]*/

/*[[[head:DOS$_wcserror_s,hash:CRC-32=0xc9bf913]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno._wcserror_s") errno_t
NOTHROW_NCX(LIBDCALL libd__wcserror_s)(char16_t *buf,
                                       size_t bufsize,
                                       int errno_value)
/*[[[body:DOS$_wcserror_s]]]*/
{
	(void)buf;
	(void)bufsize;
	(void)errno_value;
	CRT_UNIMPLEMENTED("_wcserror_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$_wcserror_s]]]*/

/*[[[head:_wcserror,hash:CRC-32=0x8497a7b7]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno._wcserror") char32_t *
NOTHROW_NCX(LIBCCALL libc__wcserror)(int errno_value)
/*[[[body:_wcserror]]]*/
{
	(void)errno_value;
	CRT_UNIMPLEMENTED("_wcserror"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:_wcserror]]]*/

/*[[[head:DOS$_wcserror,hash:CRC-32=0x503e59fc]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno._wcserror") char16_t *
NOTHROW_NCX(LIBDCALL libd__wcserror)(int errno_value)
/*[[[body:DOS$_wcserror]]]*/
{
	(void)errno_value;
	CRT_UNIMPLEMENTED("_wcserror"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$_wcserror]]]*/

/*[[[head:__wcserror,hash:CRC-32=0xa5fe8163]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno.__wcserror") char32_t *
NOTHROW_NCX(LIBCCALL libc___wcserror)(char32_t const *message)
/*[[[body:__wcserror]]]*/
{
	(void)message;
	CRT_UNIMPLEMENTED("__wcserror"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:__wcserror]]]*/

/*[[[head:DOS$__wcserror,hash:CRC-32=0x6be2a92b]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno.__wcserror") char16_t *
NOTHROW_NCX(LIBDCALL libd___wcserror)(char16_t const *message)
/*[[[body:DOS$__wcserror]]]*/
{
	(void)message;
	CRT_UNIMPLEMENTED("__wcserror"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$__wcserror]]]*/

/*[[[head:__wcserror_s,hash:CRC-32=0xdd67c7b2]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno.__wcserror_s") errno_t
NOTHROW_NCX(LIBCCALL libc___wcserror_s)(char32_t *buf,
                                        size_t bufsize,
                                        char32_t const *message)
/*[[[body:__wcserror_s]]]*/
{
	(void)buf;
	(void)bufsize;
	(void)message;
	CRT_UNIMPLEMENTED("__wcserror_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:__wcserror_s]]]*/

/*[[[head:DOS$__wcserror_s,hash:CRC-32=0x635cfb7e]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.errno.__wcserror_s") errno_t
NOTHROW_NCX(LIBDCALL libd___wcserror_s)(char16_t *buf,
                                        size_t bufsize,
                                        char16_t const *message)
/*[[[body:DOS$__wcserror_s]]]*/
{
	(void)buf;
	(void)bufsize;
	(void)message;
	CRT_UNIMPLEMENTED("__wcserror_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$__wcserror_s]]]*/







/*[[[head:_wfsopen,hash:CRC-32=0x73cac798]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access._wfsopen") FILE *
NOTHROW_NCX(LIBCCALL libc__wfsopen)(char32_t const *filename,
                                    char32_t const *mode,
                                    int sh_flag)
/*[[[body:_wfsopen]]]*/
{
	(void)filename;
	(void)mode;
	(void)sh_flag;
	CRT_UNIMPLEMENTED("_wfsopen"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:_wfsopen]]]*/

/*[[[head:DOS$_wfsopen,hash:CRC-32=0xddbb32f1]]]*/
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access._wfsopen") FILE *
NOTHROW_NCX(LIBDCALL libd__wfsopen)(char16_t const *filename,
                                    char16_t const *mode,
                                    int sh_flag)
/*[[[body:DOS$_wfsopen]]]*/
{
	(void)filename;
	(void)mode;
	(void)sh_flag;
	CRT_UNIMPLEMENTED("_wfsopen"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$_wfsopen]]]*/

/*[[[head:_wfdopen,hash:CRC-32=0xf6cb83a3]]]*/
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access._wfdopen") FILE *
NOTHROW_NCX(LIBCCALL libc__wfdopen)(fd_t fd,
                                    char32_t const *mode)
/*[[[body:_wfdopen]]]*/
{
	(void)fd;
	(void)mode;
	CRT_UNIMPLEMENTED("_wfdopen"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:_wfdopen]]]*/

/*[[[head:DOS$_wfdopen,hash:CRC-32=0x9c2d8e15]]]*/
INTERN WUNUSED NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access._wfdopen") FILE *
NOTHROW_NCX(LIBDCALL libd__wfdopen)(fd_t fd,
                                    char16_t const *mode)
/*[[[body:DOS$_wfdopen]]]*/
{
	(void)fd;
	(void)mode;
	CRT_UNIMPLEMENTED("_wfdopen"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$_wfdopen]]]*/





/*[[[head:_wfopen_s,hash:CRC-32=0xcc91613c]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access._wfopen_s") errno_t
NOTHROW_NCX(LIBCCALL libc__wfopen_s)(FILE **pstream,
                                     char32_t const *filename,
                                     char32_t const *mode)
/*[[[body:_wfopen_s]]]*/
{
	(void)pstream;
	(void)filename;
	(void)mode;
	CRT_UNIMPLEMENTED("_wfopen_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_wfopen_s]]]*/

/*[[[head:DOS$_wfopen_s,hash:CRC-32=0xae128a21]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access._wfopen_s") errno_t
NOTHROW_NCX(LIBDCALL libd__wfopen_s)(FILE **pstream,
                                     char16_t const *filename,
                                     char16_t const *mode)
/*[[[body:DOS$_wfopen_s]]]*/
{
	(void)pstream;
	(void)filename;
	(void)mode;
	CRT_UNIMPLEMENTED("_wfopen_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$_wfopen_s]]]*/

/*[[[head:_wfreopen_s,hash:CRC-32=0x6e87ad15]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access._wfreopen_s") errno_t
NOTHROW_NCX(LIBCCALL libc__wfreopen_s)(FILE **pstream,
                                       char32_t const *filename,
                                       char32_t const *mode,
                                       FILE *stream)
/*[[[body:_wfreopen_s]]]*/
{
	(void)pstream;
	(void)filename;
	(void)mode;
	(void)stream;
	CRT_UNIMPLEMENTED("_wfreopen_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_wfreopen_s]]]*/

/*[[[head:DOS$_wfreopen_s,hash:CRC-32=0xdb4f6874]]]*/
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.FILE.locked.access._wfreopen_s") errno_t
NOTHROW_NCX(LIBDCALL libd__wfreopen_s)(FILE **pstream,
                                       char16_t const *filename,
                                       char16_t const *mode,
                                       FILE *stream)
/*[[[body:DOS$_wfreopen_s]]]*/
{
	(void)pstream;
	(void)filename;
	(void)mode;
	(void)stream;
	CRT_UNIMPLEMENTED("_wfreopen_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$_wfreopen_s]]]*/

/*[[[head:_wtempnam,hash:CRC-32=0xddbca9c8]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.utility._wtempnam") char32_t *
NOTHROW_NCX(LIBCCALL libc__wtempnam)(char32_t const *directory,
                                     char32_t const *file_prefix)
/*[[[body:_wtempnam]]]*/
{
	(void)directory;
	(void)file_prefix;
	CRT_UNIMPLEMENTED("_wtempnam"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:_wtempnam]]]*/

/*[[[head:DOS$_wtempnam,hash:CRC-32=0xbc1e511a]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.utility._wtempnam") char16_t *
NOTHROW_NCX(LIBDCALL libd__wtempnam)(char16_t const *directory,
                                     char16_t const *file_prefix)
/*[[[body:DOS$_wtempnam]]]*/
{
	(void)directory;
	(void)file_prefix;
	CRT_UNIMPLEMENTED("_wtempnam"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:DOS$_wtempnam]]]*/





/*[[[head:_wtmpnam_s,hash:CRC-32=0x1268f60]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.utility._wtmpnam_s") errno_t
NOTHROW_NCX(LIBCCALL libc__wtmpnam_s)(char32_t *dst,
                                      size_t wchar_count)
/*[[[body:_wtmpnam_s]]]*/
{
	(void)dst;
	(void)wchar_count;
	CRT_UNIMPLEMENTED("_wtmpnam_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:_wtmpnam_s]]]*/

/*[[[head:DOS$_wtmpnam_s,hash:CRC-32=0x878b516]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.dos.wchar.fs.utility._wtmpnam_s") errno_t
NOTHROW_NCX(LIBDCALL libd__wtmpnam_s)(char16_t *dst,
                                      size_t wchar_count)
/*[[[body:DOS$_wtmpnam_s]]]*/
{
	(void)dst;
	(void)wchar_count;
	CRT_UNIMPLEMENTED("_wtmpnam_s"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:DOS$_wtmpnam_s]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xc2b3e6f7]]]*/
#undef fwprintf
#undef fwprintf_s
#undef wprintf
#undef wprintf_s
#undef fwscanf
#undef fwscanf_s
#undef wscanf
#undef wscanf_s
#undef fwprintf_unlocked
#undef wprintf_unlocked
#undef fwscanf_unlocked
#undef wscanf_unlocked
#undef _wprintf_p
#undef _wprintf_l
#undef _wprintf_p_l
#undef _wprintf_s_l
#undef _fwprintf_l
#undef _fwprintf_s_l
#undef _fwscanf_l
#undef _fwscanf_s_l
#undef _wscanf_l
#undef _wscanf_s_l
DEFINE_PUBLIC_WEAK_ALIAS(getwchar, libc_getwchar);
DEFINE_PUBLIC_WEAK_ALIAS(_fgetwchar, libc_getwchar);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$getwchar, libd_getwchar);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_fgetwchar, libd_getwchar);
DEFINE_PUBLIC_WEAK_ALIAS(fgetwc, libc_fgetwc);
DEFINE_PUBLIC_WEAK_ALIAS(getwc, libc_fgetwc);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fgetwc, libd_fgetwc);
DEFINE_PUBLIC_WEAK_ALIAS(putwchar, libc_putwchar);
DEFINE_PUBLIC_WEAK_ALIAS(_fputwchar, libc_putwchar);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$putwchar, libd_putwchar);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_fputwchar, libd_putwchar);
DEFINE_PUBLIC_WEAK_ALIAS(fputwc, libc_fputwc);
DEFINE_PUBLIC_WEAK_ALIAS(putwc, libc_fputwc);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fputwc, libd_fputwc);
DEFINE_PUBLIC_WEAK_ALIAS(fgetws, libc_fgetws);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fgetws, libd_fgetws);
DEFINE_PUBLIC_WEAK_ALIAS(fputws, libc_fputws);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fputws, libd_fputws);
DEFINE_PUBLIC_WEAK_ALIAS(ungetwc, libc_ungetwc);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$ungetwc, libd_ungetwc);
DEFINE_PUBLIC_WEAK_ALIAS(fwprintf, libc_fwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(fwprintf_s, libc_fwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fwprintf, libd_fwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vfwprintf, libc_vfwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vfwprintf_s, libc_vfwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vfwprintf, libd_vfwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(wprintf, libc_wprintf);
DEFINE_PUBLIC_WEAK_ALIAS(wprintf_s, libc_wprintf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wprintf, libd_wprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vwprintf, libc_vwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(vwprintf_s, libc_vwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vwprintf, libd_vwprintf);
DEFINE_PUBLIC_WEAK_ALIAS(fwscanf, libc_fwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(fwscanf_s, libc_fwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fwscanf, libd_fwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(wscanf, libc_wscanf);
DEFINE_PUBLIC_WEAK_ALIAS(wscanf_s, libc_wscanf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wscanf, libd_wscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vfwscanf, libc_vfwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vfwscanf_s, libc_vfwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vfwscanf, libd_vfwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vwscanf, libc_vwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(vwscanf_s, libc_vwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vwscanf, libd_vwscanf);
DEFINE_PUBLIC_WEAK_ALIAS(mbsnrtowcs, libc_mbsnrtowcs);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$mbsnrtowcs, libd_mbsnrtowcs);
DEFINE_PUBLIC_WEAK_ALIAS(wcsnrtombs, libc_wcsnrtombs);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wcsnrtombs, libd_wcsnrtombs);
DEFINE_PUBLIC_WEAK_ALIAS(open_wmemstream, libc_open_wmemstream);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$open_wmemstream, libd_open_wmemstream);
DEFINE_PUBLIC_WEAK_ALIAS(wcsdup, libc_wcsdup);
DEFINE_PUBLIC_WEAK_ALIAS(_wcsdup, libc_wcsdup);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wcsdup, libd_wcsdup);
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
DEFINE_PUBLIC_WEAK_ALIAS(_fgetwc_nolock, libc_fgetwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_getwc_nolock, libc_fgetwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_fgetwc_nolock, libd__fgetwc_nolock);
DEFINE_PUBLIC_WEAK_ALIAS(fputwc_unlocked, libc_fputwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(putwc_unlocked, libc_fputwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_fputwc_nolock, libc_fputwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_putwc_nolock, libc_fputwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_fputwc_nolock, libd__fputwc_nolock);
DEFINE_PUBLIC_WEAK_ALIAS(fgetws_unlocked, libc_fgetws_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_fgetws_nolock, libd_fgetws_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fputws_unlocked, libc_fputws_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_fputws_nolock, libd_fputws_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(file_wprinter, libc_file_wprinter);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$file_wprinter, libd_file_wprinter);
DEFINE_PUBLIC_WEAK_ALIAS(file_wprinter_unlocked, libc_file_wprinter_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$file_wprinter_unlocked, libd_file_wprinter_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(ungetwc_unlocked, libc_ungetwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(_ungetwc_nolock, libc_ungetwc_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_ungetwc_nolock, libd__ungetwc_nolock);
DEFINE_PUBLIC_WEAK_ALIAS(vfwprintf_unlocked, libc_vfwprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vfwprintf_unlocked, libd_vfwprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(fwprintf_unlocked, libc_fwprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$fwprintf_unlocked, libd_fwprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(wprintf_unlocked, libc_wprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$wprintf_unlocked, libd_wprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vwprintf_unlocked, libc_vwprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vwprintf_unlocked, libd_vwprintf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(vfwscanf_unlocked, libc_vfwscanf_unlocked);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$vfwscanf_unlocked, libd_vfwscanf_unlocked);
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
DEFINE_PUBLIC_WEAK_ALIAS(_vwprintf_p, libc__vwprintf_p);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_vwprintf_p, libd__vwprintf_p);
DEFINE_PUBLIC_WEAK_ALIAS(_wprintf_p, libc__wprintf_p);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wprintf_p, libd__wprintf_p);
DEFINE_PUBLIC_WEAK_ALIAS(_vwprintf_l, libc__vwprintf_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_vwprintf_l, libd__vwprintf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wprintf_l, libc__wprintf_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wprintf_l, libd__wprintf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_vwprintf_p_l, libc__vwprintf_p_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_vwprintf_p_l, libd__vwprintf_p_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wprintf_p_l, libc__wprintf_p_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wprintf_p_l, libd__wprintf_p_l);
DEFINE_PUBLIC_WEAK_ALIAS(_vwprintf_s_l, libc__vwprintf_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_vwprintf_s_l, libd__vwprintf_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wprintf_s_l, libc__wprintf_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wprintf_s_l, libd__wprintf_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(_vfwprintf_l, libc__vfwprintf_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_vfwprintf_l, libd__vfwprintf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_fwprintf_l, libc__fwprintf_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_fwprintf_l, libd__fwprintf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_vfwprintf_s_l, libc__vfwprintf_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_vfwprintf_s_l, libd__vfwprintf_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(_fwprintf_s_l, libc__fwprintf_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_fwprintf_s_l, libd__fwprintf_s_l);
DEFINE_PUBLIC_WEAK_ALIAS(_fwscanf_l, libc__fwscanf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_fwscanf_s_l, libc__fwscanf_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_fwscanf_l, libd__fwscanf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wscanf_l, libc__wscanf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wscanf_s_l, libc__wscanf_l);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wscanf_l, libd__wscanf_l);
DEFINE_PUBLIC_WEAK_ALIAS(_wfsopen, libc__wfsopen);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wfsopen, libd__wfsopen);
DEFINE_PUBLIC_WEAK_ALIAS(_wfdopen, libc__wfdopen);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wfdopen, libd__wfdopen);
DEFINE_PUBLIC_WEAK_ALIAS(_wfopen_s, libc__wfopen_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wfopen_s, libd__wfopen_s);
DEFINE_PUBLIC_WEAK_ALIAS(_wfreopen_s, libc__wfreopen_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wfreopen_s, libd__wfreopen_s);
DEFINE_PUBLIC_WEAK_ALIAS(_getws_s, libc__getws_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_getws_s, libd__getws_s);
DEFINE_PUBLIC_WEAK_ALIAS(_putws, libc__putws);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_putws, libd__putws);
DEFINE_PUBLIC_WEAK_ALIAS(_wtempnam, libc__wtempnam);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wtempnam, libd__wtempnam);
DEFINE_PUBLIC_WEAK_ALIAS(_wtmpnam_s, libc__wtmpnam_s);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$_wtmpnam_s, libd__wtmpnam_s);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_WCHAR_C */
